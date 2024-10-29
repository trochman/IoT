#include <ESP8266WiFi.h>
#include "sys_init.h"

// Wi-Fi credentials
const char* ssid = "iPhone (4)";
const char* password = "p27v4kxs9abqn";

// Button pin definitions
const int buttonRgbPin = 0; // GPIO0 (D3) for RGB button
const int buttonLedPin = 14; // GPIO14 (D5) for regular LED button

void sysInit() {
    Serial.begin(115200);
    pinMode(buttonRgbPin, INPUT_PULLUP); // Use internal pull-up resistor
    pinMode(buttonLedPin, INPUT_PULLUP); // Use internal pull-up resistor
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(2000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi!");
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