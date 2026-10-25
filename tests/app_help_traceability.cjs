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
assert.ok(fieldDocsUrl({path:['plots','moment_ratio_roll','enabled']}).endsWith('#jacking-and-anti-geometry'));
assert.ok(fieldDocsUrl({path:['simulation','tolerance'],docsUrl:sectionDocsUrl('numerics-and-execution')}).endsWith('#numerics-and-execution'));
for (const id of ['mbd-maneuver','racing-line','four-post','ggv','lap-qss']) {
 const html = simulationMethodHtml({id});
 assert.ok(html.includes(workflowDocsUrl(id)), id);
 assert.ok(html.includes('rel="noopener noreferrer"'));
}
`, ctx);
// A docs checkout is optional in CI; maintainers pass its built directory for anchor validation.
if (process.argv[3]) {
  const topics = vm.runInContext('[...Object.values(SETUP_DOC_TOPICS), ...Object.values(WORKFLOW_DOC_TOPICS), "report", "force-based", "numerics-and-execution", "results-and-archive", "replay", "settings-and-files"]',ctx);
  const html = fs.readFileSync(process.argv[3]+'/bobsim/section-reference.html','utf8');
  for (const topic of topics) assert.ok(html.includes('id="'+topic+'"'), 'Missing built anchor: '+topic);
}
console.log('Section and workflow help coverage passed');
