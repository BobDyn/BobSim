"""Batched model evaluation and the batched Jacobians the GGV solver builds from it."""

from dataclasses import replace
import warnings

import numpy as np
import pytest
from scipy.optimize._numdiff import approx_derivative

from engines.dynpy import Vehicle
from engines.dynpy.jacobian import forward_difference_jacobian
from engines.dynpy.models import ModelOutput, create_model
from engines.dynpy.qss import _algebraic_slip_slopes, _algebraic_slip_slopes_batch, _trim_state_and_inputs
import simulations.envelope.ggv.ggv_generation as ggv
from simulations.envelope.vehicle_yaml import load_vehicle_yaml, project_vehicle_yaml

# Batched rows must match the scalar model to rounding. In practice they are bit
# for bit equal; the tolerance only leaves room for a different CPU's SIMD paths.
RTOL, ATOL = 1e-12, 1e-9


@pytest.fixture(scope="module")
def vehicle():
    return Vehicle.from_yaml()


def _qss_rows(model, rows, *, seed=0, shared_rack=False):
    """Trial QSS points like a GGV solve visits: random sideslip, steer, yaw rate, loads and slips."""
    rng = np.random.default_rng(seed)
    static = np.asarray(model.parameters.static_wheel_loads_n)
    states, inputs, loads, slips = [], [], [], []
    rack = rng.normal(0., .01)
    for _ in range(rows):
        values = np.r_[rng.normal(0., .05), rack if shared_rack else rng.normal(0., .01), 0., np.zeros(model.dof - 3)]
        state, row_inputs = _trim_state_and_inputs(
            model, values[:model.dof], speed_mps=rng.uniform(4., 30.), yaw_rate_radps=rng.normal(0., .5),
            rack_input=True,
        )
        state[2] = rng.uniform(-np.pi, np.pi) if model.dof == 3 else state[2]
        states.append(state)
        inputs.append(replace(row_inputs, wheel_torques_nm=tuple(rng.normal(0., 100., 4))))
        loads.append(static * rng.uniform(.2, 1.8, 4))
        slips.append(rng.normal(0., .05, 4))
    return np.array(states), inputs, np.array(loads), np.array(slips)


def _assert_outputs_match(batch: list[ModelOutput], reference: list[ModelOutput]) -> None:
    assert len(batch) == len(reference)
    for row, expected in zip(batch, reference, strict=True):
        for name in ModelOutput.__dataclass_fields__:
            np.testing.assert_allclose(getattr(row, name), getattr(expected, name), rtol=RTOL, atol=ATOL,
                                       err_msg=name)


@pytest.mark.parametrize("shared_rack", (False, True))
def test_planar_qss_batch_matches_scalar_rows(vehicle, shared_rack):
    model = vehicle.model(3)
    states, inputs, loads, slips = _qss_rows(model, 24, shared_rack=shared_rack)
    batch = model.evaluate_batch(states, inputs, normal_loads_n=loads, algebraic_slips=slips)
    reference = [model.evaluate(s, i, normal_loads_n=n, algebraic_slips=k)
                 for s, i, n, k in zip(states, inputs, loads, slips, strict=True)]
    _assert_outputs_match(batch, reference)


def test_planar_qss_batch_covers_steering_input_unloaded_corners_and_no_aero(vehicle):
    model = vehicle.model(3)
    states, inputs, loads, slips = _qss_rows(model, 6, seed=1)
    # Steering instead of rack, one corner off the ground and one exactly on it.
    inputs = [replace(row, rack_displacement_m=None, steering_rad=.03 * k) for k, row in enumerate(inputs)]
    loads[0, 3], loads[1, 2] = 0., 1e-9
    for candidate in (model, create_model(3, replace(model.parameters, aero=None))):
        batch = candidate.evaluate_batch(states, inputs, normal_loads_n=loads, algebraic_slips=slips)
        reference = [candidate.evaluate(s, i, normal_loads_n=n, algebraic_slips=k)
                     for s, i, n, k in zip(states, inputs, loads, slips, strict=True)]
        _assert_outputs_match(batch, reference)


