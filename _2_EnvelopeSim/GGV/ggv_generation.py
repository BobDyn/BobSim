"""
First-principles GGV envelope generator for BobSim.

This computes quasi-static full-vehicle acceleration envelopes using:
- mass properties
- static weight distribution
- aero downforce / drag
- longitudinal and lateral load transfer
- tire load-sensitive peak friction from .tir coefficients
- power limit and optional actuator force caps
- friction ellipse / combined-slip tire usage

The output is:
- 2D ax-ay GGV envelopes at multiple speeds
- 3D closed GGV envelope surface, with speed as the vertical axis
- CSV export with feasibility flags

This is intended as a first-principles BobSim analysis utility. It is not yet
a full Magic Formula combined-slip tire solver or full FMU trim solve.
"""

from __future__ import annotations

import csv
from dataclasses import dataclass
from datetime import datetime
import os
from pathlib import Path
from typing import Any, Literal

os.environ.setdefault("MPLCONFIGDIR", "/tmp/matplotlib")

import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages
import numpy as np
from numpy.typing import NDArray
import yaml


G = 9.80665
IN_TO_M = 0.0254
LB_TO_KG = 0.45359237
LBF_PER_IN_TO_N_PER_M = 175.12683524647636
MPH_TO_MPS = 0.44704
GGV_DIR = Path(__file__).resolve().parent
ENVELOPE_DIR = GGV_DIR.parent
REPO_ROOT = ENVELOPE_DIR.parent
BUILD_DIR = ENVELOPE_DIR / "Build" / "GGV"
DEFAULT_GGV_CONFIG = GGV_DIR / "ggv_config.yml"


FloatArray = NDArray[np.float64]


@dataclass(frozen=True)
class VehicleParams:
    mass: float  # kg
    wheelbase: float  # m
    track_front: float  # m
    track_rear: float  # m
    cg_height: float  # m

    front_static_frac: float  # fraction of static weight on front axle

    # Roll / lateral load transfer distribution.
    # 0.5 means equal front/rear lateral load transfer.
    # Higher means more front lateral load transfer.
    lltd: float

    # Aero
    rho: float = 1.225  # kg/m^3
    cl_a: float = 0.0  # downforce coefficient times area, positive number
    cd_a: float = 0.0  # drag coefficient times area
    aero_balance_front: float = 0.50  # fraction of downforce on front axle

    # Powertrain / braking.
    # Force caps are optional actuator limits; inf leaves the tire as the limit.
    max_drive_power: float = 80_000.0  # W
    max_drive_force: float = float("inf")  # N
    max_brake_force: float = float("inf")  # N
    drive_distribution_front: float = 0.0  # 0 for RWD, 1 for FWD, 0.5 for AWD
    brake_distribution_front: float = 0.84

    # Tire model from .tir peak friction terms
    fz_ref: float = 654.0  # N, FNOMIN
    fz_min_valid: float = 100.0  # N, FZMIN
    fz_max_valid: float = 1091.0  # N, FZMAX

    # Longitudinal Magic Formula peak coefficients:
    # mu_x ~= PDX1 + PDX2 * dfz
    pdx1: float = 2.597991
    pdx2: float = -0.618826

    # Lateral Magic Formula peak coefficients:
    # mu_y ~= abs(PDY1 + PDY2 * dfz)
    # PDY1 is negative because of tire force sign convention.
    pdy1: float = -2.40275
    pdy2: float = 0.343535

    # Safety floor for very weird extrapolated loads
    mu_min: float = 0.8


@dataclass(frozen=True)
class GGVConfig:
    speeds: tuple[float, ...] = (5.0, 10.0, 15.0, 20.0, 25.0)
    ay_max_g: float = 3.2
    ay_points: int = 321
    ax_search_min_g: float = -3.2
    ax_search_max_g: float = 2.8
    ax_search_points: int = 801

    # Symmetric GGV by default.
    # Later, this can become asymmetric if tire/camber/turn direction is modeled.
    include_left_right: bool = True

    # Console progress reporting
    verbose: bool = True
    progress_every: int = 25

    # Warn if calculated tire normal loads leave .tir validated range.
    warn_tire_load_range: bool = True


@dataclass
class GGVEnvelope:
    speed: float
    ay: FloatArray
    ax_accel: FloatArray
    ax_brake: FloatArray


def force_to_aero_area(
    downforce_n: float,
    drag_n: float,
    speed_mps: float,
    rho: float = 1.225,
) -> tuple[float, float]:
    """
    Convert CFD forces at a known speed to ClA and CdA.

    The GGV code expects:
        downforce = 0.5 * rho * V^2 * cl_a
        drag      = 0.5 * rho * V^2 * cd_a

    This avoids needing to know the CFD reference area.
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

    Positive downforce means increased normal load.
    Positive drag means resisting forward motion.
    """
    q = 0.5 * vehicle.rho * speed**2
    downforce = q * vehicle.cl_a
    drag = q * vehicle.cd_a

    front_downforce = vehicle.aero_balance_front * downforce
    rear_downforce = (1.0 - vehicle.aero_balance_front) * downforce

    return front_downforce, rear_downforce, drag


def tire_mu_x(vehicle: VehicleParams, fz: FloatArray) -> FloatArray:
    """
    Approximate longitudinal peak friction from .tir PDX terms.

    Uses:
        mu_x = PDX1 + PDX2 * dfz

    where:
        dfz = (Fz - Fz0) / Fz0

    Camber term PDX3 is ignored for this first-principles GGV.
    """
    fz_safe = np.maximum(fz, 1.0)
    dfz = (fz_safe - vehicle.fz_ref) / vehicle.fz_ref

    mu = vehicle.pdx1 + vehicle.pdx2 * dfz

    return np.maximum(mu, vehicle.mu_min)


def tire_mu_y(vehicle: VehicleParams, fz: FloatArray) -> FloatArray:
    """
    Approximate lateral peak friction from .tir PDY terms.

    Uses:
        mu_y = abs(PDY1 + PDY2 * dfz)

    where:
        dfz = (Fz - Fz0) / Fz0

    Camber term PDY3 is ignored for this first-principles GGV.
    """
    fz_safe = np.maximum(fz, 1.0)
    dfz = (fz_safe - vehicle.fz_ref) / vehicle.fz_ref

    # PDY1 is negative because of tire force sign convention.
    mu = np.abs(vehicle.pdy1 + vehicle.pdy2 * dfz)

    return np.maximum(mu, vehicle.mu_min)


def wheel_loads(
    vehicle: VehicleParams,
    speed: float,
    ax: float,
    ay: float,
) -> FloatArray:
    """
    Estimate individual wheel normal loads.

    Returns:
        [FL, FR, RL, RR] normal loads in N

    Sign convention:
        ax > 0: accelerating
        ax < 0: braking
        ay > 0: left turn / lateral acceleration to vehicle left

    For ay > 0, right-side tires are assumed outside tires and gain load.
    """
    weight = vehicle.mass * G

    front_aero, rear_aero, _drag = aero_loads(vehicle, speed)

    # Static + aero axle loads
    fz_front = vehicle.front_static_frac * weight + front_aero
    fz_rear = (1.0 - vehicle.front_static_frac) * weight + rear_aero

    # Longitudinal load transfer.
    # ax > 0 transfers load rearward.
    d_fz_long = vehicle.mass * ax * vehicle.cg_height / vehicle.wheelbase

    fz_front -= d_fz_long
    fz_rear += d_fz_long

    # Lateral load transfer split by LLTD.
    total_lat_transfer_moment = vehicle.mass * ay * vehicle.cg_height

    front_lat_transfer = vehicle.lltd * total_lat_transfer_moment / vehicle.track_front
    rear_lat_transfer = (
        (1.0 - vehicle.lltd) * total_lat_transfer_moment / vehicle.track_rear
    )

    # Per-wheel loads
    fl = 0.5 * fz_front - 0.5 * front_lat_transfer
    fr = 0.5 * fz_front + 0.5 * front_lat_transfer
    rl = 0.5 * fz_rear - 0.5 * rear_lat_transfer
    rr = 0.5 * fz_rear + 0.5 * rear_lat_transfer

    return np.array([fl, fr, rl, rr], dtype=float)


def distribute_lateral_force(vehicle: VehicleParams, ay: float) -> FloatArray:
    """
    Distribute lateral force demand to each tire.

    This is a first-principles approximation. We split lateral force by LLTD,
    then split equally left/right on each axle.

    Returns:
        [FL, FR, RL, RR] lateral forces in N
    """
    total_fy = vehicle.mass * ay

    fy_front = vehicle.lltd * total_fy
    fy_rear = (1.0 - vehicle.lltd) * total_fy

    return np.array(
        [
            0.5 * fy_front,
            0.5 * fy_front,
            0.5 * fy_rear,
            0.5 * fy_rear,
        ],
        dtype=float,
    )


def distribute_longitudinal_force(
    vehicle: VehicleParams,
    fx_total: float,
    mode: Literal["drive", "brake"],
) -> FloatArray:
    """
    Distribute longitudinal force demand to the tires.

    Returns:
        [FL, FR, RL, RR] longitudinal forces in N

    Positive Fx = drive force.
    Negative Fx = braking force.
    """
    if mode == "drive":
        front_frac = vehicle.drive_distribution_front
    elif mode == "brake":
        front_frac = vehicle.brake_distribution_front
    else:
        raise ValueError(f"Unknown mode: {mode}")

    fx_front = front_frac * fx_total
    fx_rear = (1.0 - front_frac) * fx_total

    return np.array(
        [
            0.5 * fx_front,
            0.5 * fx_front,
            0.5 * fx_rear,
            0.5 * fx_rear,
        ],
        dtype=float,
    )


def tire_usage(
    vehicle: VehicleParams,
    fz: FloatArray,
    fx: FloatArray,
    fy: FloatArray,
) -> FloatArray:
    """
    Elliptical combined tire usage at each tire.

    usage <= 1 means feasible.

    This uses different longitudinal and lateral capacities:
        Fx_capacity = mu_x(Fz) * Fz
        Fy_capacity = mu_y(Fz) * Fz
    """
    fz_positive = np.maximum(fz, 0.0)

    fx_capacity = tire_mu_x(vehicle, fz) * fz_positive
    fy_capacity = tire_mu_y(vehicle, fz) * fz_positive

    fx_capacity = np.maximum(fx_capacity, 1.0)
    fy_capacity = np.maximum(fy_capacity, 1.0)

    return np.sqrt((fx / fx_capacity) ** 2 + (fy / fy_capacity) ** 2)


def powertrain_force_limit(vehicle: VehicleParams, speed: float) -> float:
    """
    Maximum available drive force before tire limits.

    Limited by both max drive force and power / speed.
    """
    speed_safe = max(speed, 1.0)
    power_limited_force = vehicle.max_drive_power / speed_safe

    return min(vehicle.max_drive_force, power_limited_force)


