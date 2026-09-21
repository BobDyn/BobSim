"""Turn a knob setting into SteadyStateEval metrics.

Knobs in `overrides.RUNTIME_SAFE_PATHS` go to a cached executable with `-override`.
Every other value gets its own compiled executable, cached by value.
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
from StandardSens.pipeline.standards import case_loss
from StandardSens.pipeline.steady_state_eval_report import Isoline, run_report
from StandardSens.pipeline.variants import BUILD_STANDARD, VariantStore, split_cpus, variant_key

SOLVE_DIR = STANDARD_BUILD_DIR / "solve"
EVALUATION_TIMEOUT_S = 1800

Variant = dict[str, float]
Metrics = dict[str, float]


class SteadyStateEvaluator:
    """Callable mapping a batch of variants to their SteadyStateEval metrics."""

    def __init__(self, *, isoline: Isoline, cpus: int) -> None:
        # Longest (high a_y) cases first, so they do not all land in the final wave.
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
            for vehicle in compiled:  # parse each init XML once, before the threads start
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

        results = [read_metrics_csv(self._metrics_path(v)) for v in variants]
        for variant, metrics in zip(variants, results, strict=True):
            require_whole(variant, metrics)
        return results

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
            render_report=False,
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


def require_whole(variant: Variant, metrics: Metrics) -> None:
    """Refuse an evaluation that lost simulation cases. It would silently skew the cached surrogate."""
    why = case_loss(metrics)
    if why:
        raise RuntimeError(
            f"SteadyStateEval was not whole for {variant}: {why}. Its metrics are not "
            "comparable with the other evaluations, so the solve stops here rather than "
            "fit through them. The usual cause is a target a_y this setup cannot settle "
            "at: lower the top of `test_matrix.target_ays` in solve_config.yaml (which "
            "re-simulates the star), or inspect the run under Build/StandardSens/solve/."
        )


def compiled_part(variant: Variant, baseline: Variant) -> Variant:
    """Return the changes that decide which executable a variant needs.

    Runtime-safe knobs and compile-only knobs at baseline are left out, so they share an executable.
    """
    return {
        path: value
        for path, value in variant.items()
        if path not in ov.RUNTIME_SAFE_PATHS
        and not math.isclose(value, baseline[path], rel_tol=1e-12, abs_tol=1e-12)
    }
