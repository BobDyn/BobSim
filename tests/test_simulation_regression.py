from __future__ import annotations

import csv
from dataclasses import dataclass
import hashlib
import json
import math
import os
from pathlib import Path
import subprocess
import sys
import time
from typing import Any, Mapping, cast

import pytest
import yaml


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_BASELINE_PATH = "tests/regression_baselines/default_vehicle_standard.yml"
BASELINE_REGRESSION_ENABLED = os.environ.get("BOBSIM_BASELINE_REGRESSION", "").lower() in {
    "1",
    "true",
    "yes",
    "on",
}

MetricValue = bool | float | str


@dataclass(frozen=True)
class WorkflowData:
    name: str
    spec: Mapping[str, Any]
    metrics_csv: Path
    report_pdf: Path
    metrics: dict[str, MetricValue]
    refresh_started_at: float | None


@dataclass(frozen=True)
class RegressionData:
    baseline: Mapping[str, Any]
    workflows: dict[str, WorkflowData]
    refresh_started_at: float | None


def _repo_path(raw_path: str) -> Path:
    path = Path(raw_path)
    if path.is_absolute():
        return path
    return ROOT / path


def _baseline_path() -> Path:
    return _repo_path(os.environ.get("BOBSIM_REGRESSION_BASELINE", DEFAULT_BASELINE_PATH))


def _load_baseline() -> dict[str, Any]:
    path = _baseline_path()
    with path.open("r", encoding="utf-8") as f:
        data = yaml.safe_load(f)
    assert isinstance(data, dict), f"{path} must contain a YAML mapping"
    assert data.get("schema") == "bobsim.regression.baseline.v1"
    return data


def _workflow_specs(baseline: Mapping[str, Any]) -> Mapping[str, Mapping[str, Any]]:
    workflows = baseline.get("workflows")
    assert isinstance(workflows, dict), "baseline workflows section must be a mapping"
    return cast(Mapping[str, Mapping[str, Any]], workflows)


STUDY_CONFIGS = {
    "four_post": "_3_StandardSim/FourPostEval/four_post_eval_config.yml",
    "ramp_steer": "_3_StandardSim/RampSteerEval/ramp_steer_eval_config.yml",
    "steady_state": "_3_StandardSim/SteadyStateEval/steady_state_eval_config.yml",
    "transient": "_3_StandardSim/TransientEval/transient_eval_config.yml",
}

# Only sections that can move a simulated number. `execution` (worker counts),
# `report`, and `plots` are deliberately excluded so cosmetic edits and
# parallelism tuning do not invalidate a baseline that is still valid.
RESULT_AFFECTING_SECTIONS = ("simulation", "sweep", "fit")

BOBLIB_SUBMODULE = "_0_Utils/external/BobLib"


def simulation_inputs_digest() -> str:
    """Digest of everything that can change a simulated metric."""
    payload: dict[str, Any] = {}
    for name, relative in sorted(STUDY_CONFIGS.items()):
        config = yaml.safe_load((ROOT / relative).read_text(encoding="utf-8")) or {}
        payload[name] = {
            section: config[section]
            for section in RESULT_AFFECTING_SECTIONS
            if section in config
        }
    payload["vehicle"] = yaml.safe_load((ROOT / "vehicle.yml").read_text(encoding="utf-8"))
    blob = json.dumps(payload, sort_keys=True, separators=(",", ":"), default=str)
    return hashlib.sha256(blob.encode("utf-8")).hexdigest()


def pinned_boblib_commit() -> str | None:
    """The committed BobLib gitlink, or None outside a git checkout."""
    try:
        result = subprocess.run(
            ["git", "rev-parse", f"HEAD:{BOBLIB_SUBMODULE}"],
            cwd=ROOT,
            capture_output=True,
            text=True,
            timeout=30,
        )
    except (OSError, subprocess.SubprocessError):
        return None
    if result.returncode != 0:
        return None
    return result.stdout.strip() or None


