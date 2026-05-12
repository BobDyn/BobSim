"""
First-principles GGV envelope generator for BobSim.

This computes quasi-static full-vehicle acceleration envelopes using:
- mass properties
- static weight distribution
- aero downforce / drag
- longitudinal and lateral load transfer
- tire load-sensitive peak friction from .tir coefficients
- powertrain force limit
- brake force limit
- friction ellipse / combined-slip tire usage

The output is:
- 2D ax-ay GGV envelopes at multiple speeds
- 3D closed GGV envelope surface, with speed as the vertical axis
- CSV export with feasibility flags

This is intended as a first-principles BobSim analysis utility. It is not yet
a full Magic Formula combined-slip tire solver or full FMU trim solve.
"""

from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
from typing import Literal

import matplotlib.pyplot as plt
import numpy as np
from numpy.typing import NDArray


G = 9.80665
IN_TO_M = 0.0254
LB_TO_KG = 0.45359237
LBF_PER_IN_TO_N_PER_M = 175.12683524647636
MPH_TO_MPS = 0.44704


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

    # Powertrain / braking
    max_drive_power: float = 80_000.0  # W
    max_drive_force: float = 4_000.0  # N, traction/drivetrain cap before tires
    max_brake_force: float = 12_000.0  # N, brake system cap before tires
    drive_distribution_front: float = 0.0  # 0 for RWD, 1 for FWD, 0.5 for AWD
    brake_distribution_front: float = 0.65

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

    np.savetxt(output_path, data, delimiter=",", header=header, comments="")
    print(f"Saved CSV: {output_path}")


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
    # FRH = 1.4 in, RRH = 1.65 in
    #
    # From averaged CFD report:
    #   Cl = 1.1736
    #   Cd = 0.5863
    #   Downforce Fz = 161.7379 N
    #   Drag Fx = 80.7986 N
    #
    # Use force-derived ClA/CdA so we do not need the CFD reference area.
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
        # Mass properties
        mass=total_mass_kg,
        wheelbase=wheelbase_m,
        track_front=track_front_m,
        track_rear=track_rear_m,
        cg_height=cg_height_m,

        # Static load distribution
        front_static_frac=0.50,

        # Front convention:
        #   LLTD = front lateral load transfer / total lateral load transfer.
        lltd=0.50,

        # Aero
        cl_a=cl_a,
        cd_a=cd_a,
        aero_balance_front=0.50,

        # Powertrain / braking
        # TODO: replace with actual power, gearing, motor curve, brake sizing.
        max_drive_power=80_000.0,
        max_drive_force=3_735.0,
        max_brake_force=14_000.0,
        drive_distribution_front=0.0,  # RWD
        brake_distribution_front=0.62,

        # Tire model from .tir
        fz_ref=654.0,
        fz_min_valid=100.0,
        fz_max_valid=1091.0,

        # .tir longitudinal peak coefficients
        pdx1=2.597991,
        pdx2=-0.618826,

        # .tir lateral peak coefficients
        pdy1=-2.40275,
        pdy2=0.343535,

        mu_min=0.8,
    )

    print("\nVehicle values:")
    print(f"  mass       = {vehicle.mass:.2f} kg")
    print(f"  wheelbase  = {vehicle.wheelbase:.4f} m")
    print(f"  front track= {vehicle.track_front:.4f} m")
    print(f"  rear track = {vehicle.track_rear:.4f} m")
    print(f"  CG height  = {vehicle.cg_height:.4f} m")
    print(f"  static Fz/tire ≈ {vehicle.mass * G / 4.0:.1f} N")

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

    config = GGVConfig(
        speeds=(5.0, 10.0, 15.0, 20.0, 25.0),
        ay_max_g=3.2,
        ay_points=321,
        ax_search_min_g=-3.2,
        ax_search_max_g=2.8,
        ax_search_points=801,
        include_left_right=True,
        verbose=True,
        progress_every=25,
        warn_tire_load_range=True,
    )

    envelopes = generate_ggv(vehicle, config)

    output_dir = Path("results")
    output_dir.mkdir(parents=True, exist_ok=True)

    save_ggv_csv(envelopes, output_dir / "ggv_first_principles.csv")
    plot_ggv(envelopes, output_dir / "ggv_first_principles.png")
    plot_ggv_surface(envelopes, output_dir / "ggv_first_principles_surface.png")
    plot_ggv_metrics(envelopes, output_dir / "ggv_first_principles_metrics.png")


if __name__ == "__main__":
    main()