"""MF5.2 steady-state forces and moments matching BobLib's tire evaluator."""

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

MOMENT_COEFFICIENTS = tuple(
    """
UNLOADED_RADIUS LONGVL QSX1 QSX2 QSX3 LVMX LMX QSY1 QSY2 QSY3 QSY4 LMY
QBZ1 QBZ2 QBZ3 QBZ4 QBZ5 QBZ9 QBZ10 QCZ1 QDZ1 QDZ2 QDZ3 QDZ4 QDZ6 QDZ7 QDZ8 QDZ9
QEZ1 QEZ2 QEZ3 QEZ4 QEZ5 QHZ1 QHZ2 QHZ3 QHZ4 LGAZ LTR LRES SSZ1 SSZ2 SSZ3 SSZ4 LS
""".split()
)
MF52_COEFFICIENTS = FORCE_COEFFICIENTS + MOMENT_COEFFICIENTS


@dataclass(frozen=True)
class MF52Tire:
    """## MF5.2 Tire

    Pure and combined forces and moments in BobLib's z-up frame.
    No friction floor or friction-ellipse clipping is applied.

    Parameters
    ----------
    coefficients : Mapping[str, float]
        MF5.2 coefficients from a TIR file, in SI units.
    """

    coefficients: Mapping[str, float]

    def __post_init__(self) -> None:
        missing = set(MF52_COEFFICIENTS) - self.coefficients.keys()
        if missing:
            raise ValueError(f"Missing MF5.2 coefficients: {', '.join(sorted(missing))}")
        p = {key: float(self.coefficients[key]) for key in MF52_COEFFICIENTS}
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

    def evaluate(
        self,
        fz_n: ArrayLike,
        alpha_rad: ArrayLike,
        kappa: ArrayLike,
        camber_rad: ArrayLike = 0.0,
        speed_mps: ArrayLike = 0.0,
    ) -> tuple[FloatArray, FloatArray, FloatArray, FloatArray, FloatArray]:
        """## Tire Wrench

        Evaluate BobLib's steady-state MF5.2 forces and moments.

        Parameters
        ----------
        fz_n : ArrayLike
            Normal load in newtons.
        alpha_rad : ArrayLike
            Wheel-frame slip angle in radians.
        kappa : ArrayLike
            Longitudinal slip ratio.
        camber_rad : ArrayLike
            Signed inclination angle in radians.
        speed_mps : ArrayLike
            Wheel-frame longitudinal speed in meters per second.

        Returns
        -------
        tuple[NDArray, NDArray, NDArray, NDArray, NDArray]
            Fx, Fy in newtons and Mx, My, Mz in newton meters, in the z-up wheel frame.
        """
        load, alpha, slip, gamma, speed = np.broadcast_arrays(fz_n, alpha_rad, kappa, camber_rad, speed_mps)
        fx, fy = self.forces(load, alpha, slip, gamma)
        mx, my, mz = self.moments(load, alpha, slip, gamma, speed)
        return fx, fy, mx, my, mz

    def rolling_moment(self, fz_n: ArrayLike, fx_n: ArrayLike, speed_mps: ArrayLike) -> FloatArray:
        """## Rolling Moment

        Evaluate BobLib's My equation in the z-up wheel frame.

        Parameters
        ----------
        fz_n : ArrayLike
            Actual normal load in newtons.
        fx_n : ArrayLike
            Actual longitudinal force in newtons, including low-load fading.
        speed_mps : ArrayLike
            Longitudinal speed in meters per second.

        Returns
        -------
        NDArray
            Rolling moment in newton meters.
        """
        load, fx, speed = np.broadcast_arrays(fz_n, fx_n, speed_mps)
        fz = np.maximum(load, self.fz_min_n)
        scale = np.where(load > 1e-3, load / fz, 0.0)
        raw_fx = np.divide(fx, scale, out=np.zeros_like(fz, dtype=float), where=scale != 0)
        return -scale * self._my_raw(fz, raw_fx, speed)

    def _my_raw(self, fz: FloatArray, fx: FloatArray, speed: FloatArray) -> FloatArray:
        p = self.coefficients
        if abs(p["QSY1"]) <= 1e-8 and abs(p["QSY2"]) <= 1e-8:
            dfz = (fz - p["FNOMIN"] * p["LFZO"]) / (p["FNOMIN"] * p["LFZO"])
            kx = fz * (p["PKX1"] + p["PKX2"] * dfz) * np.exp(p["PKX3"] * dfz) * p["LKX"]
            hx = (p["PHX1"] + p["PHX2"] * dfz) * p["LHX"]
            vx = fz * (p["PVX1"] + p["PVX2"] * dfz) * p["LVX"] * p["LMUX"]
            return p["UNLOADED_RADIUS"] * (vx + kx * hx)
        speed_ratio = speed / max(abs(p["LONGVL"]), 1e-8)
        return (
            p["UNLOADED_RADIUS"]
            * fz
            * (p["QSY1"] + p["QSY2"] * fx / p["FNOMIN"] + p["QSY3"] * np.abs(speed_ratio) + p["QSY4"] * speed_ratio**4)
            * p["LMY"]
        )

    def moments(
        self,
        fz_n: ArrayLike,
        alpha_rad: ArrayLike,
        kappa: ArrayLike,
        camber_rad: ArrayLike = 0.0,
        speed_mps: ArrayLike = 0.0,
    ) -> tuple[FloatArray, FloatArray, FloatArray]:
        """## Tire Moments

        Port of BobLib MF52's pure and combined Mx, My and Mz equations.

        Parameters
        ----------
        fz_n : ArrayLike
            Normal load in newtons.
        alpha_rad : ArrayLike
            Slip angle in radians.
        kappa : ArrayLike
            Longitudinal slip ratio.
        camber_rad : ArrayLike
            Signed inclination angle in radians.
        speed_mps : ArrayLike
            Longitudinal speed in meters per second.

        Returns
        -------
        tuple[NDArray, NDArray, NDArray]
            Overturning, rolling and aligning moments in the z-up wheel frame.
        """
        load, alpha, slip, gamma, speed = np.broadcast_arrays(fz_n, alpha_rad, kappa, camber_rad, speed_mps)
        fz = np.maximum(load, self.fz_min_n)
        scale = np.where(load > 1e-3, load / fz, 0.0)
        p = self.coefficients
        fx, fy_up = self.forces(fz, alpha, slip, gamma)
        fy = -fy_up
        radius, nominal = p["UNLOADED_RADIUS"], p["FNOMIN"]
        mx = radius * fz * (p["QSX1"] * p["LVMX"] + (-p["QSX2"] * gamma + p["QSX3"] * fy / nominal) * p["LMX"])
        my = self._my_raw(fz, fx, speed)
        dfz = (fz - nominal * p["LFZO"]) / (nominal * p["LFZO"])
        iy = gamma * p["LGAY"]
        cy = p["PCY1"] * p["LCY"]
        muy = (p["PDY1"] + p["PDY2"] * dfz) * (1 - p["PDY3"] * iy**2) * p["LMUY"]
        ky = p["PKY1"] * nominal * np.sin(2 * np.arctan(fz / (p["PKY2"] * nominal * p["LFZO"])))
        ky *= (1 - p["PKY3"] * np.abs(iy)) * p["LFZO"] * p["LKY"]
        by = ky / (cy * muy * fz + 1e-8)
        hy = (p["PHY1"] + p["PHY2"] * dfz) * p["LHY"] + p["PHY3"] * iy
        vy = fz * ((p["PVY1"] + p["PVY2"] * dfz) * p["LVY"] + (p["PVY3"] + p["PVY4"] * dfz) * iy) * p["LMUY"]
        kx = fz * (p["PKX1"] + p["PKX2"] * dfz) * np.exp(p["PKX3"] * dfz) * p["LKX"]
        iz = gamma * p["LGAZ"]
        dt = (
            fz
            * (p["QDZ1"] + p["QDZ2"] * dfz)
            * (1 + p["QDZ3"] * iz + p["QDZ4"] * iz**2)
            * (radius / nominal)
            * p["LTR"]
        )
        ct = p["QCZ1"]
        # The zero-friction limit has no lateral aligning moment. Avoid 0/0 without a friction floor.
        stiffness_scale = p["LKY"] / p["LMUY"] if p["LMUY"] != 0 else 0.0
        bt = (
            (p["QBZ1"] + p["QBZ2"] * dfz + p["QBZ3"] * dfz**2)
            * (1 + p["QBZ4"] * iz + p["QBZ5"] * np.abs(iz))
            * stiffness_scale
        )
        ht = p["QHZ1"] + p["QHZ2"] * dfz + (p["QHZ3"] + p["QHZ4"] * dfz) * iz
        at = alpha + ht
        et = np.minimum(
            (p["QEZ1"] + p["QEZ2"] * dfz + p["QEZ3"] * dfz**2)
            * (1 + (p["QEZ4"] + p["QEZ5"] * iz) * (2 / np.pi) * np.arctan(bt * ct * at)),
            1,
        )
        at_eq = np.arctan(np.sqrt(np.tan(at) ** 2 + (kx / (ky + 1e-8)) ** 2 * slip**2)) * np.sign(at)
        trail = dt * np.cos(ct * _magic_argument(bt * at_eq, et)) * np.cos(alpha)
        ar = alpha + hy + vy / (ky + 1e-8)
        ar_eq = np.arctan(np.sqrt(np.tan(ar) ** 2 + (kx / (ky + 1e-8)) ** 2 * slip**2)) * np.sign(ar)
        dr = fz * ((p["QDZ6"] + p["QDZ7"] * dfz) * p["LRES"] + (p["QDZ8"] + p["QDZ9"] * dfz) * iz) * radius * p["LMUY"]
        br = p["QBZ9"] * stiffness_scale + p["QBZ10"] * by * cy
        residual = dr * np.cos(np.arctan(br * ar_eq)) * np.cos(alpha)
        vyk = muy * fz * (p["RVY1"] + p["RVY2"] * dfz + p["RVY3"] * gamma) * np.cos(np.arctan(p["RVY4"] * alpha))
        vyk *= np.sin(p["RVY5"] * np.arctan(p["RVY6"] * slip)) * p["LVYKA"]
        arm = (p["SSZ1"] + p["SSZ2"] * fy / nominal + (p["SSZ3"] + p["SSZ4"] * dfz) * gamma) * radius * p["LS"]
        mz = -trail * (fy - vyk) + residual + arm * fx
        return scale * mx, -scale * my, -scale * mz

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
