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
    assert f"redeclare record FrontAxleRecord = {front_arch.record_type}," in record_text
    assert f"redeclare record RearAxleRecord = {rear_arch.record_type});" in record_text
    assert "parameter ChassisRecord chassis(" in record_text
    assert "parameter Controllers.VCURecord controller(" in record_text
    assert "finalDriveRatio = transmission.gearRatio*driveline.inputRatio" in record_text
    assert f"tau_max = {vehicle_data['powertrain']['pVCU']['tau_max']}" in record_text
    assert f"P_max_mot = {vehicle_data['powertrain']['pVCU']['P_max_mot']}" in record_text
    assert "parameter ElectricDrives.MotorRecord motor(" in record_text
    assert f"P_mech_peak = {vehicle_data['powertrain']['pMotor']['P_mech_peak']}" in record_text
    assert f"gearRatio = {vehicle_data['powertrain']['pDriveline']['finalDriveRatio']}" in record_text
    assert "torsionalStiffness = 500000" in record_text
    assert "FNOMIN = 650" in record_text
    assert "UNLOADED_RADIUS = chassis.frontAxle.tire.wheel.geometry.R0" in record_text
    assert "pQSSInitialization" not in record_text

    vehicle_template_text = (
        tmp_path
        / BUILD_BOBLIB
        / "Experiments/Standards/BobSimTemplates/VehicleSim_EVBatInvMotDiff_DWBCStabar_DWBCStabar.mo"
    ).read_text(encoding="utf-8")
    record_redeclare = (
        "redeclare record VehicleRecord = "
        "BobLib.Records.VehicleDefn.EVBatInvMotDiff_DWBCStabar_DWBCStabarRecord"
    )
    assert record_redeclare in vehicle_template_text
    assert f"redeclare model FrAxleModel = {front_arch.model}" in vehicle_template_text
    assert f"redeclare model RrAxleModel = {rear_arch.model}" in vehicle_template_text
    assert "extends BobLib.Experiments.Standards.BaseClasses.PartialVehicleSim(" in vehicle_template_text
    assert "pChassis = pVehicle.chassis" in vehicle_template_text
    assert "frontBrakePlacement = BobLib.Brakes.Types.Placement.Outboard" in vehicle_template_text
    assert "rearBrakePlacement = BobLib.Brakes.Types.Placement.Inboard" in vehicle_template_text
    lsd = "differentialArchitecture = BobLib.Drivelines.Types.DifferentialArchitecture.ClutchLSD"
    assert lsd in vehicle_template_text
    assert "Stabar(" not in vehicle_template_text

    four_post_template_text = (
        tmp_path
        / BUILD_BOBLIB
        / "Experiments/Standards/BobSimTemplates/FourPostSim_EVBatInvMotDiff_DWBCStabar_DWBCStabar.mo"
    ).read_text(encoding="utf-8")
    assert "extends BobLib.Experiments.Standards.BaseClasses.PartialDoubleWishboneFourPost(" in four_post_template_text
    assert ("frAxleDW(" in four_post_template_text) is front_arch.has_stabar
    assert ("rrAxleDW(" in four_post_template_text) is rear_arch.has_stabar
    assert ("leftArmEnd = pVehicle.chassis.frontAxle.stabilizer.leftArmEnd" in four_post_template_text) is (
        front_arch.has_stabar
    )
    assert ("barRate = 0" in four_post_template_text) is (front_arch.has_stabar or rear_arch.has_stabar)

    vehicle_entry_text = (tmp_path / BUILD_BOBLIB / "Experiments/Standards/VehicleSim.mo").read_text(encoding="utf-8")
    assert "extends BobSimTemplates.VehicleSim_EVBatInvMotDiff_DWBCStabar_DWBCStabar;" in vehicle_entry_text
    four_post_entry_text = (tmp_path / BUILD_BOBLIB / "Experiments/Standards/FourPostSim.mo").read_text(
        encoding="utf-8"
    )
    assert "extends BobSimTemplates.FourPostSim_EVBatInvMotDiff_DWBCStabar_DWBCStabar;" in four_post_entry_text
    package_text = (tmp_path / BUILD_BOBLIB / "Experiments/Standards/BobSimTemplates/package.mo").read_text(
        encoding="utf-8"
    )
    assert "package BobSimTemplates" in package_text


