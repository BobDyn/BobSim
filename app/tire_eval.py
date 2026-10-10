from __future__ import annotations

from collections.abc import Callable
import math
from pathlib import Path
from typing import Any

import yaml

from common.vehicle_io import parse_tir


def _num(values: dict[str, Any], key: str, default: float = 0.0) -> float:
    try:
        value = float(values.get(key, default))
    except (TypeError, ValueError):
        return default
    return value if math.isfinite(value) else default


def _sign(value: float) -> float:
    if value > 0.0:
        return 1.0
    if value < 0.0:
        return -1.0
    return 0.0


def _linspace(start: float, stop: float, count: int) -> list[float]:
    if count <= 1:
        return [start]
    step = (stop - start) / (count - 1)
    return [start + idx * step for idx in range(count)]


def _point(raw: Any) -> list[float] | None:
    if not isinstance(raw, list) or len(raw) < 3:
        return None
    try:
        point = [float(raw[0]), float(raw[1]), float(raw[2])]
    except (TypeError, ValueError):
        return None
    return point if all(math.isfinite(value) for value in point) else None


def _active_mass_records(vehicle: dict[str, Any]) -> list[tuple[float, list[float]]]:
    records: list[tuple[float, list[float]]] = []

    def add(raw_mass: Any, raw_cg: Any, *, mirror_y: float = 1.0) -> None:
        try:
            mass = float(raw_mass)
        except (TypeError, ValueError):
            return
        cg = _point(raw_cg)
        if cg is None or not math.isfinite(mass) or mass <= 0.0:
            return
        records.append((mass, [cg[0], cg[1] * mirror_y, cg[2]]))

    for key in ("sprung_mass", "driver_mass"):
        section = vehicle.get(key)
        if isinstance(section, dict):
            add(section.get("mass_kg"), section.get("cg_m"))

    for axle_name in ("front", "rear"):
        axle = vehicle.get(axle_name)
        if not isinstance(axle, dict):
            continue
        masses = axle.get("masses", {})
        if not isinstance(masses, dict):
            continue
        for side in (1.0, -1.0):
            for mass_section in masses.values():
                if isinstance(mass_section, dict):
                    add(mass_section.get("mass_kg"), mass_section.get("cg_m"), mirror_y=side)
    return records


def _active_static_tire_loads(vehicle: dict[str, Any]) -> dict[str, float]:
    summary = _active_static_load_summary(vehicle)
    loads = summary.get("per_tire_loads_n", {})
    return dict(loads) if isinstance(loads, dict) else {}


def _active_static_load_summary(vehicle: dict[str, Any]) -> dict[str, Any]:
    records = _active_mass_records(vehicle)
    if not records:
        return {}
    total_mass = sum(mass for mass, _ in records)
    if total_mass <= 0.0:
        return {}
    cg = [sum(mass * point[index] for mass, point in records) / total_mass for index in range(3)]
    front_wc = _point(vehicle.get("front", {}).get("suspension", {}).get("wheel_center_m"))
    rear_wc = _point(vehicle.get("rear", {}).get("suspension", {}).get("wheel_center_m"))
    if front_wc is None or rear_wc is None:
        return {}
    wheelbase = front_wc[0] - rear_wc[0]
    if abs(wheelbase) <= 1e-9:
        return {}
    front_fraction = max(0.0, min(1.0, (cg[0] - rear_wc[0]) / wheelbase))
    rear_fraction = 1.0 - front_fraction
    total_weight = total_mass * 9.80665
    front_load = total_weight * front_fraction / 2.0
    rear_load = total_weight * rear_fraction / 2.0
    return {
        "source": "total mass properties from vehicle.yml",
        "total_mass_kg": total_mass,
        "cg_m": cg,
        "wheelbase_m": abs(wheelbase),
        "front_static_frac": front_fraction,
        "rear_static_frac": rear_fraction,
        "per_tire_loads_n": {
            "front": front_load,
            "rear": rear_load,
        },
    }


