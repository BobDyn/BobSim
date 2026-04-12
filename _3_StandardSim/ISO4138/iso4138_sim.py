from pathlib import Path
import numpy as np

from _2_GeneralSim.general_sim import _2_GeneralSim
from _3_StandardSim.ISO4138.iso4138_schema import ISO4138_SCHEMA


class ISO4138Sim:
    def __init__(self, config):
        self.config = config

        build_dir = Path(__file__).parent / "build"
        exec_name = "BobLib.Standards.ISO4138"

        self.sim = _2_GeneralSim(
            build_dir=build_dir,
            exec_name=exec_name,
            simulation=config.get("simulation", {}),
        )

    def build_cases(self):
        sweep = self.config["sweep"]

        t = np.linspace(0.0, 1.0, sweep["n_cases"])
        p = sweep.get("radius_bias_power", 2.5)

        log_min = np.log10(sweep["r_min"])
        log_max = np.log10(sweep["r_max"])

        radii = 10 ** (log_min + (log_max - log_min) * t**p)
        radii = np.concatenate([radii, -radii])

        return [
            {"testVel": sweep["testVel"], "testRad": float(r)}
            for r in radii
        ]

    def run(self):
        cases = self.build_cases()

        exec_cfg = self.config.get("execution", {})

        cleanup = exec_cfg.get("cleanup", False)

        if exec_cfg.get("parallel", True):
            results = self.sim.run_cases_parallel(
                schema=ISO4138_SCHEMA,
                cases=cases,
                max_workers=exec_cfg.get("max_workers"),
                cleanup=cleanup,              # 🔥 add this
            )
            results = [r for r in results if r is not None]
        else:
            results = self.sim.run_cases(
                schema=ISO4138_SCHEMA,
                cases=cases,
                cleanup=cleanup,
            )

        return self.summarize(results)

    def summarize(self, results):
        # =========================
        # EXTRACT RAW
        # =========================
        left = np.array([r["iso.leftSteerAngle"] for r in results])
        right = np.array([r["iso.rightSteerAngle"] for r in results])
        roadwheel = 0.5 * (left + right)

        ay = np.array([r["iso.accY"] for r in results])
        curvature = np.array([r["iso.curvature"] for r in results])
        roll = np.array([r["iso.roll"] for r in results])
        beta = np.array([r["iso.sideslip"] for r in results])
        torque = np.array([r["iso.handwheelTorque"] for r in results])

        # commanded radius
        R_cmd = np.array([r["testRad"] for r in results])

        # =========================
        # SIGNED AY + SORT
        # =========================
        ay_signed = np.sign(curvature) * np.abs(ay)

        idx = np.argsort(ay_signed)

        ay_signed = ay_signed[idx]
        roadwheel = roadwheel[idx]
        curvature = curvature[idx]
        roll = roll[idx]
        beta = beta[idx]
        torque = torque[idx]
        R_cmd = R_cmd[idx]

        # =========================
        # ACTUAL RADIUS
        # =========================
        eps = 1e-6
        curvature_safe = np.clip(curvature, -np.inf, -eps)
        curvature_safe[curvature > eps] = np.clip(curvature[curvature > eps], eps, np.inf)

        R_actual = 1.0 / curvature_safe

        # =========================
        # TRACKING ERROR (ROBUST)
        # =========================
        radius_error = (R_actual - R_cmd) / np.abs(R_cmd)
        radius_error_pct = 100.0 * radius_error

        # 🔥 remove low-curvature region (blows up)
        mask = np.abs(curvature) > 1e-3
        radius_error_pct[~mask] = np.nan

        # =========================
        # STEERING FIT (UNDERSTEER ONLY)
        # =========================
        coeffs = np.polyfit(ay_signed, roadwheel, 1)
        steer_fit = np.polyval(coeffs, ay_signed)

        # =========================
        # GRADIENTS
        # =========================
        def grad(x, y):
            return np.gradient(y, x)

        steer_grad = grad(ay_signed, roadwheel)
        curv_grad = grad(ay_signed, curvature)
        beta_grad = grad(ay_signed, beta)
        roll_grad = grad(ay_signed, roll)

        # =========================
        # METRICS
        # =========================
        K_us = coeffs[0]
        K_roll = np.polyfit(ay_signed, roll, 1)[0]

        return {
            "summary": {
                "Ay_range": (float(ay_signed.min()), float(ay_signed.max())),
                "understeer_gradient_rad_per_mps2": float(K_us),
                "understeer_gradient_deg_per_g": float(K_us * 57.2958 * 9.81),
                "roll_gradient_deg_per_g": float(K_roll * 57.2958 * 9.81),

                # 🔥 CLEAN metric
                "max_radius_error_pct": float(np.nanmax(np.abs(radius_error_pct))),
                "mean_radius_error_pct": float(np.nanmean(np.abs(radius_error_pct))),
            },

            "series": {
                "ay_signed": ay_signed,
                "roadwheel": roadwheel,
                "curvature": curvature,
                "roll": roll,
                "sideslip": beta,
                "torque": torque,

                # 🔥 tracking
                "radius_cmd": R_cmd,
                "radius_actual": R_actual,
                "radius_error_pct": radius_error_pct,

                # fits
                "steer_fit": steer_fit,

                # gradients
                "steer_gradient": steer_grad,
                "curvature_gradient": curv_grad,
                "sideslip_gradient": beta_grad,
                "roll_gradient": roll_grad,
            }
        }