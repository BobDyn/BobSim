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
    let body;
    try {
      const response = await fetch("/api/visual/runs");
      body = await response.json();
    } catch (error) {
      // Without this the rejection is unhandled and the tab just sits there
      // blank, which looks identical to a run that is still loading.
      setStatus("Could not reach the app to list captured runs: " + error.message);
      return;
    }
    if (body && body.error) {
      setStatus("Could not list captured runs: " + body.error);
      return;
    }
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
  }

  // ==========================================================================
  // Video export
  //
  // MediaRecorder writes the file; everything below feeds it frames. The old
  // desktop viewer rendered the run off-screen through VTK and handed the
  // frames to imageio, and that is the shape kept here: the export draws the
  // run itself, frame by frame, rather than filming what is on screen.
  //
  // So none of it hangs off the draw loop or the clock. A hidden tab gets no
  // requestAnimationFrame at all and has its timers clamped to about a second,
  // which stalls anything paced by either the moment someone switches tab.
  // Frames are stepped by a counter, pumped through a MessageChannel -- which
  // the browser does not throttle -- and stamped with their own timestamps, so
  // a sixty-second run takes seconds to export and still plays for sixty.
  //
  // MP4 where the browser can write it, WebM where it cannot, and the file is
  // named for whichever the recorder actually chose: nobody is handed an .mp4
  // that is really WebM.
  // ==========================================================================

  const EXPORT_TYPES = [
    "video/mp4;codecs=avc1",
    "video/webm;codecs=vp9",
    "video/webm;codecs=vp8",
    "video/webm",
  ];
  const EXPORT_FPS = 30;
  /** How long to wait for a stopped recorder's final chunk before giving up. */
  const FLUSH_GRACE_MS = 5000;
  const EXPORT_BITRATE = 12e6;

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

  function canGenerateFrames() {
    return (
      typeof window.VideoFrame === "function" &&
      (typeof window.MediaStreamTrackGenerator === "function" ||
        typeof window.VideoTrackGenerator === "function")
    );
  }

  function canExport() {
    if (!exportMimeType()) return false;
    return canGenerateFrames() || typeof HTMLCanvasElement.prototype.captureStream === "function";
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
   * Hand control back to the browser and take it straight back again.
   *
   * A hidden tab clamps `setTimeout` to roughly a second and stops
   * `requestAnimationFrame` outright. A MessageChannel message is delivered at
   * full speed either way, which is the whole reason an export keeps running
   * with the tab in the background.
   */
  function nextTurn() {
    return new Promise((resolve) => {
      const channel = new MessageChannel();
      channel.port1.onmessage = () => {
        channel.port1.close();
        resolve();
      };
      channel.port2.postMessage(0);
    });
  }

  /** Idle until `deadline`, for the sink that can only be filmed in real time. */
  async function waitUntil(deadline) {
    while (performance.now() < deadline) await nextTurn();
  }

  /** A track that VideoFrames can be written into, or null on older browsers. */
  function openGenerator() {
    if (typeof window.VideoFrame !== "function") return null;
    if (typeof window.MediaStreamTrackGenerator === "function") {
      const generator = new window.MediaStreamTrackGenerator({ kind: "video" });
      return { track: generator, writable: generator.writable };
    }
    if (typeof window.VideoTrackGenerator === "function") {
      const generator = new window.VideoTrackGenerator();
      return { track: generator.track, writable: generator.writable };
    }
    return null;
  }

  /**
   * Somewhere to put a drawn frame, and the stream MediaRecorder listens to.
   *
   * The WebCodecs sink stamps each frame with the time it belongs at, so
   * frames can go in as fast as the encoder will take them and the file still
   * comes out the right length. The capture-stream fallback has no such say:
   * the recorder times those frames by when they arrive, so that one has to be
   * played out in real time.
   *
   * Both expose the same two calls. `ready` waits for the encoder to want
   * another frame and is awaited *before* anything is drawn -- grabbing the
   * canvas has to happen in the same task as the draw, because a WebGL
   * drawing buffer does not survive the end of it.
   */
  function openFrameSink(canvas) {
    const generator = openGenerator();
    if (generator) {
      const writer = generator.writable.getWriter();
      return {
        stream: new MediaStream([generator.track]),
        realTime: false,
        ready: () => writer.ready,
        write(microseconds) {
          const frame = new window.VideoFrame(canvas, { timestamp: microseconds });
          return writer.write(frame).finally(() => {
            try {
              frame.close();
            } catch (error) {
              /* the writer already took it */
            }
          });
        },
        async close() {
          try {
            await writer.close();
          } catch (error) {
            /* already ended */
          }
        },
      };
    }

    let stream = canvas.captureStream(0);
    let track = stream.getVideoTracks()[0];
    if (!track || typeof track.requestFrame !== "function") {
      stream.getTracks().forEach((t) => t.stop());
      stream = canvas.captureStream(EXPORT_FPS); // the browser samples it itself
      track = null;
    }
    return {
      stream,
      realTime: true,
      ready: () => Promise.resolve(),
      write() {
        if (track) track.requestFrame();
        return Promise.resolve();
      },
      close() {
        stream.getTracks().forEach((t) => t.stop());
        return Promise.resolve();
      },
    };
  }

  function startExport() {
    const scene = state.scene;
    const viewer = state.viewer;
    if (!scene || !viewer || state.recording) return;
    const mime = exportMimeType();
    if (!mime) return;

    let sink;
    let recorder;
    try {
      sink = openFrameSink(viewer.canvas);
      recorder = new window.MediaRecorder(sink.stream, {
        mimeType: mime,
        videoBitsPerSecond: EXPORT_BITRATE,
      });
    } catch (error) {
      if (sink) sink.close();
      setStatus("Could not start recording: " + error.message);
      return;
    }

    const chunks = [];
    recorder.addEventListener("dataavailable", (event) => {
      if (event.data && event.data.size) chunks.push(event.data);
    });
    // Resolves once the recorder has emitted its final dataavailable.
    let flushed;
    const flushedReady = new Promise((resolve) => {
      flushed = resolve;
    });
    recorder.addEventListener("stop", () => {
      flushed();
      finishExport();
    });
    recorder.addEventListener("error", (event) => {
      setStatus("Recording stopped: " + ((event.error && event.error.message) || "unknown error"));
      stopExport();
    });

    const rec = {
      recorder,
      chunks,
      flushedReady,
      sink,
      runId: state.runId,
      wasPlaying: viewer.playing,
      wasTime: viewer.simTime,
      cancelled: false,
      stopping: false,
    };
    state.recording = rec;

    // The export owns the clock and the canvas until it is done; the live loop
    // would otherwise be advancing time underneath it.
    viewer.playing = false;
    $("replay-play").textContent = "Play";
    recorder.start();
    setExportLabel("Recording 0%", "Click to stop and save what has been recorded");
    setStatus("");
    recordRun(rec).catch((error) => {
      setStatus("Recording stopped: " + error.message);
      stopExport();
    });
  }

  /** Draw the run from its first frame to its last, one exported frame apiece. */
  async function recordRun(rec) {
    const viewer = state.viewer;
    const scene = state.scene;
    const start = scene.time[0];
    const end = scene.time[scene.time.length - 1];
    // A second of video covers `speed` seconds of the run, which is what the
    // viewer shows when it plays it.
    const step = Math.max(scene.header.speed || 1, 1e-3) / EXPORT_FPS;
    const total = Math.max(Math.ceil((end - start) / step) + 1, 1);
    const began = performance.now();

    for (let i = 0; i < total; i++) {
      await rec.sink.ready(); // backpressure: never queue the whole run at once
      if (rec.cancelled) break;
      viewer.simTime = Math.min(start + i * step, end);
      viewer.render();
      if (viewer.onTick) viewer.onTick(viewer.simTime);
      await rec.sink.write(Math.round((i * 1e6) / EXPORT_FPS));
      if (rec.cancelled) break;
      setExportLabel("Recording " + Math.round(((i + 1) / total) * 100) + "%");
      if (rec.sink.realTime) await waitUntil(began + ((i + 1) * 1000) / EXPORT_FPS);
      else await nextTurn();
    }
    stopExport();
  }

  function stopExport() {
    const rec = state.recording;
    if (!rec || rec.stopping) return;
    rec.stopping = true;
    rec.cancelled = true; // ends the frame loop, if it is still running
    setExportLabel("Saving…", "");
    // Close the sink first so the last frames reach the encoder. Ending the
    // track can stop the recorder by itself, which is why the stop below is
    // guarded rather than assumed.
    Promise.resolve(rec.sink.close())
      .then(nextTurn)
      .then(() => {
        try {
          if (rec.recorder.state !== "inactive") {
            rec.recorder.stop(); // the stop listener finishes the export
            return;
          }
        } catch (error) {
          finishExport();
          return;
        }
        // Ending the track stopped the recorder by itself, but its last
        // dataavailable has not landed yet: at this point the chunk list is
        // still empty, and finishing here threw away the whole recording and
        // reported it as "no frames". Wait for the stop event instead, and
        // give up only if it never comes.
        Promise.race([
          rec.flushedReady,
          new Promise((resolve) => window.setTimeout(resolve, FLUSH_GRACE_MS)),
        ]).then(finishExport);
      });
  }

  function finishExport() {
    const rec = state.recording;
    if (!rec) return;
    state.recording = null;
    rec.sink.stream.getTracks().forEach((track) => track.stop());

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
      viewer.render(); // put the frame the export borrowed the view from back
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
      "Render the whole run and download it as ." + exportExtension(mime)
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

    loadRuns().catch((error) => setStatus("Could not open the viewer: " + error.message));

    const frame = (wall) => {
      // An export drives the clock and the canvas itself, at its own pace and
      // without waiting for a frame callback, so the live loop stands aside.
      if (screenActive() && !state.recording) state.viewer.tick(wall);
      requestAnimationFrame(frame);
    };
    requestAnimationFrame(frame);
  }

  function watch() {
    if (screenActive()) start();
  }

  function bootstrap() {
    // The rail is wired by app.js; this only needs to know when its own screen
    // becomes visible, so the WebGL context is not created for people who
    // never open the tab.
    //
    // app.js switches screens inside its own click handler, so this one has to
    // look afterwards rather than during: a microtask is enough and, unlike a
    // timer, is not clamped when the tab is in the background.
    document.querySelectorAll(".rail-item").forEach((button) => {
      button.addEventListener("click", () => Promise.resolve().then(watch));
    });
    watch();
  }

  // Not gated on DOMContentLoaded: this script is loaded at the end of the
  // body, so that event may already have fired, and then the rail would never
  // be wired and the Replay tab would open to nothing at all.
  if (document.readyState === "loading") {
    document.addEventListener("DOMContentLoaded", bootstrap, { once: true });
  } else {
    bootstrap();
  }
})();
