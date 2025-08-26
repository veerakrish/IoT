// Motor control pins
const int enA = 25;  // PWM pin for speed control
const int in1 = 26;  // Control pin 1
const int in2 = 27;  // Control pin 2

// PWM properties
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;  // 8-bit resolution (0-255)

void setup() {
  Serial.begin(115200);
  
  // Configure motor control pins as outputs
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  // Configure LED PWM functionalitites
  ledcSetup(pwmChannel, freq, resolution);
  
  // Attach the channel to the GPIO to be controlled
  ledcAttachPin(enA, pwmChannel);
  
  Serial.println("DC Motor Control with L298N");
  Serial.println("---------------------------");
  Serial.println("Motor will run forward, then backward, then stop");
}

void loop() {
  // Run motor forward at 50% speed
  Serial.println("Motor Forward - 50% speed");
  setMotor(128, true);  // 128/255 ≈ 50% speed
  delay(5000);
  
  // Run motor backward at 50% speed
  Serial.println("Motor Backward - 50% speed");
  setMotor(128, false);
  delay(5000);
  
  // Stop motor
  Serial.println("Motor Stop");
  stopMotor();
  delay(2000);
  
  // Ramp up speed forward
  Serial.println("Ramping up speed forward");
  for (int i = 0; i <= 255; i++) {
    setMotor(i, true);
    delay(20);
  }
  delay(1000);
  
  // Ramp down speed
  Serial.println("Ramping down speed");
  for (int i = 255; i >= 0; i--) {
    setMotor(i, true);
    delay(20);
  }
  stopMotor();
  delay(2000);
}

// Function to control motor speed and direction
// speed: 0-255 (0 = off, 255 = full speed)
// direction: true = forward, false = backward
void setMotor(int speed, bool direction) {
  // Ensure speed is within valid range
  speed = constrain(speed, 0, 255);
  
  // Set motor direction
  if (direction) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
  
  // Set motor speed using PWM
  ledcWrite(pwmChannel, speed);
}

// Function to stop the motor
void stopMotor() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  ledcWrite(pwmChannel, 0);
}
