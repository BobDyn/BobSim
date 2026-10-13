const fs = require('node:fs');
const vm = require('node:vm');
const assert = require('node:assert/strict');
const source = fs.readFileSync('app/static/app.js', 'utf8').split('\nwireEvents();')[0];
const ctx = vm.createContext({localStorage:{getItem:()=>null}, console, assert, document:{body:{classList:{toggle(){}}}}});
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
simulationRequest=async()=>({simulation:{id:'test',workflow_id:'mbd'},config:{id:'mbd',data:{}},library:{sources:[]}});
refreshStatus=async()=>{};
setView=()=>{};
`,ctx);
(async()=>{await vm.runInContext("configureSimulationWorkflow('mbd')",ctx); assert.equal(vm.runInContext('state.simModalOpen',ctx),true); console.log('Editor behavior checks passed');})().catch(e=>{console.error(e);process.exitCode=1});

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

const momentCtx = vm.createContext({localStorage:{getItem:()=>null}, console, assert, document:{body:{classList:{toggle(){}}}}});
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
  const deletionContext=vm.createContext({localStorage:{getItem:()=>null},console,assert,document:{body:{classList:{toggle(){}}}}});
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
