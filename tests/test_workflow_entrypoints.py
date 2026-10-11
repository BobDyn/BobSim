"""Consumer entry points must survive source layout changes."""

from __future__ import annotations

import importlib.util
import re
import subprocess

from app import registry, runtime
from common.deploy import deploy
from common.vehicle_io import repo_root


def test_make_entrypoints_resolve_to_importable_modules() -> None:
    """Resolve the modules launched by make, including each replay maneuver."""
    targets = [
        "standard-eval-all", "reduced-eval", "reduced-fidelity-suite",
        "reduced-suspension-correlation", "reduced-kinematics-benchmark",
        "envelope-all", "lap-eval", "lap-validation-visuals",
        "opt-standard", "opt-envelope", "opt-refined", "opt-search",
        "opt-solve", "opt-trade", "visual-capture",
    ]
    for maneuver in ("four_post", "ramp_steer", "steady_state", "transient"):
        result = subprocess.run(
            ["make", "-n", "RUN=", "METRICS=ay_max=10", f"VISUAL_EVAL={maneuver}", *targets],
            cwd=repo_root(), check=True, capture_output=True, text=True,
        )
        modules = set(re.findall(r"\s-m ([\w.]+)", result.stdout))
        assert modules
        for module in modules:
            assert importlib.util.find_spec(module) is not None, module


def test_packaged_workflows_include_modules_and_seed_assets() -> None:
    """Check the desktop bundle against the same actions and assets as the app."""
    root = repo_root()
    modules = set(deploy.discover_hidden_imports())
    for action in registry.build_action_specs(root, "python", "-m").values():
        if "-m" in action.argv:
            module = action.argv[action.argv.index("-m") + 1]
            assert module in modules, module
    for relative in (*deploy.DATA_PATHS, *runtime.APP_SEED_RUNTIME_PATHS):
        assert (root / relative).exists(), relative
