"""overrides.py — Evaluate a vehicle on an already-compiled executable.

Compiling a variant costs about twice what simulating it does, and between
variants the model's equations never change: only parameter values do. Every
swept parameter lands on a runtime-changeable `pVehicle.*` root in the compiled
model, so one executable can stand in for any variant by overriding those
roots. This module owns the mapping from a DOE variable to its override names.

The runner drops any override it cannot find in the init XML without saying so.
A misspelled name would therefore sweep nothing, silently — the same failure
the DOE docs warn about for a wrong `path`. Every name is checked here first.
"""

from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
from typing import Any
import xml.etree.ElementTree as ET

from StandardSens.pipeline.generator import resolve_targets

# The vehicle record instance at the top of the standard experiment models.
VEHICLE_RECORD = "pVehicle"


@dataclass(frozen=True)
class InitParameter:
    start: float | None
    changeable: bool


def load_init_parameters(init_xml: Path) -> dict[str, InitParameter]:
    """Read every scalar's start value and whether it may be set at runtime."""
    parameters: dict[str, InitParameter] = {}
    for variable in ET.parse(init_xml).getroot().iter("ScalarVariable"):
        name = variable.attrib.get("name")
        if not name:
            continue
        value_node = next(iter(variable), None)
        raw = None if value_node is None else value_node.attrib.get("start")
        try:
            start = None if raw is None else float(raw)
        except ValueError:
            start = None
        parameters[name] = InitParameter(
            start=start,
            changeable=variable.attrib.get("isValueChangeable") == "true",
        )
    return parameters


def find_init_xml(build_dir: Path, exec_name: str) -> Path:
    init_xml = build_dir / f"{exec_name}_init.xml"
    if not init_xml.exists():
        raise FileNotFoundError(
            f"No init XML at {init_xml}. The baseline executable has not been compiled."
        )
    return init_xml


def override_name(target: dict[str, Any]) -> str:
    """Name a target's root parameter; DOE indices are 0-based, Modelica's 1-based."""
    name = f"{VEHICLE_RECORD}.{target['block']}.{target['param']}"
    if "index" in target:
        name += "[" + ",".join(str(int(i) + 1) for i in target["index"]) + "]"
    return name


def variant_overrides(
    variant: dict[str, float],
    variables: dict[str, dict[str, Any]],
    context: dict[str, Any],
    init_parameters: dict[str, InitParameter],
) -> dict[str, float]:
    """Translate {vehicle.yml path: value} into {Modelica parameter: value}."""
    overrides: dict[str, float] = {}
    problems: list[str] = []

    for path, value in variant.items():
        if path not in variables:
            raise KeyError(f"Path {path!r} is not a DOE variable")
        spec = variables[path]
        for target, target_value in resolve_targets(spec, float(value), context):
            name = override_name(target)
            if "targets" in spec and target.get("operation") == "scale":
                scaled = _scaled_elements(name, target_value, init_parameters)
                if not scaled:
                    problems.append(f"{name} (from {path}): no changeable elements to scale")
                overrides.update(scaled)
                continue
            parameter = init_parameters.get(name)
            if parameter is None:
                problems.append(f"{name} (from {path}): not in the compiled model")
            elif not parameter.changeable:
                problems.append(f"{name} (from {path}): fixed at compile time")
            else:
                overrides[name] = float(target_value)

    if problems:
        raise ValueError(
            "These parameters cannot be overridden on the compiled executable, so "
            "evaluating this variant would silently leave them at baseline:\n  "
            + "\n  ".join(problems)
        )
    return overrides


def _scaled_elements(
    name: str,
    factor: float,
    init_parameters: dict[str, InitParameter],
) -> dict[str, float]:
    """Scale every changeable element of a table from its compiled baseline."""
    return {
        element: parameter.start * factor
        for element, parameter in init_parameters.items()
        if (element == name or element.startswith(name + "["))
        and parameter.changeable
        and parameter.start is not None
    }
