from __future__ import annotations

from pathlib import Path
import subprocess
from typing import Any

import pytest
import yaml

from _3_StandardSim.FourPostEval.four_post_eval_sim import (
    FOUR_POST_HEAVE_POSE_COUNT,
    FOUR_POST_STOP_TIME_S,
    FourPostEvalSim,
)
from _3_StandardSim.TransientEval.transient_eval_sim import TransientEvalSim


ROOT = Path(__file__).resolve().parents[1]
STANDARD_CONFIGS = (
    Path("_3_StandardSim/SteadyStateEval/steady_state_eval_config.yml"),
    Path("_3_StandardSim/TransientEval/transient_eval_config.yml"),
    Path("_3_StandardSim/FourPostEval/four_post_eval_config.yml"),
)


def _load_yaml(path: Path) -> dict[str, Any]:
    with (ROOT / path).open("r", encoding="utf-8") as f:
        data = yaml.safe_load(f)
    assert isinstance(data, dict)
    return data


def test_standard_sim_configs_use_internal_numerical_jacobian() -> None:
    for rel_path in STANDARD_CONFIGS:
        simulation = _load_yaml(rel_path)["simulation"]
        assert "-jacobian=internalNumerical" in simulation.get("extra_args", []), rel_path


def test_report_outputs_stay_under_standard_results() -> None:
    for rel_path in STANDARD_CONFIGS:
        report = _load_yaml(rel_path).get("report", {})
        assert isinstance(report, dict)
        for key in ("output_path", "metrics_csv_path"):
            if key not in report:
                continue
            path = Path(str(report[key]))
            assert not path.is_absolute(), f"{rel_path}: {key} should be repo-relative"
            assert path.parts[:2] == ("_3_StandardSim", "results"), rel_path


def test_application_specific_artifacts_are_not_in_bobsim() -> None:
    forbidden = (
        ROOT / "tools/generate_fsae_design_notebook.py",
        ROOT / "tools/__pycache__",
        ROOT / "uv.lock",
    )
    for path in forbidden:
        assert not path.exists(), path


def test_boblib_submodule_is_available_for_bobsim_development() -> None:
    package_mo = ROOT / "_0_Utils/external/BobLib/BobLib/package.mo"
    assert package_mo.is_file()


def test_make_help_uses_intentional_target_language() -> None:
    completed = subprocess.run(
        ["make", "help"],
        cwd=ROOT,
        check=True,
        stdout=subprocess.PIPE,
        text=True,
    )
    help_text = completed.stdout
    help_lines = {line.strip().split(maxsplit=1)[0] for line in help_text.splitlines() if line.strip()}

    for target in (
        "docker-build",
        "shell-standard",
        "standard-build",
        "standard-eval-steady-state",
        "envelope-ggv",
        "opt-standard",
        "clean-all",
    ):
        assert target in help_text

    for stale_target in (
        "sim-steady-state",
        "clean-doe",
        "ggv-envelope",
        "build-standard",
        "eval-steady-state",
        "standard-steady-state",
    ):
        assert stale_target not in help_lines


def test_compose_services_match_workflow_language() -> None:
    compose = _load_yaml(Path("docker-compose.yml"))
    services = compose.get("services")

    assert isinstance(services, dict)
    assert set(services) == {"bobsim", "standard", "envelope", "opt"}
    assert services["bobsim"]["working_dir"] == "/workspace"
    assert services["standard"]["working_dir"] == "/workspace/_3_StandardSim"
    assert services["envelope"]["working_dir"] == "/workspace/_2_EnvelopeSim"
    assert services["opt"]["working_dir"] == "/workspace/_4_OptSim"


def test_four_post_eval_uses_full_symmetric_pose_schedule() -> None:
    config = _load_yaml(Path("_3_StandardSim/FourPostEval/four_post_eval_config.yml"))

    assert FOUR_POST_HEAVE_POSE_COUNT == 11
    assert FOUR_POST_STOP_TIME_S == 118.0
    assert FourPostEvalSim(config).build_overrides()["_stopTime"] == pytest.approx(118.0)


def test_transient_eval_generates_only_step_and_sine_modes() -> None:
    config = _load_yaml(Path("_3_StandardSim/TransientEval/transient_eval_config.yml"))

    sim = TransientEvalSim.__new__(TransientEvalSim)
    sim.config = config
    cases, metadata = sim.build_cases()

    assert cases
    assert metadata
    assert {case["useMode"] for case in cases} == {1, 2}
    assert {meta["mode"] for meta in metadata} == {"step", "continuous_sine"}
    assert all(case["useMode"] != 3 for case in cases)
