from simulations.reduced.fidelity_suite import default_cases


def test_fidelity_suite_cases_target_added_physics():
    cases = {case.name: case for case in default_cases()}

    assert set(cases) == {
        "step_steer",
        "slalom",
        "brake_in_turn",
        "four_wheel_bump",
    }
    assert "wheel" in cases["brake_in_turn"].exposes
    assert "unsprung" in cases["four_wheel_bump"].exposes
