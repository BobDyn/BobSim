"""Edit report layouts and render archived signals without running a solver."""
from __future__ import annotations

import base64
import copy
from io import BytesIO
import json
import re
from pathlib import Path
import threading
from typing import Any
from uuid import uuid4

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages
import pandas as pd
import yaml

from common.plotting.plot_engine import PlotEngine
from common.reporting.editable import validate_plots

_RENDER_LOCK = threading.RLock()
_INPUT_CACHE: dict[tuple, tuple[dict, dict, list[str]]] = {}


def _context(body: dict) -> tuple[Any, dict | None, dict | None, Path]:
    from app import data_services as ds
    key = ds._active_vehicle_workspace_key()
    if body.get("vehicle_key") != key:
        raise ValueError("The active vehicle changed. Reopen the report editor.")
    runs = ds.saved_results_payload(key)["results"]
    run = next((r for r in runs if r["id"] == body.get("result_id")), None)
    if body.get("result_id") and run is None:
        raise ValueError("Saved run not found for this vehicle.")
    sim_path = ds._vehicle_workspace_dir(key) / "simulations.json"
    simulations = json.loads(sim_path.read_text()) if sim_path.exists() else []
    sim = next((s for s in simulations if s["id"] == body.get("simulation_id")), None)
    if body.get("simulation_id") and sim is None:
        raise ValueError("Simulation no longer exists.")
    if sim and run and (run.get("simulation") or {}).get("id") != sim["id"]:
        raise ValueError("Choose a saved run from this simulation.")
    if not run and not sim:
        raise ValueError("Choose a simulation or saved run.")
    directory = (ds._safe_repo_path(run["workspace_result_path"]) if run else
                 ds._vehicle_workspace_dir(key) / "report-layouts" / sim["id"])
    return ds, run, sim, directory


def _inputs(ds: Any, run: dict | None, sim: dict | None) -> tuple[dict, dict, list[str]]:
    if run is None:
        return _read_inputs(ds, run, sim)
    paths = [ds._safe_repo_path(f["path"]) for f in run["files"] if f["kind"] in {"json", "csv"}]
    paths += [ds._safe_repo_path(run[k]) for k in ("config_snapshot", "vehicle_snapshot") if run.get(k)]
    key = (str(ds.ROOT), run["id"], tuple((str(p), p.stat().st_mtime_ns, p.stat().st_size) for p in paths))
    if key not in _INPUT_CACHE:
        if len(_INPUT_CACHE) >= 3:
            _INPUT_CACHE.pop(next(iter(_INPUT_CACHE)))
        _INPUT_CACHE[key] = _read_inputs(ds, run, sim)
    config, result, warnings = _INPUT_CACHE[key]
    return copy.deepcopy(config), result, list(warnings)


def _read_inputs(ds: Any, run: dict | None, sim: dict | None) -> tuple[dict, dict, list[str]]:
    config = yaml.safe_load(sim["config_text"]) if sim else {}
    result: dict = {"series": {}}
    warnings: list[str] = []
    if run:
        config = (yaml.safe_load(ds._safe_repo_path(run["config_snapshot"]).read_text())
                  if run.get("config_snapshot") else {})
        bundle = next((f for f in run["files"] if f["label"] == "Report Data"), None)
        if bundle:
            data = json.loads(ds._safe_repo_path(bundle["path"]).read_text())
            config, result = data["config"], data["result"]
        else:
            warnings.append("This older run has no processed report snapshot. Recorded CSV signals are available; "
                            "missing processed signals are marked below.")
        if not bundle and run.get("workflow", {}).get("id") == "four-post":
            signals = next((f for f in run["files"] if f["label"] == "Signals"), None)
            provenance = next((f for f in run["files"] if f["label"].lower() == "binary provenance"), None)
            if signals and provenance and run.get("vehicle_snapshot"):
                from app.native_four_post import apply_force_results
                from simulations.response.mbd.four_post.four_post_eval_sim import FourPostEvalSim
                recorded = pd.read_csv(ds._safe_repo_path(signals["path"]))
                vehicle = yaml.safe_load(ds._safe_repo_path(run["vehicle_snapshot"]).read_text())
                native = json.loads(ds._safe_repo_path(provenance["path"]).read_text())
                if native.get("iterations") and native.get("force_based"):
                    summary, series = FourPostEvalSim(config).summarize(
                        {str(k): v for k, v in recorded.to_dict("list").items()}, vehicle=vehicle)
                    result = {"summary": summary, "series": series}
                    apply_force_results(result, native["iterations"][-1], native["force_based"])
                    warnings = ["Plot data reconstructed from this run's archived signals, vehicle and force results."]
        for file in run["files"]:
            if file["kind"] != "csv" or "metric" in file["label"].lower():
                continue
            frame = pd.read_csv(ds._safe_repo_path(file["path"]))
            numeric = frame.apply(pd.to_numeric, errors="coerce").dropna(axis=1, how="all")
            prefix = "raw:" if file["label"] == "Signals" else f"raw:{file['label']}:"
            result["series"].update({prefix + str(k): v for k, v in numeric.to_dict("list").items()})
    workflow = (run or {}).get("workflow", {}).get("id") or (sim or {}).get("workflow_id")
    if workflow == "four-post" and not config.get("report", {}).get("custom_plots"):
        from app.native_four_post import report_plots
        config["plots"] = report_plots(config)
    return config, result, warnings


