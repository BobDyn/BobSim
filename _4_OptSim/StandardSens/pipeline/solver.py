"""solver.py — Solve for the setup that hits target metrics.

The sweep-and-search route samples the whole parameter space and returns the
nearest sample. Its cost grows exponentially with the number of parameters and
its answer can only ever be a point that happened to be sampled. This module
treats the same question as what it is, a small bounded least-squares problem:

    min_x  sum_i ((f_i(x) - target_i) / tol_i)^2
         + reg * sum_j ((x_j - baseline_j) / span_j)^2      lower <= x <= upper

`f` is a full vehicle simulation, so evaluations are what cost money. The plan
spends them where they buy the most:

1. A star design — the centre plus one step each way per knob, 2n + 1 runs. Cost
   is linear in the number of knobs, not exponential.
2. A separable quadratic fitted through the star: slope and curvature per knob.
   Central steps matter. Static toe acts through an even function, so its slope
   at zero toe is exactly zero and a one-sided gradient would conclude toe does
   nothing.
3. The inverse is solved on that surrogate, which costs milliseconds.
4. The proposed setup is then simulated. If it misses, a secant update folds
   the miss back into the surrogate and the solve repeats. No answer is
   returned unverified.

The regulariser picks the smallest change from the current car when there are
fewer targets than knobs, so an under-determined question still has one answer.
The star does not depend on the targets, so once it is cached a new set of
targets costs only the verification runs.

Nothing here touches the filesystem or a simulator. The evaluator is injected,
which is what lets the numerics be tested without OpenModelica.
"""

from __future__ import annotations

from collections.abc import Callable, Sequence
from dataclasses import dataclass, field
from itertools import product
import math

import numpy as np
from scipy.optimize import least_squares

Variant = dict[str, float]
Metrics = dict[str, float]
Evaluator = Callable[[list[Variant]], list[Metrics]]

# Enumerating every combination of available parts is exact on the surrogate and
# instant at this size. Beyond it, fall back to snapping each knob independently.
MAX_DISCRETE_COMBINATIONS = 256
_RANDOM_STARTS = 8


@dataclass(frozen=True)
class Knob:
    """One decision variable: a setup parameter someone can actually turn."""

    path: str
    lower: float
    upper: float
    baseline: float
    values: tuple[float, ...] = ()

    def __post_init__(self) -> None:
        if not self.upper > self.lower:
            raise ValueError(f"{self.path}: upper bound must exceed lower bound")

    @property
    def span(self) -> float:
        return self.upper - self.lower


@dataclass
class Surrogate:
    """Separable quadratic through a star design, plus verification corrections."""

    center: np.ndarray
    f0: np.ndarray
    gradient: np.ndarray
    curvature: np.ndarray
    offset: np.ndarray

    def predict(self, x: np.ndarray) -> np.ndarray:
        d = x - self.center
        return self.f0 + self.gradient @ d + 0.5 * self.curvature @ (d * d) + self.offset


@dataclass
class Evaluation:
    kind: str  # "star" or "verify"
    variant: Variant
    metrics: Metrics


@dataclass
class SolveResult:
    status: str  # "converged", "best_effort", or "unreachable"
    knobs: list[Knob]
    targets: dict[str, float]
    tolerances: dict[str, float]
    solution: Variant
    achieved: Metrics
    predicted: Metrics
    ideal: Variant
    at_bound: list[str]
    evaluations: list[Evaluation] = field(default_factory=list)
    message: str = ""

    @property
    def errors(self) -> dict[str, float]:
        return {m: self.achieved[m] - t for m, t in self.targets.items()}

    @property
    def n_simulated(self) -> int:
        return len(self.evaluations)


def star_design(
    knobs: Sequence[Knob], step_fraction: float = 0.5
) -> tuple[np.ndarray, np.ndarray, list[np.ndarray]]:
    """Return (centre, steps, points): the centre then a -/+ pair per knob.

    The centre is the baseline, pulled inward just far enough that both steps
    stay inside the bounds. A baseline sitting on a bound — zero camber on a
    [-2, 0] range — would otherwise leave no room for the step that measures
    curvature.
    """
    if not 0.0 < step_fraction <= 1.0:
        raise ValueError("step_fraction must be in (0, 1]")
    steps = np.array([0.5 * step_fraction * k.span for k in knobs])
    lower = np.array([k.lower for k in knobs]) + steps
    upper = np.array([k.upper for k in knobs]) - steps
    center = np.clip(np.array([k.baseline for k in knobs]), lower, upper)

    points = [center.copy()]
    for j, step in enumerate(steps):
        for sign in (-1.0, 1.0):
            point = center.copy()
            point[j] += sign * step
            points.append(point)
    return center, steps, points


