"""Tire grip use and lateral load transfer for BobVis.

Numpy only, like :mod:`_1_VisualSim.navigation`, so it tests without the
rendering stack. Two things are derived here from signals a run already has:

Friction circles
    How much of its available grip each tire is using. The limit is MF5.2's
    pure-slip peak friction, from the same expressions BobLib's
    ``MF52.PureSlip`` evaluations use::

        dfz  = (Fz - FNOMIN*LFZO) / (FNOMIN*LFZO)
        mu_x = (PDX1 + PDX2*dfz) * (1 - PDX3*gamma^2) * LMUX
        mu_y = (PDY1 + PDY2*dfz) * (1 - PDY3*gamma^2) * LMUY

    Usage is the radius on the friction ellipse, ``hypot(Fx/(mu_x Fz),
    Fy/(mu_y Fz))``: 1.0 is at the peak. The ellipse is an approximation of
    MF5.2's combined-slip envelope, so read the edge as "at the limit", not as
    a hard wall.

LLTD
    Each axle's lateral load transfer is half its left-right load split,
    measured from where the run started so a static asymmetry does not read as
    transfer. LLTD is the front axle's share of the total, and is left
    undefined while there is too little transfer to divide by.
"""

from __future__ import annotations

from typing import Mapping

import numpy as np

REQUIRED_TIR_KEYS = ("FNOMIN", "PDX1", "PDX2", "PDY1", "PDY2")
OPTIONAL_TIR_KEYS = {"LFZO": 1.0, "LMUX": 1.0, "LMUY": 1.0, "PDX3": 0.0, "PDY3": 0.0}

MU_FLOOR = 0.05
"""Smallest peak friction used, so extreme load or camber never divides by ~0."""

MIN_LOAD_N = 10.0
"""Below this a tire is treated as off the ground: it has no grip to use."""

LLTD_MIN_FRACTION = 0.01
"""LLTD is undefined until total transfer reaches this share of the car's weight."""


def friction_coefficients(tir: Mapping[str, float | str]) -> dict[str, float]:
    """The peak-friction terms of a parsed ``.tir`` file.

    Scale factors default to 1 and camber terms to 0, as a ``.tir`` that omits
    them means. A missing required term raises ``KeyError`` naming it.
    """
    missing = [key for key in REQUIRED_TIR_KEYS if key not in tir]
    if missing:
        raise KeyError(f"tire file lacks {', '.join(missing)}")
    coeffs = {key: float(tir[key]) for key in REQUIRED_TIR_KEYS}
    coeffs.update({key: float(tir.get(key, default)) for key, default in OPTIONAL_TIR_KEYS.items()})
    return coeffs


def peak_mu(
    fz: np.ndarray | float, gamma: np.ndarray | float, coeffs: Mapping[str, float]
) -> tuple[np.ndarray, np.ndarray]:
    """Longitudinal and lateral peak friction at a normal load and camber (radians)."""
    fz = np.asarray(fz, dtype=float)
    gamma_sq = np.asarray(gamma, dtype=float) ** 2
    fz0 = float(coeffs["FNOMIN"]) * float(coeffs.get("LFZO", 1.0))
    dfz = (fz - fz0) / fz0

    mu_x = (coeffs["PDX1"] + coeffs["PDX2"] * dfz) * (1.0 - coeffs.get("PDX3", 0.0) * gamma_sq)
    mu_y = (coeffs["PDY1"] + coeffs["PDY2"] * dfz) * (1.0 - coeffs.get("PDY3", 0.0) * gamma_sq)
    # PDY1 is negative in the ISO sign convention; grip is a magnitude.
    mu_x = np.maximum(np.abs(mu_x * coeffs.get("LMUX", 1.0)), MU_FLOOR)
    mu_y = np.maximum(np.abs(mu_y * coeffs.get("LMUY", 1.0)), MU_FLOOR)
    return mu_x, mu_y


def grip_usage(
    fx: np.ndarray,
    fy: np.ndarray,
    fz: np.ndarray,
    gamma: np.ndarray | float,
    coeffs: Mapping[str, float],
) -> tuple[np.ndarray, np.ndarray, np.ndarray]:
    """Forces as fractions of peak grip: ``(longitudinal, lateral, usage)``.

    ``usage`` is the friction-ellipse radius, 1.0 at the limit. All three are
    NaN where the tire is off the ground.
    """
    fx = np.asarray(fx, dtype=float)
    fy = np.asarray(fy, dtype=float)
    fz = np.asarray(fz, dtype=float)
    mu_x, mu_y = peak_mu(fz, gamma, coeffs)

    loaded = fz > MIN_LOAD_N
    safe_fz = np.where(loaded, fz, 1.0)
    longitudinal = np.where(loaded, fx / (mu_x * safe_fz), np.nan)
    lateral = np.where(loaded, fy / (mu_y * safe_fz), np.nan)
    return longitudinal, lateral, np.hypot(longitudinal, lateral)


def lateral_transfer(fz_left: np.ndarray, fz_right: np.ndarray) -> np.ndarray:
    """One axle's lateral load transfer, N: half its left-right split, less the split at the start."""
    split = 0.5 * (np.asarray(fz_left, dtype=float) - np.asarray(fz_right, dtype=float))
    return split - split[0]


def lltd(front: np.ndarray, rear: np.ndarray, min_total: float) -> np.ndarray:
    """Front share of lateral load transfer; NaN while the total is below ``min_total`` N."""
    front = np.asarray(front, dtype=float)
    rear = np.asarray(rear, dtype=float)
    total = front + rear
    enough = np.abs(total) >= max(float(min_total), 1e-9)
    return np.where(enough, front / np.where(enough, total, 1.0), np.nan)


def axle_load_transfer(
    loads: Mapping[str, np.ndarray],
) -> tuple[np.ndarray, np.ndarray, np.ndarray]:
    """``(front transfer, rear transfer, LLTD)`` from ``fl``/``fr``/``rl``/``rr`` normal loads."""
    front = lateral_transfer(loads["fl"], loads["fr"])
    rear = lateral_transfer(loads["rl"], loads["rr"])
    weight = float(sum(abs(float(np.asarray(loads[c], dtype=float)[0])) for c in ("fl", "fr", "rl", "rr")))
    return front, rear, lltd(front, rear, LLTD_MIN_FRACTION * weight)
