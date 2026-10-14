"""Independent GGV speed slices for the file-backed workflow."""

from __future__ import annotations

from concurrent.futures import ProcessPoolExecutor
from dataclasses import asdict, replace
from itertools import repeat
import multiprocessing
import os
from pathlib import Path
from typing import TYPE_CHECKING, Any

if TYPE_CHECKING:
    from simulations.envelope.ggv.ggv_generation import GGVConfig, GGVEnvelope


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
    """Solve independent speed slices while retaining the configured order.

    Parameters
    ----------
    vehicle_path : Path
        Vehicle definition shared by all speed slices.
    config : GGVConfig
        Envelope settings. Each slice retains its lateral continuation order.

    Returns
    -------
    list[GGVEnvelope]
        Envelopes in the configured speed order. Worker failures propagate.
    """
    path = vehicle_path.resolve().as_posix()
    workers = min(4, len(config.speeds), os.cpu_count() or 1)
    if workers <= 1:
        return _generate_speed(path, asdict(config))
    if config.verbose:
        print(f"Solving {len(config.speeds)} speed slices with {workers} workers.", flush=True)
    settings = [asdict(replace(config, speeds=(speed,))) for speed in config.speeds]
    with ProcessPoolExecutor(max_workers=workers, mp_context=multiprocessing.get_context("spawn")) as pool:
        slices = pool.map(_generate_speed, repeat(path), settings)
        return [envelope for result in slices for envelope in result]
