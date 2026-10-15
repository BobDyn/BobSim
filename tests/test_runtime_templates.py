from pathlib import Path

import pytest

from app.runtime import _seed_runtime_root


@pytest.mark.parametrize('relative', ['common/tire_templates', 'common/vehicle_templates'])
def test_template_seeding_preserves_edits_and_adds_missing_files(tmp_path, relative):
    package = tmp_path / 'package'
    runtime = tmp_path / 'runtime'
    shipped = package / relative
    saved = runtime / relative
    shipped.mkdir(parents=True)
    (shipped / 'stock').write_text('original template')
    _seed_runtime_root(runtime, package_root=package)
    assert (saved / 'stock').read_text() == 'original template'

    (saved / 'stock').write_text('user edit')
    (saved / 'custom').write_text('custom template')
    (shipped / 'stock').write_text('updated shipped template')
    (shipped / 'nested').mkdir()
    (shipped / 'nested/new').write_text('new template')
    (shipped / '__pycache__').mkdir()
    (shipped / '__pycache__/ignored.pyc').write_bytes(b'cache')
    _seed_runtime_root(runtime, package_root=package)
    assert (saved / 'nested/new').read_text() == 'new template'
    assert not (saved / '__pycache__').exists()

    (saved / 'nested/new').write_text('nested user edit')
    (shipped / 'nested/another').write_text('another new template')
    _seed_runtime_root(runtime, package_root=package)
    assert (saved / 'stock').read_text() == 'user edit'
    assert (saved / 'custom').read_text() == 'custom template'
    assert (saved / 'nested/new').read_text() == 'nested user edit'
    assert (saved / 'nested/another').read_text() == 'another new template'


@pytest.mark.parametrize('conflict', ['root', 'file', 'directory'])
def test_template_seeding_preserves_existing_type_conflicts(tmp_path, conflict):
    package = tmp_path / 'package'
    runtime = tmp_path / 'runtime'
    relative = Path('common/tire_templates')
    shipped = package / relative
    saved = runtime / relative
    shipped.mkdir(parents=True)
    (shipped / 'stock').write_text('shipped template')
    if conflict == 'root':
        saved.parent.mkdir(parents=True)
        saved.write_text('existing user file')
    else:
        saved.mkdir(parents=True)
        if conflict == 'file':
            (shipped / 'nested').mkdir()
            (shipped / 'nested/new').write_text('shipped template')
            (saved / 'nested').write_text('existing user file')
        else:
            (saved / 'stock').mkdir()
            (saved / 'stock/custom').write_text('existing user file')

    _seed_runtime_root(runtime, package_root=package)
    preserved = {'root': saved, 'file': saved / 'nested', 'directory': saved / 'stock/custom'}[conflict]
    assert preserved.read_text() == 'existing user file'


@pytest.mark.parametrize('link_at_root', [False, True])
def test_template_seeding_does_not_follow_existing_directory_links(tmp_path, link_at_root):
    package = tmp_path / 'package'
    runtime = tmp_path / 'runtime'
    relative = Path('common/tire_templates')
    shipped = package / relative
    saved = runtime / relative
    outside = tmp_path / 'user-templates'
    outside.mkdir()
    (outside / 'stock').write_text('user edit')
    source = shipped if link_at_root else shipped / 'nested'
    target = saved if link_at_root else saved / 'nested'
    source.mkdir(parents=True)
    target.parent.mkdir(parents=True)
    (source / 'stock').write_text('shipped template')
    (source / 'new').write_text('new template')
    try:
        target.symlink_to(outside, target_is_directory=True)
    except OSError:
        pytest.skip('Directory symlinks are unavailable')

    _seed_runtime_root(runtime, package_root=package)
    assert target.is_symlink()
    assert (outside / 'stock').read_text() == 'user edit'
    assert not (outside / 'new').exists()
