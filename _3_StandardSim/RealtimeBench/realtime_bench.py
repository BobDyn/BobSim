"""Time fixed-step stepping of the VehicleSim FMU and the dyn_py models.

A closed-loop caller (a ROS node, a driver model) advances the plant one
controller period at a time and reads the state back. This measures what that
costs for each model, as the ratio of simulated time to wall time.
"""

from __future__ import annotations

import argparse
import json
import math
import time
from collections.abc import Callable
from pathlib import Path
from typing import Any, cast

import numpy as np
from scipy.integrate import solve_ivp

from _0_Utils.dyn_py import DOFModel, ModelInputs, Vehicle
from _0_Utils.vehicle_io import repo_root

DEFAULT_FMU = "_3_StandardSim/BuildBobLib/VehicleFMU/VehicleSim.fmu"
DEFAULT_OUTPUT = "_3_StandardSim/generated_results/realtime_bench.json"
FMU_SIGNALS = ("velX", "velY", "yawVel", "accY")


def _summary(step_wall_s: list[float], sim_s: float, setup_s: float) -> dict[str, Any]:
    walls = np.asarray(step_wall_s, dtype=float)
    total = float(walls.sum())
    return {
        "setup_wall_s": setup_s,
        "simulated_s": sim_s,
        "stepping_wall_s": total,
        "realtime_factor": sim_s / total if total > 0.0 else math.inf,
        "step_wall_ms_p50": float(np.percentile(walls, 50) * 1e3) if walls.size else None,
        "step_wall_ms_p99": float(np.percentile(walls, 99) * 1e3) if walls.size else None,
        "step_wall_ms_max": float(walls.max() * 1e3) if walls.size else None,
        "steps": int(walls.size),
    }


def bench_fmu(fmu_path: Path, dt_s: float, stop_s: float) -> dict[str, Any]:
    from fmpy import extract, read_model_description
    from fmpy.fmi2 import FMU2Slave

    setup_start = time.perf_counter()
    description = read_model_description(str(fmu_path))
    if description.coSimulation is None:
        raise ValueError(f"{fmu_path} has no co-simulation interface.")
    fmu = FMU2Slave(
        guid=description.guid,
        unzipDirectory=extract(str(fmu_path)),
        modelIdentifier=description.coSimulation.modelIdentifier,
        instanceName="realtime_bench",
    )
    references = {v.name: v.valueReference for v in description.modelVariables}
    readable = [name for name in FMU_SIGNALS if name in references]
    fmu.instantiate()
    fmu.setupExperiment(startTime=0.0, stopTime=stop_s)
    fmu.enterInitializationMode()
    fmu.exitInitializationMode()
    setup_s = time.perf_counter() - setup_start

    walls: list[float] = []
    t = 0.0
    stopped_early = None
    try:
        while t < stop_s - 1e-9:
            start = time.perf_counter()
            fmu.doStep(currentCommunicationPoint=t, communicationStepSize=dt_s)
            walls.append(time.perf_counter() - start)
            t += dt_s
    except Exception as error:  # noqa: BLE001 - the model's own termination monitors end runs this way
        stopped_early = f"{type(error).__name__}: {error}"
    final = dict(zip(readable, fmu.getReal([references[n] for n in readable]))) if readable else {}
    fmu.terminate()
    fmu.freeInstance()

    result = _summary(walls, len(walls) * dt_s, setup_s)
    result.update(
        model="VehicleSim FMU (co-simulation, CVODE)",
        states=description.numberOfContinuousStates,
        stopped_early=stopped_early,
        final=final,
    )
    return result


def bench_dyn_py(
    vehicle: Vehicle,
    dof: DOFModel,
    *,
    dt_s: float,
    stop_s: float,
    speed_mps: float,
    controls: Callable[[float, ModelInputs], ModelInputs],
) -> dict[str, Any]:
    model = vehicle.model(dof)
    setup_start = time.perf_counter()
    if speed_mps > 0.0:
        trim = vehicle.steady_state(dof, speed_mps=speed_mps)
        if not trim.success:
            raise RuntimeError(f"{dof}DOF trim failed at {speed_mps} m/s: {trim.message}")
        state, base = trim.state, trim.inputs
    else:
        state, base = vehicle.initial_state(dof, 0.0), ModelInputs()
    setup_s = time.perf_counter() - setup_start
    method = "Radau" if dof >= 10 else "RK45"

    walls: list[float] = []
    t = 0.0
    failure = None
    while t < stop_s - 1e-9:
        inputs = controls(t, base)
        start = time.perf_counter()
        solution = solve_ivp(  # type: ignore[call-overload]
            lambda time_s, x: model.derivative(time_s, x, inputs),
            (t, t + dt_s),
            state,
            method=method,
            rtol=1e-6,
            atol=1e-8,
        )
        walls.append(time.perf_counter() - start)
        if not solution.success or not np.all(np.isfinite(solution.y[:, -1])):
            failure = solution.message
            break
        state = solution.y[:, -1]
        t += dt_s

    names = model.state_names
    final = {name: float(state[names.index(name)]) for name in ("x", "y", "yaw", "u", "v", "yaw_rate") if name in names}
    result = _summary(walls, len(walls) * dt_s, setup_s)
    result.update(model=f"dyn_py {dof}DOF ({method})", states=model.state_size, failure=failure, final=final)
    return result


