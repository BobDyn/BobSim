import matplotlib.pyplot as plt
import numpy as np


class SingleLayout:
    def render(self, plotter, result, p_cfg):

        fig, ax = plt.subplots(figsize=(11, 8.5))

        series = plotter.get_xy(result, p_cfg)

        xscale = p_cfg.get("xscale", "linear")
        yscale = p_cfg.get("yscale", "linear")
        ax.set_xscale(xscale)
        ax.set_yscale(yscale)

        style = p_cfg.get("style", "line")
        xmins = []
        xmaxs = []
        has_data = False

        for idx, item in enumerate(series):
            x = np.asarray(item["x"], dtype=float)
            y = np.asarray(item["y"], dtype=float)
            if x.size == 0 or y.size == 0:
                continue

            has_data = True
            xmins.append(float(np.nanmin(x)))
            xmaxs.append(float(np.nanmax(x)))

            label = item.get("label")
            if label is None and len(series) == 1:
                label = "Data"

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

            fit = plotter.compute_fit(x, y, p_cfg) if item.get("fit", p_cfg.get("fit", False)) else None
            if fit is not None:
                ax.plot(
                    x,
                    fit,
                    "--",
                    linewidth=2,
                    color=line.get_color(),
                    alpha=0.85,
                )

        refs = p_cfg.get("reference")
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

        ax.set_title(p_cfg["title"])
        ax.set_xlabel(p_cfg["x"].get("label", p_cfg["x"]["key"]), fontsize=11)
        ax.set_ylabel(p_cfg["y"].get("label", p_cfg["y"]["key"]), fontsize=11)

        if has_data and xmins and xmaxs:
            ax.set_xlim(min(xmins), max(xmaxs))

        ax.grid(True, linestyle="--", linewidth=0.5, alpha=0.7)
        ax.tick_params(labelsize=10)

        if ax.get_legend_handles_labels()[0]:
            ax.legend()

        fig.subplots_adjust(
            left=1.25 / 11,
            right=1 - 0.9 / 11,
            bottom=0.9 / 8.5,
            top=1 - 0.9 / 8.5,
        )

        return fig
