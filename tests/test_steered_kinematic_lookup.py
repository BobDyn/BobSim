from __future__ import annotations

from pathlib import Path

import numpy as np
import pytest
import yaml

from engines.kinpy.lookup import DoubleWishboneKinematicLookup


@pytest.fixture(scope="module")
def lookup() -> DoubleWishboneKinematicLookup:
    vehicle = yaml.safe_load((Path(__file__).resolve().parents[1] / "vehicle.yml").read_text())
    return DoubleWishboneKinematicLookup.from_vehicle(vehicle)


def test_steered_grid_matches_exact_geometry_and_force_slopes(lookup: DoubleWishboneKinematicLookup) -> None:
    rng = np.random.default_rng(92)
    for _ in range(20):
        jounce = rng.uniform(-0.04, 0.04, 4)
        rack = float(rng.uniform(-0.006, 0.006))
        actual = lookup.at(jounce, rack)
        exact = lookup.nonlinear.at(jounce, rack)
        for field in ("contact_patch_offsets_m", "wheel_center_offsets_m", "mechanical_trail_m", "scrub_radius_m"):
            np.testing.assert_allclose(getattr(actual, field), getattr(exact, field), atol=1e-5, rtol=0)
        for field in ("camber_rad", "toe_rad", "caster_rad", "kpi_rad"):
            np.testing.assert_allclose(getattr(actual, field), getattr(exact, field), atol=2e-5, rtol=0)
        np.testing.assert_allclose(actual.contact_patch_tangents, exact.contact_patch_tangents, atol=1e-4, rtol=0)
        np.testing.assert_allclose(
            actual.instant_links.coefficient_matrix, exact.instant_links.coefficient_matrix, atol=1e-4, rtol=0,
        )


def test_planar_lookup_only_solves_zero_jounce_and_reuses_cells(
    lookup: DoubleWishboneKinematicLookup, monkeypatch: pytest.MonkeyPatch,
) -> None:
    steering = type(lookup.steering)(lookup.nonlinear, lookup.steering.jounce)
    original = lookup.nonlinear._solve
    solved: list[float] = []

    def record(axle: str, jounce: float, rack: float = 0.0):
        solved.append(jounce)
        return original(axle, jounce, rack)

    monkeypatch.setattr(lookup.nonlinear, "_solve", record)
    steering.at(0.0, 0.0011)
    assert solved and set(solved) == {0.0}
    solved.clear()
    steering.at(0.0, 0.0012)
    assert not solved


def test_lookup_falls_back_beyond_travel_grid(lookup: DoubleWishboneKinematicLookup) -> None:
    jounce = np.array([0.061, -0.061, 0.062, -0.062])
    actual = lookup.at(jounce, 0.002)
    exact = lookup.nonlinear.at(jounce, 0.002)
    np.testing.assert_array_equal(actual.contact_patch_offsets_m, exact.contact_patch_offsets_m)
    np.testing.assert_array_equal(actual.contact_patch_tangents, exact.contact_patch_tangents)


def test_invalid_cell_uses_exact_solution(
    lookup: DoubleWishboneKinematicLookup, monkeypatch: pytest.MonkeyPatch,
) -> None:
    monkeypatch.setattr(lookup.steering, "_cell_valid", lambda *args: False)
    actual = lookup.steering.at(0.0123, 0.0034)
    assert actual == lookup.nonlinear._solve("front", 0.0123, 0.0034)


def test_unreachable_grid_node_keeps_reachable_query_exact(
    lookup: DoubleWishboneKinematicLookup, monkeypatch: pytest.MonkeyPatch,
) -> None:
    steering = type(lookup.steering)(lookup.nonlinear, lookup.steering.jounce)

    def unreachable(*args):
        raise ValueError("Unreachable grid endpoint")

    monkeypatch.setattr(steering, "_node", unreachable)
    assert steering.at(0.0123, 0.0034) == lookup.nonlinear._solve("front", 0.0123, 0.0034)


def test_rack_conversion_matches_exact_and_is_continuous_at_zero(lookup: DoubleWishboneKinematicLookup) -> None:
    for steer in np.deg2rad([-12.0, -3.0, 0.0, 3.0, 12.0]):
        rack = lookup.rack_from_steering(float(steer))
        headings = lookup.nonlinear.at(np.zeros(4), rack).toe_rad
        assert np.mean(headings[:2]) == pytest.approx(steer, abs=2e-5)
    below = lookup.at(np.zeros(4), -1e-10)
    above = lookup.at(np.zeros(4), 1e-10)
    np.testing.assert_allclose(below.toe_rad, above.toe_rad, atol=1e-8, rtol=0)


def test_lookup_tangent_matches_contact_motion(lookup: DoubleWishboneKinematicLookup) -> None:
    jounce = np.array([0.0121, -0.0061, 0.0201, -0.0181])
    step = 1e-6
    state = lookup.at(jounce, 0.0032)
    derivative = (
        lookup.at(jounce + step, 0.0032).contact_patch_offsets_m
        - lookup.at(jounce - step, 0.0032).contact_patch_offsets_m
    ) / (2 * step)
    np.testing.assert_allclose(state.contact_patch_tangents, derivative, atol=1e-7, rtol=0)


@pytest.mark.parametrize("rack", [float("nan"), float("inf")])
def test_lookup_rejects_nonfinite_rack(lookup: DoubleWishboneKinematicLookup, rack: float) -> None:
    with pytest.raises(ValueError, match="Rack displacement must be finite"):
        lookup.at(np.zeros(4), rack)
