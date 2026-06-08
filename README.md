# BobSim

BobSim is the BobDyn high-fidelity vehicle analysis workspace. It wraps the
BobLib Modelica vehicle models with repeatable Python workflows for standard
vehicle dynamics studies, envelope calculations, sensitivity workflows,
post-processing, and report generation.

The full documentation lives at:

https://bobdyn.com

Use the BobDyn documentation site as the detailed source of truth. This README is
the quick release guide for getting a clean checkout running and checking that it
is healthy.

## Repository Layout

- `_0_Utils/`: shared Python utilities, plotting/reporting helpers, and the
  BobLib submodule.
- `_1_VisualSim/`: experimental/offline visualization tooling; core model
  visualization currently happens in OMEdit.
- `_2_EnvelopeSim/`: GGV/YMD performance-envelope workflows.
- `_3_StandardSim/`: standard vehicle studies: SteadyStateEval, TransientEval,
  and FourPostEval.
- `_4_OptSim/`: sensitivity and response-surface workflows.
- `tests/`: release-polish and workflow regression checks.
- `vehicle.yml`: active vehicle configuration copied into BobLib generation
  inputs by the build targets.

## Quick Start

Initialize the BobLib submodule:

```bash
make init
```

Build the Docker development image:

```bash
make docker-build
```

Show the available targets:

```bash
make help
```

The Docker image is based on OpenModelica and installs the Python dependencies
from `requirements.txt`.

## Release Checks

Run the local release gate:

```bash
make ci
```

This runs:

- `make lint`
- `make typecheck`
- `make test`

GitHub Actions runs the same make targets directly on the runner with the BobLib
submodule checked out recursively.

## Target Language

BobSim's make targets use a small, intentional vocabulary:

- `docker-*`: build or rebuild the development image.
- `shell-*`: open an interactive shell in a workflow context.
- `standard-*`: build and run standard vehicle evaluations.
- `envelope-*`: generate performance-envelope outputs.
- `opt-*`: run sensitivity and response-surface workflows.
- `clean-*`: remove generated artifacts.

## Standard Simulation Entrypoints

Run the complete standard baseline:

```bash
make standard-eval-all
```

That target builds missing executables, then runs SteadyStateEval,
TransientEval, and FourPostEval.

For focused standard work, build and run individual studies:

```bash
make standard-build
make standard-eval-steady-state
make standard-eval-transient

make standard-build-four-post
make standard-eval-four-post
```

Build-only targets are also available:

```bash
make standard-build
make standard-build-four-post
```

Reports and metric CSVs are written under `_3_StandardSim/results/`.

## Cleanup

Remove local Python/tool caches:

```bash
make clean
```

Use the more specific cleanup targets for generated simulation artifacts:

```bash
make clean-standard
make clean-envelope
make clean-opt
```
