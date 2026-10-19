# Simulation entry points

Each result identifies its analysis method, vehicle model and runtime.
QSS is a method, not a model fidelity.

## Models

| Engine | Representation | Runtime |
| --- | --- | --- |
| KinPy | Suspension geometry and corner lookups | Python |
| DynPy 3 DOF | Planar body motion, four tire contacts and algebraic load transfer | Python |
| DynPy 6 DOF | Adds body heave, roll and pitch | Python |
| DynPy 10 DOF | Adds four wheel rotations | Python |
| DynPy 14 DOF | Adds four unsprung vertical motions | Python |
| BobLib MBD | Multibody vehicle with joints and constraints | OpenModelica compiled executable |

DynPy uses KinPy corner geometry and independent front and rear MF5.2 tire
models. App workflows generate corner lookups automatically. Runtime depends
on the vehicle, sampling and convergence. BobLib compilation is a separate cost.

## App simulations

| Simulation | Calculation | Inputs and results |
| --- | --- | --- |
| Four post | BobLib prescribes chassis roll about global x and heave along rotated local z. Contact-patch global heights remain fixed while other contact motions are free. | Vehicle suspension, heave, roll, handwheel input and test forces. Reports geometry, motion ratios, loads and stiffness metrics. |
| Maneuver | DynPy or BobLib integrates a ramp-and-hold, finite-rise step or sine input with speed control. | Speed, waveform magnitude and timing. DynPy steering is nominal mean front roadwheel angle. BobLib steering is handwheel angle. Results include histories and a response report. |
| Steady state | BobLib advances through time until speed, lateral acceleration and monitored handling signals settle. | Speed and lateral-acceleration targets. Reports settled steering, roll, sideslip and handling gradients. |
| GGV | DynPy solves constrained algebraic operating points and searches acceleration boundaries across speed. | Vehicle definition and selected DOF. Speed coverage and acceleration searches are automatic. Results include path-tangential and path-normal acceleration envelopes. |
| YMD | DynPy sweeps sideslip and nominal roadwheel steer at prescribed speed and yaw rate. Longitudinal, vertical and retained wheel states are equilibrated. | Steering and sideslip grids. Lateral acceleration and yaw moment remain outputs. Most points are not steady cornering equilibria. |
| Racing line | Periodic boundary splines interpolate the cones. A bounded sparse optimization minimizes integrated squared path curvature. | Paired-boundary CSV and edge clearance. Vehicle width and wheelbase come from Setup. Results include the saved path, curvature and report. |
| QSS lap | Forward acceleration and backward braking passes solve a closed-lap speed profile on the saved path. | Linked GGV and racing-line results. Fidelity and power limits come from the GGV. Results include lap time, speed and acceleration along the path. |
| Transient lap | A feedback driver follows a generated QSS reference while DynPy integrates the vehicle states. | Model DOF, track, line mode, event power cap and driver settings. Reports tracking, lap completion and time histories. |

Four post uses zero world gravity and spring preload with scheduled test forces.
It is a constrained rig, not a free-running vehicle. Its handwheel input acts
on the rack pinion through the vehicle C-factor.

GGV points constrain angular acceleration without setting yaw rate to zero.
Both turn directions are solved independently when enabled. QSS Lap does not
integrate suspension transients or optimize the linked path. Racing-line
clearance is enforced at gates, not over the complete swept vehicle between gates.

Maneuver uses RK45 for DynPy 3/6 DOF and Radau for 10/14 DOF. Transient Lap uses
RK45 for 3 DOF and Radau for 6/10/14 DOF. Output sampling is separate from the
integrators' adaptive steps. A single sine maneuver represents one frequency
and amplitude, not a frequency sweep.

## CLI workflows

`make help` lists the available targets. Source entry points live under
`simulations/response`, `simulations/envelope` and `simulations/lap`.

| Targets | Workflow |
| --- | --- |
| `standard-eval-four-post` | BobLib four-post rig |
| `standard-eval-ramp-steer` | BobLib continuous handwheel ramps across speeds |
| `standard-eval-steady-state` | BobLib settled cornering cases |
| `standard-eval-transient` | BobLib step and sine case suite |
| `standard-eval-all` | All four standard studies |
| `reduced-eval` | DynPy step response |
| `envelope-ggv`, `envelope-ymd`, `envelope-all` | DynPy envelope workflows |
| `lap-eval-qss`, `lap-eval-transient`, `lap-eval` | Standalone lap runner with optional envelope and line generation |
| `lap-eval-all-dof` | Standalone laps across 3/6/10/14 DOF |

The standalone lap runner can generate its own inputs. App QSS Lap instead
requires explicit links to completed GGV and racing-line results.

Legacy output directories remain `simulations/mbd/generated_results` for
standard reports and `simulations/reduced` for reduced response artifacts.
Envelope maps and reports use `simulations/envelope/Build` and
`simulations/envelope/results`. Standalone laps use `simulations/lap/results`.
The app archives run inputs and results under its vehicle workspace.

## Optimization and validation

StandardSens sweeps BobLib standard studies. EnvelopeSens uses a separate
legacy capacity model, not the DynPy DOF selected for GGV or YMD.
[DOE workflows](doe-reverse-engineering.md) describes parameter sweeps, target
solving and vehicle comparisons.

Passing solver checks establishes internal consistency. Agreement with BobLib
or measured vehicle data requires separate correlation. Local envelope and
racing-line optimization do not establish a global optimum or dynamic stability.
