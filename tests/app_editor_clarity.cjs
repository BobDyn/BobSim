const fs = require('node:fs');
const vm = require('node:vm');
const assert = require('node:assert/strict');
const source = fs.readFileSync('app/static/simulation_diagrams.js', 'utf8') + '\n' + fs.readFileSync('app/static/vendor/katex/katex.min.js', 'utf8') + '\n' + fs.readFileSync('app/static/app.js', 'utf8').split('\nwireEvents();')[0];
const ctx = vm.createContext({localStorage:{getItem:()=>null}, console, assert, document:{compatMode:"CSS1Compat",body:{classList:{toggle(){}}}}});
vm.runInContext(source, ctx);
vm.runInContext(`
for (const view of ['iso','top','side']) {
  const axes = [{x:1,y:0,z:0},{x:0,y:1,z:0},{x:0,y:0,z:1}].map(p=>projectPointWithAngles(p,view,0.7,0.4));
  const [a,b,c] = axes.map(p=>[p.u,p.v,p.depth]);
  const determinant = a[0]*(b[1]*c[2]-b[2]*c[1])-a[1]*(b[0]*c[2]-b[2]*c[0])+a[2]*(b[0]*c[1]-b[1]*c[0]);
  assert.ok(Math.abs(determinant-1)<1e-12, view+' must preserve handedness');
}
const isoAxes = [{x:1,y:0,z:0},{x:0,y:1,z:0},{x:0,y:0,z:1}]
  .map(p=>projectPointWithAngles(p,'iso',DEFAULT_VEHICLE_YAW,DEFAULT_VEHICLE_PITCH));
assert.ok(isoAxes[0].u<0 && isoAxes[0].v<0 && isoAxes[0].depth>0);
assert.ok(isoAxes[1].u>0 && isoAxes[1].v<0);
assert.ok(Math.abs(isoAxes[2].u)<1e-12); assert.ok(isoAxes[2].v>0);
for (const axis of isoAxes) assert.ok(Math.abs(Math.hypot(axis.u,axis.v)-Math.sqrt(2/3))<1e-12);
state.vehicleComponentSelection={mass:'body'};
assert.ok(isSelectedMassComponent({group:'mass',sourcePath:['sprung_mass']}));
assert.equal(isSelectedMassComponent({group:'mass',sourcePath:['driver_mass']}),false);
state.vehicleComponentSelection.mass='front.masses.upright';
for (const side of ['left','right']) assert.ok(isSelectedMassComponent({group:'mass',side,sourcePath:['front','masses','upright']}));
assert.equal(isSelectedMassComponent({group:'mass',aggregate:true}),false);
const fitModel = {points:[
  {id:'a',x:-2,y:-0.7,z:0}, {id:'b',x:0,y:0.7,z:0.6},
  {id:'c',x:0,y:-0.7,z:0}, {id:'d',x:-2,y:0.7,z:0.6},
]};
state.vehiclePreviewZoom=1; setPreviewPan(0,0);
for (const [width,height] of [[900,500],[400,700]]) {
  for (const view of ['iso','top','side']) {
    const fit = projectVehicleModel(fitModel,width,height,view);
    const points = [...fit.map.values()];
    assert.ok(points.every(p=>p.x2>=23.99 && p.x2<=width-23.99 && p.y2>=23.99 && p.y2<=height-23.99));
    const spanX = Math.max(...points.map(p=>p.x2))-Math.min(...points.map(p=>p.x2));
    const spanY = Math.max(...points.map(p=>p.y2))-Math.min(...points.map(p=>p.y2));
    assert.ok(Math.abs(spanX-(width-48))<1e-8 || Math.abs(spanY-(height-48))<1e-8);
  }
  for (const panel of architectureAxlePanels(width,height)) {
    assert.ok(panel.y>=0 && panel.y+panel.height<=height);
    assert.ok(panel.views.every(v=>v.y>=panel.y && v.y+v.height<=panel.y+panel.height));
  }
}
state.vehiclePreviewFit=null;
state.vehiclePreviewYaw=DEFAULT_VEHICLE_YAW;
state.vehiclePreviewPitch=DEFAULT_VEHICLE_PITCH;
const initialFit=projectVehicleModel(fitModel,900,500,'iso');
const fixedCenter=JSON.stringify(state.vehiclePreviewFit.center);
state.vehiclePreviewYaw+=0.6; state.vehiclePreviewPitch+=0.2;
assert.equal(projectVehicleModel(fitModel,900,500,'iso').scale,initialFit.scale);
const editedModel={points:fitModel.points.map(p=>({...p,x:p.x*2}))};
assert.equal(projectVehicleModel(editedModel,900,500,'iso').scale,initialFit.scale);
assert.equal(JSON.stringify(state.vehiclePreviewFit.center),fixedCenter);
assert.equal(projectVehicleModel(editedModel,500,300,'iso').scale,initialFit.scale);
state.vehiclePreviewZoom=2;
assert.equal(projectVehicleModel(editedModel,900,500,'iso').scale,initialFit.scale*2);
state.vehiclePreviewZoom=1; state.vehiclePreviewFit=null;
assert.notEqual(projectVehicleModel(editedModel,900,500,'iso').scale,initialFit.scale);
const driverLeft = projectPointWithAngles({x:0,y:1,z:0},'iso',-Math.PI/2,0);
assert.ok(driverLeft.u < 0);
assert.ok(projectPointWithAngles({x:0,y:0,z:1},'iso',-Math.PI/2,0).v > 0);
setPreviewPan(50000,-60000); clampPreviewCamera();
assert.equal(state.vehiclePreviewPanX,50000); assert.equal(state.vehiclePreviewPanY,-60000);
setPreviewPan(Infinity,NaN); assert.equal(state.vehiclePreviewPanX,0); assert.equal(state.vehiclePreviewPanY,0);
const popup = {id:'test-help',matches:()=>true,style:{},getBoundingClientRect:()=>({width:280,height:100})};
document.querySelector=()=>({getBoundingClientRect:()=>({left:950,top:750,bottom:774})});
window={innerWidth:1000,innerHeight:800};
positionInfoPopup(popup);
assert.equal(popup.style.left,'712px'); assert.equal(popup.style.top,'644px');
popup.open=false;
popup.showModal=()=>{popup.open=true;};
popup.close=()=>{popup.open=false;};
popup.closest=selector=>selector==='.info-popup'?popup:null;
document.getElementById=()=>popup;
const helpButton={dataset:{infoPopup:popup.id}};
handleInfoPopupClick({target:{closest:selector=>selector==='[data-info-popup]'?helpButton:null}});
assert.equal(popup.open,true,'help opens only when requested');
handleInfoPopupClick({target:{closest:selector=>selector==='.info-popup'?popup:selector==='.info-close'?{}:null}});
assert.equal(popup.open,false,'close button dismisses help');
popup.open=true;
handleInfoPopupClick({target:popup});
assert.equal(popup.open,false,'clicking the backdrop dismisses help');

isSpatialPreviewArea=()=>true;
drawVehicleFromForm=()=>{};
syncViewButtons=()=>{};
state.rotationSensitivity=1;
state.vehicleDrag={pointerId:1,mode:'rotate',x:0,y:0,yaw:0,pitch:0};
updatePreviewDrag({pointerId:1,clientX:10,clientY:0});
assert.ok(projectPoint({x:0,y:1,z:0},'iso').u>0,'near-side point follows rightward rotation drag');
state.vehicleDrag=null;
const aeroInput = {front_left_ride_height_ref_m:[0,0.2,0.08],rear_left_ride_height_ref_m:[-1.4,0.3,0.09]};
const refs = aeroRideHeightReferences(aeroInput);
assert.equal(refs.map(r=>r.label).join(','),'FL,FR,RL,RR');
for (let i=0;i<4;i+=2) {
  assert.equal(refs[i+1].point[0],refs[i].point[0]);
  assert.equal(refs[i+1].point[1],-refs[i].point[1]);
  assert.equal(refs[i+1].point[2],refs[i].point[2]);
  assert.equal(refs[i].mirrored,false);
  assert.equal(refs[i+1].mirrored,true);
}
assert.equal(aeroInput.front_left_ride_height_ref_m[1],0.2);
assert.equal(aeroRideHeightReferences({}).length,0);
const hint = infoHint('Geometry help', '<script> & coordinates');
assert.match(hint, /<dialog[^>]+class="info-popup"/);
assert.match(hint, /aria-label="Geometry help"/);
assert.match(hint, /aria-label="Close help"/);
assert.equal(hint.includes(' popover'),false);
assert.match(hint, /<svg[^>]+aria-hidden="true"/);
assert.match(hint, /data-info-popup="info-popup-/);
assert.match(hint, /&lt;script&gt; &amp; coordinates/);
assert.equal(hint.includes('<script>'),false);
assert.equal(hint.includes('<details class="info-hint" open'),false);
assert.equal(parameterAreaForField({path:['body','torsional_stiff_n_m_per_rad']}),'suspension');
const inertiaHtml = matrixControl({path:['sprung_mass','inertia_kg_m2'],value:[[1,0,0],[0,2,0],[0,0,3]],array_element_kind:'number'});
assert.equal((inertiaHtml.match(/data-array-cell/g)||[]).length,9);
assert.ok(inertiaHtml.includes('inertia-matrix'));
assert.equal(inertiaHtml.includes('style="min-width:'),false);
const massSelect = {value:'body',options:[{dataset:{componentGroupName:'Vehicle'}},{dataset:{componentGroupName:'Rear suspension'}}]};
const massPanels = [{dataset:{componentPanel:'body'}},{dataset:{componentPanel:'rear.masses.unsprung'}}];
const massEditor = {dataset:{componentEditor:'mass'},querySelector:q=>q==='[data-component-select]'?massSelect:null,querySelectorAll:()=>massPanels};
state.vehicleComponentSelection={};
syncVehicleComponentEditor(massEditor);
assert.equal(massPanels[0].hidden,false);
assert.ok(massSelect.options.every(option=>!option.disabled));
massSelect.value='rear.masses.unsprung'; syncVehicleComponentEditor(massEditor);
assert.equal(massPanels[1].hidden,false);
assert.equal(massPanels[0].hidden,true);
const curveLabels = kinematicCurveDescriptors(null);
for (const prefix of ['bump','roll','steer']) {
  const descriptor = curveLabels.find(item=>item.id===prefix+'_camber_deg');
  assert.equal(descriptor.label,'Camber');
}
assert.equal(humanizeKinematicCurve('bump_toe_deg'),'Toe');
const curveField = {path:['front','actuation','shock','spring_table','table'],value:[[0,0],[0.01,150],[0.02,430]],array_element_kind:'number'};
const originalCurve = JSON.stringify(curveField.value);
const curveHtml = matrixControl(curveField);
assert.equal(curveHtml.includes('data-spring-rate'),false);
assert.equal(curveHtml.includes('<details'),false);
assert.match(curveHtml, /matrix-heading/);
assert.equal((curveHtml.match(/data-matrix-row/g)||[]).length,3);
assert.equal((curveHtml.match(/data-array-cell/g)||[]).length,6);
assert.match(curveHtml, /value="430"/);
assert.equal(JSON.stringify(curveField.value),originalCurve);
const structured = infoHint('Controls', [['Move','Drag'],['Axis','Tab']]);
assert.ok(structured.includes('<dt>Move</dt><dd>Drag</dd>'));
assert.ok(structured.includes('<dt>Axis</dt><dd>Tab</dd>'));
fieldControl = f => '<input data-field="'+ f.path.join('.') +'">';
currentVehicleFormData = () => ({front:{tire:{template:'front.tir'}},rear:{tire:{template:'rear.tir'}}});
state.tireTemplates = {templates:[{id:'front.tir',label:'Front tire'},{id:'rear.tir',label:'Rear tire'}]};
const tireFields = ['front','rear'].flatMap(side => ['template','toe_deg'].map(name => ({path:[side,'tire',name],label:side+' '+name})));
const html = tireSectionHtml({fields:tireFields});
assert.match(html, /data-tire-axle-panel="rear" hidden/);
assert.equal((html.match(/data-field="front.tire.toe_deg"/g)||[]).length,1);
assert.equal((html.match(/data-field="rear.tire.toe_deg"/g)||[]).length,1);
assert.match(html, /value="front.tir"/);
assert.match(html, /value="rear.tir"/);
const motor = powertrainSubsystemFieldsHtml({id:'pMotor',fields:['T_peak','eta_mot','rotorJ','w_eps'].map(name=>({path:['powertrain','pMotor',name]}))});
assert.match(motor, /Electrical/);
assert.match(motor, /Inertia/);
assert.match(motor, /Numerical settings/);
for (const name of ['T_peak','eta_mot','rotorJ','w_eps']) assert.equal(motor.split('data-field="powertrain.pMotor.'+name+'"').length-1,1);
const axleSelect={value:'front',addEventListener(t,fn){assert.equal(t,'change');this.change=fn;}};
const panels = ['front','rear'].map(side=>({dataset:{tireAxlePanel:side},hidden:side==='rear',value:side+' unsaved'}));
document = {querySelectorAll:q=>q==='[data-tire-axle]'?[axleSelect]:q==='[data-tire-axle-panel]'?panels:[]};
wireTireTabs(); axleSelect.value='rear'; axleSelect.change();
assert.equal(state.activeTireAxle,'rear');
assert.equal(panels[0].hidden,true); assert.equal(panels[1].hidden,false);
axleSelect.value='front'; axleSelect.change();
assert.equal(panels[0].value,'front unsaved'); assert.equal(panels[1].value,'rear unsaved');
assert.match(axleSelectorHtml('rear','data-tire-axle'),/<option value="rear" selected>/);
assert.equal(tireFitSelectorsHtml().includes('activeTireAxle'),false);
const aeroButtons = ['maps','references'].map(view=>({dataset:{aeroView:view},classList:{toggle(){}},setAttribute(){},addEventListener(t,fn){this.click=fn;}}));
const mapEditor = {hidden:false, value:'unsaved map'};
const refEditor = {hidden:true, value:'unsaved coordinates'};
const aeroPanel = {
  querySelector:q=>q==='[data-aero-map]'?{addEventListener(){}}:q==='[data-aero-map-editor]'?mapEditor:refEditor,
  querySelectorAll:()=>aeroButtons,
};
document.querySelector=()=>aeroPanel;
drawVehicleFromForm=()=>{};
wireAeroControls(); aeroButtons[1].click();
assert.equal(state.aeroReferenceView,true); assert.equal(refEditor.hidden,false); assert.equal(mapEditor.hidden,true);
aeroButtons[0].click(); assert.equal(mapEditor.hidden,false); assert.equal(refEditor.hidden,true);
assert.equal(mapEditor.value,'unsaved map'); assert.equal(refEditor.value,'unsaved coordinates');
standardWorkflows=()=>[{id:'mbd',config_id:'mbd',requires_mbd:true}];
activeVehicleConfigReady=()=>true;
canUseStandardSim=()=>false;
workflowAvailable=()=>true;
state.dirtyVehicle=false;
assert.equal(canRunStandardWorkflow(standardWorkflows()[0]),false);
state.selectedWorkflowId='mbd';
renderStandard=()=>{};
api=async()=>({jobs:[]});
simulationRequest=async()=>({simulation:{id:'test',workflow_id:'mbd'},config:{id:'mbd',data:{}},library:{sources:[]}});
refreshStatus=async()=>{};
setView=()=>{};
closeSimulationCatalog=()=>{};
let createdOverview = null;
openSimulationOverview=async(id)=>{createdOverview=id;};
`,ctx);
(async()=>{await vm.runInContext("configureSimulationWorkflow('mbd')",ctx); assert.equal(vm.runInContext('createdOverview',ctx),'test'); console.log('Editor behavior checks passed');})().catch(e=>{console.error(e);process.exitCode=1});

