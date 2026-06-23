from __future__ import annotations

from dataclasses import dataclass
import math
from typing import Any

try:  # Keep the web shell importable even in a minimal Python environment.
    import numpy as np  # type: ignore[import-not-found]
    from scipy.optimize import root  # type: ignore[import-not-found]
except Exception:  # pragma: no cover - exercised only when optional deps are missing
    np = None  # type: ignore[assignment]
    root = None  # type: ignore[assignment]


DEFAULT_SWEEP_M = tuple(round(-0.04 + (0.08 / 19.0) * index, 6) for index in range(20))
DEFAULT_ROLL_DEG = tuple(round(-1.5 + (3.0 / 19.0) * index, 6) for index in range(20))


def _curve_meta(
    curve_id: str,
    label: str,
    unit: str,
    x_id: str,
    x_label: str,
    x_unit: str,
    y_label: str,
    source_plot: str,
) -> dict[str, str]:
    return {
        "id": curve_id,
        "label": label,
        "unit": unit,
        "x_id": x_id,
        "x_label": x_label,
        "x_unit": x_unit,
        "y_label": y_label,
        "source_plot": source_plot,
    }


KINEMATIC_CURVE_META = [
    _curve_meta("bump_camber_deg", "Bump Camber", "deg", "jounce_mm", "Jounce", "mm", "Camber", "Plot1"),
    _curve_meta("bump_toe_deg", "Bump Toe", "deg", "jounce_mm", "Jounce", "mm", "Toe", "Plot2"),
    _curve_meta("bump_caster_deg", "Bump Caster", "deg", "jounce_mm", "Jounce", "mm", "Caster", "Plot3"),
    _curve_meta(
        "bump_kpi_deg", "Bump KPI", "deg", "jounce_mm", "Jounce", "mm", "Kingpin inclination", "Plot4",
    ),
    _curve_meta(
        "bump_mech_trail_mm", "Bump Mechanical Trail", "mm", "jounce_mm", "Jounce", "mm",
        "Mechanical Trail", "Plot5",
    ),
    _curve_meta(
        "bump_scrub_mm", "Bump Scrub Radius", "mm", "jounce_mm", "Jounce", "mm", "Scrub Radius", "Plot6",
    ),
    _curve_meta(
        "bump_rc_y_mm", "Bump RC y-Migration", "mm", "jounce_mm", "Jounce", "mm", "RC y-Position",
        "Plot11",
    ),
    _curve_meta(
        "bump_rc_z_mm", "Bump RC z-Migration", "mm", "jounce_mm", "Jounce", "mm", "RC z-Position",
        "Plot12",
    ),
    _curve_meta("roll_camber_deg", "Roll Camber", "deg", "roll_deg", "Roll", "deg", "Camber", "Plot15"),
    _curve_meta("roll_toe_deg", "Roll Toe", "deg", "roll_deg", "Roll", "deg", "Toe", "Plot16"),
    _curve_meta("roll_caster_deg", "Roll Caster", "deg", "roll_deg", "Roll", "deg", "Caster", "Plot17"),
    _curve_meta(
        "roll_kpi_deg", "Roll KPI", "deg", "roll_deg", "Roll", "deg", "Kingpin inclination", "Plot18",
    ),
    _curve_meta(
        "roll_mech_trail_mm", "Roll Mechanical Trail", "mm", "roll_deg", "Roll", "deg",
        "Mechanical Trail", "Plot19",
    ),
    _curve_meta(
        "roll_scrub_mm", "Roll Scrub Radius", "mm", "roll_deg", "Roll", "deg", "Scrub Radius", "Plot20",
    ),
    _curve_meta(
        "roll_rc_y_mm", "Roll RC y-Migration", "mm", "roll_deg", "Roll", "deg", "RC y-Position",
        "Plot25",
    ),
    _curve_meta(
        "roll_rc_z_mm", "Roll RC z-Migration", "mm", "roll_deg", "Roll", "deg", "RC z-Position",
        "Plot26",
    ),
]

BUMP_CURVE_SOURCES = {
    "bump_camber_deg": "camber_deg",
    "bump_toe_deg": "toe_deg",
    "bump_caster_deg": "caster_deg",
    "bump_kpi_deg": "kpi_deg",
    "bump_mech_trail_mm": "mech_trail_mm",
    "bump_scrub_mm": "scrub_mm",
    "bump_rc_y_mm": "rc_y_mm",
    "bump_rc_z_mm": "rc_z_mm",
}

