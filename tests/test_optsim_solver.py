"""Target-metric solver numerics, checked against a closed-form stand-in vehicle."""

from __future__ import annotations

import math
from pathlib import Path
import sys

import pytest

ROOT = Path(__file__).resolve().parents[1]
OPTSIM_DIR = ROOT / "_4_OptSim"
if str(OPTSIM_DIR) not in sys.path:
    sys.path.insert(0, str(OPTSIM_DIR))

np = pytest.importorskip("numpy", reason="the solver works on numpy arrays")
pytest.importorskip("scipy", reason="the solver uses scipy.optimize.least_squares")

from StandardSens.pipeline import solver  # noqa: E402

FRONT, REAR, TOE = "front.stabar", "rear.stabar", "front.toe"

KNOBS = [
    solver.Knob(FRONT, 200.0, 300.0, 257.0),
    solver.Knob(REAR, 360.0, 960.0, 535.0),
    solver.Knob(TOE, -0.25, 0.25, 0.0),
]
TOLERANCES = {"understeer": 0.01, "roll": 0.01}


def vehicle(variant: dict[str, float]) -> dict[str, float]:
    """Stand-in car: bars act linearly, toe acts evenly, one mild curvature."""
    front = variant.get(FRONT, 257.0) - 257.0
    rear = variant.get(REAR, 535.0) - 535.0
    toe = variant.get(TOE, 0.0)
    return {
        "understeer": 0.30 + 0.004 * front - 0.0015 * rear + 2.0 * toe * toe,
        "roll": 0.90 - 0.0008 * front - 0.0004 * rear + 1.0e-7 * rear * rear,
    }


class CountingEvaluator:
    def __init__(self, model=vehicle):
        self.model = model
        self.calls: list[dict[str, float]] = []

    def __call__(self, variants):
        self.calls.extend(variants)
        return [self.model(v) for v in variants]


def test_star_design_keeps_both_steps_inside_the_bounds() -> None:
    """A baseline on a bound must still leave room to measure curvature."""
    camber = solver.Knob("camber", -2.0, 0.0, 0.0)
    center, steps, points = solver.star_design([camber], step_fraction=0.5)
    assert center[0] == pytest.approx(-0.5)
    assert len(points) == 3
    for point in points:
        assert camber.lower <= point[0] <= camber.upper


def test_surrogate_is_exact_at_every_star_point() -> None:
    center, steps, points = solver.star_design(KNOBS)
    responses = np.array([
        [vehicle(dict(zip([FRONT, REAR, TOE], p, strict=True)))[m] for m in ("understeer", "roll")]
        for p in points
    ])
    surrogate = solver.fit_surrogate(center, steps, responses)
    for point, response in zip(points, responses, strict=True):
        assert surrogate.predict(point) == pytest.approx(response, abs=1e-12)


def test_solves_two_targets_in_a_linear_number_of_simulations() -> None:
    evaluate = CountingEvaluator()
    result = solver.solve(
        KNOBS, {"understeer": 0.45, "roll": 0.85}, TOLERANCES, evaluate, snap_discrete=False
    )
    assert result.status == "converged"
    for metric, error in result.errors.items():
        assert abs(error) <= TOLERANCES[metric]
    # 2n + 1 star runs plus at most three verifications: linear in the knob count.
    assert len(evaluate.calls) <= 2 * len(KNOBS) + 1 + 3
    assert len(result.evaluations) == len(evaluate.calls)


def test_even_response_is_not_mistaken_for_no_response() -> None:
    """Toe acts through toe squared, so a one-sided gradient at zero toe sees no slope."""
    toe_only = [solver.Knob(TOE, -0.25, 0.25, 0.0)]
    result = solver.solve(toe_only, {"understeer": 0.35}, {"understeer": 0.005}, CountingEvaluator())
    assert result.status == "converged"
    assert abs(result.solution[TOE]) == pytest.approx(math.sqrt(0.05 / 2.0), abs=0.02)


