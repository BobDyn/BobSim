# `_1_VisualSim` — BobVis

BobVis replays a simulation's motion as 3D geometry: suspension links
articulating, uprights and tires moving, force vectors growing and shrinking,
tire loads pressing into the ground.

It used to be a second desktop application, PyQt6 driving VTK through PyVista.
It is now the **Replay tab of the app** — `_5_App/visual.py` turns a captured
run into a payload and `_5_App/static/visual.js` draws it in WebGL. What is
left in this package is the part that was never about rendering: turning a
simulation result into a scene.

```bash
make visual-maneuver   # simulate a VehicleSim transient and write its scene
make visual-rig        # simulate the four-post rig and write its scene
make visual-demo       # synthetic scene, no simulation needed
make app               # open the app, then the Replay tab
```

There is nothing to install for it. The simulation behind `visual-rig` still
goes through Docker like every other BobSim workflow; the conversion steps are
host side and need only the base requirements.

---

## Targets

| Target | What it does |
| --- | --- |
| `visual-maneuver` | Re-runs a VehicleSim manoeuvre (`VISUAL_MANEUVER`) with geometry capture, then writes its scene. |
| `visual-rig` | The same for the four-post rig. |
| `visual-capture` | The general form: whichever evaluation `VISUAL_EVAL` names. |
| `visual-demo` | A synthetic scene, no simulation and no OpenModelica needed. |

Each writes a `<name>_visual.yml` and `<name>_visual.npz` pair into
`_1_VisualSim/results/`. The Replay tab lists whatever it finds there.

---

## Where the data comes from

Two inputs, always:

* a **visual template** — YAML describing which signals are 3D points, how
  they connect into links, where the tires and force vectors are, and how the
  camera follows the car;
* a **signal file** — hardpoint positions over time, `.npz` or any `.csv` with
  a `time` column.

`make visual-capture` produces both, together, from a real simulation.

### Why there is a capture step

The evaluations do not emit geometry. Each one sets a `variable_filter` naming
the handful of scalars its metrics need — `frKnC.leftGamma`, spring lengths,
`accY` — and OpenModelica writes only those. A default
`make standard-eval-four-post` result CSV is 45 columns of KnC numbers with no
positions in it at all, so there is nothing for a viewer to draw.

`make visual-capture` re-runs an evaluation with a wider filter that also asks
for the MultiBody frame origins behind each hardpoint (`from_results.FRAME_MAP`),
at a finer output step, then converts the result:

```
capture config  ->  the evaluation in the container  ->  from_results  ->  .npz + .yml
```

The rig and VehicleSim share one frame map: VehicleSim's axles are the rig's,
nested under `chassis.detailedChassis.`, and the converter detects the prefix.

It asks for ~250 columns rather than the model's 39,000, and writes the data
and the template as a pair so they cannot disagree.

The same filter keeps each tire's `Fx`, `Fy`, `Fz` and camber for the friction
circles, and the conversion records the run's metrics CSV in the template for
the Metrics tab. A scene captured before either existed has neither; re-run
`make visual-capture` to get them.

Two details worth knowing:

* **The evaluation's own signals stay in the filter.** It re-reads the same CSV
  to compute its metrics and fails if they are missing, so the capture filter
  is a union, never a replacement.
* **Some points come back by refit.** OpenModelica eliminates variables it can
  prove redundant, and the wheel-centre frames and contact-patch Z go with
  them. Rather than recompiling the model with that optimisation off, the
  converter fits the upright's pose from three outboard points that did
  survive and maps the rest through it. That is exact for a rigid upright, and
  it is where the tire spin axes come from too. The run reports which points
  were refit.

### The bundled templates

`visual_templates/` holds four older templates naming signals like
`signals/visfrontaxleleftlowerfore_i1`. **No current model emits those.** There
is no `vis` bus anywhere in the pinned BobLib, and nothing in this repo ever
wrote the `*_visual.npz` files their headers refer to. They are kept because
they document the intended layout for the VehicleSim maneuvers, but they
cannot be opened against a run produced today. Use `make visual-maneuver`.

If a template names a signal the data file has not got, BobVis lists the
missing names instead of failing somewhere inside VTK.

---

---

## Module map

| File | Role |
| --- | --- |
| `sim_data.py` | `SimData`: a visual config resolved against the signals it names. Numpy and YAML only. |
| `navigation.py` | Camera arithmetic: orbit, pan, zoom-to-cursor, and where a double-click lands. Numpy only, and the reference the browser camera is tested against. |
| `tire_state.py` | Friction-circle and LLTD arithmetic: MF5.2 peak μ from `.tir` terms, grip use, axle load transfer. Numpy only. |
| `from_results.py` | Maps BobLib frames to hardpoints; turns a result CSV into a scene. |
| `capture.py` | Writes the geometry-capture eval config, then converts what it produced. |
| `demo.py` | Generates the synthetic scene behind `make visual-demo`. |
| `visual_templates/` | Older templates, currently stale. See above. |
| `results/` | Generated output. Gitignored. |

The drawing lives in `_5_App`:

| File | Role |
| --- | --- |
| `_5_App/visual.py` | Resolves a config and its signals into a JSON header plus one float32 buffer. |
| `_5_App/static/visual.js` | The camera and the WebGL renderer. |
| `_5_App/static/visual_panel.js` | The Replay screen: run picker, timeline, layers, tire and metric tabs. |

Everything that depends on the run is resolved once, server side, into flat
indices. Per frame the browser looks up no names and makes no decisions — it
interpolates numbers and draws. Two instanced programs cover the whole scene:
segments (links, grid, trails, force arrows) and discs (tires, load
footprints, and billboarded joints).

`navigation.py` stays even though the camera now runs in the browser.
`tests/test_visual_camera_parity.py` runs the JavaScript under `node` and
holds it to this module's answers, so the arithmetic that made the first pass
at these controls feel wrong cannot drift again unnoticed. It skips where
`node` is absent, as in CI.

---

## Writing a visual template

```yaml
style:
  joints: {radius: 0.014, color: "#e0483c"}
  links:
    default: {radius: 0.010, color: "#33383f"}
    groups:
      upper: {radius: 0.011, color: "#33383f"}
      shock: {radius: 0.014, color: "#d64550"}

geometry:
  points:                       # name -> the three signals holding x, y, z
    flUpper_o: [sig/x, sig/y, sig/z]
  links:                        # group -> pairs of point names
    upper: [[flUpperFore_i, flUpper_o]]
  tires:
    fl:
      center: flWheelCenter
      x: [...]                  # longitudinal unit vector, 3 signals
      y: [...]                  # lateral unit vector, 3 signals
      radius: 0.2032
      width: 0.1778
  vectors:
    tire_force:
      fl:
        origin: flContactPatch
        direction: [fx, fy, fz] # signal names, or constants
        scale: 0.0001           # metres drawn per unit
        color: "#f0932b"

ground:                         # optional layers drawn on the road
  loads:
    radius: 0.22                # disc radius at the reference load, metres
    corners:
      fl: {point: flContactPatch, signal: Fz_FL}   # ring = median load
  tracks:
    points: [flContactPatch, rlContactPatch]
    history: 3.0                # seconds of trail
    colors: ["#2b7fd4", "#d64550"]

render:
  speed: 1.0                    # default export speed
  input_stride: 1               # keep every nth sample

plots:                          # seeds the signal panel and the export strip
  - {name: "Lateral accel (m/s²)", x: time, y: sig/accy}

camera:
  attach_to: rlWheelCenter      # point the camera follows
  forward_pair: [rl, fl]        # two points defining vehicle forward
  origin_offset: {x: 0.6, y: 0.6, z: 0.0}
  camera_offsets: {back: 3.0, height: 2.0}
```

Point coordinates are **world frame**, in metres, matching BobSim's axis
conventions ([`docs/conventions.md`](../docs/conventions.md)). Wheel spin is
integrated from wheel-center velocity, so tires roll correctly without a
spin-angle signal.

`input_stride` is applied once, to every signal including `time`, so geometry,
plots and the timeline stay on one index.

---

---

## Notes

- **The friction circle is an approximation.** It is an ellipse built from
  pure-slip peak μ, not MF5.2's combined-slip envelope. Read its edge as "at
  the limit", not as a hard wall.
- **Scenes are generated, never committed.** `_1_VisualSim/results/` is
  gitignored; `make visual-demo` rebuilds the synthetic pair whenever it is
  missing.
- **Video export is gone.** It went with the off-screen VTK renderer. Nothing
  in the repo consumed the MP4s, and a screen recording of the tab costs less
  than the dependency did.
