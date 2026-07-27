# FbrcEval — Force-Based Roll Center Study

Date: 2026-07-26
Status: design, approved-by-default (user delegated implementation without a review gate)

## 1. Goal

Add a BobSim study that computes the **front and rear Force-Based Roll Center
(FBRC)** for a given vehicle model.

The deliverable is the FBRC height of each axle as a function of operating point
(lateral acceleration), together with the per-corner force lines that produce it
and the kinematic roll center (KRC) for comparison.

## 2. Theory

### 2.1 What the FBRC is, and why it is not the KRC

The **kinematic roll center** (KRC, SAE J670) is a geometric construction: in
front view, draw a line from each contact patch to that corner's front-view
instant center; the intersection of the left and right lines is the KRC. The
construction is purely geometric and implicitly assumes the left and right tires
produce **equal** lateral force.

The **force-based roll center** drops that assumption. It is defined by the
forces the suspension linkage actually transmits to the sprung mass:

> The FBRC is the point at which the resultant of the link-borne (non-elastic)
> forces from an axle acts on the sprung mass. Equivalently, it is the height at
> which the axle's total lateral force must be applied to reproduce the observed
> **geometric** (spring-deflection-free) lateral load transfer.

The KRC is the special case of the FBRC when both tires carry equal lateral force
and the geometry is left/right symmetric (verified in §2.6). The FBRC is
therefore strictly more general, and it does not degenerate when the instant
centers run to infinity (parallel control arms), which is the classic failure
mode of the KRC.

### 2.2 Coordinate and sign conventions

BobLib's world frame, confirmed from the model
(`world(n = {0, 0, -1})`, hardpoint signs, `Vector.mirrorXZ`):

| Axis | Direction |
|------|-----------|
| `x`  | forward (rear of car is negative `x`) |
| `y`  | **left** positive |
| `z`  | up |

Right-handed. Gravity is along `-z`. This is an ISO-like frame, **not** the SAE
`x`-forward/`y`-right/`z`-down frame — every sign below follows BobLib's frame.

Moment about the `x` axis of a force `F` applied at position `r`:
`M_x = y·F_z − z·F_y`.

Heights are measured in world `z`, i.e. from the ground plane `z = 0`.

### 2.3 Splitting the corner load into geometric and elastic parts

Consider one corner. With steering locked it has a single suspension degree of
freedom (the ride/jounce DOF). Parameterise it by `ζ`, the contact-patch vertical
position relative to the chassis, so that by construction `∂z_CP/∂ζ = 1`.

Let the tire apply the wrench `(F, M)` at the contact patch, where
`F = (F_x, F_y, F_z)`. The **generalized force** on the ride DOF is

```
Q = F · (∂r_CP/∂ζ) + M · (∂φ/∂ζ)
  = F_x·(∂x_CP/∂ζ) + F_y·(∂y_CP/∂ζ) + F_z + M · (∂φ/∂ζ)
```

In equilibrium `Q` is exactly what the spring / damper / anti-roll bar has to
react — it is the **elastic** part of the corner load, the part that deflects the
suspension. The total vertical force delivered to the sprung mass is `F_z`, so
the part carried by the **rigid links** is the remainder:

```
F_z_geom = F_z − Q
         = −[ F_x·(∂x_CP/∂ζ) + F_y·(∂y_CP/∂ζ) + M · (∂φ/∂ζ) ]        (1)
```

Equation (1) is exact, fully three-dimensional, valid for any linkage topology,
and requires **no instant-center construction**. It is the generalization of the
"n-line" / force-line concept.

For a pure lateral load it reduces to

```
F_z_geom = −F_y · (∂y_CP/∂ζ)                                          (2)
```

so the force-line inclination is

```
tan θ = −∂y_CP/∂ζ = −∂y_CP/∂z_CP                                      (3)
```

i.e. **the negated lateral-scrub-per-jounce gradient**. Equation (3) is the
bridge to the classical construction: for a planar double-A-arm the contact patch
instantaneously rotates about the front-view instant center, so its velocity is
perpendicular to the radius from the IC, giving
`tan θ = (z_IC − z_CP)/(y_IC − y_CP)` — the slope of the line from the contact
patch to the instant center, which is exactly the classical force line.

