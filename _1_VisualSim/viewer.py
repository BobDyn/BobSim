"""BobVis - the BobSim suspension and vehicle motion viewer.

A PyQt6 desktop app around :mod:`_1_VisualSim.scene`: a 3D viewport with
follow/free cameras, a signal panel that tracks playback, a transport bar, and
video export that renders exactly the view on screen.

    python -m _1_VisualSim.viewer [CONFIG.yml] [DATA.npz]
    make visual

Launched with no arguments it opens a picker seeded with the configs in
``_1_VisualSim/visual_templates``.
"""

from __future__ import annotations

import argparse
import csv
import sys
import time
from dataclasses import dataclass
from pathlib import Path
from typing import Any, Callable, Literal

import numpy as np

from PyQt6.QtCore import QEvent, QObject, QPointF, QSettings, Qt, QTimer, pyqtSignal
from PyQt6.QtGui import (
    QAction,
    QInputDevice,
    QKeySequence,
    QMouseEvent,
    QNativeGestureEvent,
    QWheelEvent,
)
from PyQt6.QtWidgets import (
    QApplication,
    QCheckBox,
    QComboBox,
    QDialog,
    QDialogButtonBox,
    QDoubleSpinBox,
    QFileDialog,
    QFormLayout,
    QFrame,
    QHBoxLayout,
    QHeaderView,
    QLabel,
    QLineEdit,
    QMainWindow,
    QMenu,
    QMessageBox,
    QProgressDialog,
    QPushButton,
    QScrollArea,
    QSizePolicy,
    QSlider,
    QSpinBox,
    QSplitter,
    QStatusBar,
    QTabWidget,
    QToolBar,
    QTreeWidget,
    QTreeWidgetItem,
    QVBoxLayout,
    QWidget,
)

import matplotlib

matplotlib.use("QtAgg")
from matplotlib.backends.backend_qtagg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure

import pyvista as pv
from pyvistaqt import QtInteractor

from _1_VisualSim.exporter import (
    ExportCancelled,
    ExportError,
    ExportSettings,
    RESOLUTIONS,
    render_video,
)
from _1_VisualSim.navigation import (
    ORBIT_DEG_PER_PX,
    CameraPose,
    classify_wheel,
    orbit,
    pan,
    recenter,
    wheel_drag_pixels,
    wheel_zoom_factor,
    zoom_at,
)
from _1_VisualSim.scene import (
    FOLLOW,
    FREE,
    SceneOptions,
    SimData,
    VisualConfigError,
    VisualScene,
    trail_indices,
)
from _1_VisualSim.theme import THEME, UiTheme, matplotlib_rc, stylesheet
from _1_VisualSim.tire_state import grip_usage

APP_NAME = "BobVis"
TEMPLATE_DIR = Path(__file__).resolve().parent / "visual_templates"
DEFAULT_OUTPUT_DIR = Path(__file__).resolve().parent / "results"


# ---------------------------------------------------------------------------
# Playback clock
#
# A main-thread QTimer, not a worker thread. The previous viewer pushed frames
# from a QThread at ~125 Hz and rendered VTK from the slot, which flooded the
# event loop and drove the render from a thread that did not own the context.
# ---------------------------------------------------------------------------

class PlaybackClock(QObject):
    """Wall-clock driven simulation time with play/pause/seek/loop."""

    tick = pyqtSignal(float)
    state_changed = pyqtSignal(bool)

    INTERVAL_MS = 16  # ~60 Hz

    def __init__(self, t_start: float, t_end: float, parent: QObject | None = None) -> None:
        super().__init__(parent)
        self.t_start = float(t_start)
        self.t_end = float(t_end)
        self._sim_time = self.t_start
        self._speed = 1.0
        self._loop = False
        self._last_wall = 0.0

        self._timer = QTimer(self)
        self._timer.setInterval(self.INTERVAL_MS)
        self._timer.timeout.connect(self._on_timeout)

    # -- state --------------------------------------------------------------
    @property
    def sim_time(self) -> float:
        return self._sim_time

    @property
    def is_playing(self) -> bool:
        return self._timer.isActive()

    def set_speed(self, speed: float) -> None:
        self._speed = max(float(speed), 1e-6)

    def set_loop(self, loop: bool) -> None:
        self._loop = bool(loop)

    # -- transport ----------------------------------------------------------
    def play(self) -> None:
        if self.is_playing:
            return
        if self._sim_time >= self.t_end - 1e-12:
            self._sim_time = self.t_start  # replay rather than sit at the end
        self._last_wall = time.perf_counter()
        self._timer.start()
        self.state_changed.emit(True)

    def pause(self) -> None:
        if not self.is_playing:
            return
        self._timer.stop()
        self.state_changed.emit(False)

    def toggle(self) -> None:
        self.pause() if self.is_playing else self.play()

    def seek(self, sim_time: float) -> None:
        self._sim_time = float(np.clip(sim_time, self.t_start, self.t_end))
        self._last_wall = time.perf_counter()
        self.tick.emit(self._sim_time)

    def step(self, seconds: float) -> None:
        self.seek(self._sim_time + seconds)

    # -- internals ----------------------------------------------------------
    def _on_timeout(self) -> None:
        now = time.perf_counter()
        dt = (now - self._last_wall) * self._speed
        self._last_wall = now

        self._sim_time += dt
        if self._sim_time >= self.t_end:
            if self._loop:
                span = self.t_end - self.t_start
                self._sim_time = self.t_start + (self._sim_time - self.t_start) % max(span, 1e-9)
            else:
                self._sim_time = self.t_end
                self.pause()
        self.tick.emit(self._sim_time)


# ---------------------------------------------------------------------------
# Signal panel
# ---------------------------------------------------------------------------

class SignalPlot(QFrame):
    """One X/Y subplot with a time cursor that follows playback."""

    removed = pyqtSignal(object)

    CURSOR_MIN_INTERVAL = 1.0 / 40.0

    def __init__(self, data: SimData, theme: UiTheme, x: str = "time",
                 y: str | None = None, label: str | None = None,
                 parent: QWidget | None = None) -> None:
        super().__init__(parent)
        self.setProperty("role", "card")
        self.data = data
        self._theme = theme
        self._last_draw = 0.0
        # The config's display name, used as the axis label until the user
        # picks a different signal from the dropdown.
        self._label = label
        self._labelled_y = y

        choices = ["time"] + data.signal_names
        self._x = QComboBox()
        self._y = QComboBox()
        self._x.addItems(choices)
        self._y.addItems(choices)
        self._x.setCurrentText(x if x in choices else "time")
        if y and y in choices:
            self._y.setCurrentText(y)
        elif data.signal_names:
            self._y.setCurrentText(data.signal_names[0])
        for combo in (self._x, self._y):
            combo.setSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Fixed)
            combo.setMinimumWidth(70)
            combo.setToolTip(combo.currentText())
            combo.currentTextChanged.connect(combo.setToolTip)

        self._fig = Figure(figsize=(3.2, 1.5), layout="constrained")
        self._ax = self._fig.add_subplot(111)
        self._canvas = FigureCanvas(self._fig)
        self._canvas.setMinimumHeight(130)
        self._canvas.setSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Fixed)
        self._cursor = self._ax.axvline(float(data.time[0]), color="#e0483c", linewidth=1.0)

        close = QPushButton("×")
        close.setProperty("flat", True)
        close.setFixedSize(20, 20)
        close.setToolTip("Remove this plot")
        close.clicked.connect(lambda: self.removed.emit(self))

        header = QHBoxLayout()
        header.setSpacing(4)
        header.addWidget(self._x, 1)
        header.addWidget(QLabel("vs"))
        header.addWidget(self._y, 1)
        header.addWidget(close)

        layout = QVBoxLayout(self)
        layout.setContentsMargins(8, 6, 8, 8)
        layout.setSpacing(4)
        layout.addLayout(header)
        layout.addWidget(self._canvas)

        self._x.currentTextChanged.connect(self.replot)
        self._y.currentTextChanged.connect(self.replot)
        self.replot()

    def replot(self) -> None:
        x_name = self._x.currentText()
        y_name = self._y.currentText()
        x = self.data.time if x_name == "time" else self.data.get_signal(x_name)
        y = self.data.time if y_name == "time" else self.data.get_signal(y_name)

        rc = matplotlib_rc(self._theme)
        self._fig.set_facecolor(str(rc["figure.facecolor"]))
        self._ax.clear()
        self._ax.set_facecolor(str(rc["axes.facecolor"]))
        self._ax.plot(x, y, linewidth=1.4, color=self._theme.accent)
        y_label = self._label if (self._label and y_name == self._labelled_y) else y_name
        self._ax.set_xlabel(x_name, fontsize=7, color=self._theme.text_muted)
        self._ax.set_ylabel(_shorten(y_label), fontsize=7, color=self._theme.text_muted)
        self._ax.tick_params(labelsize=7, colors=self._theme.text_muted,
                             length=3, width=0.6)
        self._ax.grid(True, linestyle="--", linewidth=0.5, alpha=0.35,
                      color=self._theme.border)
        for side in ("top", "right"):
            self._ax.spines[side].set_visible(False)
        for side in ("left", "bottom"):
            self._ax.spines[side].set_color(self._theme.border)

        self._cursor = self._ax.axvline(float(self.data.time[0]),
                                        color="#e0483c", linewidth=1.0)
        self._canvas.draw_idle()

    def set_cursor(self, sim_time: float, force: bool = False) -> None:
        now = time.perf_counter()
        if not force and now - self._last_draw < self.CURSOR_MIN_INTERVAL:
            return
        self._last_draw = now

        x_name = self._x.currentText()
        if x_name == "time":
            value = float(sim_time)
        else:
            value = float(np.interp(sim_time, self.data.time,
                                    self.data.get_signal(x_name)))
        self._cursor.set_xdata([value])
        self._canvas.draw_idle()


