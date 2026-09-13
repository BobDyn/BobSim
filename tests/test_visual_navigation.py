"""BobVis camera navigation checks.

:mod:`_1_VisualSim.navigation` is numpy only, so unlike ``test_visual_scene.py``
these run everywhere, CI included. They pin the properties that make a gesture
feel right or wrong: what stays fixed on screen, what never flips, and which
input a wheel event is taken to be.
"""

from __future__ import annotations

import numpy as np
import pytest

from _1_VisualSim.navigation import (
    MIN_DISTANCE,
    MIN_POLAR_DEG,
    WHEEL_NOTCH,
    ZOOM_PER_NOTCH,
    CameraPose,
    camera_basis,
    classify_wheel,
    focal_plane_point,
    orbit,
    pan,
    project_to_ndc,
    recenter,
    wheel_drag_pixels,
    wheel_zoom_factor,
    zoom_at,
)

ASPECT = 16.0 / 9.0


def _pose(position=(-6.0, -4.0, 3.0), focal=(1.0, 0.5, 0.2), up=(0.0, 0.0, 1.0),
          parallel: bool = False) -> CameraPose:
    pose = CameraPose(
        position=np.array(position, dtype=float),
        focal=np.array(focal, dtype=float),
        up=np.array(up, dtype=float),
        view_angle=30.0,
        parallel_projection=parallel,
        parallel_scale=2.5,
    )
    # Orthogonalise up the way VTK does, so basis checks start clean.
    _, _, true_up = camera_basis(pose)
    return CameraPose(pose.position, pose.focal, true_up, pose.view_angle,
                      pose.parallel_projection, pose.parallel_scale)


def _distance(pose: CameraPose) -> float:
    return float(np.linalg.norm(pose.focal - pose.position))


# -- orbit ------------------------------------------------------------------

def test_orbit_keeps_distance_focal_and_height_for_pure_azimuth() -> None:
    before = _pose()
    after = orbit(before, 90.0, 0.0)

    np.testing.assert_allclose(after.focal, before.focal)
    assert _distance(after) == pytest.approx(_distance(before))
    assert after.position[2] == pytest.approx(before.position[2])


def test_orbit_azimuth_is_counter_clockwise_from_above() -> None:
    before = _pose(position=(0.0, -5.0, 0.0), focal=(0.0, 0.0, 0.0))  # south, looking north
    after = orbit(before, 90.0, 0.0)
    np.testing.assert_allclose(after.position, [5.0, 0.0, 0.0], atol=1e-9)  # now east


def test_orbit_elevation_raises_and_stops_short_of_the_pole() -> None:
    before = _pose()
    raised = orbit(before, 0.0, 20.0)
    assert raised.position[2] > before.position[2]

    over_the_top = orbit(before, 0.0, 400.0)
    offset = over_the_top.position - over_the_top.focal
    polar = np.degrees(np.arccos(offset[2] / np.linalg.norm(offset)))
    assert polar == pytest.approx(MIN_POLAR_DEG)
    assert over_the_top.up @ np.array([0.0, 0.0, 1.0]) > 0.0  # not upside down


def test_orbit_levels_roll() -> None:
    rolled = _pose(up=(0.3, 0.0, 1.0))
    after = orbit(rolled, 5.0, 0.0)
    _, right, _ = camera_basis(after)
    assert right[2] == pytest.approx(0.0, abs=1e-9)


def test_orbit_from_a_top_view_tilts_without_spinning_the_picture() -> None:
    """Regression guard: straight-down views have no azimuth to start from."""
    top = CameraPose(np.array([0.0, 0.0, 10.0]), np.zeros(3), np.array([0.0, 1.0, 0.0]))
    after = orbit(top, 0.0, -10.0)

    assert after.position[1] < 0.0  # swung toward the bottom of the screen
    assert abs(after.position[0]) < 1e-9
    assert after.up[1] > 0.0  # screen-up still points along +y


# -- pan --------------------------------------------------------------------

def test_pan_translates_camera_and_focal_together() -> None:
    before = _pose()
    after = pan(before, 37.0, -12.0, 800.0)

    np.testing.assert_allclose(after.position - before.position, after.focal - before.focal)
    np.testing.assert_allclose(camera_basis(after)[0], camera_basis(before)[0])


def test_pan_moves_one_visible_height_per_viewport_height() -> None:
    before = _pose()
    height_px = 600.0
    after = pan(before, 0.0, height_px, height_px)

    visible = 2.0 * _distance(before) * np.tan(np.radians(before.view_angle) / 2.0)
    assert np.linalg.norm(after.focal - before.focal) == pytest.approx(visible)


