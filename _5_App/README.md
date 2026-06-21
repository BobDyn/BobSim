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
Saved user variants live under `_5_App/vehicle_configs`. Vehicle setup exposes
vehicle parameters while hiding repo path plumbing, backed by a large
interactive preview with hardpoints, suspension links, scaled mass spheres, and
representative inertia rods. The header theme toggle persists light/dark mode in
the browser.

`_1_VisualSim` remains the visualization engine. `_5_App` owns the local browser
shell, setup menus, job launch, output preview, and logs.
