"""Vehicle-response workflows using Architecture's validated maneuver binary."""
from __future__ import annotations

import argparse
import copy
from pathlib import Path
from typing import Any

from app.native_calibration import vehicle_overrides
from common import config_io, native_artifacts as artifacts
from common.vehicle_io import load_yaml, vehicle_yaml_path

ACTIONS = {'run-ramp-steer', 'run-steady-state', 'run-transient',
           'run-mbd-step-steer', 'run-mbd-maneuver'}


def bundle(vehicle: dict):
    """Require a source-matched binary and validate the saved calibration."""
    selection = artifacts.architecture(vehicle)
    directory = artifacts.artifact_dir(selection, 'maneuver')
    manifest = artifacts.checked_manifest(directory)
    if manifest['identity'] != artifacts.identity(selection, 'maneuver'):
        raise ValueError('Build the matching maneuver binary in Architecture first.')
    overrides = artifacts.validate_overrides(manifest, vehicle_overrides(vehicle, manifest, artifacts.ROOT))
    return directory, manifest, overrides


def unavailable_reason(vehicle: dict) -> str:
    """Check runtime readiness without requiring a compiler or generated record."""
    try:
        bundle(vehicle)
    except (OSError, KeyError):
        return 'Build the matching maneuver binary in Architecture first.'
    except (ValueError, TypeError) as exc:
        return f'Architecture maneuver binary is not ready: {exc}'
    return ''


def configure(config: dict, vehicle: dict | None = None) -> dict:
    """Bind a report workflow to its binary and runtime calibration."""
    directory, manifest, overrides = bundle(vehicle if vehicle is not None else load_yaml(vehicle_yaml_path()))
    from simulations.response.mbd._modelica_runner import MODELICA_OVERRIDE_ALIASES
    result = copy.deepcopy(config)
    simulation = result.setdefault('simulation', {})
    simulation.update(build_dir=directory.as_posix(), exec_name=manifest['executable'],
                      runtime_overrides=overrides, strict_overrides=True, geometry_prefix="chassis.",
                      override_aliases={key: value.replace('vcu.', 'driver.')
                                        for key, value in MODELICA_OVERRIDE_ALIASES.items()})
    simulation['override_aliases']['frRampSteerDuration'] = 'driver.stepDuration'
    simulation['extra_args'] = [arg for arg in simulation.get('extra_args', []) if not arg.startswith('-nls=')]
    simulation['extra_args'].append('-nls=' + manifest['nonlinear_solver'])
    return result


def run(workflow: str, config_path: Path | None = None) -> None:
    """Reuse the established response metrics and reports without compilation."""
    from common.reporting.report_engine import ReportEngine
    from simulations.response.mbd.ramp_steer.ramp_steer_eval_sim import RampSteerEvalSim
    from simulations.response.mbd.steady_state.steady_state_eval_sim import SteadyStateEvalSim
    from simulations.response.mbd.transient.transient_eval_sim import TransientEvalSim
    classes: dict[str, Any] = {'ramp-steer': RampSteerEvalSim, 'steady-state': SteadyStateEvalSim,
               'transient': TransientEvalSim, 'mbd-step-steer': TransientEvalSim}
    folder = workflow.replace('-', '_') if workflow != 'mbd-step-steer' else 'transient'
    filename = folder + '_eval_config.yml' if workflow != 'mbd-step-steer' else 'step_steer_config.yml'
    path = config_path or config_io.resolve(f'simulations/response/mbd/{folder}/{filename}')
    config = configure(load_yaml(Path(path)))
    result = classes[workflow](config).run()
    if config.get('report', {}).get('enabled', True):
        ReportEngine(config).build(result)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('workflow', choices=['ramp-steer', 'steady-state', 'transient', 'mbd-step-steer'])
    run(parser.parse_args().workflow)
