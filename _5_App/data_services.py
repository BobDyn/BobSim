from __future__ import annotations

import copy
import csv
import json
import math
from pathlib import Path
import re
import shutil
import time
from typing import Any
import zipfile

import yaml

from _0_Utils import config_io
from _0_Utils.vehicle_io import parse_tir
from _5_App import registry as app_registry
from _5_App import storage as app_storage
from _5_App import tire_eval as tire_eval_core
from _5_App.contracts import BuildTargetSpec, ConfigSpec, FieldSpec, PathPart, WorkflowSpec
from _5_App.modelica_generator import generate_modelica_stack, modelica_generation_payload
from _5_App.registry import (
    BASE_CONFIG_SPECS,
    POWERTRAIN_DEFAULTS,
    POWERTRAIN_IMPLEMENTATIONS,
    VEHICLE_FIELDS,
    VISUAL_FIELDS,
)


BELLCRANK_ORDER_CHOICES = app_registry.BELLCRANK_ORDER_CHOICES
STABAR_BELLCRANK_ORDER_CHOICES = app_registry.STABAR_BELLCRANK_ORDER_CHOICES
ROOT = Path.cwd()
SAVED_VEHICLE_ROOT = app_storage.SAVED_VEHICLE_ROOT
SAVED_SIM_CONFIG_ROOT = app_storage.SAVED_SIM_CONFIG_ROOT
DEFAULT_SNAPSHOT_ROOT = app_storage.DEFAULT_SNAPSHOT_ROOT
SAVED_RESULTS_ROOT = app_storage.SAVED_RESULTS_ROOT
VEHICLE_WORKSPACE_ROOT = app_storage.VEHICLE_WORKSPACE_ROOT
RESULT_EXPLORER_ROOTS: tuple[Path, ...] = (
    Path("_3_StandardSim/generated_results"),
    Path("_3_StandardSim/results"),
    Path("_3_StandardSim/Build"),
    Path("_3_StandardSim/BuildBobLib"),
    Path("_2_EnvelopeSim/results"),
    Path("_2_EnvelopeSim/Build"),
    Path("_4_OptSim/results"),
    Path("_4_OptSim/Build"),
    SAVED_RESULTS_ROOT,
    VEHICLE_WORKSPACE_ROOT,
)
WORKFLOWS: tuple[WorkflowSpec, ...] = ()
MODELICA_RUN_TARGETS_BY_ACTION: dict[str, BuildTargetSpec] = {}
_num = tire_eval_core._num


def vehicle_workspace_payload(*_args: Any, **_kwargs: Any) -> dict[str, Any]:
    raise RuntimeError("vehicle_workspace_payload has not been connected")


def _safe_repo_path(raw_path: str | Path) -> Path:
    rel = Path(str(raw_path))
    if rel.is_absolute():
        candidate = rel.resolve()
    else:
        candidate = (ROOT / rel).resolve()
    if candidate != ROOT and ROOT not in candidate.parents:
        raise ValueError(f"Path escapes repo: {raw_path}")
    return candidate


def _path_payload(raw_path: str) -> dict[str, Any]:
    path = _safe_repo_path(raw_path)
    exists = path.exists()
    payload: dict[str, Any] = {
        "path": raw_path,
        "exists": exists,
        "url": f"/files/{raw_path}" if exists and path.is_file() else None,
    }
    if exists and path.is_file():
        stat = path.stat()
        payload.update(
            {
                "size": stat.st_size,
                "modified": stat.st_mtime,
                "modified_label": time.strftime(
                    "%Y-%m-%d %H:%M:%S",
                    time.localtime(stat.st_mtime),
                ),
            }
        )
    return payload


def _csv_preview(raw_path: str, limit: int = 8) -> dict[str, Any]:
    path = _safe_repo_path(raw_path)
    if not path.is_file():
        return {"headers": [], "rows": []}
    with path.open("r", encoding="utf-8", newline="", errors="replace") as handle:
        reader = csv.DictReader(handle)
        rows = []
        for idx, row in enumerate(reader):
            if idx >= limit:
                break
            rows.append(dict(row))
    return {"headers": list(reader.fieldnames or []), "rows": rows}


def _result_source_roots(vehicle_key: str | None = None, *, include_global: bool = True) -> tuple[Path, ...]:
    roots: list[Path] = []
    if vehicle_key:
        roots.append(_vehicle_workspace_dir(vehicle_key, create=False) / "results")
    if include_global or not vehicle_key:
        roots.extend(_safe_repo_path(root) for root in RESULT_EXPLORER_ROOTS)
    return tuple(roots)


def _is_result_source_path(path: Path, *, roots: tuple[Path, ...] | None = None) -> bool:
    path = path.resolve()
    if path.suffix.lower() != ".csv" or not path.is_file():
        return False
    for root_path in roots or _result_source_roots():
        if root_path.exists() and (path == root_path or root_path in path.parents):
            return True
    return False


def _result_source_group(rel_path: str) -> str:
    if rel_path.startswith(f"{VEHICLE_WORKSPACE_ROOT.as_posix()}/"):
        return "Vehicle"
    if rel_path.startswith("_3_StandardSim/"):
        return "Simulation"
    if rel_path.startswith("_2_EnvelopeSim/"):
        return "Envelope"
    if rel_path.startswith("_4_OptSim/"):
        return "Optimization"
    if rel_path.startswith(f"{SAVED_RESULTS_ROOT.as_posix()}/"):
        return "Saved"
    return "Results"


def _float_or_none(value: Any) -> float | None:
    if value is None:
        return None
    text = str(value).strip()
    if not text:
        return None
    try:
        number = float(text)
    except ValueError:
        return None
    return number if math.isfinite(number) else None


def _is_float_like(value: Any) -> bool:
    if value is None:
        return False
    text = str(value).strip()
    if not text:
        return False
    try:
        float(text)
    except ValueError:
        return False
    return True


def _csv_source_summary(path: Path, *, sample_limit: int = 240) -> dict[str, Any]:
    rel_path = path.relative_to(ROOT).as_posix()
    with path.open("r", encoding="utf-8", newline="", errors="replace") as handle:
        reader = csv.DictReader(handle)
        columns = list(reader.fieldnames or [])
        numeric_counts = {column: 0 for column in columns}
        non_empty_counts = {column: 0 for column in columns}
        row_count = 0
        for row in reader:
            row_count += 1
            if row_count > sample_limit:
                continue
            for column in columns:
                raw = row.get(column)
                if raw is None or str(raw).strip() == "":
                    continue
                non_empty_counts[column] += 1
                if _is_float_like(raw):
                    numeric_counts[column] += 1

    numeric_columns = [
        column
        for column in columns
        if non_empty_counts[column] > 0 and numeric_counts[column] / non_empty_counts[column] >= 0.85
    ]
    x_candidates: list[str] = [
        column for column in ("time", "Time", "t", "speed_mps") if column in numeric_columns
    ]
    x_candidates.extend(column for column in numeric_columns if column not in x_candidates)
    return {
        "id": rel_path,
        "label": path.stem.replace("_", " ").replace("-", " ").title(),
        "group": _result_source_group(rel_path),
        "row_count": row_count,
        "columns": columns,
        "numeric_columns": numeric_columns,
        "x_candidates": x_candidates,
        **_path_payload(rel_path),
    }


def result_sources_payload(vehicle_key: str | None = None) -> dict[str, Any]:
    sources_by_path: dict[Path, dict[str, Any]] = {}
    roots = _result_source_roots(vehicle_key, include_global=not vehicle_key)
    for root_path in roots:
        if not root_path.exists():
            continue
        for path in root_path.rglob("*.csv"):
            try:
                if _is_result_source_path(path, roots=roots):
                    sources_by_path[path.resolve()] = _csv_source_summary(path)
            except (OSError, csv.Error, UnicodeDecodeError, ValueError):
                continue
    sources = sorted(
        sources_by_path.values(),
        key=lambda item: (str(item.get("group") or ""), str(item.get("path") or "")),
    )
    return {"vehicle_key": vehicle_key or _active_vehicle_workspace_key(), "sources": sources}


