const assert=require('node:assert/strict');
const M=require('../app/static/report_metrics.js');
const copy=value=>JSON.parse(JSON.stringify(value));
function metric(title,view,count) {
  return {title:`${title} vs ${view}`,layout:['','single','dual','triple','quad'][count],subplots:Array.from({length:count},(_,i)=>({title:['Front Left','Front Right','Rear Left','Rear Right'][i],x:{key:view,label:`${view} (mm)`},y:{key:`${title}_${view}_${i}`,scale:i%2?1:-1,label:`${title} (deg)`}}))};
}
const definitions={camber_heave:metric('Camber','Heave',4),camber_roll:metric('Camber','Roll',4),toe_roll:metric('Toe','Roll',4),rc:metric('RC height','Roll',2),single:metric('Balance','Roll',1)};
const signals=Object.values(definitions).flatMap(page=>page.subplots.flatMap(sub=>[sub.x,sub.y])).map(({key})=>({key}));
const catalog=M.catalog(definitions,signals);
assert.equal(catalog.length,5);
assert.equal(M.catalog(definitions,[]).length,0);
const page=copy(definitions.camber_heave);M.initialize(page,catalog);
assert.equal(M.group(page,3).length,4);
M.apply(page,2,catalog[1]);
assert.ok(page.subplots.every(sub=>sub.x.key==='Roll'));
assert.deepEqual(page.subplots.map(sub=>sub.y.scale),[-1,1,-1,1]);
M.apply(page,3,catalog[2]);assert.ok(page.subplots.every(sub=>sub.y.key.startsWith('Toe_Roll')));
// Smaller metric occupies only available values; remaining slots are a separate group.
M.apply(page,0,catalog[3]);assert.equal(M.group(page,0).length,2);assert.equal(M.group(page,3).length,2);
const triple={layout:'triple',subplots:[...copy(page.subplots.slice(0,2)),{...copy(definitions.single.subplots[0]),_metric_group:'single',_metric_source:'single',_metric_member:0}]};
M.apply(triple,2,catalog[4]);assert.equal(M.group(triple,0).length,2);assert.equal(M.group(triple,2).length,1);assert.equal(triple.subplots[0].y.key,'RC height_Roll_0');
// An independent rear corner stays rear when changing its sweep.
const rear={layout:'single',...copy(definitions.camber_heave.subplots[3]),_metric_group:'rear',_metric_source:'camber_heave',_metric_member:3};
delete rear._metric_group;delete rear._metric_source;delete rear._metric_member;M.initialize(rear,catalog);assert.equal(rear._metric_member,3);
M.apply(rear,0,catalog[1]);assert.equal(rear.y.key,'Camber_Roll_3');
console.log('Metric catalogs, shared axes, sign conventions, mixed groups and corner identity passed');
