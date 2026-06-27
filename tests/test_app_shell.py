from __future__ import annotations

import json
from pathlib import Path
import shutil

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
    front_architecture = payload["data"]["architecture"]["front"]
    front_order_choices = ["rod", "shock", "stabar"] if front_architecture == "bellcrank_stabar" else ["rod", "shock"]
    assert ("front", "suspension", "upper_fore_i_m") in field_paths
    assert ("aero", "drag_table_n") in field_paths
    assert ("paths", "boblib") not in field_paths
    assert ("schema",) not in field_paths
    assert fields_by_path[("sprung_mass", "cg_m")]["array_shape"] == [3]
    assert fields_by_path[("sprung_mass", "cg_m")]["array_element_kind"] == "number"
    assert fields_by_path[("aero", "drag_table_n")]["array_shape"] == [5, 5]
    assert fields_by_path[("front", "actuation", "bellcrank", "order")]["choices"] == front_order_choices
    assert fields_by_path[("front", "actuation", "shock", "spring_table", "table")]["label"] == "Spring force curve"
    assert fields_by_path[("front", "actuation", "shock", "damper_table", "table")]["label"] == "Damper force curve"
    assert payload["data"]["powertrain"]["implementation"] == "EVBatInvMotDiff"
    assert fields_by_path[("powertrain", "pBattery", "Ns")]["value"] == 140
    assert fields_by_path[("powertrain", "pMotor", "P_mech_peak")]["unit"] == "W"
    assert fields_by_path[("powertrain", "pDriveline", "diff_use_lsd")]["kind"] == "boolean"


def test_frontend_renders_aero_maps_as_interactive_3d_surfaces() -> None:
    app_js = (app.ROOT / "_5_App/static/app.js").read_text(encoding="utf-8")

    assert "function aeroSurfaceRowsFromTable" in app_js
    assert 'area.visual === "aero" || (area.visual === "tires"' in app_js
    assert "state.tireSurfaceScene = {" in app_js
    assert '"FRH m"' in app_js
    assert '"RRH m"' in app_js


def test_frontend_tire_setup_draws_corner_force_envelopes_and_alignment() -> None:
    app_js = (app.ROOT / "_5_App/static/app.js").read_text(encoding="utf-8")

    assert "function tireSetupCorners" in app_js
    assert "function drawTireCornerSetupCard" in app_js
    assert "function drawTireFrictionEllipse" in app_js
    assert "function tireSetupForceMap" in app_js
    assert "force_map_nominal" in app_js
    assert "force_maps_by_gamma" in app_js
    assert "function shiftTireForceMapAlpha" in app_js
    assert "function interpolateTireForceMapAtAlpha" in app_js
    assert "function drawTireForceMapIsolines" in app_js
    assert "function tireForceMapPointAt" in app_js
    assert "function drawTireAlphaOffsetVector" in app_js
    assert "function drawTireInclinationGlyph" in app_js
    assert 'return side === "right" ? -numeric : numeric;' in app_js
    assert "x: -Math.sin(alphaRad)" in app_js
    assert "Friction Ellipses" in app_js
    assert "Shared scale" in app_js
    assert "FzNom" in app_js
    assert "skipInvalid: true" in app_js
    assert "IA ${formatSignedNumber(corner.inclinationDeg)} deg  Fy" in app_js
    assert "function queueTirePayloadRefresh" in app_js
    assert 'await api("/api/tires/eval", {' in app_js
    assert "function isTireSetupFieldTarget" in app_js
    assert "function isTireAlignmentFieldTarget" in app_js
    assert "TIRE_LIVE_WHEEL_FIELDS.has(path[2])" in app_js
    assert "function drawTirePreviewError" in app_js
    assert "function isTirePayloadRefreshTarget" in app_js
    assert 'path[1] === "tire"' in app_js
    assert '["toe_deg", "camber_deg", "radius_m"].includes' not in app_js
    assert "tire-load-camber-slider" in app_js
    assert "function currentTireLoadCamberDeg" in app_js
    assert "function interpolateTireSurfaceRowsByGamma" in app_js
    assert "function tireCombinedForceMapRowsAtFzAndCamber" in app_js
    assert "force_maps_by_gamma_fz" in app_js
    assert "longitudinal_by_gamma" in app_js


