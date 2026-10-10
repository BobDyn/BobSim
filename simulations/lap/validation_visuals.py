"""Generate the disposable all-fidelity QSS/transient validation bundle."""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import os
from pathlib import Path
from typing import Any, cast

os.environ.setdefault("MPLBACKEND", "Agg")
os.environ.setdefault("MPLCONFIGDIR", "temp/matplotlib")

import matplotlib.pyplot as plt
import numpy as np

from engines.dynpy import DOFModel, Vehicle
from simulations.lap.core import (
    GGVMap,
    TrackCorridor,
    optimize_racing_line,
    simulate_transient_lap,
    write_qss_lap_csv,
    write_transient_lap_csv,
)
from simulations.lap.core.racing_line import LineMode
from common.plotting.plot_engine import PlotEngine
from common.vehicle_io import load_yaml, repo_root
from simulations.envelope.GGV.ggv_generation import (
    GGVConfig,
    GGVEnvelope,
    generate_ggv,
    plot_ggv,
    plot_ggv_metrics,
    plot_ggv_surface,
    save_ggv_csv,
    solve_lateral_limit,
)
from simulations.envelope.YMD.ymd_generation import (
    YMDConfig,
    YMDResult,
    generate_ymd,
    plot_ymd,
    plot_ymd_beta_slices,
    plot_ymd_contours,
    save_ymd_csv,
)
from simulations.envelope.vehicle_yaml import load_vehicle_yaml, project_vehicle_yaml


DEFAULT_CONFIG = Path(__file__).with_name("lap_validation_config.yml")


