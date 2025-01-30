#!/usr/bin/env python3
import rclpy
from rclpy.node import Node

from example_interfaces.msg import String
 
 
class RobotsNewsStationNode(Node): # MODIFY NAME
    def __init__(self):
        super().__init__("robot_news_station") # MODIFY NAME

        self.robot_name_ = "C3PO"
        self.robot_name2_ ="R2D2"
        self.publisher_ = self.create_publisher(String, "robot_news_",10)
        self.publisher2_ =self.create_publisher(String, "robot_sensor_",10)
        self.timer_ = self.create_timer(0.5, self.publish_news)
        self.timer2_ = self.create_timer (1, self.publish2_news)
        self.get_logger().info("Robot News Station has been started")

    def publish2_news(self):
        msg = String()
        msg.data = "Hello Fabricio, this is " + str(self.robot_name2_) + " from the robot news station."
        self.publisher2_.publish(msg)

    def publish_news(self):
        msg = String()
        msg.data = "Hello Vincent, this is " + str(self.robot_name_) + " from the robot news station."
        self.publisher_.publish(msg)
 
 
def main(args=None):
    rclpy.init(args=args)
    node = RobotsNewsStationNode() # MODIFY NAME
    rclpy.spin(node)
    rclpy.shutdown()
 
 
if __name__ == "__main__":
    main()