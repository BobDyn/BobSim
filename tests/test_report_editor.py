from __future__ import annotations

import copy
import json
import shutil
import subprocess
from pathlib import Path

import matplotlib.pyplot as plt
import numpy as np
import pytest
import yaml

from app import app, data_services as ds
from app.report_editor import report_editor
from common.plotting.plot_engine import PlotEngine
from common.reporting.editable import save_report_data, validate_plots


def definition():
    return {"response": {"layout": "dual", "title": "Response", "subplots": [
        {"title": name, "x": {"key": "time", "label": "Time (s)"},
         "y": {"key": signal}, "xlim": [0, 2], "ylim": [-1, 5], "legend": False}
        for name, signal in (("Yaw", "yaw"), ("Acceleration", "ay"))]}}


@pytest.fixture
def report_workspace(tmp_path, monkeypatch):
    monkeypatch.setattr(app, "ROOT", tmp_path)
    (tmp_path / "vehicle.yml").write_text("vehicle:\n  name: Report test\n")
    app._sync_data_services_runtime()
    key = ds._active_vehicle_workspace_key()
    workspace = ds._vehicle_workspace_dir(key)
    run_dir = workspace / "results" / "recorded"
    files = run_dir / "files"
    files.mkdir(parents=True)
    cfg = {"standard": "TransientEval", "plots": definition(), "simulation": {"stop_time": 8}}
    (run_dir / "config.yml").write_text(yaml.safe_dump(cfg))
    result = {"series": {"time": [0, 1, 2], "yaw": [0, 1, 2], "ay": [0, 2, 4]}, "summary": {}}
    save_report_data(files / "original.pdf", cfg, result)
    (files / "original.pdf").write_bytes(b"original report")
    manifest = {"id": "recorded", "vehicle_key": key, "workflow": {"id": "transient"},
                "simulation": {"id": "sim"}, "workspace_result_path": run_dir.relative_to(tmp_path).as_posix(),
                "config_snapshot": (run_dir / "config.yml").relative_to(tmp_path).as_posix(),
                "files": [{"label": "Report Data", "kind": "json", "path":
                           (files / "original.report-data.json").relative_to(tmp_path).as_posix()}]}
    (run_dir / "manifest.json").write_text(json.dumps(manifest))
    (workspace / "simulations.json").write_text(json.dumps([
        {"id": "sim", "workflow_id": "transient", "name": "Test", "config_text": yaml.safe_dump(cfg)}]))
    return {"vehicle_key": key, "result_id": "recorded", "simulation_id": "sim"}, tmp_path, run_dir


def test_report_edit_preview_export_and_reuse_are_independent_of_recorded_inputs(report_workspace):
    context, root, run_dir = report_workspace
    original = (run_dir / "config.yml").read_bytes()
    payload = report_editor(context)
    assert len(payload["signals"]) == 3
    plots = payload["plots"]
    plots["response"]["title"] = "Edited response"
    plots["response"]["subplots"][0]["overlay"] = {
        "x": {"key": "time"}, "y": {"key": "ay", "scale": .5}, "label": "Overlay"}
    preview = report_editor({**context, "action": "preview", "plots": plots, "page": "response"})
    assert preview["image"].startswith("data:image/png;base64,iVBOR")
    assert [(label["sub"], label["kind"]) for label in preview["labels"] if not label["kind"].endswith("-unit")] == [
        (i, kind) for i in range(2) for kind in ("title", "x", "y")]
    for label in preview["labels"]:
        assert 0 <= label["x"] < 1 and 0 <= label["y"] < 1
        assert label["width"] > 0 and label["height"] > 0
    assert {label["kind"] for label in preview["labels"]} == {"title", "x", "y"}
    report_editor({**context, "action": "save", "plots": plots, "reuse": True})
    assert report_editor(context)["plots"] == plots
    sim = json.loads((run_dir.parent.parent / "simulations.json").read_text())[0]
    config = yaml.safe_load(sim["config_text"])
    assert config["plots"] == plots
    assert config["simulation"] == {"stop_time": 8}
    assert config["report"]["custom_plots"] is True
    exported = report_editor({**context, "action": "export", "plots": plots})
    assert (root / exported["path"]).read_bytes().startswith(b"%PDF")
    assert yaml.safe_load((root / exported["layout_path"]).read_text()) == plots
    assert (run_dir / "config.yml").read_bytes() == original
    assert (run_dir / "files/original.pdf").read_bytes() == b"original report"
    assert not plt.get_fignums()


def test_report_editor_rejects_cross_vehicle_and_missing_signals(report_workspace):
    context, _, run_dir = report_workspace
    with pytest.raises(ValueError, match="vehicle changed"):
        report_editor({**context, "vehicle_key": "elsewhere"})
    with pytest.raises(ValueError, match="not found"):
        report_editor({**context, "result_id": "../elsewhere"})
    plots = definition()
    plots["response"]["subplots"][0]["y"]["key"] = "not-recorded"
    with pytest.raises(ValueError, match="not recorded"):
        report_editor({**context, "action": "export", "plots": plots})
    assert not (run_dir / "report-exports").exists()
    assert not plt.get_fignums()


def test_yaml_can_repair_an_incomplete_visual_page(report_workspace):
    context, _, _ = report_workspace
    result = report_editor({**context, "action": "parse-yaml", "plots": {"unfinished": {}},
                            "yaml": yaml.safe_dump(definition())})
    assert result["plots"] == definition()


