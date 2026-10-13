from __future__ import annotations

from pathlib import Path

import pytest
import yaml

from common import config_io
from app import app, actions
from app.jobs import JobStore


@pytest.fixture
def archive_workspace(tmp_path: Path, monkeypatch):
    (tmp_path / 'vehicle.yml').write_text('vehicle:\n  name: Original\n')
    (tmp_path / 'sim.yml').write_text('simulation:\n  stop_time: 1\n')
    (tmp_path / 'report.csv').write_text('metric,value\nscore,1\n')
    active = config_io.active_config_path('sim.yml', root=tmp_path)
    active.parent.mkdir(parents=True)
    active.write_text('simulation:\n  stop_time: 99\n')
    workflow = app.WorkflowSpec('study', 'standard', 'Study', 'sim.yml', (),
                                (app.OutputSpec('Report', 'report.csv', 'csv'),))
    monkeypatch.setattr(app, 'ROOT', tmp_path)
    monkeypatch.setattr(app, 'WORKFLOWS', (workflow,))
    monkeypatch.setattr(app, 'BASE_CONFIG_SPECS', {
        'study': app.ConfigSpec('study', 'standard', 'Study', 'sim.yml',
                                workflow_id='study', relocatable=True),
    })
    monkeypatch.delenv(config_io.SEED_ONLY_ENV, raising=False)
    return tmp_path, active


def test_manual_archive_snapshots_active_config(archive_workspace):
    root, active = archive_workspace
    saved = app.save_active_results('study')['saved']
    assert (root / saved['config_snapshot']).read_text() == active.read_text()
    assert saved['config_source'] == active.relative_to(root).as_posix()
    assert saved['input_capture_phase'] == 'archive'


def test_completed_job_uses_start_snapshot_even_after_input_edits(archive_workspace):
    root, active = archive_workspace
    snapshot = app.capture_workflow_inputs('study')
    active.write_text('simulation:\n  stop_time: 7\n')
    (root / 'vehicle.yml').write_text('vehicle:\n  name: Changed\n')
    saved = app.save_active_results('study', input_snapshot=snapshot)['saved']
    assert yaml.safe_load((root / saved['config_snapshot']).read_text())['simulation']['stop_time'] == 99
    assert yaml.safe_load((root / saved['vehicle_snapshot']).read_text())['vehicle']['name'] == 'Original'
    assert saved['vehicle_name'] == 'Original'
    assert saved['input_capture_phase'] == 'job_start'


def test_job_captures_inputs_before_first_action(archive_workspace, monkeypatch):
    root, active = archive_workspace
    store = JobStore(10000)
    monkeypatch.setattr(app, 'JOBS', store)
    seen = []

    def run(*_):
        active.write_text('simulation:\n  stop_time: 7\n')
        return 0

    def save(*args, **kwargs):
        seen.append(kwargs['input_snapshot'])
        return {'saved': {'label': 'Review'}}

    monkeypatch.setattr(actions, '_run_action_process', run)
    monkeypatch.setattr(app, 'save_active_results', save)
    job = store.create('a', 'A', [])
    app.run_actions_job((app.ActionSpec('a', 'A', ()),), job['id'], 'study')
    assert store.get(job['id'])['status'] == 'succeeded'
    assert yaml.safe_load(seen[0]['config_text'])['simulation']['stop_time'] == 99


def test_seed_only_mode_is_respected_by_archive(archive_workspace, monkeypatch):
    root, _ = archive_workspace
    monkeypatch.setenv(config_io.SEED_ONLY_ENV, '1')
    saved = app.save_active_results('study')['saved']
    assert yaml.safe_load((root / saved['config_snapshot']).read_text())['simulation']['stop_time'] == 1


def test_named_simulations_keep_independent_configs_and_vehicle_ownership(archive_workspace):
    root, active = archive_workspace
    first = app.simulation_workspace('create', {'workflow_id': 'study', 'name': 'Slow'})['simulation']
    active.write_text('simulation:\n  stop_time: 12\n')
    second = app.simulation_workspace('create', {'workflow_id': 'study', 'name': 'Fast'})['simulation']
    assert first['id'] != second['id']
    app.simulation_workspace('load', {'id': first['id']})
    assert yaml.safe_load(active.read_text())['simulation']['stop_time'] == 99
    app.simulation_workspace('load', {'id': second['id']})
    assert yaml.safe_load(active.read_text())['simulation']['stop_time'] == 12
    active.write_text('simulation:\n  stop_time: 14\n')
    app.simulation_workspace('save', {'id': second['id'], 'name': 'Fast updated'})
    app.simulation_workspace('load', {'id': first['id']})
    app.simulation_workspace('load', {'id': second['id']})
    assert yaml.safe_load(active.read_text())['simulation']['stop_time'] == 14
    (root / 'vehicle.yml').write_text('vehicle:\n  name: Other\n')
    assert app.simulation_workspace()['simulations'] == []
    with pytest.raises(ValueError, match='not found'):
        app.simulation_workspace('load', {'id': first['id']})
    with pytest.raises(ValueError, match='active vehicle changed'):
        app.simulation_workspace('create', {'workflow_id': 'study', 'vehicle_key': 'original'})


