"""Build a BobLib simulator once per source state, not once per checkout.

The makefile used to rebuild VehicleSim and FourPostSim from file mtimes over a
handful of BobLib files. That missed most BobLib changes (a pin bump that only
touched a suspension model kept the stale executable) and rebuilt after any
branch switch that bumped mtimes without changing content.

This keys each build on what actually goes into it: every file under the BobLib
package, the build script, the C flags, the omc version and, for host-tuned
flags, the CPU. A key that was built before is restored from the cache in about
a second instead of recompiling for minutes.

``BOBSIM_CFLAGS_PROFILE=portable`` builds without ``-march=native``, so the key
no longer depends on the CPU and one build can be shared between machines and
CI. ``native`` (the default) keeps today's flags.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import os
import platform
import shutil
import subprocess
import sys
import tempfile
from collections.abc import Callable, Iterable, Sequence
from pathlib import Path

# Bump when the key's inputs or the cached file set change.
SCHEMA = 1
DEFAULT_CACHE_DIR = Path(".cache/bobsim/models")
DEFAULT_KEEP = 5
SKIPPED_DIRS = {".git", "__pycache__"}
PROFILES = ("native", "portable")


def cflags(profile: str, machine: str | None = None) -> str:
    """C flags for ``profile`` on ``machine`` (defaults to this host)."""
    if profile not in PROFILES:
        raise ValueError(f"Unknown C flags profile {profile!r}; use one of {', '.join(PROFILES)}.")
    if profile == "portable":
        return "-O3"
    # clang on AArch64 (Apple Silicon under Docker) rejects -march=native.
    machine = (machine or platform.machine()).lower()
    if machine in {"aarch64", "arm64"}:
        return "-O3 -mcpu=native -mtune=native"
    return "-O3 -march=native -mtune=native"


def cpu_fingerprint() -> dict[str, str]:
    fingerprint = {"machine": platform.machine()}
    cpuinfo = Path("/proc/cpuinfo")
    if cpuinfo.is_file():
        for line in cpuinfo.read_text(encoding="utf-8", errors="ignore").splitlines():
            if line.lower().startswith("model name"):
                fingerprint["cpu_model"] = line.partition(":")[2].strip()
                break
    return fingerprint


def _source_files(root: Path, sources: Iterable[str]) -> list[Path]:
    files: list[Path] = []
    for rel in sorted(set(sources)):
        path = root / rel
        if path.is_file():
            files.append(path)
        elif path.is_dir():
            files.extend(
                item
                for item in sorted(path.rglob("*"))
                if item.is_file() and not SKIPPED_DIRS & set(item.relative_to(root).parts)
            )
        else:
            raise FileNotFoundError(f"Build source {rel} does not exist (is the BobLib submodule initialized?)")
    return files


def source_digest(root: Path, sources: Iterable[str]) -> str:
    """SHA-256 over every source file's repo-relative path and bytes."""
    digest = hashlib.sha256()
    for path in _source_files(root, sources):
        digest.update(path.relative_to(root).as_posix().encode("utf-8") + b"\0")
        digest.update(path.read_bytes())
        digest.update(b"\0")
    return digest.hexdigest()


def build_key(
    root: Path,
    sources: Iterable[str],
    flags: str,
    omc_version: str,
    cpu: dict[str, str] | None = None,
) -> str:
    inputs = {
        "schema": SCHEMA,
        "sources": source_digest(root, sources),
        "cflags": flags,
        "omc": omc_version.strip(),
        # Only host-tuned code is tied to the CPU it was built on.
        "cpu": (cpu or cpu_fingerprint()) if "native" in flags else {"machine": platform.machine()},
    }
    return hashlib.sha256(json.dumps(inputs, sort_keys=True).encode("utf-8")).hexdigest()


def runtime_files(exe: Path) -> list[Path]:
    """The files an OpenModelica executable reads at run time."""
    if not exe.is_file():
        return []
    prefix = exe.name
    keep = [exe]
    for item in sorted(exe.parent.iterdir()):
        if item == exe or not item.is_file() or not item.name.startswith(prefix):
            continue
        if item.suffix in {".xml", ".json", ".bin", ".mat", ".csv"}:
            # Result files from a previous run are outputs, not build products.
            if item.name.endswith(("_res.csv", "_res.mat")):
                continue
            keep.append(item)
    return keep


def stamp_path(exe: Path) -> Path:
    return exe.with_name(exe.name + ".bobsim-key")


