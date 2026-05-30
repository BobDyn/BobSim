"""sampler.py — Read baseline car + DOE config, generate DOE variant dicts."""

from collections.abc import Iterable
from itertools import product
from pathlib import Path

import yaml
from scipy.stats.qmc import LatinHypercube

from StandardSens.pipeline.modelica_params import read_value


def load_config(config_path: str | Path) -> dict:
    with open(config_path) as f:
        return yaml.safe_load(f)


def read_baseline(mo_path: str | Path, variables: list[dict]) -> dict[str, float]:
    text = Path(mo_path).read_text()
    baseline: dict[str, float] = {}
    for var in variables:
        try:
            if "baseline" in var:
                baseline[var["path"]] = float(var["baseline"])
            elif "targets" in var:
                first = var["targets"][0]
                scale = float(first.get("scale", 1.0))
                baseline[var["path"]] = read_value(text, first) / scale
            else:
                scale = float(var.get("scale", 1.0))
                baseline[var["path"]] = read_value(text, var) / scale
        except Exception as e:
            raise ValueError(
                f"Could not read baseline for {var['path']!r} in {mo_path}: {e}"
            ) from e
    return baseline


def _linspace(lo: float, hi: float, intervals: int) -> Iterable[float]:
    if intervals < 1:
        raise ValueError("intervals must be >= 1")
    for i in range(intervals + 1):
        yield lo + (hi - lo) * i / intervals


def _sample_lhs(
    variables: list[dict],
    baseline: dict[str, float],
    n_samples: int,
    seed: int | None,
) -> list[dict[str, float]]:
    lhs = LatinHypercube(d=len(variables), seed=seed)
    unit_samples = lhs.random(n=n_samples)

    variants: list[dict[str, float]] = [baseline.copy()]
    for row in unit_samples:
        variant: dict[str, float] = {}
        for j, var in enumerate(variables):
            lo, hi = var["range"]
            variant[var["path"]] = lo + row[j] * (hi - lo)
        variants.append(variant)

    return variants


def _sample_interval_splice(
    variables: list[dict],
    baseline: dict[str, float],
    default_intervals: int,
) -> list[dict[str, float]]:
    """Generate one-factor-at-a-time interval perturbations around baseline."""
    variants: list[dict[str, float]] = [baseline.copy()]

    for var in variables:
        path = var["path"]
        lo, hi = var["range"]
        intervals = int(var.get("intervals", default_intervals))
        baseline_value = baseline[path]
        values = var.get("values")

        interval_values = values if values is not None else _linspace(float(lo), float(hi), intervals)
        for value in interval_values:
            if abs(value - baseline_value) <= 1e-12:
                continue
            variant = baseline.copy()
            variant[path] = float(value)
            variants.append(variant)

    return variants


def _grid_values(var: dict, baseline_value: float, grid_levels: int) -> list[float]:
    values = var.get("values")
    if values is None:
        lo, hi = var["range"]
        values = list(_linspace(float(lo), float(hi), grid_levels - 1))

    levels = [float(value) for value in values]
    if not any(abs(value - baseline_value) <= 1e-12 for value in levels):
        levels.append(float(baseline_value))
    return sorted(set(levels))


def _variant_key(variant: dict[str, float], variables: list[dict]) -> tuple[float, ...]:
    return tuple(round(float(variant[var["path"]]), 12) for var in variables)


def _sample_response_surface_pairs(
    variables: list[dict],
    baseline: dict[str, float],
    sampling_cfg: dict,
) -> list[dict[str, float]]:
    """Generate full-factorial 2D grids for metric-selected variable pairs."""
    pairs = sampling_cfg.get("pairs", [])
    if not isinstance(pairs, list) or not pairs:
        raise ValueError("response_surface_pairs sampling requires a non-empty pairs list")

    grid_levels = int(sampling_cfg.get("grid_levels", sampling_cfg.get("levels", 5)))
    if grid_levels < 2:
        raise ValueError("response_surface_pairs grid_levels must be >= 2")

    variables_by_path = {var["path"]: var for var in variables}
    variants: list[dict[str, float]] = [baseline.copy()]
    seen = {_variant_key(baseline, variables)}

    for pair in pairs:
        paths = pair.get("variables", pair.get("inputs"))
        if not isinstance(paths, list) or len(paths) != 2:
            raise ValueError(
                "Each response_surface_pairs entry must define exactly two variables"
            )

        for path in paths:
            if path not in variables_by_path:
                raise KeyError(f"Response-surface variable {path!r} is not in variables")

        x_path, y_path = paths
        x_values = _grid_values(variables_by_path[x_path], baseline[x_path], grid_levels)
        y_values = _grid_values(variables_by_path[y_path], baseline[y_path], grid_levels)

        for x_value, y_value in product(x_values, y_values):
            variant = baseline.copy()
            variant[x_path] = float(x_value)
            variant[y_path] = float(y_value)

            key = _variant_key(variant, variables)
            if key in seen:
                continue

            seen.add(key)
            variants.append(variant)

    return variants


def sample(config_path: str | Path) -> list[dict[str, float]]:
    cfg = load_config(config_path)
    variables = cfg["variables"]
    seed = cfg.get("seed")
    sampling_cfg = cfg.get("sampling", {})
    if sampling_cfg is None:
        sampling_cfg = {}
    if not isinstance(sampling_cfg, dict):
        raise TypeError("sampling must be a mapping when provided")
    method = sampling_cfg.get("method", "lhs")

    # Resolve mo_path relative to the config file
    config_dir = Path(config_path).resolve().parent
    mo_path = (config_dir / cfg["baseline_mo"]).resolve()

    if not mo_path.exists():
        raise FileNotFoundError(
            f"baseline_mo not found at {mo_path}. "
            f"Check _doe_config.yaml and ensure submodules are initialized."
        )

    baseline = read_baseline(mo_path, variables)

    if method == "lhs":
        return _sample_lhs(
            variables,
            baseline,
            int(cfg.get("samples", 3)),
            seed,
        )
    if method == "interval_splice":
        return _sample_interval_splice(
            variables,
            baseline,
            int(sampling_cfg.get("intervals", cfg.get("intervals", 2))),
        )
    if method == "response_surface_pairs":
        return _sample_response_surface_pairs(
            variables,
            baseline,
            sampling_cfg,
        )

    raise ValueError(f"Unsupported DOE sampling method: {method!r}")


if __name__ == "__main__":
    import sys

    cfg_path = sys.argv[1] if len(sys.argv) > 1 else (
        Path(__file__).resolve().parent.parent / "configs/_doe_config.yaml"
    )
    variants = sample(cfg_path)
    print(f"Generated {len(variants)} variants ({len(variants) - 1} sampled + 1 baseline)")
    print(f"Baseline: {variants[0]}")
    print(f"Sample 1: {variants[1]}")
