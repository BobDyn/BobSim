import sys
from pathlib import Path
from typing import Any, cast

import yaml
import numpy as np
from numpy.typing import NDArray
import pyvista as pv
import matplotlib.pyplot as plt
from matplotlib.figure import Figure
from PIL import Image
import imageio.v2 as imageio
import vtk


ArrayF = NDArray[np.float64]
ArrayU8 = NDArray[np.uint8]


# ============================================================
# HELPERS
# ============================================================
def safe_normalize(
    v: ArrayF,
    fallback: ArrayF | None = None,
) -> ArrayF:
    if fallback is None:
        fallback = np.array([1.0, 0.0, 0.0], dtype=float)

    n = np.linalg.norm(v)
    if n < 1e-8:
        return fallback.copy()
    return v / n


def set_vtk_matrix(mat: vtk.vtkMatrix4x4, T: ArrayF) -> None:
    for i in range(4):
        for j in range(4):
            mat.SetElement(i, j, float(T[i, j]))


def make_frame_from_x(
    x_axis: ArrayF,
) -> ArrayF:
    x = safe_normalize(x_axis)

    ref = np.array([0.0, 0.0, 1.0], dtype=float)
    if abs(np.dot(x, ref)) > 0.95:
        ref = np.array([0.0, 1.0, 0.0], dtype=float)

    y = np.cross(ref, x)
    y = safe_normalize(y, fallback=np.array([0.0, 1.0, 0.0], dtype=float))

    z = np.cross(x, y)
    z = safe_normalize(z, fallback=np.array([0.0, 0.0, 1.0], dtype=float))

    return np.column_stack((x, y, z))


def make_link_transform(
    p1: ArrayF,
    p2: ArrayF,
) -> ArrayF:
    d = p2 - p1
    L = np.linalg.norm(d)

    T = np.eye(4)
    if L < 1e-10:
        T[:3, 3] = p1
        return T

    R = make_frame_from_x(d)

    # unit cylinder is centered at origin and has height=1 along +x/-x
    # so scale x by link length, then move to midpoint
    S = np.diag([L, 1.0, 1.0])
    T[:3, :3] = R @ S
    T[:3, 3] = 0.5 * (p1 + p2)
    return T


# ============================================================
# ARGUMENTS
# ============================================================
if len(sys.argv) < 3:
    print("Usage:")
    print("  python run_visual.py visual.yml signals.npz --mp4 out.mp4")
    sys.exit(1)

cfg_path = Path(sys.argv[1]).resolve()
npz_path = Path(sys.argv[2]).resolve()

if "--mp4" not in sys.argv:
    raise ValueError("Use --mp4 out.mp4")

mp4_path = sys.argv[sys.argv.index("--mp4") + 1]

print(f"[bobvis] Config: {cfg_path}")
print(f"[bobvis] Data:   {npz_path}")
print(f"[bobvis] MP4:    {mp4_path}")


# ============================================================
# LOAD
# ============================================================
with open(cfg_path, "r", encoding="utf-8") as f:
    cfg: dict[str, Any] = yaml.safe_load(f)

npz_file = np.load(npz_path)
npz: dict[str, ArrayF] = {
    key: np.asarray(npz_file[key], dtype=float)
    for key in npz_file.files
}

time_arr = np.asarray(npz["time"], dtype=float)
show_signals = bool(cfg.get("render", {}).get("show_signals", False))

# Optional stride knob.
# Default is 1 so behavior is unchanged unless you explicitly set it.
input_stride = int(cfg.get("render", {}).get("input_stride", 1))
if input_stride > 1:
    time_arr = time_arr[::input_stride]


# ============================================================
# BUILD POINTS
# ============================================================
points: dict[str, ArrayF] = {}
for name, cols_any in cfg["geometry"]["points"].items():
    cols = cast(list[str], cols_any)
    arr = np.stack([np.asarray(npz[c], dtype=float) for c in cols], axis=1)
    if input_stride > 1:
        arr = arr[::input_stride]
    points[name] = arr

names = list(points.keys())


