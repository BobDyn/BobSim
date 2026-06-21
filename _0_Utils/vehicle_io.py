"""Shared helpers for BobSim vehicle YAML and tire-template inputs."""

from __future__ import annotations

from collections.abc import Mapping
from pathlib import Path
from typing import Any
import re

import yaml


def repo_root() -> Path:
    return Path(__file__).resolve().parents[1]


def vehicle_yaml_path() -> Path:
    return repo_root() / "vehicle.yml"


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
    aero = vehicle_data.get("aero", {})
    if isinstance(aero, dict) and aero.get("tire_template"):
        return str(aero["tire_template"])

    tire = require_section(side, "side", "tire")
    return str(require_key(tire, "side.tire", "template"))


def tire_templates_root(vehicle_data: Mapping[str, Any]) -> Path:
    paths = vehicle_data.get("paths", {})
    if not isinstance(paths, dict):
        paths = {}

    raw_path = Path(str(paths.get("tire_templates", "_0_Utils/tire_templates")))
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
