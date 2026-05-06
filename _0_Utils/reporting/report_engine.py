from pathlib import Path
from matplotlib.backends.backend_pdf import PdfPages

from _0_Utils.plotting.plot_engine import PlotEngine
from _0_Utils.reporting.sections import add_summary_page, add_title_page


class ReportEngine:
    def __init__(self, config):
        self.config = config

    def build(self, result):
        print("📄 ReportEngine.build() called")

        report_cfg = self.config.get("report", {})

        print("📄 report config:", report_cfg)

        if not report_cfg.get("enabled", True):
            print("🚫 Report disabled")
            return

        output_path = Path(
            report_cfg.get(
                "output_path",
                "_2_StandardSim/results/report.pdf",
            )
        )

        print("📄 Writing report to:", output_path.resolve())

        output_path.parent.mkdir(parents=True, exist_ok=True)

        standard = self.config.get("standard") or report_cfg.get("standard")

        if standard is None:
            raise KeyError(
                "Missing standard in config. Add `standard: ISO4138`, "
                "`standard: ISO7401`, or `standard: KnC` at the top level "
                "of the YAML."
            )

        with PdfPages(output_path) as pdf:
            add_title_page(pdf, self.config)

            if standard == "ISO4138":
                add_summary_page(pdf, result["summary"])

            elif standard == "ISO7401":
                from _0_Utils.reporting.sections import (
                    add_iso7401_step_page,
                    add_iso7401_frequency_page,
                )

                add_iso7401_step_page(pdf, result["summary"])
                add_iso7401_frequency_page(pdf, result["summary"])

            elif standard == "KnC":
                from _0_Utils.reporting.sections import add_knc_summary_page

                add_knc_summary_page(pdf, result["summary"])

            else:
                raise ValueError(f"Unknown standard: {standard}")

            if "plots" in self.config:
                PlotEngine(self.config).run(result, pdf)

        print("✅ Report written")