def is_feasible(
    vehicle: VehicleParams,
    speed: float,
    ax: float,
    ay: float,
    mode: Literal["drive", "brake"],
) -> bool:
    """
    Check whether a requested ax-ay point is feasible.
    """
    fz = wheel_loads(vehicle, speed=speed, ax=ax, ay=ay)

    # Wheel lift / negative normal load = infeasible.
    if np.any(fz <= 0.0):
        return False

    _front_aero, _rear_aero, drag = aero_loads(vehicle, speed)

    # Required tire longitudinal force must overcome aero drag too.
    # Sum tire Fx = m*ax + drag.
    fx_total = vehicle.mass * ax + drag

    if mode == "drive":
        if fx_total < 0.0:
            return False

        if fx_total > powertrain_force_limit(vehicle, speed):
            return False

    elif mode == "brake":
        if fx_total > 0.0:
            return False

        if abs(fx_total) > vehicle.max_brake_force:
            return False

    fy = distribute_lateral_force(vehicle, ay)
    fx = distribute_longitudinal_force(vehicle, fx_total, mode=mode)

    usage = tire_usage(vehicle, fz=fz, fx=fx, fy=fy)

    return bool(np.all(usage <= 1.0))


def solve_ax_limit(
    vehicle: VehicleParams,
    speed: float,
    ay: float,
    ax_grid: FloatArray,
    mode: Literal["drive", "brake"],
) -> float:
    """
    Find the maximum feasible acceleration or braking at a given ay.

    For drive:
        returns largest feasible positive ax.

    For brake:
        returns most negative feasible ax.
    """
    feasible = np.array(
        [
            is_feasible(vehicle, speed=speed, ax=ax, ay=ay, mode=mode)
            for ax in ax_grid
        ],
        dtype=bool,
    )

    if not np.any(feasible):
        return np.nan

    valid_ax = ax_grid[feasible]

    if mode == "drive":
        return float(np.max(valid_ax))

    return float(np.min(valid_ax))


def warn_if_tire_loads_outside_tir_range(
    vehicle: VehicleParams,
    envelopes: list[GGVEnvelope],
) -> None:
    """
    Scan generated finite GGV points and warn if wheel loads exceed .tir range.

    This does not invalidate the plot; it just tells you where the simple model
    is extrapolating beyond the fitted tire file range.
    """
    fz_min_seen = np.inf
    fz_max_seen = -np.inf

    for env in envelopes:
        speed = env.speed

        finite_accel = np.isfinite(env.ax_accel)
        for ay, ax in zip(env.ay[finite_accel], env.ax_accel[finite_accel]):
            fz = wheel_loads(vehicle, speed=speed, ax=ax, ay=ay)
            fz_min_seen = min(fz_min_seen, float(np.min(fz)))
            fz_max_seen = max(fz_max_seen, float(np.max(fz)))

        finite_brake = np.isfinite(env.ax_brake)
        for ay, ax in zip(env.ay[finite_brake], env.ax_brake[finite_brake]):
            fz = wheel_loads(vehicle, speed=speed, ax=ax, ay=ay)
            fz_min_seen = min(fz_min_seen, float(np.min(fz)))
            fz_max_seen = max(fz_max_seen, float(np.max(fz)))

    if not np.isfinite(fz_min_seen) or not np.isfinite(fz_max_seen):
        print("Tire load range warning skipped: no finite GGV points found.")
        return

    print("\nTire load range over finite GGV points:")
    print(f"  min Fz seen = {fz_min_seen:.1f} N")
    print(f"  max Fz seen = {fz_max_seen:.1f} N")
    print(
        f"  .tir valid range = "
        f"{vehicle.fz_min_valid:.1f} to {vehicle.fz_max_valid:.1f} N"
    )

    if fz_min_seen < vehicle.fz_min_valid or fz_max_seen > vehicle.fz_max_valid:
        print(
            "  WARNING: Some finite GGV points use tire loads outside the .tir "
            "vertical force range. Treat those regions as extrapolated."
        )


def generate_ggv(
    vehicle: VehicleParams,
    config: GGVConfig,
) -> list[GGVEnvelope]:
    """
    Generate GGV envelopes across the configured speeds.
    """
    ay_positive = np.linspace(0.0, config.ay_max_g * G, config.ay_points)

    ax_drive_grid = np.linspace(
        0.0,
        config.ax_search_max_g * G,
        config.ax_search_points,
    )
    ax_brake_grid = np.linspace(
        config.ax_search_min_g * G,
        0.0,
        config.ax_search_points,
    )

    envelopes: list[GGVEnvelope] = []
    total_speeds = len(config.speeds)

    if config.verbose:
        total_ay_cases = total_speeds * config.ay_points
        total_feasibility_checks = total_ay_cases * (
            len(ax_drive_grid) + len(ax_brake_grid)
        )

        print("=" * 72)
        print("Generating first-principles GGV envelope")
        print(f"Speeds: {config.speeds}")
        print(f"ay points per speed: {config.ay_points}")
        print(f"drive ax search points: {len(ax_drive_grid)}")
        print(f"brake ax search points: {len(ax_brake_grid)}")
        print(f"ay cases: {total_ay_cases}")
        print(f"approx feasibility checks: {total_feasibility_checks:,}")
        print("=" * 72, flush=True)

    for speed_idx, speed in enumerate(config.speeds, start=1):
        if config.verbose:
            print(
                f"\n[{speed_idx}/{total_speeds}] Speed = {speed:.2f} m/s "
                f"({speed / MPH_TO_MPS:.1f} mph)",
                flush=True,
            )

        ax_accel_pos = np.empty_like(ay_positive)
        ax_brake_pos = np.empty_like(ay_positive)

        for i, ay in enumerate(ay_positive):
            ax_accel_pos[i] = solve_ax_limit(
                vehicle,
                speed=speed,
                ay=ay,
                ax_grid=ax_drive_grid,
                mode="drive",
            )

            ax_brake_pos[i] = solve_ax_limit(
                vehicle,
                speed=speed,
                ay=ay,
                ax_grid=ax_brake_grid,
                mode="brake",
            )

            should_print = (
                i == 0
                or i == config.ay_points - 1
                or (i + 1) % config.progress_every == 0
            )

            if config.verbose and should_print:
                percent = 100.0 * (i + 1) / config.ay_points

                accel_text = (
                    f"{ax_accel_pos[i] / G: .3f} g"
                    if np.isfinite(ax_accel_pos[i])
                    else "infeasible"
                )
                brake_text = (
                    f"{ax_brake_pos[i] / G: .3f} g"
                    if np.isfinite(ax_brake_pos[i])
                    else "infeasible"
                )

                print(
                    f"  ay {i + 1:>4}/{config.ay_points} "
                    f"({percent:5.1f}%) | "
                    f"ay={ay / G: .3f} g | "
                    f"ax_accel={accel_text:>10} | "
                    f"ax_brake={brake_text:>10}",
                    flush=True,
                )

        # Mirror the positive-lateral branch to create left/right symmetry.
        if config.include_left_right:
            ay_full = np.concatenate((-ay_positive[:0:-1], ay_positive))
            ax_accel_full = np.concatenate((ax_accel_pos[:0:-1], ax_accel_pos))
            ax_brake_full = np.concatenate((ax_brake_pos[:0:-1], ax_brake_pos))
        else:
            ay_full = ay_positive
            ax_accel_full = ax_accel_pos
            ax_brake_full = ax_brake_pos

        envelopes.append(
            GGVEnvelope(
                speed=speed,
                ay=ay_full,
                ax_accel=ax_accel_full,
                ax_brake=ax_brake_full,
            )
        )

        if config.verbose:
            feasible_mask = np.isfinite(ax_accel_full) | np.isfinite(ax_brake_full)

            max_ay_g = (
                np.nanmax(np.abs(ay_full[feasible_mask])) / G
                if np.any(feasible_mask)
                else np.nan
            )
            max_accel_g = (
                np.nanmax(ax_accel_full) / G
                if np.any(np.isfinite(ax_accel_full))
                else np.nan
            )
            max_brake_g = (
                np.nanmin(ax_brake_full) / G
                if np.any(np.isfinite(ax_brake_full))
                else np.nan
            )

            print(
                f"  Done speed {speed:.2f} m/s | "
                f"feasible max |ay|={max_ay_g:.3f} g, "
                f"max accel={max_accel_g:.3f} g, "
                f"max brake={max_brake_g:.3f} g",
                flush=True,
            )

    if config.verbose:
        print("\nGGV generation complete.")
        print("=" * 72, flush=True)

    if config.warn_tire_load_range:
        warn_if_tire_loads_outside_tir_range(vehicle, envelopes)

    return envelopes


def plot_ggv(
    envelopes: list[GGVEnvelope],
    output_path: str | Path | None = None,
) -> None:
    """
    Plot ax-ay GGV envelopes.

    x-axis: lateral acceleration ($g$)
    y-axis: longitudinal acceleration ($g$)
    """
    fig, ax = plt.subplots(figsize=(9.5, 6.2))

    for env in envelopes:
        ay_g = env.ay / G
        ax_accel_g = env.ax_accel / G
        ax_brake_g = env.ax_brake / G

        accel_mask = np.isfinite(ax_accel_g)
        brake_mask = np.isfinite(ax_brake_g)

        if np.any(accel_mask):
            ax.plot(
                ay_g[accel_mask],
                ax_accel_g[accel_mask],
                label=f"{env.speed:.0f} m/s accel",
            )

        if np.any(brake_mask):
            ax.plot(
                ay_g[brake_mask],
                ax_brake_g[brake_mask],
                linestyle="--",
                label=f"{env.speed:.0f} m/s brake",
            )

    ax.axhline(0.0, linewidth=0.8)
    ax.axvline(0.0, linewidth=0.8)

    ax.set_xlabel(r"$A_y$ ($g$)")
    ax.set_ylabel(r"$A_x$ ($g$)")
    ax.set_title("BobSim First-Principles GGV Envelope")
    ax.grid(True, linestyle="--", alpha=0.5)

    ax.legend(
        loc="center left",
        bbox_to_anchor=(1.02, 0.5),
        fontsize=8,
        frameon=True,
    )

    fig.tight_layout(rect=(0.0, 0.0, 0.82, 1.0))

    if output_path is not None:
        fig.savefig(output_path, dpi=300)
        print(f"Saved 2D GGV plot: {output_path}")

    plt.show()


