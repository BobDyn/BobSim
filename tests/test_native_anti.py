"""Validate native anti outputs against force balance and torque support paths."""
import contextlib
import csv
import io
import math
import os

import pytest
import yaml

from app.native_knc import sprung_cg_height
from app.native_runs import run
from common.native_artifacts import ROOT


@pytest.mark.skipif(os.environ.get("BOBSIM_NATIVE_INTEGRATION") != "1", reason="Requires cached KnC binaries")
@pytest.mark.parametrize("kind,key,sign", [("knc-front", "bump_anti_dive_pct", -1),
                                        ("knc-rear-traction", "bump_anti_squat_pct", 1)])
def test_native_antis_balance_forces_transform_cg_and_close_drive_torques(kind, key, sign):
    vehicle = yaml.safe_load((ROOT / "vehicle.yml").read_text())
    side = kind.split("-")[1]
    masses = [vehicle[k] for k in ("sprung_mass", "driver_mass")]
    mass = sum(m["mass_kg"] for m in masses)
    cy, cz = [sum(m["mass_kg"] * m["cg_m"][i] for m in masses) / mass for i in (1, 2)]
    length = abs(vehicle["front"]["suspension"]["wheel_center_m"][0]
                 - vehicle["rear"]["suspension"]["wheel_center_m"][0])
    reference = None
    for amplitude in (1000, 500, -1000):
        with contextlib.redirect_stdout(io.StringIO()):
            result = run(vehicle, kind, {"kinematics_only": True, "forceMagnitude": amplitude})
        assert any(name.startswith(f"pVehicle.chassis.{side}Axle.geometry.") for name in result["overrides"])
        with (ROOT / result["csv"]).open() as stream:
            rows = [{k: float(v) for k, v in row.items() if k} for row in csv.DictReader(stream)]
        offset = 357 if side == "front" else 0
        def at(time):
            return min(rows, key=lambda row: abs(row["time"] - time - offset))
        processed = result["curves"]["curves"]
        assert "bump_anti_lift_pct" not in processed
        for i, time in enumerate(range(3, 54, 5)):
            pulse, tail = at(time), at(time + 2)
            fx = pulse["knc.fx"] - tail["knc.fx"]
            if any(row[f"knc.{w}Fz"] <= 0 for row in (pulse, tail) for w in ("left", "right")):
                assert processed[key][i] is None
                continue
            # Independent vertical force balance, not the fixture sensor.
            jacking = sum(pulse[f"knc.{w}Fz"] - tail[f"knc.{w}Fz"] for w in ("left", "right"))
            assert processed["bump_jacking_n"][i] == pytest.approx(jacking, abs=1e-6)
            # Use the native attachment frame position instead of input heave.
            roll = tail["knc.roll"]
            cg_z = (tail["chassisActuator.chassisFrame.r_0[3]"] + cy * math.sin(roll)
                    + (cz - vehicle[side]["suspension"]["wheel_center_m"][2]) * math.cos(roll))
            ground = sum(tail[f"axle.{w}CP.r_0[3]"] for w in ("left", "right")) / 2
            height = cg_z - ground
            assert sprung_cg_height(tail, vehicle) == pytest.approx(height, abs=1e-10)
            assert processed[key][i] == pytest.approx(sign * 100 * jacking / fx * length / height, abs=1e-7)
            if kind.endswith("-traction"):
                # Shaft torque reaches each wheel, with a single housing support
                # and no outboard caliper torque on either upright.
                for w in ("left", "right"):
                    assert pulse[f"brakes.{w}Shaft.inboard.tau"] == pytest.approx(
                        -pulse[f"brakes.{w}Shaft.outboard.tau"], abs=1e-8)
                    for axis in (1, 2, 3):
                        assert pulse[f"brakes.{w}WheelFrame.t[{axis}]"] == pytest.approx(0, abs=1e-9)
                wheel_torque = sum(pulse[f"brakes.{w}.tau"] for w in ("left", "right"))
                assert abs(wheel_torque) > 1
                assert pulse["brakes.differentialHousing.flange_b.tau"] == pytest.approx(wheel_torque, abs=1e-8)
        if reference is None:
            reference = processed[key]
        else:
            assert [x is None for x in processed[key]] == [x is None for x in reference]
            assert [x for x in processed[key] if x is not None] == pytest.approx(
                [x for x in reference if x is not None], abs=1e-6)
