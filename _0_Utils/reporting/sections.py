from collections.abc import Mapping
from datetime import datetime
import matplotlib.pyplot as plt
import numpy as np
import textwrap
from typing import TypedDict


class FourPostCornerSummary(TypedDict):
    corner: str
    sprung_mass_kg: float
    unsprung_mass_kg: float
    sprung_load_N: float
    motion_ratio: float
    spring_rate_N_per_m: float
    spring_force_N: float
    spring_compression_m: float
    spring_installed_length_m: float
    spring_free_length_m: float
    wheel_rate_N_per_m: float
    sprung_frequency_hz: float
    unsprung_frequency_hz: float


class FourPostAxleSummary(TypedDict):
    label: str
    left: FourPostCornerSummary
    right: FourPostCornerSummary


class FourPostVehicleSummary(TypedDict):
    sprung_mass_kg: float
    sprung_cg_m: list[float]
    wheelbase_m: float
    track_front_m: float
    track_rear_m: float
    cg_bias_front_pct: float
    cg_bias_rear_pct: float
    cg_bias_left_pct: float
    cg_bias_right_pct: float


class FourPostSetup(TypedDict):
    subtitle: str
    vehicle: FourPostVehicleSummary
    front: FourPostAxleSummary
    rear: FourPostAxleSummary


def _resolve_unit(
    unit_overrides: Mapping[str, object] | None,
    key: str,
    default_unit: str,
) -> tuple[str, float]:
    if not unit_overrides or key not in unit_overrides:
        return default_unit, 1.0

    override = unit_overrides[key]
    if override is None:
        return default_unit, 1.0

    if isinstance(override, str):
        return override, 1.0

    if isinstance(override, Mapping):
        unit = override.get("unit", override.get("label", default_unit))
        scale = override.get("scale", 1.0)
        return str(unit), float(scale)

    raise TypeError(
        f"summary_units[{key!r}] must be a string or a mapping with unit/scale."
    )


def _format_table_value(value, fmt: str, scale: float = 1.0) -> str:
    if value is None:
        return "—"

    try:
        numeric = float(value)
    except (TypeError, ValueError):
        try:
            return fmt.format(value)
        except Exception:
            return str(value)

    if not np.isfinite(numeric):
        return "—"

    return fmt.format(numeric * scale)


