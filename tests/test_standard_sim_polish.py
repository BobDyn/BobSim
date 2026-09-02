from __future__ import annotations

from pathlib import Path
import re
import subprocess
from typing import Any

import numpy as np
import pytest
import yaml

from _0_Utils.plotting.plot_types.signal_plot import SignalPlot
from _0_Utils.reporting.report_engine import _raw_time_series_frame
from _3_StandardSim.FourPostEval.four_post_eval_sim import (
    FOUR_POST_DEFAULT_ROLL_MAGNITUDE_RAD,
    FOUR_POST_HEAVE_END_S,
    FOUR_POST_HEAVE_POSE_COUNT,
    FOUR_POST_HEAVE_START_S,
    FOUR_POST_LEGACY_ROLL_MAGNITUDE_RAD,
    FOUR_POST_POSE_STEP_S,
    FOUR_POST_ROLL_POSE_COUNT,
    FOUR_POST_ROLL_START_S,
    FOUR_POST_STOP_TIME_S,
    FourPostEvalSim,
    _normalize_four_post_report_config,
)
from _3_StandardSim._modelica_runner import ModelicaRunner
from _3_StandardSim.RampSteerEval.ramp_steer_eval_sim import RampSteerEvalSim
from _3_StandardSim.SteadyStateEval.steady_state_eval_sim import SteadyStateEvalSim
from _3_StandardSim.TransientEval.transient_eval_sim import TransientEvalSim


ROOT = Path(__file__).resolve().parents[1]
VEHICLE_ENTRYPOINT = "BobLib.Experiments.Standards.VehicleSim"
FOUR_POST_ENTRYPOINT = "BobLib.Experiments.Standards.FourPostSim"
STANDARD_CONFIGS = (
    Path("_3_StandardSim/RampSteerEval/ramp_steer_eval_config.yml"),
    Path("_3_StandardSim/SteadyStateEval/steady_state_eval_config.yml"),
    Path("_3_StandardSim/TransientEval/transient_eval_config.yml"),
    Path("_3_StandardSim/FourPostEval/four_post_eval_config.yml"),
)
STANDARD_ENTRYPOINTS = {
    Path("_3_StandardSim/RampSteerEval/ramp_steer_eval_config.yml"): VEHICLE_ENTRYPOINT,
    Path("_3_StandardSim/SteadyStateEval/steady_state_eval_config.yml"): VEHICLE_ENTRYPOINT,
    Path("_3_StandardSim/TransientEval/transient_eval_config.yml"): VEHICLE_ENTRYPOINT,
    Path("_3_StandardSim/FourPostEval/four_post_eval_config.yml"): FOUR_POST_ENTRYPOINT,
}


def _load_yaml(path: Path) -> dict[str, Any]:
    with (ROOT / path).open("r", encoding="utf-8") as f:
        data = yaml.safe_load(f)
    assert isinstance(data, dict)
    return data


def _four_post_model_text() -> str:
    return (
        ROOT / "_0_Utils/external/BobLib/BobLib/Experiments/Standards/Templates/FourPost/BaseFourPostSim.mo"
    ).read_text(encoding="utf-8")


def _four_post_table(name: str) -> list[tuple[float, float]]:
    match = re.search(
        rf"final parameter Real {re.escape(name)}\[:, 2\] = \[(.*?)\];",
        _four_post_model_text(),
        flags=re.S,
    )
    assert match is not None, name
    rows: list[tuple[float, float]] = []
    for raw_row in match.group(1).split(";"):
        cols = [float(part.strip()) for part in raw_row.split(",")]
        assert len(cols) == 2
        rows.append((cols[0], cols[1]))
    return rows


def test_standard_sim_configs_use_internal_numerical_jacobian() -> None:
    for rel_path in STANDARD_CONFIGS:
        simulation = _load_yaml(rel_path)["simulation"]
        assert "-jacobian=internalNumerical" in simulation.get("extra_args", []), rel_path


def test_standard_sim_configs_use_boblib_entrypoints() -> None:
    for rel_path, exec_name in STANDARD_ENTRYPOINTS.items():
        simulation = _load_yaml(rel_path)["simulation"]
        assert simulation.get("exec_name") == exec_name, rel_path


