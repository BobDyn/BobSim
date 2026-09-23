"""BobVis camera navigation checks. Numpy only, so these run in CI."""

from __future__ import annotations

import numpy as np
import pytest

from _1_VisualSim.navigation import (
    GROUND_REACH,
    MIN_DISTANCE,
    MIN_POLAR_DEG,
    WHEEL_NOTCH,
    ZOOM_PER_NOTCH,
    CameraPose,
    camera_basis,
    cursor_ray,
    focal_plane_point,
    ground_plane_point,
    orbit,
    pan,
    project_to_ndc,
    recenter,
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


def test_cursor_ray_starts_at_the_eye_and_points_through_the_cursor() -> None:
    pose = _pose()
    origin, direction = cursor_ray(pose, 0.4, -0.2, ASPECT)
    np.testing.assert_allclose(origin, pose.position)
    assert np.linalg.norm(direction) == pytest.approx(1.0)
    through = focal_plane_point(pose, 0.4, -0.2, ASPECT)
    np.testing.assert_allclose(direction, (through - pose.position)
                               / np.linalg.norm(through - pose.position))


def test_parallel_cursor_ray_runs_along_the_view_direction() -> None:
    pose = _pose(parallel=True)
    _, direction = cursor_ray(pose, 0.4, -0.2, ASPECT)
    np.testing.assert_allclose(direction, camera_basis(pose)[0], atol=1e-12)


@pytest.mark.parametrize("parallel", [False, True])
def test_ground_point_lands_on_the_plane_under_the_cursor(parallel: bool) -> None:
    """A double-click on the floor recentres there: the plane is not pickable."""
    pose = _pose(position=(-6.0, -4.0, 3.0), focal=(0.0, 0.0, 0.0), parallel=parallel)
    point = ground_plane_point(pose, 0.3, -0.4, ASPECT)
    assert point is not None
    assert point[2] == pytest.approx(0.0)
    # It is where the cursor points, not merely somewhere on the plane.
    np.testing.assert_allclose(project_to_ndc(pose, point, ASPECT), (0.3, -0.4), atol=1e-9)


def test_ground_point_honours_a_raised_plane() -> None:
    pose = _pose(position=(-6.0, -4.0, 3.0), focal=(0.0, 0.0, 0.0))
    point = ground_plane_point(pose, 0.0, -0.2, ASPECT, height=0.25)
    assert point is not None and point[2] == pytest.approx(0.25)


def test_ground_point_gives_up_on_the_sky() -> None:
    """Pointing away from the plane, and exactly along it, have no answer."""
    up = _pose(position=(-6.0, -4.0, 3.0), focal=(-4.0, -2.0, 9.0))
    assert ground_plane_point(up, 0.0, 0.0, ASPECT) is None
    level = _pose(position=(-6.0, 0.0, 1.0), focal=(0.0, 0.0, 1.0))
    assert ground_plane_point(level, 0.0, 0.0, ASPECT) is None


def test_ground_point_gives_up_near_the_horizon() -> None:
    """A grazing hit is far away. Recentring there would leave the car a speck."""
    # Nearly level, so the top of the frame looks past the horizon.
    pose = _pose(position=(-6.0, -4.0, 1.2), focal=(4.0, 3.0, 1.2))
    distance = float(np.linalg.norm(pose.focal - pose.position))
    hits = [ground_plane_point(pose, 0.0, float(y), ASPECT)
            for y in np.linspace(-0.9, 0.9, 200)]
    assert hits[0] is not None, "the bottom of the frame is floor, and must recentre"
    assert hits[-1] is None, "the top of the frame is horizon, and must not"
    for hit in hits:
        if hit is not None:
            assert hit[2] == pytest.approx(0.0)
            assert np.linalg.norm(hit - pose.position) <= GROUND_REACH * distance + 1e-6


def test_wheel_zoom_is_proportional_to_scroll_distance() -> None:
    assert wheel_zoom_factor(0, WHEEL_NOTCH) == pytest.approx(ZOOM_PER_NOTCH)
    assert wheel_zoom_factor(0, -WHEEL_NOTCH) == pytest.approx(1.0 / ZOOM_PER_NOTCH)
    ten_small = np.prod([wheel_zoom_factor(0, WHEEL_NOTCH // 10) for _ in range(10)])
    assert ten_small == pytest.approx(ZOOM_PER_NOTCH)


def test_wheel_zoom_reads_pixel_deltas_when_that_is_all_there_is() -> None:
    """macOS trackpads report pixels and no angle. They must still zoom."""
    assert wheel_zoom_factor(0, 0, pixel_dy=40) > 1.0
    assert wheel_zoom_factor(0, 0, pixel_dy=-40) < 1.0
    assert wheel_zoom_factor(0, 0) == pytest.approx(1.0)


def test_sideways_scroll_zooms_like_a_vertical_one() -> None:
    """A tilt wheel or a horizontal swipe is still a request to zoom."""
    assert wheel_zoom_factor(WHEEL_NOTCH, 0) == pytest.approx(ZOOM_PER_NOTCH)
