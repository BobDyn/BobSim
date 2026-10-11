"""Vehicle-independent and QSS minimum-time racing-line optimization."""

from __future__ import annotations

from dataclasses import dataclass
from typing import Literal

import numpy as np
from numpy.typing import NDArray
from scipy.optimize import minimize

from simulations.lap.core.qss import GGVMap, QSSLapResult, solve_qss_lap
from simulations.lap.core.track import RacingLine, TrackCorridor


FloatArray = NDArray[np.float64]
LineMode = Literal["centerline", "minimum_curvature", "minimum_time_qss"]


@dataclass(frozen=True)
class LineOptimizationResult:
    """Selected racing line, its QSS lap, and optimization diagnostics."""

    mode: LineMode
    line: RacingLine
    qss_lap: QSSLapResult
    centerline_lap_time_s: float
    minimum_curvature_lap_time_s: float
    success: bool
    message: str
    iterations: int


def optimize_racing_line(
    corridor: TrackCorridor,
    ggv: GGVMap,
    *,
    mode: LineMode = "minimum_time_qss",
    vehicle_width_m: float,
    safety_margin_m: float = 0.1,
    sample_step_m: float = 1.0,
    curvature_max_iterations: int = 30,
    lap_time_max_iterations: int = 25,
    max_speed_mps: float | None = None,
) -> LineOptimizationResult:
    """Generate a center, minimum-curvature, or vehicle-aware minimum-time line."""

    lower, upper = corridor.offset_bounds(
        vehicle_width_m=vehicle_width_m,
        safety_margin_m=safety_margin_m,
    )
    bounds = list(zip(lower, upper))
    center_offsets = np.zeros(corridor.gate_count)
    center_line = corridor.line_from_offsets(center_offsets, sample_step_m=sample_step_m)
    center_lap = solve_qss_lap(center_line, ggv, max_speed_mps=max_speed_mps)
    if mode == "centerline":
        return LineOptimizationResult(
            mode=mode,
            line=center_line,
            qss_lap=center_lap,
            centerline_lap_time_s=center_lap.lap_time_s,
            minimum_curvature_lap_time_s=center_lap.lap_time_s,
            success=True,
            message="Centerline selected without optimization.",
            iterations=0,
        )

    def curvature_cost(offsets: FloatArray) -> float:
        try:
            line = corridor.line_from_offsets(offsets, sample_step_m=sample_step_m)
        except ValueError:
            return 1e12
        curvature_energy = np.sum(
            line.curvature_per_m**2 * line.segment_length_m
        )
        offset_roughness = np.diff(offsets, n=2, append=offsets[:2])
        return float(curvature_energy + 1e-3 * np.sum(offset_roughness**2))

    curvature_solution = minimize(
        curvature_cost,
        center_offsets,
        method="SLSQP",
        bounds=bounds,
        options={"maxiter": curvature_max_iterations, "ftol": 1e-8},
    )
    curvature_offsets = np.asarray(curvature_solution.x, dtype=float)
    curvature_line = corridor.line_from_offsets(
        curvature_offsets,
        sample_step_m=sample_step_m,
    )
    curvature_lap = solve_qss_lap(
        curvature_line,
        ggv,
        max_speed_mps=max_speed_mps,
    )
    if mode == "minimum_curvature":
        return LineOptimizationResult(
            mode=mode,
            line=curvature_line,
            qss_lap=curvature_lap,
            centerline_lap_time_s=center_lap.lap_time_s,
            minimum_curvature_lap_time_s=curvature_lap.lap_time_s,
            success=bool(curvature_solution.success),
            message=str(curvature_solution.message),
            iterations=int(curvature_solution.nit),
        )

    best_line = curvature_line
    best_lap = curvature_lap

    def lap_time_cost(offsets: FloatArray) -> float:
        nonlocal best_line, best_lap
        try:
            candidate_line = corridor.line_from_offsets(
                offsets,
                sample_step_m=sample_step_m,
            )
            candidate_lap = solve_qss_lap(
                candidate_line,
                ggv,
                max_speed_mps=max_speed_mps,
            )
        except (ValueError, FloatingPointError):
            return 1e12
        if not candidate_lap.converged or not np.isfinite(candidate_lap.lap_time_s):
            return 1e12
        if candidate_lap.lap_time_s < best_lap.lap_time_s:
            best_line = candidate_line
            best_lap = candidate_lap
        offset_roughness = np.diff(offsets, n=2, append=offsets[:2])
        return float(candidate_lap.lap_time_s + 1e-5 * np.sum(offset_roughness**2))

    time_solution = minimize(
        lap_time_cost,
        curvature_offsets,
        method="SLSQP",
        bounds=bounds,
        options={"maxiter": lap_time_max_iterations, "ftol": 1e-5},
    )
    final_line = corridor.line_from_offsets(
        np.asarray(time_solution.x),
        sample_step_m=sample_step_m,
    )
    final_lap = solve_qss_lap(final_line, ggv, max_speed_mps=max_speed_mps)
    if final_lap.lap_time_s < best_lap.lap_time_s:
        best_line, best_lap = final_line, final_lap
    return LineOptimizationResult(
        mode=mode,
        line=best_line,
        qss_lap=best_lap,
        centerline_lap_time_s=center_lap.lap_time_s,
        minimum_curvature_lap_time_s=curvature_lap.lap_time_s,
        success=bool(time_solution.success and best_lap.converged),
        message=str(time_solution.message),
        iterations=int(curvature_solution.nit + time_solution.nit),
    )
