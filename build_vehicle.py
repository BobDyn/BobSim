#!/usr/bin/env python3
"""
Build a BobLib vehicle record and replacement VehicleSim from a clean semantic
vehicle.yml.

Expected workflow:

    python build_vehicle.py

Outputs are written directly into BobLib:

    _0_Utils/external/BobLib/Resources/VehicleDefn/<RecordName>.mo
    _0_Utils/external/BobLib/Standards/VehicleSim.mo

Tire templates are resolved from:

    _0_Utils/tire_templates/<template>.tir

The vehicle YAML contains all non-tire vehicle parameters. Tire model
coefficients are the only vehicle data intentionally kept out of the YAML; they
are read from the local .tir file. Missing .tir files are treated as hard
errors.
"""

from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
from typing import Any
import re

try:
    import yaml
except ImportError as exc:  # pragma: no cover
    raise SystemExit(
        "Missing dependency: PyYAML. Install it with `python -m pip install pyyaml`."
    ) from exc


ARCH_TOKENS = {
    "direct": "DWDirect",
    "bellcrank": "DWBC",
    "bellcrank_stabar": "DWBCStabar",
}

AXLE_TYPES = {
    "direct": "Axle.AxleDW_DirectRecord",
    "bellcrank": "Axle.AxleDW_BCRecord",
    "bellcrank_stabar": "Axle.AxleDW_BC_StabarRecord",
}

DEFAULT_IMPORTS = [
    "BobLib.Resources.VehicleRecord.Chassis.Suspension.Templates.MassRecord",
]

DEFAULT_ALIASES = {
    "Aero": "BobLib.Resources.VehicleRecord.Aero",
    "TireModel": "BobLib.Resources.VehicleRecord.Chassis.Suspension.Templates.Tire.MF52",
    "Wheel": "BobLib.Resources.VehicleRecord.Chassis.Suspension.Templates.Tire",
    "Rack": "BobLib.Resources.VehicleRecord.Chassis.Suspension.Templates.SteeringRack",
    "Stabar": "BobLib.Resources.VehicleRecord.Chassis.Suspension.Templates.Stabar",
    "DW": "BobLib.Resources.VehicleRecord.Chassis.Suspension.Templates.DoubleWishbone",
    "Axle": "BobLib.Resources.VehicleRecord.Chassis.Suspension",
}

MF52_SECTION_FIELDS = {'fxCombined': ['RBX1', 'RBX2', 'RCX1', 'REX1', 'REX2', 'RHX1'],
 'fxPure': ['LFZO',
            'LGAX',
            'PCX1',
            'PDX1',
            'PDX2',
            'PDX3',
            'PKX1',
            'PKX2',
            'PKX3',
            'PHX1',
            'PHX2',
            'PVX1',
            'PVX2',
            'PEX1',
            'PEX2',
            'PEX3',
            'PEX4',
            'LCX',
            'LMUX',
            'LKX',
            'LHX',
            'LVX',
            'LEX',
            'LXAL'],
 'fyCombined': ['RBY1',
                'RBY2',
                'RBY3',
                'RCY1',
                'REY1',
                'REY2',
                'RHY1',
                'RHY2',
                'RVY1',
                'RVY2',
                'RVY3',
                'RVY4',
                'RVY5',
                'RVY6'],
 'fyPure': ['LFZO',
            'LGAY',
            'PCY1',
            'PDY1',
            'PDY2',
            'PDY3',
            'PKY1',
            'PKY2',
            'PKY3',
            'PHY1',
            'PHY2',
            'PHY3',
            'PVY1',
            'PVY2',
            'PVY3',
            'PVY4',
            'PEY1',
            'PEY2',
            'PEY3',
            'PEY4',
            'LCY',
            'LMUY',
            'LEY',
            'LKY',
            'LHY',
            'LVY',
            'LYKA',
            'LVYKA'],
 'mxCombined': [],
 'mxPure': ['QSX1', 'QSX2', 'QSX3', 'LMX', 'LVMX'],
 'myCombined': [],
 'myPure': ['QSY1', 'QSY2', 'QSY3', 'QSY4', 'Vref', 'LMY'],
 'mzCombined': ['SSZ1',
                'SSZ2',
                'SSZ3',
                'SSZ4',
                'RVY1',
                'RVY2',
                'RVY3',
                'RVY4',
                'RVY5',
                'RVY6',
                'LS',
                'LVYKA'],
 'mzPure': ['QBZ1',
            'QBZ2',
            'QBZ3',
            'QBZ4',
            'QBZ5',
            'QCZ1',
            'QDZ1',
            'QDZ2',
            'QDZ3',
            'QDZ4',
            'QEZ1',
            'QEZ2',
            'QEZ3',
            'QEZ4',
            'QEZ5',
            'QHZ1',
            'QHZ2',
            'QHZ3',
            'QHZ4',
            'QBZ9',
            'QBZ10',
            'QDZ6',
            'QDZ7',
            'QDZ8',
            'QDZ9',
            'LTR',
            'LRES',
            'LKY',
            'LMUY',
            'LGAZ'],
 'setup': ['FNOMIN', 'UNLOADED_RADIUS']}
TIRE_SECTION_TYPES = {
    "setup": "TireModel.SetupRecord",
    "fxPure": "TireModel.PureSlip.FxPureRecord",
    "fxCombined": "TireModel.CombinedSlip.FxCombinedRecord",
    "fyPure": "TireModel.PureSlip.FyPureRecord",
    "fyCombined": "TireModel.CombinedSlip.FyCombinedRecord",
    "mxPure": "TireModel.PureSlip.MxPureRecord",
    "mxCombined": "TireModel.CombinedSlip.MxCombinedRecord",
    "myPure": "TireModel.PureSlip.MyPureRecord",
    "myCombined": "TireModel.CombinedSlip.MyCombinedRecord",
    "mzPure": "TireModel.PureSlip.MzPureRecord",
    "mzCombined": "TireModel.CombinedSlip.MzCombinedRecord",
}


# Mapping from BobLib MF52 record field names to equivalent .tir keys.
# Example: BobLib MyPureRecord uses Vref, while PAC2002 .tir files
# typically store the reference/measurement speed as LONGVL.
TIR_KEY_ALIASES = {
    "VREF": "LONGVL",
}


@dataclass(frozen=True)
class BuildOutput:
    record_name: str
    variant_name: str
    vehicle_model_name: str
    source_yaml: Path
    record_path: Path
    vehicle_sim_path: Path


def repo_root() -> Path:
    return Path(__file__).resolve().parent