def generate_validation_visuals(
    config_path: str | Path = DEFAULT_CONFIG,
    *,
    force: bool = False,
    force_laps: bool = False,
    model_dof: int | None = None,
) -> list[dict[str, Any]]:
    """Validate all configured fidelities and populate the root temp folder."""

    root = repo_root()
    config = load_yaml(config_path)
    output = _root_path(root, config["output_directory"])
    output.mkdir(parents=True, exist_ok=True)
    _write_reference_track_figures(output, root, _mapping(config, "reference_tracks"))
    vehicle_path = _root_path(root, config.get("vehicle", "vehicle.yml"))
    validation_fingerprint = _validation_fingerprint(
        root,
        _root_path(root, config_path),
        vehicle_path,
    )
    vehicle = Vehicle.from_yaml(vehicle_path)
    projected = project_vehicle_yaml(load_vehicle_yaml(vehicle_path))
    track_config = _mapping(config, "track")
    corridor = TrackCorridor.from_csv(_root_path(root, track_config["boundary_csv"]))
    summaries: list[dict[str, Any]] = []

    configured_dofs = tuple(int(value) for value in config.get("model_dofs", (3, 6, 10, 14)))
    selected_dofs = (model_dof,) if model_dof is not None else configured_dofs
    for raw_dof in selected_dofs:
        dof_value = int(raw_dof)
        if dof_value not in {3, 6, 10, 14}:
            raise ValueError(f"Invalid model DOF: {dof_value}.")
        dof = cast(DOFModel, dof_value)
        dof_output = output / f"{dof}dof"
        dof_output.mkdir(parents=True, exist_ok=True)
        summary_path = dof_output / "summary.json"
        cached_current = False
        cached_summary: dict[str, Any] | None = None
        if summary_path.exists() and not force:
            raw_cached_summary = json.loads(summary_path.read_text(encoding="utf-8"))
            cached_summary = raw_cached_summary if isinstance(raw_cached_summary, dict) else None
            cached_current = bool(
                cached_summary is not None
                and cached_summary.get("validation_fingerprint")
                == validation_fingerprint
            )
            if cached_current and not force_laps:
                assert cached_summary is not None
                summaries.append(cached_summary)
                continue
        model = vehicle.model(dof)

        ggv_envelopes = _ggv_results(
            dof_output,
            projected.ggv,
            model,
            dof,
            _mapping(config, "ggv"),
            force=force or not cached_current,
        )
        _write_ggv_figures(dof_output / "envelopes", ggv_envelopes)
        ggv = GGVMap.from_csv(dof_output / "ggv.csv")

        ymd = _ymd_results(
            dof_output,
            projected.ymd,
            model,
            dof,
            _mapping(config, "ymd"),
            force=force or not cached_current,
        )
        _write_ymd_figures(dof_output / "envelopes", ymd)

        lap_config = _mapping(config, "lap")
        optimized = optimize_racing_line(
            corridor,
            ggv,
            mode=cast(LineMode, lap_config.get("line_mode", "minimum_time_qss")),
            vehicle_width_m=float(track_config.get("vehicle_width_m", 1.35)),
            safety_margin_m=float(track_config.get("safety_margin_m", 0.15)),
            sample_step_m=float(track_config.get("sample_step_m", 2.0)),
            curvature_max_iterations=int(
                lap_config.get("curvature_max_iterations", 5)
            ),
            lap_time_max_iterations=int(lap_config.get("lap_time_max_iterations", 3)),
            max_speed_mps=float(lap_config.get("max_speed_mps", 12.0)),
        )
        transient_config = _mapping(config, "transient")
        transient = simulate_transient_lap(
            model,
            optimized.qss_lap,
            sample_period_s=float(transient_config.get("sample_period_s", 0.05)),
            lookahead_m=float(transient_config.get("lookahead_m", 3.0)),
            steering_trim_step_m=float(
                transient_config.get("steering_trim_step_m", 10.0)
            ),
            integration_rtol=float(transient_config.get("integration_rtol", 2e-5)),
            integration_atol=float(transient_config.get("integration_atol", 2e-7)),
        )
        write_qss_lap_csv(dof_output / "qss_lap.csv", optimized.qss_lap)
        write_transient_lap_csv(dof_output / "transient_lap.csv", transient)
        _write_lap_figures(dof_output, corridor, optimized.qss_lap, transient, dof)

        finish = np.flatnonzero(
            transient.unwrapped_progress_m >= optimized.line.track_length_m
        )
        finish_count = int(finish[0] + 1) if finish.size else transient.transient.time_s.size
        clearance = float(
            np.min(
                0.5 * corridor.gate_widths_m
                - 0.5 * float(track_config.get("vehicle_width_m", 1.35))
                - float(track_config.get("safety_margin_m", 0.15))
            )
        )
        summary = {
            "validation_fingerprint": validation_fingerprint,
            "model_dof": dof,
            "qss_converged": optimized.qss_lap.converged,
            "qss_lap_time_s": optimized.qss_lap.lap_time_s,
            "line_optimizer_converged": optimized.success,
            "line_optimizer_message": optimized.message,
            "transient_success": transient.transient.success,
            "transient_completed_lap": transient.completed_lap,
            "transient_lap_time_s": transient.lap_time_s,
            "transient_lap_delta_s": (
                transient.lap_time_s - optimized.qss_lap.lap_time_s
            ),
            "transient_max_abs_lateral_error_m": float(
                np.max(np.abs(transient.lateral_error_m[:finish_count]))
            ),
            "transient_max_abs_heading_error_rad": float(
                np.max(np.abs(transient.heading_error_rad[:finish_count]))
            ),
            "minimum_center_clearance_m": clearance,
            "transient_stayed_in_corridor": bool(
                np.max(np.abs(transient.lateral_error_m[:finish_count])) <= clearance
            ),
            "ymd_converged_fraction": float(np.mean(ymd.converged)),
        }
        summary_path.write_text(
            json.dumps(summary, indent=2, sort_keys=True) + "\n",
            encoding="utf-8",
        )
        summaries.append(summary)

    summary_by_dof: dict[int, dict[str, Any]] = {}
    combined_summary_path = output / "summary.json"
    if combined_summary_path.exists():
        cached = json.loads(combined_summary_path.read_text(encoding="utf-8"))
        if isinstance(cached, list):
            summary_by_dof.update(
                {
                    int(item["model_dof"]): item
                    for item in cached
                    if isinstance(item, dict) and "model_dof" in item
                }
            )
    summary_by_dof.update({int(item["model_dof"]): item for item in summaries})
    combined = [summary_by_dof[dof] for dof in sorted(summary_by_dof)]
    combined_summary_path.write_text(
        json.dumps(combined, indent=2, sort_keys=True) + "\n",
        encoding="utf-8",
    )
    _write_all_fidelity_overlays(output, combined)
    return summaries


