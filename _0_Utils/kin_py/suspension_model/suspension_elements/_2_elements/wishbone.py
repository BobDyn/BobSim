from _0_Utils.kin_py.suspension_model.suspension_elements._1_elements.link import Link
from _0_Utils.kin_py.misc_math import unit_vec

from typing import Sequence
import numpy as np


class Wishbone:
    def __init__(self, fore_link: Link, aft_link: Link) -> None:
        self.fore_link: Link = fore_link
        self.aft_link: Link = aft_link

        self.direction: Sequence[float] = unit_vec(p1=self.aft_link.inboard_node.position, p2=self.fore_link.inboard_node.position)
        self.angle: float = 0.0

    def rotate(self, angle: float) -> None:
        """Rotate the wishbone by angle radians about the axis through its inboard nodes."""
        self.fore_link.outboard_node.reset()
        self.aft_link.outboard_node.reset()

        self.angle = angle
        self.fore_link.outboard_node.rotate(origin=self.fore_link.inboard_node, direction=self.direction, angle=angle)

    @property
    def plane(self) -> Sequence[float]:
        """Wishbone plane [a, b, c, x_0, y_0, z_0] for a(x - x_0) + b(y - y_0) + c(z - z_0) = 0."""
        PQ = (self.fore_link.outboard_node - self.fore_link.inboard_node).position
        PR = (self.aft_link.outboard_node - self.aft_link.inboard_node).position

        a, b, c = np.cross(PQ, PR)
        x_0, y_0, z_0 = self.fore_link.outboard_node.position

        return [a, b, c, x_0, y_0, z_0]

    @property
    def direction_vec(self) -> Sequence[float]:
        """Unit vector from the inboard aft node to the inboard fore node."""
        return unit_vec(p1=self.aft_link.inboard_node.position, p2=self.fore_link.inboard_node.position)