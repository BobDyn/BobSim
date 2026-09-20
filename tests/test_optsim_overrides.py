"""Mapping a DOE variable onto runtime overrides of a compiled executable.

The runner drops any override name it cannot find without saying so, and
OpenModelica accepts overrides of parameters it has already baked into the
executable. Both failures are silent and both leave a knob at baseline while the
solver believes it moved, so the mapping is checked here against a small
hand-written init XML rather than trusted.
"""

from __future__ import annotations

from pathlib import Path
import sys

import pytest

ROOT = Path(__file__).resolve().parents[1]
OPTSIM_DIR = ROOT / "_4_OptSim"
if str(OPTSIM_DIR) not in sys.path:
    sys.path.insert(0, str(OPTSIM_DIR))

pytest.importorskip("scipy", reason="the OptSim pipeline package imports scipy")

from StandardSens.pipeline import evaluator, overrides  # noqa: E402
from StandardSens.pipeline.generator import resolve_targets  # noqa: E402

# (name, runtime-changeable, compiled-in start value)
INIT_SCALARS = [
    ("pVehicle.pRrStabar.barRate", True, 535.0),
    ("pVehicle.pFrAxleDW.springTable[2,2]", True, 26000.0),
    ("pVehicle.pFrAxleDW.damperTable[1,2]", True, -850.0),
    ("pVehicle.pFrAxleDW.damperTable[3,2]", True, 850.0),
    ("pVehicle.pAero.downforceTable[1,1]", True, 10.0),
    ("pVehicle.pAero.downforceTable[1,2]", True, 20.0),
    # A bound copy further down the hierarchy: same leaf name, not a root.
    ("aeroModel.pAero.downforceTable[1,1]", False, 10.0),
    ("pVehicle.pFrozen.value", False, 1.0),
]
INIT_XML = (
    '<?xml version="1.0"?><fmiModelDescription><ModelVariables>'
    + "".join(
        f'<ScalarVariable name="{name}" isValueChangeable="{str(changeable).lower()}">'
        f'<Real start="{start}"/></ScalarVariable>'
        for name, changeable, start in INIT_SCALARS
    )
    + "</ModelVariables></fmiModelDescription>"
)

VARIABLES = {
    "rear.stabar": {"path": "rear.stabar", "block": "pRrStabar", "param": "barRate"},
    "front.spring": {
        "path": "front.spring",
        "targets": [{"block": "pFrAxleDW", "param": "springTable", "index": [1, 1]}],
    },
    "front.damper": {
        "path": "front.damper",
        "targets": [
            {"block": "pFrAxleDW", "param": "damperTable", "index": [0, 1], "scale": -1},
            {"block": "pFrAxleDW", "param": "damperTable", "index": [2, 1]},
        ],
    },
    "aero.load_scale": {
        "path": "aero.load_scale",
        "targets": [{"block": "pAero", "param": "downforceTable", "operation": "scale"}],
    },
    "frozen": {"path": "frozen", "block": "pFrozen", "param": "value"},
    "typo": {"path": "typo", "block": "pRrStabar", "param": "barRat"},
}


@pytest.fixture
def init_parameters(tmp_path: Path) -> dict[str, overrides.InitParameter]:
    init_xml = tmp_path / "Model_init.xml"
    init_xml.write_text(INIT_XML)
    return overrides.load_init_parameters(init_xml)


def test_doe_indices_are_zero_based_and_modelica_is_one_based() -> None:
    target = {"block": "pFrAxleDW", "param": "springTable", "index": [1, 1]}
    assert overrides.override_name(target) == "pVehicle.pFrAxleDW.springTable[2,2]"
    assert overrides.override_name({"block": "pRrStabar", "param": "barRate"}) == (
        "pVehicle.pRrStabar.barRate"
    )


def test_one_value_fans_out_to_every_target_with_its_scale(init_parameters) -> None:
    result = overrides.variant_overrides(
        {"rear.stabar": 700.0, "front.spring": 30000.0, "front.damper": 900.0},
        VARIABLES,
        {},
        init_parameters,
    )
    assert result == {
        "pVehicle.pRrStabar.barRate": 700.0,
        "pVehicle.pFrAxleDW.springTable[2,2]": 30000.0,
        "pVehicle.pFrAxleDW.damperTable[1,2]": -900.0,
        "pVehicle.pFrAxleDW.damperTable[3,2]": 900.0,
    }


def test_scale_operation_multiplies_the_compiled_baseline(init_parameters) -> None:
    """A scale acts on what is compiled in, and only on the changeable root."""
    result = overrides.variant_overrides({"aero.load_scale": 1.5}, VARIABLES, {}, init_parameters)
    assert result == {
        "pVehicle.pAero.downforceTable[1,1]": 15.0,
        "pVehicle.pAero.downforceTable[1,2]": 30.0,
    }


def test_a_name_the_model_does_not_have_is_an_error_not_a_silent_no_op(init_parameters) -> None:
    with pytest.raises(ValueError, match="not in the compiled model"):
        overrides.variant_overrides({"typo": 1.0}, VARIABLES, {}, init_parameters)


def test_a_parameter_fixed_at_compile_time_is_refused(init_parameters) -> None:
    with pytest.raises(ValueError, match="fixed at compile time"):
        overrides.variant_overrides({"frozen": 2.0}, VARIABLES, {}, init_parameters)


def test_writing_a_variant_and_overriding_one_agree_on_the_value() -> None:
    """Both paths go through resolve_targets, so they cannot drift apart."""
    resolved = resolve_targets(VARIABLES["front.damper"], 900.0)
    assert [(t["index"], v) for t, v in resolved] == [([0, 1], -900.0), ([2, 1], 900.0)]
    legacy = {"path": "camber", "block": "pWheel", "param": "staticGamma", "scale": -1.0}
    assert resolve_targets(legacy, -1.5) == [(legacy, 1.5)]


def test_runtime_knobs_share_one_executable_and_compile_only_knobs_do_not() -> None:
    baseline = {"rear.stabar": 535.0, "front.toe": 0.0}
    runtime = {"rear.stabar"}
    soft = evaluator.compile_key({"rear.stabar": 400.0, "front.toe": 0.0}, runtime, baseline)
    stiff = evaluator.compile_key({"rear.stabar": 900.0, "front.toe": 0.0}, runtime, baseline)
    toed = evaluator.compile_key({"rear.stabar": 900.0, "front.toe": 0.1}, runtime, baseline)
    assert soft == stiff == (), "bar changes must reuse the baseline executable"
    assert toed == (("front.toe", 0.1),), "a toe change must get its own executable"