def _ggv_results(
    output: Path,
    vehicle: Any,
    model: Any,
    dof: DOFModel,
    config: dict[str, Any],
    *,
    force: bool,
) -> list[GGVEnvelope]:
    path = output / "ggv.csv"
    if path.exists() and not force:
        cached = _load_ggv_envelopes(path)
        if all(_ggv_has_closed_lateral_endpoints(envelope) for envelope in cached):
            return cached
        closed = _close_cached_ggv_endpoints(
            cached,
            projected_vehicle=vehicle,
            model=model,
            config=config,
        )
        save_ggv_csv(closed, path)
        return closed
    generation = GGVConfig(
        speeds=tuple(float(value) for value in config.get("speeds_mps", (6, 12, 18))),
        model_dof=dof,
        ay_max_g=float(config.get("ay_max_g", 2.4)),
        ay_points=int(config.get("ay_points", 9)),
        ax_search_min_g=float(config.get("ax_search_min_g", -3.2)),
        ax_search_max_g=float(config.get("ax_search_max_g", 2.8)),
        ax_search_points=11,
        max_abs_beta_rad=float(config.get("max_abs_beta_rad", 0.25)),
        max_abs_steering_rad=float(config.get("max_abs_steering_rad", 0.5)),
        ax_binary_iterations=int(config.get("ax_binary_iterations", 8)),
        enforce_tire_load_range=bool(config.get("enforce_tire_load_range", True)),
        trim_multistart=bool(config.get("trim_multistart", True)),
        verbose=True,
        progress_every=3,
        warn_tire_load_range=False,
    )
    envelopes = generate_ggv(vehicle, generation, reduced_model=model)
    save_ggv_csv(envelopes, path)
    return envelopes


def _ggv_has_closed_lateral_endpoints(envelope: GGVEnvelope) -> bool:
    finite = np.isfinite(envelope.ax_accel) & np.isfinite(envelope.ax_brake)
    if np.count_nonzero(finite) < 3:
        return False
    accel = envelope.ax_accel[finite]
    brake = envelope.ax_brake[finite]
    return bool(
        np.isclose(accel[0], brake[0], atol=1e-8)
        and np.isclose(accel[-1], brake[-1], atol=1e-8)
    )


def _close_cached_ggv_endpoints(
    envelopes: list[GGVEnvelope],
    *,
    projected_vehicle: Any,
    model: Any,
    config: dict[str, Any],
) -> list[GGVEnvelope]:
    """Upgrade a zero-yaw cached sweep with its exact coast/lateral endpoints."""

    closed: list[GGVEnvelope] = []
    ay_upper = float(config.get("ay_max_g", 2.4)) * 9.80665
    for envelope in envelopes:
        lateral_limit, coast_ax = solve_lateral_limit(
            projected_vehicle,
            speed=envelope.speed,
            ay_upper=ay_upper,
            reduced_model=model,
            max_abs_beta_rad=float(config.get("max_abs_beta_rad", 0.25)),
            max_abs_steering_rad=float(config.get("max_abs_steering_rad", 0.5)),
            binary_iterations=int(config.get("ax_binary_iterations", 8)),
            enforce_tire_load_range=bool(
                config.get("enforce_tire_load_range", True)
            ),
            trim_multistart=bool(config.get("trim_multistart", True)),
        )
        positive = (
            (envelope.ay >= 0.0)
            & (envelope.ay < lateral_limit - 1e-9)
            & np.isfinite(envelope.ax_accel)
            & np.isfinite(envelope.ax_brake)
        )
        ay = np.concatenate((envelope.ay[positive], [lateral_limit]))
        accel = np.concatenate((envelope.ax_accel[positive], [coast_ax]))
        brake = np.concatenate((envelope.ax_brake[positive], [coast_ax]))
        closed.append(
            GGVEnvelope(
                speed=envelope.speed,
                ay=np.concatenate((-ay[:0:-1], ay)),
                ax_accel=np.concatenate((accel[:0:-1], accel)),
                ax_brake=np.concatenate((brake[:0:-1], brake)),
            )
        )
    return closed


def _ymd_results(
    output: Path,
    vehicle: Any,
    model: Any,
    dof: DOFModel,
    config: dict[str, Any],
    *,
    force: bool,
) -> YMDResult:
    path = output / "ymd.csv"
    if path.exists() and not force:
        return _load_ymd(path)
    generation = YMDConfig(
        speed=float(config.get("speed_mps", 12.0)),
        model_dof=dof,
        beta_min_deg=float(config.get("beta_min_deg", -8.0)),
        beta_max_deg=float(config.get("beta_max_deg", 8.0)),
        beta_points=int(config.get("beta_points", 9)),
        hwa_min_deg=float(config.get("roadwheel_min_deg", -12.0)),
        hwa_max_deg=float(config.get("roadwheel_max_deg", 12.0)),
        hwa_points=int(config.get("roadwheel_points", 9)),
        enforce_tire_load_range=bool(config.get("enforce_tire_load_range", True)),
        verbose=True,
        warn_tire_load_range=False,
    )
    result = generate_ymd(vehicle, generation, reduced_model=model)
    save_ymd_csv(result, path)
    return result


