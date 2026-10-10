"""Run the refined response-surface DOE selected from pre-screen sensitivities."""

from __future__ import annotations

import argparse
import time
from pathlib import Path

from _shared.console import elapsed, stage
from StandardSens.pipeline.aggregator import aggregate
from StandardSens.pipeline.build_pipeline import build_all
from StandardSens.pipeline.orchestration import (
    AGGREGATOR_CONFIG,
    ARCHITECTURE_CONFIG,
    COMPILER_CONFIG,
)
from StandardSens.pipeline.refined_response_surface import (
    DEFAULT_BASE_DOE_CONFIG,
    DEFAULT_COEFFICIENTS_CSV,
    DEFAULT_EXCLUDE_INPUTS,
    DEFAULT_INPUTS_CSV,
    DEFAULT_REFINED_CONFIG,
    DEFAULT_REFINED_POPULATION,
    DEFAULT_RESULTS_TABLE,
    DEFAULT_SELECTION_CSV,
    DEFAULT_SENSITIVITY_RESULTS,
    DEFAULT_SURFACE_PDF,
    DEFAULT_SURFACE_RESULTS_CSV,
    build_refined_config,
    clean_population,
    load_table,
    load_yaml,
    prepare_refined_variants,
    response_surface_pairs,
    rebase_path_field,
    select_parameters,
    write_selection,
    write_yaml_if_changed,
)
from StandardSens.pipeline.response_surfaces import make_pdf


def _parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Select influential sensitivity inputs and run a refined "
            "response-surface DOE."
        )
    )
    parser.add_argument("--sensitivity-results", type=Path, default=DEFAULT_SENSITIVITY_RESULTS)
    parser.add_argument("--base-doe-config", type=Path, default=DEFAULT_BASE_DOE_CONFIG)
    parser.add_argument("--refined-config", type=Path, default=DEFAULT_REFINED_CONFIG)
    parser.add_argument("--population-dir", type=Path, default=DEFAULT_REFINED_POPULATION)
    parser.add_argument("--selection-output", type=Path, default=DEFAULT_SELECTION_CSV)
    parser.add_argument("--inputs-output", type=Path, default=DEFAULT_INPUTS_CSV)
    parser.add_argument("--results-output", type=Path, default=DEFAULT_RESULTS_TABLE)
    parser.add_argument("--csv-output", type=Path, default=DEFAULT_SURFACE_RESULTS_CSV)
    parser.add_argument("--surface-output", type=Path, default=DEFAULT_SURFACE_PDF)
    parser.add_argument("--coefficients-output", type=Path, default=DEFAULT_COEFFICIENTS_CSV)
    parser.add_argument("--standard", default="SteadyStateEval")
    parser.add_argument("--metrics", nargs="*")
    parser.add_argument("--top-k", type=int, default=2)
    parser.add_argument("--grid-levels", type=int, default=5)
    parser.add_argument("--baseline-variant", default="variant_0000")
    parser.add_argument(
        "--exclude-input",
        action="append",
        default=None,
        help=(
            "Input column glob to exclude from selection. "
            "Defaults to '*.spring_rate_n_per_m'."
        ),
    )
    parser.add_argument(
        "--force-rebuild",
        action="store_true",
        help="Discard the refined population before generating variants.",
    )
    parser.add_argument(
        "--select-only",
        action="store_true",
        help="Only write selected parameters and the refined DOE config.",
    )
    parser.add_argument(
        "--skip-build",
        action="store_true",
        help="Aggregate and plot existing refined population results.",
    )
    return parser.parse_args()


def run() -> None:
    args = _parse_args()
    t_total = time.time()
    total_stages = 2 if args.select_only else 5

    stage(1, total_stages, "Selecting response-surface parameters from tornado effects")
    t = time.time()
    sensitivity_df = load_table(args.sensitivity_results)
    base_doe_config = load_yaml(args.base_doe_config)
    exclude_inputs = (
        DEFAULT_EXCLUDE_INPUTS
        if args.exclude_input is None
        else tuple(args.exclude_input)
    )
    selection = select_parameters(
        sensitivity_df,
        base_doe_config,
        metrics=args.metrics,
        standard=args.standard,
        top_k=args.top_k,
        baseline_variant=args.baseline_variant,
        exclude_inputs=exclude_inputs,
    )
    write_selection(selection, args.selection_output)

    refined_config = build_refined_config(
        base_doe_config,
        selection,
        grid_levels=args.grid_levels,
        top_k=args.top_k,
    )
    rebase_path_field(
        refined_config,
        "baseline_mo",
        source_config_path=args.base_doe_config,
        target_config_path=args.refined_config,
    )
    config_changed = write_yaml_if_changed(args.refined_config, refined_config)
    if config_changed:
        clean_population(args.population_dir)

    pairs = response_surface_pairs(selection, top_k=args.top_k)
    print(f"Selected {len(pairs)} response-surface pair(s):")
    for pair in pairs:
        x_col, y_col = pair["variables"]
        print(f"  {pair['metric']}: {x_col} x {y_col}")
    print(f"Selection CSV: {args.selection_output}")
    print(f"Refined config: {args.refined_config}")
    print(f"Done ({elapsed(t)})")

    if args.select_only:
        stage(2, total_stages, "Complete")
        print(f"Total {elapsed(t_total)}")
        return

    stage(2, total_stages, "Sampling and generating refined variants")
    t = time.time()
    variants = prepare_refined_variants(
        args.refined_config,
        args.population_dir,
        args.inputs_output,
        force_rebuild=args.force_rebuild,
    )
    print(f"Prepared {len(variants)} refined variants ({elapsed(t)})")
    print(f"Inputs CSV: {args.inputs_output}")

    if not args.skip_build:
        stage(3, total_stages, "Building and simulating refined variants")
        t = time.time()
        build_all(
            args.population_dir,
            COMPILER_CONFIG,
            doe_config_path=args.refined_config,
            architecture_config_path=ARCHITECTURE_CONFIG,
        )
        print(f"Done ({elapsed(t)})")
    else:
        stage(3, total_stages, "Skipping build/simulate")

    stage(4, total_stages, "Aggregating refined metrics")
    t = time.time()
    df = aggregate(
        args.population_dir,
        args.refined_config,
        AGGREGATOR_CONFIG,
        output_path=args.results_output,
    )
    args.csv_output.parent.mkdir(parents=True, exist_ok=True)
    df.to_csv(args.csv_output, index=False)
    print(f"Public results CSV: {args.csv_output}")
    print(f"Done ({elapsed(t)})")

    stage(5, total_stages, "Fitting and plotting response surfaces")
    t = time.time()
    make_pdf(
        df,
        args.surface_output,
        pairs=pairs,
        baseline_variant=args.baseline_variant,
        coefficients_output=args.coefficients_output,
    )
    print(f"Done ({elapsed(t)})")

    print(f"\nTotal {elapsed(t_total)}")


if __name__ == "__main__":
    run()
