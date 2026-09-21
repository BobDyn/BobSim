from __future__ import annotations

from dataclasses import replace
from copy import deepcopy

import numpy as np
import pytest
import yaml

from _0_Utils.dyn_py import (
    ModelInputs,
    Vehicle,
    compare_transient_signals,
    create_model,
    load_reduced_vehicle_parameters,
    simulate_transient,
    solve_acceleration_trim,
    solve_moment_state,
    solve_steady_state,
)
from _0_Utils.dyn_py.models import (
    VehicleModel3DOF,
    VehicleModel6DOF,
    VehicleModel10DOF,
    VehicleModel14DOF,
)
from _0_Utils.dyn_py.parameters import G
from _2_EnvelopeSim.GGV.ggv_generation import (
    _trim_is_racing_feasible,
    solve_ax_limit,
    solve_lateral_limit,
)
from _2_EnvelopeSim.YMD.ymd_generation import YMDConfig, ymd_point
from _2_EnvelopeSim.vehicle_yaml import load_vehicle_yaml, project_vehicle_yaml
from _0_Utils.vehicle_io import load_yaml, vehicle_yaml_path


@pytest.fixture(scope="module")
def parameters():
    return load_reduced_vehicle_parameters()


@pytest.mark.parametrize(
    ("dof", "state_size", "added_coordinates"),
    (
        (3, 6, ()),
        (6, 12, ("z", "roll", "pitch")),
        (10, 20, ("wheel_angle_fl", "wheel_angle_rr")),
        (14, 28, ("unsprung_z_fl", "unsprung_z_rr")),
    ),
)
def test_nested_model_state_contract(parameters, dof, state_size, added_coordinates):
    model = create_model(dof, parameters)
    assert model.state_size == state_size
    assert len(model.coordinate_names) == dof
    assert len(model.velocity_names) == dof
    for name in added_coordinates:
        assert name in model.coordinate_names

    state = model.initial_state(15.0)
    output = model.evaluate(state)
    assert output.derivative.shape == (state_size,)
    assert output.generalized_acceleration.shape == (dof,)
    assert output.wheel_forces_body_n.shape == (4, 3)
    assert output.geometric_vertical_forces_n.shape == (4,)
    assert output.algebraic_load_transfer_n.shape == (4,)
    assert output.jounce_m.shape == (4,)
    assert output.jounce_speed_mps.shape == (4,)
    assert output.contact_patch_positions_body_m.shape == (4, 3)
    assert output.contact_patch_tangents.shape == (4, 3)
    assert output.wheel_center_offsets_m.shape == (4, 3)
    assert output.camber_rad.shape == (4,)
    assert output.toe_rad.shape == (4,)
    assert output.caster_rad.shape == (4,)
    assert output.kpi_rad.shape == (4,)
    assert output.mechanical_trail_m.shape == (4,)
    assert output.scrub_radius_m.shape == (4,)
    assert output.instant_link_coefficients.shape == (4, 2)
    assert np.all(np.isfinite(output.derivative))


def test_model_classes_make_the_fidelity_ladder_explicit():
    assert issubclass(VehicleModel6DOF, VehicleModel3DOF)
    assert issubclass(VehicleModel10DOF, VehicleModel6DOF)
    assert issubclass(VehicleModel14DOF, VehicleModel10DOF)

    models = (VehicleModel3DOF, VehicleModel6DOF, VehicleModel10DOF, VehicleModel14DOF)
    assert [model.dof for model in models] == [3, 6, 10, 14]
    assert all(model.added_physics for model in models)


