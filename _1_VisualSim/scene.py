"""Shared scene model for BobVis.

Everything in here is Qt-free so the same geometry, camera and styling code
backs both the interactive viewer (:mod:`_1_VisualSim.viewer`) and the
off-screen video exporter (:mod:`_1_VisualSim.exporter`).

Two objects matter:

``SimData``
    Parsed visual YAML plus the signal arrays it refers to (``.npz`` or
    ``.csv``). Signals are strided once, at load, so every consumer indexes
    the same rows.

``VisualScene``
    Owns the PyVista actors for one ``SimData`` and moves them to an arbitrary
    simulation time. Time is continuous: actors are interpolated between
    samples, so playback speed is decoupled from the solver's output grid.
"""

from __future__ import annotations

import csv
import os
import shutil
import subprocess
import time
from dataclasses import dataclass, field, replace
from pathlib import Path
from typing import Any, Callable, Iterable, Literal, Sequence

import numpy as np
import pyvista as pv
import vtk
import yaml
from matplotlib import colormaps

from _1_VisualSim.navigation import CameraPose
from _1_VisualSim.tire_state import axle_load_transfer


# ---------------------------------------------------------------------------
# Palette
#
# Lives here rather than in the viewer so exported video matches the window.
# One palette, deliberately: a viewer is judged on whether the geometry reads
# clearly, and link colours come from each visual template's own style block.
# A second background scheme only gives those template colours a second set of
# contrast ratios to fail at.
#
# The accent is BobDocs' brand blue, darkened enough to stay legible as text
# and hairlines on a light ground.
# ---------------------------------------------------------------------------

@dataclass(frozen=True)
class Palette:
    name: str
    background_top: str
    background_bottom: str
    ground: str
    grid: str
    text: str
    accent: str
    grid_major: str = "#96a1ad"


LIGHT = Palette(
    name="light",
    background_top="#f5f7f9",
    background_bottom="#dde3e9",
    ground="#e9edf1",
    grid="#cdd4dc",
    text="#1c2430",
    accent="#2b7fd4",
)

PALETTES: dict[str, Palette] = {LIGHT.name: LIGHT}


# ---------------------------------------------------------------------------
# Linear algebra helpers
# ---------------------------------------------------------------------------

def safe_normalize(v: np.ndarray, fallback: np.ndarray | None = None) -> np.ndarray:
    """Unit vector, or ``fallback`` (default +x) when ``v`` is degenerate."""
    arr = np.asarray(v, dtype=float)
    if fallback is None:
        fallback = np.array([1.0, 0.0, 0.0])
    n = float(np.linalg.norm(arr))
    return arr / n if n >= 1e-8 else np.asarray(fallback, dtype=float).copy()


def frame_from_x(x_axis: np.ndarray) -> np.ndarray:
    """Right-handed rotation matrix whose first column is ``x_axis``."""
    x = safe_normalize(x_axis)
    ref = np.array([0.0, 0.0, 1.0])
    if abs(float(np.dot(x, ref))) > 0.95:
        ref = np.array([0.0, 1.0, 0.0])
    y = safe_normalize(np.cross(ref, x), fallback=np.array([0.0, 1.0, 0.0]))
    z = safe_normalize(np.cross(x, y), fallback=np.array([0.0, 0.0, 1.0]))
    return np.column_stack((x, y, z))


def link_transform(p1: np.ndarray, p2: np.ndarray) -> np.ndarray:
    """Place the unit x-aligned cylinder so it spans ``p1`` to ``p2``."""
    a = np.asarray(p1, dtype=float)
    b = np.asarray(p2, dtype=float)
    d = b - a
    length = float(np.linalg.norm(d))
    T = np.eye(4)
    if length < 1e-10:
        T[:3, 3] = a
        return T
    T[:3, :3] = frame_from_x(d) @ np.diag([length, 1.0, 1.0])
    T[:3, 3] = 0.5 * (a + b)
    return T


def _to_vtk_matrix(mat: Any, T: np.ndarray) -> None:
    for i in range(4):
        for j in range(4):
            mat.SetElement(i, j, float(T[i, j]))


# ---------------------------------------------------------------------------
# Ground helpers
#
# Pure functions, so the arithmetic behind the ground layers is testable
# without a GL context.
# ---------------------------------------------------------------------------

def grid_lines(extent: float, pitch: float, skip_pitch: float | None = None) -> pv.PolyData:
    """Segments of a square grid on z = 0, centred on the origin.

    ``skip_pitch`` drops lines that fall on its multiples, so the minor grid is
    not drawn underneath the major one.
    """
    half = 0.5 * float(extent)
    count = int(round(float(extent) / float(pitch)))
    ticks = -half + float(pitch) * np.arange(count + 1)
    if skip_pitch:
        ratio = ticks / float(skip_pitch)
        ticks = ticks[np.abs(ratio - np.round(ratio)) > 1e-6]

    zeros = np.zeros_like(ticks)
    lo, hi = np.full_like(ticks, -half), np.full_like(ticks, half)
    starts = np.concatenate([np.column_stack([ticks, lo, zeros]),
                             np.column_stack([lo, ticks, zeros])])
    ends = np.concatenate([np.column_stack([ticks, hi, zeros]),
                           np.column_stack([hi, ticks, zeros])])

    points = np.empty((2 * len(starts), 3))
    points[0::2], points[1::2] = starts, ends
    index = np.arange(len(starts))
    lines = np.column_stack([np.full_like(index, 2), 2 * index, 2 * index + 1]).ravel()
    return pv.PolyData(points, lines=lines)


