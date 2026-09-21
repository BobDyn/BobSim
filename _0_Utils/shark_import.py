"""Import Lotus SHARK (.shk) suspension geometry into a BobSim vehicle.yml.

A SHARK file holds one corner of one axle in millimetres and no mass, aero,
tyre or powertrain data. The import merges only suspension, steering and
actuation geometry into a copy of an existing vehicle.yml.
See docs/conventions.md for the target coordinate convention.
"""

from __future__ import annotations

import argparse
import copy
import hashlib
import json
import math
from pathlib import Path
from typing import Any, Sequence

import yaml

from _0_Utils.vehicle_io import load_yaml, repo_root


MM_PER_M = 1000.0

# Required for any double-wishbone corner.
REQUIRED_POINTS = (
    "Lower wishbone front pivot",
    "Lower wishbone rear pivot",
    "Lower wishbone outer ball joint",
    "Upper wishbone front pivot",
    "Upper wishbone rear pivot",
    "Upper wishbone outer ball joint",
    "Outer track rod ball joint",
    "Inner track rod ball joint",
    "Wheel centre point",
)

# Also required for a pushrod/bellcrank corner.
BELLCRANK_POINTS = (
    "Push rod wishbone end",
    "Push rod rocker end",
    "Damper to body point",
    "Damper to rocker point",
    "Rocker axis 1st point",
    "Rocker axis 2nd point",
)

# vehicle.yml key -> SHARK point name.
SUSPENSION_POINT_MAP = {
    "lower_fore_i_m": "Lower wishbone front pivot",
    "lower_aft_i_m": "Lower wishbone rear pivot",
    "lower_o_m": "Lower wishbone outer ball joint",
    "upper_fore_i_m": "Upper wishbone front pivot",
    "upper_aft_i_m": "Upper wishbone rear pivot",
    "upper_o_m": "Upper wishbone outer ball joint",
    "tie_o_m": "Outer track rod ball joint",
    "wheel_center_m": "Wheel centre point",
}

# Wheel centre agreement (mm) below which two files are taken to share a frame.
FRAME_MATCH_TOLERANCE_MM = 0.05


class SharkImportError(RuntimeError):
    """Raised when a SHARK file cannot be imported without guessing."""


def _numbers(line: str) -> list[float]:
    try:
        return [float(token) for token in line.split()]
    except ValueError:
        return []


def parse_shark(path: str | Path) -> dict[str, Any]:
    """Return the named hardpoints of a SHARK file, in millimetres.

    Values are xyz tuples. The dunder keys hold file metadata: `__template__`,
    `__loaded_radius_mm__` and `__titles__`.
    """
    lines = Path(path).read_text(encoding="utf-8", errors="ignore").splitlines()

    try:
        settings_idx = lines.index("TEMP_SETTINGS")
    except ValueError as exc:
        raise SharkImportError(f"{path}: no TEMP_SETTINGS block; not a SHARK file?") from exc

    # TEMP_SETTINGS: <count> / <template name> / <nparts> <npoints> ... / part names
    header = _numbers(lines[settings_idx + 3])
    if len(header) < 2:
        raise SharkImportError(f"{path}: malformed TEMP_SETTINGS header")
    n_parts, n_points = int(header[0]), int(header[1])

    template_name = lines[settings_idx + 2].strip()

    # Each point block is: name, 5 description lines, coords, 9 ints, 7 ints.
    cursor = settings_idx + 4 + n_parts
    names: list[str] = []
    for _ in range(n_points):
        if cursor >= len(lines):
            raise SharkImportError(f"{path}: TEMP_SETTINGS ended early")
        names.append(lines[cursor].strip())
        cursor += 9

    coords, scalars = _geometry_block(lines, path)
    if len(coords) < len(names):
        raise SharkImportError(
            f"{path}: found {len(names)} point names but only {len(coords)} coordinate triples"
        )

    points: dict[str, Any] = {name: coords[i] for i, name in enumerate(names)}
    points["__template__"] = template_name
    points["__loaded_radius_mm__"] = scalars[0] if scalars else None
    points["__titles__"] = _titles(lines)
    return points


