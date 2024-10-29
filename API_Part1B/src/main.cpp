#include <Arduino.h>
#include "sys_init.h"
#include "button.h"

void setup() {
  Serial.begin(115200);   // Set baud rate to match serial monitor
  delay(500);            // Short delay to allow serial monitor to initialize
  Serial.println("");

  // Connect to WiFi, setup buttons, etc.
  sysInit();  
}

void loop() {
  // Continuously monitor Button 1 press for sending a message to iotdata channel in ssuee.slack.com
  monitorButtonPress();

  // Delay to avoid excessive polling
  delay(100);
}