def _references(page: dict) -> set[str]:
    keys = set()
    for sub in page.get("subplots", [page]):
        overlays = sub.get("overlay", [])
        if isinstance(overlays, dict):
            overlays = [overlays]
        for curve in [sub, *overlays]:
            for axis in ("x", "y"):
                key = curve.get(axis, {}).get("key")
                if key:
                    keys.add(key)
    return keys


def report_editor(body: dict) -> dict:
    """Load, save, preview or export the editable report for a saved run."""
    from app import data_services as data_services
    with data_services._SIMULATION_LOCK:
        ds, run, sim, directory = _context(body)
        config, result, warnings = _inputs(ds, run, sim)
        recipe = directory / "report-layout.json"
        action = body.get("action", "load")
        if body.get("from_setup") and sim:
            config = yaml.safe_load(sim["config_text"])
            if sim["workflow_id"] == "four-post":
                from app.native_four_post import report_plots
                config["plots"] = report_plots(config)
        if action == "load":
            plots = (json.loads(recipe.read_text())["plots"]
                     if recipe.exists() and not body.get("from_setup") else config.get("plots", {}))
            signals = [{"key": k, "grouped": isinstance(v, dict),
                        "samples": sum(len(a) for a in v.values()) if isinstance(v, dict) else len(v)}
                       for k, v in result["series"].items() if isinstance(v, (dict, list)) or hasattr(v, "shape")]
            missing = (sorted(set().union(*(_references(p) for p in plots.values())) - result["series"].keys())
                       if plots else [])
            return {"plots": plots, "defaults": config.get("plots", {}), "signals": signals,
                    "warnings": warnings, "missing": missing, "has_results": bool(run),
                    "can_reuse": bool(sim) and ((sim or {}).get("workflow_id") in
                        {"four-post", "steady-state", "ramp-steer", "transient", "mbd-step-steer"}),
                    "title": (run or sim or {}).get("label", (sim or {}).get("name", "Report"))}
        if action == "yaml":
            return {"yaml": yaml.safe_dump(body.get("plots", {}), sort_keys=False)}
        if action == "parse-yaml":
            return {"plots": validate_plots(yaml.safe_load(body.get("yaml", "")))}
        plots = validate_plots(body.get("plots"))
        if action == "save":
            if body.get("reuse"):
                if not sim:
                    raise ValueError("Select a simulation to reuse this layout.")
                ds.simulation_workspace("report-layout",
                                        {"id": sim["id"], "vehicle_key": body["vehicle_key"], "plots": plots})
            directory.mkdir(parents=True, exist_ok=True)
            temporary = recipe.with_suffix(".tmp")
            temporary.write_text(json.dumps({"plots": plots}, indent=2, allow_nan=False))
            temporary.replace(recipe)
            return {"saved": True}
        if action not in {"preview", "export"}:
            raise ValueError("Unknown report editor action.")
        if not run:
            raise ValueError("Run the simulation to preview recorded signals.")
        selected = body.get("page")
        render_plots = {selected: plots[selected]} if action == "preview" and selected in plots else plots
        render_plots = copy.deepcopy(render_plots)
        for name, page in render_plots.items():
            if action == "preview":
                page["enabled"] = True
            if page.get("enabled", True):
                missing = _references(page) - result["series"].keys()
                if missing:
                    raise ValueError(f"{name}: signals not recorded in this run: " + ", ".join(sorted(missing)))
                page.pop("skip_if_missing", None)
        with _RENDER_LOCK:
            figures = []
            try:
                before_figures = set(plt.get_fignums())
                figures = list(PlotEngine({"plots": render_plots}).render(result))
                if not figures:
                    raise ValueError("Enable at least one report page.")
                if action == "preview":
                    fig = figures[0][1]
                    theme = body.get("theme")
                    if theme in {"dark", "light"}:
                        _preview_theme(fig, theme)
                    fig.set_dpi(125)
                    fig.canvas.draw()
                    renderer = fig.canvas.get_renderer()
                    labels = []
                    for index, ax in enumerate(fig.axes):
                        for kind, label in (("title", ax.title), ("x", ax.xaxis.label), ("y", ax.yaxis.label)):
                            bounds = label.get_window_extent(renderer).transformed(fig.transFigure.inverted())
                            labels.append({"sub": index, "kind": kind, "x": bounds.x0, "y": 1 - bounds.y1,
                                           "width": bounds.width, "height": bounds.height})
                            unit = re.search(r"\s*[([][^()[\]]+[)\]]\s*$", label.get_text())
                            if kind != "title" and unit:
                                full_width = renderer.get_text_width_height_descent(
                                    label.get_text(), label.get_fontproperties(), False)[0]
                                unit_width = renderer.get_text_width_height_descent(
                                    unit.group(), label.get_fontproperties(), False)[0]
                                fraction = min(.8, unit_width / max(full_width, 1))
                                unit_box = dict(labels[-1], kind=kind + "-unit")
                                if kind == "x":
                                    unit_box["x"] += bounds.width * (1 - fraction)
                                    unit_box["width"] *= fraction
                                    labels[-1]["width"] *= 1 - fraction
                                else:
                                    unit_box["height"] *= fraction
                                    labels[-1]["y"] += bounds.height * fraction
                                    labels[-1]["height"] *= 1 - fraction
                                labels.append(unit_box)
                    buffer = BytesIO()
                    fig.savefig(buffer, format="png", dpi=125)
                    boxes = [{"x": ax.get_position().x0, "y": 1 - ax.get_position().y1,
                              "width": ax.get_position().width, "height": ax.get_position().height}
                             for ax in fig.axes]
                    return {"image": "data:image/png;base64," + base64.b64encode(buffer.getvalue()).decode(),
                            "axes": boxes, "labels": labels}
                output_dir = directory / "report-exports" / uuid4().hex
                output_dir.mkdir(parents=True)
                target = output_dir / "report.pdf"
                with PdfPages(target) as pdf:
                    for _, fig in figures:
                        pdf.savefig(fig)
                (output_dir / "layout.yml").write_text(yaml.safe_dump(plots, sort_keys=False))
                return {"path": target.relative_to(ds.ROOT).as_posix(),
                        "layout_path": (output_dir / "layout.yml").relative_to(ds.ROOT).as_posix()}
            finally:
                for number in set(plt.get_fignums()) - before_figures:
                    plt.close(number)


