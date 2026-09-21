"""standards.py — Run any VehicleSim standard against a compiled variant.

SteadyStateEval, RampSteerEval and TransientEval are three questions asked of the
same compiled model, `BobLib.Experiments.Standards.VehicleSim`. `_3_StandardSim`
already builds that model once and points all three configs at it. They also
share one interface: `python -m <module> <config.yml>`, a `simulation` block
naming the executable, and a `report` block whose `output_path` decides where the
PDF and its `<stem>_metrics.csv` land. So one compile per vehicle serves every
standard here, and adding a standard is one entry in `STANDARDS`.

FourPostEval is not listed: it runs a different model (`FourPostSim`), which
means a second compile per vehicle and its own config conventions.
"""

from __future__ import annotations

from collections.abc import Callable
import csv
from dataclasses import dataclass
import hashlib
from pathlib import Path
import shutil
import subprocess
import sys
from typing import Any

import yaml

REPO_ROOT = Path(__file__).resolve().parents[3]
VEHICLE_SIM_MODEL = "BobLib.Experiments.Standards.VehicleSim"

ConfigEdit = Callable[[dict[str, Any]], None]


@dataclass(frozen=True)
class Standard:
    name: str
    package: str  # directory under _3_StandardSim, also the python package
    stem: str  # "<stem>_sim.py", "<stem>_config.yml", "<stem>_report.pdf"

    @property
    def module(self) -> str:
        return f"_3_StandardSim.{self.package}.{self.stem}_sim"

    @property
    def sim_path(self) -> Path:
        return REPO_ROOT / "_3_StandardSim" / self.package / f"{self.stem}_sim.py"

    @property
    def config_path(self) -> Path:
        return REPO_ROOT / "_3_StandardSim" / self.package / f"{self.stem}_config.yml"


STANDARDS: dict[str, Standard] = {
    s.name: s
    for s in (
        Standard("SteadyStateEval", "SteadyStateEval", "steady_state_eval"),
        Standard("RampSteerEval", "RampSteerEval", "ramp_steer_eval"),
        Standard("TransientEval", "TransientEval", "transient_eval"),
    )
}


def input_digest(standard: Standard) -> str:
    """Fingerprint of what decides a standard's numbers besides the vehicle.

    The pipeline hash covers SteadyStateEval's tooling only, so results cached
    for another standard are stamped with this and rerun when it changes.
    """
    digest = hashlib.sha256()
    for path in (standard.sim_path, standard.config_path):
        digest.update(path.read_bytes())
    return digest.hexdigest()


def get_standard(name: str) -> Standard:
    try:
        return STANDARDS[name]
    except KeyError:
        raise KeyError(
            f"{name!r} is not a VehicleSim standard OptSim can run. Known: {sorted(STANDARDS)}. "
            "A standard on a different model (FourPostEval runs FourPostSim) needs its own "
            "compile and is not wired in."
        ) from None


def write_config(
    standard: Standard,
    *,
    variant_dir: Path,
    build_dir: Path,
    exec_name: str = VEHICLE_SIM_MODEL,
    render_report: bool = True,
    max_workers: int | None = None,
    edit: ConfigEdit | None = None,
) -> tuple[Path, Path]:
    """Write the standard's config for one variant; return (config, metrics CSV).

    The shared standard's own config file is read, never written. `edit` is the
    hook for the few callers that need more than the executable swapped.
    """
    with standard.config_path.open(encoding="utf-8") as handle:
        config = yaml.safe_load(handle)
    if not isinstance(config, dict):
        raise TypeError(f"Expected a mapping at top level: {standard.config_path}")

    simulation = config.setdefault("simulation", {})
    simulation["build_dir"] = str(build_dir)
    simulation["exec_name"] = exec_name

    # Otherwise execution settings stay exactly as the standard's config has them.
    if max_workers is not None:
        execution = config.setdefault("execution", {})
        execution["parallel"] = True
        execution["max_workers"] = int(max_workers)

    # The metrics CSV path is derived from output_path whether or not the PDF is
    # rendered, so anchoring it to the variant keeps both beside its results.
    results_dir = variant_dir / "results" / standard.name
    report = config.setdefault("report", {})
    report["enabled"] = render_report
    report["output_path"] = str(results_dir / f"{standard.stem}_report.pdf")

    if edit is not None:
        edit(config)

    config_path = results_dir / f"{standard.stem}_config.generated.yml"
    config_path.parent.mkdir(parents=True, exist_ok=True)
    with config_path.open("w", encoding="utf-8") as handle:
        yaml.safe_dump(config, handle, sort_keys=False)
    return config_path, results_dir / f"{standard.stem}_report_metrics.csv"


def run_standard(
    standard: Standard,
    *,
    variant_dir: Path,
    build_dir: Path,
    exec_name: str = VEHICLE_SIM_MODEL,
    timeout: int | None = None,
    render_report: bool = True,
    max_workers: int | None = None,
    edit: ConfigEdit | None = None,
) -> Path:
    """Run one standard for one variant and return its metrics CSV."""
    config_path, metrics_csv = write_config(
        standard,
        variant_dir=variant_dir,
        build_dir=build_dir,
        exec_name=exec_name,
        render_report=render_report,
        max_workers=max_workers,
        edit=edit,
    )
    completed = subprocess.run(
        [sys.executable, "-m", standard.module, str(config_path)],
        cwd=str(REPO_ROOT),
        capture_output=True,
        text=True,
        timeout=timeout,
    )
    if completed.returncode != 0:
        raise RuntimeError(
            f"{standard.name} failed.\nConfig: {config_path}\n"
            f"Stdout:\n{completed.stdout}\nStderr:\n{completed.stderr}"
        )
    if not metrics_csv.exists():
        raise FileNotFoundError(f"{standard.name} produced no metrics CSV: {metrics_csv}")

    # A stable name beside the report-style one, which is what the sweep's
    # batch runner and aggregator look for.
    canonical = metrics_csv.with_name("metrics.csv")
    shutil.copyfile(metrics_csv, canonical)
    return canonical


def read_metrics(path: Path) -> dict[str, tuple[float, str]]:
    """Read a standard's metrics CSV as {name: (value, units)}.

    TransientEval reports some metrics once per group under the same name
    (`ay_gain_dc` for the step and again for the frequency sweep). Keyed by bare
    name the later row would silently replace the earlier, so a name that spans
    groups is exposed only in its qualified form, `group.metric`. A row repeated
    with the same value is one metric; repeated with a different value it is an
    ambiguity nothing here can resolve, and an error.
    """
    with path.open(newline="", encoding="utf-8") as handle:
        rows = [row for row in csv.DictReader(handle) if row.get("metric")]
    groups: dict[str, set[str]] = {}
    for row in rows:
        groups.setdefault(row["metric"], set()).add(row.get("group") or "")

    metrics: dict[str, tuple[float, str]] = {}
    for row in rows:
        name = row["metric"]
        if len(groups[name]) > 1:
            name = f"{row.get('group') or '?'}.{name}"
        try:
            value = float(row.get("value") or "nan")
        except ValueError:
            value = float("nan")
        if name in metrics and not _same(metrics[name][0], value):
            raise ValueError(f"{path} reports {name!r} twice with different values")
        metrics[name] = (value, row.get("units") or "")
    return metrics


def _same(a: float, b: float) -> bool:
    return a == b or (a != a and b != b)  # NaN equals NaN here
