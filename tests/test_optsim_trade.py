"""The trade study's comparison logic, and the multi-standard plumbing under it.

A trade study is only worth running if its table can be trusted, so these pin the
ways a comparison goes quietly wrong: a delta too small to mean anything read as
a finding, a run that lost cases compared as if it were whole, two changes
assumed to add when they do not, and a metric name that means two things.
"""

from __future__ import annotations

from pathlib import Path
import sys

import pytest

ROOT = Path(__file__).resolve().parents[1]
OPTSIM_DIR = ROOT / "_4_OptSim"
if str(OPTSIM_DIR) not in sys.path:
    sys.path.insert(0, str(OPTSIM_DIR))

pytest.importorskip("scipy", reason="the OptSim pipeline package imports scipy")

from StandardSens import trade_study  # noqa: E402
from StandardSens.pipeline import standards, trade  # noqa: E402
from StandardSens.pipeline.variants import split_cpus, variant_key  # noqa: E402

UNDERSTEER = trade.MetricSpec("SteadyStateEval", "understeer", resolution=0.02)
RISE = trade.MetricSpec("TransientEval", "yaw_rise_time_s", resolution=0.005)
WHOLE = {"n_cases": (8.0, "count"), "n_successful_cases": (8.0, "count")}


def run(understeer: float, rise: float, **overrides) -> dict[str, dict[str, tuple[float, str]]]:
    return {
        "SteadyStateEval": {**WHOLE, "understeer": (understeer, "deg/g"), **overrides},
        "TransientEval": {**WHOLE, "yaw_rise_time_s": (rise, "s")},
    }


def test_a_delta_below_the_resolution_is_shown_but_not_called_a_finding() -> None:
    results = {"baseline": run(0.300, 0.055), "bar": run(0.345, 0.056)}
    by_metric = {c.spec.name: c for c in trade.compare(results, [UNDERSTEER, RISE])}
    assert by_metric["understeer"].verdict == trade.RESOLVED
    assert by_metric["understeer"].delta == pytest.approx(0.045)
    assert by_metric["yaw_rise_time_s"].verdict == trade.BELOW_RESOLUTION
    assert by_metric["yaw_rise_time_s"].delta == pytest.approx(0.001), "still reported"


def test_a_run_that_lost_cases_is_not_compared() -> None:
    """Its fits run through fewer points, so the delta would mix two causes."""
    lossy = run(0.40, 0.055, n_successful_cases=(6.0, "count"))
    results = {"baseline": run(0.30, 0.055), "bar": lossy}
    assert trade.lost_cases(results) == {("bar", "SteadyStateEval"): "2 of 8 cases failed"}
    by_metric = {c.spec.name: c for c in trade.compare(results, [UNDERSTEER, RISE])}
    assert by_metric["understeer"].verdict == trade.NOT_COMPARABLE
    assert by_metric["yaw_rise_time_s"].verdict != trade.NOT_COMPARABLE, "other standard is fine"


def test_a_lossy_baseline_poisons_every_comparison_on_that_standard() -> None:
    results = {"baseline": run(0.30, 0.055, n_successful_cases=(7.0, "count")), "bar": run(0.35, 0.040)}
    verdicts = {c.spec.name: c.verdict for c in trade.compare(results, [UNDERSTEER, RISE])}
    assert verdicts == {"understeer": trade.NOT_COMPARABLE, "yaw_rise_time_s": trade.RESOLVED}


def test_interaction_is_found_for_a_candidate_that_is_two_others_combined() -> None:
    candidates = {"bar": {"rear.bar": 900.0}, "spring": {"front.spring": 21000.0},
                  "both": {"rear.bar": 900.0, "front.spring": 21000.0},
                  "unrelated": {"rear.bar": 700.0}}
    results = {
        "baseline": run(0.300, 0.055),
        "bar": run(0.260, 0.055),        # -0.040
        "spring": run(0.290, 0.055),     # -0.010
        "both": run(0.200, 0.055),       # -0.100, not the -0.050 the parts predict
        "unrelated": run(0.280, 0.055),
    }
    found = trade.interactions(candidates, trade.compare(results, [UNDERSTEER]))
    assert [(i.combined, i.parts) for i in found] == [("both", ("bar", "spring"))]
    assert found[0].value == pytest.approx(-0.050)
    assert found[0].stacks is False, "0.05 of unexplained understeer is five resolutions"


def test_changes_that_simply_add_are_reported_as_stacking() -> None:
    candidates = {"a": {"x": 1.0}, "b": {"y": 1.0}, "ab": {"x": 1.0, "y": 1.0}}
    results = {"baseline": run(0.30, 0.055), "a": run(0.26, 0.055), "b": run(0.29, 0.055),
               "ab": run(0.251, 0.055)}
    (found,) = trade.interactions(candidates, trade.compare(results, [UNDERSTEER]))
    assert found.value == pytest.approx(0.001) and found.stacks is True


def test_overlapping_changes_are_not_mistaken_for_a_combination() -> None:
    """`ab` sets x to a different value than `a` does, so it is not a + b."""
    candidates = {"a": {"x": 1.0}, "b": {"y": 1.0}, "ab": {"x": 2.0, "y": 1.0}}
    results = {n: run(0.3, 0.055) for n in ("baseline", "a", "b", "ab")}
    assert trade.interactions(candidates, trade.compare(results, [UNDERSTEER])) == []


