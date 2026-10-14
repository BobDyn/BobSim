"""Automatic GGV search bounds do not define the vehicle's envelope."""

from dataclasses import replace
from types import SimpleNamespace

import numpy as np
import pytest

from simulations.envelope.ggv import ggv_generation as ggv


def config(**kwargs):
    return ggv.GGVConfig(speeds=(10.,), ay_points=5, verbose=False, warn_tire_load_range=False,
                         include_left_right=False, **kwargs)


@pytest.mark.parametrize('fallback', (False, True))
@pytest.mark.parametrize('drive_limit', (8., -8.))
def test_weak_initial_bounds_expand_to_same_envelope(monkeypatch, fallback, drive_limit):
    monkeypatch.setattr(ggv, 'solve_lateral_limit', lambda *args, **kw: (min(12., kw['ay_upper']), -2.))
    calls = []

    def boundary(*args, **kw):
        calls.append(kw)
        lo, hi = kw.get('ax_bounds', kw.get('ax_grid'))
        target = drive_limit if kw['mode'] == 'drive' else -12.
        value = float(np.clip(target, lo, hi))
        if 'ax_grid' in kw:
            return value
        return SimpleNamespace(success=True, unknowns={'ax': value}, path_longitudinal_acceleration_mps2=value)

    monkeypatch.setattr(ggv, '_solve_envelope_limit', (lambda *args, **kw: None) if fallback else boundary)
    monkeypatch.setattr(ggv, '_solve_ax_limit_qss', boundary)
    small = config(ay_max_g=.1, ax_search_min_g=-.1, ax_search_max_g=.1)
    wide = replace(small, ay_max_g=5., ax_search_min_g=-5., ax_search_max_g=5.)
    actual = ggv.generate_ggv(object(), small, object())[0]
    expected = ggv.generate_ggv(object(), wide, object())[0]
    np.testing.assert_allclose(actual.ay, expected.ay)
    np.testing.assert_allclose(actual.ax_accel, expected.ax_accel)
    np.testing.assert_allclose(actual.ax_brake, expected.ax_brake)
    assert len(actual.ay) == small.ay_points
    assert actual.ay[-1] == 12.
    assert actual.ax_accel[0] == drive_limit
    assert actual.ax_brake[0] == -12.
    if not fallback:
        assert any(call['initial_unknowns'] is not None for call in calls)


@pytest.mark.parametrize('axis', ('lateral', 'longitudinal'))
def test_unclosed_envelope_fails_explicitly(monkeypatch, axis):
    monkeypatch.setattr(ggv, 'solve_lateral_limit',
                        lambda *args, **kw: (kw['ay_upper'] if axis == 'lateral' else 1., 0.))
    monkeypatch.setattr(ggv, '_solve_envelope_limit', lambda *args, **kw: SimpleNamespace(
        success=True, unknowns={}, path_longitudinal_acceleration_mps2=kw['ax_bounds'][1]))
    with pytest.raises(RuntimeError, match='envelope did not close'):
        ggv.generate_ggv(object(), config(), object())


@pytest.mark.parametrize('kwargs', ({'ay_max_g': 0.}, {'ax_search_min_g': 0.}, {'ax_search_max_g': np.inf}))
def test_invalid_initial_bounds_rejected(kwargs):
    with pytest.raises(ValueError, match='Initial bounds'):
        ggv.generate_ggv(object(), config(**kwargs), object())


def test_real_planar_envelope_is_independent_of_initial_acceleration_bounds():
    from engines.dynpy import Vehicle
    from simulations.envelope.vehicle_yaml import load_vehicle_yaml, project_vehicle_yaml

    vehicle = Vehicle.from_yaml()
    parameters = project_vehicle_yaml(load_vehicle_yaml()).ggv
    small = replace(config(ay_max_g=.1, ax_search_min_g=-.1, ax_search_max_g=.1),
                    speeds=(12.,), trim_multistart=True)
    wide = replace(small, ay_max_g=4.5, ax_search_min_g=-3.2, ax_search_max_g=2.8)
    actual = ggv.generate_ggv(parameters, small, vehicle.model(3))[0]
    expected = ggv.generate_ggv(parameters, wide, vehicle.model(3))[0]
    for name in ('ay', 'ax_accel', 'ax_brake'):
        np.testing.assert_allclose(getattr(actual, name), getattr(expected, name), atol=1e-4)
    assert actual.ay[-1] > small.ay_max_g * ggv.G
    assert actual.ax_accel[0] > small.ax_search_max_g * ggv.G
    assert actual.ax_brake[0] < small.ax_search_min_g * ggv.G


