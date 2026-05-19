from __future__ import annotations

import csv
import sys
from pathlib import Path
from typing import Any, Sequence, cast

import numpy as np
import yaml

from _0_Utils.reporting.report_engine import ReportEngine
from _3_StandardSim._modelica_runner import ModelicaRunner


DEFAULT_CONFIG_PATH = Path("_3_StandardSim/FourPostEval/four_post_eval_config.yml")
DEFAULT_BUILD_DIR = "_3_StandardSim/Build/FourPostSim"
DEFAULT_EXEC_NAME = "BobLib.Standards.FourPostSim"
DEFAULT_METRICS_CSV_PATH = "_3_StandardSim/results/four_post_eval_report_metrics.csv"


FOUR_POST_EVAL_SIGNALS = [
    "frKnC.heave",
    "frKnC.roll",
    "frKnC.fx",
    "frKnC.fy",
    "frKnC.leftSpringLength",
    "frKnC.leftGamma",
    "frKnC.leftToe",
    "frKnC.leftCaster",
    "frKnC.leftKpi",
    "frKnC.leftMechTrail",
    "frKnC.leftMechScrub",
    "frKnC.rightSpringLength",
    "frKnC.rightGamma",
    "frKnC.rightToe",
    "frKnC.rightCaster",
    "frKnC.rightKpi",
    "frKnC.rightMechTrail",
    "frKnC.rightMechScrub",
    "frKnC.jackingForce",
    "frKnC.stabarAngle",
    "rrKnC.heave",
    "rrKnC.roll",
    "rrKnC.fx",
    "rrKnC.fy",
    "rrKnC.leftSpringLength",
    "rrKnC.leftGamma",
    "rrKnC.leftToe",
    "rrKnC.leftCaster",
    "rrKnC.leftKpi",
    "rrKnC.leftMechTrail",
    "rrKnC.leftMechScrub",
    "rrKnC.rightSpringLength",
    "rrKnC.rightGamma",
    "rrKnC.rightToe",
    "rrKnC.rightCaster",
    "rrKnC.rightKpi",
    "rrKnC.rightMechTrail",
    "rrKnC.rightMechScrub",
    "rrKnC.jackingForce",
    "rrKnC.stabarAngle",
]

FOUR_POST_EVAL_VARIABLE_FILTER = "|".join(FOUR_POST_EVAL_SIGNALS)


def load_config(path: str | Path) -> dict[str, Any]:
    path = Path(path)
    with path.open("r", encoding="utf-8") as f:
        config = yaml.safe_load(f)

    if config is None:
        raise ValueError(f"Config file is empty: {path}")
    if not isinstance(config, dict):
        raise TypeError(f"Expected YAML config to contain a mapping at top level: {path}")

    return cast(dict[str, Any], config)


def _as_mapping(value: Any, *, name: str) -> dict[str, Any]:
    if value is None:
        return {}
    if not isinstance(value, dict):
        raise TypeError(f"Expected {name} to be a mapping if provided.")
    return cast(dict[str, Any], value)


def write_metrics_csv(summary: dict[str, Any], path: str | Path) -> Path:
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.unlink(missing_ok=True)

    with path.open("w", newline="", encoding="utf-8") as f:
        writer = csv.writer(f)
        writer.writerow(["metric", "value"])
        for key in sorted(summary):
            value = summary[key]
            if isinstance(value, float) and np.isnan(value):
                value = ""
            writer.writerow([key, value])

    return path


