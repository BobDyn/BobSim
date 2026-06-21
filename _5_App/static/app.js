const savedRotationSensitivity = Number(localStorage.getItem("bobsim-rotation-sensitivity"));
const DEFAULT_VEHICLE_YAW = Math.PI - 0.72;
const DEFAULT_VEHICLE_PITCH = 0.46;

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
  activeSimTab: "outputs",
  activeParamGroup: null,
  dirtyVehicle: false,
  vehiclePreviewView: "iso",
  vehiclePreviewYaw: DEFAULT_VEHICLE_YAW,
  vehiclePreviewPitch: DEFAULT_VEHICLE_PITCH,
  rotationSensitivity: Number.isFinite(savedRotationSensitivity) && savedRotationSensitivity > 0
    ? savedRotationSensitivity
    : 1,
  vehicleDrag: null,
  referenceOpen: false,
  dark: localStorage.getItem("bobsim-theme") === "dark",
};

document.body.classList.toggle("dark", state.dark);

const PARAMETER_AREAS = [
  { id: "vehicle", label: "Architecture", visual: "overview", always: true },
  { id: "hardpoints", label: "Geometry", visual: "hardpoints", always: true },
  { id: "mass", label: "Mass", visual: "mass", always: true },
  { id: "suspension", label: "Suspension", visual: "suspension", always: true },
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
  await refreshTirePayload();
  await refreshTireTemplates();
  if (!state.activeTir && state.tireTemplates?.templates?.length) {
    await loadTirTemplate(defaultTirTemplateName());
  }
  if (!state.selectedWorkflowId) {
    state.selectedWorkflowId = standardWorkflows()[0]?.id || null;
  }
  state.dirtyVehicle = false;
  render();
}

function render() {
  renderTopbar();
  renderThemeButton();
  renderVehicleControls();
  renderMode();
  renderSetup();
  renderStandard();
  renderRailActions();
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
  primary.textContent = "Run Selected";
  primary.disabled = !selectedWorkflow();
  secondary.textContent = "Back to Setup";
  secondary.disabled = false;
}

function renderSetup() {
  renderVehicleLibrary();
  renderVehicleEditor();
  renderVehiclePreview(state.vehiclePayload?.data || {});
}