def _write_ggv_figures(output: Path, envelopes: list[GGVEnvelope]) -> None:
    output.mkdir(parents=True, exist_ok=True)
    plot_ggv(envelopes, output / "ggv_2d.png")
    plot_ggv_surface(envelopes, output / "ggv_3d.png")
    plot_ggv_metrics(envelopes, output / "ggv_metrics.png")
    plt.close("all")


def _write_ymd_figures(output: Path, result: YMDResult) -> None:
    output.mkdir(parents=True, exist_ok=True)
    plot_ymd(result, output / "ymd_wireframe.png")
    plot_ymd_beta_slices(result, output / "ymd_beta_slices.png")
    plot_ymd_contours(result, output / "ymd_contours.png")
    plt.close("all")


def _write_lap_figures(output: Path, corridor: TrackCorridor, qss: Any, transient: Any, dof: DOFModel) -> None:
    finish = np.flatnonzero(transient.unwrapped_progress_m >= qss.line.track_length_m)
    count = int(finish[0] + 1) if finish.size else transient.transient.time_s.size
    state = transient.transient.signals
    series: dict[str, Any] = {
        "left_x": np.append(corridor.left_boundary_m[:, 0], corridor.left_boundary_m[0, 0]),
        "left_y": np.append(corridor.left_boundary_m[:, 1], corridor.left_boundary_m[0, 1]),
        "right_x": np.append(corridor.right_boundary_m[:, 0], corridor.right_boundary_m[0, 0]),
        "right_y": np.append(corridor.right_boundary_m[:, 1], corridor.right_boundary_m[0, 1]),
        "qss_x": np.append(qss.line.x_m, qss.line.x_m[0]),
        "qss_y": np.append(qss.line.y_m, qss.line.y_m[0]),
        "transient_x": transient.transient.state[:count, 0],
        "transient_y": transient.transient.state[:count, 1],
        "qss_station": qss.line.station_m,
        "qss_speed": qss.speed_mps,
        "qss_ax": qss.longitudinal_acceleration_mps2,
        "qss_ay": qss.lateral_acceleration_mps2,
        "curvature": qss.line.curvature_per_m,
        "time": transient.transient.time_s[:count],
        "station": transient.station_m[:count],
        "progress": transient.unwrapped_progress_m[:count],
        "target_speed": transient.target_speed_mps[:count],
        "speed": np.hypot(state["velX"][:count], state["velY"][:count]),
        "lateral_error": transient.lateral_error_m[:count],
        "heading_error": transient.heading_error_rad[:count],
        "yaw_rate": state["yawVel"][:count],
        "steering": state["handwheelAngle"][:count],
        "ax": state["accX"][:count],
        "ay": state["accY"][:count],
    }
    for name in (
        "z",
        "roll",
        "pitch",
        "wheel_speed_fl",
        "wheel_speed_fr",
        "wheel_speed_rl",
        "wheel_speed_rr",
        "unsprung_z_fl",
        "unsprung_z_fr",
        "unsprung_z_rl",
        "unsprung_z_rr",
    ):
        if name in state:
            series[name] = state[name][:count]
    for corner in ("FL", "FR", "RL", "RR"):
        for prefix in (
            "jounce",
            "jounceVel",
            "camber",
            "toe",
            "caster",
            "kpi",
            "mechanicalTrail",
            "scrubRadius",
            "instantLinkLongitudinal",
            "instantLinkLateral",
        ):
            name = f"{prefix}{corner}"
            if name in state:
                series[name] = state[name][:count]

    qss_plots = {
        "qss_racing_line": _spatial_page("QSS racing line"),
        "qss_profiles": {
            "layout": "quad",
            "title": f"{dof}DOF QSS profiles",
            "subplots": (
                _signal("Speed", "qss_station", "Station (m)", "qss_speed", "Speed (m/s)"),
                _signal("Longitudinal acceleration", "qss_station", "Station (m)", "qss_ax", "ax (m/s²)"),
                _signal("Lateral acceleration", "qss_station", "Station (m)", "qss_ay", "ay (m/s²)"),
                _signal("Curvature", "qss_station", "Station (m)", "curvature", "Curvature (1/m)"),
            ),
        },
    }
    transient_plots: dict[str, Any] = {
        "transient_path": _spatial_page("QSS reference and transient path", include_transient=True),
        "transient_tracking": {
            "layout": "quad",
            "title": f"{dof}DOF transient tracking",
            "subplots": (
                _signal(
                    "Speed tracking",
                    "time",
                    "Time (s)",
                    "speed",
                    "Speed (m/s)",
                    overlay=("target_speed", "QSS target"),
                ),
                _signal("Lateral error", "time", "Time (s)", "lateral_error", "Error (m)"),
                _signal("Heading error", "time", "Time (s)", "heading_error", "Error (rad)"),
                _signal("Lap progress", "time", "Time (s)", "progress", "Progress (m)"),
            ),
        },
        "transient_dynamics": {
            "layout": "quad",
            "title": f"{dof}DOF transient dynamics",
            "subplots": (
                _signal("Yaw rate", "time", "Time (s)", "yaw_rate", "Yaw rate (rad/s)"),
                _signal("Roadwheel steer", "time", "Time (s)", "steering", "Steer (rad)"),
                _signal("Longitudinal acceleration", "time", "Time (s)", "ax", "ax (m/s²)"),
                _signal("Lateral acceleration", "time", "Time (s)", "ay", "ay (m/s²)"),
            ),
        },
        "qss_transient_speed": {
            "layout": "single",
            "title": f"{dof}DOF QSS vs transient velocity profile",
            "x": {"key": "qss_station", "label": "Station (m)"},
            "y": {"key": "qss_speed", "label": "Speed (m/s)"},
            "label": "QSS",
            "overlay": {
                "x": {"key": "progress", "label": "Station (m)"},
                "y": {"key": "speed", "label": "Speed (m/s)"},
                "label": "Transient",
            },
        },
    }
    if dof >= 6:
        transient_plots["transient_body_attitude"] = {
            "layout": "quad",
            "title": f"{dof}DOF body attitude",
            "subplots": (
                _signal("Heave", "time", "Time (s)", "z", "z (m)"),
                _signal("Roll", "time", "Time (s)", "roll", "Roll (rad)"),
                _signal("Pitch", "time", "Time (s)", "pitch", "Pitch (rad)"),
                _signal("Yaw rate", "time", "Time (s)", "yaw_rate", "Yaw rate (rad/s)"),
            ),
        }
        transient_plots["transient_suspension_jounce"] = {
            "layout": "quad",
            "title": f"{dof}DOF suspension jounce",
            "subplots": tuple(
                _signal(corner, "time", "Time (s)", f"jounce{corner}", "Jounce (m)")
                for corner in ("FL", "FR", "RL", "RR")
            ),
        }
        transient_plots["transient_suspension_jounce_rate"] = {
            "layout": "quad",
            "title": f"{dof}DOF suspension jounce rate",
            "subplots": tuple(
                _signal(
                    corner,
                    "time",
                    "Time (s)",
                    f"jounceVel{corner}",
                    "Jounce rate (m/s)",
                )
                for corner in ("FL", "FR", "RL", "RR")
            ),
        }
        transient_plots["transient_wheel_kinematics"] = {
            "layout": "quad",
            "title": f"{dof}DOF wheel attitude from suspension kinematics",
            "subplots": tuple(
                _signal(
                    corner,
                    "time",
                    "Time (s)",
                    f"camber{corner}",
                    "Angle (rad)",
                    overlay=(f"toe{corner}", "Toe"),
                    label="Camber",
                )
                for corner in ("FL", "FR", "RL", "RR")
            ),
        }
    if dof >= 10:
        transient_plots["transient_wheel_speeds"] = {
            "layout": "quad",
            "title": f"{dof}DOF wheel speeds",
            "subplots": tuple(
                _signal(name.upper(), "time", "Time (s)", f"wheel_speed_{name}", "Wheel speed (rad/s)")
                for name in ("fl", "fr", "rl", "rr")
            ),
        }
    if dof == 14:
        transient_plots["transient_unsprung_motion"] = {
            "layout": "quad",
            "title": "14DOF unsprung vertical motion",
            "subplots": tuple(
                _signal(name.upper(), "time", "Time (s)", f"unsprung_z_{name}", "z (m)")
                for name in ("fl", "fr", "rl", "rr")
            ),
        }
    PlotEngine({"plots": qss_plots}).save_pngs({"series": series}, output / "qss")
    PlotEngine({"plots": transient_plots}).save_pngs(
        {"series": series},
        output / "transient",
    )
    plt.close("all")


