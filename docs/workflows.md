# Workflows

`make help` is the authoritative target list. This doc covers the parts that
aren't obvious from the target names.

## First run on a fresh clone

```bash
make init          # git submodule update --init --recursive  ← do not skip
make docker-build  # OpenModelica + requirements.txt
make app           # http://127.0.0.1:8765
```

`make init` is not optional. Without it BobLib is empty or stale and every
Modelica build fails. See [boblib-submodule.md](boblib-submodule.md).

## Docker vs. native

Makefile auto-detects context: inside container (`/.dockerenv` exists) targets run directly; outside they wrap in `docker compose run --rm` (the `RUN` variable).

| Target | Runs on | Needs on host | Needs in container |
| --- | --- | --- | --- |
| `make app`, `make deploy-*` | Host (not in `RUN`) | `requirements.txt` installed | — |
| `make visual-*` | Host (not in `RUN`) | `make visual-deps` | — (the simulation step still uses it) |
| `make lint`, `make test`, `make typecheck` | Container (in `RUN`) | — | Auto-built |
| `make standard-*`, `make envelope-*`, `make opt-*` | Container or host | `omc` on `PATH` (OpenModelica) | Auto-built |

**Shortcut for native testing:** `make shell` opens a container shell for any workflow.

## Target vocabulary

| Prefix | Meaning |
| --- | --- |
| `docker-*` | Build/rebuild the dev image |
| `shell-*` | Interactive shell in a workflow context |
| `standard-*` | Build and run standard vehicle evaluations |
| `lap-*` | QSS and transient reduced-order lap simulations |
| `envelope-*` | GGV / YMD performance-envelope maps |
| `opt-*` | Sensitivity, response-surface, and DOE workflows |
| `visual-*` | Replay a run in the BobVis viewer, or render it to video |
| `clean-*` | Remove generated artifacts |

## Standard studies

See [simulation-entrypoints.md](simulation-entrypoints.md) for fidelity and use-case context.

```bash
make standard-eval-all      # ramp steer + steady state + transient + four post
```

Builds are incremental: `standard-build` and `standard-build-four-post` are
file targets that only recompile when the corresponding `.mo` model, the `.mos`
build script, or `BobLib/package.mo` changes. If a build seems stale after
editing something else in BobLib, that dependency list is why — touch the model
or run `make clean-standard`.

Individual studies:

```bash
make standard-eval-ramp-steer
make standard-eval-steady-state
make standard-eval-transient
make standard-eval-four-post   # uses the separate FourPostSim executable
```

Output: `_3_StandardSim/generated_results/` (`*_report_metrics.csv`, `*_report.pdf`).

## Lap-time simulation

```bash
make lap-eval-qss        # optimize line and QSS speed profile
make lap-eval-transient  # repeat optimization, then integrate the transient model
make lap-eval            # write both result sets in one run
make lap-eval-all-dof    # repeat with model-specific maps for all four fidelities
make lap-validation-visuals  # disposable figures under temp/lap_time_validation/
```

The config selects one shared `model_dof` (3, 6, 10, or 14) for GGV generation
and transient integration. Output lands in
`_3_StandardSim/generated_results/lap_time_eval/`. See
[lap-time-simulation.md](lap-time-simulation.md) for the track schema,
optimization objective, and validation interpretation.

Compare precomputed suspension-kinematics grid sizes with an in-loop nonlinear
constraint solve:

```bash
make reduced-kinematics-benchmark
```

The benchmark writes `temp/kinematics_benchmark/summary.json`. Short reduced
transients can use the nonlinear backend directly with
`make reduced-eval REDUCED_KINEMATICS=nonlinear`; production envelopes and laps
should normally retain the lookup backend.

## Envelopes and sensitivities

See [simulation-entrypoints.md](simulation-entrypoints.md) for fidelity and use-case context.

```bash
make envelope-ggv / envelope-ymd / envelope-all
make opt-standard   # StandardSens pre-screen sensitivities
make opt-envelope   # EnvelopeSens sensitivities
make opt-refined    # StandardSens refined response surfaces
make opt-search METRICS="Metric=value ..."   # reverse lookup, see the DOE doc
```

