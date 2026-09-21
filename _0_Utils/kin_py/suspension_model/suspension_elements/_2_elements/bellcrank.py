from _0_Utils.kin_py.suspension_model.suspension_elements._1_elements.node import Node

from typing import Sequence, Tuple


class Bellcrank:
    """Bellcrank that rotates its pickup nodes about a pivot axis.

    The first node connects to the push/pull rod. The last node connects to the inboard rod or shock.
    """
    def __init__(self, *nodes: Node, pivot: Node, pivot_direction: Tuple[float, float, float]) -> None:
        self.nodes: Sequence[Node] = nodes
        self.pivot = pivot
        self.pivot_direction = pivot_direction

        self.angle: float = 0

    def rotate(self, angle: float) -> None:
        """Rotate the bellcrank by angle radians from the initial position."""
        for node in self.nodes:
            node.reset()
            node.rotate(origin=self.pivot, direction=self.pivot_direction, angle=angle)
        
        self.angle = angle
