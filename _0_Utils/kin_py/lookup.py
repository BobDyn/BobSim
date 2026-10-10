"""Precomputed and exact suspension-kinematics evaluators.

The nonlinear double-wishbone constraint solve belongs here in ``kin_py``.
Consumers such as ``dyn_py`` can select either a jounce-indexed lookup table or
the same nonlinear solve at every force evaluation.  Both backends expose the
same four-corner state, which keeps the dynamics equations independent of how
the kinematics were evaluated.
"""

from __future__ import annotations

from bisect import bisect_right
from dataclasses import dataclass
import math
from typing import Any, Literal, Mapping, Protocol

import numpy as np
from numpy.typing import ArrayLike, NDArray

from _0_Utils.kin_py.kinematics import CornerKinematics, CornerPointSet


FloatArray = NDArray[np.float64]
KinematicsMode = Literal["lookup", "nonlinear"]


@dataclass(frozen=True)
class CornerInstantLink:
    """Reciprocal force slopes for one suspension corner."""

    longitudinal_jacking_coefficient: float
    lateral_jacking_coefficient: float

    def geometric_vertical_force(self, fx_n: float, fy_n: float) -> float:
        return (
            self.longitudinal_jacking_coefficient * float(fx_n)
            + self.lateral_jacking_coefficient * float(fy_n)
        )


@dataclass(frozen=True)
class DoubleWishboneInstantLinks:
    """Instantaneous force links ordered FL, FR, RL, RR."""

    corners: tuple[
        CornerInstantLink,
        CornerInstantLink,
        CornerInstantLink,
        CornerInstantLink,
    ]

    @property
    def coefficient_matrix(self) -> FloatArray:
        return np.asarray(
            [
                (
                    corner.longitudinal_jacking_coefficient,
                    corner.lateral_jacking_coefficient,
                )
                for corner in self.corners
            ],
            dtype=float,
        )

    def geometric_vertical_forces(
        self,
        fx_n: ArrayLike,
        fy_n: ArrayLike,
    ) -> FloatArray:
        fx = np.asarray(fx_n, dtype=float)
        fy = np.asarray(fy_n, dtype=float)
        if fx.shape != (4,) or fy.shape != (4,):
            raise ValueError(
                "Instant-link force inputs must be four-vectors ordered FL, FR, RL, RR."
            )
        coefficients = self.coefficient_matrix
        return coefficients[:, 0] * fx + coefficients[:, 1] * fy

    @property
    def axle_longitudinal_coefficients(self) -> tuple[float, float]:
        coefficients = self.coefficient_matrix
        return float(np.mean(coefficients[:2, 0])), float(np.mean(coefficients[2:, 0]))

    @property
    def axle_net_lateral_coefficients(self) -> tuple[float, float]:
        coefficients = self.coefficient_matrix
        return float(np.mean(coefficients[:2, 1])), float(np.mean(coefficients[2:, 1]))


@dataclass(frozen=True)
class AxleKinematicState:
    """One left-corner state evaluated at a requested jounce."""

    contact_patch_offset_m: tuple[float, float, float]
    wheel_center_offset_m: tuple[float, float, float]
    contact_patch_tangent: tuple[float, float, float]
    camber_rad: float
    toe_rad: float
    caster_rad: float
    kpi_rad: float
    mechanical_trail_m: float
    scrub_radius_m: float

    @property
    def longitudinal_jacking_coefficient(self) -> float:
        return -self.contact_patch_tangent[0] / self.contact_patch_tangent[2]

    @property
    def lateral_jacking_coefficient(self) -> float:
        return -self.contact_patch_tangent[1] / self.contact_patch_tangent[2]


@dataclass(frozen=True)
class VehicleKinematicState:
    """Interpolated or exactly solved kinematics ordered FL, FR, RL, RR."""

    jounce_m: FloatArray
    contact_patch_offsets_m: FloatArray
    wheel_center_offsets_m: FloatArray
    contact_patch_tangents: FloatArray
    camber_rad: FloatArray
    toe_rad: FloatArray
    caster_rad: FloatArray
    kpi_rad: FloatArray
    mechanical_trail_m: FloatArray
    scrub_radius_m: FloatArray
    instant_links: DoubleWishboneInstantLinks


