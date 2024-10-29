#include <ESP8266WiFi.h>
#include "sys_init.h"
#include "button.h"

const char* ssid = "iPhone (4)";
const char* password = "p27v4kxs9abqn";

// Wi-Fi connection function
void connectToWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(2000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");
}

// System initialization
void sysInit() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Button for sending a message to iotdata channel in ssuee.slack.com

  // Connect to Wi-Fi
  connectToWiFi();
}