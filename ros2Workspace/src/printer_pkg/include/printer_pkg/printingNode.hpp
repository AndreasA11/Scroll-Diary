#pragma once

#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include "rclcpp/rclcpp.hpp"



class PrintingNode : public rclcpp::Node {
    pubic:
        explicit PrintingNode();
    ~PrintingNode() override;

    private:
        bool initPrinter();

        void transcriptionCallback();
        void transcriptionStateCallback();
        void printTranscription();
        
        
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr transcribedTextSubscriber_;
        rclcpp::Subscription<std_msgs::msg::Bool>SharedPtr transcriptionStateSubscriber_;

        //we are going to append all the trnascribed chunks we received and eventually print this
        std::String fullTranscription = "";

}; 