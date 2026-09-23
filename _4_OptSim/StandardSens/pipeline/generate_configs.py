"""generate_configs.py — Materialize DOE configs from the selected vehicle architecture.

The vehicle architecture YAML is the source of truth for which baseline record,
sampling controls, and sweepable parameter blocks should be used. This script
writes the derived _doe_config.yaml so the rest of the DOE pipeline can stay simple.

The sweep is also partitioned by *scope*: `setup` for knobs adjustable on the
built car, `architecture` for properties fixed once it exists, and untagged for
variables belonging to both or neither. Which variable belongs to which lives in
the architecture YAML, never here. The resolved scope is written to
_doe_config.yaml as a top-level `scope` key so downstream consumers — the
reverse lookup in particular — can tell a scoped population from a full one.
"""

from __future__ import annotations

import os
from pathlib import Path
import re
from typing import Any

import yaml


STANDARD_DIR = Path(__file__).resolve().parents[1]
OPTSIM_DIR = STANDARD_DIR.parent
REPO_ROOT = OPTSIM_DIR.parent
CONFIG_DIR = STANDARD_DIR / "configs"
ARCHITECTURE_CONFIG = CONFIG_DIR / "vehicle_architecture.yaml"
DOE_CONFIG = CONFIG_DIR / "_doe_config.yaml"
COMPILER_CONFIG = CONFIG_DIR / "compiler_config.yaml"

SCOPE_ENV_VAR = "BOBSIM_DOE_SCOPE"

# Sweep scopes. `all` is the default and sweeps every variable, so existing
# invocations and the committed _doe_config.yaml are unaffected. The other two
# split the study the 23-variable sweep conflates: setup knobs that can be
# changed on the built car, versus architecture properties that cannot.
#
# The membership of each scope is declared per variable in
# vehicle_architecture.yaml (`scope:`) and is deliberately *not* listed here —
# the partition is a vehicle-dynamics judgement call, so it must be editable
# without touching Python.
SWEEP_SCOPE_ALL = "all"
SWEEP_SCOPES = (SWEEP_SCOPE_ALL, "setup", "architecture")
DEFAULT_SWEEP_SCOPE = SWEEP_SCOPE_ALL


def _relpath_posix(target: Path | str, start: Path | str) -> str:
    """Relative path with forward slashes, regardless of host OS.

    `_doe_config.yaml` is checked in and is also consumed inside the Linux
    build container, so native Windows separators must never reach it: a
    backslash path is a single opaque filename on Linux, not a relative path.
    """
    return Path(os.path.relpath(target, start)).as_posix()


def _env_str(name: str) -> str | None:
    value = os.environ.get(name, "").strip()
    return value or None


def _env_int(name: str) -> int | None:
    raw = _env_str(name)
    if raw is None:
        return None
    try:
        return int(raw)
    except ValueError:
        raise ValueError(f"{name} must be an integer, got {raw!r}") from None


def _validate_scope(raw: str, source: str) -> str:
    """Normalize a sweep scope, naming the legal values when it is wrong."""
    scope = raw.strip().lower()
    if scope not in SWEEP_SCOPES:
        raise ValueError(
            f"{source} must be one of {', '.join(SWEEP_SCOPES)}, got {raw!r}"
        )
    return scope


def _resolve_sweep_scope(scope: str | None = None) -> str:
    """Pick the sweep scope: explicit argument, then env var, then the default.

    Same precedence as the sampling overrides — an explicit call wins over
    BOBSIM_DOE_SCOPE, which wins over the checked-in behaviour of `all`.
    """
    if scope is not None:
        return _validate_scope(scope, "sweep scope")
    raw = _env_str(SCOPE_ENV_VAR)
    if raw is None:
        return DEFAULT_SWEEP_SCOPE
    return _validate_scope(raw, SCOPE_ENV_VAR)


def _variable_in_scope(spec: dict[str, Any], scope: str) -> bool:
    """Does this sweep variable belong to the requested scope?

    A variable with no `scope:` key belongs to *every* scope. An untagged or
    newly added entry is therefore never silently dropped from a scoped sweep:
    the worst case is that it gets swept when it did not need to be, which is
    visible in the results table, rather than missing from it, which is not.
    """
    declared = spec.get("scope")
    if declared is None:
        return True

    # Validated even when the requested scope is `all`, so a misspelled tag
    # fails on the default sweep that CI regenerates rather than lying dormant
    # until someone asks for a scoped one.
    declared_scope = _validate_scope(
        str(declared), f"sweep variable {spec.get('path')!r} scope"
    )
    if scope == SWEEP_SCOPE_ALL:
        return True
    return declared_scope in (scope, SWEEP_SCOPE_ALL)


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


def _record_binding_present(boblib_root: Path, source_path: Path, record_name: str) -> bool:
    text = source_path.read_text(encoding="utf-8")
    record_stem = record_name.removesuffix("Record")

    patterns = (
        rf"BobLib\.Records\.VehicleDefn\.{re.escape(record_name)}\b",
        rf"\b{re.escape(record_stem)}\b",
    )
    if any(re.search(pattern, text) for pattern in patterns):
        return True

    # The public standard entrypoint can extend an architecture template that
    # owns the concrete VehicleRecord redeclare. Search the package sources so
    # this check still protects against mismatched active architectures without
    # assuming the binding lives in the front-facing wrapper.
    for mo_path in boblib_root.rglob("*.mo"):
        if mo_path == source_path:
            continue
        source = mo_path.read_text(encoding="utf-8")
        if f"BobLib.Records.VehicleDefn.{record_name}" in source:
            return True

    return False


