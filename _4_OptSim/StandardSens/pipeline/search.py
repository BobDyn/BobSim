"""search.py — Reverse lookup: target metrics → suspension parameters.
 
Loads the aggregated Parquet table, builds a KDTree over the requested
metric columns, and returns the nearest variant's suspension parameters.
 
Usage:
    python search.py --metrics \\
        SteadyStateEval_understeer_gradient_deg_per_g=0.05 \\
        SteadyStateEval_peak_handwheel_torque_Nm=12

    python search.py \\
        --metrics SteadyStateEval_understeer_gradient_deg_per_g=0.05 \\
        SteadyStateEval_peak_handwheel_torque_Nm=12 \\
        --parquet _4_OptSim/Build/StandardSens/standard_sensitivity_results.parquet \\
        --top 3
 
"""

from __future__ import annotations
import argparse
import sys
from pathlib import Path
import numpy as np
import pandas as pd
import yaml
from scipy.spatial import KDTree

from StandardSens.pipeline.generate_configs import SWEEP_SCOPE_ALL

STANDARD_DIR = Path(__file__).resolve().parents[1]
OPTSIM_DIR = STANDARD_DIR.parent
DEFAULT_PARQUET = OPTSIM_DIR / "Build/StandardSens/standard_sensitivity_results.parquet"
DEFAULT_DOE_CONFIG = STANDARD_DIR / "configs/_doe_config.yaml"

# Used only when the DOE config cannot be read. Keeping this in sync by hand is
# what caused swept parameters to go missing from the results, so prefer the
# config-derived list below.
FALLBACK_INPUT_PARAMS = [
    "front.stabar.rate_n_m_per_rad",
    "rear.stabar.rate_n_m_per_rad",
    "front.wheel.toe_deg",
    "rear.wheel.toe_deg",
    "front.wheel.camber_deg",
    "rear.wheel.camber_deg",
    "aero.load_scale",
]


def load_input_params(doe_config_path: Path = DEFAULT_DOE_CONFIG) -> list[str]:
    """Return the swept `vehicle.yml` paths, in DOE config order.

    The aggregator keys each result row by these same paths, so deriving the
    list here keeps the reverse lookup reporting every parameter the sweep
    actually varied.
    """
    try:
        with open(doe_config_path) as handle:
            cfg = yaml.safe_load(handle) or {}
    except (OSError, yaml.YAMLError):
        return list(FALLBACK_INPUT_PARAMS)

    paths = [
        variable["path"]
        for variable in (cfg.get("variables") or [])
        if isinstance(variable, dict) and variable.get("path")
    ]
    return paths or list(FALLBACK_INPUT_PARAMS)


# Returned instead of a scope name when the population is demonstrably narrower
# than the config, but the config no longer says which scope produced it.
SCOPE_UNKNOWN = "unknown"


def load_sweep_scope(doe_config_path: Path = DEFAULT_DOE_CONFIG) -> str | None:
    """Return the scope the DOE config was generated at.

    None means the config predates the `scope` key, not that the sweep was
    unrestricted — an old config cannot tell us either way.
    """
    try:
        with open(doe_config_path) as handle:
            cfg = yaml.safe_load(handle) or {}
    except (OSError, yaml.YAMLError):
        return None
    scope = cfg.get("scope")
    return str(scope) if scope else None


# ---------------------------------------------------------------------------
# Honesty guards
#
# The reverse lookup is a nearest-neighbour query over a finite population, not
# an optimizer. Each guard below turns a silent, plausible-looking answer into a
# stated limitation. None of them change the returned result.
# ---------------------------------------------------------------------------

# Below this many rows a 23-parameter sweep cannot support a meaningful
# nearest-neighbour answer, let alone the response surfaces fitted from it.
MIN_USEFUL_POPULATION = 10


def _warn_targets_outside_population(
    targets: dict[str, float], df: pd.DataFrame, ranges: np.ndarray
) -> list[str]:
    """Warn for each target that lies outside its column's sampled spread.

    Returns the metric names that were out of range, so callers can test this
    without parsing stderr.
    """
    outside: list[str] = []
    for position, (metric, target) in enumerate(targets.items()):
        column = df[metric]
        low, high = float(column.min()), float(column.max())
        if low <= target <= high:
            continue
        overshoot = (low - target) if target < low else (target - high)
        spread = float(ranges[position])
        outside.append(metric)
        print(
            f"WARNING: target {metric}={target:g} is outside the sampled population "
            f"[{low:g}, {high:g}].\n"
            f"         It sits {overshoot / spread:.2f} population-widths beyond the "
            f"nearest edge, so the result below is the closest edge variant, NOT a "
            f"vehicle that meets the target.\n"
            "         Widen the sweep bounds in configs/vehicle_architecture.yaml and "
            "rerun 'make opt-standard'.",
            file=sys.stderr,
        )
    return outside


