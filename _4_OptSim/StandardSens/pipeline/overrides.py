"""overrides.py — Apply a knob to an already-compiled executable, where that is safe.

A compile is most of a variant's wall time and the model's equations never
change between variants, so re-pointing one executable with `-override` is far
cheaper than recompiling. It is only correct for some parameters, and the
incorrect cases fail without a sound. This module owns both halves of that: which
variables are safe, and what their override names are.

Two silent failures are guarded here:

- OpenModelica accepts an override of a parameter it has already evaluated into
  the executable. `RUNTIME_SAFE_PATHS` is the allow-list that keeps those out.
- The runner drops any override name it cannot find in the init XML. Every name
  is checked against the same XML before it is handed over.
"""

from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
from typing import Any
import xml.etree.ElementTree as ET

from StandardSens.pipeline.generator import resolve_targets

# The vehicle record instance at the top of the standard experiment models.
VEHICLE_RECORD = "pVehicle"

# Variables the model reads at initialisation, so an override reaches the physics.
# Proven against BobLib v0.2.0-4-g2777aa5 by recompiling a variant that differed
# only in these six and reproducing its metrics by override on the baseline
# executable (understeer gradient to 2.5e-5 deg/g, roll gradient to 5e-6).
#
# Do NOT add a variable because its parameter says `isValueChangeable="true"`.
# Static toe and camber say so, and overriding them does nothing: they build the
# wheel's `toHub.R_rel` rotation matrix, which OpenModelica evaluates at compile
# time. The override is accepted, every bound copy of the angle updates, and the
# matrix the wheel uses stays put. Every mass and CG value fails the same way
# through `combineMassRecords`. To vet a candidate, compile two variants that
# differ only in it and diff their `*_init.xml`: a non-changeable parameter whose
# `start` differs was evaluated at compile time and will not follow an override.
# Re-check this list when the BobLib pin moves.
RUNTIME_SAFE_PATHS = frozenset(
    {
        "front.stabar.rate_n_m_per_rad",
        "rear.stabar.rate_n_m_per_rad",
        "front.actuation.spring_rate_n_per_m",
        "rear.actuation.spring_rate_n_per_m",
        "front.actuation.damper_rate_n_s_per_m",
        "rear.actuation.damper_rate_n_s_per_m",
    }
)


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
        raise FileNotFoundError(f"No init XML at {init_xml}; that executable was never compiled.")
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
        for target, target_value in resolve_targets(variables[path], float(value), context):
            name = override_name(target)
            parameter = init_parameters.get(name)
            if target.get("operation") == "scale":
                problems.append(f"{name} (from {path}): scaled tables are compiled, not overridden")
            elif parameter is None or parameter.start is None:
                # The runner looks names up by their start value, so a scalar
                # without one is dropped there exactly as a missing name is.
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
