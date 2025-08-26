#include <WiFi.h>
#include <WiFiUdp.h>
#include <DHT.h>

// WiFi credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// DHT Sensor
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// UDP for mesh communication
WiFiUDP udp;
unsigned int localUdpPort = 4210;  // Local port to listen on
IPAddress broadcastIP(255, 255, 255, 255);  // Broadcast address
const int udpPort = 4210;  // Port to send to

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  // Connect to WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  // Start UDP
  if (udp.begin(localUdpPort)) {
    Serial.println("UDP started");
  }
}

void loop() {
  static unsigned long lastUpdate = 0;
  
  // Send sensor data every 5 seconds
  if (millis() - lastUpdate > 5000) {
    lastUpdate = millis();
    
    // Read sensor data
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    
    // Create message
    char message[50];
    snprintf(message, sizeof(message), "SENSOR_DATA:%.1f:%.1f", t, h);
    
    // Send broadcast message
    udp.beginPacket(broadcastIP, udpPort);
    udp.write((uint8_t*)message, strlen(message));
    udp.endPacket();
    
    Serial.print("Sent: ");
    Serial.println(message);
  }
  
  // Check for incoming packets
  int packetSize = udp.parsePacket();
  if (packetSize) {
    char incomingPacket[255];
    int len = udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = 0;
    }
    Serial.print("Received: ");
    Serial.println(incomingPacket);
  }
  
  delay(100);
}
