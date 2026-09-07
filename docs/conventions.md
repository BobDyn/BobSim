# Vehicle geometry conventions

Reference for the `boblib.vehicle.v1` schema (`vehicle.yml`). Everything here was derived from the code; if no citation appears, treat it as unverified.

## Quick reference

| Axis | Direction | Units | Notes |
| --- | --- | --- | --- |
| **+X** | Forward (front of car) | metres | Origin at front-axle centreline |
| **+Y** | Left / outboard | metres | Only left side stored; right side derived by Y-flip |
| **+Z** | Up | metres | ⚠ See vertical datum section below |
| **Angles** | Camber, toe, roll | degrees | See sign conventions below |

**Frame:** Right-handed, chassis-fixed. Origin: front `wheel_center_m` is `[0, +0.6061, ...]`.

## Sign conventions

- **Camber**: inward tilt is negative (`_5_App/kinematics.py`)
- **Toe**: `atan2(forward_y, forward_x)`. Toe-in on +Y (left) is positive.
- **Roll**: sampled in radians from Modelica; four-post report scales to degrees by 57.2958.
- **Heave**: negated from raw signal, so positive heave = chassis moves *up* relative to contacts.

## Mirroring and hardpoint naming

Only one side is stored. The opposite corner is derived by negating Y. Asymmetric left/right geometry cannot be represented; importers must fail rather than pick a side.

**In a pure bump sweep**, both sides receive equal jounce, so roll centre lies exactly on the centreline (`rc_y_mm = 0.0`).

**Hardpoint suffixes:**
- `_i` = inboard (chassis-side)
- `_o` = outboard (upright-side)
- `fore`/`aft` = two inboard pickups of a wishbone

Instant centres are derived from the *midpoint* of each wishbone's two inboard pickups.

## Importing external geometry

External suspension exports (e.g. Lotus SHARK `.shk`) are typically in **millimetres** with a potentially different origin.

**Before importing:**
1. Compare a shared reference point (wheel centre is good).
2. If X, Y match to within ±0.01 mm, frames are aligned; use coordinates as-is.
3. If they differ, establish the datum shift explicitly — do not silently assume.
4. **Z is separate**: X/Y agreement does not mean Z is correct. See "Vertical datum" below.

**What gets withheld:** If Z datum is unclear, z-dependent outputs are suppressed (roll-centre height, migration, absolute heights, four-post jacking metrics). Angles and lengths are unaffected.

### Vertical datum (Z)

Unresolved: Z may be the road surface, or it may not, depending on whether reference radii in external files are loaded or unloaded. A SHA-256 digest (`<vehicle>.datum.json` sidecar per axle) records the verdict. If the digest does not match the current geometry, z-dependent output is withheld until someone confirms the frame with the data source.

This is deliberate: better to withhold than to publish silently wrong height-dependent metrics.
