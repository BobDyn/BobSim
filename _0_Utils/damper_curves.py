"""Resolve damper settings to passive, compression-positive shaft force tables."""

from __future__ import annotations

from bisect import bisect_right
from dataclasses import dataclass
import hashlib
import json
import math
import os
from pathlib import Path
import re
import uuid
from typing import Any, Mapping, Sequence

from _0_Utils.vehicle_io import repo_root


@dataclass(frozen=True)
class ResolvedDamperCurve:
    """Positive input is shaft shortening; positive output resists shortening.

    Extrapolation uses the terminal segment, matching BobLib's CombiTable1Ds.
    The metadata records the measured range; extrapolated forces are predictions.
    """

    table: tuple[tuple[float, float], ...]
    provenance: Mapping[str, Any]

    def force(self, compression_velocity_mps: float) -> float:
        return interpolate_force(self.table, compression_velocity_mps)

    @property
    def velocity_limits(self) -> tuple[float, float]:
        return self.table[0][0], self.table[-1][0]


def interpolate_force(table: Sequence[Sequence[float]], velocity: float) -> float:
    """Piecewise linear interpolation and terminal-slope extrapolation."""
    i = max(0, min(bisect_right([row[0] for row in table], velocity) - 1, len(table) - 2))
    x0, y0 = table[i]
    x1, y1 = table[i + 1]
    return float(y0 + (velocity - x0) * (y1 - y0) / (x1 - x0))


def _number(value: Any, label: str) -> float:
    if isinstance(value, bool) or not isinstance(value, (int, float)) or not math.isfinite(value):
        raise ValueError(f"{label} must be a finite number")
    return float(value)


def _validate_table(value: Any) -> tuple[tuple[float, float], ...]:
    if not isinstance(value, (list, tuple)) or len(value) < 3:
        raise ValueError("damper_table.table needs at least three [velocity_mps, force_n] rows")
    rows = []
    for row in value:
        if not isinstance(row, (list, tuple)) or len(row) != 2:
            raise ValueError("Each damper row must contain [velocity_mps, force_n]")
        rows.append((_number(row[0], "damper velocity"), _number(row[1], "damper force")))
    if any(b[0] <= a[0] for a, b in zip(rows, rows[1:])):
        raise ValueError("Damper velocities must be strictly increasing")
    if rows[0][0] >= 0 or rows[-1][0] <= 0 or (0.0, 0.0) not in rows:
        raise ValueError("Damper table must cover rebound and compression and include [0, 0]")
    if any(v * f < 0 for v, f in rows):
        raise ValueError("Damper force must resist motion: velocity * force must be nonnegative")
    if rows[1][1] < rows[0][1] or rows[-1][1] < rows[-2][1]:
        raise ValueError("Terminal damper slopes must be nonnegative for passive extrapolation")
    return tuple(rows)


def _keys(config: Mapping[str, Any], allowed: set[str], label: str) -> None:
    extra = set(config) - allowed
    if extra:
        raise ValueError(f"Unknown {label} fields: {', '.join(sorted(extra))}")


