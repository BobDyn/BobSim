from types import SimpleNamespace

import numpy as np
import pytest

from engines.dynpy.transient import TransientResult

from simulations.response.reduced import reduced_order_eval_sim as response


@pytest.mark.parametrize("dof", (3, 6, 10, 14))
@pytest.mark.parametrize("maneuver", ("ramp", "step"))
def test_steering_inputs_have_the_requested_shape_and_hold_speed(monkeypatch, dof, maneuver):
    torques = np.array([0.0, 0.0, 15.0, 15.0])
    trim = SimpleNamespace(success=True, state=np.zeros(2 * dof), inputs=SimpleNamespace(wheel_torques_nm=torques))
    trim.state[dof] = 15.0
    sample_times = np.array([0.0, 0.5, 0.6, 0.75, 1.0])
    observed = []

    def simulate(model_dof, *, controls, method, **kwargs):
        assert model_dof == dof
        assert method == ("Radau" if dof == 14 else "RK45")
        observed.extend(controls.inputs(t, trim.state, np.zeros(1)) for t in sample_times)
        slow = trim.state.copy()
        slow[dof] -= 1.0
        assert sum(controls.inputs(1, slow, np.zeros(1)).wheel_torques_nm) > sum(torques)
        assert controls.derivative(1, slow, np.zeros(1))[0] == 1.0
        # At the motor limit, positive error cannot wind up the integral.
        assert controls.derivative(1, slow, np.array([1000.0]))[0] == 0.0
        limited = controls.inputs(1, slow, np.array([1000.0])).wheel_torques_nm
        assert sum(limited) / 0.2 == pytest.approx(parameters.peak_drive_force_n)
        at_power_limit = trim.state.copy()
        at_power_limit[dof] = 40.0
        limited = controls.inputs(1, at_power_limit, np.array([1000.0])).wheel_torques_nm
        assert sum(limited) / 0.2 == pytest.approx(parameters.peak_drive_power_w / 40.0)
        at_power_limit[dof] = 61.0
        assert sum(controls.inputs(1, at_power_limit, np.array([1000.0])).wheel_torques_nm) == 0
        assert controls.derivative(1, at_power_limit, np.array([1000.0]))[0] < 0
        fast = trim.state.copy()
        fast[dof] += 2.0
        braking = controls.inputs(1, fast, np.zeros(1)).wheel_torques_nm
        assert sum(braking) < 0
        assert braking[0] / sum(braking) == pytest.approx(0.3)
        return TransientResult(sample_times, np.tile(trim.state, (len(sample_times), 1)), (), {}, True, "")

    parameters = SimpleNamespace(wheel_radius_m=(0.2,) * 4, mass_kg=300,
                                 peak_drive_force_n=3000, peak_drive_power_w=80000,
                                 maximum_drive_speed_mps=60, drive_distribution_front=0,
                                 brake_distribution_front=0.6)
    vehicle = SimpleNamespace(steady_state=lambda *args, **kwargs: trim, simulate=simulate, parameters=parameters)
    monkeypatch.setattr(response.Vehicle, "from_yaml", lambda *args, **kwargs: vehicle)
    if maneuver == "ramp":
        response.run_ramp_steer(
            dof=dof, start_time_s=0.5, ramp_end_time_s=0.75, stop_time_s=1.0, roadwheel_rate_deg_s=-4.0,
        )
        expected = [0.0, 0.0, -0.4, -1.0, -1.0]
    else:
        response.run_step_steer(dof=dof, step_time_s=0.5, stop_time_s=1.0,
                                roadwheel_step_deg=-2.0, rise_time_s=0.2)
        expected = [0.0, 0.0, -1.0, -2.0, -2.0]
    np.testing.assert_allclose(np.rad2deg([item.steering_rad for item in observed]), expected, atol=1e-12)
    for item in observed:
        np.testing.assert_array_equal(item.wheel_torques_nm, torques)


@pytest.mark.parametrize("start, stop", ((-1, 5), (5, 5), (6, 5)))
def test_ramp_rejects_an_invalid_time_interval(start, stop):
    with pytest.raises(ValueError, match="Ramp start"):
        response.run_ramp_steer(dof=6, start_time_s=start, stop_time_s=stop)


@pytest.mark.parametrize("end", (0.5, 0.4, 1.1, float("nan")))
def test_ramp_end_must_be_between_start_and_simulation_end(end):
    with pytest.raises(ValueError, match="Ramp start"):
        response.run_ramp_steer(dof=14, start_time_s=0.5, ramp_end_time_s=end, stop_time_s=1.0)
