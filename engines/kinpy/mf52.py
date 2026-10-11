from __future__ import annotations

from pathlib import Path


class MF52:
    """Minimal MF52-compatible tire wrapper for migrated kinematics tests."""

    def __init__(self, tire_name: str, file_path: str | Path) -> None:
        self.tire_name = tire_name
        self.file_path = Path(file_path)

    def tire_eval(self, FZ: float, alpha: float, kappa: float, gamma: float) -> list[float]:
        return [float(FZ), float(alpha), float(kappa), float(gamma)]
