"""Physical-time statistics for adaptive-step simulation output."""
from __future__ import annotations

import numpy as np


def window_statistics(time, values, duration: float, *, end_time=None) -> dict[str, float]:
    """Integrate a piecewise-linear signal over a complete time window.

    Parameters
    ----------
    time, values : array_like
        Finite chronological samples. At event duplicates, the last value wins.
    duration : float
        Positive physical duration in seconds; incomplete windows are rejected.
    end_time : float, optional
        Window end, defaulting to the last sample. No extrapolation is allowed.

    Returns
    -------
    dict
        Time-weighted mean, standard deviation, extrema and least-squares slope.
    """
    t, y = np.asarray(time, dtype=float), np.asarray(values, dtype=float)
    if (t.ndim != 1 or y.shape != t.shape or len(t) < 2 or
            not np.all(np.isfinite(t)) or not np.all(np.isfinite(y)) or
            np.any(np.diff(t) < 0)):
        raise ValueError("Measurement requires finite chronological time and signal samples.")
    if not np.isfinite(duration) or duration <= 0:
        raise ValueError("Measurement duration must be finite and positive.")
    keep = np.r_[np.diff(t) > 0, True]
    t, y = t[keep], y[keep]
    end = float(t[-1] if end_time is None else end_time)
    start = end - duration
    if not np.isfinite(end) or start < t[0] - 1e-12 or end > t[-1] + 1e-12:
        raise ValueError("Result does not cover the complete measurement window.")
    inside = (t > start) & (t < end)
    x = np.r_[start, t[inside], end]
    v = np.interp(x, t, y)
    dt = np.diff(x)
    mean = float(np.sum(dt * (v[:-1] + v[1:]) / 2) / duration)
    centered = v - mean
    variance = np.sum(dt * (centered[:-1]**2 + centered[:-1]*centered[1:] +
                            centered[1:]**2) / 3) / duration
    # Exact first moment of each linear segment, centered on the window midpoint.
    a = x[:-1] - (start + end) / 2
    moment = np.sum(dt * a * (v[:-1] + v[1:]) / 2 +
                    dt**2 * (v[:-1] + 2*v[1:]) / 6)
    return {"mean": mean, "std": float(np.sqrt(max(0, variance))),
            "minimum": float(v.min()), "maximum": float(v.max()),
            "slope": float(12 * moment / duration**3)}
