"""Solve unloaded, simultaneous axle travel using cached native KnC artifacts."""
from __future__ import annotations

import csv
from concurrent.futures import ThreadPoolExecutor
from functools import lru_cache
import json
import math
from pathlib import Path
import shutil
import subprocess
import tempfile

from app.native_calibration import vehicle_overrides
from common import native_artifacts as artifacts

LIMITS = {"heave_mm": 38.1, "roll_deg": 1.25, "steer_deg": 90.0}


def travel_payload(vehicle: dict, pose: dict) -> dict:
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
        encoded = artifacts.validate_overrides(manifest, overrides)
        runtime = {k: manifest[k] for k in ("executable", "runtime_file_sha256", "nonlinear_solver")}
        requests.append(json.dumps({"directory": directory.as_posix(), "manifest": runtime,
                                    "encoded": encoded, "pose": pose, "axle": axle,
                                    "architecture": vehicle["architecture"][axle]}, sort_keys=True))
    with ThreadPoolExecutor(max_workers=2) as executor:
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


@lru_cache(maxsize=256)
def _solve(request_json: str) -> dict:
    request = json.loads(request_json)
    directory = Path(request["directory"])
    manifest, pose, axle = request["manifest"], request["pose"], request["axle"]
    with tempfile.TemporaryDirectory(prefix="bobsim-travel-") as temporary:
        work = Path(temporary)
        for name in manifest["runtime_file_sha256"]:
            shutil.copy2(directory / name, work / name)
        (work / "overrides.txt").write_text("".join(f"{k}={v}\n" for k, v in request["encoded"].items()))
        command = [str(work / manifest["executable"]), "-overrideFile=overrides.txt", "-r=signals.csv",
                   "-stopTime=0", "-stepSize=0.1", "-variableFilter=time|knc.heave|knc.roll|inputs.steer|axle.*r_0.*",
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
            rows = list(csv.DictReader(stream))
        if not rows:
            raise RuntimeError(f"{axle} travel solve returned no pose")
        row = {k: float(v) for k, v in rows[-1].items() if k}
        expected = {"knc.heave": pose["heave_mm"] / 1000, "knc.roll": math.radians(pose["roll_deg"])}
        if axle == "front":
            expected["inputs.steer"] = math.radians(pose["steer_deg"])
        if any(not math.isclose(row.get(k, math.nan), v, abs_tol=1e-8) for k, v in expected.items()):
            raise RuntimeError(f"{axle} travel runtime did not impose the requested pose")
        points = {name: [row[f"{frame}[{i}]"] for i in (1, 2, 3)]
                  for name, frame in point_frames(axle, request["architecture"]).items()}
        if any(not math.isfinite(x) for point in points.values() for x in point):
            raise RuntimeError(f"{axle} travel returned nonfinite geometry")
        return points
