"""Validation of the force-line / FBRC physics core against analytic cases."""

from __future__ import annotations

import numpy as np
import pytest

from _0_Utils.suspension.force_line import (
    CornerGeometry,
    axle_fbrc_from_geometry,
    solve_axle_fbrc,
    solve_corner_force_line,
)


# Front-left corner of the checked-in LHR vehicle definition,
# BobLib/Records/VehicleDefn/EVBatInvMotDiff_DWBCStabar_DWBCStabarRecord.mo
FRONT_LEFT = {
    "upper_fore_i": [0.1016, 0.237744, 0.2143252],
    "upper_aft_i": [-0.0680974, 0.2356358, 0.215138],
    "lower_fore_i": [0.1016, 0.226314, 0.08001],
    "lower_aft_i": [-0.0762, 0.226314, 0.08001],
    "upper_o": [-0.0092964, 0.5420106, 0.2679954],
    "lower_o": [0.0029972, 0.562991, 0.1139952],
    "tie_rack": [0.05715, 0.2260092, 0.1137158],
    "tie_o": [0.0569976, 0.546989, 0.1522222],
    "contact_patch": [0.0, 0.606110767456, 0.199898 - 0.2045],
}

# Unloaded tire radius; the contact patch above is the wheel center dropped by it.
FRONT_WHEEL_RADIUS = 0.2045
assert FRONT_LEFT["contact_patch"][2] == pytest.approx(0.199898 - FRONT_WHEEL_RADIUS)


def _mirror(points: dict[str, list[float]]) -> dict[str, list[float]]:
    """Mirror a corner across the XZ plane, matching BobLib's Vector.mirrorXZ."""
    return {key: [value[0], -value[1], value[2]] for key, value in points.items()}


def _corner(points: dict[str, list[float]]) -> CornerGeometry:
    return CornerGeometry.from_points(**points)


def _planar_corner(
    *,
    upper_i_y: float,
    upper_i_z: float,
    upper_o_y: float,
    upper_o_z: float,
    lower_i_y: float,
    lower_i_z: float,
    lower_o_y: float,
    lower_o_z: float,
    contact_patch_y: float,
    contact_patch_z: float = 0.0,
    half_span: float = 0.15,
    steer_arm: float = 0.06,
) -> CornerGeometry:
    """Build a corner whose control-arm axes are exactly along x.

    With both arm axes parallel to x the corner reduces to the textbook planar
    double-A-arm, so the exact 3-D solve must reproduce the classical front-view
    construction.

    The tie rod is placed with a real steer arm (`steer_arm` offset in x from the
    kingpin axis) and runs along y. That restrains rotation about the kingpin
    without adding any y-z coupling. Putting `tie_o` on the kingpin axis instead
    would leave the corner with two degrees of freedom, which the solver
    correctly rejects.
    """
    steer_z = 0.5 * (lower_o_z + upper_o_z)
    return CornerGeometry.from_points(
        upper_fore_i=[half_span, upper_i_y, upper_i_z],
        upper_aft_i=[-half_span, upper_i_y, upper_i_z],
        lower_fore_i=[half_span, lower_i_y, lower_i_z],
        lower_aft_i=[-half_span, lower_i_y, lower_i_z],
        upper_o=[0.0, upper_o_y, upper_o_z],
        lower_o=[0.0, lower_o_y, lower_o_z],
        tie_rack=[steer_arm, lower_i_y, steer_z],
        tie_o=[steer_arm, lower_o_y, steer_z],
        contact_patch=[0.0, contact_patch_y, contact_patch_z],
    )


def _classical_force_line_slope(geometry: CornerGeometry) -> float:
    """Slope of the contact-patch-to-instant-center line, 2-D front view."""

    def intersect(
        a: tuple[float, float],
        b: tuple[float, float],
        c: tuple[float, float],
        d: tuple[float, float],
    ) -> tuple[float, float]:
        (ax, ay), (bx, by), (cx, cy), (dx, dy) = a, b, c, d
        denominator = (ax - bx) * (cy - dy) - (ay - by) * (cx - dx)
        det_ab = ax * by - ay * bx
        det_cd = cx * dy - cy * dx
        return (
            (det_ab * (cx - dx) - (ax - bx) * det_cd) / denominator,
            (det_ab * (cy - dy) - (ay - by) * det_cd) / denominator,
        )

    upper_i = geometry.upper_axis_point
    lower_i = geometry.lower_axis_point
    instant_center = intersect(
        (float(upper_i[1]), float(upper_i[2])),
        (float(geometry.upper_o[1]), float(geometry.upper_o[2])),
        (float(lower_i[1]), float(lower_i[2])),
        (float(geometry.lower_o[1]), float(geometry.lower_o[2])),
    )
    contact_patch = geometry.contact_patch
    return (instant_center[1] - float(contact_patch[2])) / (
        instant_center[0] - float(contact_patch[1])
    )


