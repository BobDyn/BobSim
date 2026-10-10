"""Run discriminating reduced-order maneuvers and overlay every fidelity.

The optional MBD directory contains one CSV per case (for example
``step_steer.csv``).  A reference CSV may use ``time`` or ``time_s`` and any of
the BobLib-compatible channel names emitted by :mod:`engines.dynpy`.
"""

from __future__ import annotations

import argparse
import csv
import json
import os
from dataclasses import dataclass
from pathlib import Path
from typing import Any, Callable, Mapping, cast

os.environ.setdefault("MPLBACKEND", "Agg")
os.environ.setdefault("MPLCONFIGDIR", "temp/matplotlib")

import numpy as np
import pandas as pd

from engines.dynpy import (
    DOFModel,
    ModelInputs,
    TransientResult,
    Vehicle,
    compare_transient_signals,
)
from common.plotting.plot_engine import PlotEngine
from common.vehicle_io import repo_root


FloatArray = np.ndarray[Any, np.dtype[np.float64]]
ControlLaw = Callable[[float, FloatArray], ModelInputs]
MODEL_DOFS: tuple[DOFModel, ...] = (3, 6, 10, 14)
COMMON_SIGNALS = (
    "handwheelAngle",
    "velX",
    "velY",
    "yawVel",
    "sideslip",
    "accX",
    "accY",
    "roll",
    "pitch",
    "z",
)


@dataclass(frozen=True)
class ManeuverCase:
    """One repeatable input chosen to separate model assumptions."""

    name: str
    description: str
    exposes: str
    speed_mps: float
    stop_time_s: float
    sample_period_s: float
    controls: Callable[[tuple[float, float, float, float], float], ControlLaw]


def default_cases() -> tuple[ManeuverCase, ...]:
    """Return the standard fidelity-discrimination matrix."""

    return (
        ManeuverCase(
            name="step_steer",
            description="5 deg roadwheel step at 15 m/s",
            exposes="yaw response plus sprung-body roll buildup",
            speed_mps=15.0,
            stop_time_s=5.0,
            sample_period_s=0.01,
            controls=_step_steer_controls,
        ),
        ManeuverCase(
            name="slalom",
            description="3 deg, 1.2 Hz roadwheel sine at 15 m/s",
            exposes="frequency response, phase, and transient load transfer",
            speed_mps=15.0,
            stop_time_s=6.0,
            sample_period_s=0.01,
            controls=_slalom_controls,
        ),
        ManeuverCase(
            name="brake_in_turn",
            description="2 deg steer followed by 80 Nm/corner braking at 15 m/s",
            exposes="combined slip, pitch transfer, and wheel rotational dynamics",
            speed_mps=15.0,
            stop_time_s=4.0,
            sample_period_s=0.01,
            controls=_brake_in_turn_controls,
        ),
        ManeuverCase(
            name="four_wheel_bump",
            description="20 mm half-cosine axle bumps at 12 m/s",
            exposes="tire vertical compliance, unsprung motion, and wheel hop",
            speed_mps=12.0,
            stop_time_s=3.0,
            sample_period_s=0.002,
            controls=_four_wheel_bump_controls,
        ),
    )


