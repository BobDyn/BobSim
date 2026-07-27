"""FbrcEval: front and rear force-based roll center from the BobLib vehicle model.

The study drives `BobLib.Experiments.Standards.VehicleSim` in its closed-loop
steady-state cornering mode (`vcu.useMode = 3`, the same mode `SteadyStateEval`
uses), sweeping target lateral acceleration. At each settled point it reads the
suspension hardpoint positions and contact-patch tire forces straight out of the
MultiBody model, then reduces them to each axle's force-based roll center with
`_0_Utils.suspension.force_line`.

Why steady-state cornering rather than a rig sweep: the force-based roll center
differs from the kinematic one precisely because the left and right tires carry
*unequal* lateral force. A real cornering solution supplies that asymmetry, at
the true rolled and steered attitude, which is what makes the result force-based.

Theory, derivation, and the investigation findings are in
`docs/superpowers/specs/2026-07-26-fbrc-eval-design.md`.
"""

from __future__ import annotations

import csv
import re
import sys
from pathlib import Path
from typing import Any, cast

import numpy as np
import yaml

from _0_Utils.reporting.report_engine import ReportEngine
from _0_Utils.suspension.force_line import (
    AxleForceBasedRollCenter,
    CornerGeometry,
    solve_axle_fbrc,
    solve_corner_force_line,
)
from _3_StandardSim._modelica_runner import ModelicaRunner


DEFAULT_CONFIG_PATH = Path("_3_StandardSim/FbrcEval/fbrc_eval_config.yml")
REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_VEHICLE_YAML = REPO_ROOT / "vehicle.yml"

STANDARD_GRAVITY = 9.80665
DEG_PER_RAD = 180.0 / np.pi
MM_PER_M = 1000.0

# Instance path of each axle inside VehicleSim.
AXLE_PATHS = {
    "front": "chassis.detailedChassis.frAxleDW",
    "rear": "chassis.detailedChassis.rrAxleDW",
}
SIDES = ("left", "right")

# Per-corner signals read out of the MultiBody model. The contact patch and the
# outboard ball joints move with the suspension, so they must come from the model
# rather than from the static vehicle record.
_CORNER_FRAME_SIGNALS = {
    "contact_patch": "{axle}.{side}CP.r_0",
    "upper_o": "{axle}.{side}WishboneUprightLoop.upperFrame_o.r_0",
    "lower_o": "{axle}.{side}WishboneUprightLoop.lowerFrame_o.r_0",
    "upper_i": "{axle}.{side}WishboneUprightLoop.upperFrame_i.r_0",
    "lower_i": "{axle}.{side}WishboneUprightLoop.lowerFrame_i.r_0",
    "tie_rack": "{axle}.{side}TieRod.frame_a.r_0",
    "tie_o": "{axle}.{side}TieRod.frame_b.r_0",
}

# Contact-patch tire forces. Fy is the quantity the FBRC weights by.
_CORNER_FORCE_SIGNALS = {
    "f_x": "{axle}.{side}Tire.Fx",
    "f_y": "{axle}.{side}Tire.Fy",
    "f_z": "{axle}.{side}Tire.Fz",
}

# The suspension mounting frame for each axle. Every corner position is resolved
# into this frame before the force line is solved, because the FBRC formulation is
# a front-view construction in the vehicle's own y-z plane: `tan(theta)` needs the
# vehicle lateral axis and the centerplane height needs y measured from the
# vehicle centerplane. The raw `r_0` signals are world-frame, and in a cornering
# run the car is tens of metres downrange and yawed, so using them directly is
# wrong. Resolving into the axle frame fixes both at once.
#
# Using each axle's own mount rather than one shared chassis frame matters:
# BobLib's default chassis is FrameCompX, which places a torsional revolute about
# x between the front and rear axle mounts, so the rear axle frame is twisted
# relative to the chassis reference frame under load. The compiled model confirms
# this -- front arm frames alias to chassis.chassisFrame.R.T while rear arm frames
# alias to chassis.detailedChassis.rrAxleFrame.R.T.
#
# These frames are pure translations of the vehicle-definition frame, verified
# against the compiled model: resolved inboard hardpoints are exactly mirror
# symmetric (y_left + y_right = 0 to machine precision) and match vehicle.yml's
# y values to seven digits. That is what makes the axis directions below usable
# without any rotation, and what makes y = 0 the vehicle centerplane.
AXLE_FRAME_PATHS = {
    "front": "chassis.detailedChassis.frAxleFrame",
    "rear": "chassis.detailedChassis.rrAxleFrame",
}

