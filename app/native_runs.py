"""Isolated native experiment runs and BobLib KnC plot conversion."""
from __future__ import annotations

import argparse
import csv
import hashlib
import json
import math
from pathlib import Path
import shutil
import subprocess
import tempfile
from concurrent.futures import ThreadPoolExecutor
from typing import Any

from app.native_calibration import vehicle_overrides
from app.native_knc import curves as knc_curves, metadata as knc_metadata
from common import native_artifacts as artifacts



def run(vehicle: dict, kind: str, settings: dict | None = None) -> dict:
    """Run a fresh process with validated calibration and retained provenance."""
    selection = artifacts.architecture(vehicle)
    directory = artifacts.artifact_dir(selection, kind)
    try:
        manifest = artifacts.checked_manifest(directory)
    except FileNotFoundError as exc:
        raise ValueError(f"Build {artifacts.KINDS[kind]} in Architecture first") from exc
    if manifest["identity"] != artifacts.identity(selection, kind):
        raise ValueError("Binary does not match the selected architecture and current sources")
    overrides = vehicle_overrides(vehicle, manifest, artifacts.ROOT)
    settings = dict(settings or {})
    kinematics_only = settings.pop("kinematics_only", False)
    if not isinstance(kinematics_only, bool):
        raise ValueError("kinematics_only must be a boolean")
    if kind.startswith("knc-"):
        if settings.keys() - {"forceMagnitude", "include_stabilizer"}:
            raise ValueError("Unknown KnC setting")
        # Geometry comes from unloaded plateaus; jacking uses the intervening
        # load pulses at the same poses. The editor keeps the stabilizer removed.
        side = kind.split("-")[1]
        include_bar = settings.get("include_stabilizer", False)
        if not isinstance(include_bar, bool):
            raise ValueError("include_stabilizer must be a boolean")
        rate = vehicle[side]["actuation"].get("stabar", {}).get("rate_n_m_per_rad", 0)
        overrides.update({"forceMagnitude": settings.get("forceMagnitude", 1000.0),
                          "stabilizerRate": rate if include_bar and not kinematics_only else 0.0})
        stop = 832.0 if kind == "knc-front" else 118.0
        step = 0.1
        signals = ("time|knc.*|inputs.steer|steerPosition.flange.tau|chassisActuator.rollDOF.tau|"
                   "leftLoad.worldForce.force.*|rightLoad.worldForce.force.*|axle.(left|right)CP.r_0.*|"
                   "brakes.*|chassisActuator.chassisFrame.r_0.*|"
                   "axle.(left|right)WishboneUprightLoop.(upper|lower)Frame_(i|o).r_0.*")
    else:
        stop = float(settings.pop("duration", 10.0))
        step = 0.002
        signals = "time|terminationStatus|accX|accY|velX|velY|yawVel|sideslip|Fz_.*|handwheelAngle"
        allowed = {"driver.useMode", "driver.steerStart", "driver.frRampSteerHeight", "driver.stepDuration"}
        if settings.keys() - allowed:
            raise ValueError("Unknown maneuver setting")
        overrides.update(settings)
    if not math.isfinite(stop) or not 0 < stop <= (120 if kind == "maneuver" else 832):
        raise ValueError("Duration must be between 0 and 120 seconds")
    encoded = artifacts.validate_overrides(manifest, overrides)
    request = {"identity": manifest["identity"], "overrides": overrides, "settings": settings,
               "stop": stop, "adapter": hashlib.sha256(Path(__file__).read_bytes()
                   + Path(__file__).with_name("native_knc.py").read_bytes()).hexdigest(),
               "plot_reference": {
                   "masses": [vehicle.get(key) for key in ("sprung_mass", "driver_mass")],
                   "wheel_centers": [vehicle[key]["suspension"]["wheel_center_m"] for key in ("front", "rear")],
               } if kind.startswith("knc-") else None}
    key = hashlib.sha256(json.dumps(request, sort_keys=True).encode()).hexdigest()
    results = artifacts.ROOT / "app/user_data/results/native"
    result_dir = results / key
    if (result_dir / "result.json").exists():
        return json.loads((result_dir / "result.json").read_text())
    results.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix="run-", dir=results) as temporary:
        work = Path(temporary)
        for name in manifest["runtime_file_sha256"]:
            shutil.copy2(directory / name, work / name)
        (work / "overrides.txt").write_text("\n".join(f"{k}={v}" for k, v in encoded.items()) + "\n")
        command = [str(work / manifest["executable"]), "-overrideFile=overrides.txt", "-r=signals.csv",
                   f"-stopTime={stop}", f"-stepSize={step}", f"-variableFilter={signals}",
                   "-jacobian=internalNumerical", "-nls=" + manifest["nonlinear_solver"],
                   "-s=" + ("dassl" if kind == "maneuver" else "euler")]
        try:
            completed = subprocess.run(command, cwd=work, text=True, stdout=subprocess.PIPE,
                                       stderr=subprocess.STDOUT, timeout=180)
        except subprocess.TimeoutExpired as exc:
            output = exc.stdout or b""
            (work / "run.log").write_text(output.decode(errors="replace") if isinstance(output, bytes) else output)
            failure = results / ("failed-" + work.name)
            work.rename(failure)
            raise RuntimeError(f"Native run exceeded 180 seconds; diagnostics: {failure}") from exc
        (work / "run.log").write_text(completed.stdout)
        print(completed.stdout, flush=True)
        if completed.returncode or "simulation finished successfully" not in completed.stdout:
            failure = results / ("failed-" + work.name)
            work.rename(failure)
            raise RuntimeError(f"Native run failed (exit {completed.returncode}); diagnostics: {failure}: "
                               + completed.stdout[-3000:])
        if "not found" in completed.stdout.lower() or "cannot be overridden" in completed.stdout.lower():
            raise RuntimeError("The native runtime rejected a requested parameter")
        with (work / "signals.csv").open() as stream:
            rows = [{k: float(v) for k, v in row.items() if k} for row in csv.DictReader(stream)]
        if not rows or any(not math.isfinite(v) for row in rows for v in row.values()):
            raise RuntimeError("Native run returned empty or nonfinite signals")
        if kind.startswith("knc-") and rows[-1]["time"] < stop - 1e-5:
            raise RuntimeError("KnC protocol ended before completion")
        status = int(rows[-1].get("terminationStatus", 0))
        result = {"kind": kind, "identity": manifest["identity"], "termination_status": status,
                  "final_time": rows[-1]["time"], "samples": len(rows),
                  "csv": (result_dir / "signals.csv").relative_to(artifacts.ROOT).as_posix(),
                  "log": (result_dir / "run.log").relative_to(artifacts.ROOT).as_posix(),
                  "overrides": overrides}
        if kind.startswith("knc-"):
            result["curves"] = knc_curves(rows, vehicle, side, traction=kind.endswith("-traction"))
        (work / "request.json").write_text(json.dumps(request, indent=2))
        (work / "vehicle.json").write_text(json.dumps(vehicle, indent=2))
        (work / "result.json").write_text(json.dumps(result, indent=2))
        for name in manifest["runtime_file_sha256"]:
            (work / name).unlink()
        if not result_dir.exists():
            work.rename(result_dir)
    return result


