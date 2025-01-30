#!/usr/bin/env python3
import rclpy
from rclpy.node import Node

from example_interfaces.msg import Int64
 
 
class NumberPublisherNode(Node): # MODIFY NAME
    def __init__(self):
        super().__init__("number_publisher_py") 
        
        self.number_ = 2
        self.publishe1_ = self.create_publisher(Int64, "number_py",10)
        self.timer1_ = self.create_timer(0.5, self.publisherNumber)
        self.get_logger().info("Number station has been started")

    def publisherNumber(self):
        msg = Int64()
        msg.data = self.number_
        self.publishe1_.publish(msg)
 
 
def main(args=None):
    rclpy.init(args=args)
    node = NumberPublisherNode() # MODIFY NAME
    rclpy.spin(node)
    rclpy.shutdown()
 
 
if __name__ == "__main__":
    main()