from __future__ import annotations

import textwrap
from collections.abc import Sequence
from typing import Any

import matplotlib.pyplot as plt
import numpy as np


MetricRow = tuple[str, Any, str, str, float]


def _is_finite_number(value: Any) -> bool:
    try:
        return bool(np.isfinite(float(value)))
    except (TypeError, ValueError):
        return False


def _format_value(value: Any, fmt: str = "{:.2f}", scale: float = 1.0) -> str:
    if value is None:
        return "—"

    if isinstance(value, str):
        try:
            return fmt.format(value)
        except Exception:
            return value

    try:
        numeric = float(value)
    except (TypeError, ValueError):
        return str(value)

    if not np.isfinite(numeric):
        return "—"

    try:
        return fmt.format(numeric * scale)
    except Exception:
        return str(numeric * scale)


def _make_page(title: str, subtitle: str | None = None):
    fig = plt.figure(figsize=(11, 8.5))
    ax = plt.axes((0.0, 0.0, 1.0, 1.0))
    ax.set_xlim(0, 1)
    ax.set_ylim(0, 1)
    ax.axis("off")

    ax.text(
        0.5,
        0.955,
        title,
        ha="center",
        va="top",
        fontsize=19,
        weight="bold",
        color="#1f2937",
    )
    if subtitle:
        ax.text(
            0.5,
            0.918,
            subtitle,
            ha="center",
            va="top",
            fontsize=10.4,
            color="#4b5563",
        )

    ax.plot([0.06, 0.94], [0.892, 0.892], color="#d6dbe4", linewidth=1.0)
    return fig, ax


def _draw_bullet_block(
    ax,
    x0: float,
    x1: float,
    y_top: float,
    y_bottom: float,
    title: str,
    bullets: Sequence[str],
    *,
    width_chars: int = 52,
    font_size: float = 9.8,
) -> None:
    ax.add_patch(
        plt.Rectangle(
            (x0, y_bottom),
            x1 - x0,
            y_top - y_bottom,
            fill=False,
            edgecolor="#d6dbe4",
            linewidth=1.0,
        )
    )
    ax.text(
        x0 + 0.012,
        y_top - 0.016,
        title,
        ha="left",
        va="top",
        fontsize=12.5,
        weight="bold",
        color="#1f2937",
    )

    if not bullets:
        bullets = ("No notes provided.",)

    y = y_top - 0.060
    line_step = 0.031
    paragraph_gap = 0.008

    for bullet in bullets:
        wrapped = textwrap.wrap(
            str(bullet),
            width=width_chars,
            break_long_words=False,
            break_on_hyphens=False,
        )
        if not wrapped:
            wrapped = [""]
        for idx, line in enumerate(wrapped):
            prefix = "• " if idx == 0 else "  "
            ax.text(
                x0 + 0.014,
                y,
                prefix + line,
                ha="left",
                va="top",
                fontsize=font_size,
                color="#111827",
            )
            y -= line_step
        y -= paragraph_gap


def _draw_section(
    ax,
    x0: float,
    x1: float,
    y_top: float,
    title: str,
    rows: Sequence[MetricRow],
    *,
    row_step: float = 0.045,
    title_font: float = 12.8,
    row_font: float = 9.4,
) -> float:
    width = x1 - x0
    x_metric = x0
    x_value = x0 + 0.67 * width
    x_unit = x1
    x_title = 0.5 * (x0 + x1)

    ax.text(
        x_title,
        y_top,
        title,
        fontsize=title_font,
        weight="bold",
        ha="center",
        color="#1f2937",
    )
    header_y = y_top - 0.038
    ax.text(x_metric, header_y, "Metric", fontsize=9.8, weight="bold", color="#1f2937")
    ax.text(x_value, header_y, "Value", fontsize=9.8, weight="bold", ha="right", color="#1f2937")
    ax.text(x_unit, header_y, "Units", fontsize=9.8, weight="bold", color="#1f2937")
    ax.plot(
        [x_metric, x_unit + 0.005],
        [header_y - 0.014, header_y - 0.014],
        color="#c8cfdb",
        linewidth=1.0,
    )

    y = header_y - 0.038
    for label, value, unit, fmt, scale in rows:
        ax.text(x_metric, y, label, fontsize=row_font, color="#111827")
        ax.text(
            x_value,
            y,
            _format_value(value, fmt, scale),
            fontsize=row_font,
            ha="right",
            color="#111827",
        )
        ax.text(x_unit, y, unit, fontsize=row_font, color="#444b55")
        y -= row_step

    return y