def kinematic_curves_payload(vehicle: dict, sweep_m=None) -> dict:
    """Serve geometry plots from the same native KnC artifacts as simulations."""
    if sweep_m is not None:
        raise ValueError("Native KnC uses the rig's documented heave/roll protocol")
    payload: dict[str, Any] = {"model": "BobLib native KnC",
               "basis": ("Unloaded heave/roll/steer geometry; 1000 N force pulses; "
                         "rear longitudinal response uses shaft traction; stabilizer removed"),
               "available": True, "axles": {}, "warnings": [], "curve_meta": [], "x_axes": {},
               "sweep_m": [], "roll_deg": [], "steer_m": []}
    payload["curve_meta"] = knc_metadata()
    with ThreadPoolExecutor(max_workers=3) as executor:
        pending = {side: executor.submit(run, vehicle, "knc-" + side, {"kinematics_only": True})
                   for side in ("front", "rear")}
        traction = executor.submit(run, vehicle, "knc-rear-traction", {"kinematics_only": True})
        for side, future in pending.items():
            try:
                result = future.result()
                curves = result["curves"]
                payload["x_axes"].update(curves["x_axes"])
                payload["axles"][side] = {"ok": True, "curves": curves["curves"],
                                           "x_axes": curves["x_axes"], "points": [],
                                           "solved_count": 11, "roll_solved_count": 11,
                                           "steer_solved_count": 7 if side == "front" else 0,
                                           "steer_x_deg": curves["x_axes"].get("pinion_deg", []), "warnings": []}
                if side == "rear":
                    for key in ("bump_jacking_n", "bump_jacking_ratio"):
                        payload["axles"][side]["curves"].pop(key, None)
            except (ValueError, RuntimeError, OSError) as exc:
                payload["warnings"].append(str(exc))
                payload["axles"][side] = {"ok": False, "curves": {}, "points": [], "warnings": [str(exc)]}
        try:
            traction_result = traction.result()
            rear = payload["axles"]["rear"]
            if rear["ok"]:
                drive_curves = traction_result["curves"]["curves"]
                rear["curves"]["bump_anti_squat_pct"] = drive_curves["bump_anti_squat_pct"]
                # Match the longitudinal raw jacking plots to the traction-based
                # processed rear output, retaining braking CSVs in native results.
                for key in ("bump_jacking_n", "bump_jacking_ratio"):
                    rear["curves"][key] = drive_curves[key]
                rear["traction_csv"] = traction_result["csv"]
        except (ValueError, RuntimeError, OSError) as exc:
            message = "Rear anti-squat unavailable: " + str(exc)
            payload["warnings"].append(message)
            payload["axles"]["rear"]["warnings"].append(message)
    payload["available"] = any(axle["ok"] for axle in payload["axles"].values())
    payload["sweep_m"] = [x / 1000 for x in payload["x_axes"].get("heave_mm", [])]
    payload["roll_deg"] = payload["x_axes"].get("roll_deg", [])
    return payload


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("request", type=Path)
    args = parser.parse_args()
    request = json.loads(args.request.read_text())
    print("BOBSIM_NATIVE_RESULT=" + json.dumps(run(request["vehicle"], request["kind"], request.get("settings"))))
