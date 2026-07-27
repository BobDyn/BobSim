from __future__ import annotations

import argparse
import os
import platform
from pathlib import Path
import runpy
import shutil
import subprocess
import sys
import time
from typing import Any, cast

from _5_App import actions as app_actions
from _5_App import contracts as app_contracts
from _5_App import data_services as app_data_services
from _5_App import modelica_build as app_modelica_build
from _5_App import registry as app_registry
from _5_App import runtime as app_runtime
from _5_App import server as app_server
from _5_App import storage as app_storage
from _5_App import tire_eval as tire_eval_core
from _5_App import toolchain as app_toolchain
from _5_App.contracts import (
    ActionSpec,
    WorkflowSpec,
)
from _5_App.http_utils import parse_byte_range as _parse_byte_range
from _5_App.jobs import JobStore
from _5_App.registry import (
    build_action_specs,
    build_modelica_build_targets,
    build_workflows,
)
from _5_App.kinematics import kinematic_curves_payload
from _5_App.modelica_generator import modelica_stack_status_payload

OutputSpec = app_contracts.OutputSpec
ConfigSpec = app_contracts.ConfigSpec
FieldSpec = app_contracts.FieldSpec
PathPart = app_contracts.PathPart
BuildTargetSpec = app_contracts.BuildTargetSpec
ARCHITECTURE_CHOICES = app_registry.ARCHITECTURE_CHOICES
BELLCRANK_ORDER_CHOICES = app_registry.BELLCRANK_ORDER_CHOICES
COMMON_SIM_FIELDS = app_registry.COMMON_SIM_FIELDS
DIRECTION_CHOICES = app_registry.DIRECTION_CHOICES
ROD_TARGET_CHOICES = app_registry.ROD_TARGET_CHOICES
SOLVER_CHOICES = app_registry.SOLVER_CHOICES
STABAR_BELLCRANK_ORDER_CHOICES = app_registry.STABAR_BELLCRANK_ORDER_CHOICES
BASE_CONFIG_SPECS = app_registry.BASE_CONFIG_SPECS
POWERTRAIN_DEFAULTS = app_registry.POWERTRAIN_DEFAULTS
POWERTRAIN_IMPLEMENTATIONS = app_registry.POWERTRAIN_IMPLEMENTATIONS
VEHICLE_FIELDS = app_registry.VEHICLE_FIELDS
VISUAL_FIELDS = app_registry.VISUAL_FIELDS
BUILD_METADATA_FILENAME = app_registry.BUILD_METADATA_FILENAME
_field = app_registry._field


PROJECT_NAME = app_runtime.PROJECT_NAME
APP_NAME = app_runtime.APP_NAME
PRIMARY_HOME_ENV = app_runtime.PRIMARY_HOME_ENV
LEGACY_HOME_ENV = app_runtime.LEGACY_HOME_ENV
PACKAGE_ROOT = Path(getattr(sys, "_MEIPASS", Path(__file__).resolve().parents[1])).resolve()
FROZEN_APP = bool(getattr(sys, "frozen", False))
APP_RUNTIME_SEED_SCHEMA_VERSION = app_runtime.APP_RUNTIME_SEED_SCHEMA_VERSION
APP_SEED_RUNTIME_PATHS = app_runtime.APP_SEED_RUNTIME_PATHS
APP_REFRESH_RUNTIME_PATHS = app_runtime.APP_REFRESH_RUNTIME_PATHS
APP_MERGE_RUNTIME_DIRS = app_runtime.APP_MERGE_RUNTIME_DIRS
APP_RUNTIME_SEED_MANIFEST_PATH = app_runtime.APP_RUNTIME_SEED_MANIFEST_PATH
APP_RESET_ON_RUNTIME_SEED_CHANGE_PATHS = app_runtime.APP_RESET_ON_RUNTIME_SEED_CHANGE_PATHS
APP_MODELICA_BUILD_FINGERPRINT_PATHS = app_runtime.APP_MODELICA_BUILD_FINGERPRINT_PATHS
RUNTIME_SEED_WARNINGS = app_runtime.RUNTIME_SEED_WARNINGS
WINDOWS_LOCKED_FILE_ERRORS = app_runtime.WINDOWS_LOCKED_FILE_ERRORS

_default_runtime_root = app_runtime._default_runtime_root
_runtime_copy_ignore = app_runtime._runtime_copy_ignore
_is_locked_file_error = app_runtime._is_locked_file_error
_runtime_seed_warning = app_runtime._runtime_seed_warning
_retry_runtime_io = app_runtime._retry_runtime_io
_remove_runtime_path = app_runtime._remove_runtime_path
_copy_runtime_file = app_runtime._copy_runtime_file
_copy_runtime_tree = app_runtime._copy_runtime_tree
_same_file_content = app_runtime._same_file_content
_source_path_current = app_runtime._source_path_current
_fingerprint_paths = app_runtime._fingerprint_paths
_read_runtime_seed_manifest = app_runtime._read_runtime_seed_manifest
_write_runtime_seed_manifest = app_runtime._write_runtime_seed_manifest
_runtime_seed_changed = app_runtime._runtime_seed_changed
app_runtime.time = time


def _runtime_seed_manifest() -> dict[str, Any]:
    return app_runtime._runtime_seed_manifest(PACKAGE_ROOT)


def _seed_runtime_root(runtime_root: Path) -> None:
    app_runtime._seed_runtime_root(
        runtime_root,
        package_root=PACKAGE_ROOT,
        remove_runtime_path=_remove_runtime_path,
    )


def _prepare_runtime_root() -> Path:
    if not getattr(sys, "frozen", False):
        return PACKAGE_ROOT

    runtime_root = _default_runtime_root()
    _seed_runtime_root(runtime_root)
    os.chdir(runtime_root)
    return runtime_root

