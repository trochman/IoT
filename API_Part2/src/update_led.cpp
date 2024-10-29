#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include "update_led.h"

// Define host URL
const char* hostingerUrl = "arochman.net"; // Update with your host

// LED pin definitions
#define LED_PIN 12 // GPIO12 (D6) for regular LED
#define RED_PIN 16 // GPIO16 (D0) for Red channel of RGB LED
#define GREEN_PIN 5 // GPIO5 (D1) for Green channel of RGB LED
#define BLUE_PIN 4 // GPIO4 (D2) for Blue channel of RGB LED

void sendRequest(const String& endpoint) {
    WiFiClient client;
    if (client.connect(hostingerUrl, 80)) {
        client.print(String("GET /API_Assignment/") + endpoint + " HTTP/1.1\r\n" +
                     "Host: " + String(hostingerUrl) + "\r\n" +
                     "Connection: close\r\n\r\n");
        Serial.println("Request sent to: " + endpoint);
        client.stop();
    } else {
        Serial.println("Connection to Hostinger failed");
    }
}

void updateFromJson() {
    WiFiClient client;
    if (client.connect(hostingerUrl, 80)) {
        client.print(String("GET /API_Assignment/results.txt HTTP/1.1\r\n") +
                     "Host: " + String(hostingerUrl) + "\r\n" +
                     "Connection: close\r\n\r\n");

        String response = "";
        while (client.connected() || client.available()) {
            if (client.available()) {
                response += client.readString();
            }
        }
        client.stop();

        // Parse JSON data
        JsonDocument doc = JsonDocument();  // Create JsonDocument
        DeserializationError error = deserializeJson(doc, response);

        if (!error) {
            String ledState = doc["LED_1"]; // Regular LED state
            String rgbState = doc["RGB_LED"]; // RGB LED state
            int red = doc["R"];
            int green = doc["G"];
            int blue = doc["B"];

            // Update regular LED
            if (ledState == "on") {
                digitalWrite(LED_PIN, HIGH); // Turn on the regular LED
            } else {
                digitalWrite(LED_PIN, LOW); // Turn off the regular LED
            }

            // Update RGB LED
            analogWrite(RED_PIN, red);
            analogWrite(GREEN_PIN, green);
            analogWrite(BLUE_PIN, blue);
        } else {
            Serial.println("Failed to parse JSON");
        }
    } else {
        Serial.println("Connection to Hostinger failed");
    }
}