#include "rclcpp/rclcpp.hpp"
#include <cmath>
#include "turtlesim/srv/spawn.hpp"
 
class TurtleSpawnerNode : public rclcpp::Node 
{
public:
TurtleSpawnerNode() : Node("spawner_cpp")
    {
    }
 
private:
};
 
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtleSpawnerNode>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}