def _warn_population_too_small(df: pd.DataFrame, input_params: list[str]) -> bool:
    """Warn when the results table is too sparse to support a reverse lookup."""
    if len(df) >= MIN_USEFUL_POPULATION:
        return False
    print(
        f"WARNING: the results table holds only {len(df)} variant(s) for "
        f"{len(input_params)} swept parameter(s).\n"
        "         That is a smoke-test population, not a design population: the "
        "nearest neighbour is\n"
        "         near-arbitrary and any fitted response surface is "
        "rank-deficient.\n"
        "         Rerun 'make opt-standard' with a real sample count "
        "(omit DOE_SAMPLES for the full sweep).",
        file=sys.stderr,
    )
    return True


def _warn_if_results_scope_is_narrow(
    df: pd.DataFrame, input_params: list[str], doe_config_path: Path
) -> str | None:
    """Warn when the answer rests on a scope-restricted population.

    Two ways that happens, both of which otherwise read as a complete answer:

    1. The config names a scope other than `all`, so whole families of
       parameters were pinned at baseline and were never free variables.
    2. The config names `all` (or predates scopes) but the table is missing
       parameters the config lists. That is what restoring _doe_config.yaml
       from git after a scoped run looks like: the config claims every
       parameter, the population only covers some.

    Case 2 is inferred from the table's columns, not from recorded provenance —
    the aggregated table carries no scope of its own — so it can detect a
    narrower population but cannot name the scope that produced it.

    Either way, parameters the config names but the table lacks cannot be
    reported, so this names them here. That used to be a second warning printed
    further down; one condition should not produce two warnings.

    Returns the scope warned about, SCOPE_UNKNOWN for case 2, or None.
    """
    scope = load_sweep_scope(doe_config_path)
    missing = [param for param in input_params if param not in df.columns]
    absent = (
        [
            f"         The {len(missing)} absent from the table will not be "
            f"reported: {missing}"
        ]
        if missing
        else []
    )

    if scope is not None and scope != SWEEP_SCOPE_ALL:
        print(
            "\n".join(
                [
                    f"WARNING: this answer came from a {scope}-only population.",
                    f"         The sweep was run at scope {scope!r}, so every parameter "
                    "outside that scope was held",
                    "         at baseline and is NOT a free variable here. The reported "
                    "parameters are the swept ones only.",
                    *absent,
                    "         Rerun 'make clean-opt && make opt-standard' for a sweep "
                    "over all parameters.",
                ]
            ),
            file=sys.stderr,
        )
        return scope

    if missing:
        print(
            "\n".join(
                [
                    f"WARNING: the results table covers "
                    f"{len(input_params) - len(missing)} of the {len(input_params)} "
                    "parameters the DOE config names.",
                    "         That is what a scope-restricted sweep looks like once the "
                    "generated config has been",
                    "         restored or regenerated at a wider scope: the config claims "
                    "parameters the population",
                    "         never varied.",
                    *absent,
                    "         Rerun 'make clean-opt && make opt-standard' before trusting "
                    "this.",
                ]
            ),
            file=sys.stderr,
        )
        return SCOPE_UNKNOWN

    return None


def _warn_if_results_are_stale(results_path: Path, doe_config_path: Path) -> bool:
    """Warn when inputs were modified after the results table was written.

    The existing missing-column check only fires when a swept parameter vanishes.
    A config edit that keeps the same parameter names, or a change to the vehicle
    baseline or compiler settings, leaves a stale table looking perfectly valid.
    """
    if not results_path.exists():
        return False
    results_mtime = results_path.stat().st_mtime
    newer: list[str] = []
    candidates = [
        doe_config_path,
        doe_config_path.parent / "vehicle_architecture.yaml",
        doe_config_path.parent / "compiler_config.yaml",
        doe_config_path.parent / "aggregator_config.yaml",
        OPTSIM_DIR.parent / "vehicle.yml",
    ]
    for candidate in candidates:
        if candidate.exists() and candidate.stat().st_mtime > results_mtime:
            newer.append(candidate.name)
    if not newer:
        return False
    print(
        f"WARNING: {results_path.name} predates {', '.join(newer)}.\n"
        "         The table was generated from older inputs, so these results may not "
        "describe the current vehicle or sweep.\n"
        "         Rerun 'make opt-standard' to regenerate it.",
        file=sys.stderr,
    )
    return True


# ---------------------------------------------------------------------------
# Search
# ---------------------------------------------------------------------------

