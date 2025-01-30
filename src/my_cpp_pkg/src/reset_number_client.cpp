#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/set_bool.hpp"

class resetNumberClient : public rclcpp::Node // MODIFY NAME
{
public:
    resetNumberClient() : Node("reset_number_client") // MODIFY NAME
    {
        thread1_ = std::thread(std::
                    bind(&resetNumberClient::callResetNumberclient, this, false));
        threads_.push_back(std::thread(std::
                    bind(&resetNumberClient::callResetNumberclient, this, true)));
        threads_.push_back(std::thread(std::
                    bind(&resetNumberClient::callResetNumberclient, this, false)));
    }

    void callResetNumberclient(bool data)
    {
        auto client_ = this->create_client<example_interfaces::srv::SetBool>("reset_counter");
        while (!client_->wait_for_service(std::chrono::seconds(1)))
        {
            RCLCPP_WARN(this->get_logger(),"Waiting for the server to be up...");
        }
        auto request = std::make_shared<example_interfaces::srv::SetBool::Request>();
        request->data = data;

        auto future = client_->async_send_request(request);

        try
        {
            auto response = future.get();
            RCLCPP_INFO(this->get_logger(), "Es %d", data);
        }
        catch(const std::exception &e)
        {
            RCLCPP_ERROR(this->get_logger(), "Service call failed!");
        }
        
    }
 
private:
    std::thread thread1_;
    std::vector<std::thread> threads_;
};
 
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<resetNumberClient>(); // MODIFY NAME
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}