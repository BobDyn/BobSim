# Reduced-order vehicle dynamics

**TL;DR:** `engines/dynpy` is a fast, inspectable reduced-order vehicle model for envelopes and transient lap simulation. Intentionally lower fidelity than BobLib but explicitly correlated against it. Choose 3/6/10/14 DOF to quantify the value of each added state.

KinPy owns the suspension geometry. DynPy and the app use its original
`QuarterCar`, `Wishbone`, `Link`, `Node` and `Tire` elements through a vehicle YAML
adapter. Lookup tables are sampled from that same assembly.

## Using the unified vehicle interface

```python
from engines.dynpy import Vehicle

vehicle = Vehicle.from_yaml()
wheel_state = vehicle.kinematics_at([0.01, -0.01, 0.0, 0.0])  # all four wheels
model_14dof = vehicle.model(14)                               # 14DOF transient
trim = vehicle.steady_state(14, speed_mps=12.0)              # QSS trim at 12 m/s
```

The vehicle definition and kinematics cache are shared across all DOF models. Import `create_kinematics` from `engines.kinpy`. Dynamics constructors, QSS and
transient solvers are exposed by `engines.dynpy`.

## Fidelity ladder

"DOF" counts generalized coordinates. A second-order mechanical model has two
first-order states per coordinate.

| Model | Generalized coordinates | First-order states | Added physics |
| --- | --- | ---: | --- |
| 3DOF | global x, global y, yaw | 6 | planar motion, algebraic pitch/roll load transfer, fixed drive/brake distribution |
| 6DOF | body x/y/z and roll/pitch/yaw | 12 | heave, roll, pitch, instant-link suspension load transfer, aero pitch |
| 10DOF | 6DOF body + four wheel angles | 20 | individual wheel speed/slip and torque balance |
| 14DOF | 10DOF + four unsprung vertical positions | 28 | tire vertical compliance, wheel hop, and road-height inputs |

Each row is nested in the next. The 3DOF planar equations are therefore the
planar projection of the 6DOF model, and the 10/14DOF models do not carry a
second copy of the body or tire equations.

## Dynamics equations

**Coordinate frame:** x = forward, y = left, z = up.

**Body motion:**
```
v_dot = sum(F) / m - omega × v          (translational, body frame)
omega_dot = I^-1 (sum(M) - omega × I·omega)  (rotational)
```

**Load transfer:**
- 3DOF: pitch/roll moments closed algebraically (longitudinal ∝ ride height + wheelbase, lateral ∝ roll-stiffness split)
- 6DOF: heave/roll/pitch integrated with wheel rates, damping, anti-roll stiffness, preload
- 10DOF: adds wheel rotation dynamics
- 14DOF: integrates unsprung vertical motion and tire vertical compliance

**Tire model:**

Front and rear use their own `tire.template` selections. `aero.tire_template`
is a fallback only when an axle has no selection. Load validity is checked
against each corner's active fit.
- Contact patch position/velocity from kinematics evaluator (includes bump toe, camber, migration effects)
- Slip evaluated in individual wheel frames
- MF5.2 Fx, Fy, Mx, My and Mz curves with load and camber dependence
- MF5.2 combined slip, shifts, scale factors and post-peak force reduction

**Drive and brake:**
- Drive torque: `drive_distribution_front` from `vehicle.yml` (0 = RWD)
- Brake torque: front brake fraction from `vehicle.yml`
- Capability limited by: motor/VCU peak torque, FSAE motoring-power limit, peak power, rpm ceiling
- Competition limit (80 kW) ≠ hardware rating (124 kW)

**Power limiting (event studies):** Use `Vehicle.with_power_limit()` to cap capability without modifying `vehicle.yml`. Endurance default is 32 kW constant cap (energy-budget proxy, not thermal model).

The 10/14DOF QSS constraints retain wheel inertia. A prescribed vehicle
acceleration therefore gives each wheel the corresponding rolling angular
acceleration rather than incorrectly imposing zero wheel acceleration. In the
14DOF equations, longitudinal and lateral translation use total vehicle mass;
sprung mass is used only for the independently released chassis heave equation.

