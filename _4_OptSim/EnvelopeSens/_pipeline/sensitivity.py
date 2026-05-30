"""EnvelopeSim sensitivity generation and execution.

This workflow is deliberately scoped to quasi-static vehicle envelope physics:
mass properties, CG, simple load transfer, aero scale/balance, tire peak/load
sensitivity, longitudinal limits, and architecture-scale wheelbase/track.
"""

from __future__ import annotations

from copy import deepcopy
from dataclasses import dataclass, replace
from pathlib import Path
import sys
from typing import Any

import numpy as np
import pandas as pd
import yaml


PIPELINE_DIR = Path(__file__).resolve().parent
ENVELOPE_DIR = PIPELINE_DIR.parent
OPTSIM_DIR = ENVELOPE_DIR.parent
REPO_ROOT = OPTSIM_DIR.parent
ENVELOPE_CONFIG = ENVELOPE_DIR / "config.yml"
DEFAULT_GGV_CONFIG = REPO_ROOT / "_2_EnvelopeSim/GGV/ggv_config.yml"
BUILD_DIR = OPTSIM_DIR / "Build" / "EnvelopeSens"
RESULTS_DIR = OPTSIM_DIR / "results"
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from _2_EnvelopeSim.GGV.ggv_generation import (  # noqa: E402
    G,
    GGVConfig,
    aero_loads,
    generate_ggv,
    load_ggv_config,
    save_ggv_csv,
    solve_ax_limit,
    summarize_ggv_capability,
    track_performance_metrics,
    track_profile_from_config,
)
from _2_EnvelopeSim.YMD.ymd_generation import (  # noqa: E402
    YMDConfig,
    generate_ymd,
    save_ymd_csv,
)
from _2_EnvelopeSim.vehicle_yaml import (  # noqa: E402
    EnvelopeVehicleProjection,
    load_vehicle_yaml,
    project_vehicle_yaml,
)


