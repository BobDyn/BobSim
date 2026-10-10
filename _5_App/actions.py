from __future__ import annotations

import os
from pathlib import Path
import subprocess
import sys
import threading
import time
from typing import Any, Iterable

from _5_App.contracts import ActionSpec, BuildTargetSpec, WorkflowSpec


ROOT = Path.cwd()
PYTHON = sys.executable
PYTHON_SUBPROCESS_ENCODING = "utf-8:replace"
JOBS: Any = None
ACTION_SPECS: dict[str, ActionSpec] = {}
WORKFLOWS: tuple[WorkflowSpec, ...] = ()
MODELICA_BUILD_TARGETS_BY_ACTION: dict[str, BuildTargetSpec] = {}
MODELICA_RUN_TARGETS_BY_ACTION: dict[str, BuildTargetSpec] = {}


def _path_list_value(value: str) -> list[str]:
    return [part for part in value.split(os.pathsep) if part.strip()]


def openmodelica_toolchain_payload() -> dict[str, Any]:
    return {}


def _apply_openmodelica_env_paths(
    _env: dict[str, str],
    *,
    omc_path: str | None,
    home: str | None,
    library: str | None,
) -> None:
    return None


def _sanitize_frozen_external_env(_env: dict[str, str]) -> None:
    return None


def action_available(_action: ActionSpec) -> bool:
    return True


def unavailable_action_reason(_action: ActionSpec) -> str:
    return ""


def _run_modelica_build_action(_action: ActionSpec, _target: BuildTargetSpec, _job_id: str) -> int:
    raise RuntimeError("Modelica build runner has not been connected")


def _modelica_build_missing_files(_target: BuildTargetSpec) -> list[str]:
    return []


def _workflow_by_id(_workflow_id: str) -> WorkflowSpec:
    raise KeyError(_workflow_id)


def capture_workflow_inputs(_workflow_id: str) -> dict[str, Any]:
    raise RuntimeError("Workflow input capture has not been connected")


def save_active_results(*_args: Any, **_kwargs: Any) -> dict[str, Any]:
    return {}


def _prepend_env_path(env: dict[str, str], key: str, paths: Iterable[str]) -> None:
    current = env.get(key, "")
    parts = [path for path in paths if path and Path(path).exists()]
    if current:
        parts.extend(_path_list_value(current))
    if parts:
        env[key] = os.pathsep.join(dict.fromkeys(parts))


def _action_argv(action: ActionSpec) -> tuple[str, ...]:
    if action.requires_external_toolchain and action.argv and action.argv[0] == "omc":
        omc_path = openmodelica_toolchain_payload().get("omc")
        if omc_path:
            return (str(omc_path), *action.argv[1:])
    return action.argv


def _apply_openmodelica_env(env: dict[str, str]) -> None:
    toolchain = openmodelica_toolchain_payload()
    _apply_openmodelica_env_paths(
        env,
        omc_path=toolchain.get("omc"),
        home=toolchain.get("openmodelica_home"),
        library=toolchain.get("openmodelica_library"),
    )


def _apply_python_stdio_env(env: dict[str, str]) -> None:
    env["PYTHONUTF8"] = "1"
    env["PYTHONIOENCODING"] = PYTHON_SUBPROCESS_ENCODING


def _subprocess_creation_flags() -> int:
    if sys.platform != "win32":
        return 0
    return int(getattr(subprocess, "CREATE_NO_WINDOW", 0))


def _run_subprocess_action(action: ActionSpec, job_id: str) -> int:
    env = os.environ.copy()
    env.update(action.env)
    env.setdefault("PYTHONUNBUFFERED", "1")
    _apply_python_stdio_env(env)
    argv = _action_argv(action)
    if action.requires_external_toolchain and argv and Path(argv[0]).resolve() != Path(PYTHON).resolve():
        _sanitize_frozen_external_env(env)
    if action.requires_external_toolchain:
        _apply_openmodelica_env(env)
    JOBS.append_log(job_id, f"\n$ {' '.join(argv)}\n")
    with subprocess.Popen(
        argv,
        cwd=ROOT,
        env=env,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        encoding="utf-8",
        errors="replace",
        bufsize=1,
        creationflags=_subprocess_creation_flags(),
    ) as process:
        assert process.stdout is not None
        for line in process.stdout:
            JOBS.append_log(job_id, line)
        return process.wait()


