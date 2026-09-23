"""Correlate reduced instantaneous suspension links with BobLib FourPost output."""

from __future__ import annotations

import argparse
import csv
import json
from pathlib import Path
from typing import Mapping

from _0_Utils.dyn_py import DoubleWishboneInstantLinks, load_reduced_vehicle_parameters


BOBLIB_METRIC_NAMES = {
    "front_longitudinal": "avg_longitudinal_jacking_coeff_front",
    "rear_longitudinal": "avg_longitudinal_jacking_coeff_rear",
    "front_net_lateral": "avg_lateral_jacking_coeff_front",
    "rear_net_lateral": "avg_lateral_jacking_coeff_rear",
}


def load_metrics(path: str | Path) -> dict[str, float]:

    metrics: dict[str, float] = {}
    with Path(path).open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            try:
                metrics[str(row["metric"])] = float(row["value"])
            except (KeyError, TypeError, ValueError):
                continue
    return metrics


def correlate_instant_links(
    links: DoubleWishboneInstantLinks,
    boblib_metrics: Mapping[str, float],
) -> dict[str, dict[str, float]]:
    """Compare nominal link coefficients with BobLib force-pulse reactions."""

    front_long, rear_long = links.axle_longitudinal_coefficients
    front_lateral, rear_lateral = links.axle_net_lateral_coefficients
    reduced = {
        "front_longitudinal": front_long,
        "rear_longitudinal": rear_long,
        "front_net_lateral": front_lateral,
        "rear_net_lateral": rear_lateral,
    }
    comparison: dict[str, dict[str, float]] = {}
    for name, reduced_value in reduced.items():
        metric_name = BOBLIB_METRIC_NAMES[name]
        if metric_name not in boblib_metrics:
            raise KeyError(f"BobLib FourPost metrics are missing {metric_name!r}.")
        reference = float(boblib_metrics[metric_name])
        absolute_error = reduced_value - reference
        comparison[name] = {
            "dyn_py": reduced_value,
            "boblib": reference,
            "absolute_error": absolute_error,
            "relative_error": (
                absolute_error / reference if abs(reference) > 1e-12 else float("nan")
            ),
        }
    return comparison


def _parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--metrics",
        type=Path,
        default=Path("_3_StandardSim/generated_results/four_post_eval_report_metrics.csv"),
    )
    parser.add_argument("--vehicle", type=Path)
    return parser.parse_args()


def main() -> None:
    args = _parse_args()
    parameters = load_reduced_vehicle_parameters(
        args.vehicle,
        four_post_metrics_path=args.metrics,
    )
    comparison = correlate_instant_links(
        parameters.double_wishbone.instant_links_at([0.0, 0.0, 0.0, 0.0]),
        load_metrics(args.metrics),
    )
    print(json.dumps(comparison, indent=2, sort_keys=True))


if __name__ == "__main__":
    main()
