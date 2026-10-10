"""Cache provenance independent of the compiler artifact regression tests."""
import sys

import pytest
import yaml

from _0_Utils.vehicle_io import repo_root

OPTSIM_DIR = repo_root() / "_4_OptSim"
if str(OPTSIM_DIR) not in sys.path:
    sys.path.insert(0, str(OPTSIM_DIR))


@pytest.mark.parametrize('changed', ['baseline', 'vehicle', 'source', 'metrics', 'template'])
def test_pipeline_hash_covers_referenced_inputs_and_dirty_boblib(tmp_path, monkeypatch, changed):
    from StandardSens.pipeline import _pipeline_hash as hashes
    monkeypatch.setattr(hashes, '_boblib_sha', lambda _path: 'unchanged-commit')
    config_dir = tmp_path / 'configs'
    config_dir.mkdir()
    boblib = tmp_path / 'BobLib'
    boblib.mkdir()
    files = {name: tmp_path / name for name in ('baseline', 'vehicle', 'metrics', 'template')}
    files['source'] = boblib / 'Physics.mo'
    for path in files.values():
        path.write_text('original')
    doe = config_dir / 'doe.yml'
    doe.write_text(yaml.safe_dump({'baseline_mo': '../baseline', 'architecture': {'template': 'vehicle'}}))
    compiler = config_dir / 'compiler.yml'
    compiler.write_text('{}')
    kwargs = dict(doe_config=doe, compiler_config=compiler, boblib_path=boblib / 'package.mo',
                  extra_inputs=(files['metrics'], files['template']))
    first = hashes.compute_pipeline_hash(**kwargs)
    files[changed].write_text('changed')
    assert hashes.compute_pipeline_hash(**kwargs) != first
    files[changed].unlink()
    assert hashes.compute_pipeline_hash(**kwargs) != first


def test_variant_cache_checks_midrun_changes_even_for_existing_variants(tmp_path, monkeypatch):
    from StandardSens.pipeline.variants import VariantStore, variant_key
    store = VariantStore.__new__(VariantStore)
    store.variants_dir = tmp_path
    store._index = {variant_key({}): 0}
    monkeypatch.setattr(store, '_inputs_changed', lambda: True)
    with pytest.raises(RuntimeError, match='changed while this run'):
        store.ensure_compiled([{}])
