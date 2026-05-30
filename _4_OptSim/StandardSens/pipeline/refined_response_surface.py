"""Build refined response-surface DOE configs from sensitivity results."""

from __future__ import annotations

from collections.abc import Iterable
from copy import deepcopy
import fnmatch
import os
from pathlib import Path
import shutil
from typing import Any

import numpy as np
import pandas as pd
import yaml

from StandardSens.pipeline.generator import generate_variants
from StandardSens.pipeline.sampler import sample


STANDARD_DIR = Path(__file__).resolve().parents[1]
OPTSIM_DIR = STANDARD_DIR.parent
OPTSIM_RESULTS_DIR = OPTSIM_DIR / "results"
STANDARD_BUILD_DIR = OPTSIM_DIR / "Build" / "StandardSens"
DEFAULT_BASE_DOE_CONFIG = STANDARD_DIR / "configs/_doe_config.yaml"
DEFAULT_REFINED_BUILD_DIR = STANDARD_BUILD_DIR / "refined_response_surfaces"
DEFAULT_SENSITIVITY_RESULTS = OPTSIM_RESULTS_DIR / "standard_sensitivity_results.csv"
DEFAULT_REFINED_CONFIG = DEFAULT_REFINED_BUILD_DIR / "_refined_response_surface_config.yaml"
DEFAULT_REFINED_POPULATION = STANDARD_BUILD_DIR / "refined_population"
DEFAULT_SELECTION_CSV = DEFAULT_REFINED_BUILD_DIR / "selected_parameters.csv"
DEFAULT_INPUTS_CSV = DEFAULT_REFINED_BUILD_DIR / "refined_response_surface_inputs.csv"
DEFAULT_RESULTS_TABLE = DEFAULT_REFINED_BUILD_DIR / "refined_response_surface_results.parquet"
DEFAULT_SURFACE_PDF = OPTSIM_RESULTS_DIR / "refined_response_surface_report.pdf"
DEFAULT_SURFACE_RESULTS_CSV = OPTSIM_RESULTS_DIR / "refined_response_surface_results.csv"
DEFAULT_COEFFICIENTS_CSV = DEFAULT_REFINED_BUILD_DIR / "refined_response_surface_coefficients.csv"

DEFAULT_RESPONSE_METRICS = (
    "limit_ay_mps2",
    "sideslip_gradient_deg_per_g",
    "limit_sideslip_gradient_deg_per_g",
    "understeer_gradient_deg_per_g",
    "limit_understeer_gradient_deg_per_g",
    "handwheel_angle_gradient_deg_per_g",
    "limit_handwheel_gradient_deg_per_g",
    "roll_gradient_deg_per_g",
    "limit_roll_gradient_deg_per_g",
)
DEFAULT_EXCLUDE_INPUTS = ("*.spring_rate_n_per_m",)


def load_table(path: Path) -> pd.DataFrame:
    """Load a CSV or parquet table, with sibling suffix fallback."""
    if path.exists():
        source = path
    elif path.with_suffix(".csv").exists():
        source = path.with_suffix(".csv")
    elif path.with_suffix(".parquet").exists():
        source = path.with_suffix(".parquet")
    else:
        raise FileNotFoundError(f"Could not find results table at {path}")

    if source.suffix.lower() == ".csv":
        return pd.read_csv(source)
    if source.suffix.lower() == ".parquet":
        return pd.read_parquet(source)
    raise ValueError(f"Unsupported results table format: {source}")


def load_yaml(path: Path) -> dict[str, Any]:
    with path.open("r", encoding="utf-8") as f:
        data = yaml.safe_load(f)
    if not isinstance(data, dict):
        raise TypeError(f"Expected mapping at top level: {path}")
    return data


def write_yaml_if_changed(path: Path, data: dict[str, Any]) -> bool:
    path.parent.mkdir(parents=True, exist_ok=True)
    new_text = yaml.safe_dump(data, sort_keys=False)
    old_text = path.read_text(encoding="utf-8") if path.exists() else None
    if old_text == new_text:
        return False
    path.write_text(new_text, encoding="utf-8")
    return True


def rebase_path_field(
    config: dict[str, Any],
    field: str,
    *,
    source_config_path: Path,
    target_config_path: Path,
) -> None:
    if field not in config:
        return

    source_dir = source_config_path.resolve().parent
    target_dir = target_config_path.resolve().parent
    source_value = Path(str(config[field]))
    resolved = source_value if source_value.is_absolute() else source_dir / source_value
    config[field] = os.path.relpath(resolved.resolve(), target_dir)