function renderVehicleLibrary() {
  const picker = document.getElementById("vehicle-library-picker");
  const vehicles = state.vehicleLibrary?.vehicles || [];
  if (!vehicles.some((vehicle) => vehicle.id === state.selectedVehicleSource)) {
    state.selectedVehicleSource = "active";
  }
  picker.innerHTML = vehicles.map((vehicle) => {
    const selected = vehicle.id === state.selectedVehicleSource ? " selected" : "";
    const prefix = vehicle.type === "template" ? "Template" : vehicle.type === "saved" ? "Saved" : "Active";
    return `<option value="${escapeHtml(vehicle.id)}"${selected}>${prefix}: ${escapeHtml(vehicle.label)}</option>`;
  }).join("");
  document.getElementById("save-vehicle-name").value ||= activeVehicleName();
  syncVehicleLibraryActions();
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
  form.oninput = (event) => {
    if (!event.target.closest("[data-tir-tools], [data-setup-filter]")) markVehicleDirty();
  };
  form.onchange = (event) => {
    if (!event.target.closest("[data-tir-tools], [data-setup-filter]")) markVehicleDirty();
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
  document.querySelectorAll(".config-section").forEach((section) => {
    section.querySelectorAll(".field-subsection").forEach((details) => {
      details.addEventListener("toggle", () => {
        if (!details.open) return;
        section.querySelectorAll(".field-subsection").forEach((other) => {
          if (other !== details) other.open = false;
        });
      });
    });
  });
}

function setupGuide(areaId = state.activeParamGroup) {
  const area = PARAMETER_AREAS.find((item) => item.id === areaId) || PARAMETER_AREAS[0];
  return {
    step: PARAMETER_AREAS.findIndex((item) => item.id === area.id) + 1,
    total: PARAMETER_AREAS.length,
    title: SETUP_GUIDE[area.id]?.title || area.label,
    focus: SETUP_GUIDE[area.id]?.focus || "",
  };
}

function renderSetupFocus() {
  const guide = setupGuide();
  document.getElementById("vehicle-preview-title").textContent =
    `${String(guide.step).padStart(2, "0")} ${guide.title}`;
  document.getElementById("vehicle-preview-subtitle").textContent = "";
  const heading = document.getElementById("editor-title");
  if (heading) heading.textContent = guide.title;
  renderWorkflowGuide(guide);
}

function renderWorkflowGuide(guide = setupGuide()) {
  const panel = document.getElementById("workflow-guide");
  if (!panel) return;
  const config = SETUP_GUIDE[PARAMETER_AREAS[guide.step - 1]?.id] || {};
  panel.innerHTML = `
    <div class="guide-row"><span>Purpose</span><strong>${escapeHtml(config.purpose || guide.focus)}</strong></div>
    <div class="guide-row"><span>Figure</span><strong>${escapeHtml(config.figure || "")}</strong></div>
    <div class="guide-row"><span>Check</span><strong>${escapeHtml(config.check || "")}</strong></div>
  `;
  panel.hidden = !state.referenceOpen;
  document.getElementById("reference-toggle-btn")?.classList.toggle("active", state.referenceOpen);
}

function markVehicleDirty() {
  state.dirtyVehicle = true;
  document.getElementById("save-status").textContent = "Unsaved";
  applyArchitectureVisibility();
  syncArchitectureDependentControls();
  renderArchitectureTemplateMatches();
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
  if (path.includes("mass") || path.includes("inertia") || path.startsWith("body.")) return "mass";
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

function fieldMatchesSuspensionSetup(path, label) {
  return path.endsWith(".actuation.rod_to")
    || path.endsWith(".actuation.shock.damper_model")
    || path.endsWith(".actuation.shock.dyno_reference")
    || path.endsWith(".actuation.shock.spring_table.table")
    || path.endsWith(".actuation.shock.free_length_m")
    || path.endsWith(".actuation.shock.damper_table.table")
    || path.endsWith(".actuation.bellcrank.order")
    || path.endsWith(".actuation.stabar.rate_n_m_per_rad")
    || label.includes("spring")
    || label.includes("damper");
}

function parameterAreaFields(area) {
  const extra = area.id === "tires"
    ? tireToolsHtml()
    : area.id === "vehicle"
      ? architectureToolsHtml(area.fields)
      : area.id === "powertrain"
        ? powertrainToolsHtml()
        : "";
  const fields = area.id === "vehicle" ? area.fields.filter((field) => !isArchitectureField(field)) : area.fields;
  if (!fields.length) {
    return `${extra}<div class="area-empty">${escapeHtml(emptyAreaCopy(area.id))}</div>`;
  }
  const grouped = groupFields(fields);
  return `${extra}${Object.entries(grouped).map(([group, fields]) => `
    <details class="field-subsection">
      <summary>
        <span>${escapeHtml(group)}</span>
        <small>${fields.length}</small>
      </summary>
      <div class="field-grid">${fields.map(fieldControl).join("")}</div>
    </details>
  `).join("")}`;
}

function isArchitectureField(field) {
  return fieldPathString(field).startsWith("architecture.");
}

function architectureToolsHtml(fields) {
  const frontField = fields.find((field) => fieldPathString(field) === "architecture.front");
  const rearField = fields.find((field) => fieldPathString(field) === "architecture.rear");
  const powertrains = availablePowertrains();
  const activePowertrain = powertrainProfile(state.vehiclePayload?.data || {}).id;
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
    const group = field.group || field.path?.[0] || "Vehicle";
    groups[group] ||= [];
    groups[group].push(field);
    return groups;
  }, {});
}

