"""Run QSS racing-line optimization and/or a dyn_py forward-transient lap."""

from __future__ import annotations

import argparse
from dataclasses import replace
import hashlib
import json
from pathlib import Path
from typing import Any, Literal, cast

import numpy as np

from _0_Utils.dyn_py import DOFModel, Vehicle, VehicleDynamicsSystem
from _0_Utils.lap_sim import (
    GGVMap,
    TrackCorridor,
    optimize_racing_line,
    simulate_transient_lap,
    write_qss_lap_csv,
    write_transient_lap_csv,
)
from _0_Utils.lap_sim.racing_line import LineMode
from _0_Utils.vehicle_io import load_yaml, repo_root, tire_template_name, tire_templates_root


DEFAULT_CONFIG = Path(__file__).with_name("lap_time_eval_config.yml")
Scenario = Literal["qss", "transient", "both"]


def run_lap_time_evaluation(
    config_path: str | Path = DEFAULT_CONFIG,
    *,
    scenario: Scenario = "both",
    model_dof_override: int | None = None,
) -> dict[str, Any]:
    """Run both scenarios on one shared optimized line and return summary metrics."""

    root = repo_root()
    config = load_yaml(Path(config_path))
    track_config = _mapping(config, "track")
    event_config = _mapping(config, "event")
    line_config = _mapping(config, "racing_line")
    qss_config = _mapping(config, "qss")
    transient_config = _mapping(config, "transient")
    output_config = _mapping(config, "output")

    model_dof_value = int(
        model_dof_override
        if model_dof_override is not None
        else config.get("model_dof", 3)
    )
    if model_dof_value not in {3, 6, 10, 14}:
        raise ValueError("model_dof must be 3, 6, 10, or 14.")
    model_dof = cast(DOFModel, model_dof_value)
    format_values = {"model_dof": model_dof_value}
    vehicle_path = _root_path(root, config.get("vehicle", "vehicle.yml"))
    vehicle = Vehicle.from_yaml(vehicle_path)
    configured_power_limit = event_config.get("drive_power_limit_w")
    if configured_power_limit is not None:
        vehicle = vehicle.with_power_limit(float(configured_power_limit))
    track_path = _root_path(root, track_config["boundary_csv"])
    ggv_path = _root_path(
        root,
        str(qss_config["ggv_csv"]).format_map(format_values),
    )
    output_directory = _root_path(
        root,
        str(output_config["directory"]).format_map(format_values),
    )
    if model_dof_override is not None and "{model_dof}" not in str(
        output_config["directory"]
    ):
        output_directory /= f"{model_dof_value}dof"
    output_directory.mkdir(parents=True, exist_ok=True)
    ggv, ggv_provenance = _load_or_generate_ggv(
        ggv_path,
        vehicle_path=vehicle_path,
        model_dof=model_dof,
        model=vehicle.model(model_dof),
        qss_config=qss_config,
        effective_power_limit_w=vehicle.parameters.peak_drive_power_w,
    )
    corridor = TrackCorridor.from_csv(track_path)
    line_mode = cast(LineMode, str(line_config.get("mode", "minimum_time_qss")))
    optimized = optimize_racing_line(
        corridor,
        ggv,
        mode=line_mode,
        vehicle_width_m=float(track_config.get("vehicle_width_m", 1.35)),
        safety_margin_m=float(track_config.get("safety_margin_m", 0.1)),
        sample_step_m=float(track_config.get("sample_step_m", 1.0)),
        curvature_max_iterations=int(line_config.get("curvature_max_iterations", 30)),
        lap_time_max_iterations=int(line_config.get("lap_time_max_iterations", 25)),
        max_speed_mps=(
            float(qss_config["max_speed_mps"])
            if qss_config.get("max_speed_mps") is not None
            else None
        ),
    )
    write_qss_lap_csv(output_directory / "qss_lap.csv", optimized.qss_lap)
    summary: dict[str, Any] = {
        "scenario": scenario,
        "model_dof": model_dof,
        "event": str(event_config.get("name", "unspecified")),
        "effective_drive_power_limit_w": vehicle.parameters.peak_drive_power_w,
        "ggv_csv": _display_path(ggv_path, root),
        "ggv_provenance": ggv_provenance,
        "line_mode": line_mode,
        "track_length_m": optimized.line.track_length_m,
        "centerline_qss_lap_time_s": optimized.centerline_lap_time_s,
        "minimum_curvature_qss_lap_time_s": optimized.minimum_curvature_lap_time_s,
        "optimized_qss_lap_time_s": optimized.qss_lap.lap_time_s,
        "qss_converged": optimized.qss_lap.converged,
        "line_optimizer_converged": optimized.success,
        "line_optimizer_message": optimized.message,
        "line_optimizer_iterations": optimized.iterations,
        "study_scope": _study_scope_summary(vehicle, model_dof, qss_config),
    }
    if scenario in {"transient", "both"}:
        transient = simulate_transient_lap(
            vehicle.model(model_dof),
            optimized.qss_lap,
            sample_period_s=float(transient_config.get("sample_period_s", 0.02)),
            lookahead_m=float(transient_config.get("lookahead_m", 5.0)),
            steering_trim_step_m=float(
                transient_config.get("steering_trim_step_m", 5.0)
            ),
        )
        write_transient_lap_csv(output_directory / "transient_lap.csv", transient)
        if transient.completed_lap:
            finish_index = int(
                np.flatnonzero(
                    transient.unwrapped_progress_m >= optimized.line.track_length_m
                )[0]
            ) + 1
        else:
            finish_index = transient.transient.time_s.size
        summary.update(
            {
                "transient_success": transient.transient.success,
                "transient_completed_lap": transient.completed_lap,
                "transient_lap_time_s": transient.lap_time_s,
                "transient_lap_delta_s": transient.lap_time_s - optimized.qss_lap.lap_time_s,
                "transient_max_abs_lateral_error_m": float(
                    np.max(np.abs(transient.lateral_error_m[:finish_index]))
                ),
                "transient_max_abs_heading_error_rad": float(
                    np.max(np.abs(transient.heading_error_rad[:finish_index]))
                ),
            }
        )
    summary_path = output_directory / "summary.json"
    summary_path.write_text(json.dumps(summary, indent=2, sort_keys=True) + "\n", encoding="utf-8")
    return summary


