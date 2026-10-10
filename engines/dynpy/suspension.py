"""Compatibility exports for suspension force transmission.

Kinematic curve construction is exposed by :mod:`engines.dynpy.kinematics`.
``dyn_py`` retains these names so existing reduced-order integrations do not
need to know whether the active evaluator is interpolated or nonlinear.
"""

from __future__ import annotations

from typing import Any, Mapping

import numpy as np

from engines.dynpy.kinematics import (
    CornerInstantLink,
    DoubleWishboneInstantLinks,
    DoubleWishboneKinematicLookup,
)


# Old name kept for existing callers.
DoubleWishboneGeometry = DoubleWishboneKinematicLookup


def project_double_wishbone_instant_links(
    vehicle: Mapping[str, Any],
    *,
    jounce_step_m: float = 1e-4,
) -> DoubleWishboneInstantLinks:
    """Return nominal hardpoint-derived instantaneous force links."""

    if not np.isfinite(jounce_step_m) or jounce_step_m <= 0.0:
        raise ValueError("jounce_step_m must be finite and positive.")
    lookup = DoubleWishboneKinematicLookup.from_vehicle(
        vehicle,
        travel_limit_m=2.0 * jounce_step_m,
        sample_count=5,
    )
    return lookup.instant_links_at(np.zeros(4))


__all__ = [
    "CornerInstantLink",
    "DoubleWishboneGeometry",
    "DoubleWishboneInstantLinks",
    "project_double_wishbone_instant_links",
]