def test_dragging_right_moves_the_camera_left() -> None:
    before = _pose()
    _, right, _ = camera_basis(before)
    after = pan(before, 50.0, 0.0, 600.0)
    assert (after.position - before.position) @ right < 0.0


# -- zoom -------------------------------------------------------------------

@pytest.mark.parametrize("ndc", [(0.0, 0.0), (0.6, -0.4), (-0.9, 0.8)])
@pytest.mark.parametrize("parallel", [False, True])
def test_zoom_keeps_the_point_under_the_cursor_fixed(ndc: tuple[float, float], parallel: bool) -> None:
    before = _pose(parallel=parallel)
    target = focal_plane_point(before, *ndc, ASPECT)
    after = zoom_at(before, 1.8, *ndc, ASPECT)

    assert project_to_ndc(after, target, ASPECT) == pytest.approx(ndc, abs=1e-9)


def test_zoom_at_centre_divides_distance_by_factor() -> None:
    before = _pose()
    after = zoom_at(before, 2.0, 0.0, 0.0, ASPECT)
    assert _distance(after) == pytest.approx(_distance(before) / 2.0)
    np.testing.assert_allclose(camera_basis(after)[0], camera_basis(before)[0])


def test_zoom_out_then_in_round_trips() -> None:
    before = _pose()
    after = zoom_at(zoom_at(before, 1.4, 0.3, 0.2, ASPECT), 1 / 1.4, 0.3, 0.2, ASPECT)
    np.testing.assert_allclose(after.position, before.position, atol=1e-9)
    np.testing.assert_allclose(after.focal, before.focal, atol=1e-9)


def test_zoom_never_passes_the_minimum_distance() -> None:
    after = zoom_at(_pose(), 1e6, 0.0, 0.0, ASPECT)
    assert _distance(after) == pytest.approx(MIN_DISTANCE)


def test_parallel_zoom_scales_the_view_not_the_distance() -> None:
    before = _pose(parallel=True)
    after = zoom_at(before, 2.0, 0.0, 0.0, ASPECT)
    assert after.parallel_scale == pytest.approx(before.parallel_scale / 2.0)
    assert _distance(after) == pytest.approx(_distance(before))


def test_recenter_moves_the_orbit_centre_without_turning() -> None:
    before = _pose()
    point = np.array([3.0, -2.0, 0.5])
    after = recenter(before, point)
    np.testing.assert_allclose(after.focal, point)
    np.testing.assert_allclose(camera_basis(after)[0], camera_basis(before)[0])


# -- wheel ------------------------------------------------------------------

@pytest.mark.parametrize(
    ("kwargs", "expected"),
    [
        ({"angle_dx": 0, "angle_dy": 120}, "zoom"),              # mouse notch
        ({"angle_dx": 0, "angle_dy": -240}, "zoom"),             # fast mouse spin
        ({"angle_dx": 0, "angle_dy": 12}, "orbit"),              # Windows precision touchpad
        ({"angle_dx": -30, "angle_dy": 0}, "orbit"),             # sideways swipe
        ({"angle_dx": 0, "angle_dy": 12, "shift": True}, "pan"),
        ({"angle_dx": 0, "angle_dy": 12, "ctrl": True}, "zoom"),  # Windows pinch
        ({"angle_dx": 0, "angle_dy": 120, "pixel_dy": 40}, "orbit"),       # macOS trackpad
        ({"angle_dx": 0, "angle_dy": 120, "scroll_phase": True}, "orbit"),
        ({"angle_dx": 0, "angle_dy": 120, "touchpad_device": True}, "orbit"),
        ({"angle_dx": 0, "angle_dy": 120, "recent_touchpad": True}, "orbit"),
        ({"angle_dx": 0, "angle_dy": 12, "detect_touchpad": False}, "zoom"),
        ({"angle_dx": 0, "angle_dy": 0}, "none"),
    ],
)
def test_classify_wheel(kwargs: dict, expected: str) -> None:
    assert classify_wheel(**kwargs) == expected


def test_wheel_zoom_is_proportional_to_scroll_distance() -> None:
    assert wheel_zoom_factor(0, WHEEL_NOTCH) == pytest.approx(ZOOM_PER_NOTCH)
    assert wheel_zoom_factor(0, -WHEEL_NOTCH) == pytest.approx(1.0 / ZOOM_PER_NOTCH)
    ten_small = np.prod([wheel_zoom_factor(0, WHEEL_NOTCH // 10) for _ in range(10)])
    assert ten_small == pytest.approx(ZOOM_PER_NOTCH)


def test_wheel_drag_prefers_pixel_deltas() -> None:
    assert wheel_drag_pixels(0, 120, pixel_dx=3, pixel_dy=-7) == (3.0, -7.0)
    dx, dy = wheel_drag_pixels(-120, 60)
    assert dx < 0.0 < dy
