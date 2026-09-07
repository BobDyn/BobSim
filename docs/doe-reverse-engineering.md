# DOE and reverse engineering a vehicle from target metrics

**TL;DR:** Sweep a population of vehicle variants → simulate them all → aggregate metrics → search backwards. Given target performance numbers, find the car that hits them. Everything here lives under `_4_OptSim/StandardSens/`.

## Quick start: a small sweep

From a clean checkout, this is the whole thing:

```bash
make init
make docker-build
make opt-standard DOE_METHOD=lhs DOE_SAMPLES=3
```

`DOE_SAMPLES=3` gives four variants — the baseline plus three Latin-hypercube
samples. Leave the overrides off to use the full sweep configured in
`configs/vehicle_architecture.yaml` (currently 93 variants, much slower).

| Variable | Meaning |
| --- | --- |
| `DOE_METHOD` | `lhs` or `interval_splice` |
| `DOE_SAMPLES` | LHS sample count, plus the baseline |
| `DOE_INTERVALS` | `interval_splice` steps per variable |

The overrides rewrite the generated `_doe_config.yaml`, so it will show as
modified afterwards. `git checkout _4_OptSim/StandardSens/configs/_doe_config.yaml`
restores it.

To check the plumbing without an OpenModelica toolchain — useful on any
machine, and what CI runs:

```bash
make opt-doe-smoke
```

### The FourPostEval prerequisite

The sweep varies spring rate, and holding static ride height while the rate
changes requires recomputing each spring's free length. That calculation
(`static_balance_free_length` in `pipeline/generator.py`) needs the motion
ratios measured by FourPostEval, read from
`_3_StandardSim/generated_results/four_post_eval_report_metrics.csv`
(specifically `static_motion_ratio_front` / `_rear`, falling back to
`avg_motion_ratio_*`).

`make opt-standard` now builds and runs FourPostEval automatically when that
file is missing, so this is usually invisible. It is the reason a first run is
much slower than later ones. If you invoke the Python entry point directly and
skip that step, variant generation aborts before anything is compiled, and the
error names the paths it searched.

## The forward pipeline

`pre_screen_sensitivities.py` runs the whole thing end to end in five stages:

1. **Sample and generate variants** — `pipeline/sampler.py` + `generator.py`
   read the DOE config and emit one vehicle definition per variant into
   `_4_OptSim/Build/StandardSens/population/`.
2. **Build and simulate** — `pipeline/build_pipeline.py` + `compiler.py` compile
   and run each variant. This is the expensive stage.
3. **Aggregate** — `pipeline/aggregator.py` collapses every variant's study
   output into one table:
   `_4_OptSim/Build/StandardSens/standard_sensitivity_results.parquet`.
4. **Response surfaces / sensitivities** — fit and rank parameter influence.
5. **Plot** — tornado plots via `_shared/plot_sensitivity_tornado.py`.

```bash
make opt-standard
```

Variants are content-hashed (`pipeline/_pipeline_hash.py`), so re-running skips
work whose inputs didn't change. `prepare_variants(force_rebuild=False)` is the
knob if you need to force a rebuild.

## Configuring the sweep

`_doe_config.yaml` is **generated**. The file you edit is
`configs/vehicle_architecture.yaml`; `refresh_doe_config()` regenerates
`_doe_config.yaml` from it at the start of every run. Edits to the generated
file are silently discarded.

The generated config looks like this:

```yaml
architecture:
  template: ../../vehicle.yml     # baseline vehicle
  vehicle:  EVBatInvMotDiff_DWBCStabar_DWBCStabar
  record:   EVBatInvMotDiff_DWBCStabar_DWBCStabarRecord
  source:   configs/vehicle_architecture.yaml
baseline_mo: .../BobLib/Records/VehicleDefn/EVBatInvMotDiff_DWBCStabar_DWBCStabarRecord.mo
variables:
  - path:  sprung_mass.mass_kg   # where it lives in vehicle.yml
    range: [144.576, 176.704]    # sweep bounds
    block: pBaseSprungMass       # the Modelica record block
    param: m                     # the parameter on that block
    label: sprung mass           # plot label
    index: [0]                   # optional, for vector params like rCM
```

