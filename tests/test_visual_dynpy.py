"""Reduced replay uses archived states and the vehicle saved with the run."""

import json
from pathlib import Path

import numpy as np
import pytest
import yaml

from app import visual
from visualization.dynpy import build_scene
from engines.dynpy.parameters import _combine_mass_properties, _mass_components


@pytest.mark.parametrize("dof", [3, 6, 10, 14])
def test_reduced_scene_preserves_motion_and_fidelity(tmp_path, dof):
    vehicle = yaml.safe_load((Path(__file__).resolve().parents[1] / "vehicle.yml").read_text())
    signals = {"time": np.array([0., 1., 2.]), "x": np.array([0., 2., 4.]),
               "handwheelAngle": np.zeros(3), "y": np.zeros(3), "yaw": np.array([0., np.pi/2, np.pi]),
               "z": np.array([0., .02, .04]), "roll": np.zeros(3), "pitch": np.zeros(3)}
    for corner in ("FL", "FR", "RL", "RR"):
        signals.update({f"jounce{corner}": np.zeros(3), f"toe{corner}": np.zeros(3), f"camber{corner}": np.full(3, 0.1),
                        f"wheel_angle_{corner.lower()}": np.array([0., 2., 4.]),
                        f"unsprung_z_{corner.lower()}": np.array([0., .01, .02])})
        signals.update({f"wheelCenterOffset{axis}{corner}": np.zeros(3) for axis in "XYZ"})
    config, channels = build_scene(signals, vehicle, dof)
    assert f"{dof} DOF" in config["representation"]
    assert np.allclose(channels["body.x"], signals["x"])
    assert np.allclose(np.diff(channels["body.z"]), 0 if dof == 3 else .02)
    assert len(config["geometry"]["links"]["upper"]) == 8
    assert len(config["geometry"]["links"]["lower"]) == 8
    assert len(config["geometry"]["links"]["steering"]) == 4
    assert not any("mass_" in name or "spring" in name for name in config["geometry"]["points"])
    cg = np.asarray(_combine_mass_properties(_mass_components(vehicle))[1])
    for corner, side in (("fl", 1), ("fr", -1)):
        for name in ("upper_fore_i", "upper_aft_i", "lower_fore_i", "lower_aft_i", "lower_o", "upper_o", "tie_o"):
            # At zero body pose, stored hardpoints retain their ground-referenced height and lateral coordinate.
            expected = np.asarray(vehicle["front"]["suspension"][name + "_m"]) * [1, side, 1]
            assert channels[f"{corner}_{name}.y"][0] == pytest.approx(expected[1] - cg[1], abs=1e-8)
            assert channels[f"{corner}_{name}.z"][0] == pytest.approx(expected[2], abs=1e-8)
    tire = config["geometry"]["tires"]["fl"]
    assert ("spin" in tire) == (dof >= 10)
    assert channels["fl_y.z"][0] == pytest.approx(-np.sin(0.1))
    assert np.allclose(channels["fl_x.x"], [1, 0, -1], atol=1e-12)
    assert np.allclose(channels["fl_x.y"], [0, 1, 0], atol=1e-12)
    if dof == 14:
        assert np.allclose(channels["fl.z"], vehicle["front"]["suspension"]["wheel_center_m"][2]
                           + signals["unsprung_z_fl"])
    np.savez(tmp_path / "scene.npz", **channels)
    (tmp_path / "scene.yml").write_text(yaml.safe_dump(config))
    payload = visual.scene_payload(tmp_path / "scene.yml", tmp_path / "scene.npz")
    assert payload.header["frames"] == 3
    assert np.isfinite(np.frombuffer(payload.buffer, dtype=np.float32)).all()
    assert (payload.header["tires"][0]["spin_slot"] is not None) == (dof >= 10)
    (tmp_path / "vehicle.yml").write_text(yaml.safe_dump(vehicle))
    np.savetxt(tmp_path / "signals.csv", np.column_stack(list(signals.values())),
               delimiter=",", header=",".join(signals), comments="")
    archived = visual.reduced_scene_payload(tmp_path / "vehicle.yml", tmp_path / "signals.csv", dof)
    assert archived.header["representation"] == config["representation"]
    assert archived.buffer == payload.buffer
    signals["handwheelAngle"] = np.array([0., .02, .04])
    for index, corner in enumerate(("FL", "FR", "RL", "RR")):
        signals[f"jounce{corner}"] = np.array([0., .005, .01]) * (-1 if index % 2 else 1)
    signals["roll"] = np.array([0., .01, .02])
    signals["pitch"] = np.array([0., -.01, -.02])
    moving_config, moving = build_scene(signals, vehicle, dof)
    def position(name, values):
        return np.column_stack([values[f"{name}.{axis}"] for axis in "xyz"])
    for group in ("upper", "lower", "steering"):
        for start, end in moving_config["geometry"]["links"][group]:
            lengths = np.linalg.norm(position(end, moving) - position(start, moving), axis=1)
            assert np.allclose(lengths, lengths[0], atol=1e-8)
    assert not np.allclose(position("fl_upper_o", moving), position("fl_upper_o", channels))
    assert not np.allclose(position("fr_tie_o", moving), position("fr_tie_o", channels))
    del signals["yaw"]
    with pytest.raises(ValueError, match="yaw channel"):
        build_scene(signals, vehicle, dof)


def test_archived_replay_uses_snapshots_and_rejects_paths_outside_root(tmp_path):
    archive = tmp_path / "app/user_data/results/saved/run"
    archive.mkdir(parents=True)
    (archive / "signals.csv").write_text("time,x,y,yaw\n0,0,0,0\n1,1,0,0\n")
    (archive / "vehicle.yml").write_text("vehicle: {}")
    relative = archive.relative_to(tmp_path).as_posix()
    saved = {"id": "run", "label": "Step", "created_label": "Today", "vehicle_key": "car",
             "simulation": {"id": "step"}, "workflow": {"id": "reduced-step-steer"},
             "model": {"model_dofs": [6]}, "vehicle_snapshot": relative + "/vehicle.yml",
             "files": [{"label": "Signals", "path": relative + "/signals.csv"}]}
    manifest = archive / "manifest.json"
    manifest.write_text(json.dumps(saved))
    run = visual.available_runs(tmp_path)[0]
    assert run["config"] == saved["vehicle_snapshot"]
    assert run["data"] == saved["files"][0]["path"]
    assert run["simulation_id"] == "step"
    saved["vehicle_snapshot"] = "../outside.yml"
    manifest.write_text(json.dumps(saved))
    assert visual.available_runs(tmp_path) == []
