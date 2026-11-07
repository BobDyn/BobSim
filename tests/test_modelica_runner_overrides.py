"""The runner's override contract, checked against a small hand-written init XML.

An OpenModelica executable that cannot apply an override writes one run.log
warning and still exits 0. These tests use a fake executable, so no build is needed.
"""

from __future__ import annotations

from concurrent.futures import ThreadPoolExecutor
import hashlib
import json
from pathlib import Path
import pickle
import re
import subprocess
from typing import Any

import pytest
import yaml

from simulations.response.mbd import _modelica_runner
from simulations.response.mbd._modelica_runner import (
    ModelicaRunner,
    OverrideError,
    load_init_variables,
    plan_overrides,
)
from simulations.response.mbd.modelica_overrides import read_override_log

EXEC_NAME = "Model"


def _scalar(
    name: str,
    start: str | None,
    *,
    kind: str = "Real",
    causality: str = "parameter",
    changeable: bool = True,
) -> str:
    start_attr = "" if start is None else f' start="{start}"'
    return (
        "  <ScalarVariable\n"
        f'    name = "{name}"\n'
        '    variability = "parameter" isDiscrete = "true"\n'
        f'    causality = "{causality}" isValueChangeable = "{str(changeable).lower()}"\n'
        '    alias = "noAlias">\n'
        f'    <{kind}{start_attr} fixed="true" useNominal="false" />\n'
        "  </ScalarVariable>\n"
    )


# The layout copies an OpenModelica 1.27.1 FourPostSim_init.xml: the start value is on the child element.
INIT_XML = (
    '<?xml version = "1.0" encoding="UTF-8"?>\n'
    '<fmiModelDescription modelName = "Model">\n'
    "  <ModelVariables>\n"
    + _scalar("initialVel", "15.0")
    + _scalar("driver.targetAy", "0.0")
    + _scalar("driver.useMode", "0", kind="Integer")
    + _scalar("driver.steerStart", "1.0")
    + _scalar("driver.velGain", "100.0")
    + _scalar("enableLinearityTermination", "true", kind="Boolean")
    + _scalar("pVehicle.chassis.frontAxle.stabilizer.barRate", "257.62")
    + _scalar("pVehicle.chassis.frontAxle.actuation.springFreeLength", "0.1997")
    + _scalar("frAxleDW.pAxle.actuation.springFreeLength", None, causality="calculatedParameter", changeable=False)
    + _scalar("frAxleDW.pAxle.stabilizer.barRate", "257.62", causality="calculatedParameter", changeable=False)
    + _scalar("pVehicle.pNoStart.value", None)
    + "  </ModelVariables>\n"
    "</fmiModelDescription>\n"
)

REFUSED_CALCULATED = (
    "LOG_STDOUT        | warning | It is not possible to override the following quantity: "
    "pVehicle.chassis.frontAxle.stabilizer.barRate\n"
    "|                 | |       | It seems to be structural, final, protected or evaluated "
    "or has a non-constant binding.\n"
)
REFUSED_UNKNOWN = (
    "LOG_STDOUT        | warning | simulation_input_xml.c: override variable name not found "
    "in model: pVehicle.chassis.frontAxle.stabilizer.barRate\n"
)


class FakeExecutable:
    """Stand in for subprocess.run. Echo each override the way LOG_SOLVER does."""

    def __init__(self, extra_log: str = "", echo: bool = True, echo_value: str | None = None):
        self.calls: list[list[str]] = []
        self.extra_log = extra_log
        self.echo = echo
        self.echo_value = echo_value

    def __call__(self, cmd: list[str], **_: Any) -> subprocess.CompletedProcess:
        self.calls.append(list(cmd))
        args = dict(arg[1:].split("=", 1) for arg in cmd[1:] if "=" in arg)
        lines = Path(args["overrideFile"]).read_text(encoding="utf-8").splitlines()
        log = f"LOG_SOLVER        | info    | read override values from file: {args['overrideFile']}\n"
        log += "LOG_SOLVER        | info    | -override=[not given]\n"
        if self.echo:
            for line in lines:
                name, value = line.split("=", 1)
                shown = value if self.echo_value is None else self.echo_value
                log += f"LOG_SOLVER        | info    | override {name} = {shown}\n"
        log += "LOG_SOLVER        | info    | override done!\n"
        log += self.extra_log
        log += "LOG_SUCCESS       | info    | The simulation finished successfully.\n"
        Path(args["r"]).write_text("time,sig\n0.0,1.0\n1.0,2.0\n", encoding="utf-8")
        return subprocess.CompletedProcess(cmd, 0, stdout=log)


