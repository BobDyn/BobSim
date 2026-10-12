"""Checks for the component editors without a browser runtime."""
from __future__ import annotations

import json
from pathlib import Path
import shutil
import subprocess

import pytest

from app import app


def test_aero_and_powertrain_editors_preserve_fields() -> None:
    node = shutil.which("node")
    if node is None:
        pytest.skip("Node is required for editor checks")
    source = (Path(__file__).parents[1] / "app/static/app.js").read_text()
    names = (
        "aeroSectionHtml", "aeroTableControl", "aeroSurfaceRowsFromTable", "aeroRideHeightLabel",
        "powertrainSubsystemFieldsHtml", "powertrainSubsystems", "powertrainFieldSubsystem",
        "arrayScalarControl", "arrayCellInputHtml", "formatNumber", "escapeHtml",
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
for (const map of AERO_MAPS) {
  const field = aeroFields.find(field => field.path[1] === map.key);
  const table = aeroTableControl(field, map, payload.data.aero);
  assert.equal((table.match(/data-array-cell/g) || []).length, field.value.flat().length);
  for (const [row, values] of field.value.entries()) {
    for (const [col, value] of values.entries()) {
      assert(table.includes(`data-row="${row}" data-col="${col}"`));
      assert(table.includes(`value="${value}"`));
    }
  }
  assert(html.includes(`data-aero-map-panel="${map.key}"`));
}
assert.equal((html.match(/data-array-path=/g) || []).length, 5);
assert.equal((html.match(/<section[^>]+ hidden>/g) || []).length, 4);
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
assert(motor.indexOf('T_peak') < motor.indexOf('<details'));
assert(motor.indexOf('rotorJ') > motor.indexOf('<details'));
const driveline = powertrainSubsystemFieldsHtml(sections.find(section => section.id === 'pDriveline'));
assert(driveline.indexOf('diff_T_preload') < driveline.indexOf('<details'));
assert(driveline.includes('<summary>Halfshafts</summary>'));
'''
    subprocess.run(
        [node, "-e", script], input=json.dumps(app.config_payload("vehicle")),
        text=True, check=True,
    )
