# FourPost static balance

FourPostEval checks the design pose of the rig with executed signals. This page
gives the checks, the rows they use, the tolerances, the limits and the behavior
change. The code is `simulations/response/mbd/four_post/static_balance.py`.

## Terms

- **Zero-command row**: an output row where the heave, roll, fx and fy commands
  of both axles are zero.
- **Design row**: a zero-command row whose previous and next rows are also
  zero-command rows. A row at the end of a ramp is not a design row, because the
  dampers can carry load there.
- **Target load**: the sprung corner load from the sprung mass, the driver mass
  and their combined CG. Its basis is `target`. It is not a measurement.
- **Contact patch (CP)**: the point where the rig holds the tire.

## Checks

The rig has no gravity. On a zero-command row, the only external loads on an
axle are the CP forces and torques and the chassis actuator reaction. Their sums
must be zero.

| Check | Rows | Pass rule |
| --- | --- | --- |
| Force and moment closure of each axle | every zero-command row | residual <= 1e-4 x load scale |
| Spring force against the executed spring table | every design row | residual <= 1e-4 x spring force (1 N floor) |
| Contact Fz against the target load, per corner | median over design rows | error <= max(5 N, 0.5 % of target) |

`static_balance_pass` is true only when all three checks pass.

Signals:

- CP force and torque `<axle>.<side>CP.f[1..3]`, `.t[1..3]` and position
  `<axle>.<side>CP.r_0[1..2]`. CP z is not in the result. The check uses z = 0.
- Spring force `<axle>.<side>ShockLinkage.TabularSpring.force.f` and spring
  length `<KnC>.<side>SpringLength`.
- Chassis reaction `<actuator>.sprungLoads.frame_a.f[1..3]` and `.t[1..3]`. This
  frame is at the world origin with world axes.

The load scale for force is the sum of the CP force magnitudes. For moment, it
is the sum of |r| x |F| plus |T| over the CPs. Moments are about the world
origin.

The spring rule is the BobLib `TabularSpring` rule. The table is evaluated at
the signed deflection, free length minus length. Outside the table it
extrapolates from the last two points. A spring in extension therefore gives the
force on the table line below zero deflection, not the mirror of the
compression force.

## Metrics CSV keys

| Key | Meaning |
| --- | --- |
| `static_balance_pass` | `True` when all checks pass. Empty when the status is `unavailable`. |
| `static_balance_status` | `pass`, `fail` or `unavailable`. `unavailable` means the run was not evaluated, for example a missing signal. |
| `static_balance_reason` | The failed checks, or the missing signals. |
| `static_balance_max_abs_fz_error_n`, `_pct` | Largest absolute measured contact Fz minus target load over the four corners. |
| `static_equilibrium_pass` | The closure check alone. |
| `static_equilibrium_max_force_residual_n` | Largest force residual norm over zero-command rows and axles. |
| `static_equilibrium_max_moment_residual_nm` | Largest moment residual norm. |
| `static_equilibrium_max_relative_residual` | Largest residual over load scale, force or moment. |
| `static_equilibrium_worst_time_s` | Time of that largest relative residual. |
| `static_equilibrium_rows` | Number of zero-command rows. |
| `static_spring_max_residual_n` | Largest spring force minus table force. |

## Tolerance basis

Closure, 1e-4 of the load scale. A rig with no gravity and no states must close
exactly on every row. At t = 0 the BobSim default car closes to machine
precision. A residual is not a physical load. It means that the reported forces
are not the forces that the model balanced.

Observed on the BobSim default car at `fe03bab` (BobLib `1bd6d78`, OpenModelica
1.27.1). The residual is not solver noise:

- Spring length and spring force are constant on every zero-command row
  (front 0.17943 m and 532.47 N).
- The front force residual norm is 0 at t = 0, 0.037 N at t = 1 s, 1.12 N at
  t = 30 s, 3.43 N at t = 92 s and 4.39 N at t = 118 s. It grows in proportion
  to simulated time. The rear grows at almost the same rate.
- Most of the residual is in the chassis reaction. The z part grows about
  0.026 N/s. The y part grows about 0.027 N/s with no lateral command.
- The relative residual passes 1e-4 after about 2.9 s. It is 4.1e-3 at
  t = 118 s.
- The cause is unknown. The default car therefore fails the closure check. The
  gate stays at 1e-4.

At BobLib `7363fc1` the drift is gone. BobLib #48 (`093952a`) made the rig
quasi-static and smoothed its heave and roll tables. On the default car the
largest force residual is 1.6e-12 N, the relative residual is 1.4e-15, and the
default car passes the closure check. The largest target error is 0.90 N
(0.15 %). The gate did not change.

On design rows, the front left and right contact loads also drift apart, by
about 0.35 N at t = 92 s. At t = 118 s the split is 13.8 N. That row ends a roll
ramp and has a nonzero roll rate, so the split is probably a damper load. That
row is a zero-command row, so it enters closure. It is not a design row, so it
does not enter the corner loads.

Spring, 1e-4 of the spring force. The model evaluates the table exactly. The
default car shows a residual of about 1e-12 N. A free length that did not take
effect shows as a large residual: 5 mm on the default front spring is about
130 N.

Target, max(5 N, 0.5 %). This is the setup tolerance that FourPost already had.
It is the default of `model_overrides.suspension.static_balance_tolerance_n` and
`static_balance_tolerance_pct`. 5 N is about 0.2 mm of default front spring
compression.

## Limits

- The spring check does not prove that the spring load reaches the CP. The setup
  page shows the spring force divided by the static motion ratio next to the
  contact Fz. This is not a pass rule. The static motion ratio is a fitted
  derivative from the heave sweep. On the default car the two values differ by
  0.3 N to 0.6 N front and 0.1 N to 0.4 N rear.
- The target check needs a car whose vehicle file free length holds the sprung
  mass at the design ride height. A car that does not will fail it. This is a
  setup result, not a run error.
- The check does not evaluate rows with a command. It does not check the
  sweeps.

## Behavior change

- Before, the summary derived the spring force from the target load and then
  compared the target with itself. `static_balance_max_abs_fz_error_n` was 0 and
  `static_balance_pass` was `True` for every car. Now both come from the
  measured contact loads.
- Before, when a metrics CSV from an earlier run was at
  `report.metrics_csv_path`, the spring free length came from that file. So a
  second run used a different free length than a first run. Now the free length
  comes from `model_overrides.suspension.<axle>.spring_free_length_m` or the
  vehicle file only.
- The static balance loop is removed. It always stopped after one run, because
  the error was 0. FourPost no longer reads `static_balance_iterations` or
  `static_balance_convergence_n`. The
  `static_balance_iterations` row is removed from the metrics CSV.
- On the setup page, Contact Fz is the measured CP load in the rig. Before, the
  page showed the target plus the unsprung weight. Spring length is the
  measured length. Before, it was a length from the vehicle hardpoints.
