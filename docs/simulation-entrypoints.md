# Simulation Entrypoints

BobSim offers multiple simulation workflows, each with different fidelity levels and use cases. **When generating analysis results, always specify which workflow was used so readers understand whether results came from a high-fidelity MBD study or a fast quasi-steady envelope.**

## Fidelity Levels (highest to lowest)

### VehicleSim / FourPostSim (High Fidelity — MBD)

Compiled Modelica executables built from BobLib's standard vehicle models. Used by the `StandardSim` Python layer for single-study runs.

| Property | Value |
| --- | --- |
| **Workflow** | `_3_StandardSim` Python layer + `BobLib/Experiments/Standards/` |
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

**Output:** `_3_StandardSim/generated_results/*_report.pdf`, `*_report_metrics.csv`

---

### EnvelopeSim (Low Fidelity — Quasi-Steady)

Python layer that generates performance envelopes (grip-acceleration and yaw moment diagrams) using reduced-order dynamics from `_0_Utils/dyn_py`. Fast map generation, explicitly correlated against BobLib but not time-domain integrated.

| Property | Value |
| --- | --- |
| **Workflow** | `_2_EnvelopeSim` Python layer + `_0_Utils/dyn_py` |
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

**Output:** `_2_EnvelopeSim/generated_results/` (map CSVs and visualizations)

---

### Reduced-Order Transient (Medium Fidelity — Transient Reduced-Order)

Uses the `dyn_py` models with full time-domain transient integration. Bridges envelope speed and MBD precision — good for repeated transient cycles (lap validation, sensitivity parameter sweeps).

| Property | Value |
| --- | --- |
| **Workflow** | `_3_StandardSim/ReducedOrderEval` (correlates envelope and MBD) or lap-time transient path following |
| **Model source** | `_0_Utils/dyn_py` reduced-order equations |
| **Time domain** | Transient time-series (integrated, not quasi-steady) |
| **Typical use** | Lap-time validation, transient sensitivities without MBD overhead |
| **Reported as** | "Reduced-order transient simulation" or "14DOF transient" (specify DOF if relevant) |

**Entry point targets:**
```bash
make lap-eval-transient       # lap path with transient integration
make reduced-kinematics-benchmark  # kinematics fidelity check
```

**Output:** `_3_StandardSim/generated_results/lap_time_eval/` (lap timings, transient traces)

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
