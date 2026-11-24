import os
from pathlib import Path

import pytest

from common import model_cache as mc

EXE = "simulations/mbd/BuildBobLib/VehicleSim/BobLib.Experiments.Standards.VehicleSim"
MOS = "simulations/response/mbd/build_vehicle_sim.mos"


@pytest.fixture
def repo(tmp_path):
    (tmp_path / "engines/boblib/BobLib/Chassis").mkdir(parents=True)
    (tmp_path / "engines/boblib/BobLib/package.mo").write_text("package BobLib end BobLib;")
    (tmp_path / "engines/boblib/BobLib/Chassis/Frame.mo").write_text("model Frame end Frame;")
    (tmp_path / MOS).parent.mkdir(parents=True)
    (tmp_path / MOS).write_text("buildModel(...);")
    return tmp_path


class FakeOmc:
    def __init__(self):
        self.calls = 0

    def __call__(self, mos: Path, exe: Path, flags: str):
        self.calls += 1
        exe.parent.mkdir(parents=True, exist_ok=True)
        exe.write_text(f"binary {self.calls} {flags}")
        exe.with_name(exe.name + "_init.xml").write_text("<init/>")
        exe.with_name(exe.name + "_info.json").write_text("{}")
        exe.with_name(exe.name + ".c").write_text("/* generated */")
        exe.with_name(exe.name + "_res.csv").write_text("time\n0\n")


def _build(repo, omc, profile="native", cache=Path(".cache/models"), keep=5):
    return mc.build(
        repo, MOS, EXE, ["engines/boblib/BobLib"], cache, profile, keep,
        compile_fn=omc, version_fn=lambda: "OpenModelica 1.27.1",
    )


def test_builds_once_then_is_fresh(repo):
    omc = FakeOmc()
    assert _build(repo, omc) == "built"
    assert _build(repo, omc) == "fresh"
    assert omc.calls == 1


def test_any_boblib_change_rebuilds_not_just_the_experiment(repo):
    # The old mtime rule only watched VehicleSim.mo, package.mo, records and templates.
    omc = FakeOmc()
    _build(repo, omc)
    (repo / "engines/boblib/BobLib/Chassis/Frame.mo").write_text("model Frame Real x; end Frame;")
    assert _build(repo, omc) == "built"
    assert omc.calls == 2


def test_touching_mtimes_without_content_change_does_not_rebuild(repo):
    omc = FakeOmc()
    _build(repo, omc)
    for path in (repo / "engines").rglob("*.mo"):
        os.utime(path, (1, 1))
    assert _build(repo, omc) == "fresh"


def test_returning_to_an_earlier_source_state_restores_without_omc(repo):
    omc = FakeOmc()
    frame = repo / "engines/boblib/BobLib/Chassis/Frame.mo"
    original = frame.read_text()
    _build(repo, omc)
    frame.write_text("model Frame Real y; end Frame;")
    _build(repo, omc)
    frame.write_text(original)
    assert _build(repo, omc) == "restored"
    assert omc.calls == 2
    exe = repo / EXE
    assert exe.read_text().startswith("binary 1 ")
    assert exe.with_name(exe.name + "_init.xml").is_file()


def test_cache_keeps_runtime_files_only(repo):
    omc = FakeOmc()
    _build(repo, omc)
    (entry,) = (repo / ".cache/models" / Path(EXE).name).iterdir()
    names = sorted(p.name for p in entry.iterdir())
    exe = Path(EXE).name
    assert names == sorted([exe, exe + "_init.xml", exe + "_info.json", "manifest.json"])


def test_deleted_build_is_restored_from_cache(repo):
    omc = FakeOmc()
    _build(repo, omc)
    (repo / EXE).unlink()
    assert _build(repo, omc) == "restored"
    assert omc.calls == 1


def test_flags_and_omc_version_are_part_of_the_key(repo):
    src = ["engines/boblib/BobLib", MOS]
    base = mc.build_key(repo, src, "-O3", "1.27.1")
    assert base != mc.build_key(repo, src, "-O2", "1.27.1")
    assert base != mc.build_key(repo, src, "-O3", "1.28.0")


