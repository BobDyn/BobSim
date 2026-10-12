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
const renderSetup = () => {};
const queueTirePayloadRefresh = () => {};
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