def vehicle_yaml_path() -> Path:
    return repo_root() / "vehicle.yml"


def node_value(node: Any, default: Any = None) -> Any:
    if isinstance(node, dict):
        if "Value" in node:
            return node["Value"]
        if "value" in node:
            return node["value"]
        if "Expression" in node:
            return {"expr": str(node["Expression"])}
        if "expr" in node:
            return {"expr": str(node["expr"])}
    return default if node is None else node


def load_yaml(path: Path) -> dict[str, Any]:
    if not path.exists():
        raise FileNotFoundError(f"Missing {path}. Create or copy a vehicle.yml first.")
    data = yaml.safe_load(path.read_text(encoding="utf-8"))
    if not isinstance(data, dict):
        raise ValueError(f"{path} must contain a YAML mapping.")
    if data.get("_TemplateEntrypointPlaceholder") is True:
        raise SystemExit(
            "vehicle.yml is still the placeholder. Copy a template into vehicle.yml, "
            "edit it, then rerun `python build_vehicle.py`."
        )
    return data


def require_mapping(data: dict[str, Any], key: str, yaml_path: Path) -> dict[str, Any]:
    value = data.get(key)
    if not isinstance(value, dict):
        raise ValueError(f"{yaml_path}: expected mapping at {key!r}.")
    return value


def get_path(data: dict[str, Any], keys: list[str], default: Any = None) -> Any:
    cur: Any = data
    for key in keys:
        if not isinstance(cur, dict) or key not in cur:
            return default
        cur = cur[key]
    return node_value(cur, default)


def norm_arch(value: str) -> str:
    v = str(value).strip()
    aliases = {
        "DWDirect": "direct",
        "direct": "direct",
        "DWBC": "bellcrank",
        "bellcrank": "bellcrank",
        "DWBCStabar": "bellcrank_stabar",
        "bellcrank_stabar": "bellcrank_stabar",
        "bellcrank+stabar": "bellcrank_stabar",
    }
    if v not in aliases:
        raise ValueError(f"Unknown architecture {value!r}. Expected one of {sorted(aliases)}.")
    return aliases[v]


def variant_name(data: dict[str, Any]) -> str:
    arch = require_mapping(data, "architecture", vehicle_yaml_path())
    front = norm_arch(str(arch.get("front")))
    rear = norm_arch(str(arch.get("rear")))
    return f"{ARCH_TOKENS[front]}_{ARCH_TOKENS[rear]}"


def record_name_from_yaml(data: dict[str, Any], yaml_path: Path) -> str:
    explicit = get_path(data, ["architecture", "record"])
    if isinstance(explicit, str) and explicit.strip():
        return explicit.strip()
    return f"{variant_name(data)}Record"


def record_to_variant(record_name: str) -> str:
    if not record_name.endswith("Record"):
        raise ValueError(f"Record name must end with `Record`. Got {record_name!r}.")
    return record_name[:-len("Record")]


def vehicle_model_name(data: dict[str, Any], record_name: str) -> str:
    explicit = get_path(data, ["architecture", "vehicle_model"])
    if isinstance(explicit, str) and explicit.strip():
        return explicit.strip()
    return f"Vehicle_{record_to_variant(record_name)}"


def output_record_package(data: dict[str, Any]) -> str:
    return str(get_path(data, ["output", "record_package"], "BobLib.Resources.VehicleDefn"))


def output_sim_package(data: dict[str, Any]) -> str:
    return str(get_path(data, ["output", "sim_package"], "BobLib.Standards"))


def boblib_root(data: dict[str, Any]) -> Path:
    raw = get_path(data, ["paths", "boblib"], "_0_Utils/external/BobLib")
    path = Path(str(raw))
    return path if path.is_absolute() else repo_root() / path


def tire_templates_root(data: dict[str, Any]) -> Path:
    raw = get_path(data, ["paths", "tire_templates"], "_0_Utils/tire_templates")
    path = Path(str(raw))
    return path if path.is_absolute() else repo_root() / path


def boblib_vehicledefn_dir(data: dict[str, Any]) -> Path:
    return boblib_root(data) / "Resources" / "VehicleDefn"


def boblib_vehiclesim_path(data: dict[str, Any]) -> Path:
    return boblib_root(data) / "Standards" / "VehicleSim.mo"


def modelica_number(value: int | float) -> str:
    return repr(value)


def modelica_value(value: Any) -> str:
    value = node_value(value)
    if isinstance(value, dict):
        if "expr" in value:
            return str(value["expr"])
        if "Expression" in value:
            return str(value["Expression"])
        raise TypeError(f"Unsupported Modelica expression dict: {value!r}")
    if isinstance(value, bool):
        return "true" if value else "false"
    if isinstance(value, (int, float)):
        return modelica_number(value)
    if isinstance(value, str):
        return value
    if isinstance(value, list):
        if value and all(isinstance(row, list) for row in value):
            rows = [", ".join(modelica_value(item) for item in row) for row in value]
            return "{" + ", ".join("{" + row + "}" for row in rows) + "}"
        return "{" + ", ".join(modelica_value(item) for item in value) + "}"
    raise TypeError(f"Unsupported value for Modelica rendering: {value!r}")


def modelica_table(rows: list[list[Any]]) -> str:
    return "[" + "; ".join(", ".join(modelica_value(v) for v in row) for row in rows) + "]"


def constructor(name: str, fields: dict[str, Any]) -> dict[str, Any]:
    return {"constructor": name, "fields": fields}


def render_constructor(name: str, fields: dict[str, Any]) -> str:
    if not fields:
        return f"{name}()"
    body = ", ".join(f"{key} = {render_field_value(value)}" for key, value in fields.items())
    return f"{name}({body})"


def render_field_value(value: Any) -> str:
    if isinstance(value, dict):
        if "table" in value:
            return modelica_table(value["table"])
        if "constructor" in value:
            return render_constructor(str(value["constructor"]), value.get("fields", {}))
    return modelica_value(value)


def render_parameter(name: str, modelica_type: str, fields: dict[str, Any]) -> str:
    if not fields:
        return f"parameter {modelica_type} {name};"
    assignments = [f"    {key} = {render_field_value(value)}" for key, value in fields.items()]
    return f"parameter {modelica_type} {name}(\n" + ",\n".join(assignments) + ");"