def _load_or_generate_ggv(
    path: Path,
    *,
    vehicle_path: Path,
    model_dof: DOFModel,
    model: VehicleDynamicsSystem,
    qss_config: dict[str, Any],
    effective_power_limit_w: float,
) -> tuple[GGVMap, dict[str, Any]]:
    expected_provenance = _ggv_provenance(
        vehicle_path=vehicle_path,
        model_dof=model_dof,
        qss_config=qss_config,
        effective_power_limit_w=effective_power_limit_w,
    )
    metadata_path = path.with_suffix(path.suffix + ".metadata.json")
    if path.exists():
        if not bool(qss_config.get("generate_if_missing", True)):
            return GGVMap.from_csv(path), {
                "status": "supplied_unverified",
                "fingerprint": None,
            }
        if metadata_path.exists():
            try:
                raw = json.loads(metadata_path.read_text(encoding="utf-8"))
            except (OSError, json.JSONDecodeError):
                raw = None
            if isinstance(raw, dict) and raw.get("fingerprint") == expected_provenance["fingerprint"]:
                return GGVMap.from_csv(path), {**raw, "status": "verified_cache"}
    if not bool(qss_config.get("generate_if_missing", True)):
        raise FileNotFoundError(
            f"GGV CSV does not exist: {path}. Run make envelope-ggv or enable generation."
        )

    # This layer may compose EnvelopeSim and dyn_py; neither lower layer imports it.
    from _2_EnvelopeSim.GGV.ggv_generation import GGVConfig, generate_ggv, save_ggv_csv
    from _2_EnvelopeSim.vehicle_yaml import load_vehicle_yaml, project_vehicle_yaml

    ggv_vehicle = project_vehicle_yaml(load_vehicle_yaml(vehicle_path)).ggv
    ggv_vehicle = replace(
        ggv_vehicle,
        max_drive_power=min(ggv_vehicle.max_drive_power, effective_power_limit_w),
    )
    generation = GGVConfig(
        speeds=tuple(float(value) for value in qss_config.get("speeds_mps", (5, 10, 15, 20, 25))),
        model_dof=model_dof,
        ay_max_g=float(qss_config.get("ay_max_g", 4.0)),
        ay_points=int(qss_config.get("ay_points", 21)),
        ax_search_min_g=float(qss_config.get("ax_search_min_g", -3.2)),
        ax_search_max_g=float(qss_config.get("ax_search_max_g", 2.8)),
        ax_search_points=21,
        max_abs_beta_rad=float(qss_config.get("max_abs_beta_rad", 0.25)),
        max_abs_steering_rad=float(qss_config.get("max_abs_steering_rad", 0.5)),
        ax_binary_iterations=int(qss_config.get("ax_binary_iterations", 14)),
        enforce_tire_load_range=bool(qss_config.get("enforce_tire_load_range", True)),
        trim_multistart=bool(qss_config.get("trim_multistart", True)),
        verbose=True,
        progress_every=5,
        warn_tire_load_range=False,
    )
    envelopes = generate_ggv(ggv_vehicle, generation, reduced_model=model)
    path.parent.mkdir(parents=True, exist_ok=True)
    save_ggv_csv(envelopes, path)
    metadata_path.write_text(
        json.dumps(expected_provenance, indent=2, sort_keys=True) + "\n",
        encoding="utf-8",
    )
    return GGVMap.from_csv(path), {**expected_provenance, "status": "generated"}


