"""Run the StandardSim sensitivity DOE end to end."""

from __future__ import annotations

import time

from pipeline.aggregator import aggregate
from pipeline.build_pipeline import build_all
from pipeline.orchestration import (
    AGGREGATOR_CONFIG,
    ARCHITECTURE_CONFIG,
    COMPILER_CONFIG,
    DOE_CONFIG,
    POPULATION_DIR,
    elapsed,
    prepare_variants,
    stage,
)


def run() -> None:
    t_total = time.time()

    stage(1, 4, "Sampling and generating vehicle variants")
    t = time.time()
    variants = prepare_variants(force_rebuild=False)
    print(f"Prepared {len(variants)} variants ({elapsed(t)})")

    stage(2, 4, "Building and simulating StandardSim variants")
    t = time.time()
    build_all(
        POPULATION_DIR,
        COMPILER_CONFIG,
        doe_config_path=DOE_CONFIG,
        architecture_config_path=ARCHITECTURE_CONFIG,
    )
    print(f"Done ({elapsed(t)})")

    stage(3, 4, "Aggregating StandardSim metrics")
    t = time.time()
    df = aggregate(POPULATION_DIR, DOE_CONFIG, AGGREGATOR_CONFIG)
    print(f"Done ({elapsed(t)})")

    stage(4, 4, "Complete")
    print(f"Total {elapsed(t_total)}")
    print(df.to_string())


if __name__ == "__main__":
    run()
