function simulationDiagramHtml(id) {
  const draw = {
    text: (x, y, label, options = '') => `<text x="${x}" y="${y}" ${options}>${escapeHtml(label)}</text>`,
    path: (d, kind = 'structure') => `<path d="${d}" class="${kind}"/>`,
    rect: (x, y, width, height, kind = 'body') => `<rect x="${x}" y="${y}" width="${width}" height="${height}" rx="3" class="${kind}"/>`,
    circle: (cx, cy, r, kind = 'structure') => `<circle cx="${cx}" cy="${cy}" r="${r}" class="${kind}"/>`,
    arrow: (x1, y1, x2, y2, kind = 'force') => {
      const angle = Math.atan2(y2 - y1, x2 - x1);
      const backX = x2 - 8 * Math.cos(angle), backY = y2 - 8 * Math.sin(angle);
      const sideX = 4 * Math.sin(angle), sideY = 4 * Math.cos(angle);
      return `<path d="M ${x1} ${y1} L ${x2} ${y2} M ${backX + sideX} ${backY - sideY} L ${x2} ${y2} L ${backX - sideX} ${backY + sideY}" class="${kind}"/>`;
    },
  };
  const drawing = simulationBalanceDrawing(id, draw) || simulationResponseDrawing(id, draw) || simulationLapDrawing(id, draw);
  if (!drawing) return '';
  return `<figure class="simulation-diagram"><svg viewBox="0 0 760 300" role="img" aria-labelledby="simulation-diagram-${id}"><title id="simulation-diagram-${id}">${escapeHtml(drawing.caption)}</title>${drawing.body}</svg><figcaption>${escapeHtml(drawing.caption)}</figcaption></figure>`;
}