vm.runInContext(`
state.activeTireTab='load-maps';
state.tirePayload={sides:[{side:'front'},{side:'rear'}]};
drawPreviewGrid=()=>{};
let fitCalls=[];
for (const name of ['pureLongitudinalLoadSurfaces','pureLateralLoadSurfaces','combinedFxSurfaces','combinedFySurfaces']) {
  globalThis[name]=(sides)=>{fitCalls.push({name,sides});return [{name}];};
}
let plotCalls=[];
drawTireSurfacePanel=(...args)=>{plotCalls.push(args);return {test:true};};
for (const axle of ['front','rear']) for (const slip of ['pure','combined']) for (const direction of ['longitudinal','lateral']) {
  state.activeTireAxle=axle; state.tireFitSlip=slip; state.tireFitDirection=direction;
  fitCalls=[]; plotCalls=[];
  drawTirePreview({},800,600,{});
  assert.equal(fitCalls.length,1); assert.equal(fitCalls[0].sides.length,1);
  assert.equal(fitCalls[0].sides[0].side,axle);
  const expected=slip==='pure' ? (direction==='lateral'?'pureLateralLoadSurfaces':'pureLongitudinalLoadSurfaces') : (direction==='lateral'?'combinedFySurfaces':'combinedFxSurfaces');
  assert.equal(fitCalls[0].name,expected);
  assert.equal(plotCalls.length,1); assert.equal(state.tireSurfaceScene.panels.length,1);
  assert.equal(plotCalls[0][3],768); assert.equal(plotCalls[0][4],568);
  assert.equal(plotCalls[0][9],direction==='lateral'?'Fy (N)':'Fx (N)');
}
`,ctx);

