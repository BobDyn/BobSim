#!/usr/bin/env python3
"""Generate a rubric-oriented vehicle review report for the active BobSim car."""

from __future__ import annotations

import csv
import math
import os
import sys
from pathlib import Path
from collections.abc import Mapping
from typing import Any

import numpy as np

os.environ.setdefault("MPLCONFIGDIR", "/tmp/matplotlib")

from matplotlib.backends.backend_pdf import PdfPages

if __package__ in {None, ""}:
    sys.path.insert(0, str(Path(__file__).resolve().parents[2]))

from _0_Utils.vehicle_io import (  # noqa: E402
    load_yaml,
    parse_tir,
    repo_root,
    require_key,
    require_mapping,
    require_section,
    require_side,
    tire_template_name,
    tire_templates_root,
    vehicle_yaml_path,
)
from _0_Utils.reporting.sections import add_title_page  # noqa: E402
from _0_Utils.reporting.vehicle_review_sections import (  # noqa: E402
    add_review_coverage_page,
    add_review_fundamentals_page,
    add_review_overview_page,
    add_review_performance_page,
    add_review_suspension_page,
    add_review_tires_page,
)
from _2_EnvelopeSim.GGV import ggv_generation  # noqa: E402
from _2_EnvelopeSim.YMD import ymd_generation  # noqa: E402
from _2_EnvelopeSim.vehicle_loader import (  # noqa: E402
    load_active_envelope_inputs,
    load_active_vehicle_yaml,
)


G = 9.80665
DEFAULT_CONFIG_PATH = Path(__file__).with_name("vehicle_review_config.yml")
DEFAULT_RESULTS_DIR = Path(__file__).resolve().parents[1] / "results" / "VehicleReview"
DEFAULT_PDF_NAME = "vehicle_review_report.pdf"
DEFAULT_METRICS_NAME = "vehicle_review_report_metrics.csv"
STEADY_STATE_METRICS_PATH = (
    repo_root() / "_3_StandardSim" / "results" / "steady_state_eval_report_metrics.csv"
)
TRANSIENT_METRICS_PATH = (
    repo_root() / "_3_StandardSim" / "results" / "transient_eval_report_metrics.csv"
)
FOUR_POST_METRICS_PATH = repo_root() / "_3_StandardSim" / "results" / "four_post_eval_report_metrics.csv"


def _configured_ggv_csv_path() -> Path:
    config = ggv_generation.load_ggv_config()
    report = config.get("report") or {}
    return ggv_generation.resolve_ggv_output_path(
        ggv_generation.DEFAULT_GGV_CONFIG,
        report.get("raw_output_path", "../Build/GGV/ggv_first_principles.csv"),
    )


def _configured_ymd_csv_path() -> Path:
    config = ymd_generation.load_ymd_config()
    report = config.get("report") or {}
    return ymd_generation.resolve_ymd_output_path(
        ymd_generation.DEFAULT_YMD_CONFIG,
        report.get("raw_output_path", "../Build/YMD/ymd_first_principles.csv"),
    )


GGV_CSV_PATH = _configured_ggv_csv_path()
YMD_CSV_PATH = _configured_ymd_csv_path()


FloatArray = np.ndarray
MetricRows = list[dict[str, str]]


def _mapping(data: dict[str, Any], key: str) -> dict[str, Any]:
    value = data.get(key, {})
    if value is None:
        return {}
    if not isinstance(value, dict):
        raise TypeError(f"Expected {key!r} to be a mapping.")
    return value


def _as_path(value: Any, *, name: str) -> Path:
    path = Path(str(value))
    if not str(path):
        raise TypeError(f"Expected {name} to be a non-empty path.")
    return path if path.is_absolute() else repo_root() / path


def _as_bool(value: Any, *, name: str) -> bool:
    if not isinstance(value, bool):
        raise TypeError(f"Expected {name} to be boolean.")
    return value


def _as_float(value: Any, *, name: str) -> float:
    try:
        result = float(value)
    except (TypeError, ValueError) as exc:
        raise TypeError(f"Expected {name} to be numeric.") from exc
    if not np.isfinite(result):
        raise TypeError(f"Expected {name} to be finite.")
    return result


def _as_int(value: Any, *, name: str) -> int:
    if isinstance(value, bool):
        raise TypeError(f"Expected {name} to be an integer, not boolean.")
    try:
        return int(value)
    except (TypeError, ValueError) as exc:
        raise TypeError(f"Expected {name} to be an integer.") from exc


def _format_vector(values: FloatArray, *, precision: int = 4) -> str:
    arr = np.asarray(values, dtype=float).reshape(-1)
    fmt = ", ".join(f"{{:.{precision}f}}" for _ in arr)
    return "(" + fmt.format(*arr.tolist()) + ")"


def load_review_config(path: Path = DEFAULT_CONFIG_PATH) -> dict[str, Any]:
    data = load_yaml(path)
    report = _mapping(data, "report")
    output = _mapping(data, "output")
    generation = _mapping(data, "generation")

    report.setdefault("brand", "BobDyn")
    report.setdefault("title", "Vehicle Review and Rubric Coverage")
    report.setdefault(
        "subtitle",
        "Active vehicle.yml cross-checked against StandardSim and EnvelopeSim",
    )
    report.setdefault(
        "notes",
        [
            "Active vehicle definition comes from the repo-root vehicle.yml.",
            "Envelope inputs are loaded from the same active YAML used by the model generators.",
            "GGV and YMD are regenerated from the active config before the review is assembled.",
        ],
    )

    output.setdefault("results_dir", str(DEFAULT_RESULTS_DIR))
    output.setdefault("pdf_filename", DEFAULT_PDF_NAME)
    output.setdefault("metrics_csv_filename", DEFAULT_METRICS_NAME)

    generation.setdefault("regenerate_ggv", True)
    generation.setdefault("regenerate_ymd", True)

    data["report"] = report
    data["output"] = output
    data["generation"] = generation
    return data


def _load_metric_rows(path: Path) -> dict[str, dict[str, str]]:
    if not path.exists():
        raise FileNotFoundError(path)

    with path.open("r", newline="", encoding="utf-8") as handle:
        reader = csv.DictReader(handle)
        rows: dict[str, dict[str, str]] = {}
        for row in reader:
            key = str(row.get("metric", "")).strip()
            if key:
                rows[key] = row
    return rows


def _metric_float(rows: Mapping[str, Any], key: str, default: float = float("nan")) -> float:
    row = rows.get(key)
    if not isinstance(row, dict):
        return default
    raw = str(row.get("value", "")).strip()
    try:
        value = float(raw)
    except ValueError:
        return default
    return value if np.isfinite(value) else default


def _metric_text(rows: Mapping[str, Any], key: str, default: str = "") -> str:
    row = rows.get(key)
    if not isinstance(row, dict):
        return default
    return str(row.get("value", default)).strip() or default


def _load_tire_metadata(tir_path: Path) -> dict[str, Any]:
    numeric = parse_tir(tir_path)
    lines = tir_path.read_text(encoding="utf-8").splitlines()

    def _tir_number(key: str, default: float = float("nan")) -> float:
        value = numeric.get(key, default)
        if isinstance(value, str):
            try:
                return float(value)
            except ValueError:
                return default
        return float(value)

    comments: list[str] = []
    size_comment = "not encoded"
    section_width_m = float("nan")
    nominal_pressure_pa = float("nan")
    rim_radius_m = float("nan")
    rim_width_m = float("nan")
    unloaded_radius_m = float("nan")
    test_speed_mps = float("nan")
    use_mode = int(_tir_number("USE_MODE", 0.0))

    for line in lines:
        stripped = line.strip()
        if not stripped.startswith("! : COMMENT :"):
            continue

        comment = stripped.split("! : COMMENT :", 1)[1].strip()
        comments.append(comment)

        if comment.startswith("Tire "):
            size_comment = comment
        elif comment.startswith("Nom. section width"):
            section_width_m = float(comment.rsplit(" ", 1)[1])
        elif comment.startswith("Infl. pressure"):
            nominal_pressure_pa = float(comment.rsplit(" ", 1)[1])
        elif comment.startswith("Rim radius"):
            rim_radius_m = float(comment.rsplit(" ", 1)[1])
        elif comment.startswith("Test speed"):
            test_speed_mps = float(comment.rsplit(" ", 1)[1])

    if not np.isfinite(section_width_m):
        section_width_m = _tir_number("WIDTH")
    if not np.isfinite(nominal_pressure_pa):
        nominal_pressure_pa = _tir_number("IP_NOM")
    if not np.isfinite(rim_radius_m):
        rim_radius_m = _tir_number("RIM_RADIUS")
    if not np.isfinite(rim_width_m):
        rim_width_m = _tir_number("RIM_WIDTH")
    if not np.isfinite(unloaded_radius_m):
        unloaded_radius_m = _tir_number("UNLOADED_RADIUS")
    if not np.isfinite(test_speed_mps):
        test_speed_mps = _tir_number("LONGVL")

    return {
        "template": tir_path.stem,
        "path": tir_path,
        "size_comment": size_comment,
        "section_width_m": section_width_m,
        "nominal_pressure_pa": nominal_pressure_pa,
        "nominal_pressure_psi": nominal_pressure_pa / 6894.757 if np.isfinite(nominal_pressure_pa) else float("nan"),
        "ip_nom_pa": nominal_pressure_pa,
        "ip_nom_psi": nominal_pressure_pa / 6894.757 if np.isfinite(nominal_pressure_pa) else float("nan"),
        "rim_radius_m": rim_radius_m,
        "rim_width_m": rim_width_m,
        "unloaded_radius_m": unloaded_radius_m,
        "test_speed_mps": test_speed_mps,
        "use_mode": use_mode,
        "comments": comments,
        "fznom_n": _tir_number("FNOMIN"),
        "fzmin_valid_n": _tir_number("FZMIN"),
        "fzmax_valid_n": _tir_number("FZMAX"),
        "fz_min_valid_n": _tir_number("FZMIN"),
        "fz_max_valid_n": _tir_number("FZMAX"),
        "pdx1": _tir_number("PDX1"),
        "pdx2": _tir_number("PDX2"),
        "pdx3": _tir_number("PDX3"),
        "pdy1": _tir_number("PDY1"),
        "pdy2": _tir_number("PDY2"),
        "pdy3": _tir_number("PDY3"),
        "pkx1": _tir_number("PKX1"),
        "pkx2": _tir_number("PKX2"),
        "pkx3": _tir_number("PKX3"),
        "pky1": _tir_number("PKY1"),
        "pky2": _tir_number("PKY2"),
        "pky3": _tir_number("PKY3"),
        "lsgkp": _tir_number("LSGKP"),
        "lsgal": _tir_number("LSGAL"),
        "manufacturer": "not encoded in vehicle.yml or .tir",
        "compound": "not encoded in vehicle.yml or .tir",
        "wheel_material": "not encoded in vehicle.yml or .tir",
    }


