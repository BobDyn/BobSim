"""Every numeric vehicle.yml input reaches a consumer, or says why it does not.

The OpenModelica toe bug was an input that was accepted and did nothing. This
file catches the same failure one layer up, without a compiler: it perturbs
each numeric input of the default vehicle and checks that

* the generated BobLib stack changes, or the generator reports the input as
  unbound, and
* the reduced-order projection (dynpy and KinPy) changes, or the input is in
  ``REDUCED_IGNORES`` with a reason.

A new vehicle.yml field therefore fails here until someone wires it up or
writes down why it is ignored. An ignored field that starts to matter fails
too, so the lists cannot go stale.
"""

from __future__ import annotations

import copy
import dataclasses
import warnings
from collections.abc import Iterator, Mapping, Sequence
from pathlib import Path
from typing import Any

import numpy as np
import pytest
import yaml

from app.modelica_generator import plan_modelica_stack
from common.vehicle_io import load_yaml, repo_root, vehicle_yaml_path
from engines.dynpy import create_model, load_reduced_vehicle_parameters

Leaf = tuple[Any, ...]

# Inputs the reduced-order models do not read. Each reason says which model
# owns the input, so a reviewer can judge whether ignoring it is still right.
REDUCED_IGNORES: dict[str, str] = {
    "body/torsional_stiff_n_m_per_rad": "reduced models use a rigid frame; BobLib owns frame compliance",
    "front/wheel/rim_radius_ratio": "wheel visual geometry only",
    "front/wheel/rim_width_ratio": "wheel visual geometry only",
    "rear/wheel/rim_radius_ratio": "wheel visual geometry only",
    "rear/wheel/rim_width_ratio": "wheel visual geometry only",
    "front/steering/rack_travel_per_rev_m": "reduced models take road-wheel steer, not handwheel angle",
    "rear/steering/rack_travel_per_rev_m": "reduced models take road-wheel steer, not handwheel angle",
    "front/actuation/shock/free_length_m": "reduced models linearize about design ride height; preload is BobLib-only",
    "rear/actuation/shock/free_length_m": "reduced models linearize about design ride height; preload is BobLib-only",
    "powertrain/pBattery/Ns": "battery electrical model is BobLib-only",
    "powertrain/pBattery/Np": "battery electrical model is BobLib-only",
    "powertrain/pBattery/SOC_start": "battery electrical model is BobLib-only",
    "powertrain/pVCU/tau_max": "VCU torque request shaping is BobLib-only",
    "powertrain/pVCU/regenTorqueLimit": "VCU torque request shaping is BobLib-only",
    "powertrain/pVCU/w_eps": "VCU numerical regularization is BobLib-only",
    "powertrain/pVCU/motorSpeedSign": "sign convention of the BobLib motor port",
    "powertrain/pInverter/P_max_mot": "reduced power limit comes from pVCU.P_max_mot",
    "powertrain/pInverter/P_max_reg": "regen is BobLib-only",
    "powertrain/pInverter/V_dc_max": "inverter electrical model is BobLib-only",
    "powertrain/pMotor/Vdc_max": "motor electrical model is BobLib-only",
    "powertrain/pMotor/I_peak_2min": "motor electrical model is BobLib-only",
    "powertrain/pMotor/I_cont": "motor electrical model is BobLib-only",
    "powertrain/pMotor/Kt_Nm_per_A": "motor electrical model is BobLib-only",
    "powertrain/pMotor/peakTime": "motor thermal derate is BobLib-only",
    "powertrain/pMotor/P_mech_peak": "reduced power limit comes from pVCU.P_max_mot",
    "powertrain/pMotor/P_cont_low": "continuous power map is BobLib-only",
    "powertrain/pMotor/P_cont_high": "continuous power map is BobLib-only",
    "powertrain/pMotor/eta_mot": "motor losses are BobLib-only",
    "powertrain/pMotor/eta_reg": "regen losses are BobLib-only",
    "powertrain/pMotor/w_eps": "motor numerical regularization is BobLib-only",
    "powertrain/pMotor/rotorJ": "driveline inertia is BobLib-only",
    "powertrain/pDriveline/diffInputRotorJ": "driveline inertia is BobLib-only",
    "powertrain/pDriveline/diff_driveSideTorqueSign": "sign convention of the BobLib differential",
    "powertrain/pDriveline/diff_T_preload": "reduced models have no differential",
    "powertrain/pDriveline/diff_lockFractionAccel": "reduced models have no differential",
    "powertrain/pDriveline/diff_lockFractionDecel": "reduced models have no differential",
    "powertrain/pDriveline/diff_T_capacity_max": "reduced models have no differential",
    "powertrain/pDriveline/diff_clutchEffectiveRadius": "reduced models have no differential",
    "powertrain/pDriveline/diff_kineticFrictionRatio": "reduced models have no differential",
    "powertrain/pDriveline/diff_w_transition": "reduced models have no differential",
    "powertrain/pDriveline/diff_c_viscous": "reduced models have no differential",
    "powertrain/pDriveline/halfshaftC": "reduced models have rigid halfshafts",
    "powertrain/pDriveline/halfshaftD": "reduced models have rigid halfshafts",
    "powertrain/pDriveline/halfshaftLeftJEquivalent": "driveline inertia is BobLib-only",
    "powertrain/pDriveline/halfshaftRightJEquivalent": "driveline inertia is BobLib-only",
}