Note the `opt-*` targets set `PYTHONPATH=_4_OptSim:.` and invoke modules as
`StandardSens.*` / `EnvelopeSens.*`, not `_4_OptSim.StandardSens.*`. If you run
one by hand, replicate that or the imports of `_shared` will fail.

## Visualizing a run

BobVis replays a run's 3D motion and records video of it. Full reference:
[`../_1_VisualSim/README.md`](../_1_VisualSim/README.md).

```bash
make visual-deps       # once: prebuilt wheels for the viewer, nothing compiles
make visual-demo       # synthetic scene, no OpenModelica build needed
make visual-maneuver   # VehicleSim transient: simulate with geometry captured, watch it drive
make visual-rig        # four-post rig: simulate with geometry captured, then watch it

make visual-export \
  VISUAL_CONFIG=_1_VisualSim/results/four_post_visual.yml \
  VISUAL_DATA=_1_VisualSim/results/four_post_visual.npz \
  VISUAL_OUTPUT=out.mp4 VISUAL_ARGS="--resolution 720p --speed 8"
```

The viewer runs on the host, unlike the rest of the stack: a containerised
window leaves its 3D viewport black under software GL. The simulation inside
`visual-rig` and `visual-maneuver` still goes through `$(RUN)`. Add `-video` to
any of these to render an MP4 instead of opening a window.

**A normal evaluation cannot feed the viewer.** Each one sets a
`variable_filter` naming only the scalars its metrics need, so the result CSV
carries no hardpoint positions — `make standard-eval-four-post` yields 45
columns of KnC numbers and nothing to draw. `make visual-capture` (which
`visual-rig` and `visual-maneuver` wrap) re-runs one evaluation —
`VISUAL_EVAL=four_post|transient|ramp_steer|steady_state` — asking for the
MultiBody frames as well, then writes a matched `.npz` and template into
`_1_VisualSim/results/`. The capture also keeps each tire's forces and records
the run's metrics CSV. The window then shows LLTD under each axle, a Tires tab
of friction circles, and a Metrics tab, and F1 lists the mouse and touchpad
controls. A scene captured before that has no Tires or Metrics tab until it is
re-captured. The templates in `_1_VisualSim/visual_templates/` are stale: they
name `vis*` signals no pinned model emits. See
[`../_1_VisualSim/README.md`](../_1_VisualSim/README.md).

## Testing

```bash
make ci      # lint + typecheck + test — the fast gate, matches GitHub Actions
```

The regression story has three tiers, and mixing them up is the common mistake:

| Target | Reruns simulations? | Use it for |
| --- | --- | --- |
| `make test` | No | Default fast gate. Checks current artifacts + physical invariants. |
| `make regression-invariants` | No | Artifact-only sanity check. **Not** proof a model change is safe. |
| `make regression-baseline` | **Yes** | The real check. Rebuilds, reruns all four studies, compares against `tests/regression_baselines/default_vehicle_standard.yml`. |

Full baselines are excluded from GitHub CI because they exceed hosted runner
limits. Run `make regression-baseline` locally before trusting a physics change.

Only update a baseline when behavior changed *intentionally* and you have
reviewed the regenerated reports — see [`CONTRIBUTING.md`](../CONTRIBUTING.md).

For a fast check of the DOE pipeline with no OpenModelica toolchain:

```bash
make opt-doe-smoke
```

CI runs lint, typecheck, and this DOE smoke natively for fast feedback, then
the full fast gate inside the Docker image.

## Cleaning

`make clean` only removes Python/tool caches. Generated workflow artifacts need
the specific targets (`clean-app`, `clean-standard`, `clean-envelope`,
`clean-opt`, `clean-visual`) or `clean-all`.

`clean-owned` exists because Docker-run workflows can leave root-owned files on
Linux hosts; it re-enters a no-network container to delete them. It no-ops if
the image isn't built.

## Deploy

`make deploy` builds a per-OS PyInstaller artifact into
`_0_Utils/deploy/dist/BobSim/`. It bundles the Python backend only — not
simulation executables, reports, or caches. Windows and macOS release assets
come from the `Release Builds` GitHub Actions workflow on a `v*` tag, not from a
local build. Never commit `.exe`/`.app`/`.zip`/`.tar.gz` outputs.
