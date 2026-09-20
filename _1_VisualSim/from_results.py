"""Turn a BobLib simulation result into a BobVis scene.

The visual templates in ``visual_templates/`` expect a ``*_visual.npz`` of
hardpoint positions. Nothing in the repo produced one: the evaluations write a
Modelica result CSV, and their ``variable_filter`` keeps only scalar KnC and
handling metrics, so the geometry never leaves the solver. The bundled
templates name signals (``signals/visfrontaxleleft…``) that no current model
emits, which is why they cannot be opened against a real run.

This module closes that gap from the BobSim side, without touching BobLib:

* :data:`FRAME_MAP` names the MultiBody frame behind each suspension hardpoint,
  so :func:`variable_filter` can ask OpenModelica for exactly those and nothing
  else - 200-odd columns rather than 39,000;
* :func:`convert` reads the resulting CSV and writes both the ``*_visual.npz``
  and a matching visual template, so the pair is generated together and cannot
  drift.

    make visual-capture          # run the rig with geometry on, then convert

Frame paths are BobLib component paths, and a BobLib revision may rename them.
Every lookup is checked and reported by name rather than failing deep inside
the conversion.
"""

from __future__ import annotations

import argparse
import csv
import os
import re
import sys
from pathlib import Path
from typing import Any, Iterable

import numpy as np
import yaml

# ---------------------------------------------------------------------------
# Model geometry map
# ---------------------------------------------------------------------------

CORNERS: dict[str, tuple[str, str]] = {
    "fl": ("frAxleDW", "left"),
    "fr": ("frAxleDW", "right"),
    "rl": ("rrAxleDW", "left"),
    "rr": ("rrAxleDW", "right"),
}

#: Hardpoint -> the MultiBody frame whose origin ``r_0`` is that point.
FRAME_MAP: dict[str, str] = {
    "LowerFore_i": "{axle}.{side}WishboneUprightLoop.lowerFrameToFore.frame_b",
    "LowerAft_i": "{axle}.{side}WishboneUprightLoop.lowerFrameToAft.frame_b",
    "Lower_o": "{axle}.{side}WishboneUprightLoop.lowerFrame_o",
    "UpperFore_i": "{axle}.{side}WishboneUprightLoop.upperFrameToFore.frame_b",
    "UpperAft_i": "{axle}.{side}WishboneUprightLoop.upperFrameToAft.frame_b",
    "Upper_o": "{axle}.{side}WishboneUprightLoop.upperFrame_o",
    "Tie_i": "{axle}.{side}TieRod.frame_a",
    "Tie_o": "{axle}.{side}TieRod.frame_b",
    "WheelCenter": "{axle}.to{Side}WheelCenter.frame_b",
    "ContactPatch": "{axle}.{side}CP",
    "BellcrankPivot": "{axle}.{side}Bellcrank.mountFrame",
    "BellcrankRod": "{axle}.{side}Bellcrank.pickupFrame1",
    "BellcrankShock": "{axle}.{side}Bellcrank.pickupFrame2",
    "BellcrankStabar": "{axle}.{side}Bellcrank.pickupFrame3",
    "PushrodOuter": "{axle}.{side}Pushrod.frame_a",
    "PushrodInner": "{axle}.{side}Pushrod.frame_b",
    "ShockOuter": "{axle}.{side}ShockLinkage.frame_a",
    "ShockInner": "{axle}.{side}ShockLinkage.frame_b",
    "DroplinkLower": "{axle}.{side}Droplink.frame_a",
    "DroplinkUpper": "{axle}.{side}Droplink.frame_b",
    "BarEnd": "{axle}.stabar.to{Side}BarEnd.frame_b",
    "ArmEnd": "{axle}.stabar.to{Side}ArmEnd.frame_b",
}

#: The frame whose orientation gives each wheel's spin axis and heading.
WHEEL_FRAME = "{axle}.to{Side}WheelCenter.frame_b"

