#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"

class RobotNewsStationNode : public rclcpp::Node // MODIFY NAME
{
public:
    RobotNewsStationNode() : Node("robot_news_station_cpp")
    {
        this->declare_parameter<std::string>("robot_name1", "R2D2_");
        this->declare_parameter<std::string>("robot_name2", "C3P0_");
        this->declare_parameter<std::string>("text1", "Hi Vincent, this is ");

        robot_name_ = this->get_parameter("robot_name1").as_string();
        robot_name2_ = this->get_parameter("robot_name2").as_string();
        text1_ =this->get_parameter("text1").as_string();

        Publisher_ = this->create_publisher<example_interfaces::msg::String>("robot_news_cpp", 10);
        Publisher2_ = this->create_publisher<example_interfaces::msg::String>("robot_sensor_cpp", 10);
        timer_ = create_wall_timer(std::chrono::milliseconds(500),
                                   std::bind(&RobotNewsStationNode::publishNew, this));
        timer2_ = create_wall_timer(std::chrono::milliseconds(500),
                                   std::bind(&RobotNewsStationNode::publishNew2, this));
        RCLCPP_INFO(this->get_logger(), "Robot New Station has been started.");
    }

private:
    void publishNew()
    {
        auto msg = example_interfaces::msg::String();
        msg.data = text1_ + robot_name_ + std::string(" from the Robot New Station.");
        Publisher_->publish(msg);
    }
    void publishNew2()
    {
        auto msg = example_interfaces::msg::String();
        msg.data = std::string("Hi Fabricio, this is ") + robot_name2_ + std::string(" from the Robot New Station.");
        Publisher2_->publish(msg);
    }

    std::string robot_name_;
    std::string robot_name2_;
    std::string text1_;

    rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr Publisher_;
    rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr Publisher2_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::TimerBase::SharedPtr timer2_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RobotNewsStationNode>(); // MODIFY NAME
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}