@pytest.mark.parametrize("layout,count", [("single", 1), ("dual", 2), ("triple", 3), ("quad", 4)])
def test_all_layouts_apply_axis_limits_and_legend_options(layout, count):
    sub = definition()["response"]["subplots"][0]
    sub["overlay"] = {"x": {"key": "time"}, "y": {"key": "ay"}, "fit": True, "label": "Fit"}
    page = {"layout": layout, "title": "Test", "subplots": [copy.deepcopy(sub) for _ in range(count)]}
    if count == 1:
        page = {**sub, "layout": layout}
    validate_plots({"test": page})
    figures = list(PlotEngine({"plots": {"test": page}}).render(
        {"series": {"time": [0, 1, 2], "yaw": [0, 1, 2], "ay": [0, 2, 4]}}))
    try:
        assert len(figures[0][1].axes) == count
        for axis in figures[0][1].axes:
            assert axis.get_xlim() == (0, 2)
            assert axis.get_ylim() == (-1, 5)
            assert axis.get_legend() is None
            assert len(axis.lines) == 3  # Base, overlay and overlay's fit.
            assert any(text.get_text() == "Fit: y = 2 x + 0" for text in axis.texts)
    finally:
        plt.close(figures[0][1])


def test_snapshot_handles_numpy_missing_values_and_raw_signals(tmp_path: Path):
    save_report_data(tmp_path / "report.pdf", {"plots": {}}, {
        "series": {"processed": np.array([0, np.nan])},
        "cases": [{"time": np.array([0, 1]), "yaw": np.array([1, 2]), "_private": "excluded"}],
    })
    data = json.loads((tmp_path / "report.report-data.json").read_text())
    assert data["result"]["series"]["processed"] == [0, None]
    assert data["result"]["series"]["raw:yaw"] == [1, 2]


def test_custom_four_post_pages_are_not_replaced_by_default_migrations():
    from app.native_four_post import report_plots
    from simulations.response.mbd.four_post.four_post_eval_sim import _normalize_four_post_report_config
    plots = {"jacking_roll": definition()["response"]}
    cfg = {"report": {"custom_plots": True}, "plots": copy.deepcopy(plots)}
    _normalize_four_post_report_config(cfg)
    assert report_plots(cfg) == plots


@pytest.mark.parametrize("action", ["load", "preview", "export", "save"])
def test_report_view_operations_do_not_take_the_simulation_workspace_lock(monkeypatch, action):
    from app import execution, server
    from app import report_editor as module
    handler = object.__new__(server.BobSimHandler)
    handler.headers = {"Host": "127.0.0.1:8765", "Content-Type": "application/json"}
    handler.path = "/api/reports/editor"
    monkeypatch.setattr(server, "sync_runtime", lambda: None)
    monkeypatch.setattr(module, "report_editor", lambda body: {"action": body["action"]})
    handler._read_json_body = lambda: {"action": action}
    responses = []
    handler._send_json = responses.append
    handler._send_error = lambda *args: pytest.fail(str(args))
    execution.reserve()
    try:
        handler.do_POST()
        assert responses == [{"action": action}]
    finally:
        execution.LOCK.release()


def test_reusing_layout_respects_a_running_simulation(monkeypatch):
    from app import execution, server
    from app import report_editor as module
    handler = object.__new__(server.BobSimHandler)
    handler.headers = {"Host": "127.0.0.1:8765", "Content-Type": "application/json"}
    handler.path = "/api/reports/editor"
    monkeypatch.setattr(server, "sync_runtime", lambda: None)
    monkeypatch.setattr(module, "report_editor", lambda body: pytest.fail("Must not edit running inputs"))
    handler._read_json_body = lambda: {"action": "save", "reuse": True}
    errors = []
    handler._send_error = lambda *args: errors.append(args)
    execution.reserve()
    try:
        handler.do_POST()
        assert "active workspace" in errors[0][1]
    finally:
        execution.LOCK.release()


def test_preview_theme_does_not_change_pdf_style(report_workspace, monkeypatch):
    context, _, _ = report_workspace
    backgrounds = []
    from matplotlib.figure import Figure
    original = Figure.savefig
    def record(self, *args, **kwargs):
        backgrounds.append(self.get_facecolor())
        return original(self, *args, **kwargs)
    monkeypatch.setattr(Figure, "savefig", record)
    plots = definition()
    preview = report_editor({**context, "action": "preview", "plots": plots,
                             "page": "response", "theme": "dark"})
    assert len(preview["axes"]) == 2
    report_editor({**context, "action": "export", "plots": plots, "theme": "dark"})
    assert backgrounds[0] != (1, 1, 1, 1)
    assert backgrounds[-1] == (1, 1, 1, 1)


@pytest.mark.parametrize("script", ["report_metrics.cjs", "report_units.cjs", "report_scroll.cjs"])
def test_report_browser_metric_logic(script):
    node = shutil.which("node")
    if node is None:
        pytest.skip("Node.js is not installed")
    subprocess.run([node, str(Path(__file__).with_name(script))], cwd=app.PACKAGE_ROOT, check=True)


def test_fit_equation_uses_displayed_units_and_skips_constant_x():
    from common.plotting.plot_types.signal_plot import SignalPlot
    plotter = SignalPlot()
    fig, ax = plt.subplots()
    try:
        plotter.draw_fit(ax, [0, 1000, 2000], [1, 3, 5], {}, color="blue")
        assert ax.texts[0].get_text() == "Fit: y = 0.002 x + 1"
        plotter.draw_fit(ax, [1, 1, 1], [1, 2, 3], {}, color="blue")
        assert len(ax.texts) == 1
    finally:
        plt.close(fig)
