"""Recorded YMD speed slices for a responsive, fixed-axis carpet plot."""
import csv
import math
from collections import defaultdict
from pathlib import Path

import numpy as np

from simulations.envelope.ymd.surface import lateral_moment_limits


def speed_slices(path: Path) -> dict:
    """Keep computed speeds and invalid-point gaps; never interpolate new physics."""
    speeds: dict[float, list[dict]] = defaultdict(list)
    with path.open(newline="") as stream:
        for raw in csv.DictReader(stream):
            row = {key: float(raw[key]) for key in
                   ("speed_mps", "beta_deg", "hwa_deg", "ay_g", "mz_nm", "converged")}
            if math.isfinite(row["speed_mps"]):
                speeds[row["speed_mps"]].append(row)
    slices = []
    all_x, all_y = [], []
    for speed, rows in sorted(speeds.items()):
        x: list[float | None] = []
        beta_y: list[float | None] = []
        steer_y: list[float | None] = []
        for family, other, destination in (("beta_deg", "hwa_deg", beta_y), ("hwa_deg", "beta_deg", steer_y)):
            groups: dict[float, list[dict]] = defaultdict(list)
            for row in rows:
                groups[row[family]].append(row)
            for _, group in sorted(groups.items()):
                for row in sorted(group, key=lambda r: r[other]):
                    valid = row["converged"] == 1 and math.isfinite(row["ay_g"]) and math.isfinite(row["mz_nm"])
                    x.append(row["ay_g"] if valid else None)
                    beta_y.append(None)
                    steer_y.append(None)
                    if valid:
                        destination[-1] = row["mz_nm"]
                        all_x.append(row["ay_g"])
                        all_y.append(row["mz_nm"])
                x.append(None)
                beta_y.append(None)
                steer_y.append(None)
        series: list[dict] = [{"signal": "Constant sideslip", "unit": "N m", "values": beta_y},
                  {"signal": "Constant steering", "unit": "N m", "values": steer_y}]
        betas = sorted({r["beta_deg"] for r in rows})
        steers = sorted({r["hwa_deg"] for r in rows})
        bi, si = {v: i for i, v in enumerate(betas)}, {v: i for i, v in enumerate(steers)}
        ay = np.full((len(betas), len(steers)), np.nan)
        mz = np.full_like(ay, np.nan)
        grid_valid = np.zeros(ay.shape, dtype=bool)
        for row in rows:
            index = bi[row["beta_deg"]], si[row["hwa_deg"]]
            ay[index], mz[index], grid_valid[index] = row["ay_g"], row["mz_nm"], row["converged"] == 1
        stations, low, high = lateral_moment_limits(ay, mz, grid_valid)
        if len(stations):
            offset = len(x)
            x.extend(float(v) for v in stations)
            for item in series:
                item["values"].extend([None] * len(stations))
            for label, values in (("Lower sampled limit", low), ("Upper sampled limit", high)):
                series.append({"signal": label, "unit": "N m",
                               "values": [None] * offset + [float(v) if np.isfinite(v) else None for v in values]})
        slices.append({"speed": speed, "x": x, "x_unit": "g", "x_label": "Lateral acceleration",
                       "row_indices": list(range(len(x))), "series": series})
    return {"slices": slices, "x_extent": [min(all_x), max(all_x)] if all_x else [-1, 1],
            "y_extent": [min(all_y), max(all_y)] if all_y else [-1, 1]}