def result_source_payload(raw_path: str) -> dict[str, Any]:
    path = _safe_repo_path(raw_path)
    if not _is_result_source_path(path):
        raise ValueError("Result source must be a CSV file under a results directory")
    return _csv_source_summary(path)


def result_series_payload(
    raw_path: str,
    *,
    x_axis: str = "__index__",
    signals: list[str] | None = None,
    max_points: int = 1800,
) -> dict[str, Any]:
    source = result_source_payload(raw_path)
    path = _safe_repo_path(raw_path)
    numeric_columns = set(source["numeric_columns"])
    if x_axis != "__index__" and x_axis not in numeric_columns:
        raise ValueError("x_axis must be __index__ or a numeric column")
    selected_signals = [signal for signal in signals or [] if signal in numeric_columns and signal != x_axis]
    if not selected_signals:
        selected_signals = [column for column in source["numeric_columns"] if column != x_axis][:3]
    if not selected_signals:
        raise ValueError("Select at least one numeric signal to plot")

    row_count = int(source.get("row_count") or 0)
    point_limit = max(50, min(10_000, int(max_points or 1800)))
    stride = max(1, math.ceil(row_count / point_limit)) if row_count else 1
    x_values: list[float] = []
    series: dict[str, list[float | None]] = {signal: [] for signal in selected_signals}

    with path.open("r", encoding="utf-8", newline="", errors="replace") as handle:
        reader = csv.DictReader(handle)
        for index, row in enumerate(reader):
            if index % stride != 0:
                continue
            x_value = float(index) if x_axis == "__index__" else _float_or_none(row.get(x_axis))
            if x_value is None:
                continue
            x_values.append(x_value)
            for signal in selected_signals:
                series[signal].append(_float_or_none(row.get(signal)))

    return {
        "source": source,
        "x_axis": x_axis,
        "x": x_values,
        "stride": stride,
        "row_count": row_count,
        "series": [
            {
                "signal": signal,
                "label": signal.replace("_", " "),
                "values": values,
            }
            for signal, values in series.items()
        ],
    }


def config_specs() -> dict[str, ConfigSpec]:
    specs = dict(BASE_CONFIG_SPECS)
    visual_root = _safe_repo_path("_1_VisualSim/visual_templates")
    if visual_root.is_dir():
        for path in sorted(visual_root.glob("*.yml")):
            rel_path = path.relative_to(ROOT).as_posix()
            config_id = f"visual-{path.stem.replace('_', '-')}"
            label = path.stem.replace("_", " ").title()
            specs[config_id] = ConfigSpec(
                id=config_id,
                group="visualization",
                label=label,
                path=rel_path,
                fields=VISUAL_FIELDS,
            )
    return specs


def _config_spec(config_id: str) -> ConfigSpec:
    specs = config_specs()
    if config_id not in specs:
        raise KeyError(config_id)
    return specs[config_id]


def _config_file_path(spec: ConfigSpec) -> Path:
    """The file the app reads and writes for this config.

    A relocatable spec resolves to a per-user copy under
    _5_App/user_data/config/active/, seeded from the checked-in config the first
    time it is touched, so editing in the app never writes a tracked file. Every
    other spec is still edited in place.
    """
    if not spec.relocatable:
        return _safe_repo_path(spec.path)
    _safe_repo_path(spec.path)  # keep the traversal guard on the seed path
    return config_io.ensure_active(spec.path, root=ROOT)


def _config_seed_path(spec: ConfigSpec) -> Path:
    """The checked-in config a relocatable spec is seeded and reset from."""
    return _safe_repo_path(spec.path)


def _load_yaml_config(spec: ConfigSpec) -> tuple[Path, str, Any]:
    path = _config_file_path(spec)
    if not path.is_file():
        raise FileNotFoundError(spec.path)
    raw = path.read_text(encoding="utf-8", errors="replace")
    data = yaml.safe_load(raw) or {}
    if not isinstance(data, (dict, list)):
        raise TypeError(f"{spec.path} must contain a YAML mapping or list")
    return path, raw, data


def _write_yaml_config(path: Path, data: Any) -> None:
    text = yaml.safe_dump(
        data,
        allow_unicode=False,
        default_flow_style=False,
        sort_keys=False,
    )
    path.write_text(text, encoding="utf-8")


def _humanize_path_part(value: PathPart) -> str:
    return str(value).replace("_", " ").replace("-", " ").title()


def _field_key(path: tuple[PathPart, ...]) -> str:
    return json.dumps(list(path), separators=(",", ":"))


def _decode_field_key(raw_key: str) -> tuple[PathPart, ...]:
    if raw_key.startswith("["):
        parts = json.loads(raw_key)
        if not isinstance(parts, list):
            raise TypeError("Config field path must be a list")
        return tuple(int(part) if isinstance(part, int) else str(part) for part in parts)
    return tuple(raw_key.split("."))


def _is_scalar(value: Any) -> bool:
    return value is None or isinstance(value, (str, int, float, bool))


def _is_scalar_list(value: list[Any]) -> bool:
    return all(_is_scalar(item) for item in value)


def _array_scalars(value: list[Any]) -> list[Any]:
    scalars: list[Any] = []
    for item in value:
        if isinstance(item, list):
            scalars.extend(_array_scalars(item))
        elif _is_scalar(item):
            scalars.append(item)
    return scalars


def _array_shape(value: Any) -> list[int]:
    if not isinstance(value, list):
        return []
    if not value or _is_scalar_list(value):
        return [len(value)]
    if all(isinstance(row, list) and _is_scalar_list(row) for row in value):
        width = max((len(row) for row in value), default=0)
        return [len(value), width]
    return []


def _array_element_kind(value: list[Any]) -> str:
    scalars = [item for item in _array_scalars(value) if item is not None]
    if not scalars:
        return "number"
    if all(isinstance(item, bool) for item in scalars):
        return "boolean"
    if all(isinstance(item, int) and not isinstance(item, bool) for item in scalars):
        return "integer"
    if all(isinstance(item, (int, float)) and not isinstance(item, bool) for item in scalars):
        return "number"
    if all(isinstance(item, str) for item in scalars):
        return "string"
    return "mixed"


def _array_payload(value: Any) -> dict[str, Any]:
    shape = _array_shape(value)
    if not shape:
        return {}
    return {
        "array_shape": shape,
        "array_element_kind": _array_element_kind(value),
    }


def _infer_field_kind(value: Any) -> str:
    if isinstance(value, bool):
        return "boolean"
    if isinstance(value, int) and not isinstance(value, bool):
        return "integer"
    if isinstance(value, float):
        return "number"
    if isinstance(value, list):
        return "list" if _is_scalar_list(value) else "json"
    if isinstance(value, dict):
        return "json"
    return "string"


def _discover_fields(data: Any, path: tuple[PathPart, ...] = ()) -> list[FieldSpec]:
    if isinstance(data, dict):
        fields: list[FieldSpec] = []
        for key, value in data.items():
            fields.extend(_discover_fields(value, (*path, str(key))))
        return fields
    if isinstance(data, list):
        if _is_scalar_list(data) or path:
            return [
                FieldSpec(
                    path=path,
                    label=_humanize_path_part(path[-1]) if path else "Value",
                    kind=_infer_field_kind(data),
                    group=_humanize_path_part(path[0]) if path else "General",
                )
            ]
        return []
    if path:
        return [
            FieldSpec(
                path=path,
                label=_humanize_path_part(path[-1]),
                kind=_infer_field_kind(data),
                group=_humanize_path_part(path[0]),
            )
        ]
    return []


def _get_nested(data: Any, path: tuple[PathPart, ...]) -> Any:
    current = data
    for part in path:
        current = current[part]
    return current


def _deep_merge_missing(target: dict[str, Any], defaults: dict[str, Any]) -> None:
    for key, value in defaults.items():
        if isinstance(value, dict):
            current = target.get(key)
            if not isinstance(current, dict):
                target[key] = copy.deepcopy(value)
            else:
                _deep_merge_missing(current, value)
        else:
            target.setdefault(key, copy.deepcopy(value))


