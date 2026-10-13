"""Build reduced-model replay geometry from archived signals."""

from __future__ import annotations

from typing import Any, Mapping

import numpy as np
from numpy.typing import NDArray

from engines.dynpy.models import _body_to_world_rotation
from engines.dynpy.parameters import _combine_mass_properties, _mass_components


def build_scene(
    signals: Mapping[str, NDArray[np.float64]], vehicle: Mapping[str, Any], dof: int,
) -> tuple[dict[str, Any], dict[str, NDArray[np.float64]]]:
    """## Reduced Model Scene

    Represent only the motion resolved by the saved model. Suspension is drawn
    as corner connections, not as independently simulated MBD links.

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
    required = ["x", "y", "yaw"]
    if dof >= 6:
        required += ["z", "roll", "pitch"]
    for corner in ("FL", "FR", "RL", "RR"):
        required += [f"toe{corner}", f"camber{corner}"]
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
    links: dict[str, list[list[str]]] = {"body": [], "suspension": [], "unsprung": []}

    def vector(name: str, values: NDArray[np.float64]) -> list[str]:
        names = [f"{name}.{axis}" for axis in "xyz"]
        output.update({key: values[:, index] for index, key in enumerate(names)})
        return names

    def point(name: str, values: NDArray[np.float64]) -> None:
        points[name] = vector(name, values)

    def world(local: NDArray[np.float64]) -> NDArray[np.float64]:
        return np.einsum("nij,nj->ni", rotation, np.broadcast_to(local, (len(time), 3))) + translation

    point("body", translation)
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
        mount = nominal - cg
        mount[2] = 0.0
        point(corner + "_body", world(mount))
        if dof >= 6:
            links["suspension"].append([corner + "_body", corner])
        if dof == 14:
            marker = wheel.copy()
            marker[:, 2] += 0.08
            point(corner + "_unsprung", marker)
            links["unsprung"].append([corner, corner + "_unsprung"])
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
    for first, second in (("fl", "fr"), ("fr", "rr"), ("rr", "rl"), ("rl", "fl")):
        links["body"].append([first + "_body", second + "_body"])
    descriptions = {3: "Planar body", 6: "Sprung body motion", 10: "Sprung body and wheel rotation",
                    14: "Sprung body, wheel rotation and unsprung motion"}
    config = {
        "representation": f"DynPy · {dof} DOF · {descriptions[dof]}",
        "geometry": {"points": points, "links": links, "tires": tires},
        "style": {"joints": {"radius": 0.012, "color": "#a7b8cc"},
                  "links": {"default": {"radius": 0.013, "color": "#8ba1bd"},
                            "groups": {"suspension": {"color": "#d46b7d"}, "unsprung": {"color": "#e2ac54"}}}},
        "camera": {"attach_to": "body", "forward_pair": ["rl_body", "fl_body"]},
        "ground": {"tracks": {"points": ["fl", "rl"], "history": 3.0}},
    }
    return config, output
