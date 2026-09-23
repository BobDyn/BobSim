from __future__ import annotations

import hashlib
import json
import platform
from pathlib import Path
import shutil
import time
from typing import Any
import uuid

from _5_App.contracts import ActionSpec, BuildTargetSpec
from _5_App.modelica_generator import modelica_stack_status_payload
from _5_App.registry import BUILD_METADATA_FILENAME
from _5_App import storage as app_storage


ROOT = Path.cwd()
BUILD_ARCHIVE_ROOT = app_storage.BUILD_ARCHIVE_ROOT
MODELICA_BUILD_CACHE_ROOT = app_storage.MODELICA_BUILD_CACHE_ROOT
APP_MODELICA_BUILD_FINGERPRINT_PATHS: tuple[str, ...] = ()
ACTION_SPECS: dict[str, ActionSpec] = {}
JOBS: Any = None


def _safe_repo_path(raw_path: str | Path) -> Path:
    return (ROOT / raw_path).resolve()


def _path_payload(_raw_path: str) -> dict[str, Any]:
    return {}


def _fingerprint_paths(_root: Path, _rel_paths: tuple[str, ...]) -> dict[str, Any]:
    return {"digest": "", "file_count": 0}


def action_available(_action: ActionSpec) -> bool:
    return True


def unavailable_action_reason(_action: ActionSpec) -> str:
    return ""


def _run_subprocess_action(_action: ActionSpec, _job_id: str) -> int:
    raise RuntimeError("Subprocess runner has not been connected")


def _modelica_build_payload(
    raw_path: str,
    stack: dict[str, Any] | None,
    target: BuildTargetSpec | None = None,
) -> dict[str, Any]:
    path_payload = _path_payload(raw_path)
    if target and not action_available(ACTION_SPECS[target.action_id]):
        return {
            **path_payload,
            "state": "disabled",
            "label": "Unavailable",
            "signature": None,
            "current_signature": None,
            "archive": None,
            "unavailable_reason": unavailable_action_reason(ACTION_SPECS[target.action_id]),
        }
    path = _safe_repo_path(raw_path)
    exists = path.is_file()
    written = bool(stack and stack.get("written_to_boblib"))
    latest_modelica = float(stack.get("latest_modified") or 0.0) if stack else 0.0
    modified = float(path_payload.get("modified") or 0.0)
    signature_payload = None
    archive_payload = None
    current_signature = None
    has_build_metadata = False
    if target and stack:
        try:
            signature_payload = _modelica_build_signature_payload(target, stack)
            archive_payload = _modelica_archive_payload(target, signature_payload)
            metadata = _read_modelica_build_metadata(_safe_repo_path(target.build_dir))
            has_build_metadata = metadata is not None
            current_signature = metadata.get("signature") if metadata else None
        except Exception:
            signature_payload = None
            archive_payload = None
    if not written:
        state = "waiting"
        label = "Write first"
    elif exists and signature_payload and current_signature == signature_payload["signature"]:
        state = "built"
        label = "Built"
    elif exists and signature_payload and has_build_metadata:
        state = "stale"
        label = "Rebuild needed"
    elif archive_payload and archive_payload.get("ready"):
        state = "cached"
        label = "Cache ready"
    elif not exists:
        state = "missing"
        label = "Build pending"
    elif latest_modelica and modified < latest_modelica:
        state = "stale"
        label = "Rebuild needed"
    else:
        state = "built"
        label = "Built"
    return {
        **path_payload,
        "state": state,
        "label": label,
        "signature": signature_payload.get("signature") if signature_payload else None,
        "current_signature": current_signature,
        "archive": archive_payload,
    }



def _modelica_build_exe_names(target: BuildTargetSpec) -> tuple[str, ...]:
    exe_name = target.exec_name
    names = [exe_name]
    if not exe_name.lower().endswith(".exe"):
        windows_name = f"{exe_name}.exe"
        if platform.system() == "Windows":
            names.insert(0, windows_name)
        else:
            names.append(windows_name)
    return tuple(dict.fromkeys(names))