def _vehicle_template_data() -> list[dict[str, Any]]:
    template_root = _safe_repo_path("_0_Utils/vehicle_templates")
    if not template_root.is_dir():
        return []
    templates: list[dict[str, Any]] = []
    for path in sorted(template_root.glob("*.yml")):
        data = yaml.safe_load(path.read_text(encoding="utf-8", errors="replace")) or {}
        if isinstance(data, dict):
            templates.append(data)
    return templates


def _vehicle_template_for_architecture(front: str, rear: str) -> dict[str, Any] | None:
    for data in _vehicle_template_data():
        architecture = data.get("architecture", {})
        if not isinstance(architecture, dict):
            continue
        if architecture.get("front") == front and architecture.get("rear") == rear:
            return data
    return None


def _vehicle_template_for_axle_architecture(axle: str, architecture_id: str) -> dict[str, Any] | None:
    for data in _vehicle_template_data():
        architecture = data.get("architecture", {})
        if isinstance(architecture, dict) and architecture.get(axle) == architecture_id:
            return data
    return None


def _merge_axle_defaults(data: dict[str, Any], axle: str, defaults: dict[str, Any] | None) -> None:
    if not isinstance(defaults, dict):
        return
    current = data.get(axle)
    if not isinstance(current, dict):
        data[axle] = copy.deepcopy(defaults)
        return
    _deep_merge_missing(current, defaults)


def _normalized_bellcrank_order(values: Any, choices: tuple[str, ...]) -> list[str]:
    order: list[str] = []
    raw_values = values if isinstance(values, list) else []
    for value in raw_values:
        text = str(value)
        if text in choices and text not in order:
            order.append(text)
    for choice in choices:
        if choice not in order:
            order.append(choice)
    return order[: len(choices)]


def _normalize_vehicle_actuation_for_architecture(data: dict[str, Any], *, prune_inactive: bool) -> None:
    architecture = data.get("architecture", {})
    if not isinstance(architecture, dict):
        return
    for axle in ("front", "rear"):
        axle_data = data.get(axle)
        if not isinstance(axle_data, dict):
            continue
        actuation = axle_data.get("actuation")
        if not isinstance(actuation, dict):
            continue
        axle_architecture = str(architecture.get(axle) or "direct")
        has_bellcrank = "bellcrank" in axle_architecture
        has_stabar = "stabar" in axle_architecture
        if has_bellcrank:
            bellcrank = actuation.get("bellcrank")
            if isinstance(bellcrank, dict):
                choices = STABAR_BELLCRANK_ORDER_CHOICES if has_stabar else BELLCRANK_ORDER_CHOICES
                bellcrank["order"] = _normalized_bellcrank_order(bellcrank.get("order"), choices)
                pickups = bellcrank.get("pickups_m")
                if prune_inactive and not has_stabar and isinstance(pickups, dict):
                    pickups.pop("stabar", None)
        elif prune_inactive:
            actuation.pop("bellcrank", None)
        if prune_inactive and not has_stabar:
            actuation.pop("stabar", None)


def _vehicle_with_powertrain_defaults(data: Any) -> Any:
    if not isinstance(data, dict):
        return data
    powertrain_id = _powertrain_id(data)
    defaults = POWERTRAIN_DEFAULTS.get(powertrain_id, POWERTRAIN_DEFAULTS["EVBatInvMotDiff"])
    existing = data.get("powertrain")
    if not isinstance(existing, dict):
        data["powertrain"] = copy.deepcopy(defaults)
    else:
        _deep_merge_missing(existing, defaults)
        existing["implementation"] = str(existing.get("implementation") or powertrain_id)
    return data


def _vehicle_with_architecture_defaults(data: Any, *, prune_inactive: bool = False) -> Any:
    if not isinstance(data, dict):
        return data
    architecture = data.get("architecture")
    if not isinstance(architecture, dict):
        architecture = {}
        data["architecture"] = architecture
    front = str(architecture.get("front") or "direct")
    rear = str(architecture.get("rear") or "direct")
    architecture["front"] = front
    architecture["rear"] = rear

    combined_defaults = _vehicle_template_for_architecture(front, rear)
    if combined_defaults:
        for axle in ("front", "rear"):
            _merge_axle_defaults(data, axle, combined_defaults.get(axle))

    inactive_default_order = ("direct", "bellcrank_stabar", "bellcrank")
    for axle in ("front", "rear"):
        for architecture_id in inactive_default_order:
            template = _vehicle_template_for_axle_architecture(axle, architecture_id)
            axle_defaults = template.get(axle) if isinstance(template, dict) else None
            if isinstance(axle_defaults, dict):
                actuation_defaults = axle_defaults.get("actuation")
                if isinstance(actuation_defaults, dict):
                    current_axle = data.setdefault(axle, {})
                    if isinstance(current_axle, dict):
                        current_actuation = current_axle.setdefault("actuation", {})
                        if isinstance(current_actuation, dict):
                            _deep_merge_missing(current_actuation, actuation_defaults)

    _normalize_vehicle_actuation_for_architecture(data, prune_inactive=prune_inactive)
    return data


def _bellcrank_order_choices(data: Any, axle: str) -> tuple[str, ...]:
    if not isinstance(data, dict):
        return BELLCRANK_ORDER_CHOICES
    architecture = data.get("architecture", {})
    axle_architecture = architecture.get(axle, "") if isinstance(architecture, dict) else ""
    if "stabar" in str(axle_architecture):
        return STABAR_BELLCRANK_ORDER_CHOICES
    return BELLCRANK_ORDER_CHOICES


def _field_choices(field: FieldSpec, data: Any) -> tuple[str, ...]:
    if (
        len(field.path) == 4
        and field.path[0] in {"front", "rear"}
        and field.path[1:] == ("actuation", "bellcrank", "order")
    ):
        return _bellcrank_order_choices(data, str(field.path[0]))
    return field.choices


def _set_nested(data: Any, path: tuple[PathPart, ...], value: Any) -> None:
    if not path:
        raise ValueError("Cannot replace config root through patch mode")
    current = data
    for part in path[:-1]:
        if not isinstance(current, dict):
            raise TypeError("Cannot patch through a non-mapping value")
        next_value = current.get(part)
        if not isinstance(next_value, dict):
            next_value = {}
            current[part] = next_value
        current = next_value
    current[path[-1]] = value


def _field_payload(field: FieldSpec, data: Any) -> dict[str, Any]:
    try:
        value = _get_nested(data, field.path)
    except (KeyError, IndexError, TypeError):
        if not field.disabled:
            raise
        value = None
    kind = _infer_field_kind(value) if field.kind == "auto" else field.kind
    choices = _field_choices(field, data)
    return {
        "key": _field_key(field.path),
        "path": list(field.path),
        "label": field.label,
        "kind": kind,
        "group": field.group or (_humanize_path_part(field.path[0]) if field.path else "General"),
        "unit": field.unit,
        "choices": list(choices),
        "value": value,
        "disabled": field.disabled,
        "placeholder": field.placeholder,
        "help": field.help_text,
        **_array_payload(value),
    }


def _config_fields(spec: ConfigSpec, data: Any) -> list[dict[str, Any]]:
    if spec.id == "vehicle":
        return _vehicle_config_fields(data)

    fields: list[FieldSpec] = []
    for field in spec.fields:
        try:
            _get_nested(data, field.path)
        except (KeyError, IndexError, TypeError):
            continue
        fields.append(field)
    return [_field_payload(field, data) for field in fields]


def _vehicle_config_fields(data: Any) -> list[dict[str, Any]]:
    overrides = {_field_key(field.path): field for field in VEHICLE_FIELDS}
    fields: list[FieldSpec] = []
    seen: set[str] = set()
    for field in _discover_fields(data):
        if not field.path or field.path[0] in {"schema", "paths"}:
            continue
        key = _field_key(field.path)
        fields.append(overrides.get(key, field))
        seen.add(key)
    for field in VEHICLE_FIELDS:
        key = _field_key(field.path)
        if field.disabled and key not in seen:
            fields.append(field)
    return [_field_payload(field, data) for field in fields]


