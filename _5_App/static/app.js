const savedRotationSensitivity = Number(localStorage.getItem("bobsim-rotation-sensitivity"));
const savedSetupPaneWidth = Number(localStorage.getItem("bobsim-setup-pane-width"));
const savedGeometryShowFront = localStorage.getItem("bobsim-geometry-show-front");
const savedGeometryShowRear = localStorage.getItem("bobsim-geometry-show-rear");
const DEFAULT_VEHICLE_YAW = Math.PI - 0.72;
const DEFAULT_VEHICLE_PITCH = 0.46;
const DEFAULT_SETUP_PANE_WIDTH = 320;
const MIN_SETUP_PANE_WIDTH = 260;
const MAX_SETUP_PANE_WIDTH = 620;
const MIN_VISUAL_PANE_WIDTH = 520;
const MIN_PREVIEW_ZOOM = 0.55;
const MAX_PREVIEW_ZOOM = 3.5;
const MAX_PREVIEW_PAN_FRACTION = 0.42;
const MAX_UNDO_STEPS = 80;

const state = {
  status: null,
  vehiclePayload: null,
  vehicleLibrary: null,
  vehicleTemplates: null,
  tirePayload: null,
  tireTemplates: null,
  activeTir: null,
  view: "setup",
  selectedVehicleSource: "active",
  selectedWorkflowId: null,
  selectedJobId: null,
  activeSimTab: "setup",
  simConfigPayload: null,
  simConfigLibrary: null,
  selectedSimConfigSource: "",
  dirtySimConfig: false,
  cleanSimConfigSignature: "",
  loadingSimConfigFor: null,
  activeParamGroup: null,
  vehicleStartOpen: true,
  dirtyVehicle: false,
  vehiclePreviewView: "iso",
  vehiclePreviewYaw: DEFAULT_VEHICLE_YAW,
  vehiclePreviewPitch: DEFAULT_VEHICLE_PITCH,
  vehiclePreviewZoom: 1,
  vehiclePreviewPanX: 0,
  vehiclePreviewPanY: 0,
  rotationSensitivity: Number.isFinite(savedRotationSensitivity) && savedRotationSensitivity > 0
    ? savedRotationSensitivity
    : 1,
  setupPaneWidth: Number.isFinite(savedSetupPaneWidth) && savedSetupPaneWidth > 0
    ? savedSetupPaneWidth
    : DEFAULT_SETUP_PANE_WIDTH,
  vehicleDrag: null,
  geometryScene: null,
  geometryHoverPointId: null,
  geometrySelectedPointId: null,
  geometryDrag: null,
  geometryAxis: "x",
  geometryShowFront: savedGeometryShowFront === null ? true : savedGeometryShowFront === "true",
  geometryShowRear: savedGeometryShowRear === null ? true : savedGeometryShowRear === "true",
  massScene: null,
  massHoverPointId: null,
  massSelectedPointId: null,
  massEditorPositionFrame: null,
  architectureScene: null,
  architectureHoverId: null,
  architectureSelectedId: null,
  architectureSelectedOrderIndex: 0,
  architectureModalOpen: false,
  architectureModalAxle: null,
  setupResize: null,
  undoStack: [],
  pendingUndoSnapshot: null,
  cleanVehicleSignature: "",
  suppressUndo: false,
  referenceOpen: false,
  dark: localStorage.getItem("bobsim-theme") === "dark",
};

document.body.classList.toggle("dark", state.dark);

const PARAMETER_AREAS = [
  { id: "vehicle", label: "Architecture", visual: "overview", always: true },
  { id: "hardpoints", label: "Geometry", visual: "hardpoints", always: true },
  { id: "mass", label: "Mass", visual: "mass", always: true },
  { id: "suspension", label: "Suspension", visual: "suspension", always: true },
  { id: "compliances", label: "Compliances", visual: "compliances", always: true },
  { id: "tires", label: "Tires", visual: "tires", always: true },
  { id: "aero", label: "Aero", visual: "aero", always: true },
  { id: "powertrain", label: "Powertrain", visual: "powertrain", always: true },
];

const SETUP_GUIDE = {
  vehicle: {
    title: "Architecture",
    focus: "Topology, templates, powertrain.",
    purpose: "Define model topology.",
    figure: "Assembly path.",
    check: "Template matches the car.",
  },
  hardpoints: {
    title: "Geometry",
    focus: "Hardpoints and link layout.",
    purpose: "Place the kinematic skeleton.",
    figure: "Hardpoints and links.",
    check: "Coordinates form a real suspension.",
  },
  mass: {
    title: "Mass",
    focus: "Mass, CG, inertia.",
    purpose: "Set body motion properties.",
    figure: "Mass and gyration.",
    check: "CG and inertia are plausible.",
  },
  suspension: {
    title: "Suspension",
    focus: "Rates and actuation.",
    purpose: "Convert wheel motion into force.",
    figure: "Spring and damper curves.",
    check: "Tables and linkage order make sense.",
  },
  compliances: {
    title: "Compliances",
    focus: "Chassis and elastic effects.",
    purpose: "Model non-rigid structure.",
    figure: "Torsional stiffness.",
    check: "Stiffness magnitude is plausible.",
  },
  tires: {
    title: "Tires",
    focus: ".tir files and MF curves.",
    purpose: "Define tire force generation.",
    figure: "Pure and combined slip.",
    check: "Force peaks are reasonable.",
  },
  aero: {
    title: "Aero",
    focus: "Ride-height load maps.",
    purpose: "Map attitude to aero loads.",
    figure: "Aero heatmaps.",
    check: "Map signs and magnitudes are sane.",
  },
  powertrain: {
    title: "Powertrain",
    focus: "Drivetrain chain.",
    purpose: "Convert demand to wheel force.",
    figure: "Power flow.",
    check: "Implemented family matches the car.",
  },
};

async function api(path, options = {}) {
  const response = await fetch(path, options);
  const data = await response.json();
  if (!response.ok) throw new Error(data.error || response.statusText);
  return data;
}

async function refreshTirePayload() {
  try {
    state.tirePayload = await api("/api/tires/eval");
  } catch (error) {
    state.tirePayload = { model: error.message, sides: [] };
  }
}

async function refreshTireTemplates() {
  try {
    state.tireTemplates = await api("/api/tires/templates");
  } catch (error) {
    state.tireTemplates = { templates: [], error: error.message };
  }
}

function escapeHtml(value) {
  return String(value)
    .replaceAll("&", "&amp;")
    .replaceAll("<", "&lt;")
    .replaceAll(">", "&gt;")
    .replaceAll('"', "&quot;");
}

function fmtBytes(value) {
  if (!Number.isFinite(value)) return "";
  if (value < 1024) return `${value} B`;
  if (value < 1024 * 1024) return `${(value / 1024).toFixed(1)} KB`;
  return `${(value / (1024 * 1024)).toFixed(1)} MB`;
}

function standardWorkflows() {
  return (state.status?.workflows || []).filter((workflow) => workflow.group === "standard");
}

function selectedWorkflow() {
  const workflows = standardWorkflows();
  return workflows.find((workflow) => workflow.id === state.selectedWorkflowId) || workflows[0] || null;
}

function selectedWorkflowConfigId(workflow = selectedWorkflow()) {
  return workflow?.config_id || workflow?.id || "";
}

async function refreshSelectedSimConfig() {
  const workflow = selectedWorkflow();
  if (!workflow?.config_id) {
    state.simConfigPayload = null;
    state.simConfigLibrary = null;
    state.cleanSimConfigSignature = "";
    state.dirtySimConfig = false;
    return;
  }
  state.loadingSimConfigFor = workflow.id;
  const [payload, library] = await Promise.all([
    api(`/api/configs/${encodeURIComponent(workflow.config_id)}`),
    api(`/api/sim-configs?workflow_id=${encodeURIComponent(workflow.id)}`),
  ]);
  state.simConfigPayload = payload;
  state.simConfigLibrary = library;
  state.selectedSimConfigSource = library.sources?.[0]?.id || "";
  acceptCleanSimConfigPayload();
  state.loadingSimConfigFor = null;
}

function ensureSelectedSimConfigLoaded() {
  const workflow = selectedWorkflow();
  if (!workflow?.config_id || state.loadingSimConfigFor === workflow.id) return;
  if (state.simConfigPayload?.id === workflow.config_id) return;
  refreshSelectedSimConfig()
    .then(renderStandard)
    .catch((error) => {
      state.loadingSimConfigFor = null;
      state.simConfigPayload = null;
      state.simConfigLibrary = { sources: [], error: error.message };
      renderStandard();
    });
}

function configDataSignature(data) {
  return JSON.stringify(data ?? {});
}

function acceptCleanSimConfigPayload() {
  state.cleanSimConfigSignature = configDataSignature(state.simConfigPayload?.data || {});
  state.dirtySimConfig = false;
}

function activeVehicleName() {
  return state.vehiclePayload?.data?.vehicle?.name || "Active vehicle";
}

function activeArchitecture() {
  const architecture = state.vehiclePayload?.data?.architecture || {};
  return `${architecture.front || "front"} / ${architecture.rear || "rear"}`;
}

async function refresh() {
  state.status = await api("/api/status");
  state.vehicleLibrary = await api("/api/vehicles");
  state.vehicleTemplates = await api("/api/vehicle-templates");
  state.vehiclePayload = await api("/api/configs/vehicle");
  acceptCleanVehiclePayload();
  await refreshTirePayload();
  await refreshTireTemplates();
  if (!state.activeTir && state.tireTemplates?.templates?.length) {
    await loadTirTemplate(defaultTirTemplateName());
  }
  if (!state.selectedWorkflowId) {
    state.selectedWorkflowId = standardWorkflows()[0]?.id || null;
  }
  await refreshSelectedSimConfig();
  render();
}

function render() {
  renderTopbar();
  renderThemeButton();
  renderVehicleControls();
  applySetupPaneWidth();
  renderMode();
  renderSetup();
  renderStandard();
  renderRailActions();
  renderVehicleStartModal();
  renderArchitectureConnectionModal();
}

function renderTopbar() {
  const repo = state.status?.repo;
  document.getElementById("repo-root").textContent = repo?.root ? "Local BobSim workspace" : "";

  const boblib = document.getElementById("boblib-status");
  const boblibOk = Boolean(repo?.boblib_package?.exists);
  boblib.textContent = boblibOk ? "BobLib ready" : "BobLib missing";
  boblib.className = `status-pill ${boblibOk ? "ok" : "warn"}`;

  const vehicleOk = Boolean(repo?.vehicle_exe?.exists);
  const fourPostOk = Boolean(repo?.four_post_exe?.exists);
  const build = document.getElementById("build-status");
  build.textContent = vehicleOk && fourPostOk ? "Builds ready" : "Builds pending";
  build.className = `status-pill ${vehicleOk && fourPostOk ? "ok" : "warn"}`;
}

function renderThemeButton() {
  document.getElementById("theme-toggle-btn").textContent = state.dark ? "Light" : "Dark";
}

function renderVehicleControls() {
  const sensitivity = document.getElementById("rotation-sensitivity");
  const label = document.getElementById("rotation-sensitivity-value");
  if (!sensitivity || !label) return;
  sensitivity.value = String(state.rotationSensitivity);
  label.textContent = `${state.rotationSensitivity.toFixed(2).replace(/\.?0+$/, "")}x`;
}

function renderVehicleStartModal() {
  const modal = document.getElementById("vehicle-start-modal");
  if (!modal) return;
  modal.hidden = !state.vehicleStartOpen;
  if (!state.vehicleStartOpen) return;

  const loadPicker = document.getElementById("start-load-picker");
  const templatePicker = document.getElementById("start-template-picker");
  const loadButton = document.getElementById("start-load-btn");
  const createButton = document.getElementById("start-create-btn");
  const loadSources = savedVehicleSources();
  if (loadPicker) {
    loadPicker.innerHTML = loadSources.length
      ? loadSources.map((vehicle) => `<option value="${escapeHtml(vehicle.id)}">Saved: ${escapeHtml(vehicle.label)}</option>`).join("")
      : `<option value="">No saved vehicles yet</option>`;
  }
  if (loadButton) loadButton.disabled = !loadSources.length;

  const templates = state.vehicleTemplates?.templates || [];
  if (templatePicker) {
    templatePicker.innerHTML = templates.map((template) => `
      <option value="${escapeHtml(template.id)}">${escapeHtml(templateArchitectureLabel(template))}</option>
    `).join("");
  }
  if (createButton) createButton.disabled = !templates.length;
  const nameInput = document.getElementById("start-vehicle-name");
  if (nameInput && !nameInput.value) nameInput.value = nextVehicleName();
}

function vehicleLoadSources() {
  return (state.vehicleLibrary?.vehicles || []).filter((vehicle) => vehicle.type !== "template");
}

function savedVehicleSources() {
  return (state.vehicleLibrary?.vehicles || []).filter((vehicle) => vehicle.type === "saved");
}

function nextVehicleName() {
  const count = (state.vehicleLibrary?.vehicles || []).filter((vehicle) => vehicle.type === "saved").length;
  return count ? `Vehicle ${count + 1}` : "New Vehicle";
}

function clamp(value, min, max) {
  return Math.min(max, Math.max(min, value));
}

function setupPaneBounds() {
  const workspace = document.querySelector(".setup-workspace");
  const width = workspace?.getBoundingClientRect().width || 0;
  const maxByViewport = width > 0 ? width - MIN_VISUAL_PANE_WIDTH : MAX_SETUP_PANE_WIDTH;
  const max = Math.max(
    MIN_SETUP_PANE_WIDTH,
    Math.min(MAX_SETUP_PANE_WIDTH, maxByViewport),
  );
  return { min: MIN_SETUP_PANE_WIDTH, max };
}

function setSetupPaneWidth(width, { persist = false, redraw = true } = {}) {
  const { min, max } = setupPaneBounds();
  const clamped = clamp(Number(width) || DEFAULT_SETUP_PANE_WIDTH, min, max);
  state.setupPaneWidth = clamped;
  applySetupPaneWidth(clamped, min, max);
  if (persist) localStorage.setItem("bobsim-setup-pane-width", String(Math.round(clamped)));
  if (redraw) requestAnimationFrame(drawVehicleFromForm);
}

function applySetupPaneWidth(width = state.setupPaneWidth, min, max) {
  const workspace = document.querySelector(".setup-workspace");
  if (!workspace) return;
  const bounds = min === undefined || max === undefined ? setupPaneBounds() : { min, max };
  const clamped = clamp(Number(width) || DEFAULT_SETUP_PANE_WIDTH, bounds.min, bounds.max);
  workspace.style.setProperty("--setup-pane-width", `${Math.round(clamped)}px`);
  const splitter = document.getElementById("setup-splitter");
  if (splitter) {
    splitter.setAttribute("aria-valuemin", String(Math.round(bounds.min)));
    splitter.setAttribute("aria-valuemax", String(Math.round(bounds.max)));
    splitter.setAttribute("aria-valuenow", String(Math.round(clamped)));
  }
}

function renderMode() {
  document.querySelectorAll(".rail-item").forEach((button) => {
    button.classList.toggle("active", button.dataset.view === state.view);
  });
  document.querySelectorAll(".screen").forEach((screen) => {
    screen.classList.toggle("active", screen.id === `${state.view}-view`);
  });
}

function renderRailActions() {
  const primary = document.getElementById("rail-primary-btn");
  const secondary = document.getElementById("rail-secondary-btn");
  if (state.view === "setup") {
    primary.textContent = "Save Vehicle";
    primary.disabled = false;
    secondary.textContent = "Enter Standard";
    secondary.disabled = false;
    return;
  }
  primary.textContent = "Run Simulation";
  primary.disabled = !selectedWorkflow();
  secondary.textContent = "Back to Vehicle";
  secondary.disabled = false;
}

function renderSetup() {
  renderVehicleLibrary();
  renderVehicleEditor();
  renderVehiclePreview(state.vehiclePayload?.data || {});
}

function renderVehicleLibrary() {
  const picker = document.getElementById("vehicle-library-picker");
  const vehicles = vehicleLoadSources();
  if (!vehicles.some((vehicle) => vehicle.id === state.selectedVehicleSource)) {
    state.selectedVehicleSource = "active";
  }
  picker.innerHTML = vehicles.map((vehicle) => {
    const selected = vehicle.id === state.selectedVehicleSource ? " selected" : "";
    const prefix = vehicle.type === "saved" ? "Saved" : "Active";
    return `<option value="${escapeHtml(vehicle.id)}"${selected}>${prefix}: ${escapeHtml(vehicle.label)}</option>`;
  }).join("");
  const saveName = document.getElementById("save-vehicle-name");
  if (saveName && !saveName.value) saveName.value = activeVehicleName();
  syncVehicleLibraryActions();
}

function openVehicleStartModal() {
  state.vehicleStartOpen = true;
  document.querySelector(".model-menu")?.removeAttribute("open");
  renderVehicleStartModal();
}

function selectedVehicleLibraryItem() {
  const picker = document.getElementById("vehicle-library-picker");
  const sourceId = picker?.value || state.selectedVehicleSource;
  return (state.vehicleLibrary?.vehicles || []).find((vehicle) => vehicle.id === sourceId) || null;
}

function syncVehicleLibraryActions() {
  const picker = document.getElementById("vehicle-library-picker");
  if (picker) state.selectedVehicleSource = picker.value || state.selectedVehicleSource;
  const selected = selectedVehicleLibraryItem();
  const deleteButton = document.getElementById("delete-vehicle-btn");
  if (!deleteButton) return;
  const canDelete = selected?.type === "saved";
  deleteButton.hidden = !canDelete;
  deleteButton.disabled = !canDelete;
  deleteButton.title = canDelete
    ? "Delete this saved vehicle config"
    : "Only saved vehicle configs can be deleted";
}

function renderVehicleEditor() {
  if (!state.vehiclePayload) return;
  document.getElementById("config-path").textContent = state.vehiclePayload.path;
  document.getElementById("config-text").value = state.vehiclePayload.raw;
  document.getElementById("save-status").textContent = state.dirtyVehicle ? "Unsaved" : "Saved";

  const form = document.getElementById("config-form");
  const areas = buildParameterAreas(state.vehiclePayload.fields || []);
  const areaIds = areas.map((area) => area.id);
  if (!areaIds.includes(state.activeParamGroup)) state.activeParamGroup = areaIds[0] || null;
  renderSetupFocus();
  renderParameterTabs(areas);
  form.innerHTML = areas.map((area) => `
    <section class="config-section ${area.id === state.activeParamGroup ? "active" : ""}" data-param-group="${escapeHtml(area.id)}">
      ${parameterAreaFields(area)}
    </section>
  `).join("");
  form.onfocusin = (event) => cacheUndoBaseline(event.target);
  form.onpointerdown = (event) => cacheUndoBaseline(event.target);
  form.onkeydown = (event) => {
    if (!event.repeat && ["Enter", " "].includes(event.key)) cacheUndoBaseline(event.target);
  };
  form.oninput = (event) => {
    if (!event.target.closest("[data-tir-tools], [data-setup-filter]")) {
      commitUndoBaseline("input");
      markVehicleDirty();
    }
  };
  form.onchange = (event) => {
    if (!event.target.closest("[data-tir-tools], [data-setup-filter]")) {
      if (!event.target.matches?.("input[type='text'], input[type='number'], textarea")) {
        commitUndoBaseline("change");
      }
      markVehicleDirty();
    }
  };
  form.onclick = handleArrayEditorClick;
  wireArchitectureTools();
  wireTireTools();
  wireFieldSubsections();
  applyArchitectureVisibility();
  syncArchitectureDependentControls();
  renderArchitectureTemplateMatches();
  renderParameterTabCanvases();
}

function wireFieldSubsections() {
  document.querySelectorAll(".field-subsection").forEach((section) => {
    section.classList.add("expanded");
  });
}

function setupGuide(areaId = state.activeParamGroup) {
  const area = PARAMETER_AREAS.find((item) => item.id === areaId) || PARAMETER_AREAS[0];
  const config = SETUP_GUIDE[area.id] || {};
  return {
    id: area.id,
    step: PARAMETER_AREAS.findIndex((item) => item.id === area.id) + 1,
    total: PARAMETER_AREAS.length,
    title: config.title || area.label,
    focus: config.focus || "",
    purpose: config.purpose || "",
    figure: config.figure || "",
    check: config.check || "",
  };
}

function renderSetupFocus() {
  const guide = setupGuide();
  const stepLabel = document.getElementById("setup-step-label");
  const setupTitle = document.getElementById("setup-title");
  const setupFocus = document.getElementById("setup-focus");
  if (stepLabel) stepLabel.textContent = `Step ${guide.step} of ${guide.total}`;
  if (setupTitle) setupTitle.textContent = guide.title;
  if (setupFocus) setupFocus.textContent = guide.focus;
  document.getElementById("vehicle-preview-title").textContent = guide.figure || guide.title;
  document.getElementById("vehicle-preview-subtitle").textContent = guide.purpose || "";
  const heading = document.getElementById("editor-title");
  if (heading) heading.textContent = `${String(guide.step).padStart(2, "0")} ${guide.title}`;
  renderSetupStepActions();
  renderWorkflowGuide(guide);
}

function setupAreas() {
  return state.vehiclePayload?.fields ? buildParameterAreas(state.vehiclePayload.fields) : PARAMETER_AREAS;
}

function activeParameterIndex(areas = setupAreas()) {
  const index = areas.findIndex((area) => area.id === state.activeParamGroup);
  return index >= 0 ? index : 0;
}

function renderSetupStepActions() {
  const areas = setupAreas();
  const index = activeParameterIndex(areas);
  const previous = areas[index - 1];
  const next = areas[index + 1];
  const previousButton = document.getElementById("setup-prev-btn");
  const nextButton = document.getElementById("setup-next-btn");
  if (previousButton) {
    previousButton.disabled = !previous;
    previousButton.textContent = previous ? `Previous: ${setupGuide(previous.id).title}` : "Previous";
  }
  if (nextButton) {
    nextButton.disabled = !next;
    nextButton.textContent = next ? `Next: ${setupGuide(next.id).title}` : "Next";
  }
}

function navigateParameterStep(delta) {
  const areas = setupAreas();
  const index = activeParameterIndex(areas);
  const target = areas[index + delta];
  if (target) activateParameterGroup(target.id);
}

function handleSetupStageKeys(event) {
  if (state.view !== "setup") return;
  if (!["ArrowLeft", "ArrowRight"].includes(event.key)) return;
  if (isTextEntryTarget(event.target) || event.target?.closest?.("#setup-splitter")) return;
  if (state.architectureModalOpen || state.vehicleStartOpen || document.querySelector(".model-menu[open]")) return;
  event.preventDefault();
  navigateParameterStep(event.key === "ArrowRight" ? 1 : -1);
}

function renderWorkflowGuide(guide = setupGuide()) {
  const panel = document.getElementById("workflow-guide");
  if (!panel) return;
  panel.innerHTML = `
    <div class="guide-row"><span>Why</span><strong>${escapeHtml(guide.purpose || guide.focus)}</strong></div>
    <div class="guide-row"><span>View</span><strong>${escapeHtml(guide.figure || "")}</strong></div>
    <div class="guide-row"><span>Check</span><strong>${escapeHtml(guide.check || "")}</strong></div>
  `;
  panel.hidden = !state.referenceOpen;
  document.getElementById("reference-toggle-btn")?.classList.toggle("active", state.referenceOpen);
}

function cloneData(data) {
  if (data === undefined) return undefined;
  return JSON.parse(JSON.stringify(data));
}

function vehicleDataSignature(data) {
  return JSON.stringify(data ?? {});
}

function acceptCleanVehiclePayload({ resetUndo = true } = {}) {
  state.cleanVehicleSignature = vehicleDataSignature(state.vehiclePayload?.data || {});
  state.dirtyVehicle = false;
  state.pendingUndoSnapshot = null;
  if (resetUndo) state.undoStack = [];
}

function snapshotVehicleState(label = "") {
  if (!state.vehiclePayload) return null;
  const data = currentVehicleFormData();
  if (!data) return null;
  return {
    activeParamGroup: state.activeParamGroup,
    geometrySelectedPointId: state.geometrySelectedPointId,
    geometryAxis: state.geometryAxis,
    label,
    data: cloneData(data),
  };
}

function pushUndoSnapshot(snapshot = snapshotVehicleState()) {
  if (state.suppressUndo || !snapshot?.data) return;
  const signature = vehicleDataSignature(snapshot.data);
  const last = state.undoStack[state.undoStack.length - 1];
  if (last && vehicleDataSignature(last.data) === signature) return;
  state.undoStack.push(snapshot);
  if (state.undoStack.length > MAX_UNDO_STEPS) state.undoStack.shift();
}

function cacheUndoBaseline(target) {
  if (state.suppressUndo || !isUndoableVehicleTarget(target)) return;
  state.pendingUndoSnapshot = snapshotVehicleState("edit");
}

function commitUndoBaseline(label = "edit") {
  if (state.suppressUndo) return;
  pushUndoSnapshot(state.pendingUndoSnapshot || snapshotVehicleState(label));
  state.pendingUndoSnapshot = snapshotVehicleState(label);
}

function isUndoableVehicleTarget(target) {
  return Boolean(target?.closest?.("#config-form [data-config-path], #config-form [data-array-path]"));
}

function shouldUseNativeUndo(event) {
  const editable = event.target?.closest?.("textarea, input:not([type='checkbox']), [contenteditable='true']");
  return Boolean(editable?.closest?.("#config-form, #geometry-point-editor, #config-text, #tir-editor"));
}

function updateDirtyState() {
  const data = currentVehicleFormData();
  const signature = data ? vehicleDataSignature(data) : "";
  state.dirtyVehicle = Boolean(signature && signature !== state.cleanVehicleSignature);
  document.getElementById("save-status").textContent = state.dirtyVehicle ? "Unsaved" : "Saved";
}

function applyVehicleDataToPayload(data) {
  if (!state.vehiclePayload) return;
  const nextData = cloneData(data);
  state.vehiclePayload = {
    ...state.vehiclePayload,
    data: nextData,
    fields: (state.vehiclePayload.fields || []).map((field) => {
      const value = nestedValue(nextData, field.path || []);
      return {
        ...field,
        value: cloneData(value),
        array_shape: Array.isArray(value) ? valueArrayShape(value) : field.array_shape,
      };
    }),
  };
}

function valueArrayShape(value) {
  if (!Array.isArray(value)) return [];
  if (!value.length || !Array.isArray(value[0])) return [value.length];
  return [value.length, Math.max(0, ...value.map((row) => Array.isArray(row) ? row.length : 0))];
}

function undoVehicleEdit() {
  const snapshot = state.undoStack.pop();
  if (!snapshot) return false;
  state.suppressUndo = true;
  applyVehicleDataToPayload(snapshot.data);
  state.activeParamGroup = snapshot.activeParamGroup || state.activeParamGroup;
  state.geometrySelectedPointId = snapshot.geometrySelectedPointId || null;
  state.geometryAxis = snapshot.geometryAxis || state.geometryAxis;
  state.pendingUndoSnapshot = null;
  state.suppressUndo = false;
  state.dirtyVehicle = vehicleDataSignature(snapshot.data) !== state.cleanVehicleSignature;
  renderSetup();
  return true;
}

function handleUndoShortcut(event) {
  if (!(event.ctrlKey || event.metaKey) || event.shiftKey || event.key.toLowerCase() !== "z") return;
  if (shouldUseNativeUndo(event)) return;
  if (state.view !== "setup") return;
  if (!undoVehicleEdit()) return;
  event.preventDefault();
}

function markVehicleDirty() {
  updateDirtyState();
  applyArchitectureVisibility();
  syncArchitectureDependentControls();
  renderArchitectureTemplateMatches();
  renderArchitectureConnectionModal();
  drawVehicleFromForm();
  renderParameterTabCanvases();
}

function buildParameterAreas(fields) {
  const buckets = Object.fromEntries(PARAMETER_AREAS.map((area) => [area.id, []]));
  fields.forEach((field) => {
    buckets[parameterAreaForField(field)].push(field);
  });
  return PARAMETER_AREAS
    .map((area) => ({ ...area, fields: buckets[area.id] || [] }))
    .filter((area) => area.always || area.fields.length);
}

function parameterAreaForField(field) {
  const path = fieldPathString(field);
  const group = String(field.group || "").toLowerCase();
  const label = String(field.label || "").toLowerCase();
  if (path.startsWith("aero.")) return "aero";
  if (fieldMatchesPowertrain(path, group, label)) return "powertrain";
  if (
    path.includes(".wheel.")
    || path.includes(".tire.")
    || group.includes("wheel")
    || label.includes("tire")
  ) {
    return "tires";
  }
  if (fieldMatchesCompliance(path, group, label)) return "compliances";
  if (path.includes("mass") || path.includes("inertia")) return "mass";
  if (fieldMatchesArchitectureSetup(path)) return "vehicle";
  if (fieldMatchesGeometry(path, field)) return "hardpoints";
  if (fieldMatchesSuspensionSetup(path, label)) return "suspension";
  if (
    path.includes(".suspension.")
    || path.includes(".steering.")
    || group.includes("hardpoint")
  ) {
    return "hardpoints";
  }
  return "vehicle";
}

function fieldPathString(field) {
  return (field.path || []).join(".").toLowerCase();
}

function fieldMatchesPowertrain(path, group, label) {
  const combined = `${path} ${group} ${label}`;
  return [
    "powertrain",
    "drivetrain",
    "motor",
    "battery",
    "inverter",
    "differential",
    "drive_distribution",
    "brake_distribution",
    "drive_power",
    "drive_force",
    "brake_force",
  ].some((token) => combined.includes(token));
}

function fieldMatchesGeometry(path, field) {
  const isVector = Array.isArray(field.array_shape) && field.array_shape.length === 1 && field.array_shape[0] === 3;
  if (!isVector) return false;
  return path.includes(".suspension.")
    || path.includes(".steering.")
    || (
      path.includes(".actuation.")
      && (path.endsWith("_m") || path.includes("pickups_m") || path.endsWith(".axis"))
    );
}

function fieldMatchesArchitectureSetup(path) {
  return path.endsWith(".actuation.rod_to")
    || path.endsWith(".actuation.bellcrank.order");
}

function fieldMatchesSuspensionSetup(path, label) {
  return path.endsWith(".actuation.shock.damper_model")
    || path.endsWith(".actuation.shock.dyno_reference")
    || path.endsWith(".actuation.shock.spring_table.table")
    || path.endsWith(".actuation.shock.free_length_m")
    || path.endsWith(".actuation.shock.damper_table.table")
    || path.endsWith(".actuation.stabar.rate_n_m_per_rad")
    || label.includes("spring")
    || label.includes("damper");
}

function fieldMatchesCompliance(path, group, label) {
  return path.startsWith("body.")
    || path.includes(".compliance")
    || path.includes("torsional_stiff")
    || group.includes("compliance")
    || label.includes("compliance")
    || label.includes("torsional stiffness");
}

function parameterAreaFields(area) {
  const extra = area.id === "tires"
    ? tireToolsHtml()
    : area.id === "vehicle"
      ? architectureToolsHtml(area.fields)
      : area.id === "powertrain"
        ? powertrainToolsHtml()
        : "";
  const fields = area.id === "vehicle"
    ? area.fields.filter((field) => !isArchitectureField(field) && !isArchitectureVisualOnlyField(field))
    : area.fields;
  if (!fields.length) {
    return `${extra}<div class="area-empty">${escapeHtml(emptyAreaCopy(area.id))}</div>`;
  }
  return `${extra}${fieldGroupSections(fields, area.id)}`;
}

