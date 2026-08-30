from __future__ import annotations

from pathlib import Path
import shutil

import yaml

from _0_Utils.vehicle_io import load_yaml
from _5_App.modelica_generator import (
    ARCHITECTURES,
    generate_modelica_stack,
    modelica_generation_payload,
    modelica_stack_status_payload,
)


def _write_temp_vehicle(repo_root: Path, tmp_path: Path) -> Path:
    data = load_yaml(repo_root / "_0_Utils/vehicle_templates/DWBCStabar_DWBCStabarRecord.yml")
    active_data = load_yaml(repo_root / "vehicle.yml")
    if isinstance(active_data.get("powertrain"), dict):
        data["powertrain"] = active_data["powertrain"]
    data["paths"] = {"boblib": "BobLib", "tire_templates": "tires"}
    tire_name = data["aero"].get("tire_template") or data["front"]["tire"]["template"]
    tire_root = tmp_path / "tires"
    tire_root.mkdir()
    shutil.copy(repo_root / "_0_Utils/tire_templates" / f"{tire_name}.tir", tire_root / f"{tire_name}.tir")

    vehicle_path = tmp_path / "vehicle.yml"
    vehicle_path.write_text(yaml.safe_dump(data, sort_keys=False), encoding="utf-8")
    return vehicle_path


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
    assert payload["record"]["path"] == "BobLib/Records/VehicleDefn/EVBatInvMotDiff_DWBCStabar_DWBCStabarRecord.mo"
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
        / "BobLib/Experiments/Standards/Templates/Vehicle/VehicleSim_EVBatInvMotDiff_DWBCStabar_DWBCStabar.mo"
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
        / "BobLib/Experiments/Standards/Templates/FourPost/FourPostSim_EVBatInvMotDiff_DWBCStabar_DWBCStabar.mo"
    ).read_text(encoding="utf-8")
    assert "extends BaseFourPostSim(" in four_post_template_text
    assert ("frAxleDW(" in four_post_template_text) is front_arch.has_stabar
    assert ("rrAxleDW(" in four_post_template_text) is rear_arch.has_stabar
    assert ("barRate = 0" in four_post_template_text) is (front_arch.has_stabar or rear_arch.has_stabar)

    vehicle_entry_text = (tmp_path / "BobLib/Experiments/Standards/VehicleSim.mo").read_text(encoding="utf-8")
    assert "extends Templates.Vehicle.VehicleSim_EVBatInvMotDiff_DWBCStabar_DWBCStabar;" in vehicle_entry_text
    four_post_entry_text = (tmp_path / "BobLib/Experiments/Standards/FourPostSim.mo").read_text(encoding="utf-8")
    assert "extends Templates.FourPost.FourPostSim_EVBatInvMotDiff_DWBCStabar_DWBCStabar;" in four_post_entry_text


def test_modelica_generator_updates_package_order_without_duplicates(tmp_path: Path) -> None:
    repo_root = Path(__file__).resolve().parents[1]
    vehicle_path = _write_temp_vehicle(repo_root, tmp_path)

    first = generate_modelica_stack(vehicle_path, root=tmp_path)
    second = generate_modelica_stack(vehicle_path, root=tmp_path)

    assert second.record_name == first.record_name
    assert (
        tmp_path / "BobLib/Records/VehicleDefn/package.order"
    ).read_text(encoding="utf-8").splitlines().count(first.record_name) == 1
    assert (
        tmp_path / "BobLib/Experiments/Standards/Templates/Vehicle/package.order"
    ).read_text(encoding="utf-8").splitlines().count(first.vehicle_template_name) == 1
    assert (
        tmp_path / "BobLib/Experiments/Standards/Templates/FourPost/package.order"
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
    from _0_Utils.vehicle_io import load_yaml, vehicle_yaml_path
    from _5_App.modelica_generator import _pickup_order

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

    # The two axles disagree, which is the proof that the shared order list -
    # identical for both - cannot be the source.
    assert vehicle["front"]["actuation"]["bellcrank"]["order"] == \
        vehicle["rear"]["actuation"]["bellcrank"]["order"]
    assert expected["front"] != expected["rear"]
