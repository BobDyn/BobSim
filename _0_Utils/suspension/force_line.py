"""Force-line (n-line) and force-based roll center geometry.

This module is the physics core of FbrcEval. It is pure NumPy: it takes
world-frame hardpoint positions and contact-patch tire forces for one instant and
returns the per-corner force lines plus the axle force-based roll center (FBRC).

Theory and derivation live in
``docs/superpowers/specs/2026-07-26-fbrc-eval-design.md``. The essentials:

A corner with locked steering has one suspension degree of freedom. Parameterize
it by ``zeta``, the contact-patch vertical position, so ``d z_cp / d zeta = 1``.
For a tire wrench ``(F, M)`` applied at the contact patch, the generalized force
on that degree of freedom is what the spring reacts (the elastic load), so the
part carried by the rigid links is

    Fz_geom = -[ Fx*(dx_cp/dzeta) + Fy*(dy_cp/dzeta) + M . (dphi/dzeta) ]

For pure lateral load this is ``Fz_geom = Fy * tan(theta)`` with

    tan(theta) = -dy_cp/dzeta

which is the classical force-line inclination, obtained here without any
instant-center construction and therefore without the 2-D projection
approximation or the parallel-arm degeneracy.

Coordinate convention is BobLib's world frame: x forward, y left, z up.
"""

from __future__ import annotations

from dataclasses import dataclass
import math

import numpy as np


# A twist whose contact-patch vertical rate is below this is treated as having no
# usable ride degree of freedom (the corner is at a kinematic lock).
MIN_CP_VERTICAL_RATE = 1e-9

# Below this the suspension constraint set is treated as rank-deficient, i.e. the
# corner has more than one instantaneous degree of freedom.
MIN_CONSTRAINT_SINGULAR_VALUE = 1e-9

# Lateral force magnitude below which an axle FBRC height is undefined, because
# it is the denominator of a force-weighted mean.
MIN_AXLE_LATERAL_FORCE_N = 1e-6


def _as_vector(value: object, label: str) -> np.ndarray:
    vector = np.asarray(value, dtype=float).reshape(-1)
    if vector.size != 3:
        raise ValueError(f"{label} must be a 3D vector, got size {vector.size}")
    if not np.all(np.isfinite(vector)):
        raise ValueError(f"{label} must contain finite numbers")
    return vector


def _unit(vector: np.ndarray, label: str) -> np.ndarray:
    magnitude = float(np.linalg.norm(vector))
    if magnitude < 1e-12:
        raise ValueError(f"{label} is a zero-length direction")
    return vector / magnitude


def _perpendicular_basis(direction: np.ndarray) -> tuple[np.ndarray, np.ndarray]:
    """Return two orthonormal vectors spanning the plane normal to `direction`."""
    seed = np.array([1.0, 0.0, 0.0])
    if abs(float(np.dot(seed, direction))) > 0.9:
        seed = np.array([0.0, 1.0, 0.0])
    first = _unit(np.cross(direction, seed), "perpendicular basis")
    second = _unit(np.cross(direction, first), "perpendicular basis")
    return first, second