def _step_steer(step_deg: float) -> Callable[[float, ModelInputs], ModelInputs]:
    def controls(t: float, base: ModelInputs) -> ModelInputs:
        fraction = float(np.clip((t - 1.0) / 0.02, 0.0, 1.0))
        return ModelInputs(steering_rad=fraction * math.radians(step_deg), wheel_torques_nm=base.wheel_torques_nm)

    return controls


def _launch(torque_nm: float) -> Callable[[float, ModelInputs], ModelInputs]:
    def controls(_t: float, _base: ModelInputs) -> ModelInputs:
        return ModelInputs(wheel_torques_nm=(0.0, 0.0, torque_nm, torque_nm))

    return controls


def _parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dt-s", type=float, default=0.02, help="Controller period (default 50 Hz)")
    parser.add_argument("--stop-s", type=float, default=10.0)
    parser.add_argument("--speed-mps", type=float, default=15.0)
    parser.add_argument("--dof", type=int, nargs="+", choices=(3, 6, 10, 14), default=[3, 6, 10, 14])
    parser.add_argument("--fmu", type=Path, default=Path(DEFAULT_FMU))
    parser.add_argument("--skip-fmu", action="store_true")
    parser.add_argument("--vehicle", type=Path, help="vehicle.yml for the dyn_py models")
    parser.add_argument("--launch-torque-nm", type=float, default=150.0)
    parser.add_argument("--output", type=Path, default=Path(DEFAULT_OUTPUT))
    return parser.parse_args()


def main() -> None:
    args = _parse_args()
    root = repo_root()
    results: dict[str, Any] = {
        "dt_s": args.dt_s,
        "stop_s": args.stop_s,
        "vehicle": str(args.vehicle) if args.vehicle else "vehicle.yml",
        "runs": [],
    }

    vehicle = Vehicle.from_yaml(args.vehicle)
    for dof in args.dof:
        dof_model = cast(DOFModel, dof)
        for scenario, speed, controls in (
            (f"step steer 5 deg at {args.speed_mps:g} m/s", args.speed_mps, _step_steer(5.0)),
            (f"launch from rest, {args.launch_torque_nm:g} N m per rear wheel", 0.0, _launch(args.launch_torque_nm)),
        ):
            run = bench_dyn_py(
                vehicle, dof_model, dt_s=args.dt_s, stop_s=args.stop_s, speed_mps=speed, controls=controls
            )
            run["scenario"] = scenario
            results["runs"].append(run)
            print(json.dumps(run), flush=True)

    if not args.skip_fmu:
        fmu_path = args.fmu if args.fmu.is_absolute() else root / args.fmu
        if not fmu_path.exists():
            raise SystemExit(f"{fmu_path} not found. Run 'make standard-build-fmu' or pass --skip-fmu.")
        run = bench_fmu(fmu_path, args.dt_s, args.stop_s)
        run["scenario"] = "built-in StandardVCU manoeuvre from initialVel"
        results["runs"].append(run)
        print(json.dumps(run), flush=True)

    output = args.output if args.output.is_absolute() else root / args.output
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(results, indent=2) + "\n", encoding="utf-8")
    print(f"\n{'model':38} {'scenario':42} {'x realtime':>10} {'p99 ms':>8}")
    for run in results["runs"]:
        note = run.get("failure") or run.get("stopped_early") or ""
        print(
            f"{run['model']:38} {run['scenario']:42} {run['realtime_factor']:10.2f} "
            f"{run['step_wall_ms_p99'] or float('nan'):8.1f} {note}"
        )


if __name__ == "__main__":
    main()
