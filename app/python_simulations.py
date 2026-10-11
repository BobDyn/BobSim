"""Run the app's configurable DynPy response and lap workflows."""

from __future__ import annotations

import argparse
import json
import time
from typing import cast

import pandas as pd

from common import config_io
from common.vehicle_io import load_yaml, repo_root
from engines.dynpy import DOFModel
from engines.kinpy import KinematicsMode
from simulations.lap.lap_time_eval_sim import run_lap_time_evaluation
from simulations.response.reduced.reduced_order_eval_sim import run_step_steer


def run(workflow_id: str) -> None:
    """## Run Python Simulation

    Run the selected workflow using the app's active configuration.

    Parameters
    ----------
    workflow_id : str
        Reduced step steer, QSS lap, or transient lap workflow ID.
    """
    root = repo_root()
    if workflow_id in {"lap-qss", "lap-transient"}:
        config = config_io.resolve("simulations/lap/lap_time_eval_config.yml", root=root)
        summary = run_lap_time_evaluation(
            config, scenario="qss" if workflow_id == "lap-qss" else "transient"
        )
        print(json.dumps(summary, indent=2))
        if not summary["qss_converged"]:
            raise RuntimeError("QSS lap did not converge. Inspect the summary.")
        if workflow_id == "lap-transient" and not (
            summary["transient_success"] and summary["transient_completed_lap"]
        ):
            raise RuntimeError("Transient lap did not complete. Inspect the summary.")
        return
    if workflow_id != "reduced-step-steer":
        raise ValueError(f"Unknown Python simulation: {workflow_id}")
    config = config_io.resolve("simulations/response/reduced/reduced_order_eval_config.yml", root=root)
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
    result = run_step_steer(
        dof=cast(DOFModel, dof),
        vehicle_path=root / "vehicle.yml",
        speed_mps=float(data["speed_mps"]),
        roadwheel_step_deg=float(data["roadwheel_step_deg"]),
        step_time_s=float(data["step_time_s"]),
        rise_time_s=float(data["rise_time_s"]),
        stop_time_s=duration,
        sample_period_s=sample_period,
        kinematics_mode=cast(KinematicsMode, data["kinematics_mode"]),
    )
    output = root / "app/user_data/results/reduced-step-steer"
    output.mkdir(parents=True, exist_ok=True)
    pd.DataFrame({"time": result.time_s, **result.signals}).to_csv(output / "signals.csv", index=False)
    summary = {
        "engine": "DynPy", "model_dof": dof, "method": "Transient", "runtime": "Python",
        "success": bool(result.success), "samples": len(result.time_s),
        "wall_time_s": time.perf_counter() - started,
    }
    (output / "summary.json").write_text(json.dumps(summary, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(summary, indent=2))
    if not result.success:
        raise RuntimeError("Step-steer integration failed. Inspect the job log.")


def main() -> None:
    """## Simulation Entrypoint

    Dispatch the workflow selected by the app's action registry.
    """
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("workflow", choices=("reduced-step-steer", "lap-qss", "lap-transient"))
    run(parser.parse_args().workflow)


if __name__ == "__main__":
    main()
