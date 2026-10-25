import numpy as np
import pytest

from app.ymd_view import speed_slices
from simulations.envelope.ymd.ymd_generation import YMDResult, config_to_ymd_config, save_ymd_csv


def test_ymd_workflow_only_accepts_14dof():
    assert config_to_ymd_config({}).model_dof == 14
    for dof in (3, 6, 10):
        with pytest.raises(ValueError, match="only 14DOF"):
            config_to_ymd_config({"generation": {"model_dof": dof}})


def test_speed_export_retains_slices_and_breaks_invalid_grid_lines(tmp_path):
    def result(speed):
        return YMDResult(speed, np.array([0., .1]), np.array([0., .1]),
                         np.array([[0., 1.], [2., 3.]]) * speed,
                         np.array([[0., 10.], [20., 30.]]) * speed,
                         np.array([[True, True], [False, True]]))
    first, second = result(10), result(20)
    path = tmp_path / "sweep.csv"
    save_ymd_csv(first, path, speed_results=[first, second])
    view = speed_slices(path)
    assert [item["speed"] for item in view["slices"]] == [10, 20]
    assert np.genfromtxt(path, delimiter=",", names=True).size == 8
    assert view["y_extent"] == [0, 600]
    for item in view["slices"]:
        assert len(item["x"]) == 12 + 161  # carpet families plus sampled outer limits
        assert len(item["series"]) == 4
        assert sum(x is not None for x in item["x"][:12]) == 6
        assert all(len(series["values"]) == len(item["x"]) for series in item["series"])
        assert all(item["speed"] * 20 not in series["values"] for series in item["series"][:2])
