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

from dataclasses import dataclass
from pathlib import Path

import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.art3d import Poly3DCollection
from scipy.spatial import ConvexHull
import matplotlib.patches as mpatches
import numpy as np


G = 9.80665
IN_TO_M = 0.0254
MPH_TO_MPS = 0.44704


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
    beta: np.ndarray
    hwa: np.ndarray
    ay: np.ndarray
    mz: np.ndarray
    converged: np.ndarray


@dataclass
class YMDSpeedSweepResult:
    speeds: np.ndarray
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


def tire_mu_y(vehicle: VehicleParams, fz: np.ndarray) -> np.ndarray:
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
    fz: np.ndarray,
) -> np.ndarray:
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
    fz: np.ndarray,
    alpha: np.ndarray,
) -> np.ndarray:
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


def wheel_positions(vehicle: VehicleParams) -> tuple[np.ndarray, np.ndarray]:
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

    x = np.array([a, a, -b, -b], dtype=float)

    y = np.array(
        [
            vehicle.track_front / 2.0,
            -vehicle.track_front / 2.0,
            vehicle.track_rear / 2.0,
            -vehicle.track_rear / 2.0,
        ],
        dtype=float,
    )

    return x, y


def wheel_loads(
    vehicle: VehicleParams,
    speed: float,
    ax: float,
    ay: float,
) -> np.ndarray:
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

    front_lat_transfer = (
        vehicle.lltd * total_lat_transfer_moment / vehicle.track_front
    )
    rear_lat_transfer = (
        (1.0 - vehicle.lltd) * total_lat_transfer_moment / vehicle.track_rear
    )

    fl = 0.5 * fz_front - 0.5 * front_lat_transfer
    fr = 0.5 * fz_front + 0.5 * front_lat_transfer
    rl = 0.5 * fz_rear - 0.5 * rear_lat_transfer
    rr = 0.5 * fz_rear + 0.5 * rear_lat_transfer

    return np.array([fl, fr, rl, rr], dtype=float)


def tire_slip_angles(
    vehicle: VehicleParams,
    speed: float,
    beta: float,
    hwa: float,
    yaw_rate: float = 0.0,
) -> np.ndarray:
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
        dtype=float,
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

    fy_body = np.zeros(4)
    fx_body = np.zeros(4)

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
            dtype=float,
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

    ay_grid = np.full((config.beta_points, config.hwa_points), np.nan)
    mz_grid = np.full((config.beta_points, config.hwa_points), np.nan)
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
    beta_vals: np.ndarray,
    hwa_vals: np.ndarray,
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

    return plt.get_cmap("coolwarm")(normalized)


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

    def nearest_index(values: np.ndarray, target: float) -> int:
        return int(np.argmin(np.abs(values - target)))

    def selected_integer_degree_indices(values_deg: np.ndarray) -> list[int]:
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
        x: np.ndarray,
        y: np.ndarray,
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
                color=value_to_blue_red(beta, max_abs_beta),
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
    rows = []

    for i, beta in enumerate(result.beta):
        for j, hwa in enumerate(result.hwa):
            ay = result.ay[i, j]
            mz = result.mz[i, j]

            rows.append(
                [
                    result.speed,
                    beta,
                    np.rad2deg(beta),
                    hwa,
                    np.rad2deg(hwa),
                    ay,
                    ay / G if np.isfinite(ay) else np.nan,
                    mz,
                    int(result.converged[i, j]),
                ]
            )

    data = np.asarray(rows, dtype=float)

    header = (
        "speed_mps,beta_rad,beta_deg,hwa_rad,hwa_deg,"
        "ay_mps2,ay_g,mz_nm,converged"
    )

    np.savetxt(output_path, data, delimiter=",", header=header, comments="")
    print(f"Saved YMD CSV: {output_path}")


