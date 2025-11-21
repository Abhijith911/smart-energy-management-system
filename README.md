# Edge-IoT Smart Energy Management System

This project implements a multi-node IoT-based smart energy monitoring system using ESP32 end nodes and a Raspberry Pi Edge device.  
Each node measures voltage and current, publishes readings via MQTT, while the Edge device computes power and energy, detects anomalies, and updates the dashboard.  
:contentReference[oaicite:0]{index=0}

---

## Features

- Real-time monitoring of **voltage**, **current**, **power**, and **energy**
- Two ESP32 nodes monitoring separate rooms
- Local MQTT communication between ESP32 nodes and Raspberry Pi
- **Edge-side energy computation** (W & kWh)
- **Automatic anomaly detection** (overvoltage / overcurrent)
- **Automatic relay shutdown** during unsafe conditions
- Cloud dashboard through Adafruit IO
:contentReference[oaicite:1]{index=1}

---

## 🧱 Hardware Used

- ESP32 NodeMCU (Node-1 & Node-2)
- Raspberry Pi (MQTT broker + Edge processing)
- ACS712 Current Sensor
- ZMPT101B Voltage Sensor
- Relay module
- Wi-Fi network
:contentReference[oaicite:2]{index=2}

---

## 🛠 Software & Tools

- Arduino IDE (ESP32 programming)
- Python 3 (Raspberry Pi Edge script)
- MQTT protocol
- Adafruit IO dashboard
- Wi-Fi for communication
:contentReference[oaicite:3]{index=3}

---

## ⚙ System Workflow

### **1️⃣ ESP32 Sensor Nodes (Room-1 & Room-2)**
Each node:
- Reads AC voltage via **ZMPT101B**
- Reads AC current via **ACS712**
- Computes instantaneous values and publishes:
```json
{"voltage": 230.15, "current": 0.42}
```
MQTT Topic Example: ems/node1/data 


## **2️⃣ Raspberry Pi (Edge Device)

The Edge device:

- Subscribes to node MQTT topics  
- Calculates:  
  - **Power (W) = V × I**  
  - **Energy (kWh)** over time  
- Detects anomaly conditions:  
  - Overvoltage  
  - Overcurrent  
- Sends control commands to nodes: ems/node1/control → OFF

- ## 3️⃣ Cloud Dashboard (Adafruit IO)

Displays:

- Node-1 power  
- Node-2 power  
- Total energy  
- Real-time charts and indicators  

📁 Project Files

smart-energy-management-system/
├── README.md                       # Project summary
├── Project_Report_Smart_Energy.pdf # Full project documentation
├── node1_esp32.ino                 # ESP32 Node 1 code
└── node2_esp32.ino                 # ESP32 Node 2 code



