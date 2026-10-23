"""Build and reuse architecture-specific BobLib experiment executables."""
from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
import math
import platform
from pathlib import Path
import shutil
import subprocess
import tempfile
import uuid
import xml.etree.ElementTree as ET
from typing import Any

from common.vehicle_io import repo_root

ROOT = repo_root()
BOBLIB = ROOT / "engines/boblib"
CACHE = ROOT / "app/user_data/cache/native"
KINDS = {"knc-front": "Front KnC", "knc-rear": "Rear KnC", "maneuver": "Maneuvers"}
MANEUVER_SETTERS = {
    "pVehicle.controller.tau_max": "nativeDriveTorqueLimit",
    "pVehicle.controller.mechanicalBrakeTorqueLimit": "nativeBrakeTorqueLimit",
    "pVehicle.transmission.gearRatio": "nativeTransmissionRatio",
    "pVehicle.driveline.inputRatio": "nativeDifferentialInputRatio",
}
AXLES = {"direct": "direct", "bellcrank": "bellcrank", "bellcrank_stabar": "stabar"}


def exporter():
    """Load the exporter belonging to the checked-out BobLib revision."""
    spec = importlib.util.spec_from_file_location("boblib_export", BOBLIB / "Tools/export_fmu.py")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def architecture(vehicle: dict) -> dict:
    """Validate structural choices separately from editable calibration."""
    if not isinstance(vehicle, dict) or not isinstance(vehicle.get("architecture"), dict):
        raise ValueError("Vehicle architecture must be an object")
    raw = vehicle["architecture"]
    catalog = json.loads((BOBLIB / "Tools/architectures.json").read_text())
    result: dict[str, Any] = {}
    for axle in ("front", "rear"):
        value = raw.get(axle)
        if value not in AXLES:
            raise ValueError(f"Select a supported {axle} suspension")
        result[axle] = AXLES[value]
    for key, choices in (("differential", "differentials"), ("front_brakes", "front_brakes"),
                         ("rear_brakes", "rear_brakes")):
        value = raw.get(key, catalog["defaults"][key])
        if value not in catalog[choices]:
            raise ValueError(f"Unsupported {key}: {value}")
        result[key] = value
    rotor = raw.get("rotor_effects", False)
    if not isinstance(rotor, bool):
        raise ValueError("Spatial rotor mechanics must be a boolean")
    result["rotor_effects"] = rotor
    return result


def identity(selection: dict, kind: str) -> dict:
    """Identify sources, experiment, architecture, and host ABI."""
    if kind not in KINDS:
        raise ValueError("Unknown native experiment")
    builder = "native-v1:" + wrapper(selection, kind)[1] + exporter().FLAGS
    return {"architecture": selection, "kind": kind,
            "source": exporter().source_fingerprint(BOBLIB)["sha256"],
            "builder": hashlib.sha256(builder.encode()).hexdigest(),
            "platform": {"system": platform.system(), "machine": platform.machine()}}


def artifact_dir(selection: dict, kind: str) -> Path:
    key = hashlib.sha256(json.dumps(identity(selection, kind), sort_keys=True).encode()).hexdigest()
    return CACHE / key


def checked_manifest(directory: Path) -> dict:
    """Reject incomplete, relocated incorrectly, or modified runtime bundles."""
    manifest = json.loads((directory / "manifest.json").read_text())
    for name, digest in manifest["runtime_file_sha256"].items():
        if Path(name).name != name:
            raise ValueError("Invalid runtime file name")
        path = directory / name
        if not path.is_file() or hashlib.sha256(path.read_bytes()).hexdigest() != digest:
            raise ValueError(f"Missing or changed runtime file: {name}")
    if manifest["executable"] not in manifest["runtime_file_sha256"]:
        raise ValueError("Executable is not covered by the manifest")
    return manifest


def status(vehicle: dict) -> dict:
    """Report usable artifacts, never infer availability from a directory alone."""
    selection = architecture(vehicle)
    artifacts = []
    for kind, label in KINDS.items():
        directory = artifact_dir(selection, kind)
        ready, reason = False, "Build required"
        try:
            manifest = checked_manifest(directory)
            ready = manifest["identity"] == identity(selection, kind)
            reason = "Ready to reuse" if ready else "Sources or architecture changed"
        except (OSError, ValueError, KeyError):
            pass
        artifacts.append({"kind": kind, "label": label, "ready": ready, "message": reason})
    return {"architecture": selection, "artifacts": artifacts,
            "fixed": json.loads((BOBLIB / "Tools/architectures.json").read_text())["fixed_models"]}


