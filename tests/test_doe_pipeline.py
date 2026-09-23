"""DOE plumbing checks that run without OpenModelica."""

from __future__ import annotations

from collections.abc import Callable
from pathlib import Path
import sys
from typing import TYPE_CHECKING

import pytest
import yaml

if TYPE_CHECKING:
    # mypy reads `pd` from importorskip as a value, so annotations name the module.
    import pandas


ROOT = Path(__file__).resolve().parents[1]
OPTSIM_DIR = ROOT / "_4_OptSim"
ARCHITECTURE_CONFIG = OPTSIM_DIR / "StandardSens/configs/vehicle_architecture.yaml"

# Import as the opt-* make targets do, with _4_OptSim on the path.
if str(OPTSIM_DIR) not in sys.path:
    sys.path.insert(0, str(OPTSIM_DIR))

pytest.importorskip("scipy", reason="DOE sampling requires scipy")
pd = pytest.importorskip("pandas", reason="the reverse-lookup guards operate on DataFrames")
np = pytest.importorskip("numpy", reason="normalization ranges are numpy arrays")

from StandardSens.pipeline import generate_configs, generator, search  # noqa: E402


def _localize(doe_config_path: Path) -> Path:
    """Resolve the config's relative paths against the real configs/ directory."""
    cfg = yaml.safe_load(doe_config_path.read_text())
    config_dir = generate_configs.DOE_CONFIG.parent
    cfg["baseline_mo"] = str((config_dir / cfg["baseline_mo"]).resolve())
    cfg["architecture"]["template"] = str(
        (config_dir.parent / cfg["architecture"]["template"]).resolve()
    )
    doe_config_path.write_text(yaml.safe_dump(cfg, sort_keys=False))
    return doe_config_path


def _boblib_record_available(doe_config_path: Path) -> bool:
    cfg = yaml.safe_load(doe_config_path.read_text())
    return Path(cfg["baseline_mo"]).is_file()


@pytest.fixture
def doe_config(tmp_path: Path) -> Path:
    """A freshly generated DOE config written outside the repo tree."""
    out = tmp_path / "_doe_config.yaml"
    generate_configs.refresh_doe_config(
        architecture_config_path=ARCHITECTURE_CONFIG,
        compiler_config_path=generate_configs.COMPILER_CONFIG,
        doe_config_path=out,
    )
    return out


def test_generated_config_uses_posix_separators(doe_config: Path) -> None:
    """Backslashes here are a single opaque filename inside the Linux container."""
    text = doe_config.read_text()
    assert "\\" not in text, "DOE config must not contain native Windows separators"

    cfg = yaml.safe_load(text)
    assert "/" in cfg["baseline_mo"]
    assert "/" in cfg["architecture"]["template"]


def test_checked_in_config_matches_regeneration(doe_config: Path) -> None:
    """Compare the committed blob. A local DOE_* run rewrites the working copy."""
    import subprocess

    regenerated = yaml.safe_load(doe_config.read_text())

    rel = generate_configs.DOE_CONFIG.relative_to(ROOT).as_posix()
    try:
        blob = subprocess.run(
            ["git", "show", f"HEAD:{rel}"],
            cwd=ROOT,
            capture_output=True,
            text=True,
            check=True,
        ).stdout
    except (OSError, subprocess.CalledProcessError):
        pytest.skip("git is unavailable or the config is not committed")

    committed = yaml.safe_load(blob)
    if committed == regenerated:
        return

    on_disk = yaml.safe_load(generate_configs.DOE_CONFIG.read_text())
    if on_disk == regenerated:
        pytest.skip(
            f"{rel} was regenerated but not committed. Commit it so that this "
            "check can compare against HEAD again."
        )

    assert committed == regenerated, (
        "_doe_config.yaml is stale or was hand-edited; it is generated from "
        "configs/vehicle_architecture.yaml. Regenerate it with "
        "'python -m StandardSens.pipeline.generate_configs' and commit the result."
    )


