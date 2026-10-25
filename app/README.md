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
response, Track and Laptime. Kinematics and vehicle response use Modelica/BobLib;
vehicle response no longer offers reduced-model selection. Performance envelopes
retain DynPy fidelity selection, Track uses the local Python racing-line generator,
and laptime retains its Python QSS/transient workflows. Historical reduced response
results remain readable, but their configurations cannot be run or silently
converted into Modelica handwheel-angle inputs. Each overview shows inputs and
results, with the method in a disclosure. QSS Lap connects to reusable GGV and racing-line analyses.
Its Run action is available when both linked results are valid. Existing BobLib
steady-state studies remain accessible under Vehicle response.

Four Post runs the cached front/rear KnC and rear traction binaries directly;
it does not generate a vehicle record or invoke OpenModelica. Missing or stale
bundles disable Run and point to Architecture. Procedure amplitudes and the saved
setup are applied at runtime. The adapter joins front/rear signals into the same
four-corner report, retaining static balancing, contact-load validation, stiffness
and frequency estimates, metrics and plot layouts. Setup → Report lets the user
select individual plots; all existing plots are included by default. Rear heave
force response uses shaft traction for anti-squat. Binary provenance and combined
signals are archived alongside the report.
Force-based settings specify front brake-force share and independent front/rear
left lateral-force shares. Brake share weights anti-dive relative to total braking
force; anti-squat remains rear-drive normalized. The per-axle probe magnitude is
unchanged. Lateral shares are applied in the native rigs, and the report uses the
same roll-axis reaction and posed-CG calculations as the geometry view. These
inputs are applied force shares, not an Ay-derived vertical load-transfer model.

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
in Architecture. Each supported combination has separate front KnC, rear braking KnC, rear traction,
and maneuver executables. Rear traction uses the existing static differential-input
shaft/housing reaction path, independent of rear brake placement. It applies
equal contact forces and equal shaft torques; differential slip/locking dynamics,
CV-joint force distribution and shaft bending are outside this geometry test. Other included components are listed in that view.

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
RC equivalent height uses the incremental roll reaction plus the separately
grounded front steering support reaction. The equivalent force acts at world
y=0; its height is shifted from the world origin to the mean unloaded contact
plane. This includes actual force lever arms rather than nominal track. The
test still uses equal left/right lateral force pulses. Geometric anti-roll is RC height
divided by posed sprung CG height above the same contact plane; it can be
negative even when net jacking is zero. It is a geometric proxy, not a whole-car
roll-resistance percentage. Jacking subtracts
the unloaded same-pose response from each 1000 N pulse. Processed longitudinal
outputs are front anti-dive and rear anti-squat. Both remain axle-normalized:
`100 * (signed jacking / axle Fx) * reference wheelbase / posed CG height`,
with a negative sign for front anti-dive and positive for rear anti-squat.
Brake bias and drive-force split are deliberately excluded. The sprung-plus-driver
CG is mass-weighted, translated with imposed heave, rotated with roll, then
referenced to the mean unloaded contact plane at each pose; missing/invalid
references and unloaded tire contacts remain missing. Front braking uses the selected brake reaction path;
rear anti-squat uses the separate shaft traction run. Rear longitudinal jacking
plots also use traction, matching the processed percentage. Rear braking CSVs
remain available from Simulation. Missing traction binaries leave anti-squat
unavailable with a build message rather than substituting braking results.
The front, rear braking, and rear traction runs execute concurrently,
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
converts results; `native_four_post.py` adapts axle runs to the four-corner report;
`native_service.py` exposes native build/run jobs.

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


### Force-split controls

The existing heave and roll horizontal axes remain unchanged. Front anti-dive,
rear anti-lift, rear anti-squat, force-based equivalent RC height, lateral jacking /
applied force, moment / applied force, and force-based anti-roll each have
an independent force-share slider in their plot card and expanded view. Moving
it changes the entire travel curve locally, without another simulation.

Anti-dive scales by front brake-force share; anti-lift scales by its rear
complement. RWD anti-squat retains the whole heave curve with its drive-share
control fixed at 100% rear. These are actual tire-force shares, not necessarily
hydraulic pressure bias.

At every roll sample, equivalent RC height combines the independent lateral
responses: `h = share * h_left + (1-share) * h_right`. Native tests verify equal
and 75/25 loading. Lateral-force share is distinct from vertical load transfer;
both lateral forces have the same sign. Invalid native samples remain missing.

The KnC wrapper's `lateralLeftShare` setter changes only lateral-force gains;
longitudinal probes remain symmetric. Compiled artifacts and independent native
responses are cached and reused.

The displayed anti-roll percentage uses `100 * h_equivalent / h_CG`, with both
heights above the same contact plane. It is a force-response measure and follows
the chosen lateral-force split. The old geometry-only RC/CG proxy remains an
internal diagnostic, not the displayed anti-roll curve. Moment/applied force
retains its documented rig-axis reference; the equivalent RC includes the
steering support correction and contact-plane reference.

