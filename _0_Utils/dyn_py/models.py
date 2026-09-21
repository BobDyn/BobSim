"""Nested reduced-order vehicle models.

:class:`VehicleDynamicsSystem` holds the force assembly shared by all fidelities.
Each subclass adds physics to its parent::

    VehicleModel3DOF   planar body motion
      -> VehicleModel6DOF   + heave, roll, pitch, suspension
        -> VehicleModel10DOF  + four rotating wheels
          -> VehicleModel14DOF  + four unsprung vertical masses
"""

from __future__ import annotations

from abc import ABC, abstractmethod
from dataclasses import dataclass, field
from typing import ClassVar, Literal

import numpy as np
from numpy.typing import ArrayLike, NDArray

from _0_Utils.dyn_py.parameters import G, ReducedVehicleParameters
from _0_Utils.dyn_py.kinematics import VehicleKinematicState


FloatArray = NDArray[np.float64]
DOFModel = Literal[3, 6, 10, 14]


@dataclass(frozen=True)
class ModelInputs:
    """Driver and road inputs, ordered FL, FR, RL, RR where applicable."""

    steering_rad: float = 0.0
    wheel_torques_nm: tuple[float, float, float, float] = (0.0, 0.0, 0.0, 0.0)
    road_heights_m: tuple[float, float, float, float] = (0.0, 0.0, 0.0, 0.0)
    road_vertical_speeds_mps: tuple[float, float, float, float] = (0.0, 0.0, 0.0, 0.0)


@dataclass(frozen=True)
class ModelOutput:
    derivative: FloatArray
    generalized_acceleration: FloatArray
    body_force_n: FloatArray
    body_moment_nm: FloatArray
    wheel_forces_body_n: FloatArray
    normal_loads_n: FloatArray
    slip_angles_rad: FloatArray
    slip_ratios: FloatArray
    suspension_forces_n: FloatArray
    geometric_vertical_forces_n: FloatArray
    algebraic_load_transfer_n: FloatArray
    jounce_m: FloatArray
    jounce_speed_mps: FloatArray
    contact_patch_positions_body_m: FloatArray
    contact_patch_tangents: FloatArray
    wheel_center_offsets_m: FloatArray
    camber_rad: FloatArray
    toe_rad: FloatArray
    caster_rad: FloatArray
    kpi_rad: FloatArray
    mechanical_trail_m: FloatArray
    scrub_radius_m: FloatArray
    instant_link_coefficients: FloatArray


@dataclass(frozen=True)
class VerticalForceState:
    """Corner vertical state passed into the dynamic instant-link closure."""

    normal_loads_n: FloatArray
    suspension_forces_n: FloatArray
    unsprung_acceleration_mps2: FloatArray
    jounce_m: FloatArray
    jounce_speed_mps: FloatArray


