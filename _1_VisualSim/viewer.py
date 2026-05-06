"""
viewer.py  —  BobVis Interactive Viewer
========================================
Launch:
    python viewer.py visual.yml data.npz

All geometry + scene logic lives in run_visual.py (unchanged).
This file wraps it in a PyQt6 + PyVistaQt + Matplotlib GUI.

Dependencies:
    pip install PyQt6 pyvistaqt pyvista matplotlib pyyaml numpy
"""

from __future__ import annotations

import argparse
import sys
from collections.abc import Callable
from pathlib import Path
from typing import Any

import numpy as np
import yaml

# ── Qt ────────────────────────────────────────────────────────────────────────
from PyQt6.QtCore import Qt, QThread, pyqtSignal, QTimer
from PyQt6.QtWidgets import (
    QApplication,
    QMainWindow,
    QWidget,
    QHBoxLayout,
    QVBoxLayout,
    QToolBar,
    QStatusBar,
    QLabel,
    QPushButton,
    QSlider,
    QComboBox,
    QSplitter,
    QScrollArea,
    QSizePolicy,
    QFrame,
    QDialog,
    QDialogButtonBox,
    QLineEdit,
    QFileDialog,
    QMessageBox,
    QFormLayout,
)
from PyQt6.QtGui import QAction, QKeySequence

# ── PyVista (Qt-embedded) ─────────────────────────────────────────────────────
import pyvista as pv
from pyvistaqt import QtInteractor

# ── Matplotlib (Qt-embedded) ──────────────────────────────────────────────────
import matplotlib

matplotlib.use("QtAgg")
from matplotlib.figure import Figure
from matplotlib.backends.backend_qtagg import FigureCanvasQTAgg as FigureCanvas


# ══════════════════════════════════════════════════════════════════════════════
# 1.  DATA LOADER
#     Reads .yml config + .npz signal file.  Shared by GUI and CLI.
# ══════════════════════════════════════════════════════════════════════════════

class SimData:
    """
    Holds parsed config and raw signal arrays.

    Attributes
    ----------
    cfg       : dict  — full parsed YAML
    signals   : dict[str, np.ndarray]  — all npz arrays, keyed by name
    time      : np.ndarray             — 1-D time vector
    n_frames  : int
    signal_names : list[str]           — all available signal keys (for dropdowns)
    """

    def __init__(self, yml_path: str | Path, data_path: str | Path) -> None:
        self.yml_path  = Path(yml_path)
        self.data_path = Path(data_path)

        # ── load YAML ────────────────────────────────────────────────────────
        with open(self.yml_path, "r", encoding="utf-8") as f:
            self.cfg: dict[str, Any] = yaml.safe_load(f)

        # ── load NPZ or CSV ──────────────────────────────────────────────────
        suffix = self.data_path.suffix.lower()
        if suffix == ".npz":
            raw = np.load(self.data_path)
            self.signals: dict[str, np.ndarray] = {
                k: np.asarray(raw[k], dtype=float) for k in raw.files
            }
        elif suffix == ".csv":
            import csv as _csv
            with open(self.data_path, "r", newline="", encoding="utf-8") as f:
                reader = _csv.DictReader(f)
                rows = list(reader)
            if not rows:
                raise ValueError("CSV file is empty")
            self.signals = {
                col: np.array([float(r[col]) for r in rows], dtype=float)
                for col in rows[0].keys()
            }
        else:
            raise ValueError(
                f"Unsupported data file type: {suffix!r}  (use .npz or .csv)"
            )

        self.time: np.ndarray = self.signals["time"]
        self.n_frames: int = len(self.time)

        # all signal keys available for plot dropdowns (exclude "time")
        self.signal_names: list[str] = sorted(
            k for k in self.signals if k != "time"
        )

    def get_signal(self, name: str) -> np.ndarray:
        """Return signal array by name; raises KeyError if missing."""
        return self.signals[name]


# ══════════════════════════════════════════════════════════════════════════════
# 2.  SCENE  (geometry builder + per-frame updater)
#     Wraps the logic from run_visual.py without off-screen rendering.
# ══════════════════════════════════════════════════════════════════════════════

