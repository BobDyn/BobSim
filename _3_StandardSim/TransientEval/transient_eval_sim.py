from __future__ import annotations

import csv
import sys
from pathlib import Path

import matplotlib as mpl
import numpy as np
import yaml

from _3_StandardSim._modelica_runner import ModelicaRunner
from _0_Utils.reporting.report_engine import ReportEngine


mpl.rcParams.update({
    "font.family": "STIXGeneral",
    "mathtext.fontset": "stix",
    "font.size": 12,
    "axes.titlesize": 13,
    "axes.labelsize": 12,
    "xtick.labelsize": 10,
    "ytick.labelsize": 10,
    "legend.fontsize": 10,
    "axes.grid": True,
    "grid.linestyle": "--",
    "grid.alpha": 0.4,
})


# Unified VehicleModel exposes scalar outputs directly.
TransientEval_SIGNALS = [
    "handwheelAngle",
    "leftSteerAngle",
    "rightSteerAngle",
    "velX",
    "velY",
    "yawVel",
    "sideslip",
    "accX",
    "accY",
    "roll",
    "handwheelTorque",
]


# These are Python/report metadata fields.
# They should NOT all be sent to Modelica as overrides.
CASE_METADATA_KEYS = [
    "mode",
    "useMode",
    "initialVel",
    "targetVel",
    "testVel",
    "stepTime",
    "steerStart",
    "sinusoidal",
    "steerStep",
    "frRampSteerHeight",
    "frRampSteerDuration",
    "steerAmp",
    "steerFreq",
    "nCycles",
    "analyze_cycles_after",
    "directionSign",
    "stopTime",
]


def load_config(path):
    path = Path(path)

    with path.open("r") as f:
        return yaml.safe_load(f)


