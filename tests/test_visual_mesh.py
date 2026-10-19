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