def _tire_template_for_side(vehicle: dict[str, Any], side_name: str) -> str:
    aero = vehicle.get("aero", {})
    if isinstance(aero, dict) and aero.get("tire_template"):
        return str(aero["tire_template"])
    side = vehicle.get(side_name, {})
    if not isinstance(side, dict):
        return ""
    tire = side.get("tire", {})
    return str(tire.get("template", "")) if isinstance(tire, dict) else ""


def _safe_under_root(root: Path, raw_path: str | Path) -> Path:
    rel = Path(str(raw_path))
    candidate = rel.resolve() if rel.is_absolute() else (root / rel).resolve()
    if candidate != root and root not in candidate.parents:
        raise ValueError(f"Path escapes app root: {raw_path}")
    return candidate


def _tire_template_path(root: Path, vehicle: dict[str, Any], template: str) -> Path:
    paths = vehicle.get("paths", {})
    raw_root = "common/tire_templates"
    if isinstance(paths, dict) and paths.get("tire_templates"):
        raw_root = str(paths["tire_templates"])
    return _safe_under_root(root, Path(raw_root) / f"{template}.tir")


def _mf52_fx_pure(tire: dict[str, Any], fz: float, kappa: float, gamma: float) -> float:
    if fz <= 1e-3:
        return 0.0
    lfzo = _num(tire, "LFZO", 1.0)
    fznom = max(_num(tire, "FNOMIN", 1.0) * lfzo, 1e-8)
    ia_x = gamma * _num(tire, "LGAX", 1.0)
    dfz = (fz - fznom) / fznom
    mu_x = (
        (_num(tire, "PDX1") + _num(tire, "PDX2") * dfz)
        * (1 - _num(tire, "PDX3") * ia_x**2)
        * _num(tire, "LMUX", 1.0)
    )
    c = _num(tire, "PCX1", 1.0) * _num(tire, "LCX", 1.0)
    d = mu_x * fz
    k = (
        fz
        * (_num(tire, "PKX1") + _num(tire, "PKX2") * dfz)
        * math.exp(_num(tire, "PKX3") * dfz)
        * _num(tire, "LKX", 1.0)
    )
    b = k / (c * d + 1e-8)
    sh = (_num(tire, "PHX1") + _num(tire, "PHX2") * dfz) * _num(tire, "LHX", 1.0)
    sv = fz * (_num(tire, "PVX1") + _num(tire, "PVX2") * dfz) * _num(tire, "LVX", 1.0) * _num(tire, "LMUX", 1.0)
    slip = kappa + sh
    e = (_num(tire, "PEX1") + _num(tire, "PEX2") * dfz + _num(tire, "PEX3") * dfz**2)
    e *= (1 - _num(tire, "PEX4") * _sign(slip)) * _num(tire, "LEX", 1.0)
    e = min(e, 1.0)
    return d * math.sin(c * math.atan(b * slip - e * (b * slip - math.atan(b * slip)))) + sv


def _mf52_fy_pure(tire: dict[str, Any], fz: float, alpha: float, gamma: float) -> float:
    if fz <= 1e-3:
        return 0.0
    lfzo = _num(tire, "LFZO", 1.0)
    fznom_raw = max(_num(tire, "FNOMIN", 1.0), 1e-8)
    fznom = fznom_raw * lfzo
    ia_y = gamma * _num(tire, "LGAY", 1.0)
    dfz = (fz - fznom) / fznom
    mu_y = (
        (_num(tire, "PDY1") + _num(tire, "PDY2") * dfz)
        * (1 - _num(tire, "PDY3") * ia_y**2)
        * _num(tire, "LMUY", 1.0)
    )
    c = _num(tire, "PCY1", 1.0) * _num(tire, "LCY", 1.0)
    d = mu_y * fz
    pky2 = max(abs(_num(tire, "PKY2", 1.0)), 1e-8)
    k = (
        _num(tire, "PKY1")
        * fznom_raw
        * math.sin(2 * math.atan(fz / (pky2 * fznom)))
        * (1 - _num(tire, "PKY3") * abs(ia_y))
        * lfzo
        * _num(tire, "LKY", 1.0)
    )
    b = k / (c * d + 1e-8)
    sh = (_num(tire, "PHY1") + _num(tire, "PHY2") * dfz) * _num(tire, "LHY", 1.0) + _num(tire, "PHY3") * ia_y
    sv = fz * (
        (_num(tire, "PVY1") + _num(tire, "PVY2") * dfz) * _num(tire, "LVY", 1.0)
        + (_num(tire, "PVY3") + _num(tire, "PVY4") * dfz) * ia_y
    ) * _num(tire, "LMUY", 1.0)
    slip = alpha + sh
    e = (_num(tire, "PEY1") + _num(tire, "PEY2") * dfz)
    e *= (1 - (_num(tire, "PEY3") + _num(tire, "PEY4") * ia_y) * _sign(slip)) * _num(tire, "LEY", 1.0)
    e = min(e, 1.0)
    return d * math.sin(c * math.atan(b * slip - e * (b * slip - math.atan(b * slip)))) + sv


