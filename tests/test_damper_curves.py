from copy import deepcopy
from dataclasses import replace
import json
from pathlib import Path

import numpy as np
import pytest
import yaml

from _0_Utils.damper_curves import resolve_damper_curve, write_modelica_damper_tables
from _0_Utils.dyn_py import create_model, load_reduced_vehicle_parameters
from _0_Utils.vehicle_io import load_yaml, repo_root
from _5_App.modelica_generator import plan_modelica_stack, _modelica_stack_signatures


def ttx(ls=6, hs=4.3, rebound_ls=10):
    return {"damper": {
        "model": "ohlins_ttx25_mkii", "dataset": "ttx25_mkii_c12_r12_pdf_v1",
        "compression": {"valve": "C12", "low_speed_clicks_from_closed": ls,
                        "high_speed_turns_from_open": hs},
        "rebound": {"valve": "R12", "low_speed_clicks_from_closed": rebound_ls,
                    "high_speed_turns_from_open": 4.3},
    }}


def test_digitized_reference_points_and_asymmetry():
    curve = resolve_damper_curve(ttx())
    # Independently read from the page-2 curves at 100 mm/s, to plotting precision.
    assert curve.force(0.1) == pytest.approx(240, abs=8)
    assert curve.force(-0.1) == pytest.approx(-90, abs=8)
    assert curve.force(0) == 0
    assert not curve.provenance["compression"]["interpolated"]
    assert curve.velocity_limits == (-0.25, 0.25)


def test_setting_interpolation_stays_between_measured_neighbors():
    middle = resolve_damper_curve(ttx(ls=8))
    lo, hi = (resolve_damper_curve(ttx(ls=n)) for n in (6, 10))
    for v in (0, 0.003, 0.08, 0.25):
        assert middle.force(v) == pytest.approx((lo.force(v) + hi.force(v)) / 2)
    middle_hs = resolve_damper_curve(ttx(ls=0, hs=1.5))
    a, b = (resolve_damper_curve(ttx(ls=0, hs=h)) for h in (1, 2))
    assert middle_hs.force(.1) == pytest.approx((a.force(.1) + b.force(.1)) / 2)
    assert middle.provenance["compression"]["interpolated"]


@pytest.mark.parametrize("ls,hs", [
    (6, 2), (-1, 4.3), (26, 4.3), (0, 5), (0, -1), (2.5, 4.3), (True, 4.3), (0, float('nan')),
])
def test_unsupported_settings_are_not_silently_approximated(ls, hs):
    with pytest.raises(ValueError):
        resolve_damper_curve(ttx(ls=ls, hs=hs))


def test_invalid_identity_and_conflicting_inputs():
    for field, value in (("model", "ttx25"), ("dataset", "../../file")):
        shock = ttx()
        shock["damper"][field] = value
        with pytest.raises(ValueError):
            resolve_damper_curve(shock)
    shock = ttx()
    shock["damper_table"] = {"table": [[-1, -850], [0, 0], [1, 850]]}
    with pytest.raises(ValueError, match="exactly one"):
        resolve_damper_curve(shock)
    shock = ttx()
    shock["damper"]["compression"]["valve"] = "C13"
    with pytest.raises(ValueError, match="Unsupported compression valve"):
        resolve_damper_curve(shock)


def test_legacy_linear_table_and_extrapolation():
    curve = resolve_damper_curve({"damper_table": {"table": [[-1, -850], [0, 0], [1, 850]]}})
    for v in np.linspace(-2, 2, 101):
        assert curve.force(v) == pytest.approx(850 * v)


def test_modelica_damper_sync_preserves_other_record_content(tmp_path):
    data = load_yaml(repo_root() / "vehicle.yml")
    record = tmp_path / "VehicleRecord.mo"
    original = (
        "parameter Axle.AxleDW_BC_StabarRecord pFrAxleDW(\n"
        "  springFreeLength = 0.2, damperTable = [-1, -850; 0, 0; 1, 850]);\n"
        "parameter Axle.AxleDW_BC_StabarRecord pRrAxleDW(\n"
        "  springFreeLength = 0.3, damperTable = [-1, -1300; 0, 0; 1, 1300]);\n"
        "parameter QSSInitializationRecord pQSSInitialization(referenceVelocity = 15);\n"
    )
    record.write_text(original, encoding="utf-8")

    assert write_modelica_damper_tables(data, record)
    changed = record.read_text(encoding="utf-8")
    assert "springFreeLength = 0.2" in changed
    assert "springFreeLength = 0.3" in changed
    assert "pQSSInitialization(referenceVelocity = 15)" in changed
    assert "-0.25, -324.8" in changed
    assert not write_modelica_damper_tables(data, record)