ROOT = _prepare_runtime_root()
STATIC_ROOT = PACKAGE_ROOT / app_storage.STATIC_ROOT
USER_DATA_ROOT = app_storage.USER_DATA_ROOT
USER_CONFIG_ROOT = app_storage.USER_CONFIG_ROOT
USER_CACHE_ROOT = app_storage.USER_CACHE_ROOT
USER_RESULTS_ROOT = app_storage.USER_RESULTS_ROOT
USER_WORKSPACE_ROOT = app_storage.USER_WORKSPACE_ROOT
SAVED_VEHICLE_ROOT = app_storage.SAVED_VEHICLE_ROOT
SAVED_SIM_CONFIG_ROOT = app_storage.SAVED_SIM_CONFIG_ROOT
SAVED_RESULTS_ROOT = app_storage.SAVED_RESULTS_ROOT
VEHICLE_WORKSPACE_ROOT = app_storage.VEHICLE_WORKSPACE_ROOT
BUILD_ARCHIVE_ROOT = app_storage.BUILD_ARCHIVE_ROOT
MODELICA_BUILD_CACHE_ROOT = app_storage.MODELICA_BUILD_CACHE_ROOT
SETTINGS_ROOT = app_storage.SETTINGS_ROOT
DEFAULT_SIM_CONFIG_ROOT = app_storage.DEFAULT_SIM_CONFIG_ROOT
OPENMODELICA_SETTINGS_PATH = app_storage.OPENMODELICA_SETTINGS_PATH
RESULT_EXPLORER_ROOTS = (
    Path("_3_StandardSim/generated_results"),
    Path("_3_StandardSim/results"),
    Path("_3_StandardSim/Build"),
    Path("_3_StandardSim/BuildBobLib"),
    Path("_2_EnvelopeSim/results"),
    Path("_2_EnvelopeSim/Build"),
    Path("_4_OptSim/results"),
    Path("_4_OptSim/Build"),
    SAVED_RESULTS_ROOT,
    VEHICLE_WORKSPACE_ROOT,
)
MAX_LOG_CHARS = 120_000
OPENMODELICA_OMC_ENV_KEYS = app_toolchain.OPENMODELICA_OMC_ENV_KEYS
OPENMODELICA_HOME_ENV_KEYS = app_toolchain.OPENMODELICA_HOME_ENV_KEYS
OPENMODELICA_LIBRARY_ENV_KEYS = app_toolchain.OPENMODELICA_LIBRARY_ENV_KEYS
OPENMODELICA_REQUIRED_LIBRARIES = app_toolchain.OPENMODELICA_REQUIRED_LIBRARIES
OPENMODELICA_VERIFY_TIMEOUT_S = app_toolchain.OPENMODELICA_VERIFY_TIMEOUT_S
OPENMODELICA_VERIFY_CACHE = app_toolchain.OPENMODELICA_VERIFY_CACHE

PYTHON_SUBPROCESS_ENCODING = "utf-8:replace"


PYTHON = sys.executable
PYTHON_MODULE_ARG = "--run-module" if FROZEN_APP else "-m"
ACTION_SPECS = build_action_specs(ROOT, PYTHON, PYTHON_MODULE_ARG)
MODELICA_BUILD_TARGETS = build_modelica_build_targets()
MODELICA_BUILD_TARGETS_BY_ACTION = {target.action_id: target for target in MODELICA_BUILD_TARGETS.values()}
MODELICA_RUN_TARGETS_BY_ACTION = {
    "run-ramp-steer": MODELICA_BUILD_TARGETS["vehicle"],
    "run-steady-state": MODELICA_BUILD_TARGETS["vehicle"],
    "run-transient": MODELICA_BUILD_TARGETS["vehicle"],
    "run-four-post": MODELICA_BUILD_TARGETS["four_post"],
    "run-fbrc": MODELICA_BUILD_TARGETS["vehicle"],
}
WORKFLOWS = build_workflows()


_clean_path_string = app_toolchain._clean_path_string
_path_list_value = app_toolchain._path_list_value
_path_is_within = app_toolchain._path_is_within
_strip_env_paths_under = app_toolchain._strip_env_paths_under
_dedupe_paths = app_toolchain._dedupe_paths
_openmodelica_executable_name = app_toolchain._openmodelica_executable_name
_remove_file = app_toolchain._remove_file
_first_env_value = app_toolchain._first_env_value
_configured_path = app_toolchain._configured_path
_path_info = app_toolchain._path_info
_user_path = app_toolchain._user_path
_program_files_dirs = app_toolchain._program_files_dirs
_common_openmodelica_homes = app_toolchain._common_openmodelica_homes
_common_omc_candidates = app_toolchain._common_omc_candidates
_openmodelica_user_library_dirs = app_toolchain._openmodelica_user_library_dirs
_common_openmodelica_libraries = app_toolchain._common_openmodelica_libraries
_is_omc_file = app_toolchain._is_omc_file
_omc_path_candidates = app_toolchain._omc_path_candidates
_normalize_omc_path = app_toolchain._normalize_omc_path
_resolve_omc_path = app_toolchain._resolve_omc_path
_infer_openmodelica_home = app_toolchain._infer_openmodelica_home
_resolve_openmodelica_home = app_toolchain._resolve_openmodelica_home
_configured_library_candidates = app_toolchain._configured_library_candidates
_resolve_openmodelica_library = app_toolchain._resolve_openmodelica_library
_openmodelica_selection_complete = app_toolchain._openmodelica_selection_complete
_openmodelica_selection_verified = app_toolchain._openmodelica_selection_verified
_library_contains_package = app_toolchain._library_contains_package
_missing_openmodelica_libraries = app_toolchain._missing_openmodelica_libraries
_apply_openmodelica_env_paths = app_toolchain._apply_openmodelica_env_paths
_openmodelica_verify_cache_key = app_toolchain._openmodelica_verify_cache_key

