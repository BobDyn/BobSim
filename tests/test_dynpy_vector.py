"""The reduced models' cross product must match NumPy exactly."""

import numpy as np
import pytest

from engines.dynpy.vector import cross


@pytest.mark.parametrize(
    ("a_shape", "b_shape"),
    [((3,), (3,)), ((4, 3), (4, 3)), ((3,), (4, 3)), ((4, 3), (3,)), ((2, 4, 3), (4, 3))],
)
def test_cross_is_bitwise_identical_to_numpy(a_shape, b_shape):
    rng = np.random.default_rng(7)
    a = rng.normal(scale=1e3, size=a_shape)
    b = rng.normal(scale=1e-3, size=b_shape)
    expected = np.cross(a, b)
    actual = cross(a, b)
    assert actual.shape == expected.shape
    assert actual.dtype == np.float64
    assert np.array_equal(actual, expected)


def test_cross_accepts_lists_and_special_values():
    assert np.array_equal(cross([1, 0, 0], [0, 1, 0]), [0., 0., 1.])
    special = np.array([np.inf, 1., 0.])
    np.testing.assert_array_equal(cross(special, [0., 0., 1.]), np.cross(special, [0., 0., 1.]))


def test_cross_rejects_non_3_vectors():
    with pytest.raises(IndexError):
        cross([1., 2.], [3., 4.])