def _geometry_block(
    lines: Sequence[str], path: str | Path
) -> tuple[list[tuple[float, float, float]], list[float]]:
    """Return (xyz triples, trailing scalars) from the suspension geometry block.

    The block header names the assembly slot, not the axle. The first trailing
    scalar is the loaded rolling radius (see `assess_z_datum`).
    """
    for idx, line in enumerate(lines):
        if line.strip() in {"FRONT SUSPENSION", "REAR SUSPENSION"}:
            triples: list[tuple[float, float, float]] = []
            scalars: list[float] = []
            for row in lines[idx + 2:]:
                values = _numbers(row)
                if len(values) == 3:
                    triples.append((values[0], values[1], values[2]))
                elif len(values) == 1:
                    scalars.append(values[0])
                else:
                    break
            return triples, scalars
    raise SharkImportError(f"{path}: no suspension geometry block found")


def _titles(lines: Sequence[str]) -> list[str]:
    """Return the free-text TITLES entries, which may hold a datum note."""
    try:
        idx = lines.index("TITLES")
    except ValueError:
        return []
    count_values = _numbers(lines[idx + 1]) if idx + 1 < len(lines) else []
    count = int(count_values[0]) if count_values else 0
    return [lines[idx + 2 + offset].strip() for offset in range(count) if idx + 2 + offset < len(lines)]


def _to_m(point: tuple[float, float, float]) -> list[float]:
    return [round(value / MM_PER_M, 9) for value in point]


def _distance(a: Sequence[float], b: Sequence[float]) -> float:
    return math.dist(tuple(a), tuple(b))


def detect_axle(points: dict[str, Any], vehicle: dict[str, Any]) -> tuple[str, float]:
    """Return the axle nearest the wheel centre and the offset in mm."""
    wheel_centre = points["Wheel centre point"]
    best: tuple[str, float] | None = None
    for axle in ("front", "rear"):
        baseline = vehicle[axle]["suspension"]["wheel_center_m"]
        baseline_mm = [value * MM_PER_M for value in baseline]
        planar = math.dist(wheel_centre[:2], baseline_mm[:2])
        if best is None or planar < best[1]:
            best = (axle, planar)
    assert best is not None
    return best


def verify_shared_frame(points: dict[str, Any], vehicle: dict[str, Any], axle: str) -> dict[str, float]:
    """Refuse the import unless the SHARK file and vehicle.yml share a frame."""
    shark_wc = points["Wheel centre point"]
    baseline_wc = [value * MM_PER_M for value in vehicle[axle]["suspension"]["wheel_center_m"]]
    dx, dy, dz = (shark_wc[i] - baseline_wc[i] for i in range(3))

    if abs(dx) > FRAME_MATCH_TOLERANCE_MM or abs(dy) > FRAME_MATCH_TOLERANCE_MM:
        raise SharkImportError(
            "Cannot establish a shared coordinate frame. The SHARK wheel centre differs "
            f"from the baseline {axle} wheel centre by dx={dx:.3f} mm, dy={dy:.3f} mm "
            f"(tolerance {FRAME_MATCH_TOLERANCE_MM} mm).\n"
            "The vertical datum cannot be inferred without a shared in-plane origin. "
            "Establish the datum explicitly before importing."
        )
    return {"dx_mm": dx, "dy_mm": dy, "dz_mm": dz}


# A contact patch this close to z = 0 is taken as sitting on the ground plane.
GROUND_PLANE_TOLERANCE_MM = 0.05

# Curves that move with the vertical datum. They are withheld while it is unresolved.
Z_DEPENDENT_CURVE_IDS = frozenset(
    {
        "bump_rc_z_mm", "roll_rc_z_mm",
        "bump_front_ic_z_mm", "roll_front_ic_z_mm",
        "bump_rc_height_mm", "roll_rc_height_mm",
        "bump_rc_migration_mm", "roll_rc_migration_mm",
        "bump_front_swing_arm_mm", "roll_front_swing_arm_mm",
    }
)

Z_DATUM_UNRESOLVED_WARNING = (
    "VERTICAL DATUM UNRESOLVED - roll-centre and swing-arm curves are withheld. "
    "The SHARK loaded radius corroborates the baseline's ground-plane datum but not "
    "the SHARK file's own wheel centre. See docs/conventions.md."
)


