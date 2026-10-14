"""Independent physical checks for the path-frame GGV operating points."""

from dataclasses import replace

import numpy as np
import pytest
from scipy.spatial.transform import Rotation

from engines.dynpy import Vehicle, solve_steady_state
from simulations.envelope.ggv.ggv_generation import _solve_envelope_limit, _solve_racing_trim, solve_ax_limit
from simulations.envelope.vehicle_yaml import load_vehicle_yaml, project_vehicle_yaml


@pytest.fixture(scope="module")
def vehicle():
    return Vehicle.from_yaml()


def _path_motion(model, state, output):
    velocity = state[model.dof:]
    if model.dof == 3:
        rotation = np.eye(3)
        linear = np.r_[velocity[:2], 0.]
        omega = np.array([0., 0., velocity[2]])
        acceleration = np.r_[output.generalized_acceleration[:2], 0.]
        yaw_rate = output.derivative[2]
    else:
        rotation = Rotation.from_euler("xyz", state[3:6]).as_matrix()
        linear, omega = velocity[:3], velocity[3:6]
        acceleration = output.generalized_acceleration[:3]
        yaw_rate = output.derivative[5]
    world_velocity = rotation @ linear
    world_acceleration = rotation @ (acceleration + np.cross(omega, linear))
    speed = np.linalg.norm(world_velocity[:2])
    tangent = world_velocity[:2] / speed
    normal = np.array([-tangent[1], tangent[0]])
    path_acceleration = np.array([world_acceleration[:2] @ tangent, world_acceleration[:2] @ normal])
    beta_rate = path_acceleration[1] / speed - yaw_rate
    return path_acceleration, beta_rate, yaw_rate, world_acceleration


@pytest.mark.parametrize("dof", (3, 6, 10, 14))
def test_ggv_pure_corner_matches_independent_constant_radius_trim(vehicle, dof):
    model = vehicle.model(dof)
    speed, normal_acceleration = 7.5, 6.
    steady = solve_steady_state(model, speed_mps=speed, yaw_rate_radps=normal_acceleration / speed)
    racing = _solve_racing_trim(
        model, speed_mps=speed, longitudinal_acceleration_mps2=0.,
        lateral_acceleration_mps2=normal_acceleration, initial_unknowns=None,
        max_abs_beta_rad=.25, max_abs_steering_rad=.5,
        enforce_tire_load_range=True, trim_multistart=False,
    )
    assert steady.success, steady.message
    assert racing is not None
    assert abs(racing.unknowns["beta_rad"]) > .02
    np.testing.assert_allclose(racing.state, steady.state, atol=2e-5)
    np.testing.assert_allclose(racing.output.generalized_acceleration, 0., atol=1e-5)
    acceleration, beta_rate, yaw_rate, _ = _path_motion(model, racing.state, racing.output)
    np.testing.assert_allclose(acceleration, [0., normal_acceleration], atol=1e-5)
    assert beta_rate == pytest.approx(0., abs=1e-6)
    assert yaw_rate == pytest.approx(normal_acceleration / speed, abs=1e-8)
    rotated_state = racing.state.copy()
    rotated_state[2 if dof == 3 else 5] += .73
    rotated = replace(racing, state=rotated_state, output=model.evaluate(rotated_state, racing.inputs))
    assert rotated.path_longitudinal_acceleration_mps2 == pytest.approx(0., abs=1e-5)
    assert rotated.path_lateral_acceleration_mps2 == pytest.approx(normal_acceleration, abs=1e-5)


