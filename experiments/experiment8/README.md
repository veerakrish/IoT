# Experiment 8: DC Motor Control with L298N

## Objective
Interface ESP32 with a DC motor using the L298N motor driver and control its speed and direction.

## Components Required
1. ESP32 Dev Kit V1
2. L298N Motor Driver
3. DC Motor (5-12V)
4. External Power Supply (6-12V) for motor
5. Jumper Wires
6. Breadboard

## Connections
### L298N to ESP32:
- IN1 → GPIO 26
- IN2 → GPIO 27
- ENA → GPIO 25 (PWM for speed control)
- 12V → External power supply positive
- GND → External power supply negative and ESP32 GND
- 5V → (Optional) Can power ESP32 if jumper is removed

### Motor Connections:
- Motor Terminal 1 → L298N OUT1
- Motor Terminal 2 → L298N OUT2

## Setup Instructions
1. Connect the L298N to ESP32 as per the pin configuration
2. Connect the DC motor to the L298N outputs
3. Connect the external power supply to the L298N
4. Upload the code to ESP32
5. Open the Serial Monitor (115200 baud)

## Expected Output
- The motor will run forward for 5 seconds at 50% speed
- Then reverse direction for 5 seconds at 50% speed
- Then stop for 2 seconds
- The cycle will repeat

## Safety Notes
- Ensure proper power supply for the motor (6-12V)
- Make sure to connect the grounds of ESP32 and L298N
- Double-check all connections before powering on