def _ggv_provenance(
    *,
    vehicle_path: Path,
    model_dof: DOFModel,
    qss_config: dict[str, Any],
    effective_power_limit_w: float,
) -> dict[str, Any]:
    root = repo_root()
    physics_digest = hashlib.sha256()
    physics_inputs = [
        Path(__file__),
        root / "_2_EnvelopeSim/GGV/ggv_generation.py",
        root / "_2_EnvelopeSim/vehicle_yaml.py",
        root / "_0_Utils/vehicle_io.py",
        *sorted((root / "_0_Utils/dyn_py").rglob("*.py")),
        *sorted((root / "_0_Utils/kin_py").rglob("*.py")),
    ]
    for source in physics_inputs:
        physics_digest.update(source.relative_to(root).as_posix().encode("utf-8"))
        physics_digest.update(b"\0")
        physics_digest.update(source.read_bytes())
        physics_digest.update(b"\0")
    vehicle_data = load_yaml(vehicle_path)
    tire_root = tire_templates_root(vehicle_data)
    tire_paths = {
        tire_root / f"{tire_template_name(vehicle_data, vehicle_data[side])}.tir"
        for side in ("front", "rear")
    }
    # Both the reduced model and envelope projection have consumed FourPost
    # metrics. Track absence too: creating/removing a report changes fallback
    # behavior. The projection also reads the repository baseline vehicle.
    optional_inputs = [
        root / "vehicle.yml",
        root / "_3_StandardSim/generated_results/four_post_eval_report_metrics.csv",
        root / "_3_StandardSim/results/four_post_eval_report_metrics.csv",
    ]
    input_hashes = {}
    for source in sorted(tire_paths) + optional_inputs:
        key = source.relative_to(root).as_posix() if source.is_relative_to(root) else source.as_posix()
        input_hashes[key] = (
            hashlib.sha256(source.read_bytes()).hexdigest()
            if source in tire_paths or source.is_file() else "missing"
        )
    settings = {
        key: qss_config.get(key)
        for key in (
            "speeds_mps",
            "ay_max_g",
            "ay_points",
            "ax_search_min_g",
            "ax_search_max_g",
            "max_abs_beta_rad",
            "max_abs_steering_rad",
            "ax_binary_iterations",
            "enforce_tire_load_range",
            "trim_multistart",
        )
    }
    payload = {
        "schema": "bobsim.ggv-provenance.v2",
        "model_dof": int(model_dof),
        "effective_drive_power_limit_w": float(effective_power_limit_w),
        "settings": settings,
        "vehicle_sha256": hashlib.sha256(vehicle_path.read_bytes()).hexdigest(),
        "physics_sha256": physics_digest.hexdigest(),
        "input_sha256": input_hashes,
    }
    encoded = json.dumps(payload, sort_keys=True, separators=(",", ":")).encode("utf-8")
    return {**payload, "fingerprint": hashlib.sha256(encoded).hexdigest()}


