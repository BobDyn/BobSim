# Reduced-order vehicle dynamics

**TL;DR:** `_0_Utils/dyn_py` is a fast, inspectable reduced-order vehicle model for envelopes and transient lap simulation. Intentionally lower fidelity than BobLib but explicitly correlated against it. Choose 3/6/10/14 DOF to quantify the value of each added state.

BobSim also includes the original `_0_Utils/kin_py/` kinematics — used for detailed suspension-element workflows, independent and backward-compatible.

## Using the unified vehicle interface

```python
from _0_Utils.dyn_py import Vehicle

vehicle = Vehicle.from_yaml()
wheel_state = vehicle.kinematics_at([0.01, -0.01, 0.0, 0.0])  # all four wheels
model_14dof = vehicle.model(14)                               # 14DOF transient
trim = vehicle.steady_state(14, speed_mps=12.0)              # QSS trim at 12 m/s
```

The vehicle definition and kinematics lookup are built once and shared across all DOF models. Lower-level functions (`create_kinematics`, `create_model`, QSS, transient) remain public for specialized use.

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
- 10/14DOF: unsprung masses integrated separately; 14DOF adds tire vertical compliance

**Tire model:**
- Contact patch position/velocity from kinematics evaluator (includes bump toe, camber, migration effects)
- Slip evaluated in individual wheel frames
- Load-sensitive peak and cornering-stiffness from Magic Formula
- Combined-slip ellipse with saturation

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

Aerodynamic downforce is applied at the center of pressure inferred directly
from the nominal `vehicle.yml` downforce and free-pitch-moment maps. The rigid
body receives the equivalent CG wrench
`F_aero, r_CG_to_CoP x F_downforce`; drag remains applied at `aero_ref_m`.
The reported front aero balance is derived from that CoP for the planar axle
load closure. The CoP is not clipped to the wheelbase, because doing so would
change the map's pitch moment.

`vehicle.yml` supplies geometry, component mass/inertia, wheel/tire values,
suspension tables, aero maps, and powertrain layout. When available, the
FourPost metrics CSV supplies measured/projected wheel and anti-roll stiffness;
the YAML shock tables are the fallback.

## Double-wishbone kinematic coupling

The dynamic system receives suspension hardpoints, not hand-entered curves,
instant centers, or jacking coefficients. The `dyn_py` kinematics surface uses the
shared nonlinear `CornerKinematics` constraint solver to derive contact-patch
and wheel-center migration; camber, toe, caster, KPI, trail, and scrub; and the
contact-patch tangent across wheel travel. At the current corner jounce,
`dyn_py` consumes one four-corner kinematic state. The reciprocal instantaneous
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

Two interchangeable backends are available:

- `lookup` (default) solves the hardpoints once at vehicle load, then uses
  interpolation during QSS and ODE evaluations;
- `nonlinear` solves each corner and the centered contact-patch derivative
  inside every force evaluation. It is intended for short correlation runs and
  as the accuracy reference for choosing a lookup grid.

Run the repeatable trade study or a short exact-kinematics transient with:

```bash
make reduced-kinematics-benchmark
make reduced-eval REDUCED_KINEMATICS=nonlinear
```

On the default vehicle, the 49-point lookup built in about 0.67 s and differed
from off-grid nonlinear solutions by at most 2.25 micrometers at the contact
patch, 0.00014 degrees camber, 0.00010 degrees toe, and `4.6e-6` in an
instant-link coefficient. A 14DOF force evaluation took about 1.5 ms with the
lookup and 165 ms with in-loop solves on the development machine. Grid density
has negligible interpolation-time cost, so 49 points remains the default.

Spring/damper and stabilizer-bar forces remain a separate elastic path. Spring
and damper tables are projected through the BobLib/FourPost motion ratio to an
equivalent wheel rate. Bar torsion is projected to axle roll stiffness and
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
- prescribed GGV point: body `ax/ay` are prescribed at zero yaw rate while yaw,
  vertical, rotational, wheel-speed, and unsprung accelerations are
  equilibrated. Curvature and steering-radius feasibility belong to the track
  solver, not the acceleration-capability envelope. The acceleration and brake
  branches share a separately solved pure-lateral coast endpoint, so the map is
  closed at the true lateral limit rather than the final feasible grid slice;
- YMD point: sideslip and steer are imposed, longitudinal/vertical/wheel states
  are equilibrated, and lateral acceleration plus yaw moment are outputs.

The unknown set grows naturally with fidelity: body sideslip/steer/drive torque,
then heave-roll-pitch, then four wheel slips, then four unsprung positions.

Finite tire-fit bounds are validity constraints. GGV and YMD cells are rejected
when any normal load falls outside the active `.tir` file's `FZMIN`/`FZMAX`
range; warning-only extrapolation is available only through an explicit config
override. Study-grade GGV and lap configs enable a deterministic beta/steer
multistart search after the warm start fails, which protects the reported
boundary from a disconnected local trim branch. The routine all-DOF visual
smoke config disables that expensive audit explicitly. Sideslip and roadwheel-
steer bounds remain study assumptions and are written into lap summaries.

Select the backend in `GGV/ggv_config.yml` or `YMD/ymd_config.yml`:

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
  REDUCED_BOBLIB_CSV=_3_StandardSim/BuildBobLib/VehicleSim/results/run_.../BobLib.Experiments.Standards.VehicleSim_res.csv
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

- The current map is one-dimensional in jounce. It captures fixed-rack bump
  steer, but commanded roadwheel steer is added afterward; rack travel,
  Ackermann, and steer-dependent camber/caster/trail require a future 2D
  jounce-by-rack map.
- Pushrod/bellcrank motion ratio remains a static FourPost projection, and
  compliance plus detailed individual link loads remain BobLib validation
  targets.
- The tire is a compact MF-derived saturation model, not the full MF52/MF6.2
  equation set, and has no relaxation-length states.
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
