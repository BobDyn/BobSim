"""Run the app's configurable steering response and DynPy lap workflows."""

from __future__ import annotations

import argparse
import json
import os
import time
from typing import Any, cast

os.environ.setdefault("MPLBACKEND", "Agg")

import pandas as pd

from common import config_io
from common.reporting.dynpy_report import build_dynpy_report
from common.vehicle_io import load_yaml, repo_root
from engines.dynpy import DOFModel
from engines.kinpy import KinematicsMode
from simulations.lap.lap_time_eval_sim import run_lap_time_evaluation
from simulations.response.reduced.reduced_order_eval_sim import run_ramp_steer, run_step_steer


def run(workflow_id: str) -> None:
    """## Run Python Simulation

    Run the selected workflow using the app's active configuration.

    Parameters
    ----------
    workflow_id : str
        Ramp steer, step steer, QSS lap or transient lap workflow ID.
    """
    root = repo_root()
    if workflow_id == "mbd-step-steer":
        from simulations.response.mbd.transient.transient_eval_sim import main as run_mbd_transient

        config = config_io.resolve("simulations/response/mbd/transient/step_steer_config.yml", root=root)
        run_mbd_transient(config)
        return
    if workflow_id in {"lap-qss", "lap-transient"}:
        config = config_io.resolve("simulations/lap/lap_time_eval_config.yml", root=root)
        summary = run_lap_time_evaluation(
            config, scenario="qss" if workflow_id == "lap-qss" else "transient"
        )
        data = load_yaml(config)
        output = root / str(data["output"]["directory"]).format(model_dof=summary["model_dof"])
        vehicle = load_yaml(root / data.get("vehicle", "vehicle.yml"))
        build_dynpy_report(
            workflow_id, output, data, summary, vehicle_name=vehicle.get("vehicle", {}).get("name", "Vehicle")
        )
        print(json.dumps(summary, indent=2))
        if not summary["qss_converged"]:
            raise RuntimeError("QSS lap did not converge. Inspect the summary.")
        if workflow_id == "lap-transient" and not (
            summary["transient_success"] and summary["transient_completed_lap"]
        ):
            raise RuntimeError("Transient lap did not complete. Inspect the summary.")
        return
    if workflow_id not in {"reduced-step-steer", "reduced-ramp-steer"}:
        raise ValueError(f"Unknown Python simulation: {workflow_id}")
    ramp = workflow_id == "reduced-ramp-steer"
    filename = "ramp_steer_config.yml" if ramp else "reduced_order_eval_config.yml"
    config = config_io.resolve(f"simulations/response/reduced/{filename}", root=root)
    data = load_yaml(config)
    dof = int(data["model_dof"])
    if dof not in {3, 6, 10, 14}:
        raise ValueError("Model DOF must be 3, 6, 10, or 14.")
    duration = float(data["stop_time_s"])
    sample_period = float(data["sample_period_s"])
    if not 0 < sample_period <= duration:
        raise ValueError("Sample period must be positive and no longer than the duration.")
    print(f"DynPy | {dof} DOF | Transient | Python", flush=True)
    started = time.perf_counter()
    inputs: dict[str, Any] = (
        {"roadwheel_rate_deg_s": float(data["roadwheel_rate_deg_s"]),
         "start_time_s": float(data["start_time_s"])} if ramp else
        {"roadwheel_step_deg": float(data["roadwheel_step_deg"]),
         "step_time_s": float(data["step_time_s"]), "rise_time_s": float(data["rise_time_s"])}
    )
    simulate = run_ramp_steer if ramp else run_step_steer
    result = simulate(
        dof=cast(DOFModel, dof), vehicle_path=root / "vehicle.yml",
        speed_mps=float(data["speed_mps"]), stop_time_s=duration, sample_period_s=sample_period,
        kinematics_mode=cast(KinematicsMode, data["kinematics_mode"]), **inputs,
    )
    output = root / "app/user_data/results" / workflow_id
    output.mkdir(parents=True, exist_ok=True)
    pd.DataFrame({"time": result.time_s, **result.signals}).to_csv(output / "signals.csv", index=False)
    summary = {
        "engine": "DynPy", "model_dof": dof, "method": "Transient", "runtime": "Python",
        "success": bool(result.success), "samples": len(result.time_s),
        "wall_time_s": time.perf_counter() - started,
    }
    (output / "summary.json").write_text(json.dumps(summary, indent=2) + "\n", encoding="utf-8")
    vehicle = load_yaml(root / "vehicle.yml")
    build_dynpy_report(
        workflow_id, output, data, summary, vehicle_name=vehicle.get("vehicle", {}).get("name", "Vehicle")
    )
    print(json.dumps(summary, indent=2))
    if not result.success:
        raise RuntimeError("Steering integration failed. Inspect the job log.")


def main() -> None:
    """## Simulation Entrypoint

    Dispatch the workflow selected by the app's action registry.
    """
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "workflow", choices=("reduced-step-steer", "reduced-ramp-steer", "mbd-step-steer", "lap-qss", "lap-transient")
    )
    run(parser.parse_args().workflow)


if __name__ == "__main__":
    main()
