from __future__ import annotations

from pathlib import Path
from typing import Any

from _5_App.contracts import (
    ActionSpec,
    BuildTargetSpec,
    ConfigSpec,
    FieldSpec,
    OutputSpec,
    WorkflowSpec,
)


def _field(
    path: str,
    label: str,
    *,
    kind: str = "auto",
    group: str | None = None,
    unit: str | None = None,
    choices: tuple[str, ...] = (),
    disabled: bool = False,
    placeholder: str | None = None,
    help_text: str | None = None,
) -> FieldSpec:
    return FieldSpec(
        path=tuple(path.split(".")),
        label=label,
        kind=kind,
        group=group,
        unit=unit,
        choices=choices,
        disabled=disabled,
        placeholder=placeholder,
        help_text=help_text,
    )


ARCHITECTURE_CHOICES = ("direct", "bellcrank", "bellcrank_stabar")
SOLVER_CHOICES = ("dassl", "ida", "cvode", "euler")
DIRECTION_CHOICES = ("left", "right")
ROD_TARGET_CHOICES = ("lower", "upper")
BELLCRANK_ORDER_CHOICES = ("rod", "shock")
STABAR_BELLCRANK_ORDER_CHOICES = ("rod", "shock", "stabar")
POWERTRAIN_IMPLEMENTATIONS = (
    {
        "id": "EVBatInvMotDiff",
        "label": "EV battery/VCU/inverter/motor/differential",
        "status": "implemented",
        "components": ("Battery", "VCU", "Inverter", "Motor", "Differential"),
    },
)
POWERTRAIN_DEFAULTS: dict[str, dict[str, Any]] = {
    "EVBatInvMotDiff": {
        "implementation": "EVBatInvMotDiff",
        "pBattery": {
            "Ns": 140,
            "Np": 4,
            "SOC_start": 1.0,
        },
        "pVCU": {
            "tau_max": 220,
            "regenTorqueLimit": 220,
            "w_eps": 1.0,
            "motorSpeedSign": 1,
        },
        "pInverter": {
            "P_max_mot": 124_000,
            "P_max_reg": 124_000,
            "V_dc_max": 588,
        },
        "pMotor": {
            "Vdc_max": 630,
            "rpm_max_peak": 6500,
            "T_peak": 220,
            "T_cont": 130,
            "I_peak_2min": 360,
            "I_cont": 180,
            "Kt_Nm_per_A": 0.61,
            "peakTime": 120,
            "P_mech_peak": 124_000,
            "P_cont_low": 75_000,
            "P_cont_high": 75_000,
            "eta_mot": 0.96,
            "eta_reg": 0.95,
            "w_eps": 1.0,
            "rotorJ": 0.02521,
        },
        "pDriveline": {
            "finalDriveRatio": 3.31,
            "diffInputRotorJ": 0.04,
            "diff_use_lsd": True,
            "diff_driveSideTorqueSign": 1,
            "diff_T_preload": 20,
            "diff_lockFractionAccel": 0.35,
            "diff_lockFractionDecel": 0.15,
            "diff_T_capacity_max": 1000,
            "diff_clutchEffectiveRadius": 1.0,
            "diff_kineticFrictionRatio": 0.85,
            "diff_w_transition": 1.0,
            "diff_c_viscous": 0.05,
            "halfshaftLeftC": 15_000,
            "halfshaftLeftJEquivalent": 0.02,
            "halfshaftLeftD": 34.64101615137755,
            "halfshaftRightC": 15_000,
            "halfshaftRightJEquivalent": 0.02,
            "halfshaftRightD": 34.64101615137755,
        },
    },
}

COMMON_SIM_FIELDS = (
    _field("simulation.start_time", "Start time", kind="number", group="Simulation", unit="s"),
    _field("simulation.stop_time", "Stop time", kind="number", group="Simulation", unit="s"),
    _field("simulation.stepSize", "Step size", kind="number", group="Simulation", unit="s"),
    _field("simulation.solver", "Solver", kind="select", group="Simulation", choices=SOLVER_CHOICES),
    _field("simulation.tolerance", "Tolerance", kind="number", group="Simulation"),
    _field("simulation.case_timeout_s", "Case timeout", kind="number", group="Simulation", unit="s"),
    _field("simulation.no_grid", "No grid", kind="boolean", group="Simulation"),
    _field("simulation.no_event_emit", "No event emit", kind="boolean", group="Simulation"),
    _field("execution.parallel", "Parallel", kind="boolean", group="Execution"),
    _field("execution.max_workers", "Max workers", kind="integer", group="Execution"),
    _field("execution.cleanup", "Cleanup raw artifacts", kind="boolean", group="Execution"),
    _field("execution.stream_logs", "Stream logs", kind="boolean", group="Execution"),
    _field("execution.fail_fast", "Fail fast", kind="boolean", group="Execution"),
    _field("report.enabled", "Report enabled", kind="boolean", group="Report"),
    _field("report.brand", "Brand", kind="string", group="Report"),
    _field("report.title", "Title", kind="string", group="Report"),
    _field("report.subtitle", "Subtitle", kind="string", group="Report"),
    _field("report.output_path", "Report path", kind="string", group="Report"),
    _field("report.metrics_csv_path", "Metrics CSV path", kind="string", group="Report"),
    _field("report.metric_target_velocity_mps", "Metric target velocity", kind="number", group="Report", unit="m/s"),
)

