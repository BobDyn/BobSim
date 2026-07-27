# Force-Based Roll Center Study — Findings Report

**Vehicle:** "sample_vehicle" v0.1.0 (LHR)
**Model:** `BobLib.Experiments.Standards.VehicleSim` →
`BobLib.Records.VehicleDefn.EVBatInvMotDiff_DWBCStabar_DWBCStabarRecord`
**Date:** 2026-07-27
**Tooling:** New BobSim study `FbrcEval`, OpenModelica 1.26.3

---

## 1. Executive summary

We built a study that measures the **force-based roll center (FBRC)** of each axle
directly from a full-vehicle dynamic simulation, and ran it over a lateral
acceleration sweep in steady cornering.

**The headline result: the kinematic roll center substantially understates roll
center migration, and it does so unevenly between the two axles.**

| | FBRC migration | KRC migration | understatement |
| --- | --- | --- | --- |
| Front | **−5.74 mm/g** | −2.95 mm/g | 1.9× |
| Rear | **−5.26 mm/g** | −0.82 mm/g | **6.4×** |

Read kinematically, the rear roll center looks almost stationary — 0.8 mm of travel
across the whole sweep. Measured against the actual force distribution it moves
4.9 mm. **The rear's apparent stability is an artifact of the equal-tire-force
assumption baked into the kinematic construction, not a property of the car.**

Three other findings worth acting on:

1. **The roll axis itself is very stable** — front-minus-rear FBRC holds
   −12.9 to −13.2 mm across the entire sweep (0.24 mm of variation). Nose-down and
   effectively attitude-independent. This is a genuinely good design property.
2. **Geometric load transfer is a small fraction of the total** — 17.8% front,
   7.3% rear at 1 g. This car transfers load overwhelmingly through springs and bars,
   not through suspension geometry.
3. **Geometric balance is not constant with lateral acceleration.** The front's
   share of geometric load transfer drifts 74.5% → 65.9% as load builds. Anyone
   tuning balance on the assumption of a fixed geometric split is working from a
   moving baseline.

---

## 2. Why this study exists — FBRC vs the kinematic roll center

### The problem with the kinematic roll center

The conventional **kinematic roll center (KRC)** is a drawing-board construction:
project each corner into the front view, find the instant center, draw a line from
the contact patch to it, and intersect the left and right lines. That intersection
is the roll center.

It embeds two assumptions that are false in a real corner:

1. **Left and right lateral forces are equal.** They are not. In steady cornering
   the loaded outer tire generates far more lateral force than the unloaded inner
   one. The intersection point implicitly weights both corners equally.
2. **The two lines actually intersect.** With parallel control arms the instant
   center goes to infinity, the two force lines become parallel, and the
   construction returns nothing — even though the physics is perfectly well behaved.

### What the FBRC is instead

The FBRC is defined by a **force balance rather than a geometric construction**: it
is the point through which the resultant of the link-borne (non-elastic) axle forces
acts. Equivalently, it is the **lateral-force-weighted** mean of the two corners'
force-line heights:

> **h_FBRC = (Fy_L·h_L + Fy_R·h_R) / (Fy_L + Fy_R)**

Three consequences that make it the better metric:

- It is **always defined** whenever the axle carries lateral load, including the
  parallel-arm case that breaks the KRC.
- It **reduces exactly to the KRC** when the two lateral forces and the geometry are
  symmetric. It is not a competing definition — the KRC is its special case.
- It therefore **only diverges from the KRC once the car is actually rolled**, since
  that is when the left and right corners stop being mirror images. A weighted mean
  of two *equal* heights is still that height. This is why the study sweeps lateral
  acceleration rather than reporting a single number: **at zero roll there is
  nothing to report.**

### Why it matters practically

The roll center height above the contact-patch plane is the **moment arm that sets
geometric load transfer** — the portion of lateral load transfer that goes through
the control arms instantly, rather than through the springs and bars over the roll
mode. Get the height wrong and you get the geometric/elastic split wrong, which is
what actually determines transient balance response.

---

## 3. Methodology

### 3.1 The measurement principle

Rather than construct instant centers, we measure the **suspension's actual
kinematic sensitivity** at each operating point.

For each corner we solve the suspension's single ride degree of freedom and ask: as
the contact patch moves up by one unit, how far does it move laterally? That ratio
*is* the force-line inclination:

> **tan θ = − ∂y_contact_patch / ∂z_contact_patch**

This follows from virtual work: for a rigid, frictionless linkage, the link-borne
vertical force produced by a lateral tire force is exactly `Fy · tan θ`. No
instant-center construction is needed, and the result is exact for any linkage
topology — including the parallel-arm case.

