"""Independent force inversion at a coupled GGV load equilibrium."""

from dataclasses import replace

import numpy as np
import pytest

from engines.dynpy import Vehicle
from engines.dynpy.qss import QSSResult, _algebraic_residual, _trim_state_and_inputs
from simulations.envelope.ggv import ggv_generation as ggv
from simulations.envelope.vehicle_yaml import load_vehicle_yaml, project_vehicle_yaml


@pytest.fixture(scope="module")
def vehicle():
    return Vehicle.from_yaml()


@pytest.fixture(params=[
    (3.0339375, [.08127593746751156, .011949136053417462, -1097.3396283334337],
     [1099.5210939641, 1148.0423198902045, 142.88274872158595, 203.83162832341282],
     [-.06234240696544748, -.0824486517881956, -.07328256311424661, -.038537168038737434]),
    (3.17184375, [.08600051279069058, .012546096570396875, -1083.681356518611],
     [1093.4669445579875, 1144.329837570581, 146.2953475673324, 210.18566120339926],
     [-.060682119583598045, -.08251981980547325, -.06433856632511935, -.03653720874990535]),
])
def near_peak(vehicle, request):
    ay, controls, loads, slips = request.param
    model = vehicle.model(3)
    state, inputs = _trim_state_and_inputs(model, np.array(controls), speed_mps=5.,
                                          yaw_rate_radps=ay / 5., rack_input=True)
    output = model.evaluate(state, inputs, normal_loads_n=loads, algebraic_slips=slips)
    steering = float(np.mean(output.toe_rad[:2]))
    inputs = replace(inputs, steering_rad=steering)
    return model, QSSResult(True, "Coupled equilibrium", 0., state, inputs, output,
                           {"beta_rad": controls[0], "steering_rad": steering}, 5., ay / 5.)


def racing_check(model, trim):
    return ggv._solve_racing_trim(
        model, speed_mps=trim.speed_mps,
        longitudinal_acceleration_mps2=trim.path_longitudinal_acceleration_mps2,
        lateral_acceleration_mps2=trim.path_lateral_acceleration_mps2,
        initial_unknowns=None, max_abs_beta_rad=.25, max_abs_steering_rad=.5,
        enforce_tire_load_range=True, trim_multistart=False,
    )


def test_independent_inverse_accepts_coupled_root_despite_static_start_saturation(near_peak, monkeypatch):
    model, trim = near_peak
    inverse = model.evaluate(trim.state, trim.inputs, normal_loads_n=trim.output.normal_loads_n)
    np.testing.assert_allclose(inverse.slip_ratios, trim.output.slip_ratios, atol=1e-10)
    np.testing.assert_allclose(_algebraic_residual(model, trim.inputs, inverse), 0., atol=1e-7)
    static_start = model.evaluate(trim.state, trim.inputs)
    np.testing.assert_allclose(static_start.normal_loads_n, trim.output.normal_loads_n, atol=1e-6)
    np.testing.assert_allclose(static_start.generalized_acceleration, trim.output.generalized_acceleration, atol=1e-7)
    np.testing.assert_allclose(_algebraic_residual(model, trim.inputs, static_start), 0., atol=1e-7)
    np.testing.assert_allclose(model.derivative(0., trim.state, trim.inputs), trim.output.derivative, atol=1e-7)
    monkeypatch.setattr(ggv, 'solve_acceleration_trim', lambda *args, **kwargs: trim)
    assert racing_check(model, trim) is trim


@pytest.mark.parametrize('bad_equilibrium', ['loads', 'slip'])
def test_independent_inverse_rejects_bad_loads_and_slips(near_peak, bad_equilibrium, monkeypatch):
    model, trim = near_peak
    if bad_equilibrium == 'loads':
        # Inversion is self-consistent at these loads, but the load equations are not.
        output = model.evaluate(trim.state, trim.inputs, normal_loads_n=trim.output.normal_loads_n + 10.)
    else:
        slips = trim.output.slip_ratios.copy()
        slips[1] -= .02
        output = model.evaluate(trim.state, trim.inputs, normal_loads_n=trim.output.normal_loads_n,
                                algebraic_slips=slips)
    bad = replace(trim, output=output)
    monkeypatch.setattr(ggv, 'solve_acceleration_trim', lambda *args, **kwargs: bad)
    assert racing_check(model, bad) is None


@pytest.mark.parametrize('ay', [3.0339375, 3.17184375])
def test_optimizer_accepts_near_peak_coupled_equilibrium(vehicle, ay, monkeypatch):
    def unnecessary_repair(*args, **kwargs):
        pytest.fail('A validated coupled equilibrium should not need boundary repair.')

    monkeypatch.setattr(ggv, '_consistent_boundary', unnecessary_repair)
    model = vehicle.model(3)
    trim = ggv._solve_envelope_limit(
        project_vehicle_yaml(load_vehicle_yaml()).ggv, model, speed=5., ay=ay,
        ax_bounds=(-3.2 * ggv.G, 2.8 * ggv.G), mode='brake',
        max_abs_beta_rad=.25, max_abs_steering_rad=.5, enforce_tire_load_range=True,
    )
    assert trim is not None
    inverse = model.evaluate(trim.state, trim.inputs, normal_loads_n=trim.output.normal_loads_n)
    force_scale = model.parameters.mass_kg * ggv.G / 4.
    assert np.linalg.norm(_algebraic_residual(model, trim.inputs, inverse)) / force_scale < 1e-5
    np.testing.assert_allclose(inverse.generalized_acceleration, trim.output.generalized_acceleration, atol=1e-5)


