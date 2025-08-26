# IoT Lab

Welcome to the IoT Lab repository! This repository contains a collection of hands-on experiments and projects focused on Internet of Things (IoT) development.

## Getting Started

1. **Prerequisites**
   - Arduino IDE or PlatformIO
   - ESP32 or compatible development board
   - Required libraries (specified in each experiment)

2. **Repository Structure**
   ```
   ├── experiments/
   │   ├── experiment1/     # Basic Bluetooth Communication between ESP32 and Smart Phone
   │   ├── experiment2/     # Digital Input/Output Bluetooth Communication between ESP32 and Smart Phone
   │   ├── experiment3/     # Analog Input/Output 
   │   ├── experiment4/     # PWM and Servo Control
   │   ├── experiment5/     # Sensor Interfacing
   │   ├── experiment6/     # Wireless Communication
   │   ├── experiment7/     # MQTT Protocol
   │   ├── experiment8/     # Web Server
   │   └── experiment9/     # Node-RED Integration
   ```

## How to Use

1. Clone the repository:
   ```bash
   git clone https://github.com/veerakrish/IoT.git
   ```

2. Navigate to the desired experiment directory:
   ```bash
   cd IoT/experiments/experiment1
   ```

3. Open the `.ino` file in your Arduino IDE or PlatformIO

4. Install any required libraries (check the experiment's README)

5. Upload the code to your board

## Experiment List

1. **Basic LED Blink** - Introduction to digital output
2. **Digital Input/Output** - Working with buttons and LEDs
3. **Analog Input/Output** - Reading sensors and PWM control
4. **PWM and Servo Control** - Controlling servo motors
5. **Sensor Interfacing** - Working with various sensors
6. **Wireless Communication** - ESP-NOW and WiFi communication
7. **MQTT Protocol** - IoT messaging protocol
8. **Web Server** - Creating a web interface
9. **Node-RED Integration** - Visual programming for IoT

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## Setting Up MQTT Broker on Render.com

For experiments involving MQTT (like Experiment 7), you'll need to set up your own MQTT broker. Here's how to deploy one for free on Render.com:

1. **Create a new Web Service**
   - Go to [Render.com](https://render.com) and sign up/log in
   - Click "New" and select "Web Service"
   - Connect your GitHub repository or use the provided Docker configuration

2. **Configure the Service**
   - Service Name: `your-mqtt-broker`
   - Region: Choose the one closest to you
   - Branch: `main` or your working branch
   - Runtime: Docker

3. **Docker Configuration**
   Create a `Dockerfile` in your project root:
   ```dockerfile
   FROM eclipse-mosquitto:2.0
   COPY mosquitto.conf /mosquitto/config/mosquitto.conf
   ```

4. **Create mosquitto.conf**
   Create a `mosquitto.conf` file:
   ```
   listener 1883
   allow_anonymous true
   ```

5. **Environment Variables**
   In Render.com dashboard, add these environment variables:
   ```
   PORT=1883
   ```

6. **Deploy**
   - Push your changes to GitHub
   - Render will automatically deploy your MQTT broker
   - Find your broker URL in the Render dashboard (it will be something like `your-mqtt-broker.onrender.com`)

7. **Testing**
   Use an MQTT client to test your broker:
   - Host: `your-mqtt-broker.onrender.com`
   - Port: `1883`
   - No username/password needed (for development only)

> **Note:** The free tier has limitations. For production use, consider upgrading or using a dedicated MQTT service.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
