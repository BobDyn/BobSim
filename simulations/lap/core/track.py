"""Track-corridor and racing-line geometry shared by QSS and transient laps."""

from __future__ import annotations

import csv
from dataclasses import dataclass
from pathlib import Path

import numpy as np
from numpy.typing import ArrayLike, NDArray
from scipy.interpolate import CubicSpline


FloatArray = NDArray[np.float64]


@dataclass(frozen=True)
class RacingLine:
    """Closed, arc-length-sampled path constructed inside a track corridor."""

    station_m: FloatArray
    x_m: FloatArray
    y_m: FloatArray
    heading_rad: FloatArray
    curvature_per_m: FloatArray
    segment_length_m: FloatArray
    gate_offsets_m: FloatArray
    track_length_m: float

    @property
    def points(self) -> FloatArray:
        return np.column_stack((self.x_m, self.y_m))

    def nearest_index(self, x_m: float, y_m: float) -> int:
        delta = self.points - np.array([x_m, y_m], dtype=float)
        return int(np.argmin(np.einsum("ij,ij->i", delta, delta)))

    def index_at_station(self, station_m: float) -> int:
        wrapped = float(station_m % self.track_length_m)
        return int(np.argmin(np.abs(self.station_m - wrapped)))

    def project_station_m(self, x_m: float, y_m: float) -> float:
        """Project a point onto the nearest sampled path segment continuously."""

        starts = self.points
        ends = np.roll(starts, -1, axis=0)
        segment = ends - starts
        relative = np.array([x_m, y_m], dtype=float) - starts
        denominator = np.einsum("ij,ij->i", segment, segment)
        fraction = np.clip(
            np.einsum("ij,ij->i", relative, segment)
            / np.maximum(denominator, 1e-12),
            0.0,
            1.0,
        )
        closest = starts + fraction[:, None] * segment
        delta = np.array([x_m, y_m], dtype=float) - closest
        index = int(np.argmin(np.einsum("ij,ij->i", delta, delta)))
        return float(
            (self.station_m[index] + fraction[index] * self.segment_length_m[index])
            % self.track_length_m
        )

    def interpolate(self, values: ArrayLike, station_m: float) -> float:
        """Periodically interpolate one path-sampled scalar at a station."""

        samples = np.asarray(values, dtype=float)
        if samples.shape != self.station_m.shape:
            raise ValueError("Interpolated values must match the racing-line samples.")
        wrapped = float(station_m % self.track_length_m)
        return float(
            np.interp(
                wrapped,
                np.append(self.station_m, self.track_length_m),
                np.append(samples, samples[0]),
            )
        )

    def heading_at_station(self, station_m: float) -> float:
        """Return a periodic heading without an angle discontinuity at start/finish."""

        sin_heading = self.interpolate(np.sin(self.heading_rad), station_m)
        cos_heading = self.interpolate(np.cos(self.heading_rad), station_m)
        return float(np.arctan2(sin_heading, cos_heading))

    def lateral_error_at_station(
        self,
        x_m: float,
        y_m: float,
        station_m: float,
    ) -> float:
        """Return signed cross-track error from an interpolated path point."""

        reference_x = self.interpolate(self.x_m, station_m)
        reference_y = self.interpolate(self.y_m, station_m)
        heading = self.heading_at_station(station_m)
        dx = float(x_m - reference_x)
        dy = float(y_m - reference_y)
        return -np.sin(heading) * dx + np.cos(heading) * dy

    def lateral_error_m(self, x_m: float, y_m: float, index: int) -> float:
        dx = float(x_m - self.x_m[index])
        dy = float(y_m - self.y_m[index])
        heading = float(self.heading_rad[index])
        return -np.sin(heading) * dx + np.cos(heading) * dy


