"""Shipped study configs, and the per-user copy the app edits.

A study config under ``_3_StandardSim/`` plays one role: it is the *seed*,
checked in, reviewed, and the thing a clean clone runs. What the app edits is a
copy under ``_5_App/user_data/config/active/``, which is runtime state and
gitignored like everything else there.

Before this split the two roles shared one file. The app wrote the tracked
config in place, so normal use dirtied the working tree, and a pristine copy had
to be kept in ``_5_App/sim_configs/_defaults/`` for "Default" to restore --
copies that silently drifted from their sources.

``resolve`` keeps the CLI behaving exactly as it did: with no active copy it
returns the seed, and once the app has written one, ``make standard-eval-*``
picks up the same config the app is running. Only configs whose own values are
repo-relative can move like this; ``_2_EnvelopeSim`` and ``_4_OptSim`` configs
resolve ``../`` paths against their own directory and stay where they are.
"""

from __future__ import annotations

from pathlib import Path
import shutil

from _0_Utils.vehicle_io import repo_root

ACTIVE_CONFIG_ROOT = Path("_5_App/user_data/config/active")


def active_config_path(seed_path: str | Path, *, root: str | Path | None = None) -> Path:
    """Where the app's editable copy of ``seed_path`` lives. May not exist yet."""
    base = Path(root) if root is not None else repo_root()
    return base / ACTIVE_CONFIG_ROOT / Path(seed_path).name


def resolve(seed_path: str | Path, *, root: str | Path | None = None) -> Path:
    """The config to actually read: the active copy when one exists, else the seed."""
    base = Path(root) if root is not None else repo_root()
    seed = Path(seed_path)
    if not seed.is_absolute():
        seed = base / seed
    active = active_config_path(seed_path, root=base)
    return active if active.is_file() else seed


def ensure_active(seed_path: str | Path, *, root: str | Path | None = None) -> Path:
    """Return the active copy, seeding it from ``seed_path`` the first time."""
    base = Path(root) if root is not None else repo_root()
    seed = Path(seed_path)
    if not seed.is_absolute():
        seed = base / seed
    active = active_config_path(seed_path, root=base)
    if not active.is_file():
        if not seed.is_file():
            raise FileNotFoundError(seed)
        active.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(seed, active)
    return active