def generate_ymd_speed_sweep(
    vehicle: VehicleParams,
    base_config: YMDConfig,
    speeds: np.ndarray,
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
        speeds=np.asarray(speeds, dtype=float),
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

    max_abs_mz = max(
        float(np.nanmax(np.abs(result.mz)))
        for result in sweep.results
    )

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
    point_blocks = []

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

    def interior_indices(n: int, count: int) -> np.ndarray:
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
        ay_surface = []
        mz_surface = []
        speed_surface = []

        for result in sweep.results:
            ay_surface.append(result.ay[beta_idx, :] / G)
            mz_surface.append(result.mz[beta_idx, :])
            speed_surface.append(np.full_like(result.hwa, result.speed, dtype=float))

        ay_surface = np.vstack(ay_surface)
        mz_surface = np.vstack(mz_surface)
        speed_surface = np.vstack(speed_surface)

        if np.all(~np.isfinite(ay_surface)) or np.all(~np.isfinite(mz_surface)):
            continue

        ax.plot_surface(
            ay_surface,
            mz_surface,
            speed_surface,
            color="blue",
            alpha=surface_alpha,
            linewidth=0.15,
            edgecolor="blue",
            antialiased=True,
            shade=False,
        )

        if show_slice_wireframes:
            ax.plot_wireframe(
                ay_surface,
                mz_surface,
                speed_surface,
                color="blue",
                linewidth=0.45,
                alpha=0.35,
                rstride=1,
                cstride=max(1, ay_surface.shape[1] // 8),
            )

    # -------------------------------------------------------------------------
    # Red surfaces: hwa fixed, sweep beta and speed
    # -------------------------------------------------------------------------
    for hwa_idx in hwa_indices:
        ay_surface = []
        mz_surface = []
        speed_surface = []

        for result in sweep.results:
            ay_surface.append(result.ay[:, hwa_idx] / G)
            mz_surface.append(result.mz[:, hwa_idx])
            speed_surface.append(np.full_like(result.beta, result.speed, dtype=float))

        ay_surface = np.vstack(ay_surface)
        mz_surface = np.vstack(mz_surface)
        speed_surface = np.vstack(speed_surface)

        if np.all(~np.isfinite(ay_surface)) or np.all(~np.isfinite(mz_surface)):
            continue

        ax.plot_surface(
            ay_surface,
            mz_surface,
            speed_surface,
            color="red",
            alpha=surface_alpha,
            linewidth=0.15,
            edgecolor="red",
            antialiased=True,
            shade=False,
        )

        if show_slice_wireframes:
            ax.plot_wireframe(
                ay_surface,
                mz_surface,
                speed_surface,
                color="red",
                linewidth=0.45,
                alpha=0.35,
                rstride=1,
                cstride=max(1, ay_surface.shape[1] // 8),
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
    # -------------------------------------------------------------------------
    # Chassis / vehicle inputs
    # -------------------------------------------------------------------------
    sprung_mass_kg = 240.40
    unsprung_front_axle_kg = 15.42
    unsprung_rear_axle_kg = 15.42

    total_mass_kg = sprung_mass_kg + unsprung_front_axle_kg + unsprung_rear_axle_kg

    wheelbase_m = 61.0 * IN_TO_M
    track_front_m = 48.0 * IN_TO_M
    track_rear_m = 48.0 * IN_TO_M
    cg_height_m = 11.0 * IN_TO_M

    # -------------------------------------------------------------------------
    # Aero inputs
    # -------------------------------------------------------------------------
    # Selected CFD case:
    #   FRH = 1.4 in, RRH = 1.65 in
    #   Downforce Fz = 161.7379 N
    #   Drag Fx = 80.7986 N
    #
    # Use force-derived ClA/CdA, so no reference area is needed.
    cfd_speed_mps = 25.0 * MPH_TO_MPS

    cl_a, cd_a = force_to_aero_area(
        downforce_n=161.7379,
        drag_n=80.7986,
        speed_mps=cfd_speed_mps,
    )

    print("Aero force-derived values:")
    print(f"  CFD speed = {cfd_speed_mps:.3f} m/s")
    print(f"  ClA       = {cl_a:.4f} m^2")
    print(f"  CdA       = {cd_a:.4f} m^2")

    # -------------------------------------------------------------------------
    # Vehicle model
    # -------------------------------------------------------------------------
    vehicle = VehicleParams(
        mass=total_mass_kg,
        wheelbase=wheelbase_m,
        track_front=track_front_m,
        track_rear=track_rear_m,
        cg_height=cg_height_m,
        front_static_frac=0.50,

        # Front convention:
        #   lltd = front lateral load transfer / total lateral load transfer
        lltd=0.50,

        # Update this once you want true roadwheel angle instead of roadwheel angle.
        # Example:
        #   steering_ratio = 4.0
        # means:
        #   delta_roadwheel = delta_hwa / 4
        steering_ratio=1.0,

        # 50/50 assumed aero balance for now
        cl_a=cl_a,
        cd_a=cd_a,
        aero_balance_front=0.50,

        # .tir lateral tire model
        fz_ref=654.0,
        fz_min_valid=100.0,
        fz_max_valid=1091.0,
        pdy1=-2.40275,
        pdy2=0.343535,
        pky1=-53.2421,
        pky2=2.38205,
        mu_min=0.8,
    )

    print("\nVehicle values:")
    print(f"  mass           = {vehicle.mass:.2f} kg")
    print(f"  wheelbase      = {vehicle.wheelbase:.4f} m")
    print(f"  front track    = {vehicle.track_front:.4f} m")
    print(f"  rear track     = {vehicle.track_rear:.4f} m")
    print(f"  CG height      = {vehicle.cg_height:.4f} m")
    print(f"  static Fz/tire ≈ {vehicle.mass * G / 4.0:.1f} N")
    print(f"  steering ratio = {vehicle.steering_ratio:.3f}")

    print("\nTire lateral model:")
    print(f"  FNOMIN          = {vehicle.fz_ref:.1f} N")
    print(f"  mu_y(FNOMIN)    ≈ {tire_mu_y(vehicle, np.array([vehicle.fz_ref]))[0]:.3f}")
    print(
        f"  C_alpha(FNOMIN) ≈ "
        f"{tire_cornering_stiffness_y(vehicle, np.array([vehicle.fz_ref]))[0]:.1f} N/rad"
    )
    print(
        f"  valid Fz range  = "
        f"{vehicle.fz_min_valid:.1f} to {vehicle.fz_max_valid:.1f} N"
    )

    # -------------------------------------------------------------------------
    # Single-speed YMD generation
    # -------------------------------------------------------------------------
    config = YMDConfig(
        speed=15.0,
        beta_min_deg=-8.0,
        beta_max_deg=8.0,
        beta_points=61,
        hwa_min_deg=-8.0,
        hwa_max_deg=8.0,
        hwa_points=61,
        yaw_rate=0.0,
        max_iter=50,
        tol_ay=1e-5,
        relaxation=0.35,
        verbose=True,
        warn_tire_load_range=True,
    )

    result = generate_ymd(vehicle, config)

    output_dir = Path("results")
    output_dir.mkdir(parents=True, exist_ok=True)

    save_ymd_csv(result, output_dir / "ymd_first_principles.csv")
    plot_ymd(result, output_dir / "ymd_first_principles_wireframe.png")
    plot_ymd_beta_slices(result, output_dir / "ymd_first_principles_beta_slices.png")
    plot_ymd_contours(result, output_dir / "ymd_first_principles_contours.png")

    # -------------------------------------------------------------------------
    # YMD speed sweep / 3D visualization
    # -------------------------------------------------------------------------
    # Keep this modest for slide-readability. Increase to 11-15 later if desired.
    speed_sweep = np.linspace(5.0, 25.0, 7)

    sweep = generate_ymd_speed_sweep(
        vehicle=vehicle,
        base_config=config,
        speeds=speed_sweep,
    )

    plot_ymd_speed_sweep_3d(
        sweep,
        output_dir / "ymd_first_principles_speed_sweep_3d.png",
    )

    plot_ymd_speed_sweep_hull_surfaces(
        sweep,
        output_dir / "ymd_first_principles_speed_sweep_hull_surfaces.png",
        beta_surface_count=3,
        hwa_surface_count=3,
        hull_alpha=0.10,
        surface_alpha=0.16,
        show_slice_wireframes=True,
    )

    plot_ymd_speed_sweep_surface(
        sweep,
        output_dir / "ymd_first_principles_speed_sweep_surface.png",
    )


if __name__ == "__main__":
    main()