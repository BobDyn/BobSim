from __future__ import annotations

import csv
import sys
from pathlib import Path
from typing import Any, cast

import matplotlib as mpl
import numpy as np
import yaml

from _3_StandardSim._modelica_runner import ModelicaRunner
from _0_Utils.reporting.report_engine import ReportEngine

try:
    from scipy.interpolate import UnivariateSpline as _SciPyUnivariateSpline
except Exception as exc:  # pragma: no cover - required dependency
    raise ImportError(
        "SteadyStateEval requires scipy.interpolate.UnivariateSpline. "
        "Install scipy to run the steady-state analysis."
    ) from exc


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


SteadyStateEval_SIGNALS = [
    # Controller/debug signals
    "frSteerCmd",
    "steerRatioEstimate",
    "steerFeedforward",
    "targetAyCmd",
    "targetCurvatureCmd",
    "targetRoadwheelCmd",
    "curvatureErrorRaw",
    "curvatureError",
    "ayErrorRaw",
    "ayError",
    "radError",
    "steerExcess",

    # Standard report signals
    "handwheelAngle",
    "Fz_FL",
    "Fz_FR",
    "Fz_RL",
    "Fz_RR",
    "leftSteerAngle",
    "rightSteerAngle",
    "accY",
    "roll",
    "sideslip",
    "handwheelTorque",
    "velX",
    "velY",
    "yawVel",
]

SteadyStateEval_VARIABLE_FILTER = "|".join(SteadyStateEval_SIGNALS)


def load_config(path: str | Path) -> dict[str, Any]:
    path = Path(path)

    with path.open("r") as f:
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


def _apply_hampel_prefilter(
    y: np.ndarray,
    window_size: int,
    *,
    n_sigmas: float,
) -> np.ndarray:
    y = np.asarray(y, dtype=float).reshape(-1)

    if window_size <= 1 or y.size < 3:
        return y

    window_size = int(window_size)
    if window_size < 3:
        return y

    if window_size > y.size:
        window_size = y.size
    if window_size % 2 == 0:
        window_size -= 1
    if window_size < 3:
        return y

    if n_sigmas <= 0.0:
        return y

    pad = window_size // 2
    padded = np.pad(y, (pad, pad), mode="edge")
    windows = np.lib.stride_tricks.sliding_window_view(padded, window_size)
    med = np.median(windows, axis=-1)
    mad = np.median(np.abs(windows - med[:, None]), axis=-1)
    sigma = 1.4826 * mad
    threshold = n_sigmas * sigma

    filtered = y.copy()
    outliers = np.abs(y - med) > threshold
    filtered[outliers] = med[outliers]
    return filtered


def build_smoothing_spline(
    x: np.ndarray,
    y: np.ndarray,
    *,
    smoothing_fraction: float,
    hampel_window: int = 1,
    hampel_nsigmas: float = 3.0,
):
    x = np.asarray(x, dtype=float).reshape(-1)
    y = np.asarray(y, dtype=float).reshape(-1)

    if x.size != y.size:
        raise ValueError("Fit x/y arrays must have the same length.")
    if x.size < 2:
        raise ValueError("Cannot build a cubic spline from fewer than two points.")

    order = np.argsort(x, kind="mergesort")
    x = x[order]
    y = y[order]

    unique_x, inverse = np.unique(x, return_inverse=True)
    if unique_x.size < x.size:
        counts = np.bincount(inverse)
        sums = np.bincount(inverse, weights=y)
        y = sums / counts
        x = unique_x

    y = _apply_hampel_prefilter(
        y,
        hampel_window,
        n_sigmas=hampel_nsigmas,
    )

    if x.size < 2:
        raise ValueError("Cannot build a smoothing spline from fewer than two unique points.")

    k = min(3, x.size - 1)
    if smoothing_fraction <= 0.0:
        s_value = 0.0
    else:
        s_value = float(max(0.0, smoothing_fraction) * x.size * np.nanvar(y))
    return _SciPyUnivariateSpline(x, y, k=k, s=s_value)


def evaluate_spline(spline: Any, x: np.ndarray, derivative: int = 0) -> np.ndarray:
    return np.asarray(spline(x, nu=derivative), dtype=float)


def build_split_smoothing_curve(
    x: np.ndarray,
    y: np.ndarray,
    *,
    cutoff: float,
    smoothing_fraction: float,
    hampel_window: int = 1,
    hampel_nsigmas: float = 3.0,
) -> dict[str, np.ndarray]:
    x = np.asarray(x, dtype=float).reshape(-1)
    y = np.asarray(y, dtype=float).reshape(-1)

    if x.size != y.size:
        raise ValueError("Fit x/y arrays must have the same length.")
    if x.size < 2:
        raise ValueError("Cannot build a spline from fewer than two points.")
    if cutoff <= 0.0:
        raise ValueError("Split cutoff must be positive.")

    order = np.argsort(x, kind="mergesort")
    x = x[order]
    y = y[order]

    left_mask = x <= -cutoff
    right_mask = x >= cutoff

    if np.count_nonzero(left_mask) < 2 or np.count_nonzero(right_mask) < 2:
        fit = build_smoothing_spline(
            x,
            y,
            smoothing_fraction=smoothing_fraction,
            hampel_window=hampel_window,
            hampel_nsigmas=hampel_nsigmas,
        )
        x_grid = x
        y_grid = evaluate_spline(fit, x_grid)
        dy_grid = evaluate_spline(fit, x_grid, 1)
        return {
            "x_main": x_grid,
            "y_main": y_grid,
            "dy_main": dy_grid,
            "x_bridge": np.array([], dtype=float),
            "y_bridge": np.array([], dtype=float),
            "dy_bridge": np.array([], dtype=float),
        }

    left_fit = build_smoothing_spline(
        x[left_mask],
        y[left_mask],
        smoothing_fraction=smoothing_fraction,
        hampel_window=hampel_window,
        hampel_nsigmas=hampel_nsigmas,
    )
    right_fit = build_smoothing_spline(
        x[right_mask],
        y[right_mask],
        smoothing_fraction=smoothing_fraction,
        hampel_window=hampel_window,
        hampel_nsigmas=hampel_nsigmas,
    )

    left_x = x[left_mask]
    right_x = x[right_mask]
    left_grid = left_x
    right_grid = right_x
    left_y = evaluate_spline(left_fit, left_grid)
    right_y = evaluate_spline(right_fit, right_grid)
    left_dy = evaluate_spline(left_fit, left_grid, 1)
    right_dy = evaluate_spline(right_fit, right_grid, 1)
    left_dy = _apply_hampel_prefilter(
        left_dy,
        hampel_window,
        n_sigmas=hampel_nsigmas,
    )
    right_dy = _apply_hampel_prefilter(
        right_dy,
        hampel_window,
        n_sigmas=hampel_nsigmas,
    )

    left_edge = float(evaluate_spline(left_fit, np.array([-cutoff]), 0)[0])
    right_edge = float(evaluate_spline(right_fit, np.array([cutoff]), 0)[0])
    bridge_x = np.linspace(-cutoff, cutoff, max(9, int(max(2 * cutoff * 8.0, 9.0))))
    bridge_y = np.interp(bridge_x, [-cutoff, cutoff], [left_edge, right_edge])
    bridge_slope = (right_edge - left_edge) / (2.0 * cutoff)
    bridge_dy = np.full_like(bridge_x, bridge_slope)

    return {
        "x_main": np.concatenate([left_grid, [np.nan], right_grid]),
        "y_main": np.concatenate([left_y, [np.nan], right_y]),
        "dy_main": np.concatenate([left_dy, [np.nan], right_dy]),
        "x_bridge": bridge_x,
        "y_bridge": bridge_y,
        "dy_bridge": bridge_dy,
    }