def add_four_post_setup_page(
    pdf,
    setup: FourPostSetup,
    title="FourPostEval Setup Summary",
):
    fig = plt.figure(figsize=(11, 8.5))
    ax = plt.axes((0.0, 0.0, 1.0, 1.0))
    ax.set_xlim(0, 1)
    ax.set_ylim(0, 1)
    ax.axis("off")

    vehicle = setup["vehicle"]
    cg = vehicle["sprung_cg_m"]
    stats_line_1 = (
        f"Sprung mass {vehicle['sprung_mass_kg']:.1f} kg | "
        f"CG ({cg[0]:.3f}, {cg[1]:.3f}, {cg[2]:.3f}) m | "
        f"Wheelbase {vehicle['wheelbase_m']:.3f} m | "
        f"Track Fr/Rr {vehicle['track_front_m']:.3f} / "
        f"{vehicle['track_rear_m']:.3f} m"
    )
    stats_line_2 = (
        f"CG bias Fr/Rr {vehicle['cg_bias_front_pct']:.1f} / "
        f"{vehicle['cg_bias_rear_pct']:.1f}% | "
        f"CG bias L/R {vehicle['cg_bias_left_pct']:.1f} / "
        f"{vehicle['cg_bias_right_pct']:.1f}%"
    )

    ax.text(0.5, 0.955, title, ha="center", va="top", fontsize=20, weight="bold", color="#1f2937")
    ax.text(0.5, 0.905, stats_line_1, ha="center", va="top", fontsize=10.4, color="#3f4652")
    ax.text(0.5, 0.875, stats_line_2, ha="center", va="top", fontsize=10.1, color="#4b5563")
    ax.plot([0.08, 0.92], [0.845, 0.845], color="#d6dbe4", linewidth=1.0)

    def render_setup_block(
        x0: float,
        x1: float,
        y_top: float,
        axle: FourPostAxleSummary,
        accent: str,
    ) -> None:
        left_corner = axle["left"]
        right_corner = axle["right"]
        rows = [
            ("Sprung mass", "sprung_mass_kg", "kg", "{:.1f}", 1.0),
            ("Unsprung mass", "unsprung_mass_kg", "kg", "{:.1f}", 1.0),
            ("Sprung load", "sprung_load_N", "N", "{:.0f}", 1.0),
            ("Motion ratio", "motion_ratio", "wheel/spring", "{:.3f}", 1.0),
            ("Spring rate", "spring_rate_N_per_m", "N/m", "{:.0f}", 1.0),
            ("Spring force", "spring_force_N", "N", "{:.0f}", 1.0),
            ("Installed length", "spring_installed_length_m", "mm", "{:.1f}", 1000.0),
            ("Compression", "spring_compression_m", "mm", "{:.1f}", 1000.0),
            ("Free length", "spring_free_length_m", "mm", "{:.1f}", 1000.0),
            ("Wheel rate", "wheel_rate_N_per_m", "N/m", "{:.0f}", 1.0),
            ("Sprung freq", "sprung_frequency_hz", "Hz", "{:.2f}", 1.0),
            ("Unsprung freq", "unsprung_frequency_hz", "Hz", "{:.2f}", 1.0),
        ]

        width = x1 - x0
        x_metric = x0
        x_left = x0 + 0.40 * width
        x_right = x0 + 0.70 * width
        x_unit = x0 + 0.91 * width
        x_title = 0.5 * (x_metric + x_unit)

        ax.text(x_title, y_top, f"{axle['label']} Setup", fontsize=14, weight="bold", ha="center", color="#1f2937")
        ax.text(
            x_title,
            y_top - 0.022,
            f"{left_corner['corner']} / {right_corner['corner']}",
            fontsize=9.4,
            ha="center",
            style="italic",
            color="#5d6571",
        )

        header_y = y_top - 0.060
        ax.text(x_metric, header_y, "Metric", fontsize=10.0, weight="bold", color="#1f2937")
        ax.text(x_left, header_y, left_corner["corner"], fontsize=10.0, weight="bold", ha="right", color="#1f2937")
        ax.text(x_right, header_y, right_corner["corner"], fontsize=10.0, weight="bold", ha="right", color="#1f2937")
        ax.text(x_unit, header_y, "Units", fontsize=10.0, weight="bold", color="#1f2937")
        ax.plot([x_metric, x_unit + 0.01], [header_y - 0.015, header_y - 0.015], color="#c8cfdb", linewidth=1.0)

        row_y = header_y - 0.040
        row_step = 0.050
        for i, (label, key, unit, fmt, scale) in enumerate(rows):
            yy = row_y - i * row_step
            left_val = left_corner.get(key)
            right_val = right_corner.get(key)
            label_color = "#20242b"
            value_color = "#111827"

            ax.text(x_metric, yy, label, fontsize=9.0, color=label_color)
            ax.text(x_left, yy, _format_table_value(left_val, fmt, scale), fontsize=9.0, ha="right", color=value_color)
            ax.text(
                x_right,
                yy,
                _format_table_value(right_val, fmt, scale),
                fontsize=9.0,
                ha="right",
                color=value_color,
            )
            ax.text(x_unit, yy, unit, fontsize=9.0, color="#444b55")

    render_setup_block(0.055, 0.44, 0.75, setup["front"], accent="#1f2937")
    render_setup_block(0.56, 0.945, 0.75, setup["rear"], accent="#1f2937")

    pdf.savefig(fig)
    plt.close(fig)


