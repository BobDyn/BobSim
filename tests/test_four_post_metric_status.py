from __future__ import annotations

from collections import defaultdict
from typing import Any

import matplotlib

matplotlib.use("Agg")

import matplotlib.pyplot as plt  # noqa: E402
import pytest  # noqa: E402
from matplotlib.text import Text  # noqa: E402

from common.reporting.vehicle_review_sections import add_review_suspension_page  # noqa: E402


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
