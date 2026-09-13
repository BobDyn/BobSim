from __future__ import annotations

import argparse
from datetime import date
import hashlib
import importlib.util
import json
import os
from pathlib import Path
import platform
import shutil
import subprocess
import sys
import tarfile
from typing import Iterable
import zipfile


ROOT = Path(__file__).resolve().parents[2]
if str(ROOT) not in sys.path:
    sys.path.insert(0, str(ROOT))

from _5_App import storage as app_storage  # noqa: E402

APP_NAME = "BobSim"
DEPLOY_ROOT = ROOT / "_0_Utils" / "deploy"
DIST_ROOT = DEPLOY_ROOT / "dist" / APP_NAME
WORK_ROOT = DEPLOY_ROOT / "build" / "pyinstaller"
ASSET_ROOT = DEPLOY_ROOT / "assets"
LOGO_PATH = ROOT / "_0_Utils" / "external" / "BobLib" / "BobLib" / "Resources" / "Images" / "bobdyn.png"
FALLBACK_LOGO_PATH = ROOT / "_0_Utils" / "reporting" / "media" / "bob.png"
DEPLOY_REQUIREMENTS = DEPLOY_ROOT / "requirements.txt"

DATA_PATHS = (
    "vehicle.yml",
    "_0_Utils/external/BobLib/BobLib",
    "_0_Utils/plotting",
    "_0_Utils/reporting",
    "_0_Utils/tire_templates",
    "_0_Utils/vehicle_templates",
    "_1_VisualSim/visual_templates",
    "_2_EnvelopeSim/GGV/ggv_config.yml",
    "_2_EnvelopeSim/YMD/ymd_config.yml",
    "_2_EnvelopeSim/VehicleReview/vehicle_review_config.yml",
    "_3_StandardSim/build_vehicle_sim.mos",
    "_3_StandardSim/build_four_post_sim.mos",
    "_3_StandardSim/FourPostEval/four_post_eval_config.yml",
    "_3_StandardSim/RampSteerEval/ramp_steer_eval_config.yml",
    "_3_StandardSim/SteadyStateEval/steady_state_eval_config.yml",
    "_3_StandardSim/TransientEval/transient_eval_config.yml",
    "_4_OptSim/EnvelopeSens/config.yml",
    "_4_OptSim/StandardSens/configs",
    "_5_App/static",
    "_5_App/sim_configs/_defaults",
)

MODULE_ROOTS = (
    "_0_Utils",
    "_2_EnvelopeSim",
    "_3_StandardSim",
    "_4_OptSim",
    "_5_App",
)

EXCLUDED_MODULES = (
    "_1_VisualSim.run_visual",
    "_1_VisualSim.viewer",
    "PyQt5",
    "PySide2",
    "PySide6",
    "pyvista",
    "pyvistaqt",
    "vtk",
    "vtkmodules",
)

PYINSTALLER_COLLECT_ALL = (
    "PyQt6",
    "qtpy",
    "webview",
)

PYINSTALLER_RUNTIME_HIDDEN_IMPORTS = (
    "PyQt6.QtCore",
    "PyQt6.QtGui",
    "PyQt6.QtWidgets",
    "PyQt6.QtWebEngineCore",
    "PyQt6.QtWebEngineWidgets",
    "qtpy",
    "qtpy.QtCore",
    "qtpy.QtGui",
    "qtpy.QtWidgets",
    "qtpy.QtWebEngineCore",
    "qtpy.QtWebEngineWidgets",
    "webview.platforms.qt",
)

TEXT_SUFFIXES = {
    ".css",
    ".html",
    ".js",
    ".json",
    ".md",
    ".mos",
    ".py",
    ".toml",
    ".txt",
    ".yaml",
    ".yml",
}
TEXT_NAMES = {"Dockerfile", "makefile"}
CONFLICT_START = "<<<<<<< "
CONFLICT_MIDDLE = "======="
CONFLICT_END = ">>>>>>> "


def _run(cmd: list[str], env: dict[str, str] | None = None) -> None:
    print("+ " + " ".join(cmd), flush=True)
    run_env = os.environ.copy()
    if env:
        run_env.update(env)
    subprocess.run(cmd, cwd=ROOT, check=True, env=run_env)


def _has_module(module: str) -> bool:
    try:
        return importlib.util.find_spec(module) is not None
    except ModuleNotFoundError:
        return False


