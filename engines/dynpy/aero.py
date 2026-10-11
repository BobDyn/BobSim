"""BobLib CFD map interpolation and body-frame aerodynamic wrench."""

from __future__ import annotations

from dataclasses import dataclass
from typing import Any, Mapping

import numpy as np
from numpy.typing import NDArray

FloatArray = NDArray[np.float64]


@dataclass(frozen=True)
class AeroMap:
    """## CFD Aero Map

    Attributes
    ----------
    front_grid, rear_grid : FloatArray
        Front and rear axle ride-height breakpoints in meters.
    loads : FloatArray
        Drag, downforce, Mx, My and Mz tables at the reference speed.
    reference_speed_mps : float
        CFD reference speed.
    reference_density_kg_m3 : float
        CFD reference air density.
    reference_m : FloatArray
        Aero application point relative to the vehicle CG.
    height_points_m : FloatArray
        Four chassis-mounted ride-height points relative to the vehicle CG.
    nominal_cg_height_m : float
        Nominal CG height in the YAML reference frame.
    """

    front_grid: FloatArray
    rear_grid: FloatArray
    loads: FloatArray
    reference_speed_mps: float
    reference_density_kg_m3: float
    reference_m: FloatArray
    height_points_m: FloatArray
    nominal_cg_height_m: float

    @classmethod
    def from_yaml(cls, data: Mapping[str, Any], cg: tuple[float, float, float]) -> AeroMap:
        """## Load Aero Map

        Parameters
        ----------
        data : mapping
            Vehicle YAML aero section.
        cg : tuple
            Vehicle CG in the YAML reference frame.

        Returns
        -------
        AeroMap
            CFD tables and chassis reference points.
        """
        front = np.asarray(data["front_ride_height_grid_m"], dtype=float)
        rear = np.asarray(data["rear_ride_height_grid_m"], dtype=float)
        loads = np.asarray([data[key] for key in
                            ("drag_table_n", "downforce_table_n", "mx_table_nm", "my_table_nm", "mz_table_nm")])
        speed = float(data["reference_speed_m_per_s"])
        density = 1.225  # BobLib CFDAeroMapRecord.referenceDensity default.
        points = np.asarray([data[key] for key in
                             ("front_left_ride_height_ref_m", "front_left_ride_height_ref_m",
                              "rear_left_ride_height_ref_m", "rear_left_ride_height_ref_m")], dtype=float)
        points[[1, 3], 1] *= -1
        reference = np.asarray(data["aero_ref_m"], dtype=float)
        if (front.ndim != 1 or rear.ndim != 1 or min(front.size, rear.size) < 2
                or not np.all(np.diff(front) > 0) or not np.all(np.diff(rear) > 0)
                or loads.shape != (5, front.size, rear.size) or points.shape != (4, 3)
                or reference.shape != (3,) or not np.isfinite(speed) or speed <= 0
                or not all(np.isfinite(a).all() for a in (front, rear, loads, points, reference))):
            raise ValueError(
                "Aero map requires finite tables, increasing ride-height grids and positive reference speed."
            )
        return cls(front, rear, loads, speed, density, reference - cg, points - cg, cg[2])

    def ride_heights(self, heave_m: float, rotation: FloatArray) -> FloatArray:
        """## Corner Ride Heights

        Parameters
        ----------
        heave_m : float
            Chassis displacement from the nominal pose.
        rotation : FloatArray
            Body-to-world rotation matrix.

        Returns
        -------
        FloatArray
            World heights of the FL, FR, RL and RR chassis points, as in BobLib.
        """
        return self.nominal_cg_height_m + heave_m + (rotation @ self.height_points_m.T)[2]

    def wrench(self, heights: FloatArray, velocity: FloatArray, density: float) -> tuple[FloatArray, FloatArray]:
        """## Aero Wrench About the CG

        Parameters
        ----------
        heights : FloatArray
            Four chassis reference-point heights in meters.
        velocity : FloatArray
            Three-dimensional vehicle velocity relative to air, in body axes.
        density : float
            Air density in kilograms per cubic meter.

        Returns
        -------
        tuple[FloatArray, FloatArray]
            Body-frame force and moment about the CG, including the free CFD moments.
        """
        indices = []
        fractions = []
        for grid, height in ((self.front_grid, np.mean(heights[:2])), (self.rear_grid, np.mean(heights[2:]))):
            index = int(np.clip(np.searchsorted(grid, height) - 1, 0, len(grid) - 2))
            fraction = float(np.clip((height - grid[index]) / (grid[index + 1] - grid[index]), 0, 1))
            indices.append(index)
            fractions.append(fraction)
        i, j = indices
        x, y = fractions
        raw = ((1-x)*(1-y)*self.loads[:, i, j] + x*(1-y)*self.loads[:, i+1, j]
               + (1-x)*y*self.loads[:, i, j+1] + x*y*self.loads[:, i+1, j+1])
        speed = float(np.linalg.norm(velocity))
        drag, downforce, mx, my, mz = raw * max(density, 0) / self.reference_density_kg_m3 * (
            speed / self.reference_speed_mps
        )**2
        force = -drag * velocity / max(speed, 1e-6) + np.array([0., 0., -downforce])
        moment = np.array([mx, my, mz]) + np.cross(self.reference_m, force)
        return force, moment