def test_named_simulation_run_metadata_survives_edits_and_removal(archive_workspace):
    root, _ = archive_workspace
    simulation = app.simulation_workspace('create', {'workflow_id': 'study', 'name': 'Initial'})['simulation']
    snapshot = app.capture_workflow_inputs('study')
    snapshot['simulation'] = simulation
    saved = app.save_active_results('study', input_snapshot=snapshot)['saved']
    app.simulation_workspace('save', {'id': simulation['id'], 'name': 'Renamed'})
    app.simulation_workspace('delete', {'id': simulation['id']})
    assert app.simulation_workspace()['simulations'] == []
    assert saved['simulation']['name'] == 'Initial'
    assert (root / saved['config_snapshot']).is_file()
    assert app.saved_results_payload()['results'][0]['simulation']['id'] == simulation['id']


def test_start_named_simulation_loads_its_config_under_job_lock(archive_workspace, monkeypatch):
    from app import execution

    _, active = archive_workspace
    simulation = app.simulation_workspace('create', {'workflow_id': 'study'})['simulation']
    active.write_text('simulation:\n  stop_time: 2\n')
    store = JobStore(10000)
    monkeypatch.setattr(app, 'JOBS', store)
    seen = []

    def run(_actions, job_id, workflow_id):
        assert execution.LOCK.locked()
        seen.append((store.get(job_id)['simulation'], active.read_text()))

    class InlineThread:
        def __init__(self, target, **kwargs):
            self.target = target

        def start(self):
            self.target()

    monkeypatch.setattr(actions, 'run_actions_job', run)
    monkeypatch.setattr(actions.threading, 'Thread', InlineThread)
    app.start_workflow('study', simulation_id=simulation['id'], vehicle_key='original')
    assert seen[0][0]['id'] == simulation['id']
    assert yaml.safe_load(seen[0][1])['simulation']['stop_time'] == 99
    assert not execution.LOCK.locked()
    with pytest.raises(ValueError, match='active vehicle changed'):
        app.start_workflow('study', simulation_id=simulation['id'], vehicle_key='different')
    assert not execution.LOCK.locked()


def test_visualizations_belong_to_the_parent_simulation_and_keep_the_run(archive_workspace):
    root, _ = archive_workspace
    parent = app.simulation_workspace("create", {"workflow_id": "study"})["simulation"]
    other = app.simulation_workspace("create", {"workflow_id": "study"})["simulation"]
    snapshot = app.capture_workflow_inputs("study")
    snapshot["simulation"] = parent
    saved = app.save_active_results("study", input_snapshot=snapshot)["saved"]
    with pytest.raises(ValueError, match="saved run from this simulation"):
        app.simulation_workspace("add-visualization", {"id": other["id"], "run_id": saved["id"]})
    child = app.simulation_workspace("add-visualization", {
        "id": parent["id"], "run_id": saved["id"], "name": "Response plots",
    })["visualization"]
    loaded = app.simulation_workspace("load", {"id": parent["id"]})["simulation"]
    assert loaded["visualizations"] == [child]
    app.simulation_workspace("delete-visualization", {"id": parent["id"], "child_id": child["id"]})
    assert app.simulation_workspace()["simulations"][0]["visualizations"] == []
    assert (root / saved["config_snapshot"]).is_file()
    assert app.saved_results_payload()["results"][0]["id"] == saved["id"]


def test_replay_visualization_requires_an_existing_capture(archive_workspace, monkeypatch):
    from app import visual

    parent = app.simulation_workspace("create", {"workflow_id": "study"})["simulation"]
    with pytest.raises(ValueError, match="available captured scene"):
        app.simulation_workspace("add-visualization", {
            "id": parent["id"], "kind": "replay", "source_id": "missing",
        })
    monkeypatch.setattr(visual, "available_runs", lambda root: [{"id": "captured-rig"}])
    child = app.simulation_workspace("add-visualization", {
        "id": parent["id"], "kind": "replay", "source_id": "captured-rig", "name": "Rig replay",
    })["visualization"]
    assert child["kind"] == "replay"
    assert child["run_id"] == "captured-rig"
    assert app.simulation_workspace("load", {"id": parent["id"]})["simulation"]["visualizations"] == [child]


def test_saved_replay_cannot_be_attached_to_a_different_simulation(archive_workspace, monkeypatch):
    from app import visual

    parent = app.simulation_workspace("create", {"workflow_id": "study"})["simulation"]
    monkeypatch.setattr(visual, "available_runs", lambda root: [{
        "id": "saved-other", "simulation_id": "other", "vehicle_key": "original",
    }])
    with pytest.raises(ValueError, match="available captured scene"):
        app.simulation_workspace("add-visualization", {
            "id": parent["id"], "kind": "replay", "source_id": "saved-other",
        })
