# FBRC Study: Derivation and Reproduction Procedure

Companion to `2026-07-26-fbrc-eval-design.md`. That document records the design and
the issues found. This one states the mathematics as implemented and gives the exact
procedure to reproduce every number, including the independent checks.

Everything below was executed against
`BobLib.Experiments.Standards.VehicleSim` on 2026-07-26 with
OpenModelica 1.26.3 in `bobdyn/bobsim:latest`.

---

## Part I — Mathematics

### 1. Conventions

BobLib body axes, **not** SAE:

| axis | direction |
| --- | --- |
| x | forward |
| y | **left** positive |
| z | up |

Right-handed. All suspension mathematics is done in the **axle mounting frame**
(§4), where `y = 0` is the vehicle centerplane. Forces are contact-patch forces on
the tire from the ground. `theta` is the force-line (n-line) inclination, positive
when the line rises going inboard on the left-hand corner.

### 2. What is being computed, and why not the kinematic roll center

The **kinematic roll center (KRC)** is the intersection of the two corners' force
lines in the front view. It carries two assumptions that are false in a corner:

1. Left and right lateral forces are equal. In steady cornering they are not — the
   loaded outer tire carries far more.
2. The two lines actually intersect. With parallel control arms the instant centre
   is at infinity, the two lines are parallel, and the KRC is undefined even though
   the physics is perfectly well behaved.

The **force-based roll center (FBRC)** is the point through which the *resultant of
the link-borne axle forces* acts. It is defined by a force balance rather than a
geometric construction, so it is well posed whenever the axle carries lateral load,
and it degenerates *to* the KRC in the symmetric equal-force case rather than being
a different quantity.

### 3. The corner force line from virtual work

The classical route projects the suspension into the y-z plane, builds an instant
centre, and draws a line to the contact patch. That is a 2-D approximation: it
ignores the tie rod, ignores caster/steer coupling, and breaks for parallel arms.

Instead: let `zeta` parameterise the corner's single ride degree of freedom, and let
the contact patch position be `p(zeta)`. For a rigid, frictionless linkage, virtual
work gives the generalised force directly. With the full tire wrench `(F, M)` acting
at the patch, the link-borne (non-elastic) vertical force is

$$
F_z^{geom} \;=\; -\left[
F_x \frac{\partial x_{cp}}{\partial \zeta}
+ F_y \frac{\partial y_{cp}}{\partial \zeta}
+ \mathbf{M}\cdot\frac{\partial \boldsymbol{\varphi}}{\partial \zeta}
\right]
\tag{1}
$$

Normalising `zeta` so the patch rises at unit rate
(`dz_cp/dzeta = 1`) defines the force-line inclination as

$$
\tan\theta \;=\; -\frac{\partial y_{cp}}{\partial \zeta}
\qquad\Longrightarrow\qquad
F_z^{geom,\,lat} \;=\; F_y \tan\theta
\tag{2}
$$

Equation (2) is exact for any linkage topology. No instant-centre construction, no
2-D projection, no parallel-arm degeneracy. It is implemented as
`CornerForceLine.tan_theta` and `lateral_jacking_force`; the full form (1),
including the longitudinal and moment terms, is `geometric_vertical_force` and is
reported separately, since the FBRC is by definition the lateral term only.

### 4. Getting `∂p/∂ζ` exactly: the instantaneous twist

The upright's motion relative to the chassis is a rigid-body twist
`(omega, v_0)`, with the velocity of any material point `p`

$$
\mathbf{v}(p) \;=\; \mathbf{v}_0 + \boldsymbol{\omega}\times p
\tag{3}
$$

Six unknowns. The double wishbone plus tie rod supplies five scalar constraints:

- **Each A-arm (2 constraints).** The outboard ball joint is confined to a circle
  about that arm's inboard revolute axis. Its velocity must therefore be parallel
  to the swing direction `s = a_hat x (o - q)`, where `a_hat` is the axis
  direction and `q` a point on it. Equivalently, `v(o) . e = 0` for the two
  orthonormal directions `e` spanning the plane normal to `s`.
