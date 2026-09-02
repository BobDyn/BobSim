from __future__ import annotations

import csv
import copy
import sys
from pathlib import Path
from typing import Any, Sequence, cast

import numpy as np
import yaml

from _0_Utils.reporting.report_engine import ReportEngine
from _3_StandardSim._modelica_runner import ModelicaRunner


DEFAULT_CONFIG_PATH = Path("_3_StandardSim/FourPostEval/four_post_eval_config.yml")
DEFAULT_BUILD_DIR = "_3_StandardSim/BuildBobLib/FourPostSim"
DEFAULT_EXEC_NAME = "BobLib.Experiments.Standards.FourPostSim"
DEFAULT_METRICS_CSV_PATH = "_3_StandardSim/results/four_post_eval_report_metrics.csv"
REPO_ROOT = Path(__file__).resolve().parents[2]
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

FOUR_POST_EVAL_VARIABLE_FILTER = "|".join(FOUR_POST_EVAL_SIGNALS)


def load_config(path: str | Path) -> dict[str, Any]:
    path = Path(path)
    with path.open("r", encoding="utf-8") as f:
        config = yaml.safe_load(f)

    if config is None:
        raise ValueError(f"Config file is empty: {path}")
    if not isinstance(config, dict):
        raise TypeError(f"Expected YAML config to contain a mapping at top level: {path}")

    return cast(dict[str, Any], config)


def _four_post_jacking_roll_plot_config() -> dict[str, Any]:
    return {
        "layout": "dual",
        "title": "Geometric Anti-Roll vs Roll",
        "subplots": [
            {
                "title": "Front",
                "x": {
                    "key": "fr_jacking_vs_roll_x",
                    "scale": 57.2958,
                    "label": "Roll (deg)",
                },
                "y": {"key": "fr_anti_vs_roll", "label": "Geometric Anti-Roll (%)"},
            },
            {
                "title": "Rear",
                "x": {
                    "key": "rr_jacking_vs_roll_x",
                    "scale": 57.2958,
                    "label": "Roll (deg)",
                },
                "y": {"key": "rr_anti_vs_roll", "label": "Geometric Anti-Roll (%)"},
            },
        ],
    }


def _four_post_fbrc_roll_plot_config() -> dict[str, Any]:
    return {
        "layout": "dual",
        "title": "FBRC-Equivalent Height vs Roll (Loaded Contact Patches Only)",
        "subplots": [
            {
                "title": "Front",
                "x": {
                    "key": "fr_fbrc_vs_roll_x",
                    "scale": 57.2958,
                    "label": "Roll (deg)",
                },
                "y": {
                    "key": "fr_fbrc_height_vs_roll",
                    "scale": 1000.0,
                    "label": "FBRC-equivalent height (mm)",
                },
            },
            {
                "title": "Rear",
                "x": {
                    "key": "rr_fbrc_vs_roll_x",
                    "scale": 57.2958,
                    "label": "Roll (deg)",
                },
                "y": {
                    "key": "rr_fbrc_height_vs_roll",
                    "scale": 1000.0,
                    "label": "FBRC-equivalent height (mm)",
                },
            },
        ],
    }


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
        plots_cfg["jacking_roll"] = copy.deepcopy(_four_post_jacking_roll_plot_config())
        plots_cfg["fbrc_roll"] = copy.deepcopy(_four_post_fbrc_roll_plot_config())
    return config


def _as_mapping(value: Any, *, name: str) -> dict[str, Any]:
    if value is None:
        return {}
    if not isinstance(value, dict):
        raise TypeError(f"Expected {name} to be a mapping if provided.")
    return cast(dict[str, Any], value)


def write_metrics_csv(summary: dict[str, Any], path: str | Path) -> Path:
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.unlink(missing_ok=True)

    with path.open("w", newline="", encoding="utf-8") as f:
        writer = csv.writer(f, lineterminator="\n")
        writer.writerow(["metric", "value"])
        for key in sorted(summary):
            value = summary[key]
            if isinstance(value, float) and np.isnan(value):
                value = ""
            writer.writerow([key, value])

    return path


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


