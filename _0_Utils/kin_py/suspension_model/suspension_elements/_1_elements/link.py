from _0_Utils.kin_py.suspension_model.suspension_elements._1_elements.node import Node
from _0_Utils.kin_py.misc_math import unit_vec, rotation_matrix
from typing import Sequence, Union
import numpy as np
import warnings


class Link:
    """Link between two nodes, similar to a beam.

    The optional kwarg ``compliance`` sets the linear compliance.
    """
    def __init__(self, inboard_node: Node, outboard_node: Node, **kwargs) -> None:
        
        self.inboard_node: Node = inboard_node
        self.outboard_node: Node = outboard_node
        self.initial_length: float = np.linalg.norm((self.outboard_node - self.inboard_node).position).__float__()

        self.compliance: Union[None, float, int] = None
        self.compliance_unit: Union[None, str] = None

        if "compliance" in kwargs:
            self.compliance = kwargs.pop("compliance")

    def yz_intersection(self, link: "Link") -> Node:
        """Intersection of self and link in the y-z plane. x is the mean of the two links."""
        l_1i = self.inboard_node
        l_1o = self.outboard_node
        m_1 = (l_1o - l_1i)[2] / (l_1o - l_1i)[1]
        y_1, z_1 = l_1o[1], l_1o[2]

        l_2i = link.inboard_node
        l_2o = link.outboard_node
        m_2 = (l_2o - l_2i)[2] / (l_2o - l_2i)[1]
        y_2, z_2 = l_2o[1], l_2o[2]

        a = np.array([
            [-1 * m_1, 1],
            [-1 * m_2, 1]
        ])

        b = np.array([
            [-1 * m_1 * y_1 + z_1],
            [-1 * m_2 * y_2 + z_2]
        ])

        try:
            y, z = np.linalg.solve(a=a, b=b).flatten()
        except np.linalg.LinAlgError:
            warnings.warn("\nSingular Matrix Encountered | yz intersection assumed at infinity. This is not a critical error, but check results carefully.")
            y, z = np.inf, np.average([z_2, z_1])

        # Average x of the two links, for the kinematic roll center.
        x = np.average([l_1o[0], l_2o[0]]).__float__()

        return Node(position=[x, y, z])

    def xz_intersection(self, link: "Link") -> Node:
        """Intersection of self and link in the x-z plane. y is the mean of the two links."""
        l_1i = self.inboard_node
        l_1o = self.outboard_node
        m_1 = (l_1o - l_1i)[2] / (l_1o - l_1i)[0]
        x_1, z_1 = l_1o[0], l_1o[2]

        l_2i = link.inboard_node
        l_2o = link.outboard_node
        m_2 = (l_2o - l_2i)[2] / (l_2o - l_2i)[0]
        x_2, z_2 = l_2o[0], l_2o[2]

        a = np.array([
            [-1 * m_1, 1],
            [-1 * m_2, 1]
        ])

        b = np.array([
            [-1 * m_1 * x_1 + z_1],
            [-1 * m_2 * x_2 + z_2]
        ])
        
        # Average y of the two links, for the kinematic pitch center.
        y = np.average([l_1o[1], l_2o[1]])

        try:
            x, z = np.linalg.solve(a=a, b=b).flatten()
        except:
            warnings.warn("\nSingular Matrix Encountered | xz intersection assumed at infinity. This is not a critical error, but check results carefully.")
            x, z = np.inf, np.average([z_2, z_1])

        coords = [float(x) for x in [x, y, z]]

        return Node(position=coords)

    def link_centered_coords(self, node: Node) -> np.ndarray:
        """Node coordinates in a frame with the Link as the z-axis."""
        ang_x, ang_y = self.rotation_angles
        node_translated = node - self.inboard_node

        x_rot = rotation_matrix(unit_vec=[1, 0, 0], theta=ang_x)
        y_rot = rotation_matrix(unit_vec=[0, 1, 0], theta=-1 * ang_y)
        
        node_coords_rotated: np.ndarray = np.matmul(y_rot, np.matmul(x_rot, node_translated.position))
        return node_coords_rotated

    @property
    def component_angles(self) -> Sequence[float]:
        """Smallest angles [ang_x, ang_y] in radians between the ground plane and the Link projections.

        For a kingpin Link these are KPI and caster.
        """
        origin_transform = self.outboard_node - self.inboard_node
        ang_x = np.arctan(origin_transform[2] / origin_transform[1]).__float__()
        ang_y = np.arctan(origin_transform[2] / origin_transform[0]).__float__()

        return [ang_x, ang_y]
    
    @property
    def rotation_angles(self) -> Sequence[float]:
        """Rotations about x and y in radians that align the Link with z."""
        origin_transform = self.outboard_node - self.inboard_node
        ang_x = np.arctan(origin_transform[1] / origin_transform[2]).__float__()
        ang_y = np.sign(origin_transform[2]) * np.arcsin(origin_transform[0] / self.length).__float__()

        return [ang_x, ang_y]
    
    @property
    def direction(self) -> Sequence[float]:
        """Unit vector from the inboard node to the outboard node."""
        return unit_vec(p1=self.inboard_node.position, p2=self.outboard_node.position)

    @property
    def center(self) -> Sequence[float]:
        new_node = (self.inboard_node + self.outboard_node) / 2

        return new_node.position
    
    @property
    def radius(self) -> float:
        """Fixed radius for a 5/8 in (0.015875 m) diameter link."""
        return 0.015875 / 2

    @property
    def length(self) -> float:
        return np.linalg.norm((self.outboard_node - self.inboard_node).position).__float__()