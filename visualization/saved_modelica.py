"""Generate animation outputs from a saved Modelica simulation's own results."""
from __future__ import annotations

import json
from pathlib import Path
import tempfile
import zipfile

import yaml

from visualization import from_results


def capture_saved(run_directory: Path, *, root: Path) -> list[Path]:
    """Capture each archived Modelica case without using the active vehicle setup."""
    saved = json.loads((run_directory / "manifest.json").read_text())
    if (saved.get("model") or {}).get("engine") != "BobLib":
        raise ValueError("Animation requires a Modelica simulation")
    if saved["workflow"]["id"] == "four-post":
        from visualization.native_four_post import capture
        return [capture(run_directory, root=root)]
    archive_path = root / saved["analysis"]["archive_path"]
    vehicle_path = root / saved["vehicle_snapshot"]
    output = root / "visualization/results"
    output.mkdir(parents=True, exist_ok=True)
    scenes = []
    with zipfile.ZipFile(archive_path) as archive, tempfile.TemporaryDirectory() as temporary:
        for index, case in enumerate(saved["analysis"]["runs"]):
            if not case.get("signals_file"):
                continue
            csv_path = Path(temporary) / "signals.csv"
            csv_path.write_bytes(archive.read(case["signals_file"]))
            template = output / f"modelica_{saved['id']}_{index}.yml"
            from_results.convert(csv_path, template.with_suffix(".npz"), template, vehicle_yaml=vehicle_path)
            config = yaml.safe_load(template.read_text())
            config["source"] = {"label": f"{saved['label']} · {case['label']}",
                                "simulation_id": (saved.get("simulation") or {}).get("id", ""),
                                "vehicle_key": saved["vehicle_key"], "result_id": saved["id"]}
            template.write_text(yaml.safe_dump(config, sort_keys=False))
            scenes.append(template)
    if not scenes:
        raise ValueError("No archived Modelica geometry is available. Rerun the simulation to capture animation.")
    return scenes
