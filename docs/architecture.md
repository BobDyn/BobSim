# Architecture

BobSim runs vehicle studies using three sibling physics tools.

| Engine | Model | Runtime |
| --- | --- | --- |
| `engines/kinpy` | Suspension geometry | Python |
| `engines/dynpy` | 3, 6, 10 or 14 generalized DOF | Python |
| `engines/boblib` | Modelica multibody dynamics (MBD) | OpenModelica compiled executable |

DynPy supports both quasi-steady trim and transient integration. QSS describes
an analysis method, not a DOF count. BobLib is a separate git submodule.

## Layout

| Directory | Contents |
| --- | --- |
| `engines/` | Physics tools |
| `simulations/mbd/` | BobLib builders, runners and standard maneuver studies |
| `simulations/reduced/` | DynPy transient studies and correlation against BobLib |
| `simulations/envelope/` | DynPy GGV and YMD maps and vehicle reports |
| `simulations/lap/` | Track tools, QSS racing lines and transient laps |
| `simulations/optimization/` | MBD and envelope sweeps, setup solving and trade studies |
| `common/` | Vehicle I/O, templates, plotting, reporting and packaging |
| `visualization/` | Capture and replay data |
| `app/` | Browser UI, workflow registry and local server |

Engines and common helpers must not import simulation workflows or the app.
Studies reuse `common/plotting` and `common/reporting`.

`make help` lists the entry points. Existing make target names are retained.
Python imports use the new directories, such as `engines.dynpy` and
`simulations.mbd`. Run the browser app with `python -m app.app`.

The app's `contracts.py` and `registry.py` declare workflows. Its cards identify
the engine, selected fidelity and runtime. Saved results retain the model
selection captured when the job started. See [../app/README.md](../app/README.md).

## Vehicle and configuration

`vehicle.yml` is the shared vehicle definition. Python reads it directly.
BobLib studies read generated records under `engines/boblib/BobLib/Records/VehicleDefn`.
Those records can drift from the YAML. `make sync-vehicle` checks them and
`make sync-vehicle-write` regenerates them deliberately.

The vehicle writer keeps vectors and table rows on one line. The schema and
physical values are unchanged by the directory migration.

MBD study configs are checked-in seeds. The app edits copies under
`app/user_data/config/active`. `common/config_io.py` resolves those copies for
both the app and CLI. Envelope and optimization configs resolve relative paths
against their own directories.

Generated builds, results and app state are ignored by Git. Moving from the
numbered layout requires rebuilding executables. Existing local vehicles need
their `paths.boblib` and `paths.tire_templates` updated to the new locations.
