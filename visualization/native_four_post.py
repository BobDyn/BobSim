"""Capture a saved native Four Post run with its original binaries and calibration."""
from __future__ import annotations

import argparse
import csv
import hashlib
import json
from pathlib import Path
import re
import shutil
import subprocess
import tempfile

import numpy as np
import yaml

from common import native_artifacts
from common.vehicle_io import repo_root
from visualization import from_results


# Current native rods expose the same pickup origins through their physical frames.
_FRAME_ALIASES = {
    "WishboneUprightLoop.lowerFrameToFore.frame_b": "WishboneUprightLoop.lowerForeRod.frame_a",
    "WishboneUprightLoop.lowerFrameToAft.frame_b": "WishboneUprightLoop.lowerAftRod.frame_a",
    "WishboneUprightLoop.upperFrameToFore.frame_b": "WishboneUprightLoop.upperForeRod.frame_a",
    "WishboneUprightLoop.upperFrameToAft.frame_b": "WishboneUprightLoop.upperAftRod.frame_a",
}


def geometry_filter() -> str:
    """Select the linkage origins, wheel frames and original KnC measurements."""
    frames = {template.format(axle="axle", side=side, Side=side.title())
              for template in from_results.FRAME_MAP.values() for side in ("left", "right")}
    frames.update("axle." + side + frame for side in ("left", "right") for frame in _FRAME_ALIASES.values())
    parts = ["time", r"knc\..*", "inputs.steer", r"(left|right)Load\.worldForce\.force\[[123]\]"]
    parts.extend(re.escape(frame) + r"\.r_0\[[123]\]" for frame in sorted(frames))
    parts.extend(re.escape(from_results.WHEEL_FRAME.format(axle="axle", Side=side.title()))
                 + r"\.R\.T\[[123],[123]\]" for side in ("left", "right"))
    return "|".join(parts)


def _path(root: Path, value: str) -> Path:
    path = (root / value).resolve()
    if not path.is_relative_to(root.resolve()):
        raise ValueError("Capture inputs must belong to this workspace")
    return path


def capture_axle(record: dict, destination: Path, root: Path) -> dict[str, np.ndarray]:
    """Rerun a verified archived binary without recalculating any calibration."""
    identity = record["identity"]
    digest = hashlib.sha256(json.dumps(identity, sort_keys=True).encode()).hexdigest()
    directory = root / "app/user_data/cache/native" / digest
    manifest = native_artifacts.checked_manifest(directory)
    if manifest["identity"] != identity:
        raise ValueError("The archived binary identity does not match the cached artifact")
    encoded = native_artifacts.validate_overrides(manifest, record["overrides"])
    destination.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix="capture-", dir=destination) as temporary:
        work = Path(temporary)
        for name in manifest["runtime_file_sha256"]:
            shutil.copy2(directory / name, work / name)
        (work / "overrides.txt").write_text("".join(f"{name}={value}\n" for name, value in encoded.items()))
        command = [str(work / manifest["executable"]), "-overrideFile=overrides.txt", "-r=signals.csv",
                   f"-stopTime={record['final_time']}", "-stepSize=0.1", "-variableFilter=" + geometry_filter(),
                   "-jacobian=internalNumerical", "-nls=" + manifest["nonlinear_solver"], "-s=euler"]
        completed = subprocess.run(command, cwd=work, text=True, stdout=subprocess.PIPE,
                                   stderr=subprocess.STDOUT, timeout=180)
        (destination / "capture.log").write_text(completed.stdout)
        if (completed.returncode or "simulation finished successfully" not in completed.stdout
                or "not found" in completed.stdout.lower() or "cannot be overridden" in completed.stdout.lower()):
            raise RuntimeError(f"Native geometry capture failed: {completed.stdout[-2000:]}")
        shutil.copy2(work / "signals.csv", destination / "signals.csv")
        shutil.copy2(work / "overrides.txt", destination / "overrides.txt")
    columns = from_results.read_result_csv(destination / "signals.csv")
    if not all(np.isfinite(values).all() for values in columns.values()):
        raise ValueError("Geometry capture contains nonfinite values")
    original = from_results.read_result_csv(_path(root, record["csv"]))
    verify_replay(columns, original)
    return columns


def verify_replay(captured: dict, original: dict) -> None:
    """Check the captured geometry run still follows the archived KnC signals."""
    if not np.isclose(captured["time"][-1], original["time"][-1], atol=1e-8, rtol=0):
        raise ValueError("Geometry capture did not complete the archived protocol")
    for key in original:
        if not (key.startswith("knc.") or ".worldForce.force[" in key):
            continue
        if key not in captured:
            raise ValueError(f"Capture omitted archived measurement {key}")
        # Keep the right side of duplicate event times, consistently for both runs.
        times = np.unique(original["time"])
        before = np.interp(times, original["time"], original[key])
        after = np.interp(times, captured["time"], captured[key])
        if not np.allclose(before, after, rtol=1e-6, atol=1e-8):
            raise ValueError(f"Geometry capture differs from the archived run: {key}")