def _install_deploy_dependencies() -> None:
    if not DEPLOY_REQUIREMENTS.is_file():
        raise SystemExit(f"Missing deploy requirements file: {DEPLOY_REQUIREMENTS}")
    _run([sys.executable, "-m", "pip", "install", "-r", str(DEPLOY_REQUIREMENTS)])


def _ensure_build_dependencies(install_deps: bool) -> None:
    required = {
        "PyInstaller": "PyInstaller",
        "PIL": "Pillow",
        "qtpy": "qtpy",
        "webview": "pywebview",
        "PyQt6.QtWebEngineCore": "PyQt6-WebEngine",
        "PyQt6.QtWebEngineWidgets": "PyQt6-WebEngine",
    }
    missing_required = sorted({package for module, package in required.items() if not _has_module(module)})

    if missing_required and install_deps:
        _install_deploy_dependencies()
        missing_required = sorted({package for module, package in required.items() if not _has_module(module)})

    if missing_required:
        joined = ", ".join(missing_required)
        raise SystemExit(
            f"Missing deploy dependencies: {joined}. "
            "Run `make deploy-deps` or `make deploy DEPLOY_INSTALL_DEPS=1`."
        )


def _ensure_icon_dependencies(install_deps: bool) -> None:
    if _has_module("PIL"):
        return
    if install_deps:
        _install_deploy_dependencies()
    if not _has_module("PIL"):
        raise SystemExit("Missing deploy icon dependency: Pillow. Run `make deploy-deps`.")


def _logo_source() -> Path:
    if LOGO_PATH.is_file():
        return LOGO_PATH
    if FALLBACK_LOGO_PATH.is_file():
        return FALLBACK_LOGO_PATH
    raise SystemExit("Could not find a BobDyn/BobSim logo PNG for deploy icon generation.")


def generate_icon_assets() -> dict[str, str]:
    from PIL import Image

    ASSET_ROOT.mkdir(parents=True, exist_ok=True)
    source = _logo_source()
    image = Image.open(source).convert("RGBA")
    if image.width != image.height:
        size = min(image.width, image.height)
        left = (image.width - size) // 2
        top = (image.height - size) // 2
        image = image.crop((left, top, left + size, top + size))

    png_path = ASSET_ROOT / "bobsim.png"
    ico_path = ASSET_ROOT / "bobsim.ico"
    icns_path = ASSET_ROOT / "bobsim.icns"
    sizes = [(16, 16), (32, 32), (48, 48), (64, 64), (128, 128), (256, 256)]

    image.save(png_path)
    image.save(ico_path, sizes=sizes)
    try:
        image.save(icns_path, sizes=sizes)
    except Exception as exc:
        print(f"warning: could not generate macOS icns icon: {exc}", flush=True)

    assets = {
        "source": str(source.relative_to(ROOT)),
        "png": str(png_path.relative_to(ROOT)),
        "ico": str(ico_path.relative_to(ROOT)),
    }
    if icns_path.is_file():
        assets["icns"] = str(icns_path.relative_to(ROOT))
    print("Generated deploy icon assets:", json.dumps(assets, indent=2), flush=True)
    return assets


def _is_text_file(path: Path) -> bool:
    return path.suffix in TEXT_SUFFIXES or path.name in TEXT_NAMES


def _iter_conflict_check_files() -> Iterable[Path]:
    roots = [ROOT / item for item in DATA_PATHS] + [ROOT / "makefile", ROOT / "requirements.txt", ROOT / "README.md"]
    seen: set[Path] = set()
    for root in roots:
        if not root.exists():
            continue
        paths = [root] if root.is_file() else root.rglob("*")
        for path in paths:
            if not path.is_file() or path in seen or not _is_text_file(path):
                continue
            rel_parts = path.relative_to(ROOT).parts
            if rel_parts[:2] in {
                ("_3_StandardSim", "Build"),
                ("_3_StandardSim", "BuildBobLib"),
                ("_3_StandardSim", "generated_results"),
                ("_3_StandardSim", "results"),
                ("_5_App", "user_data"),
            }:
                continue
            if rel_parts[:3] in {
                ("_0_Utils", "deploy", "assets"),
                ("_0_Utils", "deploy", "build"),
                ("_0_Utils", "deploy", "dist"),
            }:
                continue
            if "__pycache__" in path.parts:
                continue
            seen.add(path)
            yield path