class VehicleKinematics(Protocol):
    """Common interface for lookup and in-loop nonlinear kinematics."""

    @property
    def mode(self) -> KinematicsMode: ...

    def at(self, jounce_m: ArrayLike) -> VehicleKinematicState: ...

    def instant_links_at(self, jounce_m: ArrayLike) -> DoubleWishboneInstantLinks: ...


@dataclass(frozen=True)
class AxleKinematicLookup:
    """Jounce-indexed left-corner curves for one axle."""

    jounce_m: tuple[float, ...]
    contact_patch_offset_m: tuple[tuple[float, float, float], ...]
    wheel_center_offset_m: tuple[tuple[float, float, float], ...]
    contact_patch_tangent: tuple[tuple[float, float, float], ...]
    camber_rad: tuple[float, ...]
    toe_rad: tuple[float, ...]
    caster_rad: tuple[float, ...]
    kpi_rad: tuple[float, ...]
    mechanical_trail_m: tuple[float, ...]
    scrub_radius_m: tuple[float, ...]

    def at(self, jounce_m: float) -> AxleKinematicState:
        lower, upper, fraction = _interpolation_bracket(self.jounce_m, jounce_m)
        return AxleKinematicState(
            contact_patch_offset_m=_lerp_vector(
                self.contact_patch_offset_m, lower, upper, fraction
            ),
            wheel_center_offset_m=_lerp_vector(
                self.wheel_center_offset_m, lower, upper, fraction
            ),
            contact_patch_tangent=_lerp_vector(
                self.contact_patch_tangent, lower, upper, fraction
            ),
            camber_rad=_lerp_scalar(self.camber_rad, lower, upper, fraction),
            toe_rad=_lerp_scalar(self.toe_rad, lower, upper, fraction),
            caster_rad=_lerp_scalar(self.caster_rad, lower, upper, fraction),
            kpi_rad=_lerp_scalar(self.kpi_rad, lower, upper, fraction),
            mechanical_trail_m=_lerp_scalar(
                self.mechanical_trail_m, lower, upper, fraction
            ),
            scrub_radius_m=_lerp_scalar(
                self.scrub_radius_m, lower, upper, fraction
            ),
        )


@dataclass(frozen=True)
class DoubleWishboneKinematicLookup:
    """Precomputed front/rear kinematic curves consumed by vehicle dynamics."""

    front: AxleKinematicLookup
    rear: AxleKinematicLookup
    mode: KinematicsMode = "lookup"

    @classmethod
    def from_vehicle(
        cls,
        vehicle: Mapping[str, Any],
        *,
        travel_limit_m: float = 0.06,
        sample_count: int = 49,
    ) -> DoubleWishboneKinematicLookup:
        if travel_limit_m <= 0.0 or not np.isfinite(travel_limit_m):
            raise ValueError("travel_limit_m must be finite and positive.")
        if sample_count < 5 or sample_count % 2 == 0:
            raise ValueError("sample_count must be an odd integer of at least five.")
        grid = np.linspace(-travel_limit_m, travel_limit_m, sample_count)
        return cls(
            front=_derive_axle_lookup(vehicle, "front", grid),
            rear=_derive_axle_lookup(vehicle, "rear", grid),
        )

    def at(self, jounce_m: ArrayLike) -> VehicleKinematicState:
        jounce = _validate_jounce(jounce_m)
        return _assemble_vehicle_state(
            jounce,
            self.front.at(float(jounce[0])),
            self.front.at(float(jounce[1])),
            self.rear.at(float(jounce[2])),
            self.rear.at(float(jounce[3])),
        )

    def instant_links_at(self, jounce_m: ArrayLike) -> DoubleWishboneInstantLinks:
        return self.at(jounce_m).instant_links