KnC artifact selection uses only the chosen axle's suspension type and brake
reaction path. The opposite axle, differential model, and spatial rotor setting
cannot invalidate a KnC artifact. Rear traction aliases the locked rear
DifferentialInput artifact, while its result processing still labels the run as
traction. `make knc-catalog` prebuilds all 15 unique artifacts; see
[the workflow](../docs/workflows.md#precompiled-geometry-catalog).

Field help popups link to the relevant BobDocs Vehicle Dynamics section, or to
the BobSim app guide for operational controls.

Section help maps Setup areas and registered workflows to the public
[Section Reference](https://bobdyn.com/bobsim/section-reference). The maps in
`static/app.js` are checked by `tests/app_help_traceability.cjs`; add a documented
topic when adding a section/workflow. To verify built BobDocs anchors locally,
pass its `docs/.vitepress/dist` directory as the test's third command-line
argument (after a JSON array of workflow IDs). Keep field-level physics links
more specific than the section landing page.

Four Post Report also offers five optional native geometry plots: geometric RC
height and lateral position, jacking/applied force, moment/applied force, and
the geometric anti-roll proxy. They default off, retain undefined measurements,
and reuse the Geometry view's processed native values. Axle quantities use
front/rear panels; existing corner-alignment plots retain their quad layouts.

For a local BobDocs preview, set the webview's `localStorage` key
`bobsim-docs-origin` to `http://127.0.0.1:5173` and reload. Help links retain
page paths and exact anchors while using that local origin. Only HTTP(S)
localhost/127.0.0.1 overrides are accepted. Remove the key to restore public
links. This is a development preview setting, not a packaged-app default.

Report page choices live in a collapsed Pages dropdown with a live selected
count. Expanding it exposes the checkboxes and metric help; collapsing it does
not change selections or omit them from saved configuration.

Simulation outline ordering is saved per vehicle. Drag an analysis title to
reorder whole groups, or a simulation title to reorder within its group; a
highlighted horizontal bar marks the insertion point. The actions menus also
provide Move up / Move down, disabled at the ends. Reordering preserves active
setup edits, saved inputs, visualizations, and linked results. Dragging Results
onto a QSS input still creates the existing GGV/racing-line connection.

## Editable report canvas

Results opens the saved run as a continuous report document after every plot page
has preloaded. Axis labels select named metrics and independent views from the
recorded report definitions. Changing a view replaces both X and Y data together,
preserving corner-specific signs and conversions. The complete axis label opens one popup for the metric/view and display units.
Edits remain pending until Apply, which updates the group and closes the popup;
Cancel discards them without re-rendering the report. Standard subplot titles identify the
provided values and are fixed. Metric choices show the number of values and maximum
layout size; smaller layouts can select which values to display.

Single/dual/triple/quad pages can combine independent metric groups. A dual metric
and a single metric can occupy a triple page; edits affect only their own group.
Plots may be split into independent groups or filled from one metric. Mixed pages
allow custom subplot titles. Clicking a graph opens appearance controls only: curve
styles, legend, fits, limits and shared limits. Linear fits show their equations
on the plot and in PDF exports, using displayed axis units. Advanced YAML still edits the mapping consumed by `PlotEngine`.
Page handles reorder the document; disabled pages are omitted from PDF export.
Mouse-wheel scrolling uses the browser's smooth-scroll animation instead of
per-frame JavaScript position updates; small trackpad gestures and reduced-motion
settings retain native scrolling. Loading replaces the old preview before the
first request, and hidden Results views do not instantiate a legacy PDF viewer.
`report_metrics.js` maps named metric views onto the underlying plot definitions.

`report_editor.py` reads archived inputs, caches processed plot data, and renders
previews with BobSim's palette. Every page is preloaded; scrolling does not launch
new render requests. Export renders the same definitions with print styling and
writes a separate PDF and layout YAML. Original run files remain unchanged.
`report_editor.js` owns document interaction and plot-local controls. Report viewing
and exporting do not reserve the simulation execution workspace. Explicitly reusing
a layout for future runs does reserve it, like other input changes.

`ReportEngine` retains processed series in a `.report-data.json` sidecar, copied
into saved runs. Older native Four Post runs can reconstruct plots using their
archived vehicle, combined signals and native force curves. Other old runs expose
recorded CSV signals and identify unavailable processed series. Layouts are saved
per run; shared-engine simulation layouts can also be reused for subsequent runs.
Custom Four Post layouts bypass automatic replacement of default plot definitions.

Simulation results default to Animation for BobLib/Modelica and Signal Explorer
for Python analyses, including YMD and GGV. Reports remain available for both.
Modelica output archives trigger geometry conversion automatically; native Four
Post uses its archived binaries and calibration. Animation failures preserve the
simulation results and are recorded on the saved run. Legacy results without
geometry need a new run. Reduced Python states are not offered as animations.

YMD uses 14DOF only. Every run solves nine speeds from one ninth of the
vehicle drivetrain speed limit through that limit, using up to four workers.
The report reference speed selects the nearest accepted recorded slice; it
does not restrict coverage. Legacy optional speed-sweep settings are ignored.
Its Raw CSV retains every computed speed-sweep map. Signal Explorer defaults to yaw moment versus lateral
acceleration, with a velocity slider through recorded speeds. Both constant
sideslip and constant steering families retain gaps at rejected points. All
slices are preloaded and use common axis limits; dragging never starts a solve.
Older archives with one speed remain viewable at that speed.

YMD exports the sampled outer yaw-moment limits versus lateral acceleration
and speed as CSV, PNG, and a PDF page. The explorer overlays those limits on
each recorded carpet. Invalid triangles and empty speed slices remain gaps.
These are sampled bounds within the configured steer/sideslip grid, not a
guarantee of a global optimum; internal gaps in yaw authority still require
reading the carpet. Motor power/force and braking limits also gate acceptance.
