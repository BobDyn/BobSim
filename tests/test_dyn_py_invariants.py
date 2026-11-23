"""Physics invariants of the reduced-order models that no fit can satisfy by accident.

The rest of the dynpy suite checks that each model closes its own equations.
These tests check the answers against things that are true of any car:

* a symmetric car turning left is the mirror image of it turning right;
* static axle loads follow the lever rule from vehicle.yml, computed here
  without the model's own mass aggregation;
* steady cornering transfers ``m * ay * h`` of roll moment and accelerating
  transfers ``m * ax * h`` of pitch moment;
* stiffening one end of the car moves load transfer toward that end;
* more tire grip never lowers the lateral limit;
* the rigid 3DOF car closes roll and pitch at the contact patches its own
  kinematics report, and every massless wheel puts down exactly the torque
  it is given, near the grip limit as well as at cruise.

A sign flip, a swapped corner index or a dropped term breaks at least one of
these while every closure test still passes.
"""

from __future__ import annotations

import copy
import dataclasses
import warnings
from pathlib import Path
from typing import Any

import numpy as np
import pytest
import yaml

from common.vehicle_io import load_yaml, vehicle_yaml_path
from engines.dynpy import create_model, load_reduced_vehicle_parameters, solve_acceleration_trim
from engines.dynpy.models import DOFModel
from engines.dynpy.parameters import G, ReducedVehicleParameters
from engines.dynpy.tire import MF52Tire

# FL, FR, RL, RR -> FR, FL, RR, RL
MIRROR = [1, 0, 3, 2]
DOFS = (3, 6, 10, 14)
SPEED_MPS = 15.0

# MF5.2 terms that make a tire pull to one side. With them zeroed the fit is
# odd in slip angle, so any remaining left/right difference comes from the
# vehicle model, not the tire.
ASYMMETRIC_TIRE_TERMS = (
    "PHY1", "PHY2", "PVY1", "PVY2", "PEY3",
    "RVY1", "RVY2", "RBY3", "RHX1",
    "QHZ1", "QHZ2", "QDZ6", "QDZ7", "QEZ4", "QSX1", "SSZ2",
)


def _symmetric_tire(tire: MF52Tire) -> MF52Tire:
    coefficients = dict(tire.coefficients)
    for name in ASYMMETRIC_TIRE_TERMS:
        coefficients[name] = 0.0
    return MF52Tire(coefficients)


def _write(tmp_path: Path, data: dict[str, Any], name: str) -> Path:
    path = tmp_path / name
    path.write_text(yaml.safe_dump(data, sort_keys=False), encoding="utf-8")
    return path


def _centered_vehicle() -> dict[str, Any]:
    data = copy.deepcopy(load_yaml(vehicle_yaml_path()))
    data["sprung_mass"]["cg_m"][1] = 0.0
    data["driver_mass"]["cg_m"][1] = 0.0
    return data


def _load(path: Path) -> ReducedVehicleParameters:
    """Project a vehicle with tires that do not pull, so physics alone sets the answer."""

    with warnings.catch_warnings():
        warnings.simplefilter("ignore", RuntimeWarning)
        params = load_reduced_vehicle_parameters(path)
    return dataclasses.replace(
        params,
        front_tire=_symmetric_tire(params.front_tire),
        rear_tire=_symmetric_tire(params.rear_tire),
    )


@pytest.fixture(scope="module")
def symmetric(tmp_path_factory) -> ReducedVehicleParameters:
    return _load(_write(tmp_path_factory.mktemp("symmetric"), _centered_vehicle(), "vehicle.yml"))


@pytest.fixture(scope="module")
def no_aero_data() -> dict[str, Any]:
    data = _centered_vehicle()
    data.pop("aero")
    return data


@pytest.fixture(scope="module")
def no_aero(tmp_path_factory, no_aero_data) -> ReducedVehicleParameters:
    return _load(_write(tmp_path_factory.mktemp("no_aero"), no_aero_data, "vehicle.yml"))


