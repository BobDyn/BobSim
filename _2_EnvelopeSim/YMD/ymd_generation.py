"""
First-principles Yaw Moment Diagram generator for BobSim.

This computes quasi-static yaw moment diagrams using:
- mass properties
- static weight distribution
- aero downforce / drag
- lateral load transfer
- .tir-derived lateral peak friction
- .tir-derived approximate cornering stiffness
- saturated lateral tire forces
- handwheel steer and vehicle sideslip sweeps

The output is:
- YMD wireframe/carpet plot: yaw moment Mz vs lateral acceleration ay
- YMD beta-slice plot
- contour map: yaw moment over beta / roadwheel angle space, with ay contours
- CSV export
- 3D YMD speed sweep wireframe
- 3D YMD map speed sweep surface

This is intended as a first-principles BobSim analysis utility. It is not a
full Modelica trim solve and does not yet solve for steady-state yaw rate.
"""

from __future__ import annotations

import csv
from dataclasses import dataclass
from datetime import datetime
import os
from pathlib import Path
from typing import Any

os.environ.setdefault("MPLCONFIGDIR", "/tmp/matplotlib")

import matplotlib.patches as mpatches
import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages
import numpy as np
from mpl_toolkits.mplot3d.art3d import Poly3DCollection
from numpy.typing import NDArray
from scipy.spatial import ConvexHull
import yaml


G = 9.80665
IN_TO_M = 0.0254
MPH_TO_MPS = 0.44704
YMD_DIR = Path(__file__).resolve().parent
ENVELOPE_DIR = YMD_DIR.parent
REPO_ROOT = ENVELOPE_DIR.parent
BUILD_DIR = ENVELOPE_DIR / "Build" / "YMD"
DEFAULT_YMD_CONFIG = YMD_DIR / "ymd_config.yml"


FloatArray = NDArray[np.float64]
BoolArray = NDArray[np.bool_]


@dataclass(frozen=True)
class VehicleParams:
    mass: float  # kg
    wheelbase: float  # m
    track_front: float  # m
    track_rear: float  # m
    cg_height: float  # m

    front_static_frac: float  # fraction of static weight on front axle

    # Front convention:
    #   lltd = front lateral load transfer / total lateral load transfer
    lltd: float

    # Steering
    # delta_roadwheel = delta_hwa / steering_ratio
    steering_ratio: float = 1.0

    # Aero
    rho: float = 1.225  # kg/m^3
    cl_a: float = 0.0  # downforce coefficient times area, positive
    cd_a: float = 0.0  # drag coefficient times area
    aero_balance_front: float = 0.50

    # Tire model from .tir
    fz_ref: float = 654.0
    fz_min_valid: float = 100.0
    fz_max_valid: float = 1091.0

    # Lateral Magic Formula peak coefficients:
    #   mu_y ~= abs(PDY1 + PDY2 * dfz)
    pdy1: float = -2.40275
    pdy2: float = 0.343535

    # Lateral cornering stiffness coefficients:
    #   C_alpha ~= abs(PKY1) * Fz0 * sin(2 atan(Fz / (PKY2 * Fz0)))
    pky1: float = -53.2421
    pky2: float = 2.38205

    # Safety floor for extrapolated loads
    mu_min: float = 0.8


@dataclass(frozen=True)
class YMDConfig:
    speed: float = 15.0  # m/s

    beta_min_deg: float = -12.0
    beta_max_deg: float = 12.0
    beta_points: int = 61

    hwa_min_deg: float = -18.0
    hwa_max_deg: float = 18.0
    hwa_points: int = 61

    # Moment-method YMD default.
    # Later this can become a solved steady-state yaw-rate / curvature condition.
    yaw_rate: float = 0.0  # rad/s

    max_iter: int = 50
    tol_ay: float = 1e-5
    relaxation: float = 0.35

    verbose: bool = True
    warn_tire_load_range: bool = True


@dataclass
class YMDResult:
    speed: float
    beta: FloatArray
    hwa: FloatArray
    ay: FloatArray
    mz: FloatArray
    converged: BoolArray


@dataclass
class YMDSpeedSweepResult:
    speeds: FloatArray
    results: list[YMDResult]


def force_to_aero_area(
    downforce_n: float,
    drag_n: float,
    speed_mps: float,
    rho: float = 1.225,
) -> tuple[float, float]:
    """
    Convert CFD forces at a known speed to ClA and CdA.

    The vehicle model expects:
        downforce = 0.5 * rho * V^2 * cl_a
        drag      = 0.5 * rho * V^2 * cd_a
    """
    if speed_mps <= 0.0:
        raise ValueError("speed_mps must be positive.")

    q = 0.5 * rho * speed_mps**2
    cl_a = downforce_n / q
    cd_a = drag_n / q

    return cl_a, cd_a


def aero_loads(vehicle: VehicleParams, speed: float) -> tuple[float, float, float]:
    """
    Return front downforce, rear downforce, and aero drag.

    Positive downforce increases normal load.
    Positive drag opposes forward motion.
    """
    q = 0.5 * vehicle.rho * speed**2

    downforce = q * vehicle.cl_a
    drag = q * vehicle.cd_a

    front_downforce = vehicle.aero_balance_front * downforce
    rear_downforce = (1.0 - vehicle.aero_balance_front) * downforce

    return front_downforce, rear_downforce, drag


def tire_mu_y(vehicle: VehicleParams, fz: FloatArray) -> FloatArray:
    """
    Approximate lateral peak friction from .tir PDY terms.

    Uses:
        mu_y = abs(PDY1 + PDY2 * dfz)

    where:
        dfz = (Fz - Fz0) / Fz0

    Camber term PDY3 is ignored for this first-principles YMD.
    """
    fz_safe = np.maximum(fz, 1.0)
    dfz = (fz_safe - vehicle.fz_ref) / vehicle.fz_ref

    mu = np.abs(vehicle.pdy1 + vehicle.pdy2 * dfz)

    return np.maximum(mu, vehicle.mu_min)


def tire_cornering_stiffness_y(
    vehicle: VehicleParams,
    fz: FloatArray,
) -> FloatArray:
    """
    Approximate lateral cornering stiffness from .tir PKY terms.

    PAC-style approximation:
        Kya ~= PKY1 * Fz0 * sin(2 atan(Fz / (PKY2 * Fz0)))

    We use the magnitude because sign convention is handled separately.

    Returns:
        C_alpha per tire [N/rad]
    """
    fz_safe = np.maximum(fz, 1.0)

    c_alpha = abs(vehicle.pky1) * vehicle.fz_ref * np.sin(
        2.0 * np.arctan(fz_safe / (vehicle.pky2 * vehicle.fz_ref))
    )

    return np.maximum(c_alpha, 1.0)


def saturated_lateral_force(
    vehicle: VehicleParams,
    fz: FloatArray,
    alpha: FloatArray,
) -> FloatArray:
    """
    Smooth lateral tire force model.

    Linear near zero:
        Fy ~= C_alpha * alpha

    Saturated at:
        Fy_max = mu_y(Fz) * Fz
    """
    fz_positive = np.maximum(fz, 0.0)

    fy_capacity = tire_mu_y(vehicle, fz) * fz_positive
    fy_capacity = np.maximum(fy_capacity, 1.0)

    c_alpha = tire_cornering_stiffness_y(vehicle, fz)

    return fy_capacity * np.tanh(c_alpha * alpha / fy_capacity)


def wheel_positions(vehicle: VehicleParams) -> tuple[FloatArray, FloatArray]:
    """
    Wheel coordinates relative to CG.

    Coordinate convention:
        x forward
        y left

    Wheel order:
        [FL, FR, RL, RR]
    """
    # Distance from CG to front axle
    a = (1.0 - vehicle.front_static_frac) * vehicle.wheelbase

    # Distance from CG to rear axle
    b = vehicle.front_static_frac * vehicle.wheelbase

    x = np.array([a, a, -b, -b], dtype=np.float64)

    y = np.array(
        [
            vehicle.track_front / 2.0,
            -vehicle.track_front / 2.0,
            vehicle.track_rear / 2.0,
            -vehicle.track_rear / 2.0,
        ],
        dtype=np.float64,
    )

    return x, y


def wheel_loads(
    vehicle: VehicleParams,
    speed: float,
    ax: float,
    ay: float,
) -> FloatArray:
    """
    Estimate individual wheel normal loads.

    Returns:
        [FL, FR, RL, RR] normal loads [N]

    Sign convention:
        ax > 0: accelerating
        ax < 0: braking
        ay > 0: lateral acceleration to vehicle left

    For ay > 0, right-side tires are outside tires and gain load.
    """
    weight = vehicle.mass * G

    front_aero, rear_aero, _drag = aero_loads(vehicle, speed)

    fz_front = vehicle.front_static_frac * weight + front_aero
    fz_rear = (1.0 - vehicle.front_static_frac) * weight + rear_aero

    # Longitudinal load transfer.
    # ax > 0 transfers load rearward.
    d_fz_long = vehicle.mass * ax * vehicle.cg_height / vehicle.wheelbase

    fz_front -= d_fz_long
    fz_rear += d_fz_long

    # Lateral load transfer.
    total_lat_transfer_moment = vehicle.mass * ay * vehicle.cg_height

    front_lat_transfer = vehicle.lltd * total_lat_transfer_moment / vehicle.track_front
    rear_lat_transfer = (
        (1.0 - vehicle.lltd) * total_lat_transfer_moment / vehicle.track_rear
    )

    fl = 0.5 * fz_front - 0.5 * front_lat_transfer
    fr = 0.5 * fz_front + 0.5 * front_lat_transfer
    rl = 0.5 * fz_rear - 0.5 * rear_lat_transfer
    rr = 0.5 * fz_rear + 0.5 * rear_lat_transfer

    return np.array([fl, fr, rl, rr], dtype=np.float64)


def tire_slip_angles(
    vehicle: VehicleParams,
    speed: float,
    beta: float,
    hwa: float,
    yaw_rate: float = 0.0,
) -> FloatArray:
    """
    Compute tire slip angles for a simple planar 4-wheel model.

    beta:
        vehicle sideslip angle at CG [rad]

    hwa:
        roadwheel angle [rad]

    yaw_rate:
        yaw velocity [rad/s]

    Sign convention:
        positive roadwheel angle steers front tires left
        positive beta means velocity points left of vehicle x-axis

    Wheel order:
        [FL, FR, RL, RR]
    """
    x, y = wheel_positions(vehicle)

    vx_cg = speed * np.cos(beta)
    vy_cg = speed * np.sin(beta)

    vx = vx_cg - yaw_rate * y
    vy = vy_cg + yaw_rate * x

    delta_roadwheel = hwa / vehicle.steering_ratio

    wheel_heading = np.array(
        [delta_roadwheel, delta_roadwheel, 0.0, 0.0],
        dtype=np.float64,
    )

    velocity_angle = np.arctan2(vy, vx)

    # This convention gives positive front lateral force for positive steer.
    alpha = wheel_heading - velocity_angle

    return alpha


def ymd_point(
    vehicle: VehicleParams,
    config: YMDConfig,
    beta: float,
    hwa: float,
) -> tuple[float, float, bool]:
    """
    Solve one quasi-static YMD point.

    Returns:
        ay [m/s^2]
        mz [N*m]
        converged
    """
    ay = 0.0
    ax = 0.0

    x, y = wheel_positions(vehicle)

    fy_body = np.zeros(4, dtype=np.float64)
    fx_body = np.zeros(4, dtype=np.float64)

    delta_roadwheel = hwa / vehicle.steering_ratio

    for _ in range(config.max_iter):
        fz = wheel_loads(
            vehicle,
            speed=config.speed,
            ax=ax,
            ay=ay,
        )

        if np.any(fz <= 0.0):
            return np.nan, np.nan, False

        alpha = tire_slip_angles(
            vehicle,
            speed=config.speed,
            beta=beta,
            hwa=hwa,
            yaw_rate=config.yaw_rate,
        )

        fy_tire = saturated_lateral_force(vehicle, fz=fz, alpha=alpha)

        # Rotate front tire forces into vehicle body frame.
        # Rear tires have steer = 0.
        wheel_heading = np.array(
            [delta_roadwheel, delta_roadwheel, 0.0, 0.0],
            dtype=np.float64,
        )

        fx_body = -fy_tire * np.sin(wheel_heading)
        fy_body = fy_tire * np.cos(wheel_heading)

        total_fy = float(np.sum(fy_body))
        ay_new = total_fy / vehicle.mass

        if abs(ay_new - ay) < config.tol_ay:
            mz = float(np.sum(x * fy_body - y * fx_body))
            return ay_new, mz, True

        ay = (1.0 - config.relaxation) * ay + config.relaxation * ay_new

    mz = float(np.sum(x * fy_body - y * fx_body))
    return ay, mz, False