def _never(*_: Any, **__: Any) -> Any:
    raise AssertionError("A simulation process started before every override was planned.")


@pytest.fixture
def build_dir(tmp_path: Path) -> Path:
    build = tmp_path / "build"
    build.mkdir()
    (build / EXEC_NAME).write_text("not a real executable", encoding="utf-8")
    (build / f"{EXEC_NAME}_init.xml").write_text(INIT_XML, encoding="utf-8")
    return build


@pytest.fixture
def runner(build_dir: Path) -> ModelicaRunner:
    return ModelicaRunner(build_dir=build_dir, exec_name=EXEC_NAME, simulation={"log_level": "LOG_STATS"})


def _reasons(error: OverrideError) -> list[tuple[str, str]]:
    return [(rejection.key, rejection.reason) for rejection in error.rejections]


def _manifests(build_dir: Path) -> list[dict[str, Any]]:
    return [json.loads(path.read_text(encoding="utf-8")) for path in build_dir.glob("results/run_*/manifest.json")]


def test_load_init_variables_reads_the_start_value_from_the_child_element(build_dir: Path) -> None:
    variables = load_init_variables(build_dir / f"{EXEC_NAME}_init.xml")

    free_length = variables["pVehicle.chassis.frontAxle.actuation.springFreeLength"]
    assert free_length.start == "0.1997"
    assert free_length.causality == "parameter"
    assert free_length.variability == "parameter"
    assert free_length.changeable is True

    calculated = variables["frAxleDW.pAxle.actuation.springFreeLength"]
    assert calculated.start is None
    assert calculated.causality == "calculatedParameter"
    assert calculated.changeable is False
    assert variables["driver.useMode"].start == "0"
    assert variables["enableLinearityTermination"].start == "true"
    assert [variables[name].kind for name in ("driver.velGain", "driver.useMode", "enableLinearityTermination")] == [
        "Real",
        "Integer",
        "Boolean",
    ]


@pytest.mark.parametrize("parallel", [False, True])
def test_an_unknown_name_fails_before_any_process_starts(
    runner: ModelicaRunner, build_dir: Path, monkeypatch: pytest.MonkeyPatch, parallel: bool
) -> None:
    monkeypatch.setattr(_modelica_runner.subprocess, "run", _never)
    monkeypatch.setattr(_modelica_runner.subprocess, "Popen", _never)
    monkeypatch.setattr(_modelica_runner, "ProcessPoolExecutor", _never)
    good = {"targetVel": 12.0, "_case_label": "good"}
    typo = {"targetVel": 12.0, "velGian": 90.0, "_case_label": "typo"}

    with pytest.raises(OverrideError) as excinfo:
        runner.run(signals=["sig"], mode="last", cases=[good, typo], execution={"parallel": parallel})

    assert _reasons(excinfo.value) == [("velGian", "unknown_name")]
    assert excinfo.value.rejections[0].detail.startswith("case 2 (typo): ")
    assert "velGian" in str(excinfo.value)
    assert not (build_dir / "results").exists()


def test_one_error_lists_every_rejection_of_every_case(runner: ModelicaRunner) -> None:
    cases = [
        {"velGian": 1.0, "_case_label": "first"},
        {"pVehicle.pNoStart.value": 2.0, "frAxleDW.pAxle.actuation.springFreeLength": 0.25, "_case_label": "second"},
    ]

    with pytest.raises(OverrideError) as excinfo:
        runner.plan_cases(cases)

    assert _reasons(excinfo.value) == [
        ("velGian", "unknown_name"),
        ("pVehicle.pNoStart.value", "no_start_value"),
        ("frAxleDW.pAxle.actuation.springFreeLength", "not_changeable"),
    ]
    assert [rejection.detail.split(":")[0] for rejection in excinfo.value.rejections] == [
        "case 1 (first)",
        "case 2 (second)",
        "case 2 (second)",
    ]


