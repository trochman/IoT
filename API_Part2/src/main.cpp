#include <Arduino.h>
#include "sys_init.h"
#include "update_led.h"

// Function prototypes
void handleButtonPresses();

void setup() {
    Serial.begin(115200);
    delay(2500); // Allow serial monitor to initialize

    // Initialize the system and buttons
    sysInit();
}

void loop() {
    handleButtonPresses();
    delay(1000); // Delay to avoid overwhelming requests
}

void handleButtonPresses() {
    if (checkButtonPressed(D3)) { // D3 for RGB button
        updateFromJson(true); // Indicate RGB LED update
    }
    
    if (checkButtonPressed(D5)) { // D5 for regular LED button
        updateFromJson(false); // Indicate regular LED update
    }
}