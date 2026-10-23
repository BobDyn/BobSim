"""Behavioral contracts for native architecture selection and calibration."""
from __future__ import annotations

import hashlib
import json
import math
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
    assert result["x_axes"]["heave_mm"] == [float(t) for t in range(5, 56, 5)]
    assert result["curves"]["bump_scrub_mm"] == [float(t) for t in range(5, 56, 5)]
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


def test_native_plot_payload_preserves_each_axles_parametric_axes(monkeypatch):
    from app import native_runs

    def result(_vehicle, kind, _settings):
        amplitude = 12 if kind == "knc-front" else 8
        return {"csv": "traction.csv", "curves": {"curves": {"bump_camber_deg": [1, 2, 3],
                    "bump_anti_squat_pct": [10, 20, 30], "bump_jacking_n": [1, 2, 3],
                    "bump_jacking_ratio": [.01, .02, .03]},
                           "x_axes": {"jounce_mm": [-amplitude, 0, amplitude], "roll_deg": [-1, 0, 1]}}}

    monkeypatch.setattr(native_runs, "run", result)
    payload = native_runs.kinematic_curves_payload({})
    assert payload["axles"]["front"]["x_axes"]["jounce_mm"] == [-12, 0, 12]
    assert payload["axles"]["rear"]["x_axes"]["jounce_mm"] == [-8, 0, 8]


def test_projected_rc_height_uses_native_positions_and_contact_datum():
    from app.native_knc import geometric_rc
    row = {}
    for side, sign in (("left", 1), ("right", -1)):
        points = {"upperFrame_i": (.2, .3), "upperFrame_o": (.6, .7),
                  "lowerFrame_i": (.2, .2), "lowerFrame_o": (.6, .4)}
        for name, (y, z) in points.items():
            prefix = f"axle.{side}WishboneUprightLoop.{name}.r_0"
            row[prefix + "[2]"] = sign * y
            row[prefix + "[3]"] = z + .25
        row[f"axle.{side}CP.r_0[2]"] = sign
        row[f"axle.{side}CP.r_0[3]"] = .25
    height, lateral = geometric_rc(row)
    assert height == pytest.approx(100)
    assert lateral == pytest.approx(0, abs=1e-9)
    assert geometric_rc({}) == (None, None)


def test_knc_steering_and_load_pulse_metrics_use_the_correct_protocol_samples():
    from app.native_knc import curves, MEASUREMENTS
    rows = []
    for t in range(833):
        cycle, local = divmod(t, 119)
        pose = (local - 2) // 5
        longitudinal = local in range(3, 54, 5)
        lateral = local in range(64, 115, 5)
        loaded = longitudinal or lateral
        baseline = 100 + pose * 7
        row = {"time": t, "inputs.steer": (cycle - 3) * math.pi / 6,
               "knc.heave": pose / 1000, "knc.roll": pose / 1000,
               "knc.fx": 100 if longitudinal else 0, "knc.fy": 100 if lateral else 0,
               "knc.jackingForce": -(baseline + (20 if loaded else 0)),
               "chassisActuator.rollDOF.tau": 3 * baseline + (40 if lateral else 0),
               "knc.leftFz": 100, "knc.rightFz": 140 if loaded else 100}
        for signal, _, _, _ in MEASUREMENTS.values():
            row["knc." + signal] = cycle * .001
        rows.append(row)
    vehicle = {"sprung_mass": {"mass_kg": 200, "cg_m": [0, 0, .5]},
               "driver_mass": {"mass_kg": 80, "cg_m": [0, 0, .5]},
               "front": {"suspension": {"wheel_center_m": [0, 1, 0]}},
               "rear": {"suspension": {"wheel_center_m": [-3, 1, 0]}}}
    result = curves(rows, vehicle)
    assert result["x_axes"]["pinion_deg"] == pytest.approx([-90, -60, -30, 0, 30, 60, 90])
    assert result["curves"]["bump_camber_deg"] == pytest.approx([.003 * 180 / math.pi] * 11)
    assert result["curves"]["bump_jacking_n"] == pytest.approx([20] * 11)
    assert result["curves"]["bump_anti_dive_pct"] == [None] * 11  # No contact datum.
    assert result["curves"]["roll_load_reaction_nm"] == pytest.approx([-40] * 11)
    assert result["curves"]["roll_reaction_per_fy_m"] == pytest.approx([-.4] * 11)
    assert result["curves"]["roll_force_rc_height_mm"] == [None] * 11  # Missing reference geometry.
    assert result["curves"]["roll_anti_roll_pct"] == [None] * 11  # No geometry was supplied.