@pytest.mark.parametrize(
    ("name", "value"),
    [
        ("frAxleDW.pAxle.actuation.springFreeLength", 300.0),
        ("frAxleDW.pAxle.stabilizer.barRate", 300.0),
        ("frAxleDW.pAxle.stabilizer.barRate", 257.62),
    ],
    ids=["no-start", "with-start", "equal-to-start"],
)
def test_a_calculated_parameter_is_not_changeable(build_dir: Path, name: str, value: float) -> None:
    variables = load_init_variables(build_dir / f"{EXEC_NAME}_init.xml")

    with pytest.raises(OverrideError) as excinfo:
        plan_overrides({name: value}, variables)

    rejection = excinfo.value.rejections[0]
    assert (rejection.key, rejection.modelica_name, rejection.reason) == (name, name, "not_changeable")
    assert rejection.requested == value
    assert "recompile" in rejection.detail


@pytest.mark.parametrize(
    ("key", "value"),
    [
        ("velGain", "fast"),
        ("velGain", True),
        ("velGain", float("nan")),
        ("useMode", 1.5),
        ("useMode", True),
        ("enableLinearityTermination", 0.0),
        ("enableLinearityTermination", "yes"),
    ],
    ids=["real-text", "real-bool", "real-nan", "integer-fraction", "integer-bool", "boolean-number", "boolean-text"],
)
def test_a_value_of_the_wrong_kind_is_rejected(build_dir: Path, key: str, value: object) -> None:
    variables = load_init_variables(build_dir / f"{EXEC_NAME}_init.xml")

    with pytest.raises(OverrideError) as excinfo:
        plan_overrides({key: value}, variables)

    assert _reasons(excinfo.value) == [(key, "invalid_value")]


def test_a_value_of_the_right_kind_is_written_in_that_kind(build_dir: Path) -> None:
    variables = load_init_variables(build_dir / f"{EXEC_NAME}_init.xml")

    plan = plan_overrides({"useMode": 2.0, "enableLinearityTermination": "False", "velGain": "120"}, variables)

    assert plan.written == {"driver.useMode": "2", "enableLinearityTermination": "false", "driver.velGain": "120"}


def test_a_value_equal_to_the_compiled_start_is_recorded_and_not_written(build_dir: Path) -> None:
    variables = load_init_variables(build_dir / f"{EXEC_NAME}_init.xml")

    plan = plan_overrides(
        {
            "pVehicle.chassis.frontAxle.actuation.springFreeLength": 0.1997,
            "useMode": 0,
            "enableLinearityTermination": True,
            "pVehicle.chassis.frontAxle.stabilizer.barRate": 390.0,
        },
        variables,
    )

    assert plan.already_compiled == {
        "pVehicle.chassis.frontAxle.actuation.springFreeLength": "0.1997",
        "driver.useMode": "0",
        "enableLinearityTermination": "true",
    }
    assert plan.written == {"pVehicle.chassis.frontAxle.stabilizer.barRate": "390.0"}
    assert plan.file_text() == "pVehicle.chassis.frontAxle.stabilizer.barRate=390.0\n"


def test_aliases_that_disagree_are_rejected_and_aliases_that_agree_write_one_line(build_dir: Path) -> None:
    variables = load_init_variables(build_dir / f"{EXEC_NAME}_init.xml")

    plan = plan_overrides({"initialVel": 12.5, "targetVel": 12.5}, variables)
    assert plan.file_text() == "initialVel=12.5\n"
    assert plan.requested == {"initialVel": 12.5, "targetVel": 12.5}

    with pytest.raises(OverrideError) as excinfo:
        plan_overrides({"initialVel": 12.5, "targetVel": 20.0}, variables)

    rejection = excinfo.value.rejections[0]
    assert (rejection.key, rejection.modelica_name, rejection.reason) == (
        "targetVel",
        "initialVel",
        "conflicting_aliases",
    )
    assert "initialVel" in rejection.detail and "12.5" in rejection.detail


def test_runner_flags_and_metadata_are_not_overrides(build_dir: Path) -> None:
    variables = load_init_variables(build_dir / f"{EXEC_NAME}_init.xml")

    plan = plan_overrides(
        {"startTime": 0.0, "stopTime": 45.0, "stepSize": 0.5, "timeout_s": 60.0, "_mode": "x", "steerStart": 2.0},
        variables,
    )

    assert plan.requested == {"steerStart": 2.0}
    assert plan.file_text() == "driver.steerStart=2.0\n"


