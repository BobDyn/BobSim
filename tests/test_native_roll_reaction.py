"""Check roll-axis reaction against an independent native moment balance."""
import contextlib
import csv
import io
import os

import pytest
import yaml

from app.native_runs import run
from common.native_artifacts import ROOT


@pytest.mark.skipif(os.environ.get("BOBSIM_NATIVE_INTEGRATION") != "1", reason="Requires cached KnC binaries")
@pytest.mark.parametrize("side", ["front", "rear"])
def test_native_roll_reaction_balances_contact_and_steering_moments(side):
    vehicle = yaml.safe_load((ROOT / "vehicle.yml").read_text())
    reference = None
    for amplitude in (1000, 500, -1000):
        with contextlib.redirect_stdout(io.StringIO()):
            result = run(vehicle, "knc-" + side, {"kinematics_only": True, "forceMagnitude": amplitude})
        with (ROOT / result["csv"]).open() as stream:
            rows = [{k: float(v) for k, v in row.items() if k} for row in csv.DictReader(stream)]

        def at(time):
            return min(rows, key=lambda row: abs(row["time"] - time))

        def contact_moment(row):
            return sum(row[f"axle.{wheel}CP.r_0[2]"] * row[f"knc.{wheel}Fz"]
                       - row[f"axle.{wheel}CP.r_0[3]"] * row[f"{wheel}Load.worldForce.force[2]"]
                       for wheel in ("left", "right"))

        offset = 357 if side == "front" else 0
        curves = result["curves"]["curves"]
        for index, time in enumerate(range(64, 115, 5)):
            loaded, unloaded = at(offset + time), at(offset + time + 2)
            # Positive external world-X moment loads the fixture. The front
            # rack's grounded steering source is another external reaction path.
            contact_delta = contact_moment(loaded) - contact_moment(unloaded)
            steer_delta = loaded.get("steerPosition.flange.tau", 0) - unloaded.get("steerPosition.flange.tau", 0)
            measured = curves["roll_load_reaction_nm"][index]
            assert measured == pytest.approx(contact_delta - steer_delta, abs=1e-6)
            assert curves["roll_reaction_nm"][index] == pytest.approx(-loaded["chassisActuator.rollDOF.tau"])
            assert curves["roll_unloaded_reaction_nm"][index] == pytest.approx(-unloaded["chassisActuator.rollDOF.tau"])
        normalized = curves["roll_reaction_per_fy_m"]
        if reference is None:
            reference = normalized
        else:
            assert normalized == pytest.approx(reference, abs=1e-8)
        # At symmetric ride height, zero net jacking does not imply zero torque.
        assert abs(curves["roll_jacking_n"][5]) < 1e-6
        assert abs(curves["roll_load_reaction_nm"][5]) > 1
