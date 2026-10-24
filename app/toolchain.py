from __future__ import annotations

import json
import os
import platform
from pathlib import Path
import re
import shutil
import subprocess
import sys
import time
from typing import Any, Iterable

from app import storage as app_storage


ROOT = Path.cwd()
FROZEN_APP = bool(getattr(sys, "frozen", False))
OPENMODELICA_SETTINGS_PATH = app_storage.OPENMODELICA_SETTINGS_PATH

OPENMODELICA_OMC_ENV_KEYS = ("BOBSIM_OMC", "BOBDYN_OMC", "OMC")
OPENMODELICA_HOME_ENV_KEYS = ("BOBSIM_OPENMODELICA_HOME", "BOBDYN_OPENMODELICA_HOME", "OPENMODELICAHOME")
OPENMODELICA_LIBRARY_ENV_KEYS = (
    "BOBSIM_OPENMODELICA_LIBRARY",
    "BOBDYN_OPENMODELICA_LIBRARY",
    "OPENMODELICALIBRARY",
    "MODELICAPATH",
)
OPENMODELICA_REQUIRED_LIBRARIES = ("Modelica", "VehicleInterfaces")
OPENMODELICA_VERIFY_TIMEOUT_S = 12
OPENMODELICA_VERIFY_CACHE: dict[str, dict[str, Any]] = {}

def _prepend_env_path(env: dict[str, str], key: str, paths: Iterable[str]) -> None:
    existing = _path_list_value(env.get(key, "")) if env.get(key) else []
    env[key] = os.pathsep.join([*paths, *existing])


def _subprocess_creation_flags() -> int:
    if sys.platform == "win32":
        return getattr(subprocess, "CREATE_NO_WINDOW", 0)
    return 0

def external_toolchain_enabled() -> bool:
    return True


def _clean_path_string(value: Any) -> str:
    if value is None:
        return ""
    text = str(value).strip()
    if len(text) >= 2 and text[0] == text[-1] and text[0] in {'"', "'"}:
        text = text[1:-1].strip()
    return os.path.expandvars(os.path.expanduser(text))


def _path_list_value(value: str) -> list[str]:
    return [part for part in value.split(os.pathsep) if part.strip()]


def _path_is_within(path: Path, root: Path) -> bool:
    try:
        path.resolve().relative_to(root.resolve())
    except (OSError, ValueError):
        return False
    return True


def _strip_env_paths_under(value: str, root: Path) -> str:
    parts = [part for part in _path_list_value(value) if not _path_is_within(Path(part), root)]
    return os.pathsep.join(parts)


def _sanitize_frozen_external_env(env: dict[str, str]) -> None:
    """Remove PyInstaller private libraries before launching system tools."""
    if not FROZEN_APP:
        return
    bundle_root_raw = _clean_path_string(getattr(sys, "_MEIPASS", ""))
    bundle_root = Path(bundle_root_raw) if bundle_root_raw else None

    for key in ("LD_LIBRARY_PATH", "DYLD_LIBRARY_PATH"):
        original = env.get(f"{key}_ORIG")
        if original is not None:
            restored = _strip_env_paths_under(original, bundle_root) if bundle_root else original
            if restored:
                env[key] = restored
            else:
                env.pop(key, None)
            continue
        if bundle_root and env.get(key):
            cleaned = _strip_env_paths_under(env[key], bundle_root)
            if cleaned:
                env[key] = cleaned
            else:
                env.pop(key, None)

    if bundle_root and env.get("PATH"):
        cleaned_path = _strip_env_paths_under(env["PATH"], bundle_root)
        if cleaned_path:
            env["PATH"] = cleaned_path
        else:
            env.pop("PATH", None)


def _dedupe_paths(paths: Iterable[Path]) -> list[Path]:
    seen: set[str] = set()
    deduped: list[Path] = []
    for path in paths:
        key = str(path).casefold() if platform.system() == "Windows" else str(path)
        if key in seen:
            continue
        seen.add(key)
        deduped.append(path)
    return deduped


def _openmodelica_executable_name() -> str:
    return "omc.exe" if platform.system() == "Windows" else "omc"


def _openmodelica_settings_file() -> Path:
    return ROOT / OPENMODELICA_SETTINGS_PATH


def _read_openmodelica_settings() -> dict[str, str]:
    path = _openmodelica_settings_file()
    if not path.is_file():
        return {}
    data = json.loads(path.read_text(encoding="utf-8"))
    if not isinstance(data, dict):
        return {}
    settings: dict[str, str] = {}
    for key in ("omc_path", "openmodelica_home", "library_path", "verified_at", "omc_version"):
        value = _clean_path_string(data.get(key))
        if value:
            settings[key] = value
    return settings