class VisualScene:
    """
    Owns all PyVista actors.  Attached to a live QtInteractor plotter.

    Usage
    -----
        scene = VisualScene(data, plotter)
        scene.build()          # once, after plotter is shown
        scene.update(frame_i)  # called every frame
    """

    def __init__(self, data: SimData, plotter: QtInteractor) -> None:
        self.data    = data
        self.plotter = plotter
        self.cfg     = data.cfg

        # internal state built by self.build()
        self._points:        dict[str, np.ndarray] = {}
        self._joint_actors:  dict[str, Any]        = {}
        self._link_actors:   list[dict[str, Any]]  = []
        self._tire_actors:   list[dict[str, Any]]  = []
        self._vector_actors: list[dict[str, Any]]  = []

        # camera config (populated in _setup_camera)
        self._cam_attach:   str | None       = None
        self._cam_fwd_pair: list[str] | None = None
        self._cam_origin_offset: np.ndarray  = np.zeros(3)
        self._cam_back:   float = 2.5
        self._cam_height: float = 1.5

        # camera state
        self._camera_mode: str = "follow"
        self._manual_camera_state: dict[str, Any] | None = None

        # import vtk here so the rest of the class can use it
        import vtk as _vtk
        self._vtk = _vtk

    # ── helpers (ported from run_visual.py) ───────────────────────────────────

    @staticmethod
    def _safe_normalize(v: np.ndarray, fallback: np.ndarray | None = None) -> np.ndarray:
        if fallback is None:
            fallback = np.array([1.0, 0.0, 0.0])
        n = np.linalg.norm(v)
        return v / n if n >= 1e-8 else fallback.copy()

    @staticmethod
    def _make_frame_from_x(x_axis: np.ndarray) -> np.ndarray:
        x   = VisualScene._safe_normalize(x_axis)
        ref = np.array([0.0, 0.0, 1.0])
        if abs(np.dot(x, ref)) > 0.95:
            ref = np.array([0.0, 1.0, 0.0])
        y = VisualScene._safe_normalize(np.cross(ref, x),
                                        fallback=np.array([0.0, 1.0, 0.0]))
        z = VisualScene._safe_normalize(np.cross(x, y),
                                        fallback=np.array([0.0, 0.0, 1.0]))
        return np.column_stack((x, y, z))

    @staticmethod
    def _make_link_transform(p1: np.ndarray, p2: np.ndarray) -> np.ndarray:
        d = p2 - p1
        L = np.linalg.norm(d)
        T = np.eye(4)
        if L < 1e-10:
            T[:3, 3] = p1
            return T
        R = VisualScene._make_frame_from_x(d)
        S = np.diag([L, 1.0, 1.0])
        T[:3, :3] = R @ S
        T[:3, 3]  = 0.5 * (p1 + p2)
        return T

    def _set_vtk_matrix(self, mat: Any, T: np.ndarray) -> None:
        for i in range(4):
            for j in range(4):
                mat.SetElement(i, j, float(T[i, j]))

    # ------------------------------------------------------------------
    def build(self) -> None:
        """Parse cfg, pre-load point arrays, create all actors."""
        self._build_points()
        self._build_joints()
        self._build_links()
        self._build_tires()
        self._build_vectors()
        self._setup_camera()

    # ------------------------------------------------------------------
    def _build_points(self) -> None:
        """Stack x/y/z signal columns → self._points[name] shape (N, 3)."""
        sig = self.data.signals
        input_stride = int(self.cfg.get("render", {}).get("input_stride", 1))
        for name, cols in self.cfg["geometry"]["points"].items():
            arr = np.stack([np.asarray(sig[c], dtype=float) for c in cols], axis=1)
            if input_stride > 1:
                arr = arr[::input_stride]
            self._points[name] = arr

    # ------------------------------------------------------------------
    def _build_joints(self) -> None:
        """One sphere actor per point."""
        joint_cfg   = self.cfg.get("style", {}).get("joints", {})
        radius      = float(joint_cfg.get("radius", 0.02))
        color       = joint_cfg.get("color", "red")
        joint_mesh  = pv.Sphere(radius=radius)
        for name in self._points:
            actor = self.plotter.add_mesh(joint_mesh.copy(), color=color)
            self._joint_actors[name] = actor

    # ------------------------------------------------------------------
    def _build_links(self) -> None:
        """One unit cylinder per link pair, transformed each frame."""
        link_style   = self.cfg.get("style", {}).get("links", {})
        default_link = link_style.get("default", {"radius": 0.01, "color": "black"})
        group_styles = link_style.get("groups", {})

        for group, group_links in self.cfg["geometry"]["links"].items():
            style  = group_styles.get(group, default_link)
            radius = float(style["radius"])
            color  = style["color"]

            link_mesh = pv.Cylinder(
                center=(0.0, 0.0, 0.0),
                direction=(1.0, 0.0, 0.0),
                radius=radius,
                height=1.0,
                resolution=24,
            )

            for a, b in group_links:
                actor   = self.plotter.add_mesh(link_mesh.copy(), color=color,
                                                smooth_shading=False)
                vtk_mat = self._vtk.vtkMatrix4x4()
                actor.SetUserMatrix(vtk_mat)
                self._link_actors.append({"a": a, "b": b,
                                          "actor": actor, "vtk_mat": vtk_mat})

    # ------------------------------------------------------------------
    def _build_tires(self) -> None:
        """Outer tyre + silver rim cylinders per tire entry."""
        sig          = self.data.signals
        input_stride = int(self.cfg.get("render", {}).get("input_stride", 1))

        for tire_cfg in self.cfg["geometry"].get("tires", {}).values():
            x_arr = np.stack([np.asarray(sig[c], dtype=float)
                              for c in tire_cfg["x"]], axis=1)
            y_arr = np.stack([np.asarray(sig[c], dtype=float)
                              for c in tire_cfg["y"]], axis=1)
            if input_stride > 1:
                x_arr = x_arr[::input_stride]
                y_arr = y_arr[::input_stride]

            theta_series = np.zeros(len(x_arr), dtype=float)
            center_name = tire_cfg["center"]
            center_pts = self._points[center_name]
            for i in range(1, len(x_arr)):
                dt = float(self.data.time[i] - self.data.time[i - 1])
                C_prev = center_pts[i - 1]
                C_now = center_pts[i]
                x_now = self._safe_normalize(x_arr[i])
                v = (C_now - C_prev) / max(dt, 1e-6)
                theta_series[i] = theta_series[i - 1] + float(np.dot(v, x_now)) / float(tire_cfg["radius"]) * dt

            td: dict[str, Any] = {
                "center": tire_cfg["center"],
                "x": x_arr,
                "y": y_arr,
                "theta_series": theta_series,
                "radius": float(tire_cfg["radius"]),
                "width": float(tire_cfg["width"]),
            }

            outer = self.plotter.add_mesh(
                pv.Cylinder(direction=(0, 1, 0),
                            radius=td["radius"], height=td["width"],
                            resolution=48),
                color=(0.1, 0.1, 0.1), opacity=0.6, smooth_shading=False,
            )
            rim = self.plotter.add_mesh(
                pv.Cylinder(direction=(0, 1, 0),
                            radius=0.6 * td["radius"], height=0.9 * td["width"],
                            resolution=32),
                color=(0.8, 0.8, 0.8), opacity=0.6, smooth_shading=False,
            )

            vtk_outer = self._vtk.vtkMatrix4x4()
            vtk_rim   = self._vtk.vtkMatrix4x4()
            outer.SetUserMatrix(vtk_outer)
            rim.SetUserMatrix(vtk_rim)

            self._tire_actors.append({
                "data":      td,
                "outer":     outer,  "rim":     rim,
                "vtk_outer": vtk_outer, "vtk_rim": vtk_rim,
                "theta":     0.0,
            })

    # ------------------------------------------------------------------
    def _build_vectors(self) -> None:
        """Arrow actor per vector entry, collapsed to zero when magnitude < 1e-6."""
        sig          = self.data.signals
        input_stride = int(self.cfg.get("render", {}).get("input_stride", 1))

        for group in self.cfg["geometry"].get("vectors", {}).values():
            for name, vcfg in group.items():
                comps = []
                for c in vcfg["direction"]:
                    if isinstance(c, str):
                        comps.append(np.asarray(sig[c], dtype=float))
                    else:
                        comps.append(np.full(self.data.n_frames, float(c)))
                dir_arr = np.stack(comps, axis=1)
                if input_stride > 1:
                    dir_arr = dir_arr[::input_stride]

                arrow = self.plotter.add_mesh(
                    pv.Arrow(start=(0, 0, 0), direction=(1, 0, 0),
                             tip_length=0.3,
                             tip_radius=float(vcfg.get("tip_radius", 0.04)),
                             shaft_radius=float(vcfg.get("shaft_radius", 0.02))),
                    color=vcfg.get("color", "black"),
                )
                vtk_mat = self._vtk.vtkMatrix4x4()
                arrow.SetUserMatrix(vtk_mat)

                self._vector_actors.append({
                    "name":      name,
                    "origin":    vcfg["origin"],
                    "direction": dir_arr,
                    "scale":     float(vcfg.get("scale", 1.0)),
                    "actor":     arrow,
                    "vtk_mat":   vtk_mat,
                })

    # ------------------------------------------------------------------
    def _setup_camera(self) -> None:
        """Read camera config; fall back to reset_camera()."""
        cam_cfg = self.cfg.get("camera", {})
        self._cam_attach    = cam_cfg.get("attach_to", None)
        self._cam_fwd_pair  = cam_cfg.get("forward_pair", None)

        oo = cam_cfg.get("origin_offset", {})
        self._cam_origin_offset = np.array(
            [oo.get("x", 0.0), oo.get("y", 0.0), oo.get("z", 0.0)], dtype=float
        )
        offs = cam_cfg.get("camera_offsets", {})
        self._cam_back   = float(offs.get("back",   2.5))
        self._cam_height = float(offs.get("height", 1.5))

        self.plotter.camera.clipping_range = (0.01, 2000)
        self.plotter.reset_camera()

    # ------------------------------------------------------------------
    # Per-frame update
    # ------------------------------------------------------------------
    def _time_bracket(self, sim_time: float) -> tuple[int, int, float]:
        time_arr = self.data.time
        if sim_time <= float(time_arr[0]):
            return 0, 0, 0.0
        if sim_time >= float(time_arr[-1]):
            last = len(time_arr) - 1
            return last, last, 0.0
        i1 = int(np.searchsorted(time_arr, sim_time, side="right"))
        i0 = max(0, i1 - 1)
        t0 = float(time_arr[i0])
        t1 = float(time_arr[i1])
        alpha = 0.0 if t1 <= t0 else (float(sim_time) - t0) / (t1 - t0)
        return i0, i1, float(np.clip(alpha, 0.0, 1.0))

    @staticmethod
    def _lerp_vec(a: np.ndarray, b: np.ndarray, alpha: float) -> np.ndarray:
        return (1.0 - alpha) * np.asarray(a, dtype=float) + alpha * np.asarray(b, dtype=float)

    def _interp_points(self, name: str, i0: int, i1: int, alpha: float) -> np.ndarray:
        pts = self._points[name]
        if i0 == i1:
            return pts[i0]
        return self._lerp_vec(pts[i0], pts[i1], alpha)

    def _interp_array3(self, arr: np.ndarray, i0: int, i1: int, alpha: float) -> np.ndarray:
        if i0 == i1:
            return arr[i0]
        return self._lerp_vec(arr[i0], arr[i1], alpha)

    def _interp_scalar_arr(self, arr: np.ndarray, i0: int, i1: int, alpha: float) -> float:
        if i0 == i1:
            return float(arr[i0])
        return float((1.0 - alpha) * float(arr[i0]) + alpha * float(arr[i1]))

    def update(self, frame_i: int) -> None:
        self.update_time(float(self.data.time[frame_i]))

    def update_time(self, sim_time: float) -> None:
        """Move every actor to its interpolated position at sim_time."""
        i0, i1, alpha = self._time_bracket(sim_time)
        self._update_joints_interp(i0, i1, alpha)
        self._update_links_interp(i0, i1, alpha)
        self._update_tires_interp(i0, i1, alpha)
        self._update_vectors_interp(i0, i1, alpha)
        self._update_camera_interp(i0, i1, alpha)

    def _update_joints_interp(self, i0: int, i1: int, alpha: float) -> None:
        for name, actor in self._joint_actors.items():
            actor.SetPosition(*self._interp_points(name, i0, i1, alpha))

    def _update_links_interp(self, i0: int, i1: int, alpha: float) -> None:
        for link in self._link_actors:
            p1 = self._interp_points(link["a"], i0, i1, alpha)
            p2 = self._interp_points(link["b"], i0, i1, alpha)
            T  = self._make_link_transform(p1, p2)
            self._set_vtk_matrix(link["vtk_mat"], T)
            link["actor"].Modified()

    def _update_tires_interp(self, i0: int, i1: int, alpha: float) -> None:
        for tire in self._tire_actors:
            td = tire["data"]
            C = self._interp_points(td["center"], i0, i1, alpha)
            x = self._safe_normalize(self._interp_array3(td["x"], i0, i1, alpha))
            y_raw = self._interp_array3(td["y"], i0, i1, alpha)
            y = self._safe_normalize(
                y_raw - np.dot(y_raw, x) * x,
                fallback=np.array([0.0, 1.0, 0.0]),
            )
            z = self._safe_normalize(np.cross(x, y), fallback=np.array([0.0, 0.0, 1.0]))

            theta = self._interp_scalar_arr(td["theta_series"], i0, i1, alpha)
            Ry = np.array([
                [ np.cos(theta), 0.0, np.sin(theta)],
                [0.0,            1.0, 0.0           ],
                [-np.sin(theta), 0.0, np.cos(theta) ],
            ])
            R = np.column_stack((x, y, z)) @ Ry

            T = np.eye(4)
            T[:3, :3] = R
            T[:3, 3] = C

            self._set_vtk_matrix(tire["vtk_outer"], T)
            tire["outer"].Modified()
            self._set_vtk_matrix(tire["vtk_rim"], T)
            tire["rim"].Modified()

    def _update_vectors_interp(self, i0: int, i1: int, alpha: float) -> None:
        for v in self._vector_actors:
            p = self._interp_points(v["origin"], i0, i1, alpha)
            d = self._interp_array3(v["direction"], i0, i1, alpha)
            L = np.linalg.norm(d)

            if L < 1e-6:
                T = np.eye(4)
                T[:3, :3] = 0.0
                T[:3, 3] = p
            else:
                R = self._make_frame_from_x(d / L)
                S = np.diag([L * v["scale"], 1.0, 1.0])
                T = np.eye(4)
                T[:3, :3] = R @ S
                T[:3, 3] = p

            self._set_vtk_matrix(v["vtk_mat"], T)
            v["actor"].Modified()

    def _get_camera_target(self, i: int) -> np.ndarray | None:
        if self._cam_attach not in self._points:
            return None
        if not self._cam_fwd_pair:
            return None

        p1 = self._points[self._cam_fwd_pair[0]][i]
        p2 = self._points[self._cam_fwd_pair[1]][i]

        f  = self._safe_normalize(np.array([p2[0]-p1[0], p2[1]-p1[1], 0.0]))
        up = np.array([0.0, 0.0, 1.0])
        r  = self._safe_normalize(np.cross(f, up))
        up = self._safe_normalize(np.cross(r, f))
        R_vehicle = np.column_stack((f, r, up))

        return self._points[self._cam_attach][i] + R_vehicle @ self._cam_origin_offset

    def _camera_target_interp(self, i0: int, i1: int, alpha: float) -> tuple[np.ndarray | None, np.ndarray | None]:
        if self._cam_attach not in self._points or not self._cam_fwd_pair:
            return None, None

        p1 = self._interp_points(self._cam_fwd_pair[0], i0, i1, alpha)
        p2 = self._interp_points(self._cam_fwd_pair[1], i0, i1, alpha)

        f = self._safe_normalize(np.array([p2[0] - p1[0], p2[1] - p1[1], 0.0]))
        up = np.array([0.0, 0.0, 1.0])
        r = self._safe_normalize(np.cross(f, up))
        up = self._safe_normalize(np.cross(r, f))
        R_vehicle = np.column_stack((f, r, up))
        target = self._interp_points(self._cam_attach, i0, i1, alpha) + R_vehicle @ self._cam_origin_offset
        return target, R_vehicle

    def _update_camera_interp(self, i0: int, i1: int, alpha: float) -> None:
        """Update camera for follow mode, or preserve the current manual view relative to the car."""
        target, R_vehicle = self._camera_target_interp(i0, i1, alpha)
        if target is None or R_vehicle is None:
            return

        if self._camera_mode == "manual":
            if not self._manual_camera_state:
                return
            cam = self.plotter.camera
            pos_offset = np.asarray(self._manual_camera_state["position_offset"], dtype=float)
            focal_offset = np.asarray(self._manual_camera_state["focal_offset"], dtype=float)
            up = np.asarray(self._manual_camera_state["up"], dtype=float)
            cam.position = tuple(target + pos_offset)
            cam.focal_point = tuple(target + focal_offset)
            cam.up = tuple(up)
            cam.view_angle = float(self._manual_camera_state["view_angle"])
            if hasattr(cam, "parallel_projection"):
                cam.parallel_projection = bool(self._manual_camera_state["parallel_projection"])
            if hasattr(cam, "parallel_scale"):
                cam.parallel_scale = float(self._manual_camera_state["parallel_scale"])
            return

        C = target
        cam_offset_body = np.array([-self._cam_back, 0.0, self._cam_height])
        cam_pos = C + R_vehicle @ cam_offset_body

        self.plotter.camera.position = cam_pos
        self.plotter.camera.focal_point = C
        self.plotter.camera.up = R_vehicle[:, 2]

    def _remember_manual_camera(self, frame_i: int | None = None) -> None:
        if frame_i is None:
            frame_i = 0
        cam = self.plotter.camera
        target = self._get_camera_target(frame_i)
        if target is None:
            target = np.asarray(cam.focal_point, dtype=float)
        pos = np.asarray(cam.position, dtype=float)
        focal = np.asarray(cam.focal_point, dtype=float)
        self._manual_camera_state = {
            "position_offset": tuple(pos - target),
            "focal_offset": tuple(focal - target),
            "up": tuple(cam.up),
            "view_angle": float(cam.view_angle),
            "parallel_scale": float(getattr(cam, "parallel_scale", 1.0)),
            "parallel_projection": bool(getattr(cam, "parallel_projection", False)),
        }

    def _set_manual_view(self, view_func: Callable[[], Any]) -> None:
        self._camera_mode = "manual"
        view_func()
        self._remember_manual_camera(0)

    def _set_manual_view_with_azimuth(
        self,
        view_func: Callable[[], Any],
        azimuth: float,
    ) -> None:
        self._camera_mode = "manual"
        view_func()
        self.plotter.camera.azimuth = azimuth
        self._remember_manual_camera(0)

    def _set_flipped_isometric_view(self) -> None:
        self._camera_mode = "manual"
        self.plotter.view_isometric()
        self.plotter.camera.azimuth = self.plotter.camera.azimuth + 180
        self._remember_manual_camera(0)

    # ------------------------------------------------------------------
    # Camera preset helpers  (called from toolbar buttons)
    # ------------------------------------------------------------------
    def set_view_top(self) -> None:
        self._set_manual_view(self.plotter.view_xy)

    def set_view_rear(self) -> None:
        self._set_manual_view(self.plotter.view_yz)

    def set_view_front(self) -> None:
        self._set_manual_view_with_azimuth(self.plotter.view_yz, 180.0)

    def set_view_right(self) -> None:
        self._set_manual_view_with_azimuth(self.plotter.view_xz, 180.0)

    def set_view_left(self) -> None:
        self._set_manual_view(self.plotter.view_xz)

    def set_view_iso(self) -> None:
        self._set_flipped_isometric_view()

    def set_view_free(self) -> None:
        self._camera_mode = "manual"
        self._remember_manual_camera(0)

    def rotate_x(self, deg: float) -> None:
        self._camera_mode = "manual"
        self.plotter.camera.elevation += deg
        self._remember_manual_camera()

    def rotate_y(self, deg: float) -> None:
        self._camera_mode = "manual"
        self.plotter.camera.azimuth   += deg
        self._remember_manual_camera()

    def rotate_z(self, deg: float) -> None:
        self._camera_mode = "manual"
        self.plotter.camera.roll      += deg
        self._remember_manual_camera()

    def set_focus_point(self, name: str) -> None:
        """
        Override camera follow target at runtime (toolbar Focus dropdown).
        'Whole car' -> restores original YAML attach_to.
        Any other name -> follow that joint instead.
        """
        cam_cfg = self.cfg.get("camera", {})
        if name == "Whole car":
            self._cam_attach = cam_cfg.get("attach_to", None)
        elif name in self._points:
            self._cam_attach = name
        if self._camera_mode == "manual":
            self._remember_manual_camera()


