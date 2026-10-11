"""Small console helpers shared by OptSim workflows."""

from __future__ import annotations

import time


def stage(n: int, total: int, name: str) -> None:
    print(f"\n{'=' * 60}")
    print(f"  {n} / {total}  -  {name}")
    print(f"{'=' * 60}\n")


def elapsed(t0: float) -> str:
    return f"{time.time() - t0:.1f}s"