VEHICLE_FIELDS: tuple[FieldSpec, ...] = (
    _field("vehicle.name", "Vehicle name", kind="string", group="Vehicle"),
    _field("vehicle.version", "Version", kind="string", group="Vehicle"),
    _field(
        "architecture.front", "Front architecture", kind="select", group="Architecture", choices=ARCHITECTURE_CHOICES
    ),
    _field("architecture.rear", "Rear architecture", kind="select", group="Architecture", choices=ARCHITECTURE_CHOICES),
    _field("sprung_mass.mass_kg", "Sprung mass", kind="number", group="Mass", unit="kg"),
    _field("sprung_mass.cg_m", "Sprung CG", kind="list", group="Mass", unit="m"),
    _field("driver_mass.mass_kg", "Driver mass", kind="number", group="Mass", unit="kg"),
    _field("driver_mass.cg_m", "Driver CG", kind="list", group="Mass", unit="m"),
    _field(
        "body.torsional_stiff_n_m_per_rad",
        "Torsional stiffness",
        kind="number",
        group="Chassis compliance",
        unit="N m/rad",
    ),
    _field(
        "powertrain.implementation",
        "Powertrain architecture",
        kind="select",
        group="Powertrain implementation",
        choices=tuple(str(item["id"]) for item in POWERTRAIN_IMPLEMENTATIONS),
    ),
    _field("powertrain.pBattery.Ns", "Series cells", kind="integer", group="Battery"),
    _field("powertrain.pBattery.Np", "Parallel cells", kind="integer", group="Battery"),
    _field("powertrain.pBattery.SOC_start", "Start SOC", kind="number", group="Battery"),
    _field("powertrain.pVCU.tau_max", "Max drive torque", kind="number", group="VCU", unit="N m"),
    _field("powertrain.pVCU.regenTorqueLimit", "Regen torque limit", kind="number", group="VCU", unit="N m"),
    _field("powertrain.pVCU.w_eps", "Speed epsilon", kind="number", group="VCU", unit="rad/s"),
    _field("powertrain.pVCU.motorSpeedSign", "Motor speed sign", kind="integer", group="VCU"),
    _field("powertrain.pInverter.P_max_mot", "Max motoring power", kind="number", group="Inverter", unit="W"),
    _field("powertrain.pInverter.P_max_reg", "Max regen power", kind="number", group="Inverter", unit="W"),
    _field("powertrain.pInverter.V_dc_max", "Max DC voltage", kind="number", group="Inverter", unit="V"),
    _field("powertrain.pMotor.Vdc_max", "Max DC voltage", kind="number", group="Motor", unit="V"),
    _field("powertrain.pMotor.rpm_max_peak", "Peak max speed", kind="number", group="Motor", unit="rpm"),
    _field("powertrain.pMotor.T_peak", "Peak torque", kind="number", group="Motor", unit="N m"),
    _field("powertrain.pMotor.T_cont", "Continuous torque", kind="number", group="Motor", unit="N m"),
    _field("powertrain.pMotor.I_peak_2min", "Peak current, 2 min", kind="number", group="Motor", unit="A"),
    _field("powertrain.pMotor.I_cont", "Continuous current", kind="number", group="Motor", unit="A"),
    _field(
        "powertrain.pMotor.Kt_Nm_per_A",
        "Torque constant",
        kind="number",
        group="Motor",
        unit="N m/A",
    ),
    _field("powertrain.pMotor.peakTime", "Peak duration", kind="number", group="Motor", unit="s"),
    _field("powertrain.pMotor.P_mech_peak", "Peak mechanical power", kind="number", group="Motor", unit="W"),
    _field("powertrain.pMotor.P_cont_low", "Continuous power low", kind="number", group="Motor", unit="W"),
    _field("powertrain.pMotor.P_cont_high", "Continuous power high", kind="number", group="Motor", unit="W"),
    _field("powertrain.pMotor.eta_mot", "Motoring efficiency", kind="number", group="Motor"),
    _field("powertrain.pMotor.eta_reg", "Regen efficiency", kind="number", group="Motor"),
    _field("powertrain.pMotor.w_eps", "Speed epsilon", kind="number", group="Motor", unit="rad/s"),
    _field("powertrain.pMotor.rotorJ", "Rotor inertia", kind="number", group="Motor", unit="kg m2"),
    _field("powertrain.pDriveline.finalDriveRatio", "Final drive ratio", kind="number", group="Driveline"),
    _field(
        "powertrain.pDriveline.diffInputRotorJ",
        "Differential input inertia",
        kind="number",
        group="Driveline",
        unit="kg m2",
    ),
    _field("powertrain.pDriveline.diff_use_lsd", "Use LSD", kind="boolean", group="Driveline"),
    _field(
        "powertrain.pDriveline.diff_driveSideTorqueSign",
        "Drive-side torque sign",
        kind="integer",
        group="Driveline",
    ),
    _field("powertrain.pDriveline.diff_T_preload", "LSD preload torque", kind="number", group="Driveline", unit="N m"),
    _field("powertrain.pDriveline.diff_lockFractionAccel", "Accel lock fraction", kind="number", group="Driveline"),
    _field("powertrain.pDriveline.diff_lockFractionDecel", "Decel lock fraction", kind="number", group="Driveline"),
    _field(
        "powertrain.pDriveline.diff_T_capacity_max",
        "Max LSD clutch torque",
        kind="number",
        group="Driveline",
        unit="N m",
    ),
    _field(
        "powertrain.pDriveline.diff_clutchEffectiveRadius",
        "Clutch effective radius",
        kind="number",
        group="Driveline",
        unit="m",
    ),
    _field(
        "powertrain.pDriveline.diff_kineticFrictionRatio",
        "Kinetic friction ratio",
        kind="number",
        group="Driveline",
    ),
    _field(
        "powertrain.pDriveline.diff_w_transition",
        "Lock transition speed",
        kind="number",
        group="Driveline",
        unit="rad/s",
    ),
    _field(
        "powertrain.pDriveline.diff_c_viscous",
        "Viscous damping",
        kind="number",
        group="Driveline",
        unit="N m s/rad",
    ),
    _field(
        "powertrain.pDriveline.halfshaftLeftC",
        "Left halfshaft stiffness",
        kind="number",
        group="Driveline",
        unit="N m/rad",
    ),
    _field(
        "powertrain.pDriveline.halfshaftLeftJEquivalent",
        "Left halfshaft inertia",
        kind="number",
        group="Driveline",
        unit="kg m2",
    ),
    _field(
        "powertrain.pDriveline.halfshaftLeftD",
        "Left halfshaft damping",
        kind="number",
        group="Driveline",
        unit="N m s/rad",
    ),
    _field(
        "powertrain.pDriveline.halfshaftRightC",
        "Right halfshaft stiffness",
        kind="number",
        group="Driveline",
        unit="N m/rad",
    ),
    _field(
        "powertrain.pDriveline.halfshaftRightJEquivalent",
        "Right halfshaft inertia",
        kind="number",
        group="Driveline",
        unit="kg m2",
    ),
    _field(
        "powertrain.pDriveline.halfshaftRightD",
        "Right halfshaft damping",
        kind="number",
        group="Driveline",
        unit="N m s/rad",
    ),
    _field("front.wheel.radius_m", "Front tire radius", kind="number", group="Front wheel", unit="m"),
    _field("front.wheel.toe_deg", "Front toe", kind="number", group="Front wheel", unit="deg"),
    _field("front.wheel.camber_deg", "Front camber", kind="number", group="Front wheel", unit="deg"),
    _field("front.tire.template", "Front tire template", kind="string", group="Front wheel"),
    _field(
        "front.actuation.rod_to", "Front rod target", kind="select", group="Front actuation", choices=ROD_TARGET_CHOICES
    ),
    _field(
        "front.actuation.shock.free_length_m",
        "Front spring free length",
        kind="number",
        group="Front actuation",
        unit="m",
    ),
    _field(
        "front.actuation.shock.spring_table.table",
        "Spring force curve",
        kind="list",
        group="Front spring",
        unit="m -> N",
        help_text="Rows map shock deflection to spring force.",
    ),
    _field(
        "front.actuation.shock.damper_table.table",
        "Damper force curve",
        kind="list",
        group="Front damper",
        unit="m/s -> N",
        help_text="Rows map shock shaft velocity to damper force.",
    ),
    _field(
        "front.actuation.stabar.rate_n_m_per_rad",
        "Front stabar rate",
        kind="number",
        group="Front actuation",
        unit="N m/rad",
    ),
    _field("rear.wheel.radius_m", "Rear tire radius", kind="number", group="Rear wheel", unit="m"),
    _field("rear.wheel.toe_deg", "Rear toe", kind="number", group="Rear wheel", unit="deg"),
    _field("rear.wheel.camber_deg", "Rear camber", kind="number", group="Rear wheel", unit="deg"),
    _field("rear.tire.template", "Rear tire template", kind="string", group="Rear wheel"),
    _field(
        "rear.actuation.rod_to", "Rear rod target", kind="select", group="Rear actuation", choices=ROD_TARGET_CHOICES
    ),
    _field(
        "rear.actuation.shock.free_length_m", "Rear spring free length", kind="number", group="Rear actuation", unit="m"
    ),
    _field(
        "rear.actuation.shock.spring_table.table",
        "Spring force curve",
        kind="list",
        group="Rear spring",
        unit="m -> N",
        help_text="Rows map shock deflection to spring force.",
    ),
    _field(
        "rear.actuation.shock.damper_table.table",
        "Damper force curve",
        kind="list",
        group="Rear damper",
        unit="m/s -> N",
        help_text="Rows map shock shaft velocity to damper force.",
    ),
    _field(
        "rear.actuation.stabar.rate_n_m_per_rad",
        "Rear stabar rate",
        kind="number",
        group="Rear actuation",
        unit="N m/rad",
    ),
)


