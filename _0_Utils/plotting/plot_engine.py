from _0_Utils.plotting.plot_types.signal_plot import SignalPlot
from _0_Utils.plotting.layouts.single import SingleLayout
from _0_Utils.plotting.layouts.dual import DualLayout
from _0_Utils.plotting.layouts.triple import TripleLayout
from _0_Utils.plotting.layouts.quad import QuadLayout


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

        for _, p_cfg in self.config.get("plots", {}).items():

            layout_name = p_cfg.get("layout", "single")
            layout = LAYOUT_REGISTRY[layout_name]()

            # 🔥 CASE 1: multi-plot layout (dual/quad)
            if "subplots" in p_cfg:

                plotter = SignalPlot()  # always signal for now
                fig = layout.render(plotter, result, p_cfg)

            # 🔥 CASE 2: single plot
            else:

                plot_type = p_cfg.get("type", "signal")
                plotter = TYPE_REGISTRY[plot_type]()
                fig = layout.render(plotter, result, p_cfg)

            pdf.savefig(fig)