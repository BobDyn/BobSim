from __future__ import annotations

import json
import threading
from http import HTTPStatus
from pathlib import Path

import pytest

from app import actions, data_services, execution, server
from app.contracts import ActionSpec, WorkflowSpec
from app.jobs import JobStore


def test_job_reserves_workspace_until_packaging_finishes(monkeypatch):
    store = JobStore(10000)
    action = ActionSpec('simulate', 'Simulate', ('python', 'sim.py'))
    workflow = WorkflowSpec('study', 'standard', 'Study', None, ('simulate',))
    entered = threading.Event()
    release = threading.Event()
    threads = []
    real_thread = threading.Thread

    def tracked_thread(**kwargs):
        thread = real_thread(**kwargs)
        threads.append(thread)
        return thread

    def package(*args, **kwargs):
        entered.set()
        assert release.wait(5)
        raise ValueError('packaging failure')

    monkeypatch.setattr(actions, 'JOBS', store)
    monkeypatch.setattr(actions, 'ACTION_SPECS', {'simulate': action})
    monkeypatch.setattr(actions, 'WORKFLOWS', (workflow,))
    monkeypatch.setattr(actions, '_workflow_by_id', lambda _: workflow)
    # Input capture is supplied by the independent archive-provenance fix.
    monkeypatch.setattr(actions, 'capture_workflow_inputs', lambda _: {}, raising=False)
    monkeypatch.setattr(actions, '_run_action_process', lambda *_: 0)
    monkeypatch.setattr(actions, 'save_active_results', package)
    monkeypatch.setattr(actions.threading, 'Thread', tracked_thread)
    job = actions.start_workflow('study')
    try:
        assert entered.wait(5)
        with pytest.raises(RuntimeError, match='active workspace'):
            actions.start_job('simulate')
        assert len(store.list()) == 1
    finally:
        release.set()
        for thread in threads:
            thread.join(5)
    assert not execution.LOCK.locked()
    assert store.get(job['id'])['status'] == 'failed'


def test_thread_start_failure_releases_workspace(monkeypatch):
    monkeypatch.setattr(actions, 'JOBS', JobStore(1000))
    def fail(_):
        raise RuntimeError('thread failed')

    monkeypatch.setattr(actions.threading.Thread, 'start', fail)
    with pytest.raises(RuntimeError, match='thread failed'):
        actions._launch_job((), 'a', 'A', [])
    assert not execution.LOCK.locked()


def test_input_edit_is_rejected_while_job_owns_workspace():
    handler = object.__new__(server.BobSimHandler)
    handler.path = '/api/configs/vehicle'
    responses = []
    handled = []
    handler._send_error = lambda *args: responses.append(args)
    handler._handle_post = lambda: handled.append(True)
    execution.reserve()
    try:
        handler.do_POST()
        assert responses[0][0] == HTTPStatus.CONFLICT
        assert not handled
        handler.path = '/api/results/series'
        handler.do_POST()
        assert handled == [True]
    finally:
        execution.LOCK.release()


def test_signal_archive_selects_job_owner_not_timestamp(tmp_path: Path, monkeypatch):
    workflow = WorkflowSpec('study', 'standard', 'Study', None, ())
    monkeypatch.setattr(data_services, '_workflow_run_roots', lambda _: (tmp_path,))
    for name, owner in [('ours', 'job-a'), ('other', 'job-b'), ('legacy', None)]:
        path = tmp_path / f'run_{name}'
        path.mkdir()
        (path / 'manifest.json').write_text(json.dumps({'job_id': owner, 'workflow_id': 'study'}))
    assert data_services._workflow_run_dirs(workflow, job_id='job-a') == [tmp_path / 'run_ours']
    unrelated = WorkflowSpec('different', 'standard', 'Different', None, ())
    assert data_services._workflow_run_dirs(unrelated) == []


@pytest.mark.parametrize('query,run_id', [('id=analysis', None), ('id=analysis&run_id=run', 'run')])
def test_comparison_can_be_read_during_a_job(monkeypatch, query, run_id):
    handler = object.__new__(server.BobSimHandler)
    handler.path = '/api/simulations/comparison?vehicle_key=original&' + query
    responses = []
    monkeypatch.setattr(server, 'sync_runtime', lambda: None)
    monkeypatch.setattr(server, 'simulation_workspace', lambda action, payload: {'action': action, **payload})
    handler._send_json = responses.append
    execution.reserve()
    try:
        handler.do_GET()
    finally:
        execution.LOCK.release()
    assert responses == [{'action': 'comparison', 'id': 'analysis', 'run_id': run_id, 'vehicle_key': 'original'}]