def _run_action_process(action: ActionSpec, job_id: str) -> int:
    if not action_available(action):
        reason = unavailable_action_reason(action)
        JOBS.append_log(job_id, f"{action.label} unavailable: {reason}\n")
        return 2
    target = MODELICA_BUILD_TARGETS_BY_ACTION.get(action.id)
    if target:
        return _run_modelica_build_action(action, target, job_id)
    run_target = MODELICA_RUN_TARGETS_BY_ACTION.get(action.id)
    if run_target:
        missing = _modelica_build_missing_files(run_target)
        if missing:
            JOBS.append_log(
                job_id,
                f"{run_target.label} is not built yet. Run {run_target.label} build first. "
                f"Missing in {run_target.build_dir}: {', '.join(missing)}.\n",
            )
            return 2
    return _run_subprocess_action(action, job_id)


def run_actions_job(actions: tuple[ActionSpec, ...], job_id: str, workflow_id: str | None = None) -> None:
    started_at = time.time()
    JOBS.update(job_id, status="running", started_at=started_at)
    try:
        input_snapshot = capture_workflow_inputs(workflow_id) if workflow_id else None
        returncode = 0
        for action in actions:
            returncode = _run_action_process(action, job_id)
            if returncode != 0:
                break
        review = None
        if returncode == 0 and workflow_id:
            workflow = _workflow_by_id(workflow_id)
            JOBS.append_log(job_id, "\nPackaging review outputs...\n")
            try:
                review_payload = save_active_results(
                    workflow_id,
                    f"{workflow.label} review",
                    since=started_at,
                    job_id=job_id,
                    input_snapshot=input_snapshot,
                )
                review = review_payload.get("saved")
                JOBS.append_log(job_id, f"Review package saved: {review.get('label') if review else workflow.label}\n")
            except Exception as exc:
                JOBS.append_log(job_id, f"Review package failed: {type(exc).__name__}: {exc}\n")
                returncode = -1
        JOBS.update(
            job_id,
            status="succeeded" if returncode == 0 else "failed",
            returncode=returncode,
            review=review,
            ended_at=time.time(),
        )
    except Exception as exc:  # pragma: no cover - defensive job boundary
        JOBS.append_log(job_id, f"\n{type(exc).__name__}: {exc}\n")
        JOBS.update(job_id, status="failed", returncode=-1, ended_at=time.time())


def start_job(action_id: str) -> dict[str, Any]:
    if action_id not in ACTION_SPECS:
        raise KeyError(action_id)
    action = ACTION_SPECS[action_id]
    if not action_available(action):
        raise RuntimeError(unavailable_action_reason(action))
    job = JOBS.create(action.id, action.label, list(action.argv))
    thread = threading.Thread(target=run_actions_job, args=((action,), job["id"]), daemon=True)
    thread.start()
    return job


def start_workflow(workflow_id: str) -> dict[str, Any]:
    workflows = {workflow.id: workflow for workflow in WORKFLOWS}
    if workflow_id not in workflows:
        raise KeyError(workflow_id)
    workflow = workflows[workflow_id]
    actions = tuple(ACTION_SPECS[action_id] for action_id in workflow.actions)
    unavailable = [action for action in actions if not action_available(action)]
    if unavailable:
        raise RuntimeError(unavailable_action_reason(unavailable[0]))
    label = f"Run {workflow.label}"
    argv = [action.label for action in actions]
    job = JOBS.create(f"workflow:{workflow.id}", label, argv)
    thread = threading.Thread(target=run_actions_job, args=(actions, job["id"], workflow.id), daemon=True)
    thread.start()
    return job