def _modelica_build_exe_file(target: BuildTargetSpec, build_dir: Path | None = None) -> Path | None:
    directory = build_dir or _safe_repo_path(target.build_dir)
    for name in _modelica_build_exe_names(target):
        candidate = directory / name
        if candidate.is_file():
            return candidate
    return None


def _modelica_build_exe_path(target: BuildTargetSpec) -> str:
    exe_file = _modelica_build_exe_file(target)
    if exe_file is not None:
        return exe_file.relative_to(ROOT).as_posix()
    return f"{target.build_dir}/{_modelica_build_exe_names(target)[0]}"


def _modelica_build_init_name(target: BuildTargetSpec) -> str:
    return f"{target.exec_name}_init.xml"


def _modelica_build_missing_files(target: BuildTargetSpec, build_dir: Path | None = None) -> list[str]:
    directory = build_dir or _safe_repo_path(target.build_dir)
    missing: list[str] = []
    if _modelica_build_exe_file(target, directory) is None:
        missing.append("one executable: " + " or ".join(_modelica_build_exe_names(target)))
    init_name = _modelica_build_init_name(target)
    if not (directory / init_name).is_file():
        missing.append(init_name)
    return missing


def _host_build_fingerprint() -> dict[str, str]:
    fingerprint = {
        "system": platform.system(),
        "machine": platform.machine(),
        "processor": platform.processor(),
    }
    cpuinfo = Path("/proc/cpuinfo")
    if cpuinfo.is_file():
        for line in cpuinfo.read_text(encoding="utf-8", errors="ignore").splitlines():
            if line.lower().startswith("model name"):
                _, _, value = line.partition(":")
                fingerprint["cpu_model"] = value.strip()
                break
    return fingerprint


def _sha256_text(text: str) -> str:
    return hashlib.sha256(text.encode("utf-8")).hexdigest()


def _modelica_build_signature_payload(
    target: BuildTargetSpec,
    stack: dict[str, Any] | None = None,
) -> dict[str, Any]:
    stack_payload = stack or modelica_stack_status_payload(_safe_repo_path("vehicle.yml"), ROOT)
    generated = stack_payload.get("signatures", {}).get(target.id, {}).get("generated")
    if not generated:
        raise ValueError(f"Missing generated Modelica signature for {target.label}")
    script_path = _safe_repo_path(target.script)
    script_text = script_path.read_text(encoding="utf-8", errors="replace")
    host = _host_build_fingerprint()
    modelica_sources = _fingerprint_paths(ROOT, APP_MODELICA_BUILD_FINGERPRINT_PATHS)
    inputs = {
        "version": 2,
        "target": target.id,
        "label": target.label,
        "exec_name": target.exec_name,
        "generated_signature": generated,
        "script_sha256": _sha256_text(script_text),
        "modelica_source_digest": modelica_sources["digest"],
        "modelica_source_file_count": modelica_sources["file_count"],
        "host": host,
    }
    signature = hashlib.sha256(json.dumps(inputs, sort_keys=True).encode("utf-8")).hexdigest()
    return {
        "signature": signature,
        "inputs": inputs,
        "generated_signature": generated,
        "script_path": target.script,
        "script_sha256": inputs["script_sha256"],
        "modelica_source_digest": modelica_sources["digest"],
        "modelica_source_file_count": modelica_sources["file_count"],
        "host": host,
    }


def _modelica_build_archive_dir(target: BuildTargetSpec, signature: str) -> Path:
    return _safe_repo_path(MODELICA_BUILD_CACHE_ROOT / target.id / signature)


def _staging_dir(parent: Path, name: str, kind: str) -> Path:
    """Temporary sibling directory, renamed into place when complete.

    The name is truncated to stay under the Windows 260-character path limit.
    """
    return parent / f".{name[:8]}.{kind}-{uuid.uuid4().hex[:8]}"


def _modelica_build_dir_ready(target: BuildTargetSpec, build_dir: Path | None = None) -> bool:
    directory = build_dir or _safe_repo_path(target.build_dir)
    return not _modelica_build_missing_files(target, directory)


