#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from rclpy.parameter import Parameter
from typing import List
from rcl_interfaces.msg import SetParametersResult

from example_interfaces.msg import Int64
 
 
class NumberPublisherNode(Node): # MODIFY NAME
    def __init__(self):
        super().__init__("number_publisher_py")
        self.declare_parameter("number", 2)
        self.declare_parameter("timer_period", 1.0)
        
        self.add_on_set_parameters_callback(self.parameters_callback)
        
        #self.number_ = 2
        self.number_ =self.get_parameter("number").value
        self.timer_period_ =self.get_parameter("timer_period").value
        
        self.publishe1_ = self.create_publisher(Int64, "number_py",10)
        self.timer1_ = self.create_timer(self.timer_period_, self.publisherNumber)
        self.get_logger().info("Number station has been started")

    def publisherNumber(self):
        msg = Int64()
        msg.data = self.number_
        self.publishe1_.publish(msg)
        
    #def parameters_callback(self, params: list[Parameter]):
    def parameters_callback(self, params: List[Parameter]): 
        for param in params:
            if param.name == "number":
                self.number_ = param.value
                
        return SetParametersResult(successful=True)
 
 
def main(args=None):
    rclpy.init(args=args)
    node = NumberPublisherNode() # MODIFY NAME
    rclpy.spin(node)
    rclpy.shutdown()
 
 
if __name__ == "__main__":
    main()