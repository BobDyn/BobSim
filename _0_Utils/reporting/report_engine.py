from pathlib import Path
import math

import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages
import pandas as pd

from _0_Utils.plotting.plot_engine import PlotEngine
from _0_Utils.reporting.sections import add_summary_page, add_title_page

DEFAULT_RAW_TIME_SERIES_ABS_LIMIT = 1e9


def _case_result_path(case):
    raw_path = case.get("_result_file") if isinstance(case, dict) else None
    if not raw_path:
        return None
    path = Path(raw_path)
    return path if path.is_file() else None


def _case_label(case, index):
    if not isinstance(case, dict):
        return f"Run {index}"
    return str(case.get("_case_label") or case.get("label") or f"Run {index}")


def _downsample_frame(frame, max_points):
    if max_points <= 0 or len(frame) <= max_points:
        return frame
    step = max(1, math.ceil(len(frame) / max_points))
    return frame.iloc[::step, :]


def _raw_time_series_frame(path, max_points, max_abs_value=DEFAULT_RAW_TIME_SERIES_ABS_LIMIT):
    data = pd.read_csv(path)
    if data.empty:
        return pd.DataFrame(), None, []
    numeric = data.apply(pd.to_numeric, errors="coerce").dropna(axis=1, how="all")
    if max_abs_value and max_abs_value > 0:
        numeric = numeric.mask(numeric.abs() > float(max_abs_value)).dropna(axis=1, how="all")
    if numeric.empty:
        return pd.DataFrame(), None, []
    time_column = next((column for column in ("time", "Time", "t") if column in numeric.columns), None)
    plot_frame = _downsample_frame(numeric, max_points)
    signals = [column for column in plot_frame.columns if column != time_column]
    return plot_frame, time_column, signals


def _add_raw_time_series_appendix(pdf, result, config):
    report_cfg = config.get("report", {})
    if not isinstance(report_cfg, dict):
        report_cfg = {}
    standard = config.get("standard") or report_cfg.get("standard") or "Simulation"
    default_enabled = standard != "FourPostEval"
    if not report_cfg.get("raw_time_series_appendix", default_enabled):
        return
    cases = [case for case in result.get("cases", []) if _case_result_path(case)]
    if not cases:
        return
    max_points = int(report_cfg.get("raw_time_series_max_points", 2500))
    max_abs_value = float(
        report_cfg.get("raw_time_series_max_abs_value", DEFAULT_RAW_TIME_SERIES_ABS_LIMIT)
    )
    print("[report] Rendering raw time-series appendix")
    for case_index, case in enumerate(cases, start=1):
        path = _case_result_path(case)
        if path is None:
            continue
        frame, time_column, signals = _raw_time_series_frame(path, max_points, max_abs_value)
        if frame.empty or not signals:
            continue
        x = frame[time_column] if time_column else pd.Series(range(len(frame)), index=frame.index)
        x_label = time_column or "sample"
        label = _case_label(case, case_index)
        chunks = [signals[index : index + 4] for index in range(0, len(signals), 4)]
        for page_index, chunk in enumerate(chunks, start=1):
            fig, axes = plt.subplots(2, 2, figsize=(11, 8.5), squeeze=False)
            fig.suptitle(f"{standard} Raw Time Series - {label} ({page_index}/{len(chunks)})", fontsize=12)
            for axis, signal in zip(axes.ravel(), chunk):
                axis.plot(x, frame[signal], linewidth=0.8)
                axis.set_title(str(signal), fontsize=8)
                axis.set_xlabel(x_label, fontsize=7)
                axis.tick_params(axis="both", labelsize=7)
                axis.grid(True, alpha=0.25)
            for axis in axes.ravel()[len(chunk):]:
                axis.axis("off")
            fig.tight_layout(rect=(0, 0, 1, 0.95))
            pdf.savefig(fig)
            plt.close(fig)


