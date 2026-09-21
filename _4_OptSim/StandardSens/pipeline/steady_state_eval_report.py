"""steady_state_eval_report.py — SteadyStateEval's own options on the standards runner.

`standards.run_standard` runs any VehicleSim standard for a variant. This adds the
two things only SteadyStateEval callers ask for: Modelica parameter overrides
applied to every case, and a single isoline in place of the standard's four.
"""

from __future__ import annotations

from pathlib import Path
from typing import Any, NamedTuple

from StandardSens.pipeline.standards import VEHICLE_SIM_MODEL, get_standard, run_standard


class Isoline(NamedTuple):
    """One constant-speed line of target lateral accelerations."""

    velocity_mps: float
    target_ays: tuple[float, ...]


def run_report(
    *,
    variant_dir: Path,
    build_dir: Path,
    exec_name: str = VEHICLE_SIM_MODEL,
    timeout: int | None = None,
    init_parameters: dict[str, float] | None = None,
    isoline: Isoline | None = None,
    max_workers: int | None = None,
    render_report: bool = True,
) -> Path:
    """Run SteadyStateEval for one variant and return its metrics CSV.

    `init_parameters` lets one compiled executable stand in for a vehicle it was
    not compiled as. `isoline` swaps the standard's four-isoline matrix for one,
    without touching the shared standard's own config or regression baselines.
    """

    def edit(config: dict[str, Any]) -> None:
        if init_parameters:
            simulation = config["simulation"]
            merged = dict(simulation.get("init_parameters") or {})
            merged.update({name: float(value) for name, value in init_parameters.items()})
            simulation["init_parameters"] = merged
        if isoline is not None:
            # These move together: the cap and the exported-metric velocity must
            # name the one isoline being run, or the report selects nothing.
            sweep = config.setdefault("sweep", {})
            sweep["testVels"] = [isoline.velocity_mps]
            sweep["targetAys"] = list(isoline.target_ays)
            sweep["maxAyByVelocity"] = {isoline.velocity_mps: max(isoline.target_ays)}
            config["report"]["metric_target_velocity_mps"] = isoline.velocity_mps

    return run_standard(
        get_standard("SteadyStateEval"),
        variant_dir=variant_dir,
        build_dir=build_dir,
        exec_name=exec_name,
        timeout=timeout,
        render_report=render_report,
        max_workers=max_workers,
        edit=edit,
    )