@dataclass(frozen=True)
class TrackCorridor:
    """Paired left/right gates defining the legal vehicle-center corridor."""

    left_boundary_m: FloatArray
    right_boundary_m: FloatArray
    closed: bool = True

    def __post_init__(self) -> None:
        left = np.asarray(self.left_boundary_m, dtype=float)
        right = np.asarray(self.right_boundary_m, dtype=float)
        if left.shape != right.shape or left.ndim != 2 or left.shape[1] != 2:
            raise ValueError("Track boundaries must be matching N-by-2 arrays.")
        if left.shape[0] < 5:
            raise ValueError("A track corridor needs at least five paired gates.")
        if not np.all(np.isfinite(left)) or not np.all(np.isfinite(right)):
            raise ValueError("Track boundaries must contain finite coordinates.")
        if np.any(np.linalg.norm(left - right, axis=1) <= 1e-6):
            raise ValueError("Every track gate must have positive width.")
        object.__setattr__(self, "left_boundary_m", left)
        object.__setattr__(self, "right_boundary_m", right)

    @classmethod
    def from_csv(cls, path: str | Path, *, closed: bool = True) -> TrackCorridor:
        """Load columns ``left_x_m,left_y_m,right_x_m,right_y_m``."""

        left: list[tuple[float, float]] = []
        right: list[tuple[float, float]] = []
        with Path(path).open(newline="", encoding="utf-8") as handle:
            for row in csv.DictReader(handle):
                left.append((float(row["left_x_m"]), float(row["left_y_m"])))
                right.append((float(row["right_x_m"]), float(row["right_y_m"])))
        return cls(np.asarray(left), np.asarray(right), closed=closed)

    @property
    def gate_count(self) -> int:
        return int(self.left_boundary_m.shape[0])

    @property
    def center_points_m(self) -> FloatArray:
        return 0.5 * (self.left_boundary_m + self.right_boundary_m)

    @property
    def gate_directions(self) -> FloatArray:
        vector = self.left_boundary_m - self.right_boundary_m
        return vector / np.linalg.norm(vector, axis=1)[:, None]

    @property
    def gate_widths_m(self) -> FloatArray:
        return np.linalg.norm(self.left_boundary_m - self.right_boundary_m, axis=1)

    def offset_bounds(
        self,
        *,
        vehicle_width_m: float,
        safety_margin_m: float = 0.0,
    ) -> tuple[FloatArray, FloatArray]:
        """Return lateral center-position bounds after vehicle-footprint clearance."""

        clearance = 0.5 * float(vehicle_width_m) + float(safety_margin_m)
        half_available = 0.5 * self.gate_widths_m - clearance
        if np.any(half_available <= 0.0):
            raise ValueError("Vehicle width plus safety margins do not fit through every gate.")
        return -half_available, half_available

    def line_from_offsets(
        self,
        offsets_m: ArrayLike,
        *,
        sample_step_m: float = 1.0,
    ) -> RacingLine:
        """Build a smooth periodic path through lateral gate offsets."""

        if not self.closed:
            raise NotImplementedError("The first lap-simulation release supports closed tracks.")
        offsets = np.asarray(offsets_m, dtype=float)
        if offsets.shape != (self.gate_count,):
            raise ValueError(f"Expected {self.gate_count} gate offsets, got {offsets.shape}.")
        if not np.all(np.isfinite(offsets)):
            raise ValueError("Racing-line offsets must be finite.")
        if sample_step_m <= 0.0:
            raise ValueError("sample_step_m must be positive.")

        gate_points = self.center_points_m + self.gate_directions * offsets[:, None]
        closed_points = np.vstack((gate_points, gate_points[0]))
        gate_chords = np.linalg.norm(np.diff(closed_points, axis=0), axis=1)
        if np.any(gate_chords <= 1e-6):
            raise ValueError("Racing-line gate points must remain distinct.")
        parameter = np.concatenate(([0.0], np.cumsum(gate_chords)))
        x_spline = CubicSpline(parameter, closed_points[:, 0], bc_type="periodic")
        y_spline = CubicSpline(parameter, closed_points[:, 1], bc_type="periodic")

        dense_count = max(1000, 20 * self.gate_count)
        dense_parameter = np.linspace(0.0, parameter[-1], dense_count, endpoint=True)
        dense_x = x_spline(dense_parameter)
        dense_y = y_spline(dense_parameter)
        dense_ds = np.hypot(np.diff(dense_x), np.diff(dense_y))
        dense_station = np.concatenate(([0.0], np.cumsum(dense_ds)))
        length = float(dense_station[-1])
        sample_count = max(self.gate_count * 2, int(np.ceil(length / sample_step_m)))
        station = np.linspace(0.0, length, sample_count, endpoint=False)
        sample_parameter = np.interp(station, dense_station, dense_parameter)

        x = np.asarray(x_spline(sample_parameter), dtype=float)
        y = np.asarray(y_spline(sample_parameter), dtype=float)
        dx = np.asarray(x_spline(sample_parameter, 1), dtype=float)
        dy = np.asarray(y_spline(sample_parameter, 1), dtype=float)
        ddx = np.asarray(x_spline(sample_parameter, 2), dtype=float)
        ddy = np.asarray(y_spline(sample_parameter, 2), dtype=float)
        derivative_norm = np.hypot(dx, dy)
        curvature = (dx * ddy - dy * ddx) / np.maximum(derivative_norm**3, 1e-12)
        segment_length = np.diff(np.concatenate((station, [length])))
        return RacingLine(
            station_m=station,
            x_m=x,
            y_m=y,
            heading_rad=np.unwrap(np.arctan2(dy, dx)),
            curvature_per_m=np.asarray(curvature, dtype=float),
            segment_length_m=np.asarray(segment_length, dtype=float),
            gate_offsets_m=offsets.copy(),
            track_length_m=length,
        )
