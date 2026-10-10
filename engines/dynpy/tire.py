"""MF5.2 steady-state force curves matching BobLib's tire evaluator."""

from __future__ import annotations

from dataclasses import dataclass
from types import MappingProxyType
from typing import Mapping

import numpy as np
from numpy.typing import ArrayLike, NDArray
from scipy.optimize import brentq, minimize_scalar

FloatArray = NDArray[np.float64]
FORCE_COEFFICIENTS = tuple(
    """
FNOMIN FZMIN FZMAX KPUMIN KPUMAX LFZO LGAX LGAY
PCX1 PDX1 PDX2 PDX3 PKX1 PKX2 PKX3 PHX1 PHX2 PVX1 PVX2
PEX1 PEX2 PEX3 PEX4 LCX LMUX LKX LHX LVX LEX LXAL
PCY1 PDY1 PDY2 PDY3 PKY1 PKY2 PKY3 PHY1 PHY2 PHY3
PVY1 PVY2 PVY3 PVY4 PEY1 PEY2 PEY3 PEY4 LCY LMUY LEY LKY LHY LVY LYKA LVYKA
RBX1 RBX2 RCX1 REX1 REX2 RHX1
RBY1 RBY2 RBY3 RCY1 REY1 REY2 RHY1 RHY2 RVY1 RVY2 RVY3 RVY4 RVY5 RVY6
""".split()
)