# ══════════════════════════════════════════════════════════════════════════════
# 3.  ANIMATION WORKER  (QThread)
#     Drives the frame counter at the requested playback speed.
#     Never touches Qt widgets — only emits signals.
# ══════════════════════════════════════════════════════════════════════════════

class AnimationWorker(QThread):
    """
    Emits frame_ready(int) at ~60 Hz while playing.
    Main thread connects frame_ready → update scene + plots + UI.

    Signals
    -------
    frame_ready(int)   : current frame index
    playback_done()    : reached end of data
    """

    frame_ready   = pyqtSignal(int, float)
    playback_done = pyqtSignal()

    TICK_MS = 8   # ~125 Hz internal tick for smoother interpolation

    def __init__(self, n_frames: int, time_arr: np.ndarray) -> None:
        super().__init__()
        self.n_frames  = n_frames
        self.time_arr  = time_arr
        self._playing  = False
        self._speed    = 1.0          # playback speed multiplier
        self._frame    = 0            # current frame
        self._sim_time = float(time_arr[0])
        self._stop_req = False

    # ------------------------------------------------------------------
    def run(self) -> None:
        """Thread entry point — internal tick loop."""
        import time
        t_last = time.perf_counter()

        while not self._stop_req:
            time.sleep(self.TICK_MS / 1000)
            now = time.perf_counter()

            if not self._playing:
                t_last = now
                continue

            dt_wall = now - t_last
            t_last = now

            # advance continuous sim-time by wall-clock × speed
            dt_sim = dt_wall * self._speed
            self._sim_time = min(self._sim_time + dt_sim, float(self.time_arr[-1]))

            # floor frame for slider/labels; scene uses continuous time interpolation
            idx = int(np.searchsorted(self.time_arr, self._sim_time, side="right") - 1)
            idx = max(0, min(idx, self.n_frames - 1))
            self._frame = idx
            self.frame_ready.emit(self._frame, float(self._sim_time))

            if self._sim_time >= float(self.time_arr[-1]) - 1e-12:
                self._playing = False
                self.playback_done.emit()

    # ------------------------------------------------------------------
    def play(self) -> None:
        self._sim_time = float(self.time_arr[self._frame])
        self._playing = True

    def pause(self) -> None:
        self._playing = False

    def stop(self) -> None:
        self._stop_req = True

    def seek(self, frame: int) -> None:
        self._frame = max(0, min(frame, self.n_frames - 1))
        self._sim_time = float(self.time_arr[self._frame])
        self.frame_ready.emit(self._frame, self._sim_time)

    def set_speed(self, speed: float) -> None:
        self._speed = speed

    @property
    def is_playing(self) -> bool:
        return self._playing


