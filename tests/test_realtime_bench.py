from __future__ import annotations

import argparse
import json
from pathlib import Path
from types import SimpleNamespace
from typing import Any

import numpy as np
import pytest

from simulations.response.realtime import realtime_bench as bench


class VehicleStub:
    def model(self, dof):
        return SimpleNamespace(state_names=("x",), state_size=1)

    def initial_state(self, dof, speed):
        return np.zeros(1)


@pytest.mark.parametrize("dt,stop", [(0, 1), (-1, 1), (0.1, 0), (float("nan"), 1), (1, float("inf"))])
def test_invalid_times_are_rejected(dt, stop):
    with pytest.raises(ValueError):
        list(bench._steps(dt, stop))


def test_final_step_does_not_overshoot():
    steps = list(bench._steps(0.02, 0.05))
    assert [end - start for start, end in steps] == pytest.approx([0.02, 0.02, 0.01])
    assert steps[-1][1] == 0.05


@pytest.mark.parametrize("mode", ["failure", "nonfinite", "exception"])
def test_failed_dynpy_step_does_not_advance_time(monkeypatch, mode):
    calls = 0

    def solve(*args, **kwargs):
        nonlocal calls
        calls += 1
        if calls == 2:
            if mode == "exception":
                raise RuntimeError("solver crashed")
            return SimpleNamespace(success=mode == "nonfinite", message="solver failed",
                                   y=np.array([[float("nan")]]))
        return SimpleNamespace(success=True, message="", y=np.array([[1.0]]))

    monkeypatch.setattr(bench, "solve_ivp", solve)
    result = bench.bench_dyn_py(VehicleStub(), 3, dt_s=0.02, stop_s=0.05,
                               speed_mps=0, controls=bench._launch(0))
    assert result["completed"] is False
    assert result["steps"] == 1
    assert result["attempted_steps"] == 2
    assert result["simulated_s"] == 0.02
    assert result["final"] == {"x": 1.0}
    assert result["failure"]


@pytest.mark.parametrize("stage", ["initialization", "step", "readback", "success"])
def test_fmu_cleanup_and_completion(monkeypatch, tmp_path, stage):
    import fmpy
    import fmpy.fmi2

    calls: list[str] = []
    directories: list[Path] = []

    class Slave:
        def __init__(self, **kwargs):
            directories.append(Path(kwargs["unzipDirectory"]))

        def instantiate(self):
            calls.append("instantiate")

        def setupExperiment(self, **kwargs):
            pass

        def enterInitializationMode(self):
            pass

        def exitInitializationMode(self):
            if stage == "initialization":
                raise RuntimeError("initialization failed")

        def doStep(self, **kwargs):
            calls.append("step")
            if stage == "step":
                raise RuntimeError("step failed")
            assert kwargs["communicationStepSize"] <= 0.02

        def getReal(self, refs):
            if stage == "readback":
                raise RuntimeError("readback failed")
            return [1.0]

        def terminate(self):
            calls.append("terminate")

        def freeInstance(self):
            calls.append("free")

    description = SimpleNamespace(
        fmiVersion="2.0", guid="test", coSimulation=SimpleNamespace(modelIdentifier="test"),
        numberOfContinuousStates=1,
        modelVariables=[SimpleNamespace(name="velX", valueReference=1, type="Real", causality="output")],
    )
    monkeypatch.setattr(fmpy, "read_model_description", lambda path: description)
    monkeypatch.setattr(fmpy, "extract", lambda path, unzipdir: unzipdir)
    monkeypatch.setattr(fmpy.fmi2, "FMU2Slave", Slave)
    archive = tmp_path / "test.fmu"
    archive.write_bytes(b"test")
    result = bench.bench_fmu(archive, 0.02, 0.05)
    assert result["completed"] is (stage == "success")
    assert calls[-1] == "free"
    assert not directories[0].exists()
    assert ("terminate" in calls) is (stage != "initialization")
    assert result["simulated_s"] == (0.05 if stage in ("readback", "success") else 0)
    json.dumps(result, allow_nan=False)


