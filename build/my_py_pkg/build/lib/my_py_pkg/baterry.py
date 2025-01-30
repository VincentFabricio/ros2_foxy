#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
 
 
class BaterryNode(Node): 
    def __init__(self):
        super().__init__("baterry_py")
        
        self.battery_state_ ="full"
        self.last_time_battery_state_changed_ = self.get_current_time_seconds()
        
        self.battery_timer1_ = self.create_timer(8.1, self.check_battery_state)
        
    def check_battery_state(self):
        time_now = self.get_current_time_seconds()
        
        if self.battery_state_ == "full":
            if time_now - self.last_time_battery_state_changed_ > 4.0:
                self.battery_state_ = "empty"
                self.get_logger().info('Baterry is empty! Charging battery...')
                self.last_time_battery_state_changed_ = time_now
        else:
            if time_now - self.last_time_battery_state_changed_ > 6.0:
                self.battery_state_ = "full"
                self.get_logger().info('Baterry is now full again.')
                self.last_time_battery_state_changed_ = time_now

        
    def get_current_time_seconds(self):
        secs, nsecs= self.get_clock().now().seconds_nanoseconds()
        return secs + nsecs/1000000000.0
 
 
def main(args=None):
    rclpy.init(args=args)
    node = BaterryNode() # MODIFY NAME
    rclpy.spin(node)
    rclpy.shutdown()
 
 
if __name__ == "__main__":
    main()