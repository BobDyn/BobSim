"""Internal plotting helpers for EnvelopeSim sensitivity outputs."""

from __future__ import annotations

import argparse
import os
from pathlib import Path
import textwrap

os.environ.setdefault("MPLCONFIGDIR", "/tmp/matplotlib")

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages
import numpy as np
import pandas as pd

from _shared.plot_sensitivity_tornado import (
    DEFAULT_ENVELOPE_TORNADO_METRICS,
    _input_columns as _tornado_input_columns,
    _oat_effects,
    _plot_one_tornado,
)


PIPELINE_DIR = Path(__file__).resolve().parent
ENVELOPE_DIR = PIPELINE_DIR.parent
OPTSIM_DIR = ENVELOPE_DIR.parent
DEFAULT_INPUTS = (
    OPTSIM_DIR / "Build/EnvelopeSens/envelope_sensitivity_inputs.csv"
)
DEFAULT_METRICS = (
    OPTSIM_DIR
    / "Build/EnvelopeSens/envelope_sensitivities/envelope_sensitivity_metrics.csv"
)
DEFAULT_OUTPUT = OPTSIM_DIR / "results/envelope_sensitivity_report.pdf"
DEFAULT_RAW_DIR = OPTSIM_DIR / "Build/EnvelopeSens/envelope_sensitivities"
G = 9.80665

METRICS = [
    "ggv_volume_g2_mps",
    "ggv_area_ref_g2",
    "ggv_min_area_g2",
    "ggv_max_area_g2",
    "ggv_cornering_ref_g",
    "ggv_accel_ref_g",
    "ggv_braking_ref_g",
    "ggv_mean_cornering_g",
    "ggv_mean_accel_g",
    "ggv_mean_braking_g",
    "ggv_min_cornering_g",
    "ggv_min_accel_g",
    "ggv_min_braking_g",
    "ggv_area_fill_factor_ref",
    "ggv_longitudinal_balance_ref",
    "track_combined_performance_index",
    "track_lateral_performance_index",
    "track_longitudinal_performance_index",
    "track_accel_performance_index",
    "track_brake_performance_index",
    "track_velocity_mean_mps",
    "track_velocity_peak_mps",
    "track_corner_speed_mean_mps",
    "track_straight_speed_mean_mps",
    "track_accel_capacity_mean_mps2",
    "track_brake_capacity_mean_mps2",
    "ggv_max_cornering_g",
    "ggv_max_accel_g",
    "ggv_max_braking_g",
    "ggv_tire_drive_force_ref_n",
    "ggv_tire_brake_force_ref_n",
    "ggv_drive_power_required_for_tire_limit_ref_kw",
    "ggv_max_tire_drive_force_n",
    "ggv_max_tire_brake_force_n",
    "ggv_max_drive_power_required_for_tire_limit_kw",
    "ymd_max_abs_yaw_moment_nm",
    "ymd_max_abs_ay_g",
]

PRIMARY_METRICS = list(DEFAULT_ENVELOPE_TORNADO_METRICS)

TORNADO_METRICS = list(DEFAULT_ENVELOPE_TORNADO_METRICS)

METRIC_LABELS = {
    "track_combined_performance_index": "Track combined index",
    "track_lateral_performance_index": "Track lateral index",
    "track_longitudinal_performance_index": "Track longitudinal index",
    "ggv_volume_g2_mps": "GGV volume",
    "ggv_area_ref_g2": "GGV area at reference speed",
    "ggv_cornering_ref_g": "Reference cornering",
    "ggv_accel_ref_g": "Reference acceleration",
    "ggv_braking_ref_g": "Reference braking",
    "ggv_mean_cornering_g": "Mean cornering",
    "ggv_mean_accel_g": "Mean acceleration",
    "ggv_mean_braking_g": "Mean braking",
    "ggv_max_cornering_g": "Max cornering",
    "ggv_max_accel_g": "Max acceleration",
    "ggv_max_braking_g": "Max braking",
    "ymd_max_abs_yaw_moment_nm": "YMD max |Mz|",
    "ymd_max_abs_ay_g": "YMD max |ay|",
}


def _variant_num(name: str) -> int:
    return int(name.rsplit("_", maxsplit=1)[-1])