def _write_openmodelica_settings(settings: dict[str, str]) -> None:
    path = _openmodelica_settings_file()
    if not settings:
        _remove_file(path)
        return
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(settings, indent=2) + "\n", encoding="utf-8")


def _remove_file(path: Path) -> None:
    try:
        path.unlink()
    except FileNotFoundError:
        pass


def _first_env_value(keys: Iterable[str]) -> tuple[str, str] | tuple[None, None]:
    for key in keys:
        value = _clean_path_string(os.environ.get(key))
        if value:
            return value, f"env:{key}"
    return None, None


def _configured_path(
    settings: dict[str, str],
    setting_key: str,
    env_keys: Iterable[str],
) -> tuple[str, str] | tuple[None, None]:
    value = _clean_path_string(settings.get(setting_key))
    if value:
        return value, "saved"
    return _first_env_value(env_keys)


def _path_info(path: str | Path | None, source: str, *, error: str = "") -> dict[str, Any]:
    if path is None:
        return {"path": None, "source": source, "exists": False, "error": error}
    candidate = Path(path)
    exists = candidate.exists()
    return {"path": str(candidate), "source": source, "exists": exists, "error": error}


def _user_path(path: str | Path) -> Path:
    text = _clean_path_string(path)
    if platform.system() == "Windows":
        text = text.replace("\\", "/")
        match = re.match(r"^/([A-Za-z])/(.+)$", text)
        if match:
            text = f"{match.group(1).upper()}:/{match.group(2)}"
    return Path(text)


def _program_files_dirs() -> list[Path]:
    roots = []
    for key in ("ProgramFiles", "ProgramFiles(x86)"):
        value = _clean_path_string(os.environ.get(key))
        if value:
            roots.append(Path(value))
    roots.extend([Path("C:/Program Files"), Path("C:/Program Files (x86)")])
    return _dedupe_paths(roots)


def _common_openmodelica_homes() -> list[Path]:
    system = platform.system()
    homes: list[Path] = []
    if system == "Windows":
        for root in _program_files_dirs():
            if root.exists():
                homes.extend(sorted(root.glob("OpenModelica*")))
        homes.extend([Path("C:/OpenModelica"), Path("C:/Program Files/OpenModelica")])
    elif system == "Darwin":
        homes.extend(
            [
                Path("/Applications/OpenModelica.app/Contents/Resources"),
                Path("/opt/openmodelica"),
                Path("/opt/homebrew"),
                Path("/usr/local"),
            ]
        )
    else:
        homes.extend([Path("/usr"), Path("/usr/local"), Path("/opt/openmodelica"), Path("/snap/openmodelica/current")])
    return _dedupe_paths(homes)


def _common_omc_candidates(home: str | None = None) -> list[Path]:
    exe_name = _openmodelica_executable_name()
    candidates: list[Path] = []
    if home:
        candidates.append(Path(home) / "bin" / exe_name)
    for candidate_home in _common_openmodelica_homes():
        candidates.append(candidate_home / "bin" / exe_name)
    if platform.system() != "Windows":
        candidates.extend([Path("/usr/bin/omc"), Path("/usr/local/bin/omc"), Path("/opt/openmodelica/bin/omc")])
    return _dedupe_paths(candidates)


def _openmodelica_user_library_dirs() -> list[Path]:
    if platform.system() == "Windows":
        candidates: list[Path] = []
        appdata = _clean_path_string(os.environ.get("APPDATA"))
        if appdata:
            candidates.append(_user_path(appdata) / ".openmodelica" / "libraries")
        candidates.append(Path.home() / "AppData" / "Roaming" / ".openmodelica" / "libraries")
        return _dedupe_paths(candidates)
    return [Path.home() / ".openmodelica" / "libraries"]


def _common_openmodelica_libraries(home: str | None = None) -> list[Path]:
    candidates: list[Path] = []
    if home:
        candidates.append(_user_path(home) / "lib" / "omlibrary")
    candidates.extend(_openmodelica_user_library_dirs())
    for candidate_home in _common_openmodelica_homes():
        candidates.append(candidate_home / "lib" / "omlibrary")
    if platform.system() != "Windows":
        candidates.extend(
            [
                Path("/usr/lib/omlibrary"),
                Path("/usr/local/lib/omlibrary"),
                Path("/opt/openmodelica/lib/omlibrary"),
            ]
        )
    return _dedupe_paths(candidates)


