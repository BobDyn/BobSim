"""Run a reduced-order step steer and optionally compare it with BobLib CSV."""

from __future__ import annotations

import argparse
import time
import json
from pathlib import Path
from typing import Any, cast

import numpy as np
import pandas as pd

from engines.dynpy import (
    DOFModel,
    ModelInputs,
    TransientResult,
    Vehicle,
    compare_transient_signals,
)
from engines.kinpy import KinematicsMode


COMPARISON_SIGNALS = ("velX", "velY", "yawVel", "sideslip", "accX", "accY", "roll")


def run_step_steer(
    *,
    dof: DOFModel,
    speed_mps: float = 15.0,
    roadwheel_step_deg: float = 5.0,
    step_time_s: float = 1.0,
    rise_time_s: float = 0.02,
    stop_time_s: float = 5.0,
    sample_period_s: float = 0.01,
    vehicle_path: str | Path | None = None,
    kinematics_mode: KinematicsMode = "lookup",
    kinematics_sample_count: int = 49,
) -> TransientResult:
    """Run the same step-steer shape used by BobLib TransientEval."""

    vehicle = Vehicle.from_yaml(
        vehicle_path,
        kinematics_mode=kinematics_mode,
        kinematics_sample_count=kinematics_sample_count,
    )
    initial_trim = vehicle.steady_state(dof, speed_mps=speed_mps)
    if not initial_trim.success:
        raise RuntimeError(
            f"Could not initialize {dof}DOF straight-line trim: {initial_trim.message}"
        )
    target_steer = np.deg2rad(roadwheel_step_deg)
    trim_torques = initial_trim.inputs.wheel_torques_nm

    def controls(time_s: float, _state: np.ndarray[Any, Any]) -> ModelInputs:
        fraction = np.clip((time_s - step_time_s) / max(rise_time_s, 1e-9), 0.0, 1.0)
        return ModelInputs(
            steering_rad=float(fraction * target_steer),
            wheel_torques_nm=trim_torques,
        )

    time = np.arange(0.0, stop_time_s + 0.5 * sample_period_s, sample_period_s)
    method = "Radau" if dof == 14 else "RK45"
    return vehicle.simulate(
        dof,
        initial_state=initial_trim.state,
        controls=controls,
        time_s=time,
        method=method,
    )


def compare_with_boblib_csv(
    path: str | Path,
    candidate: TransientResult,
) -> dict[str, dict[str, float]]:
    """Compare common channels from a BobLib OpenModelica result CSV."""

    frame = pd.read_csv(path)
    if "time" not in frame:
        raise KeyError(f"BobLib result CSV has no 'time' column: {path}")
    reference = {
        signal: frame[signal].to_numpy(dtype=float)
        for signal in COMPARISON_SIGNALS
        if signal in frame
    }
    return compare_transient_signals(
        frame["time"].to_numpy(dtype=float),
        reference,
        candidate,
    )


def _parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dof", type=int, choices=(3, 6, 10, 14), default=6)
    parser.add_argument("--speed-mps", type=float, default=15.0)
    parser.add_argument("--roadwheel-step-deg", type=float, default=5.0)
    parser.add_argument("--step-time-s", type=float, default=1.0)
    parser.add_argument("--rise-time-s", type=float, default=0.02)
    parser.add_argument("--stop-time-s", type=float, default=5.0)
    parser.add_argument("--sample-period-s", type=float, default=0.01)
    parser.add_argument("--vehicle", type=Path)
    parser.add_argument(
        "--kinematics-mode",
        choices=("lookup", "nonlinear"),
        default="lookup",
    )
    parser.add_argument("--kinematics-sample-count", type=int, default=49)
    parser.add_argument("--boblib-csv", type=Path)
    parser.add_argument("--metrics-output", type=Path)
    return parser.parse_args()


def main() -> None:
    args = _parse_args()
    dof = cast(DOFModel, args.dof)
    print(f"Engine: DynPy | {dof} DOF transient | Runtime: Python")
    started = time.perf_counter()
    result = run_step_steer(
        dof=dof,
        speed_mps=args.speed_mps,
        roadwheel_step_deg=args.roadwheel_step_deg,
        step_time_s=args.step_time_s,
        rise_time_s=args.rise_time_s,
        stop_time_s=args.stop_time_s,
        sample_period_s=args.sample_period_s,
        vehicle_path=args.vehicle,
        kinematics_mode=cast(KinematicsMode, args.kinematics_mode),
        kinematics_sample_count=args.kinematics_sample_count,
    )
    print(f"Wall time: {time.perf_counter() - started:.2f} s")
    print(f"{dof}DOF transient: {len(result.time_s)} samples; success={result.success}")
    print(
        f"final yaw rate={result.signals['yawVel'][-1]:.6f} rad/s, "
        f"final ay={result.signals['accY'][-1]:.6f} m/s^2"
    )
    if args.boblib_csv is None:
        return

    metrics = compare_with_boblib_csv(args.boblib_csv, result)
    print(json.dumps(metrics, indent=2, sort_keys=True))
    if args.metrics_output is not None:
        args.metrics_output.parent.mkdir(parents=True, exist_ok=True)
        args.metrics_output.write_text(
            json.dumps(metrics, indent=2, sort_keys=True) + "\n",
            encoding="utf-8",
        )
        print(f"Comparison metrics written: {args.metrics_output}")


if __name__ == "__main__":
    main()
