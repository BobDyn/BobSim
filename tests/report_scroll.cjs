const fs=require('node:fs'),vm=require('node:vm'),assert=require('node:assert/strict');
const source=fs.readFileSync('app/static/report_editor.js','utf8');
const handlers={},frames=new Map();let serial=0,now=0,reduced=false;
const canvas={scrollTop:0,clientHeight:500,scrollHeight:3000,isConnected:true};
const context=vm.createContext({Math,performance:{now:()=>now},matchMedia:()=>({matches:reduced}),
  requestAnimationFrame:fn=>{frames.set(++serial,fn);return serial;},cancelAnimationFrame:id=>frames.delete(id),
  dialog:{addEventListener:(name,fn)=>handlers[name]=fn}});
vm.runInContext(source.slice(source.indexOf('  // Ease discrete mouse-wheel'),source.indexOf('  let dragging=null;')),context);
function wheel(delta,extra={}) {
  let prevented=false;
  handlers.wheel({target:{closest:selector=>selector==='[data-document]'?canvas:null},deltaMode:0,deltaX:0,deltaY:delta,
    preventDefault:()=>prevented=true,...extra});
  return prevented;
}
function tick(){now+=16;const queued=[...frames.values()];frames.clear();queued.forEach(fn=>fn(now));}
assert.ok(wheel(120));assert.equal(canvas.scrollTop,0);tick();assert.ok(canvas.scrollTop>0&&canvas.scrollTop<120);
assert.ok(wheel(120));for(let i=0;i<100&&frames.size;i++)tick();assert.equal(canvas.scrollTop,240);assert.equal(frames.size,0);
assert.equal(wheel(5),false);reduced=true;assert.equal(wheel(120),false);reduced=false;
assert.equal(wheel(120,{ctrlKey:true}),false);
assert.ok(wheel(120));handlers.pointerdown();assert.equal(frames.size,0);
canvas.scrollTop=2500;assert.equal(wheel(120),false);
console.log('Wheel easing, accumulated momentum, cancellation and native-scroll fallbacks passed');
