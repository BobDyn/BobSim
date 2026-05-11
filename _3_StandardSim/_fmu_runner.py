from __future__ import annotations

from concurrent.futures import ProcessPoolExecutor, as_completed
from pathlib import Path
import ctypes
import uuid

import numpy as np
from scipy.integrate import solve_ivp

from fmpy import read_model_description, extract
from fmpy.fmi2 import FMU2Model


class FMURunner:
    def __init__(
        self,
        fmu_path,
        snapshot_file=None,
        solver="LSODA",
        rtol=1e-4,
        atol=1e-6,
        max_step=0.005,
        output_dt=None,
        init_duration=1.0,
        init_solver="LSODA",
        init_max_step=0.005,
        use_snapshot=True,
        init_parameters=None,
        init_input_values=None,
    ):
        self.fmu_path = Path(fmu_path).resolve()

        if not self.fmu_path.exists():
            raise FileNotFoundError(f"FMU not found: {self.fmu_path}")

        self.snapshot_file = (
            Path(snapshot_file).resolve()
            if snapshot_file is not None
            else self.fmu_path.parent / f"{self.fmu_path.stem}_init_snapshot.npz"
        )

        self.solver = solver
        self.rtol = float(rtol)
        self.atol = float(atol)
        self.max_step = float(max_step)
        self.output_dt = output_dt

        self.init_duration = float(init_duration)
        self.init_solver = init_solver
        self.init_max_step = float(init_max_step)
        self.use_snapshot = bool(use_snapshot)

        self.init_parameters = dict(init_parameters or {})
        self.init_input_values = dict(init_input_values or {})

        self.model_description = read_model_description(str(self.fmu_path))
        self.unzipdir = extract(str(self.fmu_path))

        if self.model_description.modelExchange is None:
            raise ValueError(
                "FMURunner expects an FMI 2.0 Model Exchange FMU. "
                "This FMU does not expose modelExchange."
            )

        self.model_identifier = (
            self.model_description.modelExchange.modelIdentifier
        )

        self.nx = int(self.model_description.numberOfContinuousStates)

        self.variables = {
            var.name: var
            for var in self.model_description.modelVariables
        }

        self.vrs = {
            var.name: var.valueReference
            for var in self.model_description.modelVariables
        }

        self.input_vrs = {
            var.name: var.valueReference
            for var in self.model_description.modelVariables
            if getattr(var, "causality", None) == "input"
        }

        self.state_names = self._extract_state_names()

        self.fmu = None
        self.dx_buffer = np.zeros(self.nx)
        self.call_count = 0

        self._active_case = None
        self._t_global0 = 0.0

        if self.use_snapshot:
            self._ensure_initialized_snapshot()

    # ============================================================
    # CONFIG
    # ============================================================

    @classmethod
    def from_config(cls, config):
        sim_cfg = config.get("simulation", {})

        return cls(
            fmu_path=sim_cfg["fmu_path"],
            snapshot_file=sim_cfg.get("snapshot_file"),
            solver=sim_cfg.get("solver", "LSODA"),
            rtol=sim_cfg.get("rtol", 1e-4),
            atol=sim_cfg.get("atol", 1e-6),
            max_step=sim_cfg.get("max_step", 0.005),
            output_dt=sim_cfg.get("output_dt"),
            init_duration=sim_cfg.get("init_duration", 1.0),
            init_solver=sim_cfg.get("init_solver", "LSODA"),
            init_max_step=sim_cfg.get("init_max_step", 0.005),
            use_snapshot=sim_cfg.get("use_snapshot", True),
            init_parameters=sim_cfg.get("init_parameters", {}),
            init_input_values=sim_cfg.get("init_input_values", {}),
        )

    # ============================================================
    # PUBLIC API — mirrors ModelicaRunner
    # ============================================================

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

    def run_cases(
        self,
        signals,
        mode,
        cases,
        cleanup=False,
        stream_logs=False,
    ):
        results = []
        n_total = len(cases)

        print(f"Running {n_total} FMU cases serially", flush=True)

        for i, case in enumerate(cases, start=1):
            label = self._case_label(case)
            print(f"[{i}/{n_total}] started {label}", flush=True)

            result = self.run_case(
                signals=signals,
                mode=mode,
                case=case,
                cleanup=cleanup,
                stream_logs=stream_logs,
            )

            results.append(result)
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
            f"Queueing {n_total} FMU cases"
            + (f"; running up to {max_workers} at a time" if max_workers else ""),
            flush=True,
        )

        sim_cfg = self._worker_config()

        with ProcessPoolExecutor(max_workers=max_workers) as pool:
            futures = {}

            for i, case in enumerate(cases, start=1):
                label = self._case_label(case)
                print(f"[{i}/{n_total}] queued {label}", flush=True)

                future = pool.submit(
                    _run_fmu_case_worker,
                    sim_cfg,
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

                label = result.get("_case_label", self._case_label(cases[idx]))
                print(f"[{n_done}/{n_total}] complete {label}", flush=True)

        return results

    def run_case(
        self,
        signals,
        mode,
        case,
        cleanup=False,
        stream_logs=False,
    ):
        run_id = str(uuid.uuid4())[:8]
        label = self._case_label(case)

        if stream_logs:
            print(f"[FMU] started {label}", flush=True)

        duration = self._case_duration(case)

        self._instantiate()
        z0 = self._initialize_case(case)

        try:
            result = self._simulate_case(
                signals=signals,
                mode=mode,
                case=case,
                z0=z0,
                duration=duration,
                stream_logs=stream_logs,
            )
        finally:
            self.terminate()

        for key, value in case.items():
            if key not in {"_input_profiles", "_controller"} and "[" not in key:
                result[key] = value

        result["_case_label"] = label
        result["_run_id"] = run_id

        return result

    # ============================================================
    # FMU LIFECYCLE
    # ============================================================

    def _instantiate(self):
        self.fmu = FMU2Model(
            guid=self.model_description.guid,
            unzipDirectory=self.unzipdir,
            modelIdentifier=self.model_identifier,
        )

        self.fmu.instantiate()

    def _initialize_case(self, case):
        if self.fmu is None:
            raise RuntimeError("FMU has not been instantiated")

        if self.use_snapshot and self.snapshot_file.exists():
            data = np.load(self.snapshot_file)
            x_plant = np.asarray(data["x"], dtype=float)
            self._t_global0 = float(data["t"])
        else:
            x_plant = np.zeros(self.nx)
            self._t_global0 = 0.0

        self._active_case = case

        self.fmu.setupExperiment(startTime=self._t_global0)
        self.fmu.enterInitializationMode()

        for name, value in case.get("_parameters", {}).items():
            self._set_real(name, value)

        self.fmu.exitInitializationMode()

        if self.use_snapshot and self.snapshot_file.exists():
            self.fmu.setTime(self._t_global0)
            self.fmu.setContinuousStates(self._ptr(x_plant), self.nx)
        else:
            self.fmu.getContinuousStates(self._ptr(x_plant), self.nx)

        x_ctrl = self._controller_initial_state(case)

        self.t = 0.0
        self.call_count = 0
        self._last_progress_print_t = -np.inf

        return np.concatenate([x_plant, x_ctrl])

    def terminate(self):
        if self.fmu is None:
            return

        try:
            self.fmu.terminate()
        except Exception:
            pass

        try:
            self.fmu.freeInstance()
        except Exception:
            pass

        self.fmu = None

    # ============================================================
    # SNAPSHOT INIT
    # ============================================================

    def _ensure_initialized_snapshot(self):
        if self.snapshot_file.exists():
            print(
                f"Using cached FMU initialization snapshot: {self.snapshot_file}",
                flush=True,
            )
            return

        print(
            f"Creating FMU initialization snapshot: {self.snapshot_file}",
            flush=True,
        )

        self._instantiate()

        try:
            self.fmu.setupExperiment(startTime=0.0)
            self.fmu.enterInitializationMode()

            self._apply_init_values()

            self.fmu.exitInitializationMode()

            x0 = np.zeros(self.nx)
            self.fmu.getContinuousStates(self._ptr(x0), self.nx)

            if self.init_duration <= 0.0:
                np.savez(self.snapshot_file, t=0.0, x=x0)
                print("Saved FMU initialization snapshot at t=0.0", flush=True)
                return

            dx = np.zeros(self.nx)

            last_print_t = -1.0

            def rhs_init(t, x):
                nonlocal last_print_t

                if t >= last_print_t + 0.05:
                    print(
                        f"\rGenerating snapshot: sim t = {t:7.4f} / {self.init_duration:.4f} s",
                        end="",
                        flush=True,
                    )
                    last_print_t = t

                self.fmu.setTime(float(t))

                if self.init_input_values:
                    self._set_inputs(self.init_input_values)

                self.fmu.setContinuousStates(self._ptr(x), self.nx)
                self.fmu.getDerivatives(self._ptr(dx), self.nx)

                return dx.copy()

            sol = solve_ivp(
                rhs_init,
                (0.0, self.init_duration),
                x0,
                method=self.init_solver,
                rtol=self.rtol,
                atol=self.atol,
                max_step=self.init_max_step,
            )

            if not sol.success:
                raise RuntimeError(f"FMU initialization failed: {sol.message}")

            x_final = sol.y[:, -1]
            t_final = float(sol.t[-1])

            np.savez(self.snapshot_file, t=t_final, x=x_final)

            print(
                f"Saved FMU initialization snapshot at t={t_final:.3f}",
                flush=True,
            )

        finally:
            self.terminate()

    # ============================================================
    # SIMULATION
    # ============================================================

    def _simulate_case(
        self,
        signals,
        mode,
        case,
        z0,
        duration,
        stream_logs=False,
    ):
        if duration <= 0.0:
            raise ValueError(f"Case duration must be positive. Got {duration}")

        t_eval = self._make_t_eval(duration)
        events = self._make_events(case)

        sol = solve_ivp(
            self.rhs,
            (0.0, duration),
            z0,
            method=self.solver,
            rtol=self.rtol,
            atol=self.atol,
            max_step=self.max_step,
            t_eval=t_eval,
            events=events,
        )

        print(flush=True)
        
        if not sol.success:
            raise RuntimeError(
                f"FMU simulation failed for {self._case_label(case)}: "
                f"{sol.message}"
            )

        if events is not None and sol.t_events:
            if len(sol.t_events[0]) > 0:
                print(
                    f"[FMU] steady-state detected for {self._case_label(case)} "
                    f"at t={sol.t_events[0][0]:.3f} s",
                    flush=True,
                )

        self.t = float(sol.t[-1])
        self.z = sol.y[:, -1].copy()

        if stream_logs:
            print(
                f"[FMU] finished {self._case_label(case)} "
                f"at t={self.t:.3f}, rhs calls={self.call_count}",
                flush=True,
            )

        if mode == "raw":
            return self._extract_raw(signals, sol.t, sol.y)

        if mode in {"steady", "last"}:
            return self._extract_last(signals, sol.t[-1], sol.y[:, -1])

        raise ValueError(f"Unsupported extraction mode: {mode}")

    def rhs(self, t, z):
        if self.fmu is None:
            raise RuntimeError("FMU has not been instantiated")

        self.call_count += 1

        progress_dt = 0.25

        if t >= self._last_progress_print_t + progress_dt:
            case_label = self._case_label(self._active_case or {})
            duration = self._case_duration(self._active_case or {})

            print(
                f"\r[FMU] {case_label}: sim t = {t:7.3f} / {duration:.3f} s",
                end="",
                flush=True,
            )

            self._last_progress_print_t = t

        x_plant, x_ctrl = self._split_state(z)

        self.fmu.setTime(self._global_time(t))
        self.fmu.setContinuousStates(self._ptr(x_plant), self.nx)

        dx_ctrl = self._apply_inputs_and_controller(
            t=float(t),
            x_plant=x_plant,
            x_ctrl=x_ctrl,
            need_derivatives=True,
        )

        self.fmu.getDerivatives(self._ptr(self.dx_buffer), self.nx)

        return np.concatenate([self.dx_buffer.copy(), dx_ctrl])

    # ============================================================
    # INPUTS + PYTHON CONTROLLERS
    # ============================================================

    def _apply_inputs_and_controller(
        self,
        t,
        x_plant,
        x_ctrl,
        need_derivatives,
    ):
        case = self._active_case or {}

        values = {}

        # Constant FMU inputs.
        values.update(case.get("_input_values", {}))

        # Convenience: direct non-underscore case keys can set matching FMU inputs.
        for key, value in case.items():
            if key.startswith("_"):
                continue

            if key in self.input_vrs:
                values[key] = value

        # Time-varying FMU inputs.
        for name, profile in case.get("_input_profiles", {}).items():
            values[name] = self._profile_value(profile, t)

        dx_ctrl = np.zeros_like(x_ctrl, dtype=float)

        controller = case.get("_controller")
        if controller is not None:
            ctrl_values, dx_ctrl = self._controller_outputs(
                controller=controller,
                t=t,
                x_ctrl=x_ctrl,
                need_derivatives=need_derivatives,
            )

            values.update(ctrl_values)

        if values:
            self._set_inputs(values)

        return dx_ctrl

    def _controller_initial_state(self, case):
        controller = case.get("_controller")

        if controller is None:
            return np.zeros(0, dtype=float)

        ctype = controller.get("type")

        if ctype == "steady_state_eval_radius_velocity_pi":
            return np.array(
                [
                    float(controller.get("curv_integral_0", 0.0)),
                    float(controller.get("vel_integral_0", 0.0)),
                ],
                dtype=float,
            )

        raise ValueError(f"Unsupported controller type: {ctype}")

    def _controller_outputs(
        self,
        controller,
        t,
        x_ctrl,
        need_derivatives,
    ):
        ctype = controller.get("type")

        if ctype == "steady_state_eval_radius_velocity_pi":
            return self._steady_state_eval_radius_velocity_pi(
                controller=controller,
                t=t,
                x_ctrl=x_ctrl,
                need_derivatives=need_derivatives,
            )

        raise ValueError(f"Unsupported controller type: {ctype}")

    def _steady_state_eval_radius_velocity_pi(
        self,
        controller,
        t,
        x_ctrl,
        need_derivatives,
    ):
        if len(x_ctrl) != 2:
            raise ValueError(
                "steady_state_eval_radius_velocity_pi expects two controller states: "
                "[curv_integral, vel_integral]"
            )

        curv_integral = float(x_ctrl[0])
        vel_integral = float(x_ctrl[1])

        vel_x = self._get_real(controller.get("vel_x_output", "velX"))
        vel_y = self._get_real(controller.get("vel_y_output", "velY"))
        yaw_rate = self._get_real(controller.get("yaw_rate_output", "yawVel"))

        speed_floor = float(controller.get("speed_floor", 0.1))
        speed = float(np.sqrt(vel_x**2 + vel_y**2))
        speed_safe = max(speed, speed_floor)

        curvature = yaw_rate / speed_safe

        target_curvature = float(controller["target_curvature"])
        target_velocity = float(controller["target_velocity"])

        ramp = self._smooth_ramp(
            t=t,
            start=float(controller.get("curv_ramp_start", 1.0)),
            duration=float(controller.get("curv_ramp_duration", 0.2)),
        )

        curv_error = ramp * (target_curvature - curvature)
        vel_error = target_velocity - speed

        curv_ti = float(controller.get("curv_ti", 0.02))
        vel_ti = float(controller.get("vel_ti", 1.0))

        curv_kp = float(controller.get("curv_kp", 3.0))
        vel_kp = float(controller.get("vel_kp", 200.0))

        if curv_ti <= 0.0:
            d_curv_integral = 0.0
        else:
            d_curv_integral = curv_error / curv_ti

        if vel_ti <= 0.0:
            d_vel_integral = 0.0
        else:
            d_vel_integral = vel_error / vel_ti

        steer = curv_kp * (curv_error + curv_integral)
        drive_torque = vel_kp * (vel_error + vel_integral)

        steer = float(
            np.clip(
                steer,
                float(controller.get("steer_min", -np.inf)),
                float(controller.get("steer_max", np.inf)),
            )
        )

        drive_torque = float(
            np.clip(
                drive_torque,
                float(controller.get("drive_torque_min", -np.inf)),
                float(controller.get("drive_torque_max", np.inf)),
            )
        )

        values = {
            controller.get("steer_input", "steerCommand"): steer,
            controller.get("drive_torque_input", "driveTorqueCommand"): drive_torque,
        }

        if need_derivatives:
            dx_ctrl = np.array([d_curv_integral, d_vel_integral], dtype=float)
        else:
            dx_ctrl = np.zeros(2, dtype=float)

        return values, dx_ctrl

    def _smooth_ramp(self, t, start, duration):
        if duration <= 0.0:
            return 1.0 if t >= start else 0.0

        u = (t - start) / duration
        u = float(np.clip(u, 0.0, 1.0))

        # Smoothstep, close enough to Modelica smooth(1, min/max ramp)
        return u * u * (3.0 - 2.0 * u)

    def _set_inputs(self, values):
        vrs = []
        reals = []

        for name, value in values.items():
            if name not in self.input_vrs:
                raise KeyError(
                    f"FMU input not found: {name}\n"
                    f"Available FMU inputs:\n"
                    + "\n".join(sorted(self.input_vrs))
                )

            vrs.append(self.input_vrs[name])
            reals.append(float(value))

        self.fmu.setReal(vrs, reals)

    def _profile_value(self, profile, t):
        if isinstance(profile, dict):
            tp = np.asarray(profile["time"], dtype=float)
            yp = np.asarray(profile["value"], dtype=float)
        else:
            tp = np.asarray(profile[0], dtype=float)
            yp = np.asarray(profile[1], dtype=float)

        if tp.ndim != 1 or yp.ndim != 1:
            raise ValueError("Input profile time/value arrays must be 1D")

        if len(tp) != len(yp):
            raise ValueError("Input profile time/value arrays must have same length")

        if len(tp) < 2:
            raise ValueError("Input profile must have at least two points")

        return float(np.interp(float(t), tp, yp, left=yp[0], right=yp[-1]))

    # ============================================================
    # OUTPUTS
    # ============================================================

    def _extract_raw(self, signals, times, states):
        out = {"time": np.asarray(times, dtype=float)}
        values = {signal: [] for signal in signals}

        for j, t in enumerate(times):
            z = states[:, j]
            sample = self._sample_outputs(signals, t, z)

            for signal in signals:
                values[signal].append(sample[signal])

        for signal in signals:
            out[signal] = np.asarray(values[signal], dtype=float)

        return out

    def _extract_last(self, signals, t, z):
        return self._sample_outputs(signals, t, z)

    def _sample_outputs(self, signals, t, z):
        if self.fmu is None:
            raise RuntimeError("FMU has not been instantiated")

        x_plant, x_ctrl = self._split_state(z)

        self.fmu.setTime(self._global_time(t))
        self.fmu.setContinuousStates(self._ptr(x_plant), self.nx)

        # Apply controller/input values at the sampled point before reading outputs.
        self._apply_inputs_and_controller(
            t=float(t),
            x_plant=x_plant,
            x_ctrl=x_ctrl,
            need_derivatives=False,
        )

        out = {}

        for signal in signals:
            out[signal] = self._get_real(signal)

        return out

    def _get_real(self, name):
        if name not in self.vrs:
            raise KeyError(
                f"FMU variable not found: {name}\n"
                f"Available variables include:\n"
                + "\n".join(sorted(list(self.vrs))[:120])
            )

        return float(self.fmu.getReal([self.vrs[name]])[0])

    # ============================================================
    # HELPERS
    # ============================================================

    def _apply_init_values(self):
        for name, value in self.init_parameters.items():
            self._set_real(name, value)

        if self.init_input_values:
            self._set_inputs(self.init_input_values)
            
    def _make_events(self, case):
        steady = case.get("_steady_state")

        if steady is None:
            return None

        stype = steady.get("type")

        if stype == "steady_state_eval_radius_velocity":
            return self._make_steady_state_eval_steady_event(steady)

        raise ValueError(f"Unsupported steady-state detector type: {stype}")


    def _make_steady_state_eval_steady_event(self, steady):
        min_time = float(steady.get("min_time", 1.5))
        curvature_tol = float(steady.get("curvature_tol", 2.0e-4))
        velocity_tol = float(steady.get("velocity_tol", 0.10))
        speed_floor = float(steady.get("speed_floor", 0.1))

        target_curvature = float(steady["target_curvature"])
        target_velocity = float(steady["target_velocity"])

        vel_x_output = steady.get("vel_x_output", "velX")
        vel_y_output = steady.get("vel_y_output", "velY")
        yaw_rate_output = steady.get("yaw_rate_output", "yawVel")

        def event(t, z):
            if t < min_time:
                return 1.0

            x_plant, x_ctrl = self._split_state(z)

            self.fmu.setTime(self._global_time(t))
            self.fmu.setContinuousStates(self._ptr(x_plant), self.nx)

            self._apply_inputs_and_controller(
                t=float(t),
                x_plant=x_plant,
                x_ctrl=x_ctrl,
                need_derivatives=False,
            )

            vel_x = self._get_real(vel_x_output)
            vel_y = self._get_real(vel_y_output)
            yaw_rate = self._get_real(yaw_rate_output)

            speed = float(np.sqrt(vel_x**2 + vel_y**2))
            curvature = yaw_rate / max(speed, speed_floor)

            curvature_err = abs(curvature - target_curvature)
            velocity_err = abs(speed - target_velocity)

            curvature_margin = curvature_err / max(curvature_tol, 1e-12)
            velocity_margin = velocity_err / max(velocity_tol, 1e-12)

            return max(curvature_margin, velocity_margin) - 1.0

        event.terminal = True
        event.direction = -1.0

        return event

    def _case_duration(self, case):
        if "_duration" in case:
            return float(case["_duration"])

        if "_stopTime" in case:
            return float(case["_stopTime"])

        if "stopTime" in case:
            return float(case["stopTime"])

        return 1.0

    def _make_t_eval(self, duration):
        if self.output_dt is None:
            return None

        dt = float(self.output_dt)

        if dt <= 0.0:
            return None

        t_eval = np.arange(0.0, duration + 0.5 * dt, dt)

        if len(t_eval) == 0 or t_eval[-1] < duration:
            t_eval = np.append(t_eval, duration)

        t_eval[-1] = min(t_eval[-1], duration)

        return np.unique(t_eval)

    def _set_real(self, name, value):
        if name not in self.vrs:
            raise KeyError(
                f"FMU variable not found: {name}\n"
                f"Available variables include:\n"
                + "\n".join(sorted(list(self.vrs))[:120])
            )

        self.fmu.setReal([self.vrs[name]], [float(value)])

    def _extract_state_names(self):
        names = []

        for var in self.model_description.modelVariables:
            derivative = getattr(var, "derivative", None)

            if derivative is None:
                continue

            if hasattr(derivative, "name"):
                names.append(derivative.name)
            else:
                match = next(
                    (
                        v
                        for v in self.model_description.modelVariables
                        if v.valueReference == derivative
                    ),
                    None,
                )

                if match is not None:
                    names.append(match.name)

        if len(names) != self.nx:
            names = [f"x{i}" for i in range(self.nx)]

        return names

    def _ptr(self, x):
        x = np.ascontiguousarray(x, dtype=np.float64)
        return x.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

    def _split_state(self, z):
        z = np.asarray(z, dtype=float)
        return z[: self.nx], z[self.nx :]

    def _global_time(self, t):
        return self._t_global0 + float(t)

    def _case_label(self, case):
        mode = case.get("_mode", case.get("mode", "case"))

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

    def _worker_config(self):
        return {
            "simulation": {
                "fmu_path": str(self.fmu_path),
                "snapshot_file": str(self.snapshot_file),
                "solver": self.solver,
                "rtol": self.rtol,
                "atol": self.atol,
                "max_step": self.max_step,
                "output_dt": self.output_dt,
                "init_duration": self.init_duration,
                "init_solver": self.init_solver,
                "init_max_step": self.init_max_step,
                "use_snapshot": self.use_snapshot,
                "init_parameters": self.init_parameters,
                "init_input_values": self.init_input_values,
            }
        }


def _run_fmu_case_worker(
    config,
    signals,
    mode,
    case,
    cleanup,
    stream_logs,
):
    runner = FMURunner.from_config(config)

    print(f"started {runner._case_label(case)}", flush=True)

    return runner.run_case(
        signals=signals,
        mode=mode,
        case=case,
        cleanup=cleanup,
        stream_logs=stream_logs,
    )