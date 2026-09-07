# Agent Notes

BobSim is the workflow layer over BobLib's Modelica vehicle physics. Read
[`docs/README.md`](docs/README.md) before non-trivial work.

## How to use `docs/`

Don't read the whole folder. Route by task:

| Task | Read |
| --- | --- |
| Anything non-trivial, first time in the repo | [`docs/architecture.md`](docs/architecture.md) |
| Running / building / testing something | [`docs/workflows.md`](docs/workflows.md) |
| Parameter sweeps, sensitivities, target-metrics → vehicle | [`docs/doe-reverse-engineering.md`](docs/doe-reverse-engineering.md) |
| Reduced 3/6/10/14DOF dynamics, QSS envelopes, BobLib correlation | [`docs/reduced-order-dynamics.md`](docs/reduced-order-dynamics.md) |
| QSS racing lines, speed profiles, and transient laps | [`docs/lap-time-simulation.md`](docs/lap-time-simulation.md) |
| Modelica missing, build fails, BobLib edits | [`docs/boblib-submodule.md`](docs/boblib-submodule.md) |
| Touching `_5_App/` | [`_5_App/README.md`](_5_App/README.md) — module-by-module ownership |
| Touching physics / regression baselines | [`CONTRIBUTING.md`](CONTRIBUTING.md) |
| Editing Modelica models | `_0_Utils/external/BobLib/AGENTS.md` (package boundary rules) |
| Reading/writing `vehicle.yml` geometry, importing SHARK data | [`docs/conventions.md`](docs/conventions.md) |
| Doing a repeated multi-step task by hand (SHARK import, baseline refresh) | [`skills/README.md`](skills/README.md) |

`docs/` explains *why* and how layers connect. The makefile and `make help` are
authoritative for *what commands exist* — prefer reading the makefile over
trusting a doc if they disagree, and fix the doc when they do.

When you add a doc, add a row to the table in `docs/README.md` and to the table
above. Keep the set small; a stale doc is worse than no doc.

## Before you start

1. `git submodule status` — a `+` or `-` prefix means BobLib is wrong and
   Modelica builds will fail confusingly. `make init` fixes the common case.
   See [`docs/boblib-submodule.md`](docs/boblib-submodule.md).
2. `make help` — the real target list.

## Repo rules

- **Layers are numbered `_0_` … `_5_`.** `_0_Utils` is shared foundation;
  `_5_App` is the browser entry point. Lower layers must not import from higher
  ones. Reuse `_0_Utils/plotting` and `_0_Utils/reporting` rather than calling
  matplotlib or building PDFs directly in a study.
- **Never commit generated content.** `Build/`, `BuildBobLib/`, `results/`,
  `generated_results/`, `population/`, `_5_App/user_data/`, and deploy outputs
  (`.exe`, `.app`, `.zip`, `.tar.gz`) are runtime artifacts. They are gitignored;
  keep it that way.
- **Never hand-edit generated Modelica records.** `BobLib/Records/VehicleDefn/*.mo`
  are written by `_5_App/modelica_generator.py`. Change `vehicle.yml` or the
  generator.
- **`vehicle.yml` and the BobLib record can drift.** BobSim's Python workflows
  read `vehicle.yml`; the Modelica entry points read checked-in BobLib records.
  If simulated numbers disagree with `vehicle.yml`, suspect an unregenerated
  record before suspecting physics.
- **Use `_0_Utils/vehicle_io.py` for paths** (`repo_root()`, `vehicle_yaml_path()`)
  instead of new `Path(__file__).parents[n]` chains.
- **BobLib changes are a separate repo.** They need a PR in `BobDyn/BobLib` plus
  a pin bump here — not an edit committed from inside the submodule directory.

## Common agent mistakes

- **`vehicle.yml` vs. the checked-in BobLib Modelica record can silently drift.**
  Python workflows read `vehicle.yml`; Modelica entry points read the generated
  `.mo` record. Editing `vehicle.yml` alone and expecting a Modelica-backed
  study (StandardSim, FourPostSim) to reflect it is the single most common
  mistake — regenerate via `_5_App/modelica_generator.py` first, or you'll be
  debugging "wrong" physics that are actually a stale record.
- **Z-dependent outputs can be silently withheld, not wrong.** After a SHARK
  import, roll-centre height/migration and four-post jacking metrics may come
  back empty rather than incorrect if the vertical datum couldn't be verified
  (`_0_Utils/shark_import.py:datum_gate`). Don't treat missing z-metrics as a
  bug before checking the datum sidecar — see
  [`docs/conventions.md`](docs/conventions.md#vertical-datum-z) and
  [`skills/shark-import/SKILL.md`](skills/shark-import/SKILL.md).

## Verifying a change

```bash
make ci          # lint + typecheck + test — the fast gate, matches GitHub CI
```

Do not claim a physics or model change is safe on `make ci` alone.
`make test` and `make regression-invariants` check *existing* artifacts; only
`make regression-baseline` reruns the simulations. Run it for any change to
BobLib, `vehicle.yml`, study configs, or the runners, and report honestly if you
could not (it needs OpenModelica and is slow).

`make ci` does catch a *stale* baseline: the baseline records the BobLib pin and
a digest of the inputs it was generated against, and a non-simulating test fails
when they drift. See [`CONTRIBUTING.md`](CONTRIBUTING.md) before editing that
`provenance` block — refreshing it to get a green run is how the baseline rotted
for 79 commits once already.

`make opt-doe-smoke` checks the DOE pipeline (config generation, record
sampling, variant writing) without an OpenModelica toolchain, so it runs on any
machine. Use it after touching `_4_OptSim` or the BobLib records it reads.

Most targets shell out to `docker compose` unless you are already inside the
container. `make app` and `deploy-*` are the exceptions and run on the host.

Paths that get written into configs, JSON payloads, or anything consumed on
another machine must be `as_posix()`, never `str(Path)` — native Windows
separators have broken the DOE config and the app's file APIs before.

## Baselines

Update `tests/regression_baselines/default_vehicle_standard.yml` only when
behavior changed intentionally *and* the regenerated reports were reviewed.
Never update a baseline to make a failing test pass — that is the one change
that silently destroys the value of this repo's test suite. Follow the procedure
in [`CONTRIBUTING.md`](CONTRIBUTING.md).
