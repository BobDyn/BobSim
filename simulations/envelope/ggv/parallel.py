"""Independent GGV speed slices for the file-backed envelope and lap workflows."""

from __future__ import annotations

from concurrent.futures import ProcessPoolExecutor
from dataclasses import asdict, replace
from itertools import repeat
import multiprocessing
import math
import os
from pathlib import Path
from typing import TYPE_CHECKING, Any

if TYPE_CHECKING:
    from simulations.envelope.ggv.ggv_generation import GGVConfig, GGVEnvelope, VehicleParams



def automatic_vehicle_speed_grid(maximum_speed_mps: float) -> tuple[float, ...]:
    """Sample the vehicle's positive speed range at nine uniform intervals.

    Parameters
    ----------
    maximum_speed_mps : float
        Finite positive drivetrain speed limit in meters per second.

    Returns
    -------
    tuple[float, ...]
        Nine ascending speeds from one ninth of the limit to the exact limit.
        Zero speed is excluded because the steady cornering equations require motion.
    """
    if not math.isfinite(maximum_speed_mps) or maximum_speed_mps <= 0.0:
        raise ValueError("Automatic GGV coverage requires a finite positive vehicle speed limit.")
    return (*(maximum_speed_mps * (index / 9) for index in range(1, 9)), maximum_speed_mps)


def ggv_worker_count(speed_count: int) -> int:
    """Choose how many processes solve a GGV.

    Parameters
    ----------
    speed_count : int
        Number of independent speed slices.

    Returns
    -------
    int
        One process per slice, up to the CPU count. Slices are independent
        and the grid has nine, so a fixed cap would only idle cores.
        A result of one means the caller should solve in-process.
    """
    return max(1, min(speed_count, os.cpu_count() or 1))


def _generate_speed(
    vehicle_path: str,
    config: dict[str, Any],
    vehicle: VehicleParams | None = None,
    drive_power_limit_w: float | None = None,
) -> list[GGVEnvelope]:
    """Solve a speed slice with process-local vehicle and kinematics caches.

    Parameters
    ----------
    vehicle_path : str
        Vehicle definition path.
    config : dict
        Serialized GGV settings for this worker.
    vehicle : VehicleParams, optional
        Already projected envelope parameters. When omitted, the worker projects
        ``vehicle_path`` itself.
    drive_power_limit_w : float, optional
        Event power cap applied to the DynPy vehicle before building its model,
        as ``Vehicle.with_power_limit`` does for the caller.

    Returns
    -------
    list[GGVEnvelope]
        Completed envelopes for the assigned speeds.
    """
    from engines.dynpy import Vehicle
    from simulations.envelope.ggv.ggv_generation import GGVConfig, generate_ggv
    from simulations.envelope.vehicle_yaml import load_vehicle_yaml, project_vehicle_yaml

    settings = GGVConfig(**config)
    if vehicle is None:
        vehicle = project_vehicle_yaml(load_vehicle_yaml(Path(vehicle_path))).ggv
    dynamics = Vehicle.from_yaml(vehicle_path)
    if drive_power_limit_w is not None:
        dynamics = dynamics.with_power_limit(drive_power_limit_w)
    return generate_ggv(vehicle, settings, reduced_model=dynamics.model(settings.model_dof))


def generate_ggv_speeds(
    vehicle_path: Path,
    config: GGVConfig,
    *,
    vehicle: VehicleParams | None = None,
    drive_power_limit_w: float | None = None,
) -> list[GGVEnvelope]:
    """Solve the configured speed slices, one process per slice.

    Speed slices share no solver state: each restarts its lateral search,
    acceleration bounds and continuation seeds. Every worker rebuilds the model
    from ``vehicle_path``, so results match a serial ``generate_ggv`` call.

    Parameters
    ----------
    vehicle_path : Path
        Vehicle definition shared by all speed slices.
    config : GGVConfig
        Model, solver settings and the speeds to solve, in output order.
    vehicle : VehicleParams, optional
        Projected envelope parameters, for callers that adjust them, such as an
        event power cap. Must be picklable.
    drive_power_limit_w : float, optional
        Event power cap for the DynPy vehicle that supplies the reduced model.

    Returns
    -------
    list[GGVEnvelope]
        Envelopes in configured speed order. Worker failures propagate.
    """
    path = vehicle_path.resolve().as_posix()
    workers = ggv_worker_count(len(config.speeds))
    if workers <= 1:
        return _generate_speed(path, asdict(config), vehicle, drive_power_limit_w)
    if config.verbose:
        print(f"Solving {len(config.speeds)} speed slices with {workers} workers.", flush=True)
    settings = [asdict(replace(config, speeds=(speed,))) for speed in config.speeds]
    with ProcessPoolExecutor(max_workers=workers, mp_context=multiprocessing.get_context("spawn")) as pool:
        slices = pool.map(_generate_speed, repeat(path), settings, repeat(vehicle), repeat(drive_power_limit_w))
        return [envelope for result in slices for envelope in result]


def generate_ggv_from_vehicle(vehicle_path: Path, config: GGVConfig) -> list[GGVEnvelope]:
    """Solve independent speed slices across the vehicle speed range.

    Parameters
    ----------
    vehicle_path : Path
        Vehicle definition shared by all speed slices.
    config : GGVConfig
        Model and solver settings. Saved speed samples are ignored. Each slice
        retains its lateral continuation order.

    Returns
    -------
    list[GGVEnvelope]
        Envelopes in ascending speed order. Worker failures propagate.
    """
    from simulations.envelope.vehicle_yaml import load_vehicle_yaml, project_vehicle_yaml

    projection = project_vehicle_yaml(load_vehicle_yaml(vehicle_path.resolve()))
    config = replace(config, speeds=automatic_vehicle_speed_grid(projection.ggv.max_drive_speed))
    return generate_ggv_speeds(vehicle_path, config)