def test_vehicle_composes_kinematics_and_nested_dynamics(parameters):
    vehicle = Vehicle(parameters)
    jounce = np.array([0.012, -0.009, 0.004, -0.003])

    kinematics = vehicle.kinematics_at(jounce)
    np.testing.assert_array_equal(kinematics.jounce_m, jounce)
    assert vehicle.kinematics is parameters.kinematics

    model = vehicle.model(6)
    assert vehicle.model(6) is model
    assert model.parameters is parameters

    state = vehicle.initial_state(6, speed_mps=12.0)
    state[3] = np.deg2rad(0.5)
    output = vehicle.evaluate(6, state)
    np.testing.assert_allclose(
        output.instant_link_coefficients,
        vehicle.kinematics_at(output.jounce_m).instant_links.coefficient_matrix,
    )


def test_vehicle_product_api_runs_qss_and_transient(parameters):
    vehicle = Vehicle(parameters)
    trim = vehicle.steady_state(6, speed_mps=10.0)
    assert trim.success

    transient = vehicle.simulate(
        6,
        initial_state=trim.state,
        controls=trim.inputs,
        time_s=np.linspace(0.0, 0.02, 3),
        method="Radau",
    )
    assert transient.success
    assert "jounceFL" in transient.signals


def test_dyn_py_aero_projection_matches_envelope_projection(parameters):
    projection = project_vehicle_yaml(load_vehicle_yaml())

    assert parameters.cl_area_m2 == pytest.approx(projection.ggv.cl_a)
    assert parameters.cd_area_m2 == pytest.approx(projection.ggv.cd_a)
    assert parameters.aero_balance_front == pytest.approx(
        projection.ggv.aero_balance_front
    )
    assert np.isfinite(parameters.aero_balance_front)


def test_vehicle_powertrain_is_projected_to_contact_patch(parameters):
    projection = project_vehicle_yaml(load_vehicle_yaml())

    assert parameters.peak_drive_power_w == pytest.approx(80_000.0)
    assert parameters.continuous_drive_power_w == pytest.approx(75_000.0)
    assert parameters.peak_drive_force_n == pytest.approx(
        220.0 * 3.31 / parameters.wheel_radius_m[2]
    )
    assert parameters.maximum_drive_speed_mps == pytest.approx(
        6500.0 * 2.0 * np.pi / 60.0 * parameters.wheel_radius_m[2] / 3.31
    )
    assert projection.ggv.max_drive_power == pytest.approx(
        parameters.peak_drive_power_w
    )
    assert projection.summary["hardware_peak_drive_power_w"] == pytest.approx(
        124_000.0
    )
    assert projection.summary["controller_drive_power_limit_w"] == pytest.approx(
        80_000.0
    )
    assert projection.ggv.max_drive_force == pytest.approx(
        parameters.peak_drive_force_n
    )
    assert projection.ggv.max_drive_speed == pytest.approx(
        parameters.maximum_drive_speed_mps
    )


def test_event_power_cap_propagates_without_increasing_vehicle_limit(parameters):
    capped = Vehicle(parameters).with_power_limit(32_000.0)

    assert capped.parameters.peak_drive_power_w == pytest.approx(32_000.0)
    assert capped.parameters.continuous_drive_power_w == pytest.approx(32_000.0)
    assert capped.model(6).parameters.peak_drive_power_w == pytest.approx(32_000.0)
    assert parameters.peak_drive_power_w == pytest.approx(80_000.0)

    still_hardware_limited = Vehicle(parameters).with_power_limit(100_000.0)
    assert still_hardware_limited.parameters.peak_drive_power_w == pytest.approx(
        80_000.0
    )


def test_component_cg_move_recomputes_total_cg_and_yaw_inertia(
    parameters,
    tmp_path,
):
    data = deepcopy(load_yaml(vehicle_yaml_path()))
    data["driver_mass"]["cg_m"][0] += 0.10
    moved_path = tmp_path / "moved_driver.yml"
    moved_path.write_text(yaml.safe_dump(data), encoding="utf-8")

    moved = load_reduced_vehicle_parameters(moved_path)

    assert moved.mass_kg == pytest.approx(parameters.mass_kg)
    assert moved.static_wheel_loads_n != parameters.static_wheel_loads_n
    assert moved.inertia_kg_m2[2][2] != pytest.approx(
        parameters.inertia_kg_m2[2][2]
    )
    assert moved.inertia_kg_m2[0][2] != pytest.approx(
        parameters.inertia_kg_m2[0][2]
    )