#: Link groups, as pairs of hardpoint names within one corner.
LINK_GROUPS: dict[str, list[tuple[str, str]]] = {
    "lower": [("LowerFore_i", "Lower_o"), ("LowerAft_i", "Lower_o")],
    "upper": [("UpperFore_i", "Upper_o"), ("UpperAft_i", "Upper_o")],
    "tie": [("Tie_i", "Tie_o")],
    "upright": [
        ("Lower_o", "Upper_o"), ("Lower_o", "WheelCenter"),
        ("Upper_o", "WheelCenter"), ("Tie_o", "WheelCenter"),
        ("WheelCenter", "ContactPatch"),
    ],
    "pushrod": [("PushrodOuter", "PushrodInner")],
    "bellcrank": [
        ("BellcrankPivot", "BellcrankRod"),
        ("BellcrankPivot", "BellcrankShock"),
        ("BellcrankPivot", "BellcrankStabar"),
    ],
    "shock": [("ShockOuter", "ShockInner")],
    "arb": [("DroplinkLower", "DroplinkUpper"), ("BarEnd", "ArmEnd"),
            ("ArmEnd", "DroplinkUpper")],
}

#: Cross-car links, as (corner, point) pairs.
AXLE_LINKS: list[tuple[tuple[str, str], tuple[str, str]]] = [
    (("fl", "LowerFore_i"), ("fr", "LowerFore_i")),
    (("rl", "LowerFore_i"), ("rr", "LowerFore_i")),
    (("fl", "UpperAft_i"), ("fr", "UpperAft_i")),
    (("rl", "UpperAft_i"), ("rr", "UpperAft_i")),
    (("fl", "LowerFore_i"), ("rl", "LowerFore_i")),
    (("fr", "LowerFore_i"), ("rr", "LowerFore_i")),
    (("fl", "UpperAft_i"), ("rl", "UpperAft_i")),
    (("fr", "UpperAft_i"), ("rr", "UpperAft_i")),
    (("fl", "BarEnd"), ("fr", "BarEnd")),
    (("rl", "BarEnd"), ("rr", "BarEnd")),
]

STYLE: dict[str, Any] = {
    "joints": {"radius": 0.012, "color": "#e0483c"},
    "links": {
        "default": {"radius": 0.010, "color": "#33383f"},
        "groups": {
            "lower": {"radius": 0.011, "color": "#33383f"},
            "upper": {"radius": 0.011, "color": "#33383f"},
            "tie": {"radius": 0.009, "color": "#5b636d"},
            "upright": {"radius": 0.013, "color": "#4a5159"},
            "chassis": {"radius": 0.015, "color": "#8a929b"},
            "pushrod": {"radius": 0.011, "color": "#2ca05e"},
            "bellcrank": {"radius": 0.012, "color": "#e08a2f"},
            "shock": {"radius": 0.014, "color": "#d64550"},
            "arb": {"radius": 0.008, "color": "#8a6fd6"},
        },
    },
}

#: Scalar signals worth plotting when the run happens to contain them.
PREFERRED_PLOTS: list[tuple[str, str]] = [
    ("Heave (m)", "frKnC.heave"),
    ("Roll (rad)", "frKnC.roll"),
    ("FL spring length (m)", "frKnC.leftSpringLength"),
    ("FL camber (rad)", "frKnC.leftGamma"),
    ("FL toe (rad)", "frKnC.leftToe"),
    ("RL spring length (m)", "rrKnC.leftSpringLength"),
    ("Handwheel (rad)", "handwheelAngle"),
    ("Lateral accel (m/s2)", "accY"),
    ("Yaw rate (rad/s)", "yawVel"),
]

TIRE_DEFAULTS = {"radius": 0.2045, "width": 0.1778}

#: A frame every BobLib double-wishbone car has. The rig names it at the top
#: level; VehicleSim nests the same axle under ``chassis.detailedChassis.``.
ANCHOR_FRAME = "frAxleDW.leftWishboneUprightLoop.lowerFrame_o.r_0[1]"