class SignalPanel(QFrame):
    """Scrollable stack of :class:`SignalPlot` rows."""

    def __init__(self, data: SimData, theme: UiTheme,
                 parent: QWidget | None = None) -> None:
        super().__init__(parent)
        self.setProperty("role", "panel")
        self.data = data
        self._theme = theme
        self._rows: list[SignalPlot] = []

        add = QPushButton("+ Add plot")
        add.setToolTip("Add a signal plot")
        add.clicked.connect(lambda: self.add_plot())

        header = QHBoxLayout()
        header.setContentsMargins(10, 8, 10, 4)
        header.addStretch(1)
        header.addWidget(add)

        self._content = QWidget()
        self._stack = QVBoxLayout(self._content)
        self._stack.setContentsMargins(8, 4, 8, 8)
        self._stack.setSpacing(8)
        self._stack.addStretch(1)

        scroll = QScrollArea()
        scroll.setWidgetResizable(True)
        scroll.setWidget(self._content)
        scroll.setFrameShape(QFrame.Shape.NoFrame)

        layout = QVBoxLayout(self)
        layout.setContentsMargins(0, 0, 0, 0)
        layout.setSpacing(0)
        layout.addLayout(header)
        layout.addWidget(scroll, 1)

        self._seed_from_config()

    def _seed_from_config(self) -> None:
        """Start with the plots the visual YAML asked for."""
        configured = [
            (str(p.get("x", "time")), str(p["y"]), str(p.get("name", "")) or None)
            for p in self.data.plots_cfg
            if p.get("y")
        ]
        for x, y, label in configured[:4]:
            self.add_plot(x, y, label)
        if not self._rows:
            self.add_plot()

    def add_plot(self, x: str = "time", y: str | None = None,
                 label: str | None = None) -> None:
        row = SignalPlot(self.data, self._theme, x, y, label)
        row.removed.connect(self._remove)
        self._stack.insertWidget(self._stack.count() - 1, row)
        self._rows.append(row)

    def _remove(self, row: SignalPlot) -> None:
        if row in self._rows:
            self._rows.remove(row)
            self._stack.removeWidget(row)
            row.deleteLater()

    def set_cursor(self, sim_time: float, force: bool = False) -> None:
        for row in self._rows:
            row.set_cursor(sim_time, force)


# ---------------------------------------------------------------------------
# Tires and Metrics tabs
# ---------------------------------------------------------------------------

class FrictionPanel(QFrame):
    """Friction circles: each tire's force against its peak grip, laid out like the car."""

    TRAIL_S = 1.0
    MIN_INTERVAL = 1.0 / 30.0
    NEAR_LIMIT = 0.80
    AT_LIMIT = 0.95
    AMBER = "#e08a2f"
    RED = "#d64550"
    CORNERS = (("fl", "Front left"), ("fr", "Front right"),
               ("rl", "Rear left"), ("rr", "Rear right"))

    def __init__(self, data: SimData, theme: UiTheme, parent: QWidget | None = None) -> None:
        super().__init__(parent)
        self.setProperty("role", "panel")
        self.data = data
        self._theme = theme
        self._last_draw = 0.0
        self._state = self._grip_state(data)
        self._artists: dict[str, dict[str, Any]] = {}
        if not self._state:
            return

        rc = matplotlib_rc(theme)
        self._fig = Figure(figsize=(3.2, 3.4), layout="constrained")
        self._fig.set_facecolor(str(rc["figure.facecolor"]))
        circle = np.linspace(0.0, 2.0 * np.pi, 121)
        for ax, (corner, label) in zip(self._fig.subplots(2, 2).ravel(), self.CORNERS):
            ax.set_facecolor(str(rc["axes.facecolor"]))
            ax.plot(np.cos(circle), np.sin(circle), color=theme.text_muted, linewidth=1.0)
            ax.plot(0.5 * np.cos(circle), 0.5 * np.sin(circle), color=theme.border,
                    linewidth=0.8, linestyle="--")
            ax.axhline(0.0, color=theme.border, linewidth=0.6)
            ax.axvline(0.0, color=theme.border, linewidth=0.6)
            ax.set_xlim(-1.3, 1.3)
            ax.set_ylim(-1.3, 1.3)
            ax.set_aspect("equal")
            ax.set_xticks([])
            ax.set_yticks([])
            for spine in ax.spines.values():
                spine.set_visible(False)
            ax.set_title(label, fontsize=8, color=theme.text_muted)
            if corner not in self._state:
                ax.text(0.0, 0.0, "no data", ha="center", va="center",
                        fontsize=8, color=theme.text_muted)
                continue
            (trail,) = ax.plot([], [], color=theme.accent, alpha=0.35, linewidth=1.2)
            (dot,) = ax.plot([], [], "o", markersize=7, color=theme.accent)
            value = ax.text(0.5, 0.02, "", transform=ax.transAxes, ha="center",
                            va="bottom", fontsize=9, color=theme.text)
            self._artists[corner] = {"trail": trail, "dot": dot, "value": value}

        self._canvas = FigureCanvas(self._fig)
        self._canvas.setSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Expanding)

        caption = _muted(
            "Each tire's force as a share of its peak grip at its current load and "
            "camber. The outer circle is the limit: up is drive, down is braking, "
            "sideways is cornering. Amber past 80%, red past 95%."
        )
        caption.setWordWrap(True)
        tires = sorted({str(c.get("tir", "")) for c in
                        (data.tire_forces_cfg.get("friction") or {}).values()} - {""})
        source = _muted(f"Grip model: MF5.2 peak μ from {', '.join(tires) or 'the .tir'}")
        source.setWordWrap(True)

        layout = QVBoxLayout(self)
        layout.setContentsMargins(8, 8, 8, 8)
        layout.setSpacing(6)
        layout.addWidget(self._canvas, 1)
        layout.addWidget(caption)
        layout.addWidget(source)
        self.set_time(float(data.time[0]), force=True)

    @property
    def has_data(self) -> bool:
        return bool(self._state)

    @staticmethod
    def _grip_state(data: SimData) -> dict[str, dict[str, np.ndarray]]:
        cfg = data.tire_forces_cfg
        friction = cfg.get("friction") or {}
        state: dict[str, dict[str, np.ndarray]] = {}
        for corner, tire in (cfg.get("corners") or {}).items():
            coeffs = friction.get(str(tire.get("axle", ""))) or next(iter(friction.values()), None)
            if not coeffs:
                continue
            gamma = data.get_signal(str(tire["gamma"])) if tire.get("gamma") else 0.0
            longitudinal, lateral, usage = grip_usage(
                data.get_signal(str(tire["fx"])), data.get_signal(str(tire["fy"])),
                data.get_signal(str(tire["fz"])), gamma, coeffs,
            )
            state[str(corner)] = {"long": longitudinal, "lat": lateral, "usage": usage}
        return state

    def _colour(self, usage: float) -> str:
        if not np.isfinite(usage):
            return self._theme.text_muted
        if usage >= self.AT_LIMIT:
            return self.RED
        return self.AMBER if usage >= self.NEAR_LIMIT else self._theme.accent

    def set_time(self, sim_time: float, force: bool = False) -> None:
        if not self._artists:
            return
        now = time.perf_counter()
        if not force and now - self._last_draw < self.MIN_INTERVAL:
            return
        self._last_draw = now

        index = self.data.frame_at(sim_time)
        trail = trail_indices(self.data.time, index, self.TRAIL_S)
        for corner, artists in self._artists.items():
            state = self._state[corner]
            # Seen from above, car pointing up: a force toward the car's left plots left.
            x, y = -state["lat"], state["long"]
            usage = float(state["usage"][index])
            colour = self._colour(usage)
            artists["trail"].set_data(x[trail], y[trail])
            artists["dot"].set_data([x[index]], [y[index]])
            artists["dot"].set_color(colour)
            artists["value"].set_text(f"{usage:.0%}" if np.isfinite(usage) else "lifted")
            artists["value"].set_color(
                colour if not np.isfinite(usage) or usage >= self.NEAR_LIMIT else self._theme.text
            )
        self._canvas.draw_idle()


