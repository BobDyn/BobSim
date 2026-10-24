import numpy as np

from engines.dynpy.transient import _state_jacobian


def test_zero_sensitivity_coordinates_do_not_grow_jacobian_probes():
    for time in range(500):
        state = np.array([15.0 * time, 0.25, 80.0 * time])

        def rhs(t, trial):
            assert np.isfinite(trial).all()
            assert np.all(np.abs(trial - state) < 1e-4 * np.maximum(1, np.abs(state)))
            return np.array([trial[1], -3 * trial[1] + np.sin(t), trial[1] ** 2])

        actual = _state_jacobian(rhs, time, state)
        np.testing.assert_allclose(actual, [[0, 1, 0], [0, -3, 0], [0, 0.5, 0]], atol=1e-10)
