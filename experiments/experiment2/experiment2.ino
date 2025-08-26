#include <BluetoothSerial.h>

#define LED_PIN 16  // LED connected to GPIO 16
BluetoothSerial SerialBT;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);  // Start with LED off
  
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT_LED"); // Bluetooth device name
  Serial.println("Bluetooth LED Control Ready!");
  Serial.println("Send '1' to turn ON LED");
  Serial.println("Send '0' to turn OFF LED");
}

void loop() {
  if (SerialBT.available()) {
    char command = SerialBT.read();
    
    if (command == '1') {
      digitalWrite(LED_PIN, HIGH);  // Turn LED ON
      SerialBT.println("LED: ON");
      Serial.println("LED: ON");
    }
    else if (command == '0') {
      digitalWrite(LED_PIN, LOW);   // Turn LED OFF
      SerialBT.println("LED: OFF");
      Serial.println("LED: OFF");
    }
  }
  
  delay(20); // Small delay to prevent watchdog trigger
}