class NonlinearDoubleWishboneKinematics:
    """Solve the rigid suspension constraints inside every dynamics evaluation.

    This backend is intentionally expensive.  It is useful as a correlation
    oracle for lookup-grid selection and for short, high-accuracy transients.
    The centered jounce perturbation is required to recover the reciprocal
    instant-link slopes used by the force balance.
    """

    mode: KinematicsMode = "nonlinear"

    def __init__(
        self,
        vehicle: Mapping[str, Any],
        *,
        derivative_step_m: float = 1e-4,
    ) -> None:
        if derivative_step_m <= 0.0 or not np.isfinite(derivative_step_m):
            raise ValueError("derivative_step_m must be finite and positive.")
        data = dict(vehicle)
        self.front = CornerKinematics.from_vehicle(data, "front")
        self.rear = CornerKinematics.from_vehicle(data, "rear")
        self.derivative_step_m = float(derivative_step_m)

    def at(self, jounce_m: ArrayLike) -> VehicleKinematicState:
        jounce = _validate_jounce(jounce_m)
        return _assemble_vehicle_state(
            jounce,
            self._solve(self.front, float(jounce[0])),
            self._solve(self.front, float(jounce[1])),
            self._solve(self.rear, float(jounce[2])),
            self._solve(self.rear, float(jounce[3])),
        )

    def instant_links_at(self, jounce_m: ArrayLike) -> DoubleWishboneInstantLinks:
        return self.at(jounce_m).instant_links

    def _solve(self, corner: CornerKinematics, jounce_m: float) -> AxleKinematicState:
        step = self.derivative_step_m
        solution, points, _ = corner.solve_jounce(jounce_m, np.zeros(3))
        _, below, _ = corner.solve_jounce(jounce_m - step, solution)
        _, above, _ = corner.solve_jounce(jounce_m + step, solution)
        tangent = (
            np.asarray(above.contact_patch, dtype=float)
            - np.asarray(below.contact_patch, dtype=float)
        ) / (2.0 * step)
        return _state_from_solution(corner, points, tangent)


def create_kinematics(
    vehicle: Mapping[str, Any],
    *,
    mode: KinematicsMode = "lookup",
    travel_limit_m: float = 0.06,
    sample_count: int = 49,
    derivative_step_m: float = 1e-4,
) -> VehicleKinematics:
    """Build a selectable lookup or in-loop nonlinear evaluator."""

    if mode == "lookup":
        return DoubleWishboneKinematicLookup.from_vehicle(
            vehicle,
            travel_limit_m=travel_limit_m,
            sample_count=sample_count,
        )
    if mode == "nonlinear":
        return NonlinearDoubleWishboneKinematics(
            vehicle,
            derivative_step_m=derivative_step_m,
        )
    raise ValueError(f"Unsupported kinematics mode: {mode!r}")


def _derive_axle_lookup(
    vehicle: Mapping[str, Any],
    axle: str,
    jounce_grid: FloatArray,
) -> AxleKinematicLookup:
    corner = CornerKinematics.from_vehicle(dict(vehicle), axle)
    point_sets: list[CornerPointSet] = []
    guess = np.zeros(3)
    for jounce in jounce_grid:
        guess, points, _ = corner.solve_jounce(float(jounce), guess)
        point_sets.append(points)

    contact = np.asarray([points.contact_patch for points in point_sets], dtype=float)
    tangent = np.gradient(contact, jounce_grid, axis=0, edge_order=2)
    if not np.all(np.isfinite(tangent)) or np.any(np.abs(tangent[:, 2]) < 1e-9):
        raise ValueError(f"Could not derive finite {axle} contact-patch tangents.")

    states = [
        _state_from_solution(corner, points, derivative)
        for points, derivative in zip(point_sets, tangent)
    ]
    return AxleKinematicLookup(
        jounce_m=tuple(float(value) for value in jounce_grid),
        contact_patch_offset_m=tuple(state.contact_patch_offset_m for state in states),
        wheel_center_offset_m=tuple(state.wheel_center_offset_m for state in states),
        contact_patch_tangent=tuple(state.contact_patch_tangent for state in states),
        camber_rad=tuple(state.camber_rad for state in states),
        toe_rad=tuple(state.toe_rad for state in states),
        caster_rad=tuple(state.caster_rad for state in states),
        kpi_rad=tuple(state.kpi_rad for state in states),
        mechanical_trail_m=tuple(state.mechanical_trail_m for state in states),
        scrub_radius_m=tuple(state.scrub_radius_m for state in states),
    )


def _state_from_solution(
    corner: CornerKinematics,
    points: CornerPointSet,
    tangent: ArrayLike,
) -> AxleKinematicState:
    initial = corner.initial_point_set()
    radial = np.asarray(points.wheel_center) - np.asarray(points.contact_patch)
    forward = np.asarray(points.tire_front) - np.asarray(points.wheel_center)
    return AxleKinematicState(
        contact_patch_offset_m=_tuple3(
            np.asarray(points.contact_patch) - np.asarray(initial.contact_patch)
        ),
        wheel_center_offset_m=_tuple3(
            np.asarray(points.wheel_center) - np.asarray(initial.wheel_center)
        ),
        contact_patch_tangent=_tuple3(tangent),
        camber_rad=math.atan2(float(radial[1]), float(radial[2])),
        toe_rad=math.atan2(float(forward[1]), float(forward[0])),
        caster_rad=math.radians(corner.caster_deg(points)),
        kpi_rad=math.radians(corner.kpi_deg(points)),
        mechanical_trail_m=corner.mech_trail_m(points),
        scrub_radius_m=corner.scrub_m(points),
    )


