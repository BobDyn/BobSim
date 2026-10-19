"""Track-corridor and racing-line geometry shared by QSS and transient laps."""

from __future__ import annotations

import csv
from dataclasses import dataclass
from pathlib import Path

import numpy as np
from numpy.typing import ArrayLike, NDArray
from scipy.interpolate import CubicSpline, PPoly


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
        """Load ``x1,y1,x2,y2`` or the legacy left/right column names."""

        left: list[tuple[float, float]] = []
        right: list[tuple[float, float]] = []
        with Path(path).open(newline="", encoding="utf-8-sig") as handle:
            reader = csv.DictReader(handle)
            reader.fieldnames = [name.strip() for name in (reader.fieldnames or [])]
            columns = ("x1", "y1", "x2", "y2") if "x1" in (reader.fieldnames or []) else (
                "left_x_m", "left_y_m", "right_x_m", "right_y_m")
            if not set(columns).issubset(reader.fieldnames or []):
                raise ValueError("Track CSV needs x1,y1,x2,y2 columns in metres.")
            try:
                for row in reader:
                    left.append((float(row[columns[0]]), float(row[columns[1]])))
                    right.append((float(row[columns[2]]), float(row[columns[3]])))
            except (TypeError, ValueError) as exc:
                raise ValueError(f"Invalid track coordinates on row {reader.line_num}.") from exc
        if len(left) > 1 and np.linalg.norm(np.asarray(left[0]) - left[-1]) <= 1e-6 \
                and np.linalg.norm(np.asarray(right[0]) - right[-1]) <= 1e-6:
            left.pop()
            right.pop()
        corridor = cls(np.asarray(left), np.asarray(right), closed=closed)
        corridor.validate_order()
        return corridor

    def validate_order(self) -> None:
        """## Boundary Ordering

        Reject crossed boundaries, duplicate gates and reversed gate pairings.
        """
        centers = self.center_points_m
        tangent = np.roll(centers, -1, axis=0) - np.roll(centers, 1, axis=0)
        gates = self.left_boundary_m - self.right_boundary_m
        side = tangent[:, 0] * gates[:, 1] - tangent[:, 1] * gates[:, 0]
        if np.any(side > 1e-8) and np.any(side < -1e-8):
            raise ValueError("Track boundary pairs change sides. Keep each boundary in circuit order.")
        if np.any(np.linalg.norm(np.roll(centers, -1, axis=0) - centers, axis=1) <= 1e-6):
            raise ValueError("Consecutive track gates must be distinct.")
        starts = np.vstack((self.left_boundary_m, self.right_boundary_m))
        ends = np.vstack((np.roll(self.left_boundary_m, -1, axis=0),
                          np.roll(self.right_boundary_m, -1, axis=0)))
        delta = ends - starts
        for index, (point, vector) in enumerate(zip(starts, delta)):
            relative = starts[index + 1:] - point
            others = delta[index + 1:]
            denominator = vector[0] * others[:, 1] - vector[1] * others[:, 0]
            valid = np.abs(denominator) > 1e-10
            first = np.zeros_like(denominator)
            second = np.zeros_like(denominator)
            np.divide(relative[:, 0] * others[:, 1] - relative[:, 1] * others[:, 0],
                      denominator, out=first, where=valid)
            np.divide(relative[:, 0] * vector[1] - relative[:, 1] * vector[0],
                      denominator, out=second, where=valid)
            if np.any(valid & (first > 1e-8) & (first < 1. - 1e-8) & (second > 1e-8) & (second < 1. - 1e-8)):
                raise ValueError("Track boundaries cross. Check the CSV row order and boundary pairing.")

    def _boundary_splines(self) -> tuple[FloatArray, list[FloatArray], list[CubicSpline]]:
        """## Width-Constrained Boundary Interpolation

        Returns
        -------
        tuple
            Shared row coordinates, boundary chord parameters and periodic splines.
            Refinement bounds width by the cone segments and adjacent pairs, within 10 mm.
        """
        original_rows = np.arange(self.gate_count + 1, dtype=float)
        originals = [np.vstack((points, points[0]))
                     for points in (self.left_boundary_m, self.right_boundary_m)]
        if any(np.any(np.linalg.norm(np.diff(points, axis=0), axis=1) <= 1e-6) for points in originals):
            raise ValueError("Consecutive boundary points must be distinct.")
        rows = original_rows.copy()
        width_tolerance_m = .01
        for _ in range(16):
            points = [np.column_stack([np.interp(rows, original_rows, boundary[:, axis]) for axis in (0, 1)])
                      for boundary in originals]
            parameters = [np.r_[0., np.cumsum(np.linalg.norm(np.diff(boundary, axis=0), axis=1))]
                          for boundary in points]
            splines = [CubicSpline(parameter, boundary, bc_type="periodic")
                       for parameter, boundary in zip(parameters, points)]
            intervals = np.diff(rows)
            # Both boundaries use the same row coordinate when comparing their cubic coefficients.
            coefficients = [spline.c * (np.diff(parameter) / intervals)[None, :, None]
                            ** np.arange(3, -1, -1)[:, None, None]
                            for spline, parameter in zip(splines, parameters)]
            separation = (coefficients[0] - coefficients[1])[::-1]
            squared = np.zeros((7, len(intervals)))
            for i in range(4):
                for j in range(4):
                    squared[i + j] += np.sum(separation[i] * separation[j], axis=1)
            gates = points[0] - points[1]
            upper = -squared.copy()
            maximum_width = np.maximum(np.linalg.norm(gates[:-1], axis=1),
                                       np.linalg.norm(gates[1:], axis=1))
            upper[0] += (maximum_width + width_tolerance_m) ** 2
            delta = np.diff(gates, axis=0)
            slope = delta / intervals[:, None]
            squared[0] -= np.sum(gates[:-1] ** 2, axis=1)
            squared[1] -= 2. * np.sum(gates[:-1] * slope, axis=1)
            squared[2] -= np.sum(slope ** 2, axis=1)
            fraction = np.clip(-np.sum(gates[:-1] * delta, axis=1)
                               / np.maximum(np.sum(delta ** 2, axis=1), 1e-30), 0., 1.)
            minimum_width = np.linalg.norm(gates[:-1] + fraction[:, None] * delta, axis=1)
            squared[0] += np.maximum(0., 2. * width_tolerance_m * minimum_width - width_tolerance_m ** 2)
            violations = []
            for polynomial in (squared, upper):
                constraint = PPoly(polynomial[::-1], rows)
                extrema = constraint.derivative().roots(extrapolate=False)
                extrema = extrema[np.isfinite(extrema)]
                violations.append(extrema[constraint(extrema) < -1e-9])
            bad_rows = np.concatenate(violations)
            if not len(bad_rows):
                return rows, parameters, splines
            bad = np.unique(np.clip(np.searchsorted(rows, bad_rows, side="right") - 1, 0, len(intervals) - 1))
            rows = np.sort(np.r_[rows, .5 * (rows[bad] + rows[bad + 1])])
        raise ValueError("Track boundary interpolation could not preserve the cone-defined width.")

    def interpolated_boundaries(self, sample_step_m: float = 1.0) -> tuple[FloatArray, FloatArray]:
        """## Boundary Splines

        Interpolate every cone pair with closed, width-constrained cubic splines.

        Parameters
        ----------
        sample_step_m : float
            Maximum sampling interval along each boundary's chord parameter.

        Returns
        -------
        tuple[FloatArray, FloatArray]
            Boundary samples including every input point and the closing point.
        """
        if not self.closed:
            raise NotImplementedError("Boundary splines require a closed track.")
        if not np.isfinite(sample_step_m) or sample_step_m <= 0.:
            raise ValueError("Boundary sample spacing must be positive and finite.")
        rows, parameters, splines = self._boundary_splines()
        longest = np.maximum(np.diff(parameters[0]), np.diff(parameters[1]))
        samples = np.concatenate([
            np.linspace(start, end, max(2, int(np.ceil(length / sample_step_m)) + 1))[:-1]
            for start, end, length in zip(rows[:-1], rows[1:], longest)
        ] + [rows[-1:]])
        boundaries = [np.asarray(spline(np.interp(samples, rows, parameter)), dtype=float)
                      for spline, parameter in zip(splines, parameters)]
        return boundaries[0], boundaries[1]

    def resampled_gates(self, spacing_m: float) -> TrackCorridor:
        """## Uniform Optimization Gates

        Sample paired boundary splines at equal midpoint arc-length intervals.
        Original row pairs preserve correspondence between the two boundaries.

        Parameters
        ----------
        spacing_m : float
            Target gate spacing in metres, adjusted down to close the circuit.

        Returns
        -------
        TrackCorridor
            Optimization gates independent of the original CSV point density.
        """
        if not self.closed:
            raise NotImplementedError("Gate resampling requires a closed track.")
        if not np.isfinite(spacing_m) or spacing_m <= 0.:
            raise ValueError("Gate spacing must be positive and finite.")
        rows, parameters, splines = self._boundary_splines()
        longest = np.maximum(np.diff(parameters[0]), np.diff(parameters[1]))
        dense_rows = np.concatenate([
            np.linspace(start, end, max(20, int(np.ceil(length / (spacing_m / 20.)))))[:-1]
            for start, end, length in zip(rows[:-1], rows[1:], longest)
        ] + [rows[-1:]])
        boundaries = [spline(np.interp(dense_rows, rows, parameter))
                      for spline, parameter in zip(splines, parameters)]
        centers = .5 * (boundaries[0] + boundaries[1])
        station = np.r_[0., np.cumsum(np.linalg.norm(np.diff(centers, axis=0), axis=1))]
        if np.any(np.diff(station) <= 1e-10):
            raise ValueError("Track midpoint reference must advance along the circuit.")
        count = max(5, int(np.ceil(station[-1] / spacing_m)))
        gate_rows = np.interp(np.linspace(0., station[-1], count, endpoint=False), station, dense_rows)
        gates = [spline(np.interp(gate_rows, rows, parameter))
                 for spline, parameter in zip(splines, parameters)]
        corridor = TrackCorridor(gates[0], gates[1])
        corridor.validate_order()
        return corridor

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

        if not np.isfinite(vehicle_width_m) or vehicle_width_m <= 0.:
            raise ValueError("Vehicle width must be positive and finite.")
        if not np.isfinite(safety_margin_m) or safety_margin_m < 0.:
            raise ValueError("Edge clearance must be nonnegative and finite.")
        clearance = 0.5 * float(vehicle_width_m) + float(safety_margin_m)
        half_available = 0.5 * self.gate_widths_m - clearance
        if np.any(half_available <= 0.0):
            index = int(np.argmin(half_available))
            raise ValueError(
                f"Track gate {index + 1} is {self.gate_widths_m[index]:.3f} m wide. "
                f"Vehicle width plus safety margins require {2 * clearance:.3f} m."
            )
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
