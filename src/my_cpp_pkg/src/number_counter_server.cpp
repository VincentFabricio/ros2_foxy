#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"
#include "example_interfaces/srv/set_bool.hpp"

using std::placeholders::_1;
using std::placeholders::_2;
 
class NumberCounterNode : public rclcpp::Node // MODIFY NAME
{
public:
    NumberCounterNode() : Node("number_counter_server_cpp"),numberCounter_(2)
    {
        Publisher1_ = this->create_publisher<example_interfaces::msg::Int64>("number_count",10);
        Subscriber1_= this->create_subscription<example_interfaces::msg::Int64>
                                        ("number_cpp",10,std::bind
                                        (&NumberCounterNode::SubscriberNumber, this, std::placeholders::_1));
        Server1_    = this->create_service<example_interfaces::srv::SetBool>
                                        ("reset_counter", std::bind(
                                            &NumberCounterNode::callbackResetCounter, this, _1, _2));
        RCLCPP_INFO(this->get_logger(),"Number Counter has been started.");
        
    }
 
private:
    void SubscriberNumber(const example_interfaces::msg::Int64::SharedPtr msg)
    {
        numberCounter_+=msg->data;
        auto newMsg = example_interfaces::msg::Int64();
        newMsg.data = numberCounter_;
        Publisher1_ ->publish(newMsg);
    }
    void callbackResetCounter(
        const std::shared_ptr<example_interfaces::srv::SetBool::Request> request,
        const std::shared_ptr<example_interfaces::srv::SetBool::Response> response)
    {
        if (request -> data)
        {
            numberCounter_ = 0;
            response->success = true;
            response->message = "Counter has been reset";
        }
        else
        {
            response->success = false;
            response->message = "Counter has not been reset";
        }
        
    } 
    int numberCounter_;
    rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr Subscriber1_;
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr Publisher1_;
    rclcpp::Service<example_interfaces::srv::SetBool>::SharedPtr Server1_;

};
 
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberCounterNode>(); // MODIFY NAME
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}