#: Per-tire vertical load: the rig's KnC channels, or VehicleSim's.
LOAD_SIGNALS: dict[str, tuple[str, ...]] = {
    "fl": ("frKnC.leftFz", "Fz_FL"),
    "fr": ("frKnC.rightFz", "Fz_FR"),
    "rl": ("rrKnC.leftFz", "Fz_RL"),
    "rr": ("rrKnC.rightFz", "Fz_RR"),
}

#: Each corner's MF5.2 tire, and the state the friction circles read from it.
#: The rig's tires carry no road forces, so only driving runs have these.
TIRE_COMPONENT = "{axle}.{side}Tire"
TIRE_STATE = ("Fx", "Fy", "Fz", "gamma")


def default_vehicle_yaml() -> Path:
    from _0_Utils.vehicle_io import vehicle_yaml_path

    return Path(vehicle_yaml_path())


#: The three outboard points that pin the upright, and what they let us derive.
UPRIGHT_TRIAD = ("Lower_o", "Upper_o", "Tie_o")
DERIVED_FROM_UPRIGHT = ("WheelCenter", "ContactPatch")


class ResultMappingError(RuntimeError):
    """Raised when a result file does not carry the expected geometry."""


# ---------------------------------------------------------------------------
# Names
# ---------------------------------------------------------------------------

def _frame(template: str, axle: str, side: str) -> str:
    return template.format(axle=axle, side=side, Side=side.capitalize())


def frame_paths(prefix: str = "") -> dict[tuple[str, str], str]:
    """``(corner, hardpoint) -> MultiBody frame path``, nested under ``prefix``."""
    return {
        (corner, point): prefix + _frame(template, axle, side)
        for corner, (axle, side) in CORNERS.items()
        for point, template in FRAME_MAP.items()
    }


def wheel_frames(prefix: str = "") -> dict[str, str]:
    return {
        corner: prefix + _frame(WHEEL_FRAME, axle, side)
        for corner, (axle, side) in CORNERS.items()
    }


def tire_state_paths(prefix: str = "") -> dict[tuple[str, str], str]:
    """``(corner, variable) -> result column`` for each tire's force state."""
    return {
        (corner, variable): f"{prefix}{_frame(TIRE_COMPONENT, axle, side)}.{variable}"
        for corner, (axle, side) in CORNERS.items()
        for variable in TIRE_STATE
    }


def detect_prefix(names: Iterable[str]) -> str:
    """Where the axles sit in this model: ``""`` on the rig, deeper in VehicleSim."""
    for name in names:
        if name.endswith(ANCHOR_FRAME):
            return name[: -len(ANCHOR_FRAME)]
    return ""


def variable_filter(extra: Iterable[str] = (), prefix: str = "") -> str:
    """An OpenModelica ``variableFilter`` selecting time, geometry and metrics.

    Whole-model output is 39k variables and gigabytes of CSV. This asks for the
    few hundred columns BobVis actually reads.
    """
    parts = ["time"]
    for path in sorted(set(frame_paths(prefix).values())):
        parts.append(re.escape(path) + r"\.r_0\[[123]\]")
    for path in sorted(set(wheel_frames(prefix).values())):
        parts.append(re.escape(path) + r"\.R\.T\[[123],[123]\]")
    parts.extend(re.escape(name) for name in sorted(set(tire_state_paths(prefix).values())))
    parts.extend(re.escape(name) for name in extra)
    parts.extend(re.escape(name) for _, name in PREFERRED_PLOTS)
    parts.extend(re.escape(name) for names in LOAD_SIGNALS.values() for name in names)
    return "|".join(parts)


def signal_name(corner: str, point: str, axis: str) -> str:
    return f"pos/{corner}_{point}_{axis}"


# ---------------------------------------------------------------------------
# Reading
# ---------------------------------------------------------------------------

