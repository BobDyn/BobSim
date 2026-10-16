from __future__ import annotations

from pathlib import Path
import shutil

import pytest
import yaml

from common.vehicle_io import load_yaml
from app.modelica_generator import (
    ARCHITECTURES,
    BobLibRootError,
    generate_modelica_stack,
    modelica_generation_payload,
    modelica_stack_status_payload,
)

BOBLIB_PACKAGE_MO = "within ;\npackage BobLib\nend BobLib;\n"
# The package that simulations/response/mbd/build_*_sim.mos load.
BUILD_BOBLIB = "engines/boblib/BobLib"


def _write_boblib_package(path: Path) -> None:
    path.mkdir(parents=True)
    (path / "package.mo").write_text(BOBLIB_PACKAGE_MO, encoding="utf-8")


def _write_temp_vehicle(
    repo_root: Path, tmp_path: Path, *, boblib: str = BUILD_BOBLIB, brake: bool = False
) -> Path:
    data = load_yaml(repo_root / "common/vehicle_templates/DWBCStabar_DWBCStabarRecord.yml")
    active_data = load_yaml(repo_root / "vehicle.yml")
    if isinstance(active_data.get("powertrain"), dict):
        data["powertrain"] = active_data["powertrain"]
    if brake:
        data["brake"] = active_data["brake"]
    data["paths"] = {"boblib": boblib, "tire_templates": "tires"}
    tire_name = data["aero"].get("tire_template") or data["front"]["tire"]["template"]
    tire_root = tmp_path / "tires"
    tire_root.mkdir()
    shutil.copy(repo_root / "common/tire_templates" / f"{tire_name}.tir", tire_root / f"{tire_name}.tir")
    _write_boblib_package(tmp_path / BUILD_BOBLIB)

    vehicle_path = tmp_path / "vehicle.yml"
    vehicle_path.write_text(yaml.safe_dump(data, sort_keys=False), encoding="utf-8")
    return vehicle_path


def _tree(root: Path) -> dict[str, bytes | None]:
    return {
        path.relative_to(root).as_posix(): path.read_bytes() if path.is_file() else None
        for path in sorted(root.rglob("*"))
    }


