from __future__ import annotations

import hashlib
import json
import os
import platform
from pathlib import Path
import shutil
import sys
import time
from typing import Any, Iterable

from _5_App import storage as app_storage

PROJECT_NAME = "BobDyn"
APP_NAME = "BobSim"
PRIMARY_HOME_ENV = "BOBSIM_HOME"
LEGACY_HOME_ENV = "BOBDYN_HOME"
PACKAGE_ROOT = Path(getattr(sys, "_MEIPASS", Path(__file__).resolve().parents[1])).resolve()
FROZEN_APP = bool(getattr(sys, "frozen", False))
APP_RUNTIME_SEED_SCHEMA_VERSION = 4

APP_SEED_RUNTIME_PATHS = (
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
)


def _default_runtime_root() -> Path:
    override = os.environ.get(PRIMARY_HOME_ENV) or os.environ.get(LEGACY_HOME_ENV)
    if override:
        return Path(override).expanduser().resolve()

    system = platform.system()
    if system == "Windows":
        base = Path(os.environ.get("LOCALAPPDATA", Path.home() / "AppData" / "Local"))
    elif system == "Darwin":
        base = Path.home() / "Library" / "Application Support"
    else:
        base = Path(os.environ.get("XDG_DATA_HOME", Path.home() / ".local" / "share"))
    return (base / PROJECT_NAME / APP_NAME).resolve()


def _runtime_copy_ignore(_: str, names: list[str]) -> set[str]:
    ignored = {
        "__pycache__",
        ".pytest_cache",
        ".mypy_cache",
        ".ruff_cache",
        ".coverage",
        "htmlcov",
    }
    return {name for name in names if name in ignored or name.endswith((".pyc", ".pyo"))}


APP_REFRESH_RUNTIME_PATHS = {
    "_0_Utils/external/BobLib/BobLib",
    "_0_Utils/plotting",
    "_0_Utils/reporting",
    "_3_StandardSim/FourPostEval/four_post_eval_config.yml",
    "_3_StandardSim/RampSteerEval/ramp_steer_eval_config.yml",
    "_3_StandardSim/SteadyStateEval/steady_state_eval_config.yml",
    "_3_StandardSim/TransientEval/transient_eval_config.yml",
    "_3_StandardSim/build_vehicle_sim.mos",
    "_3_StandardSim/build_four_post_sim.mos",
}

APP_MERGE_RUNTIME_DIRS = {
    "_0_Utils/tire_templates",
    "_0_Utils/vehicle_templates",
}

APP_RUNTIME_SEED_MANIFEST_PATH = app_storage.RUNTIME_SEED_MANIFEST_PATH
APP_RESET_ON_RUNTIME_SEED_CHANGE_PATHS = (
    "_3_StandardSim/Build",
    "_3_StandardSim/BuildBobLib",
    "_3_StandardSim/generated_results",
    "_3_StandardSim/results",
    app_storage.MODELICA_BUILD_CACHE_ROOT.as_posix(),
)
APP_MODELICA_BUILD_FINGERPRINT_PATHS = (
    "_0_Utils/external/BobLib/BobLib",
    "_3_StandardSim/build_vehicle_sim.mos",
    "_3_StandardSim/build_four_post_sim.mos",
)
RUNTIME_SEED_WARNINGS: list[str] = []
WINDOWS_LOCKED_FILE_ERRORS = {5, 32, 33}


def _is_locked_file_error(exc: OSError) -> bool:
    return isinstance(exc, PermissionError) or (
        platform.system() == "Windows"
        and getattr(exc, "winerror", None) in WINDOWS_LOCKED_FILE_ERRORS
    )


def _runtime_seed_warning(message: str) -> None:
    RUNTIME_SEED_WARNINGS.append(message)
    print(f"Runtime update warning: {message}", file=sys.stderr, flush=True)


def _retry_runtime_io(description: str, operation: Any) -> bool:
    last_error: OSError | None = None
    for attempt in range(6):
        try:
            operation()
            return True
        except OSError as exc:
            if not _is_locked_file_error(exc):
                raise
            last_error = exc
            time.sleep(0.15 * (attempt + 1))
    _runtime_seed_warning(f"{description} failed because a file is in use: {last_error}")
    return False


def _remove_runtime_path(path: Path) -> bool:
    if not path.exists() and not path.is_symlink():
        return True
    if path.is_dir() and not path.is_symlink():
        return _retry_runtime_io(f"Remove {path}", lambda: shutil.rmtree(path))
    return _retry_runtime_io(f"Remove {path}", lambda: path.unlink(missing_ok=True))


def _copy_runtime_file(source: Path, target: Path) -> bool:
    target.parent.mkdir(parents=True, exist_ok=True)
    return _retry_runtime_io(f"Copy {source} to {target}", lambda: shutil.copy2(source, target))


def _copy_runtime_tree(source: Path, target: Path, *, merge: bool = False) -> bool:
    target.parent.mkdir(parents=True, exist_ok=True)
    return _retry_runtime_io(
        f"Copy {source} to {target}",
        lambda: shutil.copytree(
            source,
            target,
            symlinks=True,
            ignore=_runtime_copy_ignore,
            dirs_exist_ok=merge,
        ),
    )


def _same_file_content(source: Path, target: Path) -> bool:
    try:
        return source.read_bytes() == target.read_bytes()
    except OSError:
        return False