def read_result_csv(path: Path) -> dict[str, np.ndarray]:
    """Load an OpenModelica CSV result into ``{name: array}``."""
    with open(path, "r", newline="", encoding="utf-8") as handle:
        reader = csv.reader(handle)
        header = [h.strip().strip('"') for h in next(reader)]
        rows = [row for row in reader if row]
    if not rows:
        raise ResultMappingError(f"{path} has a header but no samples")

    columns: dict[str, np.ndarray] = {}
    data = np.array(
        [[float(v) if v not in ("", "nan") else np.nan for v in row[: len(header)]]
         for row in rows],
        dtype=float,
    )
    for index, name in enumerate(header):
        columns[name] = data[:, index]
    return columns


def _vector(columns: dict[str, np.ndarray], frame: str, what: str) -> np.ndarray | None:
    keys = [f"{frame}.{what}[{i}]" for i in (1, 2, 3)]
    if not all(k in columns for k in keys):
        return None
    return np.stack([columns[k] for k in keys], axis=1)


def _kabsch(reference: np.ndarray, current: np.ndarray) -> tuple[np.ndarray, np.ndarray]:
    """Best-fit rigid transform taking ``reference`` (3,3) onto ``current`` (N,3,3).

    Returns ``(R, t)`` with shapes ``(N,3,3)`` and ``(N,3)``. Exact, not
    approximate, for three points on a rigid body.
    """
    ref_c = reference - reference.mean(axis=0)
    cur_mean = current.mean(axis=1)
    cur_c = current - cur_mean[:, None, :]

    H = np.einsum("nki,kj->nij", cur_c, ref_c)
    U, _, Vt = np.linalg.svd(H)
    d = np.sign(np.linalg.det(U @ Vt))
    D = np.zeros((len(current), 3, 3))
    D[:, 0, 0] = D[:, 1, 1] = 1.0
    D[:, 2, 2] = d
    R = U @ D @ Vt
    t = cur_mean - np.einsum("nij,j->ni", R, reference.mean(axis=0))
    return R, t


def _upright_hardpoints(vehicle_yaml: Path) -> dict[str, dict[str, np.ndarray]]:
    """Reference outboard hardpoints per corner, from ``vehicle.yml``.

    Right-hand corners mirror the left about the car's centreline, which is how
    the BobLib axle records are built (``Vector.mirrorXZ``).
    """
    with open(vehicle_yaml, "r", encoding="utf-8") as handle:
        vehicle = yaml.safe_load(handle)

    axle_for = {"fl": "front", "fr": "front", "rl": "rear", "rr": "rear"}
    keys = {
        "Lower_o": "lower_o_m", "Upper_o": "upper_o_m", "Tie_o": "tie_o_m",
        "WheelCenter": "wheel_center_m",
    }
    out: dict[str, dict[str, np.ndarray]] = {}
    for corner, axle in axle_for.items():
        suspension = vehicle[axle]["suspension"]
        mirror = np.array([1.0, -1.0 if corner.endswith("r") else 1.0, 1.0])
        out[corner] = {
            point: np.asarray(suspension[key], dtype=float) * mirror
            for point, key in keys.items()
            if key in suspension
        }
    return out


def _matrix(columns: dict[str, np.ndarray], frame: str) -> np.ndarray | None:
    keys = [[f"{frame}.R.T[{i},{j}]" for j in (1, 2, 3)] for i in (1, 2, 3)]
    if not all(k in columns for row in keys for k in row):
        return None
    return np.stack(
        [np.stack([columns[k] for k in row], axis=1) for row in keys], axis=1
    )


# ---------------------------------------------------------------------------
# Conversion
# ---------------------------------------------------------------------------

