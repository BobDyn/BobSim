"""batch.py — Run compiled OMC executables for all variants.

For each variant_XXXX/build/<standard>/ that has a compiled executable:
  1. Skip if results.csv already exists and is valid (correct row count)
  2. Create variant_XXXX/results/<standard>/
  3. Run the executable with -r results.csv
  4. Verify the CSV was produced and has expected rows
  5. Write run_error_<standard>.log on failure and continue

Parallelism: controlled by batch.max_workers in compiler_config.yaml.
TACC: set max_workers to match your SLURM allocation's cores-per-node.
"""

from __future__ import annotations

import subprocess
import sys
from concurrent.futures import ProcessPoolExecutor, as_completed
from pathlib import Path

import pandas as pd
import yaml

# ---------------------------------------------------------------------------
# Config
# ---------------------------------------------------------------------------

DEFAULT_CONFIG = Path(__file__).parent / "configs/compiler_config.yaml"

# Minimum rows expected in a valid results CSV (row 0 + at least 1 timestep)
MIN_RESULT_ROWS = 2


def load_config(config_path: Path = DEFAULT_CONFIG) -> dict:
    with open(config_path) as f:
        return yaml.safe_load(f)


# ---------------------------------------------------------------------------
# CSV validation
# ---------------------------------------------------------------------------

def _csv_is_valid(csv_path: Path) -> bool:
    """Return True if results CSV exists and has enough rows to be valid.

    Guards against partial writes from crashed simulations.
    """
    if not csv_path.exists():
        return False
    try:
        df = pd.read_csv(csv_path, nrows=MIN_RESULT_ROWS + 1)
        return len(df) >= MIN_RESULT_ROWS
    except Exception:
        return False


# ---------------------------------------------------------------------------
# Single variant run
# ---------------------------------------------------------------------------

def run_variant(
        variant_dir: Path,
        standard: str,
        standard_cfg: dict,
        timeout: int,
) -> bool:
    """Run one variant's executable for one standard.

    Returns True on success, False on failure.
    Writes run_error_<standard>.log on failure.
    """
    build_dir = variant_dir / "build" / standard
    exe = _find_exe(build_dir, standard_cfg)

    if exe is None:
        _write_error(variant_dir, standard, "Executable not found — did compiler.py run?")
        return False

    results_dir = variant_dir / "results" / standard
    results_dir.mkdir(parents=True, exist_ok=True)
    results_csv = results_dir / "results.csv"

    try:
        result = subprocess.run(
            [str(exe), "-r", str(results_csv)],
            capture_output=True,
            text=True,
            cwd=str(build_dir),
            timeout=timeout,
        )
    except subprocess.TimeoutExpired:
        _write_error(variant_dir, standard, f"Simulation timed out after {timeout}s")
        return False
    except Exception as e:
        _write_error(variant_dir, standard, str(e))
        return False

    if not _csv_is_valid(results_csv):
        error_msg = (result.stdout + "\n" + result.stderr).strip()
        _write_error(variant_dir, standard, error_msg or "No valid results.csv produced")
        return False

    return True


def _find_exe(build_dir: Path, standard_cfg: dict) -> Path | None:
    model = standard_cfg["model"]       # BobLib.Standards.SteadyStateEval
    short = model.split(".")[-1]        # SteadyStateEval
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


# ---------------------------------------------------------------------------
# Worker (top-level for pickling with ProcessPoolExecutor)
# ---------------------------------------------------------------------------

def _worker(args: tuple) -> tuple[str, str, bool]:
    """Unpack args and run one variant. Returns (variant_name, standard, success)."""
    variant_dir, standard, standard_cfg, timeout = args
    success = run_variant(variant_dir, standard, standard_cfg, timeout)
    return variant_dir.name, standard, success


# ---------------------------------------------------------------------------
# Run all variants
# ---------------------------------------------------------------------------

def run_all(
        population_dir: Path,
        config_path: Path = DEFAULT_CONFIG,
) -> dict[str, list[Path]]:
    """Run all compiled variants for all standards.

    Skips variants that already have valid results.csv files.
    Returns dict mapping standard -> list of successful results.csv paths.
    Failed variants are logged and skipped.
    """
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

    # Collect already-valid results
    for vdir in variant_dirs:
        for standard in standards:
            csv = vdir / "results" / standard / "results.csv"
            if _csv_is_valid(csv):
                results[standard].append(csv)

    # Build work list — skip variants with valid results
    work = [
        (variant_dir, standard, standard_cfg, timeout)
        for variant_dir in variant_dirs
        for standard, standard_cfg in standards.items()
        if not _csv_is_valid(variant_dir / "results" / standard / "results.csv")
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
                csv = variant_dir / "results" / standard / "results.csv"
                results[standard].append(csv)

    print()
    for standard in standards:
        n_ok = len(results[standard])
        n_fail = total - n_ok
        print(f"{standard}: {n_ok}/{total} ran ok, {n_fail} failed")

    return results


# ---------------------------------------------------------------------------
# Entrypoint
# ---------------------------------------------------------------------------

if __name__ == "__main__":
    population = Path(__file__).parent / "population"
    config = Path(sys.argv[1]) if len(sys.argv) > 1 else DEFAULT_CONFIG

    print(f"Config:         {config}")
    print(f"Population dir: {population}\n")

    results = run_all(population, config_path=config)
    total_ok = sum(len(v) for v in results.values())
    print(f"\nTotal results ready: {total_ok}")