def _study_scope_summary(
    vehicle: Vehicle,
    model_dof: DOFModel,
    qss_config: dict[str, Any],
) -> dict[str, Any]:
    parameters = vehicle.parameters
    return {
        "evidence_level": "simulation_only_design_trend",
        "competition_points_supported": False,
        "swept_parameters": [],
        "active_model_space": [
            f"{model_dof}DOF reduced vehicle equations",
            "speed-dependent QSS GGV",
            "forward transient lap when requested",
            "load-sensitive combined-slip tire projection",
            "nominal ride-height aero map applied at mapped CoP",
            "component-derived mass, CG, and full inertia tensor",
        ],
        "validity_limits": {
            "tire_normal_load_min_n": parameters.tire.fz_min_n,
            "tire_normal_load_max_n": parameters.tire.fz_max_n,
            "tire_load_range_enforced": bool(
                qss_config.get("enforce_tire_load_range", True)
            ),
            "max_abs_sideslip_rad": float(qss_config.get("max_abs_beta_rad", 0.25)),
            "max_abs_roadwheel_steer_rad": float(
                qss_config.get("max_abs_steering_rad", 0.5)
            ),
            "trim_multistart": bool(qss_config.get("trim_multistart", True)),
        },
        "known_unmodeled_or_uncorrelated": [
            "aero yaw dependence and in-motion ride-height map lookup",
            "full MF tire equations, temperature, wear, and relaxation length",
            "energy depletion and thermal derating",
            "driver execution, surface/weather, reliability, and penalties",
            "competition telemetry response-space coverage",
        ],
    }


def _mapping(config: dict[str, Any], key: str) -> dict[str, Any]:
    value = config.get(key, {})
    if not isinstance(value, dict):
        raise ValueError(f"Config section {key!r} must be a mapping.")
    return value


def _root_path(root: Path, value: Any) -> Path:
    path = Path(str(value))
    return path if path.is_absolute() else root / path


def _display_path(path: Path, root: Path) -> str:
    try:
        return path.relative_to(root).as_posix()
    except ValueError:
        return path.as_posix()


def _parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--config", type=Path, default=DEFAULT_CONFIG)
    parser.add_argument("--scenario", choices=("qss", "transient", "both"), default="both")
    parser.add_argument("--model-dof", type=int, choices=(3, 6, 10, 14))
    parser.add_argument("--all-dof", action="store_true")
    return parser.parse_args()


def main() -> None:
    args = _parse_args()
    if args.all_dof and args.model_dof is not None:
        raise ValueError("Use either --all-dof or --model-dof, not both.")
    dofs = (3, 6, 10, 14) if args.all_dof else (args.model_dof,)
    summaries = [
        run_lap_time_evaluation(
            args.config,
            scenario=cast(Scenario, args.scenario),
            model_dof_override=dof,
        )
        for dof in dofs
    ]
    output: Any = summaries if args.all_dof else summaries[0]
    print(json.dumps(output, indent=2, sort_keys=True))


if __name__ == "__main__":
    main()
