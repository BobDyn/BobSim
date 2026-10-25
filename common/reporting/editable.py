"""Portable plot inputs and validation shared by reports and their editor."""
from __future__ import annotations

import json
import math
from pathlib import Path
from typing import Any

import numpy as np

LAYOUT_SIZES = {"single": 1, "dual": 2, "triple": 3, "quad": 4}


def json_values(value: Any) -> Any:
    """Convert numerical report data into portable JSON values."""
    if isinstance(value, dict):
        return {str(k): json_values(v) for k, v in value.items()}
    if isinstance(value, (list, tuple, np.ndarray)):
        return [json_values(v) for v in value]
    if isinstance(value, np.generic):
        return json_values(value.item())
    if isinstance(value, float) and not math.isfinite(value):
        return None
    if isinstance(value, Path):
        return value.as_posix()
    return value


def save_report_data(path: Path, config: dict, result: dict) -> None:
    """Save the exact processed inputs needed to render an existing report."""
    result.setdefault("series", {})
    cases = result.get("cases", [])
    if cases:
        for key, value in cases[-1].items():
            if not key.startswith("_") and isinstance(value, (list, np.ndarray)):
                result["series"]["raw:" + key] = value
    data = {key: result[key] for key in ("series", "summary", "velocity_summaries", "setup") if key in result}
    target = path.with_suffix(".report-data.json")
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_text(json.dumps(json_values({"config": config, "result": data}), allow_nan=False), encoding="utf-8")


def validate_plots(plots: Any) -> dict:
    """Validate editable page structure before saving or rendering it."""
    if not isinstance(plots, dict) or len(plots) > 100:
        raise ValueError("Provide a mapping of at most 100 plot pages.")
    for name, page in plots.items():
        if not isinstance(name, str) or not name or not isinstance(page, dict):
            raise ValueError("Each page needs a name and plot settings.")
        size = LAYOUT_SIZES.get(page.get("layout", "single"))
        if not size:
            raise ValueError(f"{name}: choose single, dual, triple, or quad.")
        subs = page.get("subplots", [page])
        if not isinstance(subs, list) or len(subs) != size:
            raise ValueError(f"{name}: this layout needs {size} subplot(s).")
        for sub in subs:
            if not isinstance(sub, dict):
                raise ValueError(f"{name}: invalid subplot.")
            overlays = sub.get("overlay", [])
            if isinstance(overlays, dict):
                overlays = [overlays]
            if not isinstance(overlays, list) or len(overlays) > 30:
                raise ValueError(f"{name}: invalid overlays.")
            for curve in [sub, *overlays]:
                if not isinstance(curve, dict):
                    raise ValueError(f"{name}: invalid curve.")
                for axis in ("x", "y"):
                    cfg = curve.get(axis)
                    if not isinstance(cfg, dict) or not isinstance(cfg.get("key"), str) or not cfg["key"]:
                        raise ValueError(f"{name}: select an {axis.upper()} signal for every curve.")
                    for key in ("scale", "offset"):
                        if key in cfg and (not isinstance(cfg[key], (int, float)) or not math.isfinite(cfg[key])):
                            raise ValueError(f"{name}: {key} must be finite.")
            for cfg in (page, sub):
                for axis in ("x", "y"):
                    if cfg.get(axis + "scale", "linear") not in ("linear", "log", "symlog"):
                        raise ValueError(f"{name}: invalid axis scale.")
                    limits = cfg.get(axis + "lim")
                    if limits is not None and (not isinstance(limits, list) or len(limits) != 2
                            or any(not isinstance(v, (int, float)) or not math.isfinite(v) for v in limits)
                            or limits[0] >= limits[1]):
                        raise ValueError(f"{name}: axis limits must be two increasing numbers.")
    return plots


def apply_page_options(fig: Any, page: dict) -> None:
    """Apply common editable axes options consistently to every layout."""
    subs = page.get("subplots", [page])
    for ax, sub in zip(fig.axes, subs):
        for axis in ("x", "y"):
            limits = sub.get(axis + "lim", page.get(axis + "lim"))
            if limits is not None:
                getattr(ax, "set_" + axis + "lim")(*limits)
        ax.grid(sub.get("grid", page.get("grid", True)))
        if not sub.get("legend", page.get("legend", True)) and ax.get_legend() is not None:
            ax.get_legend().remove()
    for axis in ("x", "y"):
        if page.get("share" + axis) and len(fig.axes) > 1:
            limits = [getattr(ax, "get_" + axis + "lim")() for ax in fig.axes]
            shared = (min(v[0] for v in limits), max(v[1] for v in limits))
            for ax in fig.axes:
                getattr(ax, "set_" + axis + "lim")(*shared)