ENVELOPE_METRICS = [
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

VEHICLE_PATHS = {
    "sprung_mass.mass_kg",
    "sprung_mass.cg_m.x",
    "sprung_mass.cg_m.z",
    "driver_mass.mass_kg",
    "driver_mass.cg_m.x",
    "driver_mass.cg_m.z",
    "front.masses.unsprung.mass_kg",
    "rear.masses.unsprung.mass_kg",
    "front.stabar.rate_n_m_per_rad",
    "rear.stabar.rate_n_m_per_rad",
}

CONTROL_PATHS = {
    "aero.load_scale",
    "aero.downforce_scale",
    "aero.drag_scale",
    "aero.balance_front",
    "tire.mu_scale",
    "tire.load_sensitivity_scale",
    "tire.cornering_stiffness_scale",
    "power.max_drive_power_kw",
    "brake.front_bias",
    "geometry.wheelbase_scale",
    "geometry.track_scale",
}

ENVELOPE_MEANINGFUL_PATHS = VEHICLE_PATHS | CONTROL_PATHS

PATH_ALIASES = {
    "front.stabar.rate_n_m_per_rad": "front.actuation.stabar.rate_n_m_per_rad",
    "rear.stabar.rate_n_m_per_rad": "rear.actuation.stabar.rate_n_m_per_rad",
}

AXIS_INDEX = {"x": 0, "y": 1, "z": 2}


@dataclass(frozen=True)
class EnvelopeControls:
    aero_downforce_scale: float = 1.0
    aero_drag_scale: float = 1.0
    aero_balance_front: float | None = None
    tire_mu_scale: float = 1.0
    tire_load_sensitivity_scale: float = 1.0
    tire_cornering_stiffness_scale: float = 1.0
    max_drive_power_w: float = 80_000.0
    brake_front_bias: float = 0.84
    wheelbase_scale: float = 1.0
    track_scale: float = 1.0


@dataclass(frozen=True)
class EnvelopeVariant:
    name: str
    params: dict[str, float]
    vehicle_data: dict[str, Any]
    controls: EnvelopeControls


def build_envelope_variants(
    config_path: Path = ENVELOPE_CONFIG,
) -> tuple[list[EnvelopeVariant], pd.DataFrame]:
    config = _load_yaml(config_path)
    vehicle_path = _resolve_vehicle_path(config, config_path)
    baseline_vehicle = load_vehicle_yaml(vehicle_path)
    baseline_projection = project_vehicle_yaml(baseline_vehicle, repo_root=REPO_ROOT)

    variables = list(config["variables"])
    included = [var for var in variables if str(var["path"]) in ENVELOPE_MEANINGFUL_PATHS]
    if not included:
        raise ValueError("No EnvelopeSim-meaningful variables found in config.")

    baseline = {
        str(var["path"]): _baseline_value(baseline_vehicle, baseline_projection, var)
        for var in included
    }
    sampling = config.get("sampling") or {}
    variants = _sample_interval_splice(
        included,
        baseline,
        int(sampling.get("intervals", 4)),
    )

    envelope_variants: list[EnvelopeVariant] = []
    for i, params in enumerate(variants):
        vehicle_data = deepcopy(baseline_vehicle)
        controls = EnvelopeControls()
        for path, value in params.items():
            if path in VEHICLE_PATHS:
                _set_vehicle_value(vehicle_data, path, float(value))
            else:
                controls = _set_control_value(controls, path, float(value))

        envelope_variants.append(
            EnvelopeVariant(
                name=f"variant_{i:04d}",
                params={path: float(value) for path, value in params.items()},
                vehicle_data=vehicle_data,
                controls=controls,
            )
        )

    return envelope_variants, envelope_scope_table(config_path)


def envelope_scope_table(config_path: Path = ENVELOPE_CONFIG) -> pd.DataFrame:
    config = _load_yaml(config_path)
    rows: list[dict[str, str | bool]] = []
    for var in config["variables"]:
        path = str(var["path"])
        included = path in ENVELOPE_MEANINGFUL_PATHS
        rows.append(
            {
                "path": path,
                "label": str(var.get("label", path)),
                "included": included,
                "reason": (
                    "represented by the quasi-static EnvelopeSim reduced model"
                    if included
                    else "excluded: not represented by the current EnvelopeSim reduced model"
                ),
            }
        )
    return pd.DataFrame(rows)


def write_envelope_variant_table(
    variants: list[EnvelopeVariant],
    output_path: Path,
) -> pd.DataFrame:
    rows = [
        {"variant": variant.name, **variant.params}
        for variant in variants
    ]
    df = pd.DataFrame(rows)
    output_path.parent.mkdir(parents=True, exist_ok=True)
    df.to_csv(output_path, index=False)
    return df


def run_envelope_sensitivities(
    variants: list[EnvelopeVariant],
    output_dir: Path,
) -> pd.DataFrame:
    output_dir.mkdir(parents=True, exist_ok=True)

    config = _load_yaml(ENVELOPE_CONFIG)
    ggv_report_config = _load_workflow_ggv_config(config, ENVELOPE_CONFIG)
    track_profile = track_profile_from_config(ggv_report_config)
    reference_speed = _workflow_reference_speed(config, ggv_report_config)

    ggv_config = GGVConfig(
        speeds=(5.0, 10.0, 15.0, 20.0, 25.0),
        ay_max_g=4.5,
        ay_points=81,
        ax_search_points=201,
        verbose=False,
        warn_tire_load_range=False,
    )
    ymd_config = YMDConfig(
        speed=15.0,
        beta_min_deg=-8.0,
        beta_max_deg=8.0,
        beta_points=31,
        hwa_min_deg=-8.0,
        hwa_max_deg=8.0,
        hwa_points=31,
        verbose=False,
        warn_tire_load_range=False,
    )

    metric_rows: list[dict[str, float | str]] = []
    projection_rows: list[dict[str, float | str]] = []
    track_profile_rows: list[dict[str, float | str]] = []
    for i, variant in enumerate(variants, start=1):
        print(f"[{i:>{len(str(len(variants)))}}/{len(variants)}] {variant.name}")
        projection = project_vehicle_yaml(
            variant.vehicle_data,
            repo_root=REPO_ROOT,
            aero_downforce_scale=variant.controls.aero_downforce_scale,
            aero_drag_scale=variant.controls.aero_drag_scale,
            aero_balance_front=variant.controls.aero_balance_front,
        )
        projection = _apply_controls(projection, variant.controls)

        variant_output = output_dir / variant.name
        variant_output.mkdir(parents=True, exist_ok=True)

        envelopes = generate_ggv(projection.ggv, ggv_config)
        save_ggv_csv(envelopes, variant_output / "ggv.csv")
        longitudinal_limits = _longitudinal_tire_limits(projection.ggv, ggv_config)
        longitudinal_limits.to_csv(
            variant_output / "longitudinal_tire_limits.csv",
            index=False,
        )

        ymd = generate_ymd(projection.ymd, ymd_config)
        save_ymd_csv(ymd, variant_output / "ymd.csv")

        max_yaw_moment = float(np.nanmax(np.abs(ymd.mz)))
        max_ymd_ay_g = float(np.nanmax(np.abs(ymd.ay))) / G
        reference_longitudinal = _nearest_speed_row(longitudinal_limits, 15.0)
        ggv_metrics, _capability_rows = summarize_ggv_capability(
            envelopes,
            reference_speed_mps=reference_speed,
        )
        track_metrics, variant_track_rows = track_performance_metrics(
            envelopes,
            track_profile,
        )
        variant_track_profile = pd.DataFrame(variant_track_rows)
        variant_track_profile.insert(0, "variant", variant.name)
        variant_track_profile.to_csv(
            variant_output / "track_performance_profile.csv",
            index=False,
        )
        track_profile_rows.extend(variant_track_profile.to_dict("records"))

        metric_rows.append(
            {
                "variant": variant.name,
                **ggv_metrics,
                **track_metrics,
                "ymd_max_abs_yaw_moment_nm": max_yaw_moment,
                "ymd_max_abs_ay_g": max_ymd_ay_g,
                "ggv_tire_drive_force_ref_n": float(
                    reference_longitudinal["tire_drive_force_limit_n"]
                ),
                "ggv_tire_brake_force_ref_n": float(
                    reference_longitudinal["tire_brake_force_limit_n"]
                ),
                "ggv_drive_power_required_for_tire_limit_ref_kw": float(
                    reference_longitudinal["drive_power_required_for_tire_limit_kw"]
                ),
                "ggv_max_tire_drive_force_n": float(
                    np.nanmax(longitudinal_limits["tire_drive_force_limit_n"])
                ),
                "ggv_max_tire_brake_force_n": float(
                    np.nanmax(longitudinal_limits["tire_brake_force_limit_n"])
                ),
                "ggv_max_drive_power_required_for_tire_limit_kw": float(
                    np.nanmax(
                        longitudinal_limits[
                            "drive_power_required_for_tire_limit_kw"
                        ]
                    )
                ),
            }
        )
        projection_rows.append(
            {
                "variant": variant.name,
                **projection.summary,
                **_control_summary(variant.controls),
            }
        )

    metrics = pd.DataFrame(metric_rows)
    _add_normalized_track_indices(metrics, track_profile)
    metrics.to_csv(output_dir / "envelope_sensitivity_metrics.csv", index=False)
    pd.DataFrame(projection_rows).to_csv(
        output_dir / "envelope_vehicle_projection.csv",
        index=False,
    )
    pd.DataFrame(track_profile_rows).to_csv(
        output_dir / "track_performance_profiles.csv",
        index=False,
    )
    return metrics


def _load_workflow_ggv_config(
    config: dict[str, Any],
    config_path: Path,
) -> dict[str, Any]:
    ggv_config_path = _resolve_ggv_config_path(config, config_path)
    ggv_config = load_ggv_config(ggv_config_path)
    performance = config.get("performance_index")
    if performance is not None:
        if not isinstance(performance, dict):
            raise ValueError("performance_index must be a mapping when provided.")
        ggv_config = dict(ggv_config)
        ggv_config["performance_index"] = performance
    return ggv_config


def _resolve_ggv_config_path(config: dict[str, Any], config_path: Path) -> Path:
    raw_path = config.get("ggv_config")
    if raw_path is None:
        return DEFAULT_GGV_CONFIG
    path = Path(str(raw_path))
    if path.is_absolute():
        return path
    return (config_path.parent / path).resolve()


def _workflow_reference_speed(
    config: dict[str, Any],
    ggv_config: dict[str, Any],
) -> float:
    performance = config.get("performance_index") or {}
    if isinstance(performance, dict) and "reference_speed_mps" in performance:
        return float(performance["reference_speed_mps"])
    report = ggv_config.get("report") or {}
    return float(report.get("reference_speed_mps", 15.0))


def _ggv_integral_metrics(
    envelopes: list[Any],
    *,
    reference_speed: float,
) -> dict[str, float]:
    area = _ggv_area_by_speed(envelopes)
    volume_mps5 = _integrate_speed_area(
        area["speed_mps"].to_numpy(dtype=float),
        area["area_mps4"].to_numpy(dtype=float),
    )
    area_ref_mps4 = _interp_by_speed(area, "area_mps4", reference_speed)
    return {
        "ggv_volume_g2_mps": volume_mps5 / G**2,
        "ggv_area_ref_g2": area_ref_mps4 / G**2,
    }


def _ggv_area_by_speed(envelopes: list[Any]) -> pd.DataFrame:
    rows: list[dict[str, float]] = []
    for env in envelopes:
        order = np.argsort(env.ay)
        ay = np.asarray(env.ay, dtype=float)[order]
        ax_accel = np.asarray(env.ax_accel, dtype=float)[order]
        ax_brake = np.asarray(env.ax_brake, dtype=float)[order]
        feasible = np.isfinite(ax_accel) & np.isfinite(ax_brake)

        if np.count_nonzero(feasible) >= 2:
            width = np.maximum(ax_accel[feasible] - ax_brake[feasible], 0.0)
            area_mps4 = _trapz(width, ay[feasible])
        else:
            area_mps4 = float("nan")

        rows.append(
            {
                "speed_mps": float(env.speed),
                "area_mps4": area_mps4,
                "area_g2": area_mps4 / G**2,
            }
        )
    return pd.DataFrame(rows)


def _track_performance_metrics(
    envelopes: list[Any],
    track_profile: dict[str, Any],
) -> tuple[dict[str, float], pd.DataFrame]:
    straightline = _straightline_capacity_by_speed(envelopes)
    rows: list[dict[str, float | str]] = []

    for maneuver in track_profile["maneuvers"]:
        maneuver_type = str(maneuver["type"])
        if maneuver_type == "corner":
            radius = float(maneuver["radius_m"])
            score = _corner_speed_for_radius(envelopes, radius)
            rows.append(
                {
                    "maneuver": str(maneuver["name"]),
                    "type": maneuver_type,
                    "group": "lateral",
                    "weight": float(maneuver["weight"]),
                    "radius_m": radius,
                    "speed_start_mps": np.nan,
                    "speed_end_mps": np.nan,
                    "score": score,
                    "score_units": "m/s",
                }
            )
        elif maneuver_type in {"accel", "brake"}:
            start = float(maneuver["speed_start_mps"])
            end = float(maneuver["speed_end_mps"])
            column = (
                "ax_accel_mps2"
                if maneuver_type == "accel"
                else "brake_decel_mps2"
            )
            score = _mean_capacity_over_speed(straightline, column, start, end)
            rows.append(
                {
                    "maneuver": str(maneuver["name"]),
                    "type": maneuver_type,
                    "group": maneuver_type,
                    "weight": float(maneuver["weight"]),
                    "radius_m": np.nan,
                    "speed_start_mps": start,
                    "speed_end_mps": end,
                    "score": score,
                    "score_units": "m/s^2",
                }
            )

    profile = pd.DataFrame(rows)
    lateral = profile[profile["group"] == "lateral"]
    accel = profile[profile["group"] == "accel"]
    brake = profile[profile["group"] == "brake"]
    longitudinal = profile[profile["group"].isin(["accel", "brake"])]

    return (
        {
            "track_corner_speed_mean_mps": _weighted_score(lateral),
            "track_corner_speed_min_mps": float(lateral["score"].min())
            if not lateral.empty
            else float("nan"),
            "track_accel_capacity_mean_mps2": _weighted_score(accel),
            "track_brake_capacity_mean_mps2": _weighted_score(brake),
            "track_longitudinal_capacity_mean_mps2": _weighted_score(longitudinal),
        },
        profile,
    )


def _add_normalized_track_indices(
    metrics: pd.DataFrame,
    track_profile: dict[str, Any],
    *,
    baseline_variant: str = "variant_0000",
) -> None:
    baseline_rows = metrics[metrics["variant"] == baseline_variant]
    baseline = baseline_rows.iloc[0] if not baseline_rows.empty else metrics.iloc[0]

    longitudinal_raw = (
        "track_straight_speed_mean_mps"
        if "track_straight_speed_mean_mps" in metrics.columns
        and np.isfinite(float(baseline.get("track_straight_speed_mean_mps", np.nan)))
        else "track_longitudinal_capacity_mean_mps2"
    )
    normalizations = {
        "track_lateral_performance_index": "track_corner_speed_mean_mps",
        "track_accel_performance_index": "track_accel_capacity_mean_mps2",
        "track_brake_performance_index": "track_brake_capacity_mean_mps2",
        "track_longitudinal_performance_index": longitudinal_raw,
    }
    for index_col, raw_col in normalizations.items():
        metrics[index_col] = _normalized_column(metrics[raw_col], float(baseline[raw_col]))

    lateral_weight = float(track_profile["lateral_weight"])
    longitudinal_weight = float(track_profile["longitudinal_weight"])
    metrics["track_combined_performance_index"] = (
        lateral_weight * metrics["track_lateral_performance_index"]
        + longitudinal_weight * metrics["track_longitudinal_performance_index"]
    )


def _straightline_capacity_by_speed(envelopes: list[Any]) -> pd.DataFrame:
    rows: list[dict[str, float]] = []
    for env in envelopes:
        ay = np.asarray(env.ay, dtype=float)
        idx = int(np.nanargmin(np.abs(ay)))
        rows.append(
            {
                "speed_mps": float(env.speed),
                "ax_accel_mps2": float(np.asarray(env.ax_accel, dtype=float)[idx]),
                "brake_decel_mps2": float(
                    abs(np.asarray(env.ax_brake, dtype=float)[idx])
                ),
            }
        )
    return pd.DataFrame(rows).sort_values("speed_mps")


def _corner_speed_for_radius(envelopes: list[Any], radius_m: float) -> float:
    if radius_m <= 0.0:
        return float("nan")

    speeds = np.array([float(env.speed) for env in envelopes], dtype=float)
    ay_limits = np.array(
        [
            _max_feasible_lateral_g(env) * G
            for env in envelopes
        ],
        dtype=float,
    )
    valid = np.isfinite(speeds) & np.isfinite(ay_limits) & (ay_limits > 0.0)
    if np.count_nonzero(valid) < 1:
        return float("nan")

    speeds = speeds[valid]
    ay_limits = ay_limits[valid]
    order = np.argsort(speeds)
    speeds = speeds[order]
    ay_limits = ay_limits[order]

    dense_speeds = np.linspace(float(speeds[0]), float(speeds[-1]), 501)
    dense_ay = np.interp(dense_speeds, speeds, ay_limits)
    required_ay = dense_speeds**2 / radius_m
    feasible = required_ay <= dense_ay
    if np.any(feasible):
        return float(np.max(dense_speeds[feasible]))

    low_speed_estimate = np.sqrt(max(float(ay_limits[0]), 0.0) * radius_m)
    return float(min(low_speed_estimate, speeds[0]))


def _mean_capacity_over_speed(
    straightline: pd.DataFrame,
    column: str,
    speed_start: float,
    speed_end: float,
) -> float:
    speeds = straightline["speed_mps"].to_numpy(dtype=float)
    values = straightline[column].to_numpy(dtype=float)
    valid = np.isfinite(speeds) & np.isfinite(values)
    if np.count_nonzero(valid) < 1:
        return float("nan")

    speeds = speeds[valid]
    values = values[valid]
    order = np.argsort(speeds)
    speeds = speeds[order]
    values = values[order]

    low, high = sorted((float(speed_start), float(speed_end)))
    low = max(low, float(speeds[0]))
    high = min(high, float(speeds[-1]))
    if high <= low:
        speed = _clip(0.5 * (float(speed_start) + float(speed_end)), speeds[0], speeds[-1])
        return float(np.interp(speed, speeds, values))

    dense_speeds = np.linspace(low, high, 101)
    dense_values = np.interp(dense_speeds, speeds, values)
    return _trapz(dense_values, dense_speeds) / (high - low)


def _weighted_score(rows: pd.DataFrame) -> float:
    if rows.empty:
        return float("nan")
    score = pd.to_numeric(rows["score"], errors="coerce").to_numpy(dtype=float)
    weight = pd.to_numeric(rows["weight"], errors="coerce").to_numpy(dtype=float)
    valid = np.isfinite(score) & np.isfinite(weight) & (weight > 0.0)
    if not np.any(valid):
        return float("nan")
    return float(np.average(score[valid], weights=weight[valid]))


def _normalized_column(values: pd.Series, baseline: float) -> pd.Series:
    if not np.isfinite(baseline) or abs(baseline) <= 1e-12:
        return pd.Series(np.nan, index=values.index)
    return values.astype(float) / baseline


def _integrate_speed_area(speeds: np.ndarray, areas: np.ndarray) -> float:
    valid = np.isfinite(speeds) & np.isfinite(areas)
    if np.count_nonzero(valid) < 2:
        return float("nan")
    speeds = speeds[valid]
    areas = areas[valid]
    order = np.argsort(speeds)
    return _trapz(areas[order], speeds[order])


def _interp_by_speed(df: pd.DataFrame, column: str, speed: float) -> float:
    speeds = df["speed_mps"].to_numpy(dtype=float)
    values = df[column].to_numpy(dtype=float)
    valid = np.isfinite(speeds) & np.isfinite(values)
    if np.count_nonzero(valid) < 1:
        return float("nan")
    speeds = speeds[valid]
    values = values[valid]
    order = np.argsort(speeds)
    return float(np.interp(float(speed), speeds[order], values[order]))


def _trapz(y: np.ndarray, x: np.ndarray) -> float:
    if hasattr(np, "trapezoid"):
        return float(np.trapezoid(y, x))
    return float(np.trapz(y, x))


def compute_relative_sensitivities(
    inputs: pd.DataFrame,
    metrics: pd.DataFrame,
    output_path: Path | None = None,
    *,
    baseline_variant: str = "variant_0000",
) -> pd.DataFrame:
    joined = inputs.merge(metrics, on="variant", how="inner")
    baseline_rows = joined[joined["variant"] == baseline_variant]
    if baseline_rows.empty:
        raise ValueError(f"Baseline variant not found: {baseline_variant}")
    baseline = baseline_rows.iloc[0]

    input_cols = [
        col
        for col in inputs.select_dtypes(include=[np.number]).columns
        if inputs[col].nunique(dropna=True) > 1
    ]
    metric_cols = [metric for metric in ENVELOPE_METRICS if metric in metrics.columns]

    rows: list[dict[str, float | str]] = []
    for input_col in input_cols:
        mask = pd.Series(True, index=joined.index)
        for other_col in input_cols:
            if other_col == input_col:
                mask &= ~np.isclose(
                    joined[other_col],
                    float(baseline[other_col]),
                    rtol=0.0,
                    atol=1e-10,
                )
            else:
                mask &= np.isclose(
                    joined[other_col],
                    float(baseline[other_col]),
                    rtol=0.0,
                    atol=1e-10,
                )

        for _, point in joined[mask].sort_values(input_col).iterrows():
            input_base = float(baseline[input_col])
            input_value = float(point[input_col])
            input_delta = input_value - input_base
            input_delta_pct = _percent_delta(input_value, input_base)
            for metric in metric_cols:
                metric_base = float(baseline[metric])
                metric_value = float(point[metric])
                metric_delta = metric_value - metric_base
                metric_delta_pct = _percent_delta(metric_value, metric_base)
                relative = (
                    metric_delta_pct / input_delta_pct
                    if np.isfinite(input_delta_pct) and abs(input_delta_pct) > 1e-12
                    else float("nan")
                )
                rows.append(
                    {
                        "input": input_col,
                        "variant": str(point["variant"]),
                        "input_baseline": input_base,
                        "input_value": input_value,
                        "input_delta": input_delta,
                        "input_delta_pct": input_delta_pct,
                        "metric": metric,
                        "metric_baseline": metric_base,
                        "metric_value": metric_value,
                        "metric_delta": metric_delta,
                        "metric_delta_pct": metric_delta_pct,
                        "relative_sensitivity": relative,
                    }
                )

    df = pd.DataFrame(rows)
    if output_path is not None:
        output_path.parent.mkdir(parents=True, exist_ok=True)
        df.to_csv(output_path, index=False)
    return df


def _apply_controls(
    projection: EnvelopeVehicleProjection,
    controls: EnvelopeControls,
) -> EnvelopeVehicleProjection:
    ggv_base = projection.ggv
    ymd_base = projection.ymd

    wheelbase = ggv_base.wheelbase * controls.wheelbase_scale
    track_front = ggv_base.track_front * controls.track_scale
    track_rear = ggv_base.track_rear * controls.track_scale
    aero_balance = (
        ggv_base.aero_balance_front
        if controls.aero_balance_front is None
        else _clip(controls.aero_balance_front, 0.0, 1.0)
    )

    pdx1 = ggv_base.pdx1 * controls.tire_mu_scale
    pdx2 = ggv_base.pdx2 * controls.tire_mu_scale * controls.tire_load_sensitivity_scale
    pdy1 = ggv_base.pdy1 * controls.tire_mu_scale
    pdy2 = ggv_base.pdy2 * controls.tire_mu_scale * controls.tire_load_sensitivity_scale

    ggv = replace(
        ggv_base,
        wheelbase=wheelbase,
        track_front=track_front,
        track_rear=track_rear,
        aero_balance_front=aero_balance,
        pdx1=pdx1,
        pdx2=pdx2,
        pdy1=pdy1,
        pdy2=pdy2,
        max_drive_power=controls.max_drive_power_w,
        brake_distribution_front=controls.brake_front_bias,
    )
    ymd = replace(
        ymd_base,
        wheelbase=wheelbase,
        track_front=track_front,
        track_rear=track_rear,
        aero_balance_front=aero_balance,
        pdy1=pdy1,
        pdy2=pdy2,
        pky1=ymd_base.pky1 * controls.tire_cornering_stiffness_scale,
    )

    summary = dict(projection.summary)
    summary.update(
        {
            "wheelbase_m": wheelbase,
            "track_front_m": track_front,
            "track_rear_m": track_rear,
            "aero_balance_front": aero_balance,
            "pdx1_effective": pdx1,
            "pdx2_effective": pdx2,
            "pdy1_effective": pdy1,
            "pdy2_effective": pdy2,
            "pky1_effective": ymd.pky1,
        }
    )
    return EnvelopeVehicleProjection(ggv=ggv, ymd=ymd, summary=summary)


def _control_summary(controls: EnvelopeControls) -> dict[str, float]:
    return {
        "aero_downforce_scale": controls.aero_downforce_scale,
        "aero_drag_scale": controls.aero_drag_scale,
        "aero_balance_front_override": (
            np.nan if controls.aero_balance_front is None else controls.aero_balance_front
        ),
        "tire_mu_scale": controls.tire_mu_scale,
        "tire_load_sensitivity_scale": controls.tire_load_sensitivity_scale,
        "tire_cornering_stiffness_scale": controls.tire_cornering_stiffness_scale,
        "max_drive_power_w": controls.max_drive_power_w,
        "brake_front_bias": controls.brake_front_bias,
        "wheelbase_scale": controls.wheelbase_scale,
        "track_scale": controls.track_scale,
    }


def _longitudinal_tire_limits(
    vehicle: Any,
    config: GGVConfig,
) -> pd.DataFrame:
    tire_limited_vehicle = replace(
        vehicle,
        max_drive_power=float("inf"),
        max_drive_force=float("inf"),
        max_brake_force=float("inf"),
    )
    drive_grid = np.linspace(
        0.0,
        config.ax_search_max_g * G,
        config.ax_search_points,
    )
    brake_grid = np.linspace(
        config.ax_search_min_g * G,
        0.0,
        config.ax_search_points,
    )

    rows: list[dict[str, float]] = []
    for speed in config.speeds:
        ax_drive = solve_ax_limit(
            tire_limited_vehicle,
            speed=speed,
            ay=0.0,
            ax_grid=drive_grid,
            mode="drive",
        )
        ax_brake = solve_ax_limit(
            tire_limited_vehicle,
            speed=speed,
            ay=0.0,
            ax_grid=brake_grid,
            mode="brake",
        )

        _front_aero, _rear_aero, drag = aero_loads(vehicle, speed)
        drive_force = (
            float(vehicle.mass * ax_drive + drag)
            if np.isfinite(ax_drive)
            else float("nan")
        )
        brake_force = (
            float(abs(vehicle.mass * ax_brake + drag))
            if np.isfinite(ax_brake)
            else float("nan")
        )
        drive_power = drive_force * float(speed)

        rows.append(
            {
                "speed_mps": float(speed),
                "straightline_drive_ax_limit_g": float(ax_drive / G),
                "straightline_brake_ax_limit_g": float(abs(ax_brake) / G),
                "tire_drive_force_limit_n": drive_force,
                "tire_brake_force_limit_n": brake_force,
                "drive_power_required_for_tire_limit_kw": drive_power / 1000.0,
            }
        )

    return pd.DataFrame(rows)


def _nearest_speed_row(df: pd.DataFrame, speed: float) -> pd.Series:
    if df.empty:
        raise ValueError("Cannot select a longitudinal limit from an empty table.")
    distance = (df["speed_mps"] - speed).abs()
    return df.loc[distance.idxmin()]


def _max_feasible_lateral_g(envelope: Any) -> float:
    feasible = np.isfinite(envelope.ax_accel) | np.isfinite(envelope.ax_brake)
    if not np.any(feasible):
        return float("nan")
    return float(np.nanmax(np.abs(envelope.ay[feasible]))) / G


def _load_yaml(path: Path) -> dict[str, Any]:
    with path.open() as f:
        data = yaml.safe_load(f)
    if not isinstance(data, dict):
        raise ValueError(f"Config did not parse as a mapping: {path}")
    return data


def _resolve_vehicle_path(config: dict[str, Any], config_path: Path) -> Path:
    template = config.get("vehicle_template", "../../vehicle.yml")
    path = (config_path.parent / str(template)).resolve()
    if not path.exists():
        raise FileNotFoundError(f"vehicle_template not found: {path}")
    return path


def _baseline_value(
    vehicle_data: dict[str, Any],
    projection: EnvelopeVehicleProjection,
    variable: dict[str, Any],
) -> float:
    if "baseline" in variable:
        return float(variable["baseline"])

    path = str(variable["path"])
    if path == "aero.balance_front":
        return float(projection.summary["aero_balance_front"])
    if path in VEHICLE_PATHS:
        return float(_get_vehicle_value(vehicle_data, path))

    raise ValueError(f"Envelope control {path!r} needs an explicit baseline.")


def _sample_interval_splice(
    variables: list[dict[str, Any]],
    baseline: dict[str, float],
    default_intervals: int,
) -> list[dict[str, float]]:
    variants = [baseline.copy()]
    for var in variables:
        path = str(var["path"])
        baseline_value = baseline[path]
        values = var.get("values")
        if values is None:
            low, high = var["range"]
            intervals = int(var.get("intervals", default_intervals))
            if intervals < 1:
                raise ValueError("intervals must be >= 1")
            values = [
                float(low) + (float(high) - float(low)) * i / intervals
                for i in range(intervals + 1)
            ]

        for value_raw in values:
            value = float(value_raw)
            if abs(value - baseline_value) <= 1e-12:
                continue
            variant = baseline.copy()
            variant[path] = value
            variants.append(variant)
    return variants


def _get_vehicle_value(vehicle_data: dict[str, Any], path: str) -> float:
    parts = _vehicle_path_parts(path)
    current: Any = vehicle_data
    for part in parts:
        if part in AXIS_INDEX:
            current = current[AXIS_INDEX[part]]
        else:
            current = current[part]
    return float(current)


def _set_vehicle_value(vehicle_data: dict[str, Any], path: str, value: float) -> None:
    parts = _vehicle_path_parts(path)
    current: Any = vehicle_data
    for part in parts[:-1]:
        if part in AXIS_INDEX:
            current = current[AXIS_INDEX[part]]
        else:
            current = current[part]

    leaf = parts[-1]
    if leaf in AXIS_INDEX:
        current[AXIS_INDEX[leaf]] = value
    else:
        current[leaf] = value


def _set_control_value(
    controls: EnvelopeControls,
    path: str,
    value: float,
) -> EnvelopeControls:
    if path == "aero.load_scale":
        return replace(
            controls,
            aero_downforce_scale=value,
            aero_drag_scale=value,
        )
    if path == "aero.downforce_scale":
        return replace(controls, aero_downforce_scale=value)
    if path == "aero.drag_scale":
        return replace(controls, aero_drag_scale=value)
    if path == "aero.balance_front":
        return replace(controls, aero_balance_front=value)
    if path == "tire.mu_scale":
        return replace(controls, tire_mu_scale=value)
    if path == "tire.load_sensitivity_scale":
        return replace(controls, tire_load_sensitivity_scale=value)
    if path == "tire.cornering_stiffness_scale":
        return replace(controls, tire_cornering_stiffness_scale=value)
    if path == "power.max_drive_power_kw":
        return replace(controls, max_drive_power_w=1000.0 * value)
    if path == "brake.front_bias":
        return replace(controls, brake_front_bias=value)
    if path == "geometry.wheelbase_scale":
        return replace(controls, wheelbase_scale=value)
    if path == "geometry.track_scale":
        return replace(controls, track_scale=value)
    raise ValueError(f"Unsupported EnvelopeSim control path: {path}")


def _vehicle_path_parts(path: str) -> list[str]:
    aliased = PATH_ALIASES.get(path, path)
    return aliased.split(".")


def _percent_delta(value: float, baseline: float) -> float:
    if abs(baseline) <= 1e-12:
        return float("nan")
    return 100.0 * (value - baseline) / abs(baseline)


def _clip(value: float, low: float, high: float) -> float:
    return min(max(value, low), high)
