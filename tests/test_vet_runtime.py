"""vet_runtime decides which knobs are trusted on a reused executable.

The real check runs a compiled simulator; here a fake runner stands in so the
verdict logic is pinned without OpenModelica: an override that changes the
result is live, one that doesn't is flagged, and a knob the init XML can't take
is rejected before anything runs.
"""

from __future__ import annotations

import subprocess
from typing import Any

import pytest

pytest.importorskip("scipy", reason="the OptSim pipeline package imports scipy")

from optimization.response.pipeline import overrides, vet_runtime  # noqa: E402

LIVE = "pVehicle.chassis.frontAxle.stabilizer.barRate"
DEAD = "pVehicle.chassis.frontAxle.tire.wheel.geometry.staticAlpha"
FROZEN = "pVehicle.chassis.frame.baseMass.m"

VARIABLES: dict[str, dict[str, Any]] = {
    "front.stabar": {
        "path": "front.stabar",
        "block": "chassis.frontAxle.stabilizer",
        "param": "barRate",
        "range": [300.0, 900.0],
    },
    "front.toe": {
        "path": "front.toe",
        "block": "chassis.frontAxle.tire.wheel.geometry",
        "param": "staticAlpha",
        "range": [-1.0, 0.5],
    },
    "mass": {"path": "mass", "block": "chassis.frame.baseMass", "param": "m", "range": [180.0, 220.0]},
}
BASELINE = {"front.stabar": 535.0, "front.toe": 0.0, "mass": 200.0}
INIT = {
    LIVE: overrides.InitParameter(start=535.0, changeable=True),
    DEAD: overrides.InitParameter(start=0.0, changeable=True),
    FROZEN: overrides.InitParameter(start=200.0, changeable=False),
}


class FakeSim:
    """Result depends only on the bar rate, like a build that folded toe away."""

    def __init__(self) -> None:
        self.calls: list[dict[str, float]] = []

    def __call__(self, names: dict[str, float]) -> list[list[str]]:
        self.calls.append(dict(names))
        roll = names.get(LIVE, 535.0) / 1000.0
        toe = str(names.get(DEAD, 0.0))  # echoed into the result, but never used
        return [["time", "toe", "roll"], ["0", toe, "0"], ["1", toe, str(roll)]]


def test_probe_moves_to_the_far_edge_of_the_range() -> None:
    assert vet_runtime.probe_value({"range": [300.0, 900.0]}, 535.0) == 900.0
    assert vet_runtime.probe_value({"range": [-1.0, 0.5]}, 0.0) == -1.0
    assert vet_runtime.probe_value({"range": [-1.0, 1.0]}, 0.0) == 1.0, "a tie goes high"


def test_verdicts_separate_live_ignored_and_compiled_knobs() -> None:
    sim = FakeSim()
    verdicts = {v.path: v for v in vet_runtime.vet(VARIABLES, BASELINE, {}, INIT, sim)}
    assert verdicts["front.stabar"].status == "live"
    assert verdicts["front.toe"].status == "no effect", "accepted but ignored must not read as live"
    assert verdicts["mass"].status == "rejected"
    assert "fixed at compile time" in verdicts["mass"].detail
    assert sim.calls == [{}, {LIVE: 900.0}, {DEAD: -1.0}], "a rejected knob never runs"


def test_only_requested_paths_are_vetted() -> None:
    sim = FakeSim()
    verdicts = vet_runtime.vet(VARIABLES, BASELINE, {}, INIT, sim, paths=["front.toe"])
    assert [v.path for v in verdicts] == ["front.toe"]
    assert len(sim.calls) == 2


def test_a_knob_that_needs_missing_metrics_is_skipped_not_failed(monkeypatch: pytest.MonkeyPatch) -> None:
    def needs_metrics(*_: Any) -> dict[str, float]:
        raise KeyError("front_motion_ratio")

    monkeypatch.setattr(overrides, "variant_overrides", needs_metrics)
    (verdict,) = vet_runtime.vet(VARIABLES, BASELINE, {}, INIT, FakeSim(), paths=["front.stabar"])
    assert verdict.status == "skipped"
    assert "front_motion_ratio" in verdict.detail


def test_a_signal_that_never_moves_is_not_evidence() -> None:
    base = [["time", "toe", "roll"], ["0", "0", "0"], ["1", "0", "0.5"]]
    echoed = [["time", "toe", "roll"], ["0", "1", "0"], ["1", "1", "0.5"]]
    rolled = [["time", "toe", "roll"], ["0", "0", "0"], ["1", "0", "0.6"]]
    assert not vet_runtime.changed(base, echoed)
    assert vet_runtime.changed(base, rolled)
    assert vet_runtime.changed(base, base[:2]), "a run that stopped early changed"


def test_a_probe_that_crashes_the_simulator_is_reported_not_raised() -> None:
    def crashes_on_toe(names: dict[str, float]) -> list[list[str]]:
        if DEAD in names:
            raise subprocess.CalledProcessError(255, ["sim"])
        return FakeSim()(names)

    seen: list[str] = []
    verdicts = vet_runtime.vet(
        VARIABLES, BASELINE, {}, INIT, crashes_on_toe, jobs=2, report=lambda v: seen.append(v.path)
    )
    assert [v.status for v in verdicts] == ["live", "run failed", "rejected"], "results keep the DOE order"
    assert sorted(seen) == sorted(VARIABLES), "every verdict is reported as it lands"
