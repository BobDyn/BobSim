const fs = require('node:fs');
const vm = require('node:vm');
const assert = require('node:assert/strict');
const source = fs.readFileSync('app/static/app.js', 'utf8').split('\nwireEvents();')[0];
const ctx = vm.createContext({localStorage:{getItem:()=>null}, console, assert,
  document:{body:{classList:{toggle(){}}}}});
vm.runInContext(source, ctx);
vm.runInContext(`
(async () => {
  activeVehicleKey = () => 'vehicle-a';
  renderStudies = renderResultExplorer = renderResultPlotCanvas = () => {};
  refreshResultBaseline = async () => {};
  setView = () => {};
  const detail = {path:'run/signals.csv', numeric_columns:['time','ax','ay','speed'], x_candidates:['time']};
  const first = {id:'one',kind:'signals',run_id:'run',settings:{x_axis:'ax',signals:['ay'],color_signal:'speed',source_label:'Signals',compare_baseline:true}};
  const second = {id:'two',kind:'signals',run_id:'run',settings:{x_axis:'time',signals:['speed'],color_signal:''}};
  state.simulationWorkspace = {simulations:[{id:'sim',visualizations:[first,second]}]};
  state.selectedSimulationId = 'sim';
  const requests = [];
  api = async (url, options) => {
    if (url.startsWith('/api/results/source?')) return detail;
    if (url === '/api/results/series') return {series:[]};
    assert.equal(url, '/api/simulations/visualization-settings');
    requests.push(JSON.parse(options.body));
    return {};
  };
  selectedResultSource = () => ({label:'Signals'});
  openSimulationVisualization(first);
  state.selectedResultSourcePath = detail.path;
  await loadResultSource();
  assert.equal(state.resultXAxis, 'ax');
  assert.deepEqual(state.resultSelectedSignals, ['ay']);
  assert.equal(state.resultColorSignal, 'speed');
  assert.equal(state.resultCompareBaseline, true);
  state.resultSelectedSignals = ['speed','ay'];
  const save = saveResultSettings();
  state.resultBaselinePayload = {series:[1]};
  state.resultComparison = {changes:[1]};
  openSimulationVisualization(second);
  assert.equal(state.resultBaselinePayload, null);
  assert.equal(state.resultComparison, null);
  assert.equal(state.resultSourceDetail, null, 'same-run siblings must not share loaded controls');
  state.selectedResultSourcePath = detail.path;
  await loadResultSource();
  await save;
  assert.equal(state.resultXAxis, 'time');
  assert.deepEqual(state.resultSelectedSignals, ['speed']);
  assert.equal(state.resultCompareBaseline, false);
  assert.equal(requests[0].child_id, 'one');
  assert.equal(requests[0].vehicle_key, 'vehicle-a');
  assert.equal(requests[0].settings.source_label, 'Signals');
  assert.equal('path' in requests[0].settings, false);
  openSimulationVisualization(first);
  state.selectedResultSourcePath = detail.path;
  await loadResultSource();
  assert.deepEqual(state.resultSelectedSignals, ['speed','ay']);

  // Loading the latest run retains named channels, while removed channels fall back safely.
  first.run_id = 'new-run';
  openSimulationVisualization(first);
  assert.equal(state.resultSourceDetail, null);
  restoreResultSettings({numeric_columns:['time','speed'],x_candidates:['time']});
  assert.equal(state.resultXAxis, 'time');
  assert.deepEqual(state.resultSelectedSignals, ['speed']);
  assert.equal(first.settings.x_axis, 'ax', 'fallback must not erase saved preferences');
  restoreResultSettings(detail, {signals:[],x_axis:'time',color_signal:'missing'});
  assert.deepEqual(state.resultSelectedSignals, []);
  assert.equal(state.resultColorSignal, '');

  // A completed request from another child must never replace its sibling's state.
  let finish;
  api = () => new Promise(resolve => { finish = resolve; });
  state.selectedResultSourcePath = detail.path;
  const oldLoad = loadResultSource();
  openSimulationVisualization(second);
  state.selectedResultSourcePath = detail.path;
  finish(detail);
  await oldLoad;
  assert.equal(state.resultSourceDetail, null);
  assert.equal(state.resultPlotStatus, 'idle');

  let fail;
  api = () => new Promise((resolve, reject) => { fail = reject; });
  const oldFailure = loadResultSource();
  openSimulationVisualization(first);
  state.selectedResultSourcePath = detail.path;
  fail(new Error('old source failed'));
  await oldFailure;
  assert.equal(state.resultPlotStatus, 'idle', 'stale failures must not poison the new child');

  // A settings edit made while polling must not be replaced by the old server response.
  const serverWorkspace = JSON.parse(JSON.stringify(state.simulationWorkspace));
  state.simulationWorkspace.vehicle_key = serverWorkspace.vehicle_key = 'vehicle-a';
  state.resultSourceDetail = detail;
  let releaseFetch;
  let notifyFetch;
  const fetched = new Promise(resolve => { notifyFetch = resolve; });
  let reads = 0;
  api = async (url, options) => {
    if (url === '/api/simulations/visualization-settings' && options) {
      const request = JSON.parse(options.body);
      serverWorkspace.simulations[0].visualizations.find(child => child.id === request.child_id).settings = request.settings;
      return serverWorkspace;
    }
    if (url === '/api/simulations') {
      if (++reads === 1) {
        const stale = JSON.parse(JSON.stringify(serverWorkspace));
        notifyFetch();
        return new Promise(resolve => { releaseFetch = () => resolve(stale); });
      }
      return JSON.parse(JSON.stringify(serverWorkspace));
    }
    return {results:[]};
  };
  savedResults = () => [];
  const refresh = refreshSavedResults();
  await fetched;
  state.resultXAxis = 'ay';
  state.resultSelectedSignals = ['ax'];
  const pending = saveResultSettings();
  openSimulationVisualization(second);
  releaseFetch();
  await Promise.all([refresh, pending]);
  assert.equal(reads, 2);
  assert.equal(state.selectedVisualizationId, 'two');
  assert.equal(state.simulationWorkspace.simulations[0].visualizations[0].settings.x_axis, 'ay');
  // Mutating workspace responses must follow the same save ordering as polling.
  let releaseAction;
  let notifyAction;
  const actionStarted = new Promise(resolve => { notifyAction = resolve; });
  const priorApi = api;
  api = async (url, options) => {
    if (url === '/api/simulations' && options) {
      const stale = JSON.parse(JSON.stringify(serverWorkspace));
      stale.simulation = stale.simulations[0];
      stale.config = {id:'preserve-action-response'};
      notifyAction();
      return new Promise(resolve => { releaseAction = () => resolve(stale); });
    }
    return priorApi(url, options);
  };
  state.resultSourceDetail = detail;
  const action = simulationRequest('load', {id:'sim'});
  await actionStarted;
  state.resultXAxis = 'speed';
  const actionSave = saveResultSettings();
  releaseAction();
  const response = await action;
  await actionSave;
  assert.equal(response.config.id, 'preserve-action-response');
  assert.equal(response.simulation.visualizations[1].settings.x_axis, 'speed');
  assert.equal(state.simulationWorkspace.simulations[0].visualizations[1].settings.x_axis, 'speed');
  console.log('Plot settings behavior checks passed');
})()
`, ctx).catch(error => { console.error(error); process.exitCode = 1; });