DynPy interpolates drag, downforce and all three CFD moments at the current
front and rear axle ride heights. Heights come from the chassis-mounted
reference points in `vehicle.yml`, mirrored for the right side, as in BobLib.
Queries outside the CFD grids clamp to the grid edges. The force acts at
`aero_ref_m`, with the interpolated free moment added to its moment about the CG.
Loads scale with air density and full three-dimensional speed. DynPy currently
assumes still air. The 3 DOF model keeps the nominal chassis pose and closes
vertical aero loads algebraically. The 6, 10 and 14 DOF models update the aero
map as the chassis moves.

`vehicle.yml` supplies geometry, component mass/inertia, wheel/tire values,
suspension tables, aero maps, and powertrain layout. Shock motion ratios and
anti-roll stiffness come from the YAML geometry. FourPost calibration requires
an explicit `four_post_metrics_path`.

## Double-wishbone kinematic coupling

The dynamic system receives suspension hardpoints, not hand-entered curves,
instant centers, or jacking coefficients. The KinPy `CornerKinematics` adapter uses the original
`QuarterCar` constraint solver to derive contact-patch
and wheel-center migration; camber, toe, caster, KPI, trail, and scrub; and the
contact-patch tangent across wheel travel. At each corner's current jounce and
the commanded rack displacement, DynPy consumes one four-corner kinematic state. Steering headings are taken from the solved wheel
poses, including the linkage's Ackermann behavior. The existing `steering_rad`
input specifies mean front-wheel heading at nominal ride height and is converted
to rack travel through KinPy. `ModelInputs.rack_displacement_m` supplies rack
travel directly when provided. The reciprocal instantaneous
links remain:

```text
Fz_geometric / Fx = -dx_contact / dz_contact
Fz_geometric / Fy = -dy_contact / dz_contact
```

That returned state retains the requested `FL, FR, RL, RR` jounce vector. Each
`dyn_py` force evaluation exposes the individual jounces and rates together
with contact-patch position/tangent, wheel-center migration, camber, toe,
caster, KPI, mechanical trail, scrub radius, and longitudinal/lateral
instant-link coefficients. Transient results publish the same corner channels
with `FL`, `FR`, `RL`, and `RR` suffixes, so suspension motion can be inspected
without reconstructing it from chassis roll, pitch, and heave.

This is equivalent to the side-view and front-view swing-arm line of action,
but remains valid when the 3D wishbone pivot axes are swept and a simple 2D
hardpoint projection is not. Left/right geometry is mirrored at the lookup
boundary; longitudinal coefficients retain their axle sign.

The app selects cached KinPy evaluation automatically. Front corners use a
jounce/rack grid that fills as a run visits new regions. The 3 DOF model stays
on the zero-jounce steering row. Rear corners use jounce curves. Each front
cell is checked against an exact midpoint solve before interpolation. Failed
checks and travel outside the grid use the direct solve. Contact positions
and their jounce derivatives share the same interpolation polynomial.

The Python API retains `nonlinear` evaluation as a correlation reference.
The existing benchmark covers zero-rack travel curves:

```bash
make reduced-kinematics-benchmark
make reduced-eval REDUCED_KINEMATICS=nonlinear
```

Spring/damper and stabilizer-bar forces remain a separate elastic path. Spring
and damper tables are projected through the nominal geometry-derived motion
ratio to an equivalent wheel rate. Bar torsion is projected to axle roll stiffness and
applied as equal-and-opposite corner force. In 6/10DOF the massless-upright
closure is

```text
Fz_tire = Fz_spring/damper/bar + Fz_geometric
```

In 14DOF the geometric force acts upward on the sprung body and with equal and
opposite sign on the explicit unsprung mass.

Repeat the hardpoint-force correlation against a fresh BobLib FourPost report:

```bash
make standard-eval-four-post
make reduced-suspension-correlation
```

For the default vehicle used during implementation, the nominal longitudinal
jacking coefficients differed from BobLib by 2.23% at the front axle and 1.55%
at the rear. Symmetry predicts zero net axle heave from equal left/right lateral
force; BobLib returned residual coefficients below `8.4e-5`.

## QSS is a constraint on the transient model

QSS does not use a parallel force implementation. It evaluates the transient
equations and constrains selected generalized accelerations:

- constant-radius trim: all generalized accelerations are zero in the body
  frame; centripetal acceleration remains through `omega x v`;
- GGV point: path-tangential and path-normal accelerations are solved with
  constant sideslip and heading rate `psi_dot = an / V`. Retained body angular
  accelerations and world-vertical acceleration are zero. Wheel acceleration
  preserves the local slip ratio. At each normal demand, the solver maximizes and minimizes tangential acceleration under the
  same tire and actuator limits. The lateral endpoint maximizes normal
  acceleration with tangential acceleration free.
- YMD point: sideslip and steer are imposed, longitudinal/vertical/wheel states
  are equilibrated, and lateral acceleration plus yaw moment are outputs.

Acceleration and constant-radius trims solve rack travel directly. Tire loads
and massless-wheel slips are algebraic unknowns solved alongside body equilibrium.
MF5.2 is evaluated directly at those slips, without nested tire-force inversion.
These algebraic unknowns do not add dynamic DOFs. The GGV solver maximizes
each boundary with the same equations and retains the trim search as a fallback.
File-backed GGV runs solve speed slices in up to four separate processes.
Lateral samples within each slice retain their continuation order.
GGV checks independent tire-force inversion at the solved loads, then verifies
load and wheel-torque balance. Near tire peaks, transient evaluation starting
from static loads can select a different saturated branch. A valid QSS point
does not guarantee identical transient initialization.
Drive power is evaluated from wheel torque and angular speed. An upper tangential
acceleration limit can be negative when drag exceeds available propulsion.
`QSSResult` keeps its body-axis acceleration properties. GGV uses the explicit
`path_longitudinal_acceleration_mps2` and `path_lateral_acceleration_mps2` properties.

This is a local QSS approximation. Zero angular acceleration does not imply zero
yaw rate or, with a full inertia tensor, zero net moment. Along a real racing
line, `psi_ddot = curvature * at + V² * d(curvature)/ds` when sideslip is constant.
The envelope omits this yaw-acceleration demand and does not certify dynamic
stability. Continuation and optional multistart reduce local-solver failures,
but do not prove global optimality. The generated opposite-turn branch remains
a reflection, not an independent asymmetric solve.

QSS rejects equilibria outside each corner's fitted slip-angle or slip-ratio
range. GGV requires positive load at every wheel. Below `FZMIN`, the existing
tire model scales the wrench toward zero load. This region is outside the fitted
data. `enforce_tire_load_range` retains the upper `FZMAX` check. YMD still checks
both fitted load limits. GGV and lap workflows select numerical settings internally
and ignore legacy search controls in saved configs. Speed samples follow the
vehicle's drivetrain limit. Acceleration bounds expand until the envelope closes,
then lateral samples span the solved range. A failed search reports an error
rather than a clipped envelope. Multistart follows failed continuation. Sideslip
and roadwheel-steer limits remain model assumptions, recorded in lap summaries.


Select the backend in `simulations/envelope/ggv/ggv_config.yml` or `simulations/envelope/ymd/ymd_config.yml`:

```yaml
generation:
  model_dof: 6  # 3, 6, 10, or 14
```

## Transient runs and BobLib comparison

Run a reduced-order step steer from a solved straight-line trim:

```bash
make reduced-eval REDUCED_DOF=6
```

Compare common time histories with an existing OpenModelica result CSV:

```bash
make reduced-eval \
  REDUCED_DOF=10 \
  REDUCED_BOBLIB_CSV=simulations/mbd/BuildBobLib/VehicleSim/results/run_.../BobLib.Experiments.Standards.VehicleSim_res.csv
```

