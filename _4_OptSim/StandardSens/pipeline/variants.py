"""A cache of compiled vehicles, keyed by the set of changes from baseline.

Uses the sweep's generator and compiler. The cache is dropped when pipeline inputs change.
"""

from __future__ import annotations

import json
from pathlib import Path
import shutil
from typing import Any

import yaml

from StandardSens.pipeline._pipeline_hash import check_pipeline_hash
from StandardSens.pipeline.compiler import (
    PIPELINE_TOOLING_INPUTS,
    compile_all,
    find_exe,
    load_compiler_config,
)
from StandardSens.pipeline.generate_configs import SWEEP_SCOPE_ALL, refresh_doe_config
from StandardSens.pipeline.generator import generate_variants
from StandardSens.pipeline.orchestration import ARCHITECTURE_CONFIG, COMPILER_CONFIG, DOE_CONFIG

# Every VehicleSim standard runs the executable built for this one.
BUILD_STANDARD = "SteadyStateEval"

Variant = dict[str, float]


def split_cpus(n_jobs: int, cpus: int, min_workers: int = 4) -> tuple[int, int]:
    """Return (jobs to run at once, case workers for each). Keeps every CPU busy."""
    concurrent = max(1, min(n_jobs, cpus // min_workers))
    return concurrent, max(1, cpus // concurrent)


def variant_key(variant: Variant) -> str:
    """Canonical text for a set of changes. Rounds so float noise does not split an entry."""
    return json.dumps({p: float(f"{float(v):.12g}") for p, v in sorted(variant.items())})


class VariantStore:
    def __init__(self, root: Path) -> None:
        self.root = root.resolve()
        self.root.mkdir(parents=True, exist_ok=True)
        self.variants_dir = self.root / "variants"
        self.doe_config_path = self.root / "_doe_config.yaml"
        self.doe_config = self._write_own_doe_config()

        compiler_cfg = load_compiler_config(COMPILER_CONFIG)
        self.standard_cfg: dict[str, Any] = compiler_cfg["standards"][BUILD_STANDARD]
        self._boblib_path = (
            COMPILER_CONFIG.resolve().parent / compiler_cfg["boblib_path"]
        ).resolve()

        # A cache must never outlive the inputs it was built from.
        self.was_reset = self.variants_dir.exists() and self._inputs_changed()
        if self.was_reset:
            print(
                f"Cache under {self.root.name}/ predates a change to BobLib, the vehicle, or "
                "the simulation tooling; discarding it."
            )
            shutil.rmtree(self.variants_dir)
        index_path = self.variants_dir / "index.json"
        self._index: dict[str, int] = json.loads(index_path.read_text()) if index_path.exists() else {}

    def _write_own_doe_config(self) -> dict[str, Any]:
        """Write an all-scope DOE config here, with absolute paths. The sweep's copy records its scope."""
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

    def _inputs_changed(self) -> bool:
        """Whether the inputs differ from the ones the compiled variants were built from."""
        try:
            # Same call as compile_all, so both agree on what is stale.
            check_pipeline_hash(
                self.variants_dir,
                self.doe_config_path,
                COMPILER_CONFIG,
                self._boblib_path,
                ARCHITECTURE_CONFIG,
                PIPELINE_TOOLING_INPUTS,
            )
        except RuntimeError:
            return True
        return False

    def variant_dir(self, variant: Variant) -> Path:
        return self.variants_dir / f"variant_{self._index[variant_key(variant)]:04d}"

    def build_dir(self, variant: Variant) -> Path:
        return self.variant_dir(variant) / "build" / BUILD_STANDARD

    def ensure_compiled(self, variants: list[Variant]) -> None:
        """Compile whichever of these vehicles has no executable yet, in one batch."""
        new = sorted({variant_key(v) for v in variants} - set(self._index))
        if not new and all(find_exe(self.build_dir(v), self.standard_cfg) for v in variants):
            return

        if self.variants_dir.exists() and self._inputs_changed():
            # Only reachable mid-run: a stale cache is discarded at construction.
            raise RuntimeError(
                "BobLib, the vehicle or the simulation tooling changed while this run was in "
                "progress, so the vehicles already simulated and the ones still to compile "
                "would not be comparable. Nothing on disk is damaged: run it again once the "
                "edits have settled, and the cache will be rebuilt against the current inputs."
            )

        for key in new:
            self._index[key] = len(self._index)
        self.variants_dir.mkdir(parents=True, exist_ok=True)
        ordered = sorted(self._index, key=self._index.__getitem__)
        generate_variants(self.doe_config_path, [json.loads(key) for key in ordered], self.variants_dir)
        (self.variants_dir / "index.json").write_text(json.dumps(self._index, indent=1))
        compile_all(
            self.variants_dir,
            COMPILER_CONFIG,
            doe_config_path=self.doe_config_path,
            only_standards=(BUILD_STANDARD,),
        )

        for variant in variants:
            if find_exe(self.build_dir(variant), self.standard_cfg) is None:
                log = self.variant_dir(variant) / f"compile_error_{BUILD_STANDARD}.log"
                detail = log.read_text()[-2000:] if log.exists() else "no compile log written"
                raise RuntimeError(f"Compile failed for {variant or 'the baseline'}:\n{detail}")
