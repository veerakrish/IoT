#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

#define LED_PIN 16  // LED connected to GPIO 16
WebServer server(80);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  Serial.begin(115200);
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi connected. IP: " + WiFi.localIP().toString());
  
  // Setup web server routes
  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);
  server.on("/status", handleStatus);
  
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  delay(2);
}

void handleRoot() {
  String html = "<html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  html += "<title>ESP32 LED Control</title>";
  html += "<style>";
  html += "body{font-family: Arial, sans-serif; text-align: center; margin-top: 50px;}";
  html += ".btn{display: inline-block; padding: 15px 25px; font-size: 24px; ";
  html += "cursor: pointer; text-align: center; text-decoration: none; outline: none;";
  html += "color: #fff; background-color: #4CAF50; border: none; border-radius: 15px;";
  html += "box-shadow: 0 9px #999; margin: 10px;}";
  html += ".btn:active{background-color: #3e8e41; box-shadow: 0 5px #666; transform: translateY(4px);}";
  html += ".off{background-color: #f44336;}";
  html += "</style></head><body>";
  
  html += "<h1>ESP32 LED Control</h1>";
  html += "<button id='toggleBtn' class='btn' onclick='toggleLED()'>Toggle LED</button>";
  
  html += "<script>";
  html += "function toggleLED(){fetch('/toggle').then(r=>r.text()).then(s=>{";
  html += "const btn=document.getElementById('toggleBtn');";
  html += "if(s=='ON'){btn.classList.add('off');btn.textContent='Turn OFF';}";
  html += "else{btn.classList.remove('off');btn.textContent='Turn ON';}});}";
  
  // Initial state
  html += "window.onload=()=>{setInterval(()=>{fetch('/status').then(r=>r.text())";
  html += ".then(s=>{const btn=document.getElementById('toggleBtn');";
  html += "if(s=='ON'){btn.classList.add('off');btn.textContent='Turn OFF';}";
  html += "else{btn.classList.remove('off');btn.textContent='Turn ON';}});},1000);}";
  
  html += "</script></body></html>";
  
  server.send(200, "text/html", html);
}

void handleToggle() {
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  server.send(200, "text/plain", digitalRead(LED_PIN) ? "ON" : "OFF");
}

void handleStatus() {
  server.send(200, "text/plain", digitalRead(LED_PIN) ? "ON" : "OFF");
}