def test_dyn_py_applies_aero_at_projected_cop(parameters):
    model = create_model(6, parameters)
    projection = project_vehicle_yaml(load_vehicle_yaml())
    speed_mps = float(projection.summary["reference_speed_m_per_s"])
    body_velocities = np.array([speed_mps, 0.0, 0.0, 0.0, 0.0, 0.0])

    force, moment = model._aero_load(body_velocities)

    dynamic_pressure = 0.5 * parameters.rho_air_kg_m3 * speed_mps**2
    drag_force = np.array(
        [-dynamic_pressure * parameters.cd_area_m2, 0.0, 0.0]
    )
    downforce_force = np.array(
        [0.0, 0.0, -dynamic_pressure * parameters.cl_area_m2]
    )
    expected_moment = np.cross(parameters.aero_cop_m, downforce_force)
    expected_moment += np.cross(parameters.aero_drag_application_m, drag_force)

    np.testing.assert_allclose(force, drag_force + downforce_force)
    np.testing.assert_allclose(moment, expected_moment)

    # Match BobLib: force at aero_ref_m plus the tabulated free pitch moment there.
    free_moment = np.array([0.0, float(projection.summary["my_nm"]), 0.0])
    source_wrench_moment = np.cross(
        parameters.aero_drag_application_m,
        drag_force + downforce_force,
    ) + free_moment
    np.testing.assert_allclose(moment, source_wrench_moment)


def test_3dof_and_6dof_initial_planar_response_remains_same_order(parameters):
    no_aero = replace(
        parameters,
        cl_area_m2=0.0,
        cd_area_m2=0.0,
    )
    model_3 = create_model(3, no_aero)
    model_6 = create_model(6, no_aero)
    inputs = ModelInputs(steering_rad=0.025)

    output_3 = model_3.evaluate(model_3.initial_state(15.0), inputs)
    output_6 = model_6.evaluate(model_6.initial_state(15.0), inputs)

    np.testing.assert_allclose(
        output_3.generalized_acceleration,
        output_6.generalized_acceleration[[0, 1, 5]],
        rtol=1e-1,
        atol=1e-3,
    )


def test_3dof_has_algebraic_load_transfer_and_rear_wheel_drive(parameters):
    model = create_model(3, parameters)
    static = solve_acceleration_trim(
        model,
        speed_mps=12.0,
        longitudinal_acceleration_mps2=0.0,
        lateral_acceleration_mps2=0.0,
    )
    accelerating = solve_acceleration_trim(
        model,
        speed_mps=12.0,
        longitudinal_acceleration_mps2=G,
        lateral_acceleration_mps2=0.0,
    )
    cornering = solve_acceleration_trim(
        model,
        speed_mps=12.0,
        longitudinal_acceleration_mps2=0.0,
        lateral_acceleration_mps2=1.5 * G,
    )

    assert static.success and accelerating.success and cornering.success
    assert np.sum(accelerating.output.normal_loads_n[:2]) < np.sum(
        static.output.normal_loads_n[:2]
    )
    assert np.sum(accelerating.output.normal_loads_n[2:]) > np.sum(
        static.output.normal_loads_n[2:]
    )
    assert cornering.output.normal_loads_n[1] > cornering.output.normal_loads_n[0]
    assert cornering.output.normal_loads_n[3] > cornering.output.normal_loads_n[2]
    np.testing.assert_allclose(accelerating.inputs.wheel_torques_nm[:2], 0.0)
    assert np.all(np.asarray(accelerating.inputs.wheel_torques_nm[2:]) > 0.0)


