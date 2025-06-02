#include "time.h"

void showTimeDisplay(RTC_DS3231& rtc, Adafruit_SSD1306& display) {
  // Reading datetime
  DateTime now = rtc.now();
  // dd:MM:yyyy
  display.print(now.day(), DEC);
  display.print('/');
  display.print(now.month(), DEC);
  display.print('/');
  display.println(now.year(), DEC);

  // HH:mm:ss
  if (now.hour() < 10) display.print("0");
  display.print(now.hour(), DEC);
  display.print(':');

  if (now.minute() < 10) display.print("0");
  display.print(now.minute(), DEC);
  display.print(':');

  if (now.second() < 10) display.print("0");
  display.println(now.second(), DEC);
}
