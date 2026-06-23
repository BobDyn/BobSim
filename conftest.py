from __future__ import annotations

import os
from pathlib import Path


ROOT = Path(__file__).resolve().parent
BOBLIB_PACKAGE_ROOT = ROOT / "_0_Utils/external/BobLib/BobLib"

if (BOBLIB_PACKAGE_ROOT / "package.mo").is_file():
    os.environ.setdefault("BOBLIB_PACKAGE_ROOT", str(BOBLIB_PACKAGE_ROOT))
