"""BobVis scene payloads: a run, flattened into something WebGL can draw.

The viewer used to be a PyQt6 window driving VTK through PyVista. It is now a
tab in the app, so this module does what ``_1_VisualSim/scene.py`` used to: it
resolves a visual config against its signals and lays the result out for the
renderer in ``_5_App/static/visual.js``.

The split is deliberate. Everything that depends on the *run* -- which signal
feeds which point, what a corner's reference load is, which columns a tire's
axes come from -- is resolved once here, server side, into flat indices. The
browser then only interpolates numbers and draws. Per frame it touches no names
and makes no decisions.

Transport is a JSON header plus one little-endian float32 buffer, because a
scene is mostly coordinates: the rig demo is 68 points over 100 frames, and as
JSON that is ~40x the bytes and a parse besides. The header says where each
block starts, so the browser does one fetch, one ``Float32Array``, and no copy.

Blocks are frame-major throughout -- every value for frame 0, then frame 1 --
so drawing a frame reads one contiguous span.
"""

from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
from typing import Any

import numpy as np

from _1_VisualSim.sim_data import SimData, resolve_load_reference
from _1_VisualSim.tire_state import axle_load_transfer, grip_usage

VISUAL_RESULTS_ROOT = Path("_1_VisualSim/results")

FLOAT = np.float32


@dataclass(frozen=True)
class ScenePayload:
    """A scene the browser can draw: the header describes the buffer."""

    header: dict[str, Any]
    buffer: bytes


class _Blocks:
    """Packs named float32 blocks and records where each one landed."""

    def __init__(self) -> None:
        self._chunks: list[np.ndarray] = []
        self._floats = 0
        self.layout: dict[str, dict[str, int]] = {}

    def add(self, name: str, values: np.ndarray, *, stride: int) -> None:
        flat = np.ascontiguousarray(values, dtype=FLOAT).ravel()
        self.layout[name] = {
            "offset": self._floats,
            "count": int(flat.size),
            "stride": int(stride),
        }
        self._chunks.append(flat)
        self._floats += int(flat.size)

    def to_bytes(self) -> bytes:
        if not self._chunks:
            return b""
        return np.concatenate(self._chunks).astype(FLOAT).tobytes()


def _columns(data: SimData, names: list[str]) -> np.ndarray:
    """Stack signal columns into ``[frames, len(names)]``."""
    return np.column_stack([data.get_signal(str(n)) for n in names])


def _finite(values: np.ndarray) -> np.ndarray:
    """Replace NaN and infinity with zero, so one bad sample cannot blank a frame."""
    return np.nan_to_num(np.asarray(values, dtype=float), nan=0.0, posinf=0.0, neginf=0.0)