def generate_ymd(
    vehicle: VehicleParams,
    config: YMDConfig,
) -> YMDResult:
    """
    Generate a first-principles yaw moment diagram.

    Sweeps:
        beta = vehicle sideslip angle
        hwa  = roadwheel angle

    Outputs:
        ay(beta, hwa)
        mz(beta, hwa)
    """
    beta_vals = np.deg2rad(
        np.linspace(config.beta_min_deg, config.beta_max_deg, config.beta_points)
    )

    hwa_vals = np.deg2rad(
        np.linspace(config.hwa_min_deg, config.hwa_max_deg, config.hwa_points)
    )

    ay_grid = np.full((config.beta_points, config.hwa_points), np.nan, dtype=np.float64)
    mz_grid = np.full((config.beta_points, config.hwa_points), np.nan, dtype=np.float64)
    converged_grid = np.zeros((config.beta_points, config.hwa_points), dtype=bool)

    if config.verbose:
        print("=" * 72)
        print("Generating first-principles moment-method YMD")
        print(f"Speed: {config.speed:.2f} m/s")
        print(
            f"Beta sweep: {config.beta_min_deg:.1f} to "
            f"{config.beta_max_deg:.1f} deg, {config.beta_points} points"
        )
        print(
            f"Handwheel sweep: {config.hwa_min_deg:.1f} to "
            f"{config.hwa_max_deg:.1f} deg, {config.hwa_points} points"
        )
        print(f"Yaw rate: {config.yaw_rate:.4f} rad/s")
        print("=" * 72, flush=True)

    for i, beta in enumerate(beta_vals):
        if config.verbose:
            print(
                f"  beta {i + 1:>3}/{config.beta_points} | "
                f"{np.rad2deg(beta): .2f} deg",
                flush=True,
            )

        for j, hwa in enumerate(hwa_vals):
            ay, mz, converged = ymd_point(
                vehicle,
                config=config,
                beta=beta,
                hwa=hwa,
            )

            ay_grid[i, j] = ay
            mz_grid[i, j] = mz
            converged_grid[i, j] = converged

    if config.verbose:
        conv_pct = 100.0 * np.mean(converged_grid)
        print(f"YMD generation complete. Converged points: {conv_pct:.1f}%")
        print("=" * 72, flush=True)

    if config.warn_tire_load_range:
        warn_if_tire_loads_outside_tir_range(vehicle, config, beta_vals, hwa_vals)

    return YMDResult(
        speed=config.speed,
        beta=beta_vals,
        hwa=hwa_vals,
        ay=ay_grid,
        mz=mz_grid,
        converged=converged_grid,
    )


def warn_if_tire_loads_outside_tir_range(
    vehicle: VehicleParams,
    config: YMDConfig,
    beta_vals: FloatArray,
    hwa_vals: FloatArray,
) -> None:
    """
    Scan approximate finite YMD points and warn if wheel loads exceed .tir range.
    """
    fz_min_seen = np.inf
    fz_max_seen = -np.inf

    for beta in beta_vals:
        for hwa in hwa_vals:
            ay, _mz, converged = ymd_point(
                vehicle,
                config=config,
                beta=beta,
                hwa=hwa,
            )

            if not converged or not np.isfinite(ay):
                continue

            fz = wheel_loads(vehicle, speed=config.speed, ax=0.0, ay=ay)

            fz_min_seen = min(fz_min_seen, float(np.min(fz)))
            fz_max_seen = max(fz_max_seen, float(np.max(fz)))

    if not np.isfinite(fz_min_seen) or not np.isfinite(fz_max_seen):
        print("Tire load range warning skipped: no finite YMD points found.")
        return

    print("\nTire load range over finite YMD points:")
    print(f"  min Fz seen = {fz_min_seen:.1f} N")
    print(f"  max Fz seen = {fz_max_seen:.1f} N")
    print(
        f"  .tir valid range = "
        f"{vehicle.fz_min_valid:.1f} to {vehicle.fz_max_valid:.1f} N"
    )

    if fz_min_seen < vehicle.fz_min_valid or fz_max_seen > vehicle.fz_max_valid:
        print(
            "  WARNING: Some finite YMD points use tire loads outside the .tir "
            "vertical force range. Treat those regions as extrapolated."
        )


def value_to_blue_red(
    value: float,
    max_abs_value: float,
) -> tuple[float, float, float, float]:
    """
    Map negative values to blue, positive values to red, and zero to light gray.
    """
    if max_abs_value <= 0.0:
        return (0.5, 0.5, 0.5, 1.0)

    normalized = 0.5 + 0.5 * value / max_abs_value
    normalized = float(np.clip(normalized, 0.0, 1.0))

    rgba = plt.get_cmap("coolwarm")(normalized)
    return (
        float(rgba[0]),
        float(rgba[1]),
        float(rgba[2]),
        float(rgba[3]),
    )


def plot_ymd(
    result: YMDResult,
    output_path: str | Path | None = None,
) -> None:
    """
    Traditional YMD wireframe/carpet plot.

    Shows both isoline families on the same Mz vs ay plane:

        blue lines = constant beta, beta
        red lines  = constant roadwheel angle, delta_rw

    Slide-friendly labeling strategy:
        - plot integer-degree isolines only
        - label every plotted isoline
        - do NOT rotate labels
        - place labels away from the pinched endpoints
    """

    def nearest_index(values: FloatArray, target: float) -> int:
        return int(np.argmin(np.abs(values - target)))

    def selected_integer_degree_indices(values_deg: FloatArray) -> list[int]:
        """
        Select indices corresponding to integer-degree values in the available range.
        Each integer degree is matched to the nearest grid index.
        """
        vmin = float(np.nanmin(values_deg))
        vmax = float(np.nanmax(values_deg))

        int_values = np.arange(np.ceil(vmin), np.floor(vmax) + 1, 1.0)

        indices = {nearest_index(values_deg, value) for value in int_values}
        indices.add(0)
        indices.add(len(values_deg) - 1)

        return sorted(indices)

    def label_line(
        ax,
        x: FloatArray,
        y: FloatArray,
        text: str,
        frac: float,
        color: str,
        fontsize: float = 6.0,
    ) -> None:
        """
        Label a finite polyline at a fractional position through its valid points.
        Labels are intentionally NOT rotated.
        """
        mask = np.isfinite(x) & np.isfinite(y)
        valid = np.where(mask)[0]

        if len(valid) < 2:
            return

        frac = float(np.clip(frac, 0.0, 1.0))
        k = valid[int(round(frac * (len(valid) - 1)))]

        ax.text(
            x[k],
            y[k],
            text,
            fontsize=fontsize,
            color=color,
            ha="center",
            va="center",
            rotation=0.0,
            alpha=0.98,
            clip_on=True,
            bbox=dict(
                facecolor="white",
                edgecolor="none",
                alpha=0.82,
                pad=0.30,
            ),
        )

    fig, ax = plt.subplots(figsize=(8.5, 7.5))

    ay_g = result.ay / G
    mz = result.mz

    beta_deg = np.rad2deg(result.beta)

    # NOTE:
    # This variable is still named hwa in YMDResult for compatibility with the
    # rest of the script, but with steering_ratio = 1.0 this is roadwheel angle.
    delta_rw_deg = np.rad2deg(result.hwa)

    # -------------------------------------------------------------------------
    # Integer-degree isoline selection
    # -------------------------------------------------------------------------
    beta_indices = selected_integer_degree_indices(beta_deg)
    delta_indices = selected_integer_degree_indices(delta_rw_deg)

    # -------------------------------------------------------------------------
    # Blue family: constant beta isolines
    # Each row i sweeps delta_rw at fixed beta.
    # -------------------------------------------------------------------------
    n_beta = max(1, len(beta_indices) - 1)

    for label_count, i in enumerate(beta_indices):
        beta = int(round(beta_deg[i]))

        mask = np.isfinite(ay_g[i, :]) & np.isfinite(mz[i, :])

        if not np.any(mask):
            continue

        ax.plot(
            ay_g[i, mask],
            mz[i, mask],
            color="blue",
            linewidth=1.00,
            alpha=0.90,
        )

        # Spread blue labels through the interior.
        frac = 0.16 + 0.68 * (label_count / n_beta)

        label_line(
            ax=ax,
            x=ay_g[i, :],
            y=mz[i, :],
            text=fr"$\beta={beta}^\circ$",
            frac=frac,
            color="blue",
            fontsize=6.0,
        )

    # -------------------------------------------------------------------------
    # Red family: constant roadwheel-angle isolines
    # Each column j sweeps beta at fixed delta_rw.
    # -------------------------------------------------------------------------
    n_delta = max(1, len(delta_indices) - 1)

    for label_count, j in enumerate(delta_indices):
        delta_rw = int(round(delta_rw_deg[j]))

        mask = np.isfinite(ay_g[:, j]) & np.isfinite(mz[:, j])

        if not np.any(mask):
            continue

        ax.plot(
            ay_g[mask, j],
            mz[mask, j],
            color="red",
            linewidth=1.00,
            alpha=0.90,
        )

        # Put red labels on an opposing band so they interleave with blue labels.
        frac = 0.84 - 0.68 * (label_count / n_delta)

        label_line(
            ax=ax,
            x=ay_g[:, j],
            y=mz[:, j],
            text=fr"$\delta_{{rw}}={delta_rw}^\circ$",
            frac=frac,
            color="red",
            fontsize=6.0,
        )

    # -------------------------------------------------------------------------
    # Axes / styling
    # -------------------------------------------------------------------------
    ax.axhline(0.0, linewidth=0.9, color="black", alpha=0.65)
    ax.axvline(0.0, linewidth=0.9, color="black", alpha=0.65)

    ax.set_xlabel(r"Lateral Acceleration, $a_y$ ($g$)")
    ax.set_ylabel(r"Yaw Moment, $M_z$ ($N\,m$)")
    ax.set_title(
        fr"First-Principles Yaw Moment Diagram, $V={result.speed:.1f}\ m/s$"
    )

    ax.grid(True, linestyle="-", linewidth=0.7, alpha=0.35)

    ay_abs = np.nanmax(np.abs(ay_g))
    mz_abs = np.nanmax(np.abs(mz))

    ax.set_xlim(-1.10 * ay_abs, 1.10 * ay_abs)
    ax.set_ylim(-1.10 * mz_abs, 1.10 * mz_abs)

    # Legend proxies
    blue_proxy, = ax.plot(
        [],
        [],
        color="blue",
        linewidth=1.5,
        label=r"constant $\beta$",
    )
    red_proxy, = ax.plot(
        [],
        [],
        color="red",
        linewidth=1.5,
        label=r"constant $\delta_{rw}$",
    )

    ax.legend(
        handles=[blue_proxy, red_proxy],
        loc="upper right",
        frameon=True,
        fontsize=9,
    )

    fig.tight_layout()

    if output_path is not None:
        fig.savefig(output_path, dpi=300)
        print(f"Saved YMD wireframe plot: {output_path}")

    plt.show()