def test_modelica_generator_writes_full_boblib_stack(tmp_path: Path) -> None:
    repo_root = Path(__file__).resolve().parents[1]
    vehicle_path = _write_temp_vehicle(repo_root, tmp_path)

    pre_status = modelica_stack_status_payload(vehicle_path, tmp_path)
    assert pre_status["written_to_boblib"] is False
    assert pre_status["state"] == "missing"

    result = generate_modelica_stack(vehicle_path, root=tmp_path)
    payload = modelica_generation_payload(result, tmp_path)
    vehicle_data = load_yaml(vehicle_path)
    post_status = modelica_stack_status_payload(vehicle_path, tmp_path)

    assert result.record_name == "EVBatInvMotDiff_DWBCStabar_DWBCStabarRecord"
    assert result.vehicle_template_name == "VehicleSim_EVBatInvMotDiff_DWBCStabar_DWBCStabar"
    assert result.four_post_template_name == "FourPostSim_EVBatInvMotDiff_DWBCStabar_DWBCStabar"
    record_rel = "Records/VehicleDefn/EVBatInvMotDiff_DWBCStabar_DWBCStabarRecord.mo"
    assert payload["record"]["path"] == f"{BUILD_BOBLIB}/{record_rel}"
    assert post_status["written_to_boblib"] is True
    assert post_status["state"] == "written"
    assert post_status["signatures"]["vehicle"]["generated"]
    assert post_status["signatures"]["four_post"]["generated"]
    assert post_status["signatures"]["vehicle"]["generated"] != post_status["signatures"]["four_post"]["generated"]

    record_text = (tmp_path / payload["record"]["path"]).read_text(encoding="utf-8")
    front_arch = ARCHITECTURES[vehicle_data["architecture"]["front"]]
    rear_arch = ARCHITECTURES[vehicle_data["architecture"]["rear"]]
    assert f"parameter {front_arch.record_type} pFrAxleDW(" in record_text
    assert f"parameter {rear_arch.record_type} pRrAxleDW(" in record_text
    assert "parameter Controllers.VCURecord pVCU(" in record_text
    assert f"tau_max = {vehicle_data['powertrain']['pVCU']['tau_max']}" in record_text
    assert f"P_max_mot = {vehicle_data['powertrain']['pVCU']['P_max_mot']}" in record_text
    assert "parameter ElectricDrives.MotorRecord pMotor(" in record_text
    assert f"P_mech_peak = {vehicle_data['powertrain']['pMotor']['P_mech_peak']}" in record_text
    assert "parameter Modelica.Units.SI.RotationalSpringConstant pTorsionalStiff = 500000;" in record_text
    assert "FNOMIN = 650" in record_text
    assert "UNLOADED_RADIUS = pFrPartialWheel.R0" in record_text

    vehicle_template_text = (
        tmp_path
        / BUILD_BOBLIB
        / "Experiments/Standards/Templates/Vehicle/VehicleSim_EVBatInvMotDiff_DWBCStabar_DWBCStabar.mo"
    ).read_text(encoding="utf-8")
    record_redeclare = (
        "redeclare record VehicleRecord = "
        "BobLib.Records.VehicleDefn.EVBatInvMotDiff_DWBCStabar_DWBCStabarRecord"
    )
    assert record_redeclare in vehicle_template_text
    assert f"redeclare model FrAxleModel = {front_arch.front_model}" in vehicle_template_text
    assert f"redeclare model RrAxleModel = {rear_arch.rear_model}" in vehicle_template_text
    assert ("pFrStabar(" in vehicle_template_text) is front_arch.has_stabar
    assert ("pRrStabar(" in vehicle_template_text) is rear_arch.has_stabar

    four_post_template_text = (
        tmp_path
        / BUILD_BOBLIB
        / "Experiments/Standards/Templates/FourPost/FourPostSim_EVBatInvMotDiff_DWBCStabar_DWBCStabar.mo"
    ).read_text(encoding="utf-8")
    assert "extends BaseFourPostSim(" in four_post_template_text
    assert ("frAxleDW(" in four_post_template_text) is front_arch.has_stabar
    assert ("rrAxleDW(" in four_post_template_text) is rear_arch.has_stabar
    assert ("barRate = 0" in four_post_template_text) is (front_arch.has_stabar or rear_arch.has_stabar)

    vehicle_entry_text = (tmp_path / BUILD_BOBLIB / "Experiments/Standards/VehicleSim.mo").read_text(encoding="utf-8")
    assert "extends Templates.Vehicle.VehicleSim_EVBatInvMotDiff_DWBCStabar_DWBCStabar;" in vehicle_entry_text
    four_post_entry_text = (tmp_path / BUILD_BOBLIB / "Experiments/Standards/FourPostSim.mo").read_text(
        encoding="utf-8"
    )
    assert "extends Templates.FourPost.FourPostSim_EVBatInvMotDiff_DWBCStabar_DWBCStabar;" in four_post_entry_text


def test_modelica_generator_updates_package_order_without_duplicates(tmp_path: Path) -> None:
    repo_root = Path(__file__).resolve().parents[1]
    vehicle_path = _write_temp_vehicle(repo_root, tmp_path)

    first = generate_modelica_stack(vehicle_path, root=tmp_path)
    second = generate_modelica_stack(vehicle_path, root=tmp_path)

    assert second.record_name == first.record_name
    assert (
        tmp_path / BUILD_BOBLIB / "Records/VehicleDefn/package.order"
    ).read_text(encoding="utf-8").splitlines().count(first.record_name) == 1
    assert (
        tmp_path / BUILD_BOBLIB / "Experiments/Standards/Templates/Vehicle/package.order"
    ).read_text(encoding="utf-8").splitlines().count(first.vehicle_template_name) == 1
    assert (
        tmp_path / BUILD_BOBLIB / "Experiments/Standards/Templates/FourPost/package.order"
    ).read_text(encoding="utf-8").splitlines().count(first.four_post_template_name) == 1