def test_bobsim_sources_do_not_reference_legacy_boblib_generation_layout() -> None:
    completed = subprocess.run(
        [
            "git",
            "ls-files",
            "--",
            ".",
            ":(exclude)_0_Utils/external/BobLib",
            ":(exclude)_0_Utils/external/BobLib/**",
        ],
        cwd=ROOT,
        check=True,
        stdout=subprocess.PIPE,
        text=True,
    )
    searchable_suffixes = {".md", ".mo", ".mos", ".py", ".toml", ".yaml", ".yml"}
    searchable_names = {"Dockerfile", "makefile"}
    legacy = "BobLib"
    resources = "Resources"
    vehicle_defn = "VehicleDefn"
    forbidden = (
        "BobLib" + "VehicleInterfaces",
        f"{legacy}.Standards",
        f"{legacy}/Standards",
        f"{legacy}/Generation",
        f"{legacy}.{resources}.{vehicle_defn}",
        f"{legacy}/{legacy}/{resources}/{vehicle_defn}",
    )

    offenders: list[str] = []
    for rel in completed.stdout.splitlines():
        path = ROOT / rel
        if path.suffix not in searchable_suffixes and path.name not in searchable_names:
            continue
        text = path.read_text(encoding="utf-8", errors="ignore")
        for token in forbidden:
            if token in text:
                offenders.append(f"{rel}: {token}")

    assert not offenders


def test_report_outputs_stay_under_standard_generated_results() -> None:
    for rel_path in STANDARD_CONFIGS:
        report = _load_yaml(rel_path).get("report", {})
        assert isinstance(report, dict)
        for key in ("output_path", "metrics_csv_path"):
            if key not in report:
                continue
            path = Path(str(report[key]))
            assert not path.is_absolute(), f"{rel_path}: {key} should be repo-relative"
            assert path.parts[:2] == ("_3_StandardSim", "generated_results"), rel_path


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
        "app",
        "docker-build",
        "shell-standard",
        "standard-build",
        "standard-eval-ramp-steer",
        "standard-eval-steady-state",
        "regression-invariants",
        "regression-baseline",
        "standard-regression-four-post",
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


def test_four_post_model_tables_match_report_sampling_schedule() -> None:
    text = _four_post_model_text()
    assert "heaveCommandTable" not in text
    assert "heaveSource(table = heaveTable)" in text

    heave_table = dict(_four_post_table("heaveTable"))
    roll_table = dict(_four_post_table("rollTable"))
    fx_table = dict(_four_post_table("fxTable"))
    fy_table = dict(_four_post_table("fyTable"))

    assert max(heave_table) == pytest.approx(FOUR_POST_STOP_TIME_S)
    assert max(roll_table) == pytest.approx(FOUR_POST_STOP_TIME_S)
    assert max(fx_table) == pytest.approx(FOUR_POST_STOP_TIME_S)
    assert max(fy_table) == pytest.approx(FOUR_POST_STOP_TIME_S)

    for time_s in range(int(FOUR_POST_HEAVE_END_S), int(FOUR_POST_STOP_TIME_S) + 1):
        assert heave_table[float(time_s)] == pytest.approx(0.0)
    for time_s in range(0, int(FOUR_POST_ROLL_START_S)):
        assert roll_table[float(time_s)] == pytest.approx(0.0)

    heave_sample_times = [
        FOUR_POST_HEAVE_START_S + FOUR_POST_POSE_STEP_S * index + 4.0 for index in range(FOUR_POST_HEAVE_POSE_COUNT)
    ]
    roll_sample_times = [
        FOUR_POST_ROLL_START_S + FOUR_POST_POSE_STEP_S * index + 4.0 for index in range(FOUR_POST_ROLL_POSE_COUNT)
    ]
    assert [heave_table[time_s] for time_s in heave_sample_times] == pytest.approx(
        [-1.0, -0.8, -0.6, -0.4, -0.2, 0.0, 0.2, 0.4, 0.6, 0.8, 1.0]
    )
    assert [roll_table[time_s] for time_s in roll_sample_times] == pytest.approx(
        [-1.0, -0.8, -0.6, -0.4, -0.2, 0.0, 0.2, 0.4, 0.6, 0.8, 1.0]
    )

    heave_force_peak_times = [
        FOUR_POST_HEAVE_START_S + FOUR_POST_POSE_STEP_S * index + 1.0 for index in range(FOUR_POST_HEAVE_POSE_COUNT)
    ]
    roll_force_peak_times = [
        FOUR_POST_ROLL_START_S + FOUR_POST_POSE_STEP_S * index + 1.0 for index in range(FOUR_POST_ROLL_POSE_COUNT)
    ]
    assert [fx_table[time_s] for time_s in heave_force_peak_times] == pytest.approx([1.0] * 11)
    assert [fy_table[time_s] for time_s in roll_force_peak_times] == pytest.approx([1.0] * 11)