def test_frontend_powertrain_subsystem_tabs_wrap_before_clipping() -> None:
    styles = (app.ROOT / "_5_App/static/styles.css").read_text(encoding="utf-8")

    assert ".powertrain-subsystem-tabs" in styles
    assert "flex-wrap: wrap;" in styles
    assert "overflow: hidden;" in styles
    assert "flex: 0 1 116px;" in styles
    assert "min-width: min(100%, 116px);" in styles
    assert ".powertrain-subsystem-tab span" in styles
    assert "text-overflow: ellipsis;" in styles
    assert ".powertrain-subsystem-panels" in styles
    assert "grid-template-rows: auto auto minmax(0, 1fr);" in styles
    assert ".workflow-guide {\n  position: static;" in styles


def test_app_can_patch_powertrain_defaults_into_vehicle(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
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
    monkeypatch.setattr(app, "ROOT", tmp_path)
    monkeypatch.setattr(
        app,
        "BASE_CONFIG_SPECS",
        {"vehicle": app.ConfigSpec(id="vehicle", group="setup", label="Active Vehicle", path="vehicle.yml")},
    )

    payload = app.patch_config(
        "vehicle",
        {
            json.dumps(["powertrain", "pMotor", "P_mech_peak"]): 95_000.0,
            json.dumps(["powertrain", "pVCU", "regenTorqueLimit"]): 180.0,
        },
    )

    saved = yaml.safe_load(active.read_text(encoding="utf-8"))
    assert saved["powertrain"]["implementation"] == "EVBatInvMotDiff"
    assert saved["powertrain"]["pBattery"]["Ns"] == 140
    assert saved["powertrain"]["pMotor"]["P_mech_peak"] == pytest.approx(95_000.0)
    assert saved["powertrain"]["pVCU"]["regenTorqueLimit"] == pytest.approx(180.0)
    assert payload["data"]["powertrain"]["pMotor"]["P_mech_peak"] == pytest.approx(95_000.0)


def test_app_can_generate_modelica_payload_from_active_vehicle(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
    data = yaml.safe_load((app.ROOT / "vehicle.yml").read_text(encoding="utf-8"))
    data["paths"] = {"boblib": "BobLib", "tire_templates": "tires"}
    tire_name = data["aero"].get("tire_template") or data["front"]["tire"]["template"]
    tire_root = tmp_path / "tires"
    tire_root.mkdir()
    shutil.copy(app.ROOT / "_0_Utils/tire_templates" / f"{tire_name}.tir", tire_root / f"{tire_name}.tir")
    (tmp_path / "vehicle.yml").write_text(yaml.safe_dump(data, sort_keys=False), encoding="utf-8")
    monkeypatch.setattr(app, "ROOT", tmp_path)

    payload = app.generate_modelica_payload()

    assert payload["record"]["name"] == "EVBatInvMotDiff_DWBCStabar_DWBCStabarRecord"
    assert payload["vehicle_template"] == "VehicleSim_EVBatInvMotDiff_DWBCStabar_DWBCStabar"
    assert payload["four_post_template"] == "FourPostSim_EVBatInvMotDiff_DWBCStabar_DWBCStabar"
    assert (tmp_path / payload["record"]["path"]).is_file()


def test_app_archives_and_restores_matching_modelica_builds(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    monkeypatch.setattr(app, "ROOT", tmp_path)
    (tmp_path / "vehicle.yml").write_text("vehicle:\n  name: CacheCar\n", encoding="utf-8")
    script_path = tmp_path / "_3_StandardSim/build_vehicle_sim.mos"
    script_path.parent.mkdir(parents=True)
    script_path.write_text("// fake build script\n", encoding="utf-8")
    stack = {
        "written_to_boblib": True,
        "latest_modified": 1.0,
        "signatures": {
            "vehicle": {
                "generated": "generated-vehicle-signature",
            }
        },
    }
    monkeypatch.setattr(app, "modelica_stack_status_payload", lambda _vehicle_path, _root: stack)

    target = app.MODELICA_BUILD_TARGETS["vehicle"]
    build_dir = tmp_path / target.build_dir
    calls = {"count": 0}

    def fake_build(action: app.ActionSpec, job_id: str) -> int:
        assert action.id == "build-vehicle"
        calls["count"] += 1
        build_dir.mkdir(parents=True, exist_ok=True)
        (build_dir / target.exec_name).write_text("exe", encoding="utf-8")
        (build_dir / f"{target.exec_name}_init.xml").write_text("<init />", encoding="utf-8")
        return 0

    monkeypatch.setattr(app, "_run_subprocess_action", fake_build)

    job = app.JOBS.create("build-vehicle", "Build VehicleSim", [])
    assert app._run_action_process(app.ACTION_SPECS["build-vehicle"], job["id"]) == 0
    assert calls["count"] == 1
    metadata = json.loads((build_dir / app.BUILD_METADATA_FILENAME).read_text(encoding="utf-8"))
    archive_dir = tmp_path / "_5_App/build_archive/modelica/vehicle" / metadata["signature"]
    assert (archive_dir / "files" / target.exec_name).is_file()
    assert (archive_dir / "files" / f"{target.exec_name}_init.xml").is_file()

    shutil.rmtree(build_dir)
    assert app._run_action_process(app.ACTION_SPECS["build-vehicle"], job["id"]) == 0
    assert calls["count"] == 1
    assert (build_dir / target.exec_name).read_text(encoding="utf-8") == "exe"
    restored = json.loads((build_dir / app.BUILD_METADATA_FILENAME).read_text(encoding="utf-8"))
    assert restored["signature"] == metadata["signature"]
    assert restored["source"] == "archive"


def test_app_evaluates_active_tire_template_for_ui_curves() -> None:
    payload = app.tire_eval_payload()

    assert payload["model"].startswith("BobLib MF52")
    assert {side["side"] for side in payload["sides"]} == {"front", "rear"}
    assert payload["load_summary"]["source"] == "total mass properties from vehicle.yml"
    assert payload["load_summary"]["total_mass_kg"] == pytest.approx(261.07265114)
    assert payload["load_summary"]["front_static_frac"] == pytest.approx(0.4834962889)
    front = next(side for side in payload["sides"] if side["side"] == "front")
    rear = next(side for side in payload["sides"] if side["side"] == "rear")
    assert front["template"] == "16x7p5_10_12psi"
    assert front["fz_n"] == pytest.approx(payload["load_summary"]["per_tire_loads_n"]["front"])
    assert rear["fz_n"] == pytest.approx(payload["load_summary"]["per_tire_loads_n"]["rear"])
    assert front["metadata"]["fznom_n"] > 0
    assert front["metadata"]["camber_thrust"]["enabled"] is False
    assert front["metadata"]["camber_thrust"]["pvy3"] == pytest.approx(0.0)
    assert front["metadata"]["camber_thrust"]["pdy3"] > 0
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
    assert len(front["curves"]["combined"]["fx_surfaces_by_fz"]) >= 5
    assert len(front["curves"]["combined"]["fy_surfaces_by_fz"]) >= 5
    assert len(front["curves"]["pure"]["longitudinal_by_gamma"]) >= 9
    assert len(front["curves"]["pure"]["lateral_by_gamma"]) >= 9
    assert {"gamma_deg", "rows"} <= set(front["curves"]["pure"]["longitudinal_by_gamma"][0])
    assert {"gamma_deg", "rows"} <= set(front["curves"]["pure"]["lateral_by_gamma"][0])
    assert len(front["curves"]["combined"]["fx_surfaces_by_fz"][0]["rows"]) == 31
    assert len(front["curves"]["combined"]["fy_surfaces_by_fz"][0]["rows"]) == 31
    assert {"fz_n", "rows"} <= set(front["curves"]["combined"]["fx_surfaces_by_fz"][0])
    assert front["curves"]["combined"]["force_map_nominal"]["fz_n"] == pytest.approx(front["metadata"]["fznom_n"])
    assert len(front["curves"]["combined"]["force_map_nominal"]["rows"]) == 31
    assert len(front["curves"]["combined"]["force_map_nominal"]["rows"][0]["points"]) == 31
    assert {"alpha_deg", "kappa", "fx_n", "fy_n", "fz_n"} <= set(
        front["curves"]["combined"]["force_map_nominal"]["rows"][0]["points"][0]
    )
    assert len(front["curves"]["combined"]["force_maps_by_gamma"]) >= 9
    assert {"gamma_deg", "fz_n", "rows"} <= set(front["curves"]["combined"]["force_maps_by_gamma"][0])
    assert len(front["curves"]["combined"]["force_maps_by_gamma_fz"]) >= 9
    assert {"gamma_deg", "maps"} <= set(front["curves"]["combined"]["force_maps_by_gamma_fz"][0])
    assert {"fz_n", "rows"} <= set(front["curves"]["combined"]["force_maps_by_gamma_fz"][0]["maps"][0])
    assert any(
        item["gamma_deg"] == pytest.approx(front["camber_deg"])
        for item in front["curves"]["combined"]["force_maps_by_gamma"]
    )
    assert any(
        item["gamma_deg"] == pytest.approx(front["camber_deg"])
        for item in front["curves"]["combined"]["force_maps_by_gamma_fz"]
    )
    assert len(front["curves"]["load_sensitivity"]) >= 5
    assert {"fz_n", "mu_x", "mu_y"} <= set(front["curves"]["load_sensitivity"][0])
    assert any(abs(point["fx_n"]) > 1 for point in front["curves"]["longitudinal"])
    assert any(abs(point["fy_n"]) > 1 for point in front["curves"]["lateral"])

    live_vehicle = yaml.safe_load((app.ROOT / "vehicle.yml").read_text(encoding="utf-8"))
    live_vehicle["front"]["wheel"]["camber_deg"] = 3.25
    live_payload = app.tire_eval_payload(live_vehicle)
    live_front = next(side for side in live_payload["sides"] if side["side"] == "front")
    assert live_front["camber_deg"] == pytest.approx(3.25)
    assert any(
        item["gamma_deg"] == pytest.approx(3.25)
        for item in live_front["curves"]["combined"]["force_maps_by_gamma"]
    )


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
    workspace_vehicle = tmp_path / "_5_App/vehicle_workspaces/my-saved-vehicle/config/vehicle.yml"
    assert workspace_vehicle.is_file()
    assert library["workspace"]["key"] == "my-saved-vehicle"
    assert library["workspace"]["config"]["exists"] is True

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


def test_app_can_save_active_simulation_results(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
    (tmp_path / "vehicle.yml").write_text(
        "vehicle:\n"
        "  name: ResultCar\n"
        "architecture:\n"
        "  front: direct\n"
        "  rear: bellcrank\n",
        encoding="utf-8",
    )
    (tmp_path / "sim.yml").write_text("simulation:\n  stop_time: 1\n", encoding="utf-8")
    results_dir = tmp_path / "results"
    results_dir.mkdir()
    (results_dir / "report.pdf").write_bytes(b"%PDF demo")
    (results_dir / "metrics.csv").write_text("name,value\nscore,1\n", encoding="utf-8")
    monkeypatch.setattr(app, "ROOT", tmp_path)
    monkeypatch.setattr(app, "SAVED_RESULTS_ROOT", Path("_5_App/saved_results"))
    monkeypatch.setattr(
        app,
        "WORKFLOWS",
        (
            app.WorkflowSpec(
                id="demo-sim",
                group="standard",
                label="DemoSim",
                config="sim.yml",
                actions=(),
                outputs=(
                    app.OutputSpec("Report", "results/report.pdf", "pdf"),
                    app.OutputSpec("Metrics", "results/metrics.csv", "csv"),
                ),
            ),
        ),
    )

    payload = app.save_active_results("demo-sim", "Baseline Run")
    saved = payload["saved"]

    assert saved["label"] == "Baseline Run"
    assert saved["vehicle_name"] == "ResultCar"
    assert saved["architecture"] == {"front": "direct", "rear": "bellcrank"}
    assert [file["label"] for file in saved["files"]] == ["Report", "Metrics"]
    assert all((tmp_path / file["path"]).is_file() for file in saved["files"])
    assert (tmp_path / saved["vehicle_snapshot"]).is_file()
    assert (tmp_path / saved["config_snapshot"]).is_file()
    assert saved["vehicle_key"] == "resultcar"
    assert (tmp_path / saved["workspace_result_path"] / "manifest.json").is_file()
    assert app.saved_results_payload()["results"][0]["id"] == saved["id"]
    assert app.saved_results_payload("resultcar")["results"][0]["id"] == saved["id"]

    sources = app.result_sources_payload("resultcar")["sources"]
    assert [Path(source["path"]).name for source in sources] == ["metrics.csv"]
    assert sources[0]["path"].startswith("_5_App/vehicle_workspaces/resultcar/results/")


def test_app_can_explore_result_csv_sources(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
    results_dir = tmp_path / "_3_StandardSim/results"
    results_dir.mkdir(parents=True)
    csv_path = results_dir / "raw_trace.csv"
    csv_path.write_text(
        "time,accY,roll,case\n"
        "0.0,0.0,0.0,A\n"
        "0.1,1.5,0.02,A\n"
        "0.2,3.0,0.04,A\n",
        encoding="utf-8",
    )
    monkeypatch.setattr(app, "ROOT", tmp_path)
    monkeypatch.setattr(app, "SAVED_RESULTS_ROOT", Path("_5_App/saved_results"))

    sources = app.result_sources_payload()["sources"]
    assert [source["path"] for source in sources] == ["_3_StandardSim/results/raw_trace.csv"]
    assert sources[0]["numeric_columns"] == ["time", "accY", "roll"]

    series = app.result_series_payload(
        "_3_StandardSim/results/raw_trace.csv",
        x_axis="time",
        signals=["accY", "roll"],
        max_points=2,
    )
    assert series["x"] == [0.0, 0.1, 0.2]
    assert series["stride"] == 1
    assert series["series"][0]["values"] == [0.0, 1.5, 3.0]
    assert series["series"][1]["values"] == [0.0, 0.02, 0.04]


def test_app_can_add_and_remove_vehicle_processing_workflows(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    (tmp_path / "vehicle.yml").write_text(
        "vehicle:\n"
        "  name: ProcessingCar\n",
        encoding="utf-8",
    )
    source_dir = tmp_path / "_5_App/vehicle_workspaces/processingcar/results/run-1/files"
    source_dir.mkdir(parents=True)
    source = source_dir / "trace.csv"
    source.write_text("time,ay,roll\n0,0,0\n1,1.2,0.03\n", encoding="utf-8")
    monkeypatch.setattr(app, "ROOT", tmp_path)

    payload = app.add_processing_workflow(
        {
            "vehicle_key": "processingcar",
            "label": "Corner balance export",
            "source_path": "_5_App/vehicle_workspaces/processingcar/results/run-1/files/trace.csv",
            "signals": ["ay", "roll"],
            "output_name": "corner-balance.csv",
        }
    )

    workflow = payload["saved"]
    assert workflow["id"] == "corner-balance-export"
    assert workflow["source"]["exists"] is True
    assert workflow["signals"] == ["ay", "roll"]
    stored = tmp_path / "_5_App/vehicle_workspaces/processingcar/processing/workflows.json"
    assert stored.is_file()
    assert app.processing_workflows_payload("processingcar")["workflows"][0]["id"] == workflow["id"]

    removed = app.delete_processing_workflow(workflow["id"], "processingcar")
    assert removed["workflows"] == []


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
