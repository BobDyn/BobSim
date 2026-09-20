from __future__ import annotations

from http import HTTPStatus
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
import json
import mimetypes
from pathlib import Path
from typing import Any
from urllib.parse import parse_qs, unquote, urlparse

from _5_App.http_utils import parse_byte_range as _parse_byte_range
from _5_App import visual as app_visual
from _0_Utils.dyn_py import kinematic_curves_payload


ROOT = Path.cwd()
STATIC_ROOT = Path("_5_App/static")
JOBS: Any = None

# The browser asks for a scene's header and its buffer separately, and building
# a payload reads the whole run. Hold the last one so the pair costs one build,
# keyed on the data file's mtime so a re-simulated run is never served stale.
_VISUAL_CACHE: dict[str, Any] = {"key": None, "payload": None}


def _visual_payload(run_id: str) -> Any:
    runs = {run["id"]: run for run in app_visual.available_runs(ROOT)}
    run = runs.get(run_id)
    if run is None:
        raise FileNotFoundError(f"No visual run named {run_id!r}")
    data_path = ROOT / run["data"]
    key = f"{run_id}:{data_path.stat().st_mtime_ns}"
    if _VISUAL_CACHE["key"] != key:
        _VISUAL_CACHE["payload"] = app_visual.scene_payload(ROOT / run["config"], data_path)
        _VISUAL_CACHE["key"] = key
    return _VISUAL_CACHE["payload"]


def sync_runtime() -> None:
    return None


def _not_connected(*_args: Any, **_kwargs: Any) -> Any:
    raise RuntimeError("Server dependency has not been connected")


status_payload = _not_connected
config_summary = _not_connected
config_specs = _not_connected
config_payload = _not_connected
vehicle_library_payload = _not_connected
vehicle_workspace_payload = _not_connected
vehicle_template_payloads = _not_connected
sim_config_library_payload = _not_connected
saved_results_payload = _not_connected
_active_vehicle_workspace_key = _not_connected
result_sources_payload = _not_connected
result_source_payload = _not_connected
processing_workflows_payload = _not_connected
tire_eval_payload = _not_connected
kinematic_curves_from_active_vehicle = _not_connected
tire_template_library_payload = _not_connected
read_tire_template = _not_connected
read_text_payload = _not_connected
_csv_preview = _not_connected
openmodelica_toolchain_payload = _not_connected
start_job = _not_connected
save_openmodelica_toolchain_settings = _not_connected
start_workflow = _not_connected
save_raw_config = _not_connected
patch_config = _not_connected
apply_vehicle_template = _not_connected
load_vehicle_source = _not_connected
save_active_vehicle = _not_connected
delete_saved_vehicle = _not_connected
generate_modelica_payload = _not_connected
load_sim_config_source = _not_connected
save_active_sim_config = _not_connected
delete_saved_sim_config = _not_connected
save_active_results = _not_connected
delete_saved_result = _not_connected
add_processing_workflow = _not_connected
delete_processing_workflow = _not_connected
result_series_payload = _not_connected
_load_vehicle_yaml_file = _not_connected
_safe_repo_path = _not_connected
save_tire_template = _not_connected


