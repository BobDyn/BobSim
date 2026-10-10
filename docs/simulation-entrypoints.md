# Simulation Entrypoints

BobSim offers multiple simulation workflows, each with different fidelity levels and use cases. **When generating analysis results, always specify which workflow was used so readers understand whether results came from a high-fidelity MBD study or a fast quasi-steady envelope.**

## Engines and execution

| Engine | Fidelity | Runtime |
| --- | --- | --- |
| KinPy | Suspension geometry | Python |
| DynPy | 3, 6, 10 or 14 DOF | Python |
| BobLib | MBD | OpenModelica compiled executable |

DynPy 3DOF models planar motion. 6DOF adds heave, roll and pitch. 10DOF adds
four wheel rotations. 14DOF adds four unsprung vertical motions.
Select `REDUCED_DOF` for reduced transients, `generation.model_dof` for envelopes,
and `model_dof` or `LAP_DOF` for laps. QSS and transient are analysis methods.
Runtime duration depends on the model, grid and hardware. Compilation is a
separate cost for BobLib, and no fixed duration is promised here.

## Workflows

### VehicleSim / FourPostSim (High Fidelity — MBD)

Compiled Modelica executables built from BobLib's standard vehicle models. Used by the `StandardSim` Python layer for single-study runs.

| Property | Value |
| --- | --- |
| **Workflow** | `simulations/mbd` Python layer + `BobLib/Experiments/Standards/` |
| **Model source** | BobLib high-fidelity Modelica equations |
| **Time domain** | Transient time-series (direct integration) |
| **Typical use** | Single ramp-steer, steady-state, or transient evaluation |
| **Reported as** | "BobLib standard study" or "MBD simulation" |

**Executables:**
- `VehicleSim`: runs `RampSteerEval`, `SteadyStateEval`, `TransientEval`
- `FourPostSim`: runs `FourPostEval` (four-post rig path following)

**Entry point targets:**
```bash
make standard-eval-ramp-steer
make standard-eval-steady-state
make standard-eval-transient
make standard-eval-four-post
make standard-eval-all  # all four studies
```

**Output:** `simulations/mbd/generated_results/*_report.pdf`, `*_report_metrics.csv`

---

### EnvelopeSim (DynPy QSS)

Python layer that generates performance envelopes (grip-acceleration and yaw moment diagrams) using reduced-order dynamics from `engines/dynpy`. Fast map generation, explicitly correlated against BobLib but not time-domain integrated.

| Property | Value |
| --- | --- |
| **Workflow** | `simulations/envelope` Python layer + `engines/dynpy` |
| **Model source** | Reduced-order vehicle dynamics (3/6/10/14 DOF options) |
| **Time domain** | Quasi-steady (no time integration; outputs steady-state or trim-based maps) |
| **Typical use** | Performance envelope maps, lap-line optimization, sensitivity studies |
| **Reported as** | "Envelope simulation" or "quasi-steady simulation" |

**Envelope types:**
- `GGV`: grip-acceleration envelope (Gg, forward acceleration × lateral acceleration space)
- `YMD`: yaw moment diagram (understeer/oversteer balance)

**Entry point targets:**
```bash
make envelope-ggv
make envelope-ymd
make envelope-all
```

**Output:** `simulations/envelope/Build/` (maps) and `simulations/envelope/results/` (reports)

---

### Reduced-Order Transient (Medium Fidelity — Transient Reduced-Order)

Uses the `dyn_py` models with full time-domain transient integration. Bridges envelope speed and MBD precision — good for repeated transient cycles (lap validation, sensitivity parameter sweeps).

| Property | Value |
| --- | --- |
| **Workflow** | `simulations/reduced` (correlates envelope and MBD) or lap-time transient path following |
| **Model source** | `engines/dynpy` reduced-order equations |
| **Time domain** | Transient time-series (integrated, not quasi-steady) |
| **Typical use** | Lap-time validation, transient sensitivities without MBD overhead |
| **Reported as** | "Reduced-order transient simulation" or "14DOF transient" (specify DOF if relevant) |

**Entry point targets:**
```bash
make lap-eval-transient       # lap path with transient integration
make reduced-kinematics-benchmark  # kinematics fidelity check
```

**Output:** `simulations/lap/results/` (lap timings, transient traces)

---

## Quick Reference: When to Use What

| Goal | Workflow | Fidelity | Speed |
| --- | --- | --- | --- |
| Understand single maneuver (ramp steer, etc.) | `StandardSim` + VehicleSim | High (MBD) | Slow |
| Performance envelope or lap line | `EnvelopeSim` | Low (QSS) | Very fast |
| Lap sensitivity studies | `EnvelopeSim` GGV + `LapTimeEval` | Low-Medium | Fast |
| Transient lap validation | `LapTimeEval` reduced transient | Medium | Medium |
| Compare reduced vs. full model | `ReducedOrderEval` | Medium (reduced) | Medium |
| Four-post rig evaluation | `StandardSim` + FourPostSim | High (MBD) | Slow |

---

## In Reports and Analysis

When publishing results, use the workflow name or fidelity level in figure captions and metric tables:

**Good:**
- "BobLib standard RampSteerEval: understeer gradient = 0.042 °/g"
- "Envelope GGV-based lap time prediction: 1:42.3"
- "14DOF transient lap simulation: peak yaw rate = 4.2 °/s"

**Ambiguous (avoid):**
- "Simulation shows…" ← Which one?
- "Full model predicts…" ← VehicleSim (MBD) or reduced transient?

**Avoid confusion by naming both the workflow and the model fidelity level, especially in comparison contexts.**

---

## Sensitivity and DOE Workflows

Sensitivity and design-of-experiments (DOE) runs sweep parameters across **any** of the above simulators:

- `StandardSens`: sweeps StandardSim studies (VehicleSim/FourPostSim)
- `EnvelopeSens`: sweeps EnvelopeSim outputs (GGV/YMD generation)
- `opt-standard`, `opt-envelope`, `opt-refined`: DOE targets using the sensitivity layer

See [doe-reverse-engineering.md](doe-reverse-engineering.md) for details.