def run_fidelity_suite(
    *,
    output_directory: str | Path = "temp/fidelity_validation",
    mbd_directory: str | Path | None = None,
    vehicle_path: str | Path | None = None,
    case_names: set[str] | None = None,
) -> dict[str, Any]:
    """Run every reduced fidelity and render optional MBD comparisons."""

    root = repo_root()
    output = _root_path(root, output_directory)
    output.mkdir(parents=True, exist_ok=True)
    mbd = _root_path(root, mbd_directory) if mbd_directory is not None else None
    vehicle = Vehicle.from_yaml(vehicle_path)
    parameters = vehicle.parameters
    cases = tuple(
        case for case in default_cases() if case_names is None or case.name in case_names
    )
    if not cases:
        raise ValueError("No fidelity comparison cases were selected.")

    manifest: dict[str, Any] = {"reference": "MBD (BobLib)", "cases": {}}
    all_metrics: dict[str, Any] = {}
    for case in cases:
        case_output = output / case.name
        case_output.mkdir(parents=True, exist_ok=True)
        results: dict[str, TransientResult] = {}
        for dof in MODEL_DOFS:
            trim = vehicle.steady_state(dof, speed_mps=case.speed_mps)
            if not trim.success:
                raise RuntimeError(
                    f"Could not initialize {dof}DOF {case.name}: {trim.message}"
                )
            controls = case.controls(trim.inputs.wheel_torques_nm, parameters.wheelbase_m)
            time = np.arange(
                0.0,
                case.stop_time_s + 0.5 * case.sample_period_s,
                case.sample_period_s,
            )
            result = vehicle.simulate(
                dof,
                initial_state=trim.state,
                controls=controls,
                time_s=time,
                method="Radau" if dof >= 6 else "RK45",
                rtol=2e-5,
                atol=2e-7,
            )
            if not result.success:
                raise RuntimeError(f"{dof}DOF {case.name} failed: {result.message}")
            results[f"{dof}DOF"] = result
            _write_result_csv(case_output / f"{dof}dof.csv", result, controls)

        reference_path = mbd / f"{case.name}.csv" if mbd is not None else None
        reference = (
            _load_reference_csv(reference_path)
            if reference_path is not None and reference_path.exists()
            else None
        )
        _write_case_plots(case_output / "overlays", case, results, reference)
        metrics = _comparison_metrics(results, reference)
        if metrics:
            (case_output / "mbd_metrics.json").write_text(
                json.dumps(metrics, indent=2, sort_keys=True) + "\n",
                encoding="utf-8",
            )
            all_metrics[case.name] = metrics
        manifest["cases"][case.name] = {
            "description": case.description,
            "exposes": case.exposes,
            "speed_mps": case.speed_mps,
            "mbd_csv": reference_path.as_posix() if reference_path is not None else None,
            "mbd_loaded": reference is not None,
        }

    (output / "case_manifest.json").write_text(
        json.dumps(manifest, indent=2, sort_keys=True) + "\n",
        encoding="utf-8",
    )
    if all_metrics:
        (output / "mbd_metrics.json").write_text(
            json.dumps(all_metrics, indent=2, sort_keys=True) + "\n",
            encoding="utf-8",
        )
    return manifest


def _step_steer_controls(
    trim_torques: tuple[float, float, float, float],
    wheelbase_m: float,
) -> ControlLaw:
    del wheelbase_m

    def controls(time_s: float, _state: FloatArray) -> ModelInputs:
        fraction = np.clip((time_s - 1.0) / 0.02, 0.0, 1.0)
        return ModelInputs(
            steering_rad=float(fraction * np.deg2rad(5.0)),
            wheel_torques_nm=trim_torques,
        )

    return controls


def _slalom_controls(
    trim_torques: tuple[float, float, float, float],
    wheelbase_m: float,
) -> ControlLaw:
    del wheelbase_m

    def controls(time_s: float, _state: FloatArray) -> ModelInputs:
        active_time = max(time_s - 0.75, 0.0)
        ramp = float(np.clip(active_time / 0.25, 0.0, 1.0))
        steering = ramp * np.deg2rad(3.0) * np.sin(2.0 * np.pi * 1.2 * active_time)
        return ModelInputs(steering_rad=float(steering), wheel_torques_nm=trim_torques)

    return controls


def _brake_in_turn_controls(
    trim_torques: tuple[float, float, float, float],
    wheelbase_m: float,
) -> ControlLaw:
    del wheelbase_m

    def controls(time_s: float, _state: FloatArray) -> ModelInputs:
        steer = np.clip((time_s - 0.5) / 0.1, 0.0, 1.0) * np.deg2rad(2.0)
        brake = np.clip((time_s - 1.5) / 0.1, 0.0, 1.0)
        torques = (1.0 - brake) * np.asarray(trim_torques) - brake * 80.0
        return ModelInputs(
            steering_rad=float(steer),
            wheel_torques_nm=cast(tuple[float, float, float, float], tuple(torques)),
        )

    return controls


