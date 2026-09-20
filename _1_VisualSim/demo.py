"""Synthetic BobVis scene, for trying the viewer without running a simulation.

    python -m _1_VisualSim.demo            # writes config + signals, prints paths
    make visual-demo                       # generate, then open the viewer

The motion here is a kinematic mock-up of a step-steer manoeuvre - roll, heave,
pitch and steer driven by closed-form functions, with double-wishbone corners
articulated about their inboard pickups. It is not physics, and nothing here
feeds a result. It exists so the viewer, the exporter and the docs have
something to run against on a machine with no OpenModelica build.
"""

from __future__ import annotations

import argparse
from pathlib import Path
from typing import Any

import numpy as np
import yaml

OUT_DIR = Path(__file__).resolve().parent / "results"
CONFIG_NAME = "demo_step_steer.yml"
DATA_NAME = "demo_step_steer.npz"

# Vehicle dimensions, metres.
WHEELBASE = 2.60
TRACK = 1.60
TIRE_RADIUS = 0.2032
TIRE_WIDTH = 0.1778
MASS = 1450.0       # kg
CG_HEIGHT = 0.30    # m
FRONT_SHARE = 0.60  # of weight, lateral force and lateral load transfer

CORNERS = {
    "fl": (+1, +1),   # (fore/aft sign, left/right sign)
    "fr": (+1, -1),
    "rl": (-1, +1),
    "rr": (-1, -1),
}


def _rot_z(angle: np.ndarray) -> np.ndarray:
    """Stack of yaw rotation matrices, shape (N, 3, 3)."""
    c, s = np.cos(angle), np.sin(angle)
    zero, one = np.zeros_like(c), np.ones_like(c)
    return np.stack([
        np.stack([c, -s, zero], axis=-1),
        np.stack([s, c, zero], axis=-1),
        np.stack([zero, zero, one], axis=-1),
    ], axis=-2)


def _rot_x(angle: np.ndarray) -> np.ndarray:
    c, s = np.cos(angle), np.sin(angle)
    zero, one = np.zeros_like(c), np.ones_like(c)
    return np.stack([
        np.stack([one, zero, zero], axis=-1),
        np.stack([zero, c, -s], axis=-1),
        np.stack([zero, s, c], axis=-1),
    ], axis=-2)


def _rot_y(angle: np.ndarray) -> np.ndarray:
    c, s = np.cos(angle), np.sin(angle)
    zero, one = np.zeros_like(c), np.ones_like(c)
    return np.stack([
        np.stack([c, zero, s], axis=-1),
        np.stack([zero, one, zero], axis=-1),
        np.stack([-s, zero, c], axis=-1),
    ], axis=-2)


def _smooth_step(t: np.ndarray, t0: float, tau: float) -> np.ndarray:
    """0 before ``t0``, rising to 1 with time constant ``tau``."""
    return np.where(t < t0, 0.0, 1.0 - np.exp(-np.clip(t - t0, 0.0, None) / tau))


