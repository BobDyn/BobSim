from __future__ import annotations

import csv
import copy
import re
import sys
from pathlib import Path
from typing import Any, Sequence, cast

import numpy as np
import yaml

from common import config_io
from common.vehicle_io import repo_root
from common.reporting.report_engine import ReportEngine
from simulations.response.mbd._modelica_runner import ModelicaRunner
from simulations.response.mbd.four_post import static_balance


SEED_CONFIG_PATH = Path("simulations/response/mbd/four_post/four_post_eval_config.yml")
DEFAULT_CONFIG_PATH = config_io.resolve(SEED_CONFIG_PATH)
DEFAULT_BUILD_DIR = "simulations/mbd/BuildBobLib/FourPostSim"
DEFAULT_EXEC_NAME = "BobLib.Experiments.Standards.FourPostSim"
FOUR_POST_SIMULATION = {
    "build_dir": DEFAULT_BUILD_DIR,
    "exec_name": DEFAULT_EXEC_NAME,
    "solver": "dassl",
    "stepSize": 0.5,
    "output_format": "csv",
    "log_level": "LOG_STATS,LOG_SOLVER,LOG_INIT,LOG_STDOUT,LOG_ASSERT",
    "extra_args": ["-jacobian=internalNumerical"],
    "no_grid": False,
    "no_event_emit": True,
}
DEFAULT_METRICS_CSV_PATH = "simulations/mbd/results/four_post_eval_report_metrics.csv"
REPO_ROOT = repo_root()
ACTIVE_VEHICLE_YAML_CANDIDATES = (REPO_ROOT / "vehicle.yml",)
GRAVITY_MPS2 = 9.80665
FOUR_POST_POSE_STEP_S = 5.0
FOUR_POST_HEAVE_START_S = 2.0
FOUR_POST_HEAVE_POSE_COUNT = 11
FOUR_POST_HEAVE_END_S = FOUR_POST_HEAVE_START_S + FOUR_POST_POSE_STEP_S * (FOUR_POST_HEAVE_POSE_COUNT + 1)
FOUR_POST_ROLL_START_S = FOUR_POST_HEAVE_END_S + 1.0
FOUR_POST_ROLL_POSE_COUNT = 11
FOUR_POST_STOP_TIME_S = FOUR_POST_ROLL_START_S + FOUR_POST_POSE_STEP_S * FOUR_POST_ROLL_POSE_COUNT
FOUR_POST_SAMPLE_WINDOW_S = 0.5
FOUR_POST_FORCE_SAMPLE_FRACTION = 0.5
FOUR_POST_SIGNAL_ABS_LIMIT = 1e9
FOUR_POST_RATIO_ABS_LIMIT = 1e4
FOUR_POST_FRACTION_ABS_LIMIT = 10.0
FOUR_POST_PERCENT_ABS_LIMIT = 1e3
FOUR_POST_MOTION_RATIO_ABS_LIMIT = 20.0
FOUR_POST_DEFAULT_ROLL_MAGNITUDE_RAD = 0.01308996938995747
FOUR_POST_LEGACY_ROLL_MAGNITUDE_RAD = 0.035
FOUR_POST_MIN_CONTACT_FZ_N = 1.0
FOUR_POST_ANTI_FORCE_PATH = "contact_patch_upright_reacted"
# Plots whose meaning or label changed. Older app-data copies take them from the seed.
FOUR_POST_SEED_OWNED_PLOTS = ("jacking_heave", "jacking_roll", "fbrc_roll", "lltd_roll")
STATUS_ORDER = ("ok", "partial", "invalid")


FOUR_POST_EVAL_SIGNALS = [
    "frKnC.heave",
    "frKnC.roll",
    "frKnC.fx",
    "frKnC.fy",
    "frKnC.leftSpringLength",
    "frKnC.leftFz",
    "frKnC.leftGamma",
    "frKnC.leftToe",
    "frKnC.leftCaster",
    "frKnC.leftKpi",
    "frKnC.leftMechTrail",
    "frKnC.leftMechScrub",
    "frKnC.rightSpringLength",
    "frKnC.rightFz",
    "frKnC.rightGamma",
    "frKnC.rightToe",
    "frKnC.rightCaster",
    "frKnC.rightKpi",
    "frKnC.rightMechTrail",
    "frKnC.rightMechScrub",
    "frKnC.jackingForce",
    "frKnC.stabarAngle",
    "rrKnC.heave",
    "rrKnC.roll",
    "rrKnC.fx",
    "rrKnC.fy",
    "rrKnC.leftSpringLength",
    "rrKnC.leftFz",
    "rrKnC.leftGamma",
    "rrKnC.leftToe",
    "rrKnC.leftCaster",
    "rrKnC.leftKpi",
    "rrKnC.leftMechTrail",
    "rrKnC.leftMechScrub",
    "rrKnC.rightSpringLength",
    "rrKnC.rightFz",
    "rrKnC.rightGamma",
    "rrKnC.rightToe",
    "rrKnC.rightCaster",
    "rrKnC.rightKpi",
    "rrKnC.rightMechTrail",
    "rrKnC.rightMechScrub",
    "rrKnC.jackingForce",
    "rrKnC.stabarAngle",
]
FOUR_POST_STATIC_BALANCE_AXLES = (
    ("front", "frKnC", "frAxleDW", "frChassisActuator"),
    ("rear", "rrKnC", "rrAxleDW", "rrChassisActuator"),
)
FOUR_POST_EVAL_SIGNALS += static_balance.executed_signals(
    [(axle, actuator) for _, _, axle, actuator in FOUR_POST_STATIC_BALANCE_AXLES]
)
FOUR_POST_ANTI_PATH_POINTS = (("contact_patch", "CP"), ("wheel_center", "Tire.chassisFrame"))


def _anti_path_x_signals(axle: str, point: str) -> list[str]:
    return [f"{axle}.{side}{point}.r_0[1]" for side in ("left", "right")]


FOUR_POST_EVAL_SIGNALS += [
    signal
    for _, _, axle, _ in FOUR_POST_STATIC_BALANCE_AXLES
    for _, point in FOUR_POST_ANTI_PATH_POINTS
    for signal in _anti_path_x_signals(axle, point)
]

# The filter is a regular expression, and the executed-signal names contain brackets.
FOUR_POST_EVAL_VARIABLE_FILTER = "|".join(re.escape(signal) for signal in FOUR_POST_EVAL_SIGNALS)


def load_config(path: str | Path) -> dict[str, Any]:
    path = Path(path)
    with path.open("r", encoding="utf-8") as f:
        config = yaml.safe_load(f)

    if config is None:
        raise ValueError(f"Config file is empty: {path}")
    if not isinstance(config, dict):
        raise TypeError(f"Expected YAML config to contain a mapping at top level: {path}")

    return cast(dict[str, Any], config)


def _seed_plot_configs() -> dict[str, Any]:
    plots = _as_mapping(load_config(REPO_ROOT / SEED_CONFIG_PATH).get("plots"), name="plots")
    return {key: copy.deepcopy(plots[key]) for key in FOUR_POST_SEED_OWNED_PLOTS}


def _normalize_four_post_report_config(config: dict[str, Any]) -> dict[str, Any]:
    """Keep older app-data report configs aligned with current FourPost semantics."""
    report_cfg = config.setdefault("report", {})
    if isinstance(report_cfg, dict):
        report_cfg.setdefault("raw_time_series_appendix", False)
    procedure_cfg = config.setdefault("procedure", {})
    if isinstance(procedure_cfg, dict):
        try:
            roll_magnitude = float(procedure_cfg.get("rollMagnitude", 0.0))
        except (TypeError, ValueError):
            roll_magnitude = float("nan")
        if np.isclose(roll_magnitude, FOUR_POST_LEGACY_ROLL_MAGNITUDE_RAD):
            procedure_cfg["rollMagnitude"] = FOUR_POST_DEFAULT_ROLL_MAGNITUDE_RAD
    plots_cfg = config.setdefault("plots", {})
    if isinstance(plots_cfg, dict):
        plots_cfg.update(_seed_plot_configs())
    return config


def _as_mapping(value: Any, *, name: str) -> dict[str, Any]:
    if value is None:
        return {}
    if not isinstance(value, dict):
        raise TypeError(f"Expected {name} to be a mapping if provided.")
    return cast(dict[str, Any], value)


def write_metrics_csv(
    summary: dict[str, Any],
    path: str | Path,
    status: dict[str, str] | None = None,
) -> Path:
    """Write metric, value and status. A metric without a given status is ok, or invalid when NaN."""
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.unlink(missing_ok=True)
    status = status or {}

    with path.open("w", newline="", encoding="utf-8") as f:
        writer = csv.writer(f, lineterminator="\n")
        writer.writerow(["metric", "value", "status"])
        for key in sorted(summary):
            value = summary[key]
            missing = isinstance(value, float) and np.isnan(value)
            writer.writerow([key, "" if missing else value, status.get(key, "invalid" if missing else "ok")])

    return path


def _coverage_status(n_valid: int, n_total: int) -> str:
    if n_total > 0 and n_valid == n_total:
        return "ok"
    return "partial" if n_valid > 0 else "invalid"


def _worst_status(*statuses: str) -> str:
    return max(statuses, key=STATUS_ORDER.index)


def _load_active_vehicle_yaml() -> dict[str, Any]:
    for path in ACTIVE_VEHICLE_YAML_CANDIDATES:
        if not path.exists():
            continue
        with path.open("r", encoding="utf-8") as f:
            data = yaml.safe_load(f)
        if data is None:
            raise ValueError(f"Vehicle YAML is empty: {path}")
        if not isinstance(data, dict):
            raise TypeError(f"Expected vehicle YAML to contain a mapping: {path}")
        return cast(dict[str, Any], data)
    raise FileNotFoundError(
        "Missing active vehicle.yml. Expected one of: "
        + ", ".join(str(path) for path in ACTIVE_VEHICLE_YAML_CANDIDATES)
    )