def config_summary(spec: ConfigSpec) -> dict[str, Any]:
    return {
        "id": spec.id,
        "group": spec.group,
        "label": spec.label,
        "workflow_id": spec.workflow_id,
        **_path_payload(_config_file_path(spec).relative_to(ROOT).as_posix()),
    }


def config_payload(config_id: str) -> dict[str, Any]:
    spec = _config_spec(config_id)
    path, raw, data = _load_yaml_config(spec)
    if spec.id == "vehicle":
        data = _vehicle_with_powertrain_defaults(data)
        data = _vehicle_with_architecture_defaults(data)
    return {
        **config_summary(spec),
        "modified": path.stat().st_mtime,
        "raw": raw,
        "data": data,
        "fields": _config_fields(spec, data),
    }


def patch_config(config_id: str, values: dict[str, Any]) -> dict[str, Any]:
    spec = _config_spec(config_id)
    path, _, data = _load_yaml_config(spec)
    if spec.id == "vehicle":
        data = _vehicle_with_powertrain_defaults(data)
        data = _vehicle_with_architecture_defaults(data)
    disabled_paths = {
        field.path
        for field in (VEHICLE_FIELDS if spec.id == "vehicle" else spec.fields)
        if field.disabled
    }
    for raw_key, value in values.items():
        decoded_path = _decode_field_key(raw_key)
        if decoded_path in disabled_paths:
            continue
        _set_nested(data, decoded_path, value)
    if spec.id == "vehicle":
        data = _vehicle_with_powertrain_defaults(data)
        data = _vehicle_with_architecture_defaults(data, prune_inactive=True)
    _write_yaml_config(path, data)
    return config_payload(config_id)


def save_raw_config(config_id: str, text: str) -> dict[str, Any]:
    spec = _config_spec(config_id)
    path = _config_file_path(spec)
    data = yaml.safe_load(text) or {}
    if not isinstance(data, (dict, list)):
        raise TypeError("Config must contain a YAML mapping or list")
    path.write_text(text if text.endswith("\n") else f"{text}\n", encoding="utf-8")
    return config_payload(config_id)


def generate_modelica_payload() -> dict[str, Any]:
    vehicle_path = _safe_repo_path("vehicle.yml")
    result = generate_modelica_stack(vehicle_path, root=ROOT)
    if vehicle_path.is_file():
        data = _load_vehicle_yaml_file(vehicle_path)
        _sync_vehicle_workspace_config(_vehicle_workspace_key_from_data(data), vehicle_path, data)
    return modelica_generation_payload(result, ROOT)


def _configurable_workflow_ids() -> set[str]:
    return {workflow.id for workflow in WORKFLOWS if workflow.config}


def _sim_config_spec(workflow_id: str) -> ConfigSpec:
    spec = _config_spec(workflow_id)
    if spec.workflow_id not in _configurable_workflow_ids():
        raise ValueError("Only runnable workflow configs are supported here")
    return spec


def _sim_config_slug(raw_name: str) -> str:
    base = raw_name.strip() or "sim-config"
    slug = re.sub(r"[^A-Za-z0-9_.-]+", "-", base).strip("-_.").lower()
    return slug or "sim-config"


def _saved_sim_config_dir(workflow_id: str) -> Path:
    _sim_config_spec(workflow_id)
    root = _safe_repo_path(SAVED_SIM_CONFIG_ROOT / workflow_id)
    root.mkdir(parents=True, exist_ok=True)
    return root


def _default_sim_config_path(workflow_id: str) -> Path:
    """Where "restore the default" reads from: the checked-in config itself.

    It used to be a snapshot under _5_App/sim_configs/_defaults/. Nothing tied
    those snapshots to their sources, so six of nine had drifted -- reverting
    report paths, worker counts and envelope physics whenever someone picked
    Default. The seed cannot drift from itself.

    A spec that is edited in place has no pristine seed left once the user saves,
    so those keep a snapshot -- but under user_data, taken from the checked-in
    file the first time it is needed, rather than committed alongside it.
    """
    spec = _sim_config_spec(workflow_id)
    if spec.relocatable:
        return _config_seed_path(spec)
    snapshot = _safe_repo_path(DEFAULT_SNAPSHOT_ROOT / f"{workflow_id}.yml")
    if not snapshot.is_file():
        snapshot.parent.mkdir(parents=True, exist_ok=True)
        snapshot.write_text(_config_seed_path(spec).read_text(encoding="utf-8"), encoding="utf-8")
    return snapshot


def _sim_config_summary(source_id: str, source_type: str, path: Path, workflow_id: str) -> dict[str, Any]:
    stat = path.stat()
    label = "Default" if source_type == "default" else path.stem.replace("-", " ").replace("_", " ").title()
    return {
        "id": source_id,
        "type": source_type,
        "workflow_id": workflow_id,
        "label": label,
        "modified": stat.st_mtime,
        **_path_payload(path.relative_to(ROOT).as_posix()),
    }


def sim_config_library_payload(workflow_id: str) -> dict[str, Any]:
    spec = _sim_config_spec(workflow_id)
    default_path = _default_sim_config_path(workflow_id)
    sources = [_sim_config_summary(f"default:{workflow_id}", "default", default_path, workflow_id)]
    saved_dir = _saved_sim_config_dir(workflow_id)
    for path in sorted(saved_dir.glob("*.yml")):
        sources.append(_sim_config_summary(f"saved:{workflow_id}:{path.stem}", "saved", path, workflow_id))
    return {
        "workflow_id": workflow_id,
        "config_id": spec.id,
        "active": config_payload(spec.id),
        "sources": sources,
    }


def _parse_sim_config_source(source_id: str) -> tuple[str, str, str | None]:
    parts = source_id.split(":", 2)
    if len(parts) < 2 or parts[0] not in {"default", "saved"}:
        raise ValueError("Invalid sim config source")
    workflow_id = parts[1]
    _sim_config_spec(workflow_id)
    slug = parts[2] if len(parts) == 3 else None
    if parts[0] == "saved" and not slug:
        raise ValueError("Saved sim config id is missing a name")
    return parts[0], workflow_id, slug


def load_sim_config_source(source_id: str) -> dict[str, Any]:
    source_type, workflow_id, slug = _parse_sim_config_source(source_id)
    spec = _sim_config_spec(workflow_id)
    source = (
        _default_sim_config_path(workflow_id)
        if source_type == "default"
        else _saved_sim_config_dir(workflow_id) / f"{slug}.yml"
    )
    if not source.is_file():
        raise FileNotFoundError(source_id)
    target = _config_file_path(spec)
    target.write_text(source.read_text(encoding="utf-8"), encoding="utf-8")
    return {
        "source": _sim_config_summary(source_id, source_type, source, workflow_id),
        "library": sim_config_library_payload(workflow_id),
        "config": config_payload(spec.id),
    }


def save_active_sim_config(workflow_id: str, name: str | None = None) -> dict[str, Any]:
    spec = _sim_config_spec(workflow_id)
    source = _config_file_path(spec)
    slug = _sim_config_slug(name or f"{spec.label} Config")
    saved_path = _saved_sim_config_dir(workflow_id) / f"{slug}.yml"
    saved_path.write_text(source.read_text(encoding="utf-8"), encoding="utf-8")
    return {
        "saved": _sim_config_summary(f"saved:{workflow_id}:{slug}", "saved", saved_path, workflow_id),
        "library": sim_config_library_payload(workflow_id),
    }


def delete_saved_sim_config(source_id: str) -> dict[str, Any]:
    source_type, workflow_id, slug = _parse_sim_config_source(source_id)
    if source_type != "saved" or not slug:
        raise ValueError("Only saved simulation configs can be deleted")
    path = _saved_sim_config_dir(workflow_id) / f"{slug}.yml"
    if not path.is_file():
        raise FileNotFoundError(source_id)
    path.unlink()
    return sim_config_library_payload(workflow_id)


