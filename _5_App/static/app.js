const savedRotationSensitivity = Number(localStorage.getItem("bobsim-rotation-sensitivity"));
const savedSetupPaneWidth = Number(localStorage.getItem("bobsim-setup-pane-width"));
const savedGeometryPlotHeight = Number(localStorage.getItem("bobsim-geometry-plot-height"));
const savedGeometryShowFront = localStorage.getItem("bobsim-geometry-show-front");
const savedGeometryShowRear = localStorage.getItem("bobsim-geometry-show-rear");
const savedGeometryPlotSelections = (() => {
  try {
    const parsed = JSON.parse(localStorage.getItem("bobsim-geometry-plots") || "[]");
    if (!Array.isArray(parsed)) return [];
    const keyFor = (item) => {
      if (typeof item === "string") {
        return `${item.startsWith("roll_") ? "roll_deg" : "jounce_mm"}:${item}`;
      }
      if (!item || typeof item !== "object") return "";
      const y = String(item.y || item.id || "");
      const x = String(item.x || (y.startsWith("roll_") ? "roll_deg" : "jounce_mm"));
      return `${x}:${y}`;
    };
    const keys = parsed.map(keyFor).filter(Boolean);
    const oldDefaults = [
      ["jounce_mm:bump_camber_deg", "jounce_mm:bump_toe_deg", "jounce_mm:bump_rc_z_mm"],
      ["jounce_mm:bump_camber_deg", "jounce_mm:bump_toe_deg", "roll_deg:roll_camber_deg"],
    ];
    if (oldDefaults.some((defaults) => (
      defaults.length === keys.length && defaults.every((key, index) => key === keys[index])
    ))) {
      return [];
    }
    return parsed;
  } catch {
    return [];
  }
})();
const DEFAULT_VEHICLE_YAW = Math.PI - 0.72;
const DEFAULT_VEHICLE_PITCH = 0.46;
const DEFAULT_TIRE_SURFACE_YAW = -0.72;
const DEFAULT_TIRE_SURFACE_PITCH = 0.68;
const MIN_TIRE_SURFACE_ZOOM = 0.62;
const MAX_TIRE_SURFACE_ZOOM = 7.5;
const DEFAULT_SETUP_PANE_WIDTH = 320;
const MIN_SETUP_PANE_WIDTH = 260;
const MAX_SETUP_PANE_WIDTH = 620;
const DEFAULT_GEOMETRY_PLOT_HEIGHT = 252;
const MIN_GEOMETRY_PLOT_HEIGHT = 150;
const MAX_GEOMETRY_PLOT_HEIGHT = 560;
const MIN_VISUAL_PANE_WIDTH = 520;
const MIN_PREVIEW_ZOOM = 0.55;
const MAX_PREVIEW_ZOOM = 3.5;
const MAX_PREVIEW_PAN_FRACTION = 0.42;
const MAX_UNDO_STEPS = 80;
const MAX_GEOMETRY_PLOTS = 3;
const TIRE_LIVE_WHEEL_FIELDS = new Set(["camber_deg", "toe_deg", "radius_m"]);

const state = {
  status: null,
  vehiclePayload: null,
  vehicleLibrary: null,
  vehicleTemplates: null,
  tirePayload: null,
  tireTemplates: null,
  activeTir: null,
  activeTirCleanText: "",
  tireSaving: false,
  tirePayloadUpdating: false,
  tireStatusMessage: "",
  kinematicsPayload: null,
  kinematicsStatus: "idle",
  kinematicsRequestId: 0,
  kinematicsRefreshTimer: null,
  tirePayloadRequestId: 0,
  tirePayloadRefreshTimer: null,
  view: "setup",
  selectedVehicleSource: "active",
  selectedWorkflowId: null,
  selectedStudyWorkflowId: null,
  selectedJobId: null,
  toolchainModalOpen: false,
  toolchainSaving: false,
  toolchainInputsDirty: false,
  toolchainStatusMessage: "",
  activeSimTab: "setup",
  simModalOpen: false,
  activeStudyTab: "saved",
  simConfigPayload: null,
  simConfigLibrary: null,
  selectedSimConfigSource: "",
  dirtySimConfig: false,
  cleanSimConfigSignature: "",
  loadingSimConfigFor: null,
  savedResultsPayload: null,
  selectedResultId: null,
  resultSourcesPayload: null,
  selectedResultSourcePath: null,
  resultSourceDetail: null,
  resultSelectedSignals: [],
  resultXAxis: "__index__",
  resultSignalSearch: "",
  resultPlotPayload: null,
  resultPlotStatus: "idle",
  resultPlotMessage: "",
  savingResults: false,
  deletingResultId: null,
  resultsStatusMessage: "",
  processingPayload: null,
  selectedProcessingWorkflowId: null,
  processingStatusMessage: "",
  studyConfigPayload: null,
  studyConfigLibrary: null,
  selectedStudyConfigSource: "",
  dirtyStudyConfig: false,
  cleanStudyConfigSignature: "",
  loadingStudyConfigFor: null,
  activeParamGroup: null,
  vehicleStartOpen: true,
  dirtyVehicle: false,
  vehicleSaving: false,
  saveStatusMessage: "",
  vehicleDefinitionState: "pending",
  vehiclePreviewView: "iso",
  vehiclePreviewYaw: DEFAULT_VEHICLE_YAW,
  vehiclePreviewPitch: DEFAULT_VEHICLE_PITCH,
  vehiclePreviewZoom: 1,
  vehiclePreviewPanX: 0,
  vehiclePreviewPanY: 0,
  tireSurfaceYaw: DEFAULT_TIRE_SURFACE_YAW,
  tireSurfacePitch: DEFAULT_TIRE_SURFACE_PITCH,
  tireSurfaceZoom: 1,
  tireSurfacePanX: 0,
  tireSurfacePanY: 0,
  tireSurfaceDrag: null,
  tireSurfaceScene: null,
  tireSurfaceHover: null,
  activeTireTab: "setup",
  tireCombinedFzN: null,
  tireLoadCamberDeg: null,
  activePowertrainSubsystem: "pBattery",
  rotationSensitivity: Number.isFinite(savedRotationSensitivity) && savedRotationSensitivity > 0
    ? savedRotationSensitivity
    : 1,
  setupPaneWidth: Number.isFinite(savedSetupPaneWidth) && savedSetupPaneWidth > 0
    ? savedSetupPaneWidth
    : DEFAULT_SETUP_PANE_WIDTH,
  geometryPlotHeight: Number.isFinite(savedGeometryPlotHeight) && savedGeometryPlotHeight > 0
    ? savedGeometryPlotHeight
    : DEFAULT_GEOMETRY_PLOT_HEIGHT,
  vehicleDrag: null,
  geometryScene: null,
  geometryHoverPointId: null,
  geometrySelectedPointId: null,
  geometryDrag: null,
  geometryAxis: "x",
  geometryShiftActive: false,
  geometryShowFront: savedGeometryShowFront === null ? true : savedGeometryShowFront === "true",
  geometryShowRear: savedGeometryShowRear === null ? true : savedGeometryShowRear === "true",
  geometryPlotSelections: savedGeometryPlotSelections,
  geometryPlotDraftX: "jounce_mm",
  geometryPlotDraftY: "",
  geometryPlotScene: null,
  geometryPlotHover: null,
  massScene: null,
  massHoverPointId: null,
  massSelectedPointId: null,
  massEditorPositionFrame: null,
  suspensionPlotScene: null,
  suspensionPlotHover: null,
  suspensionPlotModalKey: null,
  suspensionPlotModalScene: null,
  suspensionPlotModalHover: null,
  architectureScene: null,
  architectureHoverId: null,
  architectureSelectedId: null,
  architectureSelectedOrderIndex: 0,
  architectureModalOpen: false,
  architectureModalAxle: null,
  architectureModalScene: null,
  architectureModalHoverId: null,
  architectureDrag: null,
  setupResize: null,
  geometryPlotResize: null,
  undoStack: [],
  pendingUndoSnapshot: null,
  cleanVehicleSignature: "",
  suppressUndo: false,
  referenceOpen: false,
  busyAction: null,
  modelicaWriting: false,
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

const TIRE_TABS = [
  { id: "setup", label: "Setup" },
  { id: "load-maps", label: "Load Maps" },
];

const POWERTRAIN_SUBSYSTEMS = [
  { id: "pBattery", label: "Battery", component: "Battery" },
  { id: "pVCU", label: "VCU", component: "VCU" },
  { id: "pInverter", label: "Inverter", component: "Inverter" },
  { id: "pMotor", label: "Motor", component: "Motor" },
  { id: "pDriveline", label: "Driveline", component: "Differential" },
];

const POWERTRAIN_MAIN_LOOP = ["pBattery", "pInverter", "pMotor", "pDriveline"];

const POWERTRAIN_OBJECT_LABELS = {
  pBattery: "Battery",
  pVCU: "VCU",
  pInverter: "Inverter",
  pMotor: "Motor",
  pDriveline: "Driveline",
};

const KNOWN_TIR_PARAMETERS = [
  ["FNOMIN", "Nominal load", "N"],
  ["FZMIN", "Minimum load", "N"],
  ["FZMAX", "Maximum load", "N"],
  ["IP_NOM", "Nominal pressure", "Pa"],
  ["UNLOADED_RADIUS", "Unloaded radius", "m"],
  ["WIDTH", "Section width", "m"],
  ["LONGVL", "Reference speed", "m/s"],
  ["LFZO", "Load scale", ""],
  ["LCX", "Fx shape scale", ""],
  ["LMUX", "Fx friction scale", ""],
  ["LEX", "Fx curvature scale", ""],
  ["LKX", "Fx stiffness scale", ""],
  ["LHX", "Fx horizontal shift scale", ""],
  ["LVX", "Fx vertical shift scale", ""],
  ["LGAX", "Fx camber scale", ""],
  ["PCX1", "Fx shape factor", ""],
  ["PDX1", "Fx friction coefficient 1", ""],
  ["PDX2", "Fx friction coefficient 2", ""],
  ["PDX3", "Fx camber friction coefficient", ""],
  ["PEX1", "Fx curvature coefficient 1", ""],
  ["PEX2", "Fx curvature coefficient 2", ""],
  ["PEX3", "Fx curvature coefficient 3", ""],
  ["PEX4", "Fx curvature sign coefficient", ""],
  ["PKX1", "Fx stiffness coefficient 1", ""],
  ["PKX2", "Fx stiffness coefficient 2", ""],
  ["PKX3", "Fx stiffness coefficient 3", ""],
  ["PHX1", "Fx horizontal shift 1", ""],
  ["PHX2", "Fx horizontal shift 2", ""],
  ["PVX1", "Fx vertical shift 1", ""],
  ["PVX2", "Fx vertical shift 2", ""],
  ["LCY", "Fy shape scale", ""],
  ["LMUY", "Fy friction scale", ""],
  ["LEY", "Fy curvature scale", ""],
  ["LKY", "Fy stiffness scale", ""],
  ["LHY", "Fy horizontal shift scale", ""],
  ["LVY", "Fy vertical shift scale", ""],
  ["LGAY", "Fy camber scale", ""],
  ["PCY1", "Fy shape factor", ""],
  ["PDY1", "Fy friction coefficient 1", ""],
  ["PDY2", "Fy friction coefficient 2", ""],
  ["PDY3", "Fy camber friction coefficient", ""],
  ["PEY1", "Fy curvature coefficient 1", ""],
  ["PEY2", "Fy curvature coefficient 2", ""],
  ["PEY3", "Fy curvature coefficient 3", ""],
  ["PEY4", "Fy camber curvature coefficient", ""],
  ["PKY1", "Fy stiffness coefficient 1", ""],
  ["PKY2", "Fy stiffness coefficient 2", ""],
  ["PKY3", "Fy camber stiffness coefficient", ""],
  ["PHY1", "Fy horizontal shift 1", ""],
  ["PHY2", "Fy horizontal shift 2", ""],
  ["PHY3", "Fy camber horizontal shift", ""],
  ["PVY1", "Fy vertical shift 1", ""],
  ["PVY2", "Fy vertical shift 2", ""],
  ["PVY3", "Fy camber vertical shift 1", ""],
  ["PVY4", "Fy camber vertical shift 2", ""],
  ["LXAL", "Fx combined-slip scale", ""],
  ["RCX1", "Fx combined shape", ""],
  ["RBX1", "Fx combined stiffness 1", ""],
  ["RBX2", "Fx combined stiffness 2", ""],
  ["REX1", "Fx combined curvature 1", ""],
  ["REX2", "Fx combined curvature 2", ""],
  ["RHX1", "Fx combined horizontal shift", ""],
  ["LYKA", "Fy combined-slip scale", ""],
  ["LVYKA", "Fy combined vertical scale", ""],
  ["RCY1", "Fy combined shape", ""],
  ["RBY1", "Fy combined stiffness 1", ""],
  ["RBY2", "Fy combined stiffness 2", ""],
  ["RBY3", "Fy combined stiffness offset", ""],
  ["REY1", "Fy combined curvature 1", ""],
  ["REY2", "Fy combined curvature 2", ""],
  ["RHY1", "Fy combined horizontal shift 1", ""],
  ["RHY2", "Fy combined horizontal shift 2", ""],
  ["RVY1", "Fy combined vertical shift 1", ""],
  ["RVY2", "Fy combined vertical shift 2", ""],
  ["RVY3", "Fy combined camber vertical shift", ""],
  ["RVY4", "Fy combined vertical alpha scale", ""],
  ["RVY5", "Fy combined vertical kappa scale", ""],
  ["RVY6", "Fy combined vertical kappa shape", ""],
  ["KPUMIN", "Minimum kappa", ""],
  ["KPUMAX", "Maximum kappa", ""],
  ["ALPMIN", "Minimum alpha", "rad"],
  ["ALPMAX", "Maximum alpha", "rad"],
];

const STUDY_GROUPS = [
  { id: "envelope", label: "Envelope", accent: "blue" },
  { id: "report", label: "Review", accent: "green" },
  { id: "opt", label: "Optimization", accent: "amber" },
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

const DEFAULT_KINEMATIC_CURVES = [
  { id: "bump_camber_deg", label: "Bump Camber", unit: "deg", x_id: "jounce_mm", x_label: "Jounce", x_unit: "mm", y_label: "Camber" },
  { id: "bump_toe_deg", label: "Bump Toe", unit: "deg", x_id: "jounce_mm", x_label: "Jounce", x_unit: "mm", y_label: "Toe" },
  { id: "bump_caster_deg", label: "Bump Caster", unit: "deg", x_id: "jounce_mm", x_label: "Jounce", x_unit: "mm", y_label: "Caster" },
  { id: "bump_kpi_deg", label: "Bump KPI", unit: "deg", x_id: "jounce_mm", x_label: "Jounce", x_unit: "mm", y_label: "Kingpin inclination" },
  { id: "bump_mech_trail_mm", label: "Bump Mechanical Trail", unit: "mm", x_id: "jounce_mm", x_label: "Jounce", x_unit: "mm", y_label: "Mechanical Trail" },
  { id: "bump_scrub_mm", label: "Bump Scrub Radius", unit: "mm", x_id: "jounce_mm", x_label: "Jounce", x_unit: "mm", y_label: "Scrub Radius" },
  { id: "bump_rc_y_mm", label: "Bump RC y-Migration", unit: "mm", x_id: "jounce_mm", x_label: "Jounce", x_unit: "mm", y_label: "RC y-Position" },
  { id: "bump_rc_z_mm", label: "Bump RC z-Migration", unit: "mm", x_id: "jounce_mm", x_label: "Jounce", x_unit: "mm", y_label: "RC z-Position" },
  { id: "roll_camber_deg", label: "Roll Camber", unit: "deg", x_id: "roll_deg", x_label: "Roll", x_unit: "deg", y_label: "Camber" },
  { id: "roll_toe_deg", label: "Roll Toe", unit: "deg", x_id: "roll_deg", x_label: "Roll", x_unit: "deg", y_label: "Toe" },
  { id: "roll_caster_deg", label: "Roll Caster", unit: "deg", x_id: "roll_deg", x_label: "Roll", x_unit: "deg", y_label: "Caster" },
  { id: "roll_kpi_deg", label: "Roll KPI", unit: "deg", x_id: "roll_deg", x_label: "Roll", x_unit: "deg", y_label: "Kingpin inclination" },
  { id: "roll_mech_trail_mm", label: "Roll Mechanical Trail", unit: "mm", x_id: "roll_deg", x_label: "Roll", x_unit: "deg", y_label: "Mechanical Trail" },
  { id: "roll_scrub_mm", label: "Roll Scrub Radius", unit: "mm", x_id: "roll_deg", x_label: "Roll", x_unit: "deg", y_label: "Scrub Radius" },
  { id: "roll_rc_y_mm", label: "Roll RC y-Migration", unit: "mm", x_id: "roll_deg", x_label: "Roll", x_unit: "deg", y_label: "RC y-Position" },
  { id: "roll_rc_z_mm", label: "Roll RC z-Migration", unit: "mm", x_id: "roll_deg", x_label: "Roll", x_unit: "deg", y_label: "RC z-Position" },
  { id: "bump_front_ic_y_mm", label: "Bump Front-View IC y", unit: "mm", x_id: "jounce_mm", x_label: "Jounce", x_unit: "mm", y_label: "Front-View IC y" },
  { id: "bump_front_ic_z_mm", label: "Bump Front-View IC z", unit: "mm", x_id: "jounce_mm", x_label: "Jounce", x_unit: "mm", y_label: "Front-View IC z" },
  { id: "bump_front_swing_arm_mm", label: "Bump Front-View Swing Arm", unit: "mm", x_id: "jounce_mm", x_label: "Jounce", x_unit: "mm", y_label: "Swing Arm Length" },
  { id: "bump_rc_height_mm", label: "Bump RC Height", unit: "mm", x_id: "jounce_mm", x_label: "Jounce", x_unit: "mm", y_label: "RC Height above Contact Patch" },
  { id: "bump_rc_migration_mm", label: "Bump RC Migration", unit: "mm", x_id: "jounce_mm", x_label: "Jounce", x_unit: "mm", y_label: "RC Migration" },
  { id: "roll_front_ic_y_mm", label: "Roll Front-View IC y", unit: "mm", x_id: "roll_deg", x_label: "Roll", x_unit: "deg", y_label: "Front-View IC y" },
  { id: "roll_front_ic_z_mm", label: "Roll Front-View IC z", unit: "mm", x_id: "roll_deg", x_label: "Roll", x_unit: "deg", y_label: "Front-View IC z" },
  { id: "roll_front_swing_arm_mm", label: "Roll Front-View Swing Arm", unit: "mm", x_id: "roll_deg", x_label: "Roll", x_unit: "deg", y_label: "Swing Arm Length" },
  { id: "roll_rc_height_mm", label: "Roll RC Height", unit: "mm", x_id: "roll_deg", x_label: "Roll", x_unit: "deg", y_label: "RC Height above Contact Patch" },
  { id: "roll_rc_migration_mm", label: "Roll RC Migration", unit: "mm", x_id: "roll_deg", x_label: "Roll", x_unit: "deg", y_label: "RC Migration" },
];

async function api(path, options = {}) {
  const response = await fetch(path, options);
  const data = await response.json();
  if (!response.ok) throw new Error(data.error || response.statusText);
  return data;
}

async function refreshTirePayload(vehicle = null, { showBusy = false } = {}) {
  if (showBusy) {
    state.tirePayloadUpdating = true;
    renderTirActionState();
  }
  try {
    const payload = vehicle
      ? await api("/api/tires/eval", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ vehicle }),
      })
      : await api("/api/tires/eval");
    state.tirePayload = payload;
    syncTireCombinedFzFromPayload();
    syncTireLoadCamberFromPayload();
    return true;
  } catch (error) {
    if (!state.tirePayload) {
      state.tirePayload = { model: error.message, sides: [] };
      state.tireCombinedFzN = null;
    } else {
      state.tirePayload = { ...state.tirePayload, model: error.message };
    }
    return false;
  } finally {
    if (showBusy) {
      state.tirePayloadUpdating = false;
      renderTirActionState();
    }
  }
}

function queueTirePayloadRefresh() {
  const requestId = state.tirePayloadRequestId + 1;
  state.tirePayloadRequestId = requestId;
  state.tirePayloadUpdating = true;
  renderTirActionState();
  window.clearTimeout(state.tirePayloadRefreshTimer);
  state.tirePayloadRefreshTimer = window.setTimeout(async () => {
    const vehicle = currentVehicleFormData();
    if (!vehicle) {
      if (requestId === state.tirePayloadRequestId) {
        state.tirePayloadUpdating = false;
        renderTirActionState();
      }
      return;
    }
    await refreshTirePayload(vehicle);
    if (requestId !== state.tirePayloadRequestId) return;
    state.tirePayloadUpdating = false;
    renderTirActionState();
    drawVehicleFromForm();
  }, 180);
}

async function refreshKinematicsPayload(vehicle = state.vehiclePayload?.data || {}) {
  const requestId = state.kinematicsRequestId + 1;
  state.kinematicsRequestId = requestId;
  state.kinematicsStatus = state.kinematicsPayload ? "refreshing" : "loading";
  try {
    const payload = await api("/api/kinematics/curves", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ vehicle }),
    });
    if (requestId !== state.kinematicsRequestId) return;
    state.kinematicsPayload = payload;
    state.kinematicsStatus = "ready";
  } catch (error) {
    if (requestId !== state.kinematicsRequestId) return;
    state.kinematicsPayload = {
      model: error.message,
      available: false,
      sweep_m: [],
      axles: {},
      warnings: [error.message],
    };
    state.kinematicsStatus = "error";
  }
}

function queueKinematicsRefresh({ force = false } = {}) {
  window.clearTimeout(state.kinematicsRefreshTimer);
  if (!force && !isKinematicPlotArea()) return;
  state.kinematicsStatus = state.kinematicsPayload ? "refreshing" : "loading";
  state.kinematicsRefreshTimer = window.setTimeout(() => {
    refreshKinematicsPayload(currentVehicleFormData()).then(() => {
      if (isKinematicPlotArea()) {
        drawVehicleFromForm();
        renderGeometryPlotControls();
      }
    });
  }, 220);
}

async function refreshVehicleDiagnostics(vehicle = state.vehiclePayload?.data || {}) {
  await Promise.all([
    refreshTirePayload(),
    refreshKinematicsPayload(vehicle),
  ]);
}

async function refreshTireTemplates() {
  try {
    state.tireTemplates = await api("/api/tires/templates");
  } catch (error) {
    state.tireTemplates = { templates: [], error: error.message };
  }
}

async function refreshSavedResults() {
  try {
    state.savedResultsPayload = await api("/api/results");
  } catch (error) {
    state.savedResultsPayload = { results: [], error: error.message };
  }
  const results = savedResults();
  if (!results.some((result) => result.id === state.selectedResultId)) {
    state.selectedResultId = results[0]?.id || null;
  }
}

async function refreshResultSources() {
  try {
    const query = activeVehicleKey() ? `?vehicle_key=${encodeURIComponent(activeVehicleKey())}` : "";
    state.resultSourcesPayload = await api(`/api/results/sources${query}`);
  } catch (error) {
    state.resultSourcesPayload = { sources: [], error: error.message };
  }
  const sources = resultSources();
  if (!sources.some((source) => source.path === state.selectedResultSourcePath)) {
    state.selectedResultSourcePath = sources[0]?.path || null;
    state.resultSourceDetail = null;
    state.resultSelectedSignals = [];
    state.resultPlotPayload = null;
  }
}

async function refreshProcessingWorkflows() {
  try {
    const query = activeVehicleKey() ? `?vehicle_key=${encodeURIComponent(activeVehicleKey())}` : "";
    state.processingPayload = await api(`/api/processing/workflows${query}`);
  } catch (error) {
    state.processingPayload = { workflows: [], error: error.message };
  }
  const workflows = processingWorkflows();
  if (!workflows.some((workflow) => workflow.id === state.selectedProcessingWorkflowId)) {
    state.selectedProcessingWorkflowId = workflows[0]?.id || null;
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

function activeVehicleWorkspace() {
  return state.status?.vehicle_workspace || {};
}

function activeVehicleKey() {
  return activeVehicleWorkspace().key || "";
}

function activeVehicleConfigReady() {
  const workspace = activeVehicleWorkspace();
  return Boolean(workspace.key && workspace.config?.exists);
}

function vehicleWorkspaceStatusLabel() {
  const workspace = activeVehicleWorkspace();
  if (!workspace.key) return "No vehicle config selected";
  return `Config ${workspace.key}`;
}

function studyWorkflows() {
  const studyGroups = new Set(STUDY_GROUPS.map((group) => group.id));
  return (state.status?.workflows || []).filter((workflow) => studyGroups.has(workflow.group));
}

function selectedWorkflow() {
  const workflows = standardWorkflows();
  return workflows.find((workflow) => workflow.id === state.selectedWorkflowId) || workflows[0] || null;
}

function savedResults() {
  return state.savedResultsPayload?.results || [];
}

function selectedSavedResult() {
  const results = savedResults();
  return results.find((result) => result.id === state.selectedResultId) || results[0] || null;
}

function resultSources() {
  return state.resultSourcesPayload?.sources || [];
}

function processingWorkflows() {
  return state.processingPayload?.workflows || [];
}

function selectedProcessingWorkflow() {
  const workflows = processingWorkflows();
  return workflows.find((workflow) => workflow.id === state.selectedProcessingWorkflowId) || workflows[0] || null;
}

function selectedResultSource() {
  const sources = resultSources();
  return sources.find((source) => source.path === state.selectedResultSourcePath) || sources[0] || null;
}

function boblibInitialized() {
  return Boolean(state.status?.repo?.boblib_package?.exists);
}

function externalToolchainAvailable() {
  return Boolean(state.status?.external_toolchain?.available);
}

function workflowAvailable(workflow) {
  return Boolean(workflow) && workflow.available !== false;
}

function workflowUnavailableMessage(workflow) {
  return workflow?.unavailable_reason
    || state.status?.external_toolchain?.reason
    || "Simulation runner unavailable.";
}

function vehicleDefinitionCurrent() {
  return Boolean(state.vehiclePayload) && !state.dirtyVehicle && state.vehicleDefinitionState === "current";
}

function vehicleDefinitionPending() {
  return Boolean(state.vehiclePayload) && !state.dirtyVehicle && state.vehicleDefinitionState === "pending";
}

function canWriteMbd() {
  return boblibInitialized() && activeVehicleConfigReady() && vehicleDefinitionPending() && !state.modelicaWriting;
}

function canUseStandardSim() {
  return externalToolchainAvailable() && vehicleDefinitionCurrent() && activeVehicleConfigReady();
}

function canRunStandardWorkflow(workflow = selectedWorkflow()) {
  return canUseStandardSim() && workflowAvailable(workflow);
}

function canSaveActiveResults() {
  const workflow = selectedWorkflow();
  return activeVehicleConfigReady() && Boolean(workflow?.outputs?.some((output) => output.exists)) && !state.savingResults;
}

function saveActiveResultsDisabledReason() {
  if (state.savingResults) return "Saving active simulation results";
  if (!activeVehicleConfigReady()) return "Save this vehicle config before storing results";
  const workflow = selectedWorkflow();
  if (!workflow) return "Select a simulation first";
  if (!workflow.outputs?.some((output) => output.exists)) return "Run a simulation before saving active results";
  return "Save active simulation results";
}

function selectedStudyWorkflow() {
  const workflows = studyWorkflows();
  const workflow = workflows.find((item) => item.id === state.selectedStudyWorkflowId) || workflows[0] || null;
  if (workflow && !state.selectedStudyWorkflowId) state.selectedStudyWorkflowId = workflow.id;
  return workflow;
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

async function refreshSelectedStudyConfig() {
  const workflow = selectedStudyWorkflow();
  if (!workflow?.config_id) {
    state.studyConfigPayload = null;
    state.studyConfigLibrary = null;
    state.cleanStudyConfigSignature = "";
    state.dirtyStudyConfig = false;
    return;
  }
  state.loadingStudyConfigFor = workflow.id;
  const [payload, library] = await Promise.all([
    api(`/api/configs/${encodeURIComponent(workflow.config_id)}`),
    api(`/api/sim-configs?workflow_id=${encodeURIComponent(workflow.id)}`),
  ]);
  state.studyConfigPayload = payload;
  state.studyConfigLibrary = library;
  state.selectedStudyConfigSource = library.sources?.[0]?.id || "";
  acceptCleanStudyConfigPayload();
  state.loadingStudyConfigFor = null;
}

function ensureSelectedStudyConfigLoaded() {
  const workflow = selectedStudyWorkflow();
  if (!workflow?.config_id || state.loadingStudyConfigFor === workflow.id) return;
  if (state.studyConfigPayload?.id === workflow.config_id) return;
  refreshSelectedStudyConfig()
    .then(renderStudies)
    .catch((error) => {
      state.loadingStudyConfigFor = null;
      state.studyConfigPayload = null;
      state.studyConfigLibrary = { sources: [], error: error.message };
      renderStudies();
    });
}

function configDataSignature(data) {
  return JSON.stringify(data ?? {});
}

function acceptCleanSimConfigPayload() {
  state.cleanSimConfigSignature = configDataSignature(state.simConfigPayload?.data || {});
  state.dirtySimConfig = false;
}

function acceptCleanStudyConfigPayload() {
  state.cleanStudyConfigSignature = configDataSignature(state.studyConfigPayload?.data || {});
  state.dirtyStudyConfig = false;
}

function activeVehicleName() {
  return state.vehiclePayload?.data?.vehicle?.name || "Active vehicle";
}

function setSaveStatus(message) {
  state.saveStatusMessage = message || "";
  const saveStatus = document.getElementById("save-status");
  if (saveStatus) {
    saveStatus.textContent = state.saveStatusMessage || (state.dirtyVehicle ? "Unsaved" : "Saved");
  }
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
  await refreshVehicleDiagnostics(state.vehiclePayload?.data || {});
  await refreshTireTemplates();
  await refreshSavedResults();
  if (!state.activeTir && state.tireTemplates?.templates?.length) {
    await loadTirTemplate(defaultTirTemplateName());
  }
  if (!state.selectedWorkflowId) {
    state.selectedWorkflowId = standardWorkflows()[0]?.id || null;
  }
  if (!state.selectedStudyWorkflowId) {
    state.selectedStudyWorkflowId = studyWorkflows()[0]?.id || null;
  }
  await refreshSelectedSimConfig();
  render();
}

async function refreshStatus() {
  state.status = await api("/api/status");
}

function render() {
  renderTopbar();
  renderThemeButton();
  renderVehicleControls();
  applySetupPaneWidth();
  renderMode();
  renderSetup();
  renderStandard();
  renderToolchainModal();
  renderStudies();
  renderRailActions();
  renderVehicleStartModal();
  renderArchitectureConnectionModal();
}

function renderTopbar() {
  const repo = state.status?.repo;
  document.getElementById("repo-root").textContent = repo?.root ? "Local BobSim workspace" : "";
  const toolchainButton = document.getElementById("toolchain-settings-btn");
  if (toolchainButton) {
    const toolchain = openmodelicaToolchain();
    toolchainButton.title = toolchain.reason || "OpenModelica toolchain";
  }
  renderModelicaStack();
}

function renderModelicaStack() {
  const stack = state.status?.modelica || {};
  const definitionCurrent = vehicleDefinitionCurrent() && activeVehicleConfigReady();
  setModelicaStep(
    "boblib-initialized-step",
    boblibInitialized() ? "BobLib submodule initialized" : "BobLib submodule missing",
    boblibInitialized() ? "ok" : "warn",
  );
  setModelicaStep(
    "modelica-write-step",
    modelicaDefinitionTitle(stack),
    modelicaDefinitionTone(stack),
  );

  const vehicleBuild = stack.builds?.vehicle || {};
  const fourPostBuild = stack.builds?.four_post || {};
  const buildReadyTone = (build) => (["built", "cached"].includes(build.state) ? "ok" : "warn");
  setModelicaStep(
    "modelica-vehicle-build-step",
    definitionCurrent ? `VehicleSim ${vehicleBuild.label || "status unknown"}` : "Save and write the vehicle config first",
    definitionCurrent ? buildReadyTone(vehicleBuild) : "disabled",
  );
  setModelicaStep(
    "modelica-four-post-build-step",
    definitionCurrent ? `FourPostSim ${fourPostBuild.label || "status unknown"}` : "Save and write the vehicle config first",
    definitionCurrent ? buildReadyTone(fourPostBuild) : "disabled",
  );

  renderRailActions();
}

function setModelicaStep(stepId, title, tone) {
  const step = document.getElementById(stepId);
  if (step) step.className = `modelica-stack-step ${tone}`;
  if (step) step.title = title;
}

function modelicaDefinitionTitle(stack) {
  if (state.dirtyVehicle) return "Save the vehicle before writing the vehicle definition to MBD";
  if (stack.state === "error") return stack.error || "Vehicle definition status unavailable";
  if (state.vehicleDefinitionState === "current") return "Vehicle definition is current in MBD";
  if (state.vehicleDefinitionState === "pending") return "Vehicle definition is saved and ready to write to MBD";
  return "Save the vehicle before writing to MBD";
}

function modelicaDefinitionTone(stack) {
  if (!state.vehiclePayload) return "disabled";
  if (state.dirtyVehicle || state.vehicleDefinitionState === "invalid") return "error";
  if (stack.state === "error") return "error";
  if (state.vehicleDefinitionState === "current") return "ok";
  return "warn";
}

function renderThemeButton() {
  document.getElementById("theme-toggle-btn").textContent = state.dark ? "Light" : "Dark";
}

function actionBusy(actionKey) {
  return Boolean(actionKey && state.busyAction === actionKey);
}

function startActionBusy() {
  return ["start-load", "start-create", "start-import"].includes(state.busyAction);
}

function actionButtonContent(label, busy) {
  return `${busy ? `<span class="action-spinner" aria-hidden="true"></span>` : ""}<span>${escapeHtml(label)}</span>`;
}

function setActionButton(button, { label, busy = false, busyLabel = label, disabled = false, title = "" }) {
  if (!button) return;
  button.innerHTML = actionButtonContent(busy ? busyLabel : label, busy);
  button.disabled = Boolean(disabled || busy);
  button.classList.toggle("is-loading", busy);
  button.setAttribute("aria-busy", busy ? "true" : "false");
  button.title = title || "";
}

function renderVehicleMenuActions() {
  const saveButton = document.getElementById("save-vehicle-btn");
  setActionButton(saveButton, {
    label: "Save As",
    busy: state.vehicleSaving && actionBusy("menu-save-vehicle"),
    busyLabel: "Saving",
    disabled: state.vehicleSaving || state.modelicaWriting || !state.vehiclePayload,
  });
}

function renderBusyActionSurfaces() {
  renderRailActions();
  renderVehicleMenuActions();
  renderVehicleStartModal();
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
  const importButton = document.getElementById("start-import-btn");
  const activeButton = document.getElementById("start-active-btn");
  const startBusy = startActionBusy();
  const loadSources = savedVehicleSources();
  if (loadPicker) {
    loadPicker.innerHTML = loadSources.length
      ? loadSources.map((vehicle) => `<option value="${escapeHtml(vehicle.id)}">Saved: ${escapeHtml(vehicle.label)}</option>`).join("")
      : `<option value="">No saved vehicles yet</option>`;
    loadPicker.disabled = startBusy;
  }
  setActionButton(loadButton, {
    label: "Load Vehicle",
    busy: actionBusy("start-load"),
    busyLabel: "Loading",
    disabled: !loadSources.length || startBusy,
  });

  const templates = state.vehicleTemplates?.templates || [];
  if (templatePicker) {
    templatePicker.innerHTML = templates.map((template) => `
      <option value="${escapeHtml(template.id)}">${escapeHtml(templateArchitectureLabel(template))}</option>
    `).join("");
    templatePicker.disabled = startBusy;
  }
  setActionButton(createButton, {
    label: "Create Vehicle",
    busy: actionBusy("start-create"),
    busyLabel: "Creating",
    disabled: !templates.length || startBusy,
  });
  const nameInput = document.getElementById("start-vehicle-name");
  if (nameInput && !nameInput.value) nameInput.value = nextVehicleName();
  if (nameInput) nameInput.disabled = startBusy;
  setActionButton(importButton, {
    label: "Import YAML",
    busy: actionBusy("start-import"),
    busyLabel: "Importing",
    disabled: startBusy,
  });
  setActionButton(activeButton, {
    label: "Continue Active File",
    disabled: startBusy,
  });
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
  if (max < min) return min;
  return Math.min(max, Math.max(min, value));
}

function finiteRange(values, { positive = false } = {}) {
  let min = Infinity;
  let max = -Infinity;
  let count = 0;
  (values || []).forEach((value) => {
    const numeric = Number(value);
    if (!Number.isFinite(numeric)) return;
    if (positive && numeric <= 0) return;
    min = Math.min(min, numeric);
    max = Math.max(max, numeric);
    count += 1;
  });
  return count ? { min, max, count } : null;
}

function finiteMax(values, fallback = 0) {
  const range = finiteRange(values);
  return range ? range.max : fallback;
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

function simulationLockedMessage() {
  if (!activeVehicleConfigReady()) return "Save this vehicle config before viewing Simulation.";
  if (!vehicleDefinitionCurrent()) return "Write the saved vehicle definition to MBD before viewing Simulation.";
  if (!externalToolchainAvailable()) return state.status?.external_toolchain?.reason || "Simulation runner unavailable.";
  return "Simulation is available.";
}

function standardWorkflowLockedMessage(workflow = selectedWorkflow()) {
  if (!canUseStandardSim()) return simulationLockedMessage();
  if (!workflowAvailable(workflow)) return workflowUnavailableMessage(workflow);
  return "";
}

function geometryPlotHeightBounds() {
  const stage = document.querySelector(".visual-stage");
  const height = stage?.getBoundingClientRect().height || 0;
  const toolbarHeight = document.querySelector(".preview-toolbar")?.getBoundingClientRect().height || 46;
  const maxByViewport = height > 0
    ? height - toolbarHeight - 260
    : MAX_GEOMETRY_PLOT_HEIGHT;
  const max = Math.max(
    MIN_GEOMETRY_PLOT_HEIGHT,
    Math.min(MAX_GEOMETRY_PLOT_HEIGHT, maxByViewport),
  );
  return { min: MIN_GEOMETRY_PLOT_HEIGHT, max };
}

function setGeometryPlotHeight(height, { persist = false, redraw = true } = {}) {
  const { min, max } = geometryPlotHeightBounds();
  const clamped = clamp(Number(height) || DEFAULT_GEOMETRY_PLOT_HEIGHT, min, max);
  state.geometryPlotHeight = clamped;
  applyGeometryPlotHeight(clamped, min, max);
  if (persist) localStorage.setItem("bobsim-geometry-plot-height", String(Math.round(clamped)));
  if (redraw) requestAnimationFrame(drawVehicleFromForm);
}

function applyGeometryPlotHeight(height = state.geometryPlotHeight, min, max) {
  const stage = document.querySelector(".visual-stage");
  if (!stage) return;
  const bounds = min === undefined || max === undefined ? geometryPlotHeightBounds() : { min, max };
  const clamped = clamp(Number(height) || DEFAULT_GEOMETRY_PLOT_HEIGHT, bounds.min, bounds.max);
  state.geometryPlotHeight = clamped;
  stage.style.setProperty("--geometry-plot-height", `${Math.round(clamped)}px`);
  const splitter = document.getElementById("geometry-plot-splitter");
  if (splitter) {
    splitter.setAttribute("aria-valuemin", String(Math.round(bounds.min)));
    splitter.setAttribute("aria-valuemax", String(Math.round(bounds.max)));
    splitter.setAttribute("aria-valuenow", String(Math.round(clamped)));
  }
}

function renderMode() {
  document.querySelectorAll(".rail-item").forEach((button) => {
    const disabled = button.dataset.view === "standard" && !canUseStandardSim();
    button.disabled = disabled;
    button.classList.toggle("disabled", disabled);
    button.classList.toggle("active", button.dataset.view === state.view && !disabled);
    if (button.dataset.view === "standard") {
      button.title = disabled ? simulationLockedMessage() : "";
    }
  });
  document.querySelectorAll(".screen").forEach((screen) => {
    screen.classList.toggle("active", screen.id === `${state.view}-view`);
  });
}

function renderRailActions() {
  const primary = document.getElementById("rail-primary-btn");
  const secondary = document.getElementById("rail-secondary-btn");
  if (state.view === "setup") {
    secondary.classList.add("run-button");
    secondary.classList.remove("ghost-button");
    const needsVehicleConfig = !activeVehicleConfigReady();
    const canSaveVehicle = Boolean(state.vehiclePayload) && (state.dirtyVehicle || needsVehicleConfig);
    setActionButton(primary, {
      label: "Save Vehicle",
      busy: state.vehicleSaving && actionBusy("rail-save-vehicle"),
      busyLabel: "Saving",
      disabled: !canSaveVehicle || state.modelicaWriting || state.vehicleSaving,
      title: state.dirtyVehicle
        ? "Save active vehicle edits and update the saved config"
        : needsVehicleConfig
        ? "Save this vehicle config"
        : "Vehicle has no unsaved edits",
    });
    setActionButton(secondary, {
      label: "Write to MBD",
      busy: state.modelicaWriting && actionBusy("rail-write-mbd"),
      busyLabel: "Writing",
      disabled: !canWriteMbd() || state.vehicleSaving,
      title: mbdWriteDisabledReason(),
    });
    return;
  }
  secondary.classList.add("ghost-button");
  secondary.classList.remove("run-button");
  if (state.view === "studies") {
    setActionButton(primary, {
      label: "Refresh Archive",
      busy: false,
      disabled: false,
      title: "Refresh local simulation archive",
    });
  } else {
    const workflow = selectedWorkflow();
    setActionButton(primary, {
      label: "Configure Simulation",
      disabled: !canRunStandardWorkflow(workflow),
      title: canRunStandardWorkflow(workflow) ? "" : standardWorkflowLockedMessage(workflow),
    });
  }
  setActionButton(secondary, {
    label: "Back to Vehicle",
  });
}

function mbdWriteDisabledReason() {
  if (state.modelicaWriting) return "Writing vehicle definition to MBD";
  if (!boblibInitialized()) return "Initialize the BobLib submodule first";
  if (!state.vehiclePayload) return "Load or create a vehicle first";
  if (!activeVehicleConfigReady()) return "Save this vehicle config before writing to MBD";
  if (state.dirtyVehicle || state.vehicleDefinitionState === "invalid") return "Save the vehicle before writing to MBD";
  if (state.vehicleDefinitionState === "current") return "Vehicle definition is already current in MBD";
  return "Write the saved vehicle definition to MBD";
}

function renderSetup() {
  renderVehicleLibrary();
  renderVehicleEditor();
  renderModelicaStack();
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
  renderVehicleMenuActions();
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
  renderVehicleMenuActions();
}

function renderVehicleEditor() {
  if (!state.vehiclePayload) return;
  document.getElementById("config-path").textContent = state.vehiclePayload.path;
  document.getElementById("config-text").value = state.vehiclePayload.raw;
  setSaveStatus(state.saveStatusMessage);

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
    if (!event.target.closest("[data-tir-tools], [data-tire-load-controls], [data-setup-filter]")) {
      commitUndoBaseline("input");
      markVehicleDirty(event.target);
    }
  };
  form.onchange = (event) => {
    if (!event.target.closest("[data-tir-tools], [data-tire-load-controls], [data-setup-filter]")) {
      if (!event.target.matches?.("input[type='text'], input[type='number'], textarea")) {
        commitUndoBaseline("change");
      }
      markVehicleDirty(event.target);
    }
  };
  form.onclick = handleArrayEditorClick;
  wireArchitectureTools();
  wireTireTabs();
  wireTireAssignments();
  wireTireLoadControls();
  wirePowertrainSubsystems();
  wireTireTools();
  wireTirParameterFields();
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
  if (isTextEntryTarget(event.target) || event.target?.closest?.("#setup-splitter, #geometry-plot-splitter")) return;
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

function acceptCleanVehiclePayload({ resetUndo = true, definitionState = "pending" } = {}) {
  state.cleanVehicleSignature = vehicleDataSignature(state.vehiclePayload?.data || {});
  state.dirtyVehicle = false;
  state.vehicleDefinitionState = definitionState;
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
  if (state.dirtyVehicle) state.vehicleDefinitionState = "invalid";
  else if (state.vehicleDefinitionState === "invalid") state.vehicleDefinitionState = "pending";
  state.saveStatusMessage = "";
  setSaveStatus("");
  renderMode();
  renderRailActions();
  renderModelicaStack();
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
  if (state.dirtyVehicle) state.vehicleDefinitionState = "invalid";
  else if (state.vehicleDefinitionState === "invalid") state.vehicleDefinitionState = "pending";
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

function markVehicleDirty(target = null) {
  updateDirtyState();
  const data = currentVehicleFormData();
  if (data) applyVehicleDataToPayload(data);
  applyArchitectureVisibility();
  syncArchitectureDependentControls();
  renderArchitectureTemplateMatches();
  renderArchitectureConnectionModal();
  drawVehicleFromForm();
  renderParameterTabCanvases();
  if (!isTireSetupFieldTarget(target)) queueKinematicsRefresh();
  if (isTirePayloadRefreshTarget(target)) queueTirePayloadRefresh();
}

function configPathFromTarget(target) {
  if (!target?.dataset?.configPath) return null;
  try {
    const path = JSON.parse(target.dataset.configPath);
    return Array.isArray(path) ? path : null;
  } catch {
    return null;
  }
}

function isTireSetupFieldTarget(target) {
  const path = configPathFromTarget(target);
  if (!path) return false;
  return ["front", "rear"].includes(path[0]) && (
    path[1] === "tire"
    || isTireAlignmentFieldTarget(target)
  );
}

function isTireAlignmentFieldTarget(target) {
  const path = configPathFromTarget(target);
  return Boolean(
    path
    && ["front", "rear"].includes(path[0])
    && path[1] === "wheel"
    && TIRE_LIVE_WHEEL_FIELDS.has(path[2]),
  );
}

function isTirePayloadRefreshTarget(target) {
  const path = configPathFromTarget(target);
  return Boolean(path && ["front", "rear"].includes(path[0]) && (
    path[1] === "tire"
    || isTireAlignmentFieldTarget(target)
  ));
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
  if (area.id === "tires") return tireSectionHtml(area);
  if (area.id === "powertrain") return powertrainSectionHtml(area);
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

function tireSectionHtml(area) {
  if (!TIRE_TABS.some((tab) => tab.id === state.activeTireTab)) state.activeTireTab = "setup";
  const tabs = `
    <div class="tire-subtabs" role="tablist" aria-label="Tire setup views">
      ${TIRE_TABS.map((tab) => `
        <button class="tire-subtab ${state.activeTireTab === tab.id ? "active" : ""}" data-tire-tab="${escapeHtml(tab.id)}" type="button">
          ${escapeHtml(tab.label)}
        </button>
      `).join("")}
    </div>
  `;
  if (state.activeTireTab === "load-maps") {
    return `${tabs}${tireLoadMapControlsHtml()}${tireParameterToolsHtml()}${tirParameterPanelHtml()}`;
  }
  return `${tabs}${tireAssignmentHtml()}${tireSetupFieldsHtml(area.fields)}`;
}

function tireSetupFieldsHtml(fields) {
  const setupFields = (fields || []).filter((field) => {
    const path = fieldPathString(field);
    return path !== "front.tire.template" && path !== "rear.tire.template";
  });
  if (!setupFields.length) return "";
  return fieldGroupSections(setupFields, "tires");
}

function tireAssignmentHtml() {
  const templates = state.tireTemplates?.templates || [];
  const options = (selected) => templates.length
    ? templates.map((template) => `
      <option value="${escapeHtml(template.id)}"${template.id === selected ? " selected" : ""}>${escapeHtml(template.label)}</option>
    `).join("")
    : `<option value="">No tire templates</option>`;
  const data = currentVehicleFormData() || state.vehiclePayload?.data || {};
  return `
    <div class="tire-assignment-grid">
      ${["front", "rear"].map((side) => {
        const selected = data?.[side]?.tire?.template || "";
        const evalSide = (state.tirePayload?.sides || []).find((item) => item.side === side);
        return `
          <section class="tire-assignment-card">
            <h4>${escapeHtml(humanizeToken(side))}</h4>
            <input type="hidden" data-config-path="${escapeHtml(JSON.stringify([side, "tire", "template"]))}" data-kind="string" value="${escapeHtml(selected)}">
            <select class="config-picker" data-tire-assignment="${escapeHtml(side)}">
              ${options(selected)}
            </select>
            <dl>
              <div><dt>Active</dt><dd>${escapeHtml(selected || "none")}</dd></div>
              <div><dt>Fz</dt><dd>${formatNumber(evalSide?.fz_n)} N</dd></div>
              <div><dt>Camber</dt><dd>${formatNumber(evalSide?.camber_deg)} deg</dd></div>
            </dl>
          </section>
        `;
      }).join("")}
    </div>
  `;
}

function tireLoadMapControlsHtml() {
  const range = tireCombinedFzRange();
  const value = currentTireCombinedFz();
  const disabled = !(Number.isFinite(range.min) && Number.isFinite(range.max) && range.max > range.min);
  const step = Math.max(1, Math.round((range.max - range.min) / 120));
  const camberRange = tireLoadCamberRange();
  const camberValue = currentTireLoadCamberDeg();
  const camberDisabled = !(Number.isFinite(camberRange.min) && Number.isFinite(camberRange.max) && camberRange.max > camberRange.min);
  const camberStep = Math.max(0.1, Math.round(((camberRange.max - camberRange.min) / 96) * 100) / 100);
  const sides = state.tirePayload?.sides || [];
  const baseLoads = sides.length
    ? sides.map((side) => `${humanizeToken(side.side)} ${formatNumber(side.fz_n)} N`).join(" / ")
    : "No active tire loads";
  const camberSource = sides.length
    ? sides.map((side) => `${humanizeToken(side.side)} ${formatSignedNumber(side.camber_deg)} deg`).join(" / ")
    : "No active camber";
  return `
    <div class="tire-load-controls" data-tire-load-controls>
      <div class="tire-load-row">
        <div class="tire-load-head">
          <span>Combined Fz</span>
          <strong id="tire-combined-fz-value">${formatNumber(value)} N</strong>
        </div>
        <input
          id="tire-combined-fz-slider"
          type="range"
          min="${escapeHtml(range.min)}"
          max="${escapeHtml(range.max)}"
          step="${escapeHtml(step)}"
          value="${escapeHtml(value)}"
          ${disabled ? "disabled" : ""}
        >
        <div class="tire-load-meta">
          <span>${formatNumber(range.min)} N</span>
          <span>${escapeHtml(baseLoads)}</span>
          <span>${formatNumber(range.max)} N</span>
        </div>
      </div>
      <div class="tire-load-row">
        <div class="tire-load-head">
          <span>Camber / IA</span>
          <strong id="tire-load-camber-value">${formatSignedNumber(camberValue)} deg</strong>
        </div>
        <input
          id="tire-load-camber-slider"
          type="range"
          min="${escapeHtml(camberRange.min)}"
          max="${escapeHtml(camberRange.max)}"
          step="${escapeHtml(camberStep)}"
          value="${escapeHtml(camberValue)}"
          ${camberDisabled ? "disabled" : ""}
        >
        <div class="tire-load-meta">
          <span>${formatSignedNumber(camberRange.min)} deg</span>
          <span>${escapeHtml(camberSource)}</span>
          <span>${formatSignedNumber(camberRange.max)} deg</span>
        </div>
      </div>
    </div>
  `;
}

function tireParameterToolsHtml() {
  return `
    <div class="tir-tools compact-tir-tools" data-tir-tools>
      <div class="tir-tools-head">
        <select id="tir-template-picker" class="config-picker"></select>
        <button id="save-tir-btn" class="ghost-button" type="button">Save .tir + Update Plot</button>
      </div>
      <div class="tir-status-row">
        <span id="tir-editor-meta"></span>
        <span class="tir-update-state">
          <span id="tir-update-spinner" class="tir-spinner" hidden aria-hidden="true"></span>
          <span id="tir-update-status"></span>
        </span>
      </div>
    </div>
  `;
}

function tireCombinedFzRange() {
  const sideRanges = (state.tirePayload?.sides || []).map((side) => {
    const metadata = side.metadata || {};
    const combined = side.curves?.combined || {};
    const samples = [
      side.fz_n,
      metadata.fzmin_n,
      metadata.fzmax_n,
      metadata.fznom_n,
      ...(combined.fx_surfaces_by_fz || []).map((surface) => surface.fz_n),
      ...(combined.fy_surfaces_by_fz || []).map((surface) => surface.fz_n),
    ].map(Number).filter((value) => Number.isFinite(value) && value > 0);
    const range = finiteRange(samples);
    return range ? { min: range.min, max: range.max, samples } : null;
  }).filter(Boolean);
  const samples = sideRanges.flatMap((range) => range.samples);
  if (!samples.length) return { min: 1, max: 1 };
  const sampleRange = finiteRange(samples, { positive: true });
  let min = sideRanges.length ? finiteMax(sideRanges.map((range) => range.min), sampleRange?.min || 1) : sampleRange.min;
  let max = sideRanges.length
    ? (finiteRange(sideRanges.map((range) => range.max))?.min ?? sampleRange.max)
    : sampleRange.max;
  if (max <= min) {
    min = sampleRange.min;
    max = sampleRange.max;
  }
  if (max <= min) {
    min = Math.max(1, min * 0.5);
    max = Math.max(min + 1, max * 1.5);
  }
  return { min, max };
}

function defaultTireCombinedFz() {
  const sideLoads = (state.tirePayload?.sides || [])
    .map((side) => Number(side.fz_n))
    .filter((value) => Number.isFinite(value) && value > 0);
  if (sideLoads.length) {
    return sideLoads.reduce((total, value) => total + value, 0) / sideLoads.length;
  }
  const nominalLoads = (state.tirePayload?.sides || [])
    .map((side) => Number(side.metadata?.fznom_n))
    .filter((value) => Number.isFinite(value) && value > 0);
  return nominalLoads[0] || 1;
}

function currentTireCombinedFz() {
  const range = tireCombinedFzRange();
  const fallback = defaultTireCombinedFz();
  return clamp(Number(state.tireCombinedFzN) || fallback, range.min, range.max);
}

function syncTireCombinedFzFromPayload() {
  const range = tireCombinedFzRange();
  if (!(Number.isFinite(range.min) && Number.isFinite(range.max) && range.max >= range.min)) {
    state.tireCombinedFzN = null;
    return;
  }
  state.tireCombinedFzN = currentTireCombinedFz();
}

function tireLoadCamberRange() {
  const samples = (state.tirePayload?.sides || []).flatMap((side) => {
    const combined = side.curves?.combined || {};
    const pure = side.curves?.pure || {};
    return [
      side.camber_deg,
      ...(pure.longitudinal_by_gamma || []).map((surface) => surface.gamma_deg),
      ...(pure.lateral_by_gamma || []).map((surface) => surface.gamma_deg),
      ...(combined.force_maps_by_gamma || []).map((surface) => surface.gamma_deg),
      ...(combined.force_maps_by_gamma_fz || []).map((surface) => surface.gamma_deg),
    ];
  }).map(Number).filter(Number.isFinite);
  if (!samples.length) return { min: 0, max: 0 };
  const range = finiteRange(samples);
  return { min: range.min, max: range.max };
}

function defaultTireLoadCamberDeg() {
  const cambers = (state.tirePayload?.sides || [])
    .map((side) => Number(side.camber_deg))
    .filter(Number.isFinite);
  if (cambers.length) return cambers.reduce((total, value) => total + value, 0) / cambers.length;
  return 0;
}

function currentTireLoadCamberDeg() {
  const range = tireLoadCamberRange();
  const fallback = defaultTireLoadCamberDeg();
  return clamp(Number(state.tireLoadCamberDeg ?? fallback), range.min, range.max);
}

function syncTireLoadCamberFromPayload() {
  const range = tireLoadCamberRange();
  if (!(Number.isFinite(range.min) && Number.isFinite(range.max) && range.max >= range.min)) {
    state.tireLoadCamberDeg = null;
    return;
  }
  state.tireLoadCamberDeg = currentTireLoadCamberDeg();
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
          <select id="architecture-powertrain-select" data-config-path="${escapeHtml(JSON.stringify(["powertrain", "implementation"]))}" data-kind="select">
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

function powertrainSectionHtml(area) {
  const data = currentVehicleFormData() || state.vehiclePayload?.data || {};
  const profile = powertrainProfile(data);
  const subsystems = powertrainSubsystems(profile, area.fields);
  if (!subsystems.some((subsystem) => subsystem.id === state.activePowertrainSubsystem)) {
    state.activePowertrainSubsystem = subsystems[0]?.id || "pBattery";
  }
  const implementationField = area.fields.find((field) => fieldPathString(field) === "powertrain.implementation");
  return `
    <div class="powertrain-config-panel">
      ${powertrainImplementationHtml(profile, implementationField)}
      <div class="powertrain-subsystem-tabs" role="tablist" aria-label="Powertrain subsystems">
        ${subsystems.map((subsystem) => `
          <button
            class="powertrain-subsystem-tab ${state.activePowertrainSubsystem === subsystem.id ? "active" : ""}"
            data-powertrain-subsystem="${escapeHtml(subsystem.id)}"
            aria-selected="${state.activePowertrainSubsystem === subsystem.id ? "true" : "false"}"
            role="tab"
            type="button"
          >
            <span>${escapeHtml(subsystem.label)}</span>
            <small>${subsystem.fields.length}</small>
          </button>
        `).join("")}
      </div>
      <div class="powertrain-subsystem-panels">
        ${subsystems.map((subsystem) => `
          <section class="powertrain-subsystem-panel" data-powertrain-panel="${escapeHtml(subsystem.id)}"${state.activePowertrainSubsystem === subsystem.id ? "" : " hidden"}>
            <div class="powertrain-subsystem-head">
              <span>${escapeHtml(subsystem.label)}</span>
              <small>${escapeHtml(profile.id)}</small>
            </div>
            ${subsystem.fields.length
              ? `<div class="field-grid">${subsystem.fields.map(fieldControl).join("")}</div>`
              : `<div class="area-empty">No ${escapeHtml(subsystem.label.toLowerCase())} specs are exposed for this architecture.</div>`}
          </section>
        `).join("")}
      </div>
    </div>
  `;
}

function powertrainImplementationHtml(profile, field) {
  const choices = availablePowertrains();
  const key = field?.key || JSON.stringify(["powertrain", "implementation"]);
  return `
    <div class="powertrain-implementation-card">
      <div>
        <span class="tool-label">Implementation</span>
        <strong>${escapeHtml(profile.label)}</strong>
      </div>
      <select class="config-picker" data-config-path="${escapeHtml(key)}" data-kind="select" data-powertrain-implementation>
        ${choices.map((item) => `
          <option value="${escapeHtml(item.id)}"${item.id === profile.id ? " selected" : ""}>${escapeHtml(item.label)}</option>
        `).join("")}
      </select>
      <span class="mini-pill ok">${escapeHtml(humanizeToken(profile.status))}</span>
    </div>
  `;
}

function powertrainSubsystems(profile, fields) {
  const components = new Set((profile.components || []).map((item) => String(item).toLowerCase()));
  const specs = fields.filter((field) => {
    const path = fieldPathString(field);
    return path.startsWith("powertrain.") && path !== "powertrain.implementation";
  });
  return POWERTRAIN_SUBSYSTEMS
    .filter((subsystem) => subsystem.always || components.has(String(subsystem.component).toLowerCase()))
    .map((subsystem) => ({
      ...subsystem,
      fields: specs.filter((field) => powertrainFieldSubsystem(field) === subsystem.id),
    }));
}

function powertrainFieldSubsystem(field) {
  return String(field.path?.[1] || "pVCU");
}

function availablePowertrains() {
  return state.vehicleTemplates?.powertrains?.length
    ? state.vehicleTemplates.powertrains
    : [{ id: "EVBatInvMotDiff", label: "EV battery/VCU/inverter/motor/differential", status: "implemented", components: ["Battery", "VCU", "Inverter", "Motor", "Differential"] }];
}

function wireArchitectureTools() {
  const tools = document.querySelector("[data-architecture-tools]");
  if (!tools) return;
  tools.querySelectorAll("select").forEach((select) => {
    select.addEventListener("change", () => {
      if (select.id === "architecture-powertrain-select") syncPowertrainImplementationInputs(select.value);
      renderArchitectureTemplateMatches();
    });
  });
  tools.querySelector("#architecture-template-list")?.addEventListener("click", (event) => {
    const button = event.target.closest("[data-template-apply]");
    const picker = document.getElementById("architecture-template-picker");
    if (button && picker?.value) applyVehicleTemplate(picker.value);
  });
}

function syncPowertrainImplementationInputs(value) {
  const key = JSON.stringify(["powertrain", "implementation"]);
  Array.from(document.querySelectorAll("#config-form [data-config-path]"))
    .filter((input) => input.dataset.configPath === key)
    .forEach((input) => {
      input.value = value;
    });
}

function wirePowertrainSubsystems() {
  const panel = document.querySelector(".powertrain-config-panel");
  if (!panel) return;
  panel.querySelectorAll("[data-powertrain-subsystem]").forEach((button) => {
    button.addEventListener("click", () => {
      state.activePowertrainSubsystem = button.dataset.powertrainSubsystem || "pBattery";
      panel.querySelectorAll("[data-powertrain-subsystem]").forEach((item) => {
        item.classList.toggle("active", item === button);
        item.setAttribute("aria-selected", item === button ? "true" : "false");
      });
      panel.querySelectorAll("[data-powertrain-panel]").forEach((section) => {
        section.hidden = section.dataset.powertrainPanel !== state.activePowertrainSubsystem;
      });
      drawVehicleFromForm();
    });
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
        <button id="save-tir-btn" class="ghost-button" type="button">Save .tir + Update Plot</button>
      </div>
      <div class="tir-status-row">
        <span id="tir-editor-meta"></span>
        <span class="tir-update-state">
          <span id="tir-update-spinner" class="tir-spinner" hidden aria-hidden="true"></span>
          <span id="tir-update-status"></span>
        </span>
      </div>
      <textarea id="tir-editor" class="tir-editor" spellcheck="false"></textarea>
    </div>
  `;
}

function parseTirParameterText(text) {
  const params = new Map();
  const lines = String(text || "").split(/\r?\n/);
  lines.forEach((line, index) => {
    const match = line.match(/^\s*([A-Za-z][A-Za-z0-9_]*)\s*=\s*([^$!#;]+)/);
    if (!match) return;
    const key = match[1].toUpperCase();
    const value = match[2].trim();
    if (!params.has(key)) params.set(key, { key, value, lineIndex: index });
  });
  return { params, lines };
}

function tirParameterPanelHtml() {
  const parsed = parseTirParameterText(state.activeTir?.text || "");
  const knownKeys = new Set(KNOWN_TIR_PARAMETERS.map(([key]) => key));
  const knownRows = KNOWN_TIR_PARAMETERS.map(([key, label, unit]) => {
    const param = parsed.params.get(key);
    const missing = !param;
    return `
      <label class="tir-param-row ${missing ? "missing" : ""}">
        <span class="tir-param-key">${escapeHtml(key)}</span>
        <span class="tir-param-label">${escapeHtml(label)}</span>
        <input
          class="tir-param-input"
          data-tir-param="${escapeHtml(key)}"
          value="${escapeHtml(param?.value || "")}"
          placeholder="not in .tir"
          ${missing ? "disabled" : ""}
        >
        <span class="tir-param-unit">${escapeHtml(unit || "")}</span>
      </label>
    `;
  }).join("");
  const unknownRows = [...parsed.params.values()]
    .filter((param) => !knownKeys.has(param.key))
    .sort((left, right) => left.key.localeCompare(right.key))
    .map((param) => `
      <div class="tir-param-row unknown">
        <span class="tir-param-key">${escapeHtml(param.key)}</span>
        <span class="tir-param-label">Unknown parameter</span>
        <input class="tir-param-input" value="${escapeHtml(param.value)}" disabled>
        <span class="tir-param-unit">!</span>
      </div>
    `).join("");
  return `
    <div class="tir-param-panel" data-tir-param-panel>
      <div class="tir-param-grid">${knownRows}</div>
      ${unknownRows ? `<div class="tir-param-unknown">${unknownRows}</div>` : ""}
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
  if (isKinematicPlotArea()) queueKinematicsRefresh({ force: true });
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
  if (path[0] === "powertrain" && path[1]) return POWERTRAIN_OBJECT_LABELS[path[1]] || humanizeToken(path[1]);
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
      implementation: "Architecture",
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
  const choices = JSON.stringify(Array.isArray(field.choices) ? field.choices : []);
  const attrs = `data-array-path="${escapeHtml(field.key)}" data-array-rank="${rank}" data-array-element-kind="${escapeHtml(elementKind)}" data-array-choices="${escapeHtml(choices)}"${field.disabled ? ` data-field-disabled="true"` : ""}`;
  const control = rank === 2 ? matrixControl(field) : vectorControl(field);
  return `<div class="form-field array-field ${field.disabled ? "disabled-field" : ""}" ${fieldWrapperAttrs(field)} ${attrs}>${label}${control}${fieldHelpHtml(field)}</div>`;
}

function vectorControl(field) {
  const values = Array.isArray(field.value) ? field.value : [];
  const coordinate = isNumericArrayKind(field.array_element_kind) && values.length === 3;
  const displayValues = values.length ? values : Array.from({ length: isNumericArrayKind(field.array_element_kind) ? 3 : 0 }, () => "");
  const cells = displayValues.map((value, index) => vectorCell(field, value, index, coordinate)).join("");
  const variableQueue = vectorSupportsQueueControls(field, coordinate);
  return `
    <div class="array-literal ${coordinate ? "coordinate-input" : "array-list-input"} ${variableQueue ? "array-queue-input" : ""}" data-array-list>
      <span class="array-bracket">[</span>
      <div class="array-inline-cells">
        ${cells}
      </div>
      <span class="array-bracket">]</span>
      ${variableQueue ? `
        <div class="array-queue-actions" aria-label="List controls">
          <button class="array-icon-button" type="button" data-array-action="add-item" aria-label="Add item" title="Add item">+</button>
          <button class="array-icon-button" type="button" data-array-action="remove-item" aria-label="Remove last item" title="Remove last item"${displayValues.length <= 1 ? " disabled" : ""}>-</button>
        </div>
      ` : ""}
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

function vectorSupportsQueueControls(field, coordinate) {
  if (coordinate || field.disabled) return false;
  if (field.array_shape?.length !== 1) return false;
  const path = fieldPathString(field);
  if (path.includes(".actuation.bellcrank.order")) return false;
  return true;
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
  const vehicleForm = container.closest("#config-form");
  if (vehicleForm) pushUndoSnapshot(snapshotVehicleState(`array-${action}`));
  if (action === "add-item") addArrayItem(container);
  else if (action === "remove-item") removeArrayItem(button, container);
  else if (action === "add-row") addMatrixRow(container);
  else if (action === "remove-row") removeMatrixRow(button, container);
  renumberArrayEditor(container);
  if (vehicleForm) markVehicleDirty();
  else if (container.closest("#sim-config-form")) markSimConfigDirty();
  else if (container.closest("#study-config-form")) markStudyConfigDirty();
}

function addArrayItem(container) {
  const list = container.querySelector("[data-array-list]");
  if (!list) return;
  const kind = container.dataset.arrayElementKind || "number";
  const choices = arrayChoicesFromContainer(container);
  const cells = list.querySelector(".array-inline-cells");
  if (!cells) return;
  const index = cells.querySelectorAll(".array-list-row").length;
  cells.insertAdjacentHTML("beforeend", `
    <label class="array-list-row array-cell">
      <span>#${index + 1}</span>
      ${arrayCellInputHtml(kind, { index }, choices[0] ?? defaultArrayValue(kind), choices)}
    </label>
  `);
}

function arrayChoicesFromContainer(container) {
  try {
    const parsed = JSON.parse(container.dataset.arrayChoices || "[]");
    return Array.isArray(parsed) ? parsed : [];
  } catch {
    return [];
  }
}

function removeArrayItem(button, container) {
  const rows = Array.from(container.querySelectorAll(".array-list-row"));
  if (rows.length <= 1) return;
  const row = button.closest(".array-list-row") || rows[rows.length - 1];
  row?.remove();
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

function collectVehicleValues({ reportInvalid = false, skipInvalid = false } = {}) {
  return collectConfigValues("#config-form", { reportInvalid, skipInvalid });
}

function collectSimConfigValues({ reportInvalid = false } = {}) {
  return collectConfigValues("#sim-config-form", { reportInvalid });
}

function collectStudyConfigValues({ reportInvalid = false } = {}) {
  return collectConfigValues("#study-config-form", { reportInvalid });
}

function currentStudyConfigData() {
  if (!state.studyConfigPayload) return {};
  try {
    const data = JSON.parse(JSON.stringify(state.studyConfigPayload.data || {}));
    const values = collectStudyConfigValues();
    Object.entries(values).forEach(([key, value]) => setNestedValue(data, JSON.parse(key), value));
    return data;
  } catch {
    return state.studyConfigPayload.data || {};
  }
}

function collectConfigValues(rootSelector, { reportInvalid = false, skipInvalid = false } = {}) {
  const values = {};
  document.querySelectorAll(`${rootSelector} [data-array-path]:not([data-field-disabled='true'])`).forEach((container) => {
    try {
      values[container.dataset.arrayPath] = collectArrayValue(container, reportInvalid);
    } catch (error) {
      if (!skipInvalid) throw error;
    }
  });
  document.querySelectorAll(`${rootSelector} [data-config-path]:not(:disabled)`).forEach((input) => {
    try {
      values[input.dataset.configPath] = collectPrimitiveValue(input, reportInvalid);
    } catch (error) {
      if (!skipInvalid) throw error;
    }
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

async function saveVehicleEdits({ successMessage = "Vehicle saved" } = {}) {
  let values;
  try {
    values = collectVehicleValues({ reportInvalid: true });
  } catch (error) {
    setSaveStatus(error.message);
    return null;
  }
  setSaveStatus("Saving vehicle...");
  try {
    const payload = await api("/api/configs/vehicle", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ mode: "patch", values }),
    });
    state.vehiclePayload = payload;
    acceptCleanVehiclePayload({ definitionState: "pending" });
    await refreshStatus();
    state.vehicleLibrary = await api("/api/vehicles");
    await refreshVehicleDiagnostics(state.vehiclePayload?.data || {});
    renderSetup();
    setSaveStatus(successMessage);
    return payload;
  } catch (error) {
    setSaveStatus(error.message || "Could not save vehicle");
    renderRailActions();
    return null;
  }
}

async function saveVehicleAs({ useNameInput = true, actionKey = "rail-save-vehicle" } = {}) {
  if (state.vehicleSaving) return null;
  state.vehicleSaving = true;
  state.busyAction = actionKey;
  renderBusyActionSurfaces();
  try {
    const payload = await saveVehicleEdits({ successMessage: "Vehicle edits saved" });
    if (!payload) return null;
    const nameInput = document.getElementById("save-vehicle-name");
    const name = useNameInput && nameInput?.value.trim() ? nameInput.value.trim() : activeVehicleName();
    setSaveStatus(`Saving ${name}...`);
    try {
      state.vehicleLibrary = await api("/api/vehicles/save", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ name }),
      });
      state.selectedVehicleSource = state.vehicleLibrary.saved?.id || "active";
      await refreshStatus();
      await refreshSavedResults();
      await refreshResultSources();
      await refreshProcessingWorkflows();
      renderSetup();
      setSaveStatus(`Saved ${name}`);
      return state.vehicleLibrary;
    } catch (error) {
      setSaveStatus(error.message || "Could not save vehicle config");
      renderRailActions();
      return null;
    }
  } finally {
    state.vehicleSaving = false;
    if (state.busyAction === actionKey) state.busyAction = null;
    renderBusyActionSurfaces();
  }
}

async function generateModelicaFromVehicle({ actionKey = "rail-write-mbd" } = {}) {
  if (!canWriteMbd()) {
    const saveStatus = document.getElementById("save-status");
    if (saveStatus) saveStatus.textContent = mbdWriteDisabledReason();
    renderRailActions();
    return;
  }
  state.modelicaWriting = true;
  state.busyAction = actionKey;
  renderBusyActionSurfaces();
  renderModelicaStack();
  try {
    const generated = await api("/api/modelica/generate", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({}),
    });
    state.vehicleDefinitionState = "current";
    state.status = await api("/api/status");
    await refreshSavedResults();
    await refreshResultSources();
    await refreshProcessingWorkflows();
    setSaveStatus(`Wrote ${generated.record?.name || "vehicle definition"} to MBD`);
    renderTopbar();
    renderModelicaStack();
    state.activeSimTab = "setup";
    setView("standard");
  } catch (error) {
    setSaveStatus(error.message);
    renderModelicaStack();
  } finally {
    state.modelicaWriting = false;
    if (state.busyAction === actionKey) state.busyAction = null;
    renderBusyActionSurfaces();
    renderModelicaStack();
  }
}

async function saveRawVehicle() {
  setSaveStatus("Saving raw vehicle...");
  try {
    const payload = await api("/api/configs/vehicle", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ mode: "raw", text: document.getElementById("config-text").value }),
    });
    state.vehiclePayload = payload;
    acceptCleanVehiclePayload({ definitionState: "pending" });
    await refreshStatus();
    state.vehicleLibrary = await api("/api/vehicles");
    await refreshSavedResults();
    await refreshResultSources();
    await refreshProcessingWorkflows();
    await refreshVehicleDiagnostics(state.vehiclePayload?.data || {});
    renderSetup();
    setSaveStatus("Saved raw vehicle");
  } catch (error) {
    setSaveStatus(error.message || "Could not save raw vehicle");
    renderRailActions();
  }
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
  await refreshStatus();
  state.vehicleLibrary = await api("/api/vehicles");
  await refreshSavedResults();
  await refreshResultSources();
  await refreshProcessingWorkflows();
  await refreshVehicleDiagnostics(state.vehiclePayload?.data || {});
  state.selectedVehicleSource = "active";
  renderSetup();
}

async function loadVehicleFromStart() {
  const sourceId = document.getElementById("start-load-picker")?.value;
  if (!sourceId || startActionBusy()) return;
  state.busyAction = "start-load";
  renderVehicleStartModal();
  try {
    await loadVehicleSourceById(sourceId);
    state.vehicleStartOpen = false;
    render();
  } catch (error) {
    setSaveStatus(error.message || "Could not load vehicle");
    renderVehicleStartModal();
  } finally {
    if (state.busyAction === "start-load") state.busyAction = null;
    renderBusyActionSurfaces();
  }
}

async function createVehicleFromStart() {
  const templateId = document.getElementById("start-template-picker")?.value;
  const name = document.getElementById("start-vehicle-name")?.value.trim() || nextVehicleName();
  if (!templateId || startActionBusy()) return;
  state.busyAction = "start-create";
  renderVehicleStartModal();
  try {
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
    await refreshStatus();
    state.vehicleLibrary = await api("/api/vehicles/save", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ name }),
    });
    await refreshStatus();
    await refreshSavedResults();
    await refreshResultSources();
    await refreshProcessingWorkflows();
    await refreshVehicleDiagnostics(state.vehiclePayload?.data || {});
    await refreshTireTemplates();
    if (state.tireTemplates?.templates?.length) {
      await loadTirTemplate(defaultTirTemplateName());
    }
    state.selectedVehicleSource = state.vehicleLibrary.saved?.id || "active";
    state.vehicleStartOpen = false;
    const saveName = document.getElementById("save-vehicle-name");
    if (saveName) saveName.value = name;
    render();
  } catch (error) {
    setSaveStatus(error.message || "Could not create vehicle");
    renderVehicleStartModal();
  } finally {
    if (state.busyAction === "start-create") state.busyAction = null;
    renderBusyActionSurfaces();
  }
}

async function importVehicleFile(file, { actionKey = "start-import" } = {}) {
  if (!file || startActionBusy()) return;
  state.busyAction = actionKey;
  renderVehicleStartModal();
  try {
    const text = await file.text();
    state.vehiclePayload = await api("/api/configs/vehicle", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ mode: "raw", text }),
    });
    acceptCleanVehiclePayload();
    await refreshStatus();
    state.vehicleLibrary = await api("/api/vehicles");
    state.vehicleTemplates = await api("/api/vehicle-templates");
    await refreshSavedResults();
    await refreshResultSources();
    await refreshProcessingWorkflows();
    await refreshVehicleDiagnostics(state.vehiclePayload?.data || {});
    await refreshTireTemplates();
    if (state.tireTemplates?.templates?.length) {
      await loadTirTemplate(defaultTirTemplateName());
    }
    state.selectedVehicleSource = "active";
    state.vehicleStartOpen = false;
    document.getElementById("save-vehicle-name").value = file.name.replace(/\.(ya?ml)$/i, "");
    render();
  } catch (error) {
    setSaveStatus(error.message || "Could not import vehicle");
    renderVehicleStartModal();
  } finally {
    if (state.busyAction === actionKey) state.busyAction = null;
    renderBusyActionSurfaces();
  }
}

async function applyVehicleTemplate(templateId) {
  if (!templateId) return;
  state.vehiclePayload = await api("/api/vehicle-template", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ template_id: templateId }),
  });
  acceptCleanVehiclePayload();
  await refreshStatus();
  state.vehicleLibrary = await api("/api/vehicles");
  await refreshSavedResults();
  await refreshResultSources();
  await refreshProcessingWorkflows();
  await refreshVehicleDiagnostics(state.vehiclePayload?.data || {});
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

async function applyStudyConfigEdits() {
  if (!state.studyConfigPayload) return null;
  let values;
  try {
    values = collectStudyConfigValues({ reportInvalid: true });
  } catch (error) {
    const status = document.getElementById("study-config-status");
    if (status) status.textContent = error.message;
    return null;
  }
  const payload = await api(`/api/configs/${encodeURIComponent(state.studyConfigPayload.id)}`, {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ mode: "patch", values }),
  });
  state.studyConfigPayload = payload;
  acceptCleanStudyConfigPayload();
  renderStudySetup(selectedStudyWorkflow());
  renderStudyDiagnostic(selectedStudyWorkflow());
  return payload;
}

async function saveStudyConfigAs() {
  const workflow = selectedStudyWorkflow();
  if (!workflow) return;
  const applied = await applyStudyConfigEdits();
  if (!applied) return;
  const name = document.getElementById("save-study-config-name")?.value || `${workflow.label} study`;
  const payload = await api("/api/sim-configs/save", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ workflow_id: workflow.id, name }),
  });
  state.studyConfigLibrary = payload.library;
  state.selectedStudyConfigSource = payload.saved?.id || state.selectedStudyConfigSource;
  renderStudySetup(workflow);
}

async function loadSelectedStudyConfig() {
  const sourceId = document.getElementById("study-config-picker")?.value || state.selectedStudyConfigSource;
  if (!sourceId) return;
  const payload = await api("/api/sim-configs/load", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ source_id: sourceId }),
  });
  state.studyConfigPayload = payload.config;
  state.studyConfigLibrary = payload.library;
  state.selectedStudyConfigSource = payload.source?.id || sourceId;
  acceptCleanStudyConfigPayload();
  renderStudies();
}

async function deleteSelectedStudyConfig() {
  const selected = (state.studyConfigLibrary?.sources || []).find((source) => source.id === state.selectedStudyConfigSource);
  if (selected?.type !== "saved") return;
  const confirmed = window.confirm(`Delete saved study config "${selected.label}"?`);
  if (!confirmed) return;
  state.studyConfigLibrary = await api("/api/sim-configs/delete", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ source_id: selected.id }),
  });
  state.selectedStudyConfigSource = state.studyConfigLibrary.sources?.[0]?.id || "";
  renderStudySetup(selectedStudyWorkflow());
}

async function saveActiveResults() {
  if (!canSaveActiveResults()) {
    state.resultsStatusMessage = saveActiveResultsDisabledReason();
    renderStudies();
    return null;
  }
  const workflow = selectedWorkflow();
  const nameInput = document.getElementById("save-results-name");
  state.savingResults = true;
  state.resultsStatusMessage = "Saving active outputs";
  renderRailActions();
  renderResultSaveControls();
  try {
    const payload = await api("/api/results/save", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        workflow_id: workflow.id,
        name: nameInput?.value || "",
      }),
    });
    state.savedResultsPayload = { results: payload.results || [] };
    state.selectedResultId = payload.saved?.id || state.savedResultsPayload.results[0]?.id || null;
    state.status = await api("/api/status");
    state.resultsStatusMessage = "Saved active results";
    if (nameInput) nameInput.value = "";
    renderStudies();
    return payload.saved || null;
  } catch (error) {
    state.resultsStatusMessage = error.message;
    renderStudies();
    return null;
  } finally {
    state.savingResults = false;
    renderRailActions();
    renderResultSaveControls();
  }
}

async function deleteSavedResult(resultId) {
  const result = savedResults().find((item) => item.id === resultId);
  if (!result || state.deletingResultId) return;
  const label = result.label || result.workflow?.label || "archived run";
  if (!window.confirm(`Delete archived run "${label}"?`)) return;
  state.deletingResultId = resultId;
  state.resultsStatusMessage = "Deleting archived run";
  renderStudies();
  try {
    const payload = await api("/api/results/delete", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ result_id: resultId }),
    });
    state.savedResultsPayload = { results: payload.results || [] };
    if (state.selectedResultId === resultId) {
      state.selectedResultId = state.savedResultsPayload.results[0]?.id || null;
    }
    state.status = await api("/api/status");
    await refreshResultSources();
    state.resultsStatusMessage = "Deleted archived run";
  } catch (error) {
    state.resultsStatusMessage = error.message;
  } finally {
    state.deletingResultId = null;
    renderRailActions();
    renderStudies();
  }
}

function defaultTirTemplateName() {
  const activeTemplate = state.vehiclePayload?.data?.front?.tire?.template
    || state.vehiclePayload?.data?.rear?.tire?.template;
  if (activeTemplate) return activeTemplate;
  return state.tireTemplates?.templates?.[0]?.id || "";
}

function setActiveTir(payload, { status = "" } = {}) {
  state.activeTir = payload;
  state.activeTirCleanText = payload?.text || "";
  state.tireStatusMessage = status;
}

function currentTirEditorText() {
  const editor = document.getElementById("tir-editor");
  return editor ? editor.value : state.activeTir?.text || "";
}

function activeTirDirty() {
  return Boolean(state.activeTir) && currentTirEditorText() !== (state.activeTirCleanText || "");
}

function renderTirActionState() {
  const saveButton = document.getElementById("save-tir-btn");
  const status = document.getElementById("tir-update-status");
  const spinner = document.getElementById("tir-update-spinner");
  const dirty = activeTirDirty();
  const busy = state.tireSaving || state.tirePayloadUpdating;

  if (saveButton) {
    saveButton.textContent = state.tireSaving
      ? "Saving..."
      : state.tirePayloadUpdating
      ? "Updating plot..."
      : "Save .tir + Update Plot";
    saveButton.disabled = !state.activeTir || !dirty || busy;
    saveButton.title = dirty
      ? "Save the edited .tir file and update the tire plot"
      : "Edit a tire parameter before saving";
  }
  if (spinner) spinner.hidden = !busy;
  if (status) {
    status.textContent = state.tireSaving
      ? "Saving .tir"
      : state.tirePayloadUpdating
      ? "Updating plot"
      : state.tireStatusMessage
        || (dirty ? "Unsaved tire edits" : state.activeTir ? "Saved" : "No .tir loaded");
  }
}

async function loadTirTemplate(name) {
  const template = name || defaultTirTemplateName();
  if (!template) return;
  setActiveTir(await api(`/api/tires/template?name=${encodeURIComponent(template)}`));
  renderTirEditorContent();
}

async function saveActiveTirTemplate() {
  if (!state.activeTir || !activeTirDirty() || state.tireSaving || state.tirePayloadUpdating) return;
  const name = document.getElementById("tir-template-picker")?.value || state.activeTir?.id || defaultTirTemplateName();
  const text = document.getElementById("tir-editor")?.value ?? state.activeTir?.text ?? "";
  state.tireSaving = true;
  state.tireStatusMessage = "";
  renderTirActionState();
  try {
    setActiveTir(await api("/api/tires/template", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ name, text }),
    }));
    await refreshTireTemplates();
    await refreshTirePayload(currentVehicleFormData(), { showBusy: true });
    state.tireStatusMessage = "Saved and updated plot";
    renderTirEditorContent();
    drawVehicleFromForm();
  } catch (error) {
    state.tireStatusMessage = error.message;
    renderTirActionState();
  } finally {
    state.tireSaving = false;
    renderTirActionState();
  }
}

async function importTirFile(file) {
  if (!file) return;
  const text = await file.text();
  state.tireSaving = true;
  state.tireStatusMessage = "";
  renderTirActionState();
  try {
    setActiveTir(await api("/api/tires/import", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ name: file.name, text }),
    }), { status: "Imported and updated plot" });
    await refreshTireTemplates();
    await refreshTirePayload(currentVehicleFormData(), { showBusy: true });
    renderTirEditorContent();
    drawVehicleFromForm();
  } catch (error) {
    state.tireStatusMessage = error.message;
    renderTirActionState();
  } finally {
    state.tireSaving = false;
    renderTirActionState();
  }
}

function syncActiveTirText(value) {
  if (!state.activeTir) return;
  state.activeTir = { ...state.activeTir, text: value };
  state.tireStatusMessage = "";
  renderTirActionState();
}

function renderTirEditorContent() {
  const picker = document.getElementById("tir-template-picker");
  const editor = document.getElementById("tir-editor");
  const meta = document.getElementById("tir-editor-meta");
  if (!picker || !meta) return;
  const templates = state.tireTemplates?.templates || [];
  picker.innerHTML = templates.map((template) => `
    <option value="${escapeHtml(template.id)}"${template.id === state.activeTir?.id ? " selected" : ""}>${escapeHtml(template.label)}</option>
  `).join("");
  if (state.activeTir && !templates.some((template) => template.id === state.activeTir.id)) {
    picker.innerHTML = `<option value="${escapeHtml(state.activeTir.id)}" selected>${escapeHtml(state.activeTir.label)}</option>${picker.innerHTML}`;
  }
  if (editor) editor.value = state.activeTir?.text || "";
  const metadata = state.activeTir?.metadata || {};
  meta.textContent = state.activeTir
    ? `${state.activeTir.path} | FNOMIN ${formatNumber(metadata.fznom_n)} N | R0 ${formatNumber(metadata.unloaded_radius_m)} m`
    : "No .tir template loaded";
  renderTirActionState();
}

function wireTireTabs() {
  document.querySelectorAll("[data-tire-tab]").forEach((button) => {
    button.addEventListener("click", () => {
      state.activeTireTab = button.dataset.tireTab || "setup";
      renderVehicleEditor();
      drawVehicleFromForm();
    });
  });
}

function wireTireAssignments() {
  document.querySelectorAll("[data-tire-assignment]").forEach((select) => {
    select.addEventListener("change", () => {
      applyTirTemplateToSide(select.dataset.tireAssignment, select.value);
    });
  });
}

function wireTireLoadControls() {
  const fzSlider = document.getElementById("tire-combined-fz-slider");
  const fzValue = document.getElementById("tire-combined-fz-value");
  fzSlider?.addEventListener("input", () => {
    state.tireCombinedFzN = Number(fzSlider.value);
    if (fzValue) fzValue.textContent = `${formatNumber(currentTireCombinedFz())} N`;
    drawVehicleFromForm();
  });
  const camberSlider = document.getElementById("tire-load-camber-slider");
  const camberValue = document.getElementById("tire-load-camber-value");
  camberSlider?.addEventListener("input", () => {
    state.tireLoadCamberDeg = Number(camberSlider.value);
    if (camberValue) camberValue.textContent = `${formatSignedNumber(currentTireLoadCamberDeg())} deg`;
    drawVehicleFromForm();
  });
}

function applyTirTemplateToSide(side, name) {
  if (!["front", "rear"].includes(side) || !name) return;
  pushUndoSnapshot(snapshotVehicleState("tire-template"));
  let updated = false;
  document.querySelectorAll("#config-form [data-config-path]").forEach((input) => {
    const path = JSON.parse(input.dataset.configPath);
    if (path.join(".") === `${side}.tire.template`) {
      input.value = name;
      updated = true;
    }
  });
  if (!updated && state.vehiclePayload?.data) {
    state.vehiclePayload.data[side] ||= {};
    state.vehiclePayload.data[side].tire ||= {};
    state.vehiclePayload.data[side].tire.template = name;
  }
  loadTirTemplate(name);
  markVehicleDirty();
  queueTirePayloadRefresh();
  renderVehicleEditor();
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
  document.getElementById("tir-editor")?.addEventListener("input", (event) => {
    syncActiveTirText(event.target.value);
  });
}

function wireTirParameterFields() {
  document.querySelectorAll("[data-tir-param]").forEach((input) => {
    input.addEventListener("input", () => {
      updateActiveTirParameter(input.dataset.tirParam, input.value);
    });
  });
}

function updateActiveTirParameter(key, value) {
  if (!state.activeTir || !key) return;
  const parsed = parseTirParameterText(state.activeTir.text || "");
  const param = parsed.params.get(String(key).toUpperCase());
  if (!param) return;
  const line = parsed.lines[param.lineIndex] || "";
  parsed.lines[param.lineIndex] = line.replace(
    /^(\s*[A-Za-z][A-Za-z0-9_]*\s*=\s*)([^$!#;]*)(.*)$/,
    (_match, prefix, _oldValue, suffix) => `${prefix}${value}${suffix}`,
  );
  state.activeTir = { ...state.activeTir, text: parsed.lines.join("\n") };
  const editor = document.getElementById("tir-editor");
  if (editor) editor.value = state.activeTir.text;
  state.tireStatusMessage = "";
  renderTirActionState();
}

function openModelicaToolchain() {
  state.toolchainModalOpen = true;
  state.toolchainInputsDirty = false;
  state.toolchainStatusMessage = "";
  renderToolchainModal();
}

function closeModelicaToolchain() {
  state.toolchainModalOpen = false;
  state.toolchainStatusMessage = "";
  renderToolchainModal();
}

function openmodelicaToolchain() {
  return state.status?.external_toolchain || {};
}

function toolchainSourceLabel(source) {
  if (!source) return "auto";
  if (source === "PATH") return "PATH";
  if (source === "saved") return "saved";
  if (source === "default") return "default";
  if (source === "omc") return "inferred";
  if (source === "omc-default") return "omc default";
  if (source.startsWith("env:")) return source.slice(4);
  return source.replaceAll("-", " ");
}

function toolchainPathLabel(path, source, fallback) {
  if (!path) return fallback;
  return `${path} (${toolchainSourceLabel(source)})`;
}

function existingToolchainCandidates(items = [], current = "") {
  const seen = new Set();
  return items
    .filter((item) => item?.exists && item.path && item.path !== current)
    .filter((item) => {
      if (seen.has(item.path)) return false;
      seen.add(item.path);
      return true;
    })
    .slice(0, 6);
}

function fillToolchainInputsFromStatus() {
  const toolchain = openmodelicaToolchain();
  const settings = toolchain.settings || {};
  const omcInput = document.getElementById("toolchain-omc-input");
  const libraryInput = document.getElementById("toolchain-library-input");
  if (omcInput) {
    omcInput.value = settings.omc_path || "";
    omcInput.placeholder = toolchain.omc || "Auto-detect omc";
  }
  if (libraryInput) {
    libraryInput.value = settings.library_path || "";
    libraryInput.placeholder = toolchain.openmodelica_library || "Use omc defaults";
  }
}

function renderToolchainCandidates(toolchain) {
  const container = document.getElementById("toolchain-candidates");
  if (!container) return;
  const omcCandidates = existingToolchainCandidates(toolchain.omc_candidates, toolchain.settings?.omc_path || toolchain.omc);
  const libraryCandidates = existingToolchainCandidates(
    toolchain.library_candidates,
    toolchain.settings?.library_path || toolchain.openmodelica_library,
  );
  const buttons = [
    ...omcCandidates.map((item) => ({ field: "toolchain-omc-input", label: `omc: ${item.path}`, path: item.path })),
    ...libraryCandidates.map((item) => ({ field: "toolchain-library-input", label: `lib: ${item.path}`, path: item.path })),
  ];
  container.innerHTML = buttons.map((button) => `
    <button class="ghost-button" type="button" data-toolchain-field="${escapeHtml(button.field)}" data-toolchain-path="${escapeHtml(button.path)}" title="${escapeHtml(button.path)}">${escapeHtml(button.label)}</button>
  `).join("");
  container.querySelectorAll("[data-toolchain-field]").forEach((button) => {
    button.addEventListener("click", () => {
      const input = document.getElementById(button.dataset.toolchainField);
      if (!input) return;
      input.value = button.dataset.toolchainPath || "";
      state.toolchainInputsDirty = true;
    });
  });
}

function renderToolchainModal() {
  const modal = document.getElementById("toolchain-modal");
  if (!modal) return;
  modal.hidden = !state.toolchainModalOpen;
  if (!state.toolchainModalOpen) return;

  const toolchain = openmodelicaToolchain();
  const subtitle = document.getElementById("toolchain-modal-subtitle");
  const activeOmc = document.getElementById("toolchain-active-omc");
  const activeLibrary = document.getElementById("toolchain-active-library");
  const saveButton = document.getElementById("toolchain-save-btn");
  const resetButton = document.getElementById("toolchain-reset-btn");
  const status = document.getElementById("toolchain-status");

  if (subtitle) subtitle.textContent = toolchain.reason || "";
  if (activeOmc) {
    activeOmc.textContent = toolchainPathLabel(toolchain.omc, toolchain.omc_source, "Not found");
  }
  if (activeLibrary) {
    activeLibrary.textContent = toolchainPathLabel(
      toolchain.openmodelica_library,
      toolchain.openmodelica_library_source,
      "omc default",
    );
  }
  if (!state.toolchainInputsDirty) fillToolchainInputsFromStatus();
  renderToolchainCandidates(toolchain);
  if (saveButton) saveButton.disabled = state.toolchainSaving;
  if (resetButton) resetButton.disabled = state.toolchainSaving;
  if (status) status.textContent = state.toolchainSaving ? "Saving." : state.toolchainStatusMessage;
}

async function saveOpenModelicaToolchain() {
  const payload = {
    omc_path: document.getElementById("toolchain-omc-input")?.value || "",
    library_path: document.getElementById("toolchain-library-input")?.value || "",
  };
  state.toolchainSaving = true;
  state.toolchainStatusMessage = "";
  renderToolchainModal();
  try {
    state.status.external_toolchain = await api("/api/toolchain/openmodelica", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(payload),
    });
    state.toolchainInputsDirty = false;
    state.toolchainStatusMessage = "Saved.";
    await refreshStatus();
  } catch (error) {
    state.toolchainStatusMessage = error.message;
  } finally {
    state.toolchainSaving = false;
    render();
  }
}

async function resetOpenModelicaToolchain() {
  state.toolchainSaving = true;
  state.toolchainStatusMessage = "";
  renderToolchainModal();
  try {
    state.status.external_toolchain = await api("/api/toolchain/openmodelica", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ reset: true }),
    });
    state.toolchainInputsDirty = false;
    state.toolchainStatusMessage = "Auto detection restored.";
    await refreshStatus();
  } catch (error) {
    state.toolchainStatusMessage = error.message;
  } finally {
    state.toolchainSaving = false;
    render();
  }
}

function renderStandard() {
  if (canUseStandardSim()) ensureSelectedSimConfigLoaded();
  const workflow = canUseStandardSim() ? selectedWorkflow() : null;
  document.getElementById("standard-context").textContent =
    `${activeVehicleName()} | ${vehicleWorkspaceStatusLabel()} | ${workflow?.label || simulationLockedMessage()}`;
  syncSimTabs();
  renderWorkflows();
  renderSimSetup(workflow);
  renderJobs();
  renderSimulationModal(workflow);
}

function syncSimTabs() {
  if (!["setup", "jobs"].includes(state.activeSimTab)) state.activeSimTab = "setup";
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
  if (!canUseStandardSim()) {
    grid.innerHTML = `<div class="empty-state">${escapeHtml(simulationLockedMessage())}</div>`;
    return;
  }
  grid.innerHTML = workflows.map(workflowCard).join("");
  grid.querySelectorAll("[data-workflow]").forEach((card) => {
    card.addEventListener("click", async () => {
      await selectStandardWorkflow(card.dataset.workflow);
    });
  });
  grid.querySelectorAll("[data-configure-workflow]").forEach((button) => {
    button.addEventListener("click", async (event) => {
      event.stopPropagation();
      await configureSimulationWorkflow(button.dataset.configureWorkflow);
    });
  });
  grid.querySelectorAll("[data-review-workflow]").forEach((button) => {
    button.addEventListener("click", async (event) => {
      event.stopPropagation();
      await reviewSimulationWorkflow(button.dataset.reviewWorkflow);
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

async function configureSimulationWorkflow(workflowId) {
  const workflow = standardWorkflows().find((item) => item.id === workflowId);
  if (!workflow || !canRunStandardWorkflow(workflow)) return;
  if (workflowId !== state.selectedWorkflowId) {
    await selectStandardWorkflow(workflowId);
  }
  state.activeSimTab = "setup";
  state.simModalOpen = true;
  renderStandard();
}

function closeSimulationModal() {
  state.simModalOpen = false;
  renderSimulationModal(selectedWorkflow());
}

function firstExistingWorkflowOutput(workflow) {
  return workflow?.outputs?.find((output) => output.exists) || null;
}

function savedReviewForWorkflow(workflowId) {
  const key = activeVehicleKey();
  if (!key || !vehicleDefinitionCurrent()) return null;
  return savedResults().find((result) => result.workflow?.id === workflowId && result.vehicle_key === key) || null;
}

function workflowReviewAvailable(workflow) {
  return Boolean(savedReviewForWorkflow(workflow?.id));
}

async function reviewSimulationWorkflow(workflowId) {
  const workflow = standardWorkflows().find((item) => item.id === workflowId);
  if (!workflow) return;
  state.selectedWorkflowId = workflow.id;
  await refreshSavedResults();
  const review = savedReviewForWorkflow(workflow.id);
  if (review) {
    state.selectedResultId = review.id;
    state.view = "studies";
    render();
    return;
  }
}

function renderSimulationModal(workflow = selectedWorkflow()) {
  const modal = document.getElementById("simulation-config-modal");
  if (!modal) return;
  if (!canUseStandardSim()) state.simModalOpen = false;
  modal.hidden = !state.simModalOpen;
  const title = document.getElementById("simulation-modal-title");
  const subtitle = document.getElementById("simulation-modal-subtitle");
  const meta = simWorkflowMeta(workflow);
  if (title) title.textContent = meta.title || workflow?.label || "Configure Simulation";
  if (subtitle) subtitle.textContent = state.activeSimTab === "jobs"
    ? "Run log"
    : meta.summary || workflowDescription(workflow);
  if (state.simModalOpen && workflow?.config_id && state.simConfigPayload?.id !== workflow.config_id) {
    ensureSelectedSimConfigLoaded();
  }
}

function workflowCard(workflow) {
  const runLabel = workflow.actions.length > 1 ? "Build + run" : "Run";
  const meta = simWorkflowMeta(workflow);
  const canReview = workflowReviewAvailable(workflow);
  const reviewTitle = canReview ? "Open archived simulation results" : "Run this simulation to create a local archive entry";
  const canConfigure = workflowAvailable(workflow);
  const configureTitle = canConfigure ? "Configure simulation" : workflowUnavailableMessage(workflow);
  return `
    <article class="workflow-card simulation-card ${workflow.id === state.selectedWorkflowId ? "active" : ""} ${canConfigure ? "" : "disabled"}" data-workflow="${workflow.id}">
      <div class="simulation-card-figure">
        ${simFigureHtml(workflow)}
      </div>
      <div class="simulation-card-body">
        <div class="card-head">
          <div>
            <div class="card-title">${escapeHtml(meta.title || workflow.label)}</div>
            <div class="card-meta">${escapeHtml(meta.summary || workflowDescription(workflow))}</div>
          </div>
          <span class="mini-pill">${runLabel}</span>
        </div>
        <div class="simulation-explanation">
          ${meta.explanation.map((item) => `<p>${escapeHtml(item)}</p>`).join("")}
        </div>
        <div class="simulation-detail-grid">
          ${simDetailBlock("What happens", meta.sequence)}
          ${simDetailBlock("Key parameters", meta.parameters)}
          ${simDetailBlock("Outputs", meta.outputs)}
        </div>
        <div class="card-actions">
          ${architectureStatusPill()}
          <button class="ghost-button simulation-review-button" type="button" data-review-workflow="${escapeHtml(workflow.id)}"${canReview ? "" : " disabled"} title="${escapeHtml(reviewTitle)}">Review</button>
          <button class="run-button" type="button" data-configure-workflow="${escapeHtml(workflow.id)}"${canConfigure ? "" : " disabled"} title="${escapeHtml(configureTitle)}">Configure</button>
        </div>
      </div>
    </article>
  `;
}

function architectureStatusPill() {
  if (!activeVehicleConfigReady()) {
    return `<span class="mini-pill missing" title="Save a vehicle before running simulations">No saved vehicle</span>`;
  }
  if (!vehicleDefinitionCurrent()) {
    return `<span class="mini-pill missing" title="Save Vehicle and Write to MBD before running simulations">Architecture stale</span>`;
  }
  return `<span class="mini-pill ok" title="Current architecture is saved and written to MBD">${escapeHtml(activeArchitecture())}</span>`;
}

function workflowDescription(workflow) {
  return simWorkflowMeta(workflow).summary || workflow?.config?.path || "";
}

function simDetailBlock(title, items = []) {
  return `
    <div class="simulation-detail-block">
      <h4>${escapeHtml(title)}</h4>
      <ul>
        ${items.map((item) => `<li>${escapeHtml(item)}</li>`).join("")}
      </ul>
    </div>
  `;
}

function simWorkflowMeta(workflow) {
  const fallback = {
    title: workflow?.label || "Simulation",
    summary: "Configure the run, execute it against the active vehicle definition, then inspect generated logs and outputs.",
    explanation: [
      "This workflow uses the active vehicle definition and run-specific YAML to produce a repeatable simulation case.",
    ],
    sequence: ["Load active vehicle definition", "Apply run configuration", "Execute workflow actions"],
    parameters: ["Solver and stop time", "Case-specific sweep values", "Report output paths"],
    outputs: ["Job log", "Registered reports and CSV files"],
    steps: ["Vehicle is selected", "Configure run", "Run"],
  };
  return {
    "ramp-steer": {
      title: "Ramp Steer",
      summary: "Open-loop steering ramp across speed and lateral-acceleration operating points.",
      explanation: [
        "RampSteerEval builds the full VehicleSim model, applies a prescribed handwheel ramp, and sweeps the requested velocity cases.",
        "The run is useful for checking steering response shape, lateral acceleration build-up, yaw-rate response, and whether the vehicle stays inside expected handling limits.",
      ],
      sequence: ["Build VehicleSim if needed", "Initialize the active vehicle record", "Sweep speed cases", "Apply steering ramp", "Collect report metrics"],
      parameters: ["Velocity isolines", "Handwheel ramp timing and amplitude", "Nonlinearity cutoff", "Solver tolerance and stop time"],
      outputs: ["Ramp steer PDF report", "Metrics CSV", "Job log with build and run output"],
      steps: ["Vehicle is selected", "Set speed sweep", "Build + run"],
    },
    "steady-state": {
      title: "Steady State",
      summary: "Closed-loop lateral acceleration map for settled cornering operating points.",
      explanation: [
        "SteadyStateEval asks the model to converge to target lateral-acceleration points across the configured operating range.",
        "It is the browser-side doorway into balance, understeer behavior, control demand, and tire utilization at settled conditions.",
      ],
      sequence: ["Build VehicleSim if needed", "Initialize each target condition", "Close the control loop", "Converge settled states", "Export metrics"],
      parameters: ["Target lateral-acceleration grid", "Velocity-specific Ay caps", "Convergence criteria", "Report and solver controls"],
      outputs: ["Steady-state PDF report", "Metrics CSV", "Settled-point job log"],
      steps: ["Vehicle is selected", "Set target grid", "Build + run"],
    },
    transient: {
      title: "Transient",
      summary: "Time-domain response to steering inputs such as step and sine events.",
      explanation: [
        "TransientEval runs the full vehicle forward in time with configured steering inputs and records the dynamic response.",
        "This is the place to inspect yaw-rate gain, phase, overshoot, settling, and how quickly the chassis responds after the input changes.",
      ],
      sequence: ["Build VehicleSim if needed", "Apply input schedule", "Integrate the time response", "Capture response channels", "Generate summary files"],
      parameters: ["Input type and amplitude", "Input timing/frequency", "Initial speed", "Stop time, step size, and solver"],
      outputs: ["Transient PDF report", "Metrics CSV", "Time-response job log"],
      steps: ["Vehicle is selected", "Set input cases", "Build + run"],
    },
    "four-post": {
      title: "Four Post",
      summary: "Heave, roll, and vertical-force procedures for suspension and chassis response.",
      explanation: [
        "FourPostEval builds the FourPostSim model and drives the corners with configured vertical procedures.",
        "It is focused on ride/suspension behavior rather than the full powertrain loop, so it can isolate heave, roll, spring/damper, and tire vertical-load behavior.",
      ],
      sequence: ["Build FourPostSim if needed", "Initialize corner positions", "Apply vertical actuator procedures", "Sweep heave/roll/force cases", "Collect suspension metrics"],
      parameters: ["Corner input magnitudes", "Heave and roll sweeps", "Override rates and initial conditions", "Solver and output controls"],
      outputs: ["Four-post PDF report", "Metrics CSV", "Build/run log"],
      steps: ["Vehicle is selected", "Set procedure", "Build + run"],
    },
  }[workflow?.id] || fallback;
}

function simFigureHtml(workflow) {
  const id = workflow?.id || "generic";
  if (id === "steady-state") {
    return `
      <svg viewBox="0 0 260 150" role="img" aria-label="Second-order steady-state response">
        <rect x="18" y="18" width="224" height="106" rx="6"></rect>
        <path class="axis" d="M34 104 H226 M42 116 V30"></path>
        <path class="target" d="M34 58 H226"></path>
        <path class="accent" d="M34 104 C54 104, 59 58, 76 41 S105 65, 122 57 S151 54, 168 58 S202 58, 226 58"></path>
        <path d="M34 104 H56 V58 H226"></path>
        <text x="28" y="139">time</text>
        <text x="154" y="40">settled output</text>
      </svg>
    `;
  }
  if (id === "transient") {
    return `
      <svg viewBox="0 0 260 150" role="img" aria-label="Step and sine inputs about the x-axis">
        <rect x="18" y="18" width="224" height="106" rx="6"></rect>
        <path class="axis" d="M34 72 H226 M42 116 V30"></path>
        <path d="M34 94 H64 V52 H114"></path>
        <path class="accent" d="M122 72 C132 46, 146 46, 156 72 S180 98, 190 72 S214 46, 226 72"></path>
        <text x="28" y="139">time</text>
        <text x="52" y="42">step</text>
        <text x="168" y="42">sine</text>
      </svg>
    `;
  }
  if (id === "four-post") {
    return `
      <svg viewBox="0 0 260 150" role="img" aria-label="Kinematics and compliance rig with four vertical posts">
        <rect x="42" y="42" width="176" height="62" rx="6"></rect>
        <path class="fixture" d="M54 36 H206 M54 110 H206 M70 36 V116 M190 36 V116"></path>
        <path d="M78 54 H182 M78 92 H182 M92 54 L168 92 M168 54 L92 92"></path>
        <circle cx="70" cy="42" r="11"></circle>
        <circle cx="190" cy="42" r="11"></circle>
        <circle cx="70" cy="104" r="11"></circle>
        <circle cx="190" cy="104" r="11"></circle>
        <path class="post" d="M70 18 V32 M190 18 V32 M70 114 V136 M190 114 V136"></path>
        <path class="accent" d="M60 24 H80 M180 24 H200 M60 130 H80 M180 130 H200"></path>
        <text x="24" y="139">vertical posts</text>
        <text x="153" y="28">KnC fixture</text>
      </svg>
    `;
  }
  return `
    <svg viewBox="0 0 260 150" role="img" aria-label="Ramp input">
      <rect x="18" y="18" width="224" height="106" rx="6"></rect>
      <path class="axis" d="M34 104 H226 M42 116 V30"></path>
      <path class="accent" d="M42 104 H78 L176 44 H222"></path>
      <text x="28" y="139">time</text>
      <text x="171" y="36">ramp</text>
    </svg>
  `;
}

function studyGroupMeta(groupId) {
  return STUDY_GROUPS.find((group) => group.id === groupId) || { id: groupId, label: humanizeToken(groupId || "Study") };
}

function studyDescription(workflow) {
  return {
    ggv: "Acceleration envelope and track-profile grip proxies.",
    ymd: "Beta and steer sweeps for yaw moment authority.",
    "vehicle-review": "Report-ready vehicle, envelope, and rubric coverage.",
    "standard-sens": "Modelica DOE around the standard simulation model.",
    "envelope-sens": "Fast reduced-order sensitivity sweep for envelope metrics.",
  }[workflow?.id] || workflow?.config?.path || "";
}

function studyWorkflowGuide(workflow) {
  return {
    ggv: {
      title: "GGV Envelope",
      copy: "Set the speed grid and acceleration search bounds, then generate the tire-limited acceleration envelope.",
      steps: ["Vehicle selected", "Set grid", "Run envelope"],
    },
    ymd: {
      title: "Yaw Moment Diagram",
      copy: "Set beta, handwheel, and speed grids to inspect lateral force and yaw moment authority.",
      steps: ["Vehicle selected", "Set map", "Run YMD"],
    },
    "vehicle-review": {
      title: "Vehicle Review",
      copy: "Choose report labels and whether envelope artifacts should be regenerated before assembly.",
      steps: ["Vehicle selected", "Set report", "Run review"],
    },
    "standard-sens": {
      title: "Standard Sensitivity",
      copy: "Configure the DOE sampler for the Modelica-backed standard simulation sensitivity study.",
      steps: ["Vehicle selected", "Set sampler", "Run DOE"],
    },
    "envelope-sens": {
      title: "Envelope Sensitivity",
      copy: "Configure a quick reduced-order sensitivity sweep around envelope-level controls.",
      steps: ["Vehicle selected", "Set sampler", "Run study"],
    },
  }[workflow?.id] || {
    title: workflow?.label || "Study",
    copy: "Select a study, configure the run, then execute it.",
    steps: ["Vehicle selected", "Configure", "Run"],
  };
}

function configValue(data, path, fallback = null) {
  if (!data || !path) return fallback;
  const parts = path.split(".");
  let current = data;
  for (const part of parts) {
    if (current == null || typeof current !== "object" || !(part in current)) return fallback;
    current = current[part];
  }
  return current;
}

function arrayRangeLabel(values, unit = "") {
  if (!Array.isArray(values) || !values.length) return "Not set";
  const numbers = values
    .filter((value) => value !== null && value !== undefined && value !== "")
    .map(Number)
    .filter(Number.isFinite);
  if (!numbers.length) return `${values.length} items`;
  const suffix = unit ? ` ${unit}` : "";
  if (numbers.length === 1) return `${formatNumber(numbers[0])}${suffix}`;
  const range = finiteRange(numbers);
  return `${formatNumber(range.min)} to ${formatNumber(range.max)}${suffix}`;
}

function scalarLabel(value, unit = "") {
  const numeric = Number(value);
  if (Number.isFinite(numeric)) return `${formatNumber(numeric)}${unit ? ` ${unit}` : ""}`;
  if (value === true) return "On";
  if (value === false) return "Off";
  return value == null || value === "" ? "Not set" : String(value);
}

function studyVariables(data) {
  return Array.isArray(data?.variables) ? data.variables : [];
}

function studyMetric(label, value) {
  return `
    <div class="study-metric">
      <span>${escapeHtml(label)}</span>
      <strong>${escapeHtml(value)}</strong>
    </div>
  `;
}

function studyMetrics(workflow, data) {
  if (workflow?.id === "ggv") {
    return [
      studyMetric("Speeds", arrayRangeLabel(configValue(data, "generation.speeds_mps"), "m/s")),
      studyMetric("Lat grid", scalarLabel(configValue(data, "generation.ay_points"), "pts")),
      studyMetric("Long grid", scalarLabel(configValue(data, "generation.ax_search_points"), "pts")),
    ];
  }
  if (workflow?.id === "ymd") {
    return [
      studyMetric("Speed", scalarLabel(configValue(data, "generation.speed_mps"), "m/s")),
      studyMetric("Beta", `${scalarLabel(configValue(data, "generation.beta_min_deg"), "deg")} to ${scalarLabel(configValue(data, "generation.beta_max_deg"), "deg")}`),
      studyMetric("Handwheel", `${scalarLabel(configValue(data, "generation.hwa_min_deg"), "deg")} to ${scalarLabel(configValue(data, "generation.hwa_max_deg"), "deg")}`),
    ];
  }
  if (workflow?.id === "vehicle-review") {
    return [
      studyMetric("Report", scalarLabel(configValue(data, "report.brand"))),
      studyMetric("GGV", scalarLabel(configValue(data, "generation.regenerate_ggv"))),
      studyMetric("YMD", scalarLabel(configValue(data, "generation.regenerate_ymd"))),
    ];
  }
  if (workflow?.group === "opt") {
    const variables = studyVariables(data);
    return [
      studyMetric("Variables", scalarLabel(variables.length)),
      studyMetric("Sampler", scalarLabel(configValue(data, "sampling.method"))),
      studyMetric("Intervals", scalarLabel(configValue(data, "sampling.intervals"))),
    ];
  }
  return [
    studyMetric("Config", workflow?.config?.exists ? "Ready" : "Missing"),
    studyMetric("Outputs", `${workflow?.outputs?.filter((output) => output.exists).length || 0}`),
    studyMetric("Action", workflow?.actions?.[0]?.label || "Run"),
  ];
}

function studyDiagnosticHtml(workflow, data) {
  if (!workflow) return `<div class="empty-state">Select a study to inspect its setup.</div>`;
  const group = studyGroupMeta(workflow.group);
  return `
    <div class="study-diagnostic-summary">
      <div>
        <span class="context-label">${escapeHtml(group.label)}</span>
        <h3>${escapeHtml(workflow.label)}</h3>
        <p>${escapeHtml(studyDescription(workflow))}</p>
      </div>
      <div class="study-metrics">
        ${studyMetrics(workflow, data).join("")}
      </div>
    </div>
    <div class="study-figure-shell">
      ${studyFigureHtml(workflow, data)}
    </div>
  `;
}

function studyFigureHtml(workflow, data) {
  if (workflow?.id === "ggv") return ggvFigureHtml(data);
  if (workflow?.id === "ymd") return ymdFigureHtml(data);
  if (workflow?.id === "vehicle-review") return reviewFigureHtml(data);
  if (workflow?.group === "opt") return optFigureHtml(data);
  return `<div class="study-figure-empty">Study diagnostic</div>`;
}

function ggvFigureHtml(data) {
  const ay = Number(configValue(data, "generation.ay_max_g", 0));
  const axMin = Number(configValue(data, "generation.ax_search_min_g", 0));
  const axMax = Number(configValue(data, "generation.ax_search_max_g", 0));
  return `
    <div class="study-figure ggv-figure">
      <div class="ggv-axis ggv-axis-x"></div>
      <div class="ggv-axis ggv-axis-y"></div>
      <div class="ggv-envelope"></div>
      <span class="ggv-label top">Ay ${escapeHtml(scalarLabel(ay, "g"))}</span>
      <span class="ggv-label left">${escapeHtml(scalarLabel(axMin, "g"))}</span>
      <span class="ggv-label right">${escapeHtml(scalarLabel(axMax, "g"))}</span>
    </div>
  `;
}

function ymdFigureHtml(data) {
  const cells = Array.from({ length: 54 }, (_, index) => {
    const heat = Math.abs((index % 9) - 4) + Math.abs(Math.floor(index / 9) - 2);
    return `<span class="heat-${Math.max(0, Math.min(4, heat))}"></span>`;
  }).join("");
  return `
    <div class="study-figure ymd-figure">
      <div class="ymd-grid">${cells}</div>
      <div class="ymd-zero-line"></div>
      <span class="ymd-label beta">Beta ${escapeHtml(arrayRangeLabel([configValue(data, "generation.beta_min_deg"), configValue(data, "generation.beta_max_deg")], "deg"))}</span>
      <span class="ymd-label steer">Handwheel ${escapeHtml(arrayRangeLabel([configValue(data, "generation.hwa_min_deg"), configValue(data, "generation.hwa_max_deg")], "deg"))}</span>
    </div>
  `;
}

function reviewFigureHtml(data) {
  const items = [
    ["GGV", configValue(data, "generation.regenerate_ggv")],
    ["YMD", configValue(data, "generation.regenerate_ymd")],
    ["PDF", configValue(data, "output.pdf_filename")],
    ["Metrics", configValue(data, "output.metrics_csv_filename")],
  ];
  return `
    <div class="study-figure review-figure">
      ${items.map(([label, value]) => `
        <div class="review-row">
          <span>${escapeHtml(label)}</span>
          <strong>${escapeHtml(scalarLabel(value))}</strong>
        </div>
      `).join("")}
    </div>
  `;
}

function optFigureHtml(data) {
  const variables = studyVariables(data).slice(0, 6);
  if (!variables.length) {
    return `<div class="study-figure-empty">No variables listed in this study config.</div>`;
  }
  return `
    <div class="study-figure opt-figure">
      ${variables.map((variable, index) => {
        const range = Array.isArray(variable.range) ? variable.range : variable.values;
        return `
          <div class="opt-range-row">
            <span>${escapeHtml(variable.label || variable.path || `Variable ${index + 1}`)}</span>
            <div class="opt-range-track"><i style="width: ${Math.max(18, 96 - index * 8)}%"></i></div>
            <strong>${escapeHtml(arrayRangeLabel(range))}</strong>
          </div>
        `;
      }).join("")}
    </div>
  `;
}

function renderStudies() {
  state.activeStudyTab = "saved";
  renderResultSaveControls();
  renderSavedResultCatalog();
  renderSavedResultSummary();
  renderSavedResultOutputs();
}

function renderResultSaveControls() {
  const context = document.getElementById("studies-context");
  if (context) {
    const status = state.resultsStatusMessage ? ` | ${state.resultsStatusMessage}` : "";
    const count = savedResults().length;
    const packageLabel = count === 1 ? "1 local run" : `${count} local runs`;
    context.textContent = `Local simulation archive | ${packageLabel}${status}`;
  }
  const saveButton = document.getElementById("run-study-btn");
  if (saveButton) {
    saveButton.textContent = state.savingResults ? "Saving..." : "Save Review Package";
    saveButton.disabled = !canSaveActiveResults();
    saveButton.title = saveActiveResultsDisabledReason();
  }
  const nameInput = document.getElementById("save-results-name");
  const workflow = selectedWorkflow();
  if (nameInput && workflow) {
    nameInput.placeholder = `Save ${workflow.label} results as`;
  }
}

function renderResultSourceCatalog() {
  const grid = document.getElementById("result-source-grid");
  if (!grid) return;
  const sources = resultSources();
  if (!activeVehicleConfigReady()) {
    grid.innerHTML = `<div class="empty-state">Save this vehicle config before viewing result sources.</div>`;
    return;
  }
  if (!sources.length) {
    grid.innerHTML = `<div class="empty-state">No CSV result sources saved for this vehicle config.</div>`;
    return;
  }
  grid.innerHTML = sources.map(resultSourceCard).join("");
  grid.querySelectorAll("[data-result-source]").forEach((card) => {
    card.addEventListener("click", async () => {
      await selectResultSource(card.dataset.resultSource);
    });
  });
}

function resultSourceCard(source) {
  const active = source.path === state.selectedResultSourcePath;
  return `
    <article class="workflow-card result-source-card ${active ? "active" : ""}" data-result-source="${escapeHtml(source.path)}">
      <div class="card-head">
        <div class="card-title">${escapeHtml(source.label || source.path)}</div>
        <span class="mini-pill">${escapeHtml(source.group || "Results")}</span>
      </div>
      <div class="card-meta">${escapeHtml(source.path)}</div>
      <div class="signal-row">
        <span class="mini-pill ok">${formatNumber(source.row_count || 0)} rows</span>
        <span class="mini-pill">${(source.numeric_columns || []).length}/${(source.columns || []).length} numeric</span>
      </div>
    </article>
  `;
}

async function selectResultSource(path) {
  if (!path) return;
  state.selectedResultSourcePath = path;
  state.resultSourceDetail = null;
  state.resultPlotPayload = null;
  state.resultPlotStatus = "loading";
  state.resultPlotMessage = "";
  state.resultSelectedSignals = [];
  renderStudies();
  await loadResultSource(path);
}

async function loadResultSource(path = state.selectedResultSourcePath) {
  if (!path) return;
  state.resultPlotStatus = "loading";
  renderResultExplorer();
  try {
    const detail = await api(`/api/results/source?path=${encodeURIComponent(path)}`);
    if (state.selectedResultSourcePath !== path) return;
    state.resultSourceDetail = detail;
    state.resultXAxis = defaultResultXAxis(detail);
    state.resultSelectedSignals = defaultResultSignals(detail);
    state.resultPlotStatus = "idle";
    renderStudies();
    await refreshResultPlot();
  } catch (error) {
    state.resultPlotStatus = "error";
    state.resultPlotMessage = error.message;
    renderResultExplorer();
  }
}

function defaultResultXAxis(detail) {
  const candidates = detail?.x_candidates || [];
  return candidates[0] || "__index__";
}

function defaultResultSignals(detail) {
  const xAxis = state.resultXAxis || defaultResultXAxis(detail);
  const preferred = ["value", "accY", "ay_mps2", "ax_accel_mps2", "roll", "yawVel", "speed_mps"];
  const numeric = (detail?.numeric_columns || []).filter((column) => column !== xAxis);
  const ordered = [
    ...preferred.filter((column) => numeric.includes(column)),
    ...numeric.filter((column) => !preferred.includes(column)),
  ];
  return ordered.slice(0, Math.min(3, ordered.length));
}

function renderResultExplorer() {
  const source = selectedResultSource();
  if (!source) {
    renderResultSourceDiagnostic(null);
    renderResultControls(null);
    renderResultPlotCanvas();
    return;
  }
  const detail = state.resultSourceDetail?.path === source.path ? state.resultSourceDetail : null;
  if (!detail && state.resultPlotStatus !== "loading") {
    loadResultSource(source.path);
  }
  renderResultSourceDiagnostic(detail || source);
  renderResultControls(detail);
  renderResultPlotCanvas();
}

function renderResultSourceDiagnostic(source) {
  const target = document.getElementById("result-source-diagnostic");
  if (!target) return;
  if (!source) {
    target.innerHTML = `<div class="empty-state">No result source selected.</div>`;
    return;
  }
  target.innerHTML = `
    <div class="study-diagnostic-summary">
      <div>
        <span class="context-label">${escapeHtml(source.group || "Results")}</span>
        <h3>${escapeHtml(source.label || source.path)}</h3>
        <p>${escapeHtml(source.path || "")}</p>
      </div>
      <div class="study-metrics">
        ${studyMetric("Rows", formatNumber(source.row_count || 0))}
        ${studyMetric("Signals", String((source.numeric_columns || []).length))}
        ${studyMetric("Size", fmtBytes(source.size || 0))}
      </div>
    </div>
    <div class="study-figure-shell">
      <div class="study-figure result-figure">
        ${(source.numeric_columns || []).slice(0, 10).map((column) => `
          <div class="review-row">
            <span>${escapeHtml(column)}</span>
            <strong>${column === state.resultXAxis ? "x axis" : state.resultSelectedSignals.includes(column) ? "selected" : "available"}</strong>
          </div>
        `).join("") || `<div class="study-figure-empty">No numeric signals found.</div>`}
      </div>
    </div>
  `;
}

function renderResultControls(detail) {
  const xSelect = document.getElementById("result-x-axis");
  const search = document.getElementById("result-signal-search");
  const list = document.getElementById("result-signal-list");
  const selected = document.getElementById("result-selected-signals");
  if (!xSelect || !search || !list || !selected) return;
  if (!detail) {
    xSelect.innerHTML = `<option value="__index__">Row index</option>`;
    search.value = state.resultSignalSearch || "";
    list.innerHTML = `<div class="empty-state">Loading signals.</div>`;
    selected.innerHTML = "";
    return;
  }
  const numeric = detail.numeric_columns || [];
  if (state.resultXAxis !== "__index__" && !numeric.includes(state.resultXAxis)) {
    state.resultXAxis = defaultResultXAxis(detail);
  }
  state.resultSelectedSignals = state.resultSelectedSignals.filter((signal) => numeric.includes(signal) && signal !== state.resultXAxis);
  if (!state.resultSelectedSignals.length) state.resultSelectedSignals = defaultResultSignals(detail);
  xSelect.innerHTML = [
    `<option value="__index__"${state.resultXAxis === "__index__" ? " selected" : ""}>Row index</option>`,
    ...numeric.map((column) => `<option value="${escapeHtml(column)}"${column === state.resultXAxis ? " selected" : ""}>${escapeHtml(column)}</option>`),
  ].join("");
  xSelect.onchange = async (event) => {
    state.resultXAxis = event.target.value;
    state.resultSelectedSignals = state.resultSelectedSignals.filter((signal) => signal !== state.resultXAxis);
    if (!state.resultSelectedSignals.length) state.resultSelectedSignals = defaultResultSignals(detail);
    renderResultControls(detail);
    renderResultSourceDiagnostic(detail);
    await refreshResultPlot();
  };
  search.value = state.resultSignalSearch || "";
  search.oninput = (event) => {
    state.resultSignalSearch = event.target.value;
    renderResultControls(detail);
  };
  const needle = state.resultSignalSearch.trim().toLowerCase();
  const signals = numeric
    .filter((column) => column !== state.resultXAxis)
    .filter((column) => !needle || column.toLowerCase().includes(needle));
  list.innerHTML = signals.length
    ? signals.map((column) => `
      <label class="result-signal-option">
        <input type="checkbox" value="${escapeHtml(column)}"${state.resultSelectedSignals.includes(column) ? " checked" : ""}>
        <span>${escapeHtml(column)}</span>
      </label>
    `).join("")
    : `<div class="empty-state">No matching signals.</div>`;
  list.querySelectorAll("input[type='checkbox']").forEach((input) => {
    input.addEventListener("change", async () => {
      const signal = input.value;
      if (input.checked) state.resultSelectedSignals = [...new Set([...state.resultSelectedSignals, signal])].slice(0, 8);
      else state.resultSelectedSignals = state.resultSelectedSignals.filter((item) => item !== signal);
      renderResultControls(detail);
      renderResultSourceDiagnostic(detail);
      await refreshResultPlot();
    });
  });
  selected.innerHTML = state.resultSelectedSignals.length
    ? state.resultSelectedSignals.map((signal) => `<span class="mini-pill ok">${escapeHtml(signal)}</span>`).join("")
    : `<span class="mini-pill missing">No signals</span>`;
}

async function refreshResultPlot() {
  const detail = state.resultSourceDetail;
  if (!detail?.path || !state.resultSelectedSignals.length) {
    state.resultPlotPayload = null;
    renderResultPlotCanvas();
    return;
  }
  state.resultPlotStatus = "loading";
  state.resultPlotMessage = "";
  renderResultPlotCanvas();
  try {
    state.resultPlotPayload = await api("/api/results/series", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        path: detail.path,
        x_axis: state.resultXAxis,
        signals: state.resultSelectedSignals,
        max_points: 2200,
      }),
    });
    state.resultPlotStatus = "ready";
  } catch (error) {
    state.resultPlotStatus = "error";
    state.resultPlotMessage = error.message;
    state.resultPlotPayload = null;
  }
  renderResultPlotCanvas();
}

function renderResultPlotCanvas() {
  requestAnimationFrame(drawResultPlotCanvas);
}

function drawResultPlotCanvas() {
  const canvas = document.getElementById("result-plot-canvas");
  if (!canvas) return;
  const rect = canvas.getBoundingClientRect();
  const width = Math.max(360, Math.floor(rect.width || 760));
  const height = Math.max(260, Math.floor(rect.height || 420));
  const dpr = window.devicePixelRatio || 1;
  canvas.width = Math.floor(width * dpr);
  canvas.height = Math.floor(height * dpr);
  const ctx = canvas.getContext("2d");
  const palette = canvasPalette();
  ctx.setTransform(dpr, 0, 0, dpr, 0, 0);
  ctx.clearRect(0, 0, width, height);
  ctx.fillStyle = palette.surface;
  ctx.fillRect(0, 0, width, height);
  const title = document.getElementById("result-plot-title");
  const subtitle = document.getElementById("result-plot-subtitle");
  const payload = state.resultPlotPayload;
  if (title) title.textContent = selectedResultSource()?.label || "Signal Plot";
  if (subtitle) {
    const detail = state.resultSourceDetail || selectedResultSource();
    subtitle.textContent = detail ? `${detail.path} | x: ${state.resultXAxis === "__index__" ? "row index" : state.resultXAxis}` : "";
  }
  if (state.resultPlotStatus === "loading") {
    drawCanvasText(ctx, "Loading result data", width / 2, height / 2, { align: "center", color: palette.muted, weight: 760 });
    return;
  }
  if (state.resultPlotStatus === "error") {
    drawCanvasText(ctx, state.resultPlotMessage || "Could not load result data", width / 2, height / 2, {
      align: "center",
      color: palette.red,
      weight: 760,
    });
    return;
  }
  if (!payload?.x?.length || !payload.series?.length) {
    drawCanvasText(ctx, "Select a result source and signals to plot", width / 2, height / 2, {
      align: "center",
      color: palette.muted,
      weight: 760,
    });
    return;
  }
  const plot = { x: 58, y: 28, width: width - 78, height: height - 76 };
  const xDomain = plotDomain(payload.x, { padFraction: 0.02 });
  const yValues = payload.series.flatMap((series) => series.values).filter((value) => value !== null && value !== undefined);
  const yDomain = plotDomain(yValues, { padFraction: 0.1 });
  drawPlotGrid(ctx, { plot, xDomain, yDomain });
  const toX = (value) => plot.x + ((value - xDomain[0]) / Math.max(1e-9, xDomain[1] - xDomain[0])) * plot.width;
  const toY = (value) => plot.y + plot.height - ((value - yDomain[0]) / Math.max(1e-9, yDomain[1] - yDomain[0])) * plot.height;
  const colors = [palette.blue, palette.green, palette.amber, palette.red, palette.tireFront, palette.tireRear, "#7c3aed", "#0f766e"];
  payload.series.forEach((series, seriesIndex) => {
    ctx.save();
    ctx.strokeStyle = colors[seriesIndex % colors.length];
    ctx.lineWidth = seriesIndex === 0 ? 2.1 : 1.7;
    ctx.beginPath();
    let drawing = false;
    series.values.forEach((value, index) => {
      const x = Number(payload.x[index]);
      const y = Number(value);
      if (!Number.isFinite(x) || !Number.isFinite(y)) {
        drawing = false;
        return;
      }
      if (!drawing) {
        ctx.moveTo(toX(x), toY(y));
        drawing = true;
      } else {
        ctx.lineTo(toX(x), toY(y));
      }
    });
    ctx.stroke();
    ctx.restore();
  });
  ctx.save();
  ctx.fillStyle = palette.surface;
  ctx.fillRect(plot.x + 8, plot.y + 8, Math.min(plot.width - 16, 310), Math.min(26 + payload.series.length * 18, plot.height - 16));
  payload.series.slice(0, 8).forEach((series, index) => {
    const y = plot.y + 24 + index * 18;
    ctx.strokeStyle = colors[index % colors.length];
    ctx.lineWidth = 3;
    ctx.beginPath();
    ctx.moveTo(plot.x + 18, y);
    ctx.lineTo(plot.x + 40, y);
    ctx.stroke();
    drawCanvasText(ctx, series.signal, plot.x + 48, y + 1, { size: 11, weight: 760, color: palette.ink });
  });
  ctx.restore();
  drawCanvasText(ctx, state.resultXAxis === "__index__" ? "row index" : state.resultXAxis, plot.x + plot.width / 2, height - 18, {
    align: "center",
    size: 11,
    weight: 760,
    color: palette.muted,
  });
}

function renderSavedResultCatalog() {
  const grid = document.getElementById("saved-result-list");
  if (!grid) return;
  const results = savedResults();
  if (!results.length) {
    grid.innerHTML = `<div class="empty-state">No archived simulation runs yet. Run a simulation to save the report, metrics, and signal archive locally.</div>`;
    return;
  }
  grid.innerHTML = results.map(resultArchiveCard).join("");
  grid.querySelectorAll("[data-result-id]").forEach((card) => {
    card.addEventListener("click", () => {
      state.selectedResultId = card.dataset.resultId;
      state.activeStudyTab = "saved";
      renderStudies();
    });
  });
  grid.querySelectorAll("[data-delete-result]").forEach((button) => {
    button.addEventListener("click", async (event) => {
      event.stopPropagation();
      await deleteSavedResult(button.dataset.deleteResult);
    });
  });
}

function resultArchiveCard(result) {
  const fileCount = result.files?.filter((file) => file.exists).length || 0;
  const workflow = result.workflow?.label || "Simulation";
  const runCount = Number(result.analysis?.run_count || result.run_count || 0);
  const deleting = state.deletingResultId === result.id;
  return `
    <article class="workflow-card study-card result-card ${result.id === state.selectedResultId ? "active" : ""}" data-result-id="${escapeHtml(result.id)}">
      <div class="card-head">
        <div class="card-title">${escapeHtml(result.label || workflow)}</div>
        <div class="archive-card-actions">
          <span class="mini-pill">${escapeHtml(workflow)}</span>
          <button class="ghost-button danger-button archive-delete-button" type="button" data-delete-result="${escapeHtml(result.id)}"${deleting ? " disabled" : ""}>${deleting ? "Deleting" : "Delete"}</button>
        </div>
      </div>
      <div class="card-meta">${escapeHtml(result.created_label || "")}</div>
      <div class="signal-row">
        <span class="mini-pill ok">${fileCount} files</span>
        ${runCount ? `<span class="mini-pill ok">${runCount} runs</span>` : ""}
        <span class="mini-pill">${escapeHtml(result.vehicle_name || activeVehicleName())}</span>
      </div>
    </article>
  `;
}

function renderSavedResultSummary() {
  const panel = document.getElementById("result-summary-panel");
  const result = selectedSavedResult();
  if (!panel) return;
  if (!result) {
    panel.innerHTML = `<div class="empty-state">Run a simulation, then return here to download the report, metrics, and per-run signal archive.</div>`;
    return;
  }
  const architecture = result.architecture || {};
  const runCount = Number(result.analysis?.run_count || result.run_count || 0);
  const deleting = state.deletingResultId === result.id;
  panel.innerHTML = `
    <div class="result-summary-grid">
      ${resultSummaryItem("Workflow", result.workflow?.label || "Simulation")}
      ${resultSummaryItem("Vehicle", result.vehicle_name || "Active vehicle")}
      ${resultSummaryItem("Architecture", `${architecture.front || "front"} / ${architecture.rear || "rear"}`)}
      ${runCount ? resultSummaryItem("Runs", String(runCount)) : ""}
      ${resultSummaryItem("Saved", result.created_label || "")}
      ${result.vehicle_snapshot ? resultSummaryLink("Vehicle YAML", result.vehicle_snapshot) : ""}
      ${result.config_snapshot ? resultSummaryLink("Run Config", result.config_snapshot) : ""}
    </div>
    <div class="result-summary-actions">
      <button class="ghost-button danger-button" type="button" data-delete-selected-result="${escapeHtml(result.id)}"${deleting ? " disabled" : ""}>${deleting ? "Deleting Archived Run" : "Delete Archived Run"}</button>
    </div>
  `;
  panel.querySelector("[data-delete-selected-result]")?.addEventListener("click", () => {
    deleteSavedResult(result.id);
  });
}

function resultSummaryItem(label, value) {
  return `
    <div class="result-summary-item">
      <span>${escapeHtml(label)}</span>
      <strong>${escapeHtml(value)}</strong>
    </div>
  `;
}

function resultSummaryLink(label, path) {
  return `
    <a class="result-summary-item result-summary-link" href="/files/${encodeURIComponent(path)}" target="_blank" rel="noreferrer">
      <span>${escapeHtml(label)}</span>
      <strong>${escapeHtml(path)}</strong>
    </a>
  `;
}

function renderSavedResultOutputs() {
  const title = document.getElementById("study-selected-title");
  const list = document.getElementById("study-output-list");
  const preview = document.getElementById("study-preview");
  const result = selectedSavedResult();
  if (!title || !list || !preview) return;
  title.textContent = result?.label ? `${result.label} Files` : "Archived Files";
  if (!result?.files?.length) {
    list.innerHTML = `<div class="empty-state">No archived files yet.</div>`;
    preview.innerHTML = `<div class="empty-state">Run a simulation to create downloadable archive files.</div>`;
    return;
  }
  list.innerHTML = result.files.map(outputItem).join("");
  list.querySelectorAll("[data-file-path]").forEach((button) => {
    button.addEventListener("click", () => previewFile(button.dataset.filePath, button.dataset.fileKind, "study-preview"));
  });
  const first = result.files.find((file) => file.exists && isPreviewableFile(file.kind));
  if (first) previewFile(first.path, first.kind, "study-preview");
  else preview.innerHTML = `<div class="empty-state">Download the archive files from the list.</div>`;
}

function renderProcessingWorkflows() {
  const list = document.getElementById("processing-workflow-list");
  const summary = document.getElementById("processing-summary-panel");
  if (!list || !summary) return;
  const workflows = processingWorkflows();
  if (!workflows.length) {
    list.innerHTML = `<div class="empty-state">No processing workflows yet.</div>`;
  } else {
    list.innerHTML = workflows.map(processingWorkflowCard).join("");
    list.querySelectorAll("[data-processing-workflow]").forEach((card) => {
      card.addEventListener("click", () => {
        state.selectedProcessingWorkflowId = card.dataset.processingWorkflow;
        renderProcessingWorkflows();
        renderProcessingForm();
      });
    });
  }
  const selected = selectedProcessingWorkflow();
  if (!selected) {
    summary.innerHTML = `
      <div class="result-summary-grid">
        ${resultSummaryItem("Vehicle Config", activeVehicleKey() || "Unsaved")}
        ${resultSummaryItem("Workspace", activeVehicleWorkspace().workspace?.path || "No workspace")}
        ${resultSummaryItem("Processing", "0 workflows")}
      </div>
    `;
    return;
  }
  summary.innerHTML = `
    <div class="result-summary-grid">
      ${resultSummaryItem("Workflow", selected.label)}
      ${resultSummaryItem("Source", selected.source_path || "No source")}
      ${resultSummaryItem("Signals", selected.signals?.length ? selected.signals.join(", ") : "All numeric")}
      ${resultSummaryItem("Output", selected.output_name || "Not set")}
      ${resultSummaryItem("Created", selected.created_label || "")}
      ${resultSummaryItem("Vehicle Config", selected.vehicle_key || activeVehicleKey())}
    </div>
  `;
}

function processingWorkflowCard(workflow) {
  const active = workflow.id === state.selectedProcessingWorkflowId;
  const signalCount = workflow.signals?.length || 0;
  return `
    <article class="workflow-card result-source-card ${active ? "active" : ""}" data-processing-workflow="${escapeHtml(workflow.id)}">
      <div class="card-head">
        <div class="card-title">${escapeHtml(workflow.label)}</div>
        <span class="mini-pill">Processing</span>
      </div>
      <div class="card-meta">${escapeHtml(workflow.source_path || "No source selected")}</div>
      <div class="signal-row">
        <span class="mini-pill ${workflow.source?.exists ? "ok" : "missing"}">${workflow.source?.exists ? "Source" : "Missing"}</span>
        <span class="mini-pill">${signalCount ? `${signalCount} signals` : "All numeric"}</span>
      </div>
    </article>
  `;
}

function renderProcessingForm() {
  const sourcePicker = document.getElementById("processing-source-picker");
  const addButton = document.getElementById("add-processing-btn");
  const removeButton = document.getElementById("remove-processing-btn");
  const status = document.getElementById("processing-status");
  if (!sourcePicker || !addButton || !removeButton || !status) return;
  const sources = resultSources();
  sourcePicker.innerHTML = sources.length
    ? sources.map((source) => `<option value="${escapeHtml(source.path)}">${escapeHtml(source.label || source.path)}</option>`).join("")
    : `<option value="">No result CSV sources</option>`;
  addButton.disabled = !activeVehicleConfigReady() || !sources.length;
  addButton.title = !activeVehicleConfigReady()
    ? "Save this vehicle config before adding processing"
    : !sources.length
    ? "Save result CSVs before adding processing"
    : "";
  removeButton.disabled = !selectedProcessingWorkflow();
  status.textContent = state.processingStatusMessage || `${processingWorkflows().length} workflow${processingWorkflows().length === 1 ? "" : "s"} for ${activeVehicleKey() || "this vehicle"}.`;
}

async function addProcessingWorkflow() {
  const sourcePath = document.getElementById("processing-source-picker")?.value || "";
  const name = document.getElementById("processing-name")?.value.trim() || "Processing workflow";
  const signals = (document.getElementById("processing-signals")?.value || "")
    .split(",")
    .map((signal) => signal.trim())
    .filter(Boolean);
  const outputName = document.getElementById("processing-output-name")?.value.trim() || "";
  const notes = document.getElementById("processing-notes")?.value.trim() || "";
  if (!activeVehicleConfigReady()) {
    state.processingStatusMessage = "Save this vehicle config before adding processing.";
    renderProcessingForm();
    return;
  }
  if (!sourcePath) {
    state.processingStatusMessage = "Select a result CSV before adding processing.";
    renderProcessingForm();
    return;
  }
  try {
    const payload = await api("/api/processing/workflows", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        vehicle_key: activeVehicleKey(),
        label: name,
        source_path: sourcePath,
        signals,
        output_name: outputName,
        notes,
      }),
    });
    state.processingPayload = { workflows: payload.workflows || [] };
    state.selectedProcessingWorkflowId = payload.saved?.id || state.selectedProcessingWorkflowId;
    state.processingStatusMessage = "Added processing workflow.";
    state.status = await api("/api/status");
    ["processing-name", "processing-signals", "processing-output-name", "processing-notes"].forEach((id) => {
      const input = document.getElementById(id);
      if (input) input.value = "";
    });
  } catch (error) {
    state.processingStatusMessage = error.message;
  }
  renderStudies();
}

async function removeSelectedProcessingWorkflow() {
  const selected = selectedProcessingWorkflow();
  if (!selected) return;
  const confirmed = window.confirm(`Remove processing workflow "${selected.label}"?`);
  if (!confirmed) return;
  try {
    const payload = await api("/api/processing/workflows/delete", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ vehicle_key: activeVehicleKey(), workflow_id: selected.id }),
    });
    state.processingPayload = { workflows: payload.workflows || [] };
    state.selectedProcessingWorkflowId = state.processingPayload.workflows[0]?.id || null;
    state.processingStatusMessage = "Removed processing workflow.";
    state.status = await api("/api/status");
  } catch (error) {
    state.processingStatusMessage = error.message;
  }
  renderStudies();
}

function syncStudyTabs() {
  document.querySelectorAll(".study-tab").forEach((item) => {
    item.classList.toggle("active", item.dataset.studyTab === state.activeStudyTab);
  });
  document.querySelectorAll(".study-panel").forEach((panel) => {
    panel.classList.toggle("active", panel.id === `study-${state.activeStudyTab}-panel`);
  });
}

function renderStudyCatalog() {
  const grid = document.getElementById("study-catalog-grid");
  if (!grid) return;
  const workflows = studyWorkflows();
  if (!workflows.length) {
    grid.innerHTML = `<div class="empty-state">No studies are registered.</div>`;
    return;
  }
  grid.innerHTML = STUDY_GROUPS
    .map((group) => {
      const groupWorkflows = workflows.filter((workflow) => workflow.group === group.id);
      if (!groupWorkflows.length) return "";
      return `
        <section class="study-group study-group-${escapeHtml(group.accent)}">
          <div class="study-group-title">
            <span>${escapeHtml(group.label)}</span>
            <small>${groupWorkflows.length}</small>
          </div>
          <div class="workflow-grid">
            ${groupWorkflows.map(studyWorkflowCard).join("")}
          </div>
        </section>
      `;
    })
    .join("");
  grid.querySelectorAll("[data-study-workflow]").forEach((card) => {
    card.addEventListener("click", async () => {
      await selectStudyWorkflow(card.dataset.studyWorkflow);
    });
  });
}

function studyWorkflowCard(workflow) {
  const group = studyGroupMeta(workflow.group);
  const canRun = workflowAvailable(workflow);
  return `
    <article class="workflow-card study-card ${workflow.id === state.selectedStudyWorkflowId ? "active" : ""} ${canRun ? "" : "disabled"}" data-study-workflow="${workflow.id}">
      <div class="card-head">
        <div class="card-title">${escapeHtml(workflow.label)}</div>
        <span class="mini-pill">${escapeHtml(group.label)}</span>
      </div>
      <div class="card-meta">${escapeHtml(studyDescription(workflow))}</div>
      <div class="signal-row">
        <span class="mini-pill ${workflow.config?.exists ? "ok" : "missing"}">Config</span>
        ${canRun ? "" : `<span class="mini-pill missing">Unavailable</span>`}
      </div>
    </article>
  `;
}

async function selectStudyWorkflow(workflowId) {
  if (!workflowId || workflowId === state.selectedStudyWorkflowId) return;
  state.selectedStudyWorkflowId = workflowId;
  state.activeStudyTab = "setup";
  state.studyConfigPayload = null;
  state.studyConfigLibrary = null;
  state.selectedStudyConfigSource = "";
  const saveName = document.getElementById("save-study-config-name");
  if (saveName) saveName.value = "";
  renderStudies();
  await refreshSelectedStudyConfig();
  renderStudies();
}

function renderStudyDiagnostic(workflow = selectedStudyWorkflow()) {
  const target = document.getElementById("study-diagnostic");
  if (!target) return;
  target.innerHTML = studyDiagnosticHtml(workflow, currentStudyConfigData());
}

function renderStudySetup(workflow) {
  const guide = studyWorkflowGuide(workflow);
  const title = document.getElementById("study-setup-title");
  const copy = document.getElementById("study-setup-copy");
  const steps = document.getElementById("study-step-strip");
  if (title) title.textContent = guide.title;
  if (copy) copy.textContent = guide.copy;
  if (steps) {
    steps.innerHTML = guide.steps.map((step, index) => `
      <div class="sim-step ${index === 1 ? "active" : ""}">
        <span>${index + 1}</span>
        <strong>${escapeHtml(step)}</strong>
      </div>
    `).join("");
  }
  renderStudyConfigLibrary();
  renderStudyConfigForm();
}

function renderStudyConfigLibrary() {
  const picker = document.getElementById("study-config-picker");
  const sources = state.studyConfigLibrary?.sources || [];
  if (picker) {
    if (!sources.some((source) => source.id === state.selectedStudyConfigSource)) {
      state.selectedStudyConfigSource = sources[0]?.id || "";
    }
    picker.innerHTML = sources.length
      ? sources.map((source) => `
        <option value="${escapeHtml(source.id)}"${source.id === state.selectedStudyConfigSource ? " selected" : ""}>
          ${escapeHtml(source.type === "default" ? "Default" : `Saved: ${source.label}`)}
        </option>
      `).join("")
      : `<option value="">No study configs</option>`;
  }
  const selected = sources.find((source) => source.id === state.selectedStudyConfigSource);
  const deleteButton = document.getElementById("delete-study-config-btn");
  if (deleteButton) {
    const canDelete = selected?.type === "saved";
    deleteButton.hidden = !canDelete;
    deleteButton.disabled = !canDelete;
  }
  const workflow = selectedStudyWorkflow();
  const saveName = document.getElementById("save-study-config-name");
  if (saveName && !saveName.value && workflow) saveName.value = `${workflow.label} study`;
  updateStudyConfigStatus();
}

function renderStudyConfigForm() {
  const form = document.getElementById("study-config-form");
  if (!form) return;
  if (!state.studyConfigPayload) {
    form.innerHTML = `<div class="empty-state">Select a study to configure its inputs.</div>`;
    return;
  }
  const fields = state.studyConfigPayload.fields || [];
  form.innerHTML = fields.length
    ? fieldGroupSections(fields, "study-config")
    : `<div class="empty-state">This study has no editable fields yet. Its YAML can still be wired into the backend.</div>`;
  form.oninput = () => {
    markStudyConfigDirty();
    renderStudyDiagnostic(selectedStudyWorkflow());
  };
  form.onchange = () => {
    markStudyConfigDirty();
    renderStudyDiagnostic(selectedStudyWorkflow());
  };
  form.onclick = handleArrayEditorClick;
}

function markStudyConfigDirty() {
  state.dirtyStudyConfig = true;
  updateStudyConfigStatus();
}

function updateStudyConfigStatus() {
  const status = document.getElementById("study-config-status");
  if (!status) return;
  const workflow = selectedStudyWorkflow();
  if (!workflow) {
    status.textContent = "No study selected.";
    return;
  }
  if (!state.studyConfigPayload) {
    status.textContent = "Loading study configuration.";
    return;
  }
  status.textContent = state.dirtyStudyConfig
    ? "Study config has unapplied edits."
    : `Editing ${state.studyConfigPayload.label || workflow.label} config.`;
}

function renderStudyOutputs(workflow) {
  const title = document.getElementById("study-selected-title");
  const list = document.getElementById("study-output-list");
  const preview = document.getElementById("study-preview");
  if (!list || !preview) return;
  if (title) title.textContent = workflow?.label ? `${workflow.label} Outputs` : "Study Outputs";
  if (!workflow?.outputs.length) {
    list.innerHTML = `<div class="empty-state">This study does not register static outputs yet.</div>`;
    preview.innerHTML = `<div class="empty-state">Run logs will still show execution details.</div>`;
    return;
  }
  list.innerHTML = workflow.outputs.map(outputItem).join("");
  list.querySelectorAll("[data-file-path]").forEach((button) => {
    button.addEventListener("click", () => previewFile(button.dataset.filePath, button.dataset.fileKind, "study-preview"));
  });
  const first = workflow.outputs.find((output) => output.exists);
  if (first) previewFile(first.path, first.kind, "study-preview");
  else preview.innerHTML = `<div class="empty-state">No output file yet.</div>`;
}

function renderStudyJobs() {
  const jobs = state.status?.jobs || [];
  const list = document.getElementById("study-job-list");
  const runButton = document.getElementById("run-study-btn");
  const workflow = selectedStudyWorkflow();
  if (runButton) {
    const canRun = workflowAvailable(workflow);
    runButton.disabled = !canRun;
    const runVerb = workflow?.actions.length > 1 ? "Build + Run" : "Run";
    runButton.textContent = canRun
      ? `${state.dirtyStudyConfig ? "Apply + " : ""}${runVerb} ${workflow.label}`
      : "Study locked";
    runButton.title = canRun ? "" : workflowUnavailableMessage(workflow);
  }
  if (!list) return;
  if (!jobs.length) {
    list.innerHTML = `<div class="empty-state">No jobs yet.</div>`;
    const log = document.getElementById("study-job-log");
    if (log) log.textContent = "";
    return;
  }
  if (!state.selectedJobId) state.selectedJobId = jobs[0].id;
  list.innerHTML = jobs.map(jobItem).join("");
  list.querySelectorAll("[data-job]").forEach((item) => {
    item.addEventListener("click", async () => {
      state.selectedJobId = item.dataset.job;
      await loadJobLog("study-job-log");
      renderStudyJobs();
    });
  });
  loadJobLog("study-job-log");
}

function simWorkflowGuide(workflow) {
  const meta = simWorkflowMeta(workflow);
  return {
    title: meta.title,
    copy: meta.summary,
    steps: meta.steps,
  };
}

function renderSimSetup(workflow) {
  const guide = simWorkflowGuide(workflow);
  document.getElementById("sim-setup-title").textContent = guide.title;
  document.getElementById("sim-setup-copy").textContent = guide.copy;
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
  form.onclick = handleArrayEditorClick;
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
    status.textContent = "No simulation workflow selected.";
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
  const title = document.getElementById("selected-title");
  const list = document.getElementById("output-list");
  const preview = document.getElementById("preview");
  if (!title || !list || !preview) return;
  title.textContent = workflow?.label || "Outputs";
  if (!workflow?.outputs.length) {
    list.innerHTML = `<div class="empty-state">No registered outputs.</div>`;
    preview.innerHTML = `<div class="empty-state"></div>`;
    return;
  }
  list.innerHTML = workflow.outputs.map(outputItem).join("");
  list.querySelectorAll("[data-file-path]").forEach((button) => {
    button.addEventListener("click", () => previewFile(button.dataset.filePath, button.dataset.fileKind));
  });
  const first = workflow.outputs.find((output) => output.exists);
  if (first) previewFile(first.path, first.kind);
  else preview.innerHTML = `<div class="empty-state">No output file yet.</div>`;
}

function fileDownloadUrl(path) {
  return `/files/${encodeURIComponent(path)}`;
}

function isPreviewableFile(kind) {
  return ["pdf", "csv", "text", "json"].includes(String(kind || "").toLowerCase());
}

function pdfPreviewHtml(path) {
  const url = fileDownloadUrl(path);
  return `
    <div class="pdf-preview-shell">
      <div class="pdf-preview-actions">
        <a class="file-button" href="${url}" target="_blank" rel="noreferrer">Open PDF</a>
        <a class="file-button" href="${url}" download>Download</a>
      </div>
      <object class="pdf-preview-frame" data="${url}" type="application/pdf">
        <iframe src="${url}"></iframe>
      </object>
    </div>
  `;
}

function outputItem(output) {
  const meta = output.exists ? `${escapeHtml(output.modified_label)} | ${fmtBytes(output.size)}` : "missing";
  const previewButton = output.exists && isPreviewableFile(output.kind)
    ? `<button class="file-button" type="button" data-file-path="${escapeHtml(output.path)}" data-file-kind="${escapeHtml(output.kind)}">Preview</button>`
    : `<button class="file-button" type="button" disabled>Preview</button>`;
  const downloadButton = output.exists
    ? `<a class="file-button" href="${fileDownloadUrl(output.path)}" download>Download</a>`
    : `<button class="file-button" type="button" disabled>Download</button>`;
  return `
    <div class="output-item">
      <div>
        <div class="output-name">${escapeHtml(output.label)}</div>
        <div class="output-meta">${meta}</div>
      </div>
      <div class="output-actions">${previewButton}${downloadButton}</div>
    </div>
  `;
}

async function previewFile(path, kind, targetId = "preview") {
  const preview = document.getElementById(targetId);
  if (!preview) return;
  if (kind === "pdf") {
    preview.innerHTML = pdfPreviewHtml(path);
    return;
  }
  if (kind === "csv") {
    const data = await api(`/api/csv?path=${encodeURIComponent(path)}`);
    preview.innerHTML = csvTable(data);
    return;
  }
  if (kind === "text" || kind === "json") {
    const response = await fetch(`/files/${encodeURIComponent(path)}`);
    const text = await response.text();
    preview.innerHTML = `<pre class="log-view">${escapeHtml(text)}</pre>`;
    return;
  }
  if (kind === "zip") {
    preview.innerHTML = `<div class="empty-state"><a class="file-button" href="${fileDownloadUrl(path)}" download>Download Signal Archive</a></div>`;
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
  const canRun = canRunStandardWorkflow(workflow);
  runButton.disabled = !canRun;
  const runVerb = workflow?.actions.length > 1 ? "Build + Run" : "Run";
  runButton.textContent = !canRun
    ? "Simulation locked"
    : workflow
    ? `${state.dirtySimConfig ? "Apply + " : ""}${runVerb} ${workflow.label}`
    : "No Workflow";
  runButton.title = canRun ? "" : standardWorkflowLockedMessage(workflow);
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

async function loadJobLog(targetId = "job-log") {
  if (!state.selectedJobId) return;
  const job = await api(`/api/jobs/${state.selectedJobId}`);
  const log = document.getElementById(targetId);
  if (!log) return;
  log.textContent = job.log || "";
  log.scrollTop = log.scrollHeight;
}

async function startSelectedWorkflow() {
  const workflow = selectedWorkflow();
  if (!workflow) return;
  if (!canRunStandardWorkflow(workflow)) {
    state.view = "setup";
    render();
    return;
  }
  if (state.dirtySimConfig) {
    const applied = await applySimConfigEdits();
    if (!applied) return;
  }
  try {
    const job = await api(`/api/workflows/${workflow.id}/run`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
    });
    state.selectedJobId = job.id;
    state.activeSimTab = "jobs";
    state.simModalOpen = true;
    state.status = await api("/api/status");
    renderStandard();
  } catch (error) {
    state.activeSimTab = "jobs";
    state.simModalOpen = true;
    state.status = await api("/api/status").catch(() => state.status);
    renderStandard();
    const log = document.getElementById("job-log");
    if (log) log.textContent = error.message;
  }
}

async function startSelectedStudyWorkflow() {
  const workflow = selectedStudyWorkflow();
  if (!workflow) return;
  if (!workflowAvailable(workflow)) {
    const log = document.getElementById("study-job-log");
    if (log) log.textContent = workflowUnavailableMessage(workflow);
    return;
  }
  if (state.dirtyStudyConfig) {
    const applied = await applyStudyConfigEdits();
    if (!applied) return;
  }
  try {
    const job = await api(`/api/workflows/${workflow.id}/run`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
    });
    state.selectedJobId = job.id;
    state.activeStudyTab = "jobs";
    state.status = await api("/api/status");
    renderStudies();
  } catch (error) {
    state.activeStudyTab = "jobs";
    state.status = await api("/api/status").catch(() => state.status);
    renderStudies();
    const log = document.getElementById("study-job-log");
    if (log) log.textContent = error.message;
  }
}

function setView(view) {
  if (view === "standard" && !canUseStandardSim()) {
    state.view = "setup";
    renderMode();
    renderRailActions();
    renderSetup();
    return;
  }
  state.view = view;
  renderMode();
  renderRailActions();
  if (view === "standard") renderStandard();
  if (view === "studies") renderStudies();
  if (view === "setup") renderSetup();
}

function toggleTheme() {
  state.dark = !state.dark;
  localStorage.setItem("bobsim-theme", state.dark ? "dark" : "light");
  document.body.classList.toggle("dark", state.dark);
  renderThemeButton();
  drawVehicleFromForm();
  drawSuspensionPlotModal();
  drawGeometryPlotPanel();
}

function renderVehiclePreview(data) {
  requestAnimationFrame(() => drawVehiclePreview(data));
}

function currentVehicleFormData() {
  if (!state.vehiclePayload) return;
  try {
    const data = JSON.parse(JSON.stringify(state.vehiclePayload.data || {}));
    const values = collectVehicleValues({ skipInvalid: true });
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
  if (!Array.isArray(path) || !path.length) return;
  let current = data;
  for (let idx = 0; idx < path.length - 1; idx += 1) {
    const key = path[idx];
    const nextKey = path[idx + 1];
    if (!current[key] || typeof current[key] !== "object") {
      current[key] = Number.isInteger(nextKey) ? [] : {};
    }
    current = current[key];
  }
  current[path[path.length - 1]] = value;
}

function drawVehiclePreview(data) {
  const canvas = document.getElementById("vehicle-canvas");
  const area = activeParameterArea();
  syncPreviewModeControls(area);
  if (!isKinematicPlotArea(area)) clearSuspensionPlotInteractionScene();
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
    try {
      drawTirePreview(ctx, width, height, data);
    } catch (error) {
      console.error("Tire preview draw failed", error?.stack || error);
      drawTirePreviewError(ctx, width, height, error, data);
    }
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
  renderGeometryPlotControls();
  drawGeometryPlotPanel();
}

function clearGeometryInteractionScene() {
  state.geometryScene = null;
  state.geometryHoverPointId = null;
  state.geometryDrag = null;
  document.getElementById("vehicle-canvas")?.classList.remove("geometry-hot", "geometry-dragging");
  syncGeometryPointEditor();
}

function clearGeometryPlotScene() {
  state.geometryPlotScene = null;
  state.geometryPlotHover = null;
}

function clearArchitectureInteractionScene() {
  state.architectureScene = null;
  state.architectureHoverId = null;
  state.architectureDrag = null;
  state.architectureModalOpen = false;
  state.architectureModalAxle = null;
  state.architectureModalScene = null;
  state.architectureModalHoverId = null;
  document.getElementById("vehicle-canvas")?.classList.remove("architecture-hot");
  document.getElementById("architecture-connection-canvas")?.classList.remove("hot", "dragging");
  renderArchitectureConnectionModal();
}

function clearMassInteractionScene() {
  state.massScene = null;
  state.massHoverPointId = null;
  state.massSelectedPointId = null;
  document.getElementById("vehicle-canvas")?.classList.remove("mass-hot");
  syncMassPropertyEditor();
}

function clearSuspensionPlotInteractionScene() {
  state.suspensionPlotScene = null;
  state.suspensionPlotHover = null;
  closeSuspensionPlotModal({ redraw: false });
  document.getElementById("vehicle-canvas")?.classList.remove("kinematic-hot");
}

function isArchitecturePreviewArea(area = activeParameterArea()) {
  return area.visual === "overview";
}

function isKinematicPlotArea(area = activeParameterArea()) {
  return area.id === "hardpoints";
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
    .find((hotspot) => architectureHotspotContainsPoint(hotspot, point)) || null;
}

function architectureHotspotContainsPoint(hotspot, point) {
  if (!hotspot || !point) return false;
  if (
    hotspot.type === "bellcrank-pickup"
    && Number.isFinite(hotspot.cx)
    && Number.isFinite(hotspot.cy)
  ) {
    return Math.hypot(point.x - hotspot.cx, point.y - hotspot.cy) <= (hotspot.radius || 24);
  }
  if (!hotspot.rect) return false;
  return point.x >= hotspot.rect.x
    && point.x <= hotspot.rect.x + hotspot.rect.width
    && point.y >= hotspot.rect.y
    && point.y <= hotspot.rect.y + hotspot.rect.height;
}

function updateArchitectureHover(event) {
  const hotspot = hitTestArchitectureHotspot(event);
  const next = hotspot?.id || null;
  if (next !== state.architectureHoverId) {
    state.architectureHoverId = next;
    drawVehicleFromForm();
  }
  const canvas = document.getElementById("vehicle-canvas");
  canvas?.classList.toggle("architecture-hot", Boolean(hotspot));
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

function hitTestArchitectureModalHotspot(event) {
  const canvas = document.getElementById("architecture-connection-canvas");
  const point = pointerCanvasPointFor(event, canvas);
  if (!point || !state.architectureModalScene) return null;
  return [...state.architectureModalScene.hotspots]
    .reverse()
    .find((hotspot) => architectureHotspotContainsPoint(hotspot, point)) || null;
}

function updateArchitectureModalHover(event) {
  if (state.architectureDrag) return;
  const hotspot = hitTestArchitectureModalHotspot(event);
  const next = hotspot?.id || null;
  if (next !== state.architectureModalHoverId) {
    state.architectureModalHoverId = next;
    drawArchitectureConnectionCanvas();
  }
  document.getElementById("architecture-connection-canvas")?.classList.toggle("hot", hotspot?.type === "bellcrank-pickup");
}

function startArchitecturePickupDrag(event, hotspot) {
  const canvas = document.getElementById("architecture-connection-canvas");
  const point = pointerCanvasPointFor(event, canvas);
  if (!canvas || !point || event.button !== 0 || hotspot?.type !== "bellcrank-pickup") return false;
  state.architectureSelectedOrderIndex = Number(hotspot.index) || 0;
  state.architectureSelectedId = `architecture-${hotspot.axle}-pickup-${state.architectureSelectedOrderIndex}`;
  state.architectureModalHoverId = hotspot.id;
  state.architectureDrag = {
    pointerId: event.pointerId,
    axle: hotspot.axle,
    side: hotspot.side || "",
    index: Number(hotspot.index) || 0,
    role: hotspot.role || "",
    startX: point.x,
    startY: point.y,
    x: point.x,
    y: point.y,
    originX: hotspot.cx,
    originY: hotspot.cy,
    active: false,
    targetIndex: null,
  };
  canvas.classList.add("dragging");
  canvas.setPointerCapture(event.pointerId);
  drawArchitectureConnectionCanvas();
  return true;
}

function updateArchitecturePickupDrag(event) {
  const drag = state.architectureDrag;
  if (!drag || drag.pointerId !== event.pointerId) return false;
  const canvas = document.getElementById("architecture-connection-canvas");
  const point = pointerCanvasPointFor(event, canvas);
  if (!point) return false;
  drag.x = point.x;
  drag.y = point.y;
  drag.active = drag.active || Math.hypot(point.x - drag.startX, point.y - drag.startY) > 6;
  const target = drag.active ? closestArchitecturePickupDropTarget(drag, point) : null;
  drag.targetIndex = Number.isFinite(target?.index) ? target.index : null;
  drawArchitectureConnectionCanvas();
  return true;
}

function closestArchitecturePickupDropTarget(drag, point) {
  const candidates = (state.architectureModalScene?.hotspots || [])
    .filter((hotspot) => (
      hotspot.type === "bellcrank-pickup"
      && hotspot.axle === drag.axle
      && hotspot.side === drag.side
      && Number(hotspot.index) !== Number(drag.index)
      && Number.isFinite(hotspot.cx)
      && Number.isFinite(hotspot.cy)
    ))
    .map((hotspot) => ({
      ...hotspot,
      distance: Math.hypot(point.x - hotspot.cx, point.y - hotspot.cy),
    }))
    .filter((hotspot) => hotspot.distance <= Math.max(34, (hotspot.radius || 24) + 16))
    .sort((a, b) => a.distance - b.distance);
  return candidates[0] || null;
}

function finishArchitecturePickupDrag(pointerId) {
  const drag = state.architectureDrag;
  if (!drag || drag.pointerId !== pointerId) return false;
  state.architectureDrag = null;
  const canvas = document.getElementById("architecture-connection-canvas");
  canvas?.classList.remove("dragging");
  if (canvas?.hasPointerCapture?.(pointerId)) canvas.releasePointerCapture(pointerId);
  if (drag.active && Number.isFinite(drag.targetIndex)) {
    swapArchitectureOrderPickups(drag.axle, drag.index, drag.targetIndex);
  } else if (!drag.active) {
    selectArchitectureOrderPickup(drag.axle, drag.index);
  } else {
    drawArchitectureConnectionCanvas();
  }
  return true;
}

function cancelArchitecturePickupDrag(pointerId) {
  const drag = state.architectureDrag;
  if (!drag || drag.pointerId !== pointerId) return false;
  state.architectureDrag = null;
  const canvas = document.getElementById("architecture-connection-canvas");
  canvas?.classList.remove("dragging");
  if (canvas?.hasPointerCapture?.(pointerId)) canvas.releasePointerCapture(pointerId);
  drawArchitectureConnectionCanvas();
  return true;
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
  state.architectureModalScene = null;
  state.architectureModalHoverId = null;
  state.architectureDrag = null;
  document.getElementById("architecture-connection-canvas")?.classList.remove("hot", "dragging");
  renderArchitectureConnectionModal();
}

function renderArchitectureConnectionModal(data = currentVehicleFormData() || state.vehiclePayload?.data || {}) {
  const modal = document.getElementById("architecture-connection-modal");
  if (!modal) return;
  const axle = state.architectureModalAxle;
  const active = state.architectureModalOpen && isArchitecturePreviewArea() && ["front", "rear"].includes(axle);
  modal.hidden = !active;
  if (!active) {
    state.architectureModalScene = null;
    state.architectureModalHoverId = null;
    return;
  }

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
  if (architecture.includes("bellcrank")) requestAnimationFrame(() => drawArchitectureConnectionCanvas());
  else state.architectureModalScene = null;
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
  return `
    <section class="connection-map-panel">
      <canvas id="architecture-connection-canvas" class="connection-canvas" aria-label="${escapeHtml(humanizeToken(axle))} bellcrank front view"></canvas>
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

function drawArchitectureConnectionCanvas(data = currentVehicleFormData() || state.vehiclePayload?.data || {}) {
  const canvas = document.getElementById("architecture-connection-canvas");
  const axle = state.architectureModalAxle;
  if (!canvas || !["front", "rear"].includes(axle)) return;
  const side = architectureModalSide();
  const rect = canvas.getBoundingClientRect();
  const width = Math.max(420, Math.floor(rect.width || 620));
  const height = Math.max(320, Math.floor(rect.height || 440));
  const dpr = window.devicePixelRatio || 1;
  canvas.width = Math.floor(width * dpr);
  canvas.height = Math.floor(height * dpr);
  const ctx = canvas.getContext("2d");
  ctx.setTransform(dpr, 0, 0, dpr, 0, 0);
  ctx.clearRect(0, 0, width, height);

  const architecture = String(data.architecture?.[axle] || "");
  const fullModel = buildVehicleGeometry(data);
  const geometryModel = filterVehicleModel(fullModel, sectionFocus("geometry"));
  const model = architectureConnectionModalModel(geometryModel, axle, side);
  const viewport = {
    id: `${axle}-modal-front`,
    axle,
    side,
    label: "Front",
    view: "front",
    x: 12,
    y: 12,
    width: width - 24,
    height: height - 24,
  };
  const hotspots = [];

  drawPreviewGrid(ctx, width, height);
  if (!model.points.length) {
    state.architectureModalScene = { hotspots, width, height };
    drawCanvasText(ctx, "No bellcrank geometry is available.", width / 2, height / 2, {
      align: "center",
      color: canvasPalette().muted,
    });
    return;
  }

  const scene = projectArchitectureScene(model, viewport);
  drawArchitectureViewport(ctx, viewport);
  drawArchitectureAssemblyScene(ctx, scene, model);
  drawArchitectureModalConnections(ctx, scene, axle, side, architecture, data, hotspots);
  state.architectureModalScene = { hotspots, width, height };
}

function architectureModalSide() {
  return "left";
}

function architectureConnectionModalModel(model, axle, side) {
  const pointRoles = new Set(["actuation", "bellcrank", "stabar"]);
  const points = model.points.filter((point) => (
    point.axle === axle
    && point.side === side
    && pointRoles.has(point.role)
  ));
  const pointIds = new Set(points.map((point) => point.id));
  return {
    points,
    links: model.links.filter((link) => (
      link.axle === axle
      && link.role === "bellcrank"
      && pointIds.has(link.from)
      && pointIds.has(link.to)
    )),
  };
}

function drawArchitectureModalConnections(ctx, scene, axle, side, architecture, data, hotspots) {
  if (!architecture.includes("bellcrank")) return;
  const path = [axle, "actuation", "bellcrank", "order"];
  const choices = bellcrankOrderChoicesForPath(path, data) || ["rod", "shock"];
  const values = architectureOrderValuesForData(axle, data);
  const prefix = `${axle}-${side}`;
  const drag = state.architectureDrag;
  const sockets = choices.map((socketRole, index) => {
    const point = scene.map.get(`${prefix}-bellcrank-${socketRole}`);
    if (!point) return null;
    return {
      index,
      socketRole,
      role: values[index] || socketRole,
      point,
    };
  }).filter(Boolean);
  sockets.forEach((socket) => {
    const draggingThis = drag
      && drag.axle === axle
      && drag.side === side
      && Number(drag.index) === Number(socket.index);
    const end = draggingThis && drag.active
      ? { ...socket.point, x2: drag.x, y2: drag.y }
      : socket.point;
    drawArchitectureModalLink(ctx, scene, prefix, socket.role, end, draggingThis);
  });
  sockets.forEach((socket) => {
    drawArchitectureModalSocket(ctx, socket, drag, axle, side);
  });
  sockets.forEach((socket) => {
    const draggingThis = drag
      && drag.axle === axle
      && drag.side === side
      && Number(drag.index) === Number(socket.index);
    const point = draggingThis && drag.active
      ? { ...socket.point, x2: drag.x, y2: drag.y }
      : socket.point;
    drawArchitectureModalHandle(ctx, socket, point, draggingThis);
    hotspots.push({
      id: `architecture-${axle}-pickup-${socket.index}`,
      type: "bellcrank-pickup",
      axle,
      side,
      index: socket.index,
      role: socket.role,
      cx: socket.point.x2,
      cy: socket.point.y2,
      radius: 26,
      rect: { x: socket.point.x2 - 26, y: socket.point.y2 - 26, width: 52, height: 52 },
      view: "front",
    });
  });
}

function drawArchitectureModalLink(ctx, scene, prefix, role, end, draggingThis = false) {
  const source = scene.map.get(architectureConnectionSourceId(prefix, role));
  if (!source || !end) return;
  const linkRole = architectureConnectionLinkRole(role);
  drawCylinder(ctx, source, end, {
    role: linkRole,
    color: linkColor(linkRole),
    width: draggingThis ? 6 : 5,
    opacity: draggingThis ? 0.9 : 0.76,
  });
}

function drawArchitectureModalSocket(ctx, socket, drag, axle, side) {
  const palette = canvasPalette();
  const draggingThis = drag
    && drag.axle === axle
    && drag.side === side
    && Number(drag.index) === Number(socket.index);
  const targetThis = drag?.active
    && drag.axle === axle
    && drag.side === side
    && Number(drag.targetIndex) === Number(socket.index);
  ctx.save();
  ctx.fillStyle = draggingThis || targetThis
    ? colorWithAlpha(palette.muted, state.dark ? 0.2 : 0.14)
    : colorWithAlpha(palette.amber, state.dark ? 0.14 : 0.1);
  ctx.strokeStyle = draggingThis || targetThis
    ? colorWithAlpha(palette.muted, 0.82)
    : colorWithAlpha(palette.amber, 0.82);
  if (draggingThis || targetThis) ctx.setLineDash([5, 4]);
  ctx.lineWidth = targetThis ? 3 : 2;
  ctx.beginPath();
  ctx.arc(socket.point.x2, socket.point.y2, targetThis ? 16 : 13, 0, Math.PI * 2);
  ctx.fill();
  ctx.stroke();
  ctx.restore();
}

function drawArchitectureModalHandle(ctx, socket, point, draggingThis = false) {
  const palette = canvasPalette();
  const selected = socket.index === state.architectureSelectedOrderIndex;
  const hovered = `architecture-${state.architectureModalAxle}-pickup-${socket.index}` === state.architectureModalHoverId;
  const color = bellcrankRoleColor(socket.role);
  const radius = draggingThis ? 16 : selected ? 15 : hovered ? 14 : 13;
  ctx.save();
  if (draggingThis) {
    ctx.shadowColor = state.dark ? "rgba(0,0,0,0.48)" : "rgba(25,38,52,0.24)";
    ctx.shadowBlur = 18;
    ctx.shadowOffsetY = 8;
  }
  ctx.fillStyle = colorWithAlpha(color, draggingThis ? 0.9 : selected ? 0.78 : 0.66);
  ctx.strokeStyle = selected ? palette.amber : hovered ? palette.blue : color;
  ctx.lineWidth = selected || hovered || draggingThis ? 3 : 2;
  ctx.beginPath();
  ctx.arc(point.x2, point.y2, radius, 0, Math.PI * 2);
  ctx.fill();
  ctx.stroke();
  ctx.shadowColor = "transparent";
  drawCanvasText(ctx, String(socket.index + 1), point.x2, point.y2 - 2, {
    align: "center",
    size: 10,
    weight: 860,
    color: "#ffffff",
  });
  drawCanvasText(ctx, humanizeToken(socket.role), point.x2 + 18, point.y2 - 14, {
    size: 10,
    weight: 820,
    color: draggingThis ? palette.ink : palette.muted,
  });
  ctx.restore();
}

function architectureConnectionSourceId(prefix, role) {
  return {
    rod: `${prefix}-rod`,
    shock: `${prefix}-shock-mount`,
    stabar: `${prefix}-stabar-arm`,
  }[role] || `${prefix}-${role}`;
}

function architectureConnectionLinkRole(role) {
  return role === "rod" ? "pushrod" : role;
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

function swapArchitectureOrderPickups(axle, fromIndex, toIndex) {
  const data = currentVehicleFormData() || state.vehiclePayload?.data || {};
  const path = [axle, "actuation", "bellcrank", "order"];
  const choices = bellcrankOrderChoicesForPath(path, data) || ["rod", "shock"];
  const values = architectureOrderValuesForData(axle, data);
  const from = clamp(Number(fromIndex) || 0, 0, Math.max(0, values.length - 1));
  const to = clamp(Number(toIndex) || 0, 0, Math.max(0, values.length - 1));
  if (from === to || !values[from] || !values[to]) {
    drawVehicleFromForm();
    return;
  }
  const nextValues = [...values];
  [nextValues[from], nextValues[to]] = [nextValues[to], nextValues[from]];
  state.architectureSelectedOrderIndex = to;
  state.architectureSelectedId = `architecture-${axle}-pickup-${to}`;
  if (state.architectureModalOpen) state.architectureModalAxle = axle;
  pushUndoSnapshot(snapshotVehicleState("architecture-order-drag"));
  setArchitectureOrderValues(axle, normalizeBellcrankOrder(nextValues, choices));
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
  queueKinematicsRefresh();
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

function canUseGeometryAxisShortcut(target = document.activeElement) {
  if (!isSpatialPreviewArea()) return false;
  if (!isTextEntryTarget(target)) return true;
  return Boolean(target?.closest?.("#geometry-point-editor"));
}

function handleGeometryAxisShortcut(event = null) {
  if (!canUseGeometryAxisShortcut(event?.target)) return false;
  event?.preventDefault?.();
  cycleGeometryAxis();
  return true;
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

function isTirePreviewArea(area = activeParameterArea()) {
  return area.visual === "tires";
}

function isSurfaceMapPreviewArea(area = activeParameterArea()) {
  return area.visual === "aero" || (area.visual === "tires" && state.activeTireTab === "load-maps");
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
  if (event.shiftKey && !state.geometryShiftActive) {
    state.geometryShiftActive = true;
    cycleGeometryAxis();
  } else if (!event.shiftKey) {
    state.geometryShiftActive = false;
  }
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
  state.geometryShiftActive = false;
  document.getElementById("vehicle-canvas")?.classList.remove("geometry-dragging");
  renderParameterTabCanvases();
  return true;
}

function isMiddleClick(event) {
  return event?.button === 1;
}

function isPanClick(event) {
  return Boolean(event?.ctrlKey || isMiddleClick(event));
}

function dragPointerId(event) {
  return event?.pointerId ?? "mouse";
}

function captureDragPointer(canvas, event) {
  if (event?.pointerId === undefined || typeof canvas?.setPointerCapture !== "function") return;
  canvas.setPointerCapture(event.pointerId);
}

function isCanvasAuxActionArea() {
  return isSpatialPreviewArea() || isSurfaceMapPreviewArea();
}

function suppressMiddleCanvasAuxAction(event) {
  if (!isMiddleClick(event) || !isCanvasAuxActionArea()) return false;
  event.preventDefault();
  return true;
}

function startMiddleCanvasPan(event) {
  if (!suppressMiddleCanvasAuxAction(event)) return false;
  if (state.vehicleDrag || state.tireSurfaceDrag) return true;
  if (isSurfaceMapPreviewArea()) return startTireSurfaceDrag(event);
  if (isSpatialPreviewArea()) {
    startPreviewDrag(event, "pan");
    return true;
  }
  return false;
}

function startPreviewDrag(event, mode = "rotate") {
  const canvas = document.getElementById("vehicle-canvas");
  if (!canvas || (event.button !== 0 && !(mode === "pan" && isMiddleClick(event)))) return;
  const width = state.geometryScene?.width || canvas.getBoundingClientRect().width || 800;
  const height = state.geometryScene?.height || canvas.getBoundingClientRect().height || 600;
  captureDragPointer(canvas, event);
  state.vehicleDrag = {
    pointerId: dragPointerId(event),
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
  if (!drag || drag.pointerId !== dragPointerId(event) || !isSpatialPreviewArea()) return false;
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

function startTireSurfaceDrag(event) {
  const canvas = document.getElementById("vehicle-canvas");
  if (!canvas || (event.button !== 0 && !isMiddleClick(event))) return;
  const hit = hitTestTireSurfacePanel(event);
  if (!hit) return false;
  captureDragPointer(canvas, event);
  state.tireSurfaceDrag = {
    pointerId: dragPointerId(event),
    mode: isPanClick(event) ? "pan" : "rotate",
    x: event.clientX,
    y: event.clientY,
    yaw: state.tireSurfaceYaw,
    pitch: state.tireSurfacePitch,
    panX: state.tireSurfacePanX,
    panY: state.tireSurfacePanY,
  };
  canvas.classList.add("tire-surface-dragging");
  event.preventDefault();
  return true;
}

function updateTireSurfaceDrag(event) {
  const drag = state.tireSurfaceDrag;
  if (!drag || drag.pointerId !== dragPointerId(event) || !isSurfaceMapPreviewArea()) return false;
  const dx = event.clientX - drag.x;
  const dy = event.clientY - drag.y;
  if (drag.mode === "pan") {
    setTireSurfacePan(drag.panX + dx, drag.panY + dy);
    drawVehicleFromForm();
    return true;
  }
  const sensitivity = 0.01 * state.rotationSensitivity;
  state.tireSurfaceYaw = drag.yaw - dx * sensitivity;
  state.tireSurfacePitch = drag.pitch - dy * sensitivity;
  drawVehicleFromForm();
  return true;
}

function finishTireSurfaceDrag(pointerId) {
  const drag = state.tireSurfaceDrag;
  if (!drag || drag.pointerId !== pointerId) return false;
  state.tireSurfaceDrag = null;
  document.getElementById("vehicle-canvas")?.classList.remove("tire-surface-dragging");
  return true;
}

function resetTireSurfaceView() {
  state.tireSurfaceYaw = DEFAULT_TIRE_SURFACE_YAW;
  state.tireSurfacePitch = DEFAULT_TIRE_SURFACE_PITCH;
  state.tireSurfaceZoom = 1;
  state.tireSurfacePanX = 0;
  state.tireSurfacePanY = 0;
  drawVehicleFromForm();
}

function tireSurfacePanLimit(plot = null) {
  const source = plot
    || state.tireSurfaceScene?.panels?.[0]?.plot
    || state.tireSurfaceScene?.panels?.[0]?.bounds
    || {};
  const width = Math.max(1, Number(source.width) || 360);
  const height = Math.max(1, Number(source.height) || 220);
  const zoom = Math.max(1, Number(state.tireSurfaceZoom) || 1);
  const zoomTravel = Math.max(0, zoom - 1);
  return {
    x: width * (0.28 + zoomTravel * 0.42),
    y: height * (0.24 + zoomTravel * 0.38),
  };
}

function setTireSurfacePan(x, y) {
  const limit = tireSurfacePanLimit();
  state.tireSurfacePanX = clamp(Number(x) || 0, -limit.x, limit.x);
  state.tireSurfacePanY = clamp(Number(y) || 0, -limit.y, limit.y);
}

function setTireSurfaceZoom(zoom) {
  state.tireSurfaceZoom = clamp(Number(zoom) || 1, MIN_TIRE_SURFACE_ZOOM, MAX_TIRE_SURFACE_ZOOM);
  setTireSurfacePan(state.tireSurfacePanX, state.tireSurfacePanY);
}

function hitTestTireSurfacePanel(event) {
  const point = pointerCanvasPoint(event);
  if (!point || !state.tireSurfaceScene?.panels?.length || !isSurfaceMapPreviewArea()) return null;
  return state.tireSurfaceScene.panels.find((panel) => pointInRect(point, panel.bounds, 0)) || null;
}

function updateTireSurfaceHover(event) {
  const canvas = document.getElementById("vehicle-canvas");
  if (!isSurfaceMapPreviewArea() || state.tireSurfaceDrag) {
    state.tireSurfaceHover = null;
    canvas?.classList.remove("tire-surface-hot");
    return;
  }
  const hit = hitTestTireSurfacePanel(event);
  state.tireSurfaceHover = hit;
  canvas?.classList.toggle("tire-surface-hot", Boolean(hit));
}

function handlePreviewWheel(event) {
  if (isSurfaceMapPreviewArea() && hitTestTireSurfacePanel(event)) {
    event.preventDefault();
    const factor = Math.exp(-event.deltaY * 0.0012);
    setTireSurfaceZoom(state.tireSurfaceZoom * factor);
    drawVehicleFromForm();
    return;
  }
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

function updateSuspensionPlotHover(event) {
  const canvas = document.getElementById("vehicle-canvas");
  if (activeParameterArea().visual !== "suspension" || !state.suspensionPlotScene) {
    if (state.suspensionPlotHover) {
      state.suspensionPlotHover = null;
      canvas?.classList.remove("kinematic-hot");
      drawVehicleFromForm();
    } else {
      canvas?.classList.remove("kinematic-hot");
    }
    return;
  }
  const hover = hitTestSuspensionPlot(event);
  const nextId = hover?.id || null;
  const previous = state.suspensionPlotHover;
  const moved = hover && previous && (
    Math.abs(hover.pointerX - previous.pointerX) > 4
    || Math.abs(hover.pointerY - previous.pointerY) > 4
  );
  if ((previous?.id || null) !== nextId || moved) {
    state.suspensionPlotHover = hover;
    drawVehicleFromForm();
  } else if (hover) {
    state.suspensionPlotHover = hover;
  }
  canvas?.classList.toggle("kinematic-hot", Boolean(hover));
}

function hitTestSuspensionPlot(event) {
  const point = pointerCanvasPoint(event);
  if (!point || !state.suspensionPlotScene) return null;
  const chart = state.suspensionPlotScene.charts.find((item) => pointInRect(point, item.plot, 3));
  if (!chart) return null;
  const sample = nearestPlotSample(chart, point);
  if (!sample) return null;
  return {
    id: `${chart.key}:${sample.sampleKey}`,
    chartKey: chart.key,
    sampleKey: sample.sampleKey,
    pointerX: point.x,
    pointerY: point.y,
  };
}

function handleSuspensionPlotClick(event) {
  void event;
  return false;
}

function clearSuspensionPlotFocus() {
  if (state.suspensionPlotModalKey) {
    closeSuspensionPlotModal();
    return true;
  }
  if (!state.suspensionPlotHover) return false;
  state.suspensionPlotHover = null;
  document.getElementById("vehicle-canvas")?.classList.remove("kinematic-hot");
  drawVehicleFromForm();
  return true;
}

function nearestPlotSample(chart, point) {
  return chart.samples.reduce((best, sample) => {
    const distance = Math.abs(sample.canvasX - point.x);
    return !best || distance < best.distance ? { ...sample, distance } : best;
  }, null);
}

function pointInRect(point, rect, pad = 0) {
  return point.x >= rect.x - pad
    && point.x <= rect.x + rect.width + pad
    && point.y >= rect.y - pad
    && point.y <= rect.y + rect.height + pad;
}

function openSuspensionPlotModal(key) {
  state.suspensionPlotModalKey = key;
  state.suspensionPlotModalHover = null;
  renderSuspensionPlotModal();
}

function closeSuspensionPlotModal({ redraw = true } = {}) {
  state.suspensionPlotModalKey = null;
  state.suspensionPlotModalScene = null;
  state.suspensionPlotModalHover = null;
  const modal = document.getElementById("kinematic-plot-modal");
  if (modal) modal.hidden = true;
  if (redraw) drawVehicleFromForm();
}

function renderSuspensionPlotModal() {
  const modal = document.getElementById("kinematic-plot-modal");
  if (!modal) return;
  const descriptor = suspensionPlotModalDescriptor();
  modal.hidden = !descriptor;
  if (!descriptor) {
    state.suspensionPlotModalScene = null;
    return;
  }
  document.getElementById("kinematic-plot-title").textContent = descriptor.label || humanizeKinematicCurve(descriptor.id);
  document.getElementById("kinematic-plot-subtitle").textContent = [
    `${descriptor.x_label || "Jounce"}${descriptor.x_unit ? ` (${descriptor.x_unit})` : ""}`,
    `${descriptor.y_label || descriptor.label}${descriptor.y_unit || descriptor.unit ? ` (${descriptor.y_unit || descriptor.unit})` : ""}`,
  ].join(" vs ");
  requestAnimationFrame(drawSuspensionPlotModal);
}

function suspensionPlotModalDescriptor() {
  const key = state.suspensionPlotModalKey;
  if (!key) return null;
  return [
    ...geometryPlotDescriptors(),
    ...kinematicCurveDescriptors(state.kinematicsPayload),
  ].find((item) => item.id === key) || null;
}

function drawSuspensionPlotModal() {
  const modal = document.getElementById("kinematic-plot-modal");
  const canvas = document.getElementById("kinematic-plot-modal-canvas");
  const descriptor = suspensionPlotModalDescriptor();
  if (!modal || modal.hidden || !canvas || !descriptor || !state.kinematicsPayload?.available) return;
  const rect = canvas.getBoundingClientRect();
  const width = Math.max(460, Math.floor(rect.width));
  const height = Math.max(320, Math.floor(rect.height));
  const dpr = window.devicePixelRatio || 1;
  canvas.width = Math.floor(width * dpr);
  canvas.height = Math.floor(height * dpr);
  const ctx = canvas.getContext("2d");
  ctx.setTransform(dpr, 0, 0, dpr, 0, 0);
  ctx.clearRect(0, 0, width, height);
  const chart = drawKinematicChart(
    ctx,
    16,
    16,
    width - 32,
    height - 32,
    state.kinematicsPayload,
    descriptor,
    { focused: true, hover: state.suspensionPlotModalHover, axles: visibleGeometryAxles() },
  );
  state.suspensionPlotModalScene = chart ? { charts: [chart] } : null;
}

function updateSuspensionPlotModalHover(event) {
  const hover = hitTestSuspensionPlotScene(
    event,
    state.suspensionPlotModalScene,
    document.getElementById("kinematic-plot-modal-canvas"),
  );
  const previous = state.suspensionPlotModalHover;
  const moved = hover && previous && (
    Math.abs(hover.pointerX - previous.pointerX) > 4
    || Math.abs(hover.pointerY - previous.pointerY) > 4
  );
  if ((previous?.id || null) !== (hover?.id || null) || moved) {
    state.suspensionPlotModalHover = hover;
    drawSuspensionPlotModal();
  } else if (hover) {
    state.suspensionPlotModalHover = hover;
  }
}

function hitTestSuspensionPlotScene(event, scene, canvas) {
  const point = pointerCanvasPointFor(event, canvas);
  if (!point || !scene) return null;
  const chart = scene.charts.find((item) => pointInRect(point, item.plot, 3));
  if (!chart) return null;
  const sample = nearestPlotSample(chart, point);
  if (!sample) return null;
  return {
    id: `${chart.key}:${sample.sampleKey}`,
    chartKey: chart.key,
    sampleKey: sample.sampleKey,
    pointerX: point.x,
    pointerY: point.y,
  };
}

function pointerCanvasPointFor(event, canvas) {
  if (!canvas) return null;
  const rect = canvas.getBoundingClientRect();
  return {
    x: event.clientX - rect.left,
    y: event.clientY - rect.top,
  };
}

function geometryPlotDescriptorMap() {
  const descriptors = new Map(DEFAULT_KINEMATIC_CURVES.map((item) => [item.id, item]));
  kinematicCurveDescriptors(state.kinematicsPayload).forEach((item) => descriptors.set(item.id, item));
  return descriptors;
}

function descriptorXAxisId(descriptor) {
  if (descriptor?.x_id) return descriptor.x_id;
  return String(descriptor?.id || "").startsWith("roll_") ? "roll_deg" : "jounce_mm";
}

function geometryXAxisOptions(payload = state.kinematicsPayload) {
  const axisIds = new Set();
  Object.keys(payload?.x_axes || {}).forEach((key) => axisIds.add(key));
  DEFAULT_KINEMATIC_CURVES.forEach((item) => axisIds.add(item.x_id || "jounce_mm"));
  return [...axisIds]
    .filter(Boolean)
    .map((id) => ({
      id,
      label: id === "roll_deg" ? "Roll" : id === "jounce_mm" ? "Jounce" : humanizeToken(id),
      unit: id === "roll_deg" ? "deg" : id === "jounce_mm" ? "mm" : "",
    }))
    .sort((left, right) => (left.id === "jounce_mm" ? -1 : right.id === "jounce_mm" ? 1 : left.label.localeCompare(right.label)));
}

function geometryXAxisOption(id) {
  return geometryXAxisOptions().find((item) => item.id === id) || { id, label: humanizeToken(id), unit: "" };
}

function geometryPlotKey(plot) {
  return `${plot.x}:${plot.y}`;
}

function normalizeGeometryPlotSelection(selection, descriptorMap) {
  if (typeof selection === "string") {
    const descriptor = descriptorMap.get(selection);
    return descriptor ? { x: descriptorXAxisId(descriptor), y: selection } : null;
  }
  if (!selection || typeof selection !== "object") return null;
  const y = String(selection.y || selection.id || "");
  const descriptor = descriptorMap.get(y);
  if (!descriptor) return null;
  const descriptorX = descriptorXAxisId(descriptor);
  const x = String(selection.x || descriptorX);
  if (descriptorX !== x) return { x: descriptorX, y };
  return { x, y };
}

function cleanGeometryPlotSelections() {
  const descriptorMap = geometryPlotDescriptorMap();
  const seen = new Set();
  const selected = [];
  state.geometryPlotSelections.forEach((selection) => {
    const plot = normalizeGeometryPlotSelection(selection, descriptorMap);
    if (!plot) return;
    const key = geometryPlotKey(plot);
    if (seen.has(key) || selected.length >= MAX_GEOMETRY_PLOTS) return;
    seen.add(key);
    selected.push(plot);
  });
  state.geometryPlotSelections = selected;
  return descriptorMap;
}

function geometryPlotDescriptors() {
  const descriptorMap = cleanGeometryPlotSelections();
  return state.geometryPlotSelections
    .map((plot) => {
      const yDescriptor = descriptorMap.get(plot.y);
      if (!yDescriptor) return null;
      const xAxis = geometryXAxisOption(plot.x);
      const yLabel = yDescriptor.y_label || yDescriptor.label || humanizeKinematicCurve(yDescriptor.id);
      return {
        id: geometryPlotKey(plot),
        x_id: xAxis.id,
        x_label: xAxis.label,
        x_unit: xAxis.unit,
        y_id: yDescriptor.id,
        y_label: yLabel,
        y_unit: yDescriptor.unit || inferCurveUnit(yDescriptor.id),
        label: `${yLabel} vs ${xAxis.label}`,
        source_plot: yDescriptor.source_plot,
      };
    })
    .filter(Boolean);
}

function kinematicPayloadHasCurve(payload, key) {
  return ["front", "rear"].some((axle) => {
    const curve = payload?.axles?.[axle]?.curves?.[key];
    return Array.isArray(curve) && curve.length > 1;
  });
}

function renderGeometryPlotControls() {
  const panel = document.getElementById("geometry-plot-panel");
  if (!panel || panel.hidden) return;
  const descriptorMap = cleanGeometryPlotSelections();
  const descriptors = [...descriptorMap.values()];
  const selected = new Set(state.geometryPlotSelections.map(geometryPlotKey));
  const xSelect = document.getElementById("geometry-plot-x-axis");
  const ySelect = document.getElementById("geometry-plot-y-axis");
  const addButton = document.getElementById("geometry-add-plot-btn");
  const list = document.getElementById("geometry-plot-list");
  const xChoices = geometryXAxisOptions();
  if (!xChoices.some((item) => item.id === state.geometryPlotDraftX)) {
    state.geometryPlotDraftX = xChoices[0]?.id || "jounce_mm";
  }
  const yChoices = descriptors.filter((item) => descriptorXAxisId(item) === state.geometryPlotDraftX);
  if (!yChoices.some((item) => item.id === state.geometryPlotDraftY)) {
    state.geometryPlotDraftY = yChoices[0]?.id || "";
  }
  const draftKey = geometryPlotKey({ x: state.geometryPlotDraftX, y: state.geometryPlotDraftY });
  const draftAlreadySelected = selected.has(draftKey);
  const trayFull = state.geometryPlotSelections.length >= MAX_GEOMETRY_PLOTS;
  if (xSelect) {
    xSelect.innerHTML = xChoices.map((item) => (
      `<option value="${escapeHtml(item.id)}">${escapeHtml(item.label)}${item.unit ? ` (${escapeHtml(item.unit)})` : ""}</option>`
    )).join("");
    xSelect.value = state.geometryPlotDraftX;
  }
  if (ySelect) {
    ySelect.innerHTML = yChoices.length
      ? yChoices.map((item) => (
        `<option value="${escapeHtml(item.id)}">${escapeHtml(item.label || humanizeKinematicCurve(item.id))}</option>`
      )).join("")
      : '<option value="">No compatible signals</option>';
    ySelect.value = state.geometryPlotDraftY;
    ySelect.disabled = false;
  }
  if (addButton) {
    addButton.disabled = !yChoices.length || draftAlreadySelected || trayFull;
    addButton.title = !yChoices.length
      ? "No compatible signals for this x-axis"
      : draftAlreadySelected
        ? "This plot is already in the tray"
        : trayFull
          ? `Keep the tray to ${MAX_GEOMETRY_PLOTS} active plots`
          : "Add selected plot";
  }
  if (list) {
    list.innerHTML = geometryPlotDescriptors().map((item) => `
      <span class="geometry-plot-chip">
        ${escapeHtml(item.label || humanizeKinematicCurve(item.id))}
        <button type="button" data-geometry-plot-remove="${escapeHtml(item.id)}" aria-label="Remove ${escapeHtml(item.label || item.id)}">x</button>
      </span>
    `).join("");
  }
}

function persistGeometryPlotSelections() {
  localStorage.setItem("bobsim-geometry-plots", JSON.stringify(state.geometryPlotSelections));
}

function addGeometryPlotSelection() {
  const x = document.getElementById("geometry-plot-x-axis")?.value || state.geometryPlotDraftX;
  const y = document.getElementById("geometry-plot-y-axis")?.value || state.geometryPlotDraftY;
  if (!x || !y) return;
  const plot = { x, y };
  const key = geometryPlotKey(plot);
  if (state.geometryPlotSelections.some((item) => geometryPlotKey(item) === key)) return;
  if (state.geometryPlotSelections.length >= MAX_GEOMETRY_PLOTS) return;
  state.geometryPlotSelections.push(plot);
  persistGeometryPlotSelections();
  renderGeometryPlotControls();
  drawGeometryPlotPanel();
}

function removeGeometryPlotSelection(key) {
  const next = state.geometryPlotSelections.filter((item) => geometryPlotKey(item) !== key);
  if (next.length === state.geometryPlotSelections.length) return;
  state.geometryPlotSelections = next;
  persistGeometryPlotSelections();
  renderGeometryPlotControls();
  drawGeometryPlotPanel();
}

function drawGeometryPlotPanel() {
  const panel = document.getElementById("geometry-plot-panel");
  const canvas = document.getElementById("geometry-plot-canvas");
  if (!panel || panel.hidden || !canvas) {
    clearGeometryPlotScene();
    return;
  }
  const rect = canvas.getBoundingClientRect();
  const width = Math.max(420, Math.floor(rect.width));
  const height = Math.max(120, Math.floor(rect.height));
  const dpr = window.devicePixelRatio || 1;
  canvas.width = Math.floor(width * dpr);
  canvas.height = Math.floor(height * dpr);
  const ctx = canvas.getContext("2d");
  ctx.setTransform(dpr, 0, 0, dpr, 0, 0);
  ctx.clearRect(0, 0, width, height);
  const palette = canvasPalette();
  if (!state.kinematicsPayload) {
    drawCanvasText(ctx, "Solving current hardpoints...", width / 2, height / 2, {
      align: "center",
      color: palette.muted,
    });
    clearGeometryPlotScene();
    return;
  }
  if (!state.kinematicsPayload.available) {
    drawCanvasText(ctx, state.kinematicsPayload.warnings?.[0] || "Kinematics unavailable", width / 2, height / 2, {
      align: "center",
      color: palette.amber,
    });
    clearGeometryPlotScene();
    return;
  }
  const descriptors = geometryPlotDescriptors();
  if (!descriptors.length) {
    drawCanvasText(ctx, "Add a signal above", width / 2, height / 2, {
      align: "center",
      color: palette.muted,
    });
    clearGeometryPlotScene();
    return;
  }
  const missingCurve = descriptors.find((descriptor) => !kinematicPayloadHasCurve(state.kinematicsPayload, descriptor.y_id));
  if (missingCurve) {
    if (state.kinematicsStatus !== "loading" && state.kinematicsStatus !== "refreshing") {
      queueKinematicsRefresh({ force: true });
    }
    drawCanvasText(ctx, "Solving current hardpoints...", width / 2, height / 2, {
      align: "center",
      color: palette.muted,
    });
    clearGeometryPlotScene();
    return;
  }
  const columns = Math.min(descriptors.length, width > 760 ? 3 : width > 520 ? 2 : 1);
  const rows = Math.ceil(descriptors.length / columns);
  const gap = 10;
  const chartWidth = (width - gap * (columns + 1)) / columns;
  const chartHeight = (height - gap * (rows + 1)) / rows;
  const charts = [];
  descriptors.forEach((descriptor, index) => {
    const col = index % columns;
    const row = Math.floor(index / columns);
    const chart = drawKinematicChart(
      ctx,
      gap + col * (chartWidth + gap),
      gap + row * (chartHeight + gap),
      chartWidth,
      chartHeight,
      state.kinematicsPayload,
      descriptor,
      { hover: state.geometryPlotHover, axles: visibleGeometryAxles() },
    );
    if (chart) charts.push(chart);
  });
  state.geometryPlotScene = charts.length ? { charts } : null;
}

function updateGeometryPlotHover(event) {
  const hover = hitTestSuspensionPlotScene(
    event,
    state.geometryPlotScene,
    document.getElementById("geometry-plot-canvas"),
  );
  const previous = state.geometryPlotHover;
  const moved = hover && previous && (
    Math.abs(hover.pointerX - previous.pointerX) > 4
    || Math.abs(hover.pointerY - previous.pointerY) > 4
  );
  if ((previous?.id || null) !== (hover?.id || null) || moved) {
    state.geometryPlotHover = hover;
    drawGeometryPlotPanel();
  } else if (hover) {
    state.geometryPlotHover = hover;
  }
}

function handleGeometryPlotClick(event) {
  const hover = hitTestSuspensionPlotScene(
    event,
    state.geometryPlotScene,
    document.getElementById("geometry-plot-canvas"),
  );
  if (!hover) return;
  state.geometryPlotHover = hover;
  openSuspensionPlotModal(hover.chartKey);
  drawGeometryPlotPanel();
}

function syncPreviewModeControls(area = activeParameterArea()) {
  const controls = document.querySelector(".preview-controls");
  const geometryToggles = document.getElementById("geometry-axle-toggles");
  const geometryPlotPanel = document.getElementById("geometry-plot-panel");
  const geometryPlotSplitter = document.getElementById("geometry-plot-splitter");
  const canvas = document.getElementById("vehicle-canvas");
  const stage = document.querySelector(".visual-stage");
  const usesSpatialView = isSpatialPreviewArea(area);
  const usesMassScroll = area.id === "mass";
  const usesGeometryPlots = area.id === "hardpoints";
  const usesTireSurface = isSurfaceMapPreviewArea(area);
  if (controls) {
    controls.hidden = true;
    controls.style.display = "none";
  }
  if (geometryToggles) {
    geometryToggles.hidden = area.id !== "hardpoints";
    syncGeometryAxleToggles();
  }
  if (geometryPlotPanel) {
    geometryPlotPanel.hidden = !usesGeometryPlots;
    if (usesGeometryPlots) renderGeometryPlotControls();
    else clearGeometryPlotScene();
  }
  if (geometryPlotSplitter) {
    geometryPlotSplitter.hidden = !usesGeometryPlots;
    if (usesGeometryPlots) applyGeometryPlotHeight();
  }
  if (stage) {
    stage.classList.toggle("mass-scroll-stage", usesMassScroll);
    stage.classList.toggle("geometry-plot-stage", usesGeometryPlots);
  }
  if (canvas) {
    canvas.classList.toggle("diagnostic-canvas", !usesSpatialView);
    canvas.classList.toggle("mass-scroll-canvas", usesMassScroll);
    canvas.classList.toggle("tire-surface-canvas", usesTireSurface);
    if (!usesTireSurface) canvas.classList.remove("tire-surface-hot", "tire-surface-dragging");
    if (usesMassScroll) {
      const stageHeight = Math.max(360, stage?.clientHeight || canvas.clientHeight || 360);
      const toolbarHeight = document.querySelector(".preview-toolbar")?.getBoundingClientRect().height || 46;
      const contentHeight = Math.max(360, stageHeight - toolbarHeight - 28);
      const plotMinimumHeight = 900;
      const targetHeight = contentHeight * 2 + 64;
      canvas.style.height = `${Math.max(plotMinimumHeight, targetHeight)}px`;
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
  drawSuspensionPlotModal();
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
    tireFront: state.dark ? "#8ec7ff" : "#286fb7",
    tireRear: state.dark ? "#eba0c3" : "#b44f89",
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

function fitCanvasText(ctx, text, maxWidth, options = {}) {
  const raw = String(text ?? "");
  if (!raw) return "";
  ctx.save();
  ctx.font = `${options.weight || 700} ${options.size || 13}px Inter, sans-serif`;
  if (ctx.measureText(raw).width <= maxWidth) {
    ctx.restore();
    return raw;
  }
  const suffix = "...";
  let trimmed = raw;
  while (trimmed.length > 0 && ctx.measureText(`${trimmed}${suffix}`).width > maxWidth) {
    trimmed = trimmed.slice(0, -1);
  }
  ctx.restore();
  return trimmed ? `${trimmed}${suffix}` : suffix;
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
      drawArchitectureAxle3d(ctx, scene.points, viewport.axle, architecture[viewport.axle] || "direct", data, null, null, null, viewport);
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
  const sortedLinks = [...model.links].sort((a, b) => ((scene.map.get(a.from)?.depth || 0) + (scene.map.get(a.to)?.depth || 0))
    - ((scene.map.get(b.from)?.depth || 0) + (scene.map.get(b.to)?.depth || 0)));
  sortedLinks
    .filter((link) => link.role !== "pushrod")
    .forEach((link) => drawCylinder(ctx, scene.map.get(link.from), scene.map.get(link.to), {
      ...link,
      width: Math.max(2, link.width * 0.78),
      opacity: Math.min(link.opacity ?? 1, link.detail ? 0.8 : 0.9),
    }));
  sortedLinks
    .filter((link) => link.role === "pushrod")
    .forEach((link) => drawCylinder(ctx, scene.map.get(link.from), scene.map.get(link.to), link));
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
  const path = [axle, "actuation", "bellcrank", "order"];
  const choices = bellcrankOrderChoicesForPath(path, data) || ["rod", "shock"];
  const values = architectureOrderValuesForData(axle, data);
  const palette = canvasPalette();
  const drag = state.architectureDrag;
  choices.forEach((socketRole, index) => {
    const role = values[index] || socketRole;
    ["left", "right"].forEach((side) => {
      const point = points.find((item) => item.id === `${axle}-${side}-bellcrank-${socketRole}`);
      if (!point) return;
      const id = `architecture-${axle}-pickup-${index}`;
      const hotspot = {
        id,
        type: "bellcrank-pickup",
        axle,
        side,
        index,
        role,
        cx: point.x2,
        cy: point.y2,
        radius: 24,
        rect: { x: point.x2 - 24, y: point.y2 - 24, width: 48, height: 48 },
        view: viewport.view,
      };
      if (hotspots) hotspots.push(hotspot);
      const draggingThis = drag
        && drag.axle === axle
        && drag.side === side
        && Number(drag.index) === Number(index);
      const targetThis = drag?.active
        && drag.axle === axle
        && drag.side === side
        && Number(drag.targetIndex) === Number(index);
      const active = id === selectedId || id === hoverId;
      const radius = active ? 12 : 10;
      const color = bellcrankRoleColor(role);
      ctx.save();
      if (draggingThis || targetThis) {
        ctx.globalAlpha = draggingThis ? 0.45 : 0.38;
        ctx.fillStyle = colorWithAlpha(palette.muted, state.dark ? 0.18 : 0.14);
        ctx.strokeStyle = colorWithAlpha(palette.muted, 0.82);
        ctx.setLineDash([5, 4]);
      } else {
        ctx.fillStyle = colorWithAlpha(color, id === selectedId ? 0.36 : 0.24);
        ctx.strokeStyle = id === selectedId ? palette.amber : id === hoverId ? palette.blue : color;
      }
      ctx.lineWidth = id === selectedId ? 3 : 2;
      ctx.beginPath();
      ctx.arc(point.x2, point.y2, radius, 0, Math.PI * 2);
      ctx.fill();
      ctx.stroke();
      drawCanvasText(ctx, String(index + 1), point.x2, point.y2, {
        align: "center",
        size: 9,
        weight: 860,
        color: draggingThis || targetThis ? palette.muted : palette.ink,
      });
      drawCanvasText(ctx, humanizeToken(role), point.x2 + 14, point.y2 - 13, {
        size: 9,
        weight: 760,
        color: draggingThis || targetThis ? palette.muted : palette.ink,
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
    {
      title: "Downforce",
      table: aero.downforce_table_n,
      zKey: "downforce_n",
      unit: "N",
      color: palette.green,
    },
    {
      title: "Drag",
      table: aero.drag_table_n,
      zKey: "drag_n",
      unit: "N",
      color: palette.red,
    },
    {
      title: "Pitch moment",
      table: aero.my_table_nm,
      zKey: "pitch_moment_nm",
      unit: "Nm",
      color: palette.amber,
    },
    {
      title: "Yaw moment",
      table: aero.mz_table_nm,
      zKey: "yaw_moment_nm",
      unit: "Nm",
      color: palette.magenta,
    },
  ];
  const gap = 14;
  const top = 76;
  const panelWidth = (width - 56 - gap) / 2;
  const panelHeight = (height - top - 28 - gap) / 2;
  const surfacePanels = [];
  panels.forEach((panelDef, index) => {
    const col = index % 2;
    const row = Math.floor(index / 2);
    const rows = aeroSurfaceRowsFromTable(
      panelDef.table,
      aero.front_ride_height_grid_m,
      aero.rear_ride_height_grid_m,
      panelDef.zKey,
    );
    surfacePanels.push(drawTireSurfacePanel(
      ctx,
      28 + col * (panelWidth + gap),
      top + row * (panelHeight + gap),
      panelWidth,
      panelHeight,
      panelDef.title,
      [{
        label: `${panelDef.title} map`,
        shortLabel: panelDef.title,
        color: panelDef.color,
        rows,
        xKey: "front_ride_height_m",
        yKey: "rear_ride_height_m",
        zKey: panelDef.zKey,
      }],
      "FRH m",
      "RRH m",
      `${panelDef.title} ${panelDef.unit}`,
      { emptyMessage: "No aero map data" },
    ));
  });
  state.tireSurfaceScene = {
    panels: surfacePanels.filter(Boolean),
  };
}

function aeroSurfaceRowsFromTable(table, xGrid, yGrid, zKey) {
  if (!Array.isArray(table) || !table.length) return [];
  const xValues = Array.isArray(xGrid) ? xGrid : [];
  const yValues = Array.isArray(yGrid) ? yGrid : [];
  return table
    .map((row, rowIndex) => {
      if (!Array.isArray(row)) return null;
      const rearRideHeight = Number(yValues[rowIndex] ?? rowIndex);
      const points = row
        .map((value, colIndex) => {
          const frontRideHeight = Number(xValues[colIndex] ?? colIndex);
          const z = Number(value);
          if (!Number.isFinite(frontRideHeight) || !Number.isFinite(rearRideHeight) || !Number.isFinite(z)) return null;
          return {
            front_ride_height_m: frontRideHeight,
            rear_ride_height_m: rearRideHeight,
            [zKey]: z,
          };
        })
        .filter(Boolean);
      return points.length
        ? {
            rear_ride_height_m: rearRideHeight,
            points,
          }
        : null;
    })
    .filter(Boolean);
}

function drawHeatmapPanel(ctx, x, y, width, height, title, table, xGrid, yGrid, unit) {
  const palette = canvasPalette();
  drawPanel(ctx, x, y, width, height, state.dark ? "rgba(23,30,37,0.92)" : "rgba(255,255,255,0.94)");
  drawCanvasText(ctx, title, x + 12, y + 17, { size: 13, weight: 780 });
  if (!Array.isArray(table) || !table.length) {
    drawCanvasText(ctx, "No map", x + width / 2, y + height / 2, { align: "center", color: palette.muted });
    return;
  }
  const range = finiteRange(table.flat());
  const min = range?.min ?? 0;
  const max = range?.max ?? 0;
  drawCanvasText(ctx, `${formatNumber(min)} to ${formatNumber(max)} ${unit}`, x + width - 12, y + 17, {
    size: 11,
    weight: 650,
    align: "right",
    color: palette.muted,
  });
  const rows = table.length;
  const cols = finiteMax(table.map((row) => Array.isArray(row) ? row.length : 0), 0);
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
  const activeSubsystem = activePowertrainSubsystemId();
  drawCanvasText(ctx, "Powertrain", 28, 30, { size: 18, weight: 780 });
  drawCanvasText(ctx, profile.label, 28, 52, {
    size: 12,
    weight: 650,
    color: palette.muted,
  });

  const diagramTop = 82;
  const diagramHeight = Math.min(300, Math.max(220, height * 0.42));
  drawPowertrainArchitecture(ctx, 28, diagramTop, width - 56, diagramHeight, data, activeSubsystem);

  const metricTop = diagramTop + diagramHeight + 16;
  const metricGap = 12;
  const metricWidth = (width - 56 - metricGap * 3) / 4;
  const activeEntries = powertrainSubsystemEntries(explicit, activeSubsystem);
  [
    ["Selected", powertrainSubsystemLabel(activeSubsystem)],
    ["Maturity", humanizeToken(profile.status)],
    ["Inputs", `${activeEntries.length} scalar${activeEntries.length === 1 ? "" : "s"}`],
    ["Loop", activeSubsystem === "pVCU" ? "Off-loop control" : "Main path"],
  ].forEach(([label, value], index) => {
    drawDiagnosticTile(ctx, 28 + index * (metricWidth + metricGap), metricTop, metricWidth, 78, label, value);
  });

  drawPowertrainStats(ctx, width, height, activeEntries, metricTop + 98, activeSubsystem);
}

function activePowertrainSubsystemId() {
  return POWERTRAIN_SUBSYSTEMS.some((subsystem) => subsystem.id === state.activePowertrainSubsystem)
    ? state.activePowertrainSubsystem
    : "pBattery";
}

function powertrainSubsystemLabel(id) {
  return POWERTRAIN_OBJECT_LABELS[id] || humanizeToken(id);
}

function drawPowertrainArchitecture(ctx, x, y, width, height, data, activeSubsystem) {
  const palette = canvasPalette();
  const fill = state.dark ? "rgba(20, 27, 35, 0.92)" : "rgba(255, 255, 255, 0.96)";
  drawPanel(ctx, x, y, width, height, fill);
  drawCanvasText(ctx, "Architecture", x + 14, y + 18, { size: 13, weight: 800 });
  drawCanvasText(ctx, "VCU", x + width - 14, y + 18, {
    size: 11,
    weight: 760,
    align: "right",
    color: palette.muted,
  });

  const nodes = powertrainMainLoopNodes(data);
  const nodeWidth = clamp((width - 68 - 14 * (nodes.length - 1)) / nodes.length, 64, 136);
  const nodeHeight = clamp(height * 0.33, 74, 92);
  const gap = Math.max(12, (width - 68 - nodeWidth * nodes.length) / Math.max(1, nodes.length - 1));
  const totalWidth = nodeWidth * nodes.length + gap * (nodes.length - 1);
  const centerY = y + height * 0.64;
  const startX = x + width / 2 - totalWidth / 2 + nodeWidth / 2;
  nodes.forEach((node, index) => {
    node.cx = startX + index * (nodeWidth + gap);
    node.cy = centerY;
    node.width = nodeWidth;
    node.height = nodeHeight;
  });

  const vcu = {
    id: "pVCU",
    label: "VCU",
    meta: powertrainNodeMetric(data, "pVCU"),
    color: palette.amber,
    cx: (nodes[1].cx + nodes[2].cx) / 2,
    cy: y + Math.max(66, height * 0.25),
    width: clamp(nodeWidth * 0.95, 76, 116),
    height: 58,
  };

  nodes.forEach((node, index) => {
    if (index > 0) {
      const previous = nodes[index - 1];
      drawPowertrainConnection(
        ctx,
        previous.cx + previous.width / 2,
        previous.cy,
        node.cx - node.width / 2,
        node.cy,
        palette.blue,
      );
    }
  });

  const driveline = nodes[nodes.length - 1];
  const splitX = Math.min(x + width - 64, driveline.cx + driveline.width / 2 + Math.max(38, gap * 0.72));
  const wheelX = Math.min(x + width - 28, splitX + 36);
  const wheelY = [centerY - Math.min(48, height * 0.18), centerY + Math.min(48, height * 0.18)];
  drawPowertrainConnection(ctx, driveline.cx + driveline.width / 2, centerY, splitX, centerY, palette.green, {
    arrow: false,
  });
  wheelY.forEach((yPos) => {
    drawPowertrainConnection(ctx, splitX, centerY, wheelX - 20, yPos, palette.green, { arrow: false });
    drawWheelGlyph(ctx, wheelX, yPos, 20, 0, palette.green);
  });

  const signalTargets = [nodes[1], nodes[2], nodes[3]];
  signalTargets.forEach((node) => {
    drawPowertrainConnection(ctx, vcu.cx, vcu.cy + vcu.height / 2, node.cx, node.cy - node.height / 2, palette.amber, {
      dashed: true,
      arrow: false,
      width: 1.6,
    });
  });

  nodes.forEach((node) => drawPowertrainNode(ctx, node, activeSubsystem === node.id));
  drawPowertrainNode(ctx, vcu, activeSubsystem === "pVCU");
}

function powertrainMainLoopNodes(data) {
  return POWERTRAIN_MAIN_LOOP.map((id) => ({
    id,
    label: powertrainSubsystemLabel(id),
    meta: powertrainNodeMetric(data, id),
    color: powertrainSubsystemColor(id),
  }));
}

function powertrainSubsystemColor(id) {
  const palette = canvasPalette();
  return {
    pBattery: palette.green,
    pVCU: palette.amber,
    pInverter: palette.blue,
    pMotor: palette.magenta,
    pDriveline: palette.tireRear,
  }[id] || palette.blue;
}

function powertrainNodeMetric(data, id) {
  const block = powertrainSubsystemBlock(data, id);
  if (id === "pBattery") {
    const ns = Number(block.Ns);
    const np = Number(block.Np);
    return Number.isFinite(ns) && Number.isFinite(np) ? `${ns}s x ${np}p` : "Pack";
  }
  if (id === "pVCU") return powertrainTorqueText(block.tau_max, "tau");
  if (id === "pInverter") return powertrainPowerText(block.P_max_mot);
  if (id === "pMotor") return powertrainTorqueText(block.T_peak, "peak");
  if (id === "pDriveline") {
    const ratio = Number(block.finalDriveRatio);
    return Number.isFinite(ratio) ? `${formatNumber(ratio)}:1` : "Final drive";
  }
  return "";
}

function powertrainSubsystemBlock(data, id) {
  const powertrain = explicitPowertrainData(data);
  const block = powertrain[id];
  return block && typeof block === "object" && !Array.isArray(block) ? block : {};
}

function powertrainPowerText(value) {
  const watts = Number(value);
  if (!Number.isFinite(watts)) return "Power";
  return Math.abs(watts) >= 1000 ? `${formatNumber(watts / 1000)} kW` : `${formatNumber(watts)} W`;
}

function powertrainTorqueText(value, prefix) {
  const torque = Number(value);
  return Number.isFinite(torque) ? `${prefix} ${formatNumber(torque)} N m` : "Torque";
}

function drawPowertrainConnection(ctx, x1, y1, x2, y2, color, options = {}) {
  ctx.save();
  ctx.strokeStyle = color;
  ctx.lineWidth = options.width || 3;
  ctx.lineCap = "round";
  ctx.lineJoin = "round";
  ctx.setLineDash(options.dashed ? [5, 5] : []);
  ctx.beginPath();
  ctx.moveTo(x1, y1);
  ctx.lineTo(x2, y2);
  ctx.stroke();
  ctx.setLineDash([]);
  if (options.arrow !== false) drawPowertrainArrowHead(ctx, x1, y1, x2, y2, color);
  ctx.restore();
}

function drawPowertrainArrowHead(ctx, x1, y1, x2, y2, color) {
  const angle = Math.atan2(y2 - y1, x2 - x1);
  const size = 8;
  ctx.fillStyle = color;
  ctx.beginPath();
  ctx.moveTo(x2, y2);
  ctx.lineTo(x2 - Math.cos(angle - 0.52) * size, y2 - Math.sin(angle - 0.52) * size);
  ctx.lineTo(x2 - Math.cos(angle + 0.52) * size, y2 - Math.sin(angle + 0.52) * size);
  ctx.closePath();
  ctx.fill();
}

function drawPowertrainNode(ctx, node, active) {
  const palette = canvasPalette();
  const x = node.cx - node.width / 2;
  const y = node.cy - node.height / 2;
  ctx.save();
  ctx.fillStyle = active
    ? colorWithAlpha(node.color, state.dark ? 0.18 : 0.12)
    : (state.dark ? "#141d26" : "#f8fafc");
  ctx.strokeStyle = active ? node.color : colorWithAlpha(palette.line, state.dark ? 0.82 : 0.9);
  ctx.lineWidth = active ? 2 : 1;
  ctx.beginPath();
  if (ctx.roundRect) ctx.roundRect(x, y, node.width, node.height, 7);
  else ctx.rect(x, y, node.width, node.height);
  ctx.fill();
  ctx.stroke();
  ctx.restore();

  const iconSize = Math.min(34, node.height * 0.4, node.width * 0.38);
  drawPowertrainIcon(ctx, node.id, node.cx, y + 26, iconSize, node.color);
  drawCanvasText(ctx, node.label, node.cx, y + node.height - 28, {
    align: "center",
    size: node.width < 80 ? 10 : 12,
    weight: 820,
  });
  drawCanvasText(ctx, node.meta, node.cx, y + node.height - 12, {
    align: "center",
    size: node.width < 80 ? 8 : 9,
    weight: 700,
    color: palette.muted,
  });
}

function drawPowertrainIcon(ctx, id, cx, cy, size, color) {
  if (id === "pBattery") drawPowertrainBatteryIcon(ctx, cx, cy, size, color);
  else if (id === "pInverter") drawPowertrainInverterIcon(ctx, cx, cy, size, color);
  else if (id === "pMotor") drawPowertrainMotorIcon(ctx, cx, cy, size, color);
  else if (id === "pDriveline") drawPowertrainDifferentialIcon(ctx, cx, cy, size, color);
  else drawPowertrainVcuIcon(ctx, cx, cy, size, color);
}

function drawPowertrainBatteryIcon(ctx, cx, cy, size, color) {
  const palette = canvasPalette();
  const w = size * 1.72;
  const h = size * 0.86;
  ctx.save();
  ctx.strokeStyle = palette.ink;
  ctx.fillStyle = state.dark ? "#182821" : "#ebf5ef";
  ctx.lineWidth = 1.4;
  ctx.fillRect(cx - w / 2, cy - h / 2, w, h);
  ctx.strokeRect(cx - w / 2, cy - h / 2, w, h);
  ctx.strokeRect(cx + w / 2, cy - h * 0.22, size * 0.16, h * 0.44);
  ctx.strokeStyle = color;
  ctx.lineWidth = 1.8;
  ctx.beginPath();
  ctx.moveTo(cx - size * 0.45, cy);
  ctx.lineTo(cx - size * 0.17, cy);
  ctx.moveTo(cx - size * 0.31, cy - size * 0.16);
  ctx.lineTo(cx - size * 0.31, cy + size * 0.16);
  ctx.moveTo(cx + size * 0.14, cy);
  ctx.lineTo(cx + size * 0.48, cy);
  ctx.stroke();
  ctx.restore();
}

function drawPowertrainInverterIcon(ctx, cx, cy, size, color) {
  const palette = canvasPalette();
  ctx.save();
  ctx.fillStyle = state.dark ? "#172331" : "#f0f3f8";
  ctx.strokeStyle = palette.ink;
  ctx.lineWidth = 1.4;
  ctx.fillRect(cx - size * 0.58, cy - size * 0.58, size * 1.16, size * 1.16);
  ctx.strokeRect(cx - size * 0.58, cy - size * 0.58, size * 1.16, size * 1.16);
  ctx.strokeStyle = color;
  ctx.lineWidth = 1.8;
  ctx.beginPath();
  ctx.moveTo(cx - size * 0.42, cy + size * 0.18);
  ctx.lineTo(cx - size * 0.14, cy - size * 0.2);
  ctx.lineTo(cx + size * 0.14, cy + size * 0.18);
  ctx.lineTo(cx + size * 0.42, cy - size * 0.2);
  ctx.stroke();
  drawCanvasText(ctx, "DC/AC", cx, cy + size * 0.45, {
    align: "center",
    size: Math.max(6, size * 0.22),
    weight: 800,
    color: palette.muted,
  });
  ctx.restore();
}

function drawPowertrainMotorIcon(ctx, cx, cy, size, color) {
  const palette = canvasPalette();
  ctx.save();
  ctx.fillStyle = state.dark ? "#271b26" : "#fbf0f6";
  ctx.strokeStyle = color;
  ctx.lineWidth = 2;
  ctx.beginPath();
  ctx.arc(cx, cy, size * 0.56, 0, Math.PI * 2);
  ctx.fill();
  ctx.stroke();
  drawCanvasText(ctx, "M", cx, cy + 1, {
    align: "center",
    size: Math.max(12, size * 0.58),
    weight: 860,
    color: palette.ink,
  });
  ctx.restore();
}

function drawPowertrainDifferentialIcon(ctx, cx, cy, size, color) {
  const palette = canvasPalette();
  ctx.save();
  ctx.fillStyle = state.dark ? "#241d28" : "#f4edf3";
  ctx.strokeStyle = palette.ink;
  ctx.lineWidth = 1.4;
  ctx.beginPath();
  ctx.ellipse(cx, cy, size * 0.58, size * 0.44, 0, 0, Math.PI * 2);
  ctx.fill();
  ctx.stroke();
  ctx.fillStyle = state.dark ? "#2e3338" : "#d2d7dc";
  ctx.beginPath();
  ctx.arc(cx, cy, size * 0.2, 0, Math.PI * 2);
  ctx.fill();
  ctx.stroke();
  ctx.strokeStyle = color;
  ctx.lineWidth = 1.8;
  ctx.beginPath();
  ctx.moveTo(cx - size * 0.42, cy);
  ctx.lineTo(cx + size * 0.42, cy);
  ctx.moveTo(cx, cy - size * 0.34);
  ctx.lineTo(cx, cy + size * 0.34);
  ctx.stroke();
  ctx.restore();
}

function drawPowertrainVcuIcon(ctx, cx, cy, size, color) {
  const palette = canvasPalette();
  const w = size * 1.34;
  const h = size * 0.92;
  ctx.save();
  ctx.fillStyle = state.dark ? "#2b2415" : "#fff7e8";
  ctx.strokeStyle = color;
  ctx.lineWidth = 1.7;
  ctx.beginPath();
  if (ctx.roundRect) ctx.roundRect(cx - w / 2, cy - h / 2, w, h, 5);
  else ctx.rect(cx - w / 2, cy - h / 2, w, h);
  ctx.fill();
  ctx.stroke();
  ctx.strokeStyle = colorWithAlpha(color, 0.78);
  ctx.lineWidth = 1.2;
  [-0.36, 0, 0.36].forEach((offset) => {
    ctx.beginPath();
    ctx.moveTo(cx - w / 2 - size * 0.12, cy + offset * h);
    ctx.lineTo(cx - w / 2, cy + offset * h);
    ctx.moveTo(cx + w / 2, cy + offset * h);
    ctx.lineTo(cx + w / 2 + size * 0.12, cy + offset * h);
    ctx.stroke();
  });
  drawCanvasText(ctx, "VCU", cx, cy + 1, {
    align: "center",
    size: Math.max(8, size * 0.28),
    weight: 860,
    color: palette.ink,
  });
  ctx.restore();
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
    : ["Battery", "VCU", "Inverter", "Motor", "Differential"];
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

function powertrainSubsystemEntries(powertrain, subsystemId) {
  const block = powertrain?.[subsystemId];
  return flattenedPowertrainEntries(block);
}

function drawDiagnosticTile(ctx, x, y, width, height, label, value) {
  const palette = canvasPalette();
  drawPanel(ctx, x, y, width, height, palette.surface);
  drawCanvasText(ctx, label, x + 12, y + 18, { size: 11, weight: 740, color: palette.muted });
  drawCanvasText(ctx, value, x + 12, y + 48, { size: 13, weight: 780 });
}

function drawPowertrainStats(ctx, width, height, entries, top, subsystemId) {
  const palette = canvasPalette();
  const panelX = 28;
  const panelY = top;
  const panelW = width - 56;
  const panelH = Math.max(110, height - top - 28);
  drawPanel(ctx, panelX, panelY, panelW, panelH, palette.surface);
  drawCanvasText(ctx, `${powertrainSubsystemLabel(subsystemId)} Parameters`, panelX + 14, panelY + 18, {
    size: 13,
    weight: 780,
  });
  if (!entries.length) {
    drawCanvasText(ctx, "No parameters exposed for this subsystem", panelX + panelW / 2, panelY + panelH / 2, {
      align: "center",
      color: palette.muted,
    });
    return;
  }
  const columns = panelW > 650 ? 3 : 2;
  const cellW = (panelW - 28 - 12 * (columns - 1)) / columns;
  entries.slice(0, columns * 4).forEach(([key, value], index) => {
    const col = index % columns;
    const row = Math.floor(index / columns);
    const x = panelX + 14 + col * (cellW + 12);
    const y = panelY + 48 + row * 42;
    drawCanvasText(ctx, humanizeToken(key), x, y, { size: 10, weight: 700, color: palette.muted });
    drawCanvasText(ctx, formatDisplayValue(value), x, y + 18, { size: 13, weight: 760 });
  });
  if (entries.length > columns * 4) {
    drawCanvasText(ctx, `+${entries.length - columns * 4} more`, panelX + panelW - 14, panelY + panelH - 16, {
      size: 10,
      weight: 760,
      align: "right",
      color: palette.muted,
    });
  }
}

function drawTirePreview(ctx, width, height, data) {
  const palette = canvasPalette();
  state.tireSurfaceScene = null;
  drawPreviewGrid(ctx, width, height);
  drawCanvasText(ctx, "Tires", 28, 30, { size: 18, weight: 780 });
  drawCanvasText(ctx, state.tirePayload?.model || `${data.front?.tire?.template || "front tire"} / ${data.rear?.tire?.template || "rear tire"}`, 28, 52, {
    size: 12,
    weight: 650,
    color: palette.muted,
  });

  if (state.activeTireTab !== "load-maps") {
    drawTireSetupPreview(ctx, width, height, data);
    return;
  }

  const chartX = 28;
  const chartW = width - chartX - 28;
  const chartGap = 12;
  const chartH = (height - 78 - 28 - chartGap) / 2;
  const chartW2 = (chartW - chartGap) / 2;
  const sides = state.tirePayload?.sides || [];
  const combinedFzLabel = `@ ${formatNumber(currentTireCombinedFz())} N`;
  const camberLabel = `IA ${formatSignedNumber(currentTireLoadCamberDeg())} deg`;
  const surfacePanels = [];
  surfacePanels.push(drawTireSurfacePanel(
    ctx,
    chartX,
    78,
    chartW2,
    chartH,
    `Pure Fx Load Map, ${camberLabel}`,
    pureLongitudinalLoadSurfaces(sides, palette),
    "kappa",
    "Fz N",
    "Fx N",
  ));
  surfacePanels.push(drawTireSurfacePanel(
    ctx,
    chartX + chartW2 + chartGap,
    78,
    chartW2,
    chartH,
    `Pure Fy Load Map, ${camberLabel}`,
    pureLateralLoadSurfaces(sides, palette),
    "alpha deg",
    "Fz N",
    "Fy N",
  ));
  surfacePanels.push(drawTireSurfacePanel(
    ctx,
    chartX,
    78 + chartH + chartGap,
    chartW2,
    chartH,
    `Combined Fx ${combinedFzLabel}, ${camberLabel}`,
    combinedFxSurfaces(sides, palette),
    "kappa",
    "alpha deg",
    "Fx N",
  ));
  surfacePanels.push(drawTireSurfacePanel(
    ctx,
    chartX + chartW2 + chartGap,
    78 + chartH + chartGap,
    chartW2,
    chartH,
    `Combined Fy ${combinedFzLabel}, ${camberLabel}`,
    combinedFySurfaces(sides, palette),
    "alpha deg",
    "kappa",
    "Fy N",
  ));
  state.tireSurfaceScene = {
    panels: surfacePanels.filter(Boolean),
  };
}

function drawTirePreviewError(ctx, width, height, error, data) {
  const palette = canvasPalette();
  state.tireSurfaceScene = null;
  drawPreviewGrid(ctx, width, height);
  drawCanvasText(ctx, "Tires", 28, 30, { size: 18, weight: 780 });
  drawCanvasText(ctx, `${data.front?.tire?.template || "front tire"} / ${data.rear?.tire?.template || "rear tire"}`, 28, 52, {
    size: 12,
    weight: 650,
    color: palette.muted,
  });
  const panelW = Math.min(520, width - 56);
  const panelH = 118;
  const panelX = (width - panelW) / 2;
  const panelY = (height - panelH) / 2;
  drawPanel(ctx, panelX, panelY, panelW, panelH, colorWithAlpha(palette.amber, state.dark ? 0.14 : 0.1));
  drawCanvasText(ctx, "Tire preview did not redraw", panelX + 18, panelY + 30, {
    size: 15,
    weight: 780,
    color: palette.ink,
  });
  drawCanvasText(ctx, String(error?.message || error || "Unknown tire preview error"), panelX + 18, panelY + 58, {
    size: 11,
    weight: 650,
    color: palette.muted,
  });
  drawCanvasText(ctx, "The current form values are still preserved.", panelX + 18, panelY + 84, {
    size: 11,
    weight: 650,
    color: palette.muted,
  });
}

function drawTireSetupPreview(ctx, width, height, data) {
  drawTireStancePanel(ctx, 28, 78, width - 56, height - 106, data);
}

function pureLongitudinalLoadSurfaces(sides, palette) {
  return sides.map((side) => ({
    label: tireSurfaceLayerLabel(side.side),
    shortLabel: humanizeToken(side.side),
    color: tireSurfaceLayerColor(side.side, palette),
    dash: tireSurfaceLayerDash(side.side),
    rows: tirePureSurfaceRowsAtCamber(
      side,
      "longitudinal_by_gamma",
      "longitudinal_by_fz",
      side.curves?.pure?.longitudinal || side.curves?.longitudinal,
      "kappa",
      "fz_n",
      "fx_n",
      side.fz_n,
    ),
    zDomainValues: tireGammaSurfaceZDomainValues(side.curves?.pure?.longitudinal_by_gamma, "fx_n"),
    xKey: "kappa",
    yKey: "fz_n",
    zKey: "fx_n",
  }));
}

function pureLateralLoadSurfaces(sides, palette) {
  return sides.map((side) => ({
    label: tireSurfaceLayerLabel(side.side),
    shortLabel: humanizeToken(side.side),
    color: tireSurfaceLayerColor(side.side, palette),
    dash: tireSurfaceLayerDash(side.side),
    rows: tirePureSurfaceRowsAtCamber(
      side,
      "lateral_by_gamma",
      "lateral_by_fz",
      side.curves?.pure?.lateral || side.curves?.lateral,
      "alpha_deg",
      "fz_n",
      "fy_n",
      side.fz_n,
    ),
    zDomainValues: tireGammaSurfaceZDomainValues(side.curves?.pure?.lateral_by_gamma, "fy_n"),
    xKey: "alpha_deg",
    yKey: "fz_n",
    zKey: "fy_n",
  }));
}

function combinedFxSurfaces(sides, palette) {
  return sides.map((side) => ({
    label: tireSurfaceLayerLabel(side.side),
    shortLabel: humanizeToken(side.side),
    color: tireSurfaceLayerColor(side.side, palette),
    dash: tireSurfaceLayerDash(side.side),
    rows: tireCombinedSurfaceRowsAtFz(
      side,
      "fx_surfaces_by_fz",
      "fx_surface",
      "fx_by_alpha",
      "kappa",
      "alpha_deg",
      "fx_n",
    ),
    zDomainValues: [
      ...tireCombinedForceMapZDomainValues(side.curves?.combined?.force_maps_by_gamma_fz, "fx_n"),
      ...tireCombinedSurfaceZDomainValues(side.curves?.combined?.fx_surfaces_by_fz, "fx_n"),
    ],
    xKey: "kappa",
    yKey: "alpha_deg",
    zKey: "fx_n",
  }));
}

function combinedFySurfaces(sides, palette) {
  return sides.map((side) => ({
    label: tireSurfaceLayerLabel(side.side),
    shortLabel: humanizeToken(side.side),
    color: tireSurfaceLayerColor(side.side, palette),
    dash: tireSurfaceLayerDash(side.side),
    rows: tireCombinedSurfaceRowsAtFz(
      side,
      "fy_surfaces_by_fz",
      "fy_surface",
      "fy_by_kappa",
      "alpha_deg",
      "kappa",
      "fy_n",
    ),
    zDomainValues: [
      ...tireCombinedForceMapZDomainValues(side.curves?.combined?.force_maps_by_gamma_fz, "fy_n"),
      ...tireCombinedSurfaceZDomainValues(side.curves?.combined?.fy_surfaces_by_fz, "fy_n"),
    ],
    xKey: "alpha_deg",
    yKey: "kappa",
    zKey: "fy_n",
  }));
}

function tireSurfaceLayerLabel(side) {
  return `${humanizeToken(side)} tire`;
}

function tireSurfaceLayerColor(side, palette) {
  if (side === "front") return palette.tireFront;
  if (side === "rear") return palette.tireRear;
  return palette.amber;
}

function tireSurfaceLayerDash(side) {
  return side === "rear" ? [5, 4] : [];
}

function tireCombinedSurfaceRowsAtFz(side, loadSurfaceKey, baseSurfaceKey, fallbackRowsKey, xKey, yKey, zKey) {
  const combined = side.curves?.combined || {};
  const forceRows = tireCombinedForceMapRowsAtFzAndCamber(side);
  if (forceRows.length) {
    return zKey === "fy_n"
      ? fySurfaceRowsFromForceMapRows(forceRows)
      : fxSurfaceRowsFromForceMapRows(forceRows);
  }
  const rows = interpolateTireSurfaceRowsByFz(combined[loadSurfaceKey], currentTireCombinedFz(), zKey);
  if (rows) return rows;
  return surfaceRowsFromCombinedSurface(combined[baseSurfaceKey], combined[fallbackRowsKey], xKey, yKey, zKey);
}

function tirePureSurfaceRowsAtCamber(side, gammaKey, loadKey, fallbackPoints, xKey, yKey, zKey, fallbackLoad) {
  const pure = side.curves?.pure || {};
  const camberRows = interpolateTireSurfaceRowsByGamma(pure[gammaKey], currentTireLoadCamberDeg(), zKey);
  if (camberRows) return camberRows;
  return surfaceRowsFromLoadCurves(pure[loadKey], fallbackPoints, xKey, yKey, zKey, fallbackLoad);
}

function interpolateTireSurfaceRowsByGamma(gammaSurfaces, gammaDeg, zKey) {
  const surfaces = (gammaSurfaces || [])
    .map((surface) => ({
      gammaDeg: Number(surface.gamma_deg),
      rows: Array.isArray(surface.rows) ? surface.rows : [],
    }))
    .filter((surface) => Number.isFinite(surface.gammaDeg) && surface.rows.length)
    .sort((left, right) => left.gammaDeg - right.gammaDeg);
  if (!surfaces.length) return null;
  const gamma = Number(gammaDeg) || 0;
  if (gamma <= surfaces[0].gammaDeg) return cloneTireSurfaceRows(surfaces[0].rows, zKey);
  const last = surfaces[surfaces.length - 1];
  if (gamma >= last.gammaDeg) return cloneTireSurfaceRows(last.rows, zKey);
  const upperIndex = surfaces.findIndex((surface) => surface.gammaDeg >= gamma);
  const lower = surfaces[Math.max(0, upperIndex - 1)];
  const upper = surfaces[upperIndex];
  const span = upper.gammaDeg - lower.gammaDeg;
  if (Math.abs(span) <= 1e-9) return cloneTireSurfaceRows(lower.rows, zKey);
  return interpolateTireSurfaceRows(lower.rows, upper.rows, (gamma - lower.gammaDeg) / span, zKey);
}

function tireCombinedForceMapRowsAtFzAndCamber(side) {
  const gammaMaps = (side.curves?.combined?.force_maps_by_gamma_fz || [])
    .map((surface) => ({
      gammaDeg: Number(surface.gamma_deg),
      rows: tireForceMapRowsAtFz(surface.maps, currentTireCombinedFz()),
    }))
    .filter((surface) => Number.isFinite(surface.gammaDeg) && surface.rows.length)
    .sort((left, right) => left.gammaDeg - right.gammaDeg);
  if (!gammaMaps.length) return [];
  const gamma = currentTireLoadCamberDeg();
  if (gamma <= gammaMaps[0].gammaDeg) return cloneTireForceMapRows(gammaMaps[0].rows);
  const last = gammaMaps[gammaMaps.length - 1];
  if (gamma >= last.gammaDeg) return cloneTireForceMapRows(last.rows);
  const upperIndex = gammaMaps.findIndex((surface) => surface.gammaDeg >= gamma);
  const lower = gammaMaps[Math.max(0, upperIndex - 1)];
  const upper = gammaMaps[upperIndex];
  const span = upper.gammaDeg - lower.gammaDeg;
  if (Math.abs(span) <= 1e-9) return cloneTireForceMapRows(lower.rows);
  return interpolateTireForceMapRows(lower.rows, upper.rows, (gamma - lower.gammaDeg) / span);
}

function tireForceMapRowsAtFz(forceMaps, fz) {
  const maps = (forceMaps || [])
    .map((map) => ({
      fzN: Number(map.fz_n),
      rows: normalizeTireForceMapRows(map.rows, Number(map.fz_n) || fz),
    }))
    .filter((map) => Number.isFinite(map.fzN) && map.rows.length)
    .sort((left, right) => left.fzN - right.fzN);
  if (!maps.length) return [];
  const load = Number(fz) || maps[0].fzN;
  if (load <= maps[0].fzN) return cloneTireForceMapRows(maps[0].rows);
  const last = maps[maps.length - 1];
  if (load >= last.fzN) return cloneTireForceMapRows(last.rows);
  const upperIndex = maps.findIndex((map) => map.fzN >= load);
  const lower = maps[Math.max(0, upperIndex - 1)];
  const upper = maps[upperIndex];
  const span = upper.fzN - lower.fzN;
  if (Math.abs(span) <= 1e-9) return cloneTireForceMapRows(lower.rows);
  return interpolateTireForceMapRows(lower.rows, upper.rows, (load - lower.fzN) / span);
}

function fxSurfaceRowsFromForceMapRows(rows) {
  return rows.map((row) => ({
    alpha_deg: row.alphaDeg,
    points: (row.points || []).map((point) => ({
      alpha_deg: point.alphaDeg,
      kappa: point.kappa,
      fz_n: point.fzN,
      fx_n: point.fxN,
    })),
  }));
}

function fySurfaceRowsFromForceMapRows(rows) {
  const columnCount = finiteMax(rows.map((row) => row.points?.length || 0), 0);
  return Array.from({ length: columnCount }, (_item, columnIndex) => {
    const points = rows
      .map((row) => row.points?.[columnIndex])
      .filter(Boolean)
      .map((point) => ({
        alpha_deg: point.alphaDeg,
        kappa: point.kappa,
        fz_n: point.fzN,
        fy_n: point.fyN,
      }));
    return {
      kappa: points[0]?.kappa,
      points,
    };
  }).filter((row) => row.points.length);
}

function interpolateTireSurfaceRowsByFz(loadSurfaces, fz, zKey) {
  const surfaces = (loadSurfaces || [])
    .map((surface) => ({
      fz: Number(surface.fz_n),
      rows: Array.isArray(surface.rows) ? surface.rows : [],
    }))
    .filter((surface) => Number.isFinite(surface.fz) && surface.rows.length)
    .sort((left, right) => left.fz - right.fz);
  if (!surfaces.length) return null;
  if (fz <= surfaces[0].fz) return cloneTireSurfaceRows(surfaces[0].rows, zKey, surfaces[0].fz);
  const last = surfaces[surfaces.length - 1];
  if (fz >= last.fz) return cloneTireSurfaceRows(last.rows, zKey, last.fz);
  const upperIndex = surfaces.findIndex((surface) => surface.fz >= fz);
  const lower = surfaces[Math.max(0, upperIndex - 1)];
  const upper = surfaces[upperIndex];
  const span = upper.fz - lower.fz;
  if (Math.abs(span) <= 1e-9) return cloneTireSurfaceRows(lower.rows, zKey, lower.fz);
  const t = (fz - lower.fz) / span;
  return lower.rows.map((row, rowIndex) => {
    const upperRow = upper.rows[rowIndex] || row;
    const lowerPoints = Array.isArray(row.points) ? row.points : [];
    const upperPoints = Array.isArray(upperRow.points) ? upperRow.points : [];
    return {
      ...row,
      fz_n: fz,
      points: lowerPoints.map((point, pointIndex) => {
        const upperPoint = upperPoints[pointIndex] || point;
        const z0 = Number(point[zKey]);
        const z1 = Number(upperPoint[zKey]);
        return {
          ...point,
          fz_n: fz,
          [zKey]: Number.isFinite(z0) && Number.isFinite(z1) ? z0 + (z1 - z0) * t : point[zKey],
        };
      }),
    };
  });
}

function interpolateTireSurfaceRows(lowerRows, upperRows, t, zKey) {
  return lowerRows.map((row, rowIndex) => {
    const upperRow = upperRows[rowIndex] || row;
    const lowerPoints = Array.isArray(row.points) ? row.points : [];
    const upperPoints = Array.isArray(upperRow.points) ? upperRow.points : [];
    const rowFz = Number(row.fz_n ?? upperRow.fz_n);
    return {
      ...row,
      fz_n: rowFz,
      points: lowerPoints.map((point, pointIndex) => {
        const upperPoint = upperPoints[pointIndex] || point;
        const z0 = Number(point[zKey]);
        const z1 = Number(upperPoint[zKey]);
        return {
          ...point,
          fz_n: Number(point.fz_n ?? rowFz),
          [zKey]: Number.isFinite(z0) && Number.isFinite(z1) ? z0 + (z1 - z0) * t : point[zKey],
        };
      }),
    };
  });
}

function cloneTireSurfaceRows(rows, zKey, fz = null) {
  return rows.map((row) => ({
    ...row,
    fz_n: Number.isFinite(Number(fz)) ? Number(fz) : row.fz_n,
    points: (row.points || []).map((point) => ({
      ...point,
      fz_n: Number.isFinite(Number(fz)) ? Number(fz) : point.fz_n,
      [zKey]: point[zKey],
    })),
  }));
}

function tireCombinedSurfaceZDomainValues(loadSurfaces, zKey) {
  return (loadSurfaces || [])
    .flatMap((surface) => surface.rows || [])
    .flatMap((row) => row.points || [])
    .map((point) => Number(point[zKey]))
    .filter(Number.isFinite);
}

function tireCombinedForceMapZDomainValues(gammaSurfaces, zKey) {
  return (gammaSurfaces || [])
    .flatMap((surface) => surface.maps || [])
    .flatMap((map) => map.rows || [])
    .flatMap((row) => row.points || [])
    .map((point) => Number(point[zKey]))
    .filter(Number.isFinite);
}

function tireGammaSurfaceZDomainValues(gammaSurfaces, zKey) {
  return (gammaSurfaces || [])
    .flatMap((surface) => surface.rows || [])
    .flatMap((row) => row.points || [])
    .map((point) => Number(point[zKey]))
    .filter(Number.isFinite);
}

function surfaceRowsFromLoadCurves(rows, fallbackPoints, xKey, yKey, zKey, fallbackLoad) {
  if (Array.isArray(rows) && rows.length) return rows;
  const points = Array.isArray(fallbackPoints) ? fallbackPoints : [];
  const load = Number(fallbackLoad);
  if (!points.length || !Number.isFinite(load)) return [];
  return [{
    [yKey]: load,
    points: points.map((point) => ({ ...point, [yKey]: load, [zKey]: Number(point[zKey]) })),
  }];
}

function surfaceRowsFromCombinedSurface(surface, fallbackRows, xKey, yKey, zKey) {
  if (Array.isArray(surface?.rows) && surface.rows.length) return surface.rows;
  if (!Array.isArray(fallbackRows)) return [];
  return fallbackRows.map((row) => ({
    ...row,
    points: (row.points || []).map((point) => ({
      ...point,
      [yKey]: Number(point[yKey] ?? row[yKey]),
      [xKey]: Number(point[xKey]),
      [zKey]: Number(point[zKey]),
    })),
  }));
}

function drawTireSurfacePanel(ctx, x, y, width, height, title, surfaces, xLabel, yLabel, zLabel, options = {}) {
  const palette = canvasPalette();
  const panel = { title, bounds: { x, y, width, height } };
  drawPanel(ctx, x, y, width, height, palette.surface);
  drawCanvasText(ctx, fitCanvasText(ctx, title, Math.max(80, width - 58), { size: 13, weight: 780 }), x + 12, y + 17, { size: 13, weight: 780 });
  drawTireSurfaceDragIndicator(ctx, x + width - 24, y + 18);
  const usableSurfaces = (surfaces || [])
    .map((surface) => ({
      ...surface,
      rows: normalizeSurfaceRows(surface.rows, surface.xKey, surface.yKey, surface.zKey),
    }))
    .filter((surface) => surface.rows.length);
  if (!usableSurfaces.length) {
    drawCanvasText(ctx, options.emptyMessage || "No surface data", x + width / 2, y + height / 2, {
      align: "center",
      color: palette.muted,
    });
    return null;
  }
  drawTireSurfaceLegend(ctx, usableSurfaces, x + 12, y + 36, Math.max(80, width - 64));

  const xValues = [];
  const yValues = [];
  const zValues = [];
  usableSurfaces.forEach((surface) => {
    surface.rows.forEach((row) => {
      row.points.forEach((point) => {
        xValues.push(point.x);
        yValues.push(point.y);
        zValues.push(point.z);
      });
    });
    if (Array.isArray(surface.zDomainValues)) {
      surface.zDomainValues.forEach((value) => zValues.push(value));
    }
  });
  const xDomain = plotDomain(xValues, { padFraction: 0.02 });
  const yDomain = plotDomain(yValues, { padFraction: 0.02 });
  const zDomain = plotDomain(zValues, { includeZero: true, padFraction: 0.08 });
  const plot = {
    x: x + 42,
    y: y + 50,
    width: Math.max(84, width - 62),
    height: Math.max(72, height - 84),
  };
  panel.plot = plot;
  const project = tireSurfaceProjector(plot, xDomain, yDomain, zDomain);

  ctx.save();
  clipTireSurfacePlot(ctx, plot);
  usableSurfaces.forEach((surface, surfaceIndex) => {
    drawTireSurfaceWireframe(ctx, surface, project, surfaceIndex);
  });
  drawTireSurfaceAxes(ctx, project, xDomain, yDomain, zDomain, { x: xLabel, y: yLabel, z: zLabel });
  ctx.restore();
  drawTireSurfacePlotFrame(ctx, plot);
  drawCanvasText(ctx, `${formatNumber(zDomain[0])} to ${formatNumber(zDomain[1])}`, x + width - 12, y + height - 30, {
    size: 10,
    weight: 650,
    align: "right",
    color: palette.muted,
  });
  return panel;
}

function drawTireSurfaceLegend(ctx, surfaces, x, y, maxWidth) {
  const palette = canvasPalette();
  const items = surfaces.slice(0, 4);
  if (!items.length) return;
  ctx.save();
  ctx.font = "760 10px Inter, sans-serif";
  const swatchW = 18;
  const labelGap = 6;
  const itemGap = 16;
  const itemWidth = (surface, useShortLabel = false) => {
    const label = String((useShortLabel && surface.shortLabel) || surface.label || "");
    return swatchW + labelGap + ctx.measureText(label).width;
  };
  const fullWidth = items.reduce((total, surface, index) => (
    total + itemWidth(surface) + (index ? itemGap : 0)
  ), 0);
  const useShortLabels = fullWidth > maxWidth;
  let cursorX = x;
  items.forEach((surface, index) => {
    const label = String((useShortLabels && surface.shortLabel) || surface.label || `Layer ${index + 1}`);
    const width = swatchW + labelGap + ctx.measureText(label).width;
    if (cursorX + width > x + maxWidth && cursorX > x) return;
    ctx.strokeStyle = surface.color || palette.blue;
    ctx.lineWidth = 3.4;
    ctx.lineCap = "round";
    ctx.setLineDash(surface.dash || []);
    ctx.beginPath();
    ctx.moveTo(cursorX, y);
    ctx.lineTo(cursorX + swatchW, y);
    ctx.stroke();
    ctx.setLineDash([]);
    drawCanvasText(ctx, label, cursorX + swatchW + labelGap, y, {
      size: 10,
      weight: 760,
      color: palette.ink,
    });
    cursorX += width + itemGap;
  });
  ctx.restore();
}

function normalizeSurfaceRows(rows, xKey, yKey, zKey) {
  if (!Array.isArray(rows)) return [];
  return rows
    .map((row) => ({
      points: (row.points || [])
        .map((point) => ({
          x: Number(point[xKey]),
          y: Number(point[yKey] ?? row[yKey]),
          z: Number(point[zKey]),
        }))
        .filter((point) => Number.isFinite(point.x) && Number.isFinite(point.y) && Number.isFinite(point.z)),
    }))
    .filter((row) => row.points.length);
}

function tireSurfaceProjector(plot, xDomain, yDomain, zDomain) {
  const panLimit = tireSurfacePanLimit(plot);
  const center = {
    x: plot.x + plot.width * 0.5 + clamp(state.tireSurfacePanX, -panLimit.x, panLimit.x),
    y: plot.y + plot.height * 0.64 + clamp(state.tireSurfacePanY, -panLimit.y, panLimit.y),
  };
  const scale = Math.min(plot.width * 0.58, plot.height * 0.62) * state.tireSurfaceZoom;
  const yawCos = Math.cos(state.tireSurfaceYaw);
  const yawSin = Math.sin(state.tireSurfaceYaw);
  const pitchCos = Math.cos(state.tireSurfacePitch);
  const pitchSin = Math.sin(state.tireSurfacePitch);
  const xSpan = Math.max(1e-9, xDomain[1] - xDomain[0]);
  const ySpan = Math.max(1e-9, yDomain[1] - yDomain[0]);
  const zSpan = Math.max(1e-9, zDomain[1] - zDomain[0]);
  return (point) => {
    const nx = (point.x - xDomain[0]) / xSpan;
    const ny = (point.y - yDomain[0]) / ySpan;
    const nz = (point.z - zDomain[0]) / zSpan;
    const localX = (nx - 0.5) * 1.18;
    const localY = (ny - 0.5) * 0.96;
    const localZ = nz * 0.9;
    const yawX = localX * yawCos - localY * yawSin;
    const yawY = localX * yawSin + localY * yawCos;
    const pitchY = yawY * pitchCos - localZ * pitchSin;
    return {
      x: center.x + yawX * scale,
      y: center.y + pitchY * scale,
    };
  };
}

function clipTireSurfacePlot(ctx, plot) {
  ctx.beginPath();
  ctx.rect(plot.x, plot.y, plot.width, plot.height);
  ctx.clip();
}

function drawTireSurfacePlotFrame(ctx, plot) {
  const palette = canvasPalette();
  ctx.save();
  ctx.strokeStyle = colorWithAlpha(palette.line, state.dark ? 0.38 : 0.5);
  ctx.lineWidth = 1;
  ctx.strokeRect(plot.x + 0.5, plot.y + 0.5, plot.width - 1, plot.height - 1);
  ctx.restore();
}

function drawTireSurfaceAxes(ctx, project, xDomain, yDomain, zDomain, labels) {
  const palette = canvasPalette();
  const origin = {
    x: surfaceOriginValue(xDomain),
    y: surfaceOriginValue(yDomain),
    z: surfaceOriginValue(zDomain),
  };
  const planeCorners = [
    project({ x: xDomain[0], y: yDomain[0], z: origin.z }),
    project({ x: xDomain[1], y: yDomain[0], z: origin.z }),
    project({ x: xDomain[1], y: yDomain[1], z: origin.z }),
    project({ x: xDomain[0], y: yDomain[1], z: origin.z }),
  ];
  ctx.strokeStyle = colorWithAlpha(palette.line, state.dark ? 0.24 : 0.36);
  ctx.lineWidth = 1;
  ctx.beginPath();
  planeCorners.forEach((corner, index) => {
    if (index === 0) ctx.moveTo(corner.x, corner.y);
    else ctx.lineTo(corner.x, corner.y);
  });
  ctx.closePath();
  ctx.stroke();
  for (let index = 1; index < 4; index += 1) {
    const t = index / 4;
    const xGrid = xDomain[0] + (xDomain[1] - xDomain[0]) * t;
    const yGrid = yDomain[0] + (yDomain[1] - yDomain[0]) * t;
    const xa = project({ x: xGrid, y: yDomain[0], z: origin.z });
    const xb = project({ x: xGrid, y: yDomain[1], z: origin.z });
    const ya = project({ x: xDomain[0], y: yGrid, z: origin.z });
    const yb = project({ x: xDomain[1], y: yGrid, z: origin.z });
    ctx.strokeStyle = colorWithAlpha(palette.line, state.dark ? 0.24 : 0.42);
    ctx.beginPath();
    ctx.moveTo(xa.x, xa.y);
    ctx.lineTo(xb.x, xb.y);
    ctx.moveTo(ya.x, ya.y);
    ctx.lineTo(yb.x, yb.y);
    ctx.stroke();
  }
  const x0 = project({ x: xDomain[0], y: origin.y, z: origin.z });
  const x1 = project({ x: xDomain[1], y: origin.y, z: origin.z });
  const y0 = project({ x: origin.x, y: yDomain[0], z: origin.z });
  const y1 = project({ x: origin.x, y: yDomain[1], z: origin.z });
  const z0 = project({ x: origin.x, y: origin.y, z: zDomain[0] });
  const z1 = project({ x: origin.x, y: origin.y, z: zDomain[1] });
  ctx.strokeStyle = colorWithAlpha(palette.muted, state.dark ? 0.72 : 0.78);
  ctx.lineWidth = 1.4;
  ctx.beginPath();
  ctx.moveTo(x0.x, x0.y);
  ctx.lineTo(x1.x, x1.y);
  ctx.moveTo(y0.x, y0.y);
  ctx.lineTo(y1.x, y1.y);
  ctx.moveTo(z0.x, z0.y);
  ctx.lineTo(z1.x, z1.y);
  ctx.stroke();

  drawSurfaceAxisLabel(ctx, labels.x, x1, axisLabelOffset(x0, x1, 13));
  drawSurfaceAxisLabel(ctx, labels.y, y1, axisLabelOffset(y0, y1, -13));
  drawSurfaceAxisLabel(ctx, labels.z, z1, { dx: 0, dy: -12 }, "center");
}

function surfaceOriginValue(domain) {
  if (domain[0] <= 0 && domain[1] >= 0) return 0;
  return Math.abs(domain[0]) < Math.abs(domain[1]) ? domain[0] : domain[1];
}

function axisLabelOffset(start, end, distance) {
  const dx = end.x - start.x;
  const dy = end.y - start.y;
  const length = Math.max(1e-9, Math.hypot(dx, dy));
  return {
    dx: (-dy / length) * distance,
    dy: (dx / length) * distance,
  };
}

function drawSurfaceAxisLabel(ctx, label, point, { dx = 0, dy = 0 } = {}, align = "left") {
  const palette = canvasPalette();
  const text = String(label || "");
  if (!text) return;
  ctx.save();
  ctx.font = "760 9px Inter, sans-serif";
  const textWidth = ctx.measureText(text).width;
  const padX = 5;
  const boxW = textWidth + padX * 2;
  const boxH = 16;
  const x = align === "center"
    ? point.x + dx - boxW / 2
    : align === "right"
      ? point.x + dx - boxW
      : point.x + dx;
  const y = point.y + dy - boxH / 2;
  ctx.fillStyle = colorWithAlpha(palette.surface, state.dark ? 0.88 : 0.92);
  ctx.strokeStyle = colorWithAlpha(palette.line, state.dark ? 0.62 : 0.72);
  ctx.lineWidth = 1;
  ctx.beginPath();
  if (ctx.roundRect) ctx.roundRect(x, y, boxW, boxH, 4);
  else ctx.rect(x, y, boxW, boxH);
  ctx.fill();
  ctx.stroke();
  ctx.restore();
  drawCanvasText(ctx, text, x + padX, y + boxH / 2, {
    size: 9,
    weight: 760,
    color: palette.muted,
  });
}

function drawTireSurfaceDragIndicator(ctx, x, y) {
  const palette = canvasPalette();
  ctx.save();
  ctx.strokeStyle = colorWithAlpha(palette.muted, state.dark ? 0.72 : 0.82);
  ctx.fillStyle = colorWithAlpha(palette.muted, state.dark ? 0.72 : 0.82);
  ctx.lineWidth = 1.4;
  ctx.lineCap = "round";
  ctx.beginPath();
  ctx.arc(x, y, 8, -0.25 * Math.PI, 1.25 * Math.PI);
  ctx.stroke();
  const arrow = projectArrowHead(x - 5.7, y + 5.7, -0.2);
  ctx.beginPath();
  ctx.moveTo(arrow.tip.x, arrow.tip.y);
  ctx.lineTo(arrow.left.x, arrow.left.y);
  ctx.moveTo(arrow.tip.x, arrow.tip.y);
  ctx.lineTo(arrow.right.x, arrow.right.y);
  ctx.stroke();
  ctx.beginPath();
  ctx.arc(x, y, 2.1, 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();
}

function projectArrowHead(x, y, angle) {
  const size = 4;
  return {
    tip: { x, y },
    left: { x: x + Math.cos(angle + 2.4) * size, y: y + Math.sin(angle + 2.4) * size },
    right: { x: x + Math.cos(angle - 2.4) * size, y: y + Math.sin(angle - 2.4) * size },
  };
}

function drawTireSurfaceWireframe(ctx, surface, project, surfaceIndex) {
  const color = surface.color || canvasPalette().blue;
  const rows = (surface.rows || []).filter((row) => Array.isArray(row.points) && row.points.length);
  if (!rows.length) return;
  const rowStep = Math.max(1, Math.floor(rows.length / 9));
  const columnCount = finiteMax(rows.map((row) => row.points.length), 0);
  if (!Number.isFinite(columnCount) || columnCount <= 0) return;
  const columnStep = Math.max(1, Math.floor(columnCount / 9));
  ctx.save();
  ctx.lineJoin = "round";
  ctx.lineCap = "round";
  ctx.lineWidth = surfaceIndex === 0 ? 1.7 : 1.55;
  ctx.strokeStyle = colorWithAlpha(color, 0.82);
  ctx.setLineDash(surface.dash || []);
  rows.forEach((row, index) => {
    if (index % rowStep !== 0 && index !== rows.length - 1) return;
    drawProjectedPolyline(ctx, row.points.map(project));
  });
  for (let column = 0; column < columnCount; column += columnStep) {
    const projected = rows
      .map((row) => row.points[column])
      .filter(Boolean)
      .map(project);
    drawProjectedPolyline(ctx, projected);
  }
  ctx.restore();
}

function drawProjectedPolyline(ctx, points) {
  if (points.length < 2) return;
  ctx.beginPath();
  points.forEach((point, index) => {
    if (index === 0) ctx.moveTo(point.x, point.y);
    else ctx.lineTo(point.x, point.y);
  });
  ctx.stroke();
}

function drawTireStancePanel(ctx, x, y, width, height, data) {
  const palette = canvasPalette();
  const corners = tireSetupCorners(data);
  const maxForce = Math.max(
    100,
    ...corners
      .flatMap((corner) => [corner.fxPeakN, corner.fyPeakN, corner.forceMapMaxN])
      .map(Number)
      .filter((value) => Number.isFinite(value) && value > 0),
  );
  drawPanel(ctx, x, y, width, height, palette.surface);
  drawCanvasText(ctx, "Friction Ellipses", x + 14, y + 18, { size: 13, weight: 780 });
  drawCanvasText(ctx, `Shared scale ${formatNumber(maxForce)} N`, x + width - 14, y + 18, {
    size: 11,
    weight: 650,
    align: "right",
    color: palette.muted,
  });

  const inset = 14;
  const gap = clamp(width * 0.02, 10, 16);
  const innerX = x + inset;
  const innerY = y + 36;
  const innerW = Math.max(140, width - inset * 2);
  const innerH = Math.max(140, height - 50);
  const cardW = Math.max(96, (innerW - gap) / 2);
  const cardH = Math.max(70, (innerH - gap) / 2);
  const positions = {
    FL: { x: innerX, y: innerY },
    FR: { x: innerX + cardW + gap, y: innerY },
    RL: { x: innerX, y: innerY + cardH + gap },
    RR: { x: innerX + cardW + gap, y: innerY + cardH + gap },
  };
  drawTireSetupCenterline(ctx, innerX, innerY, innerW, innerH);
  corners.forEach((corner) => {
    const position = positions[corner.id];
    drawTireCornerSetupCard(ctx, corner, position.x, position.y, cardW, cardH, maxForce);
  });
}

function tireSetupCorners(data) {
  const evalByAxle = new Map((state.tirePayload?.sides || []).map((side) => [side.side, side]));
  return [
    { id: "FL", label: "Front left", axle: "front", side: "left" },
    { id: "FR", label: "Front right", axle: "front", side: "right" },
    { id: "RL", label: "Rear left", axle: "rear", side: "left" },
    { id: "RR", label: "Rear right", axle: "rear", side: "right" },
  ].map((spec) => {
    const axle = data?.[spec.axle] || {};
    const wheel = axle.wheel || {};
    const evalSide = evalByAxle.get(spec.axle) || {};
    const toeDeg = Number(wheel.toe_deg || 0);
    const inclinationDeg = Number(wheel.camber_deg || 0);
    const alphaOffsetDeg = cornerAlphaOffsetDeg(toeDeg, spec.side);
    const recordInclinationDeg = spec.side === "right" ? -inclinationDeg : inclinationDeg;
    const forceMap = tireSetupForceMap(evalSide, recordInclinationDeg, alphaOffsetDeg);
    const camberOnlyMap = tireSetupForceMap(evalSide, recordInclinationDeg, 0);
    const fzN = forceMap.fzN;
    return {
      ...spec,
      color: spec.axle === "front" ? canvasPalette().tireFront : canvasPalette().tireRear,
      template: axle.tire?.template || evalSide.template || "unassigned",
      radiusM: Number(wheel.radius_m || evalSide.metadata?.unloaded_radius_m || 0),
      fzN,
      forceMapRows: forceMap.rows,
      forceMapMaxN: forceMap.maxForceN,
      muX: forceMap.muX,
      muY: forceMap.muY,
      fxPeakN: forceMap.fxPeakN,
      fyPeakN: forceMap.fyPeakN,
      zeroForcePoint: forceMap.zeroPoint,
      zeroFxN: forceMap.zeroFxN,
      zeroFyN: forceMap.zeroFyN,
      camberFyN: camberOnlyMap.zeroFyN,
      camberThrustEnabled: Boolean(evalSide.metadata?.camber_thrust?.enabled),
      alphaOffsetDeg,
      inclinationDeg,
      recordInclinationDeg,
    };
  });
}

function tireSetupLoad(evalSide) {
  const values = [
    evalSide?.fz_n,
    evalSide?.metadata?.fznom_n,
    evalSide?.metadata?.fzmax_n,
  ].map(Number).filter((value) => Number.isFinite(value) && value > 0);
  return values[0] || 1;
}

function positiveFiniteOr(value, fallback) {
  const numeric = Number(value);
  return Number.isFinite(numeric) && numeric > 0 ? numeric : fallback;
}

function tireSetupForceMap(evalSide, gammaDeg = 0, alphaOffsetDeg = 0) {
  const nominalLoad = positiveFiniteOr(evalSide?.metadata?.fznom_n, tireSetupLoad(evalSide));
  const combined = evalSide?.curves?.combined || {};
  const gammaRows = tireForceMapRowsForGamma(combined, gammaDeg, nominalLoad);
  if (gammaRows.length) return summarizeTireForceMap(shiftTireForceMapAlpha(gammaRows, alphaOffsetDeg), nominalLoad);

  const directMap = combined.force_map_nominal || {};
  const directRows = normalizeTireForceMapRows(directMap.rows, Number(directMap.fz_n) || nominalLoad);
  if (directRows.length) {
    return summarizeTireForceMap(
      shiftTireForceMapAlpha(directRows, alphaOffsetDeg),
      Number(directMap.fz_n) || nominalLoad,
    );
  }

  const fxRows = interpolateTireSurfaceRowsByFz(combined.fx_surfaces_by_fz, nominalLoad, "fx_n")
    || combined.fx_surface?.rows
    || [];
  const fyRows = interpolateTireSurfaceRowsByFz(combined.fy_surfaces_by_fz, nominalLoad, "fy_n")
    || combined.fy_surface?.rows
    || [];
  const combinedRows = forceMapRowsFromFxFySurfaces(fxRows, fyRows, nominalLoad);
  if (combinedRows.length) {
    return summarizeTireForceMap(shiftTireForceMapAlpha(combinedRows, alphaOffsetDeg), nominalLoad);
  }

  const fallbackRows = forceMapRowsFromPureCurves(evalSide, nominalLoad);
  return summarizeTireForceMap(shiftTireForceMapAlpha(fallbackRows, alphaOffsetDeg), nominalLoad);
}

function tireForceMapRowsForGamma(combined, gammaDeg, nominalLoad) {
  const maps = (combined.force_maps_by_gamma || [])
    .map((map) => ({
      gammaDeg: Number(map.gamma_deg),
      fzN: Number(map.fz_n) || nominalLoad,
      rows: normalizeTireForceMapRows(map.rows, Number(map.fz_n) || nominalLoad),
    }))
    .filter((map) => Number.isFinite(map.gammaDeg) && map.rows.length)
    .sort((left, right) => left.gammaDeg - right.gammaDeg);
  if (!maps.length) return [];
  const gamma = Number(gammaDeg) || 0;
  if (gamma <= maps[0].gammaDeg) return cloneTireForceMapRows(maps[0].rows);
  const last = maps[maps.length - 1];
  if (gamma >= last.gammaDeg) return cloneTireForceMapRows(last.rows);
  const upperIndex = maps.findIndex((map) => map.gammaDeg >= gamma);
  const lower = maps[Math.max(0, upperIndex - 1)];
  const upper = maps[upperIndex];
  const span = upper.gammaDeg - lower.gammaDeg;
  if (Math.abs(span) <= 1e-9) return cloneTireForceMapRows(lower.rows);
  const t = (gamma - lower.gammaDeg) / span;
  return interpolateTireForceMapRows(lower.rows, upper.rows, t);
}

function interpolateTireForceMapRows(lowerRows, upperRows, t) {
  return lowerRows.map((row, rowIndex) => {
    const upperRow = upperRows[rowIndex] || row;
    return {
      alphaDeg: row.alphaDeg,
      points: (row.points || []).map((point, pointIndex) => {
        const upperPoint = upperRow.points?.[pointIndex] || point;
        const fx0 = Number(point.fxN);
        const fx1 = Number(upperPoint.fxN);
        const fy0 = Number(point.fyN);
        const fy1 = Number(upperPoint.fyN);
        const fz0 = Number(point.fzN);
        const fz1 = Number(upperPoint.fzN);
        return {
          ...point,
          fzN: Number.isFinite(fz0) && Number.isFinite(fz1) ? fz0 + (fz1 - fz0) * t : point.fzN,
          fxN: Number.isFinite(fx0) && Number.isFinite(fx1) ? fx0 + (fx1 - fx0) * t : point.fxN,
          fyN: Number.isFinite(fy0) && Number.isFinite(fy1) ? fy0 + (fy1 - fy0) * t : point.fyN,
        };
      }),
    };
  });
}

function cloneTireForceMapRows(rows) {
  return rows.map((row) => ({
    ...row,
    points: (row.points || []).map((point) => ({ ...point })),
  }));
}

function shiftTireForceMapAlpha(rows, alphaOffsetDeg) {
  const offset = Number(alphaOffsetDeg) || 0;
  if (!rows.length || Math.abs(offset) < 1e-9) return cloneTireForceMapRows(rows);
  const sorted = cloneTireForceMapRows(rows).sort((left, right) => left.alphaDeg - right.alphaDeg);
  return sorted.map((row) => {
    const tireAlphaDeg = row.alphaDeg + offset;
    const shifted = interpolateTireForceMapAtAlpha(sorted, tireAlphaDeg);
    return {
      alphaDeg: row.alphaDeg,
      tireAlphaDeg,
      points: shifted.points.map((point) => ({
        ...point,
        alphaDeg: row.alphaDeg,
        tireAlphaDeg,
      })),
    };
  });
}

function interpolateTireForceMapAtAlpha(rows, alphaDeg) {
  if (alphaDeg <= rows[0].alphaDeg) return cloneTireForceMapRow(rows[0]);
  const last = rows[rows.length - 1];
  if (alphaDeg >= last.alphaDeg) return cloneTireForceMapRow(last);
  const upperIndex = rows.findIndex((row) => row.alphaDeg >= alphaDeg);
  const lower = rows[Math.max(0, upperIndex - 1)];
  const upper = rows[upperIndex];
  const span = upper.alphaDeg - lower.alphaDeg;
  if (Math.abs(span) <= 1e-9) return cloneTireForceMapRow(lower);
  const t = (alphaDeg - lower.alphaDeg) / span;
  return interpolateTireForceMapRows([lower], [upper], t)[0];
}

function cloneTireForceMapRow(row) {
  return {
    ...row,
    points: (row.points || []).map((point) => ({ ...point })),
  };
}

function normalizeTireForceMapRows(rows, fzN) {
  if (!Array.isArray(rows)) return [];
  return rows
    .map((row) => {
      const alphaDeg = Number(row.alpha_deg);
      return {
        alphaDeg,
        points: (row.points || [])
          .map((point) => ({
            alphaDeg: Number(point.alpha_deg ?? alphaDeg),
            kappa: Number(point.kappa),
            fzN: Number(point.fz_n ?? fzN),
            fxN: Number(point.fx_n),
            fyN: Number(point.fy_n),
          }))
          .filter((point) => (
            Number.isFinite(point.alphaDeg)
            && Number.isFinite(point.kappa)
            && Number.isFinite(point.fxN)
            && Number.isFinite(point.fyN)
          )),
      };
    })
    .filter((row) => Number.isFinite(row.alphaDeg) && row.points.length);
}

function forceMapRowsFromFxFySurfaces(fxRows, fyRows, fzN) {
  const fyBySlip = new Map();
  (fyRows || []).forEach((row) => {
    const kappa = Number(row.kappa ?? row.points?.[0]?.kappa);
    (row.points || []).forEach((point) => {
      const alphaDeg = Number(point.alpha_deg);
      const pointKappa = Number(point.kappa ?? kappa);
      const fyN = Number(point.fy_n);
      if (Number.isFinite(alphaDeg) && Number.isFinite(pointKappa) && Number.isFinite(fyN)) {
        fyBySlip.set(tireForceMapKey(alphaDeg, pointKappa), fyN);
      }
    });
  });
  return (fxRows || [])
    .map((row) => {
      const alphaDeg = Number(row.alpha_deg ?? row.points?.[0]?.alpha_deg);
      return {
        alphaDeg,
        points: (row.points || [])
          .map((point) => {
            const pointAlphaDeg = Number(point.alpha_deg ?? alphaDeg);
            const kappa = Number(point.kappa);
            const fxN = Number(point.fx_n);
            const fyN = fyBySlip.get(tireForceMapKey(pointAlphaDeg, kappa));
            return {
              alphaDeg: pointAlphaDeg,
              kappa,
              fzN,
              fxN,
              fyN,
            };
          })
          .filter((point) => (
            Number.isFinite(point.alphaDeg)
            && Number.isFinite(point.kappa)
            && Number.isFinite(point.fxN)
            && Number.isFinite(point.fyN)
          )),
      };
    })
    .filter((row) => Number.isFinite(row.alphaDeg) && row.points.length);
}

function tireForceMapKey(alphaDeg, kappa) {
  return `${Number(alphaDeg).toFixed(6)}:${Number(kappa).toFixed(6)}`;
}

function forceMapRowsFromPureCurves(evalSide, fzN) {
  const longitudinal = Array.isArray(evalSide?.curves?.longitudinal) ? evalSide.curves.longitudinal : [];
  const lateral = Array.isArray(evalSide?.curves?.lateral) ? evalSide.curves.lateral : [];
  const fyByAlpha = new Map(lateral.map((point) => [Number(point.alpha_deg).toFixed(6), Number(point.fy_n)]));
  return lateral.map((latPoint) => {
    const alphaDeg = Number(latPoint.alpha_deg);
    const fyN = Number(latPoint.fy_n);
    return {
      alphaDeg,
      points: longitudinal.map((longPoint) => ({
        alphaDeg,
        kappa: Number(longPoint.kappa),
        fzN,
        fxN: Number(longPoint.fx_n),
        fyN: Number.isFinite(fyN) ? fyN : fyByAlpha.get(alphaDeg.toFixed(6)),
      })).filter((point) => (
        Number.isFinite(point.alphaDeg)
        && Number.isFinite(point.kappa)
        && Number.isFinite(point.fxN)
        && Number.isFinite(point.fyN)
      )),
    };
  }).filter((row) => Number.isFinite(row.alphaDeg) && row.points.length);
}

function summarizeTireForceMap(rows, fzN) {
  let fxPeakN = 0;
  let fyPeakN = 0;
  (rows || []).forEach((row) => {
    (row.points || []).forEach((point) => {
      const fx = Math.abs(Number(point.fxN));
      const fy = Math.abs(Number(point.fyN));
      if (Number.isFinite(fx)) fxPeakN = Math.max(fxPeakN, fx);
      if (Number.isFinite(fy)) fyPeakN = Math.max(fyPeakN, fy);
    });
  });
  const load = positiveFiniteOr(fzN, 1);
  const zeroPoint = tireForceMapPointAt(rows, 0, 0) || { alphaDeg: 0, kappa: 0, fxN: 0, fyN: 0 };
  return {
    rows,
    fzN: load,
    fxPeakN,
    fyPeakN,
    maxForceN: Math.max(100, fxPeakN, fyPeakN),
    muX: fxPeakN / load,
    muY: fyPeakN / load,
    zeroPoint,
    zeroFxN: Number(zeroPoint.fxN) || 0,
    zeroFyN: Number(zeroPoint.fyN) || 0,
  };
}

function tireForceMapPointAt(rows, alphaDeg, kappa) {
  if (!Array.isArray(rows) || !rows.length) return null;
  const sorted = cloneTireForceMapRows(rows).sort((left, right) => left.alphaDeg - right.alphaDeg);
  const alpha = Number(alphaDeg) || 0;
  let row;
  if (alpha <= sorted[0].alphaDeg) row = sorted[0];
  else if (alpha >= sorted[sorted.length - 1].alphaDeg) row = sorted[sorted.length - 1];
  else {
    const upperIndex = sorted.findIndex((item) => item.alphaDeg >= alpha);
    const lower = sorted[Math.max(0, upperIndex - 1)];
    const upper = sorted[upperIndex];
    const span = upper.alphaDeg - lower.alphaDeg;
    const t = Math.abs(span) <= 1e-9 ? 0 : (alpha - lower.alphaDeg) / span;
    row = interpolateTireForceMapRows([lower], [upper], t)[0];
  }
  return tireForceMapPointAtKappa(row.points || [], kappa);
}

function tireForceMapPointAtKappa(points, kappa) {
  const sorted = (points || [])
    .map((point) => ({ ...point, kappa: Number(point.kappa), fxN: Number(point.fxN), fyN: Number(point.fyN) }))
    .filter((point) => Number.isFinite(point.kappa) && Number.isFinite(point.fxN) && Number.isFinite(point.fyN))
    .sort((left, right) => left.kappa - right.kappa);
  if (!sorted.length) return null;
  const slip = Number(kappa) || 0;
  if (slip <= sorted[0].kappa) return sorted[0];
  const last = sorted[sorted.length - 1];
  if (slip >= last.kappa) return last;
  const upperIndex = sorted.findIndex((point) => point.kappa >= slip);
  const lower = sorted[Math.max(0, upperIndex - 1)];
  const upper = sorted[upperIndex];
  const span = upper.kappa - lower.kappa;
  const t = Math.abs(span) <= 1e-9 ? 0 : (slip - lower.kappa) / span;
  return {
    ...lower,
    kappa: slip,
    fxN: lower.fxN + (upper.fxN - lower.fxN) * t,
    fyN: lower.fyN + (upper.fyN - lower.fyN) * t,
  };
}

function cornerAlphaOffsetDeg(toeDeg, side) {
  const numeric = Number(toeDeg) || 0;
  return side === "right" ? -numeric : numeric;
}

function drawTireSetupCenterline(ctx, x, y, width, height) {
  const palette = canvasPalette();
  const midX = x + width / 2;
  const midY = y + height / 2;
  ctx.save();
  ctx.strokeStyle = colorWithAlpha(palette.line, state.dark ? 0.5 : 0.7);
  ctx.lineWidth = 1.5;
  ctx.setLineDash([5, 6]);
  ctx.beginPath();
  ctx.moveTo(midX, y + 6);
  ctx.lineTo(midX, y + height - 6);
  ctx.moveTo(x + 6, midY);
  ctx.lineTo(x + width - 6, midY);
  ctx.stroke();
  ctx.restore();
}

function drawTireCornerSetupCard(ctx, corner, x, y, width, height, maxForce) {
  const palette = canvasPalette();
  const accent = corner.color || palette.blue;
  drawPanel(ctx, x, y, width, height, colorWithAlpha(accent, state.dark ? 0.12 : 0.07));
  ctx.save();
  ctx.strokeStyle = accent;
  ctx.lineWidth = 3;
  ctx.lineCap = "round";
  ctx.beginPath();
  ctx.moveTo(x + 1.5, y + 11);
  ctx.lineTo(x + 1.5, y + height - 11);
  ctx.stroke();
  ctx.restore();

  drawCanvasText(ctx, corner.id, x + 12, y + 17, { size: 13, weight: 820, color: palette.ink });
  const template = fitCanvasText(ctx, corner.template, Math.max(54, width - 78), { size: 10, weight: 650 });
  drawCanvasText(ctx, template, x + width - 12, y + 17, {
    size: 10,
    weight: 650,
    align: "right",
    color: palette.muted,
  });

  const compact = height < 112 || width < 170;
  const statsH = 38;
  const plot = {
    x: x + 12,
    y: y + 30,
    width: Math.max(64, width - 24),
    height: Math.max(38, height - 36 - statsH),
  };
  const center = {
    x: plot.x + plot.width / 2,
    y: plot.y + plot.height / 2,
  };
  const maxRadius = Math.max(20, Math.min(plot.width * 0.42, plot.height * 0.43));
  drawTireFrictionEllipse(ctx, corner, center.x, center.y, maxRadius, maxForce);
  drawTireAlphaOffsetVector(ctx, corner, center.x, center.y, maxRadius);
  if (!compact) {
    drawTireInclinationGlyph(
      ctx,
      plot.x + plot.width - 52,
      plot.y + plot.height - 30,
      44,
      25,
      corner.inclinationDeg,
      corner.side,
      accent,
    );
  }

  const leftX = x + 12;
  const rightX = x + width - 12;
  const statY = y + height - 29;
  drawCanvasText(ctx, `FzNom ${formatNumber(corner.fzN)} N`, leftX, statY, {
    size: compact ? 9 : 10,
    weight: 760,
    color: palette.ink,
  });
  drawCanvasText(ctx, `alpha0 ${formatSignedNumber(corner.alphaOffsetDeg)} deg`, rightX, statY, {
    size: compact ? 9 : 10,
    weight: 760,
    align: "right",
    color: palette.ink,
  });
  drawCanvasText(ctx, `Fy0 ${formatSignedNumber(corner.zeroFyN)} N`, leftX, statY + 15, {
    size: compact ? 9 : 10,
    weight: 650,
    color: palette.muted,
  });
  drawCanvasText(ctx, `IA ${formatSignedNumber(corner.inclinationDeg)} deg  Fy ${formatSignedNumber(corner.camberFyN)} N`, rightX, statY + 15, {
    size: compact ? 9 : 10,
    weight: 650,
    align: "right",
    color: corner.camberThrustEnabled ? palette.muted : palette.amber,
  });
}

function drawTireFrictionEllipse(ctx, corner, cx, cy, maxRadius, maxForce) {
  const palette = canvasPalette();
  const accent = corner.color || palette.blue;
  const rows = Array.isArray(corner.forceMapRows) ? corner.forceMapRows : [];
  const project = (point) => ({
    x: cx + (Number(point.fyN) / Math.max(1e-8, maxForce)) * maxRadius,
    y: cy - (Number(point.fxN) / Math.max(1e-8, maxForce)) * maxRadius,
  });
  ctx.save();
  ctx.strokeStyle = colorWithAlpha(palette.line, state.dark ? 0.66 : 0.78);
  ctx.lineWidth = 1;
  ctx.beginPath();
  ctx.moveTo(cx - maxRadius - 6, cy);
  ctx.lineTo(cx + maxRadius + 6, cy);
  ctx.moveTo(cx, cy + maxRadius + 6);
  ctx.lineTo(cx, cy - maxRadius - 6);
  ctx.stroke();
  drawTireForceMapIsolines(ctx, rows, project, accent);
  ctx.restore();
  if (maxRadius >= 24) {
    drawCanvasText(ctx, "Fy", cx + maxRadius + 9, cy, {
      size: 9,
      weight: 760,
      color: palette.muted,
    });
    drawCanvasText(ctx, "Fx", cx, cy - maxRadius - 13, {
      size: 9,
      weight: 760,
      align: "center",
      color: palette.muted,
    });
  }
  if (maxRadius >= 30) drawTireForceMapLegend(ctx, cx - maxRadius, cy - maxRadius, accent);
}

function drawTireForceMapIsolines(ctx, rows, project, color) {
  const usableRows = (rows || []).filter((row) => Array.isArray(row.points) && row.points.length);
  if (!usableRows.length) return;
  const palette = canvasPalette();
  const rowIndexes = tireForceMapIsolineIndexes(usableRows.length, 13);
  const columnCount = finiteMax(usableRows.map((row) => row.points.length), 0);
  if (!Number.isFinite(columnCount) || columnCount <= 0) return;
  const columnIndexes = tireForceMapIsolineIndexes(columnCount, 13);
  const majorRowStep = Math.max(1, Math.floor(usableRows.length / 6));
  const majorColumnStep = Math.max(1, Math.floor(columnCount / 6));
  ctx.save();
  ctx.lineJoin = "round";
  ctx.lineCap = "round";
  rowIndexes.forEach((rowIndex) => {
    const row = usableRows[rowIndex];
    const isZeroAlpha = Math.abs(Number(row.alphaDeg)) < 1e-6;
    const isMajor = rowIndex % majorRowStep === 0 || rowIndex === usableRows.length - 1;
    ctx.strokeStyle = colorWithAlpha(color, isZeroAlpha ? 0.95 : isMajor ? 0.38 : 0.18);
    ctx.lineWidth = isZeroAlpha ? 2.1 : isMajor ? 1.15 : 0.7;
    ctx.setLineDash([]);
    drawProjectedPolyline(ctx, row.points.map(project));
  });
  columnIndexes.forEach((columnIndex) => {
    const points = usableRows.map((row) => row.points[columnIndex]).filter(Boolean);
    const kappa = Number(points[0]?.kappa);
    const isZeroKappa = Math.abs(kappa) < 1e-6;
    const isMajor = columnIndex % majorColumnStep === 0 || columnIndex === columnCount - 1;
    ctx.strokeStyle = isZeroKappa
      ? colorWithAlpha(palette.ink, state.dark ? 0.76 : 0.66)
      : colorWithAlpha(palette.muted, isMajor ? (state.dark ? 0.46 : 0.42) : (state.dark ? 0.23 : 0.22));
    ctx.lineWidth = isZeroKappa ? 1.8 : isMajor ? 1 : 0.6;
    ctx.setLineDash(isZeroKappa ? [] : [3, 4]);
    drawProjectedPolyline(ctx, points.map(project));
  });
  ctx.restore();
}

function tireForceMapIsolineIndexes(count, targetCount) {
  if (!Number.isFinite(count) || count <= 0) return [];
  const target = Math.max(1, Math.min(Math.floor(targetCount) || 1, count));
  if (count <= target) return Array.from({ length: count }, (_item, index) => index);
  const indexes = new Set([0, Math.floor((count - 1) / 2), count - 1]);
  const step = (count - 1) / Math.max(1, target - 1);
  for (let index = 1; index < target - 1; index += 1) {
    indexes.add(Math.round(index * step));
  }
  return [...indexes].sort((left, right) => left - right);
}

function drawTireForceMapLegend(ctx, x, y, color) {
  const palette = canvasPalette();
  ctx.save();
  ctx.lineCap = "round";
  ctx.strokeStyle = colorWithAlpha(color, 0.72);
  ctx.lineWidth = 1.6;
  ctx.beginPath();
  ctx.moveTo(x + 2, y + 5);
  ctx.lineTo(x + 18, y + 5);
  ctx.stroke();
  ctx.strokeStyle = colorWithAlpha(palette.muted, state.dark ? 0.58 : 0.54);
  ctx.setLineDash([3, 3]);
  ctx.beginPath();
  ctx.moveTo(x + 2, y + 18);
  ctx.lineTo(x + 18, y + 18);
  ctx.stroke();
  ctx.restore();
  drawCanvasText(ctx, "alpha", x + 23, y + 5, {
    size: 8,
    weight: 700,
    color: palette.muted,
  });
  drawCanvasText(ctx, "kappa", x + 23, y + 18, {
    size: 8,
    weight: 700,
    color: palette.muted,
  });
}

function drawTireAlphaOffsetVector(ctx, corner, cx, cy, maxRadius) {
  const palette = canvasPalette();
  const accent = corner.color || palette.blue;
  const alphaRad = corner.alphaOffsetDeg * Math.PI / 180;
  const heading = {
    x: -Math.sin(alphaRad),
    y: -Math.cos(alphaRad),
  };
  const length = clamp(maxRadius * 0.72, 16, 42);
  ctx.save();
  ctx.strokeStyle = colorWithAlpha(accent, 0.72);
  ctx.lineWidth = 1.5;
  ctx.lineCap = "round";
  ctx.setLineDash([4, 4]);
  ctx.beginPath();
  ctx.moveTo(cx, cy);
  ctx.lineTo(cx + heading.x * length, cy + heading.y * length);
  ctx.stroke();
  ctx.setLineDash([]);
  const angle = Math.atan2(heading.y, heading.x);
  const arrow = projectArrowHead(cx + heading.x * length, cy + heading.y * length, angle);
  ctx.beginPath();
  ctx.moveTo(arrow.tip.x, arrow.tip.y);
  ctx.lineTo(arrow.left.x, arrow.left.y);
  ctx.moveTo(arrow.tip.x, arrow.tip.y);
  ctx.lineTo(arrow.right.x, arrow.right.y);
  ctx.stroke();
  ctx.fillStyle = colorWithAlpha(palette.surface, state.dark ? 0.86 : 0.92);
  ctx.strokeStyle = colorWithAlpha(palette.line, state.dark ? 0.56 : 0.72);
  ctx.lineWidth = 1;
  const badgeW = 42;
  const badgeH = 16;
  const badgeX = cx - maxRadius - 4;
  const badgeY = cy + maxRadius - badgeH + 4;
  ctx.beginPath();
  if (ctx.roundRect) ctx.roundRect(badgeX, badgeY, badgeW, badgeH, 4);
  else ctx.rect(badgeX, badgeY, badgeW, badgeH);
  ctx.fill();
  ctx.stroke();
  ctx.restore();
  drawCanvasText(ctx, "alpha0", badgeX + badgeW / 2, badgeY + badgeH / 2, {
    size: 8,
    weight: 760,
    align: "center",
    color: palette.muted,
  });
}

function drawTireToeFootprint(ctx, corner, cx, cy, maxRadius) {
  const palette = canvasPalette();
  const accent = corner.color || palette.blue;
  const alphaRad = corner.alphaOffsetDeg * Math.PI / 180;
  const heading = {
    x: -Math.sin(alphaRad),
    y: -Math.cos(alphaRad),
  };
  const lateral = {
    x: -heading.y,
    y: heading.x,
  };
  const halfLong = clamp(maxRadius * 0.42, 15, 34);
  const halfWide = clamp(maxRadius * 0.15, 5, 11);
  const corners = [
    { h: 1, l: 1 },
    { h: 1, l: -1 },
    { h: -1, l: -1 },
    { h: -1, l: 1 },
  ].map((point) => ({
    x: cx + heading.x * halfLong * point.h + lateral.x * halfWide * point.l,
    y: cy + heading.y * halfLong * point.h + lateral.y * halfWide * point.l,
  }));
  ctx.save();
  ctx.strokeStyle = colorWithAlpha(palette.muted, state.dark ? 0.5 : 0.42);
  ctx.lineWidth = 1;
  ctx.setLineDash([4, 4]);
  ctx.beginPath();
  ctx.moveTo(cx, cy + halfLong + 7);
  ctx.lineTo(cx, cy - halfLong - 7);
  ctx.stroke();
  ctx.setLineDash([]);
  ctx.fillStyle = state.dark ? "#101820" : "#f6f8fa";
  ctx.strokeStyle = accent;
  ctx.lineWidth = 2;
  ctx.beginPath();
  corners.forEach((point, index) => {
    if (index === 0) ctx.moveTo(point.x, point.y);
    else ctx.lineTo(point.x, point.y);
  });
  ctx.closePath();
  ctx.fill();
  ctx.stroke();
  ctx.strokeStyle = colorWithAlpha(accent, 0.86);
  ctx.lineWidth = 1.4;
  ctx.beginPath();
  ctx.moveTo(cx - heading.x * halfLong * 0.74, cy - heading.y * halfLong * 0.74);
  ctx.lineTo(cx + heading.x * (halfLong + 8), cy + heading.y * (halfLong + 8));
  ctx.stroke();
  const angle = Math.atan2(heading.y, heading.x);
  const arrow = projectArrowHead(cx + heading.x * (halfLong + 8), cy + heading.y * (halfLong + 8), angle);
  ctx.beginPath();
  ctx.moveTo(arrow.tip.x, arrow.tip.y);
  ctx.lineTo(arrow.left.x, arrow.left.y);
  ctx.moveTo(arrow.tip.x, arrow.tip.y);
  ctx.lineTo(arrow.right.x, arrow.right.y);
  ctx.stroke();
  ctx.restore();
}

function drawTireInclinationGlyph(ctx, x, y, width, height, inclinationDeg, side, color) {
  const palette = canvasPalette();
  const centerX = x + width * 0.52;
  const groundY = y + height - 5;
  const topY = y + 6;
  const lean = clamp((Number(inclinationDeg) || 0) * 2.4, -13, 13);
  const topX = centerX + lean;
  const carSideX = side === "left" ? x + width - 5 : x + 5;
  ctx.save();
  ctx.strokeStyle = colorWithAlpha(palette.line, state.dark ? 0.7 : 0.8);
  ctx.lineWidth = 1;
  ctx.beginPath();
  ctx.moveTo(x + 5, groundY);
  ctx.lineTo(x + width - 5, groundY);
  ctx.stroke();
  ctx.strokeStyle = colorWithAlpha(palette.muted, state.dark ? 0.5 : 0.46);
  ctx.setLineDash([3, 3]);
  ctx.beginPath();
  ctx.moveTo(centerX, groundY);
  ctx.lineTo(centerX, topY);
  ctx.stroke();
  ctx.setLineDash([]);
  ctx.strokeStyle = color || palette.magenta;
  ctx.lineWidth = 3;
  ctx.lineCap = "round";
  ctx.beginPath();
  ctx.moveTo(centerX, groundY);
  ctx.lineTo(topX, topY);
  ctx.stroke();
  ctx.fillStyle = colorWithAlpha(color || palette.magenta, state.dark ? 0.78 : 0.9);
  ctx.beginPath();
  ctx.arc(topX, topY, 2.5, 0, Math.PI * 2);
  ctx.fill();
  ctx.strokeStyle = colorWithAlpha(palette.muted, state.dark ? 0.56 : 0.48);
  ctx.lineWidth = 1.2;
  ctx.beginPath();
  ctx.moveTo(carSideX, groundY - 3);
  ctx.lineTo(carSideX, topY + 3);
  ctx.stroke();
  ctx.restore();
  drawCanvasText(ctx, "car", carSideX, topY - 4, {
    size: 8,
    weight: 760,
    align: side === "left" ? "right" : "left",
    color: palette.muted,
  });
}

function formatSignedNumber(value) {
  const numeric = Number(value);
  if (!Number.isFinite(numeric)) return "";
  if (Math.abs(numeric) < 1e-9) return "0";
  return `${numeric > 0 ? "+" : ""}${formatNumber(numeric)}`;
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
  const xRange = finiteRange(allPoints.map((point) => point.x));
  const yRange = finiteRange(allPoints.map((point) => point.y));
  if (!xRange || !yRange) return;
  const minX = xRange.min;
  const maxX = xRange.max;
  const minY = yRange.min;
  const maxY = yRange.max;
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
  drawCanvasText(ctx, "Spring and damper tables feeding the force-based run.", 28, 52, {
    size: 12,
    weight: 650,
    color: palette.muted,
  });
  const maps = [
    ["front-spring", "Front spring", nestedValue(data, ["front", "actuation", "shock", "spring_table", "table"]), "Deflection", "m", "Force", "N"],
    ["front-damper", "Front damper", nestedValue(data, ["front", "actuation", "shock", "damper_table", "table"]), "Velocity", "m/s", "Force", "N"],
    ["rear-spring", "Rear spring", nestedValue(data, ["rear", "actuation", "shock", "spring_table", "table"]), "Deflection", "m", "Force", "N"],
    ["rear-damper", "Rear damper", nestedValue(data, ["rear", "actuation", "shock", "damper_table", "table"]), "Velocity", "m/s", "Force", "N"],
  ];
  const gap = 14;
  const top = 76;
  const plotCharts = [];
  const rateTop = top;
  const rateHeight = Math.max(260, height - rateTop - 28);
  const panelWidth = (width - 56 - gap) / 2;
  const panelHeight = Math.max(82, (rateHeight - gap) / 2);
  maps.forEach(([key, title, table, xLabel, xUnit, yLabel, yUnit], index) => {
    const col = index % 2;
    const row = Math.floor(index / 2);
    const chart = drawLinePanel(
      ctx,
      28 + col * (panelWidth + gap),
      rateTop + row * (panelHeight + gap),
      panelWidth,
      panelHeight,
      title,
      table,
      xLabel,
      xUnit,
      yLabel,
      yUnit,
      { key },
    );
    if (chart) plotCharts.push(chart);
  });
  state.suspensionPlotScene = plotCharts.length ? { charts: plotCharts } : null;
}

function kinematicCurveDescriptors(payload) {
  const meta = Array.isArray(payload?.curve_meta) && payload.curve_meta.length
    ? payload.curve_meta
    : DEFAULT_KINEMATIC_CURVES;
  const curveKeys = new Set();
  ["front", "rear"].forEach((axle) => {
    Object.keys(payload?.axles?.[axle]?.curves || {}).forEach((key) => curveKeys.add(key));
  });
  const descriptors = [];
  const seen = new Set();
  meta.forEach((item) => {
    const id = String(item?.id || "");
    if (!id || seen.has(id)) return;
    if (curveKeys.size && !curveKeys.has(id)) return;
    seen.add(id);
    descriptors.push({
      id,
      label: item?.label || humanizeKinematicCurve(id),
      unit: item?.unit || inferCurveUnit(id),
      x_id: item?.x_id || "jounce_mm",
      x_label: item?.x_label || "Jounce",
      x_unit: item?.x_unit || "mm",
      y_label: item?.y_label || item?.label || humanizeKinematicCurve(id),
    });
  });
  [...curveKeys].sort().forEach((id) => {
    if (seen.has(id)) return;
    const rollCurve = id.startsWith("roll_");
    descriptors.push({
      id,
      label: humanizeKinematicCurve(id),
      unit: inferCurveUnit(id),
      x_id: rollCurve ? "roll_deg" : "jounce_mm",
      x_label: rollCurve ? "Roll" : "Jounce",
      x_unit: rollCurve ? "deg" : "mm",
      y_label: humanizeKinematicCurve(id),
    });
  });
  return descriptors.length ? descriptors : DEFAULT_KINEMATIC_CURVES;
}

function humanizeKinematicCurve(id) {
  return humanizeToken(String(id).replace(/_(deg|mm|m|rad)$/i, ""));
}

function inferCurveUnit(id) {
  if (String(id).endsWith("_deg")) return "deg";
  if (String(id).endsWith("_mm")) return "mm";
  if (String(id).endsWith("_rad")) return "rad";
  return "";
}

function drawKinematicChart(
  ctx,
  x,
  y,
  width,
  height,
  payload,
  descriptor,
  { focused = false, hover = undefined, axles = null } = {},
) {
  const palette = canvasPalette();
  const key = descriptor.id;
  const yKey = descriptor.y_id || descriptor.id;
  const title = descriptor.label || humanizeKinematicCurve(key);
  const unit = descriptor.y_unit || descriptor.unit || inferCurveUnit(yKey);
  const xValues = kinematicChartXValues(payload, descriptor);
  const visibleAxles = new Set(Array.isArray(axles) && axles.length ? axles : ["front", "rear"]);
  const series = [
    { axle: "front", label: "Front", shortLabel: "F", color: palette.blue, values: payload.axles?.front?.curves?.[yKey] || [] },
    { axle: "rear", label: "Rear", shortLabel: "R", color: palette.green, values: payload.axles?.rear?.curves?.[yKey] || [] },
  ].filter((item) => visibleAxles.has(item.axle)).map((item) => ({
    ...item,
    points: item.values
      .map((value, index) => ({
        index,
        sampleKey: String(index),
        xValue: xValues[index],
        yValue: Number(value),
      }))
      .filter((point) => Number.isFinite(point.xValue) && Number.isFinite(point.yValue)),
  }));
  ctx.save();
  ctx.fillStyle = colorWithAlpha(palette.bg, state.dark ? 0.2 : 0.42);
  ctx.strokeStyle = focused ? palette.amber : palette.line;
  ctx.lineWidth = focused ? 1.5 : 1;
  ctx.beginPath();
  if (ctx.roundRect) ctx.roundRect(x, y, width, height, 6);
  else ctx.rect(x, y, width, height);
  ctx.fill();
  ctx.stroke();
  drawCanvasText(ctx, title, x + 10, y + (focused ? 18 : 14), { size: focused ? 14 : 11, weight: 780 });
  const chart = createPlotChart({
    key,
    title,
    x,
    y,
    width,
    height,
    xLabel: descriptor.x_label || "Jounce",
    xUnit: descriptor.x_unit || "mm",
    yLabel: descriptor.y_label || title,
    yUnit: unit,
    series,
    includeZeroY: true,
    margins: focused
      ? { left: 62, right: 18, top: 48, bottom: 44 }
      : { left: 50, right: 14, top: 36, bottom: 36 },
  });
  if (!chart) {
    drawCanvasText(ctx, "Waiting for curve data", x + width / 2, y + height / 2, { align: "center", color: palette.muted });
    ctx.restore();
    return null;
  }
  drawPlotGrid(ctx, chart);
  chart.series.forEach((item) => drawPlotSeries(ctx, item, chart.plot));
  drawCanvasText(ctx, chart.yUnit, x + width - 10, y + 14, {
    size: 10,
    weight: 650,
    align: "right",
    color: palette.muted,
  });
  drawKinematicLegend(ctx, chart.series, x + 10, y + height - 12);
  drawPlotHover(ctx, chart, hover);
  ctx.restore();
  return chart;
}

function kinematicChartXValues(payload, descriptor) {
  const xId = descriptor?.x_id || "jounce_mm";
  const axisValues = payload?.x_axes?.[xId];
  if (Array.isArray(axisValues) && axisValues.length) {
    return axisValues.map(Number);
  }
  if (xId === "roll_deg" && Array.isArray(payload?.roll_deg)) {
    return payload.roll_deg.map(Number);
  }
  return (payload?.sweep_m || []).map((value) => Number(value) * 1000);
}

function drawPlotSeries(ctx, item, plot) {
  if (!item.points.length) return;
  ctx.save();
  ctx.beginPath();
  ctx.rect(plot.x, plot.y, plot.width, plot.height);
  ctx.clip();
  ctx.strokeStyle = item.color;
  ctx.lineWidth = 2.4;
  ctx.lineJoin = "round";
  ctx.lineCap = "round";
  ctx.beginPath();
  item.points.forEach((point, index) => {
    if (index === 0) ctx.moveTo(point.canvasX, point.canvasY);
    else ctx.lineTo(point.canvasX, point.canvasY);
  });
  ctx.stroke();
  if (item.points.length <= 18) {
    ctx.fillStyle = item.color;
    item.points.forEach((point) => {
      ctx.beginPath();
      ctx.arc(point.canvasX, point.canvasY, 2.2, 0, Math.PI * 2);
      ctx.fill();
    });
  }
  ctx.restore();
}

function drawKinematicLegend(ctx, series, x, y) {
  series.forEach((item, index) => {
    const offset = index * 30;
    ctx.fillStyle = item.color;
    ctx.beginPath();
    ctx.arc(x + offset, y, 3, 0, Math.PI * 2);
    ctx.fill();
    drawCanvasText(ctx, item.shortLabel || item.label, x + offset + 7, y, { size: 9, weight: 760, color: canvasPalette().muted });
  });
}

function createPlotChart({
  key,
  title,
  x,
  y,
  width,
  height,
  xLabel,
  xUnit,
  yLabel,
  yUnit,
  series,
  includeZeroY = false,
  margins = { left: 52, right: 16, top: 38, bottom: 38 },
}) {
  const validSeries = series
    .map((item) => ({
      ...item,
      points: (item.points || []).filter((point) => (
        Number.isFinite(point.xValue) && Number.isFinite(point.yValue)
      )),
    }))
    .filter((item) => item.points.length);
  const allPoints = validSeries.flatMap((item) => item.points);
  if (allPoints.length < 2) return null;
  const [minX, maxX] = plotDomain(allPoints.map((point) => point.xValue), { padFraction: 0.02 });
  const [minY, maxY] = plotDomain(allPoints.map((point) => point.yValue), { includeZero: includeZeroY, padFraction: 0.12 });
  const plot = {
    x: x + margins.left,
    y: y + margins.top,
    width: Math.max(36, width - margins.left - margins.right),
    height: Math.max(24, height - margins.top - margins.bottom),
  };
  const toX = (value) => plot.x + ((value - minX) / Math.max(1e-9, maxX - minX)) * plot.width;
  const toY = (value) => plot.y + plot.height - ((value - minY) / Math.max(1e-9, maxY - minY)) * plot.height;
  const sampleMap = new Map();
  const chartSeries = validSeries.map((item) => ({
    ...item,
    points: item.points.map((point) => {
      const sampleKey = String(point.sampleKey ?? point.index);
      const canvasX = toX(point.xValue);
      const canvasY = toY(point.yValue);
      if (!sampleMap.has(sampleKey)) {
        sampleMap.set(sampleKey, {
          sampleKey,
          index: point.index,
          xValue: point.xValue,
          canvasX,
        });
      }
      return {
        ...point,
        sampleKey,
        canvasX,
        canvasY,
      };
    }),
  }));
  return {
    key,
    title,
    x,
    y,
    width,
    height,
    bounds: { x, y, width, height },
    plot,
    xDomain: [minX, maxX],
    yDomain: [minY, maxY],
    xLabel,
    xUnit,
    yLabel,
    yUnit,
    series: chartSeries,
    samples: [...sampleMap.values()].sort((left, right) => left.xValue - right.xValue),
  };
}

function plotDomain(values, { includeZero = false, padFraction = 0.08 } = {}) {
  const range = finiteRange(values);
  if (!range) return [-1, 1];
  let min = range.min;
  let max = range.max;
  if (includeZero) {
    min = Math.min(min, 0);
    max = Math.max(max, 0);
  }
  const span = max - min;
  const pad = span > 0
    ? span * padFraction
    : Math.max(Math.abs(max) * 0.12, 1e-3);
  return [min - pad, max + pad];
}

function drawPlotGrid(ctx, chart) {
  const palette = canvasPalette();
  const { plot } = chart;
  const xTicks = niceTickValues(chart.xDomain[0], chart.xDomain[1], 5);
  const yTicks = niceTickValues(chart.yDomain[0], chart.yDomain[1], 5);
  const toX = (value) => plot.x + ((value - chart.xDomain[0]) / Math.max(1e-9, chart.xDomain[1] - chart.xDomain[0])) * plot.width;
  const toY = (value) => plot.y + plot.height - ((value - chart.yDomain[0]) / Math.max(1e-9, chart.yDomain[1] - chart.yDomain[0])) * plot.height;
  ctx.save();
  ctx.lineWidth = 1;
  ctx.strokeStyle = colorWithAlpha(palette.line, state.dark ? 0.42 : 0.68);
  xTicks.forEach((tick) => {
    const px = toX(tick);
    ctx.beginPath();
    ctx.moveTo(px, plot.y);
    ctx.lineTo(px, plot.y + plot.height);
    ctx.stroke();
    drawCanvasText(ctx, formatNumber(tick), px, plot.y + plot.height + 13, {
      size: 9,
      weight: 650,
      align: "center",
      color: palette.muted,
    });
  });
  yTicks.forEach((tick) => {
    const py = toY(tick);
    ctx.beginPath();
    ctx.moveTo(plot.x, py);
    ctx.lineTo(plot.x + plot.width, py);
    ctx.stroke();
    drawCanvasText(ctx, formatNumber(tick), plot.x - 7, py, {
      size: 9,
      weight: 650,
      align: "right",
      color: palette.muted,
    });
  });
  ctx.strokeStyle = palette.line;
  ctx.strokeRect(plot.x, plot.y, plot.width, plot.height);
  ctx.restore();
  drawCanvasText(ctx, `${chart.xLabel}${chart.xUnit ? ` (${chart.xUnit})` : ""}`, plot.x + plot.width / 2, chart.y + chart.height - 11, {
    size: 9,
    weight: 720,
    align: "center",
    color: palette.muted,
  });
}

function niceTickValues(min, max, targetCount = 5) {
  if (!Number.isFinite(min) || !Number.isFinite(max)) return [];
  if (min === max) return [min];
  const span = Math.abs(max - min);
  const rawStep = span / Math.max(1, targetCount - 1);
  const magnitude = 10 ** Math.floor(Math.log10(rawStep));
  const fraction = rawStep / magnitude;
  const niceFraction = fraction <= 1 ? 1 : fraction <= 2 ? 2 : fraction <= 5 ? 5 : 10;
  const step = niceFraction * magnitude;
  const start = Math.ceil(min / step) * step;
  const ticks = [];
  for (let value = start; value <= max + step * 0.5; value += step) {
    ticks.push(Math.abs(value) < step * 1e-6 ? 0 : value);
    if (ticks.length > 12) break;
  }
  return ticks.length ? ticks : [min, max];
}

function drawPlotHover(ctx, chart, hoverState = undefined) {
  const activeHover = hoverState === undefined ? state.suspensionPlotHover : hoverState;
  const hover = suspensionHoverForChart(chart, activeHover);
  if (!hover) return;
  const palette = canvasPalette();
  const { plot } = chart;
  ctx.save();
  ctx.strokeStyle = colorWithAlpha(palette.ink, state.dark ? 0.36 : 0.28);
  ctx.lineWidth = 1;
  ctx.setLineDash([4, 4]);
  ctx.beginPath();
  ctx.moveTo(hover.sample.canvasX, plot.y);
  ctx.lineTo(hover.sample.canvasX, plot.y + plot.height);
  ctx.stroke();
  ctx.setLineDash([]);
  hover.items.forEach((item) => {
    ctx.fillStyle = item.color;
    ctx.strokeStyle = palette.surface;
    ctx.lineWidth = 2;
    ctx.beginPath();
    ctx.arc(item.point.canvasX, item.point.canvasY, 4.5, 0, Math.PI * 2);
    ctx.fill();
    ctx.stroke();
  });

  const lines = [
    `${chart.xLabel}: ${formatSignedNumber(hover.sample.xValue)} ${chart.xUnit}`.trim(),
    ...hover.items.map((item) => `${item.label}: ${formatNumber(item.point.yValue)} ${chart.yUnit}`.trim()),
  ];
  ctx.font = "700 11px Inter, sans-serif";
  const textWidth = Math.max(...lines.map((line) => ctx.measureText(line).width));
  const tooltipW = Math.min(chart.bounds.width - 16, textWidth + 22);
  const tooltipH = 14 + lines.length * 16;
  let tooltipX = hover.sample.canvasX + 12;
  if (tooltipX + tooltipW > chart.bounds.x + chart.bounds.width - 8) {
    tooltipX = hover.sample.canvasX - tooltipW - 12;
  }
  tooltipX = clamp(tooltipX, chart.bounds.x + 8, chart.bounds.x + chart.bounds.width - tooltipW - 8);
  const requestedY = Number.isFinite(activeHover?.pointerY)
    ? activeHover.pointerY - tooltipH - 10
    : plot.y + 8;
  const tooltipY = clamp(requestedY, plot.y + 8, plot.y + plot.height - tooltipH - 8);
  ctx.fillStyle = state.dark ? "#1c242b" : "#ffffff";
  ctx.strokeStyle = palette.line;
  ctx.lineWidth = 1;
  ctx.beginPath();
  if (ctx.roundRect) ctx.roundRect(tooltipX, tooltipY, tooltipW, tooltipH, 7);
  else ctx.rect(tooltipX, tooltipY, tooltipW, tooltipH);
  ctx.fill();
  ctx.stroke();
  lines.forEach((line, index) => {
    const item = index > 0 ? hover.items[index - 1] : null;
    ctx.fillStyle = item?.color || palette.muted;
    ctx.font = `${index === 0 ? 760 : 700} 11px Inter, sans-serif`;
    ctx.textAlign = "left";
    ctx.textBaseline = "middle";
    ctx.fillText(line, tooltipX + 11, tooltipY + 13 + index * 16);
  });
  ctx.restore();
}

function suspensionHoverForChart(chart, hover = state.suspensionPlotHover) {
  if (!hover || hover.chartKey !== chart.key) return null;
  const sample = chart.samples.find((item) => item.sampleKey === hover.sampleKey);
  if (!sample) return null;
  const items = chart.series
    .map((series) => {
      const point = series.points.find((item) => item.sampleKey === hover.sampleKey);
      return point ? { label: series.label, color: series.color, point } : null;
    })
    .filter(Boolean);
  if (!items.length) return null;
  return { sample, items };
}

function formatSignedNumber(value) {
  const numeric = Number(value);
  if (!Number.isFinite(numeric) || numeric === 0) return formatNumber(value);
  return `${numeric > 0 ? "+" : ""}${formatNumber(numeric)}`;
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

function drawLinePanel(ctx, x, y, width, height, title, table, xLabel, xUnit, yLabel, yUnit, { key = title } = {}) {
  const palette = canvasPalette();
  drawPanel(ctx, x, y, width, height, palette.surface);
  drawCanvasText(ctx, title, x + 12, y + 17, { size: 13, weight: 780 });
  if (!Array.isArray(table) || table.length < 2) {
    drawCanvasText(ctx, "No table", x + width / 2, y + height / 2, { align: "center", color: palette.muted });
    return null;
  }
  const points = table
    .map((row, index) => (Array.isArray(row)
      ? {
        index,
        sampleKey: String(index),
        xValue: Number(row[0]),
        yValue: Number(row[1]),
      }
      : null))
    .filter((point) => point && Number.isFinite(point.xValue) && Number.isFinite(point.yValue));
  const chart = createPlotChart({
    key,
    title,
    x,
    y,
    width,
    height,
    xLabel,
    xUnit,
    yLabel,
    yUnit,
    series: [{
      label: title,
      color: key.includes("damper") ? palette.red : palette.blue,
      points,
    }],
    includeZeroY: true,
    margins: { left: 54, right: 16, top: 40, bottom: 36 },
  });
  if (!chart) return null;
  drawPlotGrid(ctx, chart);
  chart.series.forEach((item) => drawPlotSeries(ctx, item, chart.plot));
  drawCanvasText(ctx, `${yLabel}${yUnit ? ` (${yUnit})` : ""}`, x + width - 12, y + 17, {
    size: 10,
    weight: 650,
    align: "right",
    color: palette.muted,
  });
  drawPlotHover(ctx, chart);
  return chart;
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
  const range = finiteRange(rows.flat());
  const min = range?.min ?? 0;
  const max = range?.max ?? 0;
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
  const nodes = POWERTRAIN_MAIN_LOOP.length;
  const lineY = height * 0.62;
  ctx.strokeStyle = palette.blue;
  ctx.lineWidth = 2;
  ctx.beginPath();
  ctx.moveTo(8, lineY);
  ctx.lineTo(width - 8, lineY);
  ctx.stroke();
  for (let index = 0; index < nodes; index += 1) {
    const x = 9 + index * ((width - 18) / Math.max(1, nodes - 1));
    ctx.fillStyle = palette.surface;
    ctx.strokeStyle = index === nodes - 1 ? palette.green : palette.blue;
    ctx.lineWidth = 2;
    ctx.beginPath();
    ctx.rect(x - 5, lineY - 7, 10, 14);
    ctx.fill();
    ctx.stroke();
  }
  const controlX = width * 0.5;
  const controlY = height * 0.24;
  ctx.setLineDash([3, 3]);
  ctx.strokeStyle = palette.amber;
  ctx.lineWidth = 1.4;
  ctx.beginPath();
  ctx.moveTo(controlX, controlY + 6);
  ctx.lineTo(width * 0.42, lineY - 8);
  ctx.moveTo(controlX, controlY + 6);
  ctx.lineTo(width * 0.62, lineY - 8);
  ctx.stroke();
  ctx.setLineDash([]);
  ctx.fillStyle = state.dark ? "#2b2415" : "#fff7e8";
  ctx.strokeStyle = palette.amber;
  ctx.beginPath();
  if (ctx.roundRect) ctx.roundRect(controlX - 9, controlY - 6, 18, 12, 3);
  else ctx.rect(controlX - 9, controlY - 6, 18, 12);
  ctx.fill();
  ctx.stroke();
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
  const bellcrankSocketRoles = hasStabar ? ["rod", "shock", "stabar"] : ["rod", "shock"];
  const bellcrankOrder = hasBellcrank ? normalizeBellcrankOrder(bellcrank.order, bellcrankSocketRoles) : [];
  const bellcrankSocketByRole = Object.fromEntries(bellcrankOrder.map((role, index) => [role, bellcrankSocketRoles[index]]));
  const bellcrankTarget = (role) => `${prefix}-bellcrank-${bellcrankSocketByRole[role] || role}`;
  if (hasBellcrank) {
    addLink(`${prefix}-rod`, bellcrankTarget("rod"), "pushrod", 5, linkMeta("pushrod", true));
    addLink(`${prefix}-shock-mount`, bellcrankTarget("shock"), "shock", 6, linkMeta("shock", true));
  } else {
    addLink(`${prefix}-shock-mount`, `${prefix}-rod`, "shock", 6, linkMeta("shock", true));
  }
  if (hasStabar) {
    addLink(`${prefix}-stabar-arm`, `${prefix}-stabar-bar`, "stabar", 4, linkMeta("stabar", true));
    if (hasBellcrank) {
      addLink(`${prefix}-stabar-arm`, bellcrankTarget("stabar"), "stabar", 4, linkMeta("stabar", true));
    }
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
    if (isSurfaceMapPreviewArea()) {
      if (startTireSurfaceDrag(event)) return;
      return;
    }
    if (handleSuspensionPlotClick(event)) return;
    if (!isSpatialPreviewArea()) return;
    if (isPanClick(event)) {
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
  canvas.addEventListener("mousedown", startMiddleCanvasPan);
  canvas.addEventListener("auxclick", suppressMiddleCanvasAuxAction);
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
    if (updateTireSurfaceDrag(event)) return;
    if (updatePreviewDrag(event)) return;
  });
  canvas.addEventListener("pointerup", (event) => {
    if (finishGeometryDrag(event.pointerId)) return;
    if (finishTireSurfaceDrag(event.pointerId)) return;
    if (finishPreviewDrag(event.pointerId)) return;
  });
  canvas.addEventListener("pointercancel", (event) => {
    if (finishGeometryDrag(event.pointerId)) return;
    if (finishTireSurfaceDrag(event.pointerId)) return;
    if (finishPreviewDrag(event.pointerId)) return;
  });
  canvas.addEventListener("wheel", handlePreviewWheel, { passive: false });
  window.addEventListener("mousemove", (event) => {
    if (updateTireSurfaceDrag(event)) return;
    if (updatePreviewDrag(event)) return;
  });
  window.addEventListener("mouseup", (event) => {
    const pointerId = dragPointerId(event);
    if (finishTireSurfaceDrag(pointerId)) return;
    if (finishPreviewDrag(pointerId)) return;
  });
  canvas.addEventListener("pointermove", updateGeometryHover);
  canvas.addEventListener("pointermove", updateSuspensionPlotHover);
  canvas.addEventListener("pointermove", updateTireSurfaceHover);
  canvas.addEventListener("pointerleave", () => {
    state.geometryHoverPointId = null;
    state.architectureHoverId = null;
    state.massHoverPointId = null;
    state.suspensionPlotHover = null;
    state.tireSurfaceDrag = null;
    state.tireSurfaceHover = null;
    canvas.classList.remove("geometry-hot");
    canvas.classList.remove("architecture-hot");
    canvas.classList.remove("mass-hot");
    canvas.classList.remove("kinematic-hot");
    canvas.classList.remove("tire-surface-hot");
    canvas.classList.remove("preview-panning");
    canvas.classList.remove("tire-surface-dragging");
    drawVehicleFromForm();
  });
  canvas.addEventListener("dblclick", () => {
    if (isSurfaceMapPreviewArea()) {
      resetTireSurfaceView();
      return;
    }
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
    if (event.key === "Escape" && activeParameterArea().visual === "suspension" && clearSuspensionPlotFocus()) {
      event.preventDefault();
      return;
    }
    if (event.key === "Escape" && isSpatialPreviewArea() && clearGeometrySelection()) {
      event.preventDefault();
      return;
    }
    if (event.key === "Shift" && !event.repeat && handleGeometryAxisShortcut(event)) {
      state.geometryShiftActive = true;
    }
  });
  window.addEventListener("keyup", (event) => {
    if (event.key === "Shift") state.geometryShiftActive = false;
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

function wireGeometryPlotSplitter() {
  const splitter = document.getElementById("geometry-plot-splitter");
  if (!splitter) return;
  applyGeometryPlotHeight();
  splitter.addEventListener("pointerdown", (event) => {
    state.geometryPlotResize = {
      pointerId: event.pointerId,
      startY: event.clientY,
      startHeight: state.geometryPlotHeight,
    };
    splitter.classList.add("active");
    document.body.classList.add("resizing-plot-pane");
    splitter.setPointerCapture(event.pointerId);
    event.preventDefault();
  });
  splitter.addEventListener("pointermove", (event) => {
    const resize = state.geometryPlotResize;
    if (!resize || resize.pointerId !== event.pointerId) return;
    setGeometryPlotHeight(resize.startHeight - (event.clientY - resize.startY), { redraw: false });
    drawVehicleFromForm();
  });
  splitter.addEventListener("pointerup", (event) => finishGeometryPlotResize(event.pointerId));
  splitter.addEventListener("pointercancel", (event) => finishGeometryPlotResize(event.pointerId));
  splitter.addEventListener("keydown", (event) => {
    const step = event.shiftKey ? 48 : 16;
    if (event.key === "ArrowUp") {
      event.preventDefault();
      setGeometryPlotHeight(state.geometryPlotHeight + step, { persist: true });
    }
    if (event.key === "ArrowDown") {
      event.preventDefault();
      setGeometryPlotHeight(state.geometryPlotHeight - step, { persist: true });
    }
    if (event.key === "Home") {
      event.preventDefault();
      setGeometryPlotHeight(MIN_GEOMETRY_PLOT_HEIGHT, { persist: true });
    }
    if (event.key === "End") {
      event.preventDefault();
      setGeometryPlotHeight(geometryPlotHeightBounds().max, { persist: true });
    }
  });
}

function finishGeometryPlotResize(pointerId) {
  const resize = state.geometryPlotResize;
  if (!resize || resize.pointerId !== pointerId) return;
  state.geometryPlotResize = null;
  document.getElementById("geometry-plot-splitter")?.classList.remove("active");
  document.body.classList.remove("resizing-plot-pane");
  localStorage.setItem("bobsim-geometry-plot-height", String(Math.round(state.geometryPlotHeight)));
  drawVehicleFromForm();
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
  document.getElementById("simulation-modal-close").addEventListener("click", closeSimulationModal);
  document.getElementById("simulation-config-modal").addEventListener("pointerdown", (event) => {
    if (event.target.id === "simulation-config-modal") closeSimulationModal();
  });
  document.getElementById("toolchain-settings-btn").addEventListener("click", openModelicaToolchain);
  document.getElementById("toolchain-close-btn").addEventListener("click", closeModelicaToolchain);
  document.getElementById("toolchain-save-btn").addEventListener("click", saveOpenModelicaToolchain);
  document.getElementById("toolchain-reset-btn").addEventListener("click", resetOpenModelicaToolchain);
  document.getElementById("toolchain-modal").addEventListener("pointerdown", (event) => {
    if (event.target.id === "toolchain-modal") closeModelicaToolchain();
  });
  ["toolchain-omc-input", "toolchain-library-input"].forEach((id) => {
    document.getElementById(id).addEventListener("input", () => {
      state.toolchainInputsDirty = true;
    });
  });
  document.getElementById("architecture-connection-close").addEventListener("click", closeArchitectureConnectionModal);
  document.getElementById("architecture-connection-modal").addEventListener("pointerdown", (event) => {
    if (event.target.id === "architecture-connection-modal") closeArchitectureConnectionModal();
  });
  document.getElementById("architecture-modal-select").addEventListener("change", (event) => {
    updateArchitectureModalArchitecture(event.target.value);
  });
  const connectionBody = document.getElementById("architecture-connection-body");
  connectionBody.addEventListener("pointerdown", (event) => {
    if (!event.target.closest?.("#architecture-connection-canvas")) return;
    const hotspot = hitTestArchitectureModalHotspot(event);
    if (hotspot?.type === "bellcrank-pickup" && startArchitecturePickupDrag(event, hotspot)) {
      event.preventDefault();
    }
  });
  connectionBody.addEventListener("pointermove", (event) => {
    if (state.architectureDrag && updateArchitecturePickupDrag(event)) {
      event.preventDefault();
      return;
    }
    if (event.target.closest?.("#architecture-connection-canvas")) updateArchitectureModalHover(event);
  });
  connectionBody.addEventListener("pointerup", (event) => {
    if (finishArchitecturePickupDrag(event.pointerId)) event.preventDefault();
  });
  connectionBody.addEventListener("pointercancel", (event) => {
    if (cancelArchitecturePickupDrag(event.pointerId)) event.preventDefault();
  });
  connectionBody.addEventListener("pointerleave", () => {
    if (state.architectureDrag) return;
    state.architectureModalHoverId = null;
    document.getElementById("architecture-connection-canvas")?.classList.remove("hot");
    drawArchitectureConnectionCanvas();
  });
  connectionBody.addEventListener("click", (event) => {
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
  document.getElementById("kinematic-plot-close").addEventListener("click", () => closeSuspensionPlotModal());
  document.getElementById("kinematic-plot-modal").addEventListener("pointerdown", (event) => {
    if (event.target.id === "kinematic-plot-modal") closeSuspensionPlotModal();
  });
  document.getElementById("kinematic-plot-modal-canvas").addEventListener("pointermove", updateSuspensionPlotModalHover);
  document.getElementById("kinematic-plot-modal-canvas").addEventListener("pointerleave", () => {
    if (!state.suspensionPlotModalHover) return;
    state.suspensionPlotModalHover = null;
    drawSuspensionPlotModal();
  });
  document.getElementById("geometry-add-plot-btn").addEventListener("click", addGeometryPlotSelection);
  document.getElementById("geometry-plot-x-axis").addEventListener("change", (event) => {
    state.geometryPlotDraftX = event.target.value;
    state.geometryPlotDraftY = "";
    renderGeometryPlotControls();
  });
  document.getElementById("geometry-plot-y-axis").addEventListener("change", (event) => {
    state.geometryPlotDraftY = event.target.value;
  });
  document.getElementById("geometry-plot-list").addEventListener("click", (event) => {
    const remove = event.target.closest("[data-geometry-plot-remove]");
    if (remove) removeGeometryPlotSelection(remove.dataset.geometryPlotRemove);
  });
  document.getElementById("geometry-plot-canvas").addEventListener("pointermove", updateGeometryPlotHover);
  document.getElementById("geometry-plot-canvas").addEventListener("pointerleave", () => {
    if (!state.geometryPlotHover) return;
    state.geometryPlotHover = null;
    drawGeometryPlotPanel();
  });
  document.getElementById("geometry-plot-canvas").addEventListener("click", handleGeometryPlotClick);
  window.addEventListener("keydown", (event) => {
    if (event.key === "Escape" && state.toolchainModalOpen) {
      closeModelicaToolchain();
      event.preventDefault();
      return;
    }
    if (event.key === "Escape" && state.simModalOpen) {
      closeSimulationModal();
      event.preventDefault();
      return;
    }
    if (event.key === "Escape" && state.suspensionPlotModalKey) {
      closeSuspensionPlotModal();
      event.preventDefault();
      return;
    }
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
  document.getElementById("save-vehicle-btn").addEventListener("click", () => saveVehicleAs({ actionKey: "menu-save-vehicle" }));
  document.getElementById("save-raw-btn").addEventListener("click", saveRawVehicle);
  document.getElementById("run-workflow-btn").addEventListener("click", startSelectedWorkflow);
  document.getElementById("run-study-btn")?.addEventListener("click", saveActiveResults);
  document.getElementById("add-processing-btn")?.addEventListener("click", addProcessingWorkflow);
  document.getElementById("remove-processing-btn")?.addEventListener("click", removeSelectedProcessingWorkflow);
  document.getElementById("apply-sim-config-btn").addEventListener("click", applySimConfigEdits);
  document.getElementById("save-sim-config-btn").addEventListener("click", saveSimConfigAs);
  document.getElementById("load-sim-config-btn").addEventListener("click", loadSelectedSimConfig);
  document.getElementById("delete-sim-config-btn").addEventListener("click", deleteSelectedSimConfig);
  document.getElementById("apply-study-config-btn")?.addEventListener("click", applyStudyConfigEdits);
  document.getElementById("save-study-config-btn")?.addEventListener("click", saveStudyConfigAs);
  document.getElementById("load-study-config-btn")?.addEventListener("click", loadSelectedStudyConfig);
  document.getElementById("delete-study-config-btn")?.addEventListener("click", deleteSelectedStudyConfig);
  document.getElementById("sim-config-picker").addEventListener("change", (event) => {
    state.selectedSimConfigSource = event.target.value;
    renderSimConfigLibrary();
  });
  document.getElementById("study-config-picker")?.addEventListener("change", (event) => {
    state.selectedStudyConfigSource = event.target.value;
    renderStudyConfigLibrary();
  });
  document.getElementById("clear-log-btn").addEventListener("click", () => {
    document.getElementById("job-log").textContent = "";
  });
  document.getElementById("clear-study-log-btn")?.addEventListener("click", () => {
    document.getElementById("study-job-log").textContent = "";
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
    if (state.view === "setup") await saveVehicleAs({ useNameInput: false, actionKey: "rail-save-vehicle" });
    else if (state.view === "studies") {
      state.resultsStatusMessage = "Refreshing archive";
      renderStudies();
      await refreshSavedResults();
      state.resultsStatusMessage = "";
      renderStudies();
    }
    else await configureSimulationWorkflow(selectedWorkflow()?.id);
  });
  document.getElementById("rail-secondary-btn").addEventListener("click", async () => {
    if (state.view === "setup") await generateModelicaFromVehicle({ actionKey: "rail-write-mbd" });
    else setView("setup");
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
  document.querySelectorAll(".study-tab").forEach((button) => {
    button.addEventListener("click", () => {
      state.activeStudyTab = button.dataset.studyTab;
      syncStudyTabs();
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
  wireGeometryPlotSplitter();
  wireGeometryEditor();
  wireVehicleCanvas();
  window.addEventListener("resize", () => {
    applySetupPaneWidth();
    applyGeometryPlotHeight();
    drawVehicleFromForm();
    drawArchitectureConnectionCanvas();
    drawSuspensionPlotModal();
    drawGeometryPlotPanel();
    drawResultPlotCanvas();
  });
}

wireEvents();
refresh();
setInterval(async () => {
  if ((state.status?.jobs || []).some((job) => job.status === "running" || job.status === "queued")) {
    state.status = await api("/api/status");
    await refreshSavedResults();
    renderTopbar();
    renderModelicaStack();
    if (state.view === "studies") renderStudies();
    else if (state.view === "standard") renderStandard();
  }
}, 2000);
