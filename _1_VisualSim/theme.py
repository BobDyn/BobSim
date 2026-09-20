"""Qt styling for the BobVis desktop app.

One flat stylesheet, derived from the same :class:`~_1_VisualSim.scene.Palette`
the 3D view and the exported video use, so the window and the file it produces
read as one thing.

Deliberately minimal: no icon set, no gradients, no custom-painted widgets.
Spacing, one accent colour and a single hairline border carry the whole UI.

Two things are borrowed from BobDocs so BobSim's surfaces feel related without
BobVis turning into a branded artefact: the system font stack, and the brand
blue - darkened here from ``#4ea1ff``, which is tuned for that site's dark
ground and washes out as text on this one. Nothing else is shared.
"""

from __future__ import annotations

from dataclasses import dataclass

from _1_VisualSim.scene import LIGHT, Palette


@dataclass(frozen=True)
class UiTheme:
    """Widget-chrome colours that sit around the viewport."""

    palette: Palette
    surface: str
    surface_alt: str
    border: str
    text: str
    text_muted: str
    accent: str
    accent_soft: str
    accent_text: str
    hover: str
    pressed: str


THEME = UiTheme(
    palette=LIGHT,
    surface="#ffffff",
    surface_alt="#f5f7f9",
    border="#dfe4ea",
    text="#1c2430",
    text_muted="#6b7684",
    accent=LIGHT.accent,
    accent_soft="rgba(43, 127, 212, 0.10)",
    accent_text="#ffffff",
    hover="#eef2f7",
    pressed="#e2e8f0",
)

# BobDocs' stack, with Segoe UI promoted since BobSim is developed on Windows.
FONT_STACK = (
    'system-ui, -apple-system, BlinkMacSystemFont, "Segoe UI", "Ubuntu", sans-serif'
)
MONO_STACK = '"Cascadia Mono", "SF Mono", Consolas, "Ubuntu Mono", monospace'