def _mass_record(section: dict[str, Any], *, path: str) -> tuple[float, FloatArray, FloatArray]:
    mass = float(require_key(section, path, "mass_kg"))
    cg = np.asarray(require_key(section, path, "cg_m"), dtype=float).reshape(3)
    inertia = np.asarray(require_key(section, path, "inertia_kg_m2"), dtype=float)
    return mass, cg, inertia


def _combine_mass_properties(
    points: list[tuple[float, FloatArray, FloatArray]],
) -> tuple[float, FloatArray, FloatArray]:
    total_mass = float(sum(mass for mass, _, _ in points))
    if total_mass <= 0.0:
        raise ValueError("Combined mass must be positive.")

    cg = np.zeros(3, dtype=float)
    for mass, point_cg, _inertia in points:
        cg += mass * point_cg
    cg /= total_mass

    inertia = np.zeros((3, 3), dtype=float)
    eye = np.eye(3, dtype=float)
    for mass, point_cg, point_inertia in points:
        delta = point_cg - cg
        inertia += point_inertia + mass * ((delta @ delta) * eye - np.outer(delta, delta))

    return total_mass, cg, inertia


def _table_array(table_like: Any) -> FloatArray:
    arr = np.asarray(table_like, dtype=float)
    if arr.ndim != 2 or arr.shape[1] < 2:
        raise ValueError("Expected a 2D table with at least two columns.")
    return arr[:, :2]


def _interp_with_extrap(x: float, xp: FloatArray, fp: FloatArray) -> float:
    mask = np.isfinite(xp) & np.isfinite(fp)
    xp = np.asarray(xp[mask], dtype=float)
    fp = np.asarray(fp[mask], dtype=float)
    if xp.size < 2:
        return float("nan")

    order = np.argsort(xp)
    xp = xp[order]
    fp = fp[order]

    unique_xp, unique_idx = np.unique(xp, return_index=True)
    xp = unique_xp
    fp = fp[unique_idx]
    if xp.size < 2:
        return float("nan")

    if x <= xp[0]:
        slope = (fp[1] - fp[0]) / (xp[1] - xp[0] + 1e-12)
        return float(fp[0] + slope * (x - xp[0]))
    if x >= xp[-1]:
        slope = (fp[-1] - fp[-2]) / (xp[-1] - xp[-2] + 1e-12)
        return float(fp[-1] + slope * (x - xp[-1]))

    return float(np.interp(x, xp, fp))


def _table_rate_at_value(table_like: Any, x_value: float) -> float:
    table = _table_array(table_like)
    xs = table[:, 0]
    ys = table[:, 1]
    mask = np.isfinite(xs) & np.isfinite(ys)
    xs = np.asarray(xs[mask], dtype=float)
    ys = np.asarray(ys[mask], dtype=float)
    if xs.size < 2:
        return float("nan")

    order = np.argsort(xs)
    xs = xs[order]
    ys = ys[order]

    unique_xs, unique_idx = np.unique(xs, return_index=True)
    xs = unique_xs
    ys = ys[unique_idx]
    if xs.size < 2:
        return float("nan")

    if x_value <= xs[0]:
        idx = 0
    elif x_value >= xs[-1]:
        idx = xs.size - 2
    else:
        idx = int(np.searchsorted(xs, x_value) - 1)

    dx = xs[idx + 1] - xs[idx]
    if abs(dx) < 1e-12:
        return float("nan")
    return float((ys[idx + 1] - ys[idx]) / dx)


def _force_to_deflection(table_like: Any, force_n: float) -> float:
    table = _table_array(table_like)
    return _interp_with_extrap(force_n, table[:, 1], table[:, 0])


def _installed_length(axle_name: str, side: dict[str, Any]) -> float:
    actuation = require_section(side, axle_name, "actuation")
    shock = require_section(actuation, f"{axle_name}.actuation", "shock")
    shock_mount = np.asarray(require_key(shock, f"{axle_name}.actuation.shock", "mount_m"), dtype=float)

    bellcrank = actuation.get("bellcrank")
    if isinstance(bellcrank, dict):
        pickups = require_key(bellcrank, f"{axle_name}.actuation.bellcrank", "pickups_m")
        shock_pickup = np.asarray(pickups["shock"], dtype=float)
        return float(np.linalg.norm(shock_mount - shock_pickup))

    rod_mount = np.asarray(require_key(actuation, f"{axle_name}.actuation", "rod_mount_m"), dtype=float)
    return float(np.linalg.norm(shock_mount - rod_mount))


def _quarter_car_modes(
    sprung_mass_kg: float,
    unsprung_mass_kg: float,
    wheel_rate_n_per_m: float,
    wheel_damping_n_s_per_m: float,
    tire_rate_n_per_m: float,
    tire_damping_n_s_per_m: float,
) -> tuple[float, float, float, float]:
    if sprung_mass_kg <= 0.0 or unsprung_mass_kg <= 0.0 or wheel_rate_n_per_m <= 0.0 or tire_rate_n_per_m <= 0.0:
        return float("nan"), float("nan"), float("nan"), float("nan")

    m = np.array([[sprung_mass_kg, 0.0], [0.0, unsprung_mass_kg]], dtype=float)
    c = np.array(
        [
            [wheel_damping_n_s_per_m, -wheel_damping_n_s_per_m],
            [
                -wheel_damping_n_s_per_m,
                wheel_damping_n_s_per_m + tire_damping_n_s_per_m,
            ],
        ],
        dtype=float,
    )
    k = np.array(
        [
            [wheel_rate_n_per_m, -wheel_rate_n_per_m],
            [-wheel_rate_n_per_m, wheel_rate_n_per_m + tire_rate_n_per_m],
        ],
        dtype=float,
    )

    zero = np.zeros((2, 2), dtype=float)
    eye = np.eye(2, dtype=float)
    a_top = np.concatenate([zero, eye], axis=1)
    a_bottom = np.concatenate([-np.linalg.solve(m, k), -np.linalg.solve(m, c)], axis=1)
    a = np.concatenate([a_top, a_bottom], axis=0)

    eigvals = np.linalg.eigvals(a)
    modes = [ev for ev in eigvals if np.isfinite(ev) and np.imag(ev) > 1e-9]
    modes.sort(key=lambda ev: abs(np.imag(ev)))
    if len(modes) < 2:
        return float("nan"), float("nan"), float("nan"), float("nan")

    sprung_mode = modes[0]
    unsprung_mode = modes[-1]

    def freq_and_zeta(ev: complex) -> tuple[float, float]:
        wn = abs(ev)
        if wn <= 0.0:
            return float("nan"), float("nan")
        freq = abs(np.imag(ev)) / (2.0 * math.pi)
        zeta = max(0.0, min(1.5, -float(np.real(ev)) / wn))
        return float(freq), float(zeta)

    sprung_freq_hz, sprung_zeta = freq_and_zeta(sprung_mode)
    unsprung_freq_hz, unsprung_zeta = freq_and_zeta(unsprung_mode)
    return sprung_freq_hz, unsprung_freq_hz, sprung_zeta, unsprung_zeta


def _corner_fraction_from_cg(
    sprung_cg: FloatArray,
    front_wc: FloatArray,
    rear_wc: FloatArray,
) -> tuple[float, float, float, float]:
    front_x = float(front_wc[0])
    rear_x = float(rear_wc[0])
    left_y = 0.5 * (float(front_wc[1]) + float(rear_wc[1]))
    right_y = -left_y

    wheelbase = abs(front_x - rear_x)
    if wheelbase <= 0.0:
        raise ValueError("Wheelbase must be positive.")

    front_fraction = (float(sprung_cg[0]) - rear_x) / (front_x - rear_x)
    rear_fraction = 1.0 - front_fraction
    left_fraction = (float(sprung_cg[1]) - right_y) / (left_y - right_y)
    right_fraction = 1.0 - left_fraction
    return front_fraction, rear_fraction, left_fraction, right_fraction


def _side_table(axle_name: str, side: dict[str, Any], key: str) -> FloatArray:
    actuation = require_section(side, axle_name, "actuation")
    shock = require_section(actuation, f"{axle_name}.actuation", "shock")
    table = shock.get(key)
    if isinstance(table, dict):
        table = table.get("table")
    return _table_array(table)


