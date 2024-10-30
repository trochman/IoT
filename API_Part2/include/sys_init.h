#ifndef SYS_INIT_H
#define SYS_INIT_H

void sysInit();
extern const int buttonRgbPin;
extern const int buttonLedPin;
#define LED_PIN 12    // GPIO12 (D6) for regular LED
#define RED_PIN 16    // GPIO16 (D0) for Red channel of RGB LED
#define GREEN_PIN 5    // GPIO5 (D1) for Green channel of RGB LED
#define BLUE_PIN 4     // GPIO4 (D2) for Blue channel of RGB LED

#endif // SYS_INIT_H