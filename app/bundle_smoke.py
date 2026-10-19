"""Exercise edited runtime inputs and archived results inside the built app."""

from __future__ import annotations

import json
import os
import subprocess
import sys

import numpy as np
import pandas as pd
import yaml

from app import app, runtime
from app.visual import reduced_scene_payload
from common.physics_provenance import ggv_physics_sha256
from engines.dynpy.parameters import G, load_reduced_vehicle_parameters


def main() -> None:
    """## Bundled Simulation Check

    Run a short edited-vehicle simulation in the release check's temporary home.
    """
    if not getattr(sys, "frozen", False) or os.environ.get("BOBSIM_BUNDLE_SMOKE") != "1":
        raise RuntimeError("This check requires a bundled app and an isolated smoke-test home.")
    root = app.ROOT
    assert root != runtime.PACKAGE_ROOT
    assert len(ggv_physics_sha256(runtime.PACKAGE_ROOT)) == 64
    vehicle = yaml.safe_load((root / "vehicle.yml").read_text())
    vehicle["vehicle"]["name"] = "Bundle smoke vehicle"
    vehicle["sprung_mass"]["mass_kg"] += 20
    for key, table in vehicle["aero"].items():
        if "_table_" in key:
            vehicle["aero"][key] = np.zeros_like(table).tolist()
    app.save_raw_config("vehicle", yaml.safe_dump(vehicle))
    workflow = "reduced-step-steer"
    config = dict(model_dof=3, speed_mps=8, roadwheel_step_deg=0.5,
                  step_time_s=0.05, rise_time_s=0.02, stop_time_s=0.2,
                  sample_period_s=0.01, kinematics_mode="lookup")
    app.save_raw_config(workflow, yaml.safe_dump(config))
    inputs = app.capture_workflow_inputs(workflow)
    subprocess.run([sys.executable, "--run-module", "app.python_simulations", workflow],
                   cwd=root, check=True, timeout=180)
    saved = app.save_active_results(workflow, input_snapshot=inputs)["saved"]
    files = {item["label"]: root / item["path"] for item in saved["files"]}
    summary = json.loads(files["Summary"].read_text())
    assert summary["success"] and summary["model_dof"] == 3
    assert files["Report"].read_bytes().startswith(b"%PDF")
    frame = pd.read_csv(files["Signals"])
    assert len(frame) == 21 and np.isclose(frame["time"].iloc[-1], 0.2)
    assert np.isclose(frame["velX"].iloc[0], 8)
    params = load_reduced_vehicle_parameters(root / "vehicle.yml")
    loads = frame[[f"tireFz{corner}" for corner in ("FL", "FR", "RL", "RR")]]
    assert np.allclose(loads.sum(axis=1), params.mass_kg * G, atol=0.01)
    archived_vehicle = root / saved["vehicle_snapshot"]
    assert yaml.safe_load(archived_vehicle.read_text()) == vehicle
    plot = app.result_series_payload(files["Signals"].relative_to(root).as_posix(),
                                               x_axis="time", signals=["accY"])
    assert len(plot["x"]) == 21
    scene = reduced_scene_payload(archived_vehicle, files["Signals"], 3)
    assert scene.buffer and scene.header["grip"]
    assert "unavailable" not in scene.header["representation"].lower()
    (root / "bundle-smoke-passed.json").write_text(json.dumps(summary), encoding="utf-8")
    print("Bundled simulation, report, signals, and replay checks passed.", flush=True)


if __name__ == "__main__":
    main()