def plot_ggv_surface(
    envelopes: list[GGVEnvelope],
    output_path: str | Path | None = None,
) -> None:
    """
    Plot the GGV as one continuous closed envelope surface.

    Axes:
        x = lateral acceleration ay ($g$)
        y = longitudinal acceleration ax ($g$)
        z = speed V ($m/s$)

    This makes velocity the vertical axis.
    """
    if not envelopes:
        raise ValueError("No GGV envelopes provided.")

    n_perimeter = 240

    speed_values: list[float] = []
    ay_loops: list[FloatArray] = []
    ax_loops: list[FloatArray] = []

    for env in envelopes:
        ay_g = env.ay / G
        ax_accel_g = env.ax_accel / G
        ax_brake_g = env.ax_brake / G

        accel_mask = np.isfinite(ax_accel_g)
        brake_mask = np.isfinite(ax_brake_g)

        if not np.any(accel_mask) or not np.any(brake_mask):
            continue

        # Accel branch: left -> right
        ay_accel = ay_g[accel_mask]
        ax_accel = ax_accel_g[accel_mask]

        sort_accel = np.argsort(ay_accel)
        ay_accel = ay_accel[sort_accel]
        ax_accel = ax_accel[sort_accel]

        # Brake branch: right -> left
        ay_brake = ay_g[brake_mask]
        ax_brake = ax_brake_g[brake_mask]

        sort_brake = np.argsort(ay_brake)[::-1]
        ay_brake = ay_brake[sort_brake]
        ax_brake = ax_brake[sort_brake]

        # Closed loop at this speed.
        ay_loop = np.concatenate([ay_accel, ay_brake, ay_accel[:1]])
        ax_loop = np.concatenate([ax_accel, ax_brake, ax_accel[:1]])

        # Remove duplicate adjacent points.
        d_ay = np.diff(ay_loop)
        d_ax = np.diff(ax_loop)
        keep = np.concatenate([[True], np.hypot(d_ay, d_ax) > 1e-9])

        ay_loop = ay_loop[keep]
        ax_loop = ax_loop[keep]

        # Parameterize loop by perimeter distance.
        ds = np.hypot(np.diff(ay_loop), np.diff(ax_loop))
        s = np.concatenate([[0.0], np.cumsum(ds)])

        if s[-1] <= 0.0:
            continue

        s_norm = s / s[-1]
        s_target = np.linspace(0.0, 1.0, n_perimeter)

        ay_resampled = np.interp(s_target, s_norm, ay_loop)
        ax_resampled = np.interp(s_target, s_norm, ax_loop)

        speed_values.append(env.speed)
        ay_loops.append(ay_resampled)
        ax_loops.append(ax_resampled)

    if not speed_values:
        raise ValueError("No valid finite GGV loops could be built.")

    speeds = np.asarray(speed_values, dtype=float)

    ay_surface = np.vstack(ay_loops)
    ax_surface = np.vstack(ax_loops)
    speed_surface = np.repeat(speeds[:, None], n_perimeter, axis=1)

    fig = plt.figure(figsize=(9.0, 7.5))
    ax = fig.add_subplot(111, projection="3d")

    ax.plot_surface(
        ay_surface,
        ax_surface,
        speed_surface,
        alpha=0.88,
        linewidth=0.15,
        edgecolor="k",
        antialiased=True,
    )

    # Draw speed slices on top of the surface.
    for i, _speed in enumerate(speeds):
        ax.plot(
            ay_surface[i, :],
            ax_surface[i, :],
            speed_surface[i, :],
            linewidth=1.0,
        )

    ax.set_xlabel(r"$A_y$ ($g$)", labelpad=10, fontsize=16)
    ax.set_ylabel(r"$A_x$ ($g$)", labelpad=10, fontsize=16)
    ax.set_zlabel(r"Speed, $V$ ($m/s$)", labelpad=10, fontsize=16)

    ax.set_title("BobSim First-Principles GGV Envelope Surface")

    # Speed vertical; ay left/right; ax depth.
    ax.view_init(elev=24, azim=-62)

    # Manual visual scaling. Do not use physical data ranges here because
    # speed is numerically much larger than acceleration in g.
    ax.set_box_aspect((1.35, 1.0, 1.15))

    ay_lim = np.nanmax(np.abs(ay_surface))
    ax_lim = np.nanmax(np.abs(ax_surface))

    ax.set_xlim(-ay_lim, ay_lim)
    ax.set_ylim(-ax_lim, ax_lim)
    ax.set_zlim(np.nanmin(speed_surface), np.nanmax(speed_surface))

    fig.tight_layout()

    if output_path is not None:
        fig.savefig(output_path, dpi=300)
        print(f"Saved 3D GGV surface plot: {output_path}")

    plt.show()


def plot_ggv_metrics(
    envelopes: list[GGVEnvelope],
    output_path: str | Path | None = None,
) -> None:
    """
    Plot scalar capability metrics extracted from the GGV vs speed.

    Metrics:
        - max cornering capability: max |ay|
        - max acceleration capability: max ax on accel branch
        - max braking capability: |min ax| on brake branch

    All quantities are shown in g.
    """
    if not envelopes:
        raise ValueError("No GGV envelopes provided.")

    speeds_list: list[float] = []
    max_cornering_g_list: list[float] = []
    max_accel_g_list: list[float] = []
    max_braking_g_list: list[float] = []

    for env in envelopes:
        ay_g = env.ay / G
        ax_accel_g = env.ax_accel / G
        ax_brake_g = env.ax_brake / G

        finite_accel = np.isfinite(ax_accel_g)
        finite_brake = np.isfinite(ax_brake_g)
        finite_any = finite_accel | finite_brake

        if np.any(finite_any):
            ay_cap: float = float(np.nanmax(np.abs(ay_g[finite_any])))
        else:
            ay_cap = float("nan")

        if np.any(finite_accel):
            accel_cap: float = float(np.nanmax(ax_accel_g[finite_accel]))
        else:
            accel_cap = float("nan")

        if np.any(finite_brake):
            brake_cap: float = float(np.abs(np.nanmin(ax_brake_g[finite_brake])))
        else:
            brake_cap = float("nan")

        speeds_list.append(float(env.speed))
        max_cornering_g_list.append(ay_cap)
        max_accel_g_list.append(accel_cap)
        max_braking_g_list.append(brake_cap)

    speeds_arr = np.asarray(speeds_list, dtype=np.float64)
    max_cornering_g_arr = np.asarray(max_cornering_g_list, dtype=np.float64)
    max_accel_g_arr = np.asarray(max_accel_g_list, dtype=np.float64)
    max_braking_g_arr = np.asarray(max_braking_g_list, dtype=np.float64)

    sort_idx = np.argsort(speeds_arr)
    speeds_sorted = speeds_arr[sort_idx]
    max_cornering_g_sorted = max_cornering_g_arr[sort_idx]
    max_accel_g_sorted = max_accel_g_arr[sort_idx]
    max_braking_g_sorted = max_braking_g_arr[sort_idx]

    fig, ax = plt.subplots(figsize=(11.0, 8.0))

    ax.plot(
        speeds_sorted,
        max_cornering_g_sorted,
        marker="o",
        linewidth=2.0,
        label=r"Max Cornering, $\max |a_y|$",
    )
    ax.plot(
        speeds_sorted,
        max_accel_g_sorted,
        marker="o",
        linewidth=2.0,
        label=r"Max Acceleration, $\max a_x$",
    )
    ax.plot(
        speeds_sorted,
        max_braking_g_sorted,
        marker="o",
        linewidth=2.0,
        label=r"Max Braking, $|\min a_x|$",
    )

    ax.set_xlabel(r"Speed, $V$ ($m/s$)")
    ax.set_ylabel(r"Acceleration Capability ($g$)")
    ax.set_title("GGV-Derived Capability Metrics")
    ax.grid(True, linestyle="--", alpha=0.5)
    ax.legend(loc="best", frameon=True)

    fig.tight_layout()

    if output_path is not None:
        fig.savefig(output_path, dpi=300)
        print(f"Saved GGV metrics plot: {output_path}")

    plt.show()


def save_ggv_csv(envelopes: list[GGVEnvelope], output_path: str | Path) -> None:
    """
    Save envelopes to CSV with columns:
        speed_mps, ay_mps2, ax_accel_mps2, ax_brake_mps2,
        accel_feasible, brake_feasible
    """
    output = Path(output_path)
    output.parent.mkdir(parents=True, exist_ok=True)
    rows: list[list[float]] = []

    for env in envelopes:
        for ay, ax_accel, ax_brake in zip(env.ay, env.ax_accel, env.ax_brake):
            accel_feasible = np.isfinite(ax_accel)
            brake_feasible = np.isfinite(ax_brake)

            rows.append(
                [
                    env.speed,
                    ay,
                    ax_accel,
                    ax_brake,
                    int(accel_feasible),
                    int(brake_feasible),
                ]
            )

    data = np.asarray(rows, dtype=float)

    header = (
        "speed_mps,ay_mps2,ax_accel_mps2,ax_brake_mps2,"
        "accel_feasible,brake_feasible"
    )

    np.savetxt(output, data, delimiter=",", header=header, comments="")
    print(f"Saved CSV: {output}")


def load_ggv_config(path: str | Path = DEFAULT_GGV_CONFIG) -> dict[str, Any]:
    config_path = Path(path)
    with config_path.open() as f:
        config = yaml.safe_load(f)
    if not isinstance(config, dict):
        raise ValueError(f"GGV config did not parse as a mapping: {config_path}")
    return config


def config_to_ggv_config(config: dict[str, Any]) -> GGVConfig:
    generation = config.get("generation") or {}
    speeds = tuple(float(v) for v in generation.get("speeds_mps", GGVConfig.speeds))
    return GGVConfig(
        speeds=speeds,
        ay_max_g=float(generation.get("ay_max_g", GGVConfig.ay_max_g)),
        ay_points=int(generation.get("ay_points", GGVConfig.ay_points)),
        ax_search_min_g=float(
            generation.get("ax_search_min_g", GGVConfig.ax_search_min_g)
        ),
        ax_search_max_g=float(
            generation.get("ax_search_max_g", GGVConfig.ax_search_max_g)
        ),
        ax_search_points=int(
            generation.get("ax_search_points", GGVConfig.ax_search_points)
        ),
        include_left_right=bool(
            generation.get("include_left_right", GGVConfig.include_left_right)
        ),
        verbose=bool(generation.get("verbose", True)),
        progress_every=int(generation.get("progress_every", GGVConfig.progress_every)),
        warn_tire_load_range=bool(
            generation.get("warn_tire_load_range", GGVConfig.warn_tire_load_range)
        ),
    )


def resolve_ggv_output_path(config_path: Path, raw_path: str | Path) -> Path:
    path = Path(raw_path)
    if path.is_absolute():
        return path
    return (config_path.parent / path).resolve()


def default_track_profile() -> dict[str, Any]:
    return load_ggv_config(DEFAULT_GGV_CONFIG)["performance_index"]["track_profile"]


def track_profile_from_config(config: dict[str, Any]) -> dict[str, Any]:
    performance = config.get("performance_index") or {}
    if not isinstance(performance, dict):
        raise ValueError("performance_index must be a mapping.")

    raw_profile = performance.get("track_profile") or default_track_profile()
    if not isinstance(raw_profile, dict):
        raise ValueError("performance_index.track_profile must be a mapping.")

    maneuvers = [
        _normalize_track_maneuver(raw)
        for raw in raw_profile.get("maneuvers", [])
    ]
    if not maneuvers:
        maneuvers = [
            _normalize_track_maneuver(raw)
            for raw in default_track_profile().get("maneuvers", [])
        ]

    weights = raw_profile.get("combined_weights") or {}
    if not isinstance(weights, dict):
        raise ValueError("track_profile.combined_weights must be a mapping.")

    lateral_weight = float(weights.get("lateral", 0.60))
    longitudinal_weight = float(weights.get("longitudinal", 0.40))
    total_weight = lateral_weight + longitudinal_weight
    if total_weight <= 0.0:
        lateral_weight = 0.60
        longitudinal_weight = 0.40
        total_weight = 1.0

    return {
        "name": str(raw_profile.get("name", "track_profile")),
        "mode": str(raw_profile.get("mode", "path")),
        "integration_step_m": float(raw_profile.get("integration_step_m", 1.0)),
        "lateral_weight": lateral_weight / total_weight,
        "longitudinal_weight": longitudinal_weight / total_weight,
        "maneuvers": maneuvers,
    }


