from __future__ import annotations

from types import SimpleNamespace

import numpy as np

from simulations.lap.core.track import TrackCorridor
from simulations.lap.validation_visuals import _write_lap_figures


def test_validation_visuals_render_corner_kinematic_histories(tmp_path) -> None:
    sample_count = 7
    time = np.linspace(0.0, 0.6, sample_count)
    station = np.linspace(0.0, 6.0, sample_count)
    zeros = np.zeros(sample_count)
    state = np.zeros((sample_count, 12))
    state[:, 0] = station

    signals = {
        "velX": np.full(sample_count, 10.0),
        "velY": zeros,
        "yawVel": zeros,
        "handwheelAngle": zeros,
        "accX": zeros,
        "accY": zeros,
        "z": zeros,
        "roll": zeros,
        "pitch": zeros,
    }
    for corner_index, corner in enumerate(("FL", "FR", "RL", "RR"), start=1):
        phase = corner_index * 0.2
        signals[f"jounce{corner}"] = 0.01 * np.sin(time + phase)
        signals[f"jounceVel{corner}"] = 0.01 * np.cos(time + phase)
        signals[f"camber{corner}"] = 0.02 * np.sin(time + phase)
        signals[f"toe{corner}"] = 0.002 * np.sin(time + phase)

    line = SimpleNamespace(
        track_length_m=10.0,
        x_m=station,
        y_m=zeros,
        station_m=station,
        curvature_per_m=zeros,
    )
    qss = SimpleNamespace(
        line=line,
        speed_mps=np.full(sample_count, 10.0),
        longitudinal_acceleration_mps2=zeros,
        lateral_acceleration_mps2=zeros,
    )
    transient = SimpleNamespace(
        transient=SimpleNamespace(time_s=time, state=state, signals=signals),
        station_m=station,
        unwrapped_progress_m=station,
        target_speed_mps=np.full(sample_count, 10.0),
        lateral_error_m=zeros,
        heading_error_rad=zeros,
    )
    corridor = TrackCorridor(
        np.column_stack((station, np.ones(sample_count))),
        np.column_stack((station, -np.ones(sample_count))),
    )

    _write_lap_figures(tmp_path, corridor, qss, transient, 6)

    for name in (
        "transient_suspension_jounce.png",
        "transient_suspension_jounce_rate.png",
        "transient_wheel_kinematics.png",
    ):
        figure = tmp_path / "transient" / name
        assert figure.is_file()
        assert figure.stat().st_size > 0
