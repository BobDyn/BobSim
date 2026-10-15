"""Plan and check the runtime overrides of a compiled OpenModelica executable.

The executable cannot apply an unknown name or a calculated parameter. It writes
one run.log warning and still exits 0. So the runner plans every override
against the build's init XML before any process starts, and it checks run.log
after each run. Both checks raise `OverrideError`.

A planned override can still have no effect. OpenModelica evaluates some
changeable parameters, such as static toe, at compile time. Only an achieved
signal shows that a change took effect.
"""

from __future__ import annotations

from collections.abc import Iterable, Mapping
from dataclasses import asdict, dataclass, field
import os
import re
from typing import Any
import xml.etree.ElementTree as ET

import numpy as np

MODELICA_OVERRIDE_ALIASES = {
    # VCU targetVel derives from initialVel. Override the source so chassis, driveline, and VCU move together.
    "targetVel": "initialVel",
    "targetAy": "vcu.targetAy",
    "useMode": "vcu.useMode",
    "steerStart": "vcu.steerStart",
    "linearitySlopeSamplePeriod": "vcu.linearitySlopeSamplePeriod",
    "handwheelRampRate": "vcu.handwheelRampRate",
    "handwheelRampStopDuration": "vcu.handwheelRampStopDuration",
    "enableNormalLoadSteerLimiter": "vcu.enableNormalLoadSteerLimiter",
    "tireNormalLoadMin": "vcu.tireNormalLoadMin",
    "steadyStateAyRampRate": "vcu.steadyStateAyRampRate",
    "steadyStateMaxHandwheel": "vcu.steadyStateMaxHandwheel",
    "steadyStateAyGain": "vcu.steadyStateAyGain",
    "steadyStateAyTi": "vcu.steadyStateAyTi",
    "steadyStateSteerTimeConstant": "vcu.steadyStateSteerTimeConstant",
    "frRampSteerHeight": "vcu.frRampSteerHeight",
    "frRampSteerDuration": "vcu.frRampSteerDuration",
    "stepDuration": "vcu.stepDuration",
    "steerAmp": "vcu.steerAmp",
    "steerFreq": "vcu.steerFreq",
    "velGain": "vcu.velGain",
    "velTi": "vcu.velTi",
}

# The runner reads these case keys itself. They never go to the override file.
RUNNER_CASE_KEYS = frozenset({"startTime", "stopTime", "stepSize", "timeout_s"})

OVERRIDE_REASONS = (
    "unknown_name",
    "no_start_value",
    "not_changeable",
    "conflicting_aliases",
    "missing_init_xml",
    "not_applied",
)

# OpenModelica echoes each applied override ("override NAME = VALUE") only on this stream.
READBACK_LOG_STREAM = "LOG_SOLVER"

_APPLIED_LINE = re.compile(r"\|\s*override\s+(?P<name>[^\s=]+)\s*=\s*(?P<value>.*?)\s*$")
_REFUSED_LINES = (
    re.compile(r"it is not possible to override the following quantity(?::\s*(?P<name>\S+))?", re.IGNORECASE),
    re.compile(r"override variable name not found in model(?::\s*(?P<name>\S+))?", re.IGNORECASE),
)


@dataclass(frozen=True)
class InitVariable:
    name: str
    start: str | None
    causality: str | None
    variability: str | None
    changeable: bool


@dataclass(frozen=True)
class OverrideRejection:
    key: str
    modelica_name: str
    reason: str
    requested: object
    detail: str

    def as_dict(self) -> dict[str, Any]:
        return asdict(self)


class OverrideError(ValueError):
    """One or more runtime overrides cannot take effect. Nothing from the run is valid."""

    def __init__(self, rejections: Iterable[OverrideRejection]):
        self.rejections: tuple[OverrideRejection, ...] = tuple(rejections)
        super().__init__(_error_message(self.rejections))

    def __reduce__(self) -> tuple[Any, ...]:
        return (type(self), (self.rejections,))


@dataclass(frozen=True)
class OverridePlan:
    """What one case asks for and what the runner writes to the override file."""

    requested: dict[str, Any] = field(default_factory=dict)
    written: dict[str, str] = field(default_factory=dict)
    already_compiled: dict[str, str] = field(default_factory=dict)
    modelica_names: dict[str, str] = field(default_factory=dict)

    def file_text(self) -> str:
        return "".join(f"{name}={value}\n" for name, value in self.written.items())

    def manifest(
        self,
        file_sha256: str | None,
        readback: Mapping[str, Any] | None = None,
        rejected: Iterable[OverrideRejection] = (),
    ) -> dict[str, Any]:
        return {
            "requested": dict(self.requested),
            "written": dict(self.written),
            "already_compiled": dict(self.already_compiled),
            "rejected": [rejection.as_dict() for rejection in rejected],
            "readback": dict(readback or {}),
            "file_sha256": file_sha256,
        }


@dataclass(frozen=True)
class OverrideLog:
    applied: dict[str, str]
    refused: dict[str, str]


def load_init_variables(init_xml: str | os.PathLike[str]) -> dict[str, InitVariable]:
    """Read each ScalarVariable of an OpenModelica *_init.xml."""
    variables: dict[str, InitVariable] = {}
    for _, element in ET.iterparse(init_xml, events=("end",)):
        if element.tag != "ScalarVariable":
            continue
        name = element.attrib.get("name")
        if name:
            value_node = next(iter(element), None)
            variables[name] = InitVariable(
                name=name,
                start=None if value_node is None else value_node.attrib.get("start"),
                causality=element.attrib.get("causality"),
                variability=element.attrib.get("variability"),
                changeable=element.attrib.get("isValueChangeable") == "true",
            )
        element.clear()
    return variables