def test_flat_road_qss_loads_converge_across_fidelity_ladder(parameters):
    results = {
        dof: solve_acceleration_trim(
            create_model(dof, parameters),
            speed_mps=12.0,
            longitudinal_acceleration_mps2=0.5 * G,
            lateral_acceleration_mps2=G,
        )
        for dof in (3, 6, 10, 14)
    }
    assert all(result.success for result in results.values())
    np.testing.assert_allclose(
        results[3].output.normal_loads_n,
        results[6].output.normal_loads_n,
        rtol=0.06,
        atol=15.0,
    )
    np.testing.assert_allclose(
        results[6].output.normal_loads_n,
        results[10].output.normal_loads_n,
        rtol=2e-4,
        atol=1e-3,
    )
    np.testing.assert_allclose(
        results[10].output.normal_loads_n,
        results[14].output.normal_loads_n,
        rtol=0.04,
        atol=15.0,
    )


@pytest.mark.parametrize(("dof", "wheel_slice"), ((10, slice(6, 10)), (14, slice(10, 14))))
def test_qss_rotating_wheels_follow_vehicle_acceleration(parameters, dof, wheel_slice):
    result = solve_acceleration_trim(
        create_model(dof, parameters),
        speed_mps=12.0,
        longitudinal_acceleration_mps2=G,
        lateral_acceleration_mps2=0.0,
    )

    assert result.success
    expected = G / np.asarray(parameters.wheel_radius_m)
    np.testing.assert_allclose(
        result.output.generalized_acceleration[wheel_slice],
        expected,
        rtol=1e-7,
        atol=1e-7,
    )


def test_instant_links_are_mirrored_and_close_6dof_upright_force_balance(parameters):
    coefficients = parameters.double_wishbone.instant_links_at(np.zeros(4)).coefficient_matrix
    np.testing.assert_allclose(coefficients[0, 0], coefficients[1, 0], atol=1e-12)
    np.testing.assert_allclose(coefficients[2, 0], coefficients[3, 0], atol=1e-12)
    np.testing.assert_allclose(coefficients[0, 1], -coefficients[1, 1], atol=1e-12)
    np.testing.assert_allclose(coefficients[2, 1], -coefficients[3, 1], atol=1e-12)

    model = create_model(6, parameters)
    output = model.evaluate(model.initial_state(15.0), ModelInputs(steering_rad=0.04))
    assert np.max(np.abs(output.geometric_vertical_forces_n)) > 1.0
    np.testing.assert_allclose(
        output.normal_loads_n,
        output.suspension_forces_n + output.geometric_vertical_forces_n,
        rtol=1e-9,
        atol=1e-8,
    )


def test_instant_links_are_derived_at_current_corner_jounce(parameters):
    nominal = parameters.double_wishbone.instant_links_at(np.zeros(4)).coefficient_matrix
    traveled = parameters.double_wishbone.instant_links_at(
        np.array([0.02, -0.02, 0.02, -0.02])
    ).coefficient_matrix
    assert not np.allclose(traveled, nominal)


def test_body_roll_uses_precomputed_kinematic_attitude_and_contact_migration(parameters):
    model = create_model(6, parameters)
    state = model.initial_state(12.0)
    state[3] = np.deg2rad(1.0)

    output = model.evaluate(state)
    nominal = parameters.corner_positions

    assert np.max(np.abs(output.camber_rad)) > np.deg2rad(0.05)
    assert np.max(np.abs(output.toe_rad)) > np.deg2rad(0.001)
    assert not np.allclose(output.contact_patch_positions_body_m, nominal)
    assert output.camber_rad[0] != pytest.approx(-output.camber_rad[1])
    assert output.jounce_m[0] * output.jounce_m[1] < 0.0
    assert abs(output.jounce_m[0]) == pytest.approx(
        abs(output.jounce_m[1]),
        rel=1e-2,
    )
    np.testing.assert_allclose(
        output.instant_link_coefficients,
        parameters.double_wishbone.instant_links_at(output.jounce_m).coefficient_matrix,
    )


