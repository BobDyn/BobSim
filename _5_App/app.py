from __future__ import annotations

from dataclasses import dataclass, field as dataclass_field
from http import HTTPStatus
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
import argparse
import csv
import json
import math
import mimetypes
import os
from pathlib import Path
import subprocess
import sys
import threading
import time
from typing import Any
from urllib.parse import parse_qs, unquote, urlparse
import uuid
import re

import yaml

from _0_Utils.vehicle_io import parse_tir


ROOT = Path(__file__).resolve().parents[1]
STATIC_ROOT = Path(__file__).resolve().parent / "static"
SAVED_VEHICLE_ROOT = Path("_5_App/vehicle_configs")
MAX_LOG_CHARS = 120_000


@dataclass(frozen=True)
class OutputSpec:
    label: str
    path: str
    kind: str


@dataclass(frozen=True)
class ActionSpec:
    id: str
    label: str
    argv: tuple[str, ...]
    env: dict[str, str] = dataclass_field(default_factory=dict)


@dataclass(frozen=True)
class WorkflowSpec:
    id: str
    group: str
    label: str
    config: str | None
    actions: tuple[str, ...]
    outputs: tuple[OutputSpec, ...] = ()


PathPart = str | int


@dataclass(frozen=True)
class FieldSpec:
    path: tuple[PathPart, ...]
    label: str
    kind: str = "auto"
    group: str | None = None
    unit: str | None = None
    choices: tuple[str, ...] = ()


@dataclass(frozen=True)
class ConfigSpec:
    id: str
    group: str
    label: str
    path: str
    workflow_id: str | None = None
    fields: tuple[FieldSpec, ...] = ()


PYTHON = sys.executable

ACTION_SPECS: dict[str, ActionSpec] = {
    "build-vehicle": ActionSpec(
        id="build-vehicle",
        label="Build VehicleSim",
        argv=("omc", "_3_StandardSim/build_vehicle_sim.mos"),
    ),
    "build-four-post": ActionSpec(
        id="build-four-post",
        label="Build FourPostSim",
        argv=("omc", "_3_StandardSim/build_four_post_sim.mos"),
    ),
    "run-ramp-steer": ActionSpec(
        id="run-ramp-steer",
        label="Run RampSteerEval",
        argv=(PYTHON, "-m", "_3_StandardSim.RampSteerEval.ramp_steer_eval_sim"),
    ),
    "run-steady-state": ActionSpec(
        id="run-steady-state",
        label="Run SteadyStateEval",
        argv=(PYTHON, "-m", "_3_StandardSim.SteadyStateEval.steady_state_eval_sim"),
    ),
    "run-transient": ActionSpec(
        id="run-transient",
        label="Run TransientEval",
        argv=(PYTHON, "-m", "_3_StandardSim.TransientEval.transient_eval_sim"),
    ),
    "run-four-post": ActionSpec(
        id="run-four-post",
        label="Run FourPostEval",
        argv=(PYTHON, "-m", "_3_StandardSim.FourPostEval.four_post_eval_sim"),
    ),
    "run-ggv": ActionSpec(
        id="run-ggv",
        label="Run GGV",
        argv=(PYTHON, "-m", "_2_EnvelopeSim.GGV.ggv_generation"),
    ),
    "run-ymd": ActionSpec(
        id="run-ymd",
        label="Run YMD",
        argv=(PYTHON, "-m", "_2_EnvelopeSim.YMD.ymd_generation"),
    ),
    "run-review": ActionSpec(
        id="run-review",
        label="Run VehicleReview",
        argv=(PYTHON, "-m", "_2_EnvelopeSim.VehicleReview.vehicle_review_sim"),
    ),
    "run-opt-standard": ActionSpec(
        id="run-opt-standard",
        label="Run StandardSens",
        argv=(PYTHON, "-m", "StandardSens.pre_screen_sensitivities"),
        env={"PYTHONPATH": f"{ROOT / '_4_OptSim'}:{ROOT}"},
    ),
    "run-opt-envelope": ActionSpec(
        id="run-opt-envelope",
        label="Run EnvelopeSens",
        argv=(PYTHON, "-m", "EnvelopeSens.sensitivities"),
        env={"PYTHONPATH": f"{ROOT / '_4_OptSim'}:{ROOT}"},
    ),
}


WORKFLOWS: tuple[WorkflowSpec, ...] = (
    WorkflowSpec(
        id="ramp-steer",
        group="standard",
        label="RampSteerEval",
        config="_3_StandardSim/RampSteerEval/ramp_steer_eval_config.yml",
        actions=("build-vehicle", "run-ramp-steer"),
        outputs=(
            OutputSpec("Report", "_3_StandardSim/results/ramp_steer_eval_report.pdf", "pdf"),
            OutputSpec("Metrics", "_3_StandardSim/results/ramp_steer_eval_report_metrics.csv", "csv"),
        ),
    ),
    WorkflowSpec(
        id="steady-state",
        group="standard",
        label="SteadyStateEval",
        config="_3_StandardSim/SteadyStateEval/steady_state_eval_config.yml",
        actions=("build-vehicle", "run-steady-state"),
        outputs=(
            OutputSpec("Report", "_3_StandardSim/results/steady_state_eval_report.pdf", "pdf"),
            OutputSpec("Metrics", "_3_StandardSim/results/steady_state_eval_report_metrics.csv", "csv"),
        ),
    ),
    WorkflowSpec(
        id="transient",
        group="standard",
        label="TransientEval",
        config="_3_StandardSim/TransientEval/transient_eval_config.yml",
        actions=("build-vehicle", "run-transient"),
        outputs=(
            OutputSpec("Report", "_3_StandardSim/results/transient_eval_report.pdf", "pdf"),
            OutputSpec("Metrics", "_3_StandardSim/results/transient_eval_report_metrics.csv", "csv"),
        ),
    ),
    WorkflowSpec(
        id="four-post",
        group="standard",
        label="FourPostEval",
        config="_3_StandardSim/FourPostEval/four_post_eval_config.yml",
        actions=("build-four-post", "run-four-post"),
        outputs=(
            OutputSpec("Report", "_3_StandardSim/results/four_post_eval_report.pdf", "pdf"),
            OutputSpec("Metrics", "_3_StandardSim/results/four_post_eval_report_metrics.csv", "csv"),
        ),
    ),
    WorkflowSpec(
        id="ggv",
        group="envelope",
        label="GGV",
        config="_2_EnvelopeSim/GGV/ggv_config.yml",
        actions=("run-ggv",),
        outputs=(
            OutputSpec("Report", "_2_EnvelopeSim/results/ggv_report.pdf", "pdf"),
            OutputSpec("Metrics", "_2_EnvelopeSim/results/ggv_report_metrics.csv", "csv"),
            OutputSpec("Raw CSV", "_2_EnvelopeSim/Build/GGV/ggv_first_principles.csv", "csv"),
        ),
    ),
    WorkflowSpec(
        id="ymd",
        group="envelope",
        label="YMD",
        config="_2_EnvelopeSim/YMD/ymd_config.yml",
        actions=("run-ymd",),
        outputs=(
            OutputSpec("Report", "_2_EnvelopeSim/results/ymd_report.pdf", "pdf"),
            OutputSpec("Metrics", "_2_EnvelopeSim/results/ymd_report_metrics.csv", "csv"),
            OutputSpec("Raw CSV", "_2_EnvelopeSim/Build/YMD/ymd_first_principles.csv", "csv"),
        ),
    ),
    WorkflowSpec(
        id="vehicle-review",
        group="report",
        label="VehicleReview",
        config="_2_EnvelopeSim/VehicleReview/vehicle_review_config.yml",
        actions=("run-review",),
        outputs=(
            OutputSpec("Report", "_2_EnvelopeSim/results/VehicleReview/vehicle_review_report.pdf", "pdf"),
            OutputSpec("Metrics", "_2_EnvelopeSim/results/VehicleReview/vehicle_review_report_metrics.csv", "csv"),
        ),
    ),
    WorkflowSpec(
        id="standard-sens",
        group="opt",
        label="StandardSens",
        config="_4_OptSim/StandardSens/configs/_doe_config.yaml",
        actions=("run-opt-standard",),
        outputs=(),
    ),
    WorkflowSpec(
        id="envelope-sens",
        group="opt",
        label="EnvelopeSens",
        config="_4_OptSim/EnvelopeSens/config.yml",
        actions=("run-opt-envelope",),
        outputs=(),
    ),
)


class JobStore:
    def __init__(self) -> None:
        self._lock = threading.Lock()
        self._jobs: dict[str, dict[str, Any]] = {}

    def create(self, action_id: str, label: str, argv: list[str]) -> dict[str, Any]:
        job_id = uuid.uuid4().hex[:10]
        now = time.time()
        job = {
            "id": job_id,
            "action_id": action_id,
            "label": label,
            "argv": argv,
            "status": "queued",
            "returncode": None,
            "started_at": None,
            "ended_at": None,
            "created_at": now,
            "log": "",
        }
        with self._lock:
            self._jobs[job_id] = job
        return job

    def append_log(self, job_id: str, text: str) -> None:
        if not text:
            return
        with self._lock:
            job = self._jobs[job_id]
            job["log"] = (job["log"] + text)[-MAX_LOG_CHARS:]

    def update(self, job_id: str, **values: Any) -> None:
        with self._lock:
            self._jobs[job_id].update(values)

    def get(self, job_id: str) -> dict[str, Any] | None:
        with self._lock:
            job = self._jobs.get(job_id)
            return dict(job) if job else None

    def list(self) -> list[dict[str, Any]]:
        with self._lock:
            return [
                dict(job)
                for job in sorted(
                    self._jobs.values(),
                    key=lambda item: float(item["created_at"]),
                    reverse=True,
                )
            ]


