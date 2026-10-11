"""Quasi-steady constraints solved on the shared transient equations."""

from __future__ import annotations

from dataclasses import dataclass
from typing import Literal, Mapping

import numpy as np
from numpy.typing import NDArray
from scipy.optimize import least_squares

from engines.dynpy.models import ModelInputs, ModelOutput, ReducedVehicleModel
from engines.dynpy.parameters import G


FloatArray = NDArray[np.float64]


@dataclass(frozen=True)
class QSSResult:
    """A steady circular-running trim point.

    Success requires equation and wheel-force closure within the tire slip fits.
    Workflows separately enforce load, steering and sideslip limits.
    """

    success: bool
    message: str
    residual_norm: float
    state: FloatArray
    inputs: ModelInputs
    output: ModelOutput
    unknowns: Mapping[str, float]
    speed_mps: float
    yaw_rate_radps: float

    @property
    def lateral_acceleration_mps2(self) -> float:
        velocity = self.state[self.output.generalized_acceleration.size :]
        if velocity.size < 3:
            return float("nan")
        u = float(velocity[0])
        yaw_rate = float(velocity[2] if velocity.size == 3 else velocity[5])
        return float(self.output.generalized_acceleration[1] + yaw_rate * u)

    @property
    def longitudinal_acceleration_mps2(self) -> float:
        velocity = self.state[self.output.generalized_acceleration.size :]
        if velocity.size < 3:
            return float("nan")
        v = float(velocity[1])
        yaw_rate = float(velocity[2] if velocity.size == 3 else velocity[5])
        return float(self.output.generalized_acceleration[0] - yaw_rate * v)


def steady_state_residual(
    model: ReducedVehicleModel,
    state: FloatArray,
    inputs: ModelInputs,
) -> FloatArray:
    """Return all generalized accelerations constrained by QSS trim.

    At constant body-frame velocities, suspension positions, unsprung positions,
    and wheel speeds, every generalized acceleration is zero. Centripetal
    acceleration is retained by the body-frame ``omega x velocity`` term in the
    transient equations; it must not be manually added to this residual.
    """

    return model.evaluate(state, inputs).generalized_acceleration.copy()


def solve_steady_state(
    model: ReducedVehicleModel,
    *,
    speed_mps: float,
    yaw_rate_radps: float = 0.0,
    initial_beta_rad: float | None = None,
    initial_steering_rad: float | None = None,
    initial_unknowns: Mapping[str, float] | None = None,
    max_nfev: int = 400,
    tolerance: float = 1e-8,
) -> QSSResult:
    """Solve a constant-speed, constant-radius QSS operating point.

    The unknown set grows with fidelity while the constraint is unchanged:
    all generalized accelerations from the transient model are zero.
    """

    return _solve_trim(
        model,
        speed_mps=speed_mps,
        yaw_rate_radps=yaw_rate_radps,
        target_acceleration_mps2=None,
        initial_beta_rad=initial_beta_rad,
        initial_steering_rad=initial_steering_rad,
        initial_unknowns=initial_unknowns,
        max_nfev=max_nfev,
        tolerance=tolerance,
    )


def solve_acceleration_trim(
    model: ReducedVehicleModel,
    *,
    speed_mps: float,
    longitudinal_acceleration_mps2: float,
    lateral_acceleration_mps2: float,
    yaw_rate_radps: float = 0.0,
    acceleration_frame: Literal["body", "path"] = "body",
    initial_beta_rad: float | None = None,
    initial_steering_rad: float | None = None,
    initial_unknowns: Mapping[str, float] | None = None,
    max_nfev: int = 400,
    tolerance: float = 1e-8,
) -> QSSResult:
    """## Acceleration Trim

    Solve prescribed acceleration using the transient equations.

    Parameters
    ----------
    acceleration_frame : {"body", "path"}, optional
        Body axes by default. Path axes follow the velocity direction, with
        longitudinal acceleration tangent to the path and lateral to its left.
    initial_beta_rad : float, optional
        Initial sideslip. When omitted, use rear-axle rolling geometry.

    Returns
    -------
    QSSResult
        Trim state and convergence diagnostics. Reported accelerations remain
        in body axes.
    """

    return _solve_trim(
        model,
        speed_mps=speed_mps,
        yaw_rate_radps=yaw_rate_radps,
        target_acceleration_mps2=(
            float(longitudinal_acceleration_mps2),
            float(lateral_acceleration_mps2),
        ),
        acceleration_frame=acceleration_frame,
        initial_beta_rad=initial_beta_rad,
        initial_steering_rad=initial_steering_rad,
        initial_unknowns=initial_unknowns,
        max_nfev=max_nfev,
        tolerance=tolerance,
    )


