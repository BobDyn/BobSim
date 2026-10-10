"""Unified suspension kinematics and reduced-order vehicle dynamics.

``Vehicle`` is the product-level entry point.  The lower-level kinematics,
model, QSS, and transient interfaces remain public for focused workflows.

The model names count generalized coordinates, not first-order states:

* 3DOF: global x/y/yaw planar body motion.
* 6DOF: full rigid-body translation and rotation.
* 10DOF: 6DOF body plus four wheel rotations.
* 14DOF: 10DOF plus four unsprung vertical motions.
"""

from engines.dynpy.kinematics import (
    BUMP_CURVE_SOURCES,
    DEFAULT_ROLL_DEG,
    DEFAULT_SWEEP_M,
    KINEMATIC_CURVE_META,
    ROLL_CURVE_SOURCES,
    AxleKinematicLookup,
    AxleKinematicState,
    CornerKinematics,
    CornerPointSet,
    DoubleWishboneKinematicLookup,
    KinematicsMode,
    NonlinearDoubleWishboneKinematics,
    VehicleKinematicState,
    VehicleKinematics,
    create_kinematics,
    kinematic_curves_payload,
)

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
    TireParameters,
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
from engines.dynpy.suspension import (
    CornerInstantLink,
    DoubleWishboneGeometry,
    DoubleWishboneInstantLinks,
    project_double_wishbone_instant_links,
)
from engines.dynpy.transient import (
    TransientResult,
    compare_transient_signals,
    simulate_transient,
)
from engines.dynpy.vehicle import Vehicle

__all__ = [
    "AxleKinematicLookup",
    "AxleKinematicState",
    "BUMP_CURVE_SOURCES",
    "CORNERS",
    "CornerInstantLink",
    "CornerKinematics",
    "CornerPointSet",
    "DEFAULT_ROLL_DEG",
    "DEFAULT_SWEEP_M",
    "DOFModel",
    "DoubleWishboneGeometry",
    "DoubleWishboneInstantLinks",
    "DoubleWishboneKinematicLookup",
    "KINEMATIC_CURVE_META",
    "KinematicsMode",
    "ModelInputs",
    "ModelOutput",
    "NonlinearDoubleWishboneKinematics",
    "PowertrainLimits",
    "QSSResult",
    "ROLL_CURVE_SOURCES",
    "ReducedVehicleParameters",
    "TireParameters",
    "TransientResult",
    "Vehicle",
    "VehicleDynamicsSystem",
    "VehicleKinematicState",
    "VehicleKinematics",
    "VehicleModel3DOF",
    "VehicleModel6DOF",
    "VehicleModel10DOF",
    "VehicleModel14DOF",
    "compare_transient_signals",
    "create_kinematics",
    "create_model",
    "kinematic_curves_payload",
    "load_reduced_vehicle_parameters",
    "project_double_wishbone_instant_links",
    "project_powertrain_limits",
    "simulate_transient",
    "solve_acceleration_trim",
    "solve_moment_state",
    "solve_steady_state",
    "steady_state_residual",
]
