#!/usr/bin/env python3
import rclpy
from rclpy.node import Node

from example_interfaces.msg import Int64
from example_interfaces.srv import SetBool
 
 
class NUmberCounterNode(Node): # MODIFY NAME
    def __init__(self):
        super().__init__("number_counter_server_py")
        
        self.numberCounter_ = 0

        self.publisher1_    = self.create_publisher(Int64, "number_counter",10)
        self.subscriber1_   = self.create_subscription(Int64,"number_py",self.SubscriberNumber,10)
        self.myServer_      = self.create_service(SetBool, "reset_counter", self.server_number_counter)
        self.get_logger().info("Number Counter has been started")

    def server_number_counter(self, request, response):
        if request.data:
            self.numberCounter_ = 0
            response.success = True
            response.message = "Counter has been reset"
        else:
            response.success = False
            response.message = "Counter has not been reset"
        return response

    def SubscriberNumber(self, msg):
        self.numberCounter_ += msg.data
        new_msg = Int64()
        new_msg.data = self.numberCounter_
        self.publisher1_.publish(new_msg)
 
 
def main(args=None):
    rclpy.init(args=args)
    node = NUmberCounterNode() # MODIFY NAME
    rclpy.spin(node)
    rclpy.shutdown()
 
 
if __name__ == "__main__":
    main()