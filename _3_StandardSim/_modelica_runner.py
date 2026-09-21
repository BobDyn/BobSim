from __future__ import annotations

from concurrent.futures import ProcessPoolExecutor, as_completed
import json
import os
from pathlib import Path
import time
from typing import Any

import shutil
import subprocess
import sys
import uuid
import traceback
import xml.etree.ElementTree as ET

import numpy as np
import pandas as pd


MODELICA_OVERRIDE_ALIASES = {
    # VCU targetVel derives from initialVel. Override the source so chassis, driveline, and VCU move together.
    "targetVel": "initialVel",
    "targetAy": "vcu.targetAy",
    "useMode": "vcu.useMode",
    "steerStart": "vcu.steerStart",
    "linearitySlopeSamplePeriod": "vcu.linearitySlopeSamplePeriod",
    "handwheelRampRate": "vcu.handwheelRampRate",
    "handwheelRampStopDuration": "vcu.handwheelRampStopDuration",
    "enableNormalLoadSteerLimiter": "vcu.enableNormalLoadSteerLimiter",
    "tireNormalLoadMin": "vcu.tireNormalLoadMin",
    "steadyStateAyRampRate": "vcu.steadyStateAyRampRate",
    "steadyStateMaxHandwheel": "vcu.steadyStateMaxHandwheel",
    "steadyStateAyGain": "vcu.steadyStateAyGain",
    "steadyStateAyTi": "vcu.steadyStateAyTi",
    "steadyStateSteerTimeConstant": "vcu.steadyStateSteerTimeConstant",
    "frRampSteerHeight": "vcu.frRampSteerHeight",
    "frRampSteerDuration": "vcu.frRampSteerDuration",
    "stepDuration": "vcu.stepDuration",
    "steerAmp": "vcu.steerAmp",
    "steerFreq": "vcu.steerFreq",
    "velGain": "vcu.velGain",
    "velTi": "vcu.velTi",
}


def _modelica_exec_base_name(exec_name: str) -> str:
    return exec_name[:-4] if exec_name.lower().endswith(".exe") else exec_name


def _modelica_executable_candidates(build_dir: Path, exec_name: str) -> list[Path]:
    base_name = _modelica_exec_base_name(exec_name)
    names = [exec_name]
    if not exec_name.lower().endswith(".exe"):
        names.append(f"{exec_name}.exe")
    else:
        names.append(base_name)
    return [build_dir / name for name in dict.fromkeys(names)]


def _path_list_value(value: str) -> list[str]:
    return [part for part in value.split(os.pathsep) if part.strip()]


def _path_is_within(path: Path, root: Path) -> bool:
    try:
        path.resolve().relative_to(root.resolve())
    except (OSError, ValueError):
        return False
    return True


def _strip_env_paths_under(value: str, root: Path) -> str:
    parts = [part for part in _path_list_value(value) if not _path_is_within(Path(part), root)]
    return os.pathsep.join(parts)


def _sanitize_frozen_external_env(env: dict[str, str]) -> None:
    if not getattr(sys, "frozen", False):
        return
    bundle_root_raw = str(getattr(sys, "_MEIPASS", "") or "").strip()
    bundle_root = Path(bundle_root_raw) if bundle_root_raw else None

    for key in ("LD_LIBRARY_PATH", "DYLD_LIBRARY_PATH"):
        original = env.get(f"{key}_ORIG")
        if original is not None:
            restored = _strip_env_paths_under(original, bundle_root) if bundle_root else original
            if restored:
                env[key] = restored
            else:
                env.pop(key, None)
            continue
        if bundle_root and env.get(key):
            cleaned = _strip_env_paths_under(env[key], bundle_root)
            if cleaned:
                env[key] = cleaned
            else:
                env.pop(key, None)

    if bundle_root and env.get("PATH"):
        cleaned_path = _strip_env_paths_under(env["PATH"], bundle_root)
        if cleaned_path:
            env["PATH"] = cleaned_path
        else:
            env.pop("PATH", None)


