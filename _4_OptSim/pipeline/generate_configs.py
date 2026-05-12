"""generate_configs.py — Materialize DOE configs from the selected vehicle architecture.

The vehicle architecture YAML is the source of truth for which baseline record,
sampling controls, and sweepable parameter blocks should be used. This script
writes the derived _doe_config.yaml so the rest of the DOE pipeline can stay simple.
"""

from __future__ import annotations

import os
from pathlib import Path
import re
from typing import Any

import yaml


DOE_DIR = Path(__file__).resolve().parent.parent
REPO_ROOT = DOE_DIR.parent
CONFIG_DIR = DOE_DIR / "configs"
ARCHITECTURE_CONFIG = CONFIG_DIR / "vehicle_architecture.yaml"
DOE_CONFIG = CONFIG_DIR / "_doe_config.yaml"
COMPILER_CONFIG = CONFIG_DIR / "compiler_config.yaml"

def load_yaml(path: Path) -> dict[str, Any]:
    with path.open("r", encoding="utf-8") as f:
        data = yaml.safe_load(f)
    if not isinstance(data, dict):
        raise TypeError(f"Expected mapping at top level: {path}")
    return data


def _resolve_path(base: Path, value: str | Path) -> Path:
    path = Path(value)
    return (base / path).resolve() if not path.is_absolute() else path.resolve()


def _find_standard_source(boblib_root: Path, model_name: str) -> Path:
    stem = model_name.split(".")[-1]
    matches = sorted(boblib_root.rglob(f"{stem}.mo"))
    if not matches:
        raise FileNotFoundError(
            f"Could not locate a Modelica source file for {model_name!r} under {boblib_root}"
        )
    if len(matches) > 1:
        # Prefer the shortest path if the same stem appears in multiple places.
        matches.sort(key=lambda p: len(p.as_posix()))
    return matches[0]


def _record_import_present(source_path: Path, record_name: str) -> bool:
    text = source_path.read_text(encoding="utf-8")
    pattern = rf"import\s+BobLib\.Resources\.VehicleDefn\.{re.escape(record_name)}\s*;"
    return re.search(pattern, text) is not None


def build_doe_config(
    *,
    template_cfg: dict[str, Any],
    template_cfg_path: Path,
    architecture_cfg: dict[str, Any],
    architecture_config_path: Path,
) -> dict[str, Any]:
    vehicle_cfg = template_cfg.get("vehicle", {})
    if not isinstance(vehicle_cfg, dict):
        raise TypeError("vehicle_template YAML must contain a vehicle mapping")

    if "name" not in vehicle_cfg:
        raise KeyError("vehicle_template YAML must define vehicle.name")

    vehicle_name = str(vehicle_cfg["name"])
    record_name = f"{vehicle_name}Record"

    paths_cfg = template_cfg.get("paths", {})
    if not isinstance(paths_cfg, dict):
        raise TypeError("vehicle_template YAML must contain a paths mapping")

    boblib_root = _resolve_path(REPO_ROOT, paths_cfg["boblib"])
    record_path = boblib_root / "Resources" / "VehicleDefn" / f"{record_name}.mo"
    if not record_path.exists():
        raise FileNotFoundError(
            f"Vehicle definition record not found for {vehicle_name!r}: {record_path}"
        )

    sweep_cfg = architecture_cfg.get("sweep", {})
    if not isinstance(sweep_cfg, dict):
        raise TypeError("architecture YAML must contain a sweep mapping")

    raw_variables = sweep_cfg.get("variables", [])
    if not isinstance(raw_variables, list) or not raw_variables:
        raise ValueError("architecture YAML sweep.variables must be a non-empty list")

    variables: list[dict[str, Any]] = []
    for spec in raw_variables:
        if not isinstance(spec, dict):
            raise TypeError("Each sweep variable must be a mapping")
        for field in ("path", "block", "param", "range"):
            if field not in spec:
                raise KeyError(f"Missing sweep variable field {field!r}")

        variables.append(
            {
                "path": str(spec["path"]),
                "block": str(spec["block"]),
                "param": str(spec["param"]),
                "range": list(spec["range"]),
            }
        )

    if not variables:
        raise ValueError(
            f"No DOE sweep variables were enabled for architecture {vehicle_name!r}"
        )

    return {
        "architecture": {
            "template": os.path.relpath(template_cfg_path, DOE_DIR),
            "vehicle": vehicle_name,
            "record": record_name,
            "source": os.path.relpath(architecture_config_path, DOE_DIR),
        },
        "baseline_mo": os.path.relpath(record_path, DOE_CONFIG.parent),
        "variables": variables,
        "samples": int(architecture_cfg.get("samples", 3)),
        "seed": architecture_cfg.get("seed", 42),
    }


def refresh_doe_config(
    architecture_config_path: Path = ARCHITECTURE_CONFIG,
    compiler_config_path: Path = COMPILER_CONFIG,
    doe_config_path: Path = DOE_CONFIG,
) -> dict[str, Any]:
    """Generate the active DOE config from the selected vehicle architecture."""
    architecture_cfg = load_yaml(architecture_config_path)
    template_ref = architecture_cfg.get("vehicle_template")
    if template_ref is None:
        raise KeyError(
            f"Missing vehicle_template in architecture config: {architecture_config_path}"
        )

    template_cfg_path = _resolve_path(architecture_config_path.parent, template_ref)
    template_cfg = load_yaml(template_cfg_path)
    vehicle_cfg = template_cfg.get("vehicle", {})
    if not isinstance(vehicle_cfg, dict) or "name" not in vehicle_cfg:
        raise KeyError(f"vehicle_template must define vehicle.name: {template_cfg_path}")
    vehicle_name = str(vehicle_cfg["name"])

    compiler_cfg = load_yaml(compiler_config_path)
    standards = compiler_cfg.get("standards", {})
    if not isinstance(standards, dict) or not standards:
        raise ValueError(f"No standards defined in compiler config: {compiler_config_path}")

    record_name = f"{vehicle_name}Record"
    boblib_root = _resolve_path(REPO_ROOT, template_cfg["paths"]["boblib"])

    for standard_name, standard_cfg in standards.items():
        model_name = standard_cfg["model"]
        source_path = _find_standard_source(boblib_root, model_name)
        if not _record_import_present(source_path, record_name):
            raise ValueError(
                "Selected vehicle architecture does not match the standard model.\n"
                f"  architecture record: {record_name}\n"
                f"  standard: {standard_name}\n"
                f"  source: {source_path}\n"
                "Update the standard model or choose a matching vehicle template."
            )

    doe_cfg = build_doe_config(
        template_cfg=template_cfg,
        template_cfg_path=template_cfg_path,
        architecture_cfg=architecture_cfg,
        architecture_config_path=architecture_config_path,
    )

    doe_config_path.parent.mkdir(parents=True, exist_ok=True)
    with doe_config_path.open("w", encoding="utf-8") as f:
        yaml.safe_dump(doe_cfg, f, sort_keys=False)

    return doe_cfg


if __name__ == "__main__":
    cfg = refresh_doe_config()
    print(f"Generated DOE config: {DOE_CONFIG}")
    print(cfg)
