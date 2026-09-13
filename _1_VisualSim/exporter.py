"""Off-screen video export for BobVis.

The exporter renders the same :class:`~_1_VisualSim.scene.VisualScene` the
viewer shows, but into an off-screen plotter at an arbitrary resolution, and
muxes the frames into an MP4 or animated GIF.

It is used two ways:

* from the viewer's *Export video* button, with the live camera handed over so
  the file matches what the user framed on screen;
* from the ``python -m _1_VisualSim.run_visual`` CLI, headless.
"""

from __future__ import annotations

from dataclasses import dataclass, replace
from pathlib import Path
from typing import Any, Callable, Sequence

import numpy as np

from _1_VisualSim.scene import (
    CameraOffset,
    LIGHT,
    Palette,
    SceneOptions,
    SimData,
    build_offscreen_scene,
)

ProgressFn = Callable[[int, int], bool]
"""``(frame_index, total_frames) -> keep_going``. Return False to cancel."""

RESOLUTIONS: dict[str, tuple[int, int]] = {
    "720p": (1280, 720),
    "1080p": (1920, 1080),
    "1440p": (2560, 1440),
    "square": (1080, 1080),
}


class ExportError(RuntimeError):
    """Raised when a video cannot be written."""


@dataclass
class ExportSettings:
    """Everything that determines the contents of an exported file."""

    output: Path
    width: int = 1920
    height: int = 1080
    fps: int = 60
    speed: float = 1.0
    start_time: float | None = None
    end_time: float | None = None
    show_plots: bool = True
    quality: int = 8
    palette: Palette | None = None
    scene_options: SceneOptions | None = None
    camera_offset: CameraOffset | None = None
    camera_mode: str | None = None
    focus_point: str | None = None

    def resolved_range(self, data: SimData) -> tuple[float, float]:
        t0 = float(data.time[0] if self.start_time is None else self.start_time)
        t1 = float(data.time[-1] if self.end_time is None else self.end_time)
        t0 = float(np.clip(t0, data.time[0], data.time[-1]))
        t1 = float(np.clip(t1, data.time[0], data.time[-1]))
        if t1 <= t0:
            raise ExportError("Export end time must be after the start time.")
        return t0, t1

    def frame_times(self, data: SimData) -> np.ndarray:
        t0, t1 = self.resolved_range(data)
        speed = max(float(self.speed), 1e-6)
        n_frames = max(2, int(round((t1 - t0) / speed * self.fps)))
        return np.linspace(t0, t1, n_frames)


# ---------------------------------------------------------------------------
# Signal strip
# ---------------------------------------------------------------------------

class SignalStrip:
    """Matplotlib panel of the config's ``plots``, with a moving time cursor.

    Rendered to an RGB array once per frame and stacked beside the 3D view.
    """

    MAX_PLOTS = 4

    def __init__(self, data: SimData, height_px: int, palette: Palette) -> None:
        import matplotlib

        matplotlib.use("Agg", force=False)
        from matplotlib.figure import Figure

        self.data = data
        self.palette = palette
        # Past four traces in a fixed-height column the axis labels collide and
        # each trace is too short to read. Take the first few; the viewer's
        # panel scrolls and can show the rest.
        self.plots = data.plots_cfg[: self.MAX_PLOTS]
        self._cursors: list[Any] = []

        dpi = 100.0
        n = max(1, len(self.plots))
        fig_h = height_px / dpi
        self.fig = Figure(figsize=(0.52 * fig_h, fig_h), dpi=dpi)
        self.fig.patch.set_facecolor(palette.background_top)

        axes = self.fig.subplots(n, 1, sharex=True)
        self._axes = list(np.atleast_1d(axes))

        for ax, plot in zip(self._axes, self.plots):
            x = data.get_signal(str(plot.get("x", "time")))
            y = data.get_signal(str(plot["y"]))
            ax.plot(x, y, linewidth=1.6, color=palette.accent)
            ax.set_ylabel(_wrap_label(str(plot.get("name", plot["y"]))),
                          fontsize=8, color=palette.text)
            _style_axes(ax, palette)
            self._cursors.append(
                ax.axvline(float(data.time[0]), color="#e0483c", linewidth=1.2)
            )

        if self.plots:
            self._axes[-1].set_xlabel("Time (s)", fontsize=9, color=palette.text)

        self.fig.subplots_adjust(left=0.26, right=0.97, top=0.98, bottom=0.08,
                                 hspace=0.26)
        self._canvas = _figure_canvas(self.fig)
        self._canvas.draw()
        self._w, self._h = self._canvas.get_width_height()

    @property
    def is_empty(self) -> bool:
        return not self.plots

    def render(self, sim_time: float, target_height: int) -> np.ndarray:
        from PIL import Image

        for cursor in self._cursors:
            cursor.set_xdata([float(sim_time)])
        self._canvas.draw()

        buf = np.frombuffer(self._canvas.buffer_rgba(), dtype=np.uint8)
        img = buf.reshape((self._h, self._w, 4))[:, :, :3]

        target_w = max(1, int(round(self._w * target_height / self._h)))
        return np.asarray(
            Image.fromarray(img).resize((target_w, target_height),
                                        resample=Image.Resampling.LANCZOS),
            dtype=np.uint8,
        )


def _wrap_label(text: str, width: int = 18) -> str:
    """Break a long axis label onto a second line rather than let it collide."""
    if len(text) <= width:
        return text
    head, sep, tail = text[:width].rpartition(" ")
    if not sep:
        return text
    return head + "\n" + text[len(head) + 1:]


def _figure_canvas(fig: Any) -> Any:
    from matplotlib.backends.backend_agg import FigureCanvasAgg

    return FigureCanvasAgg(fig)