# ══════════════════════════════════════════════════════════════════════════════
# 4.  PLOT PANEL  (right-side Matplotlib panel)
#     Supports N user-configured subplots, each with X/Y dropdowns.
# ══════════════════════════════════════════════════════════════════════════════

class PlotRow(QWidget):
    """
    One subplot row: [X dropdown] vs [Y dropdown] [remove button] + canvas.
    Owns its own Figure / Axes.
    """

    removed = pyqtSignal(object)   # emits self when × clicked

    def __init__(self, data: SimData, parent: QWidget | None = None) -> None:
        super().__init__(parent)
        self.data = data

        # ── dropdowns ────────────────────────────────────────────────────
        self._x_combo = QComboBox()
        self._y_combo = QComboBox()
        self._populate_combos()

        self._x_combo.currentTextChanged.connect(self._replot)
        self._y_combo.currentTextChanged.connect(self._replot)

        # ── figure ───────────────────────────────────────────────────────
        self._fig = Figure(figsize=(4, 1.8), tight_layout=True)
        self._ax  = self._fig.add_subplot(111)
        self._canvas = FigureCanvas(self._fig)
        self._canvas.setSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Fixed)
        self._canvas.setFixedHeight(160)

        # cursor vertical line
        self._cursor_line = self._ax.axvline(
            self.data.time[0], color="#E24B4A", linewidth=1.0, alpha=0.8
        )

        # throttle: only redraw canvas at most every 33 ms (~30 fps)
        self._last_cursor_draw: float = 0.0

        # ── remove button ─────────────────────────────────────────────────
        rm_btn = QPushButton("×")
        rm_btn.setFixedSize(20, 20)
        rm_btn.clicked.connect(lambda: self.removed.emit(self))

        # ── header row layout ─────────────────────────────────────────────
        hdr = QHBoxLayout()
        hdr.addWidget(QLabel("X"))
        hdr.addWidget(self._x_combo)
        hdr.addWidget(QLabel("vs"))
        hdr.addWidget(self._y_combo)
        hdr.addStretch()
        hdr.addWidget(rm_btn)

        # ── main layout ───────────────────────────────────────────────────
        vbox = QVBoxLayout(self)
        vbox.setContentsMargins(4, 4, 4, 4)
        vbox.setSpacing(2)
        vbox.addLayout(hdr)
        vbox.addWidget(self._canvas)

        self._replot()

    # ------------------------------------------------------------------
    def _populate_combos(self) -> None:
        """Fill X/Y dropdowns: X defaults to 'time', Y to first signal."""
        choices = ["time"] + self.data.signal_names

        self._x_combo.blockSignals(True)
        self._y_combo.blockSignals(True)

        self._x_combo.addItems(choices)
        self._y_combo.addItems(choices)

        self._x_combo.setCurrentText("time")
        if self.data.signal_names:
            self._y_combo.setCurrentIndex(1)   # first real signal

        self._x_combo.blockSignals(False)
        self._y_combo.blockSignals(False)

    # ------------------------------------------------------------------
    def _replot(self) -> None:
        """Redraw axes when user changes dropdown selection."""
        x_name = self._x_combo.currentText()
        y_name = self._y_combo.currentText()

        x = self.data.time if x_name == "time" else self.data.get_signal(x_name)
        y = self.data.get_signal(y_name) if y_name != "time" else self.data.time

        self._ax.cla()
        self._ax.plot(x, y, linewidth=1.2, color="#378ADD")
        self._ax.set_xlabel(x_name, fontsize=8)
        self._ax.set_ylabel(y_name, fontsize=8)
        self._ax.tick_params(labelsize=7)
        self._ax.grid(True, linestyle="--", linewidth=0.4, alpha=0.5)
        self._fig.tight_layout()

        # re-add cursor line after cla()
        self._cursor_line = self._ax.axvline(
            self.data.time[0], color="#E24B4A", linewidth=1.0, alpha=0.8
        )

        self._canvas.draw_idle()

    # ------------------------------------------------------------------
    def update_cursor_time(self, sim_time: float) -> None:
        """Move cursor to current simulation time. Called every frame — throttled to ~30 fps."""
        import time as _time
        now = _time.perf_counter()
        if now - self._last_cursor_draw < 0.033:
            return
        self._last_cursor_draw = now

        x_name = self._x_combo.currentText()

        if x_name == "time":
            self._cursor_line.set_xdata([float(sim_time)])
        else:
            val = float(np.interp(sim_time, self.data.time, self.data.get_signal(x_name)))
            self._cursor_line.set_xdata([val])

        self._canvas.draw_idle()