Each `variables` entry is the bridge between a `vehicle.yml` path and a Modelica
record parameter. Both halves must be right: `path` drives the YAML mutation,
`block`/`param`/`index` drive the generated `.mo`. A wrong `block`/`param` fails
loudly at compile; a wrong `path` silently sweeps nothing.

The `architecture` and `baseline_mo` paths are relative to the config file, not
the repo root.

### Editing `configs/build_template.mos`

That file is filled in with Python's `str.format()`, so **every literal brace
must be doubled**. Modelica array literals are the trap:

```modelica
loadModel(Modelica, {{"4.1.0"}});   ← renders as {"4.1.0"}
buildModel({model}, ...);           ← a real substitution
```

A single brace makes `format()` read `{"4.1.0"}` as a replacement field and the
build dies with `KeyError: '"4'` inside a worker process, far from the cause.
`test_build_template_renders` guards this.

## Refining

Once the pre-screen ranks parameters, `refined_response_surfaces.py` selects the
influential ones and runs a denser sweep over just those, producing proper
response surfaces instead of a coarse scatter.

```bash
make opt-refined
```

It reuses the pre-screen's coefficient/selection CSVs as input, so it must run
*after* `make opt-standard`.

## The reverse lookup

`pipeline/search.py` is the backwards step. It loads the aggregated table,
builds a KDTree over whichever metric columns you name, and returns the nearest
variant's swept parameters.

```bash
make opt-search METRICS="SteadyStateEval_understeer_gradient_deg_per_g=0.05 SteadyStateEval_peak_handwheel_torque_Nm=12"
make opt-search METRICS="SteadyStateEval_understeer_gradient_deg_per_g=0.05" SEARCH_TOP=5
```

Equivalent direct invocation:

```bash
PYTHONPATH=_4_OptSim:. python -m StandardSens.pipeline.search \
    --metrics SteadyStateEval_understeer_gradient_deg_per_g=0.05 \
    --top 3
```

It reads the parquet, or falls back to a sibling `.csv` if no parquet exists.
If neither is present you get `Results not found ... Has the pipeline run?` —
run `make opt-standard` first.

Each metric dimension is normalized by its observed range before the KDTree
query, so metrics with wildly different units (deg/g vs. Nm) contribute
comparably to "nearest". The reported `distance` is in that normalized space —
useful for ranking candidates against each other, not as a physical error.

### Reading the result honestly

This is nearest-neighbour lookup over a finite sampled population, not an
optimizer. Three limits to keep in front of you:

- **The answer is only as good as the population.** If your targets sit outside
  the sampled ranges, you get the closest edge variant with a large distance,
  not a warning. Check `distance` and check the target against the `range`
  bounds in `_doe_config.yaml`.
- **The reported parameters are the swept ones only.** `search.py` derives them
  from `variables[].path` in `_doe_config.yaml`, so it reports exactly what the
  sweep varied (23 parameters as configured today). Everything else in the
  returned variant is baseline. If the results table predates a config change,
  the search warns about the parameters it could not report.
- **Under-constrained targets have many answers.** Naming one metric will find a
  variant that matches it and says nothing about the rest of the car. Use
  `--top`/`SEARCH_TOP` to see the spread of candidates rather than trusting the
  single nearest.

Treat the result as a starting point, then run the real study
(`make standard-eval-steady-state`) on that configuration to confirm.

### Adding a swept parameter

Edit `configs/vehicle_architecture.yaml` — **not** `_doe_config.yaml`, which is
generated from it by `pipeline/generate_configs.py` and overwritten on every
run. Each entry needs a `vehicle.yml` `path` plus the `block`/`param`(/`index`)
that locate it in the Modelica record.

The sampler, aggregator, and reverse lookup all key off `variables[].path`, so
nothing else needs updating. Rerun `make opt-standard` to rebuild the table;
the old one is stale and `opt-search` will say so.

## Envelope sensitivities

`_4_OptSim/EnvelopeSens/` is the same idea against GGV/YMD envelope outputs
rather than StandardSim studies, driven by `EnvelopeSens/config.yml`:

```bash
make opt-envelope
```

It has no reverse-lookup equivalent today.