const momentCtx = vm.createContext({localStorage:{getItem:()=>null}, console, assert, document:{compatMode:"CSS1Compat",body:{classList:{toggle(){}}}}});
vm.runInContext(source, momentCtx);
vm.runInContext(`
currentTireCombinedFz=()=>150;
currentTireLoadCamberDeg=()=>1;
for (const output of ['mx','my','mz']) {
  const key=output+'_nm';
  const maps = [0,2].map(gamma=>({gamma_deg:gamma,maps:[100,200].map(load=>({fz_n:load,rows:[-4,4].map(alpha=>({alpha_deg:alpha,points:[-0.1,0.1].map(kappa=>({alpha_deg:alpha,kappa,fz_n:load,[key]:load+gamma+alpha+kappa}))}))}))}));
  const pure=[0,2].map(gamma=>({gamma_deg:gamma,rows:[100,200].map(load=>({fz_n:load,points:[-0.1,0.1].map(slip=>({alpha_deg:slip,kappa:slip,fz_n:load,[key]:load+gamma+slip}))}))}));
  for (const side of ['front','rear']) for (const combined of [false,true]) {
    const surface=tireMomentSurfaces([{side,curves:{moments:{[output]:pure},combined:{force_maps_by_gamma_fz:maps}}}],output,combined,canvasPalette())[0];
    assert.equal(surface.zKey,key);
    assert.equal(surface.xKey,output==='my'?'kappa':'alpha_deg');
    assert.equal(surface.yKey,combined?(output==='my'?'alpha_deg':'kappa'):'fz_n');
    for (const row of surface.rows) for (const point of row.points) {
      const expected=combined?151+point.alpha_deg+point.kappa:point.fz_n+1+point.kappa;
      assert.ok(Math.abs(point[key]-expected)<1e-10);
    }
  }
}
`, momentCtx);

vm.runInContext(`
const ellipseCalls=[];
drawPanel=()=>{}; drawCanvasText=()=>{}; drawTireForceMapLegend=()=>{};
drawTireFrictionEllipse=(...args)=>ellipseCalls.push(args);
tireSetupCorners=()=>['front','rear'].flatMap(axle=>['left','right'].map(side=>({axle,side,fxPeakN:500,fyPeakN:700,forceMapMaxN:700,fzN:400})));
for (const axle of ['front','rear']) {
  state.activeTireAxle=axle; ellipseCalls.length=0;
  drawTireStancePanel({},16,16,800,600,{});
  assert.equal(ellipseCalls.length,1);
  assert.equal(ellipseCalls[0][1].axle,axle);
  assert.equal(ellipseCalls[0][1].side,'left');
  assert.equal(ellipseCalls[0][4],240);
}
`,ctx);

vm.runInContext(`
const suspensionSelect={value:'front',addEventListener(t,fn){assert.equal(t,'change');this.change=fn;}};
const suspensionPanels=['front-spring','rear-spring'].map(key=>({dataset:{suspensionPanel:key}}));
document={querySelectorAll:q=>q==='[data-suspension-axle]'?[suspensionSelect]:q==='[data-suspension-panel]'?suspensionPanels:[]};
state.suspensionAxle='front'; state.suspensionComponent='spring';
wireSuspensionSelection(); suspensionSelect.value='rear'; suspensionSelect.change();
assert.equal(state.suspensionAxle,'rear');
assert.equal(suspensionPanels[0].hidden,true); assert.equal(suspensionPanels[1].hidden,false);
`,ctx);

vm.runInContext(`
state.activeParamGroup='mass';
assert.equal(isSpatialPreviewArea(),true);
const handlers={};
const massCanvas={clientLeft:0,clientTop:0,classList:{toggle(){},remove(){}},
  getBoundingClientRect:()=>({left:0,top:0,width:800,height:600}),
  setPointerCapture(){},addEventListener(name,fn){(handlers[name]||=[]).push(fn);}};
document={getElementById:()=>massCanvas,querySelectorAll:()=>[]};
window={addEventListener(){}};
drawVehicleFromForm=()=>{};
wireVehicleCanvas();
const event={pointerId:4,button:0,clientX:400,clientY:300,preventDefault(){}};
handlers.pointerdown[0](event);
assert.equal(state.vehicleDrag.mode,'rotate');
const oldYaw=state.vehiclePreviewYaw;
handlers.pointermove[0]({...event,clientX:440});
assert.notEqual(state.vehiclePreviewYaw,oldYaw);
handlers.pointerup[0](event);
handlers.pointerdown[0]({...event,ctrlKey:true});
assert.equal(state.vehicleDrag.mode,'pan');
handlers.pointermove[0]({...event,clientX:500,clientY:340});
assert.equal(state.vehiclePreviewPanX,100); assert.equal(state.vehiclePreviewPanY,40);
handlers.pointerup[0](event);
handlers.wheel[0]({...event,deltaY:-100});
assert.ok(state.vehiclePreviewZoom>1);
handlers.dblclick[0]();
assert.equal(state.vehiclePreviewZoom,1); assert.equal(state.vehiclePreviewPanX,0);
`,momentCtx);