def format_override_value(value: Any) -> str:
    if isinstance(value, (bool, np.bool_)):
        return "true" if value else "false"
    if isinstance(value, (float, np.floating)):
        return repr(float(value))
    if isinstance(value, (int, np.integer)):
        return str(int(value))
    return str(value)


def values_match(left: str, right: str) -> bool:
    left, right = left.strip(), right.strip()
    if left.lower() in {"true", "false"} or right.lower() in {"true", "false"}:
        return left.lower() == right.lower()
    try:
        return float(left) == float(right)
    except ValueError:
        return left == right


def plan_overrides(
    case: Mapping[str, Any],
    init_variables: Mapping[str, InitVariable],
    *,
    aliases: Mapping[str, str] = MODELICA_OVERRIDE_ALIASES,
) -> OverridePlan:
    """Sort each override of one case into written or already compiled, or raise OverrideError."""
    requested: dict[str, Any] = {}
    written: dict[str, str] = {}
    already_compiled: dict[str, str] = {}
    modelica_names: dict[str, str] = {}
    first_key: dict[str, tuple[str, str]] = {}
    rejections: list[OverrideRejection] = []

    for key, value in case.items():
        if key.startswith("_") or key in RUNNER_CASE_KEYS:
            continue
        name = aliases.get(key, key)
        formatted = format_override_value(value)
        requested[key] = value
        modelica_names[key] = name

        if name in first_key:
            other_key, other_value = first_key[name]
            if not values_match(formatted, other_value):
                detail = f"`{other_key}` also sets {name}, to {other_value}."
                rejections.append(OverrideRejection(key, name, "conflicting_aliases", value, detail))
            continue
        first_key[name] = (key, formatted)

        variable = init_variables.get(name)
        if variable is not None and variable.start is not None and values_match(formatted, variable.start):
            already_compiled[name] = formatted
        elif variable is not None and variable.changeable and variable.start is not None:
            written[name] = formatted
        else:
            rejections.append(_rejection(key, name, value, variable))

    if rejections:
        raise OverrideError(rejections)
    return OverridePlan(requested, written, already_compiled, modelica_names)


def read_override_log(log_text: str) -> OverrideLog:
    """Find the overrides that an OpenModelica run.log says it applied or refused."""
    applied: dict[str, str] = {}
    refused: dict[str, str] = {}
    for line in log_text.splitlines():
        for pattern in _REFUSED_LINES:
            match = pattern.search(line)
            if match:
                refused[match.group("name") or ""] = line.strip()
                break
        else:
            match = _APPLIED_LINE.search(line)
            if match:
                applied[match.group("name")] = match.group("value")
    return OverrideLog(applied, refused)


def readback_overrides(
    plan: OverridePlan, log_text: str
) -> tuple[dict[str, dict[str, str | None]], tuple[OverrideRejection, ...]]:
    """Compare run.log with the plan. Return the readback per written name and any not_applied rejections."""
    log = read_override_log(log_text)
    key_of = {name: key for key, name in reversed(plan.modelica_names.items())}
    readback: dict[str, dict[str, str | None]] = {}
    rejections: list[OverrideRejection] = []

    def reject(name: str, detail: str) -> None:
        key = key_of.get(name, name)
        rejections.append(OverrideRejection(key, name, "not_applied", plan.requested.get(key), detail))

    for name, requested in plan.written.items():
        observed = log.applied.get(name)
        if observed is None:
            status = "unavailable"
        elif values_match(observed, requested):
            status = "match"
        else:
            status = "mismatch"
            reject(name, f"The executable read {observed}, not {requested}.")
        readback[name] = {"requested": requested, "observed": observed, "status": status}

    for name, line in log.refused.items():
        reject(name, f"run.log: {line}")

    return readback, tuple(rejections)


def with_readback_stream(log_level: str | None) -> str:
    streams = [stream.strip() for stream in str(log_level or "").split(",") if stream.strip()]
    if READBACK_LOG_STREAM not in streams:
        streams.append(READBACK_LOG_STREAM)
    return ",".join(streams)


def _rejection(key: str, name: str, value: Any, variable: InitVariable | None) -> OverrideRejection:
    if variable is None:
        return OverrideRejection(
            key, name, "unknown_name", value, "The compiled model has no variable with this name. Check the spelling."
        )
    if not variable.changeable:
        compiled = "no start value" if variable.start is None else f"compiled start {variable.start}"
        return OverrideRejection(
            key,
            name,
            "not_changeable",
            value,
            f"The init XML marks it {variable.causality} with isValueChangeable=false ({compiled}). "
            "Set the parameter that it is computed from, or change the model and recompile.",
        )
    return OverrideRejection(
        key,
        name,
        "no_start_value",
        value,
        "The init XML gives it no start value. The executable can compute it at initialization and ignore the "
        "override.",
    )


def _error_message(rejections: tuple[OverrideRejection, ...]) -> str:
    lines = [
        f"{len(rejections)} runtime override(s) cannot take effect. "
        "No simulation result is valid until each one is fixed:"
    ]
    for rejection in rejections:
        target = rejection.key
        if rejection.modelica_name and rejection.modelica_name != rejection.key:
            target += f" -> {rejection.modelica_name}"
        lines.append(f"  - {target or '(no name)'}: {rejection.reason}. {rejection.detail}")
    return "\n".join(lines)