def test_sample_count_overrides(monkeypatch: pytest.MonkeyPatch, tmp_path: Path) -> None:
    monkeypatch.setenv("BOBSIM_DOE_METHOD", "lhs")
    monkeypatch.setenv("BOBSIM_DOE_SAMPLES", "3")
    out = tmp_path / "_doe_config.yaml"
    generate_configs.refresh_doe_config(
        architecture_config_path=ARCHITECTURE_CONFIG,
        compiler_config_path=generate_configs.COMPILER_CONFIG,
        doe_config_path=out,
    )
    cfg = yaml.safe_load(out.read_text())
    assert cfg["sampling"]["method"] == "lhs"
    assert cfg["samples"] == 3

    monkeypatch.setenv("BOBSIM_DOE_SAMPLES", "not-a-number")
    with pytest.raises(ValueError, match="BOBSIM_DOE_SAMPLES"):
        generate_configs.refresh_doe_config(
            architecture_config_path=ARCHITECTURE_CONFIG,
            compiler_config_path=generate_configs.COMPILER_CONFIG,
            doe_config_path=out,
        )


def _variable_paths(architecture_config_path: Path = ARCHITECTURE_CONFIG) -> dict[str, list[str]]:
    """Group the architecture YAML's sweep variables by their declared scope."""
    raw = yaml.safe_load(architecture_config_path.read_text())["sweep"]["variables"]
    grouped: dict[str, list[str]] = {}
    for spec in raw:
        grouped.setdefault(str(spec.get("scope", "untagged")), []).append(spec["path"])
    return grouped


def _expected_paths(scope: str) -> list[str]:
    """Scope paths in YAML order, which grouping by scope does not keep."""
    raw = yaml.safe_load(ARCHITECTURE_CONFIG.read_text())["sweep"]["variables"]
    return [
        spec["path"]
        for spec in raw
        if scope == "all" or spec.get("scope") in (None, "all", scope)
    ]


def _generate(tmp_path: Path, **kwargs: object) -> dict:
    out = tmp_path / "_doe_config.yaml"
    generate_configs.refresh_doe_config(
        architecture_config_path=ARCHITECTURE_CONFIG,
        compiler_config_path=generate_configs.COMPILER_CONFIG,
        doe_config_path=out,
        **kwargs,  # type: ignore[arg-type]
    )
    return yaml.safe_load(out.read_text())


def test_scope_defaults_to_all(tmp_path: Path) -> None:
    """Unscoped invocations must keep sweeping every variable."""
    raw = yaml.safe_load(ARCHITECTURE_CONFIG.read_text())["sweep"]["variables"]
    every = [spec["path"] for spec in raw]

    default = _generate(tmp_path)
    assert [v["path"] for v in default["variables"]] == every
    assert _generate(tmp_path, scope="all") == default
    assert generate_configs.DEFAULT_SWEEP_SCOPE == "all"


def test_scope_filters_variables(tmp_path: Path) -> None:
    """Each scope selects exactly the variables tagged for it in the YAML."""
    untagged = _variable_paths().get("untagged", [])

    setup = _generate(tmp_path, scope="setup")
    architecture = _generate(tmp_path, scope="architecture")

    assert [v["path"] for v in setup["variables"]] == _expected_paths("setup")
    assert [v["path"] for v in architecture["variables"]] == _expected_paths(
        "architecture"
    )
    # Neither half may be the whole sweep.
    total = len(_generate(tmp_path)["variables"])
    assert len(setup["variables"]) < total
    assert len(architecture["variables"]) < total
    assert len(setup["variables"]) + len(architecture["variables"]) == (
        total + len(untagged)
    )

    # `scope` is a generation-time filter, not part of the generated config.
    assert all("scope" not in variable for variable in setup["variables"])


def test_scope_env_override(monkeypatch: pytest.MonkeyPatch, tmp_path: Path) -> None:
    monkeypatch.setenv("BOBSIM_DOE_SCOPE", "setup")
    assert [v["path"] for v in _generate(tmp_path)["variables"]] == _expected_paths(
        "setup"
    )