vm.runInContext(`
for (const area of ['hardpoints','mass','aero','tires']) {
  state.activeParamGroup=area;
  state.aeroReferenceView=true;
  state.activeTireTab='load-maps';
  state.vehiclePreviewZoom=3; state.vehiclePreviewPanX=80; state.vehiclePreviewFit={key:'old'};
  state.tireSurfaceZoom=4; state.tireSurfacePanX=90;
  resetPreviewCamera();
  if(area==='tires') {
    assert.equal(state.tireSurfaceZoom,1); assert.equal(state.tireSurfacePanX,0);
  } else {
    assert.equal(state.vehiclePreviewZoom,1); assert.equal(state.vehiclePreviewPanX,0);
    assert.equal(state.vehiclePreviewFit,null); assert.equal(state.vehiclePreviewYaw,DEFAULT_VEHICLE_YAW);
  }
}
state.activeParamGroup='aero'; state.aeroReferenceView=false; state.tireSurfaceZoom=3;
resetPreviewCamera(); assert.equal(state.tireSurfaceZoom,1);
`,momentCtx);

vm.runInContext(`
{
  const originalDocument = document;
  const originalDraw = drawGeometryPlotPanel;
  const originalStorage = localStorage;
  const elements = {
    'geometry-plot-panel': {hidden:false},
    'geometry-plot-x-axis': {},
    'geometry-plot-y-axis': {},
    'geometry-add-plot-btn': {},
  };
  document = {getElementById:id=>elements[id]};
  localStorage = {setItem(){}};
  drawGeometryPlotPanel = () => {};
  state.kinematicsPayload = null;
  state.geometryPlotSelections = [];
  const choices = [...geometryPlotDescriptorMap().values()];
  assert.equal(choices.length,21);
  assert.ok(choices.every(item=>!/(migration|swing_arm|front_ic|rc_[yz])/.test(item.id)));
  for (const item of choices) {
    state.geometryPlotDraftX = item.x_id;
    state.geometryPlotDraftY = item.id;
    renderGeometryPlotControls();
    assert.equal(elements['geometry-add-plot-btn'].disabled,false);
    addGeometryPlotSelection();
    assert.equal(elements['geometry-add-plot-btn'].disabled,true);
  }
  assert.equal(cleanGeometryPlotSelections().size,21);
  assert.equal(state.geometryPlotSelections.length,21);
  removeGeometryPlotSelection('jounce_mm:bump_camber_deg');
  assert.equal(state.geometryPlotSelections.length,20);
  assert.ok(state.geometryPlotSelections.some(item=>item.y==='bump_toe_deg'));
  state.geometryPlotSelections = [{x:'steer_deg',y:'steer_camber_deg'}];
  cleanGeometryPlotSelections();
  assert.equal(state.geometryPlotSelections[0].x,'rack_mm');
  assert.equal(geometryXAxisOption('rack_mm').unit,'mm');
  document = originalDocument;
  localStorage = originalStorage;
  drawGeometryPlotPanel = originalDraw;
}
`, ctx);

vm.runInContext(`
{
  const originalDocument = document;
  const form = {dataset:{instance:'named:step'},innerHTML:'edited inputs'};
  document = {getElementById:()=>form};
  state.selectedSimulationId='named'; state.simConfigPayload={id:'step',fields:[]};
  state.dirtySimConfig=true;
  renderSimConfigForm();
  assert.equal(form.innerHTML,'edited inputs','background refresh must preserve unsaved fields');
  state.dirtySimConfig=false;
  document=originalDocument;
}
`,ctx);

vm.runInContext(`
{
  const originalDocument = document, originalSetView = setView;
  const replay = {dataset:{}};
  document = {getElementById:()=>replay};
  setView = view => { state.view = view; };
  openSimulationVisualization({id:'plot',kind:'report',run_id:'saved-run'});
  assert.equal(state.view,'studies');
  assert.equal(state.selectedResultId,'saved-run');
  assert.equal(state.selectedVisualizationId,'plot');
  openSimulationVisualization({id:'signals',kind:'signals',run_id:'signal-run'});
  assert.equal(state.view,'studies');
  assert.equal(state.selectedResultId,'signal-run');
  assert.equal(state.selectedVisualizationId,'signals');
  openSimulationVisualization({id:'animation',kind:'replay',run_id:'captured-scene'});
  assert.equal(state.view,'replay');
  assert.equal(replay.dataset.capture,'captured-scene');
  assert.equal(state.selectedVisualizationId,'animation');
  state.selectedSimulationId='new-analysis';
  openSimulationVisualization({id:'empty',kind:'replay',run_id:null});
  assert.equal(replay.dataset.capture,'pending:new-analysis','empty views must not show another analysis');
  document=originalDocument; setView=originalSetView;
}
`,ctx);

vm.runInContext(`
{
  const originalResults = savedResults;
  savedResults = () => [{id:'unrelated'}];
  state.selectedResultId='removed'; state.selectedVisualizationId='pinned-view';
  assert.equal(selectedSavedResult(),null,'a missing visualization source must not show another run');
  state.selectedVisualizationId=null;
  assert.equal(selectedSavedResult().id,'unrelated');
  savedResults=originalResults;
}
`,ctx);

vm.runInContext(`
{
  const originalDocument=document, originalStorage=localStorage;
  const handlers={}, attributes={}, properties={}, stored={};
  const splitter={addEventListener:(event,fn)=>handlers[event]=fn,setAttribute:(key,value)=>attributes[key]=value};
  const workspace={clientWidth:1000,style:{setProperty:(key,value)=>properties[key]=value}};
  document={getElementById:()=>splitter,querySelector:()=>workspace};
  localStorage={getItem:()=>null,setItem:(key,value)=>stored[key]=value};
  globalThis.ResizeObserver=class {constructor(callback){this.callback=callback;}observe(){this.callback();}};
  wireSimulationSplitter();
  assert.equal(attributes['aria-valuenow'],'230');
  handlers.keydown({key:'ArrowRight',preventDefault(){}});
  assert.equal(attributes['aria-valuenow'],'246');
  assert.equal(stored['bobsim-simulation-pane-width'],'246');
  handlers.keydown({key:'End',preventDefault(){}});
  assert.equal(attributes['aria-valuenow'],'560');
  handlers.keydown({key:'Home',preventDefault(){}});
  assert.equal(attributes['aria-valuenow'],'180');
  document=originalDocument;localStorage=originalStorage;
  delete globalThis.ResizeObserver;
}
`,ctx);

(async () => {
  const deletionContext=vm.createContext({localStorage:{getItem:()=>null},console,assert,document:{compatMode:"CSS1Compat",body:{classList:{toggle(){}}}}});
  vm.runInContext(source,deletionContext);
  await vm.runInContext(`
  (async () => {
    const originals={request:simulationRequest,render:renderSimulationWorkspace,view:setView};
    globalThis.window={confirm:()=>true};
    let deleted=null;
    simulationRequest=async (action,payload)=>{deleted=payload.id;};
    renderSimulationWorkspace=()=>{};
    setView=view=>{state.view=view;};
    state.simulationWorkspace={simulations:[{id:'editing',name:'Editing'},{id:'other',name:'Other'}]};
    state.selectedSimulationId='editing';state.dirtySimConfig=true;state.simModalOpen=true;
    await removeSimulation('other');
    assert.equal(deleted,'other');
    assert.equal(state.selectedSimulationId,'editing');
    assert.equal(state.dirtySimConfig,true,'deleting another simulation must preserve unsaved inputs');
    await removeSimulation('editing');
    assert.equal(state.selectedSimulationId,null);
    assert.equal(state.simModalOpen,false);
    assert.equal(state.view,'standard');
    simulationRequest=originals.request;renderSimulationWorkspace=originals.render;setView=originals.view;
    delete globalThis.window;
  })()
  `,deletionContext);
})().catch(error=>{console.error(error);process.exitCode=1;});