def _corner_modal_summary(
    vehicle_yaml: dict[str, Any],
    summary: dict[str, Any],
) -> dict[str, Any]:
    front_side = require_side(vehicle_yaml, "front")
    rear_side = require_side(vehicle_yaml, "rear")
    front_suspension = require_section(front_side, "front", "suspension")
    rear_suspension = require_section(rear_side, "rear", "suspension")
    front_steering = require_section(front_side, "front", "steering")
    front_wc = np.asarray(
        require_key(front_suspension, "front.suspension", "wheel_center_m"),
        dtype=float,
    )
    rear_wc = np.asarray(
        require_key(rear_suspension, "rear.suspension", "wheel_center_m"),
        dtype=float,
    )

    sprung_points = []
    sprung_section = require_mapping(vehicle_yaml, "sprung_mass", vehicle_yaml_path())
    sprung_points.append(_mass_record(sprung_section, path="sprung_mass"))

    driver = vehicle_yaml.get("driver_mass")
    if isinstance(driver, dict):
        sprung_points.append(_mass_record(driver, path="driver_mass"))

    sprung_mass, sprung_cg, sprung_inertia = _combine_mass_properties(sprung_points)
    front_fraction, rear_fraction, left_fraction, right_fraction = _corner_fraction_from_cg(
        sprung_cg,
        front_wc,
        rear_wc,
    )

    axle_data: list[tuple[str, dict[str, Any], float, float]] = [
        (
            "front",
            front_side,
            front_fraction,
            _metric_float(summary, "avg_motion_ratio_front"),
        ),
        (
            "rear",
            rear_side,
            rear_fraction,
            _metric_float(summary, "avg_motion_ratio_rear"),
        ),
    ]

    corners: dict[str, dict[str, float]] = {}

    for axle_name, side, axle_fraction, motion_ratio in axle_data:
        axle_unsprung_mass = 0.0
        masses = require_section(side, axle_name, "masses")
        tire_section = require_section(side, axle_name, "tire")
        for mass_name in ("unsprung", "upper_control_arm", "lower_control_arm", "tie_rod"):
            mass_section = require_section(masses, f"{axle_name}.masses", mass_name)
            axle_unsprung_mass += float(require_key(mass_section, f"{axle_name}.masses.{mass_name}", "mass_kg"))

        spring_table = _side_table(axle_name, side, "spring_table")
        damper_table = _side_table(axle_name, side, "damper_table")
        tire_rate = float(require_key(tire_section, f"{axle_name}.tire", "vertical_stiffness_n_per_m"))
        tire_damping = float(require_key(tire_section, f"{axle_name}.tire", "vertical_damping_n_s_per_m"))
        installed_length = _installed_length(axle_name, side)

        for corner_name, lateral_fraction in (("left", left_fraction), ("right", right_fraction)):
            sprung_corner_mass = sprung_mass * axle_fraction * lateral_fraction
            sprung_corner_load = sprung_corner_mass * G
            spring_force = sprung_corner_load * motion_ratio
            spring_compression_m = _force_to_deflection(spring_table, spring_force)
            spring_rate = _table_rate_at_value(spring_table, spring_compression_m)
            wheel_rate = (
                spring_rate / (motion_ratio**2)
                if np.isfinite(motion_ratio) and abs(motion_ratio) > 1e-12
                else float("nan")
            )
            shock_damper_rate = _table_rate_at_value(damper_table, 0.0)
            wheel_damping = (
                shock_damper_rate / (motion_ratio**2)
                if np.isfinite(motion_ratio) and abs(motion_ratio) > 1e-12
                else float("nan")
            )
            free_length = installed_length + spring_compression_m
            sprung_freq_hz, unsprung_freq_hz, sprung_zeta, unsprung_zeta = _quarter_car_modes(
                sprung_corner_mass,
                axle_unsprung_mass,
                wheel_rate,
                wheel_damping,
                tire_rate,
                tire_damping,
            )

            key = f"{axle_name}_{corner_name}"
            corners[key] = {
                "sprung_mass_kg": float(sprung_corner_mass),
                "unsprung_mass_kg": float(axle_unsprung_mass),
                "spring_rate_n_per_m": float(spring_rate),
                "wheel_rate_n_per_m": float(wheel_rate),
                "damper_rate_n_s_per_m": float(wheel_damping),
                "spring_compression_m": float(spring_compression_m),
                "spring_free_length_m": float(free_length),
                "sprung_frequency_hz": float(sprung_freq_hz),
                "unsprung_frequency_hz": float(unsprung_freq_hz),
                "sprung_zeta": float(sprung_zeta),
                "unsprung_zeta": float(unsprung_zeta),
            }

    def _avg(name: str, axle: str) -> float:
        vals = [corners[f"{axle}_left"][name], corners[f"{axle}_right"][name]]
        arr = np.asarray(vals, dtype=float)
        return float(np.nanmean(arr))

    return {
        "combined_sprung_mass_kg": float(sprung_mass),
        "combined_sprung_cg": _format_vector(sprung_cg, precision=3),
        "combined_sprung_inertia_diag": _format_vector(np.diag(sprung_inertia), precision=3),
        "front_motion_ratio": _metric_float(summary, "avg_motion_ratio_front"),
        "rear_motion_ratio": _metric_float(summary, "avg_motion_ratio_rear"),
        "front_stabar_motion_ratio": _metric_float(summary, "avg_stabar_motion_ratio_front"),
        "rear_stabar_motion_ratio": _metric_float(summary, "avg_stabar_motion_ratio_rear"),
        "front_spring_rate_n_per_m": _avg("spring_rate_n_per_m", "front"),
        "rear_spring_rate_n_per_m": _avg("spring_rate_n_per_m", "rear"),
        "front_wheel_rate_n_per_m": _avg("wheel_rate_n_per_m", "front"),
        "rear_wheel_rate_n_per_m": _avg("wheel_rate_n_per_m", "rear"),
        "front_damper_rate_n_s_per_m": _avg("damper_rate_n_s_per_m", "front"),
        "rear_damper_rate_n_s_per_m": _avg("damper_rate_n_s_per_m", "rear"),
        "front_sprung_freq_hz": _avg("sprung_frequency_hz", "front"),
        "rear_sprung_freq_hz": _avg("sprung_frequency_hz", "rear"),
        "front_unsprung_freq_hz": _avg("unsprung_frequency_hz", "front"),
        "rear_unsprung_freq_hz": _avg("unsprung_frequency_hz", "rear"),
        "front_sprung_zeta": _avg("sprung_zeta", "front"),
        "rear_sprung_zeta": _avg("sprung_zeta", "rear"),
        "front_unsprung_zeta": _avg("unsprung_zeta", "front"),
        "rear_unsprung_zeta": _avg("unsprung_zeta", "rear"),
        "front_spring_compression_m": _avg("spring_compression_m", "front"),
        "rear_spring_compression_m": _avg("spring_compression_m", "rear"),
        "front_spring_free_length_m": _avg("spring_free_length_m", "front"),
        "rear_spring_free_length_m": _avg("spring_free_length_m", "rear"),
        "rack_travel_per_rev_m": float(require_key(front_steering, "front.steering", "rack_travel_per_rev_m")),
        "corners": corners,
    }


def _summarize_ggv(ggv_path: Path, speeds: tuple[float, ...]) -> dict[str, Any]:
    with ggv_path.open("r", newline="", encoding="utf-8") as handle:
        rows = list(csv.DictReader(handle))

    grouped: dict[float, list[dict[str, str]]] = {}
    for row in rows:
        speed = float(row["speed_mps"])
        grouped.setdefault(speed, []).append(row)

    by_speed: list[dict[str, float]] = []
    max_abs_ay = float("nan")
    max_accel = float("nan")
    max_brake = float("nan")

    for speed in sorted(grouped):
        rows_at_speed = grouped[speed]
        ay = np.asarray([float(row["ay_mps2"]) for row in rows_at_speed], dtype=float)
        ax_accel = np.asarray([float(row["ax_accel_mps2"]) for row in rows_at_speed], dtype=float)
        ax_brake = np.asarray([float(row["ax_brake_mps2"]) for row in rows_at_speed], dtype=float)

        finite_accel = np.isfinite(ax_accel)
        finite_brake = np.isfinite(ax_brake)
        finite_any = finite_accel | finite_brake

        max_abs_ay_speed = float(np.nanmax(np.abs(ay[finite_any]))) if np.any(finite_any) else float("nan")
        max_accel_speed = float(np.nanmax(ax_accel[finite_accel])) if np.any(finite_accel) else float("nan")
        max_brake_speed = float(abs(np.nanmin(ax_brake[finite_brake]))) if np.any(finite_brake) else float("nan")

        by_speed.append(
            {
                "speed_mps": float(speed),
                "max_abs_ay_g": max_abs_ay_speed / G,
                "max_accel_g": max_accel_speed / G,
                "max_brake_g": max_brake_speed / G,
            }
        )

        if np.isfinite(max_abs_ay_speed):
            max_abs_ay = max(max_abs_ay, max_abs_ay_speed / G)
        if np.isfinite(max_accel_speed):
            max_accel = max(max_accel, max_accel_speed / G)
        if np.isfinite(max_brake_speed):
            max_brake = max(max_brake, max_brake_speed / G)

    finite_rows = [
        row for row in rows if np.isfinite(float(row["ax_accel_mps2"])) or np.isfinite(float(row["ax_brake_mps2"]))
    ]

    peak_speed = float("nan")
    peak_ay = float("nan")
    if by_speed:
        peak = max(by_speed, key=lambda item: item["max_abs_ay_g"] if np.isfinite(item["max_abs_ay_g"]) else -1.0)
        peak_speed = peak["speed_mps"]
        peak_ay = peak["max_abs_ay_g"]

    return {
        "available": True,
        "csv_path": ggv_path,
        "by_speed": by_speed,
        "num_rows": len(rows),
        "num_finite_rows": len(finite_rows),
        "max_abs_ay_g": float(max_abs_ay),
        "max_accel_g": float(max_accel),
        "max_brake_g": float(max_brake),
        "peak_speed_mps": float(peak_speed),
        "peak_abs_ay_g": float(peak_ay),
        "speed_min_mps": float(min(speeds)) if speeds else float("nan"),
        "speed_max_mps": float(max(speeds)) if speeds else float("nan"),
        "summary_sentence": (
            f"{len(speeds)} speeds, peak |ay| {peak_ay:.3f} g at {peak_speed:.1f} m/s"
            if speeds
            else "no GGV speeds available"
        ),
    }


