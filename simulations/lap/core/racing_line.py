"""Vehicle-independent and QSS minimum-time racing-line optimization."""

from __future__ import annotations

from collections.abc import Callable
from dataclasses import dataclass
from typing import Literal

import numpy as np
from numpy.typing import NDArray
from scipy.optimize import OptimizeResult, minimize
from scipy.sparse import coo_matrix
from scipy.sparse.linalg import splu

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
    curvature_max_iterations: int = 10000,
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

    curvature_solution = minimize_curvature(corridor, vehicle_width_m=vehicle_width_m,
        safety_margin_m=safety_margin_m, sample_step_m=sample_step_m,
        max_iterations=curvature_max_iterations)
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


def minimize_curvature(corridor: TrackCorridor, *, vehicle_width_m: float,
                       safety_margin_m: float = 0.15, sample_step_m: float = 1.,
                       max_iterations: int = 10000) -> OptimizeResult:
    """## Minimum-Curvature Line

    Parameters
    ----------
    corridor : TrackCorridor
        Paired track boundaries.
    vehicle_width_m : float
        Nominal outside-tire width.
    safety_margin_m : float
        Clearance beyond each side of the vehicle.
    sample_step_m : float
        Output sampling distance. The objective uses fixed spline quadrature.
    max_iterations : int
        Curvature optimizer iteration limit.

    Returns
    -------
    scipy.optimize.OptimizeResult
        Gate offsets and convergence diagnostics.
    """
    lower, upper = corridor.offset_bounds(vehicle_width_m=vehicle_width_m, safety_margin_m=safety_margin_m)
    if not np.isfinite(sample_step_m) or sample_step_m <= 0.:
        raise ValueError("sample_step_m must be positive and finite.")
    return minimize(
        _curvature_objective(corridor),
        np.zeros(corridor.gate_count),
        jac=True,
        method="L-BFGS-B",
        bounds=list(zip(lower, upper)),
        options={"maxiter": max_iterations, "ftol": 1e-9, "gtol": 1e-5, "maxls": 40},
    )


def _curvature_objective(corridor: TrackCorridor) -> Callable[[FloatArray], tuple[float, FloatArray]]:
    """## Periodic Spline Curvature and Gradient

    Parameters
    ----------
    corridor : TrackCorridor
        Fixed gate centers and offset directions.

    Returns
    -------
    callable
        Integrated squared curvature plus offset smoothing, and its analytic gradient.
        Eight-point Gauss quadrature integrates each spline segment. A sparse adjoint
        accounts for the periodic spline's dependence on all gate positions.
    """
    count = corridor.gate_count
    indices = np.arange(count)
    previous, following = (indices - 1) % count, (indices + 1) % count
    centers, directions = corridor.center_points_m, corridor.gate_directions
    spacing = np.linalg.norm(centers[following] - centers, axis=1)
    if np.any(spacing <= 1e-6):
        raise ValueError("Track gate centers must remain distinct.")
    preceding = np.roll(spacing, 1)
    rows, columns = np.tile(indices, 3), np.r_[previous, indices, following]
    matrix = coo_matrix((np.r_[preceding, 2. * (preceding + spacing), spacing], (rows, columns)),
                        shape=(count, count)).tocsc()
    factor = splu(matrix)
    rhs = coo_matrix((np.r_[6. / preceding, -6. * (1. / preceding + 1. / spacing), 6. / spacing],
                      (rows, columns)), shape=(count, count)).tocsc()
    nodes, weights = np.polynomial.legendre.leggauss(8)
    fraction = .5 * (nodes + 1.)
    weights = .5 * spacing[:, None] * weights[None, :]
    start = spacing[:, None] * (1. - 3. * (1. - fraction) ** 2) / 6.
    end = spacing[:, None] * (3. * fraction ** 2 - 1.) / 6.

    def objective(offsets: FloatArray) -> tuple[float, FloatArray]:
        points = centers + directions * offsets[:, None]
        second = factor.solve(rhs @ points)
        velocity = (points[following] - points)[:, None, :] / spacing[:, None, None] \
            + start[:, :, None] * second[:, None, :] + end[:, :, None] * second[following, None, :]
        acceleration = (1. - fraction)[None, :, None] * second[:, None, :] \
            + fraction[None, :, None] * second[following, None, :]
        cross = velocity[:, :, 0] * acceleration[:, :, 1] - velocity[:, :, 1] * acceleration[:, :, 0]
        speed_squared = np.sum(velocity ** 2, axis=2) + 1e-12
        cost = np.sum(weights * cross ** 2 / speed_squared ** 2.5)
        velocity_gradient = (2. * cross / speed_squared ** 2.5)[:, :, None] \
            * np.stack((acceleration[:, :, 1], -acceleration[:, :, 0]), axis=2) \
            - (5. * cross ** 2 / speed_squared ** 3.5)[:, :, None] * velocity
        acceleration_gradient = (2. * cross / speed_squared ** 2.5)[:, :, None] \
            * np.stack((-velocity[:, :, 1], velocity[:, :, 0]), axis=2)
        velocity_gradient *= weights[:, :, None]
        acceleration_gradient *= weights[:, :, None]
        direct = np.sum(velocity_gradient, axis=1) / spacing[:, None]
        point_gradient = np.roll(direct, 1, axis=0) - direct
        second_gradient = np.sum(start[:, :, None] * velocity_gradient
                                 + (1. - fraction)[None, :, None] * acceleration_gradient, axis=1) \
            + np.roll(np.sum(end[:, :, None] * velocity_gradient
                             + fraction[None, :, None] * acceleration_gradient, axis=1), 1, axis=0)
        # The periodic spline matrix is symmetric, so its adjoint uses the same factorization.
        point_gradient += rhs.T @ factor.solve(second_gradient)
        roughness = np.roll(offsets, -2) - 2. * np.roll(offsets, -1) + offsets
        gradient = np.sum(point_gradient * directions, axis=1) \
            + .002 * (roughness - 2. * np.roll(roughness, 1) + np.roll(roughness, 2))
        return float(cost + .001 * np.dot(roughness, roughness)), gradient

    return objective
