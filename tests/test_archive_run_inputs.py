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


@pytest.mark.parametrize("kind", ["report", "signals"])
def test_visualizations_belong_to_the_parent_simulation_and_keep_the_run(archive_workspace, kind):
    root, _ = archive_workspace
    parent = app.simulation_workspace("create", {"workflow_id": "study"})["simulation"]
    other = app.simulation_workspace("create", {"workflow_id": "study"})["simulation"]
    snapshot = app.capture_workflow_inputs("study")
    snapshot["simulation"] = parent
    saved = app.save_active_results("study", input_snapshot=snapshot)["saved"]
    with pytest.raises(ValueError, match="saved run from this simulation"):
        app.simulation_workspace("add-visualization", {"id": other["id"], "run_id": saved["id"], "kind": kind})
    child = app.simulation_workspace("add-visualization", {
        "id": parent["id"], "run_id": saved["id"], "name": "Response plots", "kind": kind,
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
    with pytest.raises(ValueError, match="available captured scene"):
        app.simulation_workspace("add-visualization", {
            "id": parent["id"], "kind": "replay", "source_id": "captured-rig",
        })
    monkeypatch.setattr(visual, "available_runs", lambda root: [{
        "id": "captured-rig", "simulation_id": parent["id"], "vehicle_key": "original",
    }])
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


@pytest.mark.parametrize("kind", ["report", "signals", "replay"])
def test_analysis_views_follow_latest_results_without_a_source(archive_workspace, monkeypatch, kind):
    from app import visual

    parent = app.simulation_workspace("create", {"workflow_id": "study"})["simulation"]
    captures = []
    monkeypatch.setattr(visual, "available_runs", lambda root: captures)
    child = app.simulation_workspace("add-visualization", {"id": parent["id"], "kind": kind})["visualization"]
    assert child["run_id"] is None
    snapshot = app.capture_workflow_inputs("study")
    snapshot["simulation"] = parent
    first = app.save_active_results("study", input_snapshot=snapshot)["saved"]
    captures.append({"id": "saved-" + first["id"], "simulation_id": parent["id"], "vehicle_key": "original"})
    loaded = app.simulation_workspace()["simulations"][0]["visualizations"][0]
    assert loaded["run_id"] == ("saved-" if kind == "replay" else "") + first["id"]
    second = app.save_active_results("study", input_snapshot=snapshot)["saved"]
    if kind == "replay":
        # A new report without replay data must not silently show the old animation.
        assert app.simulation_workspace()["simulations"][0]["visualizations"][0]["run_id"] is None
    captures.insert(0, {"id": "saved-" + second["id"], "simulation_id": parent["id"], "vehicle_key": "original"})
    loaded = app.simulation_workspace()["simulations"][0]["visualizations"][0]
    assert loaded["id"] == child["id"]
    assert loaded["run_id"] == ("saved-" if kind == "replay" else "") + second["id"]


@pytest.fixture
def linked_ggv_workspace(tmp_path, monkeypatch):
    from types import SimpleNamespace
    from app import data_services
    from simulations.envelope import vehicle_yaml

    monkeypatch.setattr(app, 'ROOT', tmp_path)
    monkeypatch.setattr(data_services, '_ggv_link_signature', lambda: 'current-inputs')
    monkeypatch.setattr(vehicle_yaml, 'project_vehicle_yaml', lambda _: SimpleNamespace(
        ggv=SimpleNamespace(max_drive_power=80000.)))
    (tmp_path / 'vehicle.yml').write_text('vehicle:\n  name: Linked\n')
    ggv_path = 'simulations/envelope/ggv/ggv_config.yml'
    (tmp_path / ggv_path).parent.mkdir(parents=True)
    (tmp_path / ggv_path).write_text(yaml.safe_dump({
        'vehicle_template': '../../../vehicle.yml', 'generation': {'model_dof': 14}}))
    (tmp_path / 'lap.yml').write_text(yaml.safe_dump({
        'model_dof': 14, 'qss': {'ggv_csv': 'local.csv', 'generate_if_missing': True}}))
    (tmp_path / 'envelope.csv').write_text('speed_mps,ay_mps2,ax_accel_mps2,ax_brake_mps2\n5,0,10,-10\n')
    workflows = (
        app.WorkflowSpec('ggv', 'envelope', 'GGV', ggv_path, (),
                         (app.OutputSpec('Raw CSV', 'envelope.csv', 'csv'),), engine='DynPy'),
        app.WorkflowSpec('lap-qss', 'lap', 'Lap', 'lap.yml', (), engine='DynPy'),
    )
    monkeypatch.setattr(app, 'WORKFLOWS', workflows)
    monkeypatch.setattr(app, 'BASE_CONFIG_SPECS', {
        w.id: app.ConfigSpec(w.id, w.group, w.label, w.config, workflow_id=w.id) for w in workflows
    })
    source = app.simulation_workspace('create', {'workflow_id': 'ggv'})['simulation']
    lap = app.simulation_workspace('create', {'workflow_id': 'lap-qss'})['simulation']
    app.simulation_workspace('set-ggv', {'id': lap['id'], 'source_id': source['id']})

    def archive():
        inputs = app.capture_workflow_inputs('ggv')
        inputs['simulation'] = source
        return app.save_active_results('ggv', input_snapshot=inputs)['saved']

    return tmp_path, source, lap, archive


def test_linked_ggv_requires_a_saved_compatible_result(linked_ggv_workspace):
    root, source, lap, archive = linked_ggv_workspace
    with pytest.raises(ValueError, match='Run the connected'):
        app.simulation_workspace('prepare-run', {'id': lap['id']})
    saved = archive()
    assert saved['ggv_signature'] == 'current-inputs'
    app.simulation_workspace('prepare-run', {'id': lap['id']})
    config = yaml.safe_load((root / 'lap.yml').read_text())
    assert config['qss']['linked_ggv']['run_id'] == saved['id']
    assert config['qss']['generate_if_missing'] is False
    assert config['qss']['ggv_csv'] != 'local.csv'
    app.simulation_workspace('save', {'id': lap['id']})
    app.simulation_workspace('load', {'id': lap['id']})
    config = yaml.safe_load((root / 'lap.yml').read_text())
    assert config['qss'] == {'ggv_csv': 'local.csv', 'generate_if_missing': True}
    newer = archive()
    app.simulation_workspace('prepare-run', {'id': lap['id']})
    assert yaml.safe_load((root / 'lap.yml').read_text())['qss']['linked_ggv']['run_id'] == newer['id']
    app.simulation_workspace('delete', {'id': source['id']})
    with pytest.raises(ValueError, match='deleted'):
        app.simulation_workspace('prepare-run', {'id': lap['id']})
    app.simulation_workspace('set-ggv', {'id': lap['id'], 'source_id': None})
    app.simulation_workspace('prepare-run', {'id': lap['id']})
    assert yaml.safe_load((root / 'lap.yml').read_text())['qss']['generate_if_missing'] is True


@pytest.mark.parametrize('change,message', [
    ('power', 'Power limits differ'),
    ('settings', 'settings changed'), ('physics', 'current vehicle'),
])
def test_linked_ggv_rejects_stale_or_incompatible_inputs(linked_ggv_workspace, monkeypatch, change, message):
    from app import data_services
    root, source, lap, archive = linked_ggv_workspace
    archive()
    if change == 'physics':
        monkeypatch.setattr(data_services, '_ggv_link_signature', lambda: 'changed-tire')
    else:
        owner = source if change == 'settings' else lap
        app.simulation_workspace('load', {'id': owner['id']})
        path = root / ('simulations/envelope/ggv/ggv_config.yml' if change == 'settings' else 'lap.yml')
        data = yaml.safe_load(path.read_text())
        if change == 'settings':
            data['generation']['ay_points'] = 31
        else:
            data['event'] = {'drive_power_limit_w': 32000}
        path.write_text(yaml.safe_dump(data))
        app.simulation_workspace('save', {'id': owner['id']})
    with pytest.raises(ValueError, match=message):
        app.simulation_workspace('prepare-run', {'id': lap['id']})


def test_ggv_connection_rejects_non_ggv_source(linked_ggv_workspace):
    _, _, lap, _ = linked_ggv_workspace
    with pytest.raises(ValueError, match='Choose a GGV'):
        app.simulation_workspace('set-ggv', {'id': lap['id'], 'source_id': lap['id']})


def test_linked_lap_inherits_source_fidelity(linked_ggv_workspace):
    root, source, lap, archive = linked_ggv_workspace
    app.simulation_workspace('load', {'id': source['id']})
    source_path = root / 'simulations/envelope/ggv/ggv_config.yml'
    config = yaml.safe_load(source_path.read_text())
    config['generation']['model_dof'] = 6
    source_path.write_text(yaml.safe_dump(config))
    app.simulation_workspace('save', {'id': source['id']})
    loaded = app.simulation_workspace('load', {'id': lap['id']})
    assert loaded['simulation']['model']['model_dofs'] == [6]
    assert yaml.safe_load((root / 'lap.yml').read_text())['model_dof'] == 6
    archive()
    app.simulation_workspace('prepare-run', {'id': lap['id']})
    prepared = yaml.safe_load((root / 'lap.yml').read_text())
    assert prepared['model_dof'] == prepared['qss']['linked_ggv']['model_dof'] == 6
    app.simulation_workspace('set-ggv', {'id': lap['id'], 'source_id': None})
    app.simulation_workspace('load', {'id': lap['id']})
    assert yaml.safe_load((root / 'lap.yml').read_text())['model_dof'] == 6


def test_baseline_is_pinned_and_compares_archived_inputs(archive_workspace):
    root, active = archive_workspace
    analysis = app.simulation_workspace('create', {'workflow_id': 'study'})['simulation']

    def archive():
        snapshot = app.capture_workflow_inputs('study')
        snapshot['simulation'] = analysis
        return app.save_active_results('study', input_snapshot=snapshot)['saved']

    baseline = archive()
    original = (root / baseline['config_snapshot']).read_bytes()
    app.simulation_workspace('set-baseline', {'id': analysis['id'], 'run_id': baseline['id']})
    active.write_text('simulation:\n  stop_time: 7\nmodel_dof: 14\n')
    current = archive()
    active.write_text('simulation:\n  stop_time: 1000\n')
    result = app.simulation_workspace('comparison', {'id': analysis['id']})['comparison']
    assert result['available']
    assert result['baseline']['id'] == baseline['id']
    assert result['current']['id'] == current['id']
    assert {'path': 'config.simulation.stop_time', 'before': 99, 'after': 7} in result['changes']
    assert (root / baseline['config_snapshot']).read_bytes() == original
    newer = archive()
    assert app.simulation_workspace('comparison', {'id': analysis['id']})['comparison']['current']['id'] == newer['id']
    assert app.simulation_workspace()['simulations'][0]['baseline_run_id'] == baseline['id']
    app.simulation_workspace('set-baseline', {'id': analysis['id'], 'run_id': None})
    assert not app.simulation_workspace('comparison', {'id': analysis['id']})['comparison']['available']


def test_duplicate_keeps_independent_configuration_and_views(archive_workspace):
    _, active = archive_workspace
    original = app.simulation_workspace('create', {'workflow_id': 'study'})['simulation']
    view = app.simulation_workspace('add-visualization', {'id': original['id'], 'kind': 'signals'})['visualization']
    settings = {'x_axis': 'time', 'signals': ['speed'], 'color_signal': '', 'source_label': 'Report',
                'compare_baseline': True}
    app.simulation_workspace('update-visualization', {
        'id': original['id'], 'child_id': view['id'], 'settings': settings})
    snapshot = app.capture_workflow_inputs('study')
    snapshot['simulation'] = original
    baseline = app.save_active_results('study', input_snapshot=snapshot)['saved']
    duplicate = app.simulation_workspace('duplicate', {'id': original['id'], 'name': 'Variant'})['simulation']
    assert duplicate['id'] != original['id']
    assert duplicate['baseline_run_id'] == baseline['id']
    assert duplicate['visualizations'][0]['id'] != view['id']
    assert duplicate['visualizations'][0]['settings'] == settings
    assert duplicate['visualizations'][0]['run_id'] is None
    active.write_text('simulation:\n  stop_time: 3\n')
    app.simulation_workspace('save', {'id': duplicate['id']})
    app.simulation_workspace('load', {'id': original['id']})
    assert yaml.safe_load(active.read_text())['simulation']['stop_time'] == 99
    with pytest.raises(ValueError, match='from this simulation'):
        app.simulation_workspace('update-visualization', {
            'id': duplicate['id'], 'child_id': view['id'], 'settings': {}})


@pytest.mark.parametrize('settings', [{'signals': 'speed'}, {'x_axis': 3}, {'other': 'x'}, {'compare_baseline': 'yes'}])
def test_plot_settings_reject_invalid_payload(archive_workspace, settings):
    analysis = app.simulation_workspace('create', {'workflow_id': 'study'})['simulation']
    view = app.simulation_workspace('add-visualization', {'id': analysis['id'], 'kind': 'signals'})['visualization']
    with pytest.raises(ValueError, match='Invalid plot settings'):
        app.simulation_workspace('update-visualization', {
            'id': analysis['id'], 'child_id': view['id'], 'settings': settings})


def test_baseline_and_current_run_validate_vehicle_and_analysis(archive_workspace):
    root, _ = archive_workspace
    original = app.simulation_workspace('create', {'workflow_id': 'study'})['simulation']
    snapshot = app.capture_workflow_inputs('study')
    snapshot['simulation'] = original
    saved = app.save_active_results('study', input_snapshot=snapshot)['saved']
    other = app.simulation_workspace('create', {'workflow_id': 'study'})['simulation']
    app.simulation_workspace('set-baseline', {'id': other['id'], 'run_id': saved['id']})
    with pytest.raises(ValueError, match='from this simulation'):
        app.simulation_workspace('comparison', {'id': other['id'], 'run_id': saved['id']})
    (root / 'vehicle.yml').write_text('vehicle:\n  name: Other\n')
    foreign = app.simulation_workspace('create', {'workflow_id': 'study'})['simulation']
    with pytest.raises(ValueError, match='same analysis type'):
        app.simulation_workspace('set-baseline', {'id': foreign['id'], 'run_id': saved['id']})


def test_baseline_rejects_different_workflow_and_missing_snapshot(archive_workspace):
    import json

    root, _ = archive_workspace
    analysis = app.simulation_workspace('create', {'workflow_id': 'study'})['simulation']
    snapshot = app.capture_workflow_inputs('study')
    snapshot['simulation'] = analysis
    saved = app.save_active_results('study', input_snapshot=snapshot)['saved']
    manifest = root / saved['workspace_result_path'] / 'manifest.json'
    original = manifest.read_text()
    data = json.loads(original)
    data['workflow']['id'] = 'other'
    manifest.write_text(json.dumps(data))
    with pytest.raises(ValueError, match='same analysis type'):
        app.simulation_workspace('set-baseline', {'id': analysis['id'], 'run_id': saved['id']})
    manifest.write_text(original)
    app.simulation_workspace('set-baseline', {'id': analysis['id'], 'run_id': saved['id']})
    (root / saved['config_snapshot']).unlink()
    comparison = app.simulation_workspace('comparison', {'id': analysis['id']})['comparison']
    assert not comparison['available']
    assert 'unavailable' in comparison['message']


def test_plot_setting_updates_do_not_overwrite_another_view(archive_workspace, monkeypatch):
    from concurrent.futures import ThreadPoolExecutor
    import threading
    import time

    analysis = app.simulation_workspace('create', {'workflow_id': 'study'})['simulation']
    views = [app.simulation_workspace('add-visualization', {'id': analysis['id'], 'kind': 'signals'})['visualization']
             for _ in range(2)]
    original_read = Path.read_text

    def slow_metadata_read(path, *args, **kwargs):
        text = original_read(path, *args, **kwargs)
        if path.name == 'simulations.json':
            time.sleep(.03)
        return text

    monkeypatch.setattr(Path, 'read_text', slow_metadata_read)
    start = threading.Barrier(2)

    def update(index):
        start.wait(timeout=2)
        app.simulation_workspace('update-visualization', {'id': analysis['id'], 'child_id': views[index]['id'],
                                                         'settings': {'signals': [f'signal_{index}']}})

    with ThreadPoolExecutor(max_workers=2) as workers:
        list(workers.map(update, range(2)))
    saved = app.simulation_workspace()['simulations'][0]['visualizations']
    assert [view['settings']['signals'] for view in saved] == [['signal_0'], ['signal_1']]


@pytest.mark.parametrize('text', ['', 'incomplete', '[1, 2]'])
def test_comparison_rejects_incomplete_archived_inputs(archive_workspace, text):
    root, _ = archive_workspace
    analysis = app.simulation_workspace('create', {'workflow_id': 'study'})['simulation']
    snapshot = app.capture_workflow_inputs('study')
    snapshot['simulation'] = analysis
    saved = app.save_active_results('study', input_snapshot=snapshot)['saved']
    app.simulation_workspace('set-baseline', {'id': analysis['id'], 'run_id': saved['id']})
    (root / saved['config_snapshot']).write_text(text)
    comparison = app.simulation_workspace('comparison', {'id': analysis['id']})['comparison']
    assert not comparison['available']
    assert comparison['changes'] == []
    assert 'unavailable' in comparison['message']
