"""Camera navigation for BobVis. Pure numpy, so CI can test it.

``_5_App/static/visual.js`` ports this module. ``tests/test_visual_camera_parity.py``
keeps the two in agreement. This module is the reference because it has the tests.

Conventions
    Screen deltas are pixels: x right, y down. NDC run -1..1 with y up.
    Drags move the scene with the cursor. Orbit is turntable style about world +Z.
"""

from __future__ import annotations

from dataclasses import dataclass, replace

import numpy as np

WORLD_UP = np.array([0.0, 0.0, 1.0])

WHEEL_NOTCH = 120
"""Units in one detent of a standard mouse wheel, as Qt counted them."""

ZOOM_PER_NOTCH = 1.15
WHEEL_PX_PER_NOTCH = 40.0
"""Pixels of trackpad scroll that count as one wheel notch of zoom."""

ORBIT_DEG_PER_PX = 0.3
MIN_POLAR_DEG = 1.0
"""Closest the orbit gets to straight up or down, so the view never flips."""

MIN_DISTANCE = 0.05
"""Nearest the camera may zoom to what it is looking at, in metres."""

GROUND_REACH = 20.0
"""Farthest a ground recentre may land, in multiples of the orbit distance."""


@dataclass(frozen=True)
class CameraPose:
    """Camera state in world coordinates."""

    position: np.ndarray
    focal: np.ndarray
    up: np.ndarray
    view_angle: float = 30.0
    """Vertical field of view, degrees (VTK's default convention)."""
    parallel_projection: bool = False
    parallel_scale: float = 1.0
    """Half the viewport height in world units, when parallel."""


def _unit(v: np.ndarray, fallback: np.ndarray) -> np.ndarray:
    n = float(np.linalg.norm(v))
    return v / n if n > 1e-12 else np.asarray(fallback, dtype=float)


def camera_basis(pose: CameraPose) -> tuple[np.ndarray, np.ndarray, np.ndarray]:
    """Orthonormal (forward, right, up) for ``pose``."""
    forward = _unit(pose.focal - pose.position, np.array([0.0, 1.0, 0.0]))
    right = _unit(np.cross(forward, pose.up), np.array([1.0, 0.0, 0.0]))
    up = np.cross(right, forward)
    return forward, right, up


def _half_height(pose: CameraPose) -> float:
    """Half the visible height of the focal plane, in world units."""
    if pose.parallel_projection:
        return float(pose.parallel_scale)
    distance = float(np.linalg.norm(pose.focal - pose.position))
    return distance * float(np.tan(np.radians(pose.view_angle) / 2.0))


def orbit(pose: CameraPose, d_azimuth: float, d_elevation: float) -> CameraPose:
    """Turntable orbit about the focal point, in degrees.

    Positive ``d_azimuth`` is counter-clockwise about world +Z seen from above.
    Positive ``d_elevation`` raises the camera.
    """
    offset = pose.position - pose.focal
    radius = float(np.linalg.norm(offset))
    if radius < 1e-9:
        return pose

    horizontal = offset[:2]
    if float(np.linalg.norm(horizontal)) < 1e-6 * radius:
        # Azimuth is undefined looking straight down or up. Take it from screen
        # up so the picture does not spin when the tilt starts.
        horizontal = -np.asarray(pose.up[:2], dtype=float)
        if float(np.linalg.norm(horizontal)) < 1e-9:
            horizontal = np.array([-1.0, 0.0])

    azimuth = float(np.arctan2(horizontal[1], horizontal[0])) + np.radians(d_azimuth)
    polar = float(np.arccos(np.clip(offset[2] / radius, -1.0, 1.0))) - np.radians(d_elevation)
    polar = float(np.clip(polar, np.radians(MIN_POLAR_DEG), np.radians(180.0 - MIN_POLAR_DEG)))

    position = pose.focal + radius * np.array([
        np.sin(polar) * np.cos(azimuth),
        np.sin(polar) * np.sin(azimuth),
        np.cos(polar),
    ])
    forward = _unit(pose.focal - position, np.array([0.0, 1.0, 0.0]))
    right = _unit(np.cross(forward, WORLD_UP), np.array([1.0, 0.0, 0.0]))
    return replace(pose, position=position, up=np.cross(right, forward))


def pan(pose: CameraPose, dx_px: float, dy_px: float, viewport_height_px: float) -> CameraPose:
    """Slide the camera in its view plane so the scene tracks the cursor at the focal plane."""
    _, right, up = camera_basis(pose)
    per_px = 2.0 * _half_height(pose) / max(float(viewport_height_px), 1.0)
    shift = (-float(dx_px) * right + float(dy_px) * up) * per_px
    return replace(pose, position=pose.position + shift, focal=pose.focal + shift)


