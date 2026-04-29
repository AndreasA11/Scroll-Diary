#include "printingNode.hpp"


printingNode::printingNode() 
: rclcpp::Node("printing_node") {
    transcribedTextSubscriber_ = create_subscription<std_msgs::msg::String>(
        "/transcription", 10, std::bind(&printingNode::transcriptionCallback, this, std::placeholders::_1));
    
    transcriptionStateSubscriber_ = create_subscription<std_msgs::msg::Bool> 
    ("/transcriptionState", 10, std::bind(&printingNode::transcriptionStateCallback, this, std::placeholders::_1));


    if(!initPrinter()) {
        RCLCPP_FATAL(get_logger(), "connection to printer failed");
    }
}

printingNode::~printingNode() {
    
}

bool printingNode::initPrinter() {

}

void printingNode::transcriptionCallback(const std_msgs::msg::String::SharedPtr msg) {

}

void printingNode::transcriptionStateCallback() {
    
}

void printingNode::printTranscription() {

}


int main(int argc, char** argv) {
    rclcpp::init(argc, argv);

    try {
        rclcpp::spin(std::make_shared<printingNode>());
    } catch (const std::exception& e) {
        RCLCPP_FATAL(rclcpp::get_logger("main"), "Fatal: %s", e.what());
        rclcpp::shutdown();
        return 1;
    }

    rclcpp::shutdown();
    return 0;
    
}



