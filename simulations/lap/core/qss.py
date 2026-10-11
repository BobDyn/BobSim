"""Speed-dependent GGV interpolation and QSS lap-time propagation."""

from __future__ import annotations

import csv
from dataclasses import dataclass
from pathlib import Path
from typing import Literal

import numpy as np
from numpy.typing import ArrayLike, NDArray

from simulations.lap.core.track import RacingLine


FloatArray = NDArray[np.float64]


@dataclass(frozen=True)
class _GGVSlice:
    speed_mps: float
    ay_mps2: FloatArray
    ax_accel_mps2: FloatArray
    ax_brake_mps2: FloatArray


@dataclass(frozen=True)
class GGVMap:
    """Speed-indexed QSS acceleration envelope used by the lap solver."""

    slices: tuple[_GGVSlice, ...]

    def __post_init__(self) -> None:
        if not self.slices:
            raise ValueError("A GGV map needs at least one speed slice.")
        speeds = np.asarray([item.speed_mps for item in self.slices])
        if np.any(np.diff(speeds) <= 0.0):
            raise ValueError("GGV speed slices must be strictly increasing.")

    @classmethod
    def from_csv(cls, path: str | Path) -> GGVMap:
        """Load the CSV written by ``GGV.save_ggv_csv``."""

        rows: dict[float, list[tuple[float, float, float]]] = {}
        with Path(path).open(newline="", encoding="utf-8") as handle:
            for row in csv.DictReader(handle):
                speed = float(row["speed_mps"])
                ay = abs(float(row["ay_mps2"]))
                rows.setdefault(speed, []).append(
                    (ay, float(row["ax_accel_mps2"]), float(row["ax_brake_mps2"]))
                )
        slices: list[_GGVSlice] = []
        for speed, raw in sorted(rows.items()):
            # Left/right rows collapse to the conservative capability at |ay|.
            grouped: dict[float, list[tuple[float, float]]] = {}
            for ay, accel, brake in raw:
                grouped.setdefault(ay, []).append((accel, brake))
            ay_values: list[float] = []
            accel_values: list[float] = []
            brake_values: list[float] = []
            for ay, values in sorted(grouped.items()):
                accel_finite = [value[0] for value in values if np.isfinite(value[0])]
                brake_finite = [value[1] for value in values if np.isfinite(value[1])]
                ay_values.append(ay)
                accel_values.append(min(accel_finite) if accel_finite else float("nan"))
                brake_values.append(max(brake_finite) if brake_finite else float("nan"))
            slices.append(
                _GGVSlice(
                    speed_mps=speed,
                    ay_mps2=np.asarray(ay_values),
                    ax_accel_mps2=np.asarray(accel_values),
                    ax_brake_mps2=np.asarray(brake_values),
                )
            )
        return cls(tuple(slices))

    @classmethod
    def from_arrays(
        cls,
        speed_mps: ArrayLike,
        ay_mps2: ArrayLike,
        ax_accel_mps2: ArrayLike,
        ax_brake_mps2: ArrayLike,
    ) -> GGVMap:
        """Construct a rectangular map, primarily for programmatic studies/tests."""

        speed = np.asarray(speed_mps, dtype=float)
        ay = np.asarray(ay_mps2, dtype=float)
        accel = np.asarray(ax_accel_mps2, dtype=float)
        brake = np.asarray(ax_brake_mps2, dtype=float)
        expected = (speed.size, ay.size)
        if accel.shape != expected or brake.shape != expected:
            raise ValueError(f"GGV acceleration arrays must have shape {expected}.")
        return cls(
            tuple(
                _GGVSlice(float(value), ay.copy(), accel[index].copy(), brake[index].copy())
                for index, value in enumerate(speed)
            )
        )

    @property
    def min_speed_mps(self) -> float:
        return self.slices[0].speed_mps

    @property
    def max_speed_mps(self) -> float:
        return self.slices[-1].speed_mps

    def longitudinal_limit(
        self,
        speed_mps: float,
        lateral_acceleration_mps2: float,
        mode: Literal["drive", "brake"],
    ) -> float:
        """Interpolate the drive or braking boundary at ``(speed, |ay|)``."""

        values = np.asarray(
            [
                _slice_longitudinal_limit(item, abs(lateral_acceleration_mps2), mode)
                for item in self.slices
            ],
            dtype=float,
        )
        speeds = np.asarray([item.speed_mps for item in self.slices], dtype=float)
        finite = np.isfinite(values)
        if not np.any(finite):
            return float("nan")
        return float(np.interp(speed_mps, speeds[finite], values[finite]))

    def lateral_limit(self, speed_mps: float) -> float:
        """Interpolate maximum sustainable absolute lateral acceleration."""

        limits = np.asarray([_slice_lateral_limit(item) for item in self.slices])
        speeds = np.asarray([item.speed_mps for item in self.slices])
        return float(np.interp(speed_mps, speeds, limits))