### 2.4 Assembling the axle FBRC

The link-borne force at corner `i` acts along the force line, which passes
through the contact patch. So the sprung mass sees, at corner `i`, a force with
lateral component `F_y,i` and vertical component `F_z_geom,i`, applied on a line
through `(y_i, z_i) = (y_CP,i, z_CP,i)`.

Taking moments about the `x` axis through the world origin (ground level, vehicle
centerplane):

```
M_x = Σ_i [ y_i · F_z_geom,i − z_i · F_y,i ]                           (4)
```

An equivalent single lateral force `F_y = Σ_i F_y,i` acting at height `h` on the
centerplane (`y = 0`) produces `M_x = −h·F_y`. Equating:

```
h_FBRC = − M_x / F_y
       = [ Σ_i F_y,i·z_i − Σ_i y_i·F_z_geom,i ] / Σ_i F_y,i            (5)
```

Substituting (2) for the pure-lateral case gives the compact form

```
h_FBRC = Σ_i F_y,i · h_i / Σ_i F_y,i        where  h_i = z_i − y_i·tan θ_i   (6)
```

`h_i` is the height at which corner `i`'s force line crosses the vehicle
centerplane. **So the FBRC height is the lateral-force-weighted mean of the
per-corner force-line centerplane heights.** This matches the form quoted in the
literature (Mitchell; Milliken & Milliken, *RCVD* ch. 17–18) and is derived here
from first principles rather than assumed.

**Which terms of (1) enter the FBRC.** A roll center is by definition the point
through which *lateral* force acts, and the denominator of (5) is `Σ F_y,i`.
Folding the `F_x` and `M` terms of (1) into the numerator would therefore
contaminate the height with longitudinal- and moment-driven jacking divided by a
lateral force. So `h_FBRC` uses the lateral term only:

```
F_z_geom_lat,i = −F_y,i·(∂y_CP,i/∂ζ) = F_y,i·tan θ_i                   (7)
```

The `F_x` and `M` contributions of (1) are computed and reported **separately**
as longitudinal and moment jacking, not merged into the roll center. Both forms
are implemented; only (7) feeds `h_FBRC`.

### 2.5 Auxiliary quantities reported

- **Axle jacking force** `F_z_jack = Σ_i F_z_geom,i`. Note this is the *sum*,
  whereas `h_FBRC` needs the *moment* (a difference). For a symmetric axle with
  equal left/right lateral force the sum is identically zero while the moment is
  not — jacking is driven by left/right force **asymmetry**. This is why the
  existing `FourPostEval` jacking-based metrics do not yield a roll center
  (see §5.3).
- **Geometric lateral load transfer** `ΔF_z_geom = M_x_geom / t`, and the
  geometric share of total load transfer (the classical "anti-roll" fraction).
- **Ground-plane crossing** `y_ground = M_x / F_z_jack` — the lateral position
  where the resultant line of action crosses `z = 0`. Reported when
  `F_z_jack` is non-negligible. A planar force system reduces to a resultant
  along a *line*, not a point, so `h_FBRC` (crossing of `y = 0`) and `y_ground`
  (crossing of `z = 0`) together define that line. `h_FBRC` is the primary
  number because it is what enters the load-transfer equation.
- **Kinematic roll center** — intersection of the two force lines, reported for
  comparison, plus `h_FBRC − h_KRC` to expose the force-weighting effect.

### 2.6 Validation cases (all become unit tests)

| Case | Expected |
|------|----------|
| Symmetric geometry, equal `F_y` | `h_FBRC = h_KRC` = force-line centerplane crossing |
| Parallel horizontal control arms | `tan θ = 0`, `h_FBRC = 0` (RC at ground), KRC undefined/at infinity — FBRC stays finite |
| Force lines through the ground centerplane | `h_FBRC = 0` regardless of force split |
| All lateral force on one corner | `h_FBRC = h_i` of that corner |
| Force split swept symmetric→asymmetric | `h_FBRC` moves monotonically between `h_L` and `h_R` |
| Sign flip of both `F_y` | `h_FBRC` unchanged (it is a ratio) |
| Analytic swing-arm corner | `tan θ` matches closed form to 1e-9 |

## 3. What the model provides

Investigated `BobLib` (see §5 for the full findings). Relevant facts:

- The **only** suspension family is the double A-arm, in `Direct`/`BC`/`BC_Stabar`
  actuation variants, front and rear (`AxleDWBase` → `{Fr,Rr}AxleDW_*`).
- BobLib computes **no** roll center, instant center, force line, n-line or
  swing-arm quantity anywhere. All of that is new work.
- It is a genuine 3-D `Modelica.Mechanics.MultiBody` model, so every hardpoint
  is available as a frame with world position `r_0`, orientation `R`, and cut
  force/torque `f`/`t`.
- Public per-corner frames on an axle instance (`chassis.frAxleDW`, `chassis.rrAxleDW`):
  - `leftCP.r_0`, `rightCP.r_0` — contact patch position, and `.R` its orientation
  - `leftWishboneUprightLoop.upperFrame_o.r_0` / `.lowerFrame_o.r_0` — outboard ball joints
  - `leftWishboneUprightLoop.upperFrame_i.r_0` / `.lowerFrame_i.r_0` — inboard arm-axis midpoints
  - `leftTieRod.frame_a.r_0` (rack pickup) / `.frame_b.r_0` (`tie_o`)
  - `leftTire.Fx`, `leftTire.Fy`, `leftTire.Fz`, and the CP cut force `leftTire.cpFrame.f`
- The inboard **axis directions** are not published as frames (the fore/aft
  translations are `protected`), but they are known parameters in the vehicle
  record (`pDW.upperFore_i − pDW.upperAft_i`, chassis frame) and are rotated to
  world using each arm's own inboard frame orientation
  (`{side}WishboneUprightLoop.{upper,lower}Frame_i.R.T`) — see §5.10 for why the
  chassis reference frame is not usable for this.
- `VehicleSim`'s default `variableFilter` excludes suspension internals, but the
  study controls `simulation.variable_filter`, so the signals above can be
  requested without modifying BobLib.

**Consequence: no BobLib/Modelica change is required.** The entire study is
additive inside BobSim. This was a deliberate goal — the alternative (new
Modelica instrumentation) could not be compiled or verified in this environment
(§6).

## 4. Design

### 4.1 Operating points

FBRC is operating-point dependent, so it must be evaluated at a real attitude
with real tire forces. The study reuses the proven closed-loop steady-state
cornering mode that `SteadyStateEval` uses (`VehicleSim`, `vcu.useMode = 3`),
sweeping target lateral acceleration at one or more speeds. At each settled
point the model supplies the corner geometry at the true rolled/steered attitude
**and** the genuinely asymmetric tire lateral forces — which is precisely what
makes the result force-based rather than kinematic.

Extraction mode is `"last"` (one scalar per signal at the settled final row),
matching `SteadyStateEval`.

### 4.2 Force-line solver (the physics core)

New module `_0_Utils/suspension/force_line.py`. Pure NumPy, no Modelica, no I/O.

For one corner at one instant, given world-frame positions of the inboard axis
point + direction (upper and lower), the outboard ball joints, the tie-rod ends,
and the contact patch, it solves for the corner's instantaneous **twist**
(`ω`, `v`) relative to the chassis:

- Upper outboard point is on a revolute about the upper inboard axis →
  its velocity direction is constrained; eliminating the arm rate leaves
  **2** scalar constraints.
- Lower outboard likewise → **2** constraints.
- Tie rod length is constant → **1** constraint.

That is 5 constraints on the upright's 6-DOF twist, leaving the expected
**1 DOF**. The solver takes the null space (via SVD), normalises it so that
`ż_CP = 1` (i.e. `ζ` is contact-patch vertical travel), and returns

```
∂r_CP/∂ζ  = (∂x_CP/∂ζ, ∂y_CP/∂ζ, 1)      and      ∂φ/∂ζ = ω/ż_CP
```

From these, equations (1)–(3) give `F_z_geom`, `tan θ`, and `h_i`. The
front-view instant center is *also* recovered (for the KRC comparison) as the
point where the force line meets, but it is never required for the FBRC itself.

Rationale for solving the twist rather than projecting arms into the y–z plane:
the 2-D projection is an approximation for a 3-D linkage (the arms' axes are not
parallel to `x`, and the tie rod contributes), and it degenerates for parallel
arms. The twist formulation is exact and never degenerates.

