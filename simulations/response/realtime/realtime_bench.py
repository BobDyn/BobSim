"""Measure fixed-period stepping cost without claiming feedback control."""

from __future__ import annotations

import argparse
import hashlib
import json
import math
import time
from collections.abc import Callable, Iterator
from contextlib import suppress
from pathlib import Path
from tempfile import TemporaryDirectory
from typing import Any, cast

import numpy as np
from scipy.integrate import solve_ivp

from common.vehicle_io import repo_root, vehicle_yaml_path
from engines.dynpy import DOFModel, ModelInputs, Vehicle

DEFAULT_FMU = "simulations/mbd/BuildBobLib/VehicleFMU/VehicleSim.fmu"
DEFAULT_OUTPUT = "simulations/mbd/generated_results/realtime_bench.json"
FMU_SIGNALS = ("velX", "velY", "yawVel", "accY")


def _steps(dt_s: float, stop_s: float) -> Iterator[tuple[float, float]]:
    if not all(math.isfinite(v) and v > 0.0 for v in (dt_s, stop_s)):
        raise ValueError("Step and stop times must be finite and positive.")
    for index in range(math.ceil(stop_s / dt_s)):
        start = index * dt_s
        end = min((index + 1) * dt_s, stop_s)
        if end > start:
            yield start, end


def _summary(walls: list[float], sim_s: float, setup_s: float, steps: int) -> dict[str, Any]:
    durations = np.asarray(walls, dtype=float)
    total = float(durations.sum())
    return {
        "setup_wall_s": setup_s,
        "simulated_s": sim_s,
        "stepping_wall_s": total,
        "realtime_factor": sim_s / total if total > 0.0 else None,
        "step_wall_ms_p50": float(np.percentile(durations, 50) * 1e3) if durations.size else None,
        "step_wall_ms_p99": float(np.percentile(durations, 99) * 1e3) if durations.size else None,
        "step_wall_ms_max": float(durations.max() * 1e3) if durations.size else None,
        "steps": steps,
        "attempted_steps": len(walls),
    }