def _four_wheel_bump_controls(
    trim_torques: tuple[float, float, float, float],
    wheelbase_m: float,
) -> ControlLaw:
    speed_mps = 12.0
    rear_delay = wheelbase_m / speed_mps

    def pulse(time_s: float, start_s: float) -> tuple[float, float]:
        duration = 0.12
        phase = (time_s - start_s) / duration
        if phase < 0.0 or phase > 1.0:
            return 0.0, 0.0
        height = 0.01 * (1.0 - np.cos(2.0 * np.pi * phase))
        speed = 0.02 * np.pi / duration * np.sin(2.0 * np.pi * phase)
        return float(height), float(speed)

    def controls(time_s: float, _state: FloatArray) -> ModelInputs:
        front_height, front_speed = pulse(time_s, 1.0)
        rear_height, rear_speed = pulse(time_s, 1.0 + rear_delay)
        return ModelInputs(
            wheel_torques_nm=trim_torques,
            road_heights_m=(front_height, front_height, rear_height, rear_height),
            road_vertical_speeds_mps=(front_speed, front_speed, rear_speed, rear_speed),
        )

    return controls


def _write_result_csv(
    path: Path,
    result: TransientResult,
    controls: ControlLaw,
) -> None:
    signal_names = tuple(name for name in COMMON_SIGNALS if name in result.signals)
    state_lookup = {name: index for index, name in enumerate(result.state_names)}
    extra_states = tuple(
        name
        for name in result.state_names
        if name.startswith(("wheel_speed_", "unsprung_z_", "unsprung_speed_"))
    )
    columns = ("time_s",) + signal_names + extra_states
    with path.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.writer(handle)
        writer.writerow(columns)
        for index, time_s in enumerate(result.time_s):
            # Re-evaluate controls so input-driven plots can be reconstructed from CSV.
            controls(float(time_s), result.state[index])
            values: list[float] = [float(time_s)]
            values.extend(float(result.signals[name][index]) for name in signal_names)
            values.extend(float(result.state[index, state_lookup[name]]) for name in extra_states)
            writer.writerow(values)


def _load_reference_csv(path: Path) -> tuple[FloatArray, dict[str, FloatArray]]:
    frame = pd.read_csv(path)
    time_name = "time_s" if "time_s" in frame else "time"
    if time_name not in frame:
        raise KeyError(f"MBD reference has no time/time_s column: {path}")
    signals = {
        name: frame[name].to_numpy(dtype=float)
        for name in COMMON_SIGNALS
        if name in frame
    }
    return frame[time_name].to_numpy(dtype=float), signals


def _comparison_metrics(
    results: Mapping[str, TransientResult],
    reference: tuple[FloatArray, dict[str, FloatArray]] | None,
) -> dict[str, Any]:
    if reference is None:
        return {}
    time_s, signals = reference
    return {
        name: compare_transient_signals(time_s, signals, result)
        for name, result in results.items()
    }


def _write_case_plots(
    output: Path,
    case: ManeuverCase,
    results: Mapping[str, TransientResult],
    reference: tuple[FloatArray, dict[str, FloatArray]] | None,
) -> None:
    series: dict[str, FloatArray] = {}
    labels = list(results)
    for label, result in results.items():
        prefix = label.lower()
        series[f"{prefix}_time"] = result.time_s
        for signal, values in result.signals.items():
            series[f"{prefix}_{signal}"] = np.asarray(values, dtype=float)
    if reference is not None:
        reference_time, reference_signals = reference
        labels.append("MBD (BobLib)")
        series["mbd_time"] = reference_time
        for signal, values in reference_signals.items():
            series[f"mbd_{signal}"] = values

    plots = {
        "lateral_response": {
            "layout": "quad",
            "title": f"{case.description}: all-fidelity overlay",
            "subplots": tuple(
                _overlay_signal(series, labels, signal, title, y_label)
                for signal, title, y_label in (
                    ("handwheelAngle", "Roadwheel steer", "Steer (rad)"),
                    ("accY", "Lateral acceleration", "ay (m/s²)"),
                    ("yawVel", "Yaw rate", "Yaw rate (rad/s)"),
                    ("roll", "Body roll", "Roll (rad)"),
                )
            ),
        },
        "longitudinal_attitude": {
            "layout": "quad",
            "title": f"{case.description}: longitudinal/attitude overlay",
            "subplots": tuple(
                _overlay_signal(series, labels, signal, title, y_label)
                for signal, title, y_label in (
                    ("velX", "Longitudinal speed", "Speed (m/s)"),
                    ("accX", "Longitudinal acceleration", "ax (m/s²)"),
                    ("pitch", "Body pitch", "Pitch (rad)"),
                    ("z", "Body heave", "z (m)"),
                )
            ),
        },
        "added_states": {
            "layout": "quad",
            "title": f"{case.description}: states added by 10/14DOF",
            "subplots": tuple(
                _overlay_signal(series, labels, signal, title, y_label)
                for signal, title, y_label in (
                    ("wheel_speed_fl", "Front-left wheel speed", "Wheel speed (rad/s)"),
                    ("wheel_speed_rr", "Rear-right wheel speed", "Wheel speed (rad/s)"),
                    ("unsprung_z_fl", "Front-left unsprung position", "z unsprung (m)"),
                    ("unsprung_z_rr", "Rear-right unsprung position", "z unsprung (m)"),
                )
            ),
        },
    }
    PlotEngine({"plots": plots}).save_pngs({"series": series}, output)

    if reference is None:
        return
    reference_time, reference_signals = reference
    residual_series: dict[str, FloatArray] = {"reference_time": reference_time}
    residual_labels = list(results)
    for label, result in results.items():
        prefix = label.lower()
        for signal, reference_values in reference_signals.items():
            if signal in result.signals:
                predicted = np.interp(reference_time, result.time_s, result.signals[signal])
                residual_series[f"{prefix}_{signal}"] = predicted - reference_values
    residual_plots = {
        "mbd_residuals": {
            "layout": "quad",
            "title": f"{case.description}: reduced model minus MBD",
            "subplots": tuple(
                _residual_signal(residual_series, residual_labels, signal, title, y_label)
                for signal, title, y_label in (
                    ("accY", "Lateral acceleration error", "Δay (m/s²)"),
                    ("yawVel", "Yaw-rate error", "Δyaw rate (rad/s)"),
                    ("roll", "Roll error", "Δroll (rad)"),
                    ("velX", "Speed error", "Δspeed (m/s)"),
                )
            ),
        }
    }
    PlotEngine({"plots": residual_plots}).save_pngs(
        {"series": residual_series}, output
    )