# ============================================================
# BUILD VECTORS (NEW)
# ============================================================
vectors_cfg = cast(dict[str, Any], cfg["geometry"].get("vectors", {}))

vectors: list[dict[str, Any]] = []

for group in vectors_cfg.values():
    for name, vcfg_any in group.items():
        vcfg = cast(dict[str, Any], vcfg_any)

        dir_cols = vcfg["direction"]

        dir_components = []
        for c in dir_cols:
            if isinstance(c, str):
                dir_components.append(np.asarray(npz[c], dtype=float))
            else:
                # constant → broadcast to time length
                dir_components.append(np.full_like(time_arr, float(c)))

        dir_arr = np.stack(dir_components, axis=1)

        if input_stride > 1:
            dir_arr = dir_arr[::input_stride]

        vectors.append(
            {
                "name": name,
                "origin": cast(str, vcfg["origin"]),
                "direction": dir_arr,
                "scale": float(vcfg.get("scale", 1.0)),
                "color": vcfg.get("color", "black"),
                "shaft_radius": float(vcfg.get("shaft_radius", 0.02)),
                "tip_radius": float(vcfg.get("tip_radius", 0.04)),
            }
        )


# ============================================================
# CAMERA
# ============================================================
cam_cfg = cast(dict[str, Any], cfg.get("camera", {}))
attach_name = cast(str | None, cam_cfg.get("attach_to", None))

origin_offset = np.array(
    [
        cam_cfg.get("origin_offset", {}).get("x", 0.0),
        cam_cfg.get("origin_offset", {}).get("y", 0.0),
        cam_cfg.get("origin_offset", {}).get("z", 0.0),
    ],
    dtype=float,
)

cam_offs = cast(dict[str, Any], cam_cfg.get("camera_offsets", {}))


def update_camera(i: int) -> None:
    if attach_name not in points:
        return

    if "forward_pair" not in cam_cfg:
        return

    forward_pair = cast(list[str], cam_cfg["forward_pair"])

    # ============================================================
    # VEHICLE FRAME (yaw-only)
    # ============================================================
    p1 = points[forward_pair[0]][i]
    p2 = points[forward_pair[1]][i]

    f = safe_normalize(np.array([
        p2[0] - p1[0],
        p2[1] - p1[1],
        0.0
    ]))

    up = np.array([0.0, 0.0, 1.0])
    r = safe_normalize(np.cross(f, up))
    up = safe_normalize(np.cross(r, f))

    # 👉 vehicle rotation matrix (world <- body)
    R_vehicle = np.column_stack((f, r, up))

    # ============================================================
    # ORIGIN OFFSET (NOW IN VEHICLE FRAME)
    # ============================================================
    C_body = origin_offset
    C = points[attach_name][i] + R_vehicle @ C_body

    # ============================================================
    # CAMERA POSITION (still in vehicle frame)
    # ============================================================
    back = float(cam_offs.get("back", 2.5))
    height = float(cam_offs.get("height", 1.5))

    cam_offset_body = np.array([
        -back,   # behind
        0.0,
        height
    ])

    cam_pos = C + R_vehicle @ cam_offset_body

    # ============================================================
    # APPLY
    # ============================================================
    plotter.camera.position = cam_pos
    plotter.camera.focal_point = C
    plotter.camera.up = up


# ============================================================
# STYLE
# ============================================================
joint_radius = float(cfg.get("style", {}).get("joints", {}).get("radius", 0.02))
joint_color = cfg.get("style", {}).get("joints", {}).get("color", "red")

link_style = cast(dict[str, Any], cfg.get("style", {}).get("links", {}))
default_link = cast(dict[str, Any], link_style.get("default", {"radius": 0.01, "color": "black"}))
group_styles = cast(dict[str, dict[str, Any]], link_style.get("groups", {}))


# ============================================================
# PLOTTER
# ============================================================
plotter = pv.Plotter(off_screen=True, window_size=[640, 640])
plotter.set_background("white")  # type: ignore[arg-type]
plotter.add_axes()  # type: ignore[call-arg]
plotter.camera.clipping_range = (0.01, 2000)


