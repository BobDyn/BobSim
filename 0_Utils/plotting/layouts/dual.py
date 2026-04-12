import matplotlib.pyplot as plt


class DualLayout:
    def render(self, plotter, result, p_cfg):

        fig, axes = plt.subplots(1, 2, figsize=(11, 8.5))

        for ax, sub in zip(axes, p_cfg["subplots"]):
            x, y = plotter.get_xy(result, sub)

            style = sub.get("style", "line")

            if style == "line":
                ax.plot(x, y, "-", linewidth=2)
            elif style == "scatter":
                ax.plot(x, y, "o")
            else:
                ax.plot(x, y)

            fit = plotter.compute_fit(x, y, sub)
            if fit is not None:
                ax.plot(x, fit, "--", linewidth=2)

            ax.set_title(sub["title"], fontsize=12)
            ax.set_xlabel(sub["x"].get("label", sub["x"]["key"]))
            ax.set_ylabel(sub["y"].get("label", sub["y"]["key"]))
            ax.grid(True)

        fig.suptitle(p_cfg.get("title", ""), fontsize=16, y=0.96)

        fig.subplots_adjust(
            left=1.25 / 11,
            right=1 - 0.9 / 11,
            bottom=0.9 / 8.5,
            top=1 - 0.9 / 8.5,
            wspace=0.3,
        )

        return fig