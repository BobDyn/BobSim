from __future__ import annotations

import csv
from pathlib import Path

import numpy as np
import pytest
import yaml

from simulations.response.mbd.four_post import four_post_eval_sim as four_post_eval
from engines.kinpy import (
    KINEMATIC_CURVE_META,
    CornerKinematics,
    create_kinematics,
    kinematic_curves_payload,
)


ROOT = Path(__file__).resolve().parents[1]
INCH_TO_M = 0.0254


def test_kinematics_model_lives_in_shared_suspension_package() -> None:
    assert CornerKinematics.__module__ == "engines.kinpy.kinematics"
    assert kinematic_curves_payload.__module__ == "engines.kinpy.kinematics"


def test_precomputed_vehicle_kinematics_matches_in_loop_nonlinear_solution() -> None:
    vehicle = yaml.safe_load((ROOT / "vehicle.yml").read_text(encoding="utf-8"))
    lookup = create_kinematics(vehicle, sample_count=17)
    nonlinear = create_kinematics(vehicle, mode="nonlinear")
    jounce = np.array([-0.021, -0.007, 0.014, 0.031])

    interpolated = lookup.at(jounce)
    exact = nonlinear.at(jounce)

    np.testing.assert_array_equal(interpolated.jounce_m, jounce)
    np.testing.assert_array_equal(exact.jounce_m, jounce)
    np.testing.assert_allclose(
        interpolated.contact_patch_offsets_m,
        exact.contact_patch_offsets_m,
        atol=25e-6,
    )
    np.testing.assert_allclose(interpolated.camber_rad, exact.camber_rad, atol=3e-5)
    np.testing.assert_allclose(interpolated.toe_rad, exact.toe_rad, atol=2e-5)
    np.testing.assert_allclose(
        interpolated.instant_links.coefficient_matrix,
        exact.instant_links.coefficient_matrix,
        atol=6e-5,
    )


def test_vehicle_kinematic_state_mirrors_right_corner_geometry() -> None:
    vehicle = yaml.safe_load((ROOT / "vehicle.yml").read_text(encoding="utf-8"))
    state = create_kinematics(vehicle, sample_count=17).at(np.array([0.02, 0.02, -0.015, -0.015]))

    np.testing.assert_allclose(
        state.contact_patch_offsets_m[0, [0, 2]],
        state.contact_patch_offsets_m[1, [0, 2]],
    )
    assert state.contact_patch_offsets_m[0, 1] == pytest.approx(-state.contact_patch_offsets_m[1, 1])
    assert state.toe_rad[0] == pytest.approx(-state.toe_rad[1])
    assert state.camber_rad[2] == pytest.approx(-state.camber_rad[3])


def _direct_quarter_car_vehicle() -> dict[str, object]:
    radius = 16.0 * 0.0254 / 2.0
    corner = {
        "wheel": {"radius_m": radius, "toe_deg": 0.0, "camber_deg": 0.0},
        "suspension": {
            "lower_fore_i_m": [2.0, 0.0, 0.5],
            "lower_aft_i_m": [0.0, 0.0, 0.5],
            "lower_o_m": [1.0, 2.0, 0.5],
            "upper_fore_i_m": [2.0, 0.0, 1.5],
            "upper_aft_i_m": [0.0, 0.0, 1.5],
            "upper_o_m": [1.0, 2.0, 1.5],
            "tie_o_m": [2.0, 2.0, 1.0],
            "wheel_center_m": [1.0, 2.5, radius],
        },
        "steering": {"rack_pickup_m": [2.0, 0.0, 0.5]},
    }
    return {"front": corner, "rear": corner}


def _simulation_toolkit_unit_test_vehicle() -> dict[str, object]:
    radius = 0.4064 / 2.0

    def wheel_center(contact_patch: list[float], camber_deg: float) -> list[float]:
        camber_rad = np.radians(camber_deg)
        return (
            np.asarray(contact_patch, dtype=float)
            + np.array([0.0, radius * np.sin(camber_rad), radius * np.cos(camber_rad)])
        ).tolist()

    return {
        "front": {
            "wheel": {"radius_m": radius, "toe_deg": 0.0, "camber_deg": -1.0},
            "suspension": {
                "lower_fore_i_m": [0.087376, 0.215900, 0.090000],
                "lower_aft_i_m": [-0.095250, 0.215900, 0.090000],
                "lower_o_m": [0.0, 0.556499, 0.124998],
                "upper_fore_i_m": [0.086868, 0.215900, 0.200000],
                "upper_aft_i_m": [-0.095250, 0.215900, 0.200000],
                "upper_o_m": [-0.006347, 0.523240, 0.287020],
                "tie_o_m": [0.056000, 0.532333, 0.164821],
                "wheel_center_m": wheel_center([0.0, 0.609600, 0.0], -1.0),
            },
            "steering": {"rack_pickup_m": [0.041128, 0.215900, 0.117856]},
        },
        "rear": {
            "wheel": {"radius_m": radius, "toe_deg": 0.0, "camber_deg": 0.0},
            "suspension": {
                "lower_fore_i_m": [-1.298905, 0.282999, 0.090000],
                "lower_aft_i_m": [-1.490977, 0.282999, 0.090000],
                "lower_o_m": [-1.554983, 0.579999, 0.113030],
                "upper_fore_i_m": [-1.298905, 0.282999, 0.217500],
                "upper_aft_i_m": [-1.490977, 0.282999, 0.217500],
                "upper_o_m": [-1.574797, 0.554998, 0.289560],
                "tie_o_m": [-1.462710, 0.587375, 0.240741],
                "wheel_center_m": wheel_center([-1.5494, 0.609600, 0.0], 0.0),
            },
            "steering": {"rack_pickup_m": [-1.428059, 0.282999, 0.177800]},
        },
    }


def _four_post_unit_vehicle() -> dict[str, object]:
    vehicle = _simulation_toolkit_unit_test_vehicle()
    vehicle.update(
        {
            "sprung_mass": {"mass_kg": 300.0, "cg_m": [-0.75, 0.0, 0.35]},
            "driver_mass": {"mass_kg": 0.0, "cg_m": [0.0, 0.0, 0.0]},
        }
    )
    for side in (vehicle["front"], vehicle["rear"]):
        assert isinstance(side, dict)
        side["actuation"] = {
            "shock": {
                "mount_m": [0.0, 0.0, 0.5],
                "spring_table": {
                    "table": [
                        [-0.05, -1000.0],
                        [0.0, 0.0],
                        [0.05, 1000.0],
                    ]
                },
                "free_length_m": 0.25,
            },
            "rod_mount_m": [0.0, 0.0, 0.25],
            "stabar": {"rate_n_m_per_rad": 0.0},
        }
        side["masses"] = {
            "unsprung": {"mass_kg": 8.0},
            "upper_control_arm": {"mass_kg": 0.5},
            "lower_control_arm": {"mass_kg": 0.5},
            "tie_rod": {"mass_kg": 0.2},
        }
        side["tire"] = {"vertical_stiffness_n_per_m": 200000.0}
    return vehicle


def _four_post_unit_config(tmp_path: Path) -> dict[str, object]:
    return {
        "model_overrides": {
            "suspension": {
                "front": {
                    "spring_rate_n_per_m": 20000.0,
                    "stabar_rate_n_m_per_rad": 0.0,
                },
                "rear": {
                    "spring_rate_n_per_m": 20000.0,
                    "stabar_rate_n_m_per_rad": 0.0,
                },
            },
        },
        "report": {"metrics_csv_path": str(tmp_path / "missing_metrics.csv")},
    }


def _pose_sample_times(start_s: float, count: int) -> list[float]:
    return [start_s + four_post_eval.FOUR_POST_POSE_STEP_S * index + 4.0 for index in range(count)]


def _jack_times(start_s: float, count: int) -> list[float]:
    return [start_s + four_post_eval.FOUR_POST_POSE_STEP_S * index + 1.5 for index in range(count)]


