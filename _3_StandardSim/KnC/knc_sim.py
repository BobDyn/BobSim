from pathlib import Path
import numpy as np

from _2_GeneralSim.general_sim import _2_GeneralSim
from _3_StandardSim.KnC.knc_schema import KNC_SCHEMA


class KnCSim:
    def __init__(self, config):
        self.config = config

        # 🔥 ISO-style: build is implicit
        build_dir = Path(__file__).parent / "build"

        self.sim_fr = _2_GeneralSim(
            build_dir=build_dir / "fr_build",
            exec_name="BobLib.Standards.FrKnC",
            simulation=config.get("simulation", {}),
        )

        self.sim_rr = _2_GeneralSim(
            build_dir=build_dir / "rr_build",
            exec_name="BobLib.Standards.RrKnC",
            simulation=config.get("simulation", {}),
        )

    # ============================================================
    # overrides
    # ============================================================
    def build_overrides(self):
        p = self.config["procedure"]

        return {
            "steerMagnitude": p["steerMagnitude"],
            "heaveMagnitude": p["heaveMagnitude"],
            "rollMagnitude": p["rollMagnitude"],
            "forceMagnitude": p["forceMagnitude"],
        }

    # ============================================================
    # run
    # ============================================================
    def run(self):
        overrides = self.build_overrides()

        fr = self.sim_fr.run_cases(
            schema=KNC_SCHEMA,
            cases=[overrides],
        )[0]

        rr = self.sim_rr.run_cases(
            schema=KNC_SCHEMA,
            cases=[overrides],
        )[0]

        return self.summarize(fr, rr, self.config)

    # ============================================================
    # summarize (FINAL - SI CLEAN)
    # ============================================================
    def summarize(self, fr, rr, config):

        vehicle_cfg = config["vehicle"]
        susp_cfg = config["suspension"]

        h_cg = float(vehicle_cfg["h_cg"])
        L = float(vehicle_cfg["wheelbase"])
        T_f = float(vehicle_cfg["track_front"])
        T_r = float(vehicle_cfg["track_rear"])

        k_sf = float(susp_cfg["front"]["spring_rate"])
        k_sr = float(susp_cfg["rear"]["spring_rate"])
        k_arb_f = float(susp_cfg["front"]["arb_rate"])
        k_arb_r = float(susp_cfg["rear"]["arb_rate"])

        def splice_signal(t, signal, windows):
            return np.concatenate([signal[(t >= t0) & (t <= t1)] for t0, t1 in windows])

        def sample_at_times(t, signal, times):
            return np.array([signal[np.argmin(np.abs(t - ti))] for ti in times])

        def compute_gain(x, y):
            coeffs = np.polyfit(x, y, 1)
            return coeffs[0]

        # ============================================================
        # TIME BASES
        # ============================================================
        t_fr = np.array(fr["time"])
        t_rr = np.array(rr["time"])

        # ============================================================
        # INPUTS
        # ============================================================
        heave_fr = -np.array(fr["knc.heave"])
        roll_fr  =  np.array(fr["knc.roll"])

        heave_rr = -np.array(rr["knc.heave"])
        roll_rr  =  np.array(rr["knc.roll"])

        # ============================================================
        # WINDOWS
        # ============================================================
        heave_windows = [(5,6),(9,10),(13,14),(17,18),(21,22),(25,26),(29,30),(33,34),(37,38),(41,42)]
        roll_windows  = [(47,50),(51,54),(55,58),(59,62),(63,66),(67,70),(71,74),(75,78),(79,82),(83,86),(87,90)]

        heave_jack_times = [3.5,7.5,11.5,15.5,19.5,23.5,27.5,31.5,35.5,39.5,43.5]
        roll_jack_times  = [48.5,52.5,56.5,60.5,64.5,68.5,72.5,76.5,80.5,84.5,88.5]

        # ============================================================
        # SIGNAL REGISTRY (🔥 KEY PART)
        # ============================================================
        SIGNALS = {
            "camber": "Gamma",
            "toe": "Toe",
            "caster": "Caster",
            "kpi": "Kpi",
            "trail": "MechTrail",
            "scrub": "MechScrub",
        }

        CORNERS = ["fr_l", "fr_r", "rr_l", "rr_r"]

        def get_signal(data, corner, name):
            side = "left" if "_l" in corner else "right"
            return np.array(data[f"knc.{side}{name}"])

        # ============================================================
        # HEAVE SWEEP
        # ============================================================
        heave_vals = splice_signal(t_fr, heave_fr, heave_windows)
        idx = np.argsort(heave_vals)
        heave_vals = heave_vals[idx]

        def S(x): return x[idx]

        heave_series = {}

        for key, suffix in SIGNALS.items():
            for corner in CORNERS:

                data = fr if "fr" in corner else rr
                t = t_fr if "fr" in corner else t_rr

                sig = splice_signal(t, get_signal(data, corner, suffix), heave_windows)
                heave_series[f"{corner}_{key}_vs_heave"] = S(sig)

        # ============================================================
        # ROLL SWEEP
        # ============================================================
        roll_vals = splice_signal(t_fr, roll_fr, roll_windows)
        idx_r = np.argsort(roll_vals)
        roll_vals = roll_vals[idx_r]

        def SR(x): return x[idx_r]

        roll_series = {}

        for key, suffix in SIGNALS.items():
            for corner in CORNERS:

                data = fr if "fr" in corner else rr
                t = t_fr if "fr" in corner else t_rr

                sig = splice_signal(t, get_signal(data, corner, suffix), roll_windows)
                roll_series[f"{corner}_{key}_vs_roll"] = SR(sig)

        # ============================================================
        # JACKING
        # ============================================================
        fr_jack = -np.array(fr["knc.jackingForce"])
        rr_jack = -np.array(rr["knc.jackingForce"])

        fr_heave_jack_x = sample_at_times(t_fr, heave_fr, heave_jack_times)
        fr_heave_jack_y = sample_at_times(t_fr, fr_jack, heave_jack_times)

        rr_heave_jack_x = sample_at_times(t_rr, heave_rr, heave_jack_times)
        rr_heave_jack_y = sample_at_times(t_rr, rr_jack, heave_jack_times)

        fr_roll_jack_x = sample_at_times(t_fr, roll_fr, roll_jack_times)
        fr_roll_jack_y = sample_at_times(t_fr, fr_jack, roll_jack_times)

        rr_roll_jack_x = sample_at_times(t_rr, roll_rr, roll_jack_times)
        rr_roll_jack_y = sample_at_times(t_rr, rr_jack, roll_jack_times)

        # ============================================================
        # APPLIED FORCES (fx / fy)
        # ============================================================
        fr_fy = np.array(fr["knc.fy"])
        rr_fy = np.array(rr["knc.fy"])

        # Sample Fy at same roll operating points
        fr_roll_fy = sample_at_times(t_fr, fr_fy, roll_jack_times)
        rr_roll_fy = sample_at_times(t_rr, rr_fy, roll_jack_times)

        # ============================================================
        # APPLIED FORCES (HEAVE → fx)
        # ============================================================
        fr_fx = np.array(fr["knc.fx"])
        rr_fx = np.array(rr["knc.fx"])

        # Sample Fx at same heave operating points
        fr_heave_fx = sample_at_times(t_fr, fr_fx, heave_jack_times)
        rr_heave_fx = sample_at_times(t_rr, rr_fx, heave_jack_times)

        # ============================================================
        # JACKING COEFFICIENT (HEAVE)
        # ============================================================
        eps = 1e-6

        fr_coeff_heave = fr_heave_jack_y / (fr_heave_fx + eps)
        rr_coeff_heave = rr_heave_jack_y / (rr_heave_fx + eps)

        # ============================================================
        # NORMALIZE → ANTI (%)
        # ============================================================
        ref_long = h_cg / L

        fr_anti_heave = 100.0 * fr_coeff_heave / ref_long
        rr_anti_heave = 100.0 * rr_coeff_heave / ref_long

        # ============================================================
        # CLEAN (REMOVE Fx ~ 0)
        # ============================================================
        mask_fr_h = np.abs(fr_heave_fx) > 1e-3
        mask_rr_h = np.abs(rr_heave_fx) > 1e-3

        fr_heave_x = fr_heave_jack_x[mask_fr_h]
        rr_heave_x = rr_heave_jack_x[mask_rr_h]

        fr_anti_heave = fr_anti_heave[mask_fr_h]
        rr_anti_heave = rr_anti_heave[mask_rr_h]

        fr_heave_jack_y = fr_heave_jack_y[mask_fr_h]
        rr_heave_jack_y = rr_heave_jack_y[mask_rr_h]

        # ============================================================
        # JACKING COEFFICIENT (ROLL)
        # ============================================================
        eps = 1e-6

        fr_coeff_roll = fr_roll_jack_y / (fr_roll_fy + eps)
        rr_coeff_roll = rr_roll_jack_y / (rr_roll_fy + eps)

        # ============================================================
        # NORMALIZE -> ANTI (%)
        # ============================================================
        ref = h_cg / ((T_f + T_r) / 2.0)

        fr_anti_roll = 100.0 * fr_coeff_roll / ref
        rr_anti_roll = 100.0 * rr_coeff_roll / ref

        # ============================================================
        # CLEAN (REMOVE Fy ~ 0 POINTS)
        # ============================================================
        mask_fr = np.abs(fr_roll_fy) > 1e-3
        mask_rr = np.abs(rr_roll_fy) > 1e-3

        fr_roll_x = fr_roll_jack_x[mask_fr]
        rr_roll_x = rr_roll_jack_x[mask_rr]

        fr_anti_roll = fr_anti_roll[mask_fr]
        rr_anti_roll = rr_anti_roll[mask_rr]

        fr_roll_jack_y = fr_roll_jack_y[mask_fr]
        rr_roll_jack_y = rr_roll_jack_y[mask_rr]

        # ============================================================
        # 🔥 ANTI BALANCE (ROLL)
        # ============================================================
        eps = 1e-6

        # Need matching arrays → use same mask logic already applied
        min_len = min(len(fr_anti_roll), len(rr_anti_roll))

        fr_bal = fr_anti_roll[:min_len]
        rr_bal = rr_anti_roll[:min_len]
        roll_bal = fr_roll_x[:min_len]

        anti_balance = fr_bal / (rr_bal + eps)

        # ============================================================
        # MOTION RATIO (HEAVE-ONLY, CLEAN)
        # ============================================================

        def compute_motion_ratio(t, spring_signal, wheel_signal, windows):
            # Splice
            spring = splice_signal(t, np.array(spring_signal), windows)
            wheel  = splice_signal(t, wheel_signal, windows)

            # Sort
            idx = np.argsort(wheel)
            wheel = wheel[idx]
            spring = spring[idx]

            # Fit: spring = f(wheel)
            coeffs = np.polyfit(wheel, spring, 3)
            poly = np.poly1d(coeffs)

            # ds/dw
            dpoly = np.polyder(poly)
            ds_dw = dpoly(wheel)

            # Motion ratio
            mr = 1.0 / np.abs(ds_dw)

            return wheel, mr

        def compute_stabar_motion_ratio(t, stabar_signal, roll_signal, windows):
            # Splice
            stabar = splice_signal(t, np.array(stabar_signal), windows)
            roll   = splice_signal(t, roll_signal, windows)

            # Sort
            idx = np.argsort(roll)
            roll = roll[idx]
            stabar = stabar[idx]

            # Fit: stabar = f(roll)
            coeffs = np.polyfit(roll, stabar, 3)
            poly = np.poly1d(coeffs)

            # ds/droll
            dpoly = np.polyder(poly)
            ds_dphi = dpoly(roll)

            # Motion ratio: droll/ds
            mr = 1.0 / np.abs(ds_dphi)

            return roll, mr

        motion_ratio_results = {}

        motion_ratio_results["fr_l"] = compute_motion_ratio(t_fr, fr["knc.leftSpringLength"], heave_fr, heave_windows)
        motion_ratio_results["fr_r"] = compute_motion_ratio(t_fr, fr["knc.rightSpringLength"], heave_fr, heave_windows)
        motion_ratio_results["rr_l"] = compute_motion_ratio(t_rr, rr["knc.leftSpringLength"], heave_rr, heave_windows)
        motion_ratio_results["rr_r"] = compute_motion_ratio(t_rr, rr["knc.rightSpringLength"], heave_rr, heave_windows)

        h_mr_fr_l, mr_fr_l = motion_ratio_results["fr_l"]
        h_mr_fr_r, mr_fr_r = motion_ratio_results["fr_r"]
        h_mr_rr_l, mr_rr_l = motion_ratio_results["rr_l"]
        h_mr_rr_r, mr_rr_r = motion_ratio_results["rr_r"]

        stabar_mr_results = {}

        stabar_mr_results["fr"] = compute_stabar_motion_ratio(t_fr, fr["knc.stabarAngle"], roll_fr, roll_windows)
        stabar_mr_results["rr"] = compute_stabar_motion_ratio(t_rr, rr["knc.stabarAngle"], roll_rr, roll_windows)

        h_smr_fr, smr_fr = stabar_mr_results["fr"]
        h_smr_rr, smr_rr = stabar_mr_results["rr"]

        # ============================================================
        # LLTD (ROLL)
        # ============================================================
        # Assumptions:
        # - spring_rate is spring rate at the spring [N/m]
        # - motion ratio is wheel / spring
        # - wheel rate = spring_rate / MR^2
        # - arb_rate is bar torsional stiffness [Nm/rad]
        # - stabar MR is roll / bar_angle
        # - equivalent chassis roll stiffness from bar = k_bar / MR^2
        # - anti contribution is treated as a geometric multiplier on axle load transfer
        #
        # This is a very useful engineering approximation for balance studies.

        # Use mean MR values for now (simple, robust first implementation)
        mr_f = float(np.mean([np.mean(mr_fr_l), np.mean(mr_fr_r)]))
        mr_r = float(np.mean([np.mean(mr_rr_l), np.mean(mr_rr_r)]))

        smr_f = float(np.mean(smr_fr))
        smr_r = float(np.mean(smr_rr))

        # Spring contribution -> wheel rate per wheel
        kw_f = k_sf / (mr_f ** 2)
        kw_r = k_sr / (mr_r ** 2)

        # Approximate axle roll stiffness from springs
        # Each axle contributes through two wheel rates acting across track.
        # This simple form is sufficient for relative balance studies.
        Kphi_spr_f = 0.5 * kw_f * (T_f ** 2)
        Kphi_spr_r = 0.5 * kw_r * (T_r ** 2)

        # Bar contribution -> equivalent axle roll stiffness
        Kphi_arb_f = k_arb_f / (smr_f ** 2)
        Kphi_arb_r = k_arb_r / (smr_r ** 2)

        # Elastic roll stiffness
        Kphi_el_f = Kphi_spr_f + Kphi_arb_f
        Kphi_el_r = Kphi_spr_r + Kphi_arb_r

        # Match front/rear anti arrays on a common roll axis
        n_roll = min(len(fr_anti_roll), len(rr_anti_roll), len(fr_roll_x), len(rr_roll_x))
        roll_lltd_x = fr_roll_x[:n_roll]

        Af = fr_anti_roll[:n_roll] / 100.0
        Ar = rr_anti_roll[:n_roll] / 100.0

        # Geometric multiplier:
        # more anti => more direct load transfer at that axle
        Kphi_eff_f = Kphi_el_f * (1.0 + Af)
        Kphi_eff_r = Kphi_el_r * (1.0 + Ar)

        lltd_roll = Kphi_eff_f / (Kphi_eff_f + Kphi_eff_r + 1e-9)

        # ============================================================
        # SERIES
        # ============================================================
        series = {
            "heave": heave_vals,
            "roll": roll_vals,

            **heave_series,
            **roll_series,

            # ============================================================
            # JACKING (RAW)
            # ============================================================
            "fr_jacking_vs_heave_x": fr_heave_x,
            "fr_jacking_vs_heave_y": fr_heave_jack_y,
            "rr_jacking_vs_heave_x": rr_heave_x,
            "rr_jacking_vs_heave_y": rr_heave_jack_y,

            "fr_jacking_vs_roll_x": fr_roll_x,
            "fr_jacking_vs_roll_y": fr_roll_jack_y,

            "rr_jacking_vs_roll_x": rr_roll_x,
            "rr_jacking_vs_roll_y": rr_roll_jack_y,

            # ============================================================
            # ANTI (%)
            # ============================================================
            "fr_anti_vs_heave_x": fr_heave_x,
            "fr_anti_vs_heave": fr_anti_heave,

            "rr_anti_vs_heave_x": rr_heave_x,
            "rr_anti_vs_heave": rr_anti_heave,

            "fr_anti_vs_roll": fr_anti_roll,
            "rr_anti_vs_roll": rr_anti_roll,

            "anti_balance_vs_roll_x": roll_bal,
            "anti_balance_vs_roll": anti_balance,

            # ============================================================
            # SPRING MOTION RATIOS
            # ============================================================
            "fr_l_motion_ratio_x": h_mr_fr_l,
            "fr_l_motion_ratio_vs_heave": mr_fr_l,

            "fr_r_motion_ratio_x": h_mr_fr_r,
            "fr_r_motion_ratio_vs_heave": mr_fr_r,

            "rr_l_motion_ratio_x": h_mr_rr_l,
            "rr_l_motion_ratio_vs_heave": mr_rr_l,

            "rr_r_motion_ratio_x": h_mr_rr_r,
            "rr_r_motion_ratio_vs_heave": mr_rr_r,

            # ============================================================
            # STABAR MOTION RATIOS
            # ============================================================
            "fr_stabar_motion_ratio_x": h_smr_fr,
            "fr_stabar_motion_ratio_vs_roll": smr_fr,

            "rr_stabar_motion_ratio_x": h_smr_rr,
            "rr_stabar_motion_ratio_vs_roll": smr_rr,

            # ============================================================
            # LLTD
            # ============================================================
            "lltd_vs_roll_x": roll_lltd_x,
            "lltd_vs_roll": lltd_roll,
        }

        # ============================================================
        # GAINS (SYSTEMATIC)
        # ============================================================
        gains = {}

        # --------------------------
        # HEAVE GAINS (front left reference)
        # --------------------------
        gains.update({
            "camber_gain_heave_rad_per_m":
                compute_gain(heave_vals, heave_series["fr_l_camber_vs_heave"]),

            "toe_gain_heave_rad_per_m":
                compute_gain(heave_vals, heave_series["fr_l_toe_vs_heave"]),

            "caster_gain_heave_rad_per_m":
                compute_gain(heave_vals, heave_series["fr_l_caster_vs_heave"]),

            "kpi_gain_heave_rad_per_m":
                compute_gain(heave_vals, heave_series["fr_l_kpi_vs_heave"]),

            "trail_gain_heave_m_per_m":
                compute_gain(heave_vals, heave_series["fr_l_trail_vs_heave"]),

            "scrub_gain_heave_m_per_m":
                compute_gain(heave_vals, heave_series["fr_l_scrub_vs_heave"]),
        })

        # --------------------------
        # ROLL GAINS (NOW FULLY SYMMETRIC)
        # --------------------------
        gains.update({
            "camber_gain_roll_rad_per_rad":
                compute_gain(roll_vals, roll_series["fr_l_camber_vs_roll"]),

            "toe_gain_roll_rad_per_rad":
                compute_gain(roll_vals, roll_series["fr_l_toe_vs_roll"]),

            "caster_gain_roll_rad_per_rad":
                compute_gain(roll_vals, roll_series["fr_l_caster_vs_roll"]),

            "kpi_gain_roll_rad_per_rad":
                compute_gain(roll_vals, roll_series["fr_l_kpi_vs_roll"]),

            # 🔥 NEW (symmetry fix)
            "trail_gain_roll_m_per_rad":
                compute_gain(roll_vals, roll_series["fr_l_trail_vs_roll"]),

            "scrub_gain_roll_m_per_rad":
                compute_gain(roll_vals, roll_series["fr_l_scrub_vs_roll"]),
        })


        # ============================================================
        # SUMMARY
        # ============================================================
        summary = {

            # ========================================================
            # GAINS
            # ========================================================
            **{k: float(v) for k, v in gains.items()},

            # ========================================================
            # ANTI
            # ========================================================
            "avg_anti_dive_pct": float(np.mean(fr_anti_heave)),
            "avg_anti_squat_pct": float(np.mean(rr_anti_heave)),
            "avg_anti_roll_front_pct": float(np.mean(fr_anti_roll)),
            "avg_anti_roll_rear_pct": float(np.mean(rr_anti_roll)),

            # ========================================================
            # BALANCE
            # ========================================================
            "avg_anti_balance": float(np.mean(anti_balance)),
            "avg_lltd_front_frac": float(np.mean(lltd_roll)),
            "avg_lltd_front_pct": float(100.0 * np.mean(lltd_roll)),

            # ========================================================
            # JACKING (for completeness)
            # ========================================================
            "avg_longitudinal_jacking_coeff_front": float(np.mean(fr_coeff_heave)),
            "avg_longitudinal_jacking_coeff_rear": float(np.mean(rr_coeff_heave)),
            "avg_lateral_jacking_coeff_front": float(np.mean(fr_coeff_roll)),
            "avg_lateral_jacking_coeff_rear": float(np.mean(rr_coeff_roll)),

            # ========================================================
            # MOTION RATIOS
            # ========================================================
            "avg_motion_ratio_front": float(mr_f),
            "avg_motion_ratio_rear": float(mr_r),

            "avg_stabar_motion_ratio_front": float(smr_f),
            "avg_stabar_motion_ratio_rear": float(smr_r),

            # ========================================================
            # ROLL STIFFNESS BREAKDOWN
            # ========================================================
            "spring_roll_stiffness_front_Nm_per_rad": float(Kphi_spr_f),
            "spring_roll_stiffness_rear_Nm_per_rad": float(Kphi_spr_r),

            "arb_roll_stiffness_front_Nm_per_rad": float(Kphi_arb_f),
            "arb_roll_stiffness_rear_Nm_per_rad": float(Kphi_arb_r),

            "elastic_roll_stiffness_front_Nm_per_rad": float(Kphi_el_f),
            "elastic_roll_stiffness_rear_Nm_per_rad": float(Kphi_el_r),
        }

        return {"summary": summary, "series": series}