def convert(
    result_csv: Path,
    npz_path: Path,
    template_path: Path,
    tire_radius: float = TIRE_DEFAULTS["radius"],
    tire_width: float = TIRE_DEFAULTS["width"],
    vehicle_yaml: Path | None = None,
    metrics_csv: Path | None = None,
) -> tuple[Path, Path, dict[str, Any]]:
    """Write ``npz_path`` and ``template_path`` from a Modelica result CSV.

    ``metrics_csv``, when it exists, is recorded in the template so the viewer
    can show the run's metrics beside it. Returns the two paths plus a small
    summary for the caller to print.
    """
    vehicle_yaml = vehicle_yaml or default_vehicle_yaml()
    columns = read_result_csv(result_csv)
    if "time" not in columns:
        raise ResultMappingError(f"{result_csv} has no 'time' column")

    signals: dict[str, np.ndarray] = {"time": columns["time"]}
    points_cfg: dict[str, list[str]] = {}
    resolved: list[str] = []
    missing: list[str] = []

    prefix = detect_prefix(columns)
    for (corner, point), frame in frame_paths(prefix).items():
        r = _vector(columns, frame, "r_0")
        name = f"{corner}_{point}"
        if r is None:
            missing.append(f"{name}  <-  {frame}.r_0[1..3]")
            continue
        cols = []
        for axis, index in (("x", 0), ("y", 1), ("z", 2)):
            key = signal_name(corner, point, axis)
            signals[key] = r[:, index]
            cols.append(key)
        points_cfg[name] = cols
        resolved.append(name)

    if not points_cfg:
        raise ResultMappingError(
            f"{result_csv.name} carries no suspension geometry.\n"
            "Re-run the evaluation with the geometry variable filter:\n"
            "    make visual-capture\n"
            "A default evaluation run keeps only scalar metrics."
        )

    derived = _derive_upright_points(signals, points_cfg, vehicle_yaml)
    missing = [m for m in missing
               if not any(m.startswith(f"{d}  <-") for d in derived)]

    tires_cfg = _build_tires(columns, points_cfg, signals, tire_radius, tire_width, prefix)
    links_cfg = _build_links(points_cfg)
    ground_cfg = _build_ground(columns, points_cfg, signals)
    forces_cfg, warnings = _build_tire_forces(columns, signals, prefix, vehicle_yaml)
    plots_cfg = [
        {"name": label, "x": "time", "y": name}
        for label, name in PREFERRED_PLOTS
        if name in columns
    ]
    for plot in plots_cfg:
        signals[str(plot["y"])] = columns[str(plot["y"])]

    config = {
        "style": STYLE,
        "geometry": {"points": points_cfg, "links": links_cfg, "tires": tires_cfg},
        "render": {"speed": 1.0},
        "plots": plots_cfg,
        "camera": _build_camera(points_cfg),
    }
    if ground_cfg:
        config["ground"] = ground_cfg
    if forces_cfg:
        config["tire_forces"] = forces_cfg
    recorded_metrics = metrics_csv if metrics_csv is not None and Path(metrics_csv).is_file() else None
    if recorded_metrics is not None:
        config["metrics"] = {"path": _relative_posix(Path(recorded_metrics), template_path.parent)}

    npz_path.parent.mkdir(parents=True, exist_ok=True)
    template_path.parent.mkdir(parents=True, exist_ok=True)
    np.savez_compressed(npz_path, **signals)  # type: ignore[arg-type]

    header = (
        f"# Generated by `python -m _1_VisualSim.from_results` from\n"
        f"#   {result_csv.as_posix()}\n"
        f"# Regenerate with `make visual-capture`; do not hand-edit.\n"
    )
    with open(template_path, "w", encoding="utf-8") as handle:
        handle.write(header)
        yaml.safe_dump(config, handle, sort_keys=False, default_flow_style=False)

    summary = {
        "samples": int(len(signals["time"])),
        "points": len(points_cfg),
        "derived": [d for d in derived if not d.endswith("_axes")],
        "tires": len(tires_cfg),
        "plots": len(plots_cfg),
        "tire_forces": len(forces_cfg.get("corners") or {}),
        "metrics": None if recorded_metrics is None else str(recorded_metrics),
        "missing": missing,
        "warnings": warnings,
    }
    return npz_path, template_path, summary


def _relative_posix(path: Path, start: Path) -> str:
    """``path`` relative to ``start`` where possible, always with forward slashes."""
    try:
        return Path(os.path.relpath(path.resolve(), start.resolve())).as_posix()
    except ValueError:  # a different drive on Windows
        return path.resolve().as_posix()


