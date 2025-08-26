# Experiment 1: Bluetooth Sensor Data Transmission

## Objective
Interface Bluetooth with ESP32 and send sensor data to a smartphone using Bluetooth.

## Components Required
1. ESP32 Dev Kit V1
2. DHT11 Sensor (Temperature and Humidity)
3. Jumper Wires
4. Smartphone with Bluetooth capability

## Connections
- DHT11 VCC → 3.3V
- DHT11 Data → GPIO 4
- DHT11 GND → GND

## Setup Instructions
1. Connect the DHT11 sensor as specified above
2. Upload the provided code to ESP32
3. Install a Bluetooth Serial Monitor app on your smartphone
4. Pair with ESP32 (default name: "ESP32_BT")
5. Open the serial monitor to view sensor data

## Expected Output
Temperature and humidity readings will be sent to the connected smartphone via Bluetooth.
