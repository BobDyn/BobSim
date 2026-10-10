"""Run the StandardSim pre-screen sensitivity DOE end to end."""

from __future__ import annotations

import time
from pathlib import Path

from _shared.console import elapsed, stage
from _shared.plot_sensitivity_tornado import (
    DEFAULT_STANDARD_EXCLUDE_INPUTS,
    DEFAULT_STANDARD_METRICS,
    make_tornado_pdf,
)
from StandardSens.pipeline.aggregator import aggregate
from StandardSens.pipeline.build_pipeline import build_all
from StandardSens.pipeline.orchestration import (
    AGGREGATOR_CONFIG,
    ARCHITECTURE_CONFIG,
    COMPILER_CONFIG,
    DOE_CONFIG,
    prepare_variants,
    write_variant_table,
)


STANDARD_DIR = Path(__file__).resolve().parent
OPTSIM_DIR = STANDARD_DIR.parent
BUILD_DIR = OPTSIM_DIR / "Build" / "StandardSens"
POPULATION_DIR = BUILD_DIR / "population"
RESULTS_DIR = OPTSIM_DIR / "results"


def run() -> None:
    t_total = time.time()

    stage(1, 5, "Sampling and generating vehicle variants")
    t = time.time()
    variants = prepare_variants(force_rebuild=False, population_dir=POPULATION_DIR)
    inputs_path = BUILD_DIR / "standard_sensitivity_inputs.csv"
    input_df = write_variant_table(variants, inputs_path)
    print(f"Prepared {len(variants)} variants ({elapsed(t)})")
    print(f"Inputs: {inputs_path}")

    stage(2, 5, "Building and simulating StandardSim variants")
    t = time.time()
    build_all(
        POPULATION_DIR,
        COMPILER_CONFIG,
        doe_config_path=DOE_CONFIG,
        architecture_config_path=ARCHITECTURE_CONFIG,
    )
    print(f"Done ({elapsed(t)})")

    stage(3, 5, "Aggregating StandardSim metrics")
    t = time.time()
    df = aggregate(
        POPULATION_DIR,
        DOE_CONFIG,
        AGGREGATOR_CONFIG,
        output_path=BUILD_DIR / "standard_sensitivity_results.parquet",
    )
    print(f"Done ({elapsed(t)})")

    stage(4, 5, "Plotting StandardSim tornado diagrams")
    t = time.time()
    standard = "SteadyStateEval"
    prefix = f"{standard}_"
    metric_columns = {
        f"{prefix}{metric}": metric
        for metric in DEFAULT_STANDARD_METRICS
        if f"{prefix}{metric}" in df.columns
    }
    metrics_df = df[["variant", *metric_columns.keys()]].rename(columns=metric_columns)
    joined = input_df.merge(metrics_df, on="variant", how="inner")
    RESULTS_DIR.mkdir(parents=True, exist_ok=True)
    public_results_path = RESULTS_DIR / "standard_sensitivity_results.csv"
    joined.to_csv(public_results_path, index=False)
    print(f"Public results CSV: {public_results_path}")

    output_path = RESULTS_DIR / "standard_sensitivity_report.pdf"
    plot_metrics = [
        metric for metric in DEFAULT_STANDARD_METRICS if metric in metrics_df.columns
    ]
    if plot_metrics:
        make_tornado_pdf(
            joined,
            input_df,
            output_path,
            metrics=plot_metrics,
            x_scale="percent",
            exclude_inputs=DEFAULT_STANDARD_EXCLUDE_INPUTS,
            include_pearson_table=True,
            pearson_title="Pearson Correlation to StandardSim Responses",
        )
    else:
        print("Skipping tornado plot: no matching StandardSim metrics were aggregated.")
    print(f"Done ({elapsed(t)})")

    stage(5, 5, "Complete")
    print(f"Total {elapsed(t_total)}")
    print(df.to_string())


if __name__ == "__main__":
    run()