def _is_omc_file(path: Path) -> bool:
    if not path.is_file():
        return False
    if platform.system() == "Windows":
        return path.name.lower() == "omc.exe"
    return os.access(path, os.X_OK) or path.name == "omc"


def _omc_path_candidates(path: str | Path) -> list[Path]:
    base = _user_path(path)
    exe_name = _openmodelica_executable_name()
    candidates = [base]
    if base.is_dir():
        if base.name.lower() == "bin":
            candidates.append(base / exe_name)
        else:
            candidates.append(base / "bin" / exe_name)
    elif platform.system() == "Windows" and base.name.lower() == "omc":
        candidates.append(base.with_name("omc.exe"))
    return _dedupe_paths(candidates)


def _normalize_omc_path(path: str | Path) -> Path:
    candidates = _omc_path_candidates(path)
    return next((candidate for candidate in candidates if _is_omc_file(candidate)), candidates[0])


def _resolve_omc_path(settings: dict[str, str], home: str | None = None) -> dict[str, Any]:
    configured, source = _configured_path(settings, "omc_path", OPENMODELICA_OMC_ENV_KEYS)
    if configured:
        path = _normalize_omc_path(configured)
        error = "" if _is_omc_file(path) else f"Configured omc executable was not found or is not executable: {path}"
        return _path_info(path, source or "saved", error=error)

    if home:
        home_candidate = _user_path(home) / "bin" / _openmodelica_executable_name()
        if _is_omc_file(home_candidate):
            return _path_info(home_candidate, "openmodelica-home")

    which_path = shutil.which("omc")
    if which_path:
        return {"path": which_path, "source": "PATH", "exists": True, "error": ""}

    for candidate in _common_omc_candidates(home):
        if _is_omc_file(candidate):
            return _path_info(candidate, "default")
    return {
        "path": None,
        "source": "not-found",
        "exists": False,
        "error": "OpenModelica omc was not found. Install OpenModelica or set the omc path.",
    }


def _infer_openmodelica_home(omc_path: str | None) -> str | None:
    if not omc_path:
        return None
    if platform.system() == "Linux":
        return None
    path = _user_path(omc_path)
    if path.parent.name.lower() == "bin":
        return str(path.parent.parent)
    return None


def _resolve_openmodelica_home(settings: dict[str, str], omc_path: str | None) -> dict[str, Any]:
    configured, source = _configured_path(settings, "openmodelica_home", OPENMODELICA_HOME_ENV_KEYS)
    if configured:
        path = _user_path(configured)
        error = "" if path.is_dir() else f"Configured OpenModelica home directory was not found: {path}"
        return _path_info(path, source or "saved", error=error)

    inferred = _infer_openmodelica_home(omc_path)
    if inferred and Path(inferred).is_dir():
        return _path_info(inferred, "omc")
    if inferred:
        return _path_info(inferred, "omc")
    return {"path": None, "source": "not-found", "exists": False, "error": ""}


def _configured_library_candidates(settings: dict[str, str]) -> list[tuple[str, str]]:
    saved = _clean_path_string(settings.get("library_path"))
    if saved:
        return [(saved, "saved")]
    for key in OPENMODELICA_LIBRARY_ENV_KEYS:
        value = _clean_path_string(os.environ.get(key))
        if not value:
            continue
        if key == "MODELICAPATH":
            return [(part, f"env:{key}") for part in _path_list_value(value)]
        return [(value, f"env:{key}")]
    return []


def _resolve_openmodelica_library(settings: dict[str, str], home: str | None) -> dict[str, Any]:
    configured_candidates = _configured_library_candidates(settings)
    for configured, source in configured_candidates:
        path = _user_path(configured)
        if path.is_dir():
            return _path_info(path, source)
    if configured_candidates:
        configured, source = configured_candidates[0]
        path = _user_path(configured)
        return _path_info(path, source, error=f"Configured OpenModelica library directory was not found: {path}")

    existing_candidates = [candidate for candidate in _common_openmodelica_libraries(home) if candidate.is_dir()]
    for candidate in existing_candidates:
        if not _missing_openmodelica_libraries(candidate):
            return _path_info(candidate, "default")
    if existing_candidates:
        return _path_info(existing_candidates[0], "default")
    return {"path": None, "source": "omc-default", "exists": False, "error": ""}


def _openmodelica_selection_complete(settings: dict[str, str]) -> bool:
    return bool(settings.get("omc_path") and settings.get("library_path"))


def _openmodelica_selection_verified(settings: dict[str, str]) -> bool:
    return bool(settings.get("verified_at") and settings.get("omc_version"))