# ──────────────────────────────────────────────────────────────────────────────

class PlotPanel(QWidget):
    """
    Scrollable container of PlotRow widgets.
    Has an '+ Add plot' button at the top.
    """

    def __init__(self, data: SimData, parent: QWidget | None = None) -> None:
        super().__init__(parent)
        self.data = data
        self._rows: list[PlotRow] = []

        # ── add-plot button ───────────────────────────────────────────────
        add_btn = QPushButton("+ Add plot")
        add_btn.clicked.connect(self.add_plot)

        # ── scroll area ───────────────────────────────────────────────────
        self._scroll_content = QWidget()
        self._scroll_layout  = QVBoxLayout(self._scroll_content)
        self._scroll_layout.setContentsMargins(0, 0, 0, 0)
        self._scroll_layout.setSpacing(4)
        self._scroll_layout.addStretch()   # pushes rows to top

        scroll = QScrollArea()
        scroll.setWidgetResizable(True)
        scroll.setWidget(self._scroll_content)
        scroll.setFrameShape(QFrame.Shape.NoFrame)

        # ── main layout ───────────────────────────────────────────────────
        vbox = QVBoxLayout(self)
        vbox.setContentsMargins(4, 4, 4, 4)
        vbox.addWidget(add_btn)
        vbox.addWidget(scroll)

        # start with two default plots
        self.add_plot()
        self.add_plot()

    # ------------------------------------------------------------------
    def add_plot(self) -> None:
        row = PlotRow(self.data)
        row.removed.connect(self._remove_row)
        # insert before the trailing stretch
        insert_idx = self._scroll_layout.count() - 1
        self._scroll_layout.insertWidget(insert_idx, row)
        self._rows.append(row)

    # ------------------------------------------------------------------
    def _remove_row(self, row: PlotRow) -> None:
        if row in self._rows:
            self._rows.remove(row)
            self._scroll_layout.removeWidget(row)
            row.deleteLater()

    # ------------------------------------------------------------------
    def update_cursor_time(self, sim_time: float) -> None:
        for row in self._rows:
            row.update_cursor_time(sim_time)


# ══════════════════════════════════════════════════════════════════════════════
# 5.  TIMELINE BAR  (bottom strip)
# ══════════════════════════════════════════════════════════════════════════════

