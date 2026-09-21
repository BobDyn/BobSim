from __future__ import annotations

from contextlib import closing, contextmanager
import importlib.util
import multiprocessing
import os
from pathlib import Path
import socket
import sys
import threading
import time
from typing import Literal
import webbrowser


APP_TITLE = "BobSim"
HOST = "127.0.0.1"
PYTHON_STDIO_ENCODING = "utf-8:replace"
bobsim_app = None


def _configure_stdio() -> None:
    os.environ["PYTHONUTF8"] = "1"
    os.environ["PYTHONIOENCODING"] = PYTHON_STDIO_ENCODING
    for stream in (sys.stdout, sys.stderr):
        reconfigure = getattr(stream, "reconfigure", None)
        if reconfigure is None:
            continue
        try:
            reconfigure(encoding="utf-8", errors="replace")
        except (OSError, ValueError):
            try:
                reconfigure(errors="replace")
            except (OSError, ValueError):
                pass


def _bobsim_app():
    global bobsim_app
    if bobsim_app is None:
        from _5_App import app as imported_app

        bobsim_app = imported_app
    return bobsim_app


def _normalize_module_args(argv: list[str]) -> list[str]:
    if "--run-module" in argv[1:]:
        return argv
    if len(argv) >= 3 and argv[1] == "-m":
        return [argv[0], "--run-module", argv[2], *argv[3:]]
    return argv


def _available_port(host: str) -> int:
    with closing(socket.socket(socket.AF_INET, socket.SOCK_STREAM)) as sock:
        sock.bind((host, 0))
        return int(sock.getsockname()[1])


def _run_server(host: str, port: int) -> None:
    _bobsim_app().run(host, port)


def _has_module(module: str) -> bool:
    try:
        return importlib.util.find_spec(module) is not None
    except ModuleNotFoundError:
        return False


def _has_qt_webengine() -> bool:
    return _has_module("PyQt6.QtWebEngineCore") and _has_module("PyQt6.QtWebEngineWidgets")


def _can_start_embedded_window() -> bool:
    if sys.platform.startswith("linux"):
        return _has_module("gi") or _has_qt_webengine()
    return True


def _preferred_webview_gui() -> Literal["qt"] | None:
    if sys.platform.startswith("linux") and _has_qt_webengine():
        return "qt"
    return None


def _path_list_value(value: str) -> list[str]:
    return [part for part in value.split(os.pathsep) if part.strip()]


def _path_is_within(path: Path, root: Path) -> bool:
    try:
        path.resolve().relative_to(root.resolve())
    except (OSError, ValueError):
        return False
    return True


def _strip_env_paths_under(value: str, root: Path) -> str:
    parts = [part for part in _path_list_value(value) if not _path_is_within(Path(part), root)]
    return os.pathsep.join(parts)


def _sanitize_frozen_external_env(env: dict[str, str]) -> None:
    bundle_root_raw = str(getattr(sys, "_MEIPASS", "") or "").strip()
    if not bundle_root_raw:
        return
    bundle_root = Path(bundle_root_raw)

    for key in ("LD_LIBRARY_PATH", "DYLD_LIBRARY_PATH"):
        original = env.get(f"{key}_ORIG")
        if original is not None:
            restored = _strip_env_paths_under(original, bundle_root)
            if restored:
                env[key] = restored
            else:
                env.pop(key, None)
            continue
        if env.get(key):
            cleaned = _strip_env_paths_under(env[key], bundle_root)
            if cleaned:
                env[key] = cleaned
            else:
                env.pop(key, None)

    if env.get("PATH"):
        cleaned_path = _strip_env_paths_under(env["PATH"], bundle_root)
        if cleaned_path:
            env["PATH"] = cleaned_path
        else:
            env.pop("PATH", None)


@contextmanager
def _sanitized_frozen_external_environment():
    original_env = os.environ.copy()
    sanitized_env = original_env.copy()
    _sanitize_frozen_external_env(sanitized_env)
    try:
        os.environ.clear()
        os.environ.update(sanitized_env)
        yield
    finally:
        os.environ.clear()
        os.environ.update(original_env)


def _open_external_browser(url: str) -> None:
    with _sanitized_frozen_external_environment():
        webbrowser.open(url)


def _start_embedded_webview(webview_module, preferred_gui: Literal["qt"] | None) -> None:
    # QtWebEngine starts system helper processes for PDFs. Keep PyInstaller libraries out of them.
    with _sanitized_frozen_external_environment():
        if preferred_gui:
            webview_module.start(gui=preferred_gui)
        else:
            webview_module.start()


def _open_browser_and_wait(url: str, server_thread: threading.Thread) -> None:
    print(f"Opening BobSim in your browser: {url}", flush=True)
    _open_external_browser(url)
    try:
        while server_thread.is_alive():
            time.sleep(3600)
    except KeyboardInterrupt:
        return


def main() -> None:
    _configure_stdio()
    multiprocessing.freeze_support()

    sys.argv = _normalize_module_args(sys.argv)
    if "--run-module" in sys.argv[1:]:
        _bobsim_app().main()
        return

    port = _available_port(HOST)
    url = f"http://{HOST}:{port}"
    server_thread = threading.Thread(target=_run_server, args=(HOST, port), daemon=True)
    server_thread.start()
    time.sleep(0.35)

    os.environ.setdefault("QT_API", "pyqt6")

    if not _can_start_embedded_window():
        _open_browser_and_wait(url, server_thread)
        return

    try:
        import webview
    except Exception as exc:
        print(f"Embedded BobSim window unavailable: {exc}", flush=True)
        _open_browser_and_wait(url, server_thread)
        return

    try:
        webview.create_window(APP_TITLE, url, width=1440, height=960, min_size=(1100, 700))
        _start_embedded_webview(webview, _preferred_webview_gui())
    except Exception as exc:
        print(f"Embedded BobSim window failed to start: {exc}", flush=True)
        _open_browser_and_wait(url, server_thread)


if __name__ == "__main__":
    main()