def _ymd_speed_bounds(config: dict[str, Any]) -> tuple[float, float]:
    speed_sweep = config.get("speed_sweep") or {}
    if isinstance(speed_sweep, dict) and speed_sweep.get("enabled", False):
        raw_speeds = speed_sweep.get("speeds_mps", [])
        if isinstance(raw_speeds, list) and raw_speeds:
            speeds = [float(speed) for speed in raw_speeds]
            return min(speeds), max(speeds)

    generation = config.get("generation") or {}
    speed = float(generation.get("speed_mps", ymd_generation.YMDConfig.speed))
    return speed, speed


def _summarize_ymd(ymd_path: Path, config: dict[str, Any]) -> dict[str, Any]:
    speed_min_mps, speed_max_mps = _ymd_speed_bounds(config)
    if not ymd_path.exists():
        return {
            "available": False,
            "csv_path": ymd_path,
            "converged_fraction": float("nan"),
            "max_abs_ay_g": float("nan"),
            "max_abs_mz_nm": float("nan"),
            "speed_min_mps": speed_min_mps,
            "speed_max_mps": speed_max_mps,
            "summary_sentence": "YMD not yet generated.",
        }

    with ymd_path.open("r", newline="", encoding="utf-8") as handle:
        rows = list(csv.DictReader(handle))

    if not rows:
        return {
            "available": False,
            "csv_path": ymd_path,
            "converged_fraction": float("nan"),
            "max_abs_ay_g": float("nan"),
            "max_abs_mz_nm": float("nan"),
            "speed_min_mps": speed_min_mps,
            "speed_max_mps": speed_max_mps,
            "summary_sentence": "YMD CSV was empty.",
        }

    ay_g = np.asarray([float(row["ay_g"]) for row in rows], dtype=float)
    mz_nm = np.asarray([float(row["mz_nm"]) for row in rows], dtype=float)
    converged = np.asarray([float(row["converged"]) for row in rows], dtype=float)
    speed_mps = np.asarray([float(row["speed_mps"]) for row in rows], dtype=float)

    return {
        "available": True,
        "csv_path": ymd_path,
        "converged_fraction": float(np.mean(converged)),
        "max_abs_ay_g": float(np.nanmax(np.abs(ay_g))),
        "max_abs_mz_nm": float(np.nanmax(np.abs(mz_nm))),
        "speed_min_mps": float(np.nanmin(speed_mps)),
        "speed_max_mps": float(np.nanmax(speed_mps)),
        "speed_center_mps": float(np.nanmedian(speed_mps)),
        "summary_sentence": (
            f"{100.0 * float(np.mean(converged)):.1f}% converged at {float(np.nanmedian(speed_mps)):.1f} m/s"
        ),
    }