def _solve_trim(
    model: ReducedVehicleModel,
    *,
    speed_mps: float,
    yaw_rate_radps: float,
    target_acceleration_mps2: tuple[float, float] | None,
    initial_beta_rad: float | None,
    initial_steering_rad: float | None,
    initial_unknowns: Mapping[str, float] | None,
    max_nfev: int,
    tolerance: float,
    acceleration_frame: Literal["body", "path"] = "body",
) -> QSSResult:
    if speed_mps <= 0.0:
        raise ValueError("QSS speed must be positive.")
    if acceleration_frame not in ("body", "path"):
        raise ValueError("Acceleration frame must be 'body' or 'path'.")
    rear_x = float(np.mean(model.parameters.corner_positions[2:, 0]))
    beta_guess = (
        float(initial_beta_rad) if initial_beta_rad is not None
        else float(np.arcsin(np.clip(-rear_x * yaw_rate_radps / speed_mps, -1.0, 1.0)))
    )
    wheelbase = model.parameters.wheelbase_m
    steer_guess = (
        float(initial_steering_rad)
        if initial_steering_rad is not None
        else float(np.arctan2(wheelbase * yaw_rate_radps, speed_mps * np.cos(beta_guess)))
    )
    dynamic_pressure = 0.5 * model.parameters.rho_air_kg_m3 * speed_mps**2
    drag_force = dynamic_pressure * model.parameters.cd_area_m2
    mean_radius = float(np.mean(model.parameters.wheel_radius_m))
    torque_guess = drag_force * mean_radius

    names = ["beta_rad", "steering_rad", "total_wheel_torque_nm"]
    guess = [beta_guess, steer_guess, torque_guess]
    lower = [-0.6, -0.7, -20_000.0]
    upper = [0.6, 0.7, 20_000.0]
    if model.dof >= 6:
        names.extend(("heave_m", "roll_rad", "pitch_rad"))
        guess.extend((0.0, 0.0, 0.0))
        lower.extend((-0.20, -0.5, -0.5))
        upper.extend((0.20, 0.5, 0.5))
    if model.dof >= 10:
        names.extend(("slip_fl", "slip_fr", "slip_rl", "slip_rr"))
        guess.extend((0.0, 0.0, 0.0, 0.0))
        lower.extend((-1.0, -1.0, -1.0, -1.0))
        upper.extend((1.0, 1.0, 1.0, 1.0))
    if model.dof == 14:
        names.extend(("unsprung_z_fl_m", "unsprung_z_fr_m", "unsprung_z_rl_m", "unsprung_z_rr_m"))
        guess.extend((0.0, 0.0, 0.0, 0.0))
        lower.extend((-0.20, -0.20, -0.20, -0.20))
        upper.extend((0.20, 0.20, 0.20, 0.20))

    if initial_unknowns is not None:
        for index, name in enumerate(names):
            if name in initial_unknowns:
                guess[index] = float(initial_unknowns[name])

    scales = _residual_scales(model)

    def residual(values: FloatArray) -> FloatArray:
        state, controls = _trim_state_and_inputs(
            model,
            values,
            speed_mps=speed_mps,
            yaw_rate_radps=yaw_rate_radps,
        )
        output = model.evaluate(state, controls)
        acceleration = output.generalized_acceleration.copy()
        if target_acceleration_mps2 is not None:
            acceleration -= _generalized_acceleration_target(
                model,
                state,
                output,
                longitudinal_mps2=target_acceleration_mps2[0],
                lateral_mps2=target_acceleration_mps2[1],
                acceleration_frame=acceleration_frame,
            )
        return acceleration / scales

    lower_array = np.asarray(lower, dtype=float)
    upper_array = np.asarray(upper, dtype=float)
    # The kinematic steer guess can exceed the roadwheel bound in tight, slow
    # corners. That must give an infeasible trim, not an optimizer exception.
    bounded_guess = np.clip(np.asarray(guess, dtype=float), lower_array, upper_array)
    solution = least_squares(  # type: ignore[operator]
        residual,
        bounded_guess,
        # Center differences across near-zero MF52 moment shifts and geometry roundoff.
        jac="3-point",
        bounds=(lower_array, upper_array),
        xtol=tolerance,
        ftol=tolerance,
        gtol=tolerance,
        max_nfev=max_nfev,
        x_scale="jac",
    )
    state, inputs = _trim_state_and_inputs(
        model,
        solution.x,
        speed_mps=speed_mps,
        yaw_rate_radps=yaw_rate_radps,
    )
    output = model.evaluate(state, inputs)
    physical_residual = output.generalized_acceleration.copy()
    if target_acceleration_mps2 is not None:
        physical_residual -= _generalized_acceleration_target(
            model,
            state,
            output,
            longitudinal_mps2=target_acceleration_mps2[0],
            lateral_mps2=target_acceleration_mps2[1],
            acceleration_frame=acceleration_frame,
        )
    physical_norm = float(np.linalg.norm(physical_residual))
    tire_error = _tire_state_error(model, inputs, output)
    return QSSResult(
        success=bool(solution.success and np.linalg.norm(solution.fun) <= 1e-5
                     and not tire_error),
        message=f"{solution.message} {tire_error}".strip(),
        residual_norm=physical_norm,
        state=state,
        inputs=inputs,
        output=output,
        unknowns={name: float(value) for name, value in zip(names, solution.x)},
        speed_mps=float(speed_mps),
        yaw_rate_radps=float(yaw_rate_radps),
    )


