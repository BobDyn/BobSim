"""GGV continuation and local boundary-repair work."""

from dataclasses import dataclass

import numpy as np
import pytest

from simulations.envelope.ggv import ggv_generation as ggv


@dataclass
class Trim:
    unknowns: dict
    path_longitudinal_acceleration_mps2: float
    path_lateral_acceleration_mps2: float = 1.
    success: bool = True
    state: object = None
    inputs: object = None
    output: object = None


def test_local_repair_starts_at_required_boundary_precision(monkeypatch):
    attempts = []

    def feasible(model, **kwargs):
        acceleration = kwargs["longitudinal_acceleration_mps2"]
        attempts.append(acceleration)
        return Trim({}, acceleration)

    monkeypatch.setattr(ggv, "_solve_racing_trim", feasible)
    monkeypatch.setattr(ggv, "_actuator_margins", lambda *args: np.ones(1))
    result = ggv._consistent_boundary(
        object(), object(), speed=5., ax=-10., ay=1., mode="brake", ax_bounds=(-20., 20.),
        initial_unknowns={}, max_abs_beta_rad=.25, max_abs_steering_rad=.5, enforce_tire_load_range=True,
    )
    assert attempts == pytest.approx([-10. + 1e-4])
    assert result.path_longitudinal_acceleration_mps2 == pytest.approx(-10. + 1e-4)


def test_local_repair_can_expand_to_full_interior_bound(monkeypatch):
    attempts = []

    def feasible(model, **kwargs):
        acceleration = kwargs["longitudinal_acceleration_mps2"]
        attempts.append(acceleration)
        return Trim({}, acceleration) if acceleration >= 19. else None

    monkeypatch.setattr(ggv, "_solve_racing_trim", feasible)
    monkeypatch.setattr(ggv, "_actuator_margins", lambda *args: np.ones(1))
    result = ggv._consistent_boundary(
        object(), object(), speed=5., ax=-20., ay=1., mode="brake", ax_bounds=(-20., 20.),
        initial_unknowns={}, max_abs_beta_rad=.25, max_abs_steering_rad=.5, enforce_tire_load_range=True,
    )
    assert 20. in attempts
    assert result.path_longitudinal_acceleration_mps2 == pytest.approx(19., abs=1e-4)


def test_failed_boundary_retries_neighbor_and_coast_before_trim_search(monkeypatch):
    optimizations, searches = [], []
    monkeypatch.setattr(ggv, "solve_lateral_limit", lambda *args, **kwargs: (.9 * ggv.G, 0.))

    def boundary(vehicle, model, **kwargs):
        optimizations.append(kwargs["initial_unknowns"])
        if kwargs["ay"]:
            return None
        return Trim({"branch": kwargs["mode"]}, 1. if kwargs["mode"] == "drive" else -1.)

    def fallback(vehicle, model, **kwargs):
        searches.append(kwargs)
        return .5 if kwargs["mode"] == "drive" else -.5

    monkeypatch.setattr(ggv, "_solve_envelope_limit", boundary)
    monkeypatch.setattr(ggv, "_solve_ax_limit_qss", fallback)
    envelopes = ggv.generate_ggv(
        object(),
        ggv.GGVConfig(speeds=(5.,), ay_max_g=1., ay_points=3, trim_multistart=True,
                      verbose=False, warn_tire_load_range=False),
        reduced_model=object(),
    )
    assert len(envelopes) == 1
    assert optimizations == [None, None, {"branch": "drive"}, {"branch": "brake"}, None,
                             {"branch": "brake"}, {"branch": "drive"}, None]
    assert [call["initial_unknowns"] for call in searches] == [{"branch": "drive"}, {"branch": "brake"}]


def test_acceleration_fallback_retains_supplied_seed(monkeypatch):
    seed = {"beta_rad": .02}
    received = []

    def feasible(model, **kwargs):
        received.append(kwargs["initial_unknowns"])
        return Trim(seed, kwargs["longitudinal_acceleration_mps2"])

    monkeypatch.setattr(ggv, "_solve_racing_trim", feasible)
    monkeypatch.setattr(ggv, "_actuator_margins", lambda *args: np.ones(1))
    result = ggv._solve_ax_limit_qss(
        object(), object(), speed=5., ay=1., ax_grid=[-10., 10.], mode="drive",
        max_abs_beta_rad=.25, max_abs_steering_rad=.5, ax_binary_iterations=14,
        enforce_tire_load_range=True, trim_multistart=True, initial_unknowns=seed,
    )
    assert result == 10.
    assert received == [seed]
