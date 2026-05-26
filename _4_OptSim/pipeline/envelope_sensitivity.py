"""Run first-principles EnvelopeSim studies across OptSim variants."""

from __future__ import annotations

import sys
from pathlib import Path
from typing import Any

import numpy as np
import pandas as pd

from pipeline.modelica_params import read_value


DOE_DIR = Path(__file__).resolve().parent.parent
REPO_ROOT = DOE_DIR.parent
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from _2_EnvelopeSim.GGV.ggv_generation import (  # noqa: E402
    G,
    GGVConfig,
    VehicleParams as GGVVehicleParams,
    force_to_aero_area,
    generate_ggv,
    save_ggv_csv,
)
from _2_EnvelopeSim.YMD.ymd_generation import (  # noqa: E402
    YMDConfig,
    VehicleParams as YMDVehicleParams,
    generate_ymd,
    save_ymd_csv,
)


FRONT_AXLE_X_M = 0.0
REAR_AXLE_X_M = -1.5494
FRONT_TRACK_M = 2.0 * 0.606110767456
REAR_TRACK_M = 2.0 * 0.60611077
WHEELBASE_M = FRONT_AXLE_X_M - REAR_AXLE_X_M


def _value(text: str, spec: dict[str, Any]) -> float:
    return read_value(text, spec)


def _mass_record(text: str, block: str, param: str) -> tuple[float, np.ndarray]:
    mass = _value(text, {"block": block, "param": param, "field_path": ["m"]})
    cg = np.array(
        [
            _value(text, {"block": block, "param": param, "field_path": ["rCM"], "index": [0]}),
            _value(text, {"block": block, "param": param, "field_path": ["rCM"], "index": [1]}),
            _value(text, {"block": block, "param": param, "field_path": ["rCM"], "index": [2]}),
        ],
        dtype=float,
    )
    return mass, cg


def _vehicle_from_variant(text: str) -> tuple[GGVVehicleParams, YMDVehicleParams]:
    masses: list[tuple[float, np.ndarray]] = [
        (
            _value(text, {"block": "pBaseSprungMass", "param": "m"}),
            np.array(
                [
                    _value(text, {"block": "pBaseSprungMass", "param": "rCM", "index": [0]}),
                    _value(text, {"block": "pBaseSprungMass", "param": "rCM", "index": [1]}),
                    _value(text, {"block": "pBaseSprungMass", "param": "rCM", "index": [2]}),
                ],
                dtype=float,
            ),
        ),
        (
            _value(text, {"block": "pDriverMass", "param": "m"}),
            np.array(
                [
                    _value(text, {"block": "pDriverMass", "param": "rCM", "index": [0]}),
                    _value(text, {"block": "pDriverMass", "param": "rCM", "index": [1]}),
                    _value(text, {"block": "pDriverMass", "param": "rCM", "index": [2]}),
                ],
                dtype=float,
            ),
        ),
        _mass_record(text, "pFrAxleMass", "unsprungMass"),
        _mass_record(text, "pRrAxleMass", "unsprungMass"),
    ]

    total_mass = float(sum(m for m, _cg in masses))
    cg = sum(m * cg for m, cg in masses) / total_mass

    front_static_frac = float((cg[0] - REAR_AXLE_X_M) / WHEELBASE_M)
    front_static_frac = min(max(front_static_frac, 0.05), 0.95)

    fr_arb = _value(text, {"block": "pFrStabar", "param": "barRate"})
    rr_arb = _value(text, {"block": "pRrStabar", "param": "barRate"})
    lltd = fr_arb / (fr_arb + rr_arb) if (fr_arb + rr_arb) > 0 else 0.5
    lltd = min(max(lltd, 0.05), 0.95)

    cl_a, cd_a = force_to_aero_area(
        downforce_n=161.7379,
        drag_n=80.7986,
        speed_mps=25.0 * 0.44704,
    )

    shared = {
        "mass": total_mass,
        "wheelbase": WHEELBASE_M,
        "track_front": FRONT_TRACK_M,
        "track_rear": REAR_TRACK_M,
        "cg_height": float(cg[2]),
        "front_static_frac": front_static_frac,
        "lltd": lltd,
        "cl_a": cl_a,
        "cd_a": cd_a,
        "aero_balance_front": 0.50,
        "fz_ref": 654.0,
        "fz_min_valid": 100.0,
        "fz_max_valid": 1091.0,
        "pdy1": -2.40275,
        "pdy2": 0.343535,
        "mu_min": 0.8,
    }

    ggv_vehicle = GGVVehicleParams(
        **shared,
        max_drive_power=80_000.0,
        max_drive_force=3_735.0,
        max_brake_force=14_000.0,
        drive_distribution_front=0.0,
        brake_distribution_front=0.62,
        pdx1=2.597991,
        pdx2=-0.618826,
    )
    ymd_vehicle = YMDVehicleParams(
        **shared,
        steering_ratio=1.0,
        pky1=-53.2421,
        pky2=2.38205,
    )
    return ggv_vehicle, ymd_vehicle


def run_envelope_sensitivities(
    population_dir: Path,
    output_dir: Path,
) -> pd.DataFrame:
    output_dir.mkdir(parents=True, exist_ok=True)

    ggv_config = GGVConfig(
        speeds=(5.0, 10.0, 15.0, 20.0, 25.0),
        ay_points=81,
        ax_search_points=201,
        verbose=False,
        warn_tire_load_range=False,
    )
    ymd_config = YMDConfig(
        speed=15.0,
        beta_min_deg=-8.0,
        beta_max_deg=8.0,
        beta_points=31,
        hwa_min_deg=-8.0,
        hwa_max_deg=8.0,
        hwa_points=31,
        verbose=False,
        warn_tire_load_range=False,
    )

    rows: list[dict[str, float | str]] = []
    variant_dirs = sorted(population_dir.glob("variant_????"))
    for i, variant_dir in enumerate(variant_dirs, start=1):
        print(f"[{i:>{len(str(len(variant_dirs)))}}/{len(variant_dirs)}] {variant_dir.name}")
        text = (variant_dir / "variant.mo").read_text()
        ggv_vehicle, ymd_vehicle = _vehicle_from_variant(text)

        variant_output = output_dir / variant_dir.name
        variant_output.mkdir(parents=True, exist_ok=True)

        envelopes = generate_ggv(ggv_vehicle, ggv_config)
        save_ggv_csv(envelopes, variant_output / "ggv.csv")

        ymd = generate_ymd(ymd_vehicle, ymd_config)
        save_ymd_csv(ymd, variant_output / "ymd.csv")

        max_cornering_g = max(float(np.nanmax(np.abs(env.ay))) / G for env in envelopes)
        max_accel_g = max(float(np.nanmax(env.ax_accel)) / G for env in envelopes)
        max_braking_g = max(float(abs(np.nanmin(env.ax_brake))) / G for env in envelopes)
        max_yaw_moment = float(np.nanmax(np.abs(ymd.mz)))
        max_ymd_ay_g = float(np.nanmax(np.abs(ymd.ay))) / G

        rows.append(
            {
                "variant": variant_dir.name,
                "ggv_max_cornering_g": max_cornering_g,
                "ggv_max_accel_g": max_accel_g,
                "ggv_max_braking_g": max_braking_g,
                "ymd_max_abs_yaw_moment_nm": max_yaw_moment,
                "ymd_max_abs_ay_g": max_ymd_ay_g,
            }
        )

    df = pd.DataFrame(rows)
    df.to_csv(output_dir / "envelope_sensitivity_metrics.csv", index=False)
    return df