# # ============================================================
# # GROUND (WORLD-FIXED)
# # ============================================================
# ground_size = 300.0

# # --- solid ground plane
# ground = pv.Plane(
#     center=(0, 0, 0),
#     direction=(0, 0, 1),
#     i_size=ground_size,
#     j_size=ground_size,
# )

# plotter.add_mesh(
#     ground,
#     color=(0.85, 0.9, 0.85),  # light green
#     opacity=1.0,
# )

# # --- grid (slightly above to avoid z-fighting)
# grid = pv.Plane(
#     center=(0, 0, 0.001),
#     direction=(0, 0, 1),
#     i_size=ground_size,
#     j_size=ground_size,
#     i_resolution=200,
#     j_resolution=200,
# )

# plotter.add_mesh(
#     grid,
#     style="wireframe",
#     color=(0, 1, 0),
#     line_width=1.5,
#     lighting=False,
# )


# ============================================================
# JOINTS
# ============================================================
joint_mesh = pv.Sphere(radius=joint_radius)

actors: dict[str, Any] = {
    n: plotter.add_mesh(joint_mesh.copy(), color=joint_color)
    for n in names
}


# ============================================================
# LINKS
# ============================================================
links: list[dict[str, Any]] = []

for group, group_links_any in cfg["geometry"]["links"].items():
    group_links = cast(list[list[str]], group_links_any)
    style = cast(dict[str, Any], group_styles.get(group, default_link))
    radius = float(style["radius"])
    color = style["color"]

    # Unit cylinder centered at origin, aligned with x-axis.
    # We transform this each frame instead of rebuilding tube geometry.
    link_mesh = pv.Cylinder(
        center=(0.0, 0.0, 0.0),
        direction=(1.0, 0.0, 0.0),
        radius=radius,
        height=1.0,
        resolution=24,
    )

    for a, b in group_links:
        actor = plotter.add_mesh(
            link_mesh.copy(),
            color=color,
            smooth_shading=False,
        )
        vtk_mat = vtk.vtkMatrix4x4()
        actor.SetUserMatrix(vtk_mat)

        links.append(
            {
                "a": a,
                "b": b,
                "actor": actor,
                "vtk_mat": vtk_mat,
            }
        )


# ============================================================
# TIRES
# ============================================================
tire_actors: list[dict[str, Any]] = []

for tire_cfg_any in cast(dict[str, Any], cfg["geometry"].get("tires", {})).values():
    tire_cfg = cast(dict[str, Any], tire_cfg_any)

    x_cols = cast(list[str], tire_cfg["x"])
    y_cols = cast(list[str], tire_cfg["y"])

    data: dict[str, Any] = {
        "center": cast(str, tire_cfg["center"]),
        "x": np.stack([np.asarray(npz[c], dtype=float) for c in x_cols], axis=1),
        "y": np.stack([np.asarray(npz[c], dtype=float) for c in y_cols], axis=1),
        "radius": float(tire_cfg["radius"]),
        "width": float(tire_cfg["width"]),
    }

    if input_stride > 1:
        data["x"] = cast(ArrayF, data["x"])[::input_stride]
        data["y"] = cast(ArrayF, data["y"])[::input_stride]

    outer = plotter.add_mesh(
        pv.Cylinder(
            direction=(0, 1, 0),
            radius=float(data["radius"]),
            height=float(data["width"]),
            resolution=48,
        ),
        color=(0.1, 0.1, 0.1),
        opacity=0.6,
        smooth_shading=False,
    )

    rim = plotter.add_mesh(
        pv.Cylinder(
            direction=(0, 1, 0),
            radius=0.6 * float(data["radius"]),
            height=0.9 * float(data["width"]),
            resolution=32,
        ),
        color=(0.8, 0.8, 0.8),
        opacity=0.6,
        smooth_shading=False,
    )

    vtk_outer = vtk.vtkMatrix4x4()
    vtk_rim = vtk.vtkMatrix4x4()

    outer.SetUserMatrix(vtk_outer)
    rim.SetUserMatrix(vtk_rim)

    tire_actors.append(
        {
            "data": data,
            "outer": outer,
            "rim": rim,
            "vtk_outer": vtk_outer,
            "vtk_rim": vtk_rim,
            "theta": 0.6,
        }
    )


