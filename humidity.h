#ifndef HUMIDITY_H
#define HUMIDITY_H

#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

void showHumidityDisplay(DHT& dht, Adafruit_SSD1306& display);

#endif