@pytest.mark.parametrize("dof", (6, 10, 14))
def test_other_fidelities_batch_by_rows(vehicle, dof):
    model = vehicle.model(dof)
    states, inputs, loads, slips = _qss_rows(model, 3, seed=2)
    kwargs = {"normal_loads_n": loads if dof < 14 else None, "algebraic_slips": slips if dof < 10 else None}
    batch = model.evaluate_batch(states, inputs, **kwargs)
    reference = [model.evaluate(s, i, normal_loads_n=kwargs["normal_loads_n"][r] if dof < 14 else None,
                                algebraic_slips=slips[r] if dof < 10 else None)
                 for r, (s, i) in enumerate(zip(states, inputs, strict=True))]
    _assert_outputs_match(batch, reference)


def test_row_by_row_batch_rejects_mismatched_rows(vehicle):
    model = vehicle.model(6)
    states, inputs, loads, _ = _qss_rows(model, 3, seed=2)
    with pytest.raises(ValueError):
        model.evaluate_batch(states, inputs[:2], normal_loads_n=loads)


def test_planar_batch_without_trial_values_uses_the_scalar_path(vehicle, monkeypatch):
    model = vehicle.model(3)
    states, inputs, loads, _ = _qss_rows(model, 2, seed=3)
    calls = []
    original = type(model).evaluate

    def counted(self, *args, **kwargs):
        calls.append(kwargs.get("algebraic_slips"))
        return original(self, *args, **kwargs)

    monkeypatch.setattr(type(model), "evaluate", counted)
    model.evaluate_batch(states, inputs, normal_loads_n=loads)
    assert calls == [None, None]


@pytest.mark.parametrize("change", ("negative_load", "nonfinite_slip", "nonfinite_state", "shape", "inputs"))
def test_planar_batch_rejects_what_the_scalar_model_rejects(vehicle, change):
    model = vehicle.model(3)
    states, inputs, loads, slips = _qss_rows(model, 3, seed=4)
    if change == "negative_load":
        loads[1, 0] = -1.
    elif change == "nonfinite_slip":
        slips[2, 3] = np.nan
    elif change == "nonfinite_state":
        states[0, 4] = np.inf
    elif change == "shape":
        loads = loads[:, :3]
    else:
        inputs = inputs[:2]
    with pytest.raises(ValueError):
        model.evaluate_batch(states, inputs, normal_loads_n=loads, algebraic_slips=slips)


def test_aero_wrench_batch_matches_rows(vehicle):
    aero = vehicle.model(3).parameters.aero
    assert aero is not None
    rng = np.random.default_rng(5)
    # Heights inside, below and above the CFD grids exercise the clamped brackets.
    span = (min(aero.front_grid[0], aero.rear_grid[0]) - .05, max(aero.front_grid[-1], aero.rear_grid[-1]) + .05)
    heights = rng.uniform(*span, (40, 4))
    velocity = rng.normal(0., 15., (40, 3))
    velocity[0] = 0.
    force, moment = aero.wrench_batch(heights, velocity, 1.1)
    for row in range(40):
        expected = aero.wrench(heights[row], velocity[row], 1.1)
        np.testing.assert_allclose(force[row], expected[0], rtol=RTOL, atol=ATOL)
        np.testing.assert_allclose(moment[row], expected[1], rtol=RTOL, atol=ATOL)


def test_slip_slopes_batch_matches_rows(vehicle):
    model = vehicle.model(3)
    states, inputs, loads, slips = _qss_rows(model, 8, seed=6)
    outputs = model.evaluate_batch(states, inputs, normal_loads_n=loads, algebraic_slips=slips)
    np.testing.assert_allclose(_algebraic_slip_slopes_batch(model, outputs),
                               [_algebraic_slip_slopes(model, output) for output in outputs], rtol=RTOL, atol=ATOL)


def _vector_function(x):
    return np.array([np.sin(x[0]) * x[1], x[1] ** 3 - x[2], np.exp(.3 * x[2]) + x[0] * x[2]])


