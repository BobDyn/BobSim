"""The closed wheel mesh must face outward for transparent back-face culling."""

from pathlib import Path
import shutil
import subprocess

import pytest


@pytest.mark.skipif(shutil.which("node") is None, reason="Mesh check requires Node.js")
def test_cylinder_faces_point_outward():
    source = Path(__file__).resolve().parents[1] / "app/static/visual.js"
    subprocess.run(
        ["node", "-e", r"""
const fs = require('node:fs'), vm = require('node:vm'), assert = require('node:assert/strict');
const source = fs.readFileSync(process.argv[1], 'utf8').replace(
  'window.BobVis = { Viewer,', 'window.BobVis = { cylinderGeometry, Viewer,');
const ctx = vm.createContext({window:{}});
vm.runInContext(source, ctx);
const vertices = ctx.window.BobVis.cylinderGeometry();
assert(vertices.every(Number.isFinite));
const counts = [0, 0, 0];
for (let i = 0; i < vertices.length; i += 12) {
  const a = vertices.slice(i, i+4), b = vertices.slice(i+4, i+8), c = vertices.slice(i+8, i+12);
  const u = b.map((v,k)=>v-a[k]), v = c.map((v,k)=>v-a[k]);
  const n = [u[1]*v[2]-u[2]*v[1], u[2]*v[0]-u[0]*v[2], u[0]*v[1]-u[1]*v[0]];
  const cap = a[3];
  const outward = cap ? [cap,0,0] : [0,(a[1]+b[1]+c[1])/3,(a[2]+b[2]+c[2])/3];
  assert(n.reduce((sum,x,k)=>sum+x*outward[k],0)>0, 'Degenerate or inward-facing triangle');
  counts[cap+1]++;
}
assert(counts[0]>0 && counts[0]===counts[2] && counts[1]===2*counts[0]);
""", str(source)],
        check=True,
    )


@pytest.mark.skipif(shutil.which("node") is None, reason="Axis check requires Node.js")
def test_world_axes_follow_camera_orientation_only():
    source = Path(__file__).resolve().parents[1] / "app/static/visual.js"
    subprocess.run(
        ["node", "-e", r"""
const fs = require('node:fs'), vm = require('node:vm'), assert = require('node:assert/strict');
const source = fs.readFileSync(process.argv[1], 'utf8').replace(
  'window.BobVis = { Viewer,', 'window.BobVis = { worldAxes, Viewer,');
const ctx = vm.createContext({window:{}});
vm.runInContext(source, ctx);
const axes = (position, focal=[0,0,0]) => JSON.parse(JSON.stringify(
  ctx.window.BobVis.worldAxes({position,focal,up:[0,0,1]})));
const front = axes([5,0,0]);
assert.deepEqual(front.map(a=>[a.x,a.y]), [[0,0],[1,0],[0,1]]);
assert.deepEqual(axes([15,20,30],[10,20,30]), front);
const side = axes([0,5,0]);
assert.deepEqual(side.map(a=>[a.x,a.y]), [[-1,0],[0,0],[0,1]]);
""", str(source)],
        check=True,
    )


@pytest.mark.skipif(shutil.which("node") is None, reason="Link check requires Node.js")
def test_link_filter_keeps_bars_and_3dof_axle_frame():
    source = Path(__file__).resolve().parents[1] / "app/static/visual.js"
    subprocess.run(
        ["node", "-e", r"""
const fs = require('node:fs'), vm = require('node:vm'), assert = require('node:assert/strict');
const source = fs.readFileSync(process.argv[1], 'utf8').replace(
  'window.BobVis = { Viewer,', 'window.BobVis = { linkStyle, Viewer,');
const ctx = vm.createContext({window:{}});
vm.runInContext(source, ctx);
const visible = (group, a, b) => ctx.window.BobVis.linkStyle({group, rgb:[0,0,0], radius:0.01}, a, b) !== null;
assert(visible("body", "fl", "front_axle"));
assert(visible("body", "front_axle", "rear_axle"));
assert(!visible("body", "fl_upper_fore_i", "fr_upper_fore_i"));
assert(visible("chassis", "frLeftBarEnd", "frRightBarEnd"));
assert(!visible("chassis", "frLeftBarEnd", "frLowerFore"));
assert(visible("upper", "fl_upper_fore_i", "fl_upper_o"));
""", str(source)],
        check=True,
    )
