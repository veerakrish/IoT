# Experiment 9: Raspberry Pi Integration with System Components

## Objective
Demonstrate the integration of a Raspberry Pi with various system components to create an IoT system.

## Components Required
1. Raspberry Pi (3/4/Zero W)
2. ESP32 Dev Kit V1 (as a sensor node)
3. DHT11 Sensor
4. PIR Motion Sensor
5. LED
6. Jumper Wires
7. WiFi Network (for MQTT communication)

## System Architecture
1. **Sensor Node (ESP32)**:
   - Collects data from DHT11 and PIR sensors
   - Sends data to MQTT broker

2. **Central Hub (Raspberry Pi)**:
   - Runs MQTT broker (Mosquitto)
   - Runs Node-RED for data processing and visualization
   - Can send commands to ESP32

## Connections for ESP32 Node
### Sensors:
- DHT11 VCC → 3.3V
- DHT11 Data → GPIO 4
- DHT11 GND → GND
- PIR VCC → 5V
- PIR OUT → GPIO 33
- PIR GND → GND

### Actuator:
- LED Anode → GPIO 16 (with 220Ω resistor)
- LED Cathode → GND

## Setup Instructions
### On Raspberry Pi:
1. Install Mosquitto MQTT broker:
   ```bash
   sudo apt update
   sudo apt install -y mosquitto mosquitto-clients
   sudo systemctl enable mosquitto
   ```

2. Install Node-RED:
   ```bash
   bash <(curl -sL https://raw.githubusercontent.com/node-red/linux-installers/master/deb/update-nodejs-and-nodered)
   sudo systemctl enable nodered
   ```

3. Install required Node-RED nodes:
   ```bash
   cd ~/.node-red
   npm install node-red-dashboard node-red-node-serialport
   ```

4. Start Node-RED:
   ```bash
   node-red-start
   ```

### On ESP32:
1. Update the MQTT broker IP to your Raspberry Pi's IP
2. Upload the provided code to ESP32

## Expected Output
- Real-time sensor data visualization on Node-RED dashboard
- Ability to control the LED from the dashboard
- MQTT message logging in the terminal

## Accessing the Dashboard
1. Open a web browser on any device in the same network
2. Navigate to: `http://<raspberry-pi-ip>:1880/ui`
3. You should see the sensor data and control panel
