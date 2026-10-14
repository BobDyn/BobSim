from __future__ import annotations

from dataclasses import dataclass
import json
from pathlib import Path
from types import SimpleNamespace

import pytest
import yaml

from simulations.lap import lap_time_eval_sim as lap


@pytest.fixture
def provenance_workspace(tmp_path: Path, monkeypatch):
    monkeypatch.setattr(lap, 'repo_root', lambda: tmp_path)
    monkeypatch.setattr(lap, '__file__', str(tmp_path / 'lap.py'))
    for name in ('lap.py', 'simulations/envelope/ggv/ggv_generation.py',
                 'simulations/envelope/ggv/parallel.py',
    'simulations/envelope/vehicle_yaml.py', 'common/vehicle_io.py',
                 'engines/dynpy/parameters.py', 'engines/kinpy/geometry.py'):
        path = tmp_path / name
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text('# physics\n')
    tires = tmp_path / 'tires'
    tires.mkdir()
    (tires / 'front.tir').write_text('PDX1 = 1.5\n')
    (tires / 'rear.tir').write_text('PDX1 = 1.6\n')
    vehicle = tmp_path / 'vehicle.yml'
    vehicle.write_text(yaml.safe_dump({
        'paths': {'tire_templates': tires.as_posix()},
        'aero': {'tire_template': 'unused-global'},
        'front': {'tire': {'template': 'front'}},
        'rear': {'tire': {'template': 'rear'}},
    }))
    return tmp_path, dict(vehicle_path=vehicle, model_dof=3, qss_config={}, effective_power_limit_w=80000)


@pytest.mark.parametrize('relative', [
    'tires/front.tir', 'tires/rear.tir',
    'simulations/mbd/generated_results/four_post_eval_report_metrics.csv',
    'simulations/mbd/results/four_post_eval_report_metrics.csv',
    'simulations/envelope/vehicle_yaml.py', 'common/vehicle_io.py',
    'engines/kinpy/geometry.py', 'simulations/envelope/ggv/parallel.py',
])
def test_ggv_fingerprint_tracks_referenced_physics(provenance_workspace, relative):
    root, arguments = provenance_workspace
    before = lap._ggv_provenance(**arguments)['fingerprint']
    path = root / relative
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text('changed physical input\n')
    after = lap._ggv_provenance(**arguments)['fingerprint']
    assert before != after
    if 'four_post' in relative:
        path.unlink()
        assert lap._ggv_provenance(**arguments)['fingerprint'] == before


def test_ggv_cache_reused_only_while_inputs_match(provenance_workspace, monkeypatch):
    from simulations.envelope.ggv import ggv_generation
    from simulations.envelope import vehicle_yaml

    root, arguments = provenance_workspace
    path = root / 'ggv.csv'
    path.write_text('cached envelope')
    metadata = path.with_suffix('.csv.metadata.json')
    metadata.write_text(json.dumps(lap._ggv_provenance(**arguments)))
    monkeypatch.setattr(lap.GGVMap, 'from_csv', lambda _: 'cached')
    result, provenance = lap._load_or_generate_ggv(path, model=None, **arguments)
    assert result == 'cached'
    assert provenance['status'] == 'verified_cache'

    @dataclass
    class Projection:
        max_drive_power: float = 80000
        max_drive_speed: float = 42.0

    monkeypatch.setattr(vehicle_yaml, 'project_vehicle_yaml', lambda _: SimpleNamespace(ggv=Projection()))

    def regenerate(*args, **kwargs):
        raise RuntimeError('regenerating stale envelope')

    monkeypatch.setattr(ggv_generation, 'generate_ggv', regenerate)
    current = metadata.read_text()
    legacy = json.loads(current)
    legacy['schema'] = 'bobsim.ggv-provenance.v2'
    legacy.pop('formulation')
    metadata.write_text(json.dumps(legacy))
    with pytest.raises(RuntimeError, match='regenerating stale'):
        lap._load_or_generate_ggv(path, model=None, **arguments)
    metadata.write_text(current)
    arguments['qss_config']['regenerate'] = True
    with pytest.raises(RuntimeError, match='regenerating stale'):
        lap._load_or_generate_ggv(path, model=None, **arguments)
    arguments['qss_config'].pop('regenerate')
    (root / 'tires/front.tir').write_text('PDX1 = 0.8\n')
    with pytest.raises(RuntimeError, match='regenerating stale'):
        lap._load_or_generate_ggv(path, model=None, **arguments)
    metadata.write_text('{broken metadata')
    with pytest.raises(RuntimeError, match='regenerating stale'):
        lap._load_or_generate_ggv(path, model=None, **arguments)


