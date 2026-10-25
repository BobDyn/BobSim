from pathlib import Path

import numpy as np
import pytest
import yaml

from app.visual import available_runs
from visualization.native_four_post import add_applied_forces, combine, geometry_filter, verify_replay


def test_capture_is_bound_to_original_vehicle_and_simulation(tmp_path: Path):
    directory = tmp_path / "visualization/results"
    directory.mkdir(parents=True)
    source = {"label": "Saved suspension", "simulation_id": "four-post", "vehicle_key": "original", "result_id": "run"}
    (directory / "capture.yml").write_text(yaml.safe_dump({"source": source}))
    np.savez(directory / "capture.npz", time=[0, 1])
    scene = available_runs(tmp_path)[0]
    assert all(scene[key] == value for key, value in source.items())


def test_replay_validation_checks_archived_measurements_and_event_times():
    original = {"time": np.array([0, 1, 1, 2]), "knc.heave": np.array([0, 0, 1, 2])}
    verify_replay(original, original)
    with pytest.raises(ValueError, match="differs"):
        verify_replay({**original, "knc.heave": np.array([0, 0, 2, 2])}, original)
    with pytest.raises(ValueError, match="omitted"):
        verify_replay({"time": original["time"]}, original)
    with pytest.raises(ValueError, match="complete"):
        verify_replay({"time": np.array([0, 1]), "knc.heave": np.array([0, 0])}, original)


def test_combined_animation_uses_report_traction_split_and_real_time():
    frames = {kind: {"time": np.array([0, 59, 60, 118]), "knc.heave": np.full(4, value),
                     "axle.leftCP.r_0[1]": np.full(4, value)}
              for kind, value in (("knc-front", 1), ("knc-rear", 2), ("knc-rear-traction", 3))}
    result = combine(frames)
    np.testing.assert_array_equal(result["time"], [0, 59, 60, 118])
    np.testing.assert_array_equal(result["rrKnC.heave"], [3, 3, 2, 2])
    np.testing.assert_array_equal(result["rrAxleDW.leftCP.r_0[1]"], [3, 3, 2, 2])
    np.testing.assert_array_equal(result["frKnC.heave"], [1, 1, 1, 1])
    assert "frKnC.heave" not in frames["knc-front"]


def test_filter_captures_physical_pickups_and_wheel_orientations():
    import re
    pattern = re.compile(geometry_filter())
    for name in ("time", "knc.leftGamma", "axle.leftWishboneUprightLoop.lowerForeRod.frame_a.r_0[1]",
                 "axle.rightBellcrank.pickupFrame2.r_0[3]", "axle.toLeftWheelCenter.frame_b.R.T[2,3]"):
        assert pattern.fullmatch(name), name
    assert not pattern.fullmatch("unrelated.signal")


def test_applied_vectors_preserve_sign_and_magnitude_without_reaction_substitution():
    columns = {"time": np.array([0., 1.])}
    for prefix in ("fr", "rr"):
        for side in ("left", "right"):
            columns[f"{prefix}.{side}Load.worldForce.force[1]"] = np.array([-100., 200.])
            columns[f"{prefix}.{side}Load.worldForce.force[2]"] = np.array([300., -400.])
    config = {"geometry": {}, "render": {}, "plots": []}
    signals = {}
    add_applied_forces(config, signals, columns)
    for corner, vector in config["geometry"]["vectors"]["applied_force"].items():
        assert vector["origin"] == corner + "_ContactPatch"
        values = np.array([signals[name] for name in vector["direction"]]).T
        np.testing.assert_allclose(values * vector["scale"], [[-.1, .3, 0], [.2, -.4, 0]])
    del columns["fr.leftLoad.worldForce.force[1]"]
    with pytest.raises(ValueError, match="omitted applied force"):
        add_applied_forces(config, {}, columns)
