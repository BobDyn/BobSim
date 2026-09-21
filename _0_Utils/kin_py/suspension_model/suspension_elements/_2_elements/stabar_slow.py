from _0_Utils.kin_py.suspension_model.suspension_elements._1_elements.link import Link
from _0_Utils.kin_py.suspension_model.suspension_elements._1_elements.node import Node
from _0_Utils.kin_py.misc_math import nearest_root

from typing import Tuple
import numpy as np


class Stabar:
    """Stabar (anti-roll bar).

    Arm ends are the lever ends farthest from the torsion bar axis.
    Left is positive y and right is negative y. Droplink ends mount to the rest of the car.
    """
    def __init__(self, 
                 left_arm_end: Node, 
                 right_arm_end: Node, 
                 left_droplink_end: Node, 
                 right_droplink_end: Node, 
                 bar_left_end: Node, 
                 bar_right_end: Node, 
                 torsional_stiffness: float) -> None:

        self.bar: Link = Link(inboard_node=bar_left_end, outboard_node=bar_right_end)
        self.torsional_stiffness: float = torsional_stiffness

        self.left_arm: Link = Link(inboard_node=bar_left_end, outboard_node=left_arm_end)
        self.right_arm: Link = Link(inboard_node=bar_right_end, outboard_node=right_arm_end)

        self.left_droplink: Link = Link(inboard_node=left_droplink_end, outboard_node=left_arm_end)
        self.right_droplink: Link = Link(inboard_node=right_droplink_end, outboard_node=right_arm_end)

        self.left_rotation: float = 0
        self.right_rotation: float = 0

    def update(self) -> None:
        """Solve the arm rotations that keep the droplink lengths constant."""
        self.left_rotation = nearest_root(func=self._droplink_eqn, x0=0, bounds=(-np.pi/2, np.pi/2), tol=1e-10, args=[self.left_droplink])
        self.right_rotation = nearest_root(func=self._droplink_eqn, x0=0, bounds=(-np.pi/2, np.pi/2), tol=1e-10, args=[self.right_droplink])

    def _droplink_eqn(self, x: float, args: Tuple[Link]) -> float:
        """Droplink length residual. x is the rotation in radians and args is [droplink]."""
        rotation=x
        droplink = args[0]

        droplink.outboard_node.reset()

        droplink.outboard_node.rotate(origin=self.bar.inboard_node, direction=self.bar.direction, angle=rotation)

        return droplink.length - droplink.initial_length

    @property
    def rotation(self) -> float:
        """Angular deformation of the stabar in radians."""
        return self.left_rotation - self.right_rotation
    
    @property
    def torque(self) -> float:
        return abs(self.torsional_stiffness * self.rotation)