function renderParameterTabs(areas) {
  const tabs = document.getElementById("parameter-tabs");
  tabs.innerHTML = areas.map((area, index) => `
    <button class="parameter-tab ${area.id === state.activeParamGroup ? "active" : ""}" data-param-group="${escapeHtml(area.id)}" type="button">
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
  const unit = field.unit ? `<span>${escapeHtml(field.unit)}</span>` : "";
  const attrs = `data-config-path="${escapeHtml(field.key)}" data-kind="${escapeHtml(field.kind)}"`;
  const label = `<label>${escapeHtml(field.label)}${unit}</label>`;
  const value = field.value;
  const wrapperAttrs = fieldWrapperAttrs(field);
  if (isArrayField(field)) return arrayFieldControl(field, label);
  if (field.kind === "boolean") {
    return `<div class="form-field toggle-field" ${wrapperAttrs}>${label}<input ${attrs} type="checkbox"${value ? " checked" : ""}></div>`;
  }
  if (field.kind === "number" || field.kind === "integer") {
    const step = field.kind === "integer" ? "1" : "any";
    return `<div class="form-field" ${wrapperAttrs}>${label}<input ${attrs} type="number" step="${step}" required value="${escapeHtml(value ?? "")}"></div>`;
  }
  if (field.kind === "select") {
    const choices = field.choices.includes(value) ? field.choices : [value, ...field.choices].filter(Boolean);
    return `
      <div class="form-field" ${wrapperAttrs}>
        ${label}
        <select ${attrs}>
          ${choices.map((choice) => `<option value="${escapeHtml(choice)}"${choice === value ? " selected" : ""}>${escapeHtml(choice)}</option>`).join("")}
        </select>
      </div>
    `;
  }
  if (field.kind === "list" || field.kind === "json") {
    return `
      <div class="form-field" ${wrapperAttrs}>
        ${label}
        <textarea ${attrs}>${escapeHtml(JSON.stringify(value, null, 2))}</textarea>
      </div>
    `;
  }
  return `<div class="form-field" ${wrapperAttrs}>${label}<input ${attrs} type="text" value="${escapeHtml(value ?? "")}"></div>`;
}

function fieldWrapperAttrs(field) {
  return `data-field-wrapper data-field-path="${escapeHtml(fieldPathString(field))}"`;
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
  const attrs = `data-array-path="${escapeHtml(field.key)}" data-array-rank="${rank}" data-array-element-kind="${escapeHtml(elementKind)}"`;
  const control = rank === 2 ? matrixControl(field) : vectorControl(field);
  return `<div class="form-field array-field" ${fieldWrapperAttrs(field)} ${attrs}>${label}${control}</div>`;
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
    <div class="matrix-scroll">
      <div class="matrix-input" data-matrix-cols="${cols}">
        <div class="matrix-array-body">${body}</div>
      </div>
    </div>
    ${fixed ? "" : `<button class="array-action" type="button" data-array-action="add-row">Add row</button>`}
  `;
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
  if (path.includes("spring_table")) return ["Travel", "Force"][index] || `C${index + 1}`;
  if (path.includes("damper_table")) return ["Velocity", "Force"][index] || `C${index + 1}`;
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
  const values = {};
  document.querySelectorAll("#config-form [data-array-path]").forEach((container) => {
    values[container.dataset.arrayPath] = collectArrayValue(container, reportInvalid);
  });
  document.querySelectorAll("#config-form [data-config-path]").forEach((input) => {
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
  await refreshTirePayload();
  state.dirtyVehicle = false;
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
  state.vehicleLibrary = await api("/api/vehicles");
  await refreshTirePayload();
  state.dirtyVehicle = false;
  renderSetup();
}

async function loadVehicleSource() {
  const sourceId = document.getElementById("vehicle-library-picker").value;
  state.vehiclePayload = await api("/api/vehicles/load", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ source_id: sourceId }),
  });
  state.vehicleLibrary = await api("/api/vehicles");
  await refreshTirePayload();
  state.selectedVehicleSource = "active";
  state.dirtyVehicle = false;
  renderSetup();
}

