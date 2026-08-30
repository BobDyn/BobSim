"""Generate BobLib Modelica records and standard simulation wrappers from vehicle YAML."""

from __future__ import annotations

from collections.abc import Iterable, Mapping, Sequence
from dataclasses import dataclass
from pathlib import Path
from typing import Any
import hashlib
import math
import re

import numpy as np

from _0_Utils.vehicle_io import load_yaml, parse_tir, tire_template_name


@dataclass(frozen=True)
class ArchitectureSpec:
    token: str
    record_type: str
    front_model: str
    rear_model: str
    description: str
    has_bellcrank: bool = False
    has_stabar: bool = False


@dataclass(frozen=True)
class GeneratedModelicaFile:
    kind: str
    path: Path
    class_name: str
    package: str


@dataclass(frozen=True)
class ModelicaGenerationResult:
    vehicle_name: str
    record_name: str
    vehicle_template_name: str
    four_post_template_name: str
    files: tuple[GeneratedModelicaFile, ...]
    package_orders: tuple[Path, ...]


@dataclass(frozen=True)
class ModelicaStackPlan:
    result: ModelicaGenerationResult
    contents: tuple[tuple[Path, str], ...]


@dataclass(frozen=True)
class ModelicaExpression:
    text: str


@dataclass(frozen=True)
class ModelicaCall:
    type_name: str
    assignments: tuple[tuple[str, Any], ...] = ()


@dataclass(frozen=True)
class SemicolonMatrix:
    rows: Sequence[Sequence[Any]]


ARCHITECTURES: dict[str, ArchitectureSpec] = {
    "direct": ArchitectureSpec(
        token="DWDirect",
        record_type="Axle.AxleDW_DirectRecord",
        front_model="BobLib.Chassis.Suspension.FrAxleDW_Direct",
        rear_model="BobLib.Chassis.Suspension.RrAxleDW_Direct",
        description="direct-acting double wishbone suspension",
    ),
    "bellcrank": ArchitectureSpec(
        token="DWBC",
        record_type="Axle.AxleDW_BCRecord",
        front_model="BobLib.Chassis.Suspension.FrAxleDW_BC",
        rear_model="BobLib.Chassis.Suspension.RrAxleDW_BC",
        description="bellcrank-actuated double wishbone suspension",
        has_bellcrank=True,
    ),
    "bellcrank_stabar": ArchitectureSpec(
        token="DWBCStabar",
        record_type="Axle.AxleDW_BC_StabarRecord",
        front_model="BobLib.Chassis.Suspension.FrAxleDW_BC_Stabar",
        rear_model="BobLib.Chassis.Suspension.RrAxleDW_BC_Stabar",
        description="bellcrank-actuated double wishbone suspension with a stabilizer bar",
        has_bellcrank=True,
        has_stabar=True,
    ),
}

TIRE_RECORDS: tuple[tuple[str, str, tuple[str, ...]], ...] = (
    (
        "fxCombined",
        "TireModel.CombinedSlip.FxCombinedRecord",
        ("RBX1", "RBX2", "RCX1", "REX1", "REX2", "RHX1"),
    ),
    (
        "fxPure",
        "TireModel.PureSlip.FxPureRecord",
        (
            "LFZO",
            "LGAX",
            "PCX1",
            "PDX1",
            "PDX2",
            "PDX3",
            "PKX1",
            "PKX2",
            "PKX3",
            "PHX1",
            "PHX2",
            "PVX1",
            "PVX2",
            "PEX1",
            "PEX2",
            "PEX3",
            "PEX4",
            "LCX",
            "LMUX",
            "LKX",
            "LHX",
            "LVX",
            "LEX",
            "LXAL",
        ),
    ),
    (
        "fyCombined",
        "TireModel.CombinedSlip.FyCombinedRecord",
        (
            "RBY1",
            "RBY2",
            "RBY3",
            "RCY1",
            "REY1",
            "REY2",
            "RHY1",
            "RHY2",
            "RVY1",
            "RVY2",
            "RVY3",
            "RVY4",
            "RVY5",
            "RVY6",
        ),
    ),
    (
        "fyPure",
        "TireModel.PureSlip.FyPureRecord",
        (
            "LFZO",
            "LGAY",
            "PCY1",
            "PDY1",
            "PDY2",
            "PDY3",
            "PKY1",
            "PKY2",
            "PKY3",
            "PHY1",
            "PHY2",
            "PHY3",
            "PVY1",
            "PVY2",
            "PVY3",
            "PVY4",
            "PEY1",
            "PEY2",
            "PEY3",
            "PEY4",
            "LCY",
            "LMUY",
            "LEY",
            "LKY",
            "LHY",
            "LVY",
            "LYKA",
            "LVYKA",
        ),
    ),
    ("mxCombined", "TireModel.CombinedSlip.MxCombinedRecord", ()),
    ("mxPure", "TireModel.PureSlip.MxPureRecord", ("QSX1", "QSX2", "QSX3", "LMX", "LVMX")),
    ("myCombined", "TireModel.CombinedSlip.MyCombinedRecord", ()),
    ("myPure", "TireModel.PureSlip.MyPureRecord", ("QSY1", "QSY2", "QSY3", "QSY4", "Vref", "LMY")),
    (
        "mzCombined",
        "TireModel.CombinedSlip.MzCombinedRecord",
        ("SSZ1", "SSZ2", "SSZ3", "SSZ4", "RVY1", "RVY2", "RVY3", "RVY4", "RVY5", "RVY6", "LS", "LVYKA"),
    ),
    (
        "mzPure",
        "TireModel.PureSlip.MzPureRecord",
        (
            "QBZ1",
            "QBZ2",
            "QBZ3",
            "QBZ4",
            "QBZ5",
            "QCZ1",
            "QDZ1",
            "QDZ2",
            "QDZ3",
            "QDZ4",
            "QEZ1",
            "QEZ2",
            "QEZ3",
            "QEZ4",
            "QEZ5",
            "QHZ1",
            "QHZ2",
            "QHZ3",
            "QHZ4",
            "QBZ9",
            "QBZ10",
            "QDZ6",
            "QDZ7",
            "QDZ8",
            "QDZ9",
            "LTR",
            "LRES",
            "LKY",
            "LMUY",
            "LGAZ",
        ),
    ),
    (
        "relaxation",
        "TireModel.RelaxationRecord",
        ("FNOMIN", "UNLOADED_RADIUS", "LFZO", "PTX1", "PTX2", "PTX3", "PTY1", "PTY2", "PKY3", "LSGKP", "LSGAL"),
    ),
    ("setup", "TireModel.SetupRecord", ("FNOMIN", "FZMIN", "FZMAX", "UNLOADED_RADIUS")),
)