@dataclass
class VehicleDynamicsSystem(ABC):
    """Dynamic system shared by transient integration and QSS constraint solvers."""

    parameters: ReducedVehicleParameters
    dof: ClassVar[DOFModel]
    coordinate_names: ClassVar[tuple[str, ...]]
    velocity_names: ClassVar[tuple[str, ...]]
    added_physics: ClassVar[str]
    _force_path_iterations: ClassVar[int] = 1
    _last_output: ModelOutput | None = field(default=None, init=False, repr=False)

    @property
    def state_size(self) -> int:
        return 2 * self.dof

    @property
    def state_names(self) -> tuple[str, ...]:
        return self.coordinate_names + self.velocity_names

    def initial_state(self, speed_mps: float = 0.0) -> FloatArray:
        state = np.zeros(self.state_size, dtype=float)
        velocity = state[self.dof :]
        velocity[0] = float(speed_mps)
        self._initialize_added_velocities(velocity, speed_mps)
        return state

    def _initialize_added_velocities(
        self,
        velocities: FloatArray,
        speed_mps: float,
    ) -> None:
        """Initialize fidelity-specific rates; planar/body models add none."""

    def derivative(self, time_s: float, state: ArrayLike, inputs: ModelInputs) -> FloatArray:
        del time_s
        return self.evaluate(state, inputs).derivative

    def evaluate(self, state: ArrayLike, inputs: ModelInputs = ModelInputs()) -> ModelOutput:
        x = np.asarray(state, dtype=float)
        if x.shape != (self.state_size,):
            raise ValueError(
                f"{self.dof}DOF state must have shape ({self.state_size},), got {x.shape}."
            )
        if not np.all(np.isfinite(x)):
            raise ValueError("Vehicle state contains non-finite values.")

        coordinates = x[: self.dof]
        velocities = x[self.dof :]
        body_coordinates, body_velocities = self._body_state(coordinates, velocities)
        rotation = _body_to_world_rotation(body_coordinates[3:6])
        vertical = self._vertical_forces(
            coordinates,
            velocities,
            body_coordinates,
            body_velocities,
            rotation,
            inputs,
        )
        kinematics = self.parameters.kinematics.at(vertical.jounce_m)
        corner_positions = (
            self.parameters.corner_positions + kinematics.contact_patch_offsets_m
        )
        rigid_corner_velocities = body_velocities[:3] + np.cross(
            np.broadcast_to(body_velocities[3:6], corner_positions.shape),
            corner_positions,
        )
        articulation_velocities = (
            kinematics.contact_patch_tangents * vertical.jounce_speed_mps[:, None]
        )
        corner_velocities = rigid_corner_velocities + articulation_velocities

        steering = np.array(
            [inputs.steering_rad, inputs.steering_rad, 0.0, 0.0],
            dtype=float,
        ) + kinematics.toe_rad
        cos_delta = np.cos(steering)
        sin_delta = np.sin(steering)
        wheel_longitudinal_speed = (
            corner_velocities[:, 0] * cos_delta + corner_velocities[:, 1] * sin_delta
        )
        wheel_lateral_speed = (
            -corner_velocities[:, 0] * sin_delta + corner_velocities[:, 1] * cos_delta
        )
        slip_angles = -np.arctan2(
            wheel_lateral_speed,
            np.maximum(np.abs(wheel_longitudinal_speed), 0.25),
        )

        normal_loads = np.maximum(vertical.normal_loads_n, 0.0)
        suspension_forces = vertical.suspension_forces_n
        unsprung_accel = vertical.unsprung_acceleration_mps2
        wheel_speeds = self._wheel_speeds(velocities, wheel_longitudinal_speed)
        radii = np.asarray(self.parameters.wheel_radius_m, dtype=float)
        slip_denominator = np.maximum(np.abs(wheel_longitudinal_speed), 1.0)
        slip_ratios = (radii * wheel_speeds - wheel_longitudinal_speed) / slip_denominator

        # 6/10DOF uprights are massless, so tire load depends on tire force
        # through the instant links. Iterate to close that loop.
        for _iteration in range(self._force_path_iterations):
            fx_tire, fy_tire = self._tire_forces(
                normal_loads,
                slip_angles,
                slip_ratios,
                kinematics.camber_rad,
                inputs,
            )
            fx_body = fx_tire * cos_delta - fy_tire * sin_delta
            fy_body = fx_tire * sin_delta + fy_tire * cos_delta
            geometric_vertical = self._geometric_vertical_forces(
                fx_body,
                fy_body,
                kinematics,
            )
            algebraic_load_transfer = self._algebraic_load_transfer(
                fx_body,
                fy_body,
            )
            closed_loads = np.maximum(
                self._closed_normal_loads(
                    normal_loads,
                    suspension_forces,
                    geometric_vertical,
                    algebraic_load_transfer,
                ),
                0.0,
            )
            if np.allclose(closed_loads, normal_loads, rtol=1e-9, atol=1e-9):
                normal_loads = closed_loads
                break
            normal_loads = closed_loads

        # Recompute at the final load so forces stay consistent if the loop hits its cap.
        fx_tire, fy_tire = self._tire_forces(
            normal_loads,
            slip_angles,
            slip_ratios,
            kinematics.camber_rad,
            inputs,
        )
        fx_body = fx_tire * cos_delta - fy_tire * sin_delta
        fy_body = fx_tire * sin_delta + fy_tire * cos_delta
        geometric_vertical = self._geometric_vertical_forces(
            fx_body,
            fy_body,
            kinematics,
        )
        algebraic_load_transfer = self._algebraic_load_transfer(
            fx_body,
            fy_body,
        )
        unsprung_accel = self._unsprung_acceleration_with_geometry(
            unsprung_accel,
            geometric_vertical,
        )
        wheel_forces_body = np.column_stack((fx_body, fy_body, normal_loads))
        body_wheel_forces = self._forces_transmitted_to_body(
            wheel_forces_body,
            suspension_forces,
            geometric_vertical,
        )

        body_mass, body_inertia = self._body_mass_properties()
        gravity_body = self._gravity_force_body(rotation, body_mass)
        aero_force, aero_moment = self._aero_load(body_velocities)
        body_force = np.sum(body_wheel_forces, axis=0) + gravity_body + aero_force
        body_moment = (
            np.sum(np.cross(corner_positions, body_wheel_forces), axis=0) + aero_moment
        )

        omega = body_velocities[3:6]
        body_linear_accel = (
            body_force / self._body_translational_masses(body_mass)
            - np.cross(omega, body_velocities[:3])
        )
        body_angular_accel = np.linalg.solve(
            body_inertia,
            body_moment - np.cross(omega, body_inertia @ omega),
        )
        body_accel = np.concatenate((body_linear_accel, body_angular_accel))

        generalized_acceleration = self._generalized_acceleration(
            body_accel,
            velocities,
            wheel_speeds,
            fx_tire,
            unsprung_accel,
            inputs,
        )
        coordinate_derivative = self._coordinate_derivative(
            coordinates,
            velocities,
            body_coordinates,
            body_velocities,
            rotation,
        )
        derivative = np.concatenate((coordinate_derivative, generalized_acceleration))
        output = ModelOutput(
            derivative=derivative,
            generalized_acceleration=generalized_acceleration,
            body_force_n=body_force,
            body_moment_nm=body_moment,
            wheel_forces_body_n=wheel_forces_body,
            normal_loads_n=normal_loads,
            slip_angles_rad=slip_angles,
            slip_ratios=slip_ratios,
            suspension_forces_n=suspension_forces,
            geometric_vertical_forces_n=geometric_vertical,
            algebraic_load_transfer_n=algebraic_load_transfer,
            jounce_m=kinematics.jounce_m,
            jounce_speed_mps=vertical.jounce_speed_mps,
            contact_patch_positions_body_m=corner_positions,
            contact_patch_tangents=kinematics.contact_patch_tangents,
            wheel_center_offsets_m=kinematics.wheel_center_offsets_m,
            camber_rad=kinematics.camber_rad,
            toe_rad=kinematics.toe_rad,
            caster_rad=kinematics.caster_rad,
            kpi_rad=kinematics.kpi_rad,
            mechanical_trail_m=kinematics.mechanical_trail_m,
            scrub_radius_m=kinematics.scrub_radius_m,
            instant_link_coefficients=kinematics.instant_links.coefficient_matrix,
        )
        self._last_output = output
        return output

    @abstractmethod
    def _body_state(
        self,
        coordinates: FloatArray,
        velocities: FloatArray,
    ) -> tuple[FloatArray, FloatArray]:
        """Project this model's state into 6DOF body coordinates and rates."""

    def _wheel_speeds(
        self,
        velocities: FloatArray,
        wheel_longitudinal_speed: FloatArray,
    ) -> FloatArray:
        """Return rolling speeds when wheel rotation is not an independent DOF."""

        del velocities
        return wheel_longitudinal_speed / np.asarray(self.parameters.wheel_radius_m)

    @abstractmethod
    def _longitudinal_tire_force(
        self,
        normal_loads: FloatArray,
        slip_ratios: FloatArray,
        force_capacity: FloatArray,
        inputs: ModelInputs,
    ) -> FloatArray:
        """Resolve longitudinal force using this fidelity's wheel model."""

    def _tire_forces(
        self,
        normal_loads: FloatArray,
        slip_angles: FloatArray,
        slip_ratios: FloatArray,
        camber_rad: FloatArray,
        inputs: ModelInputs,
    ) -> tuple[FloatArray, FloatArray]:
        """Evaluate smooth combined-slip forces in each steered wheel frame."""

        tire = self.parameters.tire
        fx_capacity = tire.mu_x(normal_loads) * normal_loads
        fy_capacity = tire.mu_y(normal_loads, camber_rad) * normal_loads
        fy_tire = fy_capacity * np.tanh(
            tire.cornering_stiffness(normal_loads, camber_rad) * slip_angles
            / np.maximum(fy_capacity, 1.0)
        )
        fy_tire += tire.camber_thrust(normal_loads, camber_rad)
        fx_tire = self._longitudinal_tire_force(
            normal_loads,
            slip_ratios,
            fx_capacity,
            inputs,
        )
        usage = np.sqrt(
            (fx_tire / np.maximum(fx_capacity, 1.0)) ** 2
            + (fy_tire / np.maximum(fy_capacity, 1.0)) ** 2
        )
        combined_scale = np.maximum(usage, 1.0)
        return fx_tire / combined_scale, fy_tire / combined_scale

    def _geometric_vertical_forces(
        self,
        fx_body: FloatArray,
        fy_body: FloatArray,
        kinematics: VehicleKinematicState,
    ) -> FloatArray:
        """Return instant-link jacking forces; the planar model has none."""

        del fx_body, fy_body, kinematics
        return np.zeros(4)

    def _closed_normal_loads(
        self,
        normal_loads: FloatArray,
        suspension_forces: FloatArray,
        geometric_vertical: FloatArray,
        algebraic_load_transfer: FloatArray,
    ) -> FloatArray:
        """Close an algebraic upright force balance when the fidelity has one."""

        del suspension_forces, geometric_vertical, algebraic_load_transfer
        return normal_loads

    def _algebraic_load_transfer(
        self,
        fx_body: FloatArray,
        fy_body: FloatArray,
    ) -> FloatArray:
        """Return planar pitch/roll load transfer when suspension DOFs are absent."""

        del fx_body, fy_body
        return np.zeros(4)

    def _unsprung_acceleration_with_geometry(
        self,
        unsprung_accel: FloatArray,
        geometric_vertical: FloatArray,
    ) -> FloatArray:
        """Apply instant-link reaction to explicit unsprung vertical states."""

        del geometric_vertical
        return unsprung_accel

    @abstractmethod
    def _vertical_forces(
        self,
        coordinates: FloatArray,
        velocities: FloatArray,
        body_coordinates: FloatArray,
        body_velocities: FloatArray,
        rotation: FloatArray,
        inputs: ModelInputs,
    ) -> VerticalForceState:
        """Return tire loads, suspension loads, unsprung acceleration, and jounce."""

    def _suspension_kinematics(
        self,
        body_coordinates: FloatArray,
        body_velocities: FloatArray,
        rotation: FloatArray,
    ) -> tuple[FloatArray, FloatArray]:
        """Return corner vertical displacement and speed from rigid-body pose."""

        corner_positions = self.parameters.corner_positions
        rotated_positions = (rotation @ corner_positions.T).T
        corner_world_z = body_coordinates[2] + rotated_positions[:, 2]
        nominal_corner_z = corner_positions[:, 2]
        corner_vertical_displacement = corner_world_z - nominal_corner_z
        corner_velocity_body = body_velocities[:3] + np.cross(
            np.broadcast_to(body_velocities[3:6], corner_positions.shape),
            corner_positions,
        )
        corner_vertical_speed = (rotation @ corner_velocity_body.T).T[:, 2]
        return corner_vertical_displacement, corner_vertical_speed

    def _suspension_force_from_compression(
        self,
        compression: FloatArray,
        compression_speed: FloatArray,
        spring_preload: FloatArray,
    ) -> FloatArray:
        """Apply linearized wheel rates, damping, and anti-roll coupling."""

        spring_rates = np.asarray(self.parameters.suspension_stiffness_n_per_m)
        damper_rates = np.asarray(self.parameters.suspension_damping_n_s_per_m)
        suspension_forces = (
            spring_preload + spring_rates * compression + damper_rates * compression_speed
        )
        suspension_forces += self._antiroll_forces(compression)
        return suspension_forces

    def _body_mass_properties(self) -> tuple[float, FloatArray]:
        """Use total vehicle properties until unsprung masses become independent."""

        return self.parameters.mass_kg, self.parameters.inertia

    def _body_translational_masses(self, body_mass: float) -> FloatArray:
        return np.full(3, body_mass, dtype=float)

    def _gravity_force_body(
        self,
        rotation: FloatArray,
        body_mass: float,
    ) -> FloatArray:
        return rotation.T @ np.array([0.0, 0.0, -body_mass * G])

    def _forces_transmitted_to_body(
        self,
        wheel_forces_body: FloatArray,
        suspension_forces: FloatArray,
        geometric_vertical: FloatArray,
    ) -> FloatArray:
        """Without unsprung DOFs, contact-patch forces act directly on the body."""

        del suspension_forces, geometric_vertical
        return wheel_forces_body.copy()

    def _antiroll_forces(self, compression: FloatArray) -> FloatArray:
        forces = np.zeros(4, dtype=float)
        tracks = (self.parameters.track_front_m, self.parameters.track_rear_m)
        for axle, (left, right) in enumerate(((0, 1), (2, 3))):
            track = tracks[axle]
            stiffness = self.parameters.antiroll_stiffness_nm_per_rad[axle]
            delta_force = stiffness * (compression[left] - compression[right]) / track**2
            forces[left] += delta_force
            forces[right] -= delta_force
        return forces

    def _aero_downforce(self, speed_mps: float) -> float:
        return 0.5 * self.parameters.rho_air_kg_m3 * speed_mps**2 * self.parameters.cl_area_m2

    def _aero_load(self, body_velocities: FloatArray) -> tuple[FloatArray, FloatArray]:
        horizontal = body_velocities[:2]
        speed = float(np.linalg.norm(horizontal))
        dynamic_pressure = 0.5 * self.parameters.rho_air_kg_m3 * speed**2
        drag_force = np.zeros(3, dtype=float)
        if speed > 1e-9:
            drag_force[:2] = (
                -dynamic_pressure * self.parameters.cd_area_m2 * horizontal / speed
            )
        downforce = dynamic_pressure * self.parameters.cl_area_m2
        downforce_force = np.array([0.0, 0.0, -downforce], dtype=float)
        force = drag_force + downforce_force

        # Drag stays at the CFD reference point. Only the downforce CoP absorbs
        # the tabulated free pitch moment.
        moment = np.cross(
            np.asarray(self.parameters.aero_cop_m, dtype=float),
            downforce_force,
        ) + np.cross(
            np.asarray(self.parameters.aero_drag_application_m, dtype=float),
            drag_force,
        )
        return force, moment

    @abstractmethod
    def _generalized_acceleration(
        self,
        body_accel: FloatArray,
        velocities: FloatArray,
        wheel_speeds: FloatArray,
        fx_tire: FloatArray,
        unsprung_accel: FloatArray,
        inputs: ModelInputs,
    ) -> FloatArray:
        """Pack body, wheel, and unsprung accelerations in model state order."""

    def _wheel_angular_acceleration(
        self,
        fx_tire: FloatArray,
        inputs: ModelInputs,
    ) -> FloatArray:
        """Apply J*omega_dot = drive torque - tire reaction torque."""

        wheel_torque = np.asarray(inputs.wheel_torques_nm, dtype=float)
        wheel_radius = np.asarray(self.parameters.wheel_radius_m)
        wheel_inertia = np.asarray(self.parameters.wheel_inertia_kg_m2)
        return (wheel_torque - fx_tire * wheel_radius) / wheel_inertia

    @abstractmethod
    def _coordinate_derivative(
        self,
        coordinates: FloatArray,
        velocities: FloatArray,
        body_coordinates: FloatArray,
        body_velocities: FloatArray,
        rotation: FloatArray,
    ) -> FloatArray:
        """Map body-frame velocities into generalized-coordinate rates."""

    def _six_dof_coordinate_derivative(
        self,
        body_coordinates: FloatArray,
        body_velocities: FloatArray,
        rotation: FloatArray,
    ) -> FloatArray:
        """Return world translation and Euler-angle rates for the rigid body."""

        body_coordinate_rate = np.empty(6, dtype=float)
        body_coordinate_rate[:3] = rotation @ body_velocities[:3]
        body_coordinate_rate[3:6] = _euler_rates(
            body_coordinates[3],
            body_coordinates[4],
            body_velocities[3:6],
        )
        return body_coordinate_rate