def test_invalid_scope_names_the_legal_values(
    monkeypatch: pytest.MonkeyPatch, tmp_path: Path
) -> None:
    monkeypatch.setenv("BOBSIM_DOE_SCOPE", "chassis")
    with pytest.raises(ValueError, match="BOBSIM_DOE_SCOPE") as excinfo:
        _generate(tmp_path)
    for legal in generate_configs.SWEEP_SCOPES:
        assert legal in str(excinfo.value)

    monkeypatch.delenv("BOBSIM_DOE_SCOPE")
    with pytest.raises(ValueError, match="sweep scope"):
        _generate(tmp_path, scope="Setup-only")


def test_untagged_variable_survives_every_scope() -> None:
    """A variable with no `scope:` belongs to all of them, never dropped."""
    untagged = {"path": "front.wheel.toe_deg", "range": [0, 1], "block": "pFr"}
    for scope in generate_configs.SWEEP_SCOPES:
        assert generate_configs._variable_in_scope(untagged, scope) is True

    tagged = dict(untagged, scope="setup")
    assert generate_configs._variable_in_scope(tagged, "setup") is True
    assert generate_configs._variable_in_scope(tagged, "all") is True
    assert generate_configs._variable_in_scope(tagged, "architecture") is False


def _architecture_copy(
    tmp_path: Path, mutate: Callable[[list[dict]], None]
) -> Path:
    """A writable copy of the architecture YAML with its template absolutized."""
    cfg = yaml.safe_load(ARCHITECTURE_CONFIG.read_text())
    # The copy lives outside configs/, so the relative template ref must resolve.
    cfg["vehicle_template"] = str(
        (ARCHITECTURE_CONFIG.parent / cfg["vehicle_template"]).resolve()
    )
    mutate(cfg["sweep"]["variables"])
    out = tmp_path / "vehicle_architecture.yaml"
    out.write_text(yaml.safe_dump(cfg, sort_keys=False))
    return out


def test_misspelled_variable_scope_fails_the_default_sweep(tmp_path: Path) -> None:
    """A typo'd tag must not lie dormant until someone runs a scoped sweep."""

    def mistag(variables: list[dict]) -> None:
        variables[0]["scope"] = "setpu"

    architecture = _architecture_copy(tmp_path, mistag)
    with pytest.raises(ValueError, match="setpu") as excinfo:
        generate_configs.refresh_doe_config(
            architecture_config_path=architecture,
            compiler_config_path=generate_configs.COMPILER_CONFIG,
            doe_config_path=tmp_path / "_doe_config.yaml",
        )
    assert "sweep variable" in str(excinfo.value)


def test_scoped_generation_keeps_untagged_variables(tmp_path: Path) -> None:
    """Remove a tag in a copy of the YAML. The variable must still be swept."""
    untagged: list[str] = []

    def untag(variables: list[dict]) -> None:
        victim = next(v for v in variables if v.get("scope") == "architecture")
        victim.pop("scope")
        untagged.append(victim["path"])

    architecture = _architecture_copy(tmp_path, untag)

    out = tmp_path / "_doe_config.yaml"
    generate_configs.refresh_doe_config(
        architecture_config_path=architecture,
        compiler_config_path=generate_configs.COMPILER_CONFIG,
        doe_config_path=out,
        scope="setup",
    )
    paths = [v["path"] for v in yaml.safe_load(out.read_text())["variables"]]
    assert untagged[0] in paths, "an untagged variable must not be dropped"


def test_reviewed_partition_sizes() -> None:
    """Pin the partition that the vehicle-dynamics review approved."""
    grouped = _variable_paths()
    assert len(grouped["setup"]) == 10
    assert len(grouped["architecture"]) == 9
    assert sorted(grouped["untagged"]) == [
        "aero.load_scale",
        "driver_mass.cg_m.x",
        "driver_mass.cg_m.z",
        "driver_mass.mass_kg",
    ]
    assert sum(len(paths) for paths in grouped.values()) == 23


