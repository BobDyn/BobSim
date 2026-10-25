# FourPost metric meanings

This page says what each FourPostEval summary metric measures, what it does not
measure, and how a sample becomes invalid. The metrics are in
`simulations/mbd/generated_results/four_post_eval_report_metrics.csv`.

## Terms

- **Pose**: one commanded heave or roll position of the rig. A sweep has 11.
- **Pulse**: the force that the rig applies at the contact patches (CP) at one
  pose. A heave pose gets a longitudinal force Fx. A roll pose gets a lateral
  force Fy.
- **Dead tail**: the sample at the same pose 3 s after the pulse, with no force.
  A pulse response is the pulse sample minus the dead-tail sample.
- **h/L** and **h/t**: sprung and driver CG height over wheelbase, and over the
  mean track.
- **Sign convention**: x forward, y left, z up. A positive jacking force lifts
  the body.

## Metrics

| Key | Meaning |
| --- | --- |
| `avg_anti_dive_pct`, `avg_anti_squat_pct` | Anti from a CP force Fx that the upright reacts. Percent of h/L. |
| `avg_longitudinal_jacking_coeff_<axle>` | The same response as a dimensional coefficient dFz/dFx (N/N). |
| `anti_force_path` | `contact_patch_upright_reacted`. The force path of the three rows above. |
| `longitudinal_jacking_coeff_<axle>_contact_patch_path` | Kinematic dFz/dFx (N/N) at the design pose for an Fx that the upright reacts. |
| `longitudinal_jacking_coeff_<axle>_wheel_center_path` | Kinematic dFz/dFx (N/N) at the design pose for an Fx that the chassis reacts. |
| `anti_dive_<path>_path_pct`, `anti_squat_<path>_path_pct` | The front and rear coefficients above in percent of h/L. `<path>` is `contact_patch` or `wheel_center`. |
| `avg_anti_roll_<axle>_pct` | Legacy key. Net axle jacking J in percent of h/t. It is not geometric anti-roll. |
| `avg_lateral_jacking_coeff_<axle>` | Net axle jacking J = (dFz_L + dFz_R) / Fy (N/N), from the chassis reaction. |
| `avg_fbrc_differential_jacking_ratio_<axle>` | Differential jacking (dFz_R - dFz_L) / Fy. |
| `avg_fbrc_equivalent_height_<axle>_m` | Moment-equivalent height (t / 2) x (dFz_R - dFz_L) / Fy. |
| `avg_lltd_front_pct`, `_frac` | Legacy key. Elastic front share of the load transfer under imposed roll with no lateral force. It is not the total lateral load transfer distribution (LLTD). |
| `avg_roll_rate_distribution_front_pct` | The same share from the spring and bar roll stiffnesses. |
| `avg_antiroll_geometry_lltd_delta_pct` | Mean of the measured share minus the roll-stiffness share, pose by pose. It is not a geometric anti-roll value. |
| `heave_cp_tension_points` | Number of heave poses where a CP is in tension. |

### Anti-dive and anti-squat force path

The FourPost rig applies Fx at the CP. The wheel torque goes back through the
upright, as with an outboard brake or a hub motor. The `avg_` percent and the
`avg_` dFz/dFx coefficient are valid for that path only.

An inboard drive or an inboard brake reacts its torque on the chassis. The wheel
then pushes on the upright at the wheel center (WC). FourPost computes both paths
from the heave sweep kinematics at the design pose, where the jounce is 0:

- Contact-patch path: `c_cp = -(dx_cp/ds) / (dz_cp/ds)`.
- Wheel-center path: `c_wc = -(dx_wc/ds) / (dz_cp/ds)`.

Here `x` is the side-view position, and `z_cp` is the CP height relative to the
body. The fixture holds the CP height and the rig moves the body, so `dz_cp/ds`
is 1 when `s` is the jounce. The run exports the x positions of
`<axle>.{left,right}CP` and `<axle>.{left,right}Tire.chassisFrame` (the WC). The
two sides are averaged. A positive coefficient lifts the body for a positive Fx.
The percent uses the same h/L and the same signs as the `avg_` keys: anti-dive
is `-100 c / (h/L)` and anti-squat is `100 c / (h/L)`.

Use the path that matches the hardware. The BobSim default car,
`EVBatInvMotDiff`, has one inboard motor and a differential. Its rear
anti-squat is on the wheel-center path. A run without the position signals
reports these keys as `unavailable`.

On the default car at the design pose:

| Axle | CP path (N/N) | WC path (N/N) | CP path (%) | WC path (%) |
| --- | --- | --- | --- | --- |
| Front (anti-dive) | +0.00514 | -0.00389 | -2.72 | +2.06 |
| Rear (anti-squat) | -0.00895 | +0.00473 | -4.74 | +2.51 |

The kinematic CP path agrees with the force pulses. The `avg_` coefficients over
the 11 poses are +0.00525 front and -0.00881 rear. The rear anti-squat of the
inboard drive is +2.5 %, not the -4.7 % of `avg_anti_squat_pct`.

### Net jacking is not geometric load transfer