**Why this approach was chosen over the classical projection.** The conventional
2-D front-view method has three defects that this avoids:

| classical 2-D projection | this method |
| --- | --- |
| Ignores control-arm axis inclination (fore/aft skew) | Includes it — solves in full 3-D |
| Ignores the tie rod entirely | Includes the tie rod as a real constraint |
| Undefined for parallel arms | Well behaved; returns a horizontal force line |

Concretely: we solve for the upright's instantaneous motion subject to the real
constraints — each control arm's outboard joint confined to a circle about that
arm's inboard pivot axis (two constraints each), plus fixed tie-rod length (one
constraint). Five constraints on six unknowns leaves exactly the one degree of
freedom a suspension should have. The solver **verifies** that count and refuses to
return a number if the corner is over- or under-constrained, rather than silently
producing a plausible-looking result.

The two axle force lines are then combined by moment balance about the vehicle
centerline to give the axle FBRC, weighted by each tire's measured lateral force.

### 3.2 The maneuver

**Closed-loop constant-speed steady-state cornering.** Ten independent runs, one per
target lateral acceleration (1 → 10 m/s² in 1 m/s² steps), all at 15 m/s (33 mph).

Each run:

1. **Accelerate to and hold 15 m/s.** A PI speed controller maintains it via motor
   torque throughout; driver pedals are inactive.
2. **At t = 2 s, begin steering in.** The controller does *not* step the wheel. It
   ramps a *lateral-acceleration command* at 10 m/s³ following a smoothstep profile,
   so the command leaves zero and arrives at target with zero slope — no jerk
   transient to contaminate the settled point.
3. **A PI loop on lateral-acceleration error turns the handwheel** to whatever angle
   achieves the commanded ay. The car finds its own steer angle rather than being
   told one, so every case lands on a genuine trim state.
4. **Hold until steady state is confirmed.** Eight conditions must be satisfied
   *simultaneously*: ay within 0.10 m/s² of command, speed within 0.20 m/s, and the
   rates of change of ay, yaw, sideslip, roll, and handwheel all below tolerance.
   Only then is the point accepted.
5. **Sample the fully settled state** and solve the FBRC from that attitude.

The car therefore drives a **steady circle**, tightening from case to case:

| target ay | radius | lateral g | yaw rate | roll angle | time to settle |
| --- | --- | --- | --- | --- | --- |
| 1 m/s² | 225 m | 0.10 g | 0.063 rad/s | 0.095° | 5.3 s |
| 5 m/s² | 45 m | 0.51 g | 0.330 rad/s | 0.456° | 7.8 s |
| 10 m/s² | 22.5 m | 1.02 g | 0.665 rad/s | 0.912° | 9.0 s |

**All 10 points converged and were accepted.** Speed held within 0.02 m/s of target
throughout.

**Why this maneuver.** The FBRC is a property of the suspension *at an attitude*, and
the attitude variable that matters is roll — that is what breaks left/right symmetry
and separates the FBRC from the KRC. A steady circle is the cleanest way to buy roll
angle and asymmetric tire force at a genuinely stationary operating point. Only one
speed is swept because extra speeds would revisit the same attitudes.

### 3.3 What is measured vs assumed

Everything geometric is **read from the running simulation at the deflected
attitude** — contact patch positions, control-arm joint positions, tie-rod ends,
axle-frame attitude, and per-tire forces. Nothing is taken from static design
geometry except the two control-arm pivot *axis directions*, which are rigid in the
chassis and therefore cannot deflect. Those were verified component-by-component
against the compiled model record.

The measurement is taken in each **axle's own mounting frame**, not a single shared
chassis frame. This matters because the chassis model includes a torsional
compliance (500 kN·m/rad) between the front and rear mounts, so under cornering load
the rear axle is twisted relative to the chassis reference. Using one shared frame
would corrupt the rear axle results by the chassis twist angle.

### 3.4 Verification

The physics was validated four independent ways against the real run data — each
recomputing a quantity by a different route rather than re-running the same code:

| check | independent method | agreement |
| --- | --- | --- |
| Kinematic roll center | elementary 2-D line intersection from contact patches and angles | 2.8×10⁻¹⁴ mm |
| FBRC | force-weighted-mean formula vs the moment-balance route used internally | 5.6×10⁻¹⁴ mm |
| **Force-line angle** | **nonlinear finite difference: physically displace the upright, re-close the linkage by Newton iteration on the rigid-link constraints, difference the contact patch** | **1.5×10⁻⁸** |
| Load-transfer identity | recompute ΔFz = −Fy·h/track and compare to reported value | 5.0×10⁻¹⁴ N |

