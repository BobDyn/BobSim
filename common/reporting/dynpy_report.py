"""Response and lap reports using BobSim's shared report pages and plots."""

from __future__ import annotations

from pathlib import Path
from typing import Any

import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages
from matplotlib.transforms import Bbox
import numpy as np
import pandas as pd

from common.plotting.plot_engine import PlotEngine
from common.reporting.sections import add_title_page


def _plot(title: str, x: str, y: str, x_label: str, y_label: str, scale: float = 1.0) -> dict[str, Any]:
    return {"title": title, "x": {"key": x, "label": x_label},
            "y": {"key": y, "label": y_label, "scale": scale}}


def _summary_page(pdf: PdfPages, title: str, rows: list[tuple[str, Any]]) -> None:
    fig, ax = plt.subplots(figsize=(11, 8.5))
    ax.axis("off")
    fig.suptitle(title, fontsize=18, fontweight="bold", y=0.93)
    cells = [(label, f"{value:.4g}" if isinstance(value, float) else str(value)) for label, value in rows]
    table = ax.table(cellText=cells, colWidths=[0.52, 0.48], cellLoc="left", bbox=Bbox.from_bounds(0, 0.05, 1, 0.87))
    table.auto_set_font_size(False)
    table.set_fontsize(11)
    for (row, _), cell in table.get_celld().items():
        cell.set_edgecolor("#dddddd")
        cell.set_facecolor("#f2f5f8" if row % 2 == 0 else "white")
        cell.PAD = 0.08
    pdf.savefig(fig)
    plt.close(fig)


