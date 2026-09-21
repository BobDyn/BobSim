"""trade.py — Compare named vehicles across standard-sim metrics.

A trade study asks "what does this change buy, and what does it cost", across
several metrics at once. This module turns simulated metrics into that
comparison and nothing more. There is deliberately no score and no ranking: how
much understeer is worth how much roll is the engineer's call, and a weighted sum
would hide that call inside a number.

What it does insist on is that a difference be worth reading:

- Every metric may carry a `resolution`, the smallest change worth acting on. A
  smaller delta is still shown, marked as not resolved.
- A vehicle whose simulation lost cases is not comparable. Its fits run through
  fewer points than the baseline's, so a delta would mix the design change with
  the missing data.
- Where one candidate is exactly two others combined, the interaction is
  reported: whether the two changes stack, or the combination does something
  neither predicts.

Nothing here touches the filesystem or a simulator.
"""

from __future__ import annotations

from dataclasses import dataclass
import difflib
from itertools import combinations
import math

BASELINE = "baseline"

Variant = dict[str, float]
# candidate -> standard -> metric -> (value, units)
Results = dict[str, dict[str, dict[str, tuple[float, str]]]]

RESOLVED = "resolved"
BELOW_RESOLUTION = "below resolution"
NOT_COMPARABLE = "not comparable"


@dataclass(frozen=True)
class MetricSpec:
    standard: str
    name: str
    resolution: float | None = None


@dataclass(frozen=True)
class Comparison:
    spec: MetricSpec
    units: str
    candidate: str
    baseline: float
    value: float
    verdict: str  # RESOLVED, BELOW_RESOLUTION, NOT_COMPARABLE, or "" with no resolution

    @property
    def delta(self) -> float:
        return self.value - self.baseline


@dataclass(frozen=True)
class Interaction:
    """How far a combined change is from the sum of its two parts."""

    spec: MetricSpec
    combined: str
    parts: tuple[str, str]
    value: float  # delta(combined) - delta(part A) - delta(part B)

    @property
    def stacks(self) -> bool | None:
        if self.spec.resolution is None:
            return None
        return abs(self.value) < self.spec.resolution


def lost_cases(results: Results) -> dict[tuple[str, str], str]:
    """Return {(candidate, standard): why} for every run that is not whole."""
    problems: dict[tuple[str, str], str] = {}
    for candidate, by_standard in results.items():
        for standard, metrics in by_standard.items():
            total = metrics.get("n_cases", (math.nan, ""))[0]
            good = metrics.get("n_successful_cases", (math.nan, ""))[0]
            if not (math.isfinite(total) and math.isfinite(good)):
                problems[candidate, standard] = "reported no case counts"
            elif good < total:
                problems[candidate, standard] = f"{int(total - good)} of {int(total)} cases failed"
    return problems


def compare(results: Results, specs: list[MetricSpec]) -> list[Comparison]:
    """Compare every candidate with the baseline on every requested metric."""
    if BASELINE not in results:
        raise KeyError(f"results must include {BASELINE!r}")
    problems = lost_cases(results)

    comparisons = []
    for spec in specs:
        reference, units = _lookup(results, BASELINE, spec)
        for candidate in results:
            if candidate == BASELINE:
                continue
            value, _ = _lookup(results, candidate, spec)
            whole = (candidate, spec.standard) not in problems and (
                BASELINE,
                spec.standard,
            ) not in problems
            if not (whole and math.isfinite(value) and math.isfinite(reference)):
                verdict = NOT_COMPARABLE
            elif spec.resolution is None:
                verdict = ""
            else:
                verdict = RESOLVED if abs(value - reference) >= spec.resolution else BELOW_RESOLUTION
            comparisons.append(Comparison(spec, units, candidate, reference, value, verdict))
    return comparisons


def _lookup(results: Results, candidate: str, spec: MetricSpec) -> tuple[float, str]:
    metrics = results[candidate].get(spec.standard)
    if metrics is None:
        raise KeyError(f"{candidate!r} has no {spec.standard} results")
    if spec.name not in metrics:
        close = difflib.get_close_matches(spec.name, metrics, n=4, cutoff=0.5)
        qualified = sorted(m for m in metrics if m.endswith("." + spec.name))
        hint = (
            f" It is reported once per group, so name one of: {qualified}."
            if qualified
            else f" Closest: {close}." if close else ""
        )
        raise KeyError(f"{spec.standard} has no metric {spec.name!r}.{hint}")
    return metrics[spec.name]