def _combine_sprung_mass(vehicle: dict[str, Any]) -> tuple[float, np.ndarray]:
    sprung = vehicle.get("sprung_mass")
    if not isinstance(sprung, dict):
        raise ValueError("vehicle.yml is missing sprung_mass")

    base_m = float(sprung["mass_kg"])
    base_cg = np.asarray(sprung["cg_m"], dtype=float)

    driver = vehicle.get("driver_mass")
    if isinstance(driver, dict):
        driver_m = float(driver["mass_kg"])
        driver_cg = np.asarray(driver["cg_m"], dtype=float)
    else:
        driver_m = 0.0
        driver_cg = np.zeros(3, dtype=float)

    total_m = base_m + driver_m
    if total_m <= 0.0:
        raise ValueError("Combined sprung mass must be positive.")

    total_cg = (base_m * base_cg + driver_m * driver_cg) / total_m
    return total_m, total_cg


def _side_data(vehicle: dict[str, Any], side_name: str) -> dict[str, Any]:
    side = vehicle.get(side_name)
    if not isinstance(side, dict):
        raise ValueError(f"vehicle.yml is missing {side_name}")
    return side


def _nested_value(data: dict[str, Any], *keys: str) -> Any:
    cur: Any = data
    for key in keys:
        if not isinstance(cur, dict) or key not in cur:
            raise KeyError(".".join(keys))
        cur = cur[key]
    return cur


def _table_array(table_like: Any) -> np.ndarray:
    arr = np.asarray(table_like, dtype=float)
    if arr.ndim != 2 or arr.shape[1] < 2:
        raise ValueError("Expected a 2D table with at least two columns.")
    return arr[:, :2]


def _side_spring_table(side: dict[str, Any]) -> np.ndarray:
    shock = _nested_value(side, "actuation", "shock")
    table = shock.get("spring_table")
    if isinstance(table, dict):
        table = table.get("table")
    return _table_array(table)


def _side_spring_free_length(side: dict[str, Any]) -> float:
    return float(_nested_value(side, "actuation", "shock", "free_length_m"))


def _side_stabar_rate(side: dict[str, Any]) -> float:
    actuation = _nested_value(side, "actuation")
    stabar = actuation.get("stabar")
    if not isinstance(stabar, dict):
        return 0.0
    return float(stabar.get("rate_n_m_per_rad", 0.0))


def _side_has_stabar(side: dict[str, Any]) -> bool:
    actuation = _nested_value(side, "actuation")
    return isinstance(actuation.get("stabar"), dict)


def _linearize_spring_table_rate(table: np.ndarray, rate_n_per_m: float) -> np.ndarray:
    table = np.asarray(table, dtype=float).copy()
    table[:, 1] = table[:, 0] * float(rate_n_per_m)
    return table


def _configured_float(
    config: dict[str, Any],
    keys: Sequence[str],
    fallback: float,
) -> float:
    for key in keys:
        value = config.get(key)
        if value is not None:
            return float(value)
    return float(fallback)


def _configured_optional_float(config: dict[str, Any], keys: Sequence[str]) -> float | None:
    for key in keys:
        value = config.get(key)
        if value is not None:
            return float(value)
    return None


def _finite_abs_mask(values: Any, max_abs: float = FOUR_POST_SIGNAL_ABS_LIMIT) -> np.ndarray:
    arr = np.asarray(values, dtype=float)
    return np.isfinite(arr) & (np.abs(arr) <= float(max_abs))


def _plausible_array(values: Any, max_abs: float = FOUR_POST_SIGNAL_ABS_LIMIT) -> np.ndarray:
    arr = np.asarray(values, dtype=float).reshape(-1).copy()
    arr[~_finite_abs_mask(arr, max_abs)] = np.nan
    return arr


def _nanmean_plausible(values: Any, max_abs: float = FOUR_POST_SIGNAL_ABS_LIMIT) -> float:
    arr = _plausible_array(values, max_abs)
    if arr.size == 0 or not np.isfinite(arr).any():
        return float("nan")
    return float(np.nanmean(arr))


def _safe_divide_series(
    numerator: Any,
    denominator: Any,
    *,
    min_denominator_abs: float,
    max_abs: float,
) -> np.ndarray:
    numerator_arr = _plausible_array(numerator)
    denominator_arr = _plausible_array(denominator)
    size = min(numerator_arr.size, denominator_arr.size)
    out = np.full(size, float("nan"), dtype=float)
    if size <= 0:
        return out

    numerator_arr = numerator_arr[:size]
    denominator_arr = denominator_arr[:size]
    mask = np.isfinite(numerator_arr) & np.isfinite(denominator_arr) & (np.abs(denominator_arr) > min_denominator_abs)
    out[mask] = numerator_arr[mask] / denominator_arr[mask]
    out[~_finite_abs_mask(out, max_abs)] = np.nan
    return out


def _force_denominator_series(measured_force: Any, commanded_abs_force: float) -> np.ndarray:
    """Measured force, NaN where it is outside 5 % to 500 % of the commanded force."""
    measured = _plausible_array(measured_force)
    commanded_abs_force = abs(float(commanded_abs_force))
    if commanded_abs_force <= 0.0:
        return measured

    min_force = max(1e-3, 0.05 * commanded_abs_force)
    max_force = 5.0 * commanded_abs_force
    measured_ok = _finite_abs_mask(measured) & (np.abs(measured) >= min_force) & (np.abs(measured) <= max_force)
    return np.where(measured_ok, measured, float("nan"))


def _sort_xy(x: Any, y: Any) -> tuple[np.ndarray, np.ndarray]:
    x_arr = np.asarray(x, dtype=float).reshape(-1)
    y_arr = np.asarray(y, dtype=float).reshape(-1)
    size = min(x_arr.size, y_arr.size)
    if size <= 0:
        return np.array([], dtype=float), np.array([], dtype=float)
    x_trimmed = x_arr[:size]
    y_trimmed = y_arr[:size]
    idx = np.argsort(x_trimmed)
    return x_trimmed[idx], y_trimmed[idx]


def _design_pose_jacking_coefficients(
    cp_rise_m: Any,
    cp_x_m: Any,
    wc_x_m: Any,
) -> tuple[float, float]:
    """Kinematic dFz/dFx at zero CP rise for an Fx reacted through the upright and through the chassis.

    cp_rise_m is the CP height relative to the body. The contact-patch path is -(dx_cp/ds)/(dz_cp/ds).
    The wheel-center path is -(dx_wc/ds)/(dz_cp/ds).
    """
    s = np.asarray(cp_rise_m, dtype=float).reshape(-1)
    cp_x = np.asarray(cp_x_m, dtype=float).reshape(-1)
    wc_x = np.asarray(wc_x_m, dtype=float).reshape(-1)
    mask = np.isfinite(s) & np.isfinite(cp_x) & np.isfinite(wc_x)
    s, cp_x, wc_x = s[mask], cp_x[mask], wc_x[mask]
    order = np.argsort(s)
    s, cp_x, wc_x = s[order], cp_x[order], wc_x[order]
    if s.size < 3 or np.any(np.diff(s) <= 0.0) or not s[0] < 0.0 < s[-1]:
        return float("nan"), float("nan")
    cp_slope = float(np.interp(0.0, s, np.gradient(cp_x, s)))
    wc_slope = float(np.interp(0.0, s, np.gradient(wc_x, s)))
    return -cp_slope, -wc_slope


def _configured_suspension_setup(config: dict[str, Any]) -> dict[str, Any]:
    vehicle = _load_active_vehicle_yaml()
    front_side = _side_data(vehicle, "front")
    rear_side = _side_data(vehicle, "rear")
    front_vehicle_table = _side_spring_table(front_side)
    rear_vehicle_table = _side_spring_table(rear_side)

    model_overrides = _as_mapping(config.get("model_overrides"), name="model_overrides")
    suspension_cfg = _as_mapping(
        model_overrides.get("suspension"),
        name="model_overrides.suspension",
    )
    front_cfg = _as_mapping(
        suspension_cfg.get("front"),
        name="model_overrides.suspension.front",
    )
    rear_cfg = _as_mapping(
        suspension_cfg.get("rear"),
        name="model_overrides.suspension.rear",
    )

    front_spring_rate = _configured_float(
        front_cfg,
        ("spring_rate_n_per_m", "spring_rate"),
        _spring_rate_at_deflection(front_vehicle_table, 0.0),
    )
    rear_spring_rate = _configured_float(
        rear_cfg,
        ("spring_rate_n_per_m", "spring_rate"),
        _spring_rate_at_deflection(rear_vehicle_table, 0.0),
    )
    front_stabar_rate = (
        _configured_float(
            front_cfg,
            ("stabar_rate_n_m_per_rad", "bar_rate_n_m_per_rad", "arb_rate"),
            _side_stabar_rate(front_side),
        )
        if _side_has_stabar(front_side)
        else 0.0
    )
    rear_stabar_rate = (
        _configured_float(
            rear_cfg,
            ("stabar_rate_n_m_per_rad", "bar_rate_n_m_per_rad", "arb_rate"),
            _side_stabar_rate(rear_side),
        )
        if _side_has_stabar(rear_side)
        else 0.0
    )
    front_spring_table = (
        _linearize_spring_table_rate(front_vehicle_table, front_spring_rate)
        if _configured_optional_float(front_cfg, ("spring_rate_n_per_m", "spring_rate")) is not None
        else front_vehicle_table
    )
    rear_spring_table = (
        _linearize_spring_table_rate(rear_vehicle_table, rear_spring_rate)
        if _configured_optional_float(rear_cfg, ("spring_rate_n_per_m", "spring_rate")) is not None
        else rear_vehicle_table
    )

    return {
        "front_side": front_side,
        "rear_side": rear_side,
        "front_spring_rate": front_spring_rate,
        "rear_spring_rate": rear_spring_rate,
        "front_spring_table": front_spring_table,
        "rear_spring_table": rear_spring_table,
        "front_spring_free_length": _configured_spring_free_length(front_cfg, front_side),
        "rear_spring_free_length": _configured_spring_free_length(rear_cfg, rear_side),
        "front_stabar_rate": front_stabar_rate,
        "rear_stabar_rate": rear_stabar_rate,
    }