class TestCornerForceLine:
    def test_solves_single_degree_of_freedom(self) -> None:
        line = solve_corner_force_line(_corner(FRONT_LEFT))

        # Normalization: the contact patch rises at unit rate by construction.
        assert line.contact_patch_rate[2] == pytest.approx(1.0)
        # The constraint set must be full rank, i.e. exactly one free DOF.
        assert line.constraint_singular_value > 1e-6

    def test_planar_corner_matches_classical_construction(self) -> None:
        """With arm axes along x, the exact 3-D solve must equal the 2-D one."""
        geometry = _planar_corner(
            upper_i_y=0.25,
            upper_i_z=0.32,
            upper_o_y=0.52,
            upper_o_z=0.34,
            lower_i_y=0.22,
            lower_i_z=0.11,
            lower_o_y=0.56,
            lower_o_z=0.12,
            contact_patch_y=0.60,
        )
        line = solve_corner_force_line(geometry)

        assert line.tan_theta == pytest.approx(
            _classical_force_line_slope(geometry), abs=1e-9
        )

    def test_parallel_horizontal_arms_give_ground_level_force_line(self) -> None:
        """Equal-length horizontal parallel arms: instant center at infinity.

        The classical construction degenerates here, but the force line is
        exactly horizontal, so tan(theta) is 0 and the roll center sits at
        ground level. This is the case the FBRC formulation exists to survive.
        """
        geometry = _planar_corner(
            upper_i_y=0.25,
            upper_i_z=0.30,
            upper_o_y=0.55,
            upper_o_z=0.30,
            lower_i_y=0.25,
            lower_i_z=0.10,
            lower_o_y=0.55,
            lower_o_z=0.10,
            contact_patch_y=0.60,
        )
        line = solve_corner_force_line(geometry)

        assert line.tan_theta == pytest.approx(0.0, abs=1e-12)
        assert line.centerplane_height == pytest.approx(0.0, abs=1e-12)

    def test_centerplane_height_is_force_line_crossing(self) -> None:
        line = solve_corner_force_line(_corner(FRONT_LEFT))

        y_cp = float(line.contact_patch[1])
        z_cp = float(line.contact_patch[2])
        expected = z_cp + line.tan_theta * (0.0 - y_cp)

        assert line.centerplane_height == pytest.approx(expected, rel=1e-12)

    def test_lateral_jacking_force_is_linear_in_lateral_force(self) -> None:
        line = solve_corner_force_line(_corner(FRONT_LEFT))

        assert line.lateral_jacking_force(1000.0) == pytest.approx(
            1000.0 * line.tan_theta
        )
        assert line.lateral_jacking_force(-1000.0) == pytest.approx(
            -line.lateral_jacking_force(1000.0)
        )

    def test_geometric_vertical_force_matches_lateral_only_case(self) -> None:
        """Eq (1) with only Fy present must reduce to Eq (7)."""
        line = solve_corner_force_line(_corner(FRONT_LEFT))

        assert line.geometric_vertical_force([0.0, 800.0, 0.0]) == pytest.approx(
            line.lateral_jacking_force(800.0)
        )

    def test_longitudinal_force_contributes_separately(self) -> None:
        line = solve_corner_force_line(_corner(FRONT_LEFT))

        lateral_only = line.geometric_vertical_force([0.0, 800.0, 0.0])
        with_longitudinal = line.geometric_vertical_force([500.0, 800.0, 0.0])

        assert with_longitudinal - lateral_only == pytest.approx(
            -500.0 * float(line.contact_patch_rate[0])
        )

    def test_vertical_force_alone_produces_no_geometric_force(self) -> None:
        """Pure Fz is entirely an elastic (spring) load, not a link load."""
        line = solve_corner_force_line(_corner(FRONT_LEFT))

        assert line.geometric_vertical_force([0.0, 0.0, -1500.0]) == pytest.approx(0.0)

    def test_rejects_outboard_joint_on_its_own_axis(self) -> None:
        points = dict(FRONT_LEFT)
        points["upper_o"] = points["upper_fore_i"]

        with pytest.raises(ValueError, match="revolute axis"):
            solve_corner_force_line(_corner(points))

    def test_rejects_non_finite_input(self) -> None:
        points = dict(FRONT_LEFT)
        points["upper_o"] = [0.0, float("nan"), 0.0]

        with pytest.raises(ValueError, match="finite"):
            _corner(points)


