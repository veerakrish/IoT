# Experiment 6: Zigbee in IoT Systems (Simulation)

## Objective
Simulate Zigbee communication using ESP32's WiFi capabilities to demonstrate mesh networking concepts.

## Components Required
1. ESP32 Dev Kit V1 (x2 for full demonstration)
2. DHT11 Sensor (for one node)
3. LED (for the other node)
4. Jumper Wires
5. WiFi Network (2.4GHz)

## Connections
### Node 1 (Sensor Node)
- DHT11 VCC → 3.3V
- DHT11 Data → GPIO 4
- DHT11 GND → GND

### Node 2 (Actuator Node)
- LED Anode → GPIO 16 (with 220Ω resistor)
- LED Cathode → GND

## Setup Instructions
1. Update the WiFi credentials in both sketches
2. Upload the appropriate sketch to each ESP32
3. Monitor the Serial Monitor to see the simulated Zigbee communication

## Expected Output
- Sensor node will read temperature/humidity and broadcast it
- Actuator node will receive the data and control the LED based on temperature threshold
