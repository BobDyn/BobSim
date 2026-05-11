"""search.py — Reverse lookup: target metrics → suspension parameters.
 
Loads the aggregated Parquet table, builds a KDTree over the requested
metric columns, and returns the nearest variant's suspension parameters.
 
Usage:
    python search.py --metrics ISO4138_sideslip_ss=0.02 ISO4138_handwheel_angle_ss=0.3
 
    python search.py \\
        --metrics ISO4138_sideslip_ss=0.02 ISO4138_handwheel_angle_ss=0.3 \\
        --parquet results/doe_results.parquet \\
        --top 3
 
Options:
    --metrics   One or more metric=value pairs to search on (required)
    --parquet   Path to parquet file (default: results/doe_results.parquet)
    --top       Number of nearest variants to return (default: 1)
"""

from __future__ import annotations
import argparse
import sys
from pathlib import Path
import numpy as np
import pandas as pd
from scipy.spatial import KDTree

DEFAULT_PARQUET = Path(__file__).parent / "results/doe_results.parquet"

# these are params that we sweep
INPUT_PARAMS = [
    "front.stabar.bar_rate",
    "rear.stabar.bar_rate",
    "front.wheel.static_alpha",
    "rear.wheel.static_alpha",
    "front.wheel.static_gamma",
    "rear.wheel.static_gamma",
]


# ---------------------------------------------------------------------------
# Search
# ---------------------------------------------------------------------------

def search(targets: dict[str, float], parquet_path: Path = DEFAULT_PARQUET,
           top: int = 1, ) -> pd.DataFrame:
    """Find the nearest variants to the target metric values.

    Args:
        targets:      dict of metric_name -> target_value
        parquet_path: path to doe_results.parquet
        top:          number of nearest variants to return

    Returns:
        DataFrame with top nearest variants — input params + metrics + distance
    """
    if not parquet_path.exists():
        raise FileNotFoundError(
            f"Parquet not found at {parquet_path}. Has the pipeline run?"
        )

    df = pd.read_parquet(parquet_path)

    # Validate requested metrics exist
    missing = [m for m in targets if m not in df.columns]
    if missing:
        raise ValueError(
            f"Unknown metrics: {missing}\n"
            f"Available: {[c for c in df.columns if c not in INPUT_PARAMS + ['variant']]}"
        )

    metric_cols = list(targets.keys())
    target_vals = np.array([targets[m] for m in metric_cols])

    # Normalize each dimension by its range so no single metric dominates
    metric_data = df[metric_cols].values
    ranges = metric_data.max(axis=0) - metric_data.min(axis=0)
    ranges[ranges == 0] = 1.0  # avoid divide by zero for constant columns

    metric_data_norm = metric_data / ranges
    target_norm = target_vals / ranges

    # Build KDTree and query
    tree = KDTree(metric_data_norm)
    distances, indices = tree.query(target_norm, k=min(top, len(df)))

    # Ensure distances and indices are always 1D arrays for consistent handling.
    distances_arr = np.atleast_1d(distances)
    indices_arr = np.atleast_1d(indices).astype(int)

    results = df.iloc[indices_arr][["variant"] + INPUT_PARAMS + metric_cols].copy()
    results.insert(1, "distance", [round(float(d), 6) for d in distances_arr])

    return results.reset_index(drop=True)



# ---------------------------------------------------------------------------
# CLI
# ---------------------------------------------------------------------------

def _parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Reverse lookup: target metrics → suspension parameters"
    )
    parser.add_argument(
        "--metrics",
        nargs="+",
        required=True,
        metavar="METRIC=VALUE",
        help="One or more metric=value pairs e.g. ISO4138_sideslip_ss=0.02",
    )
    parser.add_argument(
        "--parquet",
        type=Path,
        default=DEFAULT_PARQUET,
        help=f"Path to parquet file (default: {DEFAULT_PARQUET})",
    )
    parser.add_argument(
        "--top",
        type=int,
        default=1,
        help="Number of nearest variants to return (default: 1)",
    )
    return parser.parse_args()


def _parse_metrics(metric_args: list[str]) -> dict[str, float]:
    targets = {}
    for arg in metric_args:
        if "=" not in arg:
            print(f"ERROR: metric must be in METRIC=VALUE format, got: {arg}")
            sys.exit(1)
        key, val = arg.split("=", 1)
        try:
            targets[key.strip()] = float(val.strip())
        except ValueError:
            print(f"ERROR: value must be a number, got: {val}")
            sys.exit(1)
    return targets


def _print_results(results: pd.DataFrame, targets: dict[str, float]) -> None:
    metric_cols = list(targets.keys())

    print("\nTarget metrics:")
    for metric, val in targets.items():
        print(f"  {metric}: {val}")

    print()
    for _, row in results.iterrows():
        print(f"Variant:  {row['variant']}  (distance: {row['distance']})")
        print("  Suspension params:")
        for param in INPUT_PARAMS:
            print(f"    {param:<35} {row[param]:.4f}")
        print("  Metrics:")
        for metric in metric_cols:
            print(f"    {metric:<35} {row[metric]:.6f}  (target: {targets[metric]})")
        print()


# ---------------------------------------------------------------------------
# Entrypoint
# ---------------------------------------------------------------------------

if __name__ == "__main__":
    args = _parse_args()
    targets = _parse_metrics(args.metrics)

    results = search(targets, parquet_path=args.parquet, top=args.top)
    _print_results(results, targets)