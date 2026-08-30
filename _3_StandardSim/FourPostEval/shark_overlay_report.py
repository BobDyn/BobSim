"""Overlay a SHARK-imported car against the Orion baseline on the kinematic curves.

The primary product is a *kinematics* overlay: every curve in the app's
`KINEMATIC_CURVE_META` registry, solved straight from the hardpoints, for both
axles and both sweeps. No Modelica build is needed, because the kinematic solver
reads only `suspension`, `steering` and `wheel` - the anti-roll bar, bellcrank and
dampers take no part in it.

The four-post force sim remains available behind `--four-post`. It is secondary and
experimental: it depends on actuation data that this workflow maintains outside
BobSim, so its numbers can conflate a hardpoint change with an ARB or damper change.

Baseline is `vehicle.yml` (Orion) and is never written to. The imported car is
per-run output: point `--shark` at any .shk and it is rebuilt at `--variant`
(`vehicle_2027.yml` by default, gitignored). Importing a second axle merges into
whatever is already there, so a later front file lands beside an imported rear
without re-running it, but nothing about that file is expected to survive the next
import of a different .shk.
"""

from __future__ import annotations

import argparse
import contextlib
import copy
import json
import os
import shutil
import subprocess
import sys
from pathlib import Path
from collections.abc import Sequence
from typing import Any, Iterator

import numpy as np
import yaml

from _0_Utils.shark_import import (
    Z_DEPENDENT_CURVE_IDS,
    datum_gate,
    import_shark,
    write_datum_sidecar,
    write_vehicle,
)
from _0_Utils.kin_py.kinematics import DEFAULT_ROLL_DEG, DEFAULT_SWEEP_M
from _0_Utils.vehicle_io import load_yaml, repo_root, vehicle_yaml_path
from _5_App.kinematics import KINEMATIC_CURVE_META, kinematic_curves_payload
from _5_App.modelica_generator import generate_modelica_stack, modelica_stack_status_payload


ROOT = repo_root()
VEHICLE_YAML = vehicle_yaml_path()
DEFAULT_VARIANT_YAML = ROOT / "vehicle_2027.yml"
BUILD_DIR = ROOT / "_3_StandardSim/BuildBobLib/FourPostSim"
GEOMETRY_STAMP = BUILD_DIR / ".bobsim_geometry_stamp.json"
OUT_DIR = ROOT / "_3_StandardSim/generated_results"

BASELINE_LABEL = "Orion"
VARIANT_LABEL = "2027"

# Validated categorical slots 1 and 2 (see dataviz palette).
# node scripts/validate_palette.js "#2a78d6,#eb6834" --mode light -> ALL CHECKS PASS
COLOR_BASELINE = "#2a78d6"
COLOR_VARIANT = "#eb6834"
INK = "#1a1a19"
MUTED = "#6b6b68"
GRID = "#e4e4e1"
SURFACE = "#fcfcfb"
WARN = "#a8341a"

# How much a curve must move before it is worth an engineer's attention, in the
# curve's own units. Ranking on delta-over-baseline-range alone is unusable on a
# rear axle, where caster and trail are nearly flat and a change of a hundredth of
# a degree scores higher than a real camber change. These are the defaults; both
# are overridable so a team can rank against its own build tolerances.
DEFAULT_TOLERANCES = {"deg": 0.05, "mm": 0.5}
HEADLINE_PANEL_LIMIT = 8

# Rear "caster" is the registry's label for a steering-axis angle that no rear
# corner steers about. Renaming it in the report avoids implying the rear wheels
# are steered, without touching the shared registry the app also reads.
REAR_RELABEL = {
    "caster": "Kingpin side-view inclination",
}


def _rear_relabel(meta: dict[str, str], axle: str) -> str | None:
    """The replacement term for this curve on this axle, if it needs one."""
    if axle != "rear":
        return None
    return next(
        (term for token, term in REAR_RELABEL.items() if token in meta["id"]), None
    )


def display_label(meta: dict[str, str], axle: str) -> str:
    """Curve title as shown to a reader, corrected for the axle it describes."""
    term = _rear_relabel(meta, axle)
    if term is None:
        return meta["label"]
    return f"{'Bump' if meta['id'].startswith('bump') else 'Roll'} {term}"


def display_y_label(meta: dict[str, str], axle: str) -> str:
    """Axis label, relabelled on the same terms as the title.

    Shares `_rear_relabel` with `display_label` so the two cannot drift: a plot
    titled "Kingpin side-view inclination" whose y axis reads "Caster" is worse
    than not renaming at all.
    """
    return _rear_relabel(meta, axle) or meta["y_label"]


class StaleGeometryError(RuntimeError):
    """Raised when the built simulator does not match the current geometry."""


# --------------------------------------------------------------------------
# Kinematics (primary)
# --------------------------------------------------------------------------


