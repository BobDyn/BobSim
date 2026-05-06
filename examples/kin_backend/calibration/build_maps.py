import numpy as np

OUT = {}

# ----------------------------
# FRONT
# ----------------------------
front_data = np.load("calibration_data/front_heave.npy", allow_pickle=True)

z = np.array([d["z"] for d in front_data])
L_left  = np.array([d["leftShockLength"] for d in front_data])
L_right = np.array([d["rightShockLength"] for d in front_data])

# sort by L for inversion
idx = np.argsort(L_left)
OUT["FL"] = {
    "L": L_left[idx],
    "z": z[idx]
}

idx = np.argsort(L_right)
OUT["FR"] = {
    "L": L_right[idx],
    "z": z[idx]
}


# ----------------------------
# REAR
# ----------------------------
rear_data = np.load("calibration_data/rear_heave.npy", allow_pickle=True)

z = np.array([d["z"] for d in rear_data])
L_left  = np.array([d["leftShockLength"] for d in rear_data])
L_right = np.array([d["rightShockLength"] for d in rear_data])

idx = np.argsort(L_left)
OUT["RL"] = {
    "L": L_left[idx],
    "z": z[idx]
}

idx = np.argsort(L_right)
OUT["RR"] = {
    "L": L_right[idx],
    "z": z[idx]
}


# ----------------------------
# SAVE
# ----------------------------
np.savez("calibration/maps.npz", **OUT)

print("✅ maps.npz created")