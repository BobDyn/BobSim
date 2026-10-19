from __future__ import annotations

import hashlib
import json

import numpy as np
import pytest
import yaml

from app.tracks import import_track, track_payload
from simulations.lap.core.track import TrackCorridor
from simulations.lap.racing_line_sim import line_signature, load_line, run, vehicle_width_m


@pytest.fixture
def track_workspace(tmp_path):
    vehicle = {axle: {"suspension": {"wheel_center_m": [x, y, .2]}, "tire": {"template": axle}}
               for axle, x, y in [("front", 0., .6), ("rear", -1.5, .65)]}
    (tmp_path / "vehicle.yml").write_text(yaml.safe_dump(vehicle))
    tires = tmp_path / "common/tire_templates"
    tires.mkdir(parents=True)
    (tires / "front.tir").write_text("WIDTH = 0.21\n")
    (tires / "rear.tir").write_text("WIDTH = 0.19\n")
    angles = np.linspace(0., 2 * np.pi, 16, endpoint=False)
    points = np.column_stack((20*np.cos(angles), 20*np.sin(angles), 26*np.cos(angles), 26*np.sin(angles)))
    path = tmp_path / "track.csv"
    np.savetxt(path, points, delimiter=",", header="x1,y1,x2,y2", comments="")
    return tmp_path, vehicle, {"track": {"boundary_csv": "track.csv", "safety_margin_m": .15}, "mode": "centerline"}


def test_track_import_width_and_generation(track_workspace):
    root, vehicle, config = track_workspace
    assert vehicle_width_m(vehicle, root) == pytest.approx(1.49)
    imported = import_track(root, "test.csv", (root / "track.csv").read_text())
    assert imported["vehicle_width_m"] == pytest.approx(1.49)
    assert len(imported["left"]) > 16
    result = run(config, root)
    line = load_line(root / "app/user_data/results/racing-line/line.json")
    np.testing.assert_array_equal(line.x_m, result["line"]["x_m"])
    assert (root / "app/user_data/results/racing-line/report.pdf").is_file()
    assert result["signature"] == line_signature(config, root)
    config["mode"] = "minimum_curvature"
    assert run(config, root)["mode"] == "minimum_curvature"


@pytest.mark.parametrize("change", ["nan", "swapped", "duplicate", "header"])
def test_invalid_track_import_does_not_save(track_workspace, change):
    root, _, _ = track_workspace
    rows = (root / "track.csv").read_text().splitlines()
    if change == "header":
        rows[0] = "x,y"
    else:
        points = np.loadtxt(root / "track.csv", delimiter=",", skiprows=1)
        if change == "nan":
            points[1, 0] = np.nan
        if change == "swapped":
            points[3] = points[3, [2, 3, 0, 1]]
        if change == "duplicate":
            points[2] = points[1]
        rows = [rows[0], *(",".join(map(str, point)) for point in points)]
    with pytest.raises(ValueError):
        import_track(root, "test.csv", "\n".join(rows))
    assert not list((root / "app/user_data/config/tracks").glob("*.csv"))


def test_track_preview_rejects_path_escape(track_workspace):
    root, _, _ = track_workspace
    with pytest.raises(ValueError, match="workspace"):
        track_payload(root, "../track.csv")


def test_legacy_headers_and_repeated_closure(track_workspace):
    root, _, _ = track_workspace
    text = (root / "track.csv").read_text()
    text = text.replace("x1,y1,x2,y2", "left_x_m,left_y_m,right_x_m,right_y_m")
    (root / "track.csv").write_text(text + text.splitlines()[1] + "\n")
    assert TrackCorridor.from_csv(root / "track.csv").gate_count == 16


def test_racing_line_link_checks_inputs_and_result_integrity(track_workspace, monkeypatch):
    from app import data_services
    root, vehicle, config = track_workspace
    result = run(config, root)
    path = "app/user_data/results/racing-line/line.json"
    digest = hashlib.sha256((root / path).read_bytes()).hexdigest()
    source = {"id": "line", "name": "Line", "workflow_id": "racing-line", "config_text": yaml.safe_dump(config)}
    lap = {"racing_line_source_id": "line"}
    monkeypatch.setattr(data_services, "ROOT", root)
    monkeypatch.setattr(data_services, "_safe_repo_path", lambda p: root / p)
    monkeypatch.setattr(data_services, "saved_results_payload", lambda _: {"results": [{
        "id": "run", "simulation": {"id": "line"},
        "files": [{"label": "Racing line", "path": path, "sha256": digest}],
    }]})
    assert data_services._simulation_line_input(lap, [source], "vehicle")["status"] == "Ready"
    vehicle["rear"]["suspension"]["wheel_center_m"][1] += .1
    (root / "vehicle.yml").write_text(yaml.safe_dump(vehicle))
    assert data_services._simulation_line_input(lap, [source], "vehicle")["status"] == "Stale"
    result["line"]["x_m"][0] += 1.
    (root / path).write_text(json.dumps(result))
    assert data_services._simulation_line_input(lap, [source], "vehicle")["status"] == "Stale"
    assert data_services._simulation_line_input(lap, [], "vehicle")["status"] == "Unavailable"


def test_boundary_splines_interpolate_every_gate_and_close(track_workspace):
    root, _, _ = track_workspace
    corridor = TrackCorridor.from_csv(root / "track.csv")
    left, right = corridor.interpolated_boundaries(.5)
    for original, sampled in ((corridor.left_boundary_m, left), (corridor.right_boundary_m, right)):
        np.testing.assert_allclose(sampled[0], sampled[-1], atol=1e-12)
        distances = np.linalg.norm(original[:, None, :] - sampled[None, :, :], axis=2)
        np.testing.assert_allclose(distances.min(axis=1), 0., atol=1e-12)
        # A circular fixture distinguishes interpolation from straight gate segments.
        assert np.max(np.abs(np.linalg.norm(sampled, axis=1) - np.linalg.norm(original[0]))) < .003
    with pytest.raises(ValueError, match="positive and finite"):
        corridor.interpolated_boundaries(0.)