def _ensure_modelica_build_directory(target: BuildTargetSpec, job_id: str | None = None) -> Path:
    build_dir = _safe_repo_path(target.build_dir)
    build_dir.mkdir(parents=True, exist_ok=True)
    if job_id:
        JOBS.append_log(job_id, f"Ensured {target.label} build directory: {target.build_dir}\n")
    return build_dir


def _modelica_build_metadata_path(build_dir: Path) -> Path:
    return build_dir / BUILD_METADATA_FILENAME


def _read_modelica_build_metadata(build_dir: Path) -> dict[str, Any] | None:
    path = _modelica_build_metadata_path(build_dir)
    if not path.is_file():
        return None
    try:
        data = json.loads(path.read_text(encoding="utf-8"))
    except (json.JSONDecodeError, OSError):
        return None
    return data if isinstance(data, dict) else None


def _write_modelica_build_metadata(
    target: BuildTargetSpec,
    signature: dict[str, Any],
    *,
    source: str,
    build_dir: Path | None = None,
) -> dict[str, Any]:
    directory = build_dir or _safe_repo_path(target.build_dir)
    metadata = {
        "target": target.id,
        "label": target.label,
        "exec_name": target.exec_name,
        "build_dir": target.build_dir,
        "source": source,
        "signature": signature["signature"],
        "signature_inputs": signature.get("inputs", {}),
        "created_at": time.time(),
        "created_label": time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()),
    }
    directory.mkdir(parents=True, exist_ok=True)
    _modelica_build_metadata_path(directory).write_text(json.dumps(metadata, indent=2), encoding="utf-8")
    return metadata


def _modelica_archive_ignore(_directory: str, names: list[str]) -> set[str]:
    ignored = {"results", "__pycache__"}
    for name in names:
        if name.endswith((".csv", ".mat", ".log")) or "_prof." in name:
            ignored.add(name)
    return ignored


def _modelica_archive_payload(target: BuildTargetSpec, signature: dict[str, Any] | None) -> dict[str, Any] | None:
    if not signature:
        return None
    archive_dir = _modelica_build_archive_dir(target, str(signature["signature"]))
    files_dir = archive_dir / "files"
    rel = archive_dir.relative_to(ROOT).as_posix() if ROOT in archive_dir.parents else archive_dir.as_posix()
    manifest = archive_dir / "manifest.json"
    return {
        "signature": signature["signature"],
        "path": rel,
        "exists": archive_dir.is_dir(),
        "ready": _modelica_build_dir_ready(target, files_dir),
        "manifest": manifest.relative_to(ROOT).as_posix() if manifest.is_file() else None,
    }


def _store_modelica_build_archive(
    target: BuildTargetSpec,
    signature: dict[str, Any],
    job_id: str | None = None,
) -> bool:
    build_dir = _safe_repo_path(target.build_dir)
    if not _modelica_build_dir_ready(target, build_dir):
        return False

    _write_modelica_build_metadata(target, signature, source="local-build", build_dir=build_dir)
    archive_dir = _modelica_build_archive_dir(target, str(signature["signature"]))
    files_dir = archive_dir / "files"
    if _modelica_build_dir_ready(target, files_dir):
        return True

    parent = archive_dir.parent
    parent.mkdir(parents=True, exist_ok=True)
    tmp_dir = _staging_dir(parent, archive_dir.name, "tmp")
    try:
        shutil.copytree(build_dir, tmp_dir / "files", symlinks=True, ignore=_modelica_archive_ignore)
        manifest = {
            "target": target.id,
            "label": target.label,
            "signature": signature["signature"],
            "signature_inputs": signature.get("inputs", {}),
            "source_build_dir": target.build_dir,
            "created_at": time.time(),
            "created_label": time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()),
        }
        (tmp_dir / "manifest.json").write_text(json.dumps(manifest, indent=2), encoding="utf-8")
        if archive_dir.exists():
            shutil.rmtree(archive_dir)
        tmp_dir.rename(archive_dir)
        if job_id:
            JOBS.append_log(
                job_id,
                f"Archived {target.label} build: {archive_dir.relative_to(ROOT).as_posix()}\n",
            )
        return True
    finally:
        if tmp_dir.exists():
            shutil.rmtree(tmp_dir, ignore_errors=True)