def test_an_unknown_metric_names_what_was_probably_meant() -> None:
    results = {"baseline": run(0.3, 0.055), "bar": run(0.3, 0.055)}
    with pytest.raises(KeyError, match="understeer"):
        trade.compare(results, [trade.MetricSpec("SteadyStateEval", "understeer_grad")])


def test_a_name_reported_per_group_must_be_asked_for_by_group(tmp_path: Path) -> None:
    csv_path = tmp_path / "metrics.csv"
    csv_path.write_text(
        "standard,group,metric,value,units,description\n"
        "T,step,yaw_gain_dc,2.10,(rad/s)/rad,\n"
        "T,frequency,yaw_gain_dc,2.30,(rad/s)/rad,\n"
        "T,step,yaw_overshoot_pct,16.6,%,\n"
        "T,step,yaw_overshoot_pct,16.6,%,\n"  # TransientEval really does write this twice
    )
    metrics = standards.read_metrics(csv_path)
    assert "yaw_gain_dc" not in metrics, "the bare name would silently mean the last row"
    assert metrics["step.yaw_gain_dc"][0] == 2.10 and metrics["frequency.yaw_gain_dc"][0] == 2.30
    assert metrics["yaw_overshoot_pct"] == (16.6, "%"), "an identical repeat is one metric"

    results = {"baseline": {"TransientEval": {**WHOLE, **metrics}}, "bar": {"TransientEval": {**WHOLE, **metrics}}}
    with pytest.raises(KeyError, match=r"name one of: \['frequency.yaw_gain_dc', 'step.yaw_gain_dc'\]"):
        trade.compare(results, [trade.MetricSpec("TransientEval", "yaw_gain_dc")])


def test_a_metric_repeated_with_conflicting_values_is_an_error(tmp_path: Path) -> None:
    csv_path = tmp_path / "metrics.csv"
    csv_path.write_text("metric,value\nroll_gain,0.04\nroll_gain,0.05\n")
    with pytest.raises(ValueError, match="twice with different values"):
        standards.read_metrics(csv_path)


def test_every_registered_standard_exists_and_shares_the_vehicle_sim_executable() -> None:
    import yaml

    for standard in standards.STANDARDS.values():
        assert standard.sim_path.is_file(), standard.sim_path
        config = yaml.safe_load(standard.config_path.read_text())
        assert config["simulation"]["exec_name"] == standards.VEHICLE_SIM_MODEL, (
            f"{standard.name} runs a different model, so one compile cannot serve it"
        )
    with pytest.raises(KeyError, match="FourPostSim"):
        standards.get_standard("FourPostEval")


def test_a_standards_config_is_written_beside_the_variant_not_over_the_shared_one(tmp_path: Path) -> None:
    standard = standards.get_standard("TransientEval")
    before = standard.config_path.read_bytes()
    config_path, metrics_csv = standards.write_config(
        standard, variant_dir=tmp_path, build_dir=tmp_path / "build", render_report=False, max_workers=6
    )
    import yaml

    written = yaml.safe_load(config_path.read_text())
    assert standard.config_path.read_bytes() == before
    assert written["simulation"]["build_dir"] == str(tmp_path / "build")
    assert written["report"]["enabled"] is False and written["execution"]["max_workers"] == 6
    assert metrics_csv == tmp_path / "results/TransientEval/transient_eval_report_metrics.csv"


def test_study_candidates_are_validated_before_anything_is_compiled() -> None:
    variables = {"rear.bar": {"range": [300.0, 900.0]}}
    good = trade_study.load_candidates({"candidates": {"stiff": {"rear.bar": 800}}}, variables)
    assert good == {"stiff": {"rear.bar": 800.0}}
    with pytest.raises(KeyError, match="not variables in vehicle_architecture.yaml"):
        trade_study.load_candidates({"candidates": {"x": {"wheelbase": 1.6}}}, variables)
    with pytest.raises(ValueError, match="always included"):
        trade_study.load_candidates({"candidates": {"baseline": {"rear.bar": 800}}}, variables)
    with pytest.raises(ValueError, match="changes nothing"):
        trade_study.load_candidates({"candidates": {"same": {}}}, variables)


def test_the_example_study_names_real_standards_and_is_loadable() -> None:
    import yaml

    study = yaml.safe_load(trade_study.DEFAULT_STUDY.read_text())
    specs = trade_study.load_specs(study)
    assert {s.standard for s in specs} <= set(standards.STANDARDS)
    assert all(s.resolution and s.resolution > 0 for s in specs)


def test_cpus_go_to_concurrent_runs_until_each_would_be_starved() -> None:
    assert split_cpus(9, 12) == (3, 4)
    assert split_cpus(1, 12) == (1, 12), "a lone run gets every CPU"
    assert split_cpus(2, 12) == (2, 6)
    assert split_cpus(5, 2) == (1, 2), "never zero concurrent runs"


def test_float_noise_does_not_split_one_vehicle_into_two_cache_entries() -> None:
    assert variant_key({"b": 0.1 + 0.2, "a": 1.0}) == variant_key({"a": 1.0, "b": 0.3})
    assert variant_key({}) != variant_key({"a": 1.0})