def _artifact_path(workflow: Mapping[str, Any], artifact_key: str) -> Path:
    artifacts = workflow.get("artifacts")
    assert isinstance(artifacts, dict), "workflow artifacts section must be a mapping"

    raw_path = artifacts.get(artifact_key)
    assert isinstance(raw_path, str), f"workflow artifacts.{artifact_key} must be a string"

    results_dir = os.environ.get("BOBSIM_REGRESSION_RESULTS_DIR")
    if results_dir:
        return _repo_path(results_dir) / Path(raw_path).name

    path = _repo_path(raw_path)
    generated_path = _standard_generated_artifact_path(path)
    if generated_path is None:
        return path
    if BASELINE_REGRESSION_ENABLED and generated_path.exists():
        return generated_path
    if path.exists():
        return path
    return generated_path


def _standard_generated_artifact_path(path: Path) -> Path | None:
    try:
        relative = path.relative_to(ROOT)
    except ValueError:
        return None
    if len(relative.parts) < 3 or relative.parts[:2] != ("_3_StandardSim", "results"):
        return None
    return ROOT / "_3_StandardSim" / "generated_results" / Path(*relative.parts[2:])


def _min_report_bytes(workflow: Mapping[str, Any]) -> int:
    artifacts = workflow.get("artifacts")
    assert isinstance(artifacts, dict), "workflow artifacts section must be a mapping"
    value = artifacts.get("min_report_bytes", 1)
    assert isinstance(value, int), "min_report_bytes must be an integer"
    return value


def _parse_scalar(raw_value: str) -> MetricValue:
    stripped = raw_value.strip()
    lowered = stripped.lower()
    if lowered == "true":
        return True
    if lowered == "false":
        return False
    try:
        return float(stripped)
    except ValueError:
        return stripped


def _metric_key(row: Mapping[str, str | None]) -> str:
    metric = row.get("metric")
    assert metric is not None, "metrics CSV row is missing metric"

    metric_name = metric.strip()
    assert metric_name, "metrics CSV row has an empty metric name"

    group = (row.get("group") or "").strip()
    if group:
        return f"{group}.{metric_name}"
    return metric_name


def _load_metrics_csv(path: Path) -> dict[str, MetricValue]:
    with path.open("r", encoding="utf-8", newline="") as f:
        reader = csv.DictReader(f)
        assert reader.fieldnames is not None, f"{path} must have a header row"
        assert "metric" in reader.fieldnames, f"{path} must include a metric column"
        assert "value" in reader.fieldnames, f"{path} must include a value column"

        metrics: dict[str, MetricValue] = {}
        for line_number, row in enumerate(reader, start=2):
            value = row.get("value")
            assert value is not None, f"{path}:{line_number} is missing value"

            metric_name = _metric_key(row)
            parsed_value = _parse_scalar(value)
            if metric_name in metrics:
                existing = metrics[metric_name]
                if isinstance(existing, float) and isinstance(parsed_value, float):
                    assert existing == pytest.approx(parsed_value, rel=1e-12, abs=1e-12), (
                        f"{path}:{line_number} duplicates {metric_name} with a different value"
                    )
                else:
                    assert existing == parsed_value, (
                        f"{path}:{line_number} duplicates {metric_name} with a different value"
                    )
                continue
            metrics[metric_name] = parsed_value
    return metrics


def _refresh_standard_artifacts(baseline: Mapping[str, Any]) -> float:
    refresh = baseline.get("refresh")
    assert isinstance(refresh, dict), "baseline refresh section must be a mapping"
    make_targets = refresh.get("make_targets")
    assert isinstance(make_targets, list) and all(isinstance(t, str) for t in make_targets), (
        "baseline refresh.make_targets must be a string list"
    )

    started_at = time.time()
    env = os.environ.copy()
    env.setdefault("PYTHON", sys.executable)
    command = ["make", "-B", *make_targets]
    completed = subprocess.run(
        command,
        cwd=ROOT,
        env=env,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        timeout=2400,
    )
    assert completed.returncode == 0, (
        "StandardSim regression refresh failed before the baseline comparison.\n"
        f"Command: {' '.join(command)}\n{completed.stdout}"
    )
    return started_at


