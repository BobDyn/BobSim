from __future__ import annotations

import json
from types import SimpleNamespace
import re

import numpy as np
import pytest
import yaml

from app import app, python_simulations
from common import config_io


PYTHON_WORKFLOWS = ("ggv", "ymd", "reduced-step-steer", "reduced-ramp-steer", "lap-qss", "lap-transient")


def test_python_workflows_do_not_require_openmodelica(monkeypatch):
    monkeypatch.setattr(app, "external_toolchain_available", lambda: False)
    for name in PYTHON_WORKFLOWS:
        workflow = next(item for item in app.WORKFLOWS if item.id == name)
        payload = app.workflow_payload(workflow)
        assert payload["available"]
        assert not payload["requires_mbd"]
        assert payload["model"]["engine"] == "DynPy"
        assert payload["model"]["model_dofs"]
    assert not app.workflow_available(next(w for w in app.WORKFLOWS if w.id == "transient"))


@pytest.mark.parametrize("workflow_id", ("reduced-step-steer", "reduced-ramp-steer", "lap-qss", "lap-transient"))
def test_model_label_and_archive_use_active_dof(tmp_path, monkeypatch, workflow_id):
    monkeypatch.setattr(app, "ROOT", tmp_path)
    workflow = next(item for item in app.WORKFLOWS if item.id == workflow_id)
    seed = tmp_path / workflow.config
    seed.parent.mkdir(parents=True)
    seed.write_text("model_dof: 3\n")
    active = config_io.active_config_path(seed, root=tmp_path)
    active.parent.mkdir(parents=True)
    active.write_text("model_dof: 14\n")
    payload = app.workflow_payload(workflow)
    assert payload["model"]["model_dofs"] == [14]
    snapshot = app.capture_workflow_inputs(workflow_id)
    assert snapshot["model"] == payload["model"]
    assert yaml.safe_load(snapshot["config_text"])["model_dof"] == 14
    assert seed.read_text() == "model_dof: 3\n"


def test_invalid_dof_is_rejected_without_changing_config(tmp_path, monkeypatch):
    monkeypatch.setattr(app, "ROOT", tmp_path)
    seed = tmp_path / app.BASE_CONFIG_SPECS["reduced-step-steer"].path
    seed.parent.mkdir(parents=True)
    seed.write_text("model_dof: 6\n")
    with pytest.raises(ValueError, match="Model DOF"):
        app.patch_config("reduced-step-steer", {json.dumps(["model_dof"]): "7"})
    active = config_io.active_config_path(seed, root=tmp_path)
    assert yaml.safe_load(active.read_text())["model_dof"] == 6
    with pytest.raises(ValueError, match="Model DOF"):
        app.save_raw_config("reduced-step-steer", "model_dof: 6.5\n")
    assert yaml.safe_load(active.read_text())["model_dof"] == 6
    assert app.patch_config("reduced-step-steer", {json.dumps(["model_dof"]): "10"})["data"]["model_dof"] == 10


def test_step_steer_uses_active_config_and_exports_signals(tmp_path, monkeypatch):
    monkeypatch.setattr(python_simulations, "repo_root", lambda: tmp_path)
    (tmp_path / "vehicle.yml").write_text("vehicle:\n  name: Report fixture\n")
    active = config_io.active_config_path("reduced_order_eval_config.yml", root=tmp_path)
    active.parent.mkdir(parents=True)
    data = {"model_dof": 14, "speed_mps": 8, "roadwheel_step_deg": 2,
            "step_time_s": 0.1, "rise_time_s": 0.05, "stop_time_s": 0.2,
            "sample_period_s": 0.1, "kinematics_mode": "nonlinear"}
    active.write_text(yaml.safe_dump(data))
    seen = {}

    def simulate(**kwargs):
        seen.update(kwargs)
        return SimpleNamespace(time_s=np.array([0, 0.1]),
                               signals={"yawVel": [0, 0.2], "accY": [0, 1.5],
                                        "velX": [8, 8], "handwheelAngle": [0, 0.03]}, success=True)

    monkeypatch.setattr(python_simulations, "run_step_steer", simulate)
    python_simulations.run("reduced-step-steer")
    assert seen["dof"] == 14
    assert seen["vehicle_path"] == tmp_path / "vehicle.yml"
    assert seen["kinematics_mode"] == "lookup"
    assert seen["roadwheel_step_deg"] == 2
    output = tmp_path / "app/user_data/results/reduced-step-steer"
    assert "yawVel" in (output / "signals.csv").read_text()
    report = (output / "report.pdf").read_bytes()
    assert report.startswith(b"%PDF")
    assert len(re.findall(rb"/Type /Page\b", report)) == 3
    assert json.loads((output / "summary.json").read_text())["model_dof"] == 14