### 4.3 Study module

`_3_StandardSim/FbrcEval/fbrc_eval_sim.py`, following the framework contract
established by `SteadyStateEval`:

- `FBRC_EVAL_SIGNALS` — the per-corner frame/force signal list plus chassis attitude
- `FbrcEvalSim.__init__(config)` — backend guard, `variable_filter` default, `ModelicaRunner.from_config`
- `build_cases()` — velocity × target-`a_y` grid, `useMode = 3`, `_`-prefixed metadata
- `run()` — `runner.run(..., mode="last", ...)`
- `summarize(results)` — per case, build the four corner geometries, solve force
  lines, assemble front/rear FBRC via (5); emit `summary`, `metrics`, `series`, `cases`
- `write_metrics_csv(metrics)` — long-form schema (`standard,metric,value,units,description`)
- `main(path)` + `__main__`

Config `_3_StandardSim/FbrcEval/fbrc_eval_config.yml` with `standard: FbrcEval`,
`-jacobian=internalNumerical` in `simulation.extra_args`, the `VehicleSim`
entrypoint, and `report.output_path` under `_3_StandardSim/generated_results/`
(all three are enforced by existing tests).

### 4.4 Reported metrics

Per axle: `h_fbrc_mm` (mean and vs `a_y`), `h_krc_mm`, `fbrc_minus_krc_mm`,
`fbrc_migration_mm_per_g`, per-corner `force_line_angle_deg` and
`force_line_centerplane_height_mm`, `jacking_force_N`,
`geometric_load_transfer_N`, `geometric_lltd_fraction`. Plus front/rear
`geometric_lltd_pct` and the roll-axis inclination implied by the two axle FBRCs.

### 4.5 Integration

- `_5_App/sim_configs/_defaults/fbrc.yml`
- `_5_App/registry.py`: `ConfigSpec`, `ActionSpec` `run-fbrc`, `WorkflowSpec` (`build-vehicle`, `run-fbrc`)
- `_5_App/app.py`: `MODELICA_RUN_TARGETS_BY_ACTION["run-fbrc"] = vehicle`
- `_0_Utils/reporting/report_engine.py`: `FbrcEval` summary branch + `sections.py` page
- `makefile`: `standard-eval-fbrc`, added to `standard-eval-all` and `help`
- `tests/`: force-line unit tests (§2.6), `build_cases` test, config added to
  `STANDARD_CONFIGS`/`STANDARD_ENTRYPOINTS`

### 4.6 Error handling

The physics core raises on genuinely ill-posed input (degenerate axis, singular
constraint set, `ż_CP ≈ 0`) and returns `None`/`NaN` for quantities that are
legitimately undefined (KRC with parallel force lines). The study skips failed or
unsettled cases the way `SteadyStateEval` does, records the reason, and never
silently substitutes a different quantity.

## 5. Findings and issues from the investigation

### 5.1 No existing roll-center capability in BobLib
Grepped the whole package for instant center / roll center / n-line / force line /
swing arm / anti-squat / motion ratio: no hits in equations, variables, or docs.
BobLib deliberately captures suspension behaviour through the MultiBody kinematic
loop rather than 2-D geometric constructions.

