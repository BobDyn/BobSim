from _0_Utils.plotting.plot_types.signal_plot import SignalPlot
from _0_Utils.plotting.layouts.single import SingleLayout
from _0_Utils.plotting.layouts.dual import DualLayout
from _0_Utils.plotting.layouts.triple import TripleLayout
from _0_Utils.plotting.layouts.quad import QuadLayout
from pathlib import Path


TYPE_REGISTRY = {
    "signal": SignalPlot,
}

LAYOUT_REGISTRY = {
    "single": SingleLayout,
    "dual": DualLayout,
    "triple": TripleLayout,
    "quad": QuadLayout,
}


class PlotEngine:
    def __init__(self, config):
        self.config = config

    def run(self, result, pdf):

        for plot_name, fig in self.render(result):
            pdf.savefig(fig)

    def save_pngs(self, result, output_directory, *, dpi=200):
        """Render configured pages as inspectable standalone PNG files."""

        output = Path(output_directory)
        output.mkdir(parents=True, exist_ok=True)
        paths = []
        for plot_name, fig in self.render(result):
            path = output / f"{plot_name}.png"
            fig.savefig(path, dpi=dpi)
            paths.append(path)
        return paths

    def render(self, result):
        """Yield ``(plot_name, figure)`` for each configured page."""

        raw_plots_only = bool(
            self.config.get("report", {}).get("raw_plots_only", False)
        )

        for plot_name, p_cfg in self.config.get("plots", {}).items():
            if raw_plots_only and not plot_name.startswith("raw_"):
                print(f"[plot] Skipping non-raw plot page: {plot_name}")
                continue

            print(f"[plot] Rendering plot page: {plot_name}")

            if p_cfg.get("skip_if_missing"):
                subplots = p_cfg.get("subplots")
                plot_cfgs = subplots if subplots is not None else [p_cfg]
                has_data = False
                plotter = SignalPlot()

                for sub in plot_cfgs:
                    try:
                        series = plotter.get_xy(result, sub)
                    except KeyError:
                        continue

                    for item in series:
                        if len(item["x"]) and len(item["y"]):
                            has_data = True
                            break

                    if has_data:
                        break

                if not has_data:
                    print(f"[plot] Skipping optional plot page: {plot_name}")
                    continue

            layout_name = p_cfg.get("layout", "single")
            layout = LAYOUT_REGISTRY[layout_name]()

            if "subplots" in p_cfg:

                plotter = SignalPlot()
                fig = layout.render(plotter, result, p_cfg)

            else:

                plot_type = p_cfg.get("type", "signal")
                plotter = TYPE_REGISTRY[plot_type]()
                fig = layout.render(plotter, result, p_cfg)

            yield plot_name, fig