def _trim(params: ReducedVehicleParameters, dof: DOFModel, *, ax: float = 0.0, ay: float = 0.0):
    result = solve_acceleration_trim(
        create_model(dof, params),
        speed_mps=SPEED_MPS,
        longitudinal_acceleration_mps2=ax,
        lateral_acceleration_mps2=ay,
    )
    assert result.success, result.message
    return result


def _yaml_mass_properties(data: dict[str, Any]) -> tuple[float, np.ndarray]:
    """Total mass and CG summed straight from vehicle.yml, both sides."""

    items = [(data[name]["mass_kg"], data[name]["cg_m"]) for name in ("sprung_mass", "driver_mass")]
    for axle in ("front", "rear"):
        for section in data[axle]["masses"].values():
            x, y, z = section["cg_m"]
            items += [(section["mass_kg"], (x, y, z)), (section["mass_kg"], (x, -y, z))]
    mass = float(sum(m for m, _ in items))
    cg = sum(m * np.asarray(c, dtype=float) for m, c in items) / mass
    return mass, cg


def _yaml_contact_points(data: dict[str, Any]) -> np.ndarray:
    """Contact points under each wheel center at design ride height, FL FR RL RR."""

    points = []
    for axle in ("front", "rear"):
        x, y, z = data[axle]["suspension"]["wheel_center_m"]
        ground = z - data[axle]["wheel"]["radius_m"]
        points += [(x, y, ground), (x, -y, ground)]
    return np.asarray(points, dtype=float)


def _lateral_transfer(loads: np.ndarray) -> tuple[float, float]:
    """Right-minus-left load on each axle; positive in a left turn."""

    return float(loads[1] - loads[0]), float(loads[3] - loads[2])


def _front_lltd(params: ReducedVehicleParameters, loads: np.ndarray) -> float:
    front, rear = _lateral_transfer(loads)
    front_moment = front * params.track_front_m
    return front_moment / (front_moment + rear * params.track_rear_m)


def test_symmetrized_tire_is_odd_in_slip_angle(symmetric):
    """Guard for the mirror tests: the tire itself has no preferred side."""

    for tire in (symmetric.front_tire, symmetric.rear_tire):
        alpha = np.linspace(0.005, 0.12, 9)
        for kappa in (0.0, 0.04, -0.06):
            fx_l, fy_l, mx_l, my_l, mz_l = tire.evaluate(900.0, alpha, kappa, 0.0, SPEED_MPS)
            fx_r, fy_r, mx_r, my_r, mz_r = tire.evaluate(900.0, -alpha, kappa, 0.0, SPEED_MPS)
            np.testing.assert_allclose(fx_r, fx_l, atol=1e-9)
            np.testing.assert_allclose(fy_r, -fy_l, atol=1e-9)
            np.testing.assert_allclose(mz_r, -mz_l, atol=1e-9)
            np.testing.assert_allclose(mx_r, -mx_l, atol=1e-9)
            np.testing.assert_allclose(my_r, my_l, atol=1e-9)


@pytest.mark.parametrize("dof", DOFS)
@pytest.mark.parametrize("ax", (0.0, 4.0, -8.0))
def test_left_turn_mirrors_right_turn(symmetric, dof, ax):
    left = _trim(symmetric, dof, ax=ax, ay=10.0)
    right = _trim(symmetric, dof, ax=ax, ay=-10.0)

    # The residual asymmetry is the few-micrometer CG offset of the default
    # car and the solver tolerance; an index or sign bug is newtons.
    np.testing.assert_allclose(right.inputs.steering_rad, -left.inputs.steering_rad, atol=5e-5)
    np.testing.assert_allclose(right.unknowns["beta_rad"], -left.unknowns["beta_rad"], atol=5e-5)
    np.testing.assert_allclose(right.output.normal_loads_n[MIRROR], left.output.normal_loads_n, atol=0.1)
    forces_left = left.output.wheel_forces_body_n
    forces_right = right.output.wheel_forces_body_n[MIRROR]
    np.testing.assert_allclose(forces_right[:, 0], forces_left[:, 0], atol=0.5)
    np.testing.assert_allclose(forces_right[:, 1], -forces_left[:, 1], atol=0.5)
    if dof >= 6:
        np.testing.assert_allclose(right.unknowns["roll_rad"], -left.unknowns["roll_rad"], atol=1e-5)
        np.testing.assert_allclose(right.unknowns["pitch_rad"], left.unknowns["pitch_rad"], atol=1e-5)
    # And the turn loads the outside wheels.
    assert all(transfer > 0.0 for transfer in _lateral_transfer(left.output.normal_loads_n))


