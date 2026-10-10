"""Exclusive access to the app's shared active inputs and build directories."""
from __future__ import annotations

import threading

LOCK = threading.Lock()
BUSY_MESSAGE = ("A simulation is using the active workspace. "
                "Wait for it to finish before starting another job or editing inputs.")


def reserve() -> None:
    if not LOCK.acquire(blocking=False):
        raise RuntimeError(BUSY_MESSAGE)