TIR_KEY_ALIASES = {
    "Vref": "LONGVL",
}

POWERTRAIN_RECORDS: tuple[tuple[str, str], ...] = (
    ("pBattery", "EnergyStorage.BatteryPackRecord"),
    ("pVCU", "Controllers.VCURecord"),
    ("pInverter", "PowerElectronics.InverterDCRecord"),
    ("pMotor", "ElectricDrives.MotorRecord"),
    ("pDriveline", "Drivelines.RearFinalDriveDifferentialRecord"),
)

VEHICLE_OMC_OPTIONS = (
    "--matchingAlgorithm=PFPlusExt --indexReductionMethod=dynamicStateSelection "
    "-d=initialization,NLSanalyticJacobian,disableStartCalc "
    "--maxSizeLinearTearing=5000 --generateDynamicJacobian=none"
)

FOUR_POST_OMC_OPTIONS = (
    "--matchingAlgorithm=PFPlusExt --indexReductionMethod=dynamicStateSelection "
    "-d=initialization,NLSanalyticJacobian --maxSizeLinearTearing=5000 --generateDynamicJacobian=none"
)

VEHICLE_VARIABLE_FILTER = (
    "time|frSteerCmd|accX|accY|handwheelAngle|steerExcess|handwheelTorque|Fz_.*|leftSteerAngle|"
    "rightSteerAngle|roll|sideslip|velX|velY|yawVel|steadyState.*|linearity.*|minTireNormalLoad"
)

TARGET_SIGNATURE_KINDS: dict[str, tuple[str, ...]] = {
    "vehicle": ("vehicle_record", "vehicle_template", "vehicle_entrypoint"),
    "four_post": ("vehicle_record", "four_post_template", "four_post_entrypoint"),
}


def generate_modelica_stack(vehicle_path: str | Path, *, root: str | Path | None = None) -> ModelicaGenerationResult:
    plan = plan_modelica_stack(vehicle_path, root=root)
    for path, text in plan.contents:
        _write_text(path, text)
    for path, entry in (
        (plan.result.package_orders[0], plan.result.record_name),
        (plan.result.package_orders[1], plan.result.vehicle_template_name),
        (plan.result.package_orders[2], plan.result.four_post_template_name),
    ):
        _ensure_package_order_entry(path, entry)
    return plan.result


def plan_modelica_stack(vehicle_path: str | Path, *, root: str | Path | None = None) -> ModelicaStackPlan:
    repo_root = Path(root).resolve() if root is not None else Path(vehicle_path).resolve().parent
    source_path = Path(vehicle_path)
    if not source_path.is_absolute():
        source_path = repo_root / source_path
    source_path = source_path.resolve()
    data = load_yaml(source_path)

    vehicle = _mapping(data.get("vehicle"), "vehicle")
    vehicle_name = _modelica_identifier(str(vehicle.get("name") or source_path.stem))
    record_name = f"{vehicle_name}Record"
    vehicle_template_name = f"VehicleSim_{vehicle_name}"
    four_post_template_name = f"FourPostSim_{vehicle_name}"

    architecture = _mapping(data.get("architecture"), "architecture")
    front_arch = _architecture(str(architecture.get("front", "direct")), "architecture.front")
    rear_arch = _architecture(str(architecture.get("rear", "direct")), "architecture.rear")
    boblib_root = _boblib_root(data, repo_root)
    tire_root = _tire_root(data, repo_root)

    record_path = boblib_root / "Records/VehicleDefn" / f"{record_name}.mo"
    vehicle_template_path = (
        boblib_root / "Experiments/Standards/Templates/Vehicle" / f"{vehicle_template_name}.mo"
    )
    four_post_template_path = (
        boblib_root / "Experiments/Standards/Templates/FourPost" / f"{four_post_template_name}.mo"
    )
    vehicle_entry_path = boblib_root / "Experiments/Standards/VehicleSim.mo"
    four_post_entry_path = boblib_root / "Experiments/Standards/FourPostSim.mo"

    record_order = boblib_root / "Records/VehicleDefn/package.order"
    vehicle_template_order = boblib_root / "Experiments/Standards/Templates/Vehicle/package.order"
    four_post_template_order = boblib_root / "Experiments/Standards/Templates/FourPost/package.order"

    files = (
        GeneratedModelicaFile(
            kind="vehicle_record",
            path=record_path,
            class_name=record_name,
            package="BobLib.Records.VehicleDefn",
        ),
        GeneratedModelicaFile(
            kind="vehicle_template",
            path=vehicle_template_path,
            class_name=vehicle_template_name,
            package="BobLib.Experiments.Standards.Templates.Vehicle",
        ),
        GeneratedModelicaFile(
            kind="four_post_template",
            path=four_post_template_path,
            class_name=four_post_template_name,
            package="BobLib.Experiments.Standards.Templates.FourPost",
        ),
        GeneratedModelicaFile(
            kind="vehicle_entrypoint",
            path=vehicle_entry_path,
            class_name="VehicleSim",
            package="BobLib.Experiments.Standards",
        ),
        GeneratedModelicaFile(
            kind="four_post_entrypoint",
            path=four_post_entry_path,
            class_name="FourPostSim",
            package="BobLib.Experiments.Standards",
        ),
    )
    result = ModelicaGenerationResult(
        vehicle_name=vehicle_name,
        record_name=record_name,
        vehicle_template_name=vehicle_template_name,
        four_post_template_name=four_post_template_name,
        files=files,
        package_orders=(record_order, vehicle_template_order, four_post_template_order),
    )
    contents = (
        (record_path, _vehicle_record_text(data, tire_root, vehicle_name, record_name, front_arch, rear_arch)),
        (vehicle_template_path, _vehicle_template_text(vehicle_template_name, record_name, front_arch, rear_arch)),
        (
            four_post_template_path,
            _four_post_template_text(four_post_template_name, record_name, front_arch, rear_arch),
        ),
        (vehicle_entry_path, _vehicle_entry_text(vehicle_template_name)),
        (four_post_entry_path, _four_post_entry_text(four_post_template_name)),
    )
    return ModelicaStackPlan(result=result, contents=contents)


