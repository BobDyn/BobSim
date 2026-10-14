"""Independent GGV slices preserve serial output and error handling."""

from pathlib import Path

import numpy as np
import pytest

from simulations.envelope.ggv.ggv_generation import GGVConfig
from simulations.envelope.ggv import parallel


ROOT = Path(__file__).resolve().parents[1]


def test_spawned_speed_slices_match_serial_in_configured_order(monkeypatch):
    config = GGVConfig(
        speeds=(12., 5.), ay_points=5, ay_max_g=4.5,
        trim_multistart=False, verbose=False, warn_tire_load_range=False,
    )
    monkeypatch.setattr(parallel.os, "cpu_count", lambda: 1)
    serial = parallel.generate_ggv_from_vehicle(ROOT / "vehicle.yml", config)
    monkeypatch.setattr(parallel.os, "cpu_count", lambda: 2)
    spawned = parallel.generate_ggv_from_vehicle(ROOT / "vehicle.yml", config)
    assert [envelope.speed for envelope in spawned] == list(config.speeds)
    for actual, expected in zip(spawned, serial):
        np.testing.assert_allclose(actual.ay, expected.ay, atol=1e-6, rtol=0)
        np.testing.assert_allclose(actual.ax_accel, expected.ax_accel, atol=1e-5, rtol=0)
        np.testing.assert_allclose(actual.ax_brake, expected.ax_brake, atol=1e-5, rtol=0)


def test_single_speed_does_not_spawn(monkeypatch):
    def unexpected_pool(*args, **kwargs):
        pytest.fail("One speed must use the serial worker.")

    expected = []
    monkeypatch.setattr(parallel, "ProcessPoolExecutor", unexpected_pool)
    monkeypatch.setattr(parallel, "_generate_speed", lambda *args: expected)
    assert parallel.generate_ggv_from_vehicle(ROOT / "vehicle.yml", GGVConfig(speeds=(5.,))) is expected


def test_worker_failure_propagates(tmp_path, monkeypatch):
    monkeypatch.setattr(parallel.os, "cpu_count", lambda: 2)
    with pytest.raises(FileNotFoundError):
        parallel.generate_ggv_from_vehicle(
            tmp_path / "missing.yml", GGVConfig(speeds=(5., 12.), verbose=False),
        )