def collapse_duplicate_samples(x: np.ndarray, values: dict[str, np.ndarray]) -> tuple[np.ndarray, dict[str, np.ndarray]]:
    x = np.asarray(x, dtype=float).reshape(-1)
    order = np.argsort(x, kind="mergesort")
    x_sorted = x[order]

    unique_x, inverse = np.unique(x_sorted, return_inverse=True)
    counts = np.bincount(inverse).astype(float)

    collapsed: dict[str, np.ndarray] = {}
    for key, value in values.items():
        arr = np.asarray(value, dtype=float).reshape(-1)[order]
        sums = np.bincount(inverse, weights=arr)
        collapsed[key] = sums / np.maximum(counts, 1.0)

    return unique_x, collapsed


def _as_series(values: Any) -> np.ndarray:
    arr = np.asarray(values, dtype=float)
    if arr.ndim == 0:
        arr = arr.reshape(1)
    return arr.reshape(-1)


def filter_samples_by_axis_magnitude(
    x: np.ndarray,
    values: dict[str, np.ndarray],
    *,
    min_magnitude: float,
) -> tuple[np.ndarray, dict[str, np.ndarray]]:
    x = _as_series(x)
    if min_magnitude < 0.0:
        raise ValueError("Axis magnitude cutoff must be nonnegative.")

    mask = np.abs(x) >= min_magnitude
    if not np.any(mask):
        empty = np.array([], dtype=float)
        return empty, {key: empty.copy() for key in values}

    filtered: dict[str, np.ndarray] = {}
    for key, value in values.items():
        arr = _as_series(value)
        if arr.shape != x.shape:
            raise ValueError(
                "Filtered series must share a common sample axis."
            )
        filtered[key] = arr[mask]

    return x[mask], filtered


