"""vet_runtime.py — Check which DOE knobs actually change a compiled simulator.

`RUNTIME_SAFE_PATHS` in overrides.py decides which knobs reuse one compiled
executable instead of getting their own compile. OpenModelica accepts an
override of a parameter it already folded into the executable and silently
ignores it, so the list can only be trusted if it is re-checked whenever the
BobLib pin moves.

This runs the executable once at baseline and once per knob with `-override`
moved to the far edge of the knob's DOE range, then reports whether the result
changed. A knob that is `live` reaches the physics at run time; `no effect`
means the override was ignored, or the run never exercised it (pick a longer
or harsher manoeuvre with --stop-time or --override before trusting that).

    python -m optimization.response.pipeline.vet_runtime \
        --build-dir simulations/mbd/BuildBobLib/VehicleSim \
        --exec-name BobLib.Experiments.Standards.VehicleSim

`--check` exits non-zero if any knob in `RUNTIME_SAFE_PATHS` shows no effect.
"""

from __future__ import annotations

import argparse
import csv
import subprocess
import sys
import tempfile
from collections.abc import Callable, Sequence
from concurrent.futures import ThreadPoolExecutor
from dataclasses import dataclass
from pathlib import Path
from typing import Any

from optimization.response.pipeline import overrides as ov
from optimization.response.pipeline import generator
from optimization.response.pipeline.sampler import read_baseline

DEFAULT_DOE_CONFIG = Path("optimization/response/configs/_doe_config.yaml")

Runner = Callable[[dict[str, float]], list[list[str]]]


@dataclass(frozen=True)
class Verdict:
    path: str
    value: float | None
    status: str  # live, no effect, run failed, rejected, skipped
    detail: str = ""


def probe_value(variable: dict[str, Any], baseline: float) -> float:
    """The DOE range edge farthest from baseline, so a live knob moves the result."""
    lo, hi = (float(x) for x in variable["range"])
    return hi if abs(hi - baseline) >= abs(lo - baseline) else lo


def changed(baseline: list[list[str]], other: list[list[str]]) -> bool:
    """Whether any signal that moves during the baseline run moved differently.

    Columns that hold one value for the whole baseline run are skipped: they are
    usually a parameter echoed into the result, which follows an override even
    when the physics that uses it was folded away at compile time.
    """
    header, rows = baseline[0], baseline[1:]
    if other[0] != header or len(other) != len(baseline):
        return True
    moving = [j for j in range(len(header)) if len({row[j] for row in rows}) > 1]
    return any(a[j] != b[j] for a, b in zip(rows, other[1:]) for j in moving)


def vet(
    variables: dict[str, dict[str, Any]],
    baseline: dict[str, float],
    context: dict[str, Any],
    init_parameters: dict[str, ov.InitParameter],
    run: Runner,
    paths: Sequence[str] | None = None,
    jobs: int = 1,
    report: Callable[[Verdict], None] | None = None,
) -> list[Verdict]:
    """Probe each DOE path once against a baseline run; ``jobs`` runs probes side by side."""
    reference = run({})
    verdicts: dict[str, Verdict] = {}
    probes: dict[str, tuple[float, dict[str, float]]] = {}
    for path in paths or list(variables):
        value = probe_value(variables[path], baseline[path])
        try:
            probes[path] = (value, ov.variant_overrides({path: value}, variables, context, init_parameters))
        except ValueError as exc:
            verdicts[path] = Verdict(path, value, "rejected", str(exc).splitlines()[-1].strip())
        except KeyError as exc:
            # Spring free length needs FourPostEval's motion ratios.
            verdicts[path] = Verdict(path, value, "skipped", f"needs FourPostEval metric {exc}")
        if path in verdicts and report:
            report(verdicts[path])

    def probe(path: str) -> Verdict:
        value, names = probes[path]
        detail = ", ".join(sorted(names))
        try:
            result = run(names)
        except subprocess.CalledProcessError as exc:
            return Verdict(path, value, "run failed", f"exit {exc.returncode}: {detail}")
        return Verdict(path, value, "live" if changed(reference, result) else "no effect", detail)

    with ThreadPoolExecutor(max_workers=max(1, jobs)) as pool:
        for verdict in pool.map(probe, probes):
            verdicts[verdict.path] = verdict
            if report:
                report(verdict)
    return [verdicts[path] for path in paths or list(variables)]