def build_doe_config(
    *,
    template_cfg: dict[str, Any],
    template_cfg_path: Path,
    architecture_cfg: dict[str, Any],
    architecture_config_path: Path,
    scope: str | None = None,
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
    record_path = boblib_root / "Records" / "VehicleDefn" / f"{record_name}.mo"
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

    sweep_scope = _resolve_sweep_scope(scope)

    variables: list[dict[str, Any]] = []
    for spec in raw_variables:
        if not isinstance(spec, dict):
            raise TypeError("Each sweep variable must be a mapping")
        if not _variable_in_scope(spec, sweep_scope):
            continue
        for field in ("path", "range"):
            if field not in spec:
                raise KeyError(f"Missing sweep variable field {field!r}")
        if "block" not in spec and "targets" not in spec:
            raise KeyError("Sweep variable must define either 'block' or 'targets'")

        variable: dict[str, Any] = {
            "path": str(spec["path"]),
            "range": list(spec["range"]),
        }
        if "values" in spec:
            variable["values"] = list(spec["values"])
        if "block" in spec:
            variable["block"] = str(spec["block"])
        if "param" in spec:
            variable["param"] = str(spec["param"])
        if "label" in spec:
            variable["label"] = str(spec["label"])
        if "baseline" in spec:
            variable["baseline"] = float(spec["baseline"])
        if "field_path" in spec:
            variable["field_path"] = list(spec["field_path"])
        if "index" in spec:
            variable["index"] = list(spec["index"])
        if "scale" in spec:
            variable["scale"] = float(spec["scale"])
        if "targets" in spec:
            variable["targets"] = [
                {
                    key: list(value) if key in {"field_path", "index"} else value
                    for key, value in target.items()
                }
                for target in spec["targets"]
            ]
        if "intervals" in spec:
            variable["intervals"] = int(spec["intervals"])
        variables.append(variable)

    if not variables:
        raise ValueError(
            f"No DOE sweep variables were enabled for architecture {vehicle_name!r} "
            f"at scope {sweep_scope!r}"
        )

    sampling_cfg = architecture_cfg.get("sampling", {})
    if sampling_cfg is None:
        sampling_cfg = {}
    if not isinstance(sampling_cfg, dict):
        raise TypeError("architecture YAML sampling must be a mapping when provided")
    sampling_cfg = dict(sampling_cfg)

    samples = int(architecture_cfg.get("samples", 3))

    # Environment overrides let a small run be requested without editing the
    # checked-in architecture YAML (make opt-standard DOE_SAMPLES=3).
    method_override = _env_str("BOBSIM_DOE_METHOD")
    if method_override:
        sampling_cfg["method"] = method_override
    intervals_override = _env_int("BOBSIM_DOE_INTERVALS")
    if intervals_override is not None:
        sampling_cfg["intervals"] = intervals_override
    samples_override = _env_int("BOBSIM_DOE_SAMPLES")
    if samples_override is not None:
        samples = samples_override

    return {
        "architecture": {
            "template": _relpath_posix(template_cfg_path, STANDARD_DIR),
            "vehicle": vehicle_name,
            "record": record_name,
            "source": _relpath_posix(architecture_config_path, STANDARD_DIR),
        },
        "baseline_mo": _relpath_posix(record_path, DOE_CONFIG.parent),
        # The resolved scope is recorded so a results table can be traced back
        # to the sweep that produced it. Without it, restoring this generated
        # file from git after a scoped run leaves the reverse lookup reporting
        # every variable as swept when only a subset was.
        "scope": sweep_scope,
        "variables": variables,
        "sampling": sampling_cfg,
        "samples": samples,
        "seed": architecture_cfg.get("seed", 42),
    }


def refresh_doe_config(
    architecture_config_path: Path = ARCHITECTURE_CONFIG,
    compiler_config_path: Path = COMPILER_CONFIG,
    doe_config_path: Path = DOE_CONFIG,
    scope: str | None = None,
) -> dict[str, Any]:
    """Generate the active DOE config from the selected vehicle architecture.

    `scope` restricts which sweep variables are written; it defaults to
    BOBSIM_DOE_SCOPE, and to `all` when that is unset.
    """
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
        if not _record_binding_present(boblib_root, source_path, record_name):
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
        scope=scope,
    )

    doe_config_path.parent.mkdir(parents=True, exist_ok=True)
    with doe_config_path.open("w", encoding="utf-8") as f:
        yaml.safe_dump(doe_cfg, f, sort_keys=False)

    return doe_cfg


if __name__ == "__main__":
    cfg = refresh_doe_config()
    print(f"Generated DOE config: {DOE_CONFIG}")
    print(f"  scope: {_resolve_sweep_scope()} ({len(cfg['variables'])} variables)")
    print(cfg)