def _build_review_metrics(review: dict[str, Any]) -> MetricRows:
    vehicle = review["vehicle"]
    powertrain = review["powertrain"]
    tire = review["tire"]
    suspension = review["suspension"]
    performance = review["performance"]
    ggv = review["ggv"]
    ymd = review["ymd"]
    coverage_rows = review["coverage_rows"]

    rows: MetricRows = []

    def add(section: str, metric: str, value: Any, units: str, description: str) -> None:
        rows.append(
            {
                "section": section,
                "metric": metric,
                "value": str(value),
                "units": units,
                "description": description,
            }
        )

    add("Overall", "vehicle_name", vehicle["vehicle_name"], "", "Active vehicle name")
    add("Overall", "source_yaml", vehicle["source_yaml"], "", "Active vehicle source YAML")
    add("Overall", "summary_sentence", review["sources"]["summary_sentence"], "", "Concise source summary")
    add(
        "Overall",
        "agreement_summary",
        review["sources"]["agreement_summary"],
        "",
        "Agreement between loader and vehicle.yml",
    )
    add("Overall", "lltd_source", review["sources"]["lltd_source"], "", "Source of LLTD used by the envelope model")
    add("Overall", "aero_source", review["sources"]["aero_source"], "", "Source of nominal aero scalars")

    add("Fundamentals", "mass_kg", vehicle["mass_kg"], "kg", "Total vehicle mass from the active YAML")
    add("Fundamentals", "wheelbase_m", vehicle["wheelbase_m"], "m", "Wheelbase")
    add("Fundamentals", "track_front_m", vehicle["track_front_m"], "m", "Front track")
    add("Fundamentals", "track_rear_m", vehicle["track_rear_m"], "m", "Rear track")
    add("Fundamentals", "cg_height_m", vehicle["cg_height_m"], "m", "Center of gravity height")
    add("Fundamentals", "front_static_frac", vehicle["front_static_frac"], "-", "Static front weight fraction")
    add("Fundamentals", "lltd_front_frac", vehicle["lltd_front_frac"], "-", "Front lateral load transfer distribution")
    add("Fundamentals", "cl_a", vehicle["cl_a"], "m^2", "Downforce area coefficient")
    add("Fundamentals", "cd_a", vehicle["cd_a"], "m^2", "Drag area coefficient")
    add(
        "Fundamentals",
        "body_torsional_stiffness_n_m_per_rad",
        vehicle["body_torsional_stiffness_n_m_per_rad"],
        "N*m/rad",
        "Chassis torsional stiffness",
    )
    add("Fundamentals", "drive_distribution_front", powertrain["drive_distribution_front"], "-", "Front drive split")
    add("Fundamentals", "brake_distribution_front", powertrain["brake_distribution_front"], "-", "Front brake split")
    add("Fundamentals", "max_drive_power_w", powertrain["max_drive_power_w"], "W", "Drive power cap")
    add("Fundamentals", "max_drive_force_n", powertrain["max_drive_force_n"], "N", "Drive force cap")
    add("Fundamentals", "max_brake_force_n", powertrain["max_brake_force_n"], "N", "Brake force cap")

    add("Tires", "template", tire["template"], "", "Active tire template")
    add("Tires", "size_comment", tire["size_comment"], "", "Template comment")
    add("Tires", "nominal_pressure_pa", tire["nominal_pressure_pa"], "Pa", "Nominal inflation pressure")
    add("Tires", "nominal_pressure_psi", tire["nominal_pressure_psi"], "psi", "Nominal inflation pressure")
    add("Tires", "test_speed_mps", tire["test_speed_mps"], "m/s", "Tire test speed from the .tir")
    add("Tires", "fznom_n", tire["fznom_n"], "N", "Nominal tire load")
    add("Tires", "fzmin_valid_n", tire["fzmin_valid_n"], "N", "Minimum valid tire load")
    add("Tires", "fzmax_valid_n", tire["fzmax_valid_n"], "N", "Maximum valid tire load")
    add("Tires", "mu_x_ref", tire["mu_x_ref"], "-", "Longitudinal peak friction at FNOMIN")
    add("Tires", "mu_y_ref", tire["mu_y_ref"], "-", "Lateral peak friction at FNOMIN")
    add("Tires", "mu_x_min", tire["mu_x_min"], "-", "Longitudinal peak friction at minimum valid load")
    add("Tires", "mu_x_max", tire["mu_x_max"], "-", "Longitudinal peak friction at maximum valid load")
    add("Tires", "mu_y_min", tire["mu_y_min"], "-", "Lateral peak friction at minimum valid load")
    add("Tires", "mu_y_max", tire["mu_y_max"], "-", "Lateral peak friction at maximum valid load")
    add("Tires", "pdx1", tire["pdx1"], "-", "Longitudinal peak coefficient")
    add("Tires", "pdx2", tire["pdx2"], "-", "Longitudinal load sensitivity")
    add("Tires", "pdx3", tire["pdx3"], "-", "Longitudinal camber sensitivity")
    add("Tires", "pdy1", tire["pdy1"], "-", "Lateral peak coefficient")
    add("Tires", "pdy2", tire["pdy2"], "-", "Lateral load sensitivity")
    add("Tires", "pdy3", tire["pdy3"], "-", "Lateral camber sensitivity")
    add("Tires", "pkx1", tire["pkx1"], "-", "Longitudinal stiffness coefficient")
    add("Tires", "pkx2", tire["pkx2"], "-", "Longitudinal stiffness load sensitivity")
    add("Tires", "pkx3", tire["pkx3"], "-", "Longitudinal stiffness exponent")
    add("Tires", "pky1", tire["pky1"], "-", "Lateral stiffness coefficient")
    add("Tires", "pky2", tire["pky2"], "-", "Lateral stiffness load sensitivity")
    add("Tires", "pky3", tire["pky3"], "-", "Lateral stiffness exponent")
    add("Tires", "lsgkp", tire["lsgkp"], "-", "Longitudinal relaxation length scale")
    add("Tires", "lsgal", tire["lsgal"], "-", "Lateral relaxation length scale")
    add(
        "Tires",
        "relaxation_summary",
        tire["relaxation_summary"],
        "",
        "Template relaxation / temperature note",
    )
    add(
        "Tires",
        "wheel_radius_m",
        vehicle["wheel_radius_m"],
        "m",
        "Wheel radius from vehicle.yml",
    )
    add("Tires", "wheel_inertia_kg_m2", vehicle["wheel_inertia_kg_m2"], "kg*m^2", "Wheel inertia")
    add("Tires", "rim_radius_m", tire["rim_radius_m"], "m", "Rim radius from the tire template")
    add("Tires", "rim_width_m", tire["rim_width_m"], "m", "Rim width from the tire template")
    add("Tires", "section_width_m", tire["section_width_m"], "m", "Nominal section width")
    add("Tires", "toe_deg", vehicle["toe_deg"], "deg", "Static toe angle")
    add("Tires", "camber_deg", vehicle["camber_deg"], "deg", "Static camber angle")
    add(
        "Tires",
        "vertical_stiffness_n_per_m",
        vehicle["tire_vertical_stiffness_n_per_m"],
        "N/m",
        "Tire vertical stiffness",
    )
    add(
        "Tires",
        "vertical_damping_n_s_per_m",
        vehicle["tire_vertical_damping_n_s_per_m"],
        "N*s/m",
        "Tire vertical damping",
    )

    add("Suspension", "combined_sprung_mass_kg", suspension["combined_sprung_mass_kg"], "kg", "Sprung + driver mass")
    add("Suspension", "combined_sprung_cg", suspension["combined_sprung_cg"], "m", "Sprung + driver CG")
    add(
        "Suspension",
        "combined_sprung_inertia_diag",
        suspension["combined_sprung_inertia_diag"],
        "kg*m^2",
        "Sprung + driver inertia diagonal",
    )
    add("Suspension", "front_motion_ratio", suspension["front_motion_ratio"], "-", "Front motion ratio")
    add("Suspension", "rear_motion_ratio", suspension["rear_motion_ratio"], "-", "Rear motion ratio")
    add(
        "Suspension",
        "front_stabar_motion_ratio",
        suspension["front_stabar_motion_ratio"],
        "-",
        "Front anti-roll bar motion ratio",
    )
    add(
        "Suspension",
        "rear_stabar_motion_ratio",
        suspension["rear_stabar_motion_ratio"],
        "-",
        "Rear anti-roll bar motion ratio",
    )
    add(
        "Suspension",
        "front_spring_rate_n_per_m",
        suspension["front_spring_rate_n_per_m"],
        "N/m",
        "Linearized front spring rate",
    )
    add(
        "Suspension",
        "rear_spring_rate_n_per_m",
        suspension["rear_spring_rate_n_per_m"],
        "N/m",
        "Linearized rear spring rate",
    )
    add(
        "Suspension",
        "front_wheel_rate_n_per_m",
        suspension["front_wheel_rate_n_per_m"],
        "N/m",
        "Front wheel rate",
    )
    add(
        "Suspension",
        "rear_wheel_rate_n_per_m",
        suspension["rear_wheel_rate_n_per_m"],
        "N/m",
        "Rear wheel rate",
    )
    add(
        "Suspension",
        "front_damper_rate_n_s_per_m",
        suspension["front_damper_rate_n_s_per_m"],
        "N*s/m",
        "Front effective damping",
    )
    add(
        "Suspension",
        "rear_damper_rate_n_s_per_m",
        suspension["rear_damper_rate_n_s_per_m"],
        "N*s/m",
        "Rear effective damping",
    )
    add("Suspension", "front_sprung_freq_hz", suspension["front_sprung_freq_hz"], "Hz", "Front sprung mode frequency")
    add("Suspension", "rear_sprung_freq_hz", suspension["rear_sprung_freq_hz"], "Hz", "Rear sprung mode frequency")
    add(
        "Suspension",
        "front_unsprung_freq_hz",
        suspension["front_unsprung_freq_hz"],
        "Hz",
        "Front unsprung mode frequency",
    )
    add(
        "Suspension",
        "rear_unsprung_freq_hz",
        suspension["rear_unsprung_freq_hz"],
        "Hz",
        "Rear unsprung mode frequency",
    )
    add("Suspension", "front_sprung_zeta", suspension["front_sprung_zeta"], "-", "Front sprung damping ratio")
    add("Suspension", "rear_sprung_zeta", suspension["rear_sprung_zeta"], "-", "Rear sprung damping ratio")
    add(
        "Suspension",
        "front_unsprung_zeta",
        suspension["front_unsprung_zeta"],
        "-",
        "Front unsprung damping ratio",
    )
    add(
        "Suspension",
        "rear_unsprung_zeta",
        suspension["rear_unsprung_zeta"],
        "-",
        "Rear unsprung damping ratio",
    )
    add(
        "Suspension",
        "front_spring_compression_m",
        suspension["front_spring_compression_m"],
        "m",
        "Front static spring compression",
    )
    add(
        "Suspension",
        "rear_spring_compression_m",
        suspension["rear_spring_compression_m"],
        "m",
        "Rear static spring compression",
    )
    add(
        "Suspension",
        "front_spring_free_length_m",
        suspension["front_spring_free_length_m"],
        "m",
        "Front spring free length",
    )
    add(
        "Suspension",
        "rear_spring_free_length_m",
        suspension["rear_spring_free_length_m"],
        "m",
        "Rear spring free length",
    )
    add(
        "Suspension",
        "rack_travel_per_rev_m",
        suspension["rack_travel_per_rev_m"],
        "m/rev",
        "Rack travel per revolution",
    )
    add(
        "Suspension",
        "camber_gain_heave_rad_per_m",
        suspension["camber_gain_heave_rad_per_m"],
        "rad/m",
        "Heave camber gain",
    )
    add(
        "Suspension",
        "toe_gain_heave_rad_per_m",
        suspension["toe_gain_heave_rad_per_m"],
        "rad/m",
        "Heave toe gain",
    )
    add(
        "Suspension",
        "caster_gain_heave_rad_per_m",
        suspension["caster_gain_heave_rad_per_m"],
        "rad/m",
        "Heave caster gain",
    )
    add(
        "Suspension",
        "kpi_gain_heave_rad_per_m",
        suspension["kpi_gain_heave_rad_per_m"],
        "rad/m",
        "Heave KPI gain",
    )
    add(
        "Suspension",
        "trail_gain_heave_m_per_m",
        suspension["trail_gain_heave_m_per_m"],
        "m/m",
        "Heave mechanical trail gain",
    )
    add(
        "Suspension",
        "scrub_gain_heave_m_per_m",
        suspension["scrub_gain_heave_m_per_m"],
        "m/m",
        "Heave scrub gain",
    )
    add(
        "Suspension",
        "camber_gain_roll_rad_per_rad",
        suspension["camber_gain_roll_rad_per_rad"],
        "rad/rad",
        "Roll camber gain",
    )
    add("Suspension", "toe_gain_roll_rad_per_rad", suspension["toe_gain_roll_rad_per_rad"], "rad/rad", "Roll toe gain")
    add(
        "Suspension",
        "caster_gain_roll_rad_per_rad",
        suspension["caster_gain_roll_rad_per_rad"],
        "rad/rad",
        "Roll caster gain",
    )
    add("Suspension", "kpi_gain_roll_rad_per_rad", suspension["kpi_gain_roll_rad_per_rad"], "rad/rad", "Roll KPI gain")
    add(
        "Suspension",
        "trail_gain_roll_m_per_rad",
        suspension["trail_gain_roll_m_per_rad"],
        "m/rad",
        "Roll mechanical trail gain",
    )
    add("Suspension", "scrub_gain_roll_m_per_rad", suspension["scrub_gain_roll_m_per_rad"], "m/rad", "Roll scrub gain")
    add("Suspension", "avg_anti_dive_pct", suspension["avg_anti_dive_pct"], "%", "Average anti-dive")
    add("Suspension", "avg_anti_squat_pct", suspension["avg_anti_squat_pct"], "%", "Average anti-squat")
    add("Suspension", "avg_anti_roll_front_pct", suspension["avg_anti_roll_front_pct"], "%", "Average front anti-roll")
    add("Suspension", "avg_anti_roll_rear_pct", suspension["avg_anti_roll_rear_pct"], "%", "Average rear anti-roll")
    add(
        "Suspension",
        "avg_lateral_jacking_coeff_front",
        suspension["avg_lateral_jacking_coeff_front"],
        "-",
        "Front lateral jacking coefficient",
    )
    add(
        "Suspension",
        "avg_lateral_jacking_coeff_rear",
        suspension["avg_lateral_jacking_coeff_rear"],
        "-",
        "Rear lateral jacking coefficient",
    )
    add(
        "Suspension",
        "avg_longitudinal_jacking_coeff_front",
        suspension["avg_longitudinal_jacking_coeff_front"],
        "-",
        "Front longitudinal jacking coefficient",
    )
    add(
        "Suspension",
        "avg_longitudinal_jacking_coeff_rear",
        suspension["avg_longitudinal_jacking_coeff_rear"],
        "-",
        "Rear longitudinal jacking coefficient",
    )
    add(
        "Suspension",
        "spring_roll_stiffness_front_Nm_per_rad",
        suspension["spring_roll_stiffness_front_Nm_per_rad"],
        "N*m/rad",
        "Front spring roll stiffness",
    )
    add(
        "Suspension",
        "spring_roll_stiffness_rear_Nm_per_rad",
        suspension["spring_roll_stiffness_rear_Nm_per_rad"],
        "N*m/rad",
        "Rear spring roll stiffness",
    )
    add(
        "Suspension",
        "arb_roll_stiffness_front_Nm_per_rad",
        suspension["arb_roll_stiffness_front_Nm_per_rad"],
        "N*m/rad",
        "Front anti-roll bar stiffness",
    )
    add(
        "Suspension",
        "arb_roll_stiffness_rear_Nm_per_rad",
        suspension["arb_roll_stiffness_rear_Nm_per_rad"],
        "N*m/rad",
        "Rear anti-roll bar stiffness",
    )
    add(
        "Suspension",
        "elastic_roll_stiffness_front_Nm_per_rad",
        suspension["elastic_roll_stiffness_front_Nm_per_rad"],
        "N*m/rad",
        "Front elastic roll stiffness",
    )
    add(
        "Suspension",
        "elastic_roll_stiffness_rear_Nm_per_rad",
        suspension["elastic_roll_stiffness_rear_Nm_per_rad"],
        "N*m/rad",
        "Rear elastic roll stiffness",
    )

    add(
        "Performance",
        "roadwheel_angle_gradient_deg_per_g",
        performance["roadwheel_angle_gradient_deg_per_g"],
        "deg/g",
        "Mean roadwheel angle gradient",
    )
    add(
        "Performance",
        "handwheel_angle_gradient_deg_per_g",
        performance["handwheel_angle_gradient_deg_per_g"],
        "deg/g",
        "Mean handwheel angle gradient",
    )
    add(
        "Performance",
        "sideslip_gradient_deg_per_g",
        performance["sideslip_gradient_deg_per_g"],
        "deg/g",
        "Mean sideslip gradient",
    )
    add(
        "Performance",
        "understeer_gradient_deg_per_g",
        performance["understeer_gradient_deg_per_g"],
        "deg/g",
        "Mean understeer gradient",
    )
    add("Performance", "roll_gradient_deg_per_g", performance["roll_gradient_deg_per_g"], "deg/g", "Mean roll gradient")
    add(
        "Performance",
        "handwheel_torque_min_nm",
        performance["handwheel_torque_min_nm"],
        "N*m",
        "Minimum handwheel torque",
    )
    add(
        "Performance",
        "handwheel_torque_max_nm",
        performance["handwheel_torque_max_nm"],
        "N*m",
        "Maximum handwheel torque",
    )
    add(
        "Performance",
        "roadwheel_angle_gradient_velocity_slope_deg_per_g_per_mps",
        performance["roadwheel_angle_gradient_velocity_slope_deg_per_g_per_mps"],
        "deg/g per m/s",
        "Roadwheel gradient vs speed",
    )
    add(
        "Performance",
        "handwheel_angle_gradient_velocity_slope_deg_per_g_per_mps",
        performance["handwheel_angle_gradient_velocity_slope_deg_per_g_per_mps"],
        "deg/g per m/s",
        "Handwheel gradient vs speed",
    )
    add("Performance", "lag_steer_to_ay_s", performance["lag_steer_to_ay_s"], "s", "Steer-to-ay lag")
    add("Performance", "lag_steer_to_yaw_s", performance["lag_steer_to_yaw_s"], "s", "Steer-to-yaw lag")
    add("Performance", "step_ay_peak_mps2", performance["step_ay_peak_mps2"], "m/s^2", "Step acceleration peak")
    add("Performance", "step_ay_rise_time_s", performance["step_ay_rise_time_s"], "s", "Step acceleration rise time")
    add("Performance", "step_yaw_rise_time_s", performance["step_yaw_rise_time_s"], "s", "Step yaw rise time")
    add("Performance", "step_yaw_overshoot_pct", performance["step_yaw_overshoot_pct"], "%", "Step yaw overshoot")
    add("Performance", "step_roll_peak_rad", performance["step_roll_peak_rad"], "rad", "Step roll peak")
    add("Performance", "step_roll_overshoot_pct", performance["step_roll_overshoot_pct"], "%", "Step roll overshoot")
    add("Performance", "step_settling_time_s", performance["step_settling_time_s"], "s", "Step settling time")
    add("Performance", "frequency_bandwidth_hz", performance["frequency_bandwidth_hz"], "Hz", "Bandwidth estimate")
    add("Performance", "ay_gain_peak", performance["ay_gain_peak"], "", "Peak ay gain")
    add("Performance", "yaw_gain_peak", performance["yaw_gain_peak"], "", "Peak yaw gain")
    add("Performance", "ggv_max_abs_ay_g", ggv["max_abs_ay_g"], "g", "Peak GGV lateral capability")
    add("Performance", "ggv_max_accel_g", ggv["max_accel_g"], "g", "Peak GGV drive capability")
    add("Performance", "ggv_max_brake_g", ggv["max_brake_g"], "g", "Peak GGV brake capability")
    add("Performance", "ggv_peak_speed_mps", ggv["peak_speed_mps"], "m/s", "Speed where peak |ay| occurs")
    add("Performance", "ymd_converged_fraction", ymd["converged_fraction"], "-", "Fraction of YMD grid converged")
    add("Performance", "ymd_max_abs_ay_g", ymd["max_abs_ay_g"], "g", "Peak YMD lateral acceleration")
    add("Performance", "ymd_max_abs_mz_nm", ymd["max_abs_mz_nm"], "N*m", "Peak YMD yaw moment")
    add("Performance", "ymd_speed_min_mps", ymd["speed_min_mps"], "m/s", "YMD speed sweep start")
    add("Performance", "ymd_speed_max_mps", ymd["speed_max_mps"], "m/s", "YMD speed sweep stop")

    for row in coverage_rows:
        add(
            "Coverage",
            row["section"],
            row["status"],
            "",
            row["evidence"],
        )

    return rows