def test_generated_config_records_the_scope(tmp_path: Path) -> None:
    """The resolved scope must round-trip into the generated config."""
    assert _generate(tmp_path)["scope"] == "all"
    assert _generate(tmp_path, scope="all")["scope"] == "all"
    assert _generate(tmp_path, scope="setup")["scope"] == "setup"
    assert _generate(tmp_path, scope="architecture")["scope"] == "architecture"

    # Use a fresh config. An override run can leave a scoped config on disk.
    _generate(tmp_path, scope="setup")
    assert search.load_sweep_scope(tmp_path / "_doe_config.yaml") == "setup"
    _generate(tmp_path)
    assert search.load_sweep_scope(tmp_path / "_doe_config.yaml") == "all"


def test_load_sweep_scope_tolerates_a_pre_scope_config(tmp_path: Path) -> None:
    """None means 'the config cannot say', not 'the sweep was unrestricted'."""
    assert search.load_sweep_scope(tmp_path / "absent.yaml") is None

    legacy = tmp_path / "_doe_config.yaml"
    legacy.write_text("variables:\n- path: front.wheel.toe_deg\n")
    assert search.load_sweep_scope(legacy) is None


def _scoped_config(tmp_path: Path, scope: str | None, paths: list[str]) -> Path:
    cfg: dict = {"variables": [{"path": path} for path in paths]}
    if scope is not None:
        cfg["scope"] = scope
    tmp_path.mkdir(parents=True, exist_ok=True)
    out = tmp_path / "_doe_config.yaml"
    out.write_text(yaml.safe_dump(cfg, sort_keys=False))
    return out


def _results(paths: list[str], rows: int = 4) -> pandas.DataFrame:
    data: dict[str, list] = {"variant": [f"variant_{i:04d}" for i in range(rows)]}
    for offset, path in enumerate(paths):
        data[path] = [float(i + offset) for i in range(rows)]
    return pd.DataFrame(data)


def test_search_warns_when_the_population_scope_is_narrow(tmp_path: Path) -> None:
    """A setup-only population must not answer as if it swept everything."""
    setup_paths = ["front.wheel.toe_deg", "rear.wheel.toe_deg"]

    scoped = _scoped_config(tmp_path, "setup", setup_paths)
    assert search._warn_if_results_scope_is_narrow(
        _results(setup_paths), setup_paths, scoped
    ) == "setup"

    # scope: all over a table that covers every named parameter is the happy path.
    full = _scoped_config(tmp_path / "full", "all", setup_paths)
    assert search._warn_if_results_scope_is_narrow(
        _results(setup_paths), setup_paths, full
    ) is None


def test_search_warns_when_the_table_is_narrower_than_the_config(tmp_path: Path) -> None:
    """The state after a scoped run when _doe_config.yaml is restored from git."""
    swept = ["front.wheel.toe_deg", "rear.wheel.toe_deg"]
    claimed = swept + ["sprung_mass.mass_kg", "body.torsional_stiff_n_m_per_rad"]

    restored = _scoped_config(tmp_path, "all", claimed)
    assert search._warn_if_results_scope_is_narrow(
        _results(swept), claimed, restored
    ) == search.SCOPE_UNKNOWN

    # A config that predates the scope key gets the same treatment.
    legacy = _scoped_config(tmp_path / "legacy", None, claimed)
    assert search._warn_if_results_scope_is_narrow(
        _results(swept), claimed, legacy
    ) == search.SCOPE_UNKNOWN

    # A single-row table is flagged too. Column presence does not depend on row count.
    assert search._warn_if_results_scope_is_narrow(
        _results(swept, rows=1), claimed, restored
    ) == search.SCOPE_UNKNOWN


