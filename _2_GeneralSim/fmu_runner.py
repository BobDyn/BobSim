import numpy as np
import ctypes
import pandas as pd
import os
from scipy.integrate import solve_ivp

from fmpy import read_model_description, extract
from fmpy.fmi2 import FMU2Model


class FMURunner:
    def __init__(
        self,
        fmu_path,
        snapshot_file="snapshot_init.npz",
        solver="LSODA",
        rtol=1e-4,
        atol=1e-6,
        max_step=0.01,
    ):
        self.fmu_path = fmu_path
        self.snapshot_file = snapshot_file
        self.solver = solver

        self.rtol = rtol
        self.atol = atol
        self.max_step = max_step

        self._load_fmu()
        self._extract_state_names()
        self._find_inputs()

        self.dx_buffer = np.zeros(self.nx)
        self.call_count = 0

        self.J_cached = None
        self.t_last_jac = -1

        # 🔥 ensure initialization snapshot exists
        self._ensure_initialized_snapshot()

        # default steering profile
        self.set_steer_profile()


    # ----------------------------
    # Setup
    # ----------------------------
    def _load_fmu(self):
        self.model_description = read_model_description(self.fmu_path)
        unzipdir = extract(self.fmu_path)

        self.fmu = FMU2Model(
            guid=self.model_description.guid,
            unzipDirectory=unzipdir,
            modelIdentifier=self.model_description.modelExchange.modelIdentifier
        )

        self.fmu.instantiate()
        self.nx = self.model_description.numberOfContinuousStates


    def _extract_state_names(self):
        names = []

        for var in self.model_description.modelVariables:
            if var.derivative is not None:
                if hasattr(var.derivative, "name"):
                    names.append(var.derivative.name)
                else:
                    state_var = next(
                        v for v in self.model_description.modelVariables
                        if v.valueReference == var.derivative
                    )
                    names.append(state_var.name)

        if len(names) != self.nx:
            print("⚠️ State name mismatch — using fallback names")
            names = [f"x{i}" for i in range(self.nx)]

        self.state_names = names


    def _find_inputs(self):
        for var in self.model_description.modelVariables:
            if var.name == "steerCommand":
                self.steer_vr = var.valueReference
                return
        raise ValueError("steerCommand input not found")


    def _ptr(self, x):
        return x.ctypes.data_as(ctypes.POINTER(ctypes.c_double))


    # ----------------------------
    # 🔥 ONE-TIME INITIALIZATION
    # ----------------------------
    def _ensure_initialized_snapshot(self):
        if os.path.exists(self.snapshot_file):
            print("✅ Using cached initialization snapshot")
            return

        print("⚙️ Running initialization (0 → 2s)...")

        # ----------------------------
        # TEMP FMU INSTANCE
        # ----------------------------
        model_description = read_model_description(self.fmu_path)
        unzipdir = extract(self.fmu_path)

        fmu = FMU2Model(
            guid=model_description.guid,
            unzipDirectory=unzipdir,
            modelIdentifier=model_description.modelExchange.modelIdentifier
        )

        fmu.instantiate()

        nx = model_description.numberOfContinuousStates

        fmu.setupExperiment(startTime=0.0)
        fmu.enterInitializationMode()
        fmu.exitInitializationMode()

        x0 = np.zeros(nx)
        fmu.getContinuousStates(self._ptr(x0), nx)

        dx = np.zeros(nx)

        # ----------------------------
        # RHS with progress printing
        # ----------------------------
        call_count = 0
        last_print_t = -1.0

        def rhs_init(t, x):
            nonlocal call_count, last_print_t
            call_count += 1

            # 🔥 Print every ~0.05s of sim time
            if t - last_print_t > 0.05:
                print(f"[INIT] t = {t:.3f}")
                last_print_t = t

            fmu.setTime(t)
            fmu.setContinuousStates(self._ptr(x), nx)
            fmu.getDerivatives(self._ptr(dx), nx)
            return dx.copy()

        # ----------------------------
        # Jacobian (same as working)
        # ----------------------------
        def jac_init(t, x):
            J = np.zeros((nx, nx))
            f0 = rhs_init(t, x)

            x_pert = x.copy()

            for i in range(nx):
                eps = 1e-6 * max(1.0, abs(x[i]))
                x_pert[i] += eps
                fi = rhs_init(t, x_pert)
                J[:, i] = (fi - f0) / eps
                x_pert[i] -= eps

            return J

        # ----------------------------
        # Solve (same pattern that worked)
        # ----------------------------
        sol = solve_ivp(
            rhs_init,
            (0.0, 2.0),
            x0,
            method="BDF",
            jac=jac_init,
            rtol=1e-4,
            atol=1e-6,
            max_step=1e-3
        )

        if not sol.success:
            raise RuntimeError(f"Initialization failed: {sol.message}")

        x_final = sol.y[:, -1]

        np.savez(self.snapshot_file, t=2.0, x=x_final)

        print(f"[INIT] complete at t = {sol.t[-1]:.3f}")
        print("💾 Initialization snapshot saved")

        # ----------------------------
        # CLEANUP
        # ----------------------------
        fmu.terminate()
        fmu.freeInstance()


    # ----------------------------
    # Initialization
    # ----------------------------
    def initialize(self, use_snapshot=True):
        data = np.load(self.snapshot_file)

        self.x = data["x"]
        self.t_global = float(data["t"])

        print(f"🔁 Loaded initialized state (t = {self.t_global:.2f})")

        self.fmu.setupExperiment(startTime=self.t_global)
        self.fmu.enterInitializationMode()
        self.fmu.exitInitializationMode()

        self.fmu.setTime(self.t_global)
        self.fmu.setContinuousStates(self._ptr(self.x), self.nx)

        # 🔥 LOCAL time starts at zero
        self.t = 0.0


    # ----------------------------
    # Steering input (LOCAL time)
    # ----------------------------
    def set_steer_profile(
        self,
        amp_deg=5.0,
        freq_hz=1.0,
        start_time=0.0,
        duration=1.0
    ):
        self.steer_amp = np.deg2rad(amp_deg)
        self.steer_freq = freq_hz
        self.steer_start = start_time
        self.steer_end = start_time + duration


    def steer_input(self, t):
        if t < self.steer_start or t > self.steer_end:
            return 0.0
        
        tau = t - self.steer_start

        return self.steer_amp * np.sin(
            2 * np.pi * self.steer_freq * tau
        )


    # ----------------------------
    # RHS
    # ----------------------------
    def rhs(self, t, x):
        self.call_count += 1

        t_global = self.t_global + t

        self.fmu.setTime(t_global)

        steer = self.steer_input(t)
        self.fmu.setReal([self.steer_vr], [steer])

        self.fmu.setContinuousStates(self._ptr(x), self.nx)
        self.fmu.getDerivatives(self._ptr(self.dx_buffer), self.nx)

        return self.dx_buffer.copy()


    def jac(self, t, x):
        if self.J_cached is not None and abs(t - self.t_last_jac) < self.max_step:
            return self.J_cached

        print(f"[JAC] computing at t={t:.6e}")

        J = np.zeros((self.nx, self.nx))
        f0 = self.rhs(t, x)

        x_pert = x.copy()

        for i in range(self.nx):
            eps = 1e-6 * max(1.0, abs(x[i]))

            x_pert[i] += eps
            fi = self.rhs(t, x_pert)

            J[:, i] = (fi - f0) / eps
            x_pert[i] -= eps

        self.J_cached = J
        self.t_last_jac = t

        return J


    # ----------------------------
    # Simulation
    # ----------------------------
    def simulate(self, duration):
        dt_chunk = self.max_step
        t_end = duration

        times = [self.t]
        states = [self.x.copy()]

        while self.t < t_end:
            sol = solve_ivp(
                self.rhs,
                (self.t, min(self.t + dt_chunk, t_end)),
                self.x,
                method=self.solver,
                rtol=self.rtol,
                atol=self.atol,
                max_step=self.max_step,
                jac=self.jac if self.solver in ["Radau", "BDF", "LSODA"] else None
            )

            if not sol.success:
                print(f"❌ Solver failed: {sol.message}")
                break

            self.t = sol.t[-1]
            self.x = sol.y[:, -1]

            times.append(self.t)
            states.append(self.x.copy())

        return np.array(times), np.array(states)


    # ----------------------------
    # Utilities
    # ----------------------------
    def save_csv(self, times, states, filename):
        data = np.column_stack([times, states])
        columns = ["time"] + self.state_names

        df = pd.DataFrame(data, columns=columns)
        df.to_csv(filename, index=False)

        print(f"📁 Saved {filename}")


    def save_snapshot(self):
        print("⏭️ Snapshot saving disabled (using init snapshot only)")


    def terminate(self):
        self.fmu.terminate()
        self.fmu.freeInstance()