def _workflow_by_id(workflow_id: str) -> WorkflowSpec:
    workflows = {workflow.id: workflow for workflow in WORKFLOWS}
    if workflow_id not in workflows:
        raise KeyError(workflow_id)
    return workflows[workflow_id]


def _result_slug(raw_name: str | None, fallback: str = "results") -> str:
    base = str(raw_name or "").strip() or fallback
    slug = re.sub(r"[^A-Za-z0-9_.-]+", "-", base).strip("-_.").lower()
    return slug or fallback


def _vehicle_workspace_key_from_data(data: dict[str, Any] | None = None) -> str:
    if data is None:
        vehicle_path = _safe_repo_path("vehicle.yml")
        data = _load_vehicle_yaml_file(vehicle_path) if vehicle_path.is_file() else {}
    vehicle = data.get("vehicle", {}) if isinstance(data, dict) else {}
    name = vehicle.get("name") if isinstance(vehicle, dict) else None
    return _saved_vehicle_id(str(name or "active-vehicle"))


def _normalize_vehicle_workspace_key(vehicle_key: str | None = None) -> str:
    return _saved_vehicle_id(str(vehicle_key or _vehicle_workspace_key_from_data()))


def _active_vehicle_workspace_key() -> str:
    return _normalize_vehicle_workspace_key(None)


def _vehicle_workspace_dir(vehicle_key: str | None = None, *, create: bool = True) -> Path:
    key = _normalize_vehicle_workspace_key(vehicle_key)
    root = _safe_repo_path(VEHICLE_WORKSPACE_ROOT / key)
    if create:
        for child in ("config", "builds", "results", "processing"):
            (root / child).mkdir(parents=True, exist_ok=True)
    return root


def _sync_vehicle_workspace_config(vehicle_key: str, source_path: Path, data: dict[str, Any]) -> Path:
    workspace = _vehicle_workspace_dir(vehicle_key)
    target = workspace / "config" / "vehicle.yml"
    shutil.copy2(source_path, target)
    vehicle = data.get("vehicle", {}) if isinstance(data, dict) else {}
    source_label = source_path.relative_to(ROOT).as_posix() if source_path.is_relative_to(ROOT) else str(source_path)
    manifest = {
        "vehicle_key": vehicle_key,
        "vehicle_name": vehicle.get("name") if isinstance(vehicle, dict) else None,
        "source_path": source_label,
        "updated_at": time.time(),
        "updated_label": time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()),
    }
    (workspace / "config" / "manifest.json").write_text(json.dumps(manifest, indent=2), encoding="utf-8")
    return target


def _result_matches_vehicle(result: dict[str, Any], vehicle_key: str | None) -> bool:
    if not vehicle_key:
        return True
    if str(result.get("vehicle_key") or "") == vehicle_key:
        return True
    vehicle_name = str(result.get("vehicle_name") or "")
    return bool(vehicle_name) and _saved_vehicle_id(vehicle_name) == vehicle_key


def _processing_workflows_path(vehicle_key: str | None = None, *, create: bool = True) -> Path:
    workspace = _vehicle_workspace_dir(vehicle_key, create=create)
    path = workspace / "processing" / "workflows.json"
    if create and not path.is_file():
        path.write_text("[]\n", encoding="utf-8")
    return path


def _processing_workflow_payload(item: dict[str, Any], vehicle_key: str) -> dict[str, Any]:
    created_at = float(item.get("created_at") or time.time())
    source_path = str(item.get("source_path") or "")
    signals = item.get("signals", [])
    if not isinstance(signals, list):
        signals = []
    payload = {
        "id": _result_slug(str(item.get("id") or item.get("label") or "processing"), "processing"),
        "label": str(item.get("label") or "Processing workflow"),
        "vehicle_key": vehicle_key,
        "source_path": source_path,
        "signals": [str(signal) for signal in signals],
        "output_name": str(item.get("output_name") or ""),
        "notes": str(item.get("notes") or ""),
        "created_at": created_at,
        "created_label": time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(created_at)),
    }
    payload["source"] = _path_payload(source_path) if source_path else None
    return payload


def _read_processing_workflows(vehicle_key: str | None = None) -> list[dict[str, Any]]:
    key = _normalize_vehicle_workspace_key(vehicle_key)
    path = _processing_workflows_path(key, create=False)
    if not path.is_file():
        return []
    raw = json.loads(path.read_text(encoding="utf-8"))
    if not isinstance(raw, list):
        return []
    workflows = []
    for item in raw:
        if isinstance(item, dict):
            workflows.append(_processing_workflow_payload(item, key))
    return workflows


def _write_processing_workflows(vehicle_key: str, workflows: list[dict[str, Any]]) -> None:
    path = _processing_workflows_path(vehicle_key)
    path.write_text(json.dumps(workflows, indent=2) + "\n", encoding="utf-8")


def processing_workflows_payload(vehicle_key: str | None = None) -> dict[str, Any]:
    key = _normalize_vehicle_workspace_key(vehicle_key)
    return {
        "vehicle_key": key,
        "workflows": _read_processing_workflows(key),
    }


def add_processing_workflow(payload: dict[str, Any]) -> dict[str, Any]:
    key = _normalize_vehicle_workspace_key(str(payload.get("vehicle_key") or ""))
    label = str(payload.get("label") or "").strip() or "Processing workflow"
    source_path = str(payload.get("source_path") or "").strip()
    signals = payload.get("signals", [])
    if not isinstance(signals, list):
        signals = []
    if source_path:
        source = _safe_repo_path(source_path)
        if not _is_result_source_path(source):
            raise ValueError("Processing source must be a CSV result source")

    existing = _read_processing_workflows(key)
    base_id = _result_slug(str(payload.get("id") or label), "processing")
    workflow_id = base_id
    suffix = 2
    existing_ids = {workflow["id"] for workflow in existing}
    while workflow_id in existing_ids:
        workflow_id = f"{base_id}-{suffix}"
        suffix += 1
    workflow = {
        "id": workflow_id,
        "label": label,
        "source_path": source_path,
        "signals": [str(signal) for signal in signals],
        "output_name": str(payload.get("output_name") or "").strip(),
        "notes": str(payload.get("notes") or "").strip(),
        "created_at": time.time(),
    }
    _write_processing_workflows(key, [*existing, workflow])
    return {"saved": _processing_workflow_payload(workflow, key), **processing_workflows_payload(key)}


def delete_processing_workflow(workflow_id: str, vehicle_key: str | None = None) -> dict[str, Any]:
    key = _normalize_vehicle_workspace_key(vehicle_key)
    workflows = _read_processing_workflows(key)
    remaining = [workflow for workflow in workflows if workflow["id"] != workflow_id]
    if len(remaining) == len(workflows):
        raise FileNotFoundError(workflow_id)
    _write_processing_workflows(key, remaining)
    return processing_workflows_payload(key)


def _saved_results_dir() -> Path:
    root = _safe_repo_path(SAVED_RESULTS_ROOT)
    root.mkdir(parents=True, exist_ok=True)
    return root


def _unique_result_dir(slug: str) -> Path:
    timestamp = time.strftime("%Y%m%d-%H%M%S", time.localtime())
    root = _saved_results_dir()
    base = f"{timestamp}-{slug}"
    candidate = root / base
    index = 2
    while candidate.exists():
        candidate = root / f"{base}-{index}"
        index += 1
    candidate.mkdir(parents=True)
    return candidate


def _result_file_payload(raw_path: str, label: str, kind: str, source_path: str | None = None) -> dict[str, Any]:
    return {
        "label": label,
        "kind": kind,
        "source_path": source_path,
        **_path_payload(raw_path),
    }


def _json_ready(value: Any) -> Any:
    if isinstance(value, dict):
        return {str(key): _json_ready(item) for key, item in value.items()}
    if isinstance(value, (list, tuple)):
        return [_json_ready(item) for item in value]
    if isinstance(value, Path):
        return str(value)
    if isinstance(value, (str, int, float, bool)) or value is None:
        return value
    return str(value)


