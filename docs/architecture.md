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
Rendering engine (`viewer.py`, `run_visual.py`) + visual templates. Offline/replay visuals, consumed by `_5_App`. (Live model visualization during development still happens in OMEdit.)

### `_2_EnvelopeSim/` — performance envelopes
GGV (grip-acceleration) and YMD (yaw moment diagram) generators. Quasi-steady maps from `vehicle.yml` via `dyn_py`.

### `_3_StandardSim/` — standard vehicle studies
- **Studies:** `RampSteerEval`, `SteadyStateEval`, `TransientEval`, `FourPostEval` (each has `*_config.yml`, `*_sim.py`)
- **Runners:** `_modelica_runner.py` (compiled Modelica), `_fmu_runner.py` (FMU export)
- **Builders:** `.mos` scripts generate executables into `BuildBobLib/`
- **Special:** `ReducedOrderEval` (correlates `dyn_py` vs. BobLib), `LapTimeEval` (envelope GGV + lap simulation)

Output: `generated_results/` (CSVs, PDFs)

### `_4_OptSim/` — sensitivities and DOE
- **`StandardSens/`**: sweep StandardSim studies over parameter ranges
- **`EnvelopeSens/`**: sweep envelope outputs (same ranges)
- **`_shared/`**: console progress, tornado-plot rendering

See [doe-reverse-engineering.md](doe-reverse-engineering.md) for reverse-lookup (target metrics → car parameters).

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

**Sync:** `_5_App/modelica_generator.py` writes `vehicle.yml` → Modelica records. After editing `vehicle.yml`, run `_5_App.app` save/generate or `make sync-vehicle` to refresh records.

**Debugging:** if study results disagree with `vehicle.yml`, suspect stale BobLib records first.