def add_summary_page(pdf, summary, title=None):

    fig = plt.figure(figsize=(11, 8.5))
    plt.axis("off")

    # --- Title ---
    page_title = title or "SteadyStateEval Summary"
    velocity = summary.get("velocity_mps")
    if velocity is not None and np.isfinite(velocity):
        page_title = f"{page_title}"

    fig.text(0.5, 0.95, page_title,
             ha="center", va="top", fontsize=18, weight="bold")

    ay_min, ay_max = summary.get("MeasuredAy_range", summary.get("Ay_range"))

    rows = [
        (
            r"Measured $a_y$ Range",
            rf"${ay_min:.2f} \rightarrow {ay_max:.2f}$",
            r"$\mathrm{m/s^2}$",
        ),
        (
            "Roadwheel Angle Gradient",
            rf"${summary['roadwheel_angle_gradient_rad_per_mps2']:.5f}$",
            r"$\frac{\mathrm{rad}}{\mathrm{m/s^2}}$",
        ),
        (
            "",
            rf"${summary['roadwheel_angle_gradient_deg_per_g']:.2f}$",
            r"$\frac{\mathrm{deg}}{g}$",
        ),
        (
            "Handwheel Angle Gradient",
            rf"${summary['handwheel_angle_gradient_rad_per_mps2']:.5f}$",
            r"$\frac{\mathrm{rad}}{\mathrm{m/s^2}}$",
        ),
        (
            "",
            rf"${summary['handwheel_angle_gradient_deg_per_g']:.2f}$",
            r"$\frac{\mathrm{deg}}{g}$",
        ),
        (
            "Sideslip Gradient",
            rf"${summary['sideslip_gradient_rad_per_mps2']:.5f}$",
            r"$\frac{\mathrm{rad}}{\mathrm{m/s^2}}$",
        ),
        (
            "",
            rf"${summary['sideslip_gradient_deg_per_g']:.2f}$",
            r"$\frac{\mathrm{deg}}{g}$",
        ),
        (
            "Understeer Gradient",
            rf"${summary['understeer_gradient_rad_per_mps2']:.5f}$",
            r"$\frac{\mathrm{rad}}{\mathrm{m/s^2}}$",
        ),
        (
            "",
            rf"${summary['understeer_gradient_deg_per_g']:.2f}$",
            r"$\frac{\mathrm{deg}}{g}$",
        ),
        (
            "Handwheel Understeer Gradient",
            rf"${summary['handwheel_understeer_gradient_rad_per_mps2']:.5f}$",
            r"$\frac{\mathrm{rad}}{\mathrm{m/s^2}}$",
        ),
        (
            "",
            rf"${summary['handwheel_understeer_gradient_deg_per_g']:.2f}$",
            r"$\frac{\mathrm{deg}}{g}$",
        ),
        (
            "Roll Gradient",
            rf"${summary['roll_gradient_deg_per_g']:.3f}$",
            r"$\frac{\mathrm{deg}}{g}$",
        ),
        (
            "Handwheel Torque Min",
            rf"${summary['handwheel_torque_min_Nm']:.1f}$",
            r"$\mathrm{N\cdot m}$",
        ),
        (
            "Handwheel Torque Max",
            rf"${summary['handwheel_torque_max_Nm']:.1f}$",
            r"$\mathrm{N\cdot m}$",
        ),
    ]

    # --- column positions ---
    x_metric = 0.2
    x_value = 0.65
    x_units = 0.82

    y_top = 0.72
    row_h = 0.048

    # --- header ---
    plt.text(x_metric, y_top, "Metric", fontsize=13, weight="bold")
    plt.text(x_value, y_top, "Value", fontsize=13, weight="bold", ha="right")
    plt.text(x_units, y_top, "Units", fontsize=13, weight="bold")

    # header line
    plt.plot([0.18, 0.9], [y_top - 0.02, y_top - 0.02],
             color="black", linewidth=1.5)

    # --- rows ---
    for i, (metric, value, units) in enumerate(rows):
        y = y_top - (i + 1) * row_h

        plt.text(x_metric, y, metric, fontsize=12)
        plt.text(x_value, y, value, fontsize=12, ha="right")
        plt.text(x_units, y, units, fontsize=12)

    # bottom line
    plt.plot([0.18, 0.9],
             [y_top - (len(rows)+1)*row_h + 0.02,
              y_top - (len(rows)+1)*row_h + 0.02],
             color="black", linewidth=1)

    pdf.savefig(fig)
    plt.close(fig)


