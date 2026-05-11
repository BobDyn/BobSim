"""pipeline_hash.py — Track pipeline state to detect stale artifacts.

Computes a hash of all inputs that affect compiled executables:
  - doe_config.yaml        (parameter ranges, sample count)
  - compiler_config.yaml   (solver, tolerance, intervals)
  - BobLib submodule SHA   (upstream model changes)

Stores the hash in population/.pipeline.hash on each fresh run.
On subsequent runs, compares current hash to stored hash.
If mismatch — raises loud error telling user to clean and rerun.

Per-variant hashes:
  - variant.mo             (generator output, one hash per variant)
Stored in population/variant_XXXX/.variant.hash
"""

from __future__ import annotations

import hashlib
import subprocess
from pathlib import Path

HASH_FILE = ".pipeline.hash"
VARIANT_HASH_FILE = ".variant.hash"


def _hash_file(path: Path) -> str:
    h = hashlib.sha256()
    h.update(path.read_bytes())
    return h.hexdigest()


def _hash_string(s: str) -> str:
    return hashlib.sha256(s.encode()).hexdigest()


def _boblib_sha(boblib_path: Path) -> str:
    """Get the git commit SHA of the BobLib submodule."""
    try:
        result = subprocess.run(
            ["git", "rev-parse", "HEAD"],
            capture_output=True,
            text=True,
            cwd=str(boblib_path.parent),
        )
        if result.returncode == 0:
            return result.stdout.strip()
    except Exception:
        pass
    # Fallback: hash package.mo directly if git unavailable
    pkg = boblib_path if boblib_path.is_file() else boblib_path / "package.mo"
    if pkg.exists():
        return _hash_file(pkg)
    return "unknown"


def compute_pipeline_hash(doe_config: Path, compiler_config: Path, boblib_path: Path) -> str:
    parts = [
        f"doe:{_hash_file(doe_config)}",
        f"compiler:{_hash_file(compiler_config)}",
        f"boblib:{_boblib_sha(boblib_path)}",
    ]
    combined = "|".join(parts)
    return _hash_string(combined)


def write_pipeline_hash(population_dir: Path, doe_config: Path, compiler_config: Path,
                        boblib_path: Path) -> str:
    h = compute_pipeline_hash(doe_config, compiler_config, boblib_path)
    (population_dir / HASH_FILE).write_text(h)
    return h


def check_pipeline_hash(population_dir: Path, doe_config: Path, compiler_config: Path,
                        boblib_path: Path) -> None:
    """Raise RuntimeError if pipeline inputs have changed since last run.

    Does nothing if no hash file exists (first run).
    """
    hash_path = population_dir / HASH_FILE
    if not hash_path.exists():
        return

    stored = hash_path.read_text().strip()
    current = compute_pipeline_hash(doe_config, compiler_config, boblib_path)

    if stored != current:
        raise RuntimeError(
            "\nPipeline inputs have changed since last compilation.\n"
            "Compiled artifacts are stale and cannot be reused.\n"
            "Run 'make clean-population' then rerun the pipeline.\n\n"
            "Changes detected in one or more of:\n"
            "  - configs/doe_config.yaml\n"
            "  - configs/compiler_config.yaml\n"
            "  - BobLib submodule\n"
        )


# ---------------------------------------------------------------------------
# Variant hash
# ---------------------------------------------------------------------------

def write_variant_hash(variant_dir: Path) -> str:
    """Hash variant.mo and write to variant_XXXX/.variant.hash."""
    variant_mo = variant_dir / "variant.mo"
    h = _hash_file(variant_mo)
    (variant_dir / VARIANT_HASH_FILE).write_text(h)
    return h


def variant_is_stale(variant_dir: Path) -> bool:
    """Return True if variant.mo has changed since last compile.

    Returns False (not stale) if no hash file exists yet.
    """
    hash_path = variant_dir / VARIANT_HASH_FILE
    if not hash_path.exists():
        return False

    stored = hash_path.read_text().strip()
    variant_mo = variant_dir / "variant.mo"
    if not variant_mo.exists():
        return False

    current = _hash_file(variant_mo)
    return stored != current
