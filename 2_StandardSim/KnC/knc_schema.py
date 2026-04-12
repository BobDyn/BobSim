# StandardSim/KnC/knc_schema.py

KNC_SCHEMA = [
    "time",

    # inputs
    "knc.heave",
    "knc.roll",
    "knc.fx",
    "knc.fy",

    # geometry (left/right)
    "knc.left.gamma",
    "knc.left.toe",
    "knc.left.caster",
    "knc.left.kpi",

    "knc.right.gamma",
    "knc.right.toe",
    "knc.right.caster",
    "knc.right.kpi",

    # forces
    "knc.jackingForce",
]