def test_four_post_report_uses_jacking_antiroll_plot_without_raw_appendix() -> None:
    for rel_path in (
        Path("_3_StandardSim/FourPostEval/four_post_eval_config.yml"),
        Path("_5_App/sim_configs/_defaults/four-post.yml"),
    ):
        config = _load_yaml(rel_path)
        assert config["report"]["raw_time_series_appendix"] is False

        jacking_roll = config["plots"]["jacking_roll"]
        assert jacking_roll["title"] == "Geometric Anti-Roll vs Roll"
        assert [subplot["x"]["key"] for subplot in jacking_roll["subplots"]] == [
            "fr_jacking_vs_roll_x",
            "rr_jacking_vs_roll_x",
        ]
        assert [subplot["y"]["key"] for subplot in jacking_roll["subplots"]] == [
            "fr_anti_vs_roll",
            "rr_anti_vs_roll",
        ]
        fbrc_roll = config["plots"]["fbrc_roll"]
        assert [subplot["y"]["key"] for subplot in fbrc_roll["subplots"]] == [
            "fr_fbrc_height_vs_roll",
            "rr_fbrc_height_vs_roll",
        ]


def test_four_post_defaults_fail_if_a_roll_pulse_unloads_a_contact_patch() -> None:
    for rel_path in (
        Path("_3_StandardSim/FourPostEval/four_post_eval_config.yml"),
        Path("_5_App/sim_configs/_defaults/four-post.yml"),
    ):
        config = _load_yaml(rel_path)
        assert config["procedure"]["rollMagnitude"] == pytest.approx(FOUR_POST_DEFAULT_ROLL_MAGNITUDE_RAD)
        assert config["validation"]["min_contact_fz_n"] == pytest.approx(1.0)
        assert config["validation"]["fail_on_contact_loss"] is True


def test_four_post_report_normalizer_disables_raw_appendix_for_legacy_app_data_config() -> None:
    config = {
        "report": {"enabled": True},
        "procedure": {"rollMagnitude": FOUR_POST_LEGACY_ROLL_MAGNITUDE_RAD},
        "plots": {
            "jacking_roll": {
                "title": "Anti-Roll Geometry Delta vs Roll",
                "subplots": [
                    {
                        "x": {"key": "lltd_vs_roll_x", "label": "Roll (deg)"},
                        "y": {
                            "key": "lltd_antiroll_geometry_delta_vs_roll",
                            "label": "LLTD Delta",
                        },
                    },
                    {
                        "x": {"key": "lltd_vs_roll_x", "label": "Roll (deg)"},
                        "y": {
                            "key": "lltd_antiroll_geometry_delta_vs_roll",
                            "label": "LLTD Delta",
                        },
                    },
                ],
            }
        },
    }

    normalized = _normalize_four_post_report_config(config)
    jacking_roll = normalized["plots"]["jacking_roll"]
    fbrc_roll = normalized["plots"]["fbrc_roll"]

    assert normalized["report"]["raw_time_series_appendix"] is False
    assert normalized["procedure"]["rollMagnitude"] == pytest.approx(FOUR_POST_DEFAULT_ROLL_MAGNITUDE_RAD)
    assert jacking_roll["title"] == "Geometric Anti-Roll vs Roll"
    assert [subplot["x"]["key"] for subplot in jacking_roll["subplots"]] == [
        "fr_jacking_vs_roll_x",
        "rr_jacking_vs_roll_x",
    ]
    assert [subplot["y"]["key"] for subplot in jacking_roll["subplots"]] == [
        "fr_anti_vs_roll",
        "rr_anti_vs_roll",
    ]
    assert [subplot["y"]["key"] for subplot in fbrc_roll["subplots"]] == [
        "fr_fbrc_height_vs_roll",
        "rr_fbrc_height_vs_roll",
    ]


def test_four_post_eval_passes_static_balanced_spring_free_lengths(
    tmp_path: Path,
) -> None:
    config = _load_yaml(Path("_3_StandardSim/FourPostEval/four_post_eval_config.yml"))
    metrics_path = tmp_path / "four_post_metrics.csv"
    metrics_path.write_text(
        "metric,value\nstatic_motion_ratio_front,1.0053063275855492\nstatic_motion_ratio_rear,1.2386785254222528\n",
        encoding="utf-8",
    )
    config["report"]["metrics_csv_path"] = str(metrics_path)

    overrides = FourPostEvalSim(config).build_model_setup_overrides()

    suspension_cfg = config["model_overrides"]["suspension"]
    assert suspension_cfg["static_balance_iterations"] == 4
    assert suspension_cfg["static_balance_convergence_n"] == pytest.approx(0.01)
    assert "motion_ratio" not in suspension_cfg["front"]
    assert "motion_ratio" not in suspension_cfg["rear"]
    assert overrides["pVehicle.pFrAxleDW.springFreeLength"] == pytest.approx(0.199700878416)
    assert overrides["pVehicle.pRrAxleDW.springFreeLength"] == pytest.approx(0.263423049137)


