# ROS 2 Waveshare USB-CAN-B Driver

This repository provides a **ROS 2 Humble** package for communicating with the **Waveshare USB-CAN-B** adapter on **ARM Linux 64-bit** systems.

It enables CAN communication over ISO-TP protocol, primarily intended for sending motor control commands in the format `"m<left>,<right>"` over CAN ID `0x123`.

---

## 📂 Repository Structure
implementation/ # Example application for testing CAN communication

usb_can_node/ # Core driver library for USB-CAN-B adapter


---

## 🔧 Dependencies
1️⃣ Download the ARM64 driver from the official Waveshare site:  
https://www.waveshare.com/wiki/USB-CAN-B#c_2

Ensure the following files are available:
- `controlcan.h`
- `libcontrolcan.so`

These are already included in this repository.

---

## 📥 Build Instructions
```bash
# Navigate to your ROS 2 workspace
cd ~/ros2_ws/src
git clone https://github.com/AniArka/ros2_waveshare_canb.git
cd ..
colcon build --packages-select usb_can_node implementation
source install/setup.bash
```

---

## 🚀 Run with ROS 2:

```bash
ros2 run implementation test_send
```
## 📡 What It Does

- **CAN ID:** `0x123`
- **Payload Format:** `"m<left>,<right>"`
- **Protocol:** ISO-TP over CAN
- **Functionality:** Sends motor control commands via Waveshare USB-CAN-B to connected CAN devices.

---

## ⚠️ Notes

- This is currently an API-based implementation; ROS 2 topics or services are not provided (yet).
- Designed and tested on **ARM Linux 64-bit** platforms. [NVIDIA Jetson Orin Nano]

---

## 📄 License

This project is licensed under the **MIT License**.

---

## 🛠️ Planned Future Features

- ROS 2 `Node` for `/can_tx` and `/can_rx`
- Diagnostics / Error Reporting
- Configurable CAN parameters via ROS 2 parameters

---

## ✨ Author

**Arka Ghosh**  
Feel free to open Issues or PRs for improvements.