@dataclass(frozen=True)
class CornerGeometry:
    """World-frame hardpoints of one double-wishbone corner.

    The two inboard entries describe each control arm's revolute axis: a point on
    the axis and its direction. `upper_o` / `lower_o` are the outboard ball
    joints, `tie_rack` the chassis-side tie-rod end, `tie_o` the upright-side tie
    rod end, and `contact_patch` the tire contact patch.
    """

    upper_axis_point: np.ndarray
    upper_axis_direction: np.ndarray
    lower_axis_point: np.ndarray
    lower_axis_direction: np.ndarray
    upper_o: np.ndarray
    lower_o: np.ndarray
    tie_rack: np.ndarray
    tie_o: np.ndarray
    contact_patch: np.ndarray

    @classmethod
    def from_points(
        cls,
        *,
        upper_fore_i: object,
        upper_aft_i: object,
        lower_fore_i: object,
        lower_aft_i: object,
        upper_o: object,
        lower_o: object,
        tie_rack: object,
        tie_o: object,
        contact_patch: object,
    ) -> CornerGeometry:
        """Build from the fore/aft inboard pickup pairs BobLib parameterizes."""
        upper_fore = _as_vector(upper_fore_i, "upper_fore_i")
        upper_aft = _as_vector(upper_aft_i, "upper_aft_i")
        lower_fore = _as_vector(lower_fore_i, "lower_fore_i")
        lower_aft = _as_vector(lower_aft_i, "lower_aft_i")
        return cls(
            upper_axis_point=0.5 * (upper_fore + upper_aft),
            upper_axis_direction=_unit(upper_fore - upper_aft, "upper arm axis"),
            lower_axis_point=0.5 * (lower_fore + lower_aft),
            lower_axis_direction=_unit(lower_fore - lower_aft, "lower arm axis"),
            upper_o=_as_vector(upper_o, "upper_o"),
            lower_o=_as_vector(lower_o, "lower_o"),
            tie_rack=_as_vector(tie_rack, "tie_rack"),
            tie_o=_as_vector(tie_o, "tie_o"),
            contact_patch=_as_vector(contact_patch, "contact_patch"),
        )


@dataclass(frozen=True)
class CornerForceLine:
    """Instantaneous ride-motion derivatives and force-line geometry.

    All derivatives are with respect to `zeta`, the contact-patch vertical
    position, so `contact_patch_rate[2] == 1` by construction.
    """

    contact_patch_rate: np.ndarray
    """d r_cp / d zeta. Component 2 is 1 by normalization."""

    angular_rate: np.ndarray
    """d phi / d zeta, the upright angular velocity per unit contact-patch rise."""

    tan_theta: float
    """Force-line inclination, -dy_cp/dzeta. Positive lifts on positive Fy."""

    contact_patch: np.ndarray

    constraint_singular_value: float
    """Smallest singular value of the 5x6 constraint matrix; a rank health check."""

    @property
    def angle_deg(self) -> float:
        """Force-line inclination angle in degrees."""
        return math.degrees(math.atan(self.tan_theta))

    @property
    def centerplane_height(self) -> float:
        """Height at which this force line crosses the vehicle centerplane y=0.

        This is `h_i` in the derivation: the per-corner contribution whose
        lateral-force-weighted mean is the axle FBRC height.
        """
        return float(self.contact_patch[2] - self.contact_patch[1] * self.tan_theta)

    def lateral_jacking_force(self, f_y: float) -> float:
        """Link-borne vertical force produced by lateral force `f_y`. Eq (7)."""
        return float(f_y) * self.tan_theta

    def geometric_vertical_force(
        self,
        force: object,
        moment: object = (0.0, 0.0, 0.0),
    ) -> float:
        """Full link-borne vertical force from the complete tire wrench, Eq (1).

        Includes the longitudinal and moment contributions. Reported separately
        from the FBRC, which by definition uses the lateral term only.
        """
        force_vector = _as_vector(force, "force")
        moment_vector = _as_vector(moment, "moment")
        return -(
            float(force_vector[0]) * float(self.contact_patch_rate[0])
            + float(force_vector[1]) * float(self.contact_patch_rate[1])
            + float(np.dot(moment_vector, self.angular_rate))
        )


