"""Solve for the setup that hits target metrics.

Bounded least squares on a quadratic surrogate fitted to a star design (2n + 1
runs). Each proposed setup is simulated and fed back with a secant update:

    min_x  sum_i ((f_i(x) - target_i) / tol_i)^2
         + reg * sum_j ((x_j - baseline_j) / span_j)^2      lower <= x <= upper

The star uses central steps because toe acts through an even function, so its
slope at zero toe is zero. The evaluator is injected so tests need no simulator.
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

# Weight on (change / range)^2. Picks one answer when there are fewer targets than knobs.
REGULARIZATION = 0.01
# Fraction of each knob's half-range. Wide steps keep the signal above simulation noise.
STAR_STEP_FRACTION = 0.5
MAX_VERIFICATIONS = 4
# An even response has a mirror-image minimum, so one start can land on either.
_RANDOM_STARTS = 8


@dataclass(frozen=True)
class Knob:
    """A setup parameter someone can actually turn."""

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


@dataclass(frozen=True)
class _Problem:
    """The fixed half of the least-squares problem, as arrays built once."""

    knobs: tuple[Knob, ...]
    target: np.ndarray
    tol: np.ndarray
    regularization: float
    lower: np.ndarray
    upper: np.ndarray
    baseline: np.ndarray
    span: np.ndarray

    @classmethod
    def build(
        cls, knobs: Sequence[Knob], target: np.ndarray, tol: np.ndarray, regularization: float
    ) -> _Problem:
        return cls(
            knobs=tuple(knobs),
            target=target,
            tol=tol,
            regularization=regularization,
            lower=np.array([k.lower for k in knobs]),
            upper=np.array([k.upper for k in knobs]),
            baseline=np.array([k.baseline for k in knobs]),
            span=np.array([k.span for k in knobs]),
        )

    def residuals(self, surrogate: Surrogate, x: np.ndarray) -> np.ndarray:
        fit = (surrogate.predict(x) - self.target) / self.tol
        pull = math.sqrt(self.regularization) * (x - self.baseline) / self.span
        return np.concatenate([fit, pull])

    def same_setup(self, a: np.ndarray, b: np.ndarray) -> bool:
        """Compare as a fraction of each knob's range, because knob units differ widely."""
        return bool(np.all(np.abs(a - b) / self.span < 1e-6))

    def at_bound(self, x: np.ndarray) -> list[str]:
        on_limit = (np.abs(x - self.lower) < 1e-9 * self.span) | (
            np.abs(x - self.upper) < 1e-9 * self.span
        )
        return [k.path for k, hit in zip(self.knobs, on_limit, strict=True) if hit]


