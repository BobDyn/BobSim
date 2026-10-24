"""Fit and plot DOE response-surface slices."""

from __future__ import annotations

import argparse
import os
from pathlib import Path
import textwrap
from typing import Any

os.environ.setdefault("MPLCONFIGDIR", "/tmp/matplotlib")

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages
import numpy as np
import pandas as pd


STANDARD_DIR = Path(__file__).resolve().parents[1]
OPTSIM_DIR = STANDARD_DIR.parent
OPTSIM_RESULTS_DIR = OPTSIM_DIR / "results"
DEFAULT_REFINED_BUILD_DIR = OPTSIM_DIR / "Build/StandardSens/refined_response_surfaces"
DEFAULT_INPUT = OPTSIM_RESULTS_DIR / "refined_response_surface_results.csv"
DEFAULT_OUTPUT = OPTSIM_RESULTS_DIR / "refined_response_surface_report.pdf"
DEFAULT_PAIRS = DEFAULT_REFINED_BUILD_DIR / "selected_parameters.csv"
DEFAULT_COEFFICIENTS = (
    DEFAULT_REFINED_BUILD_DIR / "refined_response_surface_coefficients.csv"
)

FALLBACK_INPUT_COLS = [
    "front.stabar.rate_n_m_per_rad",
    "rear.stabar.rate_n_m_per_rad",
    "front.wheel.toe_deg",
    "rear.wheel.toe_deg",
    "front.wheel.camber_deg",
    "rear.wheel.camber_deg",
]

FALLBACK_METRICS = [
    "SteadyStateEval_limit_ay_mps2",
    "SteadyStateEval_understeer_gradient_deg_per_g",
    "SteadyStateEval_limit_understeer_gradient_deg_per_g",
    "SteadyStateEval_roll_gradient_deg_per_g",
    "SteadyStateEval_limit_roll_gradient_deg_per_g",
    "SteadyStateEval_peak_handwheel_torque_Nm",
]


def _load_results(path: Path) -> pd.DataFrame:
    if path.exists():
        source = path
    elif path.with_suffix(".csv").exists():
        source = path.with_suffix(".csv")
    elif path.with_suffix(".parquet").exists():
        source = path.with_suffix(".parquet")
    else:
        raise FileNotFoundError(f"Could not find DOE results at {path}")

    if source.suffix.lower() == ".csv":
        return pd.read_csv(source)
    if source.suffix.lower() == ".parquet":
        return pd.read_parquet(source)
    raise ValueError(f"Unsupported DOE results format: {source}")


def _short_label(name: str) -> str:
    label = (
        name.replace("front.", "fr.")
        .replace("rear.", "rr.")
        .replace("sprung_mass.", "sprung.")
        .replace("driver_mass.", "driver.")
        .replace("inertia_kg_m2.", "I.")
        .replace("actuation.", "act.")
        .replace("masses.", "")
        .replace("mass_kg", "mass")
        .replace("_n_m_per_rad", "")
        .replace("_n_per_m", "")
        .replace("_n_s_per_m", "")
        .replace("_deg", "")
        .replace("_mps2", "")
        .replace("_per_mps", "/mps")
    )
    return "\n".join(textwrap.wrap(label, width=34, break_long_words=False))


def _metric_label(name: str) -> str:
    label = name.removeprefix("SteadyStateEval_").replace("_", " ")
    label = label.replace(" deg per g", " (deg/g)")
    label = label.replace(" rad per mps2", " (rad/(m/s^2))")
    label = label.replace(" n m", " (N m)")
    return "\n".join(textwrap.wrap(label, width=62, break_long_words=False))


def _load_pairs(path: Path) -> list[dict[str, Any]]:
    if not path.exists():
        return []

    selection = pd.read_csv(path)
    required = {"metric", "rank", "input"}
    missing = required - set(selection.columns)
    if missing:
        raise ValueError(f"Pair selection file is missing columns: {sorted(missing)}")

    pairs: list[dict[str, Any]] = []
    for metric, group in selection.groupby("metric", sort=False):
        ordered = group.sort_values("rank").head(2)
        inputs = ordered["input"].astype(str).tolist()
        if len(inputs) < 2:
            continue
        pairs.append({"metric": metric, "variables": inputs})
    return pairs


def _design_matrix(x: np.ndarray, y: np.ndarray) -> np.ndarray:
    return np.column_stack(
        [
            np.ones_like(x),
            x,
            y,
            x**2,
            y**2,
            x * y,
        ]
    )


def _scale_axis(values: np.ndarray) -> tuple[float, float]:
    lo = float(np.nanmin(values))
    hi = float(np.nanmax(values))
    center = 0.5 * (lo + hi)
    scale = 0.5 * (hi - lo)
    if abs(scale) <= 1e-12:
        scale = 1.0
    return center, scale


