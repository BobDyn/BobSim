"""Independent GGV slices preserve serial output and error handling."""

from dataclasses import asdict
from pathlib import Path
from types import SimpleNamespace

import numpy as np
import pytest

from simulations.envelope.ggv.ggv_generation import GGVConfig
from simulations.envelope.ggv import parallel


ROOT = Path(__file__).resolve().parents[1]


def set_projected_limit(monkeypatch, speed):
    from simulations.envelope import vehicle_yaml

    monkeypatch.setattr(vehicle_yaml, "project_vehicle_yaml",
                        lambda _: SimpleNamespace(ggv=SimpleNamespace(max_drive_speed=speed)))


def test_spawned_speed_slices_match_serial_in_configured_order(monkeypatch):
    config = GGVConfig(
        speeds=(12., 5.), ay_points=5, ay_max_g=4.5,
        trim_multistart=False, verbose=False, warn_tire_load_range=False,
    )
    monkeypatch.setattr(parallel.os, "cpu_count", lambda: 1)
    serial = parallel._generate_speed((ROOT / "vehicle.yml").as_posix(), asdict(config))
    set_projected_limit(monkeypatch, 12.)
    monkeypatch.setattr(parallel.os, "cpu_count", lambda: 2)
    spawned = parallel.generate_ggv_from_vehicle(ROOT / "vehicle.yml", config)
    assert [envelope.speed for envelope in spawned] == list(config.speeds)
    for actual, expected in zip(spawned, serial):
        np.testing.assert_allclose(actual.ay, expected.ay, atol=1e-6, rtol=0)
        np.testing.assert_allclose(actual.ax_accel, expected.ax_accel, atol=1e-5, rtol=0)
        np.testing.assert_allclose(actual.ax_brake, expected.ax_brake, atol=1e-5, rtol=0)


def test_single_speed_does_not_spawn(monkeypatch):
    set_projected_limit(monkeypatch, 5.)
    def unexpected_pool(*args, **kwargs):
        pytest.fail("One speed must use the serial worker.")

    expected = []
    monkeypatch.setattr(parallel, "ProcessPoolExecutor", unexpected_pool)
    monkeypatch.setattr(parallel, "_generate_speed", lambda *args: expected)
    assert parallel.generate_ggv_from_vehicle(ROOT / "vehicle.yml", GGVConfig(speeds=(5.,))) is expected


def test_worker_failure_propagates(tmp_path, monkeypatch):
    from simulations.envelope import vehicle_yaml

    set_projected_limit(monkeypatch, 12.)
    monkeypatch.setattr(vehicle_yaml, "load_vehicle_yaml", lambda _: {})
    monkeypatch.setattr(parallel.os, "cpu_count", lambda: 2)
    with pytest.raises(FileNotFoundError):
        parallel.generate_ggv_from_vehicle(
            tmp_path / "missing.yml", GGVConfig(speeds=(5., 12.), verbose=False),
        )


@pytest.mark.parametrize("speeds, maximum, expected", [
    ((5., 10., 15., 20., 25.), 42.054, (5., 10., 15., 20., 25., 30., 35., 40., 42.054)),
    ((10., 5., 10.), 20., (10., 5., 10., 15., 20.)),
    ((5., 12.), 12., (5., 12.)),
    ((12., 5.), 10., (12., 5.)),
    ((5.,), 12., (5., 12.)),
])
def test_speed_grid_preserves_samples_and_covers_vehicle(speeds, maximum, expected):
    assert parallel.vehicle_speed_grid(speeds, maximum) == expected


@pytest.mark.parametrize("speeds, maximum", [
    ((), 12.), ((0.,), 12.), ((float("nan"),), 12.),
    ((5.,), float("inf")), ((5.,), 0.),
])
def test_speed_grid_rejects_unknown_limits_and_invalid_samples(speeds, maximum):
    with pytest.raises(ValueError):
        parallel.vehicle_speed_grid(speeds, maximum)


def test_file_workflow_extends_grid_before_dispatch(monkeypatch):
    set_projected_limit(monkeypatch, 22.)
    monkeypatch.setattr(parallel.os, "cpu_count", lambda: 1)
    captured = []
    monkeypatch.setattr(parallel, "_generate_speed", lambda path, config: captured.append(config) or [])
    parallel.generate_ggv_from_vehicle(ROOT / "vehicle.yml", GGVConfig(speeds=(5., 10.)))
    assert captured[0]["speeds"] == (5., 10., 15., 20., 22.)