def _write_metrics_csv(path: Path, rows: MetricRows) -> None:
    with path.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(
            handle,
            fieldnames=["section", "metric", "value", "units", "description"],
            lineterminator="\n",
        )
        writer.writeheader()
        writer.writerows(rows)
    print(f"Saved review metrics CSV: {path}")


def _build_review(config: dict[str, Any]) -> dict[str, Any]:
    report_cfg = _mapping(config, "report")
    output_cfg = _mapping(config, "output")
    generation_cfg = _mapping(config, "generation")

    vehicle_data, source_yaml = load_active_vehicle_yaml()
    active_inputs = load_active_envelope_inputs(source_yaml)

    if _as_bool(generation_cfg.get("regenerate_ggv", True), name="generation.regenerate_ggv"):
        print("\nRegenerating GGV from the active vehicle configuration...")
        ggv_generation.main()

    if _as_bool(generation_cfg.get("regenerate_ymd", True), name="generation.regenerate_ymd"):
        print("\nRegenerating YMD from the active vehicle configuration...")
        ymd_generation.main()

    four_post_rows = _load_metric_rows(FOUR_POST_METRICS_PATH)
    steady_rows = _load_metric_rows(STEADY_STATE_METRICS_PATH)
    transient_rows = _load_metric_rows(TRANSIENT_METRICS_PATH)

    ggv_report_config = ggv_generation.load_ggv_config()
    ymd_report_config = ymd_generation.load_ymd_config()
    ggv_config = ggv_generation.config_to_ggv_config(ggv_report_config)

    tire_template = tire_template_name(vehicle_data, require_side(vehicle_data, "front"))
    tire_template_path = tire_templates_root(vehicle_data) / f"{tire_template}.tir"
    tire = _load_tire_metadata(tire_template_path)

    total_points: list[tuple[float, FloatArray, FloatArray]] = []
    sprung_points: list[tuple[float, FloatArray, FloatArray]] = []
    sprung_section = require_mapping(vehicle_data, "sprung_mass", vehicle_yaml_path())
    sprung_points.append(_mass_record(sprung_section, path="sprung_mass"))
    total_points.append(_mass_record(sprung_section, path="sprung_mass"))

    driver = vehicle_data.get("driver_mass")
    if isinstance(driver, dict):
        driver_mass_record = _mass_record(driver, path="driver_mass")
        sprung_points.append(driver_mass_record)
        total_points.append(driver_mass_record)
    else:
        driver_mass_record = None

    for side_name in ("front", "rear"):
        side = require_side(vehicle_data, side_name)
        masses = require_section(side, f"{side_name}", "masses")
        for mass_name in ("unsprung", "upper_control_arm", "lower_control_arm", "tie_rod"):
            mass_record = _mass_record(
                require_section(masses, f"{side_name}.masses", mass_name),
                path=f"{side_name}.masses.{mass_name}",
            )
            total_points.append(mass_record)

    total_mass, total_cg, _total_inertia = _combine_mass_properties(total_points)
    sprung_mass, sprung_cg, sprung_inertia = _combine_mass_properties(sprung_points)

    front_side = require_side(vehicle_data, "front")
    rear_side = require_side(vehicle_data, "rear")
    front_suspension = require_section(front_side, "front", "suspension")
    rear_suspension = require_section(rear_side, "rear", "suspension")
    front_wheel = require_section(front_side, "front", "wheel")
    front_tire = require_section(front_side, "front", "tire")
    front_steering = require_section(front_side, "front", "steering")
    front_wc = np.asarray(require_key(front_suspension, "front.suspension", "wheel_center_m"), dtype=float)
    rear_wc = np.asarray(require_key(rear_suspension, "rear.suspension", "wheel_center_m"), dtype=float)
    wheelbase = abs(float(front_wc[0]) - float(rear_wc[0]))
    track_front = abs(2.0 * float(front_wc[1]))
    track_rear = abs(2.0 * float(rear_wc[1]))

    direct_front_static_frac = (float(total_cg[0]) - float(rear_wc[0])) / wheelbase
    direct_front_static_frac = min(max(direct_front_static_frac, 0.0), 1.0)
    static_frac_delta = abs(direct_front_static_frac - active_inputs.front_static_frac)
    lltd_delta = abs(active_inputs.lltd - _metric_float(four_post_rows, "avg_lltd_front_frac"))

    if driver_mass_record is None:
        driver_mass = 0.0
        driver_inertia_diag = "(0.000, 0.000, 0.000)"
    else:
        driver_mass = float(driver_mass_record[0])
        driver_inertia_diag = _format_vector(np.diag(driver_mass_record[2]), precision=3)

    front_static_fz_per_tire = total_mass * G * active_inputs.front_static_frac / 2.0
    rear_static_fz_per_tire = total_mass * G * (1.0 - active_inputs.front_static_frac) / 2.0

    vehicle = {
        "vehicle_name": str(require_mapping(vehicle_data, "vehicle", vehicle_yaml_path()).get("name", "ActiveVehicle")),
        "source_yaml": str(source_yaml),
        "mass_kg": float(total_mass),
        "wheelbase_m": float(wheelbase),
        "track_front_m": float(track_front),
        "track_rear_m": float(track_rear),
        "cg_height_m": float(total_cg[2]),
        "front_static_frac": float(active_inputs.front_static_frac),
        "lltd_front_frac": float(active_inputs.lltd),
        "front_static_fz_per_tire_n": float(front_static_fz_per_tire),
        "rear_static_fz_per_tire_n": float(rear_static_fz_per_tire),
        "cl_a": float(active_inputs.cl_a),
        "cd_a": float(active_inputs.cd_a),
        "aero_reference_speed_mps": float(active_inputs.aero_reference_speed),
        "aero_balance_front": float(active_inputs.aero_balance_front),
        "sprung_mass_kg": float(sprung_section["mass_kg"]),
        "driver_mass_kg": float(driver_mass),
        "combined_sprung_mass_kg": float(sprung_mass),
        "combined_sprung_cg": _format_vector(sprung_cg, precision=3),
        "sprung_inertia_diag": _format_vector(np.diag(sprung_inertia), precision=3),
        "driver_inertia_diag": driver_inertia_diag,
        "body_torsional_stiffness_n_m_per_rad": float(
            require_mapping(vehicle_data, "body", vehicle_yaml_path())["torsional_stiff_n_m_per_rad"]
        ),
        "wheel_radius_m": float(require_key(front_wheel, "front.wheel", "radius_m")),
        "wheel_inertia_kg_m2": float(require_key(front_tire, "front.tire", "wheel_inertia_kg_m2")),
        "toe_deg": float(require_key(front_wheel, "front.wheel", "toe_deg")),
        "camber_deg": float(require_key(front_wheel, "front.wheel", "camber_deg")),
        "tire_vertical_stiffness_n_per_m": float(require_key(front_tire, "front.tire", "vertical_stiffness_n_per_m")),
        "tire_vertical_damping_n_s_per_m": float(require_key(front_tire, "front.tire", "vertical_damping_n_s_per_m")),
        "rack_travel_per_rev_m": float(require_key(front_steering, "front.steering", "rack_travel_per_rev_m")),
    }

    powertrain = {
        "drive_distribution_front": float(active_inputs.drive_distribution_front),
        "brake_distribution_front": float(active_inputs.brake_distribution_front),
        "max_drive_power_w": float(active_inputs.max_drive_power),
        "max_drive_force_n": float(active_inputs.max_drive_force),
        "max_brake_force_n": float(active_inputs.max_brake_force),
    }

    tire["ip_nom_pa"] = tire["nominal_pressure_pa"]
    tire["ip_nom_psi"] = tire["nominal_pressure_psi"]

    tire_mu_x_ref = tire["pdx1"]
    tire_mu_y_ref = abs(tire["pdy1"])
    tire["mu_x_ref"] = tire_mu_x_ref
    tire["mu_y_ref"] = tire_mu_y_ref

    def mu_x_at(fz: float) -> float:
        dfz = (fz - tire["fznom_n"]) / tire["fznom_n"]
        return max(tire["pdx1"] + tire["pdx2"] * dfz, 0.0)

    def mu_y_at(fz: float) -> float:
        dfz = (fz - tire["fznom_n"]) / tire["fznom_n"]
        return max(abs(tire["pdy1"] + tire["pdy2"] * dfz), 0.0)

    tire["mu_x_min"] = mu_x_at(tire["fzmin_valid_n"])
    tire["mu_x_max"] = mu_x_at(tire["fzmax_valid_n"])
    tire["mu_y_min"] = mu_y_at(tire["fzmin_valid_n"])
    tire["mu_y_max"] = mu_y_at(tire["fzmax_valid_n"])
    tire["relaxation_summary"] = (
        f"USE_MODE={tire['use_mode']}; LSGKP={tire['lsgkp']:.2f}; LSGAL={tire['lsgal']:.2f}; "
        "temperature state not modeled in the first-principles envelope"
    )
    tire["combined_fx_summary"] = "GGV uses peak load-sensitive longitudinal coefficients; no full combined-slip solve"
    tire["combined_fy_summary"] = "GGV/YMD use peak load-sensitive lateral coefficients plus a friction ellipse"

    suspension = _corner_modal_summary(vehicle_data, four_post_rows)
    suspension.update(
        {
            "avg_anti_dive_pct": _metric_float(four_post_rows, "avg_anti_dive_pct"),
            "avg_anti_squat_pct": _metric_float(four_post_rows, "avg_anti_squat_pct"),
            "avg_anti_roll_front_pct": _metric_float(four_post_rows, "avg_anti_roll_front_pct"),
            "avg_anti_roll_rear_pct": _metric_float(four_post_rows, "avg_anti_roll_rear_pct"),
            "avg_lltd_front_frac": _metric_float(four_post_rows, "avg_lltd_front_frac"),
            "avg_lltd_front_pct": _metric_float(four_post_rows, "avg_lltd_front_pct"),
            "avg_longitudinal_jacking_coeff_front": _metric_float(
                four_post_rows,
                "avg_longitudinal_jacking_coeff_front",
            ),
            "avg_longitudinal_jacking_coeff_rear": _metric_float(
                four_post_rows,
                "avg_longitudinal_jacking_coeff_rear",
            ),
            "avg_lateral_jacking_coeff_front": _metric_float(
                four_post_rows,
                "avg_lateral_jacking_coeff_front",
            ),
            "avg_lateral_jacking_coeff_rear": _metric_float(
                four_post_rows,
                "avg_lateral_jacking_coeff_rear",
            ),
            "camber_gain_heave_rad_per_m": _metric_float(four_post_rows, "camber_gain_heave_rad_per_m"),
            "toe_gain_heave_rad_per_m": _metric_float(four_post_rows, "toe_gain_heave_rad_per_m"),
            "caster_gain_heave_rad_per_m": _metric_float(four_post_rows, "caster_gain_heave_rad_per_m"),
            "kpi_gain_heave_rad_per_m": _metric_float(four_post_rows, "kpi_gain_heave_rad_per_m"),
            "trail_gain_heave_m_per_m": _metric_float(four_post_rows, "trail_gain_heave_m_per_m"),
            "scrub_gain_heave_m_per_m": _metric_float(four_post_rows, "scrub_gain_heave_m_per_m"),
            "camber_gain_roll_rad_per_rad": _metric_float(four_post_rows, "camber_gain_roll_rad_per_rad"),
            "toe_gain_roll_rad_per_rad": _metric_float(four_post_rows, "toe_gain_roll_rad_per_rad"),
            "caster_gain_roll_rad_per_rad": _metric_float(four_post_rows, "caster_gain_roll_rad_per_rad"),
            "kpi_gain_roll_rad_per_rad": _metric_float(four_post_rows, "kpi_gain_roll_rad_per_rad"),
            "trail_gain_roll_m_per_rad": _metric_float(four_post_rows, "trail_gain_roll_m_per_rad"),
            "scrub_gain_roll_m_per_rad": _metric_float(four_post_rows, "scrub_gain_roll_m_per_rad"),
            "spring_roll_stiffness_front_Nm_per_rad": _metric_float(
                four_post_rows,
                "spring_roll_stiffness_front_Nm_per_rad",
            ),
            "spring_roll_stiffness_rear_Nm_per_rad": _metric_float(
                four_post_rows,
                "spring_roll_stiffness_rear_Nm_per_rad",
            ),
            "arb_roll_stiffness_front_Nm_per_rad": _metric_float(
                four_post_rows,
                "arb_roll_stiffness_front_Nm_per_rad",
            ),
            "arb_roll_stiffness_rear_Nm_per_rad": _metric_float(
                four_post_rows,
                "arb_roll_stiffness_rear_Nm_per_rad",
            ),
            "elastic_roll_stiffness_front_Nm_per_rad": _metric_float(
                four_post_rows,
                "elastic_roll_stiffness_front_Nm_per_rad",
            ),
            "elastic_roll_stiffness_rear_Nm_per_rad": _metric_float(
                four_post_rows,
                "elastic_roll_stiffness_rear_Nm_per_rad",
            ),
        }
    )

    steady_state = {
        "roadwheel_angle_gradient_deg_per_g": _metric_float(
            steady_rows,
            "roadwheel_angle_gradient_deg_per_g",
        ),
        "handwheel_angle_gradient_deg_per_g": _metric_float(
            steady_rows,
            "handwheel_angle_gradient_deg_per_g",
        ),
        "sideslip_gradient_deg_per_g": _metric_float(steady_rows, "sideslip_gradient_deg_per_g"),
        "understeer_gradient_deg_per_g": _metric_float(steady_rows, "understeer_gradient_deg_per_g"),
        "roll_gradient_deg_per_g": _metric_float(steady_rows, "roll_gradient_deg_per_g"),
        "handwheel_torque_min_nm": _metric_float(steady_rows, "handwheel_torque_min"),
        "handwheel_torque_max_nm": _metric_float(steady_rows, "handwheel_torque_max"),
        "roadwheel_angle_gradient_velocity_slope_deg_per_g_per_mps": _metric_float(
            steady_rows,
            "roadwheel_angle_gradient_velocity_slope_deg_per_g_per_mps",
        ),
        "handwheel_angle_gradient_velocity_slope_deg_per_g_per_mps": _metric_float(
            steady_rows,
            "handwheel_angle_gradient_velocity_slope_deg_per_g_per_mps",
        ),
        "sideslip_gradient_velocity_slope_deg_per_g_per_mps": _metric_float(
            steady_rows,
            "sideslip_gradient_velocity_slope_deg_per_g_per_mps",
        ),
        "understeer_gradient_velocity_slope_deg_per_g_per_mps": _metric_float(
            steady_rows,
            "understeer_gradient_velocity_slope_deg_per_g_per_mps",
        ),
        "roll_gradient_velocity_slope_deg_per_g_per_mps": _metric_float(
            steady_rows,
            "roll_gradient_velocity_slope_deg_per_g_per_mps",
        ),
    }

    transient = {
        "step_ay_peak_mps2": _metric_float(transient_rows, "ay_peak"),
        "step_ay_ss_mps2": _metric_float(transient_rows, "ay_ss"),
        "step_ay_rise_time_s": _metric_float(transient_rows, "ay_rise_time_s"),
        "step_ay_peak_response_time_s": _metric_float(transient_rows, "ay_peak_response_time_s"),
        "step_ay_overshoot_pct": _metric_float(transient_rows, "ay_overshoot_pct"),
        "step_sideslip_ss_rad": _metric_float(transient_rows, "sideslip_ss"),
        "step_sideslip_rise_time_s": _metric_float(transient_rows, "sideslip_rise_time_s"),
        "step_yaw_rise_time_s": _metric_float(transient_rows, "yaw_rise_time_s"),
        "step_yaw_peak_response_time_s": _metric_float(
            transient_rows,
            "yaw_peak_response_time_s",
        ),
        "step_yaw_overshoot_pct": _metric_float(transient_rows, "yaw_overshoot_pct"),
        "step_roll_peak_rad": _metric_float(transient_rows, "roll_peak"),
        "step_roll_ss_rad": _metric_float(transient_rows, "roll_ss"),
        "step_roll_gain_dc": _metric_float(transient_rows, "roll_gain_dc"),
        "step_roll_overshoot_pct": _metric_float(transient_rows, "roll_overshoot_pct"),
        "step_settling_time_s": _metric_float(transient_rows, "settling_time_s"),
        "ay_gain_peak": _metric_float(transient_rows, "ay_gain_peak"),
        "yaw_gain_peak": _metric_float(transient_rows, "yaw_gain_peak"),
        "bandwidth_hz": _metric_float(transient_rows, "bandwidth_hz"),
        "frequency_bandwidth_hz": _metric_float(transient_rows, "bandwidth_hz"),
        "ay_phase_0p5hz_deg": _metric_float(transient_rows, "ay_phase_0p5hz"),
        "yaw_phase_0p5hz_deg": _metric_float(transient_rows, "yaw_phase_0p5hz"),
        "ay_phase_1hz_deg": _metric_float(transient_rows, "ay_phase_1hz"),
        "yaw_phase_1hz_deg": _metric_float(transient_rows, "yaw_phase_1hz"),
        "ay_lag_0p5hz_s": _metric_float(transient_rows, "ay_lag_0p5hz"),
        "yaw_lag_0p5hz_s": _metric_float(transient_rows, "yaw_lag_0p5hz"),
        "yaw_to_ay_lag_0p5hz_s": _metric_float(transient_rows, "yaw_to_ay_lag_0p5hz"),
        "ay_lag_1hz_s": _metric_float(transient_rows, "ay_lag_1hz"),
        "yaw_lag_1hz_s": _metric_float(transient_rows, "yaw_lag_1hz"),
        "yaw_to_ay_lag_1hz_s": _metric_float(transient_rows, "yaw_to_ay_lag_1hz"),
        "lag_steer_to_ay_s": _metric_float(transient_rows, "ay_lag_0p5hz"),
        "lag_steer_to_yaw_s": _metric_float(transient_rows, "yaw_lag_0p5hz"),
    }

    performance = {**steady_state, **transient}

    ggv_summary = _summarize_ggv(GGV_CSV_PATH, tuple(ggv_config.speeds))
    ymd_summary = _summarize_ymd(YMD_CSV_PATH, ymd_report_config)

    performance.update(
        {
            "ggv_max_abs_ay_g": ggv_summary["max_abs_ay_g"],
            "ggv_max_accel_g": ggv_summary["max_accel_g"],
            "ggv_max_brake_g": ggv_summary["max_brake_g"],
            "ggv_peak_speed_mps": ggv_summary["peak_speed_mps"],
        }
    )

    coverage_rows = _build_coverage_rows()
    missing_items = _build_missing_items()

    track_delta = max(
        abs(track_front - active_inputs.track_front),
        abs(track_rear - active_inputs.track_rear),
    )

    sources = {
        "vehicle_yaml": str(source_yaml),
        "lltd_source": active_inputs.lltd_source,
        "aero_source": active_inputs.aero_source,
        "tire_template_path": str(tire_template_path),
        "ggv_csv_path": str(GGV_CSV_PATH),
        "ymd_csv_path": str(YMD_CSV_PATH),
        "four_post_metrics_path": str(FOUR_POST_METRICS_PATH),
        "steady_state_metrics_path": str(STEADY_STATE_METRICS_PATH),
        "transient_metrics_path": str(TRANSIENT_METRICS_PATH),
        "summary_sentence": (
            f"vehicle.yml + {active_inputs.lltd_source} LLTD + {active_inputs.aero_source} aero + fresh GGV/YMD outputs"
        ),
        "agreement_summary": (
            f"Δmass={abs(total_mass - active_inputs.mass):.4f} kg, "
            f"Δwb={abs(wheelbase - active_inputs.wheelbase):.6f} m, "
            f"Δstatic_frac={static_frac_delta:.6f}, "
            f"Δtrack={track_delta:.6f} m, "
            f"ΔLLTD={lltd_delta:.6f}"
        ),
    }

    strategy_bullets = [
        (
            "Use the active vehicle.yml as the single source of truth, then let "
            "four-post LLTD and envelope outputs refine the review."
        ),
        (
            "Keep the envelope models load-sensitive and aero-aware so the report "
            "stays tied to the real tire and geometry choices."
        ),
        (
            "Bias the system toward predictable understeer and traction-limited "
            "acceleration rather than an artificially optimistic lap-time model."
        ),
    ]
    tradeoff_bullets = [
        (
            "Front brake bias and slightly front-biased LLTD improve stability, "
            "but they do trade away some pure cornering headroom."
        ),
        (
            "The first-principles envelope stays quasi-static and "
            "temperature-agnostic, which keeps it repeatable but leaves thermal "
            "tire behavior as a gap."
        ),
        (
            "A symmetric aero split is a deliberate simplification because the "
            "active aero map is symmetric and does not encode a separate "
            "front/rear aero balance knob."
        ),
    ]

    return {
        "report": report_cfg,
        "vehicle": vehicle,
        "powertrain": powertrain,
        "performance": performance,
        "sources": sources,
        "strategy_bullets": strategy_bullets,
        "tradeoff_bullets": tradeoff_bullets,
        "ggv": ggv_summary,
        "ymd": ymd_summary,
        "tire": tire,
        "suspension": suspension,
        "coverage_rows": coverage_rows,
        "missing_items": missing_items,
        "output_dir": _as_path(output_cfg["results_dir"], name="output.results_dir"),
        "pdf_filename": str(output_cfg["pdf_filename"]),
        "metrics_csv_filename": str(output_cfg["metrics_csv_filename"]),
    }


