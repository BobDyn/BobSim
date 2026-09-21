from _0_Utils.kin_py.suspension_model.suspension_elements._1_elements.link import Link
from _0_Utils.kin_py.suspension_model.suspension_elements._1_elements.node import Node

import warnings


class Spring(Link):
    """Coil spring. rate is force per unit compression."""
    def __init__(self, inboard_node: Node, outboard_node: Node, free_length: float, rate: float) -> None:
        super().__init__(inboard_node=inboard_node, outboard_node=outboard_node, compliance=rate)

        self.compliance: float
        self.free_length = free_length

    @property
    def compression(self) -> float:
        """Spring compression. Negative means tension."""
        comp = self.free_length - self.length

        if comp < 0:
            warnings.warn("Requested coil spring is in tension")

        return comp

    @property
    def force(self) -> float:
        return self.compliance * self.compression