def _source_path_current(source: Path, target: Path) -> bool:
    if not target.exists():
        return False
    if source.is_file():
        return target.is_file() and _same_file_content(source, target)
    if not source.is_dir() or not target.is_dir():
        return False

    for source_file in sorted(item for item in source.rglob("*") if item.is_file()):
        if _runtime_copy_ignore(str(source_file.parent), [source_file.name]):
            continue
        target_file = target / source_file.relative_to(source)
        if not target_file.is_file() or not _same_file_content(source_file, target_file):
            return False
    return True


def _fingerprint_paths(root: Path, rel_paths: Iterable[str]) -> dict[str, Any]:
    digest = hashlib.sha256()
    files: list[str] = []
    for rel_path in sorted(set(rel_paths)):
        path = root / rel_path
        if not path.exists():
            digest.update(f"missing:{rel_path}\n".encode("utf-8"))
            continue
        candidates = [path] if path.is_file() else sorted(item for item in path.rglob("*") if item.is_file())
        for candidate in candidates:
            rel = candidate.relative_to(root).as_posix()
            if _runtime_copy_ignore(str(candidate.parent), [candidate.name]):
                continue
            digest.update(f"path:{rel}\n".encode("utf-8"))
            try:
                digest.update(candidate.read_bytes())
            except OSError:
                digest.update(b"<unreadable>")
            digest.update(b"\n")
            files.append(rel)
    return {
        "digest": digest.hexdigest(),
        "file_count": len(files),
    }


def _runtime_seed_manifest(package_root: Path | None = None) -> dict[str, Any]:
    package_root = package_root or PACKAGE_ROOT
    fingerprint = _fingerprint_paths(package_root, APP_REFRESH_RUNTIME_PATHS)
    return {
        "schema": APP_RUNTIME_SEED_SCHEMA_VERSION,
        "digest": fingerprint["digest"],
        "file_count": fingerprint["file_count"],
    }


def _read_runtime_seed_manifest(runtime_root: Path) -> dict[str, Any] | None:
    manifest_path = runtime_root / APP_RUNTIME_SEED_MANIFEST_PATH
    if not manifest_path.is_file():
        return None
    try:
        data = json.loads(manifest_path.read_text(encoding="utf-8"))
    except (json.JSONDecodeError, OSError):
        return None
    return data if isinstance(data, dict) else None


def _write_runtime_seed_manifest(runtime_root: Path, manifest: dict[str, Any]) -> None:
    manifest_path = runtime_root / APP_RUNTIME_SEED_MANIFEST_PATH
    manifest_path.parent.mkdir(parents=True, exist_ok=True)
    manifest_path.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")


def _runtime_seed_changed(previous: dict[str, Any] | None, current: dict[str, Any]) -> bool:
    if not previous:
        return True
    return (
        previous.get("schema") != current.get("schema")
        or previous.get("digest") != current.get("digest")
    )


def _seed_runtime_root(
    runtime_root: Path,
    *,
    package_root: Path | None = None,
    remove_runtime_path: Any | None = None,
) -> None:
    package_root = package_root or PACKAGE_ROOT
    remove_runtime_path = remove_runtime_path or _remove_runtime_path
    runtime_output_dirs = (
        "_2_EnvelopeSim/Build",
        "_2_EnvelopeSim/results",
        "_3_StandardSim/Build",
        "_3_StandardSim/BuildBobLib",
        "_3_StandardSim/generated_results",
        "_3_StandardSim/results",
        "_4_OptSim/Build",
        "_4_OptSim/results",
        "_4_OptSim/EnvelopeSens/results",
        "_4_OptSim/StandardSens/results",
        "_4_OptSim/population",
        "_4_OptSim/population_refined",
        *(path.as_posix() for path in app_storage.USER_DATA_DIRS),
    )
    runtime_root.mkdir(parents=True, exist_ok=True)
    current_seed = _runtime_seed_manifest(package_root)
    if _runtime_seed_changed(_read_runtime_seed_manifest(runtime_root), current_seed):
        for rel_path in APP_RESET_ON_RUNTIME_SEED_CHANGE_PATHS:
            remove_runtime_path(runtime_root / rel_path)

    for rel_path in APP_SEED_RUNTIME_PATHS:
        source = package_root / rel_path
        target = runtime_root / rel_path
        if not source.exists():
            continue
        target.parent.mkdir(parents=True, exist_ok=True)
        refresh = rel_path in APP_REFRESH_RUNTIME_PATHS
        merge = rel_path in APP_MERGE_RUNTIME_DIRS
        current = _source_path_current(source, target)
        if source.is_dir():
            if target.exists() and not target.is_dir():
                if not remove_runtime_path(target):
                    continue
            if refresh and target.exists() and not current:
                if not remove_runtime_path(target):
                    continue
            if target.exists():
                if merge:
                    _copy_runtime_tree(source, target, merge=True)
                continue
            _copy_runtime_tree(source, target)
        else:
            if target.is_dir():
                if not remove_runtime_path(target):
                    continue
            if target.exists() and (not refresh or current):
                continue
            _copy_runtime_file(source, target)
    for rel_path in runtime_output_dirs:
        (runtime_root / rel_path).mkdir(parents=True, exist_ok=True)
    _write_runtime_seed_manifest(runtime_root, current_seed)


def _prepare_runtime_root() -> Path:
    if not getattr(sys, "frozen", False):
        return PACKAGE_ROOT

    runtime_root = _default_runtime_root()
    _seed_runtime_root(runtime_root)
    os.chdir(runtime_root)
    return runtime_root