def star_design(
    knobs: Sequence[Knob], step_fraction: float = STAR_STEP_FRACTION
) -> tuple[np.ndarray, np.ndarray, list[np.ndarray]]:
    """Return (centre, steps, points): the centre then a -/+ pair per knob.

    The centre is the baseline, moved inward so both steps stay inside the bounds.
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


def fit_surrogate(center: np.ndarray, steps: np.ndarray, responses: np.ndarray) -> Surrogate:
    """Fit slope and curvature per knob. `responses` rows are in `star_design` order."""
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
    regularization: float = REGULARIZATION,
    step_fraction: float = STAR_STEP_FRACTION,
    max_verifications: int = MAX_VERIFICATIONS,
    snap_discrete: bool = True,
) -> SolveResult:
    """Find the knob settings that put the simulated metrics on target."""
    if not knobs:
        raise ValueError("at least one knob is required")
    if not targets:
        raise ValueError("at least one target metric is required")
    if max_verifications < 1:
        raise ValueError("max_verifications must be at least 1: nothing is returned unsimulated")
    metric_names = list(targets)
    tol = np.array([tolerances[m] for m in metric_names])
    if np.any(tol <= 0.0):
        raise ValueError("tolerances must be positive")
    problem = _Problem.build(
        knobs, np.array([targets[m] for m in metric_names]), tol, regularization
    )
    paths = [k.path for k in knobs]
    evaluations: list[Evaluation] = []

    def simulate(kind: str, points: list[np.ndarray]) -> np.ndarray:
        variants = [_labelled(paths, point) for point in points]
        rows = []
        for variant, metrics in zip(variants, evaluate(variants), strict=True):
            evaluations.append(Evaluation(kind, variant, metrics))
            rows.append(_metric_row(metrics, metric_names, variant))
        return np.array(rows)

    center, steps, points = star_design(knobs, step_fraction)
    surrogate = fit_surrogate(center, steps, simulate("star", points))

    rng = np.random.default_rng(0)
    ideal, _ = _solve_on_surrogate(problem, surrogate, rng, {})

    # (worst miss in tolerances, setup, simulated metrics, surrogate prediction).
    best: tuple[float, np.ndarray, np.ndarray, np.ndarray] = (math.inf, ideal, ideal, ideal)
    seen: list[np.ndarray] = []
    anchor = (center, surrogate.f0)
    status = "best_effort"
    message = (
        f"Still outside tolerance after {max_verifications} verification run(s). "
        "This is the closest setup that was simulated."
    )

    for _ in range(max_verifications):
        x = _propose(problem, surrogate, rng, snap_discrete)
        if any(problem.same_setup(x, previous) for previous in seen):
            message = (
                "The correction loop proposed a setup it had already simulated, so "
                "this is the closest the available parts get."
            )
            break
        seen.append(x)

        predicted = surrogate.predict(x)
        actual = simulate("verify", [x])[0]
        miss = float(np.max(np.abs((actual - problem.target) / problem.tol)))
        if miss < best[0]:
            best = (miss, x, actual, predicted)
        if miss <= 1.0:
            status, message = "converged", ""
            break
        _secant_update(surrogate, problem.span, anchor, (x, actual))
        anchor = (x, actual)

    _, x, actual, predicted = best
    at_bound = problem.at_bound(x)
    if status != "converged" and at_bound:
        status = "unreachable"
        message = (
            "These targets are outside what the knobs can reach within their ranges. "
            f"Knobs at a limit: {', '.join(at_bound)}. {message}"
        )

    return SolveResult(
        status=status,
        knobs=list(knobs),
        targets=dict(targets),
        tolerances=_labelled(metric_names, problem.tol),
        solution=_labelled(paths, x),
        achieved=_labelled(metric_names, actual),
        predicted=_labelled(metric_names, predicted),
        ideal=_labelled(paths, ideal),
        at_bound=at_bound,
        evaluations=evaluations,
        message=message,
    )


def _labelled(names: Sequence[str], values: np.ndarray) -> dict[str, float]:
    return dict(zip(names, (float(v) for v in values), strict=True))


def _secant_update(
    surrogate: Surrogate,
    span: np.ndarray,
    previous: tuple[np.ndarray, np.ndarray],
    current: tuple[np.ndarray, np.ndarray],
) -> None:
    """Fold one verification miss back into the surrogate (Broyden's update).

    The correction is measured in range-normalised coordinates because knob units differ.
    """
    (x_prev, y_prev), (x_now, y_now) = previous, current
    step = x_now - x_prev
    weight = 1.0 / span**2
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
    problem: _Problem, surrogate: Surrogate, rng: np.random.Generator, snap_discrete: bool
) -> np.ndarray:
    """Best setup on the surrogate, restricted to parts that exist."""
    discrete = [j for j, k in enumerate(problem.knobs) if k.values] if snap_discrete else []
    candidates = (
        _solve_on_surrogate(problem, surrogate, rng, dict(zip(discrete, combination, strict=True)))
        for combination in product(*(problem.knobs[j].values for j in discrete))
    )
    return min(candidates, key=lambda candidate: candidate[1])[0]


def _solve_on_surrogate(
    problem: _Problem,
    surrogate: Surrogate,
    rng: np.random.Generator,
    fixed: dict[int, float],
) -> tuple[np.ndarray, float]:
    """Bounded least squares on the surrogate with some knobs pinned. Returns (x, cost)."""
    free = [j for j in range(len(problem.knobs)) if j not in fixed]
    template = problem.baseline.copy()
    for j, value in fixed.items():
        template[j] = value

    def expand(z: np.ndarray) -> np.ndarray:
        x = template.copy()
        x[free] = z
        return x

    def objective(z: np.ndarray) -> np.ndarray:
        return problem.residuals(surrogate, expand(z))

    if not free:
        r = problem.residuals(surrogate, template)
        return template, 0.5 * float(r @ r)

    lower, upper = problem.lower[free], problem.upper[free]
    starts = [
        np.clip(surrogate.center[free], lower, upper),
        np.clip(template[free], lower, upper),
        *(lower + rng.random(len(free)) * (upper - lower) for _ in range(_RANDOM_STARTS)),
    ]
    fits = [least_squares(objective, start, bounds=(lower, upper), method="trf") for start in starts]
    best = min(fits, key=lambda fit: fit.cost)
    return expand(best.x), float(best.cost)
