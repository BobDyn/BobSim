# Contributing

BobSim changes should keep the default vehicle regressions meaningful. The
standard fast test entry point is:

```bash
make test
```

`make test` runs pytest without refreshing full StandardSim simulations. It
checks the current report artifacts, verifies physical invariants, and skips the
baseline value comparison unless baseline refresh is explicitly enabled.

## Regression Scope

The default StandardSim baseline covers:

- `RampSteerEval`
- `SteadyStateEval`
- `TransientEval`
- `FourPostEval`

The baseline intentionally records high-signal metrics rather than every row in
each report CSV. Count/configuration metrics use exact or very tight tolerances.
Fit-derived response metrics use engineering tolerances wide enough to avoid
blocking on numerical noise, but narrow enough to catch meaningful model drift.

`make regression-invariants` is available for a quick artifact-only check. It
does not rerun simulations and should not be used as proof that a model change
did not regress. `make regression-baseline` is the explicit full-simulation path:
it rebuilds and reruns the default StandardSim workflows, checks that fresh
report artifacts were written, and compares selected metrics against
`tests/regression_baselines/default_vehicle_standard.yml`.

## Baseline Provenance

The baseline records the BobLib pin and a digest of every result-affecting input
(`vehicle.yml` plus each study's `simulation`, `sweep`, and `fit` sections) under
`provenance`. `test_baseline_provenance_matches_simulation_inputs` checks it on
every PR and needs no OpenModelica, so a stale baseline fails in seconds instead
of going unnoticed.

`execution`, `report`, and `plots` are excluded from the digest: worker counts and
plot titles cannot move a simulated number.

When that test fails you have two honest options. Either run
`make regression-baseline` and refresh, or, if you have confirmed the change
cannot affect physics (a BobLib bump touching only lint config, say), update
`provenance` deliberately in the same commit and say why in the pull request.
Never update it just to get a green run.

## Updating Baselines Intentionally

Only update a baseline when the simulation behavior changed intentionally and
the new reports have been reviewed.

1. Run the full regression explicitly:

   ```bash
   make regression-baseline
   ```

2. Inspect the regenerated artifacts under `_3_StandardSim/results/`:

   - `*_report_metrics.csv`
   - `*_report.pdf`

3. Decide whether the metric movement is expected. A baseline update is
   appropriate for intentional model, tire, suspension, controller, or report
   methodology changes. It is not appropriate for hiding a failing setup check,
   unexplained convergence change, or accidental workflow break.

4. Update `tests/regression_baselines/default_vehicle_standard.yml` from the
   regenerated metrics CSVs. Keep the same metric names unless the report schema
   intentionally changed.

5. Choose tolerances deliberately:

   - Counts, selected velocities, and configuration values should remain exact
     or nearly exact.
   - Static setup checks should remain tight.
   - Primary response metrics may use small absolute or relative tolerances.
   - Noisy endpoint or fit-derived metrics may use broader tolerances, but the
     pull request should explain why.
   - Do not widen a tolerance just to make an unexplained failure pass.

6. Rerun the fast gate and, when simulation outputs changed, the full baseline:

   ```bash
   make test
   make regression-baseline
   ```

7. In the pull request, summarize:

   - which workflows moved,
   - why the movement is expected,
   - which baseline values or tolerances changed,
   - and that `make test` and `make regression-baseline` passed after the update.

Generated report artifacts should be produced by the workflow, not hand-edited.
If tracked report artifacts change, commit only the regenerated outputs that
correspond to the intentional baseline update.