def _wheel_compliance_fields(axle: str, label: str) -> tuple[FieldSpec, ...]:
    group = f"{label} compliance"
    planned = "Planned BobLib compliance input."
    return (
        _field(
            f"{axle}.compliances.wheel_center_x_per_fx_m_per_n",
            "Wheel center X / Fx",
            kind="number",
            group=group,
            unit="m/N",
            disabled=True,
            placeholder=planned,
        ),
        _field(
            f"{axle}.compliances.wheel_center_y_per_fy_m_per_n",
            "Wheel center Y / Fy",
            kind="number",
            group=group,
            unit="m/N",
            disabled=True,
            placeholder=planned,
        ),
        _field(
            f"{axle}.compliances.toe_per_mz_rad_per_n_m",
            "Toe / Mz",
            kind="number",
            group=group,
            unit="rad/(N m)",
            disabled=True,
            placeholder=planned,
        ),
        _field(
            f"{axle}.compliances.camber_per_fy_rad_per_n",
            "Camber / Fy",
            kind="number",
            group=group,
            unit="rad/N",
            disabled=True,
            placeholder=planned,
        ),
    )


def _hardpoint_fields(axle: str, label: str) -> tuple[FieldSpec, ...]:
    hardpoint_group = f"{label} hardpoints"
    actuation_group = f"{label} actuation"
    return (
        _field(f"{axle}.suspension.upper_fore_i_m", "Upper fore inner", kind="list", group=hardpoint_group, unit="m"),
        _field(f"{axle}.suspension.upper_aft_i_m", "Upper aft inner", kind="list", group=hardpoint_group, unit="m"),
        _field(f"{axle}.suspension.upper_o_m", "Upper outer", kind="list", group=hardpoint_group, unit="m"),
        _field(f"{axle}.suspension.lower_fore_i_m", "Lower fore inner", kind="list", group=hardpoint_group, unit="m"),
        _field(f"{axle}.suspension.lower_aft_i_m", "Lower aft inner", kind="list", group=hardpoint_group, unit="m"),
        _field(f"{axle}.suspension.lower_o_m", "Lower outer", kind="list", group=hardpoint_group, unit="m"),
        _field(f"{axle}.suspension.tie_o_m", "Tie rod outer", kind="list", group=hardpoint_group, unit="m"),
        _field(f"{axle}.suspension.wheel_center_m", "Wheel center", kind="list", group=hardpoint_group, unit="m"),
        _field(f"{axle}.steering.rack_pickup_m", "Rack pickup", kind="list", group=hardpoint_group, unit="m"),
        _field(f"{axle}.actuation.rod_mount_m", "Rod mount", kind="list", group=actuation_group, unit="m"),
        _field(f"{axle}.actuation.shock.mount_m", "Shock mount", kind="list", group=actuation_group, unit="m"),
        _field(f"{axle}.actuation.bellcrank.pivot_m", "Bellcrank pivot", kind="list", group=actuation_group, unit="m"),
        _field(
            f"{axle}.actuation.bellcrank.pickups_m.rod",
            "Bellcrank rod pickup",
            kind="list",
            group=actuation_group,
            unit="m",
        ),
        _field(
            f"{axle}.actuation.bellcrank.pickups_m.shock",
            "Bellcrank shock pickup",
            kind="list",
            group=actuation_group,
            unit="m",
        ),
        _field(
            f"{axle}.actuation.bellcrank.pickups_m.stabar",
            "Bellcrank stabar pickup",
            kind="list",
            group=actuation_group,
            unit="m",
        ),
        _field(f"{axle}.actuation.bellcrank.order", "Bellcrank order", kind="list", group=actuation_group),
        _field(f"{axle}.actuation.stabar.arm_end_m", "Stabar arm end", kind="list", group=actuation_group, unit="m"),
        _field(f"{axle}.actuation.stabar.bar_end_m", "Stabar bar end", kind="list", group=actuation_group, unit="m"),
    )


