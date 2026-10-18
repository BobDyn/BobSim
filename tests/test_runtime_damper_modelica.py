"""Opt-in compiled regression: change YAML settings without rebuilding the damper."""

from copy import deepcopy
import hashlib
import os
from pathlib import Path
import shutil
import subprocess

import numpy as np
import pytest
import yaml

from _0_Utils.damper_curves import resolve_damper_curve
from _0_Utils.vehicle_io import load_yaml, repo_root
from _3_StandardSim import _modelica_runner as runner_module


@pytest.mark.skipif(
    os.environ.get("BOBSIM_RUNTIME_DAMPER_INTEGRATION") != "1",
    reason="Set BOBSIM_RUNTIME_DAMPER_INTEGRATION=1 to compile and run the Modelica regression",
)
def test_changed_yaml_changes_runtime_forces_without_recompiling(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch,
) -> None:
    omc = shutil.which("omc")
    if omc is None:
        pytest.skip("OpenModelica is unavailable")
    boblib = repo_root() / "_0_Utils/external/BobLib"
    model = "RuntimeTabularDamper"
    script = tmp_path / "build.mos"
    script.write_text(
        'loadModel(Modelica, {"4.1.0"});\n'
        'loadModel(VehicleInterfaces, {"2.0.2"});\n'
        f'loadFile("{(boblib / "BobLib/package.mo").as_posix()}");\n'
        f'loadFile("{(boblib / "Tests/RuntimeTabularDamper.mo").as_posix()}");\n'
        f'buildModel({model}, stopTime=1, numberOfIntervals=1000, outputFormat="csv");\n'
        'getErrorString();\n',
        encoding="utf-8",
    )
    compiled = subprocess.run([omc, str(script)], cwd=tmp_path, capture_output=True, text=True, timeout=180)
    exe = tmp_path / (model + (".exe" if os.name == "nt" else ""))
    assert exe.is_file(), compiled.stdout + compiled.stderr
    digest = hashlib.sha256(exe.read_bytes()).hexdigest()
    original = load_yaml(repo_root() / "vehicle.yml")
    force_traces = []
    vehicle = tmp_path / "vehicle.yml"
    monkeypatch.setattr(runner_module, "vehicle_yaml_path", lambda: vehicle)
    runner = runner_module.ModelicaRunner(tmp_path, model, {"runtime_damper_tables": True})
    run_dirs = []
    for clicks in (6, 10):
        data = deepcopy(original)
        compression = data["front"]["actuation"]["shock"]["damper"]["compression"]
        compression["low_speed_clicks_from_closed"] = clicks
        vehicle.write_text(yaml.safe_dump(data), encoding="utf-8")
        data = load_yaml(vehicle)
        results = runner.run(
            ["compressionVelocity", "damperForce", "damper.extrapolating"], "raw",
            [{"_mode": "first"}, {"_mode": "second"}] if clicks == 10 else [{}],
            execution={"parallel": clicks == 10, "max_workers": 2, "fail_fast": True},
        )
        signals = results[0]
        if clicks == 10:
            assert results[0]["_run_dir"] != results[1]["_run_dir"]
            np.testing.assert_allclose(results[0]["damperForce"], results[1]["damperForce"])
        run_dirs.append(Path(signals["_run_dir"]))
        assert (run_dirs[-1] / "damper_tables.txt").is_file()
        assert (run_dirs[-1] / "damper_curves.json").is_file()
        speed = signals["compressionVelocity"]
        force = signals["damperForce"]
        curve = resolve_damper_curve(data["front"]["actuation"]["shock"])
        np.testing.assert_allclose(force, [curve.force(v) for v in speed], atol=1e-6)
        assert (force * speed >= -1e-7).all()
        assert (np.abs(speed) > 0.25).any()
        np.testing.assert_array_equal(signals["damper.extrapolating"], np.abs(speed) > 0.25)
        force_traces.append(force)
        assert hashlib.sha256(exe.read_bytes()).hexdigest() == digest
    assert not np.allclose(force_traces[0], force_traces[1])
    assert run_dirs[0] != run_dirs[1]
    compression = data["front"]["actuation"]["shock"]["damper"]["compression"]
    compression["high_speed_turns_from_open"] = 2
    vehicle.write_text(yaml.safe_dump(data), encoding="utf-8")
    with pytest.raises(ValueError, match="unmeasured"):
        runner.run([], "raw", [{}], execution={"parallel": False})
