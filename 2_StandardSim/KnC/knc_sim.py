# StandardSim/KnC/KnCSim.py

from pathlib import Path
import numpy as np

from GeneralSim.general_sim import GeneralSim
from StandardSim.KnC.knc_schema import KNC_SCHEMA


class KnCSim:
    def __init__(self, config):
        self.config = config

        base = Path(__file__).parent / "build"

        self.sim_fr = GeneralSim(
            build_dir=base / "fr_build",
            exec_name="BobLib.Standards.FrKnC",
            simulation=config.get("simulation", {}),
        )

        self.sim_rr = GeneralSim(
            build_dir=base / "rr_build",
            exec_name="BobLib.Standards.RrKnC",
            simulation=config.get("simulation", {}),
        )

    # ============================================================
    # OVERRIDES (matches Modelica parameters)
    # ============================================================
    def build_overrides(self):

        p = self.config["test"]

        return {
            "steerMagnitude": p["steerMagnitude"],
            "heaveMagnitude": p["heaveMagnitude"],
            "rollMagnitude": p["rollMagnitude"],
            "forceMagnitude": p["forceMagnitude"],
        }

    # ============================================================
    # RUN
    # ============================================================
    def run(self):

        overrides = self.build_overrides()

        fr = self.sim_fr.run(
            schema=KNC_SCHEMA,
            overrides=overrides,
        )

        rr = self.sim_rr.run(
            schema=KNC_SCHEMA,
            overrides=overrides,
        )

        return self.summarize(fr, rr)

    # ============================================================
    # SUMMARIZE (IDENTICAL INTERFACE TO ISO4138)
    # ============================================================
    def summarize(self, fr, rr):

        # =========================
        # TIME
        # =========================
        t = np.array(fr["time"])

        # ensure consistency
        assert np.allclose(fr["time"], rr["time"])

        # =========================
        # INPUTS
        # =========================
        heave = np.array(fr["knc.heave"])
        roll  = np.array(fr["knc.roll"])
        fy    = np.array(fr["knc.fy"])

        # =========================
        # FRONT
        # =========================
        fr_left_gamma  = np.array(fr["knc.left.gamma"])
        fr_right_gamma = np.array(fr["knc.right.gamma"])

        fr_left_toe  = np.array(fr["knc.left.toe"])
        fr_right_toe = np.array(fr["knc.right.toe"])

        # =========================
        # REAR
        # =========================
        rr_left_gamma  = np.array(rr["knc.left.gamma"])
        rr_right_gamma = np.array(rr["knc.right.gamma"])

        rr_left_toe  = np.array(rr["knc.left.toe"])
        rr_right_toe = np.array(rr["knc.right.toe"])

        # =========================
        # METRICS
        # =========================
        gamma_range = (
            float(fr_left_gamma.min()),
            float(fr_left_gamma.max()),
        )

        toe_range = (
            float(fr_left_toe.min()),
            float(fr_left_toe.max()),
        )

        # =========================
        # RETURN (STANDARD FORMAT)
        # =========================
        return {
            "summary": {
                "time_span": (float(t.min()), float(t.max())),
                "gamma_range": gamma_range,
                "toe_range": toe_range,
            },

            "series": {
                "time": t,

                "heave": heave,
                "roll": roll,
                "fy": fy,

                # FRONT
                "fr_left_gamma": fr_left_gamma,
                "fr_right_gamma": fr_right_gamma,
                "fr_left_toe": fr_left_toe,
                "fr_right_toe": fr_right_toe,

                # REAR
                "rr_left_gamma": rr_left_gamma,
                "rr_right_gamma": rr_right_gamma,
                "rr_left_toe": rr_left_toe,
                "rr_right_toe": rr_right_toe,
            }
        }