def test_a_missing_init_xml_is_an_override_error(runner: ModelicaRunner, build_dir: Path) -> None:
    (build_dir / f"{EXEC_NAME}_init.xml").unlink()

    with pytest.raises(OverrideError) as excinfo:
        runner.plan_cases([{"targetVel": 12.0}])

    assert [rejection.reason for rejection in excinfo.value.rejections] == ["missing_init_xml"]


def test_a_build_without_an_init_xml_fails_when_the_runner_is_made(build_dir: Path) -> None:
    (build_dir / f"{EXEC_NAME}_init.xml").unlink()

    with pytest.raises(OverrideError) as excinfo:
        ModelicaRunner(build_dir=build_dir, exec_name=EXEC_NAME, simulation={})

    assert [rejection.reason for rejection in excinfo.value.rejections] == ["missing_init_xml"]


def test_the_manifest_records_what_was_requested_written_and_read_back(
    runner: ModelicaRunner, build_dir: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    fake = FakeExecutable()
    monkeypatch.setattr(_modelica_runner.subprocess, "run", fake)

    results = runner.run(
        signals=["sig"],
        mode="last",
        cases=[{"targetVel": 12.0, "targetAy": 4.0, "pVehicle.chassis.frontAxle.actuation.springFreeLength": 0.1997}],
        execution={"parallel": False},
    )

    assert results[0]["_status"] == "ok"
    (manifest,) = _manifests(build_dir)
    overrides = manifest["overrides"]
    override_file = Path(manifest["override_file"])
    assert overrides["requested"] == {
        "targetVel": 12.0,
        "targetAy": 4.0,
        "pVehicle.chassis.frontAxle.actuation.springFreeLength": 0.1997,
    }
    assert overrides["written"] == {"initialVel": "12.0", "driver.targetAy": "4.0"}
    assert overrides["already_compiled"] == {"pVehicle.chassis.frontAxle.actuation.springFreeLength": "0.1997"}
    assert overrides["rejected"] == []
    assert overrides["readback"] == {
        "initialVel": {"requested": "12.0", "observed": "12.0", "status": "match"},
        "driver.targetAy": {"requested": "4.0", "observed": "4.0", "status": "match"},
    }
    assert overrides["file_sha256"] == hashlib.sha256(override_file.read_bytes()).hexdigest()
    assert manifest["argv"] == fake.calls[0]


@pytest.mark.parametrize("refusal", [REFUSED_CALCULATED, REFUSED_UNKNOWN], ids=["calculated", "unknown"])
def test_a_run_log_refusal_fails_with_not_applied_and_keeps_the_run_dir(
    runner: ModelicaRunner, build_dir: Path, monkeypatch: pytest.MonkeyPatch, refusal: str
) -> None:
    monkeypatch.setattr(_modelica_runner.subprocess, "run", FakeExecutable(extra_log=refusal))

    with pytest.raises(OverrideError) as excinfo:
        runner.run(
            signals=["sig"],
            mode="last",
            cases=[{"pVehicle.chassis.frontAxle.stabilizer.barRate": 390.0}],
            execution={"parallel": False, "cleanup": True},
        )

    rejection = excinfo.value.rejections[0]
    assert (rejection.key, rejection.modelica_name, rejection.reason) == (
        "pVehicle.chassis.frontAxle.stabilizer.barRate",
        "pVehicle.chassis.frontAxle.stabilizer.barRate",
        "not_applied",
    )
    (manifest,) = _manifests(build_dir)
    assert Path(manifest["run_dir"]).is_dir()
    assert manifest["status"] == "failed"
    assert [item["reason"] for item in manifest["overrides"]["rejected"]] == ["not_applied"]


def test_not_applied_stops_a_parallel_run_instead_of_failing_one_case(
    runner: ModelicaRunner, monkeypatch: pytest.MonkeyPatch
) -> None:
    monkeypatch.setattr(_modelica_runner.subprocess, "run", FakeExecutable(extra_log=REFUSED_CALCULATED))
    monkeypatch.setattr(_modelica_runner, "ProcessPoolExecutor", ThreadPoolExecutor)

    with pytest.raises(OverrideError) as excinfo:
        runner.run(
            signals=["sig"],
            mode="last",
            cases=[
                {"pVehicle.chassis.frontAxle.stabilizer.barRate": 390.0},
                {"pVehicle.chassis.frontAxle.stabilizer.barRate": 400.0},
            ],
            execution={"parallel": True, "max_workers": 1},
        )

    assert {rejection.reason for rejection in excinfo.value.rejections} == {"not_applied"}


def test_a_readback_that_differs_from_the_request_is_not_applied(
    runner: ModelicaRunner, monkeypatch: pytest.MonkeyPatch
) -> None:
    monkeypatch.setattr(_modelica_runner.subprocess, "run", FakeExecutable(echo_value="1.0"))

    with pytest.raises(OverrideError) as excinfo:
        runner.run(
            signals=["sig"],
            mode="last",
            cases=[{"pVehicle.chassis.frontAxle.stabilizer.barRate": 390.0}],
            execution={"parallel": False},
        )

    rejection = excinfo.value.rejections[0]
    assert rejection.reason == "not_applied"
    assert "1.0" in rejection.detail and "390.0" in rejection.detail


def test_a_missing_readback_line_is_not_applied(
    runner: ModelicaRunner, build_dir: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    monkeypatch.setattr(_modelica_runner.subprocess, "run", FakeExecutable(echo=False))

    with pytest.raises(OverrideError) as excinfo:
        runner.run(
            signals=["sig"],
            mode="last",
            cases=[{"pVehicle.chassis.frontAxle.stabilizer.barRate": 390.0}],
            execution={"parallel": False},
        )

    assert _reasons(excinfo.value) == [("pVehicle.chassis.frontAxle.stabilizer.barRate", "not_applied")]
    (manifest,) = _manifests(build_dir)
    assert manifest["status"] == "failed"
    assert manifest["overrides"]["readback"] == {
        "pVehicle.chassis.frontAxle.stabilizer.barRate": {
            "requested": "390.0",
            "observed": None,
            "status": "unavailable",
        },
    }


def test_read_override_log_parses_the_lines_of_a_real_four_post_run() -> None:
    # Lines copied from a FourPostSim run.log (OpenModelica 1.27.1, LOG_SOLVER on).
    log = (
        "LOG_SOLVER        | info    | read override values from file: /tmp/run/overrides.txt\n"
        "LOG_SOLVER        | info    | -override=[not given]\n"
        "LOG_SOLVER        | info    | -overrideFile=heaveMagnitude=0.03,pFrStabar.barRate=390.0\n"
        "LOG_SOLVER        | info    | override heaveMagnitude = 0.03\n"
        "LOG_SOLVER        | info    | override pFrStabar.barRate = 390.0\n"
        "LOG_SOLVER        | info    | override done!\n"
        + REFUSED_CALCULATED.replace(
            "pVehicle.chassis.frontAxle.stabilizer.barRate", "frAxleDW.pAxle.actuation.springFreeLength"
        )
        + REFUSED_UNKNOWN.replace("pVehicle.chassis.frontAxle.stabilizer.barRate", "notARealName.x")
    )

    parsed = read_override_log(log)

    assert parsed.applied == {"heaveMagnitude": "0.03", "pFrStabar.barRate": "390.0"}
    assert set(parsed.refused) == {"frAxleDW.pAxle.actuation.springFreeLength", "notARealName.x"}


def test_the_command_always_asks_for_the_override_readback_stream(build_dir: Path) -> None:
    def log_flag(simulation: dict[str, Any]) -> list[str]:
        runner = ModelicaRunner(build_dir=build_dir, exec_name=EXEC_NAME, simulation=simulation)
        command = runner._build_command(build_dir / "overrides.txt", build_dir / "result.csv")
        return [arg for arg in command if arg.startswith("-lv=")]

    assert log_flag({"log_level": "LOG_STATS"}) == ["-lv=LOG_STATS,LOG_SOLVER"]
    assert log_flag({}) == ["-lv=LOG_SOLVER"]
    four_post = "LOG_STATS,LOG_SOLVER,LOG_INIT,LOG_STDOUT,LOG_ASSERT"
    assert log_flag({"log_level": four_post}) == [f"-lv={four_post}"]
    # A second -lv would replace the first and switch the readback off.
    assert log_flag({"log_level": "LOG_STATS", "extra_args": ["-lv=LOG_INIT,LOG_STATS"]}) == [
        "-lv=LOG_STATS,LOG_INIT,LOG_SOLVER"
    ]


def test_an_override_error_survives_the_process_pool() -> None:
    with pytest.raises(OverrideError) as excinfo:
        plan_overrides({"velGian": 1.0}, {})

    copy = pickle.loads(pickle.dumps(excinfo.value))

    assert copy.rejections == excinfo.value.rejections
    assert str(copy) == str(excinfo.value)
    assert re.search(r"velGian.*unknown_name", str(copy))


def test_a_typo_in_ramp_steer_init_parameters_fails_before_any_case_runs(
    build_dir: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    from simulations.response.mbd.ramp_steer.ramp_steer_eval_sim import RampSteerEvalSim

    monkeypatch.setattr(_modelica_runner.subprocess, "run", _never)
    monkeypatch.setattr(_modelica_runner, "ProcessPoolExecutor", _never)
    config = {
        "simulation": {
            "build_dir": str(build_dir),
            "exec_name": EXEC_NAME,
            "start_time": 0.0,
            "stop_time": 10.0,
            "init_parameters": {"steerStart": 2.0, "velGian": 100.0},
        },
        "sweep": {"testVels": [10.0, 15.0], "maxAy": 10.0},
        "execution": {"parallel": True},
    }

    with pytest.raises(OverrideError) as excinfo:
        RampSteerEvalSim(config).run()

    assert _reasons(excinfo.value) == [("velGian", "unknown_name"), ("velGian", "unknown_name")]


def test_transient_step_cases_set_the_driver_step_duration(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    from simulations.response.mbd.transient.transient_eval_sim import TransientEvalSim

    # BobLib StandardDriver has its own stepDuration. frRampSteerDuration no longer exists.
    init_xml = tmp_path / "VehicleSim_init.xml"
    init_xml.write_text(
        "<fmiModelDescription><ModelVariables>\n"
        + "".join(
            _scalar(name, "-1.0")
            for name in (
                "initialVel",
                "driver.useMode",
                "driver.steerStart",
                "driver.frRampSteerHeight",
                "driver.stepDuration",
                "driver.steerAmp",
                "driver.steerFreq",
            )
        )
        + "</ModelVariables></fmiModelDescription>",
        encoding="utf-8",
    )
    variables = load_init_variables(init_xml)
    monkeypatch.setattr(_modelica_runner.ModelicaRunner, "from_config", lambda config: None)
    config = yaml.safe_load(Path("simulations/response/mbd/transient/transient_eval_config.yml").read_text())

    cases, metadata = TransientEvalSim(config).build_cases()
    step_cases = [case for case, meta in zip(cases, metadata) if meta["mode"] == "step"]

    assert step_cases
    for case in cases:
        plan = plan_overrides(case, variables)
        assert "frRampSteerDuration" not in case
        if "stepDuration" in case:
            assert plan.modelica_names["stepDuration"] == "driver.stepDuration"
    assert {case["stepDuration"] for case in step_cases} == {config["test"]["stepDuration"]}


def test_the_removed_ramp_duration_name_fails_loudly(tmp_path: Path) -> None:
    init_xml = tmp_path / "VehicleSim_init.xml"
    init_xml.write_text(
        "<fmiModelDescription><ModelVariables>\n"
        + _scalar("driver.stepDuration", "0.001")
        + "</ModelVariables></fmiModelDescription>",
        encoding="utf-8",
    )

    with pytest.raises(OverrideError) as excinfo:
        plan_overrides({"frRampSteerDuration": 0.02}, load_init_variables(init_xml))
    assert _reasons(excinfo.value) == [("frRampSteerDuration", "unknown_name")]


def test_optsim_reads_the_init_xml_with_the_runner_loader(build_dir: Path) -> None:
    pytest.importorskip("scipy", reason="the OptSim pipeline package imports scipy")
    from optimization.response.pipeline import overrides

    init_xml = build_dir / f"{EXEC_NAME}_init.xml"
    parameters = overrides.load_init_parameters(init_xml)

    assert set(parameters) == set(load_init_variables(init_xml))
    bar_rate = parameters["pVehicle.chassis.frontAxle.stabilizer.barRate"]
    assert bar_rate == overrides.InitParameter(start=257.62, changeable=True)
    free_length = parameters["frAxleDW.pAxle.actuation.springFreeLength"]
    assert free_length == overrides.InitParameter(start=None, changeable=False)
    assert parameters["enableLinearityTermination"].start is None
