# BobSim App

The local browser app: a standard-library web shell over the existing BobSim
workflows. User-facing docs live at [bobdyn.com/bobsim/app](https://bobdyn.com/bobsim/app);
this file is the module map.

```bash
python -m _5_App.app      # then open http://127.0.0.1:8765
```

## What the UI is

Three tabs, used in order:

| Tab | Surface |
| --- | --- |
| `Setup` | Configure, visualise, load, and save the active vehicle, then `Write to MBD` |
| `Simulation` | Launch the StandardSim workflows, edit their run configs, stream job logs |
| `Archive` | Download the archive package a completed run produced |

Setup covers the checked-in architecture templates from
`_0_Utils/vehicle_templates`, so swapping between direct, bellcrank, and
bellcrank-stabar packages happens in the browser before any study runs. It
exposes vehicle parameters while hiding repo path plumbing, backed by a large
interactive preview with hardpoints, suspension links, scaled mass spheres, and
representative inertia rods.

Styling follows the BobDocs/bobdyn.com theme: same Inter face, same palette
tokens, same 8px/12px radius scale. Dark is the default; the header toggle
persists a light override in `localStorage` under `bobsim-theme`. The CSS
tokens in `static/styles.css` and the `canvasPalette()` values in `static/app.js`
are two halves of one palette — change both together or the plots drift from the
shell.

## Where data lives

Mutable app data is under `_5_App/user_data` in development, and under the
user's BobSim runtime directory in packaged builds. `storage.py` is the single
source of truth for the layout:

- `user_data/config/app` — app settings, OpenModelica selection
- `user_data/config/vehicles` — saved vehicles
- `user_data/config/simulations` — saved run configs
- `user_data/results/saved` — archive packages
- `user_data/workspaces/vehicles` — per-vehicle generated configs and results
- `user_data/cache/modelica` — cached Modelica builds

Shipped, read-only assets stay in the repo: `static/` (UI) and
`sim_configs/_defaults/` (stock run configs).

`_1_VisualSim` remains the visualization engine. `_5_App` owns the local browser
shell, setup menus, job launch, output preview, and logs.

## Module layout

- `app.py`: compatibility facade for existing imports plus the CLI entrypoint.
  New code should prefer the domain modules below.
- `contracts.py`: shared dataclasses for workflows, actions, configs, fields,
  and outputs.
- `registry.py`: declarative workflow/action/build-target/config-field
  registry.
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
- `tire_eval.py`: MF52 tire-load and curve payload generation for the UI.
- `kinematics.py`: live suspension kinematic preview payloads.
- `modelica_generator.py`: vehicle YAML to BobLib Modelica generation.
- `desktop.py`: desktop/webview wrapper for packaged builds.
- `static/`: `index.html`, `app.js`, `styles.css`, and the vendored Inter font.