def assess_z_datum(points: dict[str, Any], vehicle: dict[str, Any], axle: str) -> dict[str, Any]:
    """Decide whether the vertical datum can be established from the file itself.

    TODO(datum): unresolved for 2027_RR_SuV12. Confirm with the exporter whether
    the SHARK wheel-centre z offset is a ride-height change or a datum shift.
    """
    loaded_radius = points.get("__loaded_radius_mm__")
    titles = points.get("__titles__") or []
    shark_wc_z = points["Wheel centre point"][2]
    baseline_wc_z = float(vehicle[axle]["suspension"]["wheel_center_m"][2]) * MM_PER_M

    evidence: dict[str, Any] = {
        "loaded_radius_mm": loaded_radius,
        "titles": list(titles),
        "shark_wheel_centre_z_mm": shark_wc_z,
        "baseline_wheel_centre_z_mm": baseline_wc_z,
        "dz_mm": shark_wc_z - baseline_wc_z,
    }

    if loaded_radius is None:
        evidence["status"] = "unresolved"
        evidence["reason"] = (
            "The file carries no loaded-radius scalar and no TITLES annotation, so "
            "nothing in it bears on the vertical datum."
        )
        return evidence

    shark_cp = shark_wc_z - loaded_radius
    baseline_cp = baseline_wc_z - loaded_radius
    evidence["shark_implied_contact_patch_mm"] = shark_cp
    evidence["baseline_implied_contact_patch_mm"] = baseline_cp

    shark_on_ground = abs(shark_cp) <= GROUND_PLANE_TOLERANCE_MM
    baseline_on_ground = abs(baseline_cp) <= GROUND_PLANE_TOLERANCE_MM

    if shark_on_ground and baseline_on_ground:
        evidence["status"] = "shared_ground_plane"
        evidence["reason"] = (
            "Both wheel centres sit one loaded radius above z = 0, so the two files "
            "share a ground-plane datum and z may be taken raw."
        )
        return evidence

    evidence["status"] = "unresolved"
    evidence["reason"] = (
        "Conflicting datum evidence. Reading the trailing scalar as the loaded rolling "
        f"radius ({loaded_radius:.3f} mm), a shared ground-plane datum implies a contact "
        f"patch at z = 0. The baseline lands at {baseline_cp:+.3f} mm (consistent); the "
        f"SHARK wheel centre lands at {shark_cp:+.3f} mm (inconsistent). "
        + (
            "TITLES carries no annotation to settle it. "
            if not titles
            else f"TITLES says: {titles!r}. "
        )
        + f"The {shark_wc_z - baseline_wc_z:+.3f} mm offset is therefore NOT confirmed as a "
        "ride-height change, and z-dependent curves are withheld until it is."
    )
    return evidence


def check_single_side(points: dict[str, Any]) -> None:
    """Refuse geometry on both sides. The schema stores one side and mirrors it."""
    ys = [
        value[1]
        for name, value in points.items()
        if not name.startswith("__") and "C of G" not in name
    ]
    if not ys:
        raise SharkImportError("No hardpoints found")
    if min(ys) < 0.0 < max(ys):
        raise SharkImportError(
            "SHARK file spans both sides of the centreline (y ranges "
            f"{min(ys):.1f} .. {max(ys):.1f} mm). The boblib.vehicle.v1 schema stores one "
            "side and mirrors it, so asymmetric geometry cannot be represented. "
            "Refusing to pick a side or average."
        )


def _rod_attachment(points: dict[str, Any]) -> str:
    """Decide whether the pushrod picks up on the lower or upper wishbone."""
    rod = points["Push rod wishbone end"]
    to_lower = _distance(rod, points["Lower wishbone outer ball joint"])
    to_upper = _distance(rod, points["Upper wishbone outer ball joint"])
    return "lower" if to_lower <= to_upper else "upper"


# Max carried stabar arm, as a multiple of the largest SHARK-defined arm.
STABAR_ARM_RATIO_LIMIT = 2.0