class DemoVehicle:
    """Body states plus articulated corner geometry over a step steer."""

    def __init__(self, duration: float = 8.0, rate: float = 200.0,
                 speed: float = 22.0) -> None:
        self.time = np.arange(0.0, duration, 1.0 / rate)
        self.speed = speed
        n = self.time.size

        # -- driver input and body response --------------------------------
        step = _smooth_step(self.time, 1.5, 0.28)
        release = _smooth_step(self.time, 5.5, 0.28)
        self.steer = np.deg2rad(95.0) * (step - release)          # handwheel
        road_steer = self.steer / 14.0                            # steering ratio

        self.yaw_rate = self.speed / WHEELBASE * np.tan(road_steer)
        self.yaw = np.concatenate(([0.0], np.cumsum(self.yaw_rate[1:] / rate)))
        self.accel_y = self.speed * self.yaw_rate

        # Roll and pitch lag the lateral acceleration slightly.
        lag = np.exp(-np.arange(0, 12) / 4.0)
        lag /= lag.sum()
        ay_lagged = np.convolve(self.accel_y, lag, mode="same")
        self.roll = np.deg2rad(0.32) * ay_lagged
        self.pitch = np.deg2rad(-0.10) * np.gradient(self.speed * np.ones(n), self.time)
        self.heave = -0.004 * np.abs(ay_lagged) + 0.002 * np.sin(2.4 * self.time)

        # -- path ----------------------------------------------------------
        heading = self.yaw
        vx = self.speed * np.cos(heading)
        vy = self.speed * np.sin(heading)
        self.position = np.stack([
            np.concatenate(([0.0], np.cumsum(vx[1:] / rate))),
            np.concatenate(([0.0], np.cumsum(vy[1:] / rate))),
            self.heave,  # the body frame's origin sits on the road
        ], axis=1)

        self.road_steer = road_steer
        self.R_body = _rot_z(self.yaw) @ _rot_y(self.pitch) @ _rot_x(self.roll)

        # Per-corner wheel travel relative to the body. Heave, roll and pitch
        # move each corner of the body; the wheel moves the opposite way, so
        # the tire stays on the road. (It used to move with the body, which
        # lifted the inside wheels clear of the ground mid-corner.)
        self.travel = {
            name: -(self.heave
                    + 0.5 * TRACK * side * np.sin(self.roll)
                    - 0.5 * WHEELBASE * fore * np.sin(self.pitch))
            for name, (fore, side) in CORNERS.items()
        }

        def axle_share(fore: int) -> float:
            return FRONT_SHARE if fore > 0 else 1.0 - FRONT_SHARE

        # Vertical load: static weight plus lateral load transfer onto the
        # outside tires, which are the right-hand ones when accel_y > 0.
        transfer = MASS * self.accel_y * CG_HEIGHT / TRACK
        self.tire_load = {
            name: 0.5 * MASS * 9.81 * axle_share(fore) - side * axle_share(fore) * transfer
            for name, (fore, side) in CORNERS.items()
        }

        # Lateral tire force, biased toward the more heavily loaded outside
        # tires. Illustrative only.
        total = MASS * self.accel_y
        self.tire_force_y = {
            name: total * 0.5 * axle_share(fore)
                  * (1.0 - 0.35 * np.sign(side) * np.tanh(self.accel_y / 6.0))
            for name, (fore, side) in CORNERS.items()
        }

    # -- geometry -----------------------------------------------------------
    def corner_points(self, name: str) -> dict[str, np.ndarray]:
        """Body-frame point trajectories for one corner, shape (N, 3) each."""
        fore, side = CORNERS[name]
        x0 = fore * WHEELBASE / 2.0
        y = side
        travel = self.travel[name]
        n = self.time.size

        def fixed(x: float, y_: float, z: float) -> np.ndarray:
            return np.tile(np.array([x0 + x, y * y_, z]), (n, 1))

        inboard = {
            "LowerFore_i": fixed(+0.14, 0.24, 0.13),
            "LowerAft_i": fixed(-0.16, 0.24, 0.14),
            "UpperFore_i": fixed(+0.11, 0.28, 0.36),
            "UpperAft_i": fixed(-0.13, 0.28, 0.37),
            "Tie_i": fixed(fore * 0.17, 0.26, 0.19),
            "BellcrankPivot": fixed(-0.02, 0.31, 0.44),
            "ShockInboard": fixed(-0.30, 0.08, 0.46),
            "ArbInboard": fixed(-0.24, 0.20, 0.30),
        }

        # Outboard points ride with the upright: vertical travel plus a little
        # camber gain about the contact patch, and steer for the front axle.
        camber = np.deg2rad(-1.0) - np.deg2rad(14.0) * travel
        steer = self.road_steer if fore > 0 else np.zeros(n)
        R_upright = _rot_z(steer) @ _rot_x(side * camber)

        wheel_center = np.stack([
            np.full(n, x0),
            np.full(n, y * TRACK / 2.0),
            TIRE_RADIUS + travel,
        ], axis=1)

        def outboard(dx: float, dy: float, dz: float) -> np.ndarray:
            local = np.array([dx, y * dy, dz])
            return wheel_center + np.einsum("nij,j->ni", R_upright, local)

        points = {
            "Lower_o": outboard(0.0, -0.09, -0.075),
            "Upper_o": outboard(-0.01, -0.15, 0.145),
            "Tie_o": outboard(fore * 0.12, -0.11, 0.005),
            "WheelCenter": wheel_center,
            "ContactPatch": wheel_center - np.array([0.0, 0.0, TIRE_RADIUS]),
        }
        points.update(inboard)

        # Pushrod runs from the lower wishbone up to the bellcrank; the
        # bellcrank rocks with travel and drives the shock.
        rocker = -2.2 * travel
        pivot = inboard["BellcrankPivot"]
        points["PushrodOutboard"] = outboard(-0.02, -0.05, -0.03)
        points["BellcrankPushrod"] = pivot + np.stack([
            0.05 + 0.02 * np.cos(rocker),
            y * (-0.09) * np.ones(n),
            -0.10 * np.cos(rocker),
        ], axis=1)
        points["BellcrankShock"] = pivot + np.stack([
            -0.10 * np.cos(rocker) - 0.03,
            y * (-0.05) * np.ones(n),
            0.02 + 0.09 * np.sin(rocker),
        ], axis=1)
        points["ArbOutboard"] = outboard(-0.16, -0.06, -0.02)
        return points

    def tire_axes(self, name: str) -> tuple[np.ndarray, np.ndarray]:
        """Tire longitudinal (ex) and lateral (ey) unit vectors, body frame."""
        fore, side = CORNERS[name]
        n = self.time.size
        steer = self.road_steer if fore > 0 else np.zeros(n)
        R = _rot_z(steer)
        ex = np.einsum("nij,j->ni", R, np.array([1.0, 0.0, 0.0]))
        ey = np.einsum("nij,j->ni", R, np.array([0.0, 1.0, 0.0]))
        return ex, ey

    def to_world(self, body_points: np.ndarray) -> np.ndarray:
        return self.position + np.einsum("nij,nj->ni", self.R_body, body_points)

    def to_world_dir(self, body_dirs: np.ndarray) -> np.ndarray:
        return np.einsum("nij,nj->ni", self.R_body, body_dirs)


