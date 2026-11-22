"""Continuation preserves requested order and rejects unaccepted or incomplete points."""

import numpy as np
import pytest

from simulations.response.mbd.steady_state.continuation import sequence_cases, extract_points

CONTRACT = {'enableSteadyStateSequence': 'false', 'steadyStatePointCount': '1',
            'steadyStateTargets[64]': '0'}


def case(speed, ay):
    return {'_testVel': speed, '_testAy': ay, 'useMode': 3, 'initialVel': speed,
            'targetAy': ay, 'startTime': 0, 'stopTime': 30}


def test_grouping_preserves_reverse_sweep_and_conditions_once_per_speed():
    sequences = sequence_cases([case(15, 4), case(20, 2), case(15, 2)], {}, CONTRACT)
    assert len(sequences) == 2
    sequence = sequences[0]
    assert [sequence[f'steadyStateTargets[{i}]'] for i in (1, 2, 3)] == [0, 4, 2]
    assert sequence['stopTime'] == 90
    assert sequence['steadyStatePointCount'] == 3


def test_old_binary_cannot_silently_ignore_sequence():
    with pytest.raises(ValueError, match='Rebuild'):
        sequence_cases([case(15, 2)], {}, {})


def result(tmp_path, events):
    path = tmp_path / 'run.log'
    path.write_text(events)
    t = np.linspace(0, 3, 1501)
    return {'_status': 'ok', '_log_file': path.as_posix(), '_run_dir': tmp_path.as_posix(),
            'time': t, 'accY': 2*t, 'steadyStateConditionsMet': np.ones_like(t)}


def test_limit_exit_preserves_accepted_point_and_marks_unfinished_point(tmp_path):
    seq = sequence_cases([case(15, 2), case(15, 4)], {}, CONTRACT)[0]
    raw = result(tmp_path, 'BOBLIB_STEADY_POINT: index=1 time=1 target=0\n'
                 'BOBLIB_STEADY_POINT: index=2 time=2 target=2\nBOBLIB_TIRE_LOAD_LIMIT\n')
    rows = extract_points(seq, raw, ['accY', 'steadyStateConditionsMet'], 0.5)
    assert rows[0]['_status'] == 'ok'
    assert rows[0]['accY'] == pytest.approx(3.496)
    assert rows[0]['_acceptance_event']['time'] == 2
    assert rows[1]['_status'] == 'failed'
    assert (tmp_path / 'sequence_points.json').exists()


def test_no_event_record_means_no_accepted_point(tmp_path):
    seq = sequence_cases([case(15, 2)], {}, CONTRACT)[0]
    rows = extract_points(seq, result(tmp_path, 'Simulation finished successfully'),
                          ['accY', 'steadyStateConditionsMet'], 0.5)
    assert rows[0]['_status'] == 'failed'


def test_corrupt_acceptance_order_is_rejected(tmp_path):
    seq = sequence_cases([case(15, 2)], {}, CONTRACT)[0]
    with pytest.raises(ValueError, match='out-of-order'):
        extract_points(seq, result(tmp_path, 'BOBLIB_STEADY_POINT: index=2 time=2 target=2'),
                       ['accY', 'steadyStateConditionsMet'], 0.5)


def test_successful_process_with_unsettled_measurement_is_rejected(tmp_path):
    seq = sequence_cases([case(15, 2)], {}, CONTRACT)[0]
    raw = result(tmp_path, 'BOBLIB_STEADY_POINT: index=1 time=1 target=0\n'
                 'BOBLIB_STEADY_POINT: index=2 time=2 target=2')
    raw['steadyStateConditionsMet'][850] = 0
    assert extract_points(seq, raw, ['accY', 'steadyStateConditionsMet'], 0.5)[0]['_status'] == 'failed'


def test_app_marks_partial_study_incomplete_after_retaining_report(monkeypatch, tmp_path):
    from types import SimpleNamespace
    from app import native_response
    from common.reporting import report_engine
    from simulations.response.mbd.steady_state import steady_state_eval_sim
    result = {'n_failed_cases': 1, 'n_cases': 2}
    reports = []
    config = tmp_path / 'study.yml'
    config.write_text('{}')
    monkeypatch.setattr(native_response, 'configure', lambda _: {'report': {'enabled': True}})
    monkeypatch.setattr(steady_state_eval_sim, 'SteadyStateEvalSim',
                        lambda _: SimpleNamespace(run=lambda: result))
    monkeypatch.setattr(report_engine, 'ReportEngine', lambda _: SimpleNamespace(build=reports.append))
    with pytest.raises(RuntimeError, match='1 of 2.*incomplete'):
        native_response.run('steady-state', config)
    assert reports == [result]