async function importVehicleFile(file) {
  if (!file) return;
  const text = await file.text();
  state.vehiclePayload = await api("/api/configs/vehicle", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ mode: "raw", text }),
  });
  state.vehicleLibrary = await api("/api/vehicles");
  state.vehicleTemplates = await api("/api/vehicle-templates");
  await refreshTirePayload();
  await refreshTireTemplates();
  if (state.tireTemplates?.templates?.length) {
    await loadTirTemplate(defaultTirTemplateName());
  }
  state.selectedVehicleSource = "active";
  state.dirtyVehicle = false;
  document.getElementById("save-vehicle-name").value = file.name.replace(/\.(ya?ml)$/i, "");
  renderSetup();
}

async function applyVehicleTemplate(templateId) {
  if (!templateId) return;
  state.vehiclePayload = await api("/api/vehicle-template", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ template_id: templateId }),
  });
  state.vehicleLibrary = await api("/api/vehicles");
  await refreshTirePayload();
  await refreshTireTemplates();
  if (state.tireTemplates?.templates?.length) {
    await loadTirTemplate(defaultTirTemplateName());
  }
  state.selectedVehicleSource = "active";
  state.dirtyVehicle = false;
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
  document.getElementById("standard-context").textContent =
    `${activeVehicleName()} | ${activeArchitecture()} | StandardSim`;
  renderWorkflows();
  renderOutputs(selectedWorkflow());
  renderJobs();
}

