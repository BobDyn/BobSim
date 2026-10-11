# Lap-time reference tracks

`endurance_michigan_2019.csv` contains the 2019 Formula SAE Michigan endurance
boundaries from Longhorn Racing Electric's
[`jomama_lapsim`](https://github.com/LonghornRacingElectric/jomama_lapsim/blob/main/tracks/Endurance_Michigan_2019.csv).
It is the default track in `lap_time_eval_config.yml`.

The source `out_x,out_y,in_x,in_y` coordinates are in feet. This copy multiplies
each value by 0.3048 and uses BobSim's left/right boundary column names in metres.
The duplicated closing row is removed because BobSim closes tracks periodically.

`endurance_reference.csv` is a smaller synthetic course used for validation
across all DOF levels. `generate_endurance_reference.py` defines and regenerates
its geometry. The validation config also includes the Michigan course as a
reference.