def _find_conflict_markers() -> list[str]:
    offenders: list[str] = []
    for path in _iter_conflict_check_files():
        try:
            with path.open("r", encoding="utf-8", errors="ignore") as handle:
                for line_number, line in enumerate(handle, start=1):
                    if (
                        line.startswith(CONFLICT_START)
                        or line.rstrip("\n") == CONFLICT_MIDDLE
                        or line.startswith(CONFLICT_END)
                    ):
                        offenders.append(f"{path.relative_to(ROOT)}:{line_number}")
                        break
        except OSError as exc:
            offenders.append(f"{path.relative_to(ROOT)}: {exc}")
    return offenders


def preflight(skip_conflict_check: bool) -> None:
    if skip_conflict_check:
        return
    offenders = _find_conflict_markers()
    if not offenders:
        print("Deploy preflight passed.", flush=True)
        return

    print("Deploy preflight found unresolved merge-conflict markers:", flush=True)
    for offender in offenders[:80]:
        print(f"  {offender}", flush=True)
    remaining = len(offenders) - 80
    if remaining > 0:
        print(f"  ...and {remaining} more", flush=True)
    raise SystemExit("Resolve these conflicts before building a deploy artifact.")


def _remove_path(path: Path) -> None:
    if not path.exists() and not path.is_symlink():
        return
    if path.is_dir() and not path.is_symlink():
        shutil.rmtree(path, ignore_errors=True)
    else:
        try:
            path.unlink()
        except FileNotFoundError:
            pass


def _clean_directory_contents(path: Path, keep: set[str] | None = None) -> None:
    keep = keep or {".gitkeep"}
    path.mkdir(parents=True, exist_ok=True)
    for child in path.iterdir():
        if child.name in keep:
            continue
        _remove_path(child)


def clean_generated_artifacts(include_deploy: bool = True) -> None:
    for cache_dir in ROOT.rglob("__pycache__"):
        _remove_path(cache_dir)
    for suffix in ("*.pyc", "*.pyo"):
        for file_path in ROOT.rglob(suffix):
            _remove_path(file_path)

    for path in (
        ".pytest_cache",
        ".mypy_cache",
        ".ruff_cache",
        ".coverage",
        "htmlcov",
        "build",
        "dist",
    ):
        _remove_path(ROOT / path)

    for path in (
        *(item.as_posix() for item in app_storage.USER_DATA_DIRS),
        "_1_VisualSim/results",
        "_2_EnvelopeSim/Build",
        "_2_EnvelopeSim/results",
        "_3_StandardSim/Build",
        "_3_StandardSim/BuildBobLib",
        "_3_StandardSim/generated_results",
        "_3_StandardSim/results",
        "_4_OptSim/Build",
        "_4_OptSim/StandardSens/results",
        "_4_OptSim/EnvelopeSens/results",
        "_4_OptSim/population",
        "_4_OptSim/population_refined",
        "_4_OptSim/results",
    ):
        _clean_directory_contents(ROOT / path)

    _clean_directory_contents(ROOT / "_5_App" / "sim_configs", keep={".gitkeep", "_defaults"})

    for visual_artifact in (ROOT / "_1_VisualSim").glob("*_visual.npz"):
        _remove_path(visual_artifact)

    if include_deploy:
        for deploy_path in (DEPLOY_ROOT / "dist", WORK_ROOT.parent, ASSET_ROOT):
            _remove_path(deploy_path)

    print("Generated artifacts cleaned.", flush=True)


def _module_name_from_path(path: Path) -> str | None:
    if path.name != "__init__.py" and path.suffix != ".py":
        return None
    if "__pycache__" in path.parts or "external" in path.parts:
        return None
    if path.is_relative_to(ROOT / "_0_Utils" / "deploy"):
        return None

    if ROOT / "_4_OptSim" in path.parents:
        rel = path.relative_to(ROOT / "_4_OptSim")
        parts = list(rel.with_suffix("").parts)
    else:
        rel = path.relative_to(ROOT)
        parts = list(rel.with_suffix("").parts)

    if parts[-1] == "__init__":
        parts = parts[:-1]
    if not parts:
        return None
    return ".".join(parts)


