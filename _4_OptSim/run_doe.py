"""run_doe.py — Orchestrate the full DOE pipeline end to end.

Stages:
  1. sample    — LHS sample variants from _doe_config.yaml
  2. generate  — patch the selected vehicle record per variant → population/
  3. build     — compile each variant via OMC then immediately run its simulation
                 (pipelined per variant, parallel across variants)
  4. aggregate — collect metrics → results/doe_results.parquet

Safety checks:
  - Population count mismatch: raises if on-disk variant count differs from config
  - Stale artifacts: raises if pipeline inputs changed since last compile
  - Partial CSV: batch skips metrics.csv files with insufficient rows
"""

from __future__ import annotations

import time
from pathlib import Path

from pipeline.aggregator import aggregate
from pipeline.build_pipeline import build_all
from pipeline.generate_configs import refresh_doe_config
from pipeline.generator import generate_variants
from pipeline.sampler import sample

# ---------------------------------------------------------------------------
# Paths
# ---------------------------------------------------------------------------

ROOT = Path(__file__).parent
DOE_CONFIG = ROOT / "configs/_doe_config.yaml"
COMPILER_CONFIG = ROOT / "configs/compiler_config.yaml"
AGGREGATOR_CONFIG = ROOT / "configs/aggregator_config.yaml"
ARCHITECTURE_CONFIG = ROOT / "configs/vehicle_architecture.yaml"
POPULATION_DIR = ROOT / "population"


# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

def _stage(n: int, name: str) -> None:
    print(f"\n{'='*60}")
    print(f"  {n} / 4  —  {name}")
    print(f"{'='*60}\n")


def _elapsed(t0: float) -> str:
    return f"{time.time() - t0:.1f}s"


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

def run() -> None:
    t_total = time.time()

    print("🧭 Refreshing DOE config from selected vehicle architecture")
    refresh_doe_config(
        architecture_config_path=ARCHITECTURE_CONFIG,
        compiler_config_path=COMPILER_CONFIG,
        doe_config_path=DOE_CONFIG,
    )

    # 1. Sample
    _stage(1, "Sampling")
    t = time.time()
    variants = sample(DOE_CONFIG)
    print(f"Sampled {len(variants)} variants  ({_elapsed(t)})")

    # Guard: population count must match requested variants
    # LHS is not incrementally extensible — changing sample count requires a clean run
    existing = len(list(POPULATION_DIR.glob("variant_????")))
    if existing > 0 and existing != len(variants):
        raise RuntimeError(
            f"\nPopulation mismatch: {existing} variants on disk, "
            f"{len(variants)} in config.\n"
            f"LHS sampling is not incrementally extensible.\n"
            f"Run 'make clean-population' then rerun.\n"
        )

    # 2. Generate
    _stage(2, "Generating variant .mo files")
    t = time.time()
    generate_variants(DOE_CONFIG, variants, POPULATION_DIR)
    print(f"Done  ({_elapsed(t)})")

    # 3+4. Compile → Simulate (pipelined per variant)
    _stage(3, "Building & simulating (compile → sim per variant)")
    t = time.time()
    build_all(
        POPULATION_DIR,
        COMPILER_CONFIG,
        doe_config_path=DOE_CONFIG,
        architecture_config_path=ARCHITECTURE_CONFIG,
    )
    print(f"Done  ({_elapsed(t)})")

    # 4. Aggregate
    _stage(4, "Aggregating results")
    t = time.time()
    df = aggregate(POPULATION_DIR, DOE_CONFIG, AGGREGATOR_CONFIG)
    print(f"Done  ({_elapsed(t)})")

    print(f"\n{'='*60}")
    print(f"  Pipeline complete  —  total {_elapsed(t_total)}")
    print(f"{'='*60}\n")
    print(df.to_string())


if __name__ == "__main__":
    run()
