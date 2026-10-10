from __future__ import annotations

import threading
import time
from typing import Any
import uuid


class JobStore:
    def __init__(self, max_log_chars: int) -> None:
        self._max_log_chars = max_log_chars
        self._lock = threading.Lock()
        self._jobs: dict[str, dict[str, Any]] = {}

    def create(self, action_id: str, label: str, argv: list[str]) -> dict[str, Any]:
        job_id = uuid.uuid4().hex[:10]
        now = time.time()
        job = {
            "id": job_id,
            "action_id": action_id,
            "label": label,
            "argv": argv,
            "status": "queued",
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
