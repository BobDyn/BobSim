"""Behavioral contracts for native architecture selection and calibration."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path

import pytest

from common import native_artifacts as native
from app.native_runs import knc_curves


def test_architecture_rejects_unknown_choices():
    with pytest.raises(ValueError, match="front"):
        native.architecture({"architecture": {"front": "anything", "rear": "direct"}})
    with pytest.raises(ValueError, match="rear_brakes"):
        native.architecture({"architecture": {"front": "direct", "rear": "direct", "rear_brakes": "unknown"}})


def test_architecture_cache_changes_for_structural_choices_not_setup():
    vehicle = {"architecture": {"front": "direct", "rear": "bellcrank"}}
    original = native.artifact_dir(native.architecture(vehicle), "maneuver")
    vehicle["driver_mass"] = {"mass_kg": 90}
    assert native.artifact_dir(native.architecture(vehicle), "maneuver") == original
    vehicle["architecture"]["rear_brakes"] = "Inboard"
    assert native.artifact_dir(native.architecture(vehicle), "maneuver") != original
    assert native.artifact_dir(native.architecture(vehicle), "knc-front") != original


def test_runtime_bundle_integrity(tmp_path: Path):
    executable = tmp_path / "simulation"
    executable.write_bytes(b"example executable")
    manifest = {"executable": "simulation", "runtime_file_sha256": {
        "simulation": hashlib.sha256(executable.read_bytes()).hexdigest()}}
    (tmp_path / "manifest.json").write_text(json.dumps(manifest))
    assert native.checked_manifest(tmp_path) == manifest
    executable.write_bytes(b"different executable")
    with pytest.raises(ValueError, match="changed runtime"):
        native.checked_manifest(tmp_path)


def test_setters_reject_derived_structural_unknown_and_invalid_values():
    manifest = {"parameters": {"mass": {"type": "Real", "min": "0"},
                               "count": {"type": "Integer"}, "enabled": {"type": "Boolean"}},
                "derived": {"totalMass": {}}, "structural": {"axle": {}}}
    assert native.validate_overrides(manifest, {"mass": 42, "count": 3, "enabled": False}) == {
        "mass": "42", "count": "3", "enabled": "false"}
    for values in ({"totalMass": 1}, {"axle": 1}, {"typo": 1}, {"mass": float("nan")},
                   {"mass": -1}, {"count": 1.5}, {"enabled": "false"}):
        with pytest.raises(ValueError):
            native.validate_overrides(manifest, values)


def test_knc_samples_unloaded_plateaus_and_converts_units():
    rows = []
    for t in range(119):
        row = {"time": t, "knc.heave": t / 1000, "knc.roll": t / 1000}
        for signal in ("leftGamma", "leftToe", "leftCaster", "leftKpi", "leftMechTrail", "leftMechScrub"):
            row["knc." + signal] = t / 1000
        rows.append(row)
    result = knc_curves(rows)
    assert result["x_axes"]["jounce_mm"] == [-float(t) for t in range(55, 4, -5)]
    assert result["curves"]["bump_scrub_mm"] == [float(t) for t in range(55, 4, -5)]
    assert len(result["curves"]["roll_camber_deg"]) == 11


def test_knc_wrapper_binds_selected_axle_and_stabilizer_geometry():
    selected = native.architecture({"architecture": {"front": "direct", "rear": "bellcrank_stabar"}})
    _, source = native.wrapper(selected, "knc-rear")
    assert "axle(pAxle(actuation=pVehicle.chassis.rearAxle.actuation))" in source
    assert "leftArmEnd=pVehicle.chassis.rearAxle.stabilizer.leftArmEnd" in source
    assert "KnCLocked" in source


def test_parameter_alias_is_encoded_as_independent_runtime_setter():
    manifest = {"parameters": {"pVehicle.controller.tau_max": {
        "type": "Real", "runtime_name": "nativeDriveTorqueLimit"}}}
    assert native.validate_overrides(manifest, {"pVehicle.controller.tau_max": 180}) == {
        "nativeDriveTorqueLimit": "180"}


def test_native_calibration_recomputes_dependencies_in_fresh_processes(tmp_path):
    """Exercise actual compiled dependencies, not just accepted override names."""
    import os
    import re
    import shutil
    import subprocess
    from app import app

    if os.environ.get("BOBSIM_NATIVE_INTEGRATION") != "1":
        pytest.skip("Set BOBSIM_NATIVE_INTEGRATION=1 after building the default maneuver artifact")
    vehicle = app.config_payload("vehicle")["data"]
    directory = native.artifact_dir(native.architecture(vehicle), "maneuver")
    manifest = native.checked_manifest(directory)
    for name in manifest["runtime_file_sha256"]:
        shutil.copy2(directory / name, tmp_path / name)
    names = ["pVehicle.chassis.frame.driverMass.m", "pVehicle.controller.tau_max",
             "pVehicle.controller.finalDriveRatio", "pVehicle.brakes.maxTorque",
             "pVehicle.brakes.differentialBrakeRatio", "pVehicle.chassis.frame.mass.m"]
    values = {names[0]: 75, names[1]: 180,
              "pVehicle.controller.mechanicalBrakeTorqueLimit": 1200,
              "pVehicle.transmission.gearRatio": 4, "pVehicle.driveline.inputRatio": 2}
    results = []
    for overrides in ({}, values, {}):
        encoded = native.validate_overrides(manifest, overrides)
        (tmp_path / "overrides.txt").write_text("\n".join(f"{k}={v}" for k, v in encoded.items()) + "\n")
        command = [str(tmp_path / manifest["executable"]), "-stopTime=0", "-r=probe.csv",
                   "-s=dassl", "-jacobian=internalNumerical", "-output=" + ",".join(names)]
        if overrides:
            command.append("-overrideFile=overrides.txt")
        completed = subprocess.run(command, cwd=tmp_path, capture_output=True, text=True, timeout=120)
        assert completed.returncode == 0, completed.stdout + completed.stderr
        result = {}
        for name in names:
            matches = re.findall(re.escape(name) + r"\s*=\s*([-+\d.eE]+)", completed.stdout)
            assert matches, completed.stdout
            result[name] = float(matches[-1])
        results.append(result)
    baseline, changed, restored = results
    assert restored == baseline
    assert changed[names[0]] == 75
    assert changed[names[1]] == 180
    assert changed[names[2]] == 8
    assert changed[names[3]] == 1200
    assert changed[names[4]] == 2
    assert changed[names[5]] - baseline[names[5]] == pytest.approx(75 - baseline[names[0]])


def test_server_connects_native_jobs_to_the_shared_job_store(monkeypatch):
    from app import app, actions, native_service
    app._sync_server_runtime()
    assert actions.JOBS is app.JOBS
    observed = []
    monkeypatch.setattr(actions, "_launch_job", lambda *args: observed.append(args) or {"id": "native-build"})
    result = native_service.start_build({"architecture": {"front": "direct", "rear": "direct"}}, "knc-front")
    assert result["id"] == "native-build"
    assert observed[0][0][0].requires_external_toolchain
    assert "common.native_artifacts" in observed[0][3]