class TimelineBar(QWidget):
    """
    Bottom playback controls:
      [|<] [<] [▶/‖] [>] [>|]   ────slider────   t = 0.000 / 2.000 s
      Speed: 0.25× 0.5× 1× 2× 4×
    """

    # signals up to MainWindow
    play_requested  = pyqtSignal()
    pause_requested = pyqtSignal()
    seek_requested  = pyqtSignal(int)      # frame index
    speed_changed   = pyqtSignal(float)

    SPEEDS = [0.25, 0.5, 1.0, 2.0, 4.0]

    def __init__(self, n_frames: int, time_arr: np.ndarray,
                 parent: QWidget | None = None) -> None:
        super().__init__(parent)
        self.n_frames  = n_frames
        self.time_arr  = time_arr
        self._playing  = False

        # ── transport buttons ─────────────────────────────────────────────
        self._btn_start  = QPushButton("|◀")
        self._btn_back   = QPushButton("◀")
        self._btn_play   = QPushButton("▶")
        self._btn_fwd    = QPushButton("▶")
        self._btn_end    = QPushButton("▶|")

        for b in (self._btn_start, self._btn_back,
                  self._btn_play, self._btn_fwd, self._btn_end):
            b.setFixedSize(32, 26)

        # ── time slider ───────────────────────────────────────────────────
        self._slider = QSlider(Qt.Orientation.Horizontal)
        self._slider.setRange(0, n_frames - 1)
        self._slider.setValue(0)

        self._time_label = QLabel("t = 0.000 / {:.3f} s".format(time_arr[-1]))
        self._time_label.setFixedWidth(130)

        # ── speed buttons ─────────────────────────────────────────────────
        speed_label = QLabel("Speed:")
        self._speed_btns: dict[float, QPushButton] = {}
        for s in self.SPEEDS:
            lbl = f"{s}×" if s != 1.0 else "1×"
            btn = QPushButton(lbl)
            btn.setFixedSize(40, 22)
            btn.setCheckable(True)
            btn.clicked.connect(lambda checked, spd=s: self._on_speed(spd))
            self._speed_btns[s] = btn

        self._speed_btns[1.0].setChecked(True)

        # ── top row layout ────────────────────────────────────────────────
        top = QHBoxLayout()
        for b in (self._btn_start, self._btn_back,
                  self._btn_play, self._btn_fwd, self._btn_end):
            top.addWidget(b)
        top.addWidget(self._slider, stretch=1)
        top.addWidget(self._time_label)

        # ── bottom row layout ─────────────────────────────────────────────
        bot = QHBoxLayout()
        bot.addWidget(speed_label)
        for btn in self._speed_btns.values():
            bot.addWidget(btn)
        bot.addStretch()

        # ── main layout ───────────────────────────────────────────────────
        vbox = QVBoxLayout(self)
        vbox.setContentsMargins(6, 4, 6, 4)
        vbox.setSpacing(2)
        vbox.addLayout(top)
        vbox.addLayout(bot)

        # ── connect ───────────────────────────────────────────────────────
        self._btn_play.clicked.connect(self._toggle_play)
        self._btn_back.clicked.connect(lambda: self._step(-1))
        self._btn_fwd.clicked.connect(lambda:  self._step(+1))
        self._btn_start.clicked.connect(lambda: self._jump(0))
        self._btn_end.clicked.connect(lambda:   self._jump(n_frames - 1))
        self._slider.sliderMoved.connect(self._on_slider_moved)

    # ------------------------------------------------------------------
    def _toggle_play(self) -> None:
        if self._playing:
            self._playing = False
            self._btn_play.setText("▶")
            self.pause_requested.emit()
        else:
            self._playing = True
            self._btn_play.setText("‖")
            self.play_requested.emit()

    def _step(self, delta: int) -> None:
        new_frame = max(0, min(self._slider.value() + delta, self.n_frames - 1))
        self._slider.setValue(new_frame)
        self.seek_requested.emit(new_frame)

    def _jump(self, frame: int) -> None:
        self._slider.setValue(frame)
        self.seek_requested.emit(frame)

    def _on_slider_moved(self, frame: int) -> None:
        self.seek_requested.emit(frame)

    def _on_speed(self, speed: float) -> None:
        for s, btn in self._speed_btns.items():
            btn.setChecked(s == speed)
        self.speed_changed.emit(speed)

    # ------------------------------------------------------------------
    def sync_time(self, frame_i: int, sim_time: float | None = None) -> None:
        """Called by main window every frame to keep slider + label in sync."""
        self._slider.blockSignals(True)
        self._slider.setValue(frame_i)
        self._slider.blockSignals(False)
        t = self.time_arr[frame_i] if sim_time is None else float(sim_time)
        self._time_label.setText(f"t = {t:.3f} / {self.time_arr[-1]:.3f} s")

    def on_playback_done(self) -> None:
        """Worker signals end-of-data — reset play button."""
        self._playing = False
        self._btn_play.setText("▶")


# ══════════════════════════════════════════════════════════════════════════════
# 6.  TOOLBAR  (view presets, focus, rotate)
# ══════════════════════════════════════════════════════════════════════════════

class ViewToolbar(QToolBar):
    """
    Horizontal toolbar with:
      • View preset buttons  (Top / Front / Rear / Side L / Side R / ISO / Free)
      • Focus point dropdown (joint names from YAML)
      • Rotate ±15° per axis  (X / Y / Z)
      • Reset camera
    """

    # signals up to MainWindow → forwarded to VisualScene
    view_preset_requested = pyqtSignal(str)    # "top" | "front" | ...
    focus_changed         = pyqtSignal(str)    # joint name
    rotate_requested      = pyqtSignal(str, float)   # axis, degrees
    reset_camera          = pyqtSignal()

    PRESETS = ["Top", "Front", "Rear", "Side L", "Side R", "ISO", "Free"]
    AXES    = ["X", "Y", "Z"]
    STEP    = 15.0   # degrees per button press

    def __init__(self, data: SimData, parent: QWidget | None = None) -> None:
        super().__init__("View", parent)
        self.setMovable(False)
        self._data = data

        self._build_view_presets()
        self.addSeparator()
        self._build_focus_dropdown()
        self.addSeparator()
        self._build_rotate_controls()
        self.addSeparator()
        self._build_reset()

    # ------------------------------------------------------------------
    def _build_view_presets(self) -> None:
        lbl = QLabel("  View ")
        lbl.setStyleSheet("color: gray; font-size: 11px;")
        self.addWidget(lbl)

        for name in self.PRESETS:
            btn = QPushButton(name)
            btn.setFixedHeight(24)
            btn.clicked.connect(
                lambda _, n=name: self.view_preset_requested.emit(n.lower().replace(" ", "_"))
            )
            self.addWidget(btn)

    # ------------------------------------------------------------------
    def _build_focus_dropdown(self) -> None:
        lbl = QLabel("  Focus ")
        lbl.setStyleSheet("color: gray; font-size: 11px;")
        self.addWidget(lbl)

        combo = QComboBox()
        combo.addItem("Whole car")
        # populate from YAML geometry.points
        point_names = list(self._data.cfg.get("geometry", {}).get("points", {}).keys())
        combo.addItems(point_names)
        combo.setFixedWidth(130)
        combo.currentTextChanged.connect(self.focus_changed.emit)
        self.addWidget(combo)

    # ------------------------------------------------------------------
    def _build_rotate_controls(self) -> None:
        lbl = QLabel("  Rotate ")
        lbl.setStyleSheet("color: gray; font-size: 11px;")
        self.addWidget(lbl)

        for axis in self.AXES:
            ax_lbl = QLabel(axis)
            ax_lbl.setStyleSheet("font-size: 11px; font-weight: bold;")
            self.addWidget(ax_lbl)

            for sign, sym in [(-1, "−"), (+1, "+")]:
                btn = QPushButton(sym)
                btn.setFixedSize(22, 24)
                deg = sign * self.STEP
                btn.clicked.connect(
                    lambda _, a=axis.lower(), d=deg: self.rotate_requested.emit(a, d)
                )
                self.addWidget(btn)

    # ------------------------------------------------------------------
    def _build_reset(self) -> None:
        btn = QPushButton("Reset camera")
        btn.setFixedHeight(24)
        btn.clicked.connect(self.reset_camera.emit)
        self.addWidget(btn)