def fit_surrogate(
    center: np.ndarray, steps: np.ndarray, responses: np.ndarray
) -> Surrogate:
    """Fit slope and curvature per knob from star responses.

    `responses` has one row per star point, in `star_design` order, and one
    column per metric. Central differences make the fit exact at every point.
    """
    n = len(steps)
    if responses.shape[0] != 2 * n + 1:
        raise ValueError(f"expected {2 * n + 1} star responses, got {responses.shape[0]}")
    f0 = responses[0]
    gradient = np.empty((responses.shape[1], n))
    curvature = np.empty((responses.shape[1], n))
    for j, step in enumerate(steps):
        minus, plus = responses[1 + 2 * j], responses[2 + 2 * j]
        gradient[:, j] = (plus - minus) / (2.0 * step)
        curvature[:, j] = (plus - 2.0 * f0 + minus) / (step * step)
    return Surrogate(center, f0, gradient, curvature, np.zeros_like(f0))


def solve(
    knobs: Sequence[Knob],
    targets: dict[str, float],
    tolerances: dict[str, float],
    evaluate: Evaluator,
    *,
    regularization: float = 0.01,
    step_fraction: float = 0.5,
    max_verifications: int = 3,
    snap_discrete: bool = True,
    seed: int = 0,
) -> SolveResult:
    """Find the knob settings that put the simulated metrics on target."""
    knobs = list(knobs)
    if not knobs:
        raise ValueError("at least one knob is required")
    if not targets:
        raise ValueError("at least one target metric is required")
    metric_names = list(targets)
    target = np.array([targets[m] for m in metric_names])
    tol = np.array([tolerances[m] for m in metric_names])
    if np.any(tol <= 0.0):
        raise ValueError("tolerances must be positive")

    paths = [k.path for k in knobs]
    evaluations: list[Evaluation] = []

    def run(kind: str, points: list[np.ndarray]) -> np.ndarray:
        variants = [dict(zip(paths, (float(v) for v in point), strict=True)) for point in points]
        results = evaluate(variants)
        rows = []
        for variant, metrics in zip(variants, results, strict=True):
            evaluations.append(Evaluation(kind, variant, metrics))
            rows.append(_metric_row(metrics, metric_names, variant))
        return np.array(rows)

    center, steps, points = star_design(knobs, step_fraction)
    surrogate = fit_surrogate(center, steps, run("star", points))

    rng = np.random.default_rng(seed)
    ideal = _solve_on_surrogate(surrogate, knobs, target, tol, regularization, rng, {})

    best: tuple[float, np.ndarray, np.ndarray, np.ndarray] | None = None
    seen: list[np.ndarray] = []
    anchor = (center, surrogate.f0.copy())
    status, message = "best_effort", ""

    for _ in range(max(1, max_verifications)):
        x = _propose(surrogate, knobs, target, tol, regularization, rng, snap_discrete)
        if any(_same_setup(knobs, x, previous) for previous in seen):
            message = (
                "The correction loop proposed a setup it had already simulated, so "
                "this is the closest the available parts get."
            )
            break
        seen.append(x)

        predicted = surrogate.predict(x)
        actual = run("verify", [x])[0]
        miss = float(np.max(np.abs((actual - target) / tol)))
        if best is None or miss < best[0]:
            best = (miss, x, actual, predicted)
        if miss <= 1.0:
            status = "converged"
            break
        _secant_update(surrogate, knobs, anchor, (x, actual))
        anchor = (x, actual)

    assert best is not None
    miss, x, actual, predicted = best
    at_bound = [
        k.path for k, v in zip(knobs, x, strict=True)
        if math.isclose(v, k.lower, abs_tol=1e-9 * k.span)
        or math.isclose(v, k.upper, abs_tol=1e-9 * k.span)
    ]
    if status != "converged" and at_bound:
        status = "unreachable"
        message = (
            "These targets are outside what the knobs can reach within their "
            f"ranges; limited by: {', '.join(at_bound)}. " + message
        ).strip()

    return SolveResult(
        status=status,
        knobs=knobs,
        targets=dict(targets),
        tolerances={m: float(t) for m, t in zip(metric_names, tol, strict=True)},
        solution=dict(zip(paths, (float(v) for v in x), strict=True)),
        achieved=dict(zip(metric_names, (float(v) for v in actual), strict=True)),
        predicted=dict(zip(metric_names, (float(v) for v in predicted), strict=True)),
        ideal=dict(zip(paths, (float(v) for v in ideal), strict=True)),
        at_bound=at_bound,
        evaluations=evaluations,
        message=message,
    )


def _secant_update(
    surrogate: Surrogate,
    knobs: list[Knob],
    previous: tuple[np.ndarray, np.ndarray],
    current: tuple[np.ndarray, np.ndarray],
) -> None:
    """Fold one verification miss back into the surrogate (Broyden's update).

    Shifting the whole surface by the miss would fix the newest point but leave
    the slope wrong, so the next proposal overshoots the same way and the error
    only halves per simulation. Instead the gradient is corrected so the model
    reproduces the change actually observed between the last two simulated
    points, and the surface is then pinned to the newest one. That is the
    smallest change consistent with both.

    Knobs are in different units (N/m against degrees), so "smallest" is
    measured in range-normalised coordinates.
    """
    (x_prev, y_prev), (x_now, y_now) = previous, current
    step = x_now - x_prev
    weight = 1.0 / np.array([k.span for k in knobs]) ** 2
    scale = float(step @ (weight * step))
    if scale > 0.0:
        modelled = surrogate.predict(x_now) - surrogate.predict(x_prev)
        surrogate.gradient = surrogate.gradient + np.outer(
            (y_now - y_prev) - modelled, weight * step
        ) / scale
    surrogate.offset = surrogate.offset + (y_now - surrogate.predict(x_now))


