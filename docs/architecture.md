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
| `simulations/response/` | Dynamic response studies, with MBD and reduced implementations |
| `simulations/envelope/` | DynPy GGV and YMD maps and vehicle reports |
| `simulations/lap/` | Track tools, QSS racing lines and transient laps |
| `optimization/` | MBD and envelope sweeps, setup solving and trade studies |
| `common/` | Vehicle I/O, templates, plotting, reporting and packaging |
| `visualization/` | Capture and replay data |
| `app/` | Browser UI, workflow registry and local server |

Engines and common helpers must not import simulation workflows or the app.
Studies reuse `common/plotting` and `common/reporting`. Optimization calls these
workflows. It is separate from the simulation families and their model choices.
Response studies currently have MBD and reduced implementations. Envelopes and
laps use DynPy. There is no shared backend selection API yet.

`make help` lists the entry points. Existing make target names are retained.
Python imports use the new directories, such as `engines.dynpy` and
`simulations.response.mbd`. Run the browser app with `python -m app.app`.

The app's `contracts.py` and `registry.py` declare workflows. Its cards identify
the engine, selected fidelity and runtime. Saved results retain the model
selection captured when the job started. See [../app/README.md](../app/README.md).

## Vehicle and configuration

`vehicle.yml` is the shared vehicle definition. Python reads it directly.
BobLib studies read generated records under `engines/boblib/BobLib/Records/VehicleDefn`.
Those records can drift from the YAML. `make sync-vehicle` checks them and
`make sync-vehicle-write` regenerates them deliberately.

When the vehicle file sets `brake.front_bias`, the generated VehicleSim
template binds `brakes.frontBrakeBias` to it. This value is the front share of
mechanical brake torque, from 0 to 1. The generator stops when the value is not
a number or is outside 0 to 1. When the key is missing, the template binds
nothing. BobLib `BasicVCUBrakes` then uses its own default, 0.55 at the pinned
BobLib. `make sync-vehicle` prints which case applies.

DynPy and the envelope use the same value when the key is set. The two tiers
describe the same split only when the VCU `regenBrakeBlend` is 0, the default.
The Modelica bias splits the mechanical brake torque only, and regen acts on
the rear axle. When the key is missing, DynPy and the envelope use 0.84, not the
BobLib default. This difference is a known gap.

The vehicle writer keeps vectors and table rows on one line. The schema and
physical values are unchanged by the directory migration.

MBD study configs are checked-in seeds. The app edits copies under
`app/user_data/config/active`. `common/config_io.py` resolves those copies for
both the app and CLI. Envelope and optimization configs resolve relative paths
against their own directories.

Generated builds, results and app state are ignored by Git. Moving from the
numbered layout requires rebuilding executables. Existing local vehicles need
their `paths.boblib` and `paths.tire_templates` updated to the new locations.
The Modelica builds load `engines/boblib/BobLib`. The generator stops before
it writes anything when `paths.boblib` resolves to another directory or that
package has no `package.mo`. An old BobLib tree left on disk by a layout move
also fails. The error names both paths. The generator also refuses to write a
file that resolves outside that package. The app build stops with the same
error.

The response source move retains build and result paths under `simulations/mbd`
and `simulations/reduced` for existing consumers. Optimization assets now live
under `optimization`. Existing make commands and app workflow IDs are unchanged.
Direct Python imports must use the new package paths.
