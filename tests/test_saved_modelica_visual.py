"""Automatic animation must use the saved Modelica run and vehicle snapshot."""
import json
import shutil
import zipfile

import numpy as np
import pytest
import yaml

from tests.test_visual_results import _write_result_csv
from visualization.saved_modelica import capture_saved
from common.vehicle_io import repo_root


def test_saved_modelica_cases_keep_time_geometry_and_run_identity(tmp_path):
    run = tmp_path / "saved"
    run.mkdir()
    shutil.copy2(repo_root() / "vehicle.yml", run / "vehicle.yml")
    csv = tmp_path / "case.csv"
    _write_result_csv(csv, prefix="chassis.detailedChassis.", speed=3.)
    with zipfile.ZipFile(run / "signals.zip", "w") as archive:
        archive.write(csv, "runs/one/signals.csv")
    saved = {"id": "original", "label": "Maneuver", "model": {"engine": "BobLib"},
             "workflow": {"id": "mbd-maneuver"}, "simulation": {"id": "sim"}, "vehicle_key": "car",
             "vehicle_snapshot": "saved/vehicle.yml", "analysis": {"archive_path": "saved/signals.zip",
             "runs": [{"label": "Case one", "signals_file": "runs/one/signals.csv"}]}}
    (run / "manifest.json").write_text(json.dumps(saved))
    scenes = capture_saved(run, root=tmp_path)
    assert len(scenes) == 1
    config = yaml.safe_load(scenes[0].read_text())
    assert config["source"]["result_id"] == "original"
    assert config["source"]["simulation_id"] == "sim"
    with np.load(scenes[0].with_suffix(".npz")) as data:
        xyz = config["geometry"]["points"]["fl_Lower_o"]
        assert data[xyz[0]][-1] - data[xyz[0]][0] == pytest.approx(3.)
    saved["model"]["engine"] = "DynPy"
    (run / "manifest.json").write_text(json.dumps(saved))
    with pytest.raises(ValueError, match="requires a Modelica"):
        capture_saved(run, root=tmp_path)
