import matplotlib.pyplot as plt
import numpy as np


class TripleLayout:
    def render(self, plotter, result, p_cfg):

        fig, axes = plt.subplots(3, 1, figsize=(11, 8.5))

        for ax, sub in zip(axes, p_cfg["subplots"]):
            series = plotter.get_xy(result, sub)

            xscale = sub.get("xscale", p_cfg.get("xscale", "linear"))
            yscale = sub.get("yscale", p_cfg.get("yscale", "linear"))
            ax.set_xscale(xscale)
            ax.set_yscale(yscale)

            xmins = []
            xmaxs = []
            has_data = False

            # Empty data
            if not series:
                ax.text(0.5, 0.5, "No Data",
                        ha="center", va="center", fontsize=10)
                ax.set_xticks([])
                ax.set_yticks([])
                continue

            for item in series:
                x = np.asarray(item["x"], dtype=float)
                y = np.asarray(item["y"], dtype=float)
                if x.size == 0 or y.size == 0:
                    continue

                has_data = True
                xmins.append(float(np.nanmin(x)))
                xmaxs.append(float(np.nanmax(x)))

                label = item.get("label")
                item_style = item.get("style", "line")
                plot_kwargs = {}
                if item.get("alpha") is not None:
                    plot_kwargs["alpha"] = item["alpha"]
                if item.get("markersize") is not None:
                    plot_kwargs["markersize"] = item["markersize"]
                if item.get("color") is not None:
                    plot_kwargs["color"] = item["color"]
                if item.get("linestyle") is not None:
                    plot_kwargs["linestyle"] = item["linestyle"]
                linewidth = item.get("linewidth", 2)

                if item_style == "scatter":
                    ax.plot(x, y, "o", label=label, **plot_kwargs)
                elif item_style == "line":
                    ax.plot(x, y, linewidth=linewidth, label=label, **plot_kwargs)
                else:
                    ax.plot(x, y, linewidth=linewidth, label=label, **plot_kwargs)

                fit = plotter.compute_fit(x, y, sub) if item.get("fit", sub.get("fit", False)) else None
                if fit is not None:
                    ax.plot(
                        x,
                        fit,
                        "--",
                        linewidth=2,
                        alpha=0.85,
                    )

            if not has_data:
                ax.text(0.5, 0.5, "No Data",
                        ha="center", va="center", fontsize=10)
                ax.set_xticks([])
                ax.set_yticks([])
                continue

            ax.set_xlim(min(xmins), max(xmaxs))

            ax.set_title(sub["title"], fontsize=12)
            ax.set_xlabel(sub["x"].get("label", sub["x"]["key"]), fontsize=11)
            ax.set_ylabel(sub["y"].get("label", sub["y"]["key"]), fontsize=11)

            ax.grid(True, linestyle="--", linewidth=0.5, alpha=0.7)
            ax.tick_params(labelsize=10)

            if ax.get_legend_handles_labels()[0]:
                ax.legend()

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
