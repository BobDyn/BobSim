"""Checks for the component editors without a browser runtime."""
from __future__ import annotations

import json
from pathlib import Path
import shutil
import subprocess

import pytest
import yaml

from app import app


def test_aero_and_powertrain_editors_preserve_fields() -> None:
    node = shutil.which("node")
    if node is None:
        pytest.skip("Node is required for editor checks")
    source = (Path(__file__).parents[1] / "app/static/app.js").read_text()
    names = (
        "aeroSectionHtml", "aeroTableControl", "aeroSurfaceRowsFromTable", "aeroCellControl",
        "powertrainSubsystemFieldsHtml", "powertrainSubsystems", "powertrainFieldSubsystem",
        "arrayScalarControl", "arrayCellInputHtml", "numericDisplayAttrs", "numericDisplayValue",
        "formatNumber", "escapeHtml", "infoIcon", "infoHint",
    )
    helpers = []
    for name in names:
        start = source.index(f"function {name}(")
        end = source.find("\nfunction ", start + 1)
        helpers.append(source[start:end])
    for name in ("AERO_MAPS", "POWERTRAIN_SUBSYSTEMS"):
        start = source.index(f"const {name} = [")
        helpers.append(source[start:source.index("\n];", start) + 3])
    script = "\n".join(helpers) + r'''
const assert = require('node:assert/strict');
const payload = JSON.parse(require('node:fs').readFileSync(0, 'utf8'));
const state = {vehiclePayload: payload};
function fieldPathString(field) { return field.path.join('.'); }
function fieldControl(field) { return `<field key='${field.key}'></field>`; }
const aeroFields = payload.fields.filter(field => field.path[0] === 'aero');
const html = aeroSectionHtml({fields: aeroFields});
assert(html.includes('<details class="component-details" hidden><summary>Legacy tire fallback</summary>'));
assert(html.includes('tire_template'));
const originalTemplate = payload.data.front.tire.template;
delete payload.data.front.tire.template;
assert(aeroSectionHtml({fields: aeroFields}).includes(
  '<details class="component-details"><summary>Legacy tire fallback'));
payload.data.front.tire.template = originalTemplate;
const table = aeroTableControl(aeroFields);
const paths = [...table.matchAll(/data-config-path="([^"]+)"/g)].map(match =>
  JSON.parse(match[1].replaceAll('&quot;', '"')));
assert.equal(new Set(paths.map(path => JSON.stringify(path))).size, paths.length);
for (const map of AERO_MAPS) {
  const field = aeroFields.find(field => field.path[1] === map.key);
  assert.equal(paths.filter(path => path[1] === map.key).length, field.value.flat().length);
  for (const [row, values] of field.value.entries()) {
    for (const [col, value] of values.entries()) {
      assert(paths.some(path => path[1] === map.key && path[2] === row && path[3] === col));
      assert(table.includes(`data-original-value="${value}"`));
    }
  }
}
for (const axle of ['front', 'rear']) {
  const grid = payload.data.aero[`${axle}_ride_height_grid_m`];
  assert.equal(paths.filter(path => path[1] === `${axle}_ride_height_grid_m`).length, grid.length);
  assert(table.includes(`value="${numericDisplayValue(grid[0], 1000)}"`));
}
assert.equal((html.match(/<table /g) || []).length, 1);
assert(!html.includes('<summary>Ride-height grid</summary>'));
const rows = aeroSurfaceRowsFromTable([[1, 2], [3, 4]], [.04, .06], [.05, .07], 'force');
const coordinates = rows.map(row => row.points.map(point =>
  [point.front_ride_height_mm, point.rear_ride_height_mm, point.force]));
assert.deepEqual(coordinates,
  [[[40, 50, 1], [60, 50, 2]], [[40, 70, 3], [60, 70, 4]]]);
const fields = payload.fields.filter(field => ['powertrain', 'brake'].includes(field.path[0]));
const components = POWERTRAIN_SUBSYSTEMS.map(subsystem => subsystem.component);
const sections = powertrainSubsystems({components}, fields);
const rendered = sections.map(powertrainSubsystemFieldsHtml).join('');
for (const field of fields.filter(field => field.path[1] !== 'implementation')) {
  assert.equal(rendered.split(`<field key='${field.key}'>`).length - 1, 1, field.key);
}
const motor = powertrainSubsystemFieldsHtml(sections.find(section => section.id === 'pMotor'));
const torque = motor.match(/<details[^>]* open><summary>Torque and power<\/summary>(.*?)<\/details>/s);
assert(torque && torque[1].includes('T_peak'));
const inertia = motor.match(/<details[^>]*><summary>Inertia<\/summary>(.*?)<\/details>/s);
assert(inertia && inertia[1].includes('rotorJ'));
const driveline = powertrainSubsystemFieldsHtml(sections.find(section => section.id === 'pDriveline'));
assert(driveline.indexOf('diff_T_preload') < driveline.indexOf('<details'));
assert(driveline.includes('<summary>Halfshafts</summary>'));
'''
    subprocess.run(
        [node, "-e", script], input=json.dumps(app.config_payload("vehicle")),
        text=True, check=True,
    )


def test_vehicle_patch_updates_aero_cells_without_replacing_arrays(tmp_path, monkeypatch) -> None:
    from copy import deepcopy
    from app import data_services

    original = app.config_payload("vehicle")["data"]
    path = tmp_path / "vehicle.yml"
    path.write_text(yaml.safe_dump(original))
    monkeypatch.setattr(data_services, "_config_file_path", lambda spec: path)
    monkeypatch.setattr(data_services, "config_summary", lambda spec: {"id": spec.id})
    result = data_services.patch_config("vehicle", {
        '["aero","front_ride_height_grid_m",0]': .037125,
        '["aero","rear_ride_height_grid_m",1]': .06475,
        '["aero","downforce_table_n",1,2]': 321.987654,
    })
    expected = deepcopy(original["aero"])
    expected["front_ride_height_grid_m"][0] = .037125
    expected["rear_ride_height_grid_m"][1] = .06475
    expected["downforce_table_n"][1][2] = 321.987654
    assert result["data"]["aero"] == expected
    assert yaml.safe_load(path.read_text())["aero"] == expected


@pytest.mark.parametrize("index", [-1, 5, "0", True, 1.5])
def test_vehicle_patch_rejects_invalid_array_indices_without_writing(tmp_path, monkeypatch, index) -> None:
    from app import data_services

    original = app.config_payload("vehicle")["data"]
    path = tmp_path / "vehicle.yml"
    text = yaml.safe_dump(original)
    path.write_text(text)
    monkeypatch.setattr(data_services, "_config_file_path", lambda spec: path)
    with pytest.raises(IndexError, match="Config array index"):
        data_services.patch_config("vehicle", {
            json.dumps(["aero", "front_ride_height_grid_m", index]): .04,
        })
    assert path.read_text() == text
