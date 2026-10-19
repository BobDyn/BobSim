from __future__ import annotations

import hashlib
import json

import numpy as np
import pytest
import yaml

from app.tracks import import_track, track_payload
from simulations.lap.core.track import TrackCorridor
from simulations.lap.racing_line_sim import line_signature, load_line, run, vehicle_wheelbase_m, vehicle_width_m


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


def test_uniform_gates_ignore_uneven_input_spacing():
    angles = 2 * np.pi * np.linspace(0., 1., 80, endpoint=False) ** 1.4
    direction = np.column_stack((np.cos(angles), np.sin(angles)))
    original = TrackCorridor(20. * direction, 26. * direction)
    gates = original.resampled_gates(1.3)
    assert gates.gate_count == int(np.ceil(2 * np.pi * 23 / 1.3))
    station_angles = np.unwrap(np.arctan2(gates.center_points_m[:, 1], gates.center_points_m[:, 0]))
    spacing = np.diff(np.r_[station_angles, 2 * np.pi]) * 23
    np.testing.assert_allclose(spacing, 2 * np.pi * 23 / gates.gate_count, atol=.001)
    np.testing.assert_allclose(gates.gate_widths_m, 6., atol=.001)
    np.testing.assert_allclose(np.linalg.norm(gates.left_boundary_m, axis=1), 20., atol=.001)
    assert gates.resampled_gates(.65).gate_count > gates.gate_count
    for invalid in (0., -1., np.nan, np.inf):
        with pytest.raises(ValueError, match="positive and finite"):
            original.resampled_gates(invalid)


def test_line_signature_tracks_gate_spacing_even_with_same_outer_width(track_workspace):
    root, vehicle, config = track_workspace
    previous = line_signature(config, root)
    vehicle["rear"]["suspension"]["wheel_center_m"][0] = -1.6
    (root / "vehicle.yml").write_text(yaml.safe_dump(vehicle))
    assert vehicle_width_m(vehicle, root) == pytest.approx(1.49)
    assert line_signature(config, root) != previous


def test_gate_spacing_uses_wheelbase(track_workspace):
    _, vehicle, _ = track_workspace
    assert vehicle_wheelbase_m(vehicle) == pytest.approx(1.5)
    vehicle["front"]["suspension"]["wheel_center_m"][0] = 10.
    vehicle["rear"]["suspension"]["wheel_center_m"][0] = 8.5
    assert vehicle_wheelbase_m(vehicle) == pytest.approx(1.5)
    for invalid in (10., float("nan"), float("inf")):
        vehicle["rear"]["suspension"]["wheel_center_m"][0] = invalid
        with pytest.raises(ValueError, match="Wheelbase"):
            vehicle_wheelbase_m(vehicle)


def test_lap_rejects_track_clearance_before_building_vehicle(track_workspace, monkeypatch):
    from simulations.lap import lap_time_eval_sim as lap

    root, _, config = track_workspace
    monkeypatch.setattr(lap, "repo_root", lambda: root)
    config["track"]["safety_margin_m"] = 4.
    path = root / "lap.yml"
    path.write_text(yaml.safe_dump(config))

    def unexpected_vehicle(*args, **kwargs):
        pytest.fail("Invalid track reached the dynamics model")

    monkeypatch.setattr(lap.Vehicle, "from_yaml", unexpected_vehicle)
    with pytest.raises(ValueError, match="Track gate .* require"):
        lap.run_lap_time_evaluation(path, scenario="qss")


def test_michigan_boundary_width_and_cones_survive_interpolation():
    from common.vehicle_io import repo_root

    track = TrackCorridor.from_csv(repo_root() / 'simulations/lap/tracks/endurance_michigan_2019.csv')
    left, right = track.interpolated_boundaries(.2)
    assert np.linalg.norm(left - right, axis=1).min() >= track.gate_widths_m.min() - .01
    assert np.linalg.norm(left - right, axis=1).max() <= track.gate_widths_m.max() + .01
    for cones, boundary in ((track.left_boundary_m, left), (track.right_boundary_m, right)):
        assert max(min(np.linalg.norm(boundary - cone, axis=1)) for cone in cones) < 1e-10
    TrackCorridor(left[:-1], right[:-1]).validate_order()
    rows, parameters, splines = track._boundary_splines()
    samples = np.linspace(0., track.gate_count, 10001)
    interpolated = [spline(np.interp(samples, rows, parameter))
                    for spline, parameter in zip(splines, parameters)]
    segments = [np.column_stack([np.interp(samples, np.arange(track.gate_count + 1),
                                         np.r_[cones[:, axis], cones[0, axis]]) for axis in (0, 1)])
                for cones in (track.left_boundary_m, track.right_boundary_m)]
    loss = np.linalg.norm(segments[0] - segments[1], axis=1) \
        - np.linalg.norm(interpolated[0] - interpolated[1], axis=1)
    assert loss.max() <= .010001
    gates = track.resampled_gates(1.5494)
    gates.offset_bounds(vehicle_width_m=1.40272, safety_margin_m=.15)
    with pytest.raises(ValueError, match='require'):
        gates.offset_bounds(vehicle_width_m=3., safety_margin_m=.15)


def test_boundary_width_constraint_is_independent_of_coordinate_frame():
    from common.vehicle_io import repo_root

    track = TrackCorridor.from_csv(repo_root() / 'simulations/lap/tracks/endurance_michigan_2019.csv')
    angle = .73
    rotation = np.array([[np.cos(angle), -np.sin(angle)], [np.sin(angle), np.cos(angle)]])
    shift = np.array([137., -49.])
    moved = TrackCorridor(track.left_boundary_m @ rotation + shift, track.right_boundary_m @ rotation + shift)
    for reference, transformed in zip(track.interpolated_boundaries(.5), moved.interpolated_boundaries(.5)):
        np.testing.assert_allclose(transformed, reference @ rotation + shift, atol=1e-9)