def _fit_quadratic_surface(
    x: np.ndarray,
    y: np.ndarray,
    z: np.ndarray,
) -> dict[str, Any]:
    x_center, x_scale = _scale_axis(x)
    y_center, y_scale = _scale_axis(y)
    xs = (x - x_center) / x_scale
    ys = (y - y_center) / y_scale

    coeffs, *_ = np.linalg.lstsq(_design_matrix(xs, ys), z, rcond=None)
    z_hat = _eval_quadratic(coeffs, xs, ys)
    residuals = z - z_hat
    ss_res = float(np.sum(residuals**2))
    ss_tot = float(np.sum((z - float(np.mean(z))) ** 2))
    r2 = 1.0 - ss_res / ss_tot if ss_tot > 1e-12 else float("nan")
    rmse = float(np.sqrt(np.mean(residuals**2)))

    return {
        "coeffs": coeffs,
        "x_center": x_center,
        "x_scale": x_scale,
        "y_center": y_center,
        "y_scale": y_scale,
        "r2": r2,
        "rmse": rmse,
    }


def _eval_quadratic(coeffs: np.ndarray, x: np.ndarray, y: np.ndarray) -> np.ndarray:
    return (
        coeffs[0]
        + coeffs[1] * x
        + coeffs[2] * y
        + coeffs[3] * x**2
        + coeffs[4] * y**2
        + coeffs[5] * x * y
    )


def _eval_model(model: dict[str, Any], x: np.ndarray, y: np.ndarray) -> np.ndarray:
    xs = (x - model["x_center"]) / model["x_scale"]
    ys = (y - model["y_center"]) / model["y_scale"]
    return _eval_quadratic(model["coeffs"], xs, ys)


def _baseline_row(df: pd.DataFrame, baseline_variant: str) -> pd.Series:
    baseline = df[df["variant"] == baseline_variant]
    if baseline.empty:
        raise ValueError(f"Baseline variant not found: {baseline_variant}")
    return baseline.iloc[0]


def _pair_subset(
    df: pd.DataFrame,
    input_cols: list[str],
    pair_inputs: list[str],
    baseline: pd.Series,
) -> pd.DataFrame:
    mask = pd.Series(True, index=df.index)
    for col in input_cols:
        if col in pair_inputs:
            continue
        mask &= np.isclose(
            pd.to_numeric(df[col], errors="coerce"),
            float(baseline[col]),
            rtol=0,
            atol=1e-10,
        )
    return df[mask].copy()


def _best_pair(df: pd.DataFrame, input_cols: list[str], metric: str) -> tuple[str, str]:
    usable = [col for col in input_cols if col in df.columns and df[col].nunique(dropna=True) > 1]
    if len(usable) < 2:
        raise ValueError("At least two varying input columns are required")
    corr = df[usable + [metric]].corr(numeric_only=True)[metric].drop(metric)
    top = corr.abs().sort_values(ascending=False).head(2)
    return str(top.index[0]), str(top.index[1])


def _plot_surface_page(
    pdf: PdfPages,
    df: pd.DataFrame,
    metric: str,
    x_col: str,
    y_col: str,
) -> dict[str, Any] | None:
    plot_df = df[[x_col, y_col, metric, "variant"]].copy()
    plot_df[x_col] = pd.to_numeric(plot_df[x_col], errors="coerce")
    plot_df[y_col] = pd.to_numeric(plot_df[y_col], errors="coerce")
    plot_df[metric] = pd.to_numeric(plot_df[metric], errors="coerce")
    plot_df = plot_df.dropna(subset=[x_col, y_col, metric])

    fig, ax = plt.subplots(figsize=(9.5, 6.4))
    if len(plot_df) < 6:
        ax.axis("off")
        ax.text(
            0.5,
            0.5,
            f"Not enough points to fit {_metric_label(metric)}\n"
            f"{x_col} x {y_col}: {len(plot_df)} point(s)",
            ha="center",
            va="center",
            fontsize=12,
        )
        pdf.savefig(fig, bbox_inches="tight")
        plt.close(fig)
        return None

    x = plot_df[x_col].to_numpy(dtype=float)
    y = plot_df[y_col].to_numpy(dtype=float)
    z = plot_df[metric].to_numpy(dtype=float)

    model = _fit_quadratic_surface(x, y, z)
    x_grid = np.linspace(float(x.min()), float(x.max()), 90)
    y_grid = np.linspace(float(y.min()), float(y.max()), 90)
    xx, yy = np.meshgrid(x_grid, y_grid)
    zz = _eval_model(model, xx, yy)

    contour = ax.contourf(xx, yy, zz, levels=24, cmap="viridis")
    lines = ax.contour(xx, yy, zz, levels=8, colors="white", alpha=0.35, linewidths=0.7)
    ax.clabel(lines, inline=True, fontsize=7, fmt="%.3g")
    ax.scatter(x, y, c=z, cmap="viridis", edgecolor="white", s=52, linewidth=0.8)

    ax.set_xlabel(_short_label(x_col))
    ax.set_ylabel(_short_label(y_col))
    ax.set_title(_metric_label(metric), fontsize=12)
    ax.grid(True, alpha=0.18)

    cbar = plt.colorbar(contour, ax=ax, pad=0.02)
    cbar.set_label(_metric_label(metric))

    ax.text(
        0.02,
        0.98,
        f"quadratic fit\nn = {len(plot_df)}\n"
        f"R^2 = {model['r2']:.3f}\nRMSE = {model['rmse']:.4g}",
        transform=ax.transAxes,
        va="top",
        ha="left",
        fontsize=9,
        bbox=dict(boxstyle="round,pad=0.3", facecolor="white", alpha=0.82),
    )

    fig.suptitle("Refined DOE response surface", fontsize=14, y=0.985)
    fig.tight_layout()
    pdf.savefig(fig, bbox_inches="tight")
    plt.close(fig)

    coeffs = model["coeffs"]
    return {
        "metric": metric,
        "x": x_col,
        "y": y_col,
        "n_points": int(len(plot_df)),
        "r2": float(model["r2"]),
        "rmse": float(model["rmse"]),
        "x_center": float(model["x_center"]),
        "x_scale": float(model["x_scale"]),
        "y_center": float(model["y_center"]),
        "y_scale": float(model["y_scale"]),
        "b0": float(coeffs[0]),
        "b_x": float(coeffs[1]),
        "b_y": float(coeffs[2]),
        "b_x2": float(coeffs[3]),
        "b_y2": float(coeffs[4]),
        "b_xy": float(coeffs[5]),
    }


