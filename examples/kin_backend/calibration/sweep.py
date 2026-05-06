import numpy as np
from pathlib import Path
from core.fmu import FMU


Z = np.linspace(-2, 2, 100) * 0.0254
OUT = Path("calibration_data")
OUT.mkdir(exist_ok=True)


def run_front_heave():
    data = []
    front = FMU("./fmus/FrKnCFMI.fmu", "front")

    for z in Z:
        front.set("heaveInput", z)
        front.set("rollInput", 0.0)
        front.set("steerInput", 0.0)

        front.step(0.0)

        data.append({
            "z": z,
            "leftShockLength": front.get("leftShockLength"),
            "rightShockLength": front.get("rightShockLength"),
        })

    front.terminate()
    np.save(OUT / "front_heave.npy", data)


def run_rear_heave():
    data = []
    rear = FMU("./fmus/RrKnCFMI.fmu", "rear")

    for z in Z:
        rear.set("heaveInput", z)
        rear.set("rollInput", 0.0)

        rear.step(0.0)

        data.append({
            "z": z,
            "leftShockLength": rear.get("leftShockLength"),
            "rightShockLength": rear.get("rightShockLength"),
        })

    rear.terminate()
    np.save(OUT / "rear_heave.npy", data)


run_front_heave()
run_rear_heave()