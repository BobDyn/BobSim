"""Compare named vehicles across the standard sims.

    make opt-trade                                   # configs/trade_study.yaml
    make opt-trade STUDY=path/to/another_study.yaml

Every candidate is compiled, so any swept variable can change.
"""

from __future__ import annotations

import argparse
from concurrent.futures import ThreadPoolExecutor
import csv
from pathlib import Path
import sys
import time
from typing import Any

import yaml

from _shared.console import elapsed
from StandardSens.pipeline import trade
from StandardSens.pipeline.orchestration import RESULTS_DIR, STANDARD_BUILD_DIR
from StandardSens.pipeline.standards import (
    Standard,
    get_standard,
    input_digest,
    read_metrics,
    run_standard,
)
from StandardSens.pipeline.variants import VariantStore, split_cpus

DEFAULT_STUDY = Path(__file__).resolve().parent / "configs/trade_study.yaml"
# One store for every study, so shared candidates are compiled once.
TRADE_DIR = STANDARD_BUILD_DIR / "trade"
RUN_TIMEOUT_S = 3600

Variant = dict[str, float]


def load_candidates(study: dict[str, Any], variables: dict[str, dict[str, Any]]) -> dict[str, Variant]:
    candidates: dict[str, Variant] = {}
    for name, changes in (study.get("candidates") or {}).items():
        if name == trade.BASELINE:
            raise ValueError(f"{trade.BASELINE!r} is always included. Give your candidate a different name.")
        if not changes:
            raise ValueError(f"Candidate {name!r} changes nothing, so it is the baseline")
        unknown = sorted(set(changes) - set(variables))
        if unknown:
            raise KeyError(
                f"Candidate {name!r} changes {unknown}, which are not variables in "
                "vehicle_architecture.yaml. A parameter has to be declared there, with the "
                "Modelica record block it maps to, before a study can change it."
            )
        candidates[name] = {path: float(value) for path, value in changes.items()}
        for path, value in candidates[name].items():
            low, high = variables[path]["range"]
            if not low <= value <= high:
                print(
                    f"note: {name}.{path} = {value:g} is outside the sweep range "
                    f"[{low:g}, {high:g}]. Allowed, but nothing has been simulated out there."
                )
    if not candidates:
        raise ValueError("The study names no candidates")
    return candidates


def load_specs(study: dict[str, Any]) -> list[trade.MetricSpec]:
    specs = []
    for standard, metrics in (study.get("metrics") or {}).items():
        get_standard(standard)
        for name, options in (metrics or {}).items():
            resolution = (options or {}).get("resolution")
            specs.append(
                trade.MetricSpec(standard, name, None if resolution is None else float(resolution))
            )
    if not specs:
        raise ValueError("The study names no metrics")
    return specs


def _stamp(variant_dir: Path, standard: Standard) -> Path:
    return variant_dir / "results" / standard.name / ".input_digest"


def is_cached(variant_dir: Path, standard: Standard, render_reports: bool) -> bool:
    results_dir = variant_dir / "results" / standard.name
    stamp = _stamp(variant_dir, standard)
    return (
        (results_dir / "metrics.csv").exists()
        and stamp.exists()
        and stamp.read_text() == input_digest(standard)
        and (not render_reports or (results_dir / f"{standard.stem}_report.pdf").exists())
    )


def run(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--study", type=Path, default=DEFAULT_STUDY)
    args = parser.parse_args(argv)

    study = yaml.safe_load(args.study.read_text())
    name = str(study.get("name") or args.study.stem)
    specs = load_specs(study)
    standards = [get_standard(s) for s in dict.fromkeys(spec.standard for spec in specs)]
    render_reports = bool(study.get("render_reports", True))

    store = VariantStore(TRADE_DIR)
    variables = {v["path"]: v for v in store.doe_config["variables"]}
    candidates = load_candidates(study, variables)
    vehicles: dict[str, Variant] = {trade.BASELINE: {}, **candidates}

    started = time.time()
    store.ensure_compiled(list(vehicles.values()))

    jobs = [
        (vehicle, standard)
        for vehicle in vehicles.values()
        for standard in standards
        if not is_cached(store.variant_dir(vehicle), standard, render_reports)
    ]
    if jobs:
        concurrent, workers = split_cpus(len(jobs), int(study.get("cpus", 8)))
        total = len(vehicles) * len(standards)
        print(
            f"Simulating {len(jobs)} of {total} vehicle x standard run(s), {concurrent} at a "
            f"time with {workers} case workers each ({total - len(jobs)} cached)...",
            flush=True,
        )

        def simulate(job: tuple[Variant, Standard]) -> str:
            vehicle, standard = job
            variant_dir = store.variant_dir(vehicle)
            run_standard(
                standard,
                variant_dir=variant_dir,
                build_dir=store.build_dir(vehicle),
                exec_name=store.standard_cfg["model"],
                timeout=RUN_TIMEOUT_S,
                render_report=render_reports,
                max_workers=workers,
            )
            _stamp(variant_dir, standard).write_text(input_digest(standard))
            return standard.name

        with ThreadPoolExecutor(max_workers=concurrent) as pool:
            for done, finished in enumerate(pool.map(simulate, jobs), start=1):
                print(f"  [{done}/{len(jobs)}] {finished}  {time.time() - started:.0f}s", flush=True)

    results: trade.Results = {
        label: {
            standard.name: read_metrics(
                store.variant_dir(vehicle) / "results" / standard.name / "metrics.csv"
            )
            for standard in standards
        }
        for label, vehicle in vehicles.items()
    }
    comparisons = trade.compare(results, specs)
    problems = trade.lost_cases(results)
    report = trade.to_markdown(
        name, candidates, comparisons, trade.interactions(candidates, comparisons), problems
    )

    output_dir = RESULTS_DIR / "trade"
    output_dir.mkdir(parents=True, exist_ok=True)
    (output_dir / f"{name}.md").write_text(report, encoding="utf-8")
    with (output_dir / f"{name}.csv").open("w", newline="", encoding="utf-8") as handle:
        writer = csv.writer(handle)
        writer.writerow(
            ["standard", "metric", "units", "resolution", "candidate", "baseline", "value", "delta", "verdict"]
        )
        for c in comparisons:
            writer.writerow(
                [c.spec.standard, c.spec.name, c.units, c.spec.resolution, c.candidate,
                 c.baseline, c.value, c.delta, c.verdict]
            )

    print("\n" + report)
    print(f"Total {elapsed(started)}")
    print(f"Report: {output_dir / f'{name}.md'}")
    if render_reports:
        print(f"Per-vehicle PDF reports: {store.variants_dir}/variant_*/results/")
    return 2 if problems else 0


if __name__ == "__main__":
    sys.exit(run())
