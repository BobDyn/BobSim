from __future__ import annotations

from pathlib import Path

import pytest
import yaml

from _5_App import app


def test_app_status_exposes_bobsim_workflows_and_boblib_state() -> None:
    payload = app.status_payload()

    repo = payload["repo"]
    assert repo["boblib_package"]["path"] == "_0_Utils/external/BobLib/BobLib/package.mo"
    assert repo["vehicle_exe"]["path"].startswith("_3_StandardSim/BuildBobLib/VehicleSim/")
    assert repo["four_post_exe"]["path"].startswith("_3_StandardSim/BuildBobLib/FourPostSim/")

    workflow_ids = {workflow["id"] for workflow in payload["workflows"]}
    config_ids = {config["id"] for config in payload["configs"]}
    assert {
        "ramp-steer",
        "steady-state",
        "transient",
        "four-post",
        "ggv",
        "ymd",
        "vehicle-review",
        "standard-sens",
        "envelope-sens",
    } <= workflow_ids
    assert {"vehicle", "ramp-steer", "four-post", "visual-fr-knc-visual"} <= config_ids


def test_app_workflow_actions_are_allowlisted() -> None:
    workflow_action_ids = {action_id for workflow in app.WORKFLOWS for action_id in workflow.actions}

    assert workflow_action_ids <= set(app.ACTION_SPECS)
    for action in app.ACTION_SPECS.values():
        assert action.argv
        assert not Path(action.argv[0]).is_absolute() or action.argv[0] == app.PYTHON


def test_app_can_read_repo_configs() -> None:
    payload = app.read_text_payload("_3_StandardSim/RampSteerEval/ramp_steer_eval_config.yml")

    assert payload["path"] == "_3_StandardSim/RampSteerEval/ramp_steer_eval_config.yml"
    assert "BobLib.Experiments.Standards.VehicleSim" in payload["text"]


def test_app_rejects_paths_outside_repo() -> None:
    with pytest.raises(ValueError):
        app._safe_repo_path("../outside-bobsim")


def test_app_exposes_visual_templates_as_configurable_setups() -> None:
    payload = app.config_payload("visual-fr-knc-visual")

    field_paths = {tuple(field["path"]) for field in payload["fields"]}
    assert payload["group"] == "visualization"
    assert tuple(["render", "speed"]) in field_paths
    assert tuple(["camera", "attach_to"]) in field_paths
    assert tuple(["style", "joints", "radius"]) in field_paths


def test_app_lists_vehicle_templates_for_architecture_setup() -> None:
    payload = app.vehicle_template_payloads()

    template_ids = {template["id"] for template in payload["templates"]}
    assert "DWBCStabar_DWBCStabarRecord" in template_ids
    assert any(template["front"] == "direct" and template["rear"] == "direct" for template in payload["templates"])
    assert payload["powertrains"][0]["id"] == "EVBatInvMotDiff"
    assert all(template["powertrain"] == "EVBatInvMotDiff" for template in payload["templates"])


def test_app_vehicle_setup_exposes_vehicle_parameters_without_repo_paths() -> None:
    payload = app.config_payload("vehicle")

    field_paths = {tuple(field["path"]) for field in payload["fields"]}
    fields_by_path = {tuple(field["path"]): field for field in payload["fields"]}
    assert ("front", "suspension", "upper_fore_i_m") in field_paths
    assert ("aero", "drag_table_n") in field_paths
    assert ("paths", "boblib") not in field_paths
    assert ("schema",) not in field_paths
    assert fields_by_path[("sprung_mass", "cg_m")]["array_shape"] == [3]
    assert fields_by_path[("sprung_mass", "cg_m")]["array_element_kind"] == "number"
    assert fields_by_path[("aero", "drag_table_n")]["array_shape"] == [5, 5]
    assert fields_by_path[("front", "actuation", "bellcrank", "order")]["choices"] == ["rod", "shock", "stabar"]
    assert fields_by_path[("front", "actuation", "shock", "spring_table", "table")]["label"] == "Spring force curve"
    assert fields_by_path[("front", "actuation", "shock", "damper_table", "table")]["label"] == "Damper force curve"


