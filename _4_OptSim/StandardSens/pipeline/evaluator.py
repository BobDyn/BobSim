"""evaluator.py — Turn a knob setting into SteadyStateEval metrics, cheaply.

A sweep compiles every variant, and the compile is most of a variant's wall time
even though the model's equations never change. This evaluator compiles only
when it has to. Knobs in `overrides.RUNTIME_SAFE_PATHS` are applied to a cached
executable with `-override`; every other value gets its own executable, cached by
value. That default is the slow one on purpose: a compile is always correct, and
a wrong override is silent. See `overrides.py` for why the list is what it is.

Executables live in a `VariantStore` and evaluations beside it; both are
discarded when BobLib, the vehicle or the SteadyStateEval tooling changes. The
star design does not depend on the targets, so a second solve against new targets
reuses every star evaluation and pays only for verification.
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

from StandardSens.pipeline import overrides as ov
from StandardSens.pipeline.generator import build_context, read_metrics_csv
from StandardSens.pipeline.orchestration import STANDARD_BUILD_DIR
from StandardSens.pipeline.sampler import read_baseline
from StandardSens.pipeline.steady_state_eval_report import Isoline, run_report
from StandardSens.pipeline.variants import BUILD_STANDARD, VariantStore, split_cpus, variant_key

SOLVE_DIR = STANDARD_BUILD_DIR / "solve"
EVALUATION_TIMEOUT_S = 1800

Variant = dict[str, float]
Metrics = dict[str, float]


class SteadyStateEvaluator:
    """Callable mapping a batch of variants to their SteadyStateEval metrics."""

    def __init__(self, *, isoline: Isoline, cpus: int) -> None:
        # Longest cases first: they are the high-a_y ones, and queued last they
        # all land in the final wave and set its length.
        self.isoline = Isoline(
            float(isoline.velocity_mps), tuple(sorted(map(float, isoline.target_ays), reverse=True))
        )
        self.cpus = max(1, int(cpus))

        self.store = VariantStore(SOLVE_DIR)
        self.evals_dir = SOLVE_DIR / "evals"
        if self.store.was_reset:
            shutil.rmtree(self.evals_dir, ignore_errors=True)

        cfg = self.store.doe_config
        self.variables: dict[str, dict[str, Any]] = {v["path"]: v for v in cfg["variables"]}
        self.context = build_context(cfg, self.store.doe_config_path)
        self.baseline: Variant = read_baseline(Path(cfg["baseline_mo"]), cfg["variables"])
        self._init_cache: dict[Path, dict[str, ov.InitParameter]] = {}

    def __call__(self, variants: list[Variant]) -> list[Metrics]:
        pending = [v for v in variants if not self._metrics_path(v).exists()]
        if pending:
            compiled = [compiled_part(v, self.baseline) for v in pending]
            self.store.ensure_compiled(compiled)
            for vehicle in compiled:  # parse each init XML once, before the threads race to
                self._init_parameters(self.store.build_dir(vehicle))

            concurrent, workers = split_cpus(len(pending), self.cpus)
            workers = min(workers, len(self.isoline.target_ays))
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
        build_dir = self.store.build_dir(compiled_part(variant, self.baseline))
        runtime = {p: v for p, v in variant.items() if p in ov.RUNTIME_SAFE_PATHS}
        eval_dir = self._eval_dir(variant)
        eval_dir.mkdir(parents=True, exist_ok=True)
        (eval_dir / "variant.json").write_text(json.dumps(variant, indent=1, sort_keys=True))
        run_report(
            variant_dir=eval_dir,
            build_dir=build_dir,
            exec_name=self.store.standard_cfg["model"],
            timeout=EVALUATION_TIMEOUT_S,
            init_parameters=ov.variant_overrides(
                runtime, self.variables, self.context, self._init_parameters(build_dir)
            ),
            isoline=self.isoline,
            max_workers=workers,
            render_report=False,  # the solver reads the metrics CSV, never the PDF
        )

    def _init_parameters(self, build_dir: Path) -> dict[str, ov.InitParameter]:
        if build_dir not in self._init_cache:
            init_xml = ov.find_init_xml(build_dir, self.store.standard_cfg["model"])
            self._init_cache[build_dir] = ov.load_init_parameters(init_xml)
        return self._init_cache[build_dir]

    def _eval_dir(self, variant: Variant) -> Path:
        payload = json.dumps({"variant": variant_key(variant), "isoline": self.isoline})
        return self.evals_dir / hashlib.sha1(payload.encode()).hexdigest()[:16]

    def _metrics_path(self, variant: Variant) -> Path:
        return self._eval_dir(variant) / "results" / BUILD_STANDARD / "metrics.csv"


def compiled_part(variant: Variant, baseline: Variant) -> Variant:
    """The changes that decide which executable a variant needs.

    Runtime-safe knobs never appear, so every setting of them shares one
    executable. A compile-only knob left at its baseline does not appear either,
    so it shares the baseline executable instead of forcing an identical rebuild.
    """
    return {
        path: value
        for path, value in variant.items()
        if path not in ov.RUNTIME_SAFE_PATHS
        and not math.isclose(value, baseline[path], rel_tol=1e-12, abs_tol=1e-12)
    }
