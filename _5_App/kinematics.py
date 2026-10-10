"""Compatibility imports for the shared suspension kinematics model.

New code should import from the unified ``_0_Utils.dyn_py`` product surface.
"""

from _0_Utils.dyn_py import (
    BUMP_CURVE_SOURCES,
    DEFAULT_ROLL_DEG,
    DEFAULT_SWEEP_M,
    KINEMATIC_CURVE_META,
    ROLL_CURVE_SOURCES,
    CornerKinematics,
    CornerPointSet,
    kinematic_curves_payload,
)

__all__ = [
    "BUMP_CURVE_SOURCES",
    "DEFAULT_ROLL_DEG",
    "DEFAULT_SWEEP_M",
    "KINEMATIC_CURVE_META",
    "ROLL_CURVE_SOURCES",
    "CornerKinematics",
    "CornerPointSet",
    "kinematic_curves_payload",
]
