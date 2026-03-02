#include "rclcpp/rclcpp.hpp"
#include "minimalNodeInclude.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("my_node_name");
    std::cout << "Hello World, minimalNode1 speaking!\n";
    includeClass includeClassInstance;
    std::cout << "includeClassInstance" << includeClassInstance.count <<  " " << includeClassInstance.name << "\n";
    includeClassInstance.count = 2;
    includeClassInstance.name = "includeClassName";
    std::cout << "includeClassInstance" << includeClassInstance.count <<  " " << includeClassInstance.name << "\n";
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}