@dataclass(frozen=True)
class QSSLapResult:
    """QSS speed and acceleration history around one closed racing line."""

    line: RacingLine
    speed_mps: FloatArray
    longitudinal_acceleration_mps2: FloatArray
    lateral_acceleration_mps2: FloatArray
    segment_time_s: FloatArray
    lap_time_s: float
    converged: bool
    sweeps: int


def solve_qss_lap(
    line: RacingLine,
    ggv: GGVMap,
    *,
    max_speed_mps: float | None = None,
    max_sweeps: int = 200,
    tolerance_mps: float = 1e-5,
) -> QSSLapResult:
    """Solve a closed-lap speed profile with alternating forward/backward passes."""

    speed_ceiling = min(
        ggv.max_speed_mps,
        float(max_speed_mps) if max_speed_mps is not None else ggv.max_speed_mps,
    )
    speed = np.asarray(
        [_corner_speed_limit(abs(kappa), ggv, speed_ceiling) for kappa in line.curvature_per_m]
    )
    converged = False
    completed_sweeps = 0
    count = speed.size
    for sweep in range(1, max_sweeps + 1):
        previous = speed.copy()
        for index in range(count):
            next_index = (index + 1) % count
            ay = speed[index] ** 2 * abs(line.curvature_per_m[index])
            ax = ggv.longitudinal_limit(speed[index], ay, "drive")
            if np.isfinite(ax):
                reachable = np.sqrt(max(speed[index] ** 2 + 2.0 * max(ax, 0.0) * line.segment_length_m[index], 0.0))
                speed[next_index] = min(speed[next_index], reachable, speed_ceiling)
        for index in range(count - 1, -1, -1):
            next_index = (index + 1) % count
            ay_next = speed[next_index] ** 2 * abs(line.curvature_per_m[next_index])
            ax_brake = ggv.longitudinal_limit(speed[next_index], ay_next, "brake")
            if np.isfinite(ax_brake):
                reachable = np.sqrt(
                    max(speed[next_index] ** 2 + 2.0 * max(-ax_brake, 0.0) * line.segment_length_m[index], 0.0)
                )
                speed[index] = min(speed[index], reachable, speed_ceiling)
        completed_sweeps = sweep
        if float(np.max(np.abs(speed - previous))) <= tolerance_mps:
            converged = True
            break

    next_speed = np.roll(speed, -1)
    ds = line.segment_length_m
    segment_time = 2.0 * ds / np.maximum(speed + next_speed, 1e-6)
    ax = (next_speed**2 - speed**2) / np.maximum(2.0 * ds, 1e-9)
    ay = speed**2 * line.curvature_per_m
    return QSSLapResult(
        line=line,
        speed_mps=speed,
        longitudinal_acceleration_mps2=ax,
        lateral_acceleration_mps2=ay,
        segment_time_s=segment_time,
        lap_time_s=float(np.sum(segment_time)),
        converged=converged,
        sweeps=completed_sweeps,
    )


def _slice_longitudinal_limit(
    item: _GGVSlice,
    ay_mps2: float,
    mode: Literal["drive", "brake"],
) -> float:
    values = item.ax_accel_mps2 if mode == "drive" else item.ax_brake_mps2
    finite = np.isfinite(item.ay_mps2) & np.isfinite(values)
    if not np.any(finite):
        return float("nan")
    ay = item.ay_mps2[finite]
    boundary = values[finite]
    if ay_mps2 > float(np.max(ay)) + 1e-9:
        return float("nan")
    return float(np.interp(ay_mps2, ay, boundary))


def _slice_lateral_limit(item: _GGVSlice) -> float:
    finite = np.isfinite(item.ax_accel_mps2) | np.isfinite(item.ax_brake_mps2)
    if not np.any(finite):
        return 0.0
    return float(np.max(item.ay_mps2[finite]))


def _corner_speed_limit(curvature_per_m: float, ggv: GGVMap, ceiling_mps: float) -> float:
    if curvature_per_m <= 1e-10:
        return ceiling_mps
    lo = 0.1
    hi = ceiling_mps
    for _ in range(40):
        midpoint = 0.5 * (lo + hi)
        required_ay = midpoint**2 * curvature_per_m
        if required_ay <= ggv.lateral_limit(midpoint):
            lo = midpoint
        else:
            hi = midpoint
    return lo
