"""BobVis ``SimData`` and exporter contract checks.

Both import :mod:`_1_VisualSim.scene`, which needs PyVista. That is installed
separately (``make visual-deps``) and is absent from CI and the Docker image,
so this whole module skips there; the template and demo-scene checks that must
run everywhere are in ``test_visual_templates.py``.

Nothing here draws - rendering needs a GL context. These cover the arithmetic
around it: stride, signal resolution, and export frame times.
"""

from __future__ import annotations

from pathlib import Path

import numpy as np
import pytest
import yaml

from _1_VisualSim import demo

pytest.importorskip(
    "pyvista",
    reason="BobVis rendering deps are installed separately via `make visual-deps`",
)

from _1_VisualSim.exporter import (  # noqa: E402
    ExportError,
    ExportSettings,
    parse_resolution,
)
from _1_VisualSim.scene import (  # noqa: E402
    SimData,
    VisualConfigError,
    grid_lines,
    load_disc_radius,
    resolve_load_reference,
    trail_indices,
)



@pytest.fixture
def demo_scene(tmp_path: Path) -> tuple[Path, Path]:
    return demo.write(tmp_path, duration=0.5)


def test_simdata_loads_the_demo_scene(demo_scene: tuple[Path, Path]) -> None:
    data = SimData(*demo_scene)

    assert data.n_frames == len(data.time)
    assert data.duration > 0.0
    assert data.point_names
    assert not data.required_signals() - set(data.signals)
    assert "time" not in data.signal_names


def test_simdata_reports_missing_signals_by_name(tmp_path: Path) -> None:
    config = tmp_path / "config.yml"
    config.write_text(
        yaml.safe_dump({"geometry": {"points": {"a": ["x", "y", "z"]}}}),
        encoding="utf-8",
    )
    data_path = tmp_path / "data.npz"
    np.savez(data_path, time=np.linspace(0.0, 1.0, 10), x=np.zeros(10))

    with pytest.raises(VisualConfigError, match=r"\by\b"):
        SimData(config, data_path)


def test_input_stride_applies_to_time_as_well_as_geometry(tmp_path: Path) -> None:
    """Regression: geometry was strided while time was not, desyncing the timeline."""
    n = 40
    config = tmp_path / "config.yml"
    config.write_text(
        yaml.safe_dump({
            "render": {"input_stride": 4},
            "geometry": {"points": {"a": ["x", "y", "z"]}},
        }),
        encoding="utf-8",
    )
    data_path = tmp_path / "data.npz"
    np.savez(
        data_path,
        time=np.linspace(0.0, 1.0, n),
        x=np.zeros(n), y=np.zeros(n), z=np.zeros(n),
    )

    data = SimData(config, data_path)
    assert data.input_stride == 4
    assert data.n_frames == len(np.arange(n)[::4])
    assert len(data.get_signal("x")) == data.n_frames


def test_simdata_rejects_a_data_file_without_time(tmp_path: Path) -> None:
    config = tmp_path / "config.yml"
    config.write_text(yaml.safe_dump({"geometry": {"points": {}}}), encoding="utf-8")
    data_path = tmp_path / "data.npz"
    np.savez(data_path, x=np.zeros(4))

    with pytest.raises(VisualConfigError, match="time"):
        SimData(config, data_path)


def test_simdata_reads_csv(tmp_path: Path) -> None:
    config = tmp_path / "config.yml"
    config.write_text(
        yaml.safe_dump({"geometry": {"points": {"a": ["x", "y", "z"]}}}),
        encoding="utf-8",
    )
    csv_path = tmp_path / "data.csv"
    csv_path.write_text(
        "time,x,y,z\n0.0,0,0,0\n0.1,1,0,0\n0.2,2,0,0\n", encoding="utf-8"
    )

    data = SimData(config, csv_path)
    assert data.n_frames == 3
    assert data.get_signal("x")[-1] == pytest.approx(2.0)


def _tire_force_config(corners: dict) -> dict:
    return {"tire_forces": {"corners": corners, "friction": {"front": {"FNOMIN": 650.0}}}}


