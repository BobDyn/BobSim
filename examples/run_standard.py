import sys

from _2_GeneralSim.config import load_config
from _3_StandardSim.registry import STANDARD_REGISTRY
from _0_Utils.reporting.report_engine import ReportEngine

import matplotlib as mpl

mpl.rcParams.update({

    # --- Font system ---
    "font.family": "STIXGeneral",
    "mathtext.fontset": "stix",

    # --- Global sizes ---
    "font.size": 12,

    # --- Axes ---
    "axes.titlesize": 13,
    "axes.labelsize": 12,

    # --- Ticks ---
    "xtick.labelsize": 10,
    "ytick.labelsize": 10,

    # --- Legend ---
    "legend.fontsize": 10,

    # --- Grid ---
    "axes.grid": True,
    "grid.linestyle": "--",
    "grid.alpha": 0.4,
})


def main(path):

    config = load_config(path)

    sim = STANDARD_REGISTRY[config["standard"]](config)

    result = sim.run()

    ReportEngine(config).build(result)

    print(result["summary"])


if __name__ == "__main__":
    main(sys.argv[1])