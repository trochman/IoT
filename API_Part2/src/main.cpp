#include <Arduino.h>
#include "sys_init.h"
#include "update_led.h"

// Function prototypes
void handleButtonPresses();

void setup() {
    Serial.begin(115200);
    delay(500); // Allow serial monitor to initialize
    Serial.println("");

    // Initialize the system and buttons
    sysInit();
}

void loop() {
    handleButtonPresses();
    updateFromJson(); // Update LED states from JSON
    delay(1000); // Delay to avoid overwhelming requests
}

void handleButtonPresses() {
    if (checkButtonPressed(D3)) { // D3 for RGB button
        sendRequest("update_rgb.php");
    }
    
    if (checkButtonPressed(D5)) { // D5 for regular LED button
        sendRequest("update_led.php");
    }
}