@pytest.mark.parametrize("dof", (3, 6, 10, 14))
@pytest.mark.parametrize("mode", ("drive", "brake"))
def test_ggv_combined_boundary_closes_actual_transient_path_motion(vehicle, dof, mode):
    model = vehicle.model(dof)
    speed, normal_acceleration = 10., 6.
    result = _solve_envelope_limit(
        project_vehicle_yaml(load_vehicle_yaml()).ggv, model,
        speed=speed, ay=normal_acceleration, ax_bounds=(-31.4, 27.5), mode=mode,
        max_abs_beta_rad=.25, max_abs_steering_rad=.5, enforce_tire_load_range=True,
    )
    if result is None:
        acceleration = solve_ax_limit(
            project_vehicle_yaml(load_vehicle_yaml()).ggv, speed=speed, ay=normal_acceleration,
            ax_grid=np.array([-31.4, 27.5]), mode=mode, reduced_model=model,
            max_abs_beta_rad=.25, max_abs_steering_rad=.5, enforce_tire_load_range=True,
            trim_multistart=False,
        )
        assert np.isfinite(acceleration)
        result = _solve_racing_trim(
            model, speed_mps=speed, longitudinal_acceleration_mps2=acceleration,
            lateral_acceleration_mps2=normal_acceleration, initial_unknowns=None,
            max_abs_beta_rad=.25, max_abs_steering_rad=.5,
            enforce_tire_load_range=True, trim_multistart=False,
        )
    assert result is not None and result.success
    # This evaluates the ordinary transient force path, without trial tire loads or slips.
    forward = model.evaluate(result.state, result.inputs)
    acceleration, beta_rate, yaw_rate, world_acceleration = _path_motion(model, result.state, forward)
    np.testing.assert_allclose(
        acceleration, [result.path_longitudinal_acceleration_mps2, normal_acceleration], atol=2e-4,
    )
    assert result.path_lateral_acceleration_mps2 == pytest.approx(normal_acceleration, abs=1e-5)
    assert yaw_rate == pytest.approx(normal_acceleration / speed, abs=1e-8)
    assert beta_rate == pytest.approx(0., abs=2e-5)
    assert world_acceleration[2] == pytest.approx(0., abs=2e-4)
    assert np.sign(acceleration[0]) == (1 if mode == "drive" else -1)
    if dof >= 6:
        np.testing.assert_allclose(forward.derivative[2:5], 0., atol=1e-10)
        np.testing.assert_allclose(forward.generalized_acceleration[3:6], 0., atol=2e-4)
    if dof >= 10:
        wheel_slice = slice(6, 10) if dof == 10 else slice(10, 14)
        body_acceleration = forward.generalized_acceleration[:2]
        rolling_acceleration = (body_acceleration[0] * np.cos(forward.toe_rad)
                                + body_acceleration[1] * np.sin(forward.toe_rad))
        velocity = result.state[dof:]
        corner_velocity = velocity[:3] + np.cross(velocity[3:6], forward.contact_patch_positions_body_m)
        longitudinal_speed = (corner_velocity[:, 0] * np.cos(forward.toe_rad)
                              + corner_velocity[:, 1] * np.sin(forward.toe_rad))
        delta = 1e-4
        wheel_speeds = []
        for offset in (-delta, delta):
            speed_at_offset = longitudinal_speed + offset * rolling_acceleration
            wheel_speeds.append((speed_at_offset + forward.slip_ratios * np.maximum(abs(speed_at_offset), 1.))
                                / model.parameters.wheel_radius_m)
        expected_wheel_acceleration = (wheel_speeds[1] - wheel_speeds[0]) / (2 * delta)
        np.testing.assert_allclose(forward.generalized_acceleration[wheel_slice],
                                   expected_wheel_acceleration, atol=2e-4)
    if dof == 14:
        np.testing.assert_allclose(forward.generalized_acceleration[6:10], 0., atol=2e-4)
    velocity = result.state[dof:]
    linear = np.r_[velocity[:2], 0.] if dof == 3 else velocity[:3]
    omega = np.array([0., 0., velocity[2]]) if dof == 3 else velocity[3:6]
    corner_velocity = linear + np.cross(omega, forward.contact_patch_positions_body_m)
    longitudinal_speed = (corner_velocity[:, 0] * np.cos(forward.toe_rad)
                          + corner_velocity[:, 1] * np.sin(forward.toe_rad))
    if dof >= 10:
        wheel_speed = velocity[wheel_slice]
    else:
        wheel_speed = ((longitudinal_speed + forward.slip_ratios * np.maximum(abs(longitudinal_speed), 1.))
                       / model.parameters.wheel_radius_m)
    actuator = project_vehicle_yaml(load_vehicle_yaml()).ggv
    torque = result.inputs.wheel_torques_nm
    assert np.dot(torque, wheel_speed) <= actuator.max_drive_power + 1.
    equivalent_force = np.sum(torque / np.asarray(model.parameters.wheel_radius_m))
    assert -actuator.max_brake_force - .1 <= equivalent_force <= actuator.max_drive_force + .1
    for load, alpha, slip, tire in zip(forward.normal_loads_n, forward.slip_angles_rad,
                                      forward.slip_ratios, model.parameters.tires):
        assert tire.fz_min_n - 1e-3 <= load <= tire.fz_max_n + 1e-3
        assert tire.slip_in_fit_range(alpha, slip)


def test_near_peak_braking_repairs_locally_without_restarting_grid(vehicle, monkeypatch):
    from simulations.envelope.ggv import ggv_generation as ggv

    model = vehicle.model(3)
    boundaries = []
    original = ggv._solve_envelope_limit

    def capture(*args, **kwargs):
        result = original(*args, **kwargs)
        boundaries.append(result)
        return result

    def full_range_search(*args, **kwargs):
        pytest.fail("A near-peak branch correction must not restart the full acceleration search.")

    monkeypatch.setattr(ggv, "_solve_envelope_limit", capture)
    monkeypatch.setattr(ggv, "_solve_ax_limit_qss", full_range_search)
    normal_acceleration = 3.138128
    acceleration = ggv.solve_ax_limit(
        project_vehicle_yaml(load_vehicle_yaml()).ggv, speed=12., ay=normal_acceleration,
        ax_grid=np.array([-31.4, 27.5]), mode="brake", reduced_model=model,
        max_abs_beta_rad=.25, max_abs_steering_rad=.5, enforce_tire_load_range=True,
        trim_multistart=False,
    )
    result = boundaries[-1]
    assert result is not None and np.isfinite(acceleration)
    forward = model.evaluate(result.state, result.inputs)
    path_acceleration, beta_rate, _, _ = _path_motion(model, result.state, forward)
    np.testing.assert_allclose(path_acceleration, [acceleration, normal_acceleration], atol=2e-4)
    assert beta_rate == pytest.approx(0., abs=2e-5)
