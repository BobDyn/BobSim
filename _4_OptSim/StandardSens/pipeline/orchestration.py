"""Shared OptSim orchestration helpers for sensitivity runners."""

from __future__ import annotations

from pathlib import Path
import shutil

import pandas as pd

from StandardSens.pipeline.generate_configs import refresh_doe_config
from StandardSens.pipeline.generator import generate_variants
from StandardSens.pipeline.sampler import sample


STANDARD_DIR = Path(__file__).resolve().parents[1]
OPTSIM_DIR = STANDARD_DIR.parent
DOE_CONFIG = STANDARD_DIR / "configs/_doe_config.yaml"
COMPILER_CONFIG = STANDARD_DIR / "configs/compiler_config.yaml"
AGGREGATOR_CONFIG = STANDARD_DIR / "configs/aggregator_config.yaml"
ARCHITECTURE_CONFIG = STANDARD_DIR / "configs/vehicle_architecture.yaml"
STANDARD_BUILD_DIR = OPTSIM_DIR / "Build" / "StandardSens"
POPULATION_DIR = STANDARD_BUILD_DIR / "population"
RESULTS_DIR = OPTSIM_DIR / "results"


def clean_population(population_dir: Path = POPULATION_DIR) -> None:
    population_dir.mkdir(parents=True, exist_ok=True)
    for variant_dir in population_dir.glob("variant_????"):
        if variant_dir.is_dir():
            shutil.rmtree(variant_dir)
    for cache_file in (".pipeline.hash",):
        path = population_dir / cache_file
        if path.exists():
            path.unlink()


def prepare_variants(
    *,
    force_rebuild: bool = False,
    population_dir: Path = POPULATION_DIR,
) -> list[dict[str, float]]:
    print("Refreshing DOE config from selected vehicle architecture")
    refresh_doe_config(
        architecture_config_path=ARCHITECTURE_CONFIG,
        compiler_config_path=COMPILER_CONFIG,
        doe_config_path=DOE_CONFIG,
    )

    variants = sample(DOE_CONFIG)

    if force_rebuild:
        clean_population(population_dir)

    existing = len(list(population_dir.glob("variant_????")))
    if existing > 0 and existing != len(variants):
        raise RuntimeError(
            f"\nPopulation mismatch: {existing} variants on disk, "
            f"{len(variants)} in config.\n"
            "DOE sampling is not incrementally extensible.\n"
            "Run 'make clean-doe' then rerun.\n"
        )

    generate_variants(DOE_CONFIG, variants, population_dir)
    return variants


def write_variant_table(
    variants: list[dict[str, float]],
    output_path: Path,
) -> pd.DataFrame:
    rows = [
        {"variant": f"variant_{i:04d}", **params}
        for i, params in enumerate(variants)
    ]
    df = pd.DataFrame(rows)

    output_path.parent.mkdir(parents=True, exist_ok=True)
    df.to_csv(output_path, index=False)
    return df
