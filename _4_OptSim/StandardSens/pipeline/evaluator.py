"""evaluator.py — Turn a knob setting into SteadyStateEval metrics, cheaply.

A sweep compiles every variant, and the compile is about 70 % of a variant's
wall time even though the model's equations never change. This evaluator only
compiles when it has to:

- **Runtime knobs** — springs, anti-roll bars, dampers — are read by the model at
  initialisation, so they are applied to an existing executable with
  `-override`. No compile.
- **Compile-only knobs** — toe, camber, anything mass- or CG-derived — feed
  parameters OpenModelica evaluates at compile time. Static toe and camber build
  the wheel's `toHub.R_rel` rotation matrix, which is baked into the executable;
  overriding the angle afterwards changes a number nothing reads, and the
  executable reports no error. Those values get their own compile, cached by
  value.

Which family a knob belongs to is declared in `solve_config.yaml`, and anything
not declared is compiled. That default is the slow one on purpose: a compile is
always correct, and a wrong override is silent.

Both executables and evaluations are cached on disk under the solve directory.
The star design does not depend on the targets, so a second solve against new
targets reuses every star evaluation and pays only for verification.
"""

from __future__ import annotations

from concurrent.futures import ThreadPoolExecutor
import csv
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
    DEFAULT_ARCHITECTURE_CONFIG,
    DEFAULT_COMPILER_CONFIG,
    DEFAULT_DOE_CONFIG,
    DEFAULT_MODELICA_RUNNER,
    DEFAULT_REPORT_WRAPPER,
    DEFAULT_STEADY_STATE_CONFIG,
    DEFAULT_STEADY_STATE_SIM,
    _find_exe,
    compile_all,
    load_compiler_config,
)
from StandardSens.pipeline.generate_configs import SWEEP_SCOPE_ALL, refresh_doe_config
from StandardSens.pipeline.generator import build_context, generate_variants
from StandardSens.pipeline.sampler import read_baseline
from StandardSens.pipeline.steady_state_eval_report import run_report

STANDARD = "SteadyStateEval"
STANDARD_DIR = Path(__file__).resolve().parents[1]
DEFAULT_SOLVE_DIR = STANDARD_DIR.parent / "Build" / "StandardSens" / "solve"

Variant = dict[str, float]
Metrics = dict[str, float]


