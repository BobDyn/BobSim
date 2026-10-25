"""Native response readiness, dispatch, and strict runtime calibration."""
from pathlib import Path
import pytest

from app import native_response, registry
from simulations.response.mbd._modelica_runner import ModelicaRunner


def test_all_response_workflows_are_run_only():
    workflows = registry.build_workflows()
    actions = registry.build_action_specs(Path('.'), 'python', '-m')
    for workflow in workflows:
        if any(action in native_response.ACTIONS for action in workflow.actions):
            assert len(workflow.actions) == 1
            assert not actions[workflow.actions[0]].requires_external_toolchain


def test_configure_preserves_report_and_maps_native_driver(monkeypatch, tmp_path):
    monkeypatch.setattr(native_response, 'bundle', lambda vehicle:
                        (tmp_path, {'executable': 'Native', 'nonlinear_solver': 'kinsol'}, {'mass': '300'}))
    original = {'simulation': {'extra_args': ['-nls=old', '-jacobian=internalNumerical']},
                'plots': {'quad': {'enabled': True}}}
    result = native_response.configure(original, {})
    assert result['simulation']['geometry_prefix'] == 'chassis.'
    assert result['plots'] == original['plots']
    assert 'runtime_overrides' not in original['simulation']
    assert result['simulation']['override_aliases']['useMode'] == 'driver.useMode'
    assert result['simulation']['override_aliases']['targetVel'] == 'initialVel'
    assert result['simulation']['extra_args'][-1] == '-nls=kinsol'


def test_missing_or_stale_binary_blocks_run(monkeypatch):
    def missing(vehicle):
        raise FileNotFoundError()
    monkeypatch.setattr(native_response, 'bundle', missing)
    assert 'Architecture' in native_response.unavailable_reason({})
    with pytest.raises(FileNotFoundError):
        native_response.configure({}, {})


def test_native_overrides_cannot_be_silently_dropped(tmp_path):
    (tmp_path / 'Native').touch()
    (tmp_path / 'Native_init.xml').write_text('''<fmiModelDescription><ModelVariables>
      <ScalarVariable name="driver.stepDuration" causality="parameter" isValueChangeable="true">
        <Real start="1"/></ScalarVariable>
      <ScalarVariable name="mass" causality="parameter" isValueChangeable="true"><Real start="200"/></ScalarVariable>
      <ScalarVariable name="frozen" causality="parameter" isValueChangeable="false"><Real start="1"/></ScalarVariable>
    </ModelVariables></fmiModelDescription>''')
    runner = ModelicaRunner(tmp_path, 'Native', {'strict_overrides': True,
        'runtime_overrides': {'mass': '300'},
        'override_aliases': {'stepDuration': 'driver.stepDuration', 'frRampSteerDuration': 'driver.stepDuration'}})
    output = tmp_path / 'overrides.txt'
    runner._write_override_file(output, {'stepDuration': .1, 'frRampSteerDuration': .1, 'stopTime': 2})
    assert output.read_text().count('driver.stepDuration=') == 1
    assert 'mass=300' in output.read_text()
    with pytest.raises(ValueError, match='Unknown native'):
        runner._write_override_file(output, {'missing': 5})
    with pytest.raises(ValueError, match='not editable'):
        runner._write_override_file(output, {'frozen': 2})
