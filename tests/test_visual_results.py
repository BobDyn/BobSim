"""Checks for the result-CSV to BobVis-scene converter.

No PyVista and no OpenModelica: the converter is plain numpy and PyYAML, and
the parts worth protecting are the frame-name map (a BobLib rename silently
empties the scene) and the upright refit that stands in for the wheel-centre
frames OpenModelica's alias elimination removes.
"""

from __future__ import annotations

import csv
import re
from pathlib import Path

import numpy as np
import pytest
import yaml

from _1_VisualSim import capture, from_results
from _1_VisualSim.from_results import (
    ANCHOR_FRAME,
    CORNERS,
    FRAME_MAP,
    LOAD_SIGNALS,
    UPRIGHT_TRIAD,
    ResultMappingError,
    _kabsch,
    convert,
    frame_paths,
    tire_state_paths,
    variable_filter,
)
from tests.test_visual_templates import _referenced_signals


# ---------------------------------------------------------------------------
# Frame map
# ---------------------------------------------------------------------------

def test_frame_map_covers_every_corner_uniquely() -> None:
    paths = frame_paths()
    assert len(paths) == len(CORNERS) * len(FRAME_MAP)
    # A copy-paste slip in the templates would alias two hardpoints onto one
    # frame and silently collapse part of the linkage.
    assert len(set(paths.values())) == len(paths)


def test_frame_map_placeholders_all_resolve() -> None:
    for path in frame_paths().values():
        assert "{" not in path and "}" not in path


def test_upright_triad_is_part_of_the_frame_map() -> None:
    for point in UPRIGHT_TRIAD:
        assert point in FRAME_MAP


def test_variable_filter_is_a_valid_regex_naming_time_and_geometry() -> None:
    pattern = variable_filter()
    re.compile(pattern)
    assert pattern.startswith("time|")
    assert "r_0" in pattern
    # Escaped so a dot cannot match an arbitrary character and over-select.
    assert r"\." in pattern


def test_variable_filter_includes_extras() -> None:
    assert "frKnC.fx" in variable_filter(extra=["frKnC.fx"]).replace("\\", "")


def test_variable_filter_asks_for_every_tire_force_under_the_prefix() -> None:
    prefix = "chassis.detailedChassis."
    pattern = variable_filter(prefix=prefix)
    for column in tire_state_paths(prefix).values():
        assert re.escape(column) in pattern
    assert re.escape(prefix + "frAxleDW.leftTire.Fy") in pattern


# ---------------------------------------------------------------------------
# Rigid refit
# ---------------------------------------------------------------------------

def test_kabsch_recovers_a_known_rigid_transform() -> None:
    reference = np.array([[0.0, 0.5, 0.1], [0.0, 0.5, 0.3], [0.1, 0.5, 0.2]])
    angle = 0.2
    R_true = np.array([
        [np.cos(angle), -np.sin(angle), 0.0],
        [np.sin(angle), np.cos(angle), 0.0],
        [0.0, 0.0, 1.0],
    ])
    t_true = np.array([1.0, -2.0, 0.3])
    current = (reference @ R_true.T + t_true)[None, :, :]

    R, t = _kabsch(reference, current)

    assert np.allclose(R[0], R_true, atol=1e-9)
    assert np.allclose(t[0], t_true, atol=1e-9)
    assert np.isclose(np.linalg.det(R[0]), 1.0)  # a rotation, never a reflection


def test_kabsch_is_exact_for_a_point_off_the_fitted_triad() -> None:
    """The refit only helps if points not used in the fit land correctly."""
    reference = np.array([[0.0, 0.56, 0.11], [-0.01, 0.54, 0.27], [0.06, 0.55, 0.15]])
    other = np.array([0.0, 0.61, 0.20])

    angle = -0.13
    R_true = np.array([
        [1.0, 0.0, 0.0],
        [0.0, np.cos(angle), -np.sin(angle)],
        [0.0, np.sin(angle), np.cos(angle)],
    ])
    t_true = np.array([0.02, 0.0, -0.05])
    current = (reference @ R_true.T + t_true)[None, :, :]

    R, t = _kabsch(reference, current)
    assert np.allclose(R[0] @ other + t[0], other @ R_true.T + t_true, atol=1e-9)


# ---------------------------------------------------------------------------
# End-to-end conversion against a synthetic result CSV
# ---------------------------------------------------------------------------

