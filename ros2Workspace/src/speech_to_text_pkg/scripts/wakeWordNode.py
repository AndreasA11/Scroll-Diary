#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, QoSReliabilityPolicy, QoSHistoryPolicy
import openwakeword
from speech_to_text_interfaces.msg import AudioStamped

class openWakeWordNode(Node):
    def __init__(self):
        super().__init__('rawAudio_subscriber')
        
        qos_profile = QoSProfile(
            reliability = QoSReliabilityPolicy.BEST_EFFORT,
            history = QoSHistoryPolicy.KEEP_LAST,
            depth = 10
        )

        self.subscription = self.create_subscription(
            AudioStamped, 
            '/raw_audio',
            self.listener_callback,
            qos_profile
        )
        self.subscription

    def listener_callback(self, msg):
        self.get_logger().info('I heard: "%s"' %msg.data)       

def main(args=None):
    print("Hello World, openWakeWordNode speaking!")
    rclpy.init(args=args)
    wakeWordNodeSubscriber = openWakeWordNode()
    rclpy.spin(wakeWordNodeSubscriber)
    wakeWordNodeSubscriber.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