def test_camber_curves_modify_reduced_tire_capacity(parameters):
    loads = np.asarray(parameters.static_wheel_loads_n)
    zero_camber = np.zeros(4)
    high_camber = np.full(4, np.deg2rad(4.0))

    assert np.all(
        parameters.tire.mu_y(loads, high_camber)
        < parameters.tire.mu_y(loads, zero_camber)
    )
    assert np.all(
        parameters.tire.cornering_stiffness(loads, high_camber)
        < parameters.tire.cornering_stiffness(loads, zero_camber)
    )


def test_14dof_instant_link_force_has_equal_and_opposite_unsprung_reaction(parameters):
    model = create_model(14, parameters)
    output = model.evaluate(model.initial_state(15.0), ModelInputs(steering_rad=0.04))
    unsprung_accel = output.generalized_acceleration[6:10]
    unsprung_mass = np.asarray(parameters.unsprung_mass_kg)
    np.testing.assert_allclose(
        unsprung_accel,
        -output.geometric_vertical_forces_n / unsprung_mass,
        rtol=1e-9,
        atol=1e-9,
    )


@pytest.mark.parametrize("dof", (3, 6, 10, 14))
def test_constant_radius_qss_converges_for_every_fidelity(parameters, dof):
    model = create_model(dof, parameters)
    result = solve_steady_state(model, speed_mps=15.0, yaw_rate_radps=0.2)

    assert result.success, result.message
    assert result.residual_norm < 1e-7
    assert np.all(result.output.normal_loads_n > 0.0)
    assert result.unknowns["steering_rad"] > 0.0
    if dof >= 10:
        assert "slip_rr" in result.unknowns
    if dof == 14:
        assert "unsprung_z_rr_m" in result.unknowns


def test_qss_returns_infeasible_result_when_kinematic_steer_guess_exceeds_bound(parameters):
    model = create_model(3, parameters)
    result = solve_acceleration_trim(
        model,
        speed_mps=5.0,
        longitudinal_acceleration_mps2=0.0,
        lateral_acceleration_mps2=4.0 * 9.80665,
        max_nfev=20,
    )

    assert not result.success
    assert result.unknowns["steering_rad"] <= 0.7


@pytest.mark.parametrize("dof", (3, 6, 10, 14))
@pytest.mark.parametrize("speed_mps", (6.0, 18.0))
def test_ggv_lateral_trim_is_acceleration_not_implied_corner_radius(
    parameters,
    dof,
    speed_mps,
):
    model = create_model(dof, parameters)
    result = solve_acceleration_trim(
        model,
        speed_mps=speed_mps,
        longitudinal_acceleration_mps2=0.0,
        lateral_acceleration_mps2=8.0,
    )

    assert result.success, result.message
    assert result.yaw_rate_radps == pytest.approx(0.0)
    assert result.lateral_acceleration_mps2 == pytest.approx(8.0, abs=1e-6)


def test_ggv_pure_lateral_endpoint_is_closed_at_coast(parameters):
    projection = project_vehicle_yaml(load_vehicle_yaml())
    ay, ax = solve_lateral_limit(
        projection.ggv,
        speed=12.0,
        ay_upper=2.6 * 9.80665,
        reduced_model=create_model(3, parameters),
        binary_iterations=4,
    )

    # The endpoint is where the first tire reaches FZMIN.
    assert 1.6 * 9.80665 < ay < 1.9 * 9.80665
    assert ax < 0.0
    assert abs(ax) < 1.0


