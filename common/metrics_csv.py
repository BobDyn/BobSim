"""Read a report metrics CSV with columns metric, value and an optional status."""

from __future__ import annotations

import csv
from pathlib import Path

OK_ONLY = frozenset({"ok"})


def read_metric_status(path: str | Path) -> dict[str, tuple[float, str]]:
    """Value and status by metric. A file without a status column gives status 'unknown'."""
    out: dict[str, tuple[float, str]] = {}
    with Path(path).open(newline="", encoding="utf-8") as f:
        for row in csv.DictReader(f):
            metric = row.get("metric")
            if not metric:
                continue
            try:
                value = float(row.get("value") or "nan")
            except ValueError:
                value = float("nan")
            out[metric] = (value, (row.get("status") or "unknown").strip())
    return out


def read_metrics(path: str | Path, accept: frozenset[str] = OK_ONLY) -> dict[str, float]:
    """Value by metric. A value whose status is not in ``accept`` reads as NaN."""
    return {
        metric: value if status in accept else float("nan")
        for metric, (value, status) in read_metric_status(path).items()
    }