# Inputs both consumers validate, so a perturbation must be rejected rather
# than silently accepted. Each maps to the error text the loader raises.
CONSTRAINED: dict[str, str] = {
    "front/actuation/shock/damper/compression/high_speed_turns_from_open": "TTX25",
    "front/actuation/shock/damper/rebound/high_speed_turns_from_open": "TTX25",
    "rear/actuation/shock/damper/compression/high_speed_turns_from_open": "TTX25",
    "rear/actuation/shock/damper/rebound/high_speed_turns_from_open": "TTX25",
}

# Left and right halfshafts must match, so they move together.
LINKED: dict[str, tuple[str, ...]] = {
    "powertrain/pDriveline/halfshaftC": ("halfshaftLeftC", "halfshaftRightC"),
    "powertrain/pDriveline/halfshaftD": ("halfshaftLeftD", "halfshaftRightD"),
}

# Probe points for the kinematics, chosen inside the default travel limits.
PROBE_JOUNCE_M = (-0.02, 0.0, 0.015)
PROBE_STEER_RAD = (-0.12, 0.0, 0.08)


def _is_number(value: Any) -> bool:
    return isinstance(value, (int, float)) and not isinstance(value, bool)


def _leaves(node: Any, path: Leaf = ()) -> Iterator[Leaf]:
    """Yield scalar inputs and numeric vectors, which move as one input."""

    if isinstance(node, Mapping):
        for key, value in node.items():
            yield from _leaves(value, (*path, key))
    elif isinstance(node, list):
        if node and all(_is_number(item) for item in node):
            yield path
        else:
            for index, value in enumerate(node):
                yield from _leaves(value, (*path, index))
    elif _is_number(node):
        yield path


def _key(path: Leaf) -> str:
    return "/".join(str(part) for part in path)


def _get(data: Any, path: Leaf) -> Any:
    for part in path:
        data = data[part]
    return data


def _set(data: Any, path: Leaf, value: Any) -> None:
    for part in path[:-1]:
        data = data[part]
    data[path[-1]] = value


def _perturb(value: Any) -> Any:
    if isinstance(value, list):
        # A generic direction, so a point is never moved only along its own
        # pivot axis or a vector only along itself.
        scale = 0.02 * (float(np.linalg.norm(value)) + 0.1)
        direction = (0.31, 0.47, 0.83, 0.59, 0.71)
        return [float(item) + scale * direction[i % len(direction)] for i, item in enumerate(value)]
    if isinstance(value, int):
        return value + 1
    return float(value) * 1.05 + 0.003


def _default_vehicle() -> dict[str, Any]:
    return copy.deepcopy(load_yaml(vehicle_yaml_path()))


def _input_groups() -> list[str]:
    data = _default_vehicle()
    linked = {f"powertrain/pDriveline/{name}" for names in LINKED.values() for name in names}
    keys = [_key(path) for path in _leaves(data)]
    return [key for key in keys if key not in linked] + sorted(LINKED)


def _perturbed_vehicle(tmp_path: Path, key: str) -> Path:
    data = _default_vehicle()
    if key in LINKED:
        parent = key.rsplit("/", 1)[0].split("/")
        for name in LINKED[key]:
            path = (*parent, name)
            _set(data, path, _perturb(_get(data, path)))
    else:
        index_path: tuple[str | int, ...] = tuple(
            int(part) if part.isdigit() else part for part in key.split("/")
        )
        _set(data, index_path, _perturb(_get(data, index_path)))
    target = tmp_path / "vehicle.yml"
    target.write_text(yaml.safe_dump(data, sort_keys=False), encoding="utf-8")
    return target


