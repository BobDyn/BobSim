"""response_surfaces.py — Fit and plot 2D DOE response-surface slices.

For each selected metric, the script:
  - finds the two most correlated swept inputs
  - fits a quadratic surface in those two variables
  - plots a contour surface with the DOE points overlaid

This is deliberately a sliced/approximate response surface, not a full 6D
surrogate. It is a good fit for the current 24-run DOE table.

Usage:
    python response_surfaces.py
    python response_surfaces.py --input results/doe_results.csv --output results/doe_response_surfaces.pdf
"""

from __future__ import annotations

import argparse
import os
from pathlib import Path

os.environ.setdefault("MPLCONFIGDIR", "/tmp/matplotlib")

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages
import numpy as np
import pandas as pd


ROOT = Path(__file__).resolve().parent.parent
DEFAULT_INPUT = ROOT / "results/doe_results.csv"
DEFAULT_OUTPUT = ROOT / "results/doe_response_surfaces.pdf"

INPUT_COLS = [
    "front.stabar.bar_rate",
    "rear.stabar.bar_rate",
    "front.wheel.static_alpha",
    "rear.wheel.static_alpha",
    "front.wheel.static_gamma",
    "rear.wheel.static_gamma",
]

METRICS = [
    "SteadyStateEval_understeer_gradient_deg_per_g",
    "SteadyStateEval_roll_gradient_deg_per_g",
    "SteadyStateEval_handwheel_torque_max",
    "SteadyStateEval_max_abs_ay_error_pct",
]

FILTER_METRIC = "SteadyStateEval_max_abs_ay_error_pct"
FILTER_LIMIT = 5.0


def _load_results(path: Path) -> pd.DataFrame:
    if path.suffix.lower() == ".csv":
        return pd.read_csv(path)
    if path.suffix.lower() == ".parquet":
        return pd.read_parquet(path)
    if path.with_suffix(".csv").exists():
        return pd.read_csv(path.with_suffix(".csv"))
    if path.with_suffix(".parquet").exists():
        return pd.read_parquet(path.with_suffix(".parquet"))
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


def _best_pair(df: pd.DataFrame, metric: str) -> tuple[str, str, pd.Series]:
    corr = df[INPUT_COLS + [metric]].corr(numeric_only=True)[metric].drop(metric)
    top = corr.abs().sort_values(ascending=False).head(2)
    return top.index[0], top.index[1], corr


def _fit_quadratic_surface(x: np.ndarray, y: np.ndarray, z: np.ndarray) -> np.ndarray:
    X = np.column_stack(
        [
            np.ones_like(x),
            x,
            y,
            x**2,
            y**2,
            x * y,
        ]
    )
    coeffs, *_ = np.linalg.lstsq(X, z, rcond=None)
    return coeffs


def _eval_quadratic(coeffs: np.ndarray, x: np.ndarray, y: np.ndarray) -> np.ndarray:
    return (
        coeffs[0]
        + coeffs[1] * x
        + coeffs[2] * y
        + coeffs[3] * x**2
        + coeffs[4] * y**2
        + coeffs[5] * x * y
    )


def _plot_surface(ax: plt.Axes, df: pd.DataFrame, metric: str) -> None:
    x_col, y_col, corr = _best_pair(df, metric)
    x = df[x_col].to_numpy(dtype=float)
    y = df[y_col].to_numpy(dtype=float)
    z = df[metric].to_numpy(dtype=float)

    coeffs = _fit_quadratic_surface(x, y, z)

    x_grid = np.linspace(float(x.min()), float(x.max()), 80)
    y_grid = np.linspace(float(y.min()), float(y.max()), 80)
    xx, yy = np.meshgrid(x_grid, y_grid)
    zz = _eval_quadratic(coeffs, xx, yy)

    contour = ax.contourf(xx, yy, zz, levels=20, cmap="viridis")
    ax.scatter(x, y, c=z, cmap="viridis", edgecolor="white", s=60, linewidth=0.8)

    ax.set_xlabel(x_col)
    ax.set_ylabel(y_col)
    ax.set_title(metric.replace("SteadyStateEval_", ""))

    cbar = plt.colorbar(contour, ax=ax, pad=0.02)
    cbar.set_label(metric.replace("SteadyStateEval_", ""))

    corr_line = "\n".join(
        f"{name}: {corr.loc[name]:+.3f}" for name in corr.abs().sort_values(ascending=False).head(4).index
    )
    ax.text(
        0.02,
        0.98,
        corr_line,
        transform=ax.transAxes,
        va="top",
        ha="left",
        fontsize=8,
        bbox=dict(boxstyle="round,pad=0.3", facecolor="white", alpha=0.8),
    )


def make_pdf(df: pd.DataFrame, output_path: Path) -> None:
    df = _filter_results(df)
    output_path.parent.mkdir(parents=True, exist_ok=True)

    with PdfPages(output_path) as pdf:
        for metric in METRICS:
            fig, ax = plt.subplots(figsize=(9, 6))
            _plot_surface(ax, df, metric)
            fig.suptitle("DOE response-surface slice", fontsize=15, y=0.98)
            fig.tight_layout()
            pdf.savefig(fig, bbox_inches="tight")
            plt.close(fig)

    print(f"Response surfaces written: {output_path}")


def _parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Generate DOE response-surface slices")
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
    make_pdf(df, args.output)


if __name__ == "__main__":
    main()