def _normalize_track_maneuver(raw: Any) -> dict[str, float | str]:
    if not isinstance(raw, dict):
        raise ValueError("Track-profile maneuvers must be mappings.")

    kind = str(raw.get("type", "")).lower().replace("-", "_")
    weight = float(raw.get("weight", 1.0))
    if kind in {"corner", "constant_radius", "skidpad", "sweeper", "slalom"}:
        radius = raw.get("radius_m", raw.get("effective_radius_m"))
        if radius is None:
            raise ValueError(f"Corner maneuver needs radius_m: {raw}")
        return {
            "name": str(raw.get("name", kind)),
            "type": "corner",
            "weight": weight,
            "radius_m": float(radius),
            "angle_deg": float(raw.get("angle_deg", 90.0)),
            "distance_m": float(
                raw.get(
                    "distance_m",
                    float(radius) * np.deg2rad(float(raw.get("angle_deg", 90.0))),
                )
            ),
        }

    if kind in {"straight", "chute", "connector"}:
        distance = raw.get("distance_m", raw.get("length_m"))
        if distance is None:
            raise ValueError(f"Straight maneuver needs distance_m: {raw}")
        return {
            "name": str(raw.get("name", kind)),
            "type": "straight",
            "weight": weight,
            "distance_m": float(distance),
        }

    if kind in {"accel", "acceleration", "drive", "straight_accel"}:
        start, end = _speed_window(raw)
        return {
            "name": str(raw.get("name", kind)),
            "type": "accel",
            "weight": weight,
            "speed_start_mps": start,
            "speed_end_mps": end,
        }

    if kind in {"brake", "braking", "decel", "deceleration"}:
        start, end = _speed_window(raw)
        return {
            "name": str(raw.get("name", kind)),
            "type": "brake",
            "weight": weight,
            "speed_start_mps": start,
            "speed_end_mps": end,
        }

    raise ValueError(f"Unsupported track-profile maneuver type: {raw.get('type')!r}")


def _speed_window(raw: dict[str, Any]) -> tuple[float, float]:
    window = raw.get("speed_window_mps")
    if window is None:
        window = [raw.get("speed_start_mps"), raw.get("speed_end_mps")]
    if not isinstance(window, (list, tuple)) or len(window) != 2:
        raise ValueError(f"Maneuver needs speed_window_mps: {raw}")
    return float(window[0]), float(window[1])


def ggv_capability_by_speed(envelopes: list[GGVEnvelope]) -> list[dict[str, float]]:
    rows: list[dict[str, float]] = []
    for env in envelopes:
        ay_g = env.ay / G
        ax_accel_g = env.ax_accel / G
        ax_brake_g = env.ax_brake / G
        zero_ay_idx = int(np.nanargmin(np.abs(env.ay)))
        finite_accel = np.isfinite(ax_accel_g)
        finite_brake = np.isfinite(ax_brake_g)
        finite_any = finite_accel | finite_brake
        area_mps4 = _ggv_slice_area_mps4(env)

        rows.append(
            {
                "speed_mps": float(env.speed),
                "max_cornering_g": (
                    float(np.nanmax(np.abs(ay_g[finite_any])))
                    if np.any(finite_any)
                    else float("nan")
                ),
                "max_accel_g": (
                    float(np.nanmax(ax_accel_g[finite_accel]))
                    if np.any(finite_accel)
                    else float("nan")
                ),
                "max_braking_g": (
                    float(abs(np.nanmin(ax_brake_g[finite_brake])))
                    if np.any(finite_brake)
                    else float("nan")
                ),
                "straightline_accel_g": (
                    float(ax_accel_g[zero_ay_idx])
                    if np.isfinite(ax_accel_g[zero_ay_idx])
                    else float("nan")
                ),
                "straightline_braking_g": (
                    float(abs(ax_brake_g[zero_ay_idx]))
                    if np.isfinite(ax_brake_g[zero_ay_idx])
                    else float("nan")
                ),
                "ggv_area_g2": area_mps4 / G**2,
            }
        )
    return sorted(rows, key=lambda row: row["speed_mps"])


def summarize_ggv_capability(
    envelopes: list[GGVEnvelope],
    *,
    reference_speed_mps: float,
) -> tuple[dict[str, float], list[dict[str, float]]]:
    capability_rows = ggv_capability_by_speed(envelopes)
    speeds = np.array([row["speed_mps"] for row in capability_rows], dtype=float)
    areas = np.array([row["ggv_area_g2"] for row in capability_rows], dtype=float)
    cornering = np.array(
        [row["max_cornering_g"] for row in capability_rows],
        dtype=float,
    )
    accel = np.array(
        [row["straightline_accel_g"] for row in capability_rows],
        dtype=float,
    )
    braking = np.array(
        [row["straightline_braking_g"] for row in capability_rows],
        dtype=float,
    )

    volume_g2_mps = _integrate_valid(speeds, areas)
    area_ref_g2 = _interp_valid(speeds, areas, reference_speed_mps)
    cornering_ref_g = _interp_valid(speeds, cornering, reference_speed_mps)
    accel_ref_g = _interp_valid(speeds, accel, reference_speed_mps)
    braking_ref_g = _interp_valid(speeds, braking, reference_speed_mps)

    max_cornering = _max_row(capability_rows, "max_cornering_g")
    max_accel = _max_row(capability_rows, "max_accel_g")
    max_braking = _max_row(capability_rows, "max_braking_g")
    min_area = _min_row(capability_rows, "ggv_area_g2")
    max_area = _max_row(capability_rows, "ggv_area_g2")
    min_cornering = _min_row(capability_rows, "max_cornering_g")
    min_accel = _min_row(capability_rows, "straightline_accel_g")
    min_braking = _min_row(capability_rows, "straightline_braking_g")

    summary = {
        "reference_speed_mps": reference_speed_mps,
        "n_speed_slices": float(len(envelopes)),
        "speed_min_mps": float(np.nanmin(speeds)),
        "speed_max_mps": float(np.nanmax(speeds)),
        "ggv_volume_g2_mps": volume_g2_mps,
        "ggv_area_ref_g2": area_ref_g2,
        "ggv_cornering_ref_g": cornering_ref_g,
        "ggv_accel_ref_g": accel_ref_g,
        "ggv_braking_ref_g": braking_ref_g,
        "ggv_mean_cornering_g": _speed_average_valid(speeds, cornering),
        "ggv_mean_accel_g": _speed_average_valid(speeds, accel),
        "ggv_mean_braking_g": _speed_average_valid(speeds, braking),
        "ggv_min_cornering_g": _min_valid(cornering),
        "ggv_min_accel_g": _min_valid(accel),
        "ggv_min_braking_g": _min_valid(braking),
        "ggv_area_fill_factor_ref": _ggv_area_fill_factor(
            area_ref_g2,
            cornering_ref_g,
            accel_ref_g,
            braking_ref_g,
        ),
        "ggv_longitudinal_balance_ref": _safe_ratio(accel_ref_g, braking_ref_g),
        "ggv_min_area_g2": float(min_area["ggv_area_g2"]),
        "ggv_min_area_speed_mps": float(min_area["speed_mps"]),
        "ggv_max_area_g2": float(max_area["ggv_area_g2"]),
        "ggv_max_area_speed_mps": float(max_area["speed_mps"]),
        "ggv_max_cornering_g": float(max_cornering["max_cornering_g"]),
        "ggv_max_cornering_speed_mps": float(max_cornering["speed_mps"]),
        "ggv_min_cornering_speed_mps": float(min_cornering["speed_mps"]),
        "ggv_max_accel_g": float(max_accel["max_accel_g"]),
        "ggv_max_accel_speed_mps": float(max_accel["speed_mps"]),
        "ggv_min_accel_speed_mps": float(min_accel["speed_mps"]),
        "ggv_max_braking_g": float(max_braking["max_braking_g"]),
        "ggv_max_braking_speed_mps": float(max_braking["speed_mps"]),
        "ggv_min_braking_speed_mps": float(min_braking["speed_mps"]),
    }
    return summary, capability_rows


def summarize_ggv(
    envelopes: list[GGVEnvelope],
    *,
    reference_speed_mps: float,
    track_profile: dict[str, Any],
) -> tuple[dict[str, float | str], list[dict[str, float]], list[dict[str, float | str]]]:
    capability_summary, capability_rows = summarize_ggv_capability(
        envelopes,
        reference_speed_mps=reference_speed_mps,
    )
    track_metrics, track_rows = track_performance_metrics(envelopes, track_profile)

    summary: dict[str, float | str] = {
        "track_profile": str(track_profile["name"]),
        **capability_summary,
        **track_metrics,
    }
    return summary, capability_rows, track_rows


def track_performance_metrics(
    envelopes: list[GGVEnvelope],
    track_profile: dict[str, Any],
) -> tuple[dict[str, float], list[dict[str, float | str]]]:
    if any(str(maneuver["type"]) == "straight" for maneuver in track_profile["maneuvers"]):
        return _path_performance_metrics(envelopes, track_profile)

    return _legacy_window_performance_metrics(envelopes, track_profile)