def modelica_generation_payload(result: ModelicaGenerationResult, repo_root: str | Path) -> dict[str, Any]:
    root = Path(repo_root).resolve()
    return {
        "vehicle_name": result.vehicle_name,
        "record": {
            "name": result.record_name,
            "path": _display_path(result.files[0].path, root),
        },
        "vehicle_template": result.vehicle_template_name,
        "four_post_template": result.four_post_template_name,
        "files": [
            {
                "kind": item.kind,
                "name": item.class_name,
                "package": item.package,
                "path": _display_path(item.path, root),
            }
            for item in result.files
        ],
        "package_orders": [_display_path(path, root) for path in result.package_orders],
    }


def modelica_stack_status_payload(vehicle_path: str | Path, repo_root: str | Path) -> dict[str, Any]:
    root = Path(repo_root).resolve()
    plan = plan_modelica_stack(vehicle_path, root=root)
    expected_contents = dict(plan.contents)
    files = [_file_status_payload(item, expected_contents.get(item.path), root) for item in plan.result.files]
    package_orders = (
        _package_order_status_payload(plan.result.package_orders[0], plan.result.record_name, root),
        _package_order_status_payload(plan.result.package_orders[1], plan.result.vehicle_template_name, root),
        _package_order_status_payload(plan.result.package_orders[2], plan.result.four_post_template_name, root),
    )
    files_current = all(item["current"] for item in files)
    orders_current = all(item["contains_entry"] for item in package_orders)
    written = files_current and orders_current
    any_written = any(item["exists"] for item in files)
    state = "written" if written else "stale" if any_written else "missing"
    latest_modified = max((float(item["modified"] or 0.0) for item in files), default=0.0)
    return {
        "state": state,
        "written_to_boblib": written,
        "vehicle_name": plan.result.vehicle_name,
        "record": plan.result.record_name,
        "vehicle_template": plan.result.vehicle_template_name,
        "four_post_template": plan.result.four_post_template_name,
        "latest_modified": latest_modified or None,
        "signatures": _modelica_stack_signatures(plan),
        "files": files,
        "package_orders": list(package_orders),
    }


def _modelica_stack_signatures(plan: ModelicaStackPlan) -> dict[str, dict[str, Any]]:
    contents_by_path = dict(plan.contents)
    signatures: dict[str, dict[str, Any]] = {}
    for target, kinds in TARGET_SIGNATURE_KINDS.items():
        digest = hashlib.sha256()
        digest.update(b"bobsim-modelica-stack-signature-v1\n")
        digest.update(f"target:{target}\n".encode("utf-8"))
        included: list[dict[str, str]] = []
        for item in plan.result.files:
            if item.kind not in kinds:
                continue
            text = contents_by_path.get(item.path, "")
            rel_path = item.path.as_posix()
            digest.update(f"kind:{item.kind}\n".encode("utf-8"))
            digest.update(f"package:{item.package}\n".encode("utf-8"))
            digest.update(f"class:{item.class_name}\n".encode("utf-8"))
            digest.update(f"path:{rel_path}\n".encode("utf-8"))
            digest.update(text.encode("utf-8"))
            digest.update(b"\n")
            included.append(
                {
                    "kind": item.kind,
                    "name": item.class_name,
                    "package": item.package,
                }
            )
        signatures[target] = {
            "generated": digest.hexdigest(),
            "kinds": list(kinds),
            "files": included,
        }
    return signatures


def _file_status_payload(item: GeneratedModelicaFile, expected: str | None, repo_root: Path) -> dict[str, Any]:
    exists = item.path.is_file()
    current = False
    modified: float | None = None
    size: int | None = None
    if exists:
        stat = item.path.stat()
        modified = stat.st_mtime
        size = stat.st_size
        current = expected is None or item.path.read_text(encoding="utf-8", errors="replace") == expected
    return {
        "kind": item.kind,
        "name": item.class_name,
        "package": item.package,
        "path": _display_path(item.path, repo_root),
        "exists": exists,
        "current": current,
        "modified": modified,
        "size": size,
    }


def _package_order_status_payload(path: Path, entry: str, repo_root: Path) -> dict[str, Any]:
    exists = path.is_file()
    lines = path.read_text(encoding="utf-8").splitlines() if exists else []
    return {
        "path": _display_path(path, repo_root),
        "entry": entry,
        "exists": exists,
        "contains_entry": entry in lines,
    }


