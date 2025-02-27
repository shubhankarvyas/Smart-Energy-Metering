# IoT-Based Smart Energy Monitoring System

## Project Overview
This project focuses on designing an IoT-based smart energy monitoring system that enables real-time tracking and optimization of energy consumption in residential and industrial environments. The system leverages ESP32 microcontrollers, sensors, and cloud-based dashboards to provide users with valuable insights into their power usage and enhance efficiency.

## Features
- Real-time monitoring of voltage, current, power, and energy consumption
- Wireless data transmission using ESP32 with Wi-Fi capability
- Display of energy metrics on a Node-RED dashboard
- Automatic disconnection of loads exceeding a predefined power threshold
- MQTT protocol for lightweight and reliable communication
- Remote access and alerts for efficient energy management

## Components Used
- **ESP32 Microcontroller** (1 unit) - Core processing unit with Wi-Fi capability
- **ZMPT101B Voltage Sensor** (1 unit) - Measures AC voltage
- **SCT-013 Current Sensor** (1 unit) - Measures AC current
- **Relay Module** (1 unit) - Controls load switching
- **Breadboard and Jumper Wires** - For circuit connections
- **Passive Components** (Resistors and Capacitors) - Signal conditioning
- **LED Indicators** - For system status visualization

## System Architecture
1. **Data Collection**: Sensors measure voltage and current from connected loads.
2. **Processing**: ESP32 processes data and calculates power and energy consumption.
3. **Data Transmission**: Energy metrics are transmitted to a Node-RED dashboard via MQTT.
4. **User Interface**: Users monitor and control energy usage in real time through a graphical dashboard.
5. **Automation**: Loads are automatically disconnected if power exceeds predefined limits.

## Code Implementation
The system is programmed using **C++** in the **Arduino IDE**. The key functionalities include:

- Sensor interfacing with ESP32
- Data acquisition and processing
- MQTT communication for real-time data transfer
- Node-RED dashboard integration for visualization
- Load control through a relay module

## How to Use
1. **Set up hardware**: Connect sensors and ESP32 as per circuit diagram.
2. **Upload code**: Use Arduino IDE to flash the ESP32 with provided code.
3. **Connect to Wi-Fi**: Ensure ESP32 is connected to a local network.
4. **Configure MQTT**: Set up an MQTT broker and integrate it with Node-RED.
5. **Monitor Dashboard**: Observe real-time energy data and set automation rules.

## Future Enhancements
- Integration with **AI/ML** for predictive energy optimization
- Expansion to support **multiple loads and energy sources**
- Mobile app for **remote monitoring and control**
- Integration with **smart home automation systems**