def _branch(dataset: Mapping[str, Any], settings: Any, direction: str) -> tuple[list[float], dict[str, Any]]:
    if not isinstance(settings, Mapping):
        raise ValueError(f"damper.{direction} must specify valve and adjuster settings")
    _keys(settings, {"valve", "low_speed_clicks_from_closed", "high_speed_turns_from_open"}, direction)
    valve = settings.get("valve")
    ls = _number(settings.get("low_speed_clicks_from_closed"), f"{direction} low-speed clicks")
    hs = _number(settings.get("high_speed_turns_from_open"), f"{direction} high-speed turns")
    if not ls.is_integer():
        raise ValueError("Low-speed clicks must be integers")
    candidates = [c for c in dataset["curves"] if c["direction"] == direction and c["valve"] == valve]
    if not candidates:
        raise ValueError(f"Unsupported {direction} valve {valve!r} in {dataset['id']}")
    # Only interpolate along an actually measured sweep, never across its missing interior.
    if hs == 4.3:
        candidates = [c for c in candidates if c["high_speed_turns_from_open"] == hs]
        axis, target = "low_speed_clicks_from_closed", ls
    elif ls == 0:
        candidates = [c for c in candidates if c["low_speed_clicks_from_closed"] == 0]
        axis, target = "high_speed_turns_from_open", hs
    else:
        raise ValueError("TTX25 PDF supports HS=4.3 with LS=0..25, or LS=0 with HS=0..4.3; "
                         "this combination is unmeasured")
    candidates.sort(key=lambda c: c[axis])
    if not candidates or not candidates[0][axis] <= target <= candidates[-1][axis]:
        raise ValueError(f"Unsupported TTX25 {axis}={target}; no setting extrapolation is allowed")
    lo = max((c for c in candidates if c[axis] <= target), key=lambda c: c[axis])
    hi = min((c for c in candidates if c[axis] >= target), key=lambda c: c[axis])
    weight = 0.0 if lo[axis] == hi[axis] else (target - lo[axis]) / (hi[axis] - lo[axis])
    forces = [(1 - weight) * a + weight * b for a, b in zip(lo["force_n"], hi["force_n"])]
    return forces, {
        "settings": dict(settings), "interpolated": lo is not hi,
        "source_curves": [lo["id"]] if lo is hi else [lo["id"], hi["id"]],
        "upper_weight": weight,
    }


def resolve_damper_curve(shock: Mapping[str, Any]) -> ResolvedDamperCurve:
    """Resolve exactly one legacy table or named TTX25 configuration."""
    if ("damper" in shock) == ("damper_table" in shock):
        raise ValueError("Specify exactly one of shock.damper or shock.damper_table")
    if "damper_table" in shock:
        table = shock["damper_table"]
        if not isinstance(table, Mapping):
            raise ValueError("damper_table must contain a table mapping")
        return ResolvedDamperCurve(_validate_table(table.get("table")), {"model": "table"})
    config = shock["damper"]
    if not isinstance(config, Mapping):
        raise ValueError("shock.damper must be a mapping")
    _keys(config, {"model", "dataset", "compression", "rebound"}, "damper")
    if config.get("model") != "ohlins_ttx25_mkii":
        raise ValueError(f"Unsupported damper model {config.get('model')!r}")
    if config.get("dataset") != "ttx25_mkii_c12_r12_pdf_v1":
        raise ValueError("Supported dataset: ttx25_mkii_c12_r12_pdf_v1")
    path = repo_root() / "_0_Utils/damper_data/ttx25_mkii_c12_r12_pdf_v1.json"
    raw = path.read_bytes()
    dataset = json.loads(raw)
    grid = dataset["velocity_mps"]
    if (dataset.get("id") != config["dataset"] or len(grid) < 2 or grid[0] != 0
            or any(not math.isfinite(v) for v in grid)
            or any(b <= a for a, b in zip(grid, grid[1:]))):
        raise ValueError("Invalid TTX25 dataset velocity grid or identity")
    for item in dataset["curves"]:
        values = item["force_n"]
        if (len(values) != len(grid) or values[0] != 0
                or any(not math.isfinite(f) or f < 0 for f in values)
                or any(b < a for a, b in zip(values, values[1:]))):
            raise ValueError(f"Invalid TTX25 dataset force samples: {item['id']}")
    compression, cp = _branch(dataset, config.get("compression"), "compression")
    rebound, rp = _branch(dataset, config.get("rebound"), "rebound")
    velocities = dataset["velocity_mps"]
    table = [[-v, -f] for v, f in reversed(list(zip(velocities[1:], rebound[1:])))]
    table += list(map(list, zip(velocities, compression)))
    return ResolvedDamperCurve(_validate_table(table), {
        "model": config["model"], "dataset": dataset["id"],
        "dataset_sha256": hashlib.sha256(raw).hexdigest(),
        "source": dataset["source"], "limitations": dataset["limitations"],
        "compression": cp, "rebound": rp,
        "measured_max_speed_mps": velocities[-1],
        "extrapolation": "last_two_points",
    })


