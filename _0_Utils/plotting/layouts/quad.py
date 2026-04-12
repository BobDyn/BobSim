import matplotlib.pyplot as plt


class QuadLayout:
    def render(self, plotter, result, p_cfg):

        fig, axes = plt.subplots(2, 2, figsize=(11, 8.5))

        for ax, sub in zip(axes.flatten(), p_cfg["subplots"]):
            x, y = plotter.get_xy(result, sub)

            ax.plot(x, y)

            ax.set_title(sub["title"])
            ax.set_xlabel(sub["x"].get("label", sub["x"]["key"]))
            ax.set_ylabel(sub["y"].get("label", sub["y"]["key"]))
            ax.grid(True)

            xmin = result["series"]["ay_signed"].min()
            xmax = result["series"]["ay_signed"].max()

            ax.set_xlim(xmin, xmax)

        fig.suptitle(p_cfg.get("title", ""), fontsize=16, y=0.96)
        
        fig.subplots_adjust(
            left=1.25 / 11,
            right=1 - 0.9 / 11,
            bottom=0.9 / 8.5,
            top=1 - 0.9 / 8.5,
            hspace=0.4,
            wspace=0.3,
        )

        return fig