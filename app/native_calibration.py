"""Translate the vehicle editor's physical inputs into BobLib record setters."""
from __future__ import annotations

from pathlib import Path
from typing import Any

from app import modelica_generator as generator
from common.native_artifacts import validate_overrides


def flatten(prefix: str, value: Any) -> dict:
    """Flatten record members and Modelica's one-based array indices."""
    if isinstance(value, generator.ModelicaCall):
        return assignments(prefix, value.assignments)
    if isinstance(value, generator.SemicolonMatrix):
        value = value.rows
    if isinstance(value, (list, tuple)):
        result = {}
        for i, item in enumerate(value, 1):
            if isinstance(item, (list, tuple)):
                for j, scalar in enumerate(item, 1):
                    result.update(flatten(f"{prefix}[{i},{j}]", scalar))
            else:
                result.update(flatten(f"{prefix}[{i}]", item))
        return result
    if isinstance(value, generator.ModelicaExpression):
        raise ValueError(f"Unresolved calibration expression: {prefix}")
    return {prefix: value}


def assignments(prefix: str, values) -> dict:
    result = {}
    for key, value in values:
        result.update(flatten(prefix + "." + key, value))
    return result


def vehicle_overrides(vehicle: dict, manifest: dict, root: Path) -> dict:
    """Convert relevant setup inputs, rejecting setters absent from the contract."""
    kind = manifest["identity"]["kind"]
    requested = {}
    for side in ("front", "rear"):
        if kind.startswith("knc-") and kind.split("-")[1] != side:
            continue
        data = vehicle[side]
        prefix = f"pVehicle.chassis.{side}Axle"
        arch = generator.ARCHITECTURES[vehicle["architecture"][side]]
        for suffix, values in (
            ("geometry", generator._wishbone_assignments(side, data)),
            ("steering", generator._rack_assignments(side, data)),
            ("tire.wheel.geometry", generator._wheel_assignments(side, data)),
            ("actuation", generator._axle_assignments(side, data, arch)),
            ("tire.wheel.vertical", generator._tire_z_assignments(side, data)),
        ):
            requested.update(assignments(prefix + "." + suffix, values))
        for curve in ("spring", "damper"):
            rows = data["actuation"]["shock"][curve + "_table"]["table"]
            if len(rows) > 64:
                raise ValueError(f"{side} {curve} curve exceeds the binary's 64-point capacity")
            requested[prefix + f".actuation.{curve}Points"] = len(rows)
        if arch.has_stabar:
            requested.update(assignments(prefix + ".stabilizer", generator._stabar_assignments(side, data)))
        if kind == "maneuver":
            requested.update(assignments(prefix + ".masses", generator._axle_mass_assignments(side, data)))
            requested.update(assignments(prefix + ".tire.wheel.rotation", generator._tire_y_assignments(side, data)))
            tire_path = root / "common/tire_templates" / (generator.tire_template_name(vehicle, data) + ".tir")
            tire_values = generator.parse_tir(tire_path)
            for group, value in generator._tire_model_assignments(tire_values, "radius", tire_path):
                requested.update(assignments(prefix + ".tire.force." + group,
                                             [(key, val) for key, val in value.assignments
                                              if key != "UNLOADED_RADIUS"]))
    if kind == "maneuver":
        requested["pVehicle.brakes.frontBrakeBias"] = vehicle["brake"]["front_bias"]
        for source, dest in (("sprung_mass", "baseMass"), ("driver_mass", "driverMass")):
            requested.update(assignments("pVehicle.chassis.frame." + dest,
                                         generator._mass_record_assignments(vehicle[source], source)))
        requested["pVehicle.chassis.frame.torsionalStiffness"] = vehicle["body"]["torsional_stiff_n_m_per_rad"]
        for old, new in (("pBattery", "battery"), ("pVCU", "controller"),
                         ("pInverter", "inverter"), ("pMotor", "motor")):
            for key, value in vehicle["powertrain"][old].items():
                if new == "controller" and key == "finalDriveRatio":
                    continue
                requested.update(flatten(f"pVehicle.{new}.{key}", value))
        legacy = vehicle["powertrain"]["pDriveline"]
        mapping = {"finalDriveRatio": "transmission.gearRatio", "diffInputRotorJ": "driveline.inputInertia",
                   "diff_T_preload": "driveline.differential.preloadTorque",
                   "diff_driveSideTorqueSign": "driveline.differential.driveSideTorqueSign",
                   "diff_lockFractionAccel": "driveline.differential.driveLockingFraction",
                   "diff_lockFractionDecel": "driveline.differential.coastLockingFraction",
                   "diff_kineticFrictionRatio": "driveline.differential.slidingFrictionRatio"}
        for old, new in mapping.items():
            requested["pVehicle." + new] = legacy[old]
        for suffix in ("C",):
            if legacy["halfshaftLeft" + suffix] != legacy["halfshaftRight" + suffix]:
                raise ValueError("This architecture requires matching left/right halfshaft calibration")
        requested["pVehicle.driveline.halfshaft.stiffness"] = legacy["halfshaftLeftC"]
        # Real inertia is intentionally separate from the old equivalent damping inertia.
        if "native" not in vehicle or "halfshaft_inertia_kg_m2" not in vehicle["native"]:
            raise ValueError("Set the native halfshaft inertia in Setup before running maneuvers; "
                             "the old equivalent inertia is not a physical inertia calibration")
        requested["pVehicle.driveline.halfshaft.inertia"] = vehicle["native"]["halfshaft_inertia_kg_m2"]
        aero = vehicle["aero"]
        for key, field in (("reference_speed_m_per_s", "referenceSpeed"), ("aero_ref_m", "aeroRef"),
                           ("front_ride_height_grid_m", "frontRideHeightGrid"),
                           ("rear_ride_height_grid_m", "rearRideHeightGrid"),
                           ("drag_table_n", "dragTable"), ("downforce_table_n", "downforceTable"),
                           ("mx_table_nm", "mxTable"), ("my_table_nm", "myTable"), ("mz_table_nm", "mzTable")):
            requested.update(flatten("pVehicle.aero." + field, aero[key]))
        for side in ("front", "rear"):
            count = len(aero[side + "_ride_height_grid_m"])
            if count > 16:
                raise ValueError("Aero map exceeds the binary's 16-point axis capacity")
            requested["pVehicle.aero." + side + "Points"] = count
            requested.update(flatten(f"pVehicle.chassis.{side}Axle.rideHeightReference",
                                     aero[side + "_left_ride_height_ref_m"]))
    overrides = {}
    for name, value in requested.items():
        if name in manifest["parameters"]:
            overrides[name] = value
            continue
        meta = manifest["structural"].get(name) or manifest["derived"].get(name)
        # A fixed field is acceptable only if the requested value exactly matches the artifact.
        if meta and str(value).lower() == str(meta.get("start", "")).lower():
            continue
        if kind.startswith("knc-") and any(part in name for part in
                                            (".damper", ".wheelD", ".rimR0", ".rimWidth")):
            # The static rig deliberately omits viscous forces and animation geometry.
            continue
        raise ValueError(f"Setup field cannot be applied to this binary: {name}")
    validate_overrides(manifest, overrides)
    return overrides
