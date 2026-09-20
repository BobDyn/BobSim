"""The run a scene is drawn from: its visual config and the signals it names.

Numpy and YAML only. Rendering lives in the browser now -- ``_5_App/visual.py``
turns this into a payload and ``_5_App/static/visual.js`` draws it -- so nothing
here may import a rendering stack. That is what lets the whole pipeline be
tested in CI, which never had Qt or VTK installed.
"""

from __future__ import annotations

import csv
from pathlib import Path
from typing import Any

import numpy as np
import yaml


class VisualConfigError(ValueError):
    """Raised when the YAML config and the data file do not line up."""


def _load_signal_file(path: Path) -> dict[str, np.ndarray]:
    suffix = path.suffix.lower()
    if suffix == ".npz":
        raw = np.load(path)
        return {k: np.asarray(raw[k], dtype=float).ravel() for k in raw.files}
    if suffix == ".csv":
        with open(path, "r", newline="", encoding="utf-8") as handle:
            rows = list(csv.DictReader(handle))
        if not rows:
            raise VisualConfigError(f"{path} is empty")
        return {
            col: np.array([float(r[col]) for r in rows], dtype=float)
            for col in rows[0]
            if col
        }
    raise VisualConfigError(f"Unsupported data file type {suffix!r}; use .npz or .csv")


class SimData:
    """Visual YAML config plus the signal arrays it references."""

    def __init__(self, yml_path: str | Path, data_path: str | Path) -> None:
        self.yml_path = Path(yml_path)
        self.data_path = Path(data_path)

        with open(self.yml_path, "r", encoding="utf-8") as handle:
            cfg = yaml.safe_load(handle)
        if not isinstance(cfg, dict):
            raise VisualConfigError(f"{self.yml_path} does not contain a YAML mapping")
        self.cfg: dict[str, Any] = cfg

        raw = _load_signal_file(self.data_path)
        if "time" not in raw:
            raise VisualConfigError(f"{self.data_path} has no 'time' column")

        # Stride once, here, so points, vectors, plots and time share an index.
        # The old viewer strided geometry but not time, which desynchronised the
        # scene from the timeline whenever input_stride was greater than 1.
        stride = max(1, int(self.render_cfg.get("input_stride", 1)))
        self.input_stride = stride
        self.signals: dict[str, np.ndarray] = (
            raw if stride == 1 else {k: v[::stride] for k, v in raw.items()}
        )

        self.time: np.ndarray = np.asarray(self.signals["time"], dtype=float)
        if self.time.size < 2:
            raise VisualConfigError(
                f"{self.data_path} has {self.time.size} sample(s); need at least 2"
            )
        self.n_frames: int = int(self.time.size)
        self.signal_names: list[str] = sorted(k for k in self.signals if k != "time")

        missing = sorted(self.required_signals() - set(self.signals))
        if missing:
            shown = "\n  ".join(missing[:12])
            more = f"\n  ... and {len(missing) - 12} more" if len(missing) > 12 else ""
            raise VisualConfigError(
                f"{self.yml_path.name} references signals that are not in "
                f"{self.data_path.name}:\n  {shown}{more}"
            )

    # -- config accessors ---------------------------------------------------
    @property
    def geometry_cfg(self) -> dict[str, Any]:
        return dict(self.cfg.get("geometry") or {})

    @property
    def style_cfg(self) -> dict[str, Any]:
        return dict(self.cfg.get("style") or {})

    @property
    def render_cfg(self) -> dict[str, Any]:
        return dict(self.cfg.get("render") or {})

    @property
    def camera_cfg(self) -> dict[str, Any]:
        return dict(self.cfg.get("camera") or {})

    @property
    def ground_cfg(self) -> dict[str, Any]:
        return dict(self.cfg.get("ground") or {})

    @property
    def plots_cfg(self) -> list[dict[str, Any]]:
        plots = self.cfg.get("plots") or []
        return [p for p in plots if isinstance(p, dict)]

    @property
    def tire_forces_cfg(self) -> dict[str, Any]:
        return dict(self.cfg.get("tire_forces") or {})

    @property
    def metrics_path(self) -> Path | None:
        """The run's metrics CSV, resolved against the config's folder, if it exists."""
        raw = (self.cfg.get("metrics") or {}).get("path")
        if not raw:
            return None
        path = Path(str(raw))
        if not path.is_absolute():
            path = self.yml_path.parent / path
        return path if path.is_file() else None

    @property
    def point_names(self) -> list[str]:
        return [str(k) for k in (self.geometry_cfg.get("points") or {})]

    @property
    def duration(self) -> float:
        return float(self.time[-1] - self.time[0])

    def required_signals(self) -> set[str]:
        """Every signal name the config expects to find in the data file."""
        geom = self.geometry_cfg
        needed: set[str] = set()

        for cols in (geom.get("points") or {}).values():
            needed.update(str(c) for c in cols)

        for tire in (geom.get("tires") or {}).values():
            needed.update(str(c) for c in tire.get("x", []))
            needed.update(str(c) for c in tire.get("y", []))

        for group in (geom.get("vectors") or {}).values():
            for vcfg in group.values():
                needed.update(
                    str(c) for c in vcfg.get("direction", []) if isinstance(c, str)
                )

        for plot in self.plots_cfg:
            for key in ("x", "y"):
                name = plot.get(key)
                if isinstance(name, str):
                    needed.add(name)

        for load in ((self.ground_cfg.get("loads") or {}).get("corners") or {}).values():
            needed.add(str(load["signal"]))

        for tire in (self.tire_forces_cfg.get("corners") or {}).values():
            needed.update(str(tire[key]) for key in ("fx", "fy", "fz", "gamma") if tire.get(key))

        return needed

    def get_signal(self, name: str) -> np.ndarray:
        return self.signals[name]

    def frame_at(self, sim_time: float) -> int:
        """Index of the last sample at or before ``sim_time``."""
        idx = int(np.searchsorted(self.time, sim_time, side="right") - 1)
        return max(0, min(idx, self.n_frames - 1))


def resolve_load_reference(load: np.ndarray) -> float:
    """The load a footprint's ring stands for: the median over the run.

    On the rig that is the static corner load exactly. A manoeuvre's first
    sample is not settled - VehicleSim starts 6-10% light - but its median is
    the load the tire carries driving straight.
    """
    arr = np.asarray(load, dtype=float)
    value = float(np.nanmedian(arr)) if arr.size else 0.0
    if not np.isfinite(value) or value <= 0.0:
        peak = float(np.nanmax(np.abs(arr))) if arr.size else 0.0
        value = peak if peak > 0.0 else 1.0
    return value

def load_disc_radius(ratio: float | np.ndarray, reference_radius: float) -> Any:
    """Footprint radius for a load ``ratio``; *area* scales with load, which the eye reads linearly."""
    return float(reference_radius) * np.sqrt(np.clip(ratio, 0.0, None))
