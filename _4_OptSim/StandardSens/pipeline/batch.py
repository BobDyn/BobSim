"""Run each configured standard for all compiled variants.

On TACC, set batch.max_workers in compiler_config.yaml to the cores per node.
"""

from __future__ import annotations

import sys
from concurrent.futures import ProcessPoolExecutor, as_completed
from pathlib import Path

import pandas as pd
import yaml

from StandardSens.pipeline.standards import get_standard, run_standard

STANDARD_DIR = Path(__file__).resolve().parents[1]
OPTSIM_DIR = STANDARD_DIR.parent
DEFAULT_CONFIG = STANDARD_DIR / "configs/compiler_config.yaml"

MIN_RESULT_ROWS = 2


def load_config(config_path: Path = DEFAULT_CONFIG) -> dict:
    with open(config_path) as f:
        return yaml.safe_load(f)


def _csv_is_valid(csv_path: Path) -> bool:
    """Return True if the metrics CSV exists and is not a partial write."""
    if not csv_path.exists():
        return False
    try:
        df = pd.read_csv(csv_path, nrows=MIN_RESULT_ROWS + 1)
        return len(df) >= MIN_RESULT_ROWS
    except Exception:
        return False


def run_variant(
        variant_dir: Path,
        standard: str,
        standard_cfg: dict,
        timeout: int,
) -> bool:
    """Run one variant's report wrapper for one standard. Writes run_error_<standard>.log on failure."""
    build_dir = variant_dir / "build" / standard
    exe = _find_exe(build_dir, standard_cfg)

    if exe is None:
        _write_error(variant_dir, standard, "Executable not found — did compiler.py run?")
        return False

    results_dir = variant_dir / "results" / standard
    results_dir.mkdir(parents=True, exist_ok=True)

    try:
        # Dispatch on name. A report run on another standard's executable fails late.
        metrics_csv = run_standard(
            get_standard(standard),
            variant_dir=variant_dir,
            build_dir=build_dir,
            exec_name=standard_cfg["model"],
            timeout=timeout,
        )
    except Exception as e:
        _write_error(variant_dir, standard, str(e))
        return False

    if not _csv_is_valid(metrics_csv):
        _write_error(variant_dir, standard, "No valid metrics.csv produced")
        return False

    return True


def _find_exe(build_dir: Path, standard_cfg: dict) -> Path | None:
    model = standard_cfg["model"]
    short = model.split(".")[-1]
    candidates = [
        build_dir / model,
        build_dir / f"{model}.exe",
        build_dir / short,
        build_dir / f"{short}.exe",
        ]
    for candidate in candidates:
        if candidate.exists():
            return candidate
    return None


def _write_error(variant_dir: Path, standard: str, message: str) -> None:
    log = variant_dir / f"run_error_{standard}.log"
    log.write_text(message)


def _worker(args: tuple) -> tuple[str, str, bool]:
    """Returns (variant_name, standard, success)."""
    variant_dir, standard, standard_cfg, timeout = args
    success = run_variant(variant_dir, standard, standard_cfg, timeout)
    return variant_dir.name, standard, success


def run_all(
        population_dir: Path,
        config_path: Path = DEFAULT_CONFIG,
) -> dict[str, list[Path]]:
    """Run the report for all compiled variants. Returns standard -> metrics.csv paths."""
    cfg = load_config(config_path)
    standards: dict[str, dict] = cfg["standards"]
    batch_cfg: dict = cfg.get("batch", {})
    max_workers: int = batch_cfg.get("max_workers", 2)
    timeout: int = batch_cfg.get("timeout", 300)

    variant_dirs = sorted(population_dir.glob("variant_????"))
    if not variant_dirs:
        raise RuntimeError(f"No variant dirs found in {population_dir}")

    total = len(variant_dirs)
    results: dict[str, list[Path]] = {s: [] for s in standards}

    for vdir in variant_dirs:
        for standard in standards:
            csv = vdir / "results" / standard / "metrics.csv"
            if _csv_is_valid(csv):
                results[standard].append(csv)

    work = [
        (variant_dir, standard, standard_cfg, timeout)
        for variant_dir in variant_dirs
        for standard, standard_cfg in standards.items()
        if not _csv_is_valid(variant_dir / "results" / standard / "metrics.csv")
    ]

    n_skipped = (total * len(standards)) - len(work)

    if not work:
        print(f"All {total} variants already have results — nothing to do\n")
        return results

    print(f"Running {len(work)} simulations ({n_skipped} skipped, "
          f"{max_workers} workers, timeout {timeout}s)\n")

    completed = 0
    with ProcessPoolExecutor(max_workers=max_workers) as pool:
        futures = {pool.submit(_worker, args): args for args in work}
        for future in as_completed(futures):
            variant_name, standard, success = future.result()
            completed += 1
            status = "ok" if success else "FAILED"
            print(f"[{completed:>4}/{len(work)}] {variant_name} / {standard}: {status}")

            if success:
                variant_dir = population_dir / variant_name
                csv = variant_dir / "results" / standard / "metrics.csv"
                results[standard].append(csv)

    print()
    for standard in standards:
        n_ok = len(results[standard])
        n_fail = total - n_ok
        print(f"{standard}: {n_ok}/{total} ran ok, {n_fail} failed")

    return results


if __name__ == "__main__":
    population = OPTSIM_DIR / "Build/StandardSens/population"
    config = Path(sys.argv[1]) if len(sys.argv) > 1 else DEFAULT_CONFIG

    print(f"Config:         {config}")
    print(f"Population dir: {population}\n")

    results = run_all(population, config_path=config)
    total_ok = sum(len(v) for v in results.values())
    print(f"\nTotal results ready: {total_ok}")
