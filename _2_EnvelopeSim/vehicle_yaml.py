"""Project vehicle.yml into the simplified EnvelopeSim vehicle models.

The EnvelopeSim generators are intentionally lower fidelity than the full
Modelica vehicle. This module keeps that reduction explicit: mass, CG,
wheelbase/track, static load split, effective roll-stiffness lateral load
transfer split, nominal aero, and tire peak coefficients are carried through;
kinematics, compliance, damping, and transient effects are not.
"""

from __future__ import annotations

import csv
from dataclasses import dataclass
import math
from pathlib import Path
import re
from typing import Any

import yaml

from _2_EnvelopeSim.GGV.ggv_generation import VehicleParams as GGVVehicleParams
from _2_EnvelopeSim.YMD.ymd_generation import VehicleParams as YMDVehicleParams


REPO_ROOT = Path(__file__).resolve().parents[1]
DEFAULT_VEHICLE_YAML = REPO_ROOT / "vehicle.yml"
DEFAULT_NOMINAL_RIDE_HEIGHT_M = 0.0762
DEFAULT_FOUR_POST_METRICS = REPO_ROOT / "_3_StandardSim/results/four_post_eval_report_metrics.csv"

# Nominal FourPost-derived roll stiffnesses used only if the report metrics CSV
# is unavailable. The source report presents these as Nm/deg.
NM_PER_DEG_TO_NM_PER_RAD = 1.0 / math.radians(1.0)
DEFAULT_FRONT_SPRING_ROLL_STIFFNESS = 376.0 * NM_PER_DEG_TO_NM_PER_RAD
DEFAULT_REAR_SPRING_ROLL_STIFFNESS = 224.0 * NM_PER_DEG_TO_NM_PER_RAD
DEFAULT_FRONT_ARB_ROLL_STIFFNESS = 809.0 * NM_PER_DEG_TO_NM_PER_RAD
DEFAULT_REAR_ARB_ROLL_STIFFNESS = 868.0 * NM_PER_DEG_TO_NM_PER_RAD
DEFAULT_BRAKE_DISTRIBUTION_FRONT = 0.84


@dataclass(frozen=True)
class EnvelopeVehicleProjection:
    ggv: GGVVehicleParams
    ymd: YMDVehicleParams
    summary: dict[str, float | str]


def load_vehicle_yaml(path: Path = DEFAULT_VEHICLE_YAML) -> dict[str, Any]:
    with path.open() as f:
        data = yaml.safe_load(f)
    if not isinstance(data, dict):
        raise ValueError(f"Vehicle YAML did not parse as a mapping: {path}")
    return data