@pytest.mark.parametrize("scenario", ("qss", "transient"))
def test_lap_dispatches_selected_scenario_and_rejects_incomplete_run(tmp_path, monkeypatch, scenario):
    monkeypatch.setattr(python_simulations, "repo_root", lambda: tmp_path)
    active = config_io.active_config_path("lap_time_eval_config.yml", root=tmp_path)
    active.parent.mkdir(parents=True)
    active.write_text("model_dof: 6\noutput:\n  directory: results\n")
    (tmp_path / "vehicle.yml").write_text("vehicle:\n  name: Fixture\n")
    reports = []
    monkeypatch.setattr(python_simulations, "build_dynpy_report", lambda *args, **kwargs: reports.append(args))
    seen = []

    def simulate(config, **kwargs):
        seen.append((config, kwargs))
        return {"model_dof": 6, "qss_converged": scenario == "transient", "transient_success": True,
                "transient_completed_lap": False}

    monkeypatch.setattr(python_simulations, "run_lap_time_evaluation", simulate)
    with pytest.raises(RuntimeError):
        python_simulations.run(f"lap-{scenario}")
    assert seen == [(active, {"scenario": scenario})]
    assert reports[0][0] == f"lap-{scenario}"
    assert reports[0][1] == tmp_path / "results"


def test_every_simulation_registers_a_pdf_report():
    for workflow in app.WORKFLOWS:
        if workflow.group in {"standard", "response", "envelope", "lap"}:
            assert any(output.kind == "pdf" for output in workflow.outputs), workflow.id


@pytest.mark.parametrize("scenario, pages", (("qss", 4), ("transient", 5)))
def test_lap_reports_include_reference_and_transient_pages(tmp_path, scenario, pages):
    import pandas as pd

    from common.reporting.dynpy_report import build_dynpy_report

    pd.DataFrame({
        "station_m": [0, 10, 20], "x_m": [0, 10, 0], "y_m": [0, 5, 0],
        "speed_mps": [8, 9, 8], "ax_mps2": [0, 1, -1], "ay_mps2": [1, 2, 1],
        "curvature_per_m": [0.01, 0.02, 0.01],
    }).to_csv(tmp_path / "qss_lap.csv", index=False)
    pd.DataFrame({
        "time_s": [0, 1, 2], "speed_mps": [8, 8.5, 8], "steering_rad": [0, 0.02, 0.01],
        "lateral_error_m": [0, 0.1, 0.05], "yaw_rate_radps": [0, 0.1, 0.05],
    }).to_csv(tmp_path / "transient_lap.csv", index=False)
    summary = {
        "model_dof": 6, "qss_converged": True, "line_optimizer_converged": True,
        "line_mode": "minimum_curvature", "track_length_m": 20,
        "optimized_qss_lap_time_s": 2, "effective_drive_power_limit_w": 80000,
        "ggv_provenance": {"status": "verified"}, "transient_success": True,
        "transient_completed_lap": False, "transient_lap_time_s": 2.2,
        "transient_lap_delta_s": 0.2, "transient_max_abs_lateral_error_m": 0.1,
    }
    report = build_dynpy_report(
        f"lap-{scenario}", tmp_path, {"track": {"boundary_csv": "fixture.csv"}}, summary,
        vehicle_name="Report layout fixture",
    ).read_bytes()
    assert report.startswith(b"%PDF")
    assert len(re.findall(rb"/Type /Page\b", report)) == pages


