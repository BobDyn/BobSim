"""The scene payload the Replay tab draws.

Numpy and YAML only, so this runs everywhere -- which is the point of having
moved the viewer into the browser: the whole server-side pipeline is now
testable in CI, where the old Qt and VTK stack never was.

What is worth protecting here is the contract between the two halves. The
browser trusts the header's indices and byte offsets absolutely: it looks up no
names and makes no decisions per frame. If an offset is wrong the scene does
not fail, it silently draws the wrong numbers.
"""

from __future__ import annotations

from pathlib import Path

import numpy as np
import pytest
import yaml

from _1_VisualSim import demo
from _5_App import visual


@pytest.fixture(scope="module")
def run(tmp_path_factory: pytest.TempPathFactory) -> tuple[Path, Path]:
    return demo.write(tmp_path_factory.mktemp("scene"), duration=1.0)


@pytest.fixture(scope="module")
def payload(run: tuple[Path, Path]) -> visual.ScenePayload:
    return visual.scene_payload(*run)


def test_buffer_is_exactly_what_the_header_describes(payload: visual.ScenePayload) -> None:
    """Every float is accounted for, and the blocks tile the buffer without gaps."""
    layout = payload.header["layout"]
    floats = np.frombuffer(payload.buffer, dtype="<f4")

    assert len(floats) == sum(block["count"] for block in layout.values())

    ordered = sorted(layout.values(), key=lambda block: block["offset"])
    cursor = 0
    for block in ordered:
        assert block["offset"] == cursor, "blocks must tile the buffer with no gap"
        cursor += block["count"]
    assert cursor == len(floats)


def test_positions_round_trip_from_the_source_signals(
    run: tuple[Path, Path], payload: visual.ScenePayload
) -> None:
    """A point read back through the header's indices is the signal it came from.

    Walks the same arithmetic the browser does -- frame-major, three floats per
    point -- rather than trusting the writer's own view of the layout.
    """
    config_path, data_path = run
    config = yaml.safe_load(config_path.read_text(encoding="utf-8"))
    raw = np.load(data_path)

    header = payload.header
    floats = np.frombuffer(payload.buffer, dtype="<f4")
    block = header["layout"]["positions"]
    count = len(header["points"])
    stride = int(config.get("render", {}).get("input_stride", 1))

    for name in (header["points"][0], header["points"][len(header["points"]) // 2], header["points"][-1]):
        index = header["points"].index(name)
        columns = config["geometry"]["points"][name]
        for frame in (0, 7, header["frames"] - 1):
            start = block["offset"] + (frame * count + index) * 3
            got = floats[start : start + 3]
            want = [float(raw[column][frame * stride]) for column in columns]
            assert np.allclose(got, want, atol=1e-5), f"{name} at frame {frame}"


def test_links_reference_points_that_exist(payload: visual.ScenePayload) -> None:
    """A segment index the browser cannot resolve would read another point's memory."""
    header = payload.header
    count = len(header["points"])
    assert header["links"], "the demo scene has links"
    for group in header["links"]:
        for a, b in group["segments"]:
            assert 0 <= a < count and 0 <= b < count, f"{group['group']} points outside the table"


def test_scalar_and_vector_slots_stay_inside_their_blocks(payload: visual.ScenePayload) -> None:
    """Every slot the header hands out must be addressable on the last frame."""
    header = payload.header
    frames = header["frames"]
    scalar_stride = header["layout"]["scalars"]["count"] // frames
    vector_stride = header["layout"]["vectors"]["count"] // frames // 3

    scalar_slots = [corner["slot"] for corner in header["loads"]["corners"]]
    scalar_slots += [plot["slot"] for plot in header["plots"]]
    for slot in scalar_slots:
        assert 0 <= slot < scalar_stride

    vector_slots = [arrow["slot"] for arrow in header["arrows"]]
    for tire in header["tires"]:
        vector_slots += [tire["axis_x"], tire["axis_y"]]
    for slot in vector_slots:
        assert 0 <= slot < vector_stride


def test_load_reference_is_the_load_the_corner_normally_carries(
    run: tuple[Path, Path], payload: visual.ScenePayload
) -> None:
    """The footprint ring is sized against the median, not a cold first sample."""
    config_path, data_path = run
    config = yaml.safe_load(config_path.read_text(encoding="utf-8"))
    raw = np.load(data_path)

    for corner in payload.header["loads"]["corners"]:
        signal = config["ground"]["loads"]["corners"][corner["corner"]]["signal"]
        assert corner["reference"] == pytest.approx(float(np.nanmedian(raw[signal])))
        assert corner["reference"] > 0, "a ratio is divided by this"


def test_a_run_without_tire_forces_simply_has_no_grip_block(payload: visual.ScenePayload) -> None:
    """The rig has no tire forces, and must still produce a drawable scene."""
    assert payload.header["grip"] == {}
    assert payload.header["frames"] > 0
    assert payload.header["points"], "geometry is still there"


def test_available_runs_pairs_a_config_with_its_signals(tmp_path: Path) -> None:
    """A config whose data file was cleaned away is not offered."""
    results = tmp_path / visual.VISUAL_RESULTS_ROOT
    results.mkdir(parents=True)
    demo.write(results, duration=0.2)

    runs = visual.available_runs(tmp_path)
    assert [run["id"] for run in runs] == ["demo_step_steer"]
    assert runs[0]["config"].endswith("demo_step_steer.yml")
    assert runs[0]["data"].endswith("demo_step_steer.npz")

    (results / "demo_step_steer.npz").unlink()
    assert visual.available_runs(tmp_path) == []


def test_missing_results_directory_is_not_an_error(tmp_path: Path) -> None:
    """A fresh clone has never captured anything; the tab says so rather than failing."""
    assert visual.available_runs(tmp_path) == []
