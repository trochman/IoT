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
    WiFi.begin(ssid, password);

    pinMode(buttonRgbPin, INPUT_PULLUP); // Use internal pull-up resistor
    pinMode(buttonLedPin, INPUT_PULLUP); // Use internal pull-up resistor
    pinMode(buttonRgbPin, INPUT_PULLUP); // Use internal pull-up resistor
    pinMode(buttonLedPin, INPUT_PULLUP); // Use internal pull-up resistor
    pinMode(LED_PIN, OUTPUT);              // Set LED_PIN (D6) as OUTPUT
    pinMode(RED_PIN, OUTPUT);               // Set RGB pins as OUTPUT
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);
    
    // Initialize both the regular LED and RGB LED to be off
    digitalWrite(LED_PIN, LOW);            // Turn off regular LED
    analogWrite(RED_PIN, 0);               // Turn off RGB red channel
    analogWrite(GREEN_PIN, 0);             // Turn off RGB green channel
    analogWrite(BLUE_PIN, 0);              // Turn off RGB blue channel
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(2000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi!");
}