class TestAxleForceBasedRollCenter:
    def test_symmetric_geometry_equal_forces_equals_kinematic(self) -> None:
        """The KRC is the special case of the FBRC. This is the key reduction."""
        left = _corner(FRONT_LEFT)
        right = _corner(_mirror(FRONT_LEFT))

        result = axle_fbrc_from_geometry(left, right, 900.0, 900.0)

        assert result.height is not None
        assert result.kinematic_height is not None
        assert result.height == pytest.approx(result.kinematic_height, abs=1e-9)
        assert result.height_minus_kinematic == pytest.approx(0.0, abs=1e-9)

    def test_symmetric_axle_equal_forces_has_no_net_jacking(self) -> None:
        """Jacking is driven by left/right force asymmetry, not by roll moment.

        This is why a net-jacking measurement cannot yield a roll center.
        """
        left = _corner(FRONT_LEFT)
        right = _corner(_mirror(FRONT_LEFT))

        result = axle_fbrc_from_geometry(left, right, 900.0, 900.0)

        assert result.jacking_force == pytest.approx(0.0, abs=1e-9)
        # The roll couple, by contrast, is not zero.
        assert abs(result.geometric_load_transfer) > 1.0

    def test_asymmetric_forces_alone_do_not_move_a_symmetric_axle(self) -> None:
        """Force weighting only bites when the two force lines differ.

        With mirror-symmetric geometry both corners have the same centerplane
        height, so any weighted mean of them is that same value. The FBRC
        therefore departs from the KRC only when the geometry is also
        asymmetric -- which in practice means in roll. Documenting this keeps
        anyone from expecting a difference at zero roll.
        """
        left = _corner(FRONT_LEFT)
        right = _corner(_mirror(FRONT_LEFT))

        symmetric = axle_fbrc_from_geometry(left, right, 900.0, 900.0)
        asymmetric = axle_fbrc_from_geometry(left, right, 1400.0, 400.0)

        assert symmetric.height is not None and asymmetric.height is not None
        assert asymmetric.height == pytest.approx(symmetric.height, abs=1e-12)
        # But the jacking force, which is the symmetric part, does change.
        assert symmetric.jacking_force == pytest.approx(0.0, abs=1e-9)
        assert abs(asymmetric.jacking_force) > 1.0

    def test_asymmetric_geometry_separates_fbrc_from_kinematic(self) -> None:
        """With unequal force lines the FBRC differs from the line intersection.

        The equal-force FBRC is the force-consistent replacement for the naive
        KRC construction, so the two must not coincide once the corners differ.
        """
        left_line = solve_corner_force_line(_corner(FRONT_LEFT))
        right_points = _mirror(FRONT_LEFT)
        right_points["upper_o"] = [-0.0092964, -0.5420106, 0.2979954]
        right_line = solve_corner_force_line(_corner(right_points))

        assert right_line.centerplane_height != pytest.approx(
            left_line.centerplane_height, abs=1e-6
        )

        result = solve_axle_fbrc(left_line, right_line, 900.0, 900.0)

        assert result.height is not None
        assert result.kinematic_height is not None
        assert result.height != pytest.approx(result.kinematic_height, abs=1e-6)
        # The equal-force FBRC is exactly the mean of the two corner heights.
        assert result.height == pytest.approx(
            0.5 * (left_line.centerplane_height + right_line.centerplane_height),
            rel=1e-12,
        )

    def test_asymmetric_forces_produce_jacking(self) -> None:
        left = _corner(FRONT_LEFT)
        right = _corner(_mirror(FRONT_LEFT))

        result = axle_fbrc_from_geometry(left, right, 1400.0, 400.0)

        assert abs(result.jacking_force) > 1.0

    def test_height_is_lateral_force_weighted_mean_of_corner_heights(self) -> None:
        """Cross-check the moment form against the compact weighted-mean form."""
        left_line = solve_corner_force_line(_corner(FRONT_LEFT))
        right_line = solve_corner_force_line(_corner(_mirror(FRONT_LEFT)))
        left_f_y, right_f_y = 1250.0, 350.0

        result = solve_axle_fbrc(left_line, right_line, left_f_y, right_f_y)

        expected = (
            left_f_y * left_line.centerplane_height
            + right_f_y * right_line.centerplane_height
        ) / (left_f_y + right_f_y)

        assert result.height is not None
        assert result.height == pytest.approx(expected, rel=1e-12)

    def test_all_force_on_one_corner_gives_that_corner_height(self) -> None:
        left_line = solve_corner_force_line(_corner(FRONT_LEFT))
        right_line = solve_corner_force_line(_corner(_mirror(FRONT_LEFT)))

        result = solve_axle_fbrc(left_line, right_line, 1000.0, 0.0)

        assert result.height is not None
        assert result.height == pytest.approx(left_line.centerplane_height, rel=1e-12)

    def test_height_lies_between_corner_heights_and_moves_monotonically(self) -> None:
        left_line = solve_corner_force_line(_corner(FRONT_LEFT))
        # Deliberately asymmetric right corner so the two heights differ.
        right_points = _mirror(FRONT_LEFT)
        right_points["upper_o"] = [-0.0092964, -0.5420106, 0.2879954]
        right_line = solve_corner_force_line(_corner(right_points))

        low = min(left_line.centerplane_height, right_line.centerplane_height)
        high = max(left_line.centerplane_height, right_line.centerplane_height)

        heights = []
        for left_share in (0.0, 0.25, 0.5, 0.75, 1.0):
            result = solve_axle_fbrc(
                left_line, right_line, 1000.0 * left_share, 1000.0 * (1.0 - left_share)
            )
            assert result.height is not None
            assert low - 1e-12 <= result.height <= high + 1e-12
            heights.append(result.height)

        differences = np.diff(heights)
        assert np.all(differences > 0) or np.all(differences < 0)

    def test_height_is_invariant_to_overall_force_sign(self) -> None:
        """Roll center height is a ratio, so flipping cornering direction keeps it."""
        left = _corner(FRONT_LEFT)
        right = _corner(_mirror(FRONT_LEFT))

        positive = axle_fbrc_from_geometry(left, right, 1300.0, 500.0)
        negative = axle_fbrc_from_geometry(left, right, -1300.0, -500.0)

        assert positive.height is not None and negative.height is not None
        assert positive.height == pytest.approx(negative.height, rel=1e-12)

    def test_height_is_invariant_to_force_scale(self) -> None:
        left = _corner(FRONT_LEFT)
        right = _corner(_mirror(FRONT_LEFT))

        small = axle_fbrc_from_geometry(left, right, 130.0, 50.0)
        large = axle_fbrc_from_geometry(left, right, 1300.0, 500.0)

        assert small.height is not None and large.height is not None
        assert small.height == pytest.approx(large.height, rel=1e-12)

    def test_ground_level_force_lines_give_zero_height_for_any_split(self) -> None:
        """Force lines aimed at the ground centerplane pin the RC to the ground."""
        track_half = 0.60
        left = _planar_corner(
            upper_i_y=0.25,
            upper_i_z=0.30,
            upper_o_y=0.55,
            upper_o_z=0.30,
            lower_i_y=0.25,
            lower_i_z=0.10,
            lower_o_y=0.55,
            lower_o_z=0.10,
            contact_patch_y=track_half,
        )
        right = _planar_corner(
            upper_i_y=-0.25,
            upper_i_z=0.30,
            upper_o_y=-0.55,
            upper_o_z=0.30,
            lower_i_y=-0.25,
            lower_i_z=0.10,
            lower_o_y=-0.55,
            lower_o_z=0.10,
            contact_patch_y=-track_half,
        )

        for left_f_y, right_f_y in ((500.0, 500.0), (900.0, 100.0), (100.0, 900.0)):
            result = axle_fbrc_from_geometry(left, right, left_f_y, right_f_y)
            assert result.height == pytest.approx(0.0, abs=1e-12)

    def test_parallel_force_lines_leave_kinematic_height_undefined(self) -> None:
        """The KRC degenerates where the FBRC stays finite."""
        left = _planar_corner(
            upper_i_y=0.25,
            upper_i_z=0.30,
            upper_o_y=0.55,
            upper_o_z=0.30,
            lower_i_y=0.25,
            lower_i_z=0.10,
            lower_o_y=0.55,
            lower_o_z=0.10,
            contact_patch_y=0.60,
        )
        right = _planar_corner(
            upper_i_y=-0.25,
            upper_i_z=0.30,
            upper_o_y=-0.55,
            upper_o_z=0.30,
            lower_i_y=-0.25,
            lower_i_z=0.10,
            lower_o_y=-0.55,
            lower_o_z=0.10,
            contact_patch_y=-0.60,
        )

        result = axle_fbrc_from_geometry(left, right, 700.0, 300.0)

        assert result.kinematic_height is None
        assert result.height == pytest.approx(0.0, abs=1e-12)
        assert result.height_minus_kinematic is None

    def test_zero_lateral_force_leaves_height_undefined(self) -> None:
        left = _corner(FRONT_LEFT)
        right = _corner(_mirror(FRONT_LEFT))

        result = axle_fbrc_from_geometry(left, right, 0.0, 0.0)

        assert result.height is None

    def test_geometric_load_transfer_uses_contact_patch_plane_arm(self) -> None:
        """Load transfer must use the FBRC height above the contact-patch plane.

        The link forces are reacted at the tires, so the moment arm is measured
        from the contact-patch plane, not from world z=0. The two differ by the
        tire's static deflection, which would be a silent ~7 N error here.
        """
        left = _corner(FRONT_LEFT)
        right = _corner(_mirror(FRONT_LEFT))

        result = axle_fbrc_from_geometry(left, right, 900.0, 900.0)

        assert result.height_above_contact_patch is not None
        expected = (
            -result.lateral_force * result.height_above_contact_patch / result.track
        )

        assert result.geometric_load_transfer == pytest.approx(expected, rel=1e-9)

    def test_load_transfer_direction_follows_roll_center_height(self) -> None:
        """A roll center below the patch plane loads the inner wheel.

        With lateral force toward +y (a left turn) the outer wheel is at -y. This
        vehicle's front force lines cross the centerplane below the contact-patch
        plane, so the geometric component loads the +y (inner) wheel.
        """
        result = axle_fbrc_from_geometry(
            _corner(FRONT_LEFT), _corner(_mirror(FRONT_LEFT)), 900.0, 900.0
        )

        assert result.height_above_contact_patch is not None
        assert result.height_above_contact_patch < 0.0
        assert result.geometric_load_transfer > 0.0

    def test_contact_patch_plane_differs_from_ground(self) -> None:
        """Guard the distinction above: the patches are not at world z=0 here."""
        result = axle_fbrc_from_geometry(
            _corner(FRONT_LEFT), _corner(_mirror(FRONT_LEFT)), 900.0, 900.0
        )

        assert result.contact_patch_plane_z != pytest.approx(0.0, abs=1e-6)
        assert result.height is not None
        assert result.height_above_contact_patch is not None
        assert result.height != pytest.approx(
            result.height_above_contact_patch, abs=1e-6
        )

    def test_front_left_force_line_matches_prototype_values(self) -> None:
        """Regression pin on the real vehicle definition."""
        line = solve_corner_force_line(_corner(FRONT_LEFT))

        assert line.tan_theta == pytest.approx(0.045081, abs=1e-6)
        assert line.angle_deg == pytest.approx(2.581, abs=1e-3)
        assert line.centerplane_height == pytest.approx(-0.031926, abs=1e-6)

    def test_exact_solve_stays_close_to_classical_projection(self) -> None:
        """Sanity band: the 3-D result should be near, not equal to, the 2-D one.

        A large divergence would mean a bug; exact equality would mean the 3-D
        terms were silently dropped.
        """
        geometry = _corner(FRONT_LEFT)
        line = solve_corner_force_line(geometry)
        classical = _classical_force_line_slope(geometry)

        assert line.tan_theta == pytest.approx(classical, rel=0.05)
        assert line.tan_theta != pytest.approx(classical, rel=1e-9)


