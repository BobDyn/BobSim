from datetime import datetime
import matplotlib.pyplot as plt
import numpy as np


def add_summary_page(pdf, summary):

    fig = plt.figure(figsize=(11, 8.5))
    plt.axis("off")

    # --- Title ---
    plt.text(0.5, 0.85, "ISO4138 Summary",
             ha="center", fontsize=18, weight="bold")

    ay_min, ay_max = summary["Ay_range"]

    rows = [
        (
            r"$a_y$ Range",
            rf"${ay_min:.2f} \rightarrow {ay_max:.2f}$",
            r"$\mathrm{m/s^2}$",
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
            "Roll Gradient",
            rf"${summary['roll_gradient_deg_per_g']:.3f}$",
            r"$\frac{\mathrm{deg}}{g}$",
        ),
        (
            "Max Radius Error",
            rf"${summary['max_radius_error_pct']:.2f}$",
            r"$\%$",
        ),
    ]

    # --- column positions ---
    x_metric = 0.2
    x_value = 0.65
    x_units = 0.82

    y_top = 0.7
    row_h = 0.07

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


def add_knc_summary_page(pdf, summary):

    import matplotlib.pyplot as plt

    fig = plt.figure(figsize=(11, 8.5))
    plt.axis("off")

    # Title
    plt.text(0.5, 0.96, "KnC Metrics Summary",
             ha="center", fontsize=18, weight="bold")

    # Column anchors
    x_left_label  = 0.10
    x_left_val    = 0.38
    x_left_unit   = 0.46

    x_right_label = 0.58
    x_right_val   = 0.82
    x_right_unit  = 0.90

    y_top = 0.88

    def add_section(x_label, x_val, x_unit, y, title, rows):
        plt.text(x_label, y, title, fontsize=13, weight="bold")
        y -= 0.045

        for label, key, unit, fmt in rows:
            val = summary.get(key, None)
            val_str = "—" if val is None else fmt.format(val)

            plt.text(x_label, y, label, fontsize=11)
            plt.text(x_val, y, val_str, fontsize=11)
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
    # ANTI & BALANCE
    # --------------------------
    y_left = add_section(x_left_label, x_left_val, x_left_unit, y_left,
        "Anti & Balance", [
            ("Anti-Dive", "avg_anti_dive_pct", "%", "{:.1f}"),
            ("Anti-Squat", "avg_anti_squat_pct", "%", "{:.1f}"),
            ("Front Anti-Roll", "avg_anti_roll_front_pct", "%", "{:.1f}"),
            ("Rear Anti-Roll", "avg_anti_roll_rear_pct", "%", "{:.1f}"),
            ("Anti Balance (F/R)", "avg_anti_balance", "-", "{:.2f}"),
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


def add_iso7401_step_page(pdf, summary):

    import matplotlib.pyplot as plt

    fig = plt.figure(figsize=(11, 8.5))
    plt.axis("off")

    # ============================================================
    # TITLE
    # ============================================================

    plt.text(0.5, 0.94, "ISO7401 Metrics Summary",
             ha="center", fontsize=18, weight="bold")

    plt.text(0.5, 0.90, "Time Domain — Step Response",
             ha="center", fontsize=13)

    # ============================================================
    # ROW DEFINITIONS
    # ============================================================

    rows = [

        ("STEP RESPONSE", "", "", ""),

        ("Peak $a_y$", "ay_peak", "m/s²", "{:.2f}"),
        ("Steady-State $a_y$", "ay_ss", "m/s²", "{:.2f}"),
        ("Steady-State Gain", "ay_gain_ss", "(m/s²)/rad", "{:.2f}"),
        ("Overshoot ($a_y$)", "overshoot_pct", "%", "{:.1f}"),
        ("Rise Time (10–90%)", "rise_time_s", "s", "{:.2f}"),
        ("Settling Time", "settling_time_s", "s", "{:.2f}"),

        ("Yaw Overshoot", "yaw_overshoot_pct", "%", "{:.1f}"),
    ]

    # ============================================================
    # LAYOUT
    # ============================================================

    x_label = 0.18
    x_val   = 0.70
    x_unit  = 0.86

    y_top = 0.82
    row_h = 0.055

    for i, (label, key, unit, fmt) in enumerate(rows):
        y = y_top - i * row_h

        if key == "" and label != "":
            plt.text(x_label, y, label,
                     fontsize=13, weight="bold")
            continue

        val = summary.get(key, None)
        val_str = "—" if val is None or (isinstance(val, float) and np.isnan(val)) else fmt.format(val)

        plt.text(x_label, y, label, fontsize=11)
        plt.text(x_val, y, val_str, fontsize=11, ha="right")
        plt.text(x_unit, y, unit, fontsize=11)

    pdf.savefig(fig)
    plt.close(fig)


def add_iso7401_frequency_page(pdf, summary):

    import matplotlib.pyplot as plt

    fig = plt.figure(figsize=(11, 8.5))
    plt.axis("off")

    # ============================================================
    # TITLE
    # ============================================================

    plt.text(0.5, 0.94, "ISO7401 Metrics Summary",
             ha="center", fontsize=18, weight="bold")

    plt.text(0.5, 0.90, "Frequency Domain — Sustained Sine",
             ha="center", fontsize=13)

    # ============================================================
    # ROWS (split into two columns)
    # ============================================================

    left_rows = [

        ("FREQUENCY RESPONSE — CORE", "", "", ""),

        ("DC Gain ($a_y/\\delta_H$)", "ay_gain_dc", "(m/s²)/rad", "{:.2f}"),
        ("DC Gain ($r/\\delta_H$)", "yaw_gain_dc", "(rad/s)/rad", "{:.2f}"),

        ("Peak Gain ($a_y$)", "ay_gain_peak", "(m/s²)/rad", "{:.2f}"),
        ("Peak Freq ($a_y$)", "ay_gain_peak_freq", "Hz", "{:.2f}"),

        ("Bandwidth (-3 dB)", "bandwidth_hz", "Hz", "{:.2f}"),

        ("Phase @ 1 Hz ($a_y$)", "ay_phase_1hz", "deg", "{:.1f}"),
        ("Phase @ 1 Hz ($r$)", "yaw_phase_1hz", "deg", "{:.1f}"),

        ("Lag @ 1 Hz ($a_y$)", "ay_lag_1hz", "s", "{:.3f}"),
        ("Lag @ 1 Hz ($r$)", "yaw_lag_1hz", "s", "{:.3f}"),
    ]

    right_rows = [

        ("DYNAMIC CHARACTER", "", "", ""),

        ("Gain Slope ($a_y$)", "ay_gain_slope", "dB/dec", "{:.2f}"),
        ("Gain Slope ($r$)", "yaw_gain_slope", "dB/dec", "{:.2f}"),

        ("Phase Slope ($a_y$)", "ay_phase_slope", "deg/Hz", "{:.2f}"),
        ("Phase Slope ($r$)", "yaw_phase_slope", "deg/Hz", "{:.2f}"),

        ("Phase = -45° ($a_y$)", "ay_phase_45_freq", "Hz", "{:.2f}"),
        ("Phase = -45° ($r$)", "yaw_phase_45_freq", "Hz", "{:.2f}"),

        ("", "", "", ""),

        ("RESPONSE COUPLING", "", "", ""),

        ("Lag: $\\delta_H \\rightarrow a_y$", "ay_lag_1hz", "s", "{:.3f}"),
        ("Lag: $\\delta_H \\rightarrow r$", "yaw_lag_1hz", "s", "{:.3f}"),
        ("Lag: $r \\rightarrow a_y$", "yaw_to_ay_lag", "s", "{:.3f}"),

        ("$r/a_y$ Ratio", "yaw_to_ay_ratio", "(rad/s)/(m/s²)", "{:.3f}"),

        ("", "", "", ""),

        ("QUALITY / VALIDITY", "", "", ""),

        ("$a_y$ Fit Error", "ay_fit_error", "-", "{:.2e}"),
        ("Yaw Fit Error", "yaw_fit_error", "-", "{:.2e}"),

        ("Gain Variation", "gain_variation_pct", "%", "{:.1f}"),
    ]

    # ============================================================
    # LAYOUT
    # ============================================================

    # LEFT COLUMN
    x_left_label  = 0.05   # was 0.08
    x_left_val    = 0.32   # was 0.36
    x_left_unit   = 0.38   # was 0.42

    # RIGHT COLUMN
    x_right_label = 0.55   # was 0.60
    x_right_val   = 0.82   # was 0.88
    x_right_unit  = 0.88   # was 0.94

    y_top = 0.82
    row_h = 0.045

    def render_column(rows, x_label, x_val, x_unit):
        for i, (label, key, unit, fmt) in enumerate(rows):
            y = y_top - i * row_h

            if key == "" and label != "":
                plt.text(x_label, y, label, fontsize=13, weight="bold")
                continue

            if label == "":
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

    ax_logo = fig.add_axes([0.0, 0.74, 0.28, 0.20])
    ax_logo.imshow(logo, alpha=0.8)
    ax_logo.axis("off")

    ax_logo.set_zorder(0)
    ax.set_zorder(1)

    # ============================================================
    # MAIN TEXT
    # ============================================================
    ax.text(0.5, 0.80, brand,
            ha="center", fontsize=24, weight="bold")

    ax.text(0.5, 0.64, title,
            ha="center", fontsize=20, weight="bold")

    if subtitle:
        ax.text(0.5, 0.57, subtitle,
                ha="center", fontsize=14)

    ax.text(0.5, 0.40,
            f"Generated: {now}",
            ha="center", fontsize=12)

    # ============================================================
    # BOTTOM DIVIDER
    # ============================================================
    divider_y = 0.14

    fig.lines.append(
        plt.Line2D(
            [0.05, 0.95], [divider_y, divider_y],
            transform=fig.transFigure,
            color="black",
            linewidth=0.6,
            alpha=0.5,
        )
    )

    # ============================================================
    # BOBDYN (BOTTOM RIGHT, ABOVE DIVIDER)
    # ============================================================
    fig.text(
        0.94, divider_y + 0.015,
        "BobDyn",
        ha="right",
        fontsize=11,
        weight="bold",
        alpha=0.85,
    )

    # ============================================================
    # FOOTER NOTES (BELOW DIVIDER)
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

    y_base = 0.10
    line_spacing = 0.028
    max_lines = 6

    if clean_notes:
        for i, note in enumerate(clean_notes[:max_lines]):
            fig.text(
                0.08,
                y_base - i * line_spacing,
                f"– {note}",
                ha="left",
                fontsize=10,
                alpha=0.8,
            )
    elif footer:
        fig.text(
            0.08,
            y_base,
            footer,
            ha="left",
            fontsize=10,
            alpha=0.8,
        )

    pdf.savefig(fig)
    plt.close(fig)