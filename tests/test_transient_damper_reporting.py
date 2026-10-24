from copy import deepcopy
from pathlib import Path

import matplotlib.pyplot as plt
import numpy as np
import pytest
import yaml

from common import vehicle_io
from common.damper_curves import resolve_damper_curve, vehicle_damper_provenance
from common.plotting.plot_engine import PlotEngine
from simulations.response.mbd.transient.transient_eval_sim import TransientEvalSim


ROOT = Path(__file__).resolve().parents[1]


def _report_sim(tmp_path):
    config = vehicle_io.load_yaml(
        ROOT / 'simulations/response/mbd/transient/transient_eval_config.yml'
    )
    config['report']['metrics_csv_path'] = str(tmp_path / 'metrics.csv')
    sim = TransientEvalSim.__new__(TransientEvalSim)
    sim.config = config
    return sim


def _step_result(curves):
    time = np.linspace(0, 5, 501)
    response = 1 - np.exp(-np.maximum(time - 1, 0) / 0.25)
    result = {
        'time': time, 'testVel': 15.0, 'mode': 'step', 'direction': 'left',
        'stepTime': 1.0, 'steerStep_deg': 5.0,
        'handwheelAngle': np.where(time >= 1, np.deg2rad(5), 0),
        'accY': response * 3, 'yawVel': response * 0.2,
        'roll': response * 0.01, 'sideslip': response * 0.002,
        '_damper_curves': curves,
    }
    for index, axle in enumerate(('front', 'front', 'rear', 'rear'), 1):
        speed = np.sin(time) * 0.1
        result[f'chassis.damperCompressionVelocity[{index}]'] = speed
        table = curves[axle]['table']
        result[f'chassis.damperForce[{index}]'] = np.interp(
            speed, [row[0] for row in table], [row[1] for row in table]
        )
    return result


def test_transient_reference_uses_captured_curve_after_yaml_changes(tmp_path, monkeypatch):
    sim = _report_sim(tmp_path)
    vehicle = vehicle_io.load_yaml(ROOT / 'vehicle.yml')
    captured = vehicle_damper_provenance(vehicle)
    result = _step_result(captured)

    # The running study used C6. The user saves C10 before report generation.
    vehicle['front']['actuation']['shock']['damper']['compression']['low_speed_clicks_from_closed'] = 10
    yaml_path = tmp_path / 'vehicle.yml'
    yaml_path.write_text(yaml.safe_dump(vehicle), encoding='utf-8')
    monkeypatch.setattr(vehicle_io, 'repo_root', lambda: tmp_path)
    assert resolve_damper_curve(vehicle['front']['actuation']['shock']).table != captured['front']['table']

    report = sim.summarize([result])
    assert report['damper_reference_notes'] == []
    for axle in ('front', 'rear'):
        table = np.asarray(captured[axle]['table'])
        np.testing.assert_array_equal(report['series'][f'damper_reference_speed_{axle}'], table[:, 0])
        np.testing.assert_array_equal(report['series'][f'damper_reference_force_{axle}'], table[:, 1])

    # Reprocessing results must not require the original YAML to exist.
    yaml_path.unlink()
    again = sim.summarize([result])
    np.testing.assert_array_equal(
        again['series']['damper_reference_force_front'],
        report['series']['damper_reference_force_front'],
    )


@pytest.mark.parametrize('provenance', ['missing', 'mixed'])
def test_transient_omits_unknown_reference_but_keeps_simulated_samples(tmp_path, provenance):
    sim = _report_sim(tmp_path)
    vehicle = vehicle_io.load_yaml(ROOT / 'vehicle.yml')
    captured = vehicle_damper_provenance(vehicle)
    first = _step_result(captured)
    if provenance == 'missing':
        first.pop('_damper_curves')
        results = [first]
    else:
        changed = deepcopy(vehicle)
        changed['front']['actuation']['shock']['damper']['compression']['low_speed_clicks_from_closed'] = 10
        results = [first, _step_result(vehicle_damper_provenance(changed))]

    with pytest.warns(RuntimeWarning, match='Damper reference overlays omitted'):
        report = sim.summarize(results)
    assert report['damper_reference_notes']
    assert report['series']['damper_reference_speed_front'].size == 0
    assert report['series']['damper_reference_force_front'].size == 0
    np.testing.assert_array_equal(
        report['series']['damper_speed_fl'][15.0], first['chassis.damperCompressionVelocity[1]']
    )

    config = {'plots': {'damper_force_speed': sim.config['plots']['damper_force_speed']}}
    figures = list(PlotEngine(config).render(report))
    try:
        # The front-left plot still contains the actual simulated samples.
        assert len(figures) == 1
        assert len(figures[0][1].axes[0].lines) == 1
    finally:
        for _, figure in figures:
            plt.close(figure)