def _force_denominator_series(measured_force: Any, fallback_abs_force: float) -> np.ndarray:
    measured = _plausible_array(measured_force)
    fallback_abs_force = abs(float(fallback_abs_force))
    fallback = np.full(measured.shape, fallback_abs_force, dtype=float)
    if fallback_abs_force <= 0.0:
        return measured

    min_force = max(1e-3, 0.05 * fallback_abs_force)
    max_force = 5.0 * fallback_abs_force
    measured_ok = _finite_abs_mask(measured) & (np.abs(measured) >= min_force) & (np.abs(measured) <= max_force)
    return np.where(measured_ok, measured, fallback)


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


def _has_variation(
    values: Any,
    *,
    min_range_abs: float,
    max_abs: float = FOUR_POST_SIGNAL_ABS_LIMIT,
) -> bool:
    arr = _plausible_array(values, max_abs)
    finite = arr[np.isfinite(arr)]
    if finite.size < 2:
        return False
    return bool(float(np.nanmax(finite) - np.nanmin(finite)) > float(min_range_abs))


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
    front_spring_table = _linearize_spring_table_rate(front_vehicle_table, front_spring_rate)
    rear_spring_table = _linearize_spring_table_rate(rear_vehicle_table, rear_spring_rate)
    corner_loads = _sprung_corner_loads(vehicle)

    return {
        "front_side": front_side,
        "rear_side": rear_side,
        "front_spring_rate": front_spring_rate,
        "rear_spring_rate": rear_spring_rate,
        "front_spring_table": front_spring_table,
        "rear_spring_table": rear_spring_table,
        "front_spring_free_length": _configured_spring_free_length(
            config,
            front_cfg,
            "front",
            front_side,
            front_spring_table,
            corner_loads["front"],
        ),
        "rear_spring_free_length": _configured_spring_free_length(
            config,
            rear_cfg,
            "rear",
            rear_side,
            rear_spring_table,
            corner_loads["rear"],
        ),
        "front_stabar_rate": front_stabar_rate,
        "rear_stabar_rate": rear_stabar_rate,
    }


def _side_installed_spring_length(side: dict[str, Any]) -> float:
    actuation = _nested_value(side, "actuation")
    shock_mount = np.asarray(_nested_value(actuation, "shock", "mount_m"), dtype=float)
    if "bellcrank" in actuation:
        shock_pickup = np.asarray(_nested_value(actuation, "bellcrank", "pickups_m", "shock"), dtype=float)
        return float(np.linalg.norm(shock_mount - shock_pickup))

    rod_mount = np.asarray(_nested_value(actuation, "rod_mount_m"), dtype=float)
    return float(np.linalg.norm(shock_mount - rod_mount))


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


def _static_contact_load_n(sprung_corner_load_n: float, unsprung_corner_mass_kg: float) -> float:
    return float(sprung_corner_load_n + unsprung_corner_mass_kg * GRAVITY_MPS2)


def _metrics_csv_value(config: dict[str, Any], metric: str) -> float:
    report_cfg = _as_mapping(config.get("report"), name="report")
    metrics_path = Path(str(report_cfg.get("metrics_csv_path", DEFAULT_METRICS_CSV_PATH)))
    if not metrics_path.is_absolute():
        metrics_path = REPO_ROOT / metrics_path
    if not metrics_path.exists():
        return float("nan")

    with metrics_path.open(newline="", encoding="utf-8") as f:
        for row in csv.DictReader(f):
            if row.get("metric") != metric:
                continue
            try:
                return float(row.get("value", "nan"))
            except ValueError:
                return float("nan")
    return float("nan")


def _computed_motion_ratio(config: dict[str, Any], axle_name: str) -> float:
    for metric in (
        f"static_motion_ratio_{axle_name}",
        f"avg_motion_ratio_{axle_name}",
    ):
        value = _metrics_csv_value(config, metric)
        if np.isfinite(value) and abs(value) > 1e-12:
            return value
    return float("nan")


def _static_balance_free_length(
    side: dict[str, Any],
    spring_table: np.ndarray,
    motion_ratio: float,
    sprung_corner_loads_n: tuple[float, float],
) -> float:
    if not np.isfinite(motion_ratio) or abs(motion_ratio) <= 1e-12:
        return float("nan")

    compressions = [_force_to_deflection(spring_table, load_n * motion_ratio) for load_n in sprung_corner_loads_n]
    compression = float(np.nanmean(np.asarray(compressions, dtype=float)))
    if not np.isfinite(compression):
        return float("nan")
    return _side_installed_spring_length(side) + compression