function fieldGroupSections(fields, areaId = "") {
  const grouped = groupFields(fields);
  if (areaId === "suspension") {
    return suspensionFieldSections(grouped);
  }
  const buckets = { front: [], rear: [], shared: [] };
  Object.entries(grouped).forEach(([group, groupFields]) => {
    buckets[fieldGroupAxle(group, groupFields)].push([group, groupFields]);
  });
  const sections = [];
  if (buckets.front.length) sections.push(axleFieldBlock("front", buckets.front));
  if (buckets.rear.length) sections.push(axleFieldBlock("rear", buckets.rear));
  sections.push(...buckets.shared.map(([group, groupFields]) => fieldSubsectionHtml(group, groupFields)));
  return sections.join("");
}

function suspensionFieldSections(grouped) {
  const order = ["Front spring", "Front damper", "Front actuation", "Rear spring", "Rear damper", "Rear actuation"];
  const entries = Object.entries(grouped);
  return entries
    .sort(([left], [right]) => {
      const leftIndex = order.indexOf(left);
      const rightIndex = order.indexOf(right);
      return (leftIndex === -1 ? order.length : leftIndex) - (rightIndex === -1 ? order.length : rightIndex)
        || left.localeCompare(right);
    })
    .map(([group, groupFields]) => fieldSubsectionHtml(group, groupFields))
    .join("");
}

function axleFieldBlock(axle, grouped) {
  const count = grouped.reduce((total, [, fields]) => total + fields.length, 0);
  return `
    <section class="axle-field-block field-group-${axle}" data-axle-block="${escapeHtml(axle)}">
      <div class="axle-field-title">
        <span>${humanizeToken(axle)} axle</span>
        <small>${count}</small>
      </div>
      <div class="axle-field-groups">
        ${grouped.map(([group, fields]) => fieldSubsectionHtml(group, fields, { nested: true })).join("")}
      </div>
    </section>
  `;
}

function fieldSubsectionHtml(group, fields, { nested = false } = {}) {
  return `
    <section class="field-subsection expanded ${fieldGroupClass(group)}${nested ? " nested-subsection" : ""}">
      <div class="field-subsection-title">
        <span>${escapeHtml(humanizeToken(group))}</span>
        <small>${fields.length}</small>
      </div>
      <div class="field-grid">${fields.map(fieldControl).join("")}</div>
    </section>
  `;
}

function fieldGroupAxle(group, fields) {
  const groupName = String(group || "").toLowerCase();
  const samplePath = fieldPathString(fields[0] || {});
  if (groupName.includes("front") || samplePath.startsWith("front.")) return "front";
  if (groupName.includes("rear") || samplePath.startsWith("rear.")) return "rear";
  return "shared";
}

function fieldGroupClass(group) {
  const name = String(group || "").toLowerCase();
  if (name.includes("actuation") || name.includes("shock") || name.includes("stabar") || name.includes("spring") || name.includes("damper")) return "field-group-actuation";
  if (name.includes("hardpoint")) return "field-group-hardpoints";
  if (name.includes("compliance") || name.includes("body")) return "field-group-compliance";
  if (name.includes("front")) return "field-group-front";
  if (name.includes("rear")) return "field-group-rear";
  if (name.includes("mass") || name.includes("body") || name.includes("driver")) return "field-group-mass";
  return "field-group-general";
}

function isArchitectureField(field) {
  return fieldPathString(field).startsWith("architecture.");
}

function isArchitectureVisualOnlyField(field) {
  return fieldPathString(field).endsWith(".actuation.bellcrank.order");
}

function architectureToolsHtml(fields) {
  const frontField = fields.find((field) => fieldPathString(field) === "architecture.front");
  const rearField = fields.find((field) => fieldPathString(field) === "architecture.rear");
  const powertrains = availablePowertrains();
  const activePowertrain = powertrainProfile(state.vehiclePayload?.data || {}).id;
  const hiddenOrderFields = fields
    .filter(isArchitectureVisualOnlyField)
    .map((field) => `<div hidden>${fieldControl(field)}</div>`)
    .join("");
  return `
    <div class="architecture-tools" data-architecture-tools>
      <div class="architecture-control-grid">
        ${architectureSelectHtml(frontField, "architecture-front-select", "Front")}
        ${architectureSelectHtml(rearField, "architecture-rear-select", "Rear")}
        <label class="form-field compact-field">
          <span>Powertrain</span>
          <select id="architecture-powertrain-select" data-setup-filter>
            ${powertrains.map((item) => `
              <option value="${escapeHtml(item.id)}"${item.id === activePowertrain ? " selected" : ""}>${escapeHtml(item.label)}</option>
            `).join("")}
          </select>
        </label>
      </div>
      <div class="architecture-match-head">
        <span>Templates</span>
        <strong id="architecture-match-count"></strong>
      </div>
      <div id="architecture-template-list" class="architecture-template-list"></div>
    </div>
    ${hiddenOrderFields}
  `;
}

function architectureSelectHtml(field, id, label) {
  if (!field) return "";
  const choices = field.choices?.length ? field.choices : ["direct", "bellcrank", "bellcrank_stabar"];
  return `
    <label class="form-field compact-field">
      <span>${escapeHtml(label)}</span>
      <select id="${escapeHtml(id)}" data-config-path="${escapeHtml(field.key)}" data-kind="${escapeHtml(field.kind)}">
        ${choices.map((choice) => `
          <option value="${escapeHtml(choice)}"${choice === field.value ? " selected" : ""}>${escapeHtml(humanizeToken(choice))}</option>
        `).join("")}
      </select>
    </label>
  `;
}

function powertrainToolsHtml() {
  const profile = powertrainProfile(state.vehiclePayload?.data || {});
  return `
    <div class="powertrain-tools" data-setup-filter>
      <div>
        <span class="tool-label">Implementation</span>
        <strong>${escapeHtml(profile.label)}</strong>
      </div>
      <span class="mini-pill ok">${escapeHtml(humanizeToken(profile.status))}</span>
    </div>
  `;
}

function availablePowertrains() {
  return state.vehicleTemplates?.powertrains?.length
    ? state.vehicleTemplates.powertrains
    : [{ id: "EVBatInvMotDiff", label: "EV battery/inverter/motor/differential", status: "implemented", components: ["Battery", "Inverter", "Motor", "Differential"] }];
}

function wireArchitectureTools() {
  const tools = document.querySelector("[data-architecture-tools]");
  if (!tools) return;
  tools.querySelectorAll("select").forEach((select) => {
    select.addEventListener("change", renderArchitectureTemplateMatches);
  });
  tools.querySelector("#architecture-template-list")?.addEventListener("click", (event) => {
    const button = event.target.closest("[data-template-apply]");
    const picker = document.getElementById("architecture-template-picker");
    if (button && picker?.value) applyVehicleTemplate(picker.value);
  });
}

function renderArchitectureTemplateMatches() {
  const list = document.getElementById("architecture-template-list");
  const count = document.getElementById("architecture-match-count");
  if (!list) return;
  const front = document.getElementById("architecture-front-select")?.value || state.vehiclePayload?.data?.architecture?.front;
  const rear = document.getElementById("architecture-rear-select")?.value || state.vehiclePayload?.data?.architecture?.rear;
  const powertrain = document.getElementById("architecture-powertrain-select")?.value || powertrainProfile(state.vehiclePayload?.data || {}).id;
  const templates = (state.vehicleTemplates?.templates || []).filter((template) => (
    (!front || template.front === front)
    && (!rear || template.rear === rear)
    && (!powertrain || template.powertrain === powertrain)
  ));
  if (count) count.textContent = String(templates.length);
  if (!templates.length) {
    list.innerHTML = `<div class="area-empty">No matching template is available.</div>`;
    return;
  }
  list.innerHTML = `
    <select id="architecture-template-picker" class="config-picker compact-picker">
      ${templates.map((template) => `
        <option value="${escapeHtml(template.id)}">${escapeHtml(templateArchitectureLabel(template))}</option>
      `).join("")}
    </select>
    <button class="ghost-button" type="button" data-template-apply>Apply</button>
  `;
}

function templateArchitectureLabel(template) {
  return `${humanizeToken(template.front)} front / ${humanizeToken(template.rear)} rear`;
}

function tireToolsHtml() {
  return `
    <div class="tir-tools" data-tir-tools>
      <div class="tir-tools-head">
        <select id="tir-template-picker" class="config-picker"></select>
        <label class="file-import">
          <input id="tir-import-input" type="file" accept=".tir">
          <span>Import .tir</span>
        </label>
        <button id="save-tir-btn" class="ghost-button" type="button">Save .tir</button>
      </div>
      <div class="tir-apply-row">
        <span id="tir-editor-meta"></span>
        <button class="ghost-button" type="button" data-apply-tir="front">Use Front</button>
        <button class="ghost-button" type="button" data-apply-tir="rear">Use Rear</button>
        <button class="run-button" type="button" data-apply-tir="both">Use Both</button>
      </div>
      <textarea id="tir-editor" class="tir-editor" spellcheck="false"></textarea>
    </div>
  `;
}

function emptyAreaCopy(areaId) {
  return {
    powertrain: "No powertrain block is present in vehicle.yml yet.",
    aero: "No aero block is present in vehicle.yml yet.",
    suspension: "No spring, damper, or suspension actuation fields are present in this vehicle config.",
    compliances: "No compliance fields are present in this vehicle config yet.",
  }[areaId] || "No fields are available in this setup area.";
}

function applyArchitectureVisibility() {
  const data = currentVehicleFormData() || state.vehiclePayload?.data || {};
  document.querySelectorAll("[data-field-wrapper]").forEach((wrapper) => {
    wrapper.hidden = !fieldVisibleForArchitecture(wrapper.dataset.fieldPath, data);
  });
  document.querySelectorAll(".field-subsection").forEach((section) => {
    const wrappers = Array.from(section.querySelectorAll("[data-field-wrapper]"));
    section.hidden = wrappers.length > 0 && wrappers.every((wrapper) => wrapper.hidden);
  });
  applyAxleInputVisibility();
}

function fieldVisibleForArchitecture(path, data) {
  const parts = String(path || "").split(".");
  const axle = parts[0];
  if (!["front", "rear"].includes(axle)) return true;
  const architecture = String(data.architecture?.[axle] || "");
  if (path.includes(".actuation.bellcrank.")) return architecture.includes("bellcrank");
  if (path.includes(".actuation.stabar.")) return architecture.includes("stabar");
  return true;
}

function applyAxleInputVisibility(area = activeParameterArea()) {
  const visible = new Set(area.id === "hardpoints" ? visibleGeometryAxles() : ["front", "rear"]);
  document.querySelectorAll("[data-axle-block]").forEach((block) => {
    block.hidden = !visible.has(block.dataset.axleBlock);
  });
}

function syncArchitectureDependentControls(data = currentVehicleFormData() || state.vehiclePayload?.data || {}) {
  document.querySelectorAll("[data-array-path]").forEach((container) => {
    const path = JSON.parse(container.dataset.arrayPath || "[]");
    const choices = bellcrankOrderChoicesForPath(path, data);
    if (choices) syncChoiceArray(container, choices);
  });
}

function bellcrankOrderChoicesForPath(path, data) {
  if (
    path.length !== 4
    || !["front", "rear"].includes(path[0])
    || path.slice(1).join(".") !== "actuation.bellcrank.order"
  ) {
    return null;
  }
  const architecture = String(data.architecture?.[path[0]] || "");
  return architecture.includes("stabar") ? ["rod", "shock", "stabar"] : ["rod", "shock"];
}

function syncChoiceArray(container, choices) {
  const cells = container.querySelector(".array-inline-cells");
  if (!cells) return;
  while (cells.children.length < choices.length) {
    const index = cells.children.length;
    cells.insertAdjacentHTML("beforeend", `
      <label class="array-list-row array-cell">
        <span>${escapeHtml(vectorAxisLabel(index, 0))}</span>
        ${arrayCellInputHtml("string", { index }, choices[index], choices)}
      </label>
    `);
  }
  while (cells.children.length > choices.length) {
    cells.lastElementChild?.remove();
  }
  Array.from(cells.children).forEach((cell, index) => {
    const label = cell.querySelector("span");
    const select = cell.querySelector("[data-array-cell]");
    if (label) label.textContent = vectorAxisLabel(index, 0);
    if (!select) return;
    const current = choices.includes(select.value) ? select.value : choices[index] || choices[0];
    select.dataset.index = String(index);
    delete select.dataset.row;
    delete select.dataset.col;
    select.innerHTML = choices
      .map((choice) => `<option value="${escapeHtml(choice)}"${choice === current ? " selected" : ""}>${escapeHtml(choice)}</option>`)
      .join("");
  });
}

function groupFields(fields) {
  return fields.reduce((groups, field) => {
    const group = fieldDisplayGroup(field);
    groups[group] ||= [];
    groups[group].push(field);
    return groups;
  }, {});
}

function fieldDisplayGroup(field) {
  const path = fieldPathString(field);
  const axle = field.path?.[0] === "front" ? "Front" : field.path?.[0] === "rear" ? "Rear" : "";
  if (axle && path.includes(".actuation.shock.spring_table.")) return `${axle} spring`;
  if (axle && path.includes(".actuation.shock.damper_table.")) return `${axle} damper`;
  return field.group || field.path?.[0] || "Vehicle";
}

function renderParameterTabs(areas) {
  const tabs = document.getElementById("parameter-tabs");
  tabs.innerHTML = areas.map((area, index) => `
    <button class="parameter-tab ${area.id === state.activeParamGroup ? "active" : ""}" data-param-group="${escapeHtml(area.id)}" type="button" title="${escapeHtml(setupGuide(area.id).focus)}">
      <span class="step-number">${String(index + 1).padStart(2, "0")}</span>
      <span class="step-name">${escapeHtml(setupGuide(area.id).title)}</span>
    </button>
  `).join("");
  tabs.querySelectorAll("[data-param-group]").forEach((button) => {
    button.addEventListener("click", () => activateParameterGroup(button.dataset.paramGroup));
  });
}

function activateParameterGroup(group) {
  state.referenceOpen = false;
  state.activeParamGroup = group;
  renderSetupFocus();
  document.querySelectorAll(".parameter-tab").forEach((button) => {
    button.classList.toggle("active", button.dataset.paramGroup === group);
  });
  document.querySelectorAll(".config-section").forEach((section) => {
    section.classList.toggle("active", section.dataset.paramGroup === group);
  });
  drawVehicleFromForm();
}

function toggleReferencePanel() {
  state.referenceOpen = !state.referenceOpen;
  renderWorkflowGuide();
}

function renderParameterTabCanvases() {
  const data = currentVehicleFormData();
  requestAnimationFrame(() => {
    document.querySelectorAll(".section-preview").forEach((canvas) => {
      drawMiniVehiclePreview(canvas, data, canvas.dataset.paramPreview);
    });
  });
}

function fieldControl(field) {
  const disabled = Boolean(field.disabled);
  const disabledAttr = disabled ? " disabled" : "";
  const attrs = `data-config-path="${escapeHtml(field.key)}" data-kind="${escapeHtml(field.kind)}"${disabledAttr}`;
  const label = fieldLabelHtml(field);
  const value = field.value;
  const wrapperAttrs = fieldWrapperAttrs(field);
  if (isArrayField(field)) return arrayFieldControl(field, label);
  if (field.kind === "boolean") {
    return `<div class="form-field toggle-field ${disabled ? "disabled-field" : ""}" ${wrapperAttrs}>${label}<input ${attrs} type="checkbox"${value ? " checked" : ""}>${fieldHelpHtml(field)}</div>`;
  }
  if (field.kind === "number" || field.kind === "integer") {
    const step = field.kind === "integer" ? "1" : "any";
    return `<div class="form-field ${disabled ? "disabled-field" : ""}" ${wrapperAttrs}>${label}<input ${attrs} type="number" step="${step}"${disabled ? "" : " required"} value="${escapeHtml(value ?? "")}">${fieldHelpHtml(field)}</div>`;
  }
  if (field.kind === "select") {
    const choices = field.choices.includes(value) ? field.choices : [value, ...field.choices].filter(Boolean);
    return `
      <div class="form-field ${disabled ? "disabled-field" : ""}" ${wrapperAttrs}>
        ${label}
        <select ${attrs}>
          ${choices.map((choice) => `<option value="${escapeHtml(choice)}"${choice === value ? " selected" : ""}>${escapeHtml(choice)}</option>`).join("")}
        </select>
        ${fieldHelpHtml(field)}
      </div>
    `;
  }
  if (field.kind === "list" || field.kind === "json") {
    return `
      <div class="form-field ${disabled ? "disabled-field" : ""}" ${wrapperAttrs}>
        ${label}
        <textarea ${attrs}>${escapeHtml(JSON.stringify(value, null, 2))}</textarea>
        ${fieldHelpHtml(field)}
      </div>
    `;
  }
  return `<div class="form-field ${disabled ? "disabled-field" : ""}" ${wrapperAttrs}>${label}<input ${attrs} type="text" value="${escapeHtml(value ?? "")}">${fieldHelpHtml(field)}</div>`;
}

function fieldLabelHtml(field) {
  const unit = field.unit ? `<span>${escapeHtml(field.unit)}</span>` : "";
  const planned = field.disabled ? `<span class="field-status-pill">Planned</span>` : "";
  const meta = unit || planned ? `<span class="field-label-meta">${unit}${planned}</span>` : "";
  const objectLabel = fieldObjectLabel(field);
  const object = objectLabel ? `<span class="field-object-label">${escapeHtml(objectLabel)}</span>` : "";
  return `${object}<label><span>${escapeHtml(fieldPropertyLabel(field))}</span>${meta}</label>`;
}

function fieldHelpHtml(field) {
  const help = field.disabled ? field.placeholder : fieldHelpText(field);
  return help
    ? `<small class="field-placeholder-note">${escapeHtml(help)}</small>`
    : "";
}

function fieldHelpText(field) {
  const path = fieldPathString(field);
  if (path.includes(".actuation.shock.spring_table.table")) return "Rows map shock deflection to spring force.";
  if (path.includes(".actuation.shock.damper_table.table")) return "Rows map shock shaft velocity to damper force.";
  return field.help;
}

function fieldObjectLabel(field) {
  const path = field.path || [];
  if (path[0] === "sprung_mass") return "Sprung mass";
  if (path[0] === "driver_mass") return "Driver mass";
  if ((path[0] === "front" || path[0] === "rear") && path[1] === "masses" && path[2]) {
    return `${humanizeToken(path[0])} ${humanizeToken(path[2])}`;
  }
  return "";
}

function fieldPropertyLabel(field) {
  const path = field.path || [];
  const pathString = fieldPathString(field);
  if (pathString.includes(".actuation.shock.spring_table.table")) return "Spring force curve";
  if (pathString.includes(".actuation.shock.damper_table.table")) return "Damper force curve";
  if (fieldObjectLabel(field)) {
    return {
      mass_kg: "Mass",
      cg_m: "CG",
      inertia_kg_m2: "Inertia",
    }[path[path.length - 1]] || field.label;
  }
  return field.label;
}

function fieldWrapperAttrs(field) {
  return `data-field-wrapper data-field-path="${escapeHtml(fieldPathString(field))}"${field.disabled ? ` data-field-disabled="true"` : ""}`;
}

function isArrayField(field) {
  return Array.isArray(field.value)
    && Array.isArray(field.array_shape)
    && field.array_shape.length > 0
    && field.array_element_kind !== "mixed";
}

function arrayFieldControl(field, label) {
  const rank = field.array_shape.length;
  const elementKind = field.array_element_kind || "string";
  const attrs = `data-array-path="${escapeHtml(field.key)}" data-array-rank="${rank}" data-array-element-kind="${escapeHtml(elementKind)}"${field.disabled ? ` data-field-disabled="true"` : ""}`;
  const control = rank === 2 ? matrixControl(field) : vectorControl(field);
  return `<div class="form-field array-field ${field.disabled ? "disabled-field" : ""}" ${fieldWrapperAttrs(field)} ${attrs}>${label}${control}${fieldHelpHtml(field)}</div>`;
}

function vectorControl(field) {
  const values = Array.isArray(field.value) ? field.value : [];
  const coordinate = isNumericArrayKind(field.array_element_kind) && values.length === 3;
  const displayValues = values.length ? values : Array.from({ length: isNumericArrayKind(field.array_element_kind) ? 3 : 0 }, () => "");
  const cells = displayValues.map((value, index) => vectorCell(field, value, index, coordinate)).join("");
  return `
    <div class="array-literal ${coordinate ? "coordinate-input" : "array-list-input"}" data-array-list>
      <span class="array-bracket">[</span>
      <div class="array-inline-cells">
        ${cells}
      </div>
      <span class="array-bracket">]</span>
    </div>
  `;
}

function vectorCell(field, value, index, coordinate) {
  const axisLabel = vectorAxisLabel(index, coordinate ? 3 : 0);
  return `
    <label class="${coordinate ? "coordinate-cell" : "array-list-row"} array-cell">
      <span>${escapeHtml(axisLabel)}</span>
      ${arrayScalarControl(field, value, { index })}
    </label>
  `;
}

function matrixControl(field) {
  const rows = Array.isArray(field.value) ? field.value : [];
  const cols = Math.max(1, ...rows.map((row) => Array.isArray(row) ? row.length : 0));
  const fixed = matrixHasFixedShape(field);
  const body = rows.map((row, rowIndex) => matrixRowControl(field, row, rowIndex, cols, fixed)).join("");
  return `
    ${matrixPurposeHtml(field)}
    <div class="matrix-scroll">
      <div class="matrix-input" data-matrix-cols="${cols}">
        <div class="matrix-array-body">${body}</div>
      </div>
    </div>
    ${fixed ? "" : `<button class="array-action" type="button" data-array-action="add-row">Add row</button>`}
  `;
}

function matrixPurposeHtml(field) {
  const path = fieldPathString(field);
  if (path.includes(".actuation.shock.spring_table.table")) {
    return `
      <div class="table-purpose">
        <strong>Spring table</strong>
        <span>Shock deflection (m) -> spring force (N)</span>
      </div>
    `;
  }
  if (path.includes(".actuation.shock.damper_table.table")) {
    return `
      <div class="table-purpose">
        <strong>Damper table</strong>
        <span>Shock shaft velocity (m/s) -> damper force (N)</span>
      </div>
    `;
  }
  return "";
}

function matrixRowControl(field, row, rowIndex, cols, fixed) {
  const cells = Array.from({ length: cols }, (_, colIndex) => {
    const value = Array.isArray(row) ? row[colIndex] : "";
    return `
      <label class="matrix-array-cell array-cell">
        <span>${escapeHtml(matrixColumnLabel(field, colIndex))}</span>
        ${arrayScalarControl(field, value, { row: rowIndex, col: colIndex })}
      </label>
    `;
  }).join("");
  return `
    <div class="matrix-array-row" data-matrix-row>
      <span class="matrix-row-label">${escapeHtml(matrixRowLabel(field, rowIndex))}</span>
      <span class="array-bracket">[</span>
      <div class="matrix-array-cells">${cells}</div>
      <span class="array-bracket">]</span>
      ${fixed ? "" : `<button class="array-icon-button" type="button" data-array-action="remove-row" aria-label="Remove row">-</button>`}
    </div>
  `;
}

function vectorAxisLabel(index, length) {
  if (length === 3) return ["x", "y", "z"][index] || String(index + 1);
  return `#${index + 1}`;
}

function matrixHasFixedShape(field) {
  const path = fieldPathString(field);
  return path.startsWith("aero.")
    || path.endsWith("inertia_kg_m2")
    || path.includes("drag_table")
    || path.includes("downforce_table")
    || path.includes("_table_nm");
}

function matrixColumnLabel(field, index) {
  const path = fieldPathString(field);
  if (path.includes("spring_table")) return ["Deflection (m)", "Force (N)"][index] || `C${index + 1}`;
  if (path.includes("damper_table")) return ["Shaft velocity (m/s)", "Force (N)"][index] || `C${index + 1}`;
  if (path.endsWith("inertia_kg_m2")) return ["X", "Y", "Z"][index] || `C${index + 1}`;
  return `C${index + 1}`;
}

function matrixRowLabel(field, index) {
  return fieldPathString(field).endsWith("inertia_kg_m2") ? ["X", "Y", "Z"][index] || `R${index + 1}` : `R${index + 1}`;
}

function isNumericArrayKind(kind) {
  return kind === "number" || kind === "integer";
}

function arrayScalarControl(field, value, position) {
  return arrayCellInputHtml(field.array_element_kind, position, value, Array.isArray(field.choices) ? field.choices : []);
}

function arrayCellInputHtml(kind, position, value = "", choices = []) {
  const positionAttrs = position.col === undefined
    ? `data-index="${position.index}"`
    : `data-row="${position.row}" data-col="${position.col}"`;
  const attrs = `data-array-cell ${positionAttrs}`;
  if (choices.length) {
    const options = (choices.includes(value) ? choices : [value, ...choices].filter(Boolean))
      .map((choice) => `<option value="${escapeHtml(choice)}"${choice === value ? " selected" : ""}>${escapeHtml(choice)}</option>`)
      .join("");
    return `<select ${attrs}>${options}</select>`;
  }
  if (kind === "boolean") {
    return `<input ${attrs} type="checkbox"${value ? " checked" : ""}>`;
  }
  if (kind === "number" || kind === "integer") {
    const step = kind === "integer" ? "1" : "any";
    return `<input ${attrs} type="number" step="${step}" required value="${escapeHtml(value ?? "")}">`;
  }
  return `<input ${attrs} type="text" value="${escapeHtml(value ?? "")}">`;
}

function defaultArrayValue(kind) {
  if (kind === "boolean") return false;
  if (kind === "number" || kind === "integer") return "";
  return "";
}

function handleArrayEditorClick(event) {
  const button = event.target.closest("[data-array-action]");
  if (!button) return;
  const container = button.closest("[data-array-path]");
  if (!container) return;
  event.preventDefault();
  const action = button.dataset.arrayAction;
  pushUndoSnapshot(snapshotVehicleState(`array-${action}`));
  if (action === "add-item") addArrayItem(container);
  else if (action === "remove-item") removeArrayItem(button, container);
  else if (action === "add-row") addMatrixRow(container);
  else if (action === "remove-row") removeMatrixRow(button, container);
  renumberArrayEditor(container);
  markVehicleDirty();
}

function addArrayItem(container) {
  const list = container.querySelector("[data-array-list]");
  if (!list) return;
  const kind = container.dataset.arrayElementKind || "number";
  const cells = list.querySelector(".array-inline-cells");
  if (!cells) return;
  const index = cells.querySelectorAll(".array-list-row").length;
  cells.insertAdjacentHTML("beforeend", `
    <label class="array-list-row array-cell">
      <span>#${index + 1}</span>
      ${arrayCellInputHtml(kind, { index }, defaultArrayValue(kind))}
    </label>
  `);
}

function removeArrayItem(button, container) {
  const rows = Array.from(container.querySelectorAll(".array-list-row"));
  if (rows.length <= 1) return;
  button.closest(".array-list-row")?.remove();
}

function addMatrixRow(container) {
  const body = container.querySelector(".matrix-array-body");
  if (!body) return;
  const table = container.querySelector(".matrix-input");
  const kind = container.dataset.arrayElementKind || "number";
  const cols = Math.max(1, Number(table?.dataset.matrixCols || matrixColumnCount(container) || 2));
  const rowIndex = body.querySelectorAll("[data-matrix-row]").length;
  const labels = matrixColumnLabelsFromDom(container, cols);
  const cells = Array.from({ length: cols }, (_, col) => `
    <label class="matrix-array-cell array-cell">
      <span>${escapeHtml(labels[col])}</span>
      ${arrayCellInputHtml(kind, { row: rowIndex, col }, defaultArrayValue(kind))}
    </label>
  `).join("");
  body.insertAdjacentHTML("beforeend", `
    <div class="matrix-array-row" data-matrix-row>
      <span class="matrix-row-label">R${rowIndex + 1}</span>
      <span class="array-bracket">[</span>
      <div class="matrix-array-cells">
      ${cells}
      </div>
      <span class="array-bracket">]</span>
      <button class="array-icon-button" type="button" data-array-action="remove-row" aria-label="Remove row">-</button>
    </div>
  `);
}

function removeMatrixRow(button, container) {
  const rows = Array.from(container.querySelectorAll("[data-matrix-row]"));
  if (rows.length <= 1) return;
  button.closest("[data-matrix-row]")?.remove();
}

function matrixColumnCount(container) {
  const row = container.querySelector("[data-matrix-row]");
  if (!row) return 0;
  return row.querySelectorAll("[data-array-cell]").length;
}

function matrixColumnLabelsFromDom(container, cols) {
  const labels = Array.from(container.querySelectorAll(".matrix-array-row:first-child .matrix-array-cell > span"))
    .map((label) => label.textContent.trim())
    .filter(Boolean);
  return Array.from({ length: cols }, (_, index) => labels[index] || `C${index + 1}`);
}

function renumberArrayEditor(container) {
  const vectorRows = Array.from(container.querySelectorAll(".array-list-row"));
  vectorRows.forEach((row, index) => {
    const label = row.querySelector("span");
    if (label) label.textContent = `#${index + 1}`;
    const input = row.querySelector("[data-array-cell]");
    if (input) {
      input.dataset.index = String(index);
      delete input.dataset.row;
      delete input.dataset.col;
    }
  });
  vectorRows.forEach((row) => {
    const removeButton = row.querySelector('[data-array-action="remove-item"]');
    if (removeButton) removeButton.disabled = vectorRows.length <= 1;
  });

  const matrixRows = Array.from(container.querySelectorAll("[data-matrix-row]"));
  matrixRows.forEach((row, rowIndex) => {
    row.dataset.matrixRow = String(rowIndex);
    const label = row.querySelector(".matrix-row-label");
    if (label && /^R\s*\d+$/i.test(label.textContent.trim())) label.textContent = `R${rowIndex + 1}`;
    row.querySelectorAll("[data-array-cell]").forEach((input, colIndex) => {
      input.dataset.row = String(rowIndex);
      input.dataset.col = String(colIndex);
      delete input.dataset.index;
    });
  });
  matrixRows.forEach((row) => {
    const removeButton = row.querySelector('[data-array-action="remove-row"]');
    if (removeButton) removeButton.disabled = matrixRows.length <= 1;
  });
}

function collectVehicleValues({ reportInvalid = false } = {}) {
  return collectConfigValues("#config-form", { reportInvalid });
}

function collectSimConfigValues({ reportInvalid = false } = {}) {
  return collectConfigValues("#sim-config-form", { reportInvalid });
}

function collectConfigValues(rootSelector, { reportInvalid = false } = {}) {
  const values = {};
  document.querySelectorAll(`${rootSelector} [data-array-path]:not([data-field-disabled='true'])`).forEach((container) => {
    values[container.dataset.arrayPath] = collectArrayValue(container, reportInvalid);
  });
  document.querySelectorAll(`${rootSelector} [data-config-path]:not(:disabled)`).forEach((input) => {
    values[input.dataset.configPath] = collectPrimitiveValue(input, reportInvalid);
  });
  return values;
}

function collectArrayValue(container, reportInvalid) {
  const rank = Number(container.dataset.arrayRank || "1");
  const kind = container.dataset.arrayElementKind || "string";
  if (rank === 2) {
    const rows = [];
    container.querySelectorAll("[data-array-cell]").forEach((input) => {
      const row = Number(input.dataset.row);
      const col = Number(input.dataset.col);
      rows[row] ||= [];
      rows[row][col] = collectScalarValue(input, kind, reportInvalid);
    });
    return rows;
  }
  const values = [];
  container.querySelectorAll("[data-array-cell]").forEach((input) => {
    values[Number(input.dataset.index)] = collectScalarValue(input, kind, reportInvalid);
  });
  return values;
}