def plot_ymd_beta_slices(
    result: YMDResult,
    output_path: str | Path | None = None,
) -> None:
    """
    Alternate YMD plot.

    Lines of constant beta are plotted across roadwheel angle.
    """
    fig, ax = plt.subplots(figsize=(9.5, 6.2))

    ay_g = result.ay / G
    mz = result.mz

    beta_deg = np.rad2deg(result.beta)
    max_abs_beta = float(np.max(np.abs(beta_deg)))

    step = max(1, len(beta_deg) // 12)

    for i, beta in enumerate(beta_deg):
        if i % step != 0 and i != len(beta_deg) - 1:
            continue

        mask = np.isfinite(ay_g[i, :]) & np.isfinite(mz[i, :])

        if np.any(mask):
            ax.plot(
                ay_g[i, mask],
                mz[i, mask],
                color=value_to_blue_red(float(beta), max_abs_beta),
                linewidth=1.8,
                label=fr"$\beta={beta:.1f}^\circ$",
            )

    ax.axhline(0.0, linewidth=0.8, color="black", alpha=0.7)
    ax.axvline(0.0, linewidth=0.8, color="black", alpha=0.7)

    ax.set_xlabel(r"Lateral Acceleration, $a_y$ ($g$)")
    ax.set_ylabel(r"Yaw Moment, $M_z$ ($N m$)")
    ax.set_title(
        fr"First-Principles Moment-Method YMD, Beta Slices, $V={result.speed:.1f}$ $m/s$"
    )
    ax.grid(True, linestyle="--", alpha=0.5)

    ax.legend(
        loc="center left",
        bbox_to_anchor=(1.02, 0.5),
        fontsize=8,
        frameon=True,
    )

    fig.tight_layout(rect=(0.0, 0.0, 0.80, 1.0))

    if output_path is not None:
        fig.savefig(output_path, dpi=300)
        print(f"Saved YMD beta-slice plot: {output_path}")

    plt.show()


def plot_ymd_contours(
    result: YMDResult,
    output_path: str | Path | None = None,
) -> None:
    """
    Plot beta/roadwheel angle contour map for yaw moment, with ay contours.
    """
    beta_deg = np.rad2deg(result.beta)
    hwa_deg = np.rad2deg(result.hwa)

    beta_grid, hwa_grid = np.meshgrid(beta_deg, hwa_deg, indexing="ij")

    fig, ax = plt.subplots(figsize=(8.5, 6.5))

    max_abs_mz = np.nanmax(np.abs(result.mz))

    contour = ax.contourf(
        beta_grid,
        hwa_grid,
        result.mz,
        levels=np.linspace(-max_abs_mz, max_abs_mz, 33),
        cmap="coolwarm",
    )

    cbar = fig.colorbar(contour, ax=ax)
    cbar.set_label(r"Yaw Moment, $M_z$ ($N m$)")

    ay_contours = ax.contour(
        beta_grid,
        hwa_grid,
        result.ay / G,
        levels=12,
        colors="black",
        linewidths=0.8,
        alpha=0.8,
    )

    ax.clabel(ay_contours, inline=True, fontsize=8, fmt="%.1f g")

    ax.axhline(0.0, linewidth=0.8, color="black", alpha=0.7)
    ax.axvline(0.0, linewidth=0.8, color="black", alpha=0.7)

    ax.set_xlabel(r"Sideslip, $\beta$ ($deg$)")
    ax.set_ylabel(r", $\delta_{rwa}$ ($deg$)")
    ax.set_title(fr"Moment-Method YMD Map, $V={result.speed:.1f}$ $m/s$")
    ax.grid(True, linestyle="--", alpha=0.35)

    fig.tight_layout()

    if output_path is not None:
        fig.savefig(output_path, dpi=300)
        print(f"Saved YMD contour plot: {output_path}")

    plt.show()


def save_ymd_csv(result: YMDResult, output_path: str | Path) -> None:
    """
    Save YMD result to CSV.

    Columns:
        speed_mps,beta_rad,beta_deg,hwa_rad,hwa_deg,
        ay_mps2,ay_g,mz_nm,converged
    """
    output = Path(output_path)
    output.parent.mkdir(parents=True, exist_ok=True)
    rows: list[list[float]] = []

    for i, beta in enumerate(result.beta):
        for j, hwa in enumerate(result.hwa):
            ay = result.ay[i, j]
            mz = result.mz[i, j]

            rows.append(
                [
                    float(result.speed),
                    float(beta),
                    float(np.rad2deg(beta)),
                    float(hwa),
                    float(np.rad2deg(hwa)),
                    float(ay),
                    float(ay / G if np.isfinite(ay) else np.nan),
                    float(mz),
                    float(int(result.converged[i, j])),
                ]
            )

    data = np.asarray(rows, dtype=float)

    header = (
        "speed_mps,beta_rad,beta_deg,hwa_rad,hwa_deg,"
        "ay_mps2,ay_g,mz_nm,converged"
    )

    np.savetxt(output, data, delimiter=",", header=header, comments="")
    print(f"Saved YMD CSV: {output}")


def load_ymd_config(path: str | Path = DEFAULT_YMD_CONFIG) -> dict[str, Any]:
    config_path = Path(path)
    with config_path.open() as f:
        config = yaml.safe_load(f)
    if not isinstance(config, dict):
        raise ValueError(f"YMD config did not parse as a mapping: {config_path}")
    return config


def config_to_ymd_config(config: dict[str, Any]) -> YMDConfig:
    generation = config.get("generation") or {}
    return YMDConfig(
        speed=float(generation.get("speed_mps", YMDConfig.speed)),
        beta_min_deg=float(generation.get("beta_min_deg", YMDConfig.beta_min_deg)),
        beta_max_deg=float(generation.get("beta_max_deg", YMDConfig.beta_max_deg)),
        beta_points=int(generation.get("beta_points", YMDConfig.beta_points)),
        hwa_min_deg=float(generation.get("hwa_min_deg", YMDConfig.hwa_min_deg)),
        hwa_max_deg=float(generation.get("hwa_max_deg", YMDConfig.hwa_max_deg)),
        hwa_points=int(generation.get("hwa_points", YMDConfig.hwa_points)),
        yaw_rate=float(generation.get("yaw_rate_radps", YMDConfig.yaw_rate)),
        max_iter=int(generation.get("max_iter", YMDConfig.max_iter)),
        tol_ay=float(generation.get("tol_ay", YMDConfig.tol_ay)),
        relaxation=float(generation.get("relaxation", YMDConfig.relaxation)),
        verbose=bool(generation.get("verbose", True)),
        warn_tire_load_range=bool(
            generation.get("warn_tire_load_range", YMDConfig.warn_tire_load_range)
        ),
    )


def resolve_ymd_output_path(config_path: Path, raw_path: str | Path) -> Path:
    path = Path(raw_path)
    if path.is_absolute():
        return path
    return (config_path.parent / path).resolve()


def ymd_trim_curve(result: YMDResult) -> list[dict[str, float]]:
    rows_by_beta: list[list[dict[str, float]]] = []
    beta_deg = np.rad2deg(result.beta)
    hwa_deg = np.rad2deg(result.hwa)

    for i, beta in enumerate(beta_deg):
        candidates: list[dict[str, float]] = []
        mz_row = result.mz[i, :]
        ay_row = result.ay[i, :]
        converged = result.converged[i, :]

        for j in range(len(hwa_deg) - 1):
            if not (converged[j] and converged[j + 1]):
                continue
            mz0 = float(mz_row[j])
            mz1 = float(mz_row[j + 1])
            ay0 = float(ay_row[j])
            ay1 = float(ay_row[j + 1])
            if not all(np.isfinite(v) for v in (mz0, mz1, ay0, ay1)):
                continue

            if abs(mz0) <= 1e-9:
                frac = 0.0
            elif mz0 * mz1 > 0.0:
                continue
            else:
                denom = mz1 - mz0
                if abs(denom) <= 1e-12:
                    continue
                frac = -mz0 / denom

            hwa = float(hwa_deg[j] + frac * (hwa_deg[j + 1] - hwa_deg[j]))
            ay = float(ay0 + frac * (ay1 - ay0))
            candidates.append(
                {
                    "speed_mps": float(result.speed),
                    "beta_deg": float(beta),
                    "hwa_deg": hwa,
                    "ay_mps2": ay,
                    "ay_g": ay / G,
                    "mz_nm": 0.0,
                }
            )
        rows_by_beta.append(candidates)

    return _select_continuous_trim_branch(rows_by_beta, hwa_deg)


def _select_continuous_trim_branch(
    rows_by_beta: list[list[dict[str, float]]],
    hwa_deg: FloatArray,
) -> list[dict[str, float]]:
    seeded_indices = [idx for idx, rows in enumerate(rows_by_beta) if rows]
    if not seeded_indices:
        return []

    center_idx = min(
        seeded_indices,
        key=lambda idx: abs(float(rows_by_beta[idx][0]["beta_deg"])),
    )
    seed = min(rows_by_beta[center_idx], key=lambda row: abs(float(row["hwa_deg"])))

    if len(hwa_deg) > 1:
        hwa_step = float(np.nanmedian(np.abs(np.diff(np.sort(hwa_deg)))))
    else:
        hwa_step = float("nan")
    max_hwa_jump = max(2.0, 8.0 * hwa_step) if np.isfinite(hwa_step) else 2.0

    selected: dict[int, dict[str, float]] = {center_idx: seed}

    previous = seed
    for idx in range(center_idx + 1, len(rows_by_beta)):
        row = _nearest_trim_candidate(rows_by_beta[idx], previous, max_hwa_jump)
        if row is None:
            break
        selected[idx] = row
        previous = row

    previous = seed
    for idx in range(center_idx - 1, -1, -1):
        row = _nearest_trim_candidate(rows_by_beta[idx], previous, max_hwa_jump)
        if row is None:
            break
        selected[idx] = row
        previous = row

    return [selected[idx] for idx in sorted(selected)]


def _nearest_trim_candidate(
    candidates: list[dict[str, float]],
    previous: dict[str, float],
    max_hwa_jump: float,
) -> dict[str, float] | None:
    if not candidates:
        return None

    hwa_previous = float(previous["hwa_deg"])
    nearest = min(candidates, key=lambda row: abs(float(row["hwa_deg"]) - hwa_previous))
    if abs(float(nearest["hwa_deg"]) - hwa_previous) > max_hwa_jump:
        return None
    return nearest


def summarize_ymd(
    result: YMDResult,
) -> tuple[dict[str, float], list[dict[str, float]]]:
    valid = result.converged & np.isfinite(result.ay) & np.isfinite(result.mz)
    if not np.any(valid):
        raise ValueError("No converged finite YMD points available for metrics.")

    valid_indices = np.argwhere(valid)
    ay_valid = result.ay[valid]
    mz_valid = result.mz[valid]

    peak_ay_idx = valid_indices[int(np.nanargmax(np.abs(ay_valid)))]
    peak_mz_idx = valid_indices[int(np.nanargmax(np.abs(mz_valid)))]
    pos_mz_idx = valid_indices[int(np.nanargmax(mz_valid))]
    neg_mz_idx = valid_indices[int(np.nanargmin(mz_valid))]

    trim_rows = ymd_trim_curve(result)
    trim_peak = _peak_trim_row(trim_rows)
    zero_idx = _nearest_grid_index(result)

    max_positive_yaw_moment = float(result.mz[tuple(pos_mz_idx)])
    max_negative_yaw_moment = float(result.mz[tuple(neg_mz_idx)])
    trim_max_positive_ay = _trim_extreme(trim_rows, max)
    trim_max_negative_ay = _trim_extreme(trim_rows, min)

    summary = {
        "speed_mps": float(result.speed),
        "converged_fraction": float(np.mean(result.converged)),
        "peak_lateral_accel_mps2": float(result.ay[tuple(peak_ay_idx)]),
        "peak_lateral_accel_g": float(result.ay[tuple(peak_ay_idx)] / G),
        "peak_lateral_accel_abs_g": float(abs(result.ay[tuple(peak_ay_idx)]) / G),
        "yaw_moment_at_peak_lateral_accel_nm": float(result.mz[tuple(peak_ay_idx)]),
        "beta_at_peak_lateral_accel_deg": float(np.rad2deg(result.beta[peak_ay_idx[0]])),
        "hwa_at_peak_lateral_accel_deg": float(np.rad2deg(result.hwa[peak_ay_idx[1]])),
        "peak_abs_yaw_moment_nm": float(abs(result.mz[tuple(peak_mz_idx)])),
        "yaw_moment_peak_signed_nm": float(result.mz[tuple(peak_mz_idx)]),
        "lateral_accel_at_peak_yaw_moment_g": float(result.ay[tuple(peak_mz_idx)] / G),
        "max_positive_yaw_moment_nm": max_positive_yaw_moment,
        "max_negative_yaw_moment_nm": max_negative_yaw_moment,
        "yaw_moment_range_nm": max_positive_yaw_moment - max_negative_yaw_moment,
        "yaw_moment_balance": _safe_ratio(
            max_positive_yaw_moment,
            abs(max_negative_yaw_moment),
        ),
        "yaw_moment_hwa_gradient_nm_per_deg": _centerline_yaw_moment_gradient(
            result,
            axis="hwa",
        ),
        "yaw_moment_beta_gradient_nm_per_deg": _centerline_yaw_moment_gradient(
            result,
            axis="beta",
        ),
        "trim_points_count": float(len(trim_rows)),
        "trim_peak_lateral_accel_mps2": float(trim_peak.get("ay_mps2", np.nan)),
        "trim_peak_lateral_accel_g": float(trim_peak.get("ay_g", np.nan)),
        "trim_peak_lateral_accel_abs_g": float(abs(trim_peak.get("ay_g", np.nan))),
        "trim_beta_at_peak_lateral_accel_deg": float(trim_peak.get("beta_deg", np.nan)),
        "trim_hwa_at_peak_lateral_accel_deg": float(trim_peak.get("hwa_deg", np.nan)),
        "trim_max_positive_lateral_accel_g": trim_max_positive_ay,
        "trim_max_negative_lateral_accel_g": trim_max_negative_ay,
        "trim_lateral_accel_range_g": trim_max_positive_ay - trim_max_negative_ay,
        "trim_lateral_accel_balance": _safe_ratio(
            trim_max_positive_ay,
            abs(trim_max_negative_ay),
        ),
        "trim_steer_gradient_deg_per_g": _trim_linear_slope(
            trim_rows,
            y_key="hwa_deg",
        ),
        "trim_beta_gradient_deg_per_g": _trim_linear_slope(
            trim_rows,
            y_key="beta_deg",
        ),
        "zero_input_lateral_accel_g": float(result.ay[zero_idx] / G),
        "zero_input_yaw_moment_nm": float(result.mz[zero_idx]),
    }
    return summary, trim_rows


def ymd_metric_rows(summary: dict[str, float]) -> list[dict[str, float | str]]:
    metadata = {
        "speed_mps": ("m/s", "YMD evaluation speed"),
        "converged_fraction": ("fraction", "Fraction of converged beta/HWA points"),
        "peak_lateral_accel_mps2": ("m/s^2", "Signed ay at max absolute lateral acceleration"),
        "peak_lateral_accel_g": ("g", "Signed ay at max absolute lateral acceleration"),
        "peak_lateral_accel_abs_g": ("g", "Maximum absolute lateral acceleration"),
        "yaw_moment_at_peak_lateral_accel_nm": (
            "N*m",
            "Yaw moment at the max absolute lateral acceleration point",
        ),
        "beta_at_peak_lateral_accel_deg": (
            "deg",
            "Sideslip at max absolute lateral acceleration",
        ),
        "hwa_at_peak_lateral_accel_deg": (
            "deg",
            "Roadwheel/handwheel angle at max absolute lateral acceleration",
        ),
        "peak_abs_yaw_moment_nm": ("N*m", "Maximum absolute yaw moment"),
        "yaw_moment_peak_signed_nm": ("N*m", "Signed yaw moment at max abs yaw moment"),
        "lateral_accel_at_peak_yaw_moment_g": (
            "g",
            "Lateral acceleration at max absolute yaw moment",
        ),
        "max_positive_yaw_moment_nm": ("N*m", "Maximum positive yaw moment"),
        "max_negative_yaw_moment_nm": ("N*m", "Maximum negative yaw moment"),
        "yaw_moment_range_nm": ("N*m", "Positive-to-negative yaw moment range"),
        "yaw_moment_balance": (
            "ratio",
            "Positive yaw authority divided by negative yaw authority magnitude",
        ),
        "yaw_moment_hwa_gradient_nm_per_deg": (
            "N*m/deg",
            "Local yaw moment sensitivity to roadwheel angle near beta=0",
        ),
        "yaw_moment_beta_gradient_nm_per_deg": (
            "N*m/deg",
            "Local yaw moment sensitivity to sideslip near roadwheel angle=0",
        ),
        "trim_points_count": ("count", "Number of zero-yaw-moment trim points"),
        "trim_peak_lateral_accel_mps2": (
            "m/s^2",
            "Signed ay of the max absolute zero-yaw trim point",
        ),
        "trim_peak_lateral_accel_g": (
            "g",
            "Signed ay of the max absolute zero-yaw trim point",
        ),
        "trim_peak_lateral_accel_abs_g": (
            "g",
            "Maximum absolute zero-yaw trim lateral acceleration",
        ),
        "trim_beta_at_peak_lateral_accel_deg": (
            "deg",
            "Sideslip at max absolute trim lateral acceleration",
        ),
        "trim_hwa_at_peak_lateral_accel_deg": (
            "deg",
            "Roadwheel/handwheel angle at max absolute trim lateral acceleration",
        ),
        "trim_max_positive_lateral_accel_g": (
            "g",
            "Maximum positive zero-yaw trim lateral acceleration",
        ),
        "trim_max_negative_lateral_accel_g": (
            "g",
            "Maximum negative zero-yaw trim lateral acceleration",
        ),
        "trim_lateral_accel_range_g": ("g", "Positive-to-negative trim lateral acceleration range"),
        "trim_lateral_accel_balance": (
            "ratio",
            "Positive trim ay divided by negative trim ay magnitude",
        ),
        "trim_steer_gradient_deg_per_g": (
            "deg/g",
            "Local zero-yaw trim steer gradient near ay=0",
        ),
        "trim_beta_gradient_deg_per_g": (
            "deg/g",
            "Local zero-yaw trim sideslip gradient near ay=0",
        ),
        "zero_input_lateral_accel_g": ("g", "Ay at nearest beta=0, HWA=0 point"),
        "zero_input_yaw_moment_nm": ("N*m", "Mz at nearest beta=0, HWA=0 point"),
        "speed_sweep_min_speed_mps": (
            "m/s",
            "Minimum simulated speed in the YMD speed sweep",
        ),
        "speed_sweep_max_speed_mps": (
            "m/s",
            "Maximum simulated speed in the YMD speed sweep",
        ),
        "speed_sweep_peak_lateral_accel_abs_g": (
            "g",
            "Maximum absolute map ay across the speed sweep",
        ),
        "speed_sweep_peak_lateral_accel_speed_mps": (
            "m/s",
            "Speed at maximum absolute map ay across the speed sweep",
        ),
        "speed_sweep_peak_trim_lateral_accel_abs_g": (
            "g",
            "Maximum absolute zero-yaw trim ay across the speed sweep",
        ),
        "speed_sweep_peak_trim_lateral_accel_speed_mps": (
            "m/s",
            "Speed at maximum absolute zero-yaw trim ay across the speed sweep",
        ),
        "speed_sweep_peak_abs_yaw_moment_nm": (
            "N*m",
            "Maximum absolute yaw moment across the speed sweep",
        ),
        "speed_sweep_peak_abs_yaw_moment_speed_mps": (
            "m/s",
            "Speed at maximum absolute yaw moment across the speed sweep",
        ),
    }

    return [
        {
            "standard": "YMD",
            "metric": metric,
            "value": summary.get(metric, float("nan")),
            "units": units,
            "description": description,
        }
        for metric, (units, description) in metadata.items()
    ]


def save_metric_rows(rows: list[dict[str, float | str]], output_path: str | Path) -> None:
    output = Path(output_path)
    output.parent.mkdir(parents=True, exist_ok=True)
    with output.open("w", newline="") as f:
        writer = csv.DictWriter(
            f,
            fieldnames=["standard", "metric", "value", "units", "description"],
            lineterminator="\n",
        )
        writer.writeheader()
        writer.writerows(rows)
    print(f"Saved YMD metrics CSV: {output}")


def save_trim_curve_csv(
    rows: list[dict[str, float]],
    output_path: str | Path,
) -> None:
    output = Path(output_path)
    output.parent.mkdir(parents=True, exist_ok=True)
    with output.open("w", newline="") as f:
        fieldnames = ["speed_mps", "beta_deg", "hwa_deg", "ay_mps2", "ay_g", "mz_nm"]
        writer = csv.DictWriter(f, fieldnames=fieldnames, lineterminator="\n")
        writer.writeheader()
        writer.writerows(rows)
    print(f"Saved YMD trim curve CSV: {output}")


def build_ymd_report_pdf(
    result: YMDResult,
    *,
    summary: dict[str, float],
    trim_rows: list[dict[str, float]],
    speed_sweep: YMDSpeedSweepResult | None = None,
    speed_sweep_rows: list[dict[str, float]] | None = None,
    projection_summary: dict[str, float | str],
    config: dict[str, Any],
    output_path: str | Path,
) -> None:
    output = Path(output_path)
    output.parent.mkdir(parents=True, exist_ok=True)
    report_cfg = config.get("report") or {}
    with PdfPages(output) as pdf:
        _add_title_page(pdf, report_cfg)
        _add_ymd_summary_page(pdf, summary, projection_summary)
        if speed_sweep is not None:
            _add_ymd_speed_extremes_wireframe_page(pdf, speed_sweep)
            _add_ymd_speed_extremes_page(pdf, speed_sweep)
        else:
            _add_ymd_wireframe_page(pdf, result)
            _add_ymd_contour_page(pdf, result, trim_rows)
        _add_ymd_authority_page(pdf, result, trim_rows, summary)
        _add_ymd_trim_page(pdf, trim_rows, summary)
        if speed_sweep_rows:
            _add_ymd_speed_sweep_summary_page(pdf, speed_sweep_rows, summary)
    print(f"Saved YMD PDF report: {output}")


def _add_title_page(pdf: PdfPages, report_cfg: dict[str, Any]) -> None:
    fig, ax = plt.subplots(figsize=(11, 8.5))
    ax.axis("off")
    logo_path = REPO_ROOT / "_0_Utils/reporting/media/bob.png"
    if logo_path.exists():
        logo = plt.imread(logo_path)
        ax_logo = fig.add_axes([0.03, 0.72, 0.22, 0.19])
        ax_logo.imshow(logo, alpha=0.82)
        ax_logo.axis("off")

    ax.text(0.5, 0.80, report_cfg.get("brand", "BobSim"), ha="center", fontsize=24, weight="bold")
    ax.text(
        0.5,
        0.65,
        report_cfg.get("title", "Yaw Moment Diagram Characterization"),
        ha="center",
        fontsize=20,
        weight="bold",
    )
    subtitle = report_cfg.get("subtitle", "")
    if subtitle:
        ax.text(0.5, 0.57, str(subtitle), ha="center", va="center", fontsize=12)
    ax.text(
        0.5,
        0.46,
        f"Generated: {datetime.now().strftime('%Y-%m-%d %H:%M')}",
        ha="center",
        fontsize=11,
        alpha=0.85,
    )
    y = 0.36
    ax.text(0.08, y + 0.035, "Run Notes", fontsize=11, weight="bold")
    for note in [str(note) for note in report_cfg.get("notes", [])][:8]:
        ax.text(0.09, y, f"- {note}", fontsize=8.8, ha="left", va="top")
        y -= 0.032
    pdf.savefig(fig)
    plt.close(fig)


def _add_ymd_summary_page(
    pdf: PdfPages,
    summary: dict[str, float],
    projection: dict[str, float | str],
) -> None:
    fig, ax = plt.subplots(figsize=(11, 8.5))
    ax.axis("off")
    ax.text(
        0.5,
        0.94,
        "YMD Metrics Summary",
        ha="center",
        fontsize=18,
        weight="bold",
        transform=ax.transAxes,
    )
    vehicle_line = (
        f"Mass {float(projection.get('mass_kg', float('nan'))):.1f} kg | "
        f"Wheelbase {float(projection.get('wheelbase_m', float('nan'))):.3f} m | "
        f"Front aero balance {100.0 * float(projection.get('aero_balance_front', float('nan'))):.1f}%"
    )
    ax.text(
        0.5,
        0.895,
        vehicle_line,
        ha="center",
        fontsize=9.6,
        color="#374151",
        transform=ax.transAxes,
    )

    def metric_text(key: str, fmt: str) -> str:
        value = summary.get(key)
        try:
            return fmt.format(float(value))
        except (TypeError, ValueError):
            return "-"

    def range_text(low_key: str, high_key: str, fmt: str) -> str:
        low = metric_text(low_key, fmt)
        high = metric_text(high_key, fmt)
        if "-" in {low, high}:
            return "-"
        return f"{low} to {high}"

    rows = [
        ("Speed", metric_text("speed_mps", "{:.1f}"), "m/s"),
        ("Converged map", metric_text("converged_fraction", "{:.3f}"), "fraction"),
        ("Peak map |ay|", metric_text("peak_lateral_accel_abs_g", "{:.3f}"), "g"),
        ("Trim peak |ay|", metric_text("trim_peak_lateral_accel_abs_g", "{:.3f}"), "g"),
        (
            "Trim ay range",
            range_text(
                "trim_max_negative_lateral_accel_g",
                "trim_max_positive_lateral_accel_g",
                "{:.2f}",
            ),
            "g",
        ),
        ("Peak |yaw moment|", metric_text("peak_abs_yaw_moment_nm", "{:.0f}"), "N*m"),
        ("Yaw moment range", metric_text("yaw_moment_range_nm", "{:.0f}"), "N*m"),
        ("Yaw moment balance", metric_text("yaw_moment_balance", "{:.3f}"), "ratio"),
        ("Mz vs steer gradient", metric_text("yaw_moment_hwa_gradient_nm_per_deg", "{:.1f}"), "N*m/deg"),
        ("Mz vs beta gradient", metric_text("yaw_moment_beta_gradient_nm_per_deg", "{:.1f}"), "N*m/deg"),
        ("Trim steer gradient", metric_text("trim_steer_gradient_deg_per_g", "{:.2f}"), "deg/g"),
        ("Trim beta gradient", metric_text("trim_beta_gradient_deg_per_g", "{:.2f}"), "deg/g"),
        ("Zero-input yaw moment", metric_text("zero_input_yaw_moment_nm", "{:.2f}"), "N*m"),
    ]

    if "speed_sweep_peak_trim_lateral_accel_abs_g" in summary:
        rows.extend(
            [
                (
                    "Sweep speed bounds",
                    f"{metric_text('speed_sweep_min_speed_mps', '{:.1f}')} to "
                    f"{metric_text('speed_sweep_max_speed_mps', '{:.1f}')}",
                    "m/s",
                ),
                (
                    "Sweep peak trim |ay|",
                    f"{metric_text('speed_sweep_peak_trim_lateral_accel_abs_g', '{:.3f}')} @ "
                    f"{metric_text('speed_sweep_peak_trim_lateral_accel_speed_mps', '{:.1f}')}",
                    "g @ m/s",
                ),
                (
                    "Sweep peak |Mz|",
                    f"{metric_text('speed_sweep_peak_abs_yaw_moment_nm', '{:.0f}')} @ "
                    f"{metric_text('speed_sweep_peak_abs_yaw_moment_speed_mps', '{:.1f}')}",
                    "N*m @ m/s",
                ),
            ]
        )

    split_idx = int(np.ceil(len(rows) / 2.0))
    columns = [
        (0.08, 0.40, 0.50, rows[:split_idx]),
        (0.56, 0.83, 0.92, rows[split_idx:]),
    ]
    y_top = 0.80
    y_bottom = 0.14

    for x_label, x_value, x_unit, column_rows in columns:
        row_h = min(0.052, (y_top - y_bottom) / (len(column_rows) + 1.2))
        ax.text(
            x_label,
            y_top,
            "Metric",
            fontsize=10.4,
            weight="bold",
            transform=ax.transAxes,
        )
        ax.text(
            x_value,
            y_top,
            "Value",
            fontsize=10.4,
            weight="bold",
            ha="right",
            transform=ax.transAxes,
        )
        ax.text(
            x_unit,
            y_top,
            "Units",
            fontsize=10.4,
            weight="bold",
            transform=ax.transAxes,
        )
        ax.plot(
            [x_label, x_unit + 0.06],
            [y_top - 0.018, y_top - 0.018],
            color="black",
            linewidth=1.0,
            transform=ax.transAxes,
        )

        for i, (label, value_text, unit) in enumerate(column_rows):
            y = y_top - (i + 1) * row_h
            ax.text(x_label, y, label, fontsize=9.0, transform=ax.transAxes)
            ax.text(
                x_value,
                y,
                value_text,
                fontsize=9.0,
                ha="right",
                transform=ax.transAxes,
            )
            ax.text(x_unit, y, unit, fontsize=9.0, transform=ax.transAxes)
    pdf.savefig(fig)
    plt.close(fig)


def _plot_ymd_contour_axes(
    fig: plt.Figure,
    ax: plt.Axes,
    result: YMDResult,
    trim_rows: list[dict[str, float]],
    *,
    title: str,
    colorbar_label: str = "yaw moment Mz (N*m)",
) -> None:
    beta_deg = np.rad2deg(result.beta)
    hwa_deg = np.rad2deg(result.hwa)
    beta_grid, hwa_grid = np.meshgrid(beta_deg, hwa_deg, indexing="ij")
    max_abs_mz = np.nanmax(np.abs(result.mz))
    contour = ax.contourf(
        beta_grid,
        hwa_grid,
        result.mz,
        levels=np.linspace(-max_abs_mz, max_abs_mz, 33),
        cmap="coolwarm",
    )
    fig.colorbar(contour, ax=ax, label=colorbar_label)
    ay_contours = ax.contour(
        beta_grid,
        hwa_grid,
        result.ay / G,
        levels=12,
        colors="black",
        linewidths=0.75,
        alpha=0.75,
    )
    ax.clabel(ay_contours, inline=True, fontsize=8, fmt="%.1f g")
    if trim_rows:
        ax.plot(
            [row["beta_deg"] for row in trim_rows],
            [row["hwa_deg"] for row in trim_rows],
            color="#111827",
            linewidth=2.0,
            label="Mz = 0 trim",
        )
        ax.legend(loc="best")
    ax.axhline(0.0, color="black", linewidth=0.8, alpha=0.5)
    ax.axvline(0.0, color="black", linewidth=0.8, alpha=0.5)
    ax.set_xlabel("sideslip beta (deg)")
    ax.set_ylabel("roadwheel/handwheel angle (deg)")
    ax.set_title(title)
    ax.grid(True, alpha=0.2)


def _add_ymd_contour_page(
    pdf: PdfPages,
    result: YMDResult,
    trim_rows: list[dict[str, float]],
) -> None:
    fig, ax = plt.subplots(figsize=(8.8, 6.8))
    _plot_ymd_contour_axes(
        fig,
        ax,
        result,
        trim_rows,
        title=f"YMD map with trim curve, V={result.speed:.1f} m/s",
    )
    fig.tight_layout()
    pdf.savefig(fig)
    plt.close(fig)


def _add_ymd_wireframe_page(pdf: PdfPages, result: YMDResult) -> None:
    fig, ax = plt.subplots(figsize=(8.8, 6.8))
    _plot_ymd_wireframe_axes(
        ax,
        result,
        title=f"YMD wireframe families, V={result.speed:.1f} m/s",
        show_legend=True,
    )
    fig.tight_layout()
    pdf.savefig(fig)
    plt.close(fig)


def _plot_ymd_wireframe_axes(
    ax: plt.Axes,
    result: YMDResult,
    *,
    title: str,
    show_legend: bool = False,
) -> None:
    ay_g = result.ay / G
    beta_step = max(1, len(result.beta) // 10)
    hwa_step = max(1, len(result.hwa) // 10)
    for i in range(0, len(result.beta), beta_step):
        mask = np.isfinite(ay_g[i, :]) & np.isfinite(result.mz[i, :])
        ax.plot(ay_g[i, mask], result.mz[i, mask], color="blue", alpha=0.72, linewidth=1.0)
    for j in range(0, len(result.hwa), hwa_step):
        mask = np.isfinite(ay_g[:, j]) & np.isfinite(result.mz[:, j])
        ax.plot(ay_g[mask, j], result.mz[mask, j], color="red", alpha=0.72, linewidth=1.0)
    ax.axhline(0.0, color="black", linewidth=0.8, alpha=0.55)
    ax.axvline(0.0, color="black", linewidth=0.8, alpha=0.55)
    ax.set_xlabel("lateral acceleration ay (g)")
    ax.set_ylabel("yaw moment Mz (N*m)")
    ax.set_title(title)
    ax.grid(True, alpha=0.25)
    if show_legend:
        blue_proxy, = ax.plot([], [], color="blue", label="constant beta")
        red_proxy, = ax.plot([], [], color="red", label="constant roadwheel angle")
        ax.legend(handles=[blue_proxy, red_proxy], loc="best")


def _add_ymd_authority_page(
    pdf: PdfPages,
    result: YMDResult,
    trim_rows: list[dict[str, float]],
    summary: dict[str, float],
) -> None:
    fig, axs = plt.subplots(2, 2, figsize=(11, 8.0))
    beta_idx, hwa_idx = _nearest_grid_index(result)
    beta_deg = np.rad2deg(result.beta)
    hwa_deg = np.rad2deg(result.hwa)

    axs[0, 0].plot(hwa_deg, result.mz[beta_idx, :], color="#1f77b4", linewidth=1.8)
    axs[0, 0].axhline(0.0, color="black", linewidth=0.8, alpha=0.55)
    axs[0, 0].axvline(0.0, color="black", linewidth=0.8, alpha=0.55)
    axs[0, 0].set_xlabel("roadwheel angle (deg)")
    axs[0, 0].set_ylabel("yaw moment Mz (N*m)")
    axs[0, 0].set_title(
        f"Mz vs steer near beta=0: "
        f"{float(summary['yaw_moment_hwa_gradient_nm_per_deg']):.1f} N*m/deg"
    )
    axs[0, 0].grid(True, alpha=0.25)

    axs[0, 1].plot(beta_deg, result.mz[:, hwa_idx], color="#d62728", linewidth=1.8)
    axs[0, 1].axhline(0.0, color="black", linewidth=0.8, alpha=0.55)
    axs[0, 1].axvline(0.0, color="black", linewidth=0.8, alpha=0.55)
    axs[0, 1].set_xlabel("sideslip beta (deg)")
    axs[0, 1].set_ylabel("yaw moment Mz (N*m)")
    axs[0, 1].set_title(
        f"Mz vs beta near steer=0: "
        f"{float(summary['yaw_moment_beta_gradient_nm_per_deg']):.1f} N*m/deg"
    )
    axs[0, 1].grid(True, alpha=0.25)

    if trim_rows:
        beta_trim = np.array([row["beta_deg"] for row in trim_rows], dtype=float)
        hwa_trim = np.array([row["hwa_deg"] for row in trim_rows], dtype=float)
        ay_trim = np.array([row["ay_g"] for row in trim_rows], dtype=float)
        order = np.argsort(ay_trim)
        axs[1, 0].plot(
            ay_trim[order],
            hwa_trim[order],
            marker="o",
            markersize=3,
            color="#1f77b4",
        )
        axs[1, 1].plot(
            ay_trim[order],
            beta_trim[order],
            marker="o",
            markersize=3,
            color="#607D3B",
        )

    axs[1, 0].axhline(0.0, color="black", linewidth=0.8, alpha=0.55)
    axs[1, 0].axvline(0.0, color="black", linewidth=0.8, alpha=0.55)
    axs[1, 0].set_xlabel("trim lateral acceleration ay (g)")
    axs[1, 0].set_ylabel("trim roadwheel angle (deg)")
    axs[1, 0].set_title(
        f"Trim steer gradient: "
        f"{float(summary['trim_steer_gradient_deg_per_g']):.2f} deg/g"
    )
    axs[1, 0].grid(True, alpha=0.25)

    axs[1, 1].axhline(0.0, color="black", linewidth=0.8, alpha=0.55)
    axs[1, 1].axvline(0.0, color="black", linewidth=0.8, alpha=0.55)
    axs[1, 1].set_xlabel("trim lateral acceleration ay (g)")
    axs[1, 1].set_ylabel("trim sideslip beta (deg)")
    axs[1, 1].set_title(
        f"Trim beta gradient: "
        f"{float(summary['trim_beta_gradient_deg_per_g']):.2f} deg/g"
    )
    axs[1, 1].grid(True, alpha=0.25)

    fig.suptitle("YMD Local Authority and Zero-Moment Trim", fontsize=15, weight="bold")
    fig.tight_layout()
    pdf.savefig(fig)
    plt.close(fig)


def _add_ymd_trim_page(
    pdf: PdfPages,
    trim_rows: list[dict[str, float]],
    summary: dict[str, float],
) -> None:
    fig, axs = plt.subplots(1, 2, figsize=(13, 5.8))
    if trim_rows:
        beta = np.array([row["beta_deg"] for row in trim_rows], dtype=float)
        hwa = np.array([row["hwa_deg"] for row in trim_rows], dtype=float)
        ay = np.array([row["ay_g"] for row in trim_rows], dtype=float)
        order = np.argsort(ay)
        axs[0].plot(ay[order], hwa[order], marker="o", markersize=3)
        axs[0].set_xlabel("trim lateral acceleration ay (g)")
        axs[0].set_ylabel("trim HWA / roadwheel angle (deg)")
        axs[0].set_title("Zero-yaw trim steer demand")
        axs[0].grid(True, alpha=0.25)

        axs[1].plot(ay[order], beta[order], marker="o", markersize=3, color="#607D3B")
        axs[1].set_xlabel("trim lateral acceleration ay (g)")
        axs[1].set_ylabel("trim sideslip beta (deg)")
        axs[1].set_title("Zero-yaw trim sideslip")
        axs[1].grid(True, alpha=0.25)
    fig.suptitle(
        f"Trim peak |ay| = {float(summary['trim_peak_lateral_accel_abs_g']):.3f} g",
        fontsize=15,
    )
    fig.tight_layout()
    pdf.savefig(fig)
    plt.close(fig)


def _add_ymd_speed_sweep_summary_page(
    pdf: PdfPages,
    rows: list[dict[str, float]],
    summary: dict[str, float],
) -> None:
    speed = np.array([row["speed_mps"] for row in rows], dtype=float)
    peak_ay = np.array([row["peak_lateral_accel_abs_g"] for row in rows], dtype=float)
    trim_ay = np.array([row["trim_peak_lateral_accel_abs_g"] for row in rows], dtype=float)
    peak_mz = np.array([row["peak_abs_yaw_moment_nm"] for row in rows], dtype=float)
    mz_range = np.array([row["yaw_moment_range_nm"] for row in rows], dtype=float)
    hwa_grad = np.array(
        [row["yaw_moment_hwa_gradient_nm_per_deg"] for row in rows],
        dtype=float,
    )
    beta_grad = np.array(
        [row["yaw_moment_beta_gradient_nm_per_deg"] for row in rows],
        dtype=float,
    )
    trim_hwa_grad = np.array(
        [row["trim_steer_gradient_deg_per_g"] for row in rows],
        dtype=float,
    )
    trim_beta_grad = np.array(
        [row["trim_beta_gradient_deg_per_g"] for row in rows],
        dtype=float,
    )

    fig, axs = plt.subplots(2, 2, figsize=(11, 8.0))

    axs[0, 0].plot(speed, peak_ay, marker="o", label="map peak |ay|")
    axs[0, 0].plot(speed, trim_ay, marker="o", label="trim peak |ay|")
    axs[0, 0].set_xlabel("speed (m/s)")
    axs[0, 0].set_ylabel("lateral acceleration (g)")
    axs[0, 0].set_title(
        f"Peak trim |ay| {float(summary['speed_sweep_peak_trim_lateral_accel_abs_g']):.3f} g "
        f"@ {float(summary['speed_sweep_peak_trim_lateral_accel_speed_mps']):.1f} m/s"
    )
    axs[0, 0].legend(loc="best")
    axs[0, 0].grid(True, alpha=0.25)

    axs[0, 1].plot(speed, peak_mz, marker="o", label="peak |Mz|")
    axs[0, 1].plot(speed, mz_range, marker="o", label="Mz range")
    axs[0, 1].set_xlabel("speed (m/s)")
    axs[0, 1].set_ylabel("yaw moment (N*m)")
    axs[0, 1].set_title(
        f"Peak |Mz| {float(summary['speed_sweep_peak_abs_yaw_moment_nm']):.0f} N*m "
        f"@ {float(summary['speed_sweep_peak_abs_yaw_moment_speed_mps']):.1f} m/s"
    )
    axs[0, 1].legend(loc="best")
    axs[0, 1].grid(True, alpha=0.25)

    axs[1, 0].plot(speed, hwa_grad, marker="o", label="dMz/dsteer")
    axs[1, 0].plot(speed, beta_grad, marker="o", label="dMz/dbeta")
    axs[1, 0].axhline(0.0, color="black", linewidth=0.8, alpha=0.55)
    axs[1, 0].set_xlabel("speed (m/s)")
    axs[1, 0].set_ylabel("yaw moment gradient (N*m/deg)")
    axs[1, 0].set_title("Local yaw authority gradients")
    axs[1, 0].legend(loc="best")
    axs[1, 0].grid(True, alpha=0.25)

    axs[1, 1].plot(speed, trim_hwa_grad, marker="o", label="trim steer")
    axs[1, 1].plot(speed, trim_beta_grad, marker="o", label="trim beta")
    axs[1, 1].axhline(0.0, color="black", linewidth=0.8, alpha=0.55)
    axs[1, 1].set_xlabel("speed (m/s)")
    axs[1, 1].set_ylabel("trim gradient (deg/g)")
    axs[1, 1].set_title("Zero-moment trim gradients")
    axs[1, 1].legend(loc="best")
    axs[1, 1].grid(True, alpha=0.25)

    fig.suptitle("YMD Speed Sweep Summary", fontsize=15, weight="bold")
    fig.tight_layout()
    pdf.savefig(fig)
    plt.close(fig)


def _add_ymd_speed_extremes_page(
    pdf: PdfPages,
    sweep: YMDSpeedSweepResult,
) -> None:
    extreme_results = _speed_sweep_extreme_results(sweep)
    if not extreme_results:
        return

    fig, axs = plt.subplots(1, len(extreme_results), figsize=(13, 5.8), squeeze=False)
    for ax, result in zip(axs[0], extreme_results):
        result_summary, trim_rows = summarize_ymd(result)
        title = (
            f"V={result.speed:.1f} m/s | "
            f"trim |ay|={float(result_summary['trim_peak_lateral_accel_abs_g']):.2f} g | "
            f"peak |Mz|={float(result_summary['peak_abs_yaw_moment_nm']):.0f} N*m"
        )
        _plot_ymd_contour_axes(
            fig,
            ax,
            result,
            trim_rows,
            title=title,
            colorbar_label="Mz (N*m)",
        )

    fig.suptitle("YMD Maps at Speed Sweep Bounds", fontsize=15, weight="bold")
    fig.tight_layout()
    pdf.savefig(fig)
    plt.close(fig)


def _add_ymd_speed_extremes_wireframe_page(
    pdf: PdfPages,
    sweep: YMDSpeedSweepResult,
) -> None:
    extreme_results = _speed_sweep_extreme_results(sweep)
    if not extreme_results:
        return

    fig, axs = plt.subplots(1, len(extreme_results), figsize=(13, 5.8), squeeze=False)
    xlim, ylim = _ymd_wireframe_limits(extreme_results)

    for ax, result in zip(axs[0], extreme_results):
        _plot_ymd_wireframe_axes(
            ax,
            result,
            title=f"V={result.speed:.1f} m/s",
            show_legend=True,
        )
        if xlim is not None:
            ax.set_xlim(*xlim)
        if ylim is not None:
            ax.set_ylim(*ylim)

    fig.suptitle("YMD Wireframe Families at Speed Sweep Bounds", fontsize=15, weight="bold")
    fig.tight_layout()
    pdf.savefig(fig)
    plt.close(fig)


def _speed_sweep_extreme_results(sweep: YMDSpeedSweepResult) -> list[YMDResult]:
    if not sweep.results:
        return []

    sorted_results = sorted(sweep.results, key=lambda result: result.speed)
    extreme_results = [sorted_results[0]]
    if not np.isclose(sorted_results[-1].speed, sorted_results[0].speed):
        extreme_results.append(sorted_results[-1])
    return extreme_results


def _ymd_wireframe_limits(
    results: list[YMDResult],
) -> tuple[tuple[float, float] | None, tuple[float, float] | None]:
    ay_chunks = [
        (result.ay[np.isfinite(result.ay)] / G).ravel()
        for result in results
        if np.any(np.isfinite(result.ay))
    ]
    mz_chunks = [
        result.mz[np.isfinite(result.mz)].ravel()
        for result in results
        if np.any(np.isfinite(result.mz))
    ]
    ay_values = np.concatenate(ay_chunks) if ay_chunks else np.array([], dtype=np.float64)
    mz_values = np.concatenate(mz_chunks) if mz_chunks else np.array([], dtype=np.float64)

    xlim = _padded_limits(ay_values)
    ylim = _padded_limits(mz_values)
    return xlim, ylim


def _padded_limits(
    values: FloatArray,
    *,
    pad_fraction: float = 0.06,
) -> tuple[float, float] | None:
    finite = values[np.isfinite(values)]
    if finite.size == 0:
        return None

    low = float(np.nanmin(finite))
    high = float(np.nanmax(finite))
    if np.isclose(low, high):
        pad = max(1.0, abs(low) * pad_fraction)
    else:
        pad = (high - low) * pad_fraction
    return low - pad, high + pad


def _add_ymd_speed_sweep_carpet_page(
    pdf: PdfPages,
    sweep: YMDSpeedSweepResult,
) -> None:
    fig = plt.figure(figsize=(11, 8.0))
    ax = fig.add_subplot(111, projection="3d")

    for result in sweep.results:
        ay_g = result.ay / G
        mz = result.mz
        speed_grid = np.full_like(result.ay, result.speed, dtype=float)
        beta_step = max(1, len(result.beta) // 10)
        hwa_step = max(1, len(result.hwa) // 10)

        for i in range(0, len(result.beta), beta_step):
            mask = np.isfinite(ay_g[i, :]) & np.isfinite(mz[i, :])
            if np.any(mask):
                ax.plot(
                    ay_g[i, mask],
                    mz[i, mask],
                    speed_grid[i, mask],
                    color="blue",
                    linewidth=0.75,
                    alpha=0.55,
                )

        for j in range(0, len(result.hwa), hwa_step):
            mask = np.isfinite(ay_g[:, j]) & np.isfinite(mz[:, j])
            if np.any(mask):
                ax.plot(
                    ay_g[mask, j],
                    mz[mask, j],
                    speed_grid[mask, j],
                    color="red",
                    linewidth=0.75,
                    alpha=0.55,
                )

    ax.set_xlabel("lateral acceleration ay (g)", labelpad=10)
    ax.set_ylabel("yaw moment Mz (N*m)", labelpad=10)
    ax.set_zlabel("speed (m/s)", labelpad=10)
    ax.set_title("YMD Speed Sweep Carpet")
    ax.view_init(elev=24, azim=-58)
    ax.set_box_aspect((1.25, 1.35, 1.0))
    blue_proxy, = ax.plot([], [], [], color="blue", label="constant beta")
    red_proxy, = ax.plot([], [], [], color="red", label="constant roadwheel angle")
    ax.legend(handles=[blue_proxy, red_proxy], loc="upper right", fontsize=9)
    fig.tight_layout()
    pdf.savefig(fig)
    plt.close(fig)


def _peak_trim_row(rows: list[dict[str, float]]) -> dict[str, float]:
    if not rows:
        return {}
    return max(rows, key=lambda row: abs(float(row["ay_g"])))


def _trim_extreme(rows: list[dict[str, float]], selector) -> float:
    if not rows:
        return float("nan")
    return float(selector(row["ay_g"] for row in rows))


def _nearest_grid_index(result: YMDResult) -> tuple[int, int]:
    beta_idx = int(np.nanargmin(np.abs(result.beta)))
    hwa_idx = int(np.nanargmin(np.abs(result.hwa)))
    return beta_idx, hwa_idx


def _safe_ratio(numerator: float, denominator: float) -> float:
    if not np.isfinite(numerator) or not np.isfinite(denominator):
        return float("nan")
    if abs(denominator) <= 1e-12:
        return float("nan")
    return float(numerator / denominator)


def _local_linear_slope(
    x: FloatArray,
    y: FloatArray,
    *,
    center: float = 0.0,
    points: int = 7,
) -> float:
    valid = np.isfinite(x) & np.isfinite(y)
    if np.count_nonzero(valid) < 2:
        return float("nan")

    x_valid = x[valid]
    y_valid = y[valid]
    order = np.argsort(np.abs(x_valid - center))
    selected = order[: max(2, min(points, len(order)))]
    if len(selected) < 2:
        return float("nan")
    return float(np.polyfit(x_valid[selected], y_valid[selected], 1)[0])


def _centerline_yaw_moment_gradient(result: YMDResult, *, axis: str) -> float:
    beta_idx, hwa_idx = _nearest_grid_index(result)
    if axis == "hwa":
        x = np.rad2deg(result.hwa)
        y = result.mz[beta_idx, :]
    elif axis == "beta":
        x = np.rad2deg(result.beta)
        y = result.mz[:, hwa_idx]
    else:
        raise ValueError(f"Unsupported YMD centerline axis: {axis}")
    return _local_linear_slope(x, y)


def _trim_linear_slope(rows: list[dict[str, float]], *, y_key: str) -> float:
    if len(rows) < 2:
        return float("nan")

    ay = np.array([row["ay_g"] for row in rows], dtype=float)
    y = np.array([row[y_key] for row in rows], dtype=float)
    valid = np.isfinite(ay) & np.isfinite(y)
    if np.count_nonzero(valid) < 2:
        return float("nan")

    ay_valid = ay[valid]
    y_valid = y[valid]
    max_abs_ay = float(np.nanmax(np.abs(ay_valid)))
    window = min(1.0, 0.65 * max_abs_ay) if max_abs_ay > 0.0 else 1.0
    near = np.abs(ay_valid) <= window
    if np.count_nonzero(near) >= 2:
        ay_valid = ay_valid[near]
        y_valid = y_valid[near]

    return float(np.polyfit(ay_valid, y_valid, 1)[0])


def summarize_ymd_speed_sweep(
    sweep: YMDSpeedSweepResult,
) -> tuple[dict[str, float], list[dict[str, float]]]:
    rows: list[dict[str, float]] = []
    for result in sweep.results:
        summary, _trim_rows = summarize_ymd(result)
        rows.append(
            {
                "speed_mps": summary["speed_mps"],
                "converged_fraction": summary["converged_fraction"],
                "peak_lateral_accel_abs_g": summary["peak_lateral_accel_abs_g"],
                "trim_peak_lateral_accel_abs_g": summary[
                    "trim_peak_lateral_accel_abs_g"
                ],
                "peak_abs_yaw_moment_nm": summary["peak_abs_yaw_moment_nm"],
                "yaw_moment_range_nm": summary["yaw_moment_range_nm"],
                "trim_steer_gradient_deg_per_g": summary[
                    "trim_steer_gradient_deg_per_g"
                ],
                "trim_beta_gradient_deg_per_g": summary[
                    "trim_beta_gradient_deg_per_g"
                ],
                "yaw_moment_hwa_gradient_nm_per_deg": summary[
                    "yaw_moment_hwa_gradient_nm_per_deg"
                ],
                "yaw_moment_beta_gradient_nm_per_deg": summary[
                    "yaw_moment_beta_gradient_nm_per_deg"
                ],
                "trim_points_count": summary["trim_points_count"],
            }
        )

    if not rows:
        return {}, rows

    peak_ay = _max_row(rows, "peak_lateral_accel_abs_g")
    peak_trim = _max_row(rows, "trim_peak_lateral_accel_abs_g")
    peak_mz = _max_row(rows, "peak_abs_yaw_moment_nm")

    summary = {
        "speed_sweep_min_speed_mps": float(min(row["speed_mps"] for row in rows)),
        "speed_sweep_max_speed_mps": float(max(row["speed_mps"] for row in rows)),
        "speed_sweep_peak_lateral_accel_abs_g": float(
            peak_ay.get("peak_lateral_accel_abs_g", np.nan)
        ),
        "speed_sweep_peak_lateral_accel_speed_mps": float(
            peak_ay.get("speed_mps", np.nan)
        ),
        "speed_sweep_peak_trim_lateral_accel_abs_g": float(
            peak_trim.get("trim_peak_lateral_accel_abs_g", np.nan)
        ),
        "speed_sweep_peak_trim_lateral_accel_speed_mps": float(
            peak_trim.get("speed_mps", np.nan)
        ),
        "speed_sweep_peak_abs_yaw_moment_nm": float(
            peak_mz.get("peak_abs_yaw_moment_nm", np.nan)
        ),
        "speed_sweep_peak_abs_yaw_moment_speed_mps": float(
            peak_mz.get("speed_mps", np.nan)
        ),
    }
    return summary, rows


def _max_row(rows: list[dict[str, float]], key: str) -> dict[str, float]:
    valid = [row for row in rows if np.isfinite(row.get(key, np.nan))]
    if not valid:
        return {}
    return max(valid, key=lambda row: float(row[key]))


def generate_ymd_speed_sweep(
    vehicle: VehicleParams,
    base_config: YMDConfig,
    speeds: FloatArray,
) -> YMDSpeedSweepResult:
    """
    Generate YMD carpets across multiple velocities.
    """
    results: list[YMDResult] = []

    print("=" * 72)
    print("Generating YMD speed sweep")
    print(f"Speeds: {speeds}")
    print("=" * 72, flush=True)

    for k, speed in enumerate(speeds):
        print(f"\n[{k + 1}/{len(speeds)}] YMD at V = {speed:.2f} m/s", flush=True)

        config = YMDConfig(
            speed=float(speed),
            beta_min_deg=base_config.beta_min_deg,
            beta_max_deg=base_config.beta_max_deg,
            beta_points=base_config.beta_points,
            hwa_min_deg=base_config.hwa_min_deg,
            hwa_max_deg=base_config.hwa_max_deg,
            hwa_points=base_config.hwa_points,
            yaw_rate=base_config.yaw_rate,
            max_iter=base_config.max_iter,
            tol_ay=base_config.tol_ay,
            relaxation=base_config.relaxation,
            verbose=False,
            warn_tire_load_range=False,
        )

        result = generate_ymd(vehicle, config)
        results.append(result)

    print("\nYMD speed sweep complete.")
    print("=" * 72, flush=True)

    return YMDSpeedSweepResult(
        speeds=np.asarray(speeds, dtype=np.float64),
        results=results,
    )


def plot_ymd_speed_sweep_3d(
    sweep: YMDSpeedSweepResult,
    output_path: str | Path | None = None,
) -> None:
    """
    Plot stacked YMD carpets across velocity.

    Axes:
        x = lateral acceleration, ay ($g$)
        y = yaw moment, Mz ($N m$)
        z = speed, V (m/s)

    Blue lines = constant beta isolines.
    Red lines  = constant delta_hwa isolines.
    """
    fig = plt.figure(figsize=(11.0, 8.0))
    ax = fig.add_subplot(111, projection="3d")

    for result in sweep.results:
        ay_g = result.ay / G
        mz = result.mz
        speed = result.speed

        beta_deg = np.rad2deg(result.beta)
        hwa_deg = np.rad2deg(result.hwa)

        speed_grid = np.full_like(result.ay, speed, dtype=float)

        # Blue family: constant beta lines
        beta_step = max(1, len(beta_deg) // 14)

        for i, _beta in enumerate(beta_deg):
            if i % beta_step != 0 and i not in (0, len(beta_deg) - 1):
                continue

            mask = np.isfinite(ay_g[i, :]) & np.isfinite(mz[i, :])

            if np.any(mask):
                ax.plot(
                    ay_g[i, mask],
                    mz[i, mask],
                    speed_grid[i, mask],
                    color="blue",
                    linewidth=0.85,
                    alpha=0.72,
                )

        # Red family: constant handwheel-angle lines
        hwa_step = max(1, len(hwa_deg) // 14)

        for j, _hwa in enumerate(hwa_deg):
            if j % hwa_step != 0 and j not in (0, len(hwa_deg) - 1):
                continue

            mask = np.isfinite(ay_g[:, j]) & np.isfinite(mz[:, j])

            if np.any(mask):
                ax.plot(
                    ay_g[mask, j],
                    mz[mask, j],
                    speed_grid[mask, j],
                    color="red",
                    linewidth=0.85,
                    alpha=0.72,
                )

    ax.set_xlabel(r"Lateral Acceleration, $a_y$ ($g$)", labelpad=10)
    ax.set_ylabel(r"Yaw Moment, $M_z$ ($N m$)", labelpad=10)
    ax.set_zlabel(r"Speed, $V$ ($m/s$)", labelpad=10)

    ax.set_title("First-Principles Moment-Method YMD Speed Sweep")

    # Good initial slide view.
    ax.view_init(elev=24, azim=-58)

    # Manual visual scaling; do not use raw data ranges.
    ax.set_box_aspect((1.25, 1.35, 1.0))

    blue_proxy, = ax.plot(
        [],
        [],
        [],
        color="blue",
        linewidth=1.5,
        label=r"constant $\beta$",
    )
    red_proxy, = ax.plot(
        [],
        [],
        [],
        color="red",
        linewidth=1.5,
        label=r"constant $\delta_{rwa}$",
    )

    ax.legend(
        handles=[blue_proxy, red_proxy],
        loc="upper right",
        frameon=True,
        fontsize=9,
    )

    fig.tight_layout()

    if output_path is not None:
        fig.savefig(output_path, dpi=300)
        print(f"Saved 3D YMD speed sweep plot: {output_path}")

    plt.show()


def plot_ymd_speed_sweep_surface(
    sweep: YMDSpeedSweepResult,
    output_path: str | Path | None = None,
) -> None:
    """
    Plot YMD as stacked beta/hwa surfaces across speed.

    Axes:
        x = beta (deg)
        y = delta_hwa (deg)
        z = speed (m/s)

    Color:
        yaw moment Mz ($N m$)
    """
    fig = plt.figure(figsize=(11.0, 8.0))
    ax = fig.add_subplot(111, projection="3d")

    max_abs_mz = max(float(np.nanmax(np.abs(result.mz))) for result in sweep.results)

    cmap = plt.get_cmap("coolwarm")

    for result in sweep.results:
        beta_deg = np.rad2deg(result.beta)
        hwa_deg = np.rad2deg(result.hwa)

        beta_grid, hwa_grid = np.meshgrid(beta_deg, hwa_deg, indexing="ij")
        speed_grid = np.full_like(beta_grid, result.speed, dtype=float)

        normalized_mz = 0.5 + 0.5 * result.mz / max_abs_mz
        normalized_mz = np.clip(normalized_mz, 0.0, 1.0)

        facecolors = cmap(normalized_mz)

        ax.plot_surface(
            beta_grid,
            hwa_grid,
            speed_grid,
            facecolors=facecolors,
            linewidth=0.0,
            antialiased=True,
            shade=False,
            alpha=0.78,
        )

    ax.set_xlabel(r"Sideslip, $\beta$ (deg)", labelpad=10)
    ax.set_ylabel(r"Roadwheel angle, $\delta_{rwa}$ (deg)", labelpad=10)
    ax.set_zlabel(r"Speed, $V$ ($m/s$)", labelpad=10)

    ax.set_title(r"YMD Map Speed Sweep, colored by $M_z$")

    ax.view_init(elev=24, azim=-55)
    ax.set_box_aspect((1.2, 1.2, 1.0))

    mappable = plt.cm.ScalarMappable(cmap=cmap)
    mappable.set_array([])
    mappable.set_clim(-max_abs_mz, max_abs_mz)

    cbar = fig.colorbar(mappable, ax=ax, shrink=0.70, pad=0.12)
    cbar.set_label(r"Yaw Moment, $M_z$ ($N m$)")

    fig.tight_layout()

    if output_path is not None:
        fig.savefig(output_path, dpi=300)
        print(f"Saved 3D YMD surface plot: {output_path}")

    plt.show()


def plot_ymd_speed_sweep_hull_surfaces(
    sweep: YMDSpeedSweepResult,
    output_path: str | Path | None = None,
    beta_surface_count: int = 3,
    hwa_surface_count: int = 3,
    hull_alpha: float = 0.10,
    surface_alpha: float = 0.18,
    show_slice_wireframes: bool = True,
) -> None:
    """
    Plot a convex hull shell around the full YMD speed sweep, plus a small
    number of selected interior constant-beta and constant-delta_hwa surfaces.

    Axes:
        x = lateral acceleration, ay ($g$)
        y = yaw moment, Mz ($N m$)
        z = speed, V (m/s)

    Gray transparent shell:
        convex hull of all finite YMD points

    Blue transparent surfaces:
        selected constant beta surfaces

    Red transparent surfaces:
        selected constant delta_hwa surfaces

    This version intentionally avoids plotting boundary isoline surfaces because
    the convex hull already represents the outer envelope. The blue/red surfaces
    are used as internal slices through the volume.
    """
    if not sweep.results:
        raise ValueError("No YMD sweep results provided.")

    # -------------------------------------------------------------------------
    # Collect all finite points for convex hull
    # -------------------------------------------------------------------------
    point_blocks: list[FloatArray] = []

    for result in sweep.results:
        ay_g = result.ay / G
        mz = result.mz
        speed_grid = np.full_like(result.ay, result.speed, dtype=float)

        mask = np.isfinite(ay_g) & np.isfinite(mz) & np.isfinite(speed_grid)

        if np.any(mask):
            points = np.column_stack(
                [
                    ay_g[mask],
                    mz[mask],
                    speed_grid[mask],
                ]
            )
            point_blocks.append(points)

    if not point_blocks:
        raise ValueError("No finite YMD points found for hull plot.")

    points_all = np.vstack(point_blocks)
    points_all = np.unique(points_all, axis=0)

    if points_all.shape[0] < 4:
        raise ValueError("Need at least 4 unique finite points for a 3D convex hull.")

    hull = ConvexHull(points_all)

    # -------------------------------------------------------------------------
    # Figure
    # -------------------------------------------------------------------------
    fig = plt.figure(figsize=(12.0, 8.5))
    ax = fig.add_subplot(111, projection="3d")

    # -------------------------------------------------------------------------
    # Convex hull shell
    # -------------------------------------------------------------------------
    hull_faces = [points_all[simplex] for simplex in hull.simplices]

    hull_collection = Poly3DCollection(
        hull_faces,
        facecolor="lightgray",
        edgecolor="gray",
        linewidth=0.20,
        alpha=hull_alpha,
    )

    ax.add_collection3d(hull_collection)

    # -------------------------------------------------------------------------
    # Select only interior beta/hwa slices
    # -------------------------------------------------------------------------
    beta_vals = sweep.results[0].beta
    hwa_vals = sweep.results[0].hwa

    def interior_indices(n: int, count: int) -> NDArray[np.int_]:
        """
        Return evenly spaced interior indices, excluding the boundary indices.

        Example:
            n=61, count=3 -> roughly [15, 30, 45]
        """
        if count <= 0:
            return np.array([], dtype=int)

        if n <= 2:
            return np.arange(n, dtype=int)

        # Use 15% to 85% range to avoid outermost envelope surfaces.
        lo = int(round(0.15 * (n - 1)))
        hi = int(round(0.85 * (n - 1)))

        return np.unique(np.linspace(lo, hi, count, dtype=int))

    beta_indices = interior_indices(len(beta_vals), beta_surface_count)
    hwa_indices = interior_indices(len(hwa_vals), hwa_surface_count)

    speeds = np.asarray([result.speed for result in sweep.results], dtype=float)

    # -------------------------------------------------------------------------
    # Blue surfaces: beta fixed, sweep hwa and speed
    # -------------------------------------------------------------------------
    for beta_idx in beta_indices:
        ay_surface_list: list[FloatArray] = []
        mz_surface_list: list[FloatArray] = []
        speed_surface_list: list[FloatArray] = []

        for result in sweep.results:
            ay_surface_list.append(result.ay[beta_idx, :] / G)
            mz_surface_list.append(result.mz[beta_idx, :])
            speed_surface_list.append(
                np.full_like(result.hwa, result.speed, dtype=float)
            )

        ay_surface_arr = np.vstack(ay_surface_list)
        mz_surface_arr = np.vstack(mz_surface_list)
        speed_surface_arr = np.vstack(speed_surface_list)

        if np.all(~np.isfinite(ay_surface_arr)) or np.all(
            ~np.isfinite(mz_surface_arr)
        ):
            continue

        ax.plot_surface(
            ay_surface_arr,
            mz_surface_arr,
            speed_surface_arr,
            color="blue",
            alpha=surface_alpha,
            linewidth=0.15,
            edgecolor="blue",
            antialiased=True,
            shade=False,
        )

        if show_slice_wireframes:
            ax.plot_wireframe(
                ay_surface_arr,
                mz_surface_arr,
                speed_surface_arr,
                color="blue",
                linewidth=0.45,
                alpha=0.35,
                rstride=1,
                cstride=max(1, ay_surface_arr.shape[1] // 8),
            )

    # -------------------------------------------------------------------------
    # Red surfaces: hwa fixed, sweep beta and speed
    # -------------------------------------------------------------------------
    for hwa_idx in hwa_indices:
        hwa_ay_surface_list: list[FloatArray] = []
        hwa_mz_surface_list: list[FloatArray] = []
        hwa_speed_surface_list: list[FloatArray] = []

        for result in sweep.results:
            hwa_ay_surface_list.append(result.ay[:, hwa_idx] / G)
            hwa_mz_surface_list.append(result.mz[:, hwa_idx])
            hwa_speed_surface_list.append(
                np.full_like(result.beta, result.speed, dtype=float)
            )

        ay_surface_arr = np.vstack(hwa_ay_surface_list)
        mz_surface_arr = np.vstack(hwa_mz_surface_list)
        speed_surface_arr = np.vstack(hwa_speed_surface_list)

        if np.all(~np.isfinite(ay_surface_arr)) or np.all(
            ~np.isfinite(mz_surface_arr)
        ):
            continue

        ax.plot_surface(
            ay_surface_arr,
            mz_surface_arr,
            speed_surface_arr,
            color="red",
            alpha=surface_alpha,
            linewidth=0.15,
            edgecolor="red",
            antialiased=True,
            shade=False,
        )

        if show_slice_wireframes:
            ax.plot_wireframe(
                ay_surface_arr,
                mz_surface_arr,
                speed_surface_arr,
                color="red",
                linewidth=0.45,
                alpha=0.35,
                rstride=1,
                cstride=max(1, ay_surface_arr.shape[1] // 8),
            )

    # -------------------------------------------------------------------------
    # Add a light outline of each speed slice for readability
    # -------------------------------------------------------------------------
    for result in sweep.results:
        ay_g = result.ay / G
        mz = result.mz
        speed_grid = np.full_like(result.ay, result.speed, dtype=float)

        # Only plot outer-ish beta/hwa lines, not the full carpet.
        for i in (0, len(result.beta) - 1):
            mask = np.isfinite(ay_g[i, :]) & np.isfinite(mz[i, :])
            if np.any(mask):
                ax.plot(
                    ay_g[i, mask],
                    mz[i, mask],
                    speed_grid[i, mask],
                    color="blue",
                    linewidth=0.7,
                    alpha=0.45,
                )

        for j in (0, len(result.hwa) - 1):
            mask = np.isfinite(ay_g[:, j]) & np.isfinite(mz[:, j])
            if np.any(mask):
                ax.plot(
                    ay_g[mask, j],
                    mz[mask, j],
                    speed_grid[mask, j],
                    color="red",
                    linewidth=0.7,
                    alpha=0.45,
                )

    # -------------------------------------------------------------------------
    # Axes / styling
    # -------------------------------------------------------------------------
    ax.set_xlabel(r"Lateral Acceleration, $a_y$ ($g$)", labelpad=10)
    ax.set_ylabel(r"Yaw Moment, $M_z$ ($N m$)", labelpad=10)
    ax.set_zlabel(r"Speed, $V$ ($m/s$)", labelpad=10)

    ax.set_title(
        r"YMD Speed Sweep: Convex Envelope with Selected "
        r"$\beta$ and $\delta_{rwa}$ Slices"
    )

    ax.view_init(elev=24, azim=-58)
    ax.set_box_aspect((1.25, 1.35, 1.0))

    ay_abs = np.nanmax(np.abs(points_all[:, 0]))
    mz_abs = np.nanmax(np.abs(points_all[:, 1]))

    ax.set_xlim(-1.08 * ay_abs, 1.08 * ay_abs)
    ax.set_ylim(-1.08 * mz_abs, 1.08 * mz_abs)
    ax.set_zlim(np.min(speeds), np.max(speeds))

    # Legend proxies.
    hull_proxy = mpatches.Patch(
        facecolor="lightgray",
        edgecolor="gray",
        alpha=hull_alpha,
        label="convex YMD envelope",
    )

    beta_proxy, = ax.plot(
        [],
        [],
        [],
        color="blue",
        linewidth=2.0,
        label=r"selected constant $\beta$ slices",
    )

    hwa_proxy, = ax.plot(
        [],
        [],
        [],
        color="red",
        linewidth=2.0,
        label=r"selected constant $\delta_{rwa}$ slices",
    )

    ax.legend(
        handles=[hull_proxy, beta_proxy, hwa_proxy],
        loc="upper right",
        frameon=True,
        fontsize=9,
    )

    fig.tight_layout()

    if output_path is not None:
        fig.savefig(output_path, dpi=300)
        print(f"Saved YMD hull/surface plot: {output_path}")

    plt.show()


def main() -> None:
    import sys

    repo_root = REPO_ROOT
    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from _2_EnvelopeSim.vehicle_yaml import load_vehicle_yaml, project_vehicle_yaml

    config_path = DEFAULT_YMD_CONFIG
    ymd_report_config = load_ymd_config(config_path)
    vehicle_template = ymd_report_config.get("vehicle_template", "../../vehicle.yml")
    vehicle_path = resolve_ymd_output_path(config_path, vehicle_template)
    projection = project_vehicle_yaml(
        load_vehicle_yaml(vehicle_path),
        repo_root=repo_root,
    )
    vehicle = projection.ymd

    print("Aero values from vehicle.yml nominal ride height:")
    print(f"  reference speed = {projection.summary['reference_speed_m_per_s']:.3f} m/s")
    print(f"  downforce       = {projection.summary['downforce_n']:.3f} N")
    print(f"  drag            = {projection.summary['drag_n']:.3f} N")
    print(f"  ClA             = {vehicle.cl_a:.4f} m^2")
    print(f"  CdA             = {vehicle.cd_a:.4f} m^2")
    print(f"  front balance   = {100.0 * vehicle.aero_balance_front:.1f}%")

    print("\nVehicle values from vehicle.yml:")
    print(f"  mass           = {vehicle.mass:.2f} kg")
    print(f"  wheelbase      = {vehicle.wheelbase:.4f} m")
    print(f"  front track    = {vehicle.track_front:.4f} m")
    print(f"  rear track     = {vehicle.track_rear:.4f} m")
    print(f"  CG height      = {vehicle.cg_height:.4f} m")
    print(f"  static Fz/tire ~= {vehicle.mass * G / 4.0:.1f} N")
    print(f"  steering ratio = {vehicle.steering_ratio:.3f}")

    print("\nTire lateral model:")
    print(f"  FNOMIN          = {vehicle.fz_ref:.1f} N")
    print(
        f"  mu_y(FNOMIN)    ≈ "
        f"{tire_mu_y(vehicle, np.array([vehicle.fz_ref], dtype=np.float64))[0]:.3f}"
    )
    print(
        f"  C_alpha(FNOMIN) ≈ "
        f"{tire_cornering_stiffness_y(vehicle, np.array([vehicle.fz_ref], dtype=np.float64))[0]:.1f} N/rad"
    )
    print(
        f"  valid Fz range  = "
        f"{vehicle.fz_min_valid:.1f} to {vehicle.fz_max_valid:.1f} N"
    )

    # -------------------------------------------------------------------------
    # Single-speed YMD generation
    # -------------------------------------------------------------------------
    config = config_to_ymd_config(ymd_report_config)

    result = generate_ymd(vehicle, config)

    report_cfg = ymd_report_config.get("report") or {}
    results_dir = ENVELOPE_DIR / "results"
    build_dir = BUILD_DIR
    results_dir.mkdir(parents=True, exist_ok=True)
    build_dir.mkdir(parents=True, exist_ok=True)

    raw_output_path = resolve_ymd_output_path(
        config_path,
        report_cfg.get("raw_output_path", "../Build/YMD/ymd_first_principles.csv"),
    )
    metrics_output_path = resolve_ymd_output_path(
        config_path,
        report_cfg.get("metrics_output_path", "../results/ymd_report_metrics.csv"),
    )
    trim_output_path = resolve_ymd_output_path(
        config_path,
        report_cfg.get("trim_output_path", "../Build/YMD/ymd_trim_curve.csv"),
    )
    pdf_output_path = resolve_ymd_output_path(
        config_path,
        report_cfg.get("output_path", "../results/ymd_report.pdf"),
    )

    summary, trim_rows = summarize_ymd(result)

    # -------------------------------------------------------------------------
    # YMD speed sweep
    # -------------------------------------------------------------------------
    speed_sweep_cfg = ymd_report_config.get("speed_sweep") or {}
    speed_sweep = np.array(
        [float(v) for v in speed_sweep_cfg.get("speeds_mps", np.linspace(10.0, 25.0, 7))],
        dtype=float,
    )
    sweep_result: YMDSpeedSweepResult | None = None
    sweep_rows: list[dict[str, float]] = []

    if bool(speed_sweep_cfg.get("enabled", True)):
        sweep_result = generate_ymd_speed_sweep(
            vehicle=vehicle,
            base_config=config,
            speeds=speed_sweep,
        )
        sweep_summary, sweep_rows = summarize_ymd_speed_sweep(sweep_result)
        summary.update(sweep_summary)

    save_ymd_csv(result, raw_output_path)
    save_metric_rows(ymd_metric_rows(summary), metrics_output_path)
    save_trim_curve_csv(trim_rows, trim_output_path)
    if bool(report_cfg.get("enabled", True)):
        build_ymd_report_pdf(
            result,
            summary=summary,
            trim_rows=trim_rows,
            speed_sweep=sweep_result,
            speed_sweep_rows=sweep_rows,
            projection_summary=projection.summary,
            config=ymd_report_config,
            output_path=pdf_output_path,
        )


if __name__ == "__main__":
    main()