def _check_carried_stabar_is_coherent(bellcrank: dict[str, Any]) -> None:
    """Refuse a carried-over ARB pickup that the new bellcrank cannot support.

    An out-of-scale drop-link arm lets the Modelica model compile but fail mid-sweep.
    """
    pickups = bellcrank.get("pickups_m", {})
    pivot = pickups and bellcrank.get("pivot_m")
    if not pivot or "stabar" not in pickups:
        return

    arms = {name: _distance(pivot, point) for name, point in pickups.items()}
    stabar_arm = arms.get("stabar", 0.0)
    others = [length for name, length in arms.items() if name != "stabar"]
    if not others:
        return

    limit = STABAR_ARM_RATIO_LIMIT * max(others)
    if stabar_arm > limit:
        raise SharkImportError(
            "Cannot carry the baseline anti-roll bar onto this bellcrank.\n"
            f"  carried stabar arm : {stabar_arm * MM_PER_M:.1f} mm from the new pivot\n"
            "  SHARK-defined arms : "
            + ", ".join(
                f"{name} {length * MM_PER_M:.1f} mm"
                for name, length in sorted(arms.items())
                if name != "stabar"
            )
            + "\nThe SHARK model moved the bellcrank pivot, so the baseline ARB pickup no "
            "longer describes a physical rocker. It compiles but fails to solve.\n"
            "Drop --keep-arb (the default imports without a bar), or supply the ARB pickup "
            "in the new bellcrank's geometry."
        )


def _bellcrank_axis(points: dict[str, Any]) -> list[float]:
    first = points["Rocker axis 1st point"]
    second = points["Rocker axis 2nd point"]
    delta = [second[i] - first[i] for i in range(3)]
    length = math.sqrt(sum(value * value for value in delta))
    if length <= 0.0:
        raise SharkImportError("Rocker axis points are coincident; cannot derive bellcrank axis")
    return [round(value / length, 9) for value in delta]


def build_axle_block(
    points: dict[str, Any],
    baseline_axle: dict[str, Any],
    *,
    keep_stabar: bool,
) -> tuple[dict[str, Any], list[str]]:
    """Build the merged axle block. Returns the block and a list of notes."""
    notes: list[str] = []
    axle = copy.deepcopy(baseline_axle)

    missing = [name for name in SUSPENSION_POINT_MAP.values() if name not in points]
    if "Inner track rod ball joint" not in points:
        missing.append("Inner track rod ball joint")
    if missing:
        raise SharkImportError(
            f"SHARK file is missing hardpoints required by the schema: {', '.join(missing)}"
        )

    suspension = axle.setdefault("suspension", {})
    for key, name in SUSPENSION_POINT_MAP.items():
        suspension[key] = _to_m(points[name])

    steering = axle.setdefault("steering", {})
    steering["rack_pickup_m"] = _to_m(points["Inner track rod ball joint"])

    has_bellcrank = all(name in points for name in BELLCRANK_POINTS)
    if not has_bellcrank:
        missing = [name for name in BELLCRANK_POINTS if name not in points]
        raise SharkImportError(
            "SHARK file lacks pushrod/bellcrank points required by this vehicle's "
            f"architecture: {', '.join(missing)}"
        )

    actuation = axle.setdefault("actuation", {})
    rod_to = _rod_attachment(points)
    if rod_to != baseline_axle.get("actuation", {}).get("rod_to"):
        notes.append(
            f"rod_to changed {baseline_axle.get('actuation', {}).get('rod_to')!r} -> {rod_to!r} "
            "(pushrod picks up on the other wishbone in the SHARK model)"
        )
    actuation["rod_to"] = rod_to
    actuation["rod_mount_m"] = _to_m(points["Push rod wishbone end"])
    actuation.setdefault("shock", {})["mount_m"] = _to_m(points["Damper to body point"])

    bellcrank = actuation.setdefault("bellcrank", {})
    bellcrank["pivot_m"] = _to_m(points["Rocker axis 1st point"])
    bellcrank["axis"] = _bellcrank_axis(points)
    pickups = bellcrank.setdefault("pickups_m", {})
    pickups["rod"] = _to_m(points["Push rod rocker end"])
    pickups["shock"] = _to_m(points["Damper to rocker point"])

    # SHARK has no ARB pickups and the kinematic solve ignores the ARB, so drop it
    # by default. --keep-arb is for the four-post run.
    if keep_stabar:
        if "stabar" in actuation:
            _check_carried_stabar_is_coherent(bellcrank)
            notes.append(
                "SHARK file has no anti-roll bar points; carried the baseline stabar "
                "geometry and rate across unchanged (--keep-arb)"
            )
        else:
            notes.append("Baseline axle has no stabar and SHARK defines none")
    else:
        actuation.pop("stabar", None)
        pickups.pop("stabar", None)
        if isinstance(bellcrank.get("order"), list):
            bellcrank["order"] = [item for item in bellcrank["order"] if item != "stabar"]
        notes.append(
            "Anti-roll bar not imported (SHARK defines none). It is out of scope for "
            "kinematics and handled outside this tool."
        )

    return axle, notes