function collectPrimitiveValue(input, reportInvalid) {
  const kind = input.dataset.kind;
  if (kind === "boolean") return input.checked;
  if (kind === "number" || kind === "integer") return collectScalarValue(input, kind, reportInvalid);
  if (kind === "list" || kind === "json") return input.value.trim() ? JSON.parse(input.value) : [];
  return input.value;
}

function collectScalarValue(input, kind, reportInvalid) {
  input.setCustomValidity("");
  if (kind === "boolean") return input.checked;
  if (kind === "number" || kind === "integer") {
    const rawValue = input.value.trim();
    const number = Number(rawValue);
    const isValidInteger = kind !== "integer" || Number.isInteger(number);
    if (!rawValue || !Number.isFinite(number) || !isValidInteger || !input.checkValidity()) {
      input.setCustomValidity(kind === "integer" ? "Enter a whole number." : "Enter a number.");
      if (reportInvalid) input.reportValidity();
      throw new Error("Fix invalid numeric entries before saving.");
    }
    return kind === "integer" ? Number.parseInt(rawValue, 10) : number;
  }
  return input.value;
}

async function saveVehicleEdits() {
  let values;
  try {
    values = collectVehicleValues({ reportInvalid: true });
  } catch (error) {
    document.getElementById("save-status").textContent = error.message;
    return null;
  }
  const payload = await api("/api/configs/vehicle", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ mode: "patch", values }),
  });
  state.vehiclePayload = payload;
  acceptCleanVehiclePayload();
  await refreshTirePayload();
  renderSetup();
  return payload;
}

async function saveVehicleAs() {
  const payload = await saveVehicleEdits();
  if (!payload) return;
  const name = document.getElementById("save-vehicle-name").value || activeVehicleName();
  state.vehicleLibrary = await api("/api/vehicles/save", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ name }),
  });
  state.selectedVehicleSource = state.vehicleLibrary.saved?.id || "active";
  renderSetup();
}

async function saveRawVehicle() {
  const payload = await api("/api/configs/vehicle", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ mode: "raw", text: document.getElementById("config-text").value }),
  });
  state.vehiclePayload = payload;
  acceptCleanVehiclePayload();
  state.vehicleLibrary = await api("/api/vehicles");
  await refreshTirePayload();
  renderSetup();
}

async function loadVehicleSource() {
  const sourceId = document.getElementById("vehicle-library-picker").value;
  await loadVehicleSourceById(sourceId);
}

async function loadVehicleSourceById(sourceId) {
  state.vehiclePayload = await api("/api/vehicles/load", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ source_id: sourceId }),
  });
  acceptCleanVehiclePayload();
  state.vehicleLibrary = await api("/api/vehicles");
  await refreshTirePayload();
  state.selectedVehicleSource = "active";
  renderSetup();
}

async function loadVehicleFromStart() {
  const sourceId = document.getElementById("start-load-picker")?.value;
  if (!sourceId) return;
  state.vehicleStartOpen = false;
  await loadVehicleSourceById(sourceId);
  render();
}

async function createVehicleFromStart() {
  const templateId = document.getElementById("start-template-picker")?.value;
  const name = document.getElementById("start-vehicle-name")?.value.trim() || nextVehicleName();
  if (!templateId) return;
  state.vehiclePayload = await api("/api/vehicle-template", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ template_id: templateId }),
  });
  state.vehiclePayload = await api("/api/configs/vehicle", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({
      mode: "patch",
      values: { [JSON.stringify(["vehicle", "name"])]: name },
    }),
  });
  acceptCleanVehiclePayload();
  state.vehicleLibrary = await api("/api/vehicles/save", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ name }),
  });
  await refreshTirePayload();
  await refreshTireTemplates();
  if (state.tireTemplates?.templates?.length) {
    await loadTirTemplate(defaultTirTemplateName());
  }
  state.selectedVehicleSource = state.vehicleLibrary.saved?.id || "active";
  state.vehicleStartOpen = false;
  const saveName = document.getElementById("save-vehicle-name");
  if (saveName) saveName.value = name;
  render();
}

async function importVehicleFile(file) {
  if (!file) return;
  const text = await file.text();
  state.vehiclePayload = await api("/api/configs/vehicle", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ mode: "raw", text }),
  });
  acceptCleanVehiclePayload();
  state.vehicleLibrary = await api("/api/vehicles");
  state.vehicleTemplates = await api("/api/vehicle-templates");
  await refreshTirePayload();
  await refreshTireTemplates();
  if (state.tireTemplates?.templates?.length) {
    await loadTirTemplate(defaultTirTemplateName());
  }
  state.selectedVehicleSource = "active";
  state.vehicleStartOpen = false;
  document.getElementById("save-vehicle-name").value = file.name.replace(/\.(ya?ml)$/i, "");
  render();
}

async function applyVehicleTemplate(templateId) {
  if (!templateId) return;
  state.vehiclePayload = await api("/api/vehicle-template", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ template_id: templateId }),
  });
  acceptCleanVehiclePayload();
  state.vehicleLibrary = await api("/api/vehicles");
  await refreshTirePayload();
  await refreshTireTemplates();
  if (state.tireTemplates?.templates?.length) {
    await loadTirTemplate(defaultTirTemplateName());
  }
  state.selectedVehicleSource = "active";
  renderSetup();
}

async function deleteSelectedVehicleConfig() {
  const selected = selectedVehicleLibraryItem();
  if (selected?.type !== "saved") return;
  const confirmed = window.confirm(`Delete saved vehicle config "${selected.label}"?`);
  if (!confirmed) return;
  state.vehicleLibrary = await api("/api/vehicles/delete", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ source_id: selected.id }),
  });
  state.selectedVehicleSource = "active";
  renderSetup();
}

async function applySimConfigEdits() {
  if (!state.simConfigPayload) return null;
  let values;
  try {
    values = collectSimConfigValues({ reportInvalid: true });
  } catch (error) {
    const status = document.getElementById("sim-config-status");
    if (status) status.textContent = error.message;
    return null;
  }
  const payload = await api(`/api/configs/${encodeURIComponent(state.simConfigPayload.id)}`, {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ mode: "patch", values }),
  });
  state.simConfigPayload = payload;
  acceptCleanSimConfigPayload();
  renderSimSetup(selectedWorkflow());
  return payload;
}

async function saveSimConfigAs() {
  const workflow = selectedWorkflow();
  if (!workflow) return;
  const applied = await applySimConfigEdits();
  if (!applied) return;
  const name = document.getElementById("save-sim-config-name")?.value || `${workflow.label} setup`;
  const payload = await api("/api/sim-configs/save", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ workflow_id: workflow.id, name }),
  });
  state.simConfigLibrary = payload.library;
  state.selectedSimConfigSource = payload.saved?.id || state.selectedSimConfigSource;
  renderSimSetup(workflow);
}

async function loadSelectedSimConfig() {
  const sourceId = document.getElementById("sim-config-picker")?.value || state.selectedSimConfigSource;
  if (!sourceId) return;
  const payload = await api("/api/sim-configs/load", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ source_id: sourceId }),
  });
  state.simConfigPayload = payload.config;
  state.simConfigLibrary = payload.library;
  state.selectedSimConfigSource = payload.source?.id || sourceId;
  acceptCleanSimConfigPayload();
  renderStandard();
}

async function deleteSelectedSimConfig() {
  const selected = (state.simConfigLibrary?.sources || []).find((source) => source.id === state.selectedSimConfigSource);
  if (selected?.type !== "saved") return;
  const confirmed = window.confirm(`Delete saved run config "${selected.label}"?`);
  if (!confirmed) return;
  state.simConfigLibrary = await api("/api/sim-configs/delete", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ source_id: selected.id }),
  });
  state.selectedSimConfigSource = state.simConfigLibrary.sources?.[0]?.id || "";
  renderSimSetup(selectedWorkflow());
}

function defaultTirTemplateName() {
  const activeTemplate = state.vehiclePayload?.data?.front?.tire?.template
    || state.vehiclePayload?.data?.rear?.tire?.template;
  if (activeTemplate) return activeTemplate;
  return state.tireTemplates?.templates?.[0]?.id || "";
}

async function loadTirTemplate(name) {
  const template = name || defaultTirTemplateName();
  if (!template) return;
  state.activeTir = await api(`/api/tires/template?name=${encodeURIComponent(template)}`);
  renderTirEditorContent();
}

async function saveActiveTirTemplate() {
  const name = document.getElementById("tir-template-picker")?.value || state.activeTir?.id || defaultTirTemplateName();
  const text = document.getElementById("tir-editor")?.value || "";
  state.activeTir = await api("/api/tires/template", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ name, text }),
  });
  await refreshTireTemplates();
  await refreshTirePayload();
  renderTirEditorContent();
  drawVehicleFromForm();
}

async function importTirFile(file) {
  if (!file) return;
  const text = await file.text();
  state.activeTir = await api("/api/tires/import", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ name: file.name, text }),
  });
  await refreshTireTemplates();
  await refreshTirePayload();
  renderTirEditorContent();
  drawVehicleFromForm();
}

function applyTirTemplate(target) {
  const name = document.getElementById("tir-template-picker")?.value || state.activeTir?.id;
  if (!name) return;
  pushUndoSnapshot(snapshotVehicleState("tire-template"));
  const sides = target === "both" ? ["front", "rear"] : [target];
  sides.forEach((side) => {
    document.querySelectorAll("#config-form [data-config-path]").forEach((input) => {
      const path = JSON.parse(input.dataset.configPath);
      if (path.join(".") === `${side}.tire.template`) input.value = name;
    });
  });
  markVehicleDirty();
}

function renderTirEditorContent() {
  const picker = document.getElementById("tir-template-picker");
  const editor = document.getElementById("tir-editor");
  const meta = document.getElementById("tir-editor-meta");
  if (!picker || !editor || !meta) return;
  const templates = state.tireTemplates?.templates || [];
  picker.innerHTML = templates.map((template) => `
    <option value="${escapeHtml(template.id)}"${template.id === state.activeTir?.id ? " selected" : ""}>${escapeHtml(template.label)}</option>
  `).join("");
  if (state.activeTir && !templates.some((template) => template.id === state.activeTir.id)) {
    picker.innerHTML = `<option value="${escapeHtml(state.activeTir.id)}" selected>${escapeHtml(state.activeTir.label)}</option>${picker.innerHTML}`;
  }
  editor.value = state.activeTir?.text || "";
  const metadata = state.activeTir?.metadata || {};
  meta.textContent = state.activeTir
    ? `${state.activeTir.path} | FNOMIN ${formatNumber(metadata.fznom_n)} N | R0 ${formatNumber(metadata.unloaded_radius_m)} m`
    : "No .tir template loaded";
}

function wireTireTools() {
  const tools = document.querySelector("[data-tir-tools]");
  if (!tools) return;
  renderTirEditorContent();
  document.getElementById("tir-template-picker")?.addEventListener("change", (event) => {
    loadTirTemplate(event.target.value);
  });
  document.getElementById("tir-import-input")?.addEventListener("change", (event) => {
    importTirFile(event.target.files?.[0]);
    event.target.value = "";
  });
  document.getElementById("save-tir-btn")?.addEventListener("click", saveActiveTirTemplate);
  document.querySelectorAll("[data-apply-tir]").forEach((button) => {
    button.addEventListener("click", () => applyTirTemplate(button.dataset.applyTir));
  });
}

function renderStandard() {
  ensureSelectedSimConfigLoaded();
  const workflow = selectedWorkflow();
  document.getElementById("standard-context").textContent =
    `${activeVehicleName()} -> ${workflow?.label || "StandardSim"} | ${activeArchitecture()}`;
  syncSimTabs();
  renderWorkflows();
  renderSimSetup(workflow);
  renderOutputs(workflow);
  renderJobs();
}

function syncSimTabs() {
  document.querySelectorAll(".tab").forEach((item) => {
    item.classList.toggle("active", item.dataset.tab === state.activeSimTab);
  });
  document.querySelectorAll(".panel").forEach((panel) => {
    panel.classList.toggle("active", panel.id === `${state.activeSimTab}-panel`);
  });
}

function renderWorkflows() {
  const workflows = standardWorkflows();
  const grid = document.getElementById("workflow-grid");
  grid.innerHTML = workflows.map(workflowCard).join("");
  grid.querySelectorAll("[data-workflow]").forEach((card) => {
    card.addEventListener("click", async () => {
      await selectStandardWorkflow(card.dataset.workflow);
    });
  });
}

async function selectStandardWorkflow(workflowId) {
  if (!workflowId || workflowId === state.selectedWorkflowId) return;
  state.selectedWorkflowId = workflowId;
  state.activeSimTab = "setup";
  state.simConfigPayload = null;
  state.simConfigLibrary = null;
  renderStandard();
  await refreshSelectedSimConfig();
  renderStandard();
}

function workflowCard(workflow) {
  const outputCount = workflow.outputs.filter((output) => output.exists).length;
  const runLabel = workflow.actions.length > 1 ? "Build + run" : "Run";
  return `
    <article class="workflow-card ${workflow.id === state.selectedWorkflowId ? "active" : ""}" data-workflow="${workflow.id}">
      <div class="card-head">
        <div class="card-title">${escapeHtml(workflow.label)}</div>
        <span class="mini-pill">${runLabel}</span>
      </div>
      <div class="card-meta">${escapeHtml(workflowDescription(workflow))}</div>
      <div class="signal-row">
        <span class="mini-pill ${workflow.config?.exists ? "ok" : "missing"}">Config</span>
        <span class="mini-pill ${outputCount ? "ok" : "missing"}">${outputCount}/${workflow.outputs.length} outputs</span>
      </div>
    </article>
  `;
}

function workflowDescription(workflow) {
  return {
    "ramp-steer": "Open-loop steering ramp across speed isolines.",
    "steady-state": "Closed-loop lateral acceleration operating points.",
    transient: "Step steer and sine response in the time domain.",
    "four-post": "Heave, roll, and suspension response sweeps.",
  }[workflow?.id] || workflow?.config?.path || "";
}

function simWorkflowGuide(workflow) {
  return {
    "ramp-steer": {
      title: "Ramp Steer",
      copy: "Configure velocity isolines, lateral acceleration limits, solver controls, and report settings.",
      steps: ["Vehicle is selected", "Set speed sweep", "Build + run"],
    },
    "steady-state": {
      title: "Steady State",
      copy: "Configure target lateral accelerations and settled-point criteria for closed-loop characterization.",
      steps: ["Vehicle is selected", "Set target grid", "Build + run"],
    },
    transient: {
      title: "Transient",
      copy: "Configure step and sine steering inputs for lateral transient response.",
      steps: ["Vehicle is selected", "Set input cases", "Build + run"],
    },
    "four-post": {
      title: "Four Post",
      copy: "Configure suspension override rates and heave/roll/force procedure magnitudes.",
      steps: ["Vehicle is selected", "Set procedure", "Build + run"],
    },
  }[workflow?.id] || {
    title: workflow?.label || "Standard Sim",
    copy: "Select a standard workflow, configure the run, then execute it.",
    steps: ["Vehicle is selected", "Configure run", "Run"],
  };
}

function renderSimSetup(workflow) {
  const guide = simWorkflowGuide(workflow);
  document.getElementById("sim-setup-title").textContent = guide.title;
  document.getElementById("sim-setup-copy").textContent = guide.copy;
  document.getElementById("sim-step-strip").innerHTML = guide.steps.map((step, index) => `
    <div class="sim-step ${index === 1 ? "active" : ""}">
      <span>${index + 1}</span>
      <strong>${escapeHtml(step)}</strong>
    </div>
  `).join("");
  renderSimConfigLibrary();
  renderSimConfigForm();
}

function renderSimConfigLibrary() {
  const picker = document.getElementById("sim-config-picker");
  const sources = state.simConfigLibrary?.sources || [];
  if (picker) {
    if (!sources.some((source) => source.id === state.selectedSimConfigSource)) {
      state.selectedSimConfigSource = sources[0]?.id || "";
    }
    picker.innerHTML = sources.length
      ? sources.map((source) => `
        <option value="${escapeHtml(source.id)}"${source.id === state.selectedSimConfigSource ? " selected" : ""}>
          ${escapeHtml(source.type === "default" ? "Default" : `Saved: ${source.label}`)}
        </option>
      `).join("")
      : `<option value="">No run configs</option>`;
  }
  const selected = sources.find((source) => source.id === state.selectedSimConfigSource);
  const deleteButton = document.getElementById("delete-sim-config-btn");
  if (deleteButton) {
    const canDelete = selected?.type === "saved";
    deleteButton.hidden = !canDelete;
    deleteButton.disabled = !canDelete;
  }
  const saveName = document.getElementById("save-sim-config-name");
  if (saveName && !saveName.value && selectedWorkflow()) saveName.value = `${selectedWorkflow().label} setup`;
  updateSimConfigStatus();
}

function renderSimConfigForm() {
  const form = document.getElementById("sim-config-form");
  if (!form) return;
  if (!state.simConfigPayload) {
    form.innerHTML = `<div class="empty-state">Select a workflow to configure its simulation inputs.</div>`;
    return;
  }
  form.innerHTML = fieldGroupSections(state.simConfigPayload.fields || [], "sim-config");
  form.oninput = () => markSimConfigDirty();
  form.onchange = () => markSimConfigDirty();
}

function markSimConfigDirty() {
  state.dirtySimConfig = true;
  updateSimConfigStatus();
}

function updateSimConfigStatus() {
  const status = document.getElementById("sim-config-status");
  if (!status) return;
  const workflow = selectedWorkflow();
  if (!workflow) {
    status.textContent = "No standard workflow selected.";
    return;
  }
  if (!state.simConfigPayload) {
    status.textContent = "Loading run configuration.";
    return;
  }
  status.textContent = state.dirtySimConfig
    ? "Run config has unapplied edits."
    : `Editing ${state.simConfigPayload.label || workflow.label} config.`;
}

function renderOutputs(workflow) {
  document.getElementById("selected-title").textContent = workflow?.label || "Outputs";
  const list = document.getElementById("output-list");
  if (!workflow?.outputs.length) {
    list.innerHTML = `<div class="empty-state">No registered outputs.</div>`;
    document.getElementById("preview").innerHTML = `<div class="empty-state"></div>`;
    return;
  }
  list.innerHTML = workflow.outputs.map(outputItem).join("");
  list.querySelectorAll("[data-file-path]").forEach((button) => {
    button.addEventListener("click", () => previewFile(button.dataset.filePath, button.dataset.fileKind));
  });
  const first = workflow.outputs.find((output) => output.exists);
  if (first) previewFile(first.path, first.kind);
  else document.getElementById("preview").innerHTML = `<div class="empty-state">No output file yet.</div>`;
}

function outputItem(output) {
  const meta = output.exists ? `${escapeHtml(output.modified_label)} | ${fmtBytes(output.size)}` : "missing";
  const button = output.exists
    ? `<button class="file-button" type="button" data-file-path="${escapeHtml(output.path)}" data-file-kind="${escapeHtml(output.kind)}">Open</button>`
    : `<button class="file-button" type="button" disabled>Open</button>`;
  return `
    <div class="output-item">
      <div>
        <div class="output-name">${escapeHtml(output.label)}</div>
        <div class="output-meta">${meta}</div>
      </div>
      ${button}
    </div>
  `;
}

async function previewFile(path, kind) {
  const preview = document.getElementById("preview");
  if (kind === "pdf") {
    preview.innerHTML = `<iframe src="/files/${encodeURIComponent(path)}"></iframe>`;
    return;
  }
  if (kind === "csv") {
    const data = await api(`/api/csv?path=${encodeURIComponent(path)}`);
    preview.innerHTML = csvTable(data);
    return;
  }
  preview.innerHTML = `<iframe src="/files/${encodeURIComponent(path)}"></iframe>`;
}

function csvTable(data) {
  if (!data.headers.length) return `<div class="empty-state">No rows.</div>`;
  const head = data.headers.map((header) => `<th>${escapeHtml(header)}</th>`).join("");
  const body = data.rows.map((row) => {
    const cells = data.headers.map((header) => `<td>${escapeHtml(row[header] ?? "")}</td>`).join("");
    return `<tr>${cells}</tr>`;
  }).join("");
  return `<table><thead><tr>${head}</tr></thead><tbody>${body}</tbody></table>`;
}

function renderJobs() {
  const jobs = state.status?.jobs || [];
  const list = document.getElementById("job-list");
  const runButton = document.getElementById("run-workflow-btn");
  const workflow = selectedWorkflow();
  runButton.disabled = !workflow;
  const runVerb = workflow?.actions.length > 1 ? "Build + Run" : "Run";
  runButton.textContent = workflow
    ? `${state.dirtySimConfig ? "Apply + " : ""}${runVerb} ${workflow.label}`
    : "No Workflow";
  if (!jobs.length) {
    list.innerHTML = `<div class="empty-state">No jobs yet.</div>`;
    document.getElementById("job-log").textContent = "";
    return;
  }
  if (!state.selectedJobId) state.selectedJobId = jobs[0].id;
  list.innerHTML = jobs.map(jobItem).join("");
  list.querySelectorAll("[data-job]").forEach((item) => {
    item.addEventListener("click", async () => {
      state.selectedJobId = item.dataset.job;
      await loadJobLog();
      renderJobs();
    });
  });
  loadJobLog();
}

function jobItem(job) {
  return `
    <div class="job-item ${job.id === state.selectedJobId ? "active" : ""}" data-job="${job.id}">
      <div class="job-line">
        <strong>${escapeHtml(job.label)}</strong>
        <span class="job-status ${escapeHtml(job.status)}">${escapeHtml(job.status)}</span>
      </div>
      <div class="output-meta">${escapeHtml(job.argv.join(" -> "))}</div>
    </div>
  `;
}

async function loadJobLog() {
  if (!state.selectedJobId) return;
  const job = await api(`/api/jobs/${state.selectedJobId}`);
  const log = document.getElementById("job-log");
  log.textContent = job.log || "";
  log.scrollTop = log.scrollHeight;
}

async function startSelectedWorkflow() {
  const workflow = selectedWorkflow();
  if (!workflow) return;
  if (state.dirtySimConfig) {
    const applied = await applySimConfigEdits();
    if (!applied) return;
  }
  const job = await api(`/api/workflows/${workflow.id}/run`, {
    method: "POST",
    headers: { "Content-Type": "application/json" },
  });
  state.selectedJobId = job.id;
  state.activeSimTab = "jobs";
  state.status = await api("/api/status");
  renderStandard();
}

function setView(view) {
  state.view = view;
  renderMode();
  renderRailActions();
  if (view === "standard") renderStandard();
  if (view === "setup") renderSetup();
}

function toggleTheme() {
  state.dark = !state.dark;
  localStorage.setItem("bobsim-theme", state.dark ? "dark" : "light");
  document.body.classList.toggle("dark", state.dark);
  renderThemeButton();
  drawVehicleFromForm();
}

function renderVehiclePreview(data) {
  requestAnimationFrame(() => drawVehiclePreview(data));
}

function currentVehicleFormData() {
  if (!state.vehiclePayload) return;
  try {
    const data = JSON.parse(JSON.stringify(state.vehiclePayload.data || {}));
    const values = collectVehicleValues();
    Object.entries(values).forEach(([key, value]) => setNestedValue(data, JSON.parse(key), value));
    return data;
  } catch {
    return state.vehiclePayload.data || {};
  }
}

function drawVehicleFromForm() {
  const data = currentVehicleFormData();
  if (data) drawVehiclePreview(data);
}

function setNestedValue(data, path, value) {
  let current = data;
  for (let idx = 0; idx < path.length - 1; idx += 1) current = current[path[idx]];
  current[path[path.length - 1]] = value;
}

function drawVehiclePreview(data) {
  const canvas = document.getElementById("vehicle-canvas");
  const area = activeParameterArea();
  syncPreviewModeControls(area);
  const rect = canvas.getBoundingClientRect();
  const width = Math.max(420, Math.floor(rect.width));
  const height = Math.max(360, Math.floor(rect.height));
  const dpr = window.devicePixelRatio || 1;
  canvas.width = Math.floor(width * dpr);
  canvas.height = Math.floor(height * dpr);
  const ctx = canvas.getContext("2d");
  ctx.setTransform(dpr, 0, 0, dpr, 0, 0);
  ctx.clearRect(0, 0, width, height);

  if (area.visual === "overview") {
    clearMassInteractionScene();
    clearGeometryInteractionScene();
    drawArchitecturePreview(ctx, width, height, data);
    return;
  }
  if (area.visual === "aero") {
    clearMassInteractionScene();
    clearArchitectureInteractionScene();
    clearGeometryInteractionScene();
    drawAeroMapPreview(ctx, width, height, data);
    return;
  }
  if (area.visual === "powertrain") {
    clearMassInteractionScene();
    clearArchitectureInteractionScene();
    clearGeometryInteractionScene();
    drawPowertrainPreview(ctx, width, height, data);
    return;
  }
  if (area.visual === "suspension") {
    clearMassInteractionScene();
    clearArchitectureInteractionScene();
    clearGeometryInteractionScene();
    drawSuspensionPreview(ctx, width, height, data);
    return;
  }
  if (area.visual === "compliances") {
    clearMassInteractionScene();
    clearArchitectureInteractionScene();
    clearGeometryInteractionScene();
    drawCompliancePreview(ctx, width, height, data);
    return;
  }
  if (area.visual === "tires") {
    clearMassInteractionScene();
    clearArchitectureInteractionScene();
    clearGeometryInteractionScene();
    drawTirePreview(ctx, width, height, data);
    return;
  }
  if (area.visual === "mass") {
    clearArchitectureInteractionScene();
    clearGeometryInteractionScene();
    drawMassPreview(ctx, width, height, data);
    return;
  }

  clearArchitectureInteractionScene();
  clearMassInteractionScene();
  const fullModel = buildVehicleGeometry(data);
  let model = filterVehicleModel(fullModel, sectionFocus(area.id));
  if (area.id === "hardpoints") model = filterGeometryAxles(model);
  if (!model.points.length) {
    clearGeometryInteractionScene();
    return;
  }
  const frame = vehicleModelFrame(model);
  const scene = projectVehicleModel(model, width, height, state.vehiclePreviewView, frame);
  const { map, scale } = scene;
  state.geometryScene = {
    width,
    height,
    scale,
    points: [...map.values()],
  };

  drawPreviewGrid(ctx, width, height);
  [...model.links]
    .sort((a, b) => ((map.get(a.from)?.depth || 0) + (map.get(a.to)?.depth || 0))
      - ((map.get(b.from)?.depth || 0) + (map.get(b.to)?.depth || 0)))
    .forEach((link) => drawCylinder(ctx, map.get(link.from), map.get(link.to), link));
  [...map.values()]
    .filter((point) => point.shellRadiusM)
    .sort((a, b) => a.depth - b.depth)
    .forEach((point) => drawGyrationShell(ctx, point, scale, state.vehiclePreviewView));
  [...map.values()]
    .sort((a, b) => a.depth - b.depth)
    .forEach((point) => drawSphere(ctx, point));
  drawGeometryInteractionOverlay(ctx);
  syncGeometryPointEditor();
}

function clearGeometryInteractionScene() {
  state.geometryScene = null;
  state.geometryHoverPointId = null;
  state.geometryDrag = null;
  document.getElementById("vehicle-canvas")?.classList.remove("geometry-hot", "geometry-dragging");
  syncGeometryPointEditor();
}

function clearArchitectureInteractionScene() {
  state.architectureScene = null;
  state.architectureHoverId = null;
  state.architectureModalOpen = false;
  state.architectureModalAxle = null;
  document.getElementById("vehicle-canvas")?.classList.remove("architecture-hot");
  renderArchitectureConnectionModal();
}

function clearMassInteractionScene() {
  state.massScene = null;
  state.massHoverPointId = null;
  state.massSelectedPointId = null;
  document.getElementById("vehicle-canvas")?.classList.remove("mass-hot");
  syncMassPropertyEditor();
}

function isArchitecturePreviewArea(area = activeParameterArea()) {
  return area.visual === "overview";
}

function selectedArchitectureHotspot() {
  if (!state.architectureScene) return null;
  return state.architectureScene.hotspots.find((hotspot) => hotspot.id === state.architectureSelectedId) || null;
}

function hitTestArchitectureHotspot(event) {
  if (!isArchitecturePreviewArea() || !state.architectureScene) return null;
  const point = pointerCanvasPoint(event);
  if (!point) return null;
  return [...state.architectureScene.hotspots]
    .reverse()
    .find((hotspot) => (
      point.x >= hotspot.rect.x
      && point.x <= hotspot.rect.x + hotspot.rect.width
      && point.y >= hotspot.rect.y
      && point.y <= hotspot.rect.y + hotspot.rect.height
    )) || null;
}

function updateArchitectureHover(event) {
  const hotspot = hitTestArchitectureHotspot(event);
  const next = hotspot?.id || null;
  if (next !== state.architectureHoverId) {
    state.architectureHoverId = next;
    drawVehicleFromForm();
  }
  document.getElementById("vehicle-canvas")?.classList.toggle("architecture-hot", Boolean(hotspot));
}

function selectArchitectureHotspot(hotspot) {
  if (!hotspot) return;
  state.architectureSelectedId = hotspot.id;
  if (hotspot.type === "bellcrank-pickup") {
    state.architectureSelectedOrderIndex = Number(hotspot.index) || 0;
  }
  if (hotspot.type === "axle" || hotspot.type === "bellcrank-pickup") {
    openArchitectureConnectionModal(hotspot.axle);
  } else {
    state.architectureModalOpen = false;
    state.architectureModalAxle = null;
    renderArchitectureConnectionModal();
  }
  drawVehicleFromForm();
}

function openArchitectureConnectionModal(axle) {
  if (!["front", "rear"].includes(axle)) return;
  state.architectureModalOpen = true;
  state.architectureModalAxle = axle;
  if (!state.architectureSelectedId?.startsWith(`architecture-${axle}`)) {
    state.architectureSelectedId = `architecture-${axle}`;
  }
  renderArchitectureConnectionModal();
}

function closeArchitectureConnectionModal() {
  state.architectureModalOpen = false;
  state.architectureModalAxle = null;
  renderArchitectureConnectionModal();
}

function renderArchitectureConnectionModal(data = currentVehicleFormData() || state.vehiclePayload?.data || {}) {
  const modal = document.getElementById("architecture-connection-modal");
  if (!modal) return;
  const axle = state.architectureModalAxle;
  const active = state.architectureModalOpen && isArchitecturePreviewArea() && ["front", "rear"].includes(axle);
  modal.hidden = !active;
  if (!active) return;

  const architecture = String(data.architecture?.[axle] || "");
  const title = document.getElementById("architecture-connection-title");
  const subtitle = document.getElementById("architecture-connection-subtitle");
  const select = document.getElementById("architecture-modal-select");
  const body = document.getElementById("architecture-connection-body");
  if (title) title.textContent = `${humanizeToken(axle)} Connections`;
  if (subtitle) subtitle.textContent = architecture.includes("bellcrank")
    ? "Assign each bellcrank connection to the fixed pickup points."
    : "Select a bellcrank architecture to assign pickup connections.";
  if (select) {
    select.innerHTML = architectureChoicesForAxle(axle).map((choice) => `
      <option value="${escapeHtml(choice)}"${choice === architecture ? " selected" : ""}>${escapeHtml(humanizeToken(choice))}</option>
    `).join("");
  }
  if (body) {
    body.innerHTML = architecture.includes("bellcrank")
      ? architectureConnectionEditorHtml(axle, data)
      : architectureConnectionEmptyHtml(architecture);
  }
}