class MetricsPanel(QFrame):
    """The run's scalar metrics, grouped the way the evaluation wrote them."""

    COLLAPSED = {"trend"}
    """Groups long enough to bury the rest; open them by clicking."""

    def __init__(self, path: Path, parent: QWidget | None = None) -> None:
        super().__init__(parent)
        self.setProperty("role", "panel")
        rows = _read_metrics(path)

        self._filter = QLineEdit()
        self._filter.setPlaceholderText("Filter metrics")
        self._filter.setClearButtonEnabled(True)

        self._tree = QTreeWidget()
        self._tree.setColumnCount(3)
        self._tree.setHeaderLabels(["Metric", "Value", "Units"])
        self._tree.setUniformRowHeights(True)
        header = self._tree.header()
        if header is not None:
            header.setStretchLastSection(False)
            header.setSectionResizeMode(0, QHeaderView.ResizeMode.Stretch)
            header.setSectionResizeMode(1, QHeaderView.ResizeMode.ResizeToContents)
            header.setSectionResizeMode(2, QHeaderView.ResizeMode.ResizeToContents)

        self._groups: dict[str, QTreeWidgetItem] = {}
        for row in rows:
            group = row.get("group") or "metrics"
            parent_item = self._groups.get(group)
            if parent_item is None:
                parent_item = QTreeWidgetItem(self._tree, [group.replace("_", " ").capitalize()])
                font = parent_item.font(0)
                font.setBold(True)
                parent_item.setFont(0, font)
                parent_item.setFirstColumnSpanned(True)
                self._groups[group] = parent_item
            item = QTreeWidgetItem(parent_item, [
                row.get("metric", ""), _format_metric(row.get("value", "")), row.get("units", ""),
            ])
            item.setTextAlignment(1, Qt.AlignmentFlag.AlignRight | Qt.AlignmentFlag.AlignVCenter)
            for column in range(3):
                item.setToolTip(column, row.get("description", ""))
        self._apply_filter("")

        source = _muted(f"{path.name}  ·  hover a metric for its definition")
        source.setWordWrap(True)

        layout = QVBoxLayout(self)
        layout.setContentsMargins(8, 8, 8, 8)
        layout.setSpacing(6)
        layout.addWidget(self._filter)
        layout.addWidget(self._tree, 1)
        layout.addWidget(source)
        self._filter.textChanged.connect(self._apply_filter)

    @property
    def has_data(self) -> bool:
        return bool(self._groups)

    def _apply_filter(self, text: str) -> None:
        needle = text.strip().lower()
        for group, item in self._groups.items():
            shown = 0
            for index in range(item.childCount()):
                child = item.child(index)
                if child is None:
                    continue
                match = not needle or needle in child.text(0).lower() or needle in child.toolTip(0).lower()
                child.setHidden(not match)
                shown += int(match)
            item.setHidden(shown == 0)
            item.setExpanded(bool(needle) or group not in self.COLLAPSED)


def _read_metrics(path: Path) -> list[dict[str, str]]:
    try:
        with open(path, "r", newline="", encoding="utf-8") as handle:
            return [dict(row) for row in csv.DictReader(handle) if row.get("metric")]
    except (OSError, csv.Error):
        return []


def _format_metric(raw: str) -> str:
    try:
        value = float(raw)
    except ValueError:
        return raw
    if value.is_integer() and abs(value) < 1e6:
        return str(int(value))
    return f"{value:.4g}"


# ---------------------------------------------------------------------------
# Transport bar
# ---------------------------------------------------------------------------

