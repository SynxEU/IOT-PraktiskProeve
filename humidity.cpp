#include "humidity.h"

void showHumidityDisplay(DHT& dht, Adafruit_SSD1306& display) {
  // Delay
  unsigned int currentMillis = millis();
  unsigned int previousMillis = 0;
  const int interval = 3000;
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    // Reading humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();

    // Check if any reads failed and exit early (to try again).
    if (isnan(h)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }

    // Humitity display
    display.println("Humidity");
    display.print((int)h);
    display.print("%");
  }
}
