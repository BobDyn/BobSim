"""Generate tornado diagrams for OptSim one-factor sensitivity studies.

The current interval-splice sampler writes variant_0000 as the baseline, then
one-at-a-time perturbations of each input. This script joins those inputs with
StandardSim or EnvelopeSim metrics and plots each metric's response to the input
perturbations.

Usage:
    python _4_OptSim/pipeline/plot_sensitivity_tornado.py --source standard
    python _4_OptSim/pipeline/plot_sensitivity_tornado.py --source envelope
"""

from __future__ import annotations

import argparse
import fnmatch
import os
from pathlib import Path
import sys
import textwrap

os.environ.setdefault("MPLCONFIGDIR", "/tmp/matplotlib")

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages
import numpy as np
import pandas as pd


ROOT = Path(__file__).resolve().parent.parent
REPO_ROOT = ROOT.parent
if str(ROOT) not in sys.path:
    sys.path.insert(0, str(ROOT))

from pipeline.sampler import sample

DEFAULT_DOE_CONFIG = ROOT / "configs/_doe_config.yaml"
DEFAULT_INPUTS = ROOT / "results/envelope_sensitivity_inputs.csv"
DEFAULT_POPULATION = ROOT / "population"
DEFAULT_ENVELOPE_METRICS = ROOT / "results/envelope_sensitivities/envelope_sensitivity_metrics.csv"
DEFAULT_STANDARD_OUTPUT = ROOT / "results/standard_sensitivity_tornado.pdf"
DEFAULT_ENVELOPE_OUTPUT = ROOT / "results/envelope_sensitivity_tornado.pdf"
DEFAULT_STANDARD_EXCLUDE_INPUTS = ("*.spring_rate_n_per_m",)
DEFAULT_STANDARD_METRICS = (
    "roadwheel_angle_gradient_deg_per_g",
    "handwheel_angle_gradient_deg_per_g",
    "sideslip_gradient_deg_per_g",
    "understeer_gradient_deg_per_g",
    "roll_gradient_deg_per_g",
)

METRIC_LABELS = {
    "ggv_max_cornering_g": "GGV max cornering ($g$)",
    "ggv_max_accel_g": "GGV max acceleration ($g$)",
    "ggv_max_braking_g": "GGV max braking ($g$)",
    "ymd_max_abs_yaw_moment_nm": "YMD max abs yaw moment ($\\mathrm{N\\,m}$)",
    "ymd_max_abs_ay_g": "YMD max abs lateral acceleration ($g$)",
    "ay_min": "Minimum lateral acceleration ($\\mathrm{m/s^2}$)",
    "ay_max": "Maximum lateral acceleration ($\\mathrm{m/s^2}$)",
    "roadwheel_angle_gradient_deg_per_g": "Roadwheel angle gradient ($\\mathrm{deg}/g$)",
    "handwheel_angle_gradient_deg_per_g": "Handwheel angle gradient ($\\mathrm{deg}/g$)",
    "sideslip_gradient_deg_per_g": "Sideslip gradient ($\\mathrm{deg}/g$)",
    "understeer_gradient_deg_per_g": "Understeer gradient ($\\mathrm{deg}/g$)",
    "roll_gradient_deg_per_g": "Roll gradient ($\\mathrm{deg}/g$)",
    "handwheel_torque_min": "Minimum handwheel torque ($\\mathrm{N\\,m}$)",
    "handwheel_torque_max": "Maximum handwheel torque ($\\mathrm{N\\,m}$)",
}


def _variant_num(name: str) -> int:
    return int(name.rsplit("_", maxsplit=1)[-1])


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
    return "\n".join(textwrap.wrap(label, width=30, break_long_words=False))


def _metric_label(name: str) -> str:
    if name in METRIC_LABELS:
        return METRIC_LABELS[name]
    label = name.replace("_", " ")
    label = label.replace(" mps2", " ($\\mathrm{m/s^2}$)").replace(
        " nm", " ($\\mathrm{N\\,m}$)"
    )
    return "\n".join(textwrap.wrap(label, width=62, break_long_words=False))


def _input_unit(name: str) -> str:
    if name.endswith("_scale"):
        return "$\\times$"
    if name.endswith("_deg"):
        return "$\\mathrm{deg}$"
    if name.endswith("_kg"):
        return "$\\mathrm{kg}$"
    if name.endswith("_n_per_m"):
        return "$\\mathrm{N/m}$"
    if name.endswith("_n_s_per_m"):
        return "$\\mathrm{N\\,s/m}$"
    if name.endswith("_n_m_per_rad"):
        return "$\\mathrm{N\\,m/rad}$"
    if "inertia_kg_m2" in name:
        return "$\\mathrm{kg\\,m^2}$"
    if ".cg_m." in name:
        return "$\\mathrm{m}$"
    if name.endswith("_m"):
        return "$\\mathrm{m}$"
    return ""


