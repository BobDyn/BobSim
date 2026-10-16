"""Vehicle-clearance track geometry and reusable racing-line results."""
from __future__ import annotations

from dataclasses import asdict
import hashlib
import json
from pathlib import Path
from typing import Any

import numpy as np

from common.vehicle_io import load_yaml, parse_tir, repo_root, tire_template_name
from simulations.lap.core.racing_line import minimize_curvature
from simulations.lap.core.track import RacingLine, TrackCorridor


def vehicle_width_m(vehicle: dict[str, Any], root: Path) -> float:
    """## Nominal Vehicle Width

    Parameters
    ----------
    vehicle : dict
        Vehicle geometry and axle tire definitions.
    root : Path
        Root for relative tire paths.

    Returns
    -------
    float
        Widest nominal outside-tire span in metres. Wheels are straight ahead.
    """
    tire_root = root / vehicle.get("paths", {}).get("tire_templates", "common/tire_templates")
    widths = []
    for axle in ("front", "rear"):
        side = vehicle[axle]
        tire = parse_tir(tire_root / f"{tire_template_name(vehicle, side)}.tir")
        if "WIDTH" not in tire:
            raise ValueError(f"The {axle} tire file needs a WIDTH value in metres.")
        section_width = float(tire["WIDTH"])
        half_track = abs(float(side["suspension"]["wheel_center_m"][1]))
        if not np.isfinite(section_width + half_track) or section_width <= 0. or half_track <= 0.:
            raise ValueError(f"Invalid {axle} wheel spacing or tire WIDTH.")
        widths.append(2. * half_track + section_width)
    return max(widths)


def line_signature(config: dict[str, Any], root: Path) -> str:
    """## Racing-Line Input Signature

    Parameters
    ----------
    config : dict
        Track and clearance settings.
    root : Path
        Vehicle workspace root.

    Returns
    -------
    str
        Digest of the track, derived width, clearance and generation method.
    """
    track = config["track"]
    values = {"width": vehicle_width_m(load_yaml(root / "vehicle.yml"), root),
              "track": hashlib.sha256((root / track["boundary_csv"]).read_bytes()).hexdigest(),
              "clearance": float(track.get("safety_margin_m", .15)),
              "mode": config.get("mode", "minimum_curvature")}
    return hashlib.sha256(json.dumps(values, sort_keys=True).encode()).hexdigest()


def run(config: dict[str, Any], root: Path | None = None) -> dict[str, Any]:
    """## Racing-Line Generation

    Parameters
    ----------
    config : dict
        Track path, clearance and centerline or minimum-curvature method.
    root : Path or None
        Vehicle workspace root.

    Returns
    -------
    dict
        Converged line, original boundaries and input provenance.
    """
    root = root or repo_root()
    signature = line_signature(config, root)
    track = config["track"]
    corridor = TrackCorridor.from_csv(root / track["boundary_csv"])
    width = vehicle_width_m(load_yaml(root / "vehicle.yml"), root)
    margin = float(track.get("safety_margin_m", .15))
    corridor.offset_bounds(vehicle_width_m=width, safety_margin_m=margin)
    mode = config.get("mode", "minimum_curvature")
    if mode not in {"centerline", "minimum_curvature"}:
        raise ValueError("Choose centerline or minimum_curvature.")
    offsets = np.zeros(corridor.gate_count)
    if mode == "minimum_curvature":
        solution = minimize_curvature(corridor, vehicle_width_m=width, safety_margin_m=margin)
        if not solution.success:
            raise ValueError(f"Racing line did not converge: {solution.message}")
        offsets = solution.x
    line = corridor.line_from_offsets(offsets)
    left, right = corridor.interpolated_boundaries()
    result = {"schema": "bobsim.racing-line.v1", "signature": signature,
              "vehicle_width_m": width, "clearance_m": margin, "mode": mode,
              "track": track["boundary_csv"], "length_m": line.track_length_m,
              "left": left.tolist(), "right": right.tolist(),
              "line": {key: value.tolist() if isinstance(value, np.ndarray) else value
                       for key, value in asdict(line).items()}}
    if signature != line_signature(config, root):
        raise ValueError("Track or vehicle inputs changed during line generation. Run it again.")
    output = root / "app/user_data/results/racing-line"
    output.mkdir(parents=True, exist_ok=True)
    (output / "line.json").write_text(json.dumps(result), encoding="utf-8")
    np.savetxt(output / "signals.csv", np.column_stack((line.station_m, line.x_m, line.y_m, line.curvature_per_m)),
               delimiter=",", header="station_m,x_m,y_m,curvature_per_m", comments="")
    from common.reporting.racing_line_report import build_racing_line_report
    build_racing_line_report(result, output / "report.pdf")
    return result


def load_line(path: Path) -> RacingLine:
    """## Saved Racing Line

    Parameters
    ----------
    path : Path
        Archived racing-line JSON.

    Returns
    -------
    RacingLine
        Original sampled line, without resampling or optimization.
    """
    payload = json.loads(path.read_text(encoding="utf-8"))
    if payload.get("schema") != "bobsim.racing-line.v1":
        raise ValueError("Unsupported racing-line result.")
    raw = payload["line"]
    values: dict[str, Any] = {key: float(value) if key == "track_length_m" else np.asarray(value, dtype=float)
              for key, value in raw.items()}
    line = RacingLine(**values)
    arrays = [line.station_m, line.x_m, line.y_m, line.heading_rad, line.curvature_per_m, line.segment_length_m]
    if len(line.station_m) < 5 or any(a.shape != line.station_m.shape or not np.all(np.isfinite(a)) for a in arrays):
        raise ValueError("Invalid racing-line samples.")
    if line.station_m[0] != 0. or np.any(np.diff(line.station_m) <= 0.) or np.any(line.segment_length_m <= 0.) \
            or not np.isfinite(line.track_length_m) or not np.isclose(line.segment_length_m.sum(), line.track_length_m):
        raise ValueError("Invalid racing-line distance coordinates.")
    return line