def _restore_modelica_build_from_archive(
    target: BuildTargetSpec,
    signature: dict[str, Any],
    job_id: str | None = None,
) -> bool:
    archive_dir = _modelica_build_archive_dir(target, str(signature["signature"]))
    files_dir = archive_dir / "files"
    if not _modelica_build_dir_ready(target, files_dir):
        return False

    build_dir = _safe_repo_path(target.build_dir)
    build_dir.parent.mkdir(parents=True, exist_ok=True)
    tmp_dir = _staging_dir(build_dir.parent, build_dir.name, "restore")
    try:
        shutil.copytree(files_dir, tmp_dir, symlinks=True)
        _write_modelica_build_metadata(target, signature, source="archive", build_dir=tmp_dir)
        if build_dir.exists():
            shutil.rmtree(build_dir)
        tmp_dir.rename(build_dir)
        if job_id:
            JOBS.append_log(
                job_id,
                f"Restored {target.label} build from archive: {archive_dir.relative_to(ROOT).as_posix()}\n",
            )
        return True
    finally:
        if tmp_dir.exists():
            shutil.rmtree(tmp_dir, ignore_errors=True)


def _modelica_existing_build_matches(
    target: BuildTargetSpec,
    signature: dict[str, Any],
    stack: dict[str, Any],
) -> bool:
    build_dir = _safe_repo_path(target.build_dir)
    if not _modelica_build_dir_ready(target, build_dir):
        return False
    metadata = _read_modelica_build_metadata(build_dir)
    if metadata:
        return metadata.get("signature") == signature["signature"]

    exe_path = _modelica_build_exe_file(target, build_dir)
    if exe_path is None:
        return False
    script_path = _safe_repo_path(target.script)
    latest_input_modified = max(
        float(stack.get("latest_modified") or 0.0),
        script_path.stat().st_mtime if script_path.is_file() else 0.0,
    )
    return bool(stack.get("written_to_boblib")) and exe_path.stat().st_mtime >= latest_input_modified


def _run_modelica_build_action(action: ActionSpec, target: BuildTargetSpec, job_id: str) -> int:
    JOBS.append_log(job_id, f"\n# {target.label} build cache\n")
    _ensure_modelica_build_directory(target, job_id)
    try:
        stack = modelica_stack_status_payload(_safe_repo_path("vehicle.yml"), ROOT)
        signature = _modelica_build_signature_payload(target, stack)
    except Exception as exc:
        JOBS.append_log(job_id, f"Build cache unavailable: {type(exc).__name__}: {exc}\n")
        return _run_subprocess_action(action, job_id)

    short_signature = str(signature["signature"])[:12]
    if not stack.get("written_to_boblib"):
        JOBS.append_log(job_id, "BobLib vehicle definition is not current; running build directly.\n")
        return _run_subprocess_action(action, job_id)

    if _restore_modelica_build_from_archive(target, signature, job_id):
        JOBS.append_log(job_id, f"{target.label} cache hit ({short_signature}); skipped OpenModelica build.\n")
        return 0

    if _modelica_existing_build_matches(target, signature, stack):
        JOBS.append_log(job_id, f"{target.label} already matches signature {short_signature}; archiving local build.\n")
        _store_modelica_build_archive(target, signature, job_id)
        return 0

    JOBS.append_log(job_id, f"{target.label} cache miss ({short_signature}); running OpenModelica build.\n")
    returncode = _run_subprocess_action(action, job_id)
    if returncode == 0:
        if _store_modelica_build_archive(target, signature, job_id):
            JOBS.append_log(job_id, f"{target.label} build archived for signature {short_signature}.\n")
        else:
            missing = ", ".join(_modelica_build_missing_files(target)) or "unknown artifacts"
            JOBS.append_log(
                job_id,
                f"{target.label} build completed, but required build artifacts were missing "
                f"in {target.build_dir}: {missing}. Stopping before simulation run.\n",
            )
            return 1
    return returncode