def polyline(points: np.ndarray) -> pv.PolyData:
    """One open polyline through ``points``."""
    pts = np.asarray(points, dtype=float).reshape(-1, 3)
    if len(pts) < 2:
        # VTK draws nothing for fewer than two points; a zero-length segment is harmless.
        pts = np.vstack([pts, pts]) if len(pts) else np.zeros((2, 3))
    return pv.PolyData(pts, lines=np.concatenate(([len(pts)], np.arange(len(pts)))))


def trail_indices(time: np.ndarray, i0: int, history: float, stride: int = 1) -> np.ndarray:
    """Sample indices covering the ``history`` seconds that end at sample ``i0``.

    Indices sit on a fixed global grid of ``stride`` so a decimated trail does
    not crawl as playback advances; ``i0`` itself is always included.
    """
    stride = max(1, int(stride))
    first = int(np.searchsorted(time, float(time[i0]) - float(history), side="left"))
    first = min(-(-first // stride) * stride, i0)
    idx = np.arange(first, i0 + 1, stride)
    if idx.size == 0 or idx[-1] != i0:
        idx = np.append(idx, i0)
    return idx


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


# Looked up once: matplotlib hands back a fresh copy on every `colormaps[...]`.
_LOAD_CMAP = colormaps["coolwarm"]


def load_color(ratio: float) -> tuple[float, float, float]:
    """Blue when unloaded, neutral at the reference load, red at twice it."""
    rgba = _LOAD_CMAP(float(np.clip(0.5 * ratio, 0.0, 1.0)))
    return float(rgba[0]), float(rgba[1]), float(rgba[2])


# ---------------------------------------------------------------------------
# Data
# ---------------------------------------------------------------------------

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


# ---------------------------------------------------------------------------
# Camera / scene options
# ---------------------------------------------------------------------------

FOLLOW = "follow"
FREE = "free"

AntiAliasing = Literal["ssaa", "msaa", "fxaa"]


@dataclass
class CameraOffset:
    """A camera pose expressed relative to the vehicle frame."""

    position: tuple[float, float, float]
    focal: tuple[float, float, float]
    up: tuple[float, float, float]
    view_angle: float = 30.0
    parallel_projection: bool = False
    parallel_scale: float = 1.0


@dataclass
class SceneOptions:
    """Everything the viewer can toggle without rebuilding the scene."""

    palette: Palette = LIGHT
    show_ground: bool = True
    show_tires: bool = True
    show_vectors: bool = True
    show_joints: bool = True
    show_tracks: bool = True
    show_loads: bool = True
    show_orientation_axes: bool = True
    tire_opacity: float = 0.45
    extra: dict[str, Any] = field(default_factory=dict)

    def copy_with(self, **changes: Any) -> "SceneOptions":
        return replace(self, **{"extra": dict(self.extra), **changes})


# ---------------------------------------------------------------------------
# Scene
# ---------------------------------------------------------------------------

class VisualScene:
    """PyVista actors for one :class:`SimData`, movable to any simulation time."""

    GROUND_EXTENT = 200.0
    GRID_MINOR = 1.0
    GRID_MAJOR = 5.0
    TRACK_MAX_POINTS = 600
    # Heights above the road for the layers drawn on it. Spaced far enough
    # apart to survive depth-buffer precision with the camera metres away.
    GRID_Z = 1e-3
    TRACK_Z = 6e-3
    LOAD_Z = 9e-3
    RING_Z = 1.2e-2

    def __init__(
        self,
        data: SimData,
        plotter: Any,
        options: SceneOptions | None = None,
    ) -> None:
        self.data = data
        self.plotter = plotter
        self.options = options or SceneOptions()

        self._points: dict[str, np.ndarray] = {}
        self._joint_actors: dict[str, Any] = {}
        self._link_actors: list[dict[str, Any]] = []
        self._tire_actors: list[dict[str, Any]] = []
        self._vector_actors: list[dict[str, Any]] = []
        self._ground_actors: list[Any] = []
        self._track_actors: list[dict[str, Any]] = []
        self._track_history = 4.0
        self._track_stride = 1
        self._load_actors: list[dict[str, Any]] = []
        self._lltd_actors: dict[str, Any] = {}
        self._lltd: dict[str, Any] = {}

        self._cam_attach: str | None = None
        self._cam_default_attach: str | None = None
        self._cam_forward_pair: list[str] | None = None
        self._cam_origin_offset = np.zeros(3)
        self._cam_back = 2.5
        self._cam_height = 1.5

        self.camera_mode: str = FOLLOW
        self._offset: CameraOffset | None = None
        self._suspend_camera = False
        self._sim_time: float = float(data.time[0])

    # -- build --------------------------------------------------------------
    def build(self) -> None:
        """Create every actor and park the scene on the first sample."""
        self._apply_palette()
        self._build_points()
        self._read_camera_cfg()
        self._build_ground()
        self._build_joints()
        self._build_links()
        self._build_tires()
        self._build_vectors()
        self._build_tracks()
        self._build_loads()
        self._build_lltd()
        self._refresh_legend()
        self.update_time(float(self.data.time[0]))
        self.reset_view()

    def _apply_palette(self) -> None:
        pal = self.options.palette
        self.plotter.set_background(pal.background_bottom, top=pal.background_top)

    def _build_points(self) -> None:
        sig = self.data.signals
        points = self.data.geometry_cfg.get("points") or {}
        if not points:
            raise VisualConfigError(
                f"{self.data.yml_path.name} defines no geometry.points"
            )
        for name, cols in points.items():
            self._points[str(name)] = np.stack(
                [np.asarray(sig[str(c)], dtype=float) for c in cols], axis=1
            )

    def _build_ground(self) -> None:
        pal = self.options.palette
        extent = self.GROUND_EXTENT
        floor = self.plotter.add_mesh(
            pv.Plane(center=(0.0, 0.0, 0.0), direction=(0.0, 0.0, 1.0),
                     i_size=extent, j_size=extent),
            color=pal.ground, lighting=False, pickable=False,
        )
        # Two weights of line, so distance and speed can be judged at a glance:
        # count bold lines for tens of metres, thin ones for single metres.
        minor = self.plotter.add_mesh(
            grid_lines(extent, self.GRID_MINOR, skip_pitch=self.GRID_MAJOR),
            color=pal.grid, line_width=1.0, lighting=False, pickable=False,
        )
        major = self.plotter.add_mesh(
            grid_lines(extent, self.GRID_MAJOR),
            color=pal.grid_major, line_width=2.0, lighting=False, pickable=False,
        )
        # Lift the lines so they win the depth test against the solid plane.
        for grid in (minor, major):
            grid.SetPosition(0.0, 0.0, self.GRID_Z)
        self._ground_actors = [floor, minor, major]
        self.set_ground_visible(self.options.show_ground)

    def _build_joints(self) -> None:
        joint_cfg = self.data.style_cfg.get("joints") or {}
        mesh = pv.Sphere(
            radius=float(joint_cfg.get("radius", 0.02)),
            theta_resolution=20, phi_resolution=20,
        )
        color = joint_cfg.get("color", "#e0483c")
        for name in self._points:
            self._joint_actors[name] = self.plotter.add_mesh(
                mesh.copy(), color=color, smooth_shading=True,
                specular=0.3, specular_power=20,
            )
        self.set_joints_visible(self.options.show_joints)

    def _build_links(self) -> None:
        link_style = self.data.style_cfg.get("links") or {}
        default = link_style.get("default") or {"radius": 0.01, "color": "black"}
        groups = link_style.get("groups") or {}

        for group, pairs in (self.data.geometry_cfg.get("links") or {}).items():
            style = groups.get(group, default)
            mesh = pv.Cylinder(
                center=(0.0, 0.0, 0.0), direction=(1.0, 0.0, 0.0),
                radius=float(style.get("radius", 0.01)), height=1.0, resolution=24,
            )
            for pair in pairs:
                a, b = str(pair[0]), str(pair[1])
                if a not in self._points or b not in self._points:
                    raise VisualConfigError(
                        f"link group {group!r} references unknown point(s): {a}, {b}"
                    )
                actor = self.plotter.add_mesh(
                    mesh.copy(), color=style.get("color", "black"),
                    smooth_shading=False, specular=0.2,
                )
                mat = vtk.vtkMatrix4x4()
                actor.SetUserMatrix(mat)
                self._link_actors.append({"a": a, "b": b, "actor": actor, "mat": mat})

    def _build_tires(self) -> None:
        sig = self.data.signals
        opacity = float(self.options.tire_opacity)

        for tire_cfg in (self.data.geometry_cfg.get("tires") or {}).values():
            center = str(tire_cfg["center"])
            if center not in self._points:
                raise VisualConfigError(f"tire references unknown point {center!r}")

            x_arr = np.stack(
                [np.asarray(sig[str(c)], dtype=float) for c in tire_cfg["x"]], axis=1
            )
            y_arr = np.stack(
                [np.asarray(sig[str(c)], dtype=float) for c in tire_cfg["y"]], axis=1
            )
            radius = float(tire_cfg["radius"])
            width = float(tire_cfg["width"])

            outer = self.plotter.add_mesh(
                pv.Cylinder(direction=(0, 1, 0), radius=radius, height=width,
                            resolution=64),
                color="#1a1d21", opacity=opacity, smooth_shading=True,
                specular=0.15, specular_power=10,
            )
            rim = self.plotter.add_mesh(
                pv.Cylinder(direction=(0, 1, 0), radius=0.62 * radius,
                            height=0.92 * width, resolution=48),
                color="#b9c0c8", opacity=min(1.0, opacity + 0.25),
                smooth_shading=True, specular=0.6, specular_power=30,
            )
            mat_outer = vtk.vtkMatrix4x4()
            mat_rim = vtk.vtkMatrix4x4()
            outer.SetUserMatrix(mat_outer)
            rim.SetUserMatrix(mat_rim)

            self._tire_actors.append({
                "center": center,
                "x": x_arr,
                "y": y_arr,
                "spin": self._integrate_spin(center, x_arr, radius),
                "outer": outer,
                "rim": rim,
                "mat_outer": mat_outer,
                "mat_rim": mat_rim,
            })
        self.set_tires_visible(self.options.show_tires)

    def _integrate_spin(self, center: str, x_arr: np.ndarray, radius: float) -> np.ndarray:
        """Pre-integrate wheel rotation over the data grid.

        Integrating per rendered frame (the old off-screen path) made spin rate
        depend on export fps and on how often the scene happened to be redrawn.
        """
        pts = self._points[center]
        dt = np.diff(self.data.time)
        dt = np.where(np.abs(dt) < 1e-9, 1e-9, dt)
        velocity = np.diff(pts, axis=0) / dt[:, None]
        forward = np.einsum("ij,ij->i", velocity, x_arr[1:])
        return np.concatenate(([0.0], np.cumsum(forward / max(radius, 1e-6) * dt)))

    def _build_vectors(self) -> None:
        sig = self.data.signals
        n = self.data.n_frames

        for group in (self.data.geometry_cfg.get("vectors") or {}).values():
            for name, vcfg in group.items():
                origin = str(vcfg["origin"])
                if origin not in self._points:
                    raise VisualConfigError(
                        f"vector {name!r} references unknown point {origin!r}"
                    )
                comps = [
                    np.asarray(sig[str(c)], dtype=float) if isinstance(c, str)
                    else np.full(n, float(c))
                    for c in vcfg["direction"]
                ]
                actor = self.plotter.add_mesh(
                    pv.Arrow(
                        start=(0, 0, 0), direction=(1, 0, 0), tip_length=0.3,
                        tip_radius=float(vcfg.get("tip_radius", 0.04)),
                        shaft_radius=float(vcfg.get("shaft_radius", 0.02)),
                        tip_resolution=24, shaft_resolution=24,
                    ),
                    color=vcfg.get("color", "black"), smooth_shading=True,
                )
                mat = vtk.vtkMatrix4x4()
                actor.SetUserMatrix(mat)
                self._vector_actors.append({
                    "name": str(name),
                    "origin": origin,
                    "direction": np.stack(comps, axis=1),
                    "scale": float(vcfg.get("scale", 1.0)),
                    "actor": actor,
                    "mat": mat,
                })
        self.set_vectors_visible(self.options.show_vectors)

    def _build_tracks(self) -> None:
        """Contact-patch trails on the road: where each tire has just been.

        In a corner, rear trails running outside the fronts is understeer made
        visible, and inside is oversteer.
        """
        cfg = self.data.ground_cfg.get("tracks") or {}
        names = [str(p) for p in cfg.get("points") or []]
        if not names:
            return
        unknown = [n for n in names if n not in self._points]
        if unknown:
            raise VisualConfigError(
                f"ground.tracks references unknown point(s): {', '.join(unknown)}"
            )

        self._track_history = float(cfg.get("history", 4.0))
        dt = float(np.median(np.diff(self.data.time)))
        window = self._track_history / max(dt, 1e-9)
        self._track_stride = max(1, int(np.ceil(window / self.TRACK_MAX_POINTS)))

        colors = [str(c) for c in cfg.get("colors") or [self.options.palette.accent]]
        for index, name in enumerate(names):
            actor = self.plotter.add_mesh(
                polyline(np.zeros((2, 3))), color=colors[index % len(colors)],
                line_width=3.0, lighting=False, pickable=False,
            )
            self._track_actors.append({"name": name, "actor": actor})
        self.set_tracks_visible(self.options.show_tracks)

    def _build_loads(self) -> None:
        """Vertical-load footprints: one disc per tire, its area proportional to load.

        The ring marks the run's median load. A disc spilling past its ring
        carries more than usual and turns red; one shrinking inside it is
        unloading and turns blue. Load transfer reads without numbers.
        """
        cfg = self.data.ground_cfg.get("loads") or {}
        corners = cfg.get("corners") or {}
        if not corners:
            return
        radius = float(cfg.get("radius", 0.25))
        disc = pv.Disc(center=(0.0, 0.0, 0.0), inner=0.0, outer=1.0,
                       normal=(0.0, 0.0, 1.0), r_res=1, c_res=72)
        ring = pv.Disc(center=(0.0, 0.0, 0.0), inner=0.93, outer=1.0,
                       normal=(0.0, 0.0, 1.0), r_res=1, c_res=72)

        for name, lcfg in corners.items():
            point = str(lcfg["point"])
            if point not in self._points:
                raise VisualConfigError(
                    f"ground.loads.{name} references unknown point {point!r}"
                )
            load = np.asarray(self.data.signals[str(lcfg["signal"])], dtype=float)
            reference = resolve_load_reference(load)
            disc_actor = self.plotter.add_mesh(
                disc.copy(), color=load_color(1.0), opacity=0.85,
                lighting=False, pickable=False,
            )
            ring_actor = self.plotter.add_mesh(
                ring.copy(), color=self.options.palette.text, opacity=0.9,
                lighting=False, pickable=False,
            )
            disc_mat, ring_mat = vtk.vtkMatrix4x4(), vtk.vtkMatrix4x4()
            disc_actor.SetUserMatrix(disc_mat)
            ring_actor.SetUserMatrix(ring_mat)
            self._load_actors.append({
                "name": str(name),
                "point": point,
                "ratio": load / reference,
                "radius": radius,
                "disc": disc_actor,
                "ring": ring_actor,
                "disc_mat": disc_mat,
                "ring_mat": ring_mat,
            })
        self.set_loads_visible(self.options.show_loads)

    LLTD_Z = 0.03

    def _build_lltd(self) -> None:
        """Each axle's share of lateral load transfer, printed on the road beneath it.

        Built from the same per-tire loads as the footprints, so every run that
        has those - the rig and every driving manoeuvre - gets it.
        """
        corners = (self.data.ground_cfg.get("loads") or {}).get("corners") or {}
        names = ("fl", "fr", "rl", "rr")
        if not all(name in corners for name in names):
            return
        loads = {
            name: np.asarray(self.data.signals[str(corners[name]["signal"])], dtype=float)
            for name in names
        }
        front, rear, share = axle_load_transfer(loads)
        self._lltd = {
            "front": front,
            "rear": rear,
            "share": share,
            "points": {
                "front": (str(corners["fl"]["point"]), str(corners["fr"]["point"])),
                "rear": (str(corners["rl"]["point"]), str(corners["rr"]["point"])),
            },
        }

        text = pv.Color(self.options.palette.text).float_rgb
        backdrop = pv.Color(self.options.palette.background_top).float_rgb
        for axle in ("front", "rear"):
            # A 2D overlay anchored to a world point: a 3D billboard sits under the
            # chassis and gets hidden by the frame tubes the camera looks through.
            actor = vtk.vtkTextActor()
            actor.GetPositionCoordinate().SetCoordinateSystemToWorld()
            prop = actor.GetTextProperty()
            prop.SetFontSize(14)
            prop.SetBold(True)
            prop.SetColor(*text)
            prop.SetBackgroundColor(*backdrop)
            prop.SetBackgroundOpacity(0.8)
            prop.SetJustificationToCentered()
            prop.SetVerticalJustificationToCentered()
            actor.SetPickable(False)
            self.plotter.add_actor(actor, reset_camera=False, pickable=False)
            self._lltd_actors[axle] = actor
        self._set_visible(self._lltd_actors.values(), self.options.show_loads)

    def _read_camera_cfg(self) -> None:
        cam = self.data.camera_cfg
        self._cam_default_attach = cam.get("attach_to")
        self._cam_attach = self._cam_default_attach
        pair = cam.get("forward_pair")
        self._cam_forward_pair = [str(p) for p in pair] if pair else None

        offset = cam.get("origin_offset") or {}
        self._cam_origin_offset = np.array(
            [offset.get("x", 0.0), offset.get("y", 0.0), offset.get("z", 0.0)],
            dtype=float,
        )
        offsets = cam.get("camera_offsets") or {}
        self._cam_back = float(offsets.get("back", 2.5))
        self._cam_height = float(offsets.get("height", 1.5))
        self.plotter.camera.clipping_range = (0.01, 4000.0)

    # -- visibility ---------------------------------------------------------
    @staticmethod
    def _set_visible(actors: Iterable[Any], visible: bool) -> None:
        for actor in actors:
            actor.SetVisibility(bool(visible))

    def set_ground_visible(self, visible: bool) -> None:
        self.options.show_ground = bool(visible)
        self._set_visible(self._ground_actors, visible)
        self._refresh_legend()

    def set_joints_visible(self, visible: bool) -> None:
        self.options.show_joints = bool(visible)
        self._set_visible(self._joint_actors.values(), visible)

    def set_tires_visible(self, visible: bool) -> None:
        self.options.show_tires = bool(visible)
        self._set_visible(
            [t[key] for t in self._tire_actors for key in ("outer", "rim")], visible
        )

    def set_vectors_visible(self, visible: bool) -> None:
        self.options.show_vectors = bool(visible)
        self._set_visible([v["actor"] for v in self._vector_actors], visible)

    def set_tracks_visible(self, visible: bool) -> None:
        self.options.show_tracks = bool(visible)
        self._set_visible([t["actor"] for t in self._track_actors], visible)
        self._refresh_legend()

    def set_loads_visible(self, visible: bool) -> None:
        self.options.show_loads = bool(visible)
        self._set_visible(
            [item[key] for item in self._load_actors for key in ("disc", "ring")], visible
        )
        self._set_visible(self._lltd_actors.values(), visible)
        self._refresh_legend()

    def legend_lines(self) -> list[str]:
        """What each ground layer on screen means, one line apiece."""
        lines: list[str] = []
        if self.options.show_ground and self._ground_actors:
            lines.append(
                f"Grid: {self.GRID_MINOR:g} m squares, bold line every {self.GRID_MAJOR:g} m"
            )
        if self.options.show_tracks and self._track_actors:
            legend = (self.data.ground_cfg.get("tracks") or {}).get("legend")
            lines.append(str(legend) if legend else "Tracks: recent contact-patch paths")
        if self.options.show_loads and self._load_actors:
            lines.append(
                "Tire load: disc area ~ load, ring = median load; red heavier, blue lighter"
            )
        if self.options.show_loads and self._lltd_actors:
            lines.append("Axle labels: share of lateral load transfer (LLTD) and its size")
        return lines

    def _refresh_legend(self) -> None:
        # One named actor, replaced rather than stacked on each toggle.
        self.plotter.add_text(
            "\n".join(self.legend_lines()), position="upper_left", font_size=9,
            color=self.options.palette.text, name="bobvis-ground-legend",
        )

    # -- time ---------------------------------------------------------------
    @property
    def sim_time(self) -> float:
        return self._sim_time

    def _bracket(self, sim_time: float) -> tuple[int, int, float]:
        time = self.data.time
        if sim_time <= float(time[0]):
            return 0, 0, 0.0
        if sim_time >= float(time[-1]):
            last = len(time) - 1
            return last, last, 0.0
        i1 = int(np.searchsorted(time, sim_time, side="right"))
        i0 = i1 - 1
        t0, t1 = float(time[i0]), float(time[i1])
        alpha = 0.0 if t1 <= t0 else (float(sim_time) - t0) / (t1 - t0)
        return i0, i1, float(np.clip(alpha, 0.0, 1.0))

    @staticmethod
    def _lerp(arr: np.ndarray, i0: int, i1: int, alpha: float) -> np.ndarray:
        if i0 == i1:
            return np.asarray(arr[i0], dtype=float)
        return (1.0 - alpha) * np.asarray(arr[i0], dtype=float) + alpha * np.asarray(
            arr[i1], dtype=float
        )

    def update_time(self, sim_time: float) -> None:
        """Move every actor to its interpolated pose at ``sim_time``."""
        self._sim_time = float(sim_time)
        i0, i1, alpha = self._bracket(sim_time)

        for name, actor in self._joint_actors.items():
            actor.SetPosition(*self._lerp(self._points[name], i0, i1, alpha))

        for link in self._link_actors:
            T = link_transform(
                self._lerp(self._points[link["a"]], i0, i1, alpha),
                self._lerp(self._points[link["b"]], i0, i1, alpha),
            )
            _to_vtk_matrix(link["mat"], T)
            link["actor"].Modified()

        for tire in self._tire_actors:
            self._update_tire(tire, i0, i1, alpha)

        for vec in self._vector_actors:
            self._update_vector(vec, i0, i1, alpha)

        self._update_tracks(i0, i1, alpha)
        self._update_loads(i0, i1, alpha)
        self._update_lltd(i0, i1, alpha)
        self._update_ground(i0, i1, alpha)
        self._update_camera(i0, i1, alpha)

    def _update_ground(self, i0: int, i1: int, alpha: float) -> None:
        """Slide the ground under the car, snapped to the grid pitch.

        A world-fixed plane runs out from under a lap simulation after a couple
        of hundred metres. Snapping to the cell size keeps the grid stationary
        to the eye, so it still reads as ground the car is moving over.
        """
        if not self._ground_actors:
            return
        frame = self._vehicle_frame(i0, i1, alpha)
        if frame is None:
            lo, hi = self._car_bounds()
            centre = 0.5 * (lo + hi)
        else:
            centre = frame[0]

        # Snap to the major pitch: any finer and the bold lines would jump.
        pitch = self.GRID_MAJOR
        x = float(np.round(centre[0] / pitch) * pitch)
        y = float(np.round(centre[1] / pitch) * pitch)
        floor, *grids = self._ground_actors
        floor.SetPosition(x, y, 0.0)
        for grid in grids:
            grid.SetPosition(x, y, self.GRID_Z)

    def _update_tracks(self, i0: int, i1: int, alpha: float) -> None:
        if not self._track_actors:
            return
        idx = trail_indices(self.data.time, i0, self._track_history, self._track_stride)
        for track in self._track_actors:
            xyz = self._points[track["name"]]
            points = np.vstack([xyz[idx], self._lerp(xyz, i0, i1, alpha)])
            points[:, 2] = self.TRACK_Z  # a mark on the road, not a line in the air
            # Update the mapper's own input: PyVista's `mapper.dataset` returns a
            # fresh wrapper, and copying into that leaves the drawn line unchanged.
            track["actor"].GetMapper().GetInput().ShallowCopy(polyline(points))

    def _update_loads(self, i0: int, i1: int, alpha: float) -> None:
        for item in self._load_actors:
            centre = self._lerp(self._points[item["point"]], i0, i1, alpha)
            ratio = float(np.nan_to_num(self._lerp(item["ratio"], i0, i1, alpha)))
            disc_radius = max(float(load_disc_radius(ratio, item["radius"])), 1e-4)

            for key, radius, z in (("disc", disc_radius, self.LOAD_Z),
                                   ("ring", item["radius"], self.RING_Z)):
                T = np.diag([radius, radius, 1.0, 1.0])
                T[:3, 3] = (centre[0], centre[1], z)
                _to_vtk_matrix(item[f"{key}_mat"], T)
                item[key].Modified()
            item["disc"].prop.color = load_color(ratio)

    def _update_lltd(self, i0: int, i1: int, alpha: float) -> None:
        if not self._lltd_actors:
            return
        share = float(self._lerp(self._lltd["share"], i0, i1, alpha))
        for axle, actor in self._lltd_actors.items():
            left, right = self._lltd["points"][axle]
            middle = 0.5 * (
                self._lerp(self._points[left], i0, i1, alpha)
                + self._lerp(self._points[right], i0, i1, alpha)
            )
            actor.GetPositionCoordinate().SetValue(float(middle[0]), float(middle[1]), self.LLTD_Z)

            label = axle.capitalize()
            if not np.isfinite(share):
                actor.SetInput(f"{label}  —")
                continue
            fraction = share if axle == "front" else 1.0 - share
            transfer = abs(float(self._lerp(self._lltd[axle], i0, i1, alpha)))
            actor.SetInput(f"{label} {fraction:.0%}  ·  {transfer:.0f} N")

    def _update_tire(self, tire: dict[str, Any], i0: int, i1: int, alpha: float) -> None:
        center = self._lerp(self._points[tire["center"]], i0, i1, alpha)
        x = safe_normalize(self._lerp(tire["x"], i0, i1, alpha))
        y_raw = self._lerp(tire["y"], i0, i1, alpha)
        y = safe_normalize(y_raw - float(np.dot(y_raw, x)) * x,
                           fallback=np.array([0.0, 1.0, 0.0]))
        z = safe_normalize(np.cross(x, y), fallback=np.array([0.0, 0.0, 1.0]))

        spin = tire["spin"]
        theta = (
            float(spin[i0]) if i0 == i1
            else float((1.0 - alpha) * spin[i0] + alpha * spin[i1])
        )
        Ry = np.array([
            [np.cos(theta), 0.0, np.sin(theta)],
            [0.0, 1.0, 0.0],
            [-np.sin(theta), 0.0, np.cos(theta)],
        ])

        T = np.eye(4)
        T[:3, :3] = np.column_stack((x, y, z)) @ Ry
        T[:3, 3] = center

        _to_vtk_matrix(tire["mat_outer"], T)
        tire["outer"].Modified()
        _to_vtk_matrix(tire["mat_rim"], T)
        tire["rim"].Modified()

    def _update_vector(self, vec: dict[str, Any], i0: int, i1: int, alpha: float) -> None:
        origin = self._lerp(self._points[vec["origin"]], i0, i1, alpha)
        d = self._lerp(vec["direction"], i0, i1, alpha)
        length = float(np.linalg.norm(d))

        T = np.eye(4)
        if length < 1e-6:
            # Collapse rather than hide: no NaN transforms, no per-frame flicker.
            T[:3, :3] = 0.0
        else:
            T[:3, :3] = frame_from_x(d / length) @ np.diag(
                [length * vec["scale"], 1.0, 1.0]
            )
        T[:3, 3] = origin
        _to_vtk_matrix(vec["mat"], T)
        vec["actor"].Modified()

    # -- camera -------------------------------------------------------------
    def _vehicle_frame(
        self, i0: int, i1: int, alpha: float
    ) -> tuple[np.ndarray, np.ndarray] | None:
        if self._cam_attach not in self._points or not self._cam_forward_pair:
            return None
        p1 = self._lerp(self._points[self._cam_forward_pair[0]], i0, i1, alpha)
        p2 = self._lerp(self._points[self._cam_forward_pair[1]], i0, i1, alpha)

        forward = safe_normalize(np.array([p2[0] - p1[0], p2[1] - p1[1], 0.0]))
        right = safe_normalize(np.cross(forward, np.array([0.0, 0.0, 1.0])))
        up = safe_normalize(np.cross(right, forward))
        R = np.column_stack((forward, right, up))
        origin = (
            self._lerp(self._points[self._cam_attach], i0, i1, alpha)
            + R @ self._cam_origin_offset
        )
        return origin, R

    def _default_offset(self) -> CameraOffset:
        return CameraOffset(
            position=(-self._cam_back, 0.0, self._cam_height),
            focal=(0.0, 0.0, 0.0),
            up=(0.0, 0.0, 1.0),
            view_angle=float(self.plotter.camera.view_angle),
        )

    def _update_camera(self, i0: int, i1: int, alpha: float) -> None:
        if self.camera_mode != FOLLOW or self._suspend_camera:
            return
        frame = self._vehicle_frame(i0, i1, alpha)
        if frame is None:
            return
        origin, R = frame
        offset = self._offset or self._default_offset()

        cam = self.plotter.camera
        cam.position = tuple(origin + R @ np.asarray(offset.position, dtype=float))
        cam.focal_point = tuple(origin + R @ np.asarray(offset.focal, dtype=float))
        cam.up = tuple(R @ np.asarray(offset.up, dtype=float))
        cam.view_angle = offset.view_angle
        cam.parallel_projection = offset.parallel_projection
        cam.parallel_scale = offset.parallel_scale

    def capture_view(self) -> None:
        """Freeze the current camera pose as the vehicle-frame follow offset.

        Called after the user finishes a mouse orbit so follow mode keeps the
        view they just chose instead of snapping back on the next frame.
        """
        i0, i1, alpha = self._bracket(self._sim_time)
        frame = self._vehicle_frame(i0, i1, alpha)
        cam = self.plotter.camera
        if frame is None:
            origin = np.asarray(cam.focal_point, dtype=float)
            R = np.eye(3)
        else:
            origin, R = frame

        Rt = R.T
        self._offset = CameraOffset(
            position=tuple(Rt @ (np.asarray(cam.position, dtype=float) - origin)),
            focal=tuple(Rt @ (np.asarray(cam.focal_point, dtype=float) - origin)),
            up=tuple(Rt @ np.asarray(cam.up, dtype=float)),
            view_angle=float(cam.view_angle),
            parallel_projection=bool(getattr(cam, "parallel_projection", False)),
            parallel_scale=float(getattr(cam, "parallel_scale", 1.0)),
        )

    @property
    def camera_offset(self) -> CameraOffset | None:
        return self._offset

    @camera_offset.setter
    def camera_offset(self, offset: CameraOffset | None) -> None:
        self._offset = offset

    def set_camera_mode(self, mode: str) -> None:
        if mode not in (FOLLOW, FREE):
            raise ValueError(f"unknown camera mode {mode!r}")
        previous = self.camera_mode
        self.camera_mode = mode
        if mode == FOLLOW and previous == FREE:
            # Adopt whatever the user is looking at now as the follow offset.
            self.capture_view()

    def suspend_camera(self, suspended: bool) -> None:
        """Stop follow mode from fighting an in-progress mouse interaction."""
        self._suspend_camera = bool(suspended)

    def set_focus_point(self, name: str) -> None:
        """Retarget follow mode. ``''`` or ``'Whole car'`` restores the YAML target."""
        if name in ("", "Whole car"):
            self._cam_attach = self._cam_default_attach
        elif name in self._points:
            self._cam_attach = name
        self.capture_view()

    # -- view presets -------------------------------------------------------
    def _car_bounds(self) -> tuple[np.ndarray, np.ndarray]:
        i0, i1, alpha = self._bracket(self._sim_time)
        pts = np.array([self._lerp(p, i0, i1, alpha) for p in self._points.values()])
        return pts.min(axis=0), pts.max(axis=0)

    ZOOM = 1.35
    """Tighten VTK's default framing, which leaves a lot of empty margin."""

    def _zoom_to_car(self) -> None:
        """Frame the joint cloud at the current time, ignoring the ground plane."""
        if not self._points:
            self.plotter.reset_camera()
            return
        lo, hi = self._car_bounds()
        pad = 0.08 * float(np.max(hi - lo) + 1e-6)
        self.plotter.reset_camera(
            bounds=(lo[0] - pad, hi[0] + pad,
                    lo[1] - pad, hi[1] + pad,
                    lo[2] - pad, hi[2] + pad)
        )
        self.plotter.camera.zoom(self.ZOOM)
        self.plotter.camera.clipping_range = (0.01, 4000.0)

    def reset_view(self) -> None:
        self.set_view("iso")

    def set_view(self, preset: str) -> None:
        """Point the camera along a principal axis and reframe the car."""
        p = self.plotter

        def iso() -> None:
            p.view_isometric()
            p.camera.azimuth += 180

        def front() -> None:
            p.view_yz()
            p.camera.azimuth += 180

        def right() -> None:
            p.view_xz()
            p.camera.azimuth += 180

        presets: dict[str, Callable[[], None]] = {
            "iso": iso,
            "top": p.view_xy,
            "rear": p.view_yz,
            "front": front,
            "left": p.view_xz,
            "right": right,
        }
        apply = presets.get(preset)
        if apply is None:
            return
        apply()
        self._zoom_to_car()
        self.capture_view()

    def rotate(self, axis: str, degrees: float) -> None:
        cam = self.plotter.camera
        if axis == "x":
            cam.elevation += degrees
        elif axis == "y":
            cam.azimuth += degrees
        elif axis == "z":
            cam.roll += degrees
        else:
            return
        self.capture_view()

    def zoom(self, factor: float) -> None:
        self.plotter.camera.zoom(factor)
        self.capture_view()

    # -- navigation ---------------------------------------------------------
    def camera_pose(self) -> CameraPose:
        """The live camera, in the form :mod:`_1_VisualSim.navigation` works on."""
        cam = self.plotter.camera
        return CameraPose(
            position=np.asarray(cam.position, dtype=float),
            focal=np.asarray(cam.focal_point, dtype=float),
            up=np.asarray(cam.up, dtype=float),
            view_angle=float(cam.view_angle),
            parallel_projection=bool(getattr(cam, "parallel_projection", False)),
            parallel_scale=float(getattr(cam, "parallel_scale", 1.0)),
        )

    def set_camera_pose(self, pose: CameraPose) -> None:
        """Apply a navigation result and adopt it as the follow offset.

        Capturing on every step, not only when a gesture ends, is what lets a
        drag or scroll continue smoothly while playback moves the car.
        """
        cam = self.plotter.camera
        cam.position = tuple(float(v) for v in pose.position)
        cam.focal_point = tuple(float(v) for v in pose.focal)
        cam.up = tuple(float(v) for v in pose.up)
        if pose.parallel_projection:
            cam.parallel_scale = float(pose.parallel_scale)
        self.capture_view()

    def pick_point(self, display_x: float, display_y: float) -> np.ndarray | None:
        """World point on the geometry under a pixel, or ``None`` over empty space.

        Display coordinates are VTK's: device pixels, origin bottom-left.
        """
        renderer = getattr(self.plotter, "renderer", None)
        if renderer is None:
            return None
        picker = vtk.vtkCellPicker()
        picker.SetTolerance(0.002)
        if not picker.Pick(float(display_x), float(display_y), 0.0, renderer):
            return None
        return np.asarray(picker.GetPickPosition(), dtype=float)


def ensure_offscreen_display(timeout: float = 5.0) -> bool:
    """Start a virtual X display when there is none, on Linux.

    VTK renders without one, but it probes X first and logs a "bad X server
    connection" warning on the way to its fallback. On a headless Linux box
    with Xvfb installed, give VTK a real display and let it take the normal
    path. A no-op on Windows, macOS, and anywhere DISPLAY is already set.

    Started here rather than via ``pyvista.start_xvfb``, which was removed in
    PyVista 0.49. Returns True when a display is available.
    """
    if os.name == "nt":
        return False
    if os.environ.get("DISPLAY"):
        return True

    xvfb = shutil.which("Xvfb")
    if xvfb is None:
        return False

    display = ":99"
    socket = Path(f"/tmp/.X11-unix/X{display[1:]}")
    try:
        subprocess.Popen(
            [xvfb, display, "-screen", "0", "1920x1080x24", "-nolisten", "tcp"],
            stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL,
        )
    except OSError:  # noqa: PERF203 - rendering still works, just noisily
        return False

    deadline = time.monotonic() + timeout
    while time.monotonic() < deadline:
        if socket.exists():
            os.environ["DISPLAY"] = display
            return True
        time.sleep(0.05)
    return False


def build_offscreen_scene(
    data: SimData,
    size: Sequence[int],
    options: SceneOptions | None = None,
    anti_aliasing: AntiAliasing | None = "ssaa",
) -> tuple[Any, VisualScene]:
    """An off-screen plotter with a built scene, for video export or tests."""
    ensure_offscreen_display()
    plotter = pv.Plotter(
        off_screen=True,
        window_size=[int(size[0]), int(size[1])],
        lighting="three lights",
    )
    scene = VisualScene(data, plotter, options)
    scene.build()
    if scene.options.show_orientation_axes:
        plotter.add_axes()  # type: ignore[call-arg]
    if anti_aliasing:
        try:
            plotter.enable_anti_aliasing(anti_aliasing)
        except Exception:  # noqa: BLE001 - AA is cosmetic, never fail an export for it
            pass
    return plotter, scene
