"""Generate a resumable, axle-specific KnC catalog in BobSim's native cache."""
from __future__ import annotations

import argparse
import csv
import math
import shutil
import tempfile
from concurrent.futures import ThreadPoolExecutor, as_completed
import json
from pathlib import Path
import subprocess
import sys
import tarfile
import time

from common import native_artifacts as native


def entries() -> list[dict]:
    """Enumerate distinct compiled axle and brake-path combinations."""
    catalog = json.loads((native.BOBLIB / "Tools/architectures.json").read_text())
    result = []
    for side in ("front", "rear"):
        for axle in catalog["axles"]:
            for brake in catalog[side + "_brakes"]:
                selection = {"front": "stabar", "rear": "stabar", "differential": "ClutchLSD",
                             "front_brakes": "Outboard", "rear_brakes": "Outboard", "rotor_effects": False}
                selection[side] = axle
                selection[side + "_brakes"] = brake
                result.append({"name": f"{side}-{axle}-{brake}", "kind": "knc-" + side,
                               "selection": selection})
    return result


def verify_calibration(directory: Path, manifest: dict) -> dict:
    """Check that hardpoint and protocol overrides change solved outputs."""
    side = manifest["identity"]["kind"].split("-")[1]
    hardpoint = f"pVehicle.chassis.{side}Axle.geometry.upperFore_i[3]"
    parameters = manifest["parameters"]
    required = (hardpoint, "heaveMagnitude", "rollMagnitude", "forceMagnitude", "lateralLeftShare")
    if any(name not in parameters for name in required):
        raise ValueError("Missing required KnC runtime setters")
    original = float(parameters[hardpoint]["start"])
    heave = float(parameters["heaveMagnitude"]["start"])
    frame = "axle.leftWishboneUprightLoop.upperFrame_i.r_0[3]"
    responses = []
    with tempfile.TemporaryDirectory(prefix="knc-probe-") as temporary:
        work = Path(temporary)
        for name in manifest["runtime_file_sha256"]:
            shutil.copy2(directory / name, work / name)
        for overrides in ({}, {hardpoint: original + .002, "heaveMagnitude": heave / 2}):
            encoded = native.validate_overrides(manifest, overrides)
            (work / "probe.txt").write_text("\n".join(f"{k}={v}" for k, v in encoded.items()) + "\n")
            stop = 5 if overrides else (832 if side == "front" else 118)
            command = [str(work / manifest["executable"]), "-r=probe.csv", f"-stopTime={stop}", "-stepSize=0.1",
                       "-s=euler", "-jacobian=internalNumerical", "-nls=" + manifest["nonlinear_solver"],
                       "-variableFilter=time|knc.heave|axle.leftWishboneUprightLoop.upperFrame_i.r_0.*"]
            if overrides:
                command.append("-overrideFile=probe.txt")
            completed = subprocess.run(command, cwd=work, capture_output=True, text=True, timeout=120)
            if completed.returncode or "simulation finished successfully" not in completed.stdout:
                raise ValueError("Calibration probe failed: " + completed.stdout[-2000:] + completed.stderr[-1000:])
            with (work / "probe.csv").open() as stream:
                rows = list(csv.DictReader(stream))
            if not rows or float(rows[-1]["time"]) < stop - 1e-6:
                raise ValueError("Calibration probe ended early")
            if any(not math.isfinite(float(value)) for row in rows for key, value in row.items() if key):
                raise ValueError("Calibration probe returned nonfinite outputs")
            sample = min(rows, key=lambda row: abs(float(row["time"]) - 5))
            responses.append((float(rows[0][frame]), float(sample["knc.heave"])))
    delta = responses[1][0] - responses[0][0]
    if not math.isclose(delta, .001, abs_tol=1e-7):
        raise ValueError(f"Hardpoint override did not reach the solved frame: {delta}")
    if abs(responses[0][1]) < 1e-6 or not math.isclose(responses[1][1], responses[0][1] / 2, abs_tol=1e-7):
        raise ValueError("Heave amplitude override did not reach the prescribed motion")
    return {"hardpoint_delta_m": delta, "heave_ratio": responses[1][1] / responses[0][1],
            "full_protocol_stop_s": 832 if side == "front" else 118}


def generate(entry: dict, output: Path) -> dict:
    """Build or reuse one verified artifact and archive its runtime bundle."""
    started = time.monotonic()
    log = output / (entry["name"] + ".log")
    command = [sys.executable, "-m", "common.native_artifacts", "--selection",
               json.dumps(entry["selection"]), "--kind", entry["kind"]]
    with log.open("w") as stream:
        completed = subprocess.run(command, cwd=native.ROOT, stdout=stream, stderr=subprocess.STDOUT)
    result = {**entry, "seconds": round(time.monotonic() - started, 2), "log": log.name}
    if completed.returncode:
        return {**result, "status": "failed", "returncode": completed.returncode}
    directory = native.artifact_dir(entry["selection"], entry["kind"])
    manifest = native.checked_manifest(directory)
    if manifest["identity"] != native.identity(entry["selection"], entry["kind"]):
        raise ValueError("Source changed during catalog generation")
    calibration = verify_calibration(directory, manifest)
    files = sorted([*manifest["runtime_file_sha256"], "manifest.json"])
    archive = output / (directory.name + ".tar.gz")
    temporary = archive.with_suffix(".tmp")
    with tarfile.open(temporary, "w:gz", compresslevel=6) as bundle:
        for name in files:
            bundle.add(directory / name, arcname=f"{directory.name}/{name}")
    temporary.replace(archive)
    return {**result, "status": "ready", "cache_key": directory.name, "identity": manifest["identity"],
            "archive": archive.name, "calibration_check": calibration,
            "runtime_bytes": sum((directory / name).stat().st_size for name in files),
            "compressed_bytes": archive.stat().st_size, "editable_parameters": len(manifest["parameters"])}


def main() -> int:
    """Plan or generate the catalog with bounded compiler concurrency."""
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--build", action="store_true", help="Compile missing binaries; otherwise print the plan")
    parser.add_argument("--jobs", type=int, default=2, help="Concurrent compilers (default: 2)")
    parser.add_argument("--output", type=Path, default=native.CACHE.parent / "knc_catalog")
    args = parser.parse_args()
    if args.jobs < 1:
        parser.error("--jobs must be positive")
    plan = entries()
    if not args.build:
        print(json.dumps({"count": len(plan), "entries": plan}, indent=2))
        return 0
    args.output.mkdir(parents=True, exist_ok=True)
    results = []
    with ThreadPoolExecutor(max_workers=args.jobs) as executor:
        pending = {executor.submit(generate, item, args.output): item for item in plan}
        for future in as_completed(pending):
            item = pending[future]
            try:
                result = future.result()
            except (OSError, ValueError, KeyError, subprocess.TimeoutExpired) as exc:
                result = {**item, "status": "failed", "error": str(exc)}
            results.append(result)
            report = {"count": len(plan), "completed": len(results),
                      "ready": sum(row["status"] == "ready" for row in results),
                      "runtime_bytes": sum(row.get("runtime_bytes", 0) for row in results),
                      "compressed_bytes": sum(row.get("compressed_bytes", 0) for row in results),
                      "entries": sorted(results, key=lambda row: row["name"])}
            temporary = args.output / "index.tmp"
            temporary.write_text(json.dumps(report, indent=2) + "\n")
            temporary.replace(args.output / "index.json")
            print(f"[{len(results)}/{len(plan)}] {item['name']}: {result['status']}", flush=True)
    return int(any(row["status"] != "ready" for row in results))


if __name__ == "__main__":
    raise SystemExit(main())
