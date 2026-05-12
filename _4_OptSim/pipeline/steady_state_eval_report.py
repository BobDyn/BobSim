"""steady_state_eval_report.py — Run the SteadyStateEval postprocessor for one DOE variant.

This reuses the existing SteadyStateEval Python wrapper to generate the report-style
metrics CSV from the variant-specific compiled executable.
"""

from __future__ import annotations

import shutil
import subprocess
import sys
from pathlib import Path
from typing import Any

import yaml

ROOT = Path(__file__).resolve().parent.parent
BASE_CONFIG = ROOT.parent / "_3_StandardSim/SteadyStateEval/steady_state_eval_config.yml"


def _load_yaml(path: Path) -> dict[str, Any]:
    with path.open("r", encoding="utf-8") as f:
        data = yaml.safe_load(f)
    if not isinstance(data, dict):
        raise TypeError(f"Expected mapping at top level: {path}")
    return data


def _dump_yaml(path: Path, data: dict[str, Any]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8") as f:
        yaml.safe_dump(data, f, sort_keys=False)


def build_report_config(
    *,
    variant_dir: Path,
    build_dir: Path,
    exec_name: str,
    base_config_path: Path = BASE_CONFIG,
) -> tuple[Path, Path]:
    """Write a temporary SteadyStateEval config for one DOE variant.

    Returns:
        (config_path, canonical_metrics_csv_path)
    """
    config = _load_yaml(base_config_path)

    simulation = config.setdefault("simulation", {})
    if not isinstance(simulation, dict):
        raise TypeError("SteadyStateEval config simulation block must be a mapping")

    report = config.setdefault("report", {})
    if not isinstance(report, dict):
        raise TypeError("SteadyStateEval config report block must be a mapping")

    execution = config.setdefault("execution", {})
    if not isinstance(execution, dict):
        raise TypeError("SteadyStateEval config execution block must be a mapping")

    simulation["build_dir"] = str(build_dir)
    simulation["exec_name"] = exec_name

    # Leave execution settings exactly as defined in the standard-sim config.
    # The OptSim layer will handle serial variant execution instead.

    # Keep the report output location anchored to the variant so the generated
    # PDF and metrics CSV live beside the DOE result artifacts.
    report["enabled"] = True
    report["output_path"] = str(
        variant_dir / "results" / "SteadyStateEval" / "steady_state_eval_report.pdf"
    )

    results_dir = variant_dir / "results" / "SteadyStateEval"
    config_path = results_dir / "steady_state_eval_config.generated.yml"
    metrics_csv = results_dir / "steady_state_eval_report_metrics.csv"

    _dump_yaml(config_path, config)
    return config_path, metrics_csv


def run_report(
    *,
    variant_dir: Path,
    build_dir: Path,
    exec_name: str,
    timeout: int | None = None,
    base_config_path: Path = BASE_CONFIG,
) -> Path:
    """Run the SteadyStateEval report wrapper and return the metrics CSV path."""
    config_path, metrics_csv = build_report_config(
        variant_dir=variant_dir,
        build_dir=build_dir,
        exec_name=exec_name,
        base_config_path=base_config_path,
    )

    cmd = [
        sys.executable,
        "-m",
        "_3_StandardSim.SteadyStateEval.steady_state_eval_sim",
        str(config_path),
    ]

    completed = subprocess.run(
        cmd,
        cwd=str(ROOT.parent),
        capture_output=True,
        text=True,
        timeout=timeout,
    )

    if completed.returncode != 0:
        raise RuntimeError(
            "SteadyStateEval report generation failed.\n"
            f"Config: {config_path}\n"
            f"Stdout:\n{completed.stdout}\n"
            f"Stderr:\n{completed.stderr}"
        )

    if not metrics_csv.exists():
        raise FileNotFoundError(
            f"Metrics CSV not produced by SteadyStateEval report: {metrics_csv}"
        )

    # Keep a stable, pipeline-friendly name alongside the report-style CSV.
    canonical_metrics_csv = metrics_csv.with_name("metrics.csv")
    shutil.copyfile(metrics_csv, canonical_metrics_csv)

    return canonical_metrics_csv
