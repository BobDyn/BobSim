#!/usr/bin/env python3
"""Load active vehicle inputs for the envelope simulations.

The envelope tools only need a reduced scalar model of the vehicle, but the
values should still come from the same active vehicle definition that drives
the generated Modelica model. This helper pulls the shared geometry, mass
properties, tire coefficients, and nominal aero scalars from the synced
``vehicle.yml`` and, when available, the latest FourPost metrics.
"""

from __future__ import annotations

import csv
from dataclasses import dataclass
from pathlib import Path
from typing import Any

import numpy as np

from _0_Utils.external.BobLib.Generation.scripts.build_common import (
    get_path,
    load_yaml,
    parse_tir,
    repo_root,
    require_key,
    require_mapping,
    require_section,
    require_side,
    tire_template_name,
    tire_templates_root,
    vehicle_yaml_path,
)


FloatArray = np.ndarray


@dataclass(frozen=True)
class ActiveVehicleEnvelopeInputs:
    source_yaml: Path
    vehicle_name: str
    tire_template: str
    tire_template_path: Path
    mass: float
    wheelbase: float
    track_front: float
    track_rear: float
    cg_height: float
    front_static_frac: float
    lltd: float
    lltd_source: str
    cl_a: float
    cd_a: float
    aero_source: str
    aero_balance_front: float
    aero_reference_speed: float
    fz_ref: float
    fz_min_valid: float
    fz_max_valid: float
    pdx1: float
    pdx2: float
    pdy1: float
    pdy2: float
    pky1: float
    pky2: float
    mu_min: float = 0.8


def force_to_aero_area(
    downforce_n: float,
    drag_n: float,
    speed_mps: float,
    rho: float = 1.225,
) -> tuple[float, float]:
    """Convert a force pair at a known speed into equivalent ClA and CdA."""
    if speed_mps <= 0.0:
        raise ValueError("speed_mps must be positive.")

    q = 0.5 * rho * speed_mps**2
    cl_a = downforce_n / q
    cd_a = drag_n / q
    return cl_a, cd_a


def load_active_vehicle_yaml(source_yaml: Path | None = None) -> tuple[dict[str, Any], Path]:
    """Load the active vehicle YAML, preferring the repo-root source copy."""
    if source_yaml is not None:
        return load_yaml(source_yaml), source_yaml

    candidates = (
        repo_root() / "vehicle.yml",
        vehicle_yaml_path(),
    )
    for candidate in candidates:
        if candidate.exists():
            return load_yaml(candidate), candidate

    raise FileNotFoundError(
        "Missing active vehicle.yml. Run `make sync-vehicle-yaml` or keep the "
        "repo-root vehicle.yml present."
    )


def _mass_point(section: dict[str, Any], *, path: str) -> tuple[float, FloatArray]:
    mass = float(require_key(section, path, "mass_kg"))
    cg = np.asarray(require_key(section, path, "cg_m"), dtype=float).reshape(3)
    return mass, cg


def _combine_mass_points(points: list[tuple[float, FloatArray]]) -> tuple[float, FloatArray]:
    total_mass = float(sum(mass for mass, _ in points))
    if total_mass <= 0.0:
        raise ValueError("Vehicle total mass must be positive.")

    cg = np.zeros(3, dtype=float)
    for mass, point in points:
        cg += mass * point
    cg /= total_mass

    return total_mass, cg


def _load_lltd_front_frac() -> tuple[float | None, str]:
    """Prefer the latest four-post report, otherwise fall back to static mass bias."""
    metrics_path = repo_root() / "_3_StandardSim" / "results" / "four_post_eval_report_metrics.csv"
    if not metrics_path.exists():
        return None, "static front mass fraction fallback"

    with metrics_path.open("r", newline="", encoding="utf-8") as f:
        reader = csv.DictReader(f)
        for row in reader:
            if row.get("metric") != "avg_lltd_front_frac":
                continue
            raw = str(row.get("value", "")).strip()
            if not raw:
                return None, "static front mass fraction fallback"
            try:
                value = float(raw)
            except ValueError:
                return None, "static front mass fraction fallback"
            if not np.isfinite(value):
                return None, "static front mass fraction fallback"
            return value, "four-post report metrics"

    return None, "static front mass fraction fallback"


def _load_nominal_aero_scalars(
    data: dict[str, Any],
    yaml_path: Path,
) -> tuple[float, float, float, str]:
    aero = require_mapping(data, "aero", yaml_path)
    reference_speed = float(require_key(aero, "aero", "reference_speed_m_per_s"))

    drag_table = np.asarray(require_key(aero, "aero", "drag_table_n"), dtype=float)
    downforce_table = np.asarray(require_key(aero, "aero", "downforce_table_n"), dtype=float)
    if drag_table.ndim != 2 or downforce_table.ndim != 2:
        raise ValueError(f"{yaml_path}: aero tables must be 2D arrays.")

    row = drag_table.shape[0] // 2
    col = drag_table.shape[1] // 2
    drag_n = float(drag_table[row, col])
    downforce_n = float(downforce_table[row, col])
    cl_a, cd_a = force_to_aero_area(downforce_n, drag_n, reference_speed)
    return cl_a, cd_a, reference_speed, f"center cell ({row + 1}, {col + 1}) of the active aero map"


