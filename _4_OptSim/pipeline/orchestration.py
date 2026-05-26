"""Shared OptSim orchestration helpers for sensitivity runners."""

from __future__ import annotations

import time
from pathlib import Path
import shutil

import pandas as pd

from pipeline.generate_configs import refresh_doe_config
from pipeline.generator import generate_variants
from pipeline.sampler import sample


DOE_DIR = Path(__file__).resolve().parent.parent
DOE_CONFIG = DOE_DIR / "configs/_doe_config.yaml"
COMPILER_CONFIG = DOE_DIR / "configs/compiler_config.yaml"
AGGREGATOR_CONFIG = DOE_DIR / "configs/aggregator_config.yaml"
ARCHITECTURE_CONFIG = DOE_DIR / "configs/vehicle_architecture.yaml"
POPULATION_DIR = DOE_DIR / "population"
RESULTS_DIR = DOE_DIR / "results"


def stage(n: int, total: int, name: str) -> None:
    print(f"\n{'=' * 60}")
    print(f"  {n} / {total}  -  {name}")
    print(f"{'=' * 60}\n")


def elapsed(t0: float) -> str:
    return f"{time.time() - t0:.1f}s"


def clean_population() -> None:
    POPULATION_DIR.mkdir(parents=True, exist_ok=True)
    for variant_dir in POPULATION_DIR.glob("variant_????"):
        if variant_dir.is_dir():
            shutil.rmtree(variant_dir)
    for cache_file in (".pipeline.hash",):
        path = POPULATION_DIR / cache_file
        if path.exists():
            path.unlink()


def prepare_variants(*, force_rebuild: bool = False) -> list[dict[str, float]]:
    print("Refreshing DOE config from selected vehicle architecture")
    refresh_doe_config(
        architecture_config_path=ARCHITECTURE_CONFIG,
        compiler_config_path=COMPILER_CONFIG,
        doe_config_path=DOE_CONFIG,
    )

    variants = sample(DOE_CONFIG)

    if force_rebuild:
        clean_population()

    existing = len(list(POPULATION_DIR.glob("variant_????")))
    if existing > 0 and existing != len(variants):
        raise RuntimeError(
            f"\nPopulation mismatch: {existing} variants on disk, "
            f"{len(variants)} in config.\n"
            "DOE sampling is not incrementally extensible.\n"
            "Run 'make clean-doe' then rerun.\n"
        )

    generate_variants(DOE_CONFIG, variants, POPULATION_DIR)
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