def _library_contains_package(library_path: Path, package_name: str) -> bool:
    if not library_path.is_dir():
        return False
    direct = library_path / package_name / "package.mo"
    if direct.is_file():
        return True
    for child in library_path.glob(f"{package_name}*"):
        if child.is_dir():
            if (child / "package.mo").is_file():
                return True
            if (child / package_name / "package.mo").is_file():
                return True
    return False


def _missing_openmodelica_libraries(library_path: Path) -> list[str]:
    return [
        package_name
        for package_name in OPENMODELICA_REQUIRED_LIBRARIES
        if not _library_contains_package(library_path, package_name)
    ]


def _apply_openmodelica_env_paths(
    env: dict[str, str],
    *,
    omc_path: str | None,
    home: str | None,
    library: str | None,
) -> None:
    if omc_path:
        _prepend_env_path(env, "PATH", [str(Path(str(omc_path)).parent)])
    if home:
        env["OPENMODELICAHOME"] = str(home)
        home_path = Path(str(home))
        runtime_libs = [str(home_path / "lib"), str(home_path / "lib" / "omc")]
        if platform.system() == "Darwin":
            _prepend_env_path(env, "DYLD_LIBRARY_PATH", runtime_libs)
        elif platform.system() == "Windows":
            _prepend_env_path(
                env,
                "PATH",
                [
                    str(home_path / "bin"),
                    str(home_path / "lib"),
                    str(home_path / "tools" / "msys" / "mingw64" / "bin"),
                    str(home_path / "tools" / "msys" / "ucrt64" / "bin"),
                    str(home_path / "tools" / "msys" / "usr" / "bin"),
                ],
            )
        else:
            _prepend_env_path(env, "LD_LIBRARY_PATH", runtime_libs)
    if library:
        env["OPENMODELICALIBRARY"] = str(library)
        _prepend_env_path(env, "MODELICAPATH", [str(library)])


def _verify_openmodelica_selection(settings: dict[str, str]) -> dict[str, str]:
    omc_path = settings.get("omc_path", "")
    library_path = settings.get("library_path", "")
    home_path = settings.get("openmodelica_home", "")
    if omc_path:
        omc_path = str(_normalize_omc_path(omc_path))

    if not omc_path:
        raise ValueError("Select an omc executable before enabling Simulation.")
    if not _is_omc_file(Path(omc_path)):
        raise ValueError(f"omc executable was not found or is not executable: {omc_path}")
    if home_path and not Path(home_path).is_dir():
        raise ValueError(f"OpenModelica home directory was not found: {home_path}")
    if not library_path:
        raise ValueError("Select the OpenModelica library directory before enabling Simulation.")
    library_root = Path(library_path)
    if not library_root.is_dir():
        raise ValueError(f"OpenModelica library directory was not found: {library_path}")

    missing_libraries = _missing_openmodelica_libraries(library_root)
    if missing_libraries:
        missing = ", ".join(missing_libraries)
        raise ValueError(f"OpenModelica library directory is missing required packages: {missing}")

    env = os.environ.copy()
    _sanitize_frozen_external_env(env)
    _apply_openmodelica_env_paths(env, omc_path=omc_path, home=home_path or None, library=library_path)
    try:
        completed = subprocess.run(
            [omc_path, "--version"],
            cwd=ROOT,
            env=env,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            timeout=OPENMODELICA_VERIFY_TIMEOUT_S,
            check=False,
            creationflags=_subprocess_creation_flags(),
        )
    except subprocess.TimeoutExpired as exc:
        raise ValueError(f"omc verification timed out after {OPENMODELICA_VERIFY_TIMEOUT_S} seconds.") from exc
    except OSError as exc:
        raise ValueError(f"omc verification failed: {exc}") from exc

    output = (completed.stdout or "").strip()
    if completed.returncode != 0:
        detail = output or f"exit code {completed.returncode}"
        raise ValueError(f"omc verification failed: {detail}")

    verified = dict(settings)
    verified["omc_path"] = omc_path
    verified["omc_version"] = output.splitlines()[0].strip() if output else "OpenModelica"
    verified["verified_at"] = time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())
    return verified


def _openmodelica_verify_cache_key(settings: dict[str, str]) -> str:
    return "\n".join(
        [
            settings.get("omc_path", ""),
            settings.get("openmodelica_home", ""),
            settings.get("library_path", ""),
        ]
    )