ROLL_CURVE_SOURCES = {
    "roll_camber_deg": "camber_deg",
    "roll_toe_deg": "toe_deg",
    "roll_caster_deg": "caster_deg",
    "roll_kpi_deg": "kpi_deg",
    "roll_mech_trail_mm": "mech_trail_mm",
    "roll_scrub_mm": "scrub_mm",
    "roll_rc_y_mm": "rc_y_mm",
    "roll_rc_z_mm": "rc_z_mm",
}


@dataclass(frozen=True)
class CornerPointSet:
    lower_o: Any
    upper_o: Any
    tie_o: Any
    wheel_center: Any
    contact_patch: Any
    tire_front: Any


@dataclass
class CornerKinematics:
    axle: str
    lower_fore_i: Any
    lower_aft_i: Any
    upper_fore_i: Any
    upper_aft_i: Any
    lower_o_initial: Any
    upper_o_initial: Any
    tie_o_initial: Any
    rack_pickup_initial: Any
    wheel_center_initial: Any
    contact_patch_initial: Any
    tire_front_initial: Any

    @classmethod
    def from_vehicle(cls, vehicle: dict[str, Any], axle: str) -> CornerKinematics:
        if np is None:
            raise RuntimeError("NumPy is required for kinematics previews")

        side = vehicle.get(axle, {})
        if not isinstance(side, dict):
            raise ValueError(f"{axle} vehicle section is missing")
        suspension = side.get("suspension", {})
        steering = side.get("steering", {})
        wheel = side.get("wheel", {})
        if not isinstance(suspension, dict) or not isinstance(steering, dict):
            raise ValueError(f"{axle} suspension and steering sections are required")
        if not isinstance(wheel, dict):
            wheel = {}

        wheel_center = _vector(suspension.get("wheel_center_m"), f"{axle}.suspension.wheel_center_m")
        radius_m = _finite_number(wheel.get("radius_m"), f"{axle}.wheel.radius_m", default=0.2)
        camber_rad = math.radians(_finite_number(wheel.get("camber_deg"), f"{axle}.wheel.camber_deg", default=0.0))
        toe_rad = math.radians(_finite_number(wheel.get("toe_deg"), f"{axle}.wheel.toe_deg", default=0.0))
        contact_patch = wheel_center - np.array([0.0, radius_m * math.sin(camber_rad), radius_m * math.cos(camber_rad)])
        tire_front = wheel_center + np.array([radius_m * math.cos(toe_rad), radius_m * math.sin(toe_rad), 0.0])

        return cls(
            axle=axle,
            lower_fore_i=_vector(suspension.get("lower_fore_i_m"), f"{axle}.suspension.lower_fore_i_m"),
            lower_aft_i=_vector(suspension.get("lower_aft_i_m"), f"{axle}.suspension.lower_aft_i_m"),
            upper_fore_i=_vector(suspension.get("upper_fore_i_m"), f"{axle}.suspension.upper_fore_i_m"),
            upper_aft_i=_vector(suspension.get("upper_aft_i_m"), f"{axle}.suspension.upper_aft_i_m"),
            lower_o_initial=_vector(suspension.get("lower_o_m"), f"{axle}.suspension.lower_o_m"),
            upper_o_initial=_vector(suspension.get("upper_o_m"), f"{axle}.suspension.upper_o_m"),
            tie_o_initial=_vector(suspension.get("tie_o_m"), f"{axle}.suspension.tie_o_m"),
            rack_pickup_initial=_vector(steering.get("rack_pickup_m"), f"{axle}.steering.rack_pickup_m"),
            wheel_center_initial=wheel_center,
            contact_patch_initial=contact_patch,
            tire_front_initial=tire_front,
        )

    def solve_sweep(
        self,
        sweep_m: tuple[float, ...],
        roll_deg: tuple[float, ...] = DEFAULT_ROLL_DEG,
    ) -> dict[str, Any]:
        curves: dict[str, list[float | None]] = {str(item["id"]): [] for item in KINEMATIC_CURVE_META}
        points: list[dict[str, Any]] = []
        warnings: list[str] = []
        guess = np.array([0.0, 0.0, 0.0])
        solved_count = 0
        roll_solved_count = 0

        for jounce in sweep_m:
            try:
                solution, point_set, residual_norm = self.solve_jounce(jounce, guess)
                guess = solution
                solved_count += 1
                curve_values = self.curve_values(point_set, solution, residual_norm)
                for key, source in BUMP_CURVE_SOURCES.items():
                    curves[key].append(_json_optional_float(curve_values.get(source)))
                points.append(
                    {
                        "jounce_m": _json_float(jounce),
                        "lower_o_m": _json_point(point_set.lower_o),
                        "upper_o_m": _json_point(point_set.upper_o),
                        "wheel_center_m": _json_point(point_set.wheel_center),
                        "contact_patch_m": _json_point(point_set.contact_patch),
                        "tie_o_m": _json_point(point_set.tie_o),
                        "kingpin_ground_m": _json_point(self.kingpin_ground_intersection(point_set)),
                        "residual_norm_m": _json_float(residual_norm),
                    }
                )
            except Exception as exc:
                for key in BUMP_CURVE_SOURCES:
                    curves[key].append(None)
                points.append({"jounce_m": _json_float(jounce), "error": str(exc)})
                warnings.append(f"{self.axle} {jounce * 1000:.0f} mm: {exc}")

        right_guess = np.array([0.0, 0.0, 0.0])
        left_guess = np.array([0.0, 0.0, 0.0])
        for roll_angle in roll_deg:
            try:
                right_jounce = self.roll_jounce_m(roll_angle)
                left_jounce = -right_jounce
                right_solution, right_points, right_residual = self.solve_jounce(right_jounce, right_guess)
                left_solution, left_points, _left_residual = self.solve_jounce(left_jounce, left_guess)
                right_guess = right_solution
                left_guess = left_solution
                roll_solved_count += 1
                curve_values = self.curve_values(right_points, right_solution, right_residual)
                roll_center = self.roll_center_pair_yz(right_points, left_points)
                curve_values["rc_y_mm"] = _scale_optional(roll_center[0] if roll_center else None, 1000.0)
                curve_values["rc_z_mm"] = _scale_optional(roll_center[1] if roll_center else None, 1000.0)
                for key, source in ROLL_CURVE_SOURCES.items():
                    curves[key].append(_json_optional_float(curve_values.get(source)))
            except Exception as exc:
                for key in ROLL_CURVE_SOURCES:
                    curves[key].append(None)
                warnings.append(f"{self.axle} roll {roll_angle:+.2f} deg: {exc}")

        return {
            "ok": solved_count == len(sweep_m) and roll_solved_count == len(roll_deg),
            "solved_count": solved_count,
            "roll_solved_count": roll_solved_count,
            "curves": curves,
            "points": points,
            "warnings": warnings[:6],
        }

    def solve_jounce(
        self,
        jounce_m: float,
        guess: Any,
        rack_displacement_m: float = 0.0,
    ) -> tuple[Any, CornerPointSet, float]:
        if root is None:
            raise RuntimeError("SciPy is required for kinematics previews")
        target_contact_z = float(self.contact_patch_initial[2] + jounce_m)
        rack_pickup = self.rack_pickup_initial + np.array([0.0, rack_displacement_m, 0.0])

        def residuals(candidate: Any) -> list[float]:
            point_set = self.point_set(candidate)
            return [
                float(_distance(point_set.lower_o, point_set.upper_o) - self.kingpin_length),
                float(_distance(rack_pickup, point_set.tie_o) - self.tie_rod_length),
                float(point_set.contact_patch[2] - target_contact_z),
            ]

        best_solution = None
        best_norm = math.inf
        candidates = [
            guess,
            np.array([0.0, 0.0, 0.0]),
            np.array([0.35 * jounce_m, 0.4 * jounce_m, 0.0]),
            np.array([-0.35 * jounce_m, -0.4 * jounce_m, 0.0]),
        ]
        for candidate in candidates:
            solution = root(residuals, candidate, method="hybr")
            residual_norm = float(np.linalg.norm(residuals(solution.x)))
            if residual_norm < best_norm:
                best_solution = solution
                best_norm = residual_norm
            if math.isfinite(residual_norm) and residual_norm <= 5e-5:
                return solution.x, self.point_set(solution.x), residual_norm
        if best_solution is None:
            raise ValueError("constraint solve did not converge")
        raise ValueError(f"constraint solve residual {best_norm:.3g} m")

    def point_set(self, candidate: Any) -> CornerPointSet:
        lower_angle, upper_angle, steer_angle = [float(value) for value in candidate]
        lower_o = _rotate_about_axis(
            self.lower_o_initial,
            self.lower_fore_i,
            self.lower_axis,
            lower_angle,
        )
        upper_o = _rotate_about_axis(
            self.upper_o_initial,
            self.upper_fore_i,
            self.upper_axis,
            upper_angle,
        )
        contact_patch = self._upright_point(self.contact_patch_local, lower_o, upper_o, steer_angle)
        wheel_center = self._upright_point(self.wheel_center_local, lower_o, upper_o, steer_angle)
        tire_front = self._upright_point(self.tire_front_local, lower_o, upper_o, steer_angle)
        tie_o = self._upright_point(self.tie_o_local, lower_o, upper_o, steer_angle)
        return CornerPointSet(
            lower_o=lower_o,
            upper_o=upper_o,
            tie_o=tie_o,
            wheel_center=wheel_center,
            contact_patch=contact_patch,
            tire_front=tire_front,
        )

    def curve_values(self, point_set: CornerPointSet, solution: Any, residual_norm: float) -> dict[str, float | None]:
        radial = point_set.wheel_center - point_set.contact_patch
        forward = point_set.tire_front - point_set.wheel_center
        kingpin_ground = self.kingpin_ground_intersection(point_set)
        initial = self.initial_point_set()
        initial_radial = initial.wheel_center - initial.contact_patch
        initial_forward = initial.tire_front - initial.wheel_center
        initial_kingpin_ground = self.kingpin_ground_intersection(initial)
        # Camber uses the vehicle convention: inward wheel tilt is negative.
        # Legacy simulation_toolkit `gamma` was inclination, with the opposite sign on the left side.
        camber_deg = math.degrees(math.atan2(float(radial[1]), float(radial[2])))
        toe_deg = math.degrees(math.atan2(float(forward[1]), float(forward[0])))
        caster_deg = self.caster_deg(point_set)
        kpi_deg = self.kpi_deg(point_set)
        initial_camber_deg = math.degrees(math.atan2(float(initial_radial[1]), float(initial_radial[2])))
        initial_toe_deg = math.degrees(math.atan2(float(initial_forward[1]), float(initial_forward[0])))
        initial_caster_deg = self.caster_deg(initial)
        initial_kpi_deg = self.kpi_deg(initial)
        mech_trail_mm = 1000.0 * self.mech_trail_m(point_set, kingpin_ground)
        scrub_mm = 1000.0 * self.scrub_m(point_set, kingpin_ground)
        initial_mech_trail_mm = 1000.0 * self.mech_trail_m(initial, initial_kingpin_ground)
        initial_scrub_mm = 1000.0 * self.scrub_m(initial, initial_kingpin_ground)
        front_ic = self.front_view_instant_center(point_set)
        initial_front_ic = self.front_view_instant_center(initial)
        side_ic = self.side_view_instant_center(point_set)
        roll_center = self.roll_center(point_set, front_ic)
        initial_roll_center = self.roll_center(initial, initial_front_ic)
        values: dict[str, float | None] = {
            "camber_deg": camber_deg,
            "camber_change_deg": camber_deg - initial_camber_deg,
            "toe_deg": toe_deg,
            "toe_change_deg": toe_deg - initial_toe_deg,
            "caster_deg": caster_deg,
            "caster_change_deg": caster_deg - initial_caster_deg,
            "kpi_deg": kpi_deg,
            "kpi_change_deg": kpi_deg - initial_kpi_deg,
            "mech_trail_mm": mech_trail_mm,
            "mech_trail_change_mm": mech_trail_mm - initial_mech_trail_mm,
            "scrub_mm": scrub_mm,
            "scrub_change_mm": scrub_mm - initial_scrub_mm,
            "track_width_mm": 2000.0 * abs(float(point_set.contact_patch[1])),
            "track_change_mm": 2000.0 * float(point_set.contact_patch[1] - self.contact_patch_initial[1]),
            "wheel_center_track_change_mm": 2000.0 * float(point_set.wheel_center[1] - self.wheel_center_initial[1]),
            "wheel_center_x_mm": 1000.0 * float(point_set.wheel_center[0] - self.wheel_center_initial[0]),
            "wheel_center_y_mm": 1000.0 * float(point_set.wheel_center[1] - self.wheel_center_initial[1]),
            "wheel_center_z_mm": 1000.0 * float(point_set.wheel_center[2] - self.wheel_center_initial[2]),
            "contact_patch_x_mm": 1000.0 * float(point_set.contact_patch[0] - self.contact_patch_initial[0]),
            "contact_patch_y_mm": 1000.0 * float(point_set.contact_patch[1] - self.contact_patch_initial[1]),
            "contact_patch_z_mm": 1000.0 * float(point_set.contact_patch[2] - self.contact_patch_initial[2]),
            "contact_patch_scrub_mm": 1000.0 * float(point_set.contact_patch[1] - self.contact_patch_initial[1]),
            "kingpin_ground_x_mm": 1000.0 * float(kingpin_ground[0] - initial_kingpin_ground[0]),
            "kingpin_ground_y_mm": 1000.0 * float(kingpin_ground[1] - initial_kingpin_ground[1]),
            "kingpin_ground_z_mm": 1000.0 * float(kingpin_ground[2] - initial_kingpin_ground[2]),
            "lower_o_x_mm": 1000.0 * float(point_set.lower_o[0] - self.lower_o_initial[0]),
            "lower_o_y_mm": 1000.0 * float(point_set.lower_o[1] - self.lower_o_initial[1]),
            "lower_o_z_mm": 1000.0 * float(point_set.lower_o[2] - self.lower_o_initial[2]),
            "upper_o_x_mm": 1000.0 * float(point_set.upper_o[0] - self.upper_o_initial[0]),
            "upper_o_y_mm": 1000.0 * float(point_set.upper_o[1] - self.upper_o_initial[1]),
            "upper_o_z_mm": 1000.0 * float(point_set.upper_o[2] - self.upper_o_initial[2]),
            "tie_o_x_mm": 1000.0 * float(point_set.tie_o[0] - self.tie_o_initial[0]),
            "tie_o_y_mm": 1000.0 * float(point_set.tie_o[1] - self.tie_o_initial[1]),
            "tie_o_z_mm": 1000.0 * float(point_set.tie_o[2] - self.tie_o_initial[2]),
            "front_ic_y_mm": _scale_optional(front_ic[0] if front_ic else None, 1000.0),
            "front_ic_z_mm": _scale_optional(front_ic[1] if front_ic else None, 1000.0),
            "front_swing_arm_mm": self.front_view_swing_arm_mm(point_set, front_ic),
            "rc_y_mm": 0.0 if roll_center is not None else None,
            "rc_z_mm": _scale_optional(roll_center, 1000.0),
            "roll_center_z_mm": _scale_optional(roll_center, 1000.0),
            "roll_center_height_mm": _scale_optional(
                None if roll_center is None else roll_center - float(point_set.contact_patch[2]),
                1000.0,
            ),
            "roll_center_migration_mm": _scale_optional(
                None if roll_center is None or initial_roll_center is None else roll_center - initial_roll_center,
                1000.0,
            ),
            "side_ic_x_mm": _scale_optional(side_ic[0] if side_ic else None, 1000.0),
            "side_ic_z_mm": _scale_optional(side_ic[1] if side_ic else None, 1000.0),
            "side_swing_arm_mm": self.side_view_swing_arm_mm(point_set, side_ic),
            "side_view_angle_deg": self.side_view_swing_arm_angle_deg(point_set, side_ic),
            "lower_arm_rotation_deg": math.degrees(float(solution[0])),
            "upper_arm_rotation_deg": math.degrees(float(solution[1])),
            "steer_angle_deg": math.degrees(float(solution[2])),
            "constraint_residual_mm": 1000.0 * residual_norm,
        }
        return values

    def roll_jounce_m(self, roll_deg: float) -> float:
        return math.tan(math.radians(float(roll_deg))) * abs(float(self.contact_patch_initial[1]))

    def add_gradient_curves(self, curves: dict[str, list[float | None]], sweep_m: tuple[float, ...]) -> None:
        gradient_sources = {
            "camber_gain_deg_per_m": "camber_deg",
            "toe_gain_deg_per_m": "toe_deg",
            "caster_gain_deg_per_m": "caster_deg",
            "kpi_gain_deg_per_m": "kpi_deg",
            "trail_gain_mm_per_m": "mech_trail_mm",
            "scrub_gain_mm_per_m": "scrub_mm",
            "track_change_gain_mm_per_m": "track_change_mm",
        }
        for target, source in gradient_sources.items():
            if target in curves and source in curves:
                curves[target] = _curve_gradient(curves[source], sweep_m)

    def initial_point_set(self) -> CornerPointSet:
        return CornerPointSet(
            lower_o=self.lower_o_initial,
            upper_o=self.upper_o_initial,
            tie_o=self.tie_o_initial,
            wheel_center=self.wheel_center_initial,
            contact_patch=self.contact_patch_initial,
            tire_front=self.tire_front_initial,
        )

    def front_view_instant_center(self, point_set: CornerPointSet) -> tuple[float, float] | None:
        lower_i = (self.lower_fore_i + self.lower_aft_i) / 2.0
        upper_i = (self.upper_fore_i + self.upper_aft_i) / 2.0
        return _line_intersection_2d(
            (float(lower_i[1]), float(lower_i[2])),
            (float(point_set.lower_o[1]), float(point_set.lower_o[2])),
            (float(upper_i[1]), float(upper_i[2])),
            (float(point_set.upper_o[1]), float(point_set.upper_o[2])),
        )

    def side_view_instant_center(self, point_set: CornerPointSet) -> tuple[float, float] | None:
        lower_i = (self.lower_fore_i + self.lower_aft_i) / 2.0
        upper_i = (self.upper_fore_i + self.upper_aft_i) / 2.0
        return _line_intersection_2d(
            (float(lower_i[0]), float(lower_i[2])),
            (float(point_set.lower_o[0]), float(point_set.lower_o[2])),
            (float(upper_i[0]), float(upper_i[2])),
            (float(point_set.upper_o[0]), float(point_set.upper_o[2])),
        )

    def roll_center(self, point_set: CornerPointSet, front_ic: tuple[float, float] | None) -> float | None:
        if front_ic is None:
            return None
        contact_y = float(point_set.contact_patch[1])
        contact_z = float(point_set.contact_patch[2])
        ic_y, ic_z = front_ic
        if abs(ic_y - contact_y) < 1e-12:
            return None
        t = -contact_y / (ic_y - contact_y)
        return contact_z + t * (ic_z - contact_z)

    def roll_center_pair_yz(
        self,
        right_point_set: CornerPointSet,
        left_point_set: CornerPointSet,
    ) -> tuple[float, float] | None:
        right_ic = self.front_view_instant_center(right_point_set)
        left_ic = self.front_view_instant_center(left_point_set)
        if right_ic is None or left_ic is None:
            return None
        right_contact = (
            float(right_point_set.contact_patch[1]),
            float(right_point_set.contact_patch[2]),
        )
        left_contact = (
            -float(left_point_set.contact_patch[1]),
            float(left_point_set.contact_patch[2]),
        )
        return _line_intersection_2d(
            right_contact,
            right_ic,
            left_contact,
            (-left_ic[0], left_ic[1]),
        )

    def front_view_swing_arm_mm(self, point_set: CornerPointSet, front_ic: tuple[float, float] | None) -> float | None:
        if front_ic is None:
            return None
        return 1000.0 * math.hypot(
            front_ic[0] - float(point_set.contact_patch[1]),
            front_ic[1] - float(point_set.contact_patch[2]),
        )

    def side_view_swing_arm_mm(self, point_set: CornerPointSet, side_ic: tuple[float, float] | None) -> float | None:
        if side_ic is None:
            return None
        return 1000.0 * math.hypot(
            side_ic[0] - float(point_set.contact_patch[0]),
            side_ic[1] - float(point_set.contact_patch[2]),
        )

    def side_view_swing_arm_angle_deg(
        self,
        point_set: CornerPointSet,
        side_ic: tuple[float, float] | None,
    ) -> float | None:
        if side_ic is None:
            return None
        return math.degrees(math.atan2(
            side_ic[1] - float(point_set.contact_patch[2]),
            side_ic[0] - float(point_set.contact_patch[0]),
        ))

    def caster_deg(self, point_set: CornerPointSet) -> float:
        dx = float(point_set.lower_o[0] - point_set.upper_o[0])
        dz = float(point_set.upper_o[2] - point_set.lower_o[2])
        return math.degrees(math.atan2(dx, dz))

    def kpi_deg(self, point_set: CornerPointSet) -> float:
        dy = float(point_set.lower_o[1] - point_set.upper_o[1])
        dz = float(point_set.upper_o[2] - point_set.lower_o[2])
        side_sign = 1.0 if float(point_set.contact_patch[1]) >= 0.0 else -1.0
        return math.degrees(math.atan2(dy, dz)) * side_sign

    def kingpin_ground_intersection(self, point_set: CornerPointSet) -> Any:
        kingpin = point_set.lower_o - point_set.upper_o
        if abs(float(kingpin[2])) < 1e-12:
            raise ValueError("kingpin is parallel to the ground plane")
        t = float((point_set.contact_patch[2] - point_set.upper_o[2]) / kingpin[2])
        return point_set.upper_o + kingpin * t

    def mech_trail_m(self, point_set: CornerPointSet, kingpin_ground: Any | None = None) -> float:
        intersection = kingpin_ground if kingpin_ground is not None else self.kingpin_ground_intersection(point_set)
        magnitude = abs(float(point_set.contact_patch[0] - intersection[0]))
        direction = 1.0 if float(intersection[0]) > float(point_set.contact_patch[0]) else -1.0
        return magnitude * direction

    def scrub_m(self, point_set: CornerPointSet, kingpin_ground: Any | None = None) -> float:
        intersection = kingpin_ground if kingpin_ground is not None else self.kingpin_ground_intersection(point_set)
        magnitude = math.hypot(
            float(point_set.contact_patch[1] - intersection[1]),
            float(point_set.contact_patch[2] - intersection[2]),
        )
        scrub_direction = 1.0 if float(point_set.contact_patch[1]) > float(intersection[1]) else -1.0
        side_sign = 1.0 if float(point_set.contact_patch[1]) >= 0.0 else -1.0
        return magnitude * scrub_direction * side_sign

    def _upright_point(self, local_point: Any, lower_o: Any, upper_o: Any, steer_angle: float) -> Any:
        aligned = _from_link_centered_coords(local_point, lower_o, upper_o)
        kingpin_axis = _unit(upper_o - lower_o)
        return _rotate_about_axis(aligned, lower_o, kingpin_axis, steer_angle)

    @property
    def lower_axis(self) -> Any:
        return _unit(self.lower_fore_i - self.lower_aft_i)

    @property
    def upper_axis(self) -> Any:
        return _unit(self.upper_fore_i - self.upper_aft_i)

    @property
    def kingpin_length(self) -> float:
        return _distance(self.lower_o_initial, self.upper_o_initial)

    @property
    def tie_rod_length(self) -> float:
        return _distance(self.rack_pickup_initial, self.tie_o_initial)

    @property
    def contact_patch_local(self) -> Any:
        return _link_centered_coords(self.contact_patch_initial, self.lower_o_initial, self.upper_o_initial)

    @property
    def wheel_center_local(self) -> Any:
        return _link_centered_coords(self.wheel_center_initial, self.lower_o_initial, self.upper_o_initial)

    @property
    def tire_front_local(self) -> Any:
        return _link_centered_coords(self.tire_front_initial, self.lower_o_initial, self.upper_o_initial)

    @property
    def tie_o_local(self) -> Any:
        return _link_centered_coords(self.tie_o_initial, self.lower_o_initial, self.upper_o_initial)


