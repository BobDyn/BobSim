"""Solve unloaded, simultaneous axle travel using cached native KnC artifacts."""
from __future__ import annotations

import csv
from concurrent.futures import ThreadPoolExecutor
from functools import lru_cache
import json
import math
import re
from pathlib import Path
import shutil
import subprocess
import tempfile

from app.native_calibration import vehicle_overrides
from common import native_artifacts as artifacts

LIMITS = {"heave_mm": 38.1, "roll_deg": 1.25, "steer_deg": 90.0}


def travel_payload(vehicle: dict, pose: dict, axis: str | None = None) -> dict:
    """Return solved world coordinates without changing vehicle calibration."""
    if not isinstance(vehicle, dict) or not isinstance(pose, dict):
        raise TypeError("vehicle and pose must be objects")
    if pose.keys() != LIMITS.keys():
        raise ValueError("Travel requires heave_mm, roll_deg and steer_deg")
    for name, limit in LIMITS.items():
        value = pose[name]
        if (isinstance(value, bool) or not isinstance(value, (int, float))
                or not math.isfinite(value) or abs(value) > limit):
            raise ValueError(f"{name} must be finite and between {-limit} and {limit}")
    if axis is not None and axis not in LIMITS:
        raise ValueError("Unknown travel axis")
    selection = artifacts.architecture(vehicle)
    requests = []
    for axle in ("front", "rear"):
        kind = "knc-" + axle
        directory = artifacts.artifact_dir(selection, kind)
        try:
            manifest = artifacts.checked_manifest(directory)
        except FileNotFoundError as exc:
            raise ValueError(f"Build {artifacts.KINDS[kind]} in Architecture first") from exc
        if manifest["identity"] != artifacts.identity(selection, kind):
            raise ValueError("Travel binary does not match current architecture and sources")
        # Refresh the contract from the verified XML, including existing binaries
        # whose manifests predate support for the two table-offset parameters.
        xml_name = manifest["executable"] + "_init.xml"
        manifest.update(_contract((directory / xml_name).as_posix(), manifest["runtime_file_sha256"][xml_name]))
        overrides = vehicle_overrides(vehicle, manifest, artifacts.ROOT)
        overrides.update({"forceMagnitude": 0, "stabilizerRate": 0,
                          "heaveMagnitude": 1, "rollMagnitude": 1,
                          "inputs.heaveSource.offset[1]": pose["heave_mm"] / 1000,
                          "inputs.rollSource.offset[1]": math.radians(pose["roll_deg"])})
        if axle == "front":
            overrides.update({"angleCount": 1, "steeringAngles[1]": math.radians(pose["steer_deg"])})
        if axis:
            overrides.update({"inputs.heaveSource.startTime": 1e9, "inputs.rollSource.startTime": 1e9})
            if axis == "heave_mm":
                overrides.update({"heaveMagnitude": .0381, "inputs.heaveSource.offset[1]": 0,
                                  "inputs.heaveSource.startTime": 0})
            elif axis == "roll_deg":
                overrides.update({"rollMagnitude": math.radians(1.25), "inputs.rollSource.offset[1]": 0,
                                  "inputs.rollSource.startTime": 0})
            elif axle == "front":
                overrides["angleCount"] = 7
                overrides.update({f"steeringAngles[{i}]": math.radians(value)
                                  for i, value in enumerate(range(-90, 91, 30), 1)})
        encoded = artifacts.validate_overrides(manifest, overrides)
        runtime = {k: manifest[k] for k in ("executable", "runtime_file_sha256", "nonlinear_solver")}
        requests.append(json.dumps({"directory": directory.as_posix(), "manifest": runtime,
                                    "encoded": encoded, "pose": {**pose, axis: 0} if axis else pose,
                                    "axle": axle, "axis": axis,
                                    "architecture": vehicle["architecture"][axle]}, sort_keys=True))
    with ThreadPoolExecutor(max_workers=2) as executor:
        if axis:
            paths = list(executor.map(_trajectory, requests))
            return {"axis": axis, "pose": pose, "axles": dict(zip(("front", "rear"), paths))}
        results = list(executor.map(_solve, requests))
    return {"pose": pose, "points": {key: value for result in results for key, value in result.items()}}


@lru_cache(maxsize=16)
def _contract(path: str, digest: str) -> dict:
    # Digest belongs to the verified bundle; replacement invalidates this cache.
    return artifacts.parameter_contract(Path(path))


