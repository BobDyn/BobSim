# Contributing

BobSim changes should keep the default vehicle regressions meaningful. The
standard test entry point is:

```bash
make test
```

`make test` runs pytest with `BOBSIM_BASELINE_REGRESSION=1`. Pytest owns the
regression flow: it rebuilds and reruns the default StandardSim workflows,
checks that fresh report artifacts were written, verifies physical invariants,
and compares selected metrics against
`tests/regression_baselines/default_vehicle_standard.yml`.

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
did not regress.

## Updating Baselines Intentionally

Only update a baseline when the simulation behavior changed intentionally and
the new reports have been reviewed.

1. Run the full regression:

   ```bash
   make test
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

6. Rerun:

   ```bash
   make test
   ```

7. In the pull request, summarize:

   - which workflows moved,
   - why the movement is expected,
   - which baseline values or tolerances changed,
   - and that `make test` passed after the update.

Generated report artifacts should be produced by the workflow, not hand-edited.
If tracked report artifacts change, commit only the regenerated outputs that
correspond to the intentional baseline update.
