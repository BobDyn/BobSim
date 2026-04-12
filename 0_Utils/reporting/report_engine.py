from pathlib import Path
from matplotlib.backends.backend_pdf import PdfPages

from Utils.plotting.plot_engine import PlotEngine
from Utils.reporting.sections import add_summary_page, add_title_page


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

        report_cfg = self.config.get("report", {})

        output_path = Path(
            report_cfg.get(
                "output_path",
                "StandardSim/ISO4138/results/report.pdf"
            )
        )

        print("📄 Writing report to:", output_path.resolve())

        output_path.parent.mkdir(parents=True, exist_ok=True)

        with PdfPages(output_path) as pdf:
            add_title_page(pdf, self.config)
            add_summary_page(pdf, result["summary"])

            if "plots" in self.config:
                PlotEngine(self.config).run(result, pdf)

        print("✅ Report written")