- **Tie rod (1 constraint).** Length is fixed, so the outboard end's velocity has
  no component along the rod: `v(t_o) . r_hat = 0`.

Each row is assembled using the identity
`v(p) . e = v_0 . e + omega . (p x e)`, giving a `5 x 6` matrix `C` with

$$
C\,[\boldsymbol{\omega};\,\mathbf{v}_0] = \mathbf{0}
\tag{4}
$$

The twist is the **null space**, obtained by SVD as the right-singular vector of the
smallest singular value. That singular value is retained as
`constraint_singular_value` and used as a rank health check: if it is not
comfortably above zero the corner does not have exactly one degree of freedom, and
the solver raises rather than returning a plausible-looking number. (This is not
hypothetical — it is what caught a bad test fixture whose tie rod pointed at the
kingpin axis, leaving a genuine second DOF.)

The result is scaled so `dz_cp/dzeta = 1`, then `tan(theta) = -dy_cp/dzeta` per (2).

### 5. Per-corner centerplane height

The force line passes through the contact patch with slope `dz/dy = tan(theta)` in
the y-z plane. Its height where it crosses the vehicle centerplane `y = 0` is

$$
h_i \;=\; z_{cp,i} - y_{cp,i}\tan\theta_i
\tag{5}
$$

This is the per-corner quantity the axle FBRC is built from. **It is the reason the
whole calculation must be done in a vehicle-fixed frame** — `y_cp` is measured from
the centerplane. Feeding world-frame coordinates into (5) is the bug documented in
design §5.11.

### 6. Axle FBRC by moment balance

Each corner applies a link-borne force with lateral component `Fy_i` and vertical
component `Fy_i tan(theta_i)` on a line through its patch. Taking moments about the
x axis through the centerplane at ground level:

$$
M_x \;=\; \sum_i \left[\, y_{cp,i}\,F_{y,i}\tan\theta_i \;-\; z_{cp,i}\,F_{y,i} \,\right]
\tag{6}
$$

$$
\boxed{\;h_{FBRC} \;=\; -\,\frac{M_x}{\sum_i F_{y,i}}\;}
\tag{7}
$$

Substituting (6) into (7) and using (5) collapses it to the form quoted in the
literature,

$$
h_{FBRC} \;=\; \frac{F_{y,L}\,h_L + F_{y,R}\,h_R}{F_{y,L}+F_{y,R}}
\tag{8}
$$

i.e. the **lateral-force-weighted mean of the per-corner centerplane heights**. The
derivation reproduces the published result rather than being fitted to it; (7) and
(8) are cross-checked numerically against each other on real data (Part II, check
C2).

Two consequences worth stating explicitly:

- If `Fy_L = Fy_R` **and** the geometry is symmetric (`h_L = h_R`), then (8) returns
  that common value, which is exactly the KRC. FBRC and KRC coincide.
- Therefore the FBRC departs from the KRC **only when the geometry is also
  asymmetric** — that is, in roll. Asymmetric force alone changes the *jacking
  force*, not the roll centre. This is why the study sweeps lateral acceleration
  rather than reporting a single number.
- `h_FBRC` is undefined when `sum Fy = 0`, so `a_y = 0` is deliberately excluded
  from the sweep.

### 7. Jacking versus roll: sum and difference

These are different moments of the same forces and are easy to conflate:

$$
F_z^{jack} = \sum_i F_{y,i}\tan\theta_i
\qquad\text{(symmetric / sum part)}
\tag{9}
$$

$$
M_x^{geom} = \sum_i y_{cp,i} F_{y,i}\tan\theta_i
\qquad\Longrightarrow\qquad
\Delta F_z^{geom} = \frac{M_x^{geom}}{t}
\qquad\text{(antisymmetric / couple part)}
\tag{10}
$$

Jacking is the **sum**; geometric load transfer is the **couple**. `FourPostEval`'s
existing "geometric anti-roll" metrics are jacking coefficients — the sum part — so
they are not roll centres and the FBRC is genuinely new information, not a
duplicate.