@pytest.mark.parametrize("table", [
    [[-1, -1], [0, 0], [0, 1]], [[-1, 1], [0, 0], [1, 1]],
    [[-1, -1], [0, 1], [1, 1]], [[-1, -1], [0, 0], [1, float('inf')]],
])
def test_invalid_tables_fail(table):
    with pytest.raises(ValueError):
        resolve_damper_curve({"damper_table": {"table": table}})


def test_every_measured_setting_remains_passive_including_extrapolation():
    for ls, hs in [(n, 4.3) for n in (0, 2, 4, 6, 10, 15, 25)] + [(0, h) for h in (0, 1, 2, 3)]:
        shock = ttx(ls=ls, hs=hs, rebound_ls=ls)
        shock["damper"]["rebound"]["high_speed_turns_from_open"] = hs
        curve = resolve_damper_curve(shock)
        assert all(v * curve.force(v) >= 0 for v in np.linspace(-1, 1, 201))


def test_yaml_generation_and_dataset_changes_invalidate_signature(tmp_path, monkeypatch):
    data = load_yaml(repo_root() / "vehicle.yml")
    shock = data["front"]["actuation"]["shock"]
    shock.pop("damper_table", None)
    shock.update(ttx())
    vehicle = tmp_path / "vehicle.yml"
    vehicle.write_text(yaml.safe_dump(data), encoding="utf-8")
    plan = plan_modelica_stack(vehicle, root=repo_root())
    text = plan.contents[0][1]
    assert "ttx25_mkii_c12_r12_pdf_v1" in text
    assert "dataset_sha256" in text
    expected = resolve_damper_curve(shock).force(.1)
    assert f"0.1, {expected:g}" in text
    original = _modelica_stack_signatures(plan)
    dataset_path = repo_root() / "_0_Utils/damper_data/ttx25_mkii_c12_r12_pdf_v1.json"
    raw = dataset_path.read_bytes()
    read_bytes = Path.read_bytes

    def altered(path):
        if path == dataset_path:
            return raw + b"\n"
        return read_bytes(path)

    monkeypatch.setattr(Path, "read_bytes", altered)
    changed = _modelica_stack_signatures(plan_modelica_stack(vehicle, root=repo_root()))
    assert changed["vehicle"]["generated"] != original["vehicle"]["generated"]


def test_reduced_model_evaluates_curve_with_power_preserving_motion_ratio(tmp_path):
    data = load_yaml(repo_root() / "vehicle.yml")
    for axle in ("front", "rear"):
        data[axle]["actuation"]["shock"].pop("damper_table", None)
        data[axle]["actuation"]["shock"].update(deepcopy(ttx()))
    path = tmp_path / "vehicle.yml"
    path.write_text(yaml.safe_dump(data), encoding="utf-8")
    parameters = load_reduced_vehicle_parameters(path, kinematics_sample_count=5)
    parameters = replace(parameters, damper_motion_ratios=(2., 2., 2., 2.))
    model = create_model(6, parameters)
    speeds = np.array([.2, -.2, .05, -.05])
    actual = model._suspension_force_from_compression(np.zeros(4), speeds, np.zeros(4))
    curve = resolve_damper_curve(ttx())
    expected = np.array([curve.force(v / 2) / 2 for v in speeds])
    np.testing.assert_allclose(actual, expected)
    assert np.all(actual * speeds >= 0)
    assert not np.isclose(actual[0], -actual[1])
    # Interior shape matters even with unchanged endpoints.
    assert not np.isclose(curve.force(.1), .1 * (curve.table[-1][1] - curve.table[0][1]) / .5)


def test_dataset_has_reproducible_raw_samples():
    root = repo_root() / "_0_Utils/damper_data"
    dataset = json.loads((root / "ttx25_mkii_c12_r12_pdf_v1.json").read_text())
    samples = json.loads((root / "c12_r12_pixel_samples.json").read_text())
    assert len(dataset["curves"]) == 22
    assert len(samples) == 22 * (len(dataset["velocity_mps"]) - 1)


def test_app_architecture_defaults_preserve_named_damper_and_explicit_conflicts():
    from _5_App.data_services import _vehicle_with_architecture_defaults

    data = load_yaml(repo_root() / "vehicle.yml")
    shock = data["front"]["actuation"]["shock"]
    shock.pop("damper_table", None)
    shock.update(ttx())
    for architecture in ("direct", "bellcrank", "bellcrank_stabar"):
        data["architecture"]["front"] = architecture
        data = _vehicle_with_architecture_defaults(data, prune_inactive=True)
        shock = data["front"]["actuation"]["shock"]
        assert "damper_table" not in shock
        assert resolve_damper_curve(shock).force(.1) > 0
    shock["damper_table"] = {"table": [[-1, -850], [0, 0], [1, 850]]}
    _vehicle_with_architecture_defaults(data)
    with pytest.raises(ValueError, match="exactly one"):
        resolve_damper_curve(shock)