def _verify_openmodelica_selection_cached(settings: dict[str, str]) -> tuple[dict[str, str] | None, str]:
    key = _openmodelica_verify_cache_key(settings)
    cached = OPENMODELICA_VERIFY_CACHE.get(key)
    if cached:
        if cached.get("ok"):
            return dict(cached["settings"]), ""
        return None, str(cached.get("error") or "OpenModelica verification failed.")
    try:
        verified = _verify_openmodelica_selection(settings)
    except ValueError as exc:
        OPENMODELICA_VERIFY_CACHE[key] = {"ok": False, "error": str(exc)}
        return None, str(exc)
    OPENMODELICA_VERIFY_CACHE[key] = {"ok": True, "settings": verified}
    return verified, ""


def _openmodelica_settings_from_payload(payload: dict[str, Any]) -> dict[str, str]:
    requested: dict[str, str] = {}
    for key in ("omc_path", "openmodelica_home", "library_path"):
        value = _clean_path_string(payload.get(key))
        if value:
            requested[key] = value

    home_hint = requested.get("openmodelica_home")
    omc = _resolve_omc_path(requested, home_hint)
    if omc.get("path"):
        requested["omc_path"] = str(omc["path"])

    library = _resolve_openmodelica_library(requested, requested.get("openmodelica_home"))
    if not requested.get("library_path") and library.get("path"):
        requested["library_path"] = str(library["path"])

    return requested


def openmodelica_toolchain_payload() -> dict[str, Any]:
    saved_settings = _read_openmodelica_settings()
    detected_settings = _openmodelica_settings_from_payload(saved_settings)
    home_configured, _home_source = _configured_path(saved_settings, "openmodelica_home", OPENMODELICA_HOME_ENV_KEYS)
    omc = _resolve_omc_path(saved_settings, home_configured)
    home = _resolve_openmodelica_home(saved_settings, omc.get("path"))
    library = _resolve_openmodelica_library(saved_settings, home.get("path"))
    errors = [item["error"] for item in (omc, home, library) if item.get("error")]
    selected = _openmodelica_selection_complete(detected_settings)
    saved = _openmodelica_selection_complete(saved_settings)
    verified_settings: dict[str, str] | None = None
    verification_error = ""
    if selected and not errors:
        if saved and _openmodelica_selection_verified(saved_settings):
            verified_settings = {
                **detected_settings,
                "verified_at": saved_settings.get("verified_at", ""),
                "omc_version": saved_settings.get("omc_version", ""),
            }
        else:
            verified_settings, verification_error = _verify_openmodelica_selection_cached(detected_settings)
    verified = verified_settings is not None
    available = verified and not errors
    if available:
        reason = "OpenModelica toolchain available."
    elif not selected:
        reason = "OpenModelica was not auto-detected. Select an OpenModelica toolchain before running simulations."
    elif errors:
        reason = errors[0]
    elif not library.get("path"):
        reason = "Select the OpenModelica library directory before running simulations."
    elif verification_error:
        reason = verification_error
    else:
        reason = "OpenModelica toolchain is not ready."
    return {
        "available": available,
        "enabled": external_toolchain_enabled(),
        "frozen": FROZEN_APP,
        "selected": selected,
        "saved": saved,
        "verified": verified,
        "verified_at": (verified_settings or detected_settings).get("verified_at"),
        "omc_version": (verified_settings or detected_settings).get("omc_version"),
        "omc": omc.get("path"),
        "omc_source": omc.get("source"),
        "openmodelica_home": home.get("path"),
        "openmodelica_home_source": home.get("source"),
        "openmodelica_library": library.get("path"),
        "openmodelica_library_source": library.get("source"),
        "settings": saved_settings,
        "detected_settings": detected_settings,
        "env_keys": {
            "omc": list(OPENMODELICA_OMC_ENV_KEYS),
            "home": list(OPENMODELICA_HOME_ENV_KEYS),
            "library": list(OPENMODELICA_LIBRARY_ENV_KEYS),
        },
        "omc_candidates": [
            {"path": str(path), "exists": _is_omc_file(path)}
            for path in _common_omc_candidates(home.get("path"))
        ],
        "library_candidates": [
            {"path": str(path), "exists": path.is_dir()}
            for path in _common_openmodelica_libraries(home.get("path"))
        ],
        "reason": reason,
    }


def save_openmodelica_toolchain_settings(payload: dict[str, Any]) -> dict[str, Any]:
    if payload.get("reset"):
        _write_openmodelica_settings({})
        return openmodelica_toolchain_payload()

    settings = _verify_openmodelica_selection(_openmodelica_settings_from_payload(payload))
    _write_openmodelica_settings(settings)
    return openmodelica_toolchain_payload()


def external_toolchain_available() -> bool:
    return external_toolchain_enabled() and openmodelica_toolchain_payload()["available"]


def external_toolchain_payload() -> dict[str, Any]:
    return openmodelica_toolchain_payload()