@pytest.fixture(scope="session")
def standard_regression_data() -> RegressionData:
    baseline = _load_baseline()
    refresh_started_at = _refresh_standard_artifacts(baseline) if BASELINE_REGRESSION_ENABLED else None

    workflows: dict[str, WorkflowData] = {}
    for name, workflow in _workflow_specs(baseline).items():
        metrics_csv = _artifact_path(workflow, "metrics_csv")
        report_pdf = _artifact_path(workflow, "report_pdf")
        missing_artifacts = [path for path in (metrics_csv, report_pdf) if not path.is_file()]
        if missing_artifacts and not BASELINE_REGRESSION_ENABLED:
            pytest.skip(
                "standard regression artifacts are not available; run make regression-baseline to refresh them"
            )

        assert metrics_csv.is_file(), f"missing regression metrics artifact: {metrics_csv}"
        assert report_pdf.is_file(), f"missing regression report artifact: {report_pdf}"
        assert report_pdf.stat().st_size >= _min_report_bytes(workflow), (
            f"{report_pdf} looks too small to be a report"
        )

        if refresh_started_at is not None:
            for path in (metrics_csv, report_pdf):
                assert path.stat().st_mtime >= refresh_started_at - 1.0, (
                    f"{path} was not refreshed during this pytest run"
                )

        workflows[name] = WorkflowData(
            name=name,
            spec=workflow,
            metrics_csv=metrics_csv,
            report_pdf=report_pdf,
            metrics=_load_metrics_csv(metrics_csv),
            refresh_started_at=refresh_started_at,
        )

    return RegressionData(
        baseline=baseline,
        workflows=workflows,
        refresh_started_at=refresh_started_at,
    )


@pytest.fixture(params=("four_post", "ramp_steer", "steady_state", "transient"))
def workflow_data(
    request: pytest.FixtureRequest,
    standard_regression_data: RegressionData,
) -> WorkflowData:
    return standard_regression_data.workflows[cast(str, request.param)]


def _metric(metrics: Mapping[str, MetricValue], name: str) -> MetricValue:
    assert name in metrics, f"missing metric: {name}"
    return metrics[name]


def _numeric_metric(metrics: Mapping[str, MetricValue], name: str) -> float:
    value = _metric(metrics, name)
    assert isinstance(value, float), f"{name} must be numeric, got {value!r}"
    assert math.isfinite(value), f"{name} must be finite, got {value!r}"
    return value


def _bool_metric(metrics: Mapping[str, MetricValue], name: str) -> bool:
    value = _metric(metrics, name)
    assert isinstance(value, bool), f"{name} must be boolean, got {value!r}"
    return value


def _metric_baselines(workflow: Mapping[str, Any]) -> Mapping[str, Mapping[str, Any]]:
    metrics = workflow.get("metrics")
    assert isinstance(metrics, dict), "workflow metrics section must be a mapping"
    return cast(Mapping[str, Mapping[str, Any]], metrics)


def _optional_float(spec: Mapping[str, Any], key: str) -> float:
    value = spec.get(key, 0.0)
    assert isinstance(value, (float, int)) and not isinstance(value, bool), f"{key} must be numeric"
    return float(value)


def _keys_ending_with(metrics: Mapping[str, MetricValue], suffix: str) -> list[str]:
    return sorted(key for key in metrics if key == suffix or key.endswith(f".{suffix}"))


def test_default_vehicle_standard_artifacts_are_refreshed_by_pytest(
    standard_regression_data: RegressionData,
) -> None:
    if not BASELINE_REGRESSION_ENABLED:
        pytest.skip("set BOBSIM_BASELINE_REGRESSION=1 to refresh artifacts through pytest")

    assert standard_regression_data.refresh_started_at is not None
    for workflow in standard_regression_data.workflows.values():
        assert workflow.refresh_started_at is not None


def test_regression_artifacts_are_well_formed(workflow_data: WorkflowData) -> None:
    metric_baselines = _metric_baselines(workflow_data.spec)
    missing = [metric for metric in metric_baselines if metric not in workflow_data.metrics]
    assert not missing, f"{workflow_data.metrics_csv} is missing metrics: {missing}"

    for metric, value in workflow_data.metrics.items():
        if isinstance(value, float):
            assert math.isfinite(value), f"{workflow_data.name}.{metric} is not finite"


def test_regression_workflows_complete_successfully(workflow_data: WorkflowData) -> None:
    metrics = workflow_data.metrics

    for failed_key in _keys_ending_with(metrics, "n_failed_cases"):
        assert _numeric_metric(metrics, failed_key) == 0.0

    for cases_key in _keys_ending_with(metrics, "n_cases"):
        prefix = cases_key.removesuffix("n_cases")
        successful_key = f"{prefix}n_successful_cases"
        if successful_key in metrics:
            assert _numeric_metric(metrics, successful_key) == _numeric_metric(metrics, cases_key)


