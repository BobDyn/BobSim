"""Nominal suspension rates projected from the active vehicle's linkage geometry."""
from __future__ import annotations

from typing import Any, Mapping
import numpy as np

from engines.kinpy import CornerKinematics


def _unit(value):
    vector = np.asarray(value, dtype=float)
    length = float(np.linalg.norm(vector))
    if not np.isfinite(length) or length < 1e-10:
        raise ValueError("Degenerate suspension actuation geometry")
    return vector / length


def _ratio(numerator: float, denominator: float) -> float:
    if not np.isfinite(denominator) or abs(denominator) < 1e-10:
        raise ValueError("Suspension actuation is at a singular linkage position")
    return float(numerator / denominator)


def nominal_actuation_metrics(data: Mapping[str, Any]) -> dict[str, float]:
    """Differentiate rigid link constraints at zero jounce.

    Shock motion ratio is wheel travel / shock travel. Bar roll stiffness is
    torsional rate times (bar twist / chassis roll)^2, for mirrored corners.
    These are nominal tangent rates, not settled FourPost measurements.
    """
    metrics = {}
    for axle in ("front", "rear"):
        side = data[axle]
        architecture = data["architecture"][axle]
        corner = CornerKinematics.from_vehicle(dict(data), axle)
        step = 1e-5
        plus, _, residual_plus = corner.solve_jounce(step, np.zeros(3))
        minus, _, residual_minus = corner.solve_jounce(-step, np.zeros(3))
        if max(residual_plus, residual_minus) > 1e-8:
            raise ValueError(f"{axle}: actuation derivative needs converged kinematics")
        angles_per_m = (plus - minus) / (2 * step)
        actuation = side["actuation"]
        rod = np.asarray(actuation["rod_mount_m"], dtype=float)
        attachment = actuation.get("rod_to", "lower")
        if attachment == "lower":
            velocity = np.cross(corner.lower_axis, rod - corner.lower_fore_i) * angles_per_m[0]
        elif attachment == "upper":
            velocity = np.cross(corner.upper_axis, rod - corner.upper_fore_i) * angles_per_m[1]
        else:
            raise ValueError(f"Unsupported rod attachment: {attachment}")
        mount = np.asarray(actuation["shock"]["mount_m"], dtype=float)
        bar_stiffness = 0.0
        if architecture == "direct":
            shock_travel = float(np.dot(_unit(rod - mount), velocity))
        elif architecture in {"bellcrank", "bellcrank_stabar"}:
            rocker = actuation["bellcrank"]
            pivot = np.asarray(rocker["pivot_m"], dtype=float)
            axis = _unit(rocker["axis"])
            pickups = {key: np.asarray(value, dtype=float) for key, value in rocker["pickups_m"].items()}
            link = _unit(pickups["rod"] - rod)
            angular_rate = _ratio(float(np.dot(link, velocity)),
                                  float(np.dot(link, np.cross(axis, pickups["rod"] - pivot))))
            shock_velocity = np.cross(axis, pickups["shock"] - pivot) * angular_rate
            shock_travel = float(np.dot(_unit(pickups["shock"] - mount), shock_velocity))
            if architecture == "bellcrank_stabar":
                bar = actuation["stabar"]
                arm = np.asarray(bar["arm_end_m"], dtype=float)
                end = np.asarray(bar["bar_end_m"], dtype=float)
                droplink = _unit(pickups["stabar"] - arm)
                pickup_velocity = np.cross(axis, pickups["stabar"] - pivot) * angular_rate
                arm_rate = _ratio(float(np.dot(droplink, pickup_velocity)),
                                  float(np.dot(droplink, np.cross([0., 1., 0.], arm - end))))
                track = 2 * abs(float(side["suspension"]["wheel_center_m"][1]))
                bar_stiffness = float(bar["rate_n_m_per_rad"]) * (track * arm_rate)**2
        else:
            raise ValueError(f"Unsupported suspension architecture: {architecture}")
        metrics[f"static_motion_ratio_{axle}"] = abs(_ratio(1.0, shock_travel))
        metrics[f"arb_roll_stiffness_{axle}_Nm_per_rad"] = bar_stiffness
    return metrics
