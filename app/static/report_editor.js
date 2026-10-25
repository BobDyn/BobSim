/* Report pages are the same plot definitions consumed by Python's PlotEngine. */
(() => {
  const sizes = {single: 1, dual: 2, triple: 3, quad: 4};
  const clone = value => JSON.parse(JSON.stringify(value));
  const esc = escapeHtml;
  let editor = null, timer = null, revision = 0, opening = 0, fileView = null;
  const drafts = new Map(), previews = new Map(), pending = new Map();

  const dialog = document.createElement('dialog');
  dialog.id = 'report-editor';
  dialog.className = 'report-editor';
  document.body.append(dialog);
  const request = (action, extra = {}) => api('/api/reports/editor', {
    method: 'POST', headers: {'Content-Type': 'application/json'},
    body: JSON.stringify({...editor.context, action, plots: editor.plots, ...extra}),
  });
  const page = () => editor.plots[editor.selected];
  const subs = () => page().subplots || [page()];
  const message = text => { dialog.querySelector('[data-status]').textContent = text; };
  function field(label, value, attrs = '') {
    return `<label class="form-field"><span>${esc(label)}</span><input ${attrs} value="${esc(String(value ?? ''))}"></label>`;
  }
  function select(label, value, values, attrs = '') {
    return `<label class="form-field"><span>${esc(label)}</span><select ${attrs}>${values.map(v => {
      const [key, name] = Array.isArray(v) ? v : [v,v];
      return `<option value="${esc(key)}" ${key === value ? 'selected' : ''}>${esc(name)}</option>`;
    }).join('')}</select></label>`;
  }
  function check(label, value, attrs) {
    return `<label class="report-check"><input type="checkbox" ${attrs} ${value ? 'checked' : ''}>${esc(label)}</label>`;
  }
  function signal(label, axis, cfg) {
    return field(label, cfg?.key, `data-axis="${axis}" data-prop="key" list="report-signals" placeholder="Find a signal"`);
  }
  function curveHtml(curve, overlay = -1) {
    return `<div class="report-curve" data-curve="${overlay}">
      <div class="report-fields">${signal('X signal', 'x', curve.x)}${signal('Y signal', 'y', curve.y)}
      ${field('Legend label', curve.label, 'data-prop="label"')}
      ${select('Style', curve.style || 'line', ['line','scatter'], 'data-prop="style"')}
      ${field('Color', curve.color || '#4ea1ff', 'type="color" data-prop="color"')}
      ${select('Line', curve.linestyle || '-', [['-','Solid'],['--','Dashed'],[':','Dotted'],['-.','Dash-dot']], 'data-prop="linestyle"')}
      ${field('Line width', curve.linewidth ?? 2, 'type="number" min="0" step="0.25" data-number data-prop="linewidth"')}
      ${field('Opacity', curve.alpha ?? 1, 'type="number" min="0" max="1" step="0.1" data-number data-prop="alpha"')}</div>
      <details><summary>Units and transforms</summary><div class="report-fields">${['x','y'].map(axis =>
        field(`${axis.toUpperCase()} label / units`, curve[axis]?.label, `data-axis="${axis}" data-prop="label"`) +
        field(`${axis.toUpperCase()} scale factor`, curve[axis]?.scale ?? 1, `type="number" step="any" data-number data-axis="${axis}" data-prop="scale"`) +
        field(`${axis.toUpperCase()} offset`, curve[axis]?.offset ?? 0, `type="number" step="any" data-number data-axis="${axis}" data-prop="offset"`)).join('')}</div></details>
      ${check('Linear fit', curve.fit, 'data-prop="fit"')}
      ${overlay >= 0 ? '<button type="button" class="ghost-button" data-action="remove-overlay">Remove curve</button>' : ''}
    </div>`;
  }
  function subHtml(sub, i) {
    const inherited = key => sub[key] ?? page()[key];
    return `<details class="report-subplot" data-sub="${i}" open><summary>Plot ${i+1}${sub.title ? ' · ' + esc(sub.title) : ''}</summary>
      ${field('Plot title', sub.title, 'data-subprop="title"')}
      ${curveHtml(sub)}
      ${(Array.isArray(sub.overlay) ? sub.overlay : sub.overlay ? [sub.overlay] : []).map((c,i)=>curveHtml(c,i)).join('')}
      <button class="ghost-button" type="button" data-action="add-overlay">Add overlay curve</button>
      <details><summary>Axes and legend</summary><div class="report-fields">${['x','y'].map(axis =>
        select(`${axis.toUpperCase()} axis`, inherited(axis+'scale') || 'linear', ['linear','log','symlog'], `data-subprop="${axis}scale"`) +
        field(`${axis.toUpperCase()} minimum`, inherited(axis+'lim')?.[0], `type="number" step="any" data-limit="${axis}" data-end="0" placeholder="Automatic"`) +
        field(`${axis.toUpperCase()} maximum`, inherited(axis+'lim')?.[1], `type="number" step="any" data-limit="${axis}" data-end="1" placeholder="Automatic"`)).join('')}</div>
      ${check('Show legend', inherited('legend') !== false, 'data-subprop="legend"')}
      ${check('Show grid', inherited('grid') !== false, 'data-subprop="grid"')}</details></details>`;
  }
  function pagePreviewKey(id) { return JSON.stringify([editor.key,id,editor.plots[id],state.dark]); }
  function previewPage(id, card) {
    const signature=pagePreviewKey(id);
    const picture=card.querySelector('[data-page-image]');
    const note=card.querySelector('[data-page-status]');
    const place=payload=>{
      if(!card.isConnected || signature!==pagePreviewKey(id)) return;
      picture.src=payload.image;picture.hidden=false;note.hidden=true;
      card.querySelector('[data-plot-targets]').innerHTML=(payload.axes||[]).map((box,i)=>
        `<button type="button" class="report-plot-target" data-edit-sub="${i}" aria-label="Edit plot ${i+1}" title="Edit plot ${i+1}" style="left:${box.x*100}%;top:${box.y*100}%;width:${box.width*100}%;height:${box.height*100}%"><span>Edit plot ↗</span></button>`).join('');
    };
    if(previews.has(signature)) {place(previews.get(signature));return;}
    if(!editor.has_results) {note.textContent='Your recorded signals will appear here after the first run.';return;}
    note.textContent='Rendering plot…';
    if(!pending.has(signature)) {
      const context={...editor.context};
      const plots={[id]:clone(editor.plots[id])};
      pending.set(signature,api('/api/reports/editor', {method:'POST',headers:{'Content-Type':'application/json'},
        body:JSON.stringify({...context,action:'preview',page:id,plots,theme:state.dark?'dark':'light'})})
        .then(payload=>{if(previews.size>60) previews.delete(previews.keys().next().value);previews.set(signature,payload);return payload;})
        .finally(()=>pending.delete(signature)));
    }
    pending.get(signature).then(place).catch(e=>{
      if(card.isConnected && signature===pagePreviewKey(id)) {note.hidden=false;note.textContent=e.message;picture.hidden=true;}
    });
  }
  function renderPages() {
    const canvas=dialog.querySelector('[data-document]');
    const scroll=canvas.scrollTop;
    const entries=Object.entries(editor.plots);
    canvas.innerHTML=entries.map(([id,p],i)=>`<article class="report-sheet ${p.enabled===false?'report-sheet-excluded':''} ${id===editor.selected?'selected':''}" data-report-page="${esc(id)}">
      <header class="report-sheet-head"><div class="report-sheet-name"><button class="report-drag-grip" draggable="true" data-drag-page="${esc(id)}" title="Drag to move page" aria-label="Move page">⠿</button><span class="report-page-number">${String(i+1).padStart(2,'0')}</span><input class="report-sheet-title" data-sheet-title aria-label="Page title" value="${esc(p.title||id)}"></div>
      <div class="report-sheet-actions"><select data-layout class="report-layout-select" aria-label="Page layout">${Object.keys(sizes).map(layout=>`<option value="${layout}" ${layout===(p.layout||'single')?'selected':''}>${layout}</option>`).join('')}</select>
      <button type="button" data-sheet-action="up" title="Move page up" aria-label="Move page up" ${i===0?'disabled':''}>↑</button>
      <button type="button" data-sheet-action="down" title="Move page down" aria-label="Move page down" ${i===entries.length-1?'disabled':''}>↓</button>
      <button type="button" data-sheet-action="duplicate" title="Duplicate page" aria-label="Duplicate page">⧉</button>
      <button type="button" data-sheet-action="edit" title="Page settings" aria-label="Page settings">⋯</button></div></header>
      <div class="report-sheet-figure"><img data-page-image alt="${esc(p.title||id)}" hidden><p data-page-status>Loading preview…</p><div data-plot-targets></div></div>
      <footer class="report-sheet-foot"><span>BOBSIM <span class="report-foot-divider">/</span> ${esc(editor.title)}</span><label><input type="checkbox" data-sheet-enabled ${p.enabled!==false?'checked':''}> Include in PDF</label></footer>
      </article>`).join('')+`<button type="button" class="report-add-sheet" data-action="add"><span>＋</span> Add a page</button>`;
    canvas.querySelectorAll('[data-report-page]').forEach(card=>previewPage(card.dataset.reportPage,card));
    canvas.scrollTop=scroll;
    if(editor.activeSub!==null || editor.pageTools) renderDetail();
    dialog.querySelector('[data-report-count]').textContent=`${entries.filter(([,p])=>p.enabled!==false).length} pages · ${editor.signals.length} signals`;
  }
  function renderDetail() {
    dialog.querySelectorAll('.report-onplot-editor').forEach(el=>el.remove());
    dialog.querySelectorAll('[data-report-page]').forEach(card=>card.classList.toggle('selected',card.dataset.reportPage===editor.selected));
    const card=[...dialog.querySelectorAll('[data-report-page]')].find(c=>c.dataset.reportPage===editor.selected);
    if(!card || (editor.activeSub===null && !editor.pageTools)) return;
    const panel=document.createElement('div');panel.className='report-onplot-editor';
    panel.innerHTML=`<header><span>${editor.pageTools?'Page options':`Plot ${editor.activeSub+1}`}</span><button type="button" data-action="close-controls" aria-label="Close plot controls">×</button></header><div data-page-form></div>`;
    if(editor.pageTools) {
      panel.classList.add('report-page-options-popover');
      panel.querySelector('[data-page-form]').innerHTML=`${check('Shared X limits',page().sharex,'data-pageprop="sharex"')}${check('Shared Y limits',page().sharey,'data-pageprop="sharey"')}
        <div class="report-toolbar"><button type="button" class="ghost-button" data-action="duplicate">Duplicate page</button><button type="button" class="ghost-button" data-action="remove">Remove page</button></div>
        <details data-advanced><summary>Advanced YAML</summary><textarea data-yaml spellcheck="false" aria-label="Plot definitions YAML"></textarea><button type="button" data-action="apply-yaml">Apply YAML</button></details>
        <button type="button" class="ghost-button" data-action="restore">Restore run defaults</button>`;
      card.append(panel);
      panel.querySelector('[data-advanced]').addEventListener('toggle',async event=>{
        if(event.target.open) {try{panel.querySelector('[data-yaml]').value=(await request('yaml')).yaml;}catch(e){message(e.message);}}
      });
    } else {
      const sub=subs()[editor.activeSub];
      if(!sub) return;
      panel.querySelector('[data-page-form]').innerHTML=subHtml(sub,editor.activeSub);
      const box=previews.get(pagePreviewKey(editor.selected))?.axes?.[editor.activeSub];
      panel.style.left=`${Math.min((box?.x||.05)*100,48)}%`;
      panel.style.top=`${Math.min((box?.y||.05)*100,50)}%`;
      card.querySelector('.report-sheet-figure').append(panel);
    }
  }
  function render() {
    dialog.innerHTML=`<header class="report-editor-head"><div class="report-heading"><span class="report-eyebrow">RESULTS / REPORT</span><h2>${esc(editor.title)}</h2><span data-report-count></span></div>
      <div class="report-toolbar"><select data-new-layout aria-label="New page layout">${Object.keys(sizes).map(v=>`<option>${v}</option>`).join('')}</select><button type="button" class="ghost-button" data-action="add">＋ Add page</button><button type="button" class="ghost-button" data-action="save">Save</button><button type="button" class="primary-button" data-action="export" ${!editor.has_results?'disabled':''}>Export PDF ↗</button><button type="button" class="ghost-button" data-action="close">${editor.inline?'Files':'Close'}</button></div></header>
      <div class="report-editor-body"><section class="report-document" data-document aria-label="Interactive report pages"></section></div>
      <datalist id="report-signals">${editor.signals.map(s=>`<option value="${esc(s.key)}">${s.grouped?'Grouped · ':''}${s.samples} samples</option>`).join('')}</datalist>
      <footer class="report-editor-foot"><div>${editor.can_reuse?check('Reuse layout for future runs',editor.context.from_setup||!editor.context.result_id,'data-reuse'):''}<span data-download></span></div><p data-status role="status"></p></footer>`;
    message('Click any plot to edit. Drag the page handle to reorder.');
    renderPages();renderDetail();
  }
  function changed() {
    editor.dirty=true;revision++;
    message('Unsaved changes');
    clearTimeout(timer);timer=setTimeout(()=>{
      const cards=[...dialog.querySelectorAll('[data-report-page]')];
      if(cards.map(c=>c.dataset.reportPage).join('|')!==Object.keys(editor.plots).join('|')) {renderPages();return;}
      for(const card of cards) {
        const p=editor.plots[card.dataset.reportPage];
        card.classList.toggle('report-sheet-excluded',p.enabled===false);
        const input=card.querySelector('[data-sheet-title]');if(document.activeElement!==input)input.value=p.title||card.dataset.reportPage;
        card.querySelector('[data-sheet-enabled]').checked=p.enabled!==false;
        previewPage(card.dataset.reportPage,card);
      }
      dialog.querySelector('[data-report-count]').textContent=`${Object.values(editor.plots).filter(p=>p.enabled!==false).length} pages · ${editor.signals.length} signals`;
    },350);
  }
  function newCurve() {
    const current=page();
    const source=current?.subplots?.[0] || current;
    if(source?.x?.key && source?.y?.key) return {title:'',x:clone(source.x),y:clone(source.y)};
    const keys = editor.signals.map(s=>s.key);
    const x = keys.find(k=>k==='raw:time' || k==='time') || keys[0] || '';
    const y = keys.find(k=>k!==x) || x;
    return {title:'',x:{key:x,label:x},y:{key:y,label:y}};
  }
  function insertPage(p) {
    const id = 'page_' + Date.now().toString(36) + '_' + Math.random().toString(36).slice(2,6);
    editor.plots[id] = p; editor.selected = id; changed(); renderPages(); renderDetail();
    dialog.querySelector(`[data-report-page="${id}"]`)?.scrollIntoView({behavior:"smooth",block:"center"});
  }
  function reorder(id, target, after=false) {
    if(id===target) return;
    const entries=Object.entries(editor.plots), item=entries.find(([key])=>key===id);
    const rest=entries.filter(([key])=>key!==id);
    const at=rest.findIndex(([key])=>key===target);
    if(!item || at<0) return;
    rest.splice(at+(after?1:0),0,item); editor.plots=Object.fromEntries(rest); changed(); renderPages(); renderDetail();
  }
  dialog.addEventListener('change', event => {
    const el=event.target;
    const card=el.closest('[data-report-page]');
    if(card && (el.hasAttribute('data-sheet-title')||el.hasAttribute('data-sheet-enabled'))) {
      editor.plots[card.dataset.reportPage][el.hasAttribute('data-sheet-title')?'title':'enabled']=el.hasAttribute('data-sheet-title')?el.value:el.checked;changed();return;
    }
    if(card && el.hasAttribute('data-layout')) {editor.selected=card.dataset.reportPage;editor.activeSub=null;editor.pageTools=false;}
    const p=page();if(!p)return;
    const sub=el.closest('[data-sub]') ? subs()[Number(el.closest('[data-sub]').dataset.sub)] : null;
    let value = el.type==='checkbox' ? el.checked : el.hasAttribute('data-number') ? Number(el.value) : el.value;
    if(el.hasAttribute('data-pageprop')) p[el.dataset.pageprop]=value;
    else if(el.hasAttribute('data-layout')) {
      const old=clone(subs()), count=sizes[value];
      if(count<old.length && !confirm('This layout has fewer plots. Remove the extra subplots?')) { el.value=p.layout||'single';return; }
      p.layout=value;
      if(count===1) { const title=p.title; Object.assign(p,old[0]);p.title=title;delete p.subplots; }
      else { p.subplots=Array.from({length:count},(_,i)=>old[i]||newCurve()); for(const key of ['x','y','overlay']) delete p[key]; }
      changed();renderDetail();return;
    } else if(el.hasAttribute('data-subprop')) sub[el.dataset.subprop]=value;
    else if(el.hasAttribute('data-limit')) {
      const axis=el.dataset.limit;
      const inputs=[...el.closest('[data-sub]').querySelectorAll(`[data-limit="${axis}"]`)];
      if(inputs.every(n=>n.value==='')) delete sub[axis+'lim'];
      else if(inputs.some(n=>n.value==='')) {message('Set both axis limits, or clear both for automatic limits.');return;}
      else sub[axis+'lim']=inputs.map(n=>Number(n.value));
    } else if(el.hasAttribute('data-prop')) {
      const idx=Number(el.closest('[data-curve]').dataset.curve);
      const overlays=Array.isArray(sub.overlay)?sub.overlay:sub.overlay?[sub.overlay]:[];
      const curve=idx<0?sub:overlays[idx];
      const target=el.dataset.axis?(curve[el.dataset.axis] ||= {}):curve;
      if(value==='' && !['key','label'].includes(el.dataset.prop)) delete target[el.dataset.prop];
      else target[el.dataset.prop]=value;
    } else return;
    changed();
  });
  dialog.addEventListener('click', async event => {
    const card=event.target.closest('[data-report-page]');
    const plot=event.target.closest('[data-edit-sub]');
    const sheetButton=event.target.closest('[data-sheet-action]');
    if(card && (plot || sheetButton)) {
      editor.selected=card.dataset.reportPage;
      if(plot || sheetButton.dataset.sheetAction==='edit') {
        editor.activeSub=plot?Number(plot.dataset.editSub):null;editor.pageTools=!plot;renderDetail();return;
      }
      const action=sheetButton.dataset.sheetAction;
      if(action==='duplicate') {const p=clone(page());p.title=(p.title||'Page')+' copy';insertPage(p);return;}
      const ids=Object.keys(editor.plots),i=ids.indexOf(editor.selected);
      reorder(editor.selected,ids[i+(action==='up'?-1:1)],action==='down');return;
    }
    const button=event.target.closest('[data-action]');
    if(!button) return;
    const action=button.dataset.action;
    try {
      if(action==='close-controls') {editor.activeSub=null;editor.pageTools=false;renderDetail();return;}
      if(action==='close') {if(!editor.dirty || confirm('Close without saving your report changes?')) {fileView=editor.key;dialog.close();document.querySelector('.archive-workspace').classList.remove('report-viewing');document.getElementById('study-preview').hidden=false;}return;}
      if(action==='add') {
        editor.activeSub=0;editor.pageTools=false;
        const layout=dialog.querySelector('[data-new-layout]').value;
        const p={layout,title:'New page',enabled:true};
        if(layout==='single') Object.assign(p,newCurve(),{title:'New page'});
        else p.subplots=Array.from({length:sizes[layout]},newCurve);
        insertPage(p);return;
      }
      if(action==='duplicate') {const p=clone(page());p.title=(p.title||'Page')+' copy';insertPage(p);return;}
      if(action==='remove') {delete editor.plots[editor.selected];editor.selected=Object.keys(editor.plots)[0];changed();renderDetail();return;}
      if(action==='up'||action==='down') {const ids=Object.keys(editor.plots),i=ids.indexOf(editor.selected);reorder(editor.selected,ids[i+(action==='up'?-1:1)],action==='down');return;}
      if(action==='restore') {if(confirm('Replace these pages with the saved run defaults?')) {editor.plots=clone(editor.defaults);editor.selected=Object.keys(editor.plots)[0];changed();renderDetail();}return;}
      if(action==='add-overlay'||action==='remove-overlay') {
        const sub=subs()[Number(button.closest('[data-sub]').dataset.sub)];
        sub.overlay=Array.isArray(sub.overlay)?sub.overlay:sub.overlay?[sub.overlay]:[];
        if(action==='add-overlay') sub.overlay.push({x:clone(sub.x),y:clone(sub.y),label:'Overlay'});
        else sub.overlay.splice(Number(button.closest('[data-curve]').dataset.curve),1);
        changed();renderDetail();return;
      }
      button.disabled=true;
      if(action==='apply-yaml') {editor.plots=(await request('parse-yaml',{yaml:dialog.querySelector('[data-yaml]').value})).plots;editor.selected=Object.keys(editor.plots)[0];changed();renderDetail();message('YAML applied.');}
      if(action==='save') {
        const reuse=Boolean(dialog.querySelector('[data-reuse]')?.checked);
        await request('save',{reuse});editor.dirty=false;drafts.delete(editor.key);
        if(reuse && state.selectedSimulationId===editor.context.simulation_id) {
          // Reload only after the editor saved the simulation's new report config.
          const payload=await simulationRequest('load',{id:editor.context.simulation_id});
          state.simConfigPayload=payload.config;acceptCleanSimConfigPayload();renderSimConfigForm();
        }
        message(reuse?'Layout saved for this report and future simulation runs.':'Report layout saved.');
      }
      if(action==='export') {
        const output=await request('export');
        dialog.querySelector('[data-download]').innerHTML=`<a href="${fileDownloadUrl(output.path)}" target="_blank">Open PDF ↗</a> · <a href="${fileDownloadUrl(output.layout_path)}" target="_blank">Layout YAML ↗</a>`;
        message('PDF exported from recorded signals.');
      }
    } catch(e) {message(e.message);} finally {button.disabled=false;}
  });
  let dragging=null;
  dialog.addEventListener('dragstart',event=>{const grip=event.target.closest('[data-drag-page]');if(grip){dragging=grip.dataset.dragPage;event.dataTransfer.setData('text/plain',dragging);event.dataTransfer.effectAllowed='move';}});
  function clearDrop(){dialog.querySelectorAll('.reorder-before,.reorder-after').forEach(n=>n.classList.remove('reorder-before','reorder-after'));}
  dialog.addEventListener('dragover',event=>{if(!dragging)return;clearDrop();const target=event.target.closest('[data-report-page]');if(target&&target.dataset.reportPage!==dragging){event.preventDefault();target.classList.add(event.clientY<target.getBoundingClientRect().top+target.offsetHeight/2?'reorder-before':'reorder-after');}
    const canvas=dialog.querySelector('[data-document]'),box=canvas.getBoundingClientRect();if(event.clientY<box.top+60)canvas.scrollTop-=24;else if(event.clientY>box.bottom-60)canvas.scrollTop+=24;
  });
  dialog.addEventListener('drop',event=>{const target=event.target.closest('[data-report-page]');if(dragging&&target){event.preventDefault();reorder(dragging,target.dataset.reportPage,target.classList.contains('reorder-after'));}dragging=null;clearDrop();});
  dialog.addEventListener('dragend',()=>{dragging=null;clearDrop();});
  dialog.addEventListener('cancel',event=>{if(editor?.dirty&&!confirm('Close without saving your report changes?'))event.preventDefault();});
  dialog.addEventListener('close',()=>{clearTimeout(timer);revision++;});
  async function openEditor(run, simulation, inline, fromSetup = false, forceEditor = false) {
    const context={vehicle_key:activeVehicleKey(),result_id:run?.id||null,simulation_id:simulation?.id||null,from_setup:fromSetup};
    const key=JSON.stringify([context.vehicle_key,context.result_id,context.simulation_id]);
    if(editor && editor.key===key && (dialog.open || editor.loading) && inline===editor.inline) return;
    if(editor?.dirty) drafts.set(editor.key,{plots:clone(editor.plots),selected:editor.selected});
    clearTimeout(timer);revision++;
    const token=++opening;
    const next={context,plots:{},key,inline};
    const data=await api('/api/reports/editor',{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify({...context,action:'load'})});
    if(token!==opening) return;
    if(dialog.open) dialog.close();
    editor={...next,...data,loading:true,plots:clone(data.plots),dirty:false,activeSub:null,pageTools:false,selected:Object.keys(data.plots)[0]};
    if(drafts.has(key)) Object.assign(editor,drafts.get(key),{dirty:true});
    dialog.classList.toggle('report-inline',inline);
    (inline?document.querySelector('.results-app-pane'):document.body).append(dialog);
    const host=document.getElementById('study-preview');
    if(inline) {
      document.querySelector('.archive-workspace').classList.add('report-viewing');host.hidden=false;
      host.innerHTML='<div class="report-loading"><span class="report-loading-orbit"></span><h2>Preparing your report</h2><p data-load-count>Loading saved plot data…</p></div>';
    }
    const entries=Object.entries(editor.plots);let complete=0;
    if(!entries.length && run && !forceEditor) {
      const original=run.files?.find(file=>file.kind==='pdf'&&file.exists);
      if(original) {
        editor.loading=false;fileView=editor.key;
        document.querySelector('.archive-workspace').classList.remove('report-viewing');
        await previewFile(original.path,'pdf','study-preview');return;
      }
    }
    for(const [id,p] of entries) {
      const signature=pagePreviewKey(id);
      if(!previews.has(signature) && editor.has_results) {
        const value=await api('/api/reports/editor',{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify({...context,action:'preview',page:id,plots:{[id]:p},theme:state.dark?'dark':'light'})});
        if(token!==opening) return;
        const decoded=new Image();decoded.src=value.image;await decoded.decode();
        previews.set(signature,value);
      }
      complete++;
      if(inline && host.querySelector('[data-load-count]')) host.querySelector('[data-load-count]').textContent=`${complete} of ${entries.length} pages ready`;
    }
    editor.loading=false;
    render();
    if(inline) {document.getElementById('study-preview').hidden=true;document.querySelector('.archive-workspace').classList.add('report-viewing');dialog.show();}
    else dialog.showModal();
    dialog.querySelector('[data-document]').scrollTop=0;
  }
  window.openReportViewer=async run=>{
    const simulation=state.simulationWorkspace?.simulations?.find(s=>s.id===run?.simulation?.id);
    if(fileView===JSON.stringify([activeVehicleKey(),run?.id||null,simulation?.id||null])) return;
    try {await openEditor(run,simulation,true);} catch(e) {
      if(editor) editor.loading=false;
      document.getElementById('study-preview').hidden=false;
      document.getElementById('study-preview').textContent=e.message;
    }
  };
  document.addEventListener('click', async event => {
    const trigger=event.target.closest('[data-edit-report]');
    if(!trigger) return;
    trigger.disabled=true;
    try {
      fileView=null;
      await saveSimulationEdits();
      const fromSetup=trigger.dataset.editReport==='setup';
      const simulation=selectedSimulation();
      const run=fromSetup?savedResults().find(r=>r.simulation?.id===simulation?.id):selectedSavedResult();
      if(run && fromSetup) {
        state.selectedResultId=run.id;state.selectedVisualizationId=null;setView('studies');
      }
      const owner=fromSetup?simulation:state.simulationWorkspace?.simulations?.find(s=>s.id===run?.simulation?.id);
      await openEditor(run,owner,Boolean(run),fromSetup,true);
    } catch(e) {alert(e.message);} finally {trigger.disabled=false;}
  });
  document.addEventListener('click',event=>{
    if(event.target.closest('#study-output-list [data-file-path]')) {
      dialog.close();document.querySelector('.archive-workspace').classList.remove('report-viewing');document.getElementById('study-preview').hidden=false;
    }
  });
})();