def wrapper(selection: dict, kind: str) -> tuple[str, str]:
    """Create wrappers outside BobLib, keeping its checked-in models untouched."""
    exp = exporter()
    base_name, base_source = exp.vehicle_model(**selection)
    name = base_name.replace("BobLibVehicle", "BobSim" + kind.title().replace("-", ""))
    if kind == "maneuver":
        source = base_source.replace(base_name, name).replace(
            "BobLib.Experiments.Standards.VehicleFMI(", "BobLib.Experiments.Standards.VehicleSim(")
        declarations = "\n".join(
            f'  parameter Real {runtime} = defaultVehicle.{public.removeprefix("pVehicle.")} '
            f'"Independent {public} calibration" annotation(Evaluate=false);'
            for public, runtime in MANEUVER_SETTERS.items())
        source = source.replace(f"model {name}\n", f"model {name}\n{declarations}\n")
        source = source.replace("    pVehicle(", "    pVehicle(controller(tau_max=nativeDriveTorqueLimit, "
                                "mechanicalBrakeTorqueLimit=nativeBrakeTorqueLimit), "
                                "transmission(gearRatio=nativeTransmissionRatio), "
                                "driveline(inputRatio=nativeDifferentialInputRatio), ")
        return name, source
    if kind not in ("knc-front", "knc-rear"):
        raise ValueError("Unknown native experiment")
    axle = kind.removeprefix("knc-")
    tag_front, _ = exp.AXLES[selection["front"]]
    tag_rear, _ = exp.AXLES[selection["rear"]]
    _, axle_model = exp.AXLES[selection[axle]]
    record = f"BobLib.Records.VehicleDefn.EVBatInvMotDiff_{tag_front}_{tag_rear}Record"
    calibration = base_source.split("    pVehicle(", 1)[1].split(
        "    redeclare record VehicleRecord", 1)[0].rstrip().removesuffix(",")
    rig = "KnCSteerable" if axle == "front" else "KnCLocked"
    axle_binding = ""
    if selection[axle] == "stabar":
        base = f"pVehicle.chassis.{axle}Axle.stabilizer"
        axle_binding = f"(pAxle(stabilizer(leftArmEnd={base}.leftArmEnd, leftBarEnd={base}.leftBarEnd)))"
    return name, f'''model {name}
  constant {record} defaultVehicle;
  extends BobLib.Experiments.Standards.{rig}(
    final headless=true,
    final useRearAxle={str(axle == 'rear').lower()},
    axle(pAxle(actuation=pVehicle.chassis.{axle}Axle.actuation)),
    final brakePlacement=BobLib.Brakes.Types.Placement.{selection[axle + '_brakes']},
    redeclare record VehicleRecord = {record},
    redeclare model AxleModel = BobLib.Chassis.Suspension.{axle_model}{axle_binding},
    pVehicle({calibration});
end {name};
'''


def parameter_contract(xml: Path) -> dict:
    """Expose only compiler-confirmed editable parameters; retain diagnostics."""
    exp = exporter()
    result: dict[str, dict[str, Any]] = {"parameters": {}, "derived": {}, "structural": {}}
    for variable in ET.parse(xml).getroot().findall("./ModelVariables/ScalarVariable"):
        name = variable.get("name", "")
        if not (name.startswith(("pVehicle.", "pInitialization.", "driver.")) or "." not in name
                or name in {"inputs.heaveSource.offset[1]", "inputs.rollSource.offset[1]"}):
            continue
        scalar = next(iter(variable))
        meta = {**variable.attrib, **scalar.attrib, "type": scalar.tag}
        derived = name.startswith(exp.DERIVED) or name in exp.DERIVED_NAMES
        editable = variable.get("causality") == "parameter" and variable.get("isValueChangeable") == "true"
        # Native init XML can mark aliases as editable. The source contract remains
        # authoritative: dependent fields are never offered as independent setters.
        if derived or variable.get("causality") == "calculatedParameter":
            result["derived"][name] = meta
        elif editable:
            result["parameters"][name] = meta
        elif variable.get("variability") in ("parameter", "constant"):
            result["structural"][name] = meta
    for public, runtime in MANEUVER_SETTERS.items():
        if runtime in result["parameters"]:
            result["parameters"][public] = {**result["parameters"].pop(runtime), "runtime_name": runtime}
            result["derived"].pop(public, None)
            result["structural"].pop(public, None)
    for axle in ("frontAxle", "rearAxle"):
        prefix = f"pVehicle.chassis.{axle}.geometry."
        present = [k for group in result.values() for k in group if k.startswith(prefix)]
        frozen = [k for k in present if k not in result["parameters"]]
        if frozen:
            raise ValueError("Suspension geometry was frozen: " + ", ".join(frozen))
    return result