def _load_joined(inputs_path: Path, metrics_path: Path) -> pd.DataFrame:
    inputs = pd.read_csv(inputs_path)
    metrics = pd.read_csv(metrics_path)
    joined = inputs.merge(metrics, on="variant", how="inner").sort_values(
        "variant",
        key=lambda s: s.map(_variant_num),
    )
    joined.attrs["input_cols"] = _input_columns_from_inputs(inputs)
    return joined


def _input_columns_from_inputs(inputs: pd.DataFrame) -> list[str]:
    return [
        col
        for col in inputs.select_dtypes(include=[np.number]).columns
        if inputs[col].nunique(dropna=True) > 1
    ]


def _input_columns(df: pd.DataFrame) -> list[str]:
    if "input_cols" in df.attrs:
        return list(df.attrs["input_cols"])

    numeric = df.select_dtypes(include=[np.number])
    metric_cols = set(_available_metrics(df))
    return [
        col
        for col in numeric.columns
        if col not in metric_cols and numeric[col].nunique(dropna=True) > 1
    ]


def _available_metrics(df: pd.DataFrame) -> list[str]:
    return [metric for metric in METRICS if metric in df.columns]


def _primary_metrics(df: pd.DataFrame) -> list[str]:
    primary = [metric for metric in PRIMARY_METRICS if metric in df.columns]
    return primary or _available_metrics(df)[:9]


def _tornado_metrics(df: pd.DataFrame) -> list[str]:
    primary = [metric for metric in TORNADO_METRICS if metric in df.columns]
    return primary or _available_metrics(df)[:6]


def _short_label(name: str) -> str:
    label = (
        name.replace("front.", "fr.")
        .replace("rear.", "rr.")
        .replace("sprung_mass.", "sprung.")
        .replace("driver_mass.", "driver.")
        .replace("inertia_kg_m2.", "I.")
        .replace("masses.", "")
        .replace("mass_kg", "mass")
        .replace("_n_m_per_rad", "")
        .replace("_n_per_m", "")
        .replace("_n_s_per_m", "")
        .replace("_deg", "")
        .replace("_scale", " scale")
        .replace("_", " ")
    )
    return "\n".join(textwrap.wrap(label, width=26, break_long_words=False))


def _metric_label(metric: str) -> str:
    label = METRIC_LABELS.get(metric, metric.replace("_", " "))
    return "\n".join(textwrap.wrap(label, width=36, break_long_words=False))


def _baseline_row(df: pd.DataFrame) -> pd.Series:
    baseline = df[df["variant"] == "variant_0000"]
    if baseline.empty:
        raise ValueError("Baseline variant_0000 not found in sensitivity results.")
    return baseline.iloc[0]


def _oat_mask(
    df: pd.DataFrame,
    input_cols: list[str],
    input_col: str,
    baseline: pd.Series,
) -> pd.Series:
    mask = pd.Series(True, index=df.index)
    for other_col in input_cols:
        if other_col == input_col:
            mask &= ~np.isclose(
                df[other_col],
                float(baseline[other_col]),
                rtol=0.0,
                atol=1e-10,
            )
        else:
            mask &= np.isclose(
                df[other_col],
                float(baseline[other_col]),
                rtol=0.0,
                atol=1e-10,
            )
    return mask


def _metric_delta_pct(values: pd.Series, baseline: float) -> pd.Series:
    if abs(baseline) <= 1e-12:
        return pd.Series(np.nan, index=values.index)
    return 100.0 * (values.astype(float) - baseline) / abs(baseline)


def _plot_tornado_summary(pdf: PdfPages, df: pd.DataFrame) -> None:
    metrics = _tornado_metrics(df)
    if not metrics:
        return

    for page_start in range(0, len(metrics), 4):
        page_metrics = metrics[page_start : page_start + 4]
        fig, axs = plt.subplots(2, 2, figsize=(13.2, 8.4))
        axs = list(np.atleast_1d(axs).flat)
        for ax, metric in zip(axs, page_metrics, strict=False):
            _plot_tornado_metric(ax, df, metric)
        for ax in axs[len(page_metrics):]:
            ax.axis("off")
        fig.suptitle(
            "One-at-a-Time Sensitivity Summary",
            fontsize=15,
            weight="bold",
        )
        fig.tight_layout()
        pdf.savefig(fig, bbox_inches="tight")
        plt.close(fig)