def solve_moment_state(
    model: ReducedVehicleModel,
    *,
    speed_mps: float,
    beta_rad: float,
    steering_rad: float,
    yaw_rate_radps: float = 0.0,
    initial_unknowns: Mapping[str, float] | None = None,
    max_nfev: int = 300,
    tolerance: float = 1e-8,
) -> QSSResult:
    """Solve vertical/longitudinal QSS while leaving lateral force and yaw moment free.

    This is the operating condition needed by a yaw-moment diagram: sideslip
    and steer are imposed, heave/roll/pitch and the rotating/unsprung states are
    equilibrated, and lateral acceleration plus yaw moment are outputs.
    """

    if speed_mps <= 0.0:
        raise ValueError("Moment-state speed must be positive.")
    dynamic_pressure = 0.5 * model.parameters.rho_air_kg_m3 * speed_mps**2
    drag_force = dynamic_pressure * model.parameters.cd_area_m2
    torque_guess = drag_force * float(np.mean(model.parameters.wheel_radius_m))
    names = ["total_wheel_torque_nm"]
    guess = [torque_guess]
    lower = [-20_000.0]
    upper = [20_000.0]
    if model.dof >= 6:
        names.extend(("heave_m", "roll_rad", "pitch_rad"))
        guess.extend((0.0, 0.0, 0.0))
        lower.extend((-0.20, -0.5, -0.5))
        upper.extend((0.20, 0.5, 0.5))
    if model.dof >= 10:
        names.extend(("slip_fl", "slip_fr", "slip_rl", "slip_rr"))
        guess.extend((0.0, 0.0, 0.0, 0.0))
        lower.extend((-1.0, -1.0, -1.0, -1.0))
        upper.extend((1.0, 1.0, 1.0, 1.0))
    if model.dof == 14:
        names.extend(("unsprung_z_fl_m", "unsprung_z_fr_m", "unsprung_z_rl_m", "unsprung_z_rr_m"))
        guess.extend((0.0, 0.0, 0.0, 0.0))
        lower.extend((-0.20, -0.20, -0.20, -0.20))
        upper.extend((0.20, 0.20, 0.20, 0.20))

    if initial_unknowns is not None:
        for index, name in enumerate(names):
            if name in initial_unknowns:
                guess[index] = float(initial_unknowns[name])

    def build(values: FloatArray) -> tuple[FloatArray, ModelInputs]:
        full_values = np.empty(model.dof, dtype=float)
        full_values[:3] = (beta_rad, steering_rad, values[0])
        full_values[3:] = values[1:]
        return _trim_state_and_inputs(
            model,
            full_values,
            speed_mps=speed_mps,
            yaw_rate_radps=yaw_rate_radps,
        )

    indices = _moment_state_residual_indices(model)
    scales = _residual_scales(model)[indices]

    def residual(values: FloatArray) -> FloatArray:
        state, controls = build(values)
        return model.evaluate(state, controls).generalized_acceleration[indices] / scales

    solution = least_squares(  # type: ignore[operator]
        residual,
        np.asarray(guess, dtype=float),
        bounds=(np.asarray(lower), np.asarray(upper)),
        xtol=tolerance,
        ftol=tolerance,
        gtol=tolerance,
        max_nfev=max_nfev,
        x_scale="jac",
    )
    state, inputs = build(solution.x)
    output = model.evaluate(state, inputs)
    physical_residual = output.generalized_acceleration[indices]
    tire_error = _tire_state_error(model, inputs, output)
    return QSSResult(
        success=bool(solution.success and np.linalg.norm(solution.fun) <= 1e-5
                     and not tire_error),
        message=f"{solution.message} {tire_error}".strip(),
        residual_norm=float(np.linalg.norm(physical_residual)),
        state=state,
        inputs=inputs,
        output=output,
        unknowns={
            "beta_rad": float(beta_rad),
            "steering_rad": float(steering_rad),
            **{name: float(value) for name, value in zip(names, solution.x)},
        },
        speed_mps=float(speed_mps),
        yaw_rate_radps=float(yaw_rate_radps),
    )


