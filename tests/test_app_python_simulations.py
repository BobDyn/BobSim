from __future__ import annotations

import json
from types import SimpleNamespace

import numpy as np
import pytest
import yaml

from app import app, python_simulations
from common import config_io


PYTHON_WORKFLOWS = ("ggv", "ymd", "reduced-step-steer", "lap-qss", "lap-transient")


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


@pytest.mark.parametrize("workflow_id", ("reduced-step-steer", "lap-qss", "lap-transient"))
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
    active = config_io.active_config_path("reduced_order_eval_config.yml", root=tmp_path)
    active.parent.mkdir(parents=True)
    data = {"model_dof": 14, "speed_mps": 8, "roadwheel_step_deg": 2,
            "step_time_s": 0.1, "rise_time_s": 0.05, "stop_time_s": 0.2,
            "sample_period_s": 0.1, "kinematics_mode": "nonlinear"}
    active.write_text(yaml.safe_dump(data))
    seen = {}

    def simulate(**kwargs):
        seen.update(kwargs)
        return SimpleNamespace(time_s=np.array([0, 0.1]), signals={"yawVel": [0, 0.2]}, success=True)

    monkeypatch.setattr(python_simulations, "run_step_steer", simulate)
    python_simulations.run("reduced-step-steer")
    assert seen["dof"] == 14
    assert seen["vehicle_path"] == tmp_path / "vehicle.yml"
    assert seen["kinematics_mode"] == "nonlinear"
    assert seen["roadwheel_step_deg"] == 2
    output = tmp_path / "app/user_data/results/reduced-step-steer"
    assert "yawVel" in (output / "signals.csv").read_text()
    assert json.loads((output / "summary.json").read_text())["model_dof"] == 14


@pytest.mark.parametrize("scenario", ("qss", "transient"))
def test_lap_dispatches_selected_scenario_and_rejects_incomplete_run(tmp_path, monkeypatch, scenario):
    monkeypatch.setattr(python_simulations, "repo_root", lambda: tmp_path)
    active = config_io.active_config_path("lap_time_eval_config.yml", root=tmp_path)
    active.parent.mkdir(parents=True)
    active.write_text("model_dof: 6\n")
    seen = []

    def simulate(config, **kwargs):
        seen.append((config, kwargs))
        return {"qss_converged": scenario == "transient", "transient_success": True,
                "transient_completed_lap": False}

    monkeypatch.setattr(python_simulations, "run_lap_time_evaluation", simulate)
    with pytest.raises(RuntimeError):
        python_simulations.run(f"lap-{scenario}")
    assert seen == [(active, {"scenario": scenario})]
