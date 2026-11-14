"""Reproduce the C12/R12 dataset from the supplied PDF (requires pypdf, numpy, Pillow).

Run with PDF and output directory arguments. Writes raw pixel samples, processed
calibration JSON, and source/trace overlays for visual review. Does not ship the PDF.
"""

from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path

import numpy as np
from PIL import ImageDraw
from pypdf import PdfReader


DATASET = "ttx25_mkii_c12_r12_pdf_v1"
SPEEDS = [0, 12.5, 20, 25, 37.5, 50, 75, 100, 125, 150, 175, 200, 225, 250]
# Calibrated against the 0/250 mm/s and 0/200 N grid lines in embedded page-2 images.
CALIBRATION = {
    "low": (102, 1600, 456, 339),
    "high": (100, 1597, 459, 342),
}
COLORS = {
    "low": [(0, (255, 0, 0)), (2, (0, 0, 255)), (4, (128, 0, 0)),
            (6, (255, 128, 0)), (10, (0, 64, 0)), (15, (1, 16, 150)), (25, (138, 28, 151))],
    "high": [(3, (128, 128, 64)), (2, (0, 128, 128)),
             (1, (0, 128, 255)), (0, (126, 71, 65))],
}


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("pdf", type=Path)
    parser.add_argument("output", type=Path)
    args = parser.parse_args()
    args.output.mkdir(parents=True, exist_ok=True)
    pdf = PdfReader(args.pdf)
    images = [item.image.convert("RGB") for item in pdf.pages[1].images if item.image.width > 1000]
    if len(images) != 2:
        raise ValueError("Expected the two original C12/R12 chart images on PDF page 2")
    curves = []
    samples = []
    for image in images:
        pixels = np.asarray(image)
        sweep = "high" if np.any(np.all(pixels[100:800, 1100:1200] == (128, 128, 64), axis=2)) else "low"
        x0, x250, y0, y200 = CALIBRATION[sweep]
        overlay = image.copy()
        draw = ImageDraw.Draw(overlay)
        for setting, color in COLORS[sweep]:
            for direction, sign, valve in (("compression", 1, "C12"), ("rebound", -1, "R12")):
                ls, hs = (setting, 4.3) if sweep == "low" else (0, setting)
                curve_id = f"{valve}_LS{ls}_HS{hs}"
                forces = [0.0]
                points = [(float(x0), float(y0))]
                for speed in SPEEDS[1:]:
                    x = round(x0 + speed / 250 * (x250 - x0))
                    for radius in (2, 8):
                        y_indices, _ = np.where(np.all(pixels[:860, x-radius:x+radius+1] == color, axis=2))
                        y_indices = y_indices[y_indices < y0] if sign > 0 else y_indices[y_indices > y0]
                        if len(y_indices):
                            break
                    if not len(y_indices):
                        raise ValueError(f"Missing pixels for {curve_id} at {speed} mm/s")
                    y = float(np.median(y_indices))
                    force = sign * (y0 - y) * 200 / (y0 - y200)
                    forces.append(round(force, 1))
                    points.append((float(x), y))
                    samples.append({"curve": curve_id, "velocity_mmps": speed, "x": x,
                                    "window_radius_pixels": radius,
                                    "y_pixels": y_indices.tolist(), "median_y": y, "force_n": force})
                if curve_id == "R12_LS25_HS4.3":
                    # Its 12.5 mm/s trace is occluded by the LS15 trace; the
                    # remaining same-color pixel is a loop, not the backbone.
                    forces[1] = round(forces[2] * SPEEDS[1] / SPEEDS[2], 1)
                    points[1] = (points[1][0], y0 + forces[1] * (y0-y200) / 200)
                if any(b < a for a, b in zip(forces, forces[1:])):
                    raise ValueError(f"Nonmonotone extracted force for {curve_id}; inspect pixels")
                curves.append({"id": curve_id, "direction": direction, "valve": valve,
                               "low_speed_clicks_from_closed": ls,
                               "high_speed_turns_from_open": hs, "force_n": forces})
                draw.line(points, fill=color, width=3)
                for marker_x, marker_y in points:
                    draw.ellipse((marker_x-3, marker_y-3, marker_x+3, marker_y+3), outline=(0, 0, 0))
        overlay.save(args.output / f"{sweep}_trace_overlay.png")
    dataset = {
        "id": DATASET, "schema": 1,
        "source": {"file": args.pdf.name, "page": 2,
                   "sha256": hashlib.sha256(args.pdf.read_bytes()).hexdigest(),
                   "title": "TTX25 MkII damper dynomometer response",
                   "extraction": "Original embedded raster charts; median exact-color pixel rows in a 5-pixel "
                                 "column window, widened to 17 pixels where traces overlap",
                   "calibration_pixels": CALIBRATION},
        "limitations": [
            "Digitized chart approximation, not raw dyno measurements or a validated calibration "
            "of an individual damper.",
            "Positive plotted force is assigned to compression and negative to rebound; the PDF does not "
            "explicitly label branch directions. Verify this convention against a known-direction dyno test.",
            "First sampled speed is 12.5 mm/s; origin is imposed and the interval to that sample is linear. "
            "Near-zero hysteresis is not modeled.",
            "R12 LS25/HS4.3 at 12.5 mm/s is occluded; that point is linearly interpolated between the imposed "
            "origin and the 20 mm/s sample.",
            "Pixel medians collapse multivalued loops. Gas force, friction, temperature and acceleration "
            "dependence are not separately identified.",
            "Only C12/R12: LS=0..25 at HS=4.3, or HS=0..4.3 at LS=0. "
            "Interpolation between settings is an approximation.",
            "The common LS0/HS4.3 endpoint uses the low-speed sweep. Maximum calibrated speed is 0.25 m/s; "
            "terminal-slope extrapolation is unmeasured.",
        ],
        "velocity_mps": [speed / 1000 for speed in SPEEDS], "curves": curves,
    }
    (args.output / f"{DATASET}.json").write_text(json.dumps(dataset, indent=2) + "\n", encoding="utf-8")
    (args.output / "c12_r12_pixel_samples.json").write_text(json.dumps(samples, indent=2) + "\n", encoding="utf-8")
    print(f"Extracted {len(curves)} branches; inspect both trace overlays before using the dataset.")


if __name__ == "__main__":
    main()
