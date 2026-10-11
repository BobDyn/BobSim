"""Reduced-order vehicle dynamics using KinPy suspension geometry.

``Vehicle`` composes KinPy geometry with the model, QSS and transient interfaces.
Standalone geometry queries and lookup construction belong to ``engines.kinpy``.

The model names count generalized coordinates, not first-order states:

* 3DOF: global x/y/yaw planar body motion.
* 6DOF: full rigid-body translation and rotation.
* 10DOF: 6DOF body plus four wheel rotations.
* 14DOF: 10DOF plus four unsprung vertical motions.
"""

from engines.dynpy.models import (
    DOFModel,
    ModelInputs,
    ModelOutput,
    VehicleDynamicsSystem,
    VehicleModel3DOF,
    VehicleModel6DOF,
    VehicleModel10DOF,
    VehicleModel14DOF,
    create_model,
)
from engines.dynpy.parameters import (
    CORNERS,
    PowertrainLimits,
    ReducedVehicleParameters,
    load_reduced_vehicle_parameters,
    project_powertrain_limits,
)
from engines.dynpy.qss import (
    QSSResult,
    solve_acceleration_trim,
    solve_moment_state,
    steady_state_residual,
    solve_steady_state,
)
from engines.dynpy.transient import (
    TransientResult,
    compare_transient_signals,
    simulate_transient,
)
from engines.dynpy.vehicle import Vehicle
from engines.dynpy.tire import MF52Tire

__all__ = [
    "CORNERS",
    "DOFModel",
    "ModelInputs",
    "ModelOutput",
    "PowertrainLimits",
    "QSSResult",
    "ReducedVehicleParameters",
    "MF52Tire",
    "TransientResult",
    "Vehicle",
    "VehicleDynamicsSystem",
    "VehicleModel3DOF",
    "VehicleModel6DOF",
    "VehicleModel10DOF",
    "VehicleModel14DOF",
    "compare_transient_signals",
    "create_model",
    "load_reduced_vehicle_parameters",
    "project_powertrain_limits",
    "simulate_transient",
    "solve_acceleration_trim",
    "solve_moment_state",
    "solve_steady_state",
    "steady_state_residual",
]