def _write_result_csv(
    path: Path,
    samples: int = 12,
    prefix: str = "",
    speed: float = 0.0,
    loads: tuple[str, ...] = (),
    tire_forces: bool = False,
) -> None:
    """A CSV shaped like an OpenModelica result, carrying every mapped frame.

    Contact-patch Z and the wheel-centre frames are left out on purpose: that
    is exactly what alias elimination does to a real run, and the converter is
    expected to refit them. ``prefix`` nests the axles as VehicleSim does,
    ``speed`` drives the car forward, ``loads`` names per-tire Fz columns, and
    ``tire_forces`` adds each tire's own force state.
    """
    time = np.linspace(0.0, 1.0, samples)
    columns: dict[str, np.ndarray] = {"time": time}

    heave = 0.02 * np.sin(2 * np.pi * time)
    base = {
        "Lower_o": np.array([0.003, 0.563, 0.114]),
        "Upper_o": np.array([-0.009, 0.542, 0.268]),
        "Tie_o": np.array([0.057, 0.547, 0.152]),
    }

    for (corner, point), frame in frame_paths(prefix).items():
        if point in ("WheelCenter", "ContactPatch"):
            continue
        mirror = np.array([1.0, -1.0 if corner.endswith("r") else 1.0, 1.0])
        origin = base.get(point, np.array([0.05, 0.30, 0.20])) * mirror
        motion = {1: speed * time, 2: np.zeros(samples), 3: heave}
        for index in (1, 2, 3):
            columns[f"{frame}.r_0[{index}]"] = origin[index - 1] + motion[index]

    columns["frKnC.heave"] = heave
    for name in loads:
        columns[name] = 1000.0 + 200.0 * heave / 0.02
    if tire_forces:
        state = {"Fx": 300.0 * np.sin(2 * np.pi * time), "Fy": -900.0 * time,
                 "Fz": 700.0 + 100.0 * time, "gamma": np.full(samples, -0.01)}
        for (_, variable), column in tire_state_paths(prefix).items():
            columns[column] = state[variable]

    with open(path, "w", newline="", encoding="utf-8") as handle:
        writer = csv.writer(handle)
        writer.writerow(list(columns))
        for row in range(samples):
            writer.writerow([repr(float(columns[name][row])) for name in columns])


def test_convert_writes_a_scene_the_template_fully_describes(tmp_path: Path) -> None:
    result = tmp_path / "Model_res.csv"
    _write_result_csv(result)

    npz_path, template_path, summary = convert(
        result, tmp_path / "out_visual.npz", tmp_path / "out_visual.yml"
    )

    cfg = yaml.safe_load(template_path.read_text(encoding="utf-8"))
    with np.load(npz_path) as raw:
        stored = set(raw.files)

    # The generated pair must be self-consistent: this is the whole point of
    # emitting the template and the data together.
    assert not _referenced_signals(cfg) - stored
    assert not summary["missing"]
    assert summary["points"] == len(CORNERS) * len(FRAME_MAP)


def test_convert_refits_the_points_alias_elimination_removes(tmp_path: Path) -> None:
    result = tmp_path / "Model_res.csv"
    _write_result_csv(result)

    npz_path, template_path, summary = convert(
        result, tmp_path / "out_visual.npz", tmp_path / "out_visual.yml"
    )

    for corner in CORNERS:
        assert f"{corner}_WheelCenter" in summary["derived"]
        assert f"{corner}_ContactPatch" in summary["derived"]

    cfg = yaml.safe_load(template_path.read_text(encoding="utf-8"))
    assert len(cfg["geometry"]["tires"]) == len(CORNERS)

    with np.load(npz_path) as raw:
        # The rig's ground plane is z = 0, so every contact patch sits on it.
        patch_z = raw["pos/fl_ContactPatch_z"]
        assert np.allclose(patch_z, 0.0)
        # And the wheel centre must sit above it, near the tire radius.
        assert np.all(raw["pos/fl_WheelCenter_z"] > 0.1)


def test_detect_prefix_finds_the_axles_wherever_the_model_nests_them() -> None:
    assert from_results.detect_prefix(["time", ANCHOR_FRAME]) == ""
    assert from_results.detect_prefix(
        ["accY", "chassis.detailedChassis." + ANCHOR_FRAME]
    ) == "chassis.detailedChassis."
    assert from_results.detect_prefix(["time", "accY"]) == ""