@pytest.mark.parametrize("dof", DOFS)
@pytest.mark.parametrize("ax", (0.0, 3.0, -6.0))
def test_straight_line_has_no_lateral_response(symmetric, dof, ax):
    result = _trim(symmetric, dof, ax=ax)
    loads = result.output.normal_loads_n
    forces = result.output.wheel_forces_body_n

    assert abs(result.inputs.steering_rad) < 1e-6
    assert abs(result.unknowns["beta_rad"]) < 1e-6
    assert abs(float(np.sum(forces[:, 1]))) < 1e-3
    np.testing.assert_allclose(loads[MIRROR], loads, atol=0.05)
    np.testing.assert_allclose(forces[MIRROR, 0], forces[:, 0], atol=0.05)
    if dof >= 6:
        assert abs(result.unknowns["roll_rad"]) < 1e-7


@pytest.mark.parametrize("dof", DOFS)
@pytest.mark.parametrize("lateral_offset_m", (0.0, 0.1))
def test_static_loads_follow_the_lever_rule_from_vehicle_yaml(tmp_path, no_aero_data, dof, lateral_offset_m):
    data = copy.deepcopy(no_aero_data)
    data["driver_mass"]["cg_m"][1] = lateral_offset_m
    params = _load(_write(tmp_path, data, "vehicle.yml"))
    mass, cg = _yaml_mass_properties(data)
    contacts = _yaml_contact_points(data)

    loads = _trim(params, dof).output.normal_loads_n
    weight = mass * G
    wheelbase = contacts[0, 0] - contacts[2, 0]
    front_expected = weight * (cg[0] - contacts[2, 0]) / wheelbase

    assert np.sum(loads) == pytest.approx(weight, rel=1e-6)
    # Rolling resistance at trim speed pitches a fraction of a newton forward.
    # Hanging sprung weight at the total CG instead moved ten newtons.
    assert loads[0] + loads[1] == pytest.approx(front_expected, rel=5e-4)
    # Roll equilibrium about the CG: the left/right split must carry m*g*y_cg.
    roll_moment = float(np.dot(contacts[:, 1] - cg[1], loads))
    # Contact patches migrate a fraction of a millimeter at static jounce.
    assert abs(roll_moment) < 1.0, roll_moment
    if lateral_offset_m:
        left = loads[0] + loads[2]
        right = loads[1] + loads[3]
        assert left > right


@pytest.mark.parametrize("dof", DOFS)
def test_cornering_transfers_m_ay_h_of_roll_moment(no_aero, no_aero_data, dof):
    mass, cg = _yaml_mass_properties(no_aero_data)
    contacts = _yaml_contact_points(no_aero_data)
    height = cg[2] - float(np.mean(contacts[:, 2]))
    ay = 8.0

    result = _trim(no_aero, dof, ay=ay)
    loads = result.output.normal_loads_n
    transfer_moment = -float(np.dot(contacts[:, 1] - cg[1], loads))
    # Tire overturning moments carry part of the roll moment themselves.
    tire_overturning = float(np.sum(result.output.wheel_moments_body_nm[:, 0]))
    expected = mass * result.lateral_acceleration_mps2 * height + tire_overturning

    # The rigid 3DOF car is exact to solver tolerance. Body roll moves the CG
    # outboard and the contact patches migrate, which two percent covers.
    tolerance = 1e-4 if dof == 3 else 0.02
    assert transfer_moment == pytest.approx(expected, rel=tolerance)


