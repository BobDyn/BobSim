from dataclasses import replace

import numpy as np
import pytest

from engines.dynpy.aero import AeroMap
from engines.dynpy.models import ModelInputs, _body_to_world_rotation, create_model
from engines.dynpy.parameters import load_reduced_vehicle_parameters


@pytest.fixture
def aero():
    front = np.array([0.05, 0.1, 0.2])
    rear = np.array([0.04, 0.12, 0.25])
    x, y = np.meshgrid(front, rear, indexing="ij")
    base = 10 + 20*x + 30*y + 40*x*y
    return AeroMap(front, rear, np.array([base*i for i in (1, 2, 3, 4, 5)]), 13., 1.225,
                   np.array([.4, -.1, .2]), np.array([[1, .6, -.22], [1, -.6, -.22],
                                                     [-1, .6, -.21], [-1, -.6, -.21]]), .3)


@pytest.mark.parametrize("front,rear", [(.075, .09), (.1, .12), (-1, 2)])
def test_boblib_clamped_bilinear_wrench_includes_all_free_moments(aero, front, rear):
    velocity = np.array([3., 4., 12.])
    force, moment = aero.wrench(np.array([front]*2+[rear]*2), velocity, .6125)
    x, y = np.clip(front, .05, .2), np.clip(rear, .04, .25)
    base = 10 + 20*x + 30*y + 40*x*y
    expected_force = -.5*base*velocity/13 + np.array([0, 0, -base])
    expected_moment = .5*base*np.array([3, 4, 5]) + np.cross(aero.reference_m, expected_force)
    np.testing.assert_allclose(force, expected_force)
    np.testing.assert_allclose(moment, expected_moment)


def test_height_points_follow_chassis_pose_not_wheel_jounce(aero):
    roll = .1
    rotation = _body_to_world_rotation(np.array([roll, 0., 0.]))
    heights = aero.ride_heights(-.01, rotation)
    expected = .29 + aero.height_points_m[:, 1]*np.sin(roll) + aero.height_points_m[:, 2]*np.cos(roll)
    np.testing.assert_allclose(heights, expected)
    np.testing.assert_allclose(aero.ride_heights(0., np.eye(3)), [.08, .08, .09, .09])


def test_zero_downforce_preserves_pure_moments_and_zero_speed_removes_loads(aero):
    loads = aero.loads.copy()
    loads[:2] = 0
    pure_moment = replace(aero, loads=loads)
    force, moment = pure_moment.wrench(np.array([.1]*4), np.array([13., 0, 0]), 1.225)
    np.testing.assert_array_equal(force, np.zeros(3))
    assert np.all(moment > 0)
    for value in pure_moment.wrench(np.array([.1]*4), np.zeros(3), 1.225):
        np.testing.assert_array_equal(value, np.zeros(3))


@pytest.mark.parametrize("dof", [3, 6, 10, 14])
def test_models_use_current_aero_pose_and_full_wrench(aero, dof):
    parameters = replace(load_reduced_vehicle_parameters(), aero=aero)
    model = create_model(dof, parameters)
    state = model.initial_state(13.)
    if dof != 3:
        state[2:5] = [-.01, .02, -.01]
    pose, velocity = model._body_state(state[:dof], state[dof:])
    heights = aero.ride_heights(pose[2], _body_to_world_rotation(pose[3:6]))
    force, moment = aero.wrench(heights, velocity[:3], parameters.rho_air_kg_m3)
    without = create_model(dof, replace(parameters, aero=None))
    if dof != 3:
        actual, baseline = model.evaluate(state), without.evaluate(state)
        np.testing.assert_allclose(actual.body_force_n-baseline.body_force_n, force, atol=1e-9)
        np.testing.assert_allclose(actual.body_moment_nm-baseline.body_moment_nm, moment, atol=1e-9)
    else:
        vertical = model._vertical_forces(state[:dof], state[dof:], pose, velocity, np.eye(3), ModelInputs())
        assert sum(vertical.normal_loads_n)-sum(parameters.static_wheel_loads_n) == pytest.approx(-force[2])
        np.testing.assert_allclose(model._aero_load(velocity, pose)[1], moment)
        vertical_forces = np.zeros((4, 3))
        vertical_forces[:, 2] = vertical.normal_loads_n - parameters.static_wheel_loads_n
        reaction = np.cross(parameters.corner_positions, vertical_forces).sum(axis=0)
        np.testing.assert_allclose(reaction[:2] + moment[:2], 0, atol=1e-9)


def test_yaml_height_points_use_origin_coordinates_and_mirror_before_cg_shift():
    from common.vehicle_io import load_yaml, vehicle_yaml_path

    data = load_yaml(vehicle_yaml_path())["aero"]
    cg = (0.4, .07, .3)
    aero = AeroMap.from_yaml(data, cg)
    front, rear = data["front_left_ride_height_ref_m"], data["rear_left_ride_height_ref_m"]
    expected = np.array([front, [front[0], -front[1], front[2]],
                         rear, [rear[0], -rear[1], rear[2]]])
    np.testing.assert_allclose(aero.height_points_m + cg, expected)
    np.testing.assert_allclose(aero.ride_heights(0, np.eye(3)), expected[:, 2])
    assert aero.front_grid[0] < front[2] < aero.front_grid[-1]
    assert aero.rear_grid[0] < rear[2] < aero.rear_grid[-1]


def test_vehicle_yaml_accepts_zero_downforce_with_a_free_pitch_moment(tmp_path):
    import yaml
    from common.vehicle_io import load_yaml, vehicle_yaml_path

    data = load_yaml(vehicle_yaml_path())
    section = data["aero"]
    shape = (len(section["front_ride_height_grid_m"]), len(section["rear_ride_height_grid_m"]))
    section["downforce_table_n"] = np.zeros(shape).tolist()
    section["drag_table_n"] = np.zeros(shape).tolist()
    section["my_table_nm"] = np.full(shape, 17.).tolist()
    path = tmp_path / "vehicle.yml"
    path.write_text(yaml.safe_dump(data))
    model = create_model(6, load_reduced_vehicle_parameters(path))
    force, moment = model._aero_load(np.array([15., 0, 0, 0, 0, 0]))
    np.testing.assert_array_equal(force, np.zeros(3))
    np.testing.assert_allclose(moment, [0, 17, 0])


def test_planar_load_transfer_reuses_the_body_aero_wrench(monkeypatch):
    model = create_model(3, load_reduced_vehicle_parameters())
    original = model._aero_load
    calls = []

    def counted(*args):
        result = original(*args)
        calls.append(result)
        return result

    monkeypatch.setattr(model, '_aero_load', counted)
    state = model.initial_state(15.)
    output = model.evaluate(state, ModelInputs(), normal_loads_n=model.parameters.static_wheel_loads_n,
                            algebraic_slips=np.zeros(4))
    assert len(calls) == 1
    force, _ = calls[0]
    expected_load = sum(model.parameters.static_wheel_loads_n) - force[2]
    np.testing.assert_allclose(np.sum(output.suspension_forces_n), expected_load)
    np.testing.assert_allclose(output.body_force_n[:2], output.wheel_forces_body_n[:, :2].sum(axis=0) + force[:2])