def test_modelica_generator_updates_package_order_without_duplicates(tmp_path: Path) -> None:
    repo_root = Path(__file__).resolve().parents[1]
    vehicle_path = _write_temp_vehicle(repo_root, tmp_path)

    first = generate_modelica_stack(vehicle_path, root=tmp_path)
    second = generate_modelica_stack(vehicle_path, root=tmp_path)

    assert second.record_name == first.record_name
    assert (
        tmp_path / BUILD_BOBLIB / "Records/VehicleDefn/package.order"
    ).read_text(encoding="utf-8").splitlines().count(first.record_name) == 1
    templates = (tmp_path / BUILD_BOBLIB / "Experiments/Standards/BobSimTemplates/package.order").read_text(
        encoding="utf-8"
    ).splitlines()
    assert templates == [first.vehicle_template_name, first.four_post_template_name]
    standards = (tmp_path / BUILD_BOBLIB / "Experiments/Standards/package.order").read_text(encoding="utf-8")
    assert standards.splitlines().count("BobSimTemplates") == 1


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
    record, entry_path = result.files[0].path, result.files[3].path
    # BobLib keeps the solved pose on VehicleSim. Give the generated entry one, as a recalibration would.
    pinned = root / 'engines/boblib/BobLib/Experiments/Standards/VehicleSim.mo'
    calibration = _record_parameters(pinned.read_text())["pInitialization"]
    entry_path.write_text(entry_path.read_text().replace('  annotation(', calibration + '\n  annotation(', 1))
    generate_modelica_stack(vehicle_path, root=tmp_path)
    entry = entry_path.read_text()
    assert calibration in entry
    assert 'fixInitialSuspensionAngles = true' in entry
    assert 'initialRearRightLowerArmAngle = pInitialization.rearRightLowerArmAngle' in entry
    assert 'abs(initialVel - pInitialization.referenceVelocity)' in entry
    assert 'pInitialization' not in record.read_text()
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
    assert 'pInitialization' not in entry_path.read_text()


