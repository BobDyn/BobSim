"""Require a completed Modelica settling hold before accepting a steady point."""
import pytest

from simulations.response.mbd._modelica_runner import ModelicaRunner
from simulations.response.mbd.steady_state.steady_state_eval_sim import SteadyStateEvalSim


ACCEPTED = "Reached closed-loop steady-state lateral-acceleration target"


def test_termination_event_is_independent_of_final_csv_sample(tmp_path):
    log = tmp_path / "run.log"
    log.write_text(
        "LOG_STDOUT | info | Simulation call terminate() at time 9.700000\n"
        f"| | | Message : {ACCEPTED}\n"
        "LOG_SUCCESS | info | The simulation finished successfully.\n"
    )
    result = {"time": 9.699, "terminationStatus": 0, "steadyStateConditionsMet": 1}
    result.update(ModelicaRunner._termination_details(log))
    assert result["_termination_time"] == 9.7
    assert SteadyStateEvalSim._settling_error(result) == ""


def test_normal_stop_does_not_confirm_settling_hold(tmp_path):
    log = tmp_path / "run.log"
    log.write_text("LOG_SUCCESS | info | The simulation finished successfully.\n")
    result = {"steadyStateConditionsMet": 1, **ModelicaRunner._termination_details(log)}
    assert "hold was not confirmed" in SteadyStateEvalSim._settling_error(result)


@pytest.mark.parametrize("message", [
    "BOBLIB_TIRE_LOAD_LIMIT: t=10 s",
    "BOBLIB_SETTLING_TIMEOUT: t=30 s",
    "BOBLIB_SIDESLIP_LIMIT: t=10 s",
    "Reached open-loop step-steer steady-state: der(yawVel) below tolerance (held 0.1s)",
])
def test_limit_or_other_maneuver_exit_is_not_a_steady_point(message):
    result = {"steadyStateConditionsMet": 1, "_termination_message": message}
    sim = SteadyStateEvalSim.__new__(SteadyStateEvalSim)
    accepted, failed = sim._successful_and_failed([result])
    assert accepted == []
    assert len(failed) == 1
    assert sim._steady_rows([result]) == []


@pytest.mark.parametrize("condition", [None, float("nan"), 0])
def test_missing_or_unsettled_signal_is_not_accepted(condition):
    assert SteadyStateEvalSim._settling_error({
        "steadyStateConditionsMet": condition, "_termination_message": ACCEPTED,
    })
