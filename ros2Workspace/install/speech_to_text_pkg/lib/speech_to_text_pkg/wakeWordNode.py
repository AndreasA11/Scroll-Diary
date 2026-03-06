#!/usr/bin/env python3

import rclpy
from rclpy.node import Node

class MinimalPyNode(Node):
    def __init__(self):
        super().__init__('minimal_py_node')
        self.get_logger().info('Python node started!')

def main(args=None):
    rclpy.init(args=args)
    node = MinimalPyNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()