def _workflow_run_target(workflow: WorkflowSpec) -> BuildTargetSpec | None:
    for action_id in workflow.actions:
        target = MODELICA_RUN_TARGETS_BY_ACTION.get(action_id)
        if target:
            return target
    return None


def _workflow_run_roots(workflow: WorkflowSpec) -> tuple[Path, ...]:
    target = _workflow_run_target(workflow)
    if not target:
        return ()
    build_dir = _safe_repo_path(target.build_dir)
    return (build_dir / "results", build_dir / "runs")


def _workflow_run_dirs(workflow: WorkflowSpec, *, since: float | None = None) -> list[Path]:
    run_dirs: dict[Path, Path] = {}
    min_mtime = (since - 2.0) if since else None
    for root in _workflow_run_roots(workflow):
        if not root.is_dir():
            continue
        for path in root.glob("run_*"):
            if not path.is_dir():
                continue
            try:
                file_mtimes = (child.stat().st_mtime for child in path.rglob("*") if child.is_file())
                mtime = max(file_mtimes, default=path.stat().st_mtime)
            except OSError:
                continue
            if min_mtime is not None and mtime < min_mtime:
                continue
            run_dirs[path.resolve()] = path
    return sorted(run_dirs.values(), key=lambda item: item.stat().st_mtime)


def _read_run_manifest(run_dir: Path) -> dict[str, Any]:
    manifest_path = run_dir / "manifest.json"
    if manifest_path.is_file():
        try:
            data = json.loads(manifest_path.read_text(encoding="utf-8"))
            if isinstance(data, dict):
                return data
        except (OSError, json.JSONDecodeError):
            pass
    return {
        "run_id": run_dir.name.removeprefix("run_"),
        "case_label": run_dir.name.replace("_", " "),
        "run_dir": str(run_dir),
    }


def _run_result_csv(run_dir: Path) -> Path | None:
    candidates = sorted(run_dir.glob("*_res.csv"))
    if not candidates:
        candidates = sorted(path for path in run_dir.glob("*.csv") if path.is_file())
    return candidates[0] if candidates else None


def _zip_text(archive: zipfile.ZipFile, arcname: str, text: str) -> None:
    archive.writestr(arcname, text if text.endswith("\n") else f"{text}\n")


def _build_signal_archive(
    workflow: WorkflowSpec,
    archive_path: Path,
    *,
    since: float | None = None,
) -> dict[str, Any]:
    run_dirs = _workflow_run_dirs(workflow, since=since)
    archive_path.parent.mkdir(parents=True, exist_ok=True)
    runs: list[dict[str, Any]] = []
    created_at = time.time()

    with zipfile.ZipFile(archive_path, "w", compression=zipfile.ZIP_DEFLATED) as archive:
        for index, run_dir in enumerate(run_dirs, start=1):
            manifest = _read_run_manifest(run_dir)
            label = str(manifest.get("case_label") or manifest.get("label") or run_dir.name)
            run_slug = _result_slug(label, run_dir.name)
            arc_prefix = f"runs/{index:03d}-{run_slug}"
            result_csv = _run_result_csv(run_dir)
            run_info = {
                "index": index,
                "id": str(manifest.get("run_id") or run_dir.name.removeprefix("run_")),
                "label": label,
                "source_dir": run_dir.relative_to(ROOT).as_posix() if run_dir.is_relative_to(ROOT) else str(run_dir),
                "signals_file": f"{arc_prefix}/signals.csv" if result_csv else None,
                "description_file": f"{arc_prefix}/description.json",
                "log_file": f"{arc_prefix}/run.log" if (run_dir / "run.log").is_file() else None,
                "overrides_file": f"{arc_prefix}/overrides.txt" if (run_dir / "overrides.txt").is_file() else None,
            }
            runs.append(run_info)

            if result_csv:
                archive.write(result_csv, f"{arc_prefix}/signals.csv")
            for source_name in ("overrides.txt", "run.log"):
                source = run_dir / source_name
                if source.is_file():
                    archive.write(source, f"{arc_prefix}/{source_name}")
            _zip_text(
                archive,
                f"{arc_prefix}/description.json",
                json.dumps(
                    {
                        "workflow": {"id": workflow.id, "label": workflow.label, "group": workflow.group},
                        "run": run_info,
                        "manifest": _json_ready(manifest),
                    },
                    indent=2,
                ),
            )

        archive_manifest = {
            "workflow": {"id": workflow.id, "label": workflow.label, "group": workflow.group},
            "created_at": created_at,
            "created_label": time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(created_at)),
            "run_count": len(runs),
            "runs": runs,
        }
        _zip_text(archive, "manifest.json", json.dumps(archive_manifest, indent=2))
        if not runs:
            _zip_text(
                archive,
                "README.txt",
                "No retained Modelica run directories were found for this workflow. "
                "Run configs must keep execution.cleanup false to include raw per-run signals.",
            )

    return {
        "run_count": len(runs),
        "runs": runs,
        "archive_path": (
            archive_path.relative_to(ROOT).as_posix()
            if archive_path.is_relative_to(ROOT)
            else str(archive_path)
        ),
    }


def _result_manifest_payload(path: Path) -> dict[str, Any]:
    manifest = json.loads(path.read_text(encoding="utf-8"))
    files = []
    for item in manifest.get("files", []):
        if not isinstance(item, dict):
            continue
        raw_path = str(item.get("path") or "")
        if not raw_path:
            continue
        files.append(
            _result_file_payload(
                raw_path,
                str(item.get("label") or Path(raw_path).name),
                str(item.get("kind") or "file"),
                str(item.get("source_path") or ""),
            )
        )
    manifest["files"] = files
    return manifest


def saved_results_payload(vehicle_key: str | None = None) -> dict[str, Any]:
    key = _normalize_vehicle_workspace_key(vehicle_key) if vehicle_key else None
    results = []
    if key:
        workspace_results = _vehicle_workspace_dir(key, create=False) / "results"
        if workspace_results.is_dir():
            for manifest_path in workspace_results.glob("*/manifest.json"):
                try:
                    result = _result_manifest_payload(manifest_path)
                except (OSError, json.JSONDecodeError, ValueError):
                    continue
                if not _result_matches_vehicle(result, key):
                    continue
                results.append(result)
    else:
        root = _saved_results_dir()
        for manifest_path in root.glob("*/manifest.json"):
            try:
                results.append(_result_manifest_payload(manifest_path))
            except (OSError, json.JSONDecodeError, ValueError):
                continue
    results.sort(key=lambda item: float(item.get("created_at") or 0.0), reverse=True)
    return {"vehicle_key": key or _active_vehicle_workspace_key(), "results": results}


def _validated_result_id(raw_result_id: str) -> str:
    result_id = str(raw_result_id or "").strip()
    if not result_id or not re.fullmatch(r"[A-Za-z0-9_.-]+", result_id):
        raise ValueError("Invalid archived result id")
    return result_id


def _remove_result_dir(path: Path, root: Path) -> bool:
    path = path.resolve()
    root = root.resolve()
    if path == root or root not in path.parents:
        raise ValueError(f"Archived result path escapes root: {path}")
    if not path.exists():
        return False
    if not path.is_dir():
        raise ValueError(f"Archived result is not a directory: {path}")
    shutil.rmtree(path)
    return True