_DEFAULT_READ_OPENMODELICA_SETTINGS = app_toolchain._read_openmodelica_settings
_DEFAULT_WRITE_OPENMODELICA_SETTINGS = app_toolchain._write_openmodelica_settings


def _sync_openmodelica_toolchain_runtime() -> None:
    app_toolchain.ROOT = ROOT
    app_toolchain.FROZEN_APP = FROZEN_APP
    app_toolchain.platform = platform
    app_toolchain.shutil = shutil
    app_toolchain.OPENMODELICA_SETTINGS_PATH = OPENMODELICA_SETTINGS_PATH
    app_toolchain.OPENMODELICA_VERIFY_CACHE = OPENMODELICA_VERIFY_CACHE
    app_toolchain._common_omc_candidates = _common_omc_candidates
    app_toolchain._common_openmodelica_libraries = _common_openmodelica_libraries
    app_toolchain._read_openmodelica_settings = (
        _DEFAULT_READ_OPENMODELICA_SETTINGS
        if _read_openmodelica_settings is _READ_OPENMODELICA_SETTINGS_WRAPPER
        else _read_openmodelica_settings
    )
    app_toolchain._write_openmodelica_settings = (
        _DEFAULT_WRITE_OPENMODELICA_SETTINGS
        if _write_openmodelica_settings is _WRITE_OPENMODELICA_SETTINGS_WRAPPER
        else _write_openmodelica_settings
    )


def external_toolchain_enabled() -> bool:
    return app_toolchain.external_toolchain_enabled()


def _openmodelica_settings_file() -> Path:
    return ROOT / OPENMODELICA_SETTINGS_PATH


def _read_openmodelica_settings() -> dict[str, str]:
    app_toolchain.ROOT = ROOT
    app_toolchain.OPENMODELICA_SETTINGS_PATH = OPENMODELICA_SETTINGS_PATH
    return _DEFAULT_READ_OPENMODELICA_SETTINGS()


_READ_OPENMODELICA_SETTINGS_WRAPPER = _read_openmodelica_settings


def _write_openmodelica_settings(settings: dict[str, str]) -> None:
    app_toolchain.ROOT = ROOT
    app_toolchain.OPENMODELICA_SETTINGS_PATH = OPENMODELICA_SETTINGS_PATH
    _DEFAULT_WRITE_OPENMODELICA_SETTINGS(settings)


_WRITE_OPENMODELICA_SETTINGS_WRAPPER = _write_openmodelica_settings


def _sanitize_frozen_external_env(env: dict[str, str]) -> None:
    _sync_openmodelica_toolchain_runtime()
    app_toolchain._sanitize_frozen_external_env(env)


def _verify_openmodelica_selection(settings: dict[str, str]) -> dict[str, str]:
    _sync_openmodelica_toolchain_runtime()
    return app_toolchain._verify_openmodelica_selection(settings)


def _verify_openmodelica_selection_cached(settings: dict[str, str]) -> tuple[dict[str, str] | None, str]:
    _sync_openmodelica_toolchain_runtime()
    return app_toolchain._verify_openmodelica_selection_cached(settings)


def _openmodelica_settings_from_payload(payload: dict[str, Any]) -> dict[str, str]:
    _sync_openmodelica_toolchain_runtime()
    return app_toolchain._openmodelica_settings_from_payload(payload)


def openmodelica_toolchain_payload() -> dict[str, Any]:
    _sync_openmodelica_toolchain_runtime()
    return app_toolchain.openmodelica_toolchain_payload()


def save_openmodelica_toolchain_settings(payload: dict[str, Any]) -> dict[str, Any]:
    _sync_openmodelica_toolchain_runtime()
    return app_toolchain.save_openmodelica_toolchain_settings(payload)


def external_toolchain_available() -> bool:
    return external_toolchain_enabled() and openmodelica_toolchain_payload()["available"]


def external_toolchain_payload() -> dict[str, Any]:
    return openmodelica_toolchain_payload()

def action_available(action: ActionSpec) -> bool:
    return not action.requires_external_toolchain or external_toolchain_available()


def unavailable_action_reason(action: ActionSpec) -> str:
    if action_available(action):
        return ""
    return external_toolchain_payload()["reason"]


def workflow_available(workflow: WorkflowSpec) -> bool:
    return all(action_available(ACTION_SPECS[action_id]) for action_id in workflow.actions)


JOBS = JobStore(MAX_LOG_CHARS)


def _sync_data_services_runtime() -> None:
    app_data_services.ROOT = ROOT
    app_data_services.SAVED_VEHICLE_ROOT = SAVED_VEHICLE_ROOT
    app_data_services.SAVED_SIM_CONFIG_ROOT = SAVED_SIM_CONFIG_ROOT
    app_data_services.SAVED_RESULTS_ROOT = SAVED_RESULTS_ROOT
    app_data_services.VEHICLE_WORKSPACE_ROOT = VEHICLE_WORKSPACE_ROOT
    app_data_services.DEFAULT_SIM_CONFIG_ROOT = DEFAULT_SIM_CONFIG_ROOT
    app_data_services.RESULT_EXPLORER_ROOTS = RESULT_EXPLORER_ROOTS
    app_data_services.WORKFLOWS = tuple(WORKFLOWS)
    app_data_services.MODELICA_RUN_TARGETS_BY_ACTION = MODELICA_RUN_TARGETS_BY_ACTION
    app_data_services.BASE_CONFIG_SPECS = BASE_CONFIG_SPECS
    app_data_services.POWERTRAIN_DEFAULTS = POWERTRAIN_DEFAULTS
    app_data_services.POWERTRAIN_IMPLEMENTATIONS = POWERTRAIN_IMPLEMENTATIONS
    app_data_services.VEHICLE_FIELDS = VEHICLE_FIELDS
    app_data_services.VISUAL_FIELDS = VISUAL_FIELDS
    if "vehicle_workspace_payload" in globals():
        app_data_services.vehicle_workspace_payload = vehicle_workspace_payload


