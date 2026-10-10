"""Regenerate the deterministic synthetic endurance reference corridor."""

from __future__ import annotations

import csv
from pathlib import Path

import numpy as np


OUTPUT = Path(__file__).with_name("endurance_reference.csv")


def generate_reference(*, gate_count: int = 72, width_m: float = 5.0) -> np.ndarray:
    """Return paired boundaries for a 694 m multi-feature closed course.

    The Fourier centerline is deliberately non-circular: it contains a long
    sweeper, a tight hairpin, offsets, and eight curvature-sign changes. It is
    a stable regression/reference course, not a surveyed competition layout.
    """

    theta = np.linspace(0.0, 2.0 * np.pi, gate_count, endpoint=False)
    x_m = (
        120.0 * np.cos(theta)
        + 20.0 * np.cos(2.0 * theta)
        + 12.0 * np.sin(3.0 * theta)
        + 8.0 * np.cos(5.0 * theta)
    )
    y_m = (
        78.0 * np.sin(theta)
        + 15.0 * np.sin(2.0 * theta)
        + 10.0 * np.cos(3.0 * theta)
        + 7.0 * np.sin(5.0 * theta)
    )
    dx = (
        -120.0 * np.sin(theta)
        - 40.0 * np.sin(2.0 * theta)
        + 36.0 * np.cos(3.0 * theta)
        - 40.0 * np.sin(5.0 * theta)
    )
    dy = (
        78.0 * np.cos(theta)
        + 30.0 * np.cos(2.0 * theta)
        - 30.0 * np.sin(3.0 * theta)
        + 35.0 * np.cos(5.0 * theta)
    )
    tangent_norm = np.hypot(dx, dy)
    normal = np.column_stack((-dy / tangent_norm, dx / tangent_norm))
    centerline = np.column_stack((x_m, y_m))
    half_width = 0.5 * width_m
    left = centerline + half_width * normal
    right = centerline - half_width * normal
    return np.column_stack((left, right))


def main() -> None:
    rows = generate_reference()
    with OUTPUT.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.writer(handle)
        writer.writerow(("left_x_m", "left_y_m", "right_x_m", "right_y_m"))
        writer.writerows(rows)
    print(f"Wrote {OUTPUT}")


if __name__ == "__main__":
    main()
