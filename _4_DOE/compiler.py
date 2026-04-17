"""compiler.py — Generate build.mos per variant and compile via OMC.

Reads standards and paths from configs/compiler_config.yaml.
Uses configs/build_template.mos as the OMC script template.
To add a new standard, add an entry in compiler_config.yaml — no Python changes needed.

For each variant_XXXX/ in population/:
  1. Fill in build_template.mos and write to variant_XXXX/build_<standard>.mos
  2. Run omc on it with build dir set to variant_XXXX/build/<standard>/
  3. Verify executable exists (named after full model path e.g. BobLib.Standards.ISO4138)
  4. Write compile_error_<standard>.log on failure

Compilation runs in parallel across variants using ProcessPoolExecutor.
max_workers is configurable in compiler_config.yaml.
"""

from __future__ import annotations

import subprocess
import sys
from concurrent.futures import ProcessPoolExecutor, as_completed
from pathlib import Path

import yaml

# ---------------------------------------------------------------------------
# Paths
# ---------------------------------------------------------------------------

DOE_DIR = Path(__file__).parent
DEFAULT_COMPILER_CONFIG = DOE_DIR / "configs/compiler_config.yaml"
DEFAULT_MOS_TEMPLATE = DOE_DIR / "configs/build_template.mos"


# ---------------------------------------------------------------------------
# Config
# ---------------------------------------------------------------------------

def load_compiler_config(config_path: Path = DEFAULT_COMPILER_CONFIG) -> dict:
    with open(config_path) as f:
        return yaml.safe_load(f)


# ---------------------------------------------------------------------------
# build.mos generation
# ---------------------------------------------------------------------------

def generate_mos(
        variant_mo: Path,
        build_dir: Path,
        boblib_path: Path,
        standard_cfg: dict,
        template_path: Path = DEFAULT_MOS_TEMPLATE,
) -> str:
    """Fill in build_template.mos for one variant + standard."""
    template = template_path.read_text()
    return template.format(
        boblib_path=boblib_path.resolve().as_posix(),
        variant_mo_path=variant_mo.resolve().as_posix(),
        build_dir=build_dir.resolve().as_posix(),
        model=standard_cfg["model"],
        start_time=standard_cfg["start_time"],
        stop_time=standard_cfg["stop_time"],
        intervals=standard_cfg["intervals"],
        tolerance=standard_cfg["tolerance"],
        solver=standard_cfg["solver"],
    )


# ---------------------------------------------------------------------------
# Single variant compilation
# ---------------------------------------------------------------------------

def compile_variant(
        variant_dir: Path,
        standard: str,
        standard_cfg: dict,
        boblib_path: Path,
        template_path: Path = DEFAULT_MOS_TEMPLATE,
) -> bool:
    """Compile one variant for one standard.

    Returns True on success, False on failure.
    Writes compile_error_<standard>.log on failure.
    """
    variant_mo = variant_dir / "variant.mo"
    if not variant_mo.exists():
        _write_error(variant_dir, standard, "variant.mo not found")
        return False

    build_dir = variant_dir / "build" / standard
    build_dir.mkdir(parents=True, exist_ok=True)

    mos_content = generate_mos(
        variant_mo, build_dir, boblib_path, standard_cfg, template_path
    )
    mos_path = variant_dir / f"build_{standard}.mos"
    mos_path.write_text(mos_content)

    try:
        result = subprocess.run(
            ["omc", str(mos_path)],
            capture_output=True,
            text=True,
            cwd=str(variant_dir),
        )
    except FileNotFoundError:
        _write_error(variant_dir, standard, "omc not found on PATH")
        return False

    # OMC exits 0 even on soft failures — verify executable actually exists
    exe = _find_exe(build_dir, standard_cfg)
    if exe is None:
        error_msg = (result.stdout + "\n" + result.stderr).strip()
        _write_error(variant_dir, standard, error_msg)
        return False

    return True


def _find_exe(build_dir: Path, standard_cfg: dict) -> Path | None:
    """Return exe path if it exists.

    OMC names the executable after the full model path e.g.
    BobLib.Standards.ISO4138, not just ISO4138.
    """
    model = standard_cfg["model"]  # e.g. BobLib.Standards.ISO4138
    for candidate in [build_dir / model, build_dir / f"{model}.exe"]:
        if candidate.exists():
            return candidate
    return None


