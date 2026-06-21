from __future__ import annotations

import csv
import sys
from pathlib import Path
from typing import Any, cast

import matplotlib as mpl
import numpy as np
import yaml

from _0_Utils.reporting.report_engine import ReportEngine
from _3_StandardSim._modelica_runner import ModelicaRunner
from _3_StandardSim.RampSteerEval.ramp_steer_eval_sim import (
    _apply_hampel_prefilter,
    build_smoothing_spline,
    collapse_duplicate_samples,
    evaluate_spline,
    filter_samples_by_axis_magnitude,
    normalized_fit_rmse,
    signed_peak_with_axis,
)


mpl.rcParams.update({
    "font.family": "STIXGeneral",
    "mathtext.fontset": "stix",
    "font.size": 12,
    "axes.titlesize": 13,
    "axes.labelsize": 12,
    "xtick.labelsize": 10,
    "ytick.labelsize": 10,
    "legend.fontsize": 10,
    "axes.grid": True,
    "grid.linestyle": "--",
    "grid.alpha": 0.4,
})


DEFAULT_CONFIG_PATH = Path("_3_StandardSim/SteadyStateEval/steady_state_eval_config.yml")

DEG_PER_RAD = 180.0 / np.pi
STANDARD_GRAVITY = 9.81


STEADY_STATE_EVAL_SIGNALS = [
    "steerExcess",
    "handwheelAngle",
    "leftSteerAngle",
    "rightSteerAngle",
    "accY",
    "roll",
    "sideslip",
    "handwheelTorque",
    "velX",
    "velY",
    "yawVel",
    "steadyStateAyCommand",
    "steadyStateAyError",
    "steadyStateSpeedError",
    "steadyStateSteerCmd",
    "steadyStateConditionsMet",
    "steadyStateAyRate",
    "steadyStateYawRateDerivative",
    "steadyStateSideslipRate",
    "steadyStateRollRate",
    "steadyStateHandwheelRate",
    "vcu.driveTorqueCmd",
    "vcu.mechanicalBrakeTorqueCmd",
    "Fz_FL",
    "Fz_FR",
    "Fz_RL",
    "Fz_RR",
]

STEADY_STATE_EVAL_VARIABLE_FILTER = "|".join(STEADY_STATE_EVAL_SIGNALS)


def load_config(path: str | Path) -> dict[str, Any]:
    path = Path(path)

    with path.open("r", encoding="utf-8") as f:
        config = yaml.safe_load(f)

    if config is None:
        raise ValueError(f"Config file is empty: {path}")

    if not isinstance(config, dict):
        raise TypeError(f"Expected YAML config to contain a mapping at top level: {path}")

    return cast(dict[str, Any], config)


def _as_override_dict(value: Any, *, name: str) -> dict[str, Any]:
    if value is None:
        return {}

    if not isinstance(value, dict):
        raise TypeError(f"Expected {name} to be a mapping if provided.")

    return cast(dict[str, Any], value)


def _as_float_list(value: Any, *, name: str) -> list[float]:
    if isinstance(value, (int, float)):
        return [float(value)]

    if isinstance(value, (list, tuple, np.ndarray)):
        out = [float(v) for v in value]
        if not out:
            raise ValueError(f"{name} must contain at least one value.")
        return out

    raise TypeError(f"{name} must be a scalar or a sequence of scalars.")


def _first_not_none(*values: Any) -> Any:
    for value in values:
        if value is not None:
            return value
    return None


def _float_or_nan(value: Any) -> float:
    if isinstance(value, (list, tuple, np.ndarray)):
        arr = np.asarray(value, dtype=float).reshape(-1)
        arr = arr[np.isfinite(arr)]
        if arr.size == 0:
            return float("nan")
        return float(arr[-1])

    try:
        out = float(value)
    except (TypeError, ValueError):
        return float("nan")
    return out if np.isfinite(out) else float("nan")


def _nanmean_or_nan(values: np.ndarray) -> float:
    arr = np.asarray(values, dtype=float).reshape(-1)
    arr = arr[np.isfinite(arr)]
    if arr.size == 0:
        return float("nan")
    return float(np.mean(arr))


def _velocity_trend(
    velocity_summaries: list[dict[str, Any]],
    metric_key: str,
) -> tuple[float, float]:
    if len(velocity_summaries) < 2:
        return float("nan"), float("nan")

    vel = np.asarray(
        [float(item["velocity_mps"]) for item in velocity_summaries],
        dtype=float,
    )
    vals = np.asarray([float(item[metric_key]) for item in velocity_summaries], dtype=float)
    finite = np.isfinite(vel) & np.isfinite(vals)
    if np.count_nonzero(finite) < 2:
        return float("nan"), float("nan")

    coeffs = np.polyfit(vel[finite], vals[finite], 1)
    return float(coeffs[0]), float(coeffs[1])


def _dense_axis(
    axis: np.ndarray,
    *,
    points_per_mps2: float,
    min_points: int,
) -> np.ndarray:
    axis = np.asarray(axis, dtype=float).reshape(-1)
    finite = axis[np.isfinite(axis)]
    if finite.size < 2:
        return finite

    axis_min = float(np.nanmin(finite))
    axis_max = float(np.nanmax(finite))
    if axis_max <= axis_min:
        return np.asarray([axis_min], dtype=float)

    n_points = max(
        int(min_points),
        int(np.ceil((axis_max - axis_min) * max(points_per_mps2, 1.0))) + 1,
        finite.size,
    )
    return np.linspace(axis_min, axis_max, n_points)