class TestRearAxle:
    """The rear corner is further from the origin, so conditioning matters."""

    REAR_LEFT = {
        "upper_fore_i": [-1.279144, 0.2972308, 0.2482342],
        "upper_aft_i": [-1.4993874, 0.283845, 0.2434336],
        "lower_fore_i": [-1.3142214, 0.283464, 0.086868],
        "lower_aft_i": [-1.4998192, 0.2835148, 0.0872236],
        "upper_o": [-1.5540736, 0.5267706, 0.29464],
        "lower_o": [-1.55448, 0.57658, 0.116078],
        "tie_rack": [-1.3763498, 0.2897124, 0.1700022],
        "tie_o": [-1.45796, 0.5823966, 0.2143506],
        "contact_patch": [-1.5494, 0.60611077, 0.199898 - 0.2045],
    }

    def test_rear_axle_solves_and_reduces_to_kinematic(self) -> None:
        left = _corner(self.REAR_LEFT)
        right = _corner(_mirror(self.REAR_LEFT))

        result = axle_fbrc_from_geometry(left, right, 800.0, 800.0)

        assert result.height is not None
        assert result.kinematic_height is not None
        assert result.height == pytest.approx(result.kinematic_height, abs=1e-9)

    def test_rear_force_line_is_physically_plausible(self) -> None:
        line = solve_corner_force_line(_corner(self.REAR_LEFT))

        # An FSAE rear roll center should be within a few hundred mm of ground.
        assert abs(line.centerplane_height) < 0.4
        assert abs(line.angle_deg) < 30.0

    def test_translation_invariance(self) -> None:
        """FBRC height is defined about the ground centerplane, so shifting the
        whole axle along x must not change it."""
        left = _corner(self.REAR_LEFT)
        right = _corner(_mirror(self.REAR_LEFT))
        baseline = axle_fbrc_from_geometry(left, right, 900.0, 400.0)

        def shift(points: dict[str, list[float]]) -> dict[str, list[float]]:
            return {k: [v[0] + 3.0, v[1], v[2]] for k, v in points.items()}

        shifted = axle_fbrc_from_geometry(
            _corner(shift(self.REAR_LEFT)),
            _corner(_mirror(shift(self.REAR_LEFT))),
            900.0,
            400.0,
        )

        assert baseline.height is not None and shifted.height is not None
        assert shifted.height == pytest.approx(baseline.height, abs=1e-9)