def test_bellcrank_pickup_indices_come_from_geometry_not_the_order_list() -> None:
    """BobLib numbers pickups by position on the rocker, not by list order.

    Its annotation is the spec: "1 is the most counter-clockwise pickup about the
    left bellcrank (generally with the lowest Z coordinate)". The baseline lists
    ['rod', 'shock', 'stabar'] on both axles while the true arrangement is
    stabar/rod/shock at the front and rod/shock/stabar at the rear - one list
    cannot encode both, so list position was never a valid source.

    Expected values are the ones BobLib ships in its own checked-in record.
    """
    from common.vehicle_io import load_yaml, vehicle_yaml_path
    from app.modelica_generator import _pickup_order

    vehicle = load_yaml(vehicle_yaml_path())
    expected = {
        "front": {"stabar": 1, "rod": 2, "shock": 3},
        "rear": {"rod": 1, "shock": 2, "stabar": 3},
    }
    for axle, want in expected.items():
        bellcrank = vehicle[axle]["actuation"]["bellcrank"]
        assert _pickup_order(
            bellcrank["pickups_m"], bellcrank["pivot_m"], bellcrank["axis"], axle
        ) == want

    # The axles differ, so one shared order list cannot be the source.
    assert vehicle["front"]["actuation"]["bellcrank"]["order"] == \
        vehicle["rear"]["actuation"]["bellcrank"]["order"]
    assert expected["front"] != expected["rear"]


def test_modelica_generator_cli_reports_then_writes(tmp_path: Path, capsys) -> None:
    """`python -m app.modelica_generator` checks by default and writes on --write."""
    from app import modelica_generator

    repo_root = Path(__file__).resolve().parents[1]
    vehicle_path = _write_temp_vehicle(repo_root, tmp_path)
    argv = [str(vehicle_path), "--root", str(tmp_path)]

    assert modelica_generator.main(argv) == 1
    checked = capsys.readouterr().out
    assert "state:    missing" in checked
    assert "Rerun with --write" in checked

    assert modelica_generator.main([*argv, "--write"]) == 0
    written = capsys.readouterr().out
    assert "state:    written" in written
    assert "stale" not in written

    # A check straight after a write is clean, and writing does not report stale.
    assert modelica_generator.main(argv) == 0
    assert "state:    written" in capsys.readouterr().out


def test_calibrated_initialization_survives_generation_and_rejects_changed_inputs(tmp_path):
    import pytest
    from app.modelica_generator import plan_modelica_stack, _record_parameters
    root = Path(__file__).resolve().parents[1]
    vehicle_path = _write_temp_vehicle(root, tmp_path)
    result = generate_modelica_stack(vehicle_path, root=tmp_path)
    record = result.files[0].path
    pinned = root / 'engines/boblib/BobLib/Records/VehicleDefn' / record.name
    calibration = _record_parameters(pinned.read_text())["pQSSInitialization"]
    record.write_text(record.read_text().replace('  annotation(', calibration + '\n  annotation(', 1))
    generate_modelica_stack(vehicle_path, root=tmp_path)
    assert calibration in record.read_text()
    entry = result.files[3].path.read_text()
    assert 'fixInitialSuspensionAngles = true' in entry
    assert 'initialRearRightLowerArmAngle = pVehicle.pQSSInitialization.rearRightLowerArmAngle' in entry
    assert 'abs(initialVel - pVehicle.pQSSInitialization.referenceVelocity)' in entry
    before = {item.path: item.path.read_bytes() for item in result.files}
    data = load_yaml(vehicle_path)
    data['sprung_mass']['mass_kg'] += 10
    vehicle_path.write_text(yaml.safe_dump(data))
    assert plan_modelica_stack(vehicle_path, root=tmp_path).initialization_error
    with pytest.raises(ValueError, match='Recalibrate'):
        generate_modelica_stack(vehicle_path, root=tmp_path)
    assert before == {path: path.read_bytes() for path in before}
    data['modelica_initialization'] = 'legacy'
    vehicle_path.write_text(yaml.safe_dump(data))
    generate_modelica_stack(vehicle_path, root=tmp_path)
    assert 'pQSSInitialization' not in record.read_text()


