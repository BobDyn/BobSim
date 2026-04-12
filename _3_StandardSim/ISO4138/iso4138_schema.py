from _2_GeneralSim.output_schema import OutputSchema


ISO4138_SCHEMA = OutputSchema(
    signals=[
        "iso.handwheelAngle",
        "iso.leftSteerAngle",
        "iso.rightSteerAngle",
        "iso.accY",
        "iso.roll",
        "iso.sideslip",
        "iso.curvature",
        "iso.handwheelTorque",
    ]
)