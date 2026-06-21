from __future__ import annotations

import csv
from dataclasses import dataclass
from pathlib import Path
import time
from typing import Any

import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages
import numpy as np

from _3_StandardSim._modelica_runner import ModelicaRunner
from _3_StandardSim.FourPostEval.four_post_eval_sim import (
    DEFAULT_BUILD_DIR,
    DEFAULT_CONFIG_PATH,
    DEFAULT_EXEC_NAME,
    FOUR_POST_EVAL_SIGNALS,
    FOUR_POST_EVAL_VARIABLE_FILTER,
    FourPostEvalSim,
    _as_mapping,
    _configured_suspension_setup,
    _indexed_table_overrides,
    load_config,
)


OUTPUT_DIR = Path("_3_StandardSim/results/diagnostics")
OUTPUT_PDF = OUTPUT_DIR / "four_post_override_probe.pdf"
OUTPUT_CSV = OUTPUT_DIR / "four_post_override_probe_metrics.csv"


@dataclass(frozen=True)
class OverrideCase:
    name: str
    label: str
    front_spring_scale: float = 1.0
    rear_spring_scale: float = 1.0
    front_bar_scale: float = 1.0
    rear_bar_scale: float = 1.0


CASES = (
    OverrideCase("baseline", "Baseline"),
    OverrideCase("front_springs_x1p25", "Front springs x1.25", front_spring_scale=1.25),
    OverrideCase("rear_springs_x1p25", "Rear springs x1.25", rear_spring_scale=1.25),
    OverrideCase("front_bar_x2", "Front bar x2", front_bar_scale=2.0),
    OverrideCase("rear_bar_x2", "Rear bar x2", rear_bar_scale=2.0),
)


def _scaled_force_column(table: np.ndarray, scale: float) -> np.ndarray:
    table = np.asarray(table, dtype=float).copy()
    if table.size == 0:
        return table
    table[:, 1] *= float(scale)
    return table


def _case_overrides(
    case: OverrideCase,
    base_overrides: dict[str, Any],
    front_spring_table: np.ndarray,
    rear_spring_table: np.ndarray,
    front_bar_rate: float,
    rear_bar_rate: float,
) -> dict[str, Any]:
    overrides = dict(base_overrides)
    overrides["_mode"] = case.name
    overrides["_case_name"] = case.name
    overrides["_case_label"] = case.label

    overrides.update(
        _indexed_table_overrides(
            "pVehicle.pFrAxleDW.springTable",
            _scaled_force_column(front_spring_table, case.front_spring_scale),
        )
    )
    overrides.update(
        _indexed_table_overrides(
            "pVehicle.pRrAxleDW.springTable",
            _scaled_force_column(rear_spring_table, case.rear_spring_scale),
        )
    )

    scaled_front_bar = front_bar_rate * case.front_bar_scale
    scaled_rear_bar = rear_bar_rate * case.rear_bar_scale
    overrides["pVehicle.pFrStabar.barRate"] = scaled_front_bar
    overrides["pFrStabar.barRate"] = scaled_front_bar
    overrides["pVehicle.pRrStabar.barRate"] = scaled_rear_bar
    overrides["pRrStabar.barRate"] = scaled_rear_bar

    return overrides


def _slope_vs_abs_roll(roll_rad: np.ndarray, values: np.ndarray) -> float:
    x = np.abs(np.asarray(roll_rad, dtype=float))
    y = np.asarray(values, dtype=float)
    mask = np.isfinite(x) & np.isfinite(y) & (x > 1e-6)
    if np.count_nonzero(mask) < 2 or np.nanstd(x[mask]) < 1e-12:
        return float("nan")
    return float(np.polyfit(x[mask], y[mask], 1)[0])