def solve_corner_force_line(geometry: CornerGeometry) -> CornerForceLine:
    """Solve the corner's single ride degree of freedom and its force line.

    The upright's instantaneous twist relative to the chassis is `(omega, v0)`
    with point velocities `v(p) = v0 + omega x p`. Constraints:

    - Each control-arm outboard joint rotates about that arm's inboard axis, so
      its velocity must lie along `d = n x (p - a)`. Requiring the two
      perpendicular components to vanish gives 2 scalar equations per arm.
    - The tie rod has constant length with a chassis-fixed inboard end, so the
      velocity of its outboard end has no component along the rod: 1 equation.

    Five equations on six unknowns leave the expected single degree of freedom,
    recovered as the null space and scaled so the contact patch rises at unit
    rate.
    """
    rows: list[np.ndarray] = []

    arms = (
        (geometry.upper_axis_point, geometry.upper_axis_direction, geometry.upper_o, "upper"),
        (geometry.lower_axis_point, geometry.lower_axis_direction, geometry.lower_o, "lower"),
    )
    for axis_point, axis_direction, outboard, name in arms:
        axis_direction = _unit(np.asarray(axis_direction, dtype=float), f"{name} arm axis")
        swing = np.cross(axis_direction, outboard - axis_point)
        if float(np.linalg.norm(swing)) < 1e-12:
            raise ValueError(
                f"{name} arm outboard joint lies on its own revolute axis; "
                "the corner has no well-defined arm rotation"
            )
        swing_direction = _unit(swing, f"{name} arm swing direction")
        for constraint_direction in _perpendicular_basis(swing_direction):
            # v(p) . e = v0 . e + (omega x p) . e = v0 . e + omega . (p x e)
            rows.append(
                np.concatenate([np.cross(outboard, constraint_direction), constraint_direction])
            )

    rod_direction = _unit(geometry.tie_o - geometry.tie_rack, "tie rod")
    rows.append(np.concatenate([np.cross(geometry.tie_o, rod_direction), rod_direction]))

    constraints = np.asarray(rows, dtype=float)
    _, singular_values, right_vectors = np.linalg.svd(constraints)

    smallest = float(singular_values[-1])
    if smallest < MIN_CONSTRAINT_SINGULAR_VALUE:
        raise ValueError(
            "suspension constraint set is rank deficient "
            f"(smallest singular value {smallest:.3g}); the corner does not have "
            "exactly one degree of freedom"
        )

    null_space = right_vectors[-1]
    angular_rate = null_space[:3]
    origin_rate = null_space[3:]
    contact_patch_rate = origin_rate + np.cross(angular_rate, geometry.contact_patch)

    vertical_rate = float(contact_patch_rate[2])
    if abs(vertical_rate) < MIN_CP_VERTICAL_RATE:
        raise ValueError(
            "contact-patch vertical rate is zero for the suspension degree of "
            "freedom; the corner is at a kinematic lock"
        )

    scale = 1.0 / vertical_rate
    contact_patch_rate = contact_patch_rate * scale
    angular_rate = angular_rate * scale

    return CornerForceLine(
        contact_patch_rate=contact_patch_rate,
        angular_rate=angular_rate,
        tan_theta=-float(contact_patch_rate[1]),
        contact_patch=np.array(geometry.contact_patch, dtype=float),
        constraint_singular_value=smallest,
    )


@dataclass(frozen=True)
class AxleForceBasedRollCenter:
    """Force-based roll center of one axle at one operating point."""

    height: float | None
    """FBRC height in world z (ground plane), m. None when lateral force is ~0."""

    contact_patch_plane_z: float
    """Lateral-force-weighted mean contact-patch height, m.

    Weighted rather than arithmetic on purpose. The load-transfer identity in
    `geometric_load_transfer` is exact against this datum but only approximate
    against the arithmetic mean: the two differ by
    `(z_L - z_R)(Fy_L - Fy_R) / 2`, which is nonzero exactly in the regime this
    study targets -- a rolled attitude, where the patches sit at different
    heights *and* the tires carry different lateral force.
    """

    lateral_force: float
    """Sum of left and right contact-patch lateral force, N."""

    roll_moment: float
    """Moment about the world x axis through the ground centerplane, N*m."""

    jacking_force: float
    """Sum of link-borne vertical forces, N. Nonzero only for asymmetric load."""

    geometric_roll_moment: float
    """Roll couple from the link-borne vertical forces alone, N*m."""

    geometric_load_transfer: float
    """Geometric wheel load transfer, N, positive meaning load added to the +y
    (left) wheel and removed from the -y (right) wheel.

    Related to the roll center height by

        geometric_load_transfer = -lateral_force * height_above_contact_patch / track

    which is an exact identity because `contact_patch_plane_z` is the
    lateral-force-weighted patch height. Against an unweighted mean patch height
    the relation would be off by `(z_L - z_R)(Fy_L - Fy_R) / (2*track)`.

    The minus sign is a convention consequence, not a correction: the textbook
    form ``dFz = Fy*h/t`` gives the gain on the *outer* wheel, and the outer wheel
    is the one the lateral force points away from. With `lateral_force` positive
    (toward +y) the outer wheel is at -y, so the +y wheel takes the negative of it.
    A roll center below the contact-patch plane therefore transfers load to the
    inner wheel, which is the correct and often surprising physical result.
    """

    ground_crossing_y: float | None
    """Where the resultant line of action crosses z=0, m. None if no jacking."""

    left: CornerForceLine
    right: CornerForceLine

    track: float

    kinematic_height: float | None
    """Kinematic roll center height, for comparison. None if lines are parallel."""

    kinematic_y: float | None

    @property
    def height_above_contact_patch(self) -> float | None:
        """FBRC height above the contact-patch plane.

        This is the moment arm that actually enters the load-transfer equation,
        because the geometric forces are reacted at the tire contact patches, not
        at world z=0. The two differ by the tire's static deflection.
        """
        if self.height is None:
            return None
        return self.height - self.contact_patch_plane_z

    @property
    def kinematic_height_above_contact_patch(self) -> float | None:
        """KRC height on the same datum as `height_above_contact_patch`.

        Provided so the two roll centers are never plotted or differenced across
        mismatched datums, which would show a spurious offset equal to the patch
        plane height even where the two definitions genuinely coincide.
        """
        if self.kinematic_height is None:
            return None
        return self.kinematic_height - self.contact_patch_plane_z

    @property
    def height_minus_kinematic(self) -> float | None:
        """How far the force weighting moves the roll center off the KRC, m."""
        if self.height is None or self.kinematic_height is None:
            return None
        return self.height - self.kinematic_height


