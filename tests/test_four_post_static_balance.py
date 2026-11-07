from __future__ import annotations

import csv
from pathlib import Path
from typing import Any

import numpy as np
import pytest

from common.metrics_csv import read_metric_status
from simulations.response.mbd.four_post import four_post_eval_sim as fp

GRAVITY = fp.GRAVITY_MPS2
SPRING_RATE = 30000.0
FREE_LENGTH = 0.22
MOTION_RATIO = {"frKnC": 1.0, "rrKnC": 1.25}
AXLE_X = {"frKnC": 0.0, "rrKnC": -1.5}
MBD_AXLE = {"frKnC": "frAxleDW", "rrKnC": "rrAxleDW"}
ACTUATOR = {"frKnC": "frChassisActuator", "rrKnC": "rrChassisActuator"}
HALF_TRACK = 0.6
SPRUNG_MASS = 240.0
TARGET_N = SPRUNG_MASS * 0.25 * GRAVITY
HEAVE_POSES = 0.006 * (np.arange(fp.FOUR_POST_HEAVE_POSE_COUNT) - 5)
ROLL_POSES = np.radians(0.15 * (np.arange(fp.FOUR_POST_ROLL_POSE_COUNT) - 5))


def _vehicle() -> dict[str, Any]:
    def side(x: float) -> dict[str, Any]:
        return {
            "suspension": {"wheel_center_m": [x, HALF_TRACK, 0.2]},
            "actuation": {
                "shock": {
                    "mount_m": [x, 0.3, 0.5],
                    "spring_table": {"table": [[0.0, 0.0], [1.0, SPRING_RATE]]},
                    "free_length_m": FREE_LENGTH,
                },
                "rod_mount_m": [x, 0.3, 0.3],
                "stabar": {"rate_n_m_per_rad": 0.0},
            },
            "masses": {
                name: {"mass_kg": 1.0} for name in ("unsprung", "upper_control_arm", "lower_control_arm", "tie_rod")
            },
            "tire": {"vertical_stiffness_n_per_m": 200000.0},
        }

    return {
        "sprung_mass": {"mass_kg": SPRUNG_MASS, "cg_m": [-0.75, 0.0, 0.3]},
        "driver_mass": {"mass_kg": 0.0, "cg_m": [0.0, 0.0, 0.0]},
        "front": side(AXLE_X["frKnC"]),
        "rear": side(AXLE_X["rrKnC"]),
    }


def _config(metrics_csv: Path) -> dict[str, Any]:
    axle = {"spring_rate_n_per_m": SPRING_RATE, "stabar_rate_n_m_per_rad": 0.0}
    return {
        "model_overrides": {"suspension": {"front": dict(axle), "rear": dict(axle)}},
        "procedure": {"forceMagnitude": 1000.0},
        "validation": {"min_contact_fz_n": 1.0, "fail_on_contact_loss": False},
        "report": {"enabled": False, "metrics_csv_path": str(metrics_csv)},
    }


def _commands(time: np.ndarray) -> dict[str, np.ndarray]:
    heave = np.zeros_like(time)
    roll = np.zeros_like(time)
    fx = np.zeros_like(time)
    fy = np.zeros_like(time)
    step = fp.FOUR_POST_POSE_STEP_S
    for index, value in enumerate(HEAVE_POSES):
        start = fp.FOUR_POST_HEAVE_START_S + step * index
        heave[(time >= start) & (time < start + step)] = value
        fx[np.isclose(time, start + 1.5)] = 1000.0
    for index, value in enumerate(ROLL_POSES):
        start = fp.FOUR_POST_ROLL_START_S + step * index
        roll[(time >= start) & (time < start + step)] = value
        fy[np.isclose(time, start + 1.5)] = 1000.0
    return {"heave": heave, "roll": roll, "fx": fx, "fy": fy}


