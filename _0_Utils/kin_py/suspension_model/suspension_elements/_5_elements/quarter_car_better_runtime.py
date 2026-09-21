from _0_Utils.kin_py.suspension_model.suspension_elements._4_elements.push_pull_rod import PushPullRod
from _0_Utils.kin_py.suspension_model.suspension_elements._2_elements.wishbone import Wishbone
from _0_Utils.kin_py.suspension_model.suspension_elements._2_elements.tire import Tire
from _0_Utils.kin_py.suspension_model.suspension_elements._1_elements.link import Link
from _0_Utils.kin_py.misc_math import rotation_matrix

from scipy.optimize import fsolve # type: ignore
from typing import Sequence
import numpy as np


class QuarterCar:
    """Full corner: wishbones, tie rod, push/pull rod and tire."""
    def __init__(
            self,
            tire: Tire,
            lower_wishbone: Wishbone,
            upper_wishbone: Wishbone,
            tie_rod: Link,
            push_pull_rod: PushPullRod):
        
        self.tire = tire
        self.lower_wishbone = lower_wishbone
        self.upper_wishbone = upper_wishbone
        self.tie_rod = tie_rod
        self.push_pull_rod = push_pull_rod

        self.LCA_to_UCA = Link(inboard_node=lower_wishbone.fore_link.outboard_node, outboard_node=upper_wishbone.fore_link.outboard_node)
        self.LCA_to_tire = Link(inboard_node=lower_wishbone.fore_link.outboard_node, outboard_node=self.tire.contact_patch)

        # Upright points in the LCA-to-UCA link frame, relative to the LCA outboard pickup.
        self.tie_rod_wrt_LCA = self.LCA_to_UCA.link_centered_coords(node=self.tie_rod.outboard_node)
        self.tire_wrt_LCA = self.LCA_to_UCA.link_centered_coords(node=self.tire.contact_patch)

        self.wheel_jounce: float = 0
        self.rack_displacement: float = 0
    
    def jounce(self, jounce: float) -> None:
        """Solve the corner geometry for a contact patch travel of jounce meters from the initial state."""
        self.wheel_jounce = jounce
        self._update_geometry()
    
    def steer(self, rack_displacement: float) -> None:
        """Steer the corner by a lateral rack translation."""
        self.rack_displacement = rack_displacement
        self._update_geometry()
    
    def _update_geometry(self) -> None:
        # Set the rack before the solve so it updates only once.
        self.tie_rod.inboard_node.position[1] = self.rack_displacement
        upper_rot, lower_rot, wheel_angle = fsolve(func=self._geometry_resid_func, x0=[0, 0, 0])
        
        self.upper_wishbone.rotate(angle=upper_rot)
        self.lower_wishbone.rotate(angle=lower_rot)

        ang_x, ang_y = self.LCA_to_UCA.rotation_angles
        x_rot = rotation_matrix(unit_vec=[1, 0, 0], theta=-1 * ang_x)
        y_rot = rotation_matrix(unit_vec=[0, 1, 0], theta=ang_y)

        self.tire.contact_patch.position = np.matmul(x_rot, np.matmul(y_rot, self.tire_wrt_LCA)) + self.lower_wishbone.fore_link.outboard_node.position

        # Move the tie rod pickup with the upright. This preserves tie rod length.
        self.tie_rod.outboard_node.position = np.matmul(x_rot, np.matmul(y_rot, self.tie_rod_wrt_LCA)) + self.lower_wishbone.fore_link.outboard_node.position

        self.tire.contact_patch.rotate(origin=self.lower_wishbone.fore_link.outboard_node,
                                       persistent=True,
                                       direction=self.LCA_to_UCA.direction,
                                       angle=wheel_angle)
        self.tie_rod.outboard_node.rotate(origin=self.lower_wishbone.fore_link.outboard_node,
                                          persistent=True,
                                          direction=self.LCA_to_UCA.direction,
                                          angle=wheel_angle)

    def _geometry_resid_func(self, x: Sequence[float]) -> Sequence[float]:
        """Geometry residuals. x is [lower_wishbone_rot, upper_wishbone_rot, wheel_angle]."""
        upper_wishbone_rot = x[0]
        lower_wishbone_rot = x[1]
        wheel_angle = x[2]

        # Rotate manually. Node.rotate() updates the full link system and is about 4x slower.
        upper_rot = rotation_matrix(unit_vec=self.upper_wishbone.direction, theta=upper_wishbone_rot)
        lower_rot = rotation_matrix(unit_vec=self.lower_wishbone.direction, theta=lower_wishbone_rot)
        
        upper_node = self.upper_wishbone.fore_link.outboard_node
        upper_ref = self.upper_wishbone.fore_link.inboard_node
        lower_node = self.lower_wishbone.fore_link.outboard_node
        lower_ref = self.lower_wishbone.fore_link.inboard_node

        upper_node.position = [float(x) for x in np.matmul(upper_rot, np.array(upper_node.initial_position) - np.array(upper_ref.initial_position)) \
                               + np.array(upper_ref.initial_position)]
        lower_node.position = [float(x) for x in np.matmul(lower_rot, np.array(lower_node.initial_position) - np.array(lower_ref.initial_position)) \
                               + np.array(lower_ref.initial_position)]

        ang_x, ang_y = self.LCA_to_UCA.rotation_angles
        x_rot = rotation_matrix(unit_vec=[1, 0, 0], theta=-1 * ang_x)
        y_rot = rotation_matrix(unit_vec=[0, 1, 0], theta=ang_y)

        self.tire.contact_patch.position = np.matmul(x_rot, np.matmul(y_rot, self.tire_wrt_LCA)) + self.lower_wishbone.fore_link.outboard_node.position

        # Move the tie rod pickup with the upright. This does not preserve tie rod length.
        self.tie_rod.outboard_node.position = np.matmul(x_rot, np.matmul(y_rot, self.tie_rod_wrt_LCA)) + self.lower_wishbone.fore_link.outboard_node.position

        # Rotate manually for runtime.

        wheel_rot = rotation_matrix(unit_vec=self.LCA_to_UCA.direction, theta=wheel_angle)

        tire_node = self.tire.contact_patch
        tie_node = self.tie_rod.outboard_node
        kingpin_ref = self.LCA_to_UCA.inboard_node

        tire_node.position = [float(x) for x in np.matmul(wheel_rot, np.array(tire_node.position) - np.array(kingpin_ref.position)) \
                              + np.array(kingpin_ref.position)]
        tie_node.position = [float(x) for x in np.matmul(wheel_rot, np.array(tie_node.position) - np.array(kingpin_ref.position)) \
                             + np.array(kingpin_ref.position)]

        self.tire.steered_angle = wheel_angle

        # Residuals: kingpin length, tie rod length, contact patch height.
        kingpin_residual = self.LCA_to_UCA.length - self.LCA_to_UCA.initial_length
        tie_rod_residual = self.tie_rod.length - self.tie_rod.initial_length
        jounce_residual = self.tire.contact_patch[2] - self.wheel_jounce

        return [kingpin_residual, tie_rod_residual, jounce_residual]