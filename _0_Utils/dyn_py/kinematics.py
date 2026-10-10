"""Suspension-kinematics public surface for :mod:`_0_Utils.dyn_py`.

The nonlinear hardpoint solver remains an independently testable subsystem,
but users of the reduced vehicle product should not need to assemble it beside
the dynamics package themselves.  This module is the stable composition
boundary; ``_0_Utils.kin_py`` remains available for compatibility with the
original kinematics-only workflows.
"""

from _0_Utils.kin_py import (
    BUMP_CURVE_SOURCES,
    DEFAULT_ROLL_DEG,
    DEFAULT_SWEEP_M,
    KINEMATIC_CURVE_META,
    ROLL_CURVE_SOURCES,
    AxleKinematicLookup,
    AxleKinematicState,
    CornerInstantLink,
    CornerKinematics,
    CornerPointSet,
    DoubleWishboneInstantLinks,
    DoubleWishboneKinematicLookup,
    KinematicsMode,
    NonlinearDoubleWishboneKinematics,
    VehicleKinematicState,
    VehicleKinematics,
    create_kinematics,
    kinematic_curves_payload,
)

__all__ = [
    "AxleKinematicLookup",
    "AxleKinematicState",
    "BUMP_CURVE_SOURCES",
    "CornerInstantLink",
    "CornerKinematics",
    "CornerPointSet",
    "DEFAULT_ROLL_DEG",
    "DEFAULT_SWEEP_M",
    "DoubleWishboneInstantLinks",
    "DoubleWishboneKinematicLookup",
    "KINEMATIC_CURVE_META",
    "KinematicsMode",
    "NonlinearDoubleWishboneKinematics",
    "ROLL_CURVE_SOURCES",
    "VehicleKinematicState",
    "VehicleKinematics",
    "create_kinematics",
    "kinematic_curves_payload",
]
