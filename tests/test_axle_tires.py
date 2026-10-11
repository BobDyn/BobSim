from __future__ import annotations

from types import SimpleNamespace

import numpy as np
import pytest
import yaml

from app.tire_eval import _tire_template_for_side
from common.vehicle_io import load_yaml, repo_root, tire_template_name, vehicle_yaml_path
from engines.dynpy import ModelInputs, Vehicle
from simulations.envelope.ggv.ggv_generation import _trim_outside_tire_domain


@pytest.fixture(scope="module")
def mixed_vehicle(tmp_path_factory):
    root = tmp_path_factory.mktemp("axle-tires")
    data = load_yaml(vehicle_yaml_path())
    source = (repo_root() / "common/tire_templates/16x7p5_10_12psi.tir").read_text()
    (root / "front.tir").write_text(source)
    (root / "rear.tir").write_text(source + "\nLMUY = 0.25\nLMUX = 0.25\nFZMIN = 200\nFZMAX = 800\n")
    data["paths"]["tire_templates"] = root.as_posix()
    data["front"]["tire"]["template"] = "front"
    data["rear"]["tire"]["template"] = "rear"
    # An old global value must not silently override either explicit axle fit.
    data["aero"]["tire_template"] = "missing-global"
    path = root / "vehicle.yml"
    path.write_text(yaml.safe_dump(data))
    return Vehicle.from_yaml(path)


def test_explicit_axle_selection_and_legacy_fallback():
    data = {
        "aero": {"tire_template": "legacy"},
        "front": {"tire": {"template": "front"}},
        "rear": {"tire": {"template": "rear"}},
    }
    for axle in ["front", "rear"]:
        assert tire_template_name(data, data[axle]) == axle
        assert _tire_template_for_side(data, axle) == axle
    data["rear"]["tire"].clear()
    assert tire_template_name(data, data["rear"]) == "legacy"
    assert _tire_template_for_side(data, "rear") == "legacy"
    data["aero"].clear()
    with pytest.raises(KeyError, match="Missing tire.template"):
        tire_template_name(data, data["rear"])


@pytest.mark.parametrize("dof", [3, 6, 10, 14])
def test_each_axle_uses_its_own_force_fit(mixed_vehicle, dof):
    model = mixed_vehicle.model(dof)
    loads = np.full(4, 650.0)
    alpha = np.full(4, 0.1)
    gamma = np.zeros(4)
    controls = ModelInputs(wheel_torques_nm=(5.0, 5.0, 5.0, 5.0))
    fx, fy, slips = model._tire_forces(loads, alpha, np.full(4, 0.02), gamma, controls)
    for corner, tire in enumerate(mixed_vehicle.parameters.tires):
        expected = tire.forces(loads[corner], alpha[corner], slips[corner], gamma[corner])
        np.testing.assert_allclose([fx[corner], fy[corner]], expected, rtol=1e-12)
    assert max(abs(fy[2:])) < min(abs(fy[:2])) * 0.4
    if dof < 10:
        np.testing.assert_allclose(
            fx, np.asarray(controls.wheel_torques_nm) / model.parameters.wheel_radius_m, atol=1e-7
        )
    else:
        assert max(abs(fx[2:])) < min(abs(fx[:2]))


def test_tire_load_validity_uses_each_corners_fit(mixed_vehicle):
    model = mixed_vehicle.model(14)

    def outside(loads):
        trim = SimpleNamespace(output=SimpleNamespace(normal_loads_n=np.asarray(loads)))
        return _trim_outside_tire_domain(trim, model)

    assert not outside([150, 1200, 300, 700])
    assert outside([150, 1200, 300, 900])
    assert outside([150, 1200, 150, 700])
