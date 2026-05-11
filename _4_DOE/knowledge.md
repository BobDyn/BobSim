# BobLib Knowledge Base

Comprehensive repository findings for the BobLib Modelica vehicle dynamics library.

## 1. Repository Snapshot

- Library name: BobLib
- Language: Modelica (.mo) with Modelica scripts (.mos)
- Modelica dependency: Modelica 3.2.3
- Additional dependency in `Vehicle`: ExternData 3.2.0
- Primary intent: physics-based modular vehicle dynamics simulation with standardized tests
- File scale (current repository):
    - 172 Modelica files
    - Declaration counts:
        - 50 `model`
        - 9 `partial model`
        - 27 `record`
        - 17 `function`
        - 70 `package`
- Automation scripts:
    - `msl_setup.mos`
    - `Standards/BuildKnC.mos`

Top-level package order (`package.order`):

1. Resources
2. Standards
3. Vehicle
4. Utilities
5. Tests

## 2. What This Library Is

BobLib is structured as a vehicle-modeling framework centered on:

- Multi-body chassis and suspension modeling
- Tire force/moment modeling with MF5.2-style decomposition
- Standardized maneuver and K&C test models
- Record-driven parameterization for vehicle variants

The code confirms a strong separation between model topology and parameter data:

- Model topology and dynamics are mostly in `Vehicle`
- Parameter records and test records are in `Resources`
- Standardized procedures are in `Standards`
- Reusable math/mechanics components are in `Utilities`
- Validation and exploratory benches are in `Tests`

## 3. Architecture Overview

### 3.1 Layering

1. Foundation utilities (`Utilities`)
2. Vehicle subsystem models (`Vehicle`)
3. Parameter records (`Resources`)
4. Standardized experiments (`Standards`)
5. Development and regression-style tests (`Tests`)

### 3.2 Core Composition Pattern

The primary composition is:

- `Vehicle.VehicleBase` (partial)
    - replaceable `chassis: Vehicle.Chassis.ChassisBase`
- `Vehicle.Chassis.ChassisBase` (partial)
    - replaceable front axle
    - replaceable rear axle
    - replaceable frame/body
- Tire abstraction through `BaseTire` with replaceable slip and wheel models

This gives high extensibility through Modelica `replaceable`/`redeclare` patterns while keeping
integration points stable.

## 4. Top-Level Package Deep Dive

## 4.1 Vehicle

Vehicle contains the physical subsystem models and major assembly logic.

### Key files

- `Vehicle/VehicleBase.mo`
    - partial top-level vehicle model
    - exposes wheel contact frames (FL/FR/RL/RR), CG frame, steering flange
    - delegates physical content to replaceable chassis

- `Vehicle/VehicleDW_RWD_Lock.mo`
    - concrete vehicle assembly
    - parameterized by `Resources.VehicleDefn.OrionRecord`
    - redeclares:
        - front/rear double-wishbone axle models
        - MF52 tire models for all corners
        - wheel physics model (`Wheel1DOF_Y`)
        - slip model (`KinematicSlip`)
        - frame/body model (`FrameCompX`)
    - includes `Powertrain.PTNPlaceholder` fed by a torque input

- `Vehicle/Chassis/ChassisBase.mo`
    - partial chassis integration model
    - replaceable front axle, rear axle, frame
    - wiring between axles, wheels, steering, and frame connectors

- `Vehicle/Chassis/ChassisDW_BC_ARB.mo`
    - concrete chassis variant with rear steer lock through `Mounting1D`

### Suspension and tire stack

Significant structure under `Vehicle/Chassis/Suspension`:

- Axles:
    - `FrAxleDW_BC_ARB.mo`
    - `RrAxleDW_BC_ARB.mo`
    - `AxleDWBase.mo`
- Linkages and compliance:
    - `Linkages/Bellcrank3.mo`
    - `Linkages/Rod.mo`
    - `Linkages/ShockLinkage.mo`
    - `Linkages/TabularSpring.mo`
    - `Linkages/TabularDamper.mo`
- Templates:
    - Double wishbone geometry loop model
    - Steering rack model
    - Stabar (anti-roll bar) model
    - Tire abstractions and implementations

### Tire subsystem pattern

- `Templates/Tire/BaseTire.mo`
    - computes normal load, contact orientation, ground-projected basis
    - computes Vx/Vy for slip
    - delegates slip state generation to replaceable slip model
    - delegates force/torque generation through overridable real-expression bindings
- `Templates/Tire/MF52Tire.mo`
    - extends `BaseTire`
    - calls `MF52.Eval(Fz, alpha, kappa, gamma, Vx, pTireModel)`
- `Templates/Tire/MF52/Eval.mo`
    - composes pure and combined slip sub-functions
    - returns Fx, Fy, Mx, My, Mz plus trail-like lengths `t`, `s`
    - applies sign transformation at boundary (`Fy`, `My`, `Mz` negated)
