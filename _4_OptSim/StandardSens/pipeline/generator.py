"""generator.py — Take sampled variant dicts and write one variant.mo each."""

import csv
import math
from pathlib import Path
from typing import Any

import yaml

from StandardSens.pipeline.modelica_params import replace_value, scale_value

REPO_ROOT = Path(__file__).resolve().parents[3]
FOUR_POST_METRICS_CSV = REPO_ROOT / "_3_StandardSim/results/four_post_eval_report_metrics.csv"


def load_config(config_path: str | Path) -> dict:
    with open(config_path) as f:
        return yaml.safe_load(f)


def _load_metrics_csv(path: Path) -> dict[str, float]:
    if not path.exists():
        raise FileNotFoundError(
            "Static balance free length requires FourPostEval metrics. "
            f"Run FourPostEval first or provide the metrics file: {path}"
        )

    metrics: dict[str, float] = {}
    with path.open(newline="", encoding="utf-8") as f:
        for row in csv.DictReader(f):
            metric = row.get("metric")
            value = row.get("value")
            if not metric:
                continue
            try:
                metrics[metric] = float(value or "nan")
            except ValueError:
                metrics[metric] = float("nan")
    return metrics


def _computed_motion_ratio(axle: str, context: dict[str, Any]) -> float:
    metrics = context["four_post_metrics"]
    for metric in (f"static_motion_ratio_{axle}", f"avg_motion_ratio_{axle}"):
        value = float(metrics.get(metric, float("nan")))
        if math.isfinite(value) and abs(value) > 1e-12:
            return value
    raise ValueError(
        "Static balance free length requires a computed FourPostEval motion "
        f"ratio metric for axle {axle!r}."
    )


def _vector(values: Any) -> tuple[float, float, float]:
    items = tuple(float(value) for value in values)
    if len(items) != 3:
        raise ValueError(f"Expected a 3-vector, got {values!r}")
    return items


def _combined_sprung_mass(vehicle: dict[str, Any]) -> tuple[float, tuple[float, float, float]]:
    sprung = vehicle["sprung_mass"]
    masses = [(float(sprung["mass_kg"]), _vector(sprung["cg_m"]))]
    driver = vehicle.get("driver_mass")
    if isinstance(driver, dict):
        masses.append((float(driver["mass_kg"]), _vector(driver["cg_m"])))

    total_mass = sum(mass for mass, _cg in masses)
    if total_mass <= 0.0:
        raise ValueError("Combined sprung mass must be positive.")

    return total_mass, tuple(
        sum(mass * cg[i] for mass, cg in masses) / total_mass
        for i in range(3)
    )


def _distance(a: tuple[float, float, float], b: tuple[float, float, float]) -> float:
    return math.sqrt(sum((av - bv) ** 2 for av, bv in zip(a, b, strict=True)))


def _side_installed_spring_length(side: dict[str, Any]) -> float:
    actuation = side["actuation"]
    shock_mount = _vector(actuation["shock"]["mount_m"])
    bellcrank = actuation.get("bellcrank")
    if isinstance(bellcrank, dict):
        shock_pickup = _vector(bellcrank["pickups_m"]["shock"])
        return _distance(shock_mount, shock_pickup)

    return _distance(shock_mount, _vector(actuation["rod_mount_m"]))


def _sprung_corner_loads(vehicle: dict[str, Any]) -> dict[str, float]:
    sprung_mass_kg, sprung_cg_m = _combined_sprung_mass(vehicle)
    front_wc = _vector(vehicle["front"]["suspension"]["wheel_center_m"])
    rear_wc = _vector(vehicle["rear"]["suspension"]["wheel_center_m"])

    wheelbase = abs(front_wc[0] - rear_wc[0])
    if wheelbase <= 0.0:
        raise ValueError("Vehicle wheelbase must be positive.")

    left_y = 0.5 * (front_wc[1] + rear_wc[1])
    right_y = -left_y
    if abs(left_y - right_y) <= 1e-12:
        raise ValueError("Vehicle track width must be positive.")

    front_fraction = (sprung_cg_m[0] - rear_wc[0]) / (front_wc[0] - rear_wc[0])
    rear_fraction = 1.0 - front_fraction
    left_fraction = (sprung_cg_m[1] - right_y) / (left_y - right_y)
    right_fraction = 1.0 - left_fraction

    gravity = 9.80665
    return {
        "front": 0.5
        * sprung_mass_kg
        * front_fraction
        * (left_fraction + right_fraction)
        * gravity,
        "rear": 0.5
        * sprung_mass_kg
        * rear_fraction
        * (left_fraction + right_fraction)
        * gravity,
    }


