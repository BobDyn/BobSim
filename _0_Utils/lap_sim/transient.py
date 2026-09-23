"""Forward-transient lap simulation following a QSS racing line and speed target."""

from __future__ import annotations

from dataclasses import dataclass

import numpy as np
from numpy.typing import NDArray

from _0_Utils.dyn_py import (
    ModelInputs,
    TransientResult,
    VehicleDynamicsSystem,
    simulate_transient,
    solve_steady_state,
)
from _0_Utils.lap_sim.qss import QSSLapResult


FloatArray = NDArray[np.float64]


@dataclass(frozen=True)
class TransientLapResult:
    """Transient history plus track-relative progress and error channels."""

    transient: TransientResult
    qss_reference: QSSLapResult
    station_m: FloatArray
    unwrapped_progress_m: FloatArray
    lateral_error_m: FloatArray
    heading_error_rad: FloatArray
    target_speed_mps: FloatArray
    completed_lap: bool
    lap_time_s: float


def simulate_transient_lap(
    model: VehicleDynamicsSystem,
    qss_lap: QSSLapResult,
    *,
    sample_period_s: float = 0.02,
    stop_time_s: float | None = None,
    lookahead_m: float = 5.0,
    speed_gain_per_s: float = 1.5,
    heading_gain: float = 0.9,
    cross_track_gain_per_s: float = 1.5,
    steering_trim_step_m: float = 5.0,
    maximum_acceleration_mps2: float = 6.0,
    maximum_braking_mps2: float = 14.0,
    integration_rtol: float = 1e-5,
    integration_atol: float = 1e-7,
) -> TransientLapResult:
    """Follow a QSS optimum with feedforward plus stabilizing feedback controls."""

    line = qss_lap.line
    requested_initial_speed = max(float(qss_lap.speed_mps[0]), 1.0)
    curvature = float(line.curvature_per_m[0])
    trim = None
    # An interpolated GGV speed can sit on or just past the feasibility boundary.
    # Search inward for a valid equilibrium.
    for speed_factor in (1.0, 0.98, 0.95, 0.90, 0.80, 0.70, 0.60):
        initial_speed = max(speed_factor * requested_initial_speed, 1.0)
        initial_yaw_rate = initial_speed * curvature
        candidate = solve_steady_state(
            model,
            speed_mps=initial_speed,
            yaw_rate_radps=initial_yaw_rate,
            initial_steering_rad=float(
                np.arctan(model.parameters.wheelbase_m * curvature)
            ),
        )
        if candidate.success:
            trim = candidate
            break
    if trim is None:
        raise RuntimeError(
            "Could not initialize transient lap from a sub-limit QSS trim."
        )
    initial_state = trim.state.copy()
    initial_state[0] = line.x_m[0]
    initial_state[1] = line.y_m[0]
    initial_state[2 if model.dof == 3 else 5] = line.heading_rad[0]

    horizon = (
        float(stop_time_s)
        if stop_time_s is not None
        else max(1.35 * qss_lap.lap_time_s, qss_lap.lap_time_s + 5.0)
    )
    if horizon <= 0.0 or sample_period_s <= 0.0:
        raise ValueError("Transient lap time horizon and sample period must be positive.")

    max_steering = 0.65
    steering_feedforward = _steady_steering_profile(
        model,
        qss_lap,
        sample_step_m=steering_trim_step_m,
        initial_steering_rad=float(trim.inputs.steering_rad),
    )

    def controls(_time_s: float, state: FloatArray) -> ModelInputs:
        x_m, y_m = float(state[0]), float(state[1])
        station = line.project_station_m(x_m, y_m)
        preview_station = station + lookahead_m
        yaw = float(state[2 if model.dof == 3 else 5])
        heading_error = _wrap_angle(line.heading_at_station(station) - yaw)
        lateral_error = line.lateral_error_at_station(x_m, y_m, station)
        velocity = state[model.dof :]
        speed = max(float(np.hypot(velocity[0], velocity[1])), 0.1)

        feedforward_steer = line.interpolate(
            steering_feedforward,
            preview_station,
        )
        steering = (
            feedforward_steer
            + heading_gain * heading_error
            - np.arctan2(cross_track_gain_per_s * lateral_error, speed)
        )
        steering = float(np.clip(steering, -max_steering, max_steering))

        target_speed = line.interpolate(qss_lap.speed_mps, preview_station)
        feedforward_ax = line.interpolate(
            qss_lap.longitudinal_acceleration_mps2,
            station,
        )
        acceleration = feedforward_ax + speed_gain_per_s * (target_speed - speed)
        acceleration = float(
            np.clip(acceleration, -maximum_braking_mps2, maximum_acceleration_mps2)
        )
        dynamic_pressure = 0.5 * model.parameters.rho_air_kg_m3 * speed**2
        drag = dynamic_pressure * model.parameters.cd_area_m2
        requested_force = model.parameters.mass_kg * acceleration + drag
        if requested_force >= 0.0:
            if speed > model.parameters.maximum_drive_speed_mps:
                drive_force_limit = 0.0
            else:
                drive_force_limit = min(
                    model.parameters.peak_drive_force_n,
                    model.parameters.peak_drive_power_w / max(speed, 1.0),
                )
            total_force = min(requested_force, drive_force_limit)
        else:
            total_force = requested_force
        front_fraction = (
            model.parameters.drive_distribution_front
            if total_force >= 0.0
            else model.parameters.brake_distribution_front
        )
        wheel_forces = total_force * np.array(
            [
                front_fraction / 2.0,
                front_fraction / 2.0,
                (1.0 - front_fraction) / 2.0,
                (1.0 - front_fraction) / 2.0,
            ]
        )
        torques = wheel_forces * np.asarray(model.parameters.wheel_radius_m)
        return ModelInputs(
            steering_rad=steering,
            wheel_torques_nm=tuple(float(value) for value in torques),  # type: ignore[arg-type]
        )

    evaluation_time = np.arange(0.0, horizon + 0.5 * sample_period_s, sample_period_s)
    transient = simulate_transient(
        model,
        initial_state=initial_state,
        controls=controls,
        time_s=evaluation_time,
        method="Radau" if model.dof >= 6 else "RK45",
        rtol=integration_rtol,
        atol=integration_atol,
    )
    count = transient.time_s.size
    station = np.empty(count)
    lateral_error = np.empty(count)
    heading_error = np.empty(count)
    target_speed = np.empty(count)
    for index, state in enumerate(transient.state):
        station[index] = line.project_station_m(float(state[0]), float(state[1]))
        lateral_error[index] = line.lateral_error_at_station(
            float(state[0]),
            float(state[1]),
            station[index],
        )
        yaw = float(state[2 if model.dof == 3 else 5])
        heading_error[index] = _wrap_angle(line.heading_at_station(station[index]) - yaw)
        target_speed[index] = line.interpolate(qss_lap.speed_mps, station[index])

    station_delta = np.diff(station)
    length = line.track_length_m
    wrapped_delta = (station_delta + 0.5 * length) % length - 0.5 * length
    progress = np.concatenate(([0.0], np.cumsum(wrapped_delta)))
    completion_indices = np.flatnonzero(progress >= length)
    completed = bool(completion_indices.size)
    if completed:
        finish = int(completion_indices[0])
        prior = max(finish - 1, 0)
        progress_span = progress[finish] - progress[prior]
        fraction = (
            (length - progress[prior]) / progress_span if abs(progress_span) > 1e-12 else 1.0
        )
        lap_time = float(
            transient.time_s[prior]
            + fraction * (transient.time_s[finish] - transient.time_s[prior])
        )
    else:
        lap_time = float("nan")
    return TransientLapResult(
        transient=transient,
        qss_reference=qss_lap,
        station_m=station,
        unwrapped_progress_m=progress,
        lateral_error_m=lateral_error,
        heading_error_rad=heading_error,
        target_speed_mps=target_speed,
        completed_lap=completed,
        lap_time_s=lap_time,
    )