def point_frames(axle: str, architecture: str) -> dict[str, str]:
    """Map editor point IDs to connected native multibody frames."""
    result = {}
    for side in ("left", "right"):
        frames = {"lower-fore-i": "WishboneUprightLoop.lowerForeRod.frame_a",
                  "lower-aft-i": "WishboneUprightLoop.lowerAftRod.frame_a",
                  "upper-fore-i": "WishboneUprightLoop.upperForeRod.frame_a",
                  "upper-aft-i": "WishboneUprightLoop.upperAftRod.frame_a",
                  "lower-o": "WishboneUprightLoop.lowerFrame_o",
                  "upper-o": "WishboneUprightLoop.upperFrame_o",
                  "tie-o": "TieRod.frame_b", "rack": "TieRod.frame_a",
                  "wheel-center": "Bearing", "shock-mount": "ShockLinkage.frame_b",
                  "rod": "Pushrod.frame_b" if "bellcrank" in architecture else "ShockLinkage.frame_a"}
        if "bellcrank" in architecture:
            frames.update({"bellcrank-pivot": "Bellcrank.mountFrame",
                           "bellcrank-rod": "Bellcrank.pickupFrame1",
                           "bellcrank-shock": "Bellcrank.pickupFrame2"})
        if "stabar" in architecture:
            frames["bellcrank-stabar"] = "Bellcrank.pickupFrame3"
        for name, frame in frames.items():
            result[f"{axle}-{side}-{name}"] = f"axle.{side}{frame}.r_0"
        if "stabar" in architecture:
            result[f"{axle}-{side}-stabar-arm"] = f"axle.stabar.{side}ArmFrame.r_0"
            result[f"{axle}-{side}-stabar-bar"] = f"axle.stabar.to{side.title()}BarEnd.frame_b.r_0"
    return result


def _points(row: dict, request: dict) -> dict:
    points = {name: [row[f"{frame}[{i}]"] for i in (1, 2, 3)]
              for name, frame in point_frames(request["axle"], request["architecture"]).items()}
    if any(not math.isfinite(x) for point in points.values() for x in point):
        raise RuntimeError("Travel returned nonfinite geometry")
    return points


def _verify(row: dict, pose: dict, axle: str, varying: str | None = None) -> None:
    expected = {"heave_mm": ("knc.heave", pose["heave_mm"] / 1000),
                "roll_deg": ("knc.roll", math.radians(pose["roll_deg"]))}
    if axle == "front":
        expected["steer_deg"] = ("inputs.steer", math.radians(pose["steer_deg"]))
    if any(not math.isclose(row.get(k, math.nan), value, abs_tol=1e-8)
           for axis, (k, value) in expected.items() if axis != varying):
        raise RuntimeError(f"{axle} travel runtime did not impose the requested pose")


@lru_cache(maxsize=256)
def _solve(request_json: str) -> dict:
    request = json.loads(request_json)
    row = _run_rows(request)[-1]
    _verify(row, request["pose"], request["axle"])
    return _points(row, request)


@lru_cache(maxsize=48)
def _trajectory(request_json: str) -> list:
    request = json.loads(request_json)
    axis, axle = request["axis"], request["axle"]
    if axis == "steer_deg" and axle == "rear":
        row = _run_rows(request)[-1]
        _verify(row, request["pose"], axle)
        return [{"value": value, "points": _points(row, request)} for value in (-90, 90)]
    start, stop, step = {"heave_mm": (2, 56, .2), "roll_deg": (63, 117, .2),
                         "steer_deg": (0, 832, 1)}[axis]
    signal, scale = {"heave_mm": ("knc.heave", 1000), "roll_deg": ("knc.roll", 180 / math.pi),
                     "steer_deg": ("inputs.steer", 180 / math.pi)}[axis]
    samples = {}
    for row in _run_rows(request, start, stop, step):
        _verify(row, request["pose"], axle, varying=axis)
        value = round(row[signal] * scale, 8)
        samples[value] = {"value": value, "points": _points(row, request)}
    if not samples or abs(min(samples) + LIMITS[axis]) > 1e-5 or abs(max(samples) - LIMITS[axis]) > 1e-5:
        raise RuntimeError(f"{axle} travel sampling did not cover {axis}")
    return [samples[value] for value in sorted(samples)]


def _run_rows(request: dict, start: float = 0, stop: float = 0, step: float = .1) -> list:
    directory = Path(request["directory"])
    manifest, axle = request["manifest"], request["axle"]
    signals = "time|knc.heave|knc.roll|inputs.steer|" + "|".join(
        re.escape(frame) + ".*" for frame in point_frames(axle, request["architecture"]).values())
    with tempfile.TemporaryDirectory(prefix="bobsim-travel-") as temporary:
        work = Path(temporary)
        for name in manifest["runtime_file_sha256"]:
            shutil.copy2(directory / name, work / name)
        (work / "overrides.txt").write_text("".join(f"{k}={v}\n" for k, v in request["encoded"].items()))
        command = [str(work / manifest["executable"]), "-overrideFile=overrides.txt", "-r=signals.csv",
                   f"-startTime={start}", f"-stopTime={stop}", f"-stepSize={step}", f"-variableFilter={signals}",
                   "-jacobian=internalNumerical", "-nls=" + manifest["nonlinear_solver"], "-s=euler"]
        try:
            completed = subprocess.run(command, cwd=work, text=True, stdout=subprocess.PIPE,
                                       stderr=subprocess.STDOUT, timeout=15)
        except subprocess.TimeoutExpired as exc:
            raise RuntimeError(f"{axle} travel solve exceeded 15 seconds") from exc
        output = completed.stdout
        if (completed.returncode or "simulation finished successfully" not in output
                or "not found" in output.lower() or "cannot be overridden" in output.lower()):
            raise RuntimeError(f"{axle} travel solve failed: {output[-2500:]}")
        with (work / "signals.csv").open() as stream:
            rows = [{k: float(v) for k, v in row.items() if k} for row in csv.DictReader(stream)]
        if not rows:
            raise RuntimeError(f"{axle} travel solve returned no pose")
        return rows