def test_initial_interval_with_no_feasible_state_expands(monkeypatch):
    monkeypatch.setattr(ggv, 'solve_lateral_limit', lambda *args, **kw: (1., -3.))

    def boundary(*args, **kw):
        target = -3. if kw['mode'] == 'drive' else -5.
        lo, hi = kw['ax_bounds']
        if not lo <= target <= hi:
            return None
        return SimpleNamespace(success=True, unknowns={}, path_longitudinal_acceleration_mps2=target)

    monkeypatch.setattr(ggv, '_solve_envelope_limit', boundary)
    monkeypatch.setattr(ggv, '_solve_ax_limit_qss', lambda *args, **kw: np.nan)
    result = ggv.generate_ggv(object(), config(ax_search_min_g=-.1, ax_search_max_g=.1), object())[0]
    np.testing.assert_array_equal(result.ax_accel, -3.)
    np.testing.assert_array_equal(result.ax_brake[:-1], -5.)


def test_workflow_ignores_saved_numerical_controls():
    automatic = ggv.config_to_ggv_config({'generation': {'model_dof': 14}})
    legacy = ggv.config_to_ggv_config({'generation': {
        'model_dof': 14, 'speeds_mps': [2.], 'ay_max_g': .01, 'ay_points': 2,
        'ax_search_min_g': -.01, 'ax_search_max_g': .01, 'ax_search_points': 2,
        'max_abs_beta_rad': .01, 'max_abs_steering_rad': .01,
        'ax_binary_iterations': 1, 'enforce_tire_load_range': False,
        'trim_multistart': False, 'include_left_right': False,
    }})
    assert legacy == automatic
    assert automatic.model_dof == 14
    assert automatic.ay_points == 161
    assert automatic.trim_multistart


def test_legacy_projection_drops_infeasible_rows_without_expanding(monkeypatch):
    monkeypatch.setattr(ggv, 'solve_lateral_limit', lambda *args, **kw: (1., -.2))
    calls = []

    def boundary(*args, **kw):
        calls.append(kw)
        if kw['ay'] > 0.:
            return np.nan
        return .5 if kw['mode'] == 'drive' else -.5

    monkeypatch.setattr(ggv, 'solve_ax_limit', boundary)
    result = ggv.generate_ggv(object(), config())[0]
    assert len(calls) == 8
    np.testing.assert_array_equal(result.ay, [0., 1.])
    np.testing.assert_array_equal(result.ax_accel, [.5, -.2])
    np.testing.assert_array_equal(result.ax_brake, [-.5, -.2])


def test_fourteen_dof_lateral_continuation_releases_temporary_load_floor():
    from engines.dynpy import Vehicle
    from engines.dynpy.qss import _algebraic_residual
    from simulations.envelope.vehicle_yaml import load_vehicle_yaml, project_vehicle_yaml

    model = Vehicle.from_yaml().model(14)
    parameters = project_vehicle_yaml(load_vehicle_yaml()).ggv
    result = ggv._solve_envelope_limit(
        parameters, model, speed=9.345333333333333, ay=3.2 * ggv.G,
        ax_bounds=(-np.inf, np.inf), mode='lateral', max_abs_beta_rad=.25,
        max_abs_steering_rad=.5, enforce_tire_load_range=True,
    )
    assert result is not None and result.success
    assert result.residual_norm < 1e-5
    assert 0. < min(result.output.normal_loads_n) < 1.
    np.testing.assert_allclose(_algebraic_residual(model, result.inputs, result.output), 0., atol=1e-4)
    forward = model.evaluate(result.state, result.inputs)
    np.testing.assert_allclose(forward.generalized_acceleration, result.output.generalized_acceleration, atol=1e-6)
