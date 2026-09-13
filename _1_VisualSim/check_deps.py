"""Exit non-zero with install instructions if the BobVis dependencies are missing.

Lives in Python rather than the makefile because make runs recipes through
cmd.exe on Windows, which cannot parse the POSIX `cmd 2>/dev/null || { ... }`
guard this replaces.
"""

from __future__ import annotations

import importlib.util
import sys

REQUIRED = ("pyvista", "PyQt6")


def main() -> int:
    if all(importlib.util.find_spec(name) is not None for name in REQUIRED):
        return 0
    print(
        "\n".join(
            [
                "error: the BobVis dependencies are not installed.",
                "",
                "  make visual-deps",
                "",
                "Prebuilt wheels for Windows, macOS and Linux; nothing compiles.",
                "On a bare Linux box you may also need system GL:",
                "  apt install libgl1 libglx-mesa0 libxkbcommon-x11-0",
            ]
        ),
        file=sys.stderr,
    )
    return 1


if __name__ == "__main__":
    sys.exit(main())