def combine(frames: dict[str, dict]) -> dict[str, np.ndarray]:
    """Join axles using the same rear traction/braking split as the saved report."""
    time = np.unique(np.concatenate([frame["time"] for frame in frames.values()]))
    output = {"time": time}
    for side, prefix in (("front", "fr"), ("rear", "rr")):
        frame = frames["knc-" + side]
        for key, data in frame.items():
            if key == "time":
                continue
            values = np.interp(time, frame["time"], data)
            if side == "rear":
                traction = frames["knc-rear-traction"]
                if key not in traction:
                    raise ValueError(f"Rear traction geometry omitted {key}")
                values = np.where(time < 60, np.interp(time, traction["time"], traction[key]), values)
            name = key.replace("axle.", prefix + "AxleDW.", 1) if key.startswith("axle.") else (
                prefix + "KnC." + key[4:] if key.startswith("knc.") else prefix + "." + key)
            output[name] = values
        for side_name in ("left", "right"):
            for legacy, actual in _FRAME_ALIASES.items():
                for axis in (1, 2, 3):
                    name = f"{prefix}AxleDW.{side_name}{legacy}.r_0[{axis}]"
                    alternative = f"{prefix}AxleDW.{side_name}{actual}.r_0[{axis}]"
                    if name not in output and alternative in output:
                        output[name] = output[alternative]
    return output


def add_applied_forces(config: dict, signals: dict, columns: dict) -> None:
    """Attach world-resolved imposed forces at contact patches with a fixed scale."""
    vectors = {}
    for corner, prefix, side in (("fl", "fr", "left"), ("fr", "fr", "right"),
                                 ("rl", "rr", "left"), ("rr", "rr", "right")):
        names = [f"{prefix}.{side}Load.worldForce.force[{axis}]" for axis in (1, 2, 3)]
        if any(name not in columns for name in names[:2]):
            raise ValueError(f"Capture omitted applied force at {corner}")
        # ContactPatchForceActuator fixes Fz=0; native CSV omits constants.
        signals.update({name: columns[name] for name in names[:2]})
        signals[names[2]] = columns.get(names[2], np.zeros_like(columns["time"]))
        vectors[corner] = {"origin": corner + "_ContactPatch", "direction": names,
                           "scale": 0.001, "color": "#e67722", "shaft_radius": 0.009}
        for axis, name in zip(("x", "y", "z"), names):
            config["plots"].append({"name": f"{corner.upper()} applied F{axis} (N)", "x": "time", "y": name})
    config["geometry"]["vectors"] = {"applied_force": vectors}
    config["render"]["force_vectors"] = True


def capture(run_directory: Path, *, root: Path | None = None) -> Path:
    """Write a replay scene linked to the saved simulation and vehicle workspace."""
    root = (root or repo_root()).resolve()
    run_directory = _path(root, run_directory.as_posix())
    saved = json.loads((run_directory / "manifest.json").read_text())
    if saved["workflow"]["id"] != "four-post":
        raise ValueError("Choose a saved Four Post run")
    provenance_path = next(item["path"] for item in saved["files"] if item["label"] == "Binary provenance")
    provenance = json.loads(_path(root, provenance_path).read_text())
    runs = provenance["iterations"][-1]
    name = "four_post_" + saved["id"]
    output = root / "visualization/results"
    work = output / (name + "_capture")
    frames = {}
    for kind in ("knc-front", "knc-rear", "knc-rear-traction"):
        print(f"Capturing archived {kind}", flush=True)
        frames[kind] = capture_axle(runs[kind], work / kind, root)
    signals = combine(frames)
    merged = work / "combined.csv"
    with merged.open("w", newline="") as stream:
        writer = csv.writer(stream)
        writer.writerow(signals)
        writer.writerows(zip(*signals.values()))
    vehicle_path = _path(root, saved["vehicle_snapshot"])
    vehicle = yaml.safe_load(vehicle_path.read_text())
    template = output / (name + ".yml")
    _, _, summary = from_results.convert(merged, template.with_suffix(".npz"), template,
                                        vehicle_yaml=vehicle_path, metrics_csv=run_directory / "files/metrics.csv")
    config = yaml.safe_load(template.read_text())
    with np.load(template.with_suffix(".npz")) as stored:
        scene_signals = dict(stored)
    add_applied_forces(config, scene_signals, signals)
    summary["applied_force_vectors"] = 4
    summary["plots"] = len(config["plots"])
    np.savez_compressed(template.with_suffix(".npz"), **scene_signals)
    for corner, tire in config["geometry"]["tires"].items():
        wheel = vehicle["front" if corner.startswith("f") else "rear"]["wheel"]
        tire["radius"] = wheel["radius_m"]
        tire["width"] = wheel["radius_m"] * wheel["rim_radius_ratio"] * wheel["rim_width_ratio"]
    config["representation"] = "BobLib · native Four Post · archived calibration"
    config["source"] = {"label": saved["label"] + " · Suspension animation",
                        "simulation_id": saved["simulation"]["id"], "vehicle_key": saved["vehicle_key"],
                        "result_id": saved["id"],
                        "manifest": (run_directory / "manifest.json").relative_to(root).as_posix()}
    config["render"]["speed"] = 4.0
    template.write_text(yaml.safe_dump(config, sort_keys=False))
    (work / "provenance.json").write_text(json.dumps({"source": config["source"], "runs": runs,
                                                   "verification": "Archived KnC channels match", "summary": summary},
                                                  indent=2))
    print(json.dumps(summary, indent=2), flush=True)
    return template


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("run_directory", type=Path)
    args = parser.parse_args()
    print(capture(args.run_directory))


if __name__ == "__main__":
    main()
