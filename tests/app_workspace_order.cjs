const fs = require('node:fs');
const vm = require('node:vm');
const assert = require('node:assert/strict');
const source = fs.readFileSync('app/static/simulation_diagrams.js','utf8') + '\n' + fs.readFileSync('app/static/app.js','utf8').split('\nwireEvents();')[0];
const ctx = vm.createContext({localStorage:{getItem:()=>null}, console, assert, document:{compatMode:'CSS1Compat',body:{classList:{toggle(){}}}}});
vm.runInContext(source,ctx);
vm.runInContext(`
(async () => {
  state.simulationWorkspace={group_order:['lap','kinematic'],simulations:[
    {id:'a',workflow_id:'ggv'}, {id:'b',workflow_id:'ymd'}, {id:'c',workflow_id:'four-post'}]};
  assert.deepEqual(orderedSimulationGroups().map(g=>g.id),['lap','kinematic','steady-state','transient','track']);
  assert.deepEqual(simulationSiblingIds('a','simulation'),['a','b']);
  const handlers={}, markers=new Set();
  const target=id=>({dataset:{simulationBranch:id,analysisGroup:id},
    getBoundingClientRect:()=>({top:100,height:80}),
    classList:{add:kind=>markers.add(kind),remove:(...kinds)=>kinds.forEach(kind=>markers.delete(kind))}});
  const b=target('b'), c=target('c'), group=target('track');
  const tree={addEventListener:(name,fn)=>handlers[name]=fn,
    querySelectorAll:()=>[b,c,group], contains:()=>false};
  const pane={scrollTop:100,getBoundingClientRect:()=>({top:0,bottom:500})};
  document={getElementById:id=>id==='simulation-tree'?tree:{hidden:false},querySelector:()=>pane};
  let moved=null;
  workspaceAction=fn=>fn(); moveWorkspaceItem=async(...args)=>{moved=args;};
  wireSimulationReorder();
  const dataTransfer={setData(){}};
  const start=(id,scope)=>handlers.dragstart({target:{closest:()=>({dataset:{reorderId:id,reorderScope:scope}})},dataTransfer});
  const over=(node,y)=>handlers.dragover({target:{closest:()=>node},clientY:y,dataTransfer,preventDefault(){}});
  start('a','simulation'); over(b,110);
  assert.ok(markers.has('reorder-before')); assert.equal(dataTransfer.dropEffect,'move');
  handlers.drop({preventDefault(){}});
  assert.deepEqual(moved,['a','simulation',{target_id:'b',position:'before'}]); assert.equal(markers.size,0);
  moved=null; start('a','simulation'); over(c,175); handlers.drop({preventDefault(){}});
  assert.equal(moved,null,'cross-group drop must not submit a move'); assert.equal(markers.size,0);
  start('lap','group'); over(group,175); assert.ok(markers.has('reorder-after'));
  handlers.drop({preventDefault(){}});
  assert.deepEqual(moved,['lap','group',{target_id:'track',position:'after'}]);
  start('a','simulation'); over(b,110); handlers.dragend(); assert.equal(markers.size,0);
  moved=null; handlers.dragstart({target:{closest:()=>null},dataTransfer}); over(b,110);
  handlers.drop({preventDefault(){}}); assert.equal(moved,null,'Results drag must remain separate from reordering');
})()
`,ctx).then(()=>console.log('Workspace reorder interactions passed')).catch(error=>{console.error(error);process.exitCode=1;});
