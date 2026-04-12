from __future__ import annotations

import os
import shutil
import subprocess
from concurrent.futures import ProcessPoolExecutor, as_completed
from pathlib import Path
from typing import Any, Dict, List, Optional, Set

import numpy as np

from GeneralSim.output_schema import OutputSchema


def _run_case_worker(
    build_dir,
    exec_name,
    schema,
    case,
    idx,
    simulation,
    cleanup,
):
    sim = GeneralSim(
        build_dir=build_dir,
        exec_name=exec_name,
        simulation=simulation,
    )
    tag = f"run_{idx}"

    data = sim.run_raw(
        overrides=case,
        tag=tag,
        cleanup=cleanup,
        output_filter=schema.build_filter(),
    )

    schema.validate(sim, data)
    out = schema.extract(sim, data)
    out.update(case)
    return idx, out


class GeneralSim:
    def __init__(
        self,
        build_dir: str | Path,
        exec_name: str,
        simulation: Optional[Dict[str, Any]] = None,
    ) -> None:
        self.build_dir = Path(build_dir).resolve()
        self.exec_name = exec_name
        self.simulation = simulation or {}

        self.results_dir = self.build_dir.parent / "results"
        self.results_dir.mkdir(parents=True, exist_ok=True)

        self.executable = self._resolve_executable()
        self.init_file = self.build_dir / f"{exec_name}_init.xml"

        if not self.init_file.exists():
            raise FileNotFoundError(f"Missing init file: {self.init_file}")

    def _resolve_executable(self) -> Path:
        exe = self.build_dir / self.exec_name
        if exe.exists():
            return exe

        exe_win = exe.with_suffix(".exe")
        if exe_win.exists():
            return exe_win

        raise FileNotFoundError(f"Executable not found: {exe}")

    def _norm(self, name: str) -> str:
        return name.replace(".", "").replace("[", "").replace("]", "").replace('"', "")

    def _make_run_dir(self, tag: Optional[str]) -> Path:
        pid = os.getpid()
        run_name = tag if tag else "run"
        run_dir = self.results_dir / f"{run_name}_pid{pid}"
        run_dir.mkdir(parents=True, exist_ok=True)
        return run_dir

    def run_raw(
        self,
        overrides: Dict[str, float],
        tag: Optional[str] = None,
        timeout: Optional[float] = None,
        cleanup: bool = False,
        output_filter: Optional[str] = None,
        keep: Optional[Set[str]] = None,
    ) -> Dict[str, np.ndarray]:
        sim_cfg = self.simulation

        solver = sim_cfg.get("solver", "dassl")
        output_format = sim_cfg.get("output_format", "csv")
        log_level = sim_cfg.get("log_level", "LOG_STATS")
        no_grid = sim_cfg.get("no_grid", True)
        no_event_emit = sim_cfg.get("no_event_emit", False)

        extra_overrides = sim_cfg.get("extra_overrides", {})
        merged = {**overrides, **extra_overrides}

        override_str = ",".join(f"{k}={v}" for k, v in merged.items())

        result_name = f"{self.exec_name}_{tag}" if tag else self.exec_name
        run_dir = self._make_run_dir(tag)
        csv_file = run_dir / f"{result_name}.csv"

        cmd = [
            f"./{self.executable.name}",
            f"-override={override_str}",
            f"-r={csv_file.resolve()}",
            f"-s={solver}",
            f"-outputFormat={output_format}",
            f"-lv={log_level}",
        ]

        if no_grid:
            cmd.append("-noEquidistantTimeGrid")

        if no_event_emit:
            cmd.append("-noEventEmit")

        if output_filter:
            cmd.append(f"-variableFilter={output_filter}")

        proc = subprocess.run(
            cmd,
            cwd=self.build_dir,
            capture_output=True,
            text=True,
            timeout=timeout,
        )

        if proc.returncode != 0:
            raise RuntimeError(
                f"Simulation failed\n\n"
                f"Overrides: {merged}\n"
                f"Command: {' '.join(cmd)}\n\n"
                f"STDOUT:\n{proc.stdout}\n\n"
                f"STDERR:\n{proc.stderr}"
            )

        if not csv_file.exists():
            raise FileNotFoundError(f"Missing CSV output: {csv_file}")

        out = self._load_csv(csv_file, keep)

        if cleanup:
            csv_file.unlink(missing_ok=True)
            shutil.rmtree(run_dir, ignore_errors=True)

        return out

    def _load_csv(
        self,
        path: Path,
        keep: Optional[Set[str]] = None,
    ) -> Dict[str, np.ndarray]:
        data = np.genfromtxt(
            path,
            delimiter=",",
            names=True,
            dtype=None,
            encoding="utf-8",
        )

        if data.dtype.names is None:
            raise ValueError(f"CSV has no named columns: {path}")

        out: Dict[str, np.ndarray] = {}

        for name in data.dtype.names:
            norm = self._norm(name)
            if keep is None or norm in keep:
                out[norm] = np.atleast_1d(data[name])

        return out

    def get(self, data: Dict[str, np.ndarray], key: str) -> np.ndarray:
        norm = self._norm(key)
        if norm not in data:
            raise KeyError(f"{key} not found (normalized: {norm})")
        return data[norm]

    def steady(
        self,
        data: Dict[str, np.ndarray],
        key: str,
        window: int = 10,
        tol: float = 1e-2,
    ) -> float:
        arr = self.get(data, key)
        if len(arr) < window:
            raise RuntimeError(f"Not enough data for steady-state: {key}")

        tail = arr[-window:]
        if np.std(tail) > tol:
            raise RuntimeError(f"{key} not converged (std={np.std(tail):.3e})")

        return float(np.mean(tail))

    def last(
        self,
        data: Dict[str, np.ndarray],
        key: str,
    ) -> float:
        arr = self.get(data, key)
        return float(arr[-1])

    def run_case(
        self,
        schema: OutputSchema,
        overrides: Dict[str, float],
        tag: Optional[str] = None,
        cleanup: bool = False,
    ) -> Dict[str, float]:
        data = self.run_raw(
            overrides=overrides,
            tag=tag,
            cleanup=cleanup,
            output_filter=schema.build_filter(),
        )
        schema.validate(self, data)
        return schema.extract(self, data)

    def run_cases(
        self,
        schema: OutputSchema,
        cases: List[Dict[str, float]],
        cleanup: bool = False,
    ) -> List[Dict[str, float]]:
        results = []

        for i, case in enumerate(cases):
            print(f"[{i + 1}/{len(cases)}] {case}")
            tag = f"run_{i}"
            res = self.run_case(schema, case, tag=tag, cleanup=cleanup)
            res.update(case)
            results.append(res)

        return results

    def run_cases_parallel(
        self,
        schema: OutputSchema,
        cases: List[Dict[str, float]],
        max_workers: Optional[int] = None,
        fail_fast: bool = False,
        cleanup: bool = False,
    ) -> List[Optional[Dict[str, float]]]:
        if max_workers is None:
            print("Auto-detecting CPU cores for parallel execution...")
            cpu_count = os.cpu_count() or 1
            max_workers = max(1, cpu_count - 1)

        results: List[Optional[Dict[str, float]]] = [None] * len(cases)

        with ProcessPoolExecutor(max_workers=max_workers) as exe:
            futures = {
                exe.submit(
                    _run_case_worker,
                    str(self.build_dir),
                    self.exec_name,
                    schema,
                    case,
                    i,
                    self.simulation,
                    cleanup,
                ): i
                for i, case in enumerate(cases)
            }

            for f in as_completed(futures):
                idx = futures[f]
                case = cases[idx]

                try:
                    _, res = f.result()
                    results[idx] = res
                    print(f"✅ Completed [{idx + 1}/{len(cases)}] {case}")
                except Exception as e:
                    print(f"❌ Failed case [{idx + 1}/{len(cases)}] {case}: {e}")
                    if fail_fast:
                        raise

        return results