def _kinematic_roll_center(
    left: CornerForceLine,
    right: CornerForceLine,
) -> tuple[float | None, float | None]:
    """Intersect the two force lines in the y-z plane (the classical KRC).

    Each line passes through its contact patch with slope `tan_theta` in
    (y, z). Returns (y, z), or (None, None) when the lines are parallel --
    which is exactly the KRC degeneracy the FBRC avoids.
    """
    y_left, z_left = float(left.contact_patch[1]), float(left.contact_patch[2])
    y_right, z_right = float(right.contact_patch[1]), float(right.contact_patch[2])
    slope_left, slope_right = left.tan_theta, right.tan_theta

    denominator = slope_left - slope_right
    if abs(denominator) < 1e-12:
        return None, None

    y = (z_right - z_left + slope_left * y_left - slope_right * y_right) / denominator
    z = z_left + slope_left * (y - y_left)
    if not (math.isfinite(y) and math.isfinite(z)):
        return None, None
    return y, z


def solve_axle_fbrc(
    left: CornerForceLine,
    right: CornerForceLine,
    left_f_y: float,
    right_f_y: float,
    *,
    track: float | None = None,
) -> AxleForceBasedRollCenter:
    """Combine two corner force lines into the axle force-based roll center.

    Uses the moment form of the derivation. Each corner contributes a link-borne
    force with lateral component `f_y` and vertical component `f_y * tan(theta)`
    on a line through its contact patch. Moments about the x axis through the
    ground-level centerplane give

        M_x = sum_i [ y_i * Fz_geom_i - z_i * Fy_i ]
        h    = -M_x / sum_i Fy_i

    which is algebraically the lateral-force-weighted mean of the per-corner
    centerplane heights, and reduces to the kinematic roll center when the two
    lateral forces and the geometry are symmetric.
    """
    left_f_y = float(left_f_y)
    right_f_y = float(right_f_y)
    if not (math.isfinite(left_f_y) and math.isfinite(right_f_y)):
        raise ValueError("corner lateral forces must be finite")

    left_jack = left.lateral_jacking_force(left_f_y)
    right_jack = right.lateral_jacking_force(right_f_y)

    roll_moment = (
        float(left.contact_patch[1]) * left_jack
        - float(left.contact_patch[2]) * left_f_y
        + float(right.contact_patch[1]) * right_jack
        - float(right.contact_patch[2]) * right_f_y
    )

    total_lateral = left_f_y + right_f_y
    height: float | None
    if abs(total_lateral) < MIN_AXLE_LATERAL_FORCE_N:
        height = None
    else:
        height = -roll_moment / total_lateral

    jacking_force = left_jack + right_jack

    if track is None:
        effective_track = abs(float(left.contact_patch[1]) - float(right.contact_patch[1]))
    else:
        effective_track = abs(float(track))
    if effective_track < 1e-9:
        raise ValueError("axle track width must be positive")

    # The geometric roll couple is the moment of the link-borne vertical forces
    # about the ground centerplane. Dividing by track converts it to a wheel load
    # transfer. Using the moment form rather than 0.5*(left - right) keeps this
    # correct when the two contact patches are not symmetric about y=0.
    geometric_roll_moment = (
        float(left.contact_patch[1]) * left_jack
        + float(right.contact_patch[1]) * right_jack
    )
    geometric_load_transfer = geometric_roll_moment / effective_track

    ground_crossing_y: float | None
    if abs(jacking_force) < MIN_AXLE_LATERAL_FORCE_N:
        ground_crossing_y = None
    else:
        ground_crossing_y = roll_moment / jacking_force

    kinematic_y, kinematic_height = _kinematic_roll_center(left, right)

    # Weight the patch-height datum by lateral force so that
    # geometric_load_transfer == -lateral_force*height_above_contact_patch/track
    # is an exact identity even when the patches differ in height AND the tires
    # carry different lateral force -- i.e. in roll, which is the whole point of
    # this study. Fall back to the arithmetic mean when there is no lateral force
    # to weight with, where the distinction is moot anyway.
    if abs(total_lateral) < MIN_AXLE_LATERAL_FORCE_N:
        contact_patch_plane_z = 0.5 * (
            float(left.contact_patch[2]) + float(right.contact_patch[2])
        )
    else:
        contact_patch_plane_z = (
            float(left.contact_patch[2]) * left_f_y
            + float(right.contact_patch[2]) * right_f_y
        ) / total_lateral

    return AxleForceBasedRollCenter(
        height=height,
        contact_patch_plane_z=contact_patch_plane_z,
        lateral_force=total_lateral,
        roll_moment=roll_moment,
        jacking_force=jacking_force,
        geometric_roll_moment=geometric_roll_moment,
        geometric_load_transfer=geometric_load_transfer,
        ground_crossing_y=ground_crossing_y,
        left=left,
        right=right,
        track=effective_track,
        kinematic_height=kinematic_height,
        kinematic_y=kinematic_y,
    )


