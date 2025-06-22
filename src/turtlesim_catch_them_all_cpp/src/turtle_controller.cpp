#include "rclcpp/rclcpp.hpp"
#include <cmath>
#include "turtlesim/msg/pose.hpp"
#include "geometry_msgs/msg/twist.hpp"

using namespace std::chrono_literals;
using namespace std::placeholders;
 
class TurtleControllerNode : public rclcpp::Node 
{
public:
TurtleControllerNode() : Node("controller_cpp"), name_("turtle1"), turtlesim_up_(false)
    {
        target_x_ = 8.0;
        target_y_ = 4.0;

        cmd_vel_publisher_ = this->create_publisher<geometry_msgs::msg::Twist>(name_ + "/cmd_vel", 10);
        using std::placeholders::_1;
        pose_subscriber_ = this->create_subscription<turtlesim::msg::Pose>(
            name_ + "/pose", 10, std::bind(&TurtleControllerNode::callback_pose, this, _1));
        control_loop_timer_ = this->create_wall_timer(0.01s,
            std::bind(&TurtleControllerNode::control_loop, this));
    }
 
private:

    void callback_pose(const turtlesim::msg::Pose::SharedPtr pose)
    {
        pose_ = *pose.get();
        turtlesim_up_ = true;
    }

    void control_loop()
    {
        if (!turtlesim_up_)
        {
            return;
        }
        
        double dist_x = target_x_ - pose_.x;
        double dist_y = target_y_ - pose_.y;
        double distance = std::sqrt(dist_x*dist_x + dist_y*dist_y);

        auto msg = geometry_msgs::msg::Twist();

        if (distance > 0.5)
        {
            // position
            msg.linear.x = distance;

            // Orientaion
            double steering_angel = std::atan2(dist_y, dist_x);
            double angle_diff = steering_angel - pose_.theta;
            if (angle_diff > M_PI)
            {
                angle_diff -= 2* M_PI;
            }
            else if (angle_diff < -M_PI)
            {
                angle_diff += 2 * M_PI;
            }
            msg.angular.z = 6*angle_diff;
        }
        else
        {
            // target erached
            msg.linear.x = 0.0;
            msg.angular.z = 0.0;
        } 
        
        cmd_vel_publisher_ ->publish(msg);

    }

    std::string name_;
    bool turtlesim_up_;

    double target_x_;
    double target_y_;
    
    turtlesim::msg::Pose pose_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_publisher_;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr pose_subscriber_;
    rclcpp::TimerBase::SharedPtr control_loop_timer_;
};
 
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtleControllerNode>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}