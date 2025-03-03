#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"
 
class NumberPublisherNode : public rclcpp::Node // MODIFY NAME
{
public:
    NumberPublisherNode() : Node("number_publisher_cpp")
    {
        this->declare_parameter("number", 2);
        this->declare_parameter("timer_period", 1.0);

        number_ = this->get_parameter("number").as_int();
        double timer_period = this->get_parameter("timer_period").as_double();

        Publisher1_ = this->create_publisher<example_interfaces::msg::Int64>("number_cpp",10);
        timer1_     = this->create_wall_timer(std::chrono::duration<double>(timer_period),
                                            std::bind(&NumberPublisherNode::PublisherNumber,this));
        //timer1_     = this->create_wall_timer(std::chrono::milliseconds(800),std::bind(&NumberPublisherNode::PublisherNumber,this));
        //timer1_     = this->create_wall_timer(1s, std::bind(&NumberPublisherNode::PublisherNumber,this));
        
        RCLCPP_INFO(this->get_logger(),"Number Publisher has been started.");
    }
 
private:
    void PublisherNumber()
    {
        auto msg = example_interfaces::msg::Int64();
        msg.data = number_;
        Publisher1_ -> publish(msg);
    }
    std::int64_t number_;
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr Publisher1_;
    rclcpp::TimerBase::SharedPtr timer1_;
};
 
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberPublisherNode>(); // MODIFY NAME
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}