def _vehicle_record_text(
    data: Mapping[str, Any],
    tire_root: Path,
    vehicle_name: str,
    record_name: str,
    front_arch: ArchitectureSpec,
    rear_arch: ArchitectureSpec,
) -> str:
    sections: list[str] = [
        "within BobLib.Records.VehicleDefn;",
        "",
        f"record {record_name}",
        "",
        "  import BobLib.Records.VehicleRecord.Chassis.Suspension.Templates.MassRecord;",
        "",
        "  import Aero = BobLib.Records.VehicleRecord.Aero;",
        "  import EnergyStorage = BobLib.Records.VehicleRecord.EnergyStorage;",
        "  import Controllers = BobLib.Records.VehicleRecord.Controllers;",
        "  import PowerElectronics = BobLib.Records.VehicleRecord.PowerElectronics;",
        "  import ElectricDrives = BobLib.Records.VehicleRecord.ElectricDrives;",
        "  import Drivelines = BobLib.Records.VehicleRecord.Drivelines;",
        "  import TireModel = BobLib.Records.VehicleRecord.Chassis.Suspension.Templates.Tire.MF52;",
        "  import Wheel = BobLib.Records.VehicleRecord.Chassis.Suspension.Templates.Tire;",
        "  import Rack = BobLib.Records.VehicleRecord.Chassis.Suspension.Templates.SteeringRack;",
        "  import Stabar = BobLib.Records.VehicleRecord.Chassis.Suspension.Templates.Stabar;",
        "  import DW = BobLib.Records.VehicleRecord.Chassis.Suspension.Templates.DoubleWishbone;",
        "  import Axle = BobLib.Records.VehicleRecord.Chassis.Suspension;",
        "",
    ]

    for side_name, prefix, arch in (("front", "Fr", front_arch), ("rear", "Rr", rear_arch)):
        side = _mapping(data.get(side_name), side_name)
        sections.extend(_axle_sections(data, tire_root, side_name, prefix, side, arch))

    sections.extend(_powertrain_sections(data))
    sections.extend(_vehicle_mass_sections(data))
    sections.append(_aero_section(data))
    sections.extend(
        (
            "",
            "  annotation(",
            '    Documentation(info = "<html>',
            "<p>",
            f"Record <code>{record_name}</code> is generated from <code>vehicle.yml</code> "
            f"for <code>{vehicle_name}</code>.",
            "</p>",
            "<p>",
            "It binds axle geometry, wheel and tire records, mass properties, aero maps, "
            "and BobLib powertrain subsystem records.",
            "</p>",
            '</html>"));',
            f"end {record_name};",
            "",
        )
    )
    return "\n".join(sections)


def _axle_sections(
    vehicle_data: Mapping[str, Any],
    tire_root: Path,
    side_name: str,
    prefix: str,
    side: Mapping[str, Any],
    arch: ArchitectureSpec,
) -> list[str]:
    tire_path = tire_root / f"{tire_template_name(vehicle_data, side)}.tir"
    if not tire_path.is_file():
        raise FileNotFoundError(f"Missing tire template for {side_name}: {tire_path}")
    tire_values = parse_tir(tire_path)
    axle_prefix = f"p{prefix}"
    sections = [
        _format_parameter(arch.record_type, f"{axle_prefix}AxleDW", _axle_assignments(side_name, side, arch)),
        "",
    ]
    if arch.has_stabar:
        sections.extend(
            (
                _format_parameter(
                    "Stabar.StabarRecord",
                    f"{axle_prefix}Stabar",
                    _stabar_assignments(side_name, side),
                ),
                "",
            )
        )
    sections.extend(
        (
            _format_parameter(
                "Wheel.Templates.PartialWheelRecord",
                f"{axle_prefix}PartialWheel",
                _wheel_assignments(side_name, side),
            ),
            "",
            _format_parameter("Rack.RackAndPinionRecord", f"{axle_prefix}Rack", _rack_assignments(side_name, side)),
            "",
            _format_parameter(
                "DW.WishboneUprightLoopRecord",
                f"{axle_prefix}DW",
                _wishbone_assignments(side_name, side),
            ),
            "",
            _format_parameter(
                "Axle.Templates.AxleMassRecord",
                f"{axle_prefix}AxleMass",
                _axle_mass_assignments(side_name, side),
            ),
            "",
            _format_parameter(
                "Wheel.Wheel1DOF_YRecord",
                f"{axle_prefix}Tire1DOF_YParams",
                _tire_y_assignments(side_name, side),
            ),
            "",
            _format_parameter(
                "Wheel.Wheel1DOF_ZRecord",
                f"{axle_prefix}Tire1DOF_ZParams",
                _tire_z_assignments(side_name, side),
            ),
            "",
            _format_parameter(
                "TireModel.MF52Record",
                f"{axle_prefix}TireModel",
                _tire_model_assignments(tire_values, f"{axle_prefix}PartialWheel.R0", tire_path),
            ),
            "",
        )
    )
    return sections


def _axle_assignments(side_name: str, side: Mapping[str, Any], arch: ArchitectureSpec) -> tuple[tuple[str, Any], ...]:
    actuation_path = f"{side_name}.actuation"
    shock_path = f"{actuation_path}.shock"
    bellcrank_path = f"{actuation_path}.bellcrank"
    pickups_path = f"{bellcrank_path}.pickups_m"
    actuation = _mapping(side.get("actuation"), actuation_path)
    shock = _mapping(actuation.get("shock"), shock_path)
    assignments: list[tuple[str, Any]] = []
    if arch.has_bellcrank:
        bellcrank = _mapping(actuation.get("bellcrank"), bellcrank_path)
        pickups = _mapping(bellcrank.get("pickups_m"), pickups_path)
        pickup_order = _pickup_order(
            pickups,
            _required_vector(bellcrank, "pivot_m", bellcrank_path),
            _required_vector(bellcrank, "axis", bellcrank_path),
            pickups_path,
        )
        assignments.extend(
            (
                ("bellcrankPivot", _required_vector(bellcrank, "pivot_m", bellcrank_path)),
                ("bellcrankPivotAxis", _required_vector(bellcrank, "axis", bellcrank_path)),
                ("bellcrankRodPickup", _required_vector(pickups, "rod", pickups_path)),
                ("bellcrankShockPickup", _required_vector(pickups, "shock", pickups_path)),
            )
        )
        if arch.has_stabar:
            assignments.append(
                ("bellcrankStabarPickup", _required_vector(pickups, "stabar", pickups_path))
            )
        assignments.extend((("rodPickup", pickup_order["rod"]), ("shockPickup", pickup_order["shock"])))
        if arch.has_stabar:
            assignments.append(("stabarPickup", pickup_order["stabar"]))
    spring_path = f"{shock_path}.spring_table"
    damper_path = f"{shock_path}.damper_table"
    spring_table = _required_table(_mapping(shock.get("spring_table"), spring_path), "table", spring_path)
    damper_table = _required_table(_mapping(shock.get("damper_table"), damper_path), "table", damper_path)
    assignments.extend(
        (
            ("rodToLower", str(actuation.get("rod_to", "lower")).lower() == "lower"),
            ("rodMount", _required_vector(actuation, "rod_mount_m", actuation_path)),
            ("shockMount", _required_vector(shock, "mount_m", shock_path)),
            ("springTable", SemicolonMatrix(spring_table)),
            ("springFreeLength", _required_number(shock, "free_length_m", shock_path)),
            ("damperTable", SemicolonMatrix(damper_table)),
        )
    )
    return tuple(assignments)


