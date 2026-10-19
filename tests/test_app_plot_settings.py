"""Per-visualization settings behavior in the browser code."""
import shutil
import subprocess

import pytest

from app import app


def test_plot_settings_behavior() -> None:
    node = shutil.which("node")
    if node is None:
        pytest.skip("Node.js is not installed")
    subprocess.run(
        [node, "tests/app_plot_settings.cjs"],
        cwd=app.PACKAGE_ROOT, check=True,
    )