def _case_metrics(label: str, series: dict[str, np.ndarray]) -> dict[str, Any]:
    roll = np.asarray(series["lltd_vs_roll_x"], dtype=float)
    lltd = np.asarray(series["lltd_contact_force_vs_roll"], dtype=float)
    front_lt = np.asarray(series["front_load_transfer_vs_roll"], dtype=float)
    rear_lt = np.asarray(series["rear_load_transfer_vs_roll"], dtype=float)

    lltd_mask = np.isfinite(lltd)
    return {
        "case": label,
        "avg_lltd_front_pct": float(100.0 * np.nanmean(lltd[lltd_mask])) if lltd_mask.any() else float("nan"),
        "front_load_transfer_slope_N_per_rad": _slope_vs_abs_roll(roll, front_lt),
        "rear_load_transfer_slope_N_per_rad": _slope_vs_abs_roll(roll, rear_lt),
        "front_left_fz_at_max_pos_roll_N": float(series["fr_l_fz_vs_roll"][-1]),
        "front_right_fz_at_max_pos_roll_N": float(series["fr_r_fz_vs_roll"][-1]),
        "rear_left_fz_at_max_pos_roll_N": float(series["rr_l_fz_vs_roll"][-1]),
        "rear_right_fz_at_max_pos_roll_N": float(series["rr_r_fz_vs_roll"][-1]),
    }


def _write_metrics(rows: list[dict[str, Any]], path: Path) -> Path:
    path.parent.mkdir(parents=True, exist_ok=True)
    fieldnames = list(rows[0].keys())
    with path.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=fieldnames, lineterminator="\n")
        writer.writeheader()
        writer.writerows(rows)
    return path


def _plot_results(series_by_case: dict[str, dict[str, np.ndarray]], metrics: list[dict[str, Any]], path: Path) -> Path:
    path.parent.mkdir(parents=True, exist_ok=True)
    baseline = series_by_case["Baseline"]
    variants = [case.label for case in CASES if case.name != "baseline"]

    with PdfPages(path) as pdf:
        fig, axes = plt.subplots(2, 2, figsize=(11, 8.5), constrained_layout=True)
        for ax, label in zip(axes.flat, variants, strict=True):
            base_roll_deg = np.rad2deg(baseline["lltd_vs_roll_x"])
            variant = series_by_case[label]
            var_roll_deg = np.rad2deg(variant["lltd_vs_roll_x"])
            ax.plot(base_roll_deg, 100.0 * baseline["lltd_contact_force_vs_roll"], color="0.2", label="Baseline")
            ax.plot(var_roll_deg, 100.0 * variant["lltd_contact_force_vs_roll"], color="#1f77b4", label=label)
            ax.axhline(50.0, color="0.7", linewidth=0.8, linestyle=":")
            ax.set_title(label)
            ax.set_xlabel("Roll (deg)")
            ax.set_ylabel("Front LLTD (%)")
            ax.grid(True, color="0.9", linewidth=0.6)
            ax.legend(fontsize=8)
        fig.suptitle("LLTD Override Probe")
        pdf.savefig(fig)
        plt.close(fig)

        fig, axes = plt.subplots(2, 2, figsize=(11, 8.5), constrained_layout=True)
        for ax, label in zip(axes.flat, variants, strict=True):
            variant = series_by_case[label]
            roll_deg = np.rad2deg(variant["lltd_vs_roll_x"])
            ax.plot(
                roll_deg,
                baseline["front_load_transfer_vs_roll"],
                color="#d62728",
                linestyle="--",
                label="Baseline front",
            )
            ax.plot(
                roll_deg,
                baseline["rear_load_transfer_vs_roll"],
                color="#2ca02c",
                linestyle="--",
                label="Baseline rear",
            )
            ax.plot(roll_deg, variant["front_load_transfer_vs_roll"], color="#d62728", label=f"{label} front")
            ax.plot(roll_deg, variant["rear_load_transfer_vs_roll"], color="#2ca02c", label=f"{label} rear")
            ax.set_title(label)
            ax.set_xlabel("Roll (deg)")
            ax.set_ylabel("Load transfer (N)")
            ax.grid(True, color="0.9", linewidth=0.6)
            ax.legend(fontsize=8)
        fig.suptitle("Contact-Patch Load Transfer Override Probe")
        pdf.savefig(fig)
        plt.close(fig)

        fig, ax = plt.subplots(figsize=(11, 6), constrained_layout=True)
        names = [row["case"] for row in metrics]
        x = np.arange(len(metrics))
        avg_lltd = [row["avg_lltd_front_pct"] for row in metrics]
        ax.bar(x, avg_lltd, color=["0.35", "#1f77b4", "#ff7f0e", "#9467bd", "#2ca02c"])
        ax.axhline(avg_lltd[0], color="0.2", linewidth=1.0, linestyle="--", label="Baseline")
        ax.set_xticks(x, names, rotation=20, ha="right")
        ax.set_ylabel("Average front LLTD (%)")
        ax.set_title("Summary Response")
        ax.grid(True, axis="y", color="0.9", linewidth=0.6)
        ax.legend(fontsize=8)
        pdf.savefig(fig)
        plt.close(fig)

    return path