### 5.2 An unrelated Python roll-center implementation already exists
`_5_App/kinematics.py` has a self-contained double-wishbone kinematic solver
(`CornerKinematics`) that computes front-view instant centers and a roll center
(`roll_center()` is the force line's centerplane crossing). It is a **kinematic**
(geometry-only) preview for the browser app, driven from `vehicle.yml`, not from
the Modelica model, and it uses the 2-D projection approximation. It is a useful
cross-check but is not the FBRC and is not reused as the source of truth.

### 5.3 `FourPostEval`'s jacking metrics are not a roll center
`FourPostEval` computes `avg_anti_roll_front_pct` from
`ΔF_z_jack / F_y ÷ (h_cg/t)`, where `F_z_jack` is
`ChassisActuator.sprungLoads.force[3]` — the **net vertical** cut force, and its
fallback substitutes `leftFz + rightFz`, also a sum. A roll center requires the
**antisymmetric** part (the roll couple); the symmetric part is heave jacking.
As shown in §2.5 the sum vanishes for a symmetric axle with equal left/right
lateral force while the roll couple does not. So these existing metrics are
lateral/longitudinal jacking coefficients, not roll centers, and FBRC is genuinely
new information. Not a bug in `FourPostEval` — just a different quantity, worth
recording so the two are not confused.

### 5.4 The four-post rig cannot currently produce an asymmetric FBRC
`BaseFourPostSim` drives all four `ContactPatchForceActuator`s from one shared
`final parameter fyTable` with `forceMagnitude/2` each, so left and right lateral
forces are always equal — exactly the assumption FBRC exists to relax. `fyTable`
and `fxTable` are `final`, so they cannot be overridden from a case. The rig is
still the natural instrument for *validating* the force-line math (prescribed
pose, `g = 0`, measured jacking), and doing so would need either per-actuator
`forceMagnitude` overrides (overridability unverified — `_init.xml` needed) or a
small BobLib change. Deferred, documented in §7.

### 5.5 Left/right sign asymmetries in the existing KnC math
In `BaseFourPostSim`, left KPI uses `atan(−v[2]/v[3])` while right uses
`atan(v[2]/v[3])`, and `MechScrub` flips operand order between sides. These are
deliberate mirroring conventions but are easy to misread. The new code derives
left/right consistently in the world frame and applies no per-side sign flips, so
it does not inherit this hazard.

### 5.6 Dormant/unwired assets
`Records/in-progress/VisualRecord/.../AxleDWBaseVisualRecord.mo` already declares
almost exactly the per-corner geometry+load bundle this study needs
(`leftUpper_o`, `leftTie_i/o`, `leftWheelCenter`, `leftCP`, `leftCPForce`), but it
is unreferenced and its `within` clause does not match its on-disk path, so it is
not part of the loaded package. Not used. There is also a remote
`origin/KnC-FMI` branch that may hold related work.

### 5.7 The FBRC only departs from the KRC when the *geometry* is asymmetric too

Found while testing. Unequal left/right lateral force is necessary but not
sufficient. With mirror-symmetric geometry both corners have the same force-line
centerplane height `h_L = h_R`, and any weighted mean of two equal numbers is that
same number — so `h_FBRC = h_KRC` no matter how lopsided the force split is. What
asymmetric force *does* change even then is the **jacking force**, which is zero
at equal force and grows with the imbalance.

The FBRC therefore separates from the KRC only once the two force lines differ,
which in practice means in roll (or with asymmetric setup / one wheel light). This
is why the study sweeps lateral acceleration instead of reporting a single number:
at zero roll the two definitions coincide by construction, and the interesting
divergence appears as roll builds. Both behaviours are pinned by tests so the
expectation is not later mistaken for a bug.

### 5.8 Load transfer must use the *force-weighted* contact-patch plane

Also found while testing, then sharpened by review. The model's static contact
patch sits at `z = -4.6 mm`, not at `z = 0`, because the nominal geometry places
the wheel center one *unloaded* tire radius above the patch. The geometric forces
are reacted at the tires, so the load-transfer moment arm is the FBRC height
measured from the contact-patch plane. Using the world-`z` height instead is a
silent ~17 % error in `geometric_load_transfer` for this vehicle.

Sharper point: that datum must be the **lateral-force-weighted** mean patch
height, not the arithmetic mean. With the arithmetic mean the identity

```
geometric_load_transfer = -lateral_force * height_above_contact_patch / track
```

is off by `(z_L - z_R)(Fy_L - Fy_R) / (2*track)` — nonzero exactly when the two
patches sit at different heights **and** the tires carry different lateral force,
which is precisely the rolled cornering condition this study targets. For 8 mm of
patch split and a 1000 N force split on a 1.21 m track that is 3.3 N against a
~43 N transfer, about 8 %. With the weighted datum the identity is exact (verified
to 1e-9). A test now covers the doubly-asymmetric case; the original
mirror-symmetric test could not have caught it, because `z_L == z_R` there.

### 5.9 Roll-center heights must never be compared across datums

Found in review. `kinematic_height` is a world-`z` value while
`height_above_contact_patch` is patch-relative, so plotting one against the other
showed a constant ~4.6 mm gap even where the two definitions genuinely coincide —
contradicting the `fbrc_minus_krc_mm` metric, which correctly differences two
world-`z` values. Fixed by adding `kinematic_height_above_contact_patch` plus a
`*_krc_height_above_cp_mm` series and metric, and pointing the report overlays at
it. A test asserts the difference is datum-independent.

### 5.9 A tie rod aimed at the kingpin axis leaves the corner with 2 DOF

Caught by the solver rejecting a test fixture I had written. If `tie_o` lies on
the line through `lower_o` and `upper_o`, the tie-rod constraint cannot restrain
rotation about the kingpin, so the corner has two instantaneous degrees of freedom
and the force line is undefined. The solver detects this as a rank-deficient
constraint set and raises rather than silently returning one of the two solutions.
Worth knowing because it is an easy mistake to make in a synthetic geometry.

### 5.10 Chassis torsional compliance rules out using one chassis frame

Found during implementation, and it changed the design. The first version rotated
the arm-axis directions into world with `chassis.chassisFrame.R.T`. That is wrong
for BobLib's default vehicle: `Chassis_DW` redeclares the space frame as
`Body.FrameCompX`, which inserts a **torsional revolute about x** (plus spring and
damper, rate `pVehicle.pTorsionalStiff`) between the front and rear axle mounts.
Under a cornering load the rear axle frame is therefore twisted relative to the
chassis reference frame, and using one shared orientation would corrupt the rear
axle's force lines by the chassis twist angle.

The implementation now resolves each axle's corner geometry into that axle's own
**mounting frame** (`chassis.detailedChassis.{frAxleFrame,rrAxleFrame}`), the frame
`DetailedChassisBase` connects the axle's `axleFrame` to. This removes the
assumption entirely rather than correcting for it.

The compiled model confirms the split independently: OpenModelica's alias
resolution maps the front arm frames' `R.T` onto `chassis.chassisFrame.R.T` but the
rear arm frames' `R.T` onto `chassis.detailedChassis.rrAxleFrame.R.T`. They are
genuinely distinct variables, and `spaceFrame.torsionalRevolute.phi` appears in the
compiled state vector.

MSL's own definitions (`resolve1(R,v) = transpose(R.T)*v`,
`resolve2(R,v) = R.T*v`, read from `Modelica 4.1.0` source in the Docker image)
confirm `R.T` maps world into the local frame, so `R.T @ (p_world - r_0)` is the
correct world-to-local transform.