class TransportBar(QFrame):
    """Play/pause, scrub, speed and loop, along the bottom of the window."""

    play_toggled = pyqtSignal()
    seek_requested = pyqtSignal(float)
    speed_changed = pyqtSignal(float)
    loop_changed = pyqtSignal(bool)

    SPEEDS = [0.1, 0.25, 0.5, 1.0, 2.0, 4.0]
    TICKS = 2000  # slider resolution, independent of the sample count

    def __init__(self, t_start: float, t_end: float,
                 parent: QWidget | None = None) -> None:
        super().__init__(parent)
        self.setProperty("role", "transport")
        self.t_start = float(t_start)
        self.t_end = float(t_end)
        self._scrubbing = False
        self._syncing = False

        self._play = QPushButton("▶")
        self._play.setFixedSize(34, 26)
        self._play.setToolTip("Play / pause  (Space)")
        self._play.clicked.connect(self.play_toggled.emit)

        self._to_start = QPushButton("|◀")
        self._to_start.setFixedSize(32, 26)
        self._to_start.setToolTip("Jump to start  (Home)")
        self._to_start.clicked.connect(lambda: self.seek_requested.emit(self.t_start))

        self._to_end = QPushButton("▶|")
        self._to_end.setFixedSize(32, 26)
        self._to_end.setToolTip("Jump to end  (End)")
        self._to_end.clicked.connect(lambda: self.seek_requested.emit(self.t_end))

        self._slider = QSlider(Qt.Orientation.Horizontal)
        self._slider.setRange(0, self.TICKS)
        self._slider.setPageStep(self.TICKS // 20)
        # valueChanged (not sliderMoved) so a click on the groove also seeks.
        self._slider.valueChanged.connect(self._on_slider)
        self._slider.sliderPressed.connect(lambda: setattr(self, "_scrubbing", True))
        self._slider.sliderReleased.connect(lambda: setattr(self, "_scrubbing", False))

        self._time = QLabel()
        self._time.setProperty("role", "time")
        self._time.setMinimumWidth(150)
        self._time.setAlignment(Qt.AlignmentFlag.AlignRight | Qt.AlignmentFlag.AlignVCenter)

        self._speed = QComboBox()
        for s in self.SPEEDS:
            self._speed.addItem(f"{s:g}×", s)
        self._speed.setCurrentIndex(self.SPEEDS.index(1.0))
        self._speed.setFixedWidth(64)
        self._speed.setToolTip("Playback speed")
        self._speed.currentIndexChanged.connect(
            lambda _: self.speed_changed.emit(float(self._speed.currentData()))
        )

        self._loop = QPushButton("Loop")
        self._loop.setCheckable(True)
        self._loop.setFixedHeight(26)
        self._loop.setProperty("toggle", True)
        self._loop.setToolTip("Repeat playback")
        self._loop.toggled.connect(self.loop_changed.emit)

        layout = QHBoxLayout(self)
        layout.setContentsMargins(10, 7, 10, 7)
        layout.setSpacing(6)
        layout.addWidget(self._to_start)
        layout.addWidget(self._play)
        layout.addWidget(self._to_end)
        layout.addSpacing(4)
        layout.addWidget(self._slider, 1)
        layout.addWidget(self._time)
        layout.addSpacing(4)
        layout.addWidget(self._speed)
        layout.addWidget(self._loop)

        self.sync(self.t_start)

    def _on_slider(self, value: int) -> None:
        if self._syncing:
            return
        span = self.t_end - self.t_start
        self.seek_requested.emit(self.t_start + span * value / self.TICKS)

    def sync(self, sim_time: float) -> None:
        span = max(self.t_end - self.t_start, 1e-9)
        if not self._scrubbing:
            self._syncing = True
            self._slider.setValue(int(round(self.TICKS * (sim_time - self.t_start) / span)))
            self._syncing = False
        self._time.setText(f"{sim_time:8.3f} / {self.t_end:.3f} s")

    def set_playing(self, playing: bool) -> None:
        self._play.setText("▮▮" if playing else "▶")


# ---------------------------------------------------------------------------
# Viewport navigation
#
# VTK's Qt widget turns scrolling into fixed 10% zoom jumps once a whole wheel
# notch has piled up, ignores sideways scroll and pinch, and has no pan on a
# touchpad. So mouse, wheel and gesture input is taken here, before VTK sees
# it. The camera arithmetic lives in :mod:`_1_VisualSim.navigation`.
# ---------------------------------------------------------------------------

class ViewportNavigator(QObject):
    """Mouse and touchpad camera control, installed as an event filter on the viewport."""

    TOUCHPAD_LATCH_S = 0.4
    """How long a touchpad gesture stays one between events."""

    def __init__(self, viewport: QWidget, scene: VisualScene,
                 on_change: Callable[[], None], parent: QObject | None = None) -> None:
        super().__init__(parent)
        self._viewport = viewport
        self._scene = scene
        self._on_change = on_change
        self.touchpad_gestures = True
        self._drag: Literal["orbit", "pan"] | None = None
        self._last = QPointF()
        self._last_touchpad = float("-inf")

    def eventFilter(self, obj: QObject | None, event: QEvent | None) -> bool:
        if isinstance(event, QMouseEvent):
            kind = event.type()
            if kind == QEvent.Type.MouseButtonDblClick:
                return self._double_click(event)
            if kind == QEvent.Type.MouseButtonPress:
                return self._press(event)
            if kind == QEvent.Type.MouseMove:
                return self._move(event)
            if kind == QEvent.Type.MouseButtonRelease:
                return self._release(event)
        elif isinstance(event, QWheelEvent):
            return self._wheel(event)
        elif isinstance(event, QNativeGestureEvent):
            return self._native_gesture(event)
        return False

    # -- drags --------------------------------------------------------------
    def _press(self, event: QMouseEvent) -> bool:
        button = event.button()
        mode: Literal["orbit", "pan"]
        if button == Qt.MouseButton.LeftButton:
            pan_modifiers = Qt.KeyboardModifier.ShiftModifier | Qt.KeyboardModifier.ControlModifier
            mode = "pan" if event.modifiers() & pan_modifiers else "orbit"
        elif button in (Qt.MouseButton.RightButton, Qt.MouseButton.MiddleButton):
            mode = "pan"
        else:
            return False
        self._drag = mode
        self._last = event.position()
        self._viewport.setCursor(
            Qt.CursorShape.ClosedHandCursor if mode == "orbit" else Qt.CursorShape.SizeAllCursor
        )
        return True

    def _move(self, event: QMouseEvent) -> bool:
        if self._drag is None:
            return False
        pos = event.position()
        dx, dy = pos.x() - self._last.x(), pos.y() - self._last.y()
        self._last = pos
        if self._drag == "orbit":
            self._orbit_by(dx, dy)
        else:
            self._pan_by(dx, dy)
        return True

    def _release(self, event: QMouseEvent) -> bool:
        if self._drag is None:
            return False
        if not event.buttons():
            self._drag = None
            self._viewport.unsetCursor()
        return True

    def _double_click(self, event: QMouseEvent) -> bool:
        if event.button() != Qt.MouseButton.LeftButton:
            return False
        self._drag = None
        self._viewport.unsetCursor()
        # VTK picks in device pixels with the origin at the bottom left.
        ratio = self._viewport.devicePixelRatioF()
        pos = event.position()
        point = self._scene.pick_point(
            pos.x() * ratio, (self._viewport.height() - pos.y() - 1) * ratio
        )
        if point is not None:
            self._apply(lambda pose: recenter(pose, point))
        return True

    # -- wheel and gestures -------------------------------------------------
    def _wheel(self, event: QWheelEvent) -> bool:
        angle, pixel = event.angleDelta(), event.pixelDelta()
        modifiers = event.modifiers()
        device = event.pointingDevice()
        now = time.perf_counter()
        action = classify_wheel(
            angle.x(), angle.y(),
            pixel_dx=pixel.x(), pixel_dy=pixel.y(),
            scroll_phase=event.phase() != Qt.ScrollPhase.NoScrollPhase,
            touchpad_device=device is not None and device.type() == QInputDevice.DeviceType.TouchPad,
            recent_touchpad=now - self._last_touchpad < self.TOUCHPAD_LATCH_S,
            ctrl=bool(modifiers & Qt.KeyboardModifier.ControlModifier),
            shift=bool(modifiers & Qt.KeyboardModifier.ShiftModifier),
            detect_touchpad=self.touchpad_gestures,
        )
        if action == "zoom":
            factor = wheel_zoom_factor(angle.x(), angle.y(), pixel.x(), pixel.y())
            self._zoom_by(event.position(), factor)
        elif action in ("orbit", "pan"):
            self._last_touchpad = now
            dx, dy = wheel_drag_pixels(angle.x(), angle.y(), pixel.x(), pixel.y())
            if action == "orbit":
                self._orbit_by(dx, dy)
            else:
                self._pan_by(dx, dy)
        return True

    def _native_gesture(self, event: QNativeGestureEvent) -> bool:
        """macOS trackpad pinch; Windows and Linux send pinch as Ctrl + scroll instead."""
        if event.gestureType() != Qt.NativeGestureType.ZoomNativeGesture:
            return False
        self._zoom_by(event.position(), 1.0 + float(event.value()))
        return True

    # -- camera -------------------------------------------------------------
    def _apply(self, step: Callable[[CameraPose], CameraPose]) -> None:
        self._scene.set_camera_pose(step(self._scene.camera_pose()))
        self._on_change()

    def _orbit_by(self, dx: float, dy: float) -> None:
        self._apply(lambda pose: orbit(pose, -ORBIT_DEG_PER_PX * dx, ORBIT_DEG_PER_PX * dy))

    def _pan_by(self, dx: float, dy: float) -> None:
        height = max(self._viewport.height(), 1)
        self._apply(lambda pose: pan(pose, dx, dy, height))

    def _zoom_by(self, position: QPointF, factor: float) -> None:
        width, height = max(self._viewport.width(), 1), max(self._viewport.height(), 1)
        ndc_x = 2.0 * position.x() / width - 1.0
        ndc_y = 1.0 - 2.0 * position.y() / height
        self._apply(lambda pose: zoom_at(pose, factor, ndc_x, ndc_y, width / height))


CONTROLS: tuple[tuple[str, tuple[tuple[str, str], ...]], ...] = (
    ("Mouse", (
        ("Left-drag", "Orbit"),
        ("Right-drag, middle-drag, Shift+left-drag", "Pan"),
        ("Scroll", "Zoom toward the cursor"),
        ("Double-click", "Orbit around the point under the cursor"),
    )),
    ("Touchpad", (
        ("Two-finger drag", "Orbit"),
        ("Shift + two-finger drag", "Pan"),
        ("Pinch", "Zoom toward the cursor"),
        ("Click-drag", "Orbit"),
        ("Double-click", "Orbit around the point under the cursor"),
    )),
    ("Keyboard", (
        ("R", "Reset the view"),
        ("+  /  -", "Zoom"),
        ("Space", "Play / pause"),
        ("←  /  →", "Step one sample"),
        ("Home  /  End", "Jump to start / end"),
    )),
)


# ---------------------------------------------------------------------------
# Dialogs
# ---------------------------------------------------------------------------

@dataclass
class OpenChoice:
    config: Path
    data: Path


class OpenDialog(QDialog):
    """Pick a visual config and a signal file."""

    def __init__(self, config: str = "", data: str = "",
                 parent: QWidget | None = None) -> None:
        super().__init__(parent)
        self.setWindowTitle(f"{APP_NAME} - Open")
        self.setMinimumWidth(560)

        self._templates = QComboBox()
        self._templates.addItem("Custom file...", "")
        # Generated scenes first: those are the ones that open. The bundled
        # templates are kept for reference but name signals no current model
        # emits, so they are listed last and labelled.
        for path in sorted(DEFAULT_OUTPUT_DIR.glob("*.yml")):
            self._templates.addItem(path.stem.replace("_", " "), str(path))
        for path in sorted(TEMPLATE_DIR.glob("*.yml")):
            self._templates.addItem(f"{path.stem.replace('_', ' ')}  (stale)",
                                    str(path))
        self._templates.currentIndexChanged.connect(self._on_template)

        self._config = QLineEdit(config)
        self._config.setPlaceholderText("visual config (.yml)")
        self._data = QLineEdit(data)
        self._data.setPlaceholderText("signal file (.npz or .csv)")

        form = QFormLayout()
        form.setContentsMargins(16, 16, 16, 8)
        form.setSpacing(10)
        form.addRow("Template:", self._templates)
        form.addRow("Config:", _with_browse(
            self._config, lambda: self._browse(
                self._config, "Select visual config",
                "YAML (*.yml *.yaml);;All files (*)")))
        form.addRow("Data:", _with_browse(
            self._data, lambda: self._browse(
                self._data, "Select signal file",
                "Signals (*.npz *.csv);;All files (*)")))

        hint = QLabel(
            "No scene yet? `make visual-rig` simulates the four-post rig and "
            "opens the result; `make visual-demo` needs no simulation at all."
        )
        hint.setProperty("role", "muted")
        hint.setWordWrap(True)

        buttons = QDialogButtonBox(
            QDialogButtonBox.StandardButton.Open | QDialogButtonBox.StandardButton.Cancel
        )
        buttons.accepted.connect(self._on_accept)
        buttons.rejected.connect(self.reject)

        layout = QVBoxLayout(self)
        layout.addLayout(form)
        layout.addWidget(hint)
        layout.addSpacing(6)
        layout.addWidget(buttons)

        if config:
            self._select_matching_template(config)

    def _select_matching_template(self, config: str) -> None:
        for i in range(self._templates.count()):
            if self._templates.itemData(i) == str(Path(config).resolve()):
                self._templates.setCurrentIndex(i)
                return

    def _on_template(self, index: int) -> None:
        path = self._templates.itemData(index)
        if path:
            self._config.setText(str(path))

    def _browse(self, target: QLineEdit, title: str, filters: str) -> None:
        start = target.text().strip() or str(TEMPLATE_DIR)
        path, _ = QFileDialog.getOpenFileName(self, title, start, filters)
        if path:
            target.setText(path)

    def _on_accept(self) -> None:
        missing = [
            label for label, edit in (("config", self._config), ("data file", self._data))
            if not edit.text().strip()
        ]
        if missing:
            QMessageBox.warning(self, "Missing files",
                                "Select a " + " and a ".join(missing) + ".")
            return
        for edit in (self._config, self._data):
            if not Path(edit.text().strip()).is_file():
                QMessageBox.warning(self, "File not found",
                                    f"Cannot find:\n{edit.text().strip()}")
                return
        self.accept()

    @property
    def choice(self) -> OpenChoice:
        return OpenChoice(Path(self._config.text().strip()),
                          Path(self._data.text().strip()))


def _with_browse(edit: QLineEdit, on_click: Callable[[], None]) -> QWidget:
    button = QPushButton("Browse")
    button.clicked.connect(on_click)
    row = QWidget()
    layout = QHBoxLayout(row)
    layout.setContentsMargins(0, 0, 0, 0)
    layout.setSpacing(6)
    layout.addWidget(edit, 1)
    layout.addWidget(button)
    return row


class ExportDialog(QDialog):
    """Collect :class:`ExportSettings` for the current scene."""

    def __init__(self, data: SimData, default_output: Path, default_speed: float,
                 parent: QWidget | None = None) -> None:
        super().__init__(parent)
        self.setWindowTitle(f"{APP_NAME} - Export video")
        self.setMinimumWidth(480)
        self.data = data

        self._output = QLineEdit(str(default_output))
        output_row = _with_browse(self._output, self._browse_output)

        self._resolution = QComboBox()
        for name, (w, h) in RESOLUTIONS.items():
            self._resolution.addItem(f"{name}  ({w}x{h})", (w, h))
        self._resolution.addItem("Custom", None)
        self._resolution.setCurrentIndex(1)  # 1080p
        self._resolution.currentIndexChanged.connect(self._on_resolution)

        self._width = QSpinBox()
        self._width.setRange(64, 7680)
        self._width.setSingleStep(2)
        self._height = QSpinBox()
        self._height.setRange(64, 4320)
        self._height.setSingleStep(2)
        self._width.setValue(1920)
        self._height.setValue(1080)
        self._width.setEnabled(False)
        self._height.setEnabled(False)

        size_row = QWidget()
        size_layout = QHBoxLayout(size_row)
        size_layout.setContentsMargins(0, 0, 0, 0)
        size_layout.setSpacing(6)
        size_layout.addWidget(self._resolution, 1)
        size_layout.addWidget(self._width)
        size_layout.addWidget(QLabel("x"))
        size_layout.addWidget(self._height)

        self._fps = QSpinBox()
        self._fps.setRange(1, 240)
        self._fps.setValue(60)
        self._speed = QDoubleSpinBox()
        self._speed.setRange(0.01, 100.0)
        self._speed.setSingleStep(0.25)
        self._speed.setDecimals(2)
        self._speed.setValue(float(default_speed))

        rate_row = QWidget()
        rate_layout = QHBoxLayout(rate_row)
        rate_layout.setContentsMargins(0, 0, 0, 0)
        rate_layout.setSpacing(6)
        rate_layout.addWidget(self._fps, 1)
        rate_layout.addWidget(QLabel("fps, at"))
        rate_layout.addWidget(self._speed, 1)
        rate_layout.addWidget(QLabel("× speed"))

        self._start = QDoubleSpinBox()
        self._end = QDoubleSpinBox()
        for box, value in ((self._start, data.time[0]), (self._end, data.time[-1])):
            box.setRange(float(data.time[0]), float(data.time[-1]))
            box.setDecimals(3)
            box.setSingleStep(0.1)
            box.setValue(float(value))
            box.setSuffix(" s")

        range_row = QWidget()
        range_layout = QHBoxLayout(range_row)
        range_layout.setContentsMargins(0, 0, 0, 0)
        range_layout.setSpacing(6)
        range_layout.addWidget(self._start, 1)
        range_layout.addWidget(QLabel("to"))
        range_layout.addWidget(self._end, 1)

        self._plots = QCheckBox("Include the signal strip")
        self._plots.setChecked(bool(data.plots_cfg))
        self._plots.setEnabled(bool(data.plots_cfg))
        self._camera = QCheckBox("Use the camera currently on screen")
        self._camera.setChecked(True)

        self._estimate = QLabel()
        self._estimate.setProperty("role", "muted")
        for widget in (self._fps, self._start, self._end):
            widget.valueChanged.connect(self._update_estimate)
        self._speed.valueChanged.connect(self._update_estimate)

        form = QFormLayout()
        form.setContentsMargins(16, 16, 16, 8)
        form.setSpacing(10)
        form.addRow("Output:", output_row)
        form.addRow("Resolution:", size_row)
        form.addRow("Frame rate:", rate_row)
        form.addRow("Time range:", range_row)
        form.addRow("", self._plots)
        form.addRow("", self._camera)
        form.addRow("", self._estimate)

        buttons = QDialogButtonBox(
            QDialogButtonBox.StandardButton.Cancel
        )
        export = buttons.addButton("Export", QDialogButtonBox.ButtonRole.AcceptRole)
        export.setProperty("accent", True)
        buttons.accepted.connect(self._on_accept)
        buttons.rejected.connect(self.reject)

        layout = QVBoxLayout(self)
        layout.addLayout(form)
        layout.addSpacing(6)
        layout.addWidget(buttons)

        self._update_estimate()

    def _browse_output(self) -> None:
        path, _ = QFileDialog.getSaveFileName(
            self, "Save video as", self._output.text().strip(),
            "MP4 video (*.mp4);;Animated GIF (*.gif);;QuickTime (*.mov);;WebM (*.webm)",
        )
        if path:
            self._output.setText(path)

    def _on_resolution(self, index: int) -> None:
        size = self._resolution.itemData(index)
        custom = size is None
        self._width.setEnabled(custom)
        self._height.setEnabled(custom)
        if not custom:
            self._width.setValue(int(size[0]))
            self._height.setValue(int(size[1]))
        self._update_estimate()

    def _update_estimate(self) -> None:
        span = max(self._end.value() - self._start.value(), 0.0)
        speed = max(self._speed.value(), 1e-6)
        seconds = span / speed
        frames = max(2, int(round(seconds * self._fps.value())))
        self._estimate.setText(
            f"{frames} frames, about {seconds:.1f} s of video "
            f"at {self._width.value()}x{self._height.value()}"
        )

    def _on_accept(self) -> None:
        output = self._output.text().strip()
        if not output:
            QMessageBox.warning(self, "No output file", "Choose where to save the video.")
            return
        if self._end.value() <= self._start.value():
            QMessageBox.warning(self, "Empty time range",
                                "The end time must be after the start time.")
            return
        self.accept()

    def settings(self) -> ExportSettings:
        return ExportSettings(
            output=Path(self._output.text().strip()),
            width=self._width.value(),
            height=self._height.value(),
            fps=self._fps.value(),
            speed=self._speed.value(),
            start_time=self._start.value(),
            end_time=self._end.value(),
            show_plots=self._plots.isChecked(),
        )

    @property
    def use_current_camera(self) -> bool:
        return self._camera.isChecked()


# ---------------------------------------------------------------------------
# Main window
# ---------------------------------------------------------------------------

class ViewerWindow(QMainWindow):
    """The BobVis window: toolbar, viewport, signal panel, transport bar."""

    # Cheap enough for an interactive viewport; the exporter uses ssaa, which
    # looks better and costs more per frame.
    _ANTIALIAS: Literal["ssaa", "msaa", "fxaa"] | None = "fxaa"

    def __init__(self, data: SimData) -> None:
        super().__init__()
        self.data = data
        self.theme: UiTheme = THEME
        self.setWindowTitle(f"{APP_NAME} - {data.yml_path.stem}")
        self.resize(1440, 860)

        self._scene: VisualScene | None = None
        self._clock = PlaybackClock(float(data.time[0]), float(data.time[-1]), self)
        self._navigator: ViewportNavigator | None = None
        self._render_pending = False
        self._settings = QSettings("BobDyn", APP_NAME)

        self._build_ui()
        self._build_menu()
        self._wire()

        # Build the scene once the interactor has a live render window.
        QTimer.singleShot(0, self._build_scene)

    # -- construction -------------------------------------------------------
    def _build_ui(self) -> None:
        self._plotter = QtInteractor(self, lighting="three lights")
        self._plotter.setMinimumWidth(360)
        self._plotter.add_axes()  # type: ignore[call-arg]

        self._panel = SignalPanel(self.data, self.theme)
        self._tabs = QTabWidget()
        self._tabs.setDocumentMode(True)
        self._tabs.setMinimumWidth(260)
        self._tabs.addTab(self._panel, "Signals")

        friction = FrictionPanel(self.data, self.theme) if self.data.tire_forces_cfg else None
        self._friction = friction if friction is not None and friction.has_data else None
        if self._friction is not None:
            self._tabs.addTab(self._friction, "Tires")
        metrics_path = self.data.metrics_path
        metrics = MetricsPanel(metrics_path) if metrics_path is not None else None
        if metrics is not None and metrics.has_data:
            self._tabs.addTab(metrics, "Metrics")
        # A lone panel needs no tab bar.
        tab_bar = self._tabs.tabBar()
        if tab_bar is not None:
            tab_bar.setVisible(self._tabs.count() > 1)
        self._tabs.currentChanged.connect(lambda _: self._on_tick(self._clock.sim_time))

        self._splitter = QSplitter(Qt.Orientation.Horizontal)
        self._splitter.addWidget(self._plotter)
        self._splitter.addWidget(self._tabs)
        self._splitter.setStretchFactor(0, 4)
        self._splitter.setStretchFactor(1, 1)
        self._splitter.setSizes([1040, 400])
        self._splitter.setChildrenCollapsible(True)

        self._transport = TransportBar(float(self.data.time[0]), float(self.data.time[-1]))

        central = QWidget()
        layout = QVBoxLayout(central)
        layout.setContentsMargins(0, 0, 0, 0)
        layout.setSpacing(0)
        layout.addWidget(self._splitter, 1)
        layout.addWidget(self._transport)
        self.setCentralWidget(central)

        self._toolbar = self._build_toolbar()
        self.addToolBar(self._toolbar)

        self._status = QStatusBar()
        self.setStatusBar(self._status)
        self._status.showMessage("Loading scene…")

    def _build_toolbar(self) -> QToolBar:
        bar = QToolBar("View", self)
        bar.setMovable(False)

        views = QMenu(self)
        for label, preset in (("Iso", "iso"), ("Top", "top"), ("Front", "front"),
                              ("Rear", "rear"), ("Left", "left"), ("Right", "right")):
            action = views.addAction(label)
            if action is not None:
                action.triggered.connect(lambda _=False, p=preset: self._set_view(p))
        bar.addWidget(_menu_button("View", views, "Look along an axis and reframe the car"))

        self._camera_mode = QComboBox()
        self._camera_mode.addItem("Follow car", FOLLOW)
        self._camera_mode.addItem("Free", FREE)
        self._camera_mode.setFixedWidth(104)
        self._camera_mode.setToolTip(
            "Follow rides with the vehicle frame; Free leaves the camera in world space."
        )
        bar.addWidget(self._camera_mode)

        self._focus = QComboBox()
        self._focus.addItem("Whole car")
        self._focus.addItems(self.data.point_names)
        self._focus.setFixedWidth(150)
        self._focus.setToolTip("Point the follow camera at a specific joint")
        bar.addWidget(self._focus)

        layers = QMenu(self)
        self._toggle_ground = _layer(layers, "Ground")
        self._toggle_tires = _layer(layers, "Tires")
        self._toggle_vectors = _layer(layers, "Vectors")
        self._toggle_joints = _layer(layers, "Joints")
        self._toggle_tracks = _layer(layers, "Tracks")
        self._toggle_loads = _layer(layers, "Loads and LLTD")
        bar.addWidget(_menu_button("Layers", layers, "Show or hide parts of the scene"))

        spacer = QWidget()
        spacer.setSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Preferred)
        bar.addWidget(spacer)

        self._export_button = QPushButton("Export video")
        self._export_button.setProperty("accent", True)
        self._export_button.setFixedHeight(26)
        self._export_button.setToolTip("Render this scene to MP4 or GIF  (Ctrl+E)")
        self._export_button.clicked.connect(self._on_export)
        bar.addWidget(self._export_button)
        return bar

    def _build_menu(self) -> None:
        bar = self.menuBar()
        assert bar is not None

        file_menu = bar.addMenu("&File")
        assert file_menu is not None
        self._add_action(file_menu, "&Open…", self._on_open,
                         QKeySequence.StandardKey.Open)
        self._add_action(file_menu, "&Export video…", self._on_export, "Ctrl+E")
        self._add_action(file_menu, "Save &screenshot…", self._on_screenshot,
                         "Ctrl+Shift+S")
        file_menu.addSeparator()
        self._add_action(file_menu, "&Quit", self.close, QKeySequence.StandardKey.Quit)

        play_menu = bar.addMenu("&Playback")
        assert play_menu is not None
        self._add_action(play_menu, "Play / pause", self._clock.toggle, "Space")
        self._add_action(play_menu, "Step forward", lambda: self._step_frame(+1), "Right")
        self._add_action(play_menu, "Step back", lambda: self._step_frame(-1), "Left")
        self._add_action(play_menu, "Jump to start",
                         lambda: self._clock.seek(self._clock.t_start), "Home")
        self._add_action(play_menu, "Jump to end",
                         lambda: self._clock.seek(self._clock.t_end), "End")

        view_menu = bar.addMenu("&View")
        assert view_menu is not None
        self._add_action(view_menu, "Reset camera", lambda: self._set_view("iso"), "R")
        self._add_action(view_menu, "Zoom in", lambda: self._zoom(1.15), "+")
        self._add_action(view_menu, "Zoom out", lambda: self._zoom(1 / 1.15), "-")
        view_menu.addSeparator()
        for axis, label in (("x", "Elevation"), ("y", "Azimuth"), ("z", "Roll")):
            for sign, glyph in ((+1.0, "+"), (-1.0, "−")):
                self._add_action(
                    view_menu, f"{label} {glyph}15°",
                    self._rotator(axis, sign * 15.0),
                )
        view_menu.addSeparator()
        # Off for free-spinning mice, whose fractional scroll looks like a
        # touchpad's and would orbit instead of zoom.
        self._touchpad_action = QAction("Two-finger scroll orbits (touchpad)", self)
        self._touchpad_action.setCheckable(True)
        self._touchpad_action.setChecked(
            bool(self._settings.value("touchpad_gestures", True, type=bool))
        )
        self._touchpad_action.toggled.connect(self._on_touchpad_toggled)
        view_menu.addAction(self._touchpad_action)

        help_menu = bar.addMenu("&Help")
        assert help_menu is not None
        self._add_action(help_menu, "Mouse and touchpad controls", self._on_controls,
                         QKeySequence.StandardKey.HelpContents)
        self._add_action(help_menu, f"About {APP_NAME}", self._on_about)

    def _add_action(self, menu: Any, text: str, slot: Callable[[], Any],
                    shortcut: Any = None) -> QAction:
        action = QAction(text, self)
        if shortcut is not None:
            action.setShortcut(shortcut)
        action.triggered.connect(lambda _=False: slot())
        menu.addAction(action)
        return action

    def _wire(self) -> None:
        self._clock.tick.connect(self._on_tick)
        self._clock.state_changed.connect(self._transport.set_playing)

        self._transport.play_toggled.connect(self._clock.toggle)
        self._transport.seek_requested.connect(self._clock.seek)
        self._transport.speed_changed.connect(self._clock.set_speed)
        self._transport.loop_changed.connect(self._clock.set_loop)

        self._camera_mode.currentIndexChanged.connect(self._on_camera_mode)
        self._focus.currentTextChanged.connect(self._on_focus)
        self._toggle_ground.toggled.connect(
            lambda on: self._with_scene(lambda s: s.set_ground_visible(on)))
        self._toggle_tires.toggled.connect(
            lambda on: self._with_scene(lambda s: s.set_tires_visible(on)))
        self._toggle_vectors.toggled.connect(
            lambda on: self._with_scene(lambda s: s.set_vectors_visible(on)))
        self._toggle_joints.toggled.connect(
            lambda on: self._with_scene(lambda s: s.set_joints_visible(on)))
        self._toggle_tracks.toggled.connect(
            lambda on: self._with_scene(lambda s: s.set_tracks_visible(on)))
        self._toggle_loads.toggled.connect(
            lambda on: self._with_scene(lambda s: s.set_loads_visible(on)))

    def _build_scene(self) -> None:
        options = SceneOptions(palette=self.theme.palette)
        try:
            scene = VisualScene(self.data, self._plotter, options)
            scene.build()
        except VisualConfigError as exc:
            QMessageBox.critical(self, "Cannot build scene", str(exc))
            self._status.showMessage("Scene failed to build")
            return

        self._scene = scene
        self._observe_interaction()
        self._navigator = ViewportNavigator(self._plotter, scene, self._request_render, self)
        self._navigator.touchpad_gestures = self._touchpad_action.isChecked()
        self._plotter.installEventFilter(self._navigator)

        has_vectors = bool(self.data.geometry_cfg.get("vectors"))
        has_tires = bool(self.data.geometry_cfg.get("tires"))
        # Offer only the layers this scene has, rather than a row of dead switches.
        self._toggle_vectors.setVisible(has_vectors)
        self._toggle_tires.setVisible(has_tires)
        self._toggle_tracks.setVisible(bool(self.data.ground_cfg.get("tracks")))
        self._toggle_loads.setVisible(bool(self.data.ground_cfg.get("loads")))

        if self._ANTIALIAS:
            try:
                self._plotter.enable_anti_aliasing(self._ANTIALIAS)
            except Exception:  # noqa: BLE001 - cosmetic only
                pass

        self._clock.seek(float(self.data.time[0]))
        self._status.showMessage(
            f"{self.data.n_frames} samples  |  "
            f"t = {self.data.time[0]:.3f} to {self.data.time[-1]:.3f} s  |  "
            f"{len(self.data.point_names)} points  |  {self.data.data_path.name}  |  "
            "F1: mouse and touchpad controls"
        )

    def _observe_interaction(self) -> None:
        """Let mouse orbiting win over the follow camera, then adopt the result.

        Without this, follow mode overwrites the camera on the very next frame
        and the view snaps back mid-drag - the single biggest reason the old
        viewer felt broken.
        """
        iren = getattr(self._plotter, "iren", None)
        if iren is None or not hasattr(iren, "add_observer"):
            return
        try:
            iren.add_observer("StartInteractionEvent", self._on_interaction_start)
            iren.add_observer("EndInteractionEvent", self._on_interaction_end)
        except Exception:  # noqa: BLE001 - degrade to preset-only camera control
            pass

    # -- scene helpers ------------------------------------------------------
    def _with_scene(self, fn: Callable[[VisualScene], Any]) -> None:
        if self._scene is None:
            return
        fn(self._scene)
        self._plotter.render()

    def _on_interaction_start(self, *_: Any) -> None:
        if self._scene is not None:
            self._scene.suspend_camera(True)

    def _on_interaction_end(self, *_: Any) -> None:
        if self._scene is None:
            return
        self._scene.suspend_camera(False)
        if self._scene.camera_mode == FOLLOW:
            self._scene.capture_view()

    def _request_render(self) -> None:
        """Coalesce a burst of mouse or touchpad events into one render."""
        if self._render_pending:
            return
        self._render_pending = True
        QTimer.singleShot(0, self._flush_render)

    def _flush_render(self) -> None:
        self._render_pending = False
        self._plotter.render()

    def _on_touchpad_toggled(self, enabled: bool) -> None:
        self._settings.setValue("touchpad_gestures", enabled)
        if self._navigator is not None:
            self._navigator.touchpad_gestures = enabled
        effect = "orbits (Shift pans)" if enabled else "zooms"
        self._status.showMessage(f"Two-finger scroll {effect}", 5000)

    def _on_controls(self) -> None:
        QMessageBox.information(self, f"{APP_NAME} - Controls", _controls_html())

    def _set_view(self, preset: str) -> None:
        self._with_scene(lambda s: s.set_view(preset))

    def _rotate(self, axis: str, degrees: float) -> None:
        self._with_scene(lambda s: s.rotate(axis, degrees))

    def _rotator(self, axis: str, degrees: float) -> Callable[[], None]:
        """Bind axis and step now; menu actions all fire from the same loop."""
        return lambda: self._rotate(axis, degrees)

    def _zoom(self, factor: float) -> None:
        self._with_scene(lambda s: s.zoom(factor))

    def _on_camera_mode(self, index: int) -> None:
        mode = self._camera_mode.itemData(index)
        self._focus.setEnabled(mode == FOLLOW)
        self._with_scene(lambda s: s.set_camera_mode(mode))

    def _on_focus(self, name: str) -> None:
        self._with_scene(lambda s: s.set_focus_point(name))

    def _step_frame(self, direction: int) -> None:
        self._clock.pause()
        index = self.data.frame_at(self._clock.sim_time) + direction
        index = int(np.clip(index, 0, self.data.n_frames - 1))
        self._clock.seek(float(self.data.time[index]))

    # -- per-frame ----------------------------------------------------------
    def _on_tick(self, sim_time: float) -> None:
        if self._scene is None:
            return
        self._scene.update_time(sim_time)
        self._plotter.render()
        self._transport.sync(sim_time)
        self._panel.set_cursor(sim_time, force=not self._clock.is_playing)
        if self._friction is not None and self._friction.isVisible():
            self._friction.set_time(sim_time, force=not self._clock.is_playing)

    # -- actions ------------------------------------------------------------
    def _on_open(self) -> None:
        dialog = OpenDialog(str(self.data.yml_path), str(self.data.data_path), self)
        if dialog.exec() != QDialog.DialogCode.Accepted:
            return
        choice = dialog.choice
        try:
            data = SimData(choice.config, choice.data)
        except (OSError, VisualConfigError) as exc:
            QMessageBox.critical(self, "Cannot open files", str(exc))
            return

        window = ViewerWindow(data)
        window.show()
        # Keep a reference on the app so the new window is not garbage collected.
        _WINDOWS.append(window)
        self.close()

    def _on_screenshot(self) -> None:
        default = DEFAULT_OUTPUT_DIR / f"{self.data.yml_path.stem}.png"
        path, _ = QFileDialog.getSaveFileName(
            self, "Save screenshot", str(default), "PNG image (*.png)"
        )
        if not path:
            return
        Path(path).parent.mkdir(parents=True, exist_ok=True)
        self._plotter.screenshot(path)
        self._status.showMessage(f"Saved {path}", 5000)

    def _on_export(self) -> None:
        if self._scene is None:
            QMessageBox.information(self, "Not ready", "The scene is still loading.")
            return

        self._clock.pause()
        default = DEFAULT_OUTPUT_DIR / f"{self.data.yml_path.stem}.mp4"
        dialog = ExportDialog(self.data, default,
                              float(self.data.render_cfg.get("speed", 1.0) or 1.0), self)
        if dialog.exec() != QDialog.DialogCode.Accepted:
            return

        settings = dialog.settings()
        settings.scene_options = SceneOptions(
            palette=self.theme.palette,
            show_ground=self._toggle_ground.isChecked(),
            show_tires=self._toggle_tires.isChecked(),
            show_vectors=self._toggle_vectors.isChecked(),
            show_joints=self._toggle_joints.isChecked(),
            show_tracks=self._toggle_tracks.isChecked(),
            show_loads=self._toggle_loads.isChecked(),
        )
        settings.palette = self.theme.palette
        if dialog.use_current_camera:
            self._scene.capture_view()
            settings.camera_offset = self._scene.camera_offset
            settings.camera_mode = self._scene.camera_mode
            settings.focus_point = self._focus.currentText()

        self._run_export(settings)

    def _run_export(self, settings: ExportSettings) -> None:
        total = len(settings.frame_times(self.data))
        progress = QProgressDialog(
            f"Rendering {settings.output.name}…", "Cancel", 0, total, self
        )
        progress.setWindowTitle(f"{APP_NAME} - Export")
        progress.setWindowModality(Qt.WindowModality.ApplicationModal)
        progress.setMinimumDuration(0)
        progress.setAutoClose(False)
        progress.setValue(0)

        started = time.perf_counter()

        def on_frame(done: int, count: int) -> bool:
            progress.setValue(done)
            if done > 2:
                rate = done / max(time.perf_counter() - started, 1e-6)
                remaining = (count - done) / max(rate, 1e-6)
                progress.setLabelText(
                    f"Rendering {settings.output.name}…\n"
                    f"frame {done} of {count}  ({remaining:.0f} s left)"
                )
            QApplication.processEvents()
            return not progress.wasCanceled()

        self._export_button.setEnabled(False)
        try:
            written = render_video(self.data, settings, on_frame)
        except ExportCancelled:
            self._status.showMessage("Export cancelled", 5000)
            return
        except (ExportError, VisualConfigError, OSError) as exc:
            QMessageBox.critical(self, "Export failed", str(exc))
            self._status.showMessage("Export failed", 5000)
            return
        finally:
            progress.close()
            self._export_button.setEnabled(True)

        # Reported in the status bar rather than a modal: the progress dialog
        # already showed the work, and a popup to dismiss after every export
        # gets old fast. Failures still interrupt, because those need reading.
        elapsed = time.perf_counter() - started
        self._status.showMessage(
            f"Exported {written.resolve()}  ({elapsed:.1f} s)", 30000
        )

    def _on_about(self) -> None:
        QMessageBox.about(
            self, f"About {APP_NAME}",
            f"<b>{APP_NAME}</b><br>"
            "BobSim suspension and vehicle motion viewer.<br><br>"
            f"Config: {self.data.yml_path}<br>"
            f"Data: {self.data.data_path}<br>"
            f"Samples: {self.data.n_frames} "
            f"({self.data.time[0]:.3f} to {self.data.time[-1]:.3f} s)<br><br>"
            "Headless rendering: <code>python -m _1_VisualSim.run_visual</code>",
        )

    # -- lifecycle ----------------------------------------------------------
    def closeEvent(self, event: Any) -> None:
        self._clock.pause()
        try:
            self._plotter.close()
        except Exception:  # noqa: BLE001 - teardown must not raise
            pass
        super().closeEvent(event)