def parse_tir(path: Path) -> dict[str, float | str]:
    params: dict[str, float | str] = {}
    if not path.exists():
        return params
    line_re = re.compile(r"^\s*([A-Za-z_][A-Za-z0-9_]*)\s*=\s*(.*?)\s*(?:\$.*)?$")
    for line in path.read_text(encoding="utf-8", errors="ignore").splitlines():
        match = line_re.match(line)
        if not match:
            continue
        key = match.group(1).upper()
        raw = match.group(2).strip().strip("'").strip('"')
        try:
            params[key] = float(raw)
        except ValueError:
            params[key] = raw
    return params


def tire_template_name(data: dict[str, Any], side: dict[str, Any]) -> str:
    explicit = get_path(side, ["tire", "template"])
    if isinstance(explicit, str) and explicit.strip():
        return explicit.strip()
    default = get_path(data, ["defaults", "tire_template"])
    if isinstance(default, str) and default.strip():
        return default.strip()
    raise ValueError("Missing tire template. Set defaults.tire_template or <side>.tire.template.")


def build_mf52_fields(data: dict[str, Any], side: dict[str, Any], unloaded_radius_expr: str) -> dict[str, Any]:
    """Build BobLib MF52 fields from a local .tir file.

    Vehicle YAML intentionally does not carry tire-model coefficients. The .tir
    is the source of truth for tire coefficients; missing tire files or missing
    required coefficients fail fast so the generated record is not silently
    populated with hidden defaults.
    """
    template = tire_template_name(data, side)
    tir_path = tire_templates_root(data) / f"{template}.tir"

    if not tir_path.exists():
        raise FileNotFoundError(
            f"Missing tire template: {tir_path}\n"
            "Place the .tir file under paths.tire_templates, or update "
            "<side>.tire.template / defaults.tire_template in vehicle.yml."
        )

    tir = parse_tir(tir_path)
    if not tir:
        raise ValueError(f"Tire template {tir_path} did not contain parseable key=value coefficients.")

    out: dict[str, Any] = {}
    missing: list[str] = []

    for section, keys in MF52_SECTION_FIELDS.items():
        fields: dict[str, Any] = {}
        for key in keys:
            if key == "UNLOADED_RADIUS":
                fields[key] = {"expr": unloaded_radius_expr}
                continue
            tir_key = key.upper()
            lookup_key = TIR_KEY_ALIASES.get(tir_key, tir_key)
            if lookup_key not in tir:
                if lookup_key != tir_key:
                    missing.append(f"{tir_key}({lookup_key})")
                else:
                    missing.append(tir_key)
                continue
            fields[key] = tir[lookup_key]
        out[section] = constructor(TIRE_SECTION_TYPES[section], fields)

    if missing:
        preview = ", ".join(missing[:25])
        extra = "" if len(missing) <= 25 else f", ... ({len(missing)} total)"
        raise ValueError(
            f"Tire template {tir_path} is missing required MF52 coefficients: "
            f"{preview}{extra}\n"
            "Known aliases are supported for naming differences, e.g. "
            "BobLib Vref <- .tir LONGVL."
        )

    return out


def require_side(data: dict[str, Any], side_name: str) -> dict[str, Any]:
    side = data.get(side_name)
    if not isinstance(side, dict):
        raise ValueError(f"vehicle.yml: expected mapping for {side_name!r}.")
    return side


def require_section(parent: dict[str, Any], path: str, section: str) -> dict[str, Any]:
    value = parent.get(section)
    if not isinstance(value, dict):
        raise ValueError(f"vehicle.yml: expected {path}.{section} mapping.")
    return value


def require_key(section: dict[str, Any], path: str, key: str) -> Any:
    if key not in section:
        raise ValueError(f"vehicle.yml: missing {path}.{key}")
    return node_value(section[key])


def pickup_indices(order: list[str], required: list[str]) -> dict[str, int]:
    normalized = [str(item).strip().lower() for item in order]
    if sorted(normalized) != sorted(required):
        raise ValueError(f"pickup order must contain exactly {required}, got {order}")
    return {name: normalized.index(name) + 1 for name in required}


def spring_table(rate: Any) -> dict[str, Any]:
    return {"table": [[0, 0], [1, rate]]}


def damper_table(rate: Any) -> dict[str, Any]:
    return {"table": [[-1, -float(rate)], [0, 0], [1, rate]]}


def mass_record(value: dict[str, Any]) -> dict[str, Any]:
    return constructor("MassRecord", {
        "m": require_key(value, "mass", "mass_kg"),
        "rCM": require_key(value, "mass", "cg_m"),
        "inertia": require_key(value, "mass", "inertia_kg_m2"),
    })


