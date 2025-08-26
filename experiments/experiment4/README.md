# Experiment 4: WiFi Light Control App

## Objective
Create a web application to control an LED connected to ESP32 over WiFi.

## Components Required
1. ESP32 Dev Kit V1
2. LED
3. 220Ω Resistor
4. Jumper Wires
5. WiFi Network (2.4GHz)

## Connections
- LED Anode → GPIO 16 (with 220Ω resistor)
- LED Cathode → GND

## Setup Instructions
1. Update the WiFi credentials in the ESP32 code
2. Upload the code to ESP32
3. Note the IP address shown in the Serial Monitor
4. Connect a device to the same WiFi network
5. Open a web browser and navigate to the ESP32's IP address
6. Use the web interface to control the LED

## Expected Output
A web interface with a toggle button to control the LED.
