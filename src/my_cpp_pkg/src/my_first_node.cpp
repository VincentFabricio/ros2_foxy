#include "rclcpp/rclcpp.hpp"

class MyNode: public rclcpp::Node
{
private:
    void timerCallback()
    {
        counter_++;
        RCLCPP_INFO(this->get_logger(), "Timer event: %d",counter_);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    int counter_;
public:
    MyNode():Node("cpp_test"), counter_(0)
    {
        RCLCPP_INFO(this->get_logger(),"Hello World ROS2 CPP" );
        timer_ = this->create_wall_timer(std::chrono::seconds(1),
                                        std::bind(&MyNode::timerCallback, this));
    }
    ~MyNode();
};


MyNode::~MyNode()
{
}


int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node= std::make_shared<MyNode>();
    RCLCPP_INFO(node->get_logger(),"New Node CPP" );
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
