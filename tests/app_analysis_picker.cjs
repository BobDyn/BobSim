const fs = require('node:fs');
const vm = require('node:vm');
const assert = require('node:assert/strict');
const source = fs.readFileSync('app/static/vendor/katex/katex.min.js', 'utf8') + '\n' + fs.readFileSync('app/static/app.js', 'utf8').split('\nwireEvents();')[0];
const ctx = vm.createContext({localStorage:{getItem:()=>null}, console, assert,
  document:{compatMode:"CSS1Compat",body:{classList:{toggle(){}}}}});
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

for (const id of ['four-post', 'steady-state', 'transient', 'ramp-steer', 'mbd-step-steer', 'reduced-ramp-steer', 'reduced-step-steer', 'ggv', 'ymd', 'lap-qss', 'lap-transient']) {
  const guide = vm.runInContext(`simulationMethodGuide(${JSON.stringify(id)})`, ctx);
  for (const key of ['method', 'inputs', 'outputs', 'limits']) assert.ok(guide[key].length >= 3, `${id}: ${key}`);
  for (const path of guide.sources) assert.ok(fs.existsSync(path), `${id}: missing source ${path}`);
  const html = vm.runInContext(`simulationMethodHtml({id:${JSON.stringify(id)}})`, ctx);
  assert.match(html, /How it works/);
  assert.match(html, /Assumptions and limits/);
  assert.match(html, /Implementation sources/);
}
const markup = fs.readFileSync('app/static/index.html', 'utf8');
assert.doesNotMatch(markup, /simulation-tree-toolbar[^\n]*add-simulation-btn/);
assert.match(source, /simulation-tree-root[^\n]*add-simulation-btn/);

for (const id of ['four-post','steady-state','transient','ramp-steer','mbd-step-steer','reduced-ramp-steer','reduced-step-steer','ggv','ymd','lap-qss','lap-transient']) {
  const math = vm.runInContext(`simulationMathHtml(${JSON.stringify(id)})`,ctx);
  assert.match(math,/class="katex"/);
  assert.match(math,/<math /);
  assert.doesNotMatch(math,/katex-error/);
  assert.match(math,/<p>/);
  assert.doesNotMatch(math,/undefined/);
}
assert.match(vm.runInContext("simulationMathHtml('ggv')",ctx),/steering and wheel torque/);
assert.match(vm.runInContext("simulationMathHtml('lap-qss')",ctx),/Accelerate forward, brake backward/);
assert.match(vm.runInContext("simulationMathHtml('steady-state')",ctx),/Position and heading still change/);

const katexCSS = fs.readFileSync('app/static/vendor/katex/katex.min.css','utf8');
for (const [,font] of katexCSS.matchAll(/url\(([^)]+)\)/g)) assert.ok(fs.existsSync('app/static/vendor/katex/'+font));
assert.ok(markup.indexOf('/static/vendor/katex/katex.min.js') < markup.indexOf('/static/app.js'));