def kinematic_curves_payload(
    vehicle: dict[str, Any],
    sweep_m: list[float] | tuple[float, ...] | None = None,
) -> dict[str, Any]:
    sweep = _clean_sweep(sweep_m)
    roll = DEFAULT_ROLL_DEG
    payload: dict[str, Any] = {
        "model": "BobSim native double-wishbone kinematics preview",
        "basis": "Active plot deck mirrors simulation_toolkit/src/simulations/kin/kin_inputs/kin.yml",
        "available": np is not None and root is not None,
        "sweep_m": [_json_float(value) for value in sweep],
        "roll_deg": [_json_float(value) for value in roll],
        "x_axes": {
            "jounce_mm": [_json_float(value * 1000.0) for value in sweep],
            "roll_deg": [_json_float(value) for value in roll],
        },
        "curve_meta": KINEMATIC_CURVE_META,
        "axles": {},
        "warnings": [],
    }
    if np is None or root is None:
        payload["warnings"].append("Install NumPy and SciPy to enable live kinematics curves.")
        return payload

    for axle in ("front", "rear"):
        try:
            solver = CornerKinematics.from_vehicle(vehicle, axle)
            axle_payload = solver.solve_sweep(sweep, roll)
            payload["axles"][axle] = axle_payload
            payload["warnings"].extend(axle_payload.get("warnings", []))
        except Exception as exc:
            payload["axles"][axle] = {
                "ok": False,
                "solved_count": 0,
                "curves": {},
                "points": [],
                "warnings": [str(exc)],
            }
            payload["warnings"].append(f"{axle}: {exc}")
    return payload


