#ifndef TEMP_H
#define TEMP_H

#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

void showTempDisplay(DHT& dht, Adafruit_SSD1306& display);

#endif