def add_review_overview_page(pdf, review: dict[str, Any]) -> None:
    vehicle = review["vehicle"]
    performance = review["performance"]
    sources = review["sources"]

    fig, ax = _make_page(
        "Executive Overview",
        f"{vehicle['vehicle_name']} | active vehicle.yml + StandardSim + EnvelopeSim correlation",
    )

    _draw_bullet_block(
        ax,
        0.05,
        0.48,
        0.84,
        0.58,
        "Strategy",
        review["strategy_bullets"],
    )
    _draw_bullet_block(
        ax,
        0.52,
        0.95,
        0.84,
        0.58,
        "Trade-offs",
        review["tradeoff_bullets"],
    )

    rows: list[MetricRow] = [
        ("Mass", vehicle["mass_kg"], "kg", "{:.1f}", 1.0),
        ("Wheelbase", vehicle["wheelbase_m"], "m", "{:.3f}", 1.0),
        ("Track F / R", f"{vehicle['track_front_m']:.3f} / {vehicle['track_rear_m']:.3f}", "m", "{}", 1.0),
        ("CG height", vehicle["cg_height_m"], "m", "{:.4f}", 1.0),
        ("Front static frac", vehicle["front_static_frac"], "-", "{:.4f}", 1.0),
        ("LLTD front frac", vehicle["lltd_front_frac"], "-", "{:.4f}", 1.0),
        ("Aero balance front", vehicle["aero_balance_front"], "-", "{:.2f}", 1.0),
        ("Steady-state roll gradient", performance["roll_gradient_deg_per_g"], "deg/g", "{:.3f}", 1.0),
        ("Steady-state understeer gradient", performance["understeer_gradient_deg_per_g"], "deg/g", "{:.3f}", 1.0),
        ("GGV max |ay|", performance["ggv_max_abs_ay_g"], "g", "{:.3f}", 1.0),
        ("Step yaw rise time", performance["step_yaw_rise_time_s"], "s", "{:.3f}", 1.0),
        ("Files used", sources["summary_sentence"], "", "{}", 1.0),
    ]

    _draw_section(ax, 0.05, 0.95, 0.51, "Key Facts", rows, row_step=0.040)

    pdf.savefig(fig)
    plt.close(fig)


def add_review_fundamentals_page(pdf, review: dict[str, Any]) -> None:
    vehicle = review["vehicle"]
    powertrain = review["powertrain"]
    performance = review["performance"]

    fig, ax = _make_page("Fundamentals", "Mass properties, balance, aero, and powertrain assumptions")

    left_rows: list[MetricRow] = [
        ("Sprung mass", vehicle["sprung_mass_kg"], "kg", "{:.1f}", 1.0),
        ("Driver mass", vehicle["driver_mass_kg"], "kg", "{:.1f}", 1.0),
        ("Combined sprung mass", vehicle["combined_sprung_mass_kg"], "kg", "{:.1f}", 1.0),
        ("Sprung CG", vehicle["combined_sprung_cg"], "m", "{}", 1.0),
        ("Sprung inertia diag", vehicle["sprung_inertia_diag"], "kg·m²", "{}", 1.0),
        ("Driver inertia diag", vehicle["driver_inertia_diag"], "kg·m²", "{}", 1.0),
        ("Body torsional stiffness", vehicle["body_torsional_stiffness_n_m_per_rad"], "N·m/rad", "{:.0f}", 1.0),
        ("Wheelbase", vehicle["wheelbase_m"], "m", "{:.4f}", 1.0),
        ("Track front", vehicle["track_front_m"], "m", "{:.4f}", 1.0),
        ("Track rear", vehicle["track_rear_m"], "m", "{:.4f}", 1.0),
    ]

    right_rows: list[MetricRow] = [
        ("Total mass", vehicle["mass_kg"], "kg", "{:.1f}", 1.0),
        ("CG height", vehicle["cg_height_m"], "m", "{:.4f}", 1.0),
        ("Front static fraction", vehicle["front_static_frac"], "-", "{:.4f}", 1.0),
        ("Front LLTD fraction", vehicle["lltd_front_frac"], "-", "{:.4f}", 1.0),
        ("Static Fz / tire front", vehicle["front_static_fz_per_tire_n"], "N", "{:.1f}", 1.0),
        ("Static Fz / tire rear", vehicle["rear_static_fz_per_tire_n"], "N", "{:.1f}", 1.0),
        ("Aero ClA", vehicle["cl_a"], "m²", "{:.3f}", 1.0),
        ("Aero CdA", vehicle["cd_a"], "m²", "{:.3f}", 1.0),
        ("Aero balance front", vehicle["aero_balance_front"], "-", "{:.2f}", 1.0),
        ("Reference aero speed", vehicle["aero_reference_speed_mps"], "m/s", "{:.1f}", 1.0),
        ("Drive distribution front", powertrain["drive_distribution_front"], "-", "{:.2f}", 1.0),
        ("Brake distribution front", powertrain["brake_distribution_front"], "-", "{:.2f}", 1.0),
        ("Max drive power", powertrain["max_drive_power_w"], "W", "{:.0f}", 1.0),
        ("Max drive force", powertrain["max_drive_force_n"], "N", "{:.0f}", 1.0),
        ("Max brake force", powertrain["max_brake_force_n"], "N", "{:.0f}", 1.0),
    ]

    _draw_section(ax, 0.05, 0.47, 0.82, "Mass & Inertia", left_rows, row_step=0.040)
    _draw_section(ax, 0.53, 0.95, 0.82, "Balance & Limits", right_rows, row_step=0.034)

    note_rows: list[MetricRow] = [
        ("Roadwheel angle gradient", performance["roadwheel_angle_gradient_deg_per_g"], "deg/g", "{:.3f}", 1.0),
        ("Handwheel angle gradient", performance["handwheel_angle_gradient_deg_per_g"], "deg/g", "{:.3f}", 1.0),
        ("Understeer gradient", performance["understeer_gradient_deg_per_g"], "deg/g", "{:.3f}", 1.0),
        ("Roll gradient", performance["roll_gradient_deg_per_g"], "deg/g", "{:.3f}", 1.0),
    ]
    _draw_section(ax, 0.05, 0.95, 0.22, "Handling Baseline", note_rows, row_step=0.040)

    pdf.savefig(fig)
    plt.close(fig)


