"""BobVis viewport controls, driven the way a hand drives them.

Every other check on navigation is arithmetic: ``test_visual_navigation.py``
proves the camera maths and proves nothing about whether a drag ever reaches
it. These send real Qt mouse, wheel and key events into a real
:class:`~_1_VisualSim.viewer.ViewerWindow` and assert the camera does what the
F1 dialog promises. It is the wiring, not the maths, that quietly breaks.

Qt's offscreen platform has no GL context, so the render window comes back 0x0
and VTK's picker sees nothing: a double-click here always falls through to the
ground plane, which is the path that used to do nothing at all. Like
``test_visual_scene.py``, this whole module skips where BobVis's Qt stack is
absent (CI and the Docker image); install it with ``make visual-deps``.
"""

from __future__ import annotations

import os

import numpy as np
import pytest

pytest.importorskip("PyQt6.QtWidgets", reason="BobVis's Qt stack is installed via `make visual-deps`")
pytest.importorskip("pyvistaqt", reason="BobVis's Qt stack is installed via `make visual-deps`")

os.environ.setdefault("QT_QPA_PLATFORM", "offscreen")

from PyQt6.QtCore import QEvent, QPoint, QPointF, Qt  # noqa: E402
from PyQt6.QtGui import QMouseEvent, QWheelEvent  # noqa: E402
from PyQt6.QtTest import QTest  # noqa: E402
from PyQt6.QtWidgets import QApplication  # noqa: E402

from _1_VisualSim import demo  # noqa: E402
from _1_VisualSim.navigation import (  # noqa: E402
    WHEEL_NOTCH,
    CameraPose,
    focal_plane_point,
    project_to_ndc,
)
from _1_VisualSim.scene import FOLLOW, SimData  # noqa: E402
from _1_VisualSim.viewer import ViewerWindow  # noqa: E402

NO_BUTTON = Qt.MouseButton.NoButton
NO_MODIFIER = Qt.KeyboardModifier.NoModifier
LEFT = Qt.MouseButton.LeftButton


@pytest.fixture(scope="module")
def qapp() -> QApplication:
    app = QApplication.instance()
    return app if isinstance(app, QApplication) else QApplication([])


@pytest.fixture(scope="module")
def window(qapp: QApplication, tmp_path_factory: pytest.TempPathFactory) -> ViewerWindow:
    config, data = demo.write(tmp_path_factory.mktemp("scene"), duration=0.5)
    win = ViewerWindow(SimData(config, data))
    win.resize(1000, 700)
    win.show()
    # The scene is built from a singleShot(0), once the interactor is live.
    qapp.processEvents()
    qapp.processEvents()
    assert win._scene is not None, "the scene must build before controls can be driven"
    return win


