"""Recorded YMD speed slices for a responsive, fixed-axis carpet plot."""
import csv
import math
from collections import defaultdict
from pathlib import Path


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
        slices.append({"speed": speed, "x": x, "x_unit": "g", "x_label": "Lateral acceleration",
                       "row_indices": list(range(len(x))),
                       "series": [{"signal": "Constant sideslip", "unit": "N m", "values": beta_y},
                                  {"signal": "Constant steering", "unit": "N m", "values": steer_y}]})
    return {"slices": slices, "x_extent": [min(all_x), max(all_x)] if all_x else [-1, 1],
            "y_extent": [min(all_y), max(all_y)] if all_y else [-1, 1]}
