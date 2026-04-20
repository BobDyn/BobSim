# BobSim Knowledge

This document is a current map of the Python side of BobSim after the recent refactor.
It focuses on what is implemented in `_2_GeneralSim` and `_3_StandardSim`, with short notes on the other top-level folders.

## 1) Repository layout (high level)

- `_0_Utils/`
  - plotting/report helpers used by standard simulations
  - `external/BobLib/` is a git submodule that contains the Modelica library
- `_1_VisualSim/`
  - visual post-processing pipeline (`run_visual.py`) that renders MP4 from NPZ bundles
- `_2_GeneralSim/`
  - simulation runtime engine that executes compiled OpenModelica binaries and extracts outputs
- `_3_StandardSim/`
  - standard-specific orchestrators (`ISO4138`, `KnC`) plus build scripts/configs
- `_4_DOE/`
  - DOE scaffold exists, but major parts are still placeholders

## 2) Main execution path for standard runs

Entry points:

- `_3_StandardSim/run_standard.py`
- `examples/run_standard.py`

Flow:

1. Load YAML config via `_2_GeneralSim/config.py:load_config`.
2. Instantiate simulator from `_3_StandardSim/registry.py` using `STANDARD_REGISTRY[config["standard"]]`.
3. Call simulator `.run()`.
4. Build PDF report with `_0_Utils/reporting/report_engine.py`.

Current registry targets:

- `ISO4138 -> ISO4138Sim`
- `KnC -> KnCSim`

## 3) `_2_GeneralSim` details

Core file: `_2_GeneralSim/general_sim.py`

Main class:

- `_2_GeneralSim`

What it does:

- Resolves executable from `build_dir` (`name` or `name.exe`).
- Runs executable with OpenModelica CLI args and override string.
- Reads CSV output with NumPy and normalizes channel names.
- Supports single case, serial case list, and process-pool parallel execution.
- Optionally exports visual bundles (`.npz`) when `simulation.visual` is enabled.

Key public methods used by standards:

- `run_case(schema, overrides, ...)`
- `run_cases(schema, cases, ...)`
- `run_cases_parallel(schema, cases, ...)`
- helpers for extraction: `get`, `steady`, `last`

Schema abstraction:

- `_2_GeneralSim/output_schema.py` defines `OutputSchema` with:
  - `signals`
  - `mode` (`steady`, `raw`, `last`)
  - optional custom `validator` and `extractor`

Note on earlier mismatch concern:

- `KnCSim` now calls `run_cases(...)` (not `self.sim.run()`).
- `KNC_SCHEMA` is now an `OutputSchema` object.
- The two specific interface mismatch issues previously called out appear resolved in current code.

## 4) `_3_StandardSim` details

### ISO4138

Files:

- `_3_StandardSim/ISO4138/iso4138_sim.py`
- `_3_StandardSim/ISO4138/iso4138_schema.py`
- `_3_StandardSim/ISO4138/iso4138_config.yml`
- `_3_StandardSim/ISO4138/build.mos`

Behavior:

- Builds signed radius sweep cases (`+R` and `-R`).
- Executes serial or parallel depending on `execution.parallel`.
- Extracts steady metrics via `ISO4138_SCHEMA`.
- Produces summary metrics and plotting series (understeer, roll, curvature, radius tracking).

Expected build location from script:

- `_3_StandardSim/ISO4138/build/`

### KnC

Files:

- `_3_StandardSim/KnC/knc_sim.py`
- `_3_StandardSim/KnC/knc_schema.py`
- `_3_StandardSim/KnC/knc_config.yml`
- `_3_StandardSim/KnC/build.mos`

Behavior:

- Creates two simulation objects:
  - front: `build/fr_build`, executable `BobLib.Standards.FrKnC`
  - rear: `build/rr_build`, executable `BobLib.Standards.RrKnC`
- Executes one case each (raw mode schema) and fuses front/rear data.
- Computes engineered summary + dense series:
  - geometry gains (camber/toe/caster/KPI/trail/scrub)
  - anti metrics (heave and roll)
  - jacking curves
  - motion ratios (spring and stabar)
  - LLTD estimate and stiffness breakdown

Expected build locations from script:

- `_3_StandardSim/KnC/build/fr_build/`
- `_3_StandardSim/KnC/build/rr_build/`

## 5) Current observed filesystem state (from this checkout)

- `_3_StandardSim/KnC/build/` exists, but only `results/` is present.
- `_3_StandardSim/KnC/build/fr_build/` and `_3_StandardSim/KnC/build/rr_build/` are not currently present.
- `_3_StandardSim/ISO4138/build/` is not currently present.

Implication: compiled executables are not currently visible in expected build folders in this working tree snapshot.

## 6) Reporting and visualization

- `_0_Utils/reporting/report_engine.py` writes PDF to config `report.output_path`.
- `ISO4138` and `KnC` have dedicated summary-page handling.
- `_2_GeneralSim` can export visual NPZ bundles into `results/raw_results/...` when enabled.
- `_1_VisualSim/run_visual.py` consumes a visual YAML template + NPZ and writes MP4.

## 7) DOE area status

- `_4_DOE/` has many files, but key files like `run_doe.py` and `batch.py` are placeholders.
- Treat DOE as in-progress scaffolding, not a stable pipeline yet.

## 8) BobLib submodule policy

`_0_Utils/external/BobLib` is configured and tracked as a git submodule:

- `.gitmodules` contains `_0_Utils/external/BobLib`
- git index mode is `160000` for that path (gitlink)
- submodule has `.git` pointer to `.git/modules/_0_Utils/external/BobLib`

Recommendation:

- Do not ignore the submodule path in root `.gitignore`.
- Keep the gitlink tracked in the super-repo, and manage BobLib changes via submodule commit updates.
- If you want to suppress dirty-submodule noise only, use git config options (for example, `status.submoduleSummary` or ignore settings in `.gitmodules`), not `.gitignore`.

