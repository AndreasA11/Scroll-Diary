#include "motorNode.hpp"
#include <unistd.h>

using namespace std::chrono_literals;

motorNode::motorNode()
: rclcpp::Node("motor_node") {
    this->declare_parameter<int>("pin_step", 23);
    this->declare_parameter<int>("pin_dir", 24);
    this->declare_parameter<int>("pin_laser", 17);
    this->declare_parameter<int>("steps_per_roll", 200);
    this->declare_parameter<int>("step_pulse_us", 1000);
    this->declare_parameter<bool>("roll_direction_forward", true);
    this->declare_parameter<int>("laser_active_level", 0); // most IR break-beam modules pull LOW when broken

    this->get_parameter("pin_step", pinStep_);
    this->get_parameter("pin_dir", pinDir_);
    this->get_parameter("pin_laser", pinLaser_);
    this->get_parameter("steps_per_roll", stepsPerRoll_);
    this->get_parameter("step_pulse_us", stepPulseUs_);
    this->get_parameter("roll_direction_forward", rollDirection_);
    this->get_parameter("laser_active_level", laserActiveLevel_);

    if (!initGpio()) {
        RCLCPP_FATAL(get_logger(), "Failed to init GPIO");
        throw std::runtime_error("GPIO init failed");
    }

    // Poll the laser sensor instead of using lgpio's alert callback, which
    // fires on its own thread and would need extra synchronization to touch
    // ROS/node state safely. 100 Hz is plenty for a falling sheet of paper.
    pollTimer_ = create_wall_timer(10ms, std::bind(&motorNode::checkLaser, this));

    RCLCPP_INFO(get_logger(), "motor_node ready");
}

motorNode::~motorNode() {
    if (gpioHandle_ >= 0) {
        lgGpioFree(gpioHandle_, pinStep_);
        lgGpioFree(gpioHandle_, pinDir_);
        lgGpioFree(gpioHandle_, pinLaser_);
        lgGpiochipClose(gpioHandle_);
    }
}

bool motorNode::initGpio() {
    gpioHandle_ = lgGpiochipOpen(0);
    if (gpioHandle_ < 0) {
        RCLCPP_ERROR(get_logger(), "Failed to open gpiochip");
        return false;
    }

    if (lgGpioClaimOutput(gpioHandle_, 0, pinStep_, 0) < 0 ||
        lgGpioClaimOutput(gpioHandle_, 0, pinDir_, 0) < 0) {
        RCLCPP_ERROR(get_logger(), "Failed to claim step/dir pins as outputs");
        return false;
    }

    if (lgGpioClaimInput(gpioHandle_, LG_SET_PULL_DOWN, pinLaser_) < 0) {
        RCLCPP_ERROR(get_logger(), "Failed to claim laser pin as input");
        return false;
    }

    lgGpioWrite(gpioHandle_, pinDir_, rollDirection_ ? 1 : 0);
    return true;
}

void motorNode::checkLaser() {
    int level = lgGpioRead(gpioHandle_, pinLaser_);
    if (level < 0) {
        RCLCPP_WARN(get_logger(), "Failed to read laser pin");
        return;
    }

    bool beamBroken = (level == laserActiveLevel_);

    if (beamBroken && !paperPresent_) {
        // Paper just fell through the beam.
        paperPresent_ = true;
        RCLCPP_INFO(get_logger(), "Paper detected, rolling motor");
        stepMotor(stepsPerRoll_, rollDirection_);
    } else if (!beamBroken && paperPresent_) {
        // Beam restored: paper has cleared the sensor, ready to trigger again.
        paperPresent_ = false;
    }
}

void motorNode::stepMotor(int steps, bool direction) {
    lgGpioWrite(gpioHandle_, pinDir_, direction ? 1 : 0);
    for (int i = 0; i < steps; ++i) {
        lgGpioWrite(gpioHandle_, pinStep_, 1);
        usleep(stepPulseUs_);
        lgGpioWrite(gpioHandle_, pinStep_, 0);
        usleep(stepPulseUs_);
    }
    RCLCPP_INFO(get_logger(), "Done rolling");
}

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);

    try {
        rclcpp::spin(std::make_shared<motorNode>());
    } catch (const std::exception& e) {
        RCLCPP_FATAL(rclcpp::get_logger("main"), "Fatal: %s", e.what());
        rclcpp::shutdown();
        return 1;
    }

    rclcpp::shutdown();
    return 0;
}