class SteadyStateEvalSim:
    def __init__(self, config: dict[str, Any]):
        self.config = config

        sim_cfg = config.setdefault("simulation", {})
        sim_cfg.setdefault("variable_filter", SteadyStateEval_VARIABLE_FILTER)
        backend = sim_cfg.get("backend", "modelica")

        if backend != "modelica":
            raise ValueError(
                "SteadyStateEvalSim currently expects simulation.backend='modelica'. "
                f"Got {backend!r}."
            )

        self.runner = ModelicaRunner.from_config(config)

        self.start_time = float(sim_cfg.get("start_time", 0.0))
        self.stop_time = float(sim_cfg.get("stop_time", 10.0))
        self.steer_start = float(
            _as_override_dict(
                sim_cfg.get("init_parameters", {}),
                name="simulation.init_parameters",
            ).get("steerStart", 0.0)
        )

        if self.stop_time <= self.start_time:
            raise ValueError(
                "simulation.stop_time must be greater than simulation.start_time. "
                f"Got start_time={self.start_time}, stop_time={self.stop_time}."
            )

    # ============================================================
    # CASE GENERATION
    # ============================================================

    def _trim_pre_steer_start(
        self,
        time: np.ndarray,
        *arrays: np.ndarray,
    ) -> tuple[np.ndarray, ...]:
        time = _as_series(time)
        mask = time >= self.steer_start

        if not np.any(mask):
            empty = np.array([], dtype=float)
            return (empty,) + tuple(empty for _ in arrays)

        trimmed: list[np.ndarray] = [time[mask]]
        for arr in arrays:
            arr = _as_series(arr)
            if arr.shape != time.shape:
                raise ValueError(
                    "SteadyStateEval result series must share a common sample axis."
                )
            trimmed.append(arr[mask])

        return tuple(trimmed)

    def build_cases(self) -> list[dict[str, Any]]:
        sweep = self.config["sweep"]
        sim_cfg = self.config.get("simulation", {})

        test_vels_raw = sweep.get("testVels", sweep.get("testVel", 15.0))
        if isinstance(test_vels_raw, (int, float)):
            test_vels = [float(test_vels_raw)]
        elif isinstance(test_vels_raw, (list, tuple, np.ndarray)):
            test_vels = [float(v) for v in test_vels_raw]
        else:
            raise TypeError(
                "sweep.testVels must be a sequence of velocities, or a scalar testVel."
            )

        if not test_vels:
            raise ValueError("sweep.testVels (or testVel) must contain at least one velocity")

        max_ay = float(sweep.get("maxAy", sweep.get("ay_max", 18.0)))

        if max_ay <= 0.0:
            raise ValueError("sweep.maxAy (or ay_max) must be positive")

        # Two open-loop ramp-steer runs per velocity:
        #   1) 0 -> +maxAy
        #   2) 0 -> -maxAy
        #
        # The nominal endpoint and ramp shaping are handled inside VehicleSim.
        target_ays = np.array([max_ay, -max_ay], dtype=float)

        # VehicleSim owns its own defaults.
        #
        # simulation.init_parameters is only for explicit overrides.
        #
        init_parameters = _as_override_dict(
            sim_cfg.get("init_parameters", {}),
            name="simulation.init_parameters",
        )

        cases: list[dict[str, Any]] = []

        for test_vel in test_vels:
            for target_ay_raw in target_ays:
                target_ay = float(target_ay_raw)

                case: dict[str, Any] = {
                    # =========================
                    # Python-only metadata
                    # =========================
                    "_mode": "open_loop_ramp_steer",
                    "_testVel": float(test_vel),
                    "_testAy": target_ay,

                    # =========================
                    # Modelica executable overrides
                    # =========================
                    #
                    # These are the case-specific SteadyStateEval inputs.
                    # Controller behavior is owned by VehicleSim defaults unless
                    # explicitly overridden through simulation.init_parameters.
                    "targetVel": float(test_vel),
                    "targetAy": target_ay,

                    # Handled by ModelicaRunner._build_command(), not written into
                    # the override file.
                    "startTime": self.start_time,
                    "stopTime": self.stop_time,
                }

                case.update(init_parameters)

                cases.append(case)

        return cases

    # ============================================================
    # RUN
    # ============================================================

    def run(self) -> dict[str, Any]:
        cases = self.build_cases()

        results = self.runner.run(
            signals=SteadyStateEval_SIGNALS,
            mode="raw",
            cases=cases,
            execution=self.config.get("execution", {}),
        )

        return self.summarize(results)

    def _build_velocity_isoline_series(
        self,
        raw_results: list[dict[str, Any]],
    ) -> dict[str, dict[float, np.ndarray]]:
        fit_cfg = self.config.get("fit", {})
        report_cfg = self.config.get("report", {})
        sensitivity_cutoff_fraction = float(
            report_cfg.get("sensitivity_cutoff_fraction", 0.95)
        )
        if not (0.0 < sensitivity_cutoff_fraction <= 1.0):
            raise ValueError(
                "report.sensitivity_cutoff_fraction must be within (0, 1]."
            )

        sweep_cfg = self.config.get("sweep", {})
        max_ay_cmd = float(sweep_cfg.get("maxAy", sweep_cfg.get("ay_max", 18.0)))
        sensitivity_cutoff_ay = abs(max_ay_cmd) * sensitivity_cutoff_fraction

        def _velocity_key(result: dict[str, Any]) -> float:
            for key in ("_testVel", "targetVel"):
                value = result.get(key)
                if value is None:
                    continue
                try:
                    return float(value)
                except (TypeError, ValueError):
                    continue
            raise KeyError(
                "SteadyStateEval result is missing velocity metadata "
                "('_testVel' or 'targetVel')."
            )

        grouped_samples: dict[float, dict[str, list[np.ndarray]]] = {}

        for result in raw_results:
            time = _as_series(result.get("time", []))
            if time.size == 0:
                continue

            ay_measured = _as_series(result.get("accY", []))
            ay_cmd = _as_series(result.get("targetAyCmd", []))
            left = _as_series(result.get("leftSteerAngle", []))
            right = _as_series(result.get("rightSteerAngle", []))
            handwheel = _as_series(result.get("handwheelAngle", []))
            steer_excess = _as_series(result.get("steerExcess", []))
            roll = _as_series(result.get("roll", []))
            beta = _as_series(result.get("sideslip", []))
            torque = _as_series(result.get("handwheelTorque", []))
            vel_x = _as_series(result.get("velX", []))
            vel_y = _as_series(result.get("velY", []))
            yaw = _as_series(result.get("yawVel", []))

            if not (
                ay_measured.shape == ay_cmd.shape == left.shape == right.shape
                == handwheel.shape == steer_excess.shape == roll.shape == beta.shape
                == torque.shape == vel_x.shape == vel_y.shape == yaw.shape
            ):
                raise ValueError(
                    "SteadyStateEval result series must share a common sample axis."
                )

            vel_key = _velocity_key(result)

            (
                time,
                ay_measured,
                ay_cmd,
                left,
                right,
                handwheel,
                steer_excess,
                roll,
                beta,
                torque,
                vel_x,
                vel_y,
                yaw,
            ) = self._trim_pre_steer_start(
                time,
                ay_measured,
                ay_cmd,
                left,
                right,
                handwheel,
                steer_excess,
                roll,
                beta,
                torque,
                vel_x,
                vel_y,
                yaw,
            )
            if time.size == 0:
                continue

            roadwheel = 0.5 * (left + right)
            speed = np.sqrt(vel_x**2 + vel_y**2)
            curvature = yaw / np.maximum(speed, 0.1)

            group = grouped_samples.setdefault(
                vel_key,
                {
                    "ay_cmd": [],
                    "ay_measured": [],
                    "roadwheel": [],
                    "handwheel": [],
                    "steer_excess": [],
                    "curvature": [],
                    "roll": [],
                    "sideslip": [],
                    "torque": [],
                },
            )

            group["ay_cmd"].append(ay_cmd)
            group["ay_measured"].append(ay_measured)
            group["roadwheel"].append(roadwheel)
            group["handwheel"].append(handwheel)
            group["steer_excess"].append(steer_excess)
            group["curvature"].append(curvature)
            group["roll"].append(roll)
            group["sideslip"].append(beta)
            group["torque"].append(torque)

        grouped_series: dict[str, dict[float, np.ndarray]] = {
            "ay_measured_isoline": {},
            "ay_measured_raw_isoline": {},
            "ay_measured_bridge_isoline": {},
            "ay_cmd_isoline": {},
            "ay_cmd_raw_isoline": {},
            "roadwheel_isoline": {},
            "roadwheel_raw_isoline": {},
            "roadwheel_bridge_isoline": {},
            "handwheel_isoline": {},
            "handwheel_raw_isoline": {},
            "handwheel_bridge_isoline": {},
            "steer_excess_isoline": {},
            "steer_excess_raw_isoline": {},
            "steer_excess_bridge_isoline": {},
            "curvature_isoline": {},
            "curvature_raw_isoline": {},
            "curvature_bridge_isoline": {},
            "roll_isoline": {},
            "roll_raw_isoline": {},
            "roll_bridge_isoline": {},
            "sideslip_isoline": {},
            "sideslip_raw_isoline": {},
            "sideslip_bridge_isoline": {},
            "torque_isoline": {},
            "torque_raw_isoline": {},
            "torque_bridge_isoline": {},
            "steer_gradient_isoline": {},
            "steer_gradient_bridge_isoline": {},
            "handwheel_gradient_isoline": {},
            "handwheel_gradient_bridge_isoline": {},
            "steer_excess_gradient_isoline": {},
            "steer_excess_gradient_bridge_isoline": {},
            "curvature_gradient_isoline": {},
            "curvature_gradient_bridge_isoline": {},
            "roll_gradient_isoline": {},
            "roll_gradient_bridge_isoline": {},
            "sideslip_gradient_isoline": {},
            "sideslip_gradient_bridge_isoline": {},
        }

        fit_cfg = self.config.get("fit", {})
        ay_min_magnitude = float(fit_cfg.get("ay_min_magnitude", 1.0))
        hampel_window = int(fit_cfg.get("hampel_window", 7))
        hampel_nsigmas = float(fit_cfg.get("hampel_nsigmas", 3.0))
        spline_smoothing_fraction = float(fit_cfg.get("spline_smoothing_fraction", 0.02))

        for vel_key in sorted(grouped_samples):
            group = grouped_samples[vel_key]
            x_parts = group["ay_measured"]
            if not x_parts:
                continue

            x_raw = np.concatenate(x_parts)
            value_map = {
                name: np.concatenate(parts)
                for name, parts in group.items()
                if name != "ay_measured" and parts
            }

            x_raw, value_map = filter_samples_by_axis_magnitude(
                x_raw,
                value_map,
                min_magnitude=ay_min_magnitude,
            )

            if x_raw.size == 0:
                continue

            x_collapsed, values_collapsed = collapse_duplicate_samples(
                x_raw,
                value_map,
            )

            if x_collapsed.size == 0:
                continue

            curves = {
                name: build_split_smoothing_curve(
                    x_collapsed,
                    values,
                    cutoff=ay_min_magnitude,
                    smoothing_fraction=spline_smoothing_fraction,
                    hampel_window=hampel_window,
                    hampel_nsigmas=hampel_nsigmas,
                )
                for name, values in values_collapsed.items()
            }

            grouped_series["ay_measured_isoline"][vel_key] = next(iter(curves.values()))["x_main"]
            grouped_series["ay_measured_bridge_isoline"][vel_key] = next(iter(curves.values()))["x_bridge"]
            grouped_series["ay_measured_raw_isoline"][vel_key] = x_raw
            grouped_series["roadwheel_isoline"][vel_key] = curves["roadwheel"]["y_main"]
            grouped_series["roadwheel_bridge_isoline"][vel_key] = curves["roadwheel"]["y_bridge"]
            grouped_series["roadwheel_raw_isoline"][vel_key] = value_map["roadwheel"]
            grouped_series["handwheel_isoline"][vel_key] = curves["handwheel"]["y_main"]
            grouped_series["handwheel_bridge_isoline"][vel_key] = curves["handwheel"]["y_bridge"]
            grouped_series["handwheel_raw_isoline"][vel_key] = value_map["handwheel"]
            grouped_series["steer_excess_isoline"][vel_key] = curves["steer_excess"]["y_main"]
            grouped_series["steer_excess_bridge_isoline"][vel_key] = curves["steer_excess"]["y_bridge"]
            grouped_series["steer_excess_raw_isoline"][vel_key] = value_map["steer_excess"]
            grouped_series["curvature_isoline"][vel_key] = curves["curvature"]["y_main"]
            grouped_series["curvature_bridge_isoline"][vel_key] = curves["curvature"]["y_bridge"]
            grouped_series["curvature_raw_isoline"][vel_key] = value_map["curvature"]
            grouped_series["roll_isoline"][vel_key] = curves["roll"]["y_main"]
            grouped_series["roll_bridge_isoline"][vel_key] = curves["roll"]["y_bridge"]
            grouped_series["roll_raw_isoline"][vel_key] = value_map["roll"]
            grouped_series["sideslip_isoline"][vel_key] = curves["sideslip"]["y_main"]
            grouped_series["sideslip_bridge_isoline"][vel_key] = curves["sideslip"]["y_bridge"]
            grouped_series["sideslip_raw_isoline"][vel_key] = value_map["sideslip"]
            grouped_series["torque_isoline"][vel_key] = curves["torque"]["y_main"]
            grouped_series["torque_bridge_isoline"][vel_key] = curves["torque"]["y_bridge"]
            grouped_series["torque_raw_isoline"][vel_key] = value_map["torque"]

            grouped_series["steer_gradient_isoline"][vel_key] = curves["roadwheel"]["dy_main"]
            grouped_series["steer_gradient_bridge_isoline"][vel_key] = curves["roadwheel"]["dy_bridge"]
            grouped_series["handwheel_gradient_isoline"][vel_key] = curves["handwheel"]["dy_main"]
            grouped_series["handwheel_gradient_bridge_isoline"][vel_key] = curves["handwheel"]["dy_bridge"]
            grouped_series["steer_excess_gradient_isoline"][vel_key] = curves["steer_excess"]["dy_main"]
            grouped_series["steer_excess_gradient_bridge_isoline"][vel_key] = curves["steer_excess"]["dy_bridge"]
            grouped_series["curvature_gradient_isoline"][vel_key] = curves["curvature"]["dy_main"]
            grouped_series["curvature_gradient_bridge_isoline"][vel_key] = curves["curvature"]["dy_bridge"]
            grouped_series["roll_gradient_isoline"][vel_key] = curves["roll"]["dy_main"]
            grouped_series["roll_gradient_bridge_isoline"][vel_key] = curves["roll"]["dy_bridge"]
            grouped_series["sideslip_gradient_isoline"][vel_key] = curves["sideslip"]["dy_main"]
            grouped_series["sideslip_gradient_bridge_isoline"][vel_key] = curves["sideslip"]["dy_bridge"]

            if sensitivity_cutoff_ay > 0.0:
                cutoff_mask = np.abs(grouped_series["ay_measured_isoline"][vel_key]) > sensitivity_cutoff_ay
                for key in (
                    "steer_gradient_isoline",
                    "handwheel_gradient_isoline",
                    "steer_excess_gradient_isoline",
                    "curvature_gradient_isoline",
                    "roll_gradient_isoline",
                    "sideslip_gradient_isoline",
                ):
                    values = grouped_series[key][vel_key]
                    if values.size:
                        values = values.copy()
                        values[cutoff_mask] = np.nan
                        grouped_series[key][vel_key] = values

        return grouped_series

    # ============================================================
    # METRICS CSV
    # ============================================================

    def write_metrics_csv(self, metrics: list[dict[str, Any]]) -> Path:
        """
        Write one SteadyStateEval metrics CSV beside the PDF report.

        This intentionally exports only the report-level metric rows, not
        sweep data and not raw case data.
        """
        report_cfg = self.config.get("report", {})

        report_path = Path(
            report_cfg.get(
                "output_path",
                "_3_StandardSim/results/steady_state_eval_report.pdf",
            )
        )

        output_dir = report_path.parent
        output_dir.mkdir(parents=True, exist_ok=True)

        output_path = output_dir / f"{report_path.stem}_metrics.csv"

        fieldnames = [
            "standard",
            "metric",
            "value",
            "units",
            "description",
        ]

        with output_path.open("w", newline="") as f:
            writer = csv.DictWriter(f, fieldnames=fieldnames)
            writer.writeheader()
            writer.writerows(metrics)

        return output_path

    # ============================================================
    # SUMMARY
    # ============================================================

    def summarize(self, results: list[dict[str, Any]]) -> dict[str, Any]:
        if not results:
            raise ValueError("No SteadyStateEval results to summarize.")

        failed_results = [r for r in results if r.get("_status") == "failed"]
        successful_results = [r for r in results if r.get("_status") != "failed"]

        if not successful_results:
            failed_labels = ", ".join(
                str(r.get("_case_label", "unknown")) for r in failed_results
            )
            raise RuntimeError(
                "All SteadyStateEval cases failed; nothing to summarize. "
                f"Failed cases: {failed_labels}"
            )

        if failed_results:
            print(
                f"Warning: skipped {len(failed_results)} failed case(s) in summary.",
                flush=True,
            )

        raw_results = successful_results

        def _summarize_raw_results(raw_subset: list[dict[str, Any]]) -> dict[str, Any]:
            def _concat_samples(key: str) -> np.ndarray:
                parts: list[np.ndarray] = []
                for result in raw_subset:
                    time = np.asarray(result.get("time", []), dtype=float).reshape(-1)
                    value = np.asarray(result.get(key, []), dtype=float)
                    if value.ndim == 0:
                        value = value.reshape(1)
                    if time.size == 0 or value.size == 0:
                        continue
                    if value.shape != time.shape:
                        continue
                    mask = time >= self.steer_start
                    if np.any(mask):
                        parts.append(value.reshape(-1)[mask])
                if not parts:
                    return np.array([], dtype=float)
                return np.concatenate(parts)

            def _repeat_case_values(key: str) -> np.ndarray:
                parts: list[np.ndarray] = []
                for result in raw_subset:
                    time = np.asarray(result.get("time", []), dtype=float).reshape(-1)
                    if time.size == 0:
                        continue
                    mask = time >= self.steer_start
                    if not np.any(mask):
                        continue
                    value = float(result[key])
                    parts.append(np.full(np.count_nonzero(mask), value, dtype=float))
                if not parts:
                    return np.array([], dtype=float)
                return np.concatenate(parts)

            left = _concat_samples("leftSteerAngle")
            right = _concat_samples("rightSteerAngle")
            roadwheel = 0.5 * (left + right)
            handwheel = _concat_samples("handwheelAngle")

            ay_measured = _concat_samples("accY")
            roll = _concat_samples("roll")
            beta = _concat_samples("sideslip")
            torque = _concat_samples("handwheelTorque")
            steer_excess = _concat_samples("steerExcess")

            vel_x = _concat_samples("velX")
            vel_y = _concat_samples("velY")
            yaw = _concat_samples("yawVel")

            speed = np.sqrt(vel_x**2 + vel_y**2)
            curvature = yaw / np.maximum(speed, 0.1)

            kappa_cmd = _concat_samples("targetCurvatureCmd")
            target_ay_cmd = _concat_samples("targetAyCmd")
            ay_target = _repeat_case_values("_testAy")

            if ay_measured.size == 0:
                raise ValueError("SteadyStateEval produced no usable Ay samples.")

            ay_param = ay_measured
            idx = np.argsort(ay_param)
            ay_param = ay_param[idx]
            roadwheel = roadwheel[idx]
            handwheel = handwheel[idx]
            curvature = curvature[idx]
            roll = roll[idx]
            beta = beta[idx]
            torque = torque[idx]
            steer_excess = steer_excess[idx]
            kappa_cmd = kappa_cmd[idx]
            ay_target = ay_target[idx]

            fit_cfg = self.config.get("fit", {})
            ay_linear_max = float(fit_cfg.get("ay_linear_max", 6.0))
            ay_min_magnitude = float(fit_cfg.get("ay_min_magnitude", 1.0))
            hampel_window = int(fit_cfg.get("hampel_window", 7))
            hampel_nsigmas = float(fit_cfg.get("hampel_nsigmas", 3.0))

            ay_param, filtered = filter_samples_by_axis_magnitude(
                ay_param,
                {
                    "roadwheel": roadwheel,
                    "handwheel": handwheel,
                    "steer_excess": steer_excess,
                    "curvature": curvature,
                    "roll": roll,
                    "sideslip": beta,
                    "torque": torque,
                },
                min_magnitude=ay_min_magnitude,
            )
            if ay_param.size == 0:
                raise ValueError(
                    "SteadyStateEval produced no usable Ay samples after the configured cutoff."
                )

            roadwheel = filtered["roadwheel"]
            handwheel = filtered["handwheel"]
            curvature = filtered["curvature"]
            roll = filtered["roll"]
            beta = filtered["sideslip"]
            torque = filtered["torque"]
            steer_excess = filtered["steer_excess"]

            analysis_inputs = {
                "roadwheel": roadwheel,
                "handwheel": handwheel,
                "steer_excess": steer_excess,
                "curvature": curvature,
                "roll": roll,
                "sideslip": beta,
                "torque": torque,
            }
            ay_fit_axis, analysis_inputs = collapse_duplicate_samples(
                ay_param,
                analysis_inputs,
            )

            spline_smoothing_fraction = float(fit_cfg.get("spline_smoothing_fraction", 0.02))

            analysis_fits = {
                name: build_smoothing_spline(
                    ay_fit_axis,
                    values,
                    smoothing_fraction=spline_smoothing_fraction,
                    hampel_window=hampel_window,
                    hampel_nsigmas=hampel_nsigmas,
                )
                for name, values in analysis_inputs.items()
            }

            linear_mask = (np.abs(ay_fit_axis) >= ay_min_magnitude) & (
                np.abs(ay_fit_axis) <= ay_linear_max
            )
            roadwheel_grad = _apply_hampel_prefilter(
                evaluate_spline(analysis_fits["roadwheel"], ay_fit_axis, 1),
                hampel_window,
                n_sigmas=hampel_nsigmas,
            )
            handwheel_grad = _apply_hampel_prefilter(
                evaluate_spline(analysis_fits["handwheel"], ay_fit_axis, 1),
                hampel_window,
                n_sigmas=hampel_nsigmas,
            )
            steer_excess_grad = _apply_hampel_prefilter(
                evaluate_spline(analysis_fits["steer_excess"], ay_fit_axis, 1),
                hampel_window,
                n_sigmas=hampel_nsigmas,
            )
            roll_grad = _apply_hampel_prefilter(
                evaluate_spline(analysis_fits["roll"], ay_fit_axis, 1),
                hampel_window,
                n_sigmas=hampel_nsigmas,
            )
            beta_grad = _apply_hampel_prefilter(
                evaluate_spline(analysis_fits["sideslip"], ay_fit_axis, 1),
                hampel_window,
                n_sigmas=hampel_nsigmas,
            )
            if np.count_nonzero(linear_mask) >= 1:
                roadwheel_angle_gradient = float(np.nanmean(roadwheel_grad[linear_mask]))
                handwheel_angle_gradient = float(np.nanmean(handwheel_grad[linear_mask]))
                excess_understeer_gradient = float(np.nanmean(steer_excess_grad[linear_mask]))
                roll_gradient = float(np.nanmean(roll_grad[linear_mask]))
                sideslip_gradient = float(np.nanmean(beta_grad[linear_mask]))
            else:
                roadwheel_angle_gradient = float(np.nanmean(roadwheel_grad))
                handwheel_angle_gradient = float(np.nanmean(handwheel_grad))
                excess_understeer_gradient = float(np.nanmean(steer_excess_grad))
                roll_gradient = float(np.nanmean(roll_grad))
                sideslip_gradient = float(np.nanmean(beta_grad))

            ay_range_measured = (
                float(np.nanmin(ay_param)),
                float(np.nanmax(ay_param)),
            )

            vel_value = raw_subset[0].get("_testVel", raw_subset[0].get("targetVel"))
            return {
                "MeasuredAy_range": ay_range_measured,
                "Ay_range": ay_range_measured,
                "velocity_mps": float(vel_value) if vel_value is not None else np.nan,
                "roadwheel_angle_gradient_rad_per_mps2": roadwheel_angle_gradient,
                "roadwheel_angle_gradient_deg_per_g": float(
                    roadwheel_angle_gradient * 57.2958 * 9.81
                ),
                "handwheel_angle_gradient_rad_per_mps2": handwheel_angle_gradient,
                "handwheel_angle_gradient_deg_per_g": float(
                    handwheel_angle_gradient * 57.2958 * 9.81
                ),
                "roadwheel_steer_sensitivity_rad_per_mps2": roadwheel_angle_gradient,
                "roadwheel_steer_sensitivity_deg_per_g": float(
                    roadwheel_angle_gradient * 57.2958 * 9.81
                ),
                "handwheel_steer_sensitivity_rad_per_mps2": handwheel_angle_gradient,
                "handwheel_steer_sensitivity_deg_per_g": float(
                    handwheel_angle_gradient * 57.2958 * 9.81
                ),
                "sideslip_gradient_rad_per_mps2": sideslip_gradient,
                "sideslip_gradient_deg_per_g": float(
                    sideslip_gradient * 57.2958 * 9.81
                ),
                "understeer_gradient_rad_per_mps2": excess_understeer_gradient,
                "understeer_gradient_deg_per_g": float(
                    excess_understeer_gradient * 57.2958 * 9.81
                ),
                "roll_gradient_rad_per_mps2": roll_gradient,
                "roll_gradient_deg_per_g": float(roll_gradient * 57.2958 * 9.81),
                "handwheel_torque_min_Nm": float(np.nanmin(torque)),
                "handwheel_torque_max_Nm": float(np.nanmax(torque)),
            }

        velocity_groups: dict[float, list[dict[str, Any]]] = {}
        for result in raw_results:
            vel_value = result.get("_testVel", result.get("targetVel"))
            if vel_value is None:
                continue
            velocity_groups.setdefault(float(vel_value), []).append(result)

        velocity_summaries = [
            _summarize_raw_results(group_results)
            for _, group_results in sorted(velocity_groups.items())
            if group_results
        ]

        report_cfg = self.config.get("report", {})
        metric_target_velocity = float(report_cfg.get("metric_target_velocity_mps", 15.0))
        metric_summary = min(
            velocity_summaries,
            key=lambda item: abs(float(item.get("velocity_mps", np.nan)) - metric_target_velocity),
        ) if velocity_summaries else None
        if metric_summary is None:
            metric_summary = {
                "velocity_mps": np.nan,
                "MeasuredAy_range": (np.nan, np.nan),
                "roadwheel_angle_gradient_rad_per_mps2": np.nan,
                "roadwheel_angle_gradient_deg_per_g": np.nan,
                "handwheel_angle_gradient_rad_per_mps2": np.nan,
                "handwheel_angle_gradient_deg_per_g": np.nan,
                "sideslip_gradient_rad_per_mps2": np.nan,
                "sideslip_gradient_deg_per_g": np.nan,
                "understeer_gradient_rad_per_mps2": np.nan,
                "understeer_gradient_deg_per_g": np.nan,
                "roll_gradient_deg_per_g": np.nan,
                "handwheel_torque_min_Nm": np.nan,
                "handwheel_torque_max_Nm": np.nan,
            }

        def _velocity_trend(metric_key: str) -> tuple[float, float]:
            if len(velocity_summaries) < 2:
                return np.nan, np.nan
            vel = np.asarray([float(item["velocity_mps"]) for item in velocity_summaries], dtype=float)
            vals = np.asarray([float(item[metric_key]) for item in velocity_summaries], dtype=float)
            coeffs = np.polyfit(vel, vals, 1)
            return float(coeffs[0]), float(coeffs[1])

        roadwheel_trend, _ = _velocity_trend("roadwheel_angle_gradient_deg_per_g")
        handwheel_trend, _ = _velocity_trend("handwheel_angle_gradient_deg_per_g")
        sideslip_trend, _ = _velocity_trend("sideslip_gradient_deg_per_g")
        understeer_trend, _ = _velocity_trend("understeer_gradient_deg_per_g")
        roll_trend, _ = _velocity_trend("roll_gradient_deg_per_g")

        def _concat_samples(key: str) -> np.ndarray:
            parts: list[np.ndarray] = []
            for result in raw_results:
                time = np.asarray(result.get("time", []), dtype=float).reshape(-1)
                value = np.asarray(result.get(key, []), dtype=float)
                if value.ndim == 0:
                    value = value.reshape(1)
                if time.size == 0 or value.size == 0:
                    continue
                if value.shape != time.shape:
                    continue
                mask = time >= self.steer_start
                if np.any(mask):
                    parts.append(value.reshape(-1)[mask])
            if not parts:
                return np.array([], dtype=float)
            return np.concatenate(parts)

        def _repeat_case_values(key: str) -> np.ndarray:
            parts: list[np.ndarray] = []
            for result in raw_results:
                time = np.asarray(result.get("time", []), dtype=float).reshape(-1)
                if time.size == 0:
                    continue
                mask = time >= self.steer_start
                if not np.any(mask):
                    continue
                value = float(result[key])
                parts.append(np.full(np.count_nonzero(mask), value, dtype=float))
            if not parts:
                return np.array([], dtype=float)
            return np.concatenate(parts)

        left = _concat_samples("leftSteerAngle")
        right = _concat_samples("rightSteerAngle")
        roadwheel = 0.5 * (left + right)
        handwheel = _concat_samples("handwheelAngle")

        ay = _concat_samples("accY")
        roll = _concat_samples("roll")
        beta = _concat_samples("sideslip")
        torque = _concat_samples("handwheelTorque")
        steer_excess = _concat_samples("steerExcess")

        vel_x = _concat_samples("velX")
        vel_y = _concat_samples("velY")
        yaw = _concat_samples("yawVel")

        speed = np.sqrt(vel_x**2 + vel_y**2)
        curvature = yaw / np.maximum(speed, 0.1)

        kappa_cmd = _concat_samples("targetCurvatureCmd")
        # Controller/debug arrays.
        fr_steer_cmd = _concat_samples("frSteerCmd")
        steer_ratio_estimate = _concat_samples("steerRatioEstimate")
        steer_feedforward = _concat_samples("steerFeedforward")
        target_ay_cmd = _concat_samples("targetAyCmd")
        target_roadwheel_cmd = _concat_samples("targetRoadwheelCmd")
        ay_error_raw = _concat_samples("ayErrorRaw")
        ay_error = _concat_samples("ayError")
        rad_error = _concat_samples("radError")
        ay_target = _repeat_case_values("_testAy")

        if ay.size == 0:
            raise ValueError("SteadyStateEval produced no usable Ay samples.")

        # Use measured Ay as the common analysis axis.
        ay_param = ay

        idx = np.argsort(ay_param)

        ay_param = ay_param[idx]
        roadwheel = roadwheel[idx]
        handwheel = handwheel[idx]
        curvature = curvature[idx]
        roll = roll[idx]
        beta = beta[idx]
        torque = torque[idx]
        steer_excess = steer_excess[idx]
        kappa_cmd = kappa_cmd[idx]
        speed = speed[idx]
        yaw = yaw[idx]

        fr_steer_cmd = fr_steer_cmd[idx]
        steer_ratio_estimate = steer_ratio_estimate[idx]
        steer_feedforward = steer_feedforward[idx]
        target_ay_cmd = target_ay_cmd[idx]
        target_roadwheel_cmd = target_roadwheel_cmd[idx]
        ay_error_raw = ay_error_raw[idx]
        ay_error = ay_error[idx]
        rad_error = rad_error[idx]
        ay_target = ay_target[idx]

        fit_cfg = self.config.get("fit", {})
        ay_linear_max = float(fit_cfg.get("ay_linear_max", 6.0))
        ay_min_magnitude = float(fit_cfg.get("ay_min_magnitude", 1.0))
        hampel_window = int(fit_cfg.get("hampel_window", 7))
        hampel_nsigmas = float(fit_cfg.get("hampel_nsigmas", 3.0))

        ay_param, filtered = filter_samples_by_axis_magnitude(
            ay_param,
                {
                    "roadwheel": roadwheel,
                    "handwheel": handwheel,
                    "curvature": curvature,
                    "roll": roll,
                    "sideslip": beta,
                    "torque": torque,
                    "steer_excess": steer_excess,
                    "kappa_cmd": kappa_cmd,
                    "speed": speed,
                    "yaw": yaw,
                    "fr_steer_cmd": fr_steer_cmd,
                    "steer_ratio_estimate": steer_ratio_estimate,
                    "steer_feedforward": steer_feedforward,
                "target_ay_cmd": target_ay_cmd,
                "target_roadwheel_cmd": target_roadwheel_cmd,
                "ay_error_raw": ay_error_raw,
                "ay_error": ay_error,
                "rad_error": rad_error,
                "ay_target": ay_target,
            },
            min_magnitude=ay_min_magnitude,
        )
        if ay_param.size == 0:
            raise ValueError(
                "SteadyStateEval produced no usable Ay samples after the configured cutoff."
            )

        roadwheel = filtered["roadwheel"]
        handwheel = filtered["handwheel"]
        curvature = filtered["curvature"]
        roll = filtered["roll"]
        beta = filtered["sideslip"]
        torque = filtered["torque"]
        steer_excess = filtered["steer_excess"]
        kappa_cmd = filtered["kappa_cmd"]
        speed = filtered["speed"]
        yaw = filtered["yaw"]
        fr_steer_cmd = filtered["fr_steer_cmd"]
        steer_ratio_estimate = filtered["steer_ratio_estimate"]
        steer_feedforward = filtered["steer_feedforward"]
        target_ay_cmd = filtered["target_ay_cmd"]
        target_roadwheel_cmd = filtered["target_roadwheel_cmd"]
        ay_error_raw = filtered["ay_error_raw"]
        ay_error = filtered["ay_error"]
        rad_error = filtered["rad_error"]
        ay_target = filtered["ay_target"]
        ay = ay_param

        # Build smoothing-spline analysis channels so downstream fits and
        # gradients are evaluated from clean response curves rather than raw
        # solver samples.
        analysis_inputs = {
            "roadwheel": roadwheel,
            "handwheel": handwheel,
            "steer_excess": steer_excess,
            "curvature": curvature,
            "roll": roll,
            "sideslip": beta,
            "torque": torque,
        }
        analysis_fit_axis, analysis_inputs = collapse_duplicate_samples(
            ay_param,
            analysis_inputs,
        )

        ay_error_cmd = target_ay_cmd - ay
        ay_error_cmd_abs = np.abs(ay_error_cmd)

        steer_plot_idx = np.argsort(ay_param)
        ay_cmd_plot = ay_param[steer_plot_idx]
        roadwheel_plot = roadwheel[steer_plot_idx]
        handwheel_plot = handwheel[steer_plot_idx]

        eps = 1.0e-9

        curvature_error_pct = 100.0 * (curvature - kappa_cmd) / np.maximum(
            np.abs(kappa_cmd),
            eps,
        )

        spline_smoothing_fraction = float(fit_cfg.get("spline_smoothing_fraction", 0.02))

        analysis_fits = {
            name: build_smoothing_spline(
                analysis_fit_axis,
                values,
                smoothing_fraction=spline_smoothing_fraction,
                hampel_window=hampel_window,
                hampel_nsigmas=hampel_nsigmas,
            )
            for name, values in analysis_inputs.items()
        }

        roadwheel = evaluate_spline(analysis_fits["roadwheel"], ay_param)
        handwheel = evaluate_spline(analysis_fits["handwheel"], ay_param)
        curvature = evaluate_spline(analysis_fits["curvature"], ay_param)
        roll = evaluate_spline(analysis_fits["roll"], ay_param)
        beta = evaluate_spline(analysis_fits["sideslip"], ay_param)
        torque = evaluate_spline(analysis_fits["torque"], ay_param)

        linear_mask = (np.abs(analysis_fit_axis) >= ay_min_magnitude) & (
            np.abs(analysis_fit_axis) <= ay_linear_max
        )

        steer_grad = _apply_hampel_prefilter(
            evaluate_spline(analysis_fits["roadwheel"], analysis_fit_axis, 1),
            hampel_window,
            n_sigmas=hampel_nsigmas,
        )
        handwheel_grad = _apply_hampel_prefilter(
            evaluate_spline(analysis_fits["handwheel"], analysis_fit_axis, 1),
            hampel_window,
            n_sigmas=hampel_nsigmas,
        )
        steer_excess_grad = _apply_hampel_prefilter(
            evaluate_spline(analysis_fits["steer_excess"], analysis_fit_axis, 1),
            hampel_window,
            n_sigmas=hampel_nsigmas,
        )
        curv_grad = _apply_hampel_prefilter(
            evaluate_spline(analysis_fits["curvature"], analysis_fit_axis, 1),
            hampel_window,
            n_sigmas=hampel_nsigmas,
        )
        beta_grad = _apply_hampel_prefilter(
            evaluate_spline(analysis_fits["sideslip"], analysis_fit_axis, 1),
            hampel_window,
            n_sigmas=hampel_nsigmas,
        )
        roll_grad = _apply_hampel_prefilter(
            evaluate_spline(analysis_fits["roll"], analysis_fit_axis, 1),
            hampel_window,
            n_sigmas=hampel_nsigmas,
        )
        if np.count_nonzero(linear_mask) >= 1:
            roadwheel_angle_gradient = float(np.nanmean(steer_grad[linear_mask]))
            handwheel_angle_gradient = float(np.nanmean(handwheel_grad[linear_mask]))
            roll_gradient = float(np.nanmean(roll_grad[linear_mask]))
            sideslip_gradient = float(np.nanmean(beta_grad[linear_mask]))
            excess_understeer_gradient = float(np.nanmean(steer_excess_grad[linear_mask]))
        else:
            roadwheel_angle_gradient = float(np.nanmean(steer_grad))
            handwheel_angle_gradient = float(np.nanmean(handwheel_grad))
            roll_gradient = float(np.nanmean(roll_grad))
            sideslip_gradient = float(np.nanmean(beta_grad))
            excess_understeer_gradient = float(np.nanmean(steer_excess_grad))

        steer_fit = evaluate_spline(analysis_fits["roadwheel"], ay_param)
        handwheel_fit = evaluate_spline(analysis_fits["handwheel"], ay_param)
        steer_excess_fit = evaluate_spline(analysis_fits["steer_excess"], ay_param)

        ay_range_measured: tuple[float, float] = (
            float(np.nanmin(ay)),
            float(np.nanmax(ay)),
        )

        summary: dict[str, Any] = {
            "MeasuredAy_range": ay_range_measured,
            "Ay_range": ay_range_measured,
            "roadwheel_angle_gradient_rad_per_mps2": roadwheel_angle_gradient,
            "roadwheel_angle_gradient_deg_per_g": float(
                roadwheel_angle_gradient * 57.2958 * 9.81
            ),
            "handwheel_angle_gradient_rad_per_mps2": handwheel_angle_gradient,
            "handwheel_angle_gradient_deg_per_g": float(
                handwheel_angle_gradient * 57.2958 * 9.81
            ),
            "roadwheel_steer_sensitivity_rad_per_mps2": roadwheel_angle_gradient,
            "roadwheel_steer_sensitivity_deg_per_g": float(
                roadwheel_angle_gradient * 57.2958 * 9.81
            ),
            "handwheel_steer_sensitivity_rad_per_mps2": handwheel_angle_gradient,
            "handwheel_steer_sensitivity_deg_per_g": float(
                handwheel_angle_gradient * 57.2958 * 9.81
            ),
            "sideslip_gradient_rad_per_mps2": sideslip_gradient,
            "sideslip_gradient_deg_per_g": float(
                sideslip_gradient * 57.2958 * 9.81
            ),
            "understeer_gradient_rad_per_mps2": excess_understeer_gradient,
            "understeer_gradient_deg_per_g": float(
                excess_understeer_gradient * 57.2958 * 9.81
            ),
            "excess_understeer_gradient_rad_per_mps2": excess_understeer_gradient,
            "excess_understeer_gradient_deg_per_g": float(
                excess_understeer_gradient * 57.2958 * 9.81
            ),
            "roll_gradient_rad_per_mps2": roll_gradient,
            "roll_gradient_deg_per_g": float(roll_gradient * 57.2958 * 9.81),
            "handwheel_torque_min_Nm": float(np.nanmin(torque)),
            "handwheel_torque_max_Nm": float(np.nanmax(torque)),
            "max_curvature_error_pct": float(
                np.nanmax(np.abs(curvature_error_pct))
            ),
            "mean_curvature_error_pct": float(
                np.nanmean(np.abs(curvature_error_pct))
            ),
            "max_abs_rad_error": float(np.nanmax(np.abs(rad_error))),
            "mean_abs_rad_error": float(np.nanmean(np.abs(rad_error))),
            "roadwheel_angle_gradient_velocity_slope_deg_per_g_per_mps": roadwheel_trend,
            "handwheel_angle_gradient_velocity_slope_deg_per_g_per_mps": handwheel_trend,
            "sideslip_gradient_velocity_slope_deg_per_g_per_mps": sideslip_trend,
            "understeer_gradient_velocity_slope_deg_per_g_per_mps": understeer_trend,
            "roll_gradient_velocity_slope_deg_per_g_per_mps": roll_trend,
        }

        metrics: list[dict[str, Any]] = [
            {
                "standard": "SteadyStateEval",
                "metric": "metric_target_velocity_mps",
                "value": metric_target_velocity,
                "units": "m/s",
                "description": "Target velocity used to select the exported metric table",
            },
            {
                "standard": "SteadyStateEval",
                "metric": "metric_source_velocity_mps",
                "value": metric_summary["velocity_mps"],
                "units": "m/s",
                "description": "Velocity nearest the target used for the exported metric table",
            },
            {
                "standard": "SteadyStateEval",
                "metric": "ay_min",
                "value": float(metric_summary["MeasuredAy_range"][0]),
                "units": "m/s^2",
                "description": "Minimum measured lateral acceleration",
            },
            {
                "standard": "SteadyStateEval",
                "metric": "ay_max",
                "value": float(metric_summary["MeasuredAy_range"][1]),
                "units": "m/s^2",
                "description": "Maximum measured lateral acceleration",
            },
            {
                "standard": "SteadyStateEval",
                "metric": "roadwheel_angle_gradient_rad_per_mps2",
                "value": metric_summary["roadwheel_angle_gradient_rad_per_mps2"],
                "units": "rad/(m/s^2)",
                "description": "Mean roadwheel angle gradient over the linear region",
            },
            {
                "standard": "SteadyStateEval",
                "metric": "roadwheel_angle_gradient_deg_per_g",
                "value": metric_summary["roadwheel_angle_gradient_deg_per_g"],
                "units": "deg/g",
                "description": "Mean roadwheel angle gradient over the linear region",
            },
            {
                "standard": "SteadyStateEval",
                "metric": "handwheel_angle_gradient_rad_per_mps2",
                "value": metric_summary["handwheel_angle_gradient_rad_per_mps2"],
                "units": "rad/(m/s^2)",
                "description": "Mean handwheel angle gradient over the linear region",
            },
            {
                "standard": "SteadyStateEval",
                "metric": "handwheel_angle_gradient_deg_per_g",
                "value": metric_summary["handwheel_angle_gradient_deg_per_g"],
                "units": "deg/g",
                "description": "Mean handwheel angle gradient over the linear region",
            },
            {
                "standard": "SteadyStateEval",
                "metric": "sideslip_gradient_rad_per_mps2",
                "value": metric_summary["sideslip_gradient_rad_per_mps2"],
                "units": "rad/(m/s^2)",
                "description": "Mean sideslip gradient over the linear region",
            },
            {
                "standard": "SteadyStateEval",
                "metric": "sideslip_gradient_deg_per_g",
                "value": metric_summary["sideslip_gradient_deg_per_g"],
                "units": "deg/g",
                "description": "Mean sideslip gradient over the linear region",
            },
            {
                "standard": "SteadyStateEval",
                "metric": "understeer_gradient_rad_per_mps2",
                "value": metric_summary["understeer_gradient_rad_per_mps2"],
                "units": "rad/(m/s^2)",
                "description": "Mean steer excess derivative over the linear region",
            },
            {
                "standard": "SteadyStateEval",
                "metric": "understeer_gradient_deg_per_g",
                "value": metric_summary["understeer_gradient_deg_per_g"],
                "units": "deg/g",
                "description": "Mean steer excess derivative over the linear region",
            },
            {
                "standard": "SteadyStateEval",
                "metric": "roll_gradient_deg_per_g",
                "value": metric_summary["roll_gradient_deg_per_g"],
                "units": "deg/g",
                "description": "Mean roll gradient over the linear region",
            },
            {
                "standard": "SteadyStateEval",
                "metric": "handwheel_torque_min",
                "value": metric_summary["handwheel_torque_min_Nm"],
                "units": "N*m",
                "description": "Minimum handwheel torque over SteadyStateEval sweep",
            },
            {
                "standard": "SteadyStateEval",
                "metric": "handwheel_torque_max",
                "value": metric_summary["handwheel_torque_max_Nm"],
                "units": "N*m",
                "description": "Maximum handwheel torque over SteadyStateEval sweep",
            },
            {
                "standard": "SteadyStateEval",
                "metric": "roadwheel_angle_gradient_velocity_slope_deg_per_g_per_mps",
                "value": roadwheel_trend,
                "units": "deg/g per m/s",
                "description": "Linear fit slope of roadwheel angle gradient versus velocity",
            },
            {
                "standard": "SteadyStateEval",
                "metric": "handwheel_angle_gradient_velocity_slope_deg_per_g_per_mps",
                "value": handwheel_trend,
                "units": "deg/g per m/s",
                "description": "Linear fit slope of handwheel angle gradient versus velocity",
            },
            {
                "standard": "SteadyStateEval",
                "metric": "sideslip_gradient_velocity_slope_deg_per_g_per_mps",
                "value": sideslip_trend,
                "units": "deg/g per m/s",
                "description": "Linear fit slope of sideslip gradient versus velocity",
            },
            {
                "standard": "SteadyStateEval",
                "metric": "understeer_gradient_velocity_slope_deg_per_g_per_mps",
                "value": understeer_trend,
                "units": "deg/g per m/s",
                "description": "Linear fit slope of understeer gradient versus velocity",
            },
            {
                "standard": "SteadyStateEval",
                "metric": "roll_gradient_velocity_slope_deg_per_g_per_mps",
                "value": roll_trend,
                "units": "deg/g per m/s",
                "description": "Linear fit slope of roll gradient versus velocity",
            },
        ]

        metrics_csv_path = self.write_metrics_csv(metrics)

        print(f"📊 SteadyStateEval metrics CSV written: {metrics_csv_path}")

        velocity_summary_series = {
            "velocity_summary_mps": np.asarray(
                [summary["velocity_mps"] for summary in velocity_summaries],
                dtype=float,
            ),
            "velocity_summary_roadwheel_angle_gradient_rad_per_mps2": np.asarray(
                [summary["roadwheel_angle_gradient_rad_per_mps2"] for summary in velocity_summaries],
                dtype=float,
            ),
            "velocity_summary_handwheel_angle_gradient_rad_per_mps2": np.asarray(
                [summary["handwheel_angle_gradient_rad_per_mps2"] for summary in velocity_summaries],
                dtype=float,
            ),
            "velocity_summary_sideslip_gradient_rad_per_mps2": np.asarray(
                [summary["sideslip_gradient_rad_per_mps2"] for summary in velocity_summaries],
                dtype=float,
            ),
            "velocity_summary_understeer_gradient_rad_per_mps2": np.asarray(
                [summary["understeer_gradient_rad_per_mps2"] for summary in velocity_summaries],
                dtype=float,
            ),
            "velocity_summary_roll_gradient_rad_per_mps2": np.asarray(
                [summary["roll_gradient_rad_per_mps2"] for summary in velocity_summaries],
                dtype=float,
            ),
        }

        series = {
            "ay_cmd": ay_param,
            "ay_cmd_plot": ay_cmd_plot,
            "ay_measured": ay,
            "ay_target": ay_target,
            "roadwheel": roadwheel,
            "roadwheel_plot": roadwheel_plot,
            "handwheel": handwheel,
            "handwheel_plot": handwheel_plot,
            "steer_excess": steer_excess,
            "curvature": curvature,
            "curvature_cmd": kappa_cmd,
            "curvature_error_pct": curvature_error_pct,
            "roll": roll,
            "sideslip": beta,
            "torque": torque,
            "speed": speed,
            "yaw": yaw,
            "steer_fit": steer_fit,
            "handwheel_fit": handwheel_fit,
            "steer_excess_fit": steer_excess_fit,
            "steer_gradient": steer_grad,
            "handwheel_gradient": handwheel_grad,
            "steer_excess_gradient": steer_excess_grad,
            "curvature_gradient": curv_grad,
            "sideslip_gradient": beta_grad,
            "roll_gradient": roll_grad,

            # Controller/debug series
            "fr_steer_cmd": fr_steer_cmd,
            "steer_ratio_estimate": steer_ratio_estimate,
            "steer_feedforward": steer_feedforward,
            "target_ay_cmd": target_ay_cmd,
            "target_roadwheel_cmd": target_roadwheel_cmd,
            "ay_error_cmd": ay_error_cmd,
            "ay_error_cmd_abs": ay_error_cmd_abs,
            "ay_error_raw": ay_error_raw,
            "ay_error": ay_error,
            "rad_error": rad_error,
        }

        series.update(velocity_summary_series)
        series.update(self._build_velocity_isoline_series(raw_results))

        return {
            "summary": summary,
            "velocity_summaries": velocity_summaries,
            "metrics": metrics,
            "metrics_csv_path": metrics_csv_path,
            "series": series,
            "cases": results,
            "failed_cases": failed_results,
            "n_cases": len(results) + len(failed_results),
            "n_successful_cases": len(results),
            "n_failed_cases": len(failed_results),
        }


def main(path: str | Path | None = None) -> dict[str, Any]:
    config_path = Path(path) if path is not None else DEFAULT_CONFIG_PATH
    config = load_config(config_path)

    result = SteadyStateEvalSim(config).run()

    if config.get("report", {}).get("enabled", True):
        ReportEngine(config).build(result)

    return result


if __name__ == "__main__":
    path = sys.argv[1] if len(sys.argv) > 1 else None
    main(path)
