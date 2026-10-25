const fs=require('node:fs'),vm=require('node:vm'),assert=require('node:assert/strict');
const source=fs.readFileSync('app/static/report_editor.js','utf8');
const handlers={},calls=[];let reduced=false;
const canvas={scrollTop:0,clientHeight:500,scrollHeight:3000,scrollTo:options=>calls.push(options)};
const context=vm.createContext({Math,matchMedia:()=>({matches:reduced}),setTimeout:()=>1,clearTimeout:()=>{},
  dialog:{addEventListener:(name,fn)=>handlers[name]=fn}});
vm.runInContext(source.slice(source.indexOf('  // The browser animates scrolling'),source.indexOf('  let dragging=null;')),context);
function wheel(delta,extra={}) {
  let prevented=false;
  handlers.wheel({target:{closest:selector=>selector==='[data-document]'?canvas:null},deltaMode:0,deltaX:0,deltaY:delta,
    preventDefault:()=>prevented=true,...extra});
  return prevented;
}
assert.ok(wheel(120));assert.equal(calls.at(-1).top,120);assert.equal(calls.at(-1).behavior,'smooth');
assert.ok(wheel(120));assert.equal(calls.at(-1).top,240);
canvas.scrollTop=100;assert.ok(wheel(-60));assert.equal(calls.at(-1).top,40);
assert.equal(wheel(5),false);assert.equal(calls.at(-1).behavior,'auto');
reduced=true;assert.equal(wheel(120),false);reduced=false;
assert.equal(wheel(120,{ctrlKey:true}),false);
assert.ok(wheel(120));handlers.pointerdown();assert.equal(calls.at(-1).top,100);
canvas.scrollTop=2500;assert.equal(wheel(120),false);
console.log('Native smooth scroll, accumulated targets, direction changes and cancellation passed');
