# BobSim Docs

Documentation for this checkout. The public documentation is at
[bobdyn.com](https://bobdyn.com).

| Document | Contents |
| --- | --- |
| [architecture.md](architecture.md) | Engines, workflows, and data flow |
| [simulation-entrypoints.md](simulation-entrypoints.md) | Model fidelity and simulation entry points |
| [workflows.md](workflows.md) | App, simulation, optimization, and test commands |
| [doe-reverse-engineering.md](doe-reverse-engineering.md) | Parameter sweeps, target-metric solving, and vehicle comparisons |
| [reduced-order-dynamics.md](reduced-order-dynamics.md) | 3/6/10/14DOF dynamics, QSS envelopes, and BobLib correlation |
| [lap-time-simulation.md](lap-time-simulation.md) | Racing lines, speed profiles, and transient laps |
| [boblib-submodule.md](boblib-submodule.md) | BobLib setup and Modelica build troubleshooting |
| [conventions.md](conventions.md) | Vehicle geometry, axes, signs, hardpoints, and SHARK imports |
| [Visualization](../visualization/README.md) | Scene capture and 3D replay |
| [Skills](../skills/README.md) | SHARK import and regression baseline procedures |

Paths are relative to the repository root unless stated otherwise.
`make help` lists the available commands. The [architecture](architecture.md)
describes the source layout. Builds, results, and app state are generated locally
and excluded from Git.
