"""evaluator.py — Turn a knob setting into SteadyStateEval metrics, cheaply.

A sweep compiles every variant, and the compile is most of a variant's wall time
even though the model's equations never change. This evaluator compiles only
when it has to. Knobs in `overrides.RUNTIME_SAFE_PATHS` are applied to a cached
executable with `-override`; every other value gets its own executable, cached by
value. That default is the slow one on purpose: a compile is always correct, and
a wrong override is silent. See `overrides.py` for why the list is what it is.

Executables and evaluations are cached under the solve directory, and discarded
when BobLib, the vehicle or the SteadyStateEval tooling changes. The star design
does not depend on the targets, so a second solve against new targets reuses
every star evaluation and pays only for verification.
"""

from __future__ import annotations

from concurrent.futures import ThreadPoolExecutor
from functools import partial
import hashlib
import json
import math
from pathlib import Path
import shutil
import time
from typing import Any

import yaml

from StandardSens.pipeline import overrides as ov
from StandardSens.pipeline._pipeline_hash import check_pipeline_hash
from StandardSens.pipeline.compiler import (
    PIPELINE_TOOLING_INPUTS,
    compile_all,
    find_exe,
    load_compiler_config,
)
from StandardSens.pipeline.generate_configs import SWEEP_SCOPE_ALL, refresh_doe_config
from StandardSens.pipeline.generator import build_context, generate_variants, read_metrics_csv
from StandardSens.pipeline.orchestration import (
    ARCHITECTURE_CONFIG,
    COMPILER_CONFIG,
    DOE_CONFIG,
    STANDARD_BUILD_DIR,
)
from StandardSens.pipeline.sampler import read_baseline
from StandardSens.pipeline.steady_state_eval_report import Isoline, run_report

STANDARD = "SteadyStateEval"
SOLVE_DIR = STANDARD_BUILD_DIR / "solve"
EVALUATION_TIMEOUT_S = 1800

# Simulation throughput on a 12-CPU container was 1.9x higher with every CPU busy
# than with four, so concurrent evaluations are preferred until each would drop
# below this many case workers.
MIN_CASE_WORKERS = 4

Variant = dict[str, float]
Metrics = dict[str, float]
CompileKey = tuple[tuple[str, float], ...]