# ══════════════════════════════════════════════════════════════════════════════
# 7.  MAIN WINDOW
# ══════════════════════════════════════════════════════════════════════════════

class BobVisWindow(QMainWindow):
    """
    Top-level window.

    Layout
    ------
    ┌─ menubar ──────────────────────────────────────────┐
    ├─ ViewToolbar ──────────────────────────────────────┤
    ├─ QSplitter ─────────────────────────────────────── ┤
    │   ├─ QtInteractor (PyVista viewport)               │
    │   └─ PlotPanel (Matplotlib subplots)               │
    ├─ TimelineBar ──────────────────────────────────────┤
    └─ QStatusBar ───────────────────────────────────────┘
    """

    def __init__(self, data: SimData) -> None:
        super().__init__()
        self.data = data
        self.setWindowTitle("BobVis — Interactive Viewer")
        self.resize(1280, 760)

        self._current_frame = 0
        self._scene: VisualScene | None = None
        self._worker: AnimationWorker | None = None

        self._build_ui()
        self._wire_signals()
        self._start_worker()

        # build scene after the plotter widget is visible
        QTimer.singleShot(100, self._build_scene)

    # ──────────────────────────────────────────────────────────────────
    def _build_ui(self) -> None:

        # ── menu bar ──────────────────────────────────────────────────
        self._build_menu()

        # ── toolbar ───────────────────────────────────────────────────
        self._toolbar = ViewToolbar(self.data, self)
        self.addToolBar(self._toolbar)

        # ── PyVista viewport ─────────────────────────────────────────
        self._plotter = QtInteractor(self)
        self._plotter.set_background("white")
        self._plotter.add_axes()

        # ── plot panel ────────────────────────────────────────────────
        self._plot_panel = PlotPanel(self.data)

        # ── splitter ─────────────────────────────────────────────────
        splitter = QSplitter(Qt.Orientation.Horizontal)
        splitter.addWidget(self._plotter)
        splitter.addWidget(self._plot_panel)
        splitter.setStretchFactor(0, 3)   # viewport gets more space
        splitter.setStretchFactor(1, 1)

        # ── timeline ─────────────────────────────────────────────────
        self._timeline = TimelineBar(self.data.n_frames, self.data.time)

        # ── central widget ────────────────────────────────────────────
        central = QWidget()
        layout  = QVBoxLayout(central)
        layout.setContentsMargins(0, 0, 0, 0)
        layout.setSpacing(0)
        layout.addWidget(splitter, stretch=1)
        layout.addWidget(self._timeline)
        self.setCentralWidget(central)

        # ── status bar ────────────────────────────────────────────────
        self._status = QStatusBar()
        self.setStatusBar(self._status)
        self._status.showMessage("Ready")

    # ------------------------------------------------------------------
    def _build_menu(self) -> None:
        mb = self.menuBar()
        if mb is None:
            return

        # File
        file_menu = mb.addMenu("&File")
        if file_menu is not None:
            open_act = QAction("&Open…", self)
            open_act.setShortcut(QKeySequence.StandardKey.Open)

            export_act = QAction("Export MP4…", self)

            quit_act = QAction("&Quit", self)
            quit_act.setShortcut(QKeySequence.StandardKey.Quit)
            quit_act.triggered.connect(self.close)

            file_menu.addActions([open_act, export_act])
            file_menu.addSeparator()
            file_menu.addAction(quit_act)

        # View
        view_menu = mb.addMenu("&View")
        if view_menu is not None:
            reset_act = QAction("Reset camera", self)
            reset_act.setShortcut(QKeySequence("R"))
            reset_act.triggered.connect(self._reset_camera_from_menu)
            view_menu.addAction(reset_act)

        # Help
        help_menu = mb.addMenu("&Help")
        if help_menu is not None:
            about_act = QAction("About BobVis", self)
            help_menu.addAction(about_act)

    def _reset_camera_from_menu(self) -> None:
        if self._scene is not None:
            self._scene.set_view_iso()
            
    # ------------------------------------------------------------------
    def _wire_signals(self) -> None:
        """Connect toolbar + timeline signals to scene / worker."""

        # timeline → worker
        self._timeline.play_requested.connect(self._on_play)
        self._timeline.pause_requested.connect(self._on_pause)
        self._timeline.seek_requested.connect(self._on_seek)
        self._timeline.speed_changed.connect(self._on_speed_change)

        # toolbar → scene  (connected after scene is built in _build_scene)
        # (deferred — toolbar signals stored, connected once self._scene exists)

    # ------------------------------------------------------------------
    def _start_worker(self) -> None:
        worker = AnimationWorker(self.data.n_frames, self.data.time)
        worker.frame_ready.connect(self._on_frame)
        worker.playback_done.connect(self._timeline.on_playback_done)
        worker.start()
        self._worker = worker

    # ------------------------------------------------------------------
    def _build_scene(self) -> None:
        """Called once via QTimer after plotter is shown."""
        scene = VisualScene(self.data, self._plotter)
        scene.build()
        scene.update_time(float(self.data.time[0]))
        self._scene = scene

        self._timeline.sync_time(0, float(self.data.time[0]))
        self._plot_panel.update_cursor_time(float(self.data.time[0]))
        self._plotter.render()

        # now safe to wire toolbar → scene
        self._toolbar.view_preset_requested.connect(self._on_view_preset)
        self._toolbar.focus_changed.connect(scene.set_focus_point)
        self._toolbar.rotate_requested.connect(self._on_rotate)
        self._toolbar.reset_camera.connect(scene.set_view_iso)

        self._status.showMessage(
            f"Loaded  {self.data.n_frames} frames  |  "
            f"t = {self.data.time[0]:.3f} … {self.data.time[-1]:.3f} s"
        )

    # ──────────────────────────────────────────────────────────────────
    # Frame update  (all UI sync happens here)
    # ──────────────────────────────────────────────────────────────────
    def _on_frame(self, frame_i: int, sim_time: float) -> None:
        if self._scene is None:
            return

        self._current_frame = frame_i
        self._scene.update_time(sim_time)
        self._timeline.sync_time(frame_i, sim_time)
        self._plot_panel.update_cursor_time(sim_time)
        self._plotter.render()
        self._status.showMessage(
            f"Frame {frame_i}/{self.data.n_frames - 1}  |  "
            f"t = {float(sim_time):.4f} s"
        )

    # ──────────────────────────────────────────────────────────────────
    # Slot handlers
    # ──────────────────────────────────────────────────────────────────
    def _on_play(self) -> None:
        if self._worker is None:
            return

        self._worker.pause()
        if self._scene is not None and getattr(self._scene, "_camera_mode", "follow") == "manual":
            self._scene._remember_manual_camera(self._current_frame)
        self._worker.seek(0)
        self._worker.play()

    def _on_pause(self) -> None:
        if self._worker is not None:
            self._worker.pause()

    def _on_seek(self, frame: int) -> None:
        if self._worker is not None:
            self._worker.seek(frame)

    def _on_speed_change(self, speed: float) -> None:
        if self._worker is not None:
            self._worker.set_speed(speed)

    def _on_view_preset(self, preset: str) -> None:
        if self._scene is None:
            return

        dispatch: dict[str, Callable[[], None]] = {
            "top": self._scene.set_view_top,
            "front": self._scene.set_view_front,
            "rear": self._scene.set_view_rear,
            "side_l": self._scene.set_view_left,
            "side_r": self._scene.set_view_right,
            "iso": self._scene.set_view_iso,
            "free": self._scene.set_view_free,
        }
        view_func = dispatch.get(preset)
        if view_func is not None:
            view_func()

    def _on_rotate(self, axis: str, deg: float) -> None:
        if self._scene is None:
            return

        dispatch: dict[str, Callable[[float], None]] = {
            "x": self._scene.rotate_x,
            "y": self._scene.rotate_y,
            "z": self._scene.rotate_z,
        }
        rotate_func = dispatch.get(axis)
        if rotate_func is not None:
            rotate_func(deg)

    # ──────────────────────────────────────────────────────────────────
    def closeEvent(self, event: Any) -> None:
        if self._worker is not None:
            self._worker.stop()
            self._worker.wait(2000)
        self._plotter.close()
        super().closeEvent(event)


