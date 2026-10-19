"""Run a reduced-order step steer and optionally compare it with BobLib CSV."""

from __future__ import annotations

from dataclasses import replace
import argparse
import time
import json
from pathlib import Path
from typing import Any, Callable, cast

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
from engines.dynpy.transient import DynamicControls


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
    steering_input: Callable[[float], float] | None = None,
) -> TransientResult:
    """## Step Steer

    Apply a steering step while PI control holds the requested speed.
    Drive demand respects the vehicle force, power and speed limits.

    Parameters
    ----------
    dof : DOFModel
        Vehicle model fidelity.
    speed_mps : float
        Target speed in meters per second.
    roadwheel_step_deg : float
        Final roadwheel steer in degrees.
    step_time_s : float
        Time at which steering starts changing.
    rise_time_s : float
        Duration of the steering transition.
    stop_time_s : float
        Simulation end time.
    sample_period_s : float
        Output sample interval.
    vehicle_path : str or Path, optional
        Vehicle YAML path.
    kinematics_mode : KinematicsMode
        KinPy lookup or nonlinear evaluation.
    kinematics_sample_count : int
        Number of samples for the kinematics lookup.

    steering_input : callable, optional
        Steering command in radians as a function of time.

    Returns
    -------
    TransientResult
        Vehicle response with actual and target speed signals.
    """

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
    trim_torques = np.asarray(initial_trim.inputs.wheel_torques_nm)
    parameters = vehicle.parameters
    radii = np.asarray(parameters.wheel_radius_m)
    trim_force = float(np.sum(trim_torques / radii))

    def speed(state: np.ndarray[Any, Any]) -> float:
        return float(np.linalg.norm(state[dof:dof + (2 if dof == 3 else 3)]))

    # Gains act on acceleration: Kp = 5 / s and Ki = 10 / s².
    def demand(state: np.ndarray[Any, Any], integral: np.ndarray[Any, Any]) -> tuple[float, float, float]:
        current_speed = speed(state)
        error = speed_mps - current_speed
        requested = trim_force + parameters.mass_kg * (5.0 * error + 10.0 * integral[0])
        limit = min(parameters.peak_drive_force_n, parameters.peak_drive_power_w / max(current_speed, 1.0))
        if current_speed > parameters.maximum_drive_speed_mps:
            limit = 0.0
        return error, requested, min(requested, limit)

    def integral_derivative(_time: float, state: np.ndarray[Any, Any], integral: np.ndarray[Any, Any]):
        error, requested, applied = demand(state, integral)
        return np.array([0.0 if requested > applied and error > 0.0 else error])

    def controls(time_s: float, state: np.ndarray[Any, Any], integral: np.ndarray[Any, Any]) -> ModelInputs:
        fraction = np.clip((time_s - step_time_s) / max(rise_time_s, 1e-9), 0.0, 1.0)
        _, _, force = demand(state, integral)
        front = parameters.drive_distribution_front if force >= 0.0 else parameters.brake_distribution_front
        distribution = np.array([front, front, 1.0 - front, 1.0 - front]) / 2.0
        torques = force * distribution * radii
        return ModelInputs(
            steering_rad=float(steering_input(time_s) if steering_input else fraction * target_steer),
            wheel_torques_nm=tuple(torques),
        )

    time = np.arange(0.0, stop_time_s + 0.5 * sample_period_s, sample_period_s)
    # Wheel rotation adds fast slip dynamics in both 10 and 14 DOF models.
    method = "Radau" if dof >= 10 else "RK45"
    result = vehicle.simulate(
        dof,
        initial_state=initial_trim.state,
        controls=DynamicControls(np.zeros(1), controls, integral_derivative),
        time_s=time,
        method=method,
    )
    actual_speed = np.linalg.norm(result.state[:, dof:dof + (2 if dof == 3 else 3)], axis=1)
    return replace(result, signals={**result.signals, "speed": actual_speed,
                                    "targetSpeed": np.full_like(actual_speed, speed_mps)})


def run_ramp_steer(
    *,
    dof: DOFModel,
    speed_mps: float = 15.0,
    roadwheel_rate_deg_s: float = 1.0,
    start_time_s: float = 1.0,
    ramp_end_time_s: float | None = None,
    stop_time_s: float = 5.0,
    sample_period_s: float = 0.01,
    vehicle_path: str | Path | None = None,
    kinematics_mode: KinematicsMode = "lookup",
) -> TransientResult:
    """## Ramp Steer

    Apply a constant roadwheel steering rate after straight-line trim.
    PI control holds the requested speed throughout the ramp and hold.

    Parameters
    ----------
    dof : DOFModel
        Model fidelity: 3, 6, 10 or 14 DOF.
    speed_mps : float
        Initial longitudinal speed in m/s.
    roadwheel_rate_deg_s : float
        Signed steering rate in degrees per second.
    start_time_s : float
        Time at which the ramp begins.
    ramp_end_time_s : float, optional
        Time at which steering stops increasing and holds its final value.
        Defaults to the simulation end for older callers.
    stop_time_s : float
        End of the simulation in seconds.
    sample_period_s : float
        Output sampling interval in seconds.
    vehicle_path : str or Path, optional
        Vehicle YAML path.
    kinematics_mode : KinematicsMode
        Lookup or nonlinear KinPy evaluation.

    Returns
    -------
    TransientResult
        Time history and solver status.
    """
    ramp_end = stop_time_s if ramp_end_time_s is None else ramp_end_time_s
    if not 0 <= start_time_s < ramp_end <= stop_time_s:
        raise ValueError("Ramp start must precede ramp end, which must not exceed simulation end.")
    duration = ramp_end - start_time_s
    return run_step_steer(
        dof=dof, speed_mps=speed_mps,
        roadwheel_step_deg=roadwheel_rate_deg_s * duration,
        step_time_s=start_time_s, rise_time_s=duration,
        stop_time_s=stop_time_s, sample_period_s=sample_period_s,
        vehicle_path=vehicle_path, kinematics_mode=kinematics_mode,
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
