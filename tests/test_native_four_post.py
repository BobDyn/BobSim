"""Cached Four Post routing, calibration and force-response contracts."""
import csv
import copy
import os

import numpy as np
import pytest

from app import app, native_four_post


def test_four_post_uses_cached_binary_without_compiler_or_generated_record(monkeypatch):
    monkeypatch.setattr(app, "external_toolchain_available", lambda: False)
    monkeypatch.setattr(native_four_post, "unavailable_reason", lambda vehicle: "")
    workflow = next(w for w in app.WORKFLOWS if w.id == "four-post")
    payload = app.workflow_payload(workflow)
    assert payload["available"]
    assert not payload["requires_mbd"]
    assert workflow.actions == ("run-four-post",)
    assert "run-four-post" not in app.MODELICA_RUN_TARGETS_BY_ACTION
    assert app.ACTION_SPECS["run-four-post"].argv[-1] == "app.native_four_post"
    monkeypatch.setattr(native_four_post, "unavailable_reason", lambda vehicle: "Build in Architecture")
    assert not app.workflow_payload(workflow)["available"]
    with pytest.raises(RuntimeError, match="Architecture"):
        app.start_workflow("four-post")


def test_axle_adapter_preserves_four_corners_and_uses_rear_drive_torque(tmp_path, monkeypatch):
    from common.vehicle_io import load_yaml, repo_root
    vehicle = load_yaml(repo_root() / "vehicle.yml")
    original = copy.deepcopy(vehicle)
    calls = []
    def simulate(calibration, kind, settings):
        calls.append((calibration, kind, settings))
        path = tmp_path / (kind + ".csv")
        value = {"knc-front": 10, "knc-rear": 20, "knc-rear-traction": 30}[kind]
        path.write_text(f"time,knc.leftToe,knc.rightToe\n0,{value},{value+1}\n118,{value},{value+1}\n")
        return {"csv": path.name}
    monkeypatch.setattr(native_four_post.native_runs, "run", simulate)
    case = dict(heaveMagnitude=.02, rollMagnitude=.01, forceMagnitude=500, steerMagnitude=.1)
    for side, prefix, bar in (("front", "pVehicle.pFrAxleDW", "pFrStabar"),
                              ("rear", "pVehicle.pRrAxleDW", "pRrStabar")):
        case[prefix + ".springFreeLength"] = .21
        case[bar + ".barRate"] = 123
        for i, row in enumerate(vehicle[side]["actuation"]["shock"]["spring_table"]["table"], 1):
            for j, value in enumerate(row, 1):
                case[f"{prefix}.springTable[{i},{j}]"] = value
    signals = [prefix + "." + side + "Toe" for prefix in ("frKnC", "rrKnC") for side in ("left", "right")]
    result = native_four_post.AxleRunner(vehicle, tmp_path, {
        "front_left_lateral_share": .8, "rear_left_lateral_share": .2}).run(
        signals=signals, cases=[case], mode="raw", execution={})[0]
    assert vehicle == original
    assert result["frKnC.leftToe"].tolist() == [10, 10]
    assert result["frKnC.rightToe"].tolist() == [11, 11]
    assert result["rrKnC.leftToe"].tolist() == [30, 20]
    assert result["rrKnC.rightToe"].tolist() == [31, 21]
    assert [s["steerMagnitude"] for _, _, s in calls] == [.1, 0, 0]
    assert [s["lateralLeftShare"] for _, _, s in calls] == [.8, .2, .2]
    assert calls[0][0]["front"]["actuation"]["shock"]["free_length_m"] == .21


def test_force_shares_weight_braking_but_not_rear_drive_or_geometric_curves():
    import numpy as np
    shares = native_four_post.force_settings({}, {"force_based": {
        "front_brake_share": .6, "front_left_lateral_share": .8, "rear_left_lateral_share": .7}})
    runs = {kind: {"curves": {"x_axes": {"roll_deg": [-1, 1], "heave_mm": [-10, 10]},
        "curves": {"roll_force_rc_height_mm": [20, 30], "roll_force_anti_roll_pct": [8, 12],
                   "bump_anti_dive_pct": [50, 60], "bump_anti_squat_pct": [70, 80]}}}
        for kind in native_four_post.KINDS}
    result = {"series": {"fr_l_camber_vs_heave": [1, 2]}, "summary": {}}
    native_four_post.apply_force_results(result, runs, shares)
    assert result["series"]["fr_l_camber_vs_heave"] == [1, 2]
    np.testing.assert_allclose(result["series"]["fr_anti_vs_heave"], [36, 30])
    np.testing.assert_allclose(result["series"]["rr_anti_vs_heave"], [80, 70])
    np.testing.assert_allclose(result["series"]["fr_fbrc_height_vs_roll"], [.02, .03])
    assert result["summary"]["avg_anti_dive_pct"] == 33
    assert result["summary"]["avg_anti_squat_pct"] == 75
    for invalid in (-.1, 1.1, float("nan")):
        with pytest.raises(ValueError, match="0% and 100%"):
            native_four_post.force_settings({}, {"force_based": {"front_brake_share": invalid}})