def _write_all_fidelity_overlays(
    output: Path,
    summaries: list[dict[str, Any]],
) -> None:
    """Overlay every completed model so fidelity changes are visible directly."""

    dofs = tuple(
        dof
        for dof in (3, 6, 10, 14)
        if (output / f"{dof}dof" / "ggv.csv").exists()
        and (output / f"{dof}dof" / "qss_lap.csv").exists()
        and (output / f"{dof}dof" / "transient_lap.csv").exists()
    )
    if len(dofs) < 2:
        return

    series: dict[str, Any] = {}
    ggv_items: list[dict[str, Any]] = []
    qss_items: list[dict[str, Any]] = []
    transient_speed_items: list[dict[str, Any]] = []
    transient_yaw_items: list[dict[str, Any]] = []
    model_colors = {3: "#1f77b4", 6: "#ff7f0e", 10: "#2ca02c", 14: "#d62728"}
    for dof in dofs:
        label = f"{dof}DOF"
        prefix = f"dof{dof}"
        ggv = _load_ggv_envelopes(output / f"{dof}dof" / "ggv.csv")
        envelope = min(ggv, key=lambda item: abs(item.speed - 12.0))
        for branch, values, linestyle in (
            ("accel", envelope.ax_accel, "-"),
            ("brake", envelope.ax_brake, "--"),
        ):
            x_key = f"{prefix}_{branch}_ay"
            y_key = f"{prefix}_{branch}_ax"
            series[x_key] = envelope.ay / 9.80665
            series[y_key] = values / 9.80665
            ggv_items.append(
                _plot_item(
                    x_key,
                    y_key,
                    f"{label} {branch}",
                    "Lateral acceleration (g)",
                    "Longitudinal acceleration (g)",
                    linestyle=linestyle,
                    color=model_colors[dof],
                )
            )

        qss = _read_numeric_csv(output / f"{dof}dof" / "qss_lap.csv")
        series[f"{prefix}_qss_station"] = qss["station_m"]
        series[f"{prefix}_qss_speed"] = qss["speed_mps"]
        qss_items.append(
            _plot_item(
                f"{prefix}_qss_station",
                f"{prefix}_qss_speed",
                label,
                "Station (m)",
                "Speed (m/s)",
                color=model_colors[dof],
            )
        )

        transient = _read_numeric_csv(output / f"{dof}dof" / "transient_lap.csv")
        series[f"{prefix}_progress"] = transient["progress_m"]
        series[f"{prefix}_speed"] = transient["speed_mps"]
        series[f"{prefix}_time"] = transient["time_s"]
        series[f"{prefix}_yaw"] = transient["yaw_rate_radps"]
        transient_speed_items.append(
            _plot_item(
                f"{prefix}_progress",
                f"{prefix}_speed",
                label,
                "Progress (m)",
                "Speed (m/s)",
                color=model_colors[dof],
            )
        )
        transient_yaw_items.append(
            _plot_item(
                f"{prefix}_time",
                f"{prefix}_yaw",
                label,
                "Time (s)",
                "Yaw rate (rad/s)",
                color=model_colors[dof],
            )
        )

    completed = {
        int(item["model_dof"]): item
        for item in summaries
        if int(item.get("model_dof", -1)) in dofs
    }
    lap_dofs = np.asarray(sorted(completed), dtype=float)
    series["lap_dof"] = lap_dofs
    series["qss_lap_time"] = np.asarray(
        [completed[int(dof)]["qss_lap_time_s"] for dof in lap_dofs]
    )
    series["transient_lap_time"] = np.asarray(
        [completed[int(dof)]["transient_lap_time_s"] for dof in lap_dofs]
    )
    lap_items = [
        _plot_item(
            "lap_dof",
            "qss_lap_time",
            "QSS",
            "Model DOF",
            "Lap time (s)",
        ),
        _plot_item(
            "lap_dof",
            "transient_lap_time",
            "Transient",
            "Model DOF",
            "Lap time (s)",
            linestyle="--",
        ),
    ]
    plots = {
        "ggv_fidelity_overlay_12mps": _single_overlay_page(
            "GGV fidelity overlay at 12 m/s", ggv_items
        ),
        "qss_speed_fidelity_overlay": _single_overlay_page(
            "Endurance QSS speed profiles", qss_items
        ),
        "transient_speed_fidelity_overlay": _single_overlay_page(
            "Endurance transient speed profiles", transient_speed_items
        ),
        "transient_yaw_fidelity_overlay": _single_overlay_page(
            "Endurance transient yaw-rate profiles", transient_yaw_items
        ),
        "lap_time_fidelity_overlay": _single_overlay_page(
            "Endurance lap time by fidelity", lap_items
        ),
    }
    PlotEngine({"plots": plots}).save_pngs(
        {"series": series}, output / "overlays"
    )
    plt.close("all")


