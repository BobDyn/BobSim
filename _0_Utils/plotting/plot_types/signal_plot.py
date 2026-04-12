import numpy as np


class SignalPlot:
    def get_xy(self, result, p_cfg):
        s = result["series"]
        return s[p_cfg["x"]["key"]], s[p_cfg["y"]["key"]]

    def compute_fit(self, x, y, p_cfg):
        if not p_cfg.get("fit", False):
            return None
        coeffs = np.polyfit(x, y, 1)
        return np.polyval(coeffs, x)