function simulationBalanceDrawing(id, draw) {
  const {text, arrow, path, rect, circle} = draw;
  if (id === 'four-post') {
    const body = [
      text(32, 29, 'Chassis motion'),
      path('M 70 235 H 394', 'muted'),
      path('M 87 244 l 9 -9 M 117 244 l 9 -9 M 337 244 l 9 -9 M 367 244 l 9 -9', 'muted'),
      rect(106, 187, 28, 48), rect(326, 187, 28, 48),
      circle(120, 235, 5, 'accent'), circle(340, 235, 5, 'accent'),
      path('M 120 208 L 146 158 M 340 208 L 272 126'),
      `<g transform="translate(232 235) rotate(-14)">${rect(-80, -110, 160, 28)}${path('M 0 0 V -96')}${circle(0, -96, 4, 'accent')}${arrow(0, -96, 0, -174, 'motion')}</g>`,
      text(243, 79, 'Local z: heave'),
      path('M 219 56 Q 183 58 163 98', 'motion'),
      arrow(170, 85, 163, 98, 'motion'),
      text(80, 67, 'Roll'),
      circle(232, 235, 9), circle(232, 235, 2, 'accent'),
      text(207, 273, 'Global x'),
      text(433, 56, 'Prescribed'),
      text(433, 84, 'Roll, then local heave'),
      path('M 433 105 H 718', 'muted'),
      text(433, 140, 'At each contact patch'),
      text(433, 170, 'z fixed'),
      text(433, 198, 'x, y and rotations free'),
      path('M 433 218 H 718', 'muted'),
      text(433, 250, 'Wheel travel is a result'),
    ].join('');
    return {
      body,
      caption: 'Front-view schematic of one axle. Both axles use chassis actuation: rotation about global x, followed by translation along the rotated local z axis. Contact height is fixed. Suspension motion determines wheel travel.',
    };
  }
  if (id !== 'ggv' && id !== 'ymd') return null;
  const vehicle = [
    rect(147, 87, 130, 135),
    path('M 157 102 H 267 M 157 208 H 267'),
    path('M 212 87 V 222', 'muted'),
    `<g transform="rotate(-12 123 103)">${rect(114, 84, 18, 38)}</g>`,
    `<g transform="rotate(-12 301 103)">${rect(292, 84, 18, 38)}</g>`,
    rect(114, 188, 18, 38), rect(292, 188, 18, 38),
    path('M 132 103 H 147 M 277 103 H 292 M 132 207 H 147 M 277 207 H 292'),
    circle(212, 155, 5, 'accent'),
  ];
  if (id === 'ggv') {
    const body = [
      text(32, 29, 'Plan-view force balance'),
      ...vehicle,
      ...[[123, 103], [301, 103], [123, 207], [301, 207]].flatMap(([x, y]) => [
        arrow(x, y, x - 42, y, 'force'),
        arrow(x, y, x, y - 34, 'force'),
      ]),
      text(63, 264, 'Four tire force vectors'),
      path('M 323 181 Q 354 157 318 133', 'motion'),
      arrow(329, 141, 318, 133, 'motion'),
      text(353, 160, 'ψ̇'),
      text(438, 42, 'Path frame'),
      arrow(557, 151, 622, 86, 'motion'),
      arrow(557, 151, 492, 86, 'motion'),
      text(632, 88, 't'), text(472, 88, 'n'),
      circle(557, 151, 4, 'accent'),
      text(468, 184, 'Heading rate = aₙ / V'),
      path('M 438 205 H 720', 'muted'),
      text(438, 234, 'ΣF = m a'),
      text(438, 261, 'Angular acceleration = 0'),
      text(438, 284, 'on retained axes'),
    ].join('');
    return {
      body,
      caption: 'Plan-view schematic of a frozen cornering condition. Tire arrows show force components. The full model supplies aero, vertical balance and moments.',
    };
  }
  const body = [
    text(32, 29, 'Imposed steering and sideslip'),
    ...vehicle,
    path('M 123 75 V 49', 'muted'),
    arrow(123, 75, 109, 41, 'motion'),
    text(89, 56, 'δ'),
    arrow(212, 155, 212, 43, 'muted'),
    arrow(212, 155, 167, 46, 'motion'),
    path('M 212 111 Q 203 111 195 115', 'motion'),
    text(184, 102, 'β'), text(147, 49, 'V'),
    arrow(123, 103, 76, 103, 'force'),
    arrow(301, 103, 255, 103, 'force'),
    arrow(123, 207, 83, 207, 'force'),
    arrow(301, 207, 262, 207, 'force'),
    path('M 283 247 Q 375 205 320 140', 'force'),
    arrow(328, 152, 320, 140, 'force'),
    '<text x="350" y="204">M<tspan baseline-shift="sub" style="font-size:11px">z</tspan></text>',
    text(116, 272, 'Net yaw moment'),
    text(461, 61, 'Steering + sideslip'),
    arrow(568, 80, 568, 111, 'muted'),
    text(440, 143, 'Tire forces and moments'),
    arrow(568, 161, 568, 192, 'muted'),
    '<text x="482" y="224">aᵧ and M<tspan baseline-shift="sub" style="font-size:11px">z</tspan></text>',
    text(440, 269, 'Yaw moment is not fixed to zero'),
  ].join('');
  return {
    body,
    caption: 'Each point imposes steering and sideslip at the configured speed and yaw rate. The remaining trim equations are solved, then lateral acceleration and net body yaw moment are reported. Arrows are schematic, not calculated forces.',
  };
}
function simulationResponseDrawing(id, draw) {
  const {text, arrow, path, rect} = draw;
  const label = (x, y, value, anchor = "middle") => text(x, y, value, `text-anchor="${anchor}" font-size="16"`);
  const axis = (left, right, bottom) => `${arrow(left, bottom, right, bottom, "muted")}${arrow(left, bottom, left, 62, "muted")}`;
  const timeLabel = (right, bottom) => label(right, bottom + 24, "Time", "end");

  if (id === "steady-state") {
    const body = [
      rect(24, 40, 164, 62), rect(278, 40, 160, 62), rect(544, 40, 192, 62),
      label(106, 65, "Speed and lateral"), label(106, 88, "acceleration targets"),
      label(358, 76, "Controller"), label(640, 76, "BobLib vehicle"),
      arrow(194, 71, 268, 71, "motion"), arrow(446, 71, 534, 71, "force"),
      label(490, 30, "Steering + torque"),
      path("M640 103 V140 H358", "muted"), arrow(358, 140, 358, 108, "muted"),
      label(537, 162, "Measured speed and lateral acceleration"),
      label(38, 198, "Handling signals settle", "start"),
      arrow(54, 263, 722, 263, "muted"), arrow(54, 263, 54, 209, "muted"),
      path("M60 224 H706", "muted"),
      path("M60 256 C118 256 120 209 158 214 S204 240 240 230 S295 218 330 223 S406 224 452 224 H706", "motion"),
      label(720, 286, "Time", "end"),
      label(348, 292, "Position and heading keep changing"),
    ].join("");
    return {body, caption: "Schematic response. Feedback settles the monitored handling signals. The vehicle continues around the corner."};
  }

  if (id === "transient") {
    const body = [
      label(124, 30, "Steering cases"), label(374, 30, "Integrate the vehicle"), label(630, 30, "Time response"),
      label(42, 69, "Finite-rise step", "start"),
      path("M42 119 H96 L110 83 H220", "accent"),
      arrow(42, 129, 230, 129, "muted"),
      label(42, 168, "Sustained sine", "start"),
      path("M42 211 C57 211 57 185 72 185 S87 237 102 237 S117 185 132 185 S147 237 162 237 S177 185 192 185 S207 211 222 211", "accent"),
      arrow(42, 246, 230, 246, "muted"),
      path("M235 107 H254 V207 H235", "muted"), arrow(254, 154, 282, 154, "force"),
      rect(292, 117, 164, 74), label(374, 149, "BobLib vehicle"), label(374, 174, "Speed controlled"),
      arrow(464, 154, 506, 154, "motion"),
      arrow(518, 234, 734, 234, "muted"), arrow(518, 234, 518, 80, "muted"),
      path("M526 156 C548 156 548 120 568 120 S590 192 610 192 S632 120 652 120 S674 192 694 192 S716 156 724 156", "motion"),
      label(628, 267, "Gain and phase"),
    ].join("");
    return {body, caption: "Schematic response. Step cases measure timing and overshoot. Sine cases measure response gain and phase."};
  }

  const reduced = id === "reduced-ramp-steer" || id === "reduced-step-steer";
  const ramp = id === "reduced-ramp-steer" || id === "ramp-steer";
  const step = id === "reduced-step-steer" || id === "mbd-step-steer";
  if (!ramp && !step) return null;
  const inputTitle = reduced ? "Roadwheel steering" : "Handwheel steering";
  let input, response, caption;
  if (ramp && reduced) {
    input = [
      path("M48 192 H100 L222 88 H330", "accent"),
      path("M222 88 V203 M330 67 V203", "muted"),
      label(100, 227, "Start"), label(222, 227, "Ramp end"), label(330, 251, "Simulation end", "end"),
      label(276, 73, "Hold"),
    ].join("");
    response = path("M436 192 H488 C514 192 560 129 610 107 S681 87 720 88", "motion");
    caption = "Steering ramps, then holds. The vehicle response continues until simulation end.";
  } else if (ramp) {
    input = [
      path("M48 192 H100 L330 76", "accent"),
      path("M330 62 V203", "muted"), label(100, 227, "Start"), label(330, 251, "Run stops", "end"),
    ].join("");
    response = path("M436 192 H486 C516 192 543 170 578 140 S656 89 720 73", "motion");
    caption = "The handwheel ramp continues until the run ends or a termination condition is reached.";
  } else {
    input = [
      path("M48 192 H104 L136 88 H330", "accent"),
      path("M104 194 V216 M136 91 V216", "muted"),
      label(120, 244, "Rise time"), label(250, 73, "Hold"),
    ].join("");
    response = path("M436 192 H483 C507 192 519 69 561 72 S598 113 628 100 S670 88 696 92 H720", "motion");
    caption = "A finite-rise steering step is held while the vehicle response develops. Speed is controlled.";
  }
  const body = [
    label(190, 30, inputTitle), label(582, 30, "Vehicle response"),
    axis(42, 346, 204), axis(430, 736, 204), input, response,
    arrow(364, 139, 407, 139, "force"), timeLabel(736, 204),
    label(582, 265, "Yaw rate and lateral acceleration"),
  ].join("");
  return {body, caption: `Schematic response. ${caption}`};
}
function simulationLapDrawing(id, draw) {
  const {text, arrow, path, rect, circle} = draw;
  const centered = 'text-anchor="middle"';
  if (id === 'lap-qss') {
    const track = 'M54 30C84 2 131 12 153 32C169 47 199 28 216 48C244 83 200 112 173 91C151 74 125 80 97 97C58 120 17 90 30 62Z';
    const reference = 'M51.5 27.8L55.4 25.5L59.4 23.5L63.5 21.8L67.8 20.5L72.2 19.4L76.6 18.6L81.0 18.0L85.5 17.7L90.0 17.7L94.5 17.8L99.0 18.1L103.4 18.6L107.9 19.2L112.3 19.9L116.7 20.8L121.1 21.7L125.5 22.7L129.8 23.8L134.2 24.8L138.5 25.9L142.9 26.9L147.3 27.9L151.7 28.9L156.1 29.8L160.5 30.5L164.9 31.2L169.4 31.7L173.8 32.0L178.3 32.4L182.8 32.7L187.3 33.1L191.7 33.5L196.2 34.2L200.5 35.1L204.9 36.3L209.1 37.9L213.1 39.8L216.9 42.2L220.4 45.0L223.6 48.2L226.2 51.8L228.3 55.8L229.8 60.0L230.6 64.4L230.7 68.9L230.1 73.3L228.7 77.6L226.6 81.5L224.0 85.1L220.8 88.3L217.2 90.9L213.2 93.0L209.0 94.6L204.6 95.7L200.2 96.3L195.7 96.4L191.2 96.3L186.8 95.8L182.4 95.0L178.0 94.1L173.6 93.0L169.3 91.9L164.9 90.8L160.6 89.7L156.2 88.8L151.8 88.0L147.3 87.5L142.8 87.3L138.3 87.4L133.9 87.8L129.4 88.5L125.0 89.3L120.7 90.3L116.3 91.5L112.0 92.7L107.7 94.0L103.4 95.3L99.1 96.5L94.8 97.7L90.4 98.8L86.0 99.8L81.6 100.5L77.2 101.0L72.7 101.2L68.2 101.2L63.7 100.7L59.3 99.9L55.0 98.6L50.9 96.9L46.9 94.8L43.3 92.2L39.9 89.2L37.0 85.8L34.5 82.0L32.6 78.0L31.1 73.8L30.2 69.4L29.9 64.9L30.1 60.4L30.8 56.0L32.1 51.7L33.8 47.6L35.9 43.6L38.4 39.9L41.3 36.4L44.4 33.2L47.8 30.3Z';
    const body = [
      text(125, 29, 'Racing line', centered),
      `<g transform="translate(0 55) scale(.95)"><path d="${track}" fill="none" style="stroke:var(--ink);stroke-width:20" opacity=".12"/>${path(reference, 'accent')}</g>`,
      text(125, 200, 'Curvature κ(s)', centered),
      arrow(220, 172, 262, 172, 'motion'),
      text(339, 29, 'GGV limits', centered),
      arrow(339, 159, 339, 50, 'muted'),
      text(352, 57, 'V'),
      ...[[83, 50, 15], [112, 39, 12], [139, 28, 9]].map(([y, rx, ry]) =>
        path(`M ${339-rx} ${y} a ${rx} ${ry} 0 1 0 ${2*rx} 0 a ${rx} ${ry} 0 1 0 ${-2*rx} 0`, 'force')),
      text(339, 200, 'Acceleration bounds', centered),
      arrow(414, 172, 459, 172, 'motion'),
      text(598, 29, 'Speed profile', centered),
      path('M480 61V190H733', 'structure'),
      text(463, 71, 'v'),
      path('M487 109C514 66 537 70 551 145S585 175 596 134S631 63 652 99S696 179 724 115', 'accent'),
      text(606, 210, 'Distance along line', centered),
      text(602, 240, 'Forward acceleration', centered),
      arrow(493, 251, 716, 251, 'force'),
      arrow(716, 270, 493, 270, 'motion'),
      text(602, 293, 'Backward braking', centered),
      text(31, 256, 'Static speed calculation'),
      text(31, 281, 'No integrated vehicle trajectory'),
    ].join('');
    return {body, caption: 'Curvature sets lateral demand. GGV limits constrain forward acceleration and backward braking to produce the lap speed profile. The illustrated line reuses the solved minimum-curvature example. The speed profile is schematic.'};
  }
  if (id !== 'lap-transient') return null;
  const body = [
    text(34, 29, 'Follow the reference'),
    `<g stroke-dasharray="6 5">${path('M35 201C108 207 135 185 165 140S231 74 320 80', 'muted')}</g>`,
    path('M35 222C108 220 137 180 179 157S244 111 320 115', 'accent'),
    text(35, 265, 'Reference line'),
    `<g stroke-dasharray="6 5">${path('M157 260H194', 'muted')}</g>`,
    text(215, 265, 'Driven path'),
    path('M314 260H350', 'accent'),
    `<g transform="translate(179 157) rotate(-29)">${rect(-21, -11, 42, 22)}${rect(-13, -7, 18, 14, 'muted')}${path('M-13-15H-5M10-15H18M-13 15H-5M10 15H18', 'structure')}</g>`,
    arrow(198, 147, 253, 117, 'motion'),
    `<g stroke-dasharray="5 4">${path('M179 157L216 102', 'muted')}</g>`,
    path('M207 141A32 32 0 0 0 197 131', 'motion'),
    text(227, 98, 'Heading error'),
    arrow(158, 155, 146, 143, 'force'),
    text(35, 113, 'Cross-track error'),
    path('M112 119L147 142', 'muted'),
    text(584, 29, 'Feedback driver', centered),
    rect(444, 52, 280, 50),
    text(584, 83, 'Reference line + speed', centered),
    arrow(584, 104, 584, 134, 'motion'),
    text(598, 124, 'Targets'),
    rect(444, 139, 280, 51),
    text(584, 171, 'Driver', centered),
    arrow(584, 192, 584, 222, 'force'),
    text(597, 213, 'Steering + torque'),
    rect(444, 227, 280, 50),
    text(584, 259, 'Vehicle dynamics', centered),
    path('M444 251H393V165', 'motion'),
    arrow(393, 165, 440, 165, 'motion'),
    text(372, 149, 'Errors'),
    text(385, 294, 'Position, heading and speed'),
  ].join('');
  return {body, caption: 'Schematic of a driven corner. The reference line and speed are targets. Steering and wheel torque respond to tracking errors as the vehicle states evolve through time.'};
}