@pytest.mark.parametrize("x0, lower, upper", [
    ((.3, -1.2, 2.), (-np.inf,) * 3, (np.inf,) * 3),
    ((.3, -1.2, 2.), (-1., -2., -3.), (1., 2., 3.)),
    # On an upper bound: the step turns around. On a lower bound: it stays forward.
    ((1., -2., 0.), (-1., -2., -3.), (1., 2., 3.)),
    # A box narrower than the step: forward or backward to the wider side.
    ((.5, 1.5e-9, 1e3), (.5 - 1e-10, 0., 1e3 - 1.), (.5 + 3e-10, 2e-9, 1e3)),
    ((0., -0., 1e-300), (-np.inf, -1., 0.), (np.inf, 1., 1.)),
])
def test_forward_difference_matches_scipy_slsqp_jacobian(x0, lower, upper):
    x0 = np.asarray(x0, dtype=float)
    expected = approx_derivative(_vector_function, x0, method="2-point", abs_step=np.finfo(float).eps ** .5,
                                 bounds=(np.asarray(lower), np.asarray(upper)))
    np.testing.assert_array_equal(forward_difference_jacobian(_vector_function, x0, lower, upper), expected)


def test_forward_difference_prefetches_every_point_first_and_clips_like_slsqp():
    events = []

    def fun(x):
        events.append(("call", tuple(x)))
        return _vector_function(x)

    with pytest.warns(RuntimeWarning, match="outside bounds"):
        jacobian = forward_difference_jacobian(fun, [2., 0., 0.], -np.ones(3), np.ones(3),
                                               prefetch=lambda points: events.append(("batch", [*map(tuple, points)])))
    # One batch of the clipped point and its three steps, then fun at exactly those points.
    kind, batch = events[0]
    assert kind == "batch" and batch[0] == (1., 0., 0.) and len(batch) == 4
    assert events[1:] == [("call", point) for point in batch]
    with warnings.catch_warnings():
        warnings.simplefilter("ignore", RuntimeWarning)
        expected = approx_derivative(_vector_function, np.array([1., 0., 0.]), method="2-point",
                                     abs_step=np.finfo(float).eps ** .5, bounds=(-np.ones(3), np.ones(3)))
    np.testing.assert_array_equal(jacobian, expected)


@pytest.mark.parametrize("mode, ay", (("drive", 8.), ("brake", 15.), ("lateral", 30.)))
def test_ggv_boundary_is_unchanged_by_batched_jacobians(vehicle, monkeypatch, mode, ay):
    model = vehicle.model(3)
    arguments = dict(speed=15., ay=ay, ax_bounds=(-3.2 * ggv.G, 2.8 * ggv.G), mode=mode,
                     max_abs_beta_rad=.25, max_abs_steering_rad=.5, enforce_tire_load_range=True)
    parameters = project_vehicle_yaml(load_vehicle_yaml()).ggv
    batched = ggv._solve_envelope_limit(parameters, model, **arguments)

    def refuse(*args, **kwargs):
        raise RuntimeError("no batch")

    # A rejected batch leaves every point to the scalar model, which is the unbatched solve.
    monkeypatch.setattr(type(model), "evaluate_batch", refuse)
    scalar = ggv._solve_envelope_limit(parameters, model, **arguments)
    assert batched is not None and scalar is not None
    assert batched.unknowns.keys() == scalar.unknowns.keys()
    for name, value in scalar.unknowns.items():
        assert batched.unknowns[name] == pytest.approx(value, rel=1e-9, abs=1e-9), name


def test_ggv_jacobian_columns_reach_the_model_as_one_batch(vehicle, monkeypatch):
    model = vehicle.model(3)
    batches, scalar_calls = [], []
    batch, evaluate = type(model).evaluate_batch, type(model).evaluate

    def counted_batch(self, states, *args, **kwargs):
        batches.append(len(states))
        return batch(self, states, *args, **kwargs)

    def counted_evaluate(self, *args, **kwargs):
        scalar_calls.append(1)
        return evaluate(self, *args, **kwargs)

    monkeypatch.setattr(type(model), "evaluate_batch", counted_batch)
    monkeypatch.setattr(type(model), "evaluate", counted_evaluate)
    result = ggv._solve_envelope_limit(
        project_vehicle_yaml(load_vehicle_yaml()).ggv, model, speed=15., ay=8., ax_bounds=(-3.2 * ggv.G, 2.8 * ggv.G),
        mode="drive", max_abs_beta_rad=.25, max_abs_steering_rad=.5, enforce_tire_load_range=True,
    )
    assert result is not None
    unknowns = len(result.unknowns) - 1  # steering_rad is reported, not solved.
    assert batches and max(batches) == unknowns
    # Each Jacobian costs one batch, not one model call per column.
    assert len(scalar_calls) < sum(batches)