def _configured_spring_free_length(
    config: dict[str, Any],
    axle_cfg: dict[str, Any],
    axle_name: str,
    side: dict[str, Any],
    spring_table: np.ndarray,
    sprung_corner_loads_n: tuple[float, float],
) -> float:
    explicit = _configured_optional_float(
        axle_cfg,
        ("spring_free_length_m", "free_length_m", "spring_free_length"),
    )
    if explicit is not None:
        return explicit

    motion_ratio = _computed_motion_ratio(config, axle_name)
    balanced = _static_balance_free_length(
        side,
        spring_table,
        motion_ratio,
        sprung_corner_loads_n,
    )
    if np.isfinite(balanced):
        return balanced
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


def _static_balance_iterations(config: dict[str, Any]) -> int:
    model_overrides = _as_mapping(config.get("model_overrides"), name="model_overrides")
    suspension_cfg = _as_mapping(
        model_overrides.get("suspension"),
        name="model_overrides.suspension",
    )
    return max(1, int(suspension_cfg.get("static_balance_iterations", 3)))


def _static_balance_convergence_n(config: dict[str, Any]) -> float:
    model_overrides = _as_mapping(config.get("model_overrides"), name="model_overrides")
    suspension_cfg = _as_mapping(
        model_overrides.get("suspension"),
        name="model_overrides.suspension",
    )
    return max(0.0, float(suspension_cfg.get("static_balance_convergence_n", 0.01)))


def _series_value_at(
    series: dict[str, np.ndarray],
    x_key: str,
    y_key: str,
    x_value: float,
) -> float:
    x = np.asarray(series.get(x_key, []), dtype=float).reshape(-1)
    y = np.asarray(series.get(y_key, []), dtype=float).reshape(-1)
    if x.size != y.size or x.size < 2:
        return float("nan")
    return _interp_with_extrap(float(x_value), x, y)


def _static_balance_summary(setup: dict[str, Any]) -> dict[str, Any]:
    errors_n: list[float] = []
    errors_pct: list[float] = []
    passes: list[bool] = []
    static_motion_ratios: dict[str, list[float]] = {"front": [], "rear": []}

    for axle_name in ("front", "rear"):
        axle = setup.get(axle_name, {})
        if not isinstance(axle, dict):
            continue
        axle_errors_n: list[float] = []
        axle_errors_pct: list[float] = []
        for side_name in ("left", "right"):
            corner = axle.get(side_name, {})
            if not isinstance(corner, dict):
                continue
            error_n = float(corner.get("static_fz_error_N", float("nan")))
            error_pct = float(corner.get("static_fz_error_pct", float("nan")))
            if np.isfinite(error_n):
                axle_errors_n.append(error_n)
            if np.isfinite(error_pct):
                axle_errors_pct.append(error_pct)
            static_mr = float(corner.get("motion_ratio", float("nan")))
            if np.isfinite(static_mr):
                static_motion_ratios[axle_name].append(static_mr)
            passes.append(bool(corner.get("static_balance_ok", False)))
        if axle_errors_n:
            errors_n.append(abs(float(np.mean(axle_errors_n))))
        if axle_errors_pct:
            errors_pct.append(abs(float(np.mean(axle_errors_pct))))

    return {
        "static_balance_max_abs_fz_error_n": max(errors_n) if errors_n else float("nan"),
        "static_balance_max_abs_fz_error_pct": max(errors_pct) if errors_pct else float("nan"),
        "static_balance_pass": bool(passes and all(passes)),
        "static_motion_ratio_front": (
            float(np.mean(static_motion_ratios["front"])) if static_motion_ratios["front"] else float("nan")
        ),
        "static_motion_ratio_rear": (
            float(np.mean(static_motion_ratios["rear"])) if static_motion_ratios["rear"] else float("nan")
        ),
    }


