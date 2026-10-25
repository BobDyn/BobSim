const fs = require('node:fs');
const vm = require('node:vm');
const assert = require('node:assert/strict');
const source = fs.readFileSync('app/static/app.js', 'utf8').split('\nwireEvents();')[0];
const ctx = vm.createContext({console, assert, localStorage: {getItem: () => null},
  document: {compatMode: 'CSS1Compat', body: {classList: {toggle() {}}}}});
vm.runInContext(source, ctx);
vm.runInContext(`
activeVehicleConfigReady = () => true;
state.dirtyVehicle = false;
state.vehicleDefinitionState = 'pending';
state.status = {external_toolchain: {available: false}};
const workflow = {id:'mbd-maneuver', available:true, actions:[{id:'run-mbd-maneuver'}]};
assert.equal(canRunStandardWorkflow(workflow), true);
workflow.available = false;
workflow.unavailable_reason = 'Build the matching maneuver binary in Architecture first.';
assert.equal(canRunStandardWorkflow(workflow), false);
assert.match(standardWorkflowLockedMessage(workflow), /Architecture/);
workflow.available = true;
state.dirtyVehicle = true;
assert.equal(canRunStandardWorkflow(workflow), false);
`, ctx);
assert(!fs.readFileSync('app/static/index.html', 'utf8').includes('sim-prepare-mbd'));
console.log('Native simulation readiness passed');
