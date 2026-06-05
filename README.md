Scroll-Diary is a ROS 2–based system that enables voice-driven text capture and physical output, integrating speech-to-text processing 
with embedded device control (e.g., receipt/thermal printers). The project is designed as a modular robotics-style pipeline where 
audio input, transcription, and output devices are handled as independent ROS 2 nodes.

The goal of Scroll-Diary is to provide a hands-free journaling / logging system using spoken input. Speech is captured and transcribed 
in real time, then routed through ROS 2 nodes that can display, store, or physically print the resulting text.

------------------------------------------------------------------------------------------------------------------------------------------

Architecture

The project is structured as a ROS 2 workspace with supporting modules:

1. Speech-to-Text Node

Captures microphone audio
Performs local speech recognition
Publishes transcribed text to ROS 2 topics
Designed to run independently of output hardware

2. ROS 2 Core Workspace

Manages node lifecycle, parameters, and message passing
Allows transcription data to be consumed by multiple downstream nodes (logging, printing, storage, etc.)
Built and managed using `colcon`

3. Printer / Output Node

Interfaces with USB-connected receipt or thermal printers
Supports raw ESC/POS printing
Handles device paths (e.g. `/dev/usb/lp*`) and CUPS fallbacks
Enables real-time printing of transcribed speech

------------------------------------------------------------------------------------------------------------------------------------------

Requirements

Software

ROS 2 (jazzy)
- Python 3
- C++ (17+)
- `colcon`
- Linux audio stack (ALSA / PulseAudio / PipeWire)

Hardware

- Rasberry pi 5
- USB microphone
- USB receipt / thermal printer (ESC/POS compatible)
- Linux host (tested with `/dev/usb/lp*` devices)

------------------------------------------------------------------------------------------------------------------------------------------

Setup & Build

Clone the repository
```bash
git clone https://github.com/AndreasA11/Scroll-Diary.git
cd Scroll-Diary
```

Build the ROS 2 workspace
```bash
cd ros2Workspace
colcon build --symlink-install
source install/setup.bash
```
------------------------------------------------------------------------------------------------------------------------------------------

## ▶️ Running the System

Start the speech-to-text node

```bash
ros2 run speech_to_text speech_node
```

Start the printer/output node

```bash
ros2 run printer_pkg printing_node \
  --ros-args -p printer_device:=/dev/usb/lp2
```

The printer node listens for transcribed text messages and prints them in real time.

------------------------------------------------------------------------------------------------------------------------------------------

Current Status

✅ Speech-to-text pipeline operational
✅ ROS 2 nodes communicating correctly (Further stress testing tbd)
✅ Printer integration working with raw output
🔧 Ongoing work: Tweeking the motor timings to make sure the feed(paper) rolls up into a scroll seemlessly

------------------------------------------------------------------------------------------------------------------------------------------

Roadmap

* Add launch file for easier start
* Improve transcription accuracy and noise handling
* Add configurable output modes (print, save, display)
* Package nodes for easier deployment
* Improve motor timings
* Add physical package for entire setup
* Eventually switch to batteries so it doesn't need to be plugged in?

------------------------------------------------------------------------------------------------------------------------------------------

📄 License

License not yet specified.

------------------------------------------------------------------------------------------------------------------------------------------
