# BobSim Docs

Repo-local documentation. The public/expanded docs live at https://bobdyn.com —
this folder is the checked-in, version-matched subset that explains how *this*
working copy is laid out and how to drive it.

Read in this order:

| Doc | Read it when |
| --- | --- |
| [architecture.md](architecture.md) | You need the `_0_` … `_5_` layer map and how data flows between them. Start here. |
| [workflows.md](workflows.md) | You want to *run* something: app, standard studies, envelopes, sensitivities, tests. |
| [doe-reverse-engineering.md](doe-reverse-engineering.md) | You are doing DOE work — sweeping parameters or going backwards from target performance metrics to a car. Start here for `make opt-standard`. |

| [reduced-order-dynamics.md](reduced-order-dynamics.md) | You are working on 3/6/10/14DOF transient models, QSS envelopes, or BobLib correlation. |
| [lap-time-simulation.md](lap-time-simulation.md) | You are optimizing a QSS racing line/speed profile or running the same lap as a forward transient. |
| [boblib-submodule.md](boblib-submodule.md) | Modelica models are missing, builds fail with "file not found", or you touched BobLib. |

## Conventions used in these docs

- Paths are relative to the repo root.
- Numbered top-level directories (`_0_Utils` … `_5_App`) are pipeline *layers*,
  not an import ordering. See [architecture.md](architecture.md).
- Anything under a `Build/`, `results/`, `generated_results/`, `population/`, or
  `user_data/` directory is generated runtime content and is gitignored. Never
  hand-edit it and never commit it.
- `make help` is the authoritative list of targets. These docs explain the
  *why*; the makefile is the *what*.
