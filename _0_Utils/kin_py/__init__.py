"""Suspension-kinematics implementation and compatibility exports.

New vehicle-model consumers should import the unified public surface from
``_0_Utils.dyn_py``.  This package remains stable for the original standalone
kinematics workflows and their detailed element tests.
"""

from _0_Utils.kin_py.kinematics import (
    BUMP_CURVE_SOURCES,
    DEFAULT_ROLL_DEG,
    DEFAULT_SWEEP_M,
    KINEMATIC_CURVE_META,
    ROLL_CURVE_SOURCES,
    CornerKinematics,
    CornerPointSet,
    kinematic_curves_payload,
)
from _0_Utils.kin_py.lookup import (
    AxleKinematicLookup,
    AxleKinematicState,
    CornerInstantLink,
    DoubleWishboneInstantLinks,
    DoubleWishboneKinematicLookup,
    KinematicsMode,
    NonlinearDoubleWishboneKinematics,
    VehicleKinematicState,
    VehicleKinematics,
    create_kinematics,
)

__all__ = [
    "AxleKinematicLookup",
    "AxleKinematicState",
    "BUMP_CURVE_SOURCES",
    "CornerInstantLink",
    "DEFAULT_ROLL_DEG",
    "DEFAULT_SWEEP_M",
    "DoubleWishboneInstantLinks",
    "DoubleWishboneKinematicLookup",
    "KINEMATIC_CURVE_META",
    "KinematicsMode",
    "NonlinearDoubleWishboneKinematics",
    "ROLL_CURVE_SOURCES",
    "CornerKinematics",
    "CornerPointSet",
    "VehicleKinematicState",
    "VehicleKinematics",
    "create_kinematics",
    "kinematic_curves_payload",
]