def test_linked_ggv_is_verified_without_regeneration(provenance_workspace, monkeypatch):
    import hashlib

    root, arguments = provenance_workspace
    path = root / 'saved.csv'
    path.write_text('saved envelope')
    signature_args = {**arguments, 'model_dof': 3, 'qss_config': {}, 'effective_power_limit_w': 0.}
    linked = {'signature': lap._ggv_provenance(**signature_args)['fingerprint'],
              'model_dof': 3, 'power_limit_w': 80000,
              'csv_sha256': hashlib.sha256(path.read_bytes()).hexdigest(), 'run_id': 'saved-ggv'}
    arguments['qss_config'] = {'linked_ggv': linked, 'generate_if_missing': False}
    monkeypatch.setattr(lap.GGVMap, 'from_csv', lambda _: 'saved map')
    result, provenance = lap._load_or_generate_ggv(path, model=None, **arguments)
    assert result == 'saved map'
    assert provenance['status'] == 'linked'
    assert provenance['run_id'] == 'saved-ggv'
    solver = root / 'simulations/envelope/ggv/ggv_generation.py'
    original_solver = solver.read_text()
    solver.write_text('# new path acceleration formulation\n')
    with pytest.raises(ValueError, match='no longer matches'):
        lap._load_or_generate_ggv(path, model=None, **arguments)
    solver.write_text(original_solver)
    with pytest.raises(ValueError, match='model or power'):
        lap._load_or_generate_ggv(path, model=None, **{**arguments, 'model_dof': 14})
    path.write_text('modified envelope')
    with pytest.raises(ValueError, match='file changed'):
        lap._load_or_generate_ggv(path, model=None, **arguments)
    path.unlink()
    with pytest.raises(FileNotFoundError, match='missing'):
        lap._load_or_generate_ggv(path, model=None, **arguments)


def test_supplied_ggv_rejects_known_legacy_formulation(provenance_workspace, monkeypatch):
    root, arguments = provenance_workspace
    path = root / 'supplied.csv'
    path.write_text('saved envelope')
    metadata = path.with_suffix('.csv.metadata.json')
    provenance = lap._ggv_provenance(**arguments)
    assert provenance['schema'] == 'bobsim.ggv-provenance.v3'
    assert provenance['formulation']['acceleration_frame'] == 'path_tangent_normal'
    provenance['schema'] = 'bobsim.ggv-provenance.v2'
    provenance.pop('formulation')
    metadata.write_text(json.dumps(provenance))
    arguments['qss_config'] = {'generate_if_missing': False}
    with pytest.raises(ValueError, match='older acceleration formulation'):
        lap._load_or_generate_ggv(path, model=None, **arguments)
    assert path.read_text() == 'saved envelope'
    assert json.loads(metadata.read_text())['schema'].endswith('.v2')

    metadata.unlink()
    monkeypatch.setattr(lap.GGVMap, 'from_csv', lambda _: 'external map')
    result, external = lap._load_or_generate_ggv(path, model=None, **arguments)
    assert result == 'external map'
    assert external['status'] == 'supplied_unverified'


def test_generated_lap_envelope_covers_vehicle_speed(provenance_workspace, monkeypatch):
    from simulations.envelope.ggv import ggv_generation
    from simulations.envelope import vehicle_yaml

    root, arguments = provenance_workspace

    @dataclass
    class Projection:
        max_drive_power: float = 100000
        max_drive_speed: float = 22.

    monkeypatch.setattr(vehicle_yaml, 'project_vehicle_yaml', lambda _: SimpleNamespace(ggv=Projection()))
    arguments['qss_config'] = {'speeds_mps': [5., 10.]}
    captured = []
    monkeypatch.setattr(ggv_generation, 'generate_ggv',
                        lambda vehicle, config, **kwargs: captured.append((vehicle, config)) or [])
    monkeypatch.setattr(ggv_generation, 'save_ggv_csv', lambda *args: None)
    monkeypatch.setattr(lap.GGVMap, 'from_csv', lambda _: 'generated map')
    result, provenance = lap._load_or_generate_ggv(root / 'new.csv', model=None, **arguments)
    assert result == 'generated map'
    assert provenance['status'] == 'generated'
    assert captured[0][1].speeds == (5., 10., 15., 20., 22.)
    assert captured[0][0].max_drive_power == 80000