def _four_post_result_from_kinematics(
    vehicle: dict[str, object],
    heave_sweep_m: np.ndarray,
    roll_sweep_deg: np.ndarray,
) -> dict[str, np.ndarray]:
    heave_times = _pose_sample_times(
        four_post_eval.FOUR_POST_HEAVE_START_S,
        four_post_eval.FOUR_POST_HEAVE_POSE_COUNT,
    )
    roll_times = _pose_sample_times(
        four_post_eval.FOUR_POST_ROLL_START_S,
        four_post_eval.FOUR_POST_ROLL_POSE_COUNT,
    )
    heave_jack_times = _jack_times(
        four_post_eval.FOUR_POST_HEAVE_START_S,
        four_post_eval.FOUR_POST_HEAVE_POSE_COUNT,
    )
    roll_jack_times = _jack_times(
        four_post_eval.FOUR_POST_ROLL_START_S,
        four_post_eval.FOUR_POST_ROLL_POSE_COUNT,
    )
    times = sorted(heave_times + roll_times + heave_jack_times + roll_jack_times)
    index_by_time = {time: index for index, time in enumerate(times)}
    result: dict[str, np.ndarray] = {"time": np.asarray(times, dtype=float)}

    for prefix in ("frKnC", "rrKnC"):
        for name in ("heave", "roll", "fx", "fy", "jackingForce", "stabarAngle"):
            result[f"{prefix}.{name}"] = np.zeros(len(times), dtype=float)
        for side in ("left", "right"):
            for name in (
                "SpringLength",
                "Fz",
                "Gamma",
                "Toe",
                "Caster",
                "Kpi",
                "MechTrail",
                "MechScrub",
            ):
                result[f"{prefix}.{side}{name}"] = np.zeros(len(times), dtype=float)

    heave_by_pose = np.asarray(heave_sweep_m[::-1], dtype=float)
    roll_by_pose_rad = np.radians(np.asarray(roll_sweep_deg[::-1], dtype=float))
    solvers = {
        "front": CornerKinematics.from_vehicle(vehicle, "front"),
        "rear": CornerKinematics.from_vehicle(vehicle, "rear"),
    }
    prefixes = {"front": "frKnC", "rear": "rrKnC"}
    guesses = {axle: np.zeros(3) for axle in solvers}
    roll_guesses = {axle: np.zeros(3) for axle in solvers}

    def write_axis(prefix: str, time: float, *, heave: float = 0.0, roll: float = 0.0) -> None:
        index = index_by_time[time]
        result[f"{prefix}.heave"][index] = -heave
        result[f"{prefix}.roll"][index] = roll

    def write_corner(
        prefix: str,
        time: float,
        values: dict[str, float | None],
        *,
        jounce_m: float,
        load_delta_n: float = 0.0,
    ) -> None:
        index = index_by_time[time]
        assert values["camber_deg"] is not None
        assert values["toe_deg"] is not None
        assert values["caster_deg"] is not None
        assert values["kpi_deg"] is not None
        assert values["mech_trail_mm"] is not None
        assert values["scrub_mm"] is not None
        raw_values = {
            "Gamma": -np.radians(float(values["camber_deg"])),
            "Toe": np.radians(float(values["toe_deg"])),
            "Caster": np.radians(float(values["caster_deg"])),
            "Kpi": np.radians(float(values["kpi_deg"])),
            "MechTrail": float(values["mech_trail_mm"]) / 1000.0,
            "MechScrub": float(values["scrub_mm"]) / 1000.0,
        }
        for side_name, load_sign in (("left", 1.0), ("right", -1.0)):
            result[f"{prefix}.{side_name}SpringLength"][index] = 0.25 - 0.5 * jounce_m
            result[f"{prefix}.{side_name}Fz"][index] = 1000.0 + load_sign * load_delta_n
            for signal, value in raw_values.items():
                result[f"{prefix}.{side_name}{signal}"][index] = value

    for time, jounce in zip(heave_times, heave_by_pose, strict=True):
        for axle, solver in solvers.items():
            prefix = prefixes[axle]
            solution, point_set, residual_norm = solver.solve_jounce(jounce, guesses[axle])
            guesses[axle] = solution
            values = solver.curve_values(point_set, solution, residual_norm)
            write_axis(prefix, time, heave=jounce)
            write_corner(prefix, time, values, jounce_m=jounce)

    for time, roll_rad in zip(roll_times, roll_by_pose_rad, strict=True):
        roll_deg = float(np.degrees(roll_rad))
        for axle, solver in solvers.items():
            prefix = prefixes[axle]
            right_jounce = solver.roll_jounce_m(roll_deg)
            solution, point_set, residual_norm = solver.solve_jounce(right_jounce, roll_guesses[axle])
            roll_guesses[axle] = solution
            values = solver.curve_values(point_set, solution, residual_norm)
            write_axis(prefix, time, roll=roll_rad)
            write_corner(
                prefix,
                time,
                values,
                jounce_m=right_jounce,
                load_delta_n=100.0 * roll_rad,
            )
            result[f"{prefix}.stabarAngle"][index_by_time[time]] = 0.25 * roll_rad

    for time, jounce in zip(heave_jack_times, heave_by_pose, strict=True):
        for prefix in prefixes.values():
            write_axis(prefix, time, heave=jounce)
            result[f"{prefix}.fx"][index_by_time[time]] = 1000.0

    for time, roll_rad in zip(roll_jack_times, roll_by_pose_rad, strict=True):
        for prefix in prefixes.values():
            write_axis(prefix, time, roll=roll_rad)
            result[f"{prefix}.fy"][index_by_time[time]] = 1000.0
            result[f"{prefix}.leftFz"][index_by_time[time]] = 1000.0
            result[f"{prefix}.rightFz"][index_by_time[time]] = 1000.0

    return result


@pytest.mark.parametrize(
    ("jounce_m", "rack_m", "expected"),
    (
        (
            0.25,
            0.0,
            {
                "angles_deg": [7.18076, 7.18076, -3.67105],
                "contact_patch": [1.0320141, 2.4832875, 0.25],
                "tie_o": [1.9979481, 1.9202853, 1.25],
            },
        ),
        (
            -0.5,
            -0.25,
            {
                "angles_deg": [-14.47751, -14.47751, -7.17809],
                "contact_patch": [1.0624769, 2.4325730, -0.5],
                "tie_o": [1.9921626, 1.8115379, 0.5],
            },
        ),
        (
            0.5,
            -0.15,
            {
                "angles_deg": [14.47751, 14.47751, -16.51029],
                "contact_patch": [1.1420938, 2.4158760, 0.5],
                "tie_o": [1.9587687, 1.6523041, 1.5],
            },
        ),
        (
            -0.3,
            -0.05,
            {
                "angles_deg": [-8.62693, -8.62693, 1.40139],
                "contact_patch": [0.9877718, 2.4772224, -0.3],
                "tie_o": [1.9997009, 2.0018284, 0.7],
            },
        ),
        (
            -0.3,
            0.15,
            {
                "angles_deg": [-8.62693, -8.62693, 12.96162],
                "contact_patch": [0.8878510, 2.4646320, -0.3],
                "tie_o": [1.9745210, 2.2016700, 0.7],
            },
        ),
        (
            -0.1,
            0.25,
            {
                "angles_deg": [-2.86598, -2.86598, 15.93291],
                "contact_patch": [0.8627440, 2.4782900, -0.1],
                "tie_o": [1.9615840, 2.2720100, 0.9],
            },
        ),
    ),
)
def test_corner_kinematics_matches_simulation_toolkit_direct_quarter_car(
    jounce_m: float,
    rack_m: float,
    expected: dict[str, list[float]],
) -> None:
    solver = CornerKinematics.from_vehicle(_direct_quarter_car_vehicle(), "front")

    solution, point_set, residual_norm = solver.solve_jounce(
        jounce_m,
        np.array([0.0, 0.0, 0.0]),
        rack_displacement_m=rack_m,
    )

    assert residual_norm <= 1e-8
    assert np.degrees(solution) == pytest.approx(expected["angles_deg"], abs=0.01)
    assert point_set.contact_patch.tolist() == pytest.approx(expected["contact_patch"], abs=3e-6)
    assert point_set.tie_o.tolist() == pytest.approx(expected["tie_o"], abs=3e-6)


