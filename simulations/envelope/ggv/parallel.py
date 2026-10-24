"""Independent GGV speed slices for the file-backed workflow."""

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
    from simulations.envelope.ggv.ggv_generation import GGVConfig, GGVEnvelope


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


def _generate_speed(vehicle_path: str, config: dict[str, Any]) -> list[GGVEnvelope]:
    """Solve a speed slice with process-local vehicle and kinematics caches.

    Parameters
    ----------
    vehicle_path : str
        Vehicle definition path.
    config : dict
        Serialized GGV settings for this worker.

    Returns
    -------
    list[GGVEnvelope]
        Completed envelopes for the assigned speed.
    """
    from engines.dynpy import Vehicle
    from simulations.envelope.ggv.ggv_generation import GGVConfig, generate_ggv
    from simulations.envelope.vehicle_yaml import load_vehicle_yaml, project_vehicle_yaml

    settings = GGVConfig(**config)
    projection = project_vehicle_yaml(load_vehicle_yaml(Path(vehicle_path)))
    model = Vehicle.from_yaml(vehicle_path).model(settings.model_dof)
    return generate_ggv(projection.ggv, settings, reduced_model=model)


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

    path = vehicle_path.resolve().as_posix()
    projection = project_vehicle_yaml(load_vehicle_yaml(Path(path)))
    config = replace(config, speeds=automatic_vehicle_speed_grid(projection.ggv.max_drive_speed))
    workers = min(4, len(config.speeds), os.cpu_count() or 1)
    if workers <= 1:
        return _generate_speed(path, asdict(config))
    if config.verbose:
        print(f"Solving {len(config.speeds)} speed slices with {workers} workers.", flush=True)
    settings = [asdict(replace(config, speeds=(speed,))) for speed in config.speeds]
    with ProcessPoolExecutor(max_workers=workers, mp_context=multiprocessing.get_context("spawn")) as pool:
        slices = pool.map(_generate_speed, repeat(path), settings)
        return [envelope for result in slices for envelope in result]