def add_knc_summary_page(
    pdf,
    summary,
    title="KnC Metrics Summary",
    unit_overrides: Mapping[str, object] | None = None,
):

    import matplotlib.pyplot as plt

    fig = plt.figure(figsize=(11, 8.5))
    plt.axis("off")

    # Title
    plt.text(0.5, 0.96, title,
             ha="center", fontsize=18, weight="bold")

    # Column anchors
    x_left_label  = 0.03
    x_left_val    = 0.25
    x_left_unit   = 0.36

    x_right_label = 0.54
    x_right_val   = 0.76
    x_right_unit  = 0.87

    y_top = 0.88

    def add_section(x_label, x_val, x_unit, y, title, rows):
        x_title = 0.5 * (x_label + x_unit)
        plt.text(x_title, y, title, fontsize=13, weight="bold", ha="center")
        y -= 0.045

        for label, key, unit, fmt in rows:
            val = summary.get(key, None)
            unit, scale = _resolve_unit(unit_overrides, key, unit)
            if val is None:
                val_str = "—"
            else:
                try:
                    val_str = fmt.format(float(val) * scale)
                except (TypeError, ValueError):
                    val_str = fmt.format(val)

            plt.text(x_label, y, label, fontsize=11)
            plt.text(x_val, y, val_str, fontsize=11, ha="right")
            plt.text(x_unit, y, unit, fontsize=11)

            y -= 0.035

        return y - 0.04

    # ============================================================
    # LEFT COLUMN
    # ============================================================
    y_left = y_top

    # --------------------------
    # HEAVE GAINS
    # --------------------------
    y_left = add_section(x_left_label, x_left_val, x_left_unit, y_left,
        "Heave Gains", [
            ("Camber", "camber_gain_heave_rad_per_m", "rad/m", "{:.4f}"),
            ("Toe", "toe_gain_heave_rad_per_m", "rad/m", "{:.4f}"),
            ("Caster", "caster_gain_heave_rad_per_m", "rad/m", "{:.4f}"),
            ("KPI", "kpi_gain_heave_rad_per_m", "rad/m", "{:.4f}"),
            ("Trail", "trail_gain_heave_m_per_m", "m/m", "{:.4f}"),
            ("Scrub", "scrub_gain_heave_m_per_m", "m/m", "{:.4f}"),
        ])

    # --------------------------
    # ANTI METRICS
    # --------------------------
    y_left = add_section(x_left_label, x_left_val, x_left_unit, y_left,
        "Anti Metrics", [
            ("Anti-Dive", "avg_anti_dive_pct", "%", "{:.1f}"),
            ("Anti-Squat", "avg_anti_squat_pct", "%", "{:.1f}"),
            ("Front Anti-Roll", "avg_anti_roll_front_pct", "%", "{:.1f}"),
            ("Rear Anti-Roll", "avg_anti_roll_rear_pct", "%", "{:.1f}"),
            ("LLTD (Front)", "avg_lltd_front_pct", "%", "{:.1f}"),
        ])

    # ============================================================
    # RIGHT COLUMN
    # ============================================================
    y_right = y_top

    # --------------------------
    # ROLL GAINS (NOW FULLY SYMMETRIC)
    # --------------------------
    y_right = add_section(x_right_label, x_right_val, x_right_unit, y_right,
        "Roll Gains", [
            ("Camber", "camber_gain_roll_rad_per_rad", "rad/rad", "{:.4f}"),
            ("Toe", "toe_gain_roll_rad_per_rad", "rad/rad", "{:.4f}"),
            ("Caster", "caster_gain_roll_rad_per_rad", "rad/rad", "{:.4f}"),
            ("KPI", "kpi_gain_roll_rad_per_rad", "rad/rad", "{:.4f}"),
            ("Trail", "trail_gain_roll_m_per_rad", "m/rad", "{:.4f}"),
            ("Scrub", "scrub_gain_roll_m_per_rad", "m/rad", "{:.4f}"),
        ])

    # --------------------------
    # MOTION RATIOS
    # --------------------------
    y_right = add_section(x_right_label, x_right_val, x_right_unit, y_right,
        "Motion Ratios", [
            ("Front MR", "avg_motion_ratio_front", "-", "{:.3f}"),
            ("Rear MR", "avg_motion_ratio_rear", "-", "{:.3f}"),
            ("Front Bar MR", "avg_stabar_motion_ratio_front", "-", "{:.3f}"),
            ("Rear Bar MR", "avg_stabar_motion_ratio_rear", "-", "{:.3f}"),
        ])

    # --------------------------
    # ROLL STIFFNESS
    # --------------------------
    y_right = add_section(x_right_label, x_right_val, x_right_unit, y_right,
        "Roll Stiffness", [
            ("Spring Front", "spring_roll_stiffness_front_Nm_per_rad", "Nm/rad", "{:.0f}"),
            ("Spring Rear", "spring_roll_stiffness_rear_Nm_per_rad", "Nm/rad", "{:.0f}"),
            ("ARB Front", "arb_roll_stiffness_front_Nm_per_rad", "Nm/rad", "{:.0f}"),
            ("ARB Rear", "arb_roll_stiffness_rear_Nm_per_rad", "Nm/rad", "{:.0f}"),
            ("Total Front", "elastic_roll_stiffness_front_Nm_per_rad", "Nm/rad", "{:.0f}"),
            ("Total Rear", "elastic_roll_stiffness_rear_Nm_per_rad", "Nm/rad", "{:.0f}"),
        ])

    pdf.savefig(fig)
    plt.close(fig)