@pytest.mark.parametrize(
    ("axle", "expected"),
    (
        (
            "front",
            {
                "camber_deg": -1.0,
                "toe_deg": 0.0,
                "caster_deg": 2.2435,
                "kpi_deg": 11.6002,
                "scrub_mm": 1.0804 * 25.4,
                "mech_trail_mm": 0.1928 * 25.4,
                "front_ic_y_mm": -15.5082 * 25.4,
                "front_ic_z_mm": 1.0763 * 25.4,
            },
        ),
        (
            "rear",
            {
                "camber_deg": 0.0,
                "toe_deg": 0.0,
                "caster_deg": 6.4043,
                "kpi_deg": 8.0610,
                "scrub_mm": 0.5352 * 25.4,
                "mech_trail_mm": 0.2797 * 25.4,
                "front_ic_y_mm": -15.6465 * 25.4,
                "front_ic_z_mm": 1.4661 * 25.4,
            },
        ),
    ),
)
def test_static_outputs_match_simulation_toolkit_unit_vehicle(
    axle: str,
    expected: dict[str, float],
) -> None:
    solver = CornerKinematics.from_vehicle(_simulation_toolkit_unit_test_vehicle(), axle)
    values = solver.curve_values(solver.initial_point_set(), np.zeros(3), 0.0)

    assert values["camber_deg"] == pytest.approx(expected["camber_deg"], abs=0.01)
    assert values["toe_deg"] == pytest.approx(expected["toe_deg"], abs=0.01)
    assert values["caster_deg"] == pytest.approx(expected["caster_deg"], abs=0.01)
    assert values["kpi_deg"] == pytest.approx(expected["kpi_deg"], abs=0.01)
    assert values["scrub_mm"] == pytest.approx(expected["scrub_mm"], abs=0.02)
    assert values["mech_trail_mm"] == pytest.approx(expected["mech_trail_mm"], abs=0.02)
    assert values["front_ic_y_mm"] == pytest.approx(expected["front_ic_y_mm"], abs=0.02)
    assert values["front_ic_z_mm"] == pytest.approx(expected["front_ic_z_mm"], abs=0.02)


@pytest.mark.parametrize(
    ("jounce_in", "expected"),
    (
        (
            0.5,
            {
                "front": {
                    "camber_deg": -1.7341,
                    "caster_deg": 2.2496,
                    "kpi_deg": 12.3343,
                },
                "rear": {
                    "camber_deg": -0.7327,
                    "caster_deg": 6.4164,
                    "kpi_deg": 8.7936,
                },
            },
        ),
        (
            1.0,
            {
                "front": {
                    "camber_deg": -2.4826,
                    "caster_deg": 2.2562,
                    "kpi_deg": 13.0828,
                },
                "rear": {
                    "camber_deg": -1.4827,
                    "caster_deg": 6.4298,
                    "kpi_deg": 9.5436,
                },
            },
        ),
        (
            -1.0,
            {
                "front": {
                    "camber_deg": 0.4331,
                    "caster_deg": 2.2328,
                    "kpi_deg": 10.1670,
                },
                "rear": {"camber_deg": 1.4257, "caster_deg": 6.3840, "kpi_deg": 6.6353},
            },
        ),
        (
            -0.5,
            {
                "front": {
                    "camber_deg": -0.2782,
                    "caster_deg": 2.2379,
                    "kpi_deg": 10.8784,
                },
                "rear": {"camber_deg": 0.7185, "caster_deg": 6.3936, "kpi_deg": 7.3425},
            },
        ),
    ),
)
def test_bump_outputs_match_simulation_toolkit_unit_vehicle(
    jounce_in: float,
    expected: dict[str, dict[str, float]],
) -> None:
    vehicle = _simulation_toolkit_unit_test_vehicle()

    for axle in ("front", "rear"):
        solver = CornerKinematics.from_vehicle(vehicle, axle)
        solution, point_set, residual_norm = solver.solve_jounce(jounce_in * INCH_TO_M, np.zeros(3))
        values = solver.curve_values(point_set, solution, residual_norm)

        assert residual_norm <= 1e-8
        assert values["toe_deg"] == pytest.approx(0.0, abs=0.1)
        assert values["camber_deg"] == pytest.approx(expected[axle]["camber_deg"], abs=0.01)
        assert values["caster_deg"] == pytest.approx(expected[axle]["caster_deg"], abs=0.01)
        assert values["kpi_deg"] == pytest.approx(expected[axle]["kpi_deg"], abs=0.01)


def test_corner_kinematics_payload_reports_complete_active_vehicle_sweep() -> None:
    vehicle = yaml.safe_load((ROOT / "vehicle.yml").read_text(encoding="utf-8"))
    payload = kinematic_curves_payload(vehicle)

    assert payload["available"] is True
    assert payload["warnings"] == []
    assert payload["axles"]["front"]["ok"] is True
    assert payload["axles"]["rear"]["ok"] is True
    assert len(payload["sweep_m"]) == 21
    assert len(payload["roll_deg"]) == 21
    assert len(payload["steer_m"]) == 21
    assert len(payload["curve_meta"]) == len(KINEMATIC_CURVE_META)
    # Pin the absolute count. A bad merge once dropped ten curves from the registry.
    assert len(payload["curve_meta"]) == 35
    published = {item["id"] for item in payload["curve_meta"]}
    assert {
        "bump_front_ic_y_mm", "bump_front_ic_z_mm", "bump_front_swing_arm_mm",
        "bump_rc_height_mm", "bump_rc_migration_mm",
        "roll_front_ic_y_mm", "roll_front_ic_z_mm", "roll_front_swing_arm_mm",
        "roll_rc_height_mm", "roll_rc_migration_mm",
        "steer_camber_deg", "steer_scrub_mm", "steer_mech_trail_mm",
        "steer_rc_y_mm", "steer_rc_z_mm", "steer_kpi_deg", "steer_caster_deg",
    } <= published
    # Instant-centre and roll-centre curves come after the original sixteen.
    assert [item["source_plot"] for item in payload["curve_meta"]][:16] == [
        "Plot1",
        "Plot2",
        "Plot3",
        "Plot4",
        "Plot5",
        "Plot6",
        "Plot11",
        "Plot12",
        "Plot15",
        "Plot16",
        "Plot17",
        "Plot18",
        "Plot19",
        "Plot20",
        "Plot25",
        "Plot26",
    ]
    assert all("side_ic" not in item["id"] for item in payload["curve_meta"])
    front_curves = payload["axles"]["front"]["curves"]
    axis_lengths = {
        "jounce_mm": len(payload["x_axes"]["jounce_mm"]),
        "roll_deg": len(payload["x_axes"]["roll_deg"]),
        "rack_mm": len(payload["x_axes"]["rack_mm"]),
    }
    for item in KINEMATIC_CURVE_META:
        key = item["id"]
        assert len(front_curves[key]) == axis_lengths[item["x_id"]]
    # Front rack motion leaves the rear geometry unchanged.
    rear_curves = payload["axles"]["rear"]["curves"]
    nominal_index = payload["x_axes"]["jounce_mm"].index(0.0)
    for item in KINEMATIC_CURVE_META:
        if item["id"].startswith("steer_"):
            nominal = rear_curves[item["id"].replace("steer_", "bump_")][nominal_index]
            assert rear_curves[item["id"]] == [nominal] * axis_lengths["rack_mm"]
    assert payload["x_axes"]["rack_mm"] == pytest.approx([1000 * value for value in payload["steer_m"]])
    for axis in payload["x_axes"].values():
        assert 0.0 in axis
    for key in (
        "bump_camber_deg",
        "bump_toe_deg",
        "bump_rc_z_mm",
        "roll_camber_deg",
        "roll_toe_deg",
        "roll_rc_z_mm",
    ):
        assert any(value is not None for value in front_curves[key])