def test_current_pinned_calibration_cannot_be_silently_transplanted():
    from app.modelica_generator import plan_modelica_stack
    root = Path(__file__).resolve().parents[1]
    plan = plan_modelica_stack(root / 'vehicle.yml', root=root)
    # The current YAML aero and VCU inputs differ from the solved BobLib car.
    assert plan.initialization_error is not None


# BobSim's vehicle.yml used this path before the #82 layout move.
STALE_LAYOUT_BOBLIB = "_0_Utils/external/BobLib/BobLib"


def test_stale_boblib_root_fails_before_writing(tmp_path: Path) -> None:
    repo_root = Path(__file__).resolve().parents[1]
    vehicle_path = _write_temp_vehicle(repo_root, tmp_path, boblib=STALE_LAYOUT_BOBLIB)
    before = _tree(tmp_path)

    with pytest.raises(BobLibRootError, match="paths.boblib") as excinfo:
        generate_modelica_stack(vehicle_path, root=tmp_path)

    message = str(excinfo.value)
    assert str(tmp_path / STALE_LAYOUT_BOBLIB) in message
    assert str(tmp_path / BUILD_BOBLIB) in message
    assert "No Modelica files were written." in message
    assert _tree(tmp_path) == before
    assert not (tmp_path / "_0_Utils").exists()


def test_valid_boblib_tree_at_a_stale_path_fails_before_writing(tmp_path: Path) -> None:
    # An in-place submodule update from the old layout can leave the old tree on disk.
    repo_root = Path(__file__).resolve().parents[1]
    vehicle_path = _write_temp_vehicle(repo_root, tmp_path, boblib=STALE_LAYOUT_BOBLIB)
    _write_boblib_package(tmp_path / STALE_LAYOUT_BOBLIB)
    before = _tree(tmp_path)

    with pytest.raises(BobLibRootError, match="the Modelica builds load") as excinfo:
        generate_modelica_stack(vehicle_path, root=tmp_path)

    assert str(tmp_path / BUILD_BOBLIB) in str(excinfo.value)
    assert _tree(tmp_path) == before


def test_stale_boblib_root_fails_the_status_check(tmp_path: Path) -> None:
    repo_root = Path(__file__).resolve().parents[1]
    vehicle_path = _write_temp_vehicle(repo_root, tmp_path, boblib=STALE_LAYOUT_BOBLIB)
    _write_boblib_package(tmp_path / STALE_LAYOUT_BOBLIB)

    with pytest.raises(BobLibRootError, match="the Modelica builds load"):
        modelica_stack_status_payload(vehicle_path, tmp_path)


def test_cli_write_with_stale_boblib_root_fails_and_writes_nothing(tmp_path: Path, capsys) -> None:
    from app import modelica_generator

    repo_root = Path(__file__).resolve().parents[1]
    vehicle_path = _write_temp_vehicle(repo_root, tmp_path, boblib=STALE_LAYOUT_BOBLIB)
    _write_boblib_package(tmp_path / STALE_LAYOUT_BOBLIB)
    before = _tree(tmp_path)

    assert modelica_generator.main([str(vehicle_path), "--root", str(tmp_path), "--write"]) == 2
    captured = capsys.readouterr()
    assert "paths.boblib" in captured.err
    assert str(tmp_path / STALE_LAYOUT_BOBLIB) in captured.err
    assert "Wrote" not in captured.out
    assert _tree(tmp_path) == before


def test_boblib_root_must_be_the_top_level_package(tmp_path: Path) -> None:
    repo_root = Path(__file__).resolve().parents[1]
    vehicle_path = _write_temp_vehicle(repo_root, tmp_path, boblib=f"{BUILD_BOBLIB}/Records")
    (tmp_path / BUILD_BOBLIB / "Records").mkdir()
    (tmp_path / BUILD_BOBLIB / "Records/package.mo").write_text(
        "within BobLib;\npackage Records\nend Records;\n", encoding="utf-8"
    )
    before = _tree(tmp_path)

    with pytest.raises(BobLibRootError, match="the Modelica builds load"):
        generate_modelica_stack(vehicle_path, root=tmp_path)
    assert _tree(tmp_path) == before


