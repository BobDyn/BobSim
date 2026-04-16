import numpy as np


class SignalPlot:
    def get_xy(self, result, p_cfg):
        s = result["series"]

        x_cfg = p_cfg["x"]
        y_cfg = p_cfg["y"]

        x = s[x_cfg["key"]]
        y = s[y_cfg["key"]]

        # Scaling
        x = x * x_cfg.get("scale", 1.0)
        y = y * y_cfg.get("scale", 1.0)

        # Optional offset
        x = x + x_cfg.get("offset", 0.0)
        y = y + y_cfg.get("offset", 0.0)

        return x, y

    def compute_fit(self, x, y, p_cfg):
        if not p_cfg.get("fit", False):
            return None
        coeffs = np.polyfit(x, y, 1)
        return np.polyval(coeffs, x)