// Peak utilization may exceed the reference ellipse without leaving its cell.
{
  const arcs = [];
  const labels = [];
  const drawing = new Proxy({arc:(...args)=>arcs.push(args),fillText:text=>labels.push(text)}, {
    get:(target,key)=>key in target ? target[key] : ()=>{},
  });
  const canvas = {clientWidth:240,clientHeight:240,getContext:()=>drawing};
  const panel = vm.createContext({window:{devicePixelRatio:1},document:{compatMode:"CSS1Compat",readyState:'loading',body:{},
    addEventListener(){},getElementById:id=>id==='replay-tires-canvas'?canvas:{}},
    getComputedStyle:()=>({getPropertyValue:()=>''})});
  const panelSource = fs.readFileSync('app/static/visual_panel.js','utf8').replace(
    '  function bootstrap() {',
    '  window.testTires = scene => { state.scene=scene; state.tab="tires"; renderFrictionCircles(0); };\n  function bootstrap() {'
  );
  vm.runInContext(panelSource,panel);
  panel.window.testTires({header:{grip:{corners:['fl','fr','rl','rr'].map((corner,i)=>({
    corner,slot_x:i*4,slot_y:i*4+1,slot_usage:i*4+2,slot_airborne:i*4+3,
  }))}},scalar:slot=>[2,3,3.6,0,-4,1,4.1,0,0,0,0,0,0,0,0,1][slot]});
  const dots=arcs.filter(arc=>arc[2]===5);
  assert.equal(dots.length,3);
  dots.forEach(([x,y],i)=>{
    assert.ok(x>=(i%2)*120+5&&x<=(i%2+1)*120-5);
    assert.ok(y>=Math.floor(i/2)*120+5&&y<=(Math.floor(i/2)+1)*120-5);
  });
  assert.ok(labels.includes('410% of peak'));
}
{
  const plotContext=vm.createContext({localStorage:{getItem:()=>null},console,assert,document:{compatMode:"CSS1Compat",body:{classList:{toggle(){}}}}});
  vm.runInContext(source,plotContext);
  vm.runInContext(`
    const fills=[];
    const pen=new Proxy({fillRect:(...args)=>fills.push(args)}, {get:(target,key)=>key in target?target[key]:()=>{}});
    const legend={innerHTML:''};
    const canvas={getBoundingClientRect:()=>({width:800,height:400,left:0,top:0}),getContext:()=>pen,focus(){}};
    document={getElementById:id=>id==='result-plot-canvas'?canvas:id==='result-selected-signals'?legend:{}};
    window={devicePixelRatio:1};
    canvasPalette=()=>({surface:'#000',blue:'#00f',green:'#0f0'});
    let limits;
    drawPlotGrid=(_ctx,chart)=>{limits=chart;};
    drawCanvasText=()=>{};
    selectedResultSource=()=>null;
    state.resultPlotStatus='ready';state.resultXAxis='time';
    state.resultPlotPayload={x:[0,1,2],series:[{signal:'small',values:[-1,0,2]},{signal:'large',values:[-1000,null,2000]}]};
    drawResultPlotCanvas();
    assert.ok(limits.yDomain[0]<-1000&&limits.yDomain[1]>2000);
    assert.ok(legend.innerHTML.includes('small')&&legend.innerHTML.includes('large'));
    assert.equal(fills.length,1,'the legend must not paint over the plot');
    state.resultBaselinePayload={x:[-5,7],series:[{signal:'small',values:[-3000,4000]}]};
    drawResultPlotCanvas();
    assert.ok(limits.xDomain[0]<-5 && limits.xDomain[1]>7);
    assert.ok(limits.yDomain[0]<-3000 && limits.yDomain[1]>4000);
    assert.ok(legend.innerHTML.includes('Baseline: small'));
    state.resultBaselinePayload={x:[0,1],series:[{signal:'large',values:[2,3]}]};
    drawResultPlotCanvas();
    assert.equal(pen.strokeStyle,'#0f0','baseline must match the same signal color even when earlier signals are missing');
    assert.ok(legend.innerHTML.includes('background:#0f0"></i>Baseline: large'));
    state.resultPlotStatus='error';
    drawResultPlotCanvas();
    assert.equal(legend.innerHTML,'','failed source must not leave the previous legend');
    assert.equal(canvas.onclick,null,'failed source must not retain a sample handler');
    state.resultPlotStatus='ready'; state.resultBaselinePayload=null;
    const segments=[],strokes=[];
    pen.lineTo=(...point)=>segments.push(point);
    pen.stroke=()=>strokes.push(pen.strokeStyle);
    state.resultPlotPayload={x:[0,1,2,3,4],series:[{signal:'y',values:[0,1,2,3,4]}],color:{signal:'speed',values:[0,1,null,3,4]}};
    drawResultPlotCanvas();
    assert.equal(segments.length,2,'missing color must break the line');
    assert.notEqual(strokes[0],strokes[1]);
    assert.ok(legend.innerHTML.includes('speed'));
    assert.equal(resultSignalColor(5,[5,5]),resultSignalColor(.5,[0,1]));
    state.selectedResultId='selected-run'; state.selectedResultSourcePath='run.csv';
    state.resultPlotPayload.coordinates={time:[0,1,2,3,4]};
    state.resultBaselinePayload={x:[-1,10],series:[{signal:'y',values:[-1,10]}],coordinates:{time:[99,100]}};
    renderResultPlotCanvas=()=>{};
    drawResultPlotCanvas();
    canvas.onclick({clientX:100,clientY:100});
    assert.ok(readResultCursor('selected-run').time<=4,'baseline coordinates must not become selected-run time');
    state.resultBaselinePayload=null;
    state.resultHoverIndex=null;
    state.resultPlotPayload.color=null;
    state.resultBaselinePayload={x:[0,1],series:[{signal:'y',values:[0,1]}],color:{signal:'speed',values:[1,2]}};
    drawResultPlotCanvas();
    assert.ok(legend.innerHTML.includes('speed'),'baseline-only color must not crash the legend');
    state.resultBaselinePayload=null;
    isLapMap=()=>true;
    drawResultPlotCanvas();
    assert.ok(Math.abs((limits.xDomain[1]-limits.xDomain[0])/limits.plot.width
      -(limits.yDomain[1]-limits.yDomain[0])/limits.plot.height)<1e-9,'lap coordinates must have equal scale');
  `,plotContext);
}

{
  const cursorContext = vm.createContext({localStorage:{getItem:()=>null},console,assert,document:{compatMode:"CSS1Compat",body:{classList:{toggle(){}}}}});
  vm.runInContext(source, cursorContext);
  vm.runInContext(`
    state.selectedResultId='run-a'; state.selectedResultSourcePath='a.csv';
    const payload={coordinates:{time:[0,1,2],station_m:[0,10,20]},row_indices:[0,4,8]};
    selectResultSample(payload,1);
    assert.equal(readResultCursor('run-a').time,1);
    assert.equal(readResultCursor('run-b'),null,'a new run must not inherit the selection');
    assert.equal(resultCursorIndex({coordinates:{time:[0,.9,1.8]}},'run-a','other.csv'),1);
    assert.equal(resultCursorIndex({coordinates:{station_m:[0,9,18]}},'run-a','lap.csv'),1);
    assert.equal(resultCursorIndex({row_indices:[0,3,6]},'run-a','a.csv'),1);
    assert.equal(resultCursorIndex({row_indices:[0,3,6]},'run-a','other.csv'),null);
    setResultCursor('run-a',{time:1.9});
    assert.equal(resultCursorIndex(payload,'run-a','a.csv'),2,'replay time maps to the nearest plotted sample');
    assert.equal(resultCursorIndex({coordinates:{time:[null,NaN]}},'run-a','a.csv'),null);
  `,cursorContext);
  const panelSource=fs.readFileSync('app/static/visual_panel.js','utf8');
  const restore=panelSource.slice(panelSource.indexOf('  function cursorRunId()'),panelSource.indexOf('  function syncTimeline('));
  const replay={runId:'saved-2026-run-a',runs:[{id:'saved-2026-run-a',data:'app/user_data/results/saved/2026-run-a/files/signals.csv'}, {id:'saved-2026-capture',data:'visualization/results/saved-2026-capture.npz'}],scene:{time:[2,3,4]},viewer:{simTime:2,playing:true}};
  const play={textContent:'Pause'};
  const replayContext=vm.createContext({state:replay,window:{readResultCursor:id=>id==='2026-run-a'?{time:3.2}:null},$:()=>play});
  vm.runInContext(restore+'; restoreResultCursor();',replayContext);
  assert.equal(replay.viewer.simTime,3.2);
  assert.equal(replay.viewer.playing,false);
  assert.equal(play.textContent,'Play');
  assert.equal(vm.runInContext('cursorRunId()',replayContext),'2026-run-a');
  replay.runId='saved-2026-capture';
  assert.equal(vm.runInContext('cursorRunId()',replayContext),null,'captured scenes must not collide with archived run IDs');
  replay.runId='run-b'; replay.viewer.simTime=2;
  vm.runInContext('restoreResultCursor()',replayContext);
  assert.equal(replay.viewer.simTime,2,'unrelated replay retains its own start');
}