**The third is the meaningful one.** The first, second and fourth are algebraic
consistency checks. The third validates the kinematic solver against the *actual
nonlinear constraint manifold* — it independently articulates the linkage and
confirms the predicted sensitivity is what the mechanism really does.

Additionally, the force-line solver was cross-checked against a separately written
suspension kinematics solver (different author, different method, no shared code)
that articulates the linkage numerically and builds the classical 2-D instant
center. Over ±30 mm of jounce the two agree to **better than 0.3 mm** of roll center
height, with the residual being exactly the 3-D terms the 2-D projection drops.

**Sanity criteria applied to every run:** force-line angles in single-digit degrees;
roll center heights within tens of mm of the contact-patch plane; geometric load
transfer share between 0 and 100%; force lines near-symmetric at low ay and
diverging with roll; FBRC−KRC → 0 as ay → 0.

---

## 4. Model inputs

### 4.1 Vehicle configuration

| parameter | value |
| --- | --- |
| Wheelbase | 1.5494 m |
| Track (front / rear) | 1.2122 m / 1.2122 m |
| Total weight (measured) | 2862 N (291.8 kg) |
| Static weight split | 49.6% front / 50.4% rear |
| Sprung + driver mass | 226.4 kg |
| Sprung + driver CG height | 0.2923 m |
| Unsprung mass per corner | 7.82 kg front / 7.35 kg rear |
| Wheel radius (unloaded) | 0.2045 m |
| Chassis torsional stiffness | 500 000 N·m/rad |

### 4.2 Suspension

Double wishbone at both ends, **bellcrank-actuated with anti-roll bar front and
rear**.

| parameter | front | rear |
| --- | --- | --- |
| Spring rate | 26 269 N/m | 43 782 N/m |
| Anti-roll bar rate | 257.6 N·m/rad | 535.5 N·m/rad |
| Damper rate | 850 N·s/m | 1300 N·s/m |
| Pushrod/pullrod mounts to | lower arm | upper arm |
| Static toe / camber | 0° / 0° | 0° / 0° |

Tires: MF-5.2 model, `16x7p5_10_12psi`, vertical stiffness 98 947 N/m.

### 4.3 Test conditions

| parameter | value |
| --- | --- |
| Speed | 15 m/s (constant, closed-loop) |
| Lateral acceleration | 1 → 10 m/s² in 1 m/s² steps |
| Points accepted | 10 of 10 |
| Measured ay range | 0.95 → 9.96 m/s² (0.10 → 1.02 g) |
| Roll angle range | 0.095° → 0.912° |
| Measured roll gradient | 0.89 deg/g |

### 4.4 Configuration discrepancy — needs resolution

> **The vehicle definition file and the simulated model disagree on rear
> architecture.**
>
> `vehicle.yml` declares rear suspension as `bellcrank` (**no anti-roll bar**). The
> model actually compiled and run is `DWBCStabar_DWBCStabar` — rear bellcrank
> **with** a 535.5 N·m/rad anti-roll bar.
>
> The BobLib model uses checked-in Modelica records; the build does not regenerate
> the model from `vehicle.yml`, so the checked-in configuration silently wins.
>
> **Impact:** rear anti-roll bar rate directly sets rear roll stiffness, which sets
> rear roll angle, which is precisely what drives the 6.4× rear divergence reported
> in §1. **The rear-axle numbers in this report are for a car with a rear bar.** If
> the intended car has no rear bar, the rear column must be re-run.
>
> Separately, `vehicle.yml` lists a front bar rate of 1 N·m/rad (essentially zero)
> against the record's 257.6 N·m/rad — worth reconciling at the same time.

---

## 5. Numerical results

Heights are relative to the **contact-patch plane** (the moment arm that sets
geometric load transfer). Negative = below ground. θ is force-line inclination.

### 5.1 Front axle

