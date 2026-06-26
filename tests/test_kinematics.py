from __future__ import annotations

import csv
from pathlib import Path

import numpy as np
import pytest
import yaml

from _3_StandardSim.FourPostEval import four_post_eval_sim as four_post_eval
from _5_App.kinematics import KINEMATIC_CURVE_META, CornerKinematics, kinematic_curves_payload


ROOT = Path(__file__).resolve().parents[1]
INCH_TO_M = 0.0254


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
                "spring_table": {
                    "table": [
                        [-0.05, -1000.0],
                        [0.0, 0.0],
                        [0.05, 1000.0],
                    ]
                },
                "free_length_m": 0.25,
            },
            "stabar": {"rate_n_m_per_rad": 0.0},
        }
    return vehicle


def _four_post_unit_config(tmp_path: Path) -> dict[str, object]:
    return {
        "model_overrides": {
            "suspension": {
                "front": {"spring_rate_n_per_m": 20000.0, "stabar_rate_n_m_per_rad": 0.0},
                "rear": {"spring_rate_n_per_m": 20000.0, "stabar_rate_n_m_per_rad": 0.0},
            },
        },
        "report": {"metrics_csv_path": str(tmp_path / "missing_metrics.csv")},
    }


def _pose_sample_times(start_s: float, count: int) -> list[float]:
    return [
        start_s + four_post_eval.FOUR_POST_POSE_STEP_S * index + 4.0
        for index in range(count)
    ]


def _jack_times(start_s: float, count: int) -> list[float]:
    return [
        start_s + four_post_eval.FOUR_POST_POSE_STEP_S * index + 1.5
        for index in range(count)
    ]


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
            for name in ("SpringLength", "Fz", "Gamma", "Toe", "Caster", "Kpi", "MechTrail", "MechScrub"):
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
            write_corner(prefix, time, values, jounce_m=right_jounce, load_delta_n=100.0 * roll_rad)
            result[f"{prefix}.stabarAngle"][index_by_time[time]] = 0.25 * roll_rad

    for time, jounce in zip(heave_jack_times, heave_by_pose, strict=True):
        for prefix in prefixes.values():
            write_axis(prefix, time, heave=jounce)
            result[f"{prefix}.fx"][index_by_time[time]] = 1000.0

    for time, roll_rad in zip(roll_jack_times, roll_by_pose_rad, strict=True):
        for prefix in prefixes.values():
            write_axis(prefix, time, roll=roll_rad)
            result[f"{prefix}.fy"][index_by_time[time]] = 1000.0

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
                "front": {"camber_deg": -1.7341, "caster_deg": 2.2496, "kpi_deg": 12.3343},
                "rear": {"camber_deg": -0.7327, "caster_deg": 6.4164, "kpi_deg": 8.7936},
            },
        ),
        (
            1.0,
            {
                "front": {"camber_deg": -2.4826, "caster_deg": 2.2562, "kpi_deg": 13.0828},
                "rear": {"camber_deg": -1.4827, "caster_deg": 6.4298, "kpi_deg": 9.5436},
            },
        ),
        (
            -1.0,
            {
                "front": {"camber_deg": 0.4331, "caster_deg": 2.2328, "kpi_deg": 10.1670},
                "rear": {"camber_deg": 1.4257, "caster_deg": 6.3840, "kpi_deg": 6.6353},
            },
        ),
        (
            -0.5,
            {
                "front": {"camber_deg": -0.2782, "caster_deg": 2.2379, "kpi_deg": 10.8784},
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
    assert len(payload["sweep_m"]) == 20
    assert len(payload["roll_deg"]) == 20
    assert len(payload["curve_meta"]) == 16
    assert [item["source_plot"] for item in payload["curve_meta"]] == [
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
    }
    for item in KINEMATIC_CURVE_META:
        key = item["id"]
        assert len(front_curves[key]) == axis_lengths[item["x_id"]]
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
    summary, series = four_post_eval.FourPostEvalSim(
        _four_post_unit_config(tmp_path)
    ).summarize(
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


def test_kinematic_heave_gains_match_four_post_eval_metrics() -> None:
    metrics_path = ROOT / "_3_StandardSim/results/four_post_eval_report_metrics.csv"
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
