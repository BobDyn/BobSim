from __future__ import annotations

import csv
from typing import cast

import numpy as np
import pytest
import yaml

from engines.dynpy import DOFModel, create_model, load_reduced_vehicle_parameters
from simulations.lap.core import (
    GGVMap,
    TrackCorridor,
    optimize_racing_line,
    simulate_transient_lap,
    solve_qss_lap,
)
from simulations.lap.lap_time_eval_sim import run_lap_time_evaluation


@pytest.fixture(scope="module")
def circular_corridor() -> TrackCorridor:
    angle = np.linspace(0.0, 2.0 * np.pi, 16, endpoint=False)
    inner_radius_m = 22.0
    outer_radius_m = 28.0
    left = np.column_stack(
        (inner_radius_m * np.cos(angle), inner_radius_m * np.sin(angle))
    )
    right = np.column_stack(
        (outer_radius_m * np.cos(angle), outer_radius_m * np.sin(angle))
    )
    return TrackCorridor(left, right)


@pytest.fixture(scope="module")
def synthetic_ggv() -> GGVMap:
    speed = np.array([2.0, 15.0, 30.0])
    ay = np.linspace(0.0, 8.0, 9)
    utilization = np.sqrt(np.maximum(1.0 - (ay / ay[-1]) ** 2, 0.0))
    acceleration = np.tile(4.0 * utilization, (speed.size, 1))
    braking = np.tile(-8.0 * utilization, (speed.size, 1))
    return GGVMap.from_arrays(speed, ay, acceleration, braking)


def test_track_corridor_builds_closed_clearance_constrained_line(
    circular_corridor: TrackCorridor,
) -> None:
    lower, upper = circular_corridor.offset_bounds(
        vehicle_width_m=1.5,
        safety_margin_m=0.25,
    )
    offsets = np.linspace(float(lower[0]), float(upper[0]), circular_corridor.gate_count)
    line = circular_corridor.line_from_offsets(offsets, sample_step_m=1.0)

    assert line.track_length_m > 100.0
    assert line.station_m[0] == 0.0
    assert np.all(line.segment_length_m > 0.0)
    assert np.sum(line.segment_length_m) == pytest.approx(line.track_length_m)
    assert np.all(line.gate_offsets_m >= lower)
    assert np.all(line.gate_offsets_m <= upper)
    projected_station = line.project_station_m(line.x_m[5], line.y_m[5])
    assert projected_station == pytest.approx(line.station_m[5], abs=1e-6)
    assert line.lateral_error_at_station(
        line.x_m[5],
        line.y_m[5],
        projected_station,
    ) == pytest.approx(0.0, abs=1e-9)


def test_synthetic_endurance_reference_has_mixed_curvature() -> None:
    corridor = TrackCorridor.from_csv(
        "simulations/lap/tracks/endurance_reference.csv"
    )
    line = corridor.line_from_offsets(np.zeros(corridor.gate_count), sample_step_m=1.0)

    assert 650.0 < line.track_length_m < 750.0
    assert np.min(corridor.gate_widths_m) == pytest.approx(5.0, abs=1e-6)
    assert np.min(line.curvature_per_m) < -0.05
    assert np.max(line.curvature_per_m) > 0.10
    assert np.count_nonzero(np.diff(np.sign(line.curvature_per_m))) >= 6


def test_michigan_2019_endurance_reference_has_full_course_scale() -> None:
    corridor = TrackCorridor.from_csv(
        "simulations/lap/tracks/endurance_michigan_2019.csv"
    )
    points = corridor.center_points_m
    closed = np.vstack((points, points[0]))
    polyline_length = float(np.sum(np.linalg.norm(np.diff(closed, axis=0), axis=1)))

    assert corridor.gate_count == 150
    assert 1_900.0 < polyline_length < 2_100.0
    assert np.min(corridor.gate_widths_m) > 1.65
    assert np.ptp(points[:, 0]) > 600.0
    assert np.ptp(points[:, 1]) > 250.0