def axle_friction(vehicle_yaml: Path) -> dict[str, dict[str, Any]]:
    """Peak-friction coefficients for each axle's tire, from the ``.tir`` that ``vehicle.yml`` names."""
    from _0_Utils.vehicle_io import load_yaml, parse_tir, tire_template_name, tire_templates_root
    from _1_VisualSim.tire_state import friction_coefficients

    vehicle = load_yaml(vehicle_yaml)
    friction: dict[str, dict[str, Any]] = {}
    for axle in ("front", "rear"):
        name = tire_template_name(vehicle, vehicle[axle])
        coeffs = friction_coefficients(parse_tir(tire_templates_root(vehicle) / f"{name}.tir"))
        friction[axle] = {"tir": name, **coeffs}
    return friction


def _build_tire_forces(
    columns: dict[str, np.ndarray],
    signals: dict[str, np.ndarray],
    prefix: str,
    vehicle_yaml: Path,
) -> tuple[dict[str, Any], list[str]]:
    """Per-tire forces plus each axle's friction model, for the friction circles.

    Needs ``Fx`` and ``Fy`` from the tire itself. ``Fz`` falls back to the load
    channel the ground layer uses, and camber to zero when the run dropped it.
    Returns the template block (empty when the run has no tire forces, as on
    the rig) and any warnings worth printing.
    """
    paths = tire_state_paths(prefix)
    corners: dict[str, Any] = {}
    for corner in CORNERS:
        fx, fy = paths[(corner, "Fx")], paths[(corner, "Fy")]
        if fx not in columns or fy not in columns:
            continue
        fz: str | None = paths[(corner, "Fz")]
        if fz not in columns:
            fz = next((n for n in LOAD_SIGNALS[corner] if n in columns), None)
        if fz is None:
            continue

        entry: dict[str, str] = {"axle": "front" if corner.startswith("f") else "rear"}
        sources = {"fx": fx, "fy": fy, "fz": fz, "gamma": paths[(corner, "gamma")]}
        for key, column in sources.items():
            if column not in columns:
                continue
            name = f"force/{corner}_{key}"
            signals[name] = columns[column]
            entry[key] = name
        corners[corner] = entry

    if not corners:
        return {}, []
    try:
        friction = axle_friction(vehicle_yaml)
    except (OSError, KeyError, TypeError) as exc:
        return {}, [f"tire forces found, but no friction model to compare them with: {exc}"]
    return {"corners": corners, "friction": friction}, []


def _derive_upright_points(
    signals: dict[str, np.ndarray],
    points_cfg: dict[str, list[str]],
    vehicle_yaml: Path,
) -> list[str]:
    """Rebuild wheel centres, contact patches and wheel axes from the uprights.

    OpenModelica's alias elimination drops variables it can prove redundant,
    and the wheel-centre frames and contact-patch Z go with them - they are
    rigidly tied to points that survive. Rather than recompiling the model
    without that optimisation, refit the upright: three surviving outboard
    points fix its pose exactly, so every other point on it follows, as does
    the wheel's spin axis.
    """
    references = _upright_hardpoints(vehicle_yaml)
    derived: list[str] = []

    for corner in CORNERS:
        triad = [f"{corner}_{p}" for p in UPRIGHT_TRIAD]
        if not all(name in points_cfg for name in triad):
            continue
        reference = references.get(corner, {})
        if not all(p in reference for p in UPRIGHT_TRIAD):
            continue

        ref_triad = np.stack([reference[p] for p in UPRIGHT_TRIAD])
        current = np.stack(
            [np.stack([signals[c] for c in points_cfg[name]], axis=1) for name in triad],
            axis=1,
        )
        R, t = _kabsch(ref_triad, current)

        wheel_centre = None
        if "WheelCenter" in reference:
            wheel_centre = np.einsum("nij,j->ni", R, reference["WheelCenter"]) + t

        for point, world in (
            ("WheelCenter", wheel_centre),
            # The road is z = 0 on the rig and in VehicleSim, so the patch sits below.
            ("ContactPatch", None if wheel_centre is None
             else wheel_centre * np.array([1.0, 1.0, 0.0])),
        ):
            name = f"{corner}_{point}"
            if world is None or name in points_cfg:
                continue
            cols = []
            for axis, index in (("x", 0), ("y", 1), ("z", 2)):
                key = signal_name(corner, point, axis)
                signals[key] = world[:, index]
                cols.append(key)
            points_cfg[name] = cols
            derived.append(name)

        # Wheel axes ride with the upright: +x forward, +y toward the car's left.
        for axis_key, unit in (("ex", np.array([1.0, 0.0, 0.0])),
                               ("ey", np.array([0.0, 1.0, 0.0]))):
            vec = np.einsum("nij,j->ni", R, unit)
            for axis, index in (("x", 0), ("y", 1), ("z", 2)):
                signals[f"tire/{corner}_{axis_key}_{axis}"] = vec[:, index]
        derived.append(f"{corner}_axes")

    return derived


