from _0_Utils.kin_py.suspension_model.suspension_elements._1_elements.link import Link
from _0_Utils.kin_py.suspension_model.suspension_elements._1_elements.node import Node

from typing import Sequence, Tuple
import numpy as np


class Damper(Link):
    """Damper (shock).

    damping_curve is a lookup table of (velocity, force) pairs.
    """
    def __init__(self, inboard_node: Node, outboard_node: Node, damping_curve: Sequence[Tuple[float, float]]) -> None:
        super().__init__(inboard_node=inboard_node, outboard_node=outboard_node)
        
        self.damping_curve = list(zip(*damping_curve))
        self.velocity_reference: Sequence[float] = self.damping_curve[0]
        self.force_reference: Sequence[float] = self.damping_curve[1]
        
        self.velocity: float = 0
    
    @property
    def force(self) -> float:
        return np.interp(self.velocity, self.velocity_reference, self.force_reference).__float__()