def _magic_cos_reduction(c: float, b: float, e: float, slip: float, shift: float) -> float:
    numerator = math.cos(c * math.atan(b * slip - e * (b * slip - math.atan(b * slip))))
    denominator = math.cos(c * math.atan(b * shift - e * (b * shift - math.atan(b * shift))))
    return numerator / denominator if abs(denominator) > 1e-8 else 1.0


def _mf52_fx_combined(tire: dict[str, Any], fz: float, kappa: float, alpha: float, gamma: float) -> float:
    if fz <= 1e-3:
        return 0.0
    fx_pure = _mf52_fx_pure(tire, fz, kappa, gamma)
    lfzo = _num(tire, "LFZO", 1.0)
    fznom = max(_num(tire, "FNOMIN", 1.0) * lfzo, 1e-8)
    dfz = (fz - fznom) / fznom
    c = _num(tire, "RCX1", 1.0)
    b = _num(tire, "RBX1") * math.cos(math.atan(_num(tire, "RBX2") * kappa)) * _num(tire, "LXAL", 1.0)
    e = _num(tire, "REX1") + _num(tire, "REX2") * dfz
    shift = _num(tire, "RHX1")
    return fx_pure * _magic_cos_reduction(c, b, e, alpha + shift, shift)


def _mf52_fy_combined(tire: dict[str, Any], fz: float, alpha: float, kappa: float, gamma: float) -> float:
    if fz <= 1e-3:
        return 0.0
    fy_pure = _mf52_fy_pure(tire, fz, alpha, gamma)
    lfzo = _num(tire, "LFZO", 1.0)
    fznom = max(_num(tire, "FNOMIN", 1.0) * lfzo, 1e-8)
    dfz = (fz - fznom) / fznom
    c = _num(tire, "RCY1", 1.0)
    b = _num(tire, "RBY1") * math.cos(math.atan(_num(tire, "RBY2") * (alpha - _num(tire, "RBY3"))))
    b *= _num(tire, "LYKA", 1.0)
    e = _num(tire, "REY1") + _num(tire, "REY2") * dfz
    shift = _num(tire, "RHY1") + _num(tire, "RHY2") * dfz
    ia_y = gamma * _num(tire, "LGAY", 1.0)
    d_v = (
        (_num(tire, "PDY1") + _num(tire, "PDY2") * dfz)
        * (1 - _num(tire, "PDY3") * ia_y**2)
        * _num(tire, "LMUY", 1.0)
        * fz
        * (_num(tire, "RVY1") + _num(tire, "RVY2") * dfz + _num(tire, "RVY3") * gamma)
        * math.cos(math.atan(_num(tire, "RVY4") * alpha))
    )
    s_v = d_v * math.sin(_num(tire, "RVY5") * math.atan(_num(tire, "RVY6") * kappa))
    s_v *= _num(tire, "LVYKA", 1.0)
    return fy_pure * _magic_cos_reduction(c, b, e, kappa + shift, shift) + s_v


