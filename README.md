# BobSim

Vehicle setup, simulation studies, and results in one local browser app.
BobSim combines Modelica multibody dynamics from BobLib with Python tools for
suspension geometry, performance envelopes, optimization, and lap simulation.

[Documentation](docs/README.md) · [Simulation guide](docs/simulation-entrypoints.md) ·
[Contributing](CONTRIBUTING.md) · [BobDyn](https://bobdyn.com)

## Start the app

With Git, Docker Compose, and Make installed, run from the repository root:

```sh
make init
make docker-build
make app
```

Open **http://127.0.0.1:8765**. The container provides OpenModelica and the Python
dependencies. Use `make app APP_PORT=8766` to change the port. With a local toolchain,
use `make app RUN= PYTHON=.venv/bin/python`.

Configure a vehicle, run a study, and inspect its plots, reports, logs, and replay.
Builds, results, and app state stay local and are excluded from Git.

## Studies

| Study | Current implementation |
|---|---|
| Ramp, step, sine, settled cornering, and four-post | BobLib Modelica MBD |
| Suspension geometry | KinPy |
| Reduced transient response | DynPy |
| GGV, YMD, and lap workflows | DynPy |
| Setup sweeps and optimization | Orchestrates the underlying studies |

`make help` lists CLI entry points. See the [workflow guide](docs/workflows.md)
for simulation commands, native builds, desktop packaging, and validation.

## Find your way around

| Directory | Purpose |
|---|---|
| [app/](app/README.md) | Browser UI and study orchestration |
| [engines/](engines/) | BobLib submodule, KinPy, and DynPy physics |
| [simulations/](simulations/) | Response, envelope, and lap workflows |
| [optimization/](optimization/) | Sweeps, setup solving, and trade studies |
| [common/](common/) | Configuration, reporting, native artifacts, and deployment |
| [visualization/](visualization/README.md) | Scene capture and replay |
| [tests/](tests/) | Unit, integration, and regression checks |
| [docs/](docs/README.md) | Architecture and developer guides |

`vehicle.yml` is the shared vehicle input. Modelica studies use generated BobLib
records; `make sync-vehicle` checks that they agree with the YAML.

Run `make ci` for lint, type checks, and tests. Full MBD baseline simulations run
separately with `make regression-baseline`; see [validation](docs/workflows.md#testing).
BobSim is under active development, and simulation outputs require validation
against the vehicle and study being modeled.
