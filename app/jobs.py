from __future__ import annotations

import os
import signal
import subprocess
import sys
import threading
import time
from typing import Any
import uuid


class JobStore:
    def __init__(self, max_log_chars: int) -> None:
        self._max_log_chars = max_log_chars
        self._lock = threading.Lock()
        self._jobs: dict[str, dict[str, Any]] = {}
        self._processes: dict[str, subprocess.Popen[str]] = {}

    def create(self, action_id: str, label: str, argv: list[str]) -> dict[str, Any]:
        job_id = uuid.uuid4().hex[:10]
        now = time.time()
        job = {
            "id": job_id,
            "action_id": action_id,
            "label": label,
            "argv": argv,
            "status": "queued",
            "cancellable": True,
            "cancel_requested": False,
            "returncode": None,
            "started_at": None,
            "ended_at": None,
            "created_at": now,
            "log": "",
        }
        with self._lock:
            self._jobs[job_id] = job
        return job

    def append_log(self, job_id: str, text: str) -> None:
        if not text:
            return
        with self._lock:
            job = self._jobs[job_id]
            job["log"] = (job["log"] + text)[-self._max_log_chars :]

    def update(self, job_id: str, **values: Any) -> None:
        with self._lock:
            self._jobs[job_id].update(values)

    def get(self, job_id: str) -> dict[str, Any] | None:
        with self._lock:
            job = self._jobs.get(job_id)
            return dict(job) if job else None

    def list(self) -> list[dict[str, Any]]:
        with self._lock:
            return [
                dict(job)
                for job in sorted(
                    self._jobs.values(),
                    key=lambda item: float(item["created_at"]),
                    reverse=True,
                )
            ]

    def cancel(self, job_id: str) -> dict[str, Any]:
        with self._lock:
            job = self._jobs[job_id]
            if job["status"] not in {"queued", "running"} or job["cancel_requested"]:
                return dict(job)
            if not job["cancellable"]:
                raise ValueError("This run has finished computing and is saving its results.")
            process = self._processes.get(job_id)
            if process is not None:
                self._stop_process(process)
            job["cancel_requested"] = True
            job["log"] = (job["log"] + "\nCancellation requested.\n")[-self._max_log_chars:]
            return dict(job)

    def set_process(self, job_id: str, process: subprocess.Popen[str] | None) -> None:
        with self._lock:
            if process is None:
                self._processes.pop(job_id, None)
            else:
                self._processes[job_id] = process
                if self._jobs[job_id]["cancel_requested"]:
                    self._stop_process(process)

    def finish_execution(self, job_id: str) -> bool:
        with self._lock:
            job = self._jobs[job_id]
            job["cancellable"] = False
            return bool(job["cancel_requested"])

    @staticmethod
    def _stop_process(process: subprocess.Popen[str]) -> None:
        # Stop the whole simulation tree, including Modelica subprocesses.
        if sys.platform == "win32":
            if process.poll() is None:
                try:
                    subprocess.run(
                        ["taskkill", "/PID", str(process.pid), "/T", "/F"], check=True,
                        capture_output=True, creationflags=subprocess.CREATE_NO_WINDOW,
                    )
                except subprocess.CalledProcessError:
                    if process.poll() is None:
                        raise
        else:
            try:
                os.killpg(process.pid, signal.SIGKILL)
            except ProcessLookupError:
                pass
