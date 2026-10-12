"""Vehicle edit history behavior."""
from pathlib import Path
import shutil
import subprocess

import pytest


def test_vehicle_undo_redo_preserves_states_and_skips_selection_only_entries():
    node = shutil.which("node")
    if not node:
        pytest.skip("Node is not installed")
    source = (Path(__file__).parents[1] / "app/static/app.js").read_text()
    history = source[source.index("function restoreVehicleEdit("):source.index("function handleUndoShortcut(")]
    script = r'''
const assert = require('node:assert/strict');
const state = {undoStack: [], redoStack: [], cleanVehicleSignature: '{"x":1}', vehicleDefinitionState: 'pending'};
let data = {x: 3};
const vehicleDataSignature = JSON.stringify;
const snapshotVehicleState = () => ({data: structuredClone(data)});
const applyVehicleDataToPayload = value => {data = structuredClone(value);};
const renderSetup = () => {assert.equal(state.suppressUndo, true);};
const isTirePreviewArea = () => false;
const queueTirePayloadRefresh = () => {throw new Error("Unrelated edits must not reevaluate tires");};
const queueKinematicsRefresh = () => {};
''' + history + r'''
state.undoStack = [{data:{x:1}}, {data:{x:2}}, {data:{x:3}}];
assert(undoVehicleEdit());
assert.deepEqual(data, {x:2});
assert(undoVehicleEdit());
assert.deepEqual(data, {x:1});
assert.equal(state.dirtyVehicle, false);
assert.equal(undoVehicleEdit(), false);
assert(redoVehicleEdit());
assert.deepEqual(data, {x:2});
assert(redoVehicleEdit());
assert.deepEqual(data, {x:3});
assert.equal(redoVehicleEdit(), false);
assert.equal(state.dirtyVehicle, true);
'''
    subprocess.run([node, "-e", script], check=True, capture_output=True, text=True)


def test_tire_preview_shows_loading_instead_of_empty_force_plots():
    node = shutil.which("node")
    if not node:
        pytest.skip("Node is not installed")
    source = (Path(__file__).parents[1] / "app/static/app.js").read_text()
    preview = source[source.index("function drawTirePreview("):source.index("function drawTirePreviewError(")]
    script = r'''
const assert = require('node:assert/strict');
const state = {tirePayload: null, tirePayloadUpdating: true};
const canvasPalette = () => ({});
const drawPreviewGrid = () => {};
const messages = [];
const drawCanvasText = (ctx, message) => messages.push(message);
const drawTireSetupPreview = () => {throw new Error('Cannot plot unloaded data');};
''' + preview + r'''
drawTirePreview({}, 800, 600, {});
assert(messages.includes('Loading tire plots...'));
state.tirePayloadUpdating = false;
drawTirePreview({}, 800, 600, {});
assert(messages.includes('Tire plots unavailable. Check the selected tire files.'));
'''
    subprocess.run([node, "-e", script], check=True, capture_output=True, text=True)
