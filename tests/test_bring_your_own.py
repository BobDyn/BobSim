"""A consumer brings its own car (BOBSIM_VEHICLE) and output folder (BOBSIM_OUT).

Both default to the checkout, and every test here pins that the defaults stay
exactly as they were, as well as what changes once they are set.
"""

from __future__ import annotations

from pathlib import Path
from typing import Any
import os
import shutil
import subprocess

import pytest
import yaml

from app import modelica_generator
from app.modelica_generator import BobLibRootError, plan_modelica_stack, stage_modelica_stack
from common import config_io
from common.vehicle_io import (
    OUTPUT_ENV,
    VEHICLE_ENV,
    active_vehicle,
    external_vehicle,
    load_yaml,
    output_path,
    output_root,
    repo_root,
    repo_vehicle_yaml_path,
    vehicle_yaml_path,
)

BUILD_BOBLIB = "engines/boblib/BobLib"


@pytest.fixture(autouse=True)
def _clean_env(monkeypatch: pytest.MonkeyPatch) -> None:
    monkeypatch.delenv(VEHICLE_ENV, raising=False)
    monkeypatch.delenv(OUTPUT_ENV, raising=False)


def _outside_vehicle(tmp_path: Path) -> Path:
    path = tmp_path / "car" / "vehicle.yml"
    path.parent.mkdir()
    shutil.copy(repo_vehicle_yaml_path(), path)
    return path


# --- BOBSIM_VEHICLE ---------------------------------------------------------


def test_unset_vehicle_is_the_checked_in_file() -> None:
    assert vehicle_yaml_path() == repo_root() / "vehicle.yml"
    assert not external_vehicle()