def test_ramp_uses_active_rate_and_exports_its_own_report(tmp_path, monkeypatch):
    monkeypatch.setattr(python_simulations, "repo_root", lambda: tmp_path)
    (tmp_path / "vehicle.yml").write_text("vehicle:\n  name: Ramp fixture\n")
    active = config_io.active_config_path("ramp_steer_config.yml", root=tmp_path)
    active.parent.mkdir(parents=True)
    data = {"model_dof": 10, "speed_mps": 8, "roadwheel_rate_deg_s": -2,
            "start_time_s": 0.1, "ramp_end_time_s": 0.2, "stop_time_s": 0.3, "sample_period_s": 0.1,
            "kinematics_mode": "nonlinear"}
    active.write_text(yaml.safe_dump(data))
    seen = {}

    def simulate(**kwargs):
        seen.update(kwargs)
        return SimpleNamespace(time_s=np.array([0, 0.1, 0.2, 0.3]), success=True,
                               signals={"yawVel": [0, 0, -0.1, -0.2], "accY": [0, 0, -0.5, -1],
                                        "velX": [8] * 4, "handwheelAngle": [0, 0, -0.0035, -0.007]})

    monkeypatch.setattr(python_simulations, "run_ramp_steer", simulate)
    python_simulations.run("reduced-ramp-steer")
    assert seen["dof"] == 10
    assert seen["roadwheel_rate_deg_s"] == -2
    assert seen["start_time_s"] == 0.1
    assert seen["ramp_end_time_s"] == 0.2
    assert seen["kinematics_mode"] == "lookup"
    output = tmp_path / "app/user_data/results/reduced-ramp-steer"
    assert (output / "report.pdf").read_bytes().startswith(b"%PDF")
    assert json.loads((output / "summary.json").read_text())["model_dof"] == 10
    assert not (tmp_path / "app/user_data/results/reduced-step-steer").exists()


def test_mbd_step_dispatch_uses_its_active_config(tmp_path, monkeypatch):
    from simulations.response.mbd.transient import transient_eval_sim

    monkeypatch.setattr(python_simulations, "repo_root", lambda: tmp_path)
    active = config_io.active_config_path("step_steer_config.yml", root=tmp_path)
    active.parent.mkdir(parents=True)
    active.write_text("test:\n  run_step: true\n  run_continuous_sine: false\n")
    seen = []
    monkeypatch.setattr(transient_eval_sim, "main", lambda config: seen.append(config))
    python_simulations.run("mbd-step-steer")
    assert seen == [active]


def test_mbd_step_builds_only_step_cases(monkeypatch):
    from simulations.response.mbd.transient.transient_eval_sim import ModelicaRunner, TransientEvalSim

    monkeypatch.setattr(ModelicaRunner, "from_config", lambda config: None)
    path = app.ROOT / app.BASE_CONFIG_SPECS["mbd-step-steer"].path
    config = yaml.safe_load(path.read_text())
    cases, metadata = TransientEvalSim(config).build_cases()
    assert cases
    assert len(cases) == len(config["test"]["testVel"])
    assert all(item["mode"] == "step" for item in metadata)
    assert all(case["useMode"] == 2 for case in cases)
    assert config["report"]["output_path"].endswith("/step_steer_report.pdf")
    assert app.MODELICA_RUN_TARGETS_BY_ACTION["run-mbd-step-steer"].id == "vehicle"


def test_legacy_ramp_keeps_its_end_when_simulation_duration_changes(tmp_path, monkeypatch):
    monkeypatch.setattr(app, "ROOT", tmp_path)
    seed = tmp_path / app.BASE_CONFIG_SPECS["reduced-ramp-steer"].path
    seed.parent.mkdir(parents=True)
    seed.write_text("model_dof: 14\nstart_time_s: 1\nstop_time_s: 5\n")
    payload = app.config_payload("reduced-ramp-steer")
    assert payload["data"]["ramp_end_time_s"] == 5
    updated = app.patch_config("reduced-ramp-steer", {json.dumps(["stop_time_s"]): 20})
    assert updated["data"]["ramp_end_time_s"] == 5
    assert updated["data"]["stop_time_s"] == 20


@pytest.mark.parametrize('workflow_id', ('reduced-step-steer', 'reduced-ramp-steer'))
def test_app_kinematics_selection_is_automatic(tmp_path, monkeypatch, workflow_id):
    monkeypatch.setattr(app, 'ROOT', tmp_path)
    seed = tmp_path / app.BASE_CONFIG_SPECS[workflow_id].path
    seed.parent.mkdir(parents=True)
    seed.write_text('model_dof: 6\nstop_time_s: 1\nkinematics_mode: nonlinear\n')
    payload = app.config_payload(workflow_id)
    assert payload['data']['kinematics_mode'] == 'lookup'
    assert all(field['path'] != ['kinematics_mode'] for field in payload['fields'])