def delete_saved_result(result_id: str, vehicle_key: str | None = None) -> dict[str, Any]:
    result_id = _validated_result_id(result_id)
    removed: list[str] = []
    manifest_vehicle_key = ""
    workspace_path = ""
    saved_root = _saved_results_dir()
    global_result_dir = _safe_repo_path(saved_root / result_id)
    global_manifest = global_result_dir / "manifest.json"

    if global_manifest.is_file():
        try:
            manifest = json.loads(global_manifest.read_text(encoding="utf-8"))
            if isinstance(manifest, dict):
                manifest_vehicle_key = str(manifest.get("vehicle_key") or "")
                workspace_path = str(manifest.get("workspace_result_path") or "")
        except (OSError, json.JSONDecodeError):
            pass

    if _remove_result_dir(global_result_dir, saved_root):
        removed.append(global_result_dir.relative_to(ROOT).as_posix())

    workspace_root = _safe_repo_path(VEHICLE_WORKSPACE_ROOT)
    workspace_candidates: dict[Path, None] = {}
    for key in (vehicle_key, manifest_vehicle_key):
        if key:
            workspace_candidates[_vehicle_workspace_dir(key, create=False) / "results" / result_id] = None
    if workspace_path:
        workspace_candidates[_safe_repo_path(workspace_path)] = None
    if workspace_root.is_dir():
        for candidate in workspace_root.glob(f"*/results/{result_id}"):
            workspace_candidates[candidate] = None

    for candidate in workspace_candidates:
        if _remove_result_dir(candidate, workspace_root):
            removed.append(candidate.relative_to(ROOT).as_posix())

    if not removed:
        raise FileNotFoundError(result_id)
    return {
        "deleted": result_id,
        "removed": removed,
        **saved_results_payload(vehicle_key if vehicle_key else None),
    }


def save_active_results(
    workflow_id: str,
    name: str | None = None,
    *,
    since: float | None = None,
    job_id: str | None = None,
) -> dict[str, Any]:
    workflow = _workflow_by_id(workflow_id)
    existing_outputs = []
    for output in workflow.outputs:
        source = _safe_repo_path(output.path)
        if source.is_file():
            existing_outputs.append((output, source))
    if not existing_outputs:
        raise FileNotFoundError(f"No active output files exist for {workflow.label}")

    vehicle_path = _safe_repo_path("vehicle.yml")
    vehicle_data = _load_vehicle_yaml_file(vehicle_path) if vehicle_path.is_file() else {}
    vehicle_key = _vehicle_workspace_key_from_data(vehicle_data)
    label = str(name or "").strip() or f"{workflow.label} results"
    result_dir = _unique_result_dir(_result_slug(label))
    workspace_result_dir = _vehicle_workspace_dir(vehicle_key) / "results" / result_dir.name
    files_dir = result_dir / "files"
    files_dir.mkdir()
    created_at = time.time()

    file_entries = []
    used_names: set[str] = set()
    for output, source in existing_outputs:
        stem = _result_slug(output.label, "output")
        suffix = source.suffix or ".dat"
        file_name = f"{stem}{suffix}"
        index = 2
        while file_name in used_names:
            file_name = f"{stem}-{index}{suffix}"
            index += 1
        used_names.add(file_name)
        target = files_dir / file_name
        shutil.copy2(source, target)
        file_entries.append(
            {
                "label": output.label,
                "kind": output.kind,
                "source_path": output.path,
                "path": target.relative_to(ROOT).as_posix(),
            }
        )

    vehicle_snapshot = None
    if vehicle_path.is_file():
        snapshot = result_dir / "vehicle.yml"
        shutil.copy2(vehicle_path, snapshot)
        vehicle_snapshot = snapshot.relative_to(ROOT).as_posix()

    config_snapshot = None
    if workflow.config:
        config_path = _safe_repo_path(workflow.config)
        if config_path.is_file():
            snapshot = result_dir / "config.yml"
            shutil.copy2(config_path, snapshot)
            config_snapshot = snapshot.relative_to(ROOT).as_posix()

    architecture = vehicle_data.get("architecture", {}) if isinstance(vehicle_data, dict) else {}
    vehicle = vehicle_data.get("vehicle", {}) if isinstance(vehicle_data, dict) else {}
    analysis = _build_signal_archive(workflow, files_dir / "signals.zip", since=since)
    file_entries.append(
        {
            "label": "Signal Archive",
            "kind": "zip",
            "source_path": "",
            "path": (files_dir / "signals.zip").relative_to(ROOT).as_posix(),
        }
    )
    description = {
        "label": label,
        "workflow": {"id": workflow.id, "label": workflow.label, "group": workflow.group},
        "vehicle_name": vehicle.get("name") if isinstance(vehicle, dict) else None,
        "architecture": architecture if isinstance(architecture, dict) else {},
        "created_at": created_at,
        "created_label": time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(created_at)),
        "job_id": job_id,
        "run_count": analysis["run_count"],
        "files": [
            {"label": item["label"], "kind": item["kind"], "source_path": item.get("source_path") or ""}
            for item in file_entries
        ],
    }
    description_path = files_dir / "run-description.json"
    description_path.write_text(json.dumps(_json_ready(description), indent=2), encoding="utf-8")
    file_entries.append(
        {
            "label": "Run Description",
            "kind": "json",
            "source_path": "",
            "path": description_path.relative_to(ROOT).as_posix(),
        }
    )
    manifest = {
        "id": result_dir.name,
        "label": label,
        "vehicle_key": vehicle_key,
        "workspace_result_path": workspace_result_dir.relative_to(ROOT).as_posix(),
        "created_at": created_at,
        "created_label": time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(created_at)),
        "workflow": {"id": workflow.id, "label": workflow.label, "group": workflow.group},
        "vehicle_name": vehicle.get("name") if isinstance(vehicle, dict) else None,
        "architecture": architecture if isinstance(architecture, dict) else {},
        "vehicle_snapshot": vehicle_snapshot,
        "config_snapshot": config_snapshot,
        "analysis": analysis,
        "run_count": analysis["run_count"],
        "files": file_entries,
    }
    (result_dir / "manifest.json").write_text(json.dumps(manifest, indent=2), encoding="utf-8")
    shutil.copytree(result_dir, workspace_result_dir, dirs_exist_ok=True)
    workspace_rel = workspace_result_dir.relative_to(ROOT).as_posix()
    workspace_manifest = copy.deepcopy(manifest)
    workspace_manifest["files"] = [
        {
            **entry,
            "path": f"{workspace_rel}/files/{Path(str(entry['path'])).name}",
        }
        for entry in file_entries
    ]
    if vehicle_snapshot:
        workspace_manifest["vehicle_snapshot"] = f"{workspace_rel}/vehicle.yml"
    if config_snapshot:
        workspace_manifest["config_snapshot"] = f"{workspace_rel}/config.yml"
    if isinstance(workspace_manifest.get("analysis"), dict) and workspace_manifest["analysis"].get("archive_path"):
        workspace_manifest["analysis"]["archive_path"] = f"{workspace_rel}/files/signals.zip"
    (workspace_result_dir / "manifest.json").write_text(json.dumps(workspace_manifest, indent=2), encoding="utf-8")
    return {
        "saved": _result_manifest_payload(workspace_result_dir / "manifest.json"),
        **saved_results_payload(),
    }


def vehicle_template_payloads() -> dict[str, Any]:
    template_root = _safe_repo_path("_0_Utils/vehicle_templates")
    templates = []
    for path in sorted(template_root.glob("*.yml")):
        raw = path.read_text(encoding="utf-8", errors="replace")
        data = yaml.safe_load(raw) or {}
        if not isinstance(data, dict):
            continue
        vehicle = data.get("vehicle", {})
        architecture = data.get("architecture", {})
        templates.append(
            {
                "id": path.stem,
                "path": path.relative_to(ROOT).as_posix(),
                "label": vehicle.get("name", path.stem) if isinstance(vehicle, dict) else path.stem,
                "front": architecture.get("front") if isinstance(architecture, dict) else None,
                "rear": architecture.get("rear") if isinstance(architecture, dict) else None,
                **_powertrain_payload(data),
            }
        )
    return {"templates": templates, "powertrains": [dict(item) for item in POWERTRAIN_IMPLEMENTATIONS]}


def _powertrain_payload(data: dict[str, Any]) -> dict[str, Any]:
    powertrain_id = _powertrain_id(data)
    implementation = next(
        (item for item in POWERTRAIN_IMPLEMENTATIONS if item["id"] == powertrain_id),
        POWERTRAIN_IMPLEMENTATIONS[0],
    )
    return {
        "powertrain": implementation["id"],
        "powertrain_label": implementation["label"],
        "powertrain_status": implementation["status"],
        "powertrain_components": list(implementation["components"]),
    }


