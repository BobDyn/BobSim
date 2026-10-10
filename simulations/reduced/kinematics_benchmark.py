"""Measure kinematic lookup accuracy and runtime against in-loop solves."""

from __future__ import annotations

import argparse
from dataclasses import replace
import json
from pathlib import Path
from time import perf_counter
from typing import Any

import numpy as np

from engines.kinpy import create_kinematics
from engines.dynpy import (
    ModelInputs,
    create_model,
    load_reduced_vehicle_parameters,
)
from common.vehicle_io import load_yaml, repo_root, vehicle_yaml_path


DEFAULT_COUNTS = (9, 17, 33, 49, 65)
QUERY_JOUNCE_M = np.asarray(
    [
        (-0.043, -0.031, -0.027, -0.019),
        (-0.021, -0.011, -0.007, -0.003),
        (0.004, 0.009, 0.014, 0.019),
        (0.023, 0.031, 0.038, 0.047),
    ],
    dtype=float,
)


def benchmark_kinematics(
    *,
    vehicle_path: str | Path | None = None,
    sample_counts: tuple[int, ...] = DEFAULT_COUNTS,
    lookup_repeats: int = 1_000,
    model_repeats: int = 200,
) -> dict[str, Any]:
    """Return lookup errors and timing relative to exact nonlinear kinematics."""

    path = Path(vehicle_path) if vehicle_path is not None else vehicle_yaml_path()
    vehicle = load_yaml(path)
    nonlinear = create_kinematics(vehicle, mode="nonlinear")

    exact_start = perf_counter()
    exact_states = [nonlinear.at(jounce) for jounce in QUERY_JOUNCE_M]
    exact_state_ms = 1_000.0 * (perf_counter() - exact_start) / len(QUERY_JOUNCE_M)

    base_parameters = load_reduced_vehicle_parameters(path)
    nonlinear_parameters = replace(base_parameters, kinematics=nonlinear)
    nonlinear_model_ms = _model_evaluation_ms(
        nonlinear_parameters,
        repeats=max(min(model_repeats // 20, 10), 3),
    )

    rows: list[dict[str, float | int]] = []
    for sample_count in sample_counts:
        build_start = perf_counter()
        lookup = create_kinematics(vehicle, sample_count=sample_count)
        build_s = perf_counter() - build_start

        errors = [
            _state_errors(lookup.at(jounce), exact)
            for jounce, exact in zip(QUERY_JOUNCE_M, exact_states)
        ]
        lookup_start = perf_counter()
        for repeat in range(lookup_repeats):
            lookup.at(QUERY_JOUNCE_M[repeat % len(QUERY_JOUNCE_M)])
        lookup_state_us = 1e6 * (perf_counter() - lookup_start) / lookup_repeats

        parameters = replace(base_parameters, kinematics=lookup)
        rows.append(
            {
                "sample_count": sample_count,
                "build_s": build_s,
                "lookup_state_us": lookup_state_us,
                "model_evaluation_ms": _model_evaluation_ms(
                    parameters,
                    repeats=model_repeats,
                ),
                "max_contact_patch_error_um": 1e6
                * max(error["contact_patch_m"] for error in errors),
                "max_camber_error_deg": np.degrees(
                    max(error["camber_rad"] for error in errors)
                ),
                "max_toe_error_deg": np.degrees(
                    max(error["toe_rad"] for error in errors)
                ),
                "max_instant_link_error": max(
                    error["instant_link"] for error in errors
                ),
            }
        )

    return {
        "vehicle": path.as_posix(),
        "query_count": len(QUERY_JOUNCE_M),
        "nonlinear_state_ms": exact_state_ms,
        "nonlinear_model_evaluation_ms": nonlinear_model_ms,
        "lookup_results": rows,
    }


def _state_errors(candidate: Any, reference: Any) -> dict[str, float]:
    return {
        "contact_patch_m": float(
            np.max(
                np.abs(
                    candidate.contact_patch_offsets_m
                    - reference.contact_patch_offsets_m
                )
            )
        ),
        "camber_rad": float(np.max(np.abs(candidate.camber_rad - reference.camber_rad))),
        "toe_rad": float(np.max(np.abs(candidate.toe_rad - reference.toe_rad))),
        "instant_link": float(
            np.max(
                np.abs(
                    candidate.instant_links.coefficient_matrix
                    - reference.instant_links.coefficient_matrix
                )
            )
        ),
    }


def _model_evaluation_ms(parameters: Any, *, repeats: int) -> float:
    model = create_model(14, parameters)
    state = model.initial_state(20.0)
    inputs = ModelInputs(steering_rad=0.03)
    model.evaluate(state, inputs)
    start = perf_counter()
    for _ in range(repeats):
        model.evaluate(state, inputs)
    return 1_000.0 * (perf_counter() - start) / repeats


def _parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--vehicle", type=Path)
    parser.add_argument("--sample-counts", type=int, nargs="+", default=DEFAULT_COUNTS)
    parser.add_argument(
        "--output",
        type=Path,
        default=repo_root() / "temp/kinematics_benchmark/summary.json",
    )
    return parser.parse_args()


def main() -> None:
    args = _parse_args()
    summary = benchmark_kinematics(
        vehicle_path=args.vehicle,
        sample_counts=tuple(args.sample_counts),
    )
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(
        json.dumps(summary, indent=2, sort_keys=True) + "\n",
        encoding="utf-8",
    )
    print(json.dumps(summary, indent=2, sort_keys=True))
    print(f"Kinematics benchmark written: {args.output.as_posix()}")


if __name__ == "__main__":
    main()
