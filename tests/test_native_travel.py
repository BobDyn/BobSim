"""Travel poses must constrain native geometry without editing calibration."""
import copy
import math
import os

import pytest
import yaml

from app.native_travel import point_frames, travel_payload
from common.native_artifacts import ROOT


@pytest.mark.parametrize("pose", [None, {}, {"heave_mm": math.nan, "roll_deg": 0, "steer_deg": 0},
                                  {"heave_mm": 0, "roll_deg": 2, "steer_deg": 0},
                                  {"heave_mm": True, "roll_deg": 0, "steer_deg": 0}])
def test_invalid_pose_rejected_before_native_run(pose):
    with pytest.raises((ValueError, TypeError)):
        travel_payload({}, pose)


def test_direct_and_bellcrank_use_connected_rod_frames():
    direct = point_frames("front", "direct")
    bellcrank = point_frames("front", "bellcrank_stabar")
    assert direct["front-left-rod"] == "axle.leftShockLinkage.frame_a.r_0"
    assert bellcrank["front-left-rod"] == "axle.leftPushrod.frame_b.r_0"
    assert bellcrank["front-right-bellcrank-rod"] == "axle.rightBellcrank.pickupFrame1.r_0"
    assert not any("bellcrank" in key for key in direct)


@pytest.mark.skipif(os.environ.get("BOBSIM_NATIVE_INTEGRATION") != "1", reason="Requires cached native binaries")
def test_native_combined_travel_preserves_links_and_calibration():
    vehicle = yaml.safe_load((ROOT / "vehicle.yml").read_text())
    original = copy.deepcopy(vehicle)
    neutral = dict(heave_mm=0, roll_deg=0, steer_deg=0)
    base = travel_payload(vehicle, neutral)
    for sign in (-1, 1):
        pose = dict(heave_mm=sign * 38.1, roll_deg=sign * 1.25, steer_deg=sign * 90)
        moved = travel_payload(vehicle, pose)
        for axle in ("front", "rear"):
            for side in ("left", "right"):
                prefix = f"{axle}-{side}-"
                for a, b in (("lower-fore-i", "lower-o"), ("upper-aft-i", "upper-o"),
                             ("rack", "tie-o"), ("rod", "bellcrank-rod")):
                    before = math.dist(base["points"][prefix + a], base["points"][prefix + b])
                    after = math.dist(moved["points"][prefix + a], moved["points"][prefix + b])
                    assert after == pytest.approx(before, abs=1e-7)
        assert moved["points"]["front-left-upper-o"] != base["points"]["front-left-upper-o"]
    steered = travel_payload(vehicle, {**neutral, "steer_deg": 30})
    for key, point in base["points"].items():
        if key.startswith("rear-"):
            assert steered["points"][key] == point
    assert travel_payload(vehicle, neutral) == base
    assert vehicle == original


def test_travel_editor_request_lifecycle():
    import shutil
    import subprocess

    node = shutil.which("node")
    if not node:
        pytest.skip("Node is required for editor behavior checks")
    subprocess.run([node, "tests/app_travel.cjs"], cwd=ROOT, check=True, timeout=20)
