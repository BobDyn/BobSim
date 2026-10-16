"""Track import and geometry previews."""
from pathlib import Path
import hashlib
import tempfile
from typing import Any

from common.vehicle_io import load_yaml
from simulations.lap.core.track import TrackCorridor
from simulations.lap.racing_line_sim import vehicle_width_m


def track_payload(root: Path, path: str) -> dict[str, Any]:
    """## Track Preview

    Parameters
    ----------
    root : Path
        Vehicle workspace root.
    path : str
        Workspace-relative CSV path.

    Returns
    -------
    dict
        Track boundaries and derived nominal vehicle width.
    """
    source = (root / path).resolve()
    if not source.is_relative_to(root.resolve()) or source.suffix.lower() != ".csv":
        raise ValueError("Choose a track CSV in this workspace.")
    track = TrackCorridor.from_csv(source)
    left, right = track.interpolated_boundaries()
    return {"path": source.relative_to(root.resolve()).as_posix(), "left": left.tolist(),
            "right": right.tolist(),
            "vehicle_width_m": vehicle_width_m(load_yaml(root / "vehicle.yml"), root)}


def import_track(root: Path, name: str, text: str) -> dict[str, Any]:
    """## Track Import

    Parameters
    ----------
    root : Path
        Vehicle workspace root.
    name : str
        Original CSV filename.
    text : str
        Paired boundary coordinates in metres.

    Returns
    -------
    dict
        Saved CSV path and preview geometry.
    """
    if Path(name).suffix.lower() != ".csv" or len(text.encode()) > 2_000_000:
        raise ValueError("Choose a track CSV smaller than 2 MB.")
    directory = root / "app/user_data/config/tracks"
    directory.mkdir(parents=True, exist_ok=True)
    with tempfile.NamedTemporaryFile(mode="w", suffix=".csv", dir=directory, encoding="utf-8", delete=False) as handle:
        temporary = Path(handle.name)
        handle.write(text)
    try:
        payload = track_payload(root, temporary.relative_to(root).as_posix())
        digest = hashlib.sha256(text.encode()).hexdigest()[:16]
        destination = directory / f"track-{digest}.csv"
        temporary.replace(destination)
        payload["path"] = destination.relative_to(root).as_posix()
        return payload
    finally:
        temporary.unlink(missing_ok=True)