def test_four_post_regression_metrics_remain_physically_consistent(
    standard_regression_data: RegressionData,
) -> None:
    metrics = standard_regression_data.workflows["four_post"].metrics

    assert _bool_metric(metrics, "static_balance_pass") is True
    assert _numeric_metric(metrics, "static_balance_max_abs_fz_error_n") <= 5.0

    for metric in ("avg_motion_ratio_front", "avg_motion_ratio_rear"):
        assert 0.05 <= abs(_numeric_metric(metrics, metric)) <= 5.0

    for metric in ("avg_stabar_motion_ratio_front", "avg_stabar_motion_ratio_rear"):
        assert 0.01 <= abs(_numeric_metric(metrics, metric)) <= 2.0

    spring_front = _numeric_metric(metrics, "spring_roll_stiffness_front_Nm_per_rad")
    spring_rear = _numeric_metric(metrics, "spring_roll_stiffness_rear_Nm_per_rad")
    arb_front = _numeric_metric(metrics, "arb_roll_stiffness_front_Nm_per_rad")
    arb_rear = _numeric_metric(metrics, "arb_roll_stiffness_rear_Nm_per_rad")
    elastic_front = _numeric_metric(metrics, "elastic_roll_stiffness_front_Nm_per_rad")
    elastic_rear = _numeric_metric(metrics, "elastic_roll_stiffness_rear_Nm_per_rad")

    assert spring_front > 0.0
    assert spring_rear > 0.0
    assert arb_front > 0.0
    assert arb_rear > 0.0
    assert elastic_front == pytest.approx(spring_front + arb_front, rel=1e-9, abs=1e-6)
    assert elastic_rear == pytest.approx(spring_rear + arb_rear, rel=1e-9, abs=1e-6)

    roll_rate_distribution = _numeric_metric(metrics, "avg_roll_rate_distribution_front_pct")
    expected_roll_rate_distribution = 100.0 * elastic_front / (elastic_front + elastic_rear)
    assert roll_rate_distribution == pytest.approx(expected_roll_rate_distribution, abs=0.01)
    assert 0.0 <= roll_rate_distribution <= 100.0

    lltd_front_frac = _numeric_metric(metrics, "avg_lltd_front_frac")
    lltd_front_pct = _numeric_metric(metrics, "avg_lltd_front_pct")
    antiroll_geometry_delta = _numeric_metric(metrics, "avg_antiroll_geometry_lltd_delta_pct")

    assert lltd_front_pct == pytest.approx(100.0 * lltd_front_frac, abs=0.01)
    assert 0.0 <= lltd_front_pct <= 100.0
    assert antiroll_geometry_delta == pytest.approx(lltd_front_pct - roll_rate_distribution, abs=0.01)
    assert abs(antiroll_geometry_delta) <= 25.0


@pytest.mark.parametrize("workflow_name", ("ramp_steer", "steady_state"))
def test_lateral_response_regression_metrics_remain_physically_consistent(
    workflow_name: str,
    standard_regression_data: RegressionData,
) -> None:
    metrics = standard_regression_data.workflows[workflow_name].metrics

    ay_min = _numeric_metric(metrics, "ay_min")
    ay_max = _numeric_metric(metrics, "ay_max")
    limit_ay = _numeric_metric(metrics, "limit_ay_mps2")

    assert 0.0 < ay_min < ay_max
    assert ay_min <= limit_ay <= ay_max + 1.0
    assert 0.2 <= abs(_numeric_metric(metrics, "roll_gradient_deg_per_g")) <= 2.0
    assert 5.0 <= abs(_numeric_metric(metrics, "handwheel_angle_gradient_deg_per_g")) <= 30.0
    assert 0.0 <= _numeric_metric(metrics, "roadwheel_fit_nrmse") <= 0.15
    assert 0.0 <= _numeric_metric(metrics, "steer_excess_fit_nrmse") <= 0.25


