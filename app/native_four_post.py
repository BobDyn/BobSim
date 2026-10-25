"""Run the Simulation workspace's four-post analysis using cached axle rigs."""
from __future__ import annotations

import copy
import csv
import json
import math
from pathlib import Path

import numpy as np

from app import native_runs
from common import config_io, native_artifacts
from common.vehicle_io import load_yaml, repo_root

KINDS = ("knc-front", "knc-rear", "knc-rear-traction")


# These are axle quantities; corner-alignment plots retain their existing quads.
GEOMETRY_REPORT_METRICS = {
    "geometric_rc_height_roll": ("Geometric RC height vs roll", "roll_rc_height_mm", "Geometric RC height (mm)"),
    "geometric_rc_lateral_roll": ("Geometric RC lateral position vs roll",
                                  "roll_rc_y_mm", "Geometric RC lateral position (mm)"),
    "jacking_ratio_roll": ("Jacking / applied lateral force vs roll",
                           "roll_jacking_ratio", "Jacking / applied force (N/N)"),
    "moment_ratio_roll": ("Moment / applied lateral force vs roll",
                           "roll_reaction_per_fy_m", "Moment / applied force (m)"),
    "geometric_anti_roll": ("Geometric anti-roll proxy vs roll", "roll_anti_roll_pct", "Geometric anti-roll proxy (%)"),
}


def report_plots(config: dict) -> dict:
    """Offer optional native geometry plots without mutating saved selections."""
    plots = copy.deepcopy(config.get("plots", {}))
    for name, (title, metric, label) in GEOMETRY_REPORT_METRICS.items():
        definition = {"enabled": False, "layout": "dual", "title": title,
            "subplots": [{"title": side.title(),
                "x": {"key": prefix + "_native_roll_deg", "label": "Roll (deg)"},
                "y": {"key": prefix + "_" + metric, "label": label}}
                for side, prefix in (("front", "fr"), ("rear", "rr"))]}
        # Older saved configs may contain only an enabled flag for a new plot.
        definition.update(plots.get(name, {}))
        plots[name] = definition
    return plots


def force_settings(vehicle: dict, config: dict) -> dict:
    """Resolve physical force shares separately from imposed suspension pose."""
    defaults = {"front_brake_share": vehicle.get("brake", {}).get("front_bias", .5),
                "front_left_lateral_share": .5, "rear_left_lateral_share": .5}
    result = {name: float(config.get("force_based", {}).get(name, value)) for name, value in defaults.items()}
    if any(not math.isfinite(value) or not 0 <= value <= 1 for value in result.values()):
        raise ValueError("Force shares must be between 0% and 100%")
    return result


def unavailable_reason(vehicle: dict) -> str:
    """Check the architecture bundles without requiring a compiler or records."""
    try:
        selection = native_artifacts.architecture(vehicle)
        for kind in KINDS:
            directory = native_artifacts.artifact_dir(selection, kind)
            manifest = native_artifacts.checked_manifest(directory)
            if manifest["identity"] != native_artifacts.identity(selection, kind):
                return "Build the matching KnC binaries in Architecture first."
    except (OSError, ValueError, KeyError, TypeError):
        return "Build the matching KnC binaries in Architecture first."
    return ""


class AxleRunner:
    """Adapt independent native axle signals to the existing four-corner report."""

    def __init__(self, vehicle: dict, root: Path, force_based: dict | None = None):
        self.vehicle = vehicle
        self.root = root
        self.runs: list[dict] = []
        self.force_based = force_settings(vehicle, {"force_based": force_based or {}})

    def run(self, *, signals, mode, cases, execution):
        """Run each static-balance iteration with fresh runtime calibration."""
        outputs = []
        for case in cases:
            vehicle = copy.deepcopy(self.vehicle)
            for side, prefix, bar_prefix in (("front", "pVehicle.pFrAxleDW", "pFrStabar"),
                                             ("rear", "pVehicle.pRrAxleDW", "pRrStabar")):
                shock = vehicle[side]["actuation"]["shock"]
                shock["free_length_m"] = case[prefix + ".springFreeLength"]
                table = shock["spring_table"]["table"]
                for i, row in enumerate(table, 1):
                    for j in range(1, len(row) + 1):
                        row[j - 1] = case[f"{prefix}.springTable[{i},{j}]"]
                if "stabar" in vehicle[side]["actuation"]:
                    vehicle[side]["actuation"]["stabar"]["rate_n_m_per_rad"] = case[bar_prefix + ".barRate"]
            settings = {key: case[key] for key in ("heaveMagnitude", "rollMagnitude", "forceMagnitude")}
            results, frames = {}, {}
            for kind in KINDS:
                print(f"{case.get('_case_label', 'Four Post')}: cached {kind}", flush=True)
                result = native_runs.run(vehicle, kind, {**settings, "include_stabilizer": True,
                    "lateralLeftShare": self.force_based[kind.split("-")[1] + "_left_lateral_share"],
                    "steerMagnitude": case["steerMagnitude"] if kind == "knc-front" else 0.0})
                results[kind] = result
                with (self.root / result["csv"]).open() as stream:
                    rows = list(csv.DictReader(stream))
                frames[kind] = {key: np.array([float(row[key]) for row in rows]) for key in rows[0]}
            self.runs.append(results)
            # Both rigs execute the same 118-second heave/roll protocol. Retain
            # their physical time coordinates; union handles differing event rows.
            time = np.unique(np.concatenate([frame["time"] for frame in frames.values()]))
            output = {"time": time, "_status": "ok", "_case_label": case.get("_case_label", "Four Post")}
            for signal in signals:
                prefix, suffix = signal.split(".", 1)
                kind = "knc-front" if prefix == "frKnC" else "knc-rear"
                frame = frames[kind]
                values = np.interp(time, frame["time"], frame["knc." + suffix])
                # Rear anti-squat requires drive torque through the shafts. The
                # rear braking rig still supplies the roll/load-transfer sweep.
                if prefix == "rrKnC":
                    traction = frames["knc-rear-traction"]
                    values = np.where(time < 60, np.interp(
                        time, traction["time"], traction["knc." + suffix]), values)
                output[signal] = values
            directory = self.root / "app/user_data/results/four-post"
            directory.mkdir(parents=True, exist_ok=True)
            path = directory / "signals.csv"
            with path.open("w", newline="") as stream:
                writer = csv.writer(stream)
                writer.writerow(["time", *signals])
                writer.writerows(zip(time, *(output[key] for key in signals)))
            output["_result_file"] = path.as_posix()
            outputs.append(output)
        return outputs


