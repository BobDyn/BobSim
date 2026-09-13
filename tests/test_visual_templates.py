"""Visual template and demo-scene checks that need no rendering stack.

These import only numpy and yaml, so they run everywhere - including CI and the
Docker image, where BobVis's PyQt6/VTK dependencies are deliberately absent.
The tests that exercise ``SimData`` and the exporter live in
``test_visual_scene.py`` and skip without PyVista.

What is worth protecting here is the layer where the viewer used to go wrong:
whether a visual template's names actually resolve against the data it is
paired with.
"""

from __future__ import annotations

from pathlib import Path
from typing import Any

import numpy as np
import pytest
import yaml

from _1_VisualSim import demo

TEMPLATE_DIR = Path(__file__).resolve().parents[1] / "_1_VisualSim" / "visual_templates"


def _referenced_signals(cfg: dict[str, Any]) -> set[str]:
    """Every signal name a visual config expects, read straight from the YAML.

    Deliberately independent of ``SimData.required_signals`` so the two have to
    agree; this is the copy that can run without PyVista installed.
    """
    geometry = cfg.get("geometry") or {}
    names: set[str] = set()

    for cols in (geometry.get("points") or {}).values():
        names.update(str(c) for c in cols)
    for tire in (geometry.get("tires") or {}).values():
        names.update(str(c) for c in tire.get("x", []))
        names.update(str(c) for c in tire.get("y", []))
    for group in (geometry.get("vectors") or {}).values():
        for vector in group.values():
            names.update(
                str(c) for c in vector.get("direction", []) if isinstance(c, str)
            )
    for plot in cfg.get("plots") or []:
        for key in ("x", "y"):
            if isinstance(plot.get(key), str):
                names.add(str(plot[key]))
    for load in (((cfg.get("ground") or {}).get("loads") or {}).get("corners") or {}).values():
        names.add(str(load["signal"]))
    for tire in ((cfg.get("tire_forces") or {}).get("corners") or {}).values():
        names.update(str(tire[key]) for key in ("fx", "fy", "fz", "gamma") if tire.get(key))
    return names


# ---------------------------------------------------------------------------
# Bundled templates and the demo generator - no PyVista required
# ---------------------------------------------------------------------------

@pytest.mark.parametrize("template", sorted(TEMPLATE_DIR.glob("*.yml")), ids=lambda p: p.stem)
def test_template_is_structurally_valid(template: Path) -> None:
    """Every bundled template parses and its links resolve to declared points."""
    cfg = yaml.safe_load(template.read_text(encoding="utf-8"))
    assert isinstance(cfg, dict), f"{template.name} is not a YAML mapping"

    points = (cfg.get("geometry") or {}).get("points") or {}
    assert points, f"{template.name} declares no geometry.points"
    for name, cols in points.items():
        assert len(cols) == 3, f"{template.name}: point {name} needs exactly 3 columns"

    for group, pairs in ((cfg.get("geometry") or {}).get("links") or {}).items():
        for pair in pairs:
            assert len(pair) == 2, f"{template.name}: link in {group} is not a pair"
            for endpoint in pair:
                assert endpoint in points, (
                    f"{template.name}: link group {group} references "
                    f"undeclared point {endpoint}"
                )

    for tire_name, tire in ((cfg.get("geometry") or {}).get("tires") or {}).items():
        assert tire["center"] in points, (
            f"{template.name}: tire {tire_name} centres on undeclared point"
        )

    for group, vectors in ((cfg.get("geometry") or {}).get("vectors") or {}).items():
        for vector_name, vector in vectors.items():
            assert vector["origin"] in points, (
                f"{template.name}: vector {group}/{vector_name} "
                "originates at an undeclared point"
            )


def test_demo_scene_signals_cover_its_config() -> None:
    """The generated demo config must not reference a signal it did not write."""
    signals, cfg = demo.build(duration=0.5)

    missing = _referenced_signals(cfg) - set(signals)
    assert not missing, f"demo config references unwritten signals: {sorted(missing)}"

    length = len(signals["time"])
    for name, array in signals.items():
        assert len(array) == length, f"demo signal {name} has a mismatched length"
        assert np.all(np.isfinite(array)), f"demo signal {name} is not finite"

    assert np.all(np.diff(signals["time"]) > 0), "demo time must increase strictly"


def test_demo_write_round_trips(tmp_path: Path) -> None:
    config_path, data_path = demo.write(tmp_path, duration=0.5)
    assert config_path.is_file() and data_path.is_file()

    cfg = yaml.safe_load(config_path.read_text(encoding="utf-8"))
    with np.load(data_path) as raw:
        assert not _referenced_signals(cfg) - set(raw.files)
