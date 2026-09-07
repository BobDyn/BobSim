# Skill: import SHARK suspension geometry

**Use when:** you have a Lotus SHARK (`.shk`) export for one axle and need it
merged into a `vehicle.yml`, with the vertical datum handled correctly rather
than assumed.

**Underlying tool:** `_0_Utils/shark_import.py` (CLI + library — this skill
sequences it, it doesn't reimplement it). Coordinate conventions and the
vertical-datum rules it enforces: [`docs/conventions.md`](../../docs/conventions.md).

## Steps

1. **Locate the `.shk` file(s).** SHARK describes one corner of one axle in
   millimetres. A full car needs a front and a rear file.

2. **Import the first axle**, merging into the repo's baseline `vehicle.yml`:

   ```bash
   make shell   # or run natively if you have PyYAML installed
   python -m _0_Utils.shark_import <front.shk> -o <variant>/vehicle.yml --name "<car name>"
   ```

   This writes `<variant>/vehicle.yml` *and* a `<variant>/vehicle.datum.json`
   sidecar recording the vertical-datum verdict for that axle.

3. **Read the printed report.**
   - `frame`: the SHARK file must agree with the baseline wheel centre in X/Y
     to ±0.05 mm, or the import refuses outright — don't retry with a bigger
     tolerance, establish the frame explicitly instead.
   - `z datum`: `shared_ground_plane` = resolved; `unresolved` = z-dependent
     curves will be withheld downstream. That's a deliberate fail-closed
     behavior, not a bug — see the "what happens if it's unresolved" step below.

4. **Import the second axle**, merging into the already-imported car but
   pointing the datum check back at the *original* baseline — not the
   partially-imported file, which would compare the datum to itself and
   falsely report a resolved match:

   ```bash
   python -m _0_Utils.shark_import <rear.shk> -o <variant>/vehicle.yml \
     --baseline <variant>/vehicle.yml --datum-baseline vehicle.yml
   ```

5. **Overlay against the reference kinematics** to sanity-check the import:

   ```bash
   make shark-overlay SHARK=<variant>/vehicle.yml
   # or, with a live .shk in hand:
   make shark-overlay SHARK=<front.shk> ARGS="--four-post"
   ```

## If z-dependent metrics are missing from the report

That's `_0_Utils/shark_import.py:datum_gate` withholding them, not a solve
failure. Roll-centre height/migration and four-post jacking metrics come back
empty rather than wrong when the vertical datum can't be verified.

Resolve it with whoever produced the export — is the offset a real
ride-height change or a frame shift? — then re-import. The digest in the
sidecar ties the verdict to the exact geometry it was assessed against, so
any further hand-edit to the geometry invalidates it automatically rather
than silently going stale.
