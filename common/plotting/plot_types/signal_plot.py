import numpy as np


DEFAULT_PLOT_ABS_LIMIT = 1e9


class SignalPlot:
    def _apply_scale_offset(self, values, cfg):
        arr = np.asarray(values, dtype=float).reshape(-1)
        arr = arr * cfg.get("scale", 1.0)
        arr = arr + cfg.get("offset", 0.0)
        return arr

    def _clean_xy(self, x, y, cfg):
        x = np.asarray(x, dtype=float).reshape(-1)
        y = np.asarray(y, dtype=float).reshape(-1)
        size = min(x.size, y.size)
        if size <= 0:
            return np.array([], dtype=float), np.array([], dtype=float)

        x = x[:size]
        y = y[:size]
        limit = float(cfg.get("max_abs", DEFAULT_PLOT_ABS_LIMIT))
        x_limit = float(cfg.get("x", {}).get("max_abs", limit))
        y_limit = float(cfg.get("y", {}).get("max_abs", limit))
        mask = (
            np.isfinite(x)
            & np.isfinite(y)
            & (np.abs(x) <= x_limit)
            & (np.abs(y) <= y_limit)
        )
        return x[mask], y[mask]

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

                x, y = self._clean_xy(
                    self._apply_scale_offset(x_raw[key], x_cfg),
                    self._apply_scale_offset(y_raw[key], y_cfg),
                    cfg,
                )

                grouped.append({
                    "label": label,
                    "group": key,
                    "x": x,
                    "y": y,
                    "style": default_style,
                    "fit": cfg.get("fit", False),
                    "alpha": cfg.get("alpha"),
                    "markersize": cfg.get("markersize"),
                    "color": cfg.get("color"),
                    "linewidth": cfg.get("linewidth"),
                    "linestyle": cfg.get("linestyle"),
                    "match_color": cfg.get("match_color", False),
                })
            return grouped

        x, y = self._clean_xy(
            self._apply_scale_offset(x_raw, x_cfg),
            self._apply_scale_offset(y_raw, y_cfg),
            cfg,
        )

        return [{
            "label": cfg.get("label"),
            "group": None,
            "x": x,
            "y": y,
            "style": default_style,
            "fit": cfg.get("fit", False),
            "alpha": cfg.get("alpha"),
            "markersize": cfg.get("markersize"),
            "color": cfg.get("color"),
            "linewidth": cfg.get("linewidth"),
            "linestyle": cfg.get("linestyle"),
            "match_color": cfg.get("match_color", False),
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
        x, y = self._clean_xy(x, y, p_cfg)
        if x.size < 2 or y.size < 2 or np.nanstd(x) < 1e-12:
            return None
        coeffs = np.polyfit(x, y, 1)
        return np.polyval(coeffs, x)
