"""Static balance of the FourPost rig, measured from executed signals.

The rig has no gravity. On a zero-command row (heave, roll, fx and fy commands
all zero) the contact-patch (CP) loads and the chassis actuator reaction are the
only external loads on an axle, so their force and moment sums must close.
Corner loads are compared with the target sprung corner loads only on
zero-command rows whose neighbors are also zero-command, so damper loads at the
end of a ramp stay out. See docs/four-post-static-balance.md.
"""

from __future__ import annotations

from collections.abc import Mapping, Sequence
from dataclasses import dataclass
from typing import Any

import numpy as np

CLOSURE_REL_TOL = 1e-4
SPRING_REL_TOL = 1e-4
COMMAND_ZERO_TOL = {"heave": 1e-9, "roll": 1e-9, "fx": 1e-6, "fy": 1e-6}
SIDES = ("left", "right")


@dataclass(frozen=True)
class AxleSpec:
    name: str
    knc: str
    axle: str
    actuator: str
    free_length_m: float
    spring_table: np.ndarray
    target_load_n: tuple[float, float]


def corner_signals(axle: str, side: str) -> dict[str, str]:
    cp = f"{axle}.{side}CP"
    return {
        **{f"f{i}": f"{cp}.f[{i}]" for i in (1, 2, 3)},
        **{f"t{i}": f"{cp}.t[{i}]" for i in (1, 2, 3)},
        **{f"r{i}": f"{cp}.r_0[{i}]" for i in (1, 2)},
        "spring": f"{axle}.{side}ShockLinkage.TabularSpring.force.f",
    }


def actuator_signals(actuator: str) -> dict[str, str]:
    loads = f"{actuator}.sprungLoads.frame_a"
    return {
        **{f"f{i}": f"{loads}.f[{i}]" for i in (1, 2, 3)},
        **{f"t{i}": f"{loads}.t[{i}]" for i in (1, 2, 3)},
    }


def executed_signals(axles: Sequence[tuple[str, str]]) -> list[str]:
    """Extra result signals for (axle, actuator) pairs such as ("frAxleDW", "frChassisActuator")."""
    names: list[str] = []
    for axle, actuator in axles:
        for side in SIDES:
            names.extend(corner_signals(axle, side).values())
        names.extend(actuator_signals(actuator).values())
    return names


def _table_value(table: np.ndarray, x: float) -> float:
    xp, fp = table[:, 0], table[:, 1]
    if x <= xp[0]:
        return float(fp[0] + (fp[1] - fp[0]) / (xp[1] - xp[0]) * (x - xp[0]))
    if x >= xp[-1]:
        return float(fp[-1] + (fp[-1] - fp[-2]) / (xp[-1] - xp[-2]) * (x - xp[-1]))
    return float(np.interp(x, xp, fp))


def spring_force(table: Any, free_length_m: float, length_m: float) -> float:
    """BobLib TabularSpring force: the table at the signed deflection, last-two-point extrapolation."""
    return _table_value(np.asarray(table, dtype=float)[:, :2], float(free_length_m) - float(length_m))


def zero_command_rows(result: Mapping[str, Any], kncs: Sequence[str]) -> np.ndarray:
    time = np.asarray(result["time"], dtype=float).reshape(-1)
    rows = np.ones(time.size, dtype=bool)
    for knc in kncs:
        for name, tol in COMMAND_ZERO_TOL.items():
            rows &= np.abs(np.asarray(result[f"{knc}.{name}"], dtype=float).reshape(-1)) <= tol
    return rows


def rate_free_rows(zero_rows: np.ndarray) -> np.ndarray:
    previous = np.r_[True, zero_rows[:-1]]
    following = np.r_[zero_rows[1:], True]
    return zero_rows & previous & following


def _relative(norm: np.ndarray, scale: np.ndarray) -> np.ndarray:
    out = np.where(norm > 0.0, np.inf, 0.0)
    loaded = scale > 0.0
    out[loaded] = norm[loaded] / scale[loaded]
    return out


def _unavailable(reason: str, axles: Sequence[AxleSpec]) -> dict[str, Any]:
    nan = float("nan")
    corner = {
        "contact_fz_n": nan,
        "fz_error_n": nan,
        "fz_error_pct": nan,
        "limit_n": nan,
        "target_ok": None,
        "spring_force_n": nan,
        "spring_force_from_table_n": nan,
        "spring_length_m": nan,
        "spring_residual_n": nan,
    }
    return {
        "status": "unavailable",
        "reason": reason,
        "zero_command_rows": 0,
        "design_rows": 0,
        "closure_pass": None,
        "max_force_residual_n": nan,
        "max_moment_residual_nm": nan,
        "max_relative_residual": nan,
        "worst_time_s": nan,
        "max_abs_fz_error_n": nan,
        "max_abs_fz_error_pct": nan,
        "max_spring_residual_n": nan,
        "axles": {
            axle.name: {
                side: {**corner, "target_load_n": float(target)}
                for side, target in zip(SIDES, axle.target_load_n, strict=True)
            }
            for axle in axles
        },
    }


