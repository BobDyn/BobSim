"""Plot measurements from BobLib's native heave, roll, and steering protocol."""
from __future__ import annotations

import math
from typing import Any

import numpy as np

MEASUREMENTS = {"camber_deg": ("leftGamma", 180 / math.pi, "Camber", "deg"),
                "toe_deg": ("leftToe", 180 / math.pi, "Toe", "deg"),
                "caster_deg": ("leftCaster", 180 / math.pi, "Caster", "deg"),
                "kpi_deg": ("leftKpi", 180 / math.pi, "KPI", "deg"),
                "mech_trail_mm": ("leftMechTrail", 1000, "Mechanical trail", "mm"),
                "scrub_mm": ("leftMechScrub", 1000, "Scrub radius", "mm")}
PHASES = (("bump", "heave_mm", "Heave (chassis up)", "mm"),
          ("roll", "roll_deg", "Roll", "deg"),
          ("steer", "pinion_deg", "Steer (pinion angle)", "deg"))


def metadata() -> list[dict]:
    """Describe axes and distinguish projected geometry from force response."""
    result = []
    for phase, axis, label, unit in PHASES:
        measurements = {key: (title, y_unit) for key, (_, _, title, y_unit) in MEASUREMENTS.items()}
        measurements.update(rc_height_mm=("Geometric RC height", "mm"))
        if phase == "roll":
            measurements.update(force_rc_height_mm=("Force-based equivalent RC height", "mm"))
        measurements.update(rc_y_mm=("Geometric RC lateral position", "mm"))
        if phase != "steer":
            measurements.update(jacking_ratio=("Jacking / applied force", "N/N"))
        if phase == "bump":
            measurements.update(anti_dive_pct=("Front anti-dive", "%"),
                                anti_lift_pct=("Rear anti-lift", "%"),
                                anti_squat_pct=("Rear anti-squat (RWD)", "%"))
        if phase == "roll":
            measurements.update(reaction_per_fy_m=("Moment / applied force", "m"),
                                anti_roll_pct=("Geometric anti-roll (axle-normalized)", "%"))
        for key, (title, y_unit) in measurements.items():
            result.append({"id": phase + "_" + key, "label": title, "unit": y_unit,
                           "x_id": axis, "x_label": label, "x_unit": unit, "y_label": title})
    return result


def geometric_rc(row: dict) -> tuple[float | None, float | None]:
    """Intersect front-view wishbone and contact-to-IC lines in world Y/Z.

    The inboard frame is the midpoint of the two wishbone pickups, matching
    BobSim's existing front-view projection convention. Heights are relative to
    the mean contact plane. Homogeneous lines also handle an IC at infinity;
    an undefined roll centre returns missing values, never a fabricated zero.
    """
    def point(name):
        return np.array([row[name + ".r_0[2]"], row[name + ".r_0[3]"], 1.0])

    try:
        lines = []
        contacts = []
        for side in ("left", "right"):
            base = "axle." + side + "WishboneUprightLoop."
            lower = np.cross(point(base + "lowerFrame_i"), point(base + "lowerFrame_o"))
            upper = np.cross(point(base + "upperFrame_i"), point(base + "upperFrame_o"))
            ic = np.cross(lower, upper)
            contact = point("axle." + side + "CP")
            line = np.cross(contact, ic)
            norm = np.linalg.norm(line[:2])
            if norm < 1e-12:
                return None, None
            lines.append(line / norm)
            contacts.append(contact)
        rc = np.cross(*lines)
        if abs(rc[2]) < 1e-10:
            return None, None
        y, z = rc[:2] / rc[2]
        return float((z - (contacts[0][1] + contacts[1][1]) / 2) * 1000), float(y * 1000)
    except KeyError:
        return None, None


def roll_axis_reaction(pulse: dict, tail: dict, lateral_load: float) -> tuple:
    """Return loaded, unloaded, incremental and load-normalized rig reactions.

    Positive moment is the suspension's reaction onto the rig about world +X
    through the origin. It is the negative of the torque applied by the exact
    roll actuator. The normalized value is a signed moment arm, not an RC height.
    """
    signal = "chassisActuator.rollDOF.tau"
    if signal not in pulse or signal not in tail:
        return None, None, None, None
    loaded, unloaded = -pulse[signal], -tail[signal]
    delta = loaded - unloaded
    return loaded, unloaded, delta, delta / lateral_load if abs(lateral_load) >= 1e-3 else None


def force_rc_height(pulse: dict, tail: dict, side: str) -> float | None:
    """Return the total rig reaction's equivalent height above the contact plane.

    The equivalent lateral force acts on the world centreline (y=0). Its
    world-X moment is -z*Fy. Include the separately grounded front steering
    support in the moment balance, then shift from world origin to the mean
    unloaded contact plane. This is specific to the rig's applied force split;
    it does not locate a unique three-dimensional roll centre.

    Parameters
    ----------
    pulse, tail : dict
        Loaded and unloaded native samples at the same prescribed pose.
    side : str
        Axle name; the front requires the separate steering support torque.

    Returns
    -------
    float or None
        Equivalent height in millimetres, or missing for invalid contact,
        negligible excitation, or unavailable measurements.
    """
    try:
        fy = pulse["knc.fy"] - tail["knc.fy"]
        if abs(fy) < 1e-3 or min(pulse["knc.leftFz"], pulse["knc.rightFz"]) <= 0:
            return None
        moment = -(pulse["chassisActuator.rollDOF.tau"] - tail["chassisActuator.rollDOF.tau"])
        if side == "front":
            moment += pulse["steerPosition.flange.tau"] - tail["steerPosition.flange.tau"]
        ground = sum(tail[f"axle.{wheel}CP.r_0[3]"] for wheel in ("left", "right")) / 2
        return 1000 * (-moment / fy - ground)
    except KeyError:
        return None


