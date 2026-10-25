"""Time-weighted operating-point occupancy against the lap's exact GGV input."""
from pathlib import Path

import numpy as np
import pandas as pd

from simulations.lap.core.qss import GGVMap


def operating_points(ggv: GGVMap, speed, ax, ay, duration, station) -> pd.DataFrame:
    """Compare recorded path-frame states with the solver's interpolation.

    Parameters
    ----------
    ggv : GGVMap
        Exact map used by the lap solver.
    speed, ax, ay, duration, station : array-like
        Speed (m/s), path accelerations (m/s²), interval duration (s), and station (m).

    Returns
    -------
    pandas.DataFrame
        States and signed margins; negative margins remain visible. QSS ax is a
        segment average, so these local comparisons are not solver residuals.
    """
    values = np.column_stack([speed, ax, ay, duration, station]).astype(float)
    if not np.isfinite(values).all() or np.any(values[:, 3] < 0):
        raise ValueError("Operating states must be finite with nonnegative durations.")
    frame = pd.DataFrame(values, columns=['speed_mps', 'ax_mps2', 'ay_mps2', 'duration_s', 'station_m'])
    for mode in ('drive', 'brake'):
        frame[f'{mode}_limit_mps2'] = [ggv.longitudinal_limit(v, y, mode) for v, y in zip(speed, ay)]
    frame['drive_margin_mps2'] = frame.drive_limit_mps2 - frame.ax_mps2
    frame['brake_margin_mps2'] = frame.ax_mps2 - frame.brake_limit_mps2
    frame['lateral_margin_mps2'] = [ggv.lateral_limit(v, direction=y) - abs(y) for v, y in zip(speed, ay)]
    frame['speed_in_map'] = (frame.speed_mps >= ggv.min_speed_mps) & (frame.speed_mps <= ggv.max_speed_mps)
    frame['limits_available'] = np.isfinite(frame[['drive_limit_mps2', 'brake_limit_mps2']].to_numpy()).all(axis=1)
    frame['elapsed_time_s'] = frame.duration_s.cumsum() - frame.duration_s
    total = frame.duration_s.sum()
    frame['time_percent'] = frame.duration_s * (100 / total if total else 0)
    return frame


def occupancy(frame: pd.DataFrame, bins=16) -> pd.DataFrame:
    """Bin all operating states by speed, signed Ay and Ax, weighted by duration.

    Returns
    -------
    pandas.DataFrame
        Occupied bins with edges, seconds, sample counts and percent of total time.
    """
    coordinates = frame[['speed_mps', 'ay_mps2', 'ax_mps2']].to_numpy()
    seconds, edges = np.histogramdd(coordinates, bins=bins, weights=frame.duration_s)
    counts, _ = np.histogramdd(coordinates, bins=edges)
    rows = []
    total = frame.duration_s.sum()
    for index in zip(*np.nonzero(counts)):
        row = {}
        for axis, name in enumerate(('speed_mps', 'ay_mps2', 'ax_mps2')):
            row[f'{name}_lower'] = edges[axis][index[axis]]
            row[f'{name}_upper'] = edges[axis][index[axis] + 1]
        row.update(duration_s=seconds[index], sample_count=counts[index],
                   time_percent=100 * seconds[index] / total if total else 0.)
        rows.append(row)
    return pd.DataFrame(rows)


def usage_figure(frame: pd.DataFrame, ggv: GGVMap, title: str):
    """Render map slices, operating states and time-weighted occupancy projections."""
    import matplotlib.pyplot as plt
    fig = plt.figure(figsize=(11, 8.5))
    ax = fig.add_subplot(221, projection='3d')
    for item in ggv.slices:
        directions = (1, -1) if np.all(item.ay_mps2 >= 0) else (1,)
        for sign in directions:
            for boundary in (item.ax_accel_mps2, item.ax_brake_mps2):
                ax.plot(sign * item.ay_mps2 / 9.80665, boundary / 9.80665,
                        np.full_like(boundary, item.speed_mps), color='#9aaabd', alpha=.55, linewidth=.7)
    ax.scatter(frame.ay_mps2 / 9.80665, frame.ax_mps2 / 9.80665, frame.speed_mps,
               color='#287cb8', s=5)
    ax.set(xlabel='Lateral (g)', ylabel='Longitudinal (g)', zlabel='Speed (m/s)',
           title='Operating points on linked GGV')
    specs = [('ay_mps2', 'ax_mps2', 'Lateral (g)', 'Longitudinal (g)', 9.80665, 9.80665),
             ('speed_mps', 'ay_mps2', 'Speed (m/s)', 'Lateral (g)', 1, 9.80665),
             ('speed_mps', 'ax_mps2', 'Speed (m/s)', 'Longitudinal (g)', 1, 9.80665)]
    for position, (x, y, xl, yl, xs, ys) in enumerate(specs, 2):
        axis = fig.add_subplot(2, 2, position)
        hist = axis.hist2d(frame[x] / xs, frame[y] / ys, bins=24,
                           weights=frame.time_percent, cmin=1e-12, cmap='magma')
        fig.colorbar(hist[3], ax=axis, label='Time in bin (%)')
        axis.set(xlabel=xl, ylabel=yl, title='Time-weighted occupancy')
    fig.suptitle(title, fontsize=17)
    fig.text(.5, .015, 'Signed path-frame accelerations · all states retained, including outside-map states\n'
             'Occupancy describes time spent, not tire utilization. QSS Ax is a segment average.',
             ha='center', fontsize=8)
    fig.tight_layout(rect=(0, .055, 1, .96))
    return fig


def save_usage(output: Path, prefix: str, frame: pd.DataFrame, ggv: GGVMap) -> None:
    """Write inspectable states, occupancy bins and a report-ready figure."""
    import matplotlib.pyplot as plt
    frame.to_csv(output / f'{prefix}_operating_states.csv', index=False)
    occupancy(frame).to_csv(output / f'{prefix}_state_frequency.csv', index=False)
    fig = usage_figure(frame, ggv, f'{prefix.upper()} lap · GGV usage')
    fig.savefig(output / f'{prefix}_ggv_usage.png', dpi=160)
    plt.close(fig)


def interval_durations(times, progress, track_length, completed):
    """Weight interval-start samples through the first finish crossing only."""
    times, progress = np.asarray(times), np.asarray(progress)
    stop = float(times[-1])
    if completed:
        crossing = int(np.flatnonzero(progress >= track_length)[0])
        window = slice(max(0, crossing - 1), crossing + 1)
        stop = float(np.interp(track_length, progress[window], times[window]))
    return np.maximum(0., np.minimum(times[1:], stop) - times[:-1])