def test_knc_zero_force_does_not_fabricate_jacking_coefficients():
    from app.native_knc import curves, MEASUREMENTS
    rows = []
    for t in range(119):
        row = {"time": t, "knc.heave": 0, "knc.roll": 0, "knc.fx": 0,
               "knc.fy": 0, "knc.jackingForce": 50}
        row.update({"knc." + signal: 0 for signal, _, _, _ in MEASUREMENTS.values()})
        rows.append(row)
    result = curves(rows)
    assert result["curves"]["bump_jacking_ratio"] == [None] * 11
    assert result["curves"]["roll_jacking_ratio"] == [None] * 11
    assert "pinion_deg" not in result["x_axes"]


def test_negative_geometric_anti_roll_does_not_disappear_when_net_jacking_is_zero():
    from app.native_knc import curves, MEASUREMENTS

    rows = []
    for t in range(119):
        loaded = t in range(64, 115, 5)
        row = {"time": t, "knc.heave": 0, "knc.roll": 0, "knc.fx": 0,
               "knc.fy": 100 if loaded else 0, "knc.jackingForce": 0,
               "knc.leftFz": 110 if loaded else 100, "knc.rightFz": 90 if loaded else 100}
        row.update({"knc." + signal: 0 for signal, _, _, _ in MEASUREMENTS.values()})
        for side, sign in (("left", 1), ("right", -1)):
            # Both ICs and the symmetric RC are 100 mm below a contact plane
            # at z=250 mm. The sprung CG is 500 mm above that plane.
            for name, (y, z) in {"upperFrame_i": (.2, .1), "upperFrame_o": (.6, .5),
                                 "lowerFrame_i": (.2, 0), "lowerFrame_o": (.6, .2)}.items():
                prefix = f"axle.{side}WishboneUprightLoop.{name}.r_0"
                row[prefix + "[2]"] = sign * y
                row[prefix + "[3]"] = z + .25
            row[f"axle.{side}CP.r_0[2]"] = sign
            row[f"axle.{side}CP.r_0[3]"] = .25
        rows.append(row)
    vehicle = {"sprung_mass": {"mass_kg": 200, "cg_m": [0, 0, .75]},
               "driver_mass": {"mass_kg": 80, "cg_m": [0, 0, .75]},
               "front": {"suspension": {"wheel_center_m": [0, 1, 0]}},
               "rear": {"suspension": {"wheel_center_m": [-3, 1, 0]}}}
    result = curves(rows, vehicle)["curves"]
    assert result["roll_jacking_n"] == pytest.approx([0] * 11)
    assert result["roll_rc_height_mm"] == pytest.approx([-100] * 11)
    assert result["roll_anti_roll_pct"] == pytest.approx([-20] * 11)
    assert result["roll_force_rc_height_mm"] == [None] * 11  # Missing native reaction.


def test_roll_axis_reaction_sign_baseline_and_missing_excitation():
    from app.native_knc import roll_axis_reaction

    signal = "chassisActuator.rollDOF.tau"
    assert roll_axis_reaction({signal: 75}, {signal: 100}, 500) == (-75, -100, 25, .05)
    assert roll_axis_reaction({signal: 125}, {signal: 100}, -500) == (-125, -100, -25, .05)
    assert roll_axis_reaction({signal: 100}, {signal: 100}, 0) == (-100, -100, 0, None)
    assert roll_axis_reaction({}, {}, 1000) == (None, None, None, None)