def discover_hidden_imports() -> list[str]:
    modules: set[str] = set()
    for root_name in MODULE_ROOTS:
        root = ROOT / root_name
        if not root.exists():
            continue
        for path in root.rglob("*.py"):
            module = _module_name_from_path(path)
            if module:
                modules.add(module)
    return sorted(modules)


def _data_arg(source: Path, destination: str) -> str:
    return f"{source}{os.pathsep}{destination}"


def _data_destination(rel_path: str, source: Path) -> str:
    if source.is_dir():
        return rel_path
    parent = Path(rel_path).parent
    if str(parent) == ".":
        return "."
    return parent.as_posix()


def _icon_arg() -> Path:
    system = platform.system()
    if system == "Darwin" and (ASSET_ROOT / "bobsim.icns").is_file():
        return ASSET_ROOT / "bobsim.icns"
    return ASSET_ROOT / "bobsim.ico"


def _artifact_path(output_root: Path, mode: str) -> Path:
    system = platform.system()
    if system == "Darwin":
        app_bundle = output_root / f"{APP_NAME}.app"
        if app_bundle.exists():
            return app_bundle
    if mode == "onedir":
        executable = APP_NAME + (".exe" if system == "Windows" else "")
        return output_root / APP_NAME / executable
    artifact = output_root / APP_NAME
    if system == "Windows":
        return artifact.with_suffix(".exe")
    return artifact


def build_pyinstaller(mode: str, install_deps: bool, skip_conflict_check: bool) -> None:
    preflight(skip_conflict_check=skip_conflict_check)
    _ensure_build_dependencies(install_deps)
    generate_icon_assets()

    if mode not in {"onefile", "onedir"}:
        raise SystemExit("Deploy mode must be `onefile` or `onedir`.")

    output_root = DIST_ROOT / mode
    work_root = WORK_ROOT / mode
    matplotlib_cache = work_root / "matplotlib"
    output_root.mkdir(parents=True, exist_ok=True)
    work_root.mkdir(parents=True, exist_ok=True)
    matplotlib_cache.mkdir(parents=True, exist_ok=True)

    cmd = [
        sys.executable,
        "-m",
        "PyInstaller",
        "--noconfirm",
        "--clean",
        "--name",
        APP_NAME,
        "--distpath",
        str(output_root),
        "--workpath",
        str(work_root),
        "--specpath",
        str(work_root),
        "--paths",
        str(ROOT),
        "--paths",
        str(ROOT / "_4_OptSim"),
        "--windowed",
        "--icon",
        str(_icon_arg()),
    ]
    if mode == "onefile":
        cmd.append("--onefile")

    for module in EXCLUDED_MODULES:
        cmd.extend(["--exclude-module", module])

    for module in PYINSTALLER_COLLECT_ALL:
        cmd.extend(["--collect-all", module])

    for module in PYINSTALLER_RUNTIME_HIDDEN_IMPORTS:
        cmd.extend(["--hidden-import", module])

    for rel_path in DATA_PATHS:
        source = ROOT / rel_path
        if source.exists():
            cmd.extend(["--add-data", _data_arg(source, _data_destination(rel_path, source))])

    for module in discover_hidden_imports():
        cmd.extend(["--hidden-import", module])

    cmd.append(str(ROOT / "_5_App" / "desktop.py"))
    _run(cmd, env={"MPLCONFIGDIR": str(matplotlib_cache), "QT_API": "pyqt6"})

    artifact = _artifact_path(output_root, mode)

    manifest = {
        "app": APP_NAME,
        "mode": mode,
        "artifact": str(artifact.relative_to(ROOT)),
        "runtime_home_env": "BOBSIM_HOME",
        "legacy_runtime_home_env": "BOBDYN_HOME",
        "assets": generate_icon_assets(),
    }
    manifest_path = output_root / "manifest.json"
    manifest_path.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    print(f"Deploy artifact ready: {artifact.relative_to(ROOT)}", flush=True)
    print(f"Deploy manifest: {manifest_path.relative_to(ROOT)}", flush=True)


def _machine_slug() -> str:
    machine = platform.machine().lower() or "unknown"
    aliases = {
        "amd64": "x86_64",
        "x64": "x86_64",
        "x86-64": "x86_64",
        "aarch64": "arm64",
    }
    return aliases.get(machine, machine.replace(" ", "-"))


