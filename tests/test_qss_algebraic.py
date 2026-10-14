from dataclasses import replace

import numpy as np
import pytest

from engines.dynpy import Vehicle, solve_acceleration_trim
from engines.dynpy.qss import _algebraic_residual, _algebraic_slip_slopes, _generalized_acceleration_target
from simulations.envelope.ggv.ggv_generation import _solve_envelope_limit, _solve_racing_trim, solve_ax_limit
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
@pytest.mark.parametrize("dof", (3, 6, 10, 14))
def test_boundary_preserves_equilibrium_and_tire_domain(vehicle, mode, ay, dof):
    model = vehicle.model(dof)
    projection = project_vehicle_yaml(load_vehicle_yaml()).ggv
    result = _solve_envelope_limit(
        projection, model, speed=10., ay=ay, ax_bounds=(-31.4, 27.5), mode=mode,
        max_abs_beta_rad=.25, max_abs_steering_rad=.5, enforce_tire_load_range=True,
    )
    if result is None and mode != "lateral":
        ax = solve_ax_limit(
            projection, speed=10., ay=ay, ax_grid=np.array([-31.4, 27.5]), mode=mode,
            reduced_model=model, max_abs_beta_rad=.25, max_abs_steering_rad=.5,
            enforce_tire_load_range=True, trim_multistart=False,
        )
        assert np.isfinite(ax)
        result = _solve_racing_trim(
            model, speed_mps=10., longitudinal_acceleration_mps2=ax, lateral_acceleration_mps2=ay,
            initial_unknowns=None, max_abs_beta_rad=.25, max_abs_steering_rad=.5,
            enforce_tire_load_range=True, trim_multistart=False,
        )
    assert result is not None
    if mode == "lateral" and dof in (6, 10):
        assert np.min(result.output.normal_loads_n) < 1., "Temporary continuation bounds must be released."
    np.testing.assert_allclose(_algebraic_residual(model, result.inputs, result.output), 0., atol=1e-3)
    target = _generalized_acceleration_target(
        model, result.state, result.output,
        longitudinal_mps2=result.path_longitudinal_acceleration_mps2,
        lateral_mps2=result.path_lateral_acceleration_mps2,
        acceleration_frame="path",
    )
    np.testing.assert_allclose(result.output.generalized_acceleration, target, atol=1e-5)
    if dof >= 10:
        forward = model.evaluate(result.state, result.inputs)
        np.testing.assert_allclose(forward.generalized_acceleration, target, atol=1e-4)
    if mode != "lateral":
        assert result.path_lateral_acceleration_mps2 == pytest.approx(ay, abs=1e-5)
    for load, alpha, slip, tire in zip(
        result.output.normal_loads_n, result.output.slip_angles_rad, result.output.slip_ratios, model.parameters.tires,
    ):
        assert 0. < load <= tire.fz_max_n + 1e-8
        assert tire.slip_in_fit_range(alpha, slip)
    if dof < 10:
        assert np.all(_algebraic_slip_slopes(model, result.output) >= -1e-4)
    if mode == "drive":
        required_force = np.sum(result.inputs.wheel_torques_nm / np.asarray(model.parameters.wheel_radius_m))
        assert required_force <= projection.max_drive_force + 1e-4
    if dof == 3 and mode == "brake" and ay == 0.:
        # The former binary solver returned -22.62 with its looser torque closure.
        assert result.longitudinal_acceleration_mps2 == pytest.approx(-22.584, abs=.005)


def test_planar_boundary_honors_finite_brake_cap(vehicle):
    projection = replace(project_vehicle_yaml(load_vehicle_yaml()).ggv, max_brake_force=1000.)
    result = _solve_envelope_limit(
        projection, vehicle.model(3), speed=10., ay=0., ax_bounds=(-31.4, 0.), mode="brake",
        max_abs_beta_rad=.25, max_abs_steering_rad=.5, enforce_tire_load_range=True,
    )
    assert result is not None
    force = np.sum(result.inputs.wheel_torques_nm / np.asarray(vehicle.model(3).parameters.wheel_radius_m))
    assert -force == pytest.approx(1000., abs=1e-4)


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
def test_rejected_direct_boundary_forwards_branch_audit_setting(vehicle, monkeypatch, multistart):
    from simulations.envelope.ggv import ggv_generation as ggv

    attempts = []

    def audit(*args, **kwargs):
        attempts.append(kwargs["trim_multistart"])
        return .123

    monkeypatch.setattr(ggv, "_solve_ax_limit_qss", audit)
    monkeypatch.setattr(ggv, "_solve_envelope_limit", lambda *args, **kwargs: None)
    value = ggv.solve_ax_limit(
        project_vehicle_yaml(load_vehicle_yaml()).ggv, reduced_model=vehicle.model(3),
        speed=25., ay=20.5, ax_grid=np.array([0., 27.5]), mode="drive", trim_multistart=multistart,
    )
    assert attempts == [multistart]
    assert value == .123


def test_14dof_envelope_uses_direct_boundaries(vehicle, monkeypatch):
    from simulations.envelope.ggv import ggv_generation as ggv

    def nested_search(*args, **kwargs):
        pytest.fail("A converged direct boundary must not repeat the nested trim search.")

    monkeypatch.setattr(ggv, "_solve_racing_trim", nested_search)
    envelopes = ggv.generate_ggv(
        project_vehicle_yaml(load_vehicle_yaml()).ggv,
        ggv.GGVConfig(speeds=(5.,), model_dof=14, ay_points=3, ay_max_g=4., trim_multistart=True, verbose=False),
        reduced_model=vehicle.model(14),
    )
    assert len(envelopes) == 1
    assert np.isfinite(envelopes[0].ax_accel).any()


def test_lateral_search_cap_is_not_reported_as_a_closed_envelope(vehicle, monkeypatch):
    from simulations.envelope.ggv import ggv_generation as ggv

    monkeypatch.setattr(ggv, "solve_lateral_limit", lambda *args, **kwargs: (kwargs["ay_upper"], 0.))
    with pytest.raises(RuntimeError, match="Increase ay_max_g"):
        ggv.generate_ggv(
            project_vehicle_yaml(load_vehicle_yaml()).ggv,
            ggv.GGVConfig(speeds=(10.,), model_dof=3, ay_points=3, verbose=False),
            reduced_model=vehicle.model(3),
        )


@pytest.mark.parametrize("dof", (3, 6, 14))
@pytest.mark.parametrize("ax,ay", ((2., 4.), (-4., 6.)))
def test_trim_forward_jacobian_matches_centered_reference(vehicle, monkeypatch, dof, ax, ay):
    from engines.dynpy import qss

    model = vehicle.model(dof)
    kwargs = dict(speed_mps=12., longitudinal_acceleration_mps2=ax,
                  lateral_acceleration_mps2=ay, yaw_rate_radps=ay / 12., acceleration_frame="path")
    actual = solve_acceleration_trim(model, **kwargs)
    original = qss.least_squares

    def centered(*args, **options):
        options["jac"] = "3-point"
        return original(*args, **options)

    monkeypatch.setattr(qss, "least_squares", centered)
    reference = solve_acceleration_trim(model, **kwargs)
    assert actual.success and reference.success
    assert actual.residual_norm < 1e-6
    np.testing.assert_allclose(actual.state, reference.state, atol=1e-6, rtol=0)
    np.testing.assert_allclose(actual.output.normal_loads_n, reference.output.normal_loads_n, atol=1e-4, rtol=0)
