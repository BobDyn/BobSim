from pathlib import Path

import numpy as np
import pytest
import yaml

from simulations.response.maneuver import mbd_config, steering_degrees, validate_maneuver

ROOT = Path(__file__).resolve().parents[1]


@pytest.fixture
def settings():
    return yaml.safe_load((ROOT / 'simulations/response/maneuver_config.yml').read_text())


@pytest.mark.parametrize('kind', ['ramp', 'step', 'sine'])
def test_waveform_timing_and_magnitude(settings, kind):
    settings.update(maneuver=kind, amplitude_deg=-6., start_time_s=2., ramp_duration_s=3.,
                    rise_time_s=.02, frequency_hz=2.)
    validate_maneuver(settings)
    assert steering_degrees(0., settings) == 0.
    assert steering_degrees(2., settings) == 0.
    if kind == 'sine':
        assert steering_degrees(2.125, settings) == pytest.approx(-6.)
        assert steering_degrees(2.375, settings) == pytest.approx(6.)
    else:
        duration = settings['ramp_duration_s'] if kind == 'ramp' else settings['rise_time_s']
        assert steering_degrees(2. + duration / 2., settings) == pytest.approx(-3.)
        assert steering_degrees(20., settings) == -6.


@pytest.mark.parametrize('values', [dict(maneuver='unknown'), dict(start_time_s=10.),
    dict(amplitude_deg=float('nan')), dict(ramp_duration_s=0.), dict(speed_mps=-1.),
    dict(maneuver='sine', frequency_hz=100.)])
def test_invalid_maneuver(settings, values):
    settings.update(values)
    with pytest.raises(ValueError):
        validate_maneuver(settings)


@pytest.mark.parametrize('kind', ['ramp', 'step', 'sine'])
@pytest.mark.parametrize('amplitude', [-8., 8.])
def test_mbd_waveform_mapping(settings, kind, amplitude):
    from simulations.response.mbd.transient.transient_eval_sim import TransientEvalSim
    settings.update(maneuver=kind, amplitude_deg=amplitude, start_time_s=2., ramp_duration_s=3.)
    seed = yaml.safe_load((ROOT / 'simulations/response/mbd/transient/transient_eval_config.yml').read_text())
    config = mbd_config(settings, seed)
    simulator = object.__new__(TransientEvalSim)
    simulator.config = config
    cases, metadata = simulator.build_cases()
    selected = [(case, meta) for case, meta in zip(cases, metadata)
                if (meta['mode'] == 'continuous_sine') == (kind == 'sine')]
    assert len(selected) == 1
    case, metadata = selected[0]
    assert metadata['directionSign'] == (1 if amplitude > 0 else -1)
    assert case['steerStart'] == 2.
    assert case['targetVel'] == settings['speed_mps']
    if kind == 'sine':
        assert case['steerAmp'] == pytest.approx(np.deg2rad(amplitude))
        assert case['steerFreq'] == settings['frequency_hz']
    else:
        assert case['frRampSteerHeight'] == pytest.approx(np.deg2rad(amplitude))
        duration = 3. if kind == 'ramp' else settings['rise_time_s']
        # StandardVCU derives stepDuration from frRampSteerDuration, so only the latter is an override.
        assert case['frRampSteerDuration'] == duration
        assert 'stepDuration' not in case
        assert metadata['stepDuration'] == duration
    assert config['simulation']['stop_time'] == settings['stop_time_s']
    assert config['test']['analyze_cycles_after'] == seed['test']['analyze_cycles_after']
