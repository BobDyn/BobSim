"""Visualize EnvelopeSim sensitivity outputs.

Usage:
    python _4_OptSim/pipeline/plot_envelope_sensitivities.py
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
DEFAULT_INPUTS = ROOT / "results/envelope_sensitivity_inputs.csv"
DEFAULT_METRICS = ROOT / "results/envelope_sensitivities/envelope_sensitivity_metrics.csv"
DEFAULT_OUTPUT = ROOT / "results/envelope_sensitivity_viz.pdf"
DEFAULT_RAW_DIR = ROOT / "results/envelope_sensitivities"
G = 9.80665

METRICS = [
    "ggv_max_cornering_g",
    "ggv_max_accel_g",
    "ggv_max_braking_g",
    "ymd_max_abs_yaw_moment_nm",
    "ymd_max_abs_ay_g",
]


def _variant_num(name: str) -> int:
    return int(name.rsplit("_", maxsplit=1)[-1])


def _load_joined(inputs_path: Path, metrics_path: Path) -> pd.DataFrame:
    inputs = pd.read_csv(inputs_path)
    metrics = pd.read_csv(metrics_path)
    return inputs.merge(metrics, on="variant", how="inner").sort_values(
        "variant",
        key=lambda s: s.map(_variant_num),
    )


def _input_columns(df: pd.DataFrame) -> list[str]:
    numeric = df.select_dtypes(include=[np.number])
    return [
        col
        for col in numeric.columns
        if col not in METRICS and numeric[col].nunique(dropna=True) > 1
    ]


def _short_label(name: str) -> str:
    return (
        name.replace("front.", "fr.")
        .replace("rear.", "rr.")
        .replace("sprung_mass.", "sprung.")
        .replace("driver_mass.", "driver.")
        .replace("inertia_kg_m2.", "I.")
        .replace("mass_kg", "mass")
        .replace("_n_m_per_rad", "")
        .replace("_n_per_m", "")
        .replace("_n_s_per_m", "")
        .replace("_deg", "")
    )


def _plot_metric_overview(pdf: PdfPages, df: pd.DataFrame) -> None:
    fig, axs = plt.subplots(2, 3, figsize=(14, 8))
    axs = axs.flat

    for ax, metric in zip(axs, METRICS, strict=False):
        ordered = df.sort_values(metric)
        colors = np.where(ordered[metric] == ordered[metric].max(), "#C84C31", "#2F6B9A")
        ax.bar(np.arange(len(ordered)), ordered[metric], color=colors)
        ax.set_title(metric)
        ax.set_xlabel("variants sorted by metric")
        ax.grid(True, axis="y", alpha=0.25)

        best = ordered.iloc[-1]
        ax.text(
            0.02,
            0.95,
            f"best: {best['variant']}\n{best[metric]:.3g}",
            transform=ax.transAxes,
            va="top",
            fontsize=9,
            bbox={"boxstyle": "round,pad=0.3", "facecolor": "white", "alpha": 0.85},
        )

    axs[-1].axis("off")
    fig.suptitle("Envelope sensitivity metrics", fontsize=16)
    fig.tight_layout()
    pdf.savefig(fig, bbox_inches="tight")
    plt.close(fig)


def _plot_metric_correlations(pdf: PdfPages, df: pd.DataFrame) -> None:
    inputs = _input_columns(df)
    corr = df[inputs + METRICS].corr(numeric_only=True).loc[inputs, METRICS]
    score = corr.abs().max(axis=1).sort_values(ascending=False)
    top_inputs = score.head(18).index.tolist()
    corr = corr.loc[top_inputs]

    fig, ax = plt.subplots(figsize=(12, 8))
    im = ax.imshow(corr.to_numpy(), cmap="coolwarm", vmin=-1.0, vmax=1.0, aspect="auto")
    ax.set_xticks(np.arange(len(METRICS)))
    ax.set_xticklabels(METRICS, rotation=35, ha="right")
    ax.set_yticks(np.arange(len(top_inputs)))
    ax.set_yticklabels([_short_label(col) for col in top_inputs])
    ax.set_title("Most correlated inputs")

    for r in range(corr.shape[0]):
        for c in range(corr.shape[1]):
            val = corr.iat[r, c]
            ax.text(c, r, f"{val:+.2f}", ha="center", va="center", fontsize=8)

    cbar = fig.colorbar(im, ax=ax, pad=0.02)
    cbar.set_label("Pearson correlation")
    fig.tight_layout()
    pdf.savefig(fig, bbox_inches="tight")
    plt.close(fig)


def _ggv_boundary(df: pd.DataFrame, speed: float) -> pd.DataFrame:
    at_speed = df[np.isclose(df["speed_mps"], speed)].copy()
    accel = at_speed[at_speed["accel_feasible"] > 0][["ay_mps2", "ax_accel_mps2"]]
    accel = accel.rename(columns={"ax_accel_mps2": "ax_mps2"}).dropna()
    brake = at_speed[at_speed["brake_feasible"] > 0][["ay_mps2", "ax_brake_mps2"]]
    brake = brake.rename(columns={"ax_brake_mps2": "ax_mps2"}).dropna()
    return pd.concat([accel, brake], ignore_index=True)


def _plot_ggv_overlay(pdf: PdfPages, raw_dir: Path, metrics: pd.DataFrame) -> None:
    selected = [
        metrics.sort_values("ggv_max_cornering_g").iloc[0]["variant"],
        metrics.sort_values("ggv_max_cornering_g").iloc[len(metrics) // 2]["variant"],
        metrics.sort_values("ggv_max_cornering_g").iloc[-1]["variant"],
    ]
    labels = ["lowest cornering", "mid pack", "highest cornering"]
    colors = ["#8E5C5C", "#607D3B", "#2F6B9A"]

    fig, ax = plt.subplots(figsize=(9, 7))
    for variant, label, color in zip(selected, labels, colors, strict=True):
        ggv = pd.read_csv(raw_dir / variant / "ggv.csv")
        speed = float(np.median(sorted(ggv["speed_mps"].unique())))
        boundary = _ggv_boundary(ggv, speed)
        ax.scatter(
            boundary["ay_mps2"] / G,
            boundary["ax_mps2"] / G,
            s=18,
            alpha=0.75,
            color=color,
            label=f"{variant} ({label}, {speed:g} m/s)",
        )

    ax.axhline(0.0, color="black", linewidth=0.8, alpha=0.5)
    ax.axvline(0.0, color="black", linewidth=0.8, alpha=0.5)
    ax.set_xlabel("lateral acceleration ay (g)")
    ax.set_ylabel("longitudinal acceleration ax (g)")
    ax.set_title("GGV envelope comparison")
    ax.grid(True, alpha=0.25)
    ax.legend(loc="best")
    fig.tight_layout()
    pdf.savefig(fig, bbox_inches="tight")
    plt.close(fig)


def _plot_ymd_contours(pdf: PdfPages, raw_dir: Path, metrics: pd.DataFrame) -> None:
    selected = [
        metrics.sort_values("ymd_max_abs_yaw_moment_nm").iloc[0]["variant"],
        metrics.sort_values("ymd_max_abs_yaw_moment_nm").iloc[-1]["variant"],
    ]

    fig, axs = plt.subplots(1, 2, figsize=(14, 6), sharex=True, sharey=True)
    for ax, variant in zip(axs, selected, strict=True):
        ymd = pd.read_csv(raw_dir / variant / "ymd.csv")
        converged = ymd[ymd["converged"] > 0]
        contour = ax.tricontourf(
            converged["beta_deg"],
            converged["hwa_deg"],
            converged["mz_nm"],
            levels=24,
            cmap="coolwarm",
        )
        ax.set_title(variant)
        ax.set_xlabel("body slip beta (deg)")
        ax.set_ylabel("handwheel angle (deg)")
        ax.grid(True, alpha=0.2)
        fig.colorbar(contour, ax=ax, pad=0.02, label="yaw moment (Nm)")

    fig.suptitle("YMD yaw moment maps")
    fig.tight_layout()
    pdf.savefig(fig, bbox_inches="tight")
    plt.close(fig)


def make_pdf(
    inputs_path: Path,
    metrics_path: Path,
    raw_dir: Path,
    output_path: Path,
) -> None:
    df = _load_joined(inputs_path, metrics_path)
    metrics = pd.read_csv(metrics_path)

    output_path.parent.mkdir(parents=True, exist_ok=True)
    with PdfPages(output_path) as pdf:
        _plot_metric_overview(pdf, df)
        _plot_metric_correlations(pdf, df)
        _plot_ggv_overlay(pdf, raw_dir, metrics)
        _plot_ymd_contours(pdf, raw_dir, metrics)

    print(f"Envelope visualization written: {output_path}")


def _parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Plot EnvelopeSim sensitivity outputs")
    parser.add_argument("--inputs", type=Path, default=DEFAULT_INPUTS)
    parser.add_argument("--metrics", type=Path, default=DEFAULT_METRICS)
    parser.add_argument("--raw-dir", type=Path, default=DEFAULT_RAW_DIR)
    parser.add_argument("--output", type=Path, default=DEFAULT_OUTPUT)
    return parser.parse_args()


def main() -> None:
    args = _parse_args()
    make_pdf(args.inputs, args.metrics, args.raw_dir, args.output)


if __name__ == "__main__":
    main()
