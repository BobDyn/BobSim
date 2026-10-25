"""Sampled YMD authority limits, preserving rejected cells and speed slices."""
from pathlib import Path
import csv

import numpy as np


def lateral_moment_limits(ay, mz, valid, *, samples=161):
    """Intersect valid adjacent grid triangles with lateral-acceleration stations.

    Returns outer yaw-moment bounds of the sampled maps, not a convex hull of
    unrelated points. A missing cell is never triangulated across. Inner gaps
    in yaw authority are not represented by the outer bounds.
    """
    ay, mz, valid = np.asarray(ay), np.asarray(mz), np.asarray(valid, dtype=bool)
    valid = valid & np.isfinite(ay) & np.isfinite(mz)
    triangles = []
    for i in range(ay.shape[0] - 1):
        for j in range(ay.shape[1] - 1):
            for corners in (((i, j), (i + 1, j), (i + 1, j + 1)),
                            ((i, j), (i + 1, j + 1), (i, j + 1))):
                if all(valid[index] for index in corners):
                    triangles.append([[ay[index], mz[index]] for index in corners])
    if not triangles:
        return np.empty(0), np.empty(0), np.empty(0)
    points = np.asarray(triangles)
    stations = np.linspace(points[:, :, 0].min(), points[:, :, 0].max(), samples)
    low, high = np.full(samples, np.nan), np.full(samples, np.nan)
    for k, station in enumerate(stations):
        hits = []
        for a, b in ((0, 1), (1, 2), (2, 0)):
            x0, x1 = points[:, a, 0], points[:, b, 0]
            y0, y1 = points[:, a, 1], points[:, b, 1]
            crossing = (station >= np.minimum(x0, x1)) & (station <= np.maximum(x0, x1))
            regular = crossing & (abs(x1 - x0) > 1e-12)
            hits.extend((y0[regular] + (station - x0[regular]) / (x1[regular] - x0[regular])
                         * (y1[regular] - y0[regular])).tolist())
            vertical = crossing & ~regular
            hits.extend(y0[vertical].tolist())
            hits.extend(y1[vertical].tolist())
        if hits:
            low[k], high[k] = min(hits), max(hits)
    return stations, low, high


def save_limit_surface(sweep, path: Path) -> None:
    """Save outer yaw authority against lateral acceleration and velocity."""
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", newline="") as stream:
        writer = csv.writer(stream)
        writer.writerow(["speed_mps", "ay_mps2", "ay_g", "mz_min_nm", "mz_max_nm", "valid",
                         "slice_has_load_extrapolation"])
        for result in sweep.results:
            diagnostics = result.diagnostics or {}
            load_valid = diagnostics.get("tire_load_valid", np.ones_like(result.ay))
            extrapolated = bool(np.any(result.converged & (load_valid == 0)))
            ay, low, high = lateral_moment_limits(result.ay, result.mz, result.converged)
            if not len(ay):
                writer.writerow([result.speed, "nan", "nan", "nan", "nan", 0, int(extrapolated)])
            for x, lower, upper in zip(ay, low, high):
                writer.writerow([result.speed, x, x / 9.80665, lower, upper, int(np.isfinite(lower + upper)),
                                 int(extrapolated)])


def limit_surface_figure(sweep):
    """Render sampled lower/upper authority surfaces without closing invalid gaps."""
    import matplotlib.pyplot as plt
    fig = plt.figure(figsize=(10, 7))
    ax = fig.add_subplot(111, projection="3d")
    maps = [lateral_moment_limits(r.ay, r.mz, r.converged) for r in sweep.results]
    from mpl_toolkits.mplot3d.art3d import Poly3DCollection
    from matplotlib.patches import Patch
    # Opaque triangles in a shared collection avoid translucent face
    # overlap and per-polygon depth sorting artifacts. No smoothing of physics.
    faces, colors = [], []
    for index, color in ((1, "#287cb8"), (2, "#e17732")):
        for i in range(len(maps) - 1):
            if not len(maps[i][0]) or not len(maps[i + 1][0]):
                continue
            x = np.stack([maps[i][0], maps[i + 1][0]]) / 9.80665
            yaw = np.stack([maps[i][index], maps[i + 1][index]])
            speed = np.broadcast_to(np.asarray(sweep.speeds[i:i + 2])[:, None], x.shape)
            ok = np.isfinite(yaw)
            cells = ok[:, :-1].all(axis=0) & ok[:, 1:].all(axis=0)
            for j in np.flatnonzero(cells):
                vertices = [(x[a, b], yaw[a, b], speed[a, b])
                            for a, b in ((0, j), (0, j + 1), (1, j + 1), (1, j))]
                faces.extend([[vertices[0], vertices[1], vertices[2]],
                              [vertices[0], vertices[2], vertices[3]]])
                colors.extend([color, color])
    if faces:
        ax.add_collection3d(Poly3DCollection(faces, facecolors=colors, edgecolors="none",
                                            linewidths=0, antialiaseds=False, alpha=1))
        vertices = np.asarray(faces).reshape(-1, 3)
        ax.auto_scale_xyz(vertices[:, 0], vertices[:, 1], vertices[:, 2])
    ax.legend(handles=[Patch(color="#287cb8", label="Lower sampled yaw limit"),
                       Patch(color="#e17732", label="Upper sampled yaw limit")], loc="upper left")
    ax.set(xlabel="Lateral acceleration (g)", ylabel="Yaw moment (N m)", zlabel="Speed (m/s)",
           title="YMD sampled limit surface · 14DOF")
    ax.view_init(elev=24, azim=-55)
    extrapolated = sum(int(np.count_nonzero(r.converged &
                       ((r.diagnostics or {}).get("tire_load_valid", np.ones_like(r.ay)) == 0)))
                       for r in sweep.results)
    if extrapolated:
        fig.text(.5, .02, f"Includes {extrapolated} states outside the tire load-fit range · extrapolated",
                 ha="center", fontsize=10, color="#8c471c")
    fig.tight_layout(rect=(0, .04, 1, 1))
    return fig


def plot_limit_surface(sweep, path: Path) -> None:
    import matplotlib.pyplot as plt
    fig = limit_surface_figure(sweep)
    fig.savefig(path, dpi=150)
    plt.close(fig)