def _platform_slug() -> str:
    system = platform.system()
    names = {
        "Darwin": "macos",
        "Linux": "linux",
        "Windows": "windows",
    }
    return f"{names.get(system, system.lower() or 'unknown')}-{_machine_slug()}"


def _git_value(args: list[str]) -> str:
    try:
        return subprocess.check_output(["git", *args], cwd=ROOT, text=True, stderr=subprocess.DEVNULL).strip()
    except Exception:
        return ""


def _release_version(version: str | None) -> str:
    if version:
        return version.removeprefix("v")
    ref_name = os.environ.get("GITHUB_REF_NAME", "")
    if ref_name.startswith("v"):
        return ref_name.removeprefix("v")
    tag = _git_value(["describe", "--tags", "--exact-match"])
    if tag:
        return tag.removeprefix("v")
    return date.today().strftime("%Y.%m.%d")


def _copy_release_artifact(artifact: Path, release_dir: Path) -> Path:
    destination = release_dir / artifact.name
    if destination.exists():
        if destination.is_dir():
            shutil.rmtree(destination)
        else:
            destination.unlink()
    if artifact.is_dir():
        shutil.copytree(artifact, destination)
    else:
        shutil.copy2(artifact, destination)
    return destination


def _write_release_notes(release_dir: Path, version: str, artifact: Path) -> Path:
    commit = _git_value(["rev-parse", "--short", "HEAD"]) or "unknown"
    tag = _git_value(["describe", "--tags", "--exact-match"]) or f"v{version}"
    notes = release_dir / "RELEASE_NOTES.md"
    notes.write_text(
        "\n".join(
            [
                f"# BobSim {version}",
                "",
                f"Platform: {_platform_slug()}",
                f"Source commit: {commit}",
                f"Tag: {tag}",
                "",
                "## Highlights",
                "",
                "- One-file BobSim desktop wrapper with the Python backend and frontend bundled.",
                "- BobSim icon assets generated from the BobDyn project resource image.",
                "- Local simulation executables, generated configs, reports, workspaces, and caches are not bundled.",
                "",
                "## Run",
                "",
                "Extract this archive, then run the BobSim executable or app bundle.",
                "Set `BOBSIM_HOME` to choose where runtime-generated data is stored.",
                "`BOBDYN_HOME` is also honored for compatibility with older local installs.",
                "",
                f"Packaged artifact: `{artifact.name}`",
                "",
            ]
        ),
        encoding="utf-8",
    )
    return notes


def _make_archive(release_dir: Path, release_root: Path, release_name: str) -> Path:
    if platform.system() in {"Darwin", "Windows"}:
        archive = release_root / f"{release_name}.zip"
        if archive.exists():
            archive.unlink()
        with zipfile.ZipFile(archive, "w", compression=zipfile.ZIP_DEFLATED) as handle:
            for path in sorted(release_dir.rglob("*")):
                handle.write(path, path.relative_to(release_root))
        return archive

    archive = release_root / f"{release_name}.tar.gz"
    if archive.exists():
        archive.unlink()
    with tarfile.open(archive, "w:gz") as handle:
        handle.add(release_dir, arcname=release_dir.name)
    return archive


