const fs = require('node:fs');
const vm = require('node:vm');
const assert = require('node:assert/strict');
const source = fs.readFileSync('app/static/app.js', 'utf8').split('\nwireEvents();')[0];
const ctx = vm.createContext({localStorage:{getItem:()=>null}, console, assert,
  document:{body:{classList:{toggle(){}}}}});
vm.runInContext(source, ctx);
vm.runInContext(`
(async () => {
  const nodes = new Map();
  const element = id => {
    if (!nodes.has(id)) nodes.set(id, {open:false, textContent:'', innerHTML:'',
      querySelectorAll:()=>[], querySelector:()=>null,
      showModal(){this.open=true;}, close(){this.open=false;this.onclose?.();}});
    return nodes.get(id);
  };
  document.getElementById = element;
  document.querySelector = element;
  renderSimulationWorkspace = () => {};
  saveSimulationEdits = async () => {};
  state.simulationWorkspace = {analysis_groups:['transient'],simulations:[]};
  state.selectedSimulationId = 'existing';
  state.selectedVisualizationId = 'existing-plot';
  state.view = 'studies';
  state.simModalOpen = false;
  standardWorkflows = () => [
    {id:'four-post'}, {id:'ggv'}, {id:'lap-qss'}, {id:'ramp-steer'},
    {id:'reduced-ramp-steer',model:{model_dofs:[6]}}, {id:'lap-transient'},
  ];
  workflowCard = workflow => '<article data-workflow="'+workflow.id+'"></article>';
  wireSimulationCatalog();
  await showSimulationCatalog('transient');
  assert.equal(element('simulation-catalog').open, true);
  assert.equal(state.selectedSimulationId, 'existing');
  assert.equal(state.selectedVisualizationId, 'existing-plot');
  assert.equal(state.view, 'studies');
  assert.match(element('workflow-grid').innerHTML, /ramp-steer/);
  assert.match(element('workflow-grid').innerHTML, /lap-transient/);
  assert.doesNotMatch(element('workflow-grid').innerHTML, /lap-qss|four-post|simulation-categories/);
  closeSimulationCatalog();
  assert.equal(element('simulation-catalog').open, false);
  assert.equal(state.simulationCatalogOpen, false);
  assert.equal(state.selectedVisualizationId, 'existing-plot');
  await showSimulationCatalog('transient');
  element('simulation-catalog').close(); // The browser's Escape handling closes native dialogs.
  assert.equal(state.simulationCatalogOpen, false);

  await showAnalysisPicker();
  assert.equal(element('analysis-picker').open, true);
  assert.match(element('analysis-picker-options').innerHTML, /data-add-analysis="transient" disabled/);
  assert.match(element('analysis-picker-options').innerHTML, /data-add-analysis="kinematic">/);
  assert.match(element('analysis-picker-options').innerHTML, /data-add-analysis="steady-state">/);
  element('[data-close-analysis-picker]').onclick();
  assert.equal(element('analysis-picker').open, false);

  const calls = [];
  api = async (url, options) => { calls.push([url,JSON.parse(options.body)]); return {}; };
  let selected;
  const model = {value:'reduced-ramp-steer:14',dataset:{responseModel:'ramp-steer'},
    addEventListener(type, callback){selected=callback;}};
  element('workflow-grid').querySelectorAll = selector => selector === '[data-response-model]' ? [model] : [];
  renderWorkflows();
  selected();
  assert.equal(calls.length, 0, 'model previews must not mutate active config');
  assert.equal(state.selectedSimulationId, 'existing');
  assert.equal(responseModelDofs['ramp-steer'],14);
  simulationRequest = async (action, values) => {
    calls.push([action,values]);return {simulation:{id:'new-sim'}};
  };
  let overview;
  openSimulationOverview = async id => {overview=id;};
  await configureSimulationWorkflow('reduced-ramp-steer');
  assert.equal(calls[0][0],'/api/configs/reduced-ramp-steer');
  assert.equal(calls[0][1].values['["model_dof"]'],14);
  assert.equal(calls[1][0],'create');
  assert.equal(calls[1][1].workflow_id,'reduced-ramp-steer');
  assert.equal(overview,'new-sim');
  assert.equal(element('simulation-catalog').open,false);
  console.log('Analysis picker checks passed');
})()
`, ctx).catch(error => {console.error(error);process.exitCode=1;});