(async () => {
  const simulationContext = vm.createContext({localStorage:{getItem:()=>null},console,assert,
    document:{compatMode:"CSS1Compat",body:{classList:{toggle(){}}}}});
  vm.runInContext(source, simulationContext);
  await vm.runInContext(`(async () => {
    for (const [id, group] of [['four-post','kinematic'], ['steady-state','steady-state'],
      ['ggv','steady-state'], ['ymd','steady-state'], ['lap-qss','steady-state'],
      ['reduced-ramp-steer','transient'], ['mbd-step-steer','transient'],
      ['transient','transient'], ['lap-transient','transient']]) {
      assert.equal(simulationAnalysisGroup({id}), group);
    }
    const configRequests=[];
    state.status={workflows:[{id:'ggv',group:'envelope',config_id:'ggv'}]};
    state.dirtySimConfig=true;
    api=async path=>{configRequests.push(path);return {id:'ggv',data:{generation:{model_dof:3}}};};
    await refreshSelectedSimConfig();
    assert.deepEqual(configRequests,['/api/configs/ggv'],'simulation setup loads without a preset library');
    assert.equal(state.simConfigPayload.id,'ggv');
    assert.equal(state.dirtySimConfig,false);
    assert.equal(state.loadingSimConfigFor,null);
    let requests=[];
    api=async (path, options)=>{
      assert.equal(options,undefined,'reopening a running simulation must be read-only');
      requests.push(path);
      return {jobs:[{id:'job',simulation:{id:'ggv-test'},workflow_id:'ggv',status:'running'}]};
    };
    simulationRequest=()=>{throw new Error('Must not reload the locked workspace');};
    refreshSelectedSimConfig=async()=>{};
    refreshStatus=async()=>{};
    setView=view=>{state.view=view;};
    const runLogMenu={open:false};
    document.getElementById=()=>runLogMenu;
    await openSimulation('ggv-test');
    assert.equal(state.selectedSimulationId,'ggv-test');
    assert.equal(state.selectedJobId,'job');
    assert.equal(runLogMenu.open,true);
    assert.equal(state.simModalOpen,true);
    assert.equal(state.view,'standard');
    assert.deepEqual(requests,['/api/jobs']);

    const elements={};
    document.getElementById=id=>elements[id] ||= {options:[]};
    activeVehicleKey=()=> 'vehicle';
    savedResults=()=>[{id:'result',created_label:'Today',simulation:{id:'ggv-test'},files:[{kind:'csv'}]}];
    state.simulationWorkspace={simulations:[{id:'ggv-test',workflow_id:'ggv'}]};
    api=()=>{throw new Error('An envelope must not request replay captures');};
    await addSimulationVisualization('ggv-test');
    assert.doesNotMatch(elements['simulation-visualization-kind'].innerHTML,/report/);
    assert.match(elements['simulation-visualization-kind'].innerHTML,/Signal explorer/);
    assert.doesNotMatch(elements['simulation-visualization-kind'].innerHTML,/3D replay/);
    assert.equal(elements['simulation-visualization-name'].value,'Signal explorer');
    elements['simulation-visualization-kind'].value='signals';
    elements['simulation-visualization-kind'].onchange();
    assert.equal(elements['simulation-visualization-name'].value,'Signal explorer');
  })()`, simulationContext);
})().catch(error=>{console.error(error);process.exitCode=1;});

{
  const treeContext=vm.createContext({localStorage:{getItem:()=>null},console,assert,document:{compatMode:"CSS1Compat",body:{classList:{toggle(){}}}}});
  vm.runInContext(source,treeContext);
  vm.runInContext(`
    const elements={};
    document={getElementById:id=>elements[id] ||= {
      classList:{toggle(){}},setAttribute(){},querySelector(){return {};}
    }};
    drawSimulationGgvConnections=()=>{};
    activeVehicleKey=()=> 'car'; activeVehicleName=()=> 'Car';
    savedResults=()=> [{id:'ggv-run',vehicle_key:'car',simulation:{id:'ggv'},created_label:'Today'}];
    state.simulationWorkspace={vehicle_key:'car',simulations:[
      {id:'lap',workflow_id:'lap-qss',name:'QSS lap'},
      {id:'step',workflow_id:'reduced-step-steer',name:'Step steer',visualizations:[{id:'plot',kind:'signals',name:'Signals'},{id:'legacy-report',kind:'report',name:'Old report'}]},
      {id:'ggv',workflow_id:'ggv',name:'GGV'},
      {id:'rig',workflow_id:'four-post',name:'Rig'}
    ]};
    renderSimulationWorkspace();
    const html=elements['simulation-tree'].innerHTML;
    const group=id=>html.split('data-analysis-group="'+id+'"')[1].split('</section>')[0];
    assert.match(group('steady-state'),/data-simulation-branch="ggv"/);
    assert.match(html,/draggable="true" data-ggv-source="ggv"/);
    assert.equal((html.match(/draggable="true"/g)||[]).length,1);
    assert.match(html,/simulation-drag-grip/);
    assert.equal(html.split('>Results</span>').length-1,4,'every simulation has Results');
    assert.match(html,/data-simulation-run="" data-owner="step" aria-haspopup="menu" disabled/);
    assert.match(html,/data-simulation-run="ggv-run" data-owner="ggv" aria-haspopup="menu" draggable/);
    assert.match(html,/data-simulation-toggle="results:step"/);
    assert.doesNotMatch(html,/data-simulation-visualization="legacy-report"/);
    assert.ok(html.indexOf('data-simulation-toggle="results:step"') < html.indexOf('data-simulation-visualization="plot"'));
    assert.match(html,/ggv-link-empty/);
    assert.ok(html.includes('>Link GGV</span>'));
    assert.match(group('steady-state'),/data-simulation-branch="lap"/);
    assert.doesNotMatch(group('steady-state'),/data-simulation-branch="step"/);
    assert.match(group('transient'),/data-simulation-branch="step"/);
    assert.match(group('transient'),/data-simulation-visualization="plot" data-owner="step"/);
    assert.match(group('kinematic'),/data-simulation-branch="rig"/);
    assert.doesNotMatch(html,/data-analysis-overview/);
    assert.ok(html.includes('<span class="simulation-tree-item simulation-analysis-label">Steady state</span>'));
    assert.doesNotMatch(html,/data-simulation-add-child/);
    assert.match(html,/data-simulation-results="ggv"/);
    assert.match(html,/data-simulation-id="lap" data-simulation-overview="lap"/);
    state.simulationWorkspace.simulations[0].ggv_source_id='ggv';
    state.simulationWorkspace.simulations[0].ggv_input={name:'GGV',status:'Ready'};
    renderSimulationWorkspace();
    assert.doesNotMatch(elements['simulation-tree'].innerHTML,/ggv-link-empty/);
    assert.match(elements['simulation-tree'].innerHTML,/GGV → GGV/);
    assert.match(elements['simulation-tree'].innerHTML,/ggv-link-supplied/);
    assert.match(elements['simulation-tree'].innerHTML,/data-ggv-linked="ggv"/);
    state.collapsedSimulations.add('group:transient');
    renderSimulationWorkspace();
    assert.match(elements['simulation-tree'].innerHTML,/data-simulation-toggle="group:transient" aria-expanded="false"/);
    state.simulationWorkspace={vehicle_key:'car',simulations:[],analysis_groups:['steady-state']};
    renderSimulationWorkspace();
    assert.match(elements['simulation-tree'].innerHTML,/data-analysis-group="steady-state"/);
    assert.match(elements['simulation-tree'].innerHTML,/data-analysis-group="kinematic"/);
    assert.match(elements['simulation-tree'].innerHTML,/data-analysis-group="transient"/);
  `,treeContext);
}