class VehicleModel3DOF(VehicleDynamicsSystem):
    """Planar body model: longitudinal, lateral, and yaw motion.

    State order::

        q     = [x, y, yaw]
        qdot* = [u, v, yaw_rate]  # body-frame u/v

    Vertical loads are algebraic: static weight, the full aerodynamic wrench,
    and quasi-static longitudinal/lateral load transfer.
    Wheel torque is converted directly to a friction-limited longitudinal force.
    """

    dof: ClassVar[DOFModel] = 3
    coordinate_names: ClassVar[tuple[str, ...]] = ("x", "y", "yaw")
    velocity_names: ClassVar[tuple[str, ...]] = ("u", "v", "yaw_rate")
    added_physics: ClassVar[str] = "planar longitudinal, lateral, and yaw motion"
    _force_path_iterations: ClassVar[int] = 12

    def _body_state(
        self,
        coordinates: FloatArray,
        velocities: FloatArray,
    ) -> tuple[FloatArray, FloatArray]:
        body_coordinates = np.array(
            [coordinates[0], coordinates[1], 0.0, 0.0, 0.0, coordinates[2]],
            dtype=float,
        )
        body_velocities = np.array(
            [velocities[0], velocities[1], 0.0, 0.0, 0.0, velocities[2]],
            dtype=float,
        )
        return body_coordinates, body_velocities

    def _longitudinal_tire_force(
        self,
        normal_loads: FloatArray,
        slip_ratios: FloatArray,
        force_capacity: FloatArray,
        inputs: ModelInputs,
    ) -> FloatArray:
        """Use Fx = torque/radius, limited by the tire's available friction."""

        del normal_loads, slip_ratios
        torque = np.asarray(inputs.wheel_torques_nm, dtype=float)
        radii = np.asarray(self.parameters.wheel_radius_m, dtype=float)
        return np.clip(torque / radii, -force_capacity, force_capacity)

    def _vertical_forces(
        self,
        coordinates: FloatArray,
        velocities: FloatArray,
        body_coordinates: FloatArray,
        body_velocities: FloatArray,
        rotation: FloatArray,
        inputs: ModelInputs,
    ) -> VerticalForceState:
        """Distribute weight and the full aero wrench to the four contact patches."""

        del coordinates, velocities, body_coordinates, rotation, inputs
        static_loads = np.asarray(self.parameters.static_wheel_loads_n, dtype=float)
        aero_force, aero_moment = self._aero_load(body_velocities)
        downforce = -float(aero_force[2])
        positions = self.parameters.corner_positions
        front_x = float(np.mean(positions[:2, 0]))
        rear_x = float(np.mean(positions[2:, 0]))
        wheelbase = front_x - rear_x
        front_aero = (-rear_x * downforce + aero_moment[1]) / wheelbase
        rear_aero = downforce - front_aero
        loads = static_loads + np.array(
            [front_aero / 2.0, front_aero / 2.0, rear_aero / 2.0, rear_aero / 2.0]
        )

        # Aero roll moment uses the same roll-stiffness split as tire-force transfer.
        front_share = self._front_roll_stiffness_fraction()
        loads += self._roll_moment_load_transfer(
            float(aero_moment[0]),
            front_share,
        )
        return VerticalForceState(
            loads,
            loads.copy(),
            np.zeros(4),
            np.zeros(4),
            np.zeros(4),
        )

    def _algebraic_load_transfer(
        self,
        fx_body: FloatArray,
        fy_body: FloatArray,
    ) -> FloatArray:
        """Close planar pitch and roll moments with contact-patch reactions."""

        positions = self.parameters.corner_positions
        front_x = float(np.mean(positions[:2, 0]))
        rear_x = float(np.mean(positions[2:, 0]))
        wheelbase = front_x - rear_x

        # r x F gives My = z*Fx. Axle vertical reactions balance it.
        horizontal_pitch_moment = float(np.sum(positions[:, 2] * fx_body))
        front_delta = horizontal_pitch_moment / wheelbase
        pitch_transfer = np.array(
            [front_delta / 2.0, front_delta / 2.0, -front_delta / 2.0, -front_delta / 2.0]
        )

        # Tire lateral force gives Mx = -z*Fy. Roll stiffness splits the reaction by axle.
        horizontal_roll_moment = float(np.sum(-positions[:, 2] * fy_body))
        roll_transfer = self._roll_moment_load_transfer(
            horizontal_roll_moment,
            self._front_roll_stiffness_fraction(),
        )
        return pitch_transfer + roll_transfer

    def _front_roll_stiffness_fraction(self) -> float:
        spring_rates = np.asarray(self.parameters.suspension_stiffness_n_per_m)
        front_spring = 0.25 * float(np.sum(spring_rates[:2])) * self.parameters.track_front_m**2
        rear_spring = 0.25 * float(np.sum(spring_rates[2:])) * self.parameters.track_rear_m**2
        front_total = front_spring + self.parameters.antiroll_stiffness_nm_per_rad[0]
        rear_total = rear_spring + self.parameters.antiroll_stiffness_nm_per_rad[1]
        total = front_total + rear_total
        return front_total / total if total > 0.0 else 0.5

    def _roll_moment_load_transfer(
        self,
        external_roll_moment_nm: float,
        front_fraction: float,
    ) -> FloatArray:
        front_left_delta = (
            -front_fraction * external_roll_moment_nm / self.parameters.track_front_m
        )
        rear_left_delta = (
            -(1.0 - front_fraction)
            * external_roll_moment_nm
            / self.parameters.track_rear_m
        )
        return np.array(
            [front_left_delta, -front_left_delta, rear_left_delta, -rear_left_delta]
        )

    def _closed_normal_loads(
        self,
        normal_loads: FloatArray,
        suspension_forces: FloatArray,
        geometric_vertical: FloatArray,
        algebraic_load_transfer: FloatArray,
    ) -> FloatArray:
        del normal_loads, geometric_vertical
        return suspension_forces + algebraic_load_transfer

    def _generalized_acceleration(
        self,
        body_accel: FloatArray,
        velocities: FloatArray,
        wheel_speeds: FloatArray,
        fx_tire: FloatArray,
        unsprung_accel: FloatArray,
        inputs: ModelInputs,
    ) -> FloatArray:
        del velocities, wheel_speeds, fx_tire, unsprung_accel, inputs
        return body_accel[[0, 1, 5]]

    def _coordinate_derivative(
        self,
        coordinates: FloatArray,
        velocities: FloatArray,
        body_coordinates: FloatArray,
        body_velocities: FloatArray,
        rotation: FloatArray,
    ) -> FloatArray:
        del body_coordinates, body_velocities, rotation
        yaw = coordinates[2]
        cosine = np.cos(yaw)
        sine = np.sin(yaw)
        return np.array(
            [
                cosine * velocities[0] - sine * velocities[1],
                sine * velocities[0] + cosine * velocities[1],
                velocities[2],
            ]
        )


