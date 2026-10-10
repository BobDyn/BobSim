"""CSV serialization for QSS and transient lap results."""

from __future__ import annotations

import csv
from pathlib import Path

import numpy as np

from simulations.lap.core.qss import QSSLapResult
from simulations.lap.core.transient import TransientLapResult


def write_qss_lap_csv(path: str | Path, result: QSSLapResult) -> None:
    """Write the path, speed profile, and acceleration history."""

    output = Path(path)
    output.parent.mkdir(parents=True, exist_ok=True)
    with output.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.writer(handle)
        writer.writerow(
            (
                "station_m",
                "x_m",
                "y_m",
                "curvature_per_m",
                "speed_mps",
                "ax_mps2",
                "ay_mps2",
                "dt_s",
            )
        )
        for values in zip(
            result.line.station_m,
            result.line.x_m,
            result.line.y_m,
            result.line.curvature_per_m,
            result.speed_mps,
            result.longitudinal_acceleration_mps2,
            result.lateral_acceleration_mps2,
            result.segment_time_s,
        ):
            writer.writerow(tuple(float(value) for value in values))


def write_transient_lap_csv(path: str | Path, result: TransientLapResult) -> None:
    """Write time, path-relative channels, controls, and body response."""

    output = Path(path)
    output.parent.mkdir(parents=True, exist_ok=True)
    with output.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.writer(handle)
        writer.writerow(
            (
                "time_s",
                "x_m",
                "y_m",
                "station_m",
                "progress_m",
                "lateral_error_m",
                "heading_error_rad",
                "target_speed_mps",
                "speed_mps",
                "yaw_rate_radps",
                "steering_rad",
                "ax_mps2",
                "ay_mps2",
            )
        )
        speed = np.hypot(
            result.transient.signals["velX"],
            result.transient.signals["velY"],
        )
        for values in zip(
            result.transient.time_s,
            result.transient.state[:, 0],
            result.transient.state[:, 1],
            result.station_m,
            result.unwrapped_progress_m,
            result.lateral_error_m,
            result.heading_error_rad,
            result.target_speed_mps,
            speed,
            result.transient.signals["yawVel"],
            result.transient.signals["handwheelAngle"],
            result.transient.signals["accX"],
            result.transient.signals["accY"],
        ):
            writer.writerow(tuple(float(value) for value in values))