def test_transient_regression_metrics_remain_physically_consistent(
    standard_regression_data: RegressionData,
) -> None:
    metrics = standard_regression_data.workflows["transient"].metrics

    assert _numeric_metric(metrics, "step.ay_peak") > _numeric_metric(metrics, "step.ay_ss") > 0.0
    assert _numeric_metric(metrics, "step.ay_gain_dc") > 0.0
    assert _numeric_metric(metrics, "step.yaw_gain_dc") > 0.0
    assert _numeric_metric(metrics, "step.roll_gain_dc") > 0.0
    assert _numeric_metric(metrics, "step.settling_time_s") > 0.0
    assert _numeric_metric(metrics, "frequency.ay_gain_peak") >= _numeric_metric(
        metrics,
        "frequency.ay_gain_dc",
    )
    assert _numeric_metric(metrics, "frequency.yaw_gain_peak") >= _numeric_metric(
        metrics,
        "frequency.yaw_gain_dc",
    )
    assert 0.0 <= _numeric_metric(metrics, "quality.ay_fit_error") <= 0.05
    assert 0.0 <= _numeric_metric(metrics, "quality.yaw_fit_error") <= 0.05


def test_baseline_provenance_matches_simulation_inputs() -> None:
    """Fail fast when the baseline no longer describes the current inputs.

    Runs without OpenModelica so it gates every PR. The baseline previously went
    stale for 79 commits because nothing tied it to the pin and configs it guards.
    """
    baseline = _load_baseline()
    provenance = baseline.get("provenance")
    assert isinstance(provenance, dict), (
        "baseline must carry a provenance section; regenerate it with "
        "make regression-baseline"
    )

    expected_digest = simulation_inputs_digest()
    recorded_digest = provenance.get("simulation_inputs_digest")
    assert recorded_digest == expected_digest, (
        "Simulation inputs changed since this baseline was recorded "
        f"(recorded {recorded_digest}, current {expected_digest}).\n"
        "A vehicle.yml or study simulation/sweep/fit change can move every metric.\n"
        "Run `make regression-baseline`, review the regenerated reports, then "
        "refresh the baseline and its provenance."
    )

    recorded_commit = provenance.get("boblib_commit")
    current_commit = pinned_boblib_commit()
    if current_commit is None:
        pytest.skip("BobLib pin unavailable outside a git checkout")
    assert recorded_commit == current_commit, (
        f"BobLib pin moved since this baseline was recorded "
        f"(recorded {recorded_commit}, current {current_commit}).\n"
        "A BobLib bump can change physics -- v0.2.0 altered vehicle mass, CG, and "
        "inertia and went unnoticed for weeks.\n"
        "Run `make regression-baseline` and refresh the baseline, or, if you have "
        "confirmed the bump cannot affect physics, update provenance.boblib_commit "
        "deliberately in the same commit."
    )


@pytest.mark.skipif(
    not BASELINE_REGRESSION_ENABLED,
    reason="set BOBSIM_BASELINE_REGRESSION=1 to compare against the default vehicle baseline",
)
def test_default_vehicle_standard_metrics_match_baseline(workflow_data: WorkflowData) -> None:
    # Every metric is checked before failing: this test is gated behind a ~12 min
    # simulation refresh, so aborting on the first mismatch would leak one drifted
    # metric per run.
    failures: list[str] = []

    for metric, spec in _metric_baselines(workflow_data.spec).items():
        assert "value" in spec, f"{workflow_data.name}.{metric} baseline must define value"
        expected = spec["value"]
        observed = _metric(workflow_data.metrics, metric)

        if isinstance(expected, bool):
            if observed is not expected:
                failures.append(f"  {metric}: observed {observed!r}, expected {expected!r}")
            continue

        if isinstance(expected, str):
            if observed != expected:
                failures.append(f"  {metric}: observed {observed!r}, expected {expected!r}")
            continue

        assert isinstance(expected, (float, int)), (
            f"{workflow_data.name}.{metric} baseline value must be numeric, boolean, or string"
        )
        observed_float = _numeric_metric(workflow_data.metrics, metric)
        expected_float = float(expected)
        abs_tol = _optional_float(spec, "abs_tol")
        rel_tol = _optional_float(spec, "rel_tol")
        tolerance = max(abs_tol, abs(expected_float) * rel_tol)
        error = abs(observed_float - expected_float)

        if error > tolerance:
            failures.append(
                f"  {metric}: observed {observed_float:.6g}, expected {expected_float:.6g}, "
                f"error {error:.4g} exceeds tolerance {tolerance:.4g}"
            )

    assert not failures, (
        f"{workflow_data.name}: {len(failures)} metric(s) drifted from baseline:\n"
        + "\n".join(failures)
    )