class VehicleModel6DOF(VehicleModel3DOF):
    """Release rigid-body heave, roll, and pitch plus suspension load transfer.

    State order::

        q     = [x, y, z, roll, pitch, yaw]
        qdot* = [u, v, w, roll_rate, pitch_rate, yaw_rate]

    Linearized corner springs, dampers, and anti-roll bars act between the body
    and an algebraically fixed road plane. Wheel rotation remains kinematic.
    """

    dof: ClassVar[DOFModel] = 6
    coordinate_names: ClassVar[tuple[str, ...]] = (
        "x",
        "y",
        "z",
        "roll",
        "pitch",
        "yaw",
    )
    velocity_names: ClassVar[tuple[str, ...]] = (
        "u",
        "v",
        "w",
        "roll_rate",
        "pitch_rate",
        "yaw_rate",
    )
    added_physics: ClassVar[str] = "heave, roll, pitch, suspension, and aero pitch"
    _force_path_iterations: ClassVar[int] = 12

    def _body_state(
        self,
        coordinates: FloatArray,
        velocities: FloatArray,
    ) -> tuple[FloatArray, FloatArray]:
        return coordinates[:6], velocities[:6]

    def _vertical_forces(
        self,
        coordinates: FloatArray,
        velocities: FloatArray,
        body_coordinates: FloatArray,
        body_velocities: FloatArray,
        rotation: FloatArray,
        inputs: ModelInputs,
    ) -> VerticalForceState:
        """Resolve body-to-ground spring/damper/anti-roll load transfer."""

        del coordinates, velocities, inputs
        displacement, speed = self._suspension_kinematics(
            body_coordinates,
            body_velocities,
            rotation,
        )
        static_loads = np.asarray(self.parameters.static_wheel_loads_n, dtype=float)
        compression = -displacement
        suspension_forces = self._suspension_force_from_compression(
            compression=compression,
            compression_speed=-speed,
            spring_preload=static_loads,
        )
        return VerticalForceState(
            suspension_forces.copy(),
            suspension_forces,
            np.zeros(4),
            compression,
            -speed,
        )

    def _geometric_vertical_forces(
        self,
        fx_body: FloatArray,
        fy_body: FloatArray,
        kinematics: VehicleKinematicState,
    ) -> FloatArray:
        """Transmit tire forces through nominal double-wishbone instant links."""

        return kinematics.instant_links.geometric_vertical_forces(fx_body, fy_body)

    def _closed_normal_loads(
        self,
        normal_loads: FloatArray,
        suspension_forces: FloatArray,
        geometric_vertical: FloatArray,
        algebraic_load_transfer: FloatArray,
    ) -> FloatArray:
        """Massless upright balance: tire Fz = elastic Fz + geometric Fz."""

        del normal_loads, algebraic_load_transfer
        return suspension_forces + geometric_vertical

    def _generalized_acceleration(
        self,
        body_accel: FloatArray,
        velocities: FloatArray,
        wheel_speeds: FloatArray,
        fx_tire: FloatArray,
        unsprung_accel: FloatArray,
        inputs: ModelInputs,
    ) -> FloatArray:
        del velocities, wheel_speeds, fx_tire, unsprung_accel, inputs
        return body_accel

    def _coordinate_derivative(
        self,
        coordinates: FloatArray,
        velocities: FloatArray,
        body_coordinates: FloatArray,
        body_velocities: FloatArray,
        rotation: FloatArray,
    ) -> FloatArray:
        del coordinates, velocities
        return self._six_dof_coordinate_derivative(
            body_coordinates,
            body_velocities,
            rotation,
        )