function renderWorkflows() {
  const workflows = standardWorkflows();
  const grid = document.getElementById("workflow-grid");
  grid.innerHTML = workflows.map(workflowCard).join("");
  grid.querySelectorAll("[data-workflow]").forEach((card) => {
    card.addEventListener("click", () => {
      state.selectedWorkflowId = card.dataset.workflow;
      renderStandard();
    });
  });
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
      <div class="card-meta">${escapeHtml(workflow.config?.path || "")}</div>
      <div class="signal-row">
        <span class="mini-pill ${workflow.config?.exists ? "ok" : "missing"}">Config</span>
        <span class="mini-pill ${outputCount ? "ok" : "missing"}">${outputCount}/${workflow.outputs.length} outputs</span>
      </div>
    </article>
  `;
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
  runButton.textContent = workflow ? `${workflow.actions.length > 1 ? "Build + Run" : "Run"} ${workflow.label}` : "No Workflow";
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
  const rect = canvas.getBoundingClientRect();
  const width = Math.max(420, Math.floor(rect.width));
  const height = Math.max(360, Math.floor(rect.height));
  const dpr = window.devicePixelRatio || 1;
  canvas.width = Math.floor(width * dpr);
  canvas.height = Math.floor(height * dpr);
  const ctx = canvas.getContext("2d");
  ctx.setTransform(dpr, 0, 0, dpr, 0, 0);
  ctx.clearRect(0, 0, width, height);

  const area = activeParameterArea();
  syncPreviewModeControls(area);
  if (area.visual === "overview") {
    drawMbdReadinessPreview(ctx, width, height, data);
    return;
  }
  if (area.visual === "aero") {
    drawAeroMapPreview(ctx, width, height, data);
    return;
  }
  if (area.visual === "powertrain") {
    drawPowertrainPreview(ctx, width, height, data);
    return;
  }
  if (area.visual === "suspension") {
    drawSuspensionPreview(ctx, width, height, data);
    return;
  }
  if (area.visual === "tires") {
    drawTirePreview(ctx, width, height, data);
    return;
  }

  const model = filterVehicleModel(buildVehicleGeometry(data), sectionFocus(area.id));
  if (!model.points.length) return;
  const projected = model.points.map((point) => ({ ...point, ...projectPoint(point, state.vehiclePreviewView) }));
  const bounds = projected.reduce(
    (acc, point) => ({
      minX: Math.min(acc.minX, point.u - (point.shellRadiusM || 0)),
      maxX: Math.max(acc.maxX, point.u + (point.shellRadiusM || 0)),
      minY: Math.min(acc.minY, point.v - (point.shellRadiusM || 0)),
      maxY: Math.max(acc.maxY, point.v + (point.shellRadiusM || 0)),
    }),
    { minX: Infinity, maxX: -Infinity, minY: Infinity, maxY: -Infinity },
  );
  const spanX = Math.max(0.1, bounds.maxX - bounds.minX);
  const spanY = Math.max(0.1, bounds.maxY - bounds.minY);
  const scale = Math.min((width - 60) / spanX, (height - 60) / spanY);
  const map = new Map(projected.map((point) => [
    point.id,
    {
      ...point,
      x2: (point.u - (bounds.minX + bounds.maxX) / 2) * scale + width / 2,
      y2: height / 2 - (point.v - (bounds.minY + bounds.maxY) / 2) * scale,
    },
  ]));

  drawPreviewGrid(ctx, width, height);
  [...model.links]
    .sort((a, b) => ((map.get(a.from)?.depth || 0) + (map.get(a.to)?.depth || 0))
      - ((map.get(b.from)?.depth || 0) + (map.get(b.to)?.depth || 0)))
    .forEach((link) => drawCylinder(ctx, map.get(link.from), map.get(link.to), link));
  [...map.values()]
    .filter((point) => point.shellRadiusM)
    .sort((a, b) => a.depth - b.depth)
    .forEach((point) => drawGyrationShell(ctx, point, scale));
  [...map.values()]
    .sort((a, b) => a.depth - b.depth)
    .forEach((point) => drawSphere(ctx, point));
}

function syncPreviewModeControls(area = activeParameterArea()) {
  const controls = document.querySelector(".preview-controls");
  const canvas = document.getElementById("vehicle-canvas");
  const usesSpatialView = isSpatialPreviewArea(area);
  if (controls) controls.hidden = !usesSpatialView;
  if (canvas) canvas.classList.toggle("diagnostic-canvas", !usesSpatialView);
}

function isSpatialPreviewArea(area = activeParameterArea()) {
  return ["hardpoints", "mass"].includes(area.visual);
}

function activeParameterArea() {
  return PARAMETER_AREAS.find((area) => area.id === state.activeParamGroup) || PARAMETER_AREAS[0];
}

function canvasPalette() {
  return {
    bg: state.dark ? "#1d2630" : "#f7f9fb",
    surface: state.dark ? "#171e25" : "#ffffff",
    ink: state.dark ? "#e7edf3" : "#17202a",
    muted: state.dark ? "#9cacbb" : "#617181",
    line: state.dark ? "#303b47" : "#d8e0e7",
    blue: state.dark ? "#6aa7e8" : "#2567b3",
    green: state.dark ? "#78d0a8" : "#21835b",
    amber: state.dark ? "#e1aa5c" : "#a86612",
    red: state.dark ? "#e37a7a" : "#b43636",
    magenta: state.dark ? "#ff9dbe" : "#c2466f",
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
  ctx.fillStyle = ok ? palette.green : palette.amber;
  ctx.beginPath();
  ctx.arc(x + 5, y, 5, 0, Math.PI * 2);
  ctx.fill();
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
  drawPanel(ctx, x, y, width, height, palette.surface);
  ctx.fillStyle = check.ok ? palette.green : palette.amber;
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
  const light = state.dark ? 48 : 56;
  return `hsl(${hue}, 72%, ${light}%)`;
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

function sectionFocus(group) {
  const name = String(group || "").toLowerCase();
  const axle = name.includes("front") ? "front" : name.includes("rear") ? "rear" : null;
  let role = "overview";
  if (name.includes("mass")) role = "mass";
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
  return {
    points: model.points.filter((point) => !point.detail || point.role === "mass"),
    links: model.links.filter((link) => !link.detail),
  };
}

function pointVisibleForFocus(point, focus) {
  if (point.role === "mass") return !focus.axle || focus.role === "mass" || focus.role === "aero";
  if (focus.role === "mass") return point.role === "wheel";
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
    const radius = point.role === "mass" ? 4 : 2.4;
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
  ctx.strokeStyle = state.dark ? "#26323d" : "#e8edf2";
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

function drawGyrationShell(ctx, point, scale) {
  const radius = Math.max(14, Math.min(190, point.shellRadiusM * scale));
  ctx.save();
  ctx.fillStyle = state.dark ? "rgba(194, 70, 111, 0.12)" : "rgba(194, 70, 111, 0.1)";
  ctx.strokeStyle = state.dark ? "rgba(255, 157, 190, 0.42)" : "rgba(194, 70, 111, 0.36)";
  ctx.lineWidth = 2;
  ctx.beginPath();
  ctx.arc(point.x2, point.y2, radius, 0, Math.PI * 2);
  ctx.fill();
  ctx.stroke();
  ctx.beginPath();
  ctx.ellipse(point.x2, point.y2, radius, radius * 0.34, 0, 0, Math.PI * 2);
  ctx.stroke();
  ctx.restore();
}

function drawCylinder(ctx, from, to, link) {
  if (!from || !to) return;
  const width = link.width || 5;
  ctx.save();
  ctx.lineCap = "round";
  ctx.strokeStyle = state.dark ? "rgba(0,0,0,0.45)" : "rgba(16,25,34,0.2)";
  ctx.lineWidth = width + 3;
  ctx.beginPath();
  ctx.moveTo(from.x2, from.y2 + 1.5);
  ctx.lineTo(to.x2, to.y2 + 1.5);
  ctx.stroke();
  ctx.strokeStyle = link.color;
  ctx.lineWidth = width;
  ctx.beginPath();
  ctx.moveTo(from.x2, from.y2);
  ctx.lineTo(to.x2, to.y2);
  ctx.stroke();
  ctx.strokeStyle = "rgba(255,255,255,0.45)";
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
  const gradient = ctx.createRadialGradient(point.x2 - radius * 0.35, point.y2 - radius * 0.45, 1, point.x2, point.y2, radius);
  gradient.addColorStop(0, "#ffffff");
  gradient.addColorStop(0.28, point.color);
  gradient.addColorStop(1, state.dark ? "#0b1117" : "#24313f");
  ctx.save();
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
      detail: Boolean(meta.detail),
      shellRadiusM: meta.shellRadiusM || 0,
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
      });
    }
  };
  const addMassProperty = (rawCg, mass, inertia) => {
    const cg = toPoint(rawCg);
    const massValue = Number(mass);
    if (!cg || !Number.isFinite(massValue) || massValue <= 0) return;
    massProperties.push({ cg, mass: massValue, inertia });
  };

  addMassProperty(data.sprung_mass?.cg_m, data.sprung_mass?.mass_kg, data.sprung_mass?.inertia_kg_m2);
  addMassProperty(data.driver_mass?.cg_m, data.driver_mass?.mass_kg, data.driver_mass?.inertia_kg_m2);
  ["front", "rear"].forEach((axleName) => {
    const axle = data[axleName];
    if (!axle) return;
    const architecture = String(data.architecture?.[axleName] || "");
    ["left", "right"].forEach((sideName) => {
      addAxleSide(axleName, sideName, axle, architecture, addPoint, addLink);
      collectAxleMasses(sideName, axle, addMassProperty);
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
      role: "mass",
      shellRadiusM: aggregate.gyrationRadius,
    });
  }
  return { points, links };
}

function collectAxleMasses(sideName, axle, addMassProperty) {
  const side = sideName === "right" ? -1 : 1;
  const mirror = (raw) => {
    const point = toPoint(raw);
    if (!point) return null;
    return [point[0], point[1] * side, point[2]];
  };
  Object.values(axle.masses || {}).forEach((mass) => {
    addMassProperty(mirror(mass.cg_m), mass.mass_kg, mass.inertia_kg_m2);
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
    gyrationRadius: Math.max(0.08, Math.min(0.95, Math.sqrt(meanInertia / totalMass))),
  };
}

function inertiaDiagonal(inertia) {
  if (!Array.isArray(inertia)) return [0, 0, 0];
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
  const pointMeta = (role, detail = false) => ({ axle: axleName, role, detail });
  const linkMeta = (role, detail = false) => ({ axle: axleName, role, detail });

  addPoint(`${prefix}-lower-fore-i`, mirror(suspension.lower_fore_i_m), "hardpoint", 5, pointMeta("hardpoint"));
  addPoint(`${prefix}-lower-aft-i`, mirror(suspension.lower_aft_i_m), "hardpoint", 5, pointMeta("hardpoint"));
  addPoint(`${prefix}-lower-o`, mirror(suspension.lower_o_m), "upright", 6, pointMeta("upright"));
  addPoint(`${prefix}-upper-fore-i`, mirror(suspension.upper_fore_i_m), "hardpoint", 5, pointMeta("hardpoint"));
  addPoint(`${prefix}-upper-aft-i`, mirror(suspension.upper_aft_i_m), "hardpoint", 5, pointMeta("hardpoint"));
  addPoint(`${prefix}-upper-o`, mirror(suspension.upper_o_m), "upright", 6, pointMeta("upright"));
  addPoint(`${prefix}-tie-o`, mirror(suspension.tie_o_m), "steering", 5, pointMeta("steering"));
  addPoint(`${prefix}-wheel-center`, mirror(suspension.wheel_center_m), "wheel", 7, pointMeta("wheel"));
  addPoint(`${prefix}-rack`, mirror(steering.rack_pickup_m), "steering", 5, pointMeta("steering"));
  addPoint(`${prefix}-rod`, mirror(actuation.rod_mount_m), "actuation", 5, pointMeta("actuation", true));
  addPoint(`${prefix}-shock-mount`, mirror(shock.mount_m), "actuation", 5, pointMeta("actuation", true));
  if (hasBellcrank) {
    addPoint(`${prefix}-bellcrank-pivot`, mirror(bellcrank.pivot_m), "bellcrank", 6, pointMeta("bellcrank", true));
    addPoint(`${prefix}-bellcrank-rod`, mirror(pickups.rod), "bellcrank", 5, pointMeta("bellcrank", true));
    addPoint(`${prefix}-bellcrank-shock`, mirror(pickups.shock), "bellcrank", 5, pointMeta("bellcrank", true));
    if (hasStabar) {
      addPoint(`${prefix}-bellcrank-stabar`, mirror(pickups.stabar), "bellcrank", 5, pointMeta("bellcrank", true));
    }
  }
  if (hasStabar) {
    addPoint(`${prefix}-stabar-arm`, mirror(stabar.arm_end_m), "stabar", 5, pointMeta("stabar", true));
    addPoint(`${prefix}-stabar-bar`, mirror(stabar.bar_end_m), "stabar", 5, pointMeta("stabar", true));
  }

  addLink(`${prefix}-lower-fore-i`, `${prefix}-lower-o`, "lower", 6, linkMeta("lower"));
  addLink(`${prefix}-lower-aft-i`, `${prefix}-lower-o`, "lower", 6, linkMeta("lower"));
  addLink(`${prefix}-upper-fore-i`, `${prefix}-upper-o`, "upper", 5, linkMeta("upper"));
  addLink(`${prefix}-upper-aft-i`, `${prefix}-upper-o`, "upper", 5, linkMeta("upper"));
  addLink(`${prefix}-upper-o`, `${prefix}-lower-o`, "upright", 7, linkMeta("upright"));
  addLink(`${prefix}-rack`, `${prefix}-tie-o`, "steering", 4, linkMeta("steering"));
  addLink(`${prefix}-tie-o`, `${prefix}-wheel-center`, "steering", 4, linkMeta("steering"));
  addLink(`${prefix}-upper-o`, `${prefix}-wheel-center`, "wheel", 3, linkMeta("wheel"));
  addLink(`${prefix}-lower-o`, `${prefix}-wheel-center`, "wheel", 3, linkMeta("wheel"));
  addLink(`${prefix}-rod`, `${prefix}-lower-o`, "pushrod", 5, linkMeta("pushrod", true));
  addLink(`${prefix}-rod`, `${prefix}-bellcrank-rod`, "pushrod", 5, linkMeta("pushrod", true));
  addLink(`${prefix}-shock-mount`, `${prefix}-rod`, "shock", 6, linkMeta("shock", true));
  addLink(`${prefix}-shock-mount`, `${prefix}-bellcrank-shock`, "shock", 6, linkMeta("shock", true));
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
  return {
    hardpoint: "#2567b3",
    upright: "#4d5965",
    steering: "#21835b",
    wheel: "#6b7280",
    actuation: "#b43636",
    bellcrank: "#a86612",
    stabar: "#7c5cc4",
    mass: "#c2466f",
    inertia: "#3b82a0",
  }[group] || "#2567b3";
}

function linkColor(group) {
  return {
    lower: "#1f5f8d",
    upper: "#2d7a63",
    upright: "#4d5965",
    steering: "#21835b",
    wheel: "#7b8793",
    pushrod: "#2f8d58",
    shock: "#b43636",
    bellcrank: "#a86612",
    stabar: "#7c5cc4",
    inertia: "#3b82a0",
  }[group] || "#334155";
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
    if (!isSpatialPreviewArea()) return;
    canvas.setPointerCapture(event.pointerId);
    state.vehicleDrag = {
      x: event.clientX,
      y: event.clientY,
      yaw: state.vehiclePreviewYaw,
      pitch: state.vehiclePreviewPitch,
    };
  });
  canvas.addEventListener("pointermove", (event) => {
    if (!state.vehicleDrag || !isSpatialPreviewArea()) return;
    state.vehiclePreviewView = "iso";
    const sensitivity = 0.01 * state.rotationSensitivity;
    state.vehiclePreviewYaw = state.vehicleDrag.yaw - (event.clientX - state.vehicleDrag.x) * sensitivity;
    state.vehiclePreviewPitch = Math.max(
      -1.1,
      Math.min(1.1, state.vehicleDrag.pitch + (event.clientY - state.vehicleDrag.y) * sensitivity),
    );
    syncViewButtons();
    drawVehicleFromForm();
  });
  canvas.addEventListener("pointerup", () => {
    state.vehicleDrag = null;
  });
  canvas.addEventListener("pointercancel", () => {
    state.vehicleDrag = null;
  });
}

function resetVehicleView() {
  state.vehiclePreviewView = "iso";
  state.vehiclePreviewYaw = DEFAULT_VEHICLE_YAW;
  state.vehiclePreviewPitch = DEFAULT_VEHICLE_PITCH;
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
  document.getElementById("clear-log-btn").addEventListener("click", () => {
    document.getElementById("job-log").textContent = "";
  });
  document.getElementById("rotation-sensitivity").addEventListener("input", (event) => {
    state.rotationSensitivity = Number(event.target.value);
    localStorage.setItem("bobsim-rotation-sensitivity", String(state.rotationSensitivity));
    renderVehicleControls();
  });
  document.getElementById("reset-view-btn").addEventListener("click", resetVehicleView);
  document.getElementById("rail-primary-btn").addEventListener("click", async () => {
    if (state.view === "setup") await saveVehicleEdits();
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
      document.querySelectorAll(".tab").forEach((item) => {
        item.classList.toggle("active", item.dataset.tab === state.activeSimTab);
      });
      document.querySelectorAll(".panel").forEach((panel) => {
        panel.classList.toggle("active", panel.id === `${state.activeSimTab}-panel`);
      });
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
  wireVehicleCanvas();
  window.addEventListener("resize", drawVehicleFromForm);
}

wireEvents();
refresh();
setInterval(async () => {
  if ((state.status?.jobs || []).some((job) => job.status === "running" || job.status === "queued")) {
    state.status = await api("/api/status");
    renderStandard();
  }
}, 2000);
