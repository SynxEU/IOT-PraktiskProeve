#include "temp.h"

void showTempDisplay(DHT& dht, Adafruit_SSD1306& display) {
  // Reading temperature takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Temperature
  display.print("Temp: ");
  display.print((int)t);
  display.write(0xF8); // Degree Symbol
  display.println("C");
}
