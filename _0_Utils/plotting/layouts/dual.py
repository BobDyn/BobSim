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

            # ============================================================
            # FIT
            # ============================================================
            fit = plotter.compute_fit(x, y, sub)
            if fit is not None:
                ax.plot(x, fit, "--", linewidth=2)

            # ============================================================
            # 🔥 REFERENCE LINES (NEW)
            # ============================================================
            refs = sub.get("reference")

            if refs:
                # allow single dict OR list
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
            ax.set_title(sub["title"], fontsize=12)
            ax.set_xlabel(sub["x"].get("label", sub["x"]["key"]), fontsize=11)
            ax.set_ylabel(sub["y"].get("label", sub["y"]["key"]), fontsize=11)
            ax.grid(True)

            # Only show legend if something requested it
            if ax.get_legend_handles_labels()[0]:
                ax.legend()

        fig.suptitle(p_cfg.get("title", ""), fontsize=16, y=0.96)

        fig.subplots_adjust(
            left=1.25 / 11,
            right=1 - 0.9 / 11,
            bottom=0.9 / 8.5,
            top=1 - 0.9 / 8.5,
            wspace=0.3,
        )

        return fig