def _stabar_assignments(side_name: str, side: Mapping[str, Any]) -> tuple[tuple[str, Any], ...]:
    actuation_path = f"{side_name}.actuation"
    stabar_path = f"{actuation_path}.stabar"
    stabar = _mapping(_mapping(side.get("actuation"), actuation_path).get("stabar"), stabar_path)
    return (
        ("leftArmEnd", _required_vector(stabar, "arm_end_m", f"{side_name}.actuation.stabar")),
        ("leftBarEnd", _required_vector(stabar, "bar_end_m", f"{side_name}.actuation.stabar")),
        ("barRate", _required_number(stabar, "rate_n_m_per_rad", f"{side_name}.actuation.stabar")),
    )


def _wheel_assignments(side_name: str, side: Mapping[str, Any]) -> tuple[tuple[str, Any], ...]:
    wheel = _mapping(side.get("wheel"), f"{side_name}.wheel")
    radius = _required_number(wheel, "radius_m", f"{side_name}.wheel")
    rim_radius = radius * _number(wheel.get("rim_radius_ratio", 0.625), f"{side_name}.wheel.rim_radius_ratio")
    rim_width = rim_radius * _number(wheel.get("rim_width_ratio", 1.4), f"{side_name}.wheel.rim_width_ratio")
    return (
        ("R0", radius),
        ("rimR0", rim_radius),
        ("rimWidth", rim_width),
        ("staticAlpha", _number(wheel.get("toe_deg", 0), f"{side_name}.wheel.toe_deg")),
        ("staticGamma", _number(wheel.get("camber_deg", 0), f"{side_name}.wheel.camber_deg")),
    )


def _rack_assignments(side_name: str, side: Mapping[str, Any]) -> tuple[tuple[str, Any], ...]:
    steering = _mapping(side.get("steering"), f"{side_name}.steering")
    return (
        ("leftPickup", _required_vector(steering, "rack_pickup_m", f"{side_name}.steering")),
        ("cFactor", _required_number(steering, "rack_travel_per_rev_m", f"{side_name}.steering")),
    )


def _wishbone_assignments(side_name: str, side: Mapping[str, Any]) -> tuple[tuple[str, Any], ...]:
    suspension = _mapping(side.get("suspension"), f"{side_name}.suspension")
    return (
        ("upperFore_i", _required_vector(suspension, "upper_fore_i_m", f"{side_name}.suspension")),
        ("upperAft_i", _required_vector(suspension, "upper_aft_i_m", f"{side_name}.suspension")),
        ("lowerFore_i", _required_vector(suspension, "lower_fore_i_m", f"{side_name}.suspension")),
        ("lowerAft_i", _required_vector(suspension, "lower_aft_i_m", f"{side_name}.suspension")),
        ("upper_o", _required_vector(suspension, "upper_o_m", f"{side_name}.suspension")),
        ("lower_o", _required_vector(suspension, "lower_o_m", f"{side_name}.suspension")),
        ("tie_o", _required_vector(suspension, "tie_o_m", f"{side_name}.suspension")),
        ("wheelCenter", _required_vector(suspension, "wheel_center_m", f"{side_name}.suspension")),
    )


def _axle_mass_assignments(side_name: str, side: Mapping[str, Any]) -> tuple[tuple[str, Any], ...]:
    masses = _mapping(side.get("masses"), f"{side_name}.masses")
    return (
        ("unsprungMass", _mass_record(masses, "unsprung", f"{side_name}.masses")),
        ("ucaMass", _mass_record(masses, "upper_control_arm", f"{side_name}.masses")),
        ("lcaMass", _mass_record(masses, "lower_control_arm", f"{side_name}.masses")),
        ("tieMass", _mass_record(masses, "tie_rod", f"{side_name}.masses")),
    )


def _tire_y_assignments(side_name: str, side: Mapping[str, Any]) -> tuple[tuple[str, Any], ...]:
    tire = _mapping(side.get("tire"), f"{side_name}.tire")
    return (("wheelJ", _required_number(tire, "wheel_inertia_kg_m2", f"{side_name}.tire")),)


def _tire_z_assignments(side_name: str, side: Mapping[str, Any]) -> tuple[tuple[str, Any], ...]:
    tire = _mapping(side.get("tire"), f"{side_name}.tire")
    return (
        ("wheelC", _required_number(tire, "vertical_stiffness_n_per_m", f"{side_name}.tire")),
        ("wheelD", _required_number(tire, "vertical_damping_n_s_per_m", f"{side_name}.tire")),
    )


def _tire_model_assignments(
    tire_values: Mapping[str, float | str],
    wheel_radius_expression: str,
    tire_path: Path,
) -> tuple[tuple[str, Any], ...]:
    assignments: list[tuple[str, Any]] = []
    for name, type_name, keys in TIRE_RECORDS:
        values: list[tuple[str, Any]] = []
        for key in keys:
            if key == "UNLOADED_RADIUS":
                values.append((key, ModelicaExpression(wheel_radius_expression)))
            else:
                tir_key = TIR_KEY_ALIASES.get(key, key)
                values.append((key, _tir_number(tire_values, tir_key, tire_path, key)))
        assignments.append((name, ModelicaCall(type_name, tuple(values))))
    return tuple(assignments)


def _powertrain_sections(data: Mapping[str, Any]) -> list[str]:
    powertrain = data.get("powertrain")
    if not isinstance(powertrain, Mapping):
        return [
            _format_parameter(record_type, record_name, ())
            for record_name, record_type in POWERTRAIN_RECORDS
        ] + [""]
    sections: list[str] = []
    for record_name, record_type in POWERTRAIN_RECORDS:
        values = powertrain.get(record_name, {})
        assignments = tuple((str(key), value) for key, value in values.items()) if isinstance(values, Mapping) else ()
        sections.extend((_format_parameter(record_type, record_name, assignments), ""))
    return sections


