"""overrides.py — Apply a knob to an already-compiled executable, where that is safe.

A compile is most of a variant's wall time and the model's equations never
change between variants, so re-pointing one executable with `-override` is far
cheaper than recompiling. It is only correct for some parameters, and the
incorrect cases fail without a sound. This module owns both halves of that: which
variables are safe, and what their override names are.

Two failures are guarded here:

- OpenModelica accepts an override of a parameter it has already evaluated into
  the executable. `RUNTIME_SAFE_PATHS` is the allow-list that keeps those out.
- A name that is not in the init XML cannot take effect. The runner rejects it
  before any case runs. This module rejects it earlier and names the DOE path.
"""

from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
from typing import Any

from optimization.response.pipeline.generator import resolve_targets
from simulations.response.mbd.modelica_overrides import load_init_variables

VEHICLE_RECORD = "pVehicle"

# Variables read at initialisation, so an override reaches the physics.
# isValueChangeable="true" is not enough: OpenModelica accepts an override of a
# parameter it folded into the executable and silently ignores it.
#
# Toe, camber, the frame and driver masses, their CGs and inertias and the
# frame's torsional stiffness only follow an override from BobLib #71 on, which
# builds the wheel rotation and the combined frame mass at initialisation. On
# that build an override of each matched a separately compiled variant exactly
# (every moving VehicleSim signal identical). test_optsim_overrides checks the
# pin is new enough.
#
# Re-check this list whenever the BobLib pin moves:
#   python -m optimization.response.pipeline.vet_runtime --build-dir <dir> --exec-name <exe> --check
# It probes each DOE knob at the edge of its range on one compiled executable.
# "live" is necessary, not sufficient: before adding a knob here, also compare
# an override run with a compiled variant that differs only in that knob.
RUNTIME_SAFE_PATHS = frozenset(
    {
        "front.stabar.rate_n_m_per_rad",
        "rear.stabar.rate_n_m_per_rad",
        "front.actuation.spring_rate_n_per_m",
        "rear.actuation.spring_rate_n_per_m",
        "front.actuation.damper_rate_n_s_per_m",
        "rear.actuation.damper_rate_n_s_per_m",
        "front.wheel.toe_deg",
        "rear.wheel.toe_deg",
        "front.wheel.camber_deg",
        "rear.wheel.camber_deg",
        "sprung_mass.mass_kg",
        "sprung_mass.cg_m.x",
        "sprung_mass.cg_m.z",
        "driver_mass.mass_kg",
        "driver_mass.cg_m.x",
        "driver_mass.cg_m.z",
        "driver_mass.inertia_kg_m2.ixx",
        "driver_mass.inertia_kg_m2.iyy",
        "driver_mass.inertia_kg_m2.izz",
        "body.torsional_stiff_n_m_per_rad",
    }
)

# BobLib file that #71 added; its presence marks a pin with runtime toe and mass.
RUNTIME_SETUP_MARKER = Path("engines/boblib/BobLib/Utilities/Mechanics/MultiBody/TunableFixedRotation.mo")


@dataclass(frozen=True)
class InitParameter:
    start: float | None
    changeable: bool


def load_init_parameters(init_xml: Path) -> dict[str, InitParameter]:
    """Read every scalar's start value and whether it may be set at runtime."""
    return {
        name: InitParameter(start=_float_or_none(variable.start), changeable=variable.changeable)
        for name, variable in load_init_variables(init_xml).items()
    }


def _float_or_none(raw: str | None) -> float | None:
    try:
        return None if raw is None else float(raw)
    except ValueError:
        return None


def find_init_xml(build_dir: Path, exec_name: str) -> Path:
    init_xml = build_dir / f"{exec_name}_init.xml"
    if not init_xml.exists():
        raise FileNotFoundError(f"No init XML at {init_xml}. That executable was never compiled.")
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
                # The runner also rejects a scalar with no start value.
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
