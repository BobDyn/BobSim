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
    def _close(a: float, b: float, tol: float = 1e-12) -> bool:
        return abs(a - b) <= tol

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

    # Summary
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

            # NEW
            "ay_fit_error": [],
            "yaw_fit_error": [],
        }

        summary = {"n_cases": len(results)}

        step_found = one_found = cont_found = False

        # ============================================================
        # COLLECT
        # ============================================================
        for r in results:
            t = np.array(r["time"])
            steer = np.array(r["iso.handwheelAngle"])
            ay = np.array(r["iso.accY"])
            yaw = np.array(r["iso.yawVel"])

            if (not step_found) and r.get("is_step", False):
                series["step_time"], series["step_steer"], series["step_ay"], series["step_yaw"] = t, steer, ay, yaw
                step_found = True

            if (not one_found) and r.get("is_one_period", False):
                series["one_time"], series["one_steer"], series["one_ay"], series["one_yaw"] = t, steer, ay, yaw
                one_found = True

            if (not cont_found) and r.get("is_continuous", False):
                series["cont_time"], series["cont_steer"], series["cont_ay"], series["cont_yaw"] = t, steer, ay, yaw
                cont_found = True

            if self._include_in_freq_response(r):
                metrics = self._continuous_metrics(r)

                series["freq"].append(metrics["freq"])
                series["ay_gain"].append(metrics["ay_gain"])
                series["yaw_gain"].append(metrics["yaw_gain"])
                series["ay_phase"].append(metrics["ay_phase"])
                series["yaw_phase"].append(metrics["yaw_phase"])

                # NEW
                series["ay_fit_error"].append(metrics.get("ay_fit_error", np.nan))
                series["yaw_fit_error"].append(metrics.get("yaw_fit_error", np.nan))

        # ============================================================
        # SORT + WRAP
        # ============================================================
        for k in ["freq", "ay_gain", "yaw_gain", "ay_phase", "yaw_phase"]:
            series[k] = np.array(series[k], dtype=float)

        if len(series["freq"]) > 0:
            idx = np.argsort(series["freq"])
            for k in ["freq", "ay_gain", "yaw_gain", "ay_phase", "yaw_phase"]:
                series[k] = series[k][idx]

            def wrap(phi):
                return (phi + 180.0) % 360.0 - 180.0

            series["ay_phase"] = wrap(series["ay_phase"])
            series["yaw_phase"] = wrap(series["yaw_phase"])

        # ============================================================
        # STEP METRICS
        # ============================================================
        if len(series["step_time"]) > 0:
            t = series["step_time"]
            ay = series["step_ay"]
            steer = series["step_steer"]

            ay_ss = np.mean(ay[-20:])
            ay_peak = np.max(np.abs(ay))

            overshoot = (ay_peak - abs(ay_ss)) / abs(ay_ss) * 100 if abs(ay_ss) > 1e-8 else np.nan

            tol = 0.05 * abs(ay_ss)
            settling_time = next((t[i] for i in range(len(ay)) if np.all(np.abs(ay[i:] - ay_ss) < tol)), np.nan)

            ay_10, ay_90 = 0.1 * ay_ss, 0.9 * ay_ss
            idx10 = np.where(ay >= ay_10)[0]
            idx90 = np.where(ay >= ay_90)[0]

            rise_time = (t[idx90[0]] - t[idx10[0]]) if len(idx10) and len(idx90) else np.nan

            steer_ss = np.mean(steer[-20:])
            gain_ss = ay_ss / steer_ss if abs(steer_ss) > 1e-8 else np.nan

            summary.update({
                "ay_peak": float(ay_peak),
                "ay_ss": float(ay_ss),
                "overshoot_pct": float(overshoot),
                "settling_time_s": float(settling_time),
                "rise_time_s": float(rise_time),
                "ay_gain_ss": float(gain_ss),
            })

        # ============================================================
        # FREQUENCY METRICS
        # ============================================================
        if len(series["freq"]) > 0:
            f = series["freq"]
            ay_gain = series["ay_gain"]
            yaw_gain = series["yaw_gain"]
            ay_phase = series["ay_phase"]
            yaw_phase = series["yaw_phase"]

            idx_peak_ay = np.argmax(ay_gain)
            idx_peak_yaw = np.argmax(yaw_gain)
            idx_1hz = np.argmin(np.abs(f - 1.0))
            idx_low = 0

            # --- gains
            ay_gain_dc = ay_gain[idx_low]
            yaw_gain_dc = yaw_gain[idx_low]

            # --- bandwidth
            target = 0.707 * ay_gain[idx_peak_ay]
            bandwidth = next((f[i] for i in range(idx_peak_ay, len(f)) if ay_gain[i] <= target), np.nan)

            # --- lag
            def phase_to_lag(phi, freq):
                return -phi / 360.0 / freq if freq > 0 else np.nan

            ay_lag = phase_to_lag(ay_phase[idx_1hz], f[idx_1hz])
            yaw_lag = phase_to_lag(yaw_phase[idx_1hz], f[idx_1hz])

            # --- slopes
            def safe_log_slope(x, y):
                mask = (x > 0) & (y > 0)
                if np.sum(mask) < 2:
                    return np.nan
                lx = np.log10(x[mask])
                ly = y[mask]
                return np.polyfit(lx, ly, 1)[0]

            ay_gain_slope = safe_log_slope(f, 20*np.log10(ay_gain))
            yaw_gain_slope = safe_log_slope(f, 20*np.log10(yaw_gain))

            ay_phase_slope = safe_log_slope(f, np.abs(ay_phase))
            yaw_phase_slope = safe_log_slope(f, np.abs(yaw_phase))

            # --- phase crossover
            def closest_cross(x, y, target):
                idx = np.argmin(np.abs(y - target))
                return x[idx]

            ay_cross = closest_cross(f, ay_phase, -45.0)
            yaw_cross = closest_cross(f, yaw_phase, -45.0)

            # --- coupling
            yaw_to_ay_ratio = yaw_gain[idx_1hz] / ay_gain[idx_1hz] if ay_gain[idx_1hz] > 1e-8 else np.nan
            yaw_to_ay_lag = ay_lag - yaw_lag

            # --- fit quality
            summary["ay_fit_error"] = float(np.nanmean(series["ay_fit_error"]))
            summary["yaw_fit_error"] = float(np.nanmean(series["yaw_fit_error"]))

            summary.update({
                "ay_gain_dc": float(ay_gain_dc),
                "yaw_gain_dc": float(yaw_gain_dc),

                "ay_gain_peak": float(ay_gain[idx_peak_ay]),
                "ay_gain_peak_freq": float(f[idx_peak_ay]),

                "yaw_gain_peak": float(yaw_gain[idx_peak_yaw]),
                "yaw_gain_peak_freq": float(f[idx_peak_yaw]),

                "bandwidth_hz": float(bandwidth),

                "ay_phase_1hz": float(ay_phase[idx_1hz]),
                "yaw_phase_1hz": float(yaw_phase[idx_1hz]),

                "ay_lag_1hz": float(ay_lag),
                "yaw_lag_1hz": float(yaw_lag),

                "ay_phase_45_freq": float(ay_cross),
                "yaw_phase_45_freq": float(yaw_cross),

                "ay_gain_slope": float(ay_gain_slope),
                "yaw_gain_slope": float(yaw_gain_slope),

                "ay_phase_slope": float(ay_phase_slope),
                "yaw_phase_slope": float(yaw_phase_slope),

                "yaw_to_ay_lag": float(yaw_to_ay_lag),
                "yaw_to_ay_ratio": float(yaw_to_ay_ratio),
            })

        return {"summary": summary, "series": series}

    # ============================================================
    # CONTINUOUS METRICS (ISO-CORRECT)
    # ============================================================

    def _continuous_metrics(self, r):

        import numpy as np

        t = np.array(r["time"])
        steer = np.array(r["iso.handwheelAngle"])
        ay = np.array(r["iso.accY"])
        yaw = np.array(r["iso.yawVel"])

        freq = r["steerFreq"]
        step_time = r["stepTime"]
        period = 1.0 / freq
        n_cycles = r["nCycles"]

        # ============================================================
        # WINDOW SELECTION (clean steady-state cycles)
        # ============================================================

        cycles_to_use = 2

        end = step_time + n_cycles * period
        end = step_time + np.floor((end - step_time) / period) * period
        start = end - cycles_to_use * period

        mask = (t >= start) & (t <= end)

        if np.sum(mask) < 10:
            mask = t >= (t[-1] - 2 * period)

        t = t[mask]
        steer = steer[mask]
        ay = ay[mask]
        yaw = yaw[mask]

        # shift time for conditioning
        t = t - t[0]

        # ============================================================
        # SINE FIT (WITH DC OFFSET TERM)
        # ============================================================

        def sine_fit(x, t, freq):
            omega = 2 * np.pi * freq

            s = np.sin(omega * t)
            c = np.cos(omega * t)

            # include DC offset term
            M = np.vstack([s, c, np.ones_like(t)]).T

            coeffs, _, _, _ = np.linalg.lstsq(M, x, rcond=None)
            a, b, c0 = coeffs

            amp = np.sqrt(a**2 + b**2)
            phase = np.degrees(np.arctan2(b, a))

            # reconstructed signal
            fit = a * s + b * c + c0

            # normalized fit error (very useful metric)
            err = np.linalg.norm(x - fit) / np.linalg.norm(x)

            return amp, phase, fit, err

        steer_amp, steer_phase, steer_fit, steer_err = sine_fit(steer, t, freq)

        if steer_amp <= 1e-12:
            return {
                "freq": freq,
                "ay_gain": np.nan,
                "yaw_gain": np.nan,
                "ay_phase": np.nan,
                "yaw_phase": np.nan,
            }

        ay_amp, ay_phase, ay_fit, ay_err = sine_fit(ay, t, freq)
        yaw_amp, yaw_phase, yaw_fit, yaw_err = sine_fit(yaw, t, freq)

        # ============================================================
        # RELATIVE PHASE
        # ============================================================

        ay_phase -= steer_phase
        yaw_phase -= steer_phase

        def wrap(p):
            return (p + 180) % 360 - 180

        ay_phase = wrap(ay_phase)
        yaw_phase = wrap(yaw_phase)

        return {
            "freq": freq,
            "ay_gain": ay_amp / steer_amp,
            "yaw_gain": yaw_amp / steer_amp,
            "ay_phase": ay_phase,
            "yaw_phase": yaw_phase,
            # optional but HIGHLY useful:
            "ay_fit_error": ay_err,
            "yaw_fit_error": yaw_err,
        }