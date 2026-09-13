# `_1_VisualSim` — BobVis

BobVis replays a simulation's motion as 3D geometry: suspension links
articulating, uprights and tires moving, force vectors growing and shrinking,
with the signal traces scrubbing alongside. It runs as a desktop window, and
renders the same scene straight to video.

```bash
make visual-deps       # once - prebuilt wheels, nothing compiles
make visual-maneuver   # simulate a VehicleSim transient, then watch the car drive
make visual-rig        # simulate the four-post rig, then watch it
make visual-demo       # synthetic scene, no simulation needed
```

Runs on the host, on Windows, macOS and Linux. The simulation behind
`visual-rig` still goes through Docker like every other BobSim workflow; only
the viewer is native.

Not containerised, and that was tried: off-screen rendering worked in a
container, but the window came up with its 3D viewport black, because
`QOpenGLWidget` and Mesa's llvmpipe do not get on — no surface format,
multisample setting or anti-aliasing mode fixed it. Native works for both the
window and rendering everywhere, so there is one path instead of two with one
broken.

---

## Targets

| Target | What it does |
| --- | --- |
| `make visual-deps` | Install the viewer. Needed once, before any of the below. |
| `make visual-maneuver` | Simulate a VehicleSim manoeuvre (`VISUAL_MANEUVER`), convert it, open it. |
| `make visual-rig` | Simulate the four-post rig, convert it, open it. |
| `make visual-demo` | Generate a synthetic scene and open it. |
| `make visual` | Open the viewer on any scene, or a picker with no arguments. |
| `make visual-maneuver-video` | Simulate the manoeuvre and render it to MP4 instead. |
| `make visual-rig-video` | Simulate the rig and render it to MP4 instead. |
| `make visual-demo-video` | Synthetic scene to MP4. |
| `make visual-export` | Render any scene to video. Requires `VISUAL_CONFIG` and `VISUAL_DATA`. |
| `make visual-capture` | Simulate `VISUAL_EVAL` and write the scene, without rendering. |

| Variable | Default | Meaning |
| --- | --- | --- |
| `VISUAL_MANEUVER` | `transient` | `transient`, `ramp_steer` or `steady_state`, for `visual-maneuver`. |
| `VISUAL_EVAL` | `four_post` | Any of the above or `four_post`, for `visual-capture`. |
| `VISUAL_CONFIG` | *(empty)* | Visual template `.yml`. Empty opens the picker. |
| `VISUAL_DATA` | *(empty)* | Signal file, `.npz` or `.csv`. |
| `VISUAL_OUTPUT` | `_1_VisualSim/results/bobvis.mp4` | `visual-export` target file. |
| `VISUAL_ARGS` | *(empty)* | Extra CLI flags, e.g. `--resolution 720p --fps 30`. |

`make visual-capture` writes `results/<eval>_visual.npz` and
`results/<eval>_visual.yml`; the rig and manoeuvre targets open that pair.
A manoeuvre runs several cases and the newest result is converted. Another case
from the same capture converts with `python -m _1_VisualSim.from_results <result.csv>`.

```bash
make visual \
  VISUAL_CONFIG=_1_VisualSim/results/four_post_visual.yml \
  VISUAL_DATA=_1_VisualSim/results/four_post_visual.npz

make visual-export \
  VISUAL_CONFIG=_1_VisualSim/results/four_post_visual.yml \
  VISUAL_DATA=_1_VisualSim/results/four_post_visual.npz \
  VISUAL_OUTPUT=knc.mp4 VISUAL_ARGS="--resolution 720p --speed 8"
```

Dependencies are six prebuilt wheels — PyVista, VTK, PyQt6, pyvistaqt, imageio
and imageio-ffmpeg (which bundles ffmpeg, so nothing needs to be on `PATH`).
No compiler, no system packages on Windows or macOS. A bare Linux host may
need `libgl1 libglx-mesa0 libxkbcommon-x11-0`. `make visual` checks the imports
and tells you to run `make visual-deps` rather than failing on a traceback.

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

## Using the window

**Camera.** Two modes, in the toolbar:

* **Follow car** — the camera rides in the vehicle frame. Orbit with the mouse
  and it keeps the view you chose relative to the car, rather than snapping
  back on the next frame. Point it at a single joint with the focus dropdown
  to watch one corner work.
* **Free** — a world-fixed camera that playback never touches. Use it to watch
  the car drive past a fixed point.

**Mouse and touchpad.** `F1` lists these in the window.

| Input | Mouse | Touchpad |
| --- | --- | --- |
| Orbit | Left-drag | Two-finger drag, or click-drag |
| Pan | Right-drag, middle-drag, Shift+left-drag | Shift + two-finger drag |
| Zoom | Scroll | Pinch |
| Orbit around a point | Double-click it | Double-click it |

Orbit is turntable style about the vertical, so the horizon never rolls and
the view stops short of straight up or down. Zoom heads for whatever is under
the cursor, in proportion to how far you scrolled, rather than in fixed jumps.
All of it works while playing, in either camera mode.

A touchpad scroll and a mouse wheel arrive as the same event. Windows says
nothing about which it was, so a scroll in fractions of a notch is taken to be
a touchpad. A free-spinning mouse reports fractions too; if yours orbits when
it should zoom, untick **View ▸ Two-finger scroll orbits** (remembered between
sessions). The input arithmetic is in `navigation.py`.

View presets (Iso / Top / Front / Rear / Left / Right) reframe the geometry at
the current time and ignore the ground plane, so the car always fills the
viewport. `R` resets. `+`/`-` zoom. The **View** menu has ±15° elevation,
azimuth and roll nudges for when a preset is nearly right.