def _path_performance_metrics(
    envelopes: list[GGVEnvelope],
    track_profile: dict[str, Any],
) -> tuple[dict[str, float], list[dict[str, float | str]]]:
    rows: list[dict[str, float | str]] = []
    maneuvers = list(track_profile["maneuvers"])
    corner_speeds: dict[int, float] = {}

    for idx, maneuver in enumerate(maneuvers):
        if str(maneuver["type"]) != "corner":
            continue
        radius = float(maneuver["radius_m"])
        speed = _corner_speed_for_radius(envelopes, radius)
        corner_speeds[idx] = speed
        distance = float(maneuver.get("distance_m", radius * np.deg2rad(90.0)))
        rows.append(
            {
                "path_index": float(idx),
                "maneuver": str(maneuver["name"]),
                "type": "corner",
                "group": "lateral",
                "weight": float(maneuver.get("weight", distance)),
                "distance_m": distance,
                "radius_m": radius,
                "angle_deg": float(
                    maneuver.get("angle_deg", np.rad2deg(distance / radius))
                ),
                "speed_start_mps": speed,
                "speed_end_mps": speed,
                "speed_mean_mps": speed,
                "speed_peak_mps": speed,
                "score": speed,
                "score_units": "m/s",
            }
        )

    if not corner_speeds:
        raise ValueError("Path-style GGV track profile needs at least one corner.")

    ds_target = max(float(track_profile.get("integration_step_m", 1.0)), 0.1)
    for idx, maneuver in enumerate(maneuvers):
        if str(maneuver["type"]) != "straight":
            continue

        prev_corner_idx = _nearest_corner_index(
            corner_speeds,
            idx,
            direction=-1,
            n=len(maneuvers),
        )
        next_corner_idx = _nearest_corner_index(
            corner_speeds,
            idx,
            direction=1,
            n=len(maneuvers),
        )
        start_speed = corner_speeds[prev_corner_idx]
        end_speed = corner_speeds[next_corner_idx]
        distance = float(maneuver["distance_m"])
        profile = _integrate_straight_profile(
            envelopes,
            distance_m=distance,
            start_speed_mps=start_speed,
            end_speed_mps=end_speed,
            step_m=ds_target,
        )
        rows.append(
            {
                "path_index": float(idx),
                "maneuver": str(maneuver["name"]),
                "type": "straight",
                "group": "longitudinal",
                "weight": float(maneuver.get("weight", distance)),
                "distance_m": distance,
                "radius_m": float("nan"),
                "angle_deg": float("nan"),
                "speed_start_mps": start_speed,
                "speed_end_mps": end_speed,
                "speed_mean_mps": profile["mean_speed_mps"],
                "speed_peak_mps": profile["peak_speed_mps"],
                "accel_mean_mps2": profile["accel_mean_mps2"],
                "brake_mean_mps2": profile["brake_mean_mps2"],
                "longitudinal_mean_mps2": profile["longitudinal_mean_mps2"],
                "accel_distance_fraction": profile["accel_distance_fraction"],
                "brake_distance_fraction": profile["brake_distance_fraction"],
                "coast_distance_fraction": profile["coast_distance_fraction"],
                "score": profile["mean_speed_mps"],
                "score_units": "m/s",
            }
        )

    rows = sorted(rows, key=lambda row: float(row.get("path_index", 0.0)))
    lateral = [row for row in rows if row["group"] == "lateral"]
    straights = [row for row in rows if row["group"] == "longitudinal"]
    all_distance = sum(float(row.get("distance_m", 0.0)) for row in rows)
    straight_distance = sum(float(row.get("distance_m", 0.0)) for row in straights)

    track_velocity_mean = _distance_weighted(rows, "speed_mean_mps")
    track_velocity_peak = max(
        (float(row["speed_peak_mps"]) for row in rows),
        default=float("nan"),
    )
    accel_mean = _distance_weighted(straights, "accel_mean_mps2")
    brake_mean = _distance_weighted(straights, "brake_mean_mps2")
    longitudinal_mean = _distance_weighted(straights, "longitudinal_mean_mps2")

    metrics = {
        "track_corner_speed_mean_mps": _weighted_score(lateral),
        "track_corner_speed_min_mps": min(
            (float(row["score"]) for row in lateral),
            default=float("nan"),
        ),
        "track_velocity_mean_mps": track_velocity_mean,
        "track_velocity_peak_mps": track_velocity_peak,
        "track_path_distance_m": all_distance,
        "track_straight_distance_m": straight_distance,
        "track_straight_speed_mean_mps": _distance_weighted(straights, "speed_mean_mps"),
        "track_accel_capacity_mean_mps2": accel_mean,
        "track_brake_capacity_mean_mps2": brake_mean,
        "track_longitudinal_capacity_mean_mps2": longitudinal_mean,
        "track_lateral_performance_index": 1.0,
        "track_accel_performance_index": 1.0,
        "track_brake_performance_index": 1.0,
        "track_longitudinal_performance_index": 1.0,
        "track_combined_performance_index": 1.0,
    }
    return metrics, rows


def track_velocity_profile_rows(
    envelopes: list[GGVEnvelope],
    track_profile: dict[str, Any],
) -> list[dict[str, float | str]]:
    maneuvers = list(track_profile["maneuvers"])
    if not any(str(maneuver["type"]) == "straight" for maneuver in maneuvers):
        return []

    corner_speeds: dict[int, float] = {}
    for idx, maneuver in enumerate(maneuvers):
        if str(maneuver["type"]) == "corner":
            corner_speeds[idx] = _corner_speed_for_radius(
                envelopes,
                float(maneuver["radius_m"]),
            )

    if not corner_speeds:
        return []

    rows: list[dict[str, float | str]] = []
    ds_target = max(float(track_profile.get("integration_step_m", 1.0)), 0.1)
    path_s = 0.0

    for idx, maneuver in enumerate(maneuvers):
        kind = str(maneuver["type"])
        name = str(maneuver["name"])

        if kind == "corner":
            radius = float(maneuver["radius_m"])
            distance = float(maneuver["distance_m"])
            speed = corner_speeds[idx]
            ay = speed**2 / radius if radius > 0.0 else float("nan")
            for local_s in (0.0, distance):
                rows.append(
                    {
                        "path_index": float(idx),
                        "maneuver": name,
                        "type": "corner",
                        "s_m": path_s + local_s,
                        "local_s_m": local_s,
                        "speed_mps": speed,
                        "ax_mps2": 0.0,
                        "ay_mps2": ay,
                        "radius_m": radius,
                    }
                )
            path_s += distance
            continue

        if kind != "straight":
            continue

        prev_corner_idx = _nearest_corner_index(
            corner_speeds,
            idx,
            direction=-1,
            n=len(maneuvers),
        )
        next_corner_idx = _nearest_corner_index(
            corner_speeds,
            idx,
            direction=1,
            n=len(maneuvers),
        )
        _, local_s_values, speeds, segment_ax = _integrate_straight_profile_points(
            envelopes,
            distance_m=float(maneuver["distance_m"]),
            start_speed_mps=corner_speeds[prev_corner_idx],
            end_speed_mps=corner_speeds[next_corner_idx],
            step_m=ds_target,
        )
        for point_idx, (local_s, speed) in enumerate(zip(local_s_values, speeds)):
            if len(segment_ax) == 0:
                ax = 0.0
            else:
                segment_idx = min(max(point_idx - 1, 0), len(segment_ax) - 1)
                ax = float(segment_ax[segment_idx])
            rows.append(
                {
                    "path_index": float(idx),
                    "maneuver": name,
                    "type": "straight",
                    "s_m": path_s + float(local_s),
                    "local_s_m": float(local_s),
                    "speed_mps": float(speed),
                    "ax_mps2": ax,
                    "ay_mps2": 0.0,
                    "radius_m": float("nan"),
                }
            )
        path_s += float(maneuver["distance_m"])

    return rows


def _legacy_window_performance_metrics(
    envelopes: list[GGVEnvelope],
    track_profile: dict[str, Any],
) -> tuple[dict[str, float], list[dict[str, float | str]]]:
    straightline = _straightline_capacity_by_speed(envelopes)
    rows: list[dict[str, float | str]] = []
    for maneuver in track_profile["maneuvers"]:
        kind = str(maneuver["type"])
        if kind == "corner":
            radius = float(maneuver["radius_m"])
            score = _corner_speed_for_radius(envelopes, radius)
            rows.append(
                {
                    "maneuver": str(maneuver["name"]),
                    "type": kind,
                    "group": "lateral",
                    "weight": float(maneuver["weight"]),
                    "distance_m": float(maneuver.get("distance_m", np.nan)),
                    "radius_m": radius,
                    "speed_start_mps": float("nan"),
                    "speed_end_mps": float("nan"),
                    "score": score,
                    "score_units": "m/s",
                }
            )
        else:
            start = float(maneuver["speed_start_mps"])
            end = float(maneuver["speed_end_mps"])
            column = "ax_accel_mps2" if kind == "accel" else "brake_decel_mps2"
            score = _mean_capacity_over_speed(straightline, column, start, end)
            rows.append(
                {
                    "maneuver": str(maneuver["name"]),
                    "type": kind,
                    "group": kind,
                    "weight": float(maneuver["weight"]),
                    "distance_m": float("nan"),
                    "radius_m": float("nan"),
                    "speed_start_mps": start,
                    "speed_end_mps": end,
                    "score": score,
                    "score_units": "m/s^2",
                }
            )

    lateral = [row for row in rows if row["group"] == "lateral"]
    accel = [row for row in rows if row["group"] == "accel"]
    brake = [row for row in rows if row["group"] == "brake"]
    longitudinal = [row for row in rows if row["group"] in {"accel", "brake"}]
    accel_score = _weighted_score(accel)
    brake_score = _weighted_score(brake)
    longitudinal_score = _weighted_score(longitudinal)
    metrics = {
        "track_corner_speed_mean_mps": _weighted_score(lateral),
        "track_corner_speed_min_mps": min(
            (float(row["score"]) for row in lateral),
            default=float("nan"),
        ),
        "track_velocity_mean_mps": float("nan"),
        "track_velocity_peak_mps": float("nan"),
        "track_path_distance_m": float("nan"),
        "track_straight_distance_m": float("nan"),
        "track_straight_speed_mean_mps": float("nan"),
        "track_accel_capacity_mean_mps2": accel_score,
        "track_brake_capacity_mean_mps2": brake_score,
        "track_longitudinal_capacity_mean_mps2": longitudinal_score,
        "track_lateral_performance_index": 1.0,
        "track_accel_performance_index": 1.0,
        "track_brake_performance_index": 1.0,
        "track_longitudinal_performance_index": 1.0,
        "track_combined_performance_index": 1.0,
    }
    return metrics, rows