def restore(entry: Path, exe: Path) -> bool:
    if not (entry / exe.name).is_file():
        return False
    exe.parent.mkdir(parents=True, exist_ok=True)
    for item in entry.iterdir():
        if item.name == "manifest.json":
            continue
        shutil.copy2(item, exe.parent / item.name)
    return True


def store(entry: Path, exe: Path, key: str) -> None:
    entry.parent.mkdir(parents=True, exist_ok=True)
    staging = Path(tempfile.mkdtemp(prefix=f".{key[:12]}-", dir=entry.parent))
    try:
        files = runtime_files(exe)
        for item in files:
            shutil.copy2(item, staging / item.name)
        (staging / "manifest.json").write_text(
            json.dumps({"key": key, "files": [item.name for item in files]}, indent=2) + "\n",
            encoding="utf-8",
        )
        try:
            staging.rename(entry)
        except OSError:
            # Another build stored the same key first; theirs is as good as ours.
            if not (entry / exe.name).is_file():
                raise
    finally:
        if staging.exists():
            shutil.rmtree(staging, ignore_errors=True)


def prune(target_dir: Path, keep: int) -> list[Path]:
    """Drop all but the ``keep`` most recently used entries for one target."""
    entries = sorted(
        (item for item in target_dir.iterdir() if item.is_dir() and not item.name.startswith(".")),
        key=lambda item: item.stat().st_mtime,
        reverse=True,
    )
    removed = entries[keep:]
    for item in removed:
        shutil.rmtree(item, ignore_errors=True)
    return removed


def omc_version() -> str:
    return subprocess.run(["omc", "--version"], check=True, capture_output=True, text=True).stdout


def compile_with_omc(mos: Path, exe: Path, flags: str) -> None:
    for item in (exe, exe.with_name(exe.name + "_init.xml")):
        item.unlink(missing_ok=True)
    env = {**os.environ, "BOBSIM_NATIVE_CFLAGS": flags}
    subprocess.run(["omc", str(mos)], check=True, env=env)
    missing = [p.name for p in (exe, exe.with_name(exe.name + "_init.xml")) if not p.is_file()]
    if missing:
        raise RuntimeError(f"omc {mos} finished without producing {', '.join(missing)}")


def build(
    root: Path,
    mos: str,
    exe: str,
    sources: Sequence[str],
    cache_dir: Path,
    profile: str,
    keep: int = DEFAULT_KEEP,
    compile_fn: Callable[[Path, Path, str], None] = compile_with_omc,
    version_fn: Callable[[], str] = omc_version,
) -> str:
    """Make ``exe`` current for ``sources``. Returns ``fresh``, ``restored`` or ``built``."""
    flags = cflags(profile)
    key = build_key(root, [*sources, mos], flags, version_fn())
    exe_path = root / exe
    stamp = stamp_path(exe_path)
    if exe_path.is_file() and stamp.is_file() and stamp.read_text(encoding="utf-8").strip() == key:
        return "fresh"

    target_dir = (cache_dir if cache_dir.is_absolute() else root / cache_dir) / exe_path.name
    entry = target_dir / key
    if restore(entry, exe_path):
        outcome = "restored"
        os.utime(entry)
    else:
        compile_fn(root / mos, exe_path, flags)
        store(entry, exe_path, key)
        outcome = "built"
    stamp.write_text(key + "\n", encoding="utf-8")
    prune(target_dir, keep)
    return outcome


def main(argv: Sequence[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    sub = parser.add_subparsers(dest="command", required=True)
    for name in ("build", "key"):
        cmd = sub.add_parser(name)
        cmd.add_argument("--mos", required=True, help="Build script, relative to the repo root.")
        cmd.add_argument("--exe", required=True, help="Executable the script produces.")
        cmd.add_argument(
            "--source",
            action="append",
            default=[],
            help="File or directory the build reads (repeatable). Defaults to the BobLib package.",
        )
    args = parser.parse_args(argv)

    root = Path.cwd()
    sources = args.source or ["engines/boblib/BobLib"]
    cache_dir = Path(os.environ.get("BOBSIM_MODEL_CACHE") or DEFAULT_CACHE_DIR)
    profile = os.environ.get("BOBSIM_CFLAGS_PROFILE") or "native"
    if args.command == "key":
        print(build_key(root, [*sources, args.mos], cflags(profile), omc_version()))
        return 0
    outcome = build(root, args.mos, args.exe, sources, cache_dir, profile)
    print(f"{args.exe}: {outcome} ({profile} C flags)", file=sys.stderr)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