_AXLE_FRAME_POSITION_SIGNAL = "{frame}.r_0"
_AXLE_FRAME_ORIENTATION_SIGNAL = "{frame}.R.T"

_VEHICLE_STATE_SIGNALS = (
    "accY",
    "roll",
    "velX",
    "velY",
    "yawVel",
    "steadyStateConditionsMet",
    "Fz_FL",
    "Fz_FR",
    "Fz_RL",
    "Fz_RR",
)


def _corner_signal_names() -> list[str]:
    names: list[str] = []
    for frame in AXLE_FRAME_PATHS.values():
        names.extend(
            f"{_AXLE_FRAME_POSITION_SIGNAL.format(frame=frame)}[{index}]" for index in (1, 2, 3)
        )
        base = _AXLE_FRAME_ORIENTATION_SIGNAL.format(frame=frame)
        names.extend(f"{base}[{row},{column}]" for row in (1, 2, 3) for column in (1, 2, 3))
    for axle in AXLE_PATHS.values():
        for side in SIDES:
            for template in _CORNER_FRAME_SIGNALS.values():
                base = template.format(axle=axle, side=side)
                names.extend(f"{base}[{index}]" for index in (1, 2, 3))
            for template in _CORNER_FORCE_SIGNALS.values():
                names.append(template.format(axle=axle, side=side))
    return names


FBRC_EVAL_SIGNALS = [
    *_VEHICLE_STATE_SIGNALS,
    *_corner_signal_names(),
]


def _variable_filter_patterns() -> tuple[str, ...]:
    """Grouped `-variableFilter` patterns covering every signal the study reads.

    Enumerating all 178 fully-escaped names produces an ~11 kB command-line
    argument, which risks argument-length limits and is unreadable in run logs.
    These few grouped patterns cover the same set. `-variableFilter` matches whole
    variable names, so the patterns are effectively anchored.

    A test asserts these patterns match every name in `FBRC_EVAL_SIGNALS` and
    nothing obviously unrelated, so the compaction cannot silently drop a signal.
    """
    axles = "|".join(re.escape(path) for path in AXLE_PATHS.values())
    corner = f"({axles})\\.(left|right)"
    frames = "|".join(re.escape(path) for path in AXLE_FRAME_PATHS.values())

    def suffixes(templates: dict[str, str]) -> str:
        return "|".join(
            re.escape(template.format(axle="", side="").lstrip("."))
            for template in templates.values()
        )

    return (
        "|".join(re.escape(name) for name in _VEHICLE_STATE_SIGNALS),
        rf"({frames})\.(r_0\[[1-3]\]|R\.T\[[1-3],[1-3]\])",
        rf"{corner}({suffixes(_CORNER_FRAME_SIGNALS)})\[[1-3]\]",
        rf"{corner}({suffixes(_CORNER_FORCE_SIGNALS)})",
    )


FBRC_EVAL_VARIABLE_FILTER_PATTERNS = _variable_filter_patterns()
FBRC_EVAL_VARIABLE_FILTER = "|".join(FBRC_EVAL_VARIABLE_FILTER_PATTERNS)


def matches_variable_filter(name: str) -> bool:
    """Whether `name` would be emitted under FBRC_EVAL_VARIABLE_FILTER."""
    return any(
        re.fullmatch(pattern, name) for pattern in FBRC_EVAL_VARIABLE_FILTER_PATTERNS
    )


def load_config(path: str | Path) -> dict[str, Any]:
    path = Path(path)
    with path.open("r", encoding="utf-8") as f:
        config = yaml.safe_load(f)

    if config is None:
        raise ValueError(f"Config file is empty: {path}")
    if not isinstance(config, dict):
        raise TypeError(f"Expected YAML config to contain a mapping at top level: {path}")

    return cast(dict[str, Any], config)


def _as_mapping(value: Any, *, name: str) -> dict[str, Any]:
    if value is None:
        return {}
    if not isinstance(value, dict):
        raise TypeError(f"Expected {name} to be a mapping if provided.")
    return cast(dict[str, Any], value)


