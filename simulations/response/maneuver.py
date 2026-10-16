"""Steering inputs shared by the maneuver setup and response runners."""
from __future__ import annotations

from typing import Any
import math


def validate_maneuver(data: dict[str, Any]) -> None:
    """## Maneuver Inputs

    Parameters
    ----------
    data : dict
        Steering waveform, timing and simulation settings.
    """
    if data.get("maneuver") not in {"ramp", "step", "sine"}:
        raise ValueError("Choose ramp, step or sine steering.")
    for key in ("amplitude_deg", "start_time_s", "stop_time_s", "sample_period_s", "speed_mps"):
        if not math.isfinite(float(data[key])):
            raise ValueError(f"{key} must be finite.")
    if not 0 <= data["start_time_s"] < data["stop_time_s"]:
        raise ValueError("Input start must be before simulation end and at or after zero.")
    if not 0 < data["sample_period_s"] <= data["stop_time_s"] or data["speed_mps"] <= 0:
        raise ValueError("Speed and sample period must be positive. Sample period cannot exceed the run duration.")
    key = {"ramp": "ramp_duration_s", "step": "rise_time_s", "sine": "frequency_hz"}[data["maneuver"]]
    value = float(data[key])
    if not math.isfinite(value) or value <= 0:
        raise ValueError(f"{key} must be positive and finite.")
    if data["maneuver"] == "sine" and data["sample_period_s"] * value > .05:
        raise ValueError("Sine steering needs at least 20 output samples per cycle.")


def steering_degrees(time_s: float, data: dict[str, Any]) -> float:
    """## Steering Waveform

    Parameters
    ----------
    time_s : float
        Simulation time in seconds.
    data : dict
        Validated maneuver settings. Amplitude is the change from zero steer.

    Returns
    -------
    float
        Commanded steering angle in degrees.
    """
    elapsed = max(0., time_s - data["start_time_s"])
    if data["maneuver"] == "sine":
        return data["amplitude_deg"] * math.sin(2 * math.pi * data["frequency_hz"] * elapsed)
    duration = data["ramp_duration_s"] if data["maneuver"] == "ramp" else data["rise_time_s"]
    return data["amplitude_deg"] * min(1., elapsed / duration)


def mbd_config(data: dict[str, Any], seed: dict[str, Any]) -> dict[str, Any]:
    """## MBD Maneuver Configuration

    Parameters
    ----------
    data : dict
        Validated maneuver settings in handwheel degrees.
    seed : dict
        Existing transient report and runner configuration.

    Returns
    -------
    dict
        A single-speed transient configuration using existing BobLib inputs.
    """
    from copy import deepcopy
    config = deepcopy(seed)
    config["simulation"]["stop_time"] = data["stop_time_s"]
    config["simulation"]["step_size"] = data["sample_period_s"]
    config["execution"]["parallel"] = False
    config["test"].update(testVel=[data["speed_mps"]], stepTime=data["start_time_s"],
        run_step=True, run_continuous_sine=data["maneuver"] == "sine", directions=["left"],
        steerStep_deg=[data["amplitude_deg"]], representative_step_deg=data["amplitude_deg"],
        stepDuration=data["ramp_duration_s"] if data["maneuver"] == "ramp" else data["rise_time_s"],
        sweep_freq_hz=[data["frequency_hz"]], sweep_amp_deg=[data["amplitude_deg"]],
        representative_cont_freq_hz=data["frequency_hz"], representative_cont_amp_deg=data["amplitude_deg"],
        n_cycles=max(1, int((data["stop_time_s"] - data["start_time_s"]) * data["frequency_hz"])),
        analyze_cycles_after=0)
    config["report"].update(title=f"{data['maneuver'].capitalize()} steering response",
        subtitle="BobLib | MBD | Transient", metric_target_velocity_mps=data["speed_mps"],
        output_path="app/user_data/results/mbd-maneuver/report.pdf", notes=[])
    if data["maneuver"] == "sine":
        config["plots"] = {key: value for key, value in config["plots"].items() if key.startswith("sine")}
    else:
        config["plots"] = {key: value for key, value in config["plots"].items() if key == "step_response"}
    if data["maneuver"] == "ramp":
        config["plots"]["step_response"]["title"] = "Ramp and hold response"
    return config