JOBS = JobStore()


def _safe_repo_path(raw_path: str | Path) -> Path:
    rel = Path(str(raw_path))
    if rel.is_absolute():
        candidate = rel.resolve()
    else:
        candidate = (ROOT / rel).resolve()
    if candidate != ROOT and ROOT not in candidate.parents:
        raise ValueError(f"Path escapes repo: {raw_path}")
    return candidate


def _path_payload(raw_path: str) -> dict[str, Any]:
    path = _safe_repo_path(raw_path)
    exists = path.exists()
    payload: dict[str, Any] = {
        "path": raw_path,
        "exists": exists,
        "url": f"/files/{raw_path}" if exists and path.is_file() else None,
    }
    if exists and path.is_file():
        stat = path.stat()
        payload.update(
            {
                "size": stat.st_size,
                "modified": stat.st_mtime,
                "modified_label": time.strftime(
                    "%Y-%m-%d %H:%M:%S",
                    time.localtime(stat.st_mtime),
                ),
            }
        )
    return payload


def _csv_preview(raw_path: str, limit: int = 8) -> dict[str, Any]:
    path = _safe_repo_path(raw_path)
    if not path.is_file():
        return {"headers": [], "rows": []}
    with path.open("r", encoding="utf-8", newline="", errors="replace") as handle:
        reader = csv.DictReader(handle)
        rows = []
        for idx, row in enumerate(reader):
            if idx >= limit:
                break
            rows.append(dict(row))
    return {"headers": list(reader.fieldnames or []), "rows": rows}


def _field(
    path: str,
    label: str,
    *,
    kind: str = "auto",
    group: str | None = None,
    unit: str | None = None,
    choices: tuple[str, ...] = (),
) -> FieldSpec:
    return FieldSpec(
        path=tuple(path.split(".")),
        label=label,
        kind=kind,
        group=group,
        unit=unit,
        choices=choices,
    )


ARCHITECTURE_CHOICES = ("direct", "bellcrank", "bellcrank_stabar")
SOLVER_CHOICES = ("dassl", "ida", "cvode", "euler")
DIRECTION_CHOICES = ("left", "right")
ROD_TARGET_CHOICES = ("lower", "upper")
BELLCRANK_ORDER_CHOICES = ("rod", "shock")
STABAR_BELLCRANK_ORDER_CHOICES = ("rod", "shock", "stabar")
POWERTRAIN_IMPLEMENTATIONS = (
    {
        "id": "EVBatInvMotDiff",
        "label": "EV battery/inverter/motor/differential",
        "status": "implemented",
        "components": ("Battery", "Inverter", "Motor", "Differential"),
    },
)

COMMON_SIM_FIELDS = (
    _field("simulation.start_time", "Start time", kind="number", group="Simulation", unit="s"),
    _field("simulation.stop_time", "Stop time", kind="number", group="Simulation", unit="s"),
    _field("simulation.stepSize", "Step size", kind="number", group="Simulation", unit="s"),
    _field("simulation.solver", "Solver", kind="select", group="Simulation", choices=SOLVER_CHOICES),
    _field("simulation.tolerance", "Tolerance", kind="number", group="Simulation"),
    _field("simulation.case_timeout_s", "Case timeout", kind="number", group="Simulation", unit="s"),
    _field("simulation.no_grid", "No grid", kind="boolean", group="Simulation"),
    _field("simulation.no_event_emit", "No event emit", kind="boolean", group="Simulation"),
    _field("execution.parallel", "Parallel", kind="boolean", group="Execution"),
    _field("execution.max_workers", "Max workers", kind="integer", group="Execution"),
    _field("execution.cleanup", "Cleanup raw artifacts", kind="boolean", group="Execution"),
    _field("execution.stream_logs", "Stream logs", kind="boolean", group="Execution"),
    _field("execution.fail_fast", "Fail fast", kind="boolean", group="Execution"),
    _field("report.enabled", "Report enabled", kind="boolean", group="Report"),
    _field("report.brand", "Brand", kind="string", group="Report"),
    _field("report.title", "Title", kind="string", group="Report"),
    _field("report.subtitle", "Subtitle", kind="string", group="Report"),
    _field("report.output_path", "Report path", kind="string", group="Report"),
    _field("report.metrics_csv_path", "Metrics CSV path", kind="string", group="Report"),
    _field("report.metric_target_velocity_mps", "Metric target velocity", kind="number", group="Report", unit="m/s"),
)

VEHICLE_FIELDS: tuple[FieldSpec, ...] = (
    _field("vehicle.name", "Vehicle name", kind="string", group="Vehicle"),
    _field("vehicle.version", "Version", kind="string", group="Vehicle"),
    _field(
        "architecture.front", "Front architecture", kind="select", group="Architecture", choices=ARCHITECTURE_CHOICES
    ),
    _field("architecture.rear", "Rear architecture", kind="select", group="Architecture", choices=ARCHITECTURE_CHOICES),
    _field("sprung_mass.mass_kg", "Sprung mass", kind="number", group="Mass", unit="kg"),
    _field("sprung_mass.cg_m", "Sprung CG", kind="list", group="Mass", unit="m"),
    _field("driver_mass.mass_kg", "Driver mass", kind="number", group="Mass", unit="kg"),
    _field("driver_mass.cg_m", "Driver CG", kind="list", group="Mass", unit="m"),
    _field("body.torsional_stiff_n_m_per_rad", "Torsional stiffness", kind="number", group="Body", unit="N m/rad"),
    _field("front.wheel.radius_m", "Front tire radius", kind="number", group="Front wheel", unit="m"),
    _field("front.wheel.toe_deg", "Front toe", kind="number", group="Front wheel", unit="deg"),
    _field("front.wheel.camber_deg", "Front camber", kind="number", group="Front wheel", unit="deg"),
    _field("front.tire.template", "Front tire template", kind="string", group="Front wheel"),
    _field(
        "front.actuation.rod_to", "Front rod target", kind="select", group="Front actuation", choices=ROD_TARGET_CHOICES
    ),
    _field(
        "front.actuation.shock.free_length_m",
        "Front spring free length",
        kind="number",
        group="Front actuation",
        unit="m",
    ),
    _field(
        "front.actuation.stabar.rate_n_m_per_rad",
        "Front stabar rate",
        kind="number",
        group="Front actuation",
        unit="N m/rad",
    ),
    _field("rear.wheel.radius_m", "Rear tire radius", kind="number", group="Rear wheel", unit="m"),
    _field("rear.wheel.toe_deg", "Rear toe", kind="number", group="Rear wheel", unit="deg"),
    _field("rear.wheel.camber_deg", "Rear camber", kind="number", group="Rear wheel", unit="deg"),
    _field("rear.tire.template", "Rear tire template", kind="string", group="Rear wheel"),
    _field(
        "rear.actuation.rod_to", "Rear rod target", kind="select", group="Rear actuation", choices=ROD_TARGET_CHOICES
    ),
    _field(
        "rear.actuation.shock.free_length_m", "Rear spring free length", kind="number", group="Rear actuation", unit="m"
    ),
    _field(
        "rear.actuation.stabar.rate_n_m_per_rad",
        "Rear stabar rate",
        kind="number",
        group="Rear actuation",
        unit="N m/rad",
    ),
)


def _hardpoint_fields(axle: str, label: str) -> tuple[FieldSpec, ...]:
    hardpoint_group = f"{label} hardpoints"
    actuation_group = f"{label} actuation"
    return (
        _field(f"{axle}.suspension.upper_fore_i_m", "Upper fore inner", kind="list", group=hardpoint_group, unit="m"),
        _field(f"{axle}.suspension.upper_aft_i_m", "Upper aft inner", kind="list", group=hardpoint_group, unit="m"),
        _field(f"{axle}.suspension.upper_o_m", "Upper outer", kind="list", group=hardpoint_group, unit="m"),
        _field(f"{axle}.suspension.lower_fore_i_m", "Lower fore inner", kind="list", group=hardpoint_group, unit="m"),
        _field(f"{axle}.suspension.lower_aft_i_m", "Lower aft inner", kind="list", group=hardpoint_group, unit="m"),
        _field(f"{axle}.suspension.lower_o_m", "Lower outer", kind="list", group=hardpoint_group, unit="m"),
        _field(f"{axle}.suspension.tie_o_m", "Tie rod outer", kind="list", group=hardpoint_group, unit="m"),
        _field(f"{axle}.suspension.wheel_center_m", "Wheel center", kind="list", group=hardpoint_group, unit="m"),
        _field(f"{axle}.steering.rack_pickup_m", "Rack pickup", kind="list", group=hardpoint_group, unit="m"),
        _field(f"{axle}.actuation.rod_mount_m", "Rod mount", kind="list", group=actuation_group, unit="m"),
        _field(f"{axle}.actuation.shock.mount_m", "Shock mount", kind="list", group=actuation_group, unit="m"),
        _field(f"{axle}.actuation.bellcrank.pivot_m", "Bellcrank pivot", kind="list", group=actuation_group, unit="m"),
        _field(
            f"{axle}.actuation.bellcrank.pickups_m.rod",
            "Bellcrank rod pickup",
            kind="list",
            group=actuation_group,
            unit="m",
        ),
        _field(
            f"{axle}.actuation.bellcrank.pickups_m.shock",
            "Bellcrank shock pickup",
            kind="list",
            group=actuation_group,
            unit="m",
        ),
        _field(
            f"{axle}.actuation.bellcrank.pickups_m.stabar",
            "Bellcrank stabar pickup",
            kind="list",
            group=actuation_group,
            unit="m",
        ),
        _field(f"{axle}.actuation.bellcrank.order", "Bellcrank order", kind="list", group=actuation_group),
        _field(f"{axle}.actuation.stabar.arm_end_m", "Stabar arm end", kind="list", group=actuation_group, unit="m"),
        _field(f"{axle}.actuation.stabar.bar_end_m", "Stabar bar end", kind="list", group=actuation_group, unit="m"),
    )