def project_vehicle_yaml(
    vehicle_data: dict[str, Any],
    *,
    repo_root: Path = REPO_ROOT,
    aero_load_scale: float = 1.0,
    aero_downforce_scale: float | None = None,
    aero_drag_scale: float | None = None,
    aero_balance_front: float | None = None,
    nominal_front_ride_height_m: float | None = None,
    nominal_rear_ride_height_m: float | None = None,
) -> EnvelopeVehicleProjection:
    total_mass, cg = _combined_mass_properties(vehicle_data)

    front_wc = _vector(vehicle_data["front"]["suspension"]["wheel_center_m"])
    rear_wc = _vector(vehicle_data["rear"]["suspension"]["wheel_center_m"])
    wheelbase = abs(front_wc[0] - rear_wc[0])
    track_front = 2.0 * abs(front_wc[1])
    track_rear = 2.0 * abs(rear_wc[1])

    front_static_frac = _clip((cg[0] - rear_wc[0]) / wheelbase, 0.05, 0.95)

    lltd, lltd_summary = _project_lltd(vehicle_data, repo_root=repo_root)

    tire = _read_tire_coefficients(_resolve_tire_path(vehicle_data, repo_root))
    downforce_scale = (
        aero_load_scale if aero_downforce_scale is None else aero_downforce_scale
    )
    drag_scale = aero_load_scale if aero_drag_scale is None else aero_drag_scale
    aero = _project_aero(
        vehicle_data,
        wheelbase=wheelbase,
        aero_downforce_scale=downforce_scale,
        aero_drag_scale=drag_scale,
        aero_balance_front_override=aero_balance_front,
        nominal_front_ride_height_m=nominal_front_ride_height_m,
        nominal_rear_ride_height_m=nominal_rear_ride_height_m,
    )

    shared = {
        "mass": total_mass,
        "wheelbase": wheelbase,
        "track_front": track_front,
        "track_rear": track_rear,
        "cg_height": cg[2],
        "front_static_frac": front_static_frac,
        "lltd": lltd,
        "cl_a": aero["cl_a"],
        "cd_a": aero["cd_a"],
        "aero_balance_front": aero["aero_balance_front"],
        "fz_ref": tire["FNOMIN"],
        "fz_min_valid": tire["FZMIN"],
        "fz_max_valid": tire["FZMAX"],
        "pdy1": tire["PDY1"],
        "pdy2": tire["PDY2"],
        "mu_min": 0.8,
    }

    ggv = GGVVehicleParams(
        **shared,
        max_drive_power=80_000.0,
        drive_distribution_front=0.0,
        brake_distribution_front=DEFAULT_BRAKE_DISTRIBUTION_FRONT,
        pdx1=tire["PDX1"],
        pdx2=tire["PDX2"],
    )
    ymd = YMDVehicleParams(
        **shared,
        steering_ratio=1.0,
        pky1=tire["PKY1"],
        pky2=tire["PKY2"],
    )

    summary: dict[str, float | str] = {
        "mass_kg": total_mass,
        "cg_x_m": cg[0],
        "cg_z_m": cg[2],
        "wheelbase_m": wheelbase,
        "track_front_m": track_front,
        "track_rear_m": track_rear,
        "front_static_frac": front_static_frac,
        **lltd_summary,
        "aero_downforce_scale": downforce_scale,
        "aero_drag_scale": drag_scale,
        **aero,
        "tire_template": str(_resolve_tire_path(vehicle_data, repo_root).name),
        "fz_ref_n": tire["FNOMIN"],
        "fz_min_valid_n": tire["FZMIN"],
        "fz_max_valid_n": tire["FZMAX"],
        "drive_distribution_front": 0.0,
        "brake_distribution_front": DEFAULT_BRAKE_DISTRIBUTION_FRONT,
    }
    return EnvelopeVehicleProjection(ggv=ggv, ymd=ymd, summary=summary)


def _combined_mass_properties(vehicle_data: dict[str, Any]) -> tuple[float, tuple[float, float, float]]:
    masses: list[tuple[float, tuple[float, float, float]]] = [
        (
            float(vehicle_data["sprung_mass"]["mass_kg"]),
            _vector(vehicle_data["sprung_mass"]["cg_m"]),
        ),
        (
            float(vehicle_data["driver_mass"]["mass_kg"]),
            _vector(vehicle_data["driver_mass"]["cg_m"]),
        ),
    ]

    for axle in ("front", "rear"):
        for component in vehicle_data[axle]["masses"].values():
            mass = float(component["mass_kg"])
            cg_left = _vector(component["cg_m"])
            cg_right = (cg_left[0], -cg_left[1], cg_left[2])
            masses.append((mass, cg_left))
            masses.append((mass, cg_right))

    total_mass = sum(mass for mass, _cg in masses)
    if total_mass <= 0.0:
        raise ValueError("Projected EnvelopeSim mass must be positive.")

    weighted = [0.0, 0.0, 0.0]
    for mass, cg in masses:
        weighted[0] += mass * cg[0]
        weighted[1] += mass * cg[1]
        weighted[2] += mass * cg[2]

    return total_mass, (
        weighted[0] / total_mass,
        weighted[1] / total_mass,
        weighted[2] / total_mass,
    )