def test_signal_plots_filter_implausible_numeric_spikes() -> None:
    result = {"series": {"x": np.array([0.0, 1.0, 2.0]), "y": np.array([1.0, 1e292, 3.0])}}
    item = SignalPlot().get_xy(result, {"x": {"key": "x"}, "y": {"key": "y"}})[0]

    np.testing.assert_allclose(item["x"], np.array([0.0, 2.0]))
    np.testing.assert_allclose(item["y"], np.array([1.0, 3.0]))


def test_raw_time_series_appendix_filters_implausible_numeric_spikes(
    tmp_path: Path,
) -> None:
    path = tmp_path / "result.csv"
    path.write_text("time,good,bad\n0,1,2\n1,3,1e292\n2,4,5\n", encoding="utf-8")

    frame, time_column, signals = _raw_time_series_frame(path, max_points=100)

    assert time_column == "time"
    assert signals == ["good", "bad"]
    assert np.isnan(frame.loc[1, "bad"])


def test_standard_sens_spring_package_balances_free_length_from_rate() -> None:
    config = _load_yaml(Path("_4_OptSim/StandardSens/configs/_doe_config.yaml"))
    spring_variables = [
        variable
        for variable in config["variables"]
        if variable["path"] in {"front.actuation.spring_rate_n_per_m", "rear.actuation.spring_rate_n_per_m"}
    ]

    assert len(spring_variables) == 2
    for variable in spring_variables:
        free_length_targets = [target for target in variable["targets"] if target["param"] == "springFreeLength"]
        assert len(free_length_targets) == 1
        target = free_length_targets[0]
        assert target["operation"] == "static_balance_free_length"
        assert "range" not in target
        assert "motion_ratio" not in target
        assert target["axle"] in {"front", "rear"}


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


def test_ramp_steer_eval_uses_open_loop_ramp_mode() -> None:
    config = _load_yaml(Path("_3_StandardSim/RampSteerEval/ramp_steer_eval_config.yml"))

    sim = RampSteerEvalSim.__new__(RampSteerEvalSim)
    sim.config = config
    sim.start_time = float(config["simulation"].get("start_time", 0.0))
    sim.stop_time = float(config["simulation"].get("stop_time", 45.0))
    cases = sim.build_cases()

    assert cases
    assert {case.get("useMode", 0) for case in cases} == {0}
    assert {case["_mode"] for case in cases} == {"open_loop_ramp_steer"}
    assert {case["targetVel"] for case in cases} == {float(vel) for vel in config["sweep"]["testVels"]}


def test_modelica_runner_maps_standard_sim_shorthand_to_changeable_parameters(
    tmp_path: Path,
) -> None:
    runner = ModelicaRunner.__new__(ModelicaRunner)
    override_path = tmp_path / "case.override"

    runner._write_override_file(
        override_path,
        {
            "_testVel": 12.5,
            "targetVel": 12.5,
            "targetAy": 18.0,
            "useMode": 0,
            "steerStart": 2.0,
            "handwheelRampRate": 0.06,
            "velGain": 100.0,
            "velTi": 2.0,
            "startTime": 0.0,
            "stopTime": 45.0,
        },
    )

    lines = set(override_path.read_text(encoding="utf-8").splitlines())

    assert "initialVel=12.5" in lines
    assert "vcu.targetVel=12.5" not in lines
    assert "vcu.targetAy=18.0" in lines
    assert "vcu.useMode=0" in lines
    assert "vcu.steerStart=2.0" in lines
    assert "vcu.handwheelRampRate=0.06" in lines
    assert "vcu.velGain=100.0" in lines
    assert "vcu.velTi=2.0" in lines
    assert not any(line.startswith("_") for line in lines)
    assert not any(line.startswith("startTime=") for line in lines)
    assert not any(line.startswith("stopTime=") for line in lines)


def test_steady_state_eval_uses_closed_loop_steady_mode() -> None:
    config = _load_yaml(Path("_3_StandardSim/SteadyStateEval/steady_state_eval_config.yml"))

    sim = SteadyStateEvalSim.__new__(SteadyStateEvalSim)
    sim.config = config
    sim.start_time = float(config["simulation"].get("start_time", 0.0))
    sim.stop_time = float(config["simulation"].get("stop_time", 35.0))
    cases = sim.build_cases()

    assert cases
    assert {case["useMode"] for case in cases} == {3}
    assert {case["_mode"] for case in cases} == {"closed_loop_steady_ay"}
    cases_by_velocity = {
        test_vel: [case["targetAy"] for case in cases if case["_testVel"] == test_vel]
        for test_vel in config["sweep"]["testVels"]
    }
    for test_vel, cap in config["sweep"]["maxAyByVelocity"].items():
        assert max(cases_by_velocity[test_vel]) <= cap
    assert len(cases) < len(config["sweep"]["testVels"]) * len(config["sweep"]["targetAys"])
    assert max(config["sweep"]["targetAys"]) >= 18.0