def test_uninitialized_boblib_submodule_fails_before_writing(tmp_path: Path) -> None:
    repo_root = Path(__file__).resolve().parents[1]
    vehicle_path = _write_temp_vehicle(repo_root, tmp_path)
    (tmp_path / BUILD_BOBLIB / "package.mo").unlink()
    before = _tree(tmp_path)

    with pytest.raises(BobLibRootError, match="package.mo does not exist"):
        generate_modelica_stack(vehicle_path, root=tmp_path)
    assert _tree(tmp_path) == before


def test_build_scripts_load_the_package_the_generator_writes() -> None:
    from app.modelica_generator import BUILD_BOBLIB_DIR

    repo_root = Path(__file__).resolve().parents[1]
    assert BUILD_BOBLIB_DIR == BUILD_BOBLIB
    for script in ("build_vehicle_sim.mos", "build_four_post_sim.mos"):
        text = (repo_root / "simulations/response/mbd" / script).read_text(encoding="utf-8")
        assert f'boblibDir := root + "/{BUILD_BOBLIB_DIR}";' in text, script


def test_generator_refuses_to_write_outside_the_boblib_root(tmp_path: Path) -> None:
    repo_root = Path(__file__).resolve().parents[1]
    vehicle_path = _write_temp_vehicle(repo_root, tmp_path)
    outside = tmp_path / "outside"
    outside.mkdir()
    (tmp_path / BUILD_BOBLIB / "Records").symlink_to(outside, target_is_directory=True)

    with pytest.raises(BobLibRootError, match="outside the BobLib package root"):
        generate_modelica_stack(vehicle_path, root=tmp_path)
    assert list(outside.iterdir()) == []
    assert not (tmp_path / BUILD_BOBLIB / "Experiments").exists()


def _vehicle_template_text(plan) -> str:
    return dict(plan.contents)[plan.result.files[1].path]


def _bound_front_brake_bias(template_text: str) -> float:
    import re

    # The binding must sit at the top level of the BaseVehicleSim extends clause, beside the chassis.
    match = re.search(
        r"^(?P<indent> +)redeclare BobLib\.Chassis\.Chassis_DW chassis\(\n.*?^(?P=indent)\),\n"
        r"(?P=indent)brakes\(\n +frontBrakeBias = (?P<value>[^\s)]+)\n(?P=indent)\)\n  \);\n",
        template_text,
        re.MULTILINE | re.DOTALL,
    )
    assert match, template_text
    return float(match["value"])


def _set_brake(vehicle_path: Path, brake) -> None:
    data = load_yaml(vehicle_path)
    if brake is None:
        data.pop("brake", None)
    else:
        data["brake"] = brake
    vehicle_path.write_text(yaml.safe_dump(data, sort_keys=False), encoding="utf-8")


def test_vehicle_template_binds_front_brake_bias_from_the_vehicle_file(tmp_path: Path) -> None:
    repo_root = Path(__file__).resolve().parents[1]
    vehicle_path = _write_temp_vehicle(repo_root, tmp_path, brake=True)
    expected = load_yaml(vehicle_path)["brake"]["front_bias"]

    result = generate_modelica_stack(vehicle_path, root=tmp_path)

    template_text = result.files[1].path.read_text(encoding="utf-8")
    assert _bound_front_brake_bias(template_text) == expected
    four_post_text = result.files[2].path.read_text(encoding="utf-8")
    assert "frontBrakeBias" not in four_post_text
    status = modelica_stack_status_payload(vehicle_path, tmp_path)
    assert status["front_brake_bias"] == {"value": expected, "source": "brake.front_bias", "note": None}


def test_vehicle_template_follows_a_changed_front_brake_bias(tmp_path: Path) -> None:
    from app.modelica_generator import plan_modelica_stack

    repo_root = Path(__file__).resolve().parents[1]
    vehicle_path = _write_temp_vehicle(repo_root, tmp_path, brake=True)
    before = modelica_stack_status_payload(vehicle_path, tmp_path)["signatures"]
    data = load_yaml(vehicle_path)
    data["brake"]["front_bias"] = 0.62
    vehicle_path.write_text(yaml.safe_dump(data, sort_keys=False), encoding="utf-8")

    plan = plan_modelica_stack(vehicle_path, root=tmp_path)
    after = modelica_stack_status_payload(vehicle_path, tmp_path)["signatures"]

    assert _bound_front_brake_bias(_vehicle_template_text(plan)) == 0.62
    assert after["vehicle"]["generated"] != before["vehicle"]["generated"]
    assert after["four_post"]["generated"] == before["four_post"]["generated"]