def _build_tires(
    columns: dict[str, np.ndarray],
    points_cfg: dict[str, list[str]],
    signals: dict[str, np.ndarray],
    radius: float,
    width: float,
    prefix: str = "",
) -> dict[str, Any]:
    """Tire axes from the wheel-centre frame if the run kept it, else the upright fit."""
    tires: dict[str, Any] = {}
    for corner, frame in wheel_frames(prefix).items():
        centre = f"{corner}_WheelCenter"
        if centre not in points_cfg:
            continue
        R = _matrix(columns, frame)
        if R is None:
            if f"tire/{corner}_ex_x" in signals:
                tires[corner] = {
                    "center": centre,
                    "x": [f"tire/{corner}_ex_{a}" for a in "xyz"],
                    "y": [f"tire/{corner}_ey_{a}" for a in "xyz"],
                    "radius": float(radius),
                    "width": float(width),
                }
            continue
        # Modelica resolves R as body-from-world, so its rows are the body axes
        # expressed in world coordinates.
        ex, ey = R[:, 0, :], R[:, 1, :]
        cols: dict[str, list[str]] = {"x": [], "y": []}
        for axis_key, vec in (("ex", ex), ("ey", ey)):
            for axis, index in (("x", 0), ("y", 1), ("z", 2)):
                key = f"tire/{corner}_{axis_key}_{axis}"
                signals[key] = vec[:, index]
                cols["x" if axis_key == "ex" else "y"].append(key)
        tires[corner] = {
            "center": centre,
            "x": cols["x"],
            "y": cols["y"],
            "radius": float(radius),
            "width": float(width),
        }
    return tires


def _build_links(points_cfg: dict[str, list[str]]) -> dict[str, list[list[str]]]:
    links: dict[str, list[list[str]]] = {}
    for group, pairs in LINK_GROUPS.items():
        rows = [
            [f"{corner}_{a}", f"{corner}_{b}"]
            for corner in CORNERS
            for a, b in pairs
            if f"{corner}_{a}" in points_cfg and f"{corner}_{b}" in points_cfg
        ]
        if rows:
            links[group] = rows

    chassis = [
        [f"{c1}_{p1}", f"{c2}_{p2}"]
        for (c1, p1), (c2, p2) in AXLE_LINKS
        if f"{c1}_{p1}" in points_cfg and f"{c2}_{p2}" in points_cfg
    ]
    if chassis:
        links["chassis"] = chassis
    return links