def _tire_load_values(tire: dict[str, Any], fz_eval: float) -> list[float]:
    fz_min = _num(tire, "FZMIN", fz_eval)
    fz_max = _num(tire, "FZMAX", fz_eval)
    fz_nom = _num(tire, "FNOMIN", fz_eval)
    if fz_min <= 0.0:
        fz_min = min(fz_eval, fz_nom)
    if fz_max <= fz_min:
        fz_max = max(fz_eval, fz_nom, fz_min * 1.5)
    low = min(fz_min, fz_eval)
    high = max(fz_max, fz_eval)
    values = [value for value in _linspace(low, high, 5) if value > 0.0]
    values.append(fz_eval)
    values.append(fz_nom)
    return sorted({round(float(value), 6) for value in values})


def _mf52_curves(tire: dict[str, Any], fz: float, gamma: float) -> dict[str, Any]:
    fz_eval = max(fz, _num(tire, "FZMIN", 1.0))
    kappa_values = _linspace(_num(tire, "KPUMIN", -0.15), _num(tire, "KPUMAX", 0.15), 61)
    alpha_values = _linspace(_num(tire, "ALPMIN", -0.2617994), _num(tire, "ALPMAX", 0.2617994), 61)
    surface_kappa_values = _linspace(_num(tire, "KPUMIN", -0.15), _num(tire, "KPUMAX", 0.15), 31)
    surface_alpha_values = _linspace(_num(tire, "ALPMIN", -0.2617994), _num(tire, "ALPMAX", 0.2617994), 31)
    alpha_levels = [math.radians(value) for value in (-8.0, 0.0, 8.0)]
    kappa_levels = [-0.1, 0.0, 0.1]
    load_values = _tire_load_values(tire, fz_eval)
    gamma_values = sorted({
        *(math.radians(value) for value in (-8.0, -6.0, -4.0, -2.0, 0.0, 2.0, 4.0, 6.0, 8.0)),
        gamma,
    })
    fx = [
        {
            "kappa": value,
            "fz_n": fz_eval,
            "fx_n": _mf52_fx_pure(tire, fz_eval, value, gamma),
        }
        for value in kappa_values
    ]
    fy = [
        {
            "alpha_rad": value,
            "alpha_deg": math.degrees(value),
            "fz_n": fz_eval,
            "fy_n": -_mf52_fy_pure(tire, fz_eval, value, gamma),
        }
        for value in alpha_values
    ]

    def fx_load_surface_at_gamma(gamma_value: float) -> list[dict[str, Any]]:
        return [
            {
                "fz_n": load,
                "points": [
                    {
                        "kappa": kappa,
                        "fz_n": load,
                        "fx_n": _mf52_fx_pure(tire, load, kappa, gamma_value),
                    }
                    for kappa in kappa_values
                ],
            }
            for load in load_values
        ]

    def fy_load_surface_at_gamma(gamma_value: float) -> list[dict[str, Any]]:
        return [
            {
                "fz_n": load,
                "points": [
                    {
                        "alpha_rad": alpha,
                        "alpha_deg": math.degrees(alpha),
                        "fz_n": load,
                        "fy_n": -_mf52_fy_pure(tire, load, alpha, gamma_value),
                    }
                    for alpha in alpha_values
                ],
            }
            for load in load_values
        ]

    fx_by_fz = fx_load_surface_at_gamma(gamma)
    fy_by_fz = fy_load_surface_at_gamma(gamma)
    fx_by_gamma = [
        {
            "gamma_rad": value,
            "gamma_deg": math.degrees(value),
            "rows": fx_load_surface_at_gamma(value),
        }
        for value in gamma_values
    ]
    fy_by_gamma = [
        {
            "gamma_rad": value,
            "gamma_deg": math.degrees(value),
            "rows": fy_load_surface_at_gamma(value),
        }
        for value in gamma_values
    ]

    def fx_surface_at_load(load: float, gamma_value: float) -> list[dict[str, Any]]:
        return [
            {
                "alpha_rad": alpha,
                "alpha_deg": math.degrees(alpha),
                "points": [
                    {
                        "alpha_rad": alpha,
                        "alpha_deg": math.degrees(alpha),
                        "kappa": kappa,
                        "fz_n": load,
                        "fx_n": _mf52_fx_combined(tire, load, kappa, alpha, gamma_value),
                    }
                    for kappa in surface_kappa_values
                ],
            }
            for alpha in surface_alpha_values
        ]

    def fy_surface_at_load(load: float, gamma_value: float) -> list[dict[str, Any]]:
        return [
            {
                "kappa": kappa,
                "fz_n": load,
                "points": [
                    {
                        "alpha_rad": alpha,
                        "alpha_deg": math.degrees(alpha),
                        "kappa": kappa,
                        "fz_n": load,
                        "fy_n": -_mf52_fy_combined(tire, load, alpha, kappa, gamma_value),
                    }
                    for alpha in surface_alpha_values
                ],
            }
            for kappa in surface_kappa_values
        ]

    fx_surface = fx_surface_at_load(fz_eval, gamma)
    fy_surface = fy_surface_at_load(fz_eval, gamma)
    fx_surfaces_by_fz = [{"fz_n": load, "rows": fx_surface_at_load(load, gamma)} for load in load_values]
    fy_surfaces_by_fz = [{"fz_n": load, "rows": fy_surface_at_load(load, gamma)} for load in load_values]
    fz_nom = max(_num(tire, "FNOMIN", fz_eval), 1e-8)

    def force_map_at(load: float, gamma_value: float) -> list[dict[str, Any]]:
        return [
            {
                "alpha_rad": alpha,
                "alpha_deg": math.degrees(alpha),
                "fz_n": load,
                "points": [
                    {
                        "alpha_rad": alpha,
                        "alpha_deg": math.degrees(alpha),
                        "kappa": kappa,
                        "fz_n": load,
                        "fx_n": _mf52_fx_combined(tire, load, kappa, alpha, gamma_value),
                        "fy_n": -_mf52_fy_combined(tire, load, alpha, kappa, gamma_value),
                    }
                    for kappa in surface_kappa_values
                ],
            }
            for alpha in surface_alpha_values
        ]

    nominal_force_map = force_map_at(fz_nom, gamma)
    nominal_force_maps_by_gamma = [
        {
            "gamma_rad": value,
            "gamma_deg": math.degrees(value),
            "fz_n": fz_nom,
            "rows": force_map_at(fz_nom, value),
        }
        for value in gamma_values
    ]
    force_maps_by_gamma_fz = [
        {
            "gamma_rad": value,
            "gamma_deg": math.degrees(value),
            "maps": [
                {
                    "fz_n": load,
                    "rows": force_map_at(load, value),
                }
                for load in load_values
            ],
        }
        for value in gamma_values
    ]
    return {
        "pure": {
            "longitudinal": fx,
            "lateral": fy,
            "longitudinal_by_fz": fx_by_fz,
            "lateral_by_fz": fy_by_fz,
            "longitudinal_by_gamma": fx_by_gamma,
            "lateral_by_gamma": fy_by_gamma,
        },
        "longitudinal": fx,
        "lateral": fy,
        "combined": {
            "fx_by_alpha": [
                {
                    "alpha_rad": alpha,
                    "alpha_deg": math.degrees(alpha),
                    "points": [
                        {"kappa": kappa, "fx_n": _mf52_fx_combined(tire, fz_eval, kappa, alpha, gamma)}
                        for kappa in kappa_values
                    ],
                }
                for alpha in alpha_levels
            ],
            "fy_by_kappa": [
                {
                    "kappa": kappa,
                    "points": [
                        {
                            "alpha_rad": alpha,
                            "alpha_deg": math.degrees(alpha),
                            "fy_n": -_mf52_fy_combined(tire, fz_eval, alpha, kappa, gamma),
                        }
                        for alpha in alpha_values
                    ],
                }
                for kappa in kappa_levels
            ],
            "fx_surface": {
                "x_key": "kappa",
                "y_key": "alpha_deg",
                "z_key": "fx_n",
                "rows": fx_surface,
            },
            "fy_surface": {
                "x_key": "alpha_deg",
                "y_key": "kappa",
                "z_key": "fy_n",
                "rows": fy_surface,
            },
            "force_map_nominal": {
                "fz_n": fz_nom,
                "gamma_rad": gamma,
                "gamma_deg": math.degrees(gamma),
                "x_key": "fy_n",
                "y_key": "fx_n",
                "rows": nominal_force_map,
            },
            "force_maps_by_gamma": nominal_force_maps_by_gamma,
            "force_maps_by_gamma_fz": force_maps_by_gamma_fz,
            "fx_surfaces_by_fz": fx_surfaces_by_fz,
            "fy_surfaces_by_fz": fy_surfaces_by_fz,
        },
        "load_sensitivity": [
            {
                "fz_n": value,
                "mu_x": abs(_mf52_fx_pure(tire, value, _num(tire, "KPUMAX", 0.15), gamma)) / max(value, 1e-8),
                "mu_y": abs(_mf52_fy_pure(tire, value, _num(tire, "ALPMAX", 0.2617994), gamma)) / max(value, 1e-8),
            }
            for value in load_values
            if value > 0.0
        ],
    }


