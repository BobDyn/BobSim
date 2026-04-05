"""sampler.py — Read baseline car + DOE config, generate N variant dicts via LHS."""

from pathlib import Path

import yaml
from scipy.stats.qmc import LatinHypercube


def parse_mo_blocks(mo_path: str | Path) -> dict[str, dict[str, str]]:
    text = Path(mo_path).read_text()
    blocks: dict[str, dict[str, str]] = {}
    n = len(text)
    i = 0

    while i < n:
        paren_start = text.find("(", i)
        if paren_start == -1:
            break

        # Walk back over whitespace to grab the block name identifier
        j = paren_start - 1
        while j >= 0 and text[j] in " \t\n\r":
            j -= 1
        name_end = j + 1
        while j >= 0 and (text[j].isalnum() or text[j] == "_"):
            j -= 1
        block_name = text[j + 1: name_end]

        # Only keep top-level parameter blocks
        stmt_start = text.rfind(";", 0, j + 1)
        if "parameter" not in text[stmt_start + 1: j + 1]:
            i = paren_start + 1
            continue

        depth = 1
        k = paren_start + 1
        while k < n and depth > 0:
            if text[k] in "({":
                depth += 1
            elif text[k] in ")}":
                depth -= 1
            k += 1

        blocks[block_name] = _parse_params(text[paren_start + 1: k - 1])
        i = k

    return blocks


def _parse_params(body: str) -> dict[str, str]:
    import re

    body = re.sub(r"//[^\n]*", "", body)

    params: dict[str, str] = {}
    depth = 0
    current: list[str] = []

    for ch in body + ",":
        if ch in "({":
            depth += 1
            current.append(ch)
        elif ch in ")}":
            depth -= 1
            current.append(ch)
        elif ch == "," and depth == 0:
            token = "".join(current).strip()
            if "=" in token:
                key, _, val = token.partition("=")
                params[key.strip()] = val.strip()
            current = []
        else:
            current.append(ch)

    return params


def load_config(config_path: str | Path) -> dict:
    with open(config_path) as f:
        return yaml.safe_load(f)


def read_baseline(mo_path: str | Path, variables: list[dict]) -> dict[str, float]:
    blocks = parse_mo_blocks(mo_path)
    baseline: dict[str, float] = {}
    for var in variables:
        raw = blocks[var["block"]][var["param"]]
        baseline[var["path"]] = float(eval(raw))
    return baseline


def sample(config_path: str | Path) -> list[dict[str, float]]:
    cfg = load_config(config_path)
    variables = cfg["variables"]
    n_samples = cfg["samples"]
    seed = cfg.get("seed")

    # Resolve mo_path relative to the config file
    config_dir = Path(config_path).resolve().parent
    mo_path = (config_dir / cfg["baseline_mo"]).resolve()

    baseline = read_baseline(mo_path, variables)

    lhs = LatinHypercube(d=len(variables),
                         seed=seed)  # latin hypercube is a way to sample without needing a ton of data
    unit_samples = lhs.random(n=n_samples)  # shape (n_samples, d)

    variants: list[dict[str, float]] = [baseline.copy()]  # index 0 = baseline

    for row in unit_samples:
        variant: dict[str, float] = {}
        for j, var in enumerate(variables):
            lo, hi = var["range"]
            variant[var["path"]] = lo + row[j] * (hi - lo)
        variants.append(variant)

    return variants


if __name__ == "__main__":
    import sys

    cfg_path = sys.argv[1] if len(sys.argv) > 1 else Path(
        __file__).parent / "configs/doe_config.yaml"
    variants = sample(cfg_path)
    print(f"Generated {len(variants)} variants ({len(variants) - 1} sampled + 1 baseline)")
    print(f"Baseline: {variants[0]}")
    print(f"Sample 1: {variants[1]}")