def _trim_state_and_inputs(
    model: ReducedVehicleModel,
    values: FloatArray,
    *,
    speed_mps: float,
    yaw_rate_radps: float,
) -> tuple[FloatArray, ModelInputs]:
    cursor = 0
    beta, steering, total_torque = values[cursor : cursor + 3]
    cursor += 3
    state = model.initial_state(speed_mps)
    coordinates = state[: model.dof]
    velocities = state[model.dof :]
    velocities[0] = speed_mps * np.cos(beta)
    velocities[1] = speed_mps * np.sin(beta)
    if model.dof == 3:
        velocities[2] = yaw_rate_radps
    else:
        velocities[5] = yaw_rate_radps

    if model.dof >= 6:
        coordinates[2:5] = values[cursor : cursor + 3]
        cursor += 3

    if model.dof >= 10:
        slips = np.asarray(values[cursor : cursor + 4], dtype=float)
        cursor += 4
        positions = model.parameters.corner_positions
        body_velocity = velocities[:3]
        body_omega = velocities[3:6]
        corner_velocity = body_velocity + np.cross(
            np.broadcast_to(body_omega, positions.shape), positions
        )
        steering_angles = np.array([steering, steering, 0.0, 0.0])
        longitudinal_speed = (
            corner_velocity[:, 0] * np.cos(steering_angles)
            + corner_velocity[:, 1] * np.sin(steering_angles)
        )
        wheel_speed = longitudinal_speed * (1.0 + slips) / np.asarray(
            model.parameters.wheel_radius_m
        )
        if model.dof == 10:
            velocities[6:10] = wheel_speed
        else:
            velocities[10:14] = wheel_speed

    if model.dof == 14:
        coordinates[6:10] = values[cursor : cursor + 4]

    front_fraction = (
        model.parameters.drive_distribution_front
        if total_torque >= 0.0
        else model.parameters.brake_distribution_front
    )
    torques = total_torque * np.array(
        [front_fraction / 2.0, front_fraction / 2.0, (1.0 - front_fraction) / 2.0, (1.0 - front_fraction) / 2.0]
    )
    return state, ModelInputs(
        steering_rad=float(steering),
        wheel_torques_nm=(
            float(torques[0]),
            float(torques[1]),
            float(torques[2]),
            float(torques[3]),
        ),
    )


