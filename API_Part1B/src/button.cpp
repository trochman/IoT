#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include "button.h"

#define BUTTON_PIN D3    // Button for sending a message to iotdata channel in ssuee.slack.com

WiFiClientSecure client;  // WiFiClient object
HTTPClient https;  // Declare the HTTPClient object

int previousButtonState = HIGH;  // Previous state of Button

// Function to monitor Button press for sending a message to iotdata channel in ssuee.slack.com
void monitorButtonPress() {
  int buttonState = digitalRead(BUTTON_PIN);

  // Only check for press if the previous state was HIGH (button not pressed)
  if (buttonState == LOW && previousButtonState == HIGH) {
    delay(200);  // Small delay to avoid multiple presses being registered too quickly

    // Display the selected time zone for the user to view
    Serial.println("Button Pressed!");

    // Fetch current time after time zone selection
    iftttSlackMessage();

    previousButtonState = buttonState;  // Update previous state
  } else if (buttonState == HIGH) {
    previousButtonState = buttonState;  // If the button is not pressed, update the state
  }
}

void iftttSlackMessage() {
    // Construct the URL for the IFTTT webhook
  String url = "https://maker.ifttt.com/trigger/button_pressed/json/with/key/JlGpjH6VHnDtjIrD6hy78";

  // Print the URL for debugging
  Serial.println("Sending PUT request to URL: " + url);

  // Use WiFiClientSecure to handle the HTTPS connection
  client.setInsecure();  // Disable SSL certificate verification, useful for debugging

  // Begin the HTTP request with the secure client and HTTPS URL
  https.begin(client, url);

  // Perform the PUT request without a payload
  https.addHeader("Content-Type", "application/json");
  int httpsCode = https.PUT("");  // Perform the PUT request with an empty payload

  // Check the HTTP response code
  if (httpsCode == HTTP_CODE_OK) {
    String payload = https.getString();
    Serial.println("Response: " + payload);
    Serial.println("Message sent to iotdata Slack channel successfully!");
  } else {
    Serial.print("HTTP response code: ");
    Serial.println(httpsCode);
    String errorResponse = https.getString();
    Serial.println("Error response: " + errorResponse);  // Print error response
  }

  // End the HTTP connection
  https.end();
}