def _format_input_value(value: float, unit: str) -> str:
    formatted = f"{value:.4g}"
    return f"{formatted} {unit}" if unit else formatted


def _read_inputs(path: Path, doe_config: Path = DEFAULT_DOE_CONFIG) -> pd.DataFrame:
    if path.exists():
        df = pd.read_csv(path)
    else:
        variants = sample(doe_config)
        df = pd.DataFrame(
            [
                {"variant": f"variant_{i:04d}", **params}
                for i, params in enumerate(variants)
            ]
        )
    return df.sort_values("variant", key=lambda s: s.map(_variant_num)).reset_index(drop=True)


def _read_envelope_metrics(path: Path) -> pd.DataFrame:
    return pd.read_csv(path).sort_values("variant", key=lambda s: s.map(_variant_num))


def _read_standard_metrics(population_dir: Path, standard: str) -> pd.DataFrame:
    rows: list[dict[str, float | str]] = []
    for variant_dir in sorted(population_dir.glob("variant_????")):
        metrics_path = variant_dir / "results" / standard / "metrics.csv"
        if not metrics_path.exists():
            continue

        metrics = pd.read_csv(metrics_path)
        if "standard" in metrics.columns:
            metrics = metrics[metrics["standard"] == standard]
        numeric_metrics = metrics.copy()
        numeric_metrics["value"] = pd.to_numeric(numeric_metrics["value"], errors="coerce")
        numeric_metrics = numeric_metrics.dropna(subset=["value"])

        row: dict[str, float | str] = {"variant": variant_dir.name}
        row.update(dict(zip(numeric_metrics["metric"], numeric_metrics["value"], strict=False)))
        rows.append(row)

    if not rows:
        raise FileNotFoundError(
            f"No StandardSim metrics found below {population_dir} for {standard}"
        )

    return pd.DataFrame(rows).sort_values("variant", key=lambda s: s.map(_variant_num))


def _join(inputs: pd.DataFrame, metrics: pd.DataFrame) -> pd.DataFrame:
    joined = inputs.merge(metrics, on="variant", how="inner")
    if joined.empty:
        raise ValueError("No variants matched between inputs and metrics")
    return joined.sort_values("variant", key=lambda s: s.map(_variant_num)).reset_index(drop=True)


def _input_columns(
    inputs: pd.DataFrame,
    exclude_patterns: list[str] | tuple[str, ...] = (),
) -> list[str]:
    return [
        col
        for col in inputs.select_dtypes(include=[np.number]).columns
        if inputs[col].nunique(dropna=True) > 1
        and not any(fnmatch.fnmatch(col, pattern) for pattern in exclude_patterns)
    ]


def _metric_columns(df: pd.DataFrame, input_cols: list[str]) -> list[str]:
    excluded = set(input_cols) | {"variant"}
    metrics = []
    for col in df.select_dtypes(include=[np.number]).columns:
        if col not in excluded and df[col].nunique(dropna=True) > 1:
            metrics.append(col)
    return metrics