class SteadyStateEvaluator:
    """Callable mapping a batch of variants to their SteadyStateEval metrics."""

    def __init__(self, *, isoline: Isoline, cpus: int) -> None:
        # Longest cases first: they are the high-a_y ones, and queued last they
        # all land in the final wave and set its length.
        self.isoline = Isoline(
            float(isoline.velocity_mps), tuple(sorted(map(float, isoline.target_ays), reverse=True))
        )
        self.cpus = max(1, int(cpus))
        self.exes_dir = SOLVE_DIR / "exes"
        self.evals_dir = SOLVE_DIR / "evals"

        cfg = self._write_own_doe_config()
        self.variables: dict[str, dict[str, Any]] = {v["path"]: v for v in cfg["variables"]}
        self.context = build_context(cfg, self.doe_config_path)
        self.baseline: Variant = read_baseline(Path(cfg["baseline_mo"]), cfg["variables"])

        compiler_cfg = load_compiler_config(COMPILER_CONFIG)
        self.standard_cfg: dict[str, Any] = compiler_cfg["standards"][STANDARD]
        boblib_path = (COMPILER_CONFIG.resolve().parent / compiler_cfg["boblib_path"]).resolve()

        self._drop_caches_if_inputs_changed(boblib_path)
        self._index: dict[str, int] = (
            json.loads(self._index_path.read_text()) if self._index_path.exists() else {}
        )
        self._init_cache: dict[Path, dict[str, ov.InitParameter]] = {}

    def _write_own_doe_config(self) -> dict[str, Any]:
        """Generate the solver's DOE config beside its caches, not over the sweep's.

        The sweep's `_doe_config.yaml` is committed and records the scope its
        population was built at, which `opt-search` relies on. The solver needs
        every variable's spec whatever that scope was, so it keeps its own copy.
        The generated file names the baseline record and vehicle template
        relative to the sweep's config directory; here they are made absolute so
        they resolve from anywhere.
        """
        self.doe_config_path = (SOLVE_DIR / "_doe_config.yaml").resolve()
        self.doe_config_path.parent.mkdir(parents=True, exist_ok=True)
        cfg = refresh_doe_config(
            architecture_config_path=ARCHITECTURE_CONFIG,
            compiler_config_path=COMPILER_CONFIG,
            doe_config_path=self.doe_config_path,
            scope=SWEEP_SCOPE_ALL,
        )
        config_dir = DOE_CONFIG.resolve().parent
        cfg["baseline_mo"] = (config_dir / cfg["baseline_mo"]).resolve().as_posix()
        cfg["architecture"]["template"] = (
            (config_dir.parent / cfg["architecture"]["template"]).resolve().as_posix()
        )
        self.doe_config_path.write_text(yaml.safe_dump(cfg, sort_keys=False))
        return cfg

    # ---------------------------------------------------------------- evaluation

    def __call__(self, variants: list[Variant]) -> list[Metrics]:
        pending = [v for v in variants if not self._metrics_path(v).exists()]
        if pending:
            keys = {compile_key(v, self.baseline) for v in pending}
            self._ensure_executables(keys)
            for key in keys:  # parse each init XML once, before the threads race to
                self._init_parameters(self._build_dir(key))

            concurrent = min(len(pending), max(1, self.cpus // MIN_CASE_WORKERS))
            workers = min(len(self.isoline.target_ays), max(1, self.cpus // concurrent))
            print(
                f"Simulating {len(pending)} setup(s), {concurrent} at a time with {workers} "
                f"case workers each ({len(variants) - len(pending)} cached)...",
                flush=True,
            )
            started = time.time()
            with ThreadPoolExecutor(max_workers=concurrent) as pool:
                simulate = partial(self._simulate, workers=workers)
                for done, _ in enumerate(pool.map(simulate, pending), start=1):
                    print(f"  [{done}/{len(pending)}] {time.time() - started:.0f}s", flush=True)

        return [read_metrics_csv(self._metrics_path(v)) for v in variants]

    def _simulate(self, variant: Variant, *, workers: int) -> None:
        build_dir = self._build_dir(compile_key(variant, self.baseline))
        runtime = {p: v for p, v in variant.items() if p in ov.RUNTIME_SAFE_PATHS}
        eval_dir = self._eval_dir(variant)
        eval_dir.mkdir(parents=True, exist_ok=True)
        (eval_dir / "variant.json").write_text(json.dumps(variant, indent=1, sort_keys=True))
        run_report(
            variant_dir=eval_dir,
            build_dir=build_dir,
            exec_name=self.standard_cfg["model"],
            timeout=EVALUATION_TIMEOUT_S,
            init_parameters=ov.variant_overrides(
                runtime, self.variables, self.context, self._init_parameters(build_dir)
            ),
            isoline=self.isoline,
            max_workers=workers,
            render_report=False,  # the solver reads the metrics CSV, never the PDF
        )

    # --------------------------------------------------------------- executables

    def _ensure_executables(self, keys: set[CompileKey]) -> None:
        new = [k for k in sorted(keys) if _key_json(k) not in self._index]
        if not new and all(find_exe(self._build_dir(k), self.standard_cfg) for k in keys):
            return

        for key in new:
            self._index[_key_json(key)] = len(self._index)
        self.exes_dir.mkdir(parents=True, exist_ok=True)
        ordered = sorted(self._index, key=self._index.__getitem__)
        generate_variants(
            self.doe_config_path, [json.loads(entry) for entry in ordered], self.exes_dir
        )
        self._index_path.write_text(json.dumps(self._index, indent=1))
        compile_all(self.exes_dir, COMPILER_CONFIG, doe_config_path=self.doe_config_path)

        for key in keys:
            build_dir = self._build_dir(key)
            if find_exe(build_dir, self.standard_cfg) is None:
                log = build_dir.parents[1] / f"compile_error_{STANDARD}.log"
                detail = log.read_text()[-2000:] if log.exists() else "no compile log written"
                raise RuntimeError(f"Compile failed for {dict(key) or 'baseline'}:\n{detail}")

    def _build_dir(self, key: CompileKey) -> Path:
        return self.exes_dir / f"variant_{self._index[_key_json(key)]:04d}" / "build" / STANDARD

    def _init_parameters(self, build_dir: Path) -> dict[str, ov.InitParameter]:
        if build_dir not in self._init_cache:
            init_xml = ov.find_init_xml(build_dir, self.standard_cfg["model"])
            self._init_cache[build_dir] = ov.load_init_parameters(init_xml)
        return self._init_cache[build_dir]

    @property
    def _index_path(self) -> Path:
        return self.exes_dir / "index.json"

    # --------------------------------------------------------------------- cache

    def _eval_dir(self, variant: Variant) -> Path:
        payload = json.dumps(
            {"variant": {p: _round(v) for p, v in sorted(variant.items())}, "isoline": self.isoline},
            sort_keys=True,
        )
        return self.evals_dir / hashlib.sha1(payload.encode()).hexdigest()[:16]

    def _metrics_path(self, variant: Variant) -> Path:
        return self._eval_dir(variant) / "results" / STANDARD / "metrics.csv"

    def _drop_caches_if_inputs_changed(self, boblib_path: Path) -> None:
        """A cache must never outlive the inputs it was built from."""
        if not self.exes_dir.exists():
            return
        try:
            # The same call compile_all makes, so the two cannot disagree about
            # what counts as stale.
            check_pipeline_hash(
                self.exes_dir,
                self.doe_config_path,
                COMPILER_CONFIG,
                boblib_path,
                ARCHITECTURE_CONFIG,
                PIPELINE_TOOLING_INPUTS,
            )
        except RuntimeError:
            print(
                "Solver cache predates a change to BobLib, the vehicle, or the "
                "SteadyStateEval tooling; discarding it."
            )
            shutil.rmtree(self.exes_dir)
            shutil.rmtree(self.evals_dir, ignore_errors=True)


def compile_key(variant: Variant, baseline: Variant) -> CompileKey:
    """The compile-only values that decide which executable a variant needs.

    Runtime-safe knobs never appear, so every setting of them shares one
    executable. A compile-only knob left at its baseline does not appear either,
    so it shares the baseline executable instead of forcing an identical rebuild.
    """
    return tuple(
        sorted(
            (path, _round(value))
            for path, value in variant.items()
            if path not in ov.RUNTIME_SAFE_PATHS
            and not math.isclose(value, baseline[path], rel_tol=1e-12, abs_tol=1e-12)
        )
    )


def _round(value: float) -> float:
    """Collapse float noise so equal settings share a cache entry."""
    return float(f"{float(value):.12g}")


def _key_json(key: CompileKey) -> str:
    return json.dumps(dict(key), sort_keys=True)
