#pragma once

#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/bool.hpp"


class printingNode : public rclcpp::Node {
    public:
        explicit printingNode();
        ~printingNode() override;

    private:
        bool initPrinter();

        void transcriptionCallback();
        void transcriptionStateCallback();
        void printTranscription();
        
        
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr transcribedTextSubscriber_;
        rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr transcriptionStateSubscriber_;

        //we are going to append all the transcribed chunks we received and eventually print this
        std::string fullTranscription = "";

}; 