def _nonlinear_limit_index(
    axis: np.ndarray,
    gradient: np.ndarray,
    linear_gradient: float,
    *,
    nonlinearity_fraction: float,
    reference_ay: float,
    evaluation_margin: float,
) -> tuple[int, float, bool]:
    axis = np.asarray(axis, dtype=float).reshape(-1)
    gradient = np.asarray(gradient, dtype=float).reshape(-1)
    finite = np.isfinite(axis) & np.isfinite(gradient)

    if axis.size == 0 or gradient.shape != axis.shape or not np.any(finite):
        return 0, float("nan"), False

    finite_axis_abs = np.where(finite, np.abs(axis), np.nan)
    fallback_idx = int(np.nanargmax(finite_axis_abs))
    linear_mag = abs(float(linear_gradient))

    if not np.isfinite(linear_mag) or linear_mag <= 1e-12:
        return fallback_idx, float("nan"), False

    local_mag = np.abs(gradient)
    nonlinearity = np.abs(local_mag / linear_mag - 1.0)
    eligible = (
        finite
        & (np.abs(axis) >= reference_ay + max(0.0, evaluation_margin))
        & np.isfinite(nonlinearity)
    )

    if np.any(eligible):
        ordered = np.argsort(np.abs(axis))
        for idx in ordered:
            if eligible[idx] and nonlinearity[idx] >= nonlinearity_fraction:
                return int(idx), float(nonlinearity[idx]), True

    max_nonlinearity = float(np.nanmax(np.where(eligible, nonlinearity, np.nan)))
    if not np.isfinite(max_nonlinearity):
        max_nonlinearity = float(np.nanmax(nonlinearity[finite]))
    return fallback_idx, max_nonlinearity, False


def _metric(
    name: str,
    value: Any,
    units: str,
    description: str,
) -> dict[str, Any]:
    return {
        "standard": "SteadyStateEval",
        "metric": name,
        "value": value,
        "units": units,
        "description": description,
    }