def _sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as handle:
        for chunk in iter(lambda: handle.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def package_release(mode: str, version: str | None) -> tuple[Path, Path]:
    output_root = DIST_ROOT / mode
    artifact = _artifact_path(output_root, mode)
    if not artifact.exists():
        raise SystemExit(f"Missing deploy artifact: {artifact.relative_to(ROOT)}. Run `make deploy` first.")

    release_version = _release_version(version)
    release_name = f"{APP_NAME}-{release_version}-{_platform_slug()}"
    release_root = DEPLOY_ROOT / "dist" / "releases"
    release_dir = release_root / release_name
    if release_dir.exists():
        shutil.rmtree(release_dir)
    release_dir.mkdir(parents=True)

    copied_artifact = _copy_release_artifact(artifact, release_dir)
    manifest = output_root / "manifest.json"
    if manifest.is_file():
        shutil.copy2(manifest, release_dir / "manifest.json")
    notes = _write_release_notes(release_dir, release_version, copied_artifact)
    archive = _make_archive(release_dir, release_root, release_name)

    checksum_path = release_root / f"{release_name}.sha256"
    checksum_targets = [archive, notes]
    release_manifest = release_dir / "manifest.json"
    if release_manifest.is_file():
        checksum_targets.append(release_manifest)
    if copied_artifact.is_file():
        checksum_targets.append(copied_artifact)
    checksum_path.write_text(
        "".join(f"{_sha256(path)}  {path.relative_to(release_root).as_posix()}\n" for path in checksum_targets),
        encoding="utf-8",
    )
    print(f"Release archive: {archive.relative_to(ROOT)}", flush=True)
    print(f"Release checksums: {checksum_path.relative_to(ROOT)}", flush=True)
    return archive, checksum_path


def _release_tag(version: str | None, tag: str | None) -> str:
    if tag:
        return tag
    ref_name = os.environ.get("GITHUB_REF_NAME", "")
    if ref_name.startswith("v"):
        return ref_name
    exact_tag = _git_value(["describe", "--tags", "--exact-match"])
    if exact_tag:
        return exact_tag
    return f"v{_release_version(version)}"


def upload_github_release(version: str | None, tag: str | None, files: Iterable[Path]) -> None:
    gh = shutil.which("gh")
    if not gh:
        raise SystemExit("GitHub CLI (`gh`) is required for --upload-release.")

    release_tag = _release_tag(version, tag)
    release_version = release_tag.removeprefix("v")
    files_to_upload = [str(path) for path in files if path.exists()]
    if not files_to_upload:
        raise SystemExit("No release files were found to upload.")

    view = subprocess.run([gh, "release", "view", release_tag], cwd=ROOT, check=False)
    if view.returncode == 0:
        _run([gh, "release", "upload", release_tag, *files_to_upload, "--clobber"])
        return

    _run(
        [
            gh,
            "release",
            "create",
            release_tag,
            *files_to_upload,
            "--title",
            f"{APP_NAME} {release_version}",
            "--notes",
            f"{APP_NAME} desktop release {release_version}.",
        ]
    )


def build_release(
    mode: str,
    version: str | None,
    install_deps: bool,
    skip_conflict_check: bool,
    upload_release: bool,
    tag: str | None,
) -> None:
    clean_generated_artifacts(include_deploy=True)
    build_pyinstaller(mode, install_deps, skip_conflict_check)
    archive, checksum_path = package_release(mode, version)
    if upload_release:
        upload_github_release(version, tag, [archive, checksum_path])


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Build BobSim desktop deploy artifacts.")
    parser.add_argument("--mode", choices=("onefile", "onedir"), default="onefile")
    parser.add_argument("--install-deps", action="store_true", help="Install missing deploy dependencies with pip.")
    parser.add_argument("--assets-only", action="store_true", help="Only generate deploy icon assets.")
    parser.add_argument("--clean", action="store_true", help="Remove generated artifacts and deploy outputs.")
    parser.add_argument("--release", action="store_true", help="Clean, build, and package a release artifact.")
    parser.add_argument(
        "--package-release",
        action="store_true",
        help="Package the current deploy artifact for release.",
    )
    parser.add_argument("--upload-release", action="store_true", help="Upload packaged release files with GitHub CLI.")
    parser.add_argument("--version", help="Release version to use with --package-release.")
    parser.add_argument("--tag", help="GitHub release tag to use with --upload-release.")
    parser.add_argument("--preflight-only", action="store_true", help="Only run deploy preflight checks.")
    parser.add_argument(
        "--skip-conflict-check",
        action="store_true",
        help="Allow deploy with unresolved conflict markers.",
    )
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    if args.assets_only:
        _ensure_icon_dependencies(args.install_deps)
        generate_icon_assets()
        return
    if args.clean:
        clean_generated_artifacts(include_deploy=True)
        return
    if args.preflight_only:
        preflight(skip_conflict_check=args.skip_conflict_check)
        return
    if args.release:
        build_release(
            args.mode,
            args.version,
            args.install_deps,
            args.skip_conflict_check,
            args.upload_release,
            args.tag,
        )
        return
    if args.package_release:
        archive, checksum_path = package_release(args.mode, args.version)
        if args.upload_release:
            upload_github_release(args.version, args.tag, [archive, checksum_path])
        return
    build_pyinstaller(args.mode, args.install_deps, args.skip_conflict_check)


if __name__ == "__main__":
    main()
