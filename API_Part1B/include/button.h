#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

#define BUTTON_PIN D3

void monitorButtonPress();
void iftttSlackMessage();

#endif // BUTTON_H