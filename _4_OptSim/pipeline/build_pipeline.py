"""build_pipeline.py — Pipelined compile → run per variant.

Each variant is compiled and its simulation is run in one atomic unit of work.
Workers return a log buffer rather than printing directly so output is printed
atomically per variant, preventing interleaved terminal noise when running
multiple workers in parallel.
"""

from __future__ import annotations

import sys
from concurrent.futures import ProcessPoolExecutor, as_completed
from pathlib import Path

from pipeline.compiler import (
    compile_variant,
    _should_compile,
    load_compiler_config,
    DEFAULT_MOS_TEMPLATE,
    DEFAULT_DOE_CONFIG,
    DEFAULT_ARCHITECTURE_CONFIG,
    DEFAULT_REPORT_WRAPPER,
    DEFAULT_STEADY_STATE_SIM,
    DEFAULT_STEADY_STATE_CONFIG,
    DEFAULT_MODELICA_RUNNER,
)
from pipeline.batch import run_variant, _csv_is_valid
from pipeline._pipeline_hash import (
    check_pipeline_hash,
    write_pipeline_hash,
)

DOE_DIR = Path(__file__).resolve().parent.parent


# ---------------------------------------------------------------------------
# Per-variant pipelined worker
# ---------------------------------------------------------------------------

def _build_and_run_worker(args: tuple) -> tuple[str, bool, str]:
    """Compile one variant then immediately run its simulation.

    Returns (variant_name, overall_success, log_lines).
    Workers never print — caller prints the log atomically.
    """
    (
        variant_dir_str,
        standards,
        boblib_path_str,
        template_path_str,
        timeout,
    ) = args

    variant_dir = Path(variant_dir_str)
    boblib_path = Path(boblib_path_str)
    template_path = Path(template_path_str)

    lines: list[str] = []
    overall_ok = True

    for standard, standard_cfg in standards.items():
        # ── Compile ────────────────────────────────────────────────────────
        if _should_compile(variant_dir, standard, standard_cfg):
            ok = compile_variant(
                variant_dir, standard, standard_cfg, boblib_path, template_path
            )
            lines.append(f"  compile  {standard}: {'ok' if ok else 'FAILED'}")
            if not ok:
                overall_ok = False
                continue
        else:
            lines.append(f"  compile  {standard}: cached")

        # ── Run sim immediately after compile ──────────────────────────────
        csv = variant_dir / "results" / standard / "metrics.csv"
        if _csv_is_valid(csv):
            lines.append(f"  simulate {standard}: cached")
        else:
            ok = run_variant(variant_dir, standard, standard_cfg, timeout)
            lines.append(f"  simulate {standard}: {'ok' if ok else 'FAILED'}")
            if not ok:
                overall_ok = False

    return variant_dir.name, overall_ok, "\n".join(lines)


# ---------------------------------------------------------------------------
# Pipelined build stage (replaces compile_all + run_all)
# ---------------------------------------------------------------------------

def build_all(
    population_dir: Path,
    compiler_config_path: Path = DOE_DIR / "configs/compiler_config.yaml",
    template_path: Path = DEFAULT_MOS_TEMPLATE,
    doe_config_path: Path = DEFAULT_DOE_CONFIG,
    architecture_config_path: Path = DEFAULT_ARCHITECTURE_CONFIG,
) -> None:
    """Compile + run every variant in one pipelined pass.

    - Compiles each variant then immediately runs its simulation.
    - max_workers controls parallelism across variants (from compiler_config.yaml).
    - Output is buffered per variant and printed atomically — no interleaving.
    - Skips variants that are already compiled and simulated.
    """
    cfg = load_compiler_config(compiler_config_path)
    standards: dict[str, dict] = cfg["standards"]
    max_workers: int = cfg.get("max_workers", 2)
    timeout: int = cfg.get("batch", {}).get("timeout", 300)

    config_dir = compiler_config_path.resolve().parent
    boblib_path = (config_dir / cfg["boblib_path"]).resolve()

    if not boblib_path.exists():
        raise FileNotFoundError(
            f"BobLib not found at {boblib_path}. Run: git submodule update --init --recursive"
        )

    check_pipeline_hash(
        population_dir,
        doe_config_path,
        compiler_config_path,
        boblib_path,
        architecture_config_path,
        (
            DEFAULT_REPORT_WRAPPER,
            DEFAULT_STEADY_STATE_SIM,
            DEFAULT_STEADY_STATE_CONFIG,
            DEFAULT_MODELICA_RUNNER,
        ),
    )

    variant_dirs = sorted(population_dir.glob("variant_????"))
    if not variant_dirs:
        raise RuntimeError(f"No variant dirs found in {population_dir}")

    total = len(variant_dirs)

    # Determine which variants still have work to do (compile or sim outstanding)
    def _needs_work(vdir: Path) -> bool:
        for standard, standard_cfg in standards.items():
            if _should_compile(vdir, standard, standard_cfg):
                return True
            csv = vdir / "results" / standard / "metrics.csv"
            if not _csv_is_valid(csv):
                return True
        return False

    work_dirs = [vdir for vdir in variant_dirs if _needs_work(vdir)]
    n_skipped = total - len(work_dirs)

    if not work_dirs:
        print(f"All {total} variants already built and simulated — nothing to do\n")
        return

    print(
        f"Building {len(work_dirs)} of {total} variant(s) "
        f"({n_skipped} fully cached, {max_workers} worker(s))...\n"
    )

    work_items = [
        (
            str(vdir),
            standards,
            str(boblib_path),
            str(template_path),
            timeout,
        )
        for vdir in work_dirs
    ]

    completed = 0
    n_ok = 0

    with ProcessPoolExecutor(max_workers=max_workers) as pool:
        futures = {pool.submit(_build_and_run_worker, item): item for item in work_items}
        for future in as_completed(futures):
            variant_name, success, log = future.result()
            completed += 1
            status = "ok" if success else "FAILED"
            if success:
                n_ok += 1
            # Print atomically — all output for this variant in one block
            print(f"[{completed:>{len(str(len(work_dirs)))}}/{len(work_dirs)}] {variant_name}  {status}")
            print(log)

    n_fail = len(work_dirs) - n_ok
    print()
    print(f"Build complete: {n_ok}/{len(work_dirs)} ok, {n_fail} failed")

    write_pipeline_hash(
        population_dir,
        doe_config_path,
        compiler_config_path,
        boblib_path,
        architecture_config_path,
        (
            DEFAULT_REPORT_WRAPPER,
            DEFAULT_STEADY_STATE_SIM,
            DEFAULT_STEADY_STATE_CONFIG,
            DEFAULT_MODELICA_RUNNER,
        ),
    )


# ---------------------------------------------------------------------------
# Entrypoint
# ---------------------------------------------------------------------------

if __name__ == "__main__":
    population = DOE_DIR / "population"
    config = Path(sys.argv[1]) if len(sys.argv) > 1 else DOE_DIR / "configs/compiler_config.yaml"
    build_all(population, compiler_config_path=config)
