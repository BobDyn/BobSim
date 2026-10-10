from __future__ import annotations

from itertools import product
import re
import shutil
import subprocess

import numpy as np
import pytest

from common.vehicle_io import parse_tir, repo_root
from engines.dynpy.tire import FORCE_COEFFICIENTS, MF52Tire


@pytest.fixture
def coefficients():
    values = parse_tir(repo_root() / "common/tire_templates/16x7p5_10_12psi.tir")
    return {name: float(values[name]) for name in FORCE_COEFFICIENTS}


def test_force_signs_peak_and_contact(coefficients):
    tire = MF52Tire(coefficients)
    angle = np.linspace(0, 0.5, 501)
    _, lateral = tire.forces(650, angle, 0)
    peak = int(np.argmax(lateral))
    assert 0 < peak < len(angle) - 1
    assert lateral[-1] < lateral[peak] * 0.95
    fx, fy = tire.forces([0, -100, 650, 650], [0.1] * 4, [0, 0, -0.05, 0.05])
    np.testing.assert_array_equal(fx[:2], 0)
    np.testing.assert_array_equal(fy[:2], 0)
    assert fx[2] < 0 < fx[3]
    assert np.all(fy[2:] > 0)
    low = tire.forces(50, 0.08, 0.03)
    at_min = tire.forces(100, 0.08, 0.03)
    np.testing.assert_allclose(low, np.asarray(at_min) * 0.5)


def test_low_grip_is_not_floored(coefficients):
    tire = MF52Tire(coefficients)
    low_grip = MF52Tire({**coefficients, "LMUX": 0.1, "LMUY": 0.1})
    slip = np.linspace(-0.3, 0.3, 1001)
    fx, _ = low_grip.forces(650, 0, slip)
    _, fy = low_grip.forces(650, slip, 0)
    assert max(abs(fx)) / 650 < 0.3
    assert max(abs(fy)) / 650 < 0.3
    _, reference = tire.forces(650, slip, 0)
    assert max(abs(reference)) > 5 * max(abs(fy))
    zero_grip = MF52Tire({**coefficients, "LMUX": 0, "LMUY": 0})
    np.testing.assert_array_equal(zero_grip.forces(650, slip, slip), 0)


def test_coefficients_are_validated_and_copied(coefficients):
    tire = MF52Tire(coefficients)
    coefficients["LMUY"] = 0
    assert tire.coefficients["LMUY"] == 1
    with pytest.raises(ValueError, match="Missing MF5.2"):
        MF52Tire({})
    with pytest.raises(ValueError, match="finite"):
        MF52Tire({**coefficients, "PDX1": float("nan")})


@pytest.mark.skipif(shutil.which("omc") is None, reason="OpenModelica required for independent tire parity")
@pytest.mark.parametrize("perturbed", [False, True])
def test_boblib_force_parity(coefficients, tmp_path, perturbed):
    # Exercise shifts and scale factors that happen to be zero/unity in the default fit.
    if perturbed:
        coefficients.update({name: 0.83 for name in coefficients if name.startswith("L")})
        coefficients.update(
            dict(
                PHX1=0.012,
                PHX2=0.003,
                PVX1=0.02,
                PVX2=0.005,
                PHY1=0.006,
                PHY2=0.002,
                PHY3=0.1,
                PVY1=0.03,
                PVY2=0.01,
                PVY3=0.2,
                PVY4=0.1,
                RHX1=0.01,
                RHY1=0.01,
                RHY2=0.003,
                RVY1=0.1,
                RVY2=0.02,
                RVY3=0.03,
                RVY4=2,
                RVY5=1.5,
                RVY6=3,
            )
        )
    points = np.array(
        list(product([0, 50, 100, 650, 1800], [-0.25, -0.08, 0, 0.08, 0.25], [-0.15, 0, 0.07, 0.15], [-0.06, 0, 0.06]))
    )
    root = repo_root() / "engines/boblib/BobLib"
    records = root / "Records/VehicleRecord/Chassis/Suspension/Templates/Tire/MF52"
    declarations = []
    for group, record, variable in [
        ("PureSlip", "FxPureRecord", "px"),
        ("PureSlip", "FyPureRecord", "py"),
        ("CombinedSlip", "FxCombinedRecord", "cx"),
        ("CombinedSlip", "FyCombinedRecord", "cy"),
    ]:
        fields = re.findall(r"\bReal\s+(\w+)", (records / group / (record + ".mo")).read_text())
        args = ",".join(f"{key}={coefficients[key]:.17g}" for key in fields)
        declarations.append(f"parameter R.{group}.{record} {variable}=R.{group}.{record}({args});")
    rows = ",".join("{" + ",".join(f"{v:.17g}" for v in row) + "}" for row in points)
    source = f"""model TireParity
      import R=BobLib.Records.VehicleRecord.Chassis.Suspension.Templates.Tire.MF52;
      import T=BobLib.Chassis.Suspension.Tires.MF52.CombinedSlip;
      Boolean ok;
    protected
      parameter R.SetupRecord setup(FNOMIN={coefficients["FNOMIN"]}, FZMIN=100, FZMAX=1800, UNLOADED_RADIUS=.2032);
      {" ".join(declarations)}
      parameter Real points[{len(points)},4]={{{rows}}};
      Real fz;
      Real scale;
      Real fx;
      Real fy;
    algorithm
      when initial() then
      for i in 1:size(points,1) loop
        fz := max(points[i,1],setup.FZMIN);
        scale := if points[i,1]>1e-3 then points[i,1]/fz else 0;
        fx := scale*T.FxCombinedEval(fz,points[i,3],points[i,2],points[i,4],px,cx,setup);
        fy := -scale*T.FyCombinedEval(fz,points[i,2],points[i,3],points[i,4],py,cy,setup);
        Modelica.Utilities.Streams.print(String(fx,significantDigits=16)+","+String(fy,significantDigits=16),"forces.csv");
      end for;
      ok := true;
      end when;
    end TireParity;
    """
    (tmp_path / "TireParity.mo").write_text(source)
    (tmp_path / "run.mos").write_text(
        f'loadModel(Modelica);\nloadFile("{(root / "package.mo").as_posix()}");\n'
        'loadFile("TireParity.mo");\nsimulate(TireParity,stopTime=0.001,numberOfIntervals=1);\ngetErrorString();\n'
    )
    run = subprocess.run(["omc", "run.mos"], cwd=tmp_path, capture_output=True, text=True, timeout=120)
    assert (tmp_path / "forces.csv").exists(), run.stdout + run.stderr
    expected = np.loadtxt(tmp_path / "forces.csv", delimiter=",")
    actual = np.column_stack(MF52Tire(coefficients).forces(*points.T))
    np.testing.assert_allclose(actual, expected, rtol=1e-10, atol=1e-8)
