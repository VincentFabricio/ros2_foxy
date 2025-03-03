#!/usr/bin/env python3
import rclpy
from rclpy.node import Node

from example_interfaces.msg import String
 
 
class RobotsNewsStationNode(Node): # MODIFY NAME
    def __init__(self):
        super().__init__("robot_news_station")
        self.declare_parameter("robot_name1", "C3P0")
        self.declare_parameter("robot_name2", "R2D2")
        self.declare_parameter("text1", "Hello Fabricio, this is ")

        self.text1_ =self.get_parameter("text1").value
        self.robot_name_ = self.get_parameter("robot_name1").value
        self.robot_name2_ = self.get_parameter("robot_name2").value
        self.publisher_ = self.create_publisher(String, "robot_news_",10)
        self.publisher2_ =self.create_publisher(String, "robot_sensor_",10)
        self.timer_ = self.create_timer(0.5, self.publish_news)
        self.timer2_ = self.create_timer (1, self.publish2_news)
        self.get_logger().info("Robot News Station has been started")

    def publish2_news(self):
        msg = String()
        msg.data = str(self.text1_) + str(self.robot_name2_) + " from the robot news station."
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