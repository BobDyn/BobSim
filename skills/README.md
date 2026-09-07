# Skills

Packaged, repeatable procedures for tasks that are more than "read a doc and
run a command" — multi-step workflows where the value is in the judgment
calls and verification steps, not just the command syntax. Agent-agnostic
plain directories, readable and runnable by any coding agent or human; not
tied to any one tool's skills format.

Each skill is a folder with a `SKILL.md`: what it's for, when to reach for
it, the steps, and which underlying script/target actually does the work
(skills document and sequence existing tools in `_0_Utils` / the makefile —
they don't duplicate that logic).

| Skill | Use it when |
| --- | --- |
| [shark-import](shark-import/SKILL.md) | Importing Lotus SHARK suspension geometry into a `vehicle.yml`, including the vertical-datum check. |
| [regression-baseline-refresh](regression-baseline-refresh/SKILL.md) | Updating `tests/regression_baselines/default_vehicle_standard.yml` after an intentional physics/model change. |

If you're just running a single documented command, you want
[`docs/workflows.md`](../docs/workflows.md) or `make help`, not a skill here.