def test_scope_warning_is_the_only_one_and_names_the_missing_params(
    tmp_path: Path, capsys: pytest.CaptureFixture[str]
) -> None:
    """One warning, and it names the specific missing parameters."""
    swept = ["front.wheel.toe_deg", "rear.wheel.toe_deg"]
    absent = ["sprung_mass.mass_kg", "body.torsional_stiff_n_m_per_rad"]
    claimed = swept + absent

    search._warn_if_results_scope_is_narrow(
        _results(swept), claimed, _scoped_config(tmp_path, "all", claimed)
    )
    err = capsys.readouterr().err

    assert err.count("WARNING:") == 1, f"expected exactly one warning, got:\n{err}"
    assert "covers 2 of the 4 parameters" in err
    for param in absent:
        assert param in err, f"{param} must still be named"
    assert "make clean-opt" in err, "the remedy must survive the merge"


def test_scoped_population_warning_also_names_missing_params(
    tmp_path: Path, capsys: pytest.CaptureFixture[str]
) -> None:
    """The scope-declared branch carries the parameter list too, still once."""
    swept = ["front.wheel.toe_deg"]
    claimed = swept + ["sprung_mass.mass_kg"]

    search._warn_if_results_scope_is_narrow(
        _results(swept), claimed, _scoped_config(tmp_path, "setup", claimed)
    )
    err = capsys.readouterr().err

    assert err.count("WARNING:") == 1, f"expected exactly one warning, got:\n{err}"
    assert "setup-only population" in err
    assert "sprung_mass.mass_kg" in err
    assert "make clean-opt" in err


def test_search_input_params_match_doe_variables(doe_config: Path) -> None:
    """The reverse lookup must report every parameter the sweep varies."""
    cfg = yaml.safe_load(doe_config.read_text())
    expected = [variable["path"] for variable in cfg["variables"]]
    assert search.load_input_params(doe_config) == expected
    assert len(expected) > 7, "expected the full sweep, not the legacy hardcoded subset"


def test_search_input_params_fall_back_when_config_missing(tmp_path: Path) -> None:
    assert search.load_input_params(tmp_path / "absent.yaml") == search.FALLBACK_INPUT_PARAMS


def _population(values: list[float]) -> pandas.DataFrame:
    return pd.DataFrame({"variant": [f"variant_{i:04d}" for i in range(len(values))],
                         "metric": values})


def test_search_warns_when_target_is_outside_the_population() -> None:
    """Regression: a 0.05 target over samples in [0.278, 0.331] was reported as met."""
    df = _population([0.278154, 0.295, 0.310, 0.330610])
    ranges = np.array([df["metric"].max() - df["metric"].min()])

    outside = search._warn_targets_outside_population({"metric": 0.05}, df, ranges)
    assert outside == ["metric"]

    within = search._warn_targets_outside_population({"metric": 0.30}, df, ranges)
    assert within == [], "a reachable target must not warn"


def test_search_warns_on_smoke_sized_population() -> None:
    """Four variants across 23 parameters is not a design population."""
    assert search._warn_population_too_small(_population([1.0, 2.0, 3.0, 4.0]),
                                            ["a"] * 23) is True
    big = _population([float(i) for i in range(search.MIN_USEFUL_POPULATION)])
    assert search._warn_population_too_small(big, ["a"] * 23) is False


def test_search_warns_when_results_predate_their_inputs(tmp_path: Path) -> None:
    """A config edit that keeps parameter names still invalidates the table."""
    configs = tmp_path / "configs"
    configs.mkdir()
    doe_config = configs / "_doe_config.yaml"
    results = tmp_path / "standard_sensitivity_results.csv"

    results.write_text("variant,metric\nvariant_0000,1.0\n")
    doe_config.write_text("variables: []\n")
    import os
    old = results.stat().st_mtime - 3600
    os.utime(results, (old, old))

    assert search._warn_if_results_are_stale(results, doe_config) is True

    fresh = doe_config.stat().st_mtime + 3600
    os.utime(results, (fresh, fresh))
    assert search._warn_if_results_are_stale(results, doe_config) is False


def test_four_post_metrics_resolve_to_generated_results() -> None:
    """FourPostEval writes to generated_results/; the DOE must look there."""
    primary = generator.FOUR_POST_METRICS_CANDIDATES[0]
    assert primary.parts[-3:-1] == ("_3_StandardSim", "generated_results")

    report_cfg = yaml.safe_load(
        (ROOT / "_3_StandardSim/FourPostEval/four_post_eval_config.yml").read_text()
    )["report"]
    assert Path(report_cfg["metrics_csv_path"]) == primary.relative_to(ROOT)