Net jacking J is the vertical force that a lateral force puts on the whole
axle. The moment-equivalent height comes from the left and right difference. One
is not the other:

- An axle can have zero net jacking and a nonzero differential. The height is
  then nonzero.
- Two axles with the same differential and different net jacking have the same
  height.

The tests `test_four_post_anti_roll_key_is_net_jacking_with_zero_net_and_nonzero_differential`
and `test_four_post_fbrc_height_is_set_by_the_differential_and_not_by_net_jacking`
show both cases.

On the BobSim default car, `avg_anti_roll_front_pct` is 0.032 %. Read it as
zero:

- J is odd in roll. Per pose it goes from +8.1e-3 N/N at -0.75 deg to -7.9e-3
  N/N at +0.75 deg. The mean over the symmetric sweep cancels. The per-pose
  values are in the `fr_anti_vs_roll` series.
- The mean, 7.7e-5 N/N, is the size of the measurement resolution. At a fixed
  pose, the chassis reaction drifts about 0.026 N/s on the default car. Over the
  3 s between the pulse and the dead tail, that is about 0.08 N on a 1000 N
  pulse, or 8e-5 N/N (0.03 % of h/t).

### Elastic share

The roll sweep imposes a roll angle with no lateral force. The front and rear
transfers come from the dead-tail contact loads. So the share is the elastic
share of the springs and bars. It has no geometric or unsprung part. At zero
roll the share is 0 / 0, so that pose is not counted. A pose where the front and
rear transfers have opposite signs is invalid.

## Status column

The metrics CSV has the columns `metric`, `value` and `status`.

| Status | Meaning |
| --- | --- |
| `ok` | Every counted pose gave a valid sample. |
| `partial` | Some poses gave a valid sample. The value uses only those. |
| `invalid` | No pose gave a valid sample. The value is empty. |
| `unavailable` | The check did not run, for example because a signal is missing. The static balance keys use it. |

A sample is invalid when it is missing or not plausible. These rules replace
quiet filters that hid an invalid sample:

- A pose with no output sample in its window is missing. Before, the nearest
  sample outside the window was used.
- A measured roll pulse force outside 5 % to 500 % of half the commanded force
  magnitude is invalid. Before, that reference force replaced it.
- A bad jacking signal stays bad. Before, the roll jacking quietly switched to
  the contact-load sum.
- An invalid elastic share stays empty. Before, it was filled from the
  neighbor poses.
- The elastic share keeps the sign of each transfer. Before, `abs` hid opposite
  signs.

`common/metrics_csv.py` reads the CSV. `read_metrics` gives NaN for a status
that the caller does not accept. A CSV without a status column gives status
`unknown`, which `read_metrics` does not accept by default. These readers use it:

- `optimization/response/pipeline/generator.py`. A spring free length balance
  needs a motion ratio with status `ok`. Otherwise it stops and asks for a new
  FourPost run.
- `simulations/envelope/vehicle_yaml.py`. A roll stiffness that is not `ok` falls
  back to its default. `lltd_source` names each roll stiffness that fell back.
- The regression baseline test. Every baselined metric must have status `ok`.

## Heave poses in tension

On the default car, the two heave poses with 24 mm and 30 mm of droop extend the
springs past their free length. The rig then pulls the tires down. BobLib
reports the contact Fz clamped at 0 N. The chassis reaction shows the pull. The
per-pose residual, contact Fz sum plus the jacking force signal, is in the
`fr_tension_residual_vs_heave` and `rr_tension_residual_vs_heave` series. It is
about 291 N and 742 N front and 219 N and 564 N rear at those poses. At the
other poses it is below 1.2 N, the time drift of the rig.

These poses are rig-only geometry. `heave_cp_tension_points` counts them. The
`<corner>_fz_vs_heave` series shows NaN there, not 0 N. The anti records keep
the poses: the incremental jacking uses the chassis reaction and the pulse force,
and the geometry does not change during the pulse.

## Migration

Keys keep their names. Labels and the values below change.

- `avg_lltd_front_pct`: 49.2473 to 49.2547 on the default car (`_frac` the same
  over 100). The zero-roll pose is no longer filled from its neighbors.
- `avg_antiroll_geometry_lltd_delta_pct`: -1.2058 to -1.2060. It now uses the
  same 10 poses as the share. It is no longer exactly `avg_lltd_front_pct` minus
  `avg_roll_rate_distribution_front_pct`. On the default car the two differ by
  0.008 points.
- New keys: `heave_cp_tension_points` and `anti_force_path`.
- New keys: `longitudinal_jacking_coeff_<axle>_<path>_path` and
  `anti_dive_<path>_path_pct`, `anti_squat_<path>_path_pct`. The `avg_` anti keys
  keep their names and values. The summary page shows the four percents under
  "Anti by Force Path".
- New CSV column: `status`.
- Report labels: "Geometric Anti-Roll" is now "Net Axle Jacking". "LLTD (Front)"
  is now "Elastic Share". The anti-dive and anti-squat labels name the force
  path. The vehicle review shows net jacking in N/N and no anti-roll rows.
- An app config saved before this change gets the new jacking, FBRC and elastic
  share plots from the seed config.
