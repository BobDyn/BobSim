"""Shared helpers for BobSim vehicle YAML and tire-template inputs."""

from __future__ import annotations

from collections.abc import Mapping
from pathlib import Path
from typing import Any
import re
import os
import platform
import sys

import yaml


PROJECT_NAME = "BobDyn"
APP_NAME = "BobSim"
PRIMARY_HOME_ENV = "BOBSIM_HOME"
LEGACY_HOME_ENV = "BOBDYN_HOME"


def default_runtime_root() -> Path:
    """## Desktop Data Directory

    Returns
    -------
    Path
        User-selected or platform-default directory for mutable app data.
    """
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


def repo_root() -> Path:
    """## Working Data Root

    Returns
    -------
    Path
        Desktop runtime directory when bundled, otherwise the source checkout.
    """
    if getattr(sys, "frozen", False):
        return default_runtime_root()
    return Path(__file__).resolve().parents[1]


# A consumer brings its own car and its own output folder through these, so a
# run never has to copy a vehicle into this checkout or write results into it.
VEHICLE_ENV = "BOBSIM_VEHICLE"
OUTPUT_ENV = "BOBSIM_OUT"
# Generated paths are written as repo-relative strings under this prefix. With
# BOBSIM_OUT set, the part after it moves under the output folder.
GENERATED_PREFIX = Path("simulations/mbd")


def _env_path(name: str) -> Path | None:
    raw = os.environ.get(name, "").strip()
    return Path(raw).expanduser().resolve() if raw else None


def repo_vehicle_yaml_path() -> Path:
    """## Checked-in Vehicle

    Returns
    -------
    Path
        The ``vehicle.yml`` in this checkout, whatever ``BOBSIM_VEHICLE`` says.
    """
    return repo_root() / "vehicle.yml"


def vehicle_yaml_path() -> Path:
    """## Active Vehicle

    Returns
    -------
    Path
        ``BOBSIM_VEHICLE`` when set (relative paths resolve against the current
        directory), otherwise the checked-in ``vehicle.yml``. Relative paths
        *inside* the file still resolve against the BobSim checkout.
    """
    return _env_path(VEHICLE_ENV) or repo_vehicle_yaml_path()


def external_vehicle() -> bool:
    """True when ``BOBSIM_VEHICLE`` names a file other than the checked-in one."""
    override = _env_path(VEHICLE_ENV)
    return override is not None and override != repo_vehicle_yaml_path().resolve()


def active_vehicle(path: str | Path) -> Path:
    """## Swap The Checked-in Vehicle

    Parameters
    ----------
    path : str | Path
        A vehicle path a workflow was about to read, usually from its config.

    Returns
    -------
    Path
        ``BOBSIM_VEHICLE`` when it is set and ``path`` is the checked-in ``vehicle.yml``,
        otherwise ``path`` unchanged. A config that names some other vehicle on
        purpose keeps it.
    """
    candidate = Path(path)
    override = _env_path(VEHICLE_ENV)
    if override is not None and candidate.resolve() == repo_vehicle_yaml_path().resolve():
        return override
    return candidate


def output_root() -> Path | None:
    """``BOBSIM_OUT`` as an absolute path, or None when results stay in the checkout."""
    return _env_path(OUTPUT_ENV)


def output_path(path: str | Path) -> Path:
    """## Generated Output Location

    Parameters
    ----------
    path : str | Path
        A generated path as the configs write it, such as
        ``simulations/mbd/generated_results/x.pdf``, or the same path made
        absolute under this checkout.

    Returns
    -------
    Path
        With ``BOBSIM_OUT`` unset, ``path`` unchanged. With it set, a path under
        ``simulations/mbd/`` moves to the same place under ``BOBSIM_OUT``
        (``$BOBSIM_OUT/generated_results/x.pdf``). Other paths are unchanged.
    """
    candidate = Path(path)
    out = output_root()
    if out is None:
        return candidate
    prefixes = (GENERATED_PREFIX, repo_root() / GENERATED_PREFIX)
    for prefix in prefixes:
        if candidate.is_relative_to(prefix):
            return out / candidate.relative_to(prefix)
    return candidate