_WINDOWS: list[ViewerWindow] = []


def _controls_html() -> str:
    rows: list[str] = []
    for group, bindings in CONTROLS:
        rows.append(f"<tr><td colspan='2'><br><b>{group}</b></td></tr>")
        rows.extend(
            f"<tr><td>{key}&nbsp;&nbsp;&nbsp;</td><td>{action}</td></tr>"
            for key, action in bindings
        )
    return (
        "<table cellspacing='2'>" + "".join(rows) + "</table><br>"
        "Free-spinning mouse orbiting when it should zoom? Turn off "
        "<i>View ▸ Two-finger scroll orbits</i>."
    )


def _shorten(text: str, limit: int = 26) -> str:
    """Keep the tail of a long signal path; that is the part that identifies it."""
    return text if len(text) <= limit else "…" + text[-(limit - 1):]


def _muted(text: str) -> QLabel:
    label = QLabel(f" {text} ")
    label.setProperty("role", "muted")
    return label


def _menu_button(text: str, menu: QMenu, tooltip: str) -> QPushButton:
    # Qt draws the same drop-down chevron as on the combo boxes beside it.
    button = QPushButton(text)
    button.setMenu(menu)
    button.setFixedHeight(26)
    button.setToolTip(tooltip)
    return button


def _layer(menu: QMenu, text: str) -> QAction:
    action = QAction(text, menu)
    action.setCheckable(True)
    action.setChecked(True)
    menu.addAction(action)
    return action


