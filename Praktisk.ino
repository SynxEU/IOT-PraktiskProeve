// OLED Display
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

bool showTime = true;

// RTC
#include "RTClib.h"

// Initialize RTC
RTC_DS3231 rtc;

// DHT
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11  // DHT 11

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

// Millis
unsigned int previousMillis = 0;
const int interval = 3000;

// Extra
#include "time.h"
#include "temp.h"
#include "humidity.h"

void setup() {
  Serial.begin(9600);

  dht.begin();

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }

  display.cp437(true);  // Code page 437
}

void loop() {
  // Delay
  unsigned int currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    showTime = !showTime;

    // Clearing display
    display.clearDisplay();
    // Display Text
    display.setTextSize(2);       // 2:1 (Pixels) Scale
    display.setTextColor(WHITE);  // Text Color
    display.setCursor(0, 0);      // Cursor Placement

    if (showTime) {
      showTimeDisplay(rtc, display);
    } else {
      showHumidityDisplay(dht, display);
      showTempDisplay(dht, display);
    }
    display.display();
  }
}