# ---------------------------------------------------------------------------
# Signal + config assembly
# ---------------------------------------------------------------------------

LINK_GROUPS = {
    "lower": [("LowerFore_i", "Lower_o"), ("LowerAft_i", "Lower_o")],
    "upper": [("UpperFore_i", "Upper_o"), ("UpperAft_i", "Upper_o")],
    "tie": [("Tie_i", "Tie_o")],
    "upright": [("Lower_o", "Upper_o"), ("Lower_o", "WheelCenter"),
                ("Upper_o", "WheelCenter"), ("Tie_o", "WheelCenter")],
    "pushrod": [("PushrodOutboard", "BellcrankPushrod")],
    "bellcrank": [("BellcrankPivot", "BellcrankPushrod"),
                  ("BellcrankPivot", "BellcrankShock")],
    "shock": [("BellcrankShock", "ShockInboard")],
    "arb": [("ArbOutboard", "ArbInboard")],
}

CHASSIS_LINKS = [
    ("fl_LowerFore_i", "fr_LowerFore_i"),
    ("rl_LowerFore_i", "rr_LowerFore_i"),
    ("fl_LowerFore_i", "rl_LowerFore_i"),
    ("fr_LowerFore_i", "rr_LowerFore_i"),
    ("fl_UpperAft_i", "fr_UpperAft_i"),
    ("rl_UpperAft_i", "rr_UpperAft_i"),
    ("fl_UpperAft_i", "rl_UpperAft_i"),
    ("fr_UpperAft_i", "rr_UpperAft_i"),
    ("fl_ArbInboard", "fr_ArbInboard"),
    ("rl_ArbInboard", "rr_ArbInboard"),
]


