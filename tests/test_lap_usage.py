"""Operating frequency must measure dwell time, preserve signs and expose limits."""
import numpy as np
import pytest

from simulations.lap.core.qss import GGVMap
from simulations.lap.core.usage import occupancy, operating_points


def test_occupancy_weights_time_not_sample_count():
    ggv = GGVMap.from_arrays([10, 20], [-8, 0, 8], [[0, 4, 0]] * 2, [[0, -8, 0]] * 2)
    frame = operating_points(ggv, [10, 10, 20], [0, 0, 0], [-4, -4, 4], [1, 1, 8], [0, 1, 2])
    bins = occupancy(frame, bins=2)
    assert sorted(bins.time_percent) == pytest.approx([20, 80])
    assert bins.duration_s.sum() == 10
    assert bins.sample_count.sum() == 3
    assert frame.drive_limit_mps2.to_list() == [2, 2, 2]
    assert frame.brake_limit_mps2.to_list() == [-4, -4, -4]


def test_invalid_or_exceeded_limits_remain_in_occupancy():
    ggv = GGVMap.from_arrays([10], [-4, 0, 8], [[0, 4, 0]], [[0, -8, 0]])
    frame = operating_points(ggv, [5, 10, 10], [0, 6, 0], [0, 0, -5], [1, 2, 3], [0, 1, 2])
    assert not frame.speed_in_map.iloc[0]
    assert frame.drive_margin_mps2.iloc[1] == -2
    assert not frame.limits_available.iloc[2]
    assert frame.lateral_margin_mps2.iloc[2] == -1
    assert occupancy(frame).duration_s.sum() == 6
    with pytest.raises(ValueError):
        operating_points(ggv, [10], [0], [0], [-1], [0])


def test_empty_time_does_not_invent_frequency():
    ggv = GGVMap.from_arrays([10], [0, 4], [[4, 0]], [[-8, 0]])
    frame = operating_points(ggv, [10], [0], [0], [0], [0])
    assert np.isfinite(frame.time_percent).all()
    assert occupancy(frame).time_percent.sum() == 0


def test_path_frame_transport_with_roll_pitch_and_sideslip():
    from types import SimpleNamespace
    from engines.dynpy.models import _body_to_world_rotation
    from engines.dynpy.transient import _path_response
    model = SimpleNamespace(dof=6, _body_state=lambda q, v: (q, v))
    pose = np.array([0, 0, 0, .2, -.1, .7])
    velocity = np.array([12., 2., .3, .4, -.2, .6])
    derivative = np.array([.1, .3, -.2, 0, 0, 0])
    speed, ax, ay = _path_response(model, np.r_[pose, velocity], derivative)
    rotation = _body_to_world_rotation(pose[3:])
    # Independent finite difference of rotated body velocity under angular velocity.
    from scipy.spatial.transform import Rotation
    dt = 1e-6
    initial = rotation @ velocity[:3]
    following = rotation @ Rotation.from_rotvec(velocity[3:] * dt).as_matrix() @ (velocity[:3] + derivative[:3] * dt)
    acc = (following - initial) / dt
    tangent = initial[:2] / np.linalg.norm(initial[:2])
    assert speed == pytest.approx(np.linalg.norm(initial[:2]))
    assert ax == pytest.approx(acc[:2] @ tangent, abs=1e-5)
    assert ay == pytest.approx(acc[:2] @ [-tangent[1], tangent[0]], abs=1e-5)


def test_interval_weights_clip_first_finish_and_preserve_partial_run():
    from simulations.lap.core.usage import interval_durations
    times = [0, .1, .3, .6, 1.]
    progress = [0, 4, 8, 12, 9]  # Later progress must not affect the first finish.
    assert interval_durations(times, progress, 10, True) == pytest.approx([.1, .2, .15, 0])
    assert interval_durations(times, progress, 10, False) == pytest.approx([.1, .2, .3, .4])