def add_transient_eval_step_page(pdf, summary):
    import matplotlib.pyplot as plt

    fig = plt.figure(figsize=(11, 8.5))
    plt.axis("off")

    velocity = summary.get("velocity_mps")
    page_title = "TransientEval Metrics Summary"
    if velocity is not None and np.isfinite(velocity):
        page_title = f"{page_title} {velocity:.1f} m/s"

    plt.text(
        0.5,
        0.94,
        page_title,
        ha="center",
        fontsize=18,
        weight="bold",
    )
    plt.text(
        0.5,
        0.90,
        "Time Domain - Step Response",
        ha="center",
        fontsize=13,
    )

    left_rows = [
        ("STEP RESPONSE", "", "", ""),
        ("a_y Rise Time (50-90%)", "ay_rise_time_s", "s", "{:.2f}"),
        ("Sideslip Rise Time (50-90%)", "sideslip_rise_time_s", "s", "{:.2f}"),
        ("Yaw Rise Time (50-90%)", "yaw_rise_time_s", "s", "{:.2f}"),
        ("Yaw Peak Response Time", "yaw_peak_response_time_s", "s", "{:.2f}"),
        ("a_y DC Gain", "ay_gain_dc", r"$\frac{\mathrm{m/s^2}}{\mathrm{rad}}$", "{:.2f}"),
        ("Sideslip DC Gain", "sideslip_gain_dc", "rad/rad", "{:.3f}"),
        ("Yaw DC Gain", "yaw_gain_dc", "(rad/s)/rad", "{:.2f}"),
        ("Roll DC Gain", "roll_gain_dc", "rad/rad", "{:.3f}"),
    ]

    right_rows = [
        ("STEADY-STATE / OVERSHOOT", "", "", ""),
        ("a_y Peak", "ay_peak", r"$\mathrm{m/s^2}$", "{:.2f}"),
        ("a_y Steady-State", "ay_ss", r"$\mathrm{m/s^2}$", "{:.2f}"),
        ("a_y Overshoot", "ay_overshoot_pct", "%", "{:.1f}"),
        ("Yaw Steady-State", "yaw_ss", "rad/s", "{:.3f}"),
        ("Yaw Overshoot", "yaw_overshoot_rad_per_s", "rad/s", "{:.3f}"),
        ("Roll Steady-State", "roll_ss", "rad", "{:.3f}"),
        ("Roll Overshoot", "roll_overshoot_rad", "rad", "{:.3f}"),
        ("Settling Time", "settling_time_s", "s", "{:.2f}"),
    ]

    x_left_label = 0.07
    x_left_val = 0.36
    x_left_unit = 0.45
    x_right_label = 0.66
    x_right_val = 0.92
    x_right_unit = 0.98
    y_top = 0.82
    row_h = 0.048

    def render_column(rows, x_label, x_val, x_unit):
        for i, (label, key, unit, fmt) in enumerate(rows):
            y = y_top - i * row_h

            if key == "" and label:
                plt.text(x_label, y, label, fontsize=13, weight="bold")
                continue

            val = summary.get(key, None)
            val_str = "—" if val is None or (isinstance(val, float) and np.isnan(val)) else fmt.format(val)

            plt.text(x_label, y, label, fontsize=11)
            plt.text(x_val, y, val_str, fontsize=11, ha="right")
            plt.text(x_unit, y, unit, fontsize=11)

    render_column(left_rows, x_left_label, x_left_val, x_left_unit)
    render_column(right_rows, x_right_label, x_right_val, x_right_unit)

    pdf.savefig(fig)
    plt.close(fig)