def _rig_result(
    *,
    contact_scale: float = 1.0,
    front_left_offset_n: float = 0.0,
    front_drift_n_per_s: float = 0.0,
    ramp_end_split_n: float = 0.0,
    spring_offset_n: float = 0.0,
) -> dict[str, np.ndarray]:
    """Quasi-static rig output that closes unless a knob breaks it."""
    time = np.arange(0.0, fp.FOUR_POST_STOP_TIME_S + 0.25, 0.5)
    commands = _commands(time)
    zero = np.ones_like(time, dtype=bool)
    for name in ("heave", "roll", "fx", "fy"):
        zero &= commands[name] == 0.0
    ramp_end = zero & ~(np.r_[True, zero[:-1]] & np.r_[zero[1:], True])

    result: dict[str, np.ndarray] = {"time": time}
    for knc, axle in MBD_AXLE.items():
        mr = MOTION_RATIO[knc]
        design_length = FREE_LENGTH - TARGET_N * mr / SPRING_RATE
        result[f"{knc}.heave"] = -commands["heave"]
        result[f"{knc}.roll"] = commands["roll"]
        result[f"{knc}.fx"] = commands["fx"]
        result[f"{knc}.fy"] = commands["fy"]
        result[f"{knc}.stabarAngle"] = 0.25 * commands["roll"]
        forces = {}
        moments = np.zeros((time.size, 3))
        for side, sign in (("left", 1.0), ("right", -1.0)):
            jounce = commands["heave"] + sign * HALF_TRACK * commands["roll"]
            length = design_length - jounce / mr
            spring = SPRING_RATE * (FREE_LENGTH - length)
            fz = contact_scale * spring / mr
            if knc == "frKnC" and side == "left":
                fz = fz + front_left_offset_n
            fz = fz + sign * ramp_end_split_n * ramp_end
            result[f"{knc}.{side}SpringLength"] = length
            result[f"{knc}.{side}Fz"] = fz
            for name, gain in (
                ("Gamma", 0.4),
                ("Toe", 0.001),
                ("Caster", 0.01),
                ("Kpi", 0.3),
                ("MechTrail", 0.002),
                ("MechScrub", 0.001),
            ):
                result[f"{knc}.{side}{name}"] = gain * jounce
            force = np.column_stack([0.5 * commands["fx"], 0.5 * commands["fy"], fz])
            position = np.column_stack(
                [np.full_like(time, AXLE_X[knc]), np.full_like(time, sign * HALF_TRACK), np.zeros_like(time)]
            )
            forces[side] = force
            moments += np.cross(position, force)
            for index in (1, 2, 3):
                result[f"{axle}.{side}CP.f[{index}]"] = force[:, index - 1]
                result[f"{axle}.{side}CP.t[{index}]"] = np.zeros_like(time)
            for index in (1, 2):
                result[f"{axle}.{side}CP.r_0[{index}]"] = position[:, index - 1]
            result[f"{axle}.{side}ShockLinkage.TabularSpring.force.f"] = spring + spring_offset_n
        chassis_force = -(forces["left"] + forces["right"])
        if knc == "frKnC":
            chassis_force[:, 2] += front_drift_n_per_s * time
        for index in (1, 2, 3):
            result[f"{ACTUATOR[knc]}.sprungLoads.frame_a.f[{index}]"] = chassis_force[:, index - 1]
            result[f"{ACTUATOR[knc]}.sprungLoads.frame_a.t[{index}]"] = -moments[:, index - 1]
        result[f"{knc}.jackingForce"] = chassis_force[:, 2]
    return result


def _run(
    monkeypatch: pytest.MonkeyPatch,
    tmp_path: Path,
    result: dict[str, np.ndarray],
) -> tuple[dict[str, Any], dict[str, str]]:
    class FakeRunner:
        def __init__(self, *args: Any, **kwargs: Any) -> None:
            pass

        def run(self, signals: Any, mode: Any, cases: Any, execution: Any = None) -> list[dict[str, Any]]:
            return [{"_status": "ok", **result}]

    vehicle = _vehicle()
    monkeypatch.setattr(fp, "_load_active_vehicle_yaml", lambda: vehicle)
    monkeypatch.setattr(fp, "ModelicaRunner", FakeRunner)
    metrics_csv = tmp_path / "metrics.csv"
    out = fp.FourPostEvalSim(_config(metrics_csv)).run()
    with metrics_csv.open(newline="", encoding="utf-8") as f:
        rows = {row["metric"]: row["value"] for row in csv.DictReader(f)}
    return out, rows


def test_static_balance_error_is_measured_contact_load_minus_target(
    monkeypatch: pytest.MonkeyPatch, tmp_path: Path
) -> None:
    out, _ = _run(monkeypatch, tmp_path, _rig_result(front_left_offset_n=12.0))
    summary = out["summary"]

    assert summary["static_balance_max_abs_fz_error_n"] == pytest.approx(12.0, abs=1e-6)
    assert summary["static_balance_max_abs_fz_error_pct"] == pytest.approx(100.0 * 12.0 / TARGET_N, abs=1e-6)
    assert out["setup"]["front"]["left"]["static_fz_N"] == pytest.approx(TARGET_N + 12.0, abs=1e-6)
    assert summary["static_equilibrium_pass"] is True
    assert summary["static_balance_pass"] is False