def stylesheet(theme: UiTheme = THEME) -> str:
    """The whole application stylesheet."""
    t = theme
    return f"""
    QWidget {{
        background: {t.surface};
        color: {t.text};
        font-family: {FONT_STACK};
        font-size: 12px;
    }}

    QMainWindow::separator {{ background: {t.border}; width: 1px; height: 1px; }}

    QMenuBar {{ background: {t.surface}; border-bottom: 1px solid {t.border}; padding: 2px 4px; }}
    QMenuBar::item {{ padding: 4px 10px; border-radius: 5px; background: transparent; }}
    QMenuBar::item:selected {{ background: {t.hover}; }}
    QMenu {{ background: {t.surface}; border: 1px solid {t.border}; border-radius: 8px; padding: 4px; }}
    QMenu::item {{ padding: 5px 22px 5px 12px; border-radius: 5px; }}
    QMenu::item:selected {{ background: {t.hover}; }}
    QMenu::separator {{ height: 1px; background: {t.border}; margin: 4px 6px; }}

    QToolBar {{
        background: {t.surface};
        border: none;
        border-bottom: 1px solid {t.border};
        padding: 6px 8px;
        spacing: 4px;
    }}
    QToolBar QLabel {{ color: {t.text_muted}; padding: 0 2px; }}

    QPushButton {{
        background: {t.surface};
        border: 1px solid {t.border};
        border-radius: 6px;
        padding: 4px 10px;
        color: {t.text};
    }}
    QPushButton:hover {{ background: {t.hover}; }}
    QPushButton:pressed {{ background: {t.pressed}; }}
    QPushButton:disabled {{ color: {t.text_muted}; background: {t.surface_alt}; }}
    QPushButton[flat="true"] {{ border-color: transparent; background: transparent; }}
    QPushButton[flat="true"]:hover {{ background: {t.hover}; }}
    /* Toggles report state, so they tint rather than fill; only the export
       button gets a solid accent, because only it is a call to action. */
    QPushButton[toggle="true"] {{ color: {t.text_muted}; }}
    QPushButton[toggle="true"]:checked {{
        background: {t.accent_soft};
        border-color: {t.accent};
        color: {t.accent};
        font-weight: 650;
    }}
    QPushButton[accent="true"] {{
        background: {t.accent};
        border-color: {t.accent};
        color: {t.accent_text};
        font-weight: 650;
    }}
    QPushButton[accent="true"]:hover {{ background: #2470c0; border-color: #2470c0; }}
    QPushButton[accent="true"]:disabled {{
        background: {t.surface_alt}; border-color: {t.border}; color: {t.text_muted};
    }}

    QComboBox, QSpinBox, QDoubleSpinBox, QLineEdit {{
        background: {t.surface};
        border: 1px solid {t.border};
        border-radius: 6px;
        padding: 3px 8px;
        selection-background-color: {t.accent};
        selection-color: {t.accent_text};
    }}
    QComboBox:hover, QSpinBox:hover, QDoubleSpinBox:hover, QLineEdit:hover {{
        border-color: {t.text_muted};
    }}
    QComboBox:focus, QSpinBox:focus, QDoubleSpinBox:focus, QLineEdit:focus {{
        border-color: {t.accent};
    }}
    QComboBox::drop-down {{ border: none; width: 18px; }}
    QComboBox QAbstractItemView {{
        background: {t.surface};
        border: 1px solid {t.border};
        selection-background-color: {t.hover};
        selection-color: {t.text};
        outline: none;
    }}

    QCheckBox {{ spacing: 6px; }}
    QCheckBox::indicator {{
        width: 13px; height: 13px;
        border: 1px solid {t.border};
        border-radius: 4px;
        background: {t.surface};
    }}
    QCheckBox::indicator:checked {{ background: {t.accent}; border-color: {t.accent}; }}

    QSlider::groove:horizontal {{ height: 3px; background: {t.border}; border-radius: 2px; }}
    QSlider::sub-page:horizontal {{ background: {t.accent}; border-radius: 2px; }}
    QSlider::handle:horizontal {{
        background: {t.surface};
        border: 2px solid {t.accent};
        width: 11px; height: 11px;
        margin: -5px 0;
        border-radius: 7px;
    }}
    QSlider::handle:horizontal:hover {{ background: {t.accent}; }}

    QSplitter::handle {{ background: {t.border}; }}
    QSplitter::handle:horizontal {{ width: 1px; }}
    QSplitter::handle:vertical {{ height: 1px; }}

    QScrollArea {{ border: none; }}
    QScrollBar:vertical {{ background: transparent; width: 9px; margin: 0; }}
    QScrollBar::handle:vertical {{
        background: {t.border}; border-radius: 4px; min-height: 24px;
    }}
    QScrollBar::handle:vertical:hover {{ background: {t.text_muted}; }}
    QScrollBar::add-line, QScrollBar::sub-line {{ height: 0; width: 0; }}
    QScrollBar::add-page, QScrollBar::sub-page {{ background: transparent; }}

    QStatusBar {{
        background: {t.surface};
        border-top: 1px solid {t.border};
        color: {t.text_muted};
    }}
    QStatusBar::item {{ border: none; }}

    QProgressBar {{
        background: {t.surface_alt};
        border: 1px solid {t.border};
        border-radius: 6px;
        height: 6px;
        text-align: center;
    }}
    QProgressBar::chunk {{ background: {t.accent}; border-radius: 5px; }}

    QTabWidget::pane {{ border: none; border-left: 1px solid {t.border}; }}
    QTabBar::tab {{
        background: transparent;
        color: {t.text_muted};
        padding: 7px 14px;
        border: none;
        border-bottom: 2px solid transparent;
    }}
    QTabBar::tab:hover {{ color: {t.text}; }}
    QTabBar::tab:selected {{ color: {t.text}; border-bottom-color: {t.accent}; font-weight: 650; }}

    QTreeWidget {{ background: {t.surface}; border: none; }}
    QTreeWidget::item {{ padding: 2px 0; }}
    QTreeWidget::item:selected {{ background: {t.hover}; color: {t.text}; }}
    QHeaderView::section {{
        background: {t.surface};
        color: {t.text_muted};
        border: none;
        border-bottom: 1px solid {t.border};
        padding: 4px 6px;
    }}

    QFrame[role="panel"] {{ background: {t.surface}; border-left: 1px solid {t.border}; }}
    QFrame[role="card"] {{
        background: {t.surface_alt};
        border: 1px solid {t.border};
        border-radius: 10px;
    }}
    QFrame[role="transport"] {{ background: {t.surface}; border-top: 1px solid {t.border}; }}
    QLabel[role="time"] {{ font-family: {MONO_STACK}; color: {t.text}; }}
    QLabel[role="muted"] {{ color: {t.text_muted}; }}
    QLabel[role="heading"] {{ font-weight: 650; }}
    """


def matplotlib_rc(theme: UiTheme = THEME) -> dict[str, object]:
    """rcParams that make embedded plots match the window chrome."""
    t = theme
    return {
        "figure.facecolor": t.surface_alt,
        "axes.facecolor": t.surface_alt,
        "axes.edgecolor": t.border,
        "axes.labelcolor": t.text_muted,
        "axes.labelsize": 8,
        "axes.titlesize": 9,
        "text.color": t.text,
        "xtick.color": t.text_muted,
        "ytick.color": t.text_muted,
        "xtick.labelsize": 7,
        "ytick.labelsize": 7,
        "grid.color": t.border,
        "grid.linestyle": "--",
        "grid.linewidth": 0.5,
        "legend.frameon": False,
        "lines.linewidth": 1.4,
    }