def _static_balance_free_length(
    spring_rate_n_per_m: float,
    target: dict[str, Any],
    context: dict[str, Any],
) -> float:
    axle = str(target["axle"])
    vehicle = context["vehicle"]
    motion_ratio = _computed_motion_ratio(axle, context)
    spring_rate = float(spring_rate_n_per_m)
    if spring_rate <= 0.0:
        raise ValueError("Spring rate must be positive for static balance free length.")

    installed_length = _side_installed_spring_length(vehicle[axle])
    sprung_corner_load = _sprung_corner_loads(vehicle)[axle]
    spring_force = sprung_corner_load * motion_ratio
    return installed_length + spring_force / spring_rate


def substitute_param(text: str, block: str, param: str, value: float) -> str:
    # Find block name in text
    block_start = text.find(block)
    if block_start == -1:
        raise ValueError(f"Block '{block}' not found in record")

    # Find the opening paren of this block
    paren_open = text.find("(", block_start)
    if paren_open == -1:
        raise ValueError(f"No opening paren found for block '{block}'")

    # Walk to find the matching closing paren, tracking depth
    depth = 1
    i = paren_open + 1
    n = len(text)
    while i < n and depth > 0:
        if text[i] in "({":
            depth += 1
        elif text[i] in ")}":
            depth -= 1
        i += 1
    paren_close = i - 1  # position of closing paren

    block_body = text[paren_open + 1: paren_close]

    # Find param inside block body
    param_start = block_body.find(param)
    if param_start == -1:
        raise ValueError(f"Param '{param}' not found in block '{block}'")

    # Find the '=' after param name
    eq_pos = block_body.find("=", param_start)
    if eq_pos == -1:
        raise ValueError(f"No '=' found after param '{param}'")

    # Walk past whitespace to find value start
    val_start = eq_pos + 1
    while val_start < len(block_body) and block_body[val_start] in " \t\n\r":
        val_start += 1

    # Walk to find value end (stops at comma or closing paren)
    val_end = val_start
    while val_end < len(block_body) and block_body[val_end] not in ",)":
        val_end += 1

    # Splice new value into block body
    new_body = (
            block_body[:val_start]
            + str(value)
            + block_body[val_end:]
    )

    # Splice new block body back into full text
    return text[: paren_open + 1] + new_body + text[paren_close:]


def substitute_variable(
    text: str,
    spec: dict,
    value: float,
    context: dict[str, Any] | None = None,
) -> str:
    """Patch a variable using the extended DOE spec.

    Falls back to the original scalar block/param behavior for old configs.
    """
    if "targets" in spec:
        for target in spec["targets"]:
            target_value = value
            if target.get("operation") == "static_balance_free_length":
                if context is None:
                    raise ValueError("static_balance_free_length requires generator context")
                target_value = _static_balance_free_length(value, target, context)
            elif "range" in target:
                src_lo, src_hi = spec["range"]
                dst_lo, dst_hi = target["range"]
                if src_hi == src_lo:
                    raise ValueError(f"Cannot map zero-width range for {spec['path']}")
                fraction = (value - src_lo) / (src_hi - src_lo)
                target_value = dst_lo + fraction * (dst_hi - dst_lo)
            target_value *= float(target.get("scale", 1.0))
            if target.get("operation") == "scale":
                text = scale_value(text, target, target_value)
            else:
                text = replace_value(text, target, target_value)
        return text
    return replace_value(text, spec, value * float(spec.get("scale", 1.0)))


def generate_variants(
        config_path: str | Path,
        variants: list[dict[str, float]],
        population_dir: str | Path,
) -> list[Path]:
    """Write one variant.mo per variant dict into population_dir/variant_N/."""

    config_path = Path(config_path).resolve()
    population_dir = Path(population_dir).resolve()
    cfg = load_config(config_path)

    # Resolve base record relative to config file
    config_dir = config_path.parent
    mo_path = (config_dir / cfg["baseline_mo"]).resolve()
    base_text = mo_path.read_text()
    template_path = (config_path.parents[1] / cfg["architecture"]["template"]).resolve()
    vehicle = load_config(template_path)
    context = {
        "vehicle": vehicle,
        "four_post_metrics": _load_metrics_csv(FOUR_POST_METRICS_CSV),
    }

    var_lookup = {var["path"]: var for var in cfg["variables"]}

    written: list[Path] = []

    for i, variant in enumerate(variants):
        variant_dir = population_dir / f"variant_{i:04d}"
        variant_dir.mkdir(parents=True, exist_ok=True)

        text = base_text
        for path, value in variant.items():
            if path not in var_lookup:
                raise KeyError(f"Path '{path}' not in config variables")
            text = substitute_variable(text, var_lookup[path], value, context)

        out_path = variant_dir / "variant.mo"
        out_path.write_text(text)
        written.append(out_path)

    print(f"Generated {len(written)} variants in {population_dir}")
    return written


if __name__ == "__main__":
    from StandardSens.pipeline.sampler import sample

    standard_dir = Path(__file__).resolve().parents[1]
    optsim_dir = standard_dir.parent
    config = standard_dir / "configs/_doe_config.yaml"
    population = optsim_dir / "Build" / "StandardSens" / "population"

    variants = sample(config)
    generate_variants(config, variants, population)