def test_plot_settings_route_only_updates_visualizations_during_a_job(monkeypatch):
    handler = object.__new__(server.BobSimHandler)
    handler.path = '/api/simulations/visualization-settings'
    responses = []
    monkeypatch.setattr(server, 'sync_runtime', lambda: None)
    monkeypatch.setattr(server, 'simulation_workspace', lambda action, payload: {'action': action})
    handler._read_json_body = lambda: {'action': 'prepare-run', 'id': 'analysis'}
    handler._send_json = responses.append
    execution.reserve()
    try:
        handler.do_POST()
    finally:
        execution.LOCK.release()
    assert responses == [{'action': 'update-visualization'}]


def test_cancel_route_is_available_while_job_owns_workspace(monkeypatch):
    store = JobStore(1000)
    job = store.create('simulate', 'Simulate', [])
    monkeypatch.setattr(server, 'JOBS', store)
    monkeypatch.setattr(server, 'sync_runtime', lambda: None)
    handler = object.__new__(server.BobSimHandler)
    handler.path = f"/api/jobs/{job['id']}/cancel"
    handler._read_json_body = lambda: {}
    responses = []
    handler._send_json = lambda payload: responses.append(payload)
    execution.reserve()
    try:
        handler.do_POST()
        assert responses[0]['cancel_requested']
        assert execution.LOCK.locked()
    finally:
        execution.LOCK.release()


def test_cancel_before_run_skips_actions_and_archive(monkeypatch):
    store = JobStore(1000)
    monkeypatch.setattr(actions, 'JOBS', store)
    monkeypatch.setattr(actions, 'capture_workflow_inputs', lambda _: {})
    monkeypatch.setattr(actions, '_run_action_process', lambda *_: pytest.fail('cancelled action started'))
    monkeypatch.setattr(actions, 'save_active_results', lambda *_args, **_kwargs: pytest.fail('cancelled run saved'))
    job = store.create('simulate', 'Simulate', [])
    store.cancel(job['id'])
    actions.run_actions_job((ActionSpec('simulate', 'Simulate', ('unused',)),), job['id'], 'study')
    assert store.get(job['id'])['status'] == 'cancelled'
    assert store.cancel(job['id'])['status'] == 'cancelled'


def test_cancel_does_not_interrupt_result_packaging():
    store = JobStore(1000)
    job = store.create('simulate', 'Simulate', [])
    store.update(job['id'], status='running')
    assert not store.finish_execution(job['id'])
    with pytest.raises(ValueError, match='saving its results'):
        store.cancel(job['id'])


def test_cancel_stops_simulation_and_child_process(tmp_path, monkeypatch):
    import sys
    import time

    store = JobStore(10000)
    marker = tmp_path / 'child-finished'
    child = f"import time; from pathlib import Path; time.sleep(1); Path({str(marker)!r}).touch()"
    script = (
        f"import subprocess, sys; child = subprocess.Popen([sys.executable, '-c', {child!r}]); "
        "print('ready', flush=True); child.wait()"
    )
    action = ActionSpec('simulate', 'Simulate', (sys.executable, '-c', script))
    monkeypatch.setattr(actions, 'JOBS', store)
    monkeypatch.setattr(actions, 'ROOT', tmp_path)
    monkeypatch.setattr(actions, 'ACTION_SPECS', {'simulate': action})
    monkeypatch.setattr(actions, 'WORKFLOWS', ())
    monkeypatch.setattr(actions, 'action_available', lambda _: True)
    job = actions.start_job('simulate')
    try:
        deadline = time.monotonic() + 5
        while 'ready\n' not in store.get(job['id'])['log']:
            assert time.monotonic() < deadline
            time.sleep(.01)
        store.cancel(job['id'])
        while execution.LOCK.locked():
            assert time.monotonic() < deadline
            time.sleep(.01)
        result = store.get(job['id'])
        assert result['status'] == 'cancelled'
        assert result['returncode'] != 0
        time.sleep(1.1)
        assert not marker.exists(), 'simulation child survived cancellation'
    finally:
        store.cancel(job['id'])


def test_cancel_requested_before_process_registration(monkeypatch):
    store = JobStore(1000)
    job = store.create('simulate', 'Simulate', [])
    store.cancel(job['id'])
    stopped = []
    monkeypatch.setattr(store, '_stop_process', stopped.append)
    process = object()
    store.set_process(job['id'], process)
    assert stopped == [process]
    store.set_process(job['id'], None)


def test_windows_cancel_tolerates_process_exit_race(monkeypatch):
    import subprocess
    from types import SimpleNamespace
    from app import jobs

    monkeypatch.setattr(jobs, 'sys', SimpleNamespace(platform='win32'))
    monkeypatch.setattr(jobs.subprocess, 'CREATE_NO_WINDOW', 0, raising=False)
    states = iter([None, 0])
    process = SimpleNamespace(pid=123, poll=lambda: next(states))

    def exited(argv, **_kwargs):
        assert argv == ['taskkill', '/PID', '123', '/T', '/F']
        raise subprocess.CalledProcessError(128, argv)

    monkeypatch.setattr(jobs.subprocess, 'run', exited)
    JobStore._stop_process(process)