def _tir_float(tir: dict[str, float | str], key: str, tir_path: Path) -> float:
    value = tir.get(key)
    if not isinstance(value, (int, float)):
        raise ValueError(f"{tir_path}: missing numeric tire coefficient {key}.")
    return float(value)


def _load_tire_coefficients(
    data: dict[str, Any],
    yaml_path: Path,
) -> tuple[str, Path, float, float, float, float, float, float, float, float, float]:
    front_side = require_side(data, "front")
    template = tire_template_name(data, front_side)
    tir_path = tire_templates_root(data) / f"{template}.tir"
    if not tir_path.exists():
        raise FileNotFoundError(
            f"Missing tire template: {tir_path}\n"
            "Place the .tir file under paths.tire_templates, or update "
            "<side>.tire.template / defaults.tire_template in vehicle.yml."
        )

    tir = parse_tir(tir_path)
    if not tir:
        raise ValueError(f"{tir_path} did not contain parseable key=value coefficients.")

    return (
        template,
        tir_path,
        _tir_float(tir, "FNOMIN", tir_path),
        _tir_float(tir, "FZMIN", tir_path),
        _tir_float(tir, "FZMAX", tir_path),
        _tir_float(tir, "PDX1", tir_path),
        _tir_float(tir, "PDX2", tir_path),
        _tir_float(tir, "PDY1", tir_path),
        _tir_float(tir, "PDY2", tir_path),
        _tir_float(tir, "PKY1", tir_path),
        _tir_float(tir, "PKY2", tir_path),
    )


def load_active_envelope_inputs(source_yaml: Path | None = None) -> ActiveVehicleEnvelopeInputs:
    """Build the scalar vehicle model used by the envelope analyses."""
    data, yaml_path = load_active_vehicle_yaml(source_yaml)

    vehicle_name = str(get_path(data, ["vehicle", "name"], "ActiveVehicle"))

    front_side = require_side(data, "front")
    rear_side = require_side(data, "rear")
    front_suspension = require_section(front_side, "front", "suspension")
    rear_suspension = require_section(rear_side, "rear", "suspension")

    front_wc = np.asarray(require_key(front_suspension, "front.suspension", "wheel_center_m"), dtype=float).reshape(3)
    rear_wc = np.asarray(require_key(rear_suspension, "rear.suspension", "wheel_center_m"), dtype=float).reshape(3)

    wheelbase = abs(float(front_wc[0]) - float(rear_wc[0]))
    if wheelbase <= 0.0:
        raise ValueError(f"{yaml_path}: wheelbase must be positive.")

    track_front = abs(2.0 * float(front_wc[1]))
    track_rear = abs(2.0 * float(rear_wc[1]))
    if track_front <= 0.0 or track_rear <= 0.0:
        raise ValueError(f"{yaml_path}: track widths must be positive.")

    points: list[tuple[float, FloatArray]] = []
    points.append(_mass_point(require_mapping(data, "sprung_mass", yaml_path), path="sprung_mass"))

    driver = data.get("driver_mass")
    if isinstance(driver, dict):
        points.append(_mass_point(driver, path="driver_mass"))

    for side_name in ("front", "rear"):
        side = require_side(data, side_name)
        masses = require_section(side, side_name, "masses")
        for mass_name in ("unsprung", "upper_control_arm", "lower_control_arm", "tie_rod"):
            mass_path = f"{side_name}.masses.{mass_name}"
            points.append(
                _mass_point(
                    require_section(masses, f"{side_name}.masses", mass_name),
                    path=mass_path,
                )
            )

    total_mass, cg = _combine_mass_points(points)
    cg_height = float(cg[2])
    front_static_frac = (float(cg[0]) - float(rear_wc[0])) / wheelbase
    if front_static_frac < -1e-6 or front_static_frac > 1.0 + 1e-6:
        raise ValueError(f"{yaml_path}: derived front static fraction is out of range: {front_static_frac:.6f}")
    front_static_frac = float(min(max(front_static_frac, 0.0), 1.0))

    lltd_value, lltd_source = _load_lltd_front_frac()
    if lltd_value is None:
        lltd_value = front_static_frac

    cl_a, cd_a, aero_reference_speed, aero_source = _load_nominal_aero_scalars(data, yaml_path)

    (
        tire_template,
        tire_template_path,
        fz_ref,
        fz_min_valid,
        fz_max_valid,
        pdx1,
        pdx2,
        pdy1,
        pdy2,
        pky1,
        pky2,
    ) = _load_tire_coefficients(data, yaml_path)

    return ActiveVehicleEnvelopeInputs(
        source_yaml=yaml_path,
        vehicle_name=vehicle_name,
        tire_template=tire_template,
        tire_template_path=tire_template_path,
        mass=total_mass,
        wheelbase=wheelbase,
        track_front=track_front,
        track_rear=track_rear,
        cg_height=cg_height,
        front_static_frac=front_static_frac,
        lltd=float(lltd_value),
        lltd_source=lltd_source,
        cl_a=cl_a,
        cd_a=cd_a,
        aero_source=aero_source,
        aero_balance_front=0.50,
        aero_reference_speed=aero_reference_speed,
        fz_ref=fz_ref,
        fz_min_valid=fz_min_valid,
        fz_max_valid=fz_max_valid,
        pdx1=pdx1,
        pdx2=pdx2,
        pdy1=pdy1,
        pdy2=pdy2,
        pky1=pky1,
        pky2=pky2,
    )
