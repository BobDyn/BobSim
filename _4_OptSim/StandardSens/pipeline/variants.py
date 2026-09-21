"""variants.py — A cache of compiled vehicles, addressed by what was changed.

The sweep numbers its variants in sampling order, which is right for a population
that is generated once. The solver and the trade study instead ask for vehicles
by content — "the baseline with this toe", "the car with the stiff rear bar" —
repeatedly and in no fixed order, and a compile is the most expensive thing either
does. This store maps each distinct set of changes to one compiled variant
directory, compiles whatever is missing in a single parallel batch, and throws
everything away when BobLib, the vehicle or the simulation tooling changes.

It reuses the sweep's generator and compiler unchanged, so a variant here is
compiled exactly as the same variant in a sweep would be.
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

# Every VehicleSim standard runs the executable the sweep builds for this one.
BUILD_STANDARD = "SteadyStateEval"

Variant = dict[str, float]


def split_cpus(n_jobs: int, cpus: int, min_workers: int = 4) -> tuple[int, int]:
    """Return (jobs to run at once, case workers for each).

    Simulation throughput on a 12-CPU container was 1.9x higher with every CPU
    busy than with four, so concurrent jobs are preferred until each would drop
    below `min_workers`; a lone job gets every CPU.
    """
    concurrent = max(1, min(n_jobs, cpus // min_workers))
    return concurrent, max(1, cpus // concurrent)


def variant_key(variant: Variant) -> str:
    """Canonical text for a set of changes; float noise must not split an entry."""
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
        boblib_path = (COMPILER_CONFIG.resolve().parent / compiler_cfg["boblib_path"]).resolve()

        self.was_reset = self._drop_if_inputs_changed(boblib_path)
        index_path = self.variants_dir / "index.json"
        self._index: dict[str, int] = json.loads(index_path.read_text()) if index_path.exists() else {}

    def _write_own_doe_config(self) -> dict[str, Any]:
        """Generate a DOE config here rather than over the sweep's.

        The sweep's `_doe_config.yaml` is committed and records the scope its
        population was built at, which `opt-search` relies on. Consumers of this
        store need every variable's spec whatever that scope was, so they keep
        their own copy. The generated file names the baseline record and vehicle
        template relative to the sweep's config directory; here they are made
        absolute so they resolve from anywhere.
        """
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

    def _drop_if_inputs_changed(self, boblib_path: Path) -> bool:
        """A cache must never outlive the inputs it was built from."""
        if not self.variants_dir.exists():
            return False
        try:
            # The same call compile_all makes, so the two cannot disagree about
            # what counts as stale.
            check_pipeline_hash(
                self.variants_dir,
                self.doe_config_path,
                COMPILER_CONFIG,
                boblib_path,
                ARCHITECTURE_CONFIG,
                PIPELINE_TOOLING_INPUTS,
            )
        except RuntimeError:
            print(
                f"Cache under {self.root.name}/ predates a change to BobLib, the vehicle, or "
                "the simulation tooling; discarding it."
            )
            shutil.rmtree(self.variants_dir)
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
