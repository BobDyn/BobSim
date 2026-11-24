"""Small-vector helpers for the reduced models' hot paths."""

from __future__ import annotations

import numpy as np
from numpy.typing import ArrayLike, NDArray


def cross(a: ArrayLike, b: ArrayLike) -> NDArray[np.float64]:
    """## Cross Product

    Same result as ``np.cross`` for vectors on the last axis, without its
    axis bookkeeping. A GGV slice makes hundreds of thousands of these calls on
    3-vectors and 4x3 corner arrays, where ``np.cross`` spends most of its time
    in ``moveaxis``. The component formulas match NumPy's, so results are
    bitwise identical.

    Parameters
    ----------
    a, b : ArrayLike
        Vectors with length 3 on the last axis. Leading axes broadcast.

    Returns
    -------
    NDArray
        ``a x b`` with the broadcast shape.
    """
    a = np.asarray(a, dtype=float)
    b = np.asarray(b, dtype=float)
    if a.shape == (3,) and b.shape == (3,):
        a0, a1, a2 = a.tolist()
        b0, b1, b2 = b.tolist()
        return np.array((a1 * b2 - a2 * b1, a2 * b0 - a0 * b2, a0 * b1 - a1 * b0))
    a0, a1, a2 = a[..., 0], a[..., 1], a[..., 2]
    b0, b1, b2 = b[..., 0], b[..., 1], b[..., 2]
    return np.stack((a1 * b2 - a2 * b1, a2 * b0 - a0 * b2, a0 * b1 - a1 * b0), axis=-1)
