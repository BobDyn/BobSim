from __future__ import annotations

import csv
import sys
from pathlib import Path
from typing import Any, cast

import matplotlib as mpl
import numpy as np
import yaml

from _2_StandardSim._modelica_runner import ModelicaRunner
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


DEFAULT_CONFIG_PATH = Path("_2_StandardSim/ISO4138/iso4138_config.yml")


ISO4138_SIGNALS = [
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
]


def load_config(path: str | Path) -> dict[str, Any]:
    path = Path(path)

    with path.open("r") as f:
        config = yaml.safe_load(f)

    if config is None:
        raise ValueError(f"Config file is empty: {path}")

    if not isinstance(config, dict):
        raise TypeError(f"Expected YAML config to contain a mapping at top level: {path}")

    return cast(dict[str, Any], config)


class ISO4138Sim:
    def __init__(self, config: dict[str, Any]):
        self.config = config

        sim_cfg = config.get("simulation", {})
        backend = sim_cfg.get("backend", "modelica")

        if backend != "modelica":
            raise ValueError(
                "ISO4138Sim currently expects simulation.backend='modelica'. "
                f"Got {backend!r}."
            )

        self.runner = ModelicaRunner.from_config(config)
        self.stop_time = float(sim_cfg.get("stop_time", 10.0))

    # ============================================================
    # CASE GENERATION
    # ============================================================

    def build_cases(self) -> list[dict[str, Any]]:
        sweep = self.config["sweep"]
        sim_cfg = self.config.get("simulation", {})
        controller_cfg = self.config.get("controller", {})

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

        # Run both left and right directions.
        # The sign matters because VehicleModel uses 1 / targetRad.
        radii = np.concatenate([radii, -radii])

        init_parameters = dict(sim_cfg.get("init_parameters", {}))

        cases: list[dict[str, Any]] = []

        for radius in radii:
            radius = float(radius)
            curvature = 1.0 / radius

            case = {
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
                "initialVel": float(init_parameters.get("initialVel", test_vel)),
                "useMode": int(init_parameters.get("useMode", 0)),

                "targetVel": test_vel,
                "targetRad": radius,

                "curvGain": float(controller_cfg.get("curv_kp", 3.0)),
                "curvTi": float(controller_cfg.get("curv_ti", 0.02)),

                "velGain": float(controller_cfg.get("vel_kp", 200.0)),
                "velTi": float(controller_cfg.get("vel_ti", 1.0)),

                # Handled by ModelicaRunner._build_command(), not written
                # into the override file.
                "stopTime": self.stop_time,
            }

            cases.append(case)

        return cases

    # ============================================================
    # RUN
    # ============================================================

    def run(self) -> dict[str, Any]:
        cases = self.build_cases()

        results = self.runner.run(
            signals=ISO4138_SIGNALS,
            mode="steady",
            cases=cases,
            execution=self.config.get("execution", {}),
        )

        return self.summarize(results)

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
                "_2_StandardSim/results/iso4138_report.pdf",
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

        left = np.array([r["leftSteerAngle"] for r in results], dtype=float)
        right = np.array([r["rightSteerAngle"] for r in results], dtype=float)
        roadwheel = 0.5 * (left + right)

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

        # Use commanded curvature sign to establish signed lateral acceleration.
        # This keeps the sweep ordered even if the controller is imperfect near zero.
        ay_signed = np.sign(kappa_cmd) * np.abs(ay)

        idx = np.argsort(ay_signed)

        ay_signed = ay_signed[idx]
        roadwheel = roadwheel[idx]
        curvature = curvature[idx]
        roll = roll[idx]
        beta = beta[idx]
        torque = torque[idx]
        kappa_cmd = kappa_cmd[idx]
        radius_cmd = radius_cmd[idx]
        speed = speed[idx]
        yaw = yaw[idx]

        eps = 1.0e-9

        curvature_error_pct = 100.0 * (curvature - kappa_cmd) / np.maximum(
            np.abs(kappa_cmd),
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

        def gradient_safe(x: np.ndarray, y: np.ndarray) -> np.ndarray:
            if len(x) < 2:
                return np.zeros_like(y)

            # Avoid divide-by-zero warnings if two cases converge to identical ay.
            if np.any(np.isclose(np.diff(x), 0.0)):
                return np.gradient(y)

            return np.gradient(y, x)

        steer_grad = gradient_safe(ay_signed, roadwheel)
        curv_grad = gradient_safe(ay_signed, curvature)
        beta_grad = gradient_safe(ay_signed, beta)
        roll_grad = gradient_safe(ay_signed, roll)

        understeer_gradient = steer_coeffs[0]

        if np.count_nonzero(fit_mask) >= 2:
            roll_gradient = np.polyfit(ay_signed[fit_mask], roll[fit_mask], 1)[0]
        else:
            roll_gradient = np.polyfit(ay_signed, roll, 1)[0]

        # --------------------------------------------------------
        # Report summary metrics.
        #
        # This is the source of truth used by both the PDF report and the
        # CSV metric export below.
        # --------------------------------------------------------
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
        }

        ay_min, ay_max = ay_range

        # --------------------------------------------------------
        # CSV metric rows.
        #
        # Add/remove/reorder exported metrics here.
        # --------------------------------------------------------
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
                "description": "Linear-region understeer gradient",
            },
            {
                "standard": "ISO4138",
                "metric": "understeer_gradient_deg_per_g",
                "value": summary["understeer_gradient_deg_per_g"],
                "units": "deg/g",
                "description": "Linear-region understeer gradient",
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
            "curvature": curvature,
            "curvature_cmd": kappa_cmd,
            "curvature_error_pct": curvature_error_pct,
            "roll": roll,
            "sideslip": beta,
            "torque": torque,
            "radius_cmd": radius_cmd,
            "radius_actual": radius_actual,
            "radius_error_pct": radius_error_pct,
            "speed": speed,
            "yaw": yaw,
            "steer_fit": steer_fit,
            "steer_gradient": steer_grad,
            "curvature_gradient": curv_grad,
            "sideslip_gradient": beta_grad,
            "roll_gradient": roll_grad,
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