"""generator.py — Take variant dicts from sampler, write variant.yaml for each into population/."""

from pathlib import Path

import yaml


def load_config(config_path: str | Path) -> dict:
    with open(config_path) as f:
        return yaml.safe_load(f)


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


def generate_variants(
        config_path: str | Path,
        variants: list[dict[str, float]],
        population_dir: str | Path,
) -> list[Path]:
    """Write one variant.yaml per variant dict into population/variant_N/."""

    config_path = Path(config_path).resolve()
    population_dir = Path(population_dir).resolve()
    cfg = load_config(config_path)

    # Resolve base record relative to config file
    config_dir = config_path.parent
    mo_path = (config_dir / cfg["baseline_mo"]).resolve()
    base_text = mo_path.read_text()

    # Build lookup: path -> {block, param}
    var_lookup = {
        var["path"]: {"block": var["block"], "param": var["param"]}
        for var in cfg["variables"]
    }

    written: list[Path] = []

    for i, variant in enumerate(variants):
        variant_dir = population_dir / f"variant_{i:04d}"
        variant_dir.mkdir(parents=True, exist_ok=True)

        text = base_text
        for path, value in variant.items():
            if path not in var_lookup:
                raise KeyError(f"Path '{path}' not in config variables")
            block = var_lookup[path]["block"]
            param = var_lookup[path]["param"]
            text = substitute_param(text, block, param, value)

        out_path = variant_dir / "variant.yaml"
        out_path.write_text(text)
        written.append(out_path)

    print(f"Generated {len(written)} variants in {population_dir}")
    return written


if __name__ == "__main__":
    from sampler import sample

    config = Path(__file__).parent / "configs/doe_config.yaml"
    population = Path(__file__).parent / "population"

    variants = sample(config)
    generate_variants(config, variants, population)