VEHICLE_FIELDS = VEHICLE_FIELDS + _hardpoint_fields("front", "Front") + _hardpoint_fields("rear", "Rear")

VISUAL_FIELDS = (
    _field("render.show_signals", "Show signals", kind="boolean", group="Render"),
    _field("render.speed", "Playback speed", kind="number", group="Render"),
    _field("render.input_stride", "Input stride", kind="integer", group="Render"),
    _field("style.joints.radius", "Joint radius", kind="number", group="Style"),
    _field("style.joints.color", "Joint color", kind="string", group="Style"),
    _field("camera.attach_to", "Camera target", kind="string", group="Camera"),
    _field("camera.origin_offset.x", "Camera origin x", kind="number", group="Camera", unit="m"),
    _field("camera.origin_offset.y", "Camera origin y", kind="number", group="Camera", unit="m"),
    _field("camera.origin_offset.z", "Camera origin z", kind="number", group="Camera", unit="m"),
    _field("camera.camera_offsets.back", "Camera back", kind="number", group="Camera", unit="m"),
    _field("camera.camera_offsets.height", "Camera height", kind="number", group="Camera", unit="m"),
    _field("camera.mode", "Camera mode", kind="string", group="Camera"),
)

BASE_CONFIG_SPECS: dict[str, ConfigSpec] = {
    "vehicle": ConfigSpec(
        id="vehicle",
        group="setup",
        label="Active Vehicle",
        path="vehicle.yml",
        fields=VEHICLE_FIELDS,
    ),
    "ramp-steer": ConfigSpec(
        id="ramp-steer",
        group="standard",
        label="RampSteerEval",
        path="_3_StandardSim/RampSteerEval/ramp_steer_eval_config.yml",
        workflow_id="ramp-steer",
        fields=COMMON_SIM_FIELDS
        + (
            _field("sweep.testVels", "Test velocities", kind="list", group="Sweep", unit="m/s"),
            _field("sweep.maxAy", "Max lateral acceleration", kind="number", group="Sweep", unit="m/s^2"),
            _field("fit.ay_linear_max", "Linear fit bound", kind="number", group="Fit", unit="m/s^2"),
        ),
    ),
    "steady-state": ConfigSpec(
        id="steady-state",
        group="standard",
        label="SteadyStateEval",
        path="_3_StandardSim/SteadyStateEval/steady_state_eval_config.yml",
        workflow_id="steady-state",
        fields=COMMON_SIM_FIELDS
        + (
            _field("sweep.testVels", "Test velocities", kind="list", group="Sweep", unit="m/s"),
            _field("sweep.targetAys", "Target lateral accelerations", kind="list", group="Sweep", unit="m/s^2"),
            _field("sweep.includeNegative", "Include negative sweep", kind="boolean", group="Sweep"),
            _field("fit.nonlinearity_fraction", "Nonlinearity fraction", kind="number", group="Fit"),
        ),
    ),
    "transient": ConfigSpec(
        id="transient",
        group="standard",
        label="TransientEval",
        path="_3_StandardSim/TransientEval/transient_eval_config.yml",
        workflow_id="transient",
        fields=COMMON_SIM_FIELDS
        + (
            _field("test.testVel", "Test velocities", kind="list", group="Test", unit="m/s"),
            _field("test.run_step", "Run step steer", kind="boolean", group="Test"),
            _field("test.run_continuous_sine", "Run continuous sine", kind="boolean", group="Test"),
            _field("test.directions", "Directions", kind="list", group="Test", choices=DIRECTION_CHOICES),
            _field("test.steerStep_deg", "Step steer amplitudes", kind="list", group="Test", unit="deg"),
            _field("test.sweep_freq_hz", "Sine frequencies", kind="list", group="Test", unit="Hz"),
            _field("test.sweep_amp_deg", "Sine amplitudes", kind="list", group="Test", unit="deg"),
            _field("test.n_cycles", "Sine cycles", kind="integer", group="Test"),
        ),
    ),
    "four-post": ConfigSpec(
        id="four-post",
        group="standard",
        label="FourPostEval",
        path="_3_StandardSim/FourPostEval/four_post_eval_config.yml",
        workflow_id="four-post",
        fields=COMMON_SIM_FIELDS
        + (
            _field(
                "model_overrides.suspension.front.spring_rate_n_per_m",
                "Front spring rate",
                kind="number",
                group="Suspension",
                unit="N/m",
            ),
            _field(
                "model_overrides.suspension.front.stabar_rate_n_m_per_rad",
                "Front stabar rate",
                kind="number",
                group="Suspension",
                unit="N m/rad",
            ),
            _field(
                "model_overrides.suspension.rear.spring_rate_n_per_m",
                "Rear spring rate",
                kind="number",
                group="Suspension",
                unit="N/m",
            ),
            _field(
                "model_overrides.suspension.rear.stabar_rate_n_m_per_rad",
                "Rear stabar rate",
                kind="number",
                group="Suspension",
                unit="N m/rad",
            ),
            _field("procedure.steerMagnitude", "Steer magnitude", kind="number", group="Procedure", unit="rad"),
            _field("procedure.heaveMagnitude", "Heave magnitude", kind="number", group="Procedure", unit="m"),
            _field("procedure.rollMagnitude", "Roll magnitude", kind="number", group="Procedure", unit="rad"),
            _field("procedure.forceMagnitude", "Force magnitude", kind="number", group="Procedure", unit="N"),
        ),
    ),
    "ggv": ConfigSpec(
        id="ggv",
        group="envelope",
        label="GGV",
        path="_2_EnvelopeSim/GGV/ggv_config.yml",
        workflow_id="ggv",
        fields=(
            _field("generation.speeds_mps", "Speeds", kind="list", group="Generation", unit="m/s"),
            _field("generation.ay_max_g", "Max lateral acceleration", kind="number", group="Generation", unit="g"),
            _field("generation.ay_points", "Lateral points", kind="integer", group="Generation"),
            _field(
                "generation.ax_search_min_g", "Min longitudinal search", kind="number", group="Generation", unit="g"
            ),
            _field(
                "generation.ax_search_max_g", "Max longitudinal search", kind="number", group="Generation", unit="g"
            ),
            _field("generation.ax_search_points", "Longitudinal points", kind="integer", group="Generation"),
            _field("generation.include_left_right", "Include left/right", kind="boolean", group="Generation"),
            _field("report.enabled", "Report enabled", kind="boolean", group="Report"),
            _field("report.title", "Title", kind="string", group="Report"),
            _field("report.reference_speed_mps", "Reference speed", kind="number", group="Report", unit="m/s"),
            _field(
                "performance_index.track_profile.integration_step_m",
                "Track integration step",
                kind="number",
                group="Track profile",
                unit="m",
            ),
            _field("performance_index.track_profile.maneuvers", "Maneuvers", kind="json", group="Track profile"),
        ),
    ),
    "ymd": ConfigSpec(
        id="ymd",
        group="envelope",
        label="YMD",
        path="_2_EnvelopeSim/YMD/ymd_config.yml",
        workflow_id="ymd",
        fields=(
            _field("generation.speed_mps", "Speed", kind="number", group="Generation", unit="m/s"),
            _field("generation.beta_min_deg", "Min beta", kind="number", group="Generation", unit="deg"),
            _field("generation.beta_max_deg", "Max beta", kind="number", group="Generation", unit="deg"),
            _field("generation.beta_points", "Beta points", kind="integer", group="Generation"),
            _field("generation.hwa_min_deg", "Min handwheel", kind="number", group="Generation", unit="deg"),
            _field("generation.hwa_max_deg", "Max handwheel", kind="number", group="Generation", unit="deg"),
            _field("generation.hwa_points", "Handwheel points", kind="integer", group="Generation"),
            _field("speed_sweep.enabled", "Speed sweep", kind="boolean", group="Speed sweep"),
            _field("speed_sweep.speeds_mps", "Sweep speeds", kind="list", group="Speed sweep", unit="m/s"),
            _field("report.enabled", "Report enabled", kind="boolean", group="Report"),
            _field("report.title", "Title", kind="string", group="Report"),
        ),
    ),
    "vehicle-review": ConfigSpec(
        id="vehicle-review",
        group="report",
        label="VehicleReview",
        path="_2_EnvelopeSim/VehicleReview/vehicle_review_config.yml",
        workflow_id="vehicle-review",
        fields=(
            _field("report.brand", "Brand", kind="string", group="Report"),
            _field("report.title", "Title", kind="string", group="Report"),
            _field("report.subtitle", "Subtitle", kind="string", group="Report"),
            _field("output.results_dir", "Results directory", kind="string", group="Output"),
            _field("output.pdf_filename", "PDF filename", kind="string", group="Output"),
            _field("output.metrics_csv_filename", "Metrics CSV filename", kind="string", group="Output"),
            _field("generation.regenerate_ggv", "Regenerate GGV", kind="boolean", group="Generation"),
            _field("generation.regenerate_ymd", "Regenerate YMD", kind="boolean", group="Generation"),
        ),
    ),
    "standard-sens": ConfigSpec(
        id="standard-sens",
        group="opt",
        label="StandardSens DOE",
        path="_4_OptSim/StandardSens/configs/_doe_config.yaml",
        workflow_id="standard-sens",
    ),
    "standard-sens-compiler": ConfigSpec(
        id="standard-sens-compiler",
        group="opt",
        label="StandardSens Compiler",
        path="_4_OptSim/StandardSens/configs/compiler_config.yaml",
        fields=(
            _field("max_workers", "Compiler workers", kind="integer", group="Compiler"),
            _field("batch.max_workers", "Batch workers", kind="integer", group="Batch"),
            _field("batch.timeout", "Batch timeout", kind="integer", group="Batch", unit="s"),
        ),
    ),
    "standard-sens-architecture": ConfigSpec(
        id="standard-sens-architecture",
        group="opt",
        label="StandardSens Architecture",
        path="_4_OptSim/StandardSens/configs/vehicle_architecture.yaml",
        fields=(
            _field("sampling.method", "Sampling method", kind="string", group="Sampling"),
            _field("sampling.intervals", "Intervals", kind="integer", group="Sampling"),
            _field("samples", "Samples", kind="integer", group="Sampling"),
            _field("seed", "Seed", kind="integer", group="Sampling"),
        ),
    ),
    "envelope-sens": ConfigSpec(
        id="envelope-sens",
        group="opt",
        label="EnvelopeSens",
        path="_4_OptSim/EnvelopeSens/config.yml",
        workflow_id="envelope-sens",
        fields=(
            _field("sampling.method", "Sampling method", kind="string", group="Sampling"),
            _field("sampling.intervals", "Intervals", kind="integer", group="Sampling"),
        ),
    ),
}