VEHICLE_FIELDS = (
    VEHICLE_FIELDS
    + _wheel_compliance_fields("front", "Front")
    + _wheel_compliance_fields("rear", "Rear")
    + _hardpoint_fields("front", "Front")
    + _hardpoint_fields("rear", "Rear")
)

VISUAL_FIELDS = (
    _field("render.show_signals", "Show signals", kind="boolean", group="Render"),
    _field("render.speed", "Playback speed", kind="number", group="Render"),
    _field("render.input_stride", "Input stride", kind="integer", group="Render"),
    _field("style.joints.radius", "Joint radius", kind="number", group="Style"),
    _field("style.joints.color", "Joint color", kind="string", group="Style"),
    _field("camera.attach_to", "Camera target", kind="string", group="Camera"),
    _field("camera.origin_offset.x", "Camera origin x", kind="number", group="Camera", unit="m"),
    _field("camera.origin_offset.y", "Camera origin y", kind="number", group="Camera", unit="m"),
    _field("camera.origin_offset.z", "Camera origin z", kind="number", group="Camera", unit="m"),
    _field("camera.camera_offsets.back", "Camera back", kind="number", group="Camera", unit="m"),
    _field("camera.camera_offsets.height", "Camera height", kind="number", group="Camera", unit="m"),
    _field("camera.mode", "Camera mode", kind="string", group="Camera"),
)