@pytest.mark.parametrize("load", [1000, 500, -1000])
@pytest.mark.parametrize("ground", [0, -.3, .25])
def test_force_rc_height_reference_shift_and_separate_steering_support(load, ground):
    from app.native_knc import force_rc_height
    # A resultant at 80 mm above the plane, with a separate steering support.
    tail = {"knc.fy": 0, "knc.leftFz": 2000, "knc.rightFz": 2000,
            "chassisActuator.rollDOF.tau": 70, "steerPosition.flange.tau": 12,
            "axle.leftCP.r_0[3]": ground, "axle.rightCP.r_0[3]": ground}
    pulse = dict(tail)
    pulse.update({"knc.fy": load, "chassisActuator.rollDOF.tau": 70 + (ground + .08) * load + .02 * load,
                  "steerPosition.flange.tau": 12 + .02 * load})
    assert force_rc_height(pulse, tail, "front") == pytest.approx(80)
    assert force_rc_height(tail, tail, "front") is None
    del pulse["steerPosition.flange.tau"]
    assert force_rc_height(pulse, tail, "front") is None
    pulse["chassisActuator.rollDOF.tau"] = 70 + (ground + .08) * load
    assert force_rc_height(pulse, tail, "rear") == pytest.approx(80)
    pulse["knc.leftFz"] = 0
    assert force_rc_height(pulse, tail, "rear") is None


def test_sprung_cg_height_follows_heave_roll_mass_weighting_and_contact_datum():
    from app.native_knc import sprung_cg_height
    vehicle = {"sprung_mass": {"mass_kg": 200, "cg_m": [0, .1, .4]},
               "driver_mass": {"mass_kg": 100, "cg_m": [0, -.2, .7]}}
    row = {"knc.heave": .1, "knc.roll": 0,
           "axle.leftCP.r_0[3]": .03, "axle.rightCP.r_0[3]": .01}
    assert sprung_cg_height(row, vehicle) == pytest.approx(.58)
    row["knc.roll"] = math.pi / 3
    assert sprung_cg_height(row, vehicle) == pytest.approx(.28)
    row["knc.roll"] = 0
    row["knc.heave"] = -.1
    assert sprung_cg_height(row, vehicle) == pytest.approx(.38)
    # Translating the coordinate datum must not alter the physical height.
    for body in vehicle.values():
        body["cg_m"][2] += .25
    for wheel in ("left", "right"):
        row[f"axle.{wheel}CP.r_0[3]"] += .25
    assert sprung_cg_height(row, vehicle) == pytest.approx(.38)
    assert sprung_cg_height({}, vehicle) is None
    row["knc.heave"] = -2
    assert sprung_cg_height(row, vehicle) is None


def test_rear_traction_wrapper_uses_shaft_housing_path_independent_of_brakes():
    selected = native.architecture({"architecture": {"front": "direct", "rear": "bellcrank_stabar"}})
    for placement in ("Outboard", "Inboard", "DifferentialInput"):
        selected["rear_brakes"] = placement
        _, source = native.wrapper(selected, "knc-rear-traction")
        assert "final brakePlacement=BobLib.Brakes.Types.Placement.DifferentialInput" in source
        assert "final useRearAxle=true" in source
        assert "KnCLocked" in source


def test_missing_traction_binary_does_not_relabel_braking_as_anti_squat(monkeypatch):
    from app import native_runs
    def run(_vehicle, kind, _settings):
        if kind.endswith("-traction"):
            raise ValueError("Build Rear traction in Architecture first")
        return {"curves": {"curves": {}, "x_axes": {}}}
    monkeypatch.setattr(native_runs, "run", run)
    payload = native_runs.kinematic_curves_payload({})
    assert payload["available"]
    assert "bump_anti_squat_pct" not in payload["axles"]["rear"]["curves"]
    assert "bump_jacking_ratio" not in payload["axles"]["rear"]["curves"]
    assert "Rear anti-squat unavailable" in payload["warnings"][0]