def vetting_context(cfg: dict[str, Any], config_path: Path, metrics: Path | None) -> dict[str, Any]:
    """Like generator.build_context, but missing FourPost metrics only skip the knobs that need them."""
    template = (config_path.parents[1] / cfg["architecture"]["template"]).resolve()
    try:
        four_post = generator._load_metrics_csv(metrics)
    except FileNotFoundError:
        four_post = {}
    return {"vehicle": generator.load_config(template), "four_post_metrics": four_post}


def executable_runner(build_dir: Path, exec_name: str, stop_time: float | None, extra: Sequence[str]) -> Runner:
    exe = build_dir.resolve() / exec_name

    def run(overrides: dict[str, float]) -> list[list[str]]:
        with tempfile.TemporaryDirectory() as tmp:
            result = Path(tmp) / "result.csv"
            pairs = [*extra, *(f"{name}={value!r}" for name, value in overrides.items())]
            cmd = [str(exe), f"-r={result}", "-lv=-LOG_SUCCESS"]
            if stop_time is not None:
                cmd.append(f"-stopTime={stop_time}")
            if pairs:
                cmd.append("-override=" + ",".join(pairs))
            subprocess.run(cmd, cwd=exe.parent, check=True, capture_output=True, text=True)
            with result.open(newline="") as handle:
                return list(csv.reader(handle))

    return run


def main(argv: Sequence[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--build-dir", type=Path, required=True)
    parser.add_argument("--exec-name", required=True)
    parser.add_argument("--doe-config", type=Path, default=DEFAULT_DOE_CONFIG)
    parser.add_argument("--metrics", type=Path, help="FourPostEval metrics CSV (spring knobs need it).")
    parser.add_argument("--stop-time", type=float)
    parser.add_argument("--override", action="append", default=[], help="Extra NAME=VALUE for every run.")
    parser.add_argument("--path", action="append", help="Only vet these DOE paths (repeatable).")
    parser.add_argument("--jobs", type=int, default=1, help="Probes to run at once.")
    parser.add_argument("--check", action="store_true", help="Fail if a RUNTIME_SAFE_PATHS knob has no effect.")
    args = parser.parse_args(argv)

    cfg = generator.load_config(args.doe_config)
    variables = {v["path"]: v for v in cfg["variables"]}
    baseline_mo = (args.doe_config.parent / cfg["baseline_mo"]).resolve()
    baseline = read_baseline(baseline_mo, cfg["variables"])
    context = vetting_context(cfg, args.doe_config, args.metrics)
    init_xml = ov.find_init_xml(args.build_dir, args.exec_name)
    init_parameters = ov.load_init_parameters(init_xml)
    run = executable_runner(args.build_dir, args.exec_name, args.stop_time, args.override)

    width = max(len(path) for path in args.path or variables)

    def report(v: Verdict) -> None:
        safe = "safe-listed" if v.path in ov.RUNTIME_SAFE_PATHS else ""
        print(f"{v.path:{width}s}  {v.status:10s}  {safe:11s}  {v.detail}", flush=True)

    verdicts = vet(variables, baseline, context, init_parameters, run, args.path, args.jobs, report)
    broken = [v.path for v in verdicts if v.path in ov.RUNTIME_SAFE_PATHS and v.status != "live"]
    if args.check and broken:
        print("Runtime-safe knobs that did not change the result: " + ", ".join(broken), file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
