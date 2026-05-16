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
    "stepDuration",
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

    def _representative_velocity(self, available_velocities):
        test = self.config.get("test", {})
        target = test.get(
            "metric_target_velocity_mps",
            test.get(
                "representative_testVel",
                test.get("representative_velocity_mps"),
            ),
        )

        available = [float(v) for v in available_velocities]
        if not available:
            return np.nan

        if target is None:
            return float(available[0])

        target = float(target)
        return float(min(available, key=lambda v: abs(v - target)))

    @staticmethod
    def _velocity_trend_slope(velocity_summaries, key):
        velocities = []
        values = []

        for summary in velocity_summaries:
            velocity = summary.get("velocity_mps", np.nan)
            value = summary.get(key, np.nan)

            if np.isfinite(velocity) and np.isfinite(value):
                velocities.append(float(velocity))
                values.append(float(value))

        if len(velocities) < 2:
            return np.nan

        coeffs = np.polyfit(np.asarray(velocities, dtype=float), np.asarray(values, dtype=float), 1)
        return float(coeffs[0])

    @staticmethod
    def _csv_value(value):
        if isinstance(value, np.generic):
            value = value.item()

        if isinstance(value, float) and not np.isfinite(value):
            return ""

        return value

    @staticmethod
    def _first_threshold_time(t, y, threshold):
        t = np.asarray(t, dtype=float)
        y = np.asarray(y, dtype=float)

        if len(t) == 0:
            return np.nan

        if threshold >= 0:
            idx = np.where(y >= threshold)[0]
        else:
            idx = np.where(y <= threshold)[0]

        return float(t[idx[0]]) if len(idx) > 0 else np.nan

    def _step_channel_metrics(self, t, steer, response):
        t = np.asarray(t, dtype=float)
        steer = np.asarray(steer, dtype=float)
        response = np.asarray(response, dtype=float)

        if len(t) == 0:
            return {
                "steer_ss": np.nan,
                "response_ss": np.nan,
                "response_peak": np.nan,
                "response_peak_abs": np.nan,
                "response_peak_time_s": np.nan,
                "rise_time_s": np.nan,
                "dc_gain": np.nan,
                "overshoot_abs": np.nan,
                "overshoot_pct": np.nan,
            }

        n_tail = min(20, len(t))

        steer_ss = np.mean(steer[-n_tail:])
        response_ss = np.mean(response[-n_tail:])

        steer_50_time = self._first_threshold_time(t, steer, 0.5 * steer_ss)
        response_90_time = self._first_threshold_time(t, response, 0.9 * response_ss)

        peak_idx = int(np.argmax(np.abs(response)))
        response_peak = float(response[peak_idx])
        response_peak_abs = abs(response_peak)
        response_peak_time_s = (
            float(t[peak_idx] - steer_50_time)
            if np.isfinite(steer_50_time)
            else np.nan
        )

        rise_time_s = (
            float(response_90_time - steer_50_time)
            if np.isfinite(response_90_time) and np.isfinite(steer_50_time)
            else np.nan
        )

        overshoot_abs = (
            max(0.0, response_peak_abs - abs(response_ss))
            if np.isfinite(response_peak_abs) and np.isfinite(response_ss)
            else np.nan
        )

        overshoot_pct = (
            overshoot_abs / abs(response_ss) * 100.0
            if np.isfinite(overshoot_abs) and abs(response_ss) > 1e-8
            else np.nan
        )

        dc_gain = (
            response_ss / steer_ss
            if abs(steer_ss) > 1e-8
            else np.nan
        )

        return {
            "steer_ss": float(steer_ss),
            "response_ss": float(response_ss),
            "response_peak": response_peak,
            "response_peak_abs": float(response_peak_abs),
            "response_peak_time_s": response_peak_time_s,
            "rise_time_s": rise_time_s,
            "dc_gain": float(dc_gain),
            "overshoot_abs": overshoot_abs,
            "overshoot_pct": overshoot_pct,
        }

    @staticmethod
    def _nearest_sample(freqs, values, target_freq):
        freqs = np.asarray(freqs, dtype=float)
        values = np.asarray(values, dtype=float)

        mask = np.isfinite(freqs) & np.isfinite(values)
        if not np.any(mask):
            return np.nan, np.nan

        freqs = freqs[mask]
        values = values[mask]

        idx = np.argmin(np.abs(freqs - target_freq))
        return float(values[idx]), float(freqs[idx])

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

        return stop_time

    @staticmethod
    def _step_stop_time(step_time: float) -> float:
        # Fallback stop time. VehicleModel useMode=2 may terminate earlier
        # using its internal QSS detector.
        return step_time + 5.0

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

    def _group_results_by_velocity(self, results):
        grouped = {}

        for r in results:
            try:
                velocity = float(r.get("testVel", r.get("targetVel", np.nan)))
            except (TypeError, ValueError):
                velocity = np.nan

            if not np.isfinite(velocity):
                continue

            grouped.setdefault(velocity, []).append(r)

        return grouped

    def _summarize_velocity_group(self, velocity, group_results):
        summary = {
            "velocity_mps": float(velocity),
            "testVel": float(velocity),
            "n_cases": len(group_results),
            "n_successful_cases": len(group_results),
            "n_failed_cases": 0,
        }

        plot_series = {
            "step_time": np.array([], dtype=float),
            "step_steer": np.array([], dtype=float),
            "step_ay": np.array([], dtype=float),
            "step_sideslip": np.array([], dtype=float),
            "step_yaw": np.array([], dtype=float),
            "step_roll": np.array([], dtype=float),
            "cont_time": np.array([], dtype=float),
            "cont_steer": np.array([], dtype=float),
            "cont_ay": np.array([], dtype=float),
            "cont_yaw": np.array([], dtype=float),
            "freq": np.array([], dtype=float),
            "ay_gain": np.array([], dtype=float),
            "yaw_gain": np.array([], dtype=float),
            "ay_phase": np.array([], dtype=float),
            "yaw_phase": np.array([], dtype=float),
            "ay_fit_error": np.array([], dtype=float),
            "yaw_fit_error": np.array([], dtype=float),
        }

        step_result = next(
            (r for r in group_results if self._is_representative_step(r)),
            None,
        )
        if step_result is None:
            step_result = next((r for r in group_results if r.get("mode") == "step"), None)

        cont_result = next(
            (r for r in group_results if self._is_representative_continuous(r)),
            None,
        )
        if cont_result is None:
            cont_result = next(
                (r for r in group_results if r.get("mode") == "continuous_sine"),
                None,
            )

        if cont_result is not None:
            plot_series["cont_time"] = np.array(cont_result["time"], dtype=float)
            plot_series["cont_steer"] = self._signal(cont_result, "handwheelAngle")
            plot_series["cont_ay"] = self._signal(cont_result, "accY")
            plot_series["cont_yaw"] = self._signal(cont_result, "yawVel")

        if step_result is not None:
            plot_series["step_time"] = np.array(step_result["time"], dtype=float)
            plot_series["step_steer"] = self._signal(step_result, "handwheelAngle")
            plot_series["step_ay"] = self._signal(step_result, "accY")
            plot_series["step_sideslip"] = self._signal(step_result, "sideslip")
            plot_series["step_yaw"] = self._signal(step_result, "yawVel")
            plot_series["step_roll"] = self._signal(step_result, "roll")

            t = plot_series["step_time"]
            ay = plot_series["step_ay"]
            sideslip = plot_series["step_sideslip"]
            yaw = plot_series["step_yaw"]
            roll = plot_series["step_roll"]
            steer = plot_series["step_steer"]

            ay_metrics = self._step_channel_metrics(t, steer, ay)
            sideslip_metrics = self._step_channel_metrics(t, steer, sideslip)
            yaw_metrics = self._step_channel_metrics(t, steer, yaw)
            roll_metrics = self._step_channel_metrics(t, steer, roll)

            ay_ss = ay_metrics["response_ss"]
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

            summary.update({
                "ay_peak": float(ay_metrics["response_peak_abs"]),
                "ay_ss": float(ay_ss),
                "ay_rise_time_s": float(ay_metrics["rise_time_s"]),
                "ay_peak_response_time_s": float(
                    ay_metrics["response_peak_time_s"]
                ),
                "ay_gain_dc": float(ay_metrics["dc_gain"]),
                "ay_gain_ss": float(ay_metrics["dc_gain"]),
                "ay_overshoot_pct": float(ay_metrics["overshoot_pct"]),
                "overshoot_pct": float(ay_metrics["overshoot_pct"]),
                "settling_time_s": float(settling_time),
                "rise_time_s": float(ay_metrics["rise_time_s"]),
                "sideslip_ss": float(sideslip_metrics["response_ss"]),
                "sideslip_rise_time_s": float(sideslip_metrics["rise_time_s"]),
                "sideslip_gain_dc": float(sideslip_metrics["dc_gain"]),
                "yaw_peak": float(yaw_metrics["response_peak_abs"]),
                "yaw_ss": float(yaw_metrics["response_ss"]),
                "yaw_rise_time_s": float(yaw_metrics["rise_time_s"]),
                "yaw_peak_response_time_s": float(
                    yaw_metrics["response_peak_time_s"]
                ),
                "yaw_gain_dc": float(yaw_metrics["dc_gain"]),
                "yaw_overshoot_rad_per_s": float(yaw_metrics["overshoot_abs"]),
                "yaw_overshoot_pct": float(yaw_metrics["overshoot_pct"]),
                "roll_peak": float(roll_metrics["response_peak_abs"]),
                "roll_ss": float(roll_metrics["response_ss"]),
                "roll_rise_time_s": float(roll_metrics["rise_time_s"]),
                "roll_gain_dc": float(roll_metrics["dc_gain"]),
                "roll_overshoot_rad": float(roll_metrics["overshoot_abs"]),
                "roll_overshoot_pct": float(roll_metrics["overshoot_pct"]),
            })

        freq_results = [
            r for r in group_results if self._include_in_freq_response(r)
        ]
        if freq_results:
            freq_vals = []
            ay_gain_vals = []
            yaw_gain_vals = []
            ay_phase_vals = []
            yaw_phase_vals = []
            ay_err_vals = []
            yaw_err_vals = []

            for r in freq_results:
                metrics = self._continuous_metrics(r)
                freq_vals.append(metrics.get("freq", np.nan))
                ay_gain_vals.append(metrics.get("ay_gain", np.nan))
                yaw_gain_vals.append(metrics.get("yaw_gain", np.nan))
                ay_phase_vals.append(metrics.get("ay_phase", np.nan))
                yaw_phase_vals.append(metrics.get("yaw_phase", np.nan))
                ay_err_vals.append(metrics.get("ay_fit_error", np.nan))
                yaw_err_vals.append(metrics.get("yaw_fit_error", np.nan))

            freq = np.asarray(freq_vals, dtype=float)
            ay_gain = np.asarray(ay_gain_vals, dtype=float)
            yaw_gain = np.asarray(yaw_gain_vals, dtype=float)
            ay_phase = np.asarray(ay_phase_vals, dtype=float)
            yaw_phase = np.asarray(yaw_phase_vals, dtype=float)
            ay_fit_error = np.asarray(ay_err_vals, dtype=float)
            yaw_fit_error = np.asarray(yaw_err_vals, dtype=float)

            idx = np.argsort(freq)
            freq = freq[idx]
            ay_gain = ay_gain[idx]
            yaw_gain = yaw_gain[idx]
            ay_phase = ay_phase[idx]
            yaw_phase = yaw_phase[idx]
            ay_fit_error = ay_fit_error[idx]
            yaw_fit_error = yaw_fit_error[idx]

            ay_phase = self._wrap_phase(ay_phase)
            yaw_phase = self._wrap_phase(yaw_phase)

            plot_series.update({
                "freq": freq,
                "ay_gain": ay_gain,
                "yaw_gain": yaw_gain,
                "ay_phase": ay_phase,
                "yaw_phase": yaw_phase,
                "ay_fit_error": ay_fit_error,
                "yaw_fit_error": yaw_fit_error,
            })

            valid_gain = (
                np.isfinite(freq) & np.isfinite(ay_gain) & np.isfinite(yaw_gain)
            )

            if np.any(valid_gain):
                f_gain = freq[valid_gain]
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
                ay_gain_dc = np.nan
                yaw_gain_dc = np.nan
                ay_gain_peak = np.nan
                ay_gain_peak_freq = np.nan
                yaw_gain_peak = np.nan
                yaw_gain_peak_freq = np.nan
                bandwidth = np.nan
                ay_gain_db = np.array([], dtype=float)
                yaw_gain_db = np.array([], dtype=float)

            valid_ay_phase = np.isfinite(freq) & np.isfinite(ay_phase)
            if np.any(valid_ay_phase):
                f_ay = freq[valid_ay_phase]
                ay_phase_valid = ay_phase[valid_ay_phase]
                idx_1hz_ay = np.argmin(np.abs(f_ay - 1.0))
                ay_phase_1hz = ay_phase_valid[idx_1hz_ay]
                f_1hz_ay = f_ay[idx_1hz_ay]
            else:
                f_ay = np.array([], dtype=float)
                ay_phase_valid = np.array([], dtype=float)
                ay_phase_1hz = np.nan
                f_1hz_ay = np.nan

            valid_yaw_phase = np.isfinite(freq) & np.isfinite(yaw_phase)
            if np.any(valid_yaw_phase):
                f_yaw = freq[valid_yaw_phase]
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

            ay_phase_05hz, f_05hz_ay = self._nearest_sample(
                f_ay, ay_phase_valid, 0.5
            )
            yaw_phase_05hz, f_05hz_yaw = self._nearest_sample(
                f_yaw, yaw_phase_valid, 0.5
            )
            ay_phase_1hz, f_1hz_ay = self._nearest_sample(
                f_ay, ay_phase_valid, 1.0
            )
            yaw_phase_1hz, f_1hz_yaw = self._nearest_sample(
                f_yaw, yaw_phase_valid, 1.0
            )

            ay_lag_05hz = phase_to_lag(ay_phase_05hz, f_05hz_ay)
            yaw_lag_05hz = phase_to_lag(yaw_phase_05hz, f_05hz_yaw)
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

            ay_gain_slope = safe_log_slope(freq, ay_gain_db)
            yaw_gain_slope = safe_log_slope(freq, yaw_gain_db)
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

            yaw_to_ay_lag = (
                ay_lag - yaw_lag
                if np.isfinite(ay_lag) and np.isfinite(yaw_lag)
                else np.nan
            )

            yaw_to_ay_lag_05hz = (
                ay_lag_05hz - yaw_lag_05hz
                if np.isfinite(ay_lag_05hz) and np.isfinite(yaw_lag_05hz)
                else np.nan
            )
            yaw_to_ay_lag_1hz = yaw_to_ay_lag

            mask_var = (
                np.isfinite(freq) & np.isfinite(ay_gain) & (freq <= 2.0)
            )
            if np.sum(mask_var) > 1:
                g = ay_gain[mask_var]
                gain_variation = (
                    (np.max(g) - np.min(g)) / np.mean(g) * 100.0
                    if abs(np.mean(g)) > 1e-12
                    else np.nan
                )
            else:
                gain_variation = np.nan

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
                "ay_phase_0p5hz": float(ay_phase_05hz),
                "yaw_phase_0p5hz": float(yaw_phase_05hz),
                "ay_lag_0p5hz": float(ay_lag_05hz),
                "yaw_lag_0p5hz": float(yaw_lag_05hz),
                "yaw_to_ay_lag_0p5hz": float(yaw_to_ay_lag_05hz),
                "ay_lag_1hz": float(ay_lag),
                "yaw_lag_1hz": float(yaw_lag),
                "lag_steer_to_ay": float(ay_lag),
                "lag_steer_to_yaw": float(yaw_lag),
                "yaw_to_ay_lag": float(yaw_to_ay_lag),
                "yaw_to_ay_lag_1hz": float(yaw_to_ay_lag_1hz),
                "ay_phase_45_freq": float(ay_cross),
                "yaw_phase_45_freq": float(yaw_cross),
                "ay_gain_slope": float(ay_gain_slope),
                "yaw_gain_slope": float(yaw_gain_slope),
                "ay_phase_slope": float(ay_phase_slope),
                "yaw_phase_slope": float(yaw_phase_slope),
                "gain_variation_pct": float(gain_variation),
                "ay_fit_error": self._safe_nanmean(plot_series["ay_fit_error"]),
                "yaw_fit_error": self._safe_nanmean(plot_series["yaw_fit_error"]),
            })

        return summary, plot_series

    # ============================================================
    # CASE GENERATION
    # ============================================================

    def build_cases(self):
        test = self.config["test"]

        directions = test.get("directions", ["left", "right"])
        signs = [self._direction_sign(d) for d in directions]

        step_time = float(test["stepTime"])
        test_vels = self._as_list(test["testVel"])

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
                    "stepDuration",
                    test.get(
                        "frRampSteerDuration",
                        test.get("step_ramp_duration", 0.02),
                    ),
                )
            )

            for test_vel in test_vels:
                test_vel = float(test_vel)

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
                            "stepDuration": ramp_duration,
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
                            "stepDuration": ramp_duration,
                            "steerAmp": 0.0,
                            "steerFreq": 0.0,
                            "nCycles": 0,
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
        successful_results = [r for r in results if "time" in r]
        failed_results = [r for r in results if "time" not in r]

        if failed_results:
            print(
                f"⚠️  TransientEval skipping {len(failed_results)} failed case(s)",
                flush=True,
            )

        if not successful_results:
            raise RuntimeError("TransientEval had no successful cases to summarize")

        velocity_groups = self._group_results_by_velocity(successful_results)
        if not velocity_groups:
            raise RuntimeError(
                "TransientEval had no successful velocity groups to summarize"
            )

        velocity_keys = sorted(velocity_groups)
        representative_velocity = self._representative_velocity(velocity_keys)
        if representative_velocity not in velocity_groups:
            representative_velocity = velocity_keys[0]

        series = {
            "step_time": {},
            "step_steer": {},
            "step_ay": {},
            "step_sideslip": {},
            "step_yaw": {},
            "step_roll": {},
            "cont_time": {},
            "cont_steer": {},
            "cont_ay": {},
            "cont_yaw": {},
            "freq": {},
            "ay_gain": {},
            "yaw_gain": {},
            "ay_phase": {},
            "yaw_phase": {},
            "ay_fit_error": {},
            "yaw_fit_error": {},
        }

        velocity_summaries = []

        for velocity in velocity_keys:
            vel_summary, vel_series = self._summarize_velocity_group(
                velocity,
                velocity_groups[velocity],
            )
            velocity_summaries.append(vel_summary)

            for key, value in vel_series.items():
                if isinstance(series.get(key), dict) and len(value) > 0:
                    series[key][velocity] = value

        rep_summary = next(
            (s for s in velocity_summaries if self._close(s["velocity_mps"], representative_velocity)),
            velocity_summaries[0],
        )

        summary = dict(rep_summary)
        metric_target_velocity = float(
            self.config.get("report", {}).get(
                "metric_target_velocity_mps",
                representative_velocity,
            )
        )
        summary.update({
            "n_cases": len(results),
            "n_successful_cases": len(successful_results),
            "n_failed_cases": len(failed_results),
            "metric_target_velocity_mps": metric_target_velocity,
            "representative_testVel_mps": float(
                rep_summary.get("velocity_mps", np.nan)
            ),
            "n_velocity_groups": len(velocity_summaries),
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
            {
                "standard": "TransientEval",
                "group": "general",
                "metric": "n_successful_cases",
                "value": summary.get("n_successful_cases", np.nan),
                "units": "count",
                "description": "Number of successful simulation cases included in TransientEval run",
            },
            {
                "standard": "TransientEval",
                "group": "general",
                "metric": "n_failed_cases",
                "value": summary.get("n_failed_cases", np.nan),
                "units": "count",
                "description": "Number of failed simulation cases skipped by TransientEval",
            },
            {
                "standard": "TransientEval",
                "group": "general",
                "metric": "representative_testVel_mps",
                "value": summary.get("representative_testVel_mps", np.nan),
                "units": "m/s",
                "description": "Representative velocity used for the CSV summary rows and tables",
            },
            {
                "standard": "TransientEval",
                "group": "general",
                "metric": "metric_target_velocity_mps",
                "value": summary.get("metric_target_velocity_mps", np.nan),
                "units": "m/s",
                "description": "Target velocity used when selecting the representative summary row",
            },
            {
                "standard": "TransientEval",
                "group": "general",
                "metric": "n_velocity_groups",
                "value": summary.get("n_velocity_groups", np.nan),
                "units": "count",
                "description": "Number of velocity isolines included in the TransientEval run",
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
                "metric": "ay_rise_time_s",
                "value": summary.get("ay_rise_time_s", np.nan),
                "units": "s",
                "description": "Lateral acceleration 50 to 90 percent rise time",
            },
            {
                "standard": "TransientEval",
                "group": "step",
                "metric": "ay_peak_response_time_s",
                "value": summary.get("ay_peak_response_time_s", np.nan),
                "units": "s",
                "description": "Time from 50 percent input to peak lateral acceleration response",
            },
            {
                "standard": "TransientEval",
                "group": "step",
                "metric": "ay_gain_dc",
                "value": summary.get("ay_gain_dc", np.nan),
                "units": "(m/s^2)/rad",
                "description": "Steady-state lateral acceleration gain from handwheel angle",
            },
            {
                "standard": "TransientEval",
                "group": "step",
                "metric": "ay_overshoot_pct",
                "value": summary.get("ay_overshoot_pct", np.nan),
                "units": "%",
                "description": "Lateral acceleration overshoot in representative step steer response",
            },
            {
                "standard": "TransientEval",
                "group": "step",
                "metric": "sideslip_ss",
                "value": summary.get("sideslip_ss", np.nan),
                "units": "rad",
                "description": "Steady-state sideslip angle from representative step steer response",
            },
            {
                "standard": "TransientEval",
                "group": "step",
                "metric": "sideslip_rise_time_s",
                "value": summary.get("sideslip_rise_time_s", np.nan),
                "units": "s",
                "description": "Sideslip angle 50 to 90 percent rise time",
            },
            {
                "standard": "TransientEval",
                "group": "step",
                "metric": "sideslip_gain_dc",
                "value": summary.get("sideslip_gain_dc", np.nan),
                "units": "rad/rad",
                "description": "Steady-state sideslip gain from handwheel angle",
            },
            {
                "standard": "TransientEval",
                "group": "step",
                "metric": "yaw_rise_time_s",
                "value": summary.get("yaw_rise_time_s", np.nan),
                "units": "s",
                "description": "Yaw velocity 50 to 90 percent rise time",
            },
            {
                "standard": "TransientEval",
                "group": "step",
                "metric": "yaw_peak_response_time_s",
                "value": summary.get("yaw_peak_response_time_s", np.nan),
                "units": "s",
                "description": "Time from 50 percent input to peak yaw velocity response",
            },
            {
                "standard": "TransientEval",
                "group": "step",
                "metric": "yaw_gain_dc",
                "value": summary.get("yaw_gain_dc", np.nan),
                "units": "(rad/s)/rad",
                "description": "Steady-state yaw velocity gain from handwheel angle",
            },
            {
                "standard": "TransientEval",
                "group": "step",
                "metric": "yaw_overshoot_rad_per_s",
                "value": summary.get("yaw_overshoot_rad_per_s", np.nan),
                "units": "rad/s",
                "description": "Yaw velocity overshoot relative to final steady-state value",
            },
            {
                "standard": "TransientEval",
                "group": "step",
                "metric": "yaw_overshoot_pct",
                "value": summary.get("yaw_overshoot_pct", np.nan),
                "units": "%",
                "description": "Yaw velocity overshoot percentage relative to final steady-state value",
            },
            {
                "standard": "TransientEval",
                "group": "step",
                "metric": "roll_peak",
                "value": summary.get("roll_peak", np.nan),
                "units": "rad",
                "description": "Peak absolute roll angle during representative step steer response",
            },
            {
                "standard": "TransientEval",
                "group": "step",
                "metric": "roll_ss",
                "value": summary.get("roll_ss", np.nan),
                "units": "rad",
                "description": "Steady-state roll angle from representative step steer response",
            },
            {
                "standard": "TransientEval",
                "group": "step",
                "metric": "roll_gain_dc",
                "value": summary.get("roll_gain_dc", np.nan),
                "units": "rad/rad",
                "description": "Steady-state roll gain from handwheel angle",
            },
            {
                "standard": "TransientEval",
                "group": "step",
                "metric": "roll_overshoot_rad",
                "value": summary.get("roll_overshoot_rad", np.nan),
                "units": "rad",
                "description": "Roll angle overshoot relative to final steady-state value",
            },
            {
                "standard": "TransientEval",
                "group": "step",
                "metric": "roll_overshoot_pct",
                "value": summary.get("roll_overshoot_pct", np.nan),
                "units": "%",
                "description": "Roll angle overshoot percentage relative to final steady-state value",
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
                "metric": "ay_phase_0p5hz",
                "value": summary.get("ay_phase_0p5hz", np.nan),
                "units": "deg",
                "description": "Lateral acceleration phase relative to handwheel angle near 0.5 Hz",
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
                "metric": "yaw_phase_0p5hz",
                "value": summary.get("yaw_phase_0p5hz", np.nan),
                "units": "deg",
                "description": "Yaw velocity phase relative to handwheel angle near 0.5 Hz",
            },
            {
                "standard": "TransientEval",
                "group": "frequency",
                "metric": "ay_lag_0p5hz",
                "value": summary.get("ay_lag_0p5hz", np.nan),
                "units": "s",
                "description": "Equivalent lateral acceleration time lag near 0.5 Hz",
            },
            {
                "standard": "TransientEval",
                "group": "frequency",
                "metric": "yaw_lag_0p5hz",
                "value": summary.get("yaw_lag_0p5hz", np.nan),
                "units": "s",
                "description": "Equivalent yaw velocity time lag near 0.5 Hz",
            },
            {
                "standard": "TransientEval",
                "group": "frequency",
                "metric": "yaw_to_ay_lag_0p5hz",
                "value": summary.get("yaw_to_ay_lag_0p5hz", np.nan),
                "units": "s",
                "description": "Additional lateral acceleration lag relative to yaw velocity near 0.5 Hz",
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
                "metric": "yaw_to_ay_lag_1hz",
                "value": summary.get("yaw_to_ay_lag_1hz", np.nan),
                "units": "s",
                "description": "Additional lateral acceleration lag relative to yaw velocity near 1 Hz",
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

        trend_exclude = {
            "n_cases",
            "n_successful_cases",
            "n_failed_cases",
            "representative_testVel_mps",
            "metric_target_velocity_mps",
            "n_velocity_groups",
        }
        seen_trend_metrics = set()
        trend_rows = []
        for row in metrics:
            metric = row["metric"]
            if metric in trend_exclude or metric in seen_trend_metrics:
                continue
            seen_trend_metrics.add(metric)

            slope = self._velocity_trend_slope(velocity_summaries, metric)
            trend_rows.append({
                "standard": "TransientEval",
                "group": "trend",
                "metric": f"{metric}_velocity_slope",
                "value": slope,
                "units": f"{row['units']}/(m/s)",
                "description": (
                    f"Linear slope of {metric} versus velocity across "
                    "velocity groups"
                ),
            })

        metrics.extend(trend_rows)

        for row in metrics:
            row["value"] = self._csv_value(row["value"])

        metrics_csv_path = self.write_metrics_csv(metrics)

        print(f"📊 TransientEval metrics CSV written: {metrics_csv_path}")

        return {
            "summary": summary,
            "velocity_summaries": velocity_summaries,
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