def side_parameters(data: dict[str, Any], side_name: str, prefix: str, topology: str) -> list[tuple[str, str, dict[str, Any]]]:
    side = require_side(data, side_name)
    wheel = require_section(side, side_name, "wheel")
    tire = require_section(side, side_name, "tire")
    suspension = require_section(side, side_name, "suspension")
    steering = require_section(side, side_name, "steering")
    actuation = require_section(side, side_name, "actuation")
    shock = require_section(actuation, f"{side_name}.actuation", "shock")
    masses = require_section(side, side_name, "masses")

    params: list[tuple[str, str, dict[str, Any]]] = []

    axle_fields: dict[str, Any] = {
        "shockMount": require_key(shock, f"{side_name}.actuation.shock", "mount_m"),
        "springTable": spring_table(require_key(shock, f"{side_name}.actuation.shock", "spring_rate_n_per_m")),
        "springFreeLength": require_key(shock, f"{side_name}.actuation.shock", "free_length_m"),
        "damperTable": damper_table(require_key(shock, f"{side_name}.actuation.shock", "damper_rate_n_s_per_m")),
    }

    if topology in {"bellcrank", "bellcrank_stabar"}:
        bellcrank = require_section(actuation, f"{side_name}.actuation", "bellcrank")
        pickups = require_section(bellcrank, f"{side_name}.actuation.bellcrank", "pickups_m")
        required = ["rod", "shock"] + (["stabar"] if topology == "bellcrank_stabar" else [])
        indices = pickup_indices(require_key(bellcrank, f"{side_name}.actuation.bellcrank", "order"), required)
        axle_fields = {
            "bellcrankPivot": require_key(bellcrank, f"{side_name}.actuation.bellcrank", "pivot_m"),
            "bellcrankPivotAxis": require_key(bellcrank, f"{side_name}.actuation.bellcrank", "axis"),
            "bellcrankRodPickup": require_key(pickups, f"{side_name}.actuation.bellcrank.pickups_m", "rod"),
            "bellcrankShockPickup": require_key(pickups, f"{side_name}.actuation.bellcrank.pickups_m", "shock"),
            **({"bellcrankStabarPickup": require_key(pickups, f"{side_name}.actuation.bellcrank.pickups_m", "stabar")} if topology == "bellcrank_stabar" else {}),
            "rodPickup": indices["rod"],
            "shockPickup": indices["shock"],
            **({"stabarPickup": indices["stabar"]} if topology == "bellcrank_stabar" else {}),
            **axle_fields,
        }

    params.append((f"p{prefix}AxleDW", AXLE_TYPES[topology], axle_fields))

    if topology == "bellcrank_stabar":
        stabar = require_section(actuation, f"{side_name}.actuation", "stabar")
        params.append((f"p{prefix}Stabar", "Stabar.StabarRecord", {
            "leftArmEnd": require_key(stabar, f"{side_name}.actuation.stabar", "arm_end_m"),
            "leftBarEnd": require_key(stabar, f"{side_name}.actuation.stabar", "bar_end_m"),
            "barRate": require_key(stabar, f"{side_name}.actuation.stabar", "rate_n_m_per_rad"),
        }))

    radius = require_key(wheel, f"{side_name}.wheel", "radius_m")
    rim_radius_ratio = require_key(wheel, f"{side_name}.wheel", "rim_radius_ratio")
    rim_width_ratio = require_key(wheel, f"{side_name}.wheel", "rim_width_ratio")
    params.append((f"p{prefix}PartialWheel", "Wheel.Templates.PartialWheelRecord", {
        "R0": radius,
        "rimR0": {"expr": f"{modelica_value(radius)}*{modelica_value(rim_radius_ratio)}"},
        "rimWidth": {"expr": f"{modelica_value(radius)}*{modelica_value(rim_radius_ratio)}*{modelica_value(rim_width_ratio)}"},
        "staticAlpha": require_key(wheel, f"{side_name}.wheel", "toe_deg"),
        "staticGamma": require_key(wheel, f"{side_name}.wheel", "camber_deg"),
    }))

    params.append((f"p{prefix}Rack", "Rack.RackAndPinionRecord", {
        "leftPickup": require_key(steering, f"{side_name}.steering", "rack_pickup_m"),
        "cFactor": require_key(steering, f"{side_name}.steering", "rack_travel_per_rev_m"),
    }))

    params.append((f"p{prefix}DW", "DW.WishboneUprightLoopRecord", {
        "upperFore_i": require_key(suspension, f"{side_name}.suspension", "upper_fore_i_m"),
        "upperAft_i": require_key(suspension, f"{side_name}.suspension", "upper_aft_i_m"),
        "lowerFore_i": require_key(suspension, f"{side_name}.suspension", "lower_fore_i_m"),
        "lowerAft_i": require_key(suspension, f"{side_name}.suspension", "lower_aft_i_m"),
        "upper_o": require_key(suspension, f"{side_name}.suspension", "upper_o_m"),
        "lower_o": require_key(suspension, f"{side_name}.suspension", "lower_o_m"),
        "tie_o": require_key(suspension, f"{side_name}.suspension", "tie_o_m"),
        "wheelCenter": require_key(suspension, f"{side_name}.suspension", "wheel_center_m"),
        "rodToLower": str(require_key(actuation, f"{side_name}.actuation", "rod_to")).lower() == "lower",
        "rodMount": require_key(actuation, f"{side_name}.actuation", "rod_mount_m"),
    }))

    params.append((f"p{prefix}AxleMass", "Axle.Templates.AxleMassRecord", {
        "unsprungMass": mass_record(require_section(masses, f"{side_name}.masses", "unsprung")),
        "ucaMass": mass_record(require_section(masses, f"{side_name}.masses", "upper_control_arm")),
        "lcaMass": mass_record(require_section(masses, f"{side_name}.masses", "lower_control_arm")),
        "tieMass": mass_record(require_section(masses, f"{side_name}.masses", "tie_rod")),
    }))

    params.append((f"p{prefix}Tire1DOF_YParams", "Wheel.Wheel1DOF_YRecord", {
        "wheelJ": require_key(tire, f"{side_name}.tire", "wheel_inertia_kg_m2"),
    }))
    params.append((f"p{prefix}Tire1DOF_ZParams", "Wheel.Wheel1DOF_ZRecord", {
        "wheelC": require_key(tire, f"{side_name}.tire", "vertical_stiffness_n_per_m"),
        "wheelD": require_key(tire, f"{side_name}.tire", "vertical_damping_n_s_per_m"),
    }))
    params.append((f"p{prefix}TireModel", "TireModel.MF52Record", build_mf52_fields(data, side, f"p{prefix}PartialWheel.R0")))
    return params


def parameter_sections(data: dict[str, Any]) -> list[tuple[str, str, dict[str, Any]]]:
    arch = require_mapping(data, "architecture", vehicle_yaml_path())
    front_topology = norm_arch(str(arch.get("front")))
    rear_topology = norm_arch(str(arch.get("rear")))
    params = []
    params.extend(side_parameters(data, "front", "Fr", front_topology))
    params.extend(side_parameters(data, "rear", "Rr", rear_topology))

    sprung = require_mapping(data, "sprung_mass", vehicle_yaml_path())
    params.append(("pSprungMass", "MassRecord", {
        "m": require_key(sprung, "sprung_mass", "mass_kg"),
        "rCM": require_key(sprung, "sprung_mass", "cg_m"),
        "inertia": require_key(sprung, "sprung_mass", "inertia_kg_m2"),
    }))

    aero = data.get("aero")
    if isinstance(aero, dict):
        params.append(("pAero", "Aero.CFDAeroMapRecord", {
            "referenceSpeed": require_key(aero, "aero", "reference_speed_m_per_s"),
            "frontRideHeightGrid": require_key(aero, "aero", "front_ride_height_grid_m"),
            "rearRideHeightGrid": require_key(aero, "aero", "rear_ride_height_grid_m"),
            "dragTable": require_key(aero, "aero", "drag_table_n"),
            "downforceTable": require_key(aero, "aero", "downforce_table_n"),
            "mxTable": require_key(aero, "aero", "mx_table_nm"),
            "myTable": require_key(aero, "aero", "my_table_nm"),
            "mzTable": require_key(aero, "aero", "mz_table_nm"),
        }))
    return params