def _vehicle_mass_sections(data: Mapping[str, Any]) -> list[str]:
    sprung = _mapping(data.get("sprung_mass"), "sprung_mass")
    driver = _mapping(data.get("driver_mass"), "driver_mass")
    body = _mapping(data.get("body"), "body")
    torsional_stiff = _format_mo(_required_number(body, "torsional_stiff_n_m_per_rad", "body"))
    return [
        _format_parameter("MassRecord", "pBaseSprungMass", _mass_record_assignments(sprung, "sprung_mass")),
        "",
        _format_parameter("MassRecord", "pDriverMass", _mass_record_assignments(driver, "driver_mass")),
        "",
        f"  parameter Modelica.Units.SI.RotationalSpringConstant pTorsionalStiff = {torsional_stiff};",
        "",
        "  parameter MassRecord pSprungMass = "
        "BobLib.Utilities.Mechanics.Functions.combineMassRecords({pBaseSprungMass, pDriverMass});",
        "",
    ]


def _aero_section(data: Mapping[str, Any]) -> str:
    aero = _mapping(data.get("aero"), "aero")
    assignments = (
        ("referenceSpeed", _required_number(aero, "reference_speed_m_per_s", "aero")),
        ("aeroRef", _required_vector(aero, "aero_ref_m", "aero")),
        ("FL_RideHeightRef", _required_vector(aero, "front_left_ride_height_ref_m", "aero")),
        ("RL_RideHeightRef", _required_vector(aero, "rear_left_ride_height_ref_m", "aero")),
        ("frontRideHeightGrid", _required_vector(aero, "front_ride_height_grid_m", "aero")),
        ("rearRideHeightGrid", _required_vector(aero, "rear_ride_height_grid_m", "aero")),
        ("dragTable", _required_table(aero, "drag_table_n", "aero")),
        ("downforceTable", _required_table(aero, "downforce_table_n", "aero")),
        ("mxTable", _required_table(aero, "mx_table_nm", "aero")),
        ("myTable", _required_table(aero, "my_table_nm", "aero")),
        ("mzTable", _required_table(aero, "mz_table_nm", "aero")),
    )
    return _format_parameter("Aero.CFDAeroMapRecord", "pAero", assignments)


def _mass_record(parent: Mapping[str, Any], key: str, path: str) -> ModelicaCall:
    mass = _mapping(parent.get(key), f"{path}.{key}")
    return ModelicaCall("MassRecord", _mass_record_assignments(mass, f"{path}.{key}"))


def _mass_record_assignments(mass: Mapping[str, Any], path: str) -> tuple[tuple[str, Any], ...]:
    return (
        ("m", _required_number(mass, "mass_kg", path)),
        ("rCM", _required_vector(mass, "cg_m", path)),
        ("inertia", _required_table(mass, "inertia_kg_m2", path)),
    )


def _vehicle_template_text(
    template_name: str,
    record_name: str,
    front_arch: ArchitectureSpec,
    rear_arch: ArchitectureSpec,
) -> str:
    chassis_assignments: list[tuple[str, Any]] = [
        ("redeclare record VehicleRecord", ModelicaExpression(f"BobLib.Records.VehicleDefn.{record_name}")),
        ("redeclare model FrAxleModel", ModelicaExpression(front_arch.front_model)),
        ("redeclare model RrAxleModel", ModelicaExpression(rear_arch.rear_model)),
    ]
    if front_arch.has_stabar:
        chassis_assignments.append(
            ("pFrStabar", _stabar_passthrough_call("pFrStabar", bar_rate="pVehicle.pFrStabar.barRate"))
        )
    if rear_arch.has_stabar:
        chassis_assignments.append(
            ("pRrStabar", _stabar_passthrough_call("pRrStabar", bar_rate="pVehicle.pRrStabar.barRate"))
        )
    chassis_assignments.extend(
        (
            ("headless", ModelicaExpression("headless")),
            ("initialLongitudinalVelocity", ModelicaExpression("initialVel")),
            ("pVehicle", ModelicaExpression("pVehicle")),
        )
    )
    extends_call = ModelicaCall(
        "BaseVehicleSim",
        (
            ("redeclare record VehicleRecord", ModelicaExpression(f"BobLib.Records.VehicleDefn.{record_name}")),
            ("redeclare BobLib.Chassis.Chassis_DW chassis", ModelicaCall("", tuple(chassis_assignments))),
        ),
    )
    lines = [
        "within BobLib.Experiments.Standards.Templates.Vehicle;",
        "",
        f"model {template_name}",
        "",
        _extends_line(extends_call),
        f"end {template_name};",
        "",
    ]
    return "\n".join(lines)


def _four_post_template_text(
    template_name: str,
    record_name: str,
    front_arch: ArchitectureSpec,
    rear_arch: ArchitectureSpec,
) -> str:
    assignments: list[tuple[str, Any]] = [
        ("redeclare record VehicleRecord", ModelicaExpression(f"BobLib.Records.VehicleDefn.{record_name}")),
        ("redeclare model FrAxleModel", ModelicaExpression(front_arch.front_model)),
        ("redeclare model RrAxleModel", ModelicaExpression(rear_arch.rear_model)),
    ]
    if front_arch.has_stabar:
        assignments.extend(
            (
                ("frAxleDW", ModelicaCall("", (("pStabar", ModelicaExpression("pFrStabar")),))),
                ("pFrStabar", _stabar_passthrough_call("pFrStabar", bar_rate="0")),
            )
        )
    if rear_arch.has_stabar:
        assignments.extend(
            (
                ("rrAxleDW", ModelicaCall("", (("pStabar", ModelicaExpression("pRrStabar")),))),
                ("pRrStabar", _stabar_passthrough_call("pRrStabar", bar_rate="0")),
            )
        )
    lines = [
        "within BobLib.Experiments.Standards.Templates.FourPost;",
        "",
        f"model {template_name}",
        "",
        _extends_line(ModelicaCall("BaseFourPostSim", tuple(assignments))),
        "  annotation(",
        '    Documentation(info = "<html>',
        "<p>",
        f"Generated four-post template <code>{template_name}</code> binds the selected vehicle record "
        "and axle architecture.",
        "</p>",
        '</html>"));',
        f"end {template_name};",
        "",
    ]
    return "\n".join(lines)


