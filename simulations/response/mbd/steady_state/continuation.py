"""Orchestrate accepted Modelica points without restarting the vehicle plant."""
from __future__ import annotations

import json
from pathlib import Path
import re

import numpy as np

from simulations.response.mbd.measurement import window_statistics

POINT_EVENT = re.compile(
    r"BOBLIB_STEADY_POINT: index=(\d+) time=([^\s]+) target=([^\s]+)"
)


def sequence_cases(cases: list[dict], simulation: dict, defaults: dict) -> list[dict]:
    """Group ordered cases by speed and prepend a zero-Ay conditioning hold.

    Parameters
    ----------
    cases : list of dict
        Independent point specifications; order within a speed is preserved.
    simulation : dict
        Settings including optional sequence wall timeout.
    defaults : dict
        Compiled parameter contract, required to support the sequence explicitly.

    Returns
    -------
    list of dict
        One native process request per speed, with original point metadata.
    """
    required = {"enableSteadyStateSequence", "steadyStatePointCount", "steadyStateTargets[64]"}
    if not required.issubset(defaults):
        raise ValueError("Rebuild BobLib with the steady-state sequence contract before using continuation.")
    grouped: dict[float, list[dict]] = {}
    for case in cases:
        grouped.setdefault(float(case['_testVel']), []).append(case)
    sequences = []
    for speed, points in grouped.items():
        if len(points) > 63:
            raise ValueError("A continuation run supports at most 63 requested points plus conditioning.")
        targets = [0.0, *(float(point['_testAy']) for point in points)]
        if not np.all(np.isfinite(targets)):
            raise ValueError("Continuation targets must be finite.")
        sequence = dict(points[0])
        sequence.update(_mode='steady_ay_sequence', _testVel=speed,
                        _sequence_cases=points, enableSteadyStateSequence=True,
                        steadyStatePointCount=len(targets))
        sequence.pop('_testAy', None)
        for index, target in enumerate(targets, 1):
            sequence[f'steadyStateTargets[{index}]'] = target
        # A physical stop bound for the entire process, not a per-point clock reset.
        start = float(sequence.get('startTime', 0))
        sequence['stopTime'] = start + len(targets)*(float(sequence['stopTime']) - start)
        if 'sequence_timeout_s' in simulation:
            timeout = float(simulation['sequence_timeout_s'])
            if not np.isfinite(timeout) or timeout <= 0:
                raise ValueError("sequence_timeout_s must be finite and positive.")
            sequence['_timeout_s'] = timeout
        sequences.append(sequence)
    return sequences


def extract_points(sequence: dict, result: dict, signals: list[str], duration: float) -> list[dict]:
    """Extract only explicitly accepted points, retaining incomplete-point failures.

    Parameters
    ----------
    sequence : dict
        Native sequence request with its original independent cases.
    result : dict
        Raw native output and the retained run-log path.
    signals : list of str
        Signals required by the steady-state report.
    duration : float
        Complete measurement-window duration in seconds.

    Returns
    -------
    list of dict
        One accepted or failed report row for every requested point.
    """
    requested = sequence['_sequence_cases']
    events: dict[int, dict] = {}
    error = result.get('_error', '')
    if result.get('_status') != 'failed':
        log = Path(result['_log_file']).read_text(errors='replace')
        previous_time = -np.inf
        for index_text, time_text, target_text in POINT_EVENT.findall(log):
            index, time, target = int(index_text), float(time_text), float(target_text)
            if (index != len(events) + 1 or not np.isfinite(time + target) or time <= previous_time or
                    index > len(requested) + 1 or
                    not np.isclose(target, sequence[f'steadyStateTargets[{index}]'], rtol=0, atol=1e-10)):
                raise ValueError("Invalid or out-of-order Modelica sequence acceptance record.")
            events[index] = {'kind': 'sequence_point', 'index': index, 'time': time, 'target': target}
            previous_time = time
    rows = []
    for index, case in enumerate(requested, 2):
        row = {key: value for key, value in case.items() if key.startswith('_')}
        row.update({key: result[key] for key in ('_run_dir', '_log_file', '_result_file',
                                                '_termination_message', '_termination_time') if key in result})
        row['_sequence_index'] = index
        event = events.get(index)
        if event is None:
            row.update(_status='failed',
                       _error=error or 'Sequence ended before this point completed its settling hold.')
        else:
            try:
                t = np.asarray(result['time'], dtype=float)
                # Do not include the post-event sample after advancing to a new target.
                before = t < event['time']
                selected_time = t[before]
                if len(selected_time) < 2 or event['time'] - selected_time[-1] > min(0.01, duration/10):
                    raise ValueError('No output sufficiently close to the acceptance event; increase output sampling.')
                stats = {key: window_statistics(selected_time, np.asarray(result[key])[before], duration)
                         for key in signals}
                if stats['steadyStateConditionsMet']['minimum'] < 0.5:
                    raise ValueError('Measurement window includes unsettled samples.')
                row.update({key: stat['mean'] for key, stat in stats.items()})
                row['steadyStateConditionsMet'] = 1.0
                row.update(_status='ok', _acceptance_event=event,
                           _measurement={'duration_s': duration, 'end_time': float(selected_time[-1]),
                                         'signals': stats})
            except (ValueError, KeyError) as exc:
                row.update(_status='failed', _error=str(exc))
        rows.append(row)
    if result.get('_run_dir'):
        (Path(result['_run_dir']) / 'sequence_points.json').write_text(json.dumps(rows, indent=2))
    return rows
