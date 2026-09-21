"""Solve for the setup that hits target SteadyStateEval metrics.

    make opt-solve                      # targets from configs/solve_config.yaml
    make opt-solve TARGETS="understeer_gradient_deg_per_g=0.31 roll_gradient_deg_per_g=0.85"
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
from StandardSens.pipeline.evaluator import SOLVE_DIR, SteadyStateEvaluator
from StandardSens.pipeline.orchestration import ARCHITECTURE_CONFIG
from StandardSens.pipeline.overrides import RUNTIME_SAFE_PATHS
from StandardSens.pipeline.solver import Knob, SolveResult, solve
from StandardSens.pipeline.steady_state_eval_report import Isoline

CONFIG = Path(__file__).resolve().parent / "configs/solve_config.yaml"
# Accept metric names copied from the aggregated sweep table.
METRIC_PREFIX = "SteadyStateEval_"


def parse_targets(pairs: list[str]) -> dict[str, float]:
    targets: dict[str, float] = {}
    for pair in pairs:
        name, sep, raw = pair.partition("=")
        if not sep:
            raise ValueError(f"Target must be METRIC=VALUE, got {pair!r}")
        try:
            targets[name.strip()] = float(raw)
        except ValueError:
            raise ValueError(f"Target value must be a number, got {raw!r}") from None
    return targets


def select_targets(cli_pairs: list[str] | None, config: dict[str, Any]) -> dict[str, float]:
    """Targets from the command line if given, otherwise from the config. They do not merge."""
    chosen = parse_targets(cli_pairs) if cli_pairs else (config.get("targets") or {})
    if not chosen:
        raise ValueError(
            "No targets. Set `targets:` in solve_config.yaml or pass "
            '--targets METRIC=VALUE (make opt-solve TARGETS="METRIC=VALUE ...").'
        )
    return {str(name).removeprefix(METRIC_PREFIX): float(value) for name, value in chosen.items()}


def select_tolerances(targets: dict[str, float], config: dict[str, Any]) -> dict[str, float]:
    listed = config.get("tolerances") or {}
    missing = sorted(set(targets) - set(listed))
    if missing:
        raise ValueError(
            f"No tolerance for {missing}. Add one under `tolerances:` in solve_config.yaml: "
            "it is the acceptable error, and the scale that trades one target against another."
        )
    return {metric: float(listed[metric]) for metric in targets}


def build_knobs(
    paths: list[str],
    variables: dict[str, dict[str, Any]],
    baseline: dict[str, float],
) -> list[Knob]:
    # Only explicit `scope: setup`. Untagged variables are conditions, not knobs.
    architecture = yaml.safe_load(ARCHITECTURE_CONFIG.read_text())
    setup_paths = {
        v["path"] for v in architecture["sweep"]["variables"] if v.get("scope") == "setup"
    }
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


def format_result(result: SolveResult) -> str:
    lines = [f"\nStatus: {result.status.upper()}  ({len(result.evaluations)} evaluations)"]
    if result.message:
        lines.append(result.message)

    lines.append("\nSetup:")
    width = max(len(k.path) for k in result.knobs)
    for knob in result.knobs:
        value, ideal = result.solution[knob.path], result.ideal[knob.path]
        note = f"   ideal {ideal:.6g}" if knob.values and abs(ideal - value) > 1e-9 else ""
        if knob.path in result.at_bound:
            note += "  <- at range limit"
        lines.append(
            f"  {knob.path:<{width}}  {knob.baseline:>12.6g} -> {value:>12.6g}  "
            f"({value - knob.baseline:+.4g}){note}"
        )

    lines.append("\nMetrics (simulated at the setup above):")
    width = max(len(m) for m in result.targets)
    for metric, error in result.errors.items():
        tolerance = result.tolerances[metric]
        lines.append(
            f"  {metric:<{width}}  target {result.targets[metric]:>9.4f}  "
            f"achieved {result.achieved[metric]:>9.4f}  error {error:+.4f}  "
            f"(tol {tolerance:g})  {'ok' if abs(error) <= tolerance else 'MISS'}"
        )
    return "\n".join(lines)


def run(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument(
        "--targets", nargs="+", metavar="METRIC=VALUE",
        help="replace the targets configured in solve_config.yaml",
    )
    parser.add_argument("--knobs", nargs="+", metavar="PATH", help="replace the configured knobs")
    args = parser.parse_args(argv)

    config = yaml.safe_load(CONFIG.read_text())
    targets = select_targets(args.targets, config)
    tolerances = select_tolerances(targets, config)
    matrix = config["test_matrix"]

    evaluator = SteadyStateEvaluator(
        isoline=Isoline(matrix["velocity_mps"], tuple(matrix["target_ays"])),
        cpus=config["cpus"],
    )
    knobs = build_knobs(list(args.knobs or config["knobs"]), evaluator.variables, evaluator.baseline)

    compiled = [k.path for k in knobs if k.path not in RUNTIME_SAFE_PATHS]
    if compiled:
        print(
            "Compile-only knobs — every distinct value, verifications included, is its own "
            f"~2.5 minute compile: {', '.join(compiled)}"
        )

    started = time.time()
    result = solve(knobs, targets, tolerances, evaluator)
    print(format_result(result))
    print(f"\nTotal {elapsed(started)}")

    output = SOLVE_DIR / "last_result.json"
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