| ay (m/s²) | FBRC (mm) | KRC (mm) | FBRC−KRC (mm) | θ left | θ right | jacking (N) | ΔFz_geom (N) | ΣFy (N) |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0.95 | −33.86 | −33.83 | −0.031 | +3.084° | −3.306° | −0.60 | 4.33 | 155 |
| 1.95 | −34.06 | −33.95 | −0.111 | +2.989° | −3.420° | −2.23 | 8.65 | 308 |
| 2.95 | −34.35 | −34.11 | −0.244 | +2.895° | −3.536° | −4.89 | 12.92 | 456 |
| 3.95 | −34.73 | −34.30 | −0.427 | +2.804° | −3.654° | −8.49 | 17.13 | 598 |
| 4.95 | −35.20 | −34.54 | −0.660 | +2.716° | −3.776° | −13.06 | 21.39 | 736 |
| 5.95 | −35.78 | −34.84 | −0.945 | +2.631° | −3.901° | −18.59 | 25.78 | 873 |
| 6.95 | −36.46 | −35.18 | −1.279 | +2.548° | −4.030° | −25.12 | 30.35 | 1009 |
| 7.95 | −37.25 | −35.59 | −1.666 | +2.469° | −4.163° | −32.74 | 35.20 | 1145 |
| 8.95 | −38.15 | −36.05 | −2.103 | +2.392° | −4.300° | −41.46 | 40.35 | 1281 |
| 9.96 | −39.16 | −36.57 | −2.593 | +2.318° | −4.442° | −51.37 | 45.87 | 1419 |

### 5.2 Rear axle

| ay (m/s²) | FBRC (mm) | KRC (mm) | FBRC−KRC (mm) | θ left | θ right | jacking (N) | ΔFz_geom (N) | ΣFy (N) |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0.95 | −19.06 | −19.04 | −0.020 | +1.698° | −1.908° | −0.12 | 1.48 | 94 |
| 1.95 | −19.18 | −19.04 | −0.144 | +1.601° | −2.011° | −0.95 | 3.22 | 203 |
| 2.95 | −19.40 | −19.05 | −0.347 | +1.505° | −2.118° | −2.41 | 5.09 | 318 |
| 3.95 | −19.70 | −19.07 | −0.629 | +1.412° | −2.228° | −4.56 | 7.13 | 439 |
| 4.95 | −20.11 | −19.11 | −0.994 | +1.322° | −2.341° | −7.45 | 9.35 | 564 |
| 5.95 | −20.62 | −19.17 | −1.442 | +1.234° | −2.459° | −11.10 | 11.74 | 690 |
| 6.95 | −21.24 | −19.27 | −1.974 | +1.148° | −2.580° | −15.55 | 14.32 | 817 |
| 7.95 | −22.00 | −19.41 | −2.596 | +1.066° | −2.706° | −20.87 | 17.15 | 945 |
| 8.95 | −22.91 | −19.60 | −3.306 | +0.987° | −2.837° | −27.10 | 20.26 | 1072 |
| 9.96 | −23.98 | −19.87 | −4.109 | +0.912° | −2.973° | −34.34 | 23.71 | 1198 |

### 5.3 Roll axis and geometric balance

| ay (m/s²) | front − rear FBRC (mm) | geometric LLTD, front share |
| --- | --- | --- |
| 0.95 | −13.14 | 74.5% |
| 2.95 | −13.17 | 71.7% |
| 4.95 | −13.17 | 69.6% |
| 6.95 | −13.14 | 67.9% |
| 8.95 | −13.03 | 66.6% |
| 9.96 | −12.93 | 65.9% |

### 5.4 Wheel loads (context)

| ay (m/s²) | FL | FR | RL | RR |
| --- | --- | --- | --- | --- |
| 0.95 | 683.1 | 736.1 | 688.2 | 755.1 |
| 4.95 | 580.1 | 839.7 | 554.8 | 883.6 |
| 9.96 | 449.7 | 965.1 | 388.3 | 1038.1 |

Loads migrate monotonically inside-to-outside with no wheel approaching lift; total
normal load is conserved throughout.

---

## 6. Interpretation

### 6.1 The KRC understates migration, especially at the rear

Both roll centers start at the same place (0.03 mm and 0.02 mm apart at 0.95 m/s²)
— exactly as the theory requires, since at near-zero roll the corners are still
mirror images. They then separate monotonically with roll.

The front FBRC falls 5.3 mm over the sweep against the KRC's 2.7 mm. The rear FBRC
falls 4.9 mm against the KRC's **0.8 mm**.

**The rear is the actionable finding.** A kinematic analysis would report the rear
roll center as essentially fixed and invite the conclusion that rear geometry needs
no attention across the operating range. The force-based measurement shows it moving
as much as the front. The discrepancy arises because the rear's two force lines
happen to rotate in a way that keeps their *intersection* nearly stationary while
their *force-weighted mean* does not — a coincidence of the construction, not a
property of the mechanism.

### 6.2 Geometry is anti-jacking