def render_record(data: dict[str, Any], yaml_path: Path) -> str:
    record_package = output_record_package(data)
    record_name = record_name_from_yaml(data, yaml_path)

    lines = [
        f"within {record_package};",
        "",
        f"record {record_name}",
        "",
    ]
    for import_path in DEFAULT_IMPORTS:
        lines.append(f"  import {import_path};")
    lines.append("")
    for alias, import_path in DEFAULT_ALIASES.items():
        lines.append(f"  import {alias} = {import_path};")
    lines.append("")

    for name, modelica_type, fields in parameter_sections(data):
        text = render_parameter(name, modelica_type, fields)
        lines.extend("  " + line if line else line for line in text.splitlines())
        lines.append("")

    lines.append(f"end {record_name};")
    return "\n".join(lines).rstrip() + "\n"


def render_vehicle_sim(*, data: dict[str, Any], record_name: str) -> str:
    sim_package = output_sim_package(data)
    vehicle_model = vehicle_model_name(data, record_name)

    return f"""within {sim_package};

model VehicleSim
  import Modelica.SIunits;
  import Modelica.Constants.pi;
  import Modelica.Math.Vectors.norm;
  import Modelica.Mechanics.MultiBody.Frames;
  import BobLib.Utilities.Math.Vector;

  // Import vehicle records
  import BobLib.Resources.VehicleRecord.Chassis.Suspension.Templates.Tire.Templates.PartialWheelRecord;
  import BobLib.Resources.VehicleDefn.{record_name};

  inner parameter SIunits.Length linkDiameter = 0.020;
  inner parameter SIunits.Length jointDiameter = 0.030;

  parameter {record_name} pVehicle;

  parameter Integer useMode = 0
    "0 - closed-loop lateral acceleration and velocity; 1 - open-loop sinusoidal steer, constant velocity; 2 - custom open-loop steer and drive torque"
    annotation(Evaluate = false);

  // Toggle controllers
  final parameter Boolean closedLoopAy = useMode == 0;
  final parameter Boolean closedLoopVelocity = useMode == 0 or useMode == 1 or useMode == 2;

  parameter Modelica.SIunits.Time steerStart = 1.0
    "Start time"
    annotation(Evaluate = false);

  // Closed-loop maneuver parameters
  parameter SIunits.Length targetRad = 12.5
    "Target maneuver radius"
    annotation(Evaluate = false, Dialog(enable = closedLoopAy));

  parameter SIunits.Velocity targetVel = 15
    "Target maneuver velocity"
    annotation(Evaluate = false, Dialog(enable = closedLoopVelocity));

  parameter SIunits.Velocity initialVel = targetVel
    "Initial velocity"
    annotation(Evaluate = false);

  parameter Real curvatureGain = 3.2
    "Proportional gain of curvature PI controller"
    annotation(Evaluate = false, Dialog(enable = closedLoopAy));

  parameter Real curvatureTi = 0.03
    "Time constant of curvature PI controller"
    annotation(Evaluate = false, Dialog(enable = closedLoopAy));

  parameter Real steerRatioEstimateStart = 17.5
    "Geometry-based bootstrap for handwheel-to-roadwheel ratio"
    annotation(Evaluate = false, Dialog(enable = closedLoopAy));

  parameter Real steerRatioEstimateDecay = 15.5
    "Gain-scheduling strength for the feedforward steer ratio"
    annotation(Evaluate = false, Dialog(enable = closedLoopAy));

  parameter SIunits.Time ayRampDuration = 1.5
    "Lateral acceleration target ramp duration"
    annotation(Evaluate = false, Dialog(enable = closedLoopAy));

  parameter SIunits.Time steadyHoldDuration = 0.5
    "Duration that Ay error must remain below tolerance before termination"
    annotation(Evaluate = false, Dialog(enable = closedLoopAy));

  parameter Real ayErrorTol = 0.01
    "Lateral acceleration error tolerance"
    annotation(Evaluate = false, Dialog(enable = closedLoopAy));

  parameter Real velGain = 200
    "Proportional gain of velocity controller"
    annotation(Evaluate = false, Dialog(enable = closedLoopVelocity));

  parameter Real velTi = 1
    "Time constant of velocity controller"
    annotation(Evaluate = false, Dialog(enable = closedLoopVelocity));

  parameter Real der_yawVelTol = 0.01
    "Yaw-rate derivative tolerance for ramp-steer steady-state detection";

  // Ramp-steer parameters
  parameter SIunits.Angle frRampSteerHeight = 5*pi/180
    "Ramp steer target angle";

  parameter SIunits.Time frRampSteerDuration = 0.001
    "Ramp steer duration";

  // Frequency response parameters
  parameter SIunits.Angle steerAmp = 6*pi/180
    "Amplitude"
    annotation(Evaluate = false);

  parameter SIunits.Frequency steerFreq = 1.0
    "Frequency (Hz)"
    annotation(Evaluate = false);

  // Raw signal parameters
  Real frSteerCmd;
  Real driveTorqueCmd;
  Real bodyVels[3];
  Real bodyAngularVels[3];
  Real bodyAccels[3];
  Real bodyAngles[3];

  Real speed;
  Real curvature;
  Real targetCurvature;
  Real targetAy;
  Real targetAyCmd;
  Real targetCurvatureCmd;
  Real targetRoadwheel;
  Real targetRoadwheelCmd;
  Real steerRatioEstimate;
  Real steerFeedforward;
  Real roadwheelMag;

  Real rampXi;
  Real ayRampFactor;
  Real ayErrorRaw;
  Real ayError;
  Real curvatureErrorRaw;
  Real curvatureError;

  Real radError;
  Real velError;
  Real steerSine;
  Real steerRamp;

  // Standard outputs
  SIunits.Acceleration accX;
  SIunits.Acceleration accY;
  SIunits.Angle handwheelAngle;
  SIunits.Torque handwheelTorque;
  SIunits.Force Fz_FL;
  SIunits.Force Fz_FR;
  SIunits.Force Fz_RL;
  SIunits.Force Fz_RR;
  SIunits.Angle leftSteerAngle;
  SIunits.Angle rightSteerAngle;
  SIunits.Angle roll;
  SIunits.Angle sideslip;
  SIunits.Velocity velX;
  SIunits.Velocity velY;
  SIunits.AngularVelocity yawVel;

  inner Modelica.Mechanics.MultiBody.World world(n = {{0, 0, -1}}) annotation(
    Placement(transformation(origin = {{-130, -110}}, extent = {{{{-10, -10}}, {{10, 10}}}})));

  BobLib.Vehicle.{vehicle_model} vehicle(
    pVehicle = pVehicle,
    pAero = pVehicle.pAero) annotation(
    Placement(transformation(origin = {{0, 20}}, extent = {{{{-45, -50}}, {{45, 50}}}})));

  Modelica.Mechanics.MultiBody.Joints.FreeMotion cgFreeMotion(
    animation = false,
    r_rel_a(start = {{0, 0, 0}}, each fixed = true),
    enforceStates = false,
    v_rel_a(start = {{initialVel, 0, 0}}, each fixed = true)) annotation(
    Placement(transformation(origin = {{100, 90}}, extent = {{{{10, -10}}, {{-10, 10}}}})));

  Modelica.Mechanics.Rotational.Sources.Position frSteerPosition(
    exact = false,
    w(start = 0, fixed = true)) annotation(
    Placement(transformation(origin = {{-30, 110}}, extent = {{{{-10, -10}}, {{10, 10}}}}, rotation = -0)));

  Modelica.Mechanics.MultiBody.Sensors.RelativeAngles sprungAngles annotation(
    Placement(transformation(origin = {{70, -70}}, extent = {{{{-10, -10}}, {{10, 10}}}}, rotation = 90)));

  final parameter Real cpInitFL[3] =
    pVehicle.pFrDW.wheelCenter +
    Frames.resolve1(
      Frames.axesRotations(
        {{1, 2, 3}},
        {{
          pVehicle.pFrPartialWheel.staticGamma*pi/180,
          0,
          pVehicle.pFrPartialWheel.staticAlpha*pi/180
        }},
        {{0, 0, 0}}),
      {{0, 0, -pVehicle.pFrPartialWheel.R0}});

  final parameter Real cpInitFR[3] = Vector.mirrorXZ(cpInitFL);

  final parameter Real cpInitRL[3] =
    pVehicle.pRrDW.wheelCenter +
    Frames.resolve1(
      Frames.axesRotations(
        {{1, 2, 3}},
        {{
          pVehicle.pRrPartialWheel.staticGamma*pi/180,
          0,
          pVehicle.pRrPartialWheel.staticAlpha*pi/180
        }},
        {{0, 0, 0}}),
      {{0, 0, -pVehicle.pRrPartialWheel.R0}});

  final parameter Real cpInitRR[3] = Vector.mirrorXZ(cpInitRL);

  final parameter SIunits.Length wheelbase = abs(
    pVehicle.pFrDW.wheelCenter[1] - pVehicle.pRrDW.wheelCenter[1]);

protected
  discrete Real t_ay_hit(start = -1);
  discrete Real t_yawVel_hit(start = -1);

  Real leftWheelVector[3];
  Real rightWheelVector[3];

  Modelica.Mechanics.MultiBody.Parts.Fixed fixedFL(
    r = cpInitFL,
    animation = false) annotation(
    Placement(transformation(origin = {{-130, 10}}, extent = {{{{-10, -10}}, {{10, 10}}}})));

  Modelica.Mechanics.MultiBody.Parts.Fixed fixedFR(
    r = cpInitFR,
    animation = false) annotation(
    Placement(transformation(origin = {{130, 10}}, extent = {{{{10, -10}}, {{-10, 10}}}})));

  Modelica.Mechanics.MultiBody.Parts.Fixed fixedRL(
    r = cpInitRL,
    animation = false) annotation(
    Placement(transformation(origin = {{-130, -50}}, extent = {{{{-10, -10}}, {{10, 10}}}})));

  Modelica.Mechanics.MultiBody.Parts.Fixed fixedRR(
    r = cpInitRR,
    animation = false) annotation(
    Placement(transformation(origin = {{130, -50}}, extent = {{{{10, -10}}, {{10, 10}}}})));

  Modelica.Mechanics.MultiBody.Parts.Fixed cgFixed(
    r = pVehicle.pSprungMass.rCM,
    animation = false) annotation(
    Placement(transformation(origin = {{130, 90}}, extent = {{{{10, -10}}, {{-10, 10}}}})));

  BobLib.Utilities.Mechanics.Multibody.GroundPhysics groundFL annotation(
    Placement(transformation(origin = {{-100, 10}}, extent = {{{{-10, -10}}, {{10, 10}}}})));

  BobLib.Utilities.Mechanics.Multibody.GroundPhysics groundFR annotation(
    Placement(transformation(origin = {{100, 10}}, extent = {{{{10, -10}}, {{10, 10}}}})));

  BobLib.Utilities.Mechanics.Multibody.GroundPhysics groundRL annotation(
    Placement(transformation(origin = {{-100, -50}}, extent = {{{{-10, -10}}, {{10, 10}}}})));

  BobLib.Utilities.Mechanics.Multibody.GroundPhysics groundRR annotation(
    Placement(transformation(origin = {{100, -50}}, extent = {{{{10, -10}}, {{10, 10}}}})));

  Modelica.Blocks.Sources.RealExpression curvErrorExpression(
    y = curvatureError) annotation(
    Placement(transformation(origin = {{-110, 130}}, extent = {{{{-10, -10}}, {{10, 10}}}})));

  Modelica.Blocks.Continuous.PI curvPI(
    k = curvatureGain,
    T = curvatureTi,
    initType = Modelica.Blocks.Types.Init.InitialOutput) annotation(
    Placement(transformation(origin = {{-70, 110}}, extent = {{{{-10, -10}}, {{10, 10}}}})));

  Modelica.Blocks.Sources.RealExpression velSetpointExpression(
    y = targetVel) annotation(
    Placement(transformation(origin = {{-70, -30}}, extent = {{{{-10, -10}}, {{10, 10}}}})));

  Modelica.Blocks.Sources.RealExpression velMeasurementExpression(
    y = speed) annotation(
    Placement(transformation(origin = {{-70, -10}}, extent = {{{{-10, -10}}, {{10, 10}}}})));

  Modelica.Blocks.Continuous.LimPID speedPI(
    controllerType = Modelica.Blocks.Types.SimpleController.PI,
    k = velGain,
    Ti = velTi,
    yMax = 5000,
    yMin = -5000,
    Ni = 0.9,
    initType = Modelica.Blocks.Types.InitPID.InitialOutput,
    y_start = 0) annotation(
    Placement(transformation(origin = {{-30, -50}}, extent = {{{{-10, -10}}, {{10, 10}}}})));

initial equation
  vehicle.chassis.frAxleDW.leftTire.wheelModel.hubAxis.w =
    initialVel / pVehicle.pFrPartialWheel.R0;

  vehicle.chassis.frAxleDW.rightTire.wheelModel.hubAxis.w =
    initialVel / pVehicle.pFrPartialWheel.R0;

  vehicle.chassis.rrAxleDW.leftTire.wheelModel.hubAxis.w =
    initialVel / pVehicle.pRrPartialWheel.R0;

  vehicle.chassis.rrAxleDW.rightTire.wheelModel.hubAxis.w =
    initialVel / pVehicle.pRrPartialWheel.R0;

equation
  targetCurvature = noEvent(1 / targetRad);
  targetAy = noEvent(targetVel * targetVel / targetRad);
  targetRoadwheel = noEvent(atan(wheelbase * targetCurvature));

  curvature =
    bodyAngularVels[3] / max(speed, 0.1);

  radError =
    abs(curvature - targetCurvature) /
    max(abs(targetCurvature), 1e-6) *
    abs(targetRad);

  // Fifth-order smootherstep ramp for target Ay.
  // With steerStart = 1.0 and ayRampDuration = 1.5,
  // the target finishes ramping at t = 2.5 s.
  rampXi =
    if useMode == 0 then
      noEvent(
        if time <= steerStart then
          0
        elseif time >= steerStart + ayRampDuration then
          1
        else
          (time - steerStart) / ayRampDuration
      )
    else
      0;

  ayRampFactor =
    if useMode == 0 then
      noEvent(10*rampXi^3 - 15*rampXi^4 + 6*rampXi^5)
    else
      0;

  targetAyCmd =
    if useMode == 0 and noEvent(time >= steerStart) then
      ayRampFactor * targetAy
    else
      0;

  targetCurvatureCmd =
    if useMode == 0 and noEvent(time >= steerStart) then
      ayRampFactor * targetCurvature
    else
      0;

  targetRoadwheelCmd =
    if useMode == 0 and noEvent(time >= steerStart) then
      ayRampFactor * targetRoadwheel
    else
      0;

  ayErrorRaw =
    if useMode == 0 and noEvent(time >= steerStart) then
      targetAy - accY
    else
      0;

  ayError =
    if useMode == 0 and noEvent(time >= steerStart) then
      targetAyCmd - accY
    else
      0;

  curvatureErrorRaw =
    if useMode == 0 and noEvent(time >= steerStart) then
      targetCurvature - curvature
    else
      0;

  curvatureError =
    if useMode == 0 and noEvent(time >= steerStart) then
      ayRampFactor * (targetCurvature - curvature)
    else
      0;

  roadwheelMag =
    if useMode == 0 and noEvent(time >= steerStart) then
      sqrt(targetRoadwheelCmd*targetRoadwheelCmd + 1e-6)
    else
      0;

  steerRatioEstimate =
    if useMode == 0 and noEvent(time >= steerStart) then
      steerRatioEstimateStart /
      (1 + steerRatioEstimateDecay*roadwheelMag)
    else
      steerRatioEstimateStart;

  steerFeedforward =
    if useMode == 0 and noEvent(time >= steerStart) then
      steerRatioEstimate * targetRoadwheelCmd
    else
      0;

  // Strict Ay hold-window detection:
  // timer starts only when final Ay error enters tolerance
  // timer resets immediately if final Ay error leaves tolerance.
  when useMode == 0
     and time > steerStart + ayRampDuration
     and abs(ayErrorRaw) < ayErrorTol
     and pre(t_ay_hit) < 0 then
    t_ay_hit = time;

  elsewhen useMode == 0
     and time > steerStart + ayRampDuration
     and abs(ayErrorRaw) >= ayErrorTol then
    t_ay_hit = -1;
  end when;

  when useMode == 0
     and t_ay_hit > 0
     and time > t_ay_hit + steadyHoldDuration then
    terminate("Reached lateral acceleration target and held error below tolerance");
  end when;

  when useMode == 2
     and time > steerStart + frRampSteerDuration
     and abs(der(yawVel)) < der_yawVelTol
     and pre(t_yawVel_hit) < 0 then
    t_yawVel_hit = time;

  elsewhen useMode == 2
     and abs(der(yawVel)) >= der_yawVelTol then
    t_yawVel_hit = -1;
  end when;

  when useMode == 2
     and t_yawVel_hit > 0
     and time > t_yawVel_hit + 0.1 then
    terminate("Reached ramp-steer steady-state: der(yawVel) below tolerance (held 0.1s)");
  end when;

  steerSine =
    if noEvent(useMode == 1 and time > steerStart) then
      steerAmp*sin(2*pi*steerFreq*(time - steerStart))
    else
      0;

  steerRamp =
    frRampSteerHeight *
    noEvent(min(1, max(0, (time - steerStart) / frRampSteerDuration)));

  // Curvature error PI provides the nominal handwheel command.
  frSteerCmd =
    if useMode == 0 and noEvent(time >= steerStart) then
      steerFeedforward + curvPI.y
    elseif useMode == 1 then
      steerSine
    elseif useMode == 2 then
      steerRamp
    else
      0;

  driveTorqueCmd =
    if useMode == 0 or useMode == 1 or useMode == 2 then
      speedPI.y
    else
      0;

  frSteerPosition.phi_ref = frSteerCmd;
  vehicle.uPTNTorque = driveTorqueCmd;

  bodyVels =
    Frames.resolve2(
      vehicle.chassis.spaceFrame.sprungBody.frame_a.R,
      vehicle.chassis.spaceFrame.sprungBody.v_0);

  bodyAngularVels =
    Frames.resolve2(
      vehicle.chassis.spaceFrame.sprungBody.frame_a.R,
      vehicle.chassis.spaceFrame.sprungBody.w_a);

  bodyAccels =
    Frames.resolve2(
      vehicle.chassis.spaceFrame.sprungBody.frame_a.R,
      vehicle.chassis.spaceFrame.sprungBody.a_0);

  bodyAngles =
    Frames.resolve2(
      vehicle.chassis.spaceFrame.sprungBody.frame_a.R,
      sprungAngles.angles);

  leftWheelVector =
    Frames.resolve1(
      vehicle.chassis.frAxleFrame.R,
      Frames.resolve2(vehicle.frameFL.R, {{1, 0, 0}}));

  rightWheelVector =
    Frames.resolve1(
      vehicle.chassis.frAxleFrame.R,
      Frames.resolve2(vehicle.frameFR.R, {{1, 0, 0}}));

  leftSteerAngle = -1*atan(leftWheelVector[2] / leftWheelVector[1]);
  rightSteerAngle = -1*atan(rightWheelVector[2] / rightWheelVector[1]);

  handwheelAngle = vehicle.steerFlange.phi;

  speed = norm(bodyVels);
  velError = targetVel - speed;

  velX = bodyVels[1];
  velY = bodyVels[2];
  yawVel = bodyAngularVels[3];
  sideslip = atan(velY / velX);

  accX = bodyAccels[1];
  accY = bodyAccels[2];

  Fz_FL = vehicle.chassis.frAxleDW.leftTire.Fz;
  Fz_FR = vehicle.chassis.frAxleDW.rightTire.Fz;
  Fz_RL = vehicle.chassis.rrAxleDW.leftTire.Fz;
  Fz_RR = vehicle.chassis.rrAxleDW.rightTire.Fz;

  roll = bodyAngles[1];

  // Note that .tau is the reaction by Newton's 3rd law. Negate for applied torque.
  handwheelTorque = -1*vehicle.steerFlange.tau;

  connect(cgFixed.frame_b, cgFreeMotion.frame_a) annotation(
    Line(points = {{{{120, 90}}, {{110, 90}}}}, color = {{95, 95, 95}}));

  connect(fixedFL.frame_b, groundFL.frame_a) annotation(
    Line(points = {{{{-120, 10}}, {{-110, 10}}}}, color = {{95, 95, 95}}));

  connect(fixedFR.frame_b, groundFR.frame_a) annotation(
    Line(points = {{{{120, 10}}, {{110, 10}}}}, color = {{95, 95, 95}}));

  connect(fixedRL.frame_b, groundRL.frame_a) annotation(
    Line(points = {{{{-120, -50}}, {{-110, -50}}}}, color = {{95, 95, 95}}));

  connect(fixedRR.frame_b, groundRR.frame_a) annotation(
    Line(points = {{{{120, -50}}, {{110, -50}}}}, color = {{95, 95, 95}}));

  connect(curvErrorExpression.y, curvPI.u) annotation(
    Line(points = {{{{-99, 130}}, {{-82, 130}}}}, color = {{0, 0, 127}}));

  connect(velSetpointExpression.y, speedPI.u_s) annotation(
    Line(points = {{{{-59, -30}}, {{-42, -30}}}}, color = {{0, 0, 127}}));

  connect(velMeasurementExpression.y, speedPI.u_m) annotation(
    Line(points = {{{{-59, -10}}, {{-42, -10}}}}, color = {{0, 0, 127}}));

  connect(vehicle.frameRL, groundRL.frame_b) annotation(
    Line(points = {{{{-44, -22}}, {{-100, -22}}, {{-100, -40}}}}, color = {{95, 95, 95}}));

  connect(groundRR.frame_b, vehicle.frameRR) annotation(
    Line(points = {{{{100, -40}}, {{100, -22}}, {{46, -22}}}}, color = {{95, 95, 95}}));

  connect(vehicle.frameFL, groundFL.frame_b) annotation(
    Line(points = {{{{-44, 38}}, {{-100, 38}}, {{-100, 20}}}}, color = {{95, 95, 95}}));

  connect(vehicle.frameFR, groundFR.frame_b) annotation(
    Line(points = {{{{46, 38}}, {{100, 38}}, {{100, 20}}}}, color = {{95, 95, 95}}));

  connect(frSteerPosition.flange, vehicle.steerFlange) annotation(
    Line(points = {{{{-20, 110}}, {{0, 110}}, {{0, 62}}, {{0, 62}}}}));

  connect(cgFreeMotion.frame_b, vehicle.cgFrame) annotation(
    Line(points = {{{{90, 90}}, {{70, 90}}, {{70, 20}}, {{46, 20}}}}, color = {{95, 95, 95}}));

  connect(world.frame_b, sprungAngles.frame_a) annotation(
    Line(points = {{{{-120, -110}}, {{70, -110}}, {{70, -80}}}}, color = {{95, 95, 95}}));

  connect(vehicle.cgFrame, sprungAngles.frame_b) annotation(
    Line(points = {{{{46, 20}}, {{70, 20}}, {{70, -60}}}}, color = {{95, 95, 95}}));

  annotation(
    Diagram(coordinateSystem(extent = {{{{-140, -120}}, {{140, 120}}}})),
    Icon(coordinateSystem(extent = {{{{-140, -120}}, {{140, 120}}}})),
    experiment(StartTime = 0.5, StopTime = 10, Tolerance = 1e-06, Interval = 0.002),
    __OpenModelica_commandLineOptions = "--matchingAlgorithm=PFPlusExt --indexReductionMethod=dynamicStateSelection -d=initialization,NLSanalyticJacobian --maxSizeLinearTearing=5000",
    __OpenModelica_simulationFlags(
      lv = "LOG_STDOUT,LOG_ASSERT,LOG_STATS",
      noEventEmit = "()",
      s = "dassl",
      variableFilter = ".*"));

end VehicleSim;
"""


