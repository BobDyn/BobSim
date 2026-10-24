from pathlib import Path
from types import SimpleNamespace
import sys

import pytest

from common import config_io, vehicle_io


@pytest.mark.parametrize("system", ["Darwin", "Windows", "Linux"])
def test_frozen_root_uses_platform_data_directory(monkeypatch, tmp_path, system):
    monkeypatch.setattr(sys, "frozen", True, raising=False)
    monkeypatch.setattr(vehicle_io.platform, "system", lambda: system)
    monkeypatch.setattr(Path, "home", lambda: tmp_path)
    for name in ("BOBSIM_HOME", "BOBDYN_HOME", "LOCALAPPDATA", "XDG_DATA_HOME"):
        monkeypatch.delenv(name, raising=False)
    base = {
        "Darwin": "Library/Application Support",
        "Windows": "AppData/Local",
        "Linux": ".local/share",
    }[system]
    assert vehicle_io.repo_root() == tmp_path / base / "BobDyn/BobSim"


@pytest.mark.parametrize("variable", ["BOBSIM_HOME", "BOBDYN_HOME"])
@pytest.mark.parametrize("relative", [False, True])
def test_frozen_editor_and_workflows_share_runtime(monkeypatch, tmp_path, variable, relative):
    from app import runtime

    monkeypatch.setattr(sys, "frozen", True, raising=False)
    monkeypatch.delenv("BOBSIM_HOME", raising=False)
    monkeypatch.setenv(variable, "runtime" if relative else str(tmp_path / "runtime"))
    if variable == "BOBDYN_HOME":
        monkeypatch.setenv("BOBSIM_HOME", "")
    monkeypatch.setattr(runtime, "_seed_runtime_root", lambda root: root.mkdir())
    monkeypatch.chdir(tmp_path)
    root = runtime._prepare_runtime_root()
    assert root == vehicle_io.repo_root() == Path.cwd()
    assert vehicle_io.vehicle_yaml_path() == root / "vehicle.yml"
    assert vehicle_io.tire_templates_root({}) == root / "common/tire_templates"
    assert config_io.resolve("study.yml") == root / "study.yml"
    active = config_io.active_config_path("study.yml")
    active.parent.mkdir(parents=True)
    active.write_text("edited: true\n")
    assert config_io.resolve("study.yml") == active


def test_source_root_ignores_desktop_override(monkeypatch, tmp_path):
    monkeypatch.setattr(sys, "frozen", False, raising=False)
    monkeypatch.setenv("BOBSIM_HOME", str(tmp_path))
    assert vehicle_io.repo_root() == Path(vehicle_io.__file__).resolve().parents[1]


def test_frozen_response_reads_edited_inputs_and_writes_runtime_results(monkeypatch, tmp_path):
    from app import python_simulations

    source = vehicle_io.repo_root()
    monkeypatch.setattr(sys, "frozen", True, raising=False)
    monkeypatch.setenv("BOBSIM_HOME", str(tmp_path / "runtime"))
    monkeypatch.setenv("BOBDYN_HOME", str(tmp_path / "legacy"))
    # A different cwd catches accidental dependence on the launch directory.
    monkeypatch.chdir(tmp_path)
    root = vehicle_io.repo_root()
    active = config_io.active_config_path("reduced_order_eval_config.yml")
    active.parent.mkdir(parents=True)
    data = vehicle_io.load_yaml(source / "simulations/response/reduced/reduced_order_eval_config.yml")
    data.update(model_dof=3, stop_time_s=0.1, sample_period_s=0.01, speed_mps=7.0)
    active.write_text(vehicle_io.dump_vehicle(data))
    (root / "vehicle.yml").write_text("vehicle:\n  name: Edited vehicle\n")
    calls = {}

    def simulate(**kwargs):
        calls.update(kwargs)
        return SimpleNamespace(time_s=[0.0, 0.1], signals={"speed": [7.0, 7.0]}, success=True)

    def report(workflow, output, config, summary, *, vehicle_name):
        assert vehicle_name == "Edited vehicle"
        assert output == root / "app/user_data/results/reduced-step-steer"
        (output / "report.pdf").write_bytes(b"report fixture")

    monkeypatch.setattr(python_simulations, "run_step_steer", simulate)
    monkeypatch.setattr(python_simulations, "build_dynpy_report", report)
    python_simulations.run("reduced-step-steer")
    assert calls["vehicle_path"] == root / "vehicle.yml"
    assert calls["speed_mps"] == 7.0
    assert calls["stop_time_s"] == 0.1
    output = root / "app/user_data/results/reduced-step-steer"
    assert {path.name for path in output.iterdir()} == {"signals.csv", "summary.json", "report.pdf"}
    assert not (tmp_path / "legacy").exists()


def test_frozen_workflow_defaults_stay_in_runtime(tmp_path):
    import os
    import subprocess

    for name in ("ggv", "ymd"):
        relative = Path(f"simulations/envelope/{name}/{name}_config.yml")
        target = tmp_path / relative
        target.parent.mkdir(parents=True)
        target.write_bytes((vehicle_io.repo_root() / relative).read_bytes())

    checks = {
        "simulations.envelope.ggv.ggv_generation": ["DEFAULT_GGV_CONFIG", "BUILD_DIR"],
        "simulations.envelope.ymd.ymd_generation": ["DEFAULT_YMD_CONFIG", "BUILD_DIR"],
        "simulations.envelope.vehicle_review.vehicle_review_sim": ["DEFAULT_CONFIG_PATH", "DEFAULT_RESULTS_DIR"],
        "simulations.lap.lap_time_eval_sim": ["DEFAULT_CONFIG"],
        "optimization.envelope._pipeline.sensitivity": ["ENVELOPE_CONFIG", "BUILD_DIR", "RESULTS_DIR"],
        "optimization.response.solve_setup": ["CONFIG"],
        "optimization.response.trade_study": ["DEFAULT_STUDY"],
        "optimization.response.pipeline.compiler": ["STANDARD_DIR", "REPO_ROOT"],
        "visualization.demo": ["OUT_DIR"],
    }
    script = f"""
import importlib
from pathlib import Path
import sys
sys.frozen = True
root = Path({str(tmp_path)!r})
for name, attributes in {checks!r}.items():
    module = importlib.import_module(name)
    for attribute in attributes:
        path = getattr(module, attribute)
        assert path.is_relative_to(root), (name, attribute, path)
"""
    result = subprocess.run(
        [sys.executable, "-c", script], capture_output=True, text=True,
        cwd=vehicle_io.repo_root(), env={**os.environ, "BOBSIM_HOME": str(tmp_path)},
    )
    assert result.returncode == 0, result.stdout + result.stderr
