from __future__ import annotations

import math

import numpy as np
import pytest

from app.tire_eval import _mf52_curves
from common.vehicle_io import parse_tir, repo_root
from engines.dynpy.tire import MF52Tire


def test_preview_moments_match_dynamics_evaluator():
    coefficients = parse_tir(repo_root() / "common/tire_templates/16x7p5_10_12psi.tir")
    model = MF52Tire(coefficients)
    curves = _mf52_curves(coefficients, 600, 0.02)
    speed = curves["moment_speed_mps"]
    assert speed == coefficients["LONGVL"]
    assert curves["moment_error"] == ""
    for index, output in enumerate(("mx", "my", "mz")):
        surface = curves["moments"][output][2]
        point = surface["rows"][2]["points"][19]
        alpha = math.radians(point.get("alpha_deg", 0))
        expected = model.moments(point["fz_n"], alpha, point.get("kappa", 0),
                                 math.radians(surface["gamma_deg"]), speed)[index]
        assert point[f"{output}_nm"] == pytest.approx(float(expected))
    for surface in curves["combined"]["force_maps_by_gamma_fz"]:
        for load_map in surface["maps"]:
            point = load_map["rows"][8]["points"][21]
            expected = model.moments(point["fz_n"], point["alpha_rad"], point["kappa"],
                                     math.radians(surface["gamma_deg"]), speed)
            actual = [point[f"{output}_nm"] for output in ("mx", "my", "mz")]
            assert np.isfinite(actual).all()
            np.testing.assert_allclose(actual, expected)