class TestCrossValidationAgainstAppKinematics:
    """Independent check against `_5_App.kinematics`.

    That module is a separately written double-wishbone solver that articulates
    the linkage with `scipy.optimize.root` and then builds the classical 2-D
    front-view instant center. It shares no code with `force_line`, so agreement
    between the two is real corroboration rather than a tautology.

    They should agree closely but not exactly: `kinematics` projects the control
    arms into the y-z plane, while `force_line` solves the true 3-D twist and so
    also accounts for the arm axes' inclination and the tie rod.
    """

    AXLE = "front"
    JOUNCE_M = (-0.030, -0.015, 0.0, 0.015, 0.030)

    @staticmethod
    def _vehicle() -> dict:
        import yaml

        from _0_Utils.vehicle_io import repo_root

        with (repo_root() / "vehicle.yml").open("r", encoding="utf-8") as handle:
            return yaml.safe_load(handle)

    def _pairs(self) -> list[tuple[float, float, float, float, float]]:
        """(jounce, force_line tan, kinematics tan, force_line h, kinematics h)."""
        from _5_App.kinematics import CornerKinematics

        vehicle = self._vehicle()
        solver = CornerKinematics.from_vehicle(vehicle, self.AXLE)
        suspension = vehicle[self.AXLE]["suspension"]
        rack = np.asarray(vehicle[self.AXLE]["steering"]["rack_pickup_m"], dtype=float)

        def axis(fore: str, aft: str) -> tuple[np.ndarray, np.ndarray]:
            fore_point = np.asarray(suspension[fore], dtype=float)
            aft_point = np.asarray(suspension[aft], dtype=float)
            direction = fore_point - aft_point
            return 0.5 * (fore_point + aft_point), direction / np.linalg.norm(direction)

        upper_point, upper_direction = axis("upper_fore_i_m", "upper_aft_i_m")
        lower_point, lower_direction = axis("lower_fore_i_m", "lower_aft_i_m")

        rows = []
        guess = np.zeros(3)
        for jounce in self.JOUNCE_M:
            solution, points, _ = solver.solve_jounce(jounce, guess)
            guess = solution

            line = solve_corner_force_line(
                CornerGeometry(
                    upper_axis_point=upper_point,
                    upper_axis_direction=upper_direction,
                    lower_axis_point=lower_point,
                    lower_axis_direction=lower_direction,
                    upper_o=np.asarray(points.upper_o, dtype=float),
                    lower_o=np.asarray(points.lower_o, dtype=float),
                    tie_rack=rack,
                    tie_o=np.asarray(points.tie_o, dtype=float),
                    contact_patch=np.asarray(points.contact_patch, dtype=float),
                )
            )

            instant_center = solver.front_view_instant_center(points)
            assert instant_center is not None
            reference_tan = (instant_center[1] - float(points.contact_patch[2])) / (
                instant_center[0] - float(points.contact_patch[1])
            )
            reference_height = solver.roll_center(points, instant_center)
            assert reference_height is not None

            rows.append(
                (jounce, line.tan_theta, reference_tan, line.centerplane_height, reference_height)
            )
        return rows

    def test_force_line_slope_agrees_with_independent_solver(self) -> None:
        for jounce, mine, reference, _, _ in self._pairs():
            assert mine == pytest.approx(reference, abs=1e-3), f"jounce {jounce}"

    def test_centerplane_height_agrees_within_a_millimetre(self) -> None:
        for jounce, _, _, mine, reference in self._pairs():
            assert mine == pytest.approx(reference, abs=1e-3), f"jounce {jounce}"

    def test_roll_center_falls_with_jounce(self) -> None:
        """Both solvers must show the same qualitative migration direction."""
        rows = self._pairs()
        mine = [row[3] for row in rows]
        reference = [row[4] for row in rows]

        assert np.all(np.diff(mine) < 0)
        assert np.all(np.diff(reference) < 0)

    def test_recovered_instant_center_matches_projection(self) -> None:
        """The reporting-only IC helper must land near the 2-D construction."""
        from _5_App.kinematics import CornerKinematics

        from _0_Utils.suspension.force_line import front_view_instant_center

        vehicle = self._vehicle()
        solver = CornerKinematics.from_vehicle(vehicle, self.AXLE)
        suspension = vehicle[self.AXLE]["suspension"]
        rack = np.asarray(vehicle[self.AXLE]["steering"]["rack_pickup_m"], dtype=float)
        _, points, _ = solver.solve_jounce(0.0, np.zeros(3))

        def axis(fore: str, aft: str) -> tuple[np.ndarray, np.ndarray]:
            fore_point = np.asarray(suspension[fore], dtype=float)
            aft_point = np.asarray(suspension[aft], dtype=float)
            direction = fore_point - aft_point
            return 0.5 * (fore_point + aft_point), direction / np.linalg.norm(direction)

        upper_point, upper_direction = axis("upper_fore_i_m", "upper_aft_i_m")
        lower_point, lower_direction = axis("lower_fore_i_m", "lower_aft_i_m")

        line = solve_corner_force_line(
            CornerGeometry(
                upper_axis_point=upper_point,
                upper_axis_direction=upper_direction,
                lower_axis_point=lower_point,
                lower_axis_direction=lower_direction,
                upper_o=np.asarray(points.upper_o, dtype=float),
                lower_o=np.asarray(points.lower_o, dtype=float),
                tie_rack=rack,
                tie_o=np.asarray(points.tie_o, dtype=float),
                contact_patch=np.asarray(points.contact_patch, dtype=float),
            )
        )

        recovered = front_view_instant_center(line)
        reference = solver.front_view_instant_center(points)
        assert recovered is not None and reference is not None

        # The instant center sits ~1.6 m off centerline, so allow 2% agreement.
        assert recovered[0] == pytest.approx(reference[0], rel=0.02)
        assert recovered[1] == pytest.approx(reference[1], rel=0.05)