def sprung_cg_height(row: dict, vehicle: dict) -> float | None:
    """Transform the reference sprung CG into the prescribed rig pose.

    Parameters
    ----------
    row : dict
        Native unloaded pose, with heave, roll and world contact positions.
    vehicle : dict
        Sprung and driver masses and CGs in the chassis reference coordinates.

    Returns
    -------
    float or None
        CG height above the mean contact plane in metres; invalid references
        remain missing. The rig translates along chassis Z then rotates about X.
    """
    try:
        masses = [vehicle[key] for key in ("sprung_mass", "driver_mass")]
        mass = sum(m["mass_kg"] for m in masses)
        if mass <= 0:
            return None
        y, z = [sum(m["mass_kg"] * m["cg_m"][i] for m in masses) / mass for i in (1, 2)]
        roll, heave = row["knc.roll"], row["knc.heave"]
        ground = sum(row[f"axle.{wheel}CP.r_0[3]"] for wheel in ("left", "right")) / 2
        height = y * math.sin(roll) + (z + heave) * math.cos(roll) - ground
        return height if math.isfinite(height) and height > 1e-9 else None
    except KeyError:
        return None


def curves(rows: list[dict], vehicle: dict | None = None, side: str = "front", *, traction: bool = False) -> dict:
    """Sample unloaded geometry and subtract same-pose tails from force pulses."""
    times = np.array([row["time"] for row in rows])

    def at(t):
        return rows[int(np.argmin(np.abs(times - t)))]

    steered = times[-1] >= 831 and "inputs.steer" in rows[0]
    offset = 357 if steered else 0
    result: dict[str, Any] = {"curves": {}, "x_axes": {}}
    groups = [("bump", [at(offset + t) for t in range(5, 56, 5)], "knc.heave", 1000, "heave_mm"),
              ("roll", [at(offset + t) for t in range(66, 117, 5)], "knc.roll", 180 / math.pi, "roll_deg")]
    if steered:
        groups.append(("steer", [at(119 * i + 30) for i in range(7)], "inputs.steer", 180 / math.pi, "pinion_deg"))
    for phase, sampled, x_signal, scale, axis in groups:
        sampled.sort(key=lambda row: row[x_signal] * scale)
        result["x_axes"][axis] = [row[x_signal] * scale for row in sampled]
        for key, (signal, factor, _, _) in MEASUREMENTS.items():
            result["curves"][phase + "_" + key] = [row["knc." + signal] * factor for row in sampled]
        rc = [geometric_rc(row) for row in sampled]
        result["curves"][phase + "_rc_height_mm"] = [p[0] for p in rc]
        result["curves"][phase + "_rc_y_mm"] = [p[1] for p in rc]
        if phase == "steer":
            continue
        force = "knc.fx" if phase == "bump" else "knc.fy"
        jack: list[float | None] = []
        ratio: list[float | None] = []
        force_rc: list[float | None] = []
        reactions: list[tuple] = []
        for tail in sampled:
            pulse = at(tail["time"] - 2)
            amplitude = pulse.get(force, 0) - tail.get(force, 0)
            if phase == "roll":
                reactions.append(roll_axis_reaction(pulse, tail, amplitude))
            if abs(amplitude) < 1e-3 or "knc.jackingForce" not in pulse:
                jack.append(None)
                ratio.append(None)
                force_rc.append(None)
                continue
            delta = -(pulse["knc.jackingForce"] - tail["knc.jackingForce"])
            jack.append(delta)
            ratio.append(delta / amplitude)
            if phase == "roll":
                force_rc.append(force_rc_height(pulse, tail, side))
        result["curves"][phase + "_jacking_n"] = jack
        result["curves"][phase + "_jacking_ratio"] = ratio
        if phase == "roll":
            for index, name in enumerate(("reaction_nm", "unloaded_reaction_nm", "load_reaction_nm",
                                          "reaction_per_fy_m")):
                result["curves"]["roll_" + name] = [values[index] for values in reactions]
        if vehicle:
            front, rear = [vehicle[key]["suspension"]["wheel_center_m"] for key in ("front", "rear")]
            length = abs(front[0] - rear[0])
            # These are axle-force-normalized geometric measures, not whole-car
            # anti percentages (which also need brake/drive force distribution).
            sign = -1 if phase == "bump" and side == "front" else 1
            key = ("anti_roll_pct" if phase == "roll" else "anti_dive_pct" if side == "front"
                   else "anti_squat_pct" if traction else "anti_lift_pct")
            if phase == "roll":
                # Net jacking is the SUM of vertical reactions. It can vanish
                # while their roll moment is nonzero, so it cannot define anti-roll.
                # This geometric proxy is RC height / posed sprung CG height,
                # with both heights measured from the same contact plane.
                heights = [sprung_cg_height(row, vehicle) for row in sampled]
                result["curves"]["roll_anti_roll_pct"] = [
                    100 * rc_height / (1000 * cg_height)
                    if rc_height is not None and cg_height is not None and cg_height > 1e-9 else None
                    for (rc_height, _), cg_height in zip(rc, heights)]
                result["curves"]["roll_force_rc_height_mm"] = force_rc
            else:
                values = []
                for r, tail in zip(ratio, sampled):
                    h = sprung_cg_height(tail, vehicle)
                    pulse = at(tail["time"] - 2)
                    contact = all(row.get(f"knc.{wheel}Fz", 0) > 0
                                  for row in (pulse, tail) for wheel in ("left", "right"))
                    values.append(sign * 100 * r * length / h
                                  if r is not None and h is not None and contact else None)
                result["curves"][phase + "_" + key] = values
    return result