@pytest.mark.parametrize("dof", DOFS)
@pytest.mark.parametrize("ax", (4.0, -8.0))
def test_acceleration_transfers_m_ax_h_of_pitch_moment(no_aero, no_aero_data, dof, ax):
    mass, cg = _yaml_mass_properties(no_aero_data)
    contacts = _yaml_contact_points(no_aero_data)
    height = cg[2] - float(np.mean(contacts[:, 2]))
    wheelbase = contacts[0, 0] - contacts[2, 0]

    static = _trim(no_aero, dof).output.normal_loads_n
    result = _trim(no_aero, dof, ax=ax)
    front_change = float(np.sum(result.output.normal_loads_n[:2] - static[:2]))
    expected = -mass * result.longitudinal_acceleration_mps2 * height / wheelbase

    tolerance = 0.01 if dof == 3 else 0.06
    assert front_change == pytest.approx(expected, rel=tolerance)


def test_3dof_lltd_is_the_roll_stiffness_split(no_aero):
    params = no_aero
    springs = np.asarray(params.suspension_stiffness_n_per_m)
    front = 0.5 * springs[0] * params.track_front_m**2 + params.antiroll_stiffness_nm_per_rad[0]
    rear = 0.5 * springs[2] * params.track_rear_m**2 + params.antiroll_stiffness_nm_per_rad[1]

    loads = _trim(params, 3, ay=8.0).output.normal_loads_n
    assert _front_lltd(params, loads) == pytest.approx(front / (front + rear), abs=1e-3)


def _stiffer(params: ReducedVehicleParameters, knob: str, factor: float) -> ReducedVehicleParameters:
    arb = list(params.antiroll_stiffness_nm_per_rad)
    springs = list(params.suspension_stiffness_n_per_m)
    if knob == "front_arb":
        arb[0] = arb[0] * factor + 2000.0
    elif knob == "rear_arb":
        arb[1] = arb[1] * factor + 2000.0
    elif knob == "front_spring":
        springs[0] *= factor
        springs[1] *= factor
    elif knob == "rear_spring":
        springs[2] *= factor
        springs[3] *= factor
    return dataclasses.replace(
        params,
        antiroll_stiffness_nm_per_rad=(arb[0], arb[1]),
        suspension_stiffness_n_per_m=(springs[0], springs[1], springs[2], springs[3]),
    )


@pytest.mark.parametrize("dof", (3, 6, 14))
@pytest.mark.parametrize(
    ("knob", "front_share_rises"),
    (("front_arb", True), ("rear_arb", False), ("front_spring", True), ("rear_spring", False)),
)
def test_stiffening_one_end_moves_load_transfer_to_it(no_aero, dof, knob, front_share_rises):
    base = _trim(no_aero, dof, ay=8.0)
    stiff_params = _stiffer(no_aero, knob, 1.5)
    stiff = _trim(stiff_params, dof, ay=8.0)

    change = _front_lltd(stiff_params, stiff.output.normal_loads_n) - _front_lltd(
        no_aero, base.output.normal_loads_n
    )
    assert (change > 1e-3) if front_share_rises else (change < -1e-3), change
    if dof >= 6:
        # Any added roll stiffness rolls the car less.
        assert abs(stiff.unknowns["roll_rad"]) < abs(base.unknowns["roll_rad"])


def _scaled_grip(params: ReducedVehicleParameters, factor: float) -> ReducedVehicleParameters:
    def scale(tire: MF52Tire) -> MF52Tire:
        coefficients = dict(tire.coefficients)
        coefficients["LMUY"] = coefficients["LMUY"] * factor
        return MF52Tire(coefficients)

    return dataclasses.replace(params, front_tire=scale(params.front_tire), rear_tire=scale(params.rear_tire))


@pytest.mark.parametrize("dof", (3, 6))
def test_more_lateral_grip_holds_more_lateral_acceleration(no_aero, dof):
    """A trim that saturates the base tires is easy for grippier tires and out of reach for worse ones."""

    model = create_model(dof, no_aero)
    ay = 13.0
    base = solve_acceleration_trim(
        model, speed_mps=SPEED_MPS, longitudinal_acceleration_mps2=0.0, lateral_acceleration_mps2=ay,
    )
    assert base.success, base.message
    grippy = _trim(_scaled_grip(no_aero, 1.15), dof, ay=ay)
    # Same demand, more grip: every tire works at a smaller slip angle.
    assert np.all(np.abs(grippy.output.slip_angles_rad) < np.abs(base.output.slip_angles_rad))

    weak = solve_acceleration_trim(
        create_model(dof, _scaled_grip(no_aero, 0.5)),
        speed_mps=SPEED_MPS,
        longitudinal_acceleration_mps2=0.0,
        lateral_acceleration_mps2=ay,
    )
    # Half the grip cannot hold 13 m/s^2 on a car that peaks near 1.5 g.
    assert not weak.success


