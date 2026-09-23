# Architecture

**Three fidelity levels:**

| Model | Fidelity | Use | Entry point |
| --- | --- | --- | --- |
| **BobLib Modelica** (reference) | High (MBD) | Single maneuver studies | `_3_StandardSim` + VehicleSim/FourPostSim |
| **`dyn_py` reduced-order** | Low-Medium (QSS/transient) | Envelopes, lap sim, DOE sweeps | `_2_EnvelopeSim` or lap workflows |
| **Kinematics** (`kin_py`) | Geometry only | Detailed suspension-element workflows | `_0_Utils/kin_py` |

**Philosophy:** BobSim orchestrates workflows and makes fidelity assumptions inspectable. It does not compete with BobLib; it is explicitly correlated against it.

See [simulation-entrypoints.md](simulation-entrypoints.md) for detailed fidelity context.

```
vehicle.yml ──► _5_App / _0_Utils ──► BobLib Modelica records ──► omc build
                                                                    │
                                    ┌───────────────────────────────┘
                                    ▼
                     _3_StandardSim  (single studies)
                     _2_EnvelopeSim  (GGV / YMD maps)
                     _4_OptSim       (sweeps, sensitivities, DOE)
                                    │
                                    ▼
                     _0_Utils/plotting + reporting ──► CSV metrics, PDF reports
```

## Layers

### `_0_Utils/` — shared foundation
- **`vehicle_io.py`**: canonical loader/validator for `vehicle.yml`, tire templates, path helpers
- **`plotting/`, `reporting/`**: plot and report engines (use these, not matplotlib)
- **`vehicle_templates/`, `tire_templates/`**: checked-in architecture and tire defaults
- **`deploy/`**: PyInstaller packaging for desktop build
- **`dyn_py/`**: unified reduced-order vehicle model (kinematics + 3/6/10/14DOF + QSS + transient)
- **`kin_py/`**: original kinematics; used for detailed suspension-element workflows
- **`lap_sim/`**: track geometry, GGV/YMD propagation, racing-line optimization, path following
- **`external/BobLib/`**: Modelica physics reference (git submodule). See [boblib-submodule.md](boblib-submodule.md)

### `_1_VisualSim/` — visualization
BobVis: numpy and YAML that turn a run into a 3D scene. `from_results.py` maps BobLib frames to hardpoints and `capture.py` re-runs an evaluation asking OpenModelica for the suspension frames a normal run discards; `sim_data.py` resolves a visual template against those signals. `navigation.py` (camera arithmetic) and `tire_state.py` (LLTD, and friction-circle grip use from the `.tir` MF5.2 terms) hold the maths.

The drawing is in `_5_App`: `visual.py` flattens a scene into a JSON header plus one float32 buffer, and `static/visual.js` renders it in WebGL as the app's Replay tab. It was a separate PyQt6 + PyVista desktop application until it was ported; nothing in the repo depends on Qt or VTK now, and `deploy.py` keeps them excluded so nothing quietly does again. See [`../_1_VisualSim/README.md`](../_1_VisualSim/README.md). (Live model visualization during development still happens in OMEdit.)

### `_2_EnvelopeSim/` — performance envelopes
GGV (grip-acceleration) and YMD (yaw moment diagram) generators. Quasi-steady maps from `vehicle.yml` via `dyn_py`.

### `_3_StandardSim/` — standard vehicle studies
- **Studies:** `RampSteerEval`, `SteadyStateEval`, `TransientEval`, `FourPostEval` (each has `*_config.yml`, `*_sim.py`)
  - `*_config.yml` is the checked-in seed. The app edits a copy under `_5_App/user_data/config/active/`;
    `_0_Utils/config_io.resolve` returns that copy when it exists, so the CLI and the app run the same config.
- **Runners:** `_modelica_runner.py` (compiled Modelica), `_fmu_runner.py` (FMU export)
- **Builders:** `.mos` scripts generate executables into `BuildBobLib/`
- **Special:** `ReducedOrderEval` (correlates `dyn_py` vs. BobLib), `LapTimeEval` (envelope GGV + lap simulation)

Output: `generated_results/` (CSVs, PDFs)

### `_4_OptSim/` — sensitivities and DOE
- **`StandardSens/`**: sweep StandardSim studies over parameter ranges, solve for a
  setup from target metrics (`solve_setup.py`), and compare named vehicles across
  standard sims (`trade_study.py`). `pipeline/standards.py` is the registry of
  VehicleSim standards one compiled vehicle can serve; `pipeline/variants.py` is the
  content-addressed cache of compiled vehicles the solver and trade study share.
- **`EnvelopeSens/`**: sweep envelope outputs (same ranges)
- **`_shared/`**: console progress, tornado-plot rendering

See [doe-reverse-engineering.md](doe-reverse-engineering.md) for all three: the sweep and its reverse lookup, the setup solver, and trade studies.

### `_5_App/` — browser UI and HTTP server
Main user entry point: `python -m _5_App.app` (port 8765). Pick/edit vehicle, generate Modelica, launch jobs, view logs and results.

**Key modules:**
- **`contracts.py` + `registry.py`**: declare available workflows
- **`actions.py`**: dispatch workflow execution
- **`data_services.py`**: data layer

**Adding a workflow:** register it in `registry.py`; do not edit the server.

**State:** mutable app state in `_5_App/user_data/` (dev) or user's BobSim runtime directory (packaged). Gitignored.

See [`_5_App/README.md`](../_5_App/README.md) for module details.

## The vehicle definition

**`vehicle.yml`** (repo root): canonical vehicle definition. Schema: `boblib.vehicle.v1`. Contains masses, CGs, inertias, suspension geometry, power train, tire paths.

**Two consumption paths** (and they can drift):

1. **Python workflows** (`dyn_py`, envelopes, lap sim): read `vehicle.yml` directly
2. **Modelica studies** (VehicleSim, FourPostSim): read generated records `BobLib/Records/VehicleDefn/*.mo`

**Sync:** `_5_App/modelica_generator.py` writes `vehicle.yml` → Modelica records, from the app's
save/generate or from the command line:

```bash
make sync-vehicle         # report which records are stale or missing; exits 1 if any are
make sync-vehicle-write   # regenerate them from vehicle.yml
```

Checking is the default because the two paths are allowed to differ: the Modelica entry points read the
checked-in records, so rewriting them is a deliberate act.

**Debugging:** if study results disagree with `vehicle.yml`, suspect stale BobLib records first.
