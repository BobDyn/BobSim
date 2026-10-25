"""Shared vehicle-speed sampling for performance envelopes."""
import math


def automatic_vehicle_speed_grid(maximum_speed_mps: float) -> tuple[float, ...]:
    """Sample nine positive speeds through the exact drivetrain speed limit."""
    if not math.isfinite(maximum_speed_mps) or maximum_speed_mps <= 0.0:
        raise ValueError("Automatic envelope coverage requires a finite positive vehicle speed limit.")
    return tuple(maximum_speed_mps * (index / 9) for index in range(1, 10))
