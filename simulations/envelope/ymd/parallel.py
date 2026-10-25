"""Full-speed 14DOF YMD maps with independent, process-local solvers."""
from concurrent.futures import ProcessPoolExecutor
from dataclasses import asdict, replace
from itertools import repeat
import multiprocessing
import os
from pathlib import Path

from simulations.envelope.speed_grid import automatic_vehicle_speed_grid
from simulations.envelope.ymd.ymd_generation import YMDConfig, YMDSpeedSweepResult, generate_ymd


def _generate_speed(vehicle_path: str, settings: dict):
    from engines.dynpy import Vehicle
    from simulations.envelope.vehicle_yaml import load_vehicle_yaml, project_vehicle_yaml
    from simulations.envelope.ggv.ggv_generation import _actuator_margins

    projection = project_vehicle_yaml(load_vehicle_yaml(Path(vehicle_path)))
    model = Vehicle.from_yaml(vehicle_path).model(14)
    config = YMDConfig(**settings)
    # The yaw-moment solve holds speed. Reject torque/power demands the vehicle
    # cannot sustain, even if a mathematical tire equilibrium exists.
    def feasible(trim):
        return bool((_actuator_margins(projection.ggv, model, trim.state, trim.inputs,
                                       trim.output, config.speed) >= -1e-7).all())
    result = generate_ymd(projection.ymd, config, reduced_model=model, feasibility=feasible)
    print(f"YMD {config.speed:.2f} m/s: {int(result.converged.sum())}/{result.converged.size} accepted states.",
          flush=True)
    return result


def generate_ymd_from_vehicle(vehicle_path: Path, config: YMDConfig, *, workers: int | None = None):
    """Solve every automatic speed slice; legacy speed-sweep switches do not apply."""
    import numpy as np
    from simulations.envelope.vehicle_yaml import load_vehicle_yaml, project_vehicle_yaml

    if config.model_dof != 14:
        raise ValueError("YMD supports only 14DOF")
    path = vehicle_path.resolve().as_posix()
    projection = project_vehicle_yaml(load_vehicle_yaml(Path(path)))
    speeds = automatic_vehicle_speed_grid(projection.ggv.max_drive_speed)
    settings = [asdict(replace(config, speed=speed, verbose=False, warn_tire_load_range=False)) for speed in speeds]
    count = min(workers if workers is not None else 4, len(speeds), os.cpu_count() or 1)
    if count < 1:
        raise ValueError("YMD requires at least one worker")
    print(f"Solving full-speed YMD: {speeds[0]:.2f}–{speeds[-1]:.2f} m/s, {len(speeds)} slices, {count} workers.",
          flush=True)
    if count == 1:
        results = [_generate_speed(path, value) for value in settings]
    else:
        with ProcessPoolExecutor(max_workers=count, mp_context=multiprocessing.get_context("spawn")) as pool:
            results = list(pool.map(_generate_speed, repeat(path), settings))
    return YMDSpeedSweepResult(np.asarray(speeds), results)
