# Edge-IoT Smart Energy Management System

A multi-node IoT-based system designed for real-time monitoring and control of electrical parameters across different rooms.  
Each ESP32 node measures voltage and current, sends data via MQTT to a Raspberry Pi Edge device, which processes the data, detects anomalies, and updates a cloud dashboard via Adafruit IO.  
0

---

## 🔥 Features

- Real-time monitoring of **voltage (V)**, **current (A)**, **power (W)**, and **energy (kWh)** per node  
- Local communication using **MQTT** between ESP32 nodes and Raspberry Pi  
- **Edge-based processing** for power calculations and safety anomaly detection  
- **Automatic relay control** during overvoltage or overcurrent conditions  
- Cloud dashboard on **Adafruit IO** for live visualizations  
- Fully scalable — easily add more nodes for more rooms or appliances  
1

---

## 📁 Project Structure￼Enter

smart-energy-management-system/ 
├── README.md                       
# Project summary ├── Project_Report_Smart_Energy.pdf 
# Full project documentation
├── node1_esp32.ino                 
# ESP32 Node 1 code └── node2_esp32.ino                 
# ESP32 Node 2 code

---

## 🧱 Hardware Components

- ESP32 (Node MCU – for each room/node)  
- Raspberry Pi (Edge device)  
- ACS712 Current Sensor (30A)  
- ZMPT101B Voltage Sensor  
- Relay Module  
- Connecting wires, breadboard, power supply  
2

---

## 🛠 Software & Tools

- **Arduino IDE** – ESP32 programming  
- **Python 3** – Edge device script  
- **MQTT** – Local communication  
- **Adafruit IO** – Cloud dashboard  
- **Wi-Fi network** – Connecting all components  
3

---

## ⚙ How It Works

### 1️⃣ Sensor Nodes (ESP32)
Each node measures:
- AC voltage using **ZMPT101B**  
- AC current using **ACS712**  

It publishes MQTT messages every 2 seconds to the Edge device:
```json
{"voltage": 230.15, "current": 0.42}

Topic example:
ems/node1/data

### 2️⃣ Edge Processing (Raspberry Pi)
The Edge device:
Receives sensor MQTT messages
Calculates power = V × I
Calculates energy = Σ(P × time)/1000
Detects anomalies (e.g., voltage > 250V)
Sends relay control commands back to nodes

Example control topic:
ems/node1/control → "OFF"

### 3️⃣ Cloud Visualization (Adafruit IO)
Displays:
Node 1 & Node 2 power
Total energy
Status indicators
Real-time charts & gauges
