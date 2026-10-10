# Lap-time reference tracks

`endurance_michigan_2019.csv` is the realistic system-level reference. It is a
meter-converted copy of Longhorn Racing Electric's paired 2019 Formula SAE
Michigan endurance boundaries from
[`jomama_lapsim`](https://github.com/LonghornRacingElectric/jomama_lapsim/blob/main/tracks/Endurance_Michigan_2019.csv).
The original `out_x,out_y,in_x,in_y` values are feet; every value here is
multiplied by exactly 0.3048 and renamed to BobSim's left/right meter schema.
The duplicated closing row was removed because BobSim closes tracks
periodically.

`endurance_reference.csv` is the smaller synthetic stress/regression course.
Its adjacent generator defines the geometry exactly. Validation uses it for the
expensive all-DOF acceptance matrix so that routine checks stay bounded, while
the Michigan course remains visible beside it and is the normal LapTimeEval
default.