def add_review_tires_page(pdf, review: dict[str, Any]) -> None:
    tire = review["tire"]
    vehicle = review["vehicle"]

    fig, ax = _make_page("Tires", "Selection, static setup, load sensitivity, and peak coefficients")

    left_rows: list[MetricRow] = [
        ("Template", tire["template"], "", "{}", 1.0),
        ("Size comment", tire["size_comment"], "", "{}", 1.0),
        ("Manufacturer", tire["manufacturer"], "", "{}", 1.0),
        ("Compound", tire["compound"], "", "{}", 1.0),
        ("Wheel material", tire["wheel_material"], "", "{}", 1.0),
        ("Nominal pressure", tire["ip_nom_pa"], "Pa", "{:.0f}", 1.0),
        ("Nominal pressure", tire["ip_nom_psi"], "psi", "{:.1f}", 1.0),
        ("Rim radius", tire["rim_radius_m"], "m", "{:.4f}", 1.0),
        ("Rim width", tire["rim_width_m"], "m", "{:.4f}", 1.0),
        ("Unloaded radius", tire["unloaded_radius_m"], "m", "{:.4f}", 1.0),
        ("Wheel radius", vehicle["wheel_radius_m"], "m", "{:.4f}", 1.0),
        ("Wheel inertia", vehicle["wheel_inertia_kg_m2"], "kg·m²", "{:.4f}", 1.0),
        ("Static toe", vehicle["toe_deg"], "deg", "{:.2f}", 1.0),
        ("Static camber", vehicle["camber_deg"], "deg", "{:.2f}", 1.0),
        ("Vertical stiffness", vehicle["tire_vertical_stiffness_n_per_m"], "N/m", "{:.0f}", 1.0),
        ("Vertical damping", vehicle["tire_vertical_damping_n_s_per_m"], "N·s/m", "{:.1f}", 1.0),
        ("Valid Fz range", f"{tire['fz_min_valid_n']:.0f} to {tire['fz_max_valid_n']:.0f}", "N", "{}", 1.0),
        (
            "Static Fz / tire",
            f"{vehicle['front_static_fz_per_tire_n']:.1f} / {vehicle['rear_static_fz_per_tire_n']:.1f}",
            "N",
            "{}",
            1.0,
        ),
    ]

    right_rows: list[MetricRow] = [
        ("FNOMIN", tire["fznom_n"], "N", "{:.0f}", 1.0),
        ("PDX1", tire["pdx1"], "-", "{:.6f}", 1.0),
        ("PDX2", tire["pdx2"], "-", "{:.6f}", 1.0),
        ("PDX3", tire["pdx3"], "-", "{:.6f}", 1.0),
        ("PDY1", tire["pdy1"], "-", "{:.6f}", 1.0),
        ("PDY2", tire["pdy2"], "-", "{:.6f}", 1.0),
        ("PDY3", tire["pdy3"], "-", "{:.6f}", 1.0),
        ("PKX1", tire["pkx1"], "-", "{:.6f}", 1.0),
        ("PKX2", tire["pkx2"], "-", "{:.6f}", 1.0),
        ("PKX3", tire["pkx3"], "-", "{:.6f}", 1.0),
        ("PKY1", tire["pky1"], "-", "{:.6f}", 1.0),
        ("PKY2", tire["pky2"], "-", "{:.6f}", 1.0),
        ("PKY3", tire["pky3"], "-", "{:.6f}", 1.0),
        ("Combined-slip Fx", tire["combined_fx_summary"], "", "{}", 1.0),
        ("Combined-slip Fy", tire["combined_fy_summary"], "", "{}", 1.0),
        ("Relaxation", tire["relaxation_summary"], "", "{}", 1.0),
        ("mu_x at FNOMIN", tire["mu_x_ref"], "-", "{:.3f}", 1.0),
        ("mu_y at FNOMIN", tire["mu_y_ref"], "-", "{:.3f}", 1.0),
        ("mu_x at Fz min", tire["mu_x_min"], "-", "{:.3f}", 1.0),
        ("mu_x at Fz max", tire["mu_x_max"], "-", "{:.3f}", 1.0),
        ("mu_y at Fz min", tire["mu_y_min"], "-", "{:.3f}", 1.0),
        ("mu_y at Fz max", tire["mu_y_max"], "-", "{:.3f}", 1.0),
    ]

    _draw_section(ax, 0.05, 0.47, 0.82, "Selection & Static Setup", left_rows, row_step=0.031)
    _draw_section(ax, 0.53, 0.95, 0.82, "Peak Model & Response", right_rows, row_step=0.028)

    pdf.savefig(fig)
    plt.close(fig)