class FourPostEvalSim:
    def __init__(self, config: dict[str, Any]):
        self.config = config

    def build_overrides(self) -> dict[str, Any]:
        procedure = _as_mapping(self.config.get("procedure"), name="procedure")

        return {
            "steerMagnitude": procedure.get("steerMagnitude", 0.0),
            "heaveMagnitude": procedure.get("heaveMagnitude", 0.03),
            "rollMagnitude": procedure.get("rollMagnitude", 0.035),
            "forceMagnitude": procedure.get("forceMagnitude", 1000.0),
        }

    def run(self) -> dict[str, Any]:
        simulation_cfg = _as_mapping(self.config.get("simulation"), name="simulation")
        execution_cfg = _as_mapping(self.config.get("execution"), name="execution")
        report_cfg = _as_mapping(self.config.get("report"), name="report")

        runner = ModelicaRunner(
            build_dir=simulation_cfg.get("build_dir", DEFAULT_BUILD_DIR),
            exec_name=simulation_cfg.get("exec_name", DEFAULT_EXEC_NAME),
            simulation={
                **simulation_cfg,
                "variable_filter": simulation_cfg.get(
                    "variable_filter",
                    FOUR_POST_EVAL_VARIABLE_FILTER,
                ),
            },
        )

        results = runner.run(
            signals=FOUR_POST_EVAL_SIGNALS,
            mode="raw",
            cases=[self.build_overrides()],
            execution=execution_cfg,
        )

        if not results:
            raise RuntimeError("FourPostEval returned no cases.")

        result = results[0]
        if result.get("_status") != "ok":
            raise RuntimeError(
                "FourPostEval simulation failed:\n"
                f"{result.get('_error', 'unknown error')}\n"
                f"{result.get('_traceback', '')}"
            )

        summary, series = self.summarize(result)
        metrics_csv_path = write_metrics_csv(
            summary,
            report_cfg.get("metrics_csv_path", DEFAULT_METRICS_CSV_PATH),
        )

        return {
            "summary": summary,
            "series": series,
            "metrics_csv_path": str(metrics_csv_path),
            "cases": results,
            "failed_cases": [],
            "n_cases": len(results),
            "n_successful_cases": len(results),
            "n_failed_cases": 0,
        }

    def summarize(self, result: dict[str, Any]) -> tuple[dict[str, Any], dict[str, np.ndarray]]:
        t = np.asarray(result["time"], dtype=float).reshape(-1)

        def sig(prefix: str, name: str) -> np.ndarray:
            return np.asarray(result[f"{prefix}.{name}"], dtype=float).reshape(-1)

        def sample_at_times(signal: np.ndarray, times: list[float]) -> np.ndarray:
            return np.array([signal[np.argmin(np.abs(t - ti))] for ti in times], dtype=float)

        def compute_gain(x: np.ndarray, y: np.ndarray) -> float:
            mask = np.isfinite(x) & np.isfinite(y)
            x = x[mask]
            y = y[mask]
            if x.size < 2 or y.size < 2:
                return float("nan")
            if np.nanstd(x) < 1e-12 or np.nanstd(y) < 1e-12:
                return float("nan")
            coeffs = np.polyfit(x, y, 1)
            return float(coeffs[0])

        def nanmean_or_nan(values: Sequence[float]) -> float:
            arr = np.asarray(list(values), dtype=float)
            if arr.size == 0 or not np.isfinite(arr).any():
                return float("nan")
            return float(np.nanmean(arr))

        # FourPost uses a 5 s pose cadence with a short load pulse and a dead tail.
        pose_step_s = 5.0
        heave_pose_start_s = 2.0
        heave_pose_count = 10
        roll_pose_start_s = 58.0
        roll_pose_count = 11

        def pose_sample_times(start_s: float, count: int) -> list[float]:
            # Sample inside the dead region after the load pulse, before the next pose change.
            return [start_s + pose_step_s * i + 4.0 for i in range(count)]

        def jack_times(start_s: float, count: int) -> list[float]:
            return [start_s + pose_step_s * i + 1.5 for i in range(count)]

        heave_sample_times = pose_sample_times(heave_pose_start_s, heave_pose_count)
        roll_sample_times = pose_sample_times(roll_pose_start_s, roll_pose_count)
        heave_jack_times = jack_times(heave_pose_start_s, heave_pose_count)
        roll_jack_times = jack_times(roll_pose_start_s, roll_pose_count)

        signals = {
            "camber": "Gamma",
            "toe": "Toe",
            "caster": "Caster",
            "kpi": "Kpi",
            "trail": "MechTrail",
            "scrub": "MechScrub",
        }
        corners = ["fr_l", "fr_r", "rr_l", "rr_r"]

        def side_prefix(corner: str) -> str:
            return "frKnC" if corner.startswith("fr") else "rrKnC"

        def corner_signal(prefix: str, corner: str, name: str) -> np.ndarray:
            side = "left" if corner.endswith("_l") else "right"
            return sig(prefix, f"{side}{name}")

        heave = -sig("frKnC", "heave")
        roll = sig("frKnC", "roll")

        heave_vals = sample_at_times(heave, heave_sample_times)
        heave_mask = np.isfinite(heave_vals)
        heave_vals = heave_vals[heave_mask]
        heave_idx = np.argsort(heave_vals)
        heave_vals = heave_vals[heave_idx]

        roll_vals = sample_at_times(roll, roll_sample_times)
        roll_mask = np.isfinite(roll_vals)
        roll_vals = roll_vals[roll_mask]
        roll_idx = np.argsort(roll_vals)
        roll_vals = roll_vals[roll_idx]

        heave_series: dict[str, np.ndarray] = {}
        roll_series: dict[str, np.ndarray] = {}

        for key, suffix in signals.items():
            for corner in corners:
                prefix = side_prefix(corner)
                heave_sig = sample_at_times(corner_signal(prefix, corner, suffix), heave_sample_times)
                roll_sig = sample_at_times(corner_signal(prefix, corner, suffix), roll_sample_times)

                heave_sig = heave_sig[heave_mask]
                roll_sig = roll_sig[roll_mask]
                heave_series[f"{corner}_{key}_vs_heave"] = heave_sig[heave_idx]
                roll_series[f"{corner}_{key}_vs_roll"] = roll_sig[roll_idx]

        # Jacking is the incremental chassis reaction from the force pulse at a
        # fixed pose, not the absolute axle support load. Subtract the dead-tail
        # force at the same pose so we only retain the load introduced by the
        # heave/roll force pulse.
        fr_jack = -sig("frKnC", "jackingForce")
        rr_jack = -sig("rrKnC", "jackingForce")

        fr_heave_jack_x = sample_at_times(heave, heave_jack_times)
        fr_heave_jack_y = sample_at_times(fr_jack, heave_jack_times) - sample_at_times(
            fr_jack, heave_sample_times
        )
        rr_heave_jack_x = sample_at_times(heave, heave_jack_times)
        rr_heave_jack_y = sample_at_times(rr_jack, heave_jack_times) - sample_at_times(
            rr_jack, heave_sample_times
        )

        fr_roll_jack_x = sample_at_times(roll, roll_jack_times)
        fr_roll_jack_y = sample_at_times(fr_jack, roll_jack_times) - sample_at_times(
            fr_jack, roll_sample_times
        )
        rr_roll_jack_x = sample_at_times(roll, roll_jack_times)
        rr_roll_jack_y = sample_at_times(rr_jack, roll_jack_times) - sample_at_times(
            rr_jack, roll_sample_times
        )

        fr_fx = sig("frKnC", "fx")
        rr_fx = sig("rrKnC", "fx")
        fr_fy = sig("frKnC", "fy")
        rr_fy = sig("rrKnC", "fy")

        fr_roll_fy = sample_at_times(fr_fy, roll_jack_times)
        rr_roll_fy = sample_at_times(rr_fy, roll_jack_times)
        fr_heave_fx = sample_at_times(fr_fx, heave_jack_times)
        rr_heave_fx = sample_at_times(rr_fx, heave_jack_times)

        eps = 1e-6
        fr_coeff_heave = fr_heave_jack_y / (fr_heave_fx + eps)
        rr_coeff_heave = rr_heave_jack_y / (rr_heave_fx + eps)
        fr_coeff_roll = fr_roll_jack_y / (fr_roll_fy + eps)
        rr_coeff_roll = rr_roll_jack_y / (rr_roll_fy + eps)

        h_cg = float(self.config["vehicle"]["h_cg"])
        track_front = float(self.config["vehicle"]["track_front"])
        track_rear = float(self.config["vehicle"]["track_rear"])
        wheelbase = float(self.config["vehicle"]["wheelbase"])
        k_sf = float(self.config["suspension"]["front"]["spring_rate"])
        k_sr = float(self.config["suspension"]["rear"]["spring_rate"])
        k_arb_f = float(self.config["suspension"]["front"]["arb_rate"])
        k_arb_r = float(self.config["suspension"]["rear"]["arb_rate"])

        ref_long = h_cg / wheelbase
        ref_roll = h_cg / ((track_front + track_rear) / 2.0)

        fr_anti_heave = 100.0 * fr_coeff_heave / ref_long
        rr_anti_heave = 100.0 * rr_coeff_heave / ref_long
        fr_anti_roll = 100.0 * fr_coeff_roll / ref_roll
        rr_anti_roll = 100.0 * rr_coeff_roll / ref_roll

        mask_fr_h = np.abs(fr_heave_fx) > 1e-3
        mask_rr_h = np.abs(rr_heave_fx) > 1e-3
        fr_heave_x = fr_heave_jack_x[mask_fr_h]
        rr_heave_x = rr_heave_jack_x[mask_rr_h]
        fr_anti_heave = fr_anti_heave[mask_fr_h]
        rr_anti_heave = rr_anti_heave[mask_rr_h]

        mask_fr = np.abs(fr_roll_fy) > 1e-3
        mask_rr = np.abs(rr_roll_fy) > 1e-3
        fr_roll_x = fr_roll_jack_x[mask_fr]
        rr_roll_x = rr_roll_jack_x[mask_rr]
        fr_anti_roll = fr_anti_roll[mask_fr]
        rr_anti_roll = rr_anti_roll[mask_rr]

        def compute_motion_ratio_series(
            spring_signal: np.ndarray,
            wheel_signal: np.ndarray,
            sample_times: Sequence[float],
        ) -> tuple[np.ndarray, np.ndarray, float]:
            spring = sample_at_times(np.asarray(spring_signal, dtype=float), list(sample_times))
            wheel = sample_at_times(np.asarray(wheel_signal, dtype=float), list(sample_times))

            mask = np.isfinite(spring) & np.isfinite(wheel)
            spring = spring[mask]
            wheel = wheel[mask]

            if spring.size < 2 or wheel.size < 2 or np.nanstd(wheel) < 1e-12:
                return np.array([], dtype=float), np.array([], dtype=float), float("nan")

            idx = np.argsort(wheel)
            wheel = wheel[idx]
            spring = spring[idx]
            coeffs = np.polyfit(wheel, spring, 3)
            poly = np.poly1d(coeffs)
            dpoly = np.polyder(poly)
            ds_dw = dpoly(wheel)
            mr = 1.0 / np.abs(ds_dw)
            return wheel, mr, float(np.nanmean(mr))

        def compute_stabar_motion_ratio_series(
            stabar_signal: np.ndarray,
            roll_signal: np.ndarray,
            sample_times: Sequence[float],
        ) -> tuple[np.ndarray, np.ndarray, float]:
            stabar = sample_at_times(np.asarray(stabar_signal, dtype=float), list(sample_times))
            phi = sample_at_times(np.asarray(roll_signal, dtype=float), list(sample_times))

            mask = np.isfinite(stabar) & np.isfinite(phi)
            stabar = stabar[mask]
            phi = phi[mask]

            if stabar.size < 2 or phi.size < 2 or np.nanstd(stabar) < 1e-12 or np.nanstd(phi) < 1e-12:
                return np.array([], dtype=float), np.array([], dtype=float), float("nan")

            idx = np.argsort(phi)
            phi = phi[idx]
            stabar = stabar[idx]
            coeffs = np.polyfit(phi, stabar, 3)
            poly = np.poly1d(coeffs)
            dpoly = np.polyder(poly)
            ds_dphi = dpoly(phi)
            mr = 1.0 / np.abs(ds_dphi)
            return phi, mr, float(np.nanmean(mr))

        motion_ratio_series: dict[str, np.ndarray] = {}
        motion_ratio_means: list[float] = []
        for corner in corners:
            prefix = side_prefix(corner)
            x_mr, y_mr, mr_mean = compute_motion_ratio_series(
                corner_signal(prefix, corner, "SpringLength"),
                heave,
                heave_sample_times,
            )
            motion_ratio_series[f"{corner}_motion_ratio_x"] = x_mr
            motion_ratio_series[f"{corner}_motion_ratio_vs_heave"] = y_mr
            motion_ratio_means.append(mr_mean)

        mr_f = nanmean_or_nan(motion_ratio_means[:2])
        mr_r = nanmean_or_nan(motion_ratio_means[2:])

        stabar_motion_ratio_series: dict[str, np.ndarray] = {}
        x_smr_f, y_smr_f, smr_f = compute_stabar_motion_ratio_series(
            sig("frKnC", "stabarAngle"),
            roll,
            roll_sample_times,
        )
        x_smr_r, y_smr_r, smr_r = compute_stabar_motion_ratio_series(
            sig("rrKnC", "stabarAngle"),
            roll,
            roll_sample_times,
        )
        stabar_motion_ratio_series["fr_stabar_motion_ratio_x"] = x_smr_f
        stabar_motion_ratio_series["fr_stabar_motion_ratio_vs_roll"] = y_smr_f
        stabar_motion_ratio_series["rr_stabar_motion_ratio_x"] = x_smr_r
        stabar_motion_ratio_series["rr_stabar_motion_ratio_vs_roll"] = y_smr_r

        kw_f = k_sf / (mr_f**2)
        kw_r = k_sr / (mr_r**2)
        kphi_spr_f = 0.5 * kw_f * (track_front**2)
        kphi_spr_r = 0.5 * kw_r * (track_rear**2)
        kphi_arb_f = k_arb_f / (smr_f**2)
        kphi_arb_r = k_arb_r / (smr_r**2)
        kphi_el_f = kphi_spr_f + kphi_arb_f
        kphi_el_r = kphi_spr_r + kphi_arb_r

        n_roll = min(len(fr_anti_roll), len(rr_anti_roll))
        af = fr_anti_roll[:n_roll] / 100.0
        ar = rr_anti_roll[:n_roll] / 100.0
        kphi_eff_f = kphi_el_f * (1.0 + af)
        kphi_eff_r = kphi_el_r * (1.0 + ar)
        lltd_roll = kphi_eff_f / (kphi_eff_f + kphi_eff_r + 1e-9)

        gains = {
            "camber_gain_heave_rad_per_m": compute_gain(
                heave_vals, heave_series["fr_l_camber_vs_heave"]
            ),
            "toe_gain_heave_rad_per_m": compute_gain(
                heave_vals, heave_series["fr_l_toe_vs_heave"]
            ),
            "caster_gain_heave_rad_per_m": compute_gain(
                heave_vals, heave_series["fr_l_caster_vs_heave"]
            ),
            "kpi_gain_heave_rad_per_m": compute_gain(
                heave_vals, heave_series["fr_l_kpi_vs_heave"]
            ),
            "trail_gain_heave_m_per_m": compute_gain(
                heave_vals, heave_series["fr_l_trail_vs_heave"]
            ),
            "scrub_gain_heave_m_per_m": compute_gain(
                heave_vals, heave_series["fr_l_scrub_vs_heave"]
            ),
            "camber_gain_roll_rad_per_rad": compute_gain(
                roll_vals, roll_series["fr_l_camber_vs_roll"]
            ),
            "toe_gain_roll_rad_per_rad": compute_gain(
                roll_vals, roll_series["fr_l_toe_vs_roll"]
            ),
            "caster_gain_roll_rad_per_rad": compute_gain(
                roll_vals, roll_series["fr_l_caster_vs_roll"]
            ),
            "kpi_gain_roll_rad_per_rad": compute_gain(
                roll_vals, roll_series["fr_l_kpi_vs_roll"]
            ),
            "trail_gain_roll_m_per_rad": compute_gain(
                roll_vals, roll_series["fr_l_trail_vs_roll"]
            ),
            "scrub_gain_roll_m_per_rad": compute_gain(
                roll_vals, roll_series["fr_l_scrub_vs_roll"]
            ),
        }

        summary = {
            **{k: float(v) for k, v in gains.items()},
            "avg_anti_dive_pct": float(np.mean(fr_anti_heave)),
            "avg_anti_squat_pct": float(np.mean(rr_anti_heave)),
            "avg_anti_roll_front_pct": float(np.mean(fr_anti_roll)),
            "avg_anti_roll_rear_pct": float(np.mean(rr_anti_roll)),
            "avg_lltd_front_frac": float(np.mean(lltd_roll)),
            "avg_lltd_front_pct": float(100.0 * np.mean(lltd_roll)),
            "avg_longitudinal_jacking_coeff_front": float(np.mean(fr_coeff_heave)),
            "avg_longitudinal_jacking_coeff_rear": float(np.mean(rr_coeff_heave)),
            "avg_lateral_jacking_coeff_front": float(np.mean(fr_coeff_roll)),
            "avg_lateral_jacking_coeff_rear": float(np.mean(rr_coeff_roll)),
            "avg_motion_ratio_front": float(mr_f),
            "avg_motion_ratio_rear": float(mr_r),
            "avg_stabar_motion_ratio_front": float(smr_f),
            "avg_stabar_motion_ratio_rear": float(smr_r),
            "spring_roll_stiffness_front_Nm_per_rad": float(kphi_spr_f),
            "spring_roll_stiffness_rear_Nm_per_rad": float(kphi_spr_r),
            "arb_roll_stiffness_front_Nm_per_rad": float(kphi_arb_f),
            "arb_roll_stiffness_rear_Nm_per_rad": float(kphi_arb_r),
            "elastic_roll_stiffness_front_Nm_per_rad": float(kphi_el_f),
            "elastic_roll_stiffness_rear_Nm_per_rad": float(kphi_el_r),
        }

        series: dict[str, np.ndarray] = {
            "heave": heave_vals,
            "roll": roll_vals,
            **heave_series,
            **roll_series,
            **motion_ratio_series,
            **stabar_motion_ratio_series,
            "fr_jacking_vs_heave_x": fr_heave_x,
            "rr_jacking_vs_heave_x": rr_heave_x,
            "fr_anti_vs_heave": fr_anti_heave,
            "rr_anti_vs_heave": rr_anti_heave,
            "fr_jacking_vs_roll_x": fr_roll_x,
            "rr_jacking_vs_roll_x": rr_roll_x,
            "fr_anti_vs_roll": fr_anti_roll,
            "rr_anti_vs_roll": rr_anti_roll,
            "lltd_vs_roll_x": fr_roll_x[:n_roll],
            "lltd_vs_roll": lltd_roll,
        }

        return summary, series


def main(path: str | Path | None = None) -> dict[str, Any]:
    config_path = Path(path) if path is not None else DEFAULT_CONFIG_PATH
    config = load_config(config_path)

    result = FourPostEvalSim(config).run()

    if _as_mapping(config.get("report"), name="report").get("enabled", True):
        ReportEngine(config).build(result)

    return result


if __name__ == "__main__":
    path = sys.argv[1] if len(sys.argv) > 1 else None
    main(path)
