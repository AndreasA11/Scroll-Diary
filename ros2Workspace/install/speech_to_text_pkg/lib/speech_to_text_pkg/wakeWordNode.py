#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, QoSReliabilityPolicy, QoSHistoryPolicy
from openwakeword.model import Model
import numpy as np
from std_msgs.msg import Bool
from speech_to_text_interfaces.msg import AudioStamped

class WakeWordNode(Node):
    def __init__(self):
        super().__init__('wake_word_node')
        
        qos_profile = QoSProfile(
            reliability=QoSReliabilityPolicy.BEST_EFFORT,
            history=QoSHistoryPolicy.KEEP_LAST,
            depth=10
        )

        self.subscription = self.create_subscription(
            AudioStamped, 
            '/raw_audio',
            self.audio_callback,
            qos_profile
        )

        self.publisher = self.create_publisher(
            Bool, 
            '/wakeState',
            10
        )

        # Initialize openWakeWord (no arguments!)
        self.oww = Model(vad_threshold=0.5)
        
        # Verify hey_jarvis is loaded
        available_models = list(self.oww.models.keys())
        self.get_logger().info(f"Available models: {available_models}")
        
        if 'hey_jarvis' not in available_models:
            self.get_logger().error("'hey_jarvis' model not found!")
        else:
            self.get_logger().info("'hey_jarvis' model loaded successfully")
        
        # Buffer for accumulating audio
        self.audio_buffer = []
        self.chunk_size = 1280  # 80ms at 16kHz
        
        # Confidence threshold
        self.confidence_threshold = 0.5
        
        self.get_logger().info("WakeWordNode ready, listening for 'Hey Jarvis'")
        
    def audio_callback(self, msg: AudioStamped):
        # Convert to numpy array
        audio_np = np.array(msg.data, dtype=np.float32)
        
        # Accumulate audio samples
        self.audio_buffer.extend(audio_np)
        
        # Process when we have enough samples
        if len(self.audio_buffer) >= self.chunk_size:
            # Get chunk
            chunk = np.array(self.audio_buffer[:self.chunk_size], dtype=np.float32)
            
            chunk_int16 = (chunk * 32767).astype(np.int16)
            # Predict
            prediction = self.oww.predict(chunk_int16)
            

            if 'hey_jarvis' in prediction:
                confidence = prediction['hey_jarvis']
                
                # Log periodically for debugging (every 100 frames)
                if not hasattr(self, '_debug_counter'):
                    self._debug_counter = 0
                self._debug_counter += 1
                
                if self._debug_counter % 100 == 0:
                    self.get_logger().info(
                        f"hey_jarvis confidence: {confidence:.3f}"
                    )
                
                # Check if above threshold
                if confidence > self.confidence_threshold:
                    self.get_logger().info(
                        f"Wake word 'Hey Jarvis' detected! (confidence: {confidence:.2f})"
                    )
                    
                    # Publish wake state
                    wake_msg = Bool()
                    wake_msg.data = True
                    self.publisher.publish(wake_msg)
                    
                    # Clear buffer after detection to avoid repeated triggers
                    self.audio_buffer = []
                    return
            
            # Keep overlap for next prediction (40ms)
            self.audio_buffer = self.audio_buffer[640:]

def main(args=None):
    rclpy.init(args=args)
    wake_word_node = WakeWordNode()
    try:
        rclpy.spin(wake_word_node)
    except KeyboardInterrupt:
        pass
    finally:
        wake_word_node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()