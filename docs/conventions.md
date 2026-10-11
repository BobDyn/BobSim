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

## TTX25 MkII damper settings

Under either `front.actuation.shock` or `rear.actuation.shock`, replace the entire
`damper_table` entry with the following `damper` mapping. Retain the shock's other
fields (mount, spring table, and free length). This is an example setting, not a
recommended vehicle setup:

```yaml
damper:
  model: ohlins_ttx25_mkii
  dataset: ttx25_mkii_c12_r12_pdf_v1
  compression:
    valve: C12
    low_speed_clicks_from_closed: 6
    high_speed_turns_from_open: 4.3
  rebound:
    valve: R12
    low_speed_clicks_from_closed: 10
    high_speed_turns_from_open: 4.3
```

Specify exactly one of `damper` and `damper_table`. Explicit velocity/force tables
remain supported, in m/s and N, sorted by increasing velocity, with negative
rebound values, an exact `[0, 0]` row, and positive compression values. The
independent variable is **minus the derivative of shock length**, not wheel speed.

The initial dataset digitizes page 2 of `_TTX25 MkII Dyno N vs mmps.pdf` (C12/R12).
Only the following measured sweeps and interpolation within them are supported,
independently for compression and rebound:

- HS=4.3 turns from open, LS=0..25 integer clicks from closed. Measured clicks:
  0, 2, 4, 6, 10, 15, 25. Other integer clicks interpolate force at common speeds.
- LS=0 clicks, HS=0..4.3 turns. Measured turns: 0, 1, 2, 3, 4.3.

Other valve specifications and combinations such as LS=6/HS=2 fail explicitly.
No extrapolation in adjuster setting or interpolation between valve specs occurs.

#### Inspect, generate, and run

From the BobSim root, inspect the resolved table and its provenance:

```bash
python -m _0_Utils.damper_curves vehicle.yml --output resolved_dampers.json
python -m _0_Utils.damper_curves vehicle.yml --write-modelica
make standard-build
```

The damper-only write updates the two `damperTable` fields in the existing
Modelica record without changing its QSS initialization, vehicle template, or
FourPost files. YAML edits alone do not update an already compiled model.
The resolved JSON records dataset SHA-256, settings, contributing curves,
interpolation weights, and limitations. Result archives include
`damper_curves.json`; packaged builds include only the runtime TTX25 dataset JSON.
The existing full-stack `make sync-vehicle-write` and app **Write to MBD** actions
rewrite other Modelica files, so do not use them for a damper-only settings change.

Curve generation works with the existing BobLib tabular component. The additional
table validation and diagnostic outputs require the updated BobLib checkout.
The sibling `BobLib` repository and BobSim's `_0_Utils/external/BobLib` submodule
are separate checkouts: editing one does not update the other. Publish the BobLib
changes separately, advance BobSim's submodule to that commit, then sync the
damper tables and rebuild. Commit that submodule pointer with the BobSim
changes so other users receive the same implementation.

Reduced-order 6/10/14DOF models now evaluate the full table. Their existing static
motion ratio is wheel travel / shock travel: shaft speed = wheel jounce speed / MR,
and wheel damping force = shaft force / MR. If FourPost metrics are absent, the
existing MR=1 fallback remains; accurate wheel damping requires valid motion
ratios. The scalar damping parameter remains an endpoint-equivalent diagnostic.
3DOF has no suspension dynamics. Modal review values are local linearizations.

#### Fidelity and diagnostics

This is a chart-derived approximation, not a validated calibration of an
individual shock. The dataset assigns positive plotted force to compression and
negative to rebound; the PDF does not explicitly label these branches. Confirm
this assignment against a known-direction dyno test before relying on absolute
compression/rebound calibration.

The first sample is 12.5 mm/s. An imposed zero-force origin and linear segment to
that point approximate the near-zero loops; the occluded R12 LS25/HS4.3 sample
uses interpolation from the origin to 20 mm/s. Hysteresis, friction, gas preload,
temperature and acceleration effects are not independently identified. Interpolation
between adjuster settings is a modeling assumption, not an extra measurement.

Maximum digitized shaft speed is 0.25 m/s. Both engines extrapolate using the last
two points. Updated BobLib exposes `TabularDamper.extrapolating` and
`dissipatedPower`; reduced transients expose `damperCompressionVelFL` and
`damperExtrapolatedFL` (and FR/RL/RR equivalents). The extrapolation channels describe
saved samples; they are not a bound on intermediate solver evaluations.

The source digest, raw pixel samples and processed data live in
`_0_Utils/damper_data`. Reproduce the extraction with a Python environment containing
`pypdf`, `numpy`, and Pillow:

```bash
python _0_Utils/damper_data/digitize_ttx25.py "path/to/_TTX25 MkII Dyno N vs mmps.pdf" temp/ttx25
```

Inspect both generated trace overlays before replacing a dataset. Add new
calibrations under a new dataset version and extend the resolver's explicit
registry. Default vehicle settings are not automatically converted to TTX25.

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