def ggv_metric_rows(summary: dict[str, float | str]) -> list[dict[str, float | str]]:
    metadata = {
        "reference_speed_mps": ("m/s", "Reference speed used for GGV area metric"),
        "n_speed_slices": ("count", "Number of GGV speed slices"),
        "speed_min_mps": ("m/s", "Minimum generated GGV speed"),
        "speed_max_mps": ("m/s", "Maximum generated GGV speed"),
        "ggv_volume_g2_mps": ("g^2*m/s", "Integrated GGV area over speed"),
        "ggv_area_ref_g2": ("g^2", "GGV ax-ay area at the reference speed"),
        "ggv_cornering_ref_g": ("g", "Lateral acceleration limit at the reference speed"),
        "ggv_accel_ref_g": ("g", "Straight-line acceleration limit at the reference speed"),
        "ggv_braking_ref_g": ("g", "Straight-line braking limit at the reference speed"),
        "ggv_mean_cornering_g": ("g", "Speed-averaged lateral acceleration limit"),
        "ggv_mean_accel_g": ("g", "Speed-averaged straight-line acceleration limit"),
        "ggv_mean_braking_g": ("g", "Speed-averaged straight-line braking limit"),
        "ggv_min_cornering_g": ("g", "Weakest generated lateral acceleration limit"),
        "ggv_min_accel_g": ("g", "Weakest generated straight-line acceleration limit"),
        "ggv_min_braking_g": ("g", "Weakest generated straight-line braking limit"),
        "ggv_area_fill_factor_ref": (
            "fraction",
            "Reference-speed GGV area divided by its accel/brake/cornering bounding rectangle",
        ),
        "ggv_longitudinal_balance_ref": (
            "ratio",
            "Reference-speed acceleration limit divided by braking limit",
        ),
        "ggv_min_area_g2": ("g^2", "Minimum generated GGV ax-ay slice area"),
        "ggv_min_area_speed_mps": ("m/s", "Speed where minimum GGV slice area occurs"),
        "ggv_max_area_g2": ("g^2", "Maximum generated GGV ax-ay slice area"),
        "ggv_max_area_speed_mps": ("m/s", "Speed where maximum GGV slice area occurs"),
        "ggv_max_cornering_g": ("g", "Maximum lateral acceleration capability"),
        "ggv_max_cornering_speed_mps": ("m/s", "Speed where max cornering occurs"),
        "ggv_min_cornering_speed_mps": (
            "m/s",
            "Speed where weakest cornering limit occurs",
        ),
        "ggv_max_accel_g": ("g", "Maximum straight-line acceleration capability"),
        "ggv_max_accel_speed_mps": ("m/s", "Speed where max acceleration occurs"),
        "ggv_min_accel_speed_mps": (
            "m/s",
            "Speed where weakest straight-line acceleration limit occurs",
        ),
        "ggv_max_braking_g": ("g", "Maximum straight-line braking capability"),
        "ggv_max_braking_speed_mps": ("m/s", "Speed where max braking occurs"),
        "ggv_min_braking_speed_mps": (
            "m/s",
            "Speed where weakest straight-line braking limit occurs",
        ),
        "track_corner_speed_mean_mps": (
            "m/s",
            "Weighted corner-speed proxy from track-profile radii",
        ),
        "track_corner_speed_min_mps": (
            "m/s",
            "Slowest configured corner-speed proxy",
        ),
        "track_velocity_mean_mps": (
            "m/s",
            "Distance-weighted pseudo velocity over the configured path",
        ),
        "track_velocity_peak_mps": (
            "m/s",
            "Peak pseudo velocity reached on the configured path",
        ),
        "track_path_distance_m": (
            "m",
            "Total configured maneuver-path distance",
        ),
        "track_straight_distance_m": (
            "m",
            "Total configured straight distance",
        ),
        "track_straight_speed_mean_mps": (
            "m/s",
            "Distance-weighted mean speed over configured straights",
        ),
        "track_accel_capacity_mean_mps2": (
            "m/s^2",
            "Mean realized positive acceleration from distance integration",
        ),
        "track_brake_capacity_mean_mps2": (
            "m/s^2",
            "Mean realized braking deceleration from distance integration",
        ),
        "track_longitudinal_capacity_mean_mps2": (
            "m/s^2",
            "Mean realized absolute longitudinal acceleration over configured straights",
        ),
        "track_lateral_performance_index": (
            "index",
            "Standalone baseline-normalized lateral index",
        ),
        "track_longitudinal_performance_index": (
            "index",
            "Standalone baseline-normalized longitudinal index",
        ),
        "track_accel_performance_index": (
            "index",
            "Standalone baseline-normalized acceleration index",
        ),
        "track_brake_performance_index": (
            "index",
            "Standalone baseline-normalized braking index",
        ),
        "track_combined_performance_index": (
            "index",
            "Standalone baseline-normalized combined index",
        ),
    }

    rows: list[dict[str, float | str]] = []
    for metric, (units, description) in metadata.items():
        rows.append(
            {
                "standard": "GGV",
                "metric": metric,
                "value": summary.get(metric, float("nan")),
                "units": units,
                "description": description,
            }
        )
    return rows


def save_metric_rows(rows: list[dict[str, float | str]], output_path: str | Path) -> None:
    output = Path(output_path)
    output.parent.mkdir(parents=True, exist_ok=True)
    with output.open("w", newline="") as f:
        writer = csv.DictWriter(
            f,
            fieldnames=["standard", "metric", "value", "units", "description"],
        )
        writer.writeheader()
        writer.writerows(rows)
    print(f"Saved GGV metrics CSV: {output}")