def config_specs() -> dict[str, ConfigSpec]:
    specs = dict(BASE_CONFIG_SPECS)
    visual_root = _safe_repo_path("_1_VisualSim/visual_templates")
    if visual_root.is_dir():
        for path in sorted(visual_root.glob("*.yml")):
            rel_path = path.relative_to(ROOT).as_posix()
            config_id = f"visual-{path.stem.replace('_', '-')}"
            label = path.stem.replace("_", " ").title()
            specs[config_id] = ConfigSpec(
                id=config_id,
                group="visualization",
                label=label,
                path=rel_path,
                fields=VISUAL_FIELDS,
            )
    return specs


def _config_spec(config_id: str) -> ConfigSpec:
    specs = config_specs()
    if config_id not in specs:
        raise KeyError(config_id)
    return specs[config_id]


def _load_yaml_config(spec: ConfigSpec) -> tuple[Path, str, Any]:
    path = _safe_repo_path(spec.path)
    if not path.is_file():
        raise FileNotFoundError(spec.path)
    raw = path.read_text(encoding="utf-8", errors="replace")
    data = yaml.safe_load(raw) or {}
    if not isinstance(data, (dict, list)):
        raise TypeError(f"{spec.path} must contain a YAML mapping or list")
    return path, raw, data


def _write_yaml_config(path: Path, data: Any) -> None:
    text = yaml.safe_dump(
        data,
        allow_unicode=False,
        default_flow_style=False,
        sort_keys=False,
    )
    path.write_text(text, encoding="utf-8")


def _humanize_path_part(value: PathPart) -> str:
    return str(value).replace("_", " ").replace("-", " ").title()


def _field_key(path: tuple[PathPart, ...]) -> str:
    return json.dumps(list(path), separators=(",", ":"))


def _decode_field_key(raw_key: str) -> tuple[PathPart, ...]:
    if raw_key.startswith("["):
        parts = json.loads(raw_key)
        if not isinstance(parts, list):
            raise TypeError("Config field path must be a list")
        return tuple(int(part) if isinstance(part, int) else str(part) for part in parts)
    return tuple(raw_key.split("."))


def _is_scalar(value: Any) -> bool:
    return value is None or isinstance(value, (str, int, float, bool))


def _is_scalar_list(value: list[Any]) -> bool:
    return all(_is_scalar(item) for item in value)


def _array_scalars(value: list[Any]) -> list[Any]:
    scalars: list[Any] = []
    for item in value:
        if isinstance(item, list):
            scalars.extend(_array_scalars(item))
        elif _is_scalar(item):
            scalars.append(item)
    return scalars


def _array_shape(value: Any) -> list[int]:
    if not isinstance(value, list):
        return []
    if not value or _is_scalar_list(value):
        return [len(value)]
    if all(isinstance(row, list) and _is_scalar_list(row) for row in value):
        width = max((len(row) for row in value), default=0)
        return [len(value), width]
    return []


def _array_element_kind(value: list[Any]) -> str:
    scalars = [item for item in _array_scalars(value) if item is not None]
    if not scalars:
        return "number"
    if all(isinstance(item, bool) for item in scalars):
        return "boolean"
    if all(isinstance(item, int) and not isinstance(item, bool) for item in scalars):
        return "integer"
    if all(isinstance(item, (int, float)) and not isinstance(item, bool) for item in scalars):
        return "number"
    if all(isinstance(item, str) for item in scalars):
        return "string"
    return "mixed"


def _array_payload(value: Any) -> dict[str, Any]:
    shape = _array_shape(value)
    if not shape:
        return {}
    return {
        "array_shape": shape,
        "array_element_kind": _array_element_kind(value),
    }


def _infer_field_kind(value: Any) -> str:
    if isinstance(value, bool):
        return "boolean"
    if isinstance(value, int) and not isinstance(value, bool):
        return "integer"
    if isinstance(value, float):
        return "number"
    if isinstance(value, list):
        return "list" if _is_scalar_list(value) else "json"
    if isinstance(value, dict):
        return "json"
    return "string"


def _discover_fields(data: Any, path: tuple[PathPart, ...] = ()) -> list[FieldSpec]:
    if isinstance(data, dict):
        fields: list[FieldSpec] = []
        for key, value in data.items():
            fields.extend(_discover_fields(value, (*path, str(key))))
        return fields
    if isinstance(data, list):
        if _is_scalar_list(data) or path:
            return [
                FieldSpec(
                    path=path,
                    label=_humanize_path_part(path[-1]) if path else "Value",
                    kind=_infer_field_kind(data),
                    group=_humanize_path_part(path[0]) if path else "General",
                )
            ]
        return []
    if path:
        return [
            FieldSpec(
                path=path,
                label=_humanize_path_part(path[-1]),
                kind=_infer_field_kind(data),
                group=_humanize_path_part(path[0]),
            )
        ]
    return []


def _get_nested(data: Any, path: tuple[PathPart, ...]) -> Any:
    current = data
    for part in path:
        current = current[part]
    return current


def _bellcrank_order_choices(data: Any, axle: str) -> tuple[str, ...]:
    if not isinstance(data, dict):
        return BELLCRANK_ORDER_CHOICES
    architecture = data.get("architecture", {})
    axle_architecture = architecture.get(axle, "") if isinstance(architecture, dict) else ""
    if "stabar" in str(axle_architecture):
        return STABAR_BELLCRANK_ORDER_CHOICES
    return BELLCRANK_ORDER_CHOICES


def _field_choices(field: FieldSpec, data: Any) -> tuple[str, ...]:
    if (
        len(field.path) == 4
        and field.path[0] in {"front", "rear"}
        and field.path[1:] == ("actuation", "bellcrank", "order")
    ):
        return _bellcrank_order_choices(data, str(field.path[0]))
    return field.choices


def _set_nested(data: Any, path: tuple[PathPart, ...], value: Any) -> None:
    if not path:
        raise ValueError("Cannot replace config root through patch mode")
    current = data
    for part in path[:-1]:
        current = current[part]
    current[path[-1]] = value


def _field_payload(field: FieldSpec, data: Any) -> dict[str, Any]:
    value = _get_nested(data, field.path)
    kind = _infer_field_kind(value) if field.kind == "auto" else field.kind
    choices = _field_choices(field, data)
    return {
        "key": _field_key(field.path),
        "path": list(field.path),
        "label": field.label,
        "kind": kind,
        "group": field.group or (_humanize_path_part(field.path[0]) if field.path else "General"),
        "unit": field.unit,
        "choices": list(choices),
        "value": value,
        **_array_payload(value),
    }


def _config_fields(spec: ConfigSpec, data: Any) -> list[dict[str, Any]]:
    if spec.id == "vehicle":
        return _vehicle_config_fields(data)

    fields: list[FieldSpec] = []
    for field in spec.fields:
        try:
            _get_nested(data, field.path)
        except (KeyError, IndexError, TypeError):
            continue
        fields.append(field)
    return [_field_payload(field, data) for field in fields]


