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
