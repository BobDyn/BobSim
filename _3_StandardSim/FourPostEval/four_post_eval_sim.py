from __future__ import annotations

import csv
import sys
from pathlib import Path
from typing import Any, Sequence, cast

import numpy as np
import yaml

from _0_Utils.reporting.report_engine import ReportEngine
from _3_StandardSim._modelica_runner import ModelicaRunner


DEFAULT_CONFIG_PATH = Path("_3_StandardSim/FourPostEval/four_post_eval_config.yml")
DEFAULT_BUILD_DIR = "_3_StandardSim/Build/FourPostSim"
DEFAULT_EXEC_NAME = "BobLib.Standards.FourPostSim"
DEFAULT_METRICS_CSV_PATH = "_3_StandardSim/results/four_post_eval_report_metrics.csv"
REPO_ROOT = Path(__file__).resolve().parents[2]
ACTIVE_VEHICLE_YAML_CANDIDATES = (
    REPO_ROOT / "_0_Utils/external/BobLib/Generation/vehicle.yml",
    REPO_ROOT / "vehicle.yml",
)
GRAVITY_MPS2 = 9.80665


FOUR_POST_EVAL_SIGNALS = [
    "frKnC.heave",
    "frKnC.roll",
    "frKnC.fx",
    "frKnC.fy",
    "frKnC.leftSpringLength",
    "frKnC.leftGamma",
    "frKnC.leftToe",
    "frKnC.leftCaster",
    "frKnC.leftKpi",
    "frKnC.leftMechTrail",
    "frKnC.leftMechScrub",
    "frKnC.rightSpringLength",
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
    "rrKnC.leftGamma",
    "rrKnC.leftToe",
    "rrKnC.leftCaster",
    "rrKnC.leftKpi",
    "rrKnC.leftMechTrail",
    "rrKnC.leftMechScrub",
    "rrKnC.rightSpringLength",
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
        writer = csv.writer(f)
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
    if (
        sprung_mass_kg <= 0.0
        or unsprung_mass_kg <= 0.0
        or wheel_rate_n_per_m <= 0.0
        or tire_rate_n_per_m <= 0.0
    ):
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

        return {
            "steerMagnitude": procedure.get("steerMagnitude", 0.0),
            "heaveMagnitude": procedure.get("heaveMagnitude", 0.03),
            "rollMagnitude": procedure.get("rollMagnitude", 0.035),
            "forceMagnitude": procedure.get("forceMagnitude", 1000.0),
        }

    def build_setup(self, summary: dict[str, Any], series: dict[str, np.ndarray]) -> dict[str, Any]:
        vehicle = _load_active_vehicle_yaml()
        sprung_mass_kg, sprung_cg_m = _combine_sprung_mass(vehicle)

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
            for key in ("unsprung", "upper_control_arm", "lower_control_arm", "tie_rod"):
                total += float(_nested_value(masses, key, "mass_kg"))
            return total

        def spring_table(side: dict[str, Any]) -> np.ndarray:
            shock = _nested_value(side, "actuation", "shock")
            table = shock.get("spring_table")
            if isinstance(table, dict):
                table = table.get("table")
            return _table_array(table)

        def installed_length(side: dict[str, Any]) -> float:
            actuation = _nested_value(side, "actuation")
            shock_mount = np.asarray(_nested_value(actuation, "shock", "mount_m"), dtype=float)
            if "bellcrank" in actuation:
                shock_pickup = np.asarray(_nested_value(actuation, "bellcrank", "pickups_m", "shock"), dtype=float)
                return float(np.linalg.norm(shock_mount - shock_pickup))
            rod_mount = np.asarray(_nested_value(actuation, "rod_mount_m"), dtype=float)
            return float(np.linalg.norm(shock_mount - rod_mount))

        def tire_rate(side: dict[str, Any]) -> float:
            return float(_nested_value(side, "tire", "vertical_stiffness_n_per_m"))

        corners: dict[str, dict[str, Any]] = {}

        for axle_name, axle in axle_specs.items():
            side = axle["side"]
            axle_fraction = float(axle["axle_fraction"])
            axle_unsprung_mass = corner_unsprung_mass(side)
            axle_installed_length_m = installed_length(side)
            axle_tire_rate = tire_rate(side)
            axle_spring_table = spring_table(side)
            motion_ratio_key = (
                "avg_motion_ratio_front" if axle_name == "front" else "avg_motion_ratio_rear"
            )

            for corner_name, corner_key in axle["corner_pairs"]:
                corner_fraction = axle_fraction * (left_fraction if corner_name == "left" else right_fraction)
                sprung_corner_mass = sprung_mass_kg * corner_fraction
                sprung_corner_load = sprung_corner_mass * GRAVITY_MPS2

                static_mr = _static_motion_ratio(
                    series,
                    corner_key,
                    float(summary.get(motion_ratio_key, float("nan"))),
                )
                spring_force = sprung_corner_load * static_mr
                spring_compression_m = _force_to_deflection(axle_spring_table, spring_force)
                spring_rate = _spring_rate_at_deflection(axle_spring_table, spring_compression_m)
                wheel_rate = (
                    spring_rate / (static_mr**2)
                    if np.isfinite(static_mr) and abs(static_mr) > 1e-12
                    else float("nan")
                )
                free_length_m = axle_installed_length_m + spring_compression_m
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
                    "motion_ratio": float(static_mr),
                    "spring_rate_N_per_m": float(spring_rate),
                    "spring_force_N": float(spring_force),
                    "spring_compression_m": float(spring_compression_m),
                    "spring_installed_length_m": float(axle_installed_length_m),
                    "spring_free_length_m": float(free_length_m),
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

        results = runner.run(
            signals=FOUR_POST_EVAL_SIGNALS,
            mode="raw",
            cases=[self.build_overrides()],
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
        t = np.asarray(result["time"], dtype=float).reshape(-1)

        def sig(prefix: str, name: str) -> np.ndarray:
            return np.asarray(result[f"{prefix}.{name}"], dtype=float).reshape(-1)

        def sample_at_times(signal: np.ndarray, times: list[float]) -> np.ndarray:
            return np.array([signal[np.argmin(np.abs(t - ti))] for ti in times], dtype=float)

        def compute_gain(x: np.ndarray, y: np.ndarray) -> float:
            mask = np.isfinite(x) & np.isfinite(y)
            x = x[mask]
            y = y[mask]
            if x.size < 2 or y.size < 2:
                return float("nan")
            if np.nanstd(x) < 1e-12 or np.nanstd(y) < 1e-12:
                return float("nan")
            coeffs = np.polyfit(x, y, 1)
            return float(coeffs[0])

        def nanmean_or_nan(values: Sequence[float]) -> float:
            arr = np.asarray(list(values), dtype=float)
            if arr.size == 0 or not np.isfinite(arr).any():
                return float("nan")
            return float(np.nanmean(arr))

        # FourPost uses a 5 s pose cadence with a short load pulse and a dead tail.
        pose_step_s = 5.0
        heave_pose_start_s = 2.0
        heave_pose_count = 10
        roll_pose_start_s = 58.0
        roll_pose_count = 11

        def pose_sample_times(start_s: float, count: int) -> list[float]:
            # Sample inside the dead region after the load pulse, before the next pose change.
            return [start_s + pose_step_s * i + 4.0 for i in range(count)]

        def jack_times(start_s: float, count: int) -> list[float]:
            return [start_s + pose_step_s * i + 1.5 for i in range(count)]

        heave_sample_times = pose_sample_times(heave_pose_start_s, heave_pose_count)
        roll_sample_times = pose_sample_times(roll_pose_start_s, roll_pose_count)
        heave_jack_times = jack_times(heave_pose_start_s, heave_pose_count)
        roll_jack_times = jack_times(roll_pose_start_s, roll_pose_count)

        signals = {
            "camber": "Gamma",
            "toe": "Toe",
            "caster": "Caster",
            "kpi": "Kpi",
            "trail": "MechTrail",
            "scrub": "MechScrub",
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

        fr_heave_jack_x = sample_at_times(heave, heave_jack_times)
        fr_heave_jack_y = sample_at_times(fr_jack, heave_jack_times) - sample_at_times(
            fr_jack, heave_sample_times
        )
        rr_heave_jack_x = sample_at_times(heave, heave_jack_times)
        rr_heave_jack_y = sample_at_times(rr_jack, heave_jack_times) - sample_at_times(
            rr_jack, heave_sample_times
        )

        fr_roll_jack_x = sample_at_times(roll, roll_jack_times)
        fr_roll_jack_y = sample_at_times(fr_jack, roll_jack_times) - sample_at_times(
            fr_jack, roll_sample_times
        )
        rr_roll_jack_x = sample_at_times(roll, roll_jack_times)
        rr_roll_jack_y = sample_at_times(rr_jack, roll_jack_times) - sample_at_times(
            rr_jack, roll_sample_times
        )

        fr_fx = sig("frKnC", "fx")
        rr_fx = sig("rrKnC", "fx")
        fr_fy = sig("frKnC", "fy")
        rr_fy = sig("rrKnC", "fy")

        fr_roll_fy = sample_at_times(fr_fy, roll_jack_times)
        rr_roll_fy = sample_at_times(rr_fy, roll_jack_times)
        fr_heave_fx = sample_at_times(fr_fx, heave_jack_times)
        rr_heave_fx = sample_at_times(rr_fx, heave_jack_times)

        eps = 1e-6
        fr_coeff_heave = fr_heave_jack_y / (fr_heave_fx + eps)
        rr_coeff_heave = rr_heave_jack_y / (rr_heave_fx + eps)
        fr_coeff_roll = fr_roll_jack_y / (fr_roll_fy + eps)
        rr_coeff_roll = rr_roll_jack_y / (rr_roll_fy + eps)

        h_cg = float(self.config["vehicle"]["h_cg"])
        track_front = float(self.config["vehicle"]["track_front"])
        track_rear = float(self.config["vehicle"]["track_rear"])
        wheelbase = float(self.config["vehicle"]["wheelbase"])
        k_sf = float(self.config["suspension"]["front"]["spring_rate"])
        k_sr = float(self.config["suspension"]["rear"]["spring_rate"])
        k_arb_f = float(self.config["suspension"]["front"]["arb_rate"])
        k_arb_r = float(self.config["suspension"]["rear"]["arb_rate"])

        ref_long = h_cg / wheelbase
        ref_roll = h_cg / ((track_front + track_rear) / 2.0)

        fr_anti_heave = 100.0 * fr_coeff_heave / ref_long
        rr_anti_heave = 100.0 * rr_coeff_heave / ref_long
        fr_anti_roll = 100.0 * fr_coeff_roll / ref_roll
        rr_anti_roll = 100.0 * rr_coeff_roll / ref_roll

        mask_fr_h = np.abs(fr_heave_fx) > 1e-3
        mask_rr_h = np.abs(rr_heave_fx) > 1e-3
        fr_heave_x = fr_heave_jack_x[mask_fr_h]
        rr_heave_x = rr_heave_jack_x[mask_rr_h]
        fr_anti_heave = fr_anti_heave[mask_fr_h]
        rr_anti_heave = rr_anti_heave[mask_rr_h]

        mask_fr = np.abs(fr_roll_fy) > 1e-3
        mask_rr = np.abs(rr_roll_fy) > 1e-3
        fr_roll_x = fr_roll_jack_x[mask_fr]
        rr_roll_x = rr_roll_jack_x[mask_rr]
        fr_anti_roll = fr_anti_roll[mask_fr]
        rr_anti_roll = rr_anti_roll[mask_rr]

        def compute_motion_ratio_series(
            spring_signal: np.ndarray,
            wheel_signal: np.ndarray,
            sample_times: Sequence[float],
        ) -> tuple[np.ndarray, np.ndarray, float]:
            spring = sample_at_times(np.asarray(spring_signal, dtype=float), list(sample_times))
            wheel = sample_at_times(np.asarray(wheel_signal, dtype=float), list(sample_times))

            mask = np.isfinite(spring) & np.isfinite(wheel)
            spring = spring[mask]
            wheel = wheel[mask]

            if spring.size < 2 or wheel.size < 2 or np.nanstd(wheel) < 1e-12:
                return np.array([], dtype=float), np.array([], dtype=float), float("nan")

            idx = np.argsort(wheel)
            wheel = wheel[idx]
            spring = spring[idx]
            coeffs = np.polyfit(wheel, spring, 3)
            poly = np.poly1d(coeffs)
            dpoly = np.polyder(poly)
            ds_dw = dpoly(wheel)
            mr = 1.0 / np.abs(ds_dw)
            return wheel, mr, float(np.nanmean(mr))

        def compute_stabar_motion_ratio_series(
            stabar_signal: np.ndarray,
            roll_signal: np.ndarray,
            sample_times: Sequence[float],
        ) -> tuple[np.ndarray, np.ndarray, float]:
            stabar = sample_at_times(np.asarray(stabar_signal, dtype=float), list(sample_times))
            phi = sample_at_times(np.asarray(roll_signal, dtype=float), list(sample_times))

            mask = np.isfinite(stabar) & np.isfinite(phi)
            stabar = stabar[mask]
            phi = phi[mask]

            if stabar.size < 2 or phi.size < 2 or np.nanstd(stabar) < 1e-12 or np.nanstd(phi) < 1e-12:
                return np.array([], dtype=float), np.array([], dtype=float), float("nan")

            idx = np.argsort(phi)
            phi = phi[idx]
            stabar = stabar[idx]
            coeffs = np.polyfit(phi, stabar, 3)
            poly = np.poly1d(coeffs)
            dpoly = np.polyder(poly)
            ds_dphi = dpoly(phi)
            mr = 1.0 / np.abs(ds_dphi)
            return phi, mr, float(np.nanmean(mr))

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

        kw_f = k_sf / (mr_f**2)
        kw_r = k_sr / (mr_r**2)
        kphi_spr_f = 0.5 * kw_f * (track_front**2)
        kphi_spr_r = 0.5 * kw_r * (track_rear**2)
        kphi_arb_f = k_arb_f / (smr_f**2)
        kphi_arb_r = k_arb_r / (smr_r**2)
        kphi_el_f = kphi_spr_f + kphi_arb_f
        kphi_el_r = kphi_spr_r + kphi_arb_r

        n_roll = min(len(fr_anti_roll), len(rr_anti_roll))
        af = fr_anti_roll[:n_roll] / 100.0
        ar = rr_anti_roll[:n_roll] / 100.0
        kphi_eff_f = kphi_el_f * (1.0 + af)
        kphi_eff_r = kphi_el_r * (1.0 + ar)
        lltd_roll = kphi_eff_f / (kphi_eff_f + kphi_eff_r + 1e-9)

        gains = {
            "camber_gain_heave_rad_per_m": compute_gain(
                heave_vals, heave_series["fr_l_camber_vs_heave"]
            ),
            "toe_gain_heave_rad_per_m": compute_gain(
                heave_vals, heave_series["fr_l_toe_vs_heave"]
            ),
            "caster_gain_heave_rad_per_m": compute_gain(
                heave_vals, heave_series["fr_l_caster_vs_heave"]
            ),
            "kpi_gain_heave_rad_per_m": compute_gain(
                heave_vals, heave_series["fr_l_kpi_vs_heave"]
            ),
            "trail_gain_heave_m_per_m": compute_gain(
                heave_vals, heave_series["fr_l_trail_vs_heave"]
            ),
            "scrub_gain_heave_m_per_m": compute_gain(
                heave_vals, heave_series["fr_l_scrub_vs_heave"]
            ),
            "camber_gain_roll_rad_per_rad": compute_gain(
                roll_vals, roll_series["fr_l_camber_vs_roll"]
            ),
            "toe_gain_roll_rad_per_rad": compute_gain(
                roll_vals, roll_series["fr_l_toe_vs_roll"]
            ),
            "caster_gain_roll_rad_per_rad": compute_gain(
                roll_vals, roll_series["fr_l_caster_vs_roll"]
            ),
            "kpi_gain_roll_rad_per_rad": compute_gain(
                roll_vals, roll_series["fr_l_kpi_vs_roll"]
            ),
            "trail_gain_roll_m_per_rad": compute_gain(
                roll_vals, roll_series["fr_l_trail_vs_roll"]
            ),
            "scrub_gain_roll_m_per_rad": compute_gain(
                roll_vals, roll_series["fr_l_scrub_vs_roll"]
            ),
        }

        summary = {
            **{k: float(v) for k, v in gains.items()},
            "avg_anti_dive_pct": float(np.mean(fr_anti_heave)),
            "avg_anti_squat_pct": float(np.mean(rr_anti_heave)),
            "avg_anti_roll_front_pct": float(np.mean(fr_anti_roll)),
            "avg_anti_roll_rear_pct": float(np.mean(rr_anti_roll)),
            "avg_lltd_front_frac": float(np.mean(lltd_roll)),
            "avg_lltd_front_pct": float(100.0 * np.mean(lltd_roll)),
            "avg_longitudinal_jacking_coeff_front": float(np.mean(fr_coeff_heave)),
            "avg_longitudinal_jacking_coeff_rear": float(np.mean(rr_coeff_heave)),
            "avg_lateral_jacking_coeff_front": float(np.mean(fr_coeff_roll)),
            "avg_lateral_jacking_coeff_rear": float(np.mean(rr_coeff_roll)),
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
            "lltd_vs_roll_x": fr_roll_x[:n_roll],
            "lltd_vs_roll": lltd_roll,
        }

        return summary, series


def main(path: str | Path | None = None) -> dict[str, Any]:
    config_path = Path(path) if path is not None else DEFAULT_CONFIG_PATH
    config = load_config(config_path)

    result = FourPostEvalSim(config).run()

    if _as_mapping(config.get("report"), name="report").get("enabled", True):
        ReportEngine(config).build(result)

    return result


if __name__ == "__main__":
    path = sys.argv[1] if len(sys.argv) > 1 else None
    main(path)
