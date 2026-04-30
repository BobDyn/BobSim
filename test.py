from _2_GeneralSim.fmu_runner import FMURunner

runner = FMURunner("VehicleFMI.fmu")

runner.initialize()

runner.set_steer_profile(
    amp_deg=6,
    freq_hz=0.5,
    start_time=1.0,
    duration=2.0
)

times, states = runner.simulate(duration=4)

runner.save_csv(times, states, "sine_test.csv")

runner.terminate()