@pytest.mark.parametrize('failure', [None, 'status', 'nonfinite', 'residual'])
def test_direct_continuation_precedes_damped_retry(vehicle, monkeypatch, failure):
    from types import SimpleNamespace

    model = vehicle.model(3)
    arguments = dict(speed=5., ay=3.0339375, ax_bounds=(-3.2 * ggv.G, 2.8 * ggv.G), mode='brake',
                     max_abs_beta_rad=.25, max_abs_steering_rad=.5, enforce_tire_load_range=True)
    parameters = project_vehicle_yaml(load_vehicle_yaml()).ggv
    seed = ggv._solve_envelope_limit(parameters, model, **arguments)
    assert seed is not None
    optimizer = ggv.minimize
    guesses = []

    def inspected(fun, guess, **kwargs):
        guesses.append(guess.copy())
        if len(guesses) == 1 and failure:
            values = guess.copy()
            if failure == 'nonfinite':
                values[0] = np.nan
            elif failure == 'residual':
                values[0] += .01
            return SimpleNamespace(success=failure != 'status', x=values)
        return optimizer(fun, guess, **kwargs)

    monkeypatch.setattr(ggv, 'minimize', inspected)
    result = ggv._solve_envelope_limit(parameters, model, initial_unknowns=seed.unknowns, **arguments)
    assert result is not None
    force_scale = model.parameters.mass_kg * ggv.G / 4.
    torque_scale = force_scale * np.mean(model.parameters.wheel_radius_m)
    assert guesses[0][2] * torque_scale == pytest.approx(seed.unknowns['total_wheel_torque_nm'])
    assert len(guesses) == (2 if failure else 1)
    if failure:
        expected = guesses[0].copy()
        expected[2] *= .9
        expected[7:11] *= .9
        np.testing.assert_array_equal(guesses[1], expected)


def test_dense_planar_tail_uses_neighbor_boundary_without_full_trim_search(vehicle, monkeypatch):
    def unnecessary_search(*args, **kwargs):
        pytest.fail('Neighbor continuation should recover this envelope without a full trim search.')

    monkeypatch.setattr(ggv, '_solve_ax_limit_qss', unnecessary_search)
    envelope = ggv.generate_ggv(
        project_vehicle_yaml(load_vehicle_yaml()).ggv,
        ggv.GGVConfig(speeds=(5.,), ay_points=321, ay_max_g=4.5, trim_multistart=True,
                      include_left_right=False, verbose=False, warn_tire_load_range=False),
        reduced_model=vehicle.model(3),
    )[0]
    assert np.all(np.isfinite(envelope.ax_accel))
    assert np.all(np.isfinite(envelope.ax_brake))
    assert np.all(envelope.ax_accel >= envelope.ax_brake - 1e-5)
    assert envelope.ay[-1] > 7.
    assert envelope.ax_accel[-1] == envelope.ax_brake[-1]


def test_ggv_allows_low_load_extension_with_every_wheel_in_contact(vehicle):
    model = vehicle.model(3)
    result = ggv._solve_envelope_limit(
        project_vehicle_yaml(load_vehicle_yaml()).ggv, model, speed=15., ay=15.,
        ax_bounds=(-3.2 * ggv.G, 2.8 * ggv.G), mode='brake',
        max_abs_beta_rad=.25, max_abs_steering_rad=.5, enforce_tire_load_range=True,
    )
    assert result is not None and result.success
    loads = result.output.normal_loads_n
    assert np.all(loads > 0.)
    assert any(load < tire.fz_min_n for load, tire in zip(loads, model.parameters.tires))
    assert all(load <= tire.fz_max_n for load, tire in zip(loads, model.parameters.tires))
    inverse = model.evaluate(result.state, result.inputs, normal_loads_n=loads)
    np.testing.assert_allclose(_algebraic_residual(model, result.inputs, inverse), 0., atol=1e-4)


@pytest.mark.parametrize('dof', (3, 6, 14))
@pytest.mark.parametrize('load', (0., -1.))
@pytest.mark.parametrize('enforce_range', (False, True))
def test_ggv_rejects_lifted_wheel_even_without_fit_range_check(vehicle, dof, load, enforce_range):
    from engines.dynpy import solve_acceleration_trim

    model = vehicle.model(dof)
    trim = solve_acceleration_trim(model, speed_mps=12., longitudinal_acceleration_mps2=0.,
                                   lateral_acceleration_mps2=0.)
    assert trim.success
    loads = trim.output.normal_loads_n.copy()
    loads[0] = load
    trim = replace(trim, output=replace(trim.output, normal_loads_n=loads))
    assert not ggv._trim_is_racing_feasible(
        trim, model=model, ay=0., max_abs_beta_rad=.25, max_abs_steering_rad=.5,
        enforce_tire_load_range=enforce_range,
    )