{
  const menuContext=vm.createContext({localStorage:{getItem:()=>null},console,assert,document:{compatMode:"CSS1Compat",body:{classList:{toggle(){}}}}});
  vm.runInContext(source,menuContext);
  vm.runInContext(`
    const events={}; let focused, added;
    const buttons=['add','duplicate','replay','signals','delete'].map(action=>({
      dataset:{action},hidden:false,focus(){focused=action;}
    }));
    const menu={hidden:true,style:{},offsetWidth:200,offsetHeight:180,
      querySelectorAll:()=>buttons,
      querySelector:selector=>selector==='button:not([hidden]):not([disabled])' ? buttons.find(b=>!b.hidden&&!b.disabled)
        : buttons.find(b=>selector.includes('"'+b.dataset.action+'"')),
      addEventListener:(name,fn)=>events['menu:'+name]=fn
    };
    const trigger={setAttribute(){},focus(){}};
    document={getElementById:id=>id==='simulation-context-menu' ? menu : {
      addEventListener:(name,fn)=>events['tree:'+name]=fn
    },addEventListener(){},querySelector:()=>({addEventListener(){}})};
    window={innerWidth:1000,innerHeight:800,addEventListener(){}};
    workspaceAction=fn=>fn(); showSimulationCatalog=id=>{added=id;};
    state.simulationWorkspace={simulations:[{id:'envelope',workflow_id:'ggv'},{id:'maneuver',workflow_id:'reduced-step-steer'},{id:'lap',workflow_id:'lap-qss'}]};
    wireSimulationContextMenu();
    const rightClick=(group,id)=>events['tree:contextmenu']({clientX:40,clientY:50,preventDefault(){},target:{
      closest:selector=>selector==='[data-simulation-results]' || selector==='.simulation-tree-runs' ? null : selector==='[data-simulation-branch]' ? (id ? {dataset:{simulationBranch:id},querySelector:()=>trigger} : null)
        : {dataset:{analysisGroup:group},querySelector:()=>trigger}
    }});
    for (const group of ['kinematic','steady-state','transient']) {
      rightClick('transient','maneuver');
      assert.equal(menu.hidden,false);
      rightClick(group);
      assert.equal(menu.hidden,false);
      assert.deepEqual(buttons.filter(b=>!b.hidden).map(b=>b.dataset.action),['add']);
      events['menu:click']({target:{closest:()=>buttons[0]}});
      assert.equal(added,group);
      assert.equal(menu.hidden,true);
    }
    rightClick('steady-state','envelope');
    assert.equal(focused,'duplicate');
    assert.deepEqual(buttons.filter(b=>!b.hidden).map(b=>b.dataset.action),['duplicate','delete']);
    const resultsClick=id=>events['tree:contextmenu']({clientX:40,clientY:50,preventDefault(){},target:{
      closest:selector=>selector==='[data-simulation-results]' ? {dataset:{simulationResults:id},querySelector:()=>trigger} : null
    }});
    resultsClick('envelope');
    assert.deepEqual(buttons.filter(b=>!b.hidden).map(b=>b.dataset.action),['replay','signals']);
    assert.equal(buttons.find(b=>b.dataset.action==='replay').disabled,true);
    assert.match(buttons.find(b=>b.dataset.action==='replay').title,/steady-state/);
    resultsClick('maneuver');
    assert.equal(buttons.find(b=>b.dataset.action==='replay').disabled,false);
    events['tree:contextmenu']({preventDefault(){},target:{closest:selector=>selector==='.simulation-tree-runs' ? {} : null}});
    assert.equal(menu.hidden,true,'simulation children have no context menu');
  `,menuContext);
}

(async () => {
  const dragContext=vm.createContext({localStorage:{getItem:()=>null},console,assert,document:{compatMode:"CSS1Compat",body:{classList:{toggle(){}}}}});
  vm.runInContext(source,dragContext);
  await vm.runInContext(`(async () => {
    const events={}, requests=[]; let action, opened, saved=false, highlighted=false;
    const lap={dataset:{simulationBranch:'lap'},classList:{
      add(){highlighted=true;},remove(){highlighted=false;}
    }};
    const tree={addEventListener:(name,fn)=>events[name]=fn,
      querySelectorAll:()=>[lap],contains:()=>false};
    document={getElementById:()=>tree};
    state.simulationWorkspace={simulations:[{id:'lap',workflow_id:'lap-qss'},{id:'ggv',workflow_id:'ggv'}]};
    workspaceAction=fn=>{action=fn();};
    saveSimulationEdits=async()=>{saved=true;};
    simulationRequest=async(...args)=>{assert.ok(saved);requests.push(args);};
    openSimulationGgv=async id=>{opened=id;};
    wireSimulationGgvDrag();
    const transfer={setData(type,value){assert.equal(type,'text/plain');assert.equal(value,'ggv');}};
    const start=()=>events.dragstart({target:{closest:()=>({dataset:{ggvSource:'ggv'}})},dataTransfer:transfer});
    const drop={target:{closest:()=>lap},dataTransfer:transfer,preventDefault(){this.accepted=true;}};
    events.dragover(drop); assert.equal(drop.accepted,undefined);
    start(); assert.equal(transfer.effectAllowed,'link');
    events.dragover(drop); assert.equal(drop.accepted,true); assert.equal(highlighted,true);
    assert.equal(transfer.dropEffect,'link');
    events.drop(drop); await action;
    assert.deepEqual(requests,[['set-ggv',{id:'lap',source_id:'ggv'}]]);
    assert.equal(opened,'lap'); assert.equal(highlighted,false);
    start(); events.dragend(); events.drop(drop); assert.equal(requests.length,1);
    start(); lap.dataset.simulationBranch='ggv';
    const invalid={...drop,accepted:false}; events.dragover(invalid); events.drop(invalid);
    assert.equal(invalid.accepted,false); assert.equal(requests.length,1);
  })()`,dragContext);
})().catch(error=>{console.error(error);process.exitCode=1;});