def _as_float_list(value: Any, *, name: str) -> list[float]:
    if isinstance(value, (int, float)):
        return [float(value)]
    if isinstance(value, (list, tuple, np.ndarray)):
        out = [float(item) for item in value]
        if not out:
            raise ValueError(f"{name} must contain at least one value.")
        return out
    raise TypeError(f"{name} must be a scalar or a sequence of scalars.")


def _float_or_nan(value: Any) -> float:
    if isinstance(value, (list, tuple, np.ndarray)):
        array = np.asarray(value, dtype=float).reshape(-1)
        array = array[np.isfinite(array)]
        return float(array[-1]) if array.size else float("nan")
    try:
        out = float(value)
    except (TypeError, ValueError):
        return float("nan")
    return out if np.isfinite(out) else float("nan")


def _nanmean_or_nan(values: Any) -> float:
    array = np.asarray(values, dtype=float).reshape(-1)
    array = array[np.isfinite(array)]
    return float(np.mean(array)) if array.size else float("nan")


def _linear_slope(x: Any, y: Any) -> float:
    """Least-squares slope of y against x, NaN when underdetermined."""
    x_array = np.asarray(x, dtype=float).reshape(-1)
    y_array = np.asarray(y, dtype=float).reshape(-1)
    size = min(x_array.size, y_array.size)
    x_array, y_array = x_array[:size], y_array[:size]
    finite = np.isfinite(x_array) & np.isfinite(y_array)
    if np.count_nonzero(finite) < 2:
        return float("nan")
    if np.ptp(x_array[finite]) < 1e-12:
        return float("nan")
    return float(np.polyfit(x_array[finite], y_array[finite], 1)[0])


def _metric(name: str, value: Any, units: str, description: str) -> dict[str, Any]:
    return {
        "standard": "FbrcEval",
        "metric": name,
        "value": value,
        "units": units,
        "description": description,
    }


def _vector_signal(result: dict[str, Any], base: str) -> np.ndarray:
    """Read a 3-vector written by OpenModelica as `base[1..3]`."""
    values = []
    for index in (1, 2, 3):
        key = f"{base}[{index}]"
        if key not in result:
            raise KeyError(f"missing signal {key}")
        values.append(_float_or_nan(result[key]))
    vector = np.asarray(values, dtype=float)
    if not np.all(np.isfinite(vector)):
        raise ValueError(f"signal {base} is not finite")
    return vector


def _orientation_matrix(result: dict[str, Any], base: str) -> np.ndarray:
    """Read a Modelica `Frames.Orientation` transformation matrix `base[i,j]`.

    MSL defines `resolve1(R, v) = transpose(R.T) * v` (frame -> world) and
    `resolve2(R, v) = R.T * v` (world -> frame), so `R.T` maps world into the
    local frame and its transpose maps local into world.
    """
    matrix = np.empty((3, 3), dtype=float)
    for row in (1, 2, 3):
        for column in (1, 2, 3):
            key = f"{base}[{row},{column}]"
            if key not in result:
                raise KeyError(f"missing signal {key}")
            matrix[row - 1, column - 1] = _float_or_nan(result[key])
    if not np.all(np.isfinite(matrix)):
        raise ValueError(f"orientation matrix {base} is not finite")
    return matrix


def load_vehicle_axis_directions(
    vehicle_yaml_path: str | Path | None = None,
) -> dict[str, dict[str, np.ndarray]]:
    """Chassis-frame control-arm axis directions for each axle, from vehicle.yml.

    The axis *directions* are rigid in each axle's mounting frame and are not
    published as MultiBody frames, so they are taken from the vehicle definition.
    Because that frame is a pure translation of the vehicle-definition frame, the
    directions need no rotation. Only directions come from here; every position
    comes from the model.
    """
    path = Path(vehicle_yaml_path) if vehicle_yaml_path else DEFAULT_VEHICLE_YAML
    with path.open("r", encoding="utf-8") as f:
        vehicle = yaml.safe_load(f)
    if not isinstance(vehicle, dict):
        raise TypeError(f"Expected a mapping at the top level of {path}")

    directions: dict[str, dict[str, np.ndarray]] = {}
    for axle in AXLE_PATHS:
        section = vehicle.get(axle)
        if not isinstance(section, dict):
            raise ValueError(f"{path}: missing '{axle}' section")
        suspension = section.get("suspension")
        if not isinstance(suspension, dict):
            raise ValueError(f"{path}: missing '{axle}.suspension' section")

        def point(key: str) -> np.ndarray:
            value = suspension.get(key)
            vector = np.asarray(value, dtype=float).reshape(-1)
            if vector.size != 3 or not np.all(np.isfinite(vector)):
                raise ValueError(f"{path}: {axle}.suspension.{key} must be a finite 3-vector")
            return vector

        directions[axle] = {
            "upper": point("upper_fore_i_m") - point("upper_aft_i_m"),
            "lower": point("lower_fore_i_m") - point("lower_aft_i_m"),
        }
    return directions