# ============================================================
# VECTORS (ARROWS)
# ============================================================
vector_actors: list[dict[str, Any]] = []

for v in vectors:
    arrow = plotter.add_mesh(
        pv.Arrow(
            start=(0, 0, 0),
            direction=(1, 0, 0),
            tip_length=0.3,
            tip_radius=v["tip_radius"],
            shaft_radius=v["shaft_radius"],
        ),
        color=v["color"],
    )

    vtk_mat = vtk.vtkMatrix4x4()
    arrow.SetUserMatrix(vtk_mat)

    vector_actors.append(
        {
            "cfg": v,
            "actor": arrow,
            "vtk_mat": vtk_mat,
        }
    )


# ============================================================
# SIGNAL PLOT
# ============================================================
fig: Figure | None
cursors: list[Any]

if show_signals:
    plots_cfg = cast(list[dict[str, Any]], cfg["plots"])
    n_plots = len(plots_cfg)

    fig, axes = plt.subplots(
        n_plots,
        1,
        figsize=(6.4, 2.5 * n_plots),
        sharex=True,
    )

    if n_plots == 1:
        axes = [axes]

    cursors = []

    for ax, p in zip(axes, plots_cfg):
        x = np.asarray(npz[cast(str, p["x"])], dtype=float)
        y = np.asarray(npz[cast(str, p["y"])], dtype=float)

        ax.plot(
            x,
            y,
            linewidth=2.0,
            color="#1f77b4",
        )

        ax.set_ylabel(cast(str, p["name"]), fontsize=10)
        ax.grid(True, which="major", linestyle="--", linewidth=0.5, alpha=0.5)
        ax.spines["top"].set_visible(False)
        ax.spines["right"].set_visible(False)
        ax.spines["left"].set_alpha(0.5)
        ax.spines["bottom"].set_alpha(0.5)
        ax.tick_params(axis="both", labelsize=9)

        cursor = ax.axvline(time_arr[0], color="red", linewidth=1.5)
        cursors.append(cursor)

    fig.subplots_adjust(
        left=0.12,
        right=0.98,
        top=0.98,
        bottom=0.08,
        hspace=0.25,
    )
    axes[-1].set_xlabel("Time")

    fig.canvas.draw()
    plot_canvas_w, plot_canvas_h = fig.canvas.get_width_height()
else:
    fig = None
    cursors = []