def _oat_effects(
    df: pd.DataFrame,
    input_cols: list[str],
    metric: str,
    *,
    baseline_variant: str,
) -> pd.DataFrame:
    baseline = df[df["variant"] == baseline_variant]
    if baseline.empty:
        raise ValueError(f"Baseline variant not found: {baseline_variant}")
    base = baseline.iloc[0]
    base_metric = float(base[metric])

    rows = []
    for input_col in input_cols:
        mask = pd.Series(True, index=df.index)
        for other_col in input_cols:
            if other_col == input_col:
                mask &= ~np.isclose(df[other_col], float(base[other_col]), rtol=0, atol=1e-10)
            else:
                mask &= np.isclose(df[other_col], float(base[other_col]), rtol=0, atol=1e-10)

        perturbed = df[mask]
        if perturbed.empty:
            continue

        perturbed = perturbed.copy()
        perturbed[metric] = pd.to_numeric(perturbed[metric], errors="coerce")
        perturbed[input_col] = pd.to_numeric(perturbed[input_col], errors="coerce")
        perturbed = perturbed.dropna(subset=[metric, input_col]).sort_values(input_col)
        if perturbed.empty:
            continue

        base_input = float(base[input_col])
        points = []
        for _, point in perturbed.iterrows():
            input_value = float(point[input_col])
            metric_value = float(point[metric])
            delta = metric_value - base_metric
            delta_pct = 100.0 * delta / abs(base_metric) if abs(base_metric) > 1e-12 else np.nan
            input_pct = (
                100.0 * (input_value - base_input) / abs(base_input)
                if abs(base_input) > 1e-12
                else np.nan
            )
            points.append(
                {
                    "variant": point["variant"],
                    "input_value": input_value,
                    "metric_value": metric_value,
                    "delta": delta,
                    "delta_pct": delta_pct,
                    "input_pct": input_pct,
                }
            )

        span = max(abs(point["delta"]) for point in points)
        finite_pct = [
            abs(point["delta_pct"])
            for point in points
            if np.isfinite(point["delta_pct"])
        ]
        span_pct = max(finite_pct) if finite_pct else np.nan

        rows.append(
            {
                "input": input_col,
                "label": _short_label(input_col),
                "baseline": base_metric,
                "input_baseline": base_input,
                "points": points,
                "span": span,
                "span_pct": span_pct,
            }
        )

    effects = pd.DataFrame(rows)
    if effects.empty:
        return effects
    return effects.sort_values("span", ascending=False)


def _plot_one_tornado(
    pdf: PdfPages,
    effects: pd.DataFrame,
    metric: str,
    *,
    top_n: int,
    x_scale: str,
) -> None:
    effects = effects.copy()
    use_percent = x_scale == "percent" and effects["span_pct"].notna().any()
    if use_percent:
        x_label = "metric change from baseline (%)"
        max_abs_format = "{:.1f}%"
    else:
        x_label = "metric change from baseline"
        max_abs_format = "{:.3g}"

    effects["plot_span"] = effects["span_pct" if use_percent else "span"]
    plot_df = effects.sort_values("plot_span", ascending=False).head(top_n).iloc[::-1]
    y = np.arange(len(plot_df))

    fig_h = max(6.0, 0.62 * len(plot_df) + 1.8)
    fig, ax = plt.subplots(figsize=(12.5, fig_h))

    row_labels = []
    for row in plot_df.itertuples(index=False):
        unit = _input_unit(row.input)
        ordered_inputs = [
            (float(point["input_value"]), _format_input_value(point["input_value"], unit))
            for point in row.points
        ]
        ordered_inputs.append(
            (float(row.input_baseline), f"base {_format_input_value(row.input_baseline, unit)}")
        )
        input_line = " | ".join(label for _, label in sorted(ordered_inputs, key=lambda item: item[0]))
        row_labels.append(f"{row.label}\n{input_line}")

    color_cycle = ["#355C7D", "#6F92A8", "#A08458", "#7C5F3D"]
    label_cycle = ["lowest input", "low-mid input", "high-mid input", "highest input"]
    max_points = max(len(points) for points in plot_df["points"])
    if max_points <= 1:
        offsets = [0.0]
    else:
        offsets = np.linspace(-0.27, 0.27, max_points)
    bar_height = min(0.13, 0.52 / max_points)
    all_plot_values = [0.0]

    for point_idx in range(max_points):
        bar_y = []
        bar_x = []
        for y_pos, row in zip(y, plot_df.itertuples(index=False), strict=False):
            if point_idx >= len(row.points):
                continue
            point = row.points[point_idx]
            plot_value = point["delta_pct"] if use_percent else point["delta"]
            if not np.isfinite(plot_value):
                continue
            bar_y.append(y_pos + offsets[point_idx])
            bar_x.append(plot_value)
            all_plot_values.append(plot_value)

        if not bar_x:
            continue
        ax.barh(
            bar_y,
            bar_x,
            height=bar_height,
            color=color_cycle[point_idx % len(color_cycle)],
            alpha=0.92,
            label=label_cycle[point_idx] if point_idx < len(label_cycle) else f"input {point_idx + 1}",
        )

    ax.axvline(0.0, color="black", linewidth=1.0)
    ax.set_yticks(y)
    ax.set_yticklabels(row_labels, fontsize=7)
    ax.set_xlabel(x_label)
    fig.suptitle(f"Tornado: {_metric_label(metric)}", fontsize=12, y=0.965)
    ax.grid(True, axis="x", alpha=0.25)
    ax.legend(loc="lower right", frameon=False, ncols=2)

    xmin = float(np.nanmin(all_plot_values))
    xmax = float(np.nanmax(all_plot_values))
    span = xmax - xmin
    pad = span * 0.14 if span > 0 else max(abs(xmax), 1.0) * 0.14
    ax.set_xlim(xmin - pad, xmax + pad)

    baseline = float(plot_df["baseline"].iloc[0])
    max_abs = float(plot_df["plot_span"].max())
    ax.text(
        0.0,
        1.008,
        f"baseline {baseline:.5g}   max abs change {max_abs_format.format(max_abs)}   bars are ordered from lowest to highest input; row values include baseline",
        transform=ax.transAxes,
        ha="left",
        va="bottom",
        fontsize=9,
    )

    ax.tick_params(axis="x", labelsize=8)
    ax.margins(y=0.03)
    fig.subplots_adjust(left=0.36, right=0.96, top=0.865, bottom=0.10)
    pdf.savefig(fig, bbox_inches="tight")
    plt.close(fig)