The comparison reports RMSE, range-normalized RMSE, maximum absolute error, and
bias for common channels such as `velX`, `velY`, `yawVel`, `sideslip`, `accX`,
`accY`, and `roll`. Steering inputs must represent the same roadwheel motion;
do not compare handwheel and roadwheel degrees without applying the steering
ratio.

For a real validation pass, run `standard-eval-transient`, retain its result
CSV, then compare all four reduced fidelities against the same case. Use the
error movement between adjacent fidelities to identify whether disagreement is
caused by body attitude, wheel rotation, unsprung motion, or physics that still
belongs only to BobLib.

The repeatable fidelity-discrimination suite makes that comparison directly:

```bash
make reduced-fidelity-suite
make reduced-fidelity-suite REDUCED_MBD_DIR=path/to/boblib_case_csvs
```

It writes common-axis 3/6/10/14DOF overlays under
`temp/fidelity_validation/`. When `REDUCED_MBD_DIR` is supplied, the directory
may contain `step_steer.csv`, `slalom.csv`, `brake_in_turn.csv`, and
`four_wheel_bump.csv`. Each available BobLib CSV is drawn as `MBD (BobLib)`, a
reduced-minus-MBD residual page is added, and RMSE/normalized RMSE/max error/
bias are written to JSON.

The cases are intentionally not redundant:

| Case | Difference it should expose | Lowest useful model |
| --- | --- | --- |
| Step steer | yaw/ay response and sprung roll buildup | 3DOF for planar response; 6DOF for roll |
| 1.2 Hz slalom | gain, phase, and transient load transfer | 6DOF |
| Brake in turn | combined slip, pitch transfer, wheel slip dynamics | 10DOF when wheel-speed transients matter |
| Four-wheel bump | tire vertical compliance, wheel hop, road input | 14DOF |

BobLib is the MBD implementation reference, not automatically physical truth.
Agreement with measured vehicle data remains the final validation layer. This
distinction is kept explicit in the artifact names and metrics.

Before BobLib correlation, run the internal all-fidelity acceptance bundle:

```bash
make lap-validation-visuals
```

This exercises model-specific GGV and YMD calculations and a complete QSS plus
transient lap for 3/6/10/14DOF. Inspect the generated figures under
`temp/lap_time_validation/`; this folder is disposable and gitignored.

## Current reduction limits

- Left and right corners have independent travel and opposite rack inputs,
  but their hardpoints still come from mirrored axle geometry. Midpoint checks
  limit interpolation error locally, but do not prove an error bound throughout
  every grid cell.
- Pushrod/bellcrank motion ratio remains a nominal tangent projection, and
  compliance plus detailed individual link loads remain BobLib validation
  targets.
- Tire forces and moments use BobLib's steady-state MF5.2 curves.
  Relaxation-length states are not included. The 3/6DOF models solve algebraic
  wheel slip within the tire fit bounds and reject trims that miss wheel torque
  demand, including rolling resistance. The 10/14DOF models obtain slip from
  wheel rotation with `J*omega_dot = torque + My - Fx*radius`. The chassis
  moment balance excludes torque accelerating wheel spin. Wheel gyroscopic
  coupling and steering inertia remain outside the reduced model.
- The powertrain is represented by wheel torque in the transient equations;
  the GGV and lap-controller power cap remains an outer feasibility constraint.
- The 32 kW endurance setting is a constant event cap, not an accumulator-energy
  or motor/inverter thermal state. A defensible endurance study must add those
  histories or treat the cap as a sensitivity case.
- Aero uses the nominal ride-height map projection rather than reevaluating the
  full map during body motion.
- The 14DOF road interface currently supports vertical road height/speed only.

The early Longhorn Racing Electric transient prototypes inspired the model
ladder and state-count convention, but BobSim's implementation is original.
The linked repository has no license file, and its incomplete source was not
copied.
