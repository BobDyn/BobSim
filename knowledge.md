# BobSim Knowledge

This document is a current map of the BobSim Python and infrastructure side as
observed in this checkout on 2026-05-06. It is meant to help new contributors
understand what is active now, what is legacy, and where the build/run paths
currently live.

## 1) Repository layout

- `_0_Utils/`
  - shared plotting and reporting utilities
  - `external/BobLib/` is a git submodule containing the Modelica library
- `_1_VisualSim/`
  - PyVista/VTK post-processing pipeline that renders MP4 from NPZ bundles
  - visual templates live in `_1_VisualSim/visual_templates/`
- `_2_EnvelopeSim/`
  - first-principles envelope tools, currently GGV and YMD generators
  - this replaces the older `_2_GeneralSim` area in the tracked tree
- `_3_StandardSim/`
  - standard maneuver orchestration and shared simulation runners
  - current active standards are SteadyStateEval and ISO7401
  - KnC code still exists, but currently points at removed `_2_GeneralSim`
    imports
- `_4_DOE/`
  - DOE pipeline scaffold with sampler, generator, compiler, batch runner, and
    aggregator modules
  - this area has advanced beyond placeholder-only status, but should still be
    treated as an in-progress pipeline
- root infrastructure
  - `Dockerfile` builds on `openmodelica/openmodelica:v1.26.3-ompython`
  - `docker-compose.yml` provides `standard` and `doe` services
  - `makefile` wraps setup, shells, standard runs, DOE runs, cleanup, and direct
    ISO module entry points

## 2) Current standard-simulation architecture

The active standard-sim path no longer uses `_2_GeneralSim`.

Current shared runtime files:

- `_3_StandardSim/_modelica_runner.py`
- `_3_StandardSim/_fmu_runner.py`
- `_3_StandardSim/build.mos`

Current active standard modules:

- `_3_StandardSim/SteadyStateEval/steady_state_eval_sim.py`
- `_3_StandardSim/ISO7401/iso7401_sim.py`

Active build artifact location:

- `_3_StandardSim/Build/`

The current build script compiles one unified executable:

- model: `BobLib.Standards.VehicleSim`
- executable: `_3_StandardSim/Build/BobLib.Standards.VehicleSim`
- init XML: `_3_StandardSim/Build/BobLib.Standards.VehicleSim_init.xml`
- output format: CSV

This is different from the older per-standard build directories described in
previous versions of this file.

## 3) Standard run flow

The most reliable entry points today are module entry points:

- `python3 -m _3_StandardSim.SteadyStateEval.steady_state_eval_sim`
- `python3 -m _3_StandardSim.ISO7401.iso7401_sim`

The makefile exposes matching targets:

- `make SteadyStateEval`
- `make ISO7401`

The intended containerized flow is:

1. Initialize BobLib submodule with `make init`.
2. Build the Docker image with `make setup`.
3. Compile Modelica with `omc _3_StandardSim/build.mos`.
4. Run a standard module or make target.
5. PDF and metrics outputs are written under `_3_StandardSim/results/`.

Important caveat:

- `make sim-iso` and `make sim-knc` call `python run_standard.py ...` from
  the `_3_StandardSim` working directory, but `_3_StandardSim/run_standard.py`
  is not present in this tracked checkout.
- `examples/run_standard.py` still imports `_2_GeneralSim.config` and
  `_3_StandardSim.registry`, neither of which is present in this tracked
  checkout.

## 4) `_3_StandardSim/_modelica_runner.py`

`ModelicaRunner` is the active OpenModelica executable runner.

What it does:

- resolves a compiled executable and matching `*_init.xml`
- creates isolated run directories under `<build_dir>/results/run_<id>/`
- writes per-case `overrides.txt`
- executes the OpenModelica binary from its build directory
- passes runtime arguments such as:
  - `-overrideFile=...`
  - `-r=...`
  - `-stopTime=...`
  - `-s=...`
  - `-tolerance=...`
  - `-lv=...`
  - `-variableFilter=...`
  - `-noEquidistantTimeGrid`
  - `-noEventEmit`
- reads result CSVs with pandas
- extracts either full raw arrays or final sample values
- supports serial and process-pool parallel case execution
- preserves Python-only case metadata whose keys start with `_`
- optionally removes per-case run directories through `execution.cleanup`

Supported extraction modes:

- `raw`: returns `time` and array-valued signals
- `steady`: returns the last value of each signal
- `last`: same final-sample behavior as `steady`

