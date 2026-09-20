/* The Replay screen: run picker, timeline, layers, and the tire and metric tabs.
 *
 * visual.js owns the camera and the WebGL draw; this owns the page around it.
 * The split keeps the renderer free of DOM, so the arithmetic that decides how
 * a scene looks can be read without wading through element wiring.
 *
 * It mounts itself. app.js already routes any `.rail-item[data-view]` through
 * setView(), which toggles `.active` on the matching `.screen`, so this needs
 * no hook there -- it watches its own screen and starts when first shown.
 */
(function () {
  "use strict";

  const state = {
    viewer: null,
    scene: null,
    runs: [],
    runId: null,
    tab: "tires",
    started: false,
    metricFilter: "",
    recording: null,
  };

  const $ = (id) => document.getElementById(id);

  function screenActive() {
    const screen = $("replay-view");
    return screen && screen.classList.contains("active");
  }

  // ==========================================================================
  // Loading
  // ==========================================================================

  async function loadRuns() {
    const response = await fetch("/api/visual/runs");
    const body = await response.json();
    state.runs = body.runs || [];
    const picker = $("replay-run");
    picker.innerHTML = "";
    for (const run of state.runs) {
      const option = document.createElement("option");
      option.value = run.id;
      option.textContent = run.label;
      picker.appendChild(option);
    }
    if (!state.runs.length) {
      setStatus(
        "No captured runs yet. Produce one with a rig or manoeuvre capture, " +
          "then reopen this tab."
      );
      return;
    }
    await loadRun(state.runs[0].id);
  }

  async function loadRun(runId) {
    setStatus("Loading " + runId + "…");
    try {
      const [header, buffer] = await Promise.all([
        fetch("/api/visual/scene?run=" + encodeURIComponent(runId)).then((r) => r.json()),
        fetch("/api/visual/data?run=" + encodeURIComponent(runId)).then((r) => r.arrayBuffer()),
      ]);
      if (header.error) throw new Error(header.error);
      state.runId = runId;
      state.scene = new window.BobVis.Scene(header, buffer);
      state.viewer.load(state.scene);
      $("replay-run").value = runId;
      buildLayerToggles(header);
      buildTabs(header);
      setStatus("");
    } catch (error) {
      setStatus("Could not open this run: " + error.message);
    }
  }

  function setStatus(text) {
    const node = $("replay-status");
    node.textContent = text;
    node.hidden = !text;
  }

  // ==========================================================================
  // Controls
  // ==========================================================================

  /** Follow rides with the car; the rest are scene layers. */
  function buildFollowToggle() {
    const menu = $("replay-layers");
    const wrap = document.createElement("label");
    wrap.className = "replay-layer";
    const box = document.createElement("input");
    box.type = "checkbox";
    box.checked = state.viewer.follow;
    box.addEventListener("change", () => {
      state.viewer.follow = box.checked;
    });
    wrap.appendChild(box);
    wrap.appendChild(document.createTextNode("Follow the car"));
    menu.appendChild(wrap);
  }

  const LAYER_LABELS = {
    links: "Links",
    joints: "Joints",
    tires: "Tires",
    loads: "Load footprints",
    tracks: "Contact trails",
    arrows: "Force vectors",
    grid: "Ground grid",
  };

  function buildLayerToggles(header) {
    const menu = $("replay-layers");
    menu.innerHTML = "";
    const available = {
      links: header.links.length > 0,
      joints: header.points.length > 0,
      tires: header.tires.length > 0,
      loads: header.loads.corners.length > 0,
      tracks: header.tracks.corners.length > 0,
      arrows: header.arrows.length > 0,
      grid: true,
    };
    for (const [key, label] of Object.entries(LAYER_LABELS)) {
      if (!available[key]) continue;
      const wrap = document.createElement("label");
      wrap.className = "replay-layer";
      const box = document.createElement("input");
      box.type = "checkbox";
      box.checked = state.viewer.layers[key];
      box.addEventListener("change", () => {
        state.viewer.layers[key] = box.checked;
      });
      wrap.appendChild(box);
      wrap.appendChild(document.createTextNode(label));
      menu.appendChild(wrap);
    }
    buildFollowToggle();
  }

  /** Tabs only appear when the run actually carries their data. */
  function buildTabs(header) {
    const hasGrip = Boolean(header.grip && header.grip.corners && header.grip.corners.length);
    const hasMetrics = Boolean(header.metrics && header.metrics.length);
    $("replay-tab-tires").hidden = !hasGrip;
    $("replay-tab-metrics").hidden = !hasMetrics;
    const strip = $("replay-tabs");
    strip.hidden = !hasGrip && !hasMetrics;
    if (state.tab === "tires" && !hasGrip) state.tab = hasMetrics ? "metrics" : "";
    if (state.tab === "metrics" && !hasMetrics) state.tab = hasGrip ? "tires" : "";
    if (hasMetrics) renderMetrics(header.metrics);
    syncTabs();
  }

  function syncTabs() {
    for (const name of ["tires", "metrics"]) {
      const button = $("replay-tab-" + name);
      const panel = $("replay-panel-" + name);
      const active = state.tab === name && !button.hidden;
      button.classList.toggle("active", active);
      panel.hidden = !active;
    }
  }

  // ==========================================================================
  // Tires tab: a friction circle per corner
  // ==========================================================================

  function renderFrictionCircles(f) {
    const header = state.scene && state.scene.header;
    const grip = header && header.grip;
    if (!grip || !grip.corners || state.tab !== "tires") return;
    const canvas = $("replay-tires-canvas");
    const dpr = Math.min(window.devicePixelRatio || 1, 2);
    const width = Math.round(canvas.clientWidth * dpr);
    const height = Math.round(canvas.clientHeight * dpr);
    if (canvas.width !== width || canvas.height !== height) {
      canvas.width = width;
      canvas.height = height;
    }
    const ctx = canvas.getContext("2d");
    ctx.clearRect(0, 0, width, height);

    const corners = grip.corners;
    const columns = 2;
    const rows = Math.ceil(corners.length / columns);
    const cellW = width / columns;
    const cellH = height / rows;
    const radius = Math.min(cellW, cellH) * 0.34;
    const style = getComputedStyle(document.body);
    const ink = style.getPropertyValue("--ink") || "#18232e";
    const faint = style.getPropertyValue("--line") || "#cfdae2";

    corners.forEach((corner, i) => {
      const cx = (i % columns) * cellW + cellW / 2;
      const cy = Math.floor(i / columns) * cellH + cellH / 2 + 6 * dpr;

      ctx.strokeStyle = faint.trim();
      ctx.lineWidth = 1 * dpr;
      for (const ring of [0.5, 1]) {
        ctx.beginPath();
        ctx.arc(cx, cy, radius * ring, 0, Math.PI * 2);
        ctx.stroke();
      }
      ctx.beginPath();
      ctx.moveTo(cx - radius, cy);
      ctx.lineTo(cx + radius, cy);
      ctx.moveTo(cx, cy - radius);
      ctx.lineTo(cx, cy + radius);
      ctx.stroke();

      const airborne = state.scene.scalar(corner.slot_airborne, f) > 0.5;
      const usage = state.scene.scalar(corner.slot_usage, f);
      const gx = state.scene.scalar(corner.slot_x, f);
      const gy = state.scene.scalar(corner.slot_y, f);

      if (!airborne) {
        // Lateral is the horizontal axis: it is the one a driver feels.
        const px = cx + gy * radius;
        const py = cy - gx * radius;
        ctx.fillStyle = usage >= 1 ? "#d64550" : "#2b7fd4";
        ctx.beginPath();
        ctx.arc(px, py, 5 * dpr, 0, Math.PI * 2);
        ctx.fill();
      }

      ctx.fillStyle = ink.trim();
      ctx.font = `${12 * dpr}px system-ui, sans-serif`;
      ctx.textAlign = "center";
      ctx.fillText(corner.corner.toUpperCase(), cx, cy - radius - 10 * dpr);
      ctx.fillText(
        airborne ? "off the ground" : Math.round(usage * 100) + "% of peak",
        cx,
        cy + radius + 18 * dpr
      );
    });

    const transfer = grip.transfer || {};
    const readout = $("replay-lltd");
    if (transfer.slot_lltd === undefined) {
      readout.textContent = "";
      return;
    }
    const undefinedNow = state.scene.scalar(transfer.slot_lltd_undefined, f) > 0.5;
    readout.textContent = undefinedNow
      ? "LLTD — not enough load transfer to divide"
      : "LLTD " + Math.round(state.scene.scalar(transfer.slot_lltd, f) * 100) + "% front";
  }

  // ==========================================================================
  // Metrics tab
  // ==========================================================================

  function renderMetrics(rows) {
    const body = $("replay-metrics-body");
    body.innerHTML = "";
    const filter = state.metricFilter.trim().toLowerCase();
    const columns = Object.keys(rows[0] || {});
    let shown = 0;
    for (const row of rows) {
      const text = columns.map((c) => row[c]).join(" ").toLowerCase();
      if (filter && !text.includes(filter)) continue;
      const tr = document.createElement("tr");
      for (const column of columns) {
        const td = document.createElement("td");
        td.textContent = row[column];
        tr.appendChild(td);
      }
      body.appendChild(tr);
      shown++;
    }
    const head = $("replay-metrics-head");
    head.innerHTML = "";
    const headRow = document.createElement("tr");
    for (const column of columns) {
      const th = document.createElement("th");
      th.textContent = column;
      headRow.appendChild(th);
    }
    head.appendChild(headRow);
    $("replay-metrics-count").textContent = shown + " of " + rows.length;
  }

  // ==========================================================================
  // Timeline
  // ==========================================================================

  function syncTimeline(simTime) {
    const scene = state.scene;
    if (!scene) return;
    const slider = $("replay-time");
    if (document.activeElement !== slider) {
      slider.value = String(((simTime - scene.time[0]) / Math.max(scene.duration, 1e-6)) * 1000);
    }
    $("replay-clock").textContent = (simTime - scene.time[0]).toFixed(2) + " s";
    renderFrictionCircles(scene.frameAt(simTime));
    if (state.recording) watchExport(simTime);
  }

  // ==========================================================================
  // Video export
  //
  // MediaRecorder over the canvas's own capture stream. The old desktop viewer
  // rendered frames off-screen through VTK and fed them to imageio; this needs
  // neither, which matters because the app has to work with nothing installed
  // and nothing downloaded. MP4 where the browser can write it, WebM where it
  // cannot -- and the file is named for whichever the recorder actually chose,
  // so nobody is handed an .mp4 that is really WebM.
  // ==========================================================================

  const EXPORT_TYPES = [
    "video/mp4;codecs=avc1",
    "video/webm;codecs=vp9",
    "video/webm;codecs=vp8",
    "video/webm",
  ];
  const EXPORT_FPS = 60; // only used when the browser cannot hand over frames on demand
  const EXPORT_BITRATE = 12e6;
  const EXPORT_SLACK_MS = 15000; // wall-clock grace on top of the run's own length

  /** The best container this browser can write, or null if it can write none. */
  function exportMimeType() {
    if (typeof window.MediaRecorder !== "function") return null;
    const supported = window.MediaRecorder.isTypeSupported;
    if (typeof supported !== "function") return "video/webm"; // the historical default
    for (const mime of EXPORT_TYPES) {
      if (supported.call(window.MediaRecorder, mime)) return mime;
    }
    return null;
  }

  function canExport() {
    return Boolean(exportMimeType()) && typeof HTMLCanvasElement.prototype.captureStream === "function";
  }

  function exportExtension(mime) {
    return String(mime || "").includes("mp4") ? "mp4" : "webm";
  }

  function setExportLabel(text, title) {
    const button = $("replay-export");
    button.textContent = text;
    if (title !== undefined) button.title = title;
  }

  /**
   * A stream that carries every frame the viewer draws.
   *
   * At a frame rate of 0 the track hands over exactly the frames it is asked
   * for, and the draw loop asks once per render -- so a slow frame is a slow
   * frame in the file rather than a dropped one. Browsers without
   * `requestFrame` get a timed capture instead.
   */
  function captureCanvas(canvas) {
    let stream = canvas.captureStream(0);
    let track = stream.getVideoTracks()[0];
    if (track && typeof track.requestFrame === "function") return { stream, track };
    stream.getTracks().forEach((t) => t.stop());
    stream = canvas.captureStream(EXPORT_FPS);
    return { stream, track: null };
  }

  function startExport() {
    const scene = state.scene;
    const viewer = state.viewer;
    if (!scene || !viewer || state.recording) return;
    const mime = exportMimeType();
    if (!mime) return;

    let capture;
    let recorder;
    try {
      capture = captureCanvas(viewer.canvas);
      recorder = new window.MediaRecorder(capture.stream, {
        mimeType: mime,
        videoBitsPerSecond: EXPORT_BITRATE,
      });
    } catch (error) {
      if (capture) capture.stream.getTracks().forEach((t) => t.stop());
      setStatus("Could not start recording: " + error.message);
      return;
    }

    const chunks = [];
    recorder.addEventListener("dataavailable", (event) => {
      if (event.data && event.data.size) chunks.push(event.data);
    });
    recorder.addEventListener("stop", () => finishExport());
    recorder.addEventListener("error", (event) => {
      setStatus("Recording stopped: " + ((event.error && event.error.message) || "unknown error"));
      stopExport();
    });

    const start = scene.time[0];
    const speed = scene.header.speed || 1;
    state.recording = {
      recorder,
      chunks,
      stream: capture.stream,
      track: capture.track,
      runId: state.runId,
      lastTime: start,
      wasPlaying: viewer.playing,
      wasTime: viewer.simTime,
      deadline: Date.now() + (scene.duration / Math.max(speed, 1e-3)) * 1000 + EXPORT_SLACK_MS,
      stopping: false,
    };

    // Record the run whole: back to the top, and playing.
    viewer.simTime = start;
    viewer.playing = true;
    $("replay-play").textContent = "Pause";
    recorder.start();
    setExportLabel("Recording 0%", "Click to stop and save what has been recorded");
    setStatus("");
  }

  /** Called every drawn frame: report progress, and stop at the end of the run. */
  function watchExport(simTime) {
    const rec = state.recording;
    const scene = state.scene;
    if (!rec || !scene) return;
    const start = scene.time[0];
    const end = scene.time[scene.time.length - 1];
    const span = Math.max(end - start, 1e-6);
    // The viewer loops back to the top when it runs off the end; that wrap is
    // how the recording knows the run is done.
    const wrapped = simTime < rec.lastTime - 1e-9;
    rec.lastTime = simTime;
    const done = wrapped || simTime >= end - 1e-9 || Date.now() > rec.deadline;
    const progress = done ? 1 : Math.min(Math.max((simTime - start) / span, 0), 1);
    if (!rec.stopping) setExportLabel("Recording " + Math.round(progress * 100) + "%");
    if (done) stopExport();
  }

  function stopExport() {
    const rec = state.recording;
    if (!rec || rec.stopping) return;
    rec.stopping = true;
    setExportLabel("Saving…", "");
    try {
      rec.recorder.stop();
    } catch (error) {
      finishExport();
    }
  }

  function finishExport() {
    const rec = state.recording;
    if (!rec) return;
    state.recording = null;
    rec.stream.getTracks().forEach((track) => track.stop());

    const mime = rec.recorder.mimeType || "video/webm";
    if (rec.chunks.length) {
      const blob = new Blob(rec.chunks, { type: mime });
      const name = String(rec.runId || "replay").replace(/[^A-Za-z0-9._-]+/g, "-");
      download(blob, name + "." + exportExtension(mime));
      setStatus("");
    } else {
      setStatus("Recording produced no frames, so nothing was saved.");
    }

    const viewer = state.viewer;
    if (viewer) {
      viewer.simTime = rec.wasTime;
      viewer.playing = rec.wasPlaying;
      $("replay-play").textContent = viewer.playing ? "Pause" : "Play";
    }
    resetExportButton();
  }

  function download(blob, fileName) {
    const url = URL.createObjectURL(blob);
    const link = document.createElement("a");
    link.href = url;
    link.download = fileName;
    document.body.appendChild(link);
    link.click();
    link.remove();
    // Firefox needs the URL to outlive the click by a moment.
    window.setTimeout(() => URL.revokeObjectURL(url), 30000);
  }

  function resetExportButton() {
    const mime = exportMimeType();
    setExportLabel(
      "Export video",
      "Play the run from the start and download it as ." + exportExtension(mime)
    );
  }

  // ==========================================================================
  // Mount
  // ==========================================================================

  function start() {
    if (state.started) return;
    state.started = true;
    try {
      state.viewer = new window.BobVis.Viewer($("replay-canvas"));
    } catch (error) {
      setStatus(error.message);
      return;
    }
    state.viewer.onTick = syncTimeline;
    // Handy from the console when a scene looks wrong: window.BobVis.viewer
    // holds the live camera, layers and clock.
    window.BobVis.viewer = state.viewer;

    $("replay-run").addEventListener("change", (event) => loadRun(event.target.value));
    $("replay-play").addEventListener("click", () => {
      state.viewer.playing = !state.viewer.playing;
      $("replay-play").textContent = state.viewer.playing ? "Pause" : "Play";
    });
    $("replay-reset-view").addEventListener("click", () => state.viewer.resetView());
    const exportButton = $("replay-export");
    if (canExport()) {
      resetExportButton();
      exportButton.addEventListener("click", () => {
        if (state.recording) stopExport();
        else startExport();
      });
    } else {
      exportButton.disabled = true;
      exportButton.title =
        "This browser cannot record the view: it has no MediaRecorder video codec " +
        "or no canvas capture. Chrome, Edge and Firefox can.";
    }
    $("replay-time").addEventListener("input", (event) => {
      const scene = state.scene;
      if (!scene) return;
      state.viewer.playing = false;
      $("replay-play").textContent = "Play";
      state.viewer.simTime = scene.time[0] + (Number(event.target.value) / 1000) * scene.duration;
    });
    for (const name of ["tires", "metrics"]) {
      $("replay-tab-" + name).addEventListener("click", () => {
        state.tab = name;
        syncTabs();
      });
    }
    $("replay-metric-filter").addEventListener("input", (event) => {
      state.metricFilter = event.target.value;
      if (state.scene) renderMetrics(state.scene.header.metrics);
    });
    $("replay-help-btn").addEventListener("click", () => {
      $("replay-help").hidden = !$("replay-help").hidden;
    });
    document.addEventListener("keydown", (event) => {
      if (!screenActive()) return;
      if (event.key === "F1") {
        event.preventDefault();
        $("replay-help").hidden = !$("replay-help").hidden;
      } else if (event.key === " ") {
        event.preventDefault();
        $("replay-play").click();
      }
    });

    loadRuns();

    const frame = (wall) => {
      if (screenActive()) {
        state.viewer.tick(wall);
        // Hand the freshly drawn frame to the recorder inside the same task
        // that drew it, while the drawing buffer still holds it.
        const rec = state.recording;
        if (rec && rec.track && !rec.stopping) rec.track.requestFrame();
      }
      requestAnimationFrame(frame);
    };
    requestAnimationFrame(frame);
  }

  function watch() {
    if (screenActive()) start();
  }

  document.addEventListener("DOMContentLoaded", () => {
    // The rail is wired by app.js; this only needs to know when its own screen
    // becomes visible, so the WebGL context is not created for people who
    // never open the tab.
    document.querySelectorAll(".rail-item").forEach((button) => {
      button.addEventListener("click", () => window.setTimeout(watch, 0));
    });
    watch();
  });
})();
