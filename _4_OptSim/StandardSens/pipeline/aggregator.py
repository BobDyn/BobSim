"""Collect batch results into one Parquet table.

Metric columns are prefixed with the standard name, e.g. SteadyStateEval_ay_min.
"""

from __future__ import annotations

from pathlib import Path
from typing import Any, cast

import pandas as pd
import yaml

from StandardSens.pipeline.sampler import sample

STANDARD_DIR = Path(__file__).resolve().parents[1]
OPTSIM_DIR = STANDARD_DIR.parent
DOE_CONFIG = STANDARD_DIR / "configs/_doe_config.yaml"
AGGREGATOR_CONFIG = STANDARD_DIR / "configs/aggregator_config.yaml"
POPULATION_DIR = OPTSIM_DIR / "Build/StandardSens/population"
OUTPUT_PATH = OPTSIM_DIR / "Build/StandardSens/standard_sensitivity_results.parquet"


def load_aggregator_config(config_path: Path = AGGREGATOR_CONFIG) -> dict:
    with open(config_path) as f:
        return yaml.safe_load(f)


def _extract_metrics(
        csv_path: Path,
        metrics: dict[str, str],
        standard: str,
) -> dict[str, float]:
    """Read one metrics CSV and extract the requested metric rows."""
    df = pd.read_csv(csv_path)
    if "metric" not in df.columns or "value" not in df.columns:
        raise ValueError(f"Metrics CSV is missing required columns: {csv_path}")

    if "standard" in df.columns:
        df = df[df["standard"] == standard]

    by_metric = df.set_index("metric")

    return {
        f"{standard}_{col}": float(
            cast(Any, by_metric.loc[metric_name, "value"])
        )
        for col, metric_name in metrics.items()
    }


def aggregate(
        population_dir: Path = POPULATION_DIR,
        doe_config: Path = DOE_CONFIG,
        aggregator_config: Path = AGGREGATOR_CONFIG,
        output_path: Path = OUTPUT_PATH,
) -> pd.DataFrame:
    """Aggregate all variant results into one Parquet table and return it."""
    cfg = load_aggregator_config(aggregator_config)
    standards: dict[str, dict] = cfg["standards"]

    # The DOE seed is fixed, so this reproduces the inputs of each variant.
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
                    population_dir / variant_name / "results" / standard / "metrics.csv"
            )

            if not csv_path.exists():
                print(f"  SKIP {variant_name}/{standard} — no metrics CSV")
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
        raise RuntimeError("No metrics found — has batch.py run?")

    result = pd.DataFrame(rows)

    output_path.parent.mkdir(parents=True, exist_ok=True)
    try:
        result.to_parquet(output_path, index=False)
        output_written = output_path
    except ImportError:
        csv_path = output_path.with_suffix(".csv")
        result.to_csv(csv_path, index=False)
        output_written = csv_path

    print(f"\nAggregated {len(rows)} variants ({skipped} with missing standards)")
    print(f"Columns:  {list(result.columns)}")
    print(f"Output:   {output_written}")

    return result


if __name__ == "__main__":
    df = aggregate()
    print(df.to_string())
