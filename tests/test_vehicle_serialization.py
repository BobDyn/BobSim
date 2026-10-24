from pathlib import Path

import yaml

from common.vehicle_io import dump_vehicle, load_yaml, vehicle_yaml_path
from app import data_services


def test_vehicle_round_trip_keeps_vectors_and_table_rows_compact(tmp_path: Path) -> None:
    data = load_yaml(vehicle_yaml_path())
    output = tmp_path / "vehicle.yml"
    data_services._write_yaml_config(output, data)
    text = output.read_text()
    assert yaml.safe_load(text) == data
    assert dump_vehicle(yaml.safe_load(text)) == text
    assert "cg_m: [" in text
    assert "inertia_kg_m2:\n    - [" in text
    assert "\n\nfront:\n" in text
    assert len(text.splitlines()) < 320
