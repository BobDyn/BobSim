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
    monkeypatch.setattr(parallel, "automatic_vehicle_speed_grid", lambda _: config.speeds)
    monkeypatch.setattr(parallel.os, "cpu_count", lambda: 2)
    spawned = parallel.generate_ggv_from_vehicle(ROOT / "vehicle.yml", config)
    assert [envelope.speed for envelope in spawned] == list(config.speeds)
    for actual, expected in zip(spawned, serial):
        np.testing.assert_allclose(actual.ay, expected.ay, atol=1e-6, rtol=0)
        np.testing.assert_allclose(actual.ax_accel, expected.ax_accel, atol=1e-5, rtol=0)
        np.testing.assert_allclose(actual.ax_brake, expected.ax_brake, atol=1e-5, rtol=0)


def test_single_cpu_does_not_spawn(monkeypatch):
    set_projected_limit(monkeypatch, 5.)
    monkeypatch.setattr(parallel.os, "cpu_count", lambda: 1)
    def unexpected_pool(*args, **kwargs):
        pytest.fail("One CPU must use the serial worker.")

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


@pytest.mark.parametrize("maximum", [0.5, 9., 42.054, 100.])
def test_automatic_speed_grid_covers_vehicle(maximum):
    speeds = parallel.automatic_vehicle_speed_grid(maximum)
    assert len(speeds) == 9
    assert speeds[-1] == maximum
    assert 0. < speeds[0] < maximum
    np.testing.assert_allclose(np.diff((0., *speeds)), maximum / 9)


@pytest.mark.parametrize("maximum", [float("inf"), float("nan"), 0., -1.])
def test_speed_grid_rejects_unknown_limits(maximum):
    with pytest.raises(ValueError):
        parallel.automatic_vehicle_speed_grid(maximum)


def test_file_workflow_ignores_saved_speed_grid(monkeypatch):
    set_projected_limit(monkeypatch, 45.)
    monkeypatch.setattr(parallel.os, "cpu_count", lambda: 1)
    captured = []
    monkeypatch.setattr(parallel, "_generate_speed", lambda path, config: captured.append(config) or [])
    for speeds in ((5., 10.), (100.,), ()):
        parallel.generate_ggv_from_vehicle(ROOT / "vehicle.yml", GGVConfig(speeds=speeds))
    assert all(config["speeds"] == (5., 10., 15., 20., 25., 30., 35., 40., 45.) for config in captured)


def test_app_envelope_settings_only_expose_model_choice():
    from app.registry import BASE_CONFIG_SPECS

    ggv = BASE_CONFIG_SPECS["ggv"]
    assert [field.path for field in ggv.fields] == [("generation", "model_dof")]
    assert BASE_CONFIG_SPECS["lap-qss"].fields == ()
    assert [field.path for field in BASE_CONFIG_SPECS["lap-transient"].fields if field.path[0] == "qss"] == [
        ("qss", "regenerate"),
    ]
