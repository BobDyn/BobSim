from pathlib import Path
import numpy as np

from _2_GeneralSim.general_sim import _2_GeneralSim
from _3_StandardSim.ISO7401.iso7401_schema import ISO7401_SCHEMA


class ISO7401Sim:
    def __init__(self, config):
        self.config = config

        build_dir = Path(__file__).parent / "build"
        exec_name = "BobLib.Standards.ISO7401"

        self.sim = _2_GeneralSim(
            build_dir=build_dir,
            exec_name=exec_name,
            simulation=config.get("simulation", {}),
        )

    # ============================================================
    # HELPERS
    # ============================================================

    @staticmethod
    def _direction_sign(direction: str) -> int:
        d = direction.strip().lower()
        if d == "left":
            return 1
        if d == "right":
            return -1
        raise ValueError(f"Unsupported direction: {direction}")

    @staticmethod
    def _close(a: float, b: float, tol: float = 1e-6) -> bool:
        return abs(a - b) <= tol

    @staticmethod
    def _wrap_phase(phi):
        return (phi + 180.0) % 360.0 - 180.0

    @staticmethod
    def _safe_nanmean(x):
        x = np.asarray(x, dtype=float)
        if x.size == 0 or np.all(~np.isfinite(x)):
            return np.nan
        return float(np.nanmean(x))

    # ============================================================
    # CASE GENERATION
    # ============================================================

    def build_cases(self):
        test = self.config["test"]

        directions = test.get("directions", ["left", "right"])
        signs = [self._direction_sign(d) for d in directions]

        base = {
            "testVel": test["testVel"],
            "stepTime": test["stepTime"],
        }

        cases = []

        # STEP
        if test.get("run_step", True):
            for step in test["steerStep_deg"]:
                for s in signs:
                    cases.append(
                        {
                            **base,
                            "mode": "step",
                            "sinusoidal": False,
                            "steerStep": s * np.deg2rad(step),
                            "steerAmp": 0.0,
                            "steerFreq": 0.0,
                            "nCycles": 0,
                        }
                    )

        # ONE PERIOD SINE
        if test.get("run_sine_one_period", True):
            for f in test["sine_freq_hz"]:
                for amp in test["sine_amp_deg"]:
                    for s in signs:
                        cases.append(
                            {
                                **base,
                                "mode": "sine_one_period",
                                "sinusoidal": True,
                                "steerStep": 0.0,
                                "steerAmp": s * np.deg2rad(amp),
                                "steerFreq": f,
                                "nCycles": 1,
                            }
                        )

        # CONTINUOUS SINE
        if test.get("run_continuous_sine", True):
            for f in test["sweep_freq_hz"]:
                for amp in test["sweep_amp_deg"]:
                    for s in signs:
                        cases.append(
                            {
                                **base,
                                "mode": "continuous_sine",
                                "sinusoidal": True,
                                "steerStep": 0.0,
                                "steerAmp": s * np.deg2rad(amp),
                                "steerFreq": f,
                                "nCycles": test["n_cycles"],
                            }
                        )

        return cases

    # ============================================================
    # RUN
    # ============================================================

    def run(self):
        cases = self.build_cases()

        exec_cfg = self.config.get("execution", {})

        if exec_cfg.get("parallel", True):
            results = self.sim.run_cases_parallel(
                schema=ISO7401_SCHEMA,
                cases=cases,
                max_workers=exec_cfg.get("max_workers"),
                cleanup=exec_cfg.get("cleanup", False),
            )
            results = [r for r in results if r is not None]
        else:
            results = self.sim.run_cases(
                schema=ISO7401_SCHEMA,
                cases=cases,
                cleanup=exec_cfg.get("cleanup", False),
            )

        return self.summarize(results)

    # ============================================================
    # CASE SELECTION
    # ============================================================

    def _is_representative_step(self, r) -> bool:
        test = self.config["test"]
        target_step = np.deg2rad(test.get("representative_step_deg", 4.0))
        target_sign = self._direction_sign(
            test.get("representative_step_direction", "left")
        )

        return (
            r["mode"] == "step"
            and self._close(r["steerStep"], target_sign * target_step)
        )

    def _is_representative_one_period(self, r) -> bool:
        test = self.config["test"]
        target_freq = test.get("representative_one_freq_hz", 1.0)
        target_amp = np.deg2rad(test.get("representative_one_amp_deg", 4.0))
        target_sign = self._direction_sign(
            test.get("representative_one_direction", "left")
        )

        return (
            r["mode"] == "sine_one_period"
            and self._close(r["steerFreq"], target_freq)
            and self._close(r["steerAmp"], target_sign * target_amp)
        )

    def _is_representative_continuous(self, r) -> bool:
        test = self.config["test"]
        target_freq = test.get("representative_cont_freq_hz", 1.0)
        target_amp = np.deg2rad(test.get("representative_cont_amp_deg", 2.0))
        target_sign = self._direction_sign(
            test.get("representative_cont_direction", "left")
        )

        return (
            r["mode"] == "continuous_sine"
            and self._close(r["steerFreq"], target_freq)
            and self._close(r["steerAmp"], target_sign * target_amp)
        )

    def _include_in_freq_response(self, r) -> bool:
        test = self.config["test"]
        target_amp = np.deg2rad(test.get("freq_response_amp_deg", 2.0))
        target_sign = self._direction_sign(
            test.get("freq_response_direction", "left")
        )

        return (
            r["mode"] == "continuous_sine"
            and self._close(r["steerAmp"], target_sign * target_amp)
        )

    # ============================================================
    # SUMMARY
    # ============================================================

    def summarize(self, results):
        series = {
            "step_time": [],
            "step_steer": [],
            "step_ay": [],
            "step_yaw": [],
            "one_time": [],
            "one_steer": [],
            "one_ay": [],
            "one_yaw": [],
            "cont_time": [],
            "cont_steer": [],
            "cont_ay": [],
            "cont_yaw": [],
            "freq": [],
            "ay_gain": [],
            "yaw_gain": [],
            "ay_phase": [],
            "yaw_phase": [],
            "ay_fit_error": [],
            "yaw_fit_error": [],
        }

        summary = {"n_cases": len(results)}

        step_found = False
        one_found = False
        cont_found = False

        # ========================================================
        # COLLECT
        # ========================================================
        for r in results:
            t = np.array(r["time"], dtype=float)
            steer = np.array(r["iso.handwheelAngle"], dtype=float)
            ay = np.array(r["iso.accY"], dtype=float)
            yaw = np.array(r["iso.yawVel"], dtype=float)

            if (not step_found) and self._is_representative_step(r):
                series["step_time"] = t
                series["step_steer"] = steer
                series["step_ay"] = ay
                series["step_yaw"] = yaw
                step_found = True

            if (not one_found) and self._is_representative_one_period(r):
                series["one_time"] = t
                series["one_steer"] = steer
                series["one_ay"] = ay
                series["one_yaw"] = yaw
                one_found = True

            if (not cont_found) and self._is_representative_continuous(r):
                series["cont_time"] = t
                series["cont_steer"] = steer
                series["cont_ay"] = ay
                series["cont_yaw"] = yaw
                cont_found = True

            if self._include_in_freq_response(r):
                metrics = self._continuous_metrics(r)

                series["freq"].append(metrics.get("freq", np.nan))
                series["ay_gain"].append(metrics.get("ay_gain", np.nan))
                series["yaw_gain"].append(metrics.get("yaw_gain", np.nan))
                series["ay_phase"].append(metrics.get("ay_phase", np.nan))
                series["yaw_phase"].append(metrics.get("yaw_phase", np.nan))
                series["ay_fit_error"].append(metrics.get("ay_fit_error", np.nan))
                series["yaw_fit_error"].append(metrics.get("yaw_fit_error", np.nan))

        # ========================================================
        # SORT + WRAP
        # ========================================================
        for k in [
            "freq",
            "ay_gain",
            "yaw_gain",
            "ay_phase",
            "yaw_phase",
            "ay_fit_error",
            "yaw_fit_error",
        ]:
            series[k] = np.array(series[k], dtype=float)

        if len(series["freq"]) > 0:
            idx = np.argsort(series["freq"])
            for k in [
                "freq",
                "ay_gain",
                "yaw_gain",
                "ay_phase",
                "yaw_phase",
                "ay_fit_error",
                "yaw_fit_error",
            ]:
                series[k] = series[k][idx]

            series["ay_phase"] = self._wrap_phase(series["ay_phase"])
            series["yaw_phase"] = self._wrap_phase(series["yaw_phase"])

        # ========================================================
        # STEP METRICS
        # ========================================================
        if len(series["step_time"]) > 0:
            t = np.asarray(series["step_time"], dtype=float)
            ay = np.asarray(series["step_ay"], dtype=float)
            yaw = np.asarray(series["step_yaw"], dtype=float)
            steer = np.asarray(series["step_steer"], dtype=float)

            n_tail = min(20, len(t))

            ay_ss = np.mean(ay[-n_tail:])
            ay_peak = np.max(np.abs(ay))
            ay_overshoot = (
                (ay_peak - abs(ay_ss)) / abs(ay_ss) * 100.0
                if abs(ay_ss) > 1e-8 else np.nan
            )

            tol = 0.05 * abs(ay_ss)
            settling_time = next(
                (
                    t[i]
                    for i in range(len(ay))
                    if np.all(np.abs(ay[i:] - ay_ss) < tol)
                ),
                np.nan,
            ) if np.isfinite(tol) else np.nan

            ay_10 = 0.1 * ay_ss
            ay_90 = 0.9 * ay_ss

            if ay_ss >= 0:
                idx10 = np.where(ay >= ay_10)[0]
                idx90 = np.where(ay >= ay_90)[0]
            else:
                idx10 = np.where(ay <= ay_10)[0]
                idx90 = np.where(ay <= ay_90)[0]

            rise_time = (
                t[idx90[0]] - t[idx10[0]]
                if len(idx10) > 0 and len(idx90) > 0 else np.nan
            )

            steer_ss = np.mean(steer[-n_tail:])
            ay_gain_ss = ay_ss / steer_ss if abs(steer_ss) > 1e-8 else np.nan

            yaw_ss = np.mean(yaw[-n_tail:])
            yaw_peak = np.max(np.abs(yaw))
            yaw_overshoot = (
                (yaw_peak - abs(yaw_ss)) / abs(yaw_ss) * 100.0
                if abs(yaw_ss) > 1e-8 else np.nan
            )

            summary.update({
                "ay_peak": float(ay_peak),
                "ay_ss": float(ay_ss),
                "overshoot_pct": float(ay_overshoot),
                "settling_time_s": float(settling_time),
                "rise_time_s": float(rise_time),
                "ay_gain_ss": float(ay_gain_ss),
                "yaw_peak": float(yaw_peak),
                "yaw_ss": float(yaw_ss),
                "yaw_overshoot_pct": float(yaw_overshoot),
            })

        # ========================================================
        # FREQUENCY METRICS
        # ========================================================
        if len(series["freq"]) > 0:
            f = np.asarray(series["freq"], dtype=float)
            ay_gain = np.asarray(series["ay_gain"], dtype=float)
            yaw_gain = np.asarray(series["yaw_gain"], dtype=float)
            ay_phase = np.asarray(series["ay_phase"], dtype=float)
            yaw_phase = np.asarray(series["yaw_phase"], dtype=float)

            valid_gain = np.isfinite(f) & np.isfinite(ay_gain) & np.isfinite(yaw_gain)

            if np.any(valid_gain):
                f_gain = f[valid_gain]
                ay_gain_valid = ay_gain[valid_gain]
                yaw_gain_valid = yaw_gain[valid_gain]

                idx_peak_ay = np.argmax(ay_gain_valid)
                idx_peak_yaw = np.argmax(yaw_gain_valid)
                idx_low = np.argmin(f_gain)

                ay_gain_dc = ay_gain_valid[idx_low]
                yaw_gain_dc = yaw_gain_valid[idx_low]

                target = 0.707 * ay_gain_dc if np.isfinite(ay_gain_dc) else np.nan

                if np.isfinite(target):
                    bw_idx = np.where(ay_gain_valid <= target)[0]
                    bandwidth = float(f_gain[bw_idx[0]]) if len(bw_idx) > 0 else float(f_gain[-1])
                else:
                    bandwidth = np.nan

                ay_gain_peak = ay_gain_valid[idx_peak_ay]
                ay_gain_peak_freq = f_gain[idx_peak_ay]
                yaw_gain_peak = yaw_gain_valid[idx_peak_yaw]
                yaw_gain_peak_freq = f_gain[idx_peak_yaw]

                ay_gain_db = 20.0 * np.log10(np.maximum(ay_gain_valid, 1e-12))
                yaw_gain_db = 20.0 * np.log10(np.maximum(yaw_gain_valid, 1e-12))
            else:
                f_gain = np.array([], dtype=float)
                ay_gain_valid = np.array([], dtype=float)
                yaw_gain_valid = np.array([], dtype=float)
                ay_gain_dc = np.nan
                yaw_gain_dc = np.nan
                ay_gain_peak = np.nan
                ay_gain_peak_freq = np.nan
                yaw_gain_peak = np.nan
                yaw_gain_peak_freq = np.nan
                bandwidth = np.nan
                ay_gain_db = np.array([], dtype=float)
                yaw_gain_db = np.array([], dtype=float)

            # ========================================================
            # 🔥 FIX: HANDLE PHASES INDEPENDENTLY
            # ========================================================

            # --- ay phase
            valid_ay_phase = np.isfinite(f) & np.isfinite(ay_phase)

            if np.any(valid_ay_phase):
                f_ay = f[valid_ay_phase]
                ay_phase_valid = ay_phase[valid_ay_phase]
                idx_1hz_ay = np.argmin(np.abs(f_ay - 1.0))
                ay_phase_1hz = ay_phase_valid[idx_1hz_ay]
                f_1hz_ay = f_ay[idx_1hz_ay]
            else:
                f_ay = np.array([], dtype=float)
                ay_phase_valid = np.array([], dtype=float)
                ay_phase_1hz = np.nan
                f_1hz_ay = np.nan

            # --- yaw phase
            valid_yaw_phase = np.isfinite(f) & np.isfinite(yaw_phase)

            if np.any(valid_yaw_phase):
                f_yaw = f[valid_yaw_phase]
                yaw_phase_valid = yaw_phase[valid_yaw_phase]
                idx_1hz_yaw = np.argmin(np.abs(f_yaw - 1.0))
                yaw_phase_1hz = yaw_phase_valid[idx_1hz_yaw]
                f_1hz_yaw = f_yaw[idx_1hz_yaw]
            else:
                f_yaw = np.array([], dtype=float)
                yaw_phase_valid = np.array([], dtype=float)
                yaw_phase_1hz = np.nan
                f_1hz_yaw = np.nan

            def phase_to_lag(phi, freq_hz):
                if not np.isfinite(phi) or not np.isfinite(freq_hz) or freq_hz <= 0:
                    return np.nan
                return -phi / 360.0 / freq_hz

            ay_lag = phase_to_lag(ay_phase_1hz, f_1hz_ay)
            yaw_lag = phase_to_lag(yaw_phase_1hz, f_1hz_yaw)

            def safe_log_slope(x, y):
                x = np.asarray(x, dtype=float)
                y = np.asarray(y, dtype=float)
                mask = (x > 0) & np.isfinite(y)
                if np.sum(mask) < 2:
                    return np.nan
                lx = np.log10(x[mask])
                ly = y[mask]
                return float(np.polyfit(lx, ly, 1)[0])

            ay_gain_slope = safe_log_slope(f_gain, ay_gain_db)
            yaw_gain_slope = safe_log_slope(f_gain, yaw_gain_db)
            ay_phase_slope = safe_log_slope(f_ay, np.abs(ay_phase_valid))
            yaw_phase_slope = safe_log_slope(f_yaw, np.abs(yaw_phase_valid))

            def closest_cross(x, y, target):
                x = np.asarray(x, dtype=float)
                y = np.asarray(y, dtype=float)
                if len(x) == 0:
                    return np.nan
                idx = np.argmin(np.abs(y - target))
                return float(x[idx])

            ay_cross = closest_cross(f_ay, ay_phase_valid, -45.0)
            yaw_cross = closest_cross(f_yaw, yaw_phase_valid, -45.0)

            if np.any(valid_gain):
                idx_gain_1hz = np.argmin(np.abs(f_gain - 1.0))
                yaw_to_ay_ratio = (
                    yaw_gain_valid[idx_gain_1hz] / ay_gain_valid[idx_gain_1hz]
                    if ay_gain_valid[idx_gain_1hz] > 1e-8 else np.nan
                )
            else:
                yaw_to_ay_ratio = np.nan

            yaw_to_ay_lag = ay_lag - yaw_lag if np.isfinite(ay_lag) and np.isfinite(yaw_lag) else np.nan

            mask_var = np.isfinite(f_gain) & np.isfinite(ay_gain_valid) & (f_gain <= 2.0)
            if np.sum(mask_var) > 1:
                g = ay_gain_valid[mask_var]
                gain_variation = (
                    (np.max(g) - np.min(g)) / np.mean(g) * 100.0
                    if abs(np.mean(g)) > 1e-12 else np.nan
                )
            else:
                gain_variation = np.nan

            summary["ay_fit_error"] = self._safe_nanmean(series["ay_fit_error"])
            summary["yaw_fit_error"] = self._safe_nanmean(series["yaw_fit_error"])

            summary.update({
                "ay_gain_dc": float(ay_gain_dc),
                "yaw_gain_dc": float(yaw_gain_dc),
                "ay_gain_peak": float(ay_gain_peak),
                "ay_gain_peak_freq": float(ay_gain_peak_freq),
                "yaw_gain_peak": float(yaw_gain_peak),
                "yaw_gain_peak_freq": float(yaw_gain_peak_freq),
                "bandwidth_hz": float(bandwidth),
                "ay_phase_1hz": float(ay_phase_1hz),
                "yaw_phase_1hz": float(yaw_phase_1hz),
                "ay_lag_1hz": float(ay_lag),
                "yaw_lag_1hz": float(yaw_lag),
                "lag_steer_to_ay": float(ay_lag),
                "lag_steer_to_yaw": float(yaw_lag),
                "yaw_to_ay_lag": float(yaw_to_ay_lag),
                "ay_phase_45_freq": float(ay_cross),
                "yaw_phase_45_freq": float(yaw_cross),
                "ay_gain_slope": float(ay_gain_slope),
                "yaw_gain_slope": float(yaw_gain_slope),
                "ay_phase_slope": float(ay_phase_slope),
                "yaw_phase_slope": float(yaw_phase_slope),
                "yaw_to_ay_ratio": float(yaw_to_ay_ratio),
                "gain_variation_pct": float(gain_variation),
            })

        return {"summary": summary, "series": series}

    # ============================================================
    # CONTINUOUS METRICS (ISO-CORRECT)
    # ============================================================

    def _continuous_metrics(self, r):
        t = np.array(r["time"], dtype=float)
        steer = np.array(r["iso.handwheelAngle"], dtype=float)
        ay = np.array(r["iso.accY"], dtype=float)
        yaw = np.array(r["iso.yawVel"], dtype=float)

        freq = float(r["steerFreq"])
        step_time = float(r["stepTime"])
        n_cycles = int(r["nCycles"])

        if freq <= 0:
            return {
                "freq": freq,
                "ay_gain": np.nan,
                "yaw_gain": np.nan,
                "ay_phase": np.nan,
                "yaw_phase": np.nan,
                "ay_fit_error": np.nan,
                "yaw_fit_error": np.nan,
            }

        period = 1.0 / freq

        # ========================================================
        # WINDOW SELECTION (clean steady-state cycles)
        # ========================================================
        cycles_skip = int(r.get("analyze_cycles_after", 1))
        cycles_use = min(2, n_cycles - cycles_skip)

        start = step_time + cycles_skip * period
        end = start + cycles_use * period

        mask = (t >= start) & (t <= end)

        if np.sum(mask) < 10:
            mask = t >= (t[-1] - 2.0 * period)

        t = t[mask]
        steer = steer[mask]
        ay = ay[mask]
        yaw = yaw[mask]

        if len(t) < 5:
            return {
                "freq": freq,
                "ay_gain": np.nan,
                "yaw_gain": np.nan,
                "ay_phase": np.nan,
                "yaw_phase": np.nan,
                "ay_fit_error": np.nan,
                "yaw_fit_error": np.nan,
            }

        # shift time for conditioning
        t = t - t[0]

        # ========================================================
        # SINE FIT (WITH DC OFFSET TERM)
        # ========================================================
        def sine_fit(x, t_fit, freq_fit):
            omega = 2.0 * np.pi * freq_fit

            s = np.sin(omega * t_fit)
            c = np.cos(omega * t_fit)

            M = np.vstack([s, c, np.ones_like(t_fit)]).T
            coeffs, _, _, _ = np.linalg.lstsq(M, x, rcond=None)
            a, b, c0 = coeffs

            amp = np.sqrt(a**2 + b**2)
            phase = np.degrees(np.arctan2(b, a))

            fit = a * s + b * c + c0

            denom = np.linalg.norm(x)
            err = np.linalg.norm(x - fit) / denom if denom > 1e-12 else np.nan

            return amp, phase, fit, err

        steer_amp, steer_phase, _, _ = sine_fit(steer, t, freq)

        if not np.isfinite(steer_amp) or steer_amp <= 1e-12:
            return {
                "freq": freq,
                "ay_gain": np.nan,
                "yaw_gain": np.nan,
                "ay_phase": np.nan,
                "yaw_phase": np.nan,
                "ay_fit_error": np.nan,
                "yaw_fit_error": np.nan,
            }

        ay_amp, ay_phase, _, ay_err = sine_fit(ay, t, freq)
        yaw_amp, yaw_phase, _, yaw_err = sine_fit(yaw, t, freq)

        ay_phase = self._wrap_phase(ay_phase - steer_phase)
        yaw_phase = self._wrap_phase(yaw_phase - steer_phase)

        return {
            "freq": freq,
            "ay_gain": ay_amp / steer_amp if np.isfinite(ay_amp) else np.nan,
            "yaw_gain": yaw_amp / steer_amp if np.isfinite(yaw_amp) else np.nan,
            "ay_phase": ay_phase,
            "yaw_phase": yaw_phase,
            "ay_fit_error": ay_err,
            "yaw_fit_error": yaw_err,
        }