def _vehicle_entry_text(vehicle_template_name: str) -> str:
    return "\n".join(
        (
            "within BobLib.Experiments.Standards;",
            "",
            "model VehicleSim",
            "",
            "  \"VehicleInterfaces-aligned BobLib vehicle simulation entrypoint\"",
            f"  extends Templates.Vehicle.{vehicle_template_name};",
            "  extends BobLib.Icons.SimulationIcon;",
            "",
            "  annotation(",
            "    experiment(StartTime = 0.0, StopTime = 10, Tolerance = 1e-06, Interval = 0.002),",
            f'    __OpenModelica_commandLineOptions = "{VEHICLE_OMC_OPTIONS}",',
            "    __OpenModelica_simulationFlags(",
            '      jacobian = "internalNumerical",',
            '      lv = "LOG_STDOUT,LOG_ASSERT,LOG_STATS",',
            '      noEquidistantTimeGrid = "()",',
            '      noEventEmit = "()",',
            '      s = "dassl",',
            f'      variableFilter = "{VEHICLE_VARIABLE_FILTER}"),',
            "    Documentation(info = \"<html><p>Generated standard vehicle simulation entry point.</p></html>\"));",
            "end VehicleSim;",
            "",
        )
    )


def _four_post_entry_text(four_post_template_name: str) -> str:
    return "\n".join(
        (
            "within BobLib.Experiments.Standards;",
            "",
            "model FourPostSim",
            "",
            f"  extends Templates.FourPost.{four_post_template_name};",
            "  extends BobLib.Icons.SimulationIcon;",
            "",
            "  annotation(",
            "    experiment(StartTime = 0, StopTime = 118, Tolerance = 1e-06, Interval = 1),",
            f'    __OpenModelica_commandLineOptions = "{FOUR_POST_OMC_OPTIONS}",',
            "    __OpenModelica_simulationFlags(",
            '      jacobian = "internalNumerical",',
            '      lv = "LOG_STDOUT,LOG_ASSERT,LOG_STATS",',
            '      s = "dassl",',
            '      variableFilter = ".*"),',
            "    Documentation(info = \"<html><p>Generated standard four-post simulation entry point.</p></html>\"));",
            "end FourPostSim;",
            "",
        )
    )


def _stabar_passthrough_call(name: str, *, bar_rate: str) -> ModelicaCall:
    return ModelicaCall(
        "",
        (
            ("leftArmEnd", ModelicaExpression(f"pVehicle.{name}.leftArmEnd")),
            ("leftBarEnd", ModelicaExpression(f"pVehicle.{name}.leftBarEnd")),
            ("barRate", ModelicaExpression(bar_rate)),
        ),
    )


def _extends_line(call: ModelicaCall) -> str:
    text = _format_call(call, indent=2)
    lines = text.splitlines()
    lines[0] = f"  extends {lines[0]}"
    lines[-1] = f"{lines[-1]};"
    return "\n".join(lines)


def _format_parameter(type_name: str, name: str, assignments: Iterable[tuple[str, Any]]) -> str:
    text = _format_call(ModelicaCall(f"parameter {type_name} {name}", tuple(assignments)), indent=2)
    lines = text.splitlines()
    lines[0] = f"  {lines[0]}"
    lines[-1] = f"{lines[-1]};"
    return "\n".join(lines)


def _format_call(call: ModelicaCall, indent: int) -> str:
    assignments = tuple(call.assignments)
    if not assignments:
        return f"{call.type_name}()" if call.type_name else "()"
    lines = [f"{call.type_name}(" if call.type_name else "("]
    for index, (name, value) in enumerate(assignments):
        suffix = "," if index < len(assignments) - 1 else ""
        # +4, not +2: this is the indent BobLib's checked-in records already use.
        # Emitting +2 made every regeneration rewrite files whose values had not
        # changed, so the library showed hundreds of lines of pure whitespace diff.
        lines.extend(_format_assignment(name, value, indent + 4, suffix))
    lines.append(f"{' ' * indent})")
    return "\n".join(lines)


def _format_assignment(name: str, value: Any, indent: int, suffix: str) -> list[str]:
    if isinstance(value, ModelicaCall) and not value.type_name:
        call = _format_call(ModelicaCall(name, value.assignments), indent)
        lines = call.splitlines()
        lines[0] = f"{' ' * indent}{lines[0]}"
        lines[-1] = f"{lines[-1]}{suffix}"
        return lines
    formatted = _format_mo(value, indent + 2)
    lines = formatted.splitlines() or [""]
    lines[0] = f"{' ' * indent}{name} = {lines[0]}"
    lines[-1] = f"{lines[-1]}{suffix}"
    return lines


def _format_mo(value: Any, indent: int = 0) -> str:
    if isinstance(value, ModelicaExpression):
        return value.text
    if isinstance(value, ModelicaCall):
        return _format_call(value, indent)
    if isinstance(value, SemicolonMatrix):
        return _semicolon_matrix(value.rows)
    if isinstance(value, bool):
        return "true" if value else "false"
    if isinstance(value, int):
        return str(value)
    if isinstance(value, float):
        return _format_number(value)
    if isinstance(value, str):
        return f'"{value.replace(chr(34), chr(92) + chr(34))}"'
    if isinstance(value, Sequence) and not isinstance(value, bytes | bytearray | str):
        return _format_sequence(value)
    if value is None:
        raise TypeError("Cannot format None as Modelica")
    return _format_number(_number(value, "Modelica value"))


def _format_sequence(values: Sequence[Any]) -> str:
    return "{" + ", ".join(_format_mo(item) for item in values) + "}"


def _semicolon_matrix(rows: Sequence[Sequence[Any]]) -> str:
    return "[" + "; ".join(", ".join(_format_mo(item) for item in row) for row in rows) + "]"


def _format_number(value: float) -> str:
    if not isinstance(value, float):
        value = float(value)
    if value.is_integer():
        return str(int(value))
    return f"{value:.15g}"


