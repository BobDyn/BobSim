from dataclasses import replace

import numpy as np
import pytest

from engines.dynpy import Vehicle, solve_acceleration_trim
from engines.dynpy.qss import _algebraic_residual, _algebraic_slip_slopes
from simulations.envelope.ggv.ggv_generation import _solve_planar_limit, aero_loads, powertrain_force_limit
from simulations.envelope.vehicle_yaml import load_vehicle_yaml, project_vehicle_yaml


@pytest.fixture(scope="module")
def vehicle():
    return Vehicle.from_yaml()


@pytest.mark.parametrize("dof", (3, 6, 10, 14))
def test_trim_closes_shared_equations_without_nested_tire_inversion(vehicle, dof, monkeypatch):
    model = vehicle.model(dof)

    def no_inversion(*args, **kwargs):
        pytest.fail("QSS must evaluate tire forces directly from its slip unknowns.")

    with monkeypatch.context() as patch:
        patch.setattr(type(model.parameters.front_tire), "slip_for_force", no_inversion)
        result = solve_acceleration_trim(
            model, speed_mps=12., longitudinal_acceleration_mps2=2., lateral_acceleration_mps2=4.,
        )
    assert result.success, result.message
    assert result.inputs.rack_displacement_m is not None
    np.testing.assert_allclose(_algebraic_residual(model, result.inputs, result.output), 0., atol=1e-4)
    assert result.residual_norm < 1e-6
    # The ordinary transient force path must reproduce the solved state.
    forward = model.evaluate(result.state, result.inputs)
    np.testing.assert_allclose(forward.generalized_acceleration, result.output.generalized_acceleration, atol=1e-4)
    np.testing.assert_allclose(forward.normal_loads_n, result.output.normal_loads_n, atol=1e-3)


def test_steering_inversion_is_only_used_for_initial_seed_and_bounds(vehicle, monkeypatch):
    model = vehicle.model(3)
    evaluator = model.parameters.kinematics
    original = type(evaluator).rack_from_steering
    angles = []

    def counted(self, angle):
        angles.append(angle)
        return original(self, angle)

    monkeypatch.setattr(type(evaluator), "rack_from_steering", counted)
    result = solve_acceleration_trim(
        model, speed_mps=12., longitudinal_acceleration_mps2=2., lateral_acceleration_mps2=4.,
    )
    assert result.success
    assert len(angles) == 3
    heading = np.mean(evaluator.at(np.zeros(4), result.inputs.rack_displacement_m).toe_rad[:2])
    assert result.inputs.steering_rad == pytest.approx(heading)


@pytest.mark.parametrize("argument,value", [
    ("normal_loads_n", [100., 100., -1., 100.]),
    ("normal_loads_n", [100., 100., np.nan, 100.]),
    ("normal_loads_n", [100., 100.]),
    ("algebraic_slips", [0., np.inf, 0., 0.]),
    ("algebraic_slips", [0.]),
])
def test_trial_wheel_states_reject_invalid_values(vehicle, argument, value):
    model = vehicle.model(3)
    with pytest.raises(ValueError):
        model.evaluate(model.initial_state(10.), **{argument: value})


@pytest.mark.parametrize("mode,ay", [("drive", 0.), ("drive", 8.), ("brake", 0.), ("brake", 8.), ("lateral", 30.)])
def test_planar_boundary_preserves_equilibrium_and_tire_domain(vehicle, mode, ay):
    model = vehicle.model(3)
    projection = project_vehicle_yaml(load_vehicle_yaml()).ggv
    result = _solve_planar_limit(
        projection, model, speed=10., ay=ay, ax_bounds=(-31.4, 27.5), mode=mode,
        max_abs_beta_rad=.25, max_abs_steering_rad=.5, enforce_tire_load_range=True,
    )
    assert result is not None
    np.testing.assert_allclose(_algebraic_residual(model, result.inputs, result.output), 0., atol=1e-3)
    assert abs(result.output.generalized_acceleration[2]) < 1e-5
    if mode != "lateral":
        assert result.lateral_acceleration_mps2 == pytest.approx(ay, abs=1e-5)
    for load, alpha, slip, tire in zip(
        result.output.normal_loads_n, result.output.slip_angles_rad, result.output.slip_ratios, model.parameters.tires,
    ):
        assert tire.fz_min_n - 1e-8 <= load <= tire.fz_max_n + 1e-8
        assert tire.slip_in_fit_range(alpha, slip)
    assert np.all(_algebraic_slip_slopes(model, result.output) >= -1e-4)
    if mode == "drive":
        drag = aero_loads(projection, 10.)[2]
        required_force = projection.mass * result.longitudinal_acceleration_mps2 + drag
        assert required_force <= powertrain_force_limit(projection, 10.) + 1e-4
    if mode == "brake" and ay == 0.:
        # The former binary solver returned -22.62 with its looser torque closure.
        assert result.longitudinal_acceleration_mps2 == pytest.approx(-22.584, abs=.005)


def test_planar_boundary_honors_finite_brake_cap(vehicle):
    projection = replace(project_vehicle_yaml(load_vehicle_yaml()).ggv, max_brake_force=1000.)
    result = _solve_planar_limit(
        projection, vehicle.model(3), speed=10., ay=0., ax_bounds=(-31.4, 0.), mode="brake",
        max_abs_beta_rad=.25, max_abs_steering_rad=.5, enforce_tire_load_range=True,
    )
    assert result is not None
    drag = aero_loads(projection, 10.)[2]
    assert -(projection.mass * result.longitudinal_acceleration_mps2 + drag) == pytest.approx(1000., abs=1e-4)


def test_unreachable_steering_bound_does_not_reject_reachable_trim(vehicle, monkeypatch):
    evaluator = vehicle.model(3).parameters.kinematics
    original = type(evaluator).rack_from_steering

    def limited(self, angle):
        if abs(angle) > .5:
            raise ValueError("Unreachable rack pose")
        return original(self, angle)

    monkeypatch.setattr(type(evaluator), "rack_from_steering", limited)
    result = solve_acceleration_trim(
        vehicle.model(3), speed_mps=12., longitudinal_acceleration_mps2=2., lateral_acceleration_mps2=4.,
    )
    assert result.success, result.message


@pytest.mark.parametrize("multistart", (False, True))
def test_negative_drive_maximum_preserves_optional_branch_audit(vehicle, monkeypatch, multistart):
    from simulations.envelope.ggv import ggv_generation as ggv

    attempts = []

    def audit(*args, **kwargs):
        attempts.append(kwargs["trim_multistart"])
        return .123

    monkeypatch.setattr(ggv, "_solve_ax_limit_qss", audit)
    value = ggv.solve_ax_limit(
        project_vehicle_yaml(load_vehicle_yaml()).ggv, reduced_model=vehicle.model(3),
        speed=25., ay=20.5, ax_grid=np.array([0., 27.5]), mode="drive", trim_multistart=multistart,
    )
    if multistart:
        assert attempts == [True]
        assert value == .123
    else:
        assert not attempts
        assert np.isnan(value)
