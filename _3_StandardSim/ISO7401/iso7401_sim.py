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

    # ============================================================
    # SUMMARIZATION
    # ============================================================
    def summarize(self, results):
        series = {
            # =========================
            # STEP
            # =========================
            "step_time": [],
            "step_steer": [],
            "step_ay": [],
            "step_yaw": [],
            # =========================
            # ONE PERIOD
            # =========================
            "one_time": [],
            "one_steer": [],
            "one_ay": [],
            "one_yaw": [],
            # =========================
            # CONTINUOUS (for plotting)
            # =========================
            "cont_time": [],
            "cont_steer": [],
            "cont_ay": [],
            "cont_yaw": [],
            # =========================
            # FREQUENCY RESPONSE
            # =========================
            "freq": [],
            "ay_gain": [],
            "yaw_gain": [],
            "ay_phase": [],
            "yaw_phase": [],
        }

        summary = {
            "n_cases": len(results),
        }

        step_found = False
        one_found = False
        cont_found = False

        for r in results:
            t = np.array(r["time"])
            steer = np.array(r["iso.handwheelAngle"])
            ay = np.array(r["iso.accY"])
            yaw = np.array(r["iso.yawVel"])

            # =========================
            # STEP REPRESENTATIVE
            # =========================
            if (not step_found) and self._is_representative_step(r):
                series["step_time"] = t
                series["step_steer"] = steer
                series["step_ay"] = ay
                series["step_yaw"] = yaw
                step_found = True

            # =========================
            # ONE PERIOD REPRESENTATIVE
            # =========================
            if (not one_found) and self._is_representative_one_period(r):
                series["one_time"] = t
                series["one_steer"] = steer
                series["one_ay"] = ay
                series["one_yaw"] = yaw
                one_found = True

            # =========================
            # CONTINUOUS REPRESENTATIVE
            # =========================
            if (not cont_found) and self._is_representative_continuous(r):
                series["cont_time"] = t
                series["cont_steer"] = steer
                series["cont_ay"] = ay
                series["cont_yaw"] = yaw
                cont_found = True

            # =========================
            # CONTINUOUS METRICS
            # Only include fixed amplitude / fixed direction
            # =========================
            if self._include_in_freq_response(r):
                metrics = self._continuous_metrics(r)

                series["freq"].append(metrics["freq"])
                series["ay_gain"].append(metrics["ay_gain"])
                series["yaw_gain"].append(metrics["yaw_gain"])
                series["ay_phase"].append(metrics["ay_phase"])
                series["yaw_phase"].append(metrics["yaw_phase"])

        # ============================================================
        # FALLBACKS
        # ============================================================
        if not step_found:
            for r in results:
                if r["mode"] == "step":
                    series["step_time"] = np.array(r["time"])
                    series["step_steer"] = np.array(r["iso.handwheelAngle"])
                    series["step_ay"] = np.array(r["iso.accY"])
                    series["step_yaw"] = np.array(r["iso.yawVel"])
                    break

        if not one_found:
            for r in results:
                if r["mode"] == "sine_one_period":
                    series["one_time"] = np.array(r["time"])
                    series["one_steer"] = np.array(r["iso.handwheelAngle"])
                    series["one_ay"] = np.array(r["iso.accY"])
                    series["one_yaw"] = np.array(r["iso.yawVel"])
                    break

        if not cont_found:
            for r in results:
                if r["mode"] == "continuous_sine":
                    series["cont_time"] = np.array(r["time"])
                    series["cont_steer"] = np.array(r["iso.handwheelAngle"])
                    series["cont_ay"] = np.array(r["iso.accY"])
                    series["cont_yaw"] = np.array(r["iso.yawVel"])
                    break

        # ============================================================
        # SORT / UNWRAP FREQUENCY RESPONSE
        # ============================================================
        for k in ["freq", "ay_gain", "yaw_gain", "ay_phase", "yaw_phase"]:
            series[k] = np.array(series[k], dtype=float)

        if len(series["freq"]) > 0:
            idx = np.argsort(series["freq"])

            # ============================================================
            # SORT / WRAP FREQUENCY RESPONSE
            # ============================================================
            for k in ["freq", "ay_gain", "yaw_gain", "ay_phase", "yaw_phase"]:
                series[k] = np.array(series[k], dtype=float)

            if len(series["freq"]) > 0:
                idx = np.argsort(series["freq"])

                for k in ["freq", "ay_gain", "yaw_gain", "ay_phase", "yaw_phase"]:
                    series[k] = series[k][idx]

                # --------------------------------------------------------
                # PHASE WRAPPING (preferred for readability)
                # Wrap to [-180, 180]
                # --------------------------------------------------------
                def wrap_phase_deg(phi):
                    return (phi + 180.0) % 360.0 - 180.0

                series["ay_phase"] = wrap_phase_deg(series["ay_phase"])
                series["yaw_phase"] = wrap_phase_deg(series["yaw_phase"])
        
        # -------------------------
        # STEP METRICS
        # -------------------------
        if len(series["step_time"]) > 0:
            t = series["step_time"]
            ay = series["step_ay"]
            steer = series["step_steer"]

            ay_ss = np.mean(ay[-20:])
            ay_peak = np.max(ay)

            overshoot = (ay_peak - ay_ss) / ay_ss * 100 if ay_ss != 0 else np.nan

            # settling time (5%)
            tol = 0.05 * abs(ay_ss)
            settling_time = np.nan
            for i in range(len(ay)):
                if np.all(np.abs(ay[i:] - ay_ss) < tol):
                    settling_time = t[i]
                    break

            # rise time (10–90%)
            ay_10 = 0.1 * ay_ss
            ay_90 = 0.9 * ay_ss

            idx10 = np.where(ay >= ay_10)[0]
            idx90 = np.where(ay >= ay_90)[0]

            if len(idx10) > 0 and len(idx90) > 0:
                t10 = t[idx10[0]]
                t90 = t[idx90[0]]
                rise_time = t90 - t10
            else:
                rise_time = np.nan

            # steady-state gain
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
        
        # -------------------------
        # FREQUENCY METRICS
        # -------------------------
        if len(series["freq"]) > 0:
            f = series["freq"]
            ay_gain = series["ay_gain"]
            yaw_gain = series["yaw_gain"]
            ay_phase = series["ay_phase"]

            idx_peak_ay = np.argmax(ay_gain)
            idx_peak_yaw = np.argmax(yaw_gain)

            idx_1hz = np.argmin(np.abs(f - 1.0))
            idx_low = 0  # lowest freq (0.05 Hz)

            # bandwidth (-3 dB ≈ 0.707 of peak)
            peak = ay_gain[idx_peak_ay]
            target = 0.707 * peak

            bandwidth = np.nan
            for i in range(len(f)):
                if ay_gain[i] <= target:
                    bandwidth = f[i]
                    break

            summary.update({
                "ay_gain_peak": float(ay_gain[idx_peak_ay]),
                "ay_gain_peak_freq": float(f[idx_peak_ay]),
                "yaw_gain_peak": float(yaw_gain[idx_peak_yaw]),
                "yaw_gain_peak_freq": float(f[idx_peak_yaw]),

                "ay_gain_lowfreq": float(ay_gain[idx_low]),
                "ay_phase_1hz": float(ay_phase[idx_1hz]),

                "bandwidth_hz": float(bandwidth),
            })

        return {
            "summary": summary,
            "series": series,
        }

    # ============================================================
    # CONTINUOUS METRICS (ISO-CORRECT)
    # ============================================================

    def _continuous_metrics(self, r):
        t = np.array(r["time"])
        steer = np.array(r["iso.handwheelAngle"])
        ay = np.array(r["iso.accY"])
        yaw = np.array(r["iso.yawVel"])

        freq = r["steerFreq"]
        step_time = r["stepTime"]

        period = 1.0 / freq
        n_cycles = r["nCycles"]

        # Window selection logic
        period = 1.0 / freq
        n_cycles = r["nCycles"]

        # how many cycles to use for FFT
        cycles_to_use = 2  # tune

        # compute ideal end time
        end = step_time + n_cycles * period

        # snap end to nearest full cycle boundary
        end = step_time + np.floor((end - step_time) / period) * period

        # take last N full cycles
        start = end - cycles_to_use * period

        mask = (t >= start) & (t <= end)

        if np.sum(mask) < 10:
            # fallback: use last two periods
            mask = t >= (t[-1] - 2 * period)

        t = t[mask]
        steer = steer[mask]
        ay = ay[mask]
        yaw = yaw[mask]

        # amplitudes
        steer_amp = (np.max(steer) - np.min(steer)) / 2
        ay_amp = (np.max(ay) - np.min(ay)) / 2
        yaw_amp = (np.max(yaw) - np.min(yaw)) / 2

        if steer_amp <= 1e-12:
            return {
                "freq": freq,
                "ay_gain": np.nan,
                "yaw_gain": np.nan,
                "ay_phase": np.nan,
                "yaw_phase": np.nan,
            }

        # phase via FFT
        def phase(x, y):

            X = np.fft.rfft(x - np.mean(x))
            Y = np.fft.rfft(y - np.mean(y))

            idx = np.argmax(np.abs(X))
            phi = np.angle(Y[idx]) - np.angle(X[idx])

            return np.degrees(phi)

        return {
            "freq": freq,
            "ay_gain": ay_amp / steer_amp,
            "yaw_gain": yaw_amp / steer_amp,
            "ay_phase": phase(steer, ay),
            "yaw_phase": phase(steer, yaw),
        }