def import_shark(
    shark_path: str | Path,
    *,
    baseline_path: str | Path | None = None,
    datum_baseline_path: str | Path | None = None,
    keep_stabar: bool = False,
    vehicle_name: str | None = None,
) -> tuple[dict[str, Any], dict[str, Any]]:
    """Import a SHARK corner into a copy of the baseline vehicle.

    `datum_baseline_path` must stay the original baseline. A car built from the
    same SHARK file would compare the file to itself and hide a datum shift.
    """
    baseline_path = Path(baseline_path) if baseline_path else repo_root() / "vehicle.yml"
    baseline = load_yaml(baseline_path)
    datum_baseline = load_yaml(datum_baseline_path) if datum_baseline_path else baseline
    points = parse_shark(shark_path)

    check_single_side(points)
    missing = [name for name in REQUIRED_POINTS if name not in points]
    if missing:
        raise SharkImportError(
            f"{shark_path}: missing required hardpoints: {', '.join(missing)}"
        )

    axle, planar_offset = detect_axle(points, baseline)
    frame = verify_shared_frame(points, baseline, axle)
    datum = assess_z_datum(points, datum_baseline, axle)

    merged = copy.deepcopy(baseline)
    merged[axle], notes = build_axle_block(points, baseline[axle], keep_stabar=keep_stabar)

    other = "rear" if axle == "front" else "front"
    notes.insert(
        0,
        f"SHARK file describes the {axle.upper()} axle only; the {other} axle, and all "
        "mass/aero/tyre/powertrain data, are unchanged from the baseline.",
    )
    if datum["status"] != "shared_ground_plane":
        notes.insert(1, f"TODO(datum): {datum['reason']}")

    if not keep_stabar:
        architecture = merged.setdefault("architecture", {})
        if architecture.get(axle) == "bellcrank_stabar":
            architecture[axle] = "bellcrank"
            notes.append(f"architecture.{axle}: bellcrank_stabar -> bellcrank")

    if vehicle_name:
        merged.setdefault("vehicle", {})["name"] = vehicle_name

    report = {
        "axle": axle,
        "template": points.get("__template__"),
        "wheel_centre_planar_offset_mm": planar_offset,
        "frame_offset_mm": frame,
        "datum": datum,
        "notes": notes,
        "point_count": len([k for k in points if not k.startswith("__")]),
    }
    return merged, report


DATUM_SCHEMA = "bobsim.shark.datum.v2"


def datum_sidecar_path(vehicle_path: str | Path) -> Path:
    """Path of the datum record that travels with an imported vehicle file."""
    path = Path(vehicle_path)
    return path.with_name(f"{path.stem}.datum.json")


def geometry_digest(vehicle: dict[str, Any], axle: str) -> str:
    """Digest the inputs `CornerKinematics.from_vehicle` reads for one axle.

    A hand-edit to that geometry changes the digest and makes the datum record stale.
    """
    side = vehicle.get(axle) or {}
    material = {
        "suspension": side.get("suspension"),
        "rack_pickup_m": (side.get("steering") or {}).get("rack_pickup_m"),
        "wheel": side.get("wheel"),
    }
    blob = json.dumps(material, sort_keys=True, separators=(",", ":"), default=str)
    return hashlib.sha256(blob.encode("utf-8")).hexdigest()


def read_datum_sidecar(vehicle_path: str | Path) -> dict[str, Any] | None:
    path = datum_sidecar_path(vehicle_path)
    if not path.is_file():
        return None
    try:
        payload = json.loads(path.read_text(encoding="utf-8"))
    except Exception:
        return None
    return payload if isinstance(payload, dict) else None


