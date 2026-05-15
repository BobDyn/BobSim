import matplotlib.pyplot as plt
import numpy as np


class DualLayout:
    def render(self, plotter, result, p_cfg):

        fig, axes = plt.subplots(1, 2, figsize=(11, 8.5))

        for ax, sub in zip(axes, p_cfg["subplots"]):
            series = plotter.get_xy(result, sub)

            xscale = sub.get("xscale", p_cfg.get("xscale", "linear"))
            yscale = sub.get("yscale", p_cfg.get("yscale", "linear"))
            ax.set_xscale(xscale)
            ax.set_yscale(yscale)

            style = sub.get("style", "line")
            xmins = []
            xmaxs = []
            has_data = False

            for item in series:
                x = np.asarray(item["x"], dtype=float)
                y = np.asarray(item["y"], dtype=float)
                if x.size == 0 or y.size == 0:
                    continue

                has_data = True
                xmins.append(float(np.nanmin(x)))
                xmaxs.append(float(np.nanmax(x)))

                label = item.get("label")
                item_style = item.get("style", style)
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

                if item_style == "line":
                    line, = ax.plot(x, y, linewidth=linewidth, label=label, **plot_kwargs)
                elif item_style == "scatter":
                    line, = ax.plot(x, y, "o", label=label, **plot_kwargs)
                else:
                    line, = ax.plot(x, y, linewidth=linewidth, label=label, **plot_kwargs)

                fit = plotter.compute_fit(x, y, sub) if item.get("fit", sub.get("fit", False)) else None
                if fit is not None:
                    ax.plot(
                        x,
                        fit,
                        "--",
                        linewidth=2,
                        color=line.get_color(),
                        alpha=0.85,
                    )

            # REFERENCE LINES
            refs = sub.get("reference")
            if refs:
                if isinstance(refs, dict):
                    refs = [refs]
                for ref in refs:
                    if ref["type"] == "horizontal":
                        ax.axhline(
                            y=ref["y"],
                            linestyle=":",
                            linewidth=2,
                            color=ref.get("color", "black"),
                            label=ref.get("label", None),
                        )

            # AXES
            ax.set_title(sub["title"], fontsize=12)
            ax.set_xlabel(sub["x"].get("label", sub["x"]["key"]), fontsize=11)
            ax.set_ylabel(sub["y"].get("label", sub["y"]["key"]), fontsize=11)

            if has_data and xmins and xmaxs:
                ax.set_xlim(min(xmins), max(xmaxs))

            ax.grid(True, linestyle="--", linewidth=0.5, alpha=0.7)
            ax.tick_params(labelsize=10)

            if ax.get_legend_handles_labels()[0]:
                ax.legend()

        fig.suptitle(p_cfg.get("title", ""), fontsize=16, y=0.96)
        fig.align_ylabels()

        fig.subplots_adjust(
            left=1.25 / 11,
            right=1 - 0.9 / 11,
            bottom=0.9 / 8.5,
            top=1 - 0.9 / 8.5,
            wspace=0.3,
        )

        return fig