# ══════════════════════════════════════════════════════════════════════════════
# 8.  STARTUP FILE-PICKER DIALOG
# ══════════════════════════════════════════════════════════════════════════════

class FilePickerDialog(QDialog):
    """
    Small dialog shown on launch so the user can browse for:
      • a YAML visual-config file  (.yml / .yaml)
      • a simulation data file     (.npz  or  .csv)

    Accepts command-line paths as defaults so the old CLI workflow still works
    (pass them in via `yml_default` / `data_default`).
    """

    def __init__(
        self,
        yml_default:  str = "",
        data_default: str = "",
        parent: QWidget | None = None,
    ) -> None:
        super().__init__(parent)
        self.setWindowTitle("BobVis — Open files")
        self.setMinimumWidth(520)

        # ── YAML row ──────────────────────────────────────────────────────────
        self._yml_edit = QLineEdit(yml_default)
        self._yml_edit.setPlaceholderText("Select a .yml / .yaml config file…")
        yml_browse = QPushButton("Browse…")
        yml_browse.clicked.connect(self._browse_yml)

        yml_row = QHBoxLayout()
        yml_row.addWidget(self._yml_edit, stretch=1)
        yml_row.addWidget(yml_browse)

        # ── data row ──────────────────────────────────────────────────────────
        self._data_edit = QLineEdit(data_default)
        self._data_edit.setPlaceholderText("Select a .npz or .csv data file…")
        data_browse = QPushButton("Browse…")
        data_browse.clicked.connect(self._browse_data)

        data_row = QHBoxLayout()
        data_row.addWidget(self._data_edit, stretch=1)
        data_row.addWidget(data_browse)

        # ── form layout ───────────────────────────────────────────────────────
        form = QFormLayout()
        form.setContentsMargins(12, 12, 12, 4)
        form.setSpacing(8)
        form.addRow("YAML config:", yml_row)
        form.addRow("Data file:", data_row)

        # ── buttons ───────────────────────────────────────────────────────────
        btn_box = QDialogButtonBox(
            QDialogButtonBox.StandardButton.Ok |
            QDialogButtonBox.StandardButton.Cancel
        )
        btn_box.accepted.connect(self._on_accept)
        btn_box.rejected.connect(self.reject)

        # ── main layout ───────────────────────────────────────────────────────
        vbox = QVBoxLayout(self)
        vbox.addLayout(form)
        vbox.addSpacing(4)
        vbox.addWidget(btn_box)

    # ------------------------------------------------------------------
    def _browse_yml(self) -> None:
        path, _ = QFileDialog.getOpenFileName(
            self, "Select YAML config", "",
            "YAML files (*.yml *.yaml);;All files (*)"
        )
        if path:
            self._yml_edit.setText(path)

    def _browse_data(self) -> None:
        path, _ = QFileDialog.getOpenFileName(
            self, "Select data file", "",
            "Data files (*.npz *.csv);;NPZ files (*.npz);;CSV files (*.csv);;All files (*)"
        )
        if path:
            self._data_edit.setText(path)

    # ------------------------------------------------------------------
    def _on_accept(self) -> None:
        yml  = self._yml_edit.text().strip()
        data = self._data_edit.text().strip()
        missing = []
        if not yml:
            missing.append("YAML config")
        if not data:
            missing.append("data file")
        if missing:
            QMessageBox.warning(
                self, "Missing files",
                "Please select: " + " and ".join(missing)
            )
            return
        if not Path(yml).is_file():
            QMessageBox.warning(self, "File not found", f"Cannot find:\n{yml}")
            return
        if not Path(data).is_file():
            QMessageBox.warning(self, "File not found", f"Cannot find:\n{data}")
            return
        self.accept()

    # ------------------------------------------------------------------
    @property
    def yml_path(self) -> str:
        return self._yml_edit.text().strip()

    @property
    def data_path(self) -> str:
        return self._data_edit.text().strip()




# ══════════════════════════════════════════════════════════════════════════════
# 9.  ENTRY POINT
# ══════════════════════════════════════════════════════════════════════════════

def main() -> None:
    # ── optional CLI pre-fill (keeps old workflow as a shortcut) ──────────────
    parser = argparse.ArgumentParser(
        description="BobVis Interactive Viewer",
        epilog="If paths are omitted a file-picker dialog will appear on launch.",
    )
    parser.add_argument("yml", nargs="?", default="", help="Path to visual YAML config")
    parser.add_argument("data", nargs="?", default="", help="Path to .npz or .csv data file")
    args = parser.parse_args()

    app = QApplication(sys.argv)

    # ── show file-picker unless both paths were given on the CLI ──────────────
    if args.yml and args.data:
        yml_path  = args.yml
        data_path = args.data
    else:
        dlg = FilePickerDialog(yml_default=args.yml, data_default=args.data)
        if dlg.exec() != QDialog.DialogCode.Accepted:
            sys.exit(0)
        yml_path  = dlg.yml_path
        data_path = dlg.data_path

    # ── load data and launch main window ─────────────────────────────────────
    try:
        data = SimData(yml_path, data_path)
    except Exception as exc:
        QMessageBox.critical(None, "Failed to load files", str(exc))
        sys.exit(1)

    win = BobVisWindow(data)
    win.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()