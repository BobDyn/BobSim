"""Full-speed YMD coverage and sampled bounds must preserve missing solutions."""
from types import SimpleNamespace

import numpy as np

from simulations.envelope.ymd import parallel
from simulations.envelope.ymd.surface import lateral_moment_limits, save_limit_surface
from simulations.envelope.ymd.ymd_generation import YMDConfig, YMDResult, YMDSpeedSweepResult, summarize_ymd_speed_sweep


def test_vehicle_speed_range_is_automatic(monkeypatch, tmp_path):
    from simulations.envelope import vehicle_yaml
    monkeypatch.setattr(vehicle_yaml, "load_vehicle_yaml", lambda path: {})
    monkeypatch.setattr(vehicle_yaml, "project_vehicle_yaml", lambda data: SimpleNamespace(
        ggv=SimpleNamespace(max_drive_speed=45.)))
    calls = []
    def solve(path, config):
        calls.append(config)
        return SimpleNamespace(speed=config['speed'])
    monkeypatch.setattr(parallel, '_generate_speed', solve)
    sweep = parallel.generate_ymd_from_vehicle(tmp_path/'vehicle.yml', YMDConfig(speed=999.), workers=1)
    np.testing.assert_allclose(sweep.speeds, np.arange(5., 46., 5.))
    assert [r.speed for r in sweep.results] == list(sweep.speeds)
    assert all(c['model_dof'] == 14 for c in calls)


def test_surface_bounds_and_rejected_gap():
    ay = np.tile(np.arange(5.)[:, None], (1, 2))
    mz = np.tile([-10., 10.], (5, 1))
    valid = np.ones((5, 2), dtype=bool)
    valid[2] = False
    stations, low, high = lateral_moment_limits(ay, mz, valid, samples=9)
    np.testing.assert_allclose(stations, np.arange(0., 4.1, .5))
    assert np.isnan(low[3:6]).all()
    assert np.isnan(high[3:6]).all()
    np.testing.assert_allclose(low[[0, 1, 2, 6, 7, 8]], -10.)
    np.testing.assert_allclose(high[[0, 1, 2, 6, 7, 8]], 10.)


def test_empty_speed_retained_in_metrics_and_export(tmp_path):
    result = YMDResult(40., np.array([0., 1.]), np.array([0., 1.]),
                       np.zeros((2, 2)), np.ones((2, 2)), np.zeros((2, 2), dtype=bool))
    sweep = YMDSpeedSweepResult(np.array([40.]), [result])
    summary, rows = summarize_ymd_speed_sweep(sweep)
    assert summary['speed_sweep_max_speed_mps'] == 40.
    assert rows[0]['converged_fraction'] == 0.
    assert np.isnan(rows[0]['peak_lateral_accel_abs_g'])
    path = tmp_path/'surface.csv'
    save_limit_surface(sweep, path)
    assert '40.0,nan,nan,nan,nan,0' in path.read_text()


def test_infeasible_or_failed_trials_do_not_enter_limits(monkeypatch):
    from simulations.envelope.ymd import ymd_generation as ymd
    from dataclasses import replace
    calls = 0
    def solve(*args, **kwargs):
        nonlocal calls
        calls += 1
        if calls == 1:
            raise RuntimeError('trial equilibrium failed')
        return SimpleNamespace(success=True, state=np.zeros(28), unknowns={},
                               output=SimpleNamespace(generalized_acceleration=np.ones(14),
                                                      body_moment_nm=np.ones(3), normal_loads_n=np.ones(4)*500))
    monkeypatch.setattr(ymd, 'solve_moment_state', solve)
    cfg = replace(YMDConfig(), beta_points=2, hwa_points=2, verbose=False, warn_tire_load_range=False)
    vehicle = SimpleNamespace(steering_ratio=1., fz_min_valid=100., fz_max_valid=1800.)
    result = ymd.generate_ymd(vehicle, cfg, SimpleNamespace(dof=14), feasibility=lambda trim: False)
    assert calls == 4
    assert not result.converged.any()
    assert np.isnan(result.ay[0, 0])
    assert np.isfinite(result.ay[1, 1])
