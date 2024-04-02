#include <WiFi.h>

const char* ssid = "Free wifi";
const char* password = "spm112233";
const int port = 8888;

WiFiServer server(port);
WiFiClient client;

void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT); // set the LED pin mode to pin 13
  connectToWiFi();
  startServer();
}

void loop() {
  if (client.connected()) {
    if (client.available()) {
      String message = client.readStringUntil('\n');
      message.trim(); // Trim the whitespace
      Serial.println("Received message: " + message);
      // Process the received message here
      if (message.equals("green")) {
        digitalWrite(13, HIGH); // Turn on the LED
        Serial.println("Green button clicked");
      } else if (message.equals("red")) {
        digitalWrite(13, LOW); // Turn off the LED
        Serial.println("Red button clicked");
      }
    }
  } else {
    client = server.available();
  }
}

void connectToWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void startServer() {
  server.begin();
  Serial.println("Server started");
}
