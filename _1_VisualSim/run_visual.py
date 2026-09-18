"""Headless BobVis renderer: visual YAML + signals -> video file.

    python -m _1_VisualSim.run_visual CONFIG.yml DATA.npz -o out.mp4

Geometry, camera and styling come from :mod:`_1_VisualSim.scene`, which the
interactive viewer also uses, so a headless render and the on-screen view
cannot drift apart.
"""

from __future__ import annotations

import argparse
import sys
from pathlib import Path

from _1_VisualSim.exporter import (
    ExportCancelled,
    ExportError,
    RESOLUTIONS,
    render_video,
    settings_from_args,
)
from _1_VisualSim.scene import SimData, VisualConfigError


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        prog="python -m _1_VisualSim.run_visual",
        description="Render a BobVis scene to a video file without opening a window.",
    )
    parser.add_argument("config", type=Path, help="visual YAML config")
    parser.add_argument("data", type=Path, help="signal file (.npz or .csv)")
    parser.add_argument(
        "-o", "--output", "--mp4", dest="output", type=Path, required=True,
        help="output video (.mp4, .mov, .webm or .gif)",
    )
    parser.add_argument(
        "--resolution", default="1080p",
        help=f"{', '.join(sorted(RESOLUTIONS))} or WIDTHxHEIGHT (default: 1080p)",
    )
    parser.add_argument("--fps", type=int, default=60, help="frames per second (default: 60)")
    parser.add_argument(
        "--speed", type=float, default=None,
        help="playback speed multiplier (default: render.speed from the config)",
    )
    parser.add_argument("--start", type=float, default=None, help="start time in seconds")
    parser.add_argument("--end", type=float, default=None, help="end time in seconds")
    parser.add_argument(
        "--no-plots", action="store_true",
        help="omit the signal strip even when the config defines plots",
    )
    parser.add_argument(
        "--no-ground", action="store_true", help="hide the ground plane and grid",
    )
    parser.add_argument(
        "--quality", type=int, default=8, help="imageio quality, 1-10 (default: 8)",
    )
    return parser


def main(argv: list[str] | None = None) -> int:
    args = build_parser().parse_args(argv)

    try:
        data = SimData(args.config, args.data)
    except (OSError, VisualConfigError) as exc:
        print(f"[bobvis] {exc}", file=sys.stderr)
        return 2

    speed = args.speed
    if speed is None:
        speed = float(data.render_cfg.get("speed", 1.0) or 1.0)

    try:
        settings = settings_from_args(
            output=args.output,
            resolution=args.resolution,
            fps=args.fps,
            speed=speed,
            show_plots=not args.no_plots,
            quality=args.quality,
        )
    except ExportError as exc:
        print(f"[bobvis] {exc}", file=sys.stderr)
        return 2

    settings.start_time = args.start
    settings.end_time = args.end
    if args.no_ground and settings.scene_options is not None:
        settings.scene_options = settings.scene_options.copy_with(show_ground=False)

    total = len(settings.frame_times(data))
    print(f"[bobvis] config     {args.config}")
    print(f"[bobvis] data       {args.data}  ({data.n_frames} samples)")
    print(f"[bobvis] output     {settings.output}")
    print(f"[bobvis] {settings.width}x{settings.height} @ {settings.fps} fps, "
          f"{total} frames, speed {speed}x")

    def progress(done: int, count: int) -> bool:
        if done % 10 == 0 or done == count:
            pct = 100.0 * done / max(count, 1)
            print(f"\r[bobvis] rendering {done}/{count}  {pct:5.1f}%",
                  end="", flush=True)
        return True

    try:
        written = render_video(data, settings, progress)
    except ExportCancelled:
        print("\n[bobvis] cancelled", file=sys.stderr)
        return 1
    except (ExportError, VisualConfigError) as exc:
        print(f"\n[bobvis] {exc}", file=sys.stderr)
        return 2

    print(f"\n[bobvis] wrote {written}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
