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
| Setup | Vehicle parameters, geometry preview, saved vehicles, and Write to MBD |
| Simulation | Workflows, run configs, and job logs |
| Replay | Captured 3D scenes, tire data, and metrics |
| Archive | Saved run packages and downloads |

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
them in Replay.

The app defaults to dark mode. The theme toggle saves `bobsim-theme` in
`localStorage`. Colors are defined in `static/styles.css` and `canvasPalette()`
in `static/app.js`.

## Module layout

- `app.py`: compatibility facade for existing imports plus the CLI entrypoint.
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
- `modelica_generator.py`: vehicle YAML to BobLib Modelica generation.
- `desktop.py`: desktop/webview wrapper for packaged builds.
- `static/`: `index.html`, `app.js`, `styles.css`, and the vendored Inter font.