def test_simdata_requires_the_tire_force_signals_it_names(tmp_path: Path) -> None:
    config = tmp_path / "config.yml"
    config.write_text(yaml.safe_dump(_tire_force_config({
        "fl": {"axle": "front", "fx": "force/fl_fx", "fy": "force/fl_fy",
               "fz": "force/fl_fz", "gamma": "force/fl_gamma"},
    })), encoding="utf-8")
    data_path = tmp_path / "data.npz"
    n = 5
    signals = {"time": np.linspace(0.0, 1.0, n), "force/fl_fx": np.zeros(n),
               "force/fl_fy": np.zeros(n), "force/fl_fz": np.full(n, 700.0)}
    np.savez(data_path, **signals)  # type: ignore[arg-type]

    # Camber is named but missing, so the scene refuses to load and says which.
    with pytest.raises(VisualConfigError, match="force/fl_gamma"):
        SimData(config, data_path)

    np.savez(data_path, **signals, **{"force/fl_gamma": np.zeros(n)})  # type: ignore[arg-type]
    data = SimData(config, data_path)
    assert set(data.tire_forces_cfg["corners"]) == {"fl"}


def test_simdata_resolves_the_metrics_csv_against_the_config_folder(tmp_path: Path) -> None:
    data_path = tmp_path / "data.npz"
    np.savez(data_path, time=np.linspace(0.0, 1.0, 3))
    metrics = tmp_path / "metrics" / "run.csv"
    metrics.parent.mkdir()
    metrics.write_text("metric\n", encoding="utf-8")

    scene_dir = tmp_path / "scene"
    scene_dir.mkdir()
    config = scene_dir / "config.yml"

    config.write_text(yaml.safe_dump({"metrics": {"path": "../metrics/run.csv"}}), encoding="utf-8")
    assert SimData(config, data_path).metrics_path == (scene_dir / "../metrics/run.csv")

    config.write_text(yaml.safe_dump({"metrics": {"path": "../metrics/gone.csv"}}), encoding="utf-8")
    assert SimData(config, data_path).metrics_path is None  # no Metrics tab for a missing file

    config.write_text(yaml.safe_dump({"render": {}}), encoding="utf-8")
    assert SimData(config, data_path).metrics_path is None


def test_frame_times_follow_fps_speed_and_range(demo_scene: tuple[Path, Path]) -> None:
    data = SimData(*demo_scene)
    settings = ExportSettings(
        output=Path("unused.mp4"), fps=40, speed=2.0,
        start_time=0.1, end_time=0.4,
    )

    times = settings.frame_times(data)
    # 0.3 s of sim at 2x is 0.15 s of video, so 6 frames at 40 fps.
    assert len(times) == 6
    assert times[0] == pytest.approx(0.1)
    assert times[-1] == pytest.approx(0.4)


def test_export_range_must_be_forwards(demo_scene: tuple[Path, Path]) -> None:
    data = SimData(*demo_scene)
    settings = ExportSettings(output=Path("unused.mp4"), start_time=0.4, end_time=0.2)

    with pytest.raises(ExportError):
        settings.frame_times(data)


def test_trail_covers_the_history_window_and_ends_on_the_current_sample() -> None:
    time = np.linspace(0.0, 10.0, 101)  # 0.1 s samples

    idx = trail_indices(time, 50, history=2.0)
    assert idx[0] == 30 and idx[-1] == 50

    # Decimated trails sit on a fixed grid, so they do not crawl during playback.
    strided = trail_indices(time, 50, history=2.0, stride=4)
    assert strided[-1] == 50
    assert all(i % 4 == 0 for i in strided[:-1])


def test_load_footprint_area_scales_with_load() -> None:
    static = load_disc_radius(1.0, 0.2)
    assert static == pytest.approx(0.2)
    assert (load_disc_radius(2.0, 0.2) / static) ** 2 == pytest.approx(2.0)
    assert load_disc_radius(-0.5, 0.2) == 0.0  # a lifted tire has no footprint


def test_load_reference_is_the_median_not_the_unsettled_first_sample() -> None:
    # VehicleSim's first sample sits light before the car settles.
    load = np.array([710.0, 780.0, 781.0, 779.0, 900.0, 660.0])
    assert resolve_load_reference(load) == pytest.approx(779.5)
    # A mostly-lifted tire falls back to its peak rather than dividing by zero.
    assert resolve_load_reference(np.array([0.0, 0.0, 600.0])) == 600.0


def test_minor_grid_skips_the_lines_the_major_grid_draws() -> None:
    # A 10 m square: ticks at -5..5 every metre, bold at -5, 0 and 5.
    assert grid_lines(10.0, 5.0).n_cells == 2 * 3
    assert grid_lines(10.0, 1.0, skip_pitch=5.0).n_cells == 2 * 8


@pytest.mark.parametrize(
    ("value", "expected"),
    [("1080p", (1920, 1080)), ("720p", (1280, 720)), ("640x360", (640, 360))],
)
def test_parse_resolution(value: str, expected: tuple[int, int]) -> None:
    assert parse_resolution(value) == expected


def test_parse_resolution_rejects_nonsense() -> None:
    with pytest.raises(ExportError):
        parse_resolution("enormous")