def save_track_profile_csv(
    rows: list[dict[str, float | str]],
    output_path: str | Path,
) -> None:
    output = Path(output_path)
    output.parent.mkdir(parents=True, exist_ok=True)
    if not rows:
        output.write_text("")
        return
    fieldnames: list[str] = []
    for preferred in (
        "path_index",
        "maneuver",
        "type",
        "group",
        "weight",
        "distance_m",
        "radius_m",
        "angle_deg",
        "speed_start_mps",
        "speed_end_mps",
        "speed_mean_mps",
        "speed_peak_mps",
        "accel_mean_mps2",
        "brake_mean_mps2",
        "longitudinal_mean_mps2",
        "accel_distance_fraction",
        "brake_distance_fraction",
        "coast_distance_fraction",
        "score",
        "score_units",
    ):
        if any(preferred in row for row in rows):
            fieldnames.append(preferred)
    for row in rows:
        for key in row:
            if key not in fieldnames:
                fieldnames.append(key)
    with output.open("w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(rows)
    print(f"Saved GGV track profile CSV: {output}")


def save_velocity_profile_csv(
    rows: list[dict[str, float | str]],
    output_path: str | Path,
) -> None:
    output = Path(output_path)
    output.parent.mkdir(parents=True, exist_ok=True)
    fieldnames = [
        "path_index",
        "maneuver",
        "type",
        "s_m",
        "local_s_m",
        "speed_mps",
        "ax_mps2",
        "ay_mps2",
        "radius_m",
    ]
    with output.open("w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(rows)
    print(f"Saved GGV track velocity profile CSV: {output}")


def build_ggv_report_pdf(
    envelopes: list[GGVEnvelope],
    *,
    summary: dict[str, float | str],
    capability_rows: list[dict[str, float]],
    track_rows: list[dict[str, float | str]],
    velocity_rows: list[dict[str, float | str]] | None = None,
    projection_summary: dict[str, float | str],
    config: dict[str, Any],
    output_path: str | Path,
) -> None:
    output = Path(output_path)
    output.parent.mkdir(parents=True, exist_ok=True)
    report_cfg = config.get("report") or {}

    with PdfPages(output) as pdf:
        _add_title_page(pdf, report_cfg)
        _add_ggv_summary_page(pdf, summary, projection_summary)
        _add_ggv_envelope_page(pdf, envelopes)
        _add_ggv_capability_page(pdf, capability_rows, summary)
        if velocity_rows:
            _add_ggv_velocity_profile_page(pdf, velocity_rows)
        _add_ggv_track_page(pdf, track_rows, summary)

    print(f"Saved GGV PDF report: {output}")


def _add_title_page(pdf: PdfPages, report_cfg: dict[str, Any]) -> None:
    fig, ax = plt.subplots(figsize=(11, 8.5))
    ax.axis("off")

    logo_path = REPO_ROOT / "_0_Utils/reporting/media/bob.png"
    if logo_path.exists():
        logo = plt.imread(logo_path)
        ax_logo = fig.add_axes([0.03, 0.72, 0.22, 0.19])
        ax_logo.imshow(logo, alpha=0.82)
        ax_logo.axis("off")

    brand = report_cfg.get("brand", "BobSim")
    title = report_cfg.get("title", "GGV Envelope Characterization")
    subtitle = report_cfg.get("subtitle", "")
    ax.text(0.5, 0.80, brand, ha="center", fontsize=24, weight="bold")
    ax.text(0.5, 0.65, title, ha="center", fontsize=20, weight="bold")
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

    notes = [str(note) for note in report_cfg.get("notes", [])]
    y = 0.36
    ax.text(0.08, y + 0.035, "Run Notes", fontsize=11, weight="bold")
    for note in notes[:8]:
        ax.text(0.09, y, f"- {note}", fontsize=8.8, ha="left", va="top")
        y -= 0.032

    pdf.savefig(fig)
    plt.close(fig)


def _add_ggv_summary_page(
    pdf: PdfPages,
    summary: dict[str, float | str],
    projection: dict[str, float | str],
) -> None:
    fig, ax = plt.subplots(figsize=(11, 8.5))
    ax.axis("off")
    ax.text(
        0.5,
        0.94,
        "GGV Metrics Summary",
        ha="center",
        fontsize=18,
        weight="bold",
        transform=ax.transAxes,
    )

    vehicle_line = (
        f"Mass {float(projection.get('mass_kg', float('nan'))):.1f} kg | "
        f"Wheelbase {float(projection.get('wheelbase_m', float('nan'))):.3f} m | "
        f"Front aero balance {100.0 * float(projection.get('aero_balance_front', float('nan'))):.1f}% | "
        f"Track profile {summary.get('track_profile', 'unknown')}"
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
        return f"{low} - {high}"

    rows = [
        ("GGV volume", metric_text("ggv_volume_g2_mps", "{:.1f}"), "g^2*m/s"),
        ("GGV area @ reference speed", metric_text("ggv_area_ref_g2", "{:.2f}"), "g^2"),
        ("GGV area range", range_text("ggv_min_area_g2", "ggv_max_area_g2", "{:.2f}"), "g^2"),
        ("Reference cornering", metric_text("ggv_cornering_ref_g", "{:.3f}"), "g"),
        ("Reference acceleration", metric_text("ggv_accel_ref_g", "{:.3f}"), "g"),
        ("Reference braking", metric_text("ggv_braking_ref_g", "{:.3f}"), "g"),
        ("Cornering range", range_text("ggv_min_cornering_g", "ggv_max_cornering_g", "{:.2f}"), "g"),
        ("Acceleration range", range_text("ggv_min_accel_g", "ggv_max_accel_g", "{:.2f}"), "g"),
        ("Braking range", range_text("ggv_min_braking_g", "ggv_max_braking_g", "{:.2f}"), "g"),
        ("Area fill factor", metric_text("ggv_area_fill_factor_ref", "{:.3f}"), "fraction"),
        ("Accel/brake balance", metric_text("ggv_longitudinal_balance_ref", "{:.3f}"), "ratio"),
        ("Path mean speed", metric_text("track_velocity_mean_mps", "{:.2f}"), "m/s"),
        ("Path peak speed", metric_text("track_velocity_peak_mps", "{:.2f}"), "m/s"),
        ("Corner speed proxy", metric_text("track_corner_speed_mean_mps", "{:.2f}"), "m/s"),
        ("Longitudinal mean", metric_text("track_longitudinal_capacity_mean_mps2", "{:.2f}"), "m/s^2"),
    ]

    split_idx = int(np.ceil(len(rows) / 2.0))
    columns = [
        (0.07, 0.38, 0.48, rows[:split_idx]),
        (0.55, 0.82, 0.92, rows[split_idx:]),
    ]
    y_top = 0.82
    y_bottom = 0.08

    for x_label, x_value, x_unit, column_rows in columns:
        row_h = min(0.052, (y_top - y_bottom) / (len(column_rows) + 1.2))
        ax.text(
            x_label,
            y_top,
            "Metric",
            fontsize=10.2,
            weight="bold",
            transform=ax.transAxes,
        )
        ax.text(
            x_value,
            y_top,
            "Value",
            fontsize=10.2,
            weight="bold",
            ha="right",
            transform=ax.transAxes,
        )
        ax.text(
            x_unit,
            y_top,
            "Units",
            fontsize=10.2,
            weight="bold",
            transform=ax.transAxes,
        )
        ax.plot(
            [x_label, x_unit + 0.06],
            [y_top - 0.018, y_top - 0.018],
            color="black",
            linewidth=0.9,
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


def _add_ggv_envelope_page(pdf: PdfPages, envelopes: list[GGVEnvelope]) -> None:
    fig, ax = plt.subplots(figsize=(9.5, 7.2))
    for env in envelopes:
        ay_g = env.ay / G
        accel = env.ax_accel / G
        brake = env.ax_brake / G
        accel_mask = np.isfinite(accel)
        brake_mask = np.isfinite(brake)
        if np.any(accel_mask):
            ax.plot(ay_g[accel_mask], accel[accel_mask], label=f"{env.speed:g} m/s accel")
        if np.any(brake_mask):
            ax.plot(
                ay_g[brake_mask],
                brake[brake_mask],
                linestyle="--",
                label=f"{env.speed:g} m/s brake",
            )

    ax.axhline(0.0, color="black", linewidth=0.8, alpha=0.55)
    ax.axvline(0.0, color="black", linewidth=0.8, alpha=0.55)
    ax.set_xlabel("lateral acceleration ay (g)")
    ax.set_ylabel("longitudinal acceleration ax (g)")
    ax.set_title("GGV ax-ay envelopes")
    ax.grid(True, alpha=0.25)
    ax.legend(loc="center left", bbox_to_anchor=(1.02, 0.5), fontsize=8)
    fig.tight_layout(rect=(0.0, 0.0, 0.82, 1.0))
    pdf.savefig(fig)
    plt.close(fig)


def _add_ggv_capability_page(
    pdf: PdfPages,
    capability_rows: list[dict[str, float]],
    summary: dict[str, float | str],
) -> None:
    speeds = np.array([row["speed_mps"] for row in capability_rows], dtype=float)
    cornering = np.array([row["max_cornering_g"] for row in capability_rows], dtype=float)
    accel = np.array([row["max_accel_g"] for row in capability_rows], dtype=float)
    braking = np.array([row["max_braking_g"] for row in capability_rows], dtype=float)
    area = np.array([row["ggv_area_g2"] for row in capability_rows], dtype=float)

    fig, axs = plt.subplots(1, 2, figsize=(13, 5.8))
    axs[0].plot(speeds, cornering, marker="o", label="cornering")
    axs[0].plot(speeds, accel, marker="o", label="accel")
    axs[0].plot(speeds, braking, marker="o", label="brake")
    axs[0].set_xlabel("speed (m/s)")
    axs[0].set_ylabel("capability (g)")
    axs[0].set_title("Capability vs speed")
    axs[0].grid(True, alpha=0.25)
    axs[0].legend(loc="best")

    axs[1].plot(speeds, area, marker="o", color="#2F6B9A")
    axs[1].set_xlabel("speed (m/s)")
    axs[1].set_ylabel("GGV slice area (g^2)")
    axs[1].set_title(f"GGV volume = {float(summary['ggv_volume_g2_mps']):.2f} g^2*m/s")
    axs[1].grid(True, alpha=0.25)

    fig.tight_layout()
    pdf.savefig(fig)
    plt.close(fig)


def _add_ggv_track_page(
    pdf: PdfPages,
    track_rows: list[dict[str, float | str]],
    summary: dict[str, float | str],
) -> None:
    fig, axs = plt.subplots(1, 2, figsize=(13, 5.8))
    corner_rows = [row for row in track_rows if row["group"] == "lateral"]
    long_rows = [
        row
        for row in track_rows
        if row["group"] in {"accel", "brake", "longitudinal"}
    ]

    if corner_rows:
        labels = [str(row["maneuver"]) for row in corner_rows]
        values = [float(row["score"]) for row in corner_rows]
        axs[0].barh(labels, values, color="#2F6B9A")
        axs[0].set_xlabel("estimated corner speed (m/s)")
        axs[0].set_title("Corner maneuver proxies")
        axs[0].grid(True, axis="x", alpha=0.25)

    if long_rows:
        labels = [str(row["maneuver"]) for row in long_rows]
        values = [float(row.get("speed_mean_mps", row["score"])) for row in long_rows]
        colors = [
            "#2F6B9A"
            if row["group"] == "longitudinal"
            else "#607D3B"
            if row["group"] == "accel"
            else "#C84C31"
            for row in long_rows
        ]
        axs[1].barh(labels, values, color=colors)
        axs[1].set_xlabel("mean pseudo speed (m/s)")
        axs[1].set_title("Straight-line pseudo velocity")
        axs[1].grid(True, axis="x", alpha=0.25)

    fig.suptitle(
        f"Track profile: {summary.get('track_profile', 'unknown')}",
        fontsize=15,
    )
    fig.tight_layout()
    pdf.savefig(fig)
    plt.close(fig)


def _add_ggv_velocity_profile_page(
    pdf: PdfPages,
    velocity_rows: list[dict[str, float | str]],
) -> None:
    rows = sorted(velocity_rows, key=lambda row: float(row["s_m"]))
    s = np.array([float(row["s_m"]) for row in rows], dtype=float)
    speed = np.array([float(row["speed_mps"]) for row in rows], dtype=float)
    ax_values = np.array([float(row["ax_mps2"]) for row in rows], dtype=float)
    ay_values = np.array([float(row["ay_mps2"]) for row in rows], dtype=float)
    is_corner = np.array([str(row["type"]) == "corner" for row in rows], dtype=bool)

    fig, axs = plt.subplots(2, 1, figsize=(12, 8.0), sharex=True)

    axs[0].plot(s, speed, color="#2F6B9A", linewidth=1.8)
    if np.any(is_corner):
        axs[0].scatter(
            s[is_corner],
            speed[is_corner],
            s=22,
            color="#C84C31",
            label="corner speed cap",
            zorder=3,
        )
        axs[0].legend(loc="best", fontsize=8)
    axs[0].set_ylabel("speed (m/s)")
    axs[0].set_title("Distance-integrated pseudo velocity profile")
    axs[0].grid(True, alpha=0.25)

    axs[1].plot(s, ax_values, color="#607D3B", linewidth=1.5, label="ax")
    axs[1].plot(s, ay_values, color="#C84C31", linewidth=1.5, label="ay")
    axs[1].axhline(0.0, color="black", linewidth=0.8, alpha=0.55)
    axs[1].set_xlabel("path distance (m)")
    axs[1].set_ylabel("acceleration (m/s^2)")
    axs[1].set_title("Realized acceleration along configured maneuver path")
    axs[1].grid(True, alpha=0.25)
    axs[1].legend(loc="best", fontsize=8)

    fig.tight_layout()
    pdf.savefig(fig)
    plt.close(fig)


def _ggv_slice_area_mps4(env: GGVEnvelope) -> float:
    order = np.argsort(env.ay)
    ay = np.asarray(env.ay, dtype=float)[order]
    accel = np.asarray(env.ax_accel, dtype=float)[order]
    brake = np.asarray(env.ax_brake, dtype=float)[order]
    feasible = np.isfinite(accel) & np.isfinite(brake)
    if np.count_nonzero(feasible) < 2:
        return float("nan")
    width = np.maximum(accel[feasible] - brake[feasible], 0.0)
    return _trapz(width, ay[feasible])


def _straightline_capacity_by_speed(envelopes: list[GGVEnvelope]) -> list[dict[str, float]]:
    rows: list[dict[str, float]] = []
    for env in envelopes:
        idx = int(np.nanargmin(np.abs(env.ay)))
        rows.append(
            {
                "speed_mps": float(env.speed),
                "ax_accel_mps2": float(env.ax_accel[idx]),
                "brake_decel_mps2": float(abs(env.ax_brake[idx])),
            }
        )
    return sorted(rows, key=lambda row: row["speed_mps"])


def _nearest_corner_index(
    corner_speeds: dict[int, float],
    idx: int,
    *,
    direction: int,
    n: int,
) -> int:
    for step in range(1, n + 1):
        candidate = (idx + direction * step) % n
        if candidate in corner_speeds:
            return candidate
    raise ValueError("No corner found in path-style GGV track profile.")


def _integrate_straight_profile(
    envelopes: list[GGVEnvelope],
    *,
    distance_m: float,
    start_speed_mps: float,
    end_speed_mps: float,
    step_m: float,
) -> dict[str, float]:
    summary, _, _, _ = _integrate_straight_profile_points(
        envelopes,
        distance_m=distance_m,
        start_speed_mps=start_speed_mps,
        end_speed_mps=end_speed_mps,
        step_m=step_m,
    )
    return summary


def _integrate_straight_profile_points(
    envelopes: list[GGVEnvelope],
    *,
    distance_m: float,
    start_speed_mps: float,
    end_speed_mps: float,
    step_m: float,
) -> tuple[dict[str, float], np.ndarray, np.ndarray, np.ndarray]:
    if distance_m <= 0.0:
        speed = max(start_speed_mps, 0.0)
        return (
            {
                "mean_speed_mps": speed,
                "peak_speed_mps": speed,
                "accel_mean_mps2": 0.0,
                "brake_mean_mps2": 0.0,
                "longitudinal_mean_mps2": 0.0,
                "accel_distance_fraction": 0.0,
                "brake_distance_fraction": 0.0,
                "coast_distance_fraction": 1.0,
            },
            np.array([0.0], dtype=float),
            np.array([speed], dtype=float),
            np.array([], dtype=float),
        )

    straightline = _straightline_capacity_by_speed(envelopes)
    speeds = np.array([row["speed_mps"] for row in straightline], dtype=float)
    accel_capacity = np.array([row["ax_accel_mps2"] for row in straightline], dtype=float)
    brake_capacity = np.array([row["brake_decel_mps2"] for row in straightline], dtype=float)

    n_steps = max(1, int(np.ceil(distance_m / max(step_m, 0.1))))
    ds = distance_m / n_steps
    distance_points = np.linspace(0.0, distance_m, n_steps + 1)
    forward = np.empty(n_steps + 1, dtype=float)
    backward = np.empty(n_steps + 1, dtype=float)
    forward[0] = max(start_speed_mps, 0.0)
    backward[-1] = max(end_speed_mps, 0.0)

    for i in range(n_steps):
        accel = _interp_speed_capacity(speeds, accel_capacity, forward[i])
        forward[i + 1] = np.sqrt(
            max(forward[i] ** 2 + 2.0 * max(accel, 0.0) * ds, 0.0)
        )

    for i in range(n_steps - 1, -1, -1):
        brake = _interp_speed_capacity(speeds, brake_capacity, backward[i + 1])
        backward[i] = np.sqrt(
            max(backward[i + 1] ** 2 + 2.0 * max(brake, 0.0) * ds, 0.0)
        )

    velocity = np.minimum(forward, backward)
    velocity[0] = min(velocity[0], max(start_speed_mps, 0.0))
    velocity[-1] = min(velocity[-1], max(end_speed_mps, 0.0))

    segment_ax = (velocity[1:] ** 2 - velocity[:-1] ** 2) / (2.0 * ds)
    segment_speed = 0.5 * (velocity[1:] + velocity[:-1])
    accel_segments = segment_ax > 1e-4
    brake_segments = segment_ax < -1e-4
    coast_segments = ~(accel_segments | brake_segments)

    summary = {
        "mean_speed_mps": float(np.average(segment_speed)),
        "peak_speed_mps": float(np.nanmax(velocity)),
        "accel_mean_mps2": _positive_segment_mean(segment_ax, accel_segments),
        "brake_mean_mps2": _positive_segment_mean(-segment_ax, brake_segments),
        "longitudinal_mean_mps2": float(np.nanmean(np.abs(segment_ax))),
        "accel_distance_fraction": float(np.mean(accel_segments)),
        "brake_distance_fraction": float(np.mean(brake_segments)),
        "coast_distance_fraction": float(np.mean(coast_segments)),
    }
    return summary, distance_points, velocity, segment_ax


def _interp_speed_capacity(speeds: np.ndarray, values: np.ndarray, speed: float) -> float:
    valid = np.isfinite(speeds) & np.isfinite(values)
    if not np.any(valid):
        return 0.0
    order = np.argsort(speeds[valid])
    return float(np.interp(speed, speeds[valid][order], values[valid][order]))


def _positive_segment_mean(values: np.ndarray, mask: np.ndarray) -> float:
    if not np.any(mask):
        return 0.0
    return float(np.nanmean(values[mask]))


def _corner_speed_for_radius(envelopes: list[GGVEnvelope], radius_m: float) -> float:
    speeds = np.array([float(env.speed) for env in envelopes], dtype=float)
    ay_limits = np.array([_max_lateral_mps2(env) for env in envelopes], dtype=float)
    valid = np.isfinite(speeds) & np.isfinite(ay_limits) & (ay_limits > 0.0)
    if not np.any(valid):
        return float("nan")
    speeds = speeds[valid]
    ay_limits = ay_limits[valid]
    order = np.argsort(speeds)
    speeds = speeds[order]
    ay_limits = ay_limits[order]
    dense_speeds = np.linspace(float(speeds[0]), float(speeds[-1]), 501)
    dense_ay = np.interp(dense_speeds, speeds, ay_limits)
    feasible = dense_speeds**2 / radius_m <= dense_ay
    if np.any(feasible):
        return float(np.max(dense_speeds[feasible]))
    return float(min(np.sqrt(max(float(ay_limits[0]), 0.0) * radius_m), speeds[0]))


def _max_lateral_mps2(env: GGVEnvelope) -> float:
    feasible = np.isfinite(env.ax_accel) | np.isfinite(env.ax_brake)
    if not np.any(feasible):
        return float("nan")
    return float(np.nanmax(np.abs(env.ay[feasible])))


def _mean_capacity_over_speed(
    rows: list[dict[str, float]],
    column: str,
    speed_start: float,
    speed_end: float,
) -> float:
    speeds = np.array([row["speed_mps"] for row in rows], dtype=float)
    values = np.array([row[column] for row in rows], dtype=float)
    valid = np.isfinite(speeds) & np.isfinite(values)
    if not np.any(valid):
        return float("nan")
    speeds = speeds[valid]
    values = values[valid]
    order = np.argsort(speeds)
    speeds = speeds[order]
    values = values[order]
    low, high = sorted((speed_start, speed_end))
    low = max(low, float(speeds[0]))
    high = min(high, float(speeds[-1]))
    if high <= low:
        speed = min(max(0.5 * (speed_start + speed_end), speeds[0]), speeds[-1])
        return float(np.interp(speed, speeds, values))
    dense = np.linspace(low, high, 101)
    interpolated = np.interp(dense, speeds, values)
    return _trapz(interpolated, dense) / (high - low)


def _weighted_score(rows: list[dict[str, float | str]]) -> float:
    scores = np.array([float(row["score"]) for row in rows], dtype=float)
    weights = np.array([float(row["weight"]) for row in rows], dtype=float)
    valid = np.isfinite(scores) & np.isfinite(weights) & (weights > 0.0)
    if not np.any(valid):
        return float("nan")
    return float(np.average(scores[valid], weights=weights[valid]))


def _distance_weighted(rows: list[dict[str, float | str]], key: str) -> float:
    if not rows:
        return float("nan")
    values = np.array([float(row.get(key, np.nan)) for row in rows], dtype=float)
    distances = np.array(
        [float(row.get("distance_m", row.get("weight", np.nan))) for row in rows],
        dtype=float,
    )
    valid = np.isfinite(values) & np.isfinite(distances) & (distances > 0.0)
    if not np.any(valid):
        return float("nan")
    return float(np.average(values[valid], weights=distances[valid]))


def _max_row(rows: list[dict[str, float]], key: str) -> dict[str, float]:
    valid = [row for row in rows if np.isfinite(row[key])]
    if not valid:
        if rows:
            return {**rows[0], key: float("nan")}
        return {"speed_mps": float("nan"), key: float("nan")}
    return max(valid, key=lambda row: row[key])


def _min_row(rows: list[dict[str, float]], key: str) -> dict[str, float]:
    valid = [row for row in rows if np.isfinite(row[key])]
    if not valid:
        if rows:
            return {**rows[0], key: float("nan")}
        return {"speed_mps": float("nan"), key: float("nan")}
    return min(valid, key=lambda row: row[key])


def _min_valid(values: np.ndarray) -> float:
    valid = values[np.isfinite(values)]
    if valid.size == 0:
        return float("nan")
    return float(np.nanmin(valid))


def _speed_average_valid(speeds: np.ndarray, values: np.ndarray) -> float:
    valid = np.isfinite(speeds) & np.isfinite(values)
    if np.count_nonzero(valid) == 0:
        return float("nan")
    if np.count_nonzero(valid) == 1:
        return float(values[valid][0])

    speed_valid = speeds[valid]
    value_valid = values[valid]
    order = np.argsort(speed_valid)
    speed_sorted = speed_valid[order]
    value_sorted = value_valid[order]
    speed_span = float(speed_sorted[-1] - speed_sorted[0])
    if speed_span <= 0.0:
        return float(np.nanmean(value_sorted))
    return _trapz(value_sorted, speed_sorted) / speed_span


def _safe_ratio(numerator: float, denominator: float) -> float:
    if not np.isfinite(numerator) or not np.isfinite(denominator):
        return float("nan")
    if abs(denominator) <= 1e-12:
        return float("nan")
    return float(numerator / denominator)


def _ggv_area_fill_factor(
    area_g2: float,
    cornering_g: float,
    accel_g: float,
    braking_g: float,
) -> float:
    bounds_area_g2 = 2.0 * cornering_g * (accel_g + braking_g)
    return _safe_ratio(area_g2, bounds_area_g2)


def _integrate_valid(x: np.ndarray, y: np.ndarray) -> float:
    valid = np.isfinite(x) & np.isfinite(y)
    if np.count_nonzero(valid) < 2:
        return float("nan")
    order = np.argsort(x[valid])
    return _trapz(y[valid][order], x[valid][order])


def _interp_valid(x: np.ndarray, y: np.ndarray, target: float) -> float:
    valid = np.isfinite(x) & np.isfinite(y)
    if not np.any(valid):
        return float("nan")
    order = np.argsort(x[valid])
    return float(np.interp(target, x[valid][order], y[valid][order]))


def _trapz(y: np.ndarray, x: np.ndarray) -> float:
    if hasattr(np, "trapezoid"):
        return float(np.trapezoid(y, x))
    return float(np.trapz(y, x))


def main() -> None:
    import sys

    repo_root = REPO_ROOT
    if str(repo_root) not in sys.path:
        sys.path.insert(0, str(repo_root))

    from _2_EnvelopeSim.vehicle_yaml import load_vehicle_yaml, project_vehicle_yaml

    config_path = DEFAULT_GGV_CONFIG
    ggv_report_config = load_ggv_config(config_path)
    vehicle_template = ggv_report_config.get("vehicle_template", "../../vehicle.yml")
    vehicle_path = resolve_ggv_output_path(config_path, vehicle_template)
    projection = project_vehicle_yaml(
        load_vehicle_yaml(vehicle_path),
        repo_root=repo_root,
    )
    vehicle = projection.ggv

    print("Aero values from vehicle.yml nominal ride height:")
    print(f"  reference speed = {projection.summary['reference_speed_m_per_s']:.3f} m/s")
    print(f"  downforce       = {projection.summary['downforce_n']:.3f} N")
    print(f"  drag            = {projection.summary['drag_n']:.3f} N")
    print(f"  ClA             = {vehicle.cl_a:.4f} m^2")
    print(f"  CdA             = {vehicle.cd_a:.4f} m^2")
    print(f"  front balance   = {100.0 * vehicle.aero_balance_front:.1f}%")

    print("\nVehicle values from vehicle.yml:")
    print(f"  mass       = {vehicle.mass:.2f} kg")
    print(f"  wheelbase  = {vehicle.wheelbase:.4f} m")
    print(f"  front track= {vehicle.track_front:.4f} m")
    print(f"  rear track = {vehicle.track_rear:.4f} m")
    print(f"  CG height  = {vehicle.cg_height:.4f} m")
    print(f"  static Fz/tire ~= {vehicle.mass * G / 4.0:.1f} N")

    print("\nTire peak model:")
    print(f"  FNOMIN = {vehicle.fz_ref:.1f} N")
    print(
        f"  mu_x(FNOMIN) ≈ "
        f"{tire_mu_x(vehicle, np.array([vehicle.fz_ref], dtype=np.float64))[0]:.3f}"
    )
    print(
        f"  mu_y(FNOMIN) ≈ "
        f"{tire_mu_y(vehicle, np.array([vehicle.fz_ref], dtype=np.float64))[0]:.3f}"
    )
    print(
        f"  valid Fz range = "
        f"{vehicle.fz_min_valid:.1f} to {vehicle.fz_max_valid:.1f} N"
    )

    config = config_to_ggv_config(ggv_report_config)

    envelopes = generate_ggv(vehicle, config)

    report_cfg = ggv_report_config.get("report") or {}
    results_dir = ENVELOPE_DIR / "results"
    build_dir = BUILD_DIR
    results_dir.mkdir(parents=True, exist_ok=True)
    build_dir.mkdir(parents=True, exist_ok=True)

    raw_output_path = resolve_ggv_output_path(
        config_path,
        report_cfg.get("raw_output_path", "../Build/GGV/ggv_first_principles.csv"),
    )
    metrics_output_path = resolve_ggv_output_path(
        config_path,
        report_cfg.get("metrics_output_path", "../results/ggv_report_metrics.csv"),
    )
    track_output_path = resolve_ggv_output_path(
        config_path,
        report_cfg.get(
            "track_profile_output_path",
            "../Build/GGV/ggv_track_performance_profile.csv",
        ),
    )
    velocity_profile_output_path = resolve_ggv_output_path(
        config_path,
        report_cfg.get(
            "velocity_profile_output_path",
            "../Build/GGV/ggv_track_velocity_profile.csv",
        ),
    )
    pdf_output_path = resolve_ggv_output_path(
        config_path,
        report_cfg.get("output_path", "../results/ggv_report.pdf"),
    )
    reference_speed = float(report_cfg.get("reference_speed_mps", 15.0))
    track_profile = track_profile_from_config(ggv_report_config)
    summary, capability_rows, track_rows = summarize_ggv(
        envelopes,
        reference_speed_mps=reference_speed,
        track_profile=track_profile,
    )
    velocity_rows = track_velocity_profile_rows(envelopes, track_profile)

    save_ggv_csv(envelopes, raw_output_path)
    save_metric_rows(ggv_metric_rows(summary), metrics_output_path)
    save_track_profile_csv(track_rows, track_output_path)
    save_velocity_profile_csv(velocity_rows, velocity_profile_output_path)
    if bool(report_cfg.get("enabled", True)):
        build_ggv_report_pdf(
            envelopes,
            summary=summary,
            capability_rows=capability_rows,
            track_rows=track_rows,
            velocity_rows=velocity_rows,
            projection_summary=projection.summary,
            config=ggv_report_config,
            output_path=pdf_output_path,
        )


if __name__ == "__main__":
    main()
