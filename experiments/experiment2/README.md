# Experiment 2: Bluetooth LED Control

## Objective
Interface Bluetooth with ESP32 to control an LED using a smartphone.

## Components Required
1. ESP32 Dev Kit V1
2. LED
3. 220Ω Resistor
4. Jumper Wires
5. Smartphone with Bluetooth capability

## Connections
- LED Anode → GPIO 16 (with 220Ω resistor)
- LED Cathode → GND

## Setup Instructions
1. Connect the LED to GPIO 16 with a current-limiting resistor
2. Upload the provided code to ESP32
3. Install a Bluetooth Serial Terminal app on your smartphone
4. Pair with ESP32 (default name: "ESP32_BT_LED")
5. Send '1' to turn ON the LED, '0' to turn it OFF

## Expected Output
The LED will turn ON when '1' is received and OFF when '0' is received.
