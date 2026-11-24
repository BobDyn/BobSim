"""The DOE damper knob scales the measured force curve instead of breaking it.

The knob used to write the first and third entries of a 3-row linear table.
Once BobLib's dampers became 27-row TTX25 curves, that put a force of minus the
rate at -0.25 m/s and plus the rate at -0.2 m/s, which crashed VehicleSim. Now
the swept value is the rate at zero velocity and every entry of the force
column scales with it.
"""

from __future__ import annotations

from pathlib import Path
from typing import Any

import pytest

pytest.importorskip("scipy", reason="the OptSim pipeline package imports scipy")

from optimization.response.pipeline import generate_configs, generator, overrides  # noqa: E402
from optimization.response.pipeline.modelica_params import read_table  # noqa: E402
from optimization.response.pipeline.sampler import read_baseline  # noqa: E402

ROOT = Path(__file__).resolve().parents[1]
RECORD = ROOT / "engines/boblib/BobLib/Records/VehicleDefn/EVBatInvMotDiff_DWBCStabar_DWBCStabarRecord.mo"
BLOCK = "chassis.frontAxle.actuation"

# Digressive like a real damper: 600 N*s/m just below zero, softer at speed.
TABLE = [[-0.2, -80.0], [-0.1, -50.0], [-0.05, -30.0], [0.0, 0.0], [0.05, 45.0], [0.2, 110.0]]
RECORD_TEXT = (
    "record R\n  parameter ChassisRecord chassis(\n    frontAxle(\n      actuation(\n"
    "        springTable = [0, 0; 1, 26000],\n        damperTable = ["
    + "; ".join(f"{v:g}, {f:g}" for v, f in TABLE)
    + "])));\nend R;\n"
)
TARGET = {"block": BLOCK, "param": "damperTable", "operation": "scale_column", "column": 1}
VARIABLE: dict[str, Any] = {"path": "front.actuation.damper_rate_n_s_per_m", "range": [480.0, 720.0]}


def _spec() -> dict[str, Any]:
    return {**VARIABLE, "targets": generate_configs.expand_scale_column(TARGET, RECORD_TEXT, VARIABLE)}


def _patched_table(value: float) -> list[list[float]]:
    text = generator.substitute_variable(RECORD_TEXT, _spec(), value)
    return read_table(text, {"block": BLOCK, "param": "damperTable"})


def test_rate_at_zero_is_the_slope_just_below_zero() -> None:
    assert generate_configs.rate_at_zero(TABLE) == pytest.approx(600.0)
    assert generate_configs.rate_at_zero([[0, 0], [1, 850]]) == pytest.approx(850.0)


def test_the_baseline_value_reproduces_the_record() -> None:
    flat = [x for row in _patched_table(600.0) for x in row]
    assert flat == pytest.approx([x for row in TABLE for x in row])


def test_a_swept_rate_scales_every_force_and_keeps_the_curve_shape() -> None:
    table = _patched_table(720.0)
    assert [v for v, _ in table] == [v for v, _ in TABLE], "velocities never move"
    assert [f for _, f in table] == pytest.approx([1.2 * f for _, f in TABLE])
    assert generate_configs.rate_at_zero(table) == pytest.approx(720.0)
    forces = [f for _, f in table]
    assert forces == sorted(forces), "force still rises with velocity"


def test_the_baseline_reads_back_as_the_rate(tmp_path: Path) -> None:
    record = tmp_path / "R.mo"
    record.write_text(RECORD_TEXT)
    assert read_baseline(record, [_spec()])[VARIABLE["path"]] == pytest.approx(600.0)


def test_an_override_on_a_compiled_executable_writes_the_same_forces() -> None:
    spec = _spec()
    names = {overrides.override_name(t): t for t in spec["targets"]}
    init = {name: overrides.InitParameter(start=0.0, changeable=True) for name in names}
    written = overrides.variant_overrides({spec["path"]: 720.0}, {spec["path"]: spec}, {}, init)
    expected = {
        f"{overrides.VEHICLE_RECORD}.{BLOCK}.damperTable[{i + 1},2]": 1.2 * f
        for i, (_, f) in enumerate(TABLE)
        if f != 0.0
    }
    assert written == pytest.approx(expected)


def test_a_curve_outside_the_sweep_range_fails_generation() -> None:
    with pytest.raises(ValueError, match="outside the sweep range"):
        generate_configs.expand_scale_column(TARGET, RECORD_TEXT, {**VARIABLE, "range": [680.0, 1020.0]})


@pytest.mark.skipif(not RECORD.is_file(), reason="needs the BobLib submodule")
def test_the_real_curves_match_what_the_vehicle_review_reports() -> None:
    from simulations.envelope.vehicle_review.vehicle_review_sim import _table_rate_at_value

    text = RECORD.read_text()
    for axle in ("frontAxle", "rearAxle"):
        table = read_table(text, {"block": f"chassis.{axle}.actuation", "param": "damperTable"})
        assert generate_configs.rate_at_zero(table) == pytest.approx(_table_rate_at_value(table, 0.0))