def test_unreachable_target_says_so_and_names_the_limiting_knobs() -> None:
    result = solver.solve(
        KNOBS, {"understeer": 5.0}, {"understeer": 0.01}, CountingEvaluator(), snap_discrete=False
    )
    assert result.status == "unreachable"
    assert result.at_bound, "the knobs that ran out of range must be reported"
    assert "outside what the knobs can reach" in result.message
    # The reported numbers are still from a real evaluation, not the surrogate.
    assert result.achieved["understeer"] == pytest.approx(vehicle(result.solution)["understeer"])


def test_unreachable_target_does_not_pay_to_resimulate_the_same_setup() -> None:
    """A bounded solve hits a limit only to float noise, so compare repeats range-relative."""
    knobs = [
        solver.Knob("front.spring", 21015.2202, 31522.8303, 26269.02525),
        solver.Knob("rear.spring", 35025.367, 52538.0505, 43781.70875),
    ]

    def stiff(variant):
        front = variant["front.spring"] - 26269.02525
        rear = variant["rear.spring"] - 43781.70875
        return {"understeer": 0.325 + 2.0e-6 * front - 1.5e-6 * rear}

    evaluate = CountingEvaluator(stiff)
    result = solver.solve(knobs, {"understeer": 0.20}, {"understeer": 0.02}, evaluate)
    assert result.status == "unreachable"
    verified = [e.variant for e in result.evaluations if e.kind == "verify"]
    assert len(verified) == 1, f"the same limit setup was simulated {len(verified)} times"


def test_underdetermined_question_gets_the_smallest_change_from_baseline() -> None:
    """One target, three knobs: infinitely many answers, so prefer the nearest."""
    result = solver.solve(
        KNOBS, {"understeer": 0.33}, {"understeer": 0.005}, CountingEvaluator(), snap_discrete=False
    )
    assert result.status == "converged"
    moved = {
        knob.path: abs(result.solution[knob.path] - knob.baseline) / knob.span for knob in KNOBS
    }
    assert max(moved.values()) < 0.25, f"a small retune should not swing a knob across its range: {moved}"


def test_discrete_parts_are_respected_and_the_answer_is_still_simulated() -> None:
    bars = (205.0, 231.0, 277.0, 296.0)
    knobs = [solver.Knob(FRONT, 200.0, 300.0, 257.0, values=bars), KNOBS[1]]
    evaluate = CountingEvaluator()
    result = solver.solve(knobs, {"understeer": 0.40, "roll": 0.87}, TOLERANCES, evaluate)
    assert result.solution[FRONT] in bars
    assert evaluate.calls[-1][FRONT] in bars, "the verified setup must use a bar that exists"
    assert result.ideal[FRONT] not in bars or result.status == "converged"


def test_failed_simulation_is_reported_instead_of_fitted() -> None:
    def broken(variant):
        return {"understeer": float("nan"), "roll": 0.9}

    with pytest.raises(RuntimeError, match="missing or non-finite"):
        solver.solve(KNOBS, {"understeer": 0.4}, {"understeer": 0.01}, CountingEvaluator(broken))


def test_correction_loop_recovers_from_a_surrogate_that_is_wrong() -> None:
    """Cross terms are outside a separable fit, so the first proposal misses."""
    def coupled(variant):
        out = vehicle(variant)
        front = variant[FRONT] - 257.0
        rear = variant[REAR] - 535.0
        out["understeer"] += 6.0e-5 * front * rear
        return out

    evaluate = CountingEvaluator(coupled)
    result = solver.solve(
        KNOBS[:2], {"understeer": 0.42, "roll": 0.86}, TOLERANCES, evaluate, snap_discrete=False
    )
    assert result.status == "converged"
    verifications = [e for e in result.evaluations if e.kind == "verify"]
    assert len(verifications) >= 2, "this case is only a fair test if the first proposal missed"