def _sprung_corner_loads(vehicle: dict[str, Any]) -> dict[str, tuple[float, float]]:
    sprung_mass_kg, sprung_cg_m = _combine_sprung_mass(vehicle)
    front_side = _side_data(vehicle, "front")
    rear_side = _side_data(vehicle, "rear")
    front_wc = np.asarray(_nested_value(front_side, "suspension", "wheel_center_m"), dtype=float)
    rear_wc = np.asarray(_nested_value(rear_side, "suspension", "wheel_center_m"), dtype=float)

    front_x = float(front_wc[0])
    rear_x = float(rear_wc[0])
    wheelbase = abs(front_x - rear_x)
    if wheelbase <= 0.0:
        raise ValueError("Vehicle wheelbase must be positive.")

    left_y = 0.5 * (float(front_wc[1]) + float(rear_wc[1]))
    right_y = -left_y
    if abs(left_y - right_y) <= 1e-12:
        raise ValueError("Vehicle track width must be positive.")

    front_fraction = (sprung_cg_m[0] - rear_x) / (front_x - rear_x)
    rear_fraction = 1.0 - front_fraction
    left_fraction = (sprung_cg_m[1] - right_y) / (left_y - right_y)
    right_fraction = 1.0 - left_fraction

    return {
        "front": (
            float(sprung_mass_kg * front_fraction * left_fraction * GRAVITY_MPS2),
            float(sprung_mass_kg * front_fraction * right_fraction * GRAVITY_MPS2),
        ),
        "rear": (
            float(sprung_mass_kg * rear_fraction * left_fraction * GRAVITY_MPS2),
            float(sprung_mass_kg * rear_fraction * right_fraction * GRAVITY_MPS2),
        ),
    }


def _configured_spring_free_length(axle_cfg: dict[str, Any], side: dict[str, Any]) -> float:
    explicit = _configured_optional_float(
        axle_cfg,
        ("spring_free_length_m", "free_length_m", "spring_free_length"),
    )
    if explicit is not None:
        return explicit
    return _side_spring_free_length(side)


def _static_balance_tolerances(config: dict[str, Any]) -> tuple[float, float]:
    model_overrides = _as_mapping(config.get("model_overrides"), name="model_overrides")
    suspension_cfg = _as_mapping(
        model_overrides.get("suspension"),
        name="model_overrides.suspension",
    )
    return (
        float(suspension_cfg.get("static_balance_tolerance_n", 5.0)),
        float(suspension_cfg.get("static_balance_tolerance_pct", 0.5)),
    )


def _static_balance_summary(setup: dict[str, Any]) -> dict[str, Any]:
    balance = setup["static_balance"]
    verdict = {"pass": True, "fail": False}
    static_motion_ratios: dict[str, list[float]] = {"front": [], "rear": []}
    for axle_name in ("front", "rear"):
        for side_name in ("left", "right"):
            static_mr = float(setup[axle_name][side_name].get("motion_ratio", float("nan")))
            if np.isfinite(static_mr):
                static_motion_ratios[axle_name].append(static_mr)

    closure = balance["closure_pass"]
    return {
        "static_balance_pass": verdict.get(balance["status"], float("nan")),
        "static_balance_status": balance["status"],
        "static_balance_reason": balance["reason"],
        "static_balance_max_abs_fz_error_n": balance["max_abs_fz_error_n"],
        "static_balance_max_abs_fz_error_pct": balance["max_abs_fz_error_pct"],
        "static_equilibrium_pass": float("nan") if closure is None else closure,
        "static_equilibrium_max_force_residual_n": balance["max_force_residual_n"],
        "static_equilibrium_max_moment_residual_nm": balance["max_moment_residual_nm"],
        "static_equilibrium_max_relative_residual": balance["max_relative_residual"],
        "static_equilibrium_worst_time_s": balance["worst_time_s"],
        "static_equilibrium_rows": balance["zero_command_rows"],
        "static_spring_max_residual_n": balance["max_spring_residual_n"],
        "static_motion_ratio_front": (
            float(np.mean(static_motion_ratios["front"])) if static_motion_ratios["front"] else float("nan")
        ),
        "static_motion_ratio_rear": (
            float(np.mean(static_motion_ratios["rear"])) if static_motion_ratios["rear"] else float("nan")
        ),
    }


def _static_balance_metric_status(balance_summary: dict[str, Any]) -> dict[str, str]:
    """A static balance check that could not run reports its values as unavailable, not invalid."""
    if balance_summary["static_balance_status"] != "unavailable":
        return {}
    return {
        key: "unavailable"
        for key in balance_summary
        if key.startswith(("static_balance_", "static_equilibrium_", "static_spring_"))
        and key not in ("static_balance_status", "static_balance_reason")
    }


def _indexed_table_overrides(prefix: str, table: np.ndarray) -> dict[str, float]:
    table = np.asarray(table, dtype=float)
    return {
        f"{prefix}[{i + 1},{j + 1}]": float(table[i, j]) for i in range(table.shape[0]) for j in range(table.shape[1])
    }


def _interp_with_extrap(x: float, xp: np.ndarray, fp: np.ndarray) -> float:
    mask = np.isfinite(xp) & np.isfinite(fp)
    xp = np.asarray(xp[mask], dtype=float)
    fp = np.asarray(fp[mask], dtype=float)
    if xp.size < 2:
        return float("nan")

    order = np.argsort(xp)
    xp = xp[order]
    fp = fp[order]

    unique_xp, unique_idx = np.unique(xp, return_index=True)
    xp = unique_xp
    fp = fp[unique_idx]
    if xp.size < 2:
        return float("nan")

    if x <= xp[0]:
        slope = (fp[1] - fp[0]) / (xp[1] - xp[0] + 1e-12)
        return float(fp[0] + slope * (x - xp[0]))
    if x >= xp[-1]:
        slope = (fp[-1] - fp[-2]) / (xp[-1] - xp[-2] + 1e-12)
        return float(fp[-1] + slope * (x - xp[-1]))

    return float(np.interp(x, xp, fp))


def _spring_rate_at_deflection(spring_table: Any, deflection_m: float) -> float:
    table = _table_array(spring_table)
    deflection = table[:, 0]
    force = table[:, 1]
    mask = np.isfinite(deflection) & np.isfinite(force)
    deflection = np.asarray(deflection[mask], dtype=float)
    force = np.asarray(force[mask], dtype=float)
    if deflection.size < 2:
        return float("nan")

    order = np.argsort(deflection)
    deflection = deflection[order]
    force = force[order]

    unique_deflection, unique_idx = np.unique(deflection, return_index=True)
    deflection = unique_deflection
    force = force[unique_idx]
    if deflection.size < 2:
        return float("nan")

    if deflection_m <= deflection[0]:
        idx = 0
    elif deflection_m >= deflection[-1]:
        idx = deflection.size - 2
    else:
        idx = int(np.searchsorted(deflection, deflection_m) - 1)

    dx = deflection[idx + 1] - deflection[idx]
    if abs(dx) < 1e-12:
        return float("nan")

    return float((force[idx + 1] - force[idx]) / dx)


def _static_motion_ratio(series: dict[str, np.ndarray], corner_key: str, fallback: float) -> float:
    x = np.asarray(series.get(f"{corner_key}_motion_ratio_x", []), dtype=float).reshape(-1)
    y = np.asarray(series.get(f"{corner_key}_motion_ratio_vs_heave", []), dtype=float).reshape(-1)
    mask = np.isfinite(x) & np.isfinite(y)
    x = x[mask]
    y = y[mask]
    if x.size < 2 or y.size < 2:
        return float(fallback)

    if np.nanstd(x) < 1e-12 or np.nanstd(y) < 1e-12:
        return float(fallback)

    return _interp_with_extrap(0.0, x, y)


def _quarter_car_frequencies(
    sprung_mass_kg: float,
    unsprung_mass_kg: float,
    wheel_rate_n_per_m: float,
    tire_rate_n_per_m: float,
) -> tuple[float, float]:
    values = (sprung_mass_kg, unsprung_mass_kg, wheel_rate_n_per_m, tire_rate_n_per_m)
    if not all(np.isfinite(value) and value > 0.0 for value in values):
        return float("nan"), float("nan")

    m = np.array([[sprung_mass_kg, 0.0], [0.0, unsprung_mass_kg]], dtype=float)
    k = np.array(
        [
            [wheel_rate_n_per_m, -wheel_rate_n_per_m],
            [-wheel_rate_n_per_m, wheel_rate_n_per_m + tire_rate_n_per_m],
        ],
        dtype=float,
    )

    eigvals = np.linalg.eigvals(np.linalg.solve(m, k))
    eigvals = np.real(eigvals[np.isfinite(eigvals) & (np.real(eigvals) > 0.0)])
    eigvals.sort()
    if eigvals.size < 2:
        return float("nan"), float("nan")

    sprung_hz = float(np.sqrt(eigvals[0]) / (2.0 * np.pi))
    unsprung_hz = float(np.sqrt(eigvals[1]) / (2.0 * np.pi))
    return sprung_hz, unsprung_hz