def _plot_tornado_metric(
    ax: plt.Axes,
    df: pd.DataFrame,
    metric: str,
    *,
    top_n: int = 7,
) -> None:
    input_cols = _input_columns(df)
    baseline = _baseline_row(df)
    metric_baseline = float(baseline[metric])
    effects: list[dict[str, object]] = []

    for input_col in input_cols:
        points = df[_oat_mask(df, input_cols, input_col, baseline)].copy()
        if points.empty:
            continue

        deltas = _metric_delta_pct(points[metric], metric_baseline)
        deltas = deltas[np.isfinite(deltas)]
        if deltas.empty:
            continue

        effects.append(
            {
                "input": input_col,
                "deltas": deltas.to_numpy(dtype=float),
                "span": float(np.nanmax(np.abs(deltas))),
            }
        )

    if not effects:
        ax.axis("off")
        return

    effects = sorted(effects, key=lambda effect: float(effect["span"]), reverse=True)
    top = effects[:top_n][::-1]
    y = np.arange(len(top))
    all_values = [0.0]

    for y_pos, effect in zip(y, top, strict=False):
        deltas = np.asarray(effect["deltas"], dtype=float)
        low = float(np.nanmin(deltas))
        high = float(np.nanmax(deltas))
        all_values.extend([low, high])
        ax.hlines(y_pos, low, high, color="#2F6B9A", linewidth=5.0, alpha=0.62)
        ax.scatter(
            deltas,
            np.full_like(deltas, y_pos, dtype=float),
            s=18,
            color=np.where(deltas >= 0.0, "#9A6A3A", "#2F6B9A"),
            edgecolor="white",
            linewidth=0.35,
            zorder=3,
        )

    max_abs = max(abs(float(value)) for value in all_values)
    x_pad = max(0.5, 0.14 * max_abs)
    ax.set_xlim(-max_abs - x_pad, max_abs + x_pad)
    ax.axvline(0.0, color="black", linewidth=0.9, alpha=0.65)
    ax.set_yticks(y)
    ax.set_yticklabels([_short_label(str(effect["input"])) for effect in top], fontsize=8)
    ax.set_xlabel("metric change from baseline (%)")
    ax.set_title(f"{_metric_label(metric)}\nbaseline {metric_baseline:.3g}", fontsize=10)
    ax.grid(True, axis="x", alpha=0.25)


def _plot_tornado_pages(
    pdf: PdfPages,
    df: pd.DataFrame,
    inputs: pd.DataFrame,
) -> None:
    input_cols = _tornado_input_columns(inputs)
    for metric in _tornado_metrics(df):
        if metric not in df.columns:
            continue
        effects = _oat_effects(
            df,
            input_cols,
            metric,
            baseline_variant="variant_0000",
        )
        if effects.empty:
            continue
        _plot_one_tornado(
            pdf,
            effects,
            metric,
            top_n=15,
            x_scale="percent",
            min_plot_span=0.05,
            min_span_fraction=0.01,
        )


def _plot_metric_overview(pdf: PdfPages, df: pd.DataFrame) -> None:
    metrics = _primary_metrics(df)
    if not metrics:
        raise ValueError("No configured EnvelopeSim metrics were found.")

    n_cols = 3
    n_rows = int(np.ceil(len(metrics) / n_cols))
    fig, axs = plt.subplots(n_rows, n_cols, figsize=(13.2, 3.1 * n_rows))
    axs = list(np.atleast_1d(axs).flat)
    baseline = _baseline_row(df)

    for ax, metric in zip(axs, metrics, strict=False):
        ordered = df.sort_values(metric)
        colors = np.where(
            ordered[metric] == ordered[metric].max(),
            "#C84C31",
            "#2F6B9A",
        )
        ax.bar(np.arange(len(ordered)), ordered[metric], color=colors)
        ax.axhline(float(baseline[metric]), color="black", linewidth=0.9, alpha=0.55)
        ax.set_title(_metric_label(metric), fontsize=10)
        ax.set_xlabel("variants sorted by metric", fontsize=8)
        ax.tick_params(axis="x", labelbottom=False)
        ax.grid(True, axis="y", alpha=0.25)

        best = ordered.iloc[-1]
        ax.text(
            0.02,
            0.95,
            f"best: {best['variant']}\n{best[metric]:.3g}",
            transform=ax.transAxes,
            va="top",
            fontsize=8,
            bbox={"boxstyle": "round,pad=0.3", "facecolor": "white", "alpha": 0.85},
        )

    for ax in axs[len(metrics):]:
        ax.axis("off")
    fig.suptitle("Envelope Sensitivity Metric Spread", fontsize=15, weight="bold")
    fig.tight_layout()
    pdf.savefig(fig, bbox_inches="tight")
    plt.close(fig)


