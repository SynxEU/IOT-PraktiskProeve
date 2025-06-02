#include "humidity.h"

void showHumidityDisplay(DHT& dht, Adafruit_SSD1306& display) {
  // Reading humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Humitity
  display.print("H: ");
  display.print((int)h);
  display.println("%");
}