def test_app_evaluates_active_tire_template_for_ui_curves() -> None:
    payload = app.tire_eval_payload()

    assert payload["model"].startswith("BobLib MF52")
    assert {side["side"] for side in payload["sides"]} == {"front", "rear"}
    front = next(side for side in payload["sides"] if side["side"] == "front")
    assert front["template"] == "16x7p5_10_12psi"
    assert front["metadata"]["fznom_n"] > 0
    assert len(front["curves"]["longitudinal"]) == 61
    assert len(front["curves"]["lateral"]) == 61
    assert len(front["curves"]["combined"]["fx_by_alpha"]) == 3
    assert len(front["curves"]["combined"]["fy_by_kappa"]) == 3
    assert len(front["curves"]["combined"]["fx_by_alpha"][0]["points"]) == 61
    assert len(front["curves"]["combined"]["fy_by_kappa"][0]["points"]) == 61
    assert len(front["curves"]["pure"]["longitudinal_by_fz"]) >= 5
    assert len(front["curves"]["pure"]["lateral_by_fz"]) >= 5
    assert len(front["curves"]["pure"]["longitudinal_by_fz"][0]["points"]) == 61
    assert len(front["curves"]["pure"]["lateral_by_fz"][0]["points"]) == 61
    assert {"kappa", "fz_n", "fx_n"} <= set(front["curves"]["pure"]["longitudinal_by_fz"][0]["points"][0])
    assert {"alpha_deg", "fz_n", "fy_n"} <= set(front["curves"]["pure"]["lateral_by_fz"][0]["points"][0])
    assert len(front["curves"]["combined"]["fx_surface"]["rows"]) == 31
    assert len(front["curves"]["combined"]["fy_surface"]["rows"]) == 31
    assert len(front["curves"]["combined"]["fx_surface"]["rows"][0]["points"]) == 31
    assert len(front["curves"]["combined"]["fy_surface"]["rows"][0]["points"]) == 31
    assert {"alpha_deg", "kappa", "fx_n"} <= set(front["curves"]["combined"]["fx_surface"]["rows"][0]["points"][0])
    assert {"alpha_deg", "kappa", "fy_n"} <= set(front["curves"]["combined"]["fy_surface"]["rows"][0]["points"][0])
    assert any(abs(point["fx_n"]) > 1 for point in front["curves"]["longitudinal"])
    assert any(abs(point["fy_n"]) > 1 for point in front["curves"]["lateral"])


def test_app_generates_live_kinematic_curves_for_active_vehicle() -> None:
    payload = app.kinematic_curves_from_active_vehicle()

    assert payload["model"].startswith("BobSim native")
    if not payload["available"]:
        pytest.skip(payload["warnings"][0])
    assert payload["axles"]["front"]["ok"] is True
    assert payload["axles"]["rear"]["ok"] is True
    assert len(payload["sweep_m"]) == 20
    assert len(payload["roll_deg"]) == 20
    assert len(payload["axles"]["front"]["curves"]["bump_camber_deg"]) == 20
    assert len(payload["axles"]["rear"]["curves"]["bump_toe_deg"]) == 20
    assert len(payload["axles"]["front"]["curves"]["roll_camber_deg"]) == 20
    assert payload["warnings"] == []