def _write_reference_track_figures(
    output: Path,
    root: Path,
    tracks: dict[str, Any],
) -> None:
    """Keep real and compact validation course outlines visible side by side."""

    plots: dict[str, Any] = {}
    series: dict[str, Any] = {}
    for name, raw_path in tracks.items():
        corridor = TrackCorridor.from_csv(_root_path(root, raw_path))
        prefix = str(name)
        series[f"{prefix}_left_x"] = np.append(
            corridor.left_boundary_m[:, 0], corridor.left_boundary_m[0, 0]
        )
        series[f"{prefix}_left_y"] = np.append(
            corridor.left_boundary_m[:, 1], corridor.left_boundary_m[0, 1]
        )
        series[f"{prefix}_right_x"] = np.append(
            corridor.right_boundary_m[:, 0], corridor.right_boundary_m[0, 0]
        )
        series[f"{prefix}_right_y"] = np.append(
            corridor.right_boundary_m[:, 1], corridor.right_boundary_m[0, 1]
        )
        plots[prefix] = {
            "layout": "single",
            "title": f"Reference track: {str(name).replace('_', ' ')}",
            "x": {"key": f"{prefix}_left_x", "label": "x (m)"},
            "y": {"key": f"{prefix}_left_y", "label": "y (m)"},
            "label": "Outer / left boundary",
            "overlay": {
                "x": {"key": f"{prefix}_right_x", "label": "x (m)"},
                "y": {"key": f"{prefix}_right_y", "label": "y (m)"},
                "label": "Inner / right boundary",
            },
        }
    if plots:
        PlotEngine({"plots": plots}).save_pngs(
            {"series": series}, output / "reference_tracks"
        )
        plt.close("all")