def tire_eval_payload(
    root: Path,
    vehicle: dict[str, Any] | None = None,
    *,
    load_vehicle_yaml_file: Callable[[Path], dict[str, Any]] | None = None,
) -> dict[str, Any]:
    if vehicle is None:
        vehicle_path = _safe_under_root(root, "vehicle.yml")
        if load_vehicle_yaml_file is None:
            with vehicle_path.open("r", encoding="utf-8", errors="replace") as handle:
                vehicle = yaml.safe_load(handle) or {}
            if not isinstance(vehicle, dict):
                raise TypeError(f"Expected vehicle YAML mapping at {vehicle_path}")
        else:
            vehicle = load_vehicle_yaml_file(vehicle_path)
    load_summary = _active_static_load_summary(vehicle)
    static_loads = dict(load_summary.get("per_tire_loads_n", {}))
    sides = []
    for side_name in ("front", "rear"):
        template = _tire_template_for_side(vehicle, side_name)
        if not template:
            continue
        path = _tire_template_path(root, vehicle, template)
        tire = parse_tir(path)
        side = vehicle.get(side_name, {})
        wheel = side.get("wheel", {}) if isinstance(side, dict) else {}
        camber_deg = float(wheel.get("camber_deg", 0.0)) if isinstance(wheel, dict) else 0.0
        fz = static_loads.get(side_name, _num(tire, "FNOMIN", 1.0))
        sides.append(
            {
                "side": side_name,
                "template": template,
                "path": path.relative_to(root).as_posix(),
                "fz_n": fz,
                "camber_deg": camber_deg,
                "metadata": {
                    "fznom_n": _num(tire, "FNOMIN"),
                    "fzmin_n": _num(tire, "FZMIN"),
                    "fzmax_n": _num(tire, "FZMAX"),
                    "pressure_pa": _num(tire, "IP_NOM"),
                    "unloaded_radius_m": _num(tire, "UNLOADED_RADIUS"),
                    "width_m": _num(tire, "WIDTH"),
                    "longvl_mps": _num(tire, "LONGVL"),
                    "pdx1": _num(tire, "PDX1"),
                    "pdy1": _num(tire, "PDY1"),
                    "camber_thrust": {
                        "enabled": any(
                            abs(_num(tire, key)) > 1e-12
                            for key in ("PHY3", "PVY3", "PVY4", "RVY3")
                        ),
                        "phy3": _num(tire, "PHY3"),
                        "pvy3": _num(tire, "PVY3"),
                        "pvy4": _num(tire, "PVY4"),
                        "rvy3": _num(tire, "RVY3"),
                        "pdy3": _num(tire, "PDY3"),
                        "pky3": _num(tire, "PKY3"),
                        "lgay": _num(tire, "LGAY", 1.0),
                    },
                },
                "curves": _mf52_curves(tire, fz, math.radians(camber_deg)),
            }
        )
    return {
        "model": "BobLib MF52 pure-slip equations from active .tir coefficients",
        "load_summary": load_summary,
        "sides": sides,
    }