def _mirror_xz(vector: np.ndarray) -> np.ndarray:
    """Mirror across the XZ plane, matching BobLib's `Vector.mirrorXZ`."""
    return np.array([vector[0], -vector[1], vector[2]], dtype=float)


def build_corner_geometry(
    result: dict[str, Any],
    axle: str,
    side: str,
    axis_directions: dict[str, dict[str, np.ndarray]],
) -> CornerGeometry:
    """Assemble one corner's geometry, resolved into its axle's mounting frame.

    Positions come from MultiBody frames at the live attitude. They are published
    in the world frame, so each is resolved into the axle mounting frame: the FBRC
    is a front-view construction that needs y measured from the vehicle
    centerplane and z along the vehicle vertical, neither of which the world frame
    provides once the car has yawed and travelled downrange.

    The two inboard revolute axis directions are not published as frames, so they
    come from the vehicle record, mirrored for the right side the way BobLib
    mirrors its hardpoints. No rotation is applied: the axle mounting frame is a
    pure translation of the vehicle-definition frame, so record directions are
    already expressed in it.
    """
    axle_path = AXLE_PATHS[axle]
    axle_frame = AXLE_FRAME_PATHS[axle]

    frame_origin = _vector_signal(
        result, _AXLE_FRAME_POSITION_SIGNAL.format(frame=axle_frame)
    )
    # Frames.Orientation.T maps world -> local, so T @ (p_world - origin) is
    # MultiBody's resolve2: the point expressed in the axle frame.
    frame_rotation = _orientation_matrix(
        result, _AXLE_FRAME_ORIENTATION_SIGNAL.format(frame=axle_frame)
    )

    def frame(name: str) -> np.ndarray:
        world = _vector_signal(
            result, _CORNER_FRAME_SIGNALS[name].format(axle=axle_path, side=side)
        )
        return frame_rotation @ (world - frame_origin)

    chassis_directions = axis_directions[axle]

    def axis(name: str) -> np.ndarray:
        direction = np.asarray(chassis_directions[name], dtype=float)
        if side == "right":
            # BobLib mirrors each hardpoint with Vector.mirrorXZ, so the axis --
            # a difference of two mirrored points -- mirrors the same way.
            direction = _mirror_xz(direction)
        magnitude = float(np.linalg.norm(direction))
        if magnitude < 1e-12:
            raise ValueError(f"{axle} {side} {name} arm axis direction is degenerate")
        return direction / magnitude

    return CornerGeometry(
        upper_axis_point=frame("upper_i"),
        upper_axis_direction=axis("upper"),
        lower_axis_point=frame("lower_i"),
        lower_axis_direction=axis("lower"),
        upper_o=frame("upper_o"),
        lower_o=frame("lower_o"),
        tie_rack=frame("tie_rack"),
        tie_o=frame("tie_o"),
        contact_patch=frame("contact_patch"),
    )


def corner_lateral_force(result: dict[str, Any], axle: str, side: str) -> float:
    key = _CORNER_FORCE_SIGNALS["f_y"].format(axle=AXLE_PATHS[axle], side=side)
    if key not in result:
        raise KeyError(f"missing signal {key}")
    value = _float_or_nan(result[key])
    if not np.isfinite(value):
        raise ValueError(f"signal {key} is not finite")
    return value