def write_datum_sidecar(
    vehicle_path: str | Path, axle: str, datum: dict[str, Any], vehicle: dict[str, Any]
) -> Path:
    """Record one axle's datum verdict, merging into any existing record.

    The record is a sidecar so the vehicle file stays valid against `boblib.vehicle.v1`.
    """
    payload = read_datum_sidecar(vehicle_path) or {}
    axles = payload.get("axles")
    if not isinstance(axles, dict):
        axles = {}
    axles[axle] = {**datum, "geometry_digest": geometry_digest(vehicle, axle)}
    merged = {"schema": DATUM_SCHEMA, "axles": axles}
    path = datum_sidecar_path(vehicle_path)
    path.write_text(json.dumps(merged, indent=2, sort_keys=True), encoding="utf-8")
    return path


def datum_gate(vehicle_path: str | Path, vehicle: dict[str, Any] | None = None) -> dict[str, Any]:
    """Decide whether z-dependent output may be published for this vehicle.

    Fails closed. `valid` requires a record, every axle resolved and every digest current.
    """
    path = Path(vehicle_path)
    payload = read_datum_sidecar(path)
    if payload is None:
        return {
            "valid": False,
            "reason": f"No datum record beside {path.name}.",
            "axles": {},
        }

    if vehicle is None:
        vehicle = load_yaml(path)
    axles = payload.get("axles")
    if not isinstance(axles, dict) or not axles:
        return {"valid": False, "reason": f"{datum_sidecar_path(path).name} records no axles.", "axles": {}}

    detail: dict[str, Any] = {}
    problems: list[str] = []
    for axle, record in sorted(axles.items()):
        if not isinstance(record, dict):
            problems.append(f"{axle}: malformed record")
            continue
        status = str(record.get("status", "missing"))
        recorded = str(record.get("geometry_digest", ""))
        actual = geometry_digest(vehicle, axle)
        stale = recorded != actual
        detail[axle] = {"status": status, "digest_matches": not stale}
        if stale:
            problems.append(
                f"{axle}: geometry digest mismatch - the {axle} geometry changed since the "
                "datum was assessed, so the recorded verdict describes a different car"
            )
        elif status != "shared_ground_plane":
            problems.append(f"{axle}: datum {status}")

    if problems:
        return {"valid": False, "reason": "; ".join(problems), "axles": detail}
    return {"valid": True, "reason": "every imported axle has a resolved, current datum", "axles": detail}


def write_vehicle(vehicle: dict[str, Any], path: str | Path) -> Path:
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8") as handle:
        yaml.safe_dump(vehicle, handle, sort_keys=False, default_flow_style=False)
    return path


def main(argv: Sequence[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description="Import a Lotus SHARK file into a vehicle.yml")
    parser.add_argument("shark", help="Path to the .shk file")
    parser.add_argument("-o", "--output", required=True, help="Path to write the merged vehicle.yml")
    parser.add_argument("--baseline", default=None, help="Baseline vehicle.yml (default: repo vehicle.yml)")
    parser.add_argument(
        "--datum-baseline",
        default=None,
        help=(
            "Reference for the vertical datum check. Set this to the original baseline "
            "when merging a second axle onto an already-imported car."
        ),
    )
    parser.add_argument("--name", default=None, help="Vehicle name for the merged car")
    parser.add_argument(
        "--keep-arb",
        action="store_true",
        help=(
            "Carry the baseline anti-roll bar across. Only meaningful for the opt-in "
            "four-post run; the ARB plays no part in the kinematic solve."
        ),
    )
    args = parser.parse_args(argv)

    merged, report = import_shark(
        args.shark,
        baseline_path=args.baseline,
        datum_baseline_path=args.datum_baseline,
        keep_stabar=args.keep_arb,
        vehicle_name=args.name,
    )
    out = write_vehicle(merged, args.output)
    write_datum_sidecar(out, report["axle"], report["datum"], merged)

    print(f"Imported {report['point_count']} points from {args.shark}")
    print(f"  template : {report['template']}")
    print(f"  axle     : {report['axle']}")
    offset = report["frame_offset_mm"]
    print(
        "  frame    : wheel centre dx={dx_mm:+.4f} dy={dy_mm:+.4f} dz={dz_mm:+.4f} mm".format(**offset)
    )
    print(f"  z datum  : {report['datum']['status']}")
    for note in report["notes"]:
        print(f"  note     : {note}")
    print(f"Wrote {out}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