def _data_service_call(name: str, *args: Any, **kwargs: Any) -> Any:
    _sync_data_services_runtime()
    return getattr(app_data_services, name)(*args, **kwargs)

def _safe_repo_path(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_safe_repo_path", *args, **kwargs)


def _path_payload(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_path_payload", *args, **kwargs)


def _csv_preview(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_csv_preview", *args, **kwargs)


def _result_source_roots(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_result_source_roots", *args, **kwargs)


def _is_result_source_path(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_is_result_source_path", *args, **kwargs)


def _result_source_group(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_result_source_group", *args, **kwargs)


def _float_or_none(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_float_or_none", *args, **kwargs)


def _is_float_like(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_is_float_like", *args, **kwargs)


def _csv_source_summary(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_csv_source_summary", *args, **kwargs)


def result_sources_payload(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("result_sources_payload", *args, **kwargs)


def result_source_payload(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("result_source_payload", *args, **kwargs)


def result_series_payload(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("result_series_payload", *args, **kwargs)


def config_specs(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("config_specs", *args, **kwargs)


def _config_spec(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_config_spec", *args, **kwargs)


def _load_yaml_config(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_load_yaml_config", *args, **kwargs)


def _write_yaml_config(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_write_yaml_config", *args, **kwargs)


def _humanize_path_part(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_humanize_path_part", *args, **kwargs)


def _field_key(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_field_key", *args, **kwargs)


def _decode_field_key(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_decode_field_key", *args, **kwargs)


def _is_scalar(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_is_scalar", *args, **kwargs)


def _is_scalar_list(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_is_scalar_list", *args, **kwargs)


def _array_scalars(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_array_scalars", *args, **kwargs)


def _array_shape(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_array_shape", *args, **kwargs)


def _array_element_kind(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_array_element_kind", *args, **kwargs)


def _array_payload(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_array_payload", *args, **kwargs)


def _infer_field_kind(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_infer_field_kind", *args, **kwargs)


def _discover_fields(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_discover_fields", *args, **kwargs)


def _get_nested(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_get_nested", *args, **kwargs)


def _deep_merge_missing(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_deep_merge_missing", *args, **kwargs)


def _vehicle_template_data(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_vehicle_template_data", *args, **kwargs)


def _vehicle_template_for_architecture(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_vehicle_template_for_architecture", *args, **kwargs)


def _vehicle_template_for_axle_architecture(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_vehicle_template_for_axle_architecture", *args, **kwargs)


def _merge_axle_defaults(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_merge_axle_defaults", *args, **kwargs)


def _normalized_bellcrank_order(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_normalized_bellcrank_order", *args, **kwargs)


def _normalize_vehicle_actuation_for_architecture(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_normalize_vehicle_actuation_for_architecture", *args, **kwargs)


def _vehicle_with_powertrain_defaults(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_vehicle_with_powertrain_defaults", *args, **kwargs)


def _vehicle_with_architecture_defaults(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_vehicle_with_architecture_defaults", *args, **kwargs)


def _bellcrank_order_choices(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_bellcrank_order_choices", *args, **kwargs)


def _field_choices(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_field_choices", *args, **kwargs)


def _set_nested(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_set_nested", *args, **kwargs)


def _field_payload(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_field_payload", *args, **kwargs)


def _config_fields(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_config_fields", *args, **kwargs)


def _vehicle_config_fields(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_vehicle_config_fields", *args, **kwargs)


def config_summary(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("config_summary", *args, **kwargs)


def config_payload(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("config_payload", *args, **kwargs)


def patch_config(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("patch_config", *args, **kwargs)


def save_raw_config(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("save_raw_config", *args, **kwargs)


def generate_modelica_payload(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("generate_modelica_payload", *args, **kwargs)


def _configurable_workflow_ids(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_configurable_workflow_ids", *args, **kwargs)


def _sim_config_spec(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_sim_config_spec", *args, **kwargs)


def _sim_config_slug(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_sim_config_slug", *args, **kwargs)


def _saved_sim_config_dir(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_saved_sim_config_dir", *args, **kwargs)


def _default_sim_config_path(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_default_sim_config_path", *args, **kwargs)


def _ensure_default_sim_config(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_ensure_default_sim_config", *args, **kwargs)


def _sim_config_summary(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_sim_config_summary", *args, **kwargs)


def sim_config_library_payload(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("sim_config_library_payload", *args, **kwargs)


def _parse_sim_config_source(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_parse_sim_config_source", *args, **kwargs)


def load_sim_config_source(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("load_sim_config_source", *args, **kwargs)


def save_active_sim_config(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("save_active_sim_config", *args, **kwargs)


def delete_saved_sim_config(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("delete_saved_sim_config", *args, **kwargs)


def _workflow_by_id(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_workflow_by_id", *args, **kwargs)


def _result_slug(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_result_slug", *args, **kwargs)


def _vehicle_workspace_key_from_data(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_vehicle_workspace_key_from_data", *args, **kwargs)


def _normalize_vehicle_workspace_key(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_normalize_vehicle_workspace_key", *args, **kwargs)


def _active_vehicle_workspace_key(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_active_vehicle_workspace_key", *args, **kwargs)


def _vehicle_workspace_dir(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_vehicle_workspace_dir", *args, **kwargs)


def _sync_vehicle_workspace_config(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_sync_vehicle_workspace_config", *args, **kwargs)


def _result_matches_vehicle(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_result_matches_vehicle", *args, **kwargs)


def _processing_workflows_path(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_processing_workflows_path", *args, **kwargs)


def _processing_workflow_payload(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_processing_workflow_payload", *args, **kwargs)


def _read_processing_workflows(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_read_processing_workflows", *args, **kwargs)


def _write_processing_workflows(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_write_processing_workflows", *args, **kwargs)


def processing_workflows_payload(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("processing_workflows_payload", *args, **kwargs)


def add_processing_workflow(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("add_processing_workflow", *args, **kwargs)


def delete_processing_workflow(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("delete_processing_workflow", *args, **kwargs)


def _saved_results_dir(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_saved_results_dir", *args, **kwargs)


def _unique_result_dir(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_unique_result_dir", *args, **kwargs)


def _result_file_payload(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_result_file_payload", *args, **kwargs)


def _json_ready(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_json_ready", *args, **kwargs)


def _workflow_run_target(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_workflow_run_target", *args, **kwargs)


def _workflow_run_roots(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_workflow_run_roots", *args, **kwargs)


def _workflow_run_dirs(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_workflow_run_dirs", *args, **kwargs)


def _read_run_manifest(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_read_run_manifest", *args, **kwargs)


def _run_result_csv(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_run_result_csv", *args, **kwargs)


def _zip_text(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_zip_text", *args, **kwargs)


def _build_signal_archive(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_build_signal_archive", *args, **kwargs)


def _result_manifest_payload(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_result_manifest_payload", *args, **kwargs)


def saved_results_payload(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("saved_results_payload", *args, **kwargs)


def _validated_result_id(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_validated_result_id", *args, **kwargs)


def _remove_result_dir(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_remove_result_dir", *args, **kwargs)


def delete_saved_result(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("delete_saved_result", *args, **kwargs)


def save_active_results(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("save_active_results", *args, **kwargs)


def vehicle_template_payloads(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("vehicle_template_payloads", *args, **kwargs)


def _powertrain_payload(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_powertrain_payload", *args, **kwargs)


def _powertrain_id(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_powertrain_id", *args, **kwargs)


def _vehicle_summary(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_vehicle_summary", *args, **kwargs)


def _load_vehicle_yaml_file(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_load_vehicle_yaml_file", *args, **kwargs)


def _saved_vehicle_id(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_saved_vehicle_id", *args, **kwargs)


def _saved_vehicle_path(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_saved_vehicle_path", *args, **kwargs)


def vehicle_library_payload(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("vehicle_library_payload", *args, **kwargs)


def load_vehicle_source(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("load_vehicle_source", *args, **kwargs)


def save_active_vehicle(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("save_active_vehicle", *args, **kwargs)


def delete_saved_vehicle(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("delete_saved_vehicle", *args, **kwargs)


def _tire_template_root_from_active_vehicle(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_tire_template_root_from_active_vehicle", *args, **kwargs)


def _tire_template_slug(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_tire_template_slug", *args, **kwargs)


def _tire_template_file(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("_tire_template_file", *args, **kwargs)


def tire_template_library_payload(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("tire_template_library_payload", *args, **kwargs)


def read_tire_template(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("read_tire_template", *args, **kwargs)


def save_tire_template(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("save_tire_template", *args, **kwargs)


def apply_vehicle_template(*args: Any, **kwargs: Any) -> Any:
    return _data_service_call("apply_vehicle_template", *args, **kwargs)

def workflow_payload(workflow: WorkflowSpec) -> dict[str, Any]:
    specs = config_specs()
    available = workflow_available(workflow)
    actions = [ACTION_SPECS[action_id] for action_id in workflow.actions]
    outputs = [
        {
            "label": output.label,
            "kind": output.kind,
            **_path_payload(output.path),
        }
        for output in workflow.outputs
    ]
    return {
        "id": workflow.id,
        "group": workflow.group,
        "label": workflow.label,
        "available": available,
        "unavailable_reason": "" if available else external_toolchain_payload()["reason"],
        "config": _path_payload(workflow.config) if workflow.config else None,
        "config_id": workflow.id if workflow.id in specs else None,
        "actions": [
            {
                "id": action.id,
                "label": action.label,
                "argv": list(action.argv),
                "available": action_available(action),
                "unavailable_reason": unavailable_action_reason(action),
            }
            for action in actions
        ],
        "outputs": outputs,
    }


def modelica_stack_payload() -> dict[str, Any]:
    vehicle_target = MODELICA_BUILD_TARGETS["vehicle"]
    four_post_target = MODELICA_BUILD_TARGETS["four_post"]
    vehicle_exe = _modelica_build_exe_path(vehicle_target)
    four_post_exe = _modelica_build_exe_path(four_post_target)
    try:
        payload = modelica_stack_status_payload(_safe_repo_path("vehicle.yml"), ROOT)
    except Exception as exc:
        return {
            "state": "error",
            "written_to_boblib": False,
            "error": str(exc),
            "builds": {
                "vehicle": _modelica_build_payload(vehicle_exe, None, vehicle_target),
                "four_post": _modelica_build_payload(four_post_exe, None, four_post_target),
            },
        }
    payload["builds"] = {
        "vehicle": _modelica_build_payload(vehicle_exe, payload, vehicle_target),
        "four_post": _modelica_build_payload(four_post_exe, payload, four_post_target),
    }
    return payload


def vehicle_workspace_payload(
    vehicle_key: str | None = None,
    *,
    stack: dict[str, Any] | None = None,
) -> dict[str, Any]:
    active_path = _safe_repo_path("vehicle.yml")
    data = _load_vehicle_yaml_file(active_path) if active_path.is_file() else {}
    key = _normalize_vehicle_workspace_key(vehicle_key or _vehicle_workspace_key_from_data(data))
    vehicle = data.get("vehicle", {}) if isinstance(data, dict) else {}
    workspace = _vehicle_workspace_dir(key, create=False)
    rel_workspace = (VEHICLE_WORKSPACE_ROOT / key).as_posix()
    config_path = SAVED_VEHICLE_ROOT / f"{key}.yml"
    results = saved_results_payload(key).get("results", [])
    processing = _read_processing_workflows(key)
    build_payloads = (stack or {}).get("builds", {})
    build_labels = {"vehicle": "VehicleSim", "four_post": "FourPostSim"}
    builds = [
        {
            "id": build_id,
            "label": build_labels.get(build_id, build_id.replace("_", " ").title()),
            **payload,
        }
        for build_id, payload in build_payloads.items()
        if isinstance(payload, dict)
    ]
    return {
        "key": key,
        "label": vehicle.get("name", key) if isinstance(vehicle, dict) else key,
        "workspace": {
            "path": rel_workspace,
            "exists": workspace.exists(),
        },
        "config": _path_payload(config_path.as_posix()),
        "groups": {
            "builds": {
                "path": (VEHICLE_WORKSPACE_ROOT / key / "builds").as_posix(),
                "count": sum(1 for build in builds if build.get("exists")),
            },
            "results": {
                "path": (VEHICLE_WORKSPACE_ROOT / key / "results").as_posix(),
                "count": len(results),
            },
            "processing": {
                "path": (VEHICLE_WORKSPACE_ROOT / key / "processing").as_posix(),
                "count": len(processing),
            },
        },
        "builds": builds,
        "results": results,
        "processing": processing,
    }


def _sync_modelica_build_runtime() -> None:
    modelica_build_module = cast(Any, app_modelica_build)
    app_modelica_build.ROOT = ROOT
    app_modelica_build.BUILD_ARCHIVE_ROOT = BUILD_ARCHIVE_ROOT
    app_modelica_build.MODELICA_BUILD_CACHE_ROOT = BUILD_ARCHIVE_ROOT / "modelica"
    app_modelica_build.APP_MODELICA_BUILD_FINGERPRINT_PATHS = APP_MODELICA_BUILD_FINGERPRINT_PATHS
    app_modelica_build.platform = platform
    app_modelica_build.ACTION_SPECS = ACTION_SPECS
    app_modelica_build.JOBS = JOBS
    app_modelica_build.modelica_stack_status_payload = modelica_stack_status_payload
    app_modelica_build._safe_repo_path = _safe_repo_path
    app_modelica_build._path_payload = _path_payload
    modelica_build_module._fingerprint_paths = _fingerprint_paths
    modelica_build_module.action_available = action_available
    modelica_build_module.unavailable_action_reason = unavailable_action_reason
    app_modelica_build._run_subprocess_action = _run_subprocess_action


def _modelica_build_payload(*args: Any, **kwargs: Any) -> Any:
    _sync_modelica_build_runtime()
    return app_modelica_build._modelica_build_payload(*args, **kwargs)

def status_payload() -> dict[str, Any]:
    vehicle_exe = _modelica_build_exe_path(MODELICA_BUILD_TARGETS["vehicle"])
    four_post_exe = _modelica_build_exe_path(MODELICA_BUILD_TARGETS["four_post"])
    modelica = modelica_stack_payload()
    return {
        "repo": {
            "root": str(ROOT),
            "package_root": str(PACKAGE_ROOT),
            "frozen": FROZEN_APP,
            "boblib_package": _path_payload("_0_Utils/external/BobLib/BobLib/package.mo"),
            "vehicle_exe": _path_payload(vehicle_exe),
            "four_post_exe": _path_payload(four_post_exe),
            "vehicle_yml": _path_payload("vehicle.yml"),
        },
        "runtime": {
            "root": str(ROOT),
            "package_root": str(PACKAGE_ROOT),
            "frozen": FROZEN_APP,
            "home_env": PRIMARY_HOME_ENV,
            "legacy_home_env": LEGACY_HOME_ENV,
            "home_override": os.environ.get(PRIMARY_HOME_ENV) or os.environ.get(LEGACY_HOME_ENV) or "",
            "seed": _runtime_seed_manifest() if FROZEN_APP else None,
            "seed_warnings": list(RUNTIME_SEED_WARNINGS),
        },
        "external_toolchain": external_toolchain_payload(),
        "modelica": modelica,
        "vehicle_workspace": vehicle_workspace_payload(stack=modelica),
        "workflows": [workflow_payload(workflow) for workflow in WORKFLOWS],
        "configs": [config_summary(spec) for spec in config_specs().values()],
        "jobs": JOBS.list()[:8],
    }


_num = tire_eval_core._num
_sign = tire_eval_core._sign
_linspace = tire_eval_core._linspace
_point = tire_eval_core._point
_active_mass_records = tire_eval_core._active_mass_records
_active_static_tire_loads = tire_eval_core._active_static_tire_loads
_active_static_load_summary = tire_eval_core._active_static_load_summary
_tire_template_for_side = tire_eval_core._tire_template_for_side
_mf52_fx_pure = tire_eval_core._mf52_fx_pure
_mf52_fy_pure = tire_eval_core._mf52_fy_pure
_magic_cos_reduction = tire_eval_core._magic_cos_reduction
_mf52_fx_combined = tire_eval_core._mf52_fx_combined
_mf52_fy_combined = tire_eval_core._mf52_fy_combined
_tire_load_values = tire_eval_core._tire_load_values
_mf52_curves = tire_eval_core._mf52_curves


def _tire_template_path(vehicle: dict[str, Any], template: str) -> Path:
    return tire_eval_core._tire_template_path(ROOT, vehicle, template)


def tire_eval_payload(vehicle: dict[str, Any] | None = None) -> dict[str, Any]:
    return tire_eval_core.tire_eval_payload(
        ROOT,
        vehicle,
        load_vehicle_yaml_file=_load_vehicle_yaml_file,
    )


def kinematic_curves_from_active_vehicle() -> dict[str, Any]:
    vehicle = _load_vehicle_yaml_file(_safe_repo_path("vehicle.yml"))
    return kinematic_curves_payload(vehicle)


def read_text_payload(raw_path: str) -> dict[str, Any]:
    path = _safe_repo_path(raw_path)
    if not path.is_file():
        raise FileNotFoundError(raw_path)
    return {
        "path": raw_path,
        "text": path.read_text(encoding="utf-8", errors="replace"),
    }


def _modelica_build_exe_names(*args: Any, **kwargs: Any) -> Any:
    _sync_modelica_build_runtime()
    return app_modelica_build._modelica_build_exe_names(*args, **kwargs)


def _modelica_build_exe_file(*args: Any, **kwargs: Any) -> Any:
    _sync_modelica_build_runtime()
    return app_modelica_build._modelica_build_exe_file(*args, **kwargs)


def _modelica_build_exe_path(*args: Any, **kwargs: Any) -> Any:
    _sync_modelica_build_runtime()
    return app_modelica_build._modelica_build_exe_path(*args, **kwargs)


def _modelica_build_init_name(*args: Any, **kwargs: Any) -> Any:
    _sync_modelica_build_runtime()
    return app_modelica_build._modelica_build_init_name(*args, **kwargs)


def _modelica_build_missing_files(*args: Any, **kwargs: Any) -> Any:
    _sync_modelica_build_runtime()
    return app_modelica_build._modelica_build_missing_files(*args, **kwargs)


def _host_build_fingerprint(*args: Any, **kwargs: Any) -> Any:
    _sync_modelica_build_runtime()
    return app_modelica_build._host_build_fingerprint(*args, **kwargs)


def _sha256_text(*args: Any, **kwargs: Any) -> Any:
    _sync_modelica_build_runtime()
    return app_modelica_build._sha256_text(*args, **kwargs)


def _modelica_build_signature_payload(*args: Any, **kwargs: Any) -> Any:
    _sync_modelica_build_runtime()
    return app_modelica_build._modelica_build_signature_payload(*args, **kwargs)


def _modelica_build_archive_dir(*args: Any, **kwargs: Any) -> Any:
    _sync_modelica_build_runtime()
    return app_modelica_build._modelica_build_archive_dir(*args, **kwargs)


def _modelica_build_dir_ready(*args: Any, **kwargs: Any) -> Any:
    _sync_modelica_build_runtime()
    return app_modelica_build._modelica_build_dir_ready(*args, **kwargs)


def _ensure_modelica_build_directory(*args: Any, **kwargs: Any) -> Any:
    _sync_modelica_build_runtime()
    return app_modelica_build._ensure_modelica_build_directory(*args, **kwargs)


def _modelica_build_metadata_path(*args: Any, **kwargs: Any) -> Any:
    _sync_modelica_build_runtime()
    return app_modelica_build._modelica_build_metadata_path(*args, **kwargs)


def _read_modelica_build_metadata(*args: Any, **kwargs: Any) -> Any:
    _sync_modelica_build_runtime()
    return app_modelica_build._read_modelica_build_metadata(*args, **kwargs)


def _write_modelica_build_metadata(*args: Any, **kwargs: Any) -> Any:
    _sync_modelica_build_runtime()
    return app_modelica_build._write_modelica_build_metadata(*args, **kwargs)


def _modelica_archive_ignore(*args: Any, **kwargs: Any) -> Any:
    _sync_modelica_build_runtime()
    return app_modelica_build._modelica_archive_ignore(*args, **kwargs)


def _modelica_archive_payload(*args: Any, **kwargs: Any) -> Any:
    _sync_modelica_build_runtime()
    return app_modelica_build._modelica_archive_payload(*args, **kwargs)


def _store_modelica_build_archive(*args: Any, **kwargs: Any) -> Any:
    _sync_modelica_build_runtime()
    return app_modelica_build._store_modelica_build_archive(*args, **kwargs)


def _restore_modelica_build_from_archive(*args: Any, **kwargs: Any) -> Any:
    _sync_modelica_build_runtime()
    return app_modelica_build._restore_modelica_build_from_archive(*args, **kwargs)


def _modelica_existing_build_matches(*args: Any, **kwargs: Any) -> Any:
    _sync_modelica_build_runtime()
    return app_modelica_build._modelica_existing_build_matches(*args, **kwargs)


def _run_modelica_build_action(*args: Any, **kwargs: Any) -> Any:
    _sync_modelica_build_runtime()
    return app_modelica_build._run_modelica_build_action(*args, **kwargs)


_DEFAULT_RUN_SUBPROCESS_ACTION = app_actions._run_subprocess_action


def _sync_actions_runtime() -> None:
    actions_module = cast(Any, app_actions)
    app_actions.ROOT = ROOT
    app_actions.PYTHON = PYTHON
    app_actions.PYTHON_SUBPROCESS_ENCODING = PYTHON_SUBPROCESS_ENCODING
    app_actions.JOBS = JOBS
    app_actions.ACTION_SPECS = ACTION_SPECS
    app_actions.WORKFLOWS = tuple(WORKFLOWS)
    app_actions.MODELICA_BUILD_TARGETS_BY_ACTION = MODELICA_BUILD_TARGETS_BY_ACTION
    app_actions.MODELICA_RUN_TARGETS_BY_ACTION = MODELICA_RUN_TARGETS_BY_ACTION
    app_actions.subprocess = subprocess
    app_actions.sys = sys
    app_actions._path_list_value = _path_list_value
    app_actions.openmodelica_toolchain_payload = openmodelica_toolchain_payload
    actions_module._apply_openmodelica_env_paths = _apply_openmodelica_env_paths
    actions_module._sanitize_frozen_external_env = _sanitize_frozen_external_env
    actions_module.action_available = action_available
    actions_module.unavailable_action_reason = unavailable_action_reason
    app_actions._run_modelica_build_action = _run_modelica_build_action
    app_actions._modelica_build_missing_files = _modelica_build_missing_files
    app_actions._workflow_by_id = _workflow_by_id
    app_actions.save_active_results = save_active_results
    app_actions._run_subprocess_action = (
        _DEFAULT_RUN_SUBPROCESS_ACTION
        if _run_subprocess_action is _RUN_SUBPROCESS_ACTION_WRAPPER
        else _run_subprocess_action
    )

def _prepend_env_path(*args: Any, **kwargs: Any) -> Any:
    _sync_actions_runtime()
    return app_actions._prepend_env_path(*args, **kwargs)


def _action_argv(*args: Any, **kwargs: Any) -> Any:
    _sync_actions_runtime()
    return app_actions._action_argv(*args, **kwargs)


def _apply_openmodelica_env(*args: Any, **kwargs: Any) -> Any:
    _sync_actions_runtime()
    return app_actions._apply_openmodelica_env(*args, **kwargs)


def _apply_python_stdio_env(*args: Any, **kwargs: Any) -> Any:
    _sync_actions_runtime()
    return app_actions._apply_python_stdio_env(*args, **kwargs)


def _subprocess_creation_flags(*args: Any, **kwargs: Any) -> Any:
    _sync_actions_runtime()
    return app_actions._subprocess_creation_flags(*args, **kwargs)


def _run_subprocess_action(*args: Any, **kwargs: Any) -> Any:
    _sync_actions_runtime()
    return app_actions._run_subprocess_action(*args, **kwargs)


_RUN_SUBPROCESS_ACTION_WRAPPER = _run_subprocess_action


def _run_action_process(*args: Any, **kwargs: Any) -> Any:
    _sync_actions_runtime()
    return app_actions._run_action_process(*args, **kwargs)


def run_actions_job(*args: Any, **kwargs: Any) -> Any:
    _sync_actions_runtime()
    return app_actions.run_actions_job(*args, **kwargs)


def start_job(*args: Any, **kwargs: Any) -> Any:
    _sync_actions_runtime()
    return app_actions.start_job(*args, **kwargs)


def start_workflow(*args: Any, **kwargs: Any) -> Any:
    _sync_actions_runtime()
    return app_actions.start_workflow(*args, **kwargs)


def _sync_server_runtime() -> None:
    app_server.ROOT = ROOT
    app_server.STATIC_ROOT = STATIC_ROOT
    app_server.JOBS = JOBS
    app_server._parse_byte_range = _parse_byte_range
    app_server.status_payload = status_payload
    app_server.config_summary = config_summary
    app_server.config_specs = config_specs
    app_server.config_payload = config_payload
    app_server.vehicle_library_payload = vehicle_library_payload
    app_server.vehicle_workspace_payload = vehicle_workspace_payload
    app_server.vehicle_template_payloads = vehicle_template_payloads
    app_server.sim_config_library_payload = sim_config_library_payload
    app_server.saved_results_payload = saved_results_payload
    app_server._active_vehicle_workspace_key = _active_vehicle_workspace_key
    app_server.result_sources_payload = result_sources_payload
    app_server.result_source_payload = result_source_payload
    app_server.processing_workflows_payload = processing_workflows_payload
    app_server.tire_eval_payload = tire_eval_payload
    app_server.kinematic_curves_from_active_vehicle = kinematic_curves_from_active_vehicle
    app_server.tire_template_library_payload = tire_template_library_payload
    app_server.read_tire_template = read_tire_template
    app_server.read_text_payload = read_text_payload
    app_server._csv_preview = _csv_preview
    app_server.openmodelica_toolchain_payload = openmodelica_toolchain_payload
    app_server.start_job = start_job
    app_server.save_openmodelica_toolchain_settings = save_openmodelica_toolchain_settings
    app_server.start_workflow = start_workflow
    app_server.save_raw_config = save_raw_config
    app_server.patch_config = patch_config
    app_server.apply_vehicle_template = apply_vehicle_template
    app_server.load_vehicle_source = load_vehicle_source
    app_server.save_active_vehicle = save_active_vehicle
    app_server.delete_saved_vehicle = delete_saved_vehicle
    app_server.generate_modelica_payload = generate_modelica_payload
    app_server.load_sim_config_source = load_sim_config_source
    app_server.save_active_sim_config = save_active_sim_config
    app_server.delete_saved_sim_config = delete_saved_sim_config
    app_server.save_active_results = save_active_results
    app_server.delete_saved_result = delete_saved_result
    app_server.add_processing_workflow = add_processing_workflow
    app_server.delete_processing_workflow = delete_processing_workflow
    app_server.result_series_payload = result_series_payload
    app_server._load_vehicle_yaml_file = _load_vehicle_yaml_file
    app_server._safe_repo_path = _safe_repo_path
    app_server.kinematic_curves_payload = kinematic_curves_payload
    app_server.save_tire_template = save_tire_template


app_server.sync_runtime = _sync_server_runtime
BobSimHandler = app_server.BobSimHandler


def _safe_static_path(*args: Any, **kwargs: Any) -> Any:
    _sync_server_runtime()
    return app_server._safe_static_path(*args, **kwargs)


def _query_one(*args: Any, **kwargs: Any) -> Any:
    return app_server._query_one(*args, **kwargs)


def run(host: str, port: int) -> None:
    _sync_server_runtime()
    app_server.run(host, port)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Run the BobSim browser app.")
    parser.add_argument("--run-module", help="Run a bundled Python module and exit.")
    parser.add_argument("--host", default="127.0.0.1")
    parser.add_argument("--port", type=int, default=8765)
    parser.add_argument("module_args", nargs=argparse.REMAINDER)
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    if args.run_module:
        sys.argv = [args.run_module, *args.module_args]
        runpy.run_module(args.run_module, run_name="__main__", alter_sys=True)
        return
    run(args.host, args.port)


if __name__ == "__main__":
    main()