@pytest.fixture(scope="module")
def full_car() -> ReducedVehicleParameters:
    """The real vehicle, with aero and the fitted tires that pull."""

    with warnings.catch_warnings():
        warnings.simplefilter("ignore", RuntimeWarning)
        return load_reduced_vehicle_parameters(vehicle_yaml_path())


# Cruise, braking into a turn and power out of one, the last two near the limit.
HARD_DEMANDS = ((0.0, 4.0), (-9.0, 9.0), (6.0, -10.0))


@pytest.mark.parametrize(("ax", "ay"), HARD_DEMANDS)
def test_rigid_car_closes_roll_and_pitch_at_its_contact_patches(full_car, ax, ay):
    """No suspension means the contact patches alone react every roll and pitch moment."""

    result = solve_acceleration_trim(
        create_model(3, full_car),
        speed_mps=20.0,
        longitudinal_acceleration_mps2=ax,
        lateral_acceleration_mps2=ay,
    )
    assert result.success, result.message
    out = result.output
    # Steering and jounce move the patches off their nominal positions. The
    # balance has to hold at the moved ones, aero moment included.
    assert np.any(np.abs(out.contact_patch_positions_body_m - full_car.corner_positions) > 1e-5)
    scale = full_car.mass_kg * G * full_car.track_front_m
    np.testing.assert_allclose(out.body_moment_nm[:2], 0.0, atol=1e-7 * scale)


@pytest.mark.parametrize("dof", (3, 6))
@pytest.mark.parametrize(("ax", "ay"), HARD_DEMANDS)
def test_massless_wheels_put_down_exactly_their_torque(full_car, dof, ax, ay):
    """Without wheel spin states, tire Fx must equal (torque + rolling moment) / radius."""

    result = solve_acceleration_trim(
        create_model(dof, full_car),
        speed_mps=20.0,
        longitudinal_acceleration_mps2=ax,
        lateral_acceleration_mps2=ay,
    )
    assert result.success, result.message
    out = result.output
    forces = out.wheel_forces_body_n
    fx_heading = forces[:, 0] * np.cos(out.toe_rad) + forces[:, 1] * np.sin(out.toe_rad)
    torques = np.asarray(result.inputs.wheel_torques_nm, dtype=float)
    demand = (torques + out.wheel_moments_tire_nm[:, 1]) / np.asarray(full_car.wheel_radius_m)
    np.testing.assert_allclose(fx_heading, demand, atol=1e-6 * full_car.mass_kg * G / 4.0)


@pytest.mark.parametrize("dof", DOFS)
@pytest.mark.parametrize(("ax", "ay"), HARD_DEMANDS)
def test_simulator_sees_the_trim_it_was_handed(full_car, dof, ax, ay):
    """Evaluating a trimmed state without the trim's loads must land on the same car.

    The trim solves corner loads and slips as unknowns. The transient
    integrator only has the state, so the model has to close those loops on
    its own and reach the same loads and accelerations, near the limit too.
    """

    model = create_model(dof, full_car)
    trim = solve_acceleration_trim(
        model,
        speed_mps=20.0,
        longitudinal_acceleration_mps2=ax,
        lateral_acceleration_mps2=ay,
    )
    assert trim.success, trim.message
    free = model.evaluate(trim.state, trim.inputs)
    weight = full_car.mass_kg * G
    np.testing.assert_allclose(free.normal_loads_n, trim.output.normal_loads_n, atol=1e-6 * weight)
    np.testing.assert_allclose(
        free.generalized_acceleration, trim.output.generalized_acceleration, atol=1e-5
    )
