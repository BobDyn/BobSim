from __future__ import annotations

from dataclasses import dataclass, field as dataclass_field


@dataclass(frozen=True)
class OutputSpec:
    label: str
    path: str
    kind: str


@dataclass(frozen=True)
class ActionSpec:
    id: str
    label: str
    argv: tuple[str, ...]
    env: dict[str, str] = dataclass_field(default_factory=dict)
    requires_external_toolchain: bool = False


@dataclass(frozen=True)
class BuildTargetSpec:
    id: str
    label: str
    action_id: str
    build_dir: str
    exec_name: str
    script: str


@dataclass(frozen=True)
class WorkflowSpec:
    id: str
    group: str
    label: str
    config: str | None
    actions: tuple[str, ...]
    outputs: tuple[OutputSpec, ...] = ()


PathPart = str | int


@dataclass(frozen=True)
class FieldSpec:
    path: tuple[PathPart, ...]
    label: str
    kind: str = "auto"
    group: str | None = None
    unit: str | None = None
    choices: tuple[str, ...] = ()
    disabled: bool = False
    placeholder: str | None = None
    help_text: str | None = None


@dataclass(frozen=True)
class ConfigSpec:
    id: str
    group: str
    label: str
    path: str
    workflow_id: str | None = None
    fields: tuple[FieldSpec, ...] = ()
    # True when every path inside the config is repo-relative, so the app can
    # edit a per-user copy under _5_App/user_data/config/active/ instead of the
    # checked-in seed. EnvelopeSim and OptSim configs resolve their "../" paths
    # against their own directory and must stay where they are.
    relocatable: bool = False

