"""Solve for the setup that hits target SteadyStateEval metrics.

    make opt-solve TARGETS="understeer_gradient_deg_per_g=0.6 roll_gradient_deg_per_g=0.85"

Where `opt-search` looks up the nearest vehicle in a finished sweep, this solves
for the setup directly and simulates the answer before returning it. See
`pipeline/solver.py` for the method and `pipeline/evaluator.py` for why most
evaluations need no compile.
"""

from __future__ import annotations

import argparse
import json
from pathlib import Path
import sys
import time
from typing import Any

import yaml

from _shared.console import elapsed
from StandardSens.pipeline.evaluator import DEFAULT_SOLVE_DIR, SteadyStateEvaluator
from StandardSens.pipeline.solver import Knob, SolveResult, solve, star_design

STANDARD_DIR = Path(__file__).resolve().parent
DEFAULT_CONFIG = STANDARD_DIR / "configs/solve_config.yaml"
ARCHITECTURE_CONFIG = STANDARD_DIR / "configs/vehicle_architecture.yaml"
METRIC_PREFIX = "SteadyStateEval_"
SETUP_SCOPE = "setup"


def parse_targets(pairs: list[str]) -> dict[str, float]:
    """Parse METRIC=VALUE pairs, accepting the aggregated table's prefixed names."""
    targets: dict[str, float] = {}
    for pair in pairs:
        name, sep, raw = pair.partition("=")
        if not sep:
            raise ValueError(f"Target must be METRIC=VALUE, got {pair!r}")
        try:
            targets[name.strip().removeprefix(METRIC_PREFIX)] = float(raw)
        except ValueError:
            raise ValueError(f"Target value must be a number, got {raw!r}") from None
    if not targets:
        raise ValueError("At least one METRIC=VALUE target is required")
    return targets


def setup_scoped_paths(architecture_config_path: Path = ARCHITECTURE_CONFIG) -> set[str]:
    cfg = yaml.safe_load(architecture_config_path.read_text())
    variables = (cfg.get("sweep") or {}).get("variables") or []
    return {v["path"] for v in variables if v.get("scope") == SETUP_SCOPE}


def build_knobs(
    paths: list[str],
    variables: dict[str, dict[str, Any]],
    baseline: dict[str, float],
    setup_paths: set[str],
) -> list[Knob]:
    knobs = []
    for path in paths:
        if path not in variables:
            raise KeyError(f"Knob {path!r} is not a swept variable in vehicle_architecture.yaml")
        if path not in setup_paths:
            raise ValueError(
                f"Knob {path!r} is not tagged `scope: setup`. The solver answers 'what do I "
                "set on this car', so it only turns parameters that can be set on a built "
                "car. Conditions such as the driver belong in vehicle.yml, where they are "
                "compiled into the baseline."
            )
        spec = variables[path]
        lower, upper = (float(b) for b in spec["range"])
        knobs.append(
            Knob(
                path=path,
                lower=lower,
                upper=upper,
                baseline=min(max(float(baseline[path]), lower), upper),
                values=tuple(float(v) for v in spec.get("values", ())),
            )
        )
    return knobs


def resolve_tolerances(targets: dict[str, float], config: dict[str, Any]) -> dict[str, float]:
    listed = config.get("tolerances") or {}
    fraction = float(config.get("default_tolerance_fraction", 0.05))
    tolerances = {}
    for metric, target in targets.items():
        if metric in listed:
            tolerances[metric] = float(listed[metric])
        elif target != 0.0:
            tolerances[metric] = fraction * abs(target)
        else:
            raise ValueError(
                f"No tolerance configured for {metric!r} and its target is 0, so a "
                "fractional default is meaningless. Add it under `tolerances:`."
            )
    return tolerances