def _style_axes(ax: Any, palette: Palette) -> None:
    ax.set_facecolor(palette.background_top)
    ax.grid(True, linestyle="--", linewidth=0.5, alpha=0.35, color=palette.grid)
    for side in ("top", "right"):
        ax.spines[side].set_visible(False)
    for side in ("left", "bottom"):
        ax.spines[side].set_color(palette.grid)
    ax.tick_params(axis="both", labelsize=8, colors=palette.text,
                   length=3, width=0.6)


# ---------------------------------------------------------------------------
# Export
# ---------------------------------------------------------------------------

def _even(n: int) -> int:
    """H.264 needs even dimensions; round down rather than rescale."""
    return int(n) - (int(n) % 2)


def _open_writer(settings: ExportSettings) -> Any:
    try:
        import imageio.v2 as imageio
    except ImportError as exc:  # pragma: no cover - dependency guard
        raise ExportError(
            "imageio is required for video export. Run this in the BobVis "
            "container: make visual-export / make visual-image"
        ) from exc

    suffix = settings.output.suffix.lower()
    settings.output.parent.mkdir(parents=True, exist_ok=True)

    if suffix == ".gif":
        return imageio.get_writer(settings.output, mode="I",
                                  duration=1.0 / max(settings.fps, 1), loop=0)
    if suffix not in (".mp4", ".mov", ".webm"):
        raise ExportError(
            f"Unsupported video extension {suffix!r}; use .mp4, .mov, .webm or .gif"
        )
    try:
        return imageio.get_writer(
            settings.output,
            fps=settings.fps,
            quality=settings.quality,
            macro_block_size=1,
        )
    except Exception as exc:  # noqa: BLE001 - surface a usable message
        raise ExportError(
            f"Could not open {settings.output.name} for writing. "
            "An ffmpeg backend is required; run it in the BobVis container.\n"
            f"({exc})"
        ) from exc


def render_video(
    data: SimData,
    settings: ExportSettings,
    progress: ProgressFn | None = None,
) -> Path:
    """Render ``data`` to a video file. Returns the path actually written.

    ``progress`` is called once per frame and may return ``False`` to cancel,
    in which case the partial file is removed and :class:`ExportError` is not
    raised - the caller gets ``None``-free control back via the cancel path.
    """
    width, height = _even(settings.width), _even(settings.height)
    if width < 64 or height < 64:
        raise ExportError("Export resolution must be at least 64x64.")

    options = settings.scene_options or SceneOptions()
    if settings.palette is not None:
        options = options.copy_with(palette=settings.palette)

    times = settings.frame_times(data)
    plotter, scene = build_offscreen_scene(data, (width, height), options)

    try:
        if settings.focus_point:
            scene.set_focus_point(settings.focus_point)
        if settings.camera_mode:
            scene.camera_mode = settings.camera_mode
        if settings.camera_offset is not None:
            scene.camera_offset = settings.camera_offset

        strip: SignalStrip | None = None
        if settings.show_plots and data.plots_cfg:
            strip = SignalStrip(data, height, options.palette)
            if strip.is_empty:
                strip = None

        writer = _open_writer(settings)
        cancelled = False
        try:
            for index, sim_time in enumerate(times):
                scene.update_time(float(sim_time))
                plotter.render()

                frame = np.asarray(plotter.screenshot(return_img=True), dtype=np.uint8)
                if frame.ndim == 3 and frame.shape[2] == 4:
                    frame = frame[:, :, :3]

                if strip is not None:
                    frame = np.hstack([frame, strip.render(float(sim_time), frame.shape[0])])

                writer.append_data(frame[: _even(frame.shape[0]), : _even(frame.shape[1])])

                if progress is not None and not progress(index + 1, len(times)):
                    cancelled = True
                    break
        finally:
            writer.close()

        if cancelled:
            settings.output.unlink(missing_ok=True)
            raise ExportCancelled(settings.output)
        return settings.output
    finally:
        plotter.close()


class ExportCancelled(Exception):
    """Raised when ``progress`` asked to stop; the partial file is deleted."""

    def __init__(self, output: Path) -> None:
        super().__init__(f"Export cancelled before {output.name} was finished")
        self.output = output


def parse_resolution(value: str) -> tuple[int, int]:
    """``'1080p'`` or ``'1920x1080'`` to a (width, height) pair."""
    if value in RESOLUTIONS:
        return RESOLUTIONS[value]
    text = value.lower().replace(" ", "")
    if "x" in text:
        left, _, right = text.partition("x")
        try:
            return int(left), int(right)
        except ValueError:
            pass
    raise ExportError(
        f"Unknown resolution {value!r}; choose from "
        f"{', '.join(sorted(RESOLUTIONS))} or pass WIDTHxHEIGHT"
    )


def settings_from_args(
    output: str | Path,
    resolution: str | Sequence[int] = "1080p",
    fps: int = 60,
    speed: float = 1.0,
    show_plots: bool = True,
    quality: int = 8,
) -> ExportSettings:
    """Build :class:`ExportSettings` from CLI-shaped values."""
    if isinstance(resolution, str):
        width, height = parse_resolution(resolution)
    else:
        width, height = int(resolution[0]), int(resolution[1])

    return ExportSettings(
        output=Path(output),
        width=width,
        height=height,
        fps=int(fps),
        speed=float(speed),
        show_plots=bool(show_plots),
        quality=int(quality),
        palette=LIGHT,
        scene_options=SceneOptions(palette=LIGHT),
    )


def with_output(settings: ExportSettings, output: str | Path) -> ExportSettings:
    return replace(settings, output=Path(output))