def scene_payload(config_path: str | Path, data_path: str | Path) -> ScenePayload:
    """Resolve a visual config and its signals into a drawable payload."""
    data = SimData(config_path, data_path)
    geometry = data.geometry_cfg
    style = data.style_cfg
    blocks = _Blocks()

    blocks.add("time", data.time, stride=1)

    # -- points: every named hardpoint, resolved to xyz per frame ------------
    point_cfg: dict[str, Any] = dict(geometry.get("points") or {})
    point_names = [str(name) for name in point_cfg]
    index_of = {name: i for i, name in enumerate(point_names)}
    if point_names:
        positions = np.stack(
            [_finite(_columns(data, list(point_cfg[name]))) for name in point_names],
            axis=1,
        )
    else:
        positions = np.zeros((data.n_frames, 0, 3))
    blocks.add("positions", positions, stride=3)

    scalars: list[np.ndarray] = []
    vectors: list[np.ndarray] = []

    def scalar_slot(values: np.ndarray) -> int:
        scalars.append(_finite(values))
        return len(scalars) - 1

    def vector_slot(names: list[str]) -> int:
        vectors.append(_finite(_columns(data, names)))
        return len(vectors) - 1

    # -- links: index pairs, grouped so each group is one draw call ----------
    link_style = dict(style.get("links") or {})
    default_style = dict(link_style.get("default") or {})
    group_styles = dict(link_style.get("groups") or {})
    links: list[dict[str, Any]] = []
    for group, pairs in (geometry.get("links") or {}).items():
        segments = [
            [index_of[str(a)], index_of[str(b)]]
            for a, b in pairs
            if str(a) in index_of and str(b) in index_of
        ]
        if not segments:
            continue
        merged = {**default_style, **dict(group_styles.get(group) or {})}
        links.append(
            {
                "group": str(group),
                "color": str(merged.get("color", "#33383f")),
                "radius": float(merged.get("radius", 0.01)),
                "segments": segments,
            }
        )

    # -- tires: a disc per corner, oriented by two axis signals --------------
    tires = [
        {
            "corner": str(corner),
            "center": index_of[str(cfg["center"])],
            "radius": float(cfg.get("radius", 0.2032)),
            "width": float(cfg.get("width", 0.1778)),
            "axis_x": vector_slot([str(c) for c in cfg["x"]]),
            "axis_y": vector_slot([str(c) for c in cfg["y"]]),
        }
        for corner, cfg in (geometry.get("tires") or {}).items()
        if str(cfg.get("center")) in index_of
    ]

    # -- vectors: forces and the like, drawn as arrows from a point ---------
    arrows: list[dict[str, Any]] = []
    for group, corners in (geometry.get("vectors") or {}).items():
        for corner, cfg in (corners or {}).items():
            origin = str(cfg.get("origin", ""))
            direction = [str(c) for c in (cfg.get("direction") or [])]
            if origin not in index_of or len(direction) != 3:
                continue
            arrows.append(
                {
                    "group": str(group),
                    "corner": str(corner),
                    "origin": index_of[origin],
                    "slot": vector_slot(direction),
                    "scale": float(cfg.get("scale", 1.0)),
                    "color": str(cfg.get("color", "#f0932b")),
                    "shaft_radius": float(cfg.get("shaft_radius", 0.018)),
                }
            )

    # -- ground: contact-patch trails and load footprints --------------------
    ground = data.ground_cfg
    tracks_cfg = dict(ground.get("tracks") or {})
    track_points = [str(p) for p in (tracks_cfg.get("points") or [])]
    track_colors = [str(c) for c in (tracks_cfg.get("colors") or [])]
    tracks = {
        "history": float(tracks_cfg.get("history", 3.0)),
        "legend": str(tracks_cfg.get("legend", "")),
        "corners": [
            {
                "point": index_of[name],
                "color": track_colors[i] if i < len(track_colors) else "#2b7fd4",
            }
            for i, name in enumerate(track_points)
            if name in index_of
        ],
    }

    loads_cfg = dict(ground.get("loads") or {})
    load_corners = []
    for corner, cfg in (loads_cfg.get("corners") or {}).items():
        point = str(cfg.get("point", ""))
        signal = str(cfg.get("signal", ""))
        if point not in index_of or signal not in data.signals:
            continue
        series = data.get_signal(signal)
        load_corners.append(
            {
                "corner": str(corner),
                "point": index_of[point],
                "slot": scalar_slot(series),
                # The ring stands for the load this corner normally carries, so
                # the eye reads a footprint against the car's own static state.
                "reference": resolve_load_reference(series),
            }
        )
    loads = {"radius": float(loads_cfg.get("radius", 0.28)), "corners": load_corners}

    # -- plots: the signal traces under the viewport -------------------------
    plots = [
        {"name": str(plot.get("name", plot.get("y", ""))), "slot": scalar_slot(data.get_signal(str(plot["y"])))}
        for plot in data.plots_cfg
        if isinstance(plot.get("y"), str) and str(plot["y"]) in data.signals
    ]

    grip = _grip_payload(data, scalar_slot)

    blocks.add(
        "scalars",
        np.stack(scalars, axis=1) if scalars else np.zeros((data.n_frames, 0)),
        stride=1,
    )
    blocks.add(
        "vectors",
        np.stack(vectors, axis=1) if vectors else np.zeros((data.n_frames, 0, 3)),
        stride=3,
    )

    header: dict[str, Any] = {
        "frames": data.n_frames,
        "duration": data.duration,
        "speed": float(data.render_cfg.get("speed", 1.0)),
        "points": point_names,
        "joints": {
            "radius": float((style.get("joints") or {}).get("radius", 0.014)),
            "color": str((style.get("joints") or {}).get("color", "#e0483c")),
        },
        "links": links,
        "tires": tires,
        "arrows": arrows,
        "tracks": tracks,
        "loads": loads,
        "plots": plots,
        "grip": grip,
        "camera": data.camera_cfg,
        "metrics": _metrics_rows(data),
        "layout": blocks.layout,
    }
    return ScenePayload(header=header, buffer=blocks.to_bytes())