class ReportEngine:
    def __init__(self, config):
        self.config = config

    def build(self, result):
        print("[report] ReportEngine.build() called")

        report_cfg = self.config.get("report", {})

        print("[report] report config:", report_cfg)

        if not report_cfg.get("enabled", True):
            print("[report] Report disabled")
            return

        output_path = Path(
            report_cfg.get(
                "output_path",
                "_3_StandardSim/results/report.pdf",
            )
        )

        print("[report] Writing report to:", output_path.resolve())

        output_path.parent.mkdir(parents=True, exist_ok=True)
        output_path.unlink(missing_ok=True)

        standard = self.config.get("standard") or report_cfg.get("standard")
        summary_units = report_cfg.get("summary_units")
        if summary_units is not None and not isinstance(summary_units, dict):
            raise TypeError("report.summary_units must be a mapping if provided.")

        if standard is None:
            raise KeyError(
                "Missing standard in config. Add `standard: SteadyStateEval`, "
                "`standard: RampSteerEval`, `standard: TransientEval`, "
                "`standard: FourPostEval`, or `standard: FbrcEval` at the top "
                "level of the YAML."
            )

        with PdfPages(output_path) as pdf:
            add_title_page(pdf, self.config)

            if standard in {"SteadyStateEval", "RampSteerEval"}:
                velocity_summaries = result.get("velocity_summaries", [])
                if velocity_summaries:
                    for summary in velocity_summaries:
                        velocity = summary.get("velocity_mps")
                        page_title = f"{standard} Summary"
                        if velocity is not None:
                            page_title = f"{page_title} {velocity:.1f} m/s"
                        print(f"[report] Rendering summary page: {page_title}")
                        add_summary_page(
                            pdf,
                            summary,
                            title=page_title,
                        )
                else:
                    print(f"[report] Rendering summary page: {standard} Summary")
                    add_summary_page(
                        pdf,
                        result["summary"],
                        title=f"{standard} Summary",
                    )

            elif standard == "TransientEval":
                from _0_Utils.reporting.sections import (
                    add_transient_eval_step_page,
                    add_transient_eval_frequency_page,
                )

                velocity_summaries = result.get("velocity_summaries", [])
                if velocity_summaries:
                    for summary in velocity_summaries:
                        velocity = summary.get("velocity_mps")
                        page_title = "TransientEval Metrics Summary"
                        if velocity is not None:
                            page_title = f"{page_title} {velocity:.1f} m/s"
                        print(f"[report] Rendering summary page: {page_title}")
                        add_transient_eval_step_page(pdf, summary)
                        add_transient_eval_frequency_page(pdf, summary)
                else:
                    print("[report] Rendering summary page: TransientEval Metrics Summary")
                    add_transient_eval_step_page(pdf, result["summary"])
                    add_transient_eval_frequency_page(pdf, result["summary"])

            elif standard in {"KnC", "FourPostEval"}:
                from _0_Utils.reporting.sections import add_four_post_setup_page, add_knc_summary_page

                if standard == "FourPostEval":
                    add_four_post_setup_page(pdf, result.get("setup", {}))

                page_title = "KnC Metrics Summary" if standard == "KnC" else "FourPostEval Metrics Summary"
                add_knc_summary_page(
                    pdf,
                    result["summary"],
                    title=page_title,
                    unit_overrides=summary_units,
                )

            elif standard == "FbrcEval":
                from _0_Utils.reporting.sections import add_fbrc_summary_page

                print("[report] Rendering summary page: FbrcEval Metrics Summary")
                add_fbrc_summary_page(
                    pdf,
                    result["summary"],
                    title="FbrcEval Metrics Summary",
                    unit_overrides=summary_units,
                )

            else:
                raise ValueError(f"Unknown standard: {standard}")

            if "plots" in self.config:
                print("[report] Rendering plot pages")
                PlotEngine(self.config).run(result, pdf)

            _add_raw_time_series_appendix(pdf, result, self.config)

        print("[report] Report written")
