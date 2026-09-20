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
from typing import Any

import numpy as np
import pytest
import yaml

from _1_VisualSim import demo
from _1_VisualSim.tire_state import MIN_LOAD_N, grip_usage
from _5_App import visual


@pytest.fixture(scope="module")
def run(tmp_path_factory: pytest.TempPathFactory) -> tuple[Path, Path]:
    return demo.write(tmp_path_factory.mktemp("scene"), duration=1.0)


@pytest.fixture(scope="module")
def payload(run: tuple[Path, Path]) -> visual.ScenePayload:
    return visual.scene_payload(*run)


@pytest.fixture(scope="module")
def cornering_run(tmp_path_factory: pytest.TempPathFactory) -> tuple[Path, Path]:
    """The whole demo, long enough to contain the step steer itself.

    The one-second ``run`` above stops before the driver has turned, which is
    the right fixture for geometry but says nothing about grip.
    """
    return demo.write(tmp_path_factory.mktemp("cornering"), duration=8.0)


@pytest.fixture(scope="module")
def cornering(cornering_run: tuple[Path, Path]) -> visual.ScenePayload:
    return visual.scene_payload(*cornering_run)


def scalar_column(payload: visual.ScenePayload, slot: int) -> np.ndarray:
    """One scalar slot read back the way the browser reads it: frame-major."""
    block = payload.header["layout"]["scalars"]
    frames = payload.header["frames"]
    stride = block["count"] // frames
    floats = np.frombuffer(payload.buffer, dtype="<f4")
    values = floats[block["offset"] : block["offset"] + block["count"]]
    return np.asarray(values.reshape(frames, stride)[:, slot], dtype=float)


def write_scene(
    path: Path, signals: dict[str, np.ndarray], config: dict[str, Any]
) -> tuple[Path, Path]:
    """A scene on disk from a doctored copy of the demo's own signals and config."""
    config_path, data_path = path / "scene.yml", path / "scene.npz"
    config_path.write_text(yaml.safe_dump(config, sort_keys=False), encoding="utf-8")
    # numpy's stub types the second positional as `allow_pickle`, as in demo.py.
    np.savez_compressed(data_path, **signals)  # type: ignore[arg-type]
    return config_path, data_path


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
    for corner in header["grip"]["corners"]:
        scalar_slots += [corner[k] for k in ("slot_x", "slot_y", "slot_usage", "slot_airborne")]
    scalar_slots += list(header["grip"]["transfer"].values())
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


def test_a_run_without_tire_forces_simply_has_no_grip_block(tmp_path: Path) -> None:
    """The four-post rig has no tire forces, and must still draw a scene."""
    signals, config = demo.build(duration=0.5)
    config.pop("tire_forces")
    payload = visual.scene_payload(*write_scene(tmp_path, signals, config))

    assert payload.header["grip"] == {}
    assert payload.header["frames"] > 0
    assert payload.header["points"], "geometry is still there"


# ---------------------------------------------------------------------------
# Friction circles and LLTD
# ---------------------------------------------------------------------------


def test_the_demo_ships_a_grip_block_for_all_four_corners(
    cornering: visual.ScenePayload,
) -> None:
    """The Tires tab has to work on a machine that has never run a simulation."""
    grip = cornering.header["grip"]
    assert [corner["corner"] for corner in grip["corners"]] == ["fl", "fr", "rl", "rr"]
    assert [corner["axle"] for corner in grip["corners"]] == ["front", "front", "rear", "rear"]
    assert all(corner["tir"] for corner in grip["corners"]), "each circle names its tire"
    assert grip["transfer"], "four corners of load is enough for LLTD"


def test_grip_usage_matches_recomputing_it_from_the_signals(
    cornering_run: tuple[Path, Path], cornering: visual.ScenePayload
) -> None:
    """The browser's numbers are the ones :mod:`tire_state` produces, not near them.

    A friction circle drawn from a slightly different peak would flatter or
    libel the setup, so this walks the header's indices back to the raw
    channels and re-derives every corner.
    """
    config_path, data_path = cornering_run
    config = yaml.safe_load(config_path.read_text(encoding="utf-8"))
    raw = np.load(data_path)
    forces = config["tire_forces"]

    for corner in cornering.header["grip"]["corners"]:
        entry = forces["corners"][corner["corner"]]
        coeffs = forces["friction"][entry["axle"]]
        longitudinal, lateral, usage = grip_usage(
            raw[entry["fx"]], raw[entry["fy"]], raw[entry["fz"]], raw[entry["gamma"]], coeffs
        )
        for want, slot in (
            (longitudinal, "slot_x"),
            (lateral, "slot_y"),
            (usage, "slot_usage"),
        ):
            got = scalar_column(cornering, corner[slot])
            assert got == pytest.approx(np.nan_to_num(want), abs=1e-5), f"{corner['corner']} {slot}"


