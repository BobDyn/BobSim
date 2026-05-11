"""aggregator.py — Collect batch results into a single Parquet dataset.

For each variant and each standard:
  - Input parameters are reconstructed from sampler (seed is fixed in doe_config.yaml)
  - Output metrics are extracted from results/<standard>/results.csv

Extraction strategy:
  - Row 0 is the initial condition (all zeros) — skipped
  - Remaining rows are steady state — take the mean across them

Metric columns are prefixed with the standard name e.g. SteadyStateEval_yaw_rate_ss
so multiple standards can coexist in the same parquet table.

Output: results/doe_results.parquet
  Columns: [variant, <input params>, <standard_metric>, ...]

To add a metric:   add one line under the standard in aggregator_config.yaml
To add a standard: add a new block in aggregator_config.yaml
Nothing else changes.
"""

from __future__ import annotations

from pathlib import Path

import pandas as pd
import yaml

from sampler import sample

# ---------------------------------------------------------------------------
# Config
# ---------------------------------------------------------------------------

DOE_CONFIG = Path(__file__).parent / "configs/doe_config.yaml"
AGGREGATOR_CONFIG = Path(__file__).parent / "configs/aggregator_config.yaml"
POPULATION_DIR = Path(__file__).parent / "population"
OUTPUT_PATH = Path(__file__).parent / "results/doe_results.parquet"


def load_aggregator_config(config_path: Path = AGGREGATOR_CONFIG) -> dict:
    with open(config_path) as f:
        return yaml.safe_load(f)


# ---------------------------------------------------------------------------
# Core
# ---------------------------------------------------------------------------

def _extract_metrics(
        csv_path: Path,
        metrics: dict[str, str],
        standard: str,
) -> dict[str, float]:
    """Read one results CSV and extract all steady-state scalar metrics.

    Skips row 0 (initial condition), means the rest.
    Prefixes each column with the standard name.
    """
    df = pd.read_csv(csv_path)
    steady = df.iloc[1:]
    return {
        f"{standard}_{col}": float(steady[signal].mean())
        for col, signal in metrics.items()
    }


def aggregate(
        population_dir: Path = POPULATION_DIR,
        doe_config: Path = DOE_CONFIG,
        aggregator_config: Path = AGGREGATOR_CONFIG,
        output_path: Path = OUTPUT_PATH,
) -> pd.DataFrame:
    """Aggregate all variant results into a single Parquet table.

    Returns the full DataFrame.
    """
    cfg = load_aggregator_config(aggregator_config)
    standards: dict[str, dict] = cfg["standards"]

    # Reconstruct inputs — seed is fixed so this is deterministic
    variants = sample(doe_config)

    rows = []
    skipped = 0

    for i, params in enumerate(variants):
        variant_name = f"variant_{i:04d}"
        row: dict = {"variant": variant_name, **params}
        variant_skipped = False

        for standard, standard_cfg in standards.items():
            metrics = standard_cfg["steady_state_metrics"]
            csv_path = (
                    population_dir / variant_name / "results" / standard / "results.csv"
            )

            if not csv_path.exists():
                print(f"  SKIP {variant_name}/{standard} — no results CSV")
                variant_skipped = True
                continue

            try:
                extracted = _extract_metrics(csv_path, metrics, standard)
                row.update(extracted)
            except Exception as e:
                print(f"  SKIP {variant_name}/{standard} — {e}")
                variant_skipped = True
                continue

        if variant_skipped:
            skipped += 1

        rows.append(row)

    if not rows:
        raise RuntimeError("No results found — has batch.py run?")

    result = pd.DataFrame(rows)

    output_path.parent.mkdir(parents=True, exist_ok=True)
    result.to_parquet(output_path, index=False)

    print(f"\nAggregated {len(rows)} variants ({skipped} with missing standards)")
    print(f"Columns:  {list(result.columns)}")
    print(f"Output:   {output_path}")

    return result


# ---------------------------------------------------------------------------
# Entrypoint
# ---------------------------------------------------------------------------

if __name__ == "__main__":
    df = aggregate()
    print(df.to_string())