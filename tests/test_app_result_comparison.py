"""Archived result comparison behavior in the browser code."""
import shutil
import subprocess

import pytest

from app import app


def test_result_comparison_behavior() -> None:
    node = shutil.which("node")
    if node is None:
        pytest.skip("Node.js is not installed")
    subprocess.run([node, "tests/app_result_comparison.cjs"], cwd=app.PACKAGE_ROOT, check=True)
