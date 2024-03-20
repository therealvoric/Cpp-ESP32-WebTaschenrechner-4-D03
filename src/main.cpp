#include <WiFi.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "FORTI_INTERNET_2G4";
const char* password = "HTLInternet";

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Initialize SPIFFS
  if (!SPIFFS.begin()) {
    Serial.println("Failed to mount SPIFFS");
    return;
  }

  // Connect to WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/index.html", "text/html");
  });
  // Route for CSS file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });
  // Route for JavaScript file
  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/script.js", "text/javascript");
  });
  // Start server
  server.begin();
}

void loop() {}