# ============================================================
# UPDATE FRAME
# ============================================================
def update_frame(i: int) -> None:
    for name in names:
        actors[name].SetPosition(*points[name][i])

    for link in links:
        a = cast(str, link["a"])
        b = cast(str, link["b"])
        actor = link["actor"]
        vtk_mat = cast(vtk.vtkMatrix4x4, link["vtk_mat"])

        p1 = points[a][i]
        p2 = points[b][i]

        T = make_link_transform(p1, p2)
        set_vtk_matrix(vtk_mat, T)
        actor.Modified()

    for tire in tire_actors:
        data = cast(dict[str, Any], tire["data"])
        outer = tire["outer"]
        rim = tire["rim"]

        vtk_outer = cast(vtk.vtkMatrix4x4, tire["vtk_outer"])
        vtk_rim = cast(vtk.vtkMatrix4x4, tire["vtk_rim"])

        center_name = cast(str, data["center"])
        x_arr = cast(ArrayF, data["x"])
        y_arr = cast(ArrayF, data["y"])
        radius = float(data["radius"])

        C = points[center_name][i]

        x = safe_normalize(x_arr[i])
        y_raw = y_arr[i]
        y = safe_normalize(
            y_raw - np.dot(y_raw, x) * x,
            fallback=np.array([0.0, 1.0, 0.0], dtype=float),
        )
        z = safe_normalize(
            np.cross(x, y),
            fallback=np.array([0.0, 0.0, 1.0], dtype=float),
        )

        if i > 0:
            dt = time_arr[i] - time_arr[i - 1]
            v = (C - points[center_name][i - 1]) / max(dt, 1e-6)
            tire["theta"] = float(tire["theta"]) + float(np.dot(v, x)) / radius * dt

        theta = float(tire["theta"])

        Ry = np.array(
            [
                [np.cos(theta), 0.0, np.sin(theta)],
                [0.0, 1.0, 0.0],
                [-np.sin(theta), 0.0, np.cos(theta)],
            ],
            dtype=float,
        )

        R = np.column_stack((x, y, z)) @ Ry

        T = np.eye(4)
        T[:3, :3] = R
        T[:3, 3] = C

        set_vtk_matrix(vtk_outer, T)
        outer.Modified()

        set_vtk_matrix(vtk_rim, T)
        rim.Modified()
    
    for v in vector_actors:
        cfg_v = v["cfg"]
        actor = v["actor"]
        vtk_mat = cast(vtk.vtkMatrix4x4, v["vtk_mat"])

        origin_name = cast(str, cfg_v["origin"])
        d_arr = cast(ArrayF, cfg_v["direction"])
        scale = float(cfg_v["scale"])

        p = points[origin_name][i]
        d = d_arr[i]

        L = np.linalg.norm(d)

        # ============================================================
        # ZERO FORCE → collapse arrow (no NaNs, no flicker)
        # ============================================================
        if L < 1e-6:
            T = np.eye(4)
            T[:3, :3] = 0.0      # 🔥 collapse geometry
            T[:3, 3] = p
            set_vtk_matrix(vtk_mat, T)
            actor.Modified()
            continue

        # ============================================================
        # NORMAL CASE
        # ============================================================
        x = d / L
        R = make_frame_from_x(x)

        S = np.diag([L * scale, 1.0, 1.0])

        T = np.eye(4)
        T[:3, :3] = R @ S
        T[:3, 3] = p

        set_vtk_matrix(vtk_mat, T)
        actor.Modified()

    update_camera(i)
    plotter.render()


# ============================================================
# TIMING
# ============================================================
fps = 30
speed = float(cfg.get("render", {}).get("speed", 1.0))

t0 = float(time_arr[0])
tf = float(time_arr[-1])
duration = (tf - t0) / speed

# Keep full frame-count behavior exactly as before.
n_frames = max(2, int(duration * fps))
video_times = np.linspace(t0, tf, n_frames)
indices = np.searchsorted(time_arr, video_times, side="left")
indices = np.clip(indices, 0, len(time_arr) - 1)


# ============================================================
# VIDEO
# ============================================================
writer = imageio.get_writer(mp4_path, fps=fps)

plot_target_w: int | None = None
plot_target_h: int | None = None

for i_raw in indices:
    i = int(i_raw)
    update_frame(i)

    img_pv = plotter.screenshot(return_img=True)
    if img_pv is None:
        continue

    img: ArrayU8 = np.asarray(img_pv, dtype=np.uint8)

    if show_signals and fig is not None:
        for cursor in cursors:
            cursor.set_xdata([time_arr[i]])

        fig.canvas.draw()

        buf = np.frombuffer(
            fig.canvas.buffer_rgba(),  # type: ignore[attr-defined]
            dtype=np.uint8,
        )
        plot_img: ArrayU8 = buf.reshape((plot_canvas_h, plot_canvas_w, 4))[:, :, :3]

        if plot_target_w is None or plot_target_h is None:
            plot_target_h = int(img.shape[0])
            plot_target_w = int(plot_img.shape[1] * (plot_target_h / plot_img.shape[0]))

        plot_img = np.asarray(
            Image.fromarray(plot_img).resize(
                (plot_target_w, plot_target_h),
                resample=Image.Resampling.BILINEAR,
            ),
            dtype=np.uint8,
        )

        img = np.hstack([img, plot_img])

    h, w, _ = img.shape
    img = img[: h // 16 * 16, : w // 16 * 16]

    writer.append_data(img)

writer.close()

if show_signals and fig is not None:
    plt.close(fig)

print(f"[bobvis] ✔ MP4 saved → {mp4_path}")