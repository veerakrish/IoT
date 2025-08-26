#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi connected. IP: " + WiFi.localIP().toString());
  
  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.begin();
}

void loop() {
  server.handleClient();
  delay(2);
}

void handleRoot() {
  String html = "<html><body>";
  html += "<h1>ESP32 Web Server</h1>";
  html += "<p>Temperature: <span id='temp'>--</span> °C</p>";
  html += "<p>Humidity: <span id='humidity'>--</span> %</p>";
  html += "<script>setInterval(()=>{fetch('/data').then(r=>r.json()).then(d=>{document.getElementById('temp').innerText=d.t;document.getElementById('humidity').innerText=d.h;});},2000);</script>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleData() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if (isnan(h) || isnan(t)) {
    server.send(500, "text/plain", "Sensor error");
    return;
  }
  
  String json = "{\"t\":" + String(t, 1) + ",\"h\":" + String(h, 1) + "}";
  server.send(200, "application/json", json);
}