def _preview_theme(fig: Any, theme: str) -> None:
    """Style only the interactive preview; PDF figures retain print styling."""
    dark = theme == "dark"
    surface, ink, muted, border = (("#131720", "#dfdfd6", "#98989f", "#2e3340") if dark else
                                   ("#ffffff", "#26262c", "#67676c", "#e2e2e3"))
    fig.set_facecolor(surface)
    if fig._suptitle:
        fig._suptitle.set_visible(False)
    from matplotlib.colors import to_hex
    colors = dict(zip(["#1f77b4", "#ff7f0e", "#2ca02c", "#d62728", "#9467bd"],
                      ["#4ea1ff", "#f9b44e", "#3dd68c", "#f66f81", "#e879a8"])) if dark else {}
    for ax in fig.axes:
        ax.set_facecolor(surface)
        for line in ax.lines:
            color = to_hex(line.get_color())
            if color in colors:
                line.set_color(colors[color])
        ax.tick_params(colors=muted, labelsize=9)
        ax.title.set_color(ink)
        ax.title.set_fontsize(11)
        ax.xaxis.label.set_color(muted)
        ax.yaxis.label.set_color(muted)
        for spine in ax.spines.values():
            spine.set_color(border)
        for line in [*ax.get_xgridlines(), *ax.get_ygridlines()]:
            line.set_color(border)
            line.set_alpha(.65)
        legend = ax.get_legend()
        if legend:
            legend.get_frame().set_facecolor(surface)
            legend.get_frame().set_edgecolor(border)
            for text in legend.get_texts():
                text.set_color(ink)