class FourPostEvalSim:
    def __init__(self, config: dict[str, Any]):
        self.config = {
            **config,
            "standard": "FourPostEval",
            "report": {**_as_mapping(config.get("report"), name="report"), "brand": "BobSim"},
            "simulation": copy.deepcopy(FOUR_POST_SIMULATION),
            "execution": {"parallel": False, "cleanup": False, "stream_logs": False},
        }
        self.metric_status: dict[str, str] = {}

    def build_overrides(self) -> dict[str, Any]:
        procedure = _as_mapping(self.config.get("procedure"), name="procedure")
        simulation = _as_mapping(self.config.get("simulation"), name="simulation")

        return {
            "steerMagnitude": procedure.get("steerMagnitude", 0.0),
            "heaveMagnitude": procedure.get("heaveMagnitude", 0.03),
            "rollMagnitude": procedure.get("rollMagnitude", 0.035),
            "forceMagnitude": procedure.get("forceMagnitude", 1000.0),
            "_stopTime": procedure.get(
                "stopTime",
                simulation.get("stop_time", FOUR_POST_STOP_TIME_S),
            ),
        }

    def build_model_setup_overrides(self) -> dict[str, float]:
        setup = _configured_suspension_setup(self.config)
        front_spring_table = setup["front_spring_table"]
        rear_spring_table = setup["rear_spring_table"]
        front_stabar_rate = float(setup["front_stabar_rate"])
        rear_stabar_rate = float(setup["rear_stabar_rate"])

        overrides: dict[str, float] = {
            "pVehicle.chassis.frontAxle.actuation.springFreeLength": float(setup["front_spring_free_length"]),
            "pVehicle.chassis.rearAxle.actuation.springFreeLength": float(setup["rear_spring_free_length"]),
        }
        # The rig binds p{Fr,Rr}Stabar, not pVehicle.chassis.*.stabilizer. Its templates zero the bars for pure K&C.
        for tag, axle_name, bar_rate in (("Fr", "front", front_stabar_rate), ("Rr", "rear", rear_stabar_rate)):
            if _side_has_stabar(setup[f"{axle_name}_side"]):
                overrides[f"p{tag}Stabar.barRate"] = bar_rate
        overrides.update(
            _indexed_table_overrides(
                "pVehicle.chassis.frontAxle.actuation.springTable",
                front_spring_table,
            )
        )
        overrides.update(
            _indexed_table_overrides(
                "pVehicle.chassis.rearAxle.actuation.springTable",
                rear_spring_table,
            )
        )
        return overrides

    def build_setup(
        self,
        summary: dict[str, Any],
        series: dict[str, np.ndarray],
        result: dict[str, Any],
    ) -> dict[str, Any]:
        vehicle = _load_active_vehicle_yaml()
        sprung_mass_kg, sprung_cg_m = _combine_sprung_mass(vehicle)
        suspension_setup = _configured_suspension_setup(self.config)
        static_balance_tol_n, static_balance_tol_pct = _static_balance_tolerances(self.config)

        front_side = _side_data(vehicle, "front")
        rear_side = _side_data(vehicle, "rear")
        front_wc = np.asarray(_nested_value(front_side, "suspension", "wheel_center_m"), dtype=float)
        rear_wc = np.asarray(_nested_value(rear_side, "suspension", "wheel_center_m"), dtype=float)

        front_x = float(front_wc[0])
        rear_x = float(rear_wc[0])
        left_y = 0.5 * (float(front_wc[1]) + float(rear_wc[1]))
        right_y = -left_y

        wheelbase = abs(front_x - rear_x)
        track_front = 2.0 * float(front_wc[1])
        track_rear = 2.0 * float(rear_wc[1])

        if wheelbase <= 0.0:
            raise ValueError("Vehicle wheelbase must be positive.")
        if abs(left_y - right_y) <= 1e-12:
            raise ValueError("Vehicle track width must be positive.")

        front_fraction = (sprung_cg_m[0] - rear_x) / (front_x - rear_x)
        rear_fraction = 1.0 - front_fraction
        left_fraction = (sprung_cg_m[1] - right_y) / (left_y - right_y)
        right_fraction = 1.0 - left_fraction

        axle_specs = {
            "front": {
                "label": "Front",
                "side": front_side,
                "axle_fraction": front_fraction,
                "track_m": track_front,
                "corner_pairs": (("left", "fr_l"), ("right", "fr_r")),
            },
            "rear": {
                "label": "Rear",
                "side": rear_side,
                "axle_fraction": rear_fraction,
                "track_m": track_rear,
                "corner_pairs": (("left", "rr_l"), ("right", "rr_r")),
            },
        }

        def corner_unsprung_mass(side: dict[str, Any]) -> float:
            masses = _nested_value(side, "masses")
            total = 0.0
            for key in (
                "unsprung",
                "upper_control_arm",
                "lower_control_arm",
                "tie_rod",
            ):
                total += float(_nested_value(masses, key, "mass_kg"))
            return total

        def tire_rate(side: dict[str, Any]) -> float:
            return float(_nested_value(side, "tire", "vertical_stiffness_n_per_m"))

        target_loads = _sprung_corner_loads(vehicle)
        balance = static_balance.evaluate(
            result,
            [
                static_balance.AxleSpec(
                    name=axle_name,
                    knc=knc,
                    axle=mbd_axle,
                    actuator=actuator,
                    free_length_m=float(suspension_setup[f"{axle_name}_spring_free_length"]),
                    spring_table=np.asarray(suspension_setup[f"{axle_name}_spring_table"], dtype=float),
                    target_load_n=target_loads[axle_name],
                )
                for axle_name, knc, mbd_axle, actuator in FOUR_POST_STATIC_BALANCE_AXLES
            ],
            target_tol_n=static_balance_tol_n,
            target_tol_pct=static_balance_tol_pct,
        )
        corners: dict[str, dict[str, Any]] = {}

        for axle_name, axle in axle_specs.items():
            side = axle["side"]
            axle_fraction = float(axle["axle_fraction"])
            axle_unsprung_mass = corner_unsprung_mass(side)
            axle_tire_rate = tire_rate(side)
            axle_spring_table = suspension_setup[f"{axle_name}_spring_table"]
            free_length_m = float(suspension_setup[f"{axle_name}_spring_free_length"])
            motion_ratio_key = "avg_motion_ratio_front" if axle_name == "front" else "avg_motion_ratio_rear"

            for corner_name, corner_key in axle["corner_pairs"]:
                corner_fraction = axle_fraction * (left_fraction if corner_name == "left" else right_fraction)
                sprung_corner_mass = sprung_mass_kg * corner_fraction
                measured = balance["axles"][axle_name][corner_name]
                static_mr = _static_motion_ratio(
                    series,
                    corner_key,
                    float(summary.get(motion_ratio_key, float("nan"))),
                )
                spring_force = float(measured["spring_force_n"])
                spring_wheel_load = (
                    spring_force / static_mr if np.isfinite(static_mr) and abs(static_mr) > 1e-12 else float("nan")
                )
                spring_length_m = float(measured["spring_length_m"])
                spring_compression_m = free_length_m - spring_length_m
                spring_rate = (
                    _spring_rate_at_deflection(axle_spring_table, spring_compression_m)
                    if np.isfinite(spring_compression_m)
                    else float("nan")
                )
                wheel_rate = (
                    spring_rate / (static_mr**2) if np.isfinite(static_mr) and abs(static_mr) > 1e-12 else float("nan")
                )
                sprung_mode_hz, unsprung_mode_hz = _quarter_car_frequencies(
                    sprung_corner_mass,
                    axle_unsprung_mass,
                    wheel_rate,
                    axle_tire_rate,
                )

                corners[corner_key] = {
                    "corner": {
                        "fr_l": "FL",
                        "fr_r": "FR",
                        "rr_l": "RL",
                        "rr_r": "RR",
                    }[corner_key],
                    "sprung_mass_kg": float(sprung_corner_mass),
                    "unsprung_mass_kg": float(axle_unsprung_mass),
                    "sprung_load_N": float(measured["target_load_n"]),
                    "static_balance_target_load_N": float(measured["target_load_n"]),
                    "motion_ratio": float(static_mr),
                    "spring_rate_N_per_m": float(spring_rate),
                    "spring_force_N": spring_force,
                    "spring_force_from_table_N": float(measured["spring_force_from_table_n"]),
                    "spring_wheel_load_N": float(spring_wheel_load),
                    "spring_compression_m": float(spring_compression_m),
                    "spring_installed_length_m": spring_length_m,
                    "spring_free_length_m": free_length_m,
                    "static_fz_N": float(measured["contact_fz_n"]),
                    "static_fz_error_N": float(measured["fz_error_n"]),
                    "static_fz_error_pct": float(measured["fz_error_pct"]),
                    "static_balance_limit_N": float(measured["limit_n"]),
                    "static_balance_ok": measured["target_ok"],
                    "wheel_rate_N_per_m": float(wheel_rate),
                    "sprung_frequency_hz": float(sprung_mode_hz),
                    "unsprung_frequency_hz": float(unsprung_mode_hz),
                }

        setup = {
            "subtitle": "Measured design-pose loads and springs against the target sprung corner loads.",
            "vehicle": {
                "sprung_mass_kg": float(sprung_mass_kg),
                "sprung_cg_m": [float(v) for v in sprung_cg_m],
                "wheelbase_m": float(wheelbase),
                "track_front_m": float(track_front),
                "track_rear_m": float(track_rear),
                "cg_bias_front_pct": float(100.0 * front_fraction),
                "cg_bias_rear_pct": float(100.0 * rear_fraction),
                "cg_bias_left_pct": float(100.0 * left_fraction),
                "cg_bias_right_pct": float(100.0 * right_fraction),
            },
            "front": {
                "label": "Front",
                "left": corners["fr_l"],
                "right": corners["fr_r"],
            },
            "rear": {
                "label": "Rear",
                "left": corners["rr_l"],
                "right": corners["rr_r"],
            },
            "static_balance": balance,
        }

        return setup

    def run(self) -> dict[str, Any]:
        simulation_cfg = _as_mapping(self.config.get("simulation"), name="simulation")
        execution_cfg = _as_mapping(self.config.get("execution"), name="execution")
        report_cfg = _as_mapping(self.config.get("report"), name="report")

        runner = ModelicaRunner(
            build_dir=simulation_cfg.get("build_dir", DEFAULT_BUILD_DIR),
            exec_name=simulation_cfg.get("exec_name", DEFAULT_EXEC_NAME),
            simulation={
                **simulation_cfg,
                "variable_filter": simulation_cfg.get(
                    "variable_filter",
                    FOUR_POST_EVAL_VARIABLE_FILTER,
                ),
            },
        )

        results = runner.run(
            signals=FOUR_POST_EVAL_SIGNALS,
            mode="raw",
            cases=[
                {
                    **self.build_overrides(),
                    **self.build_model_setup_overrides(),
                    "_case_label": "four post",
                }
            ],
            execution=execution_cfg,
        )

        if not results:
            raise RuntimeError("FourPostEval returned no cases.")

        result = results[0]
        if result.get("_status") != "ok":
            raise RuntimeError(
                "FourPostEval simulation failed:\n"
                f"{result.get('_error', 'unknown error')}\n"
                f"{result.get('_traceback', '')}"
            )

        summary, series = self.summarize(result)
        setup = self.build_setup(summary, series, result)
        balance_summary = _static_balance_summary(setup)
        summary.update(balance_summary)
        self.metric_status.update(_static_balance_metric_status(balance_summary))

        metrics_csv_path = write_metrics_csv(
            summary,
            report_cfg.get("metrics_csv_path", DEFAULT_METRICS_CSV_PATH),
            self.metric_status,
        )

        return {
            "summary": summary,
            "metric_status": dict(self.metric_status),
            "series": series,
            "setup": setup,
            "metrics_csv_path": str(metrics_csv_path),
            "cases": results,
            "failed_cases": [],
            "n_cases": len(results),
            "n_successful_cases": len(results),
            "n_failed_cases": 0,
        }

    def summarize(self, result: dict[str, Any]) -> tuple[dict[str, Any], dict[str, np.ndarray]]:
        t = _plausible_array(result["time"])

        def sig(prefix: str, name: str) -> np.ndarray:
            return _plausible_array(result[f"{prefix}.{name}"])

        def sample_at_times(signal: np.ndarray, times: list[float]) -> np.ndarray:
            signal = _plausible_array(signal)
            size = min(t.size, signal.size)
            time = t[:size]
            signal = signal[:size]
            samples: list[float] = []
            valid_time = np.isfinite(time)
            half_window = 0.5 * FOUR_POST_SAMPLE_WINDOW_S
            for ti in times:
                window = valid_time & (np.abs(time - ti) <= half_window) & np.isfinite(signal)
                samples.append(float(np.nanmedian(signal[window])) if np.any(window) else float("nan"))
            return np.array(samples, dtype=float)

        def sample_in_window(signal: np.ndarray, center_s: float, half_window_s: float) -> float:
            signal = _plausible_array(signal)
            size = min(t.size, signal.size)
            time = t[:size]
            signal = signal[:size]
            valid = np.isfinite(time) & np.isfinite(signal)
            window = valid & (np.abs(time - center_s) <= half_window_s)
            return float(np.nanmedian(signal[window])) if np.any(window) else float("nan")

        def sample_force_pulses(
            pose_signal: np.ndarray,
            response_signal: np.ndarray,
            force_signal: np.ndarray,
            *,
            start_s: float,
            count: int,
            subtract_tail: bool = True,
        ) -> tuple[np.ndarray, np.ndarray, np.ndarray]:
            pose = _plausible_array(pose_signal)
            response = _plausible_array(response_signal)
            force = _plausible_array(force_signal)
            size = min(t.size, pose.size, response.size, force.size)
            time = t[:size]
            pose = pose[:size]
            response = response[:size]
            force = force[:size]
            valid_time = np.isfinite(time)

            pose_samples: list[float] = []
            response_delta_samples: list[float] = []
            force_samples: list[float] = []
            for pose_index in range(count):
                pose_start = start_s + FOUR_POST_POSE_STEP_S * pose_index
                tail_time = pose_start + 4.0
                pulse_window = (
                    valid_time & (time >= pose_start + 0.5) & (time <= pose_start + 2.25) & np.isfinite(response)
                )
                force_window = pulse_window & np.isfinite(force) & (np.abs(force) > 1e-6)
                selected_index: int | None = None
                if np.any(force_window):
                    candidates = np.flatnonzero(force_window)
                    selected_index = int(candidates[np.nanargmax(np.abs(force[candidates]))])

                if selected_index is None:
                    pose_pulse = response_pulse = force_pulse = float("nan")
                else:
                    pose_pulse = float(pose[selected_index])
                    response_pulse = float(response[selected_index])
                    force_pulse = float(force[selected_index])

                response_tail = sample_in_window(response_signal, tail_time, 0.75) if subtract_tail else 0.0
                pose_samples.append(pose_pulse)
                response_delta_samples.append(response_pulse - response_tail)
                force_samples.append(force_pulse)

            return (
                np.asarray(pose_samples, dtype=float),
                np.asarray(response_delta_samples, dtype=float),
                np.asarray(force_samples, dtype=float),
            )

        def compute_gain(x: np.ndarray, y: np.ndarray) -> float:
            x = _plausible_array(x)
            y = _plausible_array(y)
            mask = np.isfinite(x) & np.isfinite(y)
            x = x[mask]
            y = y[mask]
            if x.size < 2 or y.size < 2:
                return float("nan")
            if np.nanstd(x) < 1e-12 or np.nanstd(y) < 1e-12:
                return float("nan")
            coeffs = np.polyfit(x, y, 1)
            return float(coeffs[0])

        def nanmean_or_nan(values: Any) -> float:
            return _nanmean_plausible(list(values))

        def pose_sample_times(start_s: float, count: int) -> list[float]:
            # Sample inside the dead region after the load pulse, before the next pose change.
            return [start_s + FOUR_POST_POSE_STEP_S * i + 4.0 for i in range(count)]

        heave_sample_times = pose_sample_times(FOUR_POST_HEAVE_START_S, FOUR_POST_HEAVE_POSE_COUNT)
        roll_sample_times = pose_sample_times(FOUR_POST_ROLL_START_S, FOUR_POST_ROLL_POSE_COUNT)

        signals = {
            "camber": "Gamma",
            "toe": "Toe",
            "caster": "Caster",
            "kpi": "Kpi",
            "trail": "MechTrail",
            "scrub": "MechScrub",
            "fz": "Fz",
        }
        corners = ["fr_l", "fr_r", "rr_l", "rr_r"]

        def side_prefix(corner: str) -> str:
            return "frKnC" if corner.startswith("fr") else "rrKnC"

        def corner_signal(prefix: str, corner: str, name: str) -> np.ndarray:
            side = "left" if corner.endswith("_l") else "right"
            return sig(prefix, f"{side}{name}")

        heave = -sig("frKnC", "heave")
        roll = sig("frKnC", "roll")

        heave_vals = sample_at_times(heave, heave_sample_times)
        heave_mask = np.isfinite(heave_vals)
        heave_vals = heave_vals[heave_mask]
        heave_idx = np.argsort(heave_vals)
        heave_vals = heave_vals[heave_idx]

        roll_vals = sample_at_times(roll, roll_sample_times)
        roll_mask = np.isfinite(roll_vals)
        roll_vals = roll_vals[roll_mask]
        roll_idx = np.argsort(roll_vals)
        roll_vals = roll_vals[roll_idx]

        heave_series: dict[str, np.ndarray] = {}
        roll_series: dict[str, np.ndarray] = {}
        validation_cfg = _as_mapping(self.config.get("validation"), name="validation")
        min_contact_fz_n = float(validation_cfg.get("min_contact_fz_n", FOUR_POST_MIN_CONTACT_FZ_N))

        for key, suffix in signals.items():
            for corner in corners:
                prefix = side_prefix(corner)
                heave_sig = sample_at_times(corner_signal(prefix, corner, suffix), heave_sample_times)
                roll_sig = sample_at_times(corner_signal(prefix, corner, suffix), roll_sample_times)

                heave_sig = heave_sig[heave_mask]
                roll_sig = roll_sig[roll_mask]
                heave_series[f"{corner}_{key}_vs_heave"] = heave_sig[heave_idx]
                roll_series[f"{corner}_{key}_vs_roll"] = roll_sig[roll_idx]

        heave_tension = np.zeros(heave_vals.size, dtype=bool)
        for prefix, corner_pair in (("frKnC", ("fr_l", "fr_r")), ("rrKnC", ("rr_l", "rr_r"))):
            jacking_tail = sample_at_times(sig(prefix, "jackingForce"), heave_sample_times)[heave_mask][heave_idx]
            contact = [heave_series[f"{corner}_fz_vs_heave"] for corner in corner_pair]
            heave_series[f"{prefix[:2]}_tension_residual_vs_heave"] = contact[0] + contact[1] + jacking_tail
            for corner, fz in zip(corner_pair, contact, strict=True):
                clamped = fz < min_contact_fz_n
                heave_tension |= clamped
                heave_series[f"{corner}_fz_vs_heave"] = np.where(clamped, float("nan"), fz)

        # Jacking is the load from the force pulse only. Subtract the dead-tail force at the same pose.
        fr_jack = -sig("frKnC", "jackingForce")
        rr_jack = -sig("rrKnC", "jackingForce")
        fr_fx = sig("frKnC", "fx")
        rr_fx = sig("rrKnC", "fx")
        fr_fy = sig("frKnC", "fy")
        rr_fy = sig("rrKnC", "fy")

        fr_heave_jack_x, fr_heave_jack_y, fr_heave_fx = sample_force_pulses(
            heave,
            fr_jack,
            fr_fx,
            start_s=FOUR_POST_HEAVE_START_S,
            count=FOUR_POST_HEAVE_POSE_COUNT,
        )
        rr_heave_jack_x, rr_heave_jack_y, rr_heave_fx = sample_force_pulses(
            heave,
            rr_jack,
            rr_fx,
            start_s=FOUR_POST_HEAVE_START_S,
            count=FOUR_POST_HEAVE_POSE_COUNT,
        )
        fr_roll_jack_x, fr_roll_jack_y, fr_roll_fy = sample_force_pulses(
            roll,
            fr_jack,
            fr_fy,
            start_s=FOUR_POST_ROLL_START_S,
            count=FOUR_POST_ROLL_POSE_COUNT,
        )
        rr_roll_jack_x, rr_roll_jack_y, rr_roll_fy = sample_force_pulses(
            roll,
            rr_jack,
            rr_fy,
            start_s=FOUR_POST_ROLL_START_S,
            count=FOUR_POST_ROLL_POSE_COUNT,
        )
        roll_contact_samples = []
        roll_fz_delta: dict[tuple[str, str], np.ndarray] = {}
        for prefix in ("frKnC", "rrKnC"):
            for side in ("left", "right"):
                _, contact_fz, _ = sample_force_pulses(
                    roll,
                    sig(prefix, f"{side}Fz"),
                    sig(prefix, "fy"),
                    start_s=FOUR_POST_ROLL_START_S,
                    count=FOUR_POST_ROLL_POSE_COUNT,
                    subtract_tail=False,
                )
                roll_contact_samples.append(contact_fz)
                _, delta_fz, _ = sample_force_pulses(
                    roll,
                    sig(prefix, f"{side}Fz"),
                    sig(prefix, "fy"),
                    start_s=FOUR_POST_ROLL_START_S,
                    count=FOUR_POST_ROLL_POSE_COUNT,
                )
                roll_fz_delta[(prefix, side)] = delta_fz
        roll_contact_fz = np.vstack(roll_contact_samples)
        roll_contact_loaded = np.all(
            np.isfinite(roll_contact_fz) & (roll_contact_fz >= min_contact_fz_n),
            axis=0,
        )
        if validation_cfg.get("fail_on_contact_loss", False) and not np.all(roll_contact_loaded):
            invalid_roll_deg = np.degrees(fr_roll_jack_x[~roll_contact_loaded])
            invalid_text = ", ".join(f"{value:+.2f}" for value in invalid_roll_deg)
            raise ValueError(
                "FourPost roll-force evaluation lost contact-patch load at "
                f"roll angles [{invalid_text}] deg (minimum required Fz "
                f"{min_contact_fz_n:.1f} N). Reduce procedure.rollMagnitude or fix the suspension setup."
            )
        procedure_cfg = _as_mapping(self.config.get("procedure"), name="procedure")
        roll_force_denominator_n = FOUR_POST_FORCE_SAMPLE_FRACTION * abs(
            float(procedure_cfg.get("forceMagnitude", 1000.0))
        )
        fr_roll_force_denominator = _force_denominator_series(fr_roll_fy, roll_force_denominator_n)
        rr_roll_force_denominator = _force_denominator_series(rr_roll_fy, roll_force_denominator_n)

        fr_coeff_heave = _safe_divide_series(
            fr_heave_jack_y,
            fr_heave_fx,
            min_denominator_abs=1e-3,
            max_abs=FOUR_POST_RATIO_ABS_LIMIT,
        )
        rr_coeff_heave = _safe_divide_series(
            rr_heave_jack_y,
            rr_heave_fx,
            min_denominator_abs=1e-3,
            max_abs=FOUR_POST_RATIO_ABS_LIMIT,
        )
        fr_coeff_roll = _safe_divide_series(
            fr_roll_jack_y,
            fr_roll_force_denominator,
            min_denominator_abs=1e-3,
            max_abs=FOUR_POST_RATIO_ABS_LIMIT,
        )
        rr_coeff_roll = _safe_divide_series(
            rr_roll_jack_y,
            rr_roll_force_denominator,
            min_denominator_abs=1e-3,
            max_abs=FOUR_POST_RATIO_ABS_LIMIT,
        )

        vehicle = _load_active_vehicle_yaml()
        _, sprung_cg_m = _combine_sprung_mass(vehicle)
        suspension_setup = _configured_suspension_setup(self.config)
        front_side = suspension_setup["front_side"]
        rear_side = suspension_setup["rear_side"]
        front_wc = np.asarray(_nested_value(front_side, "suspension", "wheel_center_m"), dtype=float)
        rear_wc = np.asarray(_nested_value(rear_side, "suspension", "wheel_center_m"), dtype=float)

        h_cg = float(sprung_cg_m[2])
        track_front = 2.0 * float(front_wc[1])
        track_rear = 2.0 * float(rear_wc[1])
        wheelbase = abs(float(front_wc[0]) - float(rear_wc[0]))
        k_sf = float(suspension_setup["front_spring_rate"])
        k_sr = float(suspension_setup["rear_spring_rate"])
        k_arb_f = float(suspension_setup["front_stabar_rate"])
        k_arb_r = float(suspension_setup["rear_stabar_rate"])

        ref_long = h_cg / wheelbase
        ref_roll = h_cg / ((track_front + track_rear) / 2.0)

        # Positive anti-dive denotes a front jacking response that resists braking dive.
        # Braking Fx is negative in the x-forward frame, so negate the signed Fz/Fx
        # coefficient here. Keep raw jacking coefficients and rear anti-squat unchanged.
        fr_anti_heave = _plausible_array(-100.0 * fr_coeff_heave / ref_long, FOUR_POST_PERCENT_ABS_LIMIT)
        rr_anti_heave = _plausible_array(100.0 * rr_coeff_heave / ref_long, FOUR_POST_PERCENT_ABS_LIMIT)
        fr_anti_roll = _plausible_array(100.0 * fr_coeff_roll / ref_roll, FOUR_POST_PERCENT_ABS_LIMIT)
        rr_anti_roll = _plausible_array(100.0 * rr_coeff_roll / ref_roll, FOUR_POST_PERCENT_ABS_LIMIT)

        # Force-based roll-center height: h_eq = (track / 2) * (dFz_right - dFz_left) / Fy.
        # The legacy anti-roll key is net axle jacking: the axle sum, not the left/right split.
        fr_fbrc_ratio = _safe_divide_series(
            roll_fz_delta[("frKnC", "right")] - roll_fz_delta[("frKnC", "left")],
            fr_roll_force_denominator,
            min_denominator_abs=1e-3,
            max_abs=FOUR_POST_RATIO_ABS_LIMIT,
        )
        rr_fbrc_ratio = _safe_divide_series(
            roll_fz_delta[("rrKnC", "right")] - roll_fz_delta[("rrKnC", "left")],
            rr_roll_force_denominator,
            min_denominator_abs=1e-3,
            max_abs=FOUR_POST_RATIO_ABS_LIMIT,
        )
        fr_fbrc_height = _plausible_array(0.5 * track_front * fr_fbrc_ratio)
        rr_fbrc_height = _plausible_array(0.5 * track_rear * rr_fbrc_ratio)

        heave_count = FOUR_POST_HEAVE_POSE_COUNT
        roll_count = FOUR_POST_ROLL_POSE_COUNT
        status: dict[str, str] = {}

        def coverage(name: str, valid: Any, n_total: int) -> None:
            status[name] = _coverage_status(int(np.count_nonzero(valid)), n_total)

        coverage("avg_anti_dive_pct", np.isfinite(fr_anti_heave), heave_count)
        coverage("avg_anti_squat_pct", np.isfinite(rr_anti_heave), heave_count)
        coverage("avg_longitudinal_jacking_coeff_front", np.isfinite(fr_coeff_heave), heave_count)
        coverage("avg_longitudinal_jacking_coeff_rear", np.isfinite(rr_coeff_heave), heave_count)

        # The fixture holds the CP height and the body moves, so the jounce is the CP rise relative to the body.
        heave_pose_jounce = sample_at_times(heave, heave_sample_times)
        anti_path_summary: dict[str, float] = {}
        for axle_name, axle, anti_name, anti_sign in (
            ("front", "frAxleDW", "anti_dive", -1.0),
            ("rear", "rrAxleDW", "anti_squat", 1.0),
        ):
            point_x: list[np.ndarray] = []
            for _, point in FOUR_POST_ANTI_PATH_POINTS:
                names = _anti_path_x_signals(axle, point)
                if all(name in result for name in names):
                    sides = [sample_at_times(result[name], heave_sample_times) for name in names]
                    point_x.append(np.mean(sides, axis=0))
            available = len(point_x) == len(FOUR_POST_ANTI_PATH_POINTS)
            coeffs = (
                _design_pose_jacking_coefficients(heave_pose_jounce, *point_x)
                if available
                else (float("nan"), float("nan"))
            )
            for (path, _), coeff in zip(FOUR_POST_ANTI_PATH_POINTS, coeffs, strict=True):
                coeff_key = f"longitudinal_jacking_coeff_{axle_name}_{path}_path"
                anti_key = f"{anti_name}_{path}_path_pct"
                anti_path_summary[coeff_key] = coeff
                anti_path_summary[anti_key] = anti_sign * 100.0 * coeff / ref_long
                for key in (coeff_key, anti_key):
                    status[key] = "ok" if np.isfinite(coeff) else ("invalid" if available else "unavailable")
        coverage("avg_anti_roll_front_pct", np.isfinite(fr_anti_roll) & roll_contact_loaded, roll_count)
        coverage("avg_anti_roll_rear_pct", np.isfinite(rr_anti_roll) & roll_contact_loaded, roll_count)
        coverage("avg_lateral_jacking_coeff_front", np.isfinite(fr_coeff_roll), roll_count)
        coverage("avg_lateral_jacking_coeff_rear", np.isfinite(rr_coeff_roll), roll_count)
        for axle_name, height in (("front", fr_fbrc_height), ("rear", rr_fbrc_height)):
            coverage(f"avg_fbrc_equivalent_height_{axle_name}_m", np.isfinite(height) & roll_contact_loaded, roll_count)
            coverage(
                f"avg_fbrc_differential_jacking_ratio_{axle_name}",
                np.isfinite(height) & roll_contact_loaded,
                roll_count,
            )

        mask_fr_h = np.isfinite(fr_heave_jack_x) & np.isfinite(fr_anti_heave)
        mask_rr_h = np.isfinite(rr_heave_jack_x) & np.isfinite(rr_anti_heave)
        fr_heave_x = fr_heave_jack_x[mask_fr_h]
        rr_heave_x = rr_heave_jack_x[mask_rr_h]
        fr_anti_heave = fr_anti_heave[mask_fr_h]
        rr_anti_heave = rr_anti_heave[mask_rr_h]

        mask_fr = np.isfinite(fr_roll_jack_x) & np.isfinite(fr_anti_roll) & roll_contact_loaded
        mask_rr = np.isfinite(rr_roll_jack_x) & np.isfinite(rr_anti_roll) & roll_contact_loaded
        fr_roll_x = fr_roll_jack_x[mask_fr]
        rr_roll_x = rr_roll_jack_x[mask_rr]
        fr_anti_roll = fr_anti_roll[mask_fr]
        rr_anti_roll = rr_anti_roll[mask_rr]
        fr_roll_x, fr_anti_roll = _sort_xy(fr_roll_x, fr_anti_roll)
        rr_roll_x, rr_anti_roll = _sort_xy(rr_roll_x, rr_anti_roll)

        mask_fr_fbrc = np.isfinite(fr_roll_jack_x) & np.isfinite(fr_fbrc_height) & roll_contact_loaded
        mask_rr_fbrc = np.isfinite(rr_roll_jack_x) & np.isfinite(rr_fbrc_height) & roll_contact_loaded
        fr_fbrc_order = np.argsort(fr_roll_jack_x[mask_fr_fbrc])
        rr_fbrc_order = np.argsort(rr_roll_jack_x[mask_rr_fbrc])
        fr_fbrc_x = fr_roll_jack_x[mask_fr_fbrc][fr_fbrc_order]
        rr_fbrc_x = rr_roll_jack_x[mask_rr_fbrc][rr_fbrc_order]
        fr_fbrc_ratio = fr_fbrc_ratio[mask_fr_fbrc][fr_fbrc_order]
        rr_fbrc_ratio = rr_fbrc_ratio[mask_rr_fbrc][rr_fbrc_order]
        fr_fbrc_height = fr_fbrc_height[mask_fr_fbrc][fr_fbrc_order]
        rr_fbrc_height = rr_fbrc_height[mask_rr_fbrc][rr_fbrc_order]

        def compute_motion_ratio_series(
            spring_signal: np.ndarray,
            wheel_signal: np.ndarray,
            sample_times: Sequence[float],
        ) -> tuple[np.ndarray, np.ndarray, float]:
            spring = sample_at_times(np.asarray(spring_signal, dtype=float), list(sample_times))
            wheel = sample_at_times(np.asarray(wheel_signal, dtype=float), list(sample_times))

            mask = _finite_abs_mask(spring) & _finite_abs_mask(wheel)
            spring = spring[mask]
            wheel = wheel[mask]

            if spring.size < 2 or wheel.size < 2 or np.nanstd(wheel) < 1e-12:
                return (
                    np.array([], dtype=float),
                    np.array([], dtype=float),
                    float("nan"),
                )

            idx = np.argsort(wheel)
            wheel = wheel[idx]
            spring = spring[idx]
            coeffs = np.polyfit(wheel, spring, 3)
            poly = np.poly1d(coeffs)
            dpoly = np.polyder(poly)
            ds_dw = dpoly(wheel)
            mr = 1.0 / np.abs(ds_dw)
            mr = _plausible_array(mr, FOUR_POST_MOTION_RATIO_ABS_LIMIT)
            finite = np.isfinite(wheel) & np.isfinite(mr)
            return (
                wheel[finite],
                mr[finite],
                _nanmean_plausible(mr, FOUR_POST_MOTION_RATIO_ABS_LIMIT),
            )

        def compute_stabar_motion_ratio_series(
            stabar_signal: np.ndarray,
            roll_signal: np.ndarray,
            sample_times: Sequence[float],
        ) -> tuple[np.ndarray, np.ndarray, float]:
            stabar = sample_at_times(np.asarray(stabar_signal, dtype=float), list(sample_times))
            phi = sample_at_times(np.asarray(roll_signal, dtype=float), list(sample_times))

            mask = _finite_abs_mask(stabar) & _finite_abs_mask(phi)
            stabar = stabar[mask]
            phi = phi[mask]

            if stabar.size < 2 or phi.size < 2 or np.nanstd(stabar) < 1e-12 or np.nanstd(phi) < 1e-12:
                return (
                    np.array([], dtype=float),
                    np.array([], dtype=float),
                    float("nan"),
                )

            idx = np.argsort(phi)
            phi = phi[idx]
            stabar = stabar[idx]
            coeffs = np.polyfit(phi, stabar, 3)
            poly = np.poly1d(coeffs)
            dpoly = np.polyder(poly)
            ds_dphi = dpoly(phi)
            mr = 1.0 / np.abs(ds_dphi)
            mr = _plausible_array(mr, FOUR_POST_MOTION_RATIO_ABS_LIMIT)
            finite = np.isfinite(phi) & np.isfinite(mr)
            return (
                phi[finite],
                mr[finite],
                _nanmean_plausible(mr, FOUR_POST_MOTION_RATIO_ABS_LIMIT),
            )

        def sampled_series(
            x: np.ndarray,
            y: np.ndarray,
            sample_x: np.ndarray,
            fallback: float,
        ) -> np.ndarray:
            x = np.asarray(x, dtype=float).reshape(-1)
            y = np.asarray(y, dtype=float).reshape(-1)
            sample_x = np.asarray(sample_x, dtype=float).reshape(-1)

            mask = _finite_abs_mask(x) & _finite_abs_mask(y)
            x = x[mask]
            y = y[mask]

            if x.size < 2 or np.nanstd(x) < 1e-12 or not np.isfinite(fallback):
                return np.full_like(sample_x, float(fallback), dtype=float)

            idx = np.argsort(x)
            x = x[idx]
            y = y[idx]

            return np.asarray(
                [_interp_with_extrap(float(xi), x, y) for xi in sample_x],
                dtype=float,
            )

        def bar_roll_stiffness(
            bar_rate: float,
            motion_ratio: np.ndarray,
        ) -> np.ndarray:
            motion_ratio = np.asarray(motion_ratio, dtype=float).reshape(-1)
            if abs(float(bar_rate)) <= 1e-12:
                return np.zeros_like(motion_ratio, dtype=float)
            out = np.full_like(motion_ratio, float("nan"), dtype=float)
            mask = _finite_abs_mask(motion_ratio, FOUR_POST_MOTION_RATIO_ABS_LIMIT) & (np.abs(motion_ratio) > 1e-12)
            out[mask] = bar_rate / (motion_ratio[mask] ** 2)
            out = _plausible_array(out)
            return out

        motion_ratio_series: dict[str, np.ndarray] = {}
        motion_ratio_means: list[float] = []
        for corner in corners:
            prefix = side_prefix(corner)
            x_mr, y_mr, mr_mean = compute_motion_ratio_series(
                corner_signal(prefix, corner, "SpringLength"),
                heave,
                heave_sample_times,
            )
            motion_ratio_series[f"{corner}_motion_ratio_x"] = x_mr
            motion_ratio_series[f"{corner}_motion_ratio_vs_heave"] = y_mr
            motion_ratio_means.append(mr_mean)

        mr_f = nanmean_or_nan(motion_ratio_means[:2])
        mr_r = nanmean_or_nan(motion_ratio_means[2:])

        stabar_motion_ratio_series: dict[str, np.ndarray] = {}
        x_smr_f, y_smr_f, smr_f = compute_stabar_motion_ratio_series(
            sig("frKnC", "stabarAngle"),
            roll,
            roll_sample_times,
        )
        x_smr_r, y_smr_r, smr_r = compute_stabar_motion_ratio_series(
            sig("rrKnC", "stabarAngle"),
            roll,
            roll_sample_times,
        )
        stabar_motion_ratio_series["fr_stabar_motion_ratio_x"] = x_smr_f
        stabar_motion_ratio_series["fr_stabar_motion_ratio_vs_roll"] = y_smr_f
        stabar_motion_ratio_series["rr_stabar_motion_ratio_x"] = x_smr_r
        stabar_motion_ratio_series["rr_stabar_motion_ratio_vs_roll"] = y_smr_r

        kw_f = (
            k_sf / (mr_f**2)
            if np.isfinite(mr_f) and 1e-12 < abs(mr_f) <= FOUR_POST_MOTION_RATIO_ABS_LIMIT
            else float("nan")
        )
        kw_r = (
            k_sr / (mr_r**2)
            if np.isfinite(mr_r) and 1e-12 < abs(mr_r) <= FOUR_POST_MOTION_RATIO_ABS_LIMIT
            else float("nan")
        )
        kphi_spr_f = 0.5 * kw_f * (track_front**2)
        kphi_spr_r = 0.5 * kw_r * (track_rear**2)
        smr_f_roll = sampled_series(x_smr_f, y_smr_f, roll_vals, smr_f)
        smr_r_roll = sampled_series(x_smr_r, y_smr_r, roll_vals, smr_r)
        kphi_arb_f_roll = bar_roll_stiffness(k_arb_f, smr_f_roll)
        kphi_arb_r_roll = bar_roll_stiffness(k_arb_r, smr_r_roll)
        kphi_el_f_roll = kphi_spr_f + kphi_arb_f_roll
        kphi_el_r_roll = kphi_spr_r + kphi_arb_r_roll
        kphi_total_roll = kphi_el_f_roll + kphi_el_r_roll
        lltd_stiffness_roll = np.divide(
            kphi_el_f_roll,
            kphi_total_roll,
            out=np.full_like(kphi_total_roll, float("nan"), dtype=float),
            where=np.abs(kphi_total_roll) > 1e-9,
        )
        lltd_stiffness_roll = _plausible_array(lltd_stiffness_roll, FOUR_POST_FRACTION_ABS_LIMIT)

        fr_l_fz_roll = roll_series["fr_l_fz_vs_roll"]
        fr_r_fz_roll = roll_series["fr_r_fz_vs_roll"]
        rr_l_fz_roll = roll_series["rr_l_fz_vs_roll"]
        rr_r_fz_roll = roll_series["rr_r_fz_vs_roll"]
        fr_l_fz_ref = _interp_with_extrap(0.0, roll_vals, fr_l_fz_roll)
        fr_r_fz_ref = _interp_with_extrap(0.0, roll_vals, fr_r_fz_roll)
        rr_l_fz_ref = _interp_with_extrap(0.0, roll_vals, rr_l_fz_roll)
        rr_r_fz_ref = _interp_with_extrap(0.0, roll_vals, rr_r_fz_roll)
        front_load_transfer_roll = (fr_l_fz_roll - fr_l_fz_ref) - (fr_r_fz_roll - fr_r_fz_ref)
        rear_load_transfer_roll = (rr_l_fz_roll - rr_l_fz_ref) - (rr_r_fz_roll - rr_r_fz_ref)
        front_load_transfer_roll = _plausible_array(front_load_transfer_roll)
        rear_load_transfer_roll = _plausible_array(rear_load_transfer_roll)
        total_load_transfer_roll = front_load_transfer_roll + rear_load_transfer_roll
        lltd_contact_roll = np.divide(
            front_load_transfer_roll,
            total_load_transfer_roll,
            out=np.full_like(total_load_transfer_roll, float("nan"), dtype=float),
            where=(np.abs(total_load_transfer_roll) > 1e-9)
            & (front_load_transfer_roll * rear_load_transfer_roll >= 0.0),
        )
        lltd_contact_roll = _plausible_array(lltd_contact_roll, FOUR_POST_FRACTION_ABS_LIMIT)
        lltd_roll = lltd_contact_roll.copy()
        lltd_geometry_delta_roll = _plausible_array(
            lltd_contact_roll - lltd_stiffness_roll,
            FOUR_POST_FRACTION_ABS_LIMIT,
        )

        kphi_arb_f = nanmean_or_nan(kphi_arb_f_roll)
        kphi_arb_r = nanmean_or_nan(kphi_arb_r_roll)
        kphi_el_f = kphi_spr_f + kphi_arb_f
        kphi_el_r = kphi_spr_r + kphi_arb_r

        gain_names = {
            "camber": ("camber_gain_heave_rad_per_m", "camber_gain_roll_rad_per_rad"),
            "toe": ("toe_gain_heave_rad_per_m", "toe_gain_roll_rad_per_rad"),
            "caster": ("caster_gain_heave_rad_per_m", "caster_gain_roll_rad_per_rad"),
            "kpi": ("kpi_gain_heave_rad_per_m", "kpi_gain_roll_rad_per_rad"),
            "trail": ("trail_gain_heave_m_per_m", "trail_gain_roll_m_per_rad"),
            "scrub": ("scrub_gain_heave_m_per_m", "scrub_gain_roll_m_per_rad"),
        }
        gains: dict[str, float] = {}
        for signal_key, (heave_name, roll_name) in gain_names.items():
            for name, x, y, count in (
                (heave_name, heave_vals, heave_series[f"fr_l_{signal_key}_vs_heave"], heave_count),
                (roll_name, roll_vals, roll_series[f"fr_l_{signal_key}_vs_roll"], roll_count),
            ):
                gains[name] = compute_gain(x, y)
                coverage(name, np.isfinite(x) & np.isfinite(y), count)

        share_count = roll_count - int(np.count_nonzero(np.abs(roll_vals) <= 1e-9))
        for name in ("avg_lltd_front_frac", "avg_lltd_front_pct"):
            coverage(name, np.isfinite(lltd_roll), share_count)
        coverage("avg_antiroll_geometry_lltd_delta_pct", np.isfinite(lltd_geometry_delta_roll), share_count)
        coverage("avg_roll_rate_distribution_front_pct", np.isfinite(lltd_stiffness_roll), roll_count)
        for axle_name, axle_corners, smr_samples, arb_samples in (
            ("front", corners[:2], y_smr_f, kphi_arb_f_roll),
            ("rear", corners[2:], y_smr_r, kphi_arb_r_roll),
        ):
            mr_samples = sum(motion_ratio_series[f"{corner}_motion_ratio_vs_heave"].size for corner in axle_corners)
            status[f"avg_motion_ratio_{axle_name}"] = _coverage_status(mr_samples, 2 * heave_count)
            status[f"spring_roll_stiffness_{axle_name}_Nm_per_rad"] = status[f"avg_motion_ratio_{axle_name}"]
            status[f"avg_stabar_motion_ratio_{axle_name}"] = _coverage_status(smr_samples.size, roll_count)
            coverage(f"arb_roll_stiffness_{axle_name}_Nm_per_rad", np.isfinite(arb_samples), roll_count)
            status[f"elastic_roll_stiffness_{axle_name}_Nm_per_rad"] = _worst_status(
                status[f"spring_roll_stiffness_{axle_name}_Nm_per_rad"],
                status[f"arb_roll_stiffness_{axle_name}_Nm_per_rad"],
            )
        self.metric_status = status

        summary = {
            **{k: float(v) for k, v in gains.items()},
            "avg_anti_dive_pct": _nanmean_plausible(fr_anti_heave, FOUR_POST_PERCENT_ABS_LIMIT),
            "avg_anti_squat_pct": _nanmean_plausible(rr_anti_heave, FOUR_POST_PERCENT_ABS_LIMIT),
            "avg_anti_roll_front_pct": _nanmean_plausible(fr_anti_roll, FOUR_POST_PERCENT_ABS_LIMIT),
            "avg_anti_roll_rear_pct": _nanmean_plausible(rr_anti_roll, FOUR_POST_PERCENT_ABS_LIMIT),
            "roll_contact_valid_points": int(np.count_nonzero(roll_contact_loaded)),
            "roll_contact_rejected_points": int(np.count_nonzero(~roll_contact_loaded)),
            "minimum_roll_pulse_contact_fz_n": float(np.nanmin(roll_contact_fz)),
            "avg_lltd_front_frac": _nanmean_plausible(lltd_roll, FOUR_POST_FRACTION_ABS_LIMIT),
            "avg_lltd_front_pct": float(100.0 * _nanmean_plausible(lltd_roll, FOUR_POST_FRACTION_ABS_LIMIT)),
            "avg_roll_rate_distribution_front_pct": float(
                100.0 * _nanmean_plausible(lltd_stiffness_roll, FOUR_POST_FRACTION_ABS_LIMIT)
            ),
            "avg_antiroll_geometry_lltd_delta_pct": float(
                100.0 * _nanmean_plausible(lltd_geometry_delta_roll, FOUR_POST_FRACTION_ABS_LIMIT)
            ),
            "avg_longitudinal_jacking_coeff_front": _nanmean_plausible(
                fr_coeff_heave,
                FOUR_POST_RATIO_ABS_LIMIT,
            ),
            "avg_longitudinal_jacking_coeff_rear": _nanmean_plausible(
                rr_coeff_heave,
                FOUR_POST_RATIO_ABS_LIMIT,
            ),
            "avg_lateral_jacking_coeff_front": _nanmean_plausible(
                fr_coeff_roll,
                FOUR_POST_RATIO_ABS_LIMIT,
            ),
            "avg_lateral_jacking_coeff_rear": _nanmean_plausible(
                rr_coeff_roll,
                FOUR_POST_RATIO_ABS_LIMIT,
            ),
            "avg_fbrc_equivalent_height_front_m": _nanmean_plausible(fr_fbrc_height),
            "avg_fbrc_equivalent_height_rear_m": _nanmean_plausible(rr_fbrc_height),
            "avg_fbrc_differential_jacking_ratio_front": _nanmean_plausible(fr_fbrc_ratio, FOUR_POST_RATIO_ABS_LIMIT),
            "avg_fbrc_differential_jacking_ratio_rear": _nanmean_plausible(rr_fbrc_ratio, FOUR_POST_RATIO_ABS_LIMIT),
            "avg_motion_ratio_front": float(mr_f),
            "avg_motion_ratio_rear": float(mr_r),
            "avg_stabar_motion_ratio_front": float(smr_f),
            "avg_stabar_motion_ratio_rear": float(smr_r),
            "spring_roll_stiffness_front_Nm_per_rad": float(kphi_spr_f),
            "spring_roll_stiffness_rear_Nm_per_rad": float(kphi_spr_r),
            "arb_roll_stiffness_front_Nm_per_rad": float(kphi_arb_f),
            "arb_roll_stiffness_rear_Nm_per_rad": float(kphi_arb_r),
            "elastic_roll_stiffness_front_Nm_per_rad": float(kphi_el_f),
            "elastic_roll_stiffness_rear_Nm_per_rad": float(kphi_el_r),
            "heave_cp_tension_points": int(np.count_nonzero(heave_tension)),
            "anti_force_path": FOUR_POST_ANTI_FORCE_PATH,
            **anti_path_summary,
        }

        series: dict[str, np.ndarray] = {
            "heave": heave_vals,
            "roll": roll_vals,
            **heave_series,
            **roll_series,
            **motion_ratio_series,
            **stabar_motion_ratio_series,
            "fr_jacking_vs_heave_x": fr_heave_x,
            "rr_jacking_vs_heave_x": rr_heave_x,
            "fr_anti_vs_heave": fr_anti_heave,
            "rr_anti_vs_heave": rr_anti_heave,
            "fr_jacking_vs_roll_x": fr_roll_x,
            "rr_jacking_vs_roll_x": rr_roll_x,
            "fr_anti_vs_roll": fr_anti_roll,
            "rr_anti_vs_roll": rr_anti_roll,
            "fr_fbrc_vs_roll_x": fr_fbrc_x,
            "rr_fbrc_vs_roll_x": rr_fbrc_x,
            "fr_fbrc_jacking_ratio_vs_roll": fr_fbrc_ratio,
            "rr_fbrc_jacking_ratio_vs_roll": rr_fbrc_ratio,
            "fr_fbrc_height_vs_roll": fr_fbrc_height,
            "rr_fbrc_height_vs_roll": rr_fbrc_height,
            "lltd_vs_roll_x": roll_vals,
            "lltd_vs_roll": lltd_roll,
            "lltd_contact_force_vs_roll": lltd_contact_roll,
            "lltd_stiffness_vs_roll": lltd_stiffness_roll,
            "lltd_antiroll_geometry_delta_vs_roll": lltd_geometry_delta_roll,
            "front_load_transfer_vs_roll": front_load_transfer_roll,
            "rear_load_transfer_vs_roll": rear_load_transfer_roll,
            "total_load_transfer_vs_roll": total_load_transfer_roll,
            "front_roll_stiffness_vs_roll": kphi_el_f_roll,
            "rear_roll_stiffness_vs_roll": kphi_el_r_roll,
            "total_roll_stiffness_vs_roll": kphi_total_roll,
        }

        return summary, series


def main(path: str | Path | None = None) -> dict[str, Any]:
    config_path = Path(path) if path is not None else DEFAULT_CONFIG_PATH
    config = load_config(config_path)
    _normalize_four_post_report_config(config)

    simulation = FourPostEvalSim(config)
    result = simulation.run()

    if _as_mapping(config.get("report"), name="report").get("enabled", True):
        ReportEngine(simulation.config).build(result)

    return result


if __name__ == "__main__":
    path = sys.argv[1] if len(sys.argv) > 1 else None
    main(path)