def _write_error(variant_dir: Path, standard: str, message: str) -> None:
    log = variant_dir / f"compile_error_{standard}.log"
    log.write_text(message)


# ---------------------------------------------------------------------------
# Parallel compilation worker
# ---------------------------------------------------------------------------

def _compile_worker(args: tuple) -> tuple[str, str, bool]:
    """Top-level function for ProcessPoolExecutor (must be picklable)."""
    variant_dir, standard, standard_cfg, boblib_path, template_path = args
    success = compile_variant(
        Path(variant_dir), standard, standard_cfg, Path(boblib_path), Path(template_path)
    )
    return str(variant_dir), standard, success


# ---------------------------------------------------------------------------
# Compile all variants
# ---------------------------------------------------------------------------

def compile_all(
        population_dir: Path,
        compiler_config_path: Path = DEFAULT_COMPILER_CONFIG,
        template_path: Path = DEFAULT_MOS_TEMPLATE,
) -> dict[str, list[Path]]:
    """Compile all variants in population_dir for all standards in config.

    Runs variants in parallel using ProcessPoolExecutor.
    Returns dict mapping standard -> list of successful exe paths.
    Failed variants are logged and skipped.
    """
    cfg = load_compiler_config(compiler_config_path)
    standards: dict[str, dict] = cfg["standards"]
    max_workers: int = cfg.get("max_workers", 2)

    # Resolve boblib_path relative to the config file
    config_dir = compiler_config_path.resolve().parent
    boblib_path = (config_dir / cfg["boblib_path"]).resolve()

    if not boblib_path.exists():
        raise FileNotFoundError(
            f"BobLib not found at {boblib_path}. Did you init submodules?\n"
            f"Run: git submodule update --init --recursive"
        )

    if not template_path.exists():
        raise FileNotFoundError(f"build_template.mos not found at {template_path}")

    variant_dirs = sorted(population_dir.glob("variant_????"))
    if not variant_dirs:
        raise RuntimeError(f"No variant dirs found in {population_dir}")

    total = len(variant_dirs)
    results: dict[str, list[Path]] = {s: [] for s in standards}

    # Build all work items: one per (variant, standard) pair
    work_items = [
        (str(vdir), standard, standard_cfg, str(boblib_path), str(template_path))
        for vdir in variant_dirs
        for standard, standard_cfg in standards.items()
    ]

    completed = 0
    print(f"Compiling {total} variants × {len(standards)} standard(s) "
          f"with {max_workers} workers...\n")

    with ProcessPoolExecutor(max_workers=max_workers) as executor:
        futures = {executor.submit(_compile_worker, item): item for item in work_items}
        for future in as_completed(futures):
            variant_dir_str, standard, success = future.result()
            variant_dir = Path(variant_dir_str)
            completed += 1
            status = "ok" if success else "FAILED"
            print(f"[{completed:>4}/{len(work_items)}] {variant_dir.name} / {standard}: {status}")

            if success:
                standard_cfg = standards[standard]
                exe = _find_exe(variant_dir / "build" / standard, standard_cfg)
                results[standard].append(exe)

    print()
    for standard in standards:
        n_ok = len(results[standard])
        n_fail = total - n_ok
        print(f"{standard}: {n_ok}/{total} compiled ok, {n_fail} failed")

    return results


# ---------------------------------------------------------------------------
# Entrypoint
# ---------------------------------------------------------------------------

if __name__ == "__main__":
    population = DOE_DIR / "population"
    config = Path(sys.argv[1]) if len(sys.argv) > 1 else DEFAULT_COMPILER_CONFIG

    print(f"Compiler config:  {config}")
    print(f"MOS template:     {DEFAULT_MOS_TEMPLATE}")
    print(f"Population dir:   {population}")
    print()

    results = compile_all(population, compiler_config_path=config)
    total_ok = sum(len(v) for v in results.values())
    print(f"\nTotal executables ready: {total_ok}")