def _residual_scales(model: ReducedVehicleModel) -> FloatArray:
    if model.dof == 3:
        return np.array([G, G, 10.0])
    scales = [G, G, G, 10.0, 10.0, 10.0]
    if model.dof == 10:
        scales.extend((500.0, 500.0, 500.0, 500.0))
    elif model.dof == 14:
        scales.extend((G, G, G, G, 500.0, 500.0, 500.0, 500.0))
    return np.asarray(scales, dtype=float)


def _generalized_acceleration_target(
    model: ReducedVehicleModel,
    state: FloatArray,
    output: ModelOutput,
    *,
    longitudinal_mps2: float,
    lateral_mps2: float,
    acceleration_frame: Literal["body", "path"] = "body",
) -> FloatArray:
    velocity = state[model.dof :]
    u = float(velocity[0])
    v = float(velocity[1])
    yaw_rate = float(velocity[2] if model.dof == 3 else velocity[5])
    if acceleration_frame == "path":
        beta = np.arctan2(v, u)
        longitudinal_mps2, lateral_mps2 = (
            longitudinal_mps2 * np.cos(beta) - lateral_mps2 * np.sin(beta),
            longitudinal_mps2 * np.sin(beta) + lateral_mps2 * np.cos(beta),
        )
    target = np.zeros(model.dof, dtype=float)
    target[0] = longitudinal_mps2 + yaw_rate * v
    target[1] = lateral_mps2 - yaw_rate * u
    if model.dof >= 10:
        # With fixed yaw rate and wheel headings, rolling speed changes with
        # body-frame velocity components. Centripetal acceleration rotates the
        # wheel frame without accelerating wheel spin.
        steering = output.toe_rad
        wheel_longitudinal_acceleration = (
            target[0] * np.cos(steering)
            + target[1] * np.sin(steering)
        )
        wheel_acceleration = wheel_longitudinal_acceleration / np.asarray(
            model.parameters.wheel_radius_m
        )
        if model.dof == 10:
            target[6:10] = wheel_acceleration
        else:
            target[10:14] = wheel_acceleration
    return target


def _moment_state_residual_indices(model: ReducedVehicleModel) -> FloatArray:
    if model.dof == 3:
        return np.array([0], dtype=int)
    indices = [0, 2, 3, 4]
    if model.dof == 10:
        indices.extend((6, 7, 8, 9))
    elif model.dof == 14:
        indices.extend((6, 7, 8, 9, 10, 11, 12, 13))
    return np.asarray(indices, dtype=int)


def _wheel_force_balance_valid(
    model: ReducedVehicleModel, inputs: ModelInputs, output: ModelOutput,
) -> bool:
    if model.dof >= 10:
        return True
    headings = output.toe_rad
    forces = output.wheel_forces_body_n
    actual = forces[:, 0]*np.cos(headings)+forces[:, 1]*np.sin(headings)
    requested = (
        np.asarray(inputs.wheel_torques_nm) + output.wheel_moments_tire_nm[:, 1]
    ) / np.asarray(model.parameters.wheel_radius_m)
    return bool(np.allclose(actual, requested, rtol=2e-3, atol=1.0))


def _tire_state_error(
    model: ReducedVehicleModel, inputs: ModelInputs, output: ModelOutput,
) -> str:
    outside = [
        corner for corner, tire, alpha, slip in zip(
            ("FL", "FR", "RL", "RR"), model.parameters.tires,
            output.slip_angles_rad, output.slip_ratios,
        ) if not bool(tire.slip_in_fit_range(alpha, slip))
    ]
    if outside:
        return f"Outside tire slip fit at {', '.join(outside)}."
    if not _wheel_force_balance_valid(model, inputs, output):
        return "Wheel force does not balance applied torque and rolling moment."
    return ""
