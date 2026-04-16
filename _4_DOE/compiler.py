"""compiler.py — Generate build.mos per variant and compile via OMC.

Reads standards and paths from configs/compiler_config.yaml.
To add a new standard, add an entry there — no Python changes needed.

For each variant_XXXX/ in population/:
  1. Generate a build.mos that loads BobLib + variant.mo and calls buildModel
  2. Run omc inside variant_XXXX/build/<standard>/
  3. Verify executable exists
  4. Write compile_error_<standard>.log on failure
"""

from __future__ import annotations

import subprocess
import sys
from pathlib import Path

import yaml

# ---------------------------------------------------------------------------
# Config
# ---------------------------------------------------------------------------

DEFAULT_CONFIG = Path(__file__).parent / "configs/compiler_config.yaml"


def load_compiler_config(config_path: Path = DEFAULT_CONFIG) -> dict:
    with open(config_path) as f:
        return yaml.safe_load(f)


# ---------------------------------------------------------------------------
# build.mos template
# ---------------------------------------------------------------------------

_MOS_TEMPLATE = """\
OpenModelica.Scripting.setCommandLineOptions(
  "--simCodeTarget=C --maxSizeLinearTearing=5000"
);

clear();
loadModel(Modelica);
loadFile("{boblib_path}");
loadFile("{variant_mo_path}");

cd("{build_dir}");

buildModel(
  {model},
  startTime={start_time},
  stopTime={stop_time},
  outputFormat="csv",
  numberOfIntervals={intervals},
  tolerance={tolerance},
  method="{solver}",
  cflags="-O3 -march=native -mtune=native"
);

print(getErrorString());
"""


def generate_mos(
        variant_mo: Path,
        build_dir: Path,
        boblib_path: Path,
        standard_cfg: dict,
) -> str:
    """Return a filled-in build.mos string for one variant + standard."""
    return _MOS_TEMPLATE.format(
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

    mos_content = generate_mos(variant_mo, build_dir, boblib_path, standard_cfg)
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

    # OMC exits 0 even on soft failures — check executable exists
    exe = _find_exe(build_dir, standard_cfg)
    if exe is None:
        error_msg = (result.stdout + "\n" + result.stderr).strip()
        _write_error(variant_dir, standard, error_msg)
        return False

    return True


def _find_exe(build_dir: Path, standard_cfg: dict) -> Path | None:
    """Return exe path if it exists (handles Linux and .exe)."""
    model_name = standard_cfg["model"].split(".")[-1]
    for candidate in [build_dir / model_name, build_dir / f"{model_name}.exe"]:
        if candidate.exists():
            return candidate
    return None


def _write_error(variant_dir: Path, standard: str, message: str) -> None:
    log = variant_dir / f"compile_error_{standard}.log"
    log.write_text(message)


# ---------------------------------------------------------------------------
# Compile all variants
# ---------------------------------------------------------------------------

def compile_all(
        population_dir: Path,
        compiler_config_path: Path = DEFAULT_CONFIG,
) -> dict[str, list[Path]]:
    """Compile all variants in population_dir for all standards in config.

    Returns dict mapping standard -> list of successful exe paths.
    Failed variants are logged and skipped.
    """
    cfg = load_compiler_config(compiler_config_path)
    standards: dict[str, dict] = cfg["standards"]

    # Resolve boblib_path relative to the config file
    config_dir = compiler_config_path.resolve().parent
    boblib_path = (config_dir / cfg["boblib_path"]).resolve()

    if not boblib_path.exists():
        raise FileNotFoundError(
            f"BobLib not found at {boblib_path}. Did you init submodules?\n"
            f"Run: git submodule update --init --recursive"
        )

    variant_dirs = sorted(population_dir.glob("variant_????"))
    if not variant_dirs:
        raise RuntimeError(f"No variant dirs found in {population_dir}")

    total = len(variant_dirs)
    results: dict[str, list[Path]] = {s: [] for s in standards}

    for i, variant_dir in enumerate(variant_dirs, 1):
        for standard, standard_cfg in standards.items():
            success = compile_variant(
                variant_dir, standard, standard_cfg, boblib_path
            )
            status = "ok" if success else "FAILED"
            print(f"[{i:>4}/{total}] {variant_dir.name} / {standard}: {status}")

            if success:
                exe = _find_exe(variant_dir / "build" / standard, standard_cfg)
                results[standard].append(exe)

    for standard in standards:
        n_ok = len(results[standard])
        n_fail = total - n_ok
        print(f"\n{standard}: {n_ok}/{total} compiled ok, {n_fail} failed")

    return results


# ---------------------------------------------------------------------------
# Entrypoint
# ---------------------------------------------------------------------------

if __name__ == "__main__":
    population = Path(__file__).parent / "population"
    config = Path(sys.argv[1]) if len(sys.argv) > 1 else DEFAULT_CONFIG

    print(f"Compiler config: {config}")
    print(f"Population dir:  {population}")

    results = compile_all(population, compiler_config_path=config)
    total_ok = sum(len(v) for v in results.values())
    print(f"\nTotal executables ready: {total_ok}")