/* Metric views retain the calibrated signal pairing and corner sign conventions. */
(function(root) {
  const copy=value=>JSON.parse(JSON.stringify(value));
  const panels=page=>page.subplots || [page];
  const name=label=>(label || '').replace(/\s*[([][^()[\]]+[)\]]\s*$/, '').trim();
  function catalog(definitions, signals) {
    const available=new Set(signals.map(signal=>signal.key));
    return Object.entries(definitions).flatMap(([id,page])=>{
      const subs=panels(page);
      if(!subs.every(sub=>available.has(sub.x?.key) && available.has(sub.y?.key))) return [];
      const metric=(page.title || id).split(/\s+vs\.?\s+/i)[0];
      const view=[...new Set(subs.map(sub=>name(sub.x.label || sub.x.key)))].join(' / ');
      return [{id,metric,view,count:subs.length,subplots:copy(subs)}];
    });
  }
  function initialize(page, catalog) {
    const subs=panels(page);
    if(subs.every(sub=>sub._metric_group)) return;
    let group=0;
    for(let i=0;i<subs.length;) {
      const match=catalog.find(item=>item.subplots.some(sub=>sub.x.key===subs[i].x?.key && sub.y.key===subs[i].y?.key));
      const first=match?.subplots.findIndex(sub=>sub.x.key===subs[i].x?.key && sub.y.key===subs[i].y?.key) || 0;
      let count=1;
      if(match) while(first+count<match.count && i+count<subs.length &&
        subs[i+count].x?.key===match.subplots[first+count].x.key && subs[i+count].y?.key===match.subplots[first+count].y.key) count++;
      for(let n=0;n<count;n++) Object.assign(subs[i+n],{_metric_group:`group-${group}`, _metric_source:match?.id || '',_metric_member:first+n});
      i+=count;group++;
    }
  }
  function group(page,index) {
    const subs=panels(page), selected=subs[index];
    return subs.map((sub,i)=>({sub,i})).filter(item=>item.sub._metric_group===selected._metric_group);
  }
  function apply(page,index,view) {
    const subs=panels(page), members=group(page,index), first=members[0].i;
    const count=Math.min(view.count,members.length);
    const groupId=members[0].sub._metric_group;
    for(let n=0;n<members.length;n++) {
      const slot=members[n].i;
      if(n<count) {
        const previous=members[n].sub;
        const matched=view.subplots.findIndex(sub=>sub.title===previous.title);
        const member=count<view.count && matched>=0 ? matched : n;
        const replacement=copy(view.subplots[member]);
        Object.assign(replacement,{_metric_group:groupId,_metric_source:view.id,_metric_member:member});
        if(page.subplots) page.subplots[slot]=replacement;
        else {const title=page.title;Object.assign(page,replacement);page.title=title;}
      } else subs[slot]._metric_group=`${groupId}-extra`;
    }
    if(count===subs.length) page.title=`${view.metric} vs ${view.view}`;
    return first;
  }
  const api={catalog,initialize,group,apply,panels,name};
  if(typeof module!=='undefined') module.exports=api;
  root.ReportMetrics=api;
})(typeof window!=='undefined'?window:globalThis);