def _build_ground(
    columns: dict[str, np.ndarray],
    points_cfg: dict[str, list[str]],
    signals: dict[str, np.ndarray],
) -> dict[str, Any]:
    """Load footprints wherever the run kept per-tire Fz; tracks once the car moves."""
    ground: dict[str, Any] = {}

    corners: dict[str, Any] = {}
    for corner, candidates in LOAD_SIGNALS.items():
        point = f"{corner}_ContactPatch"
        name = next((n for n in candidates if n in columns), None)
        if name is not None and point in points_cfg:
            signals[name] = columns[name]
            corners[corner] = {"point": point, "signal": name}
    if corners:
        ground["loads"] = {"radius": 0.22, "corners": corners}

    patches = [f"{c}_ContactPatch" for c in CORNERS if f"{c}_ContactPatch" in points_cfg]
    # The rig holds the car in place, where a trail would only be a dot.
    moved = any(
        float(np.ptp(signals[points_cfg[p][axis]])) > 1.0 for p in patches for axis in (0, 1)
    )
    if moved:
        ground["tracks"] = {
            "points": patches,
            "history": 3.0,
            "colors": ["#2b7fd4" if p.startswith("f") else "#d64550" for p in patches],
            "legend": "Tracks: last 3 s of each tire, front blue, rear red",
        }
    return ground


def _build_camera(points_cfg: dict[str, list[str]]) -> dict[str, Any]:
    rear, front = "rl_WheelCenter", "fl_WheelCenter"
    if rear not in points_cfg or front not in points_cfg:
        return {}
    return {
        "attach_to": rear,
        "forward_pair": [rear, front],
        "origin_offset": {"x": 1.3, "y": -0.8, "z": 0.1},
        "camera_offsets": {"back": 4.0, "height": 1.8},
    }


# ---------------------------------------------------------------------------
# CLI
# ---------------------------------------------------------------------------

def print_summary(npz_path: Path, template_path: Path, summary: dict[str, Any]) -> None:
    """What a conversion wrote, and how to open it."""
    print(f"[bobvis] data     {npz_path}")
    print(f"[bobvis] template {template_path}")
    print(f"[bobvis] {summary['samples']} samples, {summary['points']} points, "
          f"{summary['tires']} tires, {summary['plots']} plots")
    if summary["derived"]:
        print(f"[bobvis] refit from the uprights: {', '.join(summary['derived'])}")
    if summary.get("tire_forces"):
        print(f"[bobvis] friction circles for {summary['tire_forces']} tires")
    if summary.get("metrics"):
        print(f"[bobvis] metrics  {summary['metrics']}")
    for name in summary["missing"]:
        print(f"[bobvis] warning: unmapped hardpoint {name}", file=sys.stderr)
    for message in summary.get("warnings", []):
        print(f"[bobvis] warning: {message}", file=sys.stderr)
    print(f"[bobvis] open with: make visual VISUAL_CONFIG={template_path} "
          f"VISUAL_DATA={npz_path}")


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        prog="python -m _1_VisualSim.from_results",
        description="Convert a BobLib result CSV into a BobVis scene.",
    )
    parser.add_argument("result", type=Path, help="OpenModelica result CSV (*_res.csv)")
    parser.add_argument("-o", "--output", type=Path,
                        help="output .npz (default: alongside the result)")
    parser.add_argument("-t", "--template", type=Path,
                        help="output .yml (default: alongside the .npz)")
    parser.add_argument("--vehicle", type=Path, default=None,
                        help="vehicle.yml supplying reference upright hardpoints")
    parser.add_argument("--tire-radius", type=float, default=TIRE_DEFAULTS["radius"])
    parser.add_argument("--tire-width", type=float, default=TIRE_DEFAULTS["width"])
    return parser


def main(argv: list[str] | None = None) -> int:
    args = build_parser().parse_args(argv)

    if not args.result.is_file():
        print(f"[bobvis] no such file: {args.result}", file=sys.stderr)
        return 2

    npz_path = args.output or args.result.with_name(
        args.result.stem.replace("_res", "") + "_visual.npz"
    )
    template_path = args.template or npz_path.with_suffix(".yml")

    try:
        print_summary(*convert(
            args.result, npz_path, template_path,
            args.tire_radius, args.tire_width, args.vehicle,
        ))
    except ResultMappingError as exc:
        print(f"[bobvis] {exc}", file=sys.stderr)
        return 2
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