{
  const connectionContext=vm.createContext({localStorage:{getItem:()=>null},console,assert,document:{compatMode:"CSS1Compat",body:{classList:{toggle(){}}}}});
  vm.runInContext(source,connectionContext);
  vm.runInContext(`
    let width=240, sourceVisible=true, titleVisible=true;
    const rect=top=>({right:width-24,top,height:28});
    const sourceNode={dataset:{ggvSource:'ggv'},getClientRects:()=>sourceVisible?[1]:[],getBoundingClientRect:()=>rect(100)};
    const title={dataset:{simulationId:'ggv'},getClientRects:()=>titleVisible?[1]:[],getBoundingClientRect:()=>rect(40)};
    const input={dataset:{ggvLinked:'ggv',simulationGgv:'lap'},getClientRects:()=>[1],getBoundingClientRect:()=>rect(220)};
    const svg={setAttribute(){},innerHTML:''};
    const tree={getBoundingClientRect:()=>({left:0,top:20,width,height:400}),
      querySelectorAll:selector=>selector==='[data-ggv-source]'?[sourceNode]:selector==='[data-simulation-id]'?[title]:[input]};
    document={getElementById:id=>id==='simulation-tree'?tree:svg};
    drawSimulationGgvConnections(); assert.ok(svg.innerHTML.includes('M216 94H232V214H216'));
    width=300; drawSimulationGgvConnections(); assert.ok(svg.innerHTML.includes('M276 94H292V214H276'));
    sourceVisible=false; drawSimulationGgvConnections(); assert.ok(svg.innerHTML.includes('M276 34H292V214H276'));
    titleVisible=false; drawSimulationGgvConnections(); assert.equal(svg.innerHTML,'');
  `,connectionContext);
}

(async () => {
  const overviewContext=vm.createContext({localStorage:{getItem:()=>null},console,assert,
    document:{compatMode:"CSS1Compat",body:{classList:{toggle(){}}}}});
  vm.runInContext(source,overviewContext);
  await vm.runInContext(`(async()=>{
    const controls={};
    const panel={hidden:true,innerHTML:'',querySelector:key=>controls[key] ||= {},querySelectorAll:()=>[]};
    document.getElementById=()=>panel;
    state.simulationWorkspace={vehicle_key:'car',analysis_groups:['steady-state'],simulations:[
      {id:'ggv',workflow_id:'ggv',name:'Envelope <A>',model:{engine:'DynPy <test>',fidelity:'6 DOF'}},
      {id:'step',workflow_id:'reduced-step-steer',name:'Step steer'}
    ]};
    activeVehicleKey=()=> 'car';
    savedResults=()=>[{id:'run',vehicle_key:'car',simulation:{id:'ggv'},created_label:'2026-10-15'}];
    let saves=0;
    saveSimulationEdits=async()=>{saves++;};
    api=()=>{throw new Error('Overview must not load config or start a job');};
    simulationRequest=api;
    setView=view=>{state.view=view;};
    workspaceAction=fn=>fn();
    simulationVisualHtml=()=>'<div class="existing-visual"></div>';

    await openSimulationOverview('ggv');
    assert.equal(saves,1);
    assert.equal(state.simModalOpen,false);
    assert.equal(state.simulationOverview.id,'ggv');
    assert.equal(renderSimulationOverview(),true);
    assert.match(panel.innerHTML,/Envelope &lt;A&gt;/);
    assert.doesNotMatch(panel.innerHTML,/2026-10-15|<dt>Results<|<dt>Model</);
    assert.match(panel.innerHTML,/simulation-diagram/);
    assert.doesNotMatch(panel.innerHTML, /<button|data-overview-setup|data-overview-view/);
    state.simModalOpen=true;
    assert.equal(renderSimulationOverview(),false);
    assert.equal(panel.hidden,true);
  })()`,overviewContext);
})().catch(error=>{console.error(error);process.exitCode=1;});

vm.runInContext(`
{
  const button = {classList:{toggle(){}},setAttribute(){}};
  setActionButton(button, {label:'Run',disabled:true,title:'The saved vehicle has changed.'});
  assert.equal(button.disabled,true);
  assert.equal(button.title,'The saved vehicle has changed.');
  setActionButton(button, {label:'Run',busy:true,busyLabel:'Running'});
  assert.equal(button.disabled,true);
  assert.equal(button.title,'Running in progress.');
  setActionButton(button, {label:'Run'});
  assert.equal(button.disabled,false);
  assert.equal(button.title,'');
}
`, ctx);

vm.runInContext(`
for (const [value, scale, display, edited, expected] of [
  [0.03,1000,30,40,0.04],
  [0.01308996938995747,180/Math.PI,0.75,1,Math.PI/180],
  [Math.PI/6,180/Math.PI,30,45,Math.PI/4],
]) {
  assert.equal(numericDisplayValue(value,scale),display);
  const input={value:String(display),dataset:{displayScale:String(scale),originalValue:String(value),originalDisplay:String(display)},
    setCustomValidity(){},checkValidity(){return true;}};
  assert.equal(collectScalarValue(input,'number',false),value);
  input.value=String(edited);
  assert.ok(Math.abs(collectScalarValue(input,'number',false)-expected)<1e-12);
}
`, ctx);

(async () => {
  const context=vm.createContext({localStorage:{getItem:()=>null},console,assert,document:{compatMode:'CSS1Compat',body:{classList:{toggle(){}}}}});
  vm.runInContext(source,context);
  await vm.runInContext(`(async()=>{
    const elements={};
    document.getElementById=id=>elements[id] ||= {open:true,textContent:'',scrollHeight:100,scrollTop:0,clientHeight:100,classList:{toggle(){}},querySelectorAll:()=>[]};
    state.selectedSimulationId='other-sim';
    state.view='standard';
    state.status={jobs:[{id:'done',label:'Completed',status:'completed',argv:[]},
      {id:'active',label:'GGV',status:'running',argv:[],simulation:{id:'ggv',name:'Envelope'}}]};
    const originalLoad=loadJobLog;
    let logLoads=0; loadJobLog=()=>{logLoads++;};
    renderRunLog();
    assert.equal(state.selectedJobId,'active');
    assert.match(elements['job-list'].innerHTML,/Completed/);
    assert.match(elements['job-list'].innerHTML,/Envelope/);
    assert.equal(elements['run-status'].textContent,'GGV · running');
    elements['run-log-menu'].open=false;
    renderRunLog();
    assert.equal(logLoads,1,'closed log does not fetch job output');
    elements['run-log-menu'].open=true;state.view='setup';renderRunLog();
    assert.equal(logLoads,1,'vehicle Setup does not fetch hidden logs');
    state.view='standard';
    state.status.jobs=[]; elements['run-log-menu'].open=true;
    renderRunLog();
    assert.equal(elements['run-status'].textContent,'');
    assert.match(elements['job-list'].innerHTML,/No jobs yet/);
    loadJobLog=originalLoad;
    let resolve;
    api=()=>new Promise(done=>{resolve=done;});
    state.selectedJobId='old';
    const pending=loadJobLog();
    state.selectedJobId='new';
    elements['job-log'].textContent='new output';
    resolve({log:'stale output'});await pending;
    assert.equal(elements['job-log'].textContent,'new output','late logs cannot replace a different job');
    api=async()=>({log:'updated output'});
    elements['job-log'].scrollHeight=1000; elements['job-log'].scrollTop=100;
    await loadJobLog();assert.equal(elements['job-log'].scrollTop,100,'reading position survives refresh');
    const saves=[];
    state.simulationWorkspace={simulations:[{id:'sim',name:'Original'}]};
    simulationRequest=async(action,values)=>saves.push({action,...values});
    renderSimulationWorkspace=()=>{};
    await renameSimulation('sim','  Changed  ');
    await renameSimulation('sim','  ');
    await renameSimulation('sim','Original');
    assert.deepEqual(saves,[{action:'rename',id:'sim',name:'Changed'}]);
  })()`,context);
})().catch(error=>{console.error(error);process.exitCode=1;});