def _project_lltd(
    vehicle_data: dict[str, Any],
    *,
    repo_root: Path,
) -> tuple[float, dict[str, float | str]]:
    raw_front_bar = _stabar_rate(vehicle_data, "front")
    raw_rear_bar = _stabar_rate(vehicle_data, "rear")
    raw_bar_sum = raw_front_bar + raw_rear_bar
    raw_bar_lltd = (
        raw_front_bar / raw_bar_sum
        if raw_bar_sum > 0.0
        else 0.5
    )

    four_post_metrics = _load_four_post_metrics(repo_root)
    baseline_vehicle = _load_baseline_vehicle_yaml(repo_root)

    base_front_bar = _safe_stabar_rate(baseline_vehicle, "front", raw_front_bar)
    base_rear_bar = _safe_stabar_rate(baseline_vehicle, "rear", raw_rear_bar)

    front_baseline_total = _metric_or_default(
        four_post_metrics,
        "elastic_roll_stiffness_front_Nm_per_rad",
        DEFAULT_FRONT_SPRING_ROLL_STIFFNESS + DEFAULT_FRONT_ARB_ROLL_STIFFNESS,
    )
    rear_baseline_total = _metric_or_default(
        four_post_metrics,
        "elastic_roll_stiffness_rear_Nm_per_rad",
        DEFAULT_REAR_SPRING_ROLL_STIFFNESS + DEFAULT_REAR_ARB_ROLL_STIFFNESS,
    )
    front_baseline_arb = _metric_or_default(
        four_post_metrics,
        "arb_roll_stiffness_front_Nm_per_rad",
        DEFAULT_FRONT_ARB_ROLL_STIFFNESS,
    )
    rear_baseline_arb = _metric_or_default(
        four_post_metrics,
        "arb_roll_stiffness_rear_Nm_per_rad",
        DEFAULT_REAR_ARB_ROLL_STIFFNESS,
    )

    front_spring_roll = _metric_or_default(
        four_post_metrics,
        "spring_roll_stiffness_front_Nm_per_rad",
        front_baseline_total - front_baseline_arb,
    )
    rear_spring_roll = _metric_or_default(
        four_post_metrics,
        "spring_roll_stiffness_rear_Nm_per_rad",
        rear_baseline_total - rear_baseline_arb,
    )
    if front_spring_roll < 0.0:
        front_spring_roll = max(0.0, front_baseline_total - front_baseline_arb)
    if rear_spring_roll < 0.0:
        rear_spring_roll = max(0.0, rear_baseline_total - rear_baseline_arb)

    front_arb_roll = _scaled_nominal_rate(
        nominal=front_baseline_arb,
        current=raw_front_bar,
        baseline=base_front_bar,
    )
    rear_arb_roll = _scaled_nominal_rate(
        nominal=rear_baseline_arb,
        current=raw_rear_bar,
        baseline=base_rear_bar,
    )

    total_front = front_spring_roll + front_arb_roll
    total_rear = rear_spring_roll + rear_arb_roll
    total_roll = total_front + total_rear
    lltd = total_front / total_roll if total_roll > 0.0 else raw_bar_lltd
    lltd = _clip(lltd, 0.05, 0.95)
    lltd_source = (
        "four_post_report_roll_stiffness"
        if four_post_metrics
        else "nominal_roll_stiffness_defaults"
    )

    summary: dict[str, float | str] = {
        "lltd_front_frac": lltd,
        "lltd_front_pct": 100.0 * lltd,
        "lltd_bar_rate_only_front_frac": raw_bar_lltd,
        "lltd_bar_rate_only_front_pct": 100.0 * raw_bar_lltd,
        "lltd_model": "direct_roll_stiffness",
        "lltd_source": lltd_source,
        "lltd_four_post_report_front_frac": four_post_metrics.get(
            "avg_lltd_front_frac",
            float("nan"),
        ),
        "front_spring_roll_stiffness_nm_per_rad": front_spring_roll,
        "rear_spring_roll_stiffness_nm_per_rad": rear_spring_roll,
        "front_arb_roll_stiffness_nm_per_rad": front_arb_roll,
        "rear_arb_roll_stiffness_nm_per_rad": rear_arb_roll,
        "front_total_roll_stiffness_nm_per_rad": total_front,
        "rear_total_roll_stiffness_nm_per_rad": total_rear,
        "front_baseline_total_roll_stiffness_nm_per_rad": front_baseline_total,
        "rear_baseline_total_roll_stiffness_nm_per_rad": rear_baseline_total,
        "front_baseline_stabar_rate_n_m_per_rad": base_front_bar,
        "rear_baseline_stabar_rate_n_m_per_rad": base_rear_bar,
        "front_current_stabar_rate_n_m_per_rad": raw_front_bar,
        "rear_current_stabar_rate_n_m_per_rad": raw_rear_bar,
        # Legacy name retained for downstream readers that already inspect it.
        "lltd_arb_only": raw_bar_lltd,
    }
    return lltd, summary


