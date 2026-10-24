"""Analysis and simulation picker behavior."""
import shutil
import subprocess

import pytest

from app import app


def test_analysis_picker_behavior() -> None:
    node = shutil.which("node")
    if node is None:
        pytest.skip("Node.js is not installed")
    subprocess.run([node, "tests/app_analysis_picker.cjs"], cwd=app.PACKAGE_ROOT, check=True)
