from __future__ import annotations

import json
from pathlib import Path
import re
import shutil
import zipfile

import pytest
import yaml

from _0_Utils.deploy import deploy
from _0_Utils.kin_py import KINEMATIC_CURVE_META
from _3_StandardSim import _modelica_runner
from _3_StandardSim._modelica_runner import ModelicaRunner
from _5_App import app
from _5_App import desktop

REPO_ROOT = Path(__file__).resolve().parents[1]


def clear_openmodelica_settings(monkeypatch: pytest.MonkeyPatch) -> None:
    app.OPENMODELICA_VERIFY_CACHE.clear()
    for key in {
        *app.OPENMODELICA_OMC_ENV_KEYS,
        *app.OPENMODELICA_HOME_ENV_KEYS,
        *app.OPENMODELICA_LIBRARY_ENV_KEYS,
    }:
        monkeypatch.delenv(key, raising=False)
    monkeypatch.setattr(app, "_read_openmodelica_settings", lambda: {})


def test_app_status_exposes_bobsim_workflows_and_boblib_state() -> None:
    payload = app.status_payload()

    repo = payload["repo"]
    assert repo["boblib_package"]["path"] == "_0_Utils/external/BobLib/BobLib/package.mo"
    assert repo["vehicle_exe"]["path"].startswith("_3_StandardSim/BuildBobLib/VehicleSim/")
    assert repo["four_post_exe"]["path"].startswith("_3_StandardSim/BuildBobLib/FourPostSim/")
    assert payload["runtime"]["home_env"] == "BOBSIM_HOME"
    assert payload["runtime"]["legacy_home_env"] == "BOBDYN_HOME"

    workflow_ids = {workflow["id"] for workflow in payload["workflows"]}
    config_ids = {config["id"] for config in payload["configs"]}
    assert {
        "ramp-steer",
        "steady-state",
        "transient",
        "four-post",
        "ggv",
        "ymd",
        "vehicle-review",
        "standard-sens",
        "envelope-sens",
    } <= workflow_ids
    assert {"vehicle", "ramp-steer", "four-post", "visual-fr-knc-visual"} <= config_ids


def test_app_workflow_actions_are_allowlisted() -> None:
    workflow_action_ids = {action_id for workflow in app.WORKFLOWS for action_id in workflow.actions}

    assert workflow_action_ids <= set(app.ACTION_SPECS)
    for action in app.ACTION_SPECS.values():
        assert action.argv
        assert not Path(action.argv[0]).is_absolute() or action.argv[0] == app.PYTHON


def test_standard_config_fields_expose_sim_tuning_controls() -> None:
    ramp_fields = {field.path: field for field in app.BASE_CONFIG_SPECS["ramp-steer"].fields}
    steady_fields = {field.path: field for field in app.BASE_CONFIG_SPECS["steady-state"].fields}

    ramp_cutoff = ("simulation", "init_parameters", "linearityNonlinearityFraction")
    steady_caps = ("sweep", "maxAyByVelocity")

    assert ramp_fields[ramp_cutoff].group == "Ramp termination"
    assert ramp_fields[("simulation", "init_parameters", "enableLinearityTermination")].kind == "boolean"
    assert steady_fields[steady_caps].kind == "json"
    assert steady_fields[("simulation", "init_parameters", "steadyStateSettleTimeout")].group == "Closed loop"