def _metric_row(metrics: Metrics, names: list[str], variant: Variant) -> list[float]:
    row = []
    for name in names:
        value = metrics.get(name, float("nan"))
        if not math.isfinite(value):
            available = sorted(k for k, v in metrics.items() if math.isfinite(v))
            raise RuntimeError(
                f"Metric {name!r} came back missing or non-finite for {variant}. "
                "The simulation likely failed to settle. "
                f"Finite metrics: {available}"
            )
        row.append(float(value))
    return row


def _propose(
    surrogate: Surrogate,
    knobs: list[Knob],
    target: np.ndarray,
    tol: np.ndarray,
    regularization: float,
    rng: np.random.Generator,
    snap_discrete: bool,
) -> np.ndarray:
    """Best setup on the surrogate, restricted to parts that exist."""
    discrete = [j for j, k in enumerate(knobs) if k.values] if snap_discrete else []
    if not discrete:
        return _solve_on_surrogate(surrogate, knobs, target, tol, regularization, rng, {})

    options = [knobs[j].values for j in discrete]
    if math.prod(len(o) for o in options) > MAX_DISCRETE_COMBINATIONS:
        free = _solve_on_surrogate(surrogate, knobs, target, tol, regularization, rng, {})
        options = [(_nearest(o, float(free[j])),) for j, o in zip(discrete, options, strict=True)]

    best_x, best_cost = None, math.inf
    for combination in product(*options):
        fixed = dict(zip(discrete, combination, strict=True))
        x = _solve_on_surrogate(surrogate, knobs, target, tol, regularization, rng, fixed)
        cost = _cost(surrogate, knobs, target, tol, regularization, x)
        if cost < best_cost:
            best_x, best_cost = x, cost
    assert best_x is not None
    return best_x


def _same_setup(knobs: list[Knob], a: np.ndarray, b: np.ndarray) -> bool:
    """Whether two proposals are the same setup for any practical purpose.

    Compared as a fraction of each knob's range: a bounded solve lands on a limit
    only to within float noise, and on a 20 kN/m spring rate that noise is far
    larger than any absolute tolerance that would suit a toe angle.
    """
    span = np.array([k.span for k in knobs])
    return bool(np.all(np.abs(a - b) / span < 1e-6))


def _nearest(values: tuple[float, ...], target: float) -> float:
    return min(values, key=lambda value: abs(value - target))


def _residuals(
    surrogate: Surrogate,
    knobs: list[Knob],
    target: np.ndarray,
    tol: np.ndarray,
    regularization: float,
    x: np.ndarray,
) -> np.ndarray:
    baseline = np.array([k.baseline for k in knobs])
    span = np.array([k.span for k in knobs])
    fit = (surrogate.predict(x) - target) / tol
    pull = math.sqrt(regularization) * (x - baseline) / span
    return np.concatenate([fit, pull])


def _cost(surrogate, knobs, target, tol, regularization, x) -> float:
    r = _residuals(surrogate, knobs, target, tol, regularization, x)
    return float(r @ r)


def _solve_on_surrogate(
    surrogate: Surrogate,
    knobs: list[Knob],
    target: np.ndarray,
    tol: np.ndarray,
    regularization: float,
    rng: np.random.Generator,
    fixed: dict[int, float],
) -> np.ndarray:
    """Bounded least squares on the surrogate, with some knobs optionally pinned.

    An even response has a mirror-image minimum, so a single start can land on
    either. Several starts are free at this cost, and the regulariser makes the
    one nearer the baseline the cheaper of the two.
    """
    free = [j for j in range(len(knobs)) if j not in fixed]
    template = np.array([k.baseline for k in knobs], dtype=float)
    for j, value in fixed.items():
        template[j] = value
    if not free:
        return template

    lower = np.array([knobs[j].lower for j in free])
    upper = np.array([knobs[j].upper for j in free])

    def expand(z: np.ndarray) -> np.ndarray:
        x = template.copy()
        x[free] = z
        return x

    starts = [
        np.clip(surrogate.center[free], lower, upper),
        np.clip(template[free], lower, upper),
        *(lower + rng.random(len(free)) * (upper - lower) for _ in range(_RANDOM_STARTS)),
    ]
    best_x, best_cost = template, math.inf
    for start in starts:
        fit = least_squares(
            lambda z: _residuals(surrogate, knobs, target, tol, regularization, expand(z)),
            start,
            bounds=(lower, upper),
            method="trf",
        )
        if fit.cost < best_cost:
            best_x, best_cost = expand(fit.x), float(fit.cost)
    return best_x