def load_yaml(path: str | Path) -> dict[str, Any]:
    yaml_path = Path(path)
    with yaml_path.open("r", encoding="utf-8") as handle:
        data = yaml.safe_load(handle)
    if not isinstance(data, dict):
        raise TypeError(f"Expected YAML mapping at {yaml_path}")
    return data


def require_key(mapping: Mapping[str, Any], path: str | Path, key: str) -> Any:
    if key not in mapping:
        raise KeyError(f"Missing required key {key!r} in {path}")
    return mapping[key]


def require_mapping(data: Mapping[str, Any], key: str, source: str | Path) -> dict[str, Any]:
    value = require_key(data, source, key)
    if not isinstance(value, dict):
        raise TypeError(f"Expected {key!r} in {source} to be a mapping")
    return value


def require_section(data: Mapping[str, Any], path: str, key: str) -> dict[str, Any]:
    value = require_key(data, path, key)
    if not isinstance(value, dict):
        raise TypeError(f"Expected {path}.{key} to be a mapping")
    return value


def require_side(vehicle_data: Mapping[str, Any], side: str) -> dict[str, Any]:
    if side not in {"front", "rear"}:
        raise ValueError(f"Unknown vehicle side: {side!r}")
    return require_section(vehicle_data, "vehicle", side)


def tire_template_name(vehicle_data: Mapping[str, Any], side: Mapping[str, Any]) -> str:
    tire = side.get("tire", {})
    if isinstance(tire, Mapping) and tire.get("template"):
        return str(tire["template"])
    aero = vehicle_data.get("aero", {})
    if isinstance(aero, Mapping) and aero.get("tire_template"):
        return str(aero["tire_template"])
    raise KeyError("Missing tire.template for axle and aero.tire_template fallback")


def tire_templates_root(vehicle_data: Mapping[str, Any]) -> Path:
    paths = vehicle_data.get("paths", {})
    if not isinstance(paths, dict):
        paths = {}

    raw_path = Path(str(paths.get("tire_templates", "common/tire_templates")))
    return raw_path if raw_path.is_absolute() else repo_root() / raw_path


def parse_tir(path: str | Path) -> dict[str, float | str]:
    tire_path = Path(path)
    values: dict[str, float | str] = {}
    pattern = re.compile(r"^\s*([A-Za-z0-9_]+)\s*=\s*(.+?)\s*(?:[$!].*)?$")

    for line in tire_path.read_text(encoding="utf-8", errors="ignore").splitlines():
        match = pattern.match(line)
        if match is None:
            continue
        key, raw_value = match.groups()
        value = raw_value.strip().strip("'\"")
        try:
            values[key] = float(value)
        except ValueError:
            values[key] = value

    return values


class _VehicleDumper(yaml.SafeDumper):
    def increase_indent(self, flow: bool = False, indentless: bool = False) -> None:
        return super().increase_indent(flow, False)


def _represent_sequence(dumper: yaml.SafeDumper, values: list[Any]) -> yaml.SequenceNode:
    return dumper.represent_sequence(
        "tag:yaml.org,2002:seq", values,
        flow_style=all(not isinstance(value, (dict, list, tuple)) for value in values),
    )


_VehicleDumper.add_representer(list, _represent_sequence)


def dump_vehicle(data: Mapping[str, Any]) -> str:
    """## Vehicle YAML

    Keep vectors and table rows compact, with space between vehicle sections.

    Parameters
    ----------
    data : Mapping[str, Any]
        Vehicle definition to serialize.

    Returns
    -------
    str
        YAML preserving the input values and section order.
    """
    return "\n".join(
        yaml.dump({key: value}, Dumper=_VehicleDumper, sort_keys=False, width=120)
        for key, value in data.items()
    )
