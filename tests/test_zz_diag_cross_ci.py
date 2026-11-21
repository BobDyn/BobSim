"""TEMPORARY CI diagnostic for PR #164. Reverted in the next commit."""

import numpy as np

import engines.dynpy.aero as A
import engines.dynpy.models as M
import engines.dynpy.qss as Q
import engines.dynpy.vector as V
import simulations.envelope.ggv.ggv_generation as G
from engines.dynpy import Vehicle
from engines.dynpy.qss import _generalized_acceleration_target
from simulations.envelope.ggv.ggv_generation import _solve_envelope_limit
from simulations.envelope.vehicle_yaml import load_vehicle_yaml, project_vehicle_yaml

MODULES = (M, Q, A, G)


def _case():
    model = Vehicle.from_yaml().model(10)
    projection = project_vehicle_yaml(load_vehicle_yaml()).ggv
    r = _solve_envelope_limit(projection, model, speed=10., ay=30., ax_bounds=(-31.4, 27.5), mode="lateral",
                              max_abs_beta_rad=.25, max_abs_steering_rad=.5, enforce_tire_load_range=True)
    t = _generalized_acceleration_target(model, r.state, r.output, longitudinal_mps2=r.path_longitudinal_acceleration_mps2,
                                         lateral_mps2=r.path_lateral_acceleration_mps2, acceleration_frame="path")
    return float(np.abs(r.output.generalized_acceleration - t).max()), r.output.generalized_acceleration.tobytes().hex()[:32]


def _numpy_cross(a, b):
    shape = np.broadcast_shapes(np.shape(a), np.shape(b))
    return np.cross(np.broadcast_to(np.asarray(a), shape), np.broadcast_to(np.asarray(b), shape))


def test_diag():
    cpu = [line for line in open("/proc/cpuinfo") if line.startswith(("model name", "flags"))][:2]
    simd = np.lib.introspect.opt_func_info(func_name="multiply|subtract", signature="float64.*")
    lines = [f"CPU {cpu}", f"SIMD {simd}", f"numpy {np.__version__}"]
    calls, bad = [0], []

    def checked(a, b):
        mine, ref = V.cross(a, b), _numpy_cross(a, b)
        calls[0] += 1
        if not np.array_equal(mine.view(np.int64), ref.view(np.int64)) and len(bad) < 5:
            bad.append((np.asarray(a).tolist(), np.asarray(b).tolist(), mine.tolist(), ref.tolist()))
        return mine

    for name, fn in (("vector.cross", V.cross), ("np.cross", _numpy_cross), ("checked", checked)):
        saved = [m.cross for m in MODULES]
        for m in MODULES:
            m.cross = fn
        try:
            lines.append(f"{name}: {_case()}")
        finally:
            for m, s in zip(MODULES, saved):
                m.cross = s
    lines.append(f"calls {calls[0]} mismatches {len(bad)} first {bad[:2]}")
    raise AssertionError("DIAG\n" + "\n".join(lines))