class VehicleModel10DOF(VehicleModel6DOF):
    """Add four independent wheel rotations to the 6DOF rigid body.

    State order::

        q     = [body_6, wheel_angle_fl, wheel_angle_fr, wheel_angle_rl, wheel_angle_rr]
        qdot* = [body_rate_6, wheel_speed_fl, wheel_speed_fr, wheel_speed_rl, wheel_speed_rr]

    Longitudinal force comes from tire slip ratio. Each wheel obeys
    ``J*wheel_accel = applied_torque - Fx*radius``.
    """

    dof: ClassVar[DOFModel] = 10
    coordinate_names: ClassVar[tuple[str, ...]] = VehicleModel6DOF.coordinate_names + (
        "wheel_angle_fl",
        "wheel_angle_fr",
        "wheel_angle_rl",
        "wheel_angle_rr",
    )
    velocity_names: ClassVar[tuple[str, ...]] = VehicleModel6DOF.velocity_names + (
        "wheel_speed_fl",
        "wheel_speed_fr",
        "wheel_speed_rl",
        "wheel_speed_rr",
    )
    added_physics: ClassVar[str] = "individual wheel speed, slip ratio, and torque balance"

    def _initialize_added_velocities(
        self,
        velocities: FloatArray,
        speed_mps: float,
    ) -> None:
        radii = np.asarray(self.parameters.wheel_radius_m, dtype=float)
        velocities[6:10] = speed_mps / radii

    def _wheel_speeds(
        self,
        velocities: FloatArray,
        wheel_longitudinal_speed: FloatArray,
    ) -> FloatArray:
        del wheel_longitudinal_speed
        return velocities[6:10]

    def _longitudinal_tire_force(
        self,
        normal_loads: FloatArray,
        slip_ratios: FloatArray,
        force_capacity: FloatArray,
        inputs: ModelInputs,
    ) -> FloatArray:
        """Use longitudinal stiffness and slip ratio with smooth saturation."""

        del inputs
        stiffness = self.parameters.tire.longitudinal_stiffness(normal_loads)
        return force_capacity * np.tanh(
            stiffness * slip_ratios / np.maximum(force_capacity, 1.0)
        )

    def _generalized_acceleration(
        self,
        body_accel: FloatArray,
        velocities: FloatArray,
        wheel_speeds: FloatArray,
        fx_tire: FloatArray,
        unsprung_accel: FloatArray,
        inputs: ModelInputs,
    ) -> FloatArray:
        del velocities, wheel_speeds, unsprung_accel
        wheel_accel = self._wheel_angular_acceleration(fx_tire, inputs)
        return np.concatenate((body_accel, wheel_accel))

    def _coordinate_derivative(
        self,
        coordinates: FloatArray,
        velocities: FloatArray,
        body_coordinates: FloatArray,
        body_velocities: FloatArray,
        rotation: FloatArray,
    ) -> FloatArray:
        del coordinates
        body_rate = self._six_dof_coordinate_derivative(
            body_coordinates,
            body_velocities,
            rotation,
        )
        return np.concatenate((body_rate, velocities[6:10]))