class TransientEvalSim:
    def __init__(self, config):
        self.config = config
        self.runner = ModelicaRunner.from_config(config)

        sim_cfg = config.get("simulation", {})

        # Fallback only. Individual cases should set their own stopTime.
        self.stop_time = float(
            sim_cfg.get("stop_time", self._default_stop_time(config))
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
        return abs(float(a) - float(b)) <= tol

    @staticmethod
    def _wrap_phase(phi):
        return (phi + 180.0) % 360.0 - 180.0

    @staticmethod
    def _safe_nanmean(x):
        x = np.asarray(x, dtype=float)
        if x.size == 0 or np.all(~np.isfinite(x)):
            return np.nan
        return float(np.nanmean(x))

    @staticmethod
    def _as_list(x):
        if isinstance(x, (list, tuple)):
            return list(x)
        return [x]

    @staticmethod
    def _csv_value(value):
        if isinstance(value, np.generic):
            value = value.item()

        if isinstance(value, float) and not np.isfinite(value):
            return ""

        return value

    @staticmethod
    def _default_stop_time(config):
        test = config.get("test", {})

        step_time = float(test.get("stepTime", 1.0))
        stop_time = step_time + 5.0

        if test.get("run_continuous_sine", False):
            freqs = test.get("sweep_freq_hz", [1.0])
            f_min = min(float(f) for f in freqs)
            n_cycles = int(test.get("n_cycles", 5))
            stop_time = max(stop_time, step_time + n_cycles / f_min)

        if test.get("run_sine_one_period", False):
            freqs = test.get("sine_freq_hz", [1.0])
            f_min = min(float(f) for f in freqs)
            stop_time = max(stop_time, step_time + 1.0 / f_min)

        return stop_time

    @staticmethod
    def _step_stop_time(step_time: float) -> float:
        # Fallback stop time. VehicleModel useMode=2 may terminate earlier
        # using its internal QSS detector.
        return step_time + 5.0

    @staticmethod
    def _one_period_stop_time(step_time: float, freq_hz: float) -> float:
        # No buffer here: VehicleModel useMode=1 keeps generating sine.
        # Stop exactly after one period.
        return step_time + 1.0 / freq_hz

    @staticmethod
    def _continuous_stop_time(
        step_time: float,
        freq_hz: float,
        n_cycles: int,
    ) -> float:
        # No buffer here: VehicleModel useMode=1 keeps generating sine.
        # Stop exactly after nCycles.
        return step_time + n_cycles / freq_hz

    @staticmethod
    def _attach_case_metadata(results, metadata):
        """
        ModelicaRunner returns signal data, but may not preserve case metadata.

        The summary code needs mode/frequency/amplitude information, so we
        reattach the non-Modelica case metadata here.

        IMPORTANT:
        `metadata` is intentionally separate from the runner-facing `cases`.
        The runner-facing cases should contain only actual VehicleModel
        override parameters plus runner-special keys like stopTime.
        """
        if len(results) != len(metadata):
            raise RuntimeError(
                f"Result/metadata count mismatch: got {len(results)} results "
                f"for {len(metadata)} metadata entries."
            )

        merged = []

        for result, meta in zip(results, metadata):
            out = dict(result)

            for key in CASE_METADATA_KEYS:
                if key in meta and key not in out:
                    out[key] = meta[key]

            merged.append(out)

        return merged

    # ============================================================
    # CASE GENERATION
    # ============================================================

    def build_cases(self):
        test = self.config["test"]

        directions = test.get("directions", ["left", "right"])
        signs = [self._direction_sign(d) for d in directions]

        test_vel = float(test["testVel"])
        step_time = float(test["stepTime"])

        cases = []
        metadata = []

        # --------------------------------------------------------
        # STEP / FINITE-RATE STEP
        #
        # VehicleModel:
        #   useMode = 2 -> ramp/step steer + closed-loop velocity
        # --------------------------------------------------------
        if test.get("run_step", False):
            step_steer_deg_values = self._as_list(
                test.get(
                    "steerStep_deg",
                    test.get("step_steer_deg", [5.0]),
                )
            )

            ramp_duration = float(
                test.get(
                    "frRampSteerDuration",
                    test.get("step_ramp_duration", 0.02),
                )
            )

            for amp in step_steer_deg_values:
                for s in signs:
                    amp_deg = float(amp)
                    steer_step = s * np.deg2rad(amp_deg)
                    stop_time_case = self._step_stop_time(step_time)

                    case = self._base_case(
                        use_mode=2,
                        test_vel=test_vel,
                        step_time=step_time,
                    )

                    case.update({
                        "frRampSteerHeight": steer_step,
                        "frRampSteerDuration": ramp_duration,
                        "stopTime": stop_time_case,
                    })

                    meta = {
                        "mode": "step",
                        "useMode": 2,
                        "testVel": test_vel,
                        "targetVel": test_vel,
                        "stepTime": step_time,
                        "steerStart": step_time,
                        "sinusoidal": False,
                        "steerStep": steer_step,
                        "frRampSteerHeight": steer_step,
                        "frRampSteerDuration": ramp_duration,
                        "steerAmp": 0.0,
                        "steerFreq": 0.0,
                        "nCycles": 0,
                        "directionSign": s,
                        "stopTime": stop_time_case,
                    }

                    cases.append(case)
                    metadata.append(meta)

        # --------------------------------------------------------
        # ONE-PERIOD SINE
        #
        # VehicleModel:
        #   useMode = 1 -> open-loop sine steer + closed-loop speed
        # --------------------------------------------------------
        if test.get("run_sine_one_period", True):
            for f in test["sine_freq_hz"]:
                for amp in test["sine_amp_deg"]:
                    for s in signs:
                        freq = float(f)
                        amp_deg = float(amp)
                        steer_amp = s * np.deg2rad(amp_deg)

                        stop_time_case = self._one_period_stop_time(
                            step_time=step_time,
                            freq_hz=freq,
                        )

                        case = self._base_case(
                            use_mode=1,
                            test_vel=test_vel,
                            step_time=step_time,
                        )

                        case.update({
                            "steerAmp": steer_amp,
                            "steerFreq": freq,
                            "stopTime": stop_time_case,
                        })

                        meta = {
                            "mode": "sine_one_period",
                            "useMode": 1,
                            "testVel": test_vel,
                            "targetVel": test_vel,
                            "stepTime": step_time,
                            "steerStart": step_time,
                            "sinusoidal": True,
                            "steerStep": 0.0,
                            "steerAmp": steer_amp,
                            "steerFreq": freq,
                            "nCycles": 1,
                            "directionSign": s,
                            "stopTime": stop_time_case,
                        }

                        cases.append(case)
                        metadata.append(meta)

        # --------------------------------------------------------
        # CONTINUOUS SINE
        #
        # VehicleModel:
        #   useMode = 1 -> open-loop sine steer + closed-loop speed
        # --------------------------------------------------------
        if test.get("run_continuous_sine", True):
            for f in test["sweep_freq_hz"]:
                for amp in test["sweep_amp_deg"]:
                    for s in signs:
                        freq = float(f)
                        amp_deg = float(amp)
                        steer_amp = s * np.deg2rad(amp_deg)
                        n_cycles = int(test["n_cycles"])

                        stop_time_case = self._continuous_stop_time(
                            step_time=step_time,
                            freq_hz=freq,
                            n_cycles=n_cycles,
                        )

                        case = self._base_case(
                            use_mode=1,
                            test_vel=test_vel,
                            step_time=step_time,
                        )

                        case.update({
                            "steerAmp": steer_amp,
                            "steerFreq": freq,
                            "stopTime": stop_time_case,
                        })

                        meta = {
                            "mode": "continuous_sine",
                            "useMode": 1,
                            "testVel": test_vel,
                            "targetVel": test_vel,
                            "stepTime": step_time,
                            "steerStart": step_time,
                            "sinusoidal": True,
                            "steerStep": 0.0,
                            "steerAmp": steer_amp,
                            "steerFreq": freq,
                            "nCycles": n_cycles,
                            "analyze_cycles_after": int(
                                test.get("analyze_cycles_after", 1)
                            ),
                            "directionSign": s,
                            "stopTime": stop_time_case,
                        }

                        cases.append(case)
                        metadata.append(meta)

        return cases, metadata

    def _base_case(self, use_mode, test_vel, step_time):
        """
        Build the runner-facing case dictionary.

        IMPORTANT:
        This dictionary is passed to ModelicaRunner, and ModelicaRunner appears
        to push most case keys into the -override string. Therefore, this must
        contain only real VehicleModel parameters, plus runner-special keys
        added later such as stopTime.

        Do NOT include report metadata here:
          mode
          testVel
          stepTime
          sinusoidal
          steerStep
          directionSign
          nCycles
          etc.

        Do NOT include initialVel here either. The current generated model
        reports that initialVel is not overrideable.
        """
        return {
            "useMode": use_mode,
            "targetVel": test_vel,
            "steerStart": step_time,
        }

    # ============================================================
    # RUN
    # ============================================================

    def run(self):
        cases, metadata = self.build_cases()

        results = self.runner.run(
            signals=TransientEval_SIGNALS,
            mode="raw",
            cases=cases,
            execution=self.config.get("execution", {}),
        )

        results = self._attach_case_metadata(results, metadata)

        return self.summarize(results)

    # ============================================================
    # CASE SELECTION
    # ============================================================

    def _is_representative_step(self, r) -> bool:
        test = self.config["test"]

        step_steer_deg_values = self._as_list(
            test.get(
                "steerStep_deg",
                test.get("step_steer_deg", [5.0]),
            )
        )

        default_step_deg = float(step_steer_deg_values[0])

        target_step = np.deg2rad(
            test.get("representative_step_deg", default_step_deg)
        )

        target_sign = self._direction_sign(
            test.get("representative_step_direction", "left")
        )

        return (
            r.get("mode") == "step"
            and self._close(r.get("steerStep", np.nan), target_sign * target_step)
        )

    def _is_representative_one_period(self, r) -> bool:
        test = self.config["test"]
        target_freq = float(test.get("representative_one_freq_hz", 1.0))
        target_amp = np.deg2rad(test.get("representative_one_amp_deg", 4.0))
        target_sign = self._direction_sign(
            test.get("representative_one_direction", "left")
        )

        return (
            r.get("mode") == "sine_one_period"
            and self._close(r.get("steerFreq", np.nan), target_freq)
            and self._close(r.get("steerAmp", np.nan), target_sign * target_amp)
        )

    def _is_representative_continuous(self, r) -> bool:
        test = self.config["test"]
        target_freq = float(test.get("representative_cont_freq_hz", 1.0))
        target_amp = np.deg2rad(test.get("representative_cont_amp_deg", 2.0))
        target_sign = self._direction_sign(
            test.get("representative_cont_direction", "left")
        )

        return (
            r.get("mode") == "continuous_sine"
            and self._close(r.get("steerFreq", np.nan), target_freq)
            and self._close(r.get("steerAmp", np.nan), target_sign * target_amp)
        )

    def _include_in_freq_response(self, r) -> bool:
        test = self.config["test"]
        target_amp = np.deg2rad(test.get("freq_response_amp_deg", 2.0))
        target_sign = self._direction_sign(
            test.get("freq_response_direction", "left")
        )

        return (
            r.get("mode") == "continuous_sine"
            and self._close(r.get("steerAmp", np.nan), target_sign * target_amp)
        )

    # ============================================================
    # SIGNAL ACCESS
    # ============================================================

    @staticmethod
    def _signal(r, key):
        """
        New VehicleModel exposes scalar outputs directly, e.g. accY.

        This helper also supports legacy iso.* keys if an older result sneaks
        through, which makes the transition less brittle.
        """
        if key in r:
            return np.array(r[key], dtype=float)

        legacy_key = f"iso.{key}"
        if legacy_key in r:
            return np.array(r[legacy_key], dtype=float)

        raise KeyError(
            f"Missing signal '{key}' in result. Available keys: {sorted(r.keys())}"
        )

    # ============================================================
    # METRICS CSV
    # ============================================================

    def write_metrics_csv(self, metrics) -> Path:
        """
        Write one TransientEval metrics CSV beside the PDF report.

        This intentionally exports only report-level metric rows, not time
        histories and not raw case data.
        """
        report_cfg = self.config.get("report", {})

        report_path = Path(
            report_cfg.get(
                "output_path",
                "_3_StandardSim/results/transient_eval_report.pdf",
            )
        )

        output_dir = report_path.parent
        output_dir.mkdir(parents=True, exist_ok=True)

        output_path = output_dir / f"{report_path.stem}_metrics.csv"

        fieldnames = [
            "standard",
            "group",
            "metric",
            "value",
            "units",
            "description",
        ]

        with output_path.open("w", newline="") as f:
            writer = csv.DictWriter(f, fieldnames=fieldnames)
            writer.writeheader()
            writer.writerows(metrics)

        return output_path

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

        for r in results:
            t = np.array(r["time"], dtype=float)
            steer = self._signal(r, "handwheelAngle")
            ay = self._signal(r, "accY")
            yaw = self._signal(r, "yawVel")

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

            settling_time = (
                next(
                    (
                        t[i]
                        for i in range(len(ay))
                        if np.all(np.abs(ay[i:] - ay_ss) < tol)
                    ),
                    np.nan,
                )
                if np.isfinite(tol)
                else np.nan
            )

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
                if len(idx10) > 0 and len(idx90) > 0
                else np.nan
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
                    bandwidth = (
                        float(f_gain[bw_idx[0]])
                        if len(bw_idx) > 0
                        else float(f_gain[-1])
                    )
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
                    if ay_gain_valid[idx_gain_1hz] > 1e-8
                    else np.nan
                )
            else:
                yaw_to_ay_ratio = np.nan

            yaw_to_ay_lag = (
                ay_lag - yaw_lag
                if np.isfinite(ay_lag) and np.isfinite(yaw_lag)
                else np.nan
            )

            mask_var = np.isfinite(f_gain) & np.isfinite(ay_gain_valid) & (f_gain <= 2.0)

            if np.sum(mask_var) > 1:
                g = ay_gain_valid[mask_var]
                gain_variation = (
                    (np.max(g) - np.min(g)) / np.mean(g) * 100.0
                    if abs(np.mean(g)) > 1e-12
                    else np.nan
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

        # --------------------------------------------------------
        # CSV metric rows.
        #
        # Add/remove/reorder exported metrics here.
        # --------------------------------------------------------
        metrics = [
            {
                "standard": "TransientEval",
                "group": "general",
                "metric": "n_cases",
                "value": summary.get("n_cases", np.nan),
                "units": "count",
                "description": "Number of simulation cases included in TransientEval run",
            },

            # Step response metrics.
            {
                "standard": "TransientEval",
                "group": "step",
                "metric": "ay_peak",
                "value": summary.get("ay_peak", np.nan),
                "units": "m/s^2",
                "description": "Peak absolute lateral acceleration during representative step steer response",
            },
            {
                "standard": "TransientEval",
                "group": "step",
                "metric": "ay_ss",
                "value": summary.get("ay_ss", np.nan),
                "units": "m/s^2",
                "description": "Steady-state lateral acceleration from representative step steer response",
            },
            {
                "standard": "TransientEval",
                "group": "step",
                "metric": "ay_gain_ss",
                "value": summary.get("ay_gain_ss", np.nan),
                "units": "(m/s^2)/rad",
                "description": "Steady-state lateral acceleration gain from handwheel angle",
            },
            {
                "standard": "TransientEval",
                "group": "step",
                "metric": "overshoot_pct",
                "value": summary.get("overshoot_pct", np.nan),
                "units": "%",
                "description": "Lateral acceleration overshoot in representative step steer response",
            },
            {
                "standard": "TransientEval",
                "group": "step",
                "metric": "rise_time_s",
                "value": summary.get("rise_time_s", np.nan),
                "units": "s",
                "description": "Lateral acceleration 10-90 percent rise time",
            },
            {
                "standard": "TransientEval",
                "group": "step",
                "metric": "settling_time_s",
                "value": summary.get("settling_time_s", np.nan),
                "units": "s",
                "description": "Lateral acceleration settling time using 5 percent steady-state band",
            },
            {
                "standard": "TransientEval",
                "group": "step",
                "metric": "yaw_peak",
                "value": summary.get("yaw_peak", np.nan),
                "units": "rad/s",
                "description": "Peak absolute yaw velocity during representative step steer response",
            },
            {
                "standard": "TransientEval",
                "group": "step",
                "metric": "yaw_ss",
                "value": summary.get("yaw_ss", np.nan),
                "units": "rad/s",
                "description": "Steady-state yaw velocity from representative step steer response",
            },
            {
                "standard": "TransientEval",
                "group": "step",
                "metric": "yaw_overshoot_pct",
                "value": summary.get("yaw_overshoot_pct", np.nan),
                "units": "%",
                "description": "Yaw velocity overshoot in representative step steer response",
            },

            # Frequency response metrics.
            {
                "standard": "TransientEval",
                "group": "frequency",
                "metric": "ay_gain_dc",
                "value": summary.get("ay_gain_dc", np.nan),
                "units": "(m/s^2)/rad",
                "description": "Low-frequency lateral acceleration gain from handwheel angle",
            },
            {
                "standard": "TransientEval",
                "group": "frequency",
                "metric": "yaw_gain_dc",
                "value": summary.get("yaw_gain_dc", np.nan),
                "units": "(rad/s)/rad",
                "description": "Low-frequency yaw velocity gain from handwheel angle",
            },
            {
                "standard": "TransientEval",
                "group": "frequency",
                "metric": "ay_gain_peak",
                "value": summary.get("ay_gain_peak", np.nan),
                "units": "(m/s^2)/rad",
                "description": "Peak lateral acceleration frequency response gain",
            },
            {
                "standard": "TransientEval",
                "group": "frequency",
                "metric": "ay_gain_peak_freq",
                "value": summary.get("ay_gain_peak_freq", np.nan),
                "units": "Hz",
                "description": "Frequency at peak lateral acceleration gain",
            },
            {
                "standard": "TransientEval",
                "group": "frequency",
                "metric": "yaw_gain_peak",
                "value": summary.get("yaw_gain_peak", np.nan),
                "units": "(rad/s)/rad",
                "description": "Peak yaw velocity frequency response gain",
            },
            {
                "standard": "TransientEval",
                "group": "frequency",
                "metric": "yaw_gain_peak_freq",
                "value": summary.get("yaw_gain_peak_freq", np.nan),
                "units": "Hz",
                "description": "Frequency at peak yaw velocity gain",
            },
            {
                "standard": "TransientEval",
                "group": "frequency",
                "metric": "bandwidth_hz",
                "value": summary.get("bandwidth_hz", np.nan),
                "units": "Hz",
                "description": "Approximate -3 dB lateral acceleration bandwidth",
            },
            {
                "standard": "TransientEval",
                "group": "frequency",
                "metric": "ay_phase_1hz",
                "value": summary.get("ay_phase_1hz", np.nan),
                "units": "deg",
                "description": "Lateral acceleration phase relative to handwheel angle near 1 Hz",
            },
            {
                "standard": "TransientEval",
                "group": "frequency",
                "metric": "yaw_phase_1hz",
                "value": summary.get("yaw_phase_1hz", np.nan),
                "units": "deg",
                "description": "Yaw velocity phase relative to handwheel angle near 1 Hz",
            },
            {
                "standard": "TransientEval",
                "group": "frequency",
                "metric": "ay_lag_1hz",
                "value": summary.get("ay_lag_1hz", np.nan),
                "units": "s",
                "description": "Equivalent lateral acceleration time lag near 1 Hz",
            },
            {
                "standard": "TransientEval",
                "group": "frequency",
                "metric": "yaw_lag_1hz",
                "value": summary.get("yaw_lag_1hz", np.nan),
                "units": "s",
                "description": "Equivalent yaw velocity time lag near 1 Hz",
            },
            {
                "standard": "TransientEval",
                "group": "frequency",
                "metric": "lag_steer_to_ay",
                "value": summary.get("lag_steer_to_ay", np.nan),
                "units": "s",
                "description": "Handwheel angle to lateral acceleration lag",
            },
            {
                "standard": "TransientEval",
                "group": "frequency",
                "metric": "lag_steer_to_yaw",
                "value": summary.get("lag_steer_to_yaw", np.nan),
                "units": "s",
                "description": "Handwheel angle to yaw velocity lag",
            },
            {
                "standard": "TransientEval",
                "group": "frequency",
                "metric": "yaw_to_ay_lag",
                "value": summary.get("yaw_to_ay_lag", np.nan),
                "units": "s",
                "description": "Additional lateral acceleration lag relative to yaw velocity",
            },
            {
                "standard": "TransientEval",
                "group": "frequency",
                "metric": "ay_phase_45_freq",
                "value": summary.get("ay_phase_45_freq", np.nan),
                "units": "Hz",
                "description": "Frequency closest to -45 degree lateral acceleration phase",
            },
            {
                "standard": "TransientEval",
                "group": "frequency",
                "metric": "yaw_phase_45_freq",
                "value": summary.get("yaw_phase_45_freq", np.nan),
                "units": "Hz",
                "description": "Frequency closest to -45 degree yaw velocity phase",
            },
            {
                "standard": "TransientEval",
                "group": "frequency",
                "metric": "ay_gain_slope",
                "value": summary.get("ay_gain_slope", np.nan),
                "units": "dB/dec",
                "description": "Lateral acceleration gain slope versus log frequency",
            },
            {
                "standard": "TransientEval",
                "group": "frequency",
                "metric": "yaw_gain_slope",
                "value": summary.get("yaw_gain_slope", np.nan),
                "units": "dB/dec",
                "description": "Yaw velocity gain slope versus log frequency",
            },
            {
                "standard": "TransientEval",
                "group": "frequency",
                "metric": "ay_phase_slope",
                "value": summary.get("ay_phase_slope", np.nan),
                "units": "deg/dec",
                "description": "Lateral acceleration phase slope versus log frequency",
            },
            {
                "standard": "TransientEval",
                "group": "frequency",
                "metric": "yaw_phase_slope",
                "value": summary.get("yaw_phase_slope", np.nan),
                "units": "deg/dec",
                "description": "Yaw velocity phase slope versus log frequency",
            },
            {
                "standard": "TransientEval",
                "group": "frequency",
                "metric": "yaw_to_ay_ratio",
                "value": summary.get("yaw_to_ay_ratio", np.nan),
                "units": "(rad/s)/(m/s^2)",
                "description": "Yaw velocity to lateral acceleration gain ratio near 1 Hz",
            },
            {
                "standard": "TransientEval",
                "group": "frequency",
                "metric": "gain_variation_pct",
                "value": summary.get("gain_variation_pct", np.nan),
                "units": "%",
                "description": "Lateral acceleration gain variation over low-frequency sweep",
            },
            {
                "standard": "TransientEval",
                "group": "quality",
                "metric": "ay_fit_error",
                "value": summary.get("ay_fit_error", np.nan),
                "units": "normalized error",
                "description": "Mean normalized sine-fit error for lateral acceleration frequency response",
            },
            {
                "standard": "TransientEval",
                "group": "quality",
                "metric": "yaw_fit_error",
                "value": summary.get("yaw_fit_error", np.nan),
                "units": "normalized error",
                "description": "Mean normalized sine-fit error for yaw velocity frequency response",
            },
        ]

        for row in metrics:
            row["value"] = self._csv_value(row["value"])

        metrics_csv_path = self.write_metrics_csv(metrics)

        print(f"📊 TransientEval metrics CSV written: {metrics_csv_path}")

        return {
            "summary": summary,
            "metrics": metrics,
            "metrics_csv_path": metrics_csv_path,
            "series": series,
        }

    # ============================================================
    # CONTINUOUS METRICS
    # ============================================================

    def _continuous_metrics(self, r):
        t = np.array(r["time"], dtype=float)
        steer = self._signal(r, "handwheelAngle")
        ay = self._signal(r, "accY")
        yaw = self._signal(r, "yawVel")

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

        t = t - t[0]

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


def main(config_path: str | Path | None = None):
    if config_path is None:
        config_path = Path("_3_StandardSim/TransientEval/transient_eval_config.yml")
    else:
        config_path = Path(config_path)

    config = load_config(config_path)

    result = TransientEvalSim(config).run()

    if config.get("report", {}).get("enabled", True):
        ReportEngine(config).build(result)

    return result


if __name__ == "__main__":
    path = sys.argv[1] if len(sys.argv) > 1 else None
    main(path)