def test_default_vehicle_yaml_plans_the_front_brake_bias_binding() -> None:
    from app.modelica_generator import plan_modelica_stack

    root = Path(__file__).resolve().parents[1]
    plan = plan_modelica_stack(root / "vehicle.yml", root=root)

    expected = load_yaml(root / "vehicle.yml")["brake"]["front_bias"]
    assert _bound_front_brake_bias(_vehicle_template_text(plan)) == expected


@pytest.mark.parametrize("brake", [None, {}, {"front_bias": None}])
def test_missing_front_brake_bias_binds_nothing_and_says_so(tmp_path: Path, capsys, brake) -> None:
    from app import modelica_generator

    repo_root = Path(__file__).resolve().parents[1]
    vehicle_path = _write_temp_vehicle(repo_root, tmp_path, brake=True)
    _set_brake(vehicle_path, brake)

    result = generate_modelica_stack(vehicle_path, root=tmp_path)

    template_text = result.files[1].path.read_text(encoding="utf-8")
    assert "frontBrakeBias" not in template_text
    assert "brakes(" not in template_text
    status = modelica_stack_status_payload(vehicle_path, tmp_path)
    assert status["state"] == "written"
    assert status["front_brake_bias"]["value"] is None
    assert status["front_brake_bias"]["source"] == "boblib_default"
    assert "brake.front_bias is not set" in status["front_brake_bias"]["note"]
    assert modelica_generator.main([str(vehicle_path), "--root", str(tmp_path)]) == 0
    assert "brake.front_bias is not set" in capsys.readouterr().out


SHIPPED_TEMPLATES = sorted(
    path.name for path in (Path(__file__).resolve().parents[1] / "common/vehicle_templates").glob("*.yml")
)


@pytest.mark.parametrize("template", SHIPPED_TEMPLATES)
def test_shipped_vehicle_templates_plan_without_a_brake_section(template: str) -> None:
    root = Path(__file__).resolve().parents[1]
    template_path = root / "common/vehicle_templates" / template
    assert "brake" not in load_yaml(template_path)

    status = modelica_stack_status_payload(template_path, root)

    assert status["front_brake_bias"]["value"] is None
    assert "brake.front_bias is not set" in status["front_brake_bias"]["note"]


@pytest.mark.parametrize("value", [-0.01, 1.01, float("nan"), float("inf")])
def test_out_of_range_front_brake_bias_fails_before_writing(tmp_path: Path, value: float) -> None:
    repo_root = Path(__file__).resolve().parents[1]
    vehicle_path = _write_temp_vehicle(repo_root, tmp_path, brake=True)
    data = load_yaml(vehicle_path)
    data["brake"]["front_bias"] = value
    vehicle_path.write_text(yaml.safe_dump(data, sort_keys=False), encoding="utf-8")
    before = _tree(tmp_path)

    with pytest.raises(ValueError, match="brake.front_bias must be between 0 and 1"):
        generate_modelica_stack(vehicle_path, root=tmp_path)
    assert _tree(tmp_path) == before


@pytest.mark.parametrize("brake", [{"front_bias": "0.84 front"}, {"front_bias": True}, "0.84"])
def test_malformed_front_brake_bias_fails_before_writing(tmp_path: Path, brake) -> None:
    repo_root = Path(__file__).resolve().parents[1]
    vehicle_path = _write_temp_vehicle(repo_root, tmp_path)
    _set_brake(vehicle_path, brake)
    before = _tree(tmp_path)

    with pytest.raises(TypeError, match="brake"):
        generate_modelica_stack(vehicle_path, root=tmp_path)
    assert _tree(tmp_path) == before