def test_only_native_builds_depend_on_the_cpu(repo):
    src = ["engines/boblib/BobLib"]
    a, b = {"cpu_model": "A"}, {"cpu_model": "B"}
    native = "-O3 -march=native -mtune=native"
    assert mc.build_key(repo, src, native, "v", a) != mc.build_key(repo, src, native, "v", b)
    assert mc.build_key(repo, src, "-O3", "v", a) == mc.build_key(repo, src, "-O3", "v", b)


def test_profiles():
    assert mc.cflags("portable") == "-O3"
    assert mc.cflags("native", "x86_64") == "-O3 -march=native -mtune=native"
    assert mc.cflags("native", "aarch64") == "-O3 -mcpu=native -mtune=native"
    with pytest.raises(ValueError):
        mc.cflags("fast")


def test_portable_profile_builds_with_portable_flags(repo):
    omc = FakeOmc()
    _build(repo, omc, profile="portable")
    assert (repo / EXE).read_text() == "binary 1 -O3"


def test_prune_keeps_the_newest_entries(repo):
    omc = FakeOmc()
    frame = repo / "engines/boblib/BobLib/Chassis/Frame.mo"
    for i in range(4):
        frame.write_text(f"model Frame Real x{i}; end Frame;")
        _build(repo, omc, keep=2)
    entries = [p for p in (repo / ".cache/models" / Path(EXE).name).iterdir() if p.is_dir()]
    assert len(entries) == 2


def test_missing_submodule_is_a_clear_error(tmp_path):
    with pytest.raises(FileNotFoundError, match="submodule"):
        mc.source_digest(tmp_path, ["engines/boblib/BobLib"])


def test_git_and_pycache_are_ignored(repo):
    src = ["engines/boblib/BobLib"]
    before = mc.source_digest(repo, src)
    (repo / "engines/boblib/BobLib/__pycache__").mkdir()
    (repo / "engines/boblib/BobLib/__pycache__/x.pyc").write_bytes(b"junk")
    assert mc.source_digest(repo, src) == before


def test_the_operating_system_is_part_of_the_key(repo, monkeypatch):
    src = ["engines/boblib/BobLib"]
    monkeypatch.setattr(mc.platform, "system", lambda: "Linux")
    linux = mc.build_key(repo, src, "-O3", "v")
    monkeypatch.setattr(mc.platform, "system", lambda: "Darwin")
    assert mc.build_key(repo, src, "-O3", "v") != linux


def _fake_run(outputs, seen):
    def run(cmd, **kwargs):
        seen.append(cmd[0])
        out = outputs[cmd[0]]
        if isinstance(out, Exception):
            raise out
        return mc.subprocess.CompletedProcess(cmd, 0, stdout=out, stderr="")
    return run


def test_toolchain_names_the_compiler_omc_uses(monkeypatch):
    seen = []
    outputs = {"omc": '"clang"\n', "clang": "clang version 18.1.3\nTarget: x86_64\n"}
    monkeypatch.setattr(mc.subprocess, "run", _fake_run(outputs, seen))
    assert mc.c_compiler_version() == "clang version 18.1.3"
    assert seen == ["omc", "clang"]


def test_a_compiler_upgrade_changes_the_toolchain(monkeypatch):
    outputs = {"omc": "OpenModelica 1.27.1\n", "cc": "gcc 13.2.0\n"}
    monkeypatch.setattr(mc.subprocess, "run", _fake_run(outputs, []))
    before = mc.toolchain_version()
    outputs["cc"] = "gcc 14.1.0\n"
    assert mc.toolchain_version() != before
    assert before.startswith("OpenModelica 1.27.1")


def test_an_unreadable_compiler_still_gives_a_stable_toolchain(monkeypatch):
    outputs = {"omc": "", "cc": FileNotFoundError("cc")}
    monkeypatch.setattr(mc.subprocess, "run", _fake_run(outputs, []))
    assert mc.c_compiler_version() == "cc (version unknown)"
