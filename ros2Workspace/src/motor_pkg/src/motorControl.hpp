#ifndef MOTOR_NODE_HPP_
#define MOTOR_NODE_HPP_

#include <rclcpp/rclcpp.hpp>
#include <lgpio.h>

class motorNode : public rclcpp::Node {
public:
    motorNode();
    ~motorNode();

private:
    bool initGpio();
    void checkLaser();
    void stepMotor(int steps, bool direction);

    // GPIO
    int gpioHandle_{-1};
    int pinStep_;
    int pinDir_;
    int pinLaser_;

    // Motor params
    int stepsPerRoll_;
    int stepPulseUs_;
    bool rollDirection_;

    // Laser state
    bool paperPresent_{false};
    int laserActiveLevel_; // GPIO level that means "beam broken / paper present"

    rclcpp::TimerBase::SharedPtr pollTimer_;
};

#endif  // MOTOR_NODE_HPP_