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
        writer.writerow(["speed_mps", "ay_mps2", "ay_g", "mz_min_nm", "mz_max_nm", "valid"])
        for result in sweep.results:
            ay, low, high = lateral_moment_limits(result.ay, result.mz, result.converged)
            if not len(ay):
                writer.writerow([result.speed, "nan", "nan", "nan", "nan", 0])
            for x, lower, upper in zip(ay, low, high):
                writer.writerow([result.speed, x, x / 9.80665, lower, upper, int(np.isfinite(lower + upper))])


def limit_surface_figure(sweep):
    """Render sampled lower/upper authority surfaces without closing invalid gaps."""
    import matplotlib.pyplot as plt
    fig = plt.figure(figsize=(10, 7))
    ax = fig.add_subplot(111, projection="3d")
    maps = [lateral_moment_limits(r.ay, r.mz, r.converged) for r in sweep.results]
    for i in range(len(maps) - 1):
        if not len(maps[i][0]) or not len(maps[i + 1][0]):
            continue
        x = np.stack([maps[i][0], maps[i + 1][0]]) / 9.80665
        speed = np.broadcast_to(np.asarray(sweep.speeds[i:i + 2])[:, None], x.shape)
        for index, color in ((1, "#287cb8"), (2, "#e17732")):
            yaw = np.stack([maps[i][index], maps[i + 1][index]])
            # Each face needs four valid corners. Mask neighboring samples too
            # so matplotlib cannot drop one NaN vertex and bridge a rejected cell.
            ok = np.isfinite(yaw)
            cells = ok[:, :-1].all(axis=0) & ok[:, 1:].all(axis=0)
            for j in np.flatnonzero(cells):
                ax.plot_surface(x[:, j:j + 2], yaw[:, j:j + 2], speed[:, j:j + 2],
                                color=color, alpha=.55, linewidth=0)
    ax.set(xlabel="Lateral acceleration (g)", ylabel="Yaw moment (N m)", zlabel="Speed (m/s)",
           title="YMD sampled limit surface · 14DOF")
    ax.view_init(elev=24, azim=-55)
    fig.tight_layout()
    return fig


def plot_limit_surface(sweep, path: Path) -> None:
    import matplotlib.pyplot as plt
    fig = limit_surface_figure(sweep)
    fig.savefig(path, dpi=150)
    plt.close(fig)
