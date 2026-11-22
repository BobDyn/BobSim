"""Measurement windows must not depend on an adaptive solver's sample density."""
import numpy as np
import pytest

from simulations.response.mbd.measurement import window_statistics


@pytest.mark.parametrize("time", [np.linspace(0, 2, 31), np.r_[0, 1, 1.7, 1.99, 2]])
def test_exact_linear_statistics_on_different_grids(time):
    result = window_statistics(time, 3*time + 4, 1)
    assert result["mean"] == pytest.approx(8.5)
    assert result["slope"] == pytest.approx(3)
    assert result["std"] == pytest.approx(3 / np.sqrt(12))


def test_bounds_are_interpolated_and_duplicates_use_post_event_value():
    result = window_statistics([0, 1, 1, 2], [0, 999, 2, 4], 0.5, end_time=1.75)
    assert result["mean"] == pytest.approx(3)
    assert result["minimum"] == pytest.approx(2.5)
    assert result["maximum"] == pytest.approx(3.5)


@pytest.mark.parametrize("t,y,d", [([0, 1], [0, 1], 2), ([1, 0], [0, 1], 1),
                                      ([0, 1], [0, np.nan], 1), ([0, 1], [0, 1], 0)])
def test_invalid_or_incomplete_window_is_rejected(t, y, d):
    with pytest.raises(ValueError):
        window_statistics(t, y, d)


def test_runner_preserves_command_defaults_and_failure_status(tmp_path):
    import json
    from simulations.response.mbd._modelica_runner import ModelicaRunner
    executable = tmp_path / 'Fixture'
    executable.write_text('''#!/usr/bin/python3
import sys
from pathlib import Path
for arg in sys.argv:
    if arg.startswith('-r='):
        Path(arg[3:]).write_text('time,x,steadyStateConditionsMet\\n0,0,1\\n1,2,1\\n2,4,1\\n')
print('LOG_SUCCESS | info | The simulation finished successfully.')
print('LOG_STDOUT | info | Simulation call terminate() at time 2.000000')
print('| | | Message : Reached closed-loop steady-state lateral-acceleration target')
''')
    executable.chmod(0o755)
    (tmp_path / 'Fixture_init.xml').write_text('''<fmiModelDescription><ModelVariables>
    <ScalarVariable name="steadyStateHoldDuration" causality="parameter"><Real start="1"/></ScalarVariable>
    </ModelVariables></fmiModelDescription>''')
    runner = ModelicaRunner(tmp_path, 'Fixture', {'measurement_window_s': 0.5})
    result = runner.run_case(['x', 'steadyStateConditionsMet'], 'steady', {})
    manifest = json.loads((__import__('pathlib').Path(result['_run_dir']) / 'manifest.json').read_text())
    assert result['x'] == pytest.approx(3.5)
    assert result['_termination_time'] == 2
    assert manifest['started_at'] <= manifest['ended_at']
    assert manifest['command'][0] == str(executable)
    assert manifest['effective_parameters']['steadyStateHoldDuration'] == '1'
    assert len(manifest['input_sha256']['Fixture']) == 64
    assert manifest['measurement']['duration_s'] == 0.5
    with pytest.raises(KeyError):
        runner.run_case(['absent'], 'steady', {})
    failed = [json.loads(p.read_text()) for p in tmp_path.glob('results/run_*/manifest.json')
              if json.loads(p.read_text())['status'] == 'failed']
    assert len(failed) == 1
    assert failed[0]['command'] and failed[0]['ended_at']


def test_current_driver_alias_and_empty_override_file(tmp_path):
    from simulations.response.mbd._modelica_runner import ModelicaRunner
    (tmp_path / 'Native').touch()
    (tmp_path / 'Native_init.xml').write_text('''<fmiModelDescription><ModelVariables>
    <ScalarVariable name="driver.useMode" causality="parameter"><Integer start="0"/></ScalarVariable>
    </ModelVariables></fmiModelDescription>''')
    runner = ModelicaRunner(tmp_path, 'Native', {})
    overrides = tmp_path / 'overrides.txt'
    runner._write_override_file(overrides, {'useMode': 3})
    assert overrides.read_text() == 'driver.useMode=3\n'
    runner._write_override_file(overrides, {'useMode': 0})
    command = runner._build_command(overrides, tmp_path / 'result.csv')
    assert not any(arg.startswith('-overrideFile=') for arg in command)
