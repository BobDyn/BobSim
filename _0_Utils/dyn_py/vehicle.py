"""Composed public vehicle interface for kinematics and reduced dynamics."""

from __future__ import annotations

from dataclasses import dataclass, field, replace
import math
from pathlib import Path
from typing import Mapping

from numpy.typing import ArrayLike

from _0_Utils.dyn_py.kinematics import (
    KinematicsMode,
    VehicleKinematicState,
    VehicleKinematics,
)
from _0_Utils.dyn_py.models import (
    DOFModel,
    FloatArray,
    ModelInputs,
    ModelOutput,
    VehicleDynamicsSystem,
    create_model,
)
from _0_Utils.dyn_py.parameters import (
    ReducedVehicleParameters,
    load_reduced_vehicle_parameters,
)
from _0_Utils.dyn_py.qss import (
    QSSResult,
    solve_acceleration_trim,
    solve_moment_state,
    solve_steady_state,
)
from _0_Utils.dyn_py.transient import (
    ControlLaw,
    TransientResult,
    simulate_transient,
)


@dataclass
class Vehicle:
    """One vehicle definition with shared kinematics and nested DOF models.

    The 3/6/10/14DOF systems are built on first use from the same parameters::

        vehicle = Vehicle.from_yaml()
        wheel_state = vehicle.kinematics_at([0.01, -0.01, 0.0, 0.0])
        model = vehicle.model(14)
    """

    parameters: ReducedVehicleParameters
    _models: dict[DOFModel, VehicleDynamicsSystem] = field(
        default_factory=dict,
        init=False,
        repr=False,
    )

    @classmethod
    def from_yaml(
        cls,
        path: str | Path | None = None,
        *,
        four_post_metrics_path: str | Path | None = None,
        kinematics_mode: KinematicsMode = "lookup",
        kinematics_sample_count: int = 49,
        kinematics_travel_limit_m: float = 0.06,
    ) -> Vehicle:
        """Load and project one vehicle definition into the complete model family."""

        return cls(
            load_reduced_vehicle_parameters(
                path,
                four_post_metrics_path=four_post_metrics_path,
                kinematics_mode=kinematics_mode,
                kinematics_sample_count=kinematics_sample_count,
                kinematics_travel_limit_m=kinematics_travel_limit_m,
            )
        )

    @property
    def kinematics(self) -> VehicleKinematics:
        """Return the hardpoint-derived evaluator shared by every DOF model."""

        return self.parameters.kinematics

    def kinematics_at(self, jounce_m: ArrayLike) -> VehicleKinematicState:
        """Evaluate all four suspension corners at individual jounces."""

        return self.kinematics.at(jounce_m)

    def with_power_limit(self, power_limit_w: float) -> Vehicle:
        """Return an independent vehicle capped at an event-level drive power.

        The cap cannot exceed the hardware/VCU limit. Torque and motor-speed
        limits do not change.
        """

        limit = float(power_limit_w)
        if not math.isfinite(limit) or limit <= 0.0:
            raise ValueError("Event drive-power limit must be finite and positive.")
        return Vehicle(
            replace(
                self.parameters,
                peak_drive_power_w=min(self.parameters.peak_drive_power_w, limit),
                continuous_drive_power_w=min(
                    self.parameters.continuous_drive_power_w,
                    limit,
                ),
            )
        )

    def model(self, dof: DOFModel) -> VehicleDynamicsSystem:
        """Return the cached member of the nested 3/6/10/14DOF family."""

        if dof not in self._models:
            self._models[dof] = create_model(dof, self.parameters)
        return self._models[dof]

    def initial_state(self, dof: DOFModel, speed_mps: float = 0.0) -> FloatArray:
        return self.model(dof).initial_state(speed_mps)

    def evaluate(
        self,
        dof: DOFModel,
        state: ArrayLike,
        inputs: ModelInputs = ModelInputs(),
    ) -> ModelOutput:
        return self.model(dof).evaluate(state, inputs)

    def simulate(
        self,
        dof: DOFModel,
        *,
        initial_state: ArrayLike,
        controls: ModelInputs | ControlLaw,
        time_s: ArrayLike,
        method: str = "RK45",
        rtol: float = 1e-6,
        atol: float = 1e-8,
    ) -> TransientResult:
        """Integrate one fidelity while retaining the common vehicle definition."""

        return simulate_transient(
            self.model(dof),
            initial_state=initial_state,
            controls=controls,
            time_s=time_s,
            method=method,
            rtol=rtol,
            atol=atol,
        )

    def steady_state(
        self,
        dof: DOFModel,
        *,
        speed_mps: float,
        yaw_rate_radps: float = 0.0,
        initial_beta_rad: float = 0.0,
        initial_steering_rad: float | None = None,
        initial_unknowns: Mapping[str, float] | None = None,
        max_nfev: int = 400,
        tolerance: float = 1e-8,
    ) -> QSSResult:
        """Solve a constant-speed, constant-radius operating point."""

        return solve_steady_state(
            self.model(dof),
            speed_mps=speed_mps,
            yaw_rate_radps=yaw_rate_radps,
            initial_beta_rad=initial_beta_rad,
            initial_steering_rad=initial_steering_rad,
            initial_unknowns=initial_unknowns,
            max_nfev=max_nfev,
            tolerance=tolerance,
        )

    def acceleration_trim(
        self,
        dof: DOFModel,
        *,
        speed_mps: float,
        longitudinal_acceleration_mps2: float,
        lateral_acceleration_mps2: float,
        yaw_rate_radps: float = 0.0,
        initial_beta_rad: float = 0.0,
        initial_steering_rad: float | None = None,
        initial_unknowns: Mapping[str, float] | None = None,
        max_nfev: int = 400,
        tolerance: float = 1e-8,
    ) -> QSSResult:
        """Solve a prescribed longitudinal/lateral acceleration point."""

        return solve_acceleration_trim(
            self.model(dof),
            speed_mps=speed_mps,
            longitudinal_acceleration_mps2=longitudinal_acceleration_mps2,
            lateral_acceleration_mps2=lateral_acceleration_mps2,
            yaw_rate_radps=yaw_rate_radps,
            initial_beta_rad=initial_beta_rad,
            initial_steering_rad=initial_steering_rad,
            initial_unknowns=initial_unknowns,
            max_nfev=max_nfev,
            tolerance=tolerance,
        )

    def moment_state(
        self,
        dof: DOFModel,
        *,
        speed_mps: float,
        beta_rad: float,
        steering_rad: float,
        yaw_rate_radps: float = 0.0,
        initial_unknowns: Mapping[str, float] | None = None,
        max_nfev: int = 300,
        tolerance: float = 1e-8,
    ) -> QSSResult:
        """Solve the imposed sideslip/steer state used by YMD generation."""

        return solve_moment_state(
            self.model(dof),
            speed_mps=speed_mps,
            beta_rad=beta_rad,
            steering_rad=steering_rad,
            yaw_rate_radps=yaw_rate_radps,
            initial_unknowns=initial_unknowns,
            max_nfev=max_nfev,
            tolerance=tolerance,
        )