Using the moment form (10) rather than `0.5(jack_L - jack_R)` keeps it correct when
the two contact patches are not symmetric about `y = 0`, which under steer and roll
they are not.

### 8. The datum, and an exact identity

Load transfer is driven by the moment arm above the **contact-patch plane**, not
above `z = 0`. With the patch-plane datum defined as the lateral-force-weighted mean

$$
z_{cp}^{plane} = \frac{z_{cp,L}F_{y,L} + z_{cp,R}F_{y,R}}{F_{y,L}+F_{y,R}}
\tag{11}
$$

the following holds as an **exact algebraic identity**:

$$
\Delta F_z^{geom} \;=\; -\,\frac{\left(\sum_i F_{y,i}\right)\left(h_{FBRC} - z_{cp}^{plane}\right)}{t}
\tag{12}
$$

With an *arithmetic* mean datum it is not an identity — the two differ by
`(z_L - z_R)(Fy_L - Fy_R) / (2t)`, which is nonzero precisely in the rolled
cornering regime this study targets. Measured on synthetic asymmetric data the error
was **3.30 N against a 43.12 N transfer (~8%)**, matching the predicted term exactly.
Equation (12) is used as a live invariant check (Part II, check C4).

The minus sign is a convention consequence of `+y = left`, not a sign error: the
outer wheel is the one the lateral force points away from.

### 9. Reported quantities

Per axle, per operating point: `fbrc_height`, `fbrc_height_above_cp`,
`krc_height`, `krc_height_above_cp`, `fbrc_minus_krc`, left/right
`force_line_deg`, left/right `centerplane_height`, `jacking_force`,
`geometric_load_transfer`, `lateral_force`, `roll_moment`.

Aggregate: sweep means of the above, `fbrc_migration_mm_per_g` (regression slope of
height against `a_y`), `roll_axis_front_minus_rear_mm`, and
`geometric_lltd_front_pct`.

**Heights are never compared across datums.** Both FBRC and KRC are reported in both
the frame-z and contact-patch-relative datums, and plots pair like with like. Mixing
them produced a spurious constant ~4.6 mm offset in an earlier revision (the nominal
geometry uses the *unloaded* tire radius, putting patches at z = −4.6 mm).

---

## Part II — Reproduction

### 0. Prerequisites

- Docker with a VM of **at least ~6 GB RAM**. At 2 GB the build is OOM-killed
  (exit 137) partway through the C stage. With Colima:
  `colima stop && colima start --memory 8`.
  *Check running containers first — restarting the VM kills them.*
- Image `bobdyn/bobsim:latest` (OpenModelica 1.26.3, Python 3.11).
- `docker compose` may be unavailable; the `make` targets fall back, or use plain
  `docker run` as shown below.

All commands run from `sources/BobSim`. Define once:

```bash
DR='docker run --rm -v "$PWD":/workspace -w /workspace -e PYTHONPATH=/workspace bobdyn/bobsim:latest'
```

### 1. Confirm which model you are about to run

`VehicleSim.mo` hardcodes its architecture and `build_vehicle_sim.mos` does **not**
regenerate it from `vehicle.yml`. Check before trusting any result:

```bash
grep 'extends Templates' _0_Utils/external/BobLib/BobLib/Experiments/Standards/VehicleSim.mo
grep -A2 '^architecture:' vehicle.yml
```

As of this writing these **disagree**: the YAML says rear `bellcrank`, the compiled
model is rear `bellcrank_stabar`. Reconcile, or record which one you ran.

To target a different one of the nine `VehicleDefn` records, edit line 6 of
`VehicleSim.mo` to the matching
`Templates.Vehicle.VehicleSim_EVBatInvMotDiff_<FRONT>_<REAR>` and rebuild. All nine
records share byte-identical wishbone and tie-rod hardpoints, so architecture
affects the FBRC only through roll stiffness → roll angle → deflected geometry.

### 2. Verify the study's one non-model input

The arm-axis *directions* are read from `vehicle.yml`; every position comes from the
model. Confirm the YAML matches the record actually being compiled:

```bash
grep -E "upperFore_i|upperAft_i|lowerFore_i|lowerAft_i" \
  _0_Utils/external/BobLib/BobLib/Records/VehicleDefn/EVBatInvMotDiff_DWBCStabar_DWBCStabarRecord.mo
grep -A4 -E "upper_fore_i_m|lower_fore_i_m" vehicle.yml
```

All 12 components, both axles, must match. They did.

### 3. Build

```bash
eval $DR bash -lc 'omc /workspace/_3_StandardSim/build_vehicle_sim.mos' 
test -x _3_StandardSim/BuildBobLib/VehicleSim/BobLib.Experiments.Standards.VehicleSim && echo BUILD_OK
```

Expect ~5 min and `95 linear / 42 nonlinear systems`. The script probes whether
`clang` accepts `-march=native` and falls back to `-mcpu=native` on aarch64.

### 4. Verify signal availability before running the sweep

This is the step that catches the two silent failure modes. Against the compiled
`_init.xml` (~35 332 names), assert every requested signal exists and the compacted
`variableFilter` matches exactly the intended set:

```bash
eval $DR python - <<'PY'
import re
from pathlib import Path
from _3_StandardSim.FbrcEval.fbrc_eval_sim import FBRC_EVAL_SIGNALS, matches_variable_filter
xml = Path('_3_StandardSim/BuildBobLib/VehicleSim/'
           'BobLib.Experiments.Standards.VehicleSim_init.xml').read_text(errors='replace')
names = set(re.findall(r'name\s*=\s*"([^"]+)"', xml))
missing = [s for s in FBRC_EVAL_SIGNALS if s not in names]
unmatched = [s for s in FBRC_EVAL_SIGNALS if not matches_variable_filter(s)]
print('requested:', len(FBRC_EVAL_SIGNALS), 'missing:', len(missing), 'unmatched:', len(unmatched))
PY
```

Expected: `requested: 130 missing: 0 unmatched: 0`.

The 130 break down as 24 axle-frame entries (2 axles × [3 `r_0` + 9 `R.T`]),
84 corner positions (2 axles × 2 sides × 7 points × 3 components), 12 corner tire
forces, and 10 vehicle scalars. The grouped-regex filter is 605 characters — versus
several kB if the names were enumerated literally — and passes **exactly** those 130
model names with zero extras. The result CSV has 213 columns (the surplus is
`der(...)` derivative variables OpenModelica emits alongside matched states).

Two traps this guards:

- **A `variableFilter` matching nothing is silent.** No warning is emitted for a
  pattern that matches zero variables.
- **Protected variables are dropped regardless of the filter.** Every signal the
  study reads is `protected` inside its component, so `-emit_protected` is
  mandatory and lives in `extra_args`. Note the init XML uses `name = "..."` with
  spaces around `=`; a regex expecting `name="..."` silently finds zero names.

### 5. Run the study

```bash
eval $DR python -m _3_StandardSim.FbrcEval.fbrc_eval_sim
# or: make standard-eval-fbrc
```

10 cases (`a_y` 1..10 m/s² at 15 m/s), ~2 min wall clock at 4 workers. Outputs:

- `_3_StandardSim/generated_results/fbrc_eval_report_metrics.csv`
- `_3_StandardSim/generated_results/fbrc_eval_report.pdf`

Only cases where `steadyStateConditionsMet` is set are included; rejected cases are
listed with reasons rather than silently dropped.

### 6. Independent verification checks

These do not re-run the study's own code path; each recomputes a quantity by a
different route. Run them against the persisted run directories under
`_3_StandardSim/BuildBobLib/VehicleSim/results/run_*` (the config sets
`cleanup: false` for exactly this reason).

| id | quantity | independent route | observed worst disagreement |
| --- | --- | --- | --- |
| C1 | KRC | elementary 2-D intersection of the two force lines from contact patches and angles only, not `_kinematic_roll_center` | **2.8e-14 mm** |
| C2 | FBRC | force-weighted-mean form (8) vs the moment-balance route (7) the code uses | **5.6e-14 mm** |
| C3 | `tan(theta)` | nonlinear finite difference: displace the upright, re-close the linkage by Newton iteration on the rigid-link length constraints, difference the contact patch | **1.5e-08** (consistent with `O(h^2)` at `h = 2e-4`) |
| C4 | load-transfer identity (12) | recompute `-Fy·h/t` and compare to the reported `geometric_load_transfer` | **5.0e-14 N** |

