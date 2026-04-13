from _2_GeneralSim.output_schema import OutputSchema


KNC_SCHEMA = OutputSchema(
    signals=[
        "knc.heave",
        "knc.roll",
        "knc.fx",
        "knc.fy",

        "knc.leftSpringLength",
        "knc.leftGamma",
        "knc.leftToe",
        "knc.leftCaster",
        "knc.leftKpi",
        "knc.leftMechTrail",
        "knc.leftMechScrub",

        "knc.rightSpringLength",
        "knc.rightGamma",
        "knc.rightToe",
        "knc.rightCaster",
        "knc.rightKpi",
        "knc.rightMechTrail",
        "knc.rightMechScrub",

        "knc.jackingForce",
        "knc.stabarAngle",
    ],
    mode="raw",
)