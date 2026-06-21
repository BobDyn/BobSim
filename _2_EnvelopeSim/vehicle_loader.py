"""Compatibility loader for active BobSim vehicle projections."""

from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
from typing import Any
import math

from _0_Utils.vehicle_io import repo_root
from _2_EnvelopeSim.vehicle_yaml import (
    DEFAULT_VEHICLE_YAML,
    load_vehicle_yaml,
    project_vehicle_yaml,
)


@dataclass(frozen=True)
class ActiveEnvelopeInputs:
    mass: float
    wheelbase: float
    track_front: float
    track_rear: float
    front_static_frac: float
    lltd: float
    cl_a: float
    cd_a: float
    aero_reference_speed: float
    aero_balance_front: float
    max_drive_power: float
    max_drive_force: float
    max_brake_force: float
    drive_distribution_front: float
    brake_distribution_front: float
    lltd_source: str
    aero_source: str


def load_active_vehicle_yaml(path: str | Path | None = None) -> tuple[dict[str, Any], Path]:
    source = Path(path) if path is not None else DEFAULT_VEHICLE_YAML
    if not source.is_absolute():
        source = repo_root() / source
    return load_vehicle_yaml(source), source


def load_active_envelope_inputs(path: str | Path | None = None) -> ActiveEnvelopeInputs:
    vehicle_data, _source = load_active_vehicle_yaml(path)
    projection = project_vehicle_yaml(vehicle_data, repo_root=repo_root())
    vehicle = projection.ggv
    summary = projection.summary

    reference_speed = float(summary.get("reference_speed_m_per_s", math.nan))
    aero_source = (
        "vehicle_yaml_nominal_ride_height"
        if math.isfinite(reference_speed)
        else "vehicle_yaml_no_aero_map"
    )

    return ActiveEnvelopeInputs(
        mass=float(vehicle.mass),
        wheelbase=float(vehicle.wheelbase),
        track_front=float(vehicle.track_front),
        track_rear=float(vehicle.track_rear),
        front_static_frac=float(vehicle.front_static_frac),
        lltd=float(vehicle.lltd),
        cl_a=float(vehicle.cl_a),
        cd_a=float(vehicle.cd_a),
        aero_reference_speed=reference_speed,
        aero_balance_front=float(vehicle.aero_balance_front),
        max_drive_power=float(vehicle.max_drive_power),
        max_drive_force=float(vehicle.max_drive_force),
        max_brake_force=float(vehicle.max_brake_force),
        drive_distribution_front=float(vehicle.drive_distribution_front),
        brake_distribution_front=float(vehicle.brake_distribution_front),
        lltd_source=str(summary.get("lltd_source", "vehicle_yaml_projection")),
        aero_source=aero_source,
    )
