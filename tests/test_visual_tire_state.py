"""BobVis friction-circle and LLTD arithmetic.

:mod:`_1_VisualSim.tire_state` is numpy only, so these run everywhere, CI
included. The friction limit has to match BobLib's MF5.2 peak exactly, or a
tire the solver has sliding would look like it has grip to spare.
"""

from __future__ import annotations

import numpy as np
import pytest

from _0_Utils.vehicle_io import parse_tir, repo_root
from _1_VisualSim.tire_state import (
    LLTD_MIN_FRACTION,
    MIN_LOAD_N,
    axle_load_transfer,
    friction_coefficients,
    grip_usage,
    lateral_transfer,
    lltd,
    peak_mu,
)

COEFFS = {
    "FNOMIN": 650.0, "LFZO": 1.0, "LMUX": 1.0, "LMUY": 1.0,
    "PDX1": 2.6, "PDX2": -0.62, "PDX3": 11.0,
    "PDY1": -2.4, "PDY2": 0.34, "PDY3": 3.9,
}


def test_peak_mu_at_nominal_load_and_no_camber_is_pdx1_and_pdy1() -> None:
    mu_x, mu_y = peak_mu(650.0, 0.0, COEFFS)
    assert mu_x == pytest.approx(2.6)
    assert mu_y == pytest.approx(2.4)  # a magnitude, although PDY1 is negative


def test_peak_mu_follows_load_sensitivity() -> None:
    light, heavy = peak_mu(np.array([325.0, 1300.0]), 0.0, COEFFS)[0]
    assert light == pytest.approx(2.6 + 0.62 * 0.5)
    assert heavy == pytest.approx(2.6 - 0.62)
    assert light > heavy  # tires lose friction coefficient as load rises


def test_camber_reduces_peak_mu() -> None:
    upright = peak_mu(650.0, 0.0, COEFFS)
    cambered = peak_mu(650.0, np.radians(3.0), COEFFS)
    assert cambered[0] < upright[0] and cambered[1] < upright[1]


def test_scale_factors_apply() -> None:
    scaled = dict(COEFFS, LMUX=0.5, LMUY=0.5, LFZO=2.0)
    mu_x, mu_y = peak_mu(1300.0, 0.0, scaled)  # nominal load doubled by LFZO
    assert mu_x == pytest.approx(1.3)
    assert mu_y == pytest.approx(1.2)


def test_grip_usage_is_one_at_the_pure_slip_peak() -> None:
    fz = np.array([650.0, 650.0, 650.0])
    fx = np.array([2.6 * 650.0, 0.0, 0.5 * 2.6 * 650.0])
    fy = np.array([0.0, -2.4 * 650.0, 0.0])
    longitudinal, lateral, usage = grip_usage(fx, fy, fz, 0.0, COEFFS)

    assert usage == pytest.approx([1.0, 1.0, 0.5])
    assert longitudinal[0] == pytest.approx(1.0)
    assert lateral[1] == pytest.approx(-1.0)  # the sign survives for plotting


def test_a_lifted_wheel_has_no_grip_reading() -> None:
    _, _, usage = grip_usage(np.array([10.0]), np.array([10.0]), np.array([MIN_LOAD_N / 2]), 0.0, COEFFS)
    assert np.isnan(usage[0])


def test_lateral_transfer_ignores_static_asymmetry() -> None:
    left = np.array([700.0, 800.0, 900.0])
    right = np.array([640.0, 540.0, 440.0])  # a 30 N static split before any cornering
    assert lateral_transfer(left, right) == pytest.approx([0.0, 100.0, 200.0])


def test_lltd_is_the_front_share_and_undefined_without_transfer() -> None:
    share = lltd(np.array([0.0, 60.0, 30.0]), np.array([0.0, 40.0, 70.0]), min_total=10.0)
    assert np.isnan(share[0])
    assert share[1:] == pytest.approx([0.6, 0.3])


def test_axle_load_transfer_on_a_symmetric_car_in_a_steady_corner() -> None:
    samples = 50
    ramp = np.linspace(0.0, 1.0, samples)
    static = 700.0
    front_shift, rear_shift = 180.0 * ramp, 120.0 * ramp
    loads = {
        "fl": static + front_shift, "fr": static - front_shift,
        "rl": static + rear_shift, "rr": static - rear_shift,
    }
    front, rear, share = axle_load_transfer(loads)

    assert front[-1] == pytest.approx(180.0)
    assert rear[-1] == pytest.approx(120.0)
    assert share[-1] == pytest.approx(0.6)
    # Undefined only while the total is under the threshold near the start.
    threshold = LLTD_MIN_FRACTION * 4 * static
    assert np.isnan(share[0])
    assert np.all(np.isfinite(share[(front + rear) >= threshold]))


def test_friction_coefficients_default_scales_and_name_missing_terms() -> None:
    coeffs = friction_coefficients({"FNOMIN": 650, "PDX1": 2.0, "PDX2": 0.0, "PDY1": -2.0, "PDY2": 0.0})
    assert coeffs["LMUX"] == 1.0 and coeffs["PDY3"] == 0.0

    with pytest.raises(KeyError, match="PDY1"):
        friction_coefficients({"FNOMIN": 650, "PDX1": 2.0, "PDX2": 0.0, "PDY2": 0.0})


def test_the_bundled_tire_file_gives_plausible_fsae_grip() -> None:
    tir = parse_tir(repo_root() / "_0_Utils" / "tire_templates" / "16x7p5_10_12psi.tir")
    mu_x, mu_y = peak_mu(np.array([400.0, 650.0, 1000.0]), 0.0, friction_coefficients(tir))
    assert np.all((mu_x > 1.0) & (mu_x < 4.0))
    assert np.all((mu_y > 1.0) & (mu_y < 4.0))