class Viewport:
    """A hand on the viewport: drags, scrolls, and reads the camera back."""

    def __init__(self, window: ViewerWindow, app: QApplication) -> None:
        self.window = window
        self.app = app
        self.widget = window._plotter
        self.scene = window._scene

    # -- input --------------------------------------------------------------
    def _send(self, event: QEvent) -> None:
        QApplication.sendEvent(self.widget, event)
        self.app.processEvents()

    def _mouse(self, kind: QEvent.Type, x: float, y: float, button: Qt.MouseButton,
               buttons: Qt.MouseButton, modifiers: Qt.KeyboardModifier) -> QMouseEvent:
        at = QPointF(x, y)
        return QMouseEvent(kind, at, at, button, buttons, modifiers)

    def drag(self, start: tuple[float, float], end: tuple[float, float], *,
             button: Qt.MouseButton = LEFT,
             modifiers: Qt.KeyboardModifier = NO_MODIFIER) -> None:
        self._send(self._mouse(QEvent.Type.MouseButtonPress, *start, button, button, modifiers))
        self._send(self._mouse(QEvent.Type.MouseMove, *end, NO_BUTTON, button, modifiers))
        self._send(self._mouse(QEvent.Type.MouseButtonRelease, *end, button, NO_BUTTON, modifiers))

    def double_click(self, at: tuple[float, float]) -> None:
        self._send(self._mouse(QEvent.Type.MouseButtonDblClick, *at, LEFT, LEFT, NO_MODIFIER))

    def scroll(self, at: tuple[float, float], *, angle: int = WHEEL_NOTCH, pixels: int = 0,
               modifiers: Qt.KeyboardModifier = NO_MODIFIER) -> None:
        pos = QPointF(*at)
        self._send(QWheelEvent(
            pos, pos, QPoint(0, pixels), QPoint(0, angle), NO_BUTTON, modifiers,
            Qt.ScrollPhase.NoScrollPhase, False,
        ))

    def key(self, key: Qt.Key) -> None:
        # Through QTest, not sendEvent: a menu shortcut is matched by the
        # shortcut map, which only sees keys delivered as the system's own.
        # PyQt6's stubs declare these static helpers as instance methods.
        QTest.keyClick(self.window, key)  # type: ignore[call-overload]
        self.app.processEvents()

    def reset(self) -> None:
        self.window._set_view("iso")
        self.app.processEvents()

    # -- readings -----------------------------------------------------------
    @property
    def centre(self) -> tuple[float, float]:
        return self.widget.width() / 2.0, self.widget.height() / 2.0

    def pose(self) -> CameraPose:
        return self.scene.camera_pose()

    def distance(self) -> float:
        pose = self.pose()
        return float(np.linalg.norm(pose.position - pose.focal))

    def ndc(self, at: tuple[float, float]) -> tuple[float, float, float]:
        width, height = self.widget.width(), self.widget.height()
        return 2.0 * at[0] / width - 1.0, 1.0 - 2.0 * at[1] / height, width / height


@pytest.fixture
def view(window: ViewerWindow, qapp: QApplication) -> Viewport:
    window._clock.pause()
    viewport = Viewport(window, qapp)
    viewport.reset()
    return viewport


# -- the viewport takes the input at all ------------------------------------

def test_the_navigator_is_installed_on_the_viewport(window: ViewerWindow) -> None:
    """The one thing no amount of camera-maths testing can show."""
    assert window._navigator is not None
    assert window._navigator._viewport is window._plotter


# -- orbit and pan ----------------------------------------------------------

def test_left_drag_orbits_without_changing_the_distance(view: Viewport) -> None:
    before, distance = view.pose(), view.distance()
    x, y = view.centre
    view.drag((x, y), (x + 80.0, y))
    after = view.pose()
    assert not np.allclose(after.position, before.position)
    np.testing.assert_allclose(after.focal, before.focal, atol=1e-9)
    assert view.distance() == pytest.approx(distance, rel=1e-9)


def test_orbit_never_rolls_the_horizon(view: Viewport) -> None:
    x, y = view.centre
    view.drag((x, y), (x + 120.0, y - 60.0))
    pose = view.pose()
    level = np.cross(pose.focal - pose.position, [0.0, 0.0, 1.0])
    assert abs(float(level @ pose.up)) < 1e-9


@pytest.mark.parametrize(
    ("button", "modifiers"),
    [
        (LEFT, Qt.KeyboardModifier.ShiftModifier),
        (Qt.MouseButton.RightButton, NO_MODIFIER),
        (Qt.MouseButton.MiddleButton, NO_MODIFIER),
    ],
    ids=["shift+left", "right", "middle"],
)
def test_pan_slides_the_view_without_turning_it(
    view: Viewport, button: Qt.MouseButton, modifiers: Qt.KeyboardModifier
) -> None:
    before, distance = view.pose(), view.distance()
    x, y = view.centre
    view.drag((x, y), (x + 60.0, y + 40.0), button=button, modifiers=modifiers)
    after = view.pose()
    assert not np.allclose(after.focal, before.focal)
    # Pan moves camera and focal together, so the direction of view is untouched.
    np.testing.assert_allclose(after.position - after.focal,
                               before.position - before.focal, atol=1e-9)
    assert view.distance() == pytest.approx(distance, rel=1e-9)


# -- zoom -------------------------------------------------------------------