def _static_balance_corrected_overrides(
    overrides: dict[str, float],
    setup: dict[str, Any],
) -> dict[str, float]:
    corrected = dict(overrides)
    for axle_name, override_key in (
        ("front", "pVehicle.pFrAxleDW.springFreeLength"),
        ("rear", "pVehicle.pRrAxleDW.springFreeLength"),
    ):
        axle = setup.get(axle_name, {})
        if not isinstance(axle, dict) or override_key not in corrected:
            continue

        length_corrections: list[float] = []
        for side_name in ("left", "right"):
            corner = axle.get(side_name, {})
            if not isinstance(corner, dict):
                continue

            error_n = float(corner.get("static_fz_error_N", float("nan")))
            motion_ratio = float(corner.get("motion_ratio", float("nan")))
            spring_rate = float(corner.get("spring_rate_N_per_m", float("nan")))
            if (
                np.isfinite(error_n)
                and np.isfinite(motion_ratio)
                and np.isfinite(spring_rate)
                and abs(motion_ratio) > 1e-12
                and spring_rate > 0.0
            ):
                length_corrections.append(error_n * motion_ratio / spring_rate)

        if length_corrections:
            corrected[override_key] = float(corrected[override_key] - np.mean(length_corrections))

    return corrected


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


def _force_to_deflection(spring_table: Any, force_n: float) -> float:
    table = _table_array(spring_table)
    deflection = table[:, 0]
    force = table[:, 1]
    return _interp_with_extrap(force_n, force, deflection)


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
    if sprung_mass_kg <= 0.0 or unsprung_mass_kg <= 0.0 or wheel_rate_n_per_m <= 0.0 or tire_rate_n_per_m <= 0.0:
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
        self.config = config

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
            "pVehicle.pFrAxleDW.springFreeLength": float(setup["front_spring_free_length"]),
            "pVehicle.pRrAxleDW.springFreeLength": float(setup["rear_spring_free_length"]),
            "pVehicle.pFrStabar.barRate": front_stabar_rate,
            "pVehicle.pRrStabar.barRate": rear_stabar_rate,
            # FourPost templates zero the exposed bars for pure-K&C runs; set
            # the public bar records for the physical load-transfer pass.
            "pFrStabar.barRate": front_stabar_rate,
            "pRrStabar.barRate": rear_stabar_rate,
        }
        overrides.update(
            _indexed_table_overrides(
                "pVehicle.pFrAxleDW.springTable",
                front_spring_table,
            )
        )
        overrides.update(
            _indexed_table_overrides(
                "pVehicle.pRrAxleDW.springTable",
                rear_spring_table,
            )
        )
        return overrides

    def build_setup(self, summary: dict[str, Any], series: dict[str, np.ndarray]) -> dict[str, Any]:
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

        corners: dict[str, dict[str, Any]] = {}

        for axle_name, axle in axle_specs.items():
            side = axle["side"]
            axle_fraction = float(axle["axle_fraction"])
            axle_unsprung_mass = corner_unsprung_mass(side)
            axle_installed_length_m = _side_installed_spring_length(side)
            axle_tire_rate = tire_rate(side)
            axle_spring_table = (
                suspension_setup["front_spring_table"]
                if axle_name == "front"
                else suspension_setup["rear_spring_table"]
            )
            motion_ratio_key = "avg_motion_ratio_front" if axle_name == "front" else "avg_motion_ratio_rear"
            axle_sprung_loads = {
                "left": sprung_mass_kg * axle_fraction * left_fraction * GRAVITY_MPS2,
                "right": sprung_mass_kg * axle_fraction * right_fraction * GRAVITY_MPS2,
            }

            for corner_name, corner_key in axle["corner_pairs"]:
                corner_fraction = axle_fraction * (left_fraction if corner_name == "left" else right_fraction)
                sprung_corner_mass = sprung_mass_kg * corner_fraction
                sprung_corner_load = float(axle_sprung_loads[corner_name])
                static_balance_target_load = sprung_corner_load
                static_contact_load = _static_contact_load_n(
                    sprung_corner_load,
                    axle_unsprung_mass,
                )

                static_mr = _static_motion_ratio(
                    series,
                    corner_key,
                    float(summary.get(motion_ratio_key, float("nan"))),
                )
                spring_force = static_balance_target_load * static_mr
                spring_wheel_load = (
                    spring_force / static_mr if np.isfinite(static_mr) and abs(static_mr) > 1e-12 else float("nan")
                )
                spring_compression_m = _force_to_deflection(axle_spring_table, spring_force)
                spring_rate = _spring_rate_at_deflection(axle_spring_table, spring_compression_m)
                wheel_rate = (
                    spring_rate / (static_mr**2) if np.isfinite(static_mr) and abs(static_mr) > 1e-12 else float("nan")
                )
                free_length_m = axle_installed_length_m + spring_compression_m
                fixture_static_fz_n = _series_value_at(
                    series,
                    "heave",
                    f"{corner_key}_fz_vs_heave",
                    0.0,
                )
                static_fz_n = static_contact_load
                static_fz_error_n = spring_wheel_load - static_balance_target_load
                static_fz_error_pct = (
                    100.0 * static_fz_error_n / static_balance_target_load
                    if abs(static_balance_target_load) > 1e-12
                    else float("nan")
                )
                static_balance_limit_n = max(
                    static_balance_tol_n,
                    abs(static_balance_target_load) * static_balance_tol_pct / 100.0,
                )
                static_balance_ok = bool(
                    np.isfinite(static_fz_error_n) and abs(static_fz_error_n) <= static_balance_limit_n
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
                    "sprung_load_N": float(sprung_corner_load),
                    "static_balance_target_load_N": float(static_balance_target_load),
                    "motion_ratio": float(static_mr),
                    "spring_rate_N_per_m": float(spring_rate),
                    "spring_force_N": float(spring_force),
                    "spring_wheel_load_N": float(spring_wheel_load),
                    "spring_compression_m": float(spring_compression_m),
                    "spring_installed_length_m": float(axle_installed_length_m),
                    "spring_free_length_m": float(free_length_m),
                    "static_fixture_fz_N": float(fixture_static_fz_n),
                    "static_fz_N": float(static_fz_n),
                    "static_fz_error_N": float(static_fz_error_n),
                    "static_fz_error_pct": float(static_fz_error_pct),
                    "static_balance_limit_N": float(static_balance_limit_n),
                    "static_balance_ok": static_balance_ok,
                    "wheel_rate_N_per_m": float(wheel_rate),
                    "sprung_frequency_hz": float(sprung_mode_hz),
                    "unsprung_frequency_hz": float(unsprung_mode_hz),
                }

        setup = {
            "subtitle": "Static spring setup from the active vehicle pose and FourPost motion ratios.",
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

        base_overrides = self.build_overrides()
        setup_overrides = self.build_model_setup_overrides()
        max_static_balance_iterations = _static_balance_iterations(self.config)
        static_balance_convergence_n = _static_balance_convergence_n(self.config)
        results: list[dict[str, Any]] = []
        summary: dict[str, Any] = {}
        series: dict[str, np.ndarray] = {}
        setup: dict[str, Any] = {}

        for iteration_idx in range(max_static_balance_iterations):
            results = runner.run(
                signals=FOUR_POST_EVAL_SIGNALS,
                mode="raw",
                cases=[
                    {
                        **base_overrides,
                        **setup_overrides,
                        "_case_label": f"static balance {iteration_idx + 1}",
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
            setup = self.build_setup(summary, series)
            summary.update(_static_balance_summary(setup))
            summary["static_balance_iterations"] = iteration_idx + 1
            max_abs_error_n = float(summary.get("static_balance_max_abs_fz_error_n", float("nan")))
            if np.isfinite(max_abs_error_n) and max_abs_error_n <= static_balance_convergence_n:
                break

            corrected_overrides = _static_balance_corrected_overrides(
                setup_overrides,
                setup,
            )
            if corrected_overrides == setup_overrides:
                break
            setup_overrides = corrected_overrides

        metrics_csv_path = write_metrics_csv(
            summary,
            report_cfg.get("metrics_csv_path", DEFAULT_METRICS_CSV_PATH),
        )

        return {
            "summary": summary,
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
                if np.any(window):
                    samples.append(float(np.nanmedian(signal[window])))
                    continue

                valid_signal = valid_time & np.isfinite(signal)
                if not np.any(valid_signal):
                    samples.append(float("nan"))
                    continue

                local_index = int(np.nanargmin(np.abs(time[valid_signal] - ti)))
                samples.append(float(signal[valid_signal][local_index]))
            return np.array(samples, dtype=float)

        def sample_in_window(signal: np.ndarray, center_s: float, half_window_s: float) -> float:
            signal = _plausible_array(signal)
            size = min(t.size, signal.size)
            time = t[:size]
            signal = signal[:size]
            valid = np.isfinite(time) & np.isfinite(signal)
            window = valid & (np.abs(time - center_s) <= half_window_s)
            if np.any(window):
                return float(np.nanmedian(signal[window]))
            if not np.any(valid):
                return float("nan")
            local_index = int(np.nanargmin(np.abs(time[valid] - center_s)))
            return float(signal[valid][local_index])

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
                fallback_pulse_time = pose_start + 1.5
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
                    if np.any(pulse_window):
                        candidates = np.flatnonzero(pulse_window)
                        selected_index = int(candidates[np.nanargmin(np.abs(time[candidates] - fallback_pulse_time))])
                        pose_pulse = float(pose[selected_index])
                        response_pulse = float(response[selected_index])
                        force_pulse = (
                            float(force[selected_index]) if np.isfinite(force[selected_index]) else float("nan")
                        )
                    else:
                        pose_pulse = sample_at_times(pose_signal, [fallback_pulse_time])[0]
                        response_pulse = float("nan")
                        force_pulse = sample_at_times(force_signal, [fallback_pulse_time])[0]
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

        for key, suffix in signals.items():
            for corner in corners:
                prefix = side_prefix(corner)
                heave_sig = sample_at_times(corner_signal(prefix, corner, suffix), heave_sample_times)
                roll_sig = sample_at_times(corner_signal(prefix, corner, suffix), roll_sample_times)

                heave_sig = heave_sig[heave_mask]
                roll_sig = roll_sig[roll_mask]
                heave_series[f"{corner}_{key}_vs_heave"] = heave_sig[heave_idx]
                roll_series[f"{corner}_{key}_vs_roll"] = roll_sig[roll_idx]

        # Jacking is the incremental chassis reaction from the force pulse at a
        # fixed pose, not the absolute axle support load. Subtract the dead-tail
        # force at the same pose so we only retain the load introduced by the
        # heave/roll force pulse.
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
        validation_cfg = _as_mapping(self.config.get("validation"), name="validation")
        min_contact_fz_n = float(validation_cfg.get("min_contact_fz_n", FOUR_POST_MIN_CONTACT_FZ_N))
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
        fr_total_fz = corner_signal("frKnC", "fr_l", "Fz") + corner_signal("frKnC", "fr_r", "Fz")
        rr_total_fz = corner_signal("rrKnC", "rr_l", "Fz") + corner_signal("rrKnC", "rr_r", "Fz")
        _, fr_roll_fz_delta, _ = sample_force_pulses(
            roll,
            fr_total_fz,
            fr_fy,
            start_s=FOUR_POST_ROLL_START_S,
            count=FOUR_POST_ROLL_POSE_COUNT,
        )
        _, rr_roll_fz_delta, _ = sample_force_pulses(
            roll,
            rr_total_fz,
            rr_fy,
            start_s=FOUR_POST_ROLL_START_S,
            count=FOUR_POST_ROLL_POSE_COUNT,
        )
        procedure_cfg = _as_mapping(self.config.get("procedure"), name="procedure")
        roll_force_denominator_n = FOUR_POST_FORCE_SAMPLE_FRACTION * abs(
            float(procedure_cfg.get("forceMagnitude", 1000.0))
        )
        min_roll_jacking_variation_n = max(1e-6, 1e-5 * roll_force_denominator_n)
        if not _has_variation(fr_roll_jack_y, min_range_abs=min_roll_jacking_variation_n) and _has_variation(
            fr_roll_fz_delta, min_range_abs=min_roll_jacking_variation_n
        ):
            fr_roll_jack_y = fr_roll_fz_delta
        if not _has_variation(rr_roll_jack_y, min_range_abs=min_roll_jacking_variation_n) and _has_variation(
            rr_roll_fz_delta, min_range_abs=min_roll_jacking_variation_n
        ):
            rr_roll_jack_y = rr_roll_fz_delta
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

        fr_anti_heave = _plausible_array(100.0 * fr_coeff_heave / ref_long, FOUR_POST_PERCENT_ABS_LIMIT)
        rr_anti_heave = _plausible_array(100.0 * rr_coeff_heave / ref_long, FOUR_POST_PERCENT_ABS_LIMIT)
        fr_anti_roll = _plausible_array(100.0 * fr_coeff_roll / ref_roll, FOUR_POST_PERCENT_ABS_LIMIT)
        rr_anti_roll = _plausible_array(100.0 * rr_coeff_roll / ref_roll, FOUR_POST_PERCENT_ABS_LIMIT)

        # Force-based roll-center equivalent height from moment equivalence:
        # h_eq = (track / 2) * (delta_Fz,right - delta_Fz,left) / Fy.
        # This is deliberately separate from geometric anti-roll, which uses
        # the total axle jacking reaction rather than the left/right load split.
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

        def fill_from_finite_neighbors(x: np.ndarray, y: np.ndarray) -> np.ndarray:
            x = np.asarray(x, dtype=float).reshape(-1)
            y = np.asarray(y, dtype=float).reshape(-1).copy()
            finite = _finite_abs_mask(x) & _finite_abs_mask(y)
            missing = np.isfinite(x) & ~np.isfinite(y)
            if not missing.any() or finite.sum() < 2:
                return y

            y[missing] = np.asarray(
                [_interp_with_extrap(float(xi), x[finite], y[finite]) for xi in x[missing]],
                dtype=float,
            )
            return y

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
        front_load_transfer_roll = np.abs((fr_l_fz_roll - fr_l_fz_ref) - (fr_r_fz_roll - fr_r_fz_ref))
        rear_load_transfer_roll = np.abs((rr_l_fz_roll - rr_l_fz_ref) - (rr_r_fz_roll - rr_r_fz_ref))
        front_load_transfer_roll = _plausible_array(front_load_transfer_roll)
        rear_load_transfer_roll = _plausible_array(rear_load_transfer_roll)
        total_load_transfer_roll = front_load_transfer_roll + rear_load_transfer_roll
        lltd_contact_roll = np.divide(
            front_load_transfer_roll,
            total_load_transfer_roll,
            out=np.full_like(total_load_transfer_roll, float("nan"), dtype=float),
            where=total_load_transfer_roll > 1e-9,
        )
        lltd_contact_roll = _plausible_array(lltd_contact_roll, FOUR_POST_FRACTION_ABS_LIMIT)
        lltd_contact_roll = fill_from_finite_neighbors(roll_vals, lltd_contact_roll)
        lltd_roll = lltd_contact_roll.copy()
        lltd_geometry_delta_roll = _plausible_array(
            lltd_contact_roll - lltd_stiffness_roll,
            FOUR_POST_FRACTION_ABS_LIMIT,
        )

        kphi_arb_f = nanmean_or_nan(kphi_arb_f_roll)
        kphi_arb_r = nanmean_or_nan(kphi_arb_r_roll)
        kphi_el_f = kphi_spr_f + kphi_arb_f
        kphi_el_r = kphi_spr_r + kphi_arb_r

        gains = {
            "camber_gain_heave_rad_per_m": compute_gain(heave_vals, heave_series["fr_l_camber_vs_heave"]),
            "toe_gain_heave_rad_per_m": compute_gain(heave_vals, heave_series["fr_l_toe_vs_heave"]),
            "caster_gain_heave_rad_per_m": compute_gain(heave_vals, heave_series["fr_l_caster_vs_heave"]),
            "kpi_gain_heave_rad_per_m": compute_gain(heave_vals, heave_series["fr_l_kpi_vs_heave"]),
            "trail_gain_heave_m_per_m": compute_gain(heave_vals, heave_series["fr_l_trail_vs_heave"]),
            "scrub_gain_heave_m_per_m": compute_gain(heave_vals, heave_series["fr_l_scrub_vs_heave"]),
            "camber_gain_roll_rad_per_rad": compute_gain(roll_vals, roll_series["fr_l_camber_vs_roll"]),
            "toe_gain_roll_rad_per_rad": compute_gain(roll_vals, roll_series["fr_l_toe_vs_roll"]),
            "caster_gain_roll_rad_per_rad": compute_gain(roll_vals, roll_series["fr_l_caster_vs_roll"]),
            "kpi_gain_roll_rad_per_rad": compute_gain(roll_vals, roll_series["fr_l_kpi_vs_roll"]),
            "trail_gain_roll_m_per_rad": compute_gain(roll_vals, roll_series["fr_l_trail_vs_roll"]),
            "scrub_gain_roll_m_per_rad": compute_gain(roll_vals, roll_series["fr_l_scrub_vs_roll"]),
        }

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

    result = FourPostEvalSim(config).run()

    if _as_mapping(config.get("report"), name="report").get("enabled", True):
        ReportEngine(config).build(result)

    return result


if __name__ == "__main__":
    path = sys.argv[1] if len(sys.argv) > 1 else None
    main(path)
