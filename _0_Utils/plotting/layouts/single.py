import matplotlib.pyplot as plt


class SingleLayout:
    def render(self, plotter, result, p_cfg):

        fig, ax = plt.subplots(figsize=(11, 8.5))

        x, y = plotter.get_xy(result, p_cfg)

        # ============================================================
        # DATA
        # ============================================================
        style = p_cfg.get("style", "line")

        if style == "line":
            ax.plot(x, y, "-", linewidth=2, label="Data")
        elif style == "scatter":
            ax.plot(x, y, "o", label="Data")
        else:
            ax.plot(x, y, label="Data")

        # ============================================================
        # FIT
        # ============================================================
        fit = plotter.compute_fit(x, y, p_cfg)
        if fit is not None:
            ax.plot(x, fit, "--", linewidth=2, label="Fit")

        # ============================================================
        # 🔥 REFERENCE LINES (NEW)
        # ============================================================
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

        # ============================================================
        # AXIS FORMATTING
        # ============================================================
        ax.set_title(p_cfg["title"])
        ax.set_xlabel(p_cfg["x"].get("label", p_cfg["x"]["key"]), fontsize=11)
        ax.set_ylabel(p_cfg["y"].get("label", p_cfg["y"]["key"]), fontsize=11)
        ax.grid(True)

        # Only show legend if needed
        handles, labels = ax.get_legend_handles_labels()
        if handles:
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