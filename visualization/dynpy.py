"""Build reduced-model replay geometry from archived signals."""

from __future__ import annotations

from typing import Any, Mapping

import numpy as np
from numpy.typing import NDArray

from engines.dynpy.models import _body_to_world_rotation
from engines.dynpy.parameters import _combine_mass_properties, _mass_components
from engines.kinpy.lookup import NonlinearDoubleWishboneKinematics


def build_scene(
    signals: Mapping[str, NDArray[np.float64]], vehicle: Mapping[str, Any], dof: int,
) -> tuple[dict[str, Any], dict[str, NDArray[np.float64]]]:
    """## Reduced Model Scene

    Animate saved body and wheel states with the archived vehicle hardpoints.
    KinPy reconstructs wishbones and steering from corner travel and rack input.

    Parameters
    ----------
    signals : Mapping[str, NDArray[np.float64]]
        Archived response channels, in SI units.
    vehicle : Mapping[str, Any]
        Vehicle definition saved with the run.
    dof : int
        Reduced model fidelity, 3, 6, 10 or 14 DOF.

    Returns
    -------
    tuple[dict[str, Any], dict[str, NDArray[np.float64]]]
        BobVis configuration and geometry signals.
    """
    if dof not in (3, 6, 10, 14):
        raise ValueError("Replay requires a 3, 6, 10 or 14 DOF model.")
    time = np.asarray(signals["time"], dtype=float)
    required = ["x", "y", "yaw", "handwheelAngle"]
    if dof >= 6:
        required += ["z", "roll", "pitch"]
    for corner in ("FL", "FR", "RL", "RR"):
        required += [f"toe{corner}", f"camber{corner}", f"jounce{corner}"]
        required += [f"wheelCenterOffset{axis}{corner}" for axis in "XYZ"]
        if dof >= 10:
            required.append(f"wheel_angle_{corner.lower()}")
        if dof == 14:
            required.append(f"unsprung_z_{corner.lower()}")
    for name in ["time", *required]:
        if name not in signals or np.shape(signals[name]) != time.shape or not np.isfinite(signals[name]).all():
            raise ValueError(f"Replay requires a finite {name} channel at every sample.")
    zero = np.zeros_like(time)
    roll = signals["roll"] if dof >= 6 else zero
    pitch = signals["pitch"] if dof >= 6 else zero
    rotation = np.array([_body_to_world_rotation(angles) for angles in zip(roll, pitch, signals["yaw"])])
    cg = np.asarray(_combine_mass_properties(_mass_components(vehicle))[1])
    translation = np.column_stack((signals["x"], signals["y"], signals["z"] if dof >= 6 else zero))
    translation[:, 2] += cg[2]
    output = {"time": time}
    points: dict[str, list[str]] = {}
    tires: dict[str, Any] = {}
    links: dict[str, list[list[str]]] = {"body": [], "upper": [], "lower": [], "steering": [], "upright": []}
    kinematics = NonlinearDoubleWishboneKinematics(vehicle)
    rack = np.array([kinematics.rack_from_steering(float(angle)) for angle in signals["handwheelAngle"]])

    def vector(name: str, values: NDArray[np.float64]) -> list[str]:
        names = [f"{name}.{axis}" for axis in "xyz"]
        output.update({key: values[:, index] for index, key in enumerate(names)})
        return names

    def point(name: str, values: NDArray[np.float64]) -> None:
        points[name] = vector(name, values)

    def world(local: NDArray[np.float64]) -> NDArray[np.float64]:
        return np.einsum("nij,nj->ni", rotation, np.broadcast_to(local, (len(time), 3))) + translation

    point("body", translation)
    visible_joints = ["body"]

    for corner in ("fl", "fr", "rl", "rr"):
        axle = vehicle["front" if corner.startswith("f") else "rear"]
        nominal = np.array(axle["suspension"]["wheel_center_m"], dtype=float)
        if corner.endswith("r"):
            nominal[1] *= -1
        offset = np.column_stack([signals[f"wheelCenterOffset{axis}{corner.upper()}"] for axis in "XYZ"])
        wheel = world(nominal - cg + offset)
        if dof == 14:
            wheel[:, 2] = nominal[2] + signals[f"unsprung_z_{corner}"]
        point(corner, wheel)
        visible_joints.append(corner)
        geometry = kinematics.front if corner.startswith("f") else kinematics.rear
        mirror = np.array([1., -1. if corner.endswith("r") else 1., 1.])
        corner_rack = rack * mirror[1] if corner.startswith("f") else zero
        moving: dict[str, list[NDArray[np.float64]]] = {name: [] for name in ("lower_o", "upper_o", "tie_o")}
        guess = np.zeros(3)
        for travel, displacement in zip(signals[f"jounce{corner.upper()}"], corner_rack):
            guess, pose, residual = geometry.solve_jounce(float(travel), guess, rack_displacement_m=float(displacement))
            if residual > 1e-8:
                raise ValueError(f"Could not reconstruct {corner.upper()} suspension geometry.")
            for name in moving:
                moving[name].append(np.asarray(getattr(pose, name)))
        for name, values in moving.items():
            point(f"{corner}_{name}", world(np.asarray(values) * mirror - cg))
        for name in ("lower_fore_i", "lower_aft_i", "upper_fore_i", "upper_aft_i"):
            point(f"{corner}_{name}", world(np.asarray(getattr(geometry, name)) * mirror - cg))
        rack_pickup = np.tile(geometry.rack_pickup_initial, (len(time), 1))
        rack_pickup[:, 1] += corner_rack
        point(f"{corner}_rack", world(rack_pickup * mirror - cg))
        for arm in ("upper", "lower"):
            for end in ("fore", "aft"):
                links[arm].append([f"{corner}_{arm}_{end}_i", f"{corner}_{arm}_o"])
            links["body"].append([f"{corner}_{arm}_fore_i", f"{corner}_{arm}_aft_i"])
        links["steering"].append([f"{corner}_rack", f"{corner}_tie_o"])
        links["upright"].extend([[f"{corner}_lower_o", f"{corner}_upper_o"],
                                 [f"{corner}_lower_o", corner], [f"{corner}_upper_o", corner],
                                 [f"{corner}_tie_o", corner]])
        visible_joints.extend(f"{corner}_{name}" for name in (
            *moving, "rack", "lower_fore_i", "lower_aft_i", "upper_fore_i", "upper_aft_i",
        ))
        toe = signals[f"toe{corner.upper()}"]
        camber = signals[f"camber{corner.upper()}"]
        ex = np.column_stack((np.cos(toe), np.sin(toe), zero))
        ey = np.column_stack((-np.sin(toe)*np.cos(camber), np.cos(toe)*np.cos(camber), -np.sin(camber)))
        tires[corner] = {
            "center": corner, "radius": float(axle["wheel"]["radius_m"]),
            "width": float(axle["wheel"]["radius_m"]) * float(axle["wheel"].get("rim_radius_ratio", 0.625))
            * float(axle["wheel"].get("rim_width_ratio", 1.4)),
            "x": vector(corner + "_x", np.einsum("nij,nj->ni", rotation, ex)),
            "y": vector(corner + "_y", np.einsum("nij,nj->ni", rotation, ey)),
        }
        if dof >= 10:
            output[corner + "_spin"] = np.asarray(signals[f"wheel_angle_{corner}"])
            tires[corner]["spin"] = corner + "_spin"
    for arm in ("upper", "lower"):
        for first, second, end in (("fl", "fr", "fore"), ("rl", "rr", "aft")):
            links["body"].append([f"{first}_{arm}_{end}_i", f"{second}_{arm}_{end}_i"])
        for side in ("l", "r"):
            links["body"].append([f"f{side}_{arm}_aft_i", f"r{side}_{arm}_fore_i"])
    descriptions = {3: "Four-tire planar body", 6: "Sprung body motion", 10: "Sprung body and wheel rotation",
                    14: "Sprung body, wheel rotation and unsprung motion"}
    config = {
        "representation": f"DynPy · {dof} DOF · {descriptions[dof]} · KinPy linkages",
        "geometry": {"points": points, "links": links, "tires": tires, "joints": visible_joints},
        "style": {"joints": {"radius": 0.009, "color": "#a7b8cc"},
                  "links": {"default": {"radius": 0.008, "color": "#8ba1bd"},
                            "groups": {"upper": {"color": "#9cb6d4"}, "lower": {"color": "#9cb6d4"},
                                       "steering": {"color": "#d46b7d"}, "upright": {"color": "#e2ac54"}}}},
        "camera": {"attach_to": "body", "forward_pair": ["rl_lower_fore_i", "fl_lower_fore_i"]},
        "ground": {"tracks": {"points": ["fl", "rl"], "history": 3.0}},
    }
    return config, output
