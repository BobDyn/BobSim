from __future__ import annotations

from copy import deepcopy
import os
from unittest.mock import Mock

import pytest

from app import tire_eval


@pytest.fixture(autouse=True)
def clear_curve_cache():
    tire_eval._cached_mf52_curves.cache_clear()
    yield
    tire_eval._cached_mf52_curves.cache_clear()


def test_curve_cache_tracks_tire_contents_load_and_camber(tmp_path, monkeypatch):
    path = tmp_path / "test.tir"
    path.write_text("FNOMIN = 600\nPDX1 = 1.1\n")
    vehicle = {
        "paths": {"tire_templates": "."},
        "sprung_mass": {"mass_kg": 100, "cg_m": [-.4, 0, 0]},
        "front": {"tire": {"template": "test"}, "suspension": {"wheel_center_m": [0, 0, .2]}},
        "rear": {"tire": {"template": "test"}, "suspension": {"wheel_center_m": [-1, 0, .2]}},
    }
    evaluate = Mock(side_effect=lambda tire, load, camber: {
        "coefficient": tire["PDX1"], "load": load, "camber": camber, "points": [1, 2],
    })
    monkeypatch.setattr(tire_eval, "_mf52_curves", evaluate)
    initial = tire_eval.tire_eval_payload(tmp_path, vehicle)
    assert evaluate.call_count == 2
    expected = deepcopy(initial)
    initial["sides"][0]["curves"]["points"][0] = 99
    assert tire_eval.tire_eval_payload(tmp_path, vehicle) == expected
    assert evaluate.call_count == 2

    # Preserve file size and timestamp to ensure the key uses coefficient contents.
    stat = path.stat()
    path.write_text("FNOMIN = 600\nPDX1 = 1.2\n")
    os.utime(path, ns=(stat.st_atime_ns, stat.st_mtime_ns))
    changed = tire_eval.tire_eval_payload(tmp_path, vehicle)
    assert evaluate.call_count == 4
    assert changed["sides"][0]["curves"]["coefficient"] == 1.2

    vehicle["front"]["wheel"] = {"camber_deg": 2}
    changed = tire_eval.tire_eval_payload(tmp_path, vehicle)
    assert evaluate.call_count == 5
    assert changed["sides"][0]["curves"]["camber"] != expected["sides"][0]["curves"]["camber"]

    vehicle["sprung_mass"]["mass_kg"] = 110
    changed = tire_eval.tire_eval_payload(tmp_path, vehicle)
    assert evaluate.call_count == 7
    assert changed["sides"][0]["curves"]["load"] != expected["sides"][0]["curves"]["load"]
    assert tire_eval._cached_mf52_curves.cache_info().currsize == 2