def _vehicle_config_fields(data: Any) -> list[dict[str, Any]]:
    overrides = {_field_key(field.path): field for field in VEHICLE_FIELDS}
    fields: list[FieldSpec] = []
    for field in _discover_fields(data):
        if not field.path or field.path[0] in {"schema", "paths"}:
            continue
        fields.append(overrides.get(_field_key(field.path), field))
    return [_field_payload(field, data) for field in fields]


def config_summary(spec: ConfigSpec) -> dict[str, Any]:
    return {
        "id": spec.id,
        "group": spec.group,
        "label": spec.label,
        "workflow_id": spec.workflow_id,
        **_path_payload(spec.path),
    }


def config_payload(config_id: str) -> dict[str, Any]:
    spec = _config_spec(config_id)
    path, raw, data = _load_yaml_config(spec)
    return {
        **config_summary(spec),
        "modified": path.stat().st_mtime,
        "raw": raw,
        "data": data,
        "fields": _config_fields(spec, data),
    }


def patch_config(config_id: str, values: dict[str, Any]) -> dict[str, Any]:
    spec = _config_spec(config_id)
    path, _, data = _load_yaml_config(spec)
    for raw_key, value in values.items():
        _set_nested(data, _decode_field_key(raw_key), value)
    _write_yaml_config(path, data)
    return config_payload(config_id)


def save_raw_config(config_id: str, text: str) -> dict[str, Any]:
    spec = _config_spec(config_id)
    path = _safe_repo_path(spec.path)
    data = yaml.safe_load(text) or {}
    if not isinstance(data, (dict, list)):
        raise TypeError("Config must contain a YAML mapping or list")
    path.write_text(text if text.endswith("\n") else f"{text}\n", encoding="utf-8")
    return config_payload(config_id)


def vehicle_template_payloads() -> dict[str, Any]:
    template_root = _safe_repo_path("_0_Utils/vehicle_templates")
    templates = []
    for path in sorted(template_root.glob("*.yml")):
        raw = path.read_text(encoding="utf-8", errors="replace")
        data = yaml.safe_load(raw) or {}
        if not isinstance(data, dict):
            continue
        vehicle = data.get("vehicle", {})
        architecture = data.get("architecture", {})
        templates.append(
            {
                "id": path.stem,
                "path": path.relative_to(ROOT).as_posix(),
                "label": vehicle.get("name", path.stem) if isinstance(vehicle, dict) else path.stem,
                "front": architecture.get("front") if isinstance(architecture, dict) else None,
                "rear": architecture.get("rear") if isinstance(architecture, dict) else None,
                **_powertrain_payload(data),
            }
        )
    return {"templates": templates, "powertrains": [dict(item) for item in POWERTRAIN_IMPLEMENTATIONS]}


def _powertrain_payload(data: dict[str, Any]) -> dict[str, Any]:
    powertrain_id = _powertrain_id(data)
    implementation = next(
        (item for item in POWERTRAIN_IMPLEMENTATIONS if item["id"] == powertrain_id),
        POWERTRAIN_IMPLEMENTATIONS[0],
    )
    return {
        "powertrain": implementation["id"],
        "powertrain_label": implementation["label"],
        "powertrain_status": implementation["status"],
        "powertrain_components": list(implementation["components"]),
    }


def _powertrain_id(data: dict[str, Any]) -> str:
    explicit = data.get("powertrain")
    if isinstance(explicit, dict) and explicit.get("implementation"):
        return str(explicit["implementation"])
    vehicle = data.get("vehicle", {})
    name = vehicle.get("name", "") if isinstance(vehicle, dict) else ""
    prefix = str(name).split("_", 1)[0]
    known = {str(item["id"]) for item in POWERTRAIN_IMPLEMENTATIONS}
    return prefix if prefix in known else str(POWERTRAIN_IMPLEMENTATIONS[0]["id"])


def _vehicle_summary(source_id: str, source_type: str, path: Path, data: dict[str, Any]) -> dict[str, Any]:
    vehicle = data.get("vehicle", {})
    architecture = data.get("architecture", {})
    label = vehicle.get("name", path.stem) if isinstance(vehicle, dict) else path.stem
    return {
        "id": source_id,
        "type": source_type,
        "path": path.relative_to(ROOT).as_posix() if path.is_relative_to(ROOT) else str(path),
        "label": label,
        "front": architecture.get("front") if isinstance(architecture, dict) else None,
        "rear": architecture.get("rear") if isinstance(architecture, dict) else None,
        **_powertrain_payload(data),
    }


def _load_vehicle_yaml_file(path: Path) -> dict[str, Any]:
    data = yaml.safe_load(path.read_text(encoding="utf-8", errors="replace")) or {}
    if not isinstance(data, dict):
        raise TypeError(f"{path} must contain a vehicle YAML mapping")
    return data


def _saved_vehicle_id(raw_name: str) -> str:
    base = raw_name.strip() or "vehicle"
    slug = re.sub(r"[^A-Za-z0-9_.-]+", "-", base).strip("-_.").lower()
    return slug or "vehicle"


def _saved_vehicle_path(vehicle_id: str) -> Path:
    if vehicle_id != _saved_vehicle_id(vehicle_id):
        raise ValueError("Invalid saved vehicle id")
    return _safe_repo_path(SAVED_VEHICLE_ROOT / f"{vehicle_id}.yml")


def vehicle_library_payload() -> dict[str, Any]:
    active_path = _safe_repo_path("vehicle.yml")
    active_data = _load_vehicle_yaml_file(active_path)
    sources = [_vehicle_summary("active", "active", active_path, active_data)]

    saved_root = _safe_repo_path(SAVED_VEHICLE_ROOT)
    if saved_root.is_dir():
        for path in sorted(saved_root.glob("*.yml")):
            data = _load_vehicle_yaml_file(path)
            sources.append(_vehicle_summary(f"saved:{path.stem}", "saved", path, data))

    template_root = _safe_repo_path("_0_Utils/vehicle_templates")
    if template_root.is_dir():
        for path in sorted(template_root.glob("*.yml")):
            data = _load_vehicle_yaml_file(path)
            sources.append(_vehicle_summary(f"template:{path.stem}", "template", path, data))

    return {"vehicles": sources}


def load_vehicle_source(source_id: str) -> dict[str, Any]:
    if source_id == "active":
        return config_payload("vehicle")
    if source_id.startswith("template:"):
        template_id = source_id.removeprefix("template:")
        return apply_vehicle_template(template_id)
    if source_id.startswith("saved:"):
        vehicle_id = source_id.removeprefix("saved:")
        source = _saved_vehicle_path(vehicle_id)
        if not source.is_file():
            raise FileNotFoundError(source_id)
        target = _safe_repo_path("vehicle.yml")
        target.write_text(source.read_text(encoding="utf-8"), encoding="utf-8")
        return config_payload("vehicle")
    raise ValueError(f"Unknown vehicle source: {source_id}")


def save_active_vehicle(name: str | None = None) -> dict[str, Any]:
    active_path = _safe_repo_path("vehicle.yml")
    data = _load_vehicle_yaml_file(active_path)
    vehicle = data.get("vehicle", {})
    default_name = vehicle.get("name", "vehicle") if isinstance(vehicle, dict) else "vehicle"
    vehicle_id = _saved_vehicle_id(name or str(default_name))
    saved_path = _saved_vehicle_path(vehicle_id)
    saved_path.parent.mkdir(parents=True, exist_ok=True)
    saved_path.write_text(active_path.read_text(encoding="utf-8"), encoding="utf-8")
    return {
        "saved": _vehicle_summary(f"saved:{vehicle_id}", "saved", saved_path, data),
        **vehicle_library_payload(),
    }


def delete_saved_vehicle(source_id: str) -> dict[str, Any]:
    if not source_id.startswith("saved:"):
        raise ValueError("Only saved vehicle configs can be deleted")
    vehicle_id = source_id.removeprefix("saved:")
    path = _saved_vehicle_path(vehicle_id)
    if not path.is_file():
        raise FileNotFoundError(source_id)
    path.unlink()
    return vehicle_library_payload()


def _tire_template_root_from_active_vehicle() -> Path:
    active_path = _safe_repo_path("vehicle.yml")
    data = _load_vehicle_yaml_file(active_path)
    paths = data.get("paths", {})
    raw_root = "_0_Utils/tire_templates"
    if isinstance(paths, dict) and paths.get("tire_templates"):
        raw_root = str(paths["tire_templates"])
    root = _safe_repo_path(raw_root)
    root.mkdir(parents=True, exist_ok=True)
    return root


def _tire_template_slug(raw_name: str) -> str:
    name = Path(raw_name).stem
    slug = re.sub(r"[^A-Za-z0-9_.-]+", "_", name).strip("._-")
    if not slug:
        raise ValueError("Tire template name is required")
    return slug


def _tire_template_file(raw_name: str) -> Path:
    template_id = _tire_template_slug(raw_name)
    return _tire_template_root_from_active_vehicle() / f"{template_id}.tir"


def tire_template_library_payload() -> dict[str, Any]:
    root = _tire_template_root_from_active_vehicle()
    templates = []
    for path in sorted(root.glob("*.tir")):
        stat = path.stat()
        templates.append(
            {
                "id": path.stem,
                "label": path.name,
                "path": path.relative_to(ROOT).as_posix(),
                "size": stat.st_size,
                "modified": stat.st_mtime,
            }
        )
    return {"templates": templates}