class TestAsymmetricPatchHeights:
    """The load-transfer identity must hold when BOTH the patch heights and the
    lateral forces are unequal -- the actual operating regime in roll.

    A mirror-symmetric fixture cannot catch a datum error here, because the two
    contact patches sit at the same height and the discrepancy term
    `(z_L - z_R)(Fy_L - Fy_R)/2` vanishes.
    """

    @staticmethod
    def _rolled_pair(
        patch_height_difference: float,
    ) -> tuple[CornerGeometry, CornerGeometry]:
        left = _corner(FRONT_LEFT)
        right_points = _mirror(FRONT_LEFT)
        patch = list(right_points["contact_patch"])
        patch[2] += patch_height_difference
        right_points["contact_patch"] = patch
        return left, _corner(right_points)

    def test_load_transfer_identity_holds_with_unequal_patch_heights(self) -> None:
        left, right = self._rolled_pair(0.008)

        result = axle_fbrc_from_geometry(left, right, 400.0, 1400.0)

        assert result.height_above_contact_patch is not None
        expected = (
            -result.lateral_force * result.height_above_contact_patch / result.track
        )

        assert result.geometric_load_transfer == pytest.approx(expected, rel=1e-9)

    def test_unweighted_patch_datum_would_be_materially_wrong(self) -> None:
        """Pin the size of the error the force-weighted datum avoids.

        With 8 mm of patch-height split and a 1000 N lateral-force split this is
        ~3.3 N against a ~43 N transfer, i.e. about 8 percent.
        """
        left, right = self._rolled_pair(0.008)
        left_f_y, right_f_y = 400.0, 1400.0

        result = axle_fbrc_from_geometry(left, right, left_f_y, right_f_y)

        arithmetic_plane = 0.5 * (
            float(result.left.contact_patch[2]) + float(result.right.contact_patch[2])
        )
        assert result.height is not None
        naive = (
            -result.lateral_force * (result.height - arithmetic_plane) / result.track
        )

        error = result.geometric_load_transfer - naive
        predicted = (
            (float(result.left.contact_patch[2]) - float(result.right.contact_patch[2]))
            * (left_f_y - right_f_y)
            / (2.0 * result.track)
        )

        assert error == pytest.approx(predicted, rel=1e-9)
        assert abs(error) > 0.05 * abs(result.geometric_load_transfer)

    def test_weighted_datum_reduces_to_mean_when_forces_are_equal(self) -> None:
        left, right = self._rolled_pair(0.008)

        result = axle_fbrc_from_geometry(left, right, 900.0, 900.0)

        assert result.contact_patch_plane_z == pytest.approx(
            0.5
            * (
                float(result.left.contact_patch[2])
                + float(result.right.contact_patch[2])
            ),
            rel=1e-12,
        )

    def test_zero_lateral_force_falls_back_to_mean_datum(self) -> None:
        left, right = self._rolled_pair(0.008)

        result = axle_fbrc_from_geometry(left, right, 0.0, 0.0)

        assert result.height is None
        assert result.contact_patch_plane_z == pytest.approx(
            0.5
            * (
                float(result.left.contact_patch[2])
                + float(result.right.contact_patch[2])
            ),
            rel=1e-12,
        )

    def test_kinematic_height_is_available_on_the_patch_datum(self) -> None:
        """Both roll centers must be comparable on one datum (see report plots)."""
        left, right = self._rolled_pair(0.008)

        result = axle_fbrc_from_geometry(left, right, 400.0, 1400.0)

        assert result.kinematic_height is not None
        assert result.kinematic_height_above_contact_patch is not None
        assert result.kinematic_height_above_contact_patch == pytest.approx(
            result.kinematic_height - result.contact_patch_plane_z, rel=1e-12
        )

    def test_fbrc_minus_krc_is_datum_independent(self) -> None:
        """The difference must be the same on either datum, or the metric and the
        plot would disagree."""
        left, right = self._rolled_pair(0.008)

        result = axle_fbrc_from_geometry(left, right, 400.0, 1400.0)

        assert result.height_minus_kinematic is not None
        assert result.height_above_contact_patch is not None
        assert result.kinematic_height_above_contact_patch is not None

        on_patch_datum = (
            result.height_above_contact_patch
            - result.kinematic_height_above_contact_patch
        )
        assert on_patch_datum == pytest.approx(result.height_minus_kinematic, rel=1e-9)