def _stabar_rate(vehicle_data: dict[str, Any], axle: str) -> float:
    return float(vehicle_data[axle]["actuation"]["stabar"]["rate_n_m_per_rad"])


def _safe_stabar_rate(vehicle_data: dict[str, Any], axle: str, default: float) -> float:
    try:
        value = _stabar_rate(vehicle_data, axle)
    except (KeyError, TypeError, ValueError):
        return default
    return value if _is_finite(value) else default


def _load_four_post_metrics(repo_root: Path) -> dict[str, float]:
    path = repo_root / DEFAULT_FOUR_POST_METRICS.relative_to(REPO_ROOT)
    if not path.exists():
        return {}
    metrics: dict[str, float] = {}
    with path.open(newline="") as f:
        for row in csv.DictReader(f):
            metric = row.get("metric")
            value = row.get("value")
            if metric is None or value is None:
                continue
            try:
                metrics[metric] = float(value)
            except ValueError:
                continue
    return metrics


def _load_baseline_vehicle_yaml(repo_root: Path) -> dict[str, Any]:
    path = repo_root / DEFAULT_VEHICLE_YAML.relative_to(REPO_ROOT)
    if not path.exists():
        return {}
    return load_vehicle_yaml(path)


def _scaled_nominal_rate(
    *,
    nominal: float,
    current: float,
    baseline: float,
) -> float:
    if not _is_finite(nominal):
        return 0.0
    if not all(_is_finite(value) for value in (current, baseline)):
        return nominal
    if abs(baseline) <= 1e-12:
        return nominal
    return nominal * current / baseline


def _metric_or_default(metrics: dict[str, float], key: str, default: float) -> float:
    value = metrics.get(key, default)
    return value if _is_finite(value) else default


def _is_finite(value: float) -> bool:
    try:
        return math.isfinite(value)
    except TypeError:
        return False


def _project_aero(
    vehicle_data: dict[str, Any],
    *,
    wheelbase: float,
    aero_downforce_scale: float,
    aero_drag_scale: float,
    aero_balance_front_override: float | None,
    nominal_front_ride_height_m: float | None,
    nominal_rear_ride_height_m: float | None,
) -> dict[str, float]:
    aero = vehicle_data.get("aero", {})
    if not aero:
        return {
            "nominal_front_ride_height_m": float("nan"),
            "nominal_rear_ride_height_m": float("nan"),
            "reference_speed_m_per_s": float("nan"),
            "drag_n": 0.0,
            "downforce_n": 0.0,
            "my_nm": 0.0,
            "cop_from_front_m": wheelbase * 0.5,
            "aero_balance_front_map": 0.5,
            "aero_balance_front": 0.5,
            "cl_a": 0.0,
            "cd_a": 0.0,
        }

    frh = float(
        nominal_front_ride_height_m
        if nominal_front_ride_height_m is not None
        else aero.get("nominal_front_ride_height_m", DEFAULT_NOMINAL_RIDE_HEIGHT_M)
    )
    rrh = float(
        nominal_rear_ride_height_m
        if nominal_rear_ride_height_m is not None
        else aero.get("nominal_rear_ride_height_m", DEFAULT_NOMINAL_RIDE_HEIGHT_M)
    )

    front_grid = [float(v) for v in aero["front_ride_height_grid_m"]]
    rear_grid = [float(v) for v in aero["rear_ride_height_grid_m"]]
    drag_n = aero_drag_scale * _bilinear(front_grid, rear_grid, aero["drag_table_n"], frh, rrh)
    downforce_n = aero_downforce_scale * _bilinear(
        front_grid,
        rear_grid,
        aero["downforce_table_n"],
        frh,
        rrh,
    )
    my_nm = aero_downforce_scale * _bilinear(front_grid, rear_grid, aero["my_table_nm"], frh, rrh)

    reference_speed = float(aero["reference_speed_m_per_s"])
    cl_a, cd_a = _force_to_aero_area(downforce_n, drag_n, reference_speed)

    aero_ref_x = float(aero.get("aero_ref_m", [0.0, 0.0, 0.0])[0])
    if abs(downforce_n) > 1e-9:
        cop_from_aero_ref_m = -my_nm / downforce_n
        cop_from_front_m = _clip(cop_from_aero_ref_m - aero_ref_x, 0.0, wheelbase)
    else:
        cop_from_front_m = wheelbase * 0.5

    aero_balance_front_map = _clip(1.0 - cop_from_front_m / wheelbase, 0.0, 1.0)
    aero_balance_front = (
        aero_balance_front_map
        if aero_balance_front_override is None
        else _clip(aero_balance_front_override, 0.0, 1.0)
    )

    return {
        "nominal_front_ride_height_m": frh,
        "nominal_rear_ride_height_m": rrh,
        "reference_speed_m_per_s": reference_speed,
        "drag_n": drag_n,
        "downforce_n": downforce_n,
        "my_nm": my_nm,
        "cop_from_front_m": cop_from_front_m,
        "aero_balance_front_map": aero_balance_front_map,
        "aero_balance_front": aero_balance_front,
        "cl_a": cl_a,
        "cd_a": cd_a,
    }