def read_tire_template(raw_name: str) -> dict[str, Any]:
    path = _tire_template_file(raw_name)
    if not path.is_file():
        raise FileNotFoundError(raw_name)
    text = path.read_text(encoding="utf-8", errors="replace")
    parsed = parse_tir(path)
    return {
        "id": path.stem,
        "label": path.name,
        "path": path.relative_to(ROOT).as_posix(),
        "text": text,
        "metadata": {
            "fznom_n": _num(parsed, "FNOMIN"),
            "fzmin_n": _num(parsed, "FZMIN"),
            "fzmax_n": _num(parsed, "FZMAX"),
            "pressure_pa": _num(parsed, "IP_NOM"),
            "unloaded_radius_m": _num(parsed, "UNLOADED_RADIUS"),
            "width_m": _num(parsed, "WIDTH"),
            "longvl_mps": _num(parsed, "LONGVL"),
        },
    }


def save_tire_template(raw_name: str, text: str) -> dict[str, Any]:
    path = _tire_template_file(raw_name)
    if "[MDI_HEADER]" not in text and "FNOMIN" not in text:
        raise ValueError("Tire template text does not look like a .tir file")
    path.write_text(text if text.endswith("\n") else f"{text}\n", encoding="utf-8")
    return read_tire_template(path.stem)


def apply_vehicle_template(template_id: str) -> dict[str, Any]:
    if "/" in template_id or "\\" in template_id or template_id.startswith("."):
        raise ValueError("Invalid template id")
    source = _safe_repo_path(f"_0_Utils/vehicle_templates/{template_id}.yml")
    if not source.is_file():
        raise FileNotFoundError(template_id)
    target = _safe_repo_path("vehicle.yml")
    target.write_text(source.read_text(encoding="utf-8"), encoding="utf-8")
    return config_payload("vehicle")


def workflow_payload(workflow: WorkflowSpec) -> dict[str, Any]:
    specs = config_specs()
    actions = [ACTION_SPECS[action_id] for action_id in workflow.actions]
    outputs = [
        {
            "label": output.label,
            "kind": output.kind,
            **_path_payload(output.path),
        }
        for output in workflow.outputs
    ]
    return {
        "id": workflow.id,
        "group": workflow.group,
        "label": workflow.label,
        "config": _path_payload(workflow.config) if workflow.config else None,
        "config_id": workflow.id if workflow.id in specs else None,
        "actions": [{"id": action.id, "label": action.label, "argv": list(action.argv)} for action in actions],
        "outputs": outputs,
    }


def status_payload() -> dict[str, Any]:
    vehicle_exe = "_3_StandardSim/BuildBobLib/VehicleSim/BobLib.Experiments.Standards.VehicleSim"
    four_post_exe = "_3_StandardSim/BuildBobLib/FourPostSim/BobLib.Experiments.Standards.FourPostSim"
    return {
        "repo": {
            "root": str(ROOT),
            "boblib_package": _path_payload("_0_Utils/external/BobLib/BobLib/package.mo"),
            "vehicle_exe": _path_payload(vehicle_exe),
            "four_post_exe": _path_payload(four_post_exe),
            "vehicle_yml": _path_payload("vehicle.yml"),
        },
        "workflows": [workflow_payload(workflow) for workflow in WORKFLOWS],
        "configs": [config_summary(spec) for spec in config_specs().values()],
        "jobs": JOBS.list()[:8],
    }


def _num(values: dict[str, Any], key: str, default: float = 0.0) -> float:
    try:
        value = float(values.get(key, default))
    except (TypeError, ValueError):
        return default
    return value if math.isfinite(value) else default


def _sign(value: float) -> float:
    if value > 0.0:
        return 1.0
    if value < 0.0:
        return -1.0
    return 0.0


def _linspace(start: float, stop: float, count: int) -> list[float]:
    if count <= 1:
        return [start]
    step = (stop - start) / (count - 1)
    return [start + idx * step for idx in range(count)]


def _point(raw: Any) -> list[float] | None:
    if not isinstance(raw, list) or len(raw) < 3:
        return None
    try:
        point = [float(raw[0]), float(raw[1]), float(raw[2])]
    except (TypeError, ValueError):
        return None
    return point if all(math.isfinite(value) for value in point) else None


def _active_mass_records(vehicle: dict[str, Any]) -> list[tuple[float, list[float]]]:
    records: list[tuple[float, list[float]]] = []

    def add(raw_mass: Any, raw_cg: Any, *, mirror_y: float = 1.0) -> None:
        try:
            mass = float(raw_mass)
        except (TypeError, ValueError):
            return
        cg = _point(raw_cg)
        if cg is None or not math.isfinite(mass) or mass <= 0.0:
            return
        records.append((mass, [cg[0], cg[1] * mirror_y, cg[2]]))

    for key in ("sprung_mass", "driver_mass"):
        section = vehicle.get(key)
        if isinstance(section, dict):
            add(section.get("mass_kg"), section.get("cg_m"))

    for axle_name in ("front", "rear"):
        axle = vehicle.get(axle_name)
        if not isinstance(axle, dict):
            continue
        masses = axle.get("masses", {})
        if not isinstance(masses, dict):
            continue
        for side in (1.0, -1.0):
            for mass_section in masses.values():
                if isinstance(mass_section, dict):
                    add(mass_section.get("mass_kg"), mass_section.get("cg_m"), mirror_y=side)
    return records


def _active_static_tire_loads(vehicle: dict[str, Any]) -> dict[str, float]:
    records = _active_mass_records(vehicle)
    if not records:
        return {}
    total_mass = sum(mass for mass, _ in records)
    if total_mass <= 0.0:
        return {}
    cg_x = sum(mass * cg[0] for mass, cg in records) / total_mass
    front_wc = _point(vehicle.get("front", {}).get("suspension", {}).get("wheel_center_m"))
    rear_wc = _point(vehicle.get("rear", {}).get("suspension", {}).get("wheel_center_m"))
    if front_wc is None or rear_wc is None:
        return {}
    wheelbase = front_wc[0] - rear_wc[0]
    if abs(wheelbase) <= 1e-9:
        return {}
    front_fraction = max(0.0, min(1.0, (cg_x - rear_wc[0]) / wheelbase))
    total_weight = total_mass * 9.80665
    return {
        "front": total_weight * front_fraction / 2.0,
        "rear": total_weight * (1.0 - front_fraction) / 2.0,
    }


def _tire_template_for_side(vehicle: dict[str, Any], side_name: str) -> str:
    aero = vehicle.get("aero", {})
    if isinstance(aero, dict) and aero.get("tire_template"):
        return str(aero["tire_template"])
    side = vehicle.get(side_name, {})
    if not isinstance(side, dict):
        return ""
    tire = side.get("tire", {})
    return str(tire.get("template", "")) if isinstance(tire, dict) else ""


def _tire_template_path(vehicle: dict[str, Any], template: str) -> Path:
    paths = vehicle.get("paths", {})
    raw_root = "_0_Utils/tire_templates"
    if isinstance(paths, dict) and paths.get("tire_templates"):
        raw_root = str(paths["tire_templates"])
    return _safe_repo_path(Path(raw_root) / f"{template}.tir")


def _mf52_fx_pure(tire: dict[str, Any], fz: float, kappa: float, gamma: float) -> float:
    if fz <= 1e-3:
        return 0.0
    lfzo = _num(tire, "LFZO", 1.0)
    fznom = max(_num(tire, "FNOMIN", 1.0) * lfzo, 1e-8)
    ia_x = gamma * _num(tire, "LGAX", 1.0)
    dfz = (fz - fznom) / fznom
    mu_x = (
        (_num(tire, "PDX1") + _num(tire, "PDX2") * dfz)
        * (1 - _num(tire, "PDX3") * ia_x**2)
        * _num(tire, "LMUX", 1.0)
    )
    c = _num(tire, "PCX1", 1.0) * _num(tire, "LCX", 1.0)
    d = mu_x * fz
    k = (
        fz
        * (_num(tire, "PKX1") + _num(tire, "PKX2") * dfz)
        * math.exp(_num(tire, "PKX3") * dfz)
        * _num(tire, "LKX", 1.0)
    )
    b = k / (c * d + 1e-8)
    sh = (_num(tire, "PHX1") + _num(tire, "PHX2") * dfz) * _num(tire, "LHX", 1.0)
    sv = fz * (_num(tire, "PVX1") + _num(tire, "PVX2") * dfz) * _num(tire, "LVX", 1.0) * _num(tire, "LMUX", 1.0)
    slip = kappa + sh
    e = (_num(tire, "PEX1") + _num(tire, "PEX2") * dfz + _num(tire, "PEX3") * dfz**2)
    e *= (1 - _num(tire, "PEX4") * _sign(slip)) * _num(tire, "LEX", 1.0)
    e = min(e, 1.0)
    return d * math.sin(c * math.atan(b * slip - e * (b * slip - math.atan(b * slip)))) + sv