def _powertrain_id(data: dict[str, Any]) -> str:
    explicit = data.get("powertrain")
    if isinstance(explicit, dict) and explicit.get("implementation"):
        return str(explicit["implementation"])
    vehicle = data.get("vehicle", {})
    name = vehicle.get("name", "") if isinstance(vehicle, dict) else ""
    prefix = str(name).split("_", 1)[0]
    known = {str(item["id"]) for item in POWERTRAIN_IMPLEMENTATIONS}
    return prefix if prefix in known else str(POWERTRAIN_IMPLEMENTATIONS[0]["id"])


def _vehicle_summary(source_id: str, source_type: str, path: Path, data: dict[str, Any]) -> dict[str, Any]:
    vehicle = data.get("vehicle", {})
    architecture = data.get("architecture", {})
    label = vehicle.get("name", path.stem) if isinstance(vehicle, dict) else path.stem
    return {
        "id": source_id,
        "type": source_type,
        "path": path.relative_to(ROOT).as_posix() if path.is_relative_to(ROOT) else str(path),
        "label": label,
        "front": architecture.get("front") if isinstance(architecture, dict) else None,
        "rear": architecture.get("rear") if isinstance(architecture, dict) else None,
        **_powertrain_payload(data),
    }


def _load_vehicle_yaml_file(path: Path) -> dict[str, Any]:
    data = yaml.safe_load(path.read_text(encoding="utf-8", errors="replace")) or {}
    if not isinstance(data, dict):
        raise TypeError(f"{path} must contain a vehicle YAML mapping")
    return data


def _saved_vehicle_id(raw_name: str) -> str:
    base = raw_name.strip() or "vehicle"
    slug = re.sub(r"[^A-Za-z0-9_.-]+", "-", base).strip("-_.").lower()
    return slug or "vehicle"


def _saved_vehicle_path(vehicle_id: str) -> Path:
    if vehicle_id != _saved_vehicle_id(vehicle_id):
        raise ValueError("Invalid saved vehicle id")
    return _safe_repo_path(SAVED_VEHICLE_ROOT / f"{vehicle_id}.yml")


def vehicle_library_payload() -> dict[str, Any]:
    active_path = _safe_repo_path("vehicle.yml")
    active_data = _load_vehicle_yaml_file(active_path)
    sources = [_vehicle_summary("active", "active", active_path, active_data)]

    saved_root = _safe_repo_path(SAVED_VEHICLE_ROOT)
    if saved_root.is_dir():
        for path in sorted(saved_root.glob("*.yml")):
            data = _load_vehicle_yaml_file(path)
            sources.append(_vehicle_summary(f"saved:{path.stem}", "saved", path, data))

    template_root = _safe_repo_path("_0_Utils/vehicle_templates")
    if template_root.is_dir():
        for path in sorted(template_root.glob("*.yml")):
            data = _load_vehicle_yaml_file(path)
            sources.append(_vehicle_summary(f"template:{path.stem}", "template", path, data))

    return {"vehicles": sources}


def load_vehicle_source(source_id: str) -> dict[str, Any]:
    if source_id == "active":
        return config_payload("vehicle")
    if source_id.startswith("template:"):
        template_id = source_id.removeprefix("template:")
        return apply_vehicle_template(template_id)
    if source_id.startswith("saved:"):
        vehicle_id = source_id.removeprefix("saved:")
        source = _saved_vehicle_path(vehicle_id)
        if not source.is_file():
            raise FileNotFoundError(source_id)
        target = _safe_repo_path("vehicle.yml")
        target.write_text(source.read_text(encoding="utf-8"), encoding="utf-8")
        return config_payload("vehicle")
    raise ValueError(f"Unknown vehicle source: {source_id}")


def save_active_vehicle(name: str | None = None) -> dict[str, Any]:
    active_path = _safe_repo_path("vehicle.yml")
    data = _load_vehicle_yaml_file(active_path)
    vehicle = data.get("vehicle", {})
    default_name = vehicle.get("name", "vehicle") if isinstance(vehicle, dict) else "vehicle"
    vehicle_id = _saved_vehicle_id(name or str(default_name))
    saved_path = _saved_vehicle_path(vehicle_id)
    saved_path.parent.mkdir(parents=True, exist_ok=True)
    saved_path.write_text(active_path.read_text(encoding="utf-8"), encoding="utf-8")
    _sync_vehicle_workspace_config(vehicle_id, saved_path, data)
    return {
        "saved": _vehicle_summary(f"saved:{vehicle_id}", "saved", saved_path, data),
        "workspace": vehicle_workspace_payload(vehicle_id),
        **vehicle_library_payload(),
    }


def delete_saved_vehicle(source_id: str) -> dict[str, Any]:
    if not source_id.startswith("saved:"):
        raise ValueError("Only saved vehicle configs can be deleted")
    vehicle_id = source_id.removeprefix("saved:")
    path = _saved_vehicle_path(vehicle_id)
    if not path.is_file():
        raise FileNotFoundError(source_id)
    path.unlink()
    return vehicle_library_payload()


def _tire_template_root_from_active_vehicle() -> Path:
    active_path = _safe_repo_path("vehicle.yml")
    data = _load_vehicle_yaml_file(active_path)
    paths = data.get("paths", {})
    raw_root = "_0_Utils/tire_templates"
    if isinstance(paths, dict) and paths.get("tire_templates"):
        raw_root = str(paths["tire_templates"])
    root = _safe_repo_path(raw_root)
    root.mkdir(parents=True, exist_ok=True)
    return root


def _tire_template_slug(raw_name: str) -> str:
    name = Path(raw_name).stem
    slug = re.sub(r"[^A-Za-z0-9_.-]+", "_", name).strip("._-")
    if not slug:
        raise ValueError("Tire template name is required")
    return slug


def _tire_template_file(raw_name: str) -> Path:
    template_id = _tire_template_slug(raw_name)
    return _tire_template_root_from_active_vehicle() / f"{template_id}.tir"


def tire_template_library_payload() -> dict[str, Any]:
    root = _tire_template_root_from_active_vehicle()
    templates = []
    for path in sorted(root.glob("*.tir")):
        stat = path.stat()
        templates.append(
            {
                "id": path.stem,
                "label": path.name,
                "path": path.relative_to(ROOT).as_posix(),
                "size": stat.st_size,
                "modified": stat.st_mtime,
            }
        )
    return {"templates": templates}


def read_tire_template(raw_name: str) -> dict[str, Any]:
    path = _tire_template_file(raw_name)
    if not path.is_file():
        raise FileNotFoundError(raw_name)
    text = path.read_text(encoding="utf-8", errors="replace")
    parsed = parse_tir(path)
    return {
        "id": path.stem,
        "label": path.name,
        "path": path.relative_to(ROOT).as_posix(),
        "text": text,
        "metadata": {
            "fznom_n": _num(parsed, "FNOMIN"),
            "fzmin_n": _num(parsed, "FZMIN"),
            "fzmax_n": _num(parsed, "FZMAX"),
            "pressure_pa": _num(parsed, "IP_NOM"),
            "unloaded_radius_m": _num(parsed, "UNLOADED_RADIUS"),
            "width_m": _num(parsed, "WIDTH"),
            "longvl_mps": _num(parsed, "LONGVL"),
        },
    }


def save_tire_template(raw_name: str, text: str) -> dict[str, Any]:
    path = _tire_template_file(raw_name)
    if "[MDI_HEADER]" not in text and "FNOMIN" not in text:
        raise ValueError("Tire template text does not look like a .tir file")
    path.write_text(text if text.endswith("\n") else f"{text}\n", encoding="utf-8")
    return read_tire_template(path.stem)


def apply_vehicle_template(template_id: str) -> dict[str, Any]:
    if "/" in template_id or "\\" in template_id or template_id.startswith("."):
        raise ValueError("Invalid template id")
    source = _safe_repo_path(f"_0_Utils/vehicle_templates/{template_id}.yml")
    if not source.is_file():
        raise FileNotFoundError(template_id)
    target = _safe_repo_path("vehicle.yml")
    target.write_text(source.read_text(encoding="utf-8"), encoding="utf-8")
    return config_payload("vehicle")

