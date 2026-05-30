"""Run the EnvelopeSim sensitivity DOE."""

from __future__ import annotations

import time

from _shared.console import elapsed, stage
from _shared.plot_sensitivity_tornado import make_tornado_pdf
from EnvelopeSens._pipeline.plot_envelope_sensitivities import (
    TORNADO_METRICS,
    make_pdf as make_envelope_pdf,
)
from EnvelopeSens._pipeline.sensitivity import (
    BUILD_DIR,
    RESULTS_DIR,
    build_envelope_variants,
    compute_relative_sensitivities,
    run_envelope_sensitivities,
    write_envelope_variant_table,
)

LEGACY_PUBLIC_ARTIFACTS = [
    "envelope_sensitivity_inputs.csv",
    "envelope_sensitivity_scope.csv",
    "envelope_relative_sensitivities.csv",
    "envelope_sensitivity_tornado.pdf",
    "envelope_sensitivity_viz.pdf",
]


def _remove_legacy_public_artifacts() -> None:
    for name in LEGACY_PUBLIC_ARTIFACTS:
        path = RESULTS_DIR / name
        if path.exists():
            path.unlink()


def run() -> None:
    t_total = time.time()

    stage(1, 5, "Generating EnvelopeSim variants")
    t = time.time()
    variants, scope_df = build_envelope_variants()
    print(f"Prepared {len(variants)} EnvelopeSim variants ({elapsed(t)})")

    stage(2, 5, "Writing EnvelopeSim sensitivity inputs")
    inputs_path = BUILD_DIR / "envelope_sensitivity_inputs.csv"
    scope_path = BUILD_DIR / "envelope_sensitivity_scope.csv"
    input_df = write_envelope_variant_table(variants, inputs_path)
    scope_df.to_csv(scope_path, index=False)
    print(f"Inputs: {inputs_path}")
    print(f"Scope:  {scope_path}")

    stage(3, 5, "Running EnvelopeSim sensitivities")
    t = time.time()
    raw_dir = BUILD_DIR / "envelope_sensitivities"
    metrics_df = run_envelope_sensitivities(variants, raw_dir)
    metrics_path = raw_dir / "envelope_sensitivity_metrics.csv"
    print(f"Metrics: {metrics_path}")
    print(f"Done ({elapsed(t)})")

    stage(4, 5, "Writing relative sensitivities")
    relative_path = BUILD_DIR / "envelope_relative_sensitivities.csv"
    relative_df = compute_relative_sensitivities(input_df, metrics_df, relative_path)
    print(f"Relative sensitivities: {relative_path}")
    print(f"Rows: {len(relative_df)}")

    stage(5, 5, "Plotting EnvelopeSim sensitivity reports")
    joined = input_df.merge(metrics_df, on="variant", how="inner")
    public_results_path = RESULTS_DIR / "envelope_sensitivity_results.csv"
    RESULTS_DIR.mkdir(parents=True, exist_ok=True)
    _remove_legacy_public_artifacts()
    joined.to_csv(public_results_path, index=False)
    print(f"Public results CSV: {public_results_path}")

    tornado_path = BUILD_DIR / "envelope_sensitivity_tornado.pdf"
    make_tornado_pdf(
        joined,
        input_df,
        tornado_path,
        metrics=TORNADO_METRICS,
        top_n=15,
        x_scale="percent",
        min_plot_span=0.05,
        min_span_fraction=0.01,
    )
    make_envelope_pdf(
        inputs_path,
        metrics_path,
        raw_dir,
        RESULTS_DIR / "envelope_sensitivity_report.pdf",
    )

    print(f"Total {elapsed(t_total)}")
    print(input_df.to_string())
    print(metrics_df.to_string())


if __name__ == "__main__":
    run()