BASE_CONFIG_SPECS: dict[str, ConfigSpec] = {
    "vehicle": ConfigSpec(
        id="vehicle",
        group="setup",
        label="Active Vehicle",
        path="vehicle.yml",
        fields=VEHICLE_FIELDS,
    ),
    "ramp-steer": ConfigSpec(
        id="ramp-steer",
        group="standard",
        label="RampSteerEval",
        path="_3_StandardSim/RampSteerEval/ramp_steer_eval_config.yml",
        workflow_id="ramp-steer",
        fields=COMMON_SIM_FIELDS
        + (
            _field("sweep.testVels", "Test velocities", kind="list", group="Sweep", unit="m/s"),
            _field("sweep.maxAy", "Max lateral acceleration", kind="number", group="Sweep", unit="m/s^2"),
            _field(
                "simulation.init_parameters.enableLinearityTermination",
                "Enable nonlinearity cutoff",
                kind="boolean",
                group="Ramp termination",
                help_text="End the ramp when steering gain loss reaches the configured cutoff.",
            ),
            _field(
                "simulation.init_parameters.linearityNonlinearityFraction",
                "Nonlinearity cutoff",
                kind="number",
                group="Ramp termination",
                unit="fraction",
                help_text="Fractional local lateral-gain loss that stops the ramp after the reference Ay.",
            ),
            _field(
                "simulation.init_parameters.linearityReferenceAy",
                "Reference lateral acceleration",
                kind="number",
                group="Ramp termination",
                unit="m/s^2",
            ),
            _field(
                "simulation.init_parameters.linearityEvaluationAyMargin",
                "Evaluation margin",
                kind="number",
                group="Ramp termination",
                unit="m/s^2",
            ),
            _field(
                "simulation.init_parameters.linearitySlopeSamplePeriod",
                "Slope sample period",
                kind="number",
                group="Ramp termination",
                unit="s",
            ),
            _field(
                "simulation.init_parameters.linearityHoldDuration",
                "Cutoff hold",
                kind="number",
                group="Ramp termination",
                unit="s",
            ),
            _field("fit.ay_linear_max", "Linear fit bound", kind="number", group="Fit", unit="m/s^2"),
        ),
    ),
    "steady-state": ConfigSpec(
        id="steady-state",
        group="standard",
        label="SteadyStateEval",
        path="_3_StandardSim/SteadyStateEval/steady_state_eval_config.yml",
        workflow_id="steady-state",
        fields=COMMON_SIM_FIELDS
        + (
            _field("sweep.testVels", "Test velocities", kind="list", group="Sweep", unit="m/s"),
            _field("sweep.targetAys", "Target lateral accelerations", kind="list", group="Sweep", unit="m/s^2"),
            _field(
                "sweep.maxAyByVelocity",
                "Velocity Ay caps",
                kind="json",
                group="Sweep",
                unit="m/s^2",
                help_text="Optional per-velocity caps applied to the target grid before cases are generated.",
            ),
            _field("sweep.includeNegative", "Include negative sweep", kind="boolean", group="Sweep"),
            _field(
                "simulation.init_parameters.steadyStateSettleTimeout",
                "Settle timeout",
                kind="number",
                group="Closed loop",
                unit="s",
            ),
            _field(
                "simulation.init_parameters.steadyStateAyTolerance",
                "Ay tolerance",
                kind="number",
                group="Closed loop",
                unit="m/s^2",
            ),
            _field(
                "simulation.init_parameters.steadyStateAyRateTolerance",
                "Ay-rate tolerance",
                kind="number",
                group="Closed loop",
                unit="m/s^3",
            ),
            _field(
                "simulation.init_parameters.steadyStateSpeedTolerance",
                "Speed tolerance",
                kind="number",
                group="Closed loop",
                unit="m/s",
            ),
            _field("fit.nonlinearity_fraction", "Nonlinearity fraction", kind="number", group="Fit"),
        ),
    ),
    "fbrc": ConfigSpec(
        id="fbrc",
        group="standard",
        label="FbrcEval",
        path="_3_StandardSim/FbrcEval/fbrc_eval_config.yml",
        workflow_id="fbrc",
        fields=COMMON_SIM_FIELDS
        + (
            _field("sweep.testVels", "Test velocities", kind="list", group="Sweep", unit="m/s"),
            _field(
                "sweep.targetAys",
                "Target lateral accelerations",
                kind="list",
                group="Sweep",
                unit="m/s^2",
                help_text=(
                    "Force-based roll center height is a lateral-force-weighted mean, "
                    "so it is undefined at zero lateral acceleration."
                ),
            ),
            _field(
                "simulation.vehicle_yaml_path",
                "Vehicle YAML path",
                kind="string",
                group="Geometry",
                help_text=(
                    "Source of the control-arm inboard axis directions, which are rigid "
                    "in the chassis frame. All hardpoint positions come from the model."
                ),
            ),
            _field(
                "simulation.init_parameters.steadyStateSettleTimeout",
                "Settle timeout",
                kind="number",
                group="Closed loop",
                unit="s",
            ),
            _field(
                "simulation.init_parameters.steadyStateAyTolerance",
                "Ay tolerance",
                kind="number",
                group="Closed loop",
                unit="m/s^2",
            ),
        ),
    ),
    "transient": ConfigSpec(
        id="transient",
        group="standard",
        label="TransientEval",
        path="_3_StandardSim/TransientEval/transient_eval_config.yml",
        workflow_id="transient",
        fields=COMMON_SIM_FIELDS
        + (
            _field("test.testVel", "Test velocities", kind="list", group="Test", unit="m/s"),
            _field("test.run_step", "Run step steer", kind="boolean", group="Test"),
            _field("test.run_continuous_sine", "Run continuous sine", kind="boolean", group="Test"),
            _field("test.directions", "Directions", kind="list", group="Test", choices=DIRECTION_CHOICES),
            _field("test.steerStep_deg", "Step steer amplitudes", kind="list", group="Test", unit="deg"),
            _field("test.sweep_freq_hz", "Sine frequencies", kind="list", group="Test", unit="Hz"),
            _field("test.sweep_amp_deg", "Sine amplitudes", kind="list", group="Test", unit="deg"),
            _field("test.n_cycles", "Sine cycles", kind="integer", group="Test"),
        ),
    ),
    "four-post": ConfigSpec(
        id="four-post",
        group="standard",
        label="FourPostEval",
        path="_3_StandardSim/FourPostEval/four_post_eval_config.yml",
        workflow_id="four-post",
        fields=COMMON_SIM_FIELDS
        + (
            _field(
                "model_overrides.suspension.front.spring_rate_n_per_m",
                "Front spring rate",
                kind="number",
                group="Suspension",
                unit="N/m",
            ),
            _field(
                "model_overrides.suspension.front.stabar_rate_n_m_per_rad",
                "Front stabar rate",
                kind="number",
                group="Suspension",
                unit="N m/rad",
            ),
            _field(
                "model_overrides.suspension.rear.spring_rate_n_per_m",
                "Rear spring rate",
                kind="number",
                group="Suspension",
                unit="N/m",
            ),
            _field(
                "model_overrides.suspension.rear.stabar_rate_n_m_per_rad",
                "Rear stabar rate",
                kind="number",
                group="Suspension",
                unit="N m/rad",
            ),
            _field("procedure.steerMagnitude", "Steer magnitude", kind="number", group="Procedure", unit="rad"),
            _field("procedure.heaveMagnitude", "Heave magnitude", kind="number", group="Procedure", unit="m"),
            _field("procedure.rollMagnitude", "Roll magnitude", kind="number", group="Procedure", unit="rad"),
            _field("procedure.forceMagnitude", "Force magnitude", kind="number", group="Procedure", unit="N"),
        ),
    ),
    "ggv": ConfigSpec(
        id="ggv",
        group="envelope",
        label="GGV",
        path="_2_EnvelopeSim/GGV/ggv_config.yml",
        workflow_id="ggv",
        fields=(
            _field("generation.speeds_mps", "Speeds", kind="list", group="Generation", unit="m/s"),
            _field("generation.ay_max_g", "Max lateral acceleration", kind="number", group="Generation", unit="g"),
            _field("generation.ay_points", "Lateral points", kind="integer", group="Generation"),
            _field(
                "generation.ax_search_min_g", "Min longitudinal search", kind="number", group="Generation", unit="g"
            ),
            _field(
                "generation.ax_search_max_g", "Max longitudinal search", kind="number", group="Generation", unit="g"
            ),
            _field("generation.ax_search_points", "Longitudinal points", kind="integer", group="Generation"),
            _field("generation.include_left_right", "Include left/right", kind="boolean", group="Generation"),
            _field("report.enabled", "Report enabled", kind="boolean", group="Report"),
            _field("report.title", "Title", kind="string", group="Report"),
            _field("report.reference_speed_mps", "Reference speed", kind="number", group="Report", unit="m/s"),
            _field(
                "performance_index.track_profile.integration_step_m",
                "Track integration step",
                kind="number",
                group="Track profile",
                unit="m",
            ),
            _field("performance_index.track_profile.maneuvers", "Maneuvers", kind="json", group="Track profile"),
        ),
    ),
    "ymd": ConfigSpec(
        id="ymd",
        group="envelope",
        label="YMD",
        path="_2_EnvelopeSim/YMD/ymd_config.yml",
        workflow_id="ymd",
        fields=(
            _field("generation.speed_mps", "Speed", kind="number", group="Generation", unit="m/s"),
            _field("generation.beta_min_deg", "Min beta", kind="number", group="Generation", unit="deg"),
            _field("generation.beta_max_deg", "Max beta", kind="number", group="Generation", unit="deg"),
            _field("generation.beta_points", "Beta points", kind="integer", group="Generation"),
            _field("generation.hwa_min_deg", "Min handwheel", kind="number", group="Generation", unit="deg"),
            _field("generation.hwa_max_deg", "Max handwheel", kind="number", group="Generation", unit="deg"),
            _field("generation.hwa_points", "Handwheel points", kind="integer", group="Generation"),
            _field("speed_sweep.enabled", "Speed sweep", kind="boolean", group="Speed sweep"),
            _field("speed_sweep.speeds_mps", "Sweep speeds", kind="list", group="Speed sweep", unit="m/s"),
            _field("report.enabled", "Report enabled", kind="boolean", group="Report"),
            _field("report.title", "Title", kind="string", group="Report"),
        ),
    ),
    "vehicle-review": ConfigSpec(
        id="vehicle-review",
        group="report",
        label="VehicleReview",
        path="_2_EnvelopeSim/VehicleReview/vehicle_review_config.yml",
        workflow_id="vehicle-review",
        fields=(
            _field("report.brand", "Brand", kind="string", group="Report"),
            _field("report.title", "Title", kind="string", group="Report"),
            _field("report.subtitle", "Subtitle", kind="string", group="Report"),
            _field("output.results_dir", "Results directory", kind="string", group="Output"),
            _field("output.pdf_filename", "PDF filename", kind="string", group="Output"),
            _field("output.metrics_csv_filename", "Metrics CSV filename", kind="string", group="Output"),
            _field("generation.regenerate_ggv", "Regenerate GGV", kind="boolean", group="Generation"),
            _field("generation.regenerate_ymd", "Regenerate YMD", kind="boolean", group="Generation"),
        ),
    ),
    "standard-sens": ConfigSpec(
        id="standard-sens",
        group="opt",
        label="StandardSens DOE",
        path="_4_OptSim/StandardSens/configs/_doe_config.yaml",
        workflow_id="standard-sens",
        fields=(
            _field("architecture.vehicle", "Vehicle model", kind="string", group="Architecture"),
            _field("architecture.record", "Vehicle record", kind="string", group="Architecture"),
            _field(
                "sampling.method",
                "Sampling method",
                kind="select",
                choices=("interval_splice", "lhs", "response_surface_pairs"),
                group="Sampling",
            ),
            _field("sampling.intervals", "Intervals", kind="integer", group="Sampling"),
            _field("samples", "LHS samples", kind="integer", group="Sampling"),
            _field("seed", "Random seed", kind="integer", group="Sampling"),
        ),
    ),
    "standard-sens-compiler": ConfigSpec(
        id="standard-sens-compiler",
        group="opt",
        label="StandardSens Compiler",
        path="_4_OptSim/StandardSens/configs/compiler_config.yaml",
        fields=(
            _field("max_workers", "Compiler workers", kind="integer", group="Compiler"),
            _field("batch.max_workers", "Batch workers", kind="integer", group="Batch"),
            _field("batch.timeout", "Batch timeout", kind="integer", group="Batch", unit="s"),
        ),
    ),
    "standard-sens-architecture": ConfigSpec(
        id="standard-sens-architecture",
        group="opt",
        label="StandardSens Architecture",
        path="_4_OptSim/StandardSens/configs/vehicle_architecture.yaml",
        fields=(
            _field("sampling.method", "Sampling method", kind="string", group="Sampling"),
            _field("sampling.intervals", "Intervals", kind="integer", group="Sampling"),
            _field("samples", "Samples", kind="integer", group="Sampling"),
            _field("seed", "Seed", kind="integer", group="Sampling"),
        ),
    ),
    "envelope-sens": ConfigSpec(
        id="envelope-sens",
        group="opt",
        label="EnvelopeSens",
        path="_4_OptSim/EnvelopeSens/config.yml",
        workflow_id="envelope-sens",
        fields=(
            _field(
                "sampling.method",
                "Sampling method",
                kind="select",
                choices=("interval_splice",),
                group="Sampling",
            ),
            _field("sampling.intervals", "Intervals", kind="integer", group="Sampling"),
        ),
    ),
}



