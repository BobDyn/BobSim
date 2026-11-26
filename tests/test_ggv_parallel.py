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
    monkeypatch.setattr(parallel, "_generate_speed", lambda path, config, *_: captured.append(config) or [])
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


def test_lap_slices_match_serial_lap_solve_exactly(monkeypatch):
    from dataclasses import replace

    from engines.dynpy import Vehicle
    from simulations.envelope.ggv.ggv_generation import generate_ggv
    from simulations.envelope.vehicle_yaml import load_vehicle_yaml, project_vehicle_yaml

    # The lap caps both the envelope parameters and the DynPy vehicle at the event power.
    path = ROOT / "vehicle.yml"
    capped = Vehicle.from_yaml(path).with_power_limit(32000.)
    projected = project_vehicle_yaml(load_vehicle_yaml(path)).ggv
    vehicle = replace(projected, max_drive_power=min(projected.max_drive_power,
                                                     capped.parameters.peak_drive_power_w))
    config = GGVConfig(
        speeds=(12., 5.), ay_points=3, ay_max_g=4.5,
        trim_multistart=False, verbose=False, warn_tire_load_range=False,
    )
    serial = generate_ggv(vehicle, config, reduced_model=capped.model(config.model_dof))
    monkeypatch.setattr(parallel.os, "cpu_count", lambda: 2)
    spawned = parallel.generate_ggv_speeds(path, config, vehicle=vehicle, drive_power_limit_w=32000.)
    assert [envelope.speed for envelope in spawned] == list(config.speeds)
    for actual, expected in zip(spawned, serial, strict=True):
        for field in ("ay", "ax_accel", "ax_brake"):
            np.testing.assert_array_equal(getattr(actual, field), getattr(expected, field))


@pytest.mark.parametrize(("cpus", "speeds", "expected"), [
    (4, 9, 4), (8, 9, 4), (2, 9, 2), (None, 9, 1), (4, 3, 3), (4, 1, 1), (4, 0, 1),
])
def test_worker_count_caps_at_slices_cpus_and_four(monkeypatch, cpus, speeds, expected):
    monkeypatch.setattr(parallel.os, "cpu_count", lambda: cpus)
    assert parallel.ggv_worker_count(speeds) == expected


def test_slices_reach_pool_with_worker_count_and_lap_inputs(monkeypatch):
    pools = []

    class Pool:
        def __init__(self, max_workers, mp_context):
            pools.append((max_workers, mp_context.get_start_method()))

        def __enter__(self):
            return self

        def __exit__(self, *args):
            return False

        map = staticmethod(map)

    calls = []

    def solve(path, config, vehicle, limit):
        calls.append((path, config["speeds"], vehicle, limit))
        return [SimpleNamespace(speed=speed) for speed in config["speeds"]]

    monkeypatch.setattr(parallel, "ProcessPoolExecutor", Pool)
    monkeypatch.setattr(parallel, "_generate_speed", solve)
    monkeypatch.setattr(parallel.os, "cpu_count", lambda: 3)
    marker = object()
    speeds = (20., 5., 15., 10.)
    result = parallel.generate_ggv_speeds(
        ROOT / "vehicle.yml", GGVConfig(speeds=speeds, verbose=False),
        vehicle=marker, drive_power_limit_w=32000.,
    )
    assert pools == [(3, "spawn")]
    assert [envelope.speed for envelope in result] == list(speeds)
    assert calls == [((ROOT / "vehicle.yml").resolve().as_posix(), (speed,), marker, 32000.) for speed in speeds]

    monkeypatch.setattr(parallel.os, "cpu_count", lambda: 1)
    calls.clear()
    parallel.generate_ggv_speeds(ROOT / "vehicle.yml", GGVConfig(speeds=speeds, verbose=False),
                                 vehicle=marker, drive_power_limit_w=None)
    assert pools == [(3, "spawn")]
    assert calls == [((ROOT / "vehicle.yml").resolve().as_posix(), speeds, marker, None)]