def focal_plane_point(pose: CameraPose, ndc_x: float, ndc_y: float, aspect: float) -> np.ndarray:
    """World point on the focal plane under a screen position."""
    _, right, up = camera_basis(pose)
    half_h = _half_height(pose)
    return pose.focal + float(ndc_x) * half_h * float(aspect) * right + float(ndc_y) * half_h * up


def project_to_ndc(pose: CameraPose, point: np.ndarray, aspect: float) -> tuple[float, float]:
    """Screen position of a world point: the inverse of :func:`focal_plane_point`."""
    forward, right, up = camera_basis(pose)
    rel = np.asarray(point, dtype=float) - pose.position
    if pose.parallel_projection:
        half_h = float(pose.parallel_scale)
        rel = np.asarray(point, dtype=float) - pose.focal
    else:
        depth = float(rel @ forward)
        half_h = depth * float(np.tan(np.radians(pose.view_angle) / 2.0))
    return float(rel @ right) / (half_h * float(aspect)), float(rel @ up) / half_h


def cursor_ray(
    pose: CameraPose, ndc_x: float, ndc_y: float, aspect: float
) -> tuple[np.ndarray, np.ndarray]:
    """World ray under a screen position, as ``(origin, unit direction)``."""
    through = focal_plane_point(pose, ndc_x, ndc_y, aspect)
    if pose.parallel_projection:
        forward, _, _ = camera_basis(pose)
        return through, forward
    return pose.position, _unit(through - pose.position, np.array([0.0, 1.0, 0.0]))


def ground_plane_point(
    pose: CameraPose, ndc_x: float, ndc_y: float, aspect: float, height: float = 0.0
) -> np.ndarray | None:
    """Where the cursor ray meets the ground plane ``z = height``.

    ``None`` when the ray misses the plane or hits beyond :data:`GROUND_REACH`.
    """
    origin, direction = cursor_ray(pose, ndc_x, ndc_y, aspect)
    if abs(float(direction[2])) < 1e-9:
        return None
    along = (float(height) - float(origin[2])) / float(direction[2])
    # A parallel ray starts on the focal plane, so the ground may be behind it.
    if along <= 0.0 and not pose.parallel_projection:
        return None
    point = origin + along * direction
    distance = float(np.linalg.norm(pose.focal - pose.position))
    if float(np.linalg.norm(point - pose.position)) > GROUND_REACH * max(distance, MIN_DISTANCE):
        return None
    return point


def zoom_at(
    pose: CameraPose, factor: float, ndc_x: float, ndc_y: float, aspect: float
) -> CameraPose:
    """Zoom by ``factor`` (>1 closer) toward the point under the cursor.

    That point stays fixed on screen.
    """
    factor = float(factor)
    if factor <= 0.0 or abs(factor - 1.0) < 1e-12:
        return pose
    target = focal_plane_point(pose, ndc_x, ndc_y, aspect)

    if pose.parallel_projection:
        shift = (target - pose.focal) * (1.0 - 1.0 / factor)
        return replace(
            pose,
            position=pose.position + shift,
            focal=pose.focal + shift,
            parallel_scale=float(pose.parallel_scale) / factor,
        )

    distance = float(np.linalg.norm(pose.focal - pose.position))
    if distance < 1e-9:
        return pose
    new_distance = max(distance / factor, min(MIN_DISTANCE, distance))
    keep = new_distance / distance
    position = pose.position + (1.0 - keep) * (target - pose.position)
    return replace(pose, position=position, focal=position + keep * (pose.focal - pose.position))


def recenter(pose: CameraPose, point: np.ndarray) -> CameraPose:
    """Move the orbit centre to ``point`` without changing the viewing direction."""
    shift = np.asarray(point, dtype=float) - pose.focal
    return replace(pose, position=pose.position + shift, focal=pose.focal + shift)


def wheel_zoom_factor(angle_dx: int, angle_dy: int, pixel_dx: int = 0, pixel_dy: int = 0) -> float:
    """Zoom factor for a wheel event, proportional to how far it scrolled.

    Mouse wheels and trackpads zoom the same distance per notch.
    """
    if angle_dy:
        notches = angle_dy / WHEEL_NOTCH
    elif angle_dx:
        notches = angle_dx / WHEEL_NOTCH
    else:
        notches = (pixel_dy or pixel_dx) / WHEEL_PX_PER_NOTCH
    return float(ZOOM_PER_NOTCH ** notches)