def _clean_sweep(sweep_m: list[float] | tuple[float, ...] | None) -> tuple[float, ...]:
    if not sweep_m:
        return DEFAULT_SWEEP_M
    values: list[float] = []
    for value in sweep_m:
        number = float(value)
        if math.isfinite(number):
            values.append(max(-0.15, min(0.15, number)))
    return tuple(values[:41] or DEFAULT_SWEEP_M)


def _vector(value: Any, label: str) -> Any:
    if np is None:
        raise RuntimeError("NumPy is required for kinematics previews")
    if not isinstance(value, (list, tuple)) or len(value) != 3:
        raise ValueError(f"{label} must be a 3D coordinate")
    vector = np.array([float(item) for item in value], dtype=float)
    if not np.all(np.isfinite(vector)):
        raise ValueError(f"{label} must contain finite numbers")
    return vector


def _finite_number(value: Any, label: str, *, default: float) -> float:
    if value is None:
        return default
    number = float(value)
    if not math.isfinite(number):
        raise ValueError(f"{label} must be finite")
    return number


def _unit(vector: Any) -> Any:
    magnitude = float(np.linalg.norm(vector))
    if magnitude < 1e-12:
        raise ValueError("zero-length vector in kinematics geometry")
    return vector / magnitude


def _distance(point_a: Any, point_b: Any) -> float:
    return float(np.linalg.norm(point_b - point_a))