def _overlay_signal(
    series: Mapping[str, FloatArray],
    labels: list[str],
    signal: str,
    title: str,
    y_label: str,
) -> dict[str, Any]:
    items = []
    for label in labels:
        prefix = "mbd" if label.startswith("MBD") else label.lower()
        if f"{prefix}_{signal}" not in series:
            continue
        items.append(
            {
                "x": {"key": f"{prefix}_time", "label": "Time (s)"},
                "y": {"key": f"{prefix}_{signal}", "label": y_label},
                "label": label,
                "linewidth": 2.5 if prefix == "mbd" else 1.5,
                "linestyle": "--" if prefix == "mbd" else "-",
            }
        )
    if not items:
        return {
            "title": title,
            "x": {"key": next(iter(series)), "label": "Time (s)"},
            "y": {"key": next(iter(series)), "label": y_label},
            "max_abs": 0.0,
        }
    first, *overlays = items
    return {"title": title, **first, "overlay": overlays}


def _residual_signal(
    series: Mapping[str, FloatArray],
    labels: list[str],
    signal: str,
    title: str,
    y_label: str,
) -> dict[str, Any]:
    items = []
    for label in labels:
        prefix = label.lower()
        key = f"{prefix}_{signal}"
        if key in series:
            items.append(
                {
                    "x": {"key": "reference_time", "label": "Time (s)"},
                    "y": {"key": key, "label": y_label},
                    "label": label,
                }
            )
    if not items:
        key = next(iter(series))
        return {
            "title": title,
            "x": {"key": key, "label": "Time (s)"},
            "y": {"key": key, "label": y_label},
            "max_abs": 0.0,
        }
    first, *overlays = items
    return {"title": title, **first, "overlay": overlays}


def _root_path(root: Path, value: str | Path) -> Path:
    path = Path(value)
    return path if path.is_absolute() else root / path


def _parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path, default=Path("temp/fidelity_validation"))
    parser.add_argument("--mbd-directory", type=Path)
    parser.add_argument("--vehicle", type=Path)
    parser.add_argument("--case", action="append", choices=tuple(case.name for case in default_cases()))
    return parser.parse_args()


def main() -> None:
    args = _parse_args()
    manifest = run_fidelity_suite(
        output_directory=args.output,
        mbd_directory=args.mbd_directory,
        vehicle_path=args.vehicle,
        case_names=set(args.case) if args.case else None,
    )
    print(json.dumps(manifest, indent=2, sort_keys=True))


if __name__ == "__main__":
    main()
