from __future__ import annotations

from concurrent.futures import ProcessPoolExecutor, as_completed
from pathlib import Path
import shutil
import subprocess
import uuid

import numpy as np
import pandas as pd


class ModelicaRunner:
    def __init__(self, build_dir, exec_name, simulation):
        self.build_dir = Path(build_dir).resolve()
        self.exec_name = exec_name
        self.simulation = simulation or {}

        self.exe_path = self.build_dir / exec_name
        self.init_xml = self.build_dir / f"{exec_name}_init.xml"

        if not self.exe_path.exists():
            raise FileNotFoundError(f"Executable not found: {self.exe_path}")

        if not self.init_xml.exists():
            raise FileNotFoundError(f"Init XML not found: {self.init_xml}")

    @classmethod
    def from_config(cls, config):
        sim_cfg = config.get("simulation", {})

        return cls(
            build_dir=sim_cfg.get("build_dir", "_3_StandardSim/Build"),
            exec_name=sim_cfg.get("exec_name", "BobLib.Standards.VehicleModel"),
            simulation=sim_cfg,
        )

    def run(self, signals, mode, cases, execution=None):
        execution = execution or {}

        cleanup = bool(execution.get("cleanup", False))
        stream_logs = bool(execution.get("stream_logs", False))

        if execution.get("parallel", True):
            return self.run_cases_parallel(
                signals=signals,
                mode=mode,
                cases=cases,
                max_workers=execution.get("max_workers"),
                cleanup=cleanup,
                stream_logs=stream_logs,
            )

        return self.run_cases(
            signals=signals,
            mode=mode,
            cases=cases,
            cleanup=cleanup,
            stream_logs=stream_logs,
        )

    def run_cases(self, signals, mode, cases, cleanup=False, stream_logs=False):
        results = []
        n_total = len(cases)

        for i, case in enumerate(cases, start=1):
            label = self._case_label(case)

            print(f"[{i}/{n_total}] running {label}", flush=True)

            results.append(
                self.run_case(
                    signals=signals,
                    mode=mode,
                    case=case,
                    cleanup=cleanup,
                    stream_logs=stream_logs,
                )
            )

            print(f"[{i}/{n_total}] complete {label}", flush=True)

        return results

    def run_cases_parallel(
        self,
        signals,
        mode,
        cases,
        max_workers=None,
        cleanup=False,
        stream_logs=False,
    ):
        n_total = len(cases)
        results = [None] * n_total

        print(
            f"Running {n_total} cases in parallel"
            + (f" with max_workers={max_workers}" if max_workers else ""),
            flush=True,
        )

        with ProcessPoolExecutor(max_workers=max_workers) as pool:
            futures = {}

            n_workers = max_workers or "default"
            print(f"Queueing {n_total} cases; running up to {n_workers} at a time", flush=True)

            for i, case in enumerate(cases, start=1):
                label = self._case_label(case)

                print(f"[{i}/{n_total}] queued {label}", flush=True)

                future = pool.submit(
                    _run_case_worker,
                    str(self.build_dir),
                    self.exec_name,
                    self.simulation,
                    signals,
                    mode,
                    case,
                    cleanup,
                    stream_logs,
                )

                futures[future] = i - 1

            n_done = 0

            for future in as_completed(futures):
                idx = futures[future]
                result = future.result()
                results[idx] = result

                n_done += 1
                label = result.get("_case_label", f"case {idx + 1}")

                print(f"[{n_done}/{n_total}] complete {label}", flush=True)

        return results

    def run_case(self, signals, mode, case, cleanup=False, stream_logs=False):
        run_id = str(uuid.uuid4())[:8]

        results_root = self.build_dir / "results"
        run_dir = results_root / f"run_{run_id}"
        run_dir.mkdir(parents=True, exist_ok=True)

        override_file = run_dir / "overrides.txt"
        result_file = run_dir / f"{self.exec_name}_res.csv"
        log_file = run_dir / "run.log"

        self._write_override_file(override_file, case)

        cmd = self._build_command(
            override_file=override_file,
            result_file=result_file,
            case=case,
        )

        if stream_logs:
            returncode = self._run_subprocess_streamed(
                cmd=cmd,
                log_file=log_file,
            )
            stdout_tail = log_file.read_text(errors="replace")[-4000:]
        else:
            completed = subprocess.run(
                cmd,
                cwd=self.build_dir,
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT,
                text=True,
            )

            log_file.write_text(completed.stdout)
            returncode = completed.returncode
            stdout_tail = completed.stdout[-4000:]

        if returncode != 0:
            raise RuntimeError(
                f"Simulation failed. See log: {log_file}\n\n"
                f"{stdout_tail}"
            )

        if not result_file.exists():
            raise FileNotFoundError(
                f"Simulation finished but result file was not found: {result_file}"
            )

        data = pd.read_csv(result_file)

        extracted = self._extract_signals(
            data=data,
            signals=signals,
            mode=mode,
        )

        # Preserve non-table metadata from the case dictionary.
        # Keys starting with "_" are Python-only metadata and are intentionally
        # not written to the Modelica override file, but they are preserved here.
        for key, value in case.items():
            if key.startswith("_"):
                extracted[key] = value

        extracted["_case_label"] = self._case_label(case)
        extracted["_run_dir"] = str(run_dir)
        extracted["_result_file"] = str(result_file)
        extracted["_log_file"] = str(log_file)

        if cleanup:
            shutil.rmtree(run_dir, ignore_errors=True)

        return extracted

    def _run_subprocess_streamed(self, cmd, log_file):
        with subprocess.Popen(
            cmd,
            cwd=self.build_dir,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            bufsize=1,
        ) as process:
            with Path(log_file).open("w") as log:
                assert process.stdout is not None

                for line in process.stdout:
                    log.write(line)

                    if self._should_print_solver_line(line):
                        print(line.rstrip(), flush=True)

                return process.wait()

    def _should_print_solver_line(self, line):
        s = line.lower()

        return (
            "assert" in s
            or "error" in s
            or "warning" in s
            or "failed" in s
            or "time" in s
            or "log_stats" in s
            or "log_success" in s
            or "simulation" in s
        )

    def _extract_signals(self, data, signals, mode):
        out = {}

        if "time" in data.columns:
            time = data["time"].to_numpy()
        else:
            time = np.arange(len(data), dtype=float)

        if mode == "raw":
            out["time"] = time

            for signal in signals:
                if signal not in data.columns:
                    raise KeyError(f"Signal not found in result CSV: {signal}")

                out[signal] = data[signal].to_numpy()

            return out

        if mode in {"steady", "last"}:
            for signal in signals:
                if signal not in data.columns:
                    raise KeyError(f"Signal not found in result CSV: {signal}")

                out[signal] = float(data[signal].iloc[-1])

            return out

        raise ValueError(f"Unsupported extraction mode: {mode}")

    def _write_override_file(self, path, case):
        with Path(path).open("w", newline="\n") as f:
            for key, value in case.items():
                # Python-only metadata. Keep in result dict, but do not pass to OM.
                if key.startswith("_"):
                    continue

                # Runtime flag, not necessarily a Modelica parameter.
                # It is handled in _build_command().
                if key == "stopTime":
                    continue

                value = self._format_override_value(value)
                f.write(f"{key}={value}\n")

    def _format_override_value(self, value):
        if isinstance(value, bool):
            return "true" if value else "false"

        if isinstance(value, (float, np.floating)):
            return repr(float(value))

        if isinstance(value, (int, np.integer)):
            return str(int(value))

        return str(value)

    def _build_command(self, override_file, result_file, case=None):
        case = case or {}

        # Important:
        # OpenModelica generated executables expect their *_init.xml file
        # in the current working directory. Therefore subprocess.run uses
        # cwd=self.build_dir, and the executable is launched locally.
        cmd = [
            f"./{self.exec_name}",
            f"-overrideFile={override_file}",
            f"-r={result_file}",
        ]

        stop_time = (
            case.get("_stopTime")
            or case.get("stopTime")
            or self.simulation.get("stop_time")
        )

        if stop_time is not None:
            cmd.append(f"-stopTime={float(stop_time)}")

        solver = self.simulation.get("solver")
        if solver:
            cmd.append(f"-s={solver}")

        tolerance = self.simulation.get("tolerance")
        if tolerance:
            cmd.append(f"-tolerance={float(tolerance)}")

        log_level = self.simulation.get("log_level")
        if log_level:
            cmd.append(f"-lv={log_level}")

        variable_filter = self.simulation.get("variable_filter")
        if variable_filter:
            cmd.append(f"-variableFilter={variable_filter}")

        if self.simulation.get("no_grid", False):
            cmd.append("-noEquidistantTimeGrid")

        if self.simulation.get("no_event_emit", False):
            cmd.append("-noEventEmit")

        if self.simulation.get("no_equidistant_output_frequency", False):
            cmd.append("-noEquidistantOutputFrequency")

        extra_args = self.simulation.get("extra_args", [])
        cmd.extend(str(arg) for arg in extra_args)

        return cmd

    def _case_label(self, case):
        mode = case.get("_mode", case.get("mode", "case"))

        if "testRad" in case:
            return f"{mode}, R={float(case['testRad']):.3g} m"

        if "_testRad" in case:
            return f"{mode}, R={float(case['_testRad']):.3g} m"

        freq = case.get("_steerFreq", case.get("steerFreq"))
        amp = case.get("_steerAmp", case.get("steerAmp"))

        if freq is not None and amp is not None:
            amp_deg = float(np.rad2deg(float(amp)))
            return f"{mode}, f={float(freq):.3g} Hz, amp={amp_deg:.3g} deg"

        step = case.get("_steerStep", case.get("steerStep"))

        if step is not None:
            step_deg = float(np.rad2deg(float(step)))
            return f"{mode}, step={step_deg:.3g} deg"

        return str(mode)


def _run_case_worker(
    build_dir,
    exec_name,
    simulation,
    signals,
    mode,
    case,
    cleanup,
    stream_logs,
):
    runner = ModelicaRunner(
        build_dir=build_dir,
        exec_name=exec_name,
        simulation=simulation,
    )

    label = runner._case_label(case)
    print(f"started {label}", flush=True)

    return runner.run_case(
        signals=signals,
        mode=mode,
        case=case,
        cleanup=cleanup,
        stream_logs=stream_logs,
    )