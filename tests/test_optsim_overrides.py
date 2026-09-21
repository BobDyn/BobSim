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

from StandardSens import solve_setup  # noqa: E402
from StandardSens.pipeline import evaluator, overrides  # noqa: E402
from StandardSens.pipeline.generator import resolve_targets  # noqa: E402

# (name, runtime-changeable, compiled-in start value or None for "has none")
INIT_SCALARS = [
    ("pVehicle.pRrStabar.barRate", True, 535.0),
    ("pVehicle.pFrAxleDW.springTable[2,2]", True, 26000.0),
    ("pVehicle.pFrAxleDW.damperTable[1,2]", True, -850.0),
    ("pVehicle.pFrAxleDW.damperTable[3,2]", True, 850.0),
    ("pVehicle.pAero.downforceTable[1,1]", True, 10.0),
    ("pVehicle.pFrozen.value", False, 1.0),
    ("pVehicle.pNoStart.value", True, None),
]
INIT_XML = (
    '<?xml version="1.0"?><fmiModelDescription><ModelVariables>'
    + "".join(
        f'<ScalarVariable name="{name}" isValueChangeable="{str(changeable).lower()}">'
        + ("<Real/>" if start is None else f'<Real start="{start}"/>')
        + "</ScalarVariable>"
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
    "no_start": {"path": "no_start", "block": "pNoStart", "param": "value"},
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


@pytest.mark.parametrize(
    ("path", "reason"),
    [
        ("typo", "not in the compiled model"),
        # The runner keys its lookup on the start value, so it would drop this
        # one exactly as it drops a name that does not exist.
        ("no_start", "not in the compiled model"),
        ("frozen", "fixed at compile time"),
        ("aero.load_scale", "scaled tables are compiled"),
    ],
)
def test_an_override_that_would_silently_do_nothing_is_an_error(
    init_parameters, path: str, reason: str
) -> None:
    with pytest.raises(ValueError, match=reason):
        overrides.variant_overrides({path: 1.5}, VARIABLES, {}, init_parameters)


def test_writing_a_variant_and_overriding_one_agree_on_the_value() -> None:
    """Both paths go through resolve_targets, so they cannot drift apart."""
    resolved = resolve_targets(VARIABLES["front.damper"], 900.0)
    assert [(t["index"], v) for t, v in resolved] == [([0, 1], -900.0), ([2, 1], 900.0)]
    legacy = {"path": "camber", "block": "pWheel", "param": "staticGamma", "scale": -1.0}
    assert resolve_targets(legacy, -1.5) == [(legacy, 1.5)]


def test_runtime_safe_knobs_share_one_executable_and_the_rest_do_not() -> None:
    bar, toe = "rear.stabar.rate_n_m_per_rad", "front.wheel.toe_deg"
    assert bar in overrides.RUNTIME_SAFE_PATHS
    assert toe not in overrides.RUNTIME_SAFE_PATHS, "toe is baked into the wheel rotation matrix"
    baseline = {bar: 535.0, toe: 0.0}
    soft = evaluator.compiled_part({bar: 400.0, toe: 0.0}, baseline)
    stiff = evaluator.compiled_part({bar: 900.0, toe: 0.0}, baseline)
    toed = evaluator.compiled_part({bar: 900.0, toe: 0.1}, baseline)
    assert soft == stiff == {}, "bar changes must reuse the baseline executable"
    assert toed == {toe: 0.1}, "a toe change must get its own executable"


def test_command_line_targets_replace_the_configured_ones() -> None:
    config = {"targets": {"roll_gradient_deg_per_g": 0.85, "understeer_gradient_deg_per_g": 0.31}}
    assert solve_setup.select_targets(None, config) == config["targets"]
    assert solve_setup.select_targets(
        ["SteadyStateEval_roll_gradient_deg_per_g=0.8"], config
    ) == {"roll_gradient_deg_per_g": 0.8}, "replaced, not merged, and the table prefix is accepted"
    with pytest.raises(ValueError, match="No targets"):
        solve_setup.select_targets(None, {})


def test_every_target_needs_a_stated_tolerance() -> None:
    config = {"tolerances": {"roll_gradient_deg_per_g": 0.02}}
    assert solve_setup.select_tolerances({"roll_gradient_deg_per_g": 0.8}, config) == {
        "roll_gradient_deg_per_g": 0.02
    }
    with pytest.raises(ValueError, match="No tolerance for \\['sideslip"):
        solve_setup.select_tolerances({"sideslip_gradient_deg_per_g": 0.5}, config)
