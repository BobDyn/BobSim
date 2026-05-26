"""Run the EnvelopeSim sensitivity DOE."""

from __future__ import annotations

import time

from pipeline.envelope_sensitivity import run_envelope_sensitivities
from pipeline.orchestration import (
    POPULATION_DIR,
    RESULTS_DIR,
    elapsed,
    prepare_variants,
    stage,
    write_variant_table,
)


def run() -> None:
    t_total = time.time()

    stage(1, 3, "Sampling and generating vehicle variants")
    t = time.time()
    variants = prepare_variants(force_rebuild=True)
    print(f"Prepared {len(variants)} variants ({elapsed(t)})")

    stage(2, 3, "Writing EnvelopeSim sensitivity inputs")
    output_path = RESULTS_DIR / "envelope_sensitivity_inputs.csv"
    input_df = write_variant_table(variants, output_path)
    print(f"Output: {output_path}")

    stage(3, 3, "Running EnvelopeSim sensitivities")
    t = time.time()
    metrics_df = run_envelope_sensitivities(
        POPULATION_DIR,
        RESULTS_DIR / "envelope_sensitivities",
    )
    print(f"Done ({elapsed(t)})")
    print(f"Total {elapsed(t_total)}")
    print(input_df.to_string())
    print(metrics_df.to_string())


if __name__ == "__main__":
    run()
