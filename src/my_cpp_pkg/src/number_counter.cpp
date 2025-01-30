#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"
 
class NumberCounterNode : public rclcpp::Node // MODIFY NAME
{
public:
    NumberCounterNode() : Node("number_counter_cpp"),numberCounter_(2)
    {
        Publisher1_ = this->create_publisher<example_interfaces::msg::Int64>("number_count",10);
        Subscriber1_= this->create_subscription<example_interfaces::msg::Int64>
                                        ("number_cpp",10,std::bind
                                        (&NumberCounterNode::SubscriberNumber, this, std::placeholders::_1));
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
    int numberCounter_;
    rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr Subscriber1_;
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr Publisher1_;

};
 
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberCounterNode>(); // MODIFY NAME
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}