Both roll centers sit below the contact-patch plane at all conditions, and the
jacking force is **negative** throughout (−51 N front, −34 N rear at 1 g) — the
suspension pulls the car down under cornering rather than lifting it. This is
generally desirable: no jacking-induced CG rise, no associated roll-stiffness
surprise at the limit.

Jacking scales essentially as the **square** of axle lateral force (R² = 0.9997 for
a quadratic fit, versus 0.943 for linear), which is expected since both the force
and the force-line angle grow with load. Practically: jacking is negligible at low
ay and grows sharply at the limit.

### 6.3 This car transfers load elastically, not geometrically

Comparing geometric load transfer against total measured load transfer at 1 g:

| axle | total LT | geometric | geometric share | elastic share |
| --- | --- | --- | --- | --- |
| Front | 257.7 N | 45.9 N | **17.8%** | 82.2% |
| Rear | 324.9 N | 23.7 N | **7.3%** | 92.7% |

Load transfer runs overwhelmingly through springs and anti-roll bars. Two
implications:

- **Geometry changes are a weak balance lever on this car.** Moving a roll center a
  few mm moves only a small fraction of an already-small geometric contribution.
  Spring and bar rates are where the authority is.
- **But geometry sets the *transient*.** Geometric transfer acts instantly through
  the links; elastic transfer develops over the roll mode. The 17.8%/7.3% front/rear
  asymmetry means the car's *initial* response to steering is biased differently
  from its steady-state balance.

### 6.4 Geometric balance drifts with load

Front share of geometric load transfer moves 74.5% → 65.9% across the sweep — an
8.6-point drift. This is not constant, and using a single geometric-split figure
across the operating range will misrepresent the car at one end or the other.

Note the KRC would have reported this split as 68.5% at 1 g versus the FBRC's 65.9%
— a 2.6-point error in a balance-relevant quantity.

### 6.5 The roll axis is a design strength

Front-minus-rear FBRC stays within 0.24 mm of −13 mm across the entire sweep. The
roll axis is consistently nose-down and effectively independent of attitude. This is
a good property and worth preserving through any future geometry change — it means
roll-axis inclination is not introducing load-dependent balance drift.

---

## 7. Limitations and recommended next steps

### Limitations of the current results

- **One architecture tested.** The vehicle definition package contains nine
  front/rear architecture combinations; one was run. All nine share identical
  wishbone and tie-rod hardpoints, so the *unloaded* force-line geometry is common
  to all; architecture changes the FBRC only indirectly, through roll stiffness →
  roll angle → deflected geometry. The nine are therefore nine attitudes of one
  linkage, not nine linkages.
- **Rigid linkage.** Bushing and link compliance are excluded. This is the standard
  FBRC assumption and consistent with the model's rigid joints, but real compliance
  will move the effective force line.
- **Sprung-mass load path only.** Unsprung weight and inertia are excluded from the
  corner force split, consistent with the FBRC's definition.
- **Roll-pose dependence only.** The maneuver holds ride height constant, so
  FBRC-vs-heave is not characterized.
- **Single speed.** With one test speed, roll-angle effects cannot be formally
  separated from speed/aero effects. At 15 m/s aero is negligible on this car, so
  this is not believed to affect the results — but it is not proven by the data.

### Recommended next steps, in priority order

1. **Resolve the configuration discrepancy in §4.4.** Until the intended rear
   architecture is settled, the rear-axle numbers describe a car that may not be the
   one being built. This is the only item that could change a conclusion.
2. **Run the remaining architectures** to quantify how much roll-stiffness choice
   moves the FBRC. Cheap now that the study exists (~6 min each).
3. **Add a second test speed** to confirm the results are attitude-driven and not
   speed-driven.
4. **Characterize FBRC vs ride height** — requires a rig maneuver that sweeps heave
   while holding lateral load, which the current four-post rig cannot do (it applies
   lateral force only during its roll phase).
5. **Assess compliance sensitivity** if bushing rates are available; the rigid-link
   assumption is the largest un-quantified modelling approximation.

---

## Appendix — Reproduction

The study is `FbrcEval`, integrated as a standard BobSim study:

```
make standard-eval-fbrc
```

Outputs a metrics CSV and a 4-page PDF report (roll center height vs ay, per-corner
force-line inclination, geometric load transfer and jacking, FBRC−KRC).

Full mathematical derivation, step-by-step reproduction procedure, and the
verification checks of §3.4 are documented in
`docs/superpowers/specs/2026-07-26-fbrc-eval-method-and-reproduction.md`.
Design rationale and issues encountered are in
`docs/superpowers/specs/2026-07-26-fbrc-eval-design.md`.
