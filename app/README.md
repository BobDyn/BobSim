# BobSim App

The browser app configures vehicles, runs simulations, and displays results.
User documentation: [bobdyn.com/bobsim/app](https://bobdyn.com/bobsim/app).

```bash
make app                  # Docker
python -m app.app         # host Python and local simulation tools
```

Open `http://127.0.0.1:8765`.

## Views

| View | Contents |
| --- | --- |
| Architecture | Suspension, differential, brake placement, rotor mechanics, and reusable native binaries |
| Setup | Calibration, geometry preview, and saved vehicles |
| Simulation | Native KnC and maneuver runs, plus existing named studies and results |

Setup uses the architecture templates in `common/vehicle_templates`, including
direct, bellcrank, and bellcrank-stabar suspension. The preview shows hardpoints,
links, masses, and inertia.

## Data

Development data lives under `app/user_data`. Packaged builds use the user's
BobSim runtime directory. `storage.py` defines these paths:

| Path under `user_data/` | Contents |
| --- | --- |
| `config/app` | App settings and OpenModelica selection |
| `config/vehicles` | Saved vehicles |
| `config/simulations` | Saved run configs |
| `config/active` | Active simulation configs |
| `results/saved` | Archive packages |
| `workspaces/vehicles` | Per-vehicle generated configs and results |
| `cache/modelica` | Cached Modelica builds |

The UI assets are in `static/`. Default run configs live with their workflows.
`visualization/` captures scenes. `visual.py` and `static/visual.js` load and draw
them under Simulation → Captured scenes. Captures are separate from ordinary
simulation runs.

The app defaults to dark mode. The theme toggle saves `bobsim-theme` in
`localStorage`. Colors are defined in `static/styles.css` and `canvasPalette()`
in `static/app.js`.

The outline groups simulations under Kinematics, Performance envelopes, Vehicle
response, Track and Laptime. Each overview shows inputs and results, with the
method in a disclosure. QSS Lap connects to reusable GGV and racing-line analyses.
Its Run action is available when both linked results are valid. Existing BobLib
steady-state studies remain accessible under Vehicle response.

Named simulations are stored in `workspaces/vehicles/<vehicle>/simulations.json`.
Completed runs retain the simulation name, vehicle and config used at run time.
Removing a simulation keeps its saved runs.

## Module layout

- `app.py`: compatibility facade for existing imports plus the CLI entrypoint.
- `contracts.py`: shared dataclasses for workflows, actions, configs, fields,
  and outputs.
- `registry.py`: declarative workflow/action/build-target/config-field
  registry.
- `python_simulations.py`: app entry point for steering maneuvers, racing lines and DynPy lap runs.
- `runtime.py`: packaged-app runtime seeding, manifests, and cache invalidation.
- `toolchain.py`: OpenModelica discovery, verification, and environment setup.
- `server.py`: HTTP routing, JSON/file responses, and static/repo file serving.
- `actions.py`: job start, workflow dispatch, subprocess environment setup, and
  action result handling.
- `modelica_build.py`: Modelica executable detection, build signatures, build
  cache archives, and cache restore logic.
- `data_services.py`: app data layer for configs, vehicle libraries, result
  archives, processing workflows, and CSV result exploration.
- `jobs.py`: thread-safe job log/state store.
- `http_utils.py`: small HTTP parsing helpers.
- `storage.py`: canonical folder layout for shipped app assets and mutable user
  data.
- `tracks.py`: track CSV import and boundary previews.
- `tire_eval.py`: MF52 tire-load and curve payload generation for the UI.
- `modelica_generator.py`: vehicle YAML to BobLib Modelica generation.
- `desktop.py`: desktop/webview wrapper for packaged builds.
- `static/`: `index.html`, `app.js`, `styles.css`, and the vendored Inter font.

## Native architecture workflow

This integration branch pins BobLib PR #58 (`f35fa2f`) before merge. Select front
and rear suspension, differential, brake placement, and spatial rotor mechanics
in Architecture. Each supported combination has separate front KnC, rear KnC,
and maneuver executables. Other included components are listed in that view.

Choose **Build locally** for a missing executable. This requires OpenModelica,
Modelica 4.1.0, and VehicleInterfaces 2.0.2. Builds run as cancellable app jobs.
Successful bundles are cached in `app/user_data/cache/native`; subsequent runs
reuse them. Architecture, BobLib source, wrapper, or host-platform changes select
a different cache entry. Bundle checksums detect missing or changed files.
Executables still depend on the compatible local OpenModelica runtime libraries;
this is a local cache, not a portable artifact distribution service.

Setup values are validated against the compiled parameter contract and applied
in a fresh process. Unknown, structural, and dependent parameters are rejected.
Spring/damper tables support 64 points and aero maps 16 points per axis. Native
halfshaft inertia is a separate physical calibration (initial reference: 0.02
kg m²); the old equivalent damping inertia is not imported. Retired clutch and
shaft damping fields are hidden; differential choice belongs to Architecture.

The plot picker exposes native heave, roll, and front steering sweeps. Heave is
positive chassis-up displacement; steering is pinion angle, not rack travel or
road-wheel angle. Heave/roll curves use zero steering. Geometry is sampled from
unloaded plateaus with the bar removed. Geometric RC height uses front-view
wishbone midpoint/outer-joint projections from native positions, relative to the
mean contact plane; singular projections remain missing. A separate force-based
RC equivalent height uses differential contact-load response with nominal track
and equal left/right lateral force pulses. Geometric anti-roll is RC height
divided by reference sprung CG height above the same contact plane; it can be
negative even when net jacking is zero. It is a geometric proxy, not a whole-car
roll-resistance percentage. Jacking subtracts
the unloaded same-pose response from each 1000 N pulse. Anti percentages use
axle force and sprung CG height; they are not whole-car anti percentages. The
braked rig reports front anti-dive and rear braking anti-lift; acceleration
anti-squat requires a drive-load test. Front/rear runs execute concurrently,
repeated setups reuse results, and the UI coalesces edits and redraws without
waiting for tire diagnostics. Simulation runs the complete KnC protocol with an
explicit load amplitude and optional configured stabilizer. Front runs include
steering sweeps. Maneuvers currently run the standard ramp-steer experiment and
report its termination reason. CSV signals and input provenance are retained in
`app/user_data/results/native`; failed runs retain diagnostics. A model limit is
not reported as solver failure. Maneuvers use DASSL with an internal numerical
Jacobian, matching BobLib's simulation settings.

Maneuvers currently inherit BobLib's saved starting pose. Changed setups are not
automatically re-equilibrated; do not interpret their initial transient as a
settled-state comparison. KnC and maneuver runtime validation does not certify
all catalog combinations. KinPy remains a dependency of the reduced DynPy
workflows. The legacy generated-record/DOE workflows still require migration to
the new BobLib record layout; their regression gate is separate from native runs.
The legacy record writer is blocked on this revision to prevent overwriting the
new architecture models with incompatible generated files.

Ownership: `common/native_artifacts.py` builds and verifies bundles;
`native_calibration.py` translates setup inputs; `native_runs.py` executes and
converts results; `native_service.py` exposes them as app jobs.

Geometry's **Travel** button opens heave, roll and front pinion sliders. They
impose simultaneous displacements on the cached native KnC axle binaries through
`native_travel.py`, using an unloaded initialization solve rather than the full
plot protocol. Positions come from solved multibody frames; rear steering stays
locked and stabilizer rate is zero. Positive heave raises the chassis, and roll
is about +X. Travel never writes setup coordinates; hardpoint dragging is disabled
until travel is closed. Missing binaries can be built in Architecture. Requests
are coalesced while dragging and successful poses are cached in memory.

Native heave, roll and steering trajectories are sampled in the background for
the current values of the other two inputs. Once ready, slider input interpolates
those samples locally in the same render cycle, with no network wait. Releasing
runs an exact native solve and prepares trajectories for the new combination.
This interpolation is only a visual preview; plots and saved calibration use
native results. While a trajectory is preparing or unavailable, the view falls
back to coalesced native solves with animated transitions.

Roll plots also expose the loaded and unloaded roll-axis reaction, their
same-pose difference, and that difference per unit lateral load. These use
`-chassisActuator.rollDOF.tau`: positive is the suspension reaction onto the rig
about world +X through the origin, opposite the actuator holding torque.
The normalized response has units of metres and is not an RC height without
accounting for the reference axis and all external reaction paths; the front
rig includes the grounded steering actuator support reaction. Native integration
checks close the moment balance against contact forces and that steering reaction,
and repeat with halved and reversed lateral loads. The existing
compiled binaries expose this signal, so no BobLib rebuild is required.