def run(path: str | Path | None = None) -> dict[str, Any]:
    config = load_config(Path(path) if path is not None else DEFAULT_CONFIG_PATH)
    sim = FourPostEvalSim(config)
    simulation_cfg = _as_mapping(config.get("simulation"), name="simulation")
    execution_cfg = {**_as_mapping(config.get("execution"), name="execution"), "parallel": False, "cleanup": True}

    suspension_setup = _configured_suspension_setup(config)
    front_spring_table = suspension_setup["front_spring_table"]
    rear_spring_table = suspension_setup["rear_spring_table"]
    front_bar_rate = float(suspension_setup["front_stabar_rate"])
    rear_bar_rate = float(suspension_setup["rear_stabar_rate"])

    base_overrides = {**sim.build_overrides(), **sim.build_model_setup_overrides()}
    cases = [
        _case_overrides(
            case,
            base_overrides,
            front_spring_table,
            rear_spring_table,
            front_bar_rate,
            rear_bar_rate,
        )
        for case in CASES
    ]

    runner = ModelicaRunner(
        build_dir=simulation_cfg.get("build_dir", DEFAULT_BUILD_DIR),
        exec_name=simulation_cfg.get("exec_name", DEFAULT_EXEC_NAME),
        simulation={
            **simulation_cfg,
            "variable_filter": simulation_cfg.get("variable_filter", FOUR_POST_EVAL_VARIABLE_FILTER),
        },
    )

    started = time.perf_counter()
    raw_results = runner.run(
        signals=FOUR_POST_EVAL_SIGNALS,
        mode="raw",
        cases=cases,
        execution=execution_cfg,
    )
    runtime_s = time.perf_counter() - started

    failed = [result for result in raw_results if result.get("_status") != "ok"]
    if failed:
        raise RuntimeError(f"{len(failed)} override probe case(s) failed: {failed[0].get('_error', 'unknown error')}")

    series_by_case: dict[str, dict[str, np.ndarray]] = {}
    metrics: list[dict[str, Any]] = []
    for case, raw in zip(CASES, raw_results, strict=True):
        _, series = sim.summarize(raw)
        series_by_case[case.label] = series
        metrics.append(_case_metrics(case.label, series))

    _write_metrics(metrics, OUTPUT_CSV)
    _plot_results(series_by_case, metrics, OUTPUT_PDF)

    return {
        "runtime_s": runtime_s,
        "metrics": metrics,
        "pdf": str(OUTPUT_PDF),
        "csv": str(OUTPUT_CSV),
    }


def main() -> None:
    result = run()
    print(f"WALL_SECONDS {result['runtime_s']:.3f}")
    print(f"PDF {result['pdf']}")
    print(f"CSV {result['csv']}")
    for row in result["metrics"]:
        print(
            "{case}: LLTD={avg_lltd_front_pct:.3f}%, "
            "front LT slope={front_load_transfer_slope_N_per_rad:.3f} N/rad, "
            "rear LT slope={rear_load_transfer_slope_N_per_rad:.3f} N/rad".format(**row)
        )


if __name__ == "__main__":
    main()