function architectureConnectionEmptyHtml(architecture) {
  return `
    <div class="connection-empty">
      <span>${escapeHtml(humanizeToken(architecture || "direct"))}</span>
      <strong>No bellcrank connection map</strong>
    </div>
  `;
}

function architectureConnectionEditorHtml(axle, data) {
  const path = [axle, "actuation", "bellcrank", "order"];
  const choices = bellcrankOrderChoicesForPath(path, data) || ["rod", "shock"];
  const values = architectureOrderValuesForData(axle, data);
  const selectedIndex = clamp(state.architectureSelectedOrderIndex, 0, Math.max(0, values.length - 1));
  const nodes = architectureConnectionNodes(axle, data, choices, values);
  return `
    <section class="connection-map-panel">
      <div class="connection-map">
        ${nodes.map((node) => node.kind === "pivot"
          ? `<span class="connection-pivot-node" style="--node-x: ${node.x}%; --node-y: ${node.y}%" title="Bellcrank pivot"></span>`
          : `
            <button
              class="connection-pickup-node ${node.slotIndex === selectedIndex ? "active" : ""}"
              data-architecture-pickup="${escapeHtml(axle)}"
              data-order-index="${node.slotIndex}"
              style="--node-x: ${node.x}%; --node-y: ${node.y}%; --role-color: ${bellcrankRoleColor(node.role)}"
              type="button"
              title="${escapeHtml(humanizeToken(node.role))} pickup"
            >
              <span>${node.slotIndex + 1}</span>
              <strong>${escapeHtml(humanizeToken(node.role))}</strong>
            </button>
          `).join("")}
        <span class="connection-axis-label">Y / Z</span>
      </div>
    </section>
    <section class="connection-assignment-panel">
      <div class="connection-assignment-list">
        <span>Connection order</span>
        ${values.map((role, index) => `
          <button
            class="connection-assignment-row ${index === selectedIndex ? "active" : ""}"
            data-architecture-pickup="${escapeHtml(axle)}"
            data-order-index="${index}"
            style="--role-color: ${bellcrankRoleColor(role)}"
            type="button"
          >
            <span>${index + 1}</span>
            <strong>${escapeHtml(humanizeToken(role))}</strong>
          </button>
        `).join("")}
      </div>
      <div class="connection-role-picker">
        <span>Assign selected</span>
        <div class="connection-role-grid">
          ${choices.map((choice) => `
            <button
              class="bellcrank-role-button ${choice === values[selectedIndex] ? "active" : ""}"
              data-architecture-role="${escapeHtml(axle)}"
              data-order-index="${selectedIndex}"
              data-role="${escapeHtml(choice)}"
              style="--role-color: ${bellcrankRoleColor(choice)}"
              type="button"
            >${escapeHtml(humanizeToken(choice))}</button>
          `).join("")}
        </div>
      </div>
    </section>
  `;
}

function architectureConnectionNodes(axle, data, choices, values) {
  const pickups = nestedValue(data, [axle, "actuation", "bellcrank", "pickups_m"]) || {};
  const pivot = toPoint(nestedValue(data, [axle, "actuation", "bellcrank", "pivot_m"]));
  const pickupNodes = choices
    .map((role) => ({ kind: "pickup", role, point: toPoint(pickups[role]), slotIndex: values.indexOf(role) }))
    .filter((node) => node.point && node.slotIndex >= 0);
  const rawNodes = pivot ? [{ kind: "pivot", point: pivot }, ...pickupNodes] : pickupNodes;
  if (!rawNodes.length) return [];
  const bounds = rawNodes.reduce(
    (acc, node) => ({
      minY: Math.min(acc.minY, node.point[1]),
      maxY: Math.max(acc.maxY, node.point[1]),
      minZ: Math.min(acc.minZ, node.point[2]),
      maxZ: Math.max(acc.maxZ, node.point[2]),
    }),
    { minY: Infinity, maxY: -Infinity, minZ: Infinity, maxZ: -Infinity },
  );
  const spanY = Math.max(0.01, bounds.maxY - bounds.minY);
  const spanZ = Math.max(0.01, bounds.maxZ - bounds.minZ);
  return rawNodes.map((node) => ({
    ...node,
    x: 14 + ((node.point[1] - bounds.minY) / spanY) * 72,
    y: 86 - ((node.point[2] - bounds.minZ) / spanZ) * 72,
  }));
}

function updateArchitectureModalArchitecture(value) {
  const axle = state.architectureModalAxle;
  if (!["front", "rear"].includes(axle)) return;
  state.architectureSelectedId = `architecture-${axle}`;
  setPrimitiveConfigValue(["architecture", axle], value);
}

function architectureChoicesForAxle(axle) {
  const select = document.getElementById(`architecture-${axle}-select`);
  const choices = select ? Array.from(select.options).map((option) => option.value) : [];
  return choices.length ? choices : ["direct", "bellcrank", "bellcrank_stabar"];
}

function architectureOrderValues(axle) {
  const container = architectureOrderContainer(axle);
  if (!container) return [];
  return Array.from(container.querySelectorAll("[data-array-cell]")).map((input) => input.value);
}

function architectureOrderValuesForData(axle, data = currentVehicleFormData() || state.vehiclePayload?.data || {}) {
  const path = [axle, "actuation", "bellcrank", "order"];
  const choices = bellcrankOrderChoicesForPath(path, data) || ["rod", "shock"];
  const domValues = architectureOrderValues(axle);
  const rawValues = domValues.length ? domValues : nestedValue(data, path);
  return normalizeBellcrankOrder(rawValues, choices);
}

function normalizeBellcrankOrder(values, choices) {
  const seen = new Set();
  const normalized = [];
  (Array.isArray(values) ? values : []).forEach((value) => {
    if (!choices.includes(value) || seen.has(value)) return;
    seen.add(value);
    normalized.push(value);
  });
  choices.forEach((choice) => {
    if (seen.has(choice)) return;
    seen.add(choice);
    normalized.push(choice);
  });
  return normalized.slice(0, choices.length);
}

function bellcrankPickupLayout(count) {
  if (count <= 2) {
    return [
      { x: 50, y: 22 },
      { x: 30, y: 72 },
    ];
  }
  return [
    { x: 50, y: 18 },
    { x: 28, y: 74 },
    { x: 72, y: 74 },
  ];
}

function bellcrankRoleColor(role) {
  const palette = canvasPalette();
  return {
    rod: state.dark ? "#92bea6" : "#5e987c",
    shock: palette.red,
    stabar: state.dark ? "#b3a6d8" : "#8b7ab8",
  }[role] || palette.amber;
}

function architectureOrderContainer(axle) {
  const key = JSON.stringify([axle, "actuation", "bellcrank", "order"]);
  return Array.from(document.querySelectorAll("#config-form [data-array-path]"))
    .find((container) => container.dataset.arrayPath === key) || null;
}

function setArchitectureOrderValues(axle, values) {
  const container = architectureOrderContainer(axle);
  if (!container) return;
  values.forEach((value, index) => {
    const input = container.querySelector(`[data-array-cell][data-index="${index}"]`);
    if (input) input.value = value;
  });
}

function selectArchitectureOrderPickup(axle, index) {
  state.architectureSelectedOrderIndex = Number(index) || 0;
  state.architectureSelectedId = `architecture-${axle}-pickup-${state.architectureSelectedOrderIndex}`;
  if (state.architectureModalOpen) state.architectureModalAxle = axle;
  renderArchitectureConnectionModal();
  drawVehicleFromForm();
}

function updateArchitectureOrderRole(axle, index, role) {
  const data = currentVehicleFormData() || state.vehiclePayload?.data || {};
  const path = [axle, "actuation", "bellcrank", "order"];
  const choices = bellcrankOrderChoicesForPath(path, data) || ["rod", "shock"];
  if (!choices.includes(role)) return;
  const targetIndex = clamp(Number(index) || 0, 0, choices.length - 1);
  const values = architectureOrderValuesForData(axle, data);
  const previousRole = values[targetIndex];
  const sourceIndex = values.indexOf(role);
  values[targetIndex] = role;
  if (sourceIndex >= 0 && sourceIndex !== targetIndex) values[sourceIndex] = previousRole;
  state.architectureSelectedOrderIndex = targetIndex;
  state.architectureSelectedId = `architecture-${axle}-pickup-${targetIndex}`;
  if (state.architectureModalOpen) state.architectureModalAxle = axle;
  pushUndoSnapshot(snapshotVehicleState("architecture-order"));
  setArchitectureOrderValues(axle, normalizeBellcrankOrder(values, choices));
  markVehicleDirty();
}

function setPrimitiveConfigValue(path, value) {
  const key = JSON.stringify(path);
  const input = Array.from(document.querySelectorAll("#config-form [data-config-path]"))
    .find((item) => item.dataset.configPath === key);
  if (!input) return;
  pushUndoSnapshot(snapshotVehicleState("primitive"));
  input.value = value;
  markVehicleDirty();
}

function editableGeometryPoint(point) {
  return Array.isArray(point?.sourcePath) && point.sourcePath.length > 0;
}

function geometryPathKey(path) {
  return JSON.stringify(path);
}

function selectedGeometryPoint() {
  if (!state.geometryScene) return null;
  return state.geometryScene.points.find((point) => point.id === state.geometrySelectedPointId) || null;
}

function geometryPointById(id) {
  return state.geometryScene?.points.find((point) => point.id === id) || null;
}

function geometrySourceContainer(point) {
  if (!editableGeometryPoint(point)) return null;
  const key = geometryPathKey(point.sourcePath);
  return Array.from(document.querySelectorAll("#config-form [data-array-path]"))
    .find((container) => container.dataset.arrayPath === key) || null;
}

function geometrySourceValues(point) {
  const container = geometrySourceContainer(point);
  if (!container) return null;
  const values = [0, 1, 2].map((index) => Number(container.querySelector(`[data-array-cell][data-index="${index}"]`)?.value));
  return values.every(Number.isFinite) ? values : null;
}

function setGeometrySourceValues(point, values, { syncEditor = true, renderMini = true, pushUndo = true } = {}) {
  const container = geometrySourceContainer(point);
  if (!container || !Array.isArray(values)) return;
  if (pushUndo) pushUndoSnapshot(snapshotVehicleState("geometry"));
  [0, 1, 2].forEach((index) => {
    const input = container.querySelector(`[data-array-cell][data-index="${index}"]`);
    if (input && Number.isFinite(Number(values[index]))) {
      input.value = Number(values[index]).toFixed(4).replace(/\.?0+$/, "");
    }
  });
  markGeometryDirty({ renderMini });
  if (syncEditor) syncGeometryPointEditor();
}

function markGeometryDirty({ renderMini = true } = {}) {
  updateDirtyState();
  drawVehicleFromForm();
  if (renderMini) renderParameterTabCanvases();
}

function syncGeometryPointEditor() {
  const editor = document.getElementById("geometry-point-editor");
  if (!editor) return;
  document.querySelectorAll(".geometry-source-active").forEach((item) => item.classList.remove("geometry-source-active"));
  const point = selectedGeometryPoint();
  if (!isSpatialPreviewArea() || !editableGeometryPoint(point)) {
    editor.hidden = true;
    return;
  }
  const values = geometrySourceValues(point);
  if (!values) {
    editor.hidden = true;
    return;
  }
  editor.hidden = false;
  document.getElementById("geometry-point-name").textContent = point.sourceLabel || humanizeToken(point.id);
  document.getElementById("geometry-axis-label").textContent = state.geometryAxis.toUpperCase();
  document.querySelectorAll("[data-geometry-axis]").forEach((button) => {
    button.classList.toggle("active", button.dataset.geometryAxis === state.geometryAxis);
  });
  document.querySelectorAll("[data-geometry-coordinate]").forEach((input) => {
    const index = axisIndex(input.dataset.geometryCoordinate);
    if (index >= 0 && document.activeElement !== input) {
      input.value = values[index].toFixed(4).replace(/\.?0+$/, "");
    }
  });
  geometrySourceContainer(point)?.closest("[data-field-wrapper]")?.classList.add("geometry-source-active");
}

function selectGeometryPoint(point, { scroll = false } = {}) {
  if (!editableGeometryPoint(point)) return;
  state.geometrySelectedPointId = point.id;
  syncGeometryPointEditor();
  if (scroll) {
    geometrySourceContainer(point)?.closest("[data-field-wrapper]")?.scrollIntoView({
      behavior: "smooth",
      block: "nearest",
    });
  }
  drawVehicleFromForm();
}

function clearGeometrySelection() {
  if (!state.geometrySelectedPointId) return false;
  state.geometrySelectedPointId = null;
  syncGeometryPointEditor();
  drawVehicleFromForm();
  return true;
}

function setGeometryAxis(axis, { redraw = true } = {}) {
  if (!["x", "y", "z"].includes(axis)) return;
  state.geometryAxis = axis;
  if (state.geometryDrag) resetGeometryDragReference();
  syncGeometryPointEditor();
  if (redraw) drawVehicleFromForm();
}

function cycleGeometryAxis() {
  const axes = ["x", "y", "z"];
  setGeometryAxis(axes[(axes.indexOf(state.geometryAxis) + 1) % axes.length]);
}

function axisIndex(axis) {
  return { x: 0, y: 1, z: 2 }[axis] ?? -1;
}

function hitTestGeometryPoint(event) {
  if (!isSpatialPreviewArea() || !state.geometryScene) return null;
  const canvasPoint = pointerCanvasPoint(event);
  if (!canvasPoint) return null;
  const hits = state.geometryScene.points
    .filter(editableGeometryPoint)
    .map((point) => {
      const dx = point.x2 - canvasPoint.x;
      const dy = point.y2 - canvasPoint.y;
      return { point, distance: Math.hypot(dx, dy) };
    })
    .filter((hit) => hit.distance <= Math.max(12, (hit.point.radius || 5) + 8))
    .sort((a, b) => a.distance - b.distance || b.point.depth - a.point.depth);
  return hits[0]?.point || null;
}

function isMassPreviewArea(area = activeParameterArea()) {
  return area.visual === "mass";
}

function selectedMassPoint() {
  if (!state.massScene) return null;
  return state.massScene.uniquePoints.find((point) => point.id === state.massSelectedPointId) || null;
}

function hitTestMassPoint(event) {
  if (!isMassPreviewArea() || !state.massScene) return null;
  const canvasPoint = pointerCanvasPoint(event);
  if (!canvasPoint) return null;
  const hits = state.massScene.points
    .map((point) => {
      const dx = point.x2 - canvasPoint.x;
      const dy = point.y2 - canvasPoint.y;
      return { point, distance: Math.hypot(dx, dy) };
    })
    .filter((hit) => hit.distance <= Math.max(18, (hit.point.radius || 5) + 10))
    .sort((a, b) => a.distance - b.distance || b.point.depth - a.point.depth);
  return hits[0]?.point || null;
}

function updateMassHover(event) {
  const point = hitTestMassPoint(event);
  const next = point?.id || null;
  if (next !== state.massHoverPointId) {
    state.massHoverPointId = next;
    drawVehicleFromForm();
  }
  document.getElementById("vehicle-canvas")?.classList.toggle("mass-hot", Boolean(point));
}

function selectMassPoint(point) {
  state.massSelectedPointId = point?.id || null;
  syncMassPropertyEditor();
  drawVehicleFromForm();
}

function syncMassPropertyEditor() {
  const editor = document.getElementById("mass-property-editor");
  if (!editor) return;
  const point = selectedMassPoint();
  if (!isMassPreviewArea() || !point) {
    editor.hidden = true;
    editor.style.transform = "";
    return;
  }
  editor.hidden = false;
  positionMassPropertyEditor();
  document.getElementById("mass-property-name").textContent = massDisplayName(point);
  document.getElementById("mass-property-role").textContent = point.aggregate ? "Effective" : "Source";
  const grid = document.getElementById("mass-property-grid");
  if (!grid) return;
  grid.innerHTML = massPropertyRows(point).map(([label, value]) => `
    <div class="mass-property-row">
      <span>${escapeHtml(label)}</span>
      <strong>${escapeHtml(value)}</strong>
    </div>
  `).join("");
}

function positionMassPropertyEditor() {
  const editor = document.getElementById("mass-property-editor");
  if (!editor || editor.hidden) return;
  const stage = document.querySelector(".visual-stage");
  editor.style.transform = `translateY(${stage?.scrollTop || 0}px)`;
}

function queueMassPropertyEditorPosition() {
  if (state.massEditorPositionFrame) return;
  state.massEditorPositionFrame = requestAnimationFrame(() => {
    state.massEditorPositionFrame = null;
    positionMassPropertyEditor();
  });
}

function massPropertyRows(point) {
  const radius = massGyrationRadius(point);
  return [
    ["Name", massDisplayName(point)],
    ["Mass", formatMassValue(point.massKg)],
    ["CG", formatVector([point.x, point.y, point.z], "m")],
    ["Inertia", formatInertia(point.inertiaKgM2) || "Not set"],
    ["Rg", Number.isFinite(radius) ? `${formatNumber(radius)} m` : "Not set"],
    ["Axle", point.axle ? humanizeToken(point.axle) : "Vehicle"],
    ["Side", point.side ? humanizeToken(point.side) : "Both"],
    ["Source", massSourceLabel(point)],
  ];
}

function massDisplayName(point) {
  return (point.sourceLabel || humanizeToken(point.id)).replace(/\s+mass$/i, "");
}

function formatMassValue(value) {
  const numeric = Number(value);
  return Number.isFinite(numeric) ? `${formatNumber(numeric)} kg` : "Not set";
}

function formatVector(values, unit = "") {
  if (!Array.isArray(values)) return "";
  const formatted = values.slice(0, 3).map((value) => formatNumber(value)).join(", ");
  return unit ? `[${formatted}] ${unit}` : `[${formatted}]`;
}

function formatInertia(inertia) {
  const diagonal = inertiaDiagonal(inertia);
  return diagonal.some((value) => value > 0) ? formatVector(diagonal, "kg m2") : "";
}

function massGyrationRadius(point) {
  if (Number.isFinite(point?.shellRadiusM) && point.shellRadiusM > 0) return point.shellRadiusM;
  const mass = Number(point?.massKg);
  if (!Number.isFinite(mass) || mass <= 0) return null;
  const diagonal = inertiaDiagonal(point?.inertiaKgM2).filter((value) => value > 0);
  if (!diagonal.length) return null;
  const meanInertia = diagonal.reduce((sum, value) => sum + value, 0) / diagonal.length;
  return Math.sqrt(meanInertia / mass);
}

function massSourceLabel(point) {
  if (point.aggregate) {
    const count = Number(point.sourceCount);
    return Number.isFinite(count) && count > 0 ? `${count} mass blocks` : "Computed";
  }
  return Array.isArray(point.sourcePath) ? point.sourcePath.join(".") : "Config";
}

function pointerCanvasPoint(event) {
  const canvas = document.getElementById("vehicle-canvas");
  if (!canvas) return null;
  const rect = canvas.getBoundingClientRect();
  return {
    x: event.clientX - rect.left,
    y: event.clientY - rect.top,
  };
}

function drawGeometryInteractionOverlay(ctx) {
  const point = selectedGeometryPoint();
  if (!editableGeometryPoint(point)) return;
  const vector = geometryAxisScreenVector(point, state.geometryAxis);
  const length = Math.hypot(vector.x, vector.y);
  if (length < 0.001) return;
  const ux = vector.x / length;
  const uy = vector.y / length;
  const palette = canvasPalette();
  ctx.save();
  ctx.strokeStyle = palette.amber;
  ctx.lineWidth = 3;
  ctx.lineCap = "round";
  ctx.beginPath();
  ctx.moveTo(point.x2 - ux * 58, point.y2 - uy * 58);
  ctx.lineTo(point.x2 + ux * 58, point.y2 + uy * 58);
  ctx.stroke();
  ctx.fillStyle = palette.amber;
  ctx.beginPath();
  ctx.arc(point.x2 + ux * 66, point.y2 + uy * 66, 12, 0, Math.PI * 2);
  ctx.fill();
  drawCanvasText(ctx, state.geometryAxis.toUpperCase(), point.x2 + ux * 66, point.y2 + uy * 66, {
    align: "center",
    color: "#ffffff",
    size: 11,
    weight: 820,
  });
  ctx.restore();
}

function geometryAxisScreenVector(point, axis) {
  const index = axisIndex(axis);
  if (index < 0 || !state.geometryScene) return { x: 1, y: 0 };
  const sign = point.sourceSign?.[index] ?? 1;
  const shifted = { ...point };
  if (axis === "x") shifted.x += sign;
  if (axis === "y") shifted.y += sign;
  if (axis === "z") shifted.z += sign;
  const projected = projectPoint(shifted, state.vehiclePreviewView);
  return {
    x: (projected.u - point.u) * state.geometryScene.scale,
    y: -(projected.v - point.v) * state.geometryScene.scale,
  };
}

function startGeometryDrag(event, point) {
  const canvas = document.getElementById("vehicle-canvas");
  const values = geometrySourceValues(point);
  if (!canvas || !values) return;
  pushUndoSnapshot(snapshotVehicleState("geometry-drag"));
  state.geometryDrag = {
    pointerId: event.pointerId,
    pointId: point.id,
    startX: event.clientX,
    startY: event.clientY,
    lastX: event.clientX,
    lastY: event.clientY,
    startValues: [...values],
    axis: state.geometryAxis,
    vector: geometryAxisScreenVector(point, state.geometryAxis),
  };
  canvas.classList.add("geometry-dragging");
  canvas.setPointerCapture(event.pointerId);
}

function updateGeometryDrag(event) {
  const drag = state.geometryDrag;
  if (!drag || drag.pointerId !== event.pointerId) return;
  const point = geometryPointById(drag.pointId);
  if (!point) return;
  drag.lastX = event.clientX;
  drag.lastY = event.clientY;
  const axis = drag.axis;
  const index = axisIndex(axis);
  const vector = drag.vector;
  const denom = vector.x * vector.x + vector.y * vector.y;
  if (index < 0 || denom < 0.001) return;
  const dx = event.clientX - drag.startX;
  const dy = event.clientY - drag.startY;
  const delta = (dx * vector.x + dy * vector.y) / denom;
  const values = [...drag.startValues];
  values[index] = drag.startValues[index] + delta;
  setGeometrySourceValues(point, values, { syncEditor: true, renderMini: false, pushUndo: false });
}

function resetGeometryDragReference() {
  const drag = state.geometryDrag;
  if (!drag) return;
  const point = geometryPointById(drag.pointId);
  const values = point ? geometrySourceValues(point) : null;
  if (!point || !values) return;
  drag.axis = state.geometryAxis;
  drag.startX = drag.lastX;
  drag.startY = drag.lastY;
  drag.startValues = [...values];
  drag.vector = geometryAxisScreenVector(point, state.geometryAxis);
}

function finishGeometryDrag(pointerId) {
  const drag = state.geometryDrag;
  if (!drag || drag.pointerId !== pointerId) return false;
  state.geometryDrag = null;
  document.getElementById("vehicle-canvas")?.classList.remove("geometry-dragging");
  renderParameterTabCanvases();
  return true;
}

function startPreviewDrag(event, mode = "rotate") {
  const canvas = document.getElementById("vehicle-canvas");
  if (!canvas || event.button !== 0) return;
  const width = state.geometryScene?.width || canvas.getBoundingClientRect().width || 800;
  const height = state.geometryScene?.height || canvas.getBoundingClientRect().height || 600;
  canvas.setPointerCapture(event.pointerId);
  state.vehicleDrag = {
    pointerId: event.pointerId,
    mode,
    x: event.clientX,
    y: event.clientY,
    yaw: state.vehiclePreviewYaw,
    pitch: state.vehiclePreviewPitch,
    panX: state.vehiclePreviewPanX,
    panY: state.vehiclePreviewPanY,
    width,
    height,
  };
  canvas.classList.toggle("preview-panning", mode === "pan");
  event.preventDefault();
}

function updatePreviewDrag(event) {
  const drag = state.vehicleDrag;
  if (!drag || drag.pointerId !== event.pointerId || !isSpatialPreviewArea()) return false;
  const dx = event.clientX - drag.x;
  const dy = event.clientY - drag.y;
  if (drag.mode === "pan") {
    setPreviewPan(drag.panX + dx, drag.panY + dy, drag.width, drag.height);
  } else {
    state.vehiclePreviewView = "iso";
    const sensitivity = 0.01 * state.rotationSensitivity;
    state.vehiclePreviewYaw = drag.yaw - dx * sensitivity;
    state.vehiclePreviewPitch = Math.max(-1.1, Math.min(1.1, drag.pitch + dy * sensitivity));
    syncViewButtons();
  }
  drawVehicleFromForm();
  return true;
}

function finishPreviewDrag(pointerId) {
  const drag = state.vehicleDrag;
  if (!drag || drag.pointerId !== pointerId) return false;
  state.vehicleDrag = null;
  document.getElementById("vehicle-canvas")?.classList.remove("preview-panning");
  return true;
}

function handlePreviewWheel(event) {
  if (!isSpatialPreviewArea()) return;
  event.preventDefault();
  const anchor = pointerCanvasPoint(event);
  const factor = Math.exp(-event.deltaY * 0.0012);
  setPreviewZoom(state.vehiclePreviewZoom * factor, anchor);
  drawVehicleFromForm();
}

function updateGeometryHover(event) {
  if (state.geometryDrag || state.vehicleDrag) return;
  const point = hitTestGeometryPoint(event);
  const next = point?.id || null;
  if (next !== state.geometryHoverPointId) {
    state.geometryHoverPointId = next;
    drawVehicleFromForm();
  }
  document.getElementById("vehicle-canvas")?.classList.toggle("geometry-hot", Boolean(point));
}

function syncPreviewModeControls(area = activeParameterArea()) {
  const controls = document.querySelector(".preview-controls");
  const geometryToggles = document.getElementById("geometry-axle-toggles");
  const canvas = document.getElementById("vehicle-canvas");
  const stage = document.querySelector(".visual-stage");
  const usesSpatialView = isSpatialPreviewArea(area);
  const usesMassScroll = area.id === "mass";
  if (controls) {
    controls.hidden = true;
    controls.style.display = "none";
  }
  if (geometryToggles) {
    geometryToggles.hidden = area.id !== "hardpoints";
    syncGeometryAxleToggles();
  }
  if (stage) stage.classList.toggle("mass-scroll-stage", usesMassScroll);
  if (canvas) {
    canvas.classList.toggle("diagnostic-canvas", !usesSpatialView);
    canvas.classList.toggle("mass-scroll-canvas", usesMassScroll);
    if (usesMassScroll) {
      const stageHeight = Math.max(360, stage?.clientHeight || canvas.clientHeight || 360);
      const toolbarHeight = document.querySelector(".preview-toolbar")?.getBoundingClientRect().height || 46;
      canvas.style.height = `${Math.max(900, (stageHeight - toolbarHeight - 28) * 2 + 64)}px`;
    } else {
      canvas.style.height = "";
    }
  }
}

function isSpatialPreviewArea(area = activeParameterArea()) {
  return area.visual === "hardpoints";
}

function visibleGeometryAxles() {
  if (!state.geometryShowFront && !state.geometryShowRear) {
    state.geometryShowFront = true;
    state.geometryShowRear = true;
  }
  const axles = [];
  if (state.geometryShowFront) axles.push("front");
  if (state.geometryShowRear) axles.push("rear");
  return axles;
}

function filterGeometryAxles(model) {
  const visible = new Set(visibleGeometryAxles());
  const points = model.points.filter((point) => !point.axle || visible.has(point.axle));
  const pointIds = new Set(points.map((point) => point.id));
  return {
    points,
    links: model.links.filter((link) => pointIds.has(link.from) && pointIds.has(link.to)),
  };
}

function syncGeometryAxleToggles() {
  const front = document.getElementById("geometry-show-front");
  const rear = document.getElementById("geometry-show-rear");
  if (!front || !rear) return;
  visibleGeometryAxles();
  front.checked = state.geometryShowFront;
  rear.checked = state.geometryShowRear;
  front.disabled = state.geometryShowFront && !state.geometryShowRear;
  rear.disabled = state.geometryShowRear && !state.geometryShowFront;
}

function updateGeometryAxleVisibility(axle, visible) {
  if (axle === "front") state.geometryShowFront = visible;
  if (axle === "rear") state.geometryShowRear = visible;
  visibleGeometryAxles();
  localStorage.setItem("bobsim-geometry-show-front", String(state.geometryShowFront));
  localStorage.setItem("bobsim-geometry-show-rear", String(state.geometryShowRear));
  syncGeometryAxleToggles();
  applyAxleInputVisibility();
  drawVehicleFromForm();
}

function activeParameterArea() {
  return PARAMETER_AREAS.find((area) => area.id === state.activeParamGroup) || PARAMETER_AREAS[0];
}

function canvasPalette() {
  return {
    bg: state.dark ? "#2a343d" : "#f0f4f7",
    surface: state.dark ? "#222a32" : "#fbfcfd",
    ink: state.dark ? "#e3e9ee" : "#18232e",
    muted: state.dark ? "#aab5bf" : "#687887",
    line: state.dark ? "#3f4a54" : "#cfdae2",
    blue: state.dark ? "#91b4d7" : "#4f7fa8",
    green: state.dark ? "#9bc8b4" : "#5f967f",
    amber: state.dark ? "#d4b47d" : "#b68a57",
    red: state.dark ? "#d19494" : "#b96a6a",
    magenta: state.dark ? "#d8a8c0" : "#a86c86",
  };
}

function drawPanel(ctx, x, y, width, height, fill) {
  ctx.save();
  ctx.fillStyle = fill;
  ctx.strokeStyle = canvasPalette().line;
  ctx.lineWidth = 1;
  ctx.beginPath();
  if (ctx.roundRect) ctx.roundRect(x, y, width, height, 8);
  else ctx.rect(x, y, width, height);
  ctx.fill();
  ctx.stroke();
  ctx.restore();
}

function drawCanvasText(ctx, text, x, y, options = {}) {
  const palette = canvasPalette();
  ctx.save();
  ctx.fillStyle = options.color || palette.ink;
  ctx.font = `${options.weight || 700} ${options.size || 13}px Inter, sans-serif`;
  ctx.textAlign = options.align || "left";
  ctx.textBaseline = "middle";
  ctx.fillText(String(text), x, y);
  ctx.restore();
}

