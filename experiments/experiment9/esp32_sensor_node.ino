#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// WiFi & MQTT settings
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* mqtt_server = "RASPBERRY_PI_IP";

// Pins
#define DHTPIN 4
#define DHTTYPE DHT11
#define PIR_PIN 33
#define LED_PIN 16

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHTTYPE);

// Topics
const char* topic_temp = "sensors/esp32/temp";
const char* topic_humidity = "sensors/esp32/humidity";
const char* topic_motion = "sensors/esp32/motion";
const char* topic_led = "actuators/esp32/led";

void setup_wifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
}

void callback(char* topic, byte* payload, unsigned int length) {
  if (String(topic) == topic_led) {
    String message;
    for (int i=0; i<length; i++) message += (char)payload[i];
    digitalWrite(LED_PIN, message == "ON" ? HIGH : LOW);
  }
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP32Client")) {
      client.subscribe(topic_led);
    } else {
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);
  dht.begin();
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();
  
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate > 2000) {
    lastUpdate = millis();
    
    // Read sensors
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    bool m = digitalRead(PIR_PIN);
    
    // Publish data
    if (!isnan(t)) client.publish(topic_temp, String(t).c_str());
    if (!isnan(h)) client.publish(topic_humidity, String(h).c_str());
    client.publish(topic_motion, m ? "1" : "0");
  }
}