class VehicleModel14DOF(VehicleModel10DOF):
    """Add four unsprung vertical masses and tire vertical compliance.

    State order::

        q     = [body_6, unsprung_z_fl..rr, wheel_angle_fl..rr]
        qdot* = [body_rate_6, unsprung_speed_fl..rr, wheel_speed_fl..rr]

    The sprung body receives suspension force while each unsprung mass obeys
    ``m_u*z_u_accel = tire_vertical_force - suspension_force - m_u*g``.
    Road height and vertical road speed enter through the vertical tire model.
    """

    dof: ClassVar[DOFModel] = 14
    coordinate_names: ClassVar[tuple[str, ...]] = VehicleModel6DOF.coordinate_names + (
        "unsprung_z_fl",
        "unsprung_z_fr",
        "unsprung_z_rl",
        "unsprung_z_rr",
        "wheel_angle_fl",
        "wheel_angle_fr",
        "wheel_angle_rl",
        "wheel_angle_rr",
    )
    velocity_names: ClassVar[tuple[str, ...]] = VehicleModel6DOF.velocity_names + (
        "unsprung_speed_fl",
        "unsprung_speed_fr",
        "unsprung_speed_rl",
        "unsprung_speed_rr",
        "wheel_speed_fl",
        "wheel_speed_fr",
        "wheel_speed_rl",
        "wheel_speed_rr",
    )
    added_physics: ClassVar[str] = "unsprung vertical motion, tire compliance, and road input"
    _force_path_iterations: ClassVar[int] = 1

    def _initialize_added_velocities(
        self,
        velocities: FloatArray,
        speed_mps: float,
    ) -> None:
        radii = np.asarray(self.parameters.wheel_radius_m, dtype=float)
        velocities[10:14] = speed_mps / radii

    def _wheel_speeds(
        self,
        velocities: FloatArray,
        wheel_longitudinal_speed: FloatArray,
    ) -> FloatArray:
        del wheel_longitudinal_speed
        return velocities[10:14]

    def _vertical_forces(
        self,
        coordinates: FloatArray,
        velocities: FloatArray,
        body_coordinates: FloatArray,
        body_velocities: FloatArray,
        rotation: FloatArray,
        inputs: ModelInputs,
    ) -> VerticalForceState:
        """Separate suspension force, vertical tire force, and wheel-hop acceleration."""

        displacement, speed = self._suspension_kinematics(
            body_coordinates,
            body_velocities,
            rotation,
        )
        static_loads = np.asarray(self.parameters.static_wheel_loads_n, dtype=float)
        unsprung_masses = np.asarray(self.parameters.unsprung_mass_kg)
        unsprung_z = coordinates[6:10]
        unsprung_speed = velocities[6:10]
        compression = unsprung_z - displacement
        suspension_forces = self._suspension_force_from_compression(
            compression=compression,
            compression_speed=unsprung_speed - speed,
            spring_preload=static_loads - unsprung_masses * G,
        )

        road_height = np.asarray(inputs.road_heights_m, dtype=float)
        road_speed = np.asarray(inputs.road_vertical_speeds_mps, dtype=float)
        tire_rates = np.asarray(self.parameters.tire_vertical_stiffness_n_per_m)
        tire_damping = np.asarray(self.parameters.tire_vertical_damping_n_s_per_m)
        tire_forces = (
            static_loads
            + tire_rates * (road_height - unsprung_z)
            + tire_damping * (road_speed - unsprung_speed)
        )
        unsprung_accel = (
            tire_forces - suspension_forces - unsprung_masses * G
        ) / unsprung_masses
        return VerticalForceState(
            tire_forces,
            suspension_forces,
            unsprung_accel,
            compression,
            unsprung_speed - speed,
        )

    def _body_mass_properties(self) -> tuple[float, FloatArray]:
        return self.parameters.sprung_mass_kg, self.parameters.sprung_inertia

    def _body_translational_masses(self, body_mass: float) -> FloatArray:
        del body_mass
        return np.array(
            [
                self.parameters.mass_kg,
                self.parameters.mass_kg,
                self.parameters.sprung_mass_kg,
            ]
        )

    def _gravity_force_body(
        self,
        rotation: FloatArray,
        body_mass: float,
    ) -> FloatArray:
        del body_mass
        total_gravity = rotation.T @ np.array(
            [0.0, 0.0, -self.parameters.mass_kg * G]
        )
        sprung_gravity = rotation.T @ np.array(
            [0.0, 0.0, -self.parameters.sprung_mass_kg * G]
        )
        return np.array([total_gravity[0], total_gravity[1], sprung_gravity[2]])

    def _forces_transmitted_to_body(
        self,
        wheel_forces_body: FloatArray,
        suspension_forces: FloatArray,
        geometric_vertical: FloatArray,
    ) -> FloatArray:
        body_forces = wheel_forces_body.copy()
        body_forces[:, 2] = suspension_forces + geometric_vertical
        return body_forces

    def _closed_normal_loads(
        self,
        normal_loads: FloatArray,
        suspension_forces: FloatArray,
        geometric_vertical: FloatArray,
        algebraic_load_transfer: FloatArray,
    ) -> FloatArray:
        """Tire vertical compliance already determines 14DOF contact load."""

        del suspension_forces, geometric_vertical, algebraic_load_transfer
        return normal_loads

    def _unsprung_acceleration_with_geometry(
        self,
        unsprung_accel: FloatArray,
        geometric_vertical: FloatArray,
    ) -> FloatArray:
        """The chassis link force has an equal-and-opposite unsprung reaction."""

        unsprung_masses = np.asarray(self.parameters.unsprung_mass_kg, dtype=float)
        return unsprung_accel - geometric_vertical / unsprung_masses

    def _generalized_acceleration(
        self,
        body_accel: FloatArray,
        velocities: FloatArray,
        wheel_speeds: FloatArray,
        fx_tire: FloatArray,
        unsprung_accel: FloatArray,
        inputs: ModelInputs,
    ) -> FloatArray:
        del velocities, wheel_speeds
        wheel_accel = self._wheel_angular_acceleration(fx_tire, inputs)
        return np.concatenate((body_accel, unsprung_accel, wheel_accel))

    def _coordinate_derivative(
        self,
        coordinates: FloatArray,
        velocities: FloatArray,
        body_coordinates: FloatArray,
        body_velocities: FloatArray,
        rotation: FloatArray,
    ) -> FloatArray:
        del coordinates
        body_rate = self._six_dof_coordinate_derivative(
            body_coordinates,
            body_velocities,
            rotation,
        )
        return np.concatenate((body_rate, velocities[6:10], velocities[10:14]))


