#pragma once

#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include "rclcpp/rclcpp.hpp"

class PrintingNode : public rclcpp::Node {
    public:
        explicit PrintingNode();
        ~PrintingNode() override;

    private:
        bool initPrinter();

        void transcriptionCallback();
        void printTranscription();
        
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr transcribed_text_subscriber_;


}; 