def test_four_post_kinematic_curves_match_unit_validated_frontend_calcs(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    vehicle = _four_post_unit_vehicle()
    monkeypatch.setattr(four_post_eval, "_load_active_vehicle_yaml", lambda: vehicle)

    heave_sweep = np.linspace(
        -0.03,
        0.03,
        four_post_eval.FOUR_POST_HEAVE_POSE_COUNT,
    )
    roll_sweep_deg = np.linspace(
        -1.25,
        1.25,
        four_post_eval.FOUR_POST_ROLL_POSE_COUNT,
    )
    summary, series = four_post_eval.FourPostEvalSim(_four_post_unit_config(tmp_path)).summarize(
        _four_post_result_from_kinematics(vehicle, heave_sweep, roll_sweep_deg)
    )

    payload = kinematic_curves_payload(vehicle, sweep_m=heave_sweep.tolist())
    assert payload["available"] is True
    assert payload["warnings"] == []
    np.testing.assert_allclose(series["heave"], heave_sweep)
    np.testing.assert_allclose(series["roll"], np.radians(roll_sweep_deg))

    expected_sweeps = {
        axle: CornerKinematics.from_vehicle(vehicle, axle).solve_sweep(
            tuple(float(value) for value in heave_sweep),
            tuple(float(value) for value in roll_sweep_deg),
        )
        for axle in ("front", "rear")
    }
    curve_specs = (
        ("camber", "deg", -1.0),
        ("toe", "deg", 1.0),
        ("caster", "deg", 1.0),
        ("kpi", "deg", 1.0),
        ("mech_trail", "mm", 1.0),
        ("scrub", "mm", 1.0),
    )

    for axle, corner_prefix in (("front", "fr_l"), ("rear", "rr_l")):
        payload_curves = payload["axles"][axle]["curves"]
        expected_curves = expected_sweeps[axle]["curves"]
        for curve_name, unit, sign in curve_specs:
            heave_key = f"bump_{curve_name}_{unit}"
            roll_key = f"roll_{curve_name}_{unit}"
            four_post_name = {
                "mech_trail": "trail",
                "scrub": "scrub",
            }.get(curve_name, curve_name)
            if unit == "deg":
                expected_heave = sign * np.radians(np.asarray(payload_curves[heave_key], dtype=float))
                expected_roll = sign * np.radians(np.asarray(expected_curves[roll_key], dtype=float))
            else:
                expected_heave = sign * np.asarray(payload_curves[heave_key], dtype=float) / 1000.0
                expected_roll = sign * np.asarray(expected_curves[roll_key], dtype=float) / 1000.0

            np.testing.assert_allclose(
                series[f"{corner_prefix}_{four_post_name}_vs_heave"],
                expected_heave,
                atol=1e-8,
            )
            np.testing.assert_allclose(
                series[f"{corner_prefix}_{four_post_name}_vs_roll"],
                expected_roll,
                atol=1e-8,
            )

    front_curves = payload["axles"]["front"]["curves"]
    expected_gains = {
        "camber_gain_heave_rad_per_m": -_curve_gain_rad_per_m(heave_sweep, front_curves["bump_camber_deg"]),
        "toe_gain_heave_rad_per_m": _curve_gain_rad_per_m(heave_sweep, front_curves["bump_toe_deg"]),
        "caster_gain_heave_rad_per_m": _curve_gain_rad_per_m(heave_sweep, front_curves["bump_caster_deg"]),
        "kpi_gain_heave_rad_per_m": _curve_gain_rad_per_m(heave_sweep, front_curves["bump_kpi_deg"]),
        "trail_gain_heave_m_per_m": _curve_gain_m_per_m(heave_sweep, front_curves["bump_mech_trail_mm"]),
        "scrub_gain_heave_m_per_m": _curve_gain_m_per_m(heave_sweep, front_curves["bump_scrub_mm"]),
    }
    for metric, expected in expected_gains.items():
        assert summary[metric] == pytest.approx(expected, abs=1e-8), metric


def test_four_post_summary_filters_implausible_samples(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    vehicle = _four_post_unit_vehicle()
    monkeypatch.setattr(four_post_eval, "_load_active_vehicle_yaml", lambda: vehicle)
    heave_sweep = np.linspace(
        -0.03,
        0.03,
        four_post_eval.FOUR_POST_HEAVE_POSE_COUNT,
    )
    roll_sweep_deg = np.linspace(
        -1.25,
        1.25,
        four_post_eval.FOUR_POST_ROLL_POSE_COUNT,
    )
    result = _four_post_result_from_kinematics(vehicle, heave_sweep, roll_sweep_deg)
    first_heave_jack_time = _jack_times(four_post_eval.FOUR_POST_HEAVE_START_S, 1)[0]
    first_roll_time = _pose_sample_times(four_post_eval.FOUR_POST_ROLL_START_S, 1)[0]
    heave_jack_index = int(np.argmin(np.abs(result["time"] - first_heave_jack_time)))
    roll_index = int(np.argmin(np.abs(result["time"] - first_roll_time)))
    result["frKnC.jackingForce"][heave_jack_index] = 1e292
    result["frKnC.leftFz"][roll_index] = 1e292

    sim = four_post_eval.FourPostEvalSim(_four_post_unit_config(tmp_path))
    summary, series = sim.summarize(result)

    assert sim.metric_status["avg_anti_dive_pct"] == "partial"
    assert abs(summary["avg_anti_dive_pct"]) <= four_post_eval.FOUR_POST_PERCENT_ABS_LIMIT
    assert not np.any(np.abs(series["fr_anti_vs_heave"]) > four_post_eval.FOUR_POST_PERCENT_ABS_LIMIT)
    assert not np.any(np.abs(series["front_load_transfer_vs_roll"]) > four_post_eval.FOUR_POST_SIGNAL_ABS_LIMIT)


def test_four_post_anti_roll_does_not_replace_a_bad_measured_force_with_the_commanded_force(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    vehicle = _four_post_unit_vehicle()
    monkeypatch.setattr(four_post_eval, "_load_active_vehicle_yaml", lambda: vehicle)
    heave_sweep = np.linspace(
        -0.03,
        0.03,
        four_post_eval.FOUR_POST_HEAVE_POSE_COUNT,
    )
    roll_sweep_deg = np.linspace(
        -1.25,
        1.25,
        four_post_eval.FOUR_POST_ROLL_POSE_COUNT,
    )
    result = _four_post_result_from_kinematics(vehicle, heave_sweep, roll_sweep_deg)
    first_roll_jack_time = _jack_times(four_post_eval.FOUR_POST_ROLL_START_S, 1)[0]
    roll_jack_index = int(np.argmin(np.abs(result["time"] - first_roll_jack_time)))
    result["frKnC.fy"][roll_jack_index] = 1e-12
    result["frKnC.jackingForce"][roll_jack_index] = -50.0

    sim = four_post_eval.FourPostEvalSim(_four_post_unit_config(tmp_path))
    summary, series = sim.summarize(result)

    assert np.isfinite(summary["avg_anti_roll_front_pct"])
    assert sim.metric_status["avg_anti_roll_front_pct"] == "partial"
    assert len(series["fr_anti_vs_roll"]) == four_post_eval.FOUR_POST_ROLL_POSE_COUNT - 1


def test_four_post_anti_roll_samples_offset_force_pulses(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    vehicle = _four_post_unit_vehicle()
    monkeypatch.setattr(four_post_eval, "_load_active_vehicle_yaml", lambda: vehicle)
    heave_sweep = np.linspace(
        -0.03,
        0.03,
        four_post_eval.FOUR_POST_HEAVE_POSE_COUNT,
    )
    roll_sweep_deg = np.linspace(
        -1.25,
        1.25,
        four_post_eval.FOUR_POST_ROLL_POSE_COUNT,
    )
    result = _four_post_result_from_kinematics(vehicle, heave_sweep, roll_sweep_deg)
    roll_jack_times = _jack_times(
        four_post_eval.FOUR_POST_ROLL_START_S,
        four_post_eval.FOUR_POST_ROLL_POSE_COUNT,
    )

    def append_quiet_sample(source_index: int, time_s: float) -> None:
        for key, values in list(result.items()):
            value = float(values[source_index])
            if key.endswith(".fy") or key.endswith(".jackingForce"):
                value = 0.0
            result[key] = np.append(values, value)
        result["time"][-1] = time_s

    for jack_time in roll_jack_times:
        index = int(np.argmin(np.abs(result["time"] - jack_time)))
        roll_rad = float(result["frKnC.roll"][index])
        append_quiet_sample(index, jack_time - 0.1)
        result["time"][index] = jack_time + 0.4
        result["frKnC.fy"][index] = 1000.0
        result["rrKnC.fy"][index] = 1000.0
        result["frKnC.jackingForce"][index] = -100.0 * roll_rad
        result["rrKnC.jackingForce"][index] = -120.0 * roll_rad

    order = np.argsort(result["time"])
    for key in list(result):
        result[key] = result[key][order]

    _summary, series = four_post_eval.FourPostEvalSim(_four_post_unit_config(tmp_path)).summarize(result)

    assert len(series["fr_anti_vs_roll"]) == four_post_eval.FOUR_POST_ROLL_POSE_COUNT
    assert np.ptp(series["fr_anti_vs_roll"]) > 0.1
    assert np.ptp(series["rr_anti_vs_roll"]) > 0.1


def test_four_post_anti_roll_uses_direct_roll_jacking_signal(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    vehicle = _four_post_unit_vehicle()
    monkeypatch.setattr(four_post_eval, "_load_active_vehicle_yaml", lambda: vehicle)
    heave_sweep = np.linspace(
        -0.03,
        0.03,
        four_post_eval.FOUR_POST_HEAVE_POSE_COUNT,
    )
    roll_sweep_deg = np.linspace(
        -1.25,
        1.25,
        four_post_eval.FOUR_POST_ROLL_POSE_COUNT,
    )
    result = _four_post_result_from_kinematics(vehicle, heave_sweep, roll_sweep_deg)
    roll_jack_times = _jack_times(
        four_post_eval.FOUR_POST_ROLL_START_S,
        four_post_eval.FOUR_POST_ROLL_POSE_COUNT,
    )
    roll_tail_times = _pose_sample_times(
        four_post_eval.FOUR_POST_ROLL_START_S,
        four_post_eval.FOUR_POST_ROLL_POSE_COUNT,
    )

    for jack_time, tail_time in zip(roll_jack_times, roll_tail_times, strict=True):
        jack_index = int(np.argmin(np.abs(result["time"] - jack_time)))
        tail_index = int(np.argmin(np.abs(result["time"] - tail_time)))
        roll_rad = float(result["frKnC.roll"][jack_index])
        for prefix, gain in (("frKnC", -100.0), ("rrKnC", -120.0)):
            jacking_force = gain * roll_rad
            result[f"{prefix}.jackingForce"][jack_index] = jacking_force
            result[f"{prefix}.jackingForce"][tail_index] = 0.0

    _summary, series = four_post_eval.FourPostEvalSim(_four_post_unit_config(tmp_path)).summarize(result)

    assert np.ptp(series["fr_anti_vs_roll"]) > 0.1
    assert np.ptp(series["rr_anti_vs_roll"]) > 0.1


def test_four_post_fbrc_uses_differential_wheel_load_and_axle_track(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    vehicle = _four_post_unit_vehicle()
    monkeypatch.setattr(four_post_eval, "_load_active_vehicle_yaml", lambda: vehicle)
    heave_sweep = np.linspace(-0.03, 0.03, four_post_eval.FOUR_POST_HEAVE_POSE_COUNT)
    roll_sweep_deg = np.linspace(-1.25, 1.25, four_post_eval.FOUR_POST_ROLL_POSE_COUNT)
    result = _four_post_result_from_kinematics(vehicle, heave_sweep, roll_sweep_deg)

    jack_times = _jack_times(
        four_post_eval.FOUR_POST_ROLL_START_S,
        four_post_eval.FOUR_POST_ROLL_POSE_COUNT,
    )
    tail_times = _pose_sample_times(
        four_post_eval.FOUR_POST_ROLL_START_S,
        four_post_eval.FOUR_POST_ROLL_POSE_COUNT,
    )
    for jack_time, tail_time in zip(jack_times, tail_times, strict=True):
        jack_index = int(np.argmin(np.abs(result["time"] - jack_time)))
        tail_index = int(np.argmin(np.abs(result["time"] - tail_time)))
        for prefix in ("frKnC", "rrKnC"):
            result[f"{prefix}.leftFz"][jack_index] = result[f"{prefix}.leftFz"][tail_index] + 10.0
            result[f"{prefix}.rightFz"][jack_index] = result[f"{prefix}.rightFz"][tail_index] - 20.0

    summary, series = four_post_eval.FourPostEvalSim(_four_post_unit_config(tmp_path)).summarize(result)

    expected_ratio = -30.0 / 1000.0
    for axle, prefix in (("front", "fr"), ("rear", "rr")):
        side = vehicle[axle]
        assert isinstance(side, dict)
        suspension = side["suspension"]
        assert isinstance(suspension, dict)
        expected_height = float(suspension["wheel_center_m"][1]) * expected_ratio
        np.testing.assert_allclose(series[f"{prefix}_fbrc_jacking_ratio_vs_roll"], expected_ratio)
        np.testing.assert_allclose(series[f"{prefix}_fbrc_height_vs_roll"], expected_height)
        assert summary[f"avg_fbrc_differential_jacking_ratio_{axle}"] == pytest.approx(expected_ratio)
        assert summary[f"avg_fbrc_equivalent_height_{axle}_m"] == pytest.approx(expected_height)


def test_four_post_anti_roll_does_not_switch_to_the_contact_load_sum_when_jacking_force_is_bad(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    vehicle = _four_post_unit_vehicle()
    monkeypatch.setattr(four_post_eval, "_load_active_vehicle_yaml", lambda: vehicle)
    heave_sweep = np.linspace(
        -0.03,
        0.03,
        four_post_eval.FOUR_POST_HEAVE_POSE_COUNT,
    )
    roll_sweep_deg = np.linspace(
        -1.25,
        1.25,
        four_post_eval.FOUR_POST_ROLL_POSE_COUNT,
    )
    result = _four_post_result_from_kinematics(vehicle, heave_sweep, roll_sweep_deg)
    roll_jack_times = _jack_times(
        four_post_eval.FOUR_POST_ROLL_START_S,
        four_post_eval.FOUR_POST_ROLL_POSE_COUNT,
    )
    roll_tail_times = _pose_sample_times(
        four_post_eval.FOUR_POST_ROLL_START_S,
        four_post_eval.FOUR_POST_ROLL_POSE_COUNT,
    )

    for jack_time, tail_time in zip(roll_jack_times, roll_tail_times, strict=True):
        jack_index = int(np.argmin(np.abs(result["time"] - jack_time)))
        tail_index = int(np.argmin(np.abs(result["time"] - tail_time)))
        roll_rad = float(result["frKnC.roll"][jack_index])
        for prefix, gain in (("frKnC", 100.0), ("rrKnC", 120.0)):
            result[f"{prefix}.jackingForce"][jack_index] = 1e292
            fz_delta = gain * roll_rad
            for side in ("left", "right"):
                tail_fz = float(result[f"{prefix}.{side}Fz"][tail_index])
                result[f"{prefix}.{side}Fz"][jack_index] = tail_fz + 0.5 * fz_delta

    sim = four_post_eval.FourPostEvalSim(_four_post_unit_config(tmp_path))
    summary, series = sim.summarize(result)

    assert len(series["fr_anti_vs_roll"]) == 0
    assert np.isnan(summary["avg_anti_roll_front_pct"])
    assert sim.metric_status["avg_anti_roll_front_pct"] == "invalid"
    assert sim.metric_status["avg_lateral_jacking_coeff_rear"] == "invalid"


def test_four_post_lltd_uses_spring_roll_stiffness_when_arb_is_absent(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    vehicle = _four_post_unit_vehicle()
    for axle in ("front", "rear"):
        side = vehicle[axle]
        assert isinstance(side, dict)
        actuation = side["actuation"]
        assert isinstance(actuation, dict)
        actuation.pop("stabar", None)
    monkeypatch.setattr(four_post_eval, "_load_active_vehicle_yaml", lambda: vehicle)
    config = _four_post_unit_config(tmp_path)
    model_overrides = config["model_overrides"]
    assert isinstance(model_overrides, dict)
    suspension = model_overrides["suspension"]
    assert isinstance(suspension, dict)
    front_suspension = suspension["front"]
    rear_suspension = suspension["rear"]
    assert isinstance(front_suspension, dict)
    assert isinstance(rear_suspension, dict)
    front_suspension["stabar_rate_n_m_per_rad"] = 500.0
    rear_suspension["stabar_rate_n_m_per_rad"] = 700.0
    heave_sweep = np.linspace(
        -0.03,
        0.03,
        four_post_eval.FOUR_POST_HEAVE_POSE_COUNT,
    )
    roll_sweep_deg = np.linspace(
        -1.25,
        1.25,
        four_post_eval.FOUR_POST_ROLL_POSE_COUNT,
    )

    summary, series = four_post_eval.FourPostEvalSim(config).summarize(
        _four_post_result_from_kinematics(vehicle, heave_sweep, roll_sweep_deg)
    )

    assert summary["arb_roll_stiffness_front_Nm_per_rad"] == pytest.approx(0.0)
    assert summary["arb_roll_stiffness_rear_Nm_per_rad"] == pytest.approx(0.0)
    assert summary["elastic_roll_stiffness_front_Nm_per_rad"] == pytest.approx(
        summary["spring_roll_stiffness_front_Nm_per_rad"]
    )
    assert summary["elastic_roll_stiffness_rear_Nm_per_rad"] == pytest.approx(
        summary["spring_roll_stiffness_rear_Nm_per_rad"]
    )
    assert np.isfinite(summary["avg_roll_rate_distribution_front_pct"])
    assert np.isfinite(summary["avg_lltd_front_pct"])
    assert np.isfinite(summary["avg_antiroll_geometry_lltd_delta_pct"])
    assert np.isfinite(series["lltd_stiffness_vs_roll"]).any()


def test_kinematic_heave_gains_match_four_post_eval_metrics() -> None:
    metrics_path = ROOT / "simulations/mbd/results/four_post_eval_report_metrics.csv"
    if not metrics_path.is_file():
        pytest.skip("FourPostEval metrics artifact is not available")

    metrics: dict[str, float] = {}
    with metrics_path.open(encoding="utf-8", newline="") as f:
        for row in csv.DictReader(f):
            try:
                metrics[row["metric"]] = float(row["value"])
            except (TypeError, ValueError):
                continue

    vehicle = yaml.safe_load((ROOT / "vehicle.yml").read_text(encoding="utf-8"))
    four_post_sweep = np.linspace(-0.03, 0.03, 11)
    payload = kinematic_curves_payload(vehicle, sweep_m=four_post_sweep.tolist())
    sweep = np.asarray(payload["sweep_m"], dtype=float)
    front_curves = payload["axles"]["front"]["curves"]

    comparisons = {
        "camber_gain_heave_rad_per_m": -_curve_gain_rad_per_m(sweep, front_curves["bump_camber_deg"]),
        "toe_gain_heave_rad_per_m": _curve_gain_rad_per_m(sweep, front_curves["bump_toe_deg"]),
        "caster_gain_heave_rad_per_m": _curve_gain_rad_per_m(sweep, front_curves["bump_caster_deg"]),
        "kpi_gain_heave_rad_per_m": _curve_gain_rad_per_m(sweep, front_curves["bump_kpi_deg"]),
        "trail_gain_heave_m_per_m": _curve_gain_m_per_m(sweep, front_curves["bump_mech_trail_mm"]),
        "scrub_gain_heave_m_per_m": _curve_gain_m_per_m(sweep, front_curves["bump_scrub_mm"]),
    }

    tolerances = {"camber_gain_heave_rad_per_m": 1e-5}
    for metric, observed in comparisons.items():
        assert observed == pytest.approx(metrics[metric], abs=tolerances.get(metric, 1e-6)), metric


def _curve_gain_rad_per_m(sweep_m: np.ndarray, curve_deg: list[float]) -> float:
    curve_rad = np.radians(np.asarray(curve_deg, dtype=float))
    return float(np.polyfit(sweep_m, curve_rad, 1)[0])


def _curve_gain_m_per_m(sweep_m: np.ndarray, curve_mm: list[float]) -> float:
    curve_m = np.asarray(curve_mm, dtype=float) / 1000.0
    return float(np.polyfit(sweep_m, curve_m, 1)[0])


@pytest.mark.parametrize("pulse_force", [-1000.0, 1000.0])
@pytest.mark.parametrize("expected_anti_pct", [-20.0, 20.0])
def test_four_post_anti_dive_sign_is_independent_of_pulse_direction(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
    pulse_force: float,
    expected_anti_pct: float,
) -> None:
    vehicle = _four_post_unit_vehicle()
    monkeypatch.setattr(four_post_eval, "_load_active_vehicle_yaml", lambda: vehicle)
    result = _four_post_result_from_kinematics(
        vehicle,
        np.linspace(-0.03, 0.03, four_post_eval.FOUR_POST_HEAVE_POSE_COUNT),
        np.linspace(-0.75, 0.75, four_post_eval.FOUR_POST_ROLL_POSE_COUNT),
    )
    front = CornerKinematics.from_vehicle(vehicle, "front").wheel_center_initial
    rear = CornerKinematics.from_vehicle(vehicle, "rear").wheel_center_initial
    wheelbase = abs(front[0] - rear[0])
    # An upward response to negative braking Fx is dive-resisting geometry.
    coefficient = -(expected_anti_pct / 100.0) * 0.35 / wheelbase
    pulse = np.isin(
        result["time"],
        _jack_times(four_post_eval.FOUR_POST_HEAVE_START_S, four_post_eval.FOUR_POST_HEAVE_POSE_COUNT),
    )
    result["frKnC.fx"][pulse] = pulse_force
    # The fixture reaction signal is opposite to the chassis jacking response.
    result["frKnC.jackingForce"][pulse] = -coefficient * pulse_force
    config = _four_post_unit_config(tmp_path)
    summary, series = four_post_eval.FourPostEvalSim(config).summarize(result)

    assert summary["avg_anti_dive_pct"] == pytest.approx(expected_anti_pct)
    np.testing.assert_allclose(series["fr_anti_vs_heave"], expected_anti_pct)
    assert summary["avg_longitudinal_jacking_coeff_front"] == pytest.approx(coefficient)


@pytest.mark.parametrize("axle", ("front", "rear"))
def test_kinpy_continuation_crosses_nominal_pose(axle: str) -> None:
    vehicle = yaml.safe_load((ROOT / "vehicle.yml").read_text())
    corner = CornerKinematics.from_vehicle(vehicle, axle)
    guess = np.zeros(3)
    for jounce in (-0.0025, 0.0, 0.0025):
        guess, points, residual = corner.solve_jounce(jounce, guess)
        assert residual < 1e-8
        assert points.contact_patch[2] == pytest.approx(corner.contact_patch_initial[2] + jounce, abs=1e-8)


def test_corner_snapshots_are_independent_of_later_solves() -> None:
    corner = CornerKinematics.from_vehicle(_direct_quarter_car_vehicle(), "front")
    _, first, _ = corner.solve_jounce(0.25, np.zeros(3))
    saved = {name: values.copy() for name, values in vars(first).items()}
    corner.solve_jounce(-0.3, np.zeros(3), rack_displacement_m=0.15)
    for name, values in vars(first).items():
        np.testing.assert_array_equal(values, saved[name])
    _, repeated, _ = corner.solve_jounce(0.25, np.zeros(3))
    for name, values in vars(repeated).items():
        np.testing.assert_allclose(values, saved[name], atol=1e-10)


def test_geometry_only_corner_rejects_unreachable_pose() -> None:
    corner = CornerKinematics.from_vehicle(_direct_quarter_car_vehicle(), "front")
    with pytest.raises(ValueError, match="constraint residual"):
        corner.solve_jounce(100.0, np.zeros(3))
    _, points, residual = corner.solve_jounce(0.25, np.zeros(3))
    assert residual < 1e-8
    assert points.contact_patch[2] == pytest.approx(0.25, abs=1e-8)


def test_custom_jounce_sweep_includes_zero() -> None:
    from engines.kinpy.kinematics import _clean_sweep

    assert _clean_sweep([-0.02, 0.01]) == (-0.02, 0.0, 0.01)
    assert _clean_sweep([0.01, 0.02]) == (0.01, 0.02)
    assert _clean_sweep([-0.01, 0.0, 0.01]) == (-0.01, 0.0, 0.01)


def test_roll_center_height_uses_both_corners() -> None:
    vehicle = yaml.safe_load((ROOT / "vehicle.yml").read_text(encoding="utf-8"))
    payload = kinematic_curves_payload(vehicle, sweep_m=[0.0], roll_deg=[-1.0, 0.0, 1.0], steer_m=[0.0])
    for axle in ("front", "rear"):
        curves = payload["axles"][axle]["curves"]
        heights = curves["roll_rc_height_mm"]
        # A symmetric axle has the same height for equal left and right roll.
        assert heights[0] == pytest.approx(heights[2], abs=1e-5)
        assert heights[1] == pytest.approx(curves["bump_rc_height_mm"][0], abs=1e-5)


def test_four_post_preserves_vehicle_spring_curves_without_rate_overrides(
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    vehicle = _four_post_unit_vehicle()
    tables = {
        "front": [[-0.05, -500.0], [0.0, 0.0], [0.02, 500.0], [0.05, 1800.0]],
        "rear": [[-0.05, -600.0], [0.0, 0.0], [0.02, 700.0], [0.05, 2300.0]],
    }
    for axle, table in tables.items():
        side = vehicle[axle]
        assert isinstance(side, dict)
        side["actuation"]["shock"]["spring_table"]["table"] = table
        side["actuation"]["stabar"]["rate_n_m_per_rad"] = 321.0
    monkeypatch.setattr(four_post_eval, "_load_active_vehicle_yaml", lambda: vehicle)
    setup = four_post_eval._configured_suspension_setup({})
    for axle, table in tables.items():
        np.testing.assert_array_equal(setup[f"{axle}_spring_table"], table)
        assert setup[f"{axle}_stabar_rate"] == 321.0
    overridden = four_post_eval._configured_suspension_setup({
        "model_overrides": {"suspension": {"front": {"spring_rate_n_per_m": 10000.0}}},
    })
    np.testing.assert_array_equal(overridden["front_spring_table"][:, 1], np.asarray(tables["front"])[:, 0] * 10000.0)
    np.testing.assert_array_equal(overridden["rear_spring_table"], tables["rear"])


def test_four_post_sends_bar_rates_only_to_the_rig_bars_that_exist(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    vehicle = _four_post_unit_vehicle()
    front = vehicle["front"]
    assert isinstance(front, dict)
    front["actuation"].pop("stabar")
    monkeypatch.setattr(four_post_eval, "_load_active_vehicle_yaml", lambda: vehicle)

    overrides = four_post_eval.FourPostEvalSim(_four_post_unit_config(tmp_path)).build_model_setup_overrides()

    assert not [key for key in overrides if key.startswith("pVehicle.") and "Stabar" in key]
    assert "pFrStabar.barRate" not in overrides
    assert overrides["pRrStabar.barRate"] == 0.0


def _four_post_unit_run(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> tuple[four_post_eval.FourPostEvalSim, dict[str, np.ndarray], dict[str, object]]:
    vehicle = _four_post_unit_vehicle()
    monkeypatch.setattr(four_post_eval, "_load_active_vehicle_yaml", lambda: vehicle)
    result = _four_post_result_from_kinematics(
        vehicle,
        np.linspace(-0.03, 0.03, four_post_eval.FOUR_POST_HEAVE_POSE_COUNT),
        np.linspace(-1.25, 1.25, four_post_eval.FOUR_POST_ROLL_POSE_COUNT),
    )
    return four_post_eval.FourPostEvalSim(_four_post_unit_config(tmp_path)), result, vehicle


def _pose_indices(result: dict[str, np.ndarray], start_s: float, count: int) -> list[tuple[int, int]]:
    """(pulse row, tail row) per pose."""
    return [
        (int(np.argmin(np.abs(result["time"] - jack))), int(np.argmin(np.abs(result["time"] - tail))))
        for jack, tail in zip(_jack_times(start_s, count), _pose_sample_times(start_s, count), strict=True)
    ]


def _roll_poses(result: dict[str, np.ndarray]) -> list[tuple[int, int]]:
    return _pose_indices(result, four_post_eval.FOUR_POST_ROLL_START_S, four_post_eval.FOUR_POST_ROLL_POSE_COUNT)


def _set_roll_pulse_loads(
    result: dict[str, np.ndarray],
    left_delta_n: float,
    right_delta_n: float,
    jacking_delta_n: float,
) -> None:
    for pulse, tail in _roll_poses(result):
        for prefix in ("frKnC", "rrKnC"):
            result[f"{prefix}.leftFz"][pulse] = result[f"{prefix}.leftFz"][tail] + left_delta_n
            result[f"{prefix}.rightFz"][pulse] = result[f"{prefix}.rightFz"][tail] + right_delta_n
            # The fixture reaction signal is opposite to the chassis jacking response.
            result[f"{prefix}.jackingForce"][pulse] = result[f"{prefix}.jackingForce"][tail] - jacking_delta_n


def test_four_post_anti_roll_key_is_net_jacking_with_zero_net_and_nonzero_differential(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    sim, result, vehicle = _four_post_unit_run(tmp_path, monkeypatch)
    _set_roll_pulse_loads(result, left_delta_n=40.0, right_delta_n=-40.0, jacking_delta_n=0.0)

    summary, _series = sim.summarize(result)

    assert summary["avg_anti_roll_front_pct"] == pytest.approx(0.0, abs=1e-12)
    assert summary["avg_lateral_jacking_coeff_front"] == pytest.approx(0.0, abs=1e-12)
    assert summary["avg_fbrc_differential_jacking_ratio_front"] == pytest.approx(-0.08)
    front = vehicle["front"]
    assert isinstance(front, dict)
    half_track = float(front["suspension"]["wheel_center_m"][1])
    assert summary["avg_fbrc_equivalent_height_front_m"] == pytest.approx(-0.08 * half_track)
    plots = four_post_eval._normalize_four_post_report_config({})["plots"]
    assert "Anti-Roll" not in plots["jacking_roll"]["title"]
    assert "Net Axle Jacking" in plots["jacking_roll"]["title"]


def test_four_post_fbrc_height_is_set_by_the_differential_and_not_by_net_jacking(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    sim, result, vehicle = _four_post_unit_run(tmp_path, monkeypatch)
    _set_roll_pulse_loads(result, left_delta_n=70.0, right_delta_n=-10.0, jacking_delta_n=60.0)

    summary, series = sim.summarize(result)

    front = vehicle["front"]
    assert isinstance(front, dict)
    half_track = float(front["suspension"]["wheel_center_m"][1])
    assert summary["avg_lateral_jacking_coeff_front"] == pytest.approx(0.06)
    np.testing.assert_allclose(series["fr_fbrc_height_vs_roll"], -0.08 * half_track)
    assert summary["avg_fbrc_equivalent_height_front_m"] == pytest.approx(-0.08 * half_track)


def test_four_post_pose_without_a_sample_in_its_window_is_not_filled_from_outside(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    sim, result, _vehicle = _four_post_unit_run(tmp_path, monkeypatch)
    _pulse, tail = _roll_poses(result)[3]
    keep = np.arange(result["time"].size) != tail
    result = {key: values[keep] for key, values in result.items()}

    summary, series = sim.summarize(result)

    assert len(series["roll"]) == four_post_eval.FOUR_POST_ROLL_POSE_COUNT - 1
    assert sim.metric_status["camber_gain_roll_rad_per_rad"] == "partial"
    assert np.isfinite(summary["camber_gain_roll_rad_per_rad"])


def test_four_post_elastic_share_does_not_fill_a_bad_pose_from_its_neighbors(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    sim, result, _vehicle = _four_post_unit_run(tmp_path, monkeypatch)
    _pulse, tail = _roll_poses(result)[2]
    result["frKnC.leftFz"][tail] = 1e292

    summary, series = sim.summarize(result)

    # The bad pose and the zero-roll pose, where the share is 0/0.
    assert np.count_nonzero(np.isnan(series["lltd_contact_force_vs_roll"])) == 2
    assert sim.metric_status["avg_lltd_front_pct"] == "partial"
    assert np.isfinite(summary["avg_lltd_front_pct"])


def test_four_post_elastic_share_keeps_the_sign_of_each_axle_transfer(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    sim, result, _vehicle = _four_post_unit_run(tmp_path, monkeypatch)
    for _pulse, tail in _roll_poses(result):
        roll_rad = float(result["rrKnC.roll"][tail])
        result["rrKnC.leftFz"][tail] = 1000.0 - 300.0 * roll_rad
        result["rrKnC.rightFz"][tail] = 1000.0 + 300.0 * roll_rad

    summary, _series = sim.summarize(result)

    assert np.isnan(summary["avg_lltd_front_pct"])
    assert sim.metric_status["avg_lltd_front_pct"] == "invalid"


def test_four_post_heave_poses_in_tension_are_flagged_and_anti_records_kept(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    sim, result, _vehicle = _four_post_unit_run(tmp_path, monkeypatch)
    poses = _pose_indices(result, four_post_eval.FOUR_POST_HEAVE_START_S, four_post_eval.FOUR_POST_HEAVE_POSE_COUNT)
    for index, (pulse, tail) in enumerate(poses):
        for prefix in ("frKnC", "rrKnC"):
            if prefix == "frKnC" and index in (0, 1):
                result[f"{prefix}.leftFz"][[pulse, tail]] = 0.0
                result[f"{prefix}.rightFz"][[pulse, tail]] = 0.0
                result[f"{prefix}.jackingForce"][[pulse, tail]] = 300.0
            else:
                total = result[f"{prefix}.leftFz"][tail] + result[f"{prefix}.rightFz"][tail]
                result[f"{prefix}.jackingForce"][[pulse, tail]] = -total

    summary, series = sim.summarize(result)

    assert summary["heave_cp_tension_points"] == 2
    residual = series["fr_tension_residual_vs_heave"]
    assert np.count_nonzero(np.isclose(residual, 300.0)) == 2
    assert np.count_nonzero(np.isclose(residual, 0.0)) == four_post_eval.FOUR_POST_HEAVE_POSE_COUNT - 2
    assert np.count_nonzero(np.isnan(series["fr_l_fz_vs_heave"])) == 2
    assert sim.metric_status["avg_anti_dive_pct"] == "ok"
    assert summary["avg_anti_dive_pct"] == pytest.approx(0.0, abs=1e-12)


def test_four_post_anti_outputs_state_their_force_path(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    sim, result, _vehicle = _four_post_unit_run(tmp_path, monkeypatch)

    summary, _series = sim.summarize(result)

    assert summary["anti_force_path"] == "contact_patch_upright_reacted"
    assert "avg_longitudinal_jacking_coeff_front" in summary
    plots = four_post_eval._normalize_four_post_report_config({})["plots"]
    assert "upright" in plots["jacking_heave"]["title"]
    assert "LLTD" not in plots["lltd_roll"]["title"]


def test_four_post_metrics_csv_carries_a_status_column(tmp_path: Path) -> None:
    from common.metrics_csv import read_metric_status, read_metrics

    path = four_post_eval.write_metrics_csv(
        {"a": 1.0, "b": 2.0, "c": float("nan"), "d": True},
        tmp_path / "metrics.csv",
        status={"b": "partial"},
    )

    with path.open(newline="", encoding="utf-8") as f:
        rows = list(csv.reader(f))
    assert rows == [
        ["metric", "value", "status"],
        ["a", "1.0", "ok"],
        ["b", "2.0", "partial"],
        ["c", "", "invalid"],
        ["d", "True", "ok"],
    ]
    assert read_metric_status(path)["b"] == (2.0, "partial")
    assert np.isnan(read_metrics(path)["b"])
    assert read_metrics(path, accept=frozenset({"ok", "partial"}))["b"] == 2.0

    legacy = tmp_path / "legacy.csv"
    legacy.write_text("metric,value\na,1.0\n", encoding="utf-8")
    assert read_metric_status(legacy)["a"] == (1.0, "unknown")
    assert np.isnan(read_metrics(legacy)["a"])


def _trailing_arm_x(cp_rise_m: np.ndarray, pivot_xz: tuple[float, float], point_z_m: float) -> np.ndarray:
    """Side-view x of a point at height point_z_m above the CP on an arm that pivots at pivot_xz."""
    theta = np.linspace(-0.3, 0.3, 20001)
    rx, rz = -pivot_xz[0], point_z_m - pivot_xz[1]
    cp_rz = -pivot_xz[1]
    cp_rise = -pivot_xz[0] * np.sin(theta) + cp_rz * np.cos(theta) - cp_rz
    x = pivot_xz[0] + rx * np.cos(theta) - rz * np.sin(theta) - (pivot_xz[0] + rx)
    order = np.argsort(cp_rise)
    return np.interp(cp_rise_m, cp_rise[order], x[order])


def test_design_pose_jacking_coefficients_match_a_trailing_arm_instant_center() -> None:
    pivot = (0.5, 0.40)
    wheel_radius = 0.25
    jounce = np.linspace(-0.03, 0.03, 11)

    cp_coeff, wc_coeff = four_post_eval._design_pose_jacking_coefficients(
        jounce,
        _trailing_arm_x(jounce, pivot, 0.0),
        _trailing_arm_x(jounce, pivot, wheel_radius),
    )

    assert cp_coeff == pytest.approx(pivot[1] / pivot[0], rel=1e-3)
    assert wc_coeff == pytest.approx((pivot[1] - wheel_radius) / pivot[0], rel=1e-3)


def _add_trailing_arm_path_signals(
    result: dict[str, np.ndarray],
    pivots: dict[str, tuple[float, float]],
    wheel_radius_m: float,
) -> None:
    jounce = -result["frKnC.heave"]
    for axle, pivot in pivots.items():
        for side in ("left", "right"):
            result[f"{axle}.{side}CP.r_0[1]"] = _trailing_arm_x(jounce, pivot, 0.0)
            result[f"{axle}.{side}Tire.chassisFrame.r_0[1]"] = _trailing_arm_x(jounce, pivot, wheel_radius_m)


def test_four_post_reports_anti_on_both_force_paths(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
    sim, result, vehicle = _four_post_unit_run(tmp_path, monkeypatch)
    summary, _series = sim.summarize(result)
    assert np.isnan(summary["anti_squat_wheel_center_path_pct"])
    assert sim.metric_status["anti_squat_wheel_center_path_pct"] == "unavailable"

    # Front pivot behind and rear pivot ahead of the wheel, both above it.
    _add_trailing_arm_path_signals(result, {"frAxleDW": (-0.5, 0.40), "rrAxleDW": (0.5, 0.40)}, 0.25)
    summary, _series = sim.summarize(result)

    front = CornerKinematics.from_vehicle(vehicle, "front").wheel_center_initial
    rear = CornerKinematics.from_vehicle(vehicle, "rear").wheel_center_initial
    ref_long = 0.35 / abs(front[0] - rear[0])
    expected = {
        ("front", "contact_patch"): -0.8,
        ("front", "wheel_center"): -0.3,
        ("rear", "contact_patch"): 0.8,
        ("rear", "wheel_center"): 0.3,
    }
    for (axle, path), coeff in expected.items():
        assert summary[f"longitudinal_jacking_coeff_{axle}_{path}_path"] == pytest.approx(coeff, rel=1e-3)
        assert sim.metric_status[f"longitudinal_jacking_coeff_{axle}_{path}_path"] == "ok"
    # Braking Fx is negative, so a negative front coefficient lifts the front under braking.
    assert summary["anti_dive_contact_patch_path_pct"] == pytest.approx(80.0 / ref_long, rel=1e-3)
    assert summary["anti_dive_wheel_center_path_pct"] == pytest.approx(30.0 / ref_long, rel=1e-3)
    assert summary["anti_squat_contact_patch_path_pct"] == pytest.approx(80.0 / ref_long, rel=1e-3)
    assert summary["anti_squat_wheel_center_path_pct"] == pytest.approx(30.0 / ref_long, rel=1e-3)


def test_four_post_reaction_path_change_leaves_the_contact_patch_anti_unchanged(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    sim, result, _vehicle = _four_post_unit_run(tmp_path, monkeypatch)
    _add_trailing_arm_path_signals(result, {"frAxleDW": (-0.5, 0.40), "rrAxleDW": (0.5, 0.40)}, 0.25)
    before, _series = sim.summarize(result)

    # Only the wheel-center path changes: the wheel center now moves with the CP.
    for axle in ("frAxleDW", "rrAxleDW"):
        for side in ("left", "right"):
            result[f"{axle}.{side}Tire.chassisFrame.r_0[1]"] = result[f"{axle}.{side}CP.r_0[1]"].copy()
    after, _series = sim.summarize(result)

    for key in (
        "anti_dive_contact_patch_path_pct",
        "anti_squat_contact_patch_path_pct",
        "avg_anti_dive_pct",
        "avg_anti_squat_pct",
        "avg_longitudinal_jacking_coeff_front",
        "avg_longitudinal_jacking_coeff_rear",
    ):
        assert after[key] == pytest.approx(before[key], nan_ok=True)
    assert after["anti_squat_wheel_center_path_pct"] == pytest.approx(after["anti_squat_contact_patch_path_pct"])
    assert after["anti_squat_wheel_center_path_pct"] != pytest.approx(before["anti_squat_wheel_center_path_pct"])