def format_result(result: SolveResult, labels: dict[str, str]) -> str:
    lines = [f"\nStatus: {result.status.upper()}  ({result.n_simulated} evaluations)"]
    if result.message:
        lines.append(result.message)

    lines.append("\nSetup:")
    width = max(len(labels.get(k.path, k.path)) for k in result.knobs)
    for knob in result.knobs:
        value = result.solution[knob.path]
        change = value - knob.baseline
        note = "  <- at range limit" if knob.path in result.at_bound else ""
        if knob.values and not any(abs(value - v) < 1e-9 for v in knob.values):
            note += "  (no such part)"
        ideal = result.ideal[knob.path]
        ideal_note = f"   ideal {ideal:.6g}" if knob.values and abs(ideal - value) > 1e-9 else ""
        lines.append(
            f"  {labels.get(knob.path, knob.path):<{width}}  {knob.baseline:>12.6g} -> "
            f"{value:>12.6g}  ({change:+.4g}){ideal_note}{note}"
        )

    lines.append("\nMetrics (simulated at the setup above):")
    width = max(len(m) for m in result.targets)
    for metric, target in result.targets.items():
        achieved = result.achieved[metric]
        tolerance = result.tolerances[metric]
        verdict = "ok" if abs(achieved - target) <= tolerance else "MISS"
        lines.append(
            f"  {metric:<{width}}  target {target:>9.4f}  achieved {achieved:>9.4f}  "
            f"error {achieved - target:+.4f}  (tol {tolerance:g})  {verdict}"
        )
    return "\n".join(lines)


def run(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--targets", nargs="+", required=True, metavar="METRIC=VALUE")
    parser.add_argument("--knobs", nargs="+", metavar="PATH", help="override the configured knobs")
    parser.add_argument("--config", type=Path, default=DEFAULT_CONFIG)
    parser.add_argument("--solve-dir", type=Path, default=DEFAULT_SOLVE_DIR)
    parser.add_argument("--plan", action="store_true", help="print the cost and exit")
    args = parser.parse_args(argv)

    config = yaml.safe_load(args.config.read_text())
    targets = parse_targets(args.targets)
    tolerances = resolve_tolerances(targets, config)
    evaluation = config.get("evaluation") or {}

    evaluator = SteadyStateEvaluator(
        runtime_paths=set(config.get("runtime_override") or ()),
        test_matrix=config["test_matrix"],
        solve_dir=args.solve_dir,
        case_workers=int(evaluation.get("case_workers", 4)),
        parallel_evaluations=int(evaluation.get("parallel_evaluations", 3)),
        timeout_s=int(evaluation.get("timeout_s", 1800)),
    )
    knobs = build_knobs(
        list(args.knobs or config["knobs"]),
        evaluator.variables,
        evaluator.baseline,
        setup_scoped_paths(),
    )
    labels = {k.path: str(evaluator.variables[k.path].get("label", k.path)) for k in knobs}
    step_fraction = float(config.get("star_step_fraction", 0.5))

    _, _, points = star_design(knobs, step_fraction)
    star = [dict(zip((k.path for k in knobs), map(float, p), strict=True)) for p in points]
    cost = evaluator.plan(star)
    slow = [k.path for k in knobs if k.path not in evaluator.runtime_paths]
    print(
        f"Star design: {cost['evaluations']} evaluations for {len(knobs)} knob(s) — "
        f"{cost['cached_evaluations']} cached, {cost['compiles_needed']} compile(s) needed."
    )
    if slow:
        print(
            "  Compile-only knobs (each distinct value is its own executable, and so is "
            f"each verification): {', '.join(slow)}"
        )
    if args.plan:
        return 0

    started = time.time()
    result = solve(
        knobs,
        targets,
        tolerances,
        evaluator,
        regularization=float(config.get("regularization", 0.01)),
        step_fraction=step_fraction,
        max_verifications=int(config.get("max_verifications", 4)),
        snap_discrete=bool(config.get("snap_discrete", True)),
    )
    print(format_result(result, labels))
    print(f"\nTotal {elapsed(started)}")

    output = evaluator.solve_dir / "last_result.json"
    output.write_text(
        json.dumps(
            {
                "status": result.status,
                "message": result.message,
                "targets": result.targets,
                "tolerances": result.tolerances,
                "solution": result.solution,
                "ideal": result.ideal,
                "achieved": result.achieved,
                "predicted": result.predicted,
                "at_bound": result.at_bound,
                "evaluations": [
                    {"kind": e.kind, "variant": e.variant,
                     "metrics": {m: e.metrics.get(m) for m in result.targets}}
                    for e in result.evaluations
                ],
            },
            indent=1,
        )
    )
    print(f"Result: {output}")
    return 0 if result.status == "converged" else 2


if __name__ == "__main__":
    sys.exit(run())
