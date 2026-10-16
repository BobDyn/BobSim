"""Racing-line geometry report."""
from pathlib import Path
from typing import Any

from matplotlib.figure import Figure
from matplotlib.backends.backend_pdf import PdfPages
import numpy as np


def build_racing_line_report(result: dict[str, Any], path: Path) -> None:
    """## Racing-Line Report

    Parameters
    ----------
    result : dict
        Generated line, track boundaries and clearance inputs.
    path : Path
        Destination PDF.
    """
    line = result["line"]
    with PdfPages(path) as pdf:
        fig = Figure(figsize=(11, 8.5), layout="constrained")
        ax = fig.subplots()
        for key, label, color in (("left", "Boundary 1", "#64748b"), ("right", "Boundary 2", "#94a3b8")):
            points = np.asarray(result[key])
            points = np.vstack((points, points[0]))
            ax.plot(points[:, 0], points[:, 1], color=color, label=label)
        ax.plot([*line["x_m"], line["x_m"][0]], [*line["y_m"], line["y_m"][0]], color="#0284c7", label="Racing line")
        ax.set(aspect="equal", xlabel="x (m)", ylabel="y (m)", title="Racing line")
        ax.legend()
        fig.suptitle(f"Width {result['vehicle_width_m']:.3f} m | Clearance {result['clearance_m']:.3f} m per side")
        pdf.savefig(fig)
        fig = Figure(figsize=(11, 8.5), layout="constrained")
        ax = fig.subplots()
        ax.plot(line["station_m"], line["curvature_per_m"])
        ax.set(xlabel="Distance (m)", ylabel="Curvature (1/m)", title="Racing-line curvature")
        pdf.savefig(fig)