def metric_column(
    df: pd.DataFrame,
    metric: str,
    *,
    standard: str = "SteadyStateEval",
) -> str | None:
    candidates = [metric]
    if not metric.startswith(f"{standard}_"):
        candidates.append(f"{standard}_{metric}")

    for candidate in candidates:
        if candidate in df.columns:
            return candidate
    return None


def resolve_metric_columns(
    df: pd.DataFrame,
    metrics: Iterable[str] | None,
    *,
    standard: str = "SteadyStateEval",
) -> list[str]:
    requested = tuple(metrics or DEFAULT_RESPONSE_METRICS)
    resolved: list[str] = []
    missing: list[str] = []
    for metric in requested:
        column = metric_column(df, metric, standard=standard)
        if column is None:
            missing.append(metric)
            continue
        resolved.append(column)

    if missing:
        print(f"Skipping missing response metric(s): {', '.join(missing)}")
    if not resolved:
        raise ValueError("No requested response metrics were found in the sensitivity table")
    return resolved


def input_columns_from_config(
    df: pd.DataFrame,
    doe_config: dict[str, Any],
    *,
    exclude_patterns: Iterable[str] = (),
) -> list[str]:
    columns: list[str] = []
    for var in doe_config["variables"]:
        path = var["path"]
        if path not in df.columns:
            continue
        if any(fnmatch.fnmatch(path, pattern) for pattern in exclude_patterns):
            continue
        series = pd.to_numeric(df[path], errors="coerce")
        if series.nunique(dropna=True) <= 1:
            continue
        columns.append(path)
    return columns


def _baseline_row(df: pd.DataFrame, baseline_variant: str) -> pd.Series:
    if "variant" not in df.columns:
        raise ValueError("Sensitivity table must include a 'variant' column")
    baseline = df[df["variant"] == baseline_variant]
    if baseline.empty:
        raise ValueError(f"Baseline variant not found: {baseline_variant}")
    return baseline.iloc[0]


def oat_effects(
    df: pd.DataFrame,
    input_cols: list[str],
    metric: str,
    *,
    baseline_variant: str = "variant_0000",
) -> pd.DataFrame:
    """Return one-factor-at-a-time effect spans for one response metric."""
    base = _baseline_row(df, baseline_variant)
    base_metric = float(base[metric])

    rows: list[dict[str, float | str]] = []
    for input_col in input_cols:
        mask = pd.Series(True, index=df.index)
        for other_col in input_cols:
            other_base = float(base[other_col])
            values = pd.to_numeric(df[other_col], errors="coerce")
            if other_col == input_col:
                mask &= ~np.isclose(values, other_base, rtol=0, atol=1e-10)
            else:
                mask &= np.isclose(values, other_base, rtol=0, atol=1e-10)

        perturbed = df[mask].copy()
        if perturbed.empty:
            continue

        perturbed[metric] = pd.to_numeric(perturbed[metric], errors="coerce")
        perturbed[input_col] = pd.to_numeric(perturbed[input_col], errors="coerce")
        perturbed = perturbed.dropna(subset=[metric, input_col])
        if perturbed.empty:
            continue

        deltas = perturbed[metric].to_numpy(dtype=float) - base_metric
        span = float(np.nanmax(np.abs(deltas)))
        span_pct = (
            100.0 * span / abs(base_metric)
            if abs(base_metric) > 1e-12
            else float("nan")
        )

        rows.append(
            {
                "input": input_col,
                "baseline": base_metric,
                "input_baseline": float(base[input_col]),
                "span": span,
                "span_pct": span_pct,
                "n_points": int(len(perturbed)),
            }
        )

    effects = pd.DataFrame(rows)
    if effects.empty:
        return effects
    return effects.sort_values("span", ascending=False).reset_index(drop=True)


