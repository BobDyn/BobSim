# The BobLib submodule

```
path: _0_Utils/external/BobLib
url:  https://github.com/BobDyn/BobLib.git
```

BobLib is the Modelica physics library. BobSim pins an exact BobLib commit; that
pin is part of BobSim's source. A stale submodule is the single most common
cause of "it doesn't build on my machine".

## Always start here

```bash
make init          # == git submodule update --init --recursive
git submodule status
```

Read the status prefix carefully:

| Prefix | Meaning |
| --- | --- |
| (space) | In sync. Good. |
| `-` | Not initialized. Run `make init`. |
| `+` | **Checked-out commit ≠ the pinned commit.** |
| `U` | Merge conflict in the submodule. |

A `+` does *not* tell you which direction the drift goes. Check explicitly:

```bash
PINNED=$(git ls-tree HEAD _0_Utils/external/BobLib | awk '{print $3}')
git -C _0_Utils/external/BobLib log --oneline $PINNED..HEAD   # your local extra commits
git -C _0_Utils/external/BobLib log --oneline HEAD..$PINNED   # commits you are missing
```

- Only the **second** command prints output → you are behind. Run `make init`.
- Only the **first** prints output → you have local BobLib work. Do not run
  `make init` (it discards nothing committed, but it will move you off your
  work). Push BobLib first, then bump the pin.

## Expected layout

After a correct checkout the submodule contains a **nested** `BobLib/` package
directory:

```
_0_Utils/external/BobLib/          # the git repo
├── AGENTS.md                      # BobLib's own agent notes — read it before editing models
├── BobLib/                        # the Modelica package
│   ├── package.mo
│   ├── Records/VehicleDefn/*.mo   # vehicle records BobSim generates into
│   └── Experiments/Standards/     # VehicleSim.mo, FourPostSim.mo, VehicleFMI
├── Tests/                         # BobLibTest Modelica package
├── CHANGELOG.md
└── makefile
```

The double `BobLib/BobLib/` is correct and load-bearing. `conftest.py` sets
`BOBLIB_PACKAGE_ROOT` to the inner directory, and the makefile derives
`BOBLIB_PACKAGE_PATH` from it.

**Diagnostic:** if `_0_Utils/external/BobLib/` has `Vehicle/`, `Standards/`, and
`Resources/` at its *top* level with no nested `BobLib/`, you are on a pre-0.1.1
checkout. The build targets will fail looking for
`BobLib/BobLib/Experiments/Standards/VehicleSim.mo`. Fix with `make init`.

Note the package path also changed in that release:
`Standards.VehicleSim` → `Experiments.Standards.VehicleSim`, and
`Resources.VehicleRecord` → `Records.VehicleRecord`. BobLib's own top-level
`README.md` documents the current entry points; older docs and branches may
reference the flat paths.

## Bumping the pin

```bash
git -C _0_Utils/external/BobLib fetch origin
git -C _0_Utils/external/BobLib checkout <commit-or-tag>
git add _0_Utils/external/BobLib
git commit -m "Bump BobLib to <version>"
```

Commit the gitlink change on its own or alongside the BobSim changes it enables
— never leave the pin bumped in a working tree and uncommitted, since collaborators
will silently get the old commit.

After any bump, regenerate and re-check:

```bash
make clean-standard
make regression-baseline
```

A BobLib bump can change physics. `make test` alone will not catch it.

## Detached HEAD is normal

Submodules check out a specific commit, so `git -C _0_Utils/external/BobLib
branch --show-current` printing nothing (HEAD detached) is expected, not a
problem. Only create a branch there if you are actually developing BobLib.

## Editing BobLib

- BobLib is a separate repository with its own CI, tests, and release process.
  Changes there need a PR in `BobDyn/BobLib`, not in BobSim.
- Read `_0_Utils/external/BobLib/AGENTS.md` first. It documents package boundary
  rules (VehicleInterfaces contract layer, where physics/templates/utilities
  belong, records mirroring subsystem packages) that are easy to violate.
- Generated vehicle records under `Records/VehicleDefn/` are written by
  `_5_App/modelica_generator.py`. Hand-edits there get overwritten on the next
  generate — change `vehicle.yml` or the generator instead.