function drawArchitecturePreview(ctx, width, height, data) {
  const palette = canvasPalette();
  const architecture = data.architecture || {};
  const profile = powertrainProfile(data);
  const hoverId = state.architectureHoverId;
  const selectedId = state.architectureModalOpen && state.architectureModalAxle
    ? `architecture-${state.architectureModalAxle}`
    : state.architectureSelectedId;
  const hotspots = [];
  drawPreviewGrid(ctx, width, height);
  drawCanvasText(ctx, "Architecture Assembly", 28, 30, { size: 18, weight: 780 });
  drawCanvasText(ctx, "Front views use the actual axle pickup points.", 28, 52, {
    size: 12,
    weight: 650,
    color: palette.muted,
  });

  const fullModel = buildVehicleGeometry(data);
  const geometryModel = filterVehicleModel(fullModel, sectionFocus("geometry"));
  const referencePoints = fullModel.points.filter((point) => point.id === "vehicle-mass");
  const model = {
    points: [...geometryModel.points, ...referencePoints],
    links: geometryModel.links,
  };
  if (!model.points.length) {
    drawCanvasText(ctx, "No vehicle geometry is available.", width / 2, height / 2, {
      align: "center",
      color: palette.muted,
    });
    state.architectureScene = { hotspots };
    return;
  }

  const panelEntries = architectureAxlePanels(width, height)
    .map((panel) => ({ panel, panelModel: architectureViewportModel(model, panel) }))
    .filter(({ panelModel }) => panelModel.points.length);
  const sharedFrames = architectureSharedProjectionFrames(panelEntries);
  panelEntries.forEach(({ panel, panelModel }) => {
    if (!panelModel.points.length) return;
    drawArchitectureAxlePanel(ctx, panel, architecture[panel.axle] || "direct", hotspots, hoverId, selectedId);
    panel.views.forEach((viewport) => {
      const scene = projectArchitectureScene(panelModel, viewport, sharedFrames[viewport.view]);
      drawArchitectureViewport(ctx, viewport);
      drawArchitectureAssemblyScene(ctx, scene, panelModel);
      drawArchitectureAxle3d(ctx, scene.points, viewport.axle, architecture[viewport.axle] || "direct", data, hotspots, null, null, viewport);
    });
  });
  drawArchitecturePowertrainSummary(ctx, width, profile, hotspots, hoverId, selectedId);
  drawArchitectureLegend(ctx, width, height, data);

  state.architectureScene = { hotspots };
}

function architectureAxlePanels(width, height) {
  const top = 78;
  const margin = 28;
  const gap = 16;
  const availableHeight = Math.max(250, height - top - 48);
  const panelHeight = (availableHeight - gap) / 2;
  return ["front", "rear"].map((axle, index) => (
    architectureAxlePanel(axle, margin, top + index * (panelHeight + gap), width - margin * 2, panelHeight)
  ));
}

function architectureAxlePanel(axle, x, y, width, height) {
  const inset = 12;
  const headerHeight = 34;
  const viewHeight = Math.max(1, height - headerHeight - inset * 2);
  const viewWidth = width - inset * 2;
  const viewX = x + inset;
  const topY = y + headerHeight + inset;
  return {
    id: `architecture-${axle}`,
    axle,
    x,
    y,
    width,
    height,
    views: [
      { id: `${axle}-front`, axle, label: "Front", view: "front", x: viewX, y: topY, width: viewWidth, height: viewHeight },
    ],
  };
}

function drawArchitectureAxlePanel(ctx, panel, architecture, hotspots, hoverId, selectedId) {
  const palette = canvasPalette();
  const rect = { x: panel.x, y: panel.y, width: panel.width, height: panel.height };
  hotspots.push({ id: panel.id, type: "axle", axle: panel.axle, rect });
  drawArchitecture3dHotspotFrame(ctx, rect, panel.id, hoverId, selectedId);
  drawCanvasText(ctx, `${humanizeToken(panel.axle)} axle`, panel.x + 14, panel.y + 18, {
    size: 12,
    weight: 820,
    color: palette.ink,
  });
  drawCanvasText(ctx, humanizeToken(architecture), panel.x + panel.width - 14, panel.y + 18, {
    align: "right",
    size: 10,
    weight: 760,
    color: palette.muted,
  });
}

function architectureViewportModel(model, viewport) {
  const points = model.points.filter((point) => point.axle === viewport.axle);
  const pointIds = new Set(points.map((point) => point.id));
  return {
    points,
    links: model.links.filter((link) => pointIds.has(link.from) && pointIds.has(link.to)),
  };
}

function architectureSharedProjectionFrames(panelEntries) {
  const views = new Set(panelEntries.flatMap(({ panel }) => panel.views.map((viewport) => viewport.view)));
  return Object.fromEntries([...views].map((view) => [
    view,
    architectureProjectionFrame(panelEntries.flatMap(({ panelModel }) => panelModel.points), view),
  ]));
}

function architectureProjectionFrame(points, view) {
  if (!points.length) return { centerU: 0, centerV: 0, spanU: 1, spanV: 1 };
  const bounds = points
    .map((point) => projectAssemblyPoint(point, view))
    .reduce(
      (acc, point) => ({
        minU: Math.min(acc.minU, point.u),
        maxU: Math.max(acc.maxU, point.u),
        minV: Math.min(acc.minV, point.v),
        maxV: Math.max(acc.maxV, point.v),
      }),
      { minU: Infinity, maxU: -Infinity, minV: Infinity, maxV: -Infinity },
    );
  return {
    centerU: (bounds.minU + bounds.maxU) / 2,
    centerV: (bounds.minV + bounds.maxV) / 2,
    spanU: Math.max(0.1, bounds.maxU - bounds.minU),
    spanV: Math.max(0.1, bounds.maxV - bounds.minV),
  };
}

function projectArchitectureScene(model, viewport, sharedFrame = null) {
  const projected = model.points.map((point) => ({
    ...point,
    ...projectAssemblyPoint(point, viewport.view),
  }));
  const localFrame = architectureProjectionFrame(model.points, viewport.view);
  const scaleFrame = sharedFrame || localFrame;
  const scale = Math.min(
    Math.max(20, viewport.width - 52) / scaleFrame.spanU,
    Math.max(20, viewport.height - 32) / scaleFrame.spanV,
  );
  const map = new Map(projected.map((point) => [
    point.id,
    {
      ...point,
      x2: (point.u - localFrame.centerU) * scale + viewport.x + viewport.width / 2,
      y2: viewport.y + viewport.height / 2 - (point.v - localFrame.centerV) * scale + 10,
      architectureView: viewport.view,
    },
  ]));
  return { map, points: [...map.values()], scale, viewport };
}

function projectAssemblyPoint(point, view) {
  const { x, y, z } = point;
  if (view === "front") return { u: y, v: z, depth: -x };
  return { u: y, v: x, depth: z };
}

function drawArchitectureViewport(ctx, viewport) {
  const palette = canvasPalette();
  drawCanvasText(ctx, viewport.label, viewport.x + 4, viewport.y + 11, {
    size: 10,
    weight: 820,
    color: palette.muted,
  });
  const axis = viewport.view === "front" ? "Y / Z" : "Y / X";
  drawCanvasText(ctx, axis, viewport.x + viewport.width - 4, viewport.y + 11, {
    align: "right",
    size: 10,
    weight: 760,
    color: palette.muted,
  });
}

function drawArchitectureAssemblyScene(ctx, scene, model) {
  const { viewport } = scene;
  ctx.save();
  ctx.beginPath();
  ctx.rect(viewport.x + 1, viewport.y + 1, viewport.width - 2, viewport.height - 2);
  ctx.clip();
  drawArchitectureReferencePlane(ctx, scene.points, viewport);
  [...model.links]
    .sort((a, b) => ((scene.map.get(a.from)?.depth || 0) + (scene.map.get(a.to)?.depth || 0))
      - ((scene.map.get(b.from)?.depth || 0) + (scene.map.get(b.to)?.depth || 0)))
    .forEach((link) => drawCylinder(ctx, scene.map.get(link.from), scene.map.get(link.to), {
      ...link,
      width: Math.max(2, link.width * 0.78),
      opacity: Math.min(link.opacity ?? 1, link.detail ? 0.8 : 0.9),
    }));
  [...scene.points]
    .filter((point) => point.role !== "mass" && point.role !== "effective-mass")
    .sort((a, b) => a.depth - b.depth)
    .forEach((point) => drawSphere(ctx, { ...point, radius: Math.max(4, (point.radius || 5) * 0.78) }));
  ctx.restore();
}

function drawArchitectureReferencePlane(ctx, points, viewport) {
  const bounds = screenBounds(points.filter((point) => point.role !== "effective-mass" && point.role !== "mass"));
  if (!bounds) return;
  const palette = canvasPalette();
  const rect = expandedRect(bounds, 22);
  ctx.save();
  ctx.fillStyle = state.dark ? "rgba(106,167,232,0.035)" : "rgba(37,103,179,0.035)";
  ctx.strokeStyle = colorWithAlpha(palette.line, 0.72);
  ctx.lineWidth = 1;
  ctx.beginPath();
  if (viewport.view === "front") {
    if (ctx.roundRect) ctx.roundRect(rect.x, rect.y, rect.width, rect.height, 8);
    else ctx.rect(rect.x, rect.y, rect.width, rect.height);
  } else {
    ctx.ellipse(
      rect.x + rect.width / 2,
      rect.y + rect.height / 2,
      rect.width * 0.54,
      Math.max(30, rect.height * 0.34),
      0,
      0,
      Math.PI * 2,
    );
  }
  ctx.fill();
  ctx.stroke();
  ctx.restore();
}

function drawArchitectureAxle3d(ctx, points, axle, architecture, data, hotspots, hoverId, selectedId, viewport) {
  if (architecture.includes("bellcrank")) {
    drawArchitecturePickupReferences(ctx, points, axle, data, hotspots, hoverId, selectedId, viewport);
  }
}

function drawArchitecturePowertrain3d(ctx, points, profile, hotspots, hoverId, selectedId, viewport) {
  const mass = points.find((point) => point.id === "vehicle-mass");
  const fallback = screenBounds(points);
  if (!mass && !fallback) return;
  const cx = mass?.x2 || fallback.x + fallback.width / 2;
  const cy = mass?.y2 || fallback.y + fallback.height / 2;
  const rect = constrainRectToViewport({ x: cx - 78, y: cy - 34, width: 156, height: 68 }, viewport, 9, 31);
  const id = "architecture-powertrain";
  hotspots.push({ id, type: "powertrain", view: viewport.view, rect });
  drawArchitecture3dHotspotFrame(ctx, rect, id, hoverId, selectedId);
  drawArchitecturePowertrainBlock(ctx, rect.x + rect.width / 2, rect.y + rect.height / 2 + 4, 78, 34);
  drawArchitectureBadge(ctx, rect.x + 12, rect.y + 17, "Powertrain", profile.id, canvasPalette().green);
}

function drawArchitecturePowertrainSummary(ctx, width, profile, hotspots, hoverId, selectedId) {
  const rect = {
    x: Math.max(28, width - 238),
    y: 18,
    width: Math.min(210, width - 56),
    height: 46,
  };
  const id = "architecture-powertrain";
  hotspots.push({ id, type: "powertrain", rect });
  drawArchitecture3dHotspotFrame(ctx, rect, id, hoverId, selectedId);
  drawArchitectureBadge(ctx, rect.x + 12, rect.y + 17, "Powertrain", profile.id, canvasPalette().green);
}

function drawArchitecturePickupReferences(ctx, points, axle, data, hotspots, hoverId, selectedId, viewport) {
  const values = architectureOrderValuesForData(axle, data);
  const palette = canvasPalette();
  values.forEach((role, index) => {
    ["left", "right"].forEach((side) => {
      const point = points.find((item) => item.id === `${axle}-${side}-bellcrank-${role}`);
      if (!point) return;
      const id = `architecture-${axle}-pickup-${index}`;
      const radius = id === selectedId ? 12 : id === hoverId ? 11 : 10;
      const color = bellcrankRoleColor(role);
      ctx.save();
      ctx.fillStyle = colorWithAlpha(color, id === selectedId ? 0.36 : 0.24);
      ctx.strokeStyle = id === selectedId ? palette.amber : id === hoverId ? palette.blue : color;
      ctx.lineWidth = id === selectedId ? 3 : 2;
      ctx.beginPath();
      ctx.arc(point.x2, point.y2, radius, 0, Math.PI * 2);
      ctx.fill();
      ctx.stroke();
      drawCanvasText(ctx, String(index + 1), point.x2, point.y2, {
        align: "center",
        size: 9,
        weight: 860,
        color: palette.ink,
      });
      drawCanvasText(ctx, humanizeToken(role), point.x2 + 14, point.y2 - 13, {
        size: 9,
        weight: 760,
        color: palette.ink,
      });
      ctx.restore();
    });
  });
}

function drawArchitecture3dHotspotFrame(ctx, rect, id, hoverId, selectedId) {
  const palette = canvasPalette();
  const selected = id === selectedId;
  const active = selected || id === hoverId;
  ctx.save();
  ctx.fillStyle = active
    ? colorWithAlpha(selected ? palette.amber : palette.blue, state.dark ? 0.12 : 0.08)
    : colorWithAlpha(palette.surface, state.dark ? 0.06 : 0.14);
  ctx.strokeStyle = selected ? palette.amber : active ? palette.blue : colorWithAlpha(palette.line, 0.76);
  ctx.lineWidth = selected ? 2.5 : 1.25;
  ctx.beginPath();
  if (ctx.roundRect) ctx.roundRect(rect.x, rect.y, rect.width, rect.height, 8);
  else ctx.rect(rect.x, rect.y, rect.width, rect.height);
  ctx.fill();
  ctx.stroke();
  ctx.restore();
}

function drawArchitectureBadge(ctx, x, y, title, value, color) {
  const palette = canvasPalette();
  ctx.save();
  ctx.fillStyle = colorWithAlpha(color, state.dark ? 0.18 : 0.12);
  ctx.strokeStyle = colorWithAlpha(color, 0.48);
  ctx.lineWidth = 1;
  ctx.beginPath();
  if (ctx.roundRect) ctx.roundRect(x - 7, y - 11, 118, 38, 7);
  else ctx.rect(x - 7, y - 11, 118, 38);
  ctx.fill();
  ctx.stroke();
  ctx.restore();
  drawCanvasText(ctx, title, x, y - 1, { size: 11, weight: 820, color: palette.ink });
  drawCanvasText(ctx, value, x, y + 16, { size: 10, weight: 700, color: palette.muted });
}

function drawArchitecturePowertrainBlock(ctx, cx, cy, width, height) {
  const palette = canvasPalette();
  const depth = 14;
  ctx.save();
  ctx.fillStyle = state.dark ? "#1d2b23" : "#e8f5ee";
  ctx.strokeStyle = palette.green;
  ctx.lineWidth = 2;
  ctx.beginPath();
  ctx.rect(cx - width / 2, cy - height / 2, width, height);
  ctx.fill();
  ctx.stroke();
  ctx.fillStyle = state.dark ? "rgba(120,208,168,0.16)" : "rgba(33,131,91,0.14)";
  ctx.beginPath();
  ctx.moveTo(cx - width / 2, cy - height / 2);
  ctx.lineTo(cx - width / 2 + depth, cy - height / 2 - depth);
  ctx.lineTo(cx + width / 2 + depth, cy - height / 2 - depth);
  ctx.lineTo(cx + width / 2, cy - height / 2);
  ctx.closePath();
  ctx.fill();
  ctx.stroke();
  ctx.beginPath();
  ctx.moveTo(cx + width / 2, cy - height / 2);
  ctx.lineTo(cx + width / 2 + depth, cy - height / 2 - depth);
  ctx.lineTo(cx + width / 2 + depth, cy + height / 2 - depth);
  ctx.lineTo(cx + width / 2, cy + height / 2);
  ctx.closePath();
  ctx.fill();
  ctx.stroke();
  ctx.restore();
}

function screenBounds(points) {
  if (!points.length) return null;
  const bounds = points.reduce(
    (acc, point) => ({
      x: Math.min(acc.x, point.x2),
      y: Math.min(acc.y, point.y2),
      right: Math.max(acc.right, point.x2),
      bottom: Math.max(acc.bottom, point.y2),
    }),
    { x: Infinity, y: Infinity, right: -Infinity, bottom: -Infinity },
  );
  return {
    ...bounds,
    width: bounds.right - bounds.x,
    height: bounds.bottom - bounds.y,
  };
}

function expandedRect(bounds, padding) {
  return {
    x: bounds.x - padding,
    y: bounds.y - padding,
    width: bounds.right - bounds.x + padding * 2,
    height: bounds.bottom - bounds.y + padding * 2,
  };
}

function constrainRect(rect, width, height, margin = 18, topMargin = margin) {
  const maxX = Math.max(margin, width - rect.width - margin);
  const maxY = Math.max(topMargin, height - rect.height - margin);
  return {
    ...rect,
    x: clamp(rect.x, margin, maxX),
    y: clamp(rect.y, topMargin, maxY),
  };
}

function constrainRectToViewport(rect, viewport, margin = 8, topMargin = margin) {
  const minX = viewport.x + margin;
  const minY = viewport.y + topMargin;
  const maxX = Math.max(minX, viewport.x + viewport.width - rect.width - margin);
  const maxY = Math.max(minY, viewport.y + viewport.height - rect.height - margin);
  return {
    ...rect,
    x: clamp(rect.x, minX, maxX),
    y: clamp(rect.y, minY, maxY),
  };
}

function drawArchitectureAxle(ctx, cx, y, halfTrack, axle, architecture, data, hotspots, hoverId, selectedId) {
  const palette = canvasPalette();
  const id = `architecture-${axle}`;
  const rect = {
    x: cx - halfTrack - 68,
    y: y - 62,
    width: halfTrack * 2 + 136,
    height: 124,
  };
  hotspots.push({ id, type: "axle", axle, rect });
  drawArchitectureHotspotFrame(ctx, rect, id, hoverId, selectedId);
  ctx.strokeStyle = palette.blue;
  ctx.lineWidth = 4;
  ctx.lineCap = "round";
  ctx.beginPath();
  ctx.moveTo(cx - halfTrack, y);
  ctx.lineTo(cx + halfTrack, y);
  ctx.stroke();
  drawWheelGlyph(ctx, cx - halfTrack, y, 28, 0, palette.muted);
  drawWheelGlyph(ctx, cx + halfTrack, y, 28, 0, palette.muted);
  drawCanvasText(ctx, `${humanizeToken(axle)} axle`, rect.x + 14, rect.y + 20, { size: 12, weight: 820 });
  drawCanvasText(ctx, humanizeToken(architecture), rect.x + 14, rect.y + 40, {
    size: 11,
    weight: 680,
    color: palette.muted,
  });
  if (architecture.includes("bellcrank")) {
    drawBellcrankGlyph(ctx, cx - halfTrack * 0.45, y, axle);
    drawBellcrankGlyph(ctx, cx + halfTrack * 0.45, y, axle);
    drawArchitectureOrderPreview(ctx, rect.x + rect.width - 146, rect.y + 16, 124, 82, axle, data, hotspots, hoverId, selectedId);
  }
  if (architecture.includes("stabar")) {
    ctx.strokeStyle = "#7c5cc4";
    ctx.lineWidth = 4;
    ctx.beginPath();
    ctx.moveTo(cx - halfTrack * 0.65, y + 32);
    ctx.lineTo(cx + halfTrack * 0.65, y + 32);
    ctx.stroke();
    drawCanvasText(ctx, "Stabar", cx, y + 50, { align: "center", size: 10, weight: 720, color: palette.muted });
  }
}

function drawArchitecturePowertrain(ctx, cx, cy, profile, hotspots, hoverId, selectedId) {
  const palette = canvasPalette();
  const id = "architecture-powertrain";
  const rect = { x: cx - 86, y: cy - 44, width: 172, height: 88 };
  hotspots.push({ id, type: "powertrain", rect });
  drawArchitectureHotspotFrame(ctx, rect, id, hoverId, selectedId);
  drawPanel(ctx, rect.x + 12, rect.y + 16, rect.width - 24, rect.height - 32, state.dark ? "#1d2630" : "#f7f9fb");
  drawCanvasText(ctx, "Powertrain", cx, cy - 8, { align: "center", size: 12, weight: 820 });
  drawCanvasText(ctx, profile.id, cx, cy + 12, { align: "center", size: 11, weight: 680, color: palette.muted });
}

function drawArchitectureHotspotFrame(ctx, rect, id, hoverId, selectedId) {
  const palette = canvasPalette();
  const active = id === hoverId || id === selectedId;
  ctx.save();
  ctx.strokeStyle = id === selectedId ? palette.amber : active ? palette.blue : palette.line;
  ctx.fillStyle = active
    ? colorWithAlpha(id === selectedId ? palette.amber : palette.blue, state.dark ? 0.14 : 0.1)
    : colorWithAlpha(palette.surface, state.dark ? 0.16 : 0.42);
  ctx.lineWidth = id === selectedId ? 3 : 1.5;
  ctx.beginPath();
  if (ctx.roundRect) ctx.roundRect(rect.x, rect.y, rect.width, rect.height, 8);
  else ctx.rect(rect.x, rect.y, rect.width, rect.height);
  ctx.fill();
  ctx.stroke();
  ctx.restore();
}

function drawBellcrankGlyph(ctx, x, y, axle) {
  const palette = canvasPalette();
  ctx.save();
  ctx.strokeStyle = palette.amber;
  ctx.fillStyle = state.dark ? "rgba(225, 170, 92, 0.18)" : "rgba(168, 102, 18, 0.14)";
  ctx.lineWidth = 3;
  ctx.beginPath();
  ctx.moveTo(x, y - 24);
  ctx.lineTo(x - 22, y + 16);
  ctx.lineTo(x + 22, y + 16);
  ctx.closePath();
  ctx.fill();
  ctx.stroke();
  drawCanvasText(ctx, axle === "front" ? "BC" : "BC", x, y + 3, { align: "center", size: 10, weight: 820, color: palette.amber });
  ctx.restore();
}

function drawArchitectureOrderPreview(ctx, x, y, width, height, axle, data, hotspots, hoverId, selectedId) {
  const values = architectureOrderValuesForData(axle, data);
  if (!values.length) return;
  const palette = canvasPalette();
  const layout = bellcrankPickupLayout(values.length);
  const points = layout.map((item) => ({
    x: x + (item.x / 100) * width,
    y: y + (item.y / 100) * height,
  }));
  drawCanvasText(ctx, "Pickups", x, y - 2, { size: 10, weight: 820, color: palette.muted });
  ctx.save();
  ctx.strokeStyle = state.dark ? "rgba(225,170,92,0.55)" : "rgba(168,102,18,0.5)";
  ctx.fillStyle = state.dark ? "rgba(225,170,92,0.08)" : "rgba(168,102,18,0.08)";
  ctx.lineWidth = 2;
  ctx.beginPath();
  points.forEach((point, index) => {
    if (index === 0) ctx.moveTo(point.x, point.y);
    else ctx.lineTo(point.x, point.y);
  });
  if (points.length > 2) ctx.closePath();
  ctx.fill();
  ctx.stroke();
  ctx.restore();

  points.forEach((point, index) => {
    const value = values[index];
    const id = `architecture-${axle}-pickup-${index}`;
    const radius = id === selectedId ? 17 : id === hoverId ? 16 : 15;
    hotspots.push({
      id,
      type: "bellcrank-pickup",
      axle,
      index,
      rect: { x: point.x - 22, y: point.y - 22, width: 44, height: 44 },
    });
    ctx.save();
    ctx.fillStyle = colorWithAlpha(bellcrankRoleColor(value), id === selectedId ? 0.28 : 0.18);
    ctx.strokeStyle = id === selectedId ? palette.amber : id === hoverId ? palette.blue : bellcrankRoleColor(value);
    ctx.lineWidth = id === selectedId ? 3 : 2;
    ctx.beginPath();
    ctx.arc(point.x, point.y, radius, 0, Math.PI * 2);
    ctx.fill();
    ctx.stroke();
    drawCanvasText(ctx, String(index + 1), point.x, point.y - 3, { align: "center", size: 10, weight: 860 });
    drawCanvasText(ctx, humanizeToken(value), point.x, point.y + 18, {
      align: "center",
      size: 9,
      weight: 760,
      color: palette.ink,
    });
    ctx.restore();
  });
}

function drawArchitectureLegend(ctx, width, height, data) {
  const checks = mbdReadinessChecks(data);
  const ready = checks.filter((check) => check.ok).length;
  drawCanvasText(ctx, `${ready}/${checks.length} setup checks ready`, width - 28, height - 26, {
    align: "right",
    size: 12,
    weight: 760,
    color: ready === checks.length ? canvasPalette().green : canvasPalette().amber,
  });
}

function colorWithAlpha(color, alpha) {
  if (!String(color).startsWith("#") || String(color).length !== 7) return color;
  const r = Number.parseInt(color.slice(1, 3), 16);
  const g = Number.parseInt(color.slice(3, 5), 16);
  const b = Number.parseInt(color.slice(5, 7), 16);
  return `rgba(${r}, ${g}, ${b}, ${alpha})`;
}

function drawMbdReadinessPreview(ctx, width, height, data) {
  const palette = canvasPalette();
  drawPreviewGrid(ctx, width, height);
  const profile = powertrainProfile(data);
  const checks = mbdReadinessChecks(data);
  const byLabel = Object.fromEntries(checks.map((check) => [check.label, check]));
  drawCanvasText(ctx, "Vehicle Model", 28, 30, { size: 18, weight: 780 });
  drawCanvasText(ctx, `${architectureLabel(data)} | ${profile.label}`, 28, 52, {
    size: 12,
    weight: 650,
    color: palette.muted,
  });

  const top = 86;
  const gap = 14;
  const panelW = (width - 56 - gap * 2) / 3;
  const panelH = Math.min(250, height - top - 46);
  drawOverviewPanel(ctx, 28, top, panelW, panelH, "Assembly", [
    activeVehicleName(),
    architectureLabel(data),
    profile.id,
  ]);
  drawSimpleAssemblyFigure(ctx, 42, top + 98, panelW - 28, Math.max(90, panelH - 118), profile);

  drawOverviewPanel(ctx, 28 + panelW + gap, top, panelW, panelH, "Physics", []);
  drawSubsystemChecklist(ctx, 44 + panelW + gap, top + 56, panelW - 32, [
    byLabel.Geometry,
    byLabel.Mass,
    byLabel.Suspension,
    byLabel.Tires,
    byLabel.Aero,
    byLabel.Powertrain,
  ]);

  drawOverviewPanel(ctx, 28 + (panelW + gap) * 2, top, panelW, panelH, "Run", []);
  drawRunSummary(ctx, 44 + (panelW + gap) * 2, top + 58, panelW - 32, [
    byLabel.Backend,
    byLabel.Executable,
    byLabel.Architecture,
  ]);
}

function drawOverviewPanel(ctx, x, y, width, height, title, lines) {
  const palette = canvasPalette();
  drawPanel(ctx, x, y, width, height, palette.surface);
  drawCanvasText(ctx, title, x + 16, y + 22, { size: 13, weight: 820 });
  lines.slice(0, 3).forEach((line, index) => {
    drawCanvasText(ctx, line, x + 16, y + 52 + index * 20, {
      size: index === 0 ? 13 : 11,
      weight: index === 0 ? 760 : 680,
      color: index === 0 ? palette.ink : palette.muted,
    });
  });
}

function drawSimpleAssemblyFigure(ctx, x, y, width, height, profile) {
  const palette = canvasPalette();
  const nodes = [
    ["YAML", palette.blue],
    ["BobLib", palette.green],
    [profile.id, palette.amber],
    ["Sim", palette.magenta],
  ];
  const centerY = y + height / 2;
  const step = width / Math.max(1, nodes.length - 1);
  ctx.lineCap = "round";
  nodes.forEach(([label, color], index) => {
    const cx = x + index * step;
    if (index > 0) {
      ctx.strokeStyle = state.dark ? "#3c4a56" : "#cfd8e0";
      ctx.lineWidth = 3;
      ctx.beginPath();
      ctx.moveTo(x + (index - 1) * step + 20, centerY);
      ctx.lineTo(cx - 20, centerY);
      ctx.stroke();
    }
    ctx.fillStyle = color;
    ctx.beginPath();
    ctx.arc(cx, centerY, 16, 0, Math.PI * 2);
    ctx.fill();
    drawCanvasText(ctx, label, cx, centerY + 34, { align: "center", size: 10, weight: 740, color: palette.muted });
  });
}

function drawSubsystemChecklist(ctx, x, y, width, checks) {
  checks.filter(Boolean).forEach((check, index) => {
    const rowY = y + index * 28;
    drawStatusDot(ctx, x, rowY, check.ok);
    drawCanvasText(ctx, check.label, x + 18, rowY, { size: 12, weight: 760 });
    drawCanvasText(ctx, check.value, x + width, rowY, {
      size: 11,
      weight: 680,
      align: "right",
      color: canvasPalette().muted,
    });
  });
}

function drawRunSummary(ctx, x, y, width, checks) {
  checks.filter(Boolean).forEach((check, index) => {
    const rowY = y + index * 46;
    drawStatusDot(ctx, x, rowY, check.ok);
    drawCanvasText(ctx, check.label, x + 18, rowY, { size: 12, weight: 780 });
    drawCanvasText(ctx, check.value, x + 18, rowY + 18, { size: 11, weight: 680, color: canvasPalette().muted });
  });
  const okCount = checks.filter((check) => check?.ok).length;
  drawCanvasText(ctx, `${okCount}/${checks.filter(Boolean).length} ready`, x + width, y + 140, {
    align: "right",
    size: 13,
    weight: 780,
    color: okCount === checks.filter(Boolean).length ? canvasPalette().green : canvasPalette().amber,
  });
}

function drawStatusDot(ctx, x, y, ok) {
  const palette = canvasPalette();
  const color = ok ? palette.green : palette.amber;
  ctx.fillStyle = colorWithAlpha(color, state.dark ? 0.72 : 0.86);
  ctx.strokeStyle = colorWithAlpha(color, state.dark ? 0.55 : 0.7);
  ctx.lineWidth = 1;
  ctx.beginPath();
  ctx.arc(x + 5, y, 5, 0, Math.PI * 2);
  ctx.fill();
  ctx.stroke();
}

function drawAssemblyPipeline(ctx, x, y, width, profile) {
  const palette = canvasPalette();
  const nodes = [
    ["YAML", "Vehicle"],
    ["BobLib", "Modelica"],
    [profile.id, "Powertrain"],
    ["StandardSim", "Run"],
  ];
  const step = width / Math.max(1, nodes.length - 1);
  nodes.forEach(([label, meta], index) => {
    const cx = x + index * step;
    if (index > 0) {
      ctx.strokeStyle = palette.blue;
      ctx.lineWidth = 3;
      ctx.beginPath();
      ctx.moveTo(x + (index - 1) * step + 34, y);
      ctx.lineTo(cx - 34, y);
      ctx.stroke();
    }
    ctx.fillStyle = state.dark ? "#1d2630" : "#f7f9fb";
    ctx.strokeStyle = palette.line;
    ctx.lineWidth = 1;
    ctx.beginPath();
    if (ctx.roundRect) ctx.roundRect(cx - 34, y - 24, 68, 48, 8);
    else ctx.rect(cx - 34, y - 24, 68, 48);
    ctx.fill();
    ctx.stroke();
    drawCanvasText(ctx, label, cx, y - 5, { align: "center", size: 11, weight: 780 });
    drawCanvasText(ctx, meta, cx, y + 12, { align: "center", size: 9, weight: 650, color: palette.muted });
  });
}

function drawReadinessCard(ctx, x, y, width, height, check) {
  const palette = canvasPalette();
  const color = check.ok ? palette.green : palette.amber;
  drawPanel(ctx, x, y, width, height, palette.surface);
  ctx.fillStyle = colorWithAlpha(color, state.dark ? 0.72 : 0.86);
  ctx.beginPath();
  ctx.arc(x + 18, y + 22, 6, 0, Math.PI * 2);
  ctx.fill();
  drawCanvasText(ctx, check.label, x + 32, y + 22, { size: 12, weight: 780 });
  drawCanvasText(ctx, check.value, x + 12, y + 50, { size: 13, weight: 760 });
  drawCanvasText(ctx, check.detail, x + 12, y + 68, { size: 10, weight: 650, color: palette.muted });
}

