/* BobVis: the replay viewer, in the browser.
 *
 * Draws a run's suspension geometry, tire loads and forces from the payload
 * that _5_App/visual.py builds. Plain WebGL2 and plain DOM, like the rest of
 * _5_App/static: no framework, no build step, no dependency to vendor.
 *
 * The whole scene is two instanced draw programs. Segments cover links, the
 * ground grid, contact-patch trails and force arrows; discs cover tires, load
 * footprints and -- billboarded to face the camera -- joints. Adding a shader
 * per shape is how the VTK version grew to 1,300 lines of scene code, so
 * everything here is expressed as one of those two.
 *
 * The camera is a direct port of _1_VisualSim/navigation.py, constants and
 * all. That arithmetic is what made the first attempt at these controls feel
 * wrong (#48, reverted in #50); it is kept identical here so the behaviour the
 * Python tests pin is the behaviour the browser has.
 */
(function () {
  "use strict";

  // ==========================================================================
  // Vectors and matrices
  // ==========================================================================

  const sub = (a, b) => [a[0] - b[0], a[1] - b[1], a[2] - b[2]];
  const add = (a, b) => [a[0] + b[0], a[1] + b[1], a[2] + b[2]];
  const scale = (a, k) => [a[0] * k, a[1] * k, a[2] * k];
  const dot = (a, b) => a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
  const norm = (a) => Math.sqrt(dot(a, a));
  const cross = (a, b) => [
    a[1] * b[2] - a[2] * b[1],
    a[2] * b[0] - a[0] * b[2],
    a[0] * b[1] - a[1] * b[0],
  ];

  /** Unit vector, or `fallback` when `v` is too short to have a direction. */
  function unit(v, fallback) {
    const n = norm(v);
    return n > 1e-12 ? scale(v, 1 / n) : fallback.slice();
  }

  function perspective(fovYDeg, aspect, near, far) {
    const f = 1 / Math.tan((fovYDeg * Math.PI) / 360);
    const d = near - far;
    // prettier-ignore
    return [f / aspect, 0, 0, 0,
            0, f, 0, 0,
            0, 0, (far + near) / d, -1,
            0, 0, (2 * far * near) / d, 0];
  }

  function lookAt(eye, target, up) {
    const f = unit(sub(target, eye), [0, 1, 0]);
    const s = unit(cross(f, up), [1, 0, 0]);
    const u = cross(s, f);
    // prettier-ignore
    return [s[0], u[0], -f[0], 0,
            s[1], u[1], -f[1], 0,
            s[2], u[2], -f[2], 0,
            -dot(s, eye), -dot(u, eye), dot(f, eye), 1];
  }

  function multiply(a, b) {
    const out = new Array(16).fill(0);
    for (let c = 0; c < 4; c++) {
      for (let r = 0; r < 4; r++) {
        let sum = 0;
        for (let k = 0; k < 4; k++) sum += a[k * 4 + r] * b[c * 4 + k];
        out[c * 4 + r] = sum;
      }
    }
    return out;
  }

  // ==========================================================================
  // Camera — a port of _1_VisualSim/navigation.py
  //
  // Screen deltas are pixels: x right, y down. NDC runs -1..1 with y up. Drags
  // are "grab" semantics: the scene follows the cursor, the camera goes the
  // other way. Orbit is turntable about world +Z, so the horizon never rolls.
  // ==========================================================================

  const WORLD_UP = [0, 0, 1];
  const ZOOM_PER_NOTCH = 1.15;
  const WHEEL_PX_PER_NOTCH = 40;
  const ORBIT_DEG_PER_PX = 0.3;
  const MIN_POLAR_DEG = 1;
  const MIN_DISTANCE = 0.05;
  const GROUND_REACH = 20;

  function cameraBasis(pose) {
    const forward = unit(sub(pose.focal, pose.position), [0, 1, 0]);
    const right = unit(cross(forward, pose.up), [1, 0, 0]);
    return { forward, right, up: cross(right, forward) };
  }

  /** Half the visible height of the focal plane, in world units. */
  function halfHeight(pose) {
    const distance = norm(sub(pose.focal, pose.position));
    return distance * Math.tan((pose.viewAngle * Math.PI) / 360);
  }

  function orbit(pose, dAzimuthDeg, dElevationDeg) {
    const offset = sub(pose.position, pose.focal);
    const radius = norm(offset);
    if (radius < 1e-9) return pose;

    let horizontal = [offset[0], offset[1]];
    if (Math.hypot(horizontal[0], horizontal[1]) < 1e-6 * radius) {
      // Straight down or up: azimuth is undefined, so take it from the screen's
      // up direction, which keeps the picture from spinning as the tilt starts.
      horizontal = [-pose.up[0], -pose.up[1]];
      if (Math.hypot(horizontal[0], horizontal[1]) < 1e-9) horizontal = [-1, 0];
    }

    const azimuth = Math.atan2(horizontal[1], horizontal[0]) + (dAzimuthDeg * Math.PI) / 180;
    const minPolar = (MIN_POLAR_DEG * Math.PI) / 180;
    let polar = Math.acos(Math.min(1, Math.max(-1, offset[2] / radius)));
    polar -= (dElevationDeg * Math.PI) / 180;
    polar = Math.min(Math.PI - minPolar, Math.max(minPolar, polar));

    const position = add(pose.focal, [
      radius * Math.sin(polar) * Math.cos(azimuth),
      radius * Math.sin(polar) * Math.sin(azimuth),
      radius * Math.cos(polar),
    ]);
    const forward = unit(sub(pose.focal, position), [0, 1, 0]);
    const right = unit(cross(forward, WORLD_UP), [1, 0, 0]);
    return { ...pose, position, up: cross(right, forward) };
  }

  function pan(pose, dxPx, dyPx, viewportHeightPx) {
    const { right, up } = cameraBasis(pose);
    const perPx = (2 * halfHeight(pose)) / Math.max(viewportHeightPx, 1);
    const shift = scale(add(scale(right, -dxPx), scale(up, dyPx)), perPx);
    return { ...pose, position: add(pose.position, shift), focal: add(pose.focal, shift) };
  }

  /** World point on the focal plane under a screen position. */
  function focalPlanePoint(pose, ndcX, ndcY, aspect) {
    const { right, up } = cameraBasis(pose);
    const h = halfHeight(pose);
    return add(pose.focal, add(scale(right, ndcX * h * aspect), scale(up, ndcY * h)));
  }

  /** Where the cursor ray meets the plane z = height, or null. */
  function groundPlanePoint(pose, ndcX, ndcY, aspect, height) {
    const through = focalPlanePoint(pose, ndcX, ndcY, aspect);
    const origin = pose.position;
    const direction = unit(sub(through, origin), [0, 1, 0]);
    if (Math.abs(direction[2]) < 1e-9) return null;
    const along = (height - origin[2]) / direction[2];
    if (along <= 0) return null;
    const point = add(origin, scale(direction, along));
    // Grazing the horizon lands a world away; recentring there would leave the
    // car a speck, so the caller falls back to something nearer.
    const distance = norm(sub(pose.focal, pose.position));
    if (norm(sub(point, pose.position)) > GROUND_REACH * Math.max(distance, MIN_DISTANCE)) return null;
    return point;
  }

  /** Zoom toward the point under the cursor, which stays put on screen. */
  function zoomAt(pose, factor, ndcX, ndcY, aspect) {
    if (!(factor > 0) || Math.abs(factor - 1) < 1e-12) return pose;
    const target = focalPlanePoint(pose, ndcX, ndcY, aspect);
    const distance = norm(sub(pose.focal, pose.position));
    if (distance < 1e-9) return pose;
    const newDistance = Math.max(distance / factor, Math.min(MIN_DISTANCE, distance));
    const keep = newDistance / distance;
    const position = add(pose.position, scale(sub(target, pose.position), 1 - keep));
    return { ...pose, position, focal: add(position, scale(sub(pose.focal, pose.position), keep)) };
  }

  function recenter(pose, point) {
    const shift = sub(point, pose.focal);
    return { ...pose, position: add(pose.position, shift), focal: add(pose.focal, shift) };
  }

  /** Zoom factor for a scroll of `pixels`: up (negative) zooms in. */
  function zoomFactorForPixels(pixels) {
    return Math.pow(ZOOM_PER_NOTCH, -pixels / WHEEL_PX_PER_NOTCH);
  }

  /** A wheel event's scroll in pixels, whatever units it chose to report. */
  function wheelPixels(event) {
    const k = event.deltaMode === 1 ? 16 : event.deltaMode === 2 ? 400 : 1; // lines, pages
    return [event.deltaX * k, event.deltaY * k];
  }

  /**
   * Zoom factor for a wheel event, proportional to how far it scrolled.
   *
   * Scroll zooms on every device. A mouse wheel arrives in whole notches and a
   * trackpad in fractions of one; both mean the same thing, so nothing has to
   * work out which it was — guessing is what made the trackpad feel broken.
   */
  function wheelZoomFactor(event) {
    return zoomFactorForPixels(wheelPixels(event)[1]);
  }

  // ==========================================================================
  // Colour
  // ==========================================================================

  function hexToRgb(hex) {
    const clean = String(hex || "").replace("#", "");
    const full = clean.length === 3 ? clean.split("").map((c) => c + c).join("") : clean;
    const n = parseInt(full, 16);
    if (!Number.isFinite(n) || full.length !== 6) return [0.4, 0.4, 0.4];
    return [((n >> 16) & 255) / 255, ((n >> 8) & 255) / 255, (n & 255) / 255];
  }

  const COOLWARM = [
    [0.23, 0.299, 0.754],
    [0.865, 0.865, 0.865],
    [0.706, 0.016, 0.15],
  ];

  /** Blue when unloaded, neutral at the reference load, red at twice it. */
  function loadColor(ratio) {
    const t = Math.min(1, Math.max(0, 0.5 * ratio)) * 2;
    const i = t < 1 ? 0 : 1;
    const f = t < 1 ? t : t - 1;
    return COOLWARM[i].map((c, k) => c + (COOLWARM[i + 1][k] - c) * f);
  }

  // ==========================================================================
  // WebGL
  // ==========================================================================

  const SEGMENT_VS = `#version 300 es
  precision highp float;
  layout(location=0) in vec2 aCorner;   // t along the segment, side (-1|1)
  layout(location=1) in vec3 aStart;
  layout(location=2) in vec3 aEnd;
  layout(location=3) in vec3 aColor;
  layout(location=4) in float aRadius;
  uniform mat4 uViewProj;
  uniform vec3 uEye;
  out vec3 vColor;
  void main() {
    vec3 pos = mix(aStart, aEnd, aCorner.x);
    vec3 along = aEnd - aStart;
    float len = length(along);
    vec3 dir = len > 1e-9 ? along / len : vec3(1.0, 0.0, 0.0);
    vec3 toEye = uEye - pos;
    vec3 side = cross(dir, toEye);
    float sideLen = length(side);
    // A segment pointing straight at the eye has no ribbon direction; any
    // perpendicular will do, and it is a sliver on screen either way.
    side = sideLen > 1e-9 ? side / sideLen : vec3(0.0, 0.0, 1.0);
    pos += side * (aCorner.y * aRadius);
    vColor = aColor;
    gl_Position = uViewProj * vec4(pos, 1.0);
  }`;

  const SEGMENT_FS = `#version 300 es
  precision highp float;
  in vec3 vColor;
  out vec4 fragColor;
  void main() { fragColor = vec4(vColor, 1.0); }`;

  const DISC_VS = `#version 300 es
  precision highp float;
  layout(location=0) in vec2 aUnit;     // a point on the unit circle
  layout(location=1) in vec3 aCenter;
  layout(location=2) in vec3 aAxisX;
  layout(location=3) in vec3 aAxisY;
  layout(location=4) in vec4 aColor;    // rgb + alpha
  uniform mat4 uViewProj;
  out vec4 vColor;
  void main() {
    vec3 pos = aCenter + aAxisX * aUnit.x + aAxisY * aUnit.y;
    vColor = aColor;
    gl_Position = uViewProj * vec4(pos, 1.0);
  }`;

  const DISC_FS = `#version 300 es
  precision highp float;
  in vec4 vColor;
  out vec4 fragColor;
  void main() { fragColor = vColor; }`;

  function compile(gl, type, source) {
    const shader = gl.createShader(type);
    gl.shaderSource(shader, source.trim());
    gl.compileShader(shader);
    if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
      throw new Error("shader: " + gl.getShaderInfoLog(shader));
    }
    return shader;
  }

  function program(gl, vs, fs) {
    const prog = gl.createProgram();
    gl.attachShader(prog, compile(gl, gl.VERTEX_SHADER, vs));
    gl.attachShader(prog, compile(gl, gl.FRAGMENT_SHADER, fs));
    gl.linkProgram(prog);
    if (!gl.getProgramParameter(prog, gl.LINK_STATUS)) {
      throw new Error("link: " + gl.getProgramInfoLog(prog));
    }
    return prog;
  }

  /**
   * An instanced batch: fixed base geometry, one instance per thing drawn.
   *
   * Instance data is rebuilt into a scratch array every frame and uploaded in
   * one call. At a few hundred instances that costs less than tracking which
   * ones changed.
   */
  class Batch {
    constructor(gl, prog, baseGeometry, attributes, floatsPerInstance) {
      this.gl = gl;
      this.prog = prog;
      this.vertexCount = baseGeometry.length / 2;
      this.floatsPerInstance = floatsPerInstance;
      this.vao = gl.createVertexArray();
      gl.bindVertexArray(this.vao);

      const base = gl.createBuffer();
      gl.bindBuffer(gl.ARRAY_BUFFER, base);
      gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(baseGeometry), gl.STATIC_DRAW);
      gl.enableVertexAttribArray(0);
      gl.vertexAttribPointer(0, 2, gl.FLOAT, false, 0, 0);

      this.instanceBuffer = gl.createBuffer();
      gl.bindBuffer(gl.ARRAY_BUFFER, this.instanceBuffer);
      const stride = floatsPerInstance * 4;
      let offset = 0;
      attributes.forEach((size, i) => {
        const loc = i + 1;
        gl.enableVertexAttribArray(loc);
        gl.vertexAttribPointer(loc, size, gl.FLOAT, false, stride, offset);
        gl.vertexAttribDivisor(loc, 1);
        offset += size * 4;
      });
      gl.bindVertexArray(null);

      this.scratch = new Float32Array(floatsPerInstance * 256);
      this.count = 0;
    }

    begin() {
      this.count = 0;
    }

    /** Room for one more instance, growing the scratch array by doubling. */
    slot() {
      const need = (this.count + 1) * this.floatsPerInstance;
      if (need > this.scratch.length) {
        const grown = new Float32Array(Math.max(need, this.scratch.length * 2));
        grown.set(this.scratch);
        this.scratch = grown;
      }
      return this.count++ * this.floatsPerInstance;
    }

    draw(uniforms) {
      if (this.count === 0) return;
      const gl = this.gl;
      gl.useProgram(this.prog);
      for (const [name, value] of Object.entries(uniforms)) {
        const loc = gl.getUniformLocation(this.prog, name);
        if (loc === null) continue;
        if (value.length === 16) gl.uniformMatrix4fv(loc, false, value);
        else gl.uniform3fv(loc, value);
      }
      gl.bindVertexArray(this.vao);
      gl.bindBuffer(gl.ARRAY_BUFFER, this.instanceBuffer);
      gl.bufferData(gl.ARRAY_BUFFER, this.scratch.subarray(0, this.count * this.floatsPerInstance), gl.DYNAMIC_DRAW);
      gl.drawArraysInstanced(gl.TRIANGLES, 0, this.vertexCount, this.count);
      gl.bindVertexArray(null);
    }
  }

  const QUAD = [0, -1, 1, -1, 1, 1, 0, -1, 1, 1, 0, 1];

  function circleGeometry(segments) {
    const verts = [];
    for (let i = 0; i < segments; i++) {
      const a = (i / segments) * Math.PI * 2;
      const b = ((i + 1) / segments) * Math.PI * 2;
      verts.push(0, 0, Math.cos(a), Math.sin(a), Math.cos(b), Math.sin(b));
    }
    return verts;
  }

  // ==========================================================================
  // Scene
  // ==========================================================================

  /** A loaded run: the header, plus typed views into its float32 buffer. */
  class Scene {
    constructor(header, buffer) {
      this.header = header;
      this.floats = new Float32Array(buffer);
      const layout = header.layout;
      this.frames = header.frames;
      this.pointCount = header.points.length;
      this.time = this.block(layout.time);
      this.positions = this.block(layout.positions);
      this.scalars = this.block(layout.scalars);
      this.vectors = this.block(layout.vectors);
      this.scalarStride = this.frames ? layout.scalars.count / this.frames : 0;
      this.vectorStride = this.frames ? layout.vectors.count / this.frames / 3 : 0;
      this.duration = header.duration || 0;

      for (const group of header.links) group.rgb = hexToRgb(group.color);
      for (const arrow of header.arrows) arrow.rgb = hexToRgb(arrow.color);
      for (const corner of header.tracks.corners) corner.rgb = hexToRgb(corner.color);
      this.jointRgb = hexToRgb(header.joints.color);
    }

    block(entry) {
      return this.floats.subarray(entry.offset, entry.offset + entry.count);
    }

    /** Fractional frame index for a time in seconds. */
    frameAt(seconds) {
      const t = this.time;
      if (t.length < 2) return 0;
      const clamped = Math.min(Math.max(seconds, t[0]), t[t.length - 1]);
      let lo = 0;
      let hi = t.length - 1;
      while (hi - lo > 1) {
        const mid = (lo + hi) >> 1;
        if (t[mid] <= clamped) lo = mid;
        else hi = mid;
      }
      const span = t[hi] - t[lo];
      return lo + (span > 1e-12 ? (clamped - t[lo]) / span : 0);
    }

    /** Point `p` at fractional frame `f`, written into `out`. */
    point(p, f, out) {
      const lo = Math.floor(f);
      const hi = Math.min(lo + 1, this.frames - 1);
      const a = f - lo;
      const iLo = (lo * this.pointCount + p) * 3;
      const iHi = (hi * this.pointCount + p) * 3;
      for (let k = 0; k < 3; k++) {
        const v0 = this.positions[iLo + k];
        out[k] = v0 + (this.positions[iHi + k] - v0) * a;
      }
      return out;
    }

    scalar(slot, f) {
      const lo = Math.floor(f);
      const hi = Math.min(lo + 1, this.frames - 1);
      const a = f - lo;
      const v0 = this.scalars[lo * this.scalarStride + slot];
      return v0 + (this.scalars[hi * this.scalarStride + slot] - v0) * a;
    }

    vector(slot, f, out) {
      const lo = Math.floor(f);
      const hi = Math.min(lo + 1, this.frames - 1);
      const a = f - lo;
      const iLo = (lo * this.vectorStride + slot) * 3;
      const iHi = (hi * this.vectorStride + slot) * 3;
      for (let k = 0; k < 3; k++) {
        const v0 = this.vectors[iLo + k];
        out[k] = v0 + (this.vectors[iHi + k] - v0) * a;
      }
      return out;
    }

    /** Centre of the car at a frame, used to frame the initial view. */
    centroid(f) {
      const out = [0, 0, 0];
      const p = [0, 0, 0];
      if (!this.pointCount) return out;
      for (let i = 0; i < this.pointCount; i++) {
        this.point(i, f, p);
        out[0] += p[0];
        out[1] += p[1];
        out[2] += p[2];
      }
      return scale(out, 1 / this.pointCount);
    }

    extent(f) {
      const p = [0, 0, 0];
      const c = this.centroid(f);
      let max = 1;
      for (let i = 0; i < this.pointCount; i++) {
        this.point(i, f, p);
        max = Math.max(max, norm(sub(p, c)));
      }
      return max;
    }
  }

  // ==========================================================================
  // Viewer
  // ==========================================================================

  class Viewer {
    constructor(canvas) {
      this.canvas = canvas;
      const gl = canvas.getContext("webgl2", { antialias: true, alpha: false });
      if (!gl) throw new Error("This view needs WebGL2, which this browser did not provide.");
      this.gl = gl;
      gl.enable(gl.DEPTH_TEST);
      gl.enable(gl.BLEND);
      gl.blendFunc(gl.SRC_ALPHA, gl.ONE_MINUS_SRC_ALPHA);

      this.segments = new Batch(gl, program(gl, SEGMENT_VS, SEGMENT_FS), QUAD, [3, 3, 3, 1], 10);
      this.discs = new Batch(gl, program(gl, DISC_VS, DISC_FS), circleGeometry(36), [3, 3, 3, 4], 13);

      this.scene = null;
      this.pose = null;
      this.playing = true;
      this.simTime = 0;
      this.layers = { links: true, joints: true, tires: true, loads: true, tracks: true, arrows: true, grid: true };
      // The car drives away from wherever the view was framed, so by default
      // the camera rides with it. Following moves the whole pose by the car's
      // own delta, which keeps whatever orbit, pan and zoom the user chose.
      this.follow = true;
      this._anchor = null;
      this.onTick = null;
      this._scratch = [[0, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0]];
      this._lastWall = 0;
      this.bindInput();
    }

    load(scene) {
      this.scene = scene;
      this.simTime = scene.time.length ? scene.time[0] : 0;
      this.resetView();
    }

    /** The point the camera rides with: the config's attach point, else the centre. */
    anchorAt(f) {
      const scene = this.scene;
      const attach = scene.header.camera && scene.header.camera.attach_to;
      const index = attach ? scene.header.points.indexOf(attach) : -1;
      return index >= 0 ? scene.point(index, f, [0, 0, 0]) : scene.centroid(f);
    }

    /** Frame the car from three-quarters front, the way the rig shots read. */
    resetView() {
      const scene = this.scene;
      if (!scene) return;
      this._anchor = null;
      const focal = scene.centroid(0);
      const reach = scene.extent(0) * 2.6 + 1;
      this.pose = {
        position: add(focal, [reach * 0.75, -reach * 0.85, reach * 0.5]),
        focal,
        up: WORLD_UP.slice(),
        viewAngle: 30,
      };
    }

    // -- input --------------------------------------------------------------
    //
    // Every rule below keys off something the browser states outright: which
    // button is down, how many pointers are down, whether a modifier is held,
    // whether the wheel event carries sideways scroll or `ctrlKey`. None of it
    // asks what kind of device sent the event, because Windows does not say.
    // Guessing is exactly what made the trackpad feel broken the first time
    // (#48, reverted in #50), and it is not coming back.

    bindInput() {
      const canvas = this.canvas;
      // The page must never scroll, rubber-band or browser-zoom while a gesture
      // belongs to the canvas; the wheel and gesture handlers below preventDefault
      // for the same reason.
      canvas.style.touchAction = "none";
      this.bindPointers();
      this.bindWheel();

      // Double-click recentres on whatever is under the cursor, including the
      // floor. The VTK version drew the ground unpickable, so clicking it --
      // the obvious thing to do -- did nothing at all.
      canvas.addEventListener("dblclick", (event) => {
        if (!this.pose) return;
        const [ndcX, ndcY] = this.ndc(event);
        const hit = groundPlanePoint(this.pose, ndcX, ndcY, this.aspect(), 0);
        if (hit) this.pose = recenter(this.pose, hit);
      });

      canvas.addEventListener("contextmenu", (event) => event.preventDefault());
      // Safari sends these alongside a pinch; unhandled they zoom the page.
      for (const name of ["gesturestart", "gesturechange", "gestureend"]) {
        canvas.addEventListener(name, (event) => event.preventDefault());
      }
    }

    /**
     * Drags, from a mouse, a pen or fingers.
     *
     * One pointer orbits, or pans when shift or a non-primary button says so.
     * Two pointers -- which only a touchscreen produces -- pan by how far their
     * midpoint moved and zoom by how much their separation changed, both at
     * once, which is what a pinch actually is.
     */
    bindPointers() {
      const canvas = this.canvas;
      const active = new Map(); // pointerId -> last client position
      let mode = null; // "orbit" | "pan", while exactly one pointer is down
      let pinch = null; // {distance, center}, while two are

      const pair = () => Array.from(active.values());
      const spread = (a, b) => Math.hypot(a.x - b.x, a.y - b.y);
      const middle = (a, b) => [(a.x + b.x) / 2, (a.y + b.y) / 2];

      canvas.addEventListener("pointerdown", (event) => {
        if (!this.pose) return;
        // Touch and pen only: on a mouse this would cost the double-click that
        // recentres the view.
        if (event.pointerType !== "mouse") event.preventDefault();
        canvas.setPointerCapture(event.pointerId);
        active.set(event.pointerId, { x: event.clientX, y: event.clientY });
        if (active.size === 1) {
          mode = event.shiftKey || event.button === 1 || event.button === 2 ? "pan" : "orbit";
        } else if (active.size === 2) {
          const [a, b] = pair();
          pinch = { distance: spread(a, b), center: middle(a, b) };
          mode = null; // a second finger ends whatever the first was doing
        }
      });

      canvas.addEventListener("pointermove", (event) => {
        const previous = active.get(event.pointerId);
        if (!previous || !this.pose) return;
        const dx = event.clientX - previous.x;
        const dy = event.clientY - previous.y;
        previous.x = event.clientX;
        previous.y = event.clientY;

        if (active.size === 2 && pinch) {
          const [a, b] = pair();
          const distance = spread(a, b);
          const center = middle(a, b);
          this.pose = pan(
            this.pose,
            center[0] - pinch.center[0],
            center[1] - pinch.center[1],
            canvas.clientHeight
          );
          if (pinch.distance > 1 && distance > 1) {
            const [ndcX, ndcY] = this.ndcAt(center[0], center[1]);
            this.pose = zoomAt(this.pose, distance / pinch.distance, ndcX, ndcY, this.aspect());
          }
          pinch = { distance, center };
          return;
        }
        if (active.size !== 1 || !mode) return;
        if (mode === "pan") {
          this.pose = pan(this.pose, dx, dy, canvas.clientHeight);
        } else {
          this.pose = orbit(this.pose, -dx * ORBIT_DEG_PER_PX, -dy * ORBIT_DEG_PER_PX);
        }
      });

      const release = (event) => {
        if (!active.delete(event.pointerId)) return;
        pinch = null;
        // A finger left over from a pinch does nothing until it is put down
        // again; carrying on would snap the view to whichever one lifted.
        mode = null;
      };
      canvas.addEventListener("pointerup", release);
      canvas.addEventListener("pointercancel", release);
      canvas.addEventListener("lostpointercapture", release);
    }

    /**
     * Scroll, in the three shapes a browser reports it.
     *
     * `ctrlKey` is a trackpad pinch -- the browser sets it itself, and it is
     * the one thing about a wheel event that is reliable -- so that zooms.
     * Sideways scroll only comes from a two-finger drag or a tilt wheel, and
     * both mean pan, so a wheel event carrying `deltaX` pans in both axes.
     * Everything else zooms toward the cursor, as it always has.
     *
     * The choice is latched for the length of a gesture: a two-finger drag
     * that runs momentarily straight up or down reports no `deltaX` for a few
     * events, and flipping to zoom in the middle of a pan feels like a fault.
     */
    bindWheel() {
      const canvas = this.canvas;
      const PINCH_GAIN = 3; // a pinch reports far less scroll than it feels like
      const GESTURE_IDLE_MS = 220; // quiet for this long and the next event is a new gesture
      const GESTURE_OPEN_MS = 120; // early enough in one to still change its mind
      let kind = null;
      let startedAt = 0;
      let lastAt = 0;

      canvas.addEventListener(
        "wheel",
        (event) => {
          if (!this.pose) return;
          event.preventDefault(); // never scroll the page, never zoom the browser
          const now = event.timeStamp || performance.now();
          if (now - lastAt > GESTURE_IDLE_MS) {
            kind = null;
            startedAt = now;
          }
          lastAt = now;

          const [dxPx, dyPx] = wheelPixels(event);
          if (event.ctrlKey) {
            kind = "zoom";
            const [ndcX, ndcY] = this.ndc(event);
            const factor = zoomFactorForPixels(dyPx * PINCH_GAIN);
            this.pose = zoomAt(this.pose, factor, ndcX, ndcY, this.aspect());
            return;
          }

          const sideways = dxPx !== 0 || event.shiftKey;
          if (kind === null) kind = sideways ? "pan" : "zoom";
          else if (kind === "zoom" && sideways && now - startedAt < GESTURE_OPEN_MS) kind = "pan";

          if (kind === "pan") {
            // Scrolling down moves the scene up, which is the same as dragging
            // it up: a wheel delta is the negative of the equivalent drag.
            this.pose = pan(this.pose, -dxPx, -dyPx, canvas.clientHeight);
          } else {
            const [ndcX, ndcY] = this.ndc(event);
            this.pose = zoomAt(this.pose, wheelZoomFactor(event), ndcX, ndcY, this.aspect());
          }
        },
        { passive: false }
      );
    }

    ndc(event) {
      return this.ndcAt(event.clientX, event.clientY);
    }

    ndcAt(clientX, clientY) {
      const rect = this.canvas.getBoundingClientRect();
      return [
        ((clientX - rect.left) / Math.max(rect.width, 1)) * 2 - 1,
        1 - ((clientY - rect.top) / Math.max(rect.height, 1)) * 2,
      ];
    }

    aspect() {
      // Falls back to the drawing buffer for the same reason render() keeps the
      // last size: a hidden screen measures zero, and an export in progress
      // must not have the picture squashed underneath it.
      const width = this.canvas.clientWidth || this.canvas.width;
      const height = this.canvas.clientHeight || this.canvas.height;
      return Math.max(width, 1) / Math.max(height, 1);
    }

    // -- drawing ------------------------------------------------------------

    segment(a, b, rgb, radius) {
      const s = this.segments;
      const i = s.slot();
      const d = s.scratch;
      d[i] = a[0]; d[i + 1] = a[1]; d[i + 2] = a[2];
      d[i + 3] = b[0]; d[i + 4] = b[1]; d[i + 5] = b[2];
      d[i + 6] = rgb[0]; d[i + 7] = rgb[1]; d[i + 8] = rgb[2];
      d[i + 9] = radius;
    }

    disc(center, axisX, axisY, rgb, alpha) {
      const s = this.discs;
      const i = s.slot();
      const d = s.scratch;
      d[i] = center[0]; d[i + 1] = center[1]; d[i + 2] = center[2];
      d[i + 3] = axisX[0]; d[i + 4] = axisX[1]; d[i + 5] = axisX[2];
      d[i + 6] = axisY[0]; d[i + 7] = axisY[1]; d[i + 8] = axisY[2];
      d[i + 9] = rgb[0]; d[i + 10] = rgb[1]; d[i + 11] = rgb[2]; d[i + 12] = alpha;
    }

    /**
     * Ground lines around `center`, snapped to whole metres.
     *
     * The patch travels with the car rather than sitting at the world origin,
     * which a following camera drives straight off. Snapping keeps each line
     * on its own world coordinate, so the ground reads as fixed and the car
     * as moving over it -- the opposite of what a patch pinned to the car
     * would look like.
     */
    buildGrid(extent, center) {
      const [rgb, strong] = this.gridInk();
      const reach = Math.ceil(extent * 2.5) + 6;
      const cx = Math.round(center[0]);
      const cy = Math.round(center[1]);
      for (let i = -reach; i <= reach; i++) {
        const x = cx + i;
        const y = cy + i;
        const majorX = x % 5 === 0;
        const majorY = y % 5 === 0;
        this.segment([x, cy - reach, 0], [x, cy + reach, 0], majorX ? strong : rgb, majorX ? 0.012 : 0.006);
        this.segment([cx - reach, y, 0], [cx + reach, y, 0], majorY ? strong : rgb, majorY ? 0.012 : 0.006);
      }
    }

    render() {
      const gl = this.gl;
      const canvas = this.canvas;
      const dpr = Math.min(window.devicePixelRatio || 1, 2);
      const width = Math.round(canvas.clientWidth * dpr);
      const height = Math.round(canvas.clientHeight * dpr);
      // A hidden screen measures zero. Keeping the last real size means a
      // video export survives someone switching to another screen mid-record:
      // the drawing buffer stays the size the recording started at.
      if (width > 0 && height > 0 && (canvas.width !== width || canvas.height !== height)) {
        canvas.width = width;
        canvas.height = height;
      }
      gl.viewport(0, 0, canvas.width, canvas.height);
      const [br, bg2, bb] = this.backdrop();
      gl.clearColor(br, bg2, bb, 1);
      gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

      const scene = this.scene;
      if (!scene || !this.pose) return;

      const f = scene.frameAt(this.simTime);
      const [pa, pb, va, vb] = this._scratch;
      const header = scene.header;

      const anchor = this.anchorAt(f);
      if (this.follow && this._anchor) {
        const drift = sub(anchor, this._anchor);
        this.pose = {
          ...this.pose,
          position: add(this.pose.position, drift),
          focal: add(this.pose.focal, drift),
        };
      }
      this._anchor = anchor;

      this.segments.begin();
      this.discs.begin();

      if (this.layers.grid) this.buildGrid(scene.extent(0), anchor);

      if (this.layers.links) {
        for (const group of header.links) {
          for (const [a, b] of group.segments) {
            scene.point(a, f, pa);
            scene.point(b, f, pb);
            this.segment(pa, pb, group.rgb, group.radius);
          }
        }
      }

      const { right, up } = cameraBasis(this.pose);
      if (this.layers.joints) {
        const r = header.joints.radius;
        const ax = scale(right, r);
        const ay = scale(up, r);
        for (let i = 0; i < scene.pointCount; i++) {
          scene.point(i, f, pa);
          this.disc(pa, ax, ay, scene.jointRgb, 1);
        }
      }

      if (this.layers.tires) {
        for (const tire of header.tires) {
          scene.point(tire.center, f, pa);
          scene.vector(tire.axis_x, f, va);
          scene.vector(tire.axis_y, f, vb);
          // The wheel disc lies in the plane normal to the spin axis (y).
          const ex = unit(va, [1, 0, 0]);
          const ez = unit(cross(vb, va), [0, 0, 1]);
          this.disc(pa, scale(ex, tire.radius), scale(ez, tire.radius), [0.16, 0.17, 0.19], 0.55);
        }
      }

      if (this.layers.loads) {
        const reference = header.loads.radius;
        for (const corner of header.loads.corners) {
          scene.point(corner.point, f, pa);
          const ratio = corner.reference > 0 ? scene.scalar(corner.slot, f) / corner.reference : 0;
          // Area scales with load, which the eye reads linearly.
          const r = reference * Math.sqrt(Math.max(ratio, 0));
          const ground = [pa[0], pa[1], 0.002];
          this.disc(ground, [r, 0, 0], [0, r, 0], loadColor(ratio), 0.8);
        }
      }

      if (this.layers.tracks && header.tracks.corners.length) {
        const history = header.tracks.history;
        const start = scene.frameAt(this.simTime - history);
        const step = Math.max(1, Math.floor((f - start) / 120));
        for (const corner of header.tracks.corners) {
          for (let k = Math.floor(start); k + step <= f; k += step) {
            scene.point(corner.point, k, pa);
            scene.point(corner.point, Math.min(k + step, f), pb);
            this.segment([pa[0], pa[1], 0.001], [pb[0], pb[1], 0.001], corner.rgb, 0.01);
          }
        }
      }

      if (this.layers.arrows) {
        for (const arrow of header.arrows) {
          scene.point(arrow.origin, f, pa);
          scene.vector(arrow.slot, f, va);
          const tip = add(pa, scale(va, arrow.scale));
          this.segment(pa, tip, arrow.rgb, arrow.shaft_radius);
        }
      }

      const view = lookAt(this.pose.position, this.pose.focal, this.pose.up);
      const proj = perspective(this.pose.viewAngle, this.aspect(), 0.02, 5000);
      const viewProj = multiply(proj, view);
      const uniforms = { uViewProj: viewProj, uEye: this.pose.position };
      this.segments.draw(uniforms);
      this.discs.draw(uniforms);
    }

    /** The app's own surface colour, re-read only when the theme changes. */
    backdrop() {
      const theme = document.body.className;
      if (this._theme !== theme) {
        const raw = getComputedStyle(document.body).getPropertyValue("--surface-2").trim();
        this._backdrop = raw ? hexToRgb(raw) : [0.94, 0.96, 0.97];
        this._theme = theme;
      }
      return this._backdrop;
    }

    /** Grid ink that stays legible on either theme. */
    gridInk() {
      const [r, g, b] = this.backdrop();
      const dark = r + g + b < 1.2;
      return dark ? [[0.29, 0.34, 0.39], [0.36, 0.42, 0.48]] : [[0.82, 0.84, 0.87], [0.72, 0.75, 0.79]];
    }

    tick(wallMs) {
      const scene = this.scene;
      if (scene && this.playing && this._lastWall) {
        const dt = Math.min((wallMs - this._lastWall) / 1000, 0.25);
        this.simTime += dt * (scene.header.speed || 1);
        const end = scene.time[scene.time.length - 1];
        if (this.simTime > end) this.simTime = scene.time[0];
      }
      this._lastWall = wallMs;
      this.render();
      if (this.onTick) this.onTick(this.simTime);
    }
  }

  window.BobVis = { Viewer, Scene, camera: { orbit, pan, zoomAt, recenter, groundPlanePoint, focalPlanePoint, cameraBasis, wheelZoomFactor } };
})();