def sweep_including_zero(reference: Sequence[float], points: int = 21) -> tuple[float, ...]:
    """Rebuild a sweep over the same range with the design position on a grid point.

    The app defaults span the range in an even number of steps, so zero falls
    between samples: the bump grid's nearest point is 2.1 mm of jounce. Any
    "value at design position" taken from that grid is an extrapolation, which is
    the one number a suspension engineer is most likely to read off directly. An
    odd count puts the midpoint exactly on zero, and it is snapped to a hard 0.0 so
    float accumulation cannot leave it at 1e-18.
    """
    low, high = min(reference), max(reference)
    if points % 2 == 0:
        points += 1
    step = (high - low) / (points - 1)
    values = [low + step * index for index in range(points)]
    values[points // 2] = 0.0
    return tuple(values)


BUMP_SWEEP_M = sweep_including_zero(DEFAULT_SWEEP_M)
ROLL_SWEEP_DEG = sweep_including_zero(DEFAULT_ROLL_DEG)


def kinematic_payload(vehicle_path: Path) -> dict[str, Any]:
    """Solve the full registry curve deck over the app's ranges, sampling zero.

    Ranges match the app registry defaults so the curves stay comparable to the
    app's kinematics view; only the point count differs, to put the design
    position on a sample rather than between two.
    """
    vehicle = load_yaml(vehicle_path)
    return kinematic_curves_payload(vehicle, BUMP_SWEEP_M, ROLL_SWEEP_DEG)


def _curve_series(
    payload: dict[str, Any], axle: str, meta: dict[str, str]
) -> tuple[list[float], list[float | None]] | None:
    axle_payload = payload.get("axles", {}).get(axle) or {}
    curves = axle_payload.get("curves") or {}
    values = curves.get(meta["id"])
    x = payload.get("x_axes", {}).get(meta["x_id"])
    if not values or not x:
        return None
    size = min(len(x), len(values))
    return list(x[:size]), list(values[:size])


def _at_design_position(x: Sequence[float], y: Sequence[float | None]) -> float:
    """Value where the sweep passes through zero, read off rather than fitted."""
    for index, value in enumerate(x):
        if value == 0.0 and index < len(y) and y[index] is not None:
            return float(y[index])  # type: ignore[arg-type]
    return float("nan")


def _working_slope(x: Sequence[float], y: Sequence[float | None]) -> float:
    """Least-squares gradient over the whole swept range, in curve units per x unit."""
    pairs = [(a, b) for a, b in zip(x, y) if b is not None]
    if len(pairs) < 2:
        return float("nan")
    xs = np.asarray([a for a, _ in pairs], dtype=float)
    ys = np.asarray([b for _, b in pairs], dtype=float)
    mask = np.isfinite(xs) & np.isfinite(ys)
    if mask.sum() < 2:
        return float("nan")
    slope, _intercept = np.polyfit(xs[mask], ys[mask], 1)
    return float(slope)


def _delta_score(
    base: Sequence[float | None], variant: Sequence[float | None]
) -> dict[str, float] | None:
    """Peak divergence between two curves, in curve units and relative to range.

    Both are reported because neither is sufficient alone. The absolute peak is the
    engineering quantity, but degrees and millimetres cannot be ranked against each
    other; the ratio makes them comparable. The ratio alone is misleading on a rear
    axle, where the baseline caster/trail/scrub curves are nearly flat and any change
    divides by ~zero into a meaningless four-digit percentage.
    """
    pairs = [(b, v) for b, v in zip(base, variant) if b is not None and v is not None]
    if len(pairs) < 2:
        return None
    peak = max(abs(v - b) for b, v in pairs)
    base_values = [b for b, _ in pairs]
    span = max(base_values) - min(base_values)
    if peak <= 1e-9:
        ratio = 0.0
    elif span <= 1e-9:
        ratio = float("inf")  # flat baseline; any movement at all is notable
    else:
        ratio = peak / span
    return {"peak": peak, "span": span, "ratio": ratio}


def curve_metrics(
    payloads: dict[str, dict[str, Any]],
    withheld: frozenset[str],
    tolerances: dict[str, float],
) -> list[dict[str, Any]]:
    """Per (curve, axle): design-position values, working slopes, and significance.

    Significance is `peak delta / engineering tolerance` - how many times the
    change exceeds what the team calls negligible in that unit. That is a
    judgement an engineer can argue with, unlike delta-over-baseline-range, which
    reports a flat rear caster curve moving by a hundredth of a degree as a larger
    finding than a real camber change.
    """
    rows: list[dict[str, Any]] = []
    for meta in KINEMATIC_CURVE_META:
        for axle in ("front", "rear"):
            base = _curve_series(payloads[BASELINE_LABEL], axle, meta)
            var = _curve_series(payloads[VARIANT_LABEL], axle, meta)
            if base is None or var is None:
                continue
            score = _delta_score(base[1], var[1])
            if score is None:
                continue
            tol = tolerances.get(meta["unit"], 0.0)
            base_design = _at_design_position(base[0], base[1])
            var_design = _at_design_position(var[0], var[1])
            rows.append({
                "meta": meta,
                "axle": axle,
                "label": display_label(meta, axle),
                "unit": meta["unit"],
                "x_unit": meta["x_unit"],
                "withheld": meta["id"] in withheld,
                "baseline_design": base_design,
                "variant_design": var_design,
                "design_delta": var_design - base_design,
                "baseline_slope": _working_slope(base[0], base[1]),
                "variant_slope": _working_slope(var[0], var[1]),
                "peak": score["peak"],
                "span": score["span"],
                "ratio": score["ratio"],
                "tolerance": tol,
                "significance": (score["peak"] / tol) if tol > 0 else float("inf"),
            })
    rows.sort(key=lambda row: (row["withheld"], -row["significance"]))
    return rows


# --------------------------------------------------------------------------
# Figure helpers
# --------------------------------------------------------------------------


def _style_axis(ax: Any, xlabel: str, ylabel: str, title: str) -> None:
    ax.set_title(title, fontsize=9, color=INK, pad=6, loc="left")
    ax.set_xlabel(xlabel, fontsize=7.5, color=MUTED)
    ax.set_ylabel(ylabel, fontsize=7.5, color=MUTED)
    ax.grid(True, color=GRID, linewidth=0.8, zorder=0)
    ax.set_axisbelow(True)
    for spine in ("top", "right"):
        ax.spines[spine].set_visible(False)
    for spine in ("left", "bottom"):
        ax.spines[spine].set_color(GRID)
    ax.tick_params(colors=MUTED, labelsize=7, length=0)


def _plot_curve(
    ax: Any,
    payloads: dict[str, dict[str, Any]],
    meta: dict[str, str],
    axle: str,
    *,
    show_legend: bool,
) -> None:
    series = {
        label: _curve_series(payload, axle, meta) for label, payload in payloads.items()
    }
    drawn = {label: value for label, value in series.items() if value is not None}
    identical = False
    if len(drawn) == 2:
        base_y = drawn[BASELINE_LABEL][1]
        var_y = drawn[VARIANT_LABEL][1]
        identical = all(
            (b is None and v is None) or (b is not None and v is not None and abs(v - b) <= 1e-9)
            for b, v in zip(base_y, var_y)
        )

    for label, color in ((BASELINE_LABEL, COLOR_BASELINE), (VARIANT_LABEL, COLOR_VARIANT)):
        if label not in drawn:
            continue
        x, y = drawn[label]
        xs = np.asarray(x, dtype=float)
        ys = np.asarray([np.nan if value is None else value for value in y], dtype=float)
        ax.plot(
            xs, ys, color=color, linewidth=1.8, label=label, zorder=3,
            linestyle=(0, (4, 3)) if identical and label == VARIANT_LABEL else "-",
        )

    _style_axis(
        ax,
        f"{meta['x_label']} ({meta['x_unit']})",
        f"{display_y_label(meta, axle)} ({meta['unit']})",
        f"{axle.title()} - {display_label(meta, axle)}",
    )
    if identical:
        ax.text(
            0.5, 0.06, "curves coincide - axle unchanged by this import",
            transform=ax.transAxes, fontsize=6.5, color=MUTED, ha="center",
        )
    if show_legend:
        ax.legend(frameon=False, fontsize=7, labelcolor=INK)


def _text_page(pdf: Any, title: str, lines: Sequence[str], *, warn: bool = False) -> None:
    import matplotlib.pyplot as plt

    fig = plt.figure(figsize=(11.0, 8.5), facecolor=SURFACE)
    fig.text(0.04, 0.94, title, fontsize=15, color=INK, va="top", ha="left")
    body = "\n".join(lines)
    fig.text(
        0.04, 0.88, body, fontsize=9, color=WARN if warn else MUTED,
        va="top", ha="left", wrap=True,
    )
    pdf.savefig(fig, facecolor=SURFACE)
    plt.close(fig)


def _grid_page(
    pdf: Any,
    panels: Sequence[tuple[dict[str, str], str]],
    payloads: dict[str, dict[str, Any]],
    title: str,
    *,
    ncols: int = 2,
    nrows: int = 3,
) -> None:
    import matplotlib.pyplot as plt

    fig, axes = plt.subplots(nrows, ncols, figsize=(11.0, 8.5), facecolor=SURFACE)
    axes = np.atleast_2d(axes)
    for ax in axes.flat:
        ax.set_facecolor(SURFACE)
        ax.set_visible(False)

    for index, (meta, axle) in enumerate(panels):
        ax = axes.flat[index]
        ax.set_visible(True)
        _plot_curve(ax, payloads, meta, axle, show_legend=index == 0)

    fig.suptitle(title, fontsize=12, color=INK, x=0.02, ha="left", y=0.985)
    fig.tight_layout(rect=(0, 0, 1, 0.955))
    pdf.savefig(fig, facecolor=SURFACE)
    plt.close(fig)


def _table_page(
    pdf: Any,
    title: str,
    headers: Sequence[str],
    rows: Sequence[Sequence[str]],
    *,
    subtitle: str = "",
    col_widths: Sequence[float] | None = None,
) -> None:
    """Render a real table: ruled header, aligned columns, zebra striping."""
    import matplotlib.pyplot as plt

    fig = plt.figure(figsize=(11.0, 8.5), facecolor=SURFACE)
    fig.text(0.04, 0.95, title, fontsize=14, color=INK, va="top", ha="left")
    if subtitle:
        fig.text(0.04, 0.905, subtitle, fontsize=8, color=MUTED, va="top", ha="left")

    ax = fig.add_axes((0.04, 0.05, 0.92, 0.82))
    ax.axis("off")
    table = ax.table(
        cellText=[list(row) for row in rows] or [["-"] * len(headers)],
        colLabels=list(headers),
        colWidths=list(col_widths) if col_widths else None,
        cellLoc="right",
        loc="upper center",
    )
    table.auto_set_font_size(False)
    table.set_fontsize(7)
    table.scale(1.0, 1.25)

    for (row, col), cell in table.get_celld().items():
        cell.set_edgecolor(GRID)
        cell.set_linewidth(0.6)
        if row == 0:
            cell.set_facecolor(GRID)
            cell.set_text_props(color=INK, fontweight="bold")
            cell.set_height(cell.get_height() * 1.1)
        else:
            cell.set_facecolor(SURFACE if row % 2 else "#f4f4f1")
            cell.set_text_props(color=INK)
        if col == 0:
            cell.set_text_props(ha="left")
            cell.get_text().set_x(0.02)

    pdf.savefig(fig, facecolor=SURFACE)
    plt.close(fig)


def _fmt(value: float, unit: str = "", places: int = 3) -> str:
    if value is None or not np.isfinite(value):
        return "n/a"
    return f"{value:.{places}f}{(' ' + unit) if unit else ''}"


def build_report(
    payloads: dict[str, dict[str, Any]],
    notes: Sequence[str],
    withheld: frozenset[str],
    metrics: Sequence[dict[str, Any]],
    four_post: dict[str, Any] | None,
    out_path: Path,
    tolerances: dict[str, float],
) -> Path:
    import matplotlib
    matplotlib.use("Agg")
    import matplotlib.pyplot as plt  # noqa: F401  (backend must be set first)
    from matplotlib.backends.backend_pdf import PdfPages

    out_path.parent.mkdir(parents=True, exist_ok=True)
    publishable = [row for row in metrics if not row["withheld"]]
    headline = [
        (row["meta"], row["axle"]) for row in publishable if row["significance"] >= 1.0
    ][:HEADLINE_PANEL_LIMIT]

    tol_text = ", ".join(f"{unit}: {value:g}" for unit, value in sorted(tolerances.items()))

    with PdfPages(out_path) as pdf:
        cover = [f"{BASELINE_LABEL} (vehicle.yml) vs {VARIANT_LABEL} kinematic curves.", ""]
        cover += [f"- {note}" for note in notes]
        cover += [
            "",
            f"Engineering tolerances used for ranking - {tol_text}.",
            "A curve is called significant when its peak change exceeds one tolerance.",
            "",
            "Design position (zero) is an explicit sample point in both sweeps: "
            f"bump {len(BUMP_SWEEP_M)} points over "
            f"{min(BUMP_SWEEP_M) * 1000.0:+.0f}..{max(BUMP_SWEEP_M) * 1000.0:+.0f} mm, "
            f"roll {len(ROLL_SWEEP_DEG)} points over "
            f"{min(ROLL_SWEEP_DEG):+.2f}..{max(ROLL_SWEEP_DEG):+.2f} deg.",
        ]
        if withheld:
            cover += ["", "DATUM GATE CLOSED - the following curves are withheld:"]
            cover += [f"  - {curve_id}" for curve_id in sorted(withheld)]
        _text_page(pdf, "SHARK import overlay", cover, warn=bool(withheld))

        # Summary table: design-position values and working-range slopes. Paginated
        # because 26 curves across two axles is 52 rows, which does not fit a page.
        summary_rows = [
            (
                row["label"], row["axle"],
                _fmt(row["baseline_design"], row["unit"]),
                _fmt(row["variant_design"], row["unit"]),
                _fmt(row["design_delta"], row["unit"]),
                _fmt(row["baseline_slope"]) + f" /{row['x_unit']}",
                _fmt(row["variant_slope"]) + f" /{row['x_unit']}",
                _fmt(row["peak"], row["unit"]),
                "withheld" if row["withheld"] else _fmt(row["significance"], places=1),
            )
            for row in metrics
        ]
        per_page = 26
        pages = max(1, (len(summary_rows) + per_page - 1) // per_page)
        for index in range(pages):
            chunk = summary_rows[index * per_page:(index + 1) * per_page]
            suffix = f" ({index + 1}/{pages})" if pages > 1 else ""
            _table_page(
                pdf,
                f"Summary - design position and working-range gradient{suffix}",
                ("Curve", "Axle", f"{BASELINE_LABEL} @0", f"{VARIANT_LABEL} @0", "delta @0",
                 f"{BASELINE_LABEL} slope", f"{VARIANT_LABEL} slope", "peak delta", "x tol"),
                chunk,
                subtitle=(
                    "Values at zero are read from the sweep, not extrapolated. Slope is the "
                    "least-squares gradient over the full swept range. 'x tol' is how many "
                    "engineering tolerances the peak change spans."
                ),
                col_widths=[0.26, 0.06, 0.10, 0.10, 0.10, 0.11, 0.11, 0.09, 0.07],
            )

        if headline:
            for start in range(0, len(headline), 6):
                _grid_page(
                    pdf, headline[start:start + 6], payloads,
                    "Headline - changes beyond engineering tolerance"
                    + (" (continued)" if start else ""),
                )
        else:
            _text_page(
                pdf, "Headline",
                [f"No published curve moved by more than one engineering tolerance ({tol_text})."],
            )

        appendix = [
            (meta, axle)
            for meta in KINEMATIC_CURVE_META
            if meta["id"] not in withheld
            for axle in ("front", "rear")
        ]
        for start in range(0, len(appendix), 6):
            page = start // 6 + 1
            total = (len(appendix) + 5) // 6
            _grid_page(
                pdf, appendix[start:start + 6], payloads,
                f"Appendix - full curve deck ({page}/{total})",
            )

        if four_post is not None:
            _text_page(pdf, "Four-post (experimental, secondary)", four_post["lines"], warn=True)
            if four_post.get("rows"):
                _table_page(
                    pdf,
                    "Four-post - jacking geometry",
                    ("Metric", BASELINE_LABEL, VARIANT_LABEL, "Delta"),
                    four_post["rows"],
                    subtitle=(
                        "Percentages are jacking geometry, not roll stiffness. "
                        f"Actuation mode: {four_post['mode']}."
                    ),
                    col_widths=[0.46, 0.18, 0.18, 0.18],
                )

    return out_path


# --------------------------------------------------------------------------
# Markdown summary
# --------------------------------------------------------------------------


def write_summary_md(
    notes: Sequence[str],
    withheld: frozenset[str],
    metrics: Sequence[dict[str, Any]],
    four_post: dict[str, Any] | None,
    path: Path,
    tolerances: dict[str, float],
) -> Path:
    tol_text = ", ".join(f"{unit}: {value:g}" for unit, value in sorted(tolerances.items()))
    lines = [f"# {VARIANT_LABEL} vs {BASELINE_LABEL} - kinematic overlay", "", "## Notes", ""]
    lines += [f"- {note}" for note in notes]

    if withheld:
        lines += [
            "",
            "## Withheld by the datum gate",
            "",
            "The vertical datum could not be vouched for, so every z-dependent output is",
            "suppressed - roll-centre height and migration, absolute RC and IC z, front-view",
            "swing arm, and the four-post jacking metrics.",
            "",
        ]
        lines += [f"- `{curve_id}`" for curve_id in sorted(withheld)]

    published = [row for row in metrics if not row["withheld"]]
    significant = [row for row in published if row["significance"] >= 1.0]
    lines += [
        "",
        "## Design position and working-range gradient",
        "",
        f"Engineering tolerances: {tol_text}. Significance is peak change divided by the",
        "tolerance for that unit, so it answers 'how many times bigger than negligible'.",
        "Values at zero are read from an explicit sample, not extrapolated.",
        "",
        "| Curve | Axle | Orion @0 | 2027 @0 | delta @0 | Orion slope | 2027 slope | Peak | x tol |",
        "|---|---|---:|---:|---:|---:|---:|---:|---:|",
    ]
    for row in metrics:
        sig = "withheld" if row["withheld"] else f"{row['significance']:.1f}"
        unit, x_unit = row["unit"], row["x_unit"]
        lines.append(
            f"| {row['label']} | {row['axle']} "
            f"| {_fmt(row['baseline_design'], unit)} | {_fmt(row['variant_design'], unit)} "
            f"| {_fmt(row['design_delta'], unit)} "
            f"| {_fmt(row['baseline_slope'])} /{x_unit} | {_fmt(row['variant_slope'])} /{x_unit} "
            f"| {_fmt(row['peak'], unit)} | {sig} |"
        )

    unchanged = [row for row in published if row["peak"] == 0.0]
    lines += [
        "",
        f"{len(significant)} of {len(published)} published curve/axle pairs exceed one "
        f"engineering tolerance; {len(unchanged)} are bit-identical between the two cars "
        "(the axle this import does not touch).",
    ]

    if four_post is not None:
        lines += ["", "## Four-post (experimental, secondary)", ""] + list(four_post["lines"])
        if four_post.get("rows"):
            lines += [
                "",
                f"| Metric | {BASELINE_LABEL} | {VARIANT_LABEL} | Delta |",
                "|---|---:|---:|---:|",
            ]
            lines += [f"| {r[0]} | {r[1]} | {r[2]} | {r[3]} |" for r in four_post["rows"]]
        restored = four_post.get("restored")
        if restored:
            lines += [
                "",
                "### Restored Modelica state",
                "",
                f"- BobLib leftovers: `{restored['boblib_leftovers'] or 'none'}`",
                f"- stamp present: `{restored['stamp_present']}`",
                f"- executable present: `{restored['executable_present']}`",
            ]

    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")
    return path


# --------------------------------------------------------------------------
# Four-post (opt-in, secondary)
# --------------------------------------------------------------------------


def four_post_signature(vehicle_path: Path) -> tuple[str, dict[str, Any]]:
    """Regenerate the stack and return the four-post content signature."""
    generate_modelica_stack(vehicle_path, root=ROOT)
    status = modelica_stack_status_payload(vehicle_path, ROOT)
    if status["state"] != "written":
        stale = [f["kind"] for f in status["files"] if not f["current"]]
        raise StaleGeometryError(
            f"Modelica stack did not land cleanly (state={status['state']!r}). "
            f"Files not matching the generated content: {', '.join(stale) or 'none'}. "
            "Refusing to run the sim."
        )
    return status["signatures"]["four_post"]["generated"], status


def read_stamp() -> str | None:
    if not GEOMETRY_STAMP.is_file():
        return None
    try:
        return str(json.loads(GEOMETRY_STAMP.read_text(encoding="utf-8"))["signature"])
    except Exception:
        return None


def write_stamp(signature: str, vehicle_name: str) -> None:
    GEOMETRY_STAMP.parent.mkdir(parents=True, exist_ok=True)
    GEOMETRY_STAMP.write_text(
        json.dumps({"signature": signature, "vehicle": vehicle_name}, indent=2),
        encoding="utf-8",
    )


def host_can_run(exe: Path) -> bool:
    """Whether this host can execute the compiled simulator at all.

    The Modelica build runs inside the Linux container, so on a Windows host it
    produces an ELF binary the host cannot exec. Left undetected that surfaces
    several layers down as `OSError: [WinError 193] %1 is not a valid Win32
    application`, from inside the eval runner, long after the expensive build.
    """
    try:
        magic = exe.open("rb").read(4)
    except OSError:
        return False
    if magic[:4] == b"\x7fELF":
        return os.name != "nt"
    if magic[:2] == b"MZ":
        return os.name == "nt"
    return True


def assert_four_post_is_runnable_here() -> None:
    """Refuse before building if the result could not be executed afterwards."""
    if os.name != "nt" or Path("/.dockerenv").exists():
        return
    raise StaleGeometryError(
        "The four-post path cannot run on a Windows host.\n"
        "The Modelica stack is compiled inside the Linux container, so the simulator "
        "it produces is an ELF binary this host cannot execute; the run would fail "
        "part-way through with WinError 193 after a long build.\n"
        "Run the whole overlay inside the container instead:\n"
        "  make shark-overlay ARGS=--four-post\n"
        "which routes through `docker compose run` when --four-post is present. The "
        "kinematic overlay is unaffected and still runs natively."
    )


def build_four_post() -> None:
    try:
        result = subprocess.run(
            ["make", "standard-build-four-post"],
            cwd=ROOT,
            capture_output=True,
            text=True,
        )
    except OSError as exc:
        # A missing or unlaunchable `make` is a refusal, not a crash: the caller
        # relies on StaleGeometryError to trigger restoration and a clean exit.
        raise StaleGeometryError(
            f"Could not launch `make standard-build-four-post`: {exc}. "
            "The four-post build could not be proven, so nothing is reported."
        ) from exc
    if result.returncode != 0:
        raise StaleGeometryError(
            "Four-post build failed, so the simulator cannot be proven to match the "
            "current geometry. Refusing to report.\n"
            f"--- stdout ---\n{result.stdout[-2000:]}\n--- stderr ---\n{result.stderr[-2000:]}"
        )


def four_post_executable() -> Path | None:
    for name in (
        "BobLib.Experiments.Standards.FourPostSim",
        "BobLib.Experiments.Standards.FourPostSim.exe",
    ):
        candidate = BUILD_DIR / name
        if candidate.is_file():
            return candidate
    return None


def assert_binary_is_executable_here(label: str) -> None:
    exe = four_post_executable()
    if exe is not None and not host_can_run(exe):
        raise StaleGeometryError(
            f"[{label}] The compiled simulator at {exe.name} was built for a different "
            "platform than this host, so it cannot be executed here. Run the overlay "
            "inside the container: make shark-overlay ARGS=--four-post"
        )


def assert_binary_consumed_geometry(status: dict[str, Any], label: str) -> None:
    """Prove the executable was produced *after* the geometry it claims to model.

    Deliberately independent of the makefile: if a dependency is ever missing
    again, `make` reports success without recompiling, and stamping the new
    signature onto that untouched binary would launder stale geometry into a
    report that looks clean. Compare timestamps instead of trusting the build.
    """
    exe = four_post_executable()
    if exe is None:
        raise StaleGeometryError(
            f"[{label}] Build reported success but no four-post executable exists in {BUILD_DIR}."
        )
    newest_geometry = float(status.get("latest_modified") or 0.0)
    built_at = exe.stat().st_mtime
    if newest_geometry and built_at < newest_geometry:
        raise StaleGeometryError(
            f"[{label}] The four-post executable predates the geometry it should model.\n"
            f"  executable mtime : {built_at:.0f}\n"
            f"  geometry mtime   : {newest_geometry:.0f}\n"
            "`make` reported success without recompiling, so the binary still holds the "
            "previous hardpoints. Check the build dependencies for the generated record."
        )


def invalidate_build_artifacts() -> list[str]:
    """Drop the stamp and the compiled simulator.

    Regenerating the records is not enough on its own: the executable on disk was
    compiled from whichever car ran last, and the stamp asserts it matches. Leaving
    either behind lets a later run pair the restored vehicle.yml with hardpoints
    that are no longer in it. Removing both forces a rebuild, which is the only
    state in which the pairing is provable.
    """
    removed: list[str] = []
    if GEOMETRY_STAMP.is_file():
        GEOMETRY_STAMP.unlink()
        removed.append(GEOMETRY_STAMP.name)
    exe = four_post_executable()
    if exe is not None:
        exe.unlink()
        removed.append(exe.name)
    return removed


BOBLIB_PACKAGE = ROOT / "_0_Utils/external/BobLib/BobLib"

# Everywhere the generator writes inside BobLib. Directories are snapshotted whole
# so that files it *creates* are caught, not just ones it edits.
BOBLIB_GENERATED_DIRS = (
    "Records/VehicleDefn",
    "Experiments/Standards/Templates/Vehicle",
    "Experiments/Standards/Templates/FourPost",
)
BOBLIB_GENERATED_FILES = (
    "Experiments/Standards/VehicleSim.mo",
    "Experiments/Standards/FourPostSim.mo",
)


def _boblib_snapshot() -> dict[Path, bytes]:
    snapshot: dict[Path, bytes] = {}
    for area in BOBLIB_GENERATED_DIRS:
        directory = BOBLIB_PACKAGE / area
        if directory.is_dir():
            for path in directory.rglob("*"):
                if path.is_file():
                    snapshot[path] = path.read_bytes()
    for name in BOBLIB_GENERATED_FILES:
        path = BOBLIB_PACKAGE / name
        if path.is_file():
            snapshot[path] = path.read_bytes()
    return snapshot


def restore_boblib(snapshot: dict[Path, bytes]) -> list[str]:
    """Put BobLib back byte-for-byte, deleting anything the run created."""
    touched: list[str] = []
    for path, content in snapshot.items():
        if not path.is_file() or path.read_bytes() != content:
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(content)
            touched.append(f"restored {path.name}")
    for area in BOBLIB_GENERATED_DIRS:
        directory = BOBLIB_PACKAGE / area
        if not directory.is_dir():
            continue
        for path in directory.rglob("*"):
            if path.is_file() and path not in snapshot:
                path.unlink()
                touched.append(f"removed {path.name}")
    return touched


def _files_not_in(snapshot: dict[Path, bytes]) -> list[Path]:
    """Files present under the generated areas that the snapshot does not know."""
    extra: list[Path] = []
    for area in BOBLIB_GENERATED_DIRS:
        directory = BOBLIB_PACKAGE / area
        if not directory.is_dir():
            continue
        extra.extend(
            path for path in directory.rglob("*") if path.is_file() and path not in snapshot
        )
    return extra


@contextlib.contextmanager
def pristine_boblib() -> Iterator[dict[str, Any]]:
    """Leave BobLib exactly as it was found, whatever happened inside.

    BobLib is a black box: BobSim generates into it to build, but nothing of ours
    belongs there afterwards. A comparison writes the variant's record, template
    and experiment classes, and adds them to the package.order indexes - so
    without this the library is left carrying a car it does not own, and the next
    unrelated build can compile the imported geometry while vehicle.yml says Orion.

    Regenerating the baseline is not sufficient and was the earlier mistake: it
    rewrites the records the baseline owns but leaves the variant's *created*
    classes and their package.order entries in place. Restoring the snapshot byte
    for byte is the only version of this with a checkable end state, namely that
    the submodule is clean.

    Runs in a finally, so it covers a raised StaleGeometryError, a failed build,
    and a KeyboardInterrupt alike.
    """
    snapshot = _boblib_snapshot()
    # Yielded so the caller can report what actually happened. The check has to be
    # made against the snapshot taken *before* the run; comparing the tree against
    # a snapshot of itself afterwards is vacuously clean and proves nothing.
    outcome: dict[str, Any] = {"restored": [], "leftovers": []}
    try:
        yield outcome
    finally:
        try:
            outcome["restored"] = restore_boblib(snapshot)
        finally:
            outcome["leftovers"] = [path.name for path in _files_not_in(snapshot)]
            invalidate_build_artifacts()


def modelica_state_report(outcome: dict[str, Any] | None = None) -> dict[str, Any]:
    """Describe the post-run state, for verification and for tests."""
    outcome = outcome or {}
    return {
        "boblib_leftovers": list(outcome.get("leftovers", [])),
        "boblib_restored": list(outcome.get("restored", [])),
        "stamp_present": GEOMETRY_STAMP.is_file(),
        "executable_present": four_post_executable() is not None,
    }


@contextlib.contextmanager
def installed_vehicle(source: Path) -> Iterator[Path]:
    """Temporarily install `source` as the repo vehicle.yml, always restoring it.

    The four-post stack reads the repo vehicle.yml by construction, so the opt-in
    sim path has to swap it. vehicle.yml is restored in a finally block; the
    kinematics path never touches it at all.

    A leftover backup means a previous run was killed between the swap and the
    restore, so the vehicle.yml on disk is whatever that run installed rather than
    the baseline. Refuse instead of overwriting the good copy with the bad one.
    """
    backup = VEHICLE_YAML.with_suffix(".yml.overlay-backup")
    if backup.exists():
        raise StaleGeometryError(
            f"A leftover backup exists at {backup.name}, so a previous four-post run was "
            "interrupted before it could restore the baseline. The vehicle.yml on disk is "
            "most likely the imported car, not the baseline.\n"
            f"Compare the two, restore {VEHICLE_YAML.name} from the backup if it is wrong, "
            "then delete the backup and re-run."
        )
    shutil.copy2(VEHICLE_YAML, backup)
    try:
        if source.resolve() != VEHICLE_YAML.resolve():
            shutil.copy2(source, VEHICLE_YAML)
        yield VEHICLE_YAML
    finally:
        shutil.copy2(backup, VEHICLE_YAML)
        backup.unlink(missing_ok=True)


def run_four_post(vehicle_path: Path, label: str, *, skip_build: bool) -> dict[str, Any]:
    """Run the four-post eval against `vehicle_path`, with a stale-geometry guard."""
    from _3_StandardSim.FourPostEval import four_post_eval_sim as fp

    with installed_vehicle(vehicle_path):
        signature, status = four_post_signature(VEHICLE_YAML)
        if not skip_build:
            build_four_post()
            assert_binary_consumed_geometry(status, label)
            assert_binary_is_executable_here(label)
            write_stamp(signature, status["vehicle_name"])

        stamped = read_stamp()
        if stamped != signature:
            raise StaleGeometryError(
                f"[{label}] The built four-post simulator does not match the current "
                f"geometry.\n  generated signature : {signature}\n"
                f"  built-from signature: {stamped}\n"
                "The executable was compiled from different hardpoints. Rebuild with "
                "`make standard-build-four-post` (do not pass --skip-build)."
            )

        config = fp.load_config(fp.DEFAULT_CONFIG_PATH)
        report_cfg = config.setdefault("report", {})
        report_cfg["enabled"] = False
        # Keep the overlay's metrics out of the canonical four-post CSV: that file is
        # the repo's regression baseline, and it is also read back to seed spring free
        # lengths, so sharing it would let one car's results leak into the other's.
        slug = "baseline" if label == BASELINE_LABEL else "variant"
        report_cfg["metrics_csv_path"] = str(OUT_DIR / f"shark_overlay_metrics_{slug}.csv")
        result = fp.FourPostEvalSim(config).run()
        return {"summary": result["summary"], "series": result["series"]}


# These are jacking-geometry percentages: the share of load transfer reacted
# through the links rather than the springs. They are not roll stiffness and not a
# total anti-roll figure, and the labels say so because "anti-roll %" invites
# exactly that misreading when an ARB is in play.
SCALAR_METRICS = (
    ("avg_anti_dive_pct", "Front anti-dive geometry (%)"),
    ("avg_anti_squat_pct", "Rear anti-squat geometry (%)"),
    ("avg_anti_roll_front_pct", "Front geometric anti-roll / lateral jacking (%)"),
    ("avg_anti_roll_rear_pct", "Rear geometric anti-roll / lateral jacking (%)"),
)

_MISSING = object()

# Actuation entries that carry force or compliance rather than hardpoint geometry.
# A difference in any of these changes four-post forces independently of the
# hardpoints, so it confounds a geometry comparison.
# Spring and damper entries can be transplanted wholesale, because they are rates
# rather than positions and carry no dependence on where the rocker sits.
SHOCK_FORCE_PATHS: tuple[tuple[str, ...], ...] = (
    ("shock", "spring_table"),
    ("shock", "damper_table"),
    ("shock", "free_length_m"),
)

FORCE_PATHS: tuple[tuple[str, ...], ...] = SHOCK_FORCE_PATHS + (
    ("stabar", "rate_n_m_per_rad"),
)

# Actuation entries that are genuine geometry and are expected to move.
GEOMETRY_PATHS: tuple[tuple[str, ...], ...] = (
    ("rod_to",),
    ("rod_mount_m",),
    ("shock", "mount_m"),
    ("bellcrank", "pivot_m"),
    ("bellcrank", "axis"),
)


def _dig(mapping: Any, path: Sequence[str]) -> Any:
    node = mapping
    for key in path:
        if not isinstance(node, dict) or key not in node:
            return _MISSING
        node = node[key]
    return node


def _shown(value: Any) -> str:
    if value is _MISSING:
        return "absent"
    if isinstance(value, list) and value and isinstance(value[0], (int, float)):
        return "[" + ", ".join(f"{v:.4g}" for v in value) + "]"
    if isinstance(value, (dict, list)):
        return "present"
    return repr(value)


def actuation_differences(baseline_path: Path, variant_path: Path) -> list[dict[str, Any]]:
    """Report every actuation difference between the two cars, classified.

    A four-post delta is only a geometry result if the force elements match. This
    surfaces the ones that do not, so a confounded number is never presented as a
    clean one.
    """
    base = load_yaml(baseline_path)
    var = load_yaml(variant_path)
    found: list[dict[str, Any]] = []

    for axle in ("front", "rear"):
        b = (base.get(axle) or {}).get("actuation") or {}
        v = (var.get(axle) or {}).get("actuation") or {}

        b_arb, v_arb = "stabar" in b, "stabar" in v
        if b_arb != v_arb:
            found.append({
                "axle": axle, "field": "stabar (anti-roll bar)", "kind": "force",
                "confound": True,
                "baseline": "present" if b_arb else "absent",
                "variant": "present" if v_arb else "absent",
                "note": "an ARB changes lateral load transfer independently of hardpoints",
            })

        for path in FORCE_PATHS:
            bv, vv = _dig(b, path), _dig(v, path)
            if bv == vv or (bv is _MISSING and vv is _MISSING):
                continue
            # An ARB rate that vanishes with the whole bar is already reported above.
            if path[0] == "stabar" and b_arb != v_arb:
                continue
            found.append({
                "axle": axle, "field": ".".join(path), "kind": "force", "confound": True,
                "baseline": _shown(bv), "variant": _shown(vv),
                "note": "force element differs, so the delta is not purely geometric",
            })

        for path in GEOMETRY_PATHS:
            bv, vv = _dig(b, path), _dig(v, path)
            if bv == vv or (bv is _MISSING and vv is _MISSING):
                continue
            found.append({
                "axle": axle, "field": ".".join(path), "kind": "geometry", "confound": False,
                "baseline": _shown(bv), "variant": _shown(vv), "note": "",
            })

    return found


def hold_baseline_actuation(
    baseline_path: Path, variant_path: Path, out_path: Path
) -> tuple[Path, list[str]]:
    """Write a variant carrying the baseline's force elements, keeping its geometry.

    This is the "geometry-only, baseline actuation held constant" mode: springs,
    dampers and the anti-roll bar come from the baseline so a four-post delta is
    attributable to hardpoints, while the actuation *geometry* the SHARK file
    genuinely defines is kept.

    Returns the written path and a list of what could not be held, which is not
    always empty: an ARB pickup is defined in the baseline rocker's local frame, so
    if the import moved the pivot the bar cannot be transplanted onto it.
    """
    base = load_yaml(baseline_path)
    var = copy.deepcopy(load_yaml(variant_path))
    unheld: list[str] = []

    for axle in ("front", "rear"):
        b = (base.get(axle) or {}).get("actuation") or {}
        v = (var.get(axle) or {}).get("actuation") or {}
        if not b or not v:
            continue
        for path in SHOCK_FORCE_PATHS:
            value = _dig(b, path)
            if value is _MISSING:
                continue
            node = v
            for key in path[:-1]:
                node = node.setdefault(key, {})
            node[path[-1]] = copy.deepcopy(value)

        if "stabar" in b and "stabar" not in v:
            pickup = _dig(b, ("bellcrank", "pickups_m", "stabar"))
            same_pivot = _dig(b, ("bellcrank", "pivot_m")) == _dig(v, ("bellcrank", "pivot_m"))
            if pickup is not _MISSING and same_pivot:
                v["stabar"] = copy.deepcopy(b["stabar"])
                v.setdefault("bellcrank", {}).setdefault("pickups_m", {})["stabar"] = copy.deepcopy(pickup)
            else:
                unheld.append(
                    f"{axle} anti-roll bar: the import moved the bellcrank pivot, so the "
                    "baseline pickup no longer describes a physical rocker and the bar "
                    "cannot be held constant"
                )

    out_path.parent.mkdir(parents=True, exist_ok=True)
    with out_path.open("w", encoding="utf-8") as handle:
        yaml.safe_dump(var, handle, sort_keys=False, default_flow_style=False)
    return out_path, unheld


def four_post_section(
    runs: dict[str, Any],
    *,
    differences: Sequence[dict[str, Any]],
    mode: str,
    unheld: Sequence[str] = (),
    gated: bool = False,
) -> dict[str, Any]:
    """Render the secondary four-post block, with its caveats attached."""
    confounds = [d for d in differences if d["confound"]]
    lines = [
        "EXPERIMENTAL / SECONDARY. Every percentage here is jacking geometry - the share",
        "of load transfer reacted through the links - not roll stiffness and not a total",
        "anti-roll figure. The kinematic curves are independent of all of it.",
        "",
        f"Actuation mode: {mode}.",
        "",
    ]

    if gated:
        lines += [
            "WITHHELD. The vertical datum is unresolved, and jacking geometry is measured",
            "against the contact patch, so every number below moves with the datum. They",
            "are suppressed for the same reason the roll-centre curves are.",
            "",
        ]

    if confounds:
        lines += [
            "CONFOUNDED - the two cars differ in force elements, so the deltas below are",
            "NOT attributable to hardpoints alone:",
            "",
        ]
        lines += [
            f"  - {d['axle']} {d['field']}: {d['baseline']} -> {d['variant']}"
            + (f"  ({d['note']})" if d["note"] else "")
            for d in confounds
        ]
        lines.append("")
    else:
        lines += ["Force elements match between the two cars.", ""]

    for item in unheld:
        lines += [f"COULD NOT HOLD CONSTANT: {item}", ""]

    geometry = [d for d in differences if not d["confound"]]
    if geometry:
        lines += ["Actuation geometry differences (expected, this is the change under test):", ""]
        lines += [f"  - {d['axle']} {d['field']}: {d['baseline']} -> {d['variant']}" for d in geometry]
        lines.append("")

    base = (runs.get(BASELINE_LABEL) or {}).get("summary") or {}
    var = (runs.get(VARIANT_LABEL) or {}).get("summary") or {}
    rows: list[tuple[str, str, str, str]] = []
    if base and var and not gated:
        for key, label in SCALAR_METRICS:
            b, v = base.get(key, float("nan")), var.get(key, float("nan"))
            rows.append((label, f"{b:.3f}", f"{v:.3f}", f"{v - b:+.3f}"))
    elif not gated:
        lines.append("Four-post produced no summary.")
    return {"lines": lines, "rows": rows, "confounded": bool(confounds), "mode": mode}


# --------------------------------------------------------------------------
# Entry point
# --------------------------------------------------------------------------


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description="Overlay a SHARK-imported car against the Orion baseline"
    )
    parser.add_argument(
        "--shark",
        default=None,
        help="Import this .shk into the variant file before overlaying (optional)",
    )
    parser.add_argument("--baseline", default=str(VEHICLE_YAML), help="Baseline vehicle.yml (Orion)")
    parser.add_argument(
        "--variant", default=str(DEFAULT_VARIANT_YAML),
        help="Variant vehicle.yml holding the imported car (gitignored by default)",
    )
    parser.add_argument(
        "--import-baseline", default=None,
        help=(
            "Baseline for the import step. Defaults to the variant file when it already "
            "exists, so a later front-axle import merges into it instead of replacing it."
        ),
    )
    parser.add_argument(
        "--keep-arb", action="store_true",
        help="Carry the baseline ARB across (four-post only; irrelevant to kinematics)",
    )
    parser.add_argument(
        "--four-post", action="store_true",
        help="Also run the experimental four-post force sim (needs a Modelica build)",
    )
    parser.add_argument(
        "--actuation",
        choices=("geometry-only", "imported"),
        default="geometry-only",
        help=(
            "geometry-only: hold the baseline springs, dampers and ARB constant so a "
            "four-post delta is attributable to hardpoints. imported: use the variant's "
            "own actuation and report the resulting confounds."
        ),
    )
    parser.add_argument("--skip-build", action="store_true", help="Do not rebuild (guard still enforced)")
    parser.add_argument(
        "--tol-deg", type=float, default=DEFAULT_TOLERANCES["deg"],
        help="Angle change considered negligible, for ranking (deg)",
    )
    parser.add_argument(
        "--tol-mm", type=float, default=DEFAULT_TOLERANCES["mm"],
        help="Length change considered negligible, for ranking (mm)",
    )
    parser.add_argument("--out", default=str(OUT_DIR / "shark_overlay_report.pdf"))
    args = parser.parse_args(argv)

    tolerances = {"deg": args.tol_deg, "mm": args.tol_mm}

    baseline_path = Path(args.baseline)
    variant_path = Path(args.variant)
    notes: list[str] = []
    withheld: frozenset[str] = frozenset()

    if args.shark:
        import_baseline = Path(args.import_baseline) if args.import_baseline else (
            variant_path if variant_path.is_file() else baseline_path
        )
        merged, report = import_shark(
            args.shark,
            baseline_path=import_baseline,
            # Always judge the datum against Orion, never against a car already built
            # from a SHARK file, which would compare the export to itself.
            datum_baseline_path=baseline_path,
            keep_stabar=args.keep_arb,
            vehicle_name=VARIANT_LABEL,
        )
        write_vehicle(merged, variant_path)
        write_datum_sidecar(variant_path, report["axle"], report["datum"], merged)
        notes += list(report["notes"])
        notes.append(f"Imported {args.shark} onto {import_baseline.name} -> {variant_path.name}")
    else:
        notes.append(f"No --shark given; overlaying the tracked {variant_path.name} as it stands.")

    if not variant_path.is_file():
        print(f"No variant vehicle at {variant_path}. Pass --shark to create it.", file=sys.stderr)
        return 1

    # One gate for every z-dependent output, evaluated against the file on disk
    # rather than against this invocation, so it survives a run that does not
    # re-import. It fails closed: missing, unresolved for any imported axle, or
    # digest-mismatched all withhold.
    gate = datum_gate(variant_path)
    if not gate["valid"]:
        withheld = frozenset(Z_DEPENDENT_CURVE_IDS)
        notes.append(f"DATUM GATE CLOSED - {gate['reason']}. Z-dependent outputs withheld.")
    else:
        notes.append(f"Datum gate open - {gate['reason']}.")

    payloads = {
        BASELINE_LABEL: kinematic_payload(baseline_path),
        VARIANT_LABEL: kinematic_payload(variant_path),
    }
    for label, payload in payloads.items():
        for warning in payload.get("warnings", []):
            notes.append(f"{label}: {warning}")

    notes.append(
        f"Sweep ranges match the app registry defaults; the point count is raised to "
        f"{len(BUMP_SWEEP_M)}/{len(ROLL_SWEEP_DEG)} so the design position is sampled "
        "rather than falling between two points as it does on the app's even grid."
    )
    notes.append(
        "The anti-roll bar takes no part in the kinematic solve; it is handled outside "
        "this tool."
    )

    metrics = curve_metrics(payloads, withheld, tolerances)

    four_post: dict[str, Any] | None = None
    if args.four_post:
        # Checked before the build, not after: the failure is a property of the host
        # and there is no point spending a Modelica compile to discover it.
        try:
            assert_four_post_is_runnable_here()
        except StaleGeometryError as exc:
            print(f"REFUSING TO RUN\n\n{exc}", file=sys.stderr)
            return 1
        sim_variant_path = variant_path
        unheld: list[str] = []
        if args.actuation == "geometry-only":
            sim_variant_path, unheld = hold_baseline_actuation(
                baseline_path, variant_path, OUT_DIR / "shark_geometry_only.yml"
            )
        differences = actuation_differences(baseline_path, sim_variant_path)

        runs: dict[str, Any] = {}
        failure: str | None = None
        # Whatever happens inside, BobLib is left describing the baseline again.
        with pristine_boblib() as boblib_outcome:
            for label, path in ((BASELINE_LABEL, baseline_path), (VARIANT_LABEL, sim_variant_path)):
                try:
                    runs[label] = run_four_post(path, label, skip_build=args.skip_build)
                except StaleGeometryError as exc:
                    failure = str(exc)
                    break
        restored = modelica_state_report(boblib_outcome)
        if failure is not None:
            print(f"REFUSING TO REPORT\n\n{failure}", file=sys.stderr)
            print(
                "\nBobLib restored to its pristine state: "
                f"leftovers={restored['boblib_leftovers'] or 'none'} "
                f"stamp_present={restored['stamp_present']} "
                f"executable_present={restored['executable_present']}",
                file=sys.stderr,
            )
            return 1
        # Jacking geometry is measured against the contact patch, so it moves with
        # the datum exactly as the roll-centre curves do and takes the same gate.
        four_post = four_post_section(
            runs, differences=differences, mode=args.actuation,
            unheld=unheld, gated=not gate["valid"],
        )
        four_post["restored"] = restored

    out = build_report(
        payloads, notes, withheld, metrics, four_post, Path(args.out), tolerances
    )
    md = write_summary_md(
        notes, withheld, metrics, four_post, Path(args.out).with_suffix(".md"), tolerances
    )
    print(f"Wrote {out}")
    print(f"Wrote {md}")
    if withheld:
        print(f"  WARNING: DATUM GATE CLOSED - {gate['reason']}")
        print(f"  WARNING: {len(withheld)} z-dependent outputs withheld, including four-post jacking")
    for note in notes:
        print(f"  note: {note}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
