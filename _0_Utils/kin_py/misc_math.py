from typing import Sequence, Tuple, Union, Callable
import numpy as np


def unit_vec(p1: Union[np.ndarray, Sequence[float]], p2: Union[np.ndarray, Sequence[float]]) -> Sequence[float]:
    """Unit vector from p1 to p2."""
    p1 = np.array(p1)
    p2 = np.array(p2)
    vector_AB = p2 - p1
    vector_AB_mag = np.linalg.norm(p2 - p1)
    
    return [float(x) for x in vector_AB / vector_AB_mag]

def rotation_matrix(unit_vec: Union[np.ndarray, Sequence[float], Tuple[float, float, float]], theta: float) -> Sequence[Sequence[float]]:
    """Rotation matrix for theta radians about unit_vec."""
    ux = unit_vec[0]
    uy = unit_vec[1]
    uz = unit_vec[2]
    cos_t = np.cos(theta)
    sin_t = np.sin(theta)

    matrix = [
        [ux**2 * (1 - cos_t) + cos_t, 
         ux * uy * (1 - cos_t) - uz * sin_t, 
         ux * uz * (1 - cos_t) + uy * sin_t], 
        
        [ux * uy * (1 - cos_t) + uz * sin_t,
         uy**2 * (1 - cos_t) + cos_t,
         uy * uz * (1 - cos_t) - ux * sin_t], 
        
        [ux * uz * (1 - cos_t) - uy * sin_t,
         uy * uz * (1 - cos_t) + ux * sin_t,
         uz**2 * (1 - cos_t) + cos_t]
        ]
    
    return matrix

def nearest_root(func: Callable, x0: float, bounds: Tuple[float, float], tol: float, args: Sequence = []):
    """Find the root nearest x0. func has the form func(x, args)."""
    soln = x0

    residual: float = func(soln, args)

    step_range = bounds[1] - bounds[0]
    step = step_range / 10

    positive_check: float = abs(func(x0+step_range/1000, args))
    negative_check: float = abs(func(x0-step_range/1000, args))

    if positive_check > negative_check:
        step *= -1

    previous_residual: float = residual
    while np.sign(residual) == np.sign(previous_residual):
        previous_residual = residual

        soln += step
        residual = func(soln, args)

    x_low = soln - step
    x_high = soln

    while abs(residual) > tol:
        x_mid = (x_low + x_high) / 2

        resid_mid = func(x_mid, args)
        resid_high = func(x_high, args)

        if np.sign(resid_mid) == np.sign(resid_high):
            x_high = x_mid
        else:
            x_low = x_mid

        residual = func(x_mid, args)
    
    return x_mid

def directional_root(func: Callable, x0: float, bounds: Tuple[float, float], tol: float, args: Sequence = []):
    """Find the first root in one direction, set by the sign of bounds.

    bounds must be all negative or all positive. func has the form func(x, args).
    """
    # Intended for roots near zero.

    soln = min([abs(x) for x in bounds])

    step_size = abs(bounds[1] - bounds[0]) / 10 * np.sign(np.average(bounds))

    residual: float = func(soln, args)

    while abs(residual) > tol:
        previous_residual: float = residual
            
        soln += step_size
        residual = func(soln, args)

        if np.sign(residual) == np.sign(previous_residual):
            continue
        else:
            step_size /= -2
    
    return soln