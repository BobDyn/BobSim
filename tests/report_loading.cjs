const fs=require('node:fs'),vm=require('node:vm'),assert=require('node:assert/strict');
const source=fs.readFileSync('app/static/report_editor.js','utf8');
let calls=0,collapsed=false;
const host={hidden:true,dataset:{filePath:'old.pdf'},innerHTML:'<iframe src="old.pdf"></iframe>',collapsePdf:()=>collapsed=true};
const dialog={open:true,close(){this.open=false;}};
const context=vm.createContext({editor:{key:'old',dirty:false,inline:true},dialog,timer:null,revision:0,opening:0,
  drafts:new Map(),clone:value=>JSON.parse(JSON.stringify(value)),activeVehicleKey:()=> 'vehicle',
  clearTimeout:()=>{},api:()=>{calls++;return new Promise(()=>{});},
  document:{getElementById:()=>host,querySelector:()=>({classList:{add:()=>{}}})}});
vm.runInContext(source.slice(source.indexOf('  async function openEditor('),source.indexOf('  window.openReportViewer='))+';this.openEditor=openEditor;',context);
context.openEditor({id:'run'},{id:'sim'},true);
assert.equal(dialog.open,false);assert.equal(host.hidden,false);assert.ok(collapsed);
assert.ok(host.innerHTML.includes('Preparing your report'));assert.ok(!host.innerHTML.includes('iframe'));
assert.equal(host.dataset.filePath,undefined);assert.equal(context.editor.loading,true);
context.openEditor({id:'run'},{id:'sim'},true);assert.equal(calls,1);
console.log('Loading screen precedes network requests and duplicate opens share the pending load');
