"""Validation envelopes must be regenerated when the governing physics changes."""
from __future__ import annotations

import json
from pathlib import Path
from types import SimpleNamespace

import pytest

from simulations.lap import validation_visuals as validation


def test_validation_rebuilds_old_envelope_after_physics_change(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
    config_path = tmp_path / "config.yml"
    vehicle_path = tmp_path / "vehicle.yml"
    solver_path = tmp_path / "simulations/envelope/ggv/ggv_generation.py"
    sources = [config_path, vehicle_path, solver_path,
               tmp_path / "simulations/envelope/ymd/ymd_generation.py", tmp_path / "validation.py"]
    for source in sources:
        source.parent.mkdir(parents=True, exist_ok=True)
        source.write_text("old input\n")
    monkeypatch.setattr(validation, "__file__", str(tmp_path / "validation.py"))
    old_fingerprint = validation._validation_fingerprint(tmp_path, config_path, vehicle_path)
    solver_path.write_text("new path-frame acceleration equations\n")
    assert validation._validation_fingerprint(tmp_path, config_path, vehicle_path) != old_fingerprint
    output = tmp_path / "results/3dof"
    output.mkdir(parents=True)
    old_csv = output / "ggv.csv"
    old_csv.write_text("old zero-yaw envelope\n")
    (output / "summary.json").write_text(json.dumps({"validation_fingerprint": old_fingerprint}))
    config = {"output_directory": "results", "vehicle": "vehicle.yml", "model_dofs": [3],
              "track": {"boundary_csv": "track.csv"}}
    monkeypatch.setattr(validation, "repo_root", lambda: tmp_path)
    monkeypatch.setattr(validation, "load_yaml", lambda _: config)
    monkeypatch.setattr(validation, "load_vehicle_yaml", lambda _: {})
    monkeypatch.setattr(validation, "project_vehicle_yaml", lambda _: SimpleNamespace(ggv=None))
    monkeypatch.setattr(validation.Vehicle, "from_yaml", lambda _: SimpleNamespace(model=lambda _: None))
    monkeypatch.setattr(validation.TrackCorridor, "from_csv", lambda _: None)
    monkeypatch.setattr(validation, "_write_reference_track_figures", lambda *_: None)
    monkeypatch.setattr(validation, "_load_ggv_envelopes", lambda _: pytest.fail("Old envelope was reused"))

    def regenerate(*args, **kwargs):
        raise RuntimeError("fresh envelope solve")

    monkeypatch.setattr(validation, "generate_ggv", regenerate)
    with pytest.raises(RuntimeError, match="fresh envelope solve"):
        validation.generate_validation_visuals(config_path)
    assert old_csv.read_text() == "old zero-yaw envelope\n"
