"""sampler.py — Read baseline car + DOE config, generate DOE variant dicts."""

from collections.abc import Iterable
from pathlib import Path

import yaml
from scipy.stats.qmc import LatinHypercube

from pipeline.modelica_params import read_value


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
