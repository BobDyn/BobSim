from __future__ import annotations

from collections import defaultdict
from pathlib import Path
from typing import Any

import matplotlib

matplotlib.use("Agg")

import matplotlib.pyplot as plt  # noqa: E402
import pytest  # noqa: E402
from matplotlib.text import Text  # noqa: E402

from common.reporting.vehicle_review_sections import add_review_suspension_page  # noqa: E402
from optimization.response.pipeline import generator  # noqa: E402
from simulations.envelope import vehicle_yaml  # noqa: E402

ROLL_STIFFNESS_ROWS = (
    "elastic_roll_stiffness_front_Nm_per_rad,40000.0,{status}\n"
    "elastic_roll_stiffness_rear_Nm_per_rad,40000.0,ok\n"
    "arb_roll_stiffness_front_Nm_per_rad,20000.0,ok\n"
    "arb_roll_stiffness_rear_Nm_per_rad,20000.0,ok\n"
    "spring_roll_stiffness_front_Nm_per_rad,20000.0,ok\n"
    "spring_roll_stiffness_rear_Nm_per_rad,20000.0,ok\n"
)


def test_static_balance_free_length_rejects_a_partial_motion_ratio(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    metrics_csv = tmp_path / "four_post_eval_report_metrics.csv"
    metrics_csv.write_text(
        "metric,value,status\n"
        "static_motion_ratio_front,0.62,partial\n"
        "avg_motion_ratio_front,0.63,partial\n"
        "static_motion_ratio_rear,0.71,ok\n",
        encoding="utf-8",
    )
    monkeypatch.setattr(generator, "FOUR_POST_METRICS_CANDIDATES", (metrics_csv,), raising=True)
    context = {"four_post_metrics": generator._load_metrics_csv()}

    assert generator._computed_motion_ratio("rear", context) == pytest.approx(0.71)
    with pytest.raises(ValueError, match="status ok"):
        generator._computed_motion_ratio("front", context)


def _project_lltd_source(tmp_path: Path, status: str) -> str:
    metrics_csv = tmp_path / vehicle_yaml.DEFAULT_FOUR_POST_METRICS.relative_to(vehicle_yaml.REPO_ROOT)
    metrics_csv.parent.mkdir(parents=True, exist_ok=True)
    metrics_csv.write_text("metric,value,status\n" + ROLL_STIFFNESS_ROWS.format(status=status), encoding="utf-8")
    vehicle = {axle: {"actuation": {"stabar": {"rate_n_m_per_rad": 300.0}}} for axle in ("front", "rear")}
    _lltd, summary = vehicle_yaml._project_lltd(vehicle, repo_root=tmp_path)
    return str(summary["lltd_source"])


def test_lltd_source_names_the_roll_stiffness_that_fell_back_to_a_default(tmp_path: Path) -> None:
    assert _project_lltd_source(tmp_path, "ok") == "four_post_report_roll_stiffness"
    source = _project_lltd_source(tmp_path, "partial")
    assert source.startswith("four_post_report_roll_stiffness; defaults for ")
    assert "elastic_roll_stiffness_front_Nm_per_rad" in source


def test_vehicle_review_labels_the_legacy_anti_roll_key_as_net_jacking(monkeypatch: pytest.MonkeyPatch) -> None:
    review: dict[str, Any] = {"suspension": defaultdict(float), "vehicle": defaultdict(float)}
    figures: list[Any] = []

    class Pages:
        def savefig(self, fig: Any) -> None:
            figures.append(fig)

    monkeypatch.setattr(plt, "close", lambda *args, **kwargs: None)
    add_review_suspension_page(Pages(), review)
    monkeypatch.undo()

    labels = [text.get_text() for text in figures[0].findobj(Text)]
    plt.close(figures[0])
    assert not [label for label in labels if "anti-roll" in label.lower()]
    assert "Front net jacking" in labels
