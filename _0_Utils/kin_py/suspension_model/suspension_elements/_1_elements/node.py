from _0_Utils.kin_py.misc_math import rotation_matrix
from _0_Utils.kin_py.updateable import Updateable

from typing import Sequence, Tuple, Union, MutableSequence, cast
from copy import deepcopy
import numpy as np


class Node:
    """Point with a position, child nodes and listeners."""
    def __init__(self, position: Union[np.ndarray, Sequence[float]]) -> None:
        self.listeners: MutableSequence[Updateable] = []
        self.child_nodes: MutableSequence[Node] = []

        self.position: MutableSequence[float] = deepcopy(list(position))
        self.initial_position: MutableSequence[float] = deepcopy(list(position))

        # Last translation and rotation, read by listeners.
        self.translation: Union[None, Sequence[float]] = None

        self.rotation_angle: Union[None, float] = None
        self.rotation_origin: Union[None, Node] = None
        self.rotation_direction: Union[None, Tuple[float, float, float]] = None

    def reset(self) -> None:
        """Reset Node and its children to the initial position.

        Reset only before a translation or rotation.
        """
        self.position = self.initial_position
        
        self.translation = None
        
        self.rotation_angle = None
        self.rotation_origin = None
        self.rotation_direction = None
        
        for node in self.child_nodes:
            node.reset()
        
    def translate(self, translation: Union[np.ndarray, Sequence[float]]) -> None:
        """Translate Node and its children from the initial position."""
        self.reset()

        self.position = [x + y for x, y in zip(self.position, translation)]
        
        for node in self.child_nodes:
            node.position = [x + y for x, y in zip(node.position, translation)]
            node.translation = list(translation)
        
        self.translation = list(translation)
        
        self.__update_listeners__()
    
    def rotate(self, 
               origin: "Node",
               persistent: bool = False, 
               direction: Union[None, Tuple[float, float, float], Sequence[float]] = None, 
               angle: Union[None, float] = None,
               ang_x: Union[None, float] = None,
               ang_y: Union[None, float] = None,
               ang_z: Union[None, float] = None) -> None:
        """Rotate Node in one of two modes:

        1. About the axis `direction` through `origin`, by `angle`.
        2. By `ang_x`, `ang_y` and `ang_z` about global axes, with position as a vector from `origin`.

        Angles are in radians. If `persistent` is False, rotate from the initial position.
        """
        if not persistent:
            self.reset()

        if not ((direction == None) and (angle == None)):
            if ang_x or ang_y or ang_z:
                raise Exception("You cannot provide ang_x, and_y, or ang_z to Node.rotate() if direction and angle are also provided.")
            
            rot = rotation_matrix(unit_vec=cast(Tuple[float, float, float], direction), theta=cast(float, angle))
            
            self_rotated = list(np.matmul(rot, (self - origin).position))
            self.position = [x + y for x, y in zip(self_rotated, origin.position)]
            
            for node in self.child_nodes:
                node_rotated = np.matmul(rot, (node - origin).position)
                node.position = [x + y for x, y in zip(node_rotated, origin.position)]

                node.rotation_angle = angle
                node.rotation_origin = origin
                node.rotation_direction = cast(Tuple[float, float, float], direction)
                node.__update_listeners__()
            
            self.rotation_angle = angle
            self.rotation_origin = origin
            self.rotation_direction = cast(Tuple[float, float, float], direction)
        
        elif (not (ang_x == None)) and (not (ang_y == None)) and (not (ang_z == None)):
            x_rot = rotation_matrix(unit_vec=[1, 0, 0], theta=ang_x)
            y_rot = rotation_matrix(unit_vec=[0, 1, 0], theta=ang_y)
            z_rot = rotation_matrix(unit_vec=[0, 0, 1], theta=ang_z)
            
            self_rotated = np.matmul(z_rot, np.matmul(y_rot, np.matmul(x_rot, (self - origin).position)))
            self.position =  [x + y for x, y in zip(self_rotated, origin.position)]

            for node in self.child_nodes:
                node_rotated = np.matmul(z_rot, np.matmul(y_rot, np.matmul(x_rot, (node - origin).position)))
                node.position = [x + y for x, y in zip(node_rotated, origin.position)]

                if node.listeners:
                    raise NotImplementedError("Listeners not supported for x, y, and z rotations. Please switch rotation to unit vector + angle.")
        
        else:
            raise Exception("You must provide either: (direction and angle) OR (ang_x and ang_y and ang_z) to Node.rotate().")

        self.__update_listeners__()
    
    def add_child(self, node: "Node") -> None:
        """Add a child node that moves with this Node."""
        self.child_nodes.append(node)
    
    def add_listener(self, listener: Updateable) -> None:
        """Add a listener. Each Node update calls listener.update()."""
        self.listeners.append(listener)
    
    def __add__(self, node: "Node") -> "Node":
        node_sum = [self.position[0] + node.position[0],
                    self.position[1] + node.position[1],
                    self.position[2] + node.position[2]]

        return Node(position=node_sum)

    def __sub__(self, node: "Node") -> "Node":
        node_sub = [self.position[0] - node.position[0],
                    self.position[1] - node.position[1],
                    self.position[2] - node.position[2]]

        return Node(position=node_sub)
    
    def __mul__(self, num: float):
        node_mul = [x * num for x in self.position]

        return Node(position=node_mul)

    def __truediv__(self, num: float):
        node_div = [x / num for x in self.position]

        return Node(position=node_div)
    
    def __getitem__(self, index: int) -> float:
        value = self.position[index]

        return value
    
    def __setitem__(self, index: int, value: float) -> None:
        self.position[index] = value
        self.__update_listeners__()
    
    def __update_listeners__(self) -> None:
        for listener in self.listeners:
            listener.update()
    
    def __str__(self) -> str:
        str_rep = f"Current position: {self.position} | Initial position: {self.initial_position}"

        return str_rep
    
    @property
    def mirrored_xy(self):
        x_pos = self.initial_position[0]
        y_pos = self.initial_position[1]
        z_pos = self.initial_position[2] * -1

        return Node(position=[x_pos, y_pos, z_pos])
    
    @property
    def mirrored_xz(self):
        x_pos = self.initial_position[0]
        y_pos = self.initial_position[1] * -1
        z_pos = self.initial_position[2]

        return Node(position=[x_pos, y_pos, z_pos])

    @property
    def mirrored_yz(self):
        x_pos = self.initial_position[0] * -1
        y_pos = self.initial_position[1]
        z_pos = self.initial_position[2]

        return Node(position=[x_pos, y_pos, z_pos])