### 5.11 Corner positions are world-frame and must be resolved (found by running it)

The bug that only an end-to-end run could expose, and the reason the first real run
produced nonsense.

Every `r_0` signal MultiBody publishes is resolved in the **world** frame. The FBRC
is a front-view construction in the vehicle's own y-z plane: `tan(theta) =
-dy_cp/dz_cp` needs the *vehicle* lateral axis, and `centerplane_height = z_cp -
y_cp * tan(theta)` needs `y` measured from the *vehicle centerplane*. The first
implementation fed world coordinates straight into the solver.

At the origin with the car axis-aligned the two frames coincide, so all 41
synthetic unit tests passed -- they hand-build geometry in vehicle coordinates. In a
real closed-loop run at 9.96 m/s^2 the car sits at world `[23.9, 40.3, 0.19]`,
yawed far off the world axes, and the numbers become:

| quantity | world frame (wrong) | axle frame (correct) |
| --- | --- | --- |
| front left centerplane height | +1604 mm | -33.9 mm |
| front FBRC above contact patch | -406 mm | -35.9 mm |
| front FBRC - KRC | -387 mm | -1.01 mm |
| geometric LLTD front share | 124 % | 68.1 % |

The fix resolves every corner position into the axle mounting frame before solving.
Two properties of that frame, verified numerically against the compiled model, make
it the right choice and simplify the code:

- **Its `y = 0` is the vehicle centerplane.** Resolved inboard hardpoints come out
  exactly mirror symmetric (`y_left + y_right = 0.000000`). Contact patches show
  `y_left + y_right = -0.99 mm`, which is real lateral tire scrub under cornering,
  not frame error.
- **It is a pure translation of the vehicle-definition frame.** Resolved `y` matches
  `vehicle.yml` to seven digits (0.2367 front, 0.2905 rear). So the record's axis
  *directions* need no rotation at all, and `_CORNER_ORIENTATION_SIGNALS` (four 3x3
  matrices per axle) was deleted in favour of one frame per axle.

Pinned by `test_fbrc_eval_geometry_is_invariant_to_world_pose`, which builds the
same corner at the origin and at `[240, -37.5, 0.19]` yawed 63 deg and requires
`tan_theta` and `centerplane_height` to agree to 1e-9; a world-frame implementation
fails it. `test_fbrc_eval_axle_frames_are_mounts_of_their_axle` additionally asserts
against BobLib source that these frames really are the axle mounts, so the choice
cannot silently drift.

### 5.12 Protected variables need `-emit_protected` (found by running it)

Every signal this study reads -- frame origins, orientation matrices, tire forces --
is declared `protected` inside its component. OpenModelica omits protected variables
from the result file **regardless of `-variableFilter`**, so the first run completed
all 10 cases and then failed with `Signal not found in result CSV:
...frAxleDW.leftCP.r_0[1]`, having emitted only the 12 public scalars.

The runtime flag `-emit_protected` fixes it with no rebuild; it is now in
`extra_args` in both configs with the reason recorded inline. With it the run emits
270 columns and every requested signal is present. (Counts here are from the
diagnosis run, before §5.11 replaced the 72 per-arm orientation entries with 24
axle-frame ones; the final study requests 130 signals and emits 213 columns.)

Worth noting for future studies: a `variableFilter` that matches nothing is
**silent** -- no warning that a requested pattern matched zero variables.

### 5.13 `-march=native` breaks every Modelica build on aarch64

Pre-existing and unrelated to FBRC, but it blocks all three build scripts on Apple
Silicon: `clang: error: the clang compiler does not support '-march=native'`. The
model itself is fine -- the frontend produced 95 linear and 42 nonlinear systems
before the C stage failed.

`build_vehicle_sim.mos`, `build_four_post_sim.mos`, and
`_4_OptSim/StandardSens/configs/build_template.mos` now probe the compiler
(`clang -march=native -x c -c /dev/null`) and fall back to `-mcpu=native`, the
aarch64 spelling. x86 behaviour is unchanged.

### 5.14 `_4_OptSim` build template cannot be rendered (pre-existing, not fixed)

`compiler.py:render_mos()` fills the template with `str.format()`, but the template
contains literal Modelica braces (`loadModel(Modelica, {"4.1.0"})`) that are not
escaped as `{{...}}`. Any call raises `KeyError: '"4'`. Verified against unmodified
`HEAD`, so it predates this work and is independent of the arch-flag change above.
Left alone as out of scope; reported to the user.

### 5.15 Two copies of BobLib in the tree
`sources/BobLib` (standalone checkout, version 0.1.1) and
`sources/BobSim/_0_Utils/external/BobLib` (submodule, version 0.1.0). Contents are
identical apart from that version metadata. The build scripts use the
**submodule**. Investigation read the standalone copy; no changes were made to
either.

## 6. Execution: verified end-to-end against the real model

The model **is** built and the study **has** been run end-to-end against
`BobLib.Experiments.Standards.VehicleSim`, which extends
`Templates.Vehicle.VehicleSim_EVBatInvMotDiff_DWBCStabar_DWBCStabar` and binds
`BobLib.Records.VehicleDefn.EVBatInvMotDiff_DWBCStabar_DWBCStabarRecord`.

The record's suspension hardpoints were checked against `vehicle.yml` component by
component: all 12 arm-axis components, front and rear, match exactly. That matters
because `make sync-vehicle` documents that the BobLib models use checked-in
Modelica records while `vehicle.yml` is a BobSim-side projection, and the axis
directions are the study's one non-model input.

### 6.1 Environment note (historical)

An earlier attempt could not compile: the Colima VM had 2 GB of RAM and every build
was OOM-killed (exit 137). Raising it needed a Colima restart that would have killed
8 unrelated running containers, so it was left alone and the architecture was
arranged to keep all physics in a pure-Python, Modelica-free module that *is* fully
testable without `omc` (§2.6). The VM now has 8 GiB and the model compiles.

That constraint turned out to be worth designing around for a second reason: two of
the three bugs in §5.11-5.13 are only reachable by running the real model, and the
pure-Python core is what made the fix for §5.11 a two-line change in the adapter
rather than a rewrite of the physics.

### 6.2 Verification performed

**Signals.** All 130 signals the study requests were checked against the 35 332
names in the compiled `_init.xml`: 0 missing, 0 unmatched, 0 matched-but-unwanted.
The grouped-regex `variableFilter` (605 chars, vs several kB if enumerated) passes
exactly those 130 names. Breakdown: 24 axle-frame (2 x [3 r_0 + 9 R.T]), 84 corner
positions (2 x 2 x 7 x 3), 12 corner tire forces, 10 vehicle scalars. All 25
`init_parameters` resolve to real model variables through
`MODELICA_OVERRIDE_ALIASES` (they live under `vcu.`).

**Physics, three independent cross-checks on real run data** (not self-consistency):

| check | independent route | worst disagreement |
| --- | --- | --- |
| KRC | elementary 2-D intersection of the two force lines from contact patches and angles only | 2.8e-14 mm |
| FBRC | literature's force-weighted-mean-of-corner-heights form vs the moment-balance route the code uses | 5.6e-14 mm |
| `tan(theta)` | nonlinear finite-difference: displace the upright, re-close the linkage by Newton iteration on the rigid-link constraints, difference the contact patch | 1.5e-08 (consistent with `O(h^2)` at `h=2e-4`) |

The third is the strongest: it validates the 5x6 SVD null-space twist solve against
the actual constraint manifold rather than against itself.

**Load-transfer identity.** `dFz_geom = -Fy_axle * h_above_cp / track` holds to
**5.0e-14 N** across all 10 settled points, confirming the force-weighted
contact-patch datum of §5.8 on real asymmetric data.

**Cross-validated against `_5_App/kinematics.py`**, an independently written solver
using `scipy.optimize.root` and the classical 2-D instant center. Over ±30 mm jounce
the two agree to **< 0.3 mm** of roll-center height; the residual is the genuine 3-D
terms the 2-D projection drops. The two share no code.

**Gate.** `ruff`, `mypy`, and the full `pytest` suite pass in `bobdyn/bobsim:latest`.

### 6.3 Results for the current vehicle ("sample_vehicle")

10/10 cases settled, `a_y` from 0.95 to 9.96 m/s^2 at 15 m/s. Sweep-mean values:

| | front | rear |
| --- | --- | --- |
| FBRC above contact patch | -35.9 mm | -20.8 mm |
| KRC above contact patch | -34.9 mm | -19.3 mm |
| FBRC - KRC | -1.01 mm | -1.56 mm |
| migration | -2.15 mm/g | -2.34 mm/g |
| force line, left / right | +2.68 / -3.85 deg | +1.29 / -2.42 deg |
| jacking force | -19.9 N | -12.4 N |
| geometric load transfer | 24.2 N | 11.3 N |

Force-based roll axis is 15.1 mm nose-down; geometric LLTD is 68.1 % front.

Both roll centers are **below** the contact-patch plane, so the geometry is
anti-jacking and the small negative jacking force is consistent. The `a_y` sweep
behaves exactly as §5.7 predicts: at 0.95 m/s^2 the corners are near-symmetric
(+3.08 / -3.31 deg) and FBRC - KRC is only **0.03 mm**; by 9.96 m/s^2 roll has
broken that symmetry (+2.32 / -4.44 deg) and the gap grows to **2.59 mm**. The FBRC
departs from the KRC only once the geometry is asymmetric, monotonically with roll.

The magnitudes are small, which is the honest finding for this car rather than a
weakness of the method: a low roll center with near-parallel-ish arms gives little
for lateral-force weighting to act on.

## 7. Deferred (explicitly out of scope)

- Four-post rig cross-validation of `F_z_geom` against measured jacking, which
  needs independent left/right lateral force (§5.4).
- FBRC vs ride height / heave: the stock rig only pulses lateral force during its
  roll phase, so only roll-pose dependence is reachable without a new rig.
- Compliance (bushing) effects: the linkage is treated as rigid, which is the
  standard FBRC assumption and matches BobLib's rigid joints.
- Unsprung mass weight/inertia is excluded from the corner force split; the FBRC
  is a property of the sprung-mass load path.