def test_scroll_zooms_toward_the_cursor(view: Viewport) -> None:
    at = (view.centre[0] + 150.0, view.centre[1] - 90.0)
    ndc_x, ndc_y, aspect = view.ndc(at)
    target = focal_plane_point(view.pose(), ndc_x, ndc_y, aspect)
    before = view.distance()

    view.scroll(at)

    assert view.distance() < before
    # Whatever was under the cursor is still under the cursor.
    np.testing.assert_allclose(project_to_ndc(view.pose(), target, aspect),
                               (ndc_x, ndc_y), atol=1e-3)


@pytest.mark.parametrize(
    ("kwargs", "what"),
    [
        ({"angle": WHEEL_NOTCH}, "a mouse notch"),
        ({"angle": WHEEL_NOTCH // 10}, "a trackpad's fraction of a notch"),
        ({"angle": 0, "pixels": 40}, "a macOS trackpad's pixel delta"),
        ({"angle": WHEEL_NOTCH // 10, "modifiers": Qt.KeyboardModifier.ControlModifier},
         "a pinch, which Windows sends as Ctrl+scroll"),
        ({"angle": WHEEL_NOTCH // 10, "modifiers": Qt.KeyboardModifier.ShiftModifier},
         "Shift held down"),
    ],
    ids=["wheel", "trackpad-notch", "trackpad-pixels", "pinch", "shift"],
)
def test_every_kind_of_scroll_zooms(view: Viewport, kwargs: dict, what: str) -> None:
    """Scroll means zoom on every device.

    Guessing which device sent it is what used to make a trackpad orbit when
    the user asked to zoom.
    """
    before = view.distance()
    view.scroll(view.centre, **kwargs)
    assert view.distance() < before, f"{what} must zoom in"


def test_keyboard_zoom_moves_the_camera_like_the_wheel_does(view: Viewport) -> None:
    """``+`` used to narrow the field of view instead, which flattened the
    perspective and left keyboard and wheel zoom as two different things."""
    before = view.pose()
    view.key(Qt.Key.Key_Plus)
    after = view.pose()
    assert view.distance() < float(np.linalg.norm(before.position - before.focal))
    assert after.view_angle == pytest.approx(before.view_angle)


def test_zoom_out_then_in_returns_to_where_it_started(view: Viewport) -> None:
    before = view.pose()
    view.scroll(view.centre, angle=-WHEEL_NOTCH)
    view.scroll(view.centre, angle=WHEEL_NOTCH)
    np.testing.assert_allclose(view.pose().position, before.position, atol=1e-6)


# -- recentring -------------------------------------------------------------

def test_double_click_on_the_floor_recentres_there(view: Viewport) -> None:
    """The ground plane is drawn unpickable, so this used to do nothing at all."""
    before = view.pose()
    at = (view.centre[0], view.centre[1] + 140.0)

    view.double_click(at)

    after = view.pose()
    assert not np.allclose(after.focal, before.focal), "the orbit centre must move"
    assert after.focal[2] == pytest.approx(view.scene.GROUND_HEIGHT, abs=1e-6)
    # Recentring slides the camera along with it; the view direction holds.
    np.testing.assert_allclose(after.position - after.focal,
                               before.position - before.focal, atol=1e-9)


def test_double_click_recentres_under_the_cursor_not_the_middle(view: Viewport) -> None:
    below = view.centre[1] + 140.0
    view.double_click((view.centre[0] - 200.0, below))
    from_left = view.pose().focal.copy()

    view.reset()
    view.double_click((view.centre[0] + 200.0, below))

    assert not np.allclose(from_left, view.pose().focal)


# -- playback ---------------------------------------------------------------

def test_an_orbit_survives_the_next_playback_frame(view: Viewport) -> None:
    """Follow mode used to overwrite the camera on the very next tick, which
    was the single biggest reason the viewer felt broken."""
    view.scene.set_camera_mode(FOLLOW)
    x, y = view.centre
    view.drag((x, y), (x + 80.0, y - 30.0))
    held = view.pose()

    view.window._on_tick(view.window._clock.sim_time + 0.2)
    view.app.processEvents()

    after = view.pose()
    np.testing.assert_allclose(after.position - after.focal,
                               held.position - held.focal, atol=1e-6)