def _grip_payload(data: SimData, scalar_slot: Any) -> dict[str, Any]:
    """Friction-circle usage per corner, and the axles' load transfer.

    The MF5.2 peak-grip evaluation stays in Python, next to the ``.tir`` parsing
    it depends on, so the browser receives fractions of peak grip and never has
    to know what a tire model is. A run without tire forces -- the four-post rig
    -- gets an empty block and the Tires tab simply does not appear.
    """
    cfg = data.tire_forces_cfg
    corners_cfg = dict(cfg.get("corners") or {})
    friction = dict(cfg.get("friction") or {})
    if not corners_cfg or not friction:
        return {}

    corners: list[dict[str, Any]] = []
    loads: dict[str, np.ndarray] = {}
    for corner, entry in corners_cfg.items():
        names = {key: str(entry.get(key, "")) for key in ("fx", "fy", "fz", "gamma")}
        if not all(names[key] in data.signals for key in ("fx", "fy", "fz")):
            continue
        coeffs = friction.get(str(entry.get("axle", "front")))
        if not coeffs:
            continue
        fz = data.get_signal(names["fz"])
        loads[str(corner)] = fz
        gamma = data.get_signal(names["gamma"]) if names["gamma"] in data.signals else 0.0
        longitudinal, lateral, usage = grip_usage(
            data.get_signal(names["fx"]), data.get_signal(names["fy"]), fz, gamma, coeffs
        )
        corners.append(
            {
                "corner": str(corner),
                "axle": str(entry.get("axle", "front")),
                "tir": str(coeffs.get("tir", "")),
                # NaN means "off the ground", which JSON cannot carry and the
                # renderer must not draw as zero, so it travels as a flag.
                "slot_x": scalar_slot(np.nan_to_num(longitudinal)),
                "slot_y": scalar_slot(np.nan_to_num(lateral)),
                "slot_usage": scalar_slot(np.nan_to_num(usage)),
                "slot_airborne": scalar_slot(np.isnan(usage).astype(float)),
            }
        )
    if not corners:
        return {}

    transfer: dict[str, Any] = {}
    if set(loads) >= {"fl", "fr", "rl", "rr"}:
        front, rear, share = axle_load_transfer(loads)
        transfer = {
            "slot_front": scalar_slot(front),
            "slot_rear": scalar_slot(rear),
            "slot_lltd": scalar_slot(np.nan_to_num(share)),
            "slot_lltd_undefined": scalar_slot(np.isnan(share).astype(float)),
        }
    return {"corners": corners, "transfer": transfer}


def _metrics_rows(data: SimData) -> list[dict[str, str]]:
    """The run's metrics CSV, or an empty list when it has none.

    A missing or unreadable metrics file is not an error: it only means the tab
    has nothing to show, and a scene is still worth drawing without it.
    """
    path = data.metrics_path
    if path is None:
        return []
    import csv

    try:
        with open(path, "r", newline="", encoding="utf-8") as handle:
            rows = [
                {str(k): str(v) for k, v in row.items() if k}
                for row in csv.DictReader(handle)
                if any((v or "").strip() for v in row.values())
            ]
    except (OSError, UnicodeDecodeError, csv.Error):
        return []
    return rows


def available_runs(root: str | Path | None = None) -> list[dict[str, str]]:
    """Every visual run on disk, newest first.

    A run is any visual config beside the signal file of the same name. Captures
    write ``<eval>_visual.yml``; the demo scene writes ``demo_step_steer.yml``.
    Pairing on the stem rather than on a suffix means neither is a special case.

    A config whose data file has been cleaned away is skipped rather than
    offered and then failing to open.
    """
    base = Path(root) if root is not None else Path.cwd()
    results = base / VISUAL_RESULTS_ROOT
    if not results.is_dir():
        return []
    runs = []
    for config in sorted(results.glob("*.yml")):
        data = config.with_suffix(".npz")
        if not data.is_file():
            continue
        runs.append(
            {
                "id": config.stem,
                "label": config.stem.replace("_visual", "").replace("_", " "),
                "config": config.relative_to(base).as_posix(),
                "data": data.relative_to(base).as_posix(),
                "modified": str(int(data.stat().st_mtime)),
            }
        )
    runs.sort(key=lambda run: run["modified"], reverse=True)
    return runs
