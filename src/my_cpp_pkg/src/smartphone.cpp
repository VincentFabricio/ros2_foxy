#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"

class SmartPhoneNode : public rclcpp::Node // MODIFY NAME
{
public:
    SmartPhoneNode() : Node("smartphone_cpp") // MODIFY NAME
    {
        subcriber_ = this->create_subscription
                        <example_interfaces::msg::String>("robot_news_cpp", 10, std::bind
                        (&SmartPhoneNode::callbackRobotNews, this, std::placeholders::_1));
        subcriber2_ = this->create_subscription
                        <example_interfaces::msg::String>("robot_sensor_cpp", 10, std::bind
                        (&SmartPhoneNode::callbackRobotNews2, this, std::placeholders::_1));
        RCLCPP_INFO(this->get_logger(),"SmartPhone has been started.");
    }

private:
    void callbackRobotNews(const example_interfaces::msg::String::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "%s", msg->data.c_str());
    }
    void callbackRobotNews2(const example_interfaces::msg::String::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "%s", msg->data.c_str());
    }

    rclcpp::Subscription<example_interfaces::msg::String>::SharedPtr subcriber_;
    rclcpp::Subscription<example_interfaces::msg::String>::SharedPtr subcriber2_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SmartPhoneNode>(); // MODIFY NAME
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}