def add_review_suspension_page(pdf, review: dict[str, Any]) -> None:
    suspension = review["suspension"]
    vehicle = review["vehicle"]

    fig, ax = _make_page("Suspension & Steering", "Kinematics, anti-geometry, springs, dampers, and modal response")

    left_rows: list[MetricRow] = [
        ("Camber gain heave", suspension["camber_gain_heave_rad_per_m"], "rad/m", "{:.4f}", 1.0),
        ("Toe gain heave", suspension["toe_gain_heave_rad_per_m"], "rad/m", "{:.4f}", 1.0),
        ("Caster gain heave", suspension["caster_gain_heave_rad_per_m"], "rad/m", "{:.4f}", 1.0),
        ("KPI gain heave", suspension["kpi_gain_heave_rad_per_m"], "rad/m", "{:.4f}", 1.0),
        ("Trail gain heave", suspension["trail_gain_heave_m_per_m"], "m/m", "{:.4f}", 1.0),
        ("Scrub gain heave", suspension["scrub_gain_heave_m_per_m"], "m/m", "{:.4f}", 1.0),
        ("Camber gain roll", suspension["camber_gain_roll_rad_per_rad"], "rad/rad", "{:.4f}", 1.0),
        ("Toe gain roll", suspension["toe_gain_roll_rad_per_rad"], "rad/rad", "{:.4f}", 1.0),
        ("Caster gain roll", suspension["caster_gain_roll_rad_per_rad"], "rad/rad", "{:.4f}", 1.0),
        ("KPI gain roll", suspension["kpi_gain_roll_rad_per_rad"], "rad/rad", "{:.4f}", 1.0),
        ("Trail gain roll", suspension["trail_gain_roll_m_per_rad"], "m/rad", "{:.4f}", 1.0),
        ("Scrub gain roll", suspension["scrub_gain_roll_m_per_rad"], "m/rad", "{:.4f}", 1.0),
        ("Anti-dive", suspension["avg_anti_dive_pct"], "%", "{:.1f}", 1.0),
        ("Anti-squat", suspension["avg_anti_squat_pct"], "%", "{:.1f}", 1.0),
        ("Front anti-roll", suspension["avg_anti_roll_front_pct"], "%", "{:.1f}", 1.0),
        ("Rear anti-roll", suspension["avg_anti_roll_rear_pct"], "%", "{:.1f}", 1.0),
        ("Front jacking coeff", suspension["avg_lateral_jacking_coeff_front"], "-", "{:.3e}", 1.0),
        ("Rear jacking coeff", suspension["avg_lateral_jacking_coeff_rear"], "-", "{:.3e}", 1.0),
        ("Body torsional stiffness", vehicle["body_torsional_stiffness_n_m_per_rad"], "N·m/rad", "{:.0f}", 1.0),
    ]

    right_rows: list[MetricRow] = [
        ("Front motion ratio", suspension["avg_motion_ratio_front"], "-", "{:.3f}", 1.0),
        ("Rear motion ratio", suspension["avg_motion_ratio_rear"], "-", "{:.3f}", 1.0),
        ("Front bar motion ratio", suspension["avg_stabar_motion_ratio_front"], "-", "{:.3f}", 1.0),
        ("Rear bar motion ratio", suspension["avg_stabar_motion_ratio_rear"], "-", "{:.3f}", 1.0),
        ("Front spring rate", suspension["front_spring_rate_n_per_m"], "N/m", "{:.0f}", 1.0),
        ("Rear spring rate", suspension["rear_spring_rate_n_per_m"], "N/m", "{:.0f}", 1.0),
        ("Front wheel rate", suspension["front_wheel_rate_n_per_m"], "N/m", "{:.0f}", 1.0),
        ("Rear wheel rate", suspension["rear_wheel_rate_n_per_m"], "N/m", "{:.0f}", 1.0),
        ("Front damper rate", suspension["front_damper_rate_n_s_per_m"], "N·s/m", "{:.0f}", 1.0),
        ("Rear damper rate", suspension["rear_damper_rate_n_s_per_m"], "N·s/m", "{:.0f}", 1.0),
        ("Front sprung freq", suspension["front_sprung_freq_hz"], "Hz", "{:.2f}", 1.0),
        ("Rear sprung freq", suspension["rear_sprung_freq_hz"], "Hz", "{:.2f}", 1.0),
        ("Front unsprung freq", suspension["front_unsprung_freq_hz"], "Hz", "{:.2f}", 1.0),
        ("Rear unsprung freq", suspension["rear_unsprung_freq_hz"], "Hz", "{:.2f}", 1.0),
        ("Front sprung damping", suspension["front_sprung_zeta"], "-", "{:.2f}", 1.0),
        ("Rear sprung damping", suspension["rear_sprung_zeta"], "-", "{:.2f}", 1.0),
        ("Front unsprung damping", suspension["front_unsprung_zeta"], "-", "{:.2f}", 1.0),
        ("Rear unsprung damping", suspension["rear_unsprung_zeta"], "-", "{:.2f}", 1.0),
        ("Front compression", suspension["front_spring_compression_m"], "mm", "{:.1f}", 1000.0),
        ("Rear compression", suspension["rear_spring_compression_m"], "mm", "{:.1f}", 1000.0),
        ("Front free length", suspension["front_spring_free_length_m"], "mm", "{:.1f}", 1000.0),
        ("Rear free length", suspension["rear_spring_free_length_m"], "mm", "{:.1f}", 1000.0),
        ("Rack travel / rev", suspension["rack_travel_per_rev_m"], "m/rev", "{:.4f}", 1.0),
    ]

    _draw_section(ax, 0.05, 0.47, 0.82, "Kinematics & Anti-Geometry", left_rows, row_step=0.031)
    _draw_section(ax, 0.53, 0.95, 0.82, "Springs, Dampers, and Modes", right_rows, row_step=0.028)

    pdf.savefig(fig)
    plt.close(fig)


