"""search.py — Reverse lookup: target metrics → suspension parameters.
 
Loads the aggregated Parquet table, builds a KDTree over the requested
metric columns, and returns the nearest variant's suspension parameters.
 
Usage:
    python search.py --metrics \\
        SteadyStateEval_understeer_gradient_deg_per_g=0.05 \\
        SteadyStateEval_peak_handwheel_torque_Nm=12

    python search.py \\
        --metrics SteadyStateEval_understeer_gradient_deg_per_g=0.05 \\
        SteadyStateEval_peak_handwheel_torque_Nm=12 \\
        --parquet _4_OptSim/Build/StandardSens/standard_sensitivity_results.parquet \\
        --top 3
 
"""

from __future__ import annotations
import argparse
import sys
from pathlib import Path
import numpy as np
import pandas as pd
from scipy.spatial import KDTree

STANDARD_DIR = Path(__file__).resolve().parents[1]
OPTSIM_DIR = STANDARD_DIR.parent
DEFAULT_PARQUET = OPTSIM_DIR / "Build/StandardSens/standard_sensitivity_results.parquet"

# these are params that we sweep
INPUT_PARAMS = [
    "front.stabar.rate_n_m_per_rad",
    "rear.stabar.rate_n_m_per_rad",
    "front.wheel.toe_deg",
    "rear.wheel.toe_deg",
    "front.wheel.camber_deg",
    "rear.wheel.camber_deg",
    "aero.load_scale",
]


# ---------------------------------------------------------------------------
# Search
# ---------------------------------------------------------------------------

def search(targets: dict[str, float], parquet_path: Path = DEFAULT_PARQUET,
           top: int = 1, ) -> pd.DataFrame:
    """Find the nearest variants to the target metric values.

    Args:
        targets:      dict of metric_name -> target_value
        parquet_path: path to the aggregated StandardSens parquet
        top:          number of nearest variants to return

    Returns:
        DataFrame with top nearest variants — input params + metrics + distance
    """
    csv_path = parquet_path.with_suffix(".csv")
    if parquet_path.exists():
        df = pd.read_parquet(parquet_path)
    elif csv_path.exists():
        df = pd.read_csv(csv_path)
    else:
        raise FileNotFoundError(
            f"Results not found at {parquet_path} or {csv_path}. Has the pipeline run?"
        )

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

    input_cols = [col for col in INPUT_PARAMS if col in df.columns]
    results = df.iloc[indices_arr][["variant"] + input_cols + metric_cols].copy()
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
        help="One or more metric=value pairs e.g. SteadyStateEval_understeer_gradient_deg_per_g=0.05",
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
        print("  Swept inputs:")
        for param in INPUT_PARAMS:
            if param in row:
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