## 5) `_3_StandardSim/_fmu_runner.py`

`FMURunner` is present as an FMI 2.0 Model Exchange runner. It is not currently
used by SteadyStateEval or ISO7401, but it mirrors the public runner shape of
`ModelicaRunner`.

What it does:

- loads FMU metadata with `fmpy`
- extracts the FMU
- instantiates `FMU2Model`
- integrates the model with `scipy.integrate.solve_ivp`
- supports cached initialization snapshots as `.npz`
- supports serial and process-pool parallel case execution
- supports raw and final-sample extraction
- supports constant inputs, time-varying input profiles, and a Python-side
  controller hook

Currently implemented Python-side controller:

- `steady_state_eval_radius_velocity_pi`

Expected config keys live under `simulation`, including:

- `fmu_path`
- `snapshot_file`
- `solver`
- `rtol`
- `atol`
- `max_step`
- `output_dt`
- `init_duration`
- `use_snapshot`
- `init_parameters`
- `init_input_values`

## 6) SteadyStateEval current behavior

Files:

- `_3_StandardSim/SteadyStateEval/steady_state_eval_sim.py`
- `_3_StandardSim/SteadyStateEval/steady_state_eval_config.yml`

Backend:

- requires `simulation.backend: modelica`
- uses `ModelicaRunner.from_config(config)`
- default build dir from config is `_3_StandardSim/Build`
- executable is `BobLib.Standards.VehicleSim`

Case generation:

- reads `sweep.testVel`, `sweep.n_cases`, `sweep.r_min`, `sweep.r_max`
- creates a log-spaced radius sweep
- applies `radius_bias_power`
- duplicates the sweep with positive and negative radii
- computes commanded curvature as `1 / radius`
- sends Modelica overrides such as:
  - `initialVel`
  - `useMode`
  - `targetVel`
  - `targetRad`
  - `curvGain`
  - `curvTi`
  - `velGain`
  - `velTi`
  - `stopTime`

Extraction and summary:

- extraction mode is `steady`
- signals include steering, lateral acceleration, roll, sideslip, torque,
  velocity, and yaw rate
- summary computes:
  - signed lateral acceleration range
  - understeer gradient
  - roll gradient
  - handwheel torque range
  - curvature and radius tracking error
  - plotting series for steering behavior, vehicle states, sensitivities, and
    steering effort
- writes a metrics CSV beside the report:
  - `_3_StandardSim/results/steady_state_eval_report_metrics.csv`
- builds a PDF when `report.enabled` is true:
  - `_3_StandardSim/results/steady_state_eval_report.pdf`

## 7) ISO7401 current behavior

Files:

- `_3_StandardSim/ISO7401/iso7401_sim.py`
- `_3_StandardSim/ISO7401/iso7401_config.yml`

Backend:

- uses `ModelicaRunner.from_config(config)`
- current config relies on runner defaults for:
  - `simulation.build_dir: _3_StandardSim/Build`
  - `simulation.exec_name: BobLib.Standards.VehicleSim`

Case generation:

- supports left and right directions
- supports step cases when `test.run_step` is true
- supports one-period sine cases when `test.run_sine_one_period` is true
- supports continuous sine sweep cases when `test.run_continuous_sine` is true
- maps cases onto `VehicleModel` modes:
  - `useMode = 1`: open-loop sine steering plus closed-loop speed
  - `useMode = 2`: ramp/step steering plus closed-loop speed
- keeps report metadata separate from runner-facing Modelica overrides

Extraction and summary:

- extraction mode is `raw`
- signals include steering, velocity, yaw, sideslip, acceleration, roll, and
  handwheel torque
- summary selects representative step, one-period sine, and continuous sine
  cases
- frequency response is computed from fixed-amplitude, single-direction
  continuous sine cases
- summary computes step response metrics, gain/phase metrics, fit errors, and
  plotting series
- writes a metrics CSV beside the report:
  - `_3_StandardSim/results/iso7401_report_metrics.csv`
- builds a PDF when `report.enabled` is true:
  - `_3_StandardSim/results/iso7401_report.pdf`

## 8) KnC status

Files still present:

- `_3_StandardSim/KnC/knc_sim.py`
- `_3_StandardSim/KnC/knc_schema.py`
- `_3_StandardSim/KnC/knc_config.yml`
- `_3_StandardSim/KnC/build.mos`

Current status:

- KnC is not aligned with the current runner infrastructure.
- `knc_sim.py` imports `_2_GeneralSim.general_sim._2_GeneralSim`.
- `knc_schema.py` imports `_2_GeneralSim.output_schema.OutputSchema`.
- `_2_GeneralSim` is not present in the tracked checkout.

Older expected KnC build layout:

- `_3_StandardSim/KnC/build/fr_build/`
- `_3_StandardSim/KnC/build/rr_build/`

Current observed tree:

- `_3_StandardSim/KnC/` exists
- no `build/fr_build/` or `build/rr_build/` directories are visible in this
  checkout

Recommendation:

- Treat KnC as legacy or mid-migration until it is ported to `ModelicaRunner`
  or a replacement runner.
- Keep its config/report plotting notes, because the summarization logic still
  documents intended outputs such as heave/roll kinematics, jacking, anti
  metrics, motion ratios, and LLTD estimates.

## 9) Reporting and plotting

Report engine:

- `_0_Utils/reporting/report_engine.py`

Plot engine:

- `_0_Utils/plotting/plot_engine.py`

Supported report standards:

- `SteadyStateEval`
- `ISO7401`
- `KnC`

Report behavior:

- reads `report.output_path`
- creates output parent directories
- writes PDF pages with `matplotlib.backends.backend_pdf.PdfPages`
- adds a title page
- adds standard-specific summary pages
- renders configured plots when the YAML has a `plots` section

Supported plot layouts:

- `single`
- `dual`
- `triple`
- `quad`

Currently registered plot type:

- `signal`

## 10) Visualization

File:

- `_1_VisualSim/run_visual.py`

Inputs:

- a visual YAML template
- an NPZ signal bundle
- `--mp4 <output_path>`

Templates currently present:

- `_1_VisualSim/visual_templates/steady_state_eval_visual.yml`
- `_1_VisualSim/visual_templates/iso7401_visual.yml`
- `_1_VisualSim/visual_templates/fr_knc_visual.yml`
- `_1_VisualSim/visual_templates/rr_knc_visual.yml`

Current renderer capabilities:

- loads point trajectories from NPZ columns
- supports geometry vectors
- supports camera attachment to a moving point/frame
- renders with PyVista/VTK
- can overlay signal plots with matplotlib
- writes MP4 through imageio

Important caveat:

- The current active `ModelicaRunner` does not export visual NPZ bundles.
- Existing visual NPZ files may be checked-in/generated artifacts, but the old
  automatic export behavior from `_2_GeneralSim` is no longer present in the
  active runner.

## 11) `_2_EnvelopeSim`

This folder currently contains standalone first-principles analysis utilities.

### GGV

File:

- `_2_EnvelopeSim/GGV/ggv_generation.py`

Purpose:

- computes quasi-static full-vehicle acceleration envelopes
- models mass properties, static weight distribution, aero load, load transfer,
  tire load sensitivity, power limits, brake limits, and a friction ellipse
- outputs 2D and 3D GGV-style envelope data/plots

Core dataclasses:

- `VehicleParams`
- `GGVConfig`
- `GGVEnvelope`

### YMD

File:

- `_2_EnvelopeSim/YMD/ymd_generation.py`

Purpose:

- computes quasi-static yaw moment diagrams
- models mass properties, static weight distribution, aero load, lateral load
  transfer, tire lateral peak friction, approximate cornering stiffness,
  saturated lateral forces, sideslip sweeps, and steering sweeps
- outputs YMD carpet/wireframe plots, beta slices, contour maps, CSV exports,
  and speed-sweep surfaces

Core dataclasses:

- `VehicleParams`
- `YMDConfig`
- `YMDResult`
- `YMDSpeedSweepResult`

Important caveat:

- These tools are first-principles analysis utilities, not Modelica trim solves
  and not FMU/OpenModelica runtime wrappers.

## 12) DOE status

Entry point:

- `_4_DOE/run_doe.py`

Current pipeline stages:

1. `sampler.sample`
2. `generator.generate_variants`
3. `compiler.compile_all`
4. `batch.run_all`
5. `aggregator.aggregate`

Config files:

- `_4_DOE/configs/doe_config.yaml`
- `_4_DOE/configs/compiler_config.yaml`
- `_4_DOE/configs/build_template.mos`

Runtime folders:

- `_4_DOE/population/`
- `_4_DOE/results/`

Infrastructure:

- docker compose service: `doe`
- make target: `make sim-doe`
- cleanup target: `make clean-doe`

