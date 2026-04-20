from _2_GeneralSim.output_schema import OutputSchema


ISO7401_SCHEMA = OutputSchema(
    signals=[
        "iso.handwheelAngle",
        "iso.velX",
        "iso.velY",
        "iso.yawVel",
        "iso.sideslip",
        "iso.accX",
        "iso.accY",
        "iso.roll",
        "iso.handwheelTorque",
    ],
    mode="raw",
)