def test_zero_contact_load_fails_even_when_chassis_reaction_agrees(
    monkeypatch: pytest.MonkeyPatch, tmp_path: Path
) -> None:
    out, _ = _run(monkeypatch, tmp_path, _rig_result(contact_scale=0.0))
    summary = out["summary"]
    front_left = out["setup"]["front"]["left"]

    assert front_left["spring_force_N"] == pytest.approx(TARGET_N, rel=1e-9)
    assert front_left["static_fz_N"] == pytest.approx(0.0, abs=1e-9)
    assert summary["static_balance_max_abs_fz_error_n"] == pytest.approx(TARGET_N, rel=1e-9)
    assert summary["static_equilibrium_pass"] is True
    assert summary["static_balance_pass"] is False


def test_closure_is_checked_on_every_zero_command_row(monkeypatch: pytest.MonkeyPatch, tmp_path: Path) -> None:
    drift = 0.0255
    out, rows = _run(monkeypatch, tmp_path, _rig_result(front_drift_n_per_s=drift))
    summary = out["summary"]

    assert summary["static_balance_pass"] is False
    assert summary["static_equilibrium_worst_time_s"] == pytest.approx(fp.FOUR_POST_STOP_TIME_S)
    assert summary["static_equilibrium_max_force_residual_n"] == pytest.approx(drift * fp.FOUR_POST_STOP_TIME_S)
    assert summary["static_equilibrium_rows"] > 4
    assert summary["static_equilibrium_pass"] is False
    assert summary["static_balance_status"] == "fail"
    assert summary["static_balance_max_abs_fz_error_n"] == pytest.approx(0.0, abs=1e-9)
    assert rows["static_balance_pass"] == "False"
    assert "static_balance_pass" not in out["metric_status"]


def test_ramp_end_rows_close_but_stay_out_of_corner_loads(monkeypatch: pytest.MonkeyPatch, tmp_path: Path) -> None:
    out, _ = _run(monkeypatch, tmp_path, _rig_result(ramp_end_split_n=7.0))
    summary = out["summary"]

    assert summary["static_balance_max_abs_fz_error_n"] == pytest.approx(0.0, abs=1e-9)
    assert summary["static_equilibrium_pass"] is True
    assert summary["static_balance_status"] == "pass"
    assert summary["static_balance_pass"] is True


def test_spring_force_that_misses_the_executed_free_length_fails(
    monkeypatch: pytest.MonkeyPatch, tmp_path: Path
) -> None:
    out, _ = _run(monkeypatch, tmp_path, _rig_result(spring_offset_n=130.0))
    summary = out["summary"]

    assert summary["static_balance_pass"] is False
    assert summary["static_spring_max_residual_n"] == pytest.approx(130.0, abs=1e-6)


def test_missing_executed_signals_make_static_balance_unavailable(
    monkeypatch: pytest.MonkeyPatch, tmp_path: Path
) -> None:
    result = {key: value for key, value in _rig_result().items() if "sprungLoads" not in key}
    out, rows = _run(monkeypatch, tmp_path, result)
    summary = out["summary"]

    assert rows["static_balance_pass"] == ""
    assert summary["static_balance_status"] == "unavailable"
    assert "frChassisActuator.sprungLoads.frame_a.f[1]" in summary["static_balance_reason"]
    assert rows["static_balance_status"] == "unavailable"
    assert rows["static_balance_max_abs_fz_error_n"] == ""

    status = {metric: status for metric, (_, status) in read_metric_status(tmp_path / "metrics.csv").items()}
    for key in ("static_balance_pass", "static_balance_max_abs_fz_error_n", "static_equilibrium_rows"):
        assert status[key] == "unavailable", key
        assert out["metric_status"][key] == "unavailable", key
    assert status["static_balance_status"] == "ok"


@pytest.mark.parametrize(
    ("length_m", "expected_n"),
    (
        (0.195, 50.0),
        (0.205, -50.0),
        (0.185, 200.0),
        (0.175, 400.0),
        (0.215, -150.0),
    ),
)
def test_spring_force_uses_the_signed_deflection_like_boblib(length_m: float, expected_n: float) -> None:
    from simulations.response.mbd.four_post import static_balance

    table = np.array([[0.0, 0.0], [0.01, 100.0], [0.02, 300.0]])

    assert static_balance.spring_force(table, 0.20, length_m) == pytest.approx(expected_n)