def search(targets: dict[str, float], parquet_path: Path = DEFAULT_PARQUET,
           top: int = 1, doe_config_path: Path = DEFAULT_DOE_CONFIG) -> pd.DataFrame:
    """Find the nearest variants to the target metric values.

    Args:
        targets:         dict of metric_name -> target_value
        parquet_path:    path to the aggregated StandardSens parquet
        top:             number of nearest variants to return
        doe_config_path: DOE config used to identify the swept input columns

    Returns:
        DataFrame with top nearest variants — input params + metrics + distance
    """
    input_params = load_input_params(doe_config_path)
    csv_path = parquet_path.with_suffix(".csv")
    if parquet_path.exists():
        df = pd.read_parquet(parquet_path)
        _warn_if_results_are_stale(parquet_path, doe_config_path)
    elif csv_path.exists():
        df = pd.read_csv(csv_path)
        _warn_if_results_are_stale(csv_path, doe_config_path)
    else:
        raise FileNotFoundError(
            f"Results not found at {parquet_path} or {csv_path}. Has the pipeline run?"
        )

    # Validate requested metrics exist
    missing = [m for m in targets if m not in df.columns]
    if missing:
        raise ValueError(
            f"Unknown metrics: {missing}\n"
            f"Available: {[c for c in df.columns if c not in input_params + ['variant']]}"
        )

    metric_cols = list(targets.keys())
    target_vals = np.array([targets[m] for m in metric_cols])

    # Normalize each dimension by its range so no single metric dominates
    metric_data = df[metric_cols].values
    ranges = metric_data.max(axis=0) - metric_data.min(axis=0)
    ranges[ranges == 0] = 1.0  # avoid divide by zero for constant columns

    # A nearest-neighbour lookup cannot extrapolate. If a target sits outside the
    # sampled spread it silently returns the closest edge variant, which reads as
    # an answer. Say so instead, in units of the population's own spread.
    _warn_targets_outside_population(targets, df, ranges)
    _warn_population_too_small(df, input_params)
    _warn_if_results_scope_is_narrow(df, input_params, doe_config_path)

    metric_data_norm = metric_data / ranges
    target_norm = target_vals / ranges

    # Build KDTree and query
    tree = KDTree(metric_data_norm)
    distances, indices = tree.query(target_norm, k=min(top, len(df)))

    # Ensure distances and indices are always 1D arrays for consistent handling.
    distances_arr = np.atleast_1d(distances)
    indices_arr = np.atleast_1d(indices).astype(int)

    # Parameters the config names but the table lacks are reported by
    # _warn_if_results_scope_is_narrow above, which also explains why they are
    # missing. Warning about them again here would double up on one condition.
    input_cols = [col for col in input_params if col in df.columns]

    results = df.iloc[indices_arr][["variant"] + input_cols + metric_cols].copy()
    results.insert(1, "distance", [round(float(d), 6) for d in distances_arr])

    return results.reset_index(drop=True)



# ---------------------------------------------------------------------------
# CLI
# ---------------------------------------------------------------------------

def _parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Reverse lookup: target metrics → suspension parameters"
    )
    parser.add_argument(
        "--metrics",
        nargs="+",
        required=True,
        metavar="METRIC=VALUE",
        help="One or more metric=value pairs e.g. SteadyStateEval_understeer_gradient_deg_per_g=0.05",
    )
    parser.add_argument(
        "--parquet",
        type=Path,
        default=DEFAULT_PARQUET,
        help=f"Path to parquet file (default: {DEFAULT_PARQUET})",
    )
    parser.add_argument(
        "--top",
        type=int,
        default=1,
        help="Number of nearest variants to return (default: 1)",
    )
    return parser.parse_args()


def _parse_metrics(metric_args: list[str]) -> dict[str, float]:
    targets = {}
    for arg in metric_args:
        if "=" not in arg:
            print(f"ERROR: metric must be in METRIC=VALUE format, got: {arg}")
            sys.exit(1)
        key, val = arg.split("=", 1)
        try:
            targets[key.strip()] = float(val.strip())
        except ValueError:
            print(f"ERROR: value must be a number, got: {val}")
            sys.exit(1)
    return targets


def _print_results(results: pd.DataFrame, targets: dict[str, float]) -> None:
    metric_cols = list(targets.keys())
    input_cols = [
        col for col in results.columns
        if col not in metric_cols and col not in ("variant", "distance")
    ]
    width = max((len(col) for col in input_cols), default=35)

    print("\nTarget metrics:")
    for metric, val in targets.items():
        print(f"  {metric}: {val}")

    print()
    for _, row in results.iterrows():
        print(f"Variant:  {row['variant']}  (distance: {row['distance']})")
        print("  Swept inputs:")
        for param in input_cols:
            print(f"    {param:<{width}} {row[param]:.4f}")
        print("  Metrics:")
        for metric in metric_cols:
            print(f"    {metric:<35} {row[metric]:.6f}  (target: {targets[metric]})")
        print()


# ---------------------------------------------------------------------------
# Entrypoint
# ---------------------------------------------------------------------------

if __name__ == "__main__":
    args = _parse_args()
    targets = _parse_metrics(args.metrics)

    results = search(targets, parquet_path=args.parquet, top=args.top)
    _print_results(results, targets)
