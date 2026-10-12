from types import SimpleNamespace

import numpy as np
import pytest

from simulations.response.reduced import reduced_order_eval_sim as response


@pytest.mark.parametrize("dof", (3, 6, 10, 14))
@pytest.mark.parametrize("maneuver", ("ramp", "step"))
def test_steering_inputs_have_the_requested_shape_and_keep_trim_torque(monkeypatch, dof, maneuver):
    torques = np.array([0.0, 0.0, 15.0, 15.0])
    trim = SimpleNamespace(success=True, state=np.zeros(6), inputs=SimpleNamespace(wheel_torques_nm=torques))
    sample_times = np.array([0.0, 0.5, 0.6, 0.75, 1.0])
    observed = []

    def simulate(model_dof, *, controls, method, **kwargs):
        assert model_dof == dof
        assert method == ("Radau" if dof == 14 else "RK45")
        observed.extend(controls(t, trim.state) for t in sample_times)
        return None

    vehicle = SimpleNamespace(steady_state=lambda *args, **kwargs: trim, simulate=simulate)
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
