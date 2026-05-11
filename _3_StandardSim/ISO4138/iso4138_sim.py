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


DEFAULT_CONFIG_PATH = Path("_3_StandardSim/ISO4138/iso4138_config.yml")


ISO4138_SIGNALS = [
    # Controller/debug signals
    "frSteerCmd",
    "steerRatioEstimate",
    "steerFeedforward",
    "targetAyCmd",
    "targetRoadwheelCmd",
    "ayErrorRaw",
    "ayError",
    "radError",

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

ISO4138_VARIABLE_FILTER = "|".join(ISO4138_SIGNALS)


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


class ISO4138Sim:
    def __init__(self, config: dict[str, Any]):
        self.config = config

        sim_cfg = config.setdefault("simulation", {})
        sim_cfg.setdefault("variable_filter", ISO4138_VARIABLE_FILTER)
        backend = sim_cfg.get("backend", "modelica")

        if backend != "modelica":
            raise ValueError(
                "ISO4138Sim currently expects simulation.backend='modelica'. "
                f"Got {backend!r}."
            )

        self.runner = ModelicaRunner.from_config(config)

        self.start_time = float(sim_cfg.get("start_time", 0.0))
        self.stop_time = float(sim_cfg.get("stop_time", 10.0))
        self.steady_window_s = float(sim_cfg.get("steady_window_s", 0.25))

        if self.stop_time <= self.start_time:
            raise ValueError(
                "simulation.stop_time must be greater than simulation.start_time. "
                f"Got start_time={self.start_time}, stop_time={self.stop_time}."
            )

    # ============================================================
    # CASE GENERATION
    # ============================================================

    def build_cases(self) -> list[dict[str, Any]]:
        sweep = self.config["sweep"]
        sim_cfg = self.config.get("simulation", {})

        test_vel = float(sweep["testVel"])
        n_cases = int(sweep["n_cases"])

        if n_cases < 1:
            raise ValueError("sweep.n_cases must be >= 1")

        r_min = float(sweep["r_min"])
        r_max = float(sweep["r_max"])

        if r_min <= 0.0 or r_max <= 0.0:
            raise ValueError("sweep.r_min and sweep.r_max must be positive")

        radius_bias_power = float(sweep.get("radius_bias_power", 2.5))

        t = np.linspace(0.0, 1.0, n_cases)

        log_min = np.log10(r_min)
        log_max = np.log10(r_max)

        radii = 10.0 ** (log_min + (log_max - log_min) * t**radius_bias_power)

        # Run both directions.
        #
        # VehicleSim receives signed targetRad directly.
        # Positive radius = one turn direction.
        # Negative radius = opposite turn direction.
        radii = np.concatenate([radii, -radii])

        # VehicleSim owns its own defaults.
        #
        # simulation.init_parameters is only for explicit overrides.
        #
        init_parameters = _as_override_dict(
            sim_cfg.get("init_parameters", {}),
            name="simulation.init_parameters",
        )

        cases: list[dict[str, Any]] = []

        for radius_raw in radii:
            radius = float(radius_raw)
            curvature = 1.0 / radius

            case: dict[str, Any] = {
                # =========================
                # Python-only metadata
                # =========================
                "_mode": "constant_radius",
                "_testVel": test_vel,
                "_testRad": radius,
                "_testCurv": curvature,

                # =========================
                # Modelica executable overrides
                # =========================
                #
                # These are the case-specific ISO4138 inputs.
                # Controller behavior is owned by VehicleSim defaults unless
                # explicitly overridden through simulation.init_parameters.
                "targetVel": test_vel,
                "targetRad": radius,

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
            signals=ISO4138_SIGNALS,
            mode="raw",
            cases=cases,
            execution=self.config.get("execution", {}),
        )

        return self.summarize(results)

    def _collapse_to_steady_state(self, result: dict[str, Any]) -> dict[str, Any]:
        time = np.asarray(result.get("time", []), dtype=float)

        if time.size == 0:
            raise ValueError("ISO4138 case did not return any time samples.")

        steady_end = float(time[-1])
        steady_start = max(float(time[0]), steady_end - self.steady_window_s)
        steady_mask = time >= steady_start

        if not np.any(steady_mask):
            steady_mask = np.zeros_like(time, dtype=bool)
            steady_mask[-1] = True

        collapsed: dict[str, Any] = {}

        for key, value in result.items():
            if key.startswith("_"):
                collapsed[key] = value
                continue

            if key == "time":
                collapsed[key] = steady_end
                continue

            if isinstance(value, np.ndarray):
                if value.shape == time.shape:
                    collapsed[key] = float(np.nanmean(value[steady_mask]))
                elif value.ndim == 0:
                    collapsed[key] = float(value)
                else:
                    collapsed[key] = float(np.asarray(value).reshape(-1)[-1])
                continue

            if isinstance(value, (list, tuple)):
                arr = np.asarray(value, dtype=float)
                if arr.shape == time.shape:
                    collapsed[key] = float(np.nanmean(arr[steady_mask]))
                elif arr.size:
                    collapsed[key] = float(arr.reshape(-1)[-1])
                else:
                    collapsed[key] = value
                continue

            collapsed[key] = value

        return collapsed

    # ============================================================
    # METRICS CSV
    # ============================================================

    def write_metrics_csv(self, metrics: list[dict[str, Any]]) -> Path:
        """
        Write one ISO4138 metrics CSV beside the PDF report.

        This intentionally exports only the report-level metric rows, not
        sweep data and not raw case data.
        """
        report_cfg = self.config.get("report", {})

        report_path = Path(
            report_cfg.get(
                "output_path",
                "_3_StandardSim/results/iso4138_report.pdf",
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
            raise ValueError("No ISO4138 results to summarize.")

        raw_results = results
        results = [self._collapse_to_steady_state(result) for result in raw_results]

        def _last_sample(value: Any) -> float:
            arr = np.asarray(value, dtype=float)
            if arr.ndim == 0:
                return float(arr)
            return float(arr.reshape(-1)[-1])

        left = np.array([r["leftSteerAngle"] for r in results], dtype=float)
        right = np.array([r["rightSteerAngle"] for r in results], dtype=float)
        roadwheel = 0.5 * (left + right)
        handwheel = np.array([r["handwheelAngle"] for r in results], dtype=float)

        ay = np.array([r["accY"] for r in results], dtype=float)
        roll = np.array([r["roll"] for r in results], dtype=float)
        beta = np.array([r["sideslip"] for r in results], dtype=float)
        torque = np.array([r["handwheelTorque"] for r in results], dtype=float)

        vel_x = np.array([r["velX"] for r in results], dtype=float)
        vel_y = np.array([r["velY"] for r in results], dtype=float)
        yaw = np.array([r["yawVel"] for r in results], dtype=float)

        speed = np.sqrt(vel_x**2 + vel_y**2)
        curvature = yaw / np.maximum(speed, 0.1)

        kappa_cmd = np.array([r["_testCurv"] for r in results], dtype=float)
        radius_cmd = np.array([r["_testRad"] for r in results], dtype=float)

        # Controller/debug arrays.
        fr_steer_cmd = np.array([r["frSteerCmd"] for r in results], dtype=float)
        steer_ratio_estimate = np.array([r["steerRatioEstimate"] for r in results], dtype=float)
        steer_feedforward = np.array([r["steerFeedforward"] for r in results], dtype=float)
        target_ay_cmd = np.array([r["targetAyCmd"] for r in results], dtype=float)
        target_roadwheel_cmd = np.array([r["targetRoadwheelCmd"] for r in results], dtype=float)
        ay_error_raw = np.array([_last_sample(r["ayErrorRaw"]) for r in raw_results], dtype=float)
        ay_error = np.array([_last_sample(r["ayError"]) for r in raw_results], dtype=float)
        rad_error = np.array([r["radError"] for r in results], dtype=float)
        ay_analytical = np.array(
            [r["_testVel"] ** 2 / r["_testRad"] for r in results],
            dtype=float,
        )

        # Use commanded curvature sign to establish signed lateral acceleration.
        #
        # This makes the report ordering robust even if the controller is not
        # perfectly converged for a bad case.
        ay_signed = np.sign(kappa_cmd) * np.abs(ay)

        idx = np.argsort(ay_signed)

        ay_signed = ay_signed[idx]
        roadwheel = roadwheel[idx]
        handwheel = handwheel[idx]
        curvature = curvature[idx]
        roll = roll[idx]
        beta = beta[idx]
        torque = torque[idx]
        kappa_cmd = kappa_cmd[idx]
        radius_cmd = radius_cmd[idx]
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
        ay_analytical = ay_analytical[idx]

        eps = 1.0e-9

        curvature_error_pct = 100.0 * (curvature - kappa_cmd) / np.maximum(
            np.abs(kappa_cmd),
            eps,
        )
        ay_error_pct = 100.0 * np.abs(ay_error_raw) / np.maximum(
            np.abs(ay_analytical),
            eps,
        )

        radius_actual = np.full_like(curvature, np.nan)
        valid_kappa = np.abs(curvature) > eps
        radius_actual[valid_kappa] = 1.0 / curvature[valid_kappa]

        radius_error_pct = 100.0 * (radius_actual - radius_cmd) / np.maximum(
            np.abs(radius_cmd),
            eps,
        )

        fit_cfg = self.config.get("fit", {})
        ay_linear_max = float(fit_cfg.get("ay_linear_max", 6.0))

        fit_mask = np.abs(ay_signed) <= ay_linear_max

        if np.count_nonzero(fit_mask) >= 2:
            steer_coeffs = np.polyfit(ay_signed[fit_mask], roadwheel[fit_mask], 1)
        else:
            steer_coeffs = np.polyfit(ay_signed, roadwheel, 1)

        steer_fit = np.polyval(steer_coeffs, ay_signed)

        if np.count_nonzero(fit_mask) >= 2:
            handwheel_coeffs = np.polyfit(ay_signed[fit_mask], handwheel[fit_mask], 1)
        else:
            handwheel_coeffs = np.polyfit(ay_signed, handwheel, 1)

        handwheel_fit = np.polyval(handwheel_coeffs, ay_signed)

        def gradient_safe(x: np.ndarray, y: np.ndarray) -> np.ndarray:
            if len(x) < 2:
                return np.zeros_like(y)

            if np.any(np.isclose(np.diff(x), 0.0)):
                return np.gradient(y)

            return np.gradient(y, x)

        steer_grad = gradient_safe(ay_signed, roadwheel)
        handwheel_grad = gradient_safe(ay_signed, handwheel)
        curv_grad = gradient_safe(ay_signed, curvature)
        beta_grad = gradient_safe(ay_signed, beta)
        roll_grad = gradient_safe(ay_signed, roll)

        understeer_gradient = steer_coeffs[0]
        handwheel_understeer_gradient = handwheel_coeffs[0]

        if np.count_nonzero(fit_mask) >= 2:
            roll_gradient = np.polyfit(ay_signed[fit_mask], roll[fit_mask], 1)[0]
        else:
            roll_gradient = np.polyfit(ay_signed, roll, 1)[0]

        ay_range: tuple[float, float] = (
            float(ay_signed.min()),
            float(ay_signed.max()),
        )

        summary: dict[str, Any] = {
            "Ay_range": ay_range,
            "understeer_gradient_rad_per_mps2": float(understeer_gradient),
            "understeer_gradient_deg_per_g": float(
                understeer_gradient * 57.2958 * 9.81
            ),
            "handwheel_understeer_gradient_rad_per_mps2": float(
                handwheel_understeer_gradient
            ),
            "handwheel_understeer_gradient_deg_per_g": float(
                handwheel_understeer_gradient * 57.2958 * 9.81
            ),
            "roll_gradient_deg_per_g": float(roll_gradient * 57.2958 * 9.81),
            "handwheel_torque_min_Nm": float(np.nanmin(torque)),
            "handwheel_torque_max_Nm": float(np.nanmax(torque)),
            "max_curvature_error_pct": float(
                np.nanmax(np.abs(curvature_error_pct))
            ),
            "mean_curvature_error_pct": float(
                np.nanmean(np.abs(curvature_error_pct))
            ),
            "max_radius_error_pct": float(np.nanmax(np.abs(radius_error_pct))),
            "mean_radius_error_pct": float(np.nanmean(np.abs(radius_error_pct))),
            "max_abs_ay_error_raw": float(np.nanmax(np.abs(ay_error_raw))),
            "mean_abs_ay_error_raw": float(np.nanmean(np.abs(ay_error_raw))),
            "max_abs_ay_error_pct": float(np.nanmax(ay_error_pct)),
            "mean_abs_ay_error_pct": float(np.nanmean(ay_error_pct)),
            "max_abs_rad_error": float(np.nanmax(np.abs(rad_error))),
            "mean_abs_rad_error": float(np.nanmean(np.abs(rad_error))),
        }

        ay_min, ay_max = ay_range

        metrics: list[dict[str, Any]] = [
            {
                "standard": "ISO4138",
                "metric": "ay_min",
                "value": ay_min,
                "units": "m/s^2",
                "description": "Minimum signed lateral acceleration",
            },
            {
                "standard": "ISO4138",
                "metric": "ay_max",
                "value": ay_max,
                "units": "m/s^2",
                "description": "Maximum signed lateral acceleration",
            },
            {
                "standard": "ISO4138",
                "metric": "understeer_gradient_rad_per_mps2",
                "value": summary["understeer_gradient_rad_per_mps2"],
                "units": "rad/(m/s^2)",
                "description": "Linear-region roadwheel understeer gradient",
            },
            {
                "standard": "ISO4138",
                "metric": "understeer_gradient_deg_per_g",
                "value": summary["understeer_gradient_deg_per_g"],
                "units": "deg/g",
                "description": "Linear-region roadwheel understeer gradient",
            },
            {
                "standard": "ISO4138",
                "metric": "handwheel_understeer_gradient_rad_per_mps2",
                "value": summary["handwheel_understeer_gradient_rad_per_mps2"],
                "units": "rad/(m/s^2)",
                "description": "Linear-region handwheel understeer gradient",
            },
            {
                "standard": "ISO4138",
                "metric": "handwheel_understeer_gradient_deg_per_g",
                "value": summary["handwheel_understeer_gradient_deg_per_g"],
                "units": "deg/g",
                "description": "Linear-region handwheel understeer gradient",
            },
            {
                "standard": "ISO4138",
                "metric": "roll_gradient_deg_per_g",
                "value": summary["roll_gradient_deg_per_g"],
                "units": "deg/g",
                "description": "Linear-region roll gradient",
            },
            {
                "standard": "ISO4138",
                "metric": "max_curvature_error_pct",
                "value": summary["max_curvature_error_pct"],
                "units": "%",
                "description": "Maximum absolute curvature tracking error",
            },
            {
                "standard": "ISO4138",
                "metric": "mean_curvature_error_pct",
                "value": summary["mean_curvature_error_pct"],
                "units": "%",
                "description": "Mean absolute curvature tracking error",
            },
            {
                "standard": "ISO4138",
                "metric": "max_radius_error_pct",
                "value": summary["max_radius_error_pct"],
                "units": "%",
                "description": "Maximum absolute radius tracking error",
            },
            {
                "standard": "ISO4138",
                "metric": "mean_radius_error_pct",
                "value": summary["mean_radius_error_pct"],
                "units": "%",
                "description": "Mean absolute radius tracking error",
            },
            {
                "standard": "ISO4138",
                "metric": "max_abs_ay_error_raw",
                "value": summary["max_abs_ay_error_raw"],
                "units": "m/s^2",
                "description": "Maximum absolute final lateral acceleration tracking error",
            },
            {
                "standard": "ISO4138",
                "metric": "mean_abs_ay_error_raw",
                "value": summary["mean_abs_ay_error_raw"],
                "units": "m/s^2",
                "description": "Mean absolute final lateral acceleration tracking error",
            },
            {
                "standard": "ISO4138",
                "metric": "max_abs_ay_error_pct",
                "value": summary["max_abs_ay_error_pct"],
                "units": "%",
                "description": "Maximum absolute final lateral acceleration tracking error vs analytical Ay",
            },
            {
                "standard": "ISO4138",
                "metric": "mean_abs_ay_error_pct",
                "value": summary["mean_abs_ay_error_pct"],
                "units": "%",
                "description": "Mean absolute final lateral acceleration tracking error vs analytical Ay",
            },
            {
                "standard": "ISO4138",
                "metric": "handwheel_torque_min",
                "value": summary["handwheel_torque_min_Nm"],
                "units": "N*m",
                "description": "Minimum handwheel torque over ISO4138 sweep",
            },
            {
                "standard": "ISO4138",
                "metric": "handwheel_torque_max",
                "value": summary["handwheel_torque_max_Nm"],
                "units": "N*m",
                "description": "Maximum handwheel torque over ISO4138 sweep",
            },
        ]

        metrics_csv_path = self.write_metrics_csv(metrics)

        print(f"📊 ISO4138 metrics CSV written: {metrics_csv_path}")

        series = {
            "ay_signed": ay_signed,
            "roadwheel": roadwheel,
            "handwheel": handwheel,
            "curvature": curvature,
            "curvature_cmd": kappa_cmd,
            "curvature_error_pct": curvature_error_pct,
            "ay_analytical": ay_analytical,
            "ay_error_pct": ay_error_pct,
            "roll": roll,
            "sideslip": beta,
            "torque": torque,
            "radius_cmd": radius_cmd,
            "radius_actual": radius_actual,
            "radius_error_pct": radius_error_pct,
            "speed": speed,
            "yaw": yaw,
            "steer_fit": steer_fit,
            "handwheel_fit": handwheel_fit,
            "steer_gradient": steer_grad,
            "handwheel_gradient": handwheel_grad,
            "curvature_gradient": curv_grad,
            "sideslip_gradient": beta_grad,
            "roll_gradient": roll_grad,

            # Controller/debug series
            "fr_steer_cmd": fr_steer_cmd,
            "steer_ratio_estimate": steer_ratio_estimate,
            "steer_feedforward": steer_feedforward,
            "target_ay_cmd": target_ay_cmd,
            "target_roadwheel_cmd": target_roadwheel_cmd,
            "ay_error_raw": ay_error_raw,
            "ay_error": ay_error,
            "rad_error": rad_error,
        }

        return {
            "summary": summary,
            "metrics": metrics,
            "metrics_csv_path": metrics_csv_path,
            "series": series,
            "cases": results,
        }


def main(path: str | Path | None = None) -> dict[str, Any]:
    config_path = Path(path) if path is not None else DEFAULT_CONFIG_PATH
    config = load_config(config_path)

    result = ISO4138Sim(config).run()

    if config.get("report", {}).get("enabled", True):
        ReportEngine(config).build(result)

    return result


if __name__ == "__main__":
    path = sys.argv[1] if len(sys.argv) > 1 else None
    main(path)