def vehicle_damper_provenance(data: Mapping[str, Any]) -> dict[str, Any]:
    """Serializable resolved tables and provenance for generated records/results."""
    result = {}
    for axle in ("front", "rear"):
        curve = resolve_damper_curve(data[axle]["actuation"]["shock"])
        result[axle] = {**curve.provenance, "table": curve.table}
    return result


def write_runtime_damper_file(data: Mapping[str, Any], build_dir: Path) -> Path:
    """Write MSL named tables loaded by VehicleSim and FourPostSim at startup."""
    sections = ["#1"]
    for axle in ("front", "rear"):
        table = resolve_damper_curve(data[axle]["actuation"]["shock"]).table
        sections.append(f"double {axle}({len(table)},2)")
        sections.extend(f"{speed:.15g} {force:.15g}" for speed, force in table)
    destination = build_dir / "damper_tables.txt"
    build_dir.mkdir(parents=True, exist_ok=True)
    temporary = build_dir / f".damper_tables.{uuid.uuid4().hex}.tmp"
    try:
        temporary.write_text("\n".join(sections) + "\n", encoding="ascii")
        os.replace(temporary, destination)
    finally:
        temporary.unlink(missing_ok=True)
    return destination


def write_modelica_damper_tables(data: Mapping[str, Any], record_path: Path) -> bool:
    """Update only the two damper tables in an existing BobLib vehicle record."""
    source = record_path.read_bytes()
    text = source.decode("utf-8")
    for axle, prefix in (("front", "Fr"), ("rear", "Rr")):
        curve = resolve_damper_curve(data[axle]["actuation"]["shock"])
        table = "[" + "; ".join(f"{v:.15g}, {f:.15g}" for v, f in curve.table) + "]"
        pattern = re.compile(
            rf"(parameter\s+Axle\.\w+Record\s+p{prefix}AxleDW\([\s\S]*?damperTable\s*=\s*)"
            r"\[[^\]]+\]"
        )
        text, count = pattern.subn(lambda match: match.group(1) + table, text)
        if count != 1:
            raise ValueError(f"Expected one {axle} damperTable in {record_path}; found {count}")
    updated = text.encode("utf-8")
    if updated == source:
        return False
    record_path.write_bytes(updated)
    return True


def main() -> None:
    """Inspect resolved curves and provenance without modifying the vehicle."""
    import argparse
    from pathlib import Path
    from _0_Utils.vehicle_io import load_yaml

    parser = argparse.ArgumentParser(description=main.__doc__)
    parser.add_argument("vehicle", type=Path)
    parser.add_argument("--output", type=Path)
    parser.add_argument("--write-modelica", action="store_true",
                        help="Update only the two damper tables in the existing BobLib vehicle record")
    args = parser.parse_args()
    data = load_yaml(args.vehicle)
    if args.write_modelica:
        if args.output:
            parser.error("--output and --write-modelica cannot be combined")
        name = data["vehicle"]["name"]
        if re.fullmatch(r"[A-Za-z_]\w*", name) is None:
            parser.error("vehicle.name must be a Modelica identifier")
        boblib = Path(data["paths"]["boblib"])
        if not boblib.is_absolute():
            boblib = args.vehicle.resolve().parent / boblib
        record = boblib / "Records/VehicleDefn" / f"{name}Record.mo"
        changed = write_modelica_damper_tables(data, record)
        print(f"{'Updated' if changed else 'Already current'}: {record}")
        return
    payload = json.dumps(vehicle_damper_provenance(data), indent=2) + "\n"
    if args.output:
        args.output.write_text(payload, encoding="utf-8")
    else:
        print(payload, end="")


if __name__ == "__main__":
    main()