def test_qss_profile_respects_gvv_acceleration_boundaries(
    circular_corridor: TrackCorridor,
    synthetic_ggv: GGVMap,
) -> None:
    line = circular_corridor.line_from_offsets(np.zeros(circular_corridor.gate_count))
    lap = solve_qss_lap(line, synthetic_ggv)

    assert lap.converged
    assert np.isfinite(lap.lap_time_s)
    assert lap.lap_time_s > 0.0
    for index, (speed, ax, ay) in enumerate(
        zip(
            lap.speed_mps,
            lap.longitudinal_acceleration_mps2,
            lap.lateral_acceleration_mps2,
        )
    ):
        assert abs(ay) <= synthetic_ggv.lateral_limit(float(speed)) + 1e-6
        if ax >= 0.0:
            limit = synthetic_ggv.longitudinal_limit(float(speed), abs(float(ay)), "drive")
            assert ax <= limit + 1e-6
        else:
            next_index = (index + 1) % lap.speed_mps.size
            limit = synthetic_ggv.longitudinal_limit(
                float(lap.speed_mps[next_index]),
                abs(float(lap.lateral_acceleration_mps2[next_index])),
                "brake",
            )
            assert ax >= limit - 1e-6


def test_minimum_time_line_keeps_best_qss_candidate(
    circular_corridor: TrackCorridor,
    synthetic_ggv: GGVMap,
) -> None:
    result = optimize_racing_line(
        circular_corridor,
        synthetic_ggv,
        mode="minimum_time_qss",
        vehicle_width_m=1.5,
        safety_margin_m=0.25,
        sample_step_m=2.0,
        curvature_max_iterations=3,
        lap_time_max_iterations=2,
    )

    assert result.qss_lap.converged
    assert result.qss_lap.lap_time_s <= result.minimum_curvature_lap_time_s + 1e-9
    assert result.centerline_lap_time_s > 0.0


@pytest.mark.parametrize("dof", (3, 6, 10, 14))
def test_forward_transient_executes_against_same_qss_reference(
    circular_corridor: TrackCorridor,
    synthetic_ggv: GGVMap,
    dof: int,
) -> None:
    line = circular_corridor.line_from_offsets(
        np.zeros(circular_corridor.gate_count),
        sample_step_m=2.0,
    )
    qss = solve_qss_lap(line, synthetic_ggv, max_speed_mps=12.0)
    model = create_model(cast(DOFModel, dof), load_reduced_vehicle_parameters())
    result = simulate_transient_lap(
        model,
        qss,
        sample_period_s=0.05,
        stop_time_s=0.1,
        steering_trim_step_m=20.0,
    )

    assert result.transient.success, result.transient.message
    assert result.qss_reference is qss
    assert result.transient.time_s[-1] == pytest.approx(0.1)
    assert result.unwrapped_progress_m[-1] > 0.0
    assert np.all(np.isfinite(result.lateral_error_m))


def test_lap_time_runner_writes_qss_artifacts(tmp_path) -> None:
    ggv_path = tmp_path / "ggv.csv"
    with ggv_path.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.writer(handle)
        writer.writerow(("speed_mps", "ay_mps2", "ax_accel_mps2", "ax_brake_mps2"))
        for speed in (2.0, 15.0, 30.0):
            for ay, accel, brake in ((-8.0, 0.0, 0.0), (0.0, 4.0, -8.0), (8.0, 0.0, 0.0)):
                writer.writerow((speed, ay, accel, brake))

    output_path = tmp_path / "results"
    config_path = tmp_path / "lap.yml"
    config_path.write_text(
        yaml.safe_dump(
            {
                "schema": "bobsim.lap-time.v1",
                "vehicle": "vehicle.yml",
                "model_dof": 3,
                "event": {"name": "endurance", "drive_power_limit_w": 32_000.0},
                "track": {
                    "boundary_csv": "simulations/lap/tracks/endurance_reference.csv",
                    "vehicle_width_m": 1.35,
                    "safety_margin_m": 0.15,
                    "sample_step_m": 2.0,
                },
                "racing_line": {"mode": "centerline"},
                "qss": {"ggv_csv": ggv_path.as_posix(), "generate_if_missing": False},
                "transient": {},
                "output": {"directory": output_path.as_posix()},
            }
        ),
        encoding="utf-8",
    )

    summary = run_lap_time_evaluation(config_path, scenario="qss")

    assert summary["model_dof"] == 3
    assert summary["effective_drive_power_limit_w"] == pytest.approx(32_000.0)
    assert summary["ggv_provenance"]["status"] == "supplied_unverified"
    assert not summary["study_scope"]["competition_points_supported"]
    assert summary["qss_converged"]
    assert summary["optimized_qss_lap_time_s"] > 0.0
    assert (output_path / "qss_lap.csv").is_file()
    assert (output_path / "summary.json").is_file()
    assert not (output_path / "transient_lap.csv").exists()
