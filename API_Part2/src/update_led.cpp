#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include "update_led.h"
#include "sys_init.h"

// Define host URL
const char* hostingerUrl = "https://arochman.net";

WiFiClientSecure client;  // WiFiClientSecure object
HTTPClient https;         // HTTPClient object for handling requests

void updateFromJson(bool updateRgb) {
    String url = String(hostingerUrl) + "/API_Assignment/results.txt";  // Construct URL

    // Disable SSL certificate verification
    client.setInsecure();

    // Begin the HTTP request
    https.begin(client, url);

    int httpsCode = https.GET();  // Perform the GET request

    if (httpsCode == HTTP_CODE_OK) {
        String payload = https.getString();

        // Print the payload for debugging
        Serial.println("HTTP Response:");
        Serial.println(payload);

        // Parse the JSON response
        DynamicJsonDocument doc(1024);
        DeserializationError error = deserializeJson(doc, payload);

        if (error) {
            Serial.print("Failed to parse JSON: ");
            Serial.println(error.f_str());
        } else {
            // Extract values from the JSON document
            String ledState = doc["ledState"].as<String>();
            String rgbState = doc["rgbState"].as<String>();
            int red = doc["R"].as<int>();
            int green = doc["G"].as<int>();
            int blue = doc["B"].as<int>();

            // Update based on which LED to update
            if (updateRgb) {
                if (rgbState == "on") {
                    analogWrite(RED_PIN, red);
                    analogWrite(GREEN_PIN, green);
                    analogWrite(BLUE_PIN, blue);
                } else {
                    analogWrite(RED_PIN, 0);
                    analogWrite(GREEN_PIN, 0);
                    analogWrite(BLUE_PIN, 0);
                }
            } else {
                digitalWrite(LED_PIN, ledState == "on" ? HIGH : LOW); // Turn on/off regular LED
            }
        }
    } else {
        Serial.print("HTTPS response code: ");
        Serial.println(httpsCode);
        String errorResponse = https.getString();
        Serial.println("Error response: " + errorResponse);  // Print error response
    }

    // End the HTTP connection
    https.end();
}

// Check button pressed
bool checkButtonPressed(int buttonPin) {
    static bool lastButtonState[2] = {HIGH, HIGH}; // Assume buttons are not pressed
    int index = (buttonPin == buttonRgbPin) ? 0 : 1; // Determine index for button

    bool currentButtonState = digitalRead(buttonPin);
    
    // Check for button press (transition from HIGH to LOW)
    if (lastButtonState[index] == HIGH && currentButtonState == LOW) {
        lastButtonState[index] = currentButtonState; // Update last state
        return true; // Button pressed
    }
    
    lastButtonState[index] = currentButtonState; // Update last state
    return false; // Button not pressed
}