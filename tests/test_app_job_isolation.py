from __future__ import annotations

import json
import threading
from http import HTTPStatus
from pathlib import Path

import pytest

from _5_App import actions, data_services, execution, server
from _5_App.contracts import ActionSpec, WorkflowSpec
from _5_App.jobs import JobStore


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
