#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

// WiFi & ThingSpeak settings
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* server = "api.thingspeak.com";
String apiKey = "YOUR_THINGSPEAK_API_KEY";

// Pins
#define DHTPIN 4
#define DHTTYPE DHT11
#define PIR_PIN 33
#define LED_PIN 16
#define BUZZER_PIN 17

DHT dht(DHTPIN, DHTTYPE);
float lastTemp = 0;
bool motionDetected = false;

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  dht.begin();
  connectToWiFi();
}

void loop() {
  // Read sensors
  float temp = dht.readTemperature();
  if (!isnan(temp)) lastTemp = temp;
  bool motion = digitalRead(PIR_PIN) == HIGH;
  if (motion != motionDetected) {
    motionDetected = motion;
    digitalWrite(LED_PIN, motionDetected ? HIGH : LOW);
  }
  
  // Control buzzer
  digitalWrite(BUZZER_PIN, lastTemp > 30.0 ? HIGH : LOW);
  
  // Send data every 15s
  static unsigned long lastSend = 0;
  if (millis() - lastSend > 15000) {
    if (WiFi.status() == WL_CONNECTED) {
      sendToThingSpeak(temp, dht.readHumidity(), motionDetected);
    } else {
      connectToWiFi();
    }
    lastSend = millis();
  }
  
  delay(100);
}

void connectToWiFi() {
  WiFi.begin(ssid, password);
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts++ < 20) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.status() == WL_CONNECTED ? "\nWiFi connected" : "\nWiFi failed");
}

void sendToThingSpeak(float temp, float hum, bool motion) {
  HTTPClient http;
  String url = "http://" + String(server) + "/update?api_key=" + apiKey +
               "&field1=" + String(temp) +
               "&field2=" + String(hum) +
               "&field3=" + String(motion ? 1 : 0);
  http.begin(url);
  int code = http.GET();
  Serial.print("ThingSpeak response: ");
  Serial.println(code);
  http.end();
}