# ---------------------------------------------------------------------------
# Entry point
# ---------------------------------------------------------------------------

def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        prog="python -m _1_VisualSim.viewer",
        description=f"{APP_NAME} - interactive BobSim visualizer.",
        epilog="With no paths, a picker opens seeded with the bundled templates.",
    )
    parser.add_argument("config", nargs="?", default="", help="visual YAML config")
    parser.add_argument("data", nargs="?", default="", help="signal file (.npz or .csv)")
    return parser


def main(argv: list[str] | None = None) -> int:
    args = build_parser().parse_args(argv)

    pv.global_theme.allow_empty_mesh = True
    app = QApplication(sys.argv[:1])
    app.setApplicationName(APP_NAME)
    app.setStyleSheet(stylesheet())

    config, data_path = args.config, args.data
    if not (config and data_path):
        dialog = OpenDialog(config, data_path)
        if dialog.exec() != QDialog.DialogCode.Accepted:
            return 0
        config, data_path = str(dialog.choice.config), str(dialog.choice.data)

    try:
        data = SimData(config, data_path)
    except (OSError, VisualConfigError) as exc:
        QMessageBox.critical(None, "Cannot open files", str(exc))
        return 2

    window = ViewerWindow(data)
    _WINDOWS.append(window)
    window.show()
    return app.exec()


if __name__ == "__main__":
    raise SystemExit(main())