def bench_fmu(fmu_path: Path, dt_s: float, stop_s: float) -> dict[str, Any]:
    """Step an FMI 2.0 co-simulation model and retain failure diagnostics.

    Parameters
    ----------
    fmu_path : Path
        Archive containing an FMI 2.0 co-simulation model.
    dt_s : float
        Communication interval in seconds.
    stop_s : float
        Requested end time in seconds.

    Returns
    -------
    dict
        Setup and stepping timings, completion status, and final signals.
    """
    from fmpy import extract, read_model_description
    from fmpy.fmi2 import FMU2Slave

    schedule = _steps(dt_s, stop_s)
    setup_start = time.perf_counter()
    description = read_model_description(fmu_path.as_posix())
    if description.fmiVersion != "2.0" or description.coSimulation is None:
        raise ValueError(f"{fmu_path} needs an FMI 2.0 co-simulation interface.")
    references = {v.name: v.valueReference for v in description.modelVariables if v.type == "Real"}
    readable = [name for name in FMU_SIGNALS if name in references]
    inputs = [v.name for v in description.modelVariables if v.causality == "input"]
    walls: list[float] = []
    simulated_s = 0.0
    steps = 0
    failure = None
    final: dict[str, float] = {}
    setup_s = 0.0
    with TemporaryDirectory(prefix="bobsim-fmu-") as directory:
        extract(fmu_path.as_posix(), unzipdir=directory)
        fmu = FMU2Slave(
            guid=description.guid,
            unzipDirectory=directory,
            modelIdentifier=description.coSimulation.modelIdentifier,
            instanceName="realtime_bench",
        )
        instantiated = initialized = False
        try:
            fmu.instantiate()
            instantiated = True
            fmu.setupExperiment(startTime=0.0, stopTime=stop_s)
            fmu.enterInitializationMode()
            fmu.exitInitializationMode()
            initialized = True
            setup_s = time.perf_counter() - setup_start
            for start_s, end_s in schedule:
                start = time.perf_counter()
                try:
                    fmu.doStep(currentCommunicationPoint=start_s, communicationStepSize=end_s - start_s)
                finally:
                    walls.append(time.perf_counter() - start)
                steps += 1
                simulated_s = end_s
            if readable:
                final = dict(zip(readable, fmu.getReal([references[n] for n in readable])))
                if not all(math.isfinite(v) for v in final.values()):
                    final = {}
                    raise RuntimeError("FMU returned non-finite final signals.")
        except Exception as error:
            failure = f"{type(error).__name__}: {error}"
        finally:
            if not initialized:
                setup_s = time.perf_counter() - setup_start
            if initialized:
                with suppress(Exception):
                    fmu.terminate()
            if instantiated:
                fmu.freeInstance()
    result = _summary(walls, simulated_s, setup_s, steps)
    result.update(
        model="VehicleSim FMU (co-simulation, CVODE)",
        states=description.numberOfContinuousStates,
        inputs=inputs,
        completed=failure is None,
        failure=failure,
        final=final,
        fmu_sha256=hashlib.sha256(fmu_path.read_bytes()).hexdigest(),
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
    """Integrate prescribed inputs in controller-sized intervals.

    Parameters
    ----------
    vehicle : Vehicle
        Vehicle definition used to construct the reduced model.
    dof : DOFModel
        Degrees of freedom of the selected model.
    dt_s : float
        Input update interval in seconds.
    stop_s : float
        Requested end time in seconds.
    speed_mps : float
        Initial speed; positive values use a steady-state trim.
    controls : Callable
        Maps interval start time and trim inputs to prescribed inputs.

    Returns
    -------
    dict
        Setup and stepping timings, completion status, and final state.
    """
    schedule = _steps(dt_s, stop_s)
    setup_start = time.perf_counter()
    model = vehicle.model(dof)
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
    simulated_s = 0.0
    steps = 0
    failure = None
    try:
        for start_s, end_s in schedule:
            inputs = controls(start_s, base)
            start = time.perf_counter()
            try:
                solution = solve_ivp(  # type: ignore[call-overload]
                    lambda time_s, x: model.derivative(time_s, x, inputs),
                    (start_s, end_s), state, method=method, rtol=1e-6, atol=1e-8,
                )
            finally:
                walls.append(time.perf_counter() - start)
            if not solution.success:
                raise RuntimeError(solution.message)
            if not np.all(np.isfinite(solution.y[:, -1])):
                raise RuntimeError("Integrator returned a non-finite state.")
            state = solution.y[:, -1]
            steps += 1
            simulated_s = end_s
    except Exception as error:
        failure = f"{type(error).__name__}: {error}"
    names = model.state_names
    final = {name: float(state[names.index(name)]) for name in ("x", "y", "yaw", "u", "v", "yaw_rate") if name in names}
    result = _summary(walls, simulated_s, setup_s, steps)
    result.update(model=f"DynPy {dof}DOF ({method})", states=model.state_size,
                  completed=failure is None, failure=failure, final=final)
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


def _positive(value: str) -> float:
    number = float(value)
    if not math.isfinite(number) or number <= 0.0:
        raise argparse.ArgumentTypeError("Must be finite and positive.")
    return number


def _nonnegative(value: str) -> float:
    number = float(value)
    if not math.isfinite(number) or number < 0.0:
        raise argparse.ArgumentTypeError("Must be finite and nonnegative.")
    return number


def _parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dt-s", type=_positive, default=0.02, help="Communication period (default 50 Hz)")
    parser.add_argument("--stop-s", type=_positive, default=10.0)
    parser.add_argument("--speed-mps", type=_nonnegative, default=15.0)
    parser.add_argument("--dof", type=int, nargs="+", choices=(3, 6, 10, 14), default=[3, 6, 10, 14])
    parser.add_argument("--fmu", type=Path, default=Path(DEFAULT_FMU))
    parser.add_argument("--skip-fmu", action="store_true")
    parser.add_argument("--vehicle", type=Path, help="vehicle.yml for DynPy; does not change the compiled FMU")
    parser.add_argument("--launch-torque-nm", type=_nonnegative, default=150.0)
    parser.add_argument("--output", type=Path, default=Path(DEFAULT_OUTPUT))
    return parser.parse_args()


def main() -> None:
    args = _parse_args()
    root = repo_root()
    fmu_path = args.fmu if args.fmu.is_absolute() else root / args.fmu
    if not args.skip_fmu and not fmu_path.is_file():
        raise SystemExit(f"{fmu_path} not found. Run 'make standard-build-fmu' or pass --skip-fmu.")
    vehicle_path = args.vehicle.resolve() if args.vehicle else vehicle_yaml_path()
    output = args.output if args.output.is_absolute() else root / args.output
    output.parent.mkdir(parents=True, exist_ok=True)
    results: dict[str, Any] = {
        "dt_s": args.dt_s, "stop_s": args.stop_s,
        "vehicle": vehicle_path.as_posix(),
        "vehicle_sha256": hashlib.sha256(vehicle_path.read_bytes()).hexdigest(),
        "expected_cases": 2 * len(args.dof) + int(not args.skip_fmu),
        "runs": [],
    }
    vehicle = Vehicle.from_yaml(vehicle_path)

    def record(model: str, scenario: str, run_case: Callable[[], dict[str, Any]]) -> None:
        try:
            run = run_case()
        except Exception as error:
            run = {"model": model, "completed": False, "failure": f"{type(error).__name__}: {error}"}
        run["scenario"] = scenario
        results["runs"].append(run)
        results["completed"] = (len(results["runs"]) == results["expected_cases"]
                                and all(r["completed"] for r in results["runs"]))
        output.write_text(json.dumps(results, indent=2, allow_nan=False) + "\n", encoding="utf-8")
        print(json.dumps(run, allow_nan=False), flush=True)

    for dof in args.dof:
        dof_model = cast(DOFModel, dof)
        for scenario, speed, controls in (
            (f"prescribed 5 deg steer at {args.speed_mps:g} m/s", args.speed_mps, _step_steer(5.0)),
            (f"launch from rest, {args.launch_torque_nm:g} N m per rear wheel", 0.0, _launch(args.launch_torque_nm)),
        ):
            record(f"DynPy {dof}DOF", scenario, lambda: bench_dyn_py(
                vehicle, dof_model, dt_s=args.dt_s, stop_s=args.stop_s, speed_mps=speed, controls=controls,
            ))
    if not args.skip_fmu:
        record("VehicleSim FMU", "built-in StandardVCU manoeuvre",
               lambda: bench_fmu(fmu_path, args.dt_s, args.stop_s))
    print(f"Results: {output}")
    if not results["completed"]:
        raise SystemExit(1)


if __name__ == "__main__":
    main()