def _mf52_fy_pure(tire: dict[str, Any], fz: float, alpha: float, gamma: float) -> float:
    if fz <= 1e-3:
        return 0.0
    lfzo = _num(tire, "LFZO", 1.0)
    fznom_raw = max(_num(tire, "FNOMIN", 1.0), 1e-8)
    fznom = fznom_raw * lfzo
    ia_y = gamma * _num(tire, "LGAY", 1.0)
    dfz = (fz - fznom) / fznom
    mu_y = (
        (_num(tire, "PDY1") + _num(tire, "PDY2") * dfz)
        * (1 - _num(tire, "PDY3") * ia_y**2)
        * _num(tire, "LMUY", 1.0)
    )
    c = _num(tire, "PCY1", 1.0) * _num(tire, "LCY", 1.0)
    d = mu_y * fz
    pky2 = max(abs(_num(tire, "PKY2", 1.0)), 1e-8)
    k = (
        _num(tire, "PKY1")
        * fznom_raw
        * math.sin(2 * math.atan(fz / (pky2 * fznom)))
        * (1 - _num(tire, "PKY3") * abs(ia_y))
        * lfzo
        * _num(tire, "LKY", 1.0)
    )
    b = k / (c * d + 1e-8)
    sh = (_num(tire, "PHY1") + _num(tire, "PHY2") * dfz) * _num(tire, "LHY", 1.0) + _num(tire, "PHY3") * ia_y
    sv = fz * (
        (_num(tire, "PVY1") + _num(tire, "PVY2") * dfz) * _num(tire, "LVY", 1.0)
        + (_num(tire, "PVY3") + _num(tire, "PVY4") * dfz) * ia_y
    ) * _num(tire, "LMUY", 1.0)
    slip = alpha + sh
    e = (_num(tire, "PEY1") + _num(tire, "PEY2") * dfz)
    e *= (1 - (_num(tire, "PEY3") + _num(tire, "PEY4") * ia_y) * _sign(slip)) * _num(tire, "LEY", 1.0)
    e = min(e, 1.0)
    return d * math.sin(c * math.atan(b * slip - e * (b * slip - math.atan(b * slip)))) + sv


def _magic_cos_reduction(c: float, b: float, e: float, slip: float, shift: float) -> float:
    numerator = math.cos(c * math.atan(b * slip - e * (b * slip - math.atan(b * slip))))
    denominator = math.cos(c * math.atan(b * shift - e * (b * shift - math.atan(b * shift))))
    return numerator / denominator if abs(denominator) > 1e-8 else 1.0


def _mf52_fx_combined(tire: dict[str, Any], fz: float, kappa: float, alpha: float, gamma: float) -> float:
    if fz <= 1e-3:
        return 0.0
    fx_pure = _mf52_fx_pure(tire, fz, kappa, gamma)
    lfzo = _num(tire, "LFZO", 1.0)
    fznom = max(_num(tire, "FNOMIN", 1.0) * lfzo, 1e-8)
    dfz = (fz - fznom) / fznom
    c = _num(tire, "RCX1", 1.0)
    b = _num(tire, "RBX1") * math.cos(math.atan(_num(tire, "RBX2") * kappa)) * _num(tire, "LXAL", 1.0)
    e = _num(tire, "REX1") + _num(tire, "REX2") * dfz
    shift = _num(tire, "RHX1")
    return fx_pure * _magic_cos_reduction(c, b, e, alpha + shift, shift)


def _mf52_fy_combined(tire: dict[str, Any], fz: float, alpha: float, kappa: float, gamma: float) -> float:
    if fz <= 1e-3:
        return 0.0
    fy_pure = _mf52_fy_pure(tire, fz, alpha, gamma)
    lfzo = _num(tire, "LFZO", 1.0)
    fznom = max(_num(tire, "FNOMIN", 1.0) * lfzo, 1e-8)
    dfz = (fz - fznom) / fznom
    c = _num(tire, "RCY1", 1.0)
    b = _num(tire, "RBY1") * math.cos(math.atan(_num(tire, "RBY2") * (alpha - _num(tire, "RBY3"))))
    b *= _num(tire, "LYKA", 1.0)
    e = _num(tire, "REY1") + _num(tire, "REY2") * dfz
    shift = _num(tire, "RHY1") + _num(tire, "RHY2") * dfz
    ia_y = gamma * _num(tire, "LGAY", 1.0)
    d_v = (
        (_num(tire, "PDY1") + _num(tire, "PDY2") * dfz)
        * (1 - _num(tire, "PDY3") * ia_y**2)
        * _num(tire, "LMUY", 1.0)
        * fz
        * (_num(tire, "RVY1") + _num(tire, "RVY2") * dfz + _num(tire, "RVY3") * gamma)
        * math.cos(math.atan(_num(tire, "RVY4") * alpha))
    )
    s_v = d_v * math.sin(_num(tire, "RVY5") * math.atan(_num(tire, "RVY6") * kappa))
    s_v *= _num(tire, "LVYKA", 1.0)
    return fy_pure * _magic_cos_reduction(c, b, e, kappa + shift, shift) + s_v


def _mf52_curves(tire: dict[str, Any], fz: float, gamma: float) -> dict[str, Any]:
    fz_eval = max(fz, _num(tire, "FZMIN", 1.0))
    kappa_values = _linspace(_num(tire, "KPUMIN", -0.15), _num(tire, "KPUMAX", 0.15), 61)
    alpha_values = _linspace(_num(tire, "ALPMIN", -0.2617994), _num(tire, "ALPMAX", 0.2617994), 61)
    alpha_levels = [math.radians(value) for value in (-8.0, 0.0, 8.0)]
    kappa_levels = [-0.1, 0.0, 0.1]
    load_values = [
        _num(tire, "FZMIN", fz_eval),
        _num(tire, "FNOMIN", fz_eval),
        _num(tire, "FZMAX", fz_eval),
    ]
    fx = [{"kappa": value, "fx_n": _mf52_fx_pure(tire, fz_eval, value, gamma)} for value in kappa_values]
    fy = [
        {
            "alpha_rad": value,
            "alpha_deg": math.degrees(value),
            "fy_n": -_mf52_fy_pure(tire, fz_eval, value, gamma),
        }
        for value in alpha_values
    ]
    return {
        "pure": {
            "longitudinal": fx,
            "lateral": fy,
        },
        "longitudinal": fx,
        "lateral": fy,
        "combined": {
            "fx_by_alpha": [
                {
                    "alpha_rad": alpha,
                    "alpha_deg": math.degrees(alpha),
                    "points": [
                        {"kappa": kappa, "fx_n": _mf52_fx_combined(tire, fz_eval, kappa, alpha, gamma)}
                        for kappa in kappa_values
                    ],
                }
                for alpha in alpha_levels
            ],
            "fy_by_kappa": [
                {
                    "kappa": kappa,
                    "points": [
                        {
                            "alpha_rad": alpha,
                            "alpha_deg": math.degrees(alpha),
                            "fy_n": -_mf52_fy_combined(tire, fz_eval, alpha, kappa, gamma),
                        }
                        for alpha in alpha_values
                    ],
                }
                for kappa in kappa_levels
            ],
        },
        "load_sensitivity": [
            {
                "fz_n": value,
                "mu_x": abs(_mf52_fx_pure(tire, value, _num(tire, "KPUMAX", 0.15), gamma)) / max(value, 1e-8),
                "mu_y": abs(_mf52_fy_pure(tire, value, _num(tire, "ALPMAX", 0.2617994), gamma)) / max(value, 1e-8),
            }
            for value in load_values
            if value > 0.0
        ],
    }


def tire_eval_payload() -> dict[str, Any]:
    vehicle = _load_vehicle_yaml_file(_safe_repo_path("vehicle.yml"))
    static_loads = _active_static_tire_loads(vehicle)
    sides = []
    for side_name in ("front", "rear"):
        template = _tire_template_for_side(vehicle, side_name)
        if not template:
            continue
        path = _tire_template_path(vehicle, template)
        tire = parse_tir(path)
        side = vehicle.get(side_name, {})
        wheel = side.get("wheel", {}) if isinstance(side, dict) else {}
        camber_deg = float(wheel.get("camber_deg", 0.0)) if isinstance(wheel, dict) else 0.0
        fz = static_loads.get(side_name, _num(tire, "FNOMIN", 1.0))
        sides.append(
            {
                "side": side_name,
                "template": template,
                "path": path.relative_to(ROOT).as_posix(),
                "fz_n": fz,
                "camber_deg": camber_deg,
                "metadata": {
                    "fznom_n": _num(tire, "FNOMIN"),
                    "fzmin_n": _num(tire, "FZMIN"),
                    "fzmax_n": _num(tire, "FZMAX"),
                    "pressure_pa": _num(tire, "IP_NOM"),
                    "unloaded_radius_m": _num(tire, "UNLOADED_RADIUS"),
                    "width_m": _num(tire, "WIDTH"),
                    "longvl_mps": _num(tire, "LONGVL"),
                    "pdx1": _num(tire, "PDX1"),
                    "pdy1": _num(tire, "PDY1"),
                },
                "curves": _mf52_curves(tire, fz, math.radians(camber_deg)),
            }
        )
    return {
        "model": "BobLib MF52 pure-slip equations from active .tir coefficients",
        "sides": sides,
    }


def read_text_payload(raw_path: str) -> dict[str, Any]:
    path = _safe_repo_path(raw_path)
    if not path.is_file():
        raise FileNotFoundError(raw_path)
    return {
        "path": raw_path,
        "text": path.read_text(encoding="utf-8", errors="replace"),
    }


