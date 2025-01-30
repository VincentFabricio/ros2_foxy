#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.srv import SetBool
from functools import partial
 
 
class ResetNumberCount(Node): # MODIFY NAME
    def __init__(self):
        super().__init__("reset_number_count_service") # MODIFY NAME
        self.call_reset_number_count(False)
        self.call_reset_number_count(True)

    def call_reset_number_count(self, boolState):
        client1_ = self.create_client(SetBool, "reset_counter")
        while not client1_.wait_for_service(1):
            self.get_logger().info("Waiting for server...")
        
        request = SetBool.Request()
        request.data = bool(boolState)
        
        future = client1_.call_async(request)
        future.add_done_callback(partial
                (self.callback_call_reset_number_count, boolState = boolState))
        
    def callback_call_reset_number_count(self, future, boolState):
        try:
                response = future.result()
                self.get_logger().info('Bool state is: ' + str(boolState))
        except Exception as e:
            self.get_logger().error("service call failed %r" %(e,))
        
        
 
def main(args=None):
    rclpy.init(args=args)
    node = ResetNumberCount() # MODIFY NAME
    rclpy.spin(node)
    rclpy.shutdown()
 
 
if __name__ == "__main__":
    main()