def build(duration: float = 8.0) -> tuple[dict[str, np.ndarray], dict[str, Any]]:
    car = DemoVehicle(duration=duration)
    signals: dict[str, np.ndarray] = {"time": car.time}

    points_cfg: dict[str, list[str]] = {}
    links_cfg: dict[str, list[list[str]]] = {k: [] for k in LINK_GROUPS}
    links_cfg["chassis"] = []
    tires_cfg: dict[str, Any] = {}
    vectors_cfg: dict[str, Any] = {"tire_force": {}}
    loads_cfg: dict[str, Any] = {}

    def emit_point(name: str, world: np.ndarray) -> None:
        cols = []
        for axis, index in (("x", 0), ("y", 1), ("z", 2)):
            key = f"pos/{name}_{axis}"
            signals[key] = world[:, index]
            cols.append(key)
        points_cfg[name] = cols

    for corner in CORNERS:
        body_points = car.corner_points(corner)
        for local_name, body in body_points.items():
            emit_point(f"{corner}_{local_name}", car.to_world(body))

        for group, pairs in LINK_GROUPS.items():
            links_cfg[group].extend(
                [f"{corner}_{a}", f"{corner}_{b}"] for a, b in pairs
            )

        ex, ey = car.tire_axes(corner)
        ex_w, ey_w = car.to_world_dir(ex), car.to_world_dir(ey)
        ex_cols, ey_cols = [], []
        for axis, index in (("x", 0), ("y", 1), ("z", 2)):
            kx, ky = f"tire/{corner}_ex_{axis}", f"tire/{corner}_ey_{axis}"
            signals[kx], signals[ky] = ex_w[:, index], ey_w[:, index]
            ex_cols.append(kx)
            ey_cols.append(ky)

        tires_cfg[corner] = {
            "center": f"{corner}_WheelCenter",
            "x": ex_cols,
            "y": ey_cols,
            "radius": TIRE_RADIUS,
            "width": TIRE_WIDTH,
        }

        force = ey_w * car.tire_force_y[corner][:, None]
        force_cols = []
        for axis, index in (("x", 0), ("y", 1), ("z", 2)):
            key = f"force/{corner}_fy_{axis}"
            signals[key] = force[:, index]
            force_cols.append(key)
        vectors_cfg["tire_force"][corner] = {
            "origin": f"{corner}_ContactPatch",
            "direction": force_cols,
            "scale": 1.0 / 14000.0,
            "color": "#f0932b",
            "shaft_radius": 0.018,
            "tip_radius": 0.045,
        }

        signals[f"load/{corner}_fz"] = car.tire_load[corner]
        loads_cfg[corner] = {"point": f"{corner}_ContactPatch", "signal": f"load/{corner}_fz"}

    links_cfg["chassis"] = [[a, b] for a, b in CHASSIS_LINKS]

    signals["state/handwheel_angle_deg"] = np.rad2deg(car.steer)
    signals["state/lateral_accel_mps2"] = car.accel_y
    signals["state/yaw_rate_degps"] = np.rad2deg(car.yaw_rate)
    signals["state/roll_angle_deg"] = np.rad2deg(car.roll)
    signals["state/speed_mps"] = np.full(car.time.size, car.speed)

    config: dict[str, Any] = {
        "style": {
            "joints": {"radius": 0.014, "color": "#e0483c"},
            "links": {
                "default": {"radius": 0.010, "color": "#33383f"},
                "groups": {
                    "lower": {"radius": 0.011, "color": "#33383f"},
                    "upper": {"radius": 0.011, "color": "#33383f"},
                    "tie": {"radius": 0.009, "color": "#5b636d"},
                    "upright": {"radius": 0.013, "color": "#4a5159"},
                    "chassis": {"radius": 0.016, "color": "#8a929b"},
                    "pushrod": {"radius": 0.010, "color": "#2ca05e"},
                    "bellcrank": {"radius": 0.012, "color": "#e08a2f"},
                    "shock": {"radius": 0.014, "color": "#d64550"},
                    "arb": {"radius": 0.008, "color": "#8a6fd6"},
                },
            },
        },
        "geometry": {
            "points": points_cfg,
            "links": links_cfg,
            "tires": tires_cfg,
            "vectors": vectors_cfg,
        },
        "ground": {
            "tracks": {
                "points": [f"{corner}_ContactPatch" for corner in CORNERS],
                "history": 3.0,
                # CORNERS order is fl, fr, rl, rr.
                "colors": ["#2b7fd4", "#2b7fd4", "#d64550", "#d64550"],
                "legend": "Tracks: last 3 s of each tire, front blue, rear red",
            },
            "loads": {"radius": 0.28, "corners": loads_cfg},
        },
        "render": {"show_signals": True, "speed": 1.0},
        "plots": [
            {"name": "Handwheel (deg)", "x": "time", "y": "state/handwheel_angle_deg"},
            {"name": "Lateral accel (m/s²)", "x": "time", "y": "state/lateral_accel_mps2"},
            {"name": "Yaw rate (deg/s)", "x": "time", "y": "state/yaw_rate_degps"},
            {"name": "Roll (deg)", "x": "time", "y": "state/roll_angle_deg"},
        ],
        "camera": {
            "attach_to": "fl_WheelCenter",
            "forward_pair": ["rl_WheelCenter", "fl_WheelCenter"],
            "origin_offset": {"x": -1.3, "y": -0.8, "z": 0.2},
            "camera_offsets": {"back": 6.0, "height": 2.6},
        },
    }
    return signals, config


def write(out_dir: Path = OUT_DIR, duration: float = 8.0) -> tuple[Path, Path]:
    """Write the demo config and signal file. Returns ``(config, data)``."""
    signals, config = build(duration)
    out_dir.mkdir(parents=True, exist_ok=True)

    config_path = out_dir / CONFIG_NAME
    data_path = out_dir / DATA_NAME

    header = (
        "# Generated by `python -m _1_VisualSim.demo` - a synthetic step steer.\n"
        "# Kinematic mock-up for trying the viewer; not a simulation result.\n"
    )
    with open(config_path, "w", encoding="utf-8") as handle:
        handle.write(header)
        yaml.safe_dump(config, handle, sort_keys=False, default_flow_style=False)

    # numpy's stub types the second positional as `allow_pickle`, so **kwargs
    # of arrays does not typecheck even though it is the documented call.
    np.savez_compressed(data_path, **signals)  # type: ignore[arg-type]
    return config_path, data_path


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        prog="python -m _1_VisualSim.demo",
        description="Generate a synthetic BobVis scene for trying the viewer.",
    )
    parser.add_argument("--out-dir", type=Path, default=OUT_DIR)
    parser.add_argument("--duration", type=float, default=8.0, help="seconds")
    parser.add_argument("--quiet", action="store_true")
    args = parser.parse_args(argv)

    config_path, data_path = write(args.out_dir, args.duration)
    if not args.quiet:
        print(f"[bobvis] config {config_path}")
        print(f"[bobvis] data   {data_path}")
        print(f"[bobvis] open with: python -m _1_VisualSim.viewer "
              f"{config_path} {data_path}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
