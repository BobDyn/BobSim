from pathlib import Path

import yaml

from app import data_services
from app.registry import build_workflows


def test_model_selection_is_captured_before_config_changes(tmp_path: Path, monkeypatch) -> None:
    workflow = next(item for item in build_workflows() if item.id == "ggv")
    path = tmp_path / str(workflow.config)
    path.parent.mkdir(parents=True)
    path.write_text(yaml.safe_dump({"generation": {"model_dof": 6}}))
    monkeypatch.setattr(data_services, "ROOT", tmp_path)
    monkeypatch.setattr(data_services, "WORKFLOWS", (workflow,))
    captured = data_services.capture_workflow_inputs(workflow.id)
    path.write_text(yaml.safe_dump({"generation": {"model_dof": 14}}))
    assert captured["model"]["fidelity"] == "6 DOF QSS"
    assert data_services.workflow_model(workflow, root=tmp_path)["fidelity"] == "14 DOF QSS"
    assert captured["model"]["engine"] == "DynPy"
    assert captured["model"]["runtime"] == "Python"


def test_mbd_workflows_identify_compiled_runtime(tmp_path: Path) -> None:
    workflow = next(item for item in build_workflows() if item.id == "four-post")
    model = data_services.workflow_model(workflow, root=tmp_path)
    assert model["engine"] == "BobLib"
    assert model["fidelity"] == "MBD"
    assert model["runtime"] == "OpenModelica compiled executable"
    assert model["model_dofs"] == []
