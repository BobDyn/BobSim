"""The browser camera must agree with ``_1_VisualSim/navigation.py``.

The viewer moved to WebGL, but the arithmetic that decides how a drag feels did
not change: ``_5_App/static/visual.js`` is a port of ``navigation.py``, constant
for constant. That module and ``tests/test_visual_navigation.py`` stay as the
reference, and this pins the port to them.

It is worth the machinery. Getting this arithmetic wrong is what made the first
pass at these controls feel broken (#48, rolled back in #50), and a JS
translation is exactly the kind of change that silently drifts -- a flipped
sign, a degree-radian slip -- while still looking plausible on screen.

Needs ``node``, which CI does not have, so it skips there and runs on a dev
machine. The Python side is covered either way.
"""

from __future__ import annotations

import json
from pathlib import Path
import shutil
import subprocess
from typing import Any

import numpy as np
import pytest

from _1_VisualSim import navigation as nav

ROOT = Path(__file__).resolve().parents[1]
VISUAL_JS = ROOT / "_5_App/static/visual.js"

pytestmark = pytest.mark.skipif(
    shutil.which("node") is None,
    reason="the browser camera is checked against node, which CI does not install",
)

# A pose that is generic on purpose: off every axis, so a transposed cross
# product or a swapped sine cannot pass by symmetry.
POSE: dict[str, Any] = {
    "position": [3.2, -4.1, 2.4],
    "focal": [0.3, 0.15, 0.42],
    "up": [0.0, 0.0, 1.0],
    "viewAngle": 30.0,
}

ASPECT = 1.6

CASES: list[dict[str, Any]] = [
    {"op": "orbit", "args": [37.0, -12.0]},
    {"op": "orbit", "args": [-180.0, 0.0]},
    {"op": "orbit", "args": [0.0, 400.0]},  # clamps at the pole
    {"op": "pan", "args": [64.0, -25.0, 720.0]},
    {"op": "zoomAt", "args": [1.15, 0.4, -0.3, ASPECT]},
    {"op": "zoomAt", "args": [0.5, -0.9, 0.8, ASPECT]},
    {"op": "recenter", "args": [[1.5, -0.5, 0.25]]},
]

RAY_CASES = [(0.0, 0.0), (0.45, -0.32), (-0.8, 0.6), (0.0, 0.97)]


def _python_pose(pose: dict[str, Any]) -> nav.CameraPose:
    return nav.CameraPose(
        position=np.array(pose["position"], dtype=float),
        focal=np.array(pose["focal"], dtype=float),
        up=np.array(pose["up"], dtype=float),
        view_angle=pose["viewAngle"],
    )


def _run_node(script: str) -> dict[str, Any]:
    result = subprocess.run(
        ["node", "-e", script],
        cwd=ROOT,
        capture_output=True,
        text=True,
        timeout=60,
    )
    assert result.returncode == 0, f"node failed:\n{result.stderr}"
    return json.loads(result.stdout)


def _browser_results() -> dict[str, Any]:
    script = f"""
    globalThis.window = globalThis;
    require("fs").readFileSync({json.dumps(str(VISUAL_JS))}, "utf8");
    eval(require("fs").readFileSync({json.dumps(str(VISUAL_JS))}, "utf8"));
    const cam = window.BobVis.camera;
    const pose = {json.dumps(POSE)};
    const out = {{ ops: [], ground: [], focal: [], wheel: [] }};
    for (const c of {json.dumps(CASES)}) {{
      const p = cam[c.op](pose, ...c.args);
      out.ops.push({{ position: p.position, focal: p.focal, up: p.up }});
    }}
    for (const [x, y] of {json.dumps(RAY_CASES)}) {{
      out.ground.push(cam.groundPlanePoint(pose, x, y, {ASPECT}, 0.0));
      out.focal.push(cam.focalPlanePoint(pose, x, y, {ASPECT}));
    }}
    // A mouse notch is 120 Qt units; the browser reports the same scroll as
    // 40 pixels, and up must zoom in on both.
    out.wheel.push(cam.wheelZoomFactor({{ deltaY: -40, deltaMode: 0 }}));
    out.wheel.push(cam.wheelZoomFactor({{ deltaY: 40, deltaMode: 0 }}));
    out.wheel.push(cam.wheelZoomFactor({{ deltaY: -20, deltaMode: 0 }}));
    console.log(JSON.stringify(out));
    """
    return _run_node(script)


def test_browser_camera_matches_navigation_module() -> None:
    """Every camera operation lands the pose where numpy says it should."""
    browser = _browser_results()
    pose = _python_pose(POSE)

    for case, got in zip(CASES, browser["ops"], strict=True):
        if case["op"] == "orbit":
            want = nav.orbit(pose, *case["args"])
        elif case["op"] == "pan":
            want = nav.pan(pose, *case["args"])
        elif case["op"] == "zoomAt":
            want = nav.zoom_at(pose, *case["args"])
        else:
            want = nav.recenter(pose, np.array(case["args"][0], dtype=float))

        label = f"{case['op']}{case['args']}"
        assert np.allclose(got["position"], want.position, atol=1e-9), f"{label} position"
        assert np.allclose(got["focal"], want.focal, atol=1e-9), f"{label} focal"
        assert np.allclose(got["up"], want.up, atol=1e-9), f"{label} up"


def test_browser_cursor_rays_match_navigation_module() -> None:
    """Zoom-to-cursor and click-to-recentre both hang off these two."""
    browser = _browser_results()
    pose = _python_pose(POSE)

    for (ndc_x, ndc_y), got in zip(RAY_CASES, browser["focal"], strict=True):
        want = nav.focal_plane_point(pose, ndc_x, ndc_y, ASPECT)
        assert np.allclose(got, want, atol=1e-9), f"focal plane at {ndc_x},{ndc_y}"

    for (ndc_x, ndc_y), got in zip(RAY_CASES, browser["ground"], strict=True):
        expected = nav.ground_plane_point(pose, ndc_x, ndc_y, ASPECT, 0.0)
        if expected is None:
            assert got is None, f"ground at {ndc_x},{ndc_y} should have been refused"
        else:
            assert got is not None, f"ground at {ndc_x},{ndc_y} should have hit"
            assert np.allclose(got, expected, atol=1e-9), f"ground at {ndc_x},{ndc_y}"


def test_browser_wheel_zoom_matches_one_mouse_notch() -> None:
    """A wheel notch zooms the same distance whatever the platform calls it."""
    browser = _browser_results()
    up, down, half = browser["wheel"]

    assert up == pytest.approx(nav.wheel_zoom_factor(0, nav.WHEEL_NOTCH), rel=1e-12)
    assert down == pytest.approx(nav.wheel_zoom_factor(0, -nav.WHEEL_NOTCH), rel=1e-12)
    assert up > 1.0 > down, "scrolling up zooms in, down zooms out"
    # Ten tenth-of-a-notch trackpad events must zoom exactly as far as one notch.
    assert half**2 == pytest.approx(up, rel=1e-12)