class SteadyStateEvaluator:
    """Callable mapping a batch of variants to their SteadyStateEval metrics."""

    def __init__(
        self,
        *,
        runtime_paths: set[str],
        test_matrix: dict[str, Any],
        solve_dir: Path = DEFAULT_SOLVE_DIR,
        case_workers: int = 4,
        parallel_evaluations: int = 3,
        timeout_s: int = 1800,
    ) -> None:
        self.solve_dir = solve_dir.resolve()
        self.exes_dir = self.solve_dir / "exes"
        self.evals_dir = self.solve_dir / "evals"
        self.runtime_paths = set(runtime_paths)
        self.test_matrix = test_matrix
        self.case_workers = int(case_workers)
        self.parallel_evaluations = max(1, int(parallel_evaluations))
        self.timeout_s = int(timeout_s)

        # The solver needs every variable's spec regardless of what scope the
        # last sweep ran at, and regenerating at `all` reproduces the committed
        # config, so this leaves no diff behind.
        refresh_doe_config(
            architecture_config_path=DEFAULT_ARCHITECTURE_CONFIG,
            compiler_config_path=DEFAULT_COMPILER_CONFIG,
            doe_config_path=DEFAULT_DOE_CONFIG,
            scope=SWEEP_SCOPE_ALL,
        )
        self.doe_config_path = DEFAULT_DOE_CONFIG.resolve()
        cfg = yaml.safe_load(self.doe_config_path.read_text())
        self.variables: dict[str, dict[str, Any]] = {v["path"]: v for v in cfg["variables"]}
        self.context = build_context(cfg, self.doe_config_path)
        baseline_mo = (self.doe_config_path.parent / cfg["baseline_mo"]).resolve()
        self.baseline: Variant = read_baseline(baseline_mo, cfg["variables"])

        compiler_cfg = load_compiler_config(DEFAULT_COMPILER_CONFIG)
        self.standard_cfg: dict[str, Any] = compiler_cfg["standards"][STANDARD]
        self._boblib_path = (
            DEFAULT_COMPILER_CONFIG.resolve().parent / compiler_cfg["boblib_path"]
        ).resolve()

        unknown = sorted(self.runtime_paths - set(self.variables))
        if unknown:
            raise KeyError(f"runtime_override names unknown DOE variables: {unknown}")

        self._init_cache: dict[Path, dict[str, ov.InitParameter]] = {}
        self._drop_caches_if_inputs_changed()

    # ------------------------------------------------------------------ planning

    def compile_key(self, variant: Variant) -> tuple[tuple[str, float], ...]:
        return compile_key(variant, self.runtime_paths, self.baseline)

    def plan(self, variants: list[Variant]) -> dict[str, int]:
        """Count what a batch will cost before anything is run."""
        compiled = self._load_index()
        keys = {self.compile_key(v) for v in variants}
        cached = sum(1 for v in variants if self._cached_metrics(v) is not None)
        return {
            "evaluations": len(variants),
            "cached_evaluations": cached,
            "executables_needed": len(keys),
            "compiles_needed": sum(1 for k in keys if _key_json(k) not in compiled),
        }

    # ---------------------------------------------------------------- evaluation

    def __call__(self, variants: list[Variant]) -> list[Metrics]:
        for variant in variants:
            unknown = sorted(set(variant) - set(self.variables))
            if unknown:
                raise KeyError(f"Not DOE variables: {unknown}")

        pending = [v for v in variants if self._cached_metrics(v) is None]
        if pending:
            self._ensure_executables({self.compile_key(v) for v in pending})
            print(
                f"Simulating {len(pending)} setup(s), {self.parallel_evaluations} at a time "
                f"({len(variants) - len(pending)} cached)...",
                flush=True,
            )
            started = time.time()
            with ThreadPoolExecutor(max_workers=self.parallel_evaluations) as pool:
                for done, _ in enumerate(pool.map(self._simulate, pending), start=1):
                    print(f"  [{done}/{len(pending)}] {time.time() - started:.0f}s", flush=True)

        results = []
        for variant in variants:
            metrics = self._cached_metrics(variant)
            if metrics is None:
                raise RuntimeError(f"Evaluation produced no metrics for {variant}")
            results.append(metrics)
        return results

    def _simulate(self, variant: Variant) -> None:
        build_dir = self._build_dir(self.compile_key(variant))
        runtime = {p: v for p, v in variant.items() if p in self.runtime_paths}
        init_parameters = ov.variant_overrides(
            runtime, self.variables, self.context, self._init_parameters(build_dir)
        )
        eval_dir = self._eval_dir(variant)
        eval_dir.mkdir(parents=True, exist_ok=True)
        (eval_dir / "variant.json").write_text(json.dumps(variant, indent=1, sort_keys=True))
        run_report(
            variant_dir=eval_dir,
            build_dir=build_dir,
            exec_name=self.standard_cfg["model"],
            timeout=self.timeout_s,
            init_parameters=init_parameters,
            config_overrides=self._config_overrides(),
        )

    def _config_overrides(self) -> dict[str, dict[str, Any]]:
        velocity = float(self.test_matrix["velocity_mps"])
        target_ays = [float(a) for a in self.test_matrix["target_ays"]]
        return {
            "sweep": {
                "testVels": [velocity],
                "targetAys": target_ays,
                "maxAyByVelocity": {velocity: max(target_ays)},
            },
            "execution": {"parallel": True, "max_workers": self.case_workers},
            "report": {"metric_target_velocity_mps": velocity},
        }

    # --------------------------------------------------------------- executables

    def _ensure_executables(self, keys: set[tuple[tuple[str, float], ...]]) -> None:
        index = self._load_index()
        new = [k for k in sorted(keys) if _key_json(k) not in index]
        if new:
            for key in new:
                index[_key_json(key)] = len(index)
            ordered = sorted(index, key=index.__getitem__)
            self.exes_dir.mkdir(parents=True, exist_ok=True)
            generate_variants(
                self.doe_config_path,
                [dict(json.loads(entry)) for entry in ordered],
                self.exes_dir,
            )
            self._index_path.write_text(json.dumps(index, indent=1))
            print(f"Compiling {len(new)} executable(s) for compile-only knob values...")
        compile_all(self.exes_dir, DEFAULT_COMPILER_CONFIG, doe_config_path=self.doe_config_path)

        for key in keys:
            build_dir = self._build_dir(key)
            if _find_exe(build_dir, self.standard_cfg) is None:
                log = build_dir.parents[1] / f"compile_error_{STANDARD}.log"
                detail = log.read_text()[-2000:] if log.exists() else "no compile log written"
                raise RuntimeError(f"Compile failed for {dict(key) or 'baseline'}:\n{detail}")

    def _build_dir(self, key: tuple[tuple[str, float], ...]) -> Path:
        index = self._load_index()
        return self.exes_dir / f"variant_{index[_key_json(key)]:04d}" / "build" / STANDARD

    def _init_parameters(self, build_dir: Path) -> dict[str, ov.InitParameter]:
        if build_dir not in self._init_cache:
            init_xml = ov.find_init_xml(build_dir, self.standard_cfg["model"])
            self._init_cache[build_dir] = ov.load_init_parameters(init_xml)
        return self._init_cache[build_dir]

    @property
    def _index_path(self) -> Path:
        return self.exes_dir / "index.json"

    def _load_index(self) -> dict[str, int]:
        if not self._index_path.exists():
            return {}
        return dict(json.loads(self._index_path.read_text()))

    # --------------------------------------------------------------------- cache

    def _eval_dir(self, variant: Variant) -> Path:
        payload = json.dumps(
            {
                "variant": {p: _round(v) for p, v in sorted(variant.items())},
                "matrix": self.test_matrix,
            },
            sort_keys=True,
        )
        return self.evals_dir / hashlib.sha1(payload.encode()).hexdigest()[:16]

    def _cached_metrics(self, variant: Variant) -> Metrics | None:
        path = self._eval_dir(variant) / "results" / STANDARD / "metrics.csv"
        if not path.exists():
            return None
        metrics: Metrics = {}
        with path.open(newline="", encoding="utf-8") as handle:
            for row in csv.DictReader(handle):
                try:
                    metrics[row["metric"]] = float(row["value"])
                except (KeyError, TypeError, ValueError):
                    continue
        return metrics or None

    def _drop_caches_if_inputs_changed(self) -> None:
        """A cache must never outlive the inputs it was built from."""
        if not self.exes_dir.exists():
            return
        try:
            check_pipeline_hash(
                self.exes_dir,
                self.doe_config_path,
                DEFAULT_COMPILER_CONFIG,
                self._boblib_path,
                DEFAULT_ARCHITECTURE_CONFIG,
                (
                    DEFAULT_REPORT_WRAPPER,
                    DEFAULT_STEADY_STATE_SIM,
                    DEFAULT_STEADY_STATE_CONFIG,
                    DEFAULT_MODELICA_RUNNER,
                ),
            )
        except RuntimeError:
            print(
                "Solver cache predates a change to BobLib, the vehicle, or the "
                "SteadyStateEval tooling; discarding it."
            )
            shutil.rmtree(self.solve_dir)


def compile_key(
    variant: Variant, runtime_paths: set[str], baseline: Variant
) -> tuple[tuple[str, float], ...]:
    """The compile-only values that decide which executable a variant needs.

    Runtime knobs never appear, so every setting of them shares one executable.
    A compile-only knob left at its baseline does not appear either, so it
    shares the baseline executable instead of forcing an identical rebuild.
    """
    return tuple(
        sorted(
            (path, _round(value))
            for path, value in variant.items()
            if path not in runtime_paths
            and not math.isclose(value, baseline[path], rel_tol=1e-12, abs_tol=1e-12)
        )
    )


def _round(value: float) -> float:
    """Collapse float noise so equal settings share a cache entry."""
    return float(f"{float(value):.12g}")


def _key_json(key: tuple[tuple[str, float], ...]) -> str:
    return json.dumps(dict(key), sort_keys=True)