def test_missing_four_post_metrics_names_the_fix(tmp_path: Path) -> None:
    with pytest.raises(FileNotFoundError) as excinfo:
        generator._load_metrics_csv(tmp_path / "absent.csv")
    assert "standard-eval-four-post" in str(excinfo.value)


@pytest.mark.parametrize("samples", [3])
def test_small_doe_generates_variants(
    monkeypatch: pytest.MonkeyPatch, tmp_path: Path, samples: int
) -> None:
    """End-to-end plumbing: config -> sample the record -> write variant .mo."""
    monkeypatch.setenv("BOBSIM_DOE_METHOD", "lhs")
    monkeypatch.setenv("BOBSIM_DOE_SAMPLES", str(samples))

    doe_config_path = tmp_path / "_doe_config.yaml"
    generate_configs.refresh_doe_config(
        architecture_config_path=ARCHITECTURE_CONFIG,
        compiler_config_path=generate_configs.COMPILER_CONFIG,
        doe_config_path=doe_config_path,
    )

    _localize(doe_config_path)
    if not _boblib_record_available(doe_config_path):
        pytest.skip("BobLib submodule is not checked out; run 'make init'")

    from StandardSens.pipeline.sampler import sample

    variants = sample(doe_config_path)
    assert len(variants) == samples + 1, "LHS returns the baseline plus N samples"

    # Stub the FourPostEval motion ratios so this test does not simulate.
    metrics_csv = tmp_path / "four_post_eval_report_metrics.csv"
    metrics_csv.write_text(
        "metric,value\n"
        "static_motion_ratio_front,0.62\n"
        "static_motion_ratio_rear,0.71\n"
    )
    monkeypatch.setattr(
        generator, "FOUR_POST_METRICS_CANDIDATES", (metrics_csv,), raising=True
    )

    population = tmp_path / "population"
    generator.generate_variants(doe_config_path, variants, population)

    written = sorted(population.rglob("*.mo"))
    assert len(written) == len(variants)

    for path in written:
        text = path.read_text()
        assert text.lstrip().startswith("within "), f"{path} is not a Modelica record"
        assert "springFreeLength" in text
        # A failed substitution leaves the placeholder or an empty binding.
        assert "{" + "}" not in text

    # The sweep must actually perturb the record away from baseline.
    baseline_text = written[0].read_text()
    assert any(path.read_text() != baseline_text for path in written[1:])


def test_build_template_renders(tmp_path: Path) -> None:
    """Literal Modelica braces must be escaped as `{{...}}` for str.format."""
    from StandardSens.pipeline import compiler

    rendered = compiler.generate_mos(
        variant_mo=tmp_path / "variant.mo",
        build_dir=tmp_path / "build",
        boblib_path=tmp_path / "BobLib" / "package.mo",
        standard_cfg={"model": "BobLib.Experiments.Standards.VehicleSim"},
        build_options={
            "start_time": 0,
            "stop_time": 1,
            "intervals": 0,
            "tolerance": 1e-6,
            "solver": "dassl",
        },
    )

    # Escaped braces must survive as real Modelica array literals.
    assert 'loadModel(Modelica, {"4.1.0"});' in rendered
    assert 'loadModel(VehicleInterfaces, {"2.0.2"});' in rendered
    assert "BobLib.Experiments.Standards.VehicleSim" in rendered
    assert "{" + "boblib_path" + "}" not in rendered


def test_optsim_entrypoints_import() -> None:
    """Catch import-time breakage in the runners the make targets invoke."""
    import importlib

    for module in (
        "StandardSens.pre_screen_sensitivities",
        "StandardSens.refined_response_surfaces",
        "StandardSens.pipeline.aggregator",
        "StandardSens.pipeline.search",
        "StandardSens.solve_setup",
    ):
        importlib.import_module(module)