def test_vehicle_env_replaces_the_checked_in_file(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
    car = _outside_vehicle(tmp_path)
    monkeypatch.setenv(VEHICLE_ENV, str(car))
    assert vehicle_yaml_path() == car.resolve()
    assert external_vehicle()
    assert repo_vehicle_yaml_path() == repo_root() / "vehicle.yml"


def test_relative_vehicle_env_resolves_against_the_current_directory(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    car = _outside_vehicle(tmp_path)
    monkeypatch.chdir(tmp_path)
    monkeypatch.setenv(VEHICLE_ENV, "car/vehicle.yml")
    assert vehicle_yaml_path() == car.resolve()


def test_blank_env_counts_as_unset(monkeypatch: pytest.MonkeyPatch) -> None:
    # docker compose and make both pass empty values for unset variables.
    monkeypatch.setenv(VEHICLE_ENV, "  ")
    monkeypatch.setenv(OUTPUT_ENV, "")
    assert vehicle_yaml_path() == repo_vehicle_yaml_path()
    assert output_root() is None


def test_vehicle_env_naming_the_checked_in_file_is_not_external(monkeypatch: pytest.MonkeyPatch) -> None:
    monkeypatch.setenv(VEHICLE_ENV, str(repo_vehicle_yaml_path()))
    assert not external_vehicle()


def test_active_vehicle_swaps_only_the_checked_in_file(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
    car = _outside_vehicle(tmp_path)
    other = tmp_path / "other.yml"
    # Configs reach the checked-in car by relative paths like ../../vehicle.yml.
    via_config = repo_root() / "simulations/envelope/ggv/../../../vehicle.yml"
    assert active_vehicle(via_config) == via_config
    monkeypatch.setenv(VEHICLE_ENV, str(car))
    assert active_vehicle(via_config) == car.resolve()
    assert active_vehicle(repo_vehicle_yaml_path()) == car.resolve()
    assert active_vehicle(other) == other


def test_envelope_default_vehicle_follows_the_env(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
    from simulations.envelope.vehicle_loader import load_active_vehicle_yaml
    from simulations.envelope.vehicle_yaml import load_vehicle_yaml

    car = _outside_vehicle(tmp_path)
    data = load_yaml(car)
    data["vehicle"]["name"] = "Outside"
    car.write_text(yaml.safe_dump(data, sort_keys=False), encoding="utf-8")
    monkeypatch.setenv(VEHICLE_ENV, str(car))

    assert load_vehicle_yaml()["vehicle"]["name"] == "Outside"
    loaded, source = load_active_vehicle_yaml()
    assert source == car.resolve()
    assert loaded["vehicle"]["name"] == "Outside"
    # An explicit path is still read as given, so the repo baseline stays reachable.
    assert load_vehicle_yaml(repo_vehicle_yaml_path())["vehicle"]["name"] != "Outside"


def test_four_post_reads_the_vehicle_at_call_time(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
    from simulations.response.mbd.four_post import four_post_eval_sim

    car = _outside_vehicle(tmp_path)
    data = load_yaml(car)
    data["vehicle"]["name"] = "Outside"
    car.write_text(yaml.safe_dump(data, sort_keys=False), encoding="utf-8")

    assert four_post_eval_sim._load_active_vehicle_yaml()["vehicle"]["name"] != "Outside"
    monkeypatch.setenv(VEHICLE_ENV, str(car))
    assert four_post_eval_sim._load_active_vehicle_yaml()["vehicle"]["name"] == "Outside"


def test_four_post_names_the_missing_vehicle(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
    from simulations.response.mbd.four_post import four_post_eval_sim

    missing = tmp_path / "nope.yml"
    monkeypatch.setenv(VEHICLE_ENV, str(missing))
    with pytest.raises(FileNotFoundError, match="nope.yml"):
        four_post_eval_sim._load_active_vehicle_yaml()


# --- BOBSIM_OUT -------------------------------------------------------------


def test_unset_output_leaves_paths_alone() -> None:
    assert output_root() is None
    for path in ("simulations/mbd/generated_results/x.pdf", repo_root() / "simulations/mbd/results/y.csv"):
        assert output_path(path) == Path(path)


def test_output_env_moves_generated_paths(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
    monkeypatch.setenv(OUTPUT_ENV, str(tmp_path / "out"))
    out = (tmp_path / "out").resolve()
    assert output_path("simulations/mbd/generated_results/x.pdf") == out / "generated_results/x.pdf"
    assert output_path(repo_root() / "simulations/mbd/BuildBobLib/VehicleSim") == out / "BuildBobLib/VehicleSim"
    # Paths outside simulations/mbd/ are inputs or deliberate choices, not defaults to move.
    assert output_path("simulations/lap/x.csv") == Path("simulations/lap/x.csv")
    assert output_path(tmp_path / "elsewhere.pdf") == tmp_path / "elsewhere.pdf"
    # Moving twice is the same as moving once.
    once = output_path("simulations/mbd/results/z.csv")
    assert output_path(once) == once


def test_relocate_outputs_is_a_no_op_without_the_env() -> None:
    config = {"simulation": {"build_dir": "simulations/mbd/BuildBobLib/VehicleSim"}}
    assert config_io.relocate_outputs(config) is config


def test_relocate_outputs_moves_every_generated_key(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
    monkeypatch.setenv(OUTPUT_ENV, str(tmp_path))
    root = tmp_path.resolve()
    config: dict[str, Any] = {
        "simulation": {"build_dir": "simulations/mbd/BuildBobLib/VehicleSim", "solver": "dassl"},
        "report": {
            "output_path": "simulations/mbd/generated_results/a_report.pdf",
            "metrics_csv_path": "simulations/mbd/generated_results/a_metrics.csv",
        },
        "plots": "not a mapping section",
    }
    relocated = config_io.relocate_outputs(config)
    assert relocated["simulation"] == {"build_dir": str(root / "BuildBobLib/VehicleSim"), "solver": "dassl"}
    assert relocated["report"]["output_path"] == str(root / "generated_results/a_report.pdf")
    assert relocated["report"]["metrics_csv_path"] == str(root / "generated_results/a_metrics.csv")
    assert relocated["plots"] == "not a mapping section"
    assert config["report"]["output_path"].startswith("simulations/mbd/")
    assert config_io.relocate_outputs(relocated) == relocated


@pytest.mark.parametrize(
    ("module", "config"),
    [
        ("simulations.response.mbd.ramp_steer.ramp_steer_eval_sim", "ramp_steer/ramp_steer_eval_config.yml"),
        (
            "simulations.response.mbd.steady_state.steady_state_eval_sim",
            "steady_state/steady_state_eval_config.yml",
        ),
        ("simulations.response.mbd.transient.transient_eval_sim", "transient/transient_eval_config.yml"),
        ("simulations.response.mbd.four_post.four_post_eval_sim", "four_post/four_post_eval_config.yml"),
    ],
)
def test_standard_eval_configs_write_under_the_output_folder(
    module: str, config: str, tmp_path: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    import importlib

    load_config = importlib.import_module(module).load_config
    seed = repo_root() / "simulations/response/mbd" / config
    assert load_config(seed)["report"]["output_path"].startswith("simulations/mbd/")

    monkeypatch.setenv(OUTPUT_ENV, str(tmp_path))
    loaded = load_config(seed)
    assert Path(loaded["report"]["output_path"]).is_relative_to(tmp_path.resolve())
    build_dir = loaded.get("simulation", {}).get("build_dir")
    if build_dir:
        assert Path(build_dir).is_relative_to(tmp_path.resolve())


def test_runner_finds_its_build_under_the_output_folder(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
    from simulations.response.mbd._modelica_runner import ModelicaRunner

    exec_name = "BobLib.Experiments.Standards.VehicleSim"
    build = tmp_path / "BuildBobLib/VehicleSim"
    build.mkdir(parents=True)
    (build / exec_name).write_text("", encoding="utf-8")
    (build / f"{exec_name}_init.xml").write_text("<x/>", encoding="utf-8")
    monkeypatch.setenv(OUTPUT_ENV, str(tmp_path))

    runner = ModelicaRunner.from_config({"simulation": {}})
    assert runner.build_dir == build.resolve()


# --- Staged BobLib ----------------------------------------------------------


def _stage_fixture(tmp_path: Path) -> tuple[Path, Path]:
    """A throwaway BobSim root with the real BobLib package and an outside vehicle."""
    root = tmp_path / "bobsim"
    package = repo_root() / BUILD_BOBLIB
    if not (package / "package.mo").is_file():
        pytest.skip("BobLib submodule is not initialized")
    shutil.copytree(package, root / BUILD_BOBLIB)
    shutil.copytree(repo_root() / "common/tire_templates", root / "common/tire_templates")
    data = load_yaml(repo_vehicle_yaml_path())
    data["vehicle"]["name"] = "OutsideCar"
    # The checked-in calibrated pose belongs to the checked-in record name.
    data["modelica_initialization"] = "legacy"
    data["paths"] = {"boblib": BUILD_BOBLIB, "tire_templates": "common/tire_templates"}
    car = tmp_path / "car.yml"
    car.write_text(yaml.safe_dump(data, sort_keys=False), encoding="utf-8")
    return root, car


def _tree(path: Path) -> dict[str, bytes]:
    return {p.relative_to(path).as_posix(): p.read_bytes() for p in sorted(path.rglob("*")) if p.is_file()}


def test_stage_writes_the_records_into_a_copy_and_leaves_the_pin_alone(tmp_path: Path) -> None:
    root, car = _stage_fixture(tmp_path)
    pinned_before = _tree(root / BUILD_BOBLIB)
    stage = tmp_path / "out/BuildBobLib/BobLib"

    staged = stage_modelica_stack(car, stage, root=root)

    assert staged.changed
    assert staged.package == stage.resolve()
    assert _tree(root / BUILD_BOBLIB) == pinned_before
    record = stage / "Records/VehicleDefn" / f"{staged.result.record_name}.mo"
    assert record.is_file()
    assert "OutsideCar" in (stage / "Experiments/Standards/VehicleSim.mo").read_text(encoding="utf-8")
    # The staged copy is what writing into the pin would have produced.
    plan = plan_modelica_stack(car, root=root)
    modelica_generator.write_modelica_plan(plan)
    assert _tree(stage) == _tree(root / BUILD_BOBLIB)
    assert not list(stage.parent.glob(".BobLib-*"))


def test_restaging_an_unchanged_car_touches_nothing(tmp_path: Path) -> None:
    root, car = _stage_fixture(tmp_path)
    stage = tmp_path / "stage/BobLib"
    stage_modelica_stack(car, stage, root=root)
    stamps = {p: p.stat().st_mtime_ns for p in stage.rglob("*") if p.is_file()}
    for path in stamps:
        os.utime(path, ns=(1, 1))

    again = stage_modelica_stack(car, stage, root=root)

    assert not again.changed
    assert all(path.stat().st_mtime_ns == 1 for path in stamps)


def test_restaging_a_changed_car_rewrites_only_what_changed_and_drops_stale_files(tmp_path: Path) -> None:
    root, car = _stage_fixture(tmp_path)
    stage = tmp_path / "stage/BobLib"
    first = stage_modelica_stack(car, stage, root=root)
    stray = stage / "Stray.mo"
    stray.write_text("stale", encoding="utf-8")
    untouched = stage / "package.mo"
    os.utime(untouched, ns=(1, 1))

    data = load_yaml(car)
    data["vehicle"]["name"] = "RenamedCar"
    car.write_text(yaml.safe_dump(data, sort_keys=False), encoding="utf-8")
    second = stage_modelica_stack(car, stage, root=root)

    assert second.changed
    assert not stray.exists()
    assert untouched.stat().st_mtime_ns == 1
    assert (stage / "Records/VehicleDefn" / f"{second.result.record_name}.mo").is_file()
    assert not (stage / "Records/VehicleDefn" / f"{first.result.record_name}.mo").exists()


def test_stage_refuses_to_overlap_the_pinned_package(tmp_path: Path) -> None:
    root, car = _stage_fixture(tmp_path)
    pinned_before = _tree(root / BUILD_BOBLIB)
    for stage in (root / BUILD_BOBLIB, root / BUILD_BOBLIB / "Staged", root / "engines"):
        with pytest.raises(BobLibRootError, match="overlaps the pinned package"):
            stage_modelica_stack(car, stage, root=root)
    assert _tree(root / BUILD_BOBLIB) == pinned_before


def test_stage_cli_writes_the_stamp_only_when_the_stage_changes(tmp_path: Path, capsys) -> None:
    root, car = _stage_fixture(tmp_path)
    stage = tmp_path / "out/BuildBobLib/BobLib"
    stamp = stage.with_name("BobLib.stamp")
    argv = [str(car), "--root", str(root), "--stage", str(stage)]

    assert modelica_generator.main(argv) == 0
    assert "(updated)" in capsys.readouterr().out
    assert stamp.read_text(encoding="utf-8") == "OutsideCar\n"
    os.utime(stamp, ns=(1, 1))

    assert modelica_generator.main(argv) == 0
    assert "(unchanged)" in capsys.readouterr().out
    assert stamp.stat().st_mtime_ns == 1

    stamp.unlink()
    assert modelica_generator.main(argv) == 0
    assert stamp.is_file()


def test_stage_cli_reports_a_wrong_boblib_root(tmp_path: Path, capsys) -> None:
    root, car = _stage_fixture(tmp_path)
    data = load_yaml(car)
    data["paths"]["boblib"] = "somewhere/else"
    car.write_text(yaml.safe_dump(data, sort_keys=False), encoding="utf-8")

    assert modelica_generator.main([str(car), "--root", str(root), "--stage", str(tmp_path / "s")]) == 2
    assert "paths.boblib" in capsys.readouterr().err
    assert not (tmp_path / "s").exists()


def test_stage_cli_reports_a_blocked_initialization(tmp_path: Path, capsys) -> None:
    root, car = _stage_fixture(tmp_path)
    data = load_yaml(car)
    data.pop("modelica_initialization")
    car.write_text(yaml.safe_dump(data, sort_keys=False), encoding="utf-8")

    assert modelica_generator.main([str(car), "--root", str(root), "--stage", str(tmp_path / "s")]) == 2
    assert "Recalibrate" in capsys.readouterr().err
    assert not (tmp_path / "s").exists()


def test_stage_and_write_cannot_be_combined(tmp_path: Path) -> None:
    with pytest.raises(SystemExit):
        modelica_generator.main(["vehicle.yml", "--write", "--stage", str(tmp_path)])


# --- Build scripts and make -------------------------------------------------


def test_build_scripts_take_the_staged_package_and_output_folder_from_the_env() -> None:
    for script in ("build_vehicle_sim.mos", "build_four_post_sim.mos"):
        text = (repo_root() / "simulations/response/mbd" / script).read_text(encoding="utf-8")
        assert 'getEnvironmentVar("BOBSIM_BOBLIB")' in text, script
        assert 'getEnvironmentVar("BOBSIM_OUT")' in text, script
        assert 'outRoot + "/BuildBobLib"' in text, script


def _dry_run(*args: str) -> str:
    env = {k: v for k, v in os.environ.items() if k not in (VEHICLE_ENV, OUTPUT_ENV)}
    return subprocess.run(
        ["make", "-n", "RUN=", *args], cwd=repo_root(), env=env, check=True, capture_output=True, text=True
    ).stdout


def test_make_defaults_build_in_the_checkout_without_staging(tmp_path: Path) -> None:
    # A fresh WORKSPACE has no executable, so make prints the build recipe.
    out = _dry_run(f"WORKSPACE={tmp_path}", "standard-build", "standard-build-four-post")
    assert "--stage" not in out
    assert "BOBSIM_BOBLIB" not in out
    assert f"{tmp_path}/simulations/mbd/BuildBobLib/VehicleSim/" in out
    assert f"{tmp_path}/simulations/mbd/BuildBobLib/FourPostSim/" in out


def test_make_stages_an_outside_vehicle_and_builds_under_the_output_folder(tmp_path: Path) -> None:
    car = _outside_vehicle(tmp_path)
    out_dir = tmp_path / "out"
    out = _dry_run(f"BOBSIM_VEHICLE={car}", f"BOBSIM_OUT={out_dir}", "standard-build", "standard-build-four-post")
    assert f'-m app.modelica_generator "{car}" --stage "{out_dir}/BuildBobLib/BobLib"' in out
    assert f'export BOBSIM_BOBLIB="{out_dir}/BuildBobLib/BobLib"' in out
    assert f'export BOBSIM_OUT="{out_dir}"' in out
    assert f"{out_dir}/BuildBobLib/VehicleSim/" in out
    assert f"{out_dir}/BuildBobLib/FourPostSim/" in out
    assert "simulations/mbd/BuildBobLib" not in out
