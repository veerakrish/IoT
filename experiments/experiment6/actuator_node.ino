#include <WiFi.h>
#include <WiFiUdp.h>

// WiFi credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// LED Pin
#define LED_PIN 16

// UDP for mesh communication
WiFiUDP udp;
unsigned int localUdpPort = 4210;  // Local port to listen on
IPAddress broadcastIP(255, 255, 255, 255);  // Broadcast address
const int udpPort = 4210;  // Port to send to

// Temperature threshold for LED control
const float TEMP_THRESHOLD = 25.0;  // °C

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
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
  
  // Send a hello message
  udp.beginPacket(broadcastIP, udpPort);
  udp.write("ACTUATOR_NODE_READY");
  udp.endPacket();
}

void loop() {
  // Check for incoming packets
  int packetSize = udp.parsePacket();
  if (packetSize) {
    char incomingPacket[255];
    int len = udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = 0;
      
      // Process the received message
      if (strncmp(incomingPacket, "SENSOR_DATA:", 12) == 0) {
        // Extract temperature from message (format: "SENSOR_DATA:temperature:humidity")
        char* token = strtok(incomingPacket, ":");
        token = strtok(NULL, ":");  // Get temperature
        float temperature = atof(token);
        
        // Control LED based on temperature
        if (temperature > TEMP_THRESHOLD) {
          digitalWrite(LED_PIN, HIGH);
          Serial.println("Temperature above threshold - LED ON");
        } else {
          digitalWrite(LED_PIN, LOW);
          Serial.println("Temperature below threshold - LED OFF");
        }
        
        // Send acknowledgment
        char ack[50];
        snprintf(ack, sizeof(ack), "ACK:%.1fC_%s", temperature, 
                (temperature > TEMP_THRESHOLD) ? "ON" : "OFF");
                
        IPAddress senderIP = udp.remoteIP();
        udp.beginPacket(senderIP, udpPort);
        udp.write((uint8_t*)ack, strlen(ack));
        udp.endPacket();
      }
      
      Serial.print("Received: ");
      Serial.println(incomingPacket);
    }
  }
  
  delay(100);
}
