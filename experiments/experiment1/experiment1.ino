#include <BluetoothSerial.h>
#include <DHT.h>

#define DHTPIN 4       // DHT11 data pin connected to GPIO4
#define DHTTYPE DHT11  // DHT 11

DHT dht(DHTPIN, DHTTYPE);
BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT"); // Bluetooth device name
  Serial.println("Bluetooth Started! Ready to pair...");
  
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements
  delay(2000);
  
  // Reading temperature and humidity
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // Read temperature as Celsius
  
  // Check if any reads failed
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  // Print to Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" °C");
  
  // Send data over Bluetooth
  SerialBT.print("Temperature: ");
  SerialBT.print(t);
  SerialBT.print("°C, Humidity: ");
  SerialBT.print(h);
  SerialBT.println("%");
}