class BobSimHandler(BaseHTTPRequestHandler):
    server_version = "BobSimApp/0.1"

    def do_GET(self) -> None:  # noqa: N802
        sync_runtime()
        parsed = urlparse(self.path)
        try:
            if parsed.path == "/":
                self._send_static(STATIC_ROOT / "index.html")
            elif parsed.path.startswith("/static/"):
                rel = parsed.path.removeprefix("/static/")
                self._send_static(_safe_static_path(rel))
            elif parsed.path == "/media/bob.png":
                self._send_static(ROOT / "_0_Utils/reporting/media/bob.png")
            elif parsed.path == "/api/status":
                self._send_json(status_payload())
            elif parsed.path == "/api/configs":
                self._send_json({"configs": [config_summary(spec) for spec in config_specs().values()]})
            elif parsed.path.startswith("/api/configs/"):
                config_id = parsed.path.rsplit("/", 1)[-1]
                self._send_json(config_payload(config_id))
            elif parsed.path == "/api/vehicles":
                self._send_json(vehicle_library_payload())
            elif parsed.path == "/api/vehicle-workspace":
                query = parse_qs(parsed.query)
                vehicle_key = query.get("vehicle_key", [None])[0]
                self._send_json(vehicle_workspace_payload(vehicle_key))
            elif parsed.path == "/api/vehicle-templates":
                self._send_json(vehicle_template_payloads())
            elif parsed.path == "/api/sim-configs":
                self._send_json(sim_config_library_payload(_query_one(parsed.query, "workflow_id")))
            elif parsed.path == "/api/results":
                query = parse_qs(parsed.query)
                vehicle_key = query.get("vehicle_key", [None])[0] if "vehicle_key" in query else None
                self._send_json(saved_results_payload(vehicle_key))
            elif parsed.path == "/api/results/sources":
                query = parse_qs(parsed.query)
                vehicle_key = query.get("vehicle_key", [None])[0] or _active_vehicle_workspace_key()
                self._send_json(result_sources_payload(vehicle_key))
            elif parsed.path == "/api/results/source":
                self._send_json(result_source_payload(_query_one(parsed.query, "path")))
            elif parsed.path == "/api/processing/workflows":
                query = parse_qs(parsed.query)
                vehicle_key = query.get("vehicle_key", [None])[0]
                self._send_json(processing_workflows_payload(vehicle_key))
            elif parsed.path == "/api/visual/runs":
                self._send_json({"runs": app_visual.available_runs(ROOT)})
            elif parsed.path == "/api/visual/scene":
                run_id = (parse_qs(parsed.query).get("run") or [""])[0]
                self._send_json(_visual_payload(run_id).header)
            elif parsed.path == "/api/visual/data":
                run_id = (parse_qs(parsed.query).get("run") or [""])[0]
                self._send_binary(_visual_payload(run_id).buffer)
            elif parsed.path == "/api/tires/eval":
                self._send_json(tire_eval_payload())
            elif parsed.path == "/api/kinematics/curves":
                self._send_json(kinematic_curves_from_active_vehicle())
            elif parsed.path == "/api/tires/templates":
                self._send_json(tire_template_library_payload())
            elif parsed.path == "/api/tires/template":
                self._send_json(read_tire_template(_query_one(parsed.query, "name")))
            elif parsed.path == "/api/file":
                path = _query_one(parsed.query, "path")
                self._send_json(read_text_payload(path))
            elif parsed.path == "/api/csv":
                path = _query_one(parsed.query, "path")
                self._send_json(_csv_preview(path))
            elif parsed.path == "/api/jobs":
                self._send_json({"jobs": JOBS.list()})
            elif parsed.path == "/api/toolchain/openmodelica":
                self._send_json(openmodelica_toolchain_payload())
            elif parsed.path.startswith("/api/jobs/"):
                job_id = parsed.path.rsplit("/", 1)[-1]
                job = JOBS.get(job_id)
                if job is None:
                    self._send_error(HTTPStatus.NOT_FOUND, "Job not found")
                else:
                    self._send_json(job)
            elif parsed.path.startswith("/files/"):
                rel = unquote(parsed.path.removeprefix("/files/"))
                self._send_repo_file(rel)
            else:
                self._send_error(HTTPStatus.NOT_FOUND, "Not found")
        except Exception as exc:
            self._send_error(HTTPStatus.BAD_REQUEST, str(exc))

    def do_POST(self) -> None:  # noqa: N802
        sync_runtime()
        parsed = urlparse(self.path)
        try:
            body = self._read_json_body()
            if parsed.path == "/api/jobs":
                job = start_job(str(body.get("action_id", "")))
                self._send_json(job, status=HTTPStatus.CREATED)
            elif parsed.path == "/api/toolchain/openmodelica":
                payload = save_openmodelica_toolchain_settings(body)
                self._send_json(payload)
            elif parsed.path.startswith("/api/workflows/") and parsed.path.endswith("/run"):
                workflow_id = parsed.path.removeprefix("/api/workflows/").removesuffix("/run").strip("/")
                job = start_workflow(workflow_id)
                self._send_json(job, status=HTTPStatus.CREATED)
            elif parsed.path.startswith("/api/configs/"):
                config_id = parsed.path.rsplit("/", 1)[-1]
                mode = str(body.get("mode", "patch"))
                if mode == "raw":
                    payload = save_raw_config(config_id, str(body.get("text", "")))
                else:
                    values = body.get("values", {})
                    if not isinstance(values, dict):
                        raise TypeError("values must be an object")
                    payload = patch_config(config_id, values)
                self._send_json(payload)
            elif parsed.path == "/api/vehicle-template":
                payload = apply_vehicle_template(str(body.get("template_id", "")))
                self._send_json(payload)
            elif parsed.path == "/api/vehicles/load":
                payload = load_vehicle_source(str(body.get("source_id", "")))
                self._send_json(payload)
            elif parsed.path == "/api/vehicles/save":
                payload = save_active_vehicle(str(body.get("name", "")))
                self._send_json(payload)
            elif parsed.path == "/api/vehicles/delete":
                payload = delete_saved_vehicle(str(body.get("source_id", "")))
                self._send_json(payload)
            elif parsed.path == "/api/modelica/generate":
                payload = generate_modelica_payload()
                self._send_json(payload)
            elif parsed.path == "/api/sim-configs/load":
                payload = load_sim_config_source(str(body.get("source_id", "")))
                self._send_json(payload)
            elif parsed.path == "/api/sim-configs/save":
                payload = save_active_sim_config(str(body.get("workflow_id", "")), str(body.get("name", "")))
                self._send_json(payload)
            elif parsed.path == "/api/sim-configs/delete":
                payload = delete_saved_sim_config(str(body.get("source_id", "")))
                self._send_json(payload)
            elif parsed.path == "/api/results/save":
                payload = save_active_results(str(body.get("workflow_id", "")), str(body.get("name", "")))
                self._send_json(payload)
            elif parsed.path == "/api/results/delete":
                payload = delete_saved_result(
                    str(body.get("result_id", "")),
                    str(body.get("vehicle_key", "")) or None,
                )
                self._send_json(payload)
            elif parsed.path == "/api/processing/workflows":
                payload = add_processing_workflow(body)
                self._send_json(payload, status=HTTPStatus.CREATED)
            elif parsed.path == "/api/processing/workflows/delete":
                payload = delete_processing_workflow(
                    str(body.get("workflow_id", "")),
                    str(body.get("vehicle_key", "")) or None,
                )
                self._send_json(payload)
            elif parsed.path == "/api/results/series":
                raw_signals = body.get("signals", [])
                if not isinstance(raw_signals, list):
                    raise TypeError("signals must be a list")
                payload = result_series_payload(
                    str(body.get("path", "")),
                    x_axis=str(body.get("x_axis", "__index__")),
                    signals=[str(signal) for signal in raw_signals],
                    max_points=int(body.get("max_points", 1800)),
                )
                self._send_json(payload)
            elif parsed.path == "/api/kinematics/curves":
                vehicle = body.get("vehicle")
                if vehicle is None:
                    vehicle = _load_vehicle_yaml_file(_safe_repo_path("vehicle.yml"))
                if not isinstance(vehicle, dict):
                    raise TypeError("vehicle must be an object")
                sweep_m = body.get("sweep_m")
                if sweep_m is not None and not isinstance(sweep_m, list):
                    raise TypeError("sweep_m must be a list")
                self._send_json(kinematic_curves_payload(vehicle, sweep_m=sweep_m))
            elif parsed.path == "/api/tires/eval":
                vehicle = body.get("vehicle")
                if vehicle is None:
                    vehicle = _load_vehicle_yaml_file(_safe_repo_path("vehicle.yml"))
                if not isinstance(vehicle, dict):
                    raise TypeError("vehicle must be an object")
                self._send_json(tire_eval_payload(vehicle))
            elif parsed.path == "/api/tires/template":
                payload = save_tire_template(str(body.get("name", "")), str(body.get("text", "")))
                self._send_json(payload)
            elif parsed.path == "/api/tires/import":
                payload = save_tire_template(str(body.get("name", "")), str(body.get("text", "")))
                self._send_json(payload)
            else:
                self._send_error(HTTPStatus.NOT_FOUND, "Not found")
        except KeyError as exc:
            self._send_error(HTTPStatus.BAD_REQUEST, f"Unknown action: {exc}")
        except Exception as exc:
            self._send_error(HTTPStatus.BAD_REQUEST, str(exc))

    def log_message(self, format: str, *args: Any) -> None:
        print(f"[app] {self.address_string()} - {format % args}")

    def _read_json_body(self) -> dict[str, Any]:
        length = int(self.headers.get("Content-Length", "0"))
        if length <= 0:
            return {}
        raw = self.rfile.read(length)
        data = json.loads(raw.decode("utf-8"))
        if not isinstance(data, dict):
            raise TypeError("Expected JSON object")
        return data

    def _send_json(self, payload: Any, status: HTTPStatus = HTTPStatus.OK) -> None:
        encoded = json.dumps(payload, indent=2).encode("utf-8")
        self.send_response(status)
        self.send_header("Content-Type", "application/json; charset=utf-8")
        self.send_header("Content-Length", str(len(encoded)))
        self.end_headers()
        self.wfile.write(encoded)

    def _send_binary(self, payload: bytes) -> None:
        """Send a float32 scene buffer. Immutable for its key, so it caches hard."""
        self.send_response(HTTPStatus.OK)
        self.send_header("Content-Type", "application/octet-stream")
        self.send_header("Content-Length", str(len(payload)))
        self.send_header("Cache-Control", "no-cache")
        self.end_headers()
        self.wfile.write(payload)

    def _send_error(self, status: HTTPStatus, message: str) -> None:
        self._send_json({"error": message}, status=status)

    def _send_static(self, path: Path) -> None:
        if not path.is_file():
            self._send_error(HTTPStatus.NOT_FOUND, "Not found")
            return
        self._send_file(path)

    def _send_repo_file(self, raw_path: str) -> None:
        path = _safe_repo_path(raw_path)
        if not path.is_file():
            self._send_error(HTTPStatus.NOT_FOUND, "File not found")
            return
        self._send_file(path)

    def _send_file(self, path: Path) -> None:
        mime_type = mimetypes.guess_type(path.name)[0] or "application/octet-stream"
        data = path.read_bytes()
        byte_range: tuple[int, int] | None = None
        try:
            byte_range = _parse_byte_range(self.headers.get("Range"), len(data))
        except ValueError:
            self.send_response(HTTPStatus.REQUESTED_RANGE_NOT_SATISFIABLE)
            self.send_header("Content-Range", f"bytes */{len(data)}")
            self.send_header("Accept-Ranges", "bytes")
            self.end_headers()
            return

        if byte_range:
            start, end = byte_range
            body = data[start : end + 1]
            self.send_response(HTTPStatus.PARTIAL_CONTENT)
            self.send_header("Content-Range", f"bytes {start}-{end}/{len(data)}")
        else:
            body = data
            self.send_response(HTTPStatus.OK)
        self.send_header("Content-Type", mime_type)
        if mime_type == "application/pdf":
            self.send_header("Content-Disposition", f'inline; filename="{path.name}"')
        self.send_header("Content-Length", str(len(body)))
        self.send_header("Accept-Ranges", "bytes")
        self.send_header("Cache-Control", "no-store")
        self.end_headers()
        self.wfile.write(body)


def _safe_static_path(raw_path: str) -> Path:
    candidate = (STATIC_ROOT / raw_path).resolve()
    if candidate != STATIC_ROOT and STATIC_ROOT not in candidate.parents:
        raise ValueError("Static path escapes app root")
    return candidate


def _query_one(query: str, key: str) -> str:
    values = parse_qs(query).get(key)
    if not values:
        raise KeyError(key)
    return values[0]


def run(host: str, port: int) -> None:
    server = ThreadingHTTPServer((host, port), BobSimHandler)
    print(f"BobSim app running at http://{host}:{port}")
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        print("\nStopping BobSim app")
    finally:
        server.server_close()