- Slip models:
    - `SlipModel/KinematicSlip.mo`: kinematic slip with low-speed regularization/clamping
    - `SlipModel/NoSlip.mo`: alpha=kappa=0 for kinematics-focused tests

### Powertrain/electronics/aero maturity

- `Vehicle/Powertrain/PTNPlaceholder.mo`
    - simple torque splitter (input scaled by 1/2 to each rear side)
- `Vehicle/Powertrain/Drivetrain/Motor.mo`
    - includes realistic envelope ideas (peak/continuous torque and power, efficiency placeholders,
      loss table)
    - still marked with placeholder efficiency-map strategy
- `Vehicle/Powertrain/Battery/BatteryPack.mo`
    - equivalent-circuit-like pack with OCV table and SOC dynamics
- `Vehicle/Aero/package.mo`
    - package placeholder only (no aerodynamic models implemented)

Conclusion for `Vehicle`: chassis and suspension modeling is robust and detailed; other domains are
present but less mature.

## 4.2 Resources

Resources stores records only, used for parameterization and standard output schemas.

### Key areas

- `Resources/VehicleDefn/OrionRecord.mo`
    - master vehicle definition record
    - includes front/rear axle geometry and compliance records
    - includes steering rack records, stabar records, mass/inertia records
    - includes front/rear tire model records with large MF52 coefficient sets

- `Resources/VehicleRecord/Chassis/Suspension/...`
    - hierarchy of reusable parameter records:
        - geometric records
        - wheel/tire parameter records
        - mass records
        - steering and anti-roll bar records

- `Resources/StandardRecord/...`
    - output record schemas for standardized tests:
        - `SteadyStateEvalRecord.mo`
        - `ISO8726Record.mo`
        - `KnCRecord.mo`

- `Resources/VisualRecord/...`
    - records used for geometric/visual extraction during simulation

Design takeaway: Resources is the data spine of the library and enables fast varianting without
structural model edits.

## 4.3 Standards

Standards holds canonical test procedures and templates.

### Core models

- `Standards/SteadyStateEval.mo`
    - steady-state cornering style setup with curvature PI control
    - uses full vehicle model, ground contact blocks, and speed PI torque feed
    - includes steady-state detection and early termination criteria
    - writes to `SteadyStateEvalRecord`

- `Standards/ISO8726.mo`
    - transient steering step setup
    - similar plant/environment structure to SteadyStateEval, with step handwheel command
    - writes to `ISO8726Record`

- `Standards/Templates/KnC.mo`
    - partial K&C framework
    - applies prescribed roll/heave and patch forces via time tables
    - includes instrumentation and jounce DOF structure
    - writes to `KnCRecord`

- `Standards/FrKnC.mo` and `Standards/RrKnC.mo`
    - instantiate front/rear K&C tests from template
    - use no-slip tire model and neutralized spring/damper+stabar rates for pure
      geometric/compliance extraction behavior

### Build automation

- `Standards/BuildKnC.mos`
    - loads BobLib and builds `FrKnC` + `RrKnC`
    - configures optimization flags and output MAT format

## 4.4 Utilities

Utilities contains reusable math and multibody helper components.

- `Utilities/Math/Vector`:
    - `dot.mo`, `cross.mo`, `angle_between.mo`, `mirrorXZ.mo`
- `Utilities/Math/Tensor`:
    - `mirrorXZ.mo`
- `Utilities/Mechanics/Multibody/GroundPhysics.mo`
    - compliant unilateral normal contact
    - uses smooth penetration function:
        - `pen = 0.5*(sqrt(r_rel_z^2 + eps^2) - r_rel_z)`
        - `f_z = c*pen + d*der(pen)`
    - helps reduce hard contact discontinuity issues
- additional helpers:
    - `LinearActuator.mo`
    - `PlanarMotion.mo`
    - `RodConstraint.mo`
    - `TranslationalJoint.mo`

## 4.5 Tests

Test package is broad and mirrors subsystem structure.

- Top test groups (`Tests/package.order`):
    - `TestVehicle`
    - `TestUtilities`
- Chassis-focused examples:
    - `Tests/TestVehicle/TestChassis/TestSuspension/TestFrAxleDW.mo`
    - `Tests/TestVehicle/TestChassis/TestSuspension/TestRrAxleDW.mo`
    - various template-level tests (stabar, steering rack, tire/MF52)
- Powertrain examples:
    - `Tests/TestVehicle/TestPowertrain/TestPowertrain.mo`
    - battery/inverter/motor differential bench arrangements
- Utility tests:
    - multibody helpers under `Tests/TestUtilities/TestMechanics/TestMultibody`