def make_tornado_pdf(
    df: pd.DataFrame,
    inputs: pd.DataFrame,
    output_path: Path,
    *,
    baseline_variant: str = "variant_0000",
    top_n: int = 20,
    metrics: list[str] | None = None,
    x_scale: str = "percent",
    exclude_inputs: list[str] | tuple[str, ...] = (),
) -> None:
    input_cols = _input_columns(inputs, exclude_inputs)
    metric_cols = metrics or _metric_columns(df, input_cols)
    if not metric_cols:
        raise ValueError("No numeric metric columns found for tornado plotting")

    output_path.parent.mkdir(parents=True, exist_ok=True)
    with PdfPages(output_path) as pdf:
        for metric in metric_cols:
            effects = _oat_effects(
                df,
                input_cols,
                metric,
                baseline_variant=baseline_variant,
            )
            if effects.empty:
                continue
            _plot_one_tornado(pdf, effects, metric, top_n=top_n, x_scale=x_scale)

    print(f"Tornado PDF written: {output_path}")


def _parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Generate OptSim tornado diagrams")
    parser.add_argument(
        "--source",
        choices=["standard", "envelope"],
        required=True,
        help="Metric source to visualize",
    )
    parser.add_argument("--inputs", type=Path, default=DEFAULT_INPUTS)
    parser.add_argument("--population-dir", type=Path, default=DEFAULT_POPULATION)
    parser.add_argument("--standard", default="SteadyStateEval")
    parser.add_argument("--envelope-metrics", type=Path, default=DEFAULT_ENVELOPE_METRICS)
    parser.add_argument("--output", type=Path)
    parser.add_argument("--joined-output", type=Path)
    parser.add_argument("--baseline-variant", default="variant_0000")
    parser.add_argument("--top-n", type=int, default=15)
    parser.add_argument(
        "--exclude-input",
        action="append",
        default=None,
        help=(
            "Input column glob to exclude from tornado plots. "
            "Can be passed multiple times. StandardSim defaults to '*.spring_rate_n_per_m'."
        ),
    )
    parser.add_argument(
        "--x-scale",
        choices=["percent", "absolute"],
        default="percent",
        help="Plot metric deltas as percent of baseline or absolute values.",
    )
    parser.add_argument(
        "--metrics",
        nargs="*",
        help="Optional metric column names to plot. Defaults to all numeric metrics.",
    )
    return parser.parse_args()


def main() -> None:
    args = _parse_args()
    inputs = _read_inputs(args.inputs)

    if args.source == "standard":
        metrics = _read_standard_metrics(args.population_dir, args.standard)
        output = args.output or DEFAULT_STANDARD_OUTPUT
        exclude_inputs = (
            list(DEFAULT_STANDARD_EXCLUDE_INPUTS)
            if args.exclude_input is None
            else args.exclude_input
        )
        plot_metrics = args.metrics or [
            metric for metric in DEFAULT_STANDARD_METRICS if metric in metrics.columns
        ]
    else:
        metrics = _read_envelope_metrics(args.envelope_metrics)
        output = args.output or DEFAULT_ENVELOPE_OUTPUT
        exclude_inputs = args.exclude_input or []
        plot_metrics = args.metrics

    joined = _join(inputs, metrics)
    if args.joined_output:
        args.joined_output.parent.mkdir(parents=True, exist_ok=True)
        joined.to_csv(args.joined_output, index=False)

    make_tornado_pdf(
        joined,
        inputs,
        output,
        baseline_variant=args.baseline_variant,
        top_n=args.top_n,
        metrics=plot_metrics,
        x_scale=args.x_scale,
        exclude_inputs=exclude_inputs,
    )


if __name__ == "__main__":
    main()