def _build_coverage_rows() -> list[dict[str, str]]:
    return [
        {
            "section": "Envelope inputs",
            "status": "covered",
            "evidence": "vehicle.yml + latest four-post LLTD + active .tir",
        },
        {
            "section": "Mass/inertia",
            "status": "covered",
            "evidence": "vehicle mass, CG, and inertia are computed from the active YAML",
        },
        {
            "section": "Tire selection",
            "status": "partial",
            "evidence": "template name and .tir coefficients are known; manufacturer/compound are not encoded",
        },
        {
            "section": "Static tire setup",
            "status": "covered",
            "evidence": "toe, camber, pressure, radius, and valid load window come from vehicle.yml / .tir",
        },
        {
            "section": "Load sensitivity",
            "status": "covered",
            "evidence": "PDX/PDY peak curves plus Fz range feed the GGV and YMD models",
        },
        {
            "section": "Relaxation / temperature",
            "status": "partial",
            "evidence": "LSGKP/LSGAL exist, but thermal tire state is not time-marched here",
        },
        {
            "section": "Wheel selection",
            "status": "partial",
            "evidence": "radius and rim width are known; wheel offset/material are not encoded",
        },
        {
            "section": "Heave / pitch / roll",
            "status": "covered",
            "evidence": "four-post report gives gains, anti-geometry, and roll stiffness",
        },
        {
            "section": "Kinematics",
            "status": "covered",
            "evidence": "camber, toe, caster, KPI, trail, and scrub gains come from four-post",
        },
        {
            "section": "Anti-geometry",
            "status": "covered",
            "evidence": "anti-dive, anti-squat, anti-roll, and jacking are all reported",
        },
        {
            "section": "Springs and dampers",
            "status": "covered",
            "evidence": "motion ratios, rates, compression, and quarter-car modes are derived from the active vehicle",
        },
        {
            "section": "Steering",
            "status": "partial",
            "evidence": "roadwheel gradients and rack travel are modeled; explicit Ackermann remains manual",
        },
        {
            "section": "Performance metrics",
            "status": "covered",
            "evidence": "steady-state, transient, GGV, and YMD metrics are all summarized",
        },
        {
            "section": "Physical test data",
            "status": "manual gap",
            "evidence": "no stopwatch, accelerometer, or wheel-speed import is present in the repo",
        },
        {
            "section": "Torque vectoring",
            "status": "partial",
            "evidence": "drive/brake distribution is modeled; active torque vectoring is not",
        },
    ]