def add_transient_eval_frequency_page(pdf, summary):
    import matplotlib.pyplot as plt

    fig = plt.figure(figsize=(11, 8.5))
    plt.axis("off")

    velocity = summary.get("velocity_mps")
    page_title = "TransientEval Metrics Summary"
    if velocity is not None and np.isfinite(velocity):
        page_title = f"{page_title} {velocity:.1f} m/s"

    plt.text(
        0.5,
        0.94,
        page_title,
        ha="center",
        fontsize=18,
        weight="bold",
    )
    plt.text(
        0.5,
        0.90,
        "Frequency Domain - Sustained Sine",
        ha="center",
        fontsize=13,
    )

    left_rows = [
        ("FREQUENCY RESPONSE - CORE", "", "", ""),
        ("DC Gain (a_y)", "ay_gain_dc", r"$\frac{\mathrm{m/s^2}}{\mathrm{rad}}$", "{:.2f}"),
        ("DC Gain (r)", "yaw_gain_dc", "(rad/s)/rad", "{:.2f}"),
        ("Peak Gain (a_y)", "ay_gain_peak", r"$\frac{\mathrm{m/s^2}}{\mathrm{rad}}$", "{:.2f}"),
        ("Peak Freq (a_y)", "ay_gain_peak_freq", "Hz", "{:.2f}"),
        ("Bandwidth (-3 dB)", "bandwidth_hz", "Hz", "{:.2f}"),
        ("Gain Slope (a_y)", "ay_gain_slope", "dB/dec", "{:.2f}"),
        ("Gain Slope (r)", "yaw_gain_slope", "dB/dec", "{:.2f}"),
        ("Phase Slope (a_y)", "ay_phase_slope", "deg/dec", "{:.2f}"),
        ("Phase Slope (r)", "yaw_phase_slope", "deg/dec", "{:.2f}"),
    ]

    right_rows = [
        ("DELAY / COUPLING", "", "", ""),
        ("Ay/Yaw Delay @ 0.5 Hz", "ay_lag_0p5hz", "s", "{:.3f}"),
        ("Yaw/Steer Delay @ 0.5 Hz", "yaw_lag_0p5hz", "s", "{:.3f}"),
        ("Difference @ 0.5 Hz", "yaw_to_ay_lag_0p5hz", "s", "{:.3f}"),
        ("Ay/Yaw Delay @ 1.0 Hz", "ay_lag_1hz", "s", "{:.3f}"),
        ("Yaw/Steer Delay @ 1.0 Hz", "yaw_lag_1hz", "s", "{:.3f}"),
        ("Difference @ 1.0 Hz", "yaw_to_ay_lag_1hz", "s", "{:.3f}"),
        ("Gain Variation", "gain_variation_pct", "%", "{:.1f}"),
        ("Fit Error (a_y)", "ay_fit_error", "-", "{:.2e}"),
        ("Fit Error (r)", "yaw_fit_error", "-", "{:.2e}"),
    ]

    x_left_label = 0.05
    x_left_val = 0.30
    x_left_unit = 0.39
    x_right_label = 0.58
    x_right_val = 0.84
    x_right_unit = 0.92
    y_top = 0.82
    row_h = 0.042

    def render_column(rows, x_label, x_val, x_unit):
        for i, (label, key, unit, fmt) in enumerate(rows):
            y = y_top - i * row_h

            if key == "" and label:
                plt.text(x_label, y, label, fontsize=13, weight="bold")
                continue

            val = summary.get(key, None)
            val_str = "—" if val is None or (isinstance(val, float) and np.isnan(val)) else fmt.format(val)

            plt.text(x_label, y, label, fontsize=11)
            plt.text(x_val, y, val_str, fontsize=11, ha="right")
            plt.text(x_unit, y, unit, fontsize=11)

    render_column(left_rows, x_left_label, x_left_val, x_left_unit)
    render_column(right_rows, x_right_label, x_right_val, x_right_unit)

    pdf.savefig(fig)
    plt.close(fig)


