import matplotlib.pyplot as plt


class SingleLayout:
    def render(self, plotter, result, p_cfg):

        fig, ax = plt.subplots(figsize=(11, 8.5))

        x, y = plotter.get_xy(result, p_cfg)

        xscale = p_cfg.get("xscale", "linear")
        yscale = p_cfg.get("yscale", "linear")
        ax.set_xscale(xscale)
        ax.set_yscale(yscale)

        style = p_cfg.get("style", "line")

        if style == "line":
            ax.plot(x, y, "-", linewidth=2, label="Data")
        elif style == "scatter":
            ax.plot(x, y, "o", label="Data")
        else:
            ax.plot(x, y, linewidth=2, label="Data")

        fit = plotter.compute_fit(x, y, p_cfg)
        if fit is not None:
            ax.plot(x, fit, "--", linewidth=2, label="Fit")

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