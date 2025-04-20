#include "rclcpp/rclcpp.hpp"
#include "my_robot_interfaces/msg/led_state_array.hpp"
#include "my_robot_interfaces/srv/set_led.hpp"

using std::placeholders::_1;
using std::placeholders::_2;

class LedPanelNode : public rclcpp::Node 
{
public:
    LedPanelNode() : Node("led_panel_cpp") 
    {
        this-> declare_parameter<std::vector<int64_t>>("led_states", std::vector<int64_t>{0, 0, 0, 0});

        led_states_ = this->get_parameter("led_states").as_integer_array();

        led_states_publisher_ = this->create_publisher<my_robot_interfaces::msg::LedStateArray>("set_led", 10);
        timer_ = this->create_wall_timer(
            std::chrono::seconds(4),
            std::bind(&LedPanelNode::publish_led_states, this));
        set_led_service_ = this->create_service<my_robot_interfaces::srv::SetLed>(
            "set_led", std::bind(&LedPanelNode::callback_set_led, this, _1, _2));
        RCLCPP_INFO(this->get_logger(), "LED Panel Node has been started in CPP.");

    }
 
private:
    void publish_led_states()
    {
        auto msg = my_robot_interfaces::msg::LedStateArray();
        msg.led_states = led_states_;
        led_states_publisher_ ->publish(msg);
    }

    void callback_set_led(
        const std::shared_ptr<my_robot_interfaces::srv::SetLed::Request> request,
        const std::shared_ptr<my_robot_interfaces::srv::SetLed::Response> response)
    {
        auto led_number     = request->led_number;
        auto state         = request->state;

        //if (led_number > led_states_.size() || led_number <=0)
        if(static_cast<long unsigned>(led_number) > led_states_.size() || led_number <= 0)
        {
            response ->success = false;
            return;
        }

        if (state != 0 && state != 1)
        {
            response ->success = false;
            return;
        }
        
        led_states_[led_number -1] = state;
        publish_led_states();
        response ->success = false;
        
    }

    std::vector<int64_t> led_states_;
    rclcpp::Publisher<my_robot_interfaces::msg::LedStateArray>::SharedPtr led_states_publisher_;
    rclcpp::Service<my_robot_interfaces::srv::SetLed>::SharedPtr set_led_service_;
    rclcpp::TimerBase::SharedPtr timer_;
};
 
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<LedPanelNode>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