def _scale_optional(value: float | None, scale: float) -> float | None:
    if value is None or not math.isfinite(value):
        return None
    return value * scale


def _line_intersection_2d(
    a: tuple[float, float],
    b: tuple[float, float],
    c: tuple[float, float],
    d: tuple[float, float],
) -> tuple[float, float] | None:
    ax, ay = a
    bx, by = b
    cx, cy = c
    dx, dy = d
    denominator = (ax - bx) * (cy - dy) - (ay - by) * (cx - dx)
    if abs(denominator) < 1e-12:
        return None
    det_ab = ax * by - ay * bx
    det_cd = cx * dy - cy * dx
    x = (det_ab * (cx - dx) - (ax - bx) * det_cd) / denominator
    y = (det_ab * (cy - dy) - (ay - by) * det_cd) / denominator
    return x, y


def _curve_gradient(values: list[float | None], sweep_m: tuple[float, ...]) -> list[float | None]:
    gradients: list[float | None] = []
    if len(values) != len(sweep_m):
        return [None for _ in values]
    for index, _ in enumerate(values):
        if len(values) < 2:
            gradients.append(None)
            continue
        left_index = max(0, index - 1)
        right_index = min(len(values) - 1, index + 1)
        if left_index == right_index:
            gradients.append(None)
            continue
        left_value = values[left_index]
        right_value = values[right_index]
        dx = sweep_m[right_index] - sweep_m[left_index]
        if left_value is None or right_value is None or abs(dx) < 1e-12:
            gradients.append(None)
            continue
        gradients.append(_json_optional_float((float(right_value) - float(left_value)) / dx))
    return gradients


