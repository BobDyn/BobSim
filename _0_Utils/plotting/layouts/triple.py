import matplotlib.pyplot as plt
import numpy as np


class TripleLayout:
    def render(self, plotter, result, p_cfg):

        fig, axes = plt.subplots(3, 1, figsize=(11, 8.5))

        for ax, sub in zip(axes, p_cfg["subplots"]):
            x, y = plotter.get_xy(result, sub)

            xscale = sub.get("xscale", p_cfg.get("xscale", "linear"))
            yscale = sub.get("yscale", p_cfg.get("yscale", "linear"))
            ax.set_xscale(xscale)
            ax.set_yscale(yscale)

            ax.plot(x, y, linewidth=2)

            ax.set_xlim(np.min(x), np.max(x))

            ax.set_title(sub["title"], fontsize=12)
            ax.set_xlabel(sub["x"].get("label", sub["x"]["key"]), fontsize=11)
            ax.set_ylabel(sub["y"].get("label", sub["y"]["key"]), fontsize=11)

            ax.grid(True, linestyle="--", linewidth=0.5, alpha=0.7)
            ax.tick_params(labelsize=10)

        fig.suptitle(p_cfg.get("title", ""), fontsize=16, y=0.965)
        fig.align_ylabels()

        fig.subplots_adjust(
            left=1.25 / 11,
            right=1 - 0.9 / 11,
            bottom=0.9 / 8.5,
            top=1 - 0.9 / 8.5,
            hspace=0.45,
        )

        return fig