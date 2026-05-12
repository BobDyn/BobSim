"""plot_results.py — Quick visualizations for DOE output tables.

Generates a compact PDF with:
  - a parallel-coordinates view of swept inputs
  - a metric dashboard for the main report outputs

Usage:
    python plot_results.py
    python plot_results.py --input results/doe_results.csv --output results/doe_results_viz.pdf
"""

from __future__ import annotations

import argparse
import os
from pathlib import Path

os.environ.setdefault("MPLCONFIGDIR", "/tmp/matplotlib")

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib import colormaps
from matplotlib.backends.backend_pdf import PdfPages
import numpy as np
import pandas as pd


ROOT = Path(__file__).resolve().parent.parent
DEFAULT_INPUT = ROOT / "results/doe_results.csv"
DEFAULT_OUTPUT = ROOT / "results/doe_results_viz.pdf"

INPUT_COLS = [
    "front.stabar.bar_rate",
    "rear.stabar.bar_rate",
    "front.wheel.static_alpha",
    "rear.wheel.static_alpha",
    "front.wheel.static_gamma",
    "rear.wheel.static_gamma",
]

KEY_METRICS = [
    "SteadyStateEval_understeer_gradient_deg_per_g",
    "SteadyStateEval_handwheel_understeer_gradient_deg_per_g",
    "SteadyStateEval_roll_gradient_deg_per_g",
    "SteadyStateEval_max_radius_error_pct",
    "SteadyStateEval_max_abs_ay_error_pct",
    "SteadyStateEval_handwheel_torque_max",
]

FILTER_METRIC = "SteadyStateEval_max_abs_ay_error_pct"
FILTER_LIMIT = 5.0


def _load_results(path: Path) -> pd.DataFrame:
    if path.suffix.lower() == ".parquet":
        return pd.read_parquet(path)
    if path.suffix.lower() == ".csv":
        return pd.read_csv(path)
    if path.with_suffix(".parquet").exists():
        return pd.read_parquet(path.with_suffix(".parquet"))
    if path.with_suffix(".csv").exists():
        return pd.read_csv(path.with_suffix(".csv"))
    raise FileNotFoundError(f"Could not find DOE results at {path}")


def _filter_results(df: pd.DataFrame) -> pd.DataFrame:
    if FILTER_METRIC not in df.columns:
        return df

    kept = df[df[FILTER_METRIC] <= FILTER_LIMIT].copy()
    dropped = len(df) - len(kept)
    if dropped:
        print(
            f"Filtering out {dropped} variant(s) with "
            f"{FILTER_METRIC} > {FILTER_LIMIT}%"
        )
    return kept


def _normalize_columns(df: pd.DataFrame, cols: list[str]) -> pd.DataFrame:
    norm = df[cols].copy()
    for col in cols:
        lo = float(norm[col].min())
        hi = float(norm[col].max())
        if np.isclose(lo, hi):
            norm[col] = 0.5
        else:
            norm[col] = (norm[col] - lo) / (hi - lo)
    return norm


def _plot_parallel_coordinates(ax: plt.Axes, df: pd.DataFrame) -> None:
    norm = _normalize_columns(df, INPUT_COLS)
    x = np.arange(len(INPUT_COLS))
    cmap = colormaps["viridis"]

    color_metric = "SteadyStateEval_understeer_gradient_deg_per_g"
    colors = df[color_metric].to_numpy(dtype=float)
    cmin = float(np.min(colors))
    cmax = float(np.max(colors))
    denom = cmax - cmin if not np.isclose(cmin, cmax) else 1.0

    for idx, (_, row) in enumerate(norm.iterrows()):
        c = cmap((colors[idx] - cmin) / denom)
        ax.plot(x, row.to_numpy(dtype=float), color=c, alpha=0.9, linewidth=2.0)
        ax.scatter(x, row.to_numpy(dtype=float), color=c, s=30, zorder=3)

    ax.set_xticks(x)
    ax.set_xticklabels(
        [
            "front\nstabar",
            "rear\nstabar",
            "front\nalpha",
            "rear\nalpha",
            "front\ngamma",
            "rear\ngamma",
        ]
    )
    ax.set_yticks([0.0, 0.5, 1.0])
    ax.set_yticklabels(["low", "mid", "high"])
    ax.set_ylabel("Normalized sweep value")
    ax.set_title("DOE input sweep")
    ax.grid(True, axis="y", alpha=0.3)

    sm = plt.cm.ScalarMappable(cmap=cmap, norm=plt.Normalize(vmin=cmin, vmax=cmax))
    cbar = plt.colorbar(sm, ax=ax, pad=0.02)
    cbar.set_label("Understeer gradient (deg/g)")


def _plot_metric_dashboard(axs: np.ndarray, df: pd.DataFrame) -> None:
    variants = df["variant"].tolist()
    x = np.arange(len(variants))

    for ax, metric in zip(axs.flat, KEY_METRICS, strict=False):
        values = df[metric].to_numpy(dtype=float)
        ax.bar(x, values, color="#2F6B9A")
        ax.set_title(metric.replace("SteadyStateEval_", ""), fontsize=10)
        ax.set_xticks(x)
        ax.set_xticklabels(variants, rotation=30, ha="right")
        ax.grid(True, axis="y", alpha=0.25)

    for ax in axs.flat[len(KEY_METRICS):]:
        ax.axis("off")


def make_figure(df: pd.DataFrame, output_path: Path) -> None:
    df = _filter_results(df)
    output_path.parent.mkdir(parents=True, exist_ok=True)

    with PdfPages(output_path) as pdf:
        fig1, ax1 = plt.subplots(figsize=(12, 6))
        _plot_parallel_coordinates(ax1, df)
        fig1.suptitle("OptSim DOE overview", fontsize=16, y=0.98)
        fig1.tight_layout()
        pdf.savefig(fig1, bbox_inches="tight")
        plt.close(fig1)

        fig2, axs = plt.subplots(2, 3, figsize=(14, 8))
        _plot_metric_dashboard(axs, df)
        fig2.suptitle("Key report metrics by variant", fontsize=16, y=0.98)
        fig2.tight_layout()
        pdf.savefig(fig2, bbox_inches="tight")
        plt.close(fig2)

    print(f"Visualization written: {output_path}")


def _parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Plot DOE results")
    parser.add_argument(
        "--input",
        type=Path,
        default=DEFAULT_INPUT,
        help=f"Input DOE table (default: {DEFAULT_INPUT})",
    )
    parser.add_argument(
        "--output",
        type=Path,
        default=DEFAULT_OUTPUT,
        help=f"Output PDF (default: {DEFAULT_OUTPUT})",
    )
    return parser.parse_args()


def main() -> None:
    args = _parse_args()
    df = _load_results(args.input)
    make_figure(df, args.output)


if __name__ == "__main__":
    main()