# Alias kept for existing envelope callers.
ReducedVehicleModel = VehicleDynamicsSystem


def create_model(dof: DOFModel, parameters: ReducedVehicleParameters) -> VehicleDynamicsSystem:
    model_types = {
        3: VehicleModel3DOF,
        6: VehicleModel6DOF,
        10: VehicleModel10DOF,
        14: VehicleModel14DOF,
    }
    try:
        return model_types[dof](parameters)
    except KeyError as exc:
        raise ValueError(f"Unsupported reduced-order model: {dof}DOF.") from exc


def _body_to_world_rotation(euler_rad: ArrayLike) -> FloatArray:
    euler = np.asarray(euler_rad, dtype=float)
    roll, pitch, yaw = float(euler[0]), float(euler[1]), float(euler[2])
    cr, sr = np.cos(roll), np.sin(roll)
    cp, sp = np.cos(pitch), np.sin(pitch)
    cy, sy = np.cos(yaw), np.sin(yaw)
    return np.array(
        [
            [cy * cp, cy * sp * sr - sy * cr, cy * sp * cr + sy * sr],
            [sy * cp, sy * sp * sr + cy * cr, sy * sp * cr - cy * sr],
            [-sp, cp * sr, cp * cr],
        ],
        dtype=float,
    )


def _euler_rates(roll: float, pitch: float, body_rates: FloatArray) -> FloatArray:
    cosine_pitch = np.cos(pitch)
    if abs(cosine_pitch) < 1e-6:
        raise ValueError("Pitch is too close to the Euler-angle singularity.")
    sine_roll, cosine_roll = np.sin(roll), np.cos(roll)
    tangent_pitch = np.tan(pitch)
    transform = np.array(
        [
            [1.0, sine_roll * tangent_pitch, cosine_roll * tangent_pitch],
            [0.0, cosine_roll, -sine_roll],
            [0.0, sine_roll / cosine_pitch, cosine_roll / cosine_pitch],
        ]
    )
    return transform @ body_rates
