from __future__ import annotations

from dataclasses import dataclass
import json
from pathlib import Path
from types import SimpleNamespace

import pytest
import yaml

from _3_StandardSim.LapTimeEval import lap_time_eval_sim as lap


@pytest.fixture
def provenance_workspace(tmp_path: Path, monkeypatch):
    monkeypatch.setattr(lap, 'repo_root', lambda: tmp_path)
    monkeypatch.setattr(lap, '__file__', str(tmp_path / 'lap.py'))
    for name in ('lap.py', '_2_EnvelopeSim/GGV/ggv_generation.py',
                 '_2_EnvelopeSim/vehicle_yaml.py', '_0_Utils/vehicle_io.py',
                 '_0_Utils/dyn_py/parameters.py', '_0_Utils/kin_py/geometry.py'):
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
        'front': {'tire': {'template': 'front'}},
        'rear': {'tire': {'template': 'rear'}},
    }))
    return tmp_path, dict(vehicle_path=vehicle, model_dof=3, qss_config={}, effective_power_limit_w=80000)


@pytest.mark.parametrize('relative', [
    'tires/front.tir', 'tires/rear.tir',
    '_3_StandardSim/generated_results/four_post_eval_report_metrics.csv',
    '_3_StandardSim/results/four_post_eval_report_metrics.csv',
    '_2_EnvelopeSim/vehicle_yaml.py', '_0_Utils/vehicle_io.py',
    '_0_Utils/kin_py/geometry.py',
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
    from _2_EnvelopeSim.GGV import ggv_generation
    from _2_EnvelopeSim import vehicle_yaml

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

    monkeypatch.setattr(vehicle_yaml, 'project_vehicle_yaml', lambda _: SimpleNamespace(ggv=Projection()))

    def regenerate(*args, **kwargs):
        raise RuntimeError('regenerating stale envelope')

    monkeypatch.setattr(ggv_generation, 'generate_ggv', regenerate)
    (root / 'tires/front.tir').write_text('PDX1 = 0.8\n')
    with pytest.raises(RuntimeError, match='regenerating stale'):
        lap._load_or_generate_ggv(path, model=None, **arguments)
    metadata.write_text('{broken metadata')
    with pytest.raises(RuntimeError, match='regenerating stale'):
        lap._load_or_generate_ggv(path, model=None, **arguments)
