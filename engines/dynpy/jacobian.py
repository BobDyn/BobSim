"""Forward-difference Jacobians whose columns can be evaluated as one batch."""

from __future__ import annotations

import warnings
from collections.abc import Callable, Sequence

import numpy as np
from numpy.typing import ArrayLike, NDArray

FloatArray = NDArray[np.float64]

# SciPy's 2-point step: sqrt(machine epsilon), the default SLSQP ``eps``.
_STEP = float(np.finfo(np.float64).eps ** 0.5)


def forward_difference_jacobian(
    fun: Callable[[FloatArray], ArrayLike], x0: ArrayLike, lower: ArrayLike, upper: ArrayLike, *,
    prefetch: Callable[[Sequence[FloatArray]], None] | None = None,
) -> FloatArray:
    """## Forward-Difference Jacobian

    The Jacobian SLSQP builds for a constraint that has no ``jac``: SciPy's
    ``approx_derivative(fun, x0, method="2-point", abs_step=sqrt(eps),
    bounds=(lower, upper))`` after the same clip to bounds. The steps and
    quotients are reproduced exactly, so the result is bit for bit the same.
    The difference is ``prefetch``: it receives every point before ``fun``
    is called at any of them, so a caller can evaluate the expensive part of
    all columns at once and let ``fun`` read the results from a cache.

    Parameters
    ----------
    fun : callable
        Vector function of the unknowns.
    x0 : ArrayLike
        Point at which to differentiate.
    lower, upper : ArrayLike
        Bounds on the unknowns. Steps turn or shrink to stay inside them.
    prefetch : callable or None
        Called once with ``[x0, x0 + h_0 e_0, ...]`` before any ``fun`` call.

    Returns
    -------
    FloatArray
        ``(m, n)`` Jacobian of the ``m`` outputs by the ``n`` unknowns.
    """
    x = np.array(x0, dtype=float)
    low = np.broadcast_to(np.asarray(lower, dtype=float), x.shape)
    high = np.broadcast_to(np.asarray(upper, dtype=float), x.shape)
    if np.any(x < low) or np.any(x > high):
        warnings.warn("Values in x were outside bounds during a minimize step, clipping to bounds",
                      RuntimeWarning, stacklevel=2)
        x = np.clip(x, low, high)
    sign = (x >= 0).astype(float) * 2 - 1
    step = np.full(x.shape, _STEP)
    # A step lost to rounding falls back to one relative to |x|.
    step = np.where((x + step) - x == 0, _STEP * sign * np.maximum(1.0, np.abs(x)), step)
    if not np.all((low == -np.inf) & (high == np.inf)):
        lower_room, upper_room = x - low, high - x
        outside = (x + step < low) | (x + step > high)
        fits = np.abs(step) <= np.maximum(lower_room, upper_room)
        step[outside & fits] *= -1
        forward = (upper_room >= lower_room) & ~fits
        step[forward] = upper_room[forward]
        backward = (upper_room < lower_room) & ~fits
        step[backward] = -lower_room[backward]
    points = []
    for index in range(x.size):
        point = x.copy()
        point[index] = x[index] + step[index]
        points.append(point)
    if prefetch is not None:
        prefetch([x, *points])
    f0 = np.atleast_1d(np.asarray(fun(x), dtype=float))
    jacobian = np.empty((x.size, f0.size))
    for index, point in enumerate(points):
        jacobian[index] = (np.atleast_1d(np.asarray(fun(point), dtype=float)) - f0) / (
            (x[index] + step[index]) - x[index]
        )
    return jacobian.T