def test_cli_retains_other_cases_and_exits_nonzero(monkeypatch, tmp_path):
    output = tmp_path / "results.json"
    vehicle = tmp_path / "vehicle.yml"
    vehicle.write_text("vehicle: {}")
    monkeypatch.setattr(bench, "_parse_args", lambda: argparse.Namespace(
        dt_s=0.02, stop_s=0.05, speed_mps=0, dof=[3], skip_fmu=True,
        vehicle=vehicle, fmu=Path("missing.fmu"), output=output, launch_torque_nm=0,
    ))
    monkeypatch.setattr(bench.Vehicle, "from_yaml", lambda path: VehicleStub())
    count = 0

    def run(*args, **kwargs) -> dict[str, Any]:
        nonlocal count
        count += 1
        if count == 1:
            raise RuntimeError("trim failed")
        return {"model": "test", "completed": True}

    monkeypatch.setattr(bench, "bench_dyn_py", run)
    with pytest.raises(SystemExit) as error:
        bench.main()
    assert error.value.code == 1
    data = json.loads(output.read_text())
    assert len(data["runs"]) == 2
    assert data["completed"] is False
    assert data["runs"][1]["completed"] is True


def test_partial_report_does_not_claim_complete(monkeypatch, tmp_path):
    output = tmp_path / "results.json"
    vehicle = tmp_path / "vehicle.yml"
    vehicle.write_text("vehicle: {}")
    monkeypatch.setattr(bench, "_parse_args", lambda: argparse.Namespace(
        dt_s=0.02, stop_s=0.05, speed_mps=0, dof=[3], skip_fmu=True,
        vehicle=vehicle, fmu=Path("missing.fmu"), output=output, launch_torque_nm=0,
    ))
    monkeypatch.setattr(bench.Vehicle, "from_yaml", lambda path: VehicleStub())
    count = 0

    def run(*args, **kwargs):
        nonlocal count
        count += 1
        if count == 2:
            raise KeyboardInterrupt
        return {"model": "test", "completed": True}

    monkeypatch.setattr(bench, "bench_dyn_py", run)
    with pytest.raises(KeyboardInterrupt):
        bench.main()
    data = json.loads(output.read_text())
    assert data["completed"] is False
    assert data["expected_cases"] == 2
    assert len(data["runs"]) == 1


def test_failed_export_cannot_reuse_stale_fmu(tmp_path):
    import subprocess

    root = Path(bench.repo_root())
    package = tmp_path / "BobLib"
    package.mkdir()
    (package / "package.mo").write_text("package BobLib end BobLib;")
    model = tmp_path / "VehicleSim.mo"
    model.write_text("model VehicleSim end VehicleSim;")
    output = tmp_path / "VehicleSim.fmu"
    output.write_bytes(b"stale archive")
    runner = tmp_path / "runner"
    runner.write_text("#!/bin/sh\nexec bash -c 'omc() { return 0; }; export -f omc; exec \"$@\"' _ \"$@\"\n")
    runner.chmod(0o755)
    result = subprocess.run([
        "make", "-B", "standard-build-fmu", f"RUN={runner.as_posix()}", f"WORKSPACE={tmp_path.as_posix()}",
        "VEHICLE_FMU=VehicleSim.fmu", f"VEHICLE_SIM_MODEL={model.as_posix()}",
        f"BOBLIB_PACKAGE_PATH={package.as_posix()}",
        f"BUILD_VEHICLE_FMU_MOS={model.as_posix()}",
    ], cwd=root, text=True, capture_output=True, timeout=10)
    assert result.returncode != 0
    assert not output.exists()


def test_fmu_compile_options_only_affect_initialization(tmp_path):
    import shutil
    import subprocess

    cmake = shutil.which("cmake")
    if cmake is None:
        pytest.skip("CMake is required to build the FMU")
    (tmp_path / "CMakeLists.txt").write_text(
        "cmake_minimum_required(VERSION 3.21)\n"
        "set(FMU_NAME VehicleSim)\nproject(check C)\n"
        "set(CMAKE_BUILD_TYPE Release)\n"
        "add_library(check VehicleSim_init_fmu.c runtime.c)\n"
    )
    for name in ("VehicleSim_init_fmu.c", "runtime.c"):
        (tmp_path / name).write_text("void test(void) {}\n")
    hook = Path(bench.repo_root()) / "simulations/response/mbd/fmu_compile_options.cmake"
    subprocess.run([
        cmake, "-S", str(tmp_path), "-B", str(tmp_path / "build"),
        f"-DCMAKE_TOOLCHAIN_FILE={hook.as_posix()}", "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON",
    ], check=True, capture_output=True, text=True, timeout=30)
    commands = json.loads((tmp_path / "build/compile_commands.json").read_text())
    flags = {Path(item["file"]).name: item["command"].split() for item in commands}
    assert flags["VehicleSim_init_fmu.c"].index("-O0") > flags["VehicleSim_init_fmu.c"].index("-O3")
    assert "-O3" in flags["runtime.c"]
    assert "-O0" not in flags["runtime.c"]
