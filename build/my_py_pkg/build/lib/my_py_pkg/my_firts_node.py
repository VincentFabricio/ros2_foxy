
import rclpy
from rclpy.node import Node


def main(args=None):
    rclpy.init(args=args) #init comunication
    node = Node("py_test")
    node.get_logger().info("Hello World ROS2")
    rclpy.shutdown()

if __name__ == '__main__':
    main()