**C3 is the strongest check** — it validates the `5 x 6` SVD null-space twist solve
against the actual nonlinear constraint manifold rather than against itself. C1, C2
and C4 are algebraic consistency checks; C3 is a physics check.

Additionally, `_5_App/kinematics.py` provides a fully independent solver
(`scipy.optimize.root` articulation plus the classical 2-D instant centre) sharing
no code with `force_line.py`. Over ±30 mm jounce the two agree to **< 0.3 mm** of
roll-centre height; the residual is the genuine 3-D terms the 2-D projection drops.

### 7. Physical sanity criteria

A run is only trustworthy if all of these hold. Each failed at some point during
development, so none is rhetorical:

1. **Force-line angles are single-digit degrees.** ~2–4° for this car. Tens of
   degrees, or milli-degrees, means the frame is wrong.
2. **`|centerplane_height|` is well under 1 m.** The world-frame bug produced
   **+1604 mm**.
3. **Heights are within tens of mm of the contact-patch plane.** Hundreds of mm
   below ground is not a low roll centre, it is a frame error.
4. **`geometric_lltd_front_pct` lies in (0, 100).** The bug produced **124%**.
5. **Angles are near mirror-symmetric at low `a_y` and diverge with roll.**
   Observed: `+3.08 / -3.31°` at 0.95 m/s² → `+2.32 / -4.44°` at 9.96 m/s².
6. **`FBRC - KRC` → 0 as `a_y` → 0, growing monotonically with roll.** Observed
   **0.03 mm → 2.59 mm**. Per §6 this is required by the theory, so a constant
   offset indicates a datum mismatch and a nonzero low-`a_y` value indicates a
   frame error.
7. **The identity in check C4 holds to ~1e-13 N.**

### 8. Regression tests

```bash
eval $DR python -m pytest tests/test_force_line.py tests/test_standard_sim_polish.py -q
# full gate (note the flags -- invoking ruff/mypy bare gives false failures):
make ci
```

`make lint` excludes the vendored BobLib; `make typecheck` passes
`--no-strict-optional`. Running `ruff`/`mypy` without those reports pre-existing
issues in vendored and unrelated files.

Tests that specifically pin the bugs found by running end-to-end:

- `test_fbrc_eval_geometry_is_invariant_to_world_pose` — builds the same corner at
  the origin and at `[240, -37.5, 0.19]` yawed 63°, requiring `tan_theta` and
  `centerplane_height` to agree to 1e-9. A world-frame implementation fails this.
- `test_fbrc_eval_axle_frames_are_mounts_of_their_axle` — asserts against BobLib
  source that the frames used really are the axle mounts.
- `test_fbrc_eval_variable_filter_covers_every_requested_signal` — the compacted
  filter matches every signal and no near-miss.
- `test_boblib_default_chassis_still_has_torsional_compliance` — fails loudly if
  BobLib drops `FrameCompX`, so the per-axle-frame rationale cannot rot silently.
- `TestAsymmetricPatchHeights` — the force-weighted datum of §8; a mirror-symmetric
  fixture cannot catch it because `z_L == z_R` there.

### 9. Known limitations

- **Rigid linkage.** Bushing compliance is excluded — the standard FBRC assumption,
  and consistent with BobLib's rigid joints.
- **Sprung-mass load path only.** Unsprung weight and inertia are excluded from the
  corner force split.
- **One architecture run.** Eight of the nine `VehicleDefn` records have not been
  executed.
- **No four-post cross-validation of `F_z^{geom}`** against measured jacking; that
  needs independent left/right lateral force, and `fyTable`/`fxTable` are
  `final parameter`.
- **Roll-pose dependence only.** The stock four-post rig pulses lateral force only
  during its roll phase, so FBRC vs ride height/heave is not reachable without a new
  rig.