def add_review_performance_page(pdf, review: dict[str, Any]) -> None:
    performance = review["performance"]
    ggv = review["ggv"]
    ymd = review["ymd"]

    subtitle = "Steady-state, transient, GGV, and YMD correlation"
    fig, ax = _make_page("Performance & Correlation", subtitle)

    left_rows: list[MetricRow] = [
        ("Roadwheel angle gradient", performance["roadwheel_angle_gradient_deg_per_g"], "deg/g", "{:.3f}", 1.0),
        ("Handwheel angle gradient", performance["handwheel_angle_gradient_deg_per_g"], "deg/g", "{:.3f}", 1.0),
        ("Sideslip gradient", performance["sideslip_gradient_deg_per_g"], "deg/g", "{:.3f}", 1.0),
        ("Understeer gradient", performance["understeer_gradient_deg_per_g"], "deg/g", "{:.3f}", 1.0),
        ("Roll gradient", performance["roll_gradient_deg_per_g"], "deg/g", "{:.3f}", 1.0),
        ("Handwheel torque min", performance["handwheel_torque_min_nm"], "N·m", "{:.1f}", 1.0),
        ("Handwheel torque max", performance["handwheel_torque_max_nm"], "N·m", "{:.1f}", 1.0),
        (
            "Roadwheel gradient slope",
            performance["roadwheel_angle_gradient_velocity_slope_deg_per_g_per_mps"],
            "deg/g per m/s",
            "{:.3f}",
            1.0,
        ),
        (
            "Handwheel gradient slope",
            performance["handwheel_angle_gradient_velocity_slope_deg_per_g_per_mps"],
            "deg/g per m/s",
            "{:.3f}",
            1.0,
        ),
        ("Steer-to-ay lag @ 0.5 Hz", performance["lag_steer_to_ay_s"], "s", "{:.4f}", 1.0),
        ("Steer-to-yaw lag @ 0.5 Hz", performance["lag_steer_to_yaw_s"], "s", "{:.4f}", 1.0),
        ("Step ay peak", performance["step_ay_peak_mps2"], "m/s^2", "{:.3f}", 1.0),
        ("Step ay rise time", performance["step_ay_rise_time_s"], "s", "{:.3f}", 1.0),
        ("Step yaw overshoot", performance["step_yaw_overshoot_pct"], "%", "{:.1f}", 1.0),
        ("Step roll peak", performance["step_roll_peak_rad"], "rad", "{:.4f}", 1.0),
        ("Step roll overshoot", performance["step_roll_overshoot_pct"], "%", "{:.1f}", 1.0),
        ("Step settling time", performance["step_settling_time_s"], "s", "{:.3f}", 1.0),
        ("Bandwidth", performance["frequency_bandwidth_hz"], "Hz", "{:.2f}", 1.0),
    ]

    right_rows: list[MetricRow] = []
    for item in ggv["by_speed"]:
        right_rows.append(
            (
                f"GGV @ {item['speed_mps']:.0f} m/s",
                f"{item['max_abs_ay_g']:.3f} g | {item['max_accel_g']:.3f} / {item['max_brake_g']:.3f}",
                "lat | accel / brake",
                "{}",
                1.0,
            )
        )

    if ymd["available"]:
        right_rows.extend(
            [
                ("YMD converged", ymd["converged_fraction"], "%", "{:.1f}", 100.0),
                ("YMD |ay| max", ymd["max_abs_ay_g"], "g", "{:.3f}", 1.0),
                ("YMD |Mz| max", ymd["max_abs_mz_nm"], "N·m", "{:.0f}", 1.0),
                ("YMD speed span", f"{ymd['speed_min_mps']:.1f} to {ymd['speed_max_mps']:.1f}", "m/s", "{}", 1.0),
            ]
        )
    else:
        right_rows.append(("YMD", "not generated yet", "", "{}", 1.0))

    _draw_section(ax, 0.05, 0.47, 0.82, "Steady-State Handling", left_rows, row_step=0.030)
    _draw_section(ax, 0.53, 0.95, 0.82, "Envelope / Response", right_rows, row_step=0.032)

    ax.text(
        0.05,
        0.075,
        (
            "Interpretation: the current setup is balanced but slightly front-biased in roll load transfer, "
            "with RWD acceleration capped by tire load sensitivity and brake balance capped by the front brake split."
        ),
        fontsize=9.4,
        color="#374151",
        va="top",
    )

    pdf.savefig(fig)
    plt.close(fig)


def add_review_coverage_page(pdf, review: dict[str, Any]) -> None:
    coverage = review["coverage_rows"]
    missing_items = review["missing_items"]

    fig, ax = _make_page("Rubric Coverage", "Each row points to the concrete data used in this report")

    rows: list[MetricRow] = []
    for row in coverage:
        rows.append(
            (
                row["section"],
                row["evidence"],
                row["status"],
                "{}",
                1.0,
            )
        )

    _draw_section(ax, 0.05, 0.95, 0.82, "Coverage Map", rows, row_step=0.040)

    _draw_bullet_block(
        ax,
        0.05,
        0.95,
        0.34,
        0.09,
        "Manual Inputs / Gaps",
        missing_items,
        width_chars=92,
        font_size=9.2,
    )

    pdf.savefig(fig)
    plt.close(fig)