def apply_force_results(result: dict, runs: dict, shares: dict) -> None:
    """Use the native reaction calculation with explicit loading assumptions.

    Brake share weights the per-axle response to total vehicle braking force.
    It does not change the probe force or the rear-only drive normalization.
    Lateral shares are applied inside the rigs, including their moment balance.
    """
    series, summary = result["series"], result["summary"]
    for side, prefix in (("front", "fr"), ("rear", "rr")):
        data = runs["knc-" + side]["curves"]
        roll = np.radians(data["x_axes"]["roll_deg"])
        series[prefix + "_native_roll_deg"] = np.asarray(data["x_axes"]["roll_deg"], dtype=float)
        for _, metric, _ in GEOMETRY_REPORT_METRICS.values():
            series[prefix + "_" + metric] = np.asarray(
                data["curves"].get(metric, [None] * len(roll)), dtype=float)
        height = np.asarray(data["curves"]["roll_force_rc_height_mm"], dtype=float) / 1000
        anti = np.asarray(data["curves"]["roll_force_anti_roll_pct"], dtype=float)
        series[prefix + "_fbrc_vs_roll_x"] = roll
        series[prefix + "_fbrc_height_vs_roll"] = height
        series[prefix + "_jacking_vs_roll_x"] = roll
        series[prefix + "_anti_vs_roll"] = anti
        summary[f"avg_fbrc_equivalent_height_{side}_m"] = finite_mean(height)
        summary[f"avg_anti_roll_{side}_pct"] = finite_mean(anti)
        longitudinal = data if side == "front" else runs["knc-rear-traction"]["curves"]
        key = "anti_dive" if side == "front" else "anti_squat"
        heave = -np.asarray(longitudinal["x_axes"]["heave_mm"], dtype=float) / 1000
        values = np.asarray(longitudinal["curves"][f"bump_{key}_pct"], dtype=float)
        if side == "front":
            values *= shares["front_brake_share"]
        order = np.argsort(heave)
        series[prefix + "_jacking_vs_heave_x"] = heave[order]
        series[prefix + "_anti_vs_heave"] = values[order]
        summary[f"avg_{key}_pct"] = finite_mean(values)
    summary.update({name + "_pct": 100 * value for name, value in shares.items()})


def finite_mean(values) -> float:
    """Keep undefined force metrics missing instead of inventing zero."""
    values = np.asarray(values, dtype=float)
    finite = values[np.isfinite(values)]
    return float(np.mean(finite)) if len(finite) else float("nan")


def run(vehicle: dict, config: dict, root: Path) -> dict:
    """Preserve Four Post balancing, metrics, plots and layouts using native rigs."""
    from common.reporting.report_engine import ReportEngine
    from simulations.response.mbd.four_post.four_post_eval_sim import (
        FourPostEvalSim, _normalize_four_post_report_config, write_metrics_csv,
    )
    config = copy.deepcopy(config)
    _normalize_four_post_report_config(config)
    config["plots"] = report_plots(config)
    shares = force_settings(vehicle, config)
    runner = AxleRunner(vehicle, root, shares)
    simulation = FourPostEvalSim(config)
    result = simulation.run(runner=runner)
    apply_force_results(result, runner.runs[-1], shares)
    write_metrics_csv(result["summary"], result["metrics_csv_path"])
    provenance = root / "app/user_data/results/four-post/provenance.json"
    provenance.write_text(json.dumps({"force_based": shares, "iterations": runner.runs}, indent=2))
    plots = simulation.config.get("plots", {})
    if "jacking_roll" in plots:
        plots["jacking_roll"]["title"] = "Force-Based Anti-Roll vs Roll"
        for subplot in plots["jacking_roll"]["subplots"]:
            subplot["y"]["label"] = "Force-based anti-roll (axle-normalized, %)"
    if "jacking_heave" in plots:
        for subplot in plots["jacking_heave"].get("subplots", []):
            subplot["y"]["label"] = ("Anti-dive (selected brake share, %)"
                                      if subplot["y"]["key"] == "fr_anti_vs_heave" else "Anti-squat (RWD, %)")
    simulation.config["report"]["notes"] = [*simulation.config["report"].get("notes", []),
        f"Front brake-force share: {100 * shares['front_brake_share']:g}%; rear drive-force share: 100% (RWD).",
        f"Left (+) lateral-force share: front {100 * shares['front_left_lateral_share']:g}%, "
        f"rear {100 * shares['rear_left_lateral_share']:g}%. These are force shares, not vertical load transfer."]
    if config.get("report", {}).get("enabled", True):
        ReportEngine(simulation.config).build(result)
    return result


def main() -> None:
    """Load active inputs and run without generating records or compiling."""
    root = repo_root()
    config = load_yaml(config_io.resolve("simulations/response/mbd/four_post/four_post_eval_config.yml", root=root))
    run(load_yaml(root / "vehicle.yml"), config, root)


if __name__ == "__main__":
    main()
