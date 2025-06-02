#ifndef TIME_H
#define TIME_H

#include <Adafruit_SSD1306.h>
#include <RTClib.h>

void showTimeDisplay(RTC_DS3231& rtc, Adafruit_SSD1306& display);

#endif