def test_ggv_force_closure_uses_kinematic_bump_toe(parameters):
    model = create_model(6, parameters)
    result = solve_acceleration_trim(
        model,
        speed_mps=12.0,
        longitudinal_acceleration_mps2=0.0,
        lateral_acceleration_mps2=1.7 * G,
    )

    assert result.success
    assert np.max(np.abs(result.output.toe_rad)) > 1e-4
    assert _trim_is_racing_feasible(
        result,
        model=model,
        ay=1.7 * G,
        max_abs_beta_rad=0.25,
        max_abs_steering_rad=0.5,
    )

    invalid_output = replace(
        result.output,
        normal_loads_n=np.array(
            [parameters.tire.fz_min_n - 1.0, 500.0, 500.0, 500.0]
        ),
    )
    invalid_trim = replace(result, output=invalid_output)
    assert not _trim_is_racing_feasible(
        invalid_trim,
        model=model,
        ay=1.7 * G,
        max_abs_beta_rad=0.25,
        max_abs_steering_rad=0.5,
    )
    assert _trim_is_racing_feasible(
        invalid_trim,
        model=model,
        ay=1.7 * G,
        max_abs_beta_rad=0.25,
        max_abs_steering_rad=0.5,
        enforce_tire_load_range=False,
    )


def test_prescribed_acceleration_and_moment_qss_use_same_6dof_equations(parameters):
    model = create_model(6, parameters)
    acceleration = solve_acceleration_trim(
        model,
        speed_mps=15.0,
        longitudinal_acceleration_mps2=2.0,
        lateral_acceleration_mps2=4.0,
    )
    assert acceleration.success
    assert acceleration.residual_norm < 1e-7

    left = solve_moment_state(
        model,
        speed_mps=15.0,
        beta_rad=0.02,
        steering_rad=0.04,
    )
    right = solve_moment_state(
        model,
        speed_mps=15.0,
        beta_rad=-0.02,
        steering_rad=-0.04,
    )
    assert left.success and right.success
    assert left.output.body_moment_nm[2] == pytest.approx(
        -right.output.body_moment_nm[2], rel=2e-3, abs=1.0
    )


@pytest.mark.parametrize("dof", (3, 6, 10, 14))
def test_transient_result_exposes_boblib_comparison_channels(parameters, dof):
    model = create_model(dof, parameters)
    trim = solve_steady_state(model, speed_mps=10.0)
    assert trim.success
    result = simulate_transient(
        model,
        initial_state=trim.state,
        controls=trim.inputs,
        time_s=np.linspace(0.0, 0.1, 6),
        method="Radau" if dof >= 6 else "RK45",
        rtol=1e-5,
        atol=1e-7,
    )

    assert result.success
    for signal in (
        "velX",
        "velY",
        "yawVel",
        "sideslip",
        "accX",
        "accY",
        "roll",
        "jounceFL",
        "jounceVelRR",
        "camberFL",
        "toeFR",
        "casterRL",
        "kpiRR",
        "mechanicalTrailFL",
        "scrubRadiusFR",
        "contactPatchTangentXRL",
        "wheelCenterOffsetZRR",
        "instantLinkLongitudinalFL",
        "instantLinkLateralRR",
    ):
        assert signal in result.signals
    metrics = compare_transient_signals(
        result.time_s,
        {"yawVel": result.signals["yawVel"]},
        result,
    )
    assert metrics["yawVel"]["rmse"] == pytest.approx(0.0, abs=1e-14)


@pytest.mark.parametrize("dof", (3, 6, 10, 14))
def test_ggv_and_ymd_backends_call_shared_qss_model(parameters, dof):
    projection = project_vehicle_yaml(load_vehicle_yaml())
    model = create_model(dof, parameters)
    ax_limit = solve_ax_limit(
        projection.ggv,
        speed=15.0,
        ay=4.0,
        ax_grid=np.linspace(0.0, 20.0, 21),
        mode="drive",
        reduced_model=model,
    )
    assert np.isfinite(ax_limit)
    assert ax_limit > 0.0

    ay, mz, converged = ymd_point(
        projection.ymd,
        config=YMDConfig(
            speed=15.0,
            model_dof=dof,
            verbose=False,
            warn_tire_load_range=False,
        ),
        beta=0.02,
        hwa=0.04,
        reduced_model=model,
    )
    assert converged
    assert np.isfinite(ay)
    assert np.isfinite(mz)