def _input_cols_from_pairs(pairs: list[dict[str, Any]]) -> list[str]:
    cols: list[str] = []
    for pair in pairs:
        for col in pair["variables"]:
            if col not in cols:
                cols.append(col)
    return cols


def make_pdf(
    df: pd.DataFrame,
    output_path: Path,
    *,
    pairs: list[dict[str, Any]] | None = None,
    input_cols: list[str] | None = None,
    metrics: list[str] | None = None,
    baseline_variant: str = "variant_0000",
    coefficients_output: Path | None = None,
) -> pd.DataFrame:
    """Write a response-surface PDF and return fitted model coefficients."""
    output_path.parent.mkdir(parents=True, exist_ok=True)
    pairs = pairs or []

    if pairs:
        input_cols = input_cols or _input_cols_from_pairs(pairs)
        plot_specs = pairs
    else:
        input_cols = input_cols or [col for col in FALLBACK_INPUT_COLS if col in df.columns]
        selected_metrics = metrics or [metric for metric in FALLBACK_METRICS if metric in df.columns]
        plot_specs = []
        for metric in selected_metrics:
            x_col, y_col = _best_pair(df, input_cols, metric)
            plot_specs.append({"metric": metric, "variables": [x_col, y_col]})

    if not plot_specs:
        raise ValueError("No response-surface plot specifications were available")

    baseline = _baseline_row(df, baseline_variant)
    coefficient_rows: list[dict[str, Any]] = []
    with PdfPages(output_path) as pdf:
        for spec in plot_specs:
            metric = spec["metric"]
            x_col, y_col = spec["variables"]
            if metric not in df.columns:
                print(f"Skipping missing metric: {metric}")
                continue
            if x_col not in df.columns or y_col not in df.columns:
                print(f"Skipping {metric}: missing input columns {x_col}, {y_col}")
                continue

            plot_df = (
                _pair_subset(df, input_cols, [x_col, y_col], baseline)
                if input_cols
                else df
            )
            row = _plot_surface_page(pdf, plot_df, metric, x_col, y_col)
            if row is not None:
                coefficient_rows.append(row)

    coefficients = pd.DataFrame(coefficient_rows)
    if coefficients_output is not None:
        coefficients_output.parent.mkdir(parents=True, exist_ok=True)
        coefficients.to_csv(coefficients_output, index=False)

    print(f"Response surfaces written: {output_path}")
    if coefficients_output is not None:
        print(f"Surface coefficients written: {coefficients_output}")
    return coefficients


def _parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Generate DOE response-surface plots")
    parser.add_argument("--input", type=Path, default=DEFAULT_INPUT)
    parser.add_argument("--output", type=Path, default=DEFAULT_OUTPUT)
    parser.add_argument("--pairs", type=Path, default=DEFAULT_PAIRS)
    parser.add_argument("--coefficients-output", type=Path, default=DEFAULT_COEFFICIENTS)
    parser.add_argument("--baseline-variant", default="variant_0000")
    parser.add_argument("--metrics", nargs="*")
    parser.add_argument("--input-cols", nargs="*")
    return parser.parse_args()


def main() -> None:
    args = _parse_args()
    df = _load_results(args.input)
    pairs = _load_pairs(args.pairs)
    make_pdf(
        df,
        args.output,
        pairs=pairs,
        input_cols=args.input_cols,
        metrics=args.metrics,
        baseline_variant=args.baseline_variant,
        coefficients_output=args.coefficients_output,
    )


if __name__ == "__main__":
    main()