def _plot_item(
    x_key: str,
    y_key: str,
    label: str,
    x_label: str,
    y_label: str,
    *,
    linestyle: str = "-",
    color: str | None = None,
) -> dict[str, Any]:
    result: dict[str, Any] = {
        "x": {"key": x_key, "label": x_label},
        "y": {"key": y_key, "label": y_label},
        "label": label,
        "linestyle": linestyle,
    }
    if color is not None:
        result["color"] = color
    return result


def _single_overlay_page(title: str, items: list[dict[str, Any]]) -> dict[str, Any]:
    first, *overlays = items
    return {"layout": "single", "title": title, **first, "overlay": overlays}


def _read_numeric_csv(path: Path) -> dict[str, np.ndarray[Any, np.dtype[np.float64]]]:
    with path.open(newline="", encoding="utf-8") as handle:
        rows = list(csv.DictReader(handle))
    if not rows:
        raise ValueError(f"CSV contains no rows: {path}")
    return {
        name: np.asarray([float(row[name]) for row in rows], dtype=float)
        for name in rows[0]
    }


def _spatial_page(title: str, *, include_transient: bool = False) -> dict[str, Any]:
    overlays = [
        _overlay("right_x", "right_y", "Right boundary"),
        _overlay("qss_x", "qss_y", "QSS line"),
    ]
    if include_transient:
        overlays.append(_overlay("transient_x", "transient_y", "Transient"))
    return {
        "layout": "single",
        "title": title,
        "x": {"key": "left_x", "label": "x (m)"},
        "y": {"key": "left_y", "label": "y (m)"},
        "label": "Left boundary",
        "overlay": overlays,
    }