Current observed tree:

- `_4_DOE/population/variant_0000` through `variant_0003` exist locally
- `_4_DOE/results/` exists locally
- root `.gitignore` ignores DOE-generated population and results folders

Recommendation:

- Treat DOE as in-progress but real infrastructure.
- Validate end-to-end behavior before relying on output as a stable pipeline
  contract.

## 13) Docker and make targets

Docker image:

- base: `openmodelica/openmodelica:v1.26.3-ompython`
- installs Python 3.14 from deadsnakes
- installs Python packages needed for core simulation and analysis
- installs Modelica Standard Library `3.2.3+maint.om`

Compose services:

- `standard`
  - working directory: `/bobsim/_3_StandardSim`
  - `PYTHONPATH=/bobsim`
- `doe`
  - working directory: `/bobsim/_4_DOE`
  - `PYTHONPATH=/bobsim`

Useful make targets:

- `make init`: initialize submodules
- `make setup`: build compose image
- `make rebuild`: rebuild compose image without cache
- `make shell-standard`: shell in the standard service
- `make shell-doe`: shell in the DOE service
- `make SteadyStateEval`: run SteadyStateEval module directly on host
- `make ISO7401`: run ISO7401 module directly on host
- `make clean`: remove common Python/build/simulation artifacts
- `make clean_build`: empty `_3_StandardSim/**/Build` directories
- `make clean_results`: empty `_3_StandardSim/**/results` directories

Caveats:

- `make sim-iso` and `make sim-knc` reference a missing
  `_3_StandardSim/run_standard.py` entry point.
- The clean target removes all `*.csv`, `*.mat`, and `*.log` files under the
  repo, so be careful if generated metrics are still needed.

## 14) Current observed filesystem state

Observed active build artifacts:

- `_3_StandardSim/Build/` exists
- `_3_StandardSim/Build/BobLib.Standards.VehicleSim` exists and is executable
- `_3_StandardSim/Build/BobLib.Standards.VehicleSim_init.xml` exists
- `_3_StandardSim/Build/results/run_*` directories exist

Observed standard outputs:

- `_3_StandardSim/results/steady_state_eval_report.pdf`
- `_3_StandardSim/results/steady_state_eval_report_metrics.csv`
- `_3_StandardSim/results/iso7401_report.pdf`
- `_3_StandardSim/results/iso7401_report_metrics.csv`

Observed missing or stale paths:

- `_2_GeneralSim/` is not present
- `_3_StandardSim/run_standard.py` is not present
- `_3_StandardSim/registry.py` is not present
- `_3_StandardSim/SteadyStateEval/build/` is not present
- `_3_StandardSim/KnC/build/fr_build/` is not present
- `_3_StandardSim/KnC/build/rr_build/` is not present

## 15) Known migration cleanup items

The following references should be cleaned up when the team has bandwidth:

- `examples/run_standard.py`
  - imports `_2_GeneralSim.config`
  - imports `_3_StandardSim.registry`
- `_3_StandardSim/KnC/knc_sim.py`
  - imports `_2_GeneralSim.general_sim`
- `_3_StandardSim/KnC/knc_schema.py`
  - imports `_2_GeneralSim.output_schema`
- `pyproject.toml`
  - mypy `files` still includes `_2_GeneralSim`
- `makefile`
  - `sim-iso` and `sim-knc` reference missing `run_standard.py`

Possible cleanup direction:

- either restore a current `_3_StandardSim/run_standard.py` and registry, or
  remove the old generic entry point and standardize on module entry points
- port KnC to `ModelicaRunner`, or clearly mark it as legacy until the new KnC
  executable/build path is rebuilt
- update `pyproject.toml` to type-check `_2_EnvelopeSim` instead of
  `_2_GeneralSim`

## 16) BobLib submodule policy

`_0_Utils/external/BobLib` is configured and tracked as a git submodule.

Current submodule facts:

- `.gitmodules` contains `_0_Utils/external/BobLib`
- the super-repo tracks the path as a gitlink
- the current working tree reports BobLib as modified relative to the recorded
  gitlink

Policy:

- Do not ignore the submodule path in root `.gitignore`.
- Keep the gitlink tracked in the super-repo.
- Manage BobLib changes by committing in the submodule and then updating the
  super-repo gitlink.
- If only dirty-submodule status noise needs to be reduced, use git submodule
  ignore/status settings rather than `.gitignore`.
