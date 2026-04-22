"""run_doe.py — Orchestrate the full DOE pipeline end to end.

Stages:
  1. sample    — LHS sample variants from doe_config.yaml
  2. generate  — patch OrionRecord.mo per variant → population/
  3. compile   — compile each variant via OMC → executables
  4. batch     — run each executable → results.csv per variant
  5. aggregate — collect results → results/doe_results.parquet
"""

from __future__ import annotations

import time
from pathlib import Path

from sampler import sample
from generator import generate_variants
from compiler import compile_all
from batch import run_all
from aggregator import aggregate

# ---------------------------------------------------------------------------
# Paths
# ---------------------------------------------------------------------------

ROOT = Path(__file__).parent
DOE_CONFIG = ROOT / "configs/doe_config.yaml"
COMPILER_CONFIG = ROOT / "configs/compiler_config.yaml"
POPULATION_DIR = ROOT / "population"

# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

def _stage(name: str) -> None:
    print(f"\n{'='*60}")
    print(f"  {name}")
    print(f"{'='*60}\n")


def _elapsed(t0: float) -> str:
    s = time.time() - t0
    return f"{s:.1f}s"


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

def run() -> None:
    t_total = time.time()

    # 1. Sample
    _stage("1 / 5  —  Sampling")
    t = time.time()
    variants = sample(DOE_CONFIG)
    print(f"Sampled {len(variants)} variants  ({_elapsed(t)})")

    # 2. Generate
    _stage("2 / 5  —  Generating variant .mo files")
    t = time.time()
    generate_variants(DOE_CONFIG, variants, POPULATION_DIR)
    print(f"Done  ({_elapsed(t)})")

    # 3. Compile
    _stage("3 / 5  —  Compiling via OMC")
    t = time.time()
    compile_all(POPULATION_DIR, COMPILER_CONFIG)
    print(f"Done  ({_elapsed(t)})")

    # 4. Batch
    _stage("4 / 5  —  Running simulations")
    t = time.time()
    run_all(POPULATION_DIR, COMPILER_CONFIG)
    print(f"Done  ({_elapsed(t)})")

    # 5. Aggregate
    _stage("5 / 5  —  Aggregating results")
    t = time.time()
    df = aggregate(POPULATION_DIR, DOE_CONFIG)
    print(f"Done  ({_elapsed(t)})")

    print(f"\n{'='*60}")
    print(f"  Pipeline complete  —  total {_elapsed(t_total)}")
    print(f"{'='*60}\n")
    print(df.to_string())


if __name__ == "__main__":
    run()