def _signal(
    title: str,
    x_key: str,
    x_label: str,
    y_key: str,
    y_label: str,
    *,
    overlay: tuple[str, str] | None = None,
    label: str = "Transient",
) -> dict[str, Any]:
    result: dict[str, Any] = {
        "title": title,
        "x": {"key": x_key, "label": x_label},
        "y": {"key": y_key, "label": y_label},
    }
    if overlay is not None:
        result["label"] = label
        result["overlay"] = {
            "x": {"key": x_key, "label": x_label},
            "y": {"key": overlay[0], "label": y_label},
            "label": overlay[1],
        }
    return result


def _overlay(x_key: str, y_key: str, label: str) -> dict[str, Any]:
    return {
        "x": {"key": x_key},
        "y": {"key": y_key},
        "label": label,
    }


def _load_ggv_envelopes(path: Path) -> list[GGVEnvelope]:
    rows: dict[float, list[tuple[float, float, float]]] = {}
    with path.open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            speed = float(row["speed_mps"])
            rows.setdefault(speed, []).append(
                (
                    float(row["ay_mps2"]),
                    float(row["ax_accel_mps2"]),
                    float(row["ax_brake_mps2"]),
                )
            )
    return [
        GGVEnvelope(
            speed=speed,
            ay=np.asarray([item[0] for item in values]),
            ax_accel=np.asarray([item[1] for item in values]),
            ax_brake=np.asarray([item[2] for item in values]),
        )
        for speed, values in sorted(rows.items())
    ]


def _load_ymd(path: Path) -> YMDResult:
    with path.open(newline="", encoding="utf-8") as handle:
        rows = list(csv.DictReader(handle))
    speed = float(rows[0]["speed_mps"])
    beta = np.asarray(sorted({float(row["beta_rad"]) for row in rows}))
    hwa = np.asarray(sorted({float(row["hwa_rad"]) for row in rows}))
    ay = np.full((beta.size, hwa.size), np.nan)
    mz = np.full_like(ay, np.nan)
    converged = np.zeros_like(ay, dtype=bool)
    beta_index = {value: index for index, value in enumerate(beta)}
    hwa_index = {value: index for index, value in enumerate(hwa)}
    for row in rows:
        i = beta_index[float(row["beta_rad"])]
        j = hwa_index[float(row["hwa_rad"])]
        ay[i, j] = float(row["ay_mps2"])
        mz[i, j] = float(row["mz_nm"])
        converged[i, j] = bool(int(float(row["converged"])))
    return YMDResult(speed, beta, hwa, ay, mz, converged)


def _mapping(config: dict[str, Any], key: str) -> dict[str, Any]:
    value = config.get(key, {})
    if not isinstance(value, dict):
        raise ValueError(f"Config section {key!r} must be a mapping.")
    return value


def _root_path(root: Path, value: Any) -> Path:
    path = Path(str(value))
    return path if path.is_absolute() else root / path


def _validation_fingerprint(
    root: Path,
    config_path: Path,
    vehicle_path: Path,
) -> str:
    """Hash every input that can change the disposable validation bundle."""

    inputs = [config_path, vehicle_path]
    for directory in (
        root / "engines/dynpy",
        root / "engines/kinpy",
        root / "simulations/lap/core",
    ):
        inputs.extend(sorted(directory.glob("*.py")))
    inputs.extend(
        (
            root / "simulations/envelope/GGV/ggv_generation.py",
            root / "simulations/envelope/YMD/ymd_generation.py",
            Path(__file__),
        )
    )
    digest = hashlib.sha256()
    for path in sorted({item.resolve() for item in inputs}, key=lambda item: item.as_posix()):
        try:
            label = path.relative_to(root).as_posix()
        except ValueError:
            label = path.as_posix()
        digest.update(label.encode("utf-8"))
        digest.update(b"\0")
        digest.update(path.read_bytes())
        digest.update(b"\0")
    return digest.hexdigest()


def _parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--config", type=Path, default=DEFAULT_CONFIG)
    parser.add_argument("--force", action="store_true")
    parser.add_argument("--force-laps", action="store_true")
    parser.add_argument("--model-dof", type=int, choices=(3, 6, 10, 14))
    return parser.parse_args()


def main() -> None:
    args = _parse_args()
    summaries = generate_validation_visuals(
        args.config,
        force=args.force,
        force_laps=args.force_laps,
        model_dof=args.model_dof,
    )
    print(json.dumps(summaries, indent=2, sort_keys=True))


if __name__ == "__main__":
    main()