The toolbar is two menus and the camera. **View** looks along an axis and
reframes the car. **Layers** shows or hides ground, tires, vectors, joints,
tracks, and loads with LLTD, listing only what the scene has. Hiding tires is
the usual way to see inboard suspension motion.

**The ground** is there to be read, and a legend in the corner says how:

* **Grid** — thin lines every metre, bold every 5 m, for distance and speed.
* **Loads** — a disc under each tire, its area proportional to vertical load.
  The ring is the tire's median load over the run (static on the rig, settled
  when driving): a red disc spilling past it carries more, a blue one inside
  it is unloading. Load transfer, at a glance.
* **LLTD** — under each axle, its share of the car's lateral load transfer and
  the size of that transfer in newtons, from the same loads. It reads "—" until
  the car is moving at least 1% of its weight sideways. Every run with per-tire
  loads gets it: the rig and all three VehicleSim manoeuvres.
* **Tracks** — driving runs only: each contact patch's last 3 s, fronts blue,
  rears red. Rears running outside the fronts in a corner is understeer.

**Playback** is wall-clock driven, so 1× is real time regardless of how the
solver spaced its output, and the geometry is interpolated between samples
rather than stepped. `Space` toggles play, `←`/`→` step one sample, `Home` and
`End` jump. Speeds run 0.1× to 4×.

**Signals** on the right start from the template's `plots` block; add or remove
rows and repoint the X/Y dropdowns at any signal in the file. The red cursor
tracks playback, and setting X to something other than `time` turns the plot
into a cross-plot with the cursor riding the curve.

**Tires** appears when the run kept tire forces, which the VehicleSim
manoeuvres do. Each corner's circle plots that tire's force as a share of its
peak grip at its current load and camber, using the MF5.2 terms in the `.tir`
file `vehicle.yml` names. The outer circle is the limit: up is drive, down is
braking, sideways is cornering. The dot turns amber past 80% and red past 95%,
and its tail is the last second.

**Metrics** lists the evaluation's own metrics CSV for the run, grouped the
way the evaluation wrote them. Filter by name, and hover a row for its
definition. The long `trend` group starts collapsed.

Tabs only appear when they have something in them, so the rig shows Signals
alone.

---

## Exporting video

**Export video** in the toolbar, or `Ctrl+E`. The dialog covers output path,
resolution (720p through 1440p, or custom), frame rate, playback speed, a time
range, whether to include the signal strip, and whether to reuse the camera
currently on screen — leave that ticked and the file matches the window.

`.mp4`, `.mov`, `.webm` and `.gif` all work. ffmpeg comes from the
`imageio-ffmpeg` wheel, so nothing needs to be on `PATH`.

Headless, for scripts and CI:

```bash
python -m _1_VisualSim.run_visual CONFIG.yml DATA.npz -o out.mp4 \
    --resolution 1080p --fps 60 --speed 0.5 --start 1.0 --end 4.0
```

`--help` lists the rest (`--no-plots`, `--no-ground`, `--quality`). Rendering is
the slow part: budget roughly a second per frame at 1080p, so trim with
`--start`/`--end` before committing to a long export.

---

## Module map

| File | Role |
| --- | --- |
| `scene.py` | `SimData` (config + signals) and `VisualScene` (actors, interpolation, camera). Qt-free. |
| `navigation.py` | Camera arithmetic for mouse and touchpad input: orbit, pan, zoom-to-cursor, wheel classification. Numpy only. |
| `tire_state.py` | Friction-circle and LLTD arithmetic: MF5.2 peak μ from `.tir` terms, grip use, axle load transfer. Numpy only. |
| `viewer.py` | The desktop app: toolbar, viewport, mouse and touchpad navigation, signal panel, transport, export dialog. |
| `exporter.py` | Off-screen rendering and video muxing, plus the signal strip. |
| `run_visual.py` | Headless CLI over `exporter.py`. |
| `from_results.py` | Maps BobLib frames to hardpoints; turns a result CSV into a scene. |
| `capture.py` | Writes the geometry-capture eval config, then converts what it produced. |
| `theme.py` | The Qt stylesheet and matplotlib rcParams. |
| `demo.py` | Generates the synthetic scene behind `make visual-demo`. |
| `visual_templates/` | Older templates, currently stale. See above. |
| `requirements.txt` | The dependency list behind `make visual-deps`. |
| `results/` | Generated output. Gitignored. |

The viewer and the exporter share `scene.py`, so a headless render and the
on-screen view cannot drift apart — a fix to geometry, camera or styling lands
in both at once.

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

## Notes

- **Theme.** One light theme, matching BobDocs' font stack and brand blue. No
  dark mode: link colours come from each template's own `style` block, and a
  second background only gives them a second set of contrast ratios to fail at.
- **`results/`** is gitignored. `make clean-visual` empties it.
- **Headless Linux** works without an X server: `scene.ensure_offscreen_display`
  starts an Xvfb display when `DISPLAY` is empty and Xvfb is present. VTK
  renders without one but logs a "bad X server connection" warning first.
- **Not in the deploy bundle.** `_5_App`'s executable excludes these modules —
  see `EXCLUDED_MODULES` in `_0_Utils/deploy/deploy.py`. BobVis is a separate
  desktop app with a separate dependency set, and bundling Qt and VTK into the
  browser app would cost ~120 MB for nothing.
- **A capture run is slower and larger than a metrics run.** The finer output
  step and the extra columns put the result CSV in the tens of MB. It writes
  into the same gitignored `BuildBobLib/.../results/` as any other run.
- **`demo.py` is not physics.** It is a closed-form kinematic mock-up that
  exists so the viewer, the exporter and this README have something to run
  against. Never cite a number from it.
