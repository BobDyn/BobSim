"""Compatibility imports for the shared suspension kinematics model.

New code should import from the unified ``engines.dynpy`` product surface.
"""

from engines.dynpy import (
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
