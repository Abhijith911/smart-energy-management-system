# ⚡ Edge-IoT Smart Energy Management System

<p align="center">
  <img src="https://img.shields.io/badge/Platform-Raspberry%20Pi-red?style=for-the-badge&logo=raspberrypi"/>
  <img src="https://img.shields.io/badge/Node-ESP32-blue?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Protocol-MQTT-purple?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Dashboard-Adafruit%20IO-teal?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Language-Python%203-yellow?style=for-the-badge&logo=python"/>
</p>

<p align="center">
  A multi-node IoT-based smart energy monitoring system using <strong>ESP32</strong> end nodes and a <strong>Raspberry Pi</strong> edge device.<br/>
  Measures voltage and current in real time, computes power and energy at the edge, detects anomalies, and visualizes data on a cloud dashboard.
</p>


## 🎯 Overview

| Component | Role |
|---|---|
| ESP32 Node-1 & Node-2 | Sensor data acquisition + MQTT publishing |
| Raspberry Pi | Edge processing, MQTT broker, anomaly detection |
| Adafruit IO | Cloud dashboard + real-time visualization |
| MQTT | Local communication protocol between nodes and edge |

---

## ✨ Features

- 📡 Real-time monitoring of **voltage**, **current**, **power**, and **energy**
- 🏠 Two ESP32 nodes monitoring separate rooms independently
- 🔁 Local MQTT communication between ESP32 nodes and Raspberry Pi
- ⚙️ **Edge-side computation** — power (W) and energy (kWh) calculated on the Pi
- 🚨 **Automatic anomaly detection** — overvoltage and overcurrent alerts
- 🔌 **Automatic relay shutdown** during unsafe conditions
- ☁️ **Cloud dashboard** via Adafruit IO with live charts and indicators

---

## 🧱 Hardware Used

- ESP32 NodeMCU × 2 (Node-1 & Node-2)
- Raspberry Pi (MQTT broker + edge processing)
- ZMPT101B Voltage Sensor
- ACS712 Current Sensor
- Relay module
- Wi-Fi network

---

## 🛠️ Software & Tools

- Arduino IDE — ESP32 firmware
- Python 3 — Raspberry Pi edge script
- MQTT protocol — local pub/sub communication
- Adafruit IO — cloud dashboard
- Wi-Fi — wireless node communication

---

## ⚙️ System Workflow

### 1. ESP32 Sensor Nodes (Room-1 & Room-2)

Each node reads sensors and publishes JSON data over MQTT:

```json
{"voltage": 230.15, "current": 0.42}
```

| Sensor | Measurement |
|---|---|
| ZMPT101B | AC Voltage |
| ACS712 | AC Current |

**MQTT publish topic example:** `ems/node1/data`

---

### 2. Raspberry Pi — Edge Device

The Pi subscribes to node topics and handles all computation:

- **Power:** `W = V × I`
- **Energy:** accumulated `kWh` over time
- **Anomaly detection:** flags overvoltage and overcurrent conditions
- **Relay control:** sends shutdown command on anomaly

**MQTT control topic example:** `ems/node1/control → OFF`

---

### 3. Cloud Dashboard — Adafruit IO

Displays live and historical data:

- Node-1 power consumption
- Node-2 power consumption
- Total system energy (kWh)
- Real-time charts and status indicators

---

## 📂 Project Structure

```
smart-energy-management-system/
├── node1_esp32.ino                 # ESP32 Node-1 firmware
├── node2_esp32.ino                 # ESP32 Node-2 firmware
├── Project_Report_Smart_Energy.pdf # Full project documentation
└── README.md
```

---

## 🔌 Hardware Wiring

```
[ZMPT101B]──► ESP32 Node ──Wi-Fi──► Raspberry Pi (MQTT Broker)
[ACS712]───►              MQTT               │
[Relay]    ◄──────────────────── control cmd │
                                             │
                                       Adafruit IO
                                      (Cloud Dashboard)
```

---

## 📦 Setup & Installation

### ESP32 Nodes
1. Open `node1_esp32.ino` / `node2_esp32.ino` in **Arduino IDE**
2. Set your Wi-Fi SSID, password, and Raspberry Pi IP in the config section
3. Flash to the respective ESP32 boards

### Raspberry Pi Edge Device
```bash
pip3 install paho-mqtt adafruit-io --break-system-packages
python3 edge.py
```

> Make sure **Mosquitto MQTT broker** is installed and running on the Pi:
> ```bash
> sudo apt install mosquitto mosquitto-clients -y
> sudo systemctl enable mosquitto
> ```

---

## 🛠️ Tech Stack

| Category | Technology |
|---|---|
| Microcontroller Firmware | Arduino C++ (ESP32) |
| Edge Processing | Python 3 |
| Communication | MQTT (Mosquitto broker) |
| Sensors | ZMPT101B (voltage), ACS712 (current) |
| Cloud Dashboard | Adafruit IO |
| Hardware | Raspberry Pi, ESP32 × 2, Relay module |

---

## 🚀 Future Improvements

- Add energy cost calculation based on per-unit tariff
- Expand to more nodes for whole-building monitoring
- Integrate SMS/email alerts on anomaly detection
- Replace Adafruit IO with a self-hosted Grafana dashboard
- Add historical data logging to a local database

---