@dataclass(frozen=True)
class MF52Tire:
    """## MF5.2 Tire

    Pure and combined longitudinal/lateral curves in BobLib's z-up frame.
    No friction floor or friction-ellipse clipping is applied.

    Parameters
    ----------
    coefficients : Mapping[str, float]
        MF5.2 coefficients from a TIR file, in SI units.
    """

    coefficients: Mapping[str, float]

    def __post_init__(self) -> None:
        missing = set(FORCE_COEFFICIENTS) - self.coefficients.keys()
        if missing:
            raise ValueError(f"Missing MF5.2 force coefficients: {', '.join(sorted(missing))}")
        p = {key: float(self.coefficients[key]) for key in FORCE_COEFFICIENTS}
        if not all(np.isfinite(value) for value in p.values()):
            raise ValueError("MF5.2 coefficients must be finite.")
        if p["FNOMIN"] <= 0 or p["LFZO"] <= 0 or not 0 < p["FZMIN"] < p["FZMAX"]:
            raise ValueError("MF5.2 nominal load, load scale and load bounds must be positive.")
        if not p["KPUMIN"] < 0 < p["KPUMAX"]:
            raise ValueError("MF5.2 slip bounds must straddle zero.")
        if p["PKY2"] <= 0:
            raise ValueError("MF5.2 PKY2 must be positive.")
        object.__setattr__(self, "coefficients", MappingProxyType(p))

    @property
    def fz_min_n(self) -> float:
        return self.coefficients["FZMIN"]

    @property
    def fz_max_n(self) -> float:
        return self.coefficients["FZMAX"]

    def slip_for_force(
        self,
        fz_n: ArrayLike,
        alpha_rad: ArrayLike,
        camber_rad: ArrayLike,
        fx_n: ArrayLike,
    ) -> FloatArray:
        """## Algebraic Wheel Slip

        Find the smallest-slip rising-branch root for the requested wheel force.
        Unattainable requests return the curve extremum within the fitted slip
        range. Callers must reject a trim if the resulting force misses demand.

        Parameters
        ----------
        fz_n : ArrayLike
            Normal load in newtons.
        alpha_rad : ArrayLike
            Slip angle in radians.
        camber_rad : ArrayLike
            Inclination angle in radians.
        fx_n : ArrayLike
            Requested longitudinal force in newtons.

        Returns
        -------
        NDArray
            Longitudinal slips with the broadcast input shape.
        """
        fz, alpha, gamma, target = np.broadcast_arrays(fz_n, alpha_rad, camber_rad, fx_n)
        grid = np.linspace(self.coefficients["KPUMIN"], self.coefficients["KPUMAX"], 65)
        curves = self.forces(fz[..., None], alpha[..., None], grid, gamma[..., None])[0]
        result = np.zeros(fz.shape)
        for index in np.ndindex(fz.shape):
            if fz[index] <= 1e-3:
                continue
            curve = curves[index]
            wanted = float(target[index])

            def force(slip: float) -> float:
                return float(self.forces(fz[index], alpha[index], slip, gamma[index])[0])

            crossings = np.flatnonzero((curve[:-1] <= wanted) & (curve[1:] >= wanted))
            if crossings.size:
                left = min(crossings, key=lambda i: abs((grid[i] + grid[i + 1]) / 2))
                result[index] = brentq(lambda slip: force(slip) - wanted, grid[left], grid[left + 1], xtol=1e-12)
            else:
                sign = 1 if wanted >= force(0) else -1
                peak = int(np.argmax(sign * curve))
                lower, upper = grid[max(0, peak - 1)], grid[min(len(grid) - 1, peak + 1)]
                optimum = minimize_scalar(
                    lambda slip: -sign * force(slip), bounds=(lower, upper), method="bounded", options={"xatol": 1e-10}
                )
                candidates = [lower, float(optimum.x), upper]
                best = max(candidates, key=lambda slip: sign * force(slip))
                # A request close to the peak can fall between grid samples.
                if sign * (force(best) - wanted) >= 0:
                    start = grid[0] if sign > 0 else grid[-1]
                    result[index] = brentq(
                        lambda slip: force(slip) - wanted, min(start, best), max(start, best), xtol=1e-12
                    )
                else:
                    result[index] = best
        return result

    def forces(
        self,
        fz_n: ArrayLike,
        alpha_rad: ArrayLike,
        kappa: ArrayLike,
        camber_rad: ArrayLike = 0.0,
    ) -> tuple[FloatArray, FloatArray]:
        """## Combined-Slip Forces

        Evaluate BobLib MF52.Eval's force equations, including its low-load fade.
        Positive alpha produces positive Fy for the bundled negative-PKY1 fits.

        Parameters
        ----------
        fz_n : ArrayLike
            Normal load in newtons. Noncontact loads produce zero force.
        alpha_rad : ArrayLike
            Slip angle atan2(-Vy, abs(Vx)) in the wheel frame, in radians.
        kappa : ArrayLike
            Longitudinal slip ratio, positive for driving.
        camber_rad : ArrayLike
            Signed inclination angle in radians, using BobLib's convention.

        Returns
        -------
        tuple[NDArray, NDArray]
            Wheel-frame Fx and Fy in newtons, with broadcast input shape.
        """
        load, alpha, slip, gamma = np.broadcast_arrays(fz_n, alpha_rad, kappa, camber_rad)
        fz = np.maximum(load, self.fz_min_n)
        scale = np.where(load > 1e-3, load / fz, 0.0)
        p = self.coefficients
        dfz = (fz - p["FNOMIN"] * p["LFZO"]) / (p["FNOMIN"] * p["LFZO"])
        mux = (p["PDX1"] + p["PDX2"] * dfz) * (1 - p["PDX3"] * (gamma * p["LGAX"]) ** 2) * p["LMUX"]
        muy = (p["PDY1"] + p["PDY2"] * dfz) * (1 - p["PDY3"] * (gamma * p["LGAY"]) ** 2) * p["LMUY"]
        cx = p["PCX1"] * p["LCX"]
        cy = p["PCY1"] * p["LCY"]
        dx, dy = mux * fz, muy * fz
        kx = fz * (p["PKX1"] + p["PKX2"] * dfz) * np.exp(p["PKX3"] * dfz) * p["LKX"]
        ky = p["PKY1"] * p["FNOMIN"] * np.sin(2 * np.arctan(fz / (p["PKY2"] * p["FNOMIN"] * p["LFZO"])))
        ky *= (1 - p["PKY3"] * np.abs(gamma * p["LGAY"])) * p["LFZO"] * p["LKY"]
        bx, by = kx / (cx * dx + 1e-8), ky / (cy * dy + 1e-8)
        sx = slip + (p["PHX1"] + p["PHX2"] * dfz) * p["LHX"]
        sy = alpha + (p["PHY1"] + p["PHY2"] * dfz) * p["LHY"] + p["PHY3"] * gamma * p["LGAY"]
        vx = fz * (p["PVX1"] + p["PVX2"] * dfz) * p["LVX"] * p["LMUX"]
        vy = (
            fz
            * ((p["PVY1"] + p["PVY2"] * dfz) * p["LVY"] + (p["PVY3"] + p["PVY4"] * dfz) * gamma * p["LGAY"])
            * p["LMUY"]
        )
        ex = np.minimum(
            (p["PEX1"] + p["PEX2"] * dfz + p["PEX3"] * dfz**2) * (1 - p["PEX4"] * np.sign(sx)) * p["LEX"], 1
        )
        ey = np.minimum(
            (p["PEY1"] + p["PEY2"] * dfz) * (1 - (p["PEY3"] + p["PEY4"] * gamma * p["LGAY"]) * np.sign(sy)) * p["LEY"],
            1,
        )
        fx0 = dx * np.sin(cx * _magic_argument(bx * sx, ex)) + vx
        fy0 = dy * np.sin(cy * _magic_argument(by * sy, ey)) + vy
        bxa = p["RBX1"] * np.cos(np.arctan(p["RBX2"] * slip)) * p["LXAL"]
        exa = p["REX1"] + p["REX2"] * dfz
        gx = np.cos(p["RCX1"] * _magic_argument(bxa * (alpha + p["RHX1"]), exa)) / np.cos(
            p["RCX1"] * _magic_argument(bxa * p["RHX1"], exa)
        )
        byk = p["RBY1"] * np.cos(np.arctan(p["RBY2"] * (alpha - p["RBY3"]))) * p["LYKA"]
        eyk = p["REY1"] + p["REY2"] * dfz
        hyk = p["RHY1"] + p["RHY2"] * dfz
        gy = np.cos(p["RCY1"] * _magic_argument(byk * (slip + hyk), eyk)) / np.cos(
            p["RCY1"] * _magic_argument(byk * hyk, eyk)
        )
        vyk = muy * fz * (p["RVY1"] + p["RVY2"] * dfz + p["RVY3"] * gamma) * np.cos(np.arctan(p["RVY4"] * alpha))
        vyk *= np.sin(p["RVY5"] * np.arctan(p["RVY6"] * slip)) * p["LVYKA"]
        return scale * fx0 * gx, -scale * (fy0 * gy + vyk)


def _magic_argument(value: FloatArray, curvature: ArrayLike) -> FloatArray:
    return np.arctan(value - np.asarray(curvature, dtype=float) * (value - np.arctan(value)))
