# DOE and reverse engineering a vehicle from target metrics

**TL;DR:** Sweep a population of vehicle variants → simulate them all → aggregate metrics → search backwards. Given target performance numbers, find the car that hits them. Everything here lives under `_4_OptSim/StandardSens/`.

## Three questions, one set of compiled vehicles

OptSim answers three different questions. They are separate tools, not stages
of one tool:

| Target | Question | Vehicles | Answer |
| --- | --- | --- | --- |
| `make opt-standard` (+ `opt-refined`, `opt-search`) | Which parameters matter, and roughly where is a car with these numbers? | many, sampled | sensitivities, response surfaces, nearest sampled car |
| `make opt-solve` | What do I set on *this* car to hit these numbers? | a star of `2n + 1` around the current car | one setup, simulated |
| `make opt-trade` | What does each of these specific changes buy, and cost? | the ones you name | a comparison table |

None replaces another. The sweep is still how you learn a design space. Use the
solver or the trade study when you have a specific question. All three write
their vehicles with the same generator and compile them with the same compiler.
So a variant means the same thing in each tool.

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
| `DOE_SCOPE` | `all` (default), `setup`, or `architecture`. See [Sweep scope](#sweep-scope-setup-vs-architecture) |

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

### Sweep scope: setup vs. architecture

Each `sweep.variables` entry can have a `scope:` tag. The tag splits the
23-variable sweep into the two studies that it otherwise mixes:

| `scope:` | What it holds | Tagged |
| --- | --- | --- |
| `setup` | knobs you can adjust on the built car between sessions: front/rear toe, camber, spring package, damper rate, anti-roll bar rate | 10 |
| `architecture` | properties fixed once the car exists: sprung and unsprung masses, sprung CG, driver inertias, body torsional stiffness | 9 |
| *(omitted)* | both, or neither. Swept in **every** scope | 4 |

So `DOE_SCOPE=setup` sweeps **14** variables (10 tagged + 4 untagged),
`DOE_SCOPE=architecture` sweeps **13** (9 + 4), and `all` sweeps all 23.

A missing `scope:` tag is permissive on purpose. `_variable_in_scope()` treats an
untagged variable as a member of every scope. So a scoped sweep never silently
drops a new entry. The possible failure is a parameter that the sweep did not
need. It shows as an extra column in the results table. A missing parameter
would not show. The split is a vehicle-dynamics decision, and it is only in the
YAML. `generate_configs.py` has no hardcoded variable lists.

Two of the four untagged entries are untagged on purpose, after review. The
reasons are recorded here so that nobody has to argue them again:

- **`aero.load_scale`** applies `operation: scale` identically to `dragTable`,
  `downforceTable`, `mxTable`, `myTable` and `mzTable`. So it changes the
  downforce level and holds aero balance and L/D exactly constant. No wing
  adjustment does that. It represents air density, a change of the whole
  configuration, or CFD/tunnel map uncertainty. It is not a paddock knob and not
  a fixed property.
- **`driver_mass.mass_kg`, `driver_mass.cg_m.x`, `driver_mass.cg_m.z`** are both.
  Teams use different drivers for skidpad, autocross and endurance. Seat inserts
  and pedal-box adjustment move driver CG on the same afternoon. `cg_m.x` also
  has the second-strongest effect on understeer gradient in the whole set
  (~0.27 deg/g across its range). A setup sweep without it would hide a
  first-order effect. The driver *inertia* entries (`ixx`/`iyy`/`izz`) stay
  `architecture`.

Select a scope with `DOE_SCOPE`, or with the two wrapper targets:

```bash
make opt-standard-setup                    # = make opt-standard DOE_SCOPE=setup
make opt-standard-architecture             # = make opt-standard DOE_SCOPE=architecture
make opt-standard DOE_SCOPE=setup DOE_METHOD=lhs DOE_SAMPLES=30
```

`DOE_SCOPE` gets to the run as `BOBSIM_DOE_SCOPE` (the `DOE_ENV` block in the
makefile). `_resolve_sweep_scope()` uses an explicit `scope=` argument to
`refresh_doe_config()` first, then the env var, then `all`. So every existing
command still sweeps all 23 variables. Any other value raises an error before
the first variant is generated. The error names the three legal values.

**Why it exists.** "Prescribe target metrics, solve for a setup" is useful only
for parameters that you can actually change. A sweep of driver Izz and body
torsional stiffness together with front toe spends the sample budget on axes the
answer cannot act on. The reverse lookup then returns a car that you would have
to rebuild, not a setup sheet. Sweep `setup` when you want the setup. Sweep
`architecture` when you decide what to build.

**You can trace a scoped sweep, but only partly.** `_doe_config.yaml` records the
resolved scope as a top-level `scope:` key (`scope: all` in the checked-in file).
The generator removes the per-variable `scope:` tags, because scope is a filter
at generation time. `search.py` reads that key with `load_sweep_scope()`.
`_warn_if_results_scope_is_narrow()` warns in two situations:

- The config names a scope other than `all`. Every parameter outside that scope
  stayed at baseline and was never a free variable.
- The config names `all`, but the results table does not have all the parameters
  that the config lists. A config older than the key also counts, because the
  search reads it as unknown, not unrestricted. You see this case when you
  restore `_doe_config.yaml` from git after a scoped run. The config claims every
  parameter, but the population covers only some.

The guard **infers the second case from the table's columns**. It does not read
it from provenance, because the aggregated results table still records no scope
of its own. So the guard can tell you that a population is narrower than the
config claims. It cannot tell you which scope produced the population. It would
also miss a scoped run whose columns happened to cover everything the config
names. A record of the scope next to the results is a known follow-up. It is not
part of this change, on purpose. That condition also currently gives more than
one warning line, because the older missing-columns message covers the same
condition. Read the condition, not the count.

So `make opt-standard-setup` followed by `make opt-search` reports 14 parameters
and gives the reason. `python -m StandardSens.pipeline.generate_configs` prints
`scope: setup (14 variables)`. The pipeline run itself does not print it.

Run `make clean-opt` when you change scope. The variant count changes with the
scope. So a rerun against an existing population stops. It does not quietly use
that population again. The population-count check in `prepare_variants()` and
the pipeline-hash check both tell you to clean first. It does not matter which
one stopped you.

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

`PYTHONPATH` uses the platform's own separator. On Windows, outside the
container, that separator is `;`: `PYTHONPATH="_4_OptSim;."`. The `:` form above
fails with `No module named 'StandardSens'`. That error looks like a broken
checkout, not a path problem.

It reads the parquet, or falls back to a sibling `.csv` if no parquet exists.
If neither is present you get `Results not found ... Has the pipeline run?` —
run `make opt-standard` first.

Each metric dimension is normalized by its observed range before the KDTree
query, so metrics with wildly different units (deg/g vs. Nm) contribute
comparably to "nearest". The reported `distance` is in that normalized space —
useful for ranking candidates against each other, not as a physical error.

### Reading the result honestly

This is nearest-neighbour lookup over a finite sampled population, not an
optimizer. `search.py` runs four guards on every query and prints the results to
**stderr**. All four are advisory. None of them raises an error, drops a row, or
changes the returned frame. With four warnings, you get the same variant as with
no warnings. So if you send stderr to `/dev/null`, or read only the formatted
block on stdout, you discard the only thing that marks the answer as unusable.

| Guard (`pipeline/search.py`) | Fires when | Reports |
| --- | --- | --- |
| `_warn_targets_outside_population` | a target is below its metric column's `min()` or above its `max()` | the observed `[low, high]` bounds, and the overshoot past the nearer edge in **population-widths** (overshoot ÷ that column's sampled range, the same normalization that the KDTree uses). It then refers you to the `range` bounds in `configs/vehicle_architecture.yaml` |
| `_warn_population_too_small` | the table has fewer rows than `MIN_USEFUL_POPULATION` (10) | the row count *and* the swept-parameter count, i.e. how under-determined the lookup and any fitted surface are |
| `_warn_if_results_are_stale` | the results file's mtime predates `_doe_config.yaml`, `vehicle_architecture.yaml`, `compiler_config.yaml`, `aggregator_config.yaml`, or the repo-root `vehicle.yml` | which of those inputs is newer than the table |
| `_warn_if_results_scope_is_narrow` | the config names a scope other than `all`, **or** names `all` while the table is missing parameters the config lists | that the answer depends on a scope-restricted population. See [Sweep scope](#sweep-scope-setup-vs-architecture) for what it can and cannot tell you |

An older warning also lists each swept parameter that has no column in the
results table. The report then leaves that parameter out. This warning overlaps
the second case of the scope guard. So one condition can produce more than one
warning line. Read the condition, not the number of lines. The older warning
fires only when a parameter is *absent*. That is why the mtime guard exists. A
config edit that keeps the same parameter names makes a stale table look valid.

With a single target metric, the population-widths number and the reported
`distance` are the same quantity. With several, `distance` is the Euclidean
combination across normalized dimensions. Each guard line is for one metric.

#### The query that motivated the guards

```bash
make opt-search METRICS="SteadyStateEval_understeer_gradient_deg_per_g=0.05"
```

Against a four-variant smoke population, this query returned `variant_0000` with
`distance: 4.349424`. That population spanned `[0.278154, 0.330610]` for the
metric, and the target was `0.05`. The number is not a physical error, and it is
not a near miss in unusual units. The target is **4.35 population-widths outside
the range the sweep ever visited**. The returned variant had an actual
understeer gradient of 0.278154 deg/g. Before the guards, this result printed
with no warning at all, and it looked like an answer.

Those figures come from one recorded run. A new sweep changes the bounds and the
distance. The shape of the failure does not change. So check the warnings, not
the numbers.

The same table holds **4 variants against 23 swept parameters**. `DOE_SAMPLES=3`
produces that: a smoke-test population, not a design population. Four rows
cannot resolve 23 axes. So the "nearest" variant is almost arbitrary, whatever
you ask for. Omit `DOE_SAMPLES` to get the full sweep before you believe any
answer.

The guards cover two limits only partly:

- **The reported parameters are the swept ones only.** `search.py` derives them
  from `variables[].path` in `_doe_config.yaml`, so it reports exactly what the
  sweep varied: 23 parameters at the default scope, 14 or 13 at a scoped one.
  Everything else in the returned variant stays at baseline. The scope guard tells
  you *that* the set was narrowed. Nothing tells you the baseline values of the
  rest of the car. If they matter, read the variant's own definition under
  `_4_OptSim/Build/StandardSens/population/`.
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
that locate it in the Modelica record. Also add a `scope:`. Without one, the
variable is swept in *every* scope. That is safe, but probably not what you
meant.

The sampler, aggregator, and reverse lookup all key off `variables[].path`, so
nothing else needs updating. Rerun `make opt-standard` to rebuild the table;
the old one is stale and `opt-search` will say so.

## Solving for a setup directly

`opt-search` can return only a vehicle that the sweep sampled. The cost to sample
a space well increases exponentially with each added parameter. For the question
"what do I set on this car to hit these numbers", `opt-solve` asks it directly,
as a small bounded least-squares problem:

```bash
make opt-solve                                   # targets from configs/solve_config.yaml
make opt-solve TARGETS="understeer_gradient_deg_per_g=0.30 roll_gradient_deg_per_g=0.80"
make opt-solve TARGETS="..." KNOBS="front.stabar.rate_n_m_per_rad rear.stabar.rate_n_m_per_rad"
```

It works in these steps:

- It simulates a star design: the centre plus one step each way per knob,
  `2n + 1` runs.
- It fits a slope and a curvature for each knob.
- It solves the inverse on that surrogate in milliseconds.
- It **simulates the setup it proposes**.
- If the result misses, it adds the miss to the surrogate and repeats, up to
  four times.

Every number it reports comes from a simulation of the exact setup it returns.
`opt-search` leaves that step to you.

| | `opt-search` | `opt-solve` |
| --- | --- | --- |
| Cost in the number of parameters | exponential, to sample the space | linear, `2n + 1` |
| Answer | nearest sampled variant | a continuous setup, snapped to parts that exist |
| Answer simulated? | no | yes, always |
| Unreachable target | the closest edge variant, with a warning | `UNREACHABLE`, with the names of the knobs at their range limits |
| Fewer targets than knobs | many equally near variants | the smallest change from the current car |

The settings are in `configs/solve_config.yaml`:

- the targets
- the knobs
- a tolerance for each metric. Every targeted metric needs one, because the
  tolerance is also the scale that weights one target against another.
- the solver's own test matrix
- the CPU count

`TARGETS=` replaces the configured targets. It does not merge with them. You can
give metric names with or without the `SteadyStateEval_` prefix that the
aggregated table uses. The exit status is 0 only when every target is within
tolerance.

Know these three things before you trust it.

**Knobs are setup parameters, and conditions are compiled.** The solver accepts
only `scope: setup` variables as knobs. The driver, the masses and the aero map
are conditions of the question, not answers to it. Set them in `vehicle.yml`.
They are compiled into the baseline that the solver starts from.

**Most evaluations need no compile, but not every knob works that way.** A
compile is roughly 70 % of a variant's wall time. The model's equations do not
change between variants. The model reads springs, anti-roll bars and dampers at
initialisation. So the solver applies them to one cached executable with
`-override`. An override run of those six knobs matches a recompiled run to
2.5e-5 deg/g on understeer gradient and 5e-6 deg/g on roll gradient.

Static toe and camber do not work that way, and the failure is silent. They
build the wheel's `toHub.R_rel` rotation matrix. OpenModelica evaluates that
matrix at compile time and stores it in the executable. The toe parameter still
reports `isValueChangeable="true"`. The runner accepts the override without a
warning, and every bound copy of the angle updates. But the matrix that the
wheel actually uses does not change. Every mass and CG value has the same
problem through `combineMassRecords`.

So `RUNTIME_SAFE_PATHS` in `pipeline/overrides.py` is an allow-list. The solver
compiles each path that is not in it. Each distinct toe or camber value costs
its own executable, and that includes each verification. `opt-solve` names any
compile-only knobs before it starts. The list is a fact about the model, not a
setting. So it is in code next to the evidence for it, and it is tied to a
BobLib pin. To check a new candidate, compile two variants that differ only in
it and compare their `*_init.xml`. A non-changeable parameter whose `start`
differs was evaluated at compile time. It will not follow an override.

**It uses its own test matrix, not the standard's.** The standard runs four
isolines (22 cases). But every exported metric except the velocity slopes comes
from the isoline at `metric_target_velocity_mps`. Only three of its points are
inside the 1–4 m/s² band that the gradients are fitted over. The solver writes a
config for each evaluation with one isoline and six points in that band. That is
faster and better conditioned, and the standard and its regression baselines do
not change. But a gradient from `opt-solve` and the same gradient from
`make standard-eval-steady-state` are fitted through different points. They will
differ slightly. Compare results from the same tool.

The solver caches executables and evaluations under
`_4_OptSim/Build/StandardSens/solve/`. It discards the cache when BobLib, the
vehicle or the SteadyStateEval tooling changes. The star does not depend on the
targets. So after the star is cached, a new set of targets costs only the
verification runs.

As a guide to cost, on a 12-CPU container with the default four knobs:

- The first solve took about 8 minutes: one compile, nine star evaluations and
  one verification.
- Each later solve against different targets took about 70 seconds.
- A four-variant sweep of the same car took 26 minutes, and it cannot
  interpolate between its samples.

## Trade studies

A trade study compares vehicles you name, on metrics you choose, across more than
one standard sim:

```bash
make opt-trade                                   # configs/trade_study.yaml
make opt-trade STUDY=path/to/another_study.yaml
```

The study file names the candidates as changes from the baseline. It also names
the metrics to compare for each standard:

```yaml
name: rear_roll_stiffness
candidates:
  stiff_rear_bar:    {rear.stabar.rate_n_m_per_rad: 961.495352}
  soft_front_spring: {front.actuation.spring_rate_n_per_m: 21015.2202}
  both:              {rear.stabar.rate_n_m_per_rad: 961.495352,
                      front.actuation.spring_rate_n_per_m: 21015.2202}
metrics:
  SteadyStateEval:
    understeer_gradient_deg_per_g: {resolution: 0.02}
  TransientEval:
    yaw_rise_time_s: {resolution: 0.005}
```

The report goes to `_4_OptSim/results/trade/<name>.md` and `.csv`. It has one
table for each standard. Each cell has the simulated value and its change from
baseline.

**Every candidate is compiled, never overridden.** `opt-solve` makes the opposite
choice, and there is a reason. A trade study must be able to change mass, CG, toe
and camber. An override silently fails to change exactly those parameters (see
above). A compile is always correct. It costs about 36 s per vehicle when several
build at the same time. The cache key is the content. So the baseline, and any
candidate that two studies share, is built and simulated only once across all
studies.

**One compile serves every standard.** SteadyStateEval, RampSteerEval and
TransientEval all run the same model, `BobLib.Experiments.Standards.VehicleSim`.
`_3_StandardSim` itself builds it once and points all three configs at it. They
also share one interface. So a standard is one entry in `STANDARDS` in
`pipeline/standards.py`. FourPostEval is not in the list. It runs `FourPostSim`,
which is a different model, so it would need a second compile for each vehicle.

**There is no score and no ranking, on purpose.** How much understeer is worth how
much settling time is an engineering decision. A weighted sum would hide that
decision inside a number. The report does make sure that each difference is
worth reading:

- **Resolution.** Each metric can state the smallest change worth acting on. The
  report still shows a smaller delta, but marks it `~`. So nobody reads a 0.001 s
  change in rise time as a finding. If you leave the resolution off, the report
  does not judge the delta.
- **Lost cases.** The report marks a run whose simulation lost cases as `n/c` and
  does not compare it. Its fits use fewer points than the baseline's fits. So the
  delta would mix the design change with the missing data. If the baseline lost
  cases, every comparison on that standard is `n/c`. The command exits 2.
- **Stacking.** Sometimes one candidate makes exactly the changes of two others.
  The report then gives the interaction: the combined effect minus the sum of the
  parts. Above the metric's resolution, the combination does something that
  neither part predicts. Then "we'll do both" is not the sum you budgeted for.
  Below the resolution, the interaction cannot be told apart from zero. That is
  weaker than a claim that the changes add. So the report prints the number next
  to the label.
- **Ambiguous names.** TransientEval reports some metrics once per group under
  one name (`yaw_gain_dc` for the step and again for the frequency sweep). You
  can ask for those only with the group, for example `step.yaw_gain_dc`. The bare
  name gives an error that lists the options.

**A candidate can change only a declared variable.** The declared variables are
the `sweep.variables` entries in `configs/vehicle_architecture.yaml`. Each one
needs the Modelica record block that it maps to. To trade on something new, such
as wheelbase, declare it there first (see *Adding a swept parameter*). The study
accepts a value outside a variable's sweep range and adds a note. The range
limits what the sweep samples, not what is physically valid.

Compare results from the same tool. A metric here comes from each standard's own
test matrix. So a gradient from `opt-trade` matches
`make standard-eval-steady-state`. It does not match `opt-solve`, which fits
through its own denser isoline.

## Envelope sensitivities

`_4_OptSim/EnvelopeSens/` is the same idea against GGV/YMD envelope outputs
rather than StandardSim studies, driven by `EnvelopeSens/config.yml`:

```bash
make opt-envelope
```

It has no reverse-lookup equivalent today.