def _pickup_order(
    pickups: Mapping[str, Any], pivot: Sequence[float], axis: Sequence[float], path: str
) -> dict[str, int]:
    """Number the bellcrank pickups the way BobLib defines them.

    BobLib's own annotation is the spec: "1 is the most counter-clockwise pickup
    about the left bellcrank (generally with the lowest Z coordinate)". So the
    index is a property of where the points sit on the rocker, not of the order
    somebody happened to list them in.

    Deriving it from `bellcrank.order` was wrong: that list reads
    ['rod', 'shock', 'stabar'] on both axles of the baseline, while the true
    ordering is stabar/rod/shock at the front and rod/shock/stabar at the rear.
    One list cannot encode two different arrangements, so it never could have
    been right for both.

    Counter-clockwise is cyclic, so the lowest-Z pickup anchors index 1 - which
    is what the parenthetical in the annotation is telling us.
    """
    for item in ("rod", "shock"):
        if item not in pickups:
            raise KeyError(f"Missing {item!r} in {path}")

    normal = np.asarray(axis, dtype=float)
    length = float(np.linalg.norm(normal))
    if length == 0.0:
        raise ValueError(f"{path}: bellcrank axis has zero length")
    normal /= length

    # Any reference not parallel to the axis gives a valid in-plane basis; the
    # resulting angles are only ever compared with each other.
    reference = np.array([0.0, 0.0, 1.0])
    if abs(float(np.dot(reference, normal))) > 0.9:
        reference = np.array([1.0, 0.0, 0.0])
    e1 = reference - float(np.dot(reference, normal)) * normal
    e1 /= float(np.linalg.norm(e1))
    e2 = np.cross(normal, e1)

    angles: dict[str, float] = {}
    for name, point in pickups.items():
        offset = np.asarray(point, dtype=float) - np.asarray(pivot, dtype=float)
        offset = offset - float(np.dot(offset, normal)) * normal
        angles[name] = math.atan2(float(np.dot(offset, e2)), float(np.dot(offset, e1)))

    anchor = min(pickups, key=lambda name: float(pickups[name][2]))
    sweep = {name: (angles[name] - angles[anchor]) % (2.0 * math.pi) for name in angles}
    ordered = sorted(sweep, key=lambda name: sweep[name])
    return {name: index + 1 for index, name in enumerate(ordered)}


def _mapping(value: Any, path: str) -> Mapping[str, Any]:
    if not isinstance(value, Mapping):
        raise TypeError(f"Expected {path} to be a mapping")
    return value


def _architecture(value: str, path: str) -> ArchitectureSpec:
    try:
        return ARCHITECTURES[value]
    except KeyError as exc:
        choices = ", ".join(sorted(ARCHITECTURES))
        raise ValueError(f"Unknown {path} value {value!r}. Expected one of: {choices}") from exc


def _required_number(mapping: Mapping[str, Any], key: str, path: str) -> float:
    if key not in mapping:
        raise KeyError(f"Missing required key {path}.{key}")
    return _number(mapping[key], f"{path}.{key}")


def _number(value: Any, path: str) -> float:
    if isinstance(value, bool):
        raise TypeError(f"Expected numeric value at {path}")
    try:
        return float(value)
    except (TypeError, ValueError) as exc:
        raise TypeError(f"Expected numeric value at {path}") from exc


def _required_vector(mapping: Mapping[str, Any], key: str, path: str) -> tuple[float, ...]:
    if key not in mapping:
        raise KeyError(f"Missing required key {path}.{key}")
    value = mapping[key]
    if not isinstance(value, Sequence) or isinstance(value, str):
        raise TypeError(f"Expected {path}.{key} to be a vector")
    return tuple(_number(item, f"{path}.{key}") for item in value)


def _required_table(mapping: Mapping[str, Any], key: str, path: str) -> tuple[tuple[float, ...], ...]:
    if key not in mapping:
        raise KeyError(f"Missing required key {path}.{key}")
    value = mapping[key]
    if not isinstance(value, Sequence) or isinstance(value, str):
        raise TypeError(f"Expected {path}.{key} to be a table")
    rows: list[tuple[float, ...]] = []
    for row_index, row in enumerate(value):
        if not isinstance(row, Sequence) or isinstance(row, str):
            raise TypeError(f"Expected {path}.{key}[{row_index}] to be a row")
        rows.append(tuple(_number(item, f"{path}.{key}[{row_index}]") for item in row))
    return tuple(rows)


def _tir_number(values: Mapping[str, float | str], tir_key: str, tire_path: Path, record_key: str) -> float:
    if tir_key not in values:
        raise KeyError(f"Missing {tir_key} for {record_key} in {tire_path}")
    return _number(values[tir_key], f"{tire_path}:{tir_key}")


def _boblib_root(data: Mapping[str, Any], repo_root: Path) -> Path:
    paths = data.get("paths", {})
    default = "_0_Utils/external/BobLib/BobLib"
    raw_path = paths.get("boblib", default) if isinstance(paths, Mapping) else default
    return _resolve_path(repo_root, str(raw_path))


def _tire_root(data: Mapping[str, Any], repo_root: Path) -> Path:
    paths = data.get("paths", {})
    default = "_0_Utils/tire_templates"
    raw_path = paths.get("tire_templates", default) if isinstance(paths, Mapping) else default
    return _resolve_path(repo_root, str(raw_path))


def _resolve_path(repo_root: Path, raw_path: str) -> Path:
    path = Path(raw_path)
    return path if path.is_absolute() else (repo_root / path).resolve()


def _modelica_identifier(raw_name: str) -> str:
    name = re.sub(r"\W+", "_", raw_name.strip())
    name = re.sub(r"_+", "_", name).strip("_")
    if not name:
        name = "GeneratedVehicle"
    if not re.match(r"[A-Za-z_]", name):
        name = f"Generated_{name}"
    return name


def _write_text(path: Path, text: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8")


def _ensure_package_order_entry(path: Path, entry: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    existing = path.read_text(encoding="utf-8").splitlines() if path.is_file() else []
    if entry not in existing:
        existing.append(entry)
        path.write_text("\n".join(existing) + "\n", encoding="utf-8")


def _display_path(path: Path, repo_root: Path) -> str:
    """Repo-relative path for API payloads and the browser UI.

    Always forward-slashed: these strings are compared against and served as
    repo-relative keys, so they must not vary with the host OS separator.
    """
    try:
        return path.resolve().relative_to(repo_root).as_posix()
    except ValueError:
        return str(path)