@pytest.mark.parametrize(
    ("argv", "normalized"),
    [
        (["BobSim", "--run-module", "_3_StandardSim.SomeEval"], ["BobSim", "--run-module", "_3_StandardSim.SomeEval"]),
        (
            ["BobSim", "-m", "_3_StandardSim.SomeEval", "config.yml"],
            ["BobSim", "--run-module", "_3_StandardSim.SomeEval", "config.yml"],
        ),
    ],
)
def test_desktop_forwards_python_module_invocations_without_opening_window(
    argv: list[str],
    normalized: list[str],
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    calls: list[str] = []

    monkeypatch.setattr(desktop.sys, "argv", argv)
    monkeypatch.setattr(desktop, "bobsim_app", type("FakeApp", (), {"main": lambda _self: calls.append("main")})())
    monkeypatch.setattr(desktop.multiprocessing, "freeze_support", lambda: calls.append("freeze_support"))
    monkeypatch.setattr(
        desktop,
        "_available_port",
        lambda _host: (_ for _ in ()).throw(AssertionError("desktop window should not start")),
    )

    desktop.main()

    assert calls == ["freeze_support", "main"]
    assert desktop.sys.argv == normalized


def test_desktop_stdio_replaces_unencodable_output(monkeypatch: pytest.MonkeyPatch) -> None:
    class FakeStream:
        def __init__(self) -> None:
            self.calls: list[dict[str, str]] = []

        def reconfigure(self, **kwargs: str) -> None:
            self.calls.append(kwargs)

    stdout = FakeStream()
    stderr = FakeStream()
    monkeypatch.delenv("PYTHONUTF8", raising=False)
    monkeypatch.delenv("PYTHONIOENCODING", raising=False)
    monkeypatch.setattr(desktop.sys, "stdout", stdout)
    monkeypatch.setattr(desktop.sys, "stderr", stderr)

    desktop._configure_stdio()

    assert desktop.os.environ["PYTHONUTF8"] == "1"
    assert desktop.os.environ["PYTHONIOENCODING"] == "utf-8:replace"
    assert stdout.calls == [{"encoding": "utf-8", "errors": "replace"}]
    assert stderr.calls == [{"encoding": "utf-8", "errors": "replace"}]


def test_desktop_browser_fallback_sanitizes_pyinstaller_library_env(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    bundle = tmp_path / "_MEI123"
    system_lib = tmp_path / "system-lib"
    bundle.mkdir()
    system_lib.mkdir()
    original_ld_path = desktop.os.pathsep.join([str(bundle), str(tmp_path / "other")])
    captured: dict[str, str] = {}

    monkeypatch.setattr(desktop.sys, "_MEIPASS", str(bundle), raising=False)
    monkeypatch.setenv("LD_LIBRARY_PATH", original_ld_path)
    monkeypatch.setenv("LD_LIBRARY_PATH_ORIG", str(system_lib))
    monkeypatch.setenv("PATH", desktop.os.pathsep.join([str(bundle), str(system_lib)]))
    monkeypatch.setattr(
        desktop.webbrowser,
        "open",
        lambda _url: captured.update(
            {
                "LD_LIBRARY_PATH": desktop.os.environ.get("LD_LIBRARY_PATH", ""),
                "PATH": desktop.os.environ.get("PATH", ""),
            }
        ),
    )

    desktop._open_external_browser("http://127.0.0.1:12345")

    assert captured["LD_LIBRARY_PATH"] == str(system_lib)
    assert captured["PATH"] == str(system_lib)
    assert desktop.os.environ["LD_LIBRARY_PATH"] == original_ld_path


def test_desktop_embedded_webview_sanitizes_pyinstaller_library_env(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    bundle = tmp_path / "_MEI123"
    system_lib = tmp_path / "system-lib"
    bundle.mkdir()
    system_lib.mkdir()
    original_ld_path = desktop.os.pathsep.join([str(bundle), str(tmp_path / "other")])
    captured: dict[str, str] = {}

    class FakeWebview:
        @staticmethod
        def start(**kwargs: object) -> None:
            captured.update(
                {
                    "LD_LIBRARY_PATH": desktop.os.environ.get("LD_LIBRARY_PATH", ""),
                    "PATH": desktop.os.environ.get("PATH", ""),
                    "gui": str(kwargs.get("gui")),
                }
            )

    monkeypatch.setattr(desktop.sys, "_MEIPASS", str(bundle), raising=False)
    monkeypatch.setenv("LD_LIBRARY_PATH", original_ld_path)
    monkeypatch.setenv("LD_LIBRARY_PATH_ORIG", str(system_lib))
    monkeypatch.setenv("PATH", desktop.os.pathsep.join([str(bundle), str(system_lib)]))

    desktop._start_embedded_webview(FakeWebview, "qt")

    assert captured["LD_LIBRARY_PATH"] == str(system_lib)
    assert captured["PATH"] == str(system_lib)
    assert captured["gui"] == "qt"
    assert desktop.os.environ["LD_LIBRARY_PATH"] == original_ld_path


def test_desktop_reports_missing_openmodelica_without_running_builds(monkeypatch: pytest.MonkeyPatch) -> None:
    clear_openmodelica_settings(monkeypatch)
    monkeypatch.setattr(app, "FROZEN_APP", True)
    monkeypatch.setattr(app.shutil, "which", lambda _name: None)
    monkeypatch.setattr(app, "_common_omc_candidates", lambda _home=None: [])

    payload = app.external_toolchain_payload()
    assert payload["enabled"] is True
    assert payload["available"] is False
    assert (
        payload["reason"]
        == "OpenModelica was not auto-detected. Select an OpenModelica toolchain before running simulations."
    )

    workflow = next(workflow for workflow in app.WORKFLOWS if workflow.id == "ramp-steer")
    workflow_json = app.workflow_payload(workflow)
    assert workflow_json["available"] is False
    assert workflow_json["unavailable_reason"] == payload["reason"]

    with pytest.raises(RuntimeError, match="OpenModelica was not auto-detected"):
        app.start_workflow("ramp-steer")


def write_fake_openmodelica_library(library: Path) -> None:
    for package_name in app.OPENMODELICA_REQUIRED_LIBRARIES:
        package_dir = library / package_name
        package_dir.mkdir(parents=True, exist_ok=True)
        (package_dir / "package.mo").write_text(f"package {package_name}\nend {package_name};\n", encoding="utf-8")


def fake_omc_version_run(*_args: object, **_kwargs: object) -> object:
    return type("Completed", (), {"returncode": 0, "stdout": "OpenModelica v1.26.0\n"})()


def test_windows_subprocesses_hide_console_windows(monkeypatch: pytest.MonkeyPatch) -> None:
    monkeypatch.setattr(app.sys, "platform", "win32")
    monkeypatch.setattr(app.subprocess, "CREATE_NO_WINDOW", 0x08000000, raising=False)
    monkeypatch.setattr(_modelica_runner.sys, "platform", "win32")
    monkeypatch.setattr(_modelica_runner.subprocess, "CREATE_NO_WINDOW", 0x08000000, raising=False)

    assert app._subprocess_creation_flags() == 0x08000000
    assert _modelica_runner._subprocess_creation_flags() == 0x08000000


def test_file_byte_range_parser_supports_pdf_viewer_requests() -> None:
    assert app._parse_byte_range("bytes=0-99", 1000) == (0, 99)
    assert app._parse_byte_range("bytes=900-", 1000) == (900, 999)
    assert app._parse_byte_range("bytes=-100", 1000) == (900, 999)
    assert app._parse_byte_range(None, 1000) is None
    assert app._parse_byte_range("widgets=0-99", 1000) is None

    with pytest.raises(ValueError):
        app._parse_byte_range("bytes=1000-1100", 1000)


def fake_openmodelica_install(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> tuple[Path, Path, Path]:
    home = tmp_path / "OpenModelica"
    omc = home / "bin" / ("omc.exe" if app.platform.system() == "Windows" else "omc")
    library = home / "lib" / "omlibrary"
    omc.parent.mkdir(parents=True)
    library.mkdir(parents=True)
    omc.write_text("#!/bin/sh\n", encoding="utf-8")
    omc.chmod(0o755)
    write_fake_openmodelica_library(library)
    monkeypatch.setattr(app.shutil, "which", lambda name: str(omc) if name == "omc" else None)
    monkeypatch.setattr(app, "_common_omc_candidates", lambda _home=None: [omc])
    monkeypatch.setattr(app, "_common_openmodelica_libraries", lambda _home=None: [library])
    monkeypatch.setattr(app.subprocess, "run", fake_omc_version_run)
    return home, omc, library


def test_frozen_desktop_uses_local_openmodelica_when_available(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    clear_openmodelica_settings(monkeypatch)
    monkeypatch.setattr(app, "FROZEN_APP", True)
    _home, omc, _library = fake_openmodelica_install(tmp_path, monkeypatch)

    payload = app.external_toolchain_payload()
    assert payload["enabled"] is True
    assert payload["available"] is True
    assert payload["frozen"] is True
    assert payload["omc"] == str(omc)
    assert "enable_env" not in payload
    assert app.action_available(app.ACTION_SPECS["build-vehicle"]) is True

    workflow = next(workflow for workflow in app.WORKFLOWS if workflow.id == "ramp-steer")
    workflow_json = app.workflow_payload(workflow)
    assert workflow_json["available"] is True
    assert workflow_json["unavailable_reason"] == ""


def test_openmodelica_auto_detection_verifies_available_toolchain(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    clear_openmodelica_settings(monkeypatch)
    _home, omc, library = fake_openmodelica_install(tmp_path, monkeypatch)

    payload = app.external_toolchain_payload()

    assert payload["available"] is True
    assert payload["selected"] is True
    assert payload["saved"] is False
    assert payload["verified"] is True
    assert payload["omc"] == str(omc)
    assert payload["openmodelica_library"] == str(library)
    assert payload["settings"] == {}
    assert payload["detected_settings"]["omc_path"] == str(omc)
    assert payload["omc_version"] == "OpenModelica v1.26.0"


def test_openmodelica_auto_detection_uses_user_package_library(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    clear_openmodelica_settings(monkeypatch)
    monkeypatch.setenv("HOME", str(tmp_path))
    # Path.home() reads USERPROFILE on Windows, HOME elsewhere; set both so the
    # lookup stays inside tmp_path on every platform.
    monkeypatch.setenv("USERPROFILE", str(tmp_path))
    home = tmp_path / "OpenModelica"
    omc = home / "bin" / ("omc.exe" if app.platform.system() == "Windows" else "omc")
    if app.platform.system() == "Windows":
        monkeypatch.setenv("APPDATA", str(tmp_path / "AppData" / "Roaming"))
        user_library = tmp_path / "AppData" / "Roaming" / ".openmodelica" / "libraries"
    else:
        user_library = tmp_path / ".openmodelica" / "libraries"
    omc.parent.mkdir(parents=True)
    omc.write_text("#!/bin/sh\n", encoding="utf-8")
    omc.chmod(0o755)
    for package_name in app.OPENMODELICA_REQUIRED_LIBRARIES:
        package_dir = user_library / f"{package_name} 1.0.0" / package_name
        package_dir.mkdir(parents=True, exist_ok=True)
        (package_dir / "package.mo").write_text(f"package {package_name}\nend {package_name};\n", encoding="utf-8")
    monkeypatch.setattr(app.shutil, "which", lambda name: str(omc) if name == "omc" else None)
    monkeypatch.setattr(app, "_common_omc_candidates", lambda _home=None: [omc])
    monkeypatch.setattr(app.subprocess, "run", fake_omc_version_run)

    payload = app.external_toolchain_payload()

    assert payload["available"] is True
    assert payload["openmodelica_library"] == str(user_library)
    assert payload["openmodelica_library_source"] == "default"


def test_openmodelica_libraries_include_windows_roaming_user_directory(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    roaming = tmp_path / "Roaming"
    monkeypatch.setattr(app.platform, "system", lambda: "Windows")
    monkeypatch.setenv("APPDATA", str(roaming))

    candidates = app._common_openmodelica_libraries()

    assert roaming / ".openmodelica" / "libraries" in candidates


def test_openmodelica_settings_override_omc_and_library_paths(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    clear_openmodelica_settings(monkeypatch)
    home = tmp_path / "OpenModelica"
    omc = home / "bin" / ("omc.exe" if app.platform.system() == "Windows" else "omc")
    library = home / "lib" / "omlibrary"
    omc.parent.mkdir(parents=True)
    library.mkdir(parents=True)
    omc.write_text("#!/bin/sh\n", encoding="utf-8")
    omc.chmod(0o755)
    write_fake_openmodelica_library(library)
    monkeypatch.setattr(
        app,
        "_read_openmodelica_settings",
        lambda: {
            "omc_path": str(omc),
            "library_path": str(library),
            "verified_at": "2026-06-28T00:00:00Z",
            "omc_version": "OpenModelica v1.26.0",
        },
    )
    monkeypatch.setattr(app.shutil, "which", lambda _name: None)

    payload = app.external_toolchain_payload()

    assert payload["available"] is True
    assert payload["omc"] == str(omc)
    assert payload["omc_source"] == "saved"
    assert payload["openmodelica_library"] == str(library)
    assert payload["openmodelica_library_source"] == "saved"
    assert app._action_argv(app.ACTION_SPECS["build-vehicle"])[0] == str(omc)

    env: dict[str, str] = {}
    app._apply_openmodelica_env(env)
    if app.platform.system() == "Linux":
        assert "OPENMODELICAHOME" not in env
    else:
        assert env["OPENMODELICAHOME"] == str(home)
    assert env["OPENMODELICALIBRARY"] == str(library)
    assert str(library) in env["MODELICAPATH"].split(app.os.pathsep)


def test_openmodelica_selection_accepts_omc_bin_directory(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    clear_openmodelica_settings(monkeypatch)
    _home, omc, library = fake_openmodelica_install(tmp_path, monkeypatch)

    settings = app._openmodelica_settings_from_payload(
        {
            "omc_path": str(omc.parent),
            "library_path": str(library),
        }
    )
    verified = app._verify_openmodelica_selection(settings)

    assert settings["omc_path"] == str(omc)
    assert verified["omc_path"] == str(omc)
    assert verified["omc_version"] == "OpenModelica v1.26.0"


def test_deploy_does_not_bundle_generated_modelica_binaries() -> None:
    data_paths = set(deploy.DATA_PATHS)

    assert "_3_StandardSim/build_vehicle_sim.mos" in data_paths
    assert "_3_StandardSim/build_four_post_sim.mos" in data_paths
    assert "_3_StandardSim/BuildBobLib" not in data_paths
    assert app.BUILD_ARCHIVE_ROOT.as_posix() not in data_paths


def test_deploy_collects_qt_webengine_for_embedded_desktop_window() -> None:
    assert "PyQt6" in deploy.PYINSTALLER_COLLECT_ALL
    assert "qtpy" in deploy.PYINSTALLER_COLLECT_ALL
    assert "PyQt6.QtWebEngineCore" in deploy.PYINSTALLER_RUNTIME_HIDDEN_IMPORTS
    assert "qtpy" in deploy.PYINSTALLER_RUNTIME_HIDDEN_IMPORTS
    assert "webview.platforms.qt" in deploy.PYINSTALLER_RUNTIME_HIDDEN_IMPORTS


def test_deploy_preflight_requires_qtpy_for_linux_desktop_window(
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    monkeypatch.setattr(deploy, "_has_module", lambda module: module != "qtpy")

    with pytest.raises(SystemExit, match="qtpy"):
        deploy._ensure_build_dependencies(install_deps=False)


def test_deploy_artifacts_are_named_bobsim() -> None:
    assert deploy.APP_NAME == "BobSim"
    assert deploy.DIST_ROOT.name == "BobSim"


def test_runtime_seed_refreshes_app_owned_paths_and_preserves_user_state(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    package_root = tmp_path / "package"
    runtime_root = tmp_path / "runtime"
    package_script = package_root / "_3_StandardSim/build_vehicle_sim.mos"
    package_vehicle = package_root / "vehicle.yml"
    package_default = package_root / "_5_App/sim_configs/_defaults/four-post.yml"
    package_workflow = package_root / "_3_StandardSim/FourPostEval/four_post_eval_config.yml"
    package_tire = package_root / "_0_Utils/tire_templates/stock.tir"
    runtime_script = runtime_root / "_3_StandardSim/build_vehicle_sim.mos"
    runtime_vehicle = runtime_root / "vehicle.yml"
    runtime_default = runtime_root / "_5_App/sim_configs/_defaults/four-post.yml"
    runtime_workflow = runtime_root / "_3_StandardSim/FourPostEval/four_post_eval_config.yml"
    runtime_tire = runtime_root / "_0_Utils/tire_templates/stock.tir"
    runtime_custom_tire = runtime_root / "_0_Utils/tire_templates/custom.tir"
    runtime_build = runtime_root / "_3_StandardSim/BuildBobLib/VehicleSim/old.exe"
    runtime_archive = runtime_root / app.MODELICA_BUILD_CACHE_ROOT / "vehicle/old/files/old.exe"
    runtime_saved_result = runtime_root / app.SAVED_RESULTS_ROOT / "keep/manifest.json"
    runtime_settings = runtime_root / app.OPENMODELICA_SETTINGS_PATH

    package_script.parent.mkdir(parents=True)
    runtime_script.parent.mkdir(parents=True)
    package_default.parent.mkdir(parents=True)
    runtime_default.parent.mkdir(parents=True)
    package_workflow.parent.mkdir(parents=True)
    runtime_workflow.parent.mkdir(parents=True)
    package_tire.parent.mkdir(parents=True)
    runtime_tire.parent.mkdir(parents=True)
    runtime_build.parent.mkdir(parents=True)
    runtime_archive.parent.mkdir(parents=True)
    runtime_saved_result.parent.mkdir(parents=True)
    runtime_settings.parent.mkdir(parents=True)
    package_script.write_text("// new build script\n", encoding="utf-8")
    runtime_script.write_text("// stale build script\n", encoding="utf-8")
    package_vehicle.write_text("vehicle:\n  name: Packaged\n", encoding="utf-8")
    runtime_vehicle.write_text("vehicle:\n  name: UserCar\n", encoding="utf-8")
    package_default.write_text("report:\n  raw_time_series_appendix: false\n", encoding="utf-8")
    runtime_default.write_text("report:\n  raw_time_series_appendix: true\n", encoding="utf-8")
    package_workflow.write_text("procedure:\n  rollMagnitude: 0.02181661564992912\n", encoding="utf-8")
    runtime_workflow.write_text("procedure:\n  rollMagnitude: 0.035\n", encoding="utf-8")
    package_tire.write_text("[MDI_HEADER]\nFILE = stock\n", encoding="utf-8")
    runtime_tire.write_text("[MDI_HEADER]\nFILE = stale-stock\n", encoding="utf-8")
    runtime_custom_tire.write_text("[MDI_HEADER]\nFILE = custom\n", encoding="utf-8")
    runtime_build.write_text("stale build\n", encoding="utf-8")
    runtime_archive.write_text("stale archive\n", encoding="utf-8")
    runtime_saved_result.write_text('{"keep": true}\n', encoding="utf-8")
    runtime_settings.write_text('{"omc_path": "C:/OpenModelica/bin/omc.exe"}\n', encoding="utf-8")
    monkeypatch.setattr(app, "PACKAGE_ROOT", package_root)

    app._seed_runtime_root(runtime_root)

    assert runtime_script.read_text(encoding="utf-8") == "// new build script\n"
    assert runtime_vehicle.read_text(encoding="utf-8") == "vehicle:\n  name: UserCar\n"
    assert runtime_default.read_text(encoding="utf-8") == "report:\n  raw_time_series_appendix: false\n"
    assert runtime_workflow.read_text(encoding="utf-8") == "procedure:\n  rollMagnitude: 0.02181661564992912\n"
    assert runtime_tire.read_text(encoding="utf-8") == "[MDI_HEADER]\nFILE = stock\n"
    assert runtime_custom_tire.read_text(encoding="utf-8") == "[MDI_HEADER]\nFILE = custom\n"
    assert not runtime_build.exists()
    assert not runtime_archive.exists()
    assert runtime_saved_result.is_file()
    assert runtime_settings.is_file()
    assert (runtime_root / app.APP_RUNTIME_SEED_MANIFEST_PATH).is_file()


def test_runtime_seed_preserves_build_cache_when_packaged_sources_are_unchanged(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    package_root = tmp_path / "package"
    runtime_root = tmp_path / "runtime"
    package_script = package_root / "_3_StandardSim/build_vehicle_sim.mos"
    runtime_build = runtime_root / "_3_StandardSim/BuildBobLib/VehicleSim/current.exe"
    package_script.parent.mkdir(parents=True)
    package_script.write_text("// build script\n", encoding="utf-8")
    monkeypatch.setattr(app, "PACKAGE_ROOT", package_root)

    app._seed_runtime_root(runtime_root)
    runtime_build.parent.mkdir(parents=True)
    runtime_build.write_text("current build\n", encoding="utf-8")

    app._seed_runtime_root(runtime_root)

    assert runtime_build.read_text(encoding="utf-8") == "current build\n"


def test_runtime_seed_does_not_replace_boblib_for_generated_runtime_extras(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    package_root = tmp_path / "package"
    runtime_root = tmp_path / "runtime"
    rel_boblib = Path("_0_Utils/external/BobLib/BobLib")
    stabar_rel = Path("Records/VehicleRecord/Chassis/Suspension/Templates/Stabar/StabarRecord.mo")
    package_stabar = package_root / rel_boblib / stabar_rel
    runtime_stabar = runtime_root / rel_boblib / stabar_rel
    runtime_generated = runtime_root / rel_boblib / "Records/VehicleDefn/GeneratedVehicle.mo"
    removed: list[Path] = []

    package_stabar.parent.mkdir(parents=True)
    runtime_stabar.parent.mkdir(parents=True)
    runtime_generated.parent.mkdir(parents=True)
    package_stabar.write_text("record StabarRecord\nend StabarRecord;\n", encoding="utf-8")
    runtime_stabar.write_text("record StabarRecord\nend StabarRecord;\n", encoding="utf-8")
    runtime_generated.write_text("record GeneratedVehicle\nend GeneratedVehicle;\n", encoding="utf-8")
    monkeypatch.setattr(app, "PACKAGE_ROOT", package_root)

    original_remove = app._remove_runtime_path

    def tracking_remove(path: Path) -> bool:
        removed.append(path)
        return original_remove(path)

    monkeypatch.setattr(app, "_remove_runtime_path", tracking_remove)

    app._seed_runtime_root(runtime_root)

    assert runtime_stabar.is_file()
    assert runtime_generated.is_file()
    assert (runtime_root / rel_boblib) not in removed


def test_runtime_remove_reports_locked_windows_file_without_crashing(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    locked_dir = tmp_path / "locked"
    locked_dir.mkdir()
    monkeypatch.setattr(app.time, "sleep", lambda _seconds: None)
    monkeypatch.setattr(app.shutil, "rmtree", lambda _path: (_ for _ in ()).throw(PermissionError("locked")))
    app.RUNTIME_SEED_WARNINGS.clear()

    assert app._remove_runtime_path(locked_dir) is False
    assert app.RUNTIME_SEED_WARNINGS
    assert "file is in use" in app.RUNTIME_SEED_WARNINGS[-1]


def test_frozen_external_tool_env_removes_pyinstaller_paths(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    bundle = tmp_path / "_MEI123"
    system_lib = tmp_path / "system-lib"
    bundle.mkdir()
    system_lib.mkdir()
    monkeypatch.setattr(app, "FROZEN_APP", True)
    monkeypatch.setattr(app.sys, "_MEIPASS", str(bundle), raising=False)
    env = {
        "LD_LIBRARY_PATH": app.os.pathsep.join([str(bundle), str(tmp_path / "other")]),
        "LD_LIBRARY_PATH_ORIG": str(system_lib),
        "PATH": app.os.pathsep.join([str(bundle), str(system_lib)]),
    }

    app._sanitize_frozen_external_env(env)

    assert env["LD_LIBRARY_PATH"] == str(system_lib)
    assert env["PATH"] == str(system_lib)


def test_modelica_build_scripts_use_cross_platform_directory_creation() -> None:
    for rel_path in ("_3_StandardSim/build_vehicle_sim.mos", "_3_StandardSim/build_four_post_sim.mos"):
        text = Path(rel_path).read_text(encoding="utf-8")

        assert 'system("mkdir -p "' not in text
        assert "mkdir(buildDir);" in text


def test_modelica_build_ready_accepts_windows_executable_suffix(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    monkeypatch.setattr(app, "ROOT", tmp_path)
    monkeypatch.setattr(app.platform, "system", lambda: "Windows")
    target = app.MODELICA_BUILD_TARGETS["vehicle"]
    build_dir = tmp_path / target.build_dir
    build_dir.mkdir(parents=True)
    (build_dir / f"{target.exec_name}.exe").write_text("exe", encoding="utf-8")
    (build_dir / f"{target.exec_name}_init.xml").write_text("<init />", encoding="utf-8")

    assert app._modelica_build_dir_ready(target)
    assert app._modelica_build_missing_files(target) == []
    assert app._modelica_build_exe_path(target).endswith(f"{target.exec_name}.exe")


def test_modelica_build_action_fails_when_artifacts_are_missing(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    clear_openmodelica_settings(monkeypatch)
    monkeypatch.setattr(app, "ROOT", tmp_path)
    fake_openmodelica_install(tmp_path, monkeypatch)
    (tmp_path / "vehicle.yml").write_text("vehicle:\n  name: MissingArtifacts\n", encoding="utf-8")
    target = app.MODELICA_BUILD_TARGETS["vehicle"]
    script_path = tmp_path / target.script
    script_path.parent.mkdir(parents=True)
    script_path.write_text("// fake build script\n", encoding="utf-8")
    stack = {
        "written_to_boblib": True,
        "latest_modified": 1.0,
        "signatures": {"vehicle": {"generated": "generated-vehicle-signature"}},
    }
    monkeypatch.setattr(app, "modelica_stack_status_payload", lambda _vehicle_path, _root: stack)
    monkeypatch.setattr(app, "_run_subprocess_action", lambda _action, _job_id: 0)

    job = app.JOBS.create("build-vehicle", "Build VehicleSim", [])
    returncode = app._run_action_process(app.ACTION_SPECS["build-vehicle"], job["id"])

    assert returncode == 1
    job_state = app.JOBS.get(job["id"])
    assert job_state is not None
    assert "Stopping before simulation run" in job_state["log"]


def test_modelica_build_action_creates_build_directory_before_omc(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    clear_openmodelica_settings(monkeypatch)
    monkeypatch.setattr(app, "ROOT", tmp_path)
    fake_openmodelica_install(tmp_path, monkeypatch)
    (tmp_path / "vehicle.yml").write_text("vehicle:\n  name: DirectoryCar\n", encoding="utf-8")
    target = app.MODELICA_BUILD_TARGETS["vehicle"]
    script_path = tmp_path / target.script
    script_path.parent.mkdir(parents=True)
    script_path.write_text("// fake build script\n", encoding="utf-8")
    stack = {
        "written_to_boblib": False,
        "latest_modified": 1.0,
        "signatures": {"vehicle": {"generated": "generated-vehicle-signature"}},
    }
    monkeypatch.setattr(app, "modelica_stack_status_payload", lambda _vehicle_path, _root: stack)

    def fake_build(_action: app.ActionSpec, _job_id: str) -> int:
        assert (tmp_path / target.build_dir).is_dir()
        return 0

    monkeypatch.setattr(app, "_run_subprocess_action", fake_build)

    job = app.JOBS.create("build-vehicle", "Build VehicleSim", [])
    returncode = app._run_action_process(app.ACTION_SPECS["build-vehicle"], job["id"])

    assert returncode == 0
    job_state = app.JOBS.get(job["id"])
    assert job_state is not None
    assert f"Ensured {target.label} build directory" in job_state["log"]


def test_subprocess_action_uses_utf8_replacement_stdio(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    captured: dict[str, object] = {}

    class FakeProcess:
        stdout = iter(["\U0001f4ca ok\n"])

        def __enter__(self) -> "FakeProcess":
            return self

        def __exit__(self, *_args: object) -> None:
            return None

        def wait(self) -> int:
            return 0

    def fake_popen(argv: tuple[str, ...], **kwargs: object) -> FakeProcess:
        captured["argv"] = argv
        captured.update(kwargs)
        return FakeProcess()

    monkeypatch.setattr(app, "ROOT", tmp_path)
    monkeypatch.setattr(app.subprocess, "Popen", fake_popen)

    action = app.ActionSpec(id="echo", label="Echo", argv=("python", "-c", "print('ok')"))
    job = app.JOBS.create(action.id, action.label, list(action.argv))
    returncode = app._run_subprocess_action(action, job["id"])

    env = captured["env"]
    assert returncode == 0
    assert isinstance(env, dict)
    assert env["PYTHONUTF8"] == "1"
    assert env["PYTHONIOENCODING"] == "utf-8:replace"
    assert captured["encoding"] == "utf-8"
    assert captured["errors"] == "replace"
    job_state = app.JOBS.get(job["id"])
    assert job_state is not None
    assert "\U0001f4ca ok" in job_state["log"]


def test_standard_run_action_fails_cleanly_when_vehicle_sim_is_missing(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    clear_openmodelica_settings(monkeypatch)
    monkeypatch.setattr(app, "ROOT", tmp_path)
    fake_openmodelica_install(tmp_path, monkeypatch)
    monkeypatch.setattr(
        app,
        "_run_subprocess_action",
        lambda _action, _job_id: (_ for _ in ()).throw(AssertionError("subprocess should not start")),
    )

    job = app.JOBS.create("run-ramp-steer", "Run RampSteerEval", [])
    returncode = app._run_action_process(app.ACTION_SPECS["run-ramp-steer"], job["id"])

    assert returncode == 2
    job_state = app.JOBS.get(job["id"])
    assert job_state is not None
    log = job_state["log"]
    assert "VehicleSim is not built yet" in log
    assert "_3_StandardSim/BuildBobLib/VehicleSim" in log


def test_modelica_runner_accepts_exe_suffix(tmp_path: Path) -> None:
    build_dir = tmp_path / "build"
    exec_name = "BobLib.Experiments.Standards.VehicleSim"
    build_dir.mkdir()
    (build_dir / f"{exec_name}.exe").write_text("exe", encoding="utf-8")
    (build_dir / f"{exec_name}_init.xml").write_text("<init />", encoding="utf-8")

    runner = ModelicaRunner(build_dir=build_dir, exec_name=exec_name, simulation={})
    command = runner._build_command(build_dir / "overrides.txt", build_dir / "result.csv")

    assert runner.exe_path.name == f"{exec_name}.exe"
    assert Path(command[0]).name == f"{exec_name}.exe"


def test_app_can_read_repo_configs() -> None:
    payload = app.read_text_payload("_3_StandardSim/RampSteerEval/ramp_steer_eval_config.yml")

    assert payload["path"] == "_3_StandardSim/RampSteerEval/ramp_steer_eval_config.yml"
    assert "BobLib.Experiments.Standards.VehicleSim" in payload["text"]


def test_app_rejects_paths_outside_repo() -> None:
    with pytest.raises(ValueError):
        app._safe_repo_path("../outside-bobsim")


def test_app_exposes_visual_templates_as_configurable_setups() -> None:
    payload = app.config_payload("visual-fr-knc-visual")

    field_paths = {tuple(field["path"]) for field in payload["fields"]}
    assert payload["group"] == "visualization"
    assert tuple(["render", "speed"]) in field_paths
    assert tuple(["camera", "attach_to"]) in field_paths
    assert tuple(["style", "joints", "radius"]) in field_paths


def test_app_lists_vehicle_templates_for_architecture_setup() -> None:
    payload = app.vehicle_template_payloads()

    template_ids = {template["id"] for template in payload["templates"]}
    assert "DWBCStabar_DWBCStabarRecord" in template_ids
    assert any(template["front"] == "direct" and template["rear"] == "direct" for template in payload["templates"])
    assert payload["powertrains"][0]["id"] == "EVBatInvMotDiff"
    assert all(template["powertrain"] == "EVBatInvMotDiff" for template in payload["templates"])


def test_app_vehicle_setup_exposes_vehicle_parameters_without_repo_paths() -> None:
    payload = app.config_payload("vehicle")

    field_paths = {tuple(field["path"]) for field in payload["fields"]}
    fields_by_path = {tuple(field["path"]): field for field in payload["fields"]}
    front_architecture = payload["data"]["architecture"]["front"]
    front_order_choices = ["rod", "shock", "stabar"] if front_architecture == "bellcrank_stabar" else ["rod", "shock"]
    assert ("front", "suspension", "upper_fore_i_m") in field_paths
    assert ("aero", "drag_table_n") in field_paths
    assert ("paths", "boblib") not in field_paths
    assert ("schema",) not in field_paths
    assert fields_by_path[("sprung_mass", "cg_m")]["array_shape"] == [3]
    assert fields_by_path[("sprung_mass", "cg_m")]["array_element_kind"] == "number"
    assert fields_by_path[("aero", "drag_table_n")]["array_shape"] == [5, 5]
    assert fields_by_path[("front", "actuation", "bellcrank", "order")]["choices"] == front_order_choices
    assert fields_by_path[("front", "actuation", "shock", "spring_table", "table")]["label"] == "Spring force curve"
    assert fields_by_path[("front", "actuation", "shock", "damper_table", "table")]["label"] == "Damper force curve"
    assert payload["data"]["powertrain"]["implementation"] == "EVBatInvMotDiff"
    assert fields_by_path[("powertrain", "pBattery", "Ns")]["value"] == 140
    assert fields_by_path[("powertrain", "pMotor", "P_mech_peak")]["unit"] == "W"
    assert fields_by_path[("powertrain", "pDriveline", "diff_use_lsd")]["kind"] == "boolean"


def test_frontend_renders_aero_maps_as_interactive_3d_surfaces() -> None:
    app_js = (app.ROOT / "_5_App/static/app.js").read_text(encoding="utf-8")

    assert "function aeroSurfaceRowsFromTable" in app_js
    assert 'area.visual === "aero" || (area.visual === "tires"' in app_js
    assert "state.tireSurfaceScene = {" in app_js
    assert '"FRH m"' in app_js
    assert '"RRH m"' in app_js


def test_frontend_tire_setup_draws_corner_force_envelopes_and_alignment() -> None:
    app_js = (app.ROOT / "_5_App/static/app.js").read_text(encoding="utf-8")

    assert "function tireSetupCorners" in app_js
    assert "function drawTireCornerSetupCard" in app_js
    assert "function drawTireFrictionEllipse" in app_js
    assert "function tireSetupForceMap" in app_js
    assert "force_map_nominal" in app_js
    assert "force_maps_by_gamma" in app_js
    assert "function shiftTireForceMapAlpha" in app_js
    assert "function interpolateTireForceMapAtAlpha" in app_js
    assert "function drawTireForceMapIsolines" in app_js
    assert "function tireForceMapPointAt" in app_js
    assert "function drawTireAlphaOffsetVector" in app_js
    assert "function drawTireInclinationGlyph" in app_js
    assert 'return side === "right" ? -numeric : numeric;' in app_js
    assert "x: -Math.sin(alphaRad)" in app_js
    assert "Friction Ellipses" in app_js
    assert "Shared scale" in app_js
    assert "FzNom" in app_js
    assert "skipInvalid: true" in app_js
    assert "IA ${formatSignedNumber(corner.inclinationDeg)} deg  Fy" in app_js
    assert "function queueTirePayloadRefresh" in app_js
    assert 'await api("/api/tires/eval", {' in app_js
    assert "function isTireSetupFieldTarget" in app_js
    assert "function isTireAlignmentFieldTarget" in app_js
    assert "TIRE_LIVE_WHEEL_FIELDS.has(path[2])" in app_js
    assert "function drawTirePreviewError" in app_js
    assert "function isTirePayloadRefreshTarget" in app_js
    assert 'path[1] === "tire"' in app_js
    assert '["toe_deg", "camber_deg", "radius_m"].includes' not in app_js
    assert "tire-load-camber-slider" in app_js
    assert "function currentTireLoadCamberDeg" in app_js
    assert "function interpolateTireSurfaceRowsByGamma" in app_js
    assert "function tireCombinedForceMapRowsAtFzAndCamber" in app_js
    assert "force_maps_by_gamma_fz" in app_js
    assert "longitudinal_by_gamma" in app_js
    assert "Save .tir + Update Plot" in app_js
    assert "function activeTirDirty" in app_js
    assert "tirePayloadUpdating" in app_js
    assert "data-apply-tir" not in app_js


def test_frontend_tire_tools_show_save_update_spinner() -> None:
    styles = (app.ROOT / "_5_App/static/styles.css").read_text(encoding="utf-8")

    assert ".tir-status-row" in styles
    assert ".tir-spinner" in styles
    assert "@keyframes tir-spin" in styles


def test_frontend_archive_exposes_delete_action() -> None:
    app_js = (app.ROOT / "_5_App/static/app.js").read_text(encoding="utf-8")
    styles = (app.ROOT / "_5_App/static/styles.css").read_text(encoding="utf-8")

    assert "data-delete-result" in app_js
    assert 'await api("/api/results/delete"' in app_js
    assert "function deleteSavedResult" in app_js
    assert ".archive-delete-button" in styles


def test_frontend_pdf_preview_uses_inline_viewer_with_open_fallback() -> None:
    app_js = (app.ROOT / "_5_App/static/app.js").read_text(encoding="utf-8")
    styles = (app.ROOT / "_5_App/static/styles.css").read_text(encoding="utf-8")

    assert "function pdfPreviewHtml" in app_js
    assert "pdf-preview-frame" in app_js
    assert "Open PDF" in app_js
    assert ".pdf-preview-actions" in styles
    assert ".pdf-preview-frame" in styles


def test_frontend_toolchain_selection_uses_omc_and_library_only() -> None:
    app_js = (app.ROOT / "_5_App/static/app.js").read_text(encoding="utf-8")
    html = (app.ROOT / "_5_App/static/index.html").read_text(encoding="utf-8")

    assert "toolchain-omc-input" in html
    assert "toolchain-library-input" in html
    assert "toolchain-home-input" not in html
    assert "toolchain-home-input" not in app_js


def test_frontend_middle_click_pans_3d_interactive_plots() -> None:
    app_js = (app.ROOT / "_5_App/static/app.js").read_text(encoding="utf-8")

    assert "function isMiddleClick(event)" in app_js
    assert "function isPanClick(event)" in app_js
    assert "event?.ctrlKey || isMiddleClick(event)" in app_js
    assert 'mode === "pan" && isMiddleClick(event)' in app_js
    assert 'mode: isPanClick(event) ? "pan" : "rotate"' in app_js
    assert "if (isPanClick(event))" in app_js
    assert "function suppressMiddleCanvasAuxAction(event)" in app_js
    assert "function startMiddleCanvasPan(event)" in app_js
    assert "function dragPointerId(event)" in app_js
    assert 'canvas.addEventListener("mousedown", startMiddleCanvasPan);' in app_js
    assert 'canvas.addEventListener("auxclick", suppressMiddleCanvasAuxAction);' in app_js
    assert 'window.addEventListener("mousemove", (event) =>' in app_js
    assert 'window.addEventListener("mouseup", (event) =>' in app_js


def test_frontend_powertrain_subsystem_tabs_wrap_before_clipping() -> None:
    styles = (app.ROOT / "_5_App/static/styles.css").read_text(encoding="utf-8")

    assert ".powertrain-subsystem-tabs" in styles
    assert "flex-wrap: wrap;" in styles
    assert "overflow: hidden;" in styles
    assert "flex: 0 1 116px;" in styles
    assert "min-width: min(100%, 116px);" in styles
    assert ".powertrain-subsystem-tab span" in styles
    assert "text-overflow: ellipsis;" in styles
    assert ".powertrain-subsystem-panels" in styles
    assert "grid-template-rows: auto auto minmax(0, 1fr);" in styles
    assert ".workflow-guide {\n  position: static;" in styles


def test_frontend_gates_workflow_runner_on_toolchain_availability() -> None:
    app_js = (app.ROOT / "_5_App/static/app.js").read_text(encoding="utf-8")

    assert "function externalToolchainAvailable" in app_js
    assert "function workflowAvailable" in app_js
    assert "function canRunStandardWorkflow" in app_js
    assert "return externalToolchainAvailable() && vehicleDefinitionCurrent()" in app_js
    assert "startSelectedStudyWorkflow" in app_js


def test_app_can_patch_powertrain_defaults_into_vehicle(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
    active = tmp_path / "vehicle.yml"
    active.write_text(
        "schema: boblib.vehicle.v1\n"
        "vehicle:\n"
        "  name: ActiveVehicle\n"
        "architecture:\n"
        "  front: direct\n"
        "  rear: direct\n",
        encoding="utf-8",
    )
    monkeypatch.setattr(app, "ROOT", tmp_path)
    monkeypatch.setattr(
        app,
        "BASE_CONFIG_SPECS",
        {"vehicle": app.ConfigSpec(id="vehicle", group="setup", label="Active Vehicle", path="vehicle.yml")},
    )

    payload = app.patch_config(
        "vehicle",
        {
            json.dumps(["powertrain", "pMotor", "P_mech_peak"]): 95_000.0,
            json.dumps(["powertrain", "pVCU", "regenTorqueLimit"]): 180.0,
        },
    )

    saved = yaml.safe_load(active.read_text(encoding="utf-8"))
    assert saved["powertrain"]["implementation"] == "EVBatInvMotDiff"
    assert saved["powertrain"]["pBattery"]["Ns"] == 140
    assert saved["powertrain"]["pMotor"]["P_mech_peak"] == pytest.approx(95_000.0)
    assert saved["powertrain"]["pVCU"]["regenTorqueLimit"] == pytest.approx(180.0)
    assert payload["data"]["powertrain"]["pMotor"]["P_mech_peak"] == pytest.approx(95_000.0)


def test_app_can_switch_direct_vehicle_to_bellcrank_actuation_defaults(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    source_root = app.ROOT
    active = tmp_path / "vehicle.yml"
    active.write_text(
        (source_root / "_0_Utils/vehicle_templates/DWDirect_DWDirectRecord.yml").read_text(encoding="utf-8"),
        encoding="utf-8",
    )
    shutil.copytree(source_root / "_0_Utils/vehicle_templates", tmp_path / "_0_Utils/vehicle_templates")
    monkeypatch.setattr(app, "ROOT", tmp_path)
    monkeypatch.setattr(
        app,
        "BASE_CONFIG_SPECS",
        {"vehicle": app.ConfigSpec(id="vehicle", group="setup", label="Active Vehicle", path="vehicle.yml")},
    )

    initial = app.config_payload("vehicle")
    initial_paths = {tuple(field["path"]) for field in initial["fields"]}
    assert ("front", "actuation", "bellcrank", "pivot_m") in initial_paths
    assert ("front", "actuation", "stabar", "arm_end_m") in initial_paths

    payload = app.patch_config(
        "vehicle",
        {
            json.dumps(["architecture", "front"]): "bellcrank_stabar",
            json.dumps(["architecture", "rear"]): "direct",
        },
    )

    saved = yaml.safe_load(active.read_text(encoding="utf-8"))
    front_actuation = saved["front"]["actuation"]
    rear_actuation = saved["rear"]["actuation"]
    assert saved["architecture"] == {"front": "bellcrank_stabar", "rear": "direct"}
    assert front_actuation["bellcrank"]["pickups_m"]["stabar"]
    assert front_actuation["stabar"]["arm_end_m"]
    assert front_actuation["bellcrank"]["order"] == ["stabar", "rod", "shock"]
    assert "bellcrank" not in rear_actuation
    assert "stabar" not in rear_actuation
    fields_by_path = {tuple(field["path"]): field for field in payload["fields"]}
    assert fields_by_path[("front", "actuation", "bellcrank", "order")]["choices"] == ["rod", "shock", "stabar"]


def test_app_can_generate_modelica_payload_from_active_vehicle(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
    template_path = app.ROOT / "_0_Utils/vehicle_templates/DWBCStabar_DWBCStabarRecord.yml"
    data = yaml.safe_load(template_path.read_text(encoding="utf-8"))
    data["paths"] = {"boblib": "BobLib", "tire_templates": "tires"}
    tire_name = data["aero"].get("tire_template") or data["front"]["tire"]["template"]
    tire_root = tmp_path / "tires"
    tire_root.mkdir()
    shutil.copy(app.ROOT / "_0_Utils/tire_templates" / f"{tire_name}.tir", tire_root / f"{tire_name}.tir")
    (tmp_path / "vehicle.yml").write_text(yaml.safe_dump(data, sort_keys=False), encoding="utf-8")
    monkeypatch.setattr(app, "ROOT", tmp_path)

    payload = app.generate_modelica_payload()

    assert payload["record"]["name"] == "EVBatInvMotDiff_DWBCStabar_DWBCStabarRecord"
    assert payload["vehicle_template"] == "VehicleSim_EVBatInvMotDiff_DWBCStabar_DWBCStabar"
    assert payload["four_post_template"] == "FourPostSim_EVBatInvMotDiff_DWBCStabar_DWBCStabar"
    assert (tmp_path / payload["record"]["path"]).is_file()


def test_app_archives_and_restores_matching_modelica_builds(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    clear_openmodelica_settings(monkeypatch)
    monkeypatch.setattr(app, "ROOT", tmp_path)
    fake_openmodelica_install(tmp_path, monkeypatch)
    (tmp_path / "vehicle.yml").write_text("vehicle:\n  name: CacheCar\n", encoding="utf-8")
    script_path = tmp_path / "_3_StandardSim/build_vehicle_sim.mos"
    script_path.parent.mkdir(parents=True)
    script_path.write_text("// fake build script\n", encoding="utf-8")
    stack = {
        "written_to_boblib": True,
        "latest_modified": 1.0,
        "signatures": {
            "vehicle": {
                "generated": "generated-vehicle-signature",
            }
        },
    }
    monkeypatch.setattr(app, "modelica_stack_status_payload", lambda _vehicle_path, _root: stack)

    target = app.MODELICA_BUILD_TARGETS["vehicle"]
    build_dir = tmp_path / target.build_dir
    calls = {"count": 0}

    def fake_build(action: app.ActionSpec, job_id: str) -> int:
        assert action.id == "build-vehicle"
        calls["count"] += 1
        build_dir.mkdir(parents=True, exist_ok=True)
        (build_dir / target.exec_name).write_text("exe", encoding="utf-8")
        (build_dir / f"{target.exec_name}_init.xml").write_text("<init />", encoding="utf-8")
        return 0

    monkeypatch.setattr(app, "_run_subprocess_action", fake_build)

    job = app.JOBS.create("build-vehicle", "Build VehicleSim", [])
    assert app._run_action_process(app.ACTION_SPECS["build-vehicle"], job["id"]) == 0
    assert calls["count"] == 1
    metadata = json.loads((build_dir / app.BUILD_METADATA_FILENAME).read_text(encoding="utf-8"))
    archive_dir = tmp_path / app.MODELICA_BUILD_CACHE_ROOT / "vehicle" / metadata["signature"]
    assert (archive_dir / "files" / target.exec_name).is_file()
    assert (archive_dir / "files" / f"{target.exec_name}_init.xml").is_file()

    shutil.rmtree(build_dir)
    assert app._run_action_process(app.ACTION_SPECS["build-vehicle"], job["id"]) == 0
    assert calls["count"] == 1
    assert (build_dir / target.exec_name).read_text(encoding="utf-8") == "exe"
    restored = json.loads((build_dir / app.BUILD_METADATA_FILENAME).read_text(encoding="utf-8"))
    assert restored["signature"] == metadata["signature"]
    assert restored["source"] == "archive"


def test_modelica_build_signature_changes_when_boblib_source_changes(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    monkeypatch.setattr(app, "ROOT", tmp_path)
    script_path = tmp_path / "_3_StandardSim/build_vehicle_sim.mos"
    boblib_package = tmp_path / "_0_Utils/external/BobLib/BobLib/package.mo"
    script_path.parent.mkdir(parents=True)
    boblib_package.parent.mkdir(parents=True)
    script_path.write_text("// fake build script\n", encoding="utf-8")
    boblib_package.write_text("package BobLib end BobLib;\n", encoding="utf-8")
    stack = {
        "written_to_boblib": True,
        "signatures": {
            "vehicle": {
                "generated": "generated-vehicle-signature",
            }
        },
    }
    target = app.MODELICA_BUILD_TARGETS["vehicle"]

    before = app._modelica_build_signature_payload(target, stack)
    boblib_package.write_text("package BobLib constant Real changed = 1; end BobLib;\n", encoding="utf-8")
    after = app._modelica_build_signature_payload(target, stack)

    assert before["modelica_source_digest"] != after["modelica_source_digest"]
    assert before["signature"] != after["signature"]


def test_app_evaluates_active_tire_template_for_ui_curves() -> None:
    payload = app.tire_eval_payload()

    assert payload["model"].startswith("BobLib MF52")
    assert {side["side"] for side in payload["sides"]} == {"front", "rear"}
    assert payload["load_summary"]["source"] == "total mass properties from vehicle.yml"
    assert payload["load_summary"]["total_mass_kg"] == pytest.approx(261.07265114)
    assert payload["load_summary"]["front_static_frac"] == pytest.approx(0.4834962889)
    front = next(side for side in payload["sides"] if side["side"] == "front")
    rear = next(side for side in payload["sides"] if side["side"] == "rear")
    assert front["template"] == "16x7p5_10_12psi"
    assert front["fz_n"] == pytest.approx(payload["load_summary"]["per_tire_loads_n"]["front"])
    assert rear["fz_n"] == pytest.approx(payload["load_summary"]["per_tire_loads_n"]["rear"])
    assert front["metadata"]["fznom_n"] > 0
    assert front["metadata"]["camber_thrust"]["enabled"] is False
    assert front["metadata"]["camber_thrust"]["pvy3"] == pytest.approx(0.0)
    assert front["metadata"]["camber_thrust"]["pdy3"] > 0
    assert len(front["curves"]["longitudinal"]) == 61
    assert len(front["curves"]["lateral"]) == 61
    assert len(front["curves"]["combined"]["fx_by_alpha"]) == 3
    assert len(front["curves"]["combined"]["fy_by_kappa"]) == 3
    assert len(front["curves"]["combined"]["fx_by_alpha"][0]["points"]) == 61
    assert len(front["curves"]["combined"]["fy_by_kappa"][0]["points"]) == 61
    assert len(front["curves"]["pure"]["longitudinal_by_fz"]) >= 5
    assert len(front["curves"]["pure"]["lateral_by_fz"]) >= 5
    assert len(front["curves"]["pure"]["longitudinal_by_fz"][0]["points"]) == 61
    assert len(front["curves"]["pure"]["lateral_by_fz"][0]["points"]) == 61
    assert {"kappa", "fz_n", "fx_n"} <= set(front["curves"]["pure"]["longitudinal_by_fz"][0]["points"][0])
    assert {"alpha_deg", "fz_n", "fy_n"} <= set(front["curves"]["pure"]["lateral_by_fz"][0]["points"][0])
    assert len(front["curves"]["combined"]["fx_surface"]["rows"]) == 31
    assert len(front["curves"]["combined"]["fy_surface"]["rows"]) == 31
    assert len(front["curves"]["combined"]["fx_surface"]["rows"][0]["points"]) == 31
    assert len(front["curves"]["combined"]["fy_surface"]["rows"][0]["points"]) == 31
    assert {"alpha_deg", "kappa", "fx_n"} <= set(front["curves"]["combined"]["fx_surface"]["rows"][0]["points"][0])
    assert {"alpha_deg", "kappa", "fy_n"} <= set(front["curves"]["combined"]["fy_surface"]["rows"][0]["points"][0])
    assert len(front["curves"]["combined"]["fx_surfaces_by_fz"]) >= 5
    assert len(front["curves"]["combined"]["fy_surfaces_by_fz"]) >= 5
    assert len(front["curves"]["pure"]["longitudinal_by_gamma"]) >= 9
    assert len(front["curves"]["pure"]["lateral_by_gamma"]) >= 9
    assert {"gamma_deg", "rows"} <= set(front["curves"]["pure"]["longitudinal_by_gamma"][0])
    assert {"gamma_deg", "rows"} <= set(front["curves"]["pure"]["lateral_by_gamma"][0])
    assert len(front["curves"]["combined"]["fx_surfaces_by_fz"][0]["rows"]) == 31
    assert len(front["curves"]["combined"]["fy_surfaces_by_fz"][0]["rows"]) == 31
    assert {"fz_n", "rows"} <= set(front["curves"]["combined"]["fx_surfaces_by_fz"][0])
    assert front["curves"]["combined"]["force_map_nominal"]["fz_n"] == pytest.approx(front["metadata"]["fznom_n"])
    assert len(front["curves"]["combined"]["force_map_nominal"]["rows"]) == 31
    assert len(front["curves"]["combined"]["force_map_nominal"]["rows"][0]["points"]) == 31
    assert {"alpha_deg", "kappa", "fx_n", "fy_n", "fz_n"} <= set(
        front["curves"]["combined"]["force_map_nominal"]["rows"][0]["points"][0]
    )
    assert len(front["curves"]["combined"]["force_maps_by_gamma"]) >= 9
    assert {"gamma_deg", "fz_n", "rows"} <= set(front["curves"]["combined"]["force_maps_by_gamma"][0])
    assert len(front["curves"]["combined"]["force_maps_by_gamma_fz"]) >= 9
    assert {"gamma_deg", "maps"} <= set(front["curves"]["combined"]["force_maps_by_gamma_fz"][0])
    assert {"fz_n", "rows"} <= set(front["curves"]["combined"]["force_maps_by_gamma_fz"][0]["maps"][0])
    assert any(
        item["gamma_deg"] == pytest.approx(front["camber_deg"])
        for item in front["curves"]["combined"]["force_maps_by_gamma"]
    )
    assert any(
        item["gamma_deg"] == pytest.approx(front["camber_deg"])
        for item in front["curves"]["combined"]["force_maps_by_gamma_fz"]
    )
    assert len(front["curves"]["load_sensitivity"]) >= 5
    assert {"fz_n", "mu_x", "mu_y"} <= set(front["curves"]["load_sensitivity"][0])
    assert any(abs(point["fx_n"]) > 1 for point in front["curves"]["longitudinal"])
    assert any(abs(point["fy_n"]) > 1 for point in front["curves"]["lateral"])

    live_vehicle = yaml.safe_load((app.ROOT / "vehicle.yml").read_text(encoding="utf-8"))
    live_vehicle["front"]["wheel"]["camber_deg"] = 3.25
    live_payload = app.tire_eval_payload(live_vehicle)
    live_front = next(side for side in live_payload["sides"] if side["side"] == "front")
    assert live_front["camber_deg"] == pytest.approx(3.25)
    assert any(
        item["gamma_deg"] == pytest.approx(3.25)
        for item in live_front["curves"]["combined"]["force_maps_by_gamma"]
    )


def test_app_generates_live_kinematic_curves_for_active_vehicle() -> None:
    payload = app.kinematic_curves_from_active_vehicle()

    assert payload["model"].startswith("BobSim native")
    if not payload["available"]:
        pytest.skip(payload["warnings"][0])
    assert payload["axles"]["front"]["ok"] is True
    assert payload["axles"]["rear"]["ok"] is True
    assert len(payload["sweep_m"]) == 20
    assert len(payload["roll_deg"]) == 20
    assert len(payload["axles"]["front"]["curves"]["bump_camber_deg"]) == 20
    assert len(payload["axles"]["rear"]["curves"]["bump_toe_deg"]) == 20
    assert len(payload["axles"]["front"]["curves"]["roll_camber_deg"]) == 20
    assert payload["warnings"] == []


def test_frontend_kinematic_plot_fallbacks_reflect_unit_tested_curve_metadata() -> None:
    app_js = (app.ROOT / "_5_App/static/app.js").read_text(encoding="utf-8")
    match = re.search(r"const DEFAULT_KINEMATIC_CURVES = \[(?P<body>.*?)\];", app_js, re.S)
    assert match is not None

    fallback_curves = [
        {
            "id": item.group("id"),
            "label": item.group("label"),
            "unit": item.group("unit"),
            "x_id": item.group("x_id"),
            "x_label": item.group("x_label"),
            "x_unit": item.group("x_unit"),
            "y_label": item.group("y_label"),
        }
        for item in re.finditer(
            r'\{\s*id: "(?P<id>[^"]+)", label: "(?P<label>[^"]+)", unit: "(?P<unit>[^"]+)", '
            r'x_id: "(?P<x_id>[^"]+)", x_label: "(?P<x_label>[^"]+)", x_unit: "(?P<x_unit>[^"]+)", '
            r'y_label: "(?P<y_label>[^"]+)"\s*\}',
            match.group("body"),
        )
    ]

    expected_curves = [
        {
            "id": item["id"],
            "label": item["label"],
            "unit": item["unit"],
            "x_id": item["x_id"],
            "x_label": item["x_label"],
            "x_unit": item["x_unit"],
            "y_label": item["y_label"],
        }
        for item in KINEMATIC_CURVE_META
    ]
    assert fallback_curves == expected_curves


def test_app_lists_reads_and_saves_tire_templates(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
    (tmp_path / "vehicle.yml").write_text(
        "schema: boblib.vehicle.v1\n"
        "vehicle:\n"
        "  name: TireDemo\n"
        "paths:\n"
        "  tire_templates: tires\n",
        encoding="utf-8",
    )
    tire_root = tmp_path / "tires"
    tire_root.mkdir()
    source = Path("_0_Utils/tire_templates/16x7p5_10_12psi.tir")
    tire_text = source.read_text(encoding="utf-8")
    (tire_root / "base.tir").write_text(tire_text, encoding="utf-8")
    monkeypatch.setattr(app, "ROOT", tmp_path)

    library = app.tire_template_library_payload()
    assert library["templates"][0]["id"] == "base"

    loaded = app.read_tire_template("base")
    assert loaded["metadata"]["fznom_n"] > 0

    saved = app.save_tire_template("Imported Tire.tir", tire_text)
    assert saved["id"] == "Imported_Tire"
    assert (tire_root / "Imported_Tire.tir").is_file()


def test_app_can_save_and_load_named_vehicle_configs(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
    active = tmp_path / "vehicle.yml"
    active.write_text(
        "schema: boblib.vehicle.v1\n"
        "vehicle:\n"
        "  name: ActiveVehicle\n"
        "architecture:\n"
        "  front: direct\n"
        "  rear: direct\n",
        encoding="utf-8",
    )
    template_root = tmp_path / "_0_Utils/vehicle_templates"
    template_root.mkdir(parents=True)
    (template_root / "TemplateVehicle.yml").write_text(
        "schema: boblib.vehicle.v1\n"
        "vehicle:\n"
        "  name: TemplateVehicle\n"
        "architecture:\n"
        "  front: bellcrank\n"
        "  rear: bellcrank_stabar\n",
        encoding="utf-8",
    )
    monkeypatch.setattr(app, "ROOT", tmp_path)
    monkeypatch.setattr(
        app,
        "BASE_CONFIG_SPECS",
        {"vehicle": app.ConfigSpec(id="vehicle", group="setup", label="Active Vehicle", path="vehicle.yml")},
    )

    library = app.save_active_vehicle("My Saved Vehicle")
    saved = library["saved"]
    assert saved["id"] == "saved:my-saved-vehicle"
    assert any(vehicle["id"] == saved["id"] for vehicle in library["vehicles"])
    workspace_vehicle = tmp_path / app.VEHICLE_WORKSPACE_ROOT / "my-saved-vehicle/config/vehicle.yml"
    assert workspace_vehicle.is_file()
    assert library["workspace"]["key"] == "my-saved-vehicle"
    assert library["workspace"]["config"]["exists"] is True

    app.load_vehicle_source("template:TemplateVehicle")
    assert yaml.safe_load(active.read_text(encoding="utf-8"))["vehicle"]["name"] == "TemplateVehicle"

    app.load_vehicle_source("saved:my-saved-vehicle")
    assert yaml.safe_load(active.read_text(encoding="utf-8"))["vehicle"]["name"] == "ActiveVehicle"

    library = app.delete_saved_vehicle("saved:my-saved-vehicle")
    assert not (tmp_path / app.SAVED_VEHICLE_ROOT / "my-saved-vehicle.yml").exists()
    assert all(vehicle["id"] != "saved:my-saved-vehicle" for vehicle in library["vehicles"])
    with pytest.raises(ValueError):
        app.delete_saved_vehicle("template:TemplateVehicle")


def test_app_can_save_load_and_delete_sim_configs(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
    config_path = tmp_path / "ramp.yml"
    config_path.write_text(
        "simulation:\n"
        "  solver: dassl\n"
        "sweep:\n"
        "  testVels: [12.5, 15.0]\n",
        encoding="utf-8",
    )
    monkeypatch.setattr(app, "ROOT", tmp_path)
    monkeypatch.setattr(
        app,
        "BASE_CONFIG_SPECS",
        {
            "ramp-steer": app.ConfigSpec(
                id="ramp-steer",
                group="standard",
                label="Ramp",
                path="ramp.yml",
                workflow_id="ramp-steer",
                fields=(app.FieldSpec(("simulation", "solver"), "Solver", kind="select", choices=("dassl", "ida")),),
            )
        },
    )

    library = app.sim_config_library_payload("ramp-steer")
    assert library["sources"][0]["id"] == "default:ramp-steer"

    app.patch_config("ramp-steer", {'["simulation","solver"]': "ida"})
    saved = app.save_active_sim_config("ramp-steer", "Fast Ramp")
    source_id = saved["saved"]["id"]
    assert source_id == "saved:ramp-steer:fast-ramp"

    app.patch_config("ramp-steer", {'["simulation","solver"]': "dassl"})
    loaded = app.load_sim_config_source(source_id)
    assert loaded["config"]["data"]["simulation"]["solver"] == "ida"

    app.load_sim_config_source("default:ramp-steer")
    assert yaml.safe_load(config_path.read_text(encoding="utf-8"))["simulation"]["solver"] == "dassl"

    library = app.delete_saved_sim_config(source_id)
    assert all(source["id"] != source_id for source in library["sources"])


def test_app_can_save_load_and_delete_study_configs(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
    config_path = tmp_path / "ggv.yml"
    config_path.write_text(
        "generation:\n"
        "  ay_max_g: 4.5\n"
        "  ay_points: 321\n",
        encoding="utf-8",
    )
    monkeypatch.setattr(app, "ROOT", tmp_path)
    monkeypatch.setattr(
        app,
        "BASE_CONFIG_SPECS",
        {
            "ggv": app.ConfigSpec(
                id="ggv",
                group="envelope",
                label="GGV",
                path="ggv.yml",
                workflow_id="ggv",
                fields=(app.FieldSpec(("generation", "ay_max_g"), "Max lateral acceleration", kind="number"),),
            )
        },
    )

    library = app.sim_config_library_payload("ggv")
    assert library["sources"][0]["id"] == "default:ggv"

    app.patch_config("ggv", {'["generation","ay_max_g"]': 3.8})
    saved = app.save_active_sim_config("ggv", "Wet Skidpad")
    source_id = saved["saved"]["id"]
    assert source_id == "saved:ggv:wet-skidpad"

    app.patch_config("ggv", {'["generation","ay_max_g"]': 4.5})
    loaded = app.load_sim_config_source(source_id)
    assert loaded["config"]["data"]["generation"]["ay_max_g"] == 3.8

    app.load_sim_config_source("default:ggv")
    assert yaml.safe_load(config_path.read_text(encoding="utf-8"))["generation"]["ay_max_g"] == 4.5

    library = app.delete_saved_sim_config(source_id)
    assert all(source["id"] != source_id for source in library["sources"])


def test_app_can_save_active_simulation_results(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
    (tmp_path / "vehicle.yml").write_text(
        "vehicle:\n"
        "  name: ResultCar\n"
        "architecture:\n"
        "  front: direct\n"
        "  rear: bellcrank\n",
        encoding="utf-8",
    )
    (tmp_path / "sim.yml").write_text("simulation:\n  stop_time: 1\n", encoding="utf-8")
    results_dir = tmp_path / "results"
    results_dir.mkdir()
    (results_dir / "report.pdf").write_bytes(b"%PDF demo")
    (results_dir / "metrics.csv").write_text("name,value\nscore,1\n", encoding="utf-8")
    monkeypatch.setattr(app, "ROOT", tmp_path)
    monkeypatch.setattr(
        app,
        "WORKFLOWS",
        (
            app.WorkflowSpec(
                id="demo-sim",
                group="standard",
                label="DemoSim",
                config="sim.yml",
                actions=(),
                outputs=(
                    app.OutputSpec("Report", "results/report.pdf", "pdf"),
                    app.OutputSpec("Metrics", "results/metrics.csv", "csv"),
                ),
            ),
        ),
    )

    payload = app.save_active_results("demo-sim", "Baseline Run")
    saved = payload["saved"]

    assert saved["label"] == "Baseline Run"
    assert saved["vehicle_name"] == "ResultCar"
    assert saved["architecture"] == {"front": "direct", "rear": "bellcrank"}
    assert [file["label"] for file in saved["files"]] == [
        "Report",
        "Metrics",
        "Signal Archive",
        "Run Description",
    ]
    assert all((tmp_path / file["path"]).is_file() for file in saved["files"])
    signal_archive = next(file for file in saved["files"] if file["label"] == "Signal Archive")
    with zipfile.ZipFile(tmp_path / signal_archive["path"]) as archive:
        assert "manifest.json" in archive.namelist()
    run_description = next(file for file in saved["files"] if file["label"] == "Run Description")
    description = json.loads((tmp_path / run_description["path"]).read_text(encoding="utf-8"))
    assert description["run_count"] == 0
    assert (tmp_path / saved["vehicle_snapshot"]).is_file()
    assert (tmp_path / saved["config_snapshot"]).is_file()
    assert saved["vehicle_key"] == "resultcar"
    assert (tmp_path / saved["workspace_result_path"] / "manifest.json").is_file()
    assert app.saved_results_payload()["results"][0]["id"] == saved["id"]
    assert app.saved_results_payload("resultcar")["results"][0]["id"] == saved["id"]

    sources = app.result_sources_payload("resultcar")["sources"]
    assert [Path(source["path"]).name for source in sources] == ["metrics.csv"]
    assert sources[0]["path"].startswith(f"{app.VEHICLE_WORKSPACE_ROOT.as_posix()}/resultcar/results/")

    global_result_dir = tmp_path / app.SAVED_RESULTS_ROOT / saved["id"]
    workspace_result_dir = tmp_path / saved["workspace_result_path"]
    delete_payload = app.delete_saved_result(saved["id"])

    assert delete_payload["deleted"] == saved["id"]
    assert delete_payload["results"] == []
    assert not global_result_dir.exists()
    assert not workspace_result_dir.exists()
    assert app.saved_results_payload("resultcar")["results"] == []
    assert app.result_sources_payload("resultcar")["sources"] == []


def test_results_route_is_global_unless_vehicle_key_is_requested(monkeypatch: pytest.MonkeyPatch) -> None:
    calls: list[str | None] = []
    sent: list[dict[str, object]] = []

    def fake_saved_results_payload(vehicle_key: str | None = None) -> dict[str, object]:
        calls.append(vehicle_key)
        return {"vehicle_key": vehicle_key, "results": []}

    def fake_send_json(self: app.BobSimHandler, payload: object, **_kwargs: object) -> None:
        sent.append(payload if isinstance(payload, dict) else {"payload": payload})

    monkeypatch.setattr(app, "saved_results_payload", fake_saved_results_payload)
    monkeypatch.setattr(app.BobSimHandler, "_send_json", fake_send_json)

    handler = app.BobSimHandler.__new__(app.BobSimHandler)
    handler.path = "/api/results"
    handler.do_GET()
    handler.path = "/api/results?vehicle_key=resultcar"
    handler.do_GET()

    assert calls == [None, "resultcar"]
    assert sent == [{"vehicle_key": None, "results": []}, {"vehicle_key": "resultcar", "results": []}]


def test_app_can_explore_result_csv_sources(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
    results_dir = tmp_path / "_3_StandardSim/results"
    results_dir.mkdir(parents=True)
    csv_path = results_dir / "raw_trace.csv"
    csv_path.write_text(
        "time,accY,roll,case\n"
        "0.0,0.0,0.0,A\n"
        "0.1,1.5,0.02,A\n"
        "0.2,3.0,0.04,A\n",
        encoding="utf-8",
    )
    monkeypatch.setattr(app, "ROOT", tmp_path)

    sources = app.result_sources_payload()["sources"]
    assert [source["path"] for source in sources] == ["_3_StandardSim/results/raw_trace.csv"]
    assert sources[0]["numeric_columns"] == ["time", "accY", "roll"]

    series = app.result_series_payload(
        "_3_StandardSim/results/raw_trace.csv",
        x_axis="time",
        signals=["accY", "roll"],
        max_points=2,
    )
    assert series["x"] == [0.0, 0.1, 0.2]
    assert series["stride"] == 1
    assert series["series"][0]["values"] == [0.0, 1.5, 3.0]
    assert series["series"][1]["values"] == [0.0, 0.02, 0.04]


def test_app_can_add_and_remove_vehicle_processing_workflows(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    (tmp_path / "vehicle.yml").write_text(
        "vehicle:\n"
        "  name: ProcessingCar\n",
        encoding="utf-8",
    )
    source_dir = tmp_path / app.VEHICLE_WORKSPACE_ROOT / "processingcar/results/run-1/files"
    source_dir.mkdir(parents=True)
    source = source_dir / "trace.csv"
    source.write_text("time,ay,roll\n0,0,0\n1,1.2,0.03\n", encoding="utf-8")
    monkeypatch.setattr(app, "ROOT", tmp_path)

    payload = app.add_processing_workflow(
        {
            "vehicle_key": "processingcar",
            "label": "Corner balance export",
            "source_path": f"{app.VEHICLE_WORKSPACE_ROOT.as_posix()}/processingcar/results/run-1/files/trace.csv",
            "signals": ["ay", "roll"],
            "output_name": "corner-balance.csv",
        }
    )

    workflow = payload["saved"]
    assert workflow["id"] == "corner-balance-export"
    assert workflow["source"]["exists"] is True
    assert workflow["signals"] == ["ay", "roll"]
    stored = tmp_path / app.VEHICLE_WORKSPACE_ROOT / "processingcar/processing/workflows.json"
    assert stored.is_file()
    assert app.processing_workflows_payload("processingcar")["workflows"][0]["id"] == workflow["id"]

    removed = app.delete_processing_workflow(workflow["id"], "processingcar")
    assert removed["workflows"] == []


def test_app_patch_config_updates_registered_yaml(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
    config_path = tmp_path / "demo.yml"
    config_path.write_text(
        "simulation:\n"
        "  solver: dassl\n"
        "  stop_time: 5.0\n"
        "execution:\n"
        "  parallel: true\n"
        "sweep:\n"
        "  speeds: [10.0, 15.0]\n",
        encoding="utf-8",
    )
    monkeypatch.setattr(app, "ROOT", tmp_path)
    monkeypatch.setattr(
        app,
        "BASE_CONFIG_SPECS",
        {
            "demo": app.ConfigSpec(
                id="demo",
                group="standard",
                label="Demo",
                path="demo.yml",
                fields=(
                    app.FieldSpec(("simulation", "solver"), "Solver", kind="select", choices=("dassl", "ida")),
                    app.FieldSpec(("sweep", "speeds"), "Speeds", kind="list"),
                ),
            )
        },
    )

    payload = app.patch_config(
        "demo",
        {
            '["simulation","solver"]': "ida",
            "simulation.stop_time": 10.0,
            '["execution","parallel"]': False,
            '["sweep","speeds"]': [12.5, 17.5],
        },
    )

    saved = yaml.safe_load(config_path.read_text(encoding="utf-8"))
    assert saved["simulation"]["solver"] == "ida"
    assert saved["simulation"]["stop_time"] == 10.0
    assert saved["execution"]["parallel"] is False
    assert saved["sweep"]["speeds"] == [12.5, 17.5]
    assert any(field["label"] == "Solver" and field["kind"] == "select" for field in payload["fields"])


def test_app_raw_config_save_validates_yaml_root(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
    (tmp_path / "demo.yml").write_text("a: 1\n", encoding="utf-8")
    monkeypatch.setattr(app, "ROOT", tmp_path)
    monkeypatch.setattr(
        app,
        "BASE_CONFIG_SPECS",
        {"demo": app.ConfigSpec(id="demo", group="setup", label="Demo", path="demo.yml")},
    )

    with pytest.raises(TypeError):
        app.save_raw_config("demo", "scalar-only")


def test_app_default_sim_configs_match_their_source_configs() -> None:
    """Every _5_App/sim_configs/_defaults/<workflow>.yml mirrors its ConfigSpec path.

    The defaults directory is a pristine snapshot of the shipped study configs:
    picking "Default" in the app copies it back over the study config, so a
    drifted snapshot silently reverts real settings. Compares committed blobs
    rather than the working copies, because editing a config in the app
    legitimately rewrites the study config on disk.
    """
    import subprocess

    def committed(rel_path: str) -> str | None:
        try:
            return subprocess.run(
                ["git", "show", f"HEAD:{rel_path}"],
                cwd=REPO_ROOT,
                capture_output=True,
                text=True,
                check=True,
            ).stdout
        except (OSError, subprocess.CalledProcessError):
            return None

    checked = 0
    for workflow_id, spec in app.BASE_CONFIG_SPECS.items():
        default_rel = f"_5_App/sim_configs/_defaults/{workflow_id}.yml"
        if not (REPO_ROOT / default_rel).is_file():
            continue
        default_blob = committed(default_rel)
        source_blob = committed(spec.path)
        if default_blob is None or source_blob is None:
            pytest.skip("git is unavailable or a config is not committed")
        assert yaml.safe_load(default_blob) == yaml.safe_load(source_blob), (
            f"{default_rel} has drifted from {spec.path}. The defaults snapshot is a copy of "
            f"the study config; re-copy it instead of hand-editing."
        )
        checked += 1

    assert checked >= 9, f"expected every app default config to be checked, got {checked}"
