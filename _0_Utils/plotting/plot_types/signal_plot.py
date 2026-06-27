import numpy as np


class SignalPlot:
    def _apply_scale_offset(self, values, cfg):
        arr = np.asarray(values, dtype=float)
        arr = arr * cfg.get("scale", 1.0)
        arr = arr + cfg.get("offset", 0.0)
        return arr

    def _build_items(self, result, cfg, *, group_labels: bool = True):
        s = result["series"]

        x_cfg = cfg["x"]
        y_cfg = cfg["y"]

        x_raw = s[x_cfg["key"]]
        y_raw = s[y_cfg["key"]]
        default_style = cfg.get("style", "line")

        if isinstance(x_raw, dict) or isinstance(y_raw, dict):
            if not isinstance(x_raw, dict) or not isinstance(y_raw, dict):
                raise TypeError(
                    "Grouped plot data requires matching dicts for x and y."
                )

            def _sort_key(value):
                try:
                    return (0, float(value))
                except (TypeError, ValueError):
                    return (1, str(value))

            group_keys = sorted(set(x_raw) & set(y_raw), key=_sort_key)
            grouped = []
            for key in group_keys:
                if group_labels:
                    try:
                        label = f"V={float(key):g} m/s"
                    except (TypeError, ValueError):
                        label = str(key)
                else:
                    label = None

                grouped.append({
                    "label": label,
                    "x": self._apply_scale_offset(x_raw[key], x_cfg),
                    "y": self._apply_scale_offset(y_raw[key], y_cfg),
                    "style": default_style,
                    "fit": cfg.get("fit", False),
                    "alpha": cfg.get("alpha"),
                    "markersize": cfg.get("markersize"),
                    "color": cfg.get("color"),
                    "linewidth": cfg.get("linewidth"),
                    "linestyle": cfg.get("linestyle"),
                })
            return grouped

        return [{
            "label": None,
            "x": self._apply_scale_offset(x_raw, x_cfg),
            "y": self._apply_scale_offset(y_raw, y_cfg),
            "style": default_style,
            "fit": cfg.get("fit", False),
            "alpha": cfg.get("alpha"),
            "markersize": cfg.get("markersize"),
            "color": cfg.get("color"),
            "linewidth": cfg.get("linewidth"),
            "linestyle": cfg.get("linestyle"),
        }]

    def get_xy(self, result, p_cfg):
        items = self._build_items(result, p_cfg, group_labels=p_cfg.get("group_labels", True))

        overlay_cfg = p_cfg.get("overlay")
        if overlay_cfg:
            overlays = overlay_cfg if isinstance(overlay_cfg, list) else [overlay_cfg]
            for overlay in overlays:
                items.extend(
                    self._build_items(
                        result,
                        overlay,
                        group_labels=overlay.get("group_labels", False),
                    )
                )

        return items

    def compute_fit(self, x, y, p_cfg):
        if not p_cfg.get("fit", False):
            return None
        coeffs = np.polyfit(x, y, 1)
        return np.polyval(coeffs, x)