def build_vehicle(*, source_yaml: Path | None = None, overwrite: bool = True) -> BuildOutput:
    source_yaml = source_yaml or vehicle_yaml_path()
    data = load_yaml(source_yaml)
    record_name = record_name_from_yaml(data, source_yaml)
    variant = record_to_variant(record_name)
    model_name = vehicle_model_name(data, record_name)

    record_path = boblib_vehicledefn_dir(data) / f"{record_name}.mo"
    vehicle_sim_path = boblib_vehiclesim_path(data)

    record_path.parent.mkdir(parents=True, exist_ok=True)
    vehicle_sim_path.parent.mkdir(parents=True, exist_ok=True)

    outputs = {
        record_path: render_record(data, source_yaml),
        vehicle_sim_path: render_vehicle_sim(data=data, record_name=record_name),
    }
    for path, text in outputs.items():
        if path.exists() and not overwrite:
            raise FileExistsError(f"{path} already exists. Set overwrite=True to replace it.")
        path.write_text(text, encoding="utf-8")

    return BuildOutput(
        record_name=record_name,
        variant_name=variant,
        vehicle_model_name=model_name,
        source_yaml=source_yaml,
        record_path=record_path,
        vehicle_sim_path=vehicle_sim_path,
    )


def main() -> None:
    output = build_vehicle(overwrite=True)
    print("Generated BobLib vehicle files from vehicle.yml")
    print(f"  Variant: {output.variant_name}")
    print(f"  Record:  {output.record_name}")
    print(f"  Vehicle: BobLib.Vehicle.{output.vehicle_model_name}")
    print("")
    print("Wrote directly into BobLib:")
    print(f"  {output.record_path}")
    print(f"  {output.vehicle_sim_path}")


if __name__ == "__main__":
    main()