def _wrap_angle(angle_rad: float) -> float:
    return float((angle_rad + np.pi) % (2.0 * np.pi) - np.pi)


def _steady_steering_profile(
    model: VehicleDynamicsSystem,
    qss_lap: QSSLapResult,
    *,
    sample_step_m: float,
    initial_steering_rad: float,
) -> FloatArray:
    """Interpolate sparse QSS roadwheel trims into steering feedforward."""

    if sample_step_m <= 0.0:
        raise ValueError("steering_trim_step_m must be positive.")
    line = qss_lap.line
    nominal_ds = float(np.median(line.segment_length_m))
    stride = max(1, int(np.ceil(sample_step_m / max(nominal_ds, 1e-9))))
    indices = np.arange(0, line.station_m.size, stride, dtype=int)
    station = line.station_m[indices]
    steering = np.empty(indices.size)
    beta_guess = 0.0
    steer_guess = initial_steering_rad
    for cursor, index in enumerate(indices):
        speed = float(qss_lap.speed_mps[index])
        curvature = float(line.curvature_per_m[index])
        candidate = solve_steady_state(
            model,
            speed_mps=speed,
            yaw_rate_radps=speed * curvature,
            initial_beta_rad=beta_guess,
            initial_steering_rad=steer_guess,
            max_nfev=250,
            tolerance=1e-7,
        )
        beta = float(candidate.unknowns["beta_rad"])
        roadwheel = float(candidate.unknowns["steering_rad"])
        is_racing_root = (
            candidate.success
            and abs(beta) <= 0.30
            and (abs(curvature) <= 1e-9 or roadwheel * curvature >= 0.0)
        )
        if is_racing_root:
            beta_guess = beta
            steer_guess = roadwheel
        else:
            roadwheel = float(
                np.arctan(model.parameters.wheelbase_m * curvature)
            )
        steering[cursor] = roadwheel

    periodic_station = np.concatenate((station, [line.track_length_m]))
    periodic_steering = np.concatenate((steering, [steering[0]]))
    return np.asarray(
        np.interp(line.station_m, periodic_station, periodic_steering),
        dtype=float,
    )