def evaluate(
    result: Mapping[str, Any],
    axles: Sequence[AxleSpec],
    *,
    target_tol_n: float,
    target_tol_pct: float,
) -> dict[str, Any]:
    """Measured static balance: closure on every zero-command row, corner checks on rate-free rows."""
    needed = ["time"]
    for axle in axles:
        needed += [f"{axle.knc}.{name}" for name in COMMAND_ZERO_TOL]
        needed += [f"{axle.knc}.{side}SpringLength" for side in SIDES]
        needed += executed_signals([(axle.axle, axle.actuator)])
    missing = [name for name in needed if name not in result]
    if missing:
        return _unavailable("missing signal: " + ", ".join(missing), axles)

    time = np.asarray(result["time"], dtype=float).reshape(-1)
    zero_rows = zero_command_rows(result, [axle.knc for axle in axles])
    design_rows = rate_free_rows(zero_rows)
    if not design_rows.any():
        return _unavailable("no zero-command row with zero-command neighbors", axles)

    def signal(name: str) -> np.ndarray:
        return np.asarray(result[name], dtype=float).reshape(-1)

    bad = [name for name in needed if not np.all(np.isfinite(signal(name)[zero_rows]))]
    failures = [f"non-finite sample: {', '.join(bad)}"] if bad else []

    force_norms: list[np.ndarray] = []
    moment_norms: list[np.ndarray] = []
    relatives: list[np.ndarray] = []
    corners: dict[str, dict[str, Any]] = {}
    fz_errors: list[float] = []
    fz_errors_pct: list[float] = []
    spring_residuals: list[float] = []
    targets_ok = True
    springs_ok = True
    for axle in axles:
        chassis = actuator_signals(axle.actuator)
        force_residual = np.column_stack([signal(chassis[f"f{i}"]) for i in (1, 2, 3)])[zero_rows]
        moment_residual = np.column_stack([signal(chassis[f"t{i}"]) for i in (1, 2, 3)])[zero_rows]
        force_scale = np.zeros(int(zero_rows.sum()))
        moment_scale = np.zeros(int(zero_rows.sum()))
        corners[axle.name] = {}
        for side, target in zip(SIDES, axle.target_load_n, strict=True):
            names = corner_signals(axle.axle, side)
            force = np.column_stack([signal(names[f"f{i}"]) for i in (1, 2, 3)])[zero_rows]
            torque = np.column_stack([signal(names[f"t{i}"]) for i in (1, 2, 3)])[zero_rows]
            position = np.column_stack(
                [signal(names["r1"]), signal(names["r2"]), np.zeros(time.size)]
            )[zero_rows]
            force_residual += force
            moment_residual += np.cross(position, force) + torque
            force_scale += np.linalg.norm(force, axis=1)
            moment_scale += np.linalg.norm(position, axis=1) * np.linalg.norm(force, axis=1)
            moment_scale += np.linalg.norm(torque, axis=1)

            contact = float(np.median(signal(names["f3"])[design_rows]))
            spring = signal(names["spring"])[design_rows]
            length = signal(f"{axle.knc}.{side}SpringLength")[design_rows]
            predicted = np.array([spring_force(axle.spring_table, axle.free_length_m, value) for value in length])
            residual = spring - predicted
            worst = int(np.argmax(np.abs(residual)))
            spring_ok = bool(np.all(np.abs(residual) <= SPRING_REL_TOL * np.maximum(np.abs(spring), 1.0)))
            error = contact - float(target)
            error_pct = 100.0 * error / float(target) if target else float("nan")
            limit = max(float(target_tol_n), abs(float(target)) * float(target_tol_pct) / 100.0)
            target_ok = bool(np.isfinite(error) and abs(error) <= limit)
            targets_ok = targets_ok and target_ok
            springs_ok = springs_ok and spring_ok
            fz_errors.append(abs(error))
            fz_errors_pct.append(abs(error_pct))
            spring_residuals.append(abs(float(residual[worst])))
            corners[axle.name][side] = {
                "contact_fz_n": contact,
                "target_load_n": float(target),
                "fz_error_n": error,
                "fz_error_pct": error_pct,
                "limit_n": limit,
                "target_ok": target_ok,
                "spring_force_n": float(np.median(spring)),
                "spring_force_from_table_n": float(predicted[worst]),
                "spring_length_m": float(np.median(length)),
                "spring_residual_n": float(residual[worst]),
            }
        force_norm = np.linalg.norm(force_residual, axis=1)
        moment_norm = np.linalg.norm(moment_residual, axis=1)
        force_norms.append(force_norm)
        moment_norms.append(moment_norm)
        relatives.append(np.maximum(_relative(force_norm, force_scale), _relative(moment_norm, moment_scale)))

    relative = np.max(np.vstack(relatives), axis=0)
    worst_row = int(np.argmax(relative))
    closure_ok = bool(np.all(relative <= CLOSURE_REL_TOL))
    if not closure_ok:
        failures.append(
            f"closure {relative[worst_row]:.2e} of load scale exceeds {CLOSURE_REL_TOL:.0e} "
            f"at t = {time[zero_rows][worst_row]:g} s"
        )
    if not targets_ok:
        failures.append(f"corner load differs from target by {max(fz_errors):.3g} N")
    if not springs_ok:
        failures.append(f"spring force differs from the executed table by {max(spring_residuals):.3g} N")

    return {
        "status": "fail" if failures else "pass",
        "reason": "; ".join(failures),
        "zero_command_rows": int(zero_rows.sum()),
        "design_rows": int(design_rows.sum()),
        "closure_pass": closure_ok,
        "max_force_residual_n": float(np.max(np.vstack(force_norms))),
        "max_moment_residual_nm": float(np.max(np.vstack(moment_norms))),
        "max_relative_residual": float(relative[worst_row]),
        "worst_time_s": float(time[zero_rows][worst_row]),
        "max_abs_fz_error_n": max(fz_errors),
        "max_abs_fz_error_pct": max(fz_errors_pct),
        "max_spring_residual_n": max(spring_residuals),
        "axles": corners,
    }