def _run_action_process(action: ActionSpec, job_id: str) -> int:
    env = os.environ.copy()
    env.update(action.env)
    env.setdefault("PYTHONUNBUFFERED", "1")
    JOBS.append_log(job_id, f"\n$ {' '.join(action.argv)}\n")
    with subprocess.Popen(
        action.argv,
        cwd=ROOT,
        env=env,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        bufsize=1,
    ) as process:
        assert process.stdout is not None
        for line in process.stdout:
            JOBS.append_log(job_id, line)
        return process.wait()


def run_actions_job(actions: tuple[ActionSpec, ...], job_id: str) -> None:
    JOBS.update(job_id, status="running", started_at=time.time())
    try:
        returncode = 0
        for action in actions:
            returncode = _run_action_process(action, job_id)
            if returncode != 0:
                break
        JOBS.update(
            job_id,
            status="succeeded" if returncode == 0 else "failed",
            returncode=returncode,
            ended_at=time.time(),
        )
    except Exception as exc:  # pragma: no cover - defensive job boundary
        JOBS.append_log(job_id, f"\n{type(exc).__name__}: {exc}\n")
        JOBS.update(job_id, status="failed", returncode=-1, ended_at=time.time())


def start_job(action_id: str) -> dict[str, Any]:
    if action_id not in ACTION_SPECS:
        raise KeyError(action_id)
    action = ACTION_SPECS[action_id]
    job = JOBS.create(action.id, action.label, list(action.argv))
    thread = threading.Thread(target=run_actions_job, args=((action,), job["id"]), daemon=True)
    thread.start()
    return job


def start_workflow(workflow_id: str) -> dict[str, Any]:
    workflows = {workflow.id: workflow for workflow in WORKFLOWS}
    if workflow_id not in workflows:
        raise KeyError(workflow_id)
    workflow = workflows[workflow_id]
    actions = tuple(ACTION_SPECS[action_id] for action_id in workflow.actions)
    label = f"Run {workflow.label}"
    argv = [action.label for action in actions]
    job = JOBS.create(f"workflow:{workflow.id}", label, argv)
    thread = threading.Thread(target=run_actions_job, args=(actions, job["id"]), daemon=True)
    thread.start()
    return job


class BobSimHandler(BaseHTTPRequestHandler):
    server_version = "BobSimApp/0.1"

    def do_GET(self) -> None:  # noqa: N802
        parsed = urlparse(self.path)
        try:
            if parsed.path == "/":
                self._send_static(STATIC_ROOT / "index.html")
            elif parsed.path.startswith("/static/"):
                rel = parsed.path.removeprefix("/static/")
                self._send_static(_safe_static_path(rel))
            elif parsed.path == "/media/bob.png":
                self._send_static(ROOT / "_0_Utils/reporting/media/bob.png")
            elif parsed.path == "/api/status":
                self._send_json(status_payload())
            elif parsed.path == "/api/configs":
                self._send_json({"configs": [config_summary(spec) for spec in config_specs().values()]})
            elif parsed.path.startswith("/api/configs/"):
                config_id = parsed.path.rsplit("/", 1)[-1]
                self._send_json(config_payload(config_id))
            elif parsed.path == "/api/vehicles":
                self._send_json(vehicle_library_payload())
            elif parsed.path == "/api/vehicle-templates":
                self._send_json(vehicle_template_payloads())
            elif parsed.path == "/api/tires/eval":
                self._send_json(tire_eval_payload())
            elif parsed.path == "/api/tires/templates":
                self._send_json(tire_template_library_payload())
            elif parsed.path == "/api/tires/template":
                self._send_json(read_tire_template(_query_one(parsed.query, "name")))
            elif parsed.path == "/api/file":
                path = _query_one(parsed.query, "path")
                self._send_json(read_text_payload(path))
            elif parsed.path == "/api/csv":
                path = _query_one(parsed.query, "path")
                self._send_json(_csv_preview(path))
            elif parsed.path == "/api/jobs":
                self._send_json({"jobs": JOBS.list()})
            elif parsed.path.startswith("/api/jobs/"):
                job_id = parsed.path.rsplit("/", 1)[-1]
                job = JOBS.get(job_id)
                if job is None:
                    self._send_error(HTTPStatus.NOT_FOUND, "Job not found")
                else:
                    self._send_json(job)
            elif parsed.path.startswith("/files/"):
                rel = unquote(parsed.path.removeprefix("/files/"))
                self._send_repo_file(rel)
            else:
                self._send_error(HTTPStatus.NOT_FOUND, "Not found")
        except Exception as exc:
            self._send_error(HTTPStatus.BAD_REQUEST, str(exc))

    def do_POST(self) -> None:  # noqa: N802
        parsed = urlparse(self.path)
        try:
            body = self._read_json_body()
            if parsed.path == "/api/jobs":
                job = start_job(str(body.get("action_id", "")))
                self._send_json(job, status=HTTPStatus.CREATED)
            elif parsed.path.startswith("/api/workflows/") and parsed.path.endswith("/run"):
                workflow_id = parsed.path.removeprefix("/api/workflows/").removesuffix("/run").strip("/")
                job = start_workflow(workflow_id)
                self._send_json(job, status=HTTPStatus.CREATED)
            elif parsed.path.startswith("/api/configs/"):
                config_id = parsed.path.rsplit("/", 1)[-1]
                mode = str(body.get("mode", "patch"))
                if mode == "raw":
                    payload = save_raw_config(config_id, str(body.get("text", "")))
                else:
                    values = body.get("values", {})
                    if not isinstance(values, dict):
                        raise TypeError("values must be an object")
                    payload = patch_config(config_id, values)
                self._send_json(payload)
            elif parsed.path == "/api/vehicle-template":
                payload = apply_vehicle_template(str(body.get("template_id", "")))
                self._send_json(payload)
            elif parsed.path == "/api/vehicles/load":
                payload = load_vehicle_source(str(body.get("source_id", "")))
                self._send_json(payload)
            elif parsed.path == "/api/vehicles/save":
                payload = save_active_vehicle(str(body.get("name", "")))
                self._send_json(payload)
            elif parsed.path == "/api/vehicles/delete":
                payload = delete_saved_vehicle(str(body.get("source_id", "")))
                self._send_json(payload)
            elif parsed.path == "/api/tires/template":
                payload = save_tire_template(str(body.get("name", "")), str(body.get("text", "")))
                self._send_json(payload)
            elif parsed.path == "/api/tires/import":
                payload = save_tire_template(str(body.get("name", "")), str(body.get("text", "")))
                self._send_json(payload)
            else:
                self._send_error(HTTPStatus.NOT_FOUND, "Not found")
        except KeyError as exc:
            self._send_error(HTTPStatus.BAD_REQUEST, f"Unknown action: {exc}")
        except Exception as exc:
            self._send_error(HTTPStatus.BAD_REQUEST, str(exc))

    def log_message(self, format: str, *args: Any) -> None:
        print(f"[app] {self.address_string()} - {format % args}")

    def _read_json_body(self) -> dict[str, Any]:
        length = int(self.headers.get("Content-Length", "0"))
        if length <= 0:
            return {}
        raw = self.rfile.read(length)
        data = json.loads(raw.decode("utf-8"))
        if not isinstance(data, dict):
            raise TypeError("Expected JSON object")
        return data

    def _send_json(self, payload: Any, status: HTTPStatus = HTTPStatus.OK) -> None:
        encoded = json.dumps(payload, indent=2).encode("utf-8")
        self.send_response(status)
        self.send_header("Content-Type", "application/json; charset=utf-8")
        self.send_header("Content-Length", str(len(encoded)))
        self.end_headers()
        self.wfile.write(encoded)

    def _send_error(self, status: HTTPStatus, message: str) -> None:
        self._send_json({"error": message}, status=status)

    def _send_static(self, path: Path) -> None:
        if not path.is_file():
            self._send_error(HTTPStatus.NOT_FOUND, "Not found")
            return
        self._send_file(path)

    def _send_repo_file(self, raw_path: str) -> None:
        path = _safe_repo_path(raw_path)
        if not path.is_file():
            self._send_error(HTTPStatus.NOT_FOUND, "File not found")
            return
        self._send_file(path)

    def _send_file(self, path: Path) -> None:
        mime_type = mimetypes.guess_type(path.name)[0] or "application/octet-stream"
        data = path.read_bytes()
        self.send_response(HTTPStatus.OK)
        self.send_header("Content-Type", mime_type)
        self.send_header("Content-Length", str(len(data)))
        self.send_header("Cache-Control", "no-store")
        self.end_headers()
        self.wfile.write(data)


def _safe_static_path(raw_path: str) -> Path:
    candidate = (STATIC_ROOT / raw_path).resolve()
    if candidate != STATIC_ROOT and STATIC_ROOT not in candidate.parents:
        raise ValueError("Static path escapes app root")
    return candidate


def _query_one(query: str, key: str) -> str:
    values = parse_qs(query).get(key)
    if not values:
        raise KeyError(key)
    return values[0]


def run(host: str, port: int) -> None:
    server = ThreadingHTTPServer((host, port), BobSimHandler)
    print(f"BobSim app running at http://{host}:{port}")
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        print("\nStopping BobSim app")
    finally:
        server.server_close()


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Run the BobSim browser app.")
    parser.add_argument("--host", default="127.0.0.1")
    parser.add_argument("--port", type=int, default=8765)
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    run(args.host, args.port)


if __name__ == "__main__":
    main()
