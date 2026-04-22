"""aggregator.py — Collect batch results into a single Parquet dataset.

For each variant:
  - Input parameters are reconstructed from sampler (seed is fixed in doe_config.yaml)
  - Output metrics are read from the last row of results/ISO4138/results.csv

Output: results/doe_results.parquet
  Columns: [variant, <6 input params>, acc_y_ss]
"""

from __future__ import annotations

from pathlib import Path

import pandas as pd

from sampler import sample

# ---------------------------------------------------------------------------
# Config
# ---------------------------------------------------------------------------

DOE_CONFIG = Path(__file__).parent / "configs/doe_config.yaml"
POPULATION_DIR = Path(__file__).parent / "population"
OUTPUT_PATH = Path(__file__).parent / "results/doe_results.parquet"

STANDARD = "ISO4138"


# ---------------------------------------------------------------------------
# Core
# ---------------------------------------------------------------------------

def aggregate(
        population_dir: Path = POPULATION_DIR,
        doe_config: Path = DOE_CONFIG,
        output_path: Path = OUTPUT_PATH,
) -> pd.DataFrame:
    # Reconstruct inputs — seed is fixed so this is deterministic
    variants = sample(doe_config)

    rows = []
    skipped = 0

    for i, params in enumerate(variants):
        variant_name = f"variant_{i:04d}"
        csv_path = population_dir / variant_name / "results" / STANDARD / "results.csv"

        if not csv_path.exists():
            print(f"  SKIP {variant_name} — no results CSV")
            skipped += 1
            continue

        try:
            df = pd.read_csv(csv_path)
            acc_y_ss = df["iso.accY"].iloc[-1]
        except Exception as e:
            print(f"  SKIP {variant_name} — {e}")
            skipped += 1
            continue

        rows.append({"variant": variant_name, **params, "acc_y_ss": acc_y_ss})

    if not rows:
        raise RuntimeError("No results found — has batch.py run?")

    result = pd.DataFrame(rows)

    output_path.parent.mkdir(parents=True, exist_ok=True)
    result.to_parquet(output_path, index=False)

    print(f"\nAggregated {len(rows)} variants ({skipped} skipped)")
    print(f"Output: {output_path}")
    return result


# ---------------------------------------------------------------------------
# Entrypoint
# ---------------------------------------------------------------------------

if __name__ == "__main__":
    df = aggregate()
    print(df.to_string())