def _numbers(value: Any, depth: int = 0) -> Iterator[float]:
    """Flatten every number reachable from a parameter object."""

    if depth > 6 or value is None or isinstance(value, (str, bool)):
        return
    if _is_number(value) or isinstance(value, np.floating):
        yield float(value)
    elif isinstance(value, np.ndarray):
        yield from np.asarray(value, dtype=float).ravel()
    elif dataclasses.is_dataclass(value) and not isinstance(value, type):
        for field in dataclasses.fields(value):
            if field.name != "kinematics":
                yield from _numbers(getattr(value, field.name), depth + 1)
    elif isinstance(value, Mapping):
        for item_key in sorted(value, key=str):
            yield from _numbers(value[item_key], depth + 1)
    elif isinstance(value, Sequence):
        for item in value:
            yield from _numbers(item, depth + 1)


def _reduced_fingerprint(vehicle: Path) -> np.ndarray:
    with warnings.catch_warnings():
        warnings.simplefilter("ignore", RuntimeWarning)
        params = load_reduced_vehicle_parameters(vehicle)
        values = list(_numbers(params))
        kinematics = params.kinematics
        for steer in PROBE_STEER_RAD:
            rack = kinematics.rack_from_steering(steer)
            values.append(rack)
            for jounce in PROBE_JOUNCE_M:
                values.extend(_numbers(kinematics.at(np.full(4, jounce), rack)))
        # The model evaluation reaches anything the projection hands to it
        # indirectly, such as aero tables read at the current ride height.
        model = create_model(14, params)
        values.extend(model.evaluate(model.initial_state(18.0)).derivative)
    return np.asarray(values, dtype=float)


def _modelica_fingerprint(vehicle: Path) -> tuple[str, frozenset[str]]:
    plan = plan_modelica_stack(vehicle, root=repo_root())
    text = "\n".join(content for _path, content in plan.contents)
    return text, frozenset(item.path for item in plan.unbound)


@pytest.fixture(scope="module")
def baseline(tmp_path_factory) -> tuple[np.ndarray, str]:
    path = tmp_path_factory.mktemp("baseline") / "vehicle.yml"
    path.write_text(yaml.safe_dump(_default_vehicle(), sort_keys=False), encoding="utf-8")
    text, _unbound = _modelica_fingerprint(path)
    return _reduced_fingerprint(path), text


def _dotted(key: str) -> str:
    return key.replace("/", ".")


def _is_unbound(key: str, unbound: frozenset[str]) -> bool:
    names = {_dotted(key)}
    if key in LINKED:
        parent = _dotted(key.rsplit("/", 1)[0])
        names = {f"{parent}.{name}" for name in LINKED[key]}
    return bool(names & unbound)


@pytest.mark.parametrize("key", _input_groups())
def test_vehicle_input_reaches_its_consumers(key: str, baseline, tmp_path: Path) -> None:
    vehicle = _perturbed_vehicle(tmp_path, key)
    if key in CONSTRAINED:
        with pytest.raises(ValueError, match=CONSTRAINED[key]):
            _reduced_fingerprint(vehicle)
        return

    reduced_before, modelica_before = baseline
    text, unbound = _modelica_fingerprint(vehicle)
    if _is_unbound(key, unbound):
        assert text == modelica_before, f"{key} is reported unbound but changed the generated BobLib stack"
    else:
        assert text != modelica_before, (
            f"{key} changed nothing in the generated BobLib stack and is not reported as unbound"
        )

    reduced = _reduced_fingerprint(vehicle)
    changed = reduced.shape != reduced_before.shape or not np.array_equal(reduced, reduced_before)
    if key in REDUCED_IGNORES:
        assert not changed, f"{key} now affects the reduced models; remove it from REDUCED_IGNORES"
    else:
        assert changed, f"{key} has no effect on the reduced models; wire it up or add it to REDUCED_IGNORES"


def test_ignore_lists_name_real_inputs() -> None:
    groups = set(_input_groups())
    assert set(REDUCED_IGNORES) <= groups
    assert set(CONSTRAINED) <= groups
