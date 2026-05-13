#include "printingNode.hpp"


printingNode::printingNode() 
: rclcpp::Node("printing_node") {
    this->declare_parameter<std::string>("printer_device", "/dev/usb/lp2");
    this->get_parameter("printer_device", printerDevice_);
    
    if (!initPrinter()) {
        RCLCPP_FATAL(get_logger(), "Failed to open printer");
        throw std::runtime_error("Printer open failed");
    }

    transcribedTextSubscriber_ = create_subscription<std_msgs::msg::String>(
        "/transcription", 10, std::bind(&printingNode::transcriptionCallback, this, std::placeholders::_1));
    
    transcriptionStateSubscriber_ = create_subscription<std_msgs::msg::Bool>( 
    "/transcriptionState", 10, std::bind(&printingNode::transcriptionStateCallback, this, std::placeholders::_1));

    
    
}

printingNode::~printingNode() {
    if(fd_ >= 0) {
        close(fd_);
    }
}

bool printingNode::initPrinter() {
    fd_ = open(printerDevice_.c_str(), O_WRONLY);
    if(fd_ < 0) {
        RCLCPP_ERROR(get_logger(), "printer failed to connect");
        return false;
    }
    std::string test = "printer connected, hello from pi";
    write(fd_, test.c_str(), test.size());
    write(fd_, "\n\n\n", 3);
    RCLCPP_INFO(get_logger(), "printer connected!");
    return true;
}

void printingNode::transcriptionCallback(const std_msgs::msg::String::SharedPtr msg) {
    fullTranscription_ += msg->data;
    fullTranscription_ += "\n";
}

void printingNode::transcriptionStateCallback(const std_msgs::msg::Bool::SharedPtr state) {
    if(state) {
        if(!transcriptionStarted_) {
            transcriptionStarted_ = true;
        }
        sendingTranscription_ = true;
    } else {
        sendingTranscription_ = false;
        printTranscription();
    }
}

void printingNode::printTranscription() {
    if(transcriptionStarted_ && !sendingTranscription_) {
        if(!fullTranscription_.empty()) {
            write(fd_, fullTranscription_.c_str(), fullTranscription_.size());
            write(fd_, "\n\n\n", 3);
            RCLCPP_INFO(get_logger(), fullTranscription_.c_str());
        }
        fullTranscription_.clear();
        close(fd_);
        //send print to make it actually print? or does it print as bytes come in?        
        transcriptionStarted_ = false;
    }
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