def _python_module_argv(python: str, python_module_arg: str, module: str) -> tuple[str, ...]:
    return (python, python_module_arg, module)


def build_action_specs(root: Path, python: str, python_module_arg: str) -> dict[str, ActionSpec]:
    return {
        "build-vehicle": ActionSpec(
            id="build-vehicle",
            label="Build VehicleSim",
            argv=("omc", "_3_StandardSim/build_vehicle_sim.mos"),
            requires_external_toolchain=True,
        ),
        "build-four-post": ActionSpec(
            id="build-four-post",
            label="Build FourPostSim",
            argv=("omc", "_3_StandardSim/build_four_post_sim.mos"),
            requires_external_toolchain=True,
        ),
        "run-ramp-steer": ActionSpec(
            id="run-ramp-steer",
            label="Run RampSteerEval",
            argv=_python_module_argv(python, python_module_arg, "_3_StandardSim.RampSteerEval.ramp_steer_eval_sim"),
            requires_external_toolchain=True,
        ),
        "run-steady-state": ActionSpec(
            id="run-steady-state",
            label="Run SteadyStateEval",
            argv=_python_module_argv(python, python_module_arg, "_3_StandardSim.SteadyStateEval.steady_state_eval_sim"),
            requires_external_toolchain=True,
        ),
        "run-transient": ActionSpec(
            id="run-transient",
            label="Run TransientEval",
            argv=_python_module_argv(python, python_module_arg, "_3_StandardSim.TransientEval.transient_eval_sim"),
            requires_external_toolchain=True,
        ),
        "run-four-post": ActionSpec(
            id="run-four-post",
            label="Run FourPostEval",
            argv=_python_module_argv(python, python_module_arg, "_3_StandardSim.FourPostEval.four_post_eval_sim"),
            requires_external_toolchain=True,
        ),
        "run-fbrc": ActionSpec(
            id="run-fbrc",
            label="Run FbrcEval",
            argv=_python_module_argv(python, python_module_arg, "_3_StandardSim.FbrcEval.fbrc_eval_sim"),
            requires_external_toolchain=True,
        ),
        "run-ggv": ActionSpec(
            id="run-ggv",
            label="Run GGV",
            argv=_python_module_argv(python, python_module_arg, "_2_EnvelopeSim.GGV.ggv_generation"),
            requires_external_toolchain=True,
        ),
        "run-ymd": ActionSpec(
            id="run-ymd",
            label="Run YMD",
            argv=_python_module_argv(python, python_module_arg, "_2_EnvelopeSim.YMD.ymd_generation"),
            requires_external_toolchain=True,
        ),
        "run-review": ActionSpec(
            id="run-review",
            label="Run VehicleReview",
            argv=_python_module_argv(python, python_module_arg, "_2_EnvelopeSim.VehicleReview.vehicle_review_sim"),
            requires_external_toolchain=True,
        ),
        "run-opt-standard": ActionSpec(
            id="run-opt-standard",
            label="Run StandardSens",
            argv=_python_module_argv(python, python_module_arg, "StandardSens.pre_screen_sensitivities"),
            env={"PYTHONPATH": f"{root / '_4_OptSim'}:{root}"},
            requires_external_toolchain=True,
        ),
        "run-opt-envelope": ActionSpec(
            id="run-opt-envelope",
            label="Run EnvelopeSens",
            argv=_python_module_argv(python, python_module_arg, "EnvelopeSens.sensitivities"),
            env={"PYTHONPATH": f"{root / '_4_OptSim'}:{root}"},
            requires_external_toolchain=True,
        ),
    }


def build_modelica_build_targets() -> dict[str, BuildTargetSpec]:
    return {
        "vehicle": BuildTargetSpec(
            id="vehicle",
            label="VehicleSim",
            action_id="build-vehicle",
            build_dir="_3_StandardSim/BuildBobLib/VehicleSim",
            exec_name="BobLib.Experiments.Standards.VehicleSim",
            script="_3_StandardSim/build_vehicle_sim.mos",
        ),
        "four_post": BuildTargetSpec(
            id="four_post",
            label="FourPostSim",
            action_id="build-four-post",
            build_dir="_3_StandardSim/BuildBobLib/FourPostSim",
            exec_name="BobLib.Experiments.Standards.FourPostSim",
            script="_3_StandardSim/build_four_post_sim.mos",
        ),
    }


BUILD_METADATA_FILENAME = ".bobsim_build.json"


def build_workflows() -> tuple[WorkflowSpec, ...]:
    return (
        WorkflowSpec(
            id="ramp-steer",
            group="standard",
            label="RampSteerEval",
            config="_3_StandardSim/RampSteerEval/ramp_steer_eval_config.yml",
            actions=("build-vehicle", "run-ramp-steer"),
            outputs=(
                OutputSpec("Report", "_3_StandardSim/generated_results/ramp_steer_eval_report.pdf", "pdf"),
                OutputSpec("Metrics", "_3_StandardSim/generated_results/ramp_steer_eval_report_metrics.csv", "csv"),
            ),
        ),
        WorkflowSpec(
            id="steady-state",
            group="standard",
            label="SteadyStateEval",
            config="_3_StandardSim/SteadyStateEval/steady_state_eval_config.yml",
            actions=("build-vehicle", "run-steady-state"),
            outputs=(
                OutputSpec("Report", "_3_StandardSim/generated_results/steady_state_eval_report.pdf", "pdf"),
                OutputSpec("Metrics", "_3_StandardSim/generated_results/steady_state_eval_report_metrics.csv", "csv"),
            ),
        ),
        WorkflowSpec(
            id="transient",
            group="standard",
            label="TransientEval",
            config="_3_StandardSim/TransientEval/transient_eval_config.yml",
            actions=("build-vehicle", "run-transient"),
            outputs=(
                OutputSpec("Report", "_3_StandardSim/generated_results/transient_eval_report.pdf", "pdf"),
                OutputSpec("Metrics", "_3_StandardSim/generated_results/transient_eval_report_metrics.csv", "csv"),
            ),
        ),
        WorkflowSpec(
            id="four-post",
            group="standard",
            label="FourPostEval",
            config="_3_StandardSim/FourPostEval/four_post_eval_config.yml",
            actions=("build-four-post", "run-four-post"),
            outputs=(
                OutputSpec("Report", "_3_StandardSim/generated_results/four_post_eval_report.pdf", "pdf"),
                OutputSpec("Metrics", "_3_StandardSim/generated_results/four_post_eval_report_metrics.csv", "csv"),
            ),
        ),
        WorkflowSpec(
            id="fbrc",
            group="standard",
            label="FbrcEval",
            config="_3_StandardSim/FbrcEval/fbrc_eval_config.yml",
            actions=("build-vehicle", "run-fbrc"),
            outputs=(
                OutputSpec("Report", "_3_StandardSim/generated_results/fbrc_eval_report.pdf", "pdf"),
                OutputSpec("Metrics", "_3_StandardSim/generated_results/fbrc_eval_report_metrics.csv", "csv"),
            ),
        ),
        WorkflowSpec(
            id="ggv",
            group="envelope",
            label="GGV",
            config="_2_EnvelopeSim/GGV/ggv_config.yml",
            actions=("run-ggv",),
            outputs=(
                OutputSpec("Report", "_2_EnvelopeSim/results/ggv_report.pdf", "pdf"),
                OutputSpec("Metrics", "_2_EnvelopeSim/results/ggv_report_metrics.csv", "csv"),
                OutputSpec("Raw CSV", "_2_EnvelopeSim/Build/GGV/ggv_first_principles.csv", "csv"),
            ),
        ),
        WorkflowSpec(
            id="ymd",
            group="envelope",
            label="YMD",
            config="_2_EnvelopeSim/YMD/ymd_config.yml",
            actions=("run-ymd",),
            outputs=(
                OutputSpec("Report", "_2_EnvelopeSim/results/ymd_report.pdf", "pdf"),
                OutputSpec("Metrics", "_2_EnvelopeSim/results/ymd_report_metrics.csv", "csv"),
                OutputSpec("Raw CSV", "_2_EnvelopeSim/Build/YMD/ymd_first_principles.csv", "csv"),
            ),
        ),
        WorkflowSpec(
            id="vehicle-review",
            group="report",
            label="VehicleReview",
            config="_2_EnvelopeSim/VehicleReview/vehicle_review_config.yml",
            actions=("run-review",),
            outputs=(
                OutputSpec("Report", "_2_EnvelopeSim/results/VehicleReview/vehicle_review_report.pdf", "pdf"),
                OutputSpec("Metrics", "_2_EnvelopeSim/results/VehicleReview/vehicle_review_report_metrics.csv", "csv"),
            ),
        ),
        WorkflowSpec(
            id="standard-sens",
            group="opt",
            label="StandardSens",
            config="_4_OptSim/StandardSens/configs/_doe_config.yaml",
            actions=("run-opt-standard",),
            outputs=(),
        ),
        WorkflowSpec(
            id="envelope-sens",
            group="opt",
            label="EnvelopeSens",
            config="_4_OptSim/EnvelopeSens/config.yml",
            actions=("run-opt-envelope",),
            outputs=(),
        ),
    )

