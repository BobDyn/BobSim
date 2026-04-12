import matplotlib.pyplot as plt


class SingleLayout:
    def render(self, plotter, result, p_cfg):

        fig, ax = plt.subplots()

        x, y = plotter.get_xy(result, p_cfg)

        ax.plot(x, y, 'o', label="Data")

        fit = plotter.compute_fit(x, y, p_cfg)
        if fit is not None:
            ax.plot(x, fit, '--', label="Fit")

        ax.set_title(p_cfg["title"])
        ax.set_xlabel(p_cfg["x"].get("label", p_cfg["x"]["key"]))
        ax.set_ylabel(p_cfg["y"].get("label", p_cfg["y"]["key"]))
        ax.grid(True)
        ax.legend()

        fig.subplots_adjust(
            left=1.25 / 11,
            right=1 - 0.9 / 11,
            bottom=0.9 / 8.5,
            top=1 - 0.9 / 8.5,
            hspace=0.4,
            wspace=0.3,
        )

        return fig