def _assemble_vehicle_state(
    jounce_m: FloatArray,
    front_left: AxleKinematicState,
    front_right_left_geometry: AxleKinematicState,
    rear_left: AxleKinematicState,
    rear_right_left_geometry: AxleKinematicState,
) -> VehicleKinematicState:
    left_states = (
        front_left,
        front_right_left_geometry,
        rear_left,
        rear_right_left_geometry,
    )
    side_sign = np.array([1.0, -1.0, 1.0, -1.0])

    contact_offsets = np.asarray(
        [state.contact_patch_offset_m for state in left_states], dtype=float
    )
    wheel_offsets = np.asarray(
        [state.wheel_center_offset_m for state in left_states], dtype=float
    )
    tangents = np.asarray(
        [state.contact_patch_tangent for state in left_states], dtype=float
    )
    contact_offsets[:, 1] *= side_sign
    wheel_offsets[:, 1] *= side_sign
    tangents[:, 1] *= side_sign

    longitudinal = -tangents[:, 0] / tangents[:, 2]
    lateral = -tangents[:, 1] / tangents[:, 2]
    instant_links = DoubleWishboneInstantLinks(
        corners=tuple(
            CornerInstantLink(float(longitudinal[index]), float(lateral[index]))
            for index in range(4)
        )  # type: ignore[arg-type]
    )
    return VehicleKinematicState(
        jounce_m=jounce_m.copy(),
        contact_patch_offsets_m=contact_offsets,
        wheel_center_offsets_m=wheel_offsets,
        contact_patch_tangents=tangents,
        camber_rad=np.asarray(
            [state.camber_rad for state in left_states], dtype=float
        )
        * side_sign,
        toe_rad=np.asarray([state.toe_rad for state in left_states], dtype=float)
        * side_sign,
        caster_rad=np.asarray(
            [state.caster_rad for state in left_states], dtype=float
        ),
        kpi_rad=np.asarray([state.kpi_rad for state in left_states], dtype=float),
        mechanical_trail_m=np.asarray(
            [state.mechanical_trail_m for state in left_states], dtype=float
        ),
        scrub_radius_m=np.asarray(
            [state.scrub_radius_m for state in left_states], dtype=float
        ),
        instant_links=instant_links,
    )


def _validate_jounce(jounce_m: ArrayLike) -> FloatArray:
    jounce = np.asarray(jounce_m, dtype=float)
    if jounce.shape != (4,) or not np.all(np.isfinite(jounce)):
        raise ValueError("Corner jounce must be a finite FL, FR, RL, RR four-vector.")
    return jounce


def _interpolation_bracket(
    grid: tuple[float, ...],
    value: float,
) -> tuple[int, int, float]:
    if value <= grid[0]:
        return 0, 0, 0.0
    if value >= grid[-1]:
        last = len(grid) - 1
        return last, last, 0.0
    upper = bisect_right(grid, value)
    lower = upper - 1
    fraction = (value - grid[lower]) / (grid[upper] - grid[lower])
    return lower, upper, fraction


def _lerp_scalar(
    samples: tuple[float, ...],
    lower: int,
    upper: int,
    fraction: float,
) -> float:
    return samples[lower] + fraction * (samples[upper] - samples[lower])


def _lerp_vector(
    samples: tuple[tuple[float, float, float], ...],
    lower: int,
    upper: int,
    fraction: float,
) -> tuple[float, float, float]:
    return tuple(
        samples[lower][axis]
        + fraction * (samples[upper][axis] - samples[lower][axis])
        for axis in range(3)
    )  # type: ignore[return-value]


def _tuple3(values: ArrayLike) -> tuple[float, float, float]:
    array = np.asarray(values, dtype=float)
    if array.shape != (3,):
        raise ValueError(f"Expected a three-vector, got {array.shape}.")
    return float(array[0]), float(array[1]), float(array[2])