def test_report_plot_selection_preserves_quad_layouts_and_normalized_choices():
    from common.vehicle_io import load_yaml, repo_root
    from common.plotting.plot_engine import PlotEngine
    from simulations.response.mbd.four_post.four_post_eval_sim import _normalize_four_post_report_config
    config = load_yaml(repo_root() / app.BASE_CONFIG_SPECS["four-post"].path)
    original = copy.deepcopy(config)
    fields = app._config_fields(app.BASE_CONFIG_SPECS["four-post"], config)
    choices = [field for field in fields if field["path"][0] == "plots"]
    assert len(choices) == len(config["plots"]) + len(native_four_post.GEOMETRY_REPORT_METRICS)
    assert all(field["kind"] == "boolean" and field["group"] == "Report" for field in choices)
    assert all(field["value"] == (field["path"][1] not in native_four_post.GEOMETRY_REPORT_METRICS)
               for field in choices)
    assert config == original
    for name, plot in config["plots"].items():
        plot["enabled"] = name == "camber_heave"
    _normalize_four_post_report_config(config)
    assert not config["plots"]["fbrc_roll"]["enabled"]
    assert not config["plots"]["jacking_roll"]["enabled"]
    assert config["plots"]["camber_heave"]["layout"] == "quad"
    series = {}
    for subplot in config["plots"]["camber_heave"]["subplots"]:
        for axis in ("x", "y"):
            series[subplot[axis]["key"]] = [0, 1, 2]
    pages = list(PlotEngine(config).render({"series": series}))
    assert [name for name, _ in pages] == ["camber_heave"]
    assert len(pages[0][1].axes) == 4
    from matplotlib import pyplot as plt
    plt.close(pages[0][1])


@pytest.mark.skipif(os.environ.get("BOBSIM_NATIVE_INTEGRATION") != "1", reason="Requires cached native binaries")
def test_four_post_changes_pose_inputs_without_rebuilding():
    from common.vehicle_io import load_yaml, repo_root
    root = repo_root()
    vehicle = load_yaml(root / "vehicle.yml")
    runs = [native_four_post.native_runs.run(vehicle, "knc-front", settings) for settings in (
        {"heaveMagnitude": .02, "rollMagnitude": .01, "steerMagnitude": .1},
        {"heaveMagnitude": .025, "rollMagnitude": .012, "steerMagnitude": -.1},
    )]
    assert runs[0]["identity"] == runs[1]["identity"]
    assert runs[0]["csv"] != runs[1]["csv"]
    for result, heave, roll, steer in zip(runs, [.02, .025], [.01, .012], [.1, -.1]):
        with (root / result["csv"]).open() as stream:
            rows = list(csv.DictReader(stream))
        assert max(float(row["knc.heave"]) for row in rows) == pytest.approx(heave)
        assert max(float(row["knc.roll"]) for row in rows) == pytest.approx(roll)
        assert float(rows[-1]["inputs.steer"]) == pytest.approx(steer)
        assert result["final_time"] == pytest.approx(118)


@pytest.mark.skipif(os.environ.get("BOBSIM_NATIVE_INTEGRATION") != "1", reason="Requires cached native binaries")
def test_lateral_share_is_applied_to_the_native_forces():
    from common.vehicle_io import load_yaml, repo_root
    root = repo_root()
    vehicle = load_yaml(root / "vehicle.yml")
    for share in (0.0, 1.0):
        result = native_four_post.native_runs.run(vehicle, "knc-front", {
            "steerMagnitude": 0, "rollMagnitude": .01, "heaveMagnitude": .02, "lateralLeftShare": share})
        with (root / result["csv"]).open() as stream:
            rows = list(csv.DictReader(stream))
        pulse = min(rows, key=lambda row: abs(float(row["time"]) - 64))
        assert float(pulse["leftLoad.worldForce.force[2]"]) == pytest.approx(1000 * share)
        assert float(pulse["rightLoad.worldForce.force[2]"]) == pytest.approx(1000 * (1 - share))


def test_optional_geometry_report_uses_native_values_and_preserves_missing_data():
    from common.plotting.plot_engine import PlotEngine
    from matplotlib import pyplot as plt
    curves = {"roll_force_rc_height_mm": [100, 200], "roll_force_anti_roll_pct": [10, 20],
              "bump_anti_dive_pct": [30, 40], "bump_anti_squat_pct": [50, 60]}
    for _, metric, _ in native_four_post.GEOMETRY_REPORT_METRICS.values():
        curves[metric] = [None, 2.5]
    runs = {kind: {"curves": {"x_axes": {"roll_deg": [-1, 1], "heave_mm": [-10, 10]},
                             "curves": curves}} for kind in native_four_post.KINDS}
    result = {"series": {}, "summary": {}}
    native_four_post.apply_force_results(result, runs, native_four_post.force_settings({}, {}))
    config = {"plots": {name: {"enabled": True} for name in native_four_post.GEOMETRY_REPORT_METRICS}}
    plots = native_four_post.report_plots(config)
    for _, metric, _ in native_four_post.GEOMETRY_REPORT_METRICS.values():
        assert np.isnan(result["series"]["fr_" + metric][0])
        assert result["series"]["fr_" + metric][1] == 2.5
    assert config["plots"]["moment_ratio_roll"] == {"enabled": True}
    pages = list(PlotEngine({"plots": plots}).render(result))
    assert len(pages) == 5
    for _, figure in pages:
        assert len(figure.axes) == 2
        plt.close(figure)