def _subprocess_creation_flags() -> int:
    if sys.platform != "win32":
        return 0
    return int(getattr(subprocess, "CREATE_NO_WINDOW", 0))


def _first_not_none(*values: Any) -> Any:
    for value in values:
        if value is not None:
            return value

    return None


def _json_ready(value: Any) -> Any:
    if isinstance(value, dict):
        return {str(key): _json_ready(item) for key, item in value.items()}
    if isinstance(value, (list, tuple)):
        return [_json_ready(item) for item in value]
    if isinstance(value, Path):
        return str(value)
    if isinstance(value, (str, int, float, bool)) or value is None:
        return value
    return str(value)


class ModelicaRunner:
    def __init__(self, build_dir, exec_name, simulation):
        self.build_dir = Path(build_dir).resolve()
        self.exec_name = _modelica_exec_base_name(str(exec_name))
        self.simulation = simulation or {}

        executable_candidates = _modelica_executable_candidates(self.build_dir, str(exec_name))
        self.init_xml = self.build_dir / f"{self.exec_name}_init.xml"

        exe_path = next((candidate for candidate in executable_candidates if candidate.exists()), None)
        if exe_path is None:
            expected = " or ".join(str(candidate) for candidate in executable_candidates)
            raise FileNotFoundError(f"Executable not found. Expected one of: {expected}")
        self.exe_path = exe_path

        if not self.init_xml.exists():
            raise FileNotFoundError(f"Init XML not found: {self.init_xml}")
        self._init_defaults_cache: dict[str, str] | None = None

    @classmethod
    def from_config(cls, config):
        sim_cfg = config.get("simulation", {})

        return cls(
            build_dir=sim_cfg.get("build_dir", "_3_StandardSim/BuildBobLib/VehicleSim"),
            exec_name=sim_cfg.get(
                "exec_name",
                "BobLib.Experiments.Standards.VehicleSim",
            ),
            simulation=sim_cfg,
        )

    def run(self, signals, mode, cases, execution=None):
        execution = execution or {}

        cleanup = bool(execution.get("cleanup", False))
        stream_logs = bool(execution.get("stream_logs", False))
        fail_fast = bool(execution.get("fail_fast", False))

        if execution.get("parallel", True):
            return self.run_cases_parallel(
                signals=signals,
                mode=mode,
                cases=cases,
                max_workers=execution.get("max_workers"),
                cleanup=cleanup,
                stream_logs=stream_logs,
                fail_fast=fail_fast,
            )

        return self.run_cases(
            signals=signals,
            mode=mode,
            cases=cases,
            cleanup=cleanup,
            stream_logs=stream_logs,
            fail_fast=fail_fast,
        )

    def run_cases(self, signals, mode, cases, cleanup=False, stream_logs=False, fail_fast=False):
        results = []
        n_total = len(cases)
        n_done = 0
        n_failed = 0

        for i, case in enumerate(cases, start=1):
            label = self._case_label(case)

            print(f"[{i}/{n_total}] running {label}", flush=True)

            result = self._run_case_safe(
                signals=signals,
                mode=mode,
                case=case,
                cleanup=cleanup,
                stream_logs=stream_logs,
            )
            results.append(result)

            n_done += 1
            if result.get("_status") == "failed":
                n_failed += 1
                print(f"[{i}/{n_total}] failed {label}", flush=True)
                if fail_fast:
                    raise RuntimeError(
                        "Stopping after failed simulation case "
                        f"{label}: {result.get('_error', 'unknown error')}"
                    )
            else:
                print(f"[{i}/{n_total}] complete {label}", flush=True)

        print(
            f"Finished {n_done}/{n_total} cases"
            + (f" with {n_failed} failure(s)" if n_failed else ""),
            flush=True,
        )

        return results

    def run_cases_parallel(
        self,
        signals,
        mode,
        cases,
        max_workers=None,
        cleanup=False,
        stream_logs=False,
        fail_fast=False,
    ):
        if fail_fast:
            print(
                "Note: fail_fast is only immediate for serial execution; "
                "parallel cases already queued may continue until completion.",
                flush=True,
            )

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
            print(
                f"Queueing {n_total} cases; running up to {n_workers} at a time",
                flush=True,
            )

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
            n_failed = 0

            for future in as_completed(futures):
                idx = futures[future]
                try:
                    result = future.result()
                except Exception as exc:  # pragma: no cover - safety net
                    case = cases[idx]
                    label = self._case_label(case)
                    result = {
                        "_status": "failed",
                        "_case_label": label,
                        "_error": str(exc),
                        "_traceback": traceback.format_exc(),
                    }
                results[idx] = result

                n_done += 1
                label = result.get("_case_label", f"case {idx + 1}")

                if result.get("_status") == "failed":
                    n_failed += 1
                    print(f"[{n_done}/{n_total}] failed {label}", flush=True)
                    if fail_fast:
                        raise RuntimeError(
                            "Stopping after failed simulation case "
                            f"{label}: {result.get('_error', 'unknown error')}"
                        )
                else:
                    print(f"[{n_done}/{n_total}] complete {label}", flush=True)

        print(
            f"Finished {n_done}/{n_total} cases"
            + (f" with {n_failed} failure(s)" if n_failed else ""),
            flush=True,
        )

        return results

    def run_case(self, signals, mode, case, cleanup=False, stream_logs=False):
        run_id = str(uuid.uuid4())[:8]
        case_label = self._case_label(case)

        results_root = self._resolve_run_root()
        run_dir = results_root / f"run_{run_id}"
        run_dir.mkdir(parents=True, exist_ok=True)

        override_file = run_dir / "overrides.txt"
        result_file = run_dir / f"{self.exec_name}_res.csv"
        log_file = run_dir / "run.log"
        manifest_file = run_dir / "manifest.json"

        self._write_override_file(override_file, case)
        self._write_run_manifest(
            manifest_file,
            {
                "run_id": run_id,
                "case_label": case_label,
                "status": "running",
                "started_at": time.time(),
                "build_dir": str(self.build_dir),
                "executable": str(self.exe_path),
                "run_dir": str(run_dir),
                "override_file": str(override_file),
                "result_file": str(result_file),
                "log_file": str(log_file),
                "mode": mode,
                "signals": list(signals or []),
                "case": case,
            },
        )
        self._remove_stale_profile_files()

        cmd = self._build_command(
            override_file=override_file,
            result_file=result_file,
            case=case,
        )
        env = self._build_environment()
        timeout_s = self._timeout_seconds(case)

        if stream_logs:
            returncode = self._run_subprocess_streamed(
                cmd=cmd,
                log_file=log_file,
                env=env,
                timeout_s=timeout_s,
            )
            stdout_tail = log_file.read_text(errors="replace")[-4000:]
        else:
            try:
                completed = subprocess.run(
                    cmd,
                    cwd=self.build_dir,
                    env=env,
                    stdout=subprocess.PIPE,
                    stderr=subprocess.STDOUT,
                    text=True,
                    timeout=timeout_s,
                    creationflags=_subprocess_creation_flags(),
                )
            except subprocess.TimeoutExpired as exc:
                output = exc.stdout or ""
                if isinstance(output, bytes):
                    output = output.decode(errors="replace")
                timeout_note = (
                    f"\n\nSimulation exceeded wall-clock timeout "
                    f"of {timeout_s:.1f} s and was terminated.\n"
                )
                log_file.write_text(output + timeout_note)
                raise TimeoutError(
                    f"Simulation exceeded wall-clock timeout of {timeout_s:.1f} s. "
                    f"See log: {log_file}"
                ) from exc

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

        self._raise_if_solver_failed(log_file=log_file, stdout_tail=stdout_tail)

        data = pd.read_csv(result_file)

        extracted = self._extract_signals(
            data=data,
            signals=signals,
            mode=mode,
        )

        # Keep "_" metadata keys in the result. They do not go to the override file.
        for key, value in case.items():
            if key.startswith("_"):
                extracted[key] = value

        extracted["_case_label"] = self._case_label(case)
        extracted["_run_dir"] = str(run_dir)
        extracted["_result_file"] = str(result_file)
        extracted["_log_file"] = str(log_file)
        self._write_run_manifest(
            manifest_file,
            {
                "run_id": run_id,
                "case_label": case_label,
                "status": "succeeded",
                "ended_at": time.time(),
                "build_dir": str(self.build_dir),
                "executable": str(self.exe_path),
                "run_dir": str(run_dir),
                "override_file": str(override_file),
                "result_file": str(result_file),
                "log_file": str(log_file),
                "mode": mode,
                "signals": list(signals or []),
                "case": case,
            },
        )

        if cleanup:
            shutil.rmtree(run_dir, ignore_errors=True)

        return extracted

    def _write_run_manifest(self, path: Path, manifest: dict[str, Any]) -> None:
        path.write_text(json.dumps(_json_ready(manifest), indent=2), encoding="utf-8")

    def _resolve_run_root(self) -> Path:
        results_root = self.build_dir / "results"
        if results_root.exists():
            if os.access(results_root, os.W_OK):
                return results_root
            return self.build_dir / "runs"
        return results_root

    def _run_subprocess_streamed(self, cmd, log_file, env, timeout_s=None):
        if timeout_s is not None:
            with subprocess.Popen(
                cmd,
                cwd=self.build_dir,
                env=env,
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT,
                text=True,
                creationflags=_subprocess_creation_flags(),
            ) as process:
                try:
                    stdout, _ = process.communicate(timeout=timeout_s)
                except subprocess.TimeoutExpired as exc:
                    process.kill()
                    stdout, _ = process.communicate()
                    timeout_note = (
                        f"\n\nSimulation exceeded wall-clock timeout "
                        f"of {timeout_s:.1f} s and was terminated.\n"
                    )
                    Path(log_file).write_text((stdout or "") + timeout_note)
                    raise TimeoutError(
                        f"Simulation exceeded wall-clock timeout of {timeout_s:.1f} s. "
                        f"See log: {log_file}"
                    ) from exc

                Path(log_file).write_text(stdout or "")
                for line in (stdout or "").splitlines():
                    if self._should_print_solver_line(line):
                        print(line.rstrip(), flush=True)
                return process.returncode

        with subprocess.Popen(
            cmd,
            cwd=self.build_dir,
            env=env,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            bufsize=1,
            creationflags=_subprocess_creation_flags(),
        ) as process:
            with Path(log_file).open("w") as log:
                assert process.stdout is not None

                for line in process.stdout:
                    log.write(line)

                    if self._should_print_solver_line(line):
                        print(line.rstrip(), flush=True)

                return process.wait()

    def _timeout_seconds(self, case):
        timeout_s = _first_not_none(
            case.get("_timeout_s"),
            case.get("timeout_s"),
            self.simulation.get("case_timeout_s"),
            self.simulation.get("run_timeout_s"),
            self.simulation.get("wall_timeout_s"),
            self.simulation.get("timeout_s"),
        )
        if timeout_s is None:
            return None

        timeout_s = float(timeout_s)
        if timeout_s <= 0.0:
            return None

        return timeout_s

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

    def _raise_if_solver_failed(self, log_file, stdout_tail):
        log_path = Path(log_file)
        log_text = log_path.read_text(errors="replace") if log_path.exists() else ""
        text = log_text.lower()

        failure_markers = (
            "integrator failed",
            "can't continue",
            "error test failed repeatedly",
            "failed to solve linear system of equations",
            "residual norm is inf",
            "desired step to small",
            "##cvode## -",
            "ddassl had repeated error test failures",
            "ddassl had repeated convergence test failures",
        )

        if any(marker in text for marker in failure_markers):
            raise RuntimeError(
                f"Simulation solver failed. See log: {log_path}\n\n"
                f"{stdout_tail}"
            )

    def _extract_signals(self, data, signals, mode):
        out = {}

        if "time" in data.columns:
            time = np.asarray(data["time"].to_numpy(), dtype=float)
        else:
            time = np.arange(len(data), dtype=float)

        if not np.all(np.isfinite(time)):
            raise ValueError("Result CSV contains non-finite values in time.")

        if mode == "raw":
            out["time"] = time

            for signal in signals:
                if signal not in data.columns:
                    raise KeyError(f"Signal not found in result CSV: {signal}")

                values = np.asarray(data[signal].to_numpy(), dtype=float)
                if not np.all(np.isfinite(values)):
                    raise ValueError(
                        f"Result CSV contains non-finite values in signal: {signal}"
                    )

                out[signal] = values

            return out

        if mode in {"steady", "last"}:
            for signal in signals:
                if signal not in data.columns:
                    raise KeyError(f"Signal not found in result CSV: {signal}")

                value = float(data[signal].iloc[-1])
                if not np.isfinite(value):
                    raise ValueError(
                        f"Result CSV contains non-finite final value in signal: {signal}"
                    )

                out[signal] = value

            return out

        raise ValueError(f"Unsupported extraction mode: {mode}")

    def _build_environment(self) -> dict[str, str]:
        env = os.environ.copy()
        _sanitize_frozen_external_env(env)
        self._ensure_runtime_compat_symlink()
        runtime_dirs = self._openmodelica_runtime_dirs()
        current_ld_library_path = env.get("LD_LIBRARY_PATH", "")
        ld_library_path_parts = [
            str(self.build_dir),
            *(str(path) for path in runtime_dirs),
        ]
        if current_ld_library_path:
            ld_library_path_parts.append(current_ld_library_path)
        env["LD_LIBRARY_PATH"] = ":".join(ld_library_path_parts)
        if sys.platform == "win32":
            current_path = env.get("PATH", "")
            path_parts = [str(self.build_dir), *(str(path) for path in runtime_dirs)]
            if current_path:
                path_parts.append(current_path)
            env["PATH"] = os.pathsep.join(path_parts)
        return env

    def _ensure_runtime_compat_symlink(self) -> None:
        compat_link = self.build_dir / "libomcgc.so.1"
        target = next(
            (
                runtime_dir / "libomcgc.so"
                for runtime_dir in self._openmodelica_runtime_dirs()
                if (runtime_dir / "libomcgc.so").exists()
            ),
            None,
        )

        if compat_link.exists() or target is None:
            return

        try:
            compat_link.symlink_to(target)
        except FileExistsError:
            pass

    def _openmodelica_runtime_dirs(self) -> list[Path]:
        candidates: list[Path] = [
            Path("/usr/lib/x86_64-linux-gnu/omc"),
            Path("/usr/lib/omc"),
        ]
        if sys.platform == "win32":
            roots = [
                Path(value)
                for value in (
                    os.environ.get("OPENMODELICAHOME"),
                    os.environ.get("OPENMODELICA_HOME"),
                    r"C:\Program Files\OpenModelica1.26.1-64bit",
                    r"C:\Program Files\OpenModelica1.25.5-64bit",
                    r"C:\Program Files\OpenModelica1.25.4-64bit",
                    r"C:\Program Files\OpenModelica1.25.0-64bit",
                )
                if value
            ]
            for root in roots:
                candidates.extend((root / "bin", root / "lib" / "omc", root / "lib"))

        return [path for path in dict.fromkeys(candidates) if path.exists()]

    def _remove_stale_profile_files(self) -> None:
        profile_prefix = f"{self.exec_name}_prof."
        for path in self.build_dir.glob(f"{profile_prefix}*"):
            try:
                path.unlink()
            except FileNotFoundError:
                continue

    def _run_case_safe(self, signals, mode, case, cleanup=False, stream_logs=False):
        try:
            result = self.run_case(
                signals=signals,
                mode=mode,
                case=case,
                cleanup=cleanup,
                stream_logs=stream_logs,
            )
        except Exception as exc:
            label = self._case_label(case)
            return {
                "_status": "failed",
                "_case_label": label,
                "_error": str(exc),
                "_traceback": traceback.format_exc(),
            }

        result["_status"] = "ok"
        return result

    def _write_override_file(self, path, case):
        init_defaults = self._init_parameter_defaults()
        with Path(path).open("w", newline="\n") as f:
            for key, value in case.items():
                # "_" keys are Python-only metadata.
                if key.startswith("_"):
                    continue

                # _build_command() passes these as runtime flags.
                if key in {"startTime", "stopTime"}:
                    continue

                modelica_key = MODELICA_OVERRIDE_ALIASES.get(key, key)
                formatted_value = self._format_override_value(value)
                if init_defaults is not None:
                    default_value = init_defaults.get(modelica_key)
                    if default_value is None:
                        continue
                    if self._override_matches_default(formatted_value, default_value):
                        continue
                f.write(f"{modelica_key}={formatted_value}\n")

    def _init_parameter_defaults(self) -> dict[str, str] | None:
        if not hasattr(self, "init_xml"):
            return None
        if not hasattr(self, "_init_defaults_cache"):
            self._init_defaults_cache = None
        if self._init_defaults_cache is not None:
            return self._init_defaults_cache
        if not self.init_xml.exists():
            return None

        defaults: dict[str, str] = {}
        root = ET.parse(self.init_xml).getroot()
        for variable in root.iter("ScalarVariable"):
            name = variable.attrib.get("name")
            if not name:
                continue
            value_node = next(iter(variable), None)
            if value_node is None:
                continue
            start = value_node.attrib.get("start")
            if start is not None:
                defaults[name] = start

        self._init_defaults_cache = defaults
        return defaults

    def _override_matches_default(self, override_value: str, default_value: str) -> bool:
        override = override_value.strip()
        default = default_value.strip()

        if override.lower() in {"true", "false"} or default.lower() in {"true", "false"}:
            return override.lower() == default.lower()

        try:
            return bool(np.isclose(float(override), float(default), rtol=0.0, atol=0.0))
        except ValueError:
            return override == default

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

        # OM executables read *_init.xml from the working directory, so run from build_dir.
        cmd = [
            str(self.exe_path),
            f"-overrideFile={override_file}",
            f"-r={result_file}",
        ]

        start_time = _first_not_none(
            case.get("_startTime"),
            case.get("startTime"),
            self.simulation.get("start_time"),
        )

        stop_time = _first_not_none(
            case.get("_stopTime"),
            case.get("stopTime"),
            self.simulation.get("stop_time"),
        )

        if start_time is not None:
            cmd.append(f"-startTime={float(start_time)}")

        if stop_time is not None:
            cmd.append(f"-stopTime={float(stop_time)}")

        step_size = _first_not_none(
            case.get("_stepSize"),
            case.get("stepSize"),
            self.simulation.get("step_size"),
            self.simulation.get("stepSize"),
            self.simulation.get("initialStepSize"),
        )
        if step_size is not None:
            cmd.append(f"-stepSize={float(step_size)}")

        solver = self.simulation.get("solver")
        if solver:
            cmd.append(f"-s={solver}")

        tolerance = self.simulation.get("tolerance")
        if tolerance is not None:
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

        if any(key in case for key in ("testVel", "_testVel", "targetVel")) and any(
            key in case for key in ("testAy", "_testAy", "targetAy")
        ):
            vel = _first_not_none(case.get("testVel"), case.get("_testVel"), case.get("targetVel"))
            ay = _first_not_none(case.get("testAy"), case.get("_testAy"), case.get("targetAy"))

            if vel is not None and ay is not None:
                return (
                    f"{mode}, V={float(vel):.3g} m/s, "
                    f"Ay={float(ay):.3g} m/s^2"
                )

        if "testAy" in case:
            return f"{mode}, Ay={float(case['testAy']):.3g} m/s^2"

        if "_testAy" in case:
            return f"{mode}, Ay={float(case['_testAy']):.3g} m/s^2"

        if "targetAy" in case:
            return f"{mode}, Ay={float(case['targetAy']):.3g} m/s^2"

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

    return runner._run_case_safe(
        signals=signals,
        mode=mode,
        case=case,
        cleanup=cleanup,
        stream_logs=stream_logs,
    )
