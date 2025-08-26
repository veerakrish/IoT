# Experiment 7: Complete IoT System

## Objective
Design and implement a complete IoT system with sensor data collection, wireless communication, and data visualization.

## Components Required
1. ESP32 Dev Kit V1
2. DHT11 Sensor (Temperature & Humidity)
3. PIR Motion Sensor
4. LED
5. Buzzer
6. Jumper Wires
7. WiFi Network (2.4GHz)

## System Architecture
1. **Edge Device (ESP32)**:
   - Collects data from DHT11 and PIR sensors
   - Processes data locally
   - Sends data to cloud via WiFi
   - Controls actuators (LED, Buzzer) based on conditions

2. **Cloud Service**:
   - Receives and stores sensor data
   - Provides real-time visualization
   - Sends alerts/notifications

## Connections
### Sensors:
- DHT11 VCC → 3.3V
- DHT11 Data → GPIO 4
- DHT11 GND → GND
- PIR VCC → 5V
- PIR OUT → GPIO 33
- PIR GND → GND

### Actuators:
- LED Anode → GPIO 16 (with 220Ω resistor)
- LED Cathode → GND
- Buzzer + → GPIO 17
- Buzzer - → GND

## Setup Instructions
1. Update WiFi credentials in the code
2. Create a Thingspeak account and get API key
3. Update the Thingspeak API key in the code
4. Upload the code to ESP32
5. Monitor the Serial Monitor for status updates
6. View the data on Thingspeak dashboard

## Expected Output
- Real-time sensor data visualization on Thingspeak
- LED turns ON when motion is detected
- Buzzer sounds when temperature exceeds threshold
- Serial monitor shows sensor readings and system status
