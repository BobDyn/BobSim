"""App jobs for locally compiled architecture artifacts."""
from __future__ import annotations

import json

from app import actions
from app.contracts import ActionSpec
from common import native_artifacts


def start_build(vehicle: dict, kind: str) -> dict:
    """Reserve the app workspace and build using its configured toolchain."""
    selection = native_artifacts.architecture(vehicle)
    if kind not in native_artifacts.KINDS:
        raise ValueError("Unknown native experiment")
    label = "Build " + native_artifacts.KINDS[kind]
    action = ActionSpec(
        id="native-build-" + kind, label=label,
        argv=(actions.PYTHON, "-m", "common.native_artifacts", "--selection",
              json.dumps(selection), "--kind", kind), requires_external_toolchain=True,
    )
    return actions._launch_job((action,), action.id, label, list(action.argv))


def start_run(vehicle: dict, kind: str, settings: dict) -> dict:
    """Snapshot input data before launching an isolated native run."""
    import uuid
    from app.native_calibration import vehicle_overrides
    selection = native_artifacts.architecture(vehicle)
    if kind not in native_artifacts.KINDS:
        raise ValueError("Unknown native experiment")
    directory = native_artifacts.artifact_dir(selection, kind)
    try:
        manifest = native_artifacts.checked_manifest(directory)
    except FileNotFoundError as exc:
        raise ValueError("Build this experiment in Architecture first") from exc
    vehicle_overrides(vehicle, manifest, native_artifacts.ROOT)
    requests = native_artifacts.ROOT / "app/user_data/results/native/requests"
    requests.mkdir(parents=True, exist_ok=True)
    path = requests / (uuid.uuid4().hex + ".json")
    path.write_text(json.dumps({"vehicle": vehicle, "kind": kind, "settings": settings}))
    action = ActionSpec(id="native-run-" + kind, label="Run " + native_artifacts.KINDS[kind],
                        argv=(actions.PYTHON, "-m", "app.native_runs", str(path)))
    return actions._launch_job((action,), action.id, action.label, list(action.argv))