def build_dynpy_report(
    workflow_id: str,
    output_directory: Path,
    config: dict[str, Any],
    summary: dict[str, Any],
    *,
    vehicle_name: str,
) -> Path:
    """## DynPy Results Report

    Build a PDF from the run's exported signals and captured configuration.

    Parameters
    ----------
    workflow_id : str
        Ramp-steer, step-steer, QSS lap or transient lap workflow ID.
    output_directory : Path
        Directory containing the run's CSV files.
    config : dict
        Configuration used by the run.
    summary : dict
        Run status and summary metrics.
    vehicle_name : str
        Vehicle shown on the cover.

    Returns
    -------
    Path
        Generated PDF path.
    """
    response = workflow_id in {"reduced-step-steer", "reduced-ramp-steer"}
    ramp = workflow_id == "reduced-ramp-steer"
    transient = workflow_id == "lap-transient"
    title = "Step-steer response" if response else "Transient lap" if transient else "QSS lap"
    if ramp:
        title = "Ramp-steer response"
    method = "Transient" if response else "Transient with QSS reference" if transient else "QSS"
    model = f"DynPy | {summary['model_dof']} DOF | {method} | Python"
    filename = "report.pdf" if response else "transient_report.pdf" if transient else "qss_report.pdf"
    report_path = output_directory / filename
    deg = 180.0 / np.pi
    pages: list[tuple[pd.DataFrame, dict[str, Any]]] = []
    if response:
        frame = pd.read_csv(output_directory / "signals.csv")
        inputs = (
            [("Roadwheel rate (deg/s)", config["roadwheel_rate_deg_s"]),
             ("Ramp start (s)", config["start_time_s"]),
             ("Ramp end (s)", config.get("ramp_end_time_s", config["stop_time_s"]))] if ramp else
            [("Roadwheel step (deg)", config["roadwheel_step_deg"]),
             ("Step time (s)", config["step_time_s"]), ("Rise time (s)", config["rise_time_s"])]
        )
        rows = [("Solver succeeded", summary["success"]), ("Samples", len(frame)),
                ("Target speed (m/s)", config["speed_mps"]), *inputs,
                ("Duration (s)", float(frame.time.iloc[-1])), ("KinPy evaluation", config["kinematics_mode"]),
                ("Peak absolute lateral acceleration (m/s²)", float(frame.accY.abs().max())),
                ("Final yaw rate (deg/s)", float(frame.yawVel.iloc[-1] * deg)),
                ("Final speed (m/s)", float(frame.get("speed", frame.velX).iloc[-1]))]
        plots = [
            _plot("Steering input", "time", "handwheelAngle", "Time (s)", "Roadwheel steer (deg)", deg),
            _plot("Yaw response", "time", "yawVel", "Time (s)", "Yaw rate (deg/s)", deg),
            _plot("Lateral response", "time", "accY", "Time (s)", "Lateral acceleration (m/s²)"),
            _plot("Speed", "time", "speed" if "speed" in frame else "velX", "Time (s)", "Speed (m/s)"),
        ]
        if "targetSpeed" in frame and "speed" in frame:
            rows.extend([("Speed control", "PI"),
                         ("Maximum speed error (m/s)", float((frame.speed - frame.targetSpeed).abs().max()))])
            plots[-1]["label"] = "Actual"
            plots[-1]["overlay"] = {"x": {"key": "time"}, "y": {"key": "targetSpeed"},
                                    "label": "Target", "linestyle": "--"}
        pages.append((frame, {"layout": "quad", "title": "Steering response", "subplots": plots}))
        for signal, label, unit, scale in (("tireFy", "Lateral tire force", "N", 1.0),
                                          ("camber", "Wheel camber", "deg", deg),
                                          ("jounce", "Wheel travel", "mm", 1000.0)):
            if all(f"{signal}{corner}" in frame for corner in ("FL", "FR", "RL", "RR")):
                pages.append((frame, {"layout": "quad", "title": label, "subplots": [
                    _plot(corner, "time", f"{signal}{corner}", "Time (s)", f"{label} ({unit})", scale)
                    for corner in ("FL", "FR", "RL", "RR")
                ]}))
    else:
        qss = pd.read_csv(output_directory / "qss_lap.csv")
        rows = [("QSS converged", summary["qss_converged"]),
                ("Line optimizer converged", summary["line_optimizer_converged"]),
                ("Racing line", summary["line_mode"]), ("Track length (m)", summary["track_length_m"]),
                ("QSS lap time (s)", summary["optimized_qss_lap_time_s"]),
                ("Power cap (W)", summary["effective_drive_power_limit_w"]),
                ("GGV provenance", summary["ggv_provenance"]["status"])]
        if "ggv_speed_max_mps" in summary:
            rows.extend([
                ("GGV minimum speed (m/s)", summary["ggv_speed_min_mps"]),
                ("GGV maximum speed (m/s)", summary["ggv_speed_max_mps"]),
                ("GGV range limited", summary["ggv_range_limited"]),
            ])
        pages.append((qss, {"title": "QSS racing line", "equal_aspect": True,
                           **_plot("QSS racing line", "x_m", "y_m", "x (m)", "y (m)")}))
        pages.append((qss, {"layout": "quad", "title": "QSS speed and acceleration", "subplots": [
            _plot("Speed", "station_m", "speed_mps", "Distance (m)", "Speed (m/s)"),
            _plot("Longitudinal acceleration", "station_m", "ax_mps2", "Distance (m)", "Acceleration (m/s²)"),
            _plot("Lateral acceleration", "station_m", "ay_mps2", "Distance (m)", "Acceleration (m/s²)"),
            _plot("Curvature", "station_m", "curvature_per_m", "Distance (m)", "Curvature (1/m)"),
        ]}))
        if transient:
            frame = pd.read_csv(output_directory / "transient_lap.csv")
            rows += [("Transient solver succeeded", summary["transient_success"]),
                     ("Lap completed", summary["transient_completed_lap"]),
                     ("Transient lap time (s)", summary["transient_lap_time_s"]),
                     ("Lap-time difference from QSS (s)", summary["transient_lap_delta_s"]),
                     ("Maximum lateral error (m)", summary["transient_max_abs_lateral_error_m"])]
            pages.append((frame, {"layout": "quad", "title": "Transient lap response", "subplots": [
                _plot("Speed", "time_s", "speed_mps", "Time (s)", "Speed (m/s)"),
                _plot("Steering", "time_s", "steering_rad", "Time (s)", "Roadwheel steer (deg)", deg),
                _plot("Path tracking", "time_s", "lateral_error_m", "Time (s)", "Lateral error (m)"),
                _plot("Yaw response", "time_s", "yaw_rate_radps", "Time (s)", "Yaw rate (deg/s)", deg),
            ]}))
    notes = [f"Vehicle: {vehicle_name}", f"Run time: {summary.get('wall_time_s', 0):.2f} s"]
    if not response:
        notes += [f"Track: {config['track']['boundary_csv']}",
                  "QSS is an envelope-based reference. Transient includes the driver and vehicle dynamics."]
    with PdfPages(report_path) as pdf:
        add_title_page(pdf, {"report": {"brand": "BobSim", "title": title, "subtitle": model, "notes": notes}})
        _summary_page(pdf, f"{title} | {summary['model_dof']} DOF", rows)
        for frame, plot in pages:
            engine = PlotEngine({"plots": {"response": plot}})
            for _, fig in engine.render({"series": frame.to_dict("list")}):
                if plot.get("equal_aspect"):
                    fig.axes[0].set_aspect("equal", adjustable="datalim")
                fig.text(0.99, 0.015, model, ha="right", fontsize=8, color="#555555")
                pdf.savefig(fig)
                plt.close(fig)
    return report_path
