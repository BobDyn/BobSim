# BobSim

BobSim is the Python orchestration layer for BobDyn. It builds BobLib-based
vehicle simulations, runs standard studies, extracts signals, computes metrics,
generates reports, and supports design-of-experiments sweeps.

BobLib lives in this repository as a git submodule under
`_0_Utils/external/BobLib/`.

## Repository Layout

- `_0_Utils/` - shared plotting, reporting, and utility code
- `_1_VisualSim/` - visualization templates and MP4 rendering
- `_2_EnvelopeSim/` - first-principles envelope tools such as GGV and YMD
- `_3_StandardSim/` - standard maneuver runners and report generation
- `_4_OptSim/` - architecture-driven DOE / exploration pipeline

## What BobSim Does

BobSim follows a simple pipeline:

1. Select a vehicle or test configuration from human-readable YAML / Modelica
2. Generate case inputs or DOE variants
3. Compile Modelica into a runnable executable
4. Run the simulation or study
5. Extract signals from CSV output
6. Compute summary metrics
7. Write plots, CSV files, PDFs, and DOE tables

The active standard-simulation build path compiles the shared Modelica model
`BobLib.Standards.VehicleSim` into `_3_StandardSim/Build/`.

## Active Workflows

Current public workflows:

- `SteadyStateEval` - steady-state cornering characterization
- `TransientEval` - steering transient / frequency-response characterization
- `sim-doe` - OptSim DOE sweep and aggregation workflow

## Quick Start

From the repository root:

```bash
make init
make setup
omc _3_StandardSim/build.mos
make SteadyStateEval
make TransientEval
make sim-doe
```

Helpful shell targets:

```bash
make shell-bobsim
make shell-doe
```

Helpful cleanup targets:

```bash
make clean-doe
make clean
```

## Standard Simulation

The standard workflows live in `_3_StandardSim/` and use the shared Modelica
runner plus report engine.

Useful entry points:

- `_3_StandardSim/SteadyStateEval/steady_state_eval_config.yml`
- `_3_StandardSim/TransientEval/transient_eval_config.yml`
- `make SteadyStateEval`
- `make TransientEval`

Outputs land in `_3_StandardSim/results/` as PDF reports and metrics CSVs.

## DOE / OptSim

OptSim is BobSim's DOE-style exploration pipeline for vehicle-architecture
sweeps.

What it does:

- Selects a vehicle architecture from
  `_4_OptSim/configs/vehicle_architecture.yaml`
- Generates a private derived DOE config at `_4_OptSim/configs/_doe_config.yaml`
- Samples the design space with Latin hypercube sampling
- Writes one `variant.mo` per DOE point into `_4_OptSim/population/`
- Compiles each variant with OpenModelica
- Runs the SteadyStateEval report wrapper for each variant
- Writes per-variant report artifacts
- Aggregates the report metrics into `_4_OptSim/results/doe_results.csv`

Main entry point:

```bash
make sim-doe
```

Useful configuration files:

- `_4_OptSim/configs/vehicle_architecture.yaml`
- `_4_OptSim/configs/compiler_config.yaml`
- `_4_OptSim/configs/aggregator_config.yaml`
- `_4_OptSim/configs/build_template.mos`

`_4_OptSim/configs/_doe_config.yaml` is generated automatically from the
architecture file and should not be edited by hand.

Important unit convention:

- `_4_OptSim` sweeps `staticAlpha` and `staticGamma` in degrees
- the Modelica wheel physics consumes those values directly in the wheel
  rotation setup

Outputs land in:

- `_4_OptSim/results/doe_results.csv`
- `_4_OptSim/results/doe_results_viz.pdf`
- `_4_OptSim/results/doe_response_surfaces.pdf`
- `_4_OptSim/population/variant_XXXX/`

## Outputs

Common output locations:

- `_3_StandardSim/results/` - standard-study PDFs and metrics CSVs
- `_4_OptSim/population/` - generated DOE variants and per-variant artifacts
- `_4_OptSim/results/` - DOE result tables and visualization PDFs

## Documentation

Long-form docs live in the separate BobDocs repository under `docs/`.
Useful starting points include:

- `../BobDocs/docs/index.md`
- `../BobDocs/docs/bobsim/index.md`
- `../BobDocs/docs/bobsim/doe.md`
- `../BobDocs/docs/startup-guide/index.md`

## Notes

- `make sim-doe` runs the DOE pipeline inside the Docker `doe` service.
- `make SteadyStateEval` and `make TransientEval` run the standard workflows
  directly from Python.
- The repository intentionally keeps report generation, simulation execution,
  and DOE post-processing separate so each layer can evolve independently.
