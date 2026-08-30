# Vehicle geometry conventions

Reference for the `boblib.vehicle.v1` schema (`vehicle.yml`). Everything here was
derived from the code cited alongside it, not from external documentation — if a
statement has no citation, treat it as unverified.

## Axes and origin

Right-handed, chassis-fixed frame. Units in `vehicle.yml` are **metres**; angles
are **degrees**.

| Axis | Direction | Evidence |
| --- | --- | --- |
| **+X** | Forward (towards the front of the car) | Front `wheel_center_m` x = `0.0`, rear x = `-1.5494`. `tire_front` is built as `wheel_center + [R·cos(toe), R·sin(toe), 0]` (`_5_App/kinematics.py`), so +X is the direction the wheel points. |
| **+Y** | Left / outboard on the stored side | Every stored hardpoint has y > 0, and the opposite corner is derived by a Y sign flip (`Vector.mirrorXZ`, `BobLib/Chassis/Chassis_DWBCStabar_DWBCStabar.mo`). |
| **+Z** | Up | `contact_patch = wheel_center - [0, R·sin(camber), R·cos(camber)]` (`_5_App/kinematics.py`), i.e. the contact patch is *below* the wheel centre. |

**Origin.** X and Y originate at the front-axle centreline: front `wheel_center_m`
is `[0, +0.6061, ...]`.

**Z is unresolved, and the two readings disagree by the tyre's deflection.** Using
the *unloaded* `radius_m` = `0.2045`, the baseline rear (`wheel_center_m` z =
`0.199898`) puts the contact patch at z = `-0.004602`, 4.6 mm below zero — on which
reading z = 0 is a design datum, not the road. But `2027_RR_SuV12.shk` carries a
trailing scalar of `199.890` mm in its geometry block, which is the *loaded* rolling
radius; against that, the same wheel centre puts the contact patch at `+0.008` mm,
i.e. z = 0 **is** the road surface at design ride height with the tyre loaded. The
4.610 mm between the two radii is exactly the tyre deflection, so both readings are
arithmetically self-consistent and the file does not say which one it means.

Treat the vertical datum as **unresolved**. Do not assume z = 0 is the road surface,
and do not assume it isn't. See `assess_z_datum` in `_0_Utils/shark_import.py`, which
refuses to take an imported z raw while this is open.

## Mirroring

Only one side is stored. The opposite corner is derived by negating Y. A
consequence worth knowing: in a pure bump (heave) sweep both sides receive equal
jounce, so the two front-view instant-centre lines are exact mirror images about
y = 0 and the roll centre necessarily lies on the centreline. `rc_y_mm = 0.0` in
the bump sweep is therefore *exact*, not a placeholder.

Asymmetric left/right geometry cannot be represented in this schema. An importer
that encounters it must fail rather than pick a side or average.

## Sign conventions

- **Camber** — inward wheel tilt is negative. Stated in `_5_App/kinematics.py`
  (`curve_values`), which notes the legacy `simulation_toolkit` `gamma` was
  *inclination*, carrying the opposite sign on the left side. Computed as
  `atan2(radial_y, radial_z)` where `radial = wheel_center - contact_patch`.
- **Toe** — `atan2(forward_y, forward_x)` where
  `forward = tire_front - wheel_center`. Toe-in on the +Y (left) side is positive.
- **Roll** — sampled from `frKnC.roll` in radians; the four-post report scales to
  degrees by `57.2958` (`four_post_eval_sim.py`).
- **Heave** — the four-post driver negates the raw signal
  (`heave = -sig("frKnC", "heave")`), so positive heave in the report means the
  chassis moves *up* relative to the contacts.

## Hardpoint naming

Suffix `_i` = inboard (chassis-side) pickup, `_o` = outboard (upright-side) joint.
`fore`/`aft` distinguish the two inboard pickups of a wishbone. Front-view and
side-view instant centres are derived from the *midpoint* of each wishbone's two
inboard pickups (`front_view_instant_center` / `side_view_instant_center`).

## Importing external geometry

External suspension exports (e.g. Lotus SHARK `.shk`) are typically in
**millimetres** and may use a different origin. Before importing, prove the frames
agree rather than assuming: compare a point the two models should share (the wheel
centre is a good candidate, since package points are usually held fixed across a
redesign). If x and y agree to within a few hundredths of a millimetre, the frames
are the same and coordinates may be taken raw. If they do not, the datum must be
established explicitly — do not silently shift.

**X and Y agreeing does not license taking Z raw.** For `2027_RR_SuV12.shk` the
wheel centre matches the baseline to `dx = -0.0000`, `dy = -0.0008` mm — conclusive
for the in-plane frame — while `dz = +1.190` mm. That offset is *not* established as
a ride-height change. Reading the file's trailing scalar as the loaded radius, the
baseline lands on the ground plane (`+0.008` mm) but the SHARK wheel centre misses it
(`+1.198` mm): the file corroborates the datum for one car and contradicts it for the
other. `TITLES` is empty, so nothing in the file settles it.

Until someone confirms with whoever produced the export whether the 1.19 mm is a real
ride-height delta or a datum shift, the importer marks the datum `unresolved` and the
overlay withholds every z-dependent curve — roll-centre height, migration, absolute
RC and IC z, and front-view swing arm. Angles and lengths are unaffected: a rigid
vertical translation of a corner changes neither, which is why the rest of the deck
still publishes.

### The datum gate

The verdict is recorded **per axle** in a `<vehicle>.datum.json` sidecar, so a rear
import and a later front import each carry their own, and merging one does not erase
the other. Each record is bound to a `geometry_digest`: a SHA-256 over exactly the
inputs `CornerKinematics.from_vehicle` reads — suspension hardpoints, the steering
rack pickup and the wheel. Actuation is excluded, because it takes no part in the
kinematic solve and carries no vertical-datum meaning.

`datum_gate()` fails closed. Z-dependent output is published only when **all** hold:

| Condition | Otherwise |
| --- | --- |
| A sidecar exists | missing → withhold |
| Every recorded axle is `shared_ground_plane` | any `unresolved` → withhold |
| Every recorded digest matches the file on disk | edited → withhold |

The digest is what stops a hand-edit from inheriting someone else's verdict. Nudging
`wheel_center_m` z to probe the datum question is a plausible thing to do, and without
the digest the stale record would keep vouching for geometry that no longer exists.

The gate covers the **four-post jacking metrics too**, not just the kinematic curves.
Anti-dive, anti-squat and geometric anti-roll are all measured against the contact
patch, so they move with the datum exactly as roll-centre height does.