def interactions(candidates: dict[str, Variant], comparisons: list[Comparison]) -> list[Interaction]:
    """Find candidates that are two others combined and measure how they stack.

    `both = a + b` qualifies when `a` and `b` change disjoint variables and `both`
    makes exactly their changes. The interaction is then the part of `both`'s
    effect that neither `a` nor `b` accounts for.
    """
    deltas = {
        (c.candidate, c.spec): c.delta for c in comparisons if c.verdict != NOT_COMPARABLE
    }
    specs = list(dict.fromkeys(c.spec for c in comparisons))

    found = []
    for combined, changes in candidates.items():
        for a, b in combinations((n for n in candidates if n != combined), 2):
            disjoint = not set(candidates[a]) & set(candidates[b])
            if not (disjoint and {**candidates[a], **candidates[b]} == changes):
                continue
            for spec in specs:
                parts = [deltas.get((name, spec)) for name in (combined, a, b)]
                if None not in parts:
                    found.append(Interaction(spec, combined, (a, b), parts[0] - parts[1] - parts[2]))
    return found


def to_markdown(
    name: str,
    candidates: dict[str, Variant],
    comparisons: list[Comparison],
    found: list[Interaction],
    problems: dict[tuple[str, str], str],
) -> str:
    lines = [f"# Trade study: {name}", "", "| Candidate | Changes from baseline |", "| --- | --- |"]
    for candidate, changes in candidates.items():
        listed = ", ".join(f"`{path}` = {value:g}" for path, value in changes.items())
        lines.append(f"| {candidate} | {listed} |")

    if problems:
        lines += ["", "**Not comparable** — these runs lost cases, so their fits rest on fewer points:", ""]
        lines += [f"- {c} / {s}: {why}" for (c, s), why in sorted(problems.items())]

    names = list(candidates)
    for standard in dict.fromkeys(c.spec.standard for c in comparisons):
        rows = [c for c in comparisons if c.spec.standard == standard]
        lines += ["", f"## {standard}", ""]
        lines.append("| Metric | Units | Resolution | baseline | " + " | ".join(names) + " |")
        lines.append("| --- | --- | --- | --- | " + " | ".join("---" for _ in names) + " |")
        for spec in dict.fromkeys(c.spec for c in rows):
            cells = {c.candidate: _cell(c) for c in rows if c.spec == spec}
            first = next(c for c in rows if c.spec == spec)
            resolution = "" if spec.resolution is None else f"{spec.resolution:g}"
            lines.append(
                f"| {spec.name} | {first.units} | {resolution} | {first.baseline:.4g} | "
                + " | ".join(cells[n] for n in names)
                + " |"
            )

    if found:
        lines += ["", "## Do the changes stack?", ""]
        lines.append("| Combined | Parts | Standard | Metric | Interaction | |")
        lines.append("| --- | --- | --- | --- | --- | --- |")
        for i in found:
            says = {None: "", True: "additive within resolution", False: "**interacts**"}[i.stacks]
            lines.append(
                f"| {i.combined} | {' + '.join(i.parts)} | {i.spec.standard} | {i.spec.name} | "
                f"{i.value:+.4g} | {says} |"
            )

    lines += [
        "",
        "Each cell is the simulated value with its change from baseline. `~` marks a change "
        "smaller than the metric's resolution: reported, but too small to act on. `n/c` marks "
        "a run that is not comparable. The interaction is the combined change minus the sum of "
        "its parts. Below the resolution it cannot be told apart from zero, which is a weaker "
        "claim than saying the changes add: read the number, not just the label.",
    ]
    return "\n".join(lines) + "\n"


def _cell(comparison: Comparison) -> str:
    if comparison.verdict == NOT_COMPARABLE:
        return "n/c"
    mark = " ~" if comparison.verdict == BELOW_RESOLUTION else ""
    return f"{comparison.value:.4g} ({comparison.delta:+.3g}){mark}"
