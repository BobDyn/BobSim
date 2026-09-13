"""BobVis window pieces that can be exercised without a GL context.

The Tires and Metrics tabs are plain Qt and matplotlib widgets, so they build
under Qt's offscreen platform. Like ``test_visual_scene.py``, this whole module
skips where BobVis's PyQt6/PyVista stack is not installed (CI and the Docker
image); the arithmetic behind these panels is covered everywhere by
``test_visual_navigation.py`` and ``test_visual_tire_state.py``.
"""

from __future__ import annotations

import os
from pathlib import Path

import numpy as np
import pytest
import yaml

pytest.importorskip("PyQt6.QtWidgets", reason="BobVis's Qt stack is installed via `make visual-deps`")
pytest.importorskip("pyvistaqt", reason="BobVis's Qt stack is installed via `make visual-deps`")

os.environ.setdefault("QT_QPA_PLATFORM", "offscreen")

from PyQt6.QtWidgets import QApplication  # noqa: E402

from _1_VisualSim.from_results import axle_friction, default_vehicle_yaml  # noqa: E402
from _1_VisualSim.scene import SimData  # noqa: E402
from _1_VisualSim.theme import THEME  # noqa: E402
from _1_VisualSim.viewer import (  # noqa: E402
    CONTROLS,
    FrictionPanel,
    MetricsPanel,
    _controls_html,
    _format_metric,
    _read_metrics,
)


@pytest.fixture(scope="module")
def qapp() -> QApplication:
    app = QApplication.instance()
    return app if isinstance(app, QApplication) else QApplication([])


# -- metrics ----------------------------------------------------------------

METRICS_CSV = """standard,group,metric,value,units,description
TransientEval,general,n_cases,8,count,Number of cases
TransientEval,step,ay_overshoot_pct,18.511883252386365,%,Lateral acceleration overshoot
TransientEval,step,yaw_rise_time_s,0.05501276804386701,s,Yaw velocity rise time
TransientEval,trend,ay_peak_velocity_slope,0.368,m/s^2/(m/s),Slope of ay_peak versus velocity
TransientEval,step,,1.0,,A row with no metric name is skipped
"""


@pytest.fixture
def metrics_csv(tmp_path: Path) -> Path:
    path = tmp_path / "run_metrics.csv"
    path.write_text(METRICS_CSV, encoding="utf-8")
    return path


@pytest.mark.parametrize(
    ("raw", "shown"),
    [("8", "8"), ("18.511883252386365", "18.51"), ("0.05501276804386701", "0.05501"),
     ("-1.7763568394002505e-17", "-1.776e-17"), ("n/a", "n/a")],
)
def test_metric_values_are_shown_to_four_significant_figures(raw: str, shown: str) -> None:
    assert _format_metric(raw) == shown


def test_read_metrics_skips_nameless_rows_and_tolerates_a_missing_file(
    metrics_csv: Path, tmp_path: Path
) -> None:
    rows = _read_metrics(metrics_csv)
    assert [r["metric"] for r in rows] == [
        "n_cases", "ay_overshoot_pct", "yaw_rise_time_s", "ay_peak_velocity_slope",
    ]
    assert _read_metrics(tmp_path / "absent.csv") == []


def test_metrics_panel_groups_collapses_trend_and_filters(qapp: QApplication, metrics_csv: Path) -> None:
    panel = MetricsPanel(metrics_csv)
    groups = panel._groups

    assert panel.has_data
    assert list(groups) == ["general", "step", "trend"]
    assert groups["step"].childCount() == 2
    assert groups["step"].child(0).text(1) == "18.51"
    assert groups["step"].child(0).toolTip(0) == "Lateral acceleration overshoot"
    assert groups["step"].isExpanded() and not groups["trend"].isExpanded()

    panel._filter.setText("overshoot")
    assert not groups["step"].child(0).isHidden()
    assert groups["step"].child(1).isHidden()
    assert groups["general"].isHidden()
    # A filter also matches definitions, and opens collapsed groups it matches in.
    panel._filter.setText("versus velocity")
    assert not groups["trend"].isHidden() and groups["trend"].isExpanded()

    panel._filter.setText("")
    assert not groups["general"].isHidden() and not groups["trend"].isExpanded()


def test_metrics_panel_is_empty_for_an_unreadable_file(qapp: QApplication, tmp_path: Path) -> None:
    assert not MetricsPanel(tmp_path / "absent.csv").has_data


# -- friction circles -------------------------------------------------------

def _friction_scene(tmp_path: Path, friction: dict | None) -> SimData:
    n = 11
    time = np.linspace(0.0, 1.0, n)
    fz = np.full(n, 650.0)
    signals = {"time": time}
    corners = {}
    for corner in ("fl", "fr", "rl", "rr"):
        signals[f"force/{corner}_fx"] = np.zeros(n)
        signals[f"force/{corner}_fy"] = np.linspace(0.0, 1.0, n)  # scaled below
        signals[f"force/{corner}_fz"] = fz.copy()
        corners[corner] = {"axle": "front" if corner[0] == "f" else "rear",
                           "fx": f"force/{corner}_fx", "fy": f"force/{corner}_fy",
                           "fz": f"force/{corner}_fz"}
    signals["force/rr_fz"][-1] = 0.0  # the right rear lifts on the last sample

    cfg: dict = {"tire_forces": {"corners": corners}}
    if friction is not None:
        cfg["tire_forces"]["friction"] = friction
        mu_y = abs(friction["front"]["PDY1"])  # nominal load, no camber: mu_y = |PDY1|
        for corner in corners:
            signals[f"force/{corner}_fy"] = signals[f"force/{corner}_fy"] * mu_y * 650.0

    config, data_path = tmp_path / "scene.yml", tmp_path / "scene.npz"
    config.write_text(yaml.safe_dump(cfg), encoding="utf-8")
    np.savez(data_path, **signals)  # type: ignore[arg-type]
    return SimData(config, data_path)


def test_friction_panel_reads_grip_use_from_the_real_tire_file(qapp: QApplication, tmp_path: Path) -> None:
    data = _friction_scene(tmp_path, axle_friction(default_vehicle_yaml()))
    panel = FrictionPanel(data, THEME)

    assert panel.has_data and set(panel._artists) == {"fl", "fr", "rl", "rr"}

    halfway = float(data.time[5])
    panel.set_time(halfway, force=True)
    assert panel._artists["fl"]["value"].get_text() == "50%"
    # Seen from above: lateral force toward the car's left plots to the left.
    x, y = panel._artists["fl"]["dot"].get_data()
    assert x[0] == pytest.approx(-0.5) and y[0] == pytest.approx(0.0)

    panel.set_time(float(data.time[-1]), force=True)
    assert panel._artists["fl"]["value"].get_text() == "100%"
    assert panel._artists["fl"]["dot"].get_color() == FrictionPanel.RED
    assert panel._artists["rr"]["value"].get_text() == "lifted"


def test_friction_panel_needs_a_friction_model(qapp: QApplication, tmp_path: Path) -> None:
    assert not FrictionPanel(_friction_scene(tmp_path, None), THEME).has_data


# -- help -------------------------------------------------------------------

def test_controls_help_covers_orbit_pan_and_zoom_for_mouse_and_touchpad() -> None:
    groups = dict(CONTROLS)
    for device in ("Mouse", "Touchpad"):
        actions = " ".join(action for _, action in groups[device]).lower()
        for verb in ("orbit", "pan", "zoom"):
            assert verb in actions, f"{device} controls never mention {verb}"

    html = _controls_html()
    for _, bindings in CONTROLS:
        for key, _ in bindings:
            assert key in html