def _build_missing_items() -> list[str]:
    return [
        "Tire manufacturer and compound are not encoded in the active .tir or vehicle.yml.",
        "Wheel offset and wheel material are not modeled in the current vehicle definition.",
        "Explicit Ackermann is not separated from the rack geometry; steering is reviewed via gradients.",
        "Tire temperature dynamics are not time-marched in the first-principles GGV/YMD tools.",
        "No physical stopwatch, accelerometer, or wheel-speed dataset is imported yet.",
        "Torque vectoring is not modeled; the envelope uses fixed drive and brake distribution knobs.",
    ]


def main() -> None:
    config = load_review_config()
    report_cfg = _mapping(config, "report")
    output_cfg = _mapping(config, "output")

    output_dir = _as_path(output_cfg["results_dir"], name="output.results_dir")
    output_dir.mkdir(parents=True, exist_ok=True)
    pdf_path = output_dir / str(output_cfg["pdf_filename"])
    metrics_path = output_dir / str(output_cfg["metrics_csv_filename"])

    print(f"Loaded VehicleReview config: {DEFAULT_CONFIG_PATH}")
    print("Building rubric-oriented review from the active vehicle definition")
    print(f"  source YAML   = {vehicle_yaml_path()}")
    print(f"  results dir   = {output_dir}")
    print(f"  report title  = {report_cfg.get('title', 'Vehicle Review and Rubric Coverage')}")

    review = _build_review(config)
    metrics_rows = _build_review_metrics(review)
    _write_metrics_csv(metrics_path, metrics_rows)

    with PdfPages(pdf_path) as pdf:
        add_title_page(pdf, config)
        add_review_overview_page(pdf, review)
        add_review_fundamentals_page(pdf, review)
        add_review_tires_page(pdf, review)
        add_review_suspension_page(pdf, review)
        add_review_performance_page(pdf, review)
        add_review_coverage_page(pdf, review)

    print(f"Saved review PDF: {pdf_path}")
    print(f"Saved review metrics CSV: {metrics_path}")


if __name__ == "__main__":
    main()
