# QSS and transient lap-time simulation

**TL;DR:** One track, one racing line, one DOF model (3/6/10/14) → two results: QSS (idealized, point-wise envelope-bound) and transient (executable, with dynamics). Delta = controller lag, transient buildup, effects invisible to equilibrium envelopes.

See [simulation-entrypoints.md](simulation-entrypoints.md) for fidelity context.

## Running lap simulations

```bash
make lap-eval-qss            # QSS only
make lap-eval-transient      # transient only
make lap-eval                # both
make lap-eval-all-dof        # all fidelities (3/6/10/14 DOF)
make lap-validation-visuals  # quick acceptance matrix across all DOFs
```

**Config:**
- Default: `_3_StandardSim/LapTimeEval/lap_time_eval_config.yml`
- Override: `make lap-eval LAP_CONFIG=path/to/config.yml`
- Change `model_dof` (3, 6, 10, or 14) in the config to select fidelity

**GGV behavior:**
- If GGV CSV exists → uses it as-is (provenance must match `model_dof` when comparing fidelities)
- If missing → generates from selected model
- High-slip roots (sideslip > `max_abs_beta_rad`, steer > `max_abs_steering_rad`) are rejected; use EnvelopeSim YMD workflow for deliberate high-beta states
- Paths can contain `{model_dof}` placeholder to prevent silent reuse across fidelities
- Sidecar `summary.json` records provenance; cache mismatch regenerates

**Power caps:**
- Default endurance: 32 kW constant (energy-budget proxy, not thermal model)
- Acceleration/autocross/skidpad: 80 kW VCU limit (from `vehicle.yml`)

**Validation visuals:** `make lap-validation-visuals` generates a resumable 3/6/10/14DOF comparison matrix under `temp/lap_time_validation/`:

| Folder | Contains |
| --- | --- |
| `<dof>dof/envelopes/` | GGV 2D/3D, capability metrics, YMD views |
| `<dof>dof/qss/` | track corridor, racing line, speed/accel profiles |
| `<dof>dof/transient/` | path tracking, velocity/yaw/steer/accel histories, body/wheel states |
| `<dof>dof/` | raw CSVs and summary |
| `overlays/` | cross-fidelity GGV, speed, yaw-rate, lap-time comparisons (appears after 2+ DOFs complete) |

**Start here:** inspect `overlays/` to see whether an added DOF changes system-level results.

**Re-run options:**
```bash
make lap-validation-visuals              # resume from cached work
--force-laps                             # refresh laps only (keep envelopes)
--force                                  # regenerate everything
```

(Git ignores the bundle.)

## Track format and racing line

**Track input:** closed sequence of paired gates with left/right boundaries (metres):
```csv
left_x_m,left_y_m,right_x_m,right_y_m
...
```

Legal vehicle-center interval = gate midline ± (half vehicle width + safety margin).

Periodic cubic splines → arc-length-sampled line with heading, curvature, segment length.

**Default track:** `_3_StandardSim/LapTimeEval/tracks/endurance_michigan_2019.csv` (2019 FSAE Michigan; metres, provenance in `tracks/README.md`).

**For acceptance tests:** `endurance_reference.csv` (synthetic 694 m course, fast for repeated 10/14DOF runs). Full 2 km course → `temp/lap_time_validation/reference_tracks/`. Both are rendered so real course is always visible as a system-level reference, not confused with test-only synthetic track.

Three line modes are available:

- `centerline` uses zero gate offset.
- `minimum_curvature` minimizes integrated squared curvature and is useful as a
  fast, vehicle-independent seed.
- `minimum_time_qss` starts from the minimum-curvature line and minimizes the
  actual propagated QSS lap time. This is the default.

Integrated absolute curvature is deliberately not the final objective. It is
nearly fixed at one revolution for many simple closed tracks and does not price
corner radius, acceleration zones, braking zones, or speed-dependent grip.

## QSS calculation

At every path sample, curvature and the GGV lateral boundary set a local speed
ceiling. Alternating closed-loop forward and backward passes then enforce the
available combined acceleration and braking at each speed and lateral load.
The final segment time uses the two endpoint speeds.

The output `qss_lap.csv` contains station, path geometry, speed, longitudinal
and lateral acceleration, and segment time. It is an equilibrium envelope
calculation: it does not include actuator lag, tire relaxation, or the time
needed for roll, pitch, wheel-speed, and wheel-hop states to settle.

## Forward transient calculation

The transient begins from a steady-state trim at the first QSS path point. If
that interpolated GGV point lies numerically on the feasibility edge, the
initializer searches inward in speed for the nearest valid equilibrium. A
feedforward/feedback driver commands:

- a sparse steady-state roadwheel-steer profile, interpolated along the path,
  plus heading and cross-track correction; and
- QSS longitudinal-acceleration feedforward plus speed-error correction.

Wheel torque is distributed using the vehicle drive and brake fractions. The
same suspension instant links, wheel rates, bar rates, tire forces, body states,
wheel speeds, and unsprung states used elsewhere in `dyn_py` are therefore
active according to the selected fidelity.

`transient_lap.csv` records time, wrapped station, unwrapped progress, tracking
errors, target/actual speed, and yaw rate. `summary.json` reports QSS time,
transient time, their delta, completion, and maximum lateral error.

The summary also records the active model space and validity limits. This is a
single-configuration simulation, so its `swept_parameters` list is empty. DOE
workflows must separately identify the one parameter changed in each variant;
the EnvelopeSens interval-splice table now does that explicitly and writes an
active/swept-space study manifest.

## Interpreting validation

First require the transient run to complete the lap without leaving the legal
corridor. Then compare QSS and transient speed, acceleration, yaw rate, and
attitude histories. Finally replay the same maneuver in BobLib and use the
existing reduced-order signal correlation tools. A smaller QSS/transient delta
does not by itself prove fidelity: agreement with BobLib and measured vehicle
data remains the reference.

The current driver follows a fixed QSS reference; it is not yet a closed-loop
optimal-control solver. Future transient line optimization can replace the
driver/objective without changing the shared track or vehicle equations.

## Verification boundary

The automated tests exercise equation evaluation, constant-radius QSS, a GGV
boundary point, a YMD point, and equilibrium-start transient integration for
all four fidelities. The validation bundle additionally requires every model
to converge its QSS lap, complete the transient lap, and remain inside the
track corridor. Non-converged YMD cells are masked in figures rather than
drawn as valid results.

This establishes internal functionality, not external truth. BobLib and test-
vehicle correlation remain a separate validation phase.

Simulation-only outputs support design trends and raw event-time sensitivities,
not Formula SAE competition points. BobSim does not contain a QSS-to-points
conversion. Such a claim requires controlled correlation, uncertainty, matching
competition telemetry, and demonstrated response-space coverage; absent that
evidence, `summary.json` declares `competition_points_supported: false`.
