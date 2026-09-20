# BobSim App

Run:

```bash
python -m _5_App.app
```

Open `http://127.0.0.1:8765`.

The app is a small standard-library web shell over the existing BobSim
workflows. The left rail is intentionally small: `Setup` and `Standard Sim`.
Setup is where the active vehicle is configured, visualized, loaded from a
template or saved variant, and saved back into the local vehicle library. Once a
vehicle is selected, Standard Sim becomes the focused run/review surface for the
standard workflows.

The active vehicle setup includes the checked-in architecture templates from
`_0_Utils/vehicle_templates`, so changing between direct, bellcrank, and
bellcrank-stabar packages can be done from the browser before running studies.
Mutable app data lives under `_5_App/user_data` in development and under the
user's BobSim runtime directory in packaged builds. Vehicle setup exposes
vehicle parameters while hiding repo path plumbing, backed by a large
interactive preview with hardpoints, suspension links, scaled mass spheres, and
representative inertia rods. The header theme toggle persists light/dark mode in
the browser.

Mutable app folders are grouped as:

- `_5_App/user_data/config/app`
- `_5_App/user_data/config/vehicles`
- `_5_App/user_data/config/simulations`
- `_5_App/user_data/results/saved`
- `_5_App/user_data/workspaces/vehicles`
- `_5_App/user_data/cache/modelica`

`_1_VisualSim` turns runs into scenes; `_5_App/visual.py` and
`static/visual.js` draw them in the Replay tab. `_5_App` owns the local browser
shell, setup menus, job launch, output preview, and logs.

## Module Layout

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
