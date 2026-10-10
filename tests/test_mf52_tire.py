from __future__ import annotations

from itertools import product
import re
import shutil
import subprocess

import numpy as np
import pytest

from common.vehicle_io import parse_tir, repo_root
from engines.dynpy.tire import MF52_COEFFICIENTS, MF52Tire


@pytest.fixture
def coefficients():
    values = parse_tir(repo_root() / "common/tire_templates/16x7p5_10_12psi.tir")
    return {name: float(values[name]) for name in MF52_COEFFICIENTS}


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
@pytest.mark.parametrize("variant", ["default", "shifted", "rolling"])
def test_boblib_wrench_parity(coefficients, tmp_path, variant):
    # Exercise shifts and scale factors that happen to be zero/unity in the default fit.
    if variant != "default":
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
    if variant == "rolling":
        coefficients.update(
            QSY1=0.012, QSY2=0.003, QSY3=0.002, QSY4=0.0004, QSX2=0.1, SSZ1=0.01, SSZ2=0.02, SSZ3=0.03, SSZ4=0.01
        )
    points = np.array(
        list(product([0, 50, 100, 650, 1800], [-0.25, -0.08, 0, 0.08, 0.25], [-0.15, 0, 0.07, 0.15], [-0.06, 0, 0.06]))
    )
    points = np.column_stack((points, np.resize([-12.0, 0.0, 24.0], len(points))))
    root = repo_root() / "engines/boblib/BobLib"
    records = root / "Records/VehicleRecord/Chassis/Suspension/Templates/Tire/MF52"
    declarations = []
    for group, record, variable in [
        ("PureSlip", "FxPureRecord", "px"),
        ("PureSlip", "FyPureRecord", "py"),
        ("CombinedSlip", "FxCombinedRecord", "cx"),
        ("CombinedSlip", "FyCombinedRecord", "cy"),
        ("PureSlip", "MxPureRecord", "pmx"),
        ("PureSlip", "MyPureRecord", "pmy"),
        ("PureSlip", "MzPureRecord", "pmz"),
        ("CombinedSlip", "MxCombinedRecord", "cmx"),
        ("CombinedSlip", "MyCombinedRecord", "cmy"),
        ("CombinedSlip", "MzCombinedRecord", "cmz"),
    ]:
        fields = re.findall(r"\bReal\s+(\w+)", (records / group / (record + ".mo")).read_text())
        args = ",".join(f"{key}={coefficients['LONGVL' if key == 'Vref' else key]:.17g}" for key in fields)
        declarations.append(f"parameter R.{group}.{record} {variable}=R.{group}.{record}({args});")
    rows = ",".join("{" + ",".join(f"{v:.17g}" for v in row) + "}" for row in points)
    source = f"""model TireParity
      import R=BobLib.Records.VehicleRecord.Chassis.Suspension.Templates.Tire.MF52;
      import T=BobLib.Chassis.Suspension.Tires.MF52;
      Boolean ok;
    protected
      parameter R.SetupRecord setup(FNOMIN={coefficients["FNOMIN"]}, FZMIN=100, FZMAX=1800, UNLOADED_RADIUS=.2032);
      {" ".join(declarations)}
      parameter R.MF52Record tire(setup=setup, relaxation=R.RelaxationRecord(),
        fxPure=px, fyPure=py, fxCombined=cx, fyCombined=cy,
        mxPure=pmx, myPure=pmy, mzPure=pmz, mxCombined=cmx, myCombined=cmy, mzCombined=cmz);
      parameter Real points[{len(points)},5]={{{rows}}};
      Real fx;
      Real fy;
      Real mx;
      Real my;
      Real mz;
      Real trail;
      Real arm;
    algorithm
      when initial() then
      for i in 1:size(points,1) loop
        (fx,fy,mx,my,mz,trail,arm) := T.Eval(points[i,1],points[i,2],points[i,3],points[i,4],points[i,5],tire);
        Modelica.Utilities.Streams.print(String(fx,significantDigits=16)+","+String(fy,significantDigits=16)
          +","+String(mx,significantDigits=16)+","+String(my,significantDigits=16)
          +","+String(mz,significantDigits=16),"forces.csv");
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
    actual = np.column_stack(MF52Tire(coefficients).evaluate(*points.T))
    np.testing.assert_allclose(actual, expected, rtol=1e-10, atol=1e-8)


def test_algebraic_slip_matches_combined_force_and_rejects_excess(coefficients):
    tire = MF52Tire(coefficients)
    loads = np.array([300.0, 600.0, 900.0, 1200.0])
    alpha = np.array([-0.08, 0.04, 0.09, -0.03])
    gamma = np.array([-0.04, 0.02, 0.03, -0.01])
    demand = np.array([-150.0, 250.0, -300.0, 500.0])
    slip = tire.slip_for_force(loads, alpha, gamma, demand)
    actual = tire.forces(loads, alpha, slip, gamma)[0]
    np.testing.assert_allclose(actual, demand, atol=1e-7)
    assert np.all(np.sign(slip) == np.sign(demand))
    for direction in [-1, 1]:
        saturated = tire.slip_for_force(loads, alpha, gamma, direction * 1e6)
        force = direction * tire.forces(loads, alpha, saturated, gamma)[0]
        for offset in [-1e-4, 1e-4]:
            neighbor = (
                direction
                * tire.forces(
                    loads, alpha, np.clip(saturated + offset, coefficients["KPUMIN"], coefficients["KPUMAX"]), gamma
                )[0]
            )
            assert np.all(force >= neighbor)


def test_moment_limits_and_velocity_broadcast(coefficients):
    tire = MF52Tire({**coefficients, 'QSY1': .02, 'QSY3': .005})
    wrench = tire.evaluate(650., .08, .02, .03, np.array([12., 24.]))
    assert all(component.shape == (2,) for component in wrench)
    assert wrench[3][1] < wrench[3][0] < 0
    np.testing.assert_array_equal(tire.evaluate(0, .08, .02, .03, 12), 0)
    low = tire.evaluate(50, .08, .02, .03, 12)
    at_min = tire.evaluate(100, .08, .02, .03, 12)
    np.testing.assert_allclose(low, np.asarray(at_min)*.5)
    no_grip = MF52Tire({**coefficients, 'LMUX': 0., 'LMUY': 0.})
    result = no_grip.evaluate(650, .08, .02, .03, 12)
    assert np.isfinite(result).all()
    np.testing.assert_array_equal([result[0], result[1], result[4]], 0)


def test_slip_fit_bounds_are_inclusive_and_tire_specific(coefficients):
    tire = MF52Tire({**coefficients, "ALPMIN": -0.1, "ALPMAX": 0.2,
                     "KPUMIN": -0.08, "KPUMAX": 0.12})
    np.testing.assert_array_equal(
        tire.slip_in_fit_range([-0.1, 0.2, -0.11, 0.21, 0, 0, np.nan],
                               [-0.08, 0.12, 0, 0, -0.09, 0.13, 0]),
        [True, True, False, False, False, False, False],
    )