def _rotate_about_axis(point: Any, origin: Any, axis: Any, angle: float) -> Any:
    rot = _rotation_matrix(axis, angle)
    return rot @ (point - origin) + origin


def _rotation_matrix(unit_vector: Any, angle: float) -> Any:
    ux, uy, uz = [float(value) for value in _unit(unit_vector)]
    cos_t = math.cos(angle)
    sin_t = math.sin(angle)
    return np.array(
        [
            [ux**2 * (1 - cos_t) + cos_t, ux * uy * (1 - cos_t) - uz * sin_t, ux * uz * (1 - cos_t) + uy * sin_t],
            [ux * uy * (1 - cos_t) + uz * sin_t, uy**2 * (1 - cos_t) + cos_t, uy * uz * (1 - cos_t) - ux * sin_t],
            [ux * uz * (1 - cos_t) - uy * sin_t, uy * uz * (1 - cos_t) + ux * sin_t, uz**2 * (1 - cos_t) + cos_t],
        ],
        dtype=float,
    )


def _link_rotation_angles(lower_o: Any, upper_o: Any) -> tuple[float, float]:
    origin_transform = upper_o - lower_o
    length = _distance(lower_o, upper_o)
    z_value = float(origin_transform[2])
    y_value = float(origin_transform[1])
    x_value = float(origin_transform[0])
    ang_x = math.atan2(y_value, z_value)
    ratio = max(-1.0, min(1.0, x_value / length))
    ang_y = (1.0 if z_value >= 0.0 else -1.0) * math.asin(ratio)
    return ang_x, ang_y


def _link_centered_coords(point: Any, lower_o: Any, upper_o: Any) -> Any:
    ang_x, ang_y = _link_rotation_angles(lower_o, upper_o)
    translated = point - lower_o
    x_rot = _rotation_matrix(np.array([1.0, 0.0, 0.0]), ang_x)
    y_rot = _rotation_matrix(np.array([0.0, 1.0, 0.0]), -ang_y)
    return y_rot @ (x_rot @ translated)


def _from_link_centered_coords(local_point: Any, lower_o: Any, upper_o: Any) -> Any:
    ang_x, ang_y = _link_rotation_angles(lower_o, upper_o)
    x_rot = _rotation_matrix(np.array([1.0, 0.0, 0.0]), -ang_x)
    y_rot = _rotation_matrix(np.array([0.0, 1.0, 0.0]), ang_y)
    return x_rot @ (y_rot @ local_point) + lower_o


def _json_float(value: Any) -> float:
    return round(float(value), 8)


def _json_optional_float(value: Any) -> float | None:
    if value is None:
        return None
    number = float(value)
    if not math.isfinite(number):
        return None
    return _json_float(number)


def _json_point(point: Any) -> list[float]:
    return [_json_float(value) for value in point.tolist()]
