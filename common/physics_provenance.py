"""Code identity for generated GGV envelopes."""

from __future__ import annotations

import hashlib
from pathlib import Path
import re
import sys

GGV_PHYSICS_DIGEST_FILE = "ggv-physics.sha256"


def ggv_physics_sha256(source_root: Path) -> str:
    """## GGV Physics Fingerprint

    Parameters
    ----------
    source_root : Path
        Checkout containing the physics sources when running from source.

    Returns
    -------
    str
        Source digest, or the build-time digest shipped with a frozen app.
    """
    if getattr(sys, "frozen", False):
        package_root = Path(getattr(sys, "_MEIPASS", Path(__file__).resolve().parents[1]))
        digest = (package_root / GGV_PHYSICS_DIGEST_FILE).read_text(encoding="utf-8").strip()
        if re.fullmatch(r"[0-9a-f]{64}", digest) is None:
            raise ValueError("Invalid bundled GGV physics fingerprint. Rebuild or reinstall BobSim.")
        return digest

    inputs = [
        source_root / "simulations/lap/lap_time_eval_sim.py",
        source_root / "simulations/envelope/ggv/ggv_generation.py",
        source_root / "simulations/envelope/ggv/parallel.py",
        source_root / "simulations/envelope/vehicle_yaml.py",
        source_root / "common/vehicle_io.py",
        source_root / "common/physics_provenance.py",
    ]
    for relative in ("engines/dynpy", "engines/kinpy"):
        sources = sorted((source_root / relative).rglob("*.py"))
        if not sources:
            raise FileNotFoundError(f"Missing physics sources: {source_root / relative}")
        inputs.extend(sources)
    digest_builder = hashlib.sha256()
    for source in inputs:
        digest_builder.update(source.relative_to(source_root).as_posix().encode("utf-8"))
        digest_builder.update(b"\0")
        digest_builder.update(source.read_bytes())
        digest_builder.update(b"\0")
    return digest_builder.hexdigest()
