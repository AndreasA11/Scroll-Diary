#include "printingNode.hpp"


PrintingNode::PrintingNode() {
    transcribedTextSubscriber_ = create_subscription<std_msgs::msg::String>(
        "/transcription", 10, std::bind(&printingNode::transcriptionCallback, this, std::placeholders::_1));
    
    transcriptionStateSubscriber_ = create_subscription<std_msgs::msg::Bool> 
    ("/transcriptionState", 10, std::bind(&printingNode::transcriptionStateCallback, this, std::placeholders::_1));


    if(!initPrinter()) {
        RCLCPP_FATAL(get_logger(), "connection to printer failed");
    }
}

PrintingNode::~PrintingNode() {
    
}

bool PrintingNode::initPrinter() {

}

void PrintingNode::transcriptionCallback() {

}

void PrintingNode::transcriptionStateCallback() {
    
}

void PrintingNode::printTranscription() {

}


int main(int argc, char** argv) {
    rclcpp::init(argc, argv);

    try {
        rclcpp::spin(std::make_shared<PrintingNode>());
    } catch (const std::exception& e) {
        RCLCPP_FATAL(rclcpp::get_logger("main"), "Fatal: %s", e.what());
        rclcpp::shutdown();
        return 1;
    }

    rclcpp::shutdown();
    return 0;
    
}



