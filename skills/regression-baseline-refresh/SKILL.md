# Skill: refresh the regression baseline

**Use when:** simulation behavior changed *intentionally* (model, tire,
suspension, controller, or report methodology) and
`tests/regression_baselines/default_vehicle_standard.yml` now needs updating
to match — not when a test is failing and you want it to pass.

**Underlying tooling:** `make regression-baseline`, `make test`. Full
authoritative procedure and PR expectations:
[`CONTRIBUTING.md`](../../CONTRIBUTING.md#updating-baselines-intentionally) — this
skill is the condensed operational sequence; defer to CONTRIBUTING.md if they
ever disagree.

## Steps

1. **Rerun the full regression** (rebuilds and reruns all four StandardSim
   studies — slow, needs OpenModelica):

   ```bash
   make regression-baseline
   ```

2. **Inspect the regenerated artifacts** under `_3_StandardSim/results/`:
   - `*_report_metrics.csv`
   - `*_report.pdf`

3. **Decide whether the metric movement is expected.** A baseline update is
   appropriate for intentional model/tire/suspension/controller/report
   changes. It is **not** appropriate for hiding a failing setup check, an
   unexplained convergence change, or an accidental workflow break — if you
   can't explain *why* a number moved, stop and investigate before touching
   the baseline file.

4. **Update the baseline** from the regenerated metrics CSVs. Keep the same
   metric names unless the report schema intentionally changed. Choose
   tolerances deliberately:
   - Counts, selected velocities, configuration values: exact or nearly exact.
   - Static setup checks: tight.
   - Primary response metrics: small absolute/relative tolerances.
   - Noisy endpoint or fit-derived metrics: broader tolerances allowed, but
     the PR must explain why.
   - Never widen a tolerance just to make an unexplained failure pass.

5. **Rerun the fast gate and the full baseline** to confirm the update holds:

   ```bash
   make test
   make regression-baseline
   ```

6. **In the PR, summarize:** which workflows moved, why the movement is
   expected, which baseline values/tolerances changed, and that both `make
   test` and `make regression-baseline` passed after the update.

Generated report artifacts should come from the workflow, never be
hand-edited. If tracked report artifacts change, commit only the regenerated
outputs corresponding to the intentional update.
