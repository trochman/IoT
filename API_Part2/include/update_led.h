#ifndef UPDATE_LED_H
#define UPDATE_LED_H

void updateFromJson(bool updateRgb);
String extractValue(const String& json, const String& key);
int extractIntValue(const String& json, const String& key);
bool checkButtonPressed(int buttonPin);

#endif // UPDATE_LED_H