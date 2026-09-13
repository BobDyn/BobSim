"""Camera navigation for BobVis: how mouse and touchpad input moves the view.

Pure numpy - no Qt, no VTK - so the arithmetic that decides whether a gesture
feels right is testable everywhere, including CI where the rendering stack is
absent. :class:`_1_VisualSim.viewer.ViewportNavigator` reads the input events
and :class:`_1_VisualSim.scene.VisualScene` applies the resulting pose.

Conventions
    Screen deltas are Qt widget pixels: x right, y down. Normalised device
    coordinates (NDC) run -1..1 with y up. Drags follow "grab" semantics, as
    VTK's trackball does: the scene moves with the cursor, the camera the other
    way. Orbit is turntable style about world +Z, so the horizon never rolls.
"""

from __future__ import annotations

from dataclasses import dataclass, replace
from typing import Literal

import numpy as np

WORLD_UP = np.array([0.0, 0.0, 1.0])

WHEEL_NOTCH = 120
"""Qt ``angleDelta`` units in one detent of a standard mouse wheel."""

ZOOM_PER_NOTCH = 1.15
WHEEL_PX_PER_NOTCH = 40.0
"""Drag distance, in pixels, that one wheel notch of touchpad scroll stands for."""

ORBIT_DEG_PER_PX = 0.3
MIN_POLAR_DEG = 1.0
"""Closest the orbit gets to straight up or down, so the view never flips."""

MIN_DISTANCE = 0.05
"""Nearest the camera may zoom to what it is looking at, in metres."""

WheelAction = Literal["zoom", "orbit", "pan", "none"]


@dataclass(frozen=True)
class CameraPose:
    """The camera state navigation reads and writes, in world coordinates."""

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
    """Turntable orbit about the focal point.

    ``d_azimuth`` swings the camera counter-clockwise about world +Z seen from
    above; ``d_elevation`` raises it. Degrees. Distance and focal point are
    kept, elevation stops just short of the poles, and roll is levelled out.
    """
    offset = pose.position - pose.focal
    radius = float(np.linalg.norm(offset))
    if radius < 1e-9:
        return pose

    horizontal = offset[:2]
    if float(np.linalg.norm(horizontal)) < 1e-6 * radius:
        # Looking straight down or up: azimuth is undefined, so take it from
        # the screen's up direction. The camera sits "below" the top edge,
        # which keeps the picture from spinning when the tilt starts.
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
    """Slide the camera in its view plane so the scene tracks the cursor.

    Scaled at the focal plane: dragging the full viewport height moves the view
    by exactly the height of what is visible there.
    """
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


def zoom_at(
    pose: CameraPose, factor: float, ndc_x: float, ndc_y: float, aspect: float
) -> CameraPose:
    """Zoom by ``factor`` (>1 closer) toward the point under the cursor.

    That point stays put on screen, the way maps and CAD tools zoom, and the
    orbit centre follows it in. Never closer than :data:`MIN_DISTANCE`.
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


# ---------------------------------------------------------------------------
# Wheel input
#
# A mouse wheel and a two-finger touchpad scroll arrive as the same Qt event.
# Only some platforms say which is which (a device type, a scroll phase, a
# pixel delta); Windows precision touchpads say none of it, but they report in
# fractions of a notch where a detented wheel reports whole ones. That is the
# heuristic, and ``detect_touchpad`` turns it off for free-spinning mice that
# also report fractions.
# ---------------------------------------------------------------------------

def classify_wheel(
    angle_dx: int,
    angle_dy: int,
    *,
    pixel_dx: int = 0,
    pixel_dy: int = 0,
    scroll_phase: bool = False,
    touchpad_device: bool = False,
    recent_touchpad: bool = False,
    ctrl: bool = False,
    shift: bool = False,
    detect_touchpad: bool = True,
) -> WheelAction:
    """Decide what one wheel event should do to the camera.

    Mouse wheel zooms. Touchpad two-finger scroll orbits, or pans with Shift.
    Ctrl always zooms: Windows and Linux deliver a touchpad pinch as Ctrl +
    scroll. ``recent_touchpad`` carries a gesture across the odd event that
    happens to land on a whole notch.
    """
    if angle_dx == 0 and angle_dy == 0 and pixel_dx == 0 and pixel_dy == 0:
        return "none"
    if ctrl or not detect_touchpad:
        return "zoom"
    touchpad = (
        touchpad_device
        or scroll_phase
        or recent_touchpad
        or pixel_dx != 0
        or pixel_dy != 0
        or angle_dx != 0
        or angle_dy % WHEEL_NOTCH != 0
    )
    if not touchpad:
        return "zoom"
    return "pan" if shift else "orbit"


def wheel_zoom_factor(angle_dx: int, angle_dy: int, pixel_dx: int = 0, pixel_dy: int = 0) -> float:
    """Zoom factor for a wheel event, proportional to how far it scrolled.

    Ten tenth-of-a-notch touchpad events zoom exactly as far as one notch.
    """
    if angle_dy:
        notches = angle_dy / WHEEL_NOTCH
    elif angle_dx:
        notches = angle_dx / WHEEL_NOTCH
    else:
        notches = (pixel_dy or pixel_dx) / WHEEL_PX_PER_NOTCH
    return float(ZOOM_PER_NOTCH ** notches)


def wheel_drag_pixels(
    angle_dx: int, angle_dy: int, pixel_dx: int = 0, pixel_dy: int = 0
) -> tuple[float, float]:
    """A touchpad scroll as the equivalent cursor drag (x right, y down).

    Qt's sign convention makes a positive delta move content right and down,
    after the OS applies the user's scroll-direction setting, so the deltas
    pass straight through.
    """
    if pixel_dx or pixel_dy:
        return float(pixel_dx), float(pixel_dy)
    scale = WHEEL_PX_PER_NOTCH / WHEEL_NOTCH
    return angle_dx * scale, angle_dy * scale