def test_convert_reads_a_driving_vehicle_result(tmp_path: Path) -> None:
    """VehicleSim nests the axles and names loads Fz_*; the car moves, so tracks."""
    result = tmp_path / "VehicleSim_res.csv"
    vehicle_loads = tuple(names[1] for names in LOAD_SIGNALS.values())
    _write_result_csv(result, prefix="chassis.detailedChassis.", speed=20.0,
                      loads=vehicle_loads)

    npz_path, template_path, summary = convert(
        result, tmp_path / "v_visual.npz", tmp_path / "v_visual.yml"
    )
    cfg = yaml.safe_load(template_path.read_text(encoding="utf-8"))
    with np.load(npz_path) as raw:
        assert not _referenced_signals(cfg) - set(raw.files)

    assert summary["points"] == len(CORNERS) * len(FRAME_MAP)
    loads = cfg["ground"]["loads"]["corners"]
    assert {v["signal"] for v in loads.values()} == set(vehicle_loads)
    assert len(cfg["ground"]["tracks"]["points"]) == len(CORNERS)


def test_convert_gives_the_rig_loads_but_no_tracks(tmp_path: Path) -> None:
    """The rig holds the car in place; a trail there would only be a dot."""
    result = tmp_path / "FourPostSim_res.csv"
    _write_result_csv(result, loads=tuple(names[0] for names in LOAD_SIGNALS.values()))

    _, template_path, _ = convert(result, tmp_path / "r.npz", tmp_path / "r.yml")
    cfg = yaml.safe_load(template_path.read_text(encoding="utf-8"))

    assert len(cfg["ground"]["loads"]["corners"]) == len(CORNERS)
    assert "tracks" not in cfg["ground"]


def test_convert_adds_friction_circles_for_a_driving_result(tmp_path: Path) -> None:
    result = tmp_path / "VehicleSim_res.csv"
    _write_result_csv(result, prefix="chassis.detailedChassis.", speed=20.0, tire_forces=True)

    npz_path, template_path, summary = convert(result, tmp_path / "f.npz", tmp_path / "f.yml")
    cfg = yaml.safe_load(template_path.read_text(encoding="utf-8"))
    with np.load(npz_path) as raw:
        assert not _referenced_signals(cfg) - set(raw.files)

    forces = cfg["tire_forces"]
    assert set(forces["corners"]) == set(CORNERS)
    assert {c["axle"] for c in forces["corners"].values()} == {"front", "rear"}
    assert all("gamma" in c for c in forces["corners"].values())
    for axle in ("front", "rear"):
        assert forces["friction"][axle]["PDY1"] < 0.0  # read from the real .tir
        assert forces["friction"][axle]["tir"]
    assert summary["tire_forces"] == len(CORNERS)
    assert not summary["warnings"]


def test_convert_falls_back_to_the_load_channel_for_tire_fz(tmp_path: Path) -> None:
    result = tmp_path / "VehicleSim_res.csv"
    vehicle_loads = tuple(names[1] for names in LOAD_SIGNALS.values())
    _write_result_csv(result, prefix="chassis.detailedChassis.", loads=vehicle_loads, tire_forces=True)

    # Drop the tires' own Fz, as alias elimination might.
    with open(result, newline="", encoding="utf-8") as handle:
        rows = list(csv.reader(handle))
    keep = [i for i, name in enumerate(rows[0]) if not name.endswith("Tire.Fz")]
    with open(result, "w", newline="", encoding="utf-8") as handle:
        csv.writer(handle).writerows([[row[i] for i in keep] for row in rows])

    npz_path, template_path, _ = convert(result, tmp_path / "f.npz", tmp_path / "f.yml")
    cfg = yaml.safe_load(template_path.read_text(encoding="utf-8"))
    with np.load(npz_path) as raw:
        fl = cfg["tire_forces"]["corners"]["fl"]
        assert np.allclose(raw[fl["fz"]], raw["Fz_FL"])


def test_the_rig_gets_no_friction_circles(tmp_path: Path) -> None:
    result = tmp_path / "FourPostSim_res.csv"
    _write_result_csv(result, loads=tuple(names[0] for names in LOAD_SIGNALS.values()))

    _, template_path, summary = convert(result, tmp_path / "r.npz", tmp_path / "r.yml")
    assert "tire_forces" not in yaml.safe_load(template_path.read_text(encoding="utf-8"))
    assert summary["tire_forces"] == 0