def axle_fbrc_from_geometry(
    left_geometry: CornerGeometry,
    right_geometry: CornerGeometry,
    left_f_y: float,
    right_f_y: float,
    *,
    track: float | None = None,
) -> AxleForceBasedRollCenter:
    """Solve both corners and combine into the axle FBRC."""
    return solve_axle_fbrc(
        solve_corner_force_line(left_geometry),
        solve_corner_force_line(right_geometry),
        left_f_y,
        right_f_y,
        track=track,
    )


def front_view_instant_center(force_line: CornerForceLine) -> tuple[float, float] | None:
    """Front-view instant center implied by a force line, for reporting only.

    The FBRC never needs this. It is recovered by intersecting the force line
    with the horizontal through the contact patch offset by the swing radius,
    which for the exact-3D solve means the point about which the contact patch
    instantaneously rotates in the y-z plane. Returns None when the motion is
    pure translation (infinite swing arm).
    """
    lateral_rate = -force_line.tan_theta
    roll_rate = float(force_line.angular_rate[0])
    if abs(roll_rate) < 1e-12:
        return None
    # v = omega x r about the instant center: for planar y-z motion with roll
    # rate p, v_y = -p * (z_cp - z_ic) and v_z = p * (y_cp - y_ic).
    y_cp = float(force_line.contact_patch[1])
    z_cp = float(force_line.contact_patch[2])
    z_ic = z_cp + lateral_rate / roll_rate
    y_ic = y_cp - 1.0 / roll_rate
    if not (math.isfinite(y_ic) and math.isfinite(z_ic)):
        return None
    return y_ic, z_ic