class SteadyStateEvalSim:
    def __init__(self, config: dict[str, Any]):
        self.config = config

        sim_cfg = self.config.setdefault("simulation", {})
        sim_cfg.setdefault("variable_filter", STEADY_STATE_EVAL_VARIABLE_FILTER)
        backend = sim_cfg.get("backend", "modelica")
        if backend != "modelica":
            raise NotImplementedError(
                "SteadyStateEvalSim currently expects simulation.backend='modelica'. "
                "Closed-loop steady-state evaluation is owned by VehicleSim useMode=3."
            )

        self.start_time = float(sim_cfg.get("start_time", 0.0))
        self.stop_time = float(sim_cfg.get("stop_time", 30.0))
        self.runner = ModelicaRunner.from_config(self.config)

    def _target_ays_from_sweep(self) -> list[float]:
        sweep = self.config["sweep"]
        explicit = _first_not_none(
            sweep.get("targetAys"),
            sweep.get("targetAyValues"),
            sweep.get("testAys"),
            sweep.get("testAy"),
        )
        if explicit is not None:
            target_ays = _as_float_list(explicit, name="sweep.targetAys")
        else:
            max_ay = float(sweep.get("maxAy", sweep.get("ay_max", 8.0)))
            ay_step = float(sweep.get("ayStep", sweep.get("ay_step", 2.0)))
            min_ay = float(sweep.get("minAy", sweep.get("ay_min", ay_step)))
            if max_ay <= 0.0:
                raise ValueError("sweep.maxAy must be positive.")
            if ay_step <= 0.0:
                raise ValueError("sweep.ayStep must be positive.")
            if min_ay <= 0.0:
                raise ValueError("sweep.minAy must be positive for generated sweeps.")
            target_ays = [
                float(v)
                for v in np.arange(min_ay, max_ay + 0.5 * ay_step, ay_step)
            ]

        if bool(sweep.get("includeNegative", False)):
            negative = [-abs(v) for v in reversed(target_ays) if abs(v) > 0.0]
            positive = [abs(v) for v in target_ays if abs(v) > 0.0]
            target_ays = negative + positive

        if not target_ays:
            raise ValueError("SteadyStateEval target-a_y sweep is empty.")

        return target_ays

    def build_cases(self) -> list[dict[str, Any]]:
        sweep = self.config["sweep"]
        sim_cfg = self.config.get("simulation", {})

        test_vels_raw = sweep.get("testVels", sweep.get("testVel", 15.0))
        test_vels = _as_float_list(test_vels_raw, name="sweep.testVels")
        target_ays = self._target_ays_from_sweep()

        init_parameters = _as_override_dict(
            sim_cfg.get("init_parameters", {}),
            name="simulation.init_parameters",
        )

        cases: list[dict[str, Any]] = []
        for test_vel in test_vels:
            for target_ay in target_ays:
                case: dict[str, Any] = dict(init_parameters)
                case.update({
                    "_mode": "closed_loop_steady_ay",
                    "_testVel": float(test_vel),
                    "_testAy": float(target_ay),
                    "useMode": 3,
                    "initialVel": float(test_vel),
                    "targetVel": float(test_vel),
                    "targetAy": float(target_ay),
                    "startTime": self.start_time,
                    "stopTime": self.stop_time,
                })
                cases.append(case)

        return cases

    def run(self) -> dict[str, Any]:
        cases = self.build_cases()

        results = self.runner.run(
            signals=STEADY_STATE_EVAL_SIGNALS,
            mode="last",
            cases=cases,
            execution=self.config.get("execution", {}),
        )

        return self.summarize(results)

    def _steady_rows(self, results: list[dict[str, Any]]) -> list[dict[str, float]]:
        rows: list[dict[str, float]] = []

        for result in results:
            if result.get("_status") == "failed":
                continue

            settled = _float_or_nan(result.get("steadyStateConditionsMet", 1.0))
            if np.isfinite(settled) and settled < 0.5:
                continue

            vel = _float_or_nan(_first_not_none(result.get("_testVel"), result.get("targetVel")))
            target_ay = _float_or_nan(_first_not_none(result.get("_testAy"), result.get("targetAy")))
            acc_y = _float_or_nan(result.get("accY"))
            vel_x = _float_or_nan(result.get("velX"))
            vel_y = _float_or_nan(result.get("velY"))
            yaw = _float_or_nan(result.get("yawVel"))
            left = _float_or_nan(result.get("leftSteerAngle"))
            right = _float_or_nan(result.get("rightSteerAngle"))

            speed = float(np.sqrt(vel_x**2 + vel_y**2)) if np.isfinite(vel_x + vel_y) else float("nan")
            curvature = yaw / max(speed, 0.1) if np.isfinite(yaw + speed) else float("nan")

            row = {
                "velocity": vel,
                "target_ay": target_ay,
                "ay": acc_y,
                "roadwheel": 0.5 * (left + right),
                "handwheel": _float_or_nan(result.get("handwheelAngle")),
                "steer_excess": _float_or_nan(result.get("steerExcess")),
                "curvature": curvature,
                "roll": _float_or_nan(result.get("roll")),
                "sideslip": _float_or_nan(result.get("sideslip")),
                "torque": _float_or_nan(result.get("handwheelTorque")),
                "speed": speed,
                "yaw": yaw,
                "steady_ay_command": _float_or_nan(result.get("steadyStateAyCommand")),
                "steady_ay_error": _float_or_nan(result.get("steadyStateAyError")),
                "steady_speed_error": _float_or_nan(result.get("steadyStateSpeedError")),
                "steady_steer_cmd": _float_or_nan(result.get("steadyStateSteerCmd")),
                "steady_ay_rate": _float_or_nan(result.get("steadyStateAyRate")),
                "steady_yaw_rate_derivative": _float_or_nan(
                    result.get("steadyStateYawRateDerivative")
                ),
                "steady_sideslip_rate": _float_or_nan(result.get("steadyStateSideslipRate")),
                "steady_roll_rate": _float_or_nan(result.get("steadyStateRollRate")),
                "steady_handwheel_rate": _float_or_nan(result.get("steadyStateHandwheelRate")),
                "drive_torque": _float_or_nan(result.get("vcu.driveTorqueCmd")),
                "mechanical_brake_torque": _float_or_nan(
                    result.get("vcu.mechanicalBrakeTorqueCmd")
                ),
                "fz_fl": _float_or_nan(result.get("Fz_FL")),
                "fz_fr": _float_or_nan(result.get("Fz_FR")),
                "fz_rl": _float_or_nan(result.get("Fz_RL")),
                "fz_rr": _float_or_nan(result.get("Fz_RR")),
            }

            required = (
                "velocity",
                "target_ay",
                "ay",
                "roadwheel",
                "handwheel",
                "steer_excess",
                "roll",
                "sideslip",
                "torque",
                "speed",
                "yaw",
            )
            if all(np.isfinite(row[key]) for key in required):
                rows.append(row)

        return rows

    def _successful_and_failed(
        self,
        results: list[dict[str, Any]],
    ) -> tuple[list[dict[str, Any]], list[dict[str, Any]]]:
        successful: list[dict[str, Any]] = []
        failed: list[dict[str, Any]] = []

        for result in results:
            if result.get("_status") == "failed":
                failed.append(result)
                continue

            settled = _float_or_nan(result.get("steadyStateConditionsMet", 1.0))
            if np.isfinite(settled) and settled < 0.5:
                skipped = dict(result)
                skipped["_status"] = "failed"
                skipped["_error"] = "closed-loop steady-state conditions were not met"
                failed.append(skipped)
                continue

            successful.append(result)

        return successful, failed

    def _build_velocity_isoline_series(self, rows: list[dict[str, float]]) -> dict[str, Any]:
        grouped: dict[float, list[dict[str, float]]] = {}
        for row in rows:
            grouped.setdefault(float(row["velocity"]), []).append(row)

        series: dict[str, Any] = {
            "ay_measured_raw_isoline": {},
            "ay_target_raw_isoline": {},
            "roadwheel_raw_isoline": {},
            "handwheel_raw_isoline": {},
            "steer_excess_raw_isoline": {},
            "curvature_raw_isoline": {},
            "roll_raw_isoline": {},
            "sideslip_raw_isoline": {},
            "torque_raw_isoline": {},
            "speed_raw_isoline": {},
            "yaw_raw_isoline": {},
            "steady_ay_error_raw_isoline": {},
            "steady_speed_error_raw_isoline": {},
            "drive_torque_raw_isoline": {},
            "mechanical_brake_torque_raw_isoline": {},
            "ay_measured_fit_isoline": {},
            "roadwheel_fit_isoline": {},
            "handwheel_fit_isoline": {},
            "steer_excess_fit_isoline": {},
            "curvature_fit_isoline": {},
            "roll_fit_isoline": {},
            "sideslip_fit_isoline": {},
            "torque_fit_isoline": {},
            "drive_torque_fit_isoline": {},
            "mechanical_brake_torque_fit_isoline": {},
        }

        key_map = {
            "ay_measured_raw_isoline": "ay",
            "ay_target_raw_isoline": "target_ay",
            "roadwheel_raw_isoline": "roadwheel",
            "handwheel_raw_isoline": "handwheel",
            "steer_excess_raw_isoline": "steer_excess",
            "curvature_raw_isoline": "curvature",
            "roll_raw_isoline": "roll",
            "sideslip_raw_isoline": "sideslip",
            "torque_raw_isoline": "torque",
            "speed_raw_isoline": "speed",
            "yaw_raw_isoline": "yaw",
            "steady_ay_error_raw_isoline": "steady_ay_error",
            "steady_speed_error_raw_isoline": "steady_speed_error",
            "drive_torque_raw_isoline": "drive_torque",
            "mechanical_brake_torque_raw_isoline": "mechanical_brake_torque",
        }

        fit_cfg = self.config.get("fit", {})
        spline_smoothing_fraction = float(fit_cfg.get("spline_smoothing_fraction", 0.02))
        hampel_window = int(fit_cfg.get("hampel_window", 3))
        hampel_nsigmas = float(fit_cfg.get("hampel_nsigmas", 3.0))
        fit_points_per_mps2 = float(fit_cfg.get("fit_points_per_mps2", 20.0))
        fit_min_points = int(fit_cfg.get("fit_min_points", 120))

        fit_key_map = {
            "roadwheel_fit_isoline": "roadwheel",
            "handwheel_fit_isoline": "handwheel",
            "steer_excess_fit_isoline": "steer_excess",
            "curvature_fit_isoline": "curvature",
            "roll_fit_isoline": "roll",
            "sideslip_fit_isoline": "sideslip",
            "torque_fit_isoline": "torque",
            "drive_torque_fit_isoline": "drive_torque",
            "mechanical_brake_torque_fit_isoline": "mechanical_brake_torque",
        }

        for velocity, group_rows in sorted(grouped.items()):
            ordered = sorted(group_rows, key=lambda item: item["ay"])
            for series_key, row_key in key_map.items():
                series[series_key][velocity] = np.asarray(
                    [row[row_key] for row in ordered],
                    dtype=float,
                )

            fit_axis, fit_inputs = collapse_duplicate_samples(
                np.asarray([row["ay"] for row in ordered], dtype=float),
                {
                    row_key: np.asarray([row[row_key] for row in ordered], dtype=float)
                    for row_key in fit_key_map.values()
                },
            )
            dense_axis = _dense_axis(
                fit_axis,
                points_per_mps2=fit_points_per_mps2,
                min_points=fit_min_points,
            )
            series["ay_measured_fit_isoline"][velocity] = dense_axis

            if dense_axis.size >= 2 and fit_axis.size >= 2:
                for series_key, row_key in fit_key_map.items():
                    fit = build_smoothing_spline(
                        fit_axis,
                        fit_inputs[row_key],
                        smoothing_fraction=spline_smoothing_fraction,
                        hampel_window=hampel_window,
                        hampel_nsigmas=hampel_nsigmas,
                    )
                    series[series_key][velocity] = evaluate_spline(fit, dense_axis)
            else:
                for series_key, row_key in fit_key_map.items():
                    series[series_key][velocity] = fit_inputs[row_key]

        return series

    def _summarize_rows(self, rows: list[dict[str, float]]) -> dict[str, Any]:
        if not rows:
            return self._empty_summary()

        rows = sorted(rows, key=lambda item: item["ay"])
        ay = np.asarray([row["ay"] for row in rows], dtype=float)
        values = {
            "roadwheel": np.asarray([row["roadwheel"] for row in rows], dtype=float),
            "handwheel": np.asarray([row["handwheel"] for row in rows], dtype=float),
            "steer_excess": np.asarray([row["steer_excess"] for row in rows], dtype=float),
            "curvature": np.asarray([row["curvature"] for row in rows], dtype=float),
            "roll": np.asarray([row["roll"] for row in rows], dtype=float),
            "sideslip": np.asarray([row["sideslip"] for row in rows], dtype=float),
            "torque": np.asarray([row["torque"] for row in rows], dtype=float),
        }

        fit_cfg = self.config.get("fit", {})
        ay_linear_max = float(fit_cfg.get("ay_linear_max", 4.0))
        ay_min_magnitude = float(fit_cfg.get("ay_min_magnitude", 1.0))
        hampel_window = int(fit_cfg.get("hampel_window", 3))
        hampel_nsigmas = float(fit_cfg.get("hampel_nsigmas", 3.0))
        fit_points_per_mps2 = float(fit_cfg.get("fit_points_per_mps2", 20.0))
        fit_min_points = int(fit_cfg.get("fit_min_points", 120))
        nonlinearity_fraction = float(fit_cfg.get("nonlinearity_fraction", 0.20))
        nonlinearity_reference_ay = float(
            fit_cfg.get("nonlinearity_reference_ay", ay_linear_max)
        )
        nonlinearity_evaluation_margin = float(
            fit_cfg.get("nonlinearity_evaluation_ay_margin", 0.75)
        )
        nonlinearity_metric = str(fit_cfg.get("nonlinearity_metric", "handwheel"))

        filtered_ay, filtered_values = filter_samples_by_axis_magnitude(
            ay,
            values,
            min_magnitude=ay_min_magnitude,
        )
        if filtered_ay.size == 0:
            filtered_ay = ay
            filtered_values = values

        analysis_axis, analysis_inputs = collapse_duplicate_samples(
            filtered_ay,
            filtered_values,
        )

        fit_quality = {
            "roadwheel_fit_nrmse": float("nan"),
            "handwheel_fit_nrmse": float("nan"),
            "steer_excess_fit_nrmse": float("nan"),
            "curvature_fit_nrmse": float("nan"),
            "roll_fit_nrmse": float("nan"),
            "sideslip_fit_nrmse": float("nan"),
            "torque_fit_nrmse": float("nan"),
        }
        fit_axis = _dense_axis(
            analysis_axis,
            points_per_mps2=fit_points_per_mps2,
            min_points=fit_min_points,
        )
        if fit_axis.size == 0:
            fit_axis = analysis_axis
        gradients = {key: np.full(fit_axis.shape, np.nan) for key in analysis_inputs}

        if analysis_axis.size >= 2:
            spline_smoothing_fraction = float(
                fit_cfg.get("spline_smoothing_fraction", 0.02)
            )
            for key, value in analysis_inputs.items():
                fit = build_smoothing_spline(
                    analysis_axis,
                    value,
                    smoothing_fraction=spline_smoothing_fraction,
                    hampel_window=hampel_window,
                    hampel_nsigmas=hampel_nsigmas,
                )
                fit_quality[f"{key}_fit_nrmse"] = normalized_fit_rmse(
                    analysis_axis,
                    value,
                    fit,
                )
                gradients[key] = _apply_hampel_prefilter(
                    evaluate_spline(fit, fit_axis, 1),
                    hampel_window,
                    n_sigmas=hampel_nsigmas,
                )

        linear_mask = (np.abs(fit_axis) >= ay_min_magnitude) & (
            np.abs(fit_axis) <= ay_linear_max
        )

        def _linear_gradient(key: str) -> float:
            gradient = gradients[key]
            if np.count_nonzero(linear_mask) > 0:
                return _nanmean_or_nan(gradient[linear_mask])
            return _nanmean_or_nan(gradient)

        roadwheel_gradient = _linear_gradient("roadwheel")
        handwheel_gradient = _linear_gradient("handwheel")
        understeer_gradient = _linear_gradient("steer_excess")
        roll_gradient = _linear_gradient("roll")
        sideslip_gradient = _linear_gradient("sideslip")

        if nonlinearity_metric not in gradients:
            nonlinearity_metric = "handwheel"

        linear_gradient_map = {
            "roadwheel": roadwheel_gradient,
            "handwheel": handwheel_gradient,
            "steer_excess": understeer_gradient,
            "roll": roll_gradient,
            "sideslip": sideslip_gradient,
        }
        limit_idx, limit_nonlinearity_fraction, limit_nonlinearity_reached = (
            _nonlinear_limit_index(
                fit_axis,
                gradients[nonlinearity_metric],
                linear_gradient_map.get(nonlinearity_metric, handwheel_gradient),
                nonlinearity_fraction=nonlinearity_fraction,
                reference_ay=nonlinearity_reference_ay,
                evaluation_margin=nonlinearity_evaluation_margin,
            )
        )
        if fit_axis.size and limit_idx < fit_axis.size:
            limit_ay = float(fit_axis[limit_idx])
        else:
            limit_idx = 0
            limit_ay = float("nan")

        def _limit_gradient(key: str) -> float:
            gradient = gradients[key]
            if gradient.size <= limit_idx:
                return float("nan")
            return float(gradient[limit_idx])

        peak_torque, peak_torque_ay = signed_peak_with_axis(
            filtered_ay,
            filtered_values["torque"],
        )

        velocity = rows[0].get("velocity", float("nan"))
        summary = {
            "MeasuredAy_range": (float(np.nanmin(ay)), float(np.nanmax(ay))),
            "Ay_range": (float(np.nanmin(ay)), float(np.nanmax(ay))),
            "velocity_mps": float(velocity),
            "roadwheel_angle_gradient_rad_per_mps2": roadwheel_gradient,
            "roadwheel_angle_gradient_deg_per_g": roadwheel_gradient * DEG_PER_RAD * STANDARD_GRAVITY,
            "handwheel_angle_gradient_rad_per_mps2": handwheel_gradient,
            "handwheel_angle_gradient_deg_per_g": handwheel_gradient * DEG_PER_RAD * STANDARD_GRAVITY,
            "roadwheel_steer_sensitivity_rad_per_mps2": roadwheel_gradient,
            "roadwheel_steer_sensitivity_deg_per_g": roadwheel_gradient * DEG_PER_RAD * STANDARD_GRAVITY,
            "handwheel_steer_sensitivity_rad_per_mps2": handwheel_gradient,
            "handwheel_steer_sensitivity_deg_per_g": handwheel_gradient * DEG_PER_RAD * STANDARD_GRAVITY,
            "sideslip_gradient_rad_per_mps2": sideslip_gradient,
            "sideslip_gradient_deg_per_g": sideslip_gradient * DEG_PER_RAD * STANDARD_GRAVITY,
            "limit_ay_mps2": limit_ay,
            "limit_nonlinearity_fraction": limit_nonlinearity_fraction,
            "limit_nonlinearity_threshold_fraction": nonlinearity_fraction,
            "limit_nonlinearity_reached": float(limit_nonlinearity_reached),
            "limit_nonlinearity_metric": nonlinearity_metric,
            "limit_handwheel_gradient_rad_per_mps2": _limit_gradient("handwheel"),
            "limit_handwheel_gradient_deg_per_g": _limit_gradient("handwheel")
            * DEG_PER_RAD
            * STANDARD_GRAVITY,
            "limit_sideslip_gradient_rad_per_mps2": _limit_gradient("sideslip"),
            "limit_sideslip_gradient_deg_per_g": _limit_gradient("sideslip")
            * DEG_PER_RAD
            * STANDARD_GRAVITY,
            "limit_understeer_gradient_rad_per_mps2": _limit_gradient("steer_excess"),
            "limit_understeer_gradient_deg_per_g": _limit_gradient("steer_excess")
            * DEG_PER_RAD
            * STANDARD_GRAVITY,
            "limit_roll_gradient_rad_per_mps2": _limit_gradient("roll"),
            "limit_roll_gradient_deg_per_g": _limit_gradient("roll")
            * DEG_PER_RAD
            * STANDARD_GRAVITY,
            "understeer_gradient_rad_per_mps2": understeer_gradient,
            "understeer_gradient_deg_per_g": understeer_gradient * DEG_PER_RAD * STANDARD_GRAVITY,
            "excess_understeer_gradient_rad_per_mps2": understeer_gradient,
            "excess_understeer_gradient_deg_per_g": understeer_gradient * DEG_PER_RAD * STANDARD_GRAVITY,
            "roll_gradient_rad_per_mps2": roll_gradient,
            "roll_gradient_deg_per_g": roll_gradient * DEG_PER_RAD * STANDARD_GRAVITY,
            "peak_handwheel_torque_Nm": peak_torque,
            "peak_handwheel_torque_ay_mps2": peak_torque_ay,
        }
        summary.update(fit_quality)
        return summary

    def _empty_summary(self) -> dict[str, Any]:
        return {
            "MeasuredAy_range": (float("nan"), float("nan")),
            "Ay_range": (float("nan"), float("nan")),
            "velocity_mps": float("nan"),
            "roadwheel_angle_gradient_rad_per_mps2": float("nan"),
            "roadwheel_angle_gradient_deg_per_g": float("nan"),
            "handwheel_angle_gradient_rad_per_mps2": float("nan"),
            "handwheel_angle_gradient_deg_per_g": float("nan"),
            "roadwheel_steer_sensitivity_rad_per_mps2": float("nan"),
            "roadwheel_steer_sensitivity_deg_per_g": float("nan"),
            "handwheel_steer_sensitivity_rad_per_mps2": float("nan"),
            "handwheel_steer_sensitivity_deg_per_g": float("nan"),
            "sideslip_gradient_rad_per_mps2": float("nan"),
            "sideslip_gradient_deg_per_g": float("nan"),
            "limit_ay_mps2": float("nan"),
            "limit_nonlinearity_fraction": float("nan"),
            "limit_nonlinearity_threshold_fraction": float("nan"),
            "limit_nonlinearity_reached": float("nan"),
            "limit_nonlinearity_metric": "",
            "limit_handwheel_gradient_rad_per_mps2": float("nan"),
            "limit_handwheel_gradient_deg_per_g": float("nan"),
            "limit_sideslip_gradient_rad_per_mps2": float("nan"),
            "limit_sideslip_gradient_deg_per_g": float("nan"),
            "limit_understeer_gradient_rad_per_mps2": float("nan"),
            "limit_understeer_gradient_deg_per_g": float("nan"),
            "limit_roll_gradient_rad_per_mps2": float("nan"),
            "limit_roll_gradient_deg_per_g": float("nan"),
            "understeer_gradient_rad_per_mps2": float("nan"),
            "understeer_gradient_deg_per_g": float("nan"),
            "excess_understeer_gradient_rad_per_mps2": float("nan"),
            "excess_understeer_gradient_deg_per_g": float("nan"),
            "roll_gradient_rad_per_mps2": float("nan"),
            "roll_gradient_deg_per_g": float("nan"),
            "peak_handwheel_torque_Nm": float("nan"),
            "peak_handwheel_torque_ay_mps2": float("nan"),
            "roadwheel_fit_nrmse": float("nan"),
            "handwheel_fit_nrmse": float("nan"),
            "steer_excess_fit_nrmse": float("nan"),
            "curvature_fit_nrmse": float("nan"),
            "roll_fit_nrmse": float("nan"),
            "sideslip_fit_nrmse": float("nan"),
            "torque_fit_nrmse": float("nan"),
        }

    def write_metrics_csv(self, metrics: list[dict[str, Any]]) -> Path:
        report_cfg = self.config.get("report", {})
        metrics_cfg_path = report_cfg.get("metrics_csv_path")
        if metrics_cfg_path is not None:
            metrics_csv_path = Path(metrics_cfg_path)
        else:
            report_path = Path(
                report_cfg.get(
                    "output_path",
                    "_3_StandardSim/results/steady_state_eval_report.pdf",
                )
            )
            metrics_csv_path = report_path.with_name(f"{report_path.stem}_metrics.csv")

        metrics_csv_path.parent.mkdir(parents=True, exist_ok=True)
        with metrics_csv_path.open("w", newline="", encoding="utf-8") as f:
            fieldnames = ["standard", "metric", "value", "units", "description"]
            writer = csv.DictWriter(f, fieldnames=fieldnames)
            writer.writeheader()
            writer.writerows(metrics)

        return metrics_csv_path

    def summarize(self, results: list[dict[str, Any]]) -> dict[str, Any]:
        if not results:
            raise ValueError("No SteadyStateEval results to summarize.")

        successful_results, failed_results = self._successful_and_failed(results)
        rows = self._steady_rows(successful_results)

        if not rows:
            failed_labels = ", ".join(
                str(r.get("_case_label", "unknown")) for r in failed_results
            )
            raise RuntimeError(
                "No settled SteadyStateEval cases were available for summary. "
                f"Failed or unsettled cases: {failed_labels}"
            )

        if failed_results:
            print(
                f"Warning: skipped {len(failed_results)} failed or unsettled case(s) in summary.",
                flush=True,
            )

        velocity_groups: dict[float, list[dict[str, float]]] = {}
        for row in rows:
            velocity_groups.setdefault(float(row["velocity"]), []).append(row)

        velocity_summaries = [
            self._summarize_rows(group_rows)
            for _, group_rows in sorted(velocity_groups.items())
            if group_rows
        ]

        report_cfg = self.config.get("report", {})
        metric_target_velocity = float(report_cfg.get("metric_target_velocity_mps", 15.0))
        metric_summary = min(
            velocity_summaries,
            key=lambda item: abs(float(item.get("velocity_mps", np.nan)) - metric_target_velocity),
        )

        summary = self._summarize_rows(rows)
        roadwheel_trend, _ = _velocity_trend(
            velocity_summaries,
            "roadwheel_angle_gradient_deg_per_g",
        )
        handwheel_trend, _ = _velocity_trend(
            velocity_summaries,
            "handwheel_angle_gradient_deg_per_g",
        )
        sideslip_trend, _ = _velocity_trend(
            velocity_summaries,
            "sideslip_gradient_deg_per_g",
        )
        limit_handwheel_trend, _ = _velocity_trend(
            velocity_summaries,
            "limit_handwheel_gradient_deg_per_g",
        )
        limit_sideslip_trend, _ = _velocity_trend(
            velocity_summaries,
            "limit_sideslip_gradient_deg_per_g",
        )
        limit_understeer_trend, _ = _velocity_trend(
            velocity_summaries,
            "limit_understeer_gradient_deg_per_g",
        )
        understeer_trend, _ = _velocity_trend(
            velocity_summaries,
            "understeer_gradient_deg_per_g",
        )
        limit_roll_trend, _ = _velocity_trend(
            velocity_summaries,
            "limit_roll_gradient_deg_per_g",
        )
        roll_trend, _ = _velocity_trend(
            velocity_summaries,
            "roll_gradient_deg_per_g",
        )
        summary.update({
            "roadwheel_angle_gradient_velocity_slope_deg_per_g_per_mps": roadwheel_trend,
            "handwheel_angle_gradient_velocity_slope_deg_per_g_per_mps": handwheel_trend,
            "sideslip_gradient_velocity_slope_deg_per_g_per_mps": sideslip_trend,
            "limit_handwheel_gradient_velocity_slope_deg_per_g_per_mps": limit_handwheel_trend,
            "limit_sideslip_gradient_velocity_slope_deg_per_g_per_mps": limit_sideslip_trend,
            "limit_understeer_gradient_velocity_slope_deg_per_g_per_mps": limit_understeer_trend,
            "limit_roll_gradient_velocity_slope_deg_per_g_per_mps": limit_roll_trend,
            "understeer_gradient_velocity_slope_deg_per_g_per_mps": understeer_trend,
            "roll_gradient_velocity_slope_deg_per_g_per_mps": roll_trend,
        })

        sweep_cfg = self.config.get("sweep", {})
        target_ays = self._target_ays_from_sweep()
        metrics: list[dict[str, Any]] = [
            _metric(
                "n_cases",
                len(results),
                "count",
                "Total SteadyStateEval closed-loop target points requested",
            ),
            _metric(
                "n_successful_cases",
                len(successful_results),
                "count",
                "Number of settled SteadyStateEval cases available before finite-value filtering",
            ),
            _metric(
                "n_failed_cases",
                len(failed_results),
                "count",
                "Number of failed or unsettled SteadyStateEval cases skipped by the summary",
            ),
            _metric(
                "standard_sweep_max_ay_mps2",
                float(max(abs(v) for v in target_ays)),
                "m/s^2",
                "Maximum requested closed-loop lateral-acceleration target",
            ),
            _metric(
                "standard_sweep_target_count",
                len(target_ays),
                "count",
                "Number of requested lateral-acceleration target points per velocity",
            ),
            _metric(
                "metric_target_velocity_mps",
                metric_target_velocity,
                "m/s",
                "Target velocity used to select the exported metric table",
            ),
            _metric(
                "metric_source_velocity_mps",
                metric_summary["velocity_mps"],
                "m/s",
                "Velocity nearest the target used for the exported metric table",
            ),
            _metric(
                "ay_min",
                float(metric_summary["MeasuredAy_range"][0]),
                "m/s^2",
                "Minimum measured settled lateral acceleration",
            ),
            _metric(
                "ay_max",
                float(metric_summary["MeasuredAy_range"][1]),
                "m/s^2",
                "Maximum measured settled lateral acceleration",
            ),
            _metric(
                "sideslip_gradient_rad_per_mps2",
                metric_summary["sideslip_gradient_rad_per_mps2"],
                "rad/(m/s^2)",
                "Linear steady-state sideslip gradient versus measured Ay",
            ),
            _metric(
                "sideslip_gradient_deg_per_g",
                metric_summary["sideslip_gradient_deg_per_g"],
                "deg/g",
                "Linear steady-state sideslip gradient versus measured Ay",
            ),
            _metric(
                "limit_ay_mps2",
                metric_summary["limit_ay_mps2"],
                "m/s^2",
                "Fitted measured lateral acceleration where local steering-gradient nonlinearity first reaches the "
                "configured threshold, or the largest settled fitted point if not reached",
            ),
            _metric(
                "limit_nonlinearity_fraction",
                metric_summary["limit_nonlinearity_fraction"],
                "fraction",
                "Local steering-gradient nonlinearity fraction at the reported fitted limit point",
            ),
            _metric(
                "limit_nonlinearity_threshold_fraction",
                metric_summary["limit_nonlinearity_threshold_fraction"],
                "fraction",
                "Configured local steering-gradient nonlinearity fraction used to define the fitted limit point",
            ),
            _metric(
                "limit_nonlinearity_reached",
                metric_summary["limit_nonlinearity_reached"],
                "boolean",
                "Whether the fitted curve crossed the configured local steering-gradient nonlinearity threshold",
            ),
            _metric(
                "limit_nonlinearity_metric",
                metric_summary["limit_nonlinearity_metric"],
                "signal",
                "Fitted response gradient used for local nonlinearity detection",
            ),
            _metric(
                "limit_sideslip_gradient_rad_per_mps2",
                metric_summary["limit_sideslip_gradient_rad_per_mps2"],
                "rad/(m/s^2)",
                "Local steady-state sideslip gradient at the fitted nonlinearity limit",
            ),
            _metric(
                "limit_sideslip_gradient_deg_per_g",
                metric_summary["limit_sideslip_gradient_deg_per_g"],
                "deg/g",
                "Local steady-state sideslip gradient at the fitted nonlinearity limit",
            ),
            _metric(
                "limit_understeer_gradient_rad_per_mps2",
                metric_summary["limit_understeer_gradient_rad_per_mps2"],
                "rad/(m/s^2)",
                "Local steer-excess derivative at the fitted nonlinearity limit",
            ),
            _metric(
                "limit_understeer_gradient_deg_per_g",
                metric_summary["limit_understeer_gradient_deg_per_g"],
                "deg/g",
                "Local steer-excess derivative at the fitted nonlinearity limit",
            ),
            _metric(
                "understeer_gradient_rad_per_mps2",
                metric_summary["understeer_gradient_rad_per_mps2"],
                "rad/(m/s^2)",
                "Linear steer-excess derivative versus measured Ay",
            ),
            _metric(
                "understeer_gradient_deg_per_g",
                metric_summary["understeer_gradient_deg_per_g"],
                "deg/g",
                "Linear steer-excess derivative versus measured Ay",
            ),
            _metric(
                "handwheel_angle_gradient_rad_per_mps2",
                metric_summary["handwheel_angle_gradient_rad_per_mps2"],
                "rad/(m/s^2)",
                "Linear raw handwheel angle gradient versus measured Ay",
            ),
            _metric(
                "handwheel_angle_gradient_deg_per_g",
                metric_summary["handwheel_angle_gradient_deg_per_g"],
                "deg/g",
                "Linear raw handwheel angle gradient versus measured Ay",
            ),
            _metric(
                "limit_handwheel_gradient_rad_per_mps2",
                metric_summary["limit_handwheel_gradient_rad_per_mps2"],
                "rad/(m/s^2)",
                "Local raw handwheel angle gradient at the fitted nonlinearity limit",
            ),
            _metric(
                "limit_handwheel_gradient_deg_per_g",
                metric_summary["limit_handwheel_gradient_deg_per_g"],
                "deg/g",
                "Local raw handwheel angle gradient at the fitted nonlinearity limit",
            ),
            _metric(
                "roll_gradient_deg_per_g",
                metric_summary["roll_gradient_deg_per_g"],
                "deg/g",
                "Linear steady-state roll gradient versus measured Ay",
            ),
            _metric(
                "limit_roll_gradient_rad_per_mps2",
                metric_summary["limit_roll_gradient_rad_per_mps2"],
                "rad/(m/s^2)",
                "Local steady-state roll gradient at the fitted nonlinearity limit",
            ),
            _metric(
                "limit_roll_gradient_deg_per_g",
                metric_summary["limit_roll_gradient_deg_per_g"],
                "deg/g",
                "Local steady-state roll gradient at the fitted nonlinearity limit",
            ),
            _metric(
                "peak_handwheel_torque_Nm",
                metric_summary["peak_handwheel_torque_Nm"],
                "N*m",
                "Signed handwheel torque at maximum absolute handwheel torque",
            ),
            _metric(
                "peak_handwheel_torque_ay_mps2",
                metric_summary["peak_handwheel_torque_ay_mps2"],
                "m/s^2",
                "Measured lateral acceleration at peak absolute handwheel torque",
            ),
            _metric(
                "roadwheel_fit_nrmse",
                metric_summary["roadwheel_fit_nrmse"],
                "fraction",
                "Normalized fit residual for roadwheel angle versus measured Ay",
            ),
            _metric(
                "handwheel_fit_nrmse",
                metric_summary["handwheel_fit_nrmse"],
                "fraction",
                "Normalized fit residual for handwheel angle versus measured Ay",
            ),
            _metric(
                "steer_excess_fit_nrmse",
                metric_summary["steer_excess_fit_nrmse"],
                "fraction",
                "Normalized fit residual for steer excess versus measured Ay",
            ),
            _metric(
                "roll_fit_nrmse",
                metric_summary["roll_fit_nrmse"],
                "fraction",
                "Normalized fit residual for roll versus measured Ay",
            ),
            _metric(
                "sideslip_fit_nrmse",
                metric_summary["sideslip_fit_nrmse"],
                "fraction",
                "Normalized fit residual for sideslip versus measured Ay",
            ),
            _metric(
                "sideslip_gradient_velocity_slope_deg_per_g_per_mps",
                sideslip_trend,
                "deg/g per m/s",
                "Linear fit slope of steady-state sideslip gradient versus velocity",
            ),
            _metric(
                "limit_sideslip_gradient_velocity_slope_deg_per_g_per_mps",
                limit_sideslip_trend,
                "deg/g per m/s",
                "Linear fit slope of endpoint sideslip gradient versus velocity",
            ),
            _metric(
                "limit_understeer_gradient_velocity_slope_deg_per_g_per_mps",
                limit_understeer_trend,
                "deg/g per m/s",
                "Linear fit slope of endpoint steer-excess gradient versus velocity",
            ),
            _metric(
                "handwheel_angle_gradient_velocity_slope_deg_per_g_per_mps",
                handwheel_trend,
                "deg/g per m/s",
                "Linear fit slope of raw handwheel angle gradient versus velocity",
            ),
            _metric(
                "limit_handwheel_gradient_velocity_slope_deg_per_g_per_mps",
                limit_handwheel_trend,
                "deg/g per m/s",
                "Linear fit slope of endpoint handwheel angle gradient versus velocity",
            ),
            _metric(
                "limit_roll_gradient_velocity_slope_deg_per_g_per_mps",
                limit_roll_trend,
                "deg/g per m/s",
                "Linear fit slope of endpoint roll gradient versus velocity",
            ),
            _metric(
                "understeer_gradient_velocity_slope_deg_per_g_per_mps",
                understeer_trend,
                "deg/g per m/s",
                "Linear fit slope of steer-excess gradient versus velocity",
            ),
            _metric(
                "roll_gradient_velocity_slope_deg_per_g_per_mps",
                roll_trend,
                "deg/g per m/s",
                "Linear fit slope of steady-state roll gradient versus velocity",
            ),
        ]

        if sweep_cfg.get("includeNegative", False):
            metrics.append(_metric(
                "standard_sweep_includes_negative_targets",
                1,
                "boolean",
                "Whether the configured sweep includes negative lateral-acceleration targets",
            ))

        metrics_csv_path = self.write_metrics_csv(metrics)
        print(f"SteadyStateEval metrics CSV written: {metrics_csv_path}")

        sorted_rows = sorted(rows, key=lambda item: (item["velocity"], item["ay"]))
        row_series = {
            "ay_measured": np.asarray([row["ay"] for row in sorted_rows], dtype=float),
            "ay_target": np.asarray([row["target_ay"] for row in sorted_rows], dtype=float),
            "roadwheel": np.asarray([row["roadwheel"] for row in sorted_rows], dtype=float),
            "handwheel": np.asarray([row["handwheel"] for row in sorted_rows], dtype=float),
            "steer_excess": np.asarray([row["steer_excess"] for row in sorted_rows], dtype=float),
            "curvature": np.asarray([row["curvature"] for row in sorted_rows], dtype=float),
            "roll": np.asarray([row["roll"] for row in sorted_rows], dtype=float),
            "sideslip": np.asarray([row["sideslip"] for row in sorted_rows], dtype=float),
            "torque": np.asarray([row["torque"] for row in sorted_rows], dtype=float),
            "speed": np.asarray([row["speed"] for row in sorted_rows], dtype=float),
            "yaw": np.asarray([row["yaw"] for row in sorted_rows], dtype=float),
            "steady_ay_error": np.asarray(
                [row["steady_ay_error"] for row in sorted_rows],
                dtype=float,
            ),
            "steady_speed_error": np.asarray(
                [row["steady_speed_error"] for row in sorted_rows],
                dtype=float,
            ),
            "drive_torque": np.asarray([row["drive_torque"] for row in sorted_rows], dtype=float),
            "mechanical_brake_torque": np.asarray(
                [row["mechanical_brake_torque"] for row in sorted_rows],
                dtype=float,
            ),
        }

        velocity_summary_series = {
            "velocity_summary_mps": np.asarray(
                [item["velocity_mps"] for item in velocity_summaries],
                dtype=float,
            ),
            "velocity_summary_roadwheel_angle_gradient_rad_per_mps2": np.asarray(
                [item["roadwheel_angle_gradient_rad_per_mps2"] for item in velocity_summaries],
                dtype=float,
            ),
            "velocity_summary_handwheel_angle_gradient_rad_per_mps2": np.asarray(
                [item["handwheel_angle_gradient_rad_per_mps2"] for item in velocity_summaries],
                dtype=float,
            ),
            "velocity_summary_sideslip_gradient_rad_per_mps2": np.asarray(
                [item["sideslip_gradient_rad_per_mps2"] for item in velocity_summaries],
                dtype=float,
            ),
            "velocity_summary_limit_sideslip_gradient_rad_per_mps2": np.asarray(
                [item["limit_sideslip_gradient_rad_per_mps2"] for item in velocity_summaries],
                dtype=float,
            ),
            "velocity_summary_understeer_gradient_rad_per_mps2": np.asarray(
                [item["understeer_gradient_rad_per_mps2"] for item in velocity_summaries],
                dtype=float,
            ),
            "velocity_summary_roll_gradient_rad_per_mps2": np.asarray(
                [item["roll_gradient_rad_per_mps2"] for item in velocity_summaries],
                dtype=float,
            ),
        }

        series: dict[str, Any] = {}
        series.update(row_series)
        series.update(velocity_summary_series)
        series.update(self._build_velocity_isoline_series(rows))

        return {
            "summary": summary,
            "velocity_summaries": velocity_summaries,
            "metrics": metrics,
            "metrics_csv_path": metrics_csv_path,
            "series": series,
            "cases": results,
            "failed_cases": failed_results,
            "n_cases": len(results),
            "n_successful_cases": len(successful_results),
            "n_failed_cases": len(failed_results),
        }


def main(path: str | Path | None = None) -> dict[str, Any]:
    config = load_config(path or DEFAULT_CONFIG_PATH)

    sim_cfg = config.setdefault("simulation", {})
    sim_cfg.setdefault("variable_filter", STEADY_STATE_EVAL_VARIABLE_FILTER)

    result = SteadyStateEvalSim(config).run()

    if config.get("report", {}).get("enabled", True):
        ReportEngine(config).build(result)

    return result


if __name__ == "__main__":
    config_path = sys.argv[1] if len(sys.argv) > 1 else DEFAULT_CONFIG_PATH
    main(config_path)
