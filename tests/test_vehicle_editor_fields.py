from pathlib import Path
import shutil
import subprocess

import pytest

from app.contracts import FieldSpec
from app.data_services import _vehicle_field_payload


@pytest.mark.parametrize(
    ("path", "value", "unit", "label", "display_unit", "scale"),
    [
        (("front", "steering", "rack_travel_per_rev_m"), 0.04, None, "Rack travel per revolution", "mm/rev", 1000),
        (("aero", "aero_ref_m"), [1, 0, 0], None, "Wrench reference point", "mm", 1000),
        (("powertrain", "pVCU", "P_max_mot"), 80000, None, "Drive power limit", "kW", 0.001),
        (("powertrain", "pBattery", "SOC_start"), 0.95, None, "Initial charge", "%", 100),
        (("brake", "front_bias"), 0.6, None, "Front brake bias", "%", 100),
        (("front", "wheel", "wheel_inertia_kg_m2"), 0.04, None, "Wheel rotational inertia", "kg·m²", 1),
    ],
)
def test_vehicle_display_metadata_keeps_stored_values(path, value, unit, label, display_unit, scale):
    data = {}
    target = data
    for part in path[:-1]:
        target = target.setdefault(part, {})
    target[path[-1]] = value
    result = _vehicle_field_payload(FieldSpec(path=path, label="Old label", unit=unit), data)
    assert result["value"] == value
    assert result["label"] == label
    assert result["display_unit"] == display_unit
    assert result["display_scale"] == scale


def test_numeric_display_roundtrip_preserves_precision_and_converts_edits():
    node = shutil.which("node")
    if not node:
        pytest.skip("Node is not installed")
    source = (Path(__file__).parents[1] / "app/static/app.js").read_text()
    helpers = source[source.index("function numericDisplayValue("):source.index("function fieldControl(")]
    collector = source[source.index("function collectScalarValue("):source.index("async function saveVehicleEdits(")]
    script = helpers + collector + r'''
const assert = require('node:assert/strict');
for (const [original, scale, edited, expected] of [
  [0.1016123456789123, 1000, '125.5', 0.1255],
  [0.9582345678901234, 100, '80', 0.8],
  [123456.789012345, 0.001, '100', 100000],
  [0.01234567890123456, 1, '0.02', 0.02],
]) {
  const input = {dataset: {displayScale: String(scale)}, setCustomValidity() {}, checkValidity() {return true;}};
  setNumericInputValue(input, original);
  input.value = String(input.value);
  assert.equal(collectScalarValue(input, 'number', false), original);
  input.value = edited;
  assert.equal(collectScalarValue(input, 'number', false), expected);
  input.value = '';
  assert.throws(() => collectScalarValue(input, 'number', false));
}
'''
    subprocess.run([node, "-e", script], check=True, capture_output=True, text=True)


def test_physical_quantity_accepts_fractional_display_values():
    field = FieldSpec(path=("vertical_stiffness_n_per_m",), label="Stiffness", kind="integer")
    result = _vehicle_field_payload(field, {"vertical_stiffness_n_per_m": 98947})
    assert result["kind"] == "number"
    assert result["display_scale"] == 0.001
    assert result["value"] == 98947