def add_title_page(pdf, config):
    fig, ax = plt.subplots(figsize=(11, 8.5))
    ax.set_frame_on(False)
    ax.set_xticks([])
    ax.set_yticks([])

    report_cfg = config.get("report", {})

    brand = report_cfg.get("brand", "BobDyn")
    title = report_cfg.get("title", "Vehicle Characterization Report")
    subtitle = report_cfg.get("subtitle", "")

    now = datetime.now().strftime("%Y-%m-%d %H:%M")

    # ============================================================
    # LOGO
    # ============================================================
    logo = plt.imread("_0_Utils/reporting/media/bob.png")

    ax_logo = fig.add_axes([0.03, 0.72, 0.22, 0.19])
    ax_logo.imshow(logo, alpha=0.8)
    ax_logo.axis("off")

    ax_logo.set_zorder(0)
    ax.set_zorder(1)

    # ============================================================
    # MAIN TEXT
    # ============================================================
    ax.text(
        0.5,
        0.80,
        brand,
        ha="center",
        fontsize=24,
        weight="bold",
    )

    ax.text(
        0.5,
        0.65,
        title,
        ha="center",
        fontsize=20,
        weight="bold",
    )

    if subtitle:
        subtitle_wrapped = "\n".join(
            textwrap.wrap(str(subtitle), width=92)
        )
        ax.text(
            0.5,
            0.57,
            subtitle_wrapped,
            ha="center",
            va="center",
            fontsize=13,
            alpha=0.9,
        )

    ax.text(
        0.5,
        0.46,
        f"Generated: {now}",
        ha="center",
        fontsize=11,
        alpha=0.85,
    )

    # ============================================================
    # NOTES PANEL
    # ============================================================
    notes = report_cfg.get("notes", [])
    footer = report_cfg.get("footer", "")

    clean_notes = []
    for note in notes:
        if isinstance(note, dict):
            k, v = list(note.items())[0]
            clean_notes.append(f"{k}: {v}")
        else:
            clean_notes.append(str(note))

    if not clean_notes and footer:
        clean_notes = [str(footer)]

    panel_left = 0.07
    panel_right = 0.93
    panel_top = 0.38
    panel_bottom = 0.13

    # Panel title
    fig.text(
        panel_left,
        panel_top + 0.025,
        "Run Notes",
        ha="left",
        fontsize=11,
        weight="bold",
        alpha=0.9,
    )

    # Divider above notes
    fig.lines.append(
        plt.Line2D(
            [panel_left, panel_right],
            [panel_top + 0.012, panel_top + 0.012],
            transform=fig.transFigure,
            color="black",
            linewidth=0.6,
            alpha=0.45,
        )
    )

    # Two-column wrapped notes
    if clean_notes:
        col_x = [panel_left, 0.52]
        col_width_chars = 48
        line_spacing = 0.019
        paragraph_gap = 0.0
        font_size = 8.0

        usable_height = panel_top - panel_bottom
        max_lines_per_col = int(usable_height / line_spacing)

        wrapped_blocks = []
        for note in clean_notes:
            wrapped = textwrap.wrap(
                note,
                width=col_width_chars,
                break_long_words=False,
                break_on_hyphens=False,
            )
            if not wrapped:
                wrapped = [""]
            wrapped_blocks.append(wrapped)

        # Fill column 1 first, then column 2.
        col = 0
        line_in_col = 0

        for block in wrapped_blocks:
            block_height = len(block) + 1

            if line_in_col + block_height > max_lines_per_col and col == 0:
                col = 1
                line_in_col = 0

            if col > 1:
                break

            # If even column 2 is full, stop cleanly.
            if line_in_col >= max_lines_per_col:
                break

            for j, line in enumerate(block):
                if line_in_col >= max_lines_per_col:
                    break

                prefix = "– " if j == 0 else "  "
                fig.text(
                    col_x[col],
                    panel_top - line_in_col * line_spacing,
                    f"{prefix}{line}",
                    ha="left",
                    va="top",
                    fontsize=font_size,
                    alpha=0.82,
                )
                line_in_col += 1

            line_in_col += int(round(paragraph_gap / line_spacing))

    # ============================================================
    # BOTTOM DIVIDER
    # ============================================================
    divider_y = 0.075

    fig.lines.append(
        plt.Line2D(
            [0.05, 0.95],
            [divider_y, divider_y],
            transform=fig.transFigure,
            color="black",
            linewidth=0.6,
            alpha=0.5,
        )
    )

    # ============================================================
    # BOBDYN FOOTER
    # ============================================================
    fig.text(
        0.94,
        divider_y + 0.018,
        "BobDyn",
        ha="right",
        fontsize=11,
        weight="bold",
        alpha=0.85,
    )

    pdf.savefig(fig)
    plt.close(fig)
