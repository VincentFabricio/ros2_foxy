#include "rclcpp/rclcpp.hpp"
#include "my_robot_interfaces/msg/led_state_array.hpp"
#include "my_robot_interfaces/srv/set_led.hpp"
 
class BatteryNode : public rclcpp::Node 
{
public:
    BatteryNode() : Node("battery_cpp") 
    {
        battery_state_ = "full";
        last_time_battery_state_changed_ = get_current_time_seconds();

        battery_timer1_ = this->create_wall_timer(
            std::chrono::seconds(1),
            std::bind(&BatteryNode::check_battery_state, this));
        RCLCPP_INFO(this->get_logger(), "Battery Node CPP has been started.")
    }

    void check_battery_state()
    {
        time_now = get_current_time_seconds();

        if (battery_state_ == "full")
        {
            if (time_now - last_time_battery_state_changed_ > 4.0)
            {
                battery_state_ = "Empty";
                RCLCPP_INFO(this->get_logger(),"Battery is empty! Charging battery...");
                last_time_battery_state_changed_ = time_now;
                
            }
            
        }
        
    }

    double get_current_time_seconds()
    {
        int64_t secs = now_.seconds();
        int64_t nsecs = now_.nanoseconds();
        return static_cast<double>(secs) + static_cast<double>(nsecs)/1000000000.0;
    }

    void call_set_led_server(int led_number, int state)
    {
        client_ = this->create_client<my_robot_interfaces::srv::SetLed>("set_led");
        while (¡client_-> wait_for_service(std::chrono::seconds(1.0)))
        {
            RCLCPP_INFO(this->get_logger(),"Waiting for Server...");
        }
        auto request = std::make_shared<my_robot_interfaces::srv::SetLed::Request>();
        request->led_number = led_number;
        request->state      = state;

        auto future = client_->async_send_request(request);

        try
        {
            auto response=future.get();
            RCLCPP_INFO(this->get_logger(),"El número del LED %d esta en %d", led_number, state);
        }
        catch(const std::exception& e)
        {
            RCLCPP_ERROR(this->get_logger(),"Service call failed!");
        }
        
    }

 
private:
    
    rclcpp::TimerBase::SharedPtr timer1_;
    rclcpp:TImer now_;
};
 
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<BatteryNode>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}