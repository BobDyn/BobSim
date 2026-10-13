# BobVis

BobVis captures simulation geometry for the app's Simulation → Captured scenes view. It shows
suspension links, tires, force vectors, and tire loads.

```bash
make visual-maneuver   # capture a VehicleSim transient
make visual-rig        # capture a four-post run
make visual-demo       # generate a synthetic scene
make app               # open Simulation → Captured scenes
```

These targets run in Docker by default.

## Targets

| Target | Input |
| --- | --- |
| `visual-maneuver` | VehicleSim maneuver selected by `VISUAL_MANEUVER` |
| `visual-rig` | Four-post evaluation |
| `visual-capture` | Evaluation selected by `VISUAL_EVAL` |
| `visual-demo` | Synthetic data, no simulation required |

Each writes `<name>_visual.yml` and `<name>_visual.npz` to
`visualization/results/`. Captured scenes lists these scenes and saved DynPy
ramp- and step-steer runs. Reduced replay uses the run's archived signals and
vehicle definition. The display settings button selects geometry and tire overlays.
The Tires panel shows each corner on its peak-grip ellipse and percent utilization.

The camera uses the geometry editor's orbit, pan and zoom gestures. Home restores
the isometric view. Top, front and side views are available. World frame follows position with a fixed heading. Vehicle frame also follows
heading, keeping front and side views aligned during a turn. Roll stays visible.

Reduced replay shows two axles and a center spine at 3 DOF, body motion at 6 DOF,
and unsprung motion at 14 DOF. Wheel spin uses saved angles at 10/14 DOF and
distance traveled at 3/6 DOF. The latter is a rolling animation, without wheel slip.
Contact trails show all four wheels. Force arrows use saved Fx and Fy. Load
footprints use Fz, which is available in new runs. Wishbones and steering use archived hardpoints and KinPy reconstruction from
corner travel and rack input. Chassis lines connect the inboard mounts. Actuation
linkages are omitted in reduced replay. MBD replay uses captured linkage positions.

## Scene Capture

A scene has two inputs:

- A YAML template defining points, links, tires, force vectors, and camera settings.
- A signal file containing positions over time, in `.npz` or `.csv` format with a
  `time` column.

Normal evaluation output contains the signals needed for metrics, which may
exclude geometry. `make visual-capture` reruns the evaluation with those signals
plus the hardpoint frame origins in `from_results.FRAME_MAP`, then converts the
result to a scene pair.

The converter detects whether axle frames belong to the four-post rig or are
nested under VehicleSim's `chassis.detailedChassis`.
It reconstructs wheel-center and contact-patch positions removed by OpenModelica
from three surviving upright points. The run reports reconstructed points.

Capture also includes tire `Fx`, `Fy`, `Fz`, and camber, and records the metrics
CSV in the template. Recapture older scenes to add these channels.

The older files in `visual_templates/` name signals absent from the current
BobLib models. Use `make visual-maneuver` to generate a current template and data
pair. Missing signal names are reported when a template is loaded.

## Modules

| File | Role |
| --- | --- |
| `sim_data.py` | Resolve a visual config against its signals |
| `navigation.py` | Camera orbit, pan, zoom, and double-click calculations |
| `tire_state.py` | MF5.2 pure-slip peak friction, grip utilization, and axle load transfer |
| `from_results.py` | Convert BobLib result frames to a scene |
| `capture.py` | Run an evaluation with geometry capture and convert its output |
| `demo.py` | Generate the synthetic scene |
| `dynpy.py` | Build reduced replay geometry from archived response signals |
| `visual_templates/` | Older templates |
| `results/` | Generated scenes, excluded from Git |
| `../app/visual.py` | Resolve scenes into a JSON header and float32 buffer |
| `../app/static/visual.js` | Browser camera and WebGL renderer |
| `../app/static/visual_panel.js` | Run picker, timeline, layers, tire data, and metrics |

The server resolves signal names to buffer indices. The browser interpolates
samples and draws links, tires, joints, trails, and vectors.
`tests/test_visual_camera_parity.py` compares the browser camera calculations
with `navigation.py`. It requires Node.js and skips when Node.js is unavailable.

## Template Format

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

Point coordinates are in the world frame, in metres, matching BobSim's axis
conventions ([`docs/conventions.md`](../docs/conventions.md)). Spin markers use
saved wheel-angle signals when available. Reduced 3/6 DOF replay derives them
from distance traveled.

`input_stride` is applied once, to every signal including `time`, so geometry,
plots and the timeline stay on one index.

## Limits

The friction display uses an ellipse based on pure-slip peak friction. It does
not represent the full MF5.2 combined-slip envelope.

Video export depends on browser recording support. Generated scenes are excluded
from Git.