def _resolve_tire_path(vehicle_data: dict[str, Any], repo_root: Path) -> Path:
    tire_template = (
        vehicle_data.get("aero", {}).get("tire_template")
        or vehicle_data["front"]["tire"]["template"]
    )
    tire_templates = vehicle_data.get("paths", {}).get(
        "tire_templates",
        "_0_Utils/external/BobLib/Generation/tire_templates",
    )
    tire_path = repo_root / tire_templates / f"{tire_template}.tir"
    if not tire_path.exists():
        raise FileNotFoundError(f"Tire template not found: {tire_path}")
    return tire_path


def _read_tire_coefficients(path: Path) -> dict[str, float]:
    required = {"FNOMIN", "FZMIN", "FZMAX", "PDX1", "PDX2", "PDY1", "PDY2", "PKY1", "PKY2"}
    values: dict[str, float] = {}
    pattern = re.compile(r"^\s*([A-Z0-9_]+)\s*=\s*([-+0-9.eE]+)")
    for line in path.read_text().splitlines():
        match = pattern.match(line)
        if not match:
            continue
        key, value = match.groups()
        if key in required:
            values[key] = float(value)

    missing = sorted(required - values.keys())
    if missing:
        raise ValueError(f"Missing tire coefficients in {path}: {', '.join(missing)}")
    return values


def _bilinear(
    x_grid: list[float],
    y_grid: list[float],
    table: list[list[float]],
    x: float,
    y: float,
) -> float:
    x0_i, x1_i, tx = _bracket(x_grid, x)
    y0_i, y1_i, ty = _bracket(y_grid, y)
    q00 = float(table[x0_i][y0_i])
    q10 = float(table[x1_i][y0_i])
    q01 = float(table[x0_i][y1_i])
    q11 = float(table[x1_i][y1_i])

    return (
        (1.0 - tx) * (1.0 - ty) * q00
        + tx * (1.0 - ty) * q10
        + (1.0 - tx) * ty * q01
        + tx * ty * q11
    )


def _bracket(grid: list[float], value: float) -> tuple[int, int, float]:
    if len(grid) < 2:
        raise ValueError("Bilinear interpolation needs at least two grid points.")
    if value <= grid[0]:
        return 0, 1, 0.0
    if value >= grid[-1]:
        return len(grid) - 2, len(grid) - 1, 1.0

    for i in range(len(grid) - 1):
        lo = grid[i]
        hi = grid[i + 1]
        if lo <= value <= hi:
            return i, i + 1, (value - lo) / (hi - lo)
    raise ValueError(f"Value {value} was not bracketed by grid {grid}")


def _force_to_aero_area(
    downforce_n: float,
    drag_n: float,
    speed_mps: float,
    rho: float = 1.225,
) -> tuple[float, float]:
    if speed_mps <= 0.0:
        raise ValueError("Aero reference speed must be positive.")
    q = 0.5 * rho * speed_mps**2
    return downforce_n / q, drag_n / q


def _vector(values: Any) -> tuple[float, float, float]:
    if len(values) != 3:
        raise ValueError(f"Expected a 3-vector, got {values!r}")
    return float(values[0]), float(values[1]), float(values[2])


def _clip(value: float, low: float, high: float) -> float:
    return min(max(value, low), high)