Test philosophy appears to be model-level executable benches rather than pure unit tests.

## 5. Key Design Patterns and Conventions

## 5.1 Replaceable/redeclare extensibility

The library systematically uses replaceable submodels and redeclarations for:

- axle types
- tire model variants
- slip model variants
- wheel DOF variants
- frame implementations

This is the dominant extension mechanism.

## 5.2 Strict record-based parameterization

`OrionRecord` and lower-level records carry geometry, inertia, and tire parameter values.

Implication:

- adding variants is mostly a record-editing operation
- model equations stay mostly unchanged across vehicle variants

## 5.3 Package discipline

- every package has `package.mo` + `package.order`
- ordering is explicit and consistent with Modelica package browsing/build behavior

## 5.4 Symmetry helpers

`mirrorXZ` utilities are used repeatedly to generate right-side geometry from left-side definitions.

## 5.5 State and solver pragmatics

Standards models include OpenModelica command-line options for matching/index-reduction behavior and
nonlinear diagnostics.

## 6. Practical Simulation Entry Points

Most useful runnable starts:

1. `Standards.SteadyStateEval`
2. `Standards.ISO8726`
3. `Standards.FrKnC`
4. `Standards.RrKnC`
5. `Tests.TestVehicle.*` benches for subsystem validation

Typical setup scripts:

- `msl_setup.mos`: install/load Modelica version
- `Standards/BuildKnC.mos`: build K&C binaries/results in batch

## 7. Learning About Maturity and Gaps

Evidence from repository code indicates:

### More mature

- Chassis/suspension architecture
- Tire integration pipeline with swap-in slip models
- Standardized maneuver and K&C workflows

### Less mature / in-progress

- Aero domain has placeholder package only
- Powertrain is partially detailed but still contains placeholder assumptions in integration path
- Electronics/control stack exists but is comparatively lighter than chassis
- FMI utility package exists but has minimal implementation breadth in current tree

## 8. High-Value File Index

### Core architecture

- `Vehicle/VehicleBase.mo`
- `Vehicle/VehicleDW_RWD_Lock.mo`
- `Vehicle/Chassis/ChassisBase.mo`
- `Vehicle/Chassis/ChassisDW_BC_ARB.mo`

### Suspension and tire

- `Vehicle/Chassis/Suspension/FrAxleDW_BC_ARB.mo`
- `Vehicle/Chassis/Suspension/RrAxleDW_BC_ARB.mo`
- `Vehicle/Chassis/Suspension/Templates/Tire/BaseTire.mo`
- `Vehicle/Chassis/Suspension/Templates/Tire/MF52Tire.mo`
- `Vehicle/Chassis/Suspension/Templates/Tire/MF52/Eval.mo`
- `Vehicle/Chassis/Suspension/Templates/Tire/MF52/SlipModel/KinematicSlip.mo`
- `Vehicle/Chassis/Suspension/Templates/Tire/MF52/SlipModel/NoSlip.mo`

### Standards and scripts

- `Standards/SteadyStateEval.mo`
- `Standards/ISO8726.mo`
- `Standards/Templates/KnC.mo`
- `Standards/FrKnC.mo`
- `Standards/RrKnC.mo`
- `Standards/BuildKnC.mos`
- `msl_setup.mos`

### Resources and records

- `Resources/VehicleDefn/OrionRecord.mo`
- `Resources/StandardRecord/SteadyStateEvalRecord.mo`
- `Resources/StandardRecord/ISO8726Record.mo`
- `Resources/StandardRecord/KnCRecord.mo`

### Utilities

- `Utilities/Mechanics/Multibody/GroundPhysics.mo`
- `Utilities/Math/Vector/mirrorXZ.mo`
- `Utilities/Math/Vector/angle_between.mo`

### Powertrain representative files

- `Vehicle/Powertrain/PTNPlaceholder.mo`
- `Vehicle/Powertrain/Drivetrain/Motor.mo`
- `Vehicle/Powertrain/Battery/BatteryPack.mo`

## 9. Recommended Way To Work With BobLib

1. Start from a standard test model (`SteadyStateEval`, `ISO8726`, `FrKnC`, `RrKnC`).
2. Parameterize via `Resources/VehicleDefn/OrionRecord.mo` rather than changing equations.
3. If needed, redeclare replaceable submodels in a new vehicle variant model.
4. Use tests under `Tests/TestVehicle` for focused subsystem debugging.
5. Keep new components aligned with package discipline (`package.mo` + `package.order`) and
   record-first configuration.

## 10. Summary

BobLib is a well-structured Modelica vehicle dynamics library with a strong and extensible
chassis/suspension core, a substantial record-based parameter ecosystem, and practical standardized
test workflows. The repository is designed for modular growth: mature in chassis dynamics, and
actively evolving in powertrain/electronics/aero completeness.
