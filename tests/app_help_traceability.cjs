const fs = require('node:fs');
const vm = require('node:vm');
const assert = require('node:assert/strict');
const source = fs.readFileSync('app/static/vendor/katex/katex.min.js', 'utf8') + '\n' + fs.readFileSync('app/static/simulation_diagrams.js', 'utf8') + '\n' + fs.readFileSync('app/static/app.js', 'utf8').split('\nwireEvents();')[0];
const ctx = vm.createContext({localStorage:{getItem:()=>null}, console, assert, document:{compatMode:'CSS1Compat',body:{classList:{toggle(){}}}}});
vm.runInContext(source, ctx);
ctx.workflows = JSON.parse(process.argv[2] || '[]');
vm.runInContext(`
for (const area of PARAMETER_AREAS) assert.ok(SETUP_DOC_TOPICS[area.id], 'Missing setup documentation: '+area.id);
for (const id of workflows) assert.ok(WORKFLOW_DOC_TOPICS[id], 'Missing workflow documentation: '+id);
const common = ['Report','Force-based','Numerics','Execution','Closed loop','Fit'];
for (const group of common) assert.ok(configGroupDocsUrl(group).includes('#'));
assert.ok(configGroupDocsUrl('Report').endsWith('#report'));
assert.ok(configGroupDocsUrl('Force-based').endsWith('#force-based'));
assert.ok(fieldDocsUrl({path:['plots','moment_ratio_roll','enabled']}).endsWith('#moment-per-applied-force'));
assert.ok(fieldDocsUrl({path:['simulation','tolerance'],docsUrl:sectionDocsUrl('numerics-and-execution')}).endsWith('#numerics-and-execution'));
for (const id of ['mbd-maneuver','racing-line','four-post','ggv','lap-qss']) {
 const html = simulationMethodHtml({id});
 assert.ok(html.includes(workflowDocsUrl(id)), id);
 assert.ok(html.includes('rel="noopener noreferrer"'));
}
`, ctx);
ctx.localStorage.getItem = () => 'http://127.0.0.1:5173';
vm.runInContext(`
assert.equal(fieldDocsUrl({path:['plots','moment_ratio_roll','enabled']}), 'http://127.0.0.1:5173/reference/vehicle-dynamics#moment-per-applied-force');
assert.ok(docsLink('https://bobdyn.com/bobsim/app#setup').includes('http://127.0.0.1:5173/bobsim/app#setup'));
assert.ok(infoHint('Help', 'Text').includes('http://127.0.0.1:5173/bobsim/app'));
assert.equal(documentationUrl('https://example.com/'), 'https://example.com/');
`, ctx);
ctx.localStorage.getItem = () => 'javascript:alert(1)';
vm.runInContext(`assert.equal(documentationUrl('https://bobdyn.com/bobsim/app'), 'https://bobdyn.com/bobsim/app')`, ctx);
ctx.localStorage.getItem = () => null;
// A docs checkout is optional in CI; maintainers pass its built directory for anchor validation.
if (process.argv[3]) {
  const topics = vm.runInContext('[...Object.values(SETUP_DOC_TOPICS), ...Object.values(WORKFLOW_DOC_TOPICS), "report", "force-based", "numerics-and-execution", "results-and-archive", "replay", "settings-and-files"]',ctx);
  const html = fs.readFileSync(process.argv[3]+'/bobsim/section-reference.html','utf8');
  for (const topic of topics) assert.ok(html.includes('id="'+topic+'"'), 'Missing built anchor: '+topic);
  const dynamics = fs.readFileSync(process.argv[3]+'/reference/vehicle-dynamics.html','utf8');
  for (const anchor of vm.runInContext('Object.values(PLOT_DOC_ANCHORS)',ctx)) {
    assert.ok(dynamics.includes('id="'+anchor+'"'), 'Missing metric anchor: '+anchor);
  }
}
console.log('Section and workflow help coverage passed');
