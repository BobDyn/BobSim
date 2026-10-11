# Fixed-period stepping benchmark

This workflow measures vehicle-model stepping cost at a chosen communication
period. It reports setup time, successful simulated time, attempted step time,
latency percentiles and completion status. It does not implement a feedback
controller or prove that a model meets real-time deadlines.

```bash
make standard-realtime-bench ARGS='--skip-fmu --dof 3 --stop-s 2'
make standard-build-fmu
make standard-realtime-bench
```

DynPy receives prescribed steering and rear-wheel torque inputs. It uses RK45
for 3 and 6 DOF and Radau for 10 and 14 DOF. Each interval starts a new integrator.
The final interval ends at the requested stop time, even when it is shorter
than the communication period.

VehicleSim exports FMI 2.0 model-exchange and co-simulation interfaces. This
benchmark uses co-simulation with CVODE. The current model uses its built-in
StandardVCU manoeuvre. It has no external command inputs. Its scenario differs
from the DynPy cases, so the timing comparison is not a physics correlation.

The FMU builder uses GCC and omits build-host CPU flags. The binary still needs
a compatible operating system and architecture. It removes the previous FMU
before rebuilding so a failed build cannot reuse an old archive. A CMake
toolchain hook disables optimization only for the very large generated
initialization source, which otherwise exceeded compiler memory limits.
Stepping sources retain Release optimization. Setup time includes the
unoptimized initializer and is reported separately.

`--vehicle` changes only the DynPy vehicle. Before exporting another vehicle,
regenerate the BobLib records deliberately. See
[vehicle synchronization](../../../docs/architecture.md#vehicle-and-configuration).
The output records the DynPy vehicle file hash and the FMU archive hash. These
identify inputs but do not prove that the two models contain the same vehicle.

Results go to `simulations/mbd/generated_results/realtime_bench.json`. The runner
writes after each case and exits nonzero if any case fails. Failed step attempts
count toward wall time but do not count as successful simulated time. FMU
instances and temporary extraction directories are released after a run.
A case that fails during setup retains an error without timing metrics.

The real-time factor divides successful simulated time by attempted stepping
wall time. It excludes vehicle loading, setup, output, state readback and
external controller work. A factor above one does not guarantee every step
meets its deadline. Compare p99 and maximum latency with the step period too.

## Existing experimental limits

With BobSim `6329270`, BobLib `e03da04` and OpenModelica 1.27.1 on Linux
arm64, the export built and initialized, but the 20 ms communication-period
smoke run failed with FMI fatal status at the step after 0.68 s. The benchmark
saved the incomplete run and exited nonzero. A 2 ms run also failed, at the
step after 0.698 s. Reducing the communication interval did not resolve it.
The cause was not established; do not interpret partial-run timing as
validation of reliable real-time use.


The original `tanush/vehicle-fmu` experiment at `f94e1e8` used the older BobLib
and DynPy versions. Its VehicleSim FMU failed at 0.38 s with 20 ms steps and
reached 2 s with 2 ms steps. The cause was not established. Those observations
are historical and do not validate the current model or toolchain.
External control inputs require separate BobLib work. No such model change is
part of this export and benchmark workflow.