def test_convert_records_the_metrics_csv_relative_to_the_template(tmp_path: Path) -> None:
    result = tmp_path / "Model_res.csv"
    _write_result_csv(result)
    metrics = tmp_path / "metrics" / "run_metrics.csv"
    metrics.parent.mkdir()
    metrics.write_text("standard,group,metric,value,units,description\n", encoding="utf-8")

    _, template_path, summary = convert(
        result, tmp_path / "scene" / "o.npz", tmp_path / "scene" / "o.yml", metrics_csv=metrics
    )
    cfg = yaml.safe_load(template_path.read_text(encoding="utf-8"))
    assert cfg["metrics"]["path"] == "../metrics/run_metrics.csv"
    assert summary["metrics"] == str(metrics)

    _, missing_template, _ = convert(
        result, tmp_path / "o2.npz", tmp_path / "o2.yml", metrics_csv=tmp_path / "absent.csv"
    )
    assert "metrics" not in yaml.safe_load(missing_template.read_text(encoding="utf-8"))


def test_capture_finds_the_metrics_csv_whichever_name_the_evaluation_used(tmp_path: Path) -> None:
    config = tmp_path / "capture.yml"
    report = tmp_path / "transient_capture_report.pdf"
    config.write_text(yaml.safe_dump({"report": {
        "output_path": report.as_posix(),
        "metrics_csv_path": (tmp_path / "transient_capture_metrics.csv").as_posix(),
    }}), encoding="utf-8")

    assert capture.metrics_csv(config) is None
    derived = tmp_path / "transient_capture_report_metrics.csv"
    derived.write_text("metric\n", encoding="utf-8")
    assert capture.metrics_csv(config) == derived


@pytest.mark.parametrize("evaluation", sorted(capture.EVALUATIONS))
def test_capture_config_keeps_the_evaluations_own_signals(
    tmp_path: Path, evaluation: str
) -> None:
    """The evaluation re-reads its signals from the capture CSV and fails without them."""
    path = capture.write_config(tmp_path / f"{evaluation}.yml", evaluation)
    cfg = yaml.safe_load(path.read_text(encoding="utf-8"))
    pattern = cfg["simulation"]["variable_filter"]

    re.compile(pattern)
    for signal in capture.eval_signals(evaluation):
        assert re.escape(signal) in pattern
    prefix = capture.EVALUATIONS[evaluation].prefix
    assert re.escape(prefix + "frAxleDW.leftWishboneUprightLoop.") in pattern

    # Regression: VehicleSim's axle frames are protected, so without this flag
    # the run silently wrote only the evaluation's own 17 columns.
    assert "-emit_protected" in cfg["simulation"]["extra_args"]
    # A capture must never overwrite the metrics the regression checks read.
    for key in ("output_path", "metrics_csv_path"):
        assert cfg["report"][key].startswith("_1_VisualSim/results/")


def test_convert_rejects_a_result_with_no_geometry(tmp_path: Path) -> None:
    result = tmp_path / "Model_res.csv"
    with open(result, "w", newline="", encoding="utf-8") as handle:
        writer = csv.writer(handle)
        writer.writerow(["time", "frKnC.heave"])
        for i in range(5):
            writer.writerow([i * 0.1, 0.0])

    with pytest.raises(ResultMappingError, match="visual-capture"):
        convert(result, tmp_path / "o.npz", tmp_path / "o.yml")


def test_convert_rejects_an_empty_result(tmp_path: Path) -> None:
    result = tmp_path / "Model_res.csv"
    result.write_text("time,frKnC.heave\n", encoding="utf-8")

    with pytest.raises(ResultMappingError):
        convert(result, tmp_path / "o.npz", tmp_path / "o.yml")


def test_vehicle_yaml_supplies_mirrored_reference_hardpoints() -> None:
    references = from_results._upright_hardpoints(from_results.default_vehicle_yaml())

    for corner in CORNERS:
        assert set(UPRIGHT_TRIAD) <= set(references[corner])
    # Right-hand corners are the left mirrored about the centreline.
    assert references["fl"]["Lower_o"][1] == pytest.approx(
        -references["fr"]["Lower_o"][1]
    )
    # Front and rear are different corners of the car.
    assert references["fl"]["Lower_o"][0] != references["rl"]["Lower_o"][0]