function mbdReadinessChecks(data) {
  const repo = state.status?.repo || {};
  const model = buildVehicleGeometry(data);
  const hardpointCount = model.points.filter((point) => point.role === "hardpoint" || point.role === "steering").length;
  const massBlocks = massPropertyBlocks(data);
  const suspensionTables = [
    nestedValue(data, ["front", "actuation", "shock", "spring_table", "table"]),
    nestedValue(data, ["front", "actuation", "shock", "damper_table", "table"]),
    nestedValue(data, ["rear", "actuation", "shock", "spring_table", "table"]),
    nestedValue(data, ["rear", "actuation", "shock", "damper_table", "table"]),
  ];
  const aero = data.aero || {};
  const aeroMapCount = [
    aero.downforce_table_n,
    aero.drag_table_n,
    aero.my_table_nm,
    aero.mz_table_nm,
  ].filter((table) => Array.isArray(table) && table.length).length;
  const tireSides = state.tirePayload?.sides || [];
  const templates = state.vehicleTemplates?.templates || [];
  const profile = powertrainProfile(data);
  return [
    {
      label: "Backend",
      ok: Boolean(repo.boblib_package?.exists),
      value: repo.boblib_package?.exists ? "BobLib package found" : "BobLib package missing",
      detail: repo.boblib_package?.path || "_0_Utils/external/BobLib",
    },
    {
      label: "Executable",
      ok: Boolean(repo.vehicle_exe?.exists),
      value: repo.vehicle_exe?.exists ? "VehicleSim build ready" : "VehicleSim build pending",
      detail: repo.vehicle_exe?.path || "_3_StandardSim/BuildBobLib",
    },
    {
      label: "Architecture",
      ok: Boolean(data.architecture?.front && data.architecture?.rear && templates.length),
      value: architectureLabel(data),
      detail: `${templates.length} vehicle templates available`,
    },
    {
      label: "Geometry",
      ok: hardpointCount >= 18,
      value: `${hardpointCount} hardpoints`,
      detail: "suspension, steering, and actuation references",
    },
    {
      label: "Mass",
      ok: massBlocks >= 4,
      value: `${massBlocks} mass blocks`,
      detail: "mass, CG, and inertia source blocks",
    },
    {
      label: "Suspension",
      ok: suspensionTables.every((table) => hasTableRows(table, 2)),
      value: `${suspensionTables.filter((table) => hasTableRows(table, 2)).length}/4 rate tables`,
      detail: "front/rear spring and damper tables",
    },
    {
      label: "Tires",
      ok: tireSides.length >= 2,
      value: `${tireSides.length} MF52 evaluations`,
      detail: state.tirePayload?.model || "active .tir templates",
    },
    {
      label: "Aero",
      ok: aeroMapCount >= 2,
      value: `${aeroMapCount}/4 maps`,
      detail: "downforce, drag, pitch, and yaw maps",
    },
    {
      label: "Powertrain",
      ok: profile.status === "implemented",
      value: profile.id,
      detail: profile.components.join(" / "),
    },
  ];
}

function architectureLabel(data) {
  const architecture = data.architecture || {};
  return `${architecture.front || "front"} / ${architecture.rear || "rear"}`;
}

function hasTableRows(table, minRows = 2) {
  return Array.isArray(table) && table.filter((row) => Array.isArray(row) && row.length >= 2).length >= minRows;
}

function massPropertyBlocks(data) {
  const blocks = [data.sprung_mass, data.driver_mass];
  ["front", "rear"].forEach((axle) => {
    const masses = data[axle]?.masses || {};
    if (masses && typeof masses === "object" && !Array.isArray(masses)) blocks.push(...Object.values(masses));
  });
  return blocks.filter((block) => (
    block
    && Number.isFinite(Number(block.mass_kg))
    && Array.isArray(block.cg_m)
    && Array.isArray(block.inertia_kg_m2)
  )).length;
}

function drawAeroMapPreview(ctx, width, height, data) {
  const palette = canvasPalette();
  drawPreviewGrid(ctx, width, height);
  drawCanvasText(ctx, "Aero Maps", 28, 28, { size: 18, weight: 780 });
  drawCanvasText(ctx, `Reference speed ${formatNumber(data.aero?.reference_speed_m_per_s)} m/s`, 28, 50, {
    size: 12,
    weight: 650,
    color: palette.muted,
  });

  const aero = data.aero || {};
  const panels = [
    ["Downforce", aero.downforce_table_n, "N"],
    ["Drag", aero.drag_table_n, "N"],
    ["Pitch moment", aero.my_table_nm, "Nm"],
    ["Yaw moment", aero.mz_table_nm, "Nm"],
  ];
  const gap = 14;
  const top = 76;
  const panelWidth = (width - 56 - gap) / 2;
  const panelHeight = (height - top - 28 - gap) / 2;
  panels.forEach(([title, table, unit], index) => {
    const col = index % 2;
    const row = Math.floor(index / 2);
    drawHeatmapPanel(
      ctx,
      28 + col * (panelWidth + gap),
      top + row * (panelHeight + gap),
      panelWidth,
      panelHeight,
      title,
      table,
      aero.front_ride_height_grid_m,
      aero.rear_ride_height_grid_m,
      unit,
    );
  });
}

function drawHeatmapPanel(ctx, x, y, width, height, title, table, xGrid, yGrid, unit) {
  const palette = canvasPalette();
  drawPanel(ctx, x, y, width, height, state.dark ? "rgba(23,30,37,0.92)" : "rgba(255,255,255,0.94)");
  drawCanvasText(ctx, title, x + 12, y + 17, { size: 13, weight: 780 });
  if (!Array.isArray(table) || !table.length) {
    drawCanvasText(ctx, "No map", x + width / 2, y + height / 2, { align: "center", color: palette.muted });
    return;
  }
  const values = table.flat().map(Number).filter(Number.isFinite);
  const min = Math.min(...values);
  const max = Math.max(...values);
  drawCanvasText(ctx, `${formatNumber(min)} to ${formatNumber(max)} ${unit}`, x + width - 12, y + 17, {
    size: 11,
    weight: 650,
    align: "right",
    color: palette.muted,
  });
  const rows = table.length;
  const cols = Math.max(...table.map((row) => Array.isArray(row) ? row.length : 0));
  const chartX = x + 34;
  const chartY = y + 42;
  const chartW = width - 52;
  const chartH = height - 68;
  const cellW = chartW / Math.max(1, cols);
  const cellH = chartH / Math.max(1, rows);
  table.forEach((row, rowIndex) => {
    if (!Array.isArray(row)) return;
    row.forEach((value, colIndex) => {
      const numeric = Number(value);
      const t = max === min ? 0.5 : (numeric - min) / (max - min);
      ctx.fillStyle = heatColor(t);
      ctx.fillRect(chartX + colIndex * cellW, chartY + rowIndex * cellH, Math.ceil(cellW), Math.ceil(cellH));
    });
  });
  ctx.strokeStyle = palette.line;
  ctx.lineWidth = 1;
  ctx.strokeRect(chartX, chartY, chartW, chartH);
  drawCanvasText(ctx, "FRH", chartX + chartW / 2, y + height - 14, { size: 10, weight: 700, align: "center", color: palette.muted });
  drawCanvasText(ctx, "RRH", x + 14, chartY + chartH / 2, { size: 10, weight: 700, align: "center", color: palette.muted });
  drawCanvasText(ctx, formatNumber(Array.isArray(xGrid) ? xGrid[0] : ""), chartX, y + height - 14, { size: 9, weight: 650, color: palette.muted });
  drawCanvasText(ctx, formatNumber(Array.isArray(xGrid) ? xGrid[xGrid.length - 1] : ""), chartX + chartW, y + height - 14, {
    size: 9,
    weight: 650,
    align: "right",
    color: palette.muted,
  });
  drawCanvasText(ctx, formatNumber(Array.isArray(yGrid) ? yGrid[0] : ""), x + 12, chartY + chartH, {
    size: 9,
    weight: 650,
    align: "center",
    color: palette.muted,
  });
  drawCanvasText(ctx, formatNumber(Array.isArray(yGrid) ? yGrid[yGrid.length - 1] : ""), x + 12, chartY, {
    size: 9,
    weight: 650,
    align: "center",
    color: palette.muted,
  });
}

function heatColor(t) {
  const hue = 212 - Math.max(0, Math.min(1, t)) * 202;
  const saturation = state.dark ? 38 : 46;
  const light = state.dark ? 56 : 66;
  return `hsl(${hue}, ${saturation}%, ${light}%)`;
}

function drawPowertrainPreview(ctx, width, height, data) {
  const palette = canvasPalette();
  const profile = powertrainProfile(data);
  const explicit = explicitPowertrainData(data);
  drawPreviewGrid(ctx, width, height);
  drawCanvasText(ctx, "Powertrain Diagnostic", 28, 30, { size: 18, weight: 780 });
  drawCanvasText(ctx, profile.label, 28, 52, {
    size: 12,
    weight: 650,
    color: palette.muted,
  });

  const chainTop = 96;
  const chainHeight = Math.min(210, Math.max(150, height * 0.28));
  drawPowertrainChain(ctx, 28, chainTop, width - 56, chainHeight, profile.components);

  const metricTop = chainTop + chainHeight + 16;
  const metricGap = 12;
  const metricWidth = (width - 56 - metricGap * 3) / 4;
  const source = Object.keys(explicit).length ? "Explicit block" : "Vehicle name";
  const scalarEntries = flattenedPowertrainEntries(explicit);
  [
    ["Family", profile.id],
    ["Maturity", humanizeToken(profile.status)],
    ["Inputs", `${scalarEntries.length} scalar${scalarEntries.length === 1 ? "" : "s"}`],
    ["Source", source],
  ].forEach(([label, value], index) => {
    drawDiagnosticTile(ctx, 28 + index * (metricWidth + metricGap), metricTop, metricWidth, 78, label, value);
  });

  drawPowertrainStats(ctx, width, height, scalarEntries, metricTop + 98);
}

function drawPowertrainChain(ctx, x, y, width, height, nodes) {
  const palette = canvasPalette();
  drawPanel(ctx, x, y, width, height, palette.surface);
  const centerY = y + height / 2 + 12;
  const usable = Math.min(width - 150, 820);
  const startX = x + (width - usable) / 2;
  const gap = usable / Math.max(1, nodes.length - 1);
  const wheelY = [centerY - height * 0.34, centerY + height * 0.34];
  const wheelX = [startX - 36, startX + usable + 36];
  drawCanvasText(ctx, "Architecture", x + 14, y + 18, { size: 13, weight: 780 });
  wheelX.forEach((xPos) => {
    wheelY.forEach((yPos) => drawWheelGlyph(ctx, xPos, yPos, 24, 0, palette.muted));
  });
  nodes.forEach((node, index) => {
    const xPos = startX + index * gap;
    drawPanel(ctx, xPos - 54, centerY - 30, 108, 60, state.dark ? "#1d2630" : "#f7f9fb");
    drawCanvasText(ctx, node, xPos, centerY, { align: "center", size: 12, weight: 760 });
    if (index > 0) {
      ctx.strokeStyle = palette.blue;
      ctx.lineWidth = 4;
      ctx.lineCap = "round";
      ctx.beginPath();
      ctx.moveTo(startX + (index - 1) * gap + 55, centerY);
      ctx.lineTo(xPos - 55, centerY);
      ctx.stroke();
    }
  });
  const lastX = startX + (nodes.length - 1) * gap;
  ctx.strokeStyle = palette.green;
  ctx.lineWidth = 3;
  wheelY.forEach((yPos) => {
    ctx.beginPath();
    ctx.moveTo(lastX + 54, centerY);
    ctx.lineTo(wheelX[1] - 28, yPos);
    ctx.stroke();
  });
}

function powertrainTokens(data) {
  return powertrainProfile(data).components;
}

function powertrainProfile(data) {
  const implementations = availablePowertrains();
  const explicit = explicitPowertrainData(data);
  const rawName = String(data.vehicle?.name || "");
  const namePrefix = rawName.split("_", 1)[0];
  const explicitId = typeof explicit.implementation === "string" ? explicit.implementation : "";
  const id = explicitId || namePrefix || implementations[0]?.id || "EVBatInvMotDiff";
  const matched = implementations.find((item) => item.id === id) || implementations[0] || {};
  const components = Array.isArray(matched.components) && matched.components.length
    ? matched.components
    : ["Battery", "Inverter", "Motor", "Differential"];
  return {
    id: matched.id || id,
    label: matched.label || humanizeToken(id),
    status: matched.status || "available",
    components,
  };
}

function explicitPowertrainData(data) {
  const powertrain = data.powertrain || data.drivetrain || {};
  return typeof powertrain === "object" && !Array.isArray(powertrain) && powertrain ? powertrain : {};
}

function flattenedPowertrainEntries(value, prefix = "") {
  if (!value || typeof value !== "object" || Array.isArray(value)) return [];
  return Object.entries(value).flatMap(([key, item]) => {
    const label = prefix ? `${prefix}.${key}` : key;
    if (typeof item === "number" || typeof item === "string" || typeof item === "boolean") return [[label, item]];
    if (item && typeof item === "object" && !Array.isArray(item)) return flattenedPowertrainEntries(item, label);
    return [];
  });
}

function drawDiagnosticTile(ctx, x, y, width, height, label, value) {
  const palette = canvasPalette();
  drawPanel(ctx, x, y, width, height, palette.surface);
  drawCanvasText(ctx, label, x + 12, y + 18, { size: 11, weight: 740, color: palette.muted });
  drawCanvasText(ctx, value, x + 12, y + 48, { size: 13, weight: 780 });
}

function drawPowertrainStats(ctx, width, height, entries, top) {
  const palette = canvasPalette();
  const panelX = 28;
  const panelY = top;
  const panelW = width - 56;
  const panelH = Math.max(110, height - top - 28);
  drawPanel(ctx, panelX, panelY, panelW, panelH, palette.surface);
  drawCanvasText(ctx, "Live Inputs", panelX + 14, panelY + 18, { size: 13, weight: 780 });
  if (!entries.length) {
    drawCanvasText(ctx, "No explicit powertrain scalars in vehicle.yml", panelX + panelW / 2, panelY + panelH / 2, {
      align: "center",
      color: palette.muted,
    });
    return;
  }
  entries.slice(0, 12).forEach(([key, value], index) => {
    const col = index % 3;
    const row = Math.floor(index / 3);
    const cellW = (panelW - 28 - 24) / 3;
    const x = panelX + 14 + col * (cellW + 12);
    const y = panelY + 48 + row * 42;
    drawCanvasText(ctx, humanizeToken(key), x, y, { size: 10, weight: 700, color: palette.muted });
    drawCanvasText(ctx, formatDisplayValue(value), x, y + 18, { size: 13, weight: 760 });
  });
}

function drawTirePreview(ctx, width, height, data) {
  const palette = canvasPalette();
  drawPreviewGrid(ctx, width, height);
  drawCanvasText(ctx, "Tires", 28, 30, { size: 18, weight: 780 });
  drawCanvasText(ctx, state.tirePayload?.model || `${data.front?.tire?.template || "front tire"} / ${data.rear?.tire?.template || "rear tire"}`, 28, 52, {
    size: 12,
    weight: 650,
    color: palette.muted,
  });

  const leftWidth = Math.min(390, Math.max(280, width * 0.36));
  drawTireStancePanel(ctx, 28, 78, leftWidth, height - 106, data);

  const chartX = 42 + leftWidth;
  const chartW = width - chartX - 28;
  const chartGap = 12;
  const chartH = (height - 78 - 28 - chartGap) / 2;
  const chartW2 = (chartW - chartGap) / 2;
  const sides = state.tirePayload?.sides || [];
  drawSeriesPanel(
    ctx,
    chartX,
    78,
    chartW2,
    chartH,
    "Pure Fx",
    sides.map((side) => ({
      label: `${humanizeToken(side.side)} ${formatNumber(side.fz_n)} N`,
      color: side.side === "front" ? palette.blue : palette.green,
      points: side.curves?.pure?.longitudinal || side.curves?.longitudinal || [],
      xKey: "kappa",
      yKey: "fx_n",
    })),
    "kappa",
    "Fx N",
  );
  drawSeriesPanel(
    ctx,
    chartX + chartW2 + chartGap,
    78,
    chartW2,
    chartH,
    "Pure Fy",
    sides.map((side) => ({
      label: `${humanizeToken(side.side)} ${formatNumber(side.camber_deg)} deg`,
      color: side.side === "front" ? palette.blue : palette.green,
      points: side.curves?.pure?.lateral || side.curves?.lateral || [],
      xKey: "alpha_deg",
      yKey: "fy_n",
    })),
    "alpha deg",
    "Fy N",
  );
  drawSeriesPanel(
    ctx,
    chartX,
    78 + chartH + chartGap,
    chartW2,
    chartH,
    "Combined Fx",
    combinedFxSeries(sides, palette),
    "kappa",
    "Fx N",
  );
  drawSeriesPanel(
    ctx,
    chartX + chartW2 + chartGap,
    78 + chartH + chartGap,
    chartW2,
    chartH,
    "Combined Fy",
    combinedFySeries(sides, palette),
    "alpha deg",
    "Fy N",
  );
}

function combinedFxSeries(sides, palette) {
  const colors = [palette.blue, palette.green, palette.red, palette.amber, palette.magenta, palette.muted];
  return sides.flatMap((side, sideIndex) => (
    (side.curves?.combined?.fx_by_alpha || []).map((curve, curveIndex) => ({
      label: `${humanizeToken(side.side)} a=${formatNumber(curve.alpha_deg)}`,
      color: colors[(sideIndex * 3 + curveIndex) % colors.length],
      points: curve.points || [],
      xKey: "kappa",
      yKey: "fx_n",
    }))
  ));
}

function combinedFySeries(sides, palette) {
  const colors = [palette.blue, palette.green, palette.red, palette.amber, palette.magenta, palette.muted];
  return sides.flatMap((side, sideIndex) => (
    (side.curves?.combined?.fy_by_kappa || []).map((curve, curveIndex) => ({
      label: `${humanizeToken(side.side)} k=${formatNumber(curve.kappa)}`,
      color: colors[(sideIndex * 3 + curveIndex) % colors.length],
      points: curve.points || [],
      xKey: "alpha_deg",
      yKey: "fy_n",
    }))
  ));
}

function drawTireStancePanel(ctx, x, y, width, height, data) {
  const palette = canvasPalette();
  drawPanel(ctx, x, y, width, height, palette.surface);
  drawCanvasText(ctx, "Setup", x + 14, y + 18, { size: 13, weight: 780 });
  drawCanvasText(ctx, `${data.front?.tire?.template || "front"} / ${data.rear?.tire?.template || "rear"}`, x + width - 14, y + 18, {
    size: 11,
    weight: 650,
    align: "right",
    color: palette.muted,
  });
  const front = data.front || {};
  const rear = data.rear || {};
  const track = Math.min(width * 0.52, 230);
  const wheelbase = Math.min(height * 0.46, 260);
  const cx = x + width / 2;
  const cy = y + height / 2 + 10;
  const axles = [
    { name: "Front", axle: front, x: cx + wheelbase / 2 },
    { name: "Rear", axle: rear, x: cx - wheelbase / 2 },
  ];
  ctx.strokeStyle = palette.line;
  ctx.lineWidth = 3;
  ctx.beginPath();
  ctx.moveTo(cx - wheelbase / 2, cy);
  ctx.lineTo(cx + wheelbase / 2, cy);
  ctx.stroke();
  axles.forEach(({ name, axle, x }) => {
    const radius = Math.max(22, Math.min(54, Number(axle.wheel?.radius_m || 0.2) * 190));
    const toe = Number(axle.wheel?.toe_deg || 0) * Math.PI / 180;
    const camber = Number(axle.wheel?.camber_deg || 0);
    [-1, 1].forEach((side) => {
      const y = cy + side * track / 2;
      drawWheelGlyph(ctx, x, y, radius, toe * side, side > 0 ? palette.blue : palette.green);
      ctx.strokeStyle = palette.magenta;
      ctx.lineWidth = 2;
      ctx.beginPath();
      ctx.moveTo(x - radius * 0.7, y - camber * 1.8);
      ctx.lineTo(x + radius * 0.7, y + camber * 1.8);
      ctx.stroke();
    });
    drawCanvasText(ctx, name, x, cy - track / 2 - 34, { align: "center", size: 13, weight: 780 });
    drawCanvasText(ctx, `${formatNumber(axle.wheel?.radius_m)} m`, x, cy + track / 2 + 34, {
      align: "center",
      size: 11,
      weight: 700,
      color: palette.muted,
    });
  });
}

function drawSeriesPanel(ctx, x, y, width, height, title, series, xLabel, yLabel) {
  const palette = canvasPalette();
  drawPanel(ctx, x, y, width, height, palette.surface);
  drawCanvasText(ctx, title, x + 12, y + 17, { size: 13, weight: 780 });
  const usableSeries = series.filter((item) => Array.isArray(item.points) && item.points.length);
  if (!usableSeries.length) {
    drawCanvasText(ctx, "No tire curve data", x + width / 2, y + height / 2, {
      align: "center",
      color: palette.muted,
    });
    return;
  }
  const allPoints = usableSeries.flatMap((item) => item.points.map((point) => ({
    x: Number(point[item.xKey]),
    y: Number(point[item.yKey]),
  }))).filter((point) => Number.isFinite(point.x) && Number.isFinite(point.y));
  if (!allPoints.length) return;
  const minX = Math.min(...allPoints.map((point) => point.x));
  const maxX = Math.max(...allPoints.map((point) => point.x));
  const minY = Math.min(...allPoints.map((point) => point.y));
  const maxY = Math.max(...allPoints.map((point) => point.y));
  const chartX = x + 44;
  const chartY = y + 38;
  const chartW = width - 62;
  const chartH = height - 68;
  ctx.strokeStyle = palette.line;
  ctx.lineWidth = 1;
  ctx.strokeRect(chartX, chartY, chartW, chartH);
  if (minY < 0 && maxY > 0) {
    const zeroY = chartY + chartH - ((0 - minY) / (maxY - minY)) * chartH;
    ctx.strokeStyle = state.dark ? "#44515e" : "#c7d0d8";
    ctx.beginPath();
    ctx.moveTo(chartX, zeroY);
    ctx.lineTo(chartX + chartW, zeroY);
    ctx.stroke();
  }
  usableSeries.forEach((item) => {
    ctx.strokeStyle = item.color;
    ctx.lineWidth = 2.5;
    ctx.lineJoin = "round";
    ctx.beginPath();
    item.points.forEach((point, index) => {
      const rawX = Number(point[item.xKey]);
      const rawY = Number(point[item.yKey]);
      const px = chartX + ((rawX - minX) / Math.max(1e-9, maxX - minX)) * chartW;
      const py = chartY + chartH - ((rawY - minY) / Math.max(1e-9, maxY - minY)) * chartH;
      if (index === 0) ctx.moveTo(px, py);
      else ctx.lineTo(px, py);
    });
    ctx.stroke();
  });
  usableSeries.slice(0, 4).forEach((item, index) => {
    const lx = x + width - 14 - (index % 2) * 102;
    const ly = y + 18 + Math.floor(index / 2) * 17;
    ctx.strokeStyle = item.color;
    ctx.lineWidth = 3;
    ctx.beginPath();
    ctx.moveTo(lx - 50, ly);
    ctx.lineTo(lx - 30, ly);
    ctx.stroke();
    drawCanvasText(ctx, item.label, lx - 26, ly, { size: 10, weight: 650, color: palette.muted });
  });
  drawCanvasText(ctx, xLabel, chartX + chartW / 2, y + height - 13, { size: 10, weight: 700, align: "center", color: palette.muted });
  drawCanvasText(ctx, yLabel, x + 18, chartY + chartH / 2, { size: 10, weight: 700, align: "center", color: palette.muted });
  drawCanvasText(ctx, `${formatNumber(minY)} to ${formatNumber(maxY)}`, x + width - 12, y + height - 13, {
    size: 10,
    weight: 650,
    align: "right",
    color: palette.muted,
  });
}