def solve_axle_from_result(
    result: dict[str, Any],
    axle: str,
    axis_directions: dict[str, dict[str, np.ndarray]],
) -> AxleForceBasedRollCenter:
    """Solve one axle's FBRC from one settled simulation result."""
    lines = {
        side: solve_corner_force_line(
            build_corner_geometry(result, axle, side, axis_directions)
        )
        for side in SIDES
    }
    return solve_axle_fbrc(
        lines["left"],
        lines["right"],
        corner_lateral_force(result, axle, "left"),
        corner_lateral_force(result, axle, "right"),
    )


class FbrcEvalSim:
    def __init__(self, config: dict[str, Any]):
        self.config = config

        sim_cfg = self.config.setdefault("simulation", {})
        sim_cfg.setdefault("variable_filter", FBRC_EVAL_VARIABLE_FILTER)
        backend = sim_cfg.get("backend", "modelica")
        if backend != "modelica":
            raise NotImplementedError(
                "FbrcEvalSim expects simulation.backend='modelica'. Closed-loop "
                "steady-state cornering is owned by VehicleSim useMode=3."
            )

        self.start_time = float(sim_cfg.get("start_time", 0.0))
        self.stop_time = float(sim_cfg.get("stop_time", 30.0))
        self.axis_directions = load_vehicle_axis_directions(
            sim_cfg.get("vehicle_yaml_path")
        )
        self.runner = ModelicaRunner.from_config(self.config)

    def target_ays(self) -> list[float]:
        sweep = _as_mapping(self.config.get("sweep"), name="sweep")
        explicit = sweep.get("targetAys")
        if explicit is not None:
            target_ays = _as_float_list(explicit, name="sweep.targetAys")
        else:
            max_ay = float(sweep.get("maxAy", 8.0))
            step = float(sweep.get("ayStep", 2.0))
            min_ay = float(sweep.get("minAy", step))
            if max_ay <= 0.0 or step <= 0.0 or min_ay <= 0.0:
                raise ValueError("sweep.maxAy, sweep.ayStep and sweep.minAy must be positive.")
            target_ays = [
                float(value) for value in np.arange(min_ay, max_ay + 0.5 * step, step)
            ]
        if not target_ays:
            raise ValueError("FbrcEval target-a_y sweep is empty.")
        return target_ays

    def build_cases(self) -> list[dict[str, Any]]:
        sweep = _as_mapping(self.config.get("sweep"), name="sweep")
        sim_cfg = _as_mapping(self.config.get("simulation"), name="simulation")
        init_parameters = _as_mapping(
            sim_cfg.get("init_parameters"), name="simulation.init_parameters"
        )

        test_vels = _as_float_list(
            sweep.get("testVels", sweep.get("testVel", 15.0)), name="sweep.testVels"
        )

        cases: list[dict[str, Any]] = []
        for test_vel in test_vels:
            for target_ay in self.target_ays():
                case: dict[str, Any] = dict(init_parameters)
                case.update(
                    {
                        "_mode": "closed_loop_steady_ay",
                        "_testVel": float(test_vel),
                        "_testAy": float(target_ay),
                        "useMode": 3,
                        "initialVel": float(test_vel),
                        "targetVel": float(test_vel),
                        "targetAy": float(target_ay),
                        "startTime": self.start_time,
                        "stopTime": self.stop_time,
                    }
                )
                cases.append(case)
        return cases

    def run(self) -> dict[str, Any]:
        results = self.runner.run(
            signals=FBRC_EVAL_SIGNALS,
            mode="last",
            cases=self.build_cases(),
            execution=_as_mapping(self.config.get("execution"), name="execution"),
        )
        return self.summarize(results)

    def _settled(
        self, results: list[dict[str, Any]]
    ) -> tuple[list[dict[str, Any]], list[dict[str, Any]]]:
        settled: list[dict[str, Any]] = []
        rejected: list[dict[str, Any]] = []
        for result in results:
            if result.get("_status") == "failed":
                rejected.append(result)
                continue
            flag = _float_or_nan(result.get("steadyStateConditionsMet", 1.0))
            if np.isfinite(flag) and flag < 0.5:
                skipped = dict(result)
                skipped["_status"] = "failed"
                skipped["_error"] = "closed-loop steady-state conditions were not met"
                rejected.append(skipped)
                continue
            settled.append(result)
        return settled, rejected

    def build_rows(
        self, results: list[dict[str, Any]]
    ) -> tuple[list[dict[str, Any]], list[str]]:
        """One row per settled case, holding both axles' FBRC solutions."""
        rows: list[dict[str, Any]] = []
        warnings: list[str] = []

        for result in results:
            label = str(result.get("_case_label", "unknown"))
            try:
                axles = {
                    axle: solve_axle_from_result(result, axle, self.axis_directions)
                    for axle in AXLE_PATHS
                }
            except (KeyError, ValueError) as exc:
                warnings.append(f"{label}: {exc}")
                continue

            rows.append(
                {
                    "label": label,
                    "velocity": _float_or_nan(result.get("_testVel")),
                    "target_ay": _float_or_nan(result.get("_testAy")),
                    "ay": _float_or_nan(result.get("accY")),
                    "roll": _float_or_nan(result.get("roll")),
                    "axles": axles,
                }
            )

        return rows, warnings

    def _axle_series(self, rows: list[dict[str, Any]], axle: str) -> dict[str, np.ndarray]:
        def column(extract: Any) -> np.ndarray:
            values = []
            for row in rows:
                try:
                    value = extract(row["axles"][axle])
                except (TypeError, ValueError, ZeroDivisionError):
                    value = None
                values.append(float("nan") if value is None else float(value))
            return np.asarray(values, dtype=float)

        prefix = "fr" if axle == "front" else "rr"
        return {
            f"{prefix}_fbrc_height_mm": column(lambda a: a.height) * MM_PER_M,
            f"{prefix}_fbrc_height_above_cp_mm": column(
                lambda a: a.height_above_contact_patch
            )
            * MM_PER_M,
            f"{prefix}_krc_height_mm": column(lambda a: a.kinematic_height) * MM_PER_M,
            # Same datum as *_fbrc_height_above_cp_mm, so the two can be plotted
            # or differenced without a spurious offset equal to the patch height.
            f"{prefix}_krc_height_above_cp_mm": column(
                lambda a: a.kinematic_height_above_contact_patch
            )
            * MM_PER_M,
            f"{prefix}_fbrc_minus_krc_mm": column(lambda a: a.height_minus_kinematic)
            * MM_PER_M,
            f"{prefix}_left_force_line_deg": column(lambda a: a.left.angle_deg),
            f"{prefix}_right_force_line_deg": column(lambda a: a.right.angle_deg),
            f"{prefix}_left_centerplane_height_mm": column(
                lambda a: a.left.centerplane_height
            )
            * MM_PER_M,
            f"{prefix}_right_centerplane_height_mm": column(
                lambda a: a.right.centerplane_height
            )
            * MM_PER_M,
            f"{prefix}_jacking_force_N": column(lambda a: a.jacking_force),
            f"{prefix}_geometric_load_transfer_N": column(
                lambda a: a.geometric_load_transfer
            ),
            f"{prefix}_lateral_force_N": column(lambda a: a.lateral_force),
            f"{prefix}_roll_moment_Nm": column(lambda a: a.roll_moment),
        }

    def _axle_summary(self, rows: list[dict[str, Any]], axle: str) -> dict[str, Any]:
        series = self._axle_series(rows, axle)
        prefix = "fr" if axle == "front" else "rr"
        ay = np.asarray([row["ay"] for row in rows], dtype=float)
        height_mm = series[f"{prefix}_fbrc_height_mm"]

        return {
            f"{axle}_fbrc_height_mm": _nanmean_or_nan(height_mm),
            f"{axle}_fbrc_height_above_cp_mm": _nanmean_or_nan(
                series[f"{prefix}_fbrc_height_above_cp_mm"]
            ),
            f"{axle}_krc_height_mm": _nanmean_or_nan(series[f"{prefix}_krc_height_mm"]),
            f"{axle}_krc_height_above_cp_mm": _nanmean_or_nan(
                series[f"{prefix}_krc_height_above_cp_mm"]
            ),
            f"{axle}_fbrc_minus_krc_mm": _nanmean_or_nan(
                series[f"{prefix}_fbrc_minus_krc_mm"]
            ),
            f"{axle}_fbrc_migration_mm_per_g": _linear_slope(ay, height_mm)
            * STANDARD_GRAVITY,
            f"{axle}_left_force_line_deg": _nanmean_or_nan(
                series[f"{prefix}_left_force_line_deg"]
            ),
            f"{axle}_right_force_line_deg": _nanmean_or_nan(
                series[f"{prefix}_right_force_line_deg"]
            ),
            f"{axle}_jacking_force_N": _nanmean_or_nan(
                series[f"{prefix}_jacking_force_N"]
            ),
            f"{axle}_geometric_load_transfer_N": _nanmean_or_nan(
                series[f"{prefix}_geometric_load_transfer_N"]
            ),
        }

    def summarize(self, results: list[dict[str, Any]]) -> dict[str, Any]:
        if not results:
            raise ValueError("No FbrcEval results to summarize.")

        settled, rejected = self._settled(results)
        rows, warnings = self.build_rows(settled)

        if not rows:
            detail = "; ".join(
                f"{r.get('_case_label', 'unknown')}: {r.get('_error', 'unknown error')}"
                for r in rejected
            )
            raise RuntimeError(
                "No settled FbrcEval cases yielded a force-based roll center. "
                f"Rejected cases: {detail or 'none'}. "
                f"Geometry warnings: {'; '.join(warnings) or 'none'}"
            )

        if rejected:
            print(
                f"Warning: skipped {len(rejected)} failed or unsettled case(s).",
                flush=True,
            )
        for warning in warnings[:6]:
            print(f"Warning: {warning}", flush=True)

        rows = sorted(rows, key=lambda row: (row["velocity"], row["ay"]))

        summary: dict[str, Any] = {
            "n_points": len(rows),
            "ay_min_mps2": float(np.nanmin([row["ay"] for row in rows])),
            "ay_max_mps2": float(np.nanmax([row["ay"] for row in rows])),
            "Ay_range": (
                float(np.nanmin([row["ay"] for row in rows])),
                float(np.nanmax([row["ay"] for row in rows])),
            ),
        }
        for axle in AXLE_PATHS:
            summary.update(self._axle_summary(rows, axle))

        front_height = summary["front_fbrc_height_above_cp_mm"]
        rear_height = summary["rear_fbrc_height_above_cp_mm"]
        summary["roll_axis_front_minus_rear_mm"] = front_height - rear_height

        front_transfer = summary["front_geometric_load_transfer_N"]
        rear_transfer = summary["rear_geometric_load_transfer_N"]
        total_transfer = front_transfer + rear_transfer
        summary["geometric_lltd_front_pct"] = (
            100.0 * front_transfer / total_transfer
            if np.isfinite(total_transfer) and abs(total_transfer) > 1e-9
            else float("nan")
        )

        series: dict[str, Any] = {
            "ay_measured": np.asarray([row["ay"] for row in rows], dtype=float),
            "ay_target": np.asarray([row["target_ay"] for row in rows], dtype=float),
            "roll": np.asarray([row["roll"] for row in rows], dtype=float),
            "velocity": np.asarray([row["velocity"] for row in rows], dtype=float),
        }
        for axle in AXLE_PATHS:
            series.update(self._axle_series(rows, axle))

        metrics = self.build_metrics(summary)
        metrics_csv_path = self.write_metrics_csv(metrics)
        print(f"FbrcEval metrics CSV written: {metrics_csv_path}")

        return {
            "summary": summary,
            "metrics": metrics,
            "metrics_csv_path": metrics_csv_path,
            "series": series,
            "rows": rows,
            "cases": results,
            "failed_cases": rejected,
            "warnings": warnings,
            "n_cases": len(results),
            "n_successful_cases": len(rows),
            "n_failed_cases": len(rejected),
        }

    def build_metrics(self, summary: dict[str, Any]) -> list[dict[str, Any]]:
        metrics: list[dict[str, Any]] = [
            _metric("n_points", summary["n_points"], "count", "Settled operating points used"),
            _metric("ay_min", summary["ay_min_mps2"], "m/s^2", "Minimum measured lateral acceleration"),
            _metric("ay_max", summary["ay_max_mps2"], "m/s^2", "Maximum measured lateral acceleration"),
        ]
        for axle in AXLE_PATHS:
            label = axle.capitalize()
            metrics.extend(
                [
                    _metric(
                        f"{axle}_fbrc_height_mm",
                        summary[f"{axle}_fbrc_height_mm"],
                        "mm",
                        f"{label} force-based roll center height above ground (world z)",
                    ),
                    _metric(
                        f"{axle}_fbrc_height_above_cp_mm",
                        summary[f"{axle}_fbrc_height_above_cp_mm"],
                        "mm",
                        f"{label} FBRC height above the contact-patch plane, the "
                        "moment arm that sets geometric load transfer",
                    ),
                    _metric(
                        f"{axle}_krc_height_mm",
                        summary[f"{axle}_krc_height_mm"],
                        "mm",
                        f"{label} kinematic roll center height, for comparison",
                    ),
                    _metric(
                        f"{axle}_krc_height_above_cp_mm",
                        summary[f"{axle}_krc_height_above_cp_mm"],
                        "mm",
                        f"{label} kinematic roll center height above the "
                        "contact-patch plane, the same datum as the FBRC value",
                    ),
                    _metric(
                        f"{axle}_fbrc_minus_krc_mm",
                        summary[f"{axle}_fbrc_minus_krc_mm"],
                        "mm",
                        f"{label} FBRC minus KRC, i.e. the effect of lateral-force weighting",
                    ),
                    _metric(
                        f"{axle}_fbrc_migration_mm_per_g",
                        summary[f"{axle}_fbrc_migration_mm_per_g"],
                        "mm/g",
                        f"{label} FBRC height migration with lateral acceleration",
                    ),
                    _metric(
                        f"{axle}_left_force_line_deg",
                        summary[f"{axle}_left_force_line_deg"],
                        "deg",
                        f"{label} left force-line (n-line) inclination",
                    ),
                    _metric(
                        f"{axle}_right_force_line_deg",
                        summary[f"{axle}_right_force_line_deg"],
                        "deg",
                        f"{label} right force-line (n-line) inclination",
                    ),
                    _metric(
                        f"{axle}_jacking_force_N",
                        summary[f"{axle}_jacking_force_N"],
                        "N",
                        f"{label} axle jacking force, the sum of link-borne vertical forces",
                    ),
                    _metric(
                        f"{axle}_geometric_load_transfer_N",
                        summary[f"{axle}_geometric_load_transfer_N"],
                        "N",
                        f"{label} geometric load transfer, positive toward the +y wheel",
                    ),
                ]
            )
        metrics.extend(
            [
                _metric(
                    "roll_axis_front_minus_rear_mm",
                    summary["roll_axis_front_minus_rear_mm"],
                    "mm",
                    "Front minus rear FBRC height, the force-based roll axis inclination",
                ),
                _metric(
                    "geometric_lltd_front_pct",
                    summary["geometric_lltd_front_pct"],
                    "%",
                    "Front share of total geometric lateral load transfer",
                ),
            ]
        )
        return metrics

    def write_metrics_csv(self, metrics: list[dict[str, Any]]) -> Path:
        report_cfg = _as_mapping(self.config.get("report"), name="report")
        configured = report_cfg.get("metrics_csv_path")
        if configured is not None:
            metrics_csv_path = Path(configured)
        else:
            report_path = Path(
                report_cfg.get(
                    "output_path",
                    "_3_StandardSim/generated_results/fbrc_eval_report.pdf",
                )
            )
            metrics_csv_path = report_path.with_name(f"{report_path.stem}_metrics.csv")

        metrics_csv_path.parent.mkdir(parents=True, exist_ok=True)
        with metrics_csv_path.open("w", newline="", encoding="utf-8") as f:
            writer = csv.DictWriter(
                f, fieldnames=["standard", "metric", "value", "units", "description"]
            )
            writer.writeheader()
            writer.writerows(metrics)
        return metrics_csv_path


def main(path: str | Path | None = None) -> dict[str, Any]:
    config = load_config(path or DEFAULT_CONFIG_PATH)
    sim_cfg = config.setdefault("simulation", {})
    sim_cfg.setdefault("variable_filter", FBRC_EVAL_VARIABLE_FILTER)

    result = FbrcEvalSim(config).run()

    if _as_mapping(config.get("report"), name="report").get("enabled", True):
        ReportEngine(config).build(result)

    return result


if __name__ == "__main__":
    main(sys.argv[1] if len(sys.argv) > 1 else DEFAULT_CONFIG_PATH)
