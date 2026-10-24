"""Verify that the load-split controls excite independent native wheel forces."""
import contextlib
import csv
import io
import os

import pytest
import yaml

from app.native_runs import run
from common.native_artifacts import ROOT


@pytest.mark.skipif(os.environ.get("BOBSIM_NATIVE_INTEGRATION") != "1", reason="Requires native KnC binaries")
@pytest.mark.parametrize("side", ["front", "rear"])
def test_native_lateral_split_preserves_longitudinal_probe_and_superposes(side):
    vehicle = yaml.safe_load((ROOT / "vehicle.yml").read_text())
    responses = {}
    for share in (0, .5, .75, 1):
        with contextlib.redirect_stdout(io.StringIO()):
            result = run(vehicle, "knc-" + side, {"kinematics_only": True, "lateralLeftShare": share})
        with (ROOT / result["csv"]).open() as stream:
            rows = [{k: float(v) for k, v in row.items() if k} for row in csv.DictReader(stream)]
        offset = 357 if side == "front" else 0
        def at(time):
            return min(rows, key=lambda row: abs(row["time"] - time - offset))
        longitudinal = at(28)
        for wheel in ("left", "right"):
            assert longitudinal[f"{wheel}Load.worldForce.force[1]"] == pytest.approx(500, abs=1e-5)
        for time in range(64, 115, 5):
            loaded, unloaded = at(time), at(time + 2)
            for wheel, expected in (("left", 1000 * share), ("right", 1000 * (1 - share))):
                signal = f"{wheel}Load.worldForce.force[2]"
                assert loaded[signal] - unloaded[signal] == pytest.approx(expected, abs=1e-5)
        responses[share] = result["curves"]["curves"]["roll_force_rc_height_mm"]
    for share in (.5, .75):
        expected = [share * left + (1 - share) * right for left, right in zip(responses[1], responses[0])]
        assert responses[share] == pytest.approx(expected, abs=1e-6)
    with pytest.raises(ValueError, match="bound"):
        run(vehicle, "knc-" + side, {"lateralLeftShare": 1.1})
