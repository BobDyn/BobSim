from __future__ import annotations

from pathlib import Path
import ctypes

import matplotlib

matplotlib.use("Agg")

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from scipy.integrate import solve_ivp

from fmpy import read_model_description, extract
from fmpy.fmi2 import FMU2Model


# ============================================================
# USER SETTINGS
# ============================================================

BUILD_DIR = Path("_2_StandardSim/Build")
FMU_PATH = BUILD_DIR / "VehicleFMI.fmu"

DURATION = 1
OUTPUT_DT = 0.005
MAX_STEP = 0.005

SOLVER = "LSODA"
RTOL = 1e-4
ATOL = 1e-6

STEER_COMMAND = 0.0
DRIVE_TORQUE_COMMAND = 0.0

OUTPUT_SIGNALS = [
    "handwheelAngle",
    "leftSteerAngle",
    "rightSteerAngle",
    "accX",
    "accY",
    "roll",
    "sideslip",
    "handwheelTorque",
    "velX",
    "velY",
    "yawVel",
]

# 5 x 2 requested, so use the first 10 by default.
PLOT_SIGNALS = [
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


# ============================================================
# HELPERS
# ============================================================

def ptr(x: np.ndarray):
    x = np.ascontiguousarray(x, dtype=np.float64)
    return x.ctypes.data_as(ctypes.POINTER(ctypes.c_double))


def get_vrs(model_description):
    return {
        var.name: var.valueReference
        for var in model_description.modelVariables
    }


def require_vars(vrs, names, kind):
    missing = [name for name in names if name not in vrs]

    if missing:
        available = "\n".join(sorted(vrs.keys())[:200])
        raise KeyError(
            f"Missing {kind}: {missing}\n\n"
            f"Available FMU variables include:\n{available}"
        )


def sample_outputs(fmu, vrs, names):
    out = {}

    for name in names:
        out[name] = float(fmu.getReal([vrs[name]])[0])

    return out


# ============================================================
# MAIN
# ============================================================

def main():
    if not FMU_PATH.exists():
        raise FileNotFoundError(f"FMU not found: {FMU_PATH}")

    print(f"📦 Loading FMU: {FMU_PATH}")

    model_description = read_model_description(str(FMU_PATH))
    unzipdir = extract(str(FMU_PATH))

    if model_description.modelExchange is None:
        raise RuntimeError("This test expects an FMI 2.0 Model Exchange FMU.")

    model_identifier = model_description.modelExchange.modelIdentifier
    nx = int(model_description.numberOfContinuousStates)

    print(f"🔎 Continuous states: {nx}")

    vrs = get_vrs(model_description)

    require_vars(
        vrs,
        ["steerCommand", "driveTorqueCommand"],
        kind="inputs",
    )
    require_vars(
        vrs,
        OUTPUT_SIGNALS,
        kind="outputs",
    )

    fmu = FMU2Model(
        guid=model_description.guid,
        unzipDirectory=unzipdir,
        modelIdentifier=model_identifier,
    )

    fmu.instantiate()

    try:
        print("⚙️ Initializing FMU...")

        fmu.setupExperiment(startTime=0.0)
        fmu.enterInitializationMode()

        # These are the plant inputs for VehicleFMI.
        fmu.setReal(
            [vrs["steerCommand"], vrs["driveTorqueCommand"]],
            [STEER_COMMAND, DRIVE_TORQUE_COMMAND],
        )

        fmu.exitInitializationMode()

        x0 = np.zeros(nx)
        dx = np.zeros(nx)

        fmu.getContinuousStates(ptr(x0), nx)

        print("🚀 Running simulation...")

        call_count = 0
        last_print_t = -1.0

        def rhs(t, x):
            nonlocal call_count, last_print_t
            call_count += 1

            if t - last_print_t >= 0.05:
                print(f"sim t = {t:.3f} s", flush=True)
                last_print_t = t

            fmu.setTime(float(t))

            fmu.setReal(
                [vrs["steerCommand"], vrs["driveTorqueCommand"]],
                [STEER_COMMAND, DRIVE_TORQUE_COMMAND],
            )

            fmu.setContinuousStates(ptr(x), nx)
            fmu.getDerivatives(ptr(dx), nx)

            return dx.copy()

        t_eval = np.arange(0.0, DURATION + 0.5 * OUTPUT_DT, OUTPUT_DT)
        t_eval[-1] = min(t_eval[-1], DURATION)

        sol = solve_ivp(
            rhs,
            (0.0, DURATION),
            x0,
            method=SOLVER,
            rtol=RTOL,
            atol=ATOL,
            max_step=MAX_STEP,
            t_eval=t_eval,
        )

        if not sol.success:
            raise RuntimeError(f"Simulation failed: {sol.message}")

        print(f"✅ Simulation complete")
        print(f"   Final time: {sol.t[-1]:.3f} s")
        print(f"   RHS calls:  {call_count}")

        # ========================================================
        # SAMPLE OUTPUTS
        # ========================================================

        rows = []

        for j, t in enumerate(sol.t):
            x = sol.y[:, j]

            fmu.setTime(float(t))
            fmu.setReal(
                [vrs["steerCommand"], vrs["driveTorqueCommand"]],
                [STEER_COMMAND, DRIVE_TORQUE_COMMAND],
            )
            fmu.setContinuousStates(ptr(x), nx)

            row = {"time": float(t)}
            row.update(sample_outputs(fmu, vrs, OUTPUT_SIGNALS))
            rows.append(row)

        df = pd.DataFrame(rows)

        csv_path = BUILD_DIR / "test_fmu_outputs.csv"
        fig_path = BUILD_DIR / "test_fmu_outputs_5x2.png"

        df.to_csv(csv_path, index=False)

        print(f"📁 Saved CSV: {csv_path}")

        # ========================================================
        # PLOT 5 x 2
        # ========================================================

        fig, axes = plt.subplots(
            5,
            2,
            figsize=(18, 20),
            sharex=True,
        )

        axes = axes.ravel()

        labels = {
            "handwheelAngle": "Handwheel Angle [rad]",
            "leftSteerAngle": "Left Steer Angle [rad]",
            "rightSteerAngle": "Right Steer Angle [rad]",
            "accX": "Longitudinal Accel [m/s²]",
            "accY": "Lateral Accel [m/s²]",
            "roll": "Roll [rad]",
            "sideslip": "Sideslip [rad]",
            "handwheelTorque": "Handwheel Torque [N·m]",
            "velX": "Body X Velocity [m/s]",
            "velY": "Body Y Velocity [m/s]",
            "yawVel": "Yaw Rate [rad/s]",
        }

        for ax, signal in zip(axes, PLOT_SIGNALS):
            ax.plot(df["time"], df[signal])
            ax.set_title(signal)
            ax.set_ylabel(labels.get(signal, signal))
            ax.grid(True, linestyle="--", alpha=0.4)

        for ax in axes[-2:]:
            ax.set_xlabel("Time [s]")

        fig.suptitle(
            "VehicleFMI Output Signals — 10 Second Open-Loop Run",
            fontsize=18,
            y=0.995,
        )

        fig.tight_layout(rect=[0.0, 0.0, 1.0, 0.985])
        fig.savefig(fig_path, dpi=200)
        plt.close(fig)

        print(f"📈 Saved figure: {fig_path}")

    finally:
        try:
            fmu.terminate()
        except Exception:
            pass

        try:
            fmu.freeInstance()
        except Exception:
            pass


if __name__ == "__main__":
    main()