# BobSim Knowledge: GeneralSim and StandardSim

This document captures the current state of the refactored simulation stack in:

- `_2_GeneralSim/`
- `_3_StandardSim/`

It focuses on what exists today (interfaces, flow, and assumptions), not idealized behavior.

## 1) High-level architecture

The simulation flow is layered:

1. Load YAML config (`_2_GeneralSim/config.py`).
2. Select a standard-specific simulator from `_3_StandardSim/registry.py`.
3. Standard simulator builds one or more simulation cases and calls the generic runner (`_2_GeneralSim/general_sim.py`).
4. Standard simulator post-processes raw signals into:
   - `summary` (scalar metrics)
   - `series` (arrays for plotting/reporting)
5. Report generation is triggered by `examples/run_standard.py` via `_0_Utils/reporting/report_engine.py`.

## 2) `_2_GeneralSim/` contents

### `_2_GeneralSim/general_sim.py`

Core runner class: `_2_GeneralSim`.

What it does:

- Resolves compiled executable in a `build/` folder (`<exec_name>` or `<exec_name>.exe`).
- Requires `<exec_name>_init.xml` to exist.
- Runs OpenModelica-generated executable with runtime flags:
  - `-override=...`
  - `-r=<csv output path>`
  - `-s=<solver>`
  - `-outputFormat=<format>`
  - `-lv=<log level>`
  - optional: `-noEquidistantTimeGrid`, `-noEventEmit`, `-variableFilter`
- Stores run outputs under sibling `results/` folders (`<build parent>/results`).
- Loads CSV into `dict[str, np.ndarray]` with normalized keys (dots/brackets/quotes removed).

Primary APIs:

- `run_raw(overrides, tag=None, timeout=None, cleanup=False, output_filter=None, keep=None)`
  - Lowest-level execution + CSV loading.
- `run_case(schema, overrides, tag=None, cleanup=False)`
  - Runs one case with `OutputSchema` filter/validation/extraction.
- `run_cases(schema, cases, cleanup=False)`
  - Sequential multi-case execution.
- `run_cases_parallel(schema, cases, max_workers=None, fail_fast=False, cleanup=False)`
  - Multiprocess multi-case execution using `ProcessPoolExecutor`.

Helper methods:

- `get(data, key)` lookup with normalized key handling.
- `steady(data, key, window=10, tol=1e-2)` tail-mean with convergence check.
- `last(data, key)` last sample.

### `_2_GeneralSim/output_schema.py`

Defines dataclass `OutputSchema`:

- `signals: list[str]` required signals.
- optional `validator(sim, data)`.
- optional `extractor(sim, data)`.

Behavior:

- `build_filter()` returns `time|<signal1>|<signal2>|...` for Modelica variable filtering.
- `extract()` defaults to steady-state extraction (`sim.steady`) for each signal when no custom extractor is given.

### `_2_GeneralSim/config.py`

- `load_config(path)` reads YAML via `yaml.safe_load`.

### `_2_GeneralSim/schema.py`

- Minimal config validation: currently only asserts key `standard` exists.

## 3) `_3_StandardSim/` contents

### `_3_StandardSim/registry.py`

Maps standard name to simulator class:

- `ISO4138 -> ISO4138Sim`
- `KnC -> KnCSim`

This is the dispatch point used by `examples/run_standard.py`.

---

### ISO4138 standard (`_3_StandardSim/ISO4138/`)

Files:

- `iso4138_sim.py`
- `iso4138_schema.py`
- `iso4138_config.yml`
- `build.mos`

#### `iso4138_sim.py`

`ISO4138Sim`:

- Uses one executable:
  - build dir: `_3_StandardSim/ISO4138/build`
  - exec: `BobLib.Standards.ISO4138`
- Builds sweep cases from config:
  - logarithmic radius sweep between `r_min` and `r_max`
  - biased by `radius_bias_power`
  - mirrored to positive/negative radii
  - each case includes `testVel` and `testRad`
- Executes cases sequentially or in parallel based on `execution.parallel`.
- Summarizes into standard output format (`summary`, `series`).

Summary logic includes:

- signed lateral acceleration ordering (`ay_signed`)
- roadwheel fit (`polyfit`)
- curvature-based actual radius and tracking error
- sensitivity gradients (`np.gradient`)
- scalar metrics such as understeer gradient and radius error statistics

#### `iso4138_schema.py`

Defines `ISO4138_SCHEMA` as an `OutputSchema` with required ISO signals:

- steering angles, lateral acceleration, roll, sideslip, curvature, steering torque

#### `iso4138_config.yml`

Contains:

- simulation runtime options
- execution options (`parallel`, `max_workers`, `cleanup`)
- sweep definition (`testVel`, `n_cases`, `r_min`, `r_max`, `radius_bias_power`)
- report metadata + plot specifications

#### `build.mos`

OpenModelica script to compile `BobLib.Standards.ISO4138` into `_3_StandardSim/ISO4138/build`.

---

### KnC standard (`_3_StandardSim/KnC/`)

Files:

- `knc_sim.py`
- `knc_schema.py`
- `knc_config.yml`
- `build.mos`

#### `knc_sim.py`

`KnCSim`:

- Uses two executables:
  - front: `_3_StandardSim/KnC/build/fr_build` (`BobLib.Standards.FrKnC`)
  - rear: `_3_StandardSim/KnC/build/rr_build` (`BobLib.Standards.RrKnC`)
- Builds a single overrides dict from `test` config (`steerMagnitude`, `heaveMagnitude`, `rollMagnitude`, `forceMagnitude`).
- Runs front and rear models, then merges outputs into `summary` + `series`.

Summary includes:

- time span
- camber range (`gamma_range`)
- toe range (`toe_range`)
- full front/rear time-series for reporting

#### `knc_schema.py`

Current schema is a plain `list[str]` (`KNC_SCHEMA`) of required signals, not an `OutputSchema` object.

#### `knc_config.yml`

Contains:

- simulation options
- test magnitudes
- report output path
- plot definitions for camber, toe, and inputs

#### `build.mos`

OpenModelica script that loops over `fr_build` and `rr_build` and builds:

- `BobLib.Standards.FrKnC`
- `BobLib.Standards.RrKnC`

## 4) Entry point and runtime contract

`examples/run_standard.py` currently does:

1. `config = load_config(path)`
2. `sim = STANDARD_REGISTRY[config["standard"]](config)`
3. `result = sim.run()`
4. `ReportEngine(config).build(result)`
5. print `result["summary"]`

So each standard simulator is expected to provide:

- constructor signature: `__init__(config)`
- method: `run()` returning dict with keys:
  - `summary` (serializable scalars)
  - `series` (arrays keyed by plot config)

## 5) Current-state notes after refactor

These are important for anyone extending or debugging:

- `KnCSim.run()` calls `self.sim_fr.run(...)` / `self.sim_rr.run(...)`, but `_2_GeneralSim` currently exposes `run_case`, `run_cases`, `run_cases_parallel`, and `run_raw` (no `run` method).
- `KNC_SCHEMA` is a `list[str]`, while `_2_GeneralSim` methods expect an `OutputSchema` object when using `run_case(s)` paths.

Implication: KnC likely needs interface alignment to the refactored `_2_GeneralSim` API.

## 6) Quick extension guide

To add a new standard under `_3_StandardSim/`:

1. Add `<StandardName>/<standard>_sim.py` implementing `run()`.
2. Define signal contract (prefer `OutputSchema`).
3. Add build script (`build.mos`) and config YAML.
4. Register class in `_3_StandardSim/registry.py`.
5. Ensure `run()` returns `{"summary": ..., "series": ...}` for reporting.