def select_parameters(
    sensitivity_df: pd.DataFrame,
    base_doe_config: dict[str, Any],
    *,
    metrics: Iterable[str] | None = None,
    standard: str = "SteadyStateEval",
    top_k: int = 2,
    baseline_variant: str = "variant_0000",
    exclude_inputs: Iterable[str] = DEFAULT_EXCLUDE_INPUTS,
) -> pd.DataFrame:
    """Select the top input parameters for each metric from OAT effects."""
    if top_k < 2:
        raise ValueError("top_k must be at least 2 for 2D response surfaces")

    metric_cols = resolve_metric_columns(sensitivity_df, metrics, standard=standard)
    input_cols = input_columns_from_config(
        sensitivity_df,
        base_doe_config,
        exclude_patterns=exclude_inputs,
    )
    if not input_cols:
        raise ValueError("No numeric swept inputs found in the sensitivity table")

    rows: list[dict[str, float | int | str]] = []
    for metric in metric_cols:
        effects = oat_effects(
            sensitivity_df,
            input_cols,
            metric,
            baseline_variant=baseline_variant,
        )
        if effects.empty:
            print(f"Skipping {metric}: no one-factor effects found")
            continue

        for rank, (_, row) in enumerate(effects.head(top_k).iterrows(), start=1):
            rows.append(
                {
                    "metric": metric,
                    "metric_unprefixed": (
                        metric.removeprefix(f"{standard}_")
                        if metric.startswith(f"{standard}_")
                        else metric
                    ),
                    "rank": rank,
                    "input": str(row["input"]),
                    "span": float(row["span"]),
                    "span_pct": float(row["span_pct"]),
                    "baseline": float(row["baseline"]),
                    "input_baseline": float(row["input_baseline"]),
                    "n_points": int(row["n_points"]),
                }
            )

    selection = pd.DataFrame(rows)
    if selection.empty:
        raise ValueError("No refined response-surface selections could be made")
    return selection


def response_surface_pairs(selection: pd.DataFrame, *, top_k: int = 2) -> list[dict[str, Any]]:
    pairs: list[dict[str, Any]] = []
    for metric, group in selection.groupby("metric", sort=False):
        ordered = group.sort_values("rank").head(top_k)
        inputs = ordered["input"].astype(str).tolist()
        if len(inputs) < 2:
            continue
        pairs.append(
            {
                "metric": metric,
                "metric_unprefixed": str(ordered["metric_unprefixed"].iloc[0]),
                "variables": inputs[:2],
            }
        )
    return pairs


def build_refined_config(
    base_doe_config: dict[str, Any],
    selection: pd.DataFrame,
    *,
    grid_levels: int = 5,
    top_k: int = 2,
) -> dict[str, Any]:
    pairs = response_surface_pairs(selection, top_k=top_k)
    if not pairs:
        raise ValueError("At least one two-variable response-surface pair is required")

    selected_paths: list[str] = []
    for pair in pairs:
        for path in pair["variables"]:
            if path not in selected_paths:
                selected_paths.append(path)

    source_vars = {var["path"]: var for var in base_doe_config["variables"]}
    missing = [path for path in selected_paths if path not in source_vars]
    if missing:
        raise KeyError(f"Selected input(s) missing from DOE config: {missing}")

    refined = deepcopy(base_doe_config)
    refined["variables"] = [deepcopy(source_vars[path]) for path in selected_paths]
    refined["sampling"] = {
        "method": "response_surface_pairs",
        "grid_levels": int(grid_levels),
        "pairs": pairs,
    }
    refined["refined_response_surface"] = {
        "selection": "top tornado OAT spans",
        "top_k": int(top_k),
    }
    return refined


def clean_population(population_dir: Path) -> None:
    population_dir.mkdir(parents=True, exist_ok=True)
    for variant_dir in population_dir.glob("variant_????"):
        if variant_dir.is_dir():
            shutil.rmtree(variant_dir)
    for cache_file in (".pipeline.hash",):
        path = population_dir / cache_file
        if path.exists():
            path.unlink()


def prepare_refined_variants(
    refined_config_path: Path,
    population_dir: Path,
    inputs_csv: Path,
    *,
    force_rebuild: bool = False,
) -> list[dict[str, float]]:
    variants = sample(refined_config_path)

    if force_rebuild:
        clean_population(population_dir)

    existing = len(list(population_dir.glob("variant_????")))
    if existing > 0 and existing != len(variants):
        clean_population(population_dir)

    generate_variants(refined_config_path, variants, population_dir)

    rows = [
        {"variant": f"variant_{i:04d}", **params}
        for i, params in enumerate(variants)
    ]
    inputs_csv.parent.mkdir(parents=True, exist_ok=True)
    pd.DataFrame(rows).to_csv(inputs_csv, index=False)
    return variants


def write_selection(selection: pd.DataFrame, output_path: Path) -> None:
    output_path.parent.mkdir(parents=True, exist_ok=True)
    selection.to_csv(output_path, index=False)
