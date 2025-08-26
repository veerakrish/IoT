# Experiment 5: Network Protocols in IoT

## Objective
Demonstrate the use of various network protocols (HTTP, MQTT) in IoT systems using ESP32.

## Components Required
1. ESP32 Dev Kit V1
2. DHT11 Sensor
3. WiFi Network (2.4GHz)
4. Jumper Wires

## Connections
- DHT11 VCC → 3.3V
- DHT11 Data → GPIO 4
- DHT11 GND → GND

## Setup Instructions
1. Update the WiFi credentials in the code
2. For MQTT, set up a local MQTT broker or use a cloud service
3. Update the MQTT broker details in the code
4. Upload the code to ESP32
5. Monitor the Serial Monitor for connection status

## Expected Output
Sensor data will be published to both HTTP endpoint and MQTT broker.