def test_pose_solved_for_another_record_blocks_generation(tmp_path):
    import pytest
    from app.modelica_generator import plan_modelica_stack
    root = Path(__file__).resolve().parents[1]
    vehicle_path = _write_temp_vehicle(root, tmp_path)
    data = load_yaml(vehicle_path)
    data['vehicle']['name'] = 'OtherCar'
    vehicle_path.write_text(yaml.safe_dump(data))
    entry = tmp_path / BUILD_BOBLIB / 'Experiments/Standards/VehicleSim.mo'
    entry.parent.mkdir(parents=True)
    # BobLib's own entry point carries a pose for its default record.
    shutil.copy(root / 'engines/boblib/BobLib/Experiments/Standards/VehicleSim.mo', entry)

    error = plan_modelica_stack(vehicle_path, root=tmp_path).initialization_error
    assert error and 'EVBatInvMotDiff_DWBCStabar_DWBCStabarRecord' in error and 'OtherCarRecord' in error
    with pytest.raises(ValueError, match='Recalibrate'):
        generate_modelica_stack(vehicle_path, root=tmp_path)


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

    # The binding must sit at the top level of the PartialVehicleSim extends clause, beside the chassis.
    match = re.search(
        r"^(?P<indent> +)redeclare BobLib\.Chassis\.DoubleWishbone chassis\(\n.*?^(?P=indent)\),\n"
        r".*?^(?P=indent)pVehicle\(\n +brakes\(\n +frontBrakeBias = (?P<value>[^\s)]+)\n +\)\n"
        r"(?P=indent)\)\n  \);\n",
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


UNBOUND_DRIVELINE_FIELDS = [
    "diff_T_capacity_max",
    "diff_clutchEffectiveRadius",
    "diff_w_transition",
    "diff_c_viscous",
    "halfshaftLeftJEquivalent",
    "halfshaftRightJEquivalent",
]


def test_driveline_fields_map_to_the_boblib_records_or_are_reported_unbound(tmp_path: Path, capsys) -> None:
    from app import modelica_generator
    from app.modelica_generator import _record_parameters

    repo_root = Path(__file__).resolve().parents[1]
    vehicle_path = _write_temp_vehicle(repo_root, tmp_path)
    driveline = load_yaml(vehicle_path)["powertrain"]["pDriveline"]

    result = generate_modelica_stack(vehicle_path, root=tmp_path)
    record_text = result.files[0].path.read_text(encoding="utf-8")
    for line in (
        f"inputInertia = {driveline['diffInputRotorJ']}",
        f"preloadTorque = {driveline['diff_T_preload']}",
        f"driveLockingFraction = {driveline['diff_lockFractionAccel']}",
        f"coastLockingFraction = {driveline['diff_lockFractionDecel']}",
        f"slidingFrictionRatio = {driveline['diff_kineticFrictionRatio']}",
        f"stiffness = {driveline['halfshaftLeftC']}",
        f"damping = {driveline['halfshaftLeftD']:.15g}",
        "differentialBrakeRatio = driveline.inputRatio",
        "maxTorque = controller.mechanicalBrakeTorqueLimit",
    ):
        assert line in record_text, line
    driveline_text = _record_parameters(record_text)["driveline"]
    for name in ("inertia =", "T_capacity", "clutchEffectiveRadius", "w_transition", "c_viscous"):
        assert name not in driveline_text, name
    assert "pDriveline" not in record_text

    status = modelica_stack_status_payload(vehicle_path, tmp_path)
    assert [item["path"] for item in status["unbound_inputs"]] == [
        f"powertrain.pDriveline.{name}" for name in UNBOUND_DRIVELINE_FIELDS
    ]
    assert status["brake_placement"] == {
        "front": "Outboard",
        "rear": "Inboard",
        "source": "boblib_default",
        "note": modelica_generator.BRAKE_PLACEMENT_NOTE,
    }
    assert modelica_generator.main([str(vehicle_path), "--root", str(tmp_path)]) == 0
    out = capsys.readouterr().out
    for name in UNBOUND_DRIVELINE_FIELDS:
        assert f"unbound:  powertrain.pDriveline.{name}." in out
    assert "no brake placement input" in out


def test_open_differential_is_selected_when_the_lsd_is_off(tmp_path: Path) -> None:
    from app.modelica_generator import plan_modelica_stack

    repo_root = Path(__file__).resolve().parents[1]
    vehicle_path = _write_temp_vehicle(repo_root, tmp_path)
    data = load_yaml(vehicle_path)
    data["powertrain"]["pDriveline"]["diff_use_lsd"] = False
    vehicle_path.write_text(yaml.safe_dump(data, sort_keys=False), encoding="utf-8")

    template_text = _vehicle_template_text(plan_modelica_stack(vehicle_path, root=tmp_path))
    assert "differentialArchitecture = BobLib.Drivelines.Types.DifferentialArchitecture.Open" in template_text


@pytest.mark.parametrize(
    ("field", "value", "message"),
    [
        ("halfshaftRightC", 16000, "different left and right values"),
        ("halfshaftRightD", 30.0, "different left and right values"),
        ("diff_bias_ratio", 3.0, "no BobLib mapping: diff_bias_ratio"),
    ],
)
def test_driveline_inputs_without_a_safe_mapping_fail_before_writing(
    tmp_path: Path, field: str, value: float, message: str
) -> None:
    repo_root = Path(__file__).resolve().parents[1]
    vehicle_path = _write_temp_vehicle(repo_root, tmp_path)
    data = load_yaml(vehicle_path)
    data["powertrain"]["pDriveline"][field] = value
    vehicle_path.write_text(yaml.safe_dump(data, sort_keys=False), encoding="utf-8")
    before = _tree(tmp_path)

    with pytest.raises(ValueError, match=message):
        generate_modelica_stack(vehicle_path, root=tmp_path)
    assert _tree(tmp_path) == before


def test_controller_final_drive_ratio_comes_from_the_transmission(tmp_path: Path) -> None:
    repo_root = Path(__file__).resolve().parents[1]
    vehicle_path = _write_temp_vehicle(repo_root, tmp_path)
    data = load_yaml(vehicle_path)
    data["powertrain"]["pVCU"]["finalDriveRatio"] = 3.0
    vehicle_path.write_text(yaml.safe_dump(data, sort_keys=False), encoding="utf-8")

    with pytest.raises(ValueError, match="pVCU.finalDriveRatio cannot be set"):
        generate_modelica_stack(vehicle_path, root=tmp_path)