def test_app_lists_reads_and_saves_tire_templates(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
    (tmp_path / "vehicle.yml").write_text(
        "schema: boblib.vehicle.v1\n"
        "vehicle:\n"
        "  name: TireDemo\n"
        "paths:\n"
        "  tire_templates: tires\n",
        encoding="utf-8",
    )
    tire_root = tmp_path / "tires"
    tire_root.mkdir()
    source = Path("_0_Utils/tire_templates/16x7p5_10_12psi.tir")
    tire_text = source.read_text(encoding="utf-8")
    (tire_root / "base.tir").write_text(tire_text, encoding="utf-8")
    monkeypatch.setattr(app, "ROOT", tmp_path)

    library = app.tire_template_library_payload()
    assert library["templates"][0]["id"] == "base"

    loaded = app.read_tire_template("base")
    assert loaded["metadata"]["fznom_n"] > 0

    saved = app.save_tire_template("Imported Tire.tir", tire_text)
    assert saved["id"] == "Imported_Tire"
    assert (tire_root / "Imported_Tire.tir").is_file()


def test_app_can_save_and_load_named_vehicle_configs(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
    active = tmp_path / "vehicle.yml"
    active.write_text(
        "schema: boblib.vehicle.v1\n"
        "vehicle:\n"
        "  name: ActiveVehicle\n"
        "architecture:\n"
        "  front: direct\n"
        "  rear: direct\n",
        encoding="utf-8",
    )
    template_root = tmp_path / "_0_Utils/vehicle_templates"
    template_root.mkdir(parents=True)
    (template_root / "TemplateVehicle.yml").write_text(
        "schema: boblib.vehicle.v1\n"
        "vehicle:\n"
        "  name: TemplateVehicle\n"
        "architecture:\n"
        "  front: bellcrank\n"
        "  rear: bellcrank_stabar\n",
        encoding="utf-8",
    )
    monkeypatch.setattr(app, "ROOT", tmp_path)
    monkeypatch.setattr(
        app,
        "BASE_CONFIG_SPECS",
        {"vehicle": app.ConfigSpec(id="vehicle", group="setup", label="Active Vehicle", path="vehicle.yml")},
    )

    library = app.save_active_vehicle("My Saved Vehicle")
    saved = library["saved"]
    assert saved["id"] == "saved:my-saved-vehicle"
    assert any(vehicle["id"] == saved["id"] for vehicle in library["vehicles"])

    app.load_vehicle_source("template:TemplateVehicle")
    assert yaml.safe_load(active.read_text(encoding="utf-8"))["vehicle"]["name"] == "TemplateVehicle"

    app.load_vehicle_source("saved:my-saved-vehicle")
    assert yaml.safe_load(active.read_text(encoding="utf-8"))["vehicle"]["name"] == "ActiveVehicle"

    library = app.delete_saved_vehicle("saved:my-saved-vehicle")
    assert not (tmp_path / "_5_App/vehicle_configs/my-saved-vehicle.yml").exists()
    assert all(vehicle["id"] != "saved:my-saved-vehicle" for vehicle in library["vehicles"])
    with pytest.raises(ValueError):
        app.delete_saved_vehicle("template:TemplateVehicle")


def test_app_can_save_load_and_delete_sim_configs(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
    config_path = tmp_path / "ramp.yml"
    config_path.write_text(
        "simulation:\n"
        "  solver: dassl\n"
        "sweep:\n"
        "  testVels: [12.5, 15.0]\n",
        encoding="utf-8",
    )
    monkeypatch.setattr(app, "ROOT", tmp_path)
    monkeypatch.setattr(app, "SAVED_SIM_CONFIG_ROOT", Path("_5_App/sim_configs"))
    monkeypatch.setattr(
        app,
        "BASE_CONFIG_SPECS",
        {
            "ramp-steer": app.ConfigSpec(
                id="ramp-steer",
                group="standard",
                label="Ramp",
                path="ramp.yml",
                workflow_id="ramp-steer",
                fields=(app.FieldSpec(("simulation", "solver"), "Solver", kind="select", choices=("dassl", "ida")),),
            )
        },
    )

    library = app.sim_config_library_payload("ramp-steer")
    assert library["sources"][0]["id"] == "default:ramp-steer"

    app.patch_config("ramp-steer", {'["simulation","solver"]': "ida"})
    saved = app.save_active_sim_config("ramp-steer", "Fast Ramp")
    source_id = saved["saved"]["id"]
    assert source_id == "saved:ramp-steer:fast-ramp"

    app.patch_config("ramp-steer", {'["simulation","solver"]': "dassl"})
    loaded = app.load_sim_config_source(source_id)
    assert loaded["config"]["data"]["simulation"]["solver"] == "ida"

    app.load_sim_config_source("default:ramp-steer")
    assert yaml.safe_load(config_path.read_text(encoding="utf-8"))["simulation"]["solver"] == "dassl"

    library = app.delete_saved_sim_config(source_id)
    assert all(source["id"] != source_id for source in library["sources"])


def test_app_can_save_load_and_delete_study_configs(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
    config_path = tmp_path / "ggv.yml"
    config_path.write_text(
        "generation:\n"
        "  ay_max_g: 4.5\n"
        "  ay_points: 321\n",
        encoding="utf-8",
    )
    monkeypatch.setattr(app, "ROOT", tmp_path)
    monkeypatch.setattr(app, "SAVED_SIM_CONFIG_ROOT", Path("_5_App/sim_configs"))
    monkeypatch.setattr(
        app,
        "BASE_CONFIG_SPECS",
        {
            "ggv": app.ConfigSpec(
                id="ggv",
                group="envelope",
                label="GGV",
                path="ggv.yml",
                workflow_id="ggv",
                fields=(app.FieldSpec(("generation", "ay_max_g"), "Max lateral acceleration", kind="number"),),
            )
        },
    )

    library = app.sim_config_library_payload("ggv")
    assert library["sources"][0]["id"] == "default:ggv"

    app.patch_config("ggv", {'["generation","ay_max_g"]': 3.8})
    saved = app.save_active_sim_config("ggv", "Wet Skidpad")
    source_id = saved["saved"]["id"]
    assert source_id == "saved:ggv:wet-skidpad"

    app.patch_config("ggv", {'["generation","ay_max_g"]': 4.5})
    loaded = app.load_sim_config_source(source_id)
    assert loaded["config"]["data"]["generation"]["ay_max_g"] == 3.8

    app.load_sim_config_source("default:ggv")
    assert yaml.safe_load(config_path.read_text(encoding="utf-8"))["generation"]["ay_max_g"] == 4.5

    library = app.delete_saved_sim_config(source_id)
    assert all(source["id"] != source_id for source in library["sources"])


def test_app_patch_config_updates_registered_yaml(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
    config_path = tmp_path / "demo.yml"
    config_path.write_text(
        "simulation:\n"
        "  solver: dassl\n"
        "  stop_time: 5.0\n"
        "execution:\n"
        "  parallel: true\n"
        "sweep:\n"
        "  speeds: [10.0, 15.0]\n",
        encoding="utf-8",
    )
    monkeypatch.setattr(app, "ROOT", tmp_path)
    monkeypatch.setattr(
        app,
        "BASE_CONFIG_SPECS",
        {
            "demo": app.ConfigSpec(
                id="demo",
                group="standard",
                label="Demo",
                path="demo.yml",
                fields=(
                    app.FieldSpec(("simulation", "solver"), "Solver", kind="select", choices=("dassl", "ida")),
                    app.FieldSpec(("sweep", "speeds"), "Speeds", kind="list"),
                ),
            )
        },
    )

    payload = app.patch_config(
        "demo",
        {
            '["simulation","solver"]': "ida",
            "simulation.stop_time": 10.0,
            '["execution","parallel"]': False,
            '["sweep","speeds"]': [12.5, 17.5],
        },
    )

    saved = yaml.safe_load(config_path.read_text(encoding="utf-8"))
    assert saved["simulation"]["solver"] == "ida"
    assert saved["simulation"]["stop_time"] == 10.0
    assert saved["execution"]["parallel"] is False
    assert saved["sweep"]["speeds"] == [12.5, 17.5]
    assert any(field["label"] == "Solver" and field["kind"] == "select" for field in payload["fields"])


def test_app_raw_config_save_validates_yaml_root(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
    (tmp_path / "demo.yml").write_text("a: 1\n", encoding="utf-8")
    monkeypatch.setattr(app, "ROOT", tmp_path)
    monkeypatch.setattr(
        app,
        "BASE_CONFIG_SPECS",
        {"demo": app.ConfigSpec(id="demo", group="setup", label="Demo", path="demo.yml")},
    )

    with pytest.raises(TypeError):
        app.save_raw_config("demo", "scalar-only")
