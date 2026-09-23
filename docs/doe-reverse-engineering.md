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
| `DOE_SCOPE` | `all` (default), `setup`, or `architecture` — see [Sweep scope](#sweep-scope-setup-vs-architecture) |

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

Each `sweep.variables` entry may carry a `scope:` tag, splitting the 23-variable
sweep into the two studies it otherwise conflates:

| `scope:` | What it holds | Tagged |
| --- | --- | --- |
| `setup` | knobs adjustable on the built car between sessions — front/rear toe, camber, spring package, damper rate, anti-roll bar rate | 10 |
| `architecture` | properties fixed once the car exists — sprung and unsprung masses, sprung CG, driver inertias, body torsional stiffness | 9 |
| *(omitted)* | genuinely both, or neither — swept in **every** scope | 4 |

So `DOE_SCOPE=setup` sweeps **14** variables (10 tagged + 4 untagged),
`DOE_SCOPE=architecture` sweeps **13** (9 + 4), and `all` sweeps all 23.

Leaving `scope:` off is deliberately permissive: `_variable_in_scope()` treats an
untagged variable as a member of every scope, so a newly added entry is never
silently dropped from a scoped sweep. The failure mode is a parameter swept where
it didn't need to be — visible as an extra column in the results table — rather
than one missing from it, which is not. The partition is a vehicle-dynamics
judgement call and lives entirely in the YAML; `generate_configs.py` hardcodes no
variable lists.

Two of the four untagged entries are untagged on purpose, after review, and the
reasoning is worth keeping so it isn't re-litigated:

- **`aero.load_scale`** applies `operation: scale` identically to `dragTable`,
  `downforceTable`, `mxTable`, `myTable` and `mzTable`, so it holds aero balance
  and L/D exactly constant while moving downforce level. No wing adjustment
  behaves that way. It represents air density, a whole-configuration swap, or
  CFD/tunnel map uncertainty — neither a paddock knob nor a fixed property.
- **`driver_mass.mass_kg`, `driver_mass.cg_m.x`, `driver_mass.cg_m.z`** are both.
  Teams run different drivers between skidpad, autocross and endurance, and seat
  inserts and pedal-box adjustment move driver CG the same afternoon. `cg_m.x` is
  also the second-strongest influence on understeer gradient in the whole set
  (~0.27 deg/g across its range), so dropping it from a setup sweep would hide a
  first-order effect. The driver *inertia* entries (`ixx`/`iyy`/`izz`) stay
  `architecture`.

Select a scope with `DOE_SCOPE`, or with the two wrapper targets:

```bash
make opt-standard-setup                    # = make opt-standard DOE_SCOPE=setup
make opt-standard-architecture             # = make opt-standard DOE_SCOPE=architecture
make opt-standard DOE_SCOPE=setup DOE_METHOD=lhs DOE_SAMPLES=30
```

`DOE_SCOPE` reaches the run as `BOBSIM_DOE_SCOPE` (the `DOE_ENV` block in the
makefile). `_resolve_sweep_scope()` prefers an explicit `scope=` argument to
`refresh_doe_config()`, then the env var, then `all` — so every existing
invocation keeps sweeping all 23 variables. Any other value raises before a
single variant is generated, naming the three legal ones.

**Why it exists.** "Prescribe target metrics, solve for a setup" is only
actionable over parameters you can actually turn. Sweeping driver Izz and body
torsional stiffness jointly with front toe spends the sample budget on axes the
answer cannot act on, and the reverse lookup then hands back a car you would
have to rebuild rather than a setup sheet. Sweep `setup` when you want the setup;
sweep `architecture` when you are deciding what to build.

**A scoped sweep is traceable, but only partly.** `_doe_config.yaml` records the
resolved scope as a top-level `scope:` key (`scope: all` in the checked-in file);
the per-variable `scope:` tags are stripped, since scope is a generation-time
filter. `search.py` reads that key back with `load_sweep_scope()` and
`_warn_if_results_scope_is_narrow()` warns in two situations:

- the config names a scope other than `all` — every parameter outside it was
  pinned at baseline and was never a free variable;
- the config names `all` (or predates the key, which reads as unknown rather than
  unrestricted) but the results table is missing parameters the config lists.
  That is what restoring `_doe_config.yaml` from git after a scoped run looks
  like: the config claims every parameter, the population only covers some.

The second case is **inferred from the table's columns**, not read from
provenance: the aggregated results table still records no scope of its own. So
the guard can tell you a population is narrower than the config claims, but not
which scope produced it, and it would miss a scoped run whose columns happened to
cover everything the config names. Recording the scope alongside the results is a
known follow-up, deliberately not part of this change. That condition also
currently trips more than one warning line — the older missing-columns message
covers the same ground — so read the condition, not the count.

`make opt-standard-setup` then `make opt-search` therefore reports 14 parameters
and says why. `python -m StandardSens.pipeline.generate_configs` prints
`scope: setup (14 variables)`; the pipeline run itself does not echo it.

Run `make clean-opt` when you change scope. The variant count changes with the
scope, so a rerun against an existing population stops rather than quietly
reusing it — both the population-count check in `prepare_variants()` and the
pipeline-hash check tell you to clean first, and it is not worth working out
which one caught you.

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
container, that is `;` — `PYTHONPATH="_4_OptSim;."` — and the `:` form above
fails with `No module named 'StandardSens'`, which reads like a broken checkout
rather than a path problem.

It reads the parquet, or falls back to a sibling `.csv` if no parquet exists.
If neither is present you get `Results not found ... Has the pipeline run?` —
run `make opt-standard` first.

Each metric dimension is normalized by its observed range before the KDTree
query, so metrics with wildly different units (deg/g vs. Nm) contribute
comparably to "nearest". The reported `distance` is in that normalized space —
useful for ranking candidates against each other, not as a physical error.

### Reading the result honestly

This is nearest-neighbour lookup over a finite sampled population, not an
optimizer. `search.py` runs four guards on every query and prints what they find
to **stderr**. All four are advisory: none of them raise, drop a row, or change
the returned frame. The variant you get under four warnings is the same variant
you would have got in silence — so if you send stderr to `/dev/null`, or read
only the formatted block on stdout, you have discarded the only thing marking the
answer as unusable.

| Guard (`pipeline/search.py`) | Fires when | Reports |
| --- | --- | --- |
| `_warn_targets_outside_population` | a target is below its metric column's `min()` or above its `max()` | the observed `[low, high]` bounds, and the overshoot past the nearer edge in **population-widths** — overshoot ÷ that column's sampled range, the same normalization the KDTree uses — then points you at the `range` bounds in `configs/vehicle_architecture.yaml` |
| `_warn_population_too_small` | the table has fewer rows than `MIN_USEFUL_POPULATION` (10) | the row count *and* the swept-parameter count, i.e. how under-determined the lookup and any fitted surface are |
| `_warn_if_results_are_stale` | the results file's mtime predates `_doe_config.yaml`, `vehicle_architecture.yaml`, `compiler_config.yaml`, `aggregator_config.yaml`, or the repo-root `vehicle.yml` | which of those inputs is newer than the table |
| `_warn_if_results_scope_is_narrow` | the config names a scope other than `all`, **or** names `all` while the table is missing parameters the config lists | that the answer rests on a scope-restricted population — see [Sweep scope](#sweep-scope-setup-vs-architecture) for what it can and cannot tell you |

An older warning also lists any swept parameter that has no column in the results
table, then leaves it out of the report. It overlaps the scope guard's second
case, so one condition can produce more than one warning line; read the
condition, not the number of lines. It only fires when a parameter is *absent*,
which is why the mtime guard exists — a config edit that keeps the same parameter
names leaves a stale table looking valid.

With a single target metric, the population-widths number and the reported
`distance` are the same quantity. With several, `distance` is the Euclidean
combination across normalized dimensions, while each guard line is per-metric.

#### The query that motivated the guards

```bash
make opt-search METRICS="SteadyStateEval_understeer_gradient_deg_per_g=0.05"
```

Run against a four-variant smoke population, this returned `variant_0000` with
`distance: 4.349424`. That population spanned `[0.278154, 0.330610]` for the
metric, and the target was `0.05`: the number is not physical error and not a
near miss in awkward units — it is **4.35 population-widths outside the range
the sweep ever visited**, attached to a variant whose actual understeer gradient
was 0.278154 deg/g. Before the guards this printed with no warning at all, and
read like an answer.

Those figures are one recorded run. Re-sweep and the bounds and the distance
move; the shape of the failure does not, so check the warnings rather than
matching the numbers.

The same table holds **4 variants against 23 swept parameters**. That is what
`DOE_SAMPLES=3` produces — a smoke-test population, not a design population.
Four rows cannot resolve 23 axes, so the "nearest" variant is close to arbitrary
regardless of what you ask for. Omit `DOE_SAMPLES` for the full sweep before
believing any answer.

Two limits the guards only partly cover:

- **The reported parameters are the swept ones only.** `search.py` derives them
  from `variables[].path` in `_doe_config.yaml`, so it reports exactly what the
  sweep varied — 23 parameters at the default scope, 14 or 13 at a scoped one.
  Everything else in the returned variant sits at baseline. The scope guard tells
  you *that* the set was narrowed; nothing tells you which baseline values the
  rest of the car was pinned at, so read the variant's own definition under
  `_4_OptSim/Build/StandardSens/population/` if it matters.
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
that locate it in the Modelica record. Add a `scope:` too — without one the
variable is swept in *every* scope, which is safe but probably not what you
meant.

The sampler, aggregator, and reverse lookup all key off `variables[].path`, so
nothing else needs updating. Rerun `make opt-standard` to rebuild the table;
the old one is stale and `opt-search` will say so.

## Solving for a setup directly

`opt-search` can only return a vehicle that happened to be sampled, and sampling
a space well costs exponentially more with every parameter added. When the
question is "what do I set on this car to hit these numbers", `opt-solve` asks it
directly instead, as a small bounded least-squares problem:

```bash
make opt-solve                                   # targets from configs/solve_config.yaml
make opt-solve TARGETS="understeer_gradient_deg_per_g=0.30 roll_gradient_deg_per_g=0.80"
make opt-solve TARGETS="..." KNOBS="front.stabar.rate_n_m_per_rad rear.stabar.rate_n_m_per_rad"
```

It simulates a star design (the centre plus one step each way per knob, `2n + 1`
runs), fits a slope and a curvature per knob, solves the inverse on that
surrogate in milliseconds, and then **simulates the setup it proposes**. A miss
is folded back into the surrogate and the solve repeats, up to four times. Every number it reports comes from a simulation of the
exact setup it returns, which is the step `opt-search` leaves to you.

| | `opt-search` | `opt-solve` |
| --- | --- | --- |
| Cost in the number of parameters | exponential, to sample the space | linear, `2n + 1` |
| Answer | nearest sampled variant | a continuous setup, snapped to parts that exist |
| Answer simulated? | no | yes, always |
| Unreachable target | the closest edge variant, with a warning | `UNREACHABLE`, naming the knobs that ran out of range |
| Fewer targets than knobs | many equally near variants | the smallest change from the current car |

Settings live in `configs/solve_config.yaml`: the targets, the knobs, a tolerance
per metric (required for every targeted metric, since it doubles as the scale
that trades one target against another), the solver's own test matrix, and the
CPU count. `TARGETS=` replaces the configured targets outright rather than
merging with them. Metric names may be given with or without the
`SteadyStateEval_` prefix the aggregated table uses. Exit status is 0 only when
every target is met within tolerance.

Three things are worth knowing before trusting it.

**Knobs are setup parameters, and conditions are compiled.** Only `scope: setup`
variables are accepted as knobs. The driver, the masses and the aero map are
conditions of the question, not answers to it: set them in `vehicle.yml`, where
they are compiled into the baseline the solver starts from.

**Most evaluations need no compile, and that is not true of every knob.** A
compile is roughly 70 % of a variant's wall time, and the model's equations
never change between variants. Springs, anti-roll bars and dampers are read at
initialisation, so the solver applies them to one cached executable with
`-override`. An override run of those six reproduces a recompiled run to
2.5e-5 deg/g on understeer gradient and 5e-6 deg/g on roll gradient.

Static toe and camber do not work that way, and the failure is silent. They
build the wheel's `toHub.R_rel` rotation matrix, which OpenModelica evaluates at
compile time and bakes into the executable. The toe parameter still reports
`isValueChangeable="true"`, the override is accepted without a warning, every
bound copy of the angle updates — and the matrix the wheel actually uses does
not move. Every mass and CG value has the same problem through
`combineMassRecords`. So `RUNTIME_SAFE_PATHS` in `pipeline/overrides.py` is an
allow-list, anything absent from it is compiled, and each distinct toe or camber
value (including each verification) costs its own executable. `opt-solve` names
any compile-only knobs before it starts. The list is a fact about the model, not
a setting, which is why it lives in code beside the evidence for it and is tied
to a BobLib pin. To check a new candidate, compile two variants that differ only
in it and compare their
`*_init.xml`: any non-changeable parameter whose `start` differs was evaluated
at compile time, and will not follow an override.

**It uses its own test matrix, not the standard's.** The standard runs four
isolines (22 cases), but every exported metric except the velocity slopes comes
from the one at `metric_target_velocity_mps`, and only three of its points fall
inside the 1–4 m/s² band the gradients are fitted over. The solver writes a
per-evaluation config with one isoline and six points in that band. That is
faster and better conditioned, and it leaves the standard and its regression
baselines untouched — but it means a gradient from `opt-solve` and the same
gradient from `make standard-eval-steady-state` are fitted through different
points and will differ slightly. Compare like with like.

Executables and evaluations are cached under `_4_OptSim/Build/StandardSens/solve/`,
and the cache is discarded whenever BobLib, the vehicle or the SteadyStateEval
tooling changes. The star does not depend on the targets, so once it is cached a
new set of targets costs only the verification runs.

As a guide to cost, on a 12-CPU container with the default four knobs: the first
solve took about 8 minutes (one compile, nine star evaluations, one
verification), and each later solve against different targets took about 70
seconds. A four-variant sweep of the same car took 26 minutes and cannot
interpolate between its samples.

## Envelope sensitivities

`_4_OptSim/EnvelopeSens/` is the same idea against GGV/YMD envelope outputs
rather than StandardSim studies, driven by `EnvelopeSens/config.yml`:

```bash
make opt-envelope
```

It has no reverse-lookup equivalent today.