def test_demo_tires_work_hard_without_exceeding_their_grip(
    cornering: visual.ScenePayload,
) -> None:
    """A mock-up, but one a reviewer can believe: near the limit, never past it."""
    peaks = []
    for corner in cornering.header["grip"]["corners"]:
        usage = scalar_column(cornering, corner["slot_usage"])
        assert np.all(np.isfinite(usage))
        assert np.all(usage >= 0.0), "the ellipse radius is a magnitude"
        assert usage.max() < 1.05, f"{corner['corner']} is asked for grip it has not got"
        peaks.append(usage.max())
        # Straight-line running before the steer is nearly free of grip use.
        assert usage.min() < 0.2

    assert min(peaks) > 0.6, "a corner nobody leans on tells the reviewer nothing"
    front, rear = max(peaks[:2]), max(peaks[2:])
    assert front > rear, "the demo is meant to be understeer-limited at the front"


def test_no_demo_corner_ever_leaves_the_ground(cornering: visual.ScenePayload) -> None:
    """The step steer is a 0.9 g corner, not a three-wheeler."""
    for corner in cornering.header["grip"]["corners"]:
        assert scalar_column(cornering, corner["slot_airborne"]).sum() == 0.0


def test_a_lifted_wheel_is_flagged_airborne_rather_than_reading_as_zero_grip(
    tmp_path: Path,
) -> None:
    """Zero usage and no grip at all are opposite readings; only the flag tells them apart."""
    signals, config = demo.build(duration=8.0)
    lifted = (signals["time"] > 3.0) & (signals["time"] < 4.0)
    loads = signals["force/fl_fz"].copy()
    loads[lifted] = MIN_LOAD_N / 2.0
    signals["force/fl_fz"] = loads
    payload = visual.scene_payload(*write_scene(tmp_path, signals, config))

    corner = next(c for c in payload.header["grip"]["corners"] if c["corner"] == "fl")
    airborne = scalar_column(payload, corner["slot_airborne"])
    usage = scalar_column(payload, corner["slot_usage"])

    assert np.array_equal(airborne > 0.5, lifted), "the flag marks exactly the lifted frames"
    assert np.all(usage[lifted] == 0.0), "no grip reading survives the lift"
    assert np.all(np.isfinite(usage))
    assert usage[~lifted].max() > 0.5, "the other frames still report real usage"


def test_lltd_is_undefined_before_the_steer_and_is_the_front_share_after(
    cornering: visual.ScenePayload,
) -> None:
    """Dividing by a load transfer of nothing would give the front axle a wild share."""
    transfer = cornering.header["grip"]["transfer"]
    undefined = scalar_column(cornering, transfer["slot_lltd_undefined"]) > 0.5
    share = scalar_column(cornering, transfer["slot_lltd"])
    front = scalar_column(cornering, transfer["slot_front"])
    rear = scalar_column(cornering, transfer["slot_rear"])

    assert undefined[0], "the car starts straight, with no transfer to divide"
    assert not undefined.all(), "and it does corner"
    assert np.all(np.isfinite(share))
    assert np.all(share[undefined] == 0.0), "an undefined share travels as the flag, not a number"
    # The demo puts 60% of its lateral load transfer on the front axle.
    assert share[~undefined] == pytest.approx(demo.FRONT_SHARE, abs=1e-3)
    assert np.abs(front[~undefined]).min() > 0.0
    assert front[~undefined] + rear[~undefined] == pytest.approx(
        front[~undefined] / share[~undefined], rel=1e-4
    )


def test_a_diverged_sample_cannot_put_an_infinity_in_the_buffer(tmp_path: Path) -> None:
    """Regression: the grip slots used to sanitise NaN in a way that let infinity through.

    ``nan_to_num`` maps an infinity to 1.8e308, which is finite, so the
    payload's own guard passed it along and the float32 cast turned it straight
    back into an infinity. One such sample scales a friction circle to nothing.
    """
    signals, config = demo.build(duration=1.0)
    forces = signals["force/fl_fx"].copy()
    forces[5] = np.inf
    signals["force/fl_fx"] = forces
    payload = visual.scene_payload(*write_scene(tmp_path, signals, config))

    block = payload.header["layout"]["scalars"]
    floats = np.frombuffer(payload.buffer, dtype="<f4")
    assert np.all(np.isfinite(floats[block["offset"] : block["offset"] + block["count"]]))


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