def build(selection: dict, kind: str) -> Path:
    """Compile into a temporary bundle and publish only after initialization."""
    expected = identity(selection, kind)
    destination = artifact_dir(selection, kind)
    if destination.exists():
        try:
            cached = checked_manifest(destination)
            if cached["identity"] == expected:
                return destination
        except (OSError, ValueError, KeyError):
            pass
        # Keep the rejected bundle for diagnosis while allowing an explicit rebuild.
        destination.rename(CACHE / ("invalid-" + uuid.uuid4().hex))
    CACHE.mkdir(parents=True, exist_ok=True)
    exp = exporter()
    name, source = wrapper(selection, kind)
    with tempfile.TemporaryDirectory(prefix="build-", dir=CACHE) as temporary:
        work = Path(temporary)
        (work / f"{name}.mo").write_text(source)
        flags = exp.FLAGS.replace(" --fmiFlags=s:cvode", "")
        stop = 10 if kind == "maneuver" else (832 if kind == "knc-front" else 118)
        script = f'''loadModel(Modelica, {{"4.1.0"}});
loadModel(VehicleInterfaces, {{"2.0.2"}});
loadFile({json.dumps(str(BOBLIB / 'BobLib/package.mo'))});
loadFile({json.dumps(str(work / (name + '.mo')))});
setCommandLineOptions({json.dumps(flags)});
buildModel({name}, stopTime={stop}, numberOfIntervals={5000 if kind == 'maneuver' else stop * 10},
  tolerance=1e-6, outputFormat="csv");
getErrorString();
'''
        (work / "build.mos").write_text(script)
        result = subprocess.run(["omc", "build.mos"], cwd=work, text=True,
                                stdout=subprocess.PIPE, stderr=subprocess.STDOUT, timeout=1800)
        print(result.stdout, flush=True)
        (work / "build.log").write_text(result.stdout)
        executable = name + (".exe" if platform.system() == "Windows" else "")
        if result.returncode or not (work / executable).is_file():
            raise RuntimeError("Native compilation failed; see the build job log")
        manifest = parameter_contract(work / f"{name}_init.xml")
        settings = ET.parse(work / f"{name}_init.xml")
        experiment = settings.find("DefaultExperiment")
        if experiment is None:
            raise ValueError("Native artifact has no default experiment")
        experiment.set("stopTime", "0")
        settings.write(work / "check_init.xml")
        checked = subprocess.run([str(work / executable), "-f=check_init.xml", "-r=check.csv", "-nls=kinsol"],
                                 cwd=work, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, timeout=120)
        print(checked.stdout, flush=True)
        solver = "kinsol"
        if checked.returncode or "simulation finished successfully" not in checked.stdout:
            solver = "homotopy"
            checked = subprocess.run([str(work / executable), "-f=check_init.xml", "-r=check.csv", "-nls=homotopy"],
                                     cwd=work, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, timeout=120)
            print(checked.stdout, flush=True)
            if checked.returncode or "simulation finished successfully" not in checked.stdout:
                shutil.copytree(work, CACHE / ("failed-" + work.name), dirs_exist_ok=True)
                raise RuntimeError("Native artifact failed initialization; diagnostic build retained in cache")
        if identity(selection, kind) != expected:
            raise RuntimeError("Sources changed during the build; retry with stable sources")
        manifest.update(identity=expected, executable=executable, nonlinear_solver=solver,
                        compiler=subprocess.check_output(["omc", "--version"], text=True).strip())
        files = [work / executable, work / f"{name}_init.xml", work / f"{name}_info.json",
                 *work.glob(f"{name}*.bin")]
        manifest["runtime_file_sha256"] = {p.name: hashlib.sha256(p.read_bytes()).hexdigest()
                                           for p in files if p.is_file()}
        (work / "manifest.json").write_text(json.dumps(manifest, indent=2))
        for p in work.iterdir():
            retained = {"manifest.json", "build.log", f"{name}.mo"}
            if p.name not in manifest["runtime_file_sha256"] and p.name not in retained:
                if p.is_dir():
                    shutil.rmtree(p)
                else:
                    p.unlink()
        work.rename(destination)
    return destination


def validate_overrides(manifest: dict, overrides: dict) -> dict[str, str]:
    """Reject unknown, structural, derived, nonfinite, and mistyped setters."""
    result = {}
    for name, value in overrides.items():
        meta = manifest["parameters"].get(name)
        if meta is None:
            raise ValueError(f"Parameter is not editable in this artifact: {name}")
        kind = meta["type"]
        target = meta.get("runtime_name", name)
        if kind == "Boolean":
            if not isinstance(value, bool):
                raise ValueError(f"{name} requires a boolean")
            result[target] = str(value).lower()
        elif kind in ("Real", "Integer", "Enumeration"):
            if isinstance(value, bool) or not isinstance(value, (int, float)) or not math.isfinite(value):
                raise ValueError(f"{name} requires a finite number")
            if kind != "Real" and value != int(value):
                raise ValueError(f"{name} requires an integer")
            for bound, compare in (("min", lambda a, b: a < b), ("max", lambda a, b: a > b)):
                if bound in meta and compare(value, float(meta[bound])):
                    raise ValueError(f"{name} is outside its {bound} bound")
            result[target] = str(value)
        else:
            raise ValueError(f"Unsupported calibration type for {name}: {kind}")
    return result


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--selection", required=True)
    parser.add_argument("--kind", choices=KINDS, required=True)
    args = parser.parse_args()
    print(build(json.loads(args.selection), args.kind), flush=True)