function drawWheelGlyph(ctx, x, y, radius, angle, color) {
  const palette = canvasPalette();
  ctx.save();
  ctx.translate(x, y);
  ctx.rotate(angle);
  ctx.fillStyle = state.dark ? "#0f151b" : "#edf1f4";
  ctx.strokeStyle = color || palette.muted;
  ctx.lineWidth = 4;
  ctx.beginPath();
  ctx.ellipse(0, 0, radius * 0.72, radius, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.stroke();
  ctx.strokeStyle = palette.line;
  ctx.lineWidth = 2;
  ctx.beginPath();
  ctx.ellipse(0, 0, radius * 0.36, radius * 0.5, 0, 0, Math.PI * 2);
  ctx.stroke();
  ctx.restore();
}

function drawSuspensionPreview(ctx, width, height, data) {
  const palette = canvasPalette();
  drawPreviewGrid(ctx, width, height);
  drawCanvasText(ctx, "Suspension Rates", 28, 30, { size: 18, weight: 780 });
  drawCanvasText(ctx, "Live spring and damper tables from vehicle.yml", 28, 52, { size: 12, weight: 650, color: palette.muted });
  const maps = [
    ["Front spring", nestedValue(data, ["front", "actuation", "shock", "spring_table", "table"]), "deflection", "force"],
    ["Front damper", nestedValue(data, ["front", "actuation", "shock", "damper_table", "table"]), "velocity", "force"],
    ["Rear spring", nestedValue(data, ["rear", "actuation", "shock", "spring_table", "table"]), "deflection", "force"],
    ["Rear damper", nestedValue(data, ["rear", "actuation", "shock", "damper_table", "table"]), "velocity", "force"],
  ];
  const gap = 14;
  const top = 76;
  const panelWidth = (width - 56 - gap) / 2;
  const panelHeight = (height - top - 28 - gap) / 2;
  maps.forEach(([title, table, xLabel, yLabel], index) => {
    const col = index % 2;
    const row = Math.floor(index / 2);
    drawLinePanel(ctx, 28 + col * (panelWidth + gap), top + row * (panelHeight + gap), panelWidth, panelHeight, title, table, xLabel, yLabel);
  });
}

function drawCompliancePreview(ctx, width, height, data) {
  const palette = canvasPalette();
  const torsionalStiffness = Number(nestedValue(data, ["body", "torsional_stiff_n_m_per_rad"]));
  const hasTorsionalStiffness = Number.isFinite(torsionalStiffness) && torsionalStiffness > 0;
  const channels = compliancePreviewChannels(data);
  drawPreviewGrid(ctx, width, height);
  drawCanvasText(ctx, "Compliances", 28, 30, { size: 18, weight: 780 });
  drawCanvasText(ctx, "Chassis torsion is active. Wheel compliance channels are staged for BobLib wiring.", 28, 52, {
    size: 12,
    weight: 650,
    color: palette.muted,
  });

  const top = 76;
  const gap = 14;
  const panelWidth = width - 56;
  const sketchHeight = Math.min(Math.max(176, height * 0.42), 260);
  const matrixHeight = Math.max(122, height - top - sketchHeight - gap - 28);
  drawPanel(ctx, 28, top, panelWidth, sketchHeight, palette.surface);
  drawCleanComplianceChassis(ctx, 28, top, panelWidth, sketchHeight, {
    active: hasTorsionalStiffness,
    value: torsionalStiffness,
  });
  drawComplianceChannelMatrix(ctx, 28, top + sketchHeight + gap, panelWidth, matrixHeight, channels);
}

function compliancePreviewChannels(data) {
  return [
    {
      label: "Wheel center X / Fx",
      unit: "m/N",
      front: nestedValue(data, ["front", "compliances", "wheel_center_x_per_fx_m_per_n"]),
      rear: nestedValue(data, ["rear", "compliances", "wheel_center_x_per_fx_m_per_n"]),
    },
    {
      label: "Wheel center Y / Fy",
      unit: "m/N",
      front: nestedValue(data, ["front", "compliances", "wheel_center_y_per_fy_m_per_n"]),
      rear: nestedValue(data, ["rear", "compliances", "wheel_center_y_per_fy_m_per_n"]),
    },
    {
      label: "Toe / Mz",
      unit: "rad/(N m)",
      front: nestedValue(data, ["front", "compliances", "toe_per_mz_rad_per_n_m"]),
      rear: nestedValue(data, ["rear", "compliances", "toe_per_mz_rad_per_n_m"]),
    },
    {
      label: "Camber / Fy",
      unit: "rad/N",
      front: nestedValue(data, ["front", "compliances", "camber_per_fy_rad_per_n"]),
      rear: nestedValue(data, ["rear", "compliances", "camber_per_fy_rad_per_n"]),
    },
  ];
}

function drawCleanComplianceChassis(ctx, x, y, width, height, { active, value }) {
  const palette = canvasPalette();
  const tileMinWidth = Math.min(210, Math.max(140, width * 0.36));
  const diagramWidth = Math.max(
    150,
    Math.min(width * 0.56, 560, width - 22 - 20 - tileMinWidth - 18),
  );
  const diagramX = x + 22;
  const diagramY = y + 42;
  const diagramH = height - 62;
  const centerY = diagramY + diagramH / 2;
  const bodyLeft = diagramX + 50;
  const bodyRight = diagramX + diagramWidth - 34;
  const halfTrack = Math.min(56, diagramH * 0.34);
  const axleInset = Math.max(36, (bodyRight - bodyLeft) * 0.16);
  const frontX = bodyLeft + axleInset;
  const rearX = bodyRight - axleInset;

  drawCanvasText(ctx, "Chassis torsional stiffness", x + 14, y + 20, { size: 13, weight: 780 });
  ctx.save();
  ctx.lineCap = "round";
  ctx.lineJoin = "round";

  ctx.strokeStyle = colorWithAlpha(palette.line, 0.9);
  ctx.lineWidth = 6;
  ctx.beginPath();
  ctx.moveTo(bodyLeft, centerY - halfTrack);
  ctx.lineTo(bodyRight, centerY - halfTrack);
  ctx.moveTo(bodyLeft, centerY + halfTrack);
  ctx.lineTo(bodyRight, centerY + halfTrack);
  ctx.moveTo(frontX, centerY - halfTrack - 14);
  ctx.lineTo(frontX, centerY + halfTrack + 14);
  ctx.moveTo(rearX, centerY - halfTrack - 14);
  ctx.lineTo(rearX, centerY + halfTrack + 14);
  ctx.stroke();

  ctx.strokeStyle = active ? palette.magenta : palette.muted;
  ctx.lineWidth = 3;
  ctx.beginPath();
  ctx.moveTo(bodyLeft, centerY - halfTrack);
  ctx.lineTo(bodyRight, centerY + halfTrack);
  ctx.moveTo(bodyLeft, centerY + halfTrack);
  ctx.lineTo(bodyRight, centerY - halfTrack);
  ctx.stroke();

  [
    [frontX, centerY - halfTrack],
    [frontX, centerY + halfTrack],
    [rearX, centerY - halfTrack],
    [rearX, centerY + halfTrack],
  ].forEach(([px, py]) => {
    ctx.fillStyle = active ? palette.magenta : palette.muted;
    ctx.beginPath();
    ctx.arc(px, py, 6, 0, Math.PI * 2);
    ctx.fill();
  });

  ctx.strokeStyle = palette.blue;
  ctx.lineWidth = 3;
  drawComplianceArrow(ctx, frontX, centerY, -1);
  drawComplianceArrow(ctx, rearX, centerY, 1);
  ctx.restore();

  drawCanvasText(ctx, "front torque", frontX, centerY + halfTrack + 32, { size: 10, weight: 720, align: "center", color: palette.muted });
  drawCanvasText(ctx, "rear reaction", rearX, centerY + halfTrack + 32, { size: 10, weight: 720, align: "center", color: palette.muted });

  const tileX = diagramX + diagramWidth + 20;
  const tileW = Math.max(120, x + width - tileX - 18);
  const tileY = y + 48;
  const tileH = Math.max(96, height - 76);
  drawPanel(ctx, tileX, tileY, tileW, tileH, state.dark ? "#1d2630" : "#f7f9fb");
  drawCanvasText(ctx, "Active input", tileX + 14, tileY + 20, { size: 11, weight: 760, color: palette.muted });
  drawCanvasText(ctx, active ? `${formatNumber(value)} N m/rad` : "Unset", tileX + 14, tileY + 51, {
    size: tileW < 160 ? 13 : 17,
    weight: 820,
    color: active ? palette.ink : palette.muted,
  });
  drawCanvasText(ctx, "k = torque / twist", tileX + 14, tileY + 82, { size: 11, weight: 700, color: palette.muted });
}

function drawComplianceArrow(ctx, x, y, direction) {
  const radius = 28;
  const start = direction > 0 ? -0.8 : Math.PI - 0.8;
  const end = direction > 0 ? 0.8 : Math.PI + 0.8;
  ctx.beginPath();
  ctx.arc(x, y, radius, start, end, direction < 0);
  ctx.stroke();
  const arrowX = x + Math.cos(end) * radius;
  const arrowY = y + Math.sin(end) * radius;
  ctx.beginPath();
  ctx.moveTo(arrowX, arrowY);
  ctx.lineTo(arrowX - direction * 8, arrowY - 5);
  ctx.lineTo(arrowX - direction * 4, arrowY + 8);
  ctx.stroke();
}

function drawComplianceChannelMatrix(ctx, x, y, width, height, channels) {
  const palette = canvasPalette();
  drawPanel(ctx, x, y, width, height, palette.surface);
  drawCanvasText(ctx, "Wheel compliance channels", x + 14, y + 20, { size: 13, weight: 780 });
  if (width > 560) {
    drawCanvasText(ctx, "Inputs reserved for the compliance layer.", x + width - 14, y + 20, {
      size: 11,
      weight: 650,
      align: "right",
      color: palette.muted,
    });
  }
  const tableX = x + 14;
  const tableY = y + 42;
  const tableW = width - 28;
  const rowH = Math.max(28, Math.min(38, (height - 56) / Math.max(1, channels.length + 1)));
  const labelW = Math.max(150, Math.min(260, tableW * 0.36));
  const unitW = Math.max(82, Math.min(120, tableW * 0.18));
  const cellW = (tableW - labelW - unitW) / 2;

  drawComplianceMatrixCell(ctx, tableX, tableY, labelW, rowH, "Channel", true);
  drawComplianceMatrixCell(ctx, tableX + labelW, tableY, cellW, rowH, "Front", true);
  drawComplianceMatrixCell(ctx, tableX + labelW + cellW, tableY, cellW, rowH, "Rear", true);
  drawComplianceMatrixCell(ctx, tableX + labelW + cellW * 2, tableY, unitW, rowH, "Unit", true);
  channels.forEach((channel, index) => {
    const rowY = tableY + rowH * (index + 1);
    drawComplianceMatrixCell(ctx, tableX, rowY, labelW, rowH, channel.label, false);
    drawComplianceMatrixCell(ctx, tableX + labelW, rowY, cellW, rowH, complianceCellValue(channel.front), false, true);
    drawComplianceMatrixCell(ctx, tableX + labelW + cellW, rowY, cellW, rowH, complianceCellValue(channel.rear), false, true);
    drawComplianceMatrixCell(ctx, tableX + labelW + cellW * 2, rowY, unitW, rowH, channel.unit, false);
  });
}

function drawComplianceMatrixCell(ctx, x, y, width, height, text, header = false, staged = false) {
  const palette = canvasPalette();
  ctx.save();
  ctx.fillStyle = header
    ? colorWithAlpha(palette.blue, state.dark ? 0.16 : 0.12)
    : staged
      ? colorWithAlpha(palette.muted, state.dark ? 0.08 : 0.1)
      : colorWithAlpha(palette.bg, 0.55);
  ctx.strokeStyle = palette.line;
  ctx.lineWidth = 1;
  ctx.fillRect(x, y, width, height);
  ctx.strokeRect(x, y, width, height);
  ctx.restore();
  drawCanvasText(ctx, text, x + 10, y + height / 2, {
    size: 10,
    weight: header ? 800 : staged ? 740 : 700,
    color: staged ? palette.muted : palette.ink,
  });
}

function complianceCellValue(value) {
  const numeric = Number(value);
  return Number.isFinite(numeric) ? formatNumber(numeric) : "planned";
}

function drawLinePanel(ctx, x, y, width, height, title, table, xLabel, yLabel) {
  const palette = canvasPalette();
  drawPanel(ctx, x, y, width, height, palette.surface);
  drawCanvasText(ctx, title, x + 12, y + 17, { size: 13, weight: 780 });
  if (!Array.isArray(table) || table.length < 2) {
    drawCanvasText(ctx, "No table", x + width / 2, y + height / 2, { align: "center", color: palette.muted });
    return;
  }
  const points = table
    .map((row) => Array.isArray(row) ? [Number(row[0]), Number(row[1])] : null)
    .filter((point) => point && Number.isFinite(point[0]) && Number.isFinite(point[1]));
  if (points.length < 2) return;
  const xs = points.map((point) => point[0]);
  const ys = points.map((point) => point[1]);
  const minX = Math.min(...xs);
  const maxX = Math.max(...xs);
  const minY = Math.min(...ys);
  const maxY = Math.max(...ys);
  const chartX = x + 42;
  const chartY = y + 40;
  const chartW = width - 60;
  const chartH = height - 70;
  ctx.strokeStyle = palette.line;
  ctx.lineWidth = 1;
  ctx.strokeRect(chartX, chartY, chartW, chartH);
  ctx.strokeStyle = palette.blue;
  ctx.lineWidth = 3;
  ctx.lineJoin = "round";
  ctx.beginPath();
  points.forEach((point, index) => {
    const px = chartX + ((point[0] - minX) / Math.max(1e-9, maxX - minX)) * chartW;
    const py = chartY + chartH - ((point[1] - minY) / Math.max(1e-9, maxY - minY)) * chartH;
    if (index === 0) ctx.moveTo(px, py);
    else ctx.lineTo(px, py);
  });
  ctx.stroke();
  drawCanvasText(ctx, xLabel, chartX + chartW / 2, y + height - 14, { size: 10, weight: 700, align: "center", color: palette.muted });
  drawCanvasText(ctx, yLabel, x + 16, chartY + chartH / 2, { size: 10, weight: 700, align: "center", color: palette.muted });
  drawCanvasText(ctx, `${formatNumber(minY)} to ${formatNumber(maxY)}`, x + width - 12, y + 17, {
    size: 11,
    weight: 650,
    align: "right",
    color: palette.muted,
  });
}

function nestedValue(data, path) {
  return path.reduce((current, part) => current?.[part], data);
}

function humanizeToken(value) {
  return String(value)
    .replaceAll("_", " ")
    .replace(/([a-z])([A-Z])/g, "$1 $2")
    .replace(/\b\w/g, (char) => char.toUpperCase());
}

function formatNumber(value) {
  const numeric = Number(value);
  if (!Number.isFinite(numeric)) return "";
  if (Math.abs(numeric) >= 1000) return numeric.toFixed(0);
  if (Math.abs(numeric) >= 10) return numeric.toFixed(1).replace(/\.0$/, "");
  return numeric.toFixed(3).replace(/\.?0+$/, "");
}

function formatDisplayValue(value) {
  if (typeof value === "number") return formatNumber(value);
  if (typeof value === "boolean") return value ? "true" : "false";
  return String(value ?? "");
}

function projectPoint(point, view) {
  return projectPointWithAngles(point, view, state.vehiclePreviewYaw, state.vehiclePreviewPitch);
}

function projectPointWithAngles(point, view, yaw, pitch) {
  const { x, y, z } = point;
  if (view === "side") return { u: x, v: z, depth: y };
  if (view === "top") return { u: x, v: y, depth: z };
  const cy = Math.cos(yaw);
  const sy = Math.sin(yaw);
  const cp = Math.cos(pitch);
  const sp = Math.sin(pitch);
  const xr = x * cy - y * sy;
  const yr = x * sy + y * cy;
  return { u: xr, v: z * cp - yr * sp, depth: yr * cp + z * sp };
}

function vehicleModelFrame(model) {
  const points = model.points || [];
  if (!points.length) return { center: { x: 0, y: 0, z: 0 }, radius: 1 };
  const bounds = points.reduce(
    (acc, point) => {
      const shell = point.shellRadiusM || 0;
      return {
        minX: Math.min(acc.minX, point.x - shell),
        maxX: Math.max(acc.maxX, point.x + shell),
        minY: Math.min(acc.minY, point.y - shell),
        maxY: Math.max(acc.maxY, point.y + shell),
        minZ: Math.min(acc.minZ, point.z - shell),
        maxZ: Math.max(acc.maxZ, point.z + shell),
      };
    },
    { minX: Infinity, maxX: -Infinity, minY: Infinity, maxY: -Infinity, minZ: Infinity, maxZ: -Infinity },
  );
  const center = {
    x: (bounds.minX + bounds.maxX) / 2,
    y: (bounds.minY + bounds.maxY) / 2,
    z: (bounds.minZ + bounds.maxZ) / 2,
  };
  const radius = points.reduce((maxRadius, point) => {
    const shell = point.shellRadiusM || 0;
    return Math.max(maxRadius, Math.hypot(point.x - center.x, point.y - center.y, point.z - center.z) + shell);
  }, 0.1);
  return { center, radius: Math.max(0.1, radius) };
}

function projectVehicleModel(model, width, height, view, frame = vehicleModelFrame(model)) {
  clampPreviewCamera(width, height);
  return projectVehicleModelInRect(model, { x: 0, y: 0, width, height }, view, frame);
}

function projectVehicleModelInRect(model, viewport, view, frame = vehicleModelFrame(model)) {
  const centerProjection = projectPoint(frame.center, view);
  const baseScale = Math.min(
    Math.max(40, viewport.width - 70) / (frame.radius * 2),
    Math.max(40, viewport.height - 70) / (frame.radius * 2),
  );
  const scale = baseScale * state.vehiclePreviewZoom;
  const map = new Map((model.points || []).map((point) => {
    const projected = projectPoint(point, view);
    return [
      point.id,
      {
        ...point,
        ...projected,
        x2: (projected.u - centerProjection.u) * scale + viewport.x + viewport.width / 2 + state.vehiclePreviewPanX,
        y2: viewport.y + viewport.height / 2 - (projected.v - centerProjection.v) * scale + state.vehiclePreviewPanY,
      },
    ];
  }));
  return { map, scale, frame };
}

function previewPanLimit(width, height) {
  return {
    x: Math.max(80, width * MAX_PREVIEW_PAN_FRACTION),
    y: Math.max(80, height * MAX_PREVIEW_PAN_FRACTION),
  };
}

function clampPreviewCamera(width = state.geometryScene?.width || 800, height = state.geometryScene?.height || 600) {
  state.vehiclePreviewZoom = clamp(Number(state.vehiclePreviewZoom) || 1, MIN_PREVIEW_ZOOM, MAX_PREVIEW_ZOOM);
  const limit = previewPanLimit(width, height);
  state.vehiclePreviewPanX = clamp(Number(state.vehiclePreviewPanX) || 0, -limit.x, limit.x);
  state.vehiclePreviewPanY = clamp(Number(state.vehiclePreviewPanY) || 0, -limit.y, limit.y);
}

function setPreviewPan(x, y, width = state.geometryScene?.width, height = state.geometryScene?.height) {
  const limit = previewPanLimit(width || 800, height || 600);
  state.vehiclePreviewPanX = clamp(Number(x) || 0, -limit.x, limit.x);
  state.vehiclePreviewPanY = clamp(Number(y) || 0, -limit.y, limit.y);
}

function setPreviewZoom(zoom, anchor = null) {
  const oldZoom = state.vehiclePreviewZoom;
  const nextZoom = clamp(Number(zoom) || 1, MIN_PREVIEW_ZOOM, MAX_PREVIEW_ZOOM);
  if (Math.abs(nextZoom - oldZoom) < 0.001) return;
  const width = state.geometryScene?.width || 800;
  const height = state.geometryScene?.height || 600;
  if (anchor) {
    const ratio = nextZoom / oldZoom;
    const anchorX = anchor.x - width / 2;
    const anchorY = anchor.y - height / 2;
    setPreviewPan(
      anchorX - (anchorX - state.vehiclePreviewPanX) * ratio,
      anchorY - (anchorY - state.vehiclePreviewPanY) * ratio,
      width,
      height,
    );
  }
  state.vehiclePreviewZoom = nextZoom;
  clampPreviewCamera(width, height);
}

function projectedViewFrame(model, view) {
  const projected = (model.points || []).map((point) => projectPoint(point, view));
  if (!projected.length) {
    return { centerU: 0, centerV: 0, spanU: 1, spanV: 1 };
  }
  const bounds = projected.reduce(
    (acc, point) => ({
      minU: Math.min(acc.minU, point.u),
      maxU: Math.max(acc.maxU, point.u),
      minV: Math.min(acc.minV, point.v),
      maxV: Math.max(acc.maxV, point.v),
    }),
    { minU: Infinity, maxU: -Infinity, minV: Infinity, maxV: -Infinity },
  );
  return {
    centerU: (bounds.minU + bounds.maxU) / 2,
    centerV: (bounds.minV + bounds.maxV) / 2,
    spanU: Math.max(0.35, bounds.maxU - bounds.minU),
    spanV: Math.max(0.35, bounds.maxV - bounds.minV),
  };
}

function projectVehicleModelToViewFrame(model, viewport, view, frame) {
  const scale = Math.min(
    Math.max(40, viewport.width - 34) / frame.spanU,
    Math.max(40, viewport.height - 34) / frame.spanV,
  );
  const map = new Map((model.points || []).map((point) => {
    const projected = projectPoint(point, view);
    return [
      point.id,
      {
        ...point,
        ...projected,
        x2: (projected.u - frame.centerU) * scale + viewport.x + viewport.width / 2,
        y2: viewport.y + viewport.height / 2 - (projected.v - frame.centerV) * scale,
      },
    ];
  }));
  return { map, scale, frame };
}

function drawMassPreview(ctx, width, height, data) {
  const fullModel = buildVehicleGeometry(data);
  const massModel = filterVehicleModel(fullModel, sectionFocus("mass"));
  if (!massModel.points.length) {
    state.massScene = null;
    syncMassPropertyEditor();
    drawPreviewGrid(ctx, width, height);
    drawCanvasText(ctx, "No mass properties are available.", width / 2, height / 2, {
      align: "center",
      color: canvasPalette().muted,
    });
    return;
  }
  const scenePoints = [];
  drawPreviewGrid(ctx, width, height);
  massViewPanels(width, height).forEach((panel) => {
    scenePoints.push(...drawMassViewPanel(ctx, panel, fullModel, massModel));
  });
  state.massScene = {
    points: scenePoints,
    uniquePoints: uniqueMassPoints(scenePoints),
  };
  syncMassPropertyEditor();
}

function massViewPanels(width, height) {
  const margin = 24;
  const gap = 16;
  const panelHeight = Math.max(130, (height - margin * 2 - gap) / 2);
  return [
    { label: "Top", axis: "X / Y", view: "top", x: margin, y: margin, width: width - margin * 2, height: panelHeight },
    { label: "Side", axis: "X / Z", view: "side", x: margin, y: margin + panelHeight + gap, width: width - margin * 2, height: panelHeight },
  ];
}

function drawMassViewPanel(ctx, panel, fullModel, massModel) {
  const palette = canvasPalette();
  drawPanel(ctx, panel.x, panel.y, panel.width, panel.height, colorWithAlpha(palette.surface, 0.72));
  drawCanvasText(ctx, panel.label, panel.x + 14, panel.y + 18, {
    size: 12,
    weight: 840,
    color: palette.ink,
  });
  drawCanvasText(ctx, panel.axis, panel.x + panel.width - 14, panel.y + 18, {
    align: "right",
    size: 10,
    weight: 760,
    color: palette.muted,
  });
  const viewport = {
    x: panel.x + 10,
    y: panel.y + 30,
    width: panel.width - 20,
    height: panel.height - 40,
  };
  const frame = massViewFrame(fullModel, massModel, panel.view);
  ctx.save();
  ctx.beginPath();
  ctx.rect(viewport.x, viewport.y, viewport.width, viewport.height);
  ctx.clip();
  drawMassContext(ctx, fullModel, viewport, panel.view, frame);
  const { map, scale } = projectVehicleModelToViewFrame(massModel, viewport, panel.view, frame);
  const massPoints = [...map.values()].map((point) => ({
    ...point,
    massView: panel.view,
    panelLabel: panel.label,
  }));
  [...map.values()]
    .filter((point) => point.shellRadiusM)
    .sort((a, b) => a.depth - b.depth)
    .forEach((point) => drawGyrationShell(ctx, point, scale, panel.view));
  massPoints
    .sort((a, b) => a.depth - b.depth)
    .forEach((point) => drawSphere(ctx, point));
  massPoints
    .sort((a, b) => a.depth - b.depth)
    .filter(shouldDrawMassLabel)
    .forEach((point) => drawMassLabel(ctx, point));
  ctx.restore();
  return massPoints;
}

function uniqueMassPoints(points) {
  const byId = new Map();
  points.forEach((point) => {
    if (!byId.has(point.id)) byId.set(point.id, point);
  });
  return [...byId.values()];
}

function shouldDrawMassLabel(point) {
  return point.id === state.massHoverPointId || point.id === state.massSelectedPointId;
}

function drawMassLabel(ctx, point) {
  const label = massDisplayName(point);
  const palette = canvasPalette();
  const x = point.x2 + (point.role === "effective-mass" ? 16 : 10);
  const y = point.y2 - (point.role === "effective-mass" ? 17 : 12);
  const paddingX = 7;
  ctx.save();
  ctx.font = "760 10px Inter, sans-serif";
  const width = Math.min(170, Math.ceil(ctx.measureText(label).width) + paddingX * 2);
  const height = 20;
  ctx.fillStyle = state.dark ? "rgba(32,40,49,0.88)" : "rgba(248,250,252,0.9)";
  ctx.strokeStyle = colorWithAlpha(point.color, point.id === state.massSelectedPointId ? 0.72 : 0.36);
  ctx.lineWidth = point.id === state.massSelectedPointId ? 1.5 : 1;
  ctx.beginPath();
  if (ctx.roundRect) ctx.roundRect(x, y - height / 2, width, height, 6);
  else ctx.rect(x, y - height / 2, width, height);
  ctx.fill();
  ctx.stroke();
  ctx.fillStyle = palette.ink;
  ctx.textAlign = "left";
  ctx.textBaseline = "middle";
  ctx.fillText(label, x + paddingX, y, width - paddingX * 2);
  ctx.restore();
}

function massViewFrame(fullModel, massModel, view) {
  const contextPoints = massContextPoints(fullModel);
  const massCenters = massModel.points.map((point) => ({ ...point, shellRadiusM: 0 }));
  return projectedViewFrame({ points: [...contextPoints, ...massCenters] }, view);
}

function drawMassContext(ctx, fullModel, viewport, view, frame) {
  const contextPoints = massContextPoints(fullModel);
  const pointIds = new Set(contextPoints.map((point) => point.id));
  const contextModel = {
    points: contextPoints,
    links: fullModel.links.filter((link) => pointIds.has(link.from) && pointIds.has(link.to)),
  };
  const { map } = projectVehicleModelToViewFrame(contextModel, viewport, view, frame);
  [...contextModel.links]
    .sort((a, b) => ((map.get(a.from)?.depth || 0) + (map.get(a.to)?.depth || 0))
      - ((map.get(b.from)?.depth || 0) + (map.get(b.to)?.depth || 0)))
    .forEach((link) => drawCylinder(ctx, map.get(link.from), map.get(link.to), {
      ...link,
      width: Math.max(1.5, Math.min(3, link.width * 0.48)),
      opacity: link.detail ? 0.12 : 0.18,
    }));
  [...map.values()]
    .filter((point) => !point.detail && ["upright", "hardpoint"].includes(point.role))
    .sort((a, b) => a.depth - b.depth)
    .forEach((point) => drawSphere(ctx, {
      ...point,
      radius: Math.max(2.5, Math.min(4, (point.radius || 5) * 0.48)),
      opacity: 0.2,
    }));
}

function massContextPoints(model) {
  return model.points.filter((point) => !["mass", "effective-mass", "wheel"].includes(point.role));
}

function sectionFocus(group) {
  const name = String(group || "").toLowerCase();
  const axle = name.includes("front") ? "front" : name.includes("rear") ? "rear" : null;
  let role = "overview";
  if (name === "hardpoints" || name === "geometry") role = "geometry";
  else if (name.includes("mass")) role = "mass";
  else if (name.includes("actuation") || name.includes("shock") || name.includes("bellcrank") || name.includes("stabar")) role = "actuation";
  else if (name.includes("hardpoint") || name.includes("suspension")) role = "hardpoints";
  else if (name.includes("wheel") || name.includes("tire")) role = "wheel";
  else if (name.includes("steering")) role = "steering";
  else if (name.includes("aero")) role = "aero";
  else if (axle) role = "axle";
  return { axle, role };
}

function filterVehicleModel(model, focus) {
  const points = model.points.filter((point) => pointVisibleForFocus(point, focus));
  const pointIds = new Set(points.map((point) => point.id));
  const links = model.links.filter((link) => (
    pointIds.has(link.from) && pointIds.has(link.to) && linkVisibleForFocus(link, focus)
  ));
  if (points.length >= 2) return { points, links };
  if (focus.role === "mass") {
    return {
      points: model.points.filter((point) => ["mass", "effective-mass"].includes(point.role)),
      links: [],
    };
  }
  return {
    points: model.points.filter((point) => (
      !point.detail
      && point.role !== "mass"
      && point.role !== "effective-mass"
    )),
    links: model.links.filter((link) => !link.detail),
  };
}

function pointVisibleForFocus(point, focus) {
  if (focus.role === "mass") return ["mass", "effective-mass"].includes(point.role);
  if (point.role === "mass" || point.role === "effective-mass") return false;
  if (focus.role === "geometry") return geometryPointRoles().includes(point.role);
  if (!focus.axle) return !point.detail;
  if (point.axle && point.axle !== focus.axle) return false;
  if (focus.role === "actuation") {
    return ["actuation", "bellcrank", "stabar", "upright", "wheel", "hardpoint"].includes(point.role);
  }
  if (focus.role === "hardpoints") {
    return ["hardpoint", "upright", "wheel", "steering"].includes(point.role);
  }
  if (focus.role === "wheel") {
    return ["wheel", "upright", "steering", "hardpoint"].includes(point.role);
  }
  if (focus.role === "steering") {
    return ["steering", "wheel", "upright", "hardpoint"].includes(point.role);
  }
  return !point.detail;
}

function linkVisibleForFocus(link, focus) {
  if (focus.role === "mass") return false;
  if (focus.role === "geometry") return geometryLinkRoles().includes(link.role);
  if (!focus.axle) return !link.detail;
  if (link.axle && link.axle !== focus.axle) return false;
  if (focus.role === "actuation") {
    return ["pushrod", "shock", "bellcrank", "stabar", "upright", "wheel"].includes(link.role);
  }
  if (focus.role === "hardpoints") {
    return ["lower", "upper", "upright", "steering", "wheel"].includes(link.role);
  }
  if (focus.role === "wheel") {
    return ["upright", "wheel", "steering", "lower", "upper"].includes(link.role);
  }
  if (focus.role === "steering") {
    return ["steering", "wheel", "upright"].includes(link.role);
  }
  return !link.detail;
}

function geometryPointRoles() {
  return ["hardpoint", "upright", "wheel", "steering", "actuation", "bellcrank", "stabar"];
}

function geometryLinkRoles() {
  return ["lower", "upper", "upright", "steering", "wheel", "pushrod", "shock", "bellcrank", "stabar"];
}

function drawMiniVehiclePreview(canvas, data, group) {
  const width = Math.max(48, Math.floor(canvas.clientWidth || 58));
  const height = Math.max(30, Math.floor(canvas.clientHeight || 36));
  const dpr = window.devicePixelRatio || 1;
  canvas.width = Math.floor(width * dpr);
  canvas.height = Math.floor(height * dpr);
  const ctx = canvas.getContext("2d");
  ctx.setTransform(dpr, 0, 0, dpr, 0, 0);
  ctx.clearRect(0, 0, width, height);
  const area = PARAMETER_AREAS.find((item) => item.id === group) || PARAMETER_AREAS[0];
  if (area.visual === "aero") {
    drawMiniHeatmap(ctx, width, height, data.aero?.downforce_table_n);
    return;
  }
  if (area.visual === "powertrain") {
    drawMiniPowertrain(ctx, width, height, data);
    return;
  }
  if (area.visual === "suspension") {
    drawMiniCurves(ctx, width, height);
    return;
  }
  if (area.visual === "tires") {
    drawMiniTires(ctx, width, height);
    return;
  }

  const model = filterVehicleModel(buildVehicleGeometry(data), sectionFocus(group));
  if (!model.points.length) return;
  const projected = model.points.map((point) => ({
    ...point,
    ...projectPointWithAngles(point, "iso", DEFAULT_VEHICLE_YAW, DEFAULT_VEHICLE_PITCH),
  }));
  const bounds = projected.reduce(
    (acc, point) => ({
      minX: Math.min(acc.minX, point.u),
      maxX: Math.max(acc.maxX, point.u),
      minY: Math.min(acc.minY, point.v),
      maxY: Math.max(acc.maxY, point.v),
    }),
    { minX: Infinity, maxX: -Infinity, minY: Infinity, maxY: -Infinity },
  );
  const spanX = Math.max(0.1, bounds.maxX - bounds.minX);
  const spanY = Math.max(0.1, bounds.maxY - bounds.minY);
  const scale = Math.min((width - 10) / spanX, (height - 8) / spanY);
  const map = new Map(projected.map((point) => [
    point.id,
    {
      ...point,
      x2: (point.u - (bounds.minX + bounds.maxX) / 2) * scale + width / 2,
      y2: height / 2 - (point.v - (bounds.minY + bounds.maxY) / 2) * scale,
    },
  ]));
  ctx.save();
  ctx.lineCap = "round";
  model.links.forEach((link) => {
    const from = map.get(link.from);
    const to = map.get(link.to);
    if (!from || !to) return;
    ctx.strokeStyle = link.color;
    ctx.lineWidth = 2;
    ctx.beginPath();
    ctx.moveTo(from.x2, from.y2);
    ctx.lineTo(to.x2, to.y2);
    ctx.stroke();
  });
  [...map.values()].sort((a, b) => a.depth - b.depth).forEach((point) => {
    const radius = ["mass", "effective-mass"].includes(point.role) ? 4 : 2.4;
    ctx.fillStyle = point.color;
    ctx.beginPath();
    ctx.arc(point.x2, point.y2, radius, 0, Math.PI * 2);
    ctx.fill();
  });
  ctx.restore();
}

function drawMiniHeatmap(ctx, width, height, table) {
  const rows = Array.isArray(table) && table.length ? table : [[0, 1], [1, 0]];
  const flat = rows.flat().map(Number).filter(Number.isFinite);
  const min = Math.min(...flat);
  const max = Math.max(...flat);
  const cellW = width / Math.max(1, rows[0].length);
  const cellH = height / Math.max(1, rows.length);
  rows.forEach((row, rowIndex) => {
    row.forEach((value, colIndex) => {
      const t = max === min ? 0.5 : (Number(value) - min) / (max - min);
      ctx.fillStyle = heatColor(t);
      ctx.fillRect(colIndex * cellW, rowIndex * cellH, Math.ceil(cellW), Math.ceil(cellH));
    });
  });
}

function drawMiniPowertrain(ctx, width, height, data) {
  const palette = canvasPalette();
  const nodes = powertrainTokens(data).length || 4;
  ctx.strokeStyle = palette.blue;
  ctx.lineWidth = 2;
  ctx.beginPath();
  ctx.moveTo(8, height / 2);
  ctx.lineTo(width - 8, height / 2);
  ctx.stroke();
  for (let index = 0; index < nodes; index += 1) {
    const x = 9 + index * ((width - 18) / Math.max(1, nodes - 1));
    ctx.fillStyle = palette.surface;
    ctx.strokeStyle = index === nodes - 1 ? palette.green : palette.blue;
    ctx.lineWidth = 2;
    ctx.beginPath();
    ctx.rect(x - 5, height / 2 - 7, 10, 14);
    ctx.fill();
    ctx.stroke();
  }
}

function drawMiniCurves(ctx, width, height) {
  const palette = canvasPalette();
  [[palette.blue, 0.3], [palette.green, 0.68]].forEach(([color, phase]) => {
    ctx.strokeStyle = color;
    ctx.lineWidth = 2;
    ctx.beginPath();
    for (let index = 0; index <= 28; index += 1) {
      const x = (index / 28) * width;
      const y = height * (0.52 - 0.32 * Math.sin(index / 4 + phase));
      if (index === 0) ctx.moveTo(x, y);
      else ctx.lineTo(x, y);
    }
    ctx.stroke();
  });
}

function drawMiniTires(ctx, width, height) {
  const palette = canvasPalette();
  [[0.3, 0.28], [0.7, 0.28], [0.3, 0.72], [0.7, 0.72]].forEach(([xFrac, yFrac], index) => {
    ctx.fillStyle = state.dark ? "#0f151b" : "#edf1f4";
    ctx.strokeStyle = index < 2 ? palette.blue : palette.green;
    ctx.lineWidth = 2;
    ctx.beginPath();
    ctx.ellipse(width * xFrac, height * yFrac, 5, 9, 0.2, 0, Math.PI * 2);
    ctx.fill();
    ctx.stroke();
  });
}

function drawPreviewGrid(ctx, width, height) {
  ctx.save();
  ctx.strokeStyle = state.dark ? "rgba(74, 88, 102, 0.46)" : "rgba(196, 210, 222, 0.62)";
  ctx.lineWidth = 1;
  for (let x = 36; x < width; x += 72) {
    ctx.beginPath();
    ctx.moveTo(x, 0);
    ctx.lineTo(x, height);
    ctx.stroke();
  }
  for (let y = 36; y < height; y += 72) {
    ctx.beginPath();
    ctx.moveTo(0, y);
    ctx.lineTo(width, y);
    ctx.stroke();
  }
  ctx.restore();
}

function drawGyrationShell(ctx, point, scale, view = "iso") {
  const radius = Math.max(14, Math.min(190, point.shellRadiusM * scale));
  ctx.save();
  ctx.fillStyle = state.dark ? "rgba(194, 70, 111, 0.12)" : "rgba(194, 70, 111, 0.1)";
  ctx.strokeStyle = state.dark ? "rgba(255, 157, 190, 0.42)" : "rgba(194, 70, 111, 0.36)";
  ctx.lineWidth = 2;
  ctx.beginPath();
  ctx.arc(point.x2, point.y2, radius, 0, Math.PI * 2);
  ctx.fill();
  ctx.stroke();
  if (view === "side") {
    ctx.beginPath();
    ctx.moveTo(point.x2 - radius * 0.78, point.y2);
    ctx.lineTo(point.x2 + radius * 0.78, point.y2);
    ctx.stroke();
  } else if (view !== "top") {
    ctx.beginPath();
    ctx.ellipse(point.x2, point.y2, radius, radius * 0.34, 0, 0, Math.PI * 2);
    ctx.stroke();
  }
  ctx.restore();
}

function drawCylinder(ctx, from, to, link) {
  if (!from || !to) return;
  const width = link.width || 5;
  const opacity = Number.isFinite(link.opacity) ? clamp(link.opacity, 0.08, 1) : 1;
  const shadowOpacity = (state.dark ? 0.45 : 0.2) * opacity;
  const highlightOpacity = 0.45 * opacity;
  ctx.save();
  ctx.lineCap = "round";
  ctx.strokeStyle = state.dark
    ? `rgba(0,0,0,${shadowOpacity})`
    : `rgba(16,25,34,${shadowOpacity})`;
  ctx.lineWidth = width + 3;
  ctx.beginPath();
  ctx.moveTo(from.x2, from.y2 + 1.5);
  ctx.lineTo(to.x2, to.y2 + 1.5);
  ctx.stroke();
  ctx.strokeStyle = opacity < 1 ? colorWithAlpha(link.color, opacity) : link.color;
  ctx.lineWidth = width;
  ctx.beginPath();
  ctx.moveTo(from.x2, from.y2);
  ctx.lineTo(to.x2, to.y2);
  ctx.stroke();
  ctx.strokeStyle = `rgba(255,255,255,${highlightOpacity})`;
  ctx.lineWidth = Math.max(1, width * 0.28);
  ctx.beginPath();
  ctx.moveTo(from.x2, from.y2 - width * 0.22);
  ctx.lineTo(to.x2, to.y2 - width * 0.22);
  ctx.stroke();
  ctx.restore();
}

function drawSphere(ctx, point) {
  const radius = point.radius || 5;
  if (radius <= 0) return;
  const selected = point.id === state.geometrySelectedPointId || point.id === state.massSelectedPointId;
  const hovered = point.id === state.geometryHoverPointId || point.id === state.massHoverPointId;
  const opacity = Number.isFinite(point.opacity) ? clamp(point.opacity, 0.12, 1) : 1;
  const gradient = ctx.createRadialGradient(point.x2 - radius * 0.35, point.y2 - radius * 0.45, 1, point.x2, point.y2, radius);
  gradient.addColorStop(0, "#ffffff");
  gradient.addColorStop(0.28, point.color);
  gradient.addColorStop(1, state.dark ? "#0b1117" : "#24313f");
  ctx.save();
  if (hovered || selected) {
    ctx.strokeStyle = selected ? canvasPalette().amber : canvasPalette().blue;
    ctx.lineWidth = selected ? 3 : 2;
    ctx.beginPath();
    ctx.arc(point.x2, point.y2, radius + (selected ? 8 : 5), 0, Math.PI * 2);
    ctx.stroke();
  }
  ctx.globalAlpha = opacity;
  ctx.fillStyle = state.dark ? "rgba(0,0,0,0.36)" : "rgba(16,25,34,0.18)";
  ctx.beginPath();
  ctx.ellipse(point.x2 + 1.5, point.y2 + 2.5, radius * 1.05, radius * 0.75, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.fillStyle = gradient;
  ctx.beginPath();
  ctx.arc(point.x2, point.y2, radius, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();
}

function buildVehicleGeometry(data) {
  const points = [];
  const links = [];
  const pointById = new Set();
  const massProperties = [];
  const addPoint = (id, raw, group, radius = 5, meta = {}) => {
    const point = toPoint(raw);
    if (!point) return null;
    const mapped = {
      id,
      x: point[0],
      y: point[1],
      z: point[2],
      group,
      radius,
      color: pointColor(group),
      role: meta.role || group,
      axle: meta.axle || null,
      side: meta.side || null,
      detail: Boolean(meta.detail),
      shellRadiusM: meta.shellRadiusM || 0,
      sourcePath: meta.sourcePath || null,
      sourceSign: meta.sourceSign || [1, 1, 1],
      sourceLabel: meta.sourceLabel || "",
      massKg: Number.isFinite(meta.massKg) ? meta.massKg : null,
      inertiaKgM2: meta.inertiaKgM2 || null,
      aggregate: Boolean(meta.aggregate),
      sourceCount: Number.isFinite(meta.sourceCount) ? meta.sourceCount : null,
      opacity: Number.isFinite(meta.opacity) ? meta.opacity : 1,
    };
    points.push(mapped);
    pointById.add(id);
    return mapped;
  };
  const addLink = (from, to, group, width = 5, meta = {}) => {
    if (pointById.has(from) && pointById.has(to)) {
      links.push({
        from,
        to,
        group,
        width,
        color: linkColor(group),
        role: meta.role || group,
        axle: meta.axle || null,
        detail: Boolean(meta.detail),
        opacity: Number.isFinite(meta.opacity) ? meta.opacity : 1,
      });
    }
  };
  const addMassProperty = (rawCg, mass, inertia, meta = {}) => {
    const cg = toPoint(rawCg);
    const massValue = Number(mass);
    if (!cg || !Number.isFinite(massValue) || massValue <= 0) return;
    massProperties.push({ cg, mass: massValue, inertia });
    if (meta.id) {
      addPoint(meta.id, cg, "mass", massRadius(massValue), {
        role: "mass",
        axle: meta.axle || null,
        side: meta.side || null,
        sourceLabel: meta.label || "",
        massKg: massValue,
        inertiaKgM2: inertia,
        sourcePath: meta.sourcePath || null,
      });
    }
  };

  addMassProperty(data.sprung_mass?.cg_m, data.sprung_mass?.mass_kg, data.sprung_mass?.inertia_kg_m2, {
    id: "sprung-mass",
    label: "Sprung mass",
    sourcePath: ["sprung_mass"],
  });
  addMassProperty(data.driver_mass?.cg_m, data.driver_mass?.mass_kg, data.driver_mass?.inertia_kg_m2, {
    id: "driver-mass",
    label: "Driver mass",
    sourcePath: ["driver_mass"],
  });
  ["front", "rear"].forEach((axleName) => {
    const axle = data[axleName];
    if (!axle) return;
    const architecture = String(data.architecture?.[axleName] || "");
    ["left", "right"].forEach((sideName) => {
      addAxleSide(axleName, sideName, axle, architecture, addPoint, addLink);
      collectAxleMasses(axleName, sideName, axle, addMassProperty);
    });
    if (architecture.includes("stabar")) {
      addLink(`${axleName}-left-stabar-bar`, `${axleName}-right-stabar-bar`, "stabar", 4, {
        axle: axleName,
        role: "stabar",
        detail: true,
      });
    }
  });
  const aggregate = aggregateMassProperties(massProperties);
  if (aggregate) {
    addPoint("vehicle-mass", aggregate.cg, "mass", massRadius(aggregate.mass), {
      role: "effective-mass",
      shellRadiusM: aggregate.gyrationRadius,
      opacity: 0.3,
      sourceLabel: "Effective mass",
      massKg: aggregate.mass,
      inertiaKgM2: aggregate.inertia,
      aggregate: true,
      sourceCount: aggregate.count,
    });
  }
  return { points, links };
}

function collectAxleMasses(axleName, sideName, axle, addMassProperty) {
  const side = sideName === "right" ? -1 : 1;
  const mirror = (raw) => {
    const point = toPoint(raw);
    if (!point) return null;
    return [point[0], point[1] * side, point[2]];
  };
  Object.entries(axle.masses || {}).forEach(([name, mass]) => {
    addMassProperty(mirror(mass.cg_m), mass.mass_kg, mass.inertia_kg_m2, {
      id: `${axleName}-${sideName}-${name}-mass`,
      axle: axleName,
      side: sideName,
      label: `${humanizeToken(axleName)} ${humanizeToken(sideName)} ${humanizeToken(name)} mass`,
      sourcePath: [axleName, "masses", name],
    });
  });
}

function aggregateMassProperties(masses) {
  const validMasses = masses.filter((item) => Number.isFinite(item.mass) && item.mass > 0 && toPoint(item.cg));
  const totalMass = validMasses.reduce((sum, item) => sum + item.mass, 0);
  if (!totalMass) return null;
  const cg = [0, 1, 2].map((idx) => (
    validMasses.reduce((sum, item) => sum + item.cg[idx] * item.mass, 0) / totalMass
  ));
  const inertia = [0, 0, 0];
  validMasses.forEach((item) => {
    const diag = inertiaDiagonal(item.inertia);
    const dx = item.cg[0] - cg[0];
    const dy = item.cg[1] - cg[1];
    const dz = item.cg[2] - cg[2];
    inertia[0] += diag[0] + item.mass * (dy * dy + dz * dz);
    inertia[1] += diag[1] + item.mass * (dx * dx + dz * dz);
    inertia[2] += diag[2] + item.mass * (dx * dx + dy * dy);
  });
  const meanInertia = (inertia[0] + inertia[1] + inertia[2]) / 3;
  return {
    mass: totalMass,
    cg,
    inertia,
    gyrationRadius: Math.max(0.08, Math.min(0.95, Math.sqrt(meanInertia / totalMass))),
    count: validMasses.length,
  };
}

function inertiaDiagonal(inertia) {
  if (!Array.isArray(inertia)) return [0, 0, 0];
  if (inertia.every((value) => Number.isFinite(Number(value)))) {
    return inertia.slice(0, 3).map((value) => Math.max(0, Number(value)));
  }
  return [0, 1, 2].map((idx) => {
    const value = Number(inertia[idx]?.[idx]);
    return Number.isFinite(value) && value > 0 ? value : 0;
  });
}

function addAxleSide(axleName, sideName, axle, architecture, addPoint, addLink) {
  const side = sideName === "right" ? -1 : 1;
  const prefix = `${axleName}-${sideName}`;
  const hasBellcrank = architecture.includes("bellcrank");
  const hasStabar = architecture.includes("stabar");
  const suspension = axle.suspension || {};
  const steering = axle.steering || {};
  const actuation = axle.actuation || {};
  const shock = actuation.shock || {};
  const bellcrank = actuation.bellcrank || {};
  const pickups = bellcrank.pickups_m || {};
  const stabar = actuation.stabar || {};
  const mirror = (raw) => {
    const point = toPoint(raw);
    if (!point) return null;
    return [point[0], point[1] * side, point[2]];
  };
  const source = (...parts) => [axleName, ...parts];
  const pointMeta = (role, detail = false, sourcePath = null, label = "") => ({
    axle: axleName,
    side: sideName,
    role,
    detail,
    sourcePath,
    sourceSign: [1, side, 1],
    sourceLabel: label
      ? `${humanizeToken(axleName)} ${humanizeToken(sideName)} ${label}`
      : "",
  });
  const linkMeta = (role, detail = false, extra = {}) => ({ axle: axleName, role, detail, ...extra });
  const referenceLink = { opacity: 0.32 };

  addPoint(`${prefix}-lower-fore-i`, mirror(suspension.lower_fore_i_m), "hardpoint", 5, pointMeta("hardpoint", false, source("suspension", "lower_fore_i_m"), "lower fore inner"));
  addPoint(`${prefix}-lower-aft-i`, mirror(suspension.lower_aft_i_m), "hardpoint", 5, pointMeta("hardpoint", false, source("suspension", "lower_aft_i_m"), "lower aft inner"));
  addPoint(`${prefix}-lower-o`, mirror(suspension.lower_o_m), "upright", 6, pointMeta("upright", false, source("suspension", "lower_o_m"), "lower outer"));
  addPoint(`${prefix}-upper-fore-i`, mirror(suspension.upper_fore_i_m), "hardpoint", 5, pointMeta("hardpoint", false, source("suspension", "upper_fore_i_m"), "upper fore inner"));
  addPoint(`${prefix}-upper-aft-i`, mirror(suspension.upper_aft_i_m), "hardpoint", 5, pointMeta("hardpoint", false, source("suspension", "upper_aft_i_m"), "upper aft inner"));
  addPoint(`${prefix}-upper-o`, mirror(suspension.upper_o_m), "upright", 6, pointMeta("upright", false, source("suspension", "upper_o_m"), "upper outer"));
  addPoint(`${prefix}-tie-o`, mirror(suspension.tie_o_m), "steering", 5, pointMeta("steering", false, source("suspension", "tie_o_m"), "tie rod outer"));
  addPoint(`${prefix}-wheel-center`, mirror(suspension.wheel_center_m), "wheel", 7, pointMeta("wheel", false, source("suspension", "wheel_center_m"), "wheel center"));
  addPoint(`${prefix}-rack`, mirror(steering.rack_pickup_m), "steering", 5, pointMeta("steering", false, source("steering", "rack_pickup_m"), "rack pickup"));
  addPoint(`${prefix}-rod`, mirror(actuation.rod_mount_m), "actuation", 5, pointMeta("actuation", true, source("actuation", "rod_mount_m"), "rod mount"));
  addPoint(`${prefix}-shock-mount`, mirror(shock.mount_m), "actuation", 5, pointMeta("actuation", true, source("actuation", "shock", "mount_m"), "shock mount"));
  if (hasBellcrank) {
    addPoint(`${prefix}-bellcrank-pivot`, mirror(bellcrank.pivot_m), "bellcrank", 6, pointMeta("bellcrank", true, source("actuation", "bellcrank", "pivot_m"), "bellcrank pivot"));
    addPoint(`${prefix}-bellcrank-rod`, mirror(pickups.rod), "bellcrank", 5, pointMeta("bellcrank", true, source("actuation", "bellcrank", "pickups_m", "rod"), "bellcrank rod pickup"));
    addPoint(`${prefix}-bellcrank-shock`, mirror(pickups.shock), "bellcrank", 5, pointMeta("bellcrank", true, source("actuation", "bellcrank", "pickups_m", "shock"), "bellcrank shock pickup"));
    if (hasStabar) {
      addPoint(`${prefix}-bellcrank-stabar`, mirror(pickups.stabar), "bellcrank", 5, pointMeta("bellcrank", true, source("actuation", "bellcrank", "pickups_m", "stabar"), "bellcrank stabar pickup"));
    }
  }
  if (hasStabar) {
    addPoint(`${prefix}-stabar-arm`, mirror(stabar.arm_end_m), "stabar", 5, pointMeta("stabar", true, source("actuation", "stabar", "arm_end_m"), "stabar arm end"));
    addPoint(`${prefix}-stabar-bar`, mirror(stabar.bar_end_m), "stabar", 5, pointMeta("stabar", true, source("actuation", "stabar", "bar_end_m"), "stabar bar end"));
  }

  addLink(`${prefix}-lower-fore-i`, `${prefix}-lower-o`, "lower", 6, linkMeta("lower"));
  addLink(`${prefix}-lower-aft-i`, `${prefix}-lower-o`, "lower", 6, linkMeta("lower"));
  addLink(`${prefix}-upper-fore-i`, `${prefix}-upper-o`, "upper", 5, linkMeta("upper"));
  addLink(`${prefix}-upper-aft-i`, `${prefix}-upper-o`, "upper", 5, linkMeta("upper"));
  addLink(`${prefix}-upper-o`, `${prefix}-lower-o`, "upright", 7, linkMeta("upright"));
  addLink(`${prefix}-rack`, `${prefix}-tie-o`, "steering", 4, linkMeta("steering"));
  addLink(`${prefix}-tie-o`, `${prefix}-wheel-center`, "steering", 4, linkMeta("steering", false, referenceLink));
  addLink(`${prefix}-upper-o`, `${prefix}-wheel-center`, "wheel", 3, linkMeta("wheel", false, referenceLink));
  addLink(`${prefix}-lower-o`, `${prefix}-wheel-center`, "wheel", 3, linkMeta("wheel", false, referenceLink));
  const rodTarget = String(actuation.rod_to || "lower").includes("upper") ? "upper-o" : "lower-o";
  addLink(`${prefix}-rod`, `${prefix}-${rodTarget}`, "pushrod", 4, linkMeta("pushrod", true, referenceLink));
  if (hasBellcrank) {
    addLink(`${prefix}-rod`, `${prefix}-bellcrank-rod`, "pushrod", 5, linkMeta("pushrod", true));
    addLink(`${prefix}-shock-mount`, `${prefix}-bellcrank-shock`, "shock", 6, linkMeta("shock", true));
  } else {
    addLink(`${prefix}-shock-mount`, `${prefix}-rod`, "shock", 6, linkMeta("shock", true));
  }
  if (hasStabar) {
    addLink(`${prefix}-stabar-arm`, `${prefix}-stabar-bar`, "stabar", 4, linkMeta("stabar", true));
    addLink(`${prefix}-stabar-arm`, `${prefix}-bellcrank-stabar`, "stabar", 4, linkMeta("stabar", true));
  }
  if (hasBellcrank) {
    addLink(`${prefix}-bellcrank-pivot`, `${prefix}-bellcrank-rod`, "bellcrank", 5, linkMeta("bellcrank", true));
    addLink(`${prefix}-bellcrank-rod`, `${prefix}-bellcrank-shock`, "bellcrank", 5, linkMeta("bellcrank", true));
    addLink(`${prefix}-bellcrank-shock`, `${prefix}-bellcrank-stabar`, "bellcrank", 5, linkMeta("bellcrank", true));
    addLink(`${prefix}-bellcrank-stabar`, `${prefix}-bellcrank-pivot`, "bellcrank", 5, linkMeta("bellcrank", true));
  }
}

function toPoint(raw) {
  if (!Array.isArray(raw) || raw.length < 3) return null;
  const point = raw.slice(0, 3).map(Number);
  return point.every(Number.isFinite) ? point : null;
}

function pointColor(group) {
  const palette = canvasPalette();
  return {
    hardpoint: palette.blue,
    upright: state.dark ? "#8794a1" : "#687683",
    steering: palette.green,
    wheel: state.dark ? "#8b96a2" : "#7e8994",
    actuation: palette.red,
    bellcrank: palette.amber,
    stabar: state.dark ? "#b3a6d8" : "#8b7ab8",
    mass: palette.magenta,
    inertia: state.dark ? "#94bdc8" : "#5c95a5",
  }[group] || palette.blue;
}

function linkColor(group) {
  const palette = canvasPalette();
  return {
    lower: state.dark ? "#7fa8c8" : "#4f7fa8",
    upper: palette.green,
    upright: state.dark ? "#8794a1" : "#687683",
    steering: palette.green,
    wheel: state.dark ? "#8995a1" : "#84909a",
    pushrod: state.dark ? "#92bea6" : "#5e987c",
    shock: palette.red,
    bellcrank: palette.amber,
    stabar: state.dark ? "#b3a6d8" : "#8b7ab8",
    inertia: state.dark ? "#94bdc8" : "#5c95a5",
  }[group] || palette.muted;
}

function massRadius(mass) {
  return Math.max(6, Math.min(30, 4 + Math.cbrt(mass) * 3.2));
}

function inertiaRodLengths(inertia, mass) {
  if (!Array.isArray(inertia) || inertia.length < 3) return [0.12, 0.12, 0.12];
  return [0, 1, 2].map((idx) => {
    const value = Number(inertia[idx]?.[idx]);
    if (!Number.isFinite(value) || value <= 0) return 0.12;
    return Math.max(0.06, Math.min(0.55, Math.sqrt(value / Math.max(1, mass)) * 0.8));
  });
}

function wireVehicleCanvas() {
  const canvas = document.getElementById("vehicle-canvas");
  canvas.addEventListener("contextmenu", (event) => event.preventDefault());
  canvas.addEventListener("pointerdown", (event) => {
    if (isArchitecturePreviewArea()) {
      const hotspot = hitTestArchitectureHotspot(event);
      if (hotspot) {
        selectArchitectureHotspot(hotspot);
        event.preventDefault();
      }
      return;
    }
    if (isMassPreviewArea()) {
      const hit = hitTestMassPoint(event);
      if (hit) {
        selectMassPoint(hit);
        event.preventDefault();
      } else {
        selectMassPoint(null);
      }
      return;
    }
    if (!isSpatialPreviewArea()) return;
    if (event.ctrlKey) {
      startPreviewDrag(event, "pan");
      return;
    }
    const hit = hitTestGeometryPoint(event);
    if (hit) {
      selectGeometryPoint(hit, { scroll: true });
      startGeometryDrag(event, hit);
      event.preventDefault();
      return;
    }
    startPreviewDrag(event, "rotate");
  });
  canvas.addEventListener("pointermove", (event) => {
    if (isArchitecturePreviewArea()) {
      updateArchitectureHover(event);
      return;
    }
    if (isMassPreviewArea()) {
      updateMassHover(event);
      return;
    }
    if (state.geometryDrag) {
      updateGeometryDrag(event);
      return;
    }
    if (updatePreviewDrag(event)) return;
  });
  canvas.addEventListener("pointerup", (event) => {
    if (finishGeometryDrag(event.pointerId)) return;
    if (finishPreviewDrag(event.pointerId)) return;
  });
  canvas.addEventListener("pointercancel", (event) => {
    if (finishGeometryDrag(event.pointerId)) return;
    if (finishPreviewDrag(event.pointerId)) return;
  });
  canvas.addEventListener("wheel", handlePreviewWheel, { passive: false });
  canvas.addEventListener("pointermove", updateGeometryHover);
  canvas.addEventListener("pointerleave", () => {
    state.geometryHoverPointId = null;
    state.architectureHoverId = null;
    state.massHoverPointId = null;
    canvas.classList.remove("geometry-hot");
    canvas.classList.remove("architecture-hot");
    canvas.classList.remove("mass-hot");
    canvas.classList.remove("preview-panning");
    drawVehicleFromForm();
  });
  canvas.addEventListener("dblclick", () => {
    if (isSpatialPreviewArea()) resetVehicleView();
  });
}

function wireGeometryEditor() {
  document.querySelectorAll("[data-geometry-axis]").forEach((button) => {
    button.addEventListener("click", () => setGeometryAxis(button.dataset.geometryAxis));
  });
  document.querySelectorAll("[data-geometry-coordinate]").forEach((input) => {
    input.addEventListener("input", () => {
      const point = selectedGeometryPoint();
      if (!point) return;
      const values = ["x", "y", "z"].map((axis) => Number(document.querySelector(`[data-geometry-coordinate="${axis}"]`)?.value));
      if (!values.every(Number.isFinite)) return;
      setGeometrySourceValues(point, values, { syncEditor: false });
    });
  });
  window.addEventListener("keydown", (event) => {
    if (event.key === "Escape" && isSpatialPreviewArea() && clearGeometrySelection()) {
      event.preventDefault();
      return;
    }
    if (event.key === "Shift" && !event.repeat && isSpatialPreviewArea() && !isTextEntryTarget(event.target)) {
      event.preventDefault();
      cycleGeometryAxis();
    }
  });
}

function isTextEntryTarget(target) {
  return Boolean(target?.closest?.("input, textarea, select, [contenteditable='true']"));
}

function wireSetupSplitter() {
  const splitter = document.getElementById("setup-splitter");
  const workspace = document.querySelector(".setup-workspace");
  if (!splitter || !workspace) return;
  applySetupPaneWidth();
  splitter.addEventListener("pointerdown", (event) => {
    const rect = workspace.getBoundingClientRect();
    state.setupResize = {
      pointerId: event.pointerId,
      left: rect.left,
    };
    splitter.classList.add("active");
    document.body.classList.add("resizing-panes");
    splitter.setPointerCapture(event.pointerId);
    event.preventDefault();
  });
  splitter.addEventListener("pointermove", (event) => {
    if (!state.setupResize || state.setupResize.pointerId !== event.pointerId) return;
    setSetupPaneWidth(event.clientX - state.setupResize.left, { redraw: false });
    drawVehicleFromForm();
  });
  splitter.addEventListener("pointerup", (event) => finishSetupResize(event.pointerId));
  splitter.addEventListener("pointercancel", (event) => finishSetupResize(event.pointerId));
  splitter.addEventListener("keydown", (event) => {
    const step = event.shiftKey ? 48 : 16;
    if (event.key === "ArrowLeft") {
      event.preventDefault();
      setSetupPaneWidth(state.setupPaneWidth - step, { persist: true });
    }
    if (event.key === "ArrowRight") {
      event.preventDefault();
      setSetupPaneWidth(state.setupPaneWidth + step, { persist: true });
    }
    if (event.key === "Home") {
      event.preventDefault();
      setSetupPaneWidth(MIN_SETUP_PANE_WIDTH, { persist: true });
    }
    if (event.key === "End") {
      event.preventDefault();
      setSetupPaneWidth(setupPaneBounds().max, { persist: true });
    }
  });
}

function finishSetupResize(pointerId) {
  const resize = state.setupResize;
  if (!resize || resize.pointerId !== pointerId) return;
  state.setupResize = null;
  document.getElementById("setup-splitter")?.classList.remove("active");
  document.body.classList.remove("resizing-panes");
  localStorage.setItem("bobsim-setup-pane-width", String(Math.round(state.setupPaneWidth)));
  drawVehicleFromForm();
}

function resetVehicleView() {
  state.vehiclePreviewView = "iso";
  state.vehiclePreviewYaw = DEFAULT_VEHICLE_YAW;
  state.vehiclePreviewPitch = DEFAULT_VEHICLE_PITCH;
  state.vehiclePreviewZoom = 1;
  state.vehiclePreviewPanX = 0;
  state.vehiclePreviewPanY = 0;
  syncViewButtons();
  drawVehicleFromForm();
}

function syncViewButtons() {
  document.querySelectorAll(".view-button[data-view]").forEach((item) => {
    item.classList.toggle("active", item.dataset.view === state.vehiclePreviewView);
  });
}

function wireEvents() {
  document.getElementById("refresh-btn").addEventListener("click", refresh);
  document.getElementById("theme-toggle-btn").addEventListener("click", toggleTheme);
  document.getElementById("reference-toggle-btn").addEventListener("click", toggleReferencePanel);
  document.getElementById("open-vehicle-start-btn").addEventListener("click", openVehicleStartModal);
  document.getElementById("start-load-btn").addEventListener("click", loadVehicleFromStart);
  document.getElementById("start-create-btn").addEventListener("click", createVehicleFromStart);
  document.getElementById("start-active-btn").addEventListener("click", () => {
    state.vehicleStartOpen = false;
    renderVehicleStartModal();
  });
  document.getElementById("start-import-btn").addEventListener("click", () => {
    document.getElementById("start-import-input").click();
  });
  document.getElementById("start-import-input").addEventListener("change", (event) => {
    importVehicleFile(event.target.files?.[0]);
    event.target.value = "";
  });
  document.getElementById("architecture-connection-close").addEventListener("click", closeArchitectureConnectionModal);
  document.getElementById("architecture-connection-modal").addEventListener("pointerdown", (event) => {
    if (event.target.id === "architecture-connection-modal") closeArchitectureConnectionModal();
  });
  document.getElementById("architecture-modal-select").addEventListener("change", (event) => {
    updateArchitectureModalArchitecture(event.target.value);
  });
  document.getElementById("architecture-connection-body").addEventListener("click", (event) => {
    const pickup = event.target.closest("[data-architecture-pickup]");
    if (pickup) {
      selectArchitectureOrderPickup(pickup.dataset.architecturePickup, pickup.dataset.orderIndex);
      return;
    }
    const role = event.target.closest("[data-architecture-role]");
    if (role) {
      updateArchitectureOrderRole(role.dataset.architectureRole, role.dataset.orderIndex, role.dataset.role);
    }
  });
  window.addEventListener("keydown", (event) => {
    if (event.key === "Escape" && state.architectureModalOpen) closeArchitectureConnectionModal();
  });
  window.addEventListener("keydown", handleUndoShortcut);
  window.addEventListener("keydown", handleSetupStageKeys);
  document.getElementById("vehicle-library-picker").addEventListener("change", syncVehicleLibraryActions);
  document.getElementById("load-vehicle-btn").addEventListener("click", loadVehicleSource);
  document.getElementById("delete-vehicle-btn").addEventListener("click", deleteSelectedVehicleConfig);
  document.getElementById("vehicle-import-input").addEventListener("change", (event) => {
    importVehicleFile(event.target.files?.[0]);
    event.target.value = "";
  });
  document.getElementById("save-vehicle-btn").addEventListener("click", saveVehicleAs);
  document.getElementById("save-raw-btn").addEventListener("click", saveRawVehicle);
  document.getElementById("run-workflow-btn").addEventListener("click", startSelectedWorkflow);
  document.getElementById("apply-sim-config-btn").addEventListener("click", applySimConfigEdits);
  document.getElementById("save-sim-config-btn").addEventListener("click", saveSimConfigAs);
  document.getElementById("load-sim-config-btn").addEventListener("click", loadSelectedSimConfig);
  document.getElementById("delete-sim-config-btn").addEventListener("click", deleteSelectedSimConfig);
  document.getElementById("sim-config-picker").addEventListener("change", (event) => {
    state.selectedSimConfigSource = event.target.value;
    renderSimConfigLibrary();
  });
  document.getElementById("clear-log-btn").addEventListener("click", () => {
    document.getElementById("job-log").textContent = "";
  });
  document.getElementById("rotation-sensitivity").addEventListener("input", (event) => {
    state.rotationSensitivity = Number(event.target.value);
    localStorage.setItem("bobsim-rotation-sensitivity", String(state.rotationSensitivity));
    renderVehicleControls();
  });
  document.getElementById("geometry-show-front").addEventListener("change", (event) => {
    updateGeometryAxleVisibility("front", event.target.checked);
  });
  document.getElementById("geometry-show-rear").addEventListener("change", (event) => {
    updateGeometryAxleVisibility("rear", event.target.checked);
  });
  document.getElementById("reset-view-btn").addEventListener("click", resetVehicleView);
  document.getElementById("setup-prev-btn")?.addEventListener("click", () => navigateParameterStep(-1));
  document.getElementById("setup-next-btn")?.addEventListener("click", () => navigateParameterStep(1));
  document.getElementById("rail-primary-btn").addEventListener("click", async () => {
    if (state.view === "setup") await saveVehicleAs();
    else await startSelectedWorkflow();
  });
  document.getElementById("rail-secondary-btn").addEventListener("click", () => {
    setView(state.view === "setup" ? "standard" : "setup");
  });
  document.querySelectorAll(".rail-item").forEach((button) => {
    button.addEventListener("click", () => setView(button.dataset.view));
  });
  document.querySelectorAll(".tab").forEach((button) => {
    button.addEventListener("click", () => {
      state.activeSimTab = button.dataset.tab;
      syncSimTabs();
    });
  });
  document.querySelectorAll(".view-button[data-view]").forEach((button) => {
    button.addEventListener("click", () => {
      state.vehiclePreviewView = button.dataset.view;
      if (state.vehiclePreviewView === "iso") {
        state.vehiclePreviewYaw = DEFAULT_VEHICLE_YAW;
        state.vehiclePreviewPitch = DEFAULT_VEHICLE_PITCH;
      }
      syncViewButtons();
      drawVehicleFromForm();
    });
  });
  document.querySelector(".visual-stage")?.addEventListener("scroll", () => {
    if (state.massSelectedPointId) queueMassPropertyEditorPosition();
  });
  wireSetupSplitter();
  wireGeometryEditor();
  wireVehicleCanvas();
  window.addEventListener("resize", () => {
    applySetupPaneWidth();
    drawVehicleFromForm();
  });
}

wireEvents();
refresh();
setInterval(async () => {
  if ((state.status?.jobs || []).some((job) => job.status === "running" || job.status === "queued")) {
    state.status = await api("/api/status");
    renderStandard();
  }
}, 2000);