def _plot_track_performance(pdf: PdfPages, df: pd.DataFrame) -> None:
    required = {
        "track_combined_performance_index",
        "track_lateral_performance_index",
        "track_longitudinal_performance_index",
    }
    if not required.issubset(df.columns):
        return

    ordered = df.sort_values("track_combined_performance_index", ascending=False)
    top = ordered.head(14).iloc[::-1]

    fig, axs = plt.subplots(1, 2, figsize=(14, 6))

    scatter = axs[0].scatter(
        df["track_lateral_performance_index"],
        df["track_longitudinal_performance_index"],
        c=df["track_combined_performance_index"],
        cmap="viridis",
        s=46,
        edgecolor="black",
        linewidth=0.25,
    )
    baseline = df[df["variant"] == "variant_0000"]
    if not baseline.empty:
        axs[0].scatter(
            baseline["track_lateral_performance_index"],
            baseline["track_longitudinal_performance_index"],
            s=95,
            color="#C84C31",
            edgecolor="black",
            linewidth=0.8,
            label="baseline",
        )
        axs[0].legend(loc="best")
    axs[0].axhline(1.0, color="black", linewidth=0.8, alpha=0.35)
    axs[0].axvline(1.0, color="black", linewidth=0.8, alpha=0.35)
    axs[0].set_xlabel("lateral performance index")
    axs[0].set_ylabel("longitudinal performance index")
    axs[0].set_title("Track-profile normalized performance")
    axs[0].grid(True, alpha=0.25)
    fig.colorbar(scatter, ax=axs[0], pad=0.02, label="combined index")

    axs[1].barh(
        top["variant"],
        top["track_combined_performance_index"],
        color="#2F6B9A",
    )
    axs[1].axvline(1.0, color="black", linewidth=0.8, alpha=0.35)
    axs[1].set_xlabel("combined performance index")
    axs[1].set_title("Top combined index variants")
    axs[1].grid(True, axis="x", alpha=0.25)

    fig.suptitle("Maneuver-palette performance indices", fontsize=16)
    fig.tight_layout()
    pdf.savefig(fig, bbox_inches="tight")
    plt.close(fig)


def _plot_metric_correlations(pdf: PdfPages, df: pd.DataFrame) -> None:
    inputs = _input_columns(df)
    metrics = _primary_metrics(df)
    corr = df[inputs + metrics].corr(numeric_only=True).loc[inputs, metrics]
    score = corr.abs().max(axis=1).sort_values(ascending=False)
    top_inputs = score.head(14).index.tolist()
    corr = corr.loc[top_inputs]

    fig, ax = plt.subplots(figsize=(11.6, 7.2))
    im = ax.imshow(corr.to_numpy(), cmap="coolwarm", vmin=-1.0, vmax=1.0, aspect="auto")
    ax.set_xticks(np.arange(len(metrics)))
    ax.set_xticklabels([_metric_label(metric) for metric in metrics], rotation=35, ha="right")
    ax.set_yticks(np.arange(len(top_inputs)))
    ax.set_yticklabels([_short_label(col) for col in top_inputs])
    ax.set_title("Pearson Correlation to Key Outputs")

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
        ax.set_ylabel("roadwheel/handwheel angle (deg)")
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
    inputs = pd.read_csv(inputs_path)

    output_path.parent.mkdir(parents=True, exist_ok=True)
    with PdfPages(output_path) as pdf:
        _plot